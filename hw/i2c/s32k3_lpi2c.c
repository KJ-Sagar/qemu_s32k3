/*
 * NXP S32K3xx Low Power Inter-Integrated Circuit (LPI2C) Emulation
 *
 * See s32k3_lpi2c.h for the manual cross-reference (S32K3xx Reference
 * Manual Rev. 11, Chapter 71).
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#include "qemu/osdep.h"
#include "hw/core/sysbus.h"
#include "hw/core/qdev-properties.h"
#include "hw/core/irq.h"
#include "hw/i2c/i2c.h"
#include "qapi/error.h"
#include "qemu/log.h"
#include "qemu/module.h"
#include "qom/object.h"
#include "s32k3_lpi2c.h"

static void s32k3_lpi2c_update_irq(S32K3LPI2CState *s)
{
    uint32_t txwater = s->mfcr & S32K3_LPI2C_MFCR_TXWATER_MASK;
    uint32_t rxwater = (s->mfcr & S32K3_LPI2C_MFCR_RXWATER_MASK) >>
                       S32K3_LPI2C_MFCR_RXWATER_SHIFT;
    bool tdf = s->tx_count <= txwater;
    bool rdf = s->rx_count > rxwater;
    bool level = false;

    if ((s->mier & S32K3_LPI2C_MIER_TDIE) && tdf) {
        level = true;
    }
    if ((s->mier & S32K3_LPI2C_MIER_RDIE) && rdf) {
        level = true;
    }
    if ((s->mier & S32K3_LPI2C_MIER_EPIE) && (s->msr & S32K3_LPI2C_MSR_EPF)) {
        level = true;
    }
    if ((s->mier & S32K3_LPI2C_MIER_SDIE) && (s->msr & S32K3_LPI2C_MSR_SDF)) {
        level = true;
    }
    if ((s->mier & S32K3_LPI2C_MIER_NDIE) && (s->msr & S32K3_LPI2C_MSR_NDF)) {
        level = true;
    }
    if ((s->mier & S32K3_LPI2C_MIER_ALIE) && (s->msr & S32K3_LPI2C_MSR_ALF)) {
        level = true;
    }
    if ((s->mier & S32K3_LPI2C_MIER_FEIE) && (s->msr & S32K3_LPI2C_MSR_FEF)) {
        level = true;
    }
    if ((s->mier & S32K3_LPI2C_MIER_PLTIE) && (s->msr & S32K3_LPI2C_MSR_PLTF)) {
        level = true;
    }
    if ((s->mier & S32K3_LPI2C_MIER_DMIE) && (s->msr & S32K3_LPI2C_MSR_DMF)) {
        level = true;
    }

    qemu_set_irq(s->irq, level);
}

static uint32_t s32k3_lpi2c_compute_msr(S32K3LPI2CState *s)
{
    uint32_t txwater = s->mfcr & S32K3_LPI2C_MFCR_TXWATER_MASK;
    uint32_t rxwater = (s->mfcr & S32K3_LPI2C_MFCR_RXWATER_MASK) >>
                       S32K3_LPI2C_MFCR_RXWATER_SHIFT;
    uint32_t msr = s->msr & S32K3_LPI2C_MSR_W1C_MASK;

    if (s->tx_count <= txwater) {
        msr |= S32K3_LPI2C_MSR_TDF;
    }
    if (s->rx_count > rxwater) {
        msr |= S32K3_LPI2C_MSR_RDF;
    }
    /* MBF/BBF: transfers complete synchronously in this model, so the bus
     * is never observed mid-transfer. */
    return msr;
}

static void s32k3_lpi2c_reset_tx_fifo(S32K3LPI2CState *s)
{
    s->tx_count = 0;
    memset(s->tx_fifo, 0, sizeof(s->tx_fifo));
}

static void s32k3_lpi2c_reset_rx_fifo(S32K3LPI2CState *s)
{
    s->rx_count = 0;
    memset(s->rx_fifo, 0, sizeof(s->rx_fifo));
}

static void s32k3_lpi2c_do_reset(S32K3LPI2CState *s, bool keep_mcr)
{
    uint32_t mcr = s->mcr;

    s->verid = 0x01020003;
    s->param = 0x00000202;
    s->mcr = keep_mcr ? mcr : 0;
    s->msr = S32K3_LPI2C_MSR_RESET;
    s->mier = 0;
    s->mder = 0;
    s->mcfgr0 = 0;
    s->mcfgr1 = 0;
    s->mcfgr2 = 0;
    s->mcfgr3 = 0;
    s->mdmr = 0;
    s->mccr0 = 0;
    s->mccr1 = 0;
    s->mfcr = 0;
    s32k3_lpi2c_reset_tx_fifo(s);
    s32k3_lpi2c_reset_rx_fifo(s);
    if (s->started) {
        i2c_end_transfer(s->bus);
    }
    s->started = false;
}

static void s32k3_lpi2c_reset(DeviceState *dev)
{
    S32K3LPI2CState *s = S32K3_LPI2C(dev);

    s32k3_lpi2c_do_reset(s, false);
    s32k3_lpi2c_update_irq(s);
}

/* Execute one MTDR command word against the real QEMU I2CBus. Runs
 * synchronously to completion, same rationale as s32k3_lpspi_service(). */
static void s32k3_lpi2c_exec_command(S32K3LPI2CState *s, uint32_t word)
{
    uint32_t cmd = (word & S32K3_LPI2C_MTDR_CMD_MASK) >>
                   S32K3_LPI2C_MTDR_CMD_SHIFT;
    uint8_t data = word & S32K3_LPI2C_MTDR_DATA_MASK;

    switch (cmd) {
    case S32K3_LPI2C_CMD_START_ACK:
    case S32K3_LPI2C_CMD_START_NACK:
    case S32K3_LPI2C_CMD_START_HS_ACK:
    case S32K3_LPI2C_CMD_START_HS_NACK: {
        bool is_recv = data & 1;
        uint8_t addr7 = data >> 1;
        bool nack_expected = (cmd == S32K3_LPI2C_CMD_START_NACK) ||
                              (cmd == S32K3_LPI2C_CMD_START_HS_NACK);
        int ret;

        if (s->started) {
            /* Repeated Start: end the current transfer first. */
            i2c_end_transfer(s->bus);
            s->msr |= S32K3_LPI2C_MSR_EPF;
        }
        ret = i2c_start_transfer(s->bus, addr7, is_recv);
        if (ret != 0) {
            /* No device ACKed the address. */
            if (!nack_expected) {
                s->msr |= S32K3_LPI2C_MSR_NDF;
            }
            s->started = false;
        } else {
            s->started = true;
        }
        break;
    }
    case S32K3_LPI2C_CMD_TRANSMIT: {
        int ret;

        if (!s->started) {
            s->msr |= S32K3_LPI2C_MSR_FEF;
            break;
        }
        ret = i2c_send(s->bus, data);
        if (ret != 0) {
            s->msr |= S32K3_LPI2C_MSR_NDF;
            i2c_end_transfer(s->bus);
            s->started = false;
        }
        break;
    }
    case S32K3_LPI2C_CMD_RECEIVE:
    case S32K3_LPI2C_CMD_RECEIVE_DISCARD: {
        uint32_t count = data + 1;
        uint32_t i;

        if (!s->started) {
            s->msr |= S32K3_LPI2C_MSR_FEF;
            break;
        }
        for (i = 0; i < count; i++) {
            uint8_t rx = i2c_recv(s->bus);

            if (cmd == S32K3_LPI2C_CMD_RECEIVE) {
                if (s->rx_count >= S32K3_LPI2C_FIFO_DEPTH) {
                    qemu_log_mask(LOG_GUEST_ERROR,
                                  "s32k3_lpi2c[%u]: RX FIFO overflow, "
                                  "byte dropped\n", s->instance_id);
                    continue;
                }
                s->rx_fifo[s->rx_count++] = rx;

                /* Simple data-match: compare against MDMR[MATCH0] (low
                 * byte) when data matching is enabled via MCFGR1. Only
                 * the plain match mode is modeled (see LPSPI DMF for the
                 * same simplification rationale). */
                if ((s->mcfgr1 & 0xF0000) && rx == (s->mdmr & 0xFF)) {
                    s->msr |= S32K3_LPI2C_MSR_DMF;
                }
            }
        }
        break;
    }
    case S32K3_LPI2C_CMD_STOP:
        if (s->started) {
            i2c_end_transfer(s->bus);
            s->started = false;
        }
        s->msr |= S32K3_LPI2C_MSR_SDF | S32K3_LPI2C_MSR_EPF;
        break;
    default:
        qemu_log_mask(LOG_UNIMP,
                      "s32k3_lpi2c[%u]: unhandled MTDR command %u\n",
                      s->instance_id, cmd);
        break;
    }
}

static void s32k3_lpi2c_service(S32K3LPI2CState *s)
{
    if (!(s->mcr & S32K3_LPI2C_MCR_MEN)) {
        return;
    }

    while (s->tx_count > 0) {
        uint32_t word = s->tx_fifo[0];
        uint32_t i;

        for (i = 1; i < s->tx_count; i++) {
            s->tx_fifo[i - 1] = s->tx_fifo[i];
        }
        s->tx_count--;

        s32k3_lpi2c_exec_command(s, word);
    }

    s32k3_lpi2c_update_irq(s);
}

static uint64_t s32k3_lpi2c_read(void *opaque, hwaddr addr, unsigned size)
{
    S32K3LPI2CState *s = opaque;

    switch (addr) {
    case S32K3_LPI2C_VERID:
        return s->verid;
    case S32K3_LPI2C_PARAM:
        return s->param;
    case S32K3_LPI2C_MCR:
        return s->mcr;
    case S32K3_LPI2C_MSR:
        return s32k3_lpi2c_compute_msr(s);
    case S32K3_LPI2C_MIER:
        return s->mier;
    case S32K3_LPI2C_MDER:
        return s->mder;
    case S32K3_LPI2C_MCFGR0:
        return s->mcfgr0;
    case S32K3_LPI2C_MCFGR1:
        return s->mcfgr1;
    case S32K3_LPI2C_MCFGR2:
        return s->mcfgr2;
    case S32K3_LPI2C_MCFGR3:
        return s->mcfgr3;
    case S32K3_LPI2C_MDMR:
        return s->mdmr;
    case S32K3_LPI2C_MCCR0:
        return s->mccr0;
    case S32K3_LPI2C_MCCR1:
        return s->mccr1;
    case S32K3_LPI2C_MFCR:
        return s->mfcr;
    case S32K3_LPI2C_MFSR:
        return (s->rx_count << S32K3_LPI2C_MFSR_RXCOUNT_SHIFT) |
               (s->tx_count << S32K3_LPI2C_MFSR_TXCOUNT_SHIFT);
    case S32K3_LPI2C_MRDR:
        if (s->rx_count > 0) {
            uint32_t val = s->rx_fifo[0];
            uint32_t i;

            for (i = 1; i < s->rx_count; i++) {
                s->rx_fifo[i - 1] = s->rx_fifo[i];
            }
            s->rx_count--;
            s32k3_lpi2c_update_irq(s);
            return val & S32K3_LPI2C_MRDR_DATA_MASK;
        }
        return S32K3_LPI2C_MRDR_RXEMPTY;
    default:
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3_lpi2c[%u]: read from invalid offset 0x%"
                      HWADDR_PRIx "\n", s->instance_id, addr);
        return 0;
    }
}

static void s32k3_lpi2c_write(void *opaque, hwaddr addr, uint64_t val64,
                               unsigned size)
{
    S32K3LPI2CState *s = opaque;
    uint32_t val = val64;

    switch (addr) {
    case S32K3_LPI2C_MCR: {
        bool men_rising = !(s->mcr & S32K3_LPI2C_MCR_MEN) &&
                           (val & S32K3_LPI2C_MCR_MEN);
        bool rst_rising = !(s->mcr & S32K3_LPI2C_MCR_RST) &&
                           (val & S32K3_LPI2C_MCR_RST);

        if (val & S32K3_LPI2C_MCR_RTF) {
            s32k3_lpi2c_reset_tx_fifo(s);
        }
        if (val & S32K3_LPI2C_MCR_RRF) {
            s32k3_lpi2c_reset_rx_fifo(s);
        }
        s->mcr = val & (S32K3_LPI2C_MCR_MEN | S32K3_LPI2C_MCR_RST |
                        S32K3_LPI2C_MCR_DOZEN | S32K3_LPI2C_MCR_DBGEN);

        if (rst_rising) {
            s32k3_lpi2c_do_reset(s, true);
        }
        if (men_rising) {
            s32k3_lpi2c_service(s);
        }
        break;
    }
    case S32K3_LPI2C_MSR:
        s->msr &= ~(val & S32K3_LPI2C_MSR_W1C_MASK);
        s32k3_lpi2c_update_irq(s);
        break;
    case S32K3_LPI2C_MIER:
        s->mier = val;
        s32k3_lpi2c_update_irq(s);
        break;
    case S32K3_LPI2C_MDER:
        s->mder = val;
        if (val) {
            qemu_log_mask(LOG_UNIMP,
                          "s32k3_lpi2c[%u]: DMA requests are not modeled "
                          "(no eDMA controller yet)\n", s->instance_id);
        }
        break;
    case S32K3_LPI2C_MCFGR0:
        s->mcfgr0 = val;
        break;
    case S32K3_LPI2C_MCFGR1:
        s->mcfgr1 = val;
        break;
    case S32K3_LPI2C_MCFGR2:
        s->mcfgr2 = val;
        break;
    case S32K3_LPI2C_MCFGR3:
        s->mcfgr3 = val;
        break;
    case S32K3_LPI2C_MDMR:
        s->mdmr = val;
        break;
    case S32K3_LPI2C_MCCR0:
        s->mccr0 = val;
        break;
    case S32K3_LPI2C_MCCR1:
        s->mccr1 = val;
        break;
    case S32K3_LPI2C_MFCR:
        s->mfcr = val;
        s32k3_lpi2c_update_irq(s);
        break;
    case S32K3_LPI2C_MTDR:
        if (s->tx_count >= S32K3_LPI2C_FIFO_DEPTH) {
            qemu_log_mask(LOG_GUEST_ERROR,
                          "s32k3_lpi2c[%u]: MTDR write with TX FIFO full, "
                          "command dropped\n", s->instance_id);
            break;
        }
        s->tx_fifo[s->tx_count++] = val;
        s32k3_lpi2c_service(s);
        break;
    default:
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3_lpi2c[%u]: write to invalid offset 0x%"
                      HWADDR_PRIx " (value 0x%" PRIx32 ")\n",
                      s->instance_id, addr, val);
        break;
    }
}

static const MemoryRegionOps s32k3_lpi2c_ops = {
    .read = s32k3_lpi2c_read,
    .write = s32k3_lpi2c_write,
    .endianness = DEVICE_LITTLE_ENDIAN,
    .impl = {
        .min_access_size = 1,
        .max_access_size = 4,
    },
    .valid = {
        .min_access_size = 1,
        .max_access_size = 4,
    },
};

static void s32k3_lpi2c_instance_init(Object *obj)
{
    SysBusDevice *sbd = SYS_BUS_DEVICE(obj);
    S32K3LPI2CState *s = S32K3_LPI2C(obj);

    memory_region_init_io(&s->iomem, obj, &s32k3_lpi2c_ops, s,
                          TYPE_S32K3_LPI2C, S32K3_LPI2C_REGS_MEM_SIZE);
    sysbus_init_mmio(sbd, &s->iomem);
    sysbus_init_irq(sbd, &s->irq);

    s->bus = i2c_init_bus(DEVICE(obj), "i2c");
}

static void s32k3_lpi2c_realize(DeviceState *dev, Error **errp)
{
    s32k3_lpi2c_reset(dev);
}

static const Property s32k3_lpi2c_properties[] = {
    DEFINE_PROP_UINT32("lpi2c-id", S32K3LPI2CState, instance_id, 0),
};

static void s32k3_lpi2c_class_init(ObjectClass *klass, const void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->realize = s32k3_lpi2c_realize;
    device_class_set_props(dc, s32k3_lpi2c_properties);
}

static const TypeInfo s32k3_lpi2c_info = {
    .name = TYPE_S32K3_LPI2C,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(S32K3LPI2CState),
    .instance_init = s32k3_lpi2c_instance_init,
    .class_init = s32k3_lpi2c_class_init,
};

static void s32k3_lpi2c_register_types(void)
{
    type_register_static(&s32k3_lpi2c_info);
}

type_init(s32k3_lpi2c_register_types)
