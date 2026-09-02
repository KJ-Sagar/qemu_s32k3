/*
 * NXP S32K3X8 FlexCAN model (minimal MCAL-oriented implementation).
 *
 * This model focuses on the register and mailbox behavior needed for
 * AUTOSAR MCAL FlexCAN bring-up on S32K3X8 QEMU.
 */

#include "qemu/osdep.h"
#include "qapi/error.h"
#include "qemu/log.h"
#include "qemu/module.h"
#include "hw/core/irq.h"
#include "hw/core/qdev-properties.h"
#include "hw/net/s32k3_flexcan.h"

/* Core register offsets (S32K3xx FlexCAN layout). */
#define FLEXCAN_MCR_OFFSET             0x000
#define FLEXCAN_CTRL1_OFFSET           0x004
#define FLEXCAN_TIMER_OFFSET           0x008
#define FLEXCAN_RXMGMASK_OFFSET        0x010
#define FLEXCAN_RX14MASK_OFFSET        0x014
#define FLEXCAN_RX15MASK_OFFSET        0x018
#define FLEXCAN_ECR_OFFSET             0x01c
#define FLEXCAN_ESR1_OFFSET            0x020
#define FLEXCAN_IMASK2_OFFSET          0x024
#define FLEXCAN_IMASK1_OFFSET          0x028
#define FLEXCAN_IFLAG2_OFFSET          0x02c
#define FLEXCAN_IFLAG1_OFFSET          0x030
#define FLEXCAN_CTRL2_OFFSET           0x034
#define FLEXCAN_IMASK3_OFFSET          0x06c
#define FLEXCAN_IFLAG3_OFFSET          0x074
#define FLEXCAN_RXIMR_OFFSET           0x880

/* Message buffer RAM (classic CAN payload: 16 bytes / MB). */
#define FLEXCAN_MB_OFFSET              0x080
#define FLEXCAN_MB_STRIDE              0x10
#define FLEXCAN_MB_WORDS               4
#define FLEXCAN_MB_COUNT               32

/* MCR bits used by MCAL startup/stop sequence. */
#define FLEXCAN_MCR_MAXMB_MASK         0x0000007fU
#define FLEXCAN_MCR_IRMQ_MASK          0x00010000U
#define FLEXCAN_MCR_LPMACK_MASK        0x00100000U
#define FLEXCAN_MCR_FRZACK_MASK        0x01000000U
#define FLEXCAN_MCR_SOFTRST_MASK       0x02000000U
#define FLEXCAN_MCR_NOTRDY_MASK        0x08000000U
#define FLEXCAN_MCR_HALT_MASK          0x10000000U
#define FLEXCAN_MCR_FRZ_MASK           0x40000000U
#define FLEXCAN_MCR_MDIS_MASK          0x80000000U

/* MB CS field bits. */
#define FLEXCAN_CS_TIMESTAMP_MASK      0x0000ffffU
#define FLEXCAN_CS_DLC_MASK            0x000f0000U
#define FLEXCAN_CS_DLC_SHIFT           16
#define FLEXCAN_CS_RTR_MASK            0x00100000U
#define FLEXCAN_CS_IDE_MASK            0x00200000U
#define FLEXCAN_CS_CODE_MASK           0x0f000000U
#define FLEXCAN_CS_CODE_SHIFT          24

#define FLEXCAN_STD_ID_SHIFT           18

/* MB code values used by MCAL. */
#define FLEXCAN_RX_FULL                0x2U
#define FLEXCAN_RX_EMPTY               0x4U
#define FLEXCAN_TX_INACTIVE            0x8U
#define FLEXCAN_TX_ABORT               0x9U
#define FLEXCAN_TX_DATA_CODE           0xcU

/* ESR1 is mostly W1C from software perspective. */
#define FLEXCAN_ESR1_W1C_MASK          0xffffffffU

static inline uint32_t flexcan_reg_index(hwaddr addr)
{
    return (uint32_t)(addr >> 2);
}

static inline uint32_t *flexcan_mb_addr(S32K3X8FlexCANState *s, unsigned mb_idx)
{
    return &s->regs[flexcan_reg_index(FLEXCAN_MB_OFFSET +
                                      (mb_idx * FLEXCAN_MB_STRIDE))];
}

static inline bool flexcan_is_mb_cs_addr(hwaddr addr, unsigned *mb_idx)
{
    if (addr < FLEXCAN_MB_OFFSET) {
        return false;
    }
    if (addr >= FLEXCAN_MB_OFFSET + (FLEXCAN_MB_COUNT * FLEXCAN_MB_STRIDE)) {
        return false;
    }
    if ((addr - FLEXCAN_MB_OFFSET) % FLEXCAN_MB_STRIDE) {
        return false;
    }

    *mb_idx = (addr - FLEXCAN_MB_OFFSET) / FLEXCAN_MB_STRIDE;
    return true;
}

static inline uint32_t flexcan_cs_code(uint32_t cs)
{
    return (cs & FLEXCAN_CS_CODE_MASK) >> FLEXCAN_CS_CODE_SHIFT;
}

static inline uint8_t flexcan_word_swapped_index(uint8_t index)
{
    return (index & (uint8_t)~3U) + (3U - (index & 3U));
}

static void s32k3x8_flexcan_update_irq(S32K3X8FlexCANState *s)
{
    uint32_t pending = s->regs[flexcan_reg_index(FLEXCAN_IFLAG1_OFFSET)] &
                       s->regs[flexcan_reg_index(FLEXCAN_IMASK1_OFFSET)];

    qemu_set_irq(s->irq, pending != 0U);
}

static void s32k3x8_flexcan_update_mcr_state(S32K3X8FlexCANState *s)
{
    uint32_t mcr = s->regs[flexcan_reg_index(FLEXCAN_MCR_OFFSET)];
    bool mdis = (mcr & FLEXCAN_MCR_MDIS_MASK) != 0U;
    bool freeze_req = (mcr & FLEXCAN_MCR_FRZ_MASK) &&
                      (mcr & FLEXCAN_MCR_HALT_MASK);

    mcr &= ~(FLEXCAN_MCR_LPMACK_MASK |
             FLEXCAN_MCR_FRZACK_MASK |
             FLEXCAN_MCR_NOTRDY_MASK |
             FLEXCAN_MCR_SOFTRST_MASK);

    if (mdis) {
        mcr |= FLEXCAN_MCR_LPMACK_MASK |
               FLEXCAN_MCR_FRZACK_MASK |
               FLEXCAN_MCR_NOTRDY_MASK;
    } else if (freeze_req) {
        mcr |= FLEXCAN_MCR_FRZACK_MASK |
               FLEXCAN_MCR_NOTRDY_MASK;
    }

    s->regs[flexcan_reg_index(FLEXCAN_MCR_OFFSET)] = mcr;
}

static void s32k3x8_flexcan_reset_registers(S32K3X8FlexCANState *s)
{
    memset(s->regs, 0, sizeof(s->regs));
    s->timestamp = 0;
    s->locked_rx_mb = -1;

    /* Start disabled with 32 message buffers selected. */
    s->regs[flexcan_reg_index(FLEXCAN_MCR_OFFSET)] = FLEXCAN_MCR_MDIS_MASK |
                                                     31U;
    s->regs[flexcan_reg_index(FLEXCAN_RXMGMASK_OFFSET)] = 0xffffffffU;
    s->regs[flexcan_reg_index(FLEXCAN_RX14MASK_OFFSET)] = 0xffffffffU;
    s->regs[flexcan_reg_index(FLEXCAN_RX15MASK_OFFSET)] = 0xffffffffU;

    for (unsigned i = 0; i < 96; i++) {
        s->regs[flexcan_reg_index(FLEXCAN_RXIMR_OFFSET) + i] = 0xffffffffU;
    }

    s32k3x8_flexcan_update_mcr_state(s);
    s32k3x8_flexcan_update_irq(s);
}

static inline bool s32k3x8_flexcan_is_running(const S32K3X8FlexCANState *s)
{
    uint32_t mcr = s->regs[flexcan_reg_index(FLEXCAN_MCR_OFFSET)];

    return !(mcr & FLEXCAN_MCR_MDIS_MASK) && !(mcr & FLEXCAN_MCR_FRZACK_MASK);
}

static uint32_t s32k3x8_flexcan_mb_mask(const S32K3X8FlexCANState *s,
                                        unsigned mb_idx)
{
    uint32_t mcr = s->regs[flexcan_reg_index(FLEXCAN_MCR_OFFSET)];

    if (mcr & FLEXCAN_MCR_IRMQ_MASK) {
        return s->regs[flexcan_reg_index(FLEXCAN_RXIMR_OFFSET) + mb_idx];
    }
    if (mb_idx == 14) {
        return s->regs[flexcan_reg_index(FLEXCAN_RX14MASK_OFFSET)];
    }
    if (mb_idx == 15) {
        return s->regs[flexcan_reg_index(FLEXCAN_RX15MASK_OFFSET)];
    }

    return s->regs[flexcan_reg_index(FLEXCAN_RXMGMASK_OFFSET)];
}

static bool s32k3x8_flexcan_mb_matches_frame(const S32K3X8FlexCANState *s,
                                             unsigned mb_idx,
                                             const qemu_can_frame *frame)
{
    const uint32_t *mb = &s->regs[flexcan_reg_index(FLEXCAN_MB_OFFSET +
                                                    (mb_idx *
                                                     FLEXCAN_MB_STRIDE))];
    uint32_t cs = mb[0];
    uint32_t id = mb[1];
    uint32_t mask;
    bool mb_eff;
    bool frame_eff;

    if (flexcan_cs_code(cs) != FLEXCAN_RX_EMPTY) {
        return false;
    }

    mb_eff = (cs & FLEXCAN_CS_IDE_MASK) != 0U;
    frame_eff = (frame->can_id & QEMU_CAN_EFF_FLAG) != 0U;
    if (mb_eff != frame_eff) {
        return false;
    }

    mask = s32k3x8_flexcan_mb_mask(s, mb_idx);
    if (mb_eff) {
        uint32_t mb_id = id & QEMU_CAN_EFF_MASK;
        uint32_t frame_id = frame->can_id & QEMU_CAN_EFF_MASK;
        uint32_t cmp_mask = mask & QEMU_CAN_EFF_MASK;

        return (mb_id & cmp_mask) == (frame_id & cmp_mask);
    } else {
        uint32_t mb_id = (id >> FLEXCAN_STD_ID_SHIFT) & QEMU_CAN_SFF_MASK;
        uint32_t frame_id = frame->can_id & QEMU_CAN_SFF_MASK;
        uint32_t cmp_mask =
            (mask >> FLEXCAN_STD_ID_SHIFT) & QEMU_CAN_SFF_MASK;

        return (mb_id & cmp_mask) == (frame_id & cmp_mask);
    }
}

static void s32k3x8_flexcan_store_rx_frame(S32K3X8FlexCANState *s,
                                           unsigned mb_idx,
                                           const qemu_can_frame *frame)
{
    uint32_t *mb = flexcan_mb_addr(s, mb_idx);
    uint32_t frame_id = frame->can_id;
    bool eff = (frame_id & QEMU_CAN_EFF_FLAG) != 0U;
    bool rtr = (frame_id & QEMU_CAN_RTR_FLAG) != 0U;
    uint8_t len = frame->can_dlc;
    uint8_t *mb_bytes = (uint8_t *)&mb[2];
    uint32_t cs = 0;

    if (len > 8U) {
        len = 8U;
    }

    memset(&mb[2], 0, 2 * sizeof(uint32_t));
    for (uint8_t i = 0; i < len; i++) {
        mb_bytes[flexcan_word_swapped_index(i)] = frame->data[i];
    }

    if (eff) {
        mb[1] = frame_id & QEMU_CAN_EFF_MASK;
        cs |= FLEXCAN_CS_IDE_MASK;
    } else {
        mb[1] = (frame_id & QEMU_CAN_SFF_MASK) << FLEXCAN_STD_ID_SHIFT;
    }

    if (rtr) {
        cs |= FLEXCAN_CS_RTR_MASK;
    }

    cs |= ((uint32_t)can_len2dlc(len) << FLEXCAN_CS_DLC_SHIFT) &
          FLEXCAN_CS_DLC_MASK;
    cs |= ((uint32_t)FLEXCAN_RX_FULL << FLEXCAN_CS_CODE_SHIFT) &
          FLEXCAN_CS_CODE_MASK;
    cs |= (uint32_t)s->timestamp++ & FLEXCAN_CS_TIMESTAMP_MASK;
    mb[0] = cs;

    s->regs[flexcan_reg_index(FLEXCAN_IFLAG1_OFFSET)] |= (1U << mb_idx);
    s32k3x8_flexcan_update_irq(s);
}

static void s32k3x8_flexcan_tx_complete(S32K3X8FlexCANState *s,
                                        unsigned mb_idx,
                                        bool keep_abort_code)
{
    uint32_t *mb = flexcan_mb_addr(s, mb_idx);
    uint32_t cs = mb[0];
    uint32_t code = keep_abort_code ? FLEXCAN_TX_ABORT : FLEXCAN_TX_INACTIVE;

    cs &= ~(FLEXCAN_CS_CODE_MASK | FLEXCAN_CS_TIMESTAMP_MASK);
    cs |= (code << FLEXCAN_CS_CODE_SHIFT) & FLEXCAN_CS_CODE_MASK;
    cs |= (uint32_t)s->timestamp++ & FLEXCAN_CS_TIMESTAMP_MASK;
    mb[0] = cs;

    s->regs[flexcan_reg_index(FLEXCAN_IFLAG1_OFFSET)] |= (1U << mb_idx);
    s32k3x8_flexcan_update_irq(s);
}

static void s32k3x8_flexcan_try_tx_mb(S32K3X8FlexCANState *s, unsigned mb_idx)
{
    uint32_t *mb = flexcan_mb_addr(s, mb_idx);
    uint32_t cs = mb[0];
    uint32_t code = flexcan_cs_code(cs);
    qemu_can_frame frame = {0};
    uint8_t *mb_bytes = (uint8_t *)&mb[2];
    uint8_t len;

    if (!s32k3x8_flexcan_is_running(s)) {
        return;
    }

    if (code == FLEXCAN_TX_ABORT) {
        s32k3x8_flexcan_tx_complete(s, mb_idx, true);
        return;
    }

    if (code != FLEXCAN_TX_DATA_CODE) {
        return;
    }

    if (cs & FLEXCAN_CS_IDE_MASK) {
        frame.can_id = mb[1] & QEMU_CAN_EFF_MASK;
        frame.can_id |= QEMU_CAN_EFF_FLAG;
    } else {
        frame.can_id = (mb[1] >> FLEXCAN_STD_ID_SHIFT) & QEMU_CAN_SFF_MASK;
    }

    if (cs & FLEXCAN_CS_RTR_MASK) {
        frame.can_id |= QEMU_CAN_RTR_FLAG;
    }

    len = can_dlc2len((cs & FLEXCAN_CS_DLC_MASK) >> FLEXCAN_CS_DLC_SHIFT);
    if (len > 8U) {
        len = 8U;
    }
    frame.can_dlc = len;

    for (uint8_t i = 0; i < len; i++) {
        frame.data[i] = mb_bytes[flexcan_word_swapped_index(i)];
    }

    if (s->bus_client.bus) {
        (void)can_bus_client_send(&s->bus_client, &frame, 1);
    }

    s32k3x8_flexcan_tx_complete(s, mb_idx, false);
}

static uint64_t s32k3x8_flexcan_read(void *opaque, hwaddr addr, unsigned size)
{
    S32K3X8FlexCANState *s = S32K3X8_FLEXCAN(opaque);
    hwaddr word_addr = addr & ~3ULL;
    unsigned shift = (addr & 3U) * 8U;
    uint32_t idx;
    uint32_t value;
    unsigned mb_idx;

    if (size != 1 && size != 2 && size != 4) {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3x8-flexcan: invalid read size %u @0x%" HWADDR_PRIx
                      "\n", size, addr);
        return 0;
    }
    if (addr + size > S32K3X8_FLEXCAN_MMIO_SIZE ||
        ((addr & 3U) + size) > 4U) {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3x8-flexcan: out-of-range read @0x%" HWADDR_PRIx
                      "\n", addr);
        return 0;
    }

    if (word_addr == FLEXCAN_TIMER_OFFSET) {
        if (s->locked_rx_mb >= 0) {
            uint32_t *mb = flexcan_mb_addr(s, s->locked_rx_mb);

            if (flexcan_cs_code(mb[0]) == FLEXCAN_RX_FULL) {
                mb[0] &= ~FLEXCAN_CS_CODE_MASK;
                mb[0] |= (FLEXCAN_RX_EMPTY << FLEXCAN_CS_CODE_SHIFT) &
                         FLEXCAN_CS_CODE_MASK;
            }
            s->locked_rx_mb = -1;
        }
        s->regs[flexcan_reg_index(FLEXCAN_TIMER_OFFSET)] =
            (uint32_t)s->timestamp++;
    }

    idx = flexcan_reg_index(word_addr);
    value = s->regs[idx] >> shift;
    if (size == 4 && flexcan_is_mb_cs_addr(word_addr, &mb_idx) &&
        flexcan_cs_code(value) == FLEXCAN_RX_FULL) {
        s->locked_rx_mb = mb_idx;
    }
    if (size == 1) {
        return value & 0xffU;
    }
    if (size == 2) {
        return value & 0xffffU;
    }
    return value;
}

static void s32k3x8_flexcan_write(void *opaque,
                                  hwaddr addr,
                                  uint64_t value,
                                  unsigned size)
{
    S32K3X8FlexCANState *s = S32K3X8_FLEXCAN(opaque);
    hwaddr word_addr = addr & ~3ULL;
    unsigned shift = (addr & 3U) * 8U;
    uint32_t mask;
    uint32_t v;
    uint32_t idx;
    unsigned mb_idx;

    if (size != 1 && size != 2 && size != 4) {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3x8-flexcan: invalid write size %u @0x%" HWADDR_PRIx
                      "\n", size, addr);
        return;
    }
    if (addr + size > S32K3X8_FLEXCAN_MMIO_SIZE ||
        ((addr & 3U) + size) > 4U) {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3x8-flexcan: out-of-range write @0x%" HWADDR_PRIx
                      "\n", addr);
        return;
    }

    idx = flexcan_reg_index(word_addr);
    if (size == 4) {
        mask = 0xffffffffU;
    } else {
        mask = ((1U << (size * 8U)) - 1U) << shift;
    }
    v = (s->regs[idx] & ~mask) | (((uint32_t)value << shift) & mask);

    switch (word_addr) {
    case FLEXCAN_MCR_OFFSET:
        s->regs[idx] &= FLEXCAN_MCR_LPMACK_MASK |
                        FLEXCAN_MCR_FRZACK_MASK |
                        FLEXCAN_MCR_NOTRDY_MASK;
        s->regs[idx] |= v & ~(FLEXCAN_MCR_LPMACK_MASK |
                              FLEXCAN_MCR_FRZACK_MASK |
                              FLEXCAN_MCR_NOTRDY_MASK);
        if (v & FLEXCAN_MCR_SOFTRST_MASK) {
            s32k3x8_flexcan_reset_registers(s);
        } else {
            s32k3x8_flexcan_update_mcr_state(s);
        }
        break;
    case FLEXCAN_IMASK1_OFFSET:
    case FLEXCAN_IMASK2_OFFSET:
    case FLEXCAN_IMASK3_OFFSET:
        s->regs[idx] = v;
        s32k3x8_flexcan_update_irq(s);
        break;
    case FLEXCAN_IFLAG1_OFFSET:
    case FLEXCAN_IFLAG2_OFFSET:
    case FLEXCAN_IFLAG3_OFFSET:
        /* W1C. */
        s->regs[idx] &= ~v;
        s32k3x8_flexcan_update_irq(s);
        break;
    case FLEXCAN_ESR1_OFFSET:
        s->regs[idx] &= ~(v & FLEXCAN_ESR1_W1C_MASK);
        break;
    default:
        s->regs[idx] = v;
        break;
    }

    if (flexcan_is_mb_cs_addr(word_addr, &mb_idx)) {
        s32k3x8_flexcan_try_tx_mb(s, mb_idx);
    }
}

static const MemoryRegionOps s32k3x8_flexcan_ops = {
    .read = s32k3x8_flexcan_read,
    .write = s32k3x8_flexcan_write,
    .endianness = DEVICE_LITTLE_ENDIAN,
    .valid = {
        .min_access_size = 1,
        .max_access_size = 4,
        .unaligned = false,
    },
    .impl = {
        .min_access_size = 1,
        .max_access_size = 4,
    },
};

static bool s32k3x8_flexcan_can_receive(CanBusClientState *client)
{
    S32K3X8FlexCANState *s = container_of(client, S32K3X8FlexCANState,
                                          bus_client);

    return s32k3x8_flexcan_is_running(s);
}

static ssize_t s32k3x8_flexcan_receive(CanBusClientState *client,
                                       const qemu_can_frame *frames,
                                       size_t frames_cnt)
{
    S32K3X8FlexCANState *s = container_of(client, S32K3X8FlexCANState,
                                          bus_client);
    ssize_t accepted = 0;

    for (size_t fi = 0; fi < frames_cnt; fi++) {
        const qemu_can_frame *frame = &frames[fi];
        bool stored = false;

        for (unsigned mb = 0; mb < FLEXCAN_MB_COUNT; mb++) {
            if (s32k3x8_flexcan_mb_matches_frame(s, mb, frame)) {
                s32k3x8_flexcan_store_rx_frame(s, mb, frame);
                stored = true;
                accepted++;
                break;
            }
        }

        if (!stored) {
            /* Frame dropped when no RX_EMPTY MB matches. */
        }
    }

    return accepted;
}

static CanBusClientInfo s32k3x8_flexcan_bus_client_info = {
    .can_receive = s32k3x8_flexcan_can_receive,
    .receive = s32k3x8_flexcan_receive,
};

static void s32k3x8_flexcan_reset(DeviceState *dev)
{
    S32K3X8FlexCANState *s = S32K3X8_FLEXCAN(dev);

    s32k3x8_flexcan_reset_registers(s);
}

static void s32k3x8_flexcan_realize(DeviceState *dev, Error **errp)
{
    S32K3X8FlexCANState *s = S32K3X8_FLEXCAN(dev);

    s32k3x8_flexcan_reset(dev);

    if (s->canbus) {
        s->bus_client.info = &s32k3x8_flexcan_bus_client_info;
        if (can_bus_insert_client(s->canbus, &s->bus_client) < 0) {
            error_setg(errp, "s32k3x8-flexcan%u: failed to connect canbus",
                       s->instance_id);
            return;
        }
    }
}

static void s32k3x8_flexcan_unrealize(DeviceState *dev)
{
    S32K3X8FlexCANState *s = S32K3X8_FLEXCAN(dev);

    if (s->bus_client.bus) {
        can_bus_remove_client(&s->bus_client);
    }
}

static void s32k3x8_flexcan_init(Object *obj)
{
    S32K3X8FlexCANState *s = S32K3X8_FLEXCAN(obj);
    SysBusDevice *sbd = SYS_BUS_DEVICE(obj);

    memory_region_init_io(&s->mmio, obj, &s32k3x8_flexcan_ops, s,
                          TYPE_S32K3X8_FLEXCAN, S32K3X8_FLEXCAN_MMIO_SIZE);
    sysbus_init_mmio(sbd, &s->mmio);
    sysbus_init_irq(sbd, &s->irq);
}

static const Property s32k3x8_flexcan_properties[] = {
    DEFINE_PROP_UINT32("can-instance", S32K3X8FlexCANState, instance_id, 0),
    DEFINE_PROP_LINK("canbus", S32K3X8FlexCANState, canbus, TYPE_CAN_BUS,
                     CanBusState *),
};

static void s32k3x8_flexcan_class_init(ObjectClass *klass, const void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->realize = s32k3x8_flexcan_realize;
    dc->unrealize = s32k3x8_flexcan_unrealize;
    device_class_set_legacy_reset(dc, s32k3x8_flexcan_reset);
    device_class_set_props(dc, s32k3x8_flexcan_properties);
}

static const TypeInfo s32k3x8_flexcan_info = {
    .name = TYPE_S32K3X8_FLEXCAN,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(S32K3X8FlexCANState),
    .instance_init = s32k3x8_flexcan_init,
    .class_init = s32k3x8_flexcan_class_init,
};

static void s32k3x8_flexcan_register_types(void)
{
    type_register_static(&s32k3x8_flexcan_info);
}

type_init(s32k3x8_flexcan_register_types)
