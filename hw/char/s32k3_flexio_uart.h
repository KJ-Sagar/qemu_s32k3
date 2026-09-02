#ifndef HW_CHAR_S32K3_FLEXIO_UART_H
#define HW_CHAR_S32K3_FLEXIO_UART_H

#include "hw/core/sysbus.h"
#include "hw/char/s32k3_uart.h"
#include "qom/object.h"

#define TYPE_S32K3_FLEXIO_UART "s32k3-flexio-uart"
OBJECT_DECLARE_SIMPLE_TYPE(S32K3FlexIOUARTState, S32K3_FLEXIO_UART)

#define S32K3_FLEXIO_UART_SIZE 0x600

struct S32K3FlexIOUARTState {
    SysBusDevice parent_obj;
    MemoryRegion iomem;
    qemu_irq irq;
    uint32_t regs[S32K3_FLEXIO_UART_SIZE / sizeof(uint32_t)];
    S32K3X8LPUARTState *lpuart;
};

void s32k3_flexio_uart_connect_lpuart(S32K3FlexIOUARTState *s, S32K3X8LPUARTState *lpuart);
void s32k3_flexio_uart_receive_byte(void *opaque, uint8_t byte);

#endif
