/*
 * S32K3 FlexIO UART subset used by the LpuartFlexio example.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#include "qemu/osdep.h"
#include "hw/char/s32k3_flexio_uart.h"
#include "hw/core/irq.h"
#include "qemu/module.h"

#define FLEXIO_CTRL       0x008
#define FLEXIO_SHIFTSTAT  0x010
#define FLEXIO_SHIFTERR   0x014
#define FLEXIO_TIMSTAT    0x018
#define FLEXIO_SHIFTSIEN  0x020
#define FLEXIO_SHIFTEIEN  0x024
#define FLEXIO_TIMIEN     0x028
#define FLEXIO_SHIFTBUF   0x200

#define FLEXIO_TX_CHANNEL 0
#define FLEXIO_RX_CHANNEL 1

#define R(s, offset) ((s)->regs[(offset) / sizeof(uint32_t)])

static void s32k3_flexio_uart_update_irq(S32K3FlexIOUARTState *s)
{
    bool active = (R(s, FLEXIO_SHIFTSTAT) & R(s, FLEXIO_SHIFTSIEN)) ||
                  (R(s, FLEXIO_SHIFTERR) & R(s, FLEXIO_SHIFTEIEN)) ||
                  (R(s, FLEXIO_TIMSTAT) & R(s, FLEXIO_TIMIEN));

    qemu_set_irq(s->irq, active);
}

void s32k3_flexio_uart_receive_byte(void *opaque, uint8_t byte)
{
    S32K3FlexIOUARTState *s = opaque;

    R(s, FLEXIO_SHIFTBUF + FLEXIO_RX_CHANNEL * 4) = (uint32_t)byte << 24;
    R(s, FLEXIO_SHIFTSTAT) |= BIT(FLEXIO_RX_CHANNEL);
    s32k3_flexio_uart_update_irq(s);
}

void s32k3_flexio_uart_connect_lpuart(S32K3FlexIOUARTState *s,
                                      S32K3X8LPUARTState *lpuart)
{
    s->lpuart = lpuart;
    s32k3x8_lpuart_set_tx_sink(lpuart, s32k3_flexio_uart_receive_byte, s);
}

static uint64_t s32k3_flexio_uart_read(void *opaque, hwaddr offset,
                                       unsigned size)
{
    S32K3FlexIOUARTState *s = opaque;
    uint32_t value;

    if (offset >= S32K3_FLEXIO_UART_SIZE) {
        return 0;
    }

    value = R(s, offset);
    if (offset == FLEXIO_SHIFTBUF + FLEXIO_RX_CHANNEL * 4) {
        R(s, FLEXIO_SHIFTSTAT) &= ~BIT(FLEXIO_RX_CHANNEL);
        s32k3_flexio_uart_update_irq(s);
    }
    return value;
}

static void s32k3_flexio_uart_write(void *opaque, hwaddr offset,
                                    uint64_t value, unsigned size)
{
    S32K3FlexIOUARTState *s = opaque;
    uint32_t val = value;

    if (offset >= S32K3_FLEXIO_UART_SIZE) {
        return;
    }

    switch (offset) {
    case FLEXIO_SHIFTSTAT:
    case FLEXIO_SHIFTERR:
        R(s, offset) &= ~val;
        break;
    case FLEXIO_TIMSTAT:
        R(s, FLEXIO_TIMSTAT) &= ~val;
        if (val & R(s, FLEXIO_TIMIEN)) {
            R(s, FLEXIO_TIMSTAT) |= val & R(s, FLEXIO_TIMIEN);
        }
        break;
    case FLEXIO_SHIFTSIEN:
        R(s, offset) = val;
        if (val & BIT(FLEXIO_TX_CHANNEL)) {
            R(s, FLEXIO_SHIFTSTAT) |= BIT(FLEXIO_TX_CHANNEL);
        }
        break;
    case FLEXIO_TIMIEN:
        R(s, offset) = val;
        if (val & BIT(FLEXIO_TX_CHANNEL)) {
            R(s, FLEXIO_TIMSTAT) |= BIT(FLEXIO_TX_CHANNEL);
        }
        break;
    case FLEXIO_SHIFTBUF + FLEXIO_TX_CHANNEL * 4:
        R(s, offset) = val;
        if (val != UINT32_MAX && s->lpuart) {
            uint8_t byte = val;

            /*
             * The board example cross-connects FlexIO TX to LPUART RX.
             * Also mirror that external TX signal to the selected console.
             */
            s32k3x8_lpuart_receive_byte(s->lpuart, byte);
            s32k3x8_lpuart_write_console(s->lpuart, byte);
        }
        R(s, FLEXIO_SHIFTSTAT) |= BIT(FLEXIO_TX_CHANNEL);
        break;
    default:
        R(s, offset) = val;
        break;
    }
    s32k3_flexio_uart_update_irq(s);
}

static const MemoryRegionOps s32k3_flexio_uart_ops = {
    .read = s32k3_flexio_uart_read,
    .write = s32k3_flexio_uart_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
    .impl.min_access_size = 4,
    .impl.max_access_size = 4,
    .valid.min_access_size = 4,
    .valid.max_access_size = 4,
};

static void s32k3_flexio_uart_reset(DeviceState *dev)
{
    S32K3FlexIOUARTState *s = S32K3_FLEXIO_UART(dev);

    memset(s->regs, 0, sizeof(s->regs));
    R(s, FLEXIO_SHIFTSTAT) = BIT(FLEXIO_TX_CHANNEL);
    s32k3_flexio_uart_update_irq(s);
}

static void s32k3_flexio_uart_instance_init(Object *obj)
{
    S32K3FlexIOUARTState *s = S32K3_FLEXIO_UART(obj);
    SysBusDevice *sbd = SYS_BUS_DEVICE(obj);

    memory_region_init_io(&s->iomem, obj, &s32k3_flexio_uart_ops, s,
                          TYPE_S32K3_FLEXIO_UART, S32K3_FLEXIO_UART_SIZE);
    sysbus_init_mmio(sbd, &s->iomem);
    sysbus_init_irq(sbd, &s->irq);
}

static void s32k3_flexio_uart_class_init(ObjectClass *klass, const void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    device_class_set_legacy_reset(dc, s32k3_flexio_uart_reset);
}

static const TypeInfo s32k3_flexio_uart_info = {
    .name = TYPE_S32K3_FLEXIO_UART,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(S32K3FlexIOUARTState),
    .instance_init = s32k3_flexio_uart_instance_init,
    .class_init = s32k3_flexio_uart_class_init,
};

static void s32k3_flexio_uart_register_types(void)
{
    type_register_static(&s32k3_flexio_uart_info);
}

type_init(s32k3_flexio_uart_register_types);
