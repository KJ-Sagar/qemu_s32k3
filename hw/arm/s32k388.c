/* SPDX-License-Identifier: GPL-2.0-or-later */
#include "qemu/osdep.h"
#include "qemu/log.h"
#include "qemu/error-report.h"
#include "qapi/error.h"
#include "system/memory.h"
#include "system/address-spaces.h"
#include "system/system.h"
#include "hw/core/qdev.h"
#include "hw/core/sysbus.h"
#include "hw/arm/s32k388.h"
#include "hw/char/s32k3_uart.h"
#include "hw/net/s32k3_flexcan.h"
#include "hw/char/s32k3_flexio_uart.h"
#include "hw/arm/boot.h"
#include "hw/arm/machines-qom.h"
#include "hw/core/qdev-properties.h"
#include "hw/core/qdev-clock.h"
#include "hw/core/clock.h"
#include "hw/misc/unimp.h"
#include "qemu/units.h"
#include "semihosting/semihost.h"
#include "migration/vmstate.h"
#include "hw/core/irq.h"
#include <stdio.h>
#include <time.h>


static uint64_t s32k388_boot_status_read(void *opaque, hwaddr offset, unsigned size) {
    switch (offset) {
    case S32K3_BOOT_STATUS_GS:
        return S32K3_BOOT_STATUS_CLOCK_READY;
    case S32K3_BOOT_STATUS_CTL_STAT:
        return 0;
    case S32K3_BOOT_STATUS_PCS:
        return UINT32_MAX;
    default:
        return UINT32_MAX;
    }
}

static void s32k388_boot_status_write(void *opaque, hwaddr offset, uint64_t value, unsigned size) {
    if (size == 4 && offset + size <= S32K3_BOOT_STATUS_SIZE) {
        return;
    }

    qemu_log_mask(LOG_GUEST_ERROR,
                  "s32k388.boot-status: invalid write "
                  "(size %u, offset 0x%" HWADDR_PRIx ", value 0x%" PRIx64 ")\n",
                  size, offset, value);
}

static const MemoryRegionOps s32k388_boot_status_ops = {
    .read = s32k388_boot_status_read,
    .write = s32k388_boot_status_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
    .impl.min_access_size = 1,
    .impl.max_access_size = 4,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
};

static bool s32k388_mc_me_is_cofb_status(hwaddr offset)
{
    if (offset >= 0x110 && offset < 0x120) {
        return true;
    }

    return offset >= 0x10000 && ((offset & 0xf) == 0x4);
}

static uint64_t s32k388_mc_me_read(void *opaque, hwaddr offset, unsigned size)
{
    S32K388State *s = opaque;

    if (size != 4 || offset + size > S32K3_MC_ME_SIZE) {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k388.mc_me: invalid read size %u "
                      "@0x%" HWADDR_PRIx "\n", size, offset);
        return 0;
    }

    if (s32k388_mc_me_is_cofb_status(offset)) {
        return UINT32_MAX;
    }

    return s->mc_me_regs[offset >> 2];
}

static void s32k388_mc_me_write(void *opaque, hwaddr offset,
                                uint64_t value, unsigned size)
{
    S32K388State *s = opaque;

    if (size != 4 || offset + size > S32K3_MC_ME_SIZE) {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k388.mc_me: invalid write size %u "
                      "@0x%" HWADDR_PRIx ", value 0x%" PRIx64 "\n",
                      size, offset, value);
        return;
    }

    s->mc_me_regs[offset >> 2] = value;
}

static const MemoryRegionOps s32k388_mc_me_ops = {
    .read = s32k388_mc_me_read,
    .write = s32k388_mc_me_write,
    .endianness = DEVICE_LITTLE_ENDIAN,
    .impl.min_access_size = 4,
    .impl.max_access_size = 4,
    .valid.min_access_size = 4,
    .valid.max_access_size = 4,
};

static uint64_t s32k388_zero_read(void *opaque, hwaddr offset, unsigned size)
{
    return 0;
}

static void s32k388_zero_write(void *opaque, hwaddr offset,
                               uint64_t value, unsigned size)
{
}

static const MemoryRegionOps s32k388_zero_ops = {
    .read = s32k388_zero_read,
    .write = s32k388_zero_write,
    .endianness = DEVICE_LITTLE_ENDIAN,
    .impl.min_access_size = 1,
    .impl.max_access_size = 4,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
};

static void s32k388_add_zero_stub(MemoryRegion *system_memory,
                                  MemoryRegion *mr,
                                  const char *name,
                                  hwaddr base,
                                  hwaddr size)
{
    memory_region_init_io(mr, NULL, &s32k388_zero_ops, NULL, name, size);
    memory_region_add_subregion_overlap(system_memory, base, mr, 1);
}

static void s32k388_init_flexcan(S32K388State *s, ARMv7MState *armv7m) {
    static const hwaddr flexcan_bases[S32K388_CAN_COUNT] = {
        S32K3_FLEXCAN0_BASE,
        S32K3_FLEXCAN1_BASE,
        S32K3_FLEXCAN2_BASE,
        S32K3_FLEXCAN3_BASE,
        S32K3_FLEXCAN4_BASE,
        S32K3_FLEXCAN5_BASE
    };
    static const int flexcan_mb_irq[S32K388_CAN_COUNT] = {
        S32K3_FLEXCAN0_MB_IRQ,
        S32K3_FLEXCAN1_MB_IRQ,
        S32K3_FLEXCAN2_MB_IRQ,
        S32K3_FLEXCAN3_MB_IRQ,
        S32K3_FLEXCAN4_MB_IRQ,
        S32K3_FLEXCAN5_MB_IRQ
    };
    static const uint32_t flexcan_instance[S32K388_CAN_COUNT] = {
        0, 1, 2, 3, 4, 5
    };
    Error *local_err = NULL;

    qemu_log_mask(CPU_LOG_INT, "Initializing FlexCAN instances\n");

    for (int i = 0; i < S32K388_CAN_COUNT; i++) {
        DeviceState *dev = qdev_new(TYPE_S32K3X8_FLEXCAN);
        s->flexcan[i] = dev;

        qdev_prop_set_uint32(dev, "can-instance", flexcan_instance[i]);
        if (s->canbus[i]) {
            object_property_set_link(OBJECT(dev), "canbus", OBJECT(s->canbus[i]), &error_abort);
        }

        if (!sysbus_realize_and_unref(SYS_BUS_DEVICE(dev), &local_err)) {
            error_reportf_err(local_err, "Failed to realize FlexCAN instance %u: ", flexcan_instance[i]);
            return;
        }

        sysbus_mmio_map(SYS_BUS_DEVICE(dev), 0, flexcan_bases[i]);
        sysbus_connect_irq(SYS_BUS_DEVICE(dev), 0, qdev_get_gpio_in(DEVICE(armv7m), flexcan_mb_irq[i]));
    }

    qemu_log_mask(CPU_LOG_INT, "FlexCAN instances initialized\n");
}

static void s32k388_init_gmac(S32K388State *s, MachineState *machine)
{
    static const hwaddr gmac_bases[S32K388_GMAC_COUNT] = {
        S32K388_GMAC0_BASE,
        S32K388_GMAC1_BASE,
    };
    static const int gmac_irqs[S32K388_GMAC_COUNT] = {
        S32K388_GMAC0_IRQ,
        S32K388_GMAC1_IRQ,
    };
    char name[16];

    qemu_log_mask(CPU_LOG_INT, "Initializing GMAC Ethernet instances\n");

    for (int i = 0; i < S32K388_GMAC_COUNT; i++) {
        snprintf(name, sizeof(name), "gmac%d", i);
        object_initialize_child(OBJECT(machine), name, &s->gmac[i],
                                TYPE_NPCM_GMAC);

        qemu_configure_nic_device(DEVICE(&s->gmac[i]), true, NULL);
        sysbus_realize(SYS_BUS_DEVICE(&s->gmac[i]), &error_fatal);
        sysbus_mmio_map(SYS_BUS_DEVICE(&s->gmac[i]), 0, gmac_bases[i]);
        sysbus_connect_irq(SYS_BUS_DEVICE(&s->gmac[i]), 0,
                           qdev_get_gpio_in(DEVICE(&s->armv7m),
                                            gmac_irqs[i]));
    }

    qemu_log_mask(CPU_LOG_INT, "GMAC Ethernet instances initialized\n");
}

static void s32k388_init(MachineState* machine) {
    S32K388State* s = S32K388(machine);
    Error* error_local = NULL;
    DeviceState* dev;
    
    qemu_log_mask(CPU_LOG_INT, "Initializing S32K388\n");

    // Get system memory
    MemoryRegion* system_memory = get_system_memory();

    // Initialize memory
    qemu_log_mask(CPU_LOG_INT, "Initializing memory regions\n");
    // ITCM
    memory_region_init_ram(&s->itcm, NULL, "S32K388.itcm", INT_ITCM_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_ITCM_BASE, &s->itcm);

    // DTCM
    memory_region_init_ram(&s->dtcm, NULL, "S32K388.dtcm", INT_DTCM_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_DTCM_BASE, &s->dtcm);

    // DTCM Stack
    memory_region_init_ram(&s->dtcm_stack, NULL, "S32K388.dtcm_stack", INT_DTCM_STACK_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_DTCM_STACK_BASE, &s->dtcm_stack);

    // Flash
    memory_region_init_rom(&s->C0flash, NULL, "S32K388.C0flash", INT_CODE_FLASH0_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_CODE_FLASH0_BASE, &s->C0flash);
    memory_region_init_rom(&s->C1flash, NULL, "S32K388.C1flash", INT_CODE_FLASH1_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_CODE_FLASH1_BASE, &s->C1flash);
    memory_region_init_rom(&s->C2flash, NULL, "S32K388.C2flash", INT_CODE_FLASH2_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_CODE_FLASH2_BASE, &s->C2flash);
    memory_region_init_rom(&s->C3flash, NULL, "S32K388.C3flash", INT_CODE_FLASH3_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_CODE_FLASH3_BASE, &s->C3flash);
    memory_region_init_rom(&s->Dflash, NULL, "S32K388.Dflash", INT_DATA_FLASH_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_DATA_FLASH_BASE, &s->Dflash);
    memory_region_init_rom(&s->UNVMflash, NULL, "S32K388.UNVMflash", INT_UTEST_NVM_FLASH_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_UTEST_NVM_FLASH_BASE, &s->UNVMflash);

    // SRAM
    memory_region_init_ram(&s->sram_standby, NULL, "S32K388.sram_standby", INT_SRAM_STANDBY_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_SRAM_STANDBY_BASE, &s->sram_standby);
    memory_region_init_ram(&s->sram0, NULL, "S32K388.sram0", INT_SRAM_0_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_SRAM_0_BASE, &s->sram0);
    memory_region_init_ram(&s->sram1, NULL, "S32K388.sram1", INT_SRAM_1_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_SRAM_1_BASE, &s->sram1);
    memory_region_init_ram(&s->sram2, NULL, "S32K388.sram2", INT_SRAM_2_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_SRAM_2_BASE, &s->sram2);

    qemu_log_mask(CPU_LOG_INT, "Memory regions successfully initialized\n");

    // Initialize system clock
    s->sysclk = clock_new(OBJECT(machine), "SYSCLK");
    clock_set_hz(s->sysclk, S32K3_SYSCLK_FREQ);

    // Initialize ARM core
    object_initialize_child(OBJECT(machine), "armv7m", &s->armv7m, TYPE_ARMV7M);

    // Configure CPU
    qdev_prop_set_string(DEVICE(&s->armv7m), "cpu-type", ARM_CPU_TYPE_NAME("cortex-m7"));
    qdev_prop_set_uint32(DEVICE(&s->armv7m), "init-svtor", INT_CODE_FLASH0_CORE0_VTOR);
    qdev_prop_set_uint32(DEVICE(&s->armv7m), "init-nsvtor", INT_CODE_FLASH0_CORE0_VTOR);
    qdev_prop_set_uint32(DEVICE(&s->armv7m), "mpu-ns-regions", 0);
    qdev_prop_set_uint32(DEVICE(&s->armv7m), "mpu-s-regions", 0);
    qdev_prop_set_uint8(DEVICE(&s->armv7m), "num-prio-bits", 4);
    qdev_prop_set_uint32(DEVICE(&s->armv7m), "num-irq", 240);

    // Set up system connections
    object_property_set_link(OBJECT(&s->armv7m), "memory", OBJECT(system_memory), &error_abort);
    qdev_connect_clock_in(DEVICE(&s->armv7m), "cpuclk", s->sysclk);

    // Implement system bus device
    sysbus_realize(SYS_BUS_DEVICE(&s->armv7m), &error_local);

    // Initialize UART
    qemu_log_mask(CPU_LOG_INT, "Initializing UART\n");
    dev = qdev_new(TYPE_S32E8_LPUART);

    // Configure UART
    qdev_prop_set_chr(dev, "chardev", serial_hd(0));
    qdev_prop_set_uint32(dev, "lpuart_id", 3);
    s->uart = dev;

    sysbus_realize_and_unref(SYS_BUS_DEVICE(dev), &error_local);
    sysbus_mmio_map(SYS_BUS_DEVICE(dev), 0, S32K3_CONSOLE_LPUART_BASE);
    sysbus_connect_irq(SYS_BUS_DEVICE(dev), 0, qdev_get_gpio_in(DEVICE(&s->armv7m), S32K3_CONSOLE_LPUART_IRQ));

    // Initialize the FlexIO UART channels used for board-level loopback
    dev = qdev_new(TYPE_S32K3_FLEXIO_UART);
    s->flexio = dev;
    sysbus_realize_and_unref(SYS_BUS_DEVICE(dev), &error_local);
    s32k3_flexio_uart_connect_lpuart(S32K3_FLEXIO_UART(dev), S32K3X8_LPUART(s->uart));
    sysbus_mmio_map(SYS_BUS_DEVICE(dev), 0, S32K3_FLEXIO_BASE);
    sysbus_connect_irq(SYS_BUS_DEVICE(dev), 0, qdev_get_gpio_in(DEVICE(&s->armv7m), S32K3_FLEXIO_IRQ));

    // Initialize FlexCAN devices
    s32k388_init_flexcan(s, &s->armv7m);

    // Initialize GMAC Ethernet devices
    s32k388_init_gmac(s, machine);

    // Map any missing S32K3 peripheral region used by firmware
    create_unimplemented_device("s32k3x8.peripherals", S32K3_PERIPH_BASE, 16 * MiB);
    s32k388_add_zero_stub(system_memory, &s->mscm, "s32k388.mscm",
                          S32K3_MSCM_BASE, S32K3_MSCM_SIZE);
    s32k388_add_zero_stub(system_memory, &s->swt0, "s32k388.swt0",
                          S32K3_SWT0_BASE, S32K3_SWT0_SIZE);
    s32k388_add_zero_stub(system_memory, &s->rtc, "s32k388.rtc",
                          S32K3_RTC_BASE, S32K3_RTC_SIZE);
    s32k388_add_zero_stub(system_memory, &s->mc_rgm, "s32k388.mc_rgm",
                          S32K3_MC_RGM_BASE, S32K3_MC_RGM_SIZE);
    s32k388_add_zero_stub(system_memory, &s->dcm, "s32k388.dcm",
                          S32K3_DCM_BASE, S32K3_DCM_SIZE);
    s32k388_add_zero_stub(system_memory, &s->sxosc, "s32k388.sxosc",
                          S32K3_SXOSC_BASE, S32K3_SXOSC_SIZE);
    memory_region_init_io(&s->mc_me, NULL, &s32k388_mc_me_ops, s,
                          "s32k388.mc_me", S32K3_MC_ME_SIZE);
    memory_region_add_subregion_overlap(system_memory, S32K3_MC_ME_BASE,
                                        &s->mc_me, 1);
    memory_region_init_io(&s->boot_status, NULL, &s32k388_boot_status_ops, s, "s32k388.boot-status", S32K3_BOOT_STATUS_SIZE);
    memory_region_add_subregion_overlap(system_memory, S32K3_BOOT_STATUS_BASE, &s->boot_status, 2);

    // Enabling semihosting for guest BKPT operations
    qemu_semihosting_enable();

    // Load firmware
    armv7m_load_kernel(s->armv7m.cpu, machine->kernel_filename, INT_CODE_FLASH0_BASE, INT_CODE_FLASH0_SIZE);
}

static void s32k388_class_init(ObjectClass* oc, const void* data) {
    MachineClass* mc = MACHINE_CLASS(oc);
    mc->desc = "NXP S32K388 Development Board (Cortex-M7)";
    mc->init = s32k388_init;
    mc->default_cpus = 1;
    mc->min_cpus = 1;
    mc->max_cpus = 1;
    mc->default_ram_size = SRAM_SIZE;
}

static void s32k388_instance_init(Object *obj)
{
    S32K388State *s = S32K388(obj);

    object_property_add_link(obj, "canbus0", TYPE_CAN_BUS,
                             (Object **)&s->canbus[0],
                             object_property_allow_set_link, 0);
    object_property_add_link(obj, "canbus1", TYPE_CAN_BUS,
                             (Object **)&s->canbus[1],
                             object_property_allow_set_link, 0);
    object_property_add_link(obj, "canbus2", TYPE_CAN_BUS,
                             (Object **)&s->canbus[2],
                             object_property_allow_set_link, 0);
    object_property_add_link(obj, "canbus3", TYPE_CAN_BUS,
                             (Object **)&s->canbus[3],
                             object_property_allow_set_link, 0);
    object_property_add_link(obj, "canbus4", TYPE_CAN_BUS,
                             (Object **)&s->canbus[4],
                             object_property_allow_set_link, 0);
    object_property_add_link(obj, "canbus5", TYPE_CAN_BUS,
                             (Object **)&s->canbus[5],
                             object_property_allow_set_link, 0);
}

static const TypeInfo s32k388_type = {
    .name = TYPE_S32K388,
    .parent = TYPE_MACHINE,
    .instance_size = sizeof(S32K388State),
    .instance_init = s32k388_instance_init,
    .class_init = s32k388_class_init,
    .interfaces = arm_machine_interfaces,
};

// Register machine type
static void s32k388_machine_init(void) {
    qemu_log_mask(CPU_LOG_INT, "Registering S32K388 machine type\n");
    type_register_static(&s32k388_type);
}

type_init(s32k388_machine_init);
