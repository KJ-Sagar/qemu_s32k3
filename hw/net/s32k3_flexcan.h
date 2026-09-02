#ifndef HW_NET_S32K3X8_FLEXCAN_H
#define HW_NET_S32K3X8_FLEXCAN_H

#include "qemu/osdep.h"
#include "hw/core/sysbus.h"
#include "net/can_emu.h"

#define TYPE_S32K3X8_FLEXCAN "s32k3x8-flexcan"
OBJECT_DECLARE_SIMPLE_TYPE(S32K3X8FlexCANState, S32K3X8_FLEXCAN)

#define S32K3X8_FLEXCAN_MMIO_SIZE 0x4000U

struct S32K3X8FlexCANState {
    SysBusDevice parent_obj;

    MemoryRegion mmio;
    qemu_irq irq;

    CanBusClientState bus_client;
    CanBusState *canbus;

    uint32_t instance_id;
    uint16_t timestamp;
    int locked_rx_mb;
    uint32_t regs[S32K3X8_FLEXCAN_MMIO_SIZE / sizeof(uint32_t)];
};

#endif /* HW_NET_S32K3X8_FLEXCAN_H */
