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
#include "hw/arm/s32k389.h"
#include "hw/char/s32k3_uart.h"
#include "hw/net/s32k3_flexcan.h"
#include "hw/char/s32k3_flexio_uart.h"
#include "hw/ssi/s32k3_lpspi.h"
#include "hw/i2c/s32k3_lpi2c.h"
#include "hw/watchdog/s32k3_swt.h"
#include "hw/misc/s32k3_crc.h"
#include "hw/adc/s32k3_adc.h"
#include "hw/timer/s32k3_emios.h"
#include "hw/dma/s32k3_edma.h"
#include "hw/net/npcm_gmac.h"
#include "hw/ssi/s32k3_qspi.h"
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

/*
 * Keep the SWT implementation object in the S32K389 link. The generic HMP
 * monitor has only a weak reference because other machine targets do not
 * include the optional SWT model.
 */
static void (*const s32k389_swt_trigger_link_anchor)(uint32_t, Error **)
    __attribute__((used)) =
    s32k3_swt_trigger;

 
/*
* Real MC_ME peripheral (base 0x402DC000, verified against manual section
* 46.7.1 "MC_ME memory map"). Only the specific offsets firmware checks at
* boot are handled; values are simplified stand-ins (see S32K3_MC_ME_*
* comments in the header for the real register names/reset values).
*/
static uint64_t s32k389_mc_me_read(void *opaque, hwaddr offset, unsigned size) {
    switch (offset) {
    case S32K3_MC_ME_PRTN1_COFB0_STAT:
        return S32K3_MC_ME_CLOCK_READY_BIT;
    case S32K3_MC_ME_PRTN2_PUPD:
        return 0;
    case S32K3_MC_ME_PRTN2_COFB0_STAT:
        return UINT32_MAX;
    default:
        return UINT32_MAX;
    }
}
 
static void s32k389_mc_me_write(void *opaque, hwaddr offset, uint64_t value, unsigned size) {
    qemu_log_mask(LOG_UNIMP,
                  "s32k389.mc_me: unimplemented write "
                  "(size %u, offset 0x%" HWADDR_PRIx ", value 0x%" PRIx64 ")\n",
                  size, offset, value);
}
 
static const MemoryRegionOps s32k389_mc_me_ops = {
    .read = s32k389_mc_me_read,
    .write = s32k389_mc_me_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
    .impl.min_access_size = 1,
    .impl.max_access_size = 4,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
};
 
/*
* Generic catch-all stub covering the FIRC/FXOSC/MC_CGM address range
* (0x402D0000-0x402DBFFF). NOT a functional model of those clock modules -
* just a plain read/write register array so firmware probing them doesn't
* fault. Previously this range was (incorrectly) labeled "mc_me".
*/
static bool s32k389_clkgen_is_cofb_status(hwaddr offset)
{
    if (offset >= 0x110 && offset < 0x120) {
        return true;
    }
 
    return offset >= 0x10000 && ((offset & 0xf) == 0x4);
}
 
static uint64_t s32k389_clkgen_read(void *opaque, hwaddr offset, unsigned size)
{
    S32K389State *s = opaque;
 
    if (size != 4 || offset + size > S32K3_CLKGEN_STUB_SIZE) {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k389.clkgen_stub: invalid read size %u "
                      "@0x%" HWADDR_PRIx "\n", size, offset);
        return 0;
    }
 
    if (s32k389_clkgen_is_cofb_status(offset)) {
        return UINT32_MAX;
    }
 
    return s->clkgen_regs[offset >> 2];
}
 
static void s32k389_clkgen_write(void *opaque, hwaddr offset,
                                uint64_t value, unsigned size)
{
    S32K389State *s = opaque;
 
    if (size != 4 || offset + size > S32K3_CLKGEN_STUB_SIZE) {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k389.clkgen_stub: invalid write size %u "
                      "@0x%" HWADDR_PRIx ", value 0x%" PRIx64 "\n",
                      size, offset, value);
        return;
    }
 
    s->clkgen_regs[offset >> 2] = value;
}
 
static const MemoryRegionOps s32k389_clkgen_ops = {
    .read = s32k389_clkgen_read,
    .write = s32k389_clkgen_write,
    .endianness = DEVICE_LITTLE_ENDIAN,
    .impl.min_access_size = 4,
    .impl.max_access_size = 4,
    .valid.min_access_size = 4,
    .valid.max_access_size = 4,
};

/*
 * MSCM minimal model.
 *
 * NXP startup code reads CPXTYPE at 0x04 for the current core ID and a
 * TCM-mode word at 0x14 when choosing lockstep vs split-lock TCM bounds.
 */
static uint64_t s32k389_mscm_read(void *opaque, hwaddr offset, unsigned size)
{
    if (offset + size > S32K3_MSCM_SIZE) {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k389.mscm: invalid read size %u @0x%"
                      HWADDR_PRIx "\n", size, offset);
        return 0;
    }

    switch (offset) {
    case 0x04:
        return current_cpu ? (current_cpu->cpu_index & 0x7) : 0;
    case 0x14:
        return 0;
    default:
        return 0;
    }
}

static void s32k389_mscm_write(void *opaque, hwaddr offset,
                               uint64_t value, unsigned size)
{
    if (offset + size > S32K3_MSCM_SIZE) {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k389.mscm: invalid write size %u @0x%"
                      HWADDR_PRIx " (value 0x%" PRIx64 ")\n",
                      size, offset, value);
    }
}

static const MemoryRegionOps s32k389_mscm_ops = {
    .read = s32k389_mscm_read,
    .write = s32k389_mscm_write,
    .endianness = DEVICE_LITTLE_ENDIAN,
    .impl.min_access_size = 1,
    .impl.max_access_size = 4,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
};

/*
 * STCU2 (Self-Test Control Unit) minimal stub - see the S32K3_STCU2_BASE
 * comment in the header for scope/caveats. Offsets are our own choice
 * (not manual-verified): 0x0 = BSTART (self-test start pulses, read back
 * as always-idle/complete), 0x4 = ALGOSEL (algorithm select, plain
 * storage), 0x8 = a synthetic "lockstep/self-test status" word that
 * always reports all 4 cores present, decoupled (split-lock), and the
 * last self-test as passed - there is no real BIST/LBIST/MBIST engine
 * behind this.
 */
#define S32K389_STCU2_BSTART  0x0
#define S32K389_STCU2_ALGOSEL 0x4
#define S32K389_STCU2_STATUS  0x8
#define S32K389_STCU2_STATUS_VALUE 0x0000000Fu /* 4 cores, self-test pass */

static uint64_t s32k389_stcu2_read(void *opaque, hwaddr offset, unsigned size)
{
    S32K389State *s = opaque;

    switch (offset) {
    case S32K389_STCU2_BSTART:
        return s->stcu2_bstart;
    case S32K389_STCU2_ALGOSEL:
        return s->stcu2_algosel;
    case S32K389_STCU2_STATUS:
        return S32K389_STCU2_STATUS_VALUE;
    default:
        return 0;
    }
}

static void s32k389_stcu2_write(void *opaque, hwaddr offset,
                                uint64_t value, unsigned size)
{
    S32K389State *s = opaque;

    switch (offset) {
    case S32K389_STCU2_BSTART:
        /* Real BSTART pulses trigger a BIST run and self-clear; since
         * there's no BIST engine here, just store it (harmless echo). */
        s->stcu2_bstart = value;
        break;
    case S32K389_STCU2_ALGOSEL:
        s->stcu2_algosel = value;
        break;
    case S32K389_STCU2_STATUS:
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k389.stcu2: status word is read-only\n");
        break;
    default:
        break;
    }
}

static const MemoryRegionOps s32k389_stcu2_ops = {
    .read = s32k389_stcu2_read,
    .write = s32k389_stcu2_write,
    .endianness = DEVICE_LITTLE_ENDIAN,
    .impl.min_access_size = 4,
    .impl.max_access_size = 4,
    .valid.min_access_size = 4,
    .valid.max_access_size = 4,
};

/*
 * Additional Cortex-M7 core (CM7_1/CM7_2/CM7_3) - see S32K389_NUM_CORES
 * comment in the header. Each gets its own private ITCM/DTCM at the same
 * local addresses core 0 uses (0x0 / 0x2000_0000), overlaid on a
 * per-core alias of the shared system bus so flash/SRAM/peripherals are
 * still visible identically to core 0, and its own reset handler via
 * armv7m_load_kernel(..., NULL, ...) (kernel_filename is NULL - the
 * shared flash image was already loaded once by core 0's call).
 */
static void s32k389_init_extra_core(S32K389State *s, MemoryRegion *system_memory,
                                     ARMv7MState *core, MemoryRegion *core_mem,
                                     MemoryRegion *itcm, MemoryRegion *dtcm,
                                     MemoryRegion *dtcm_stack,
                                     const char *name_prefix, int core_num)
{
    Error *local_err = NULL;
    char name[64];

    snprintf(name, sizeof(name), "%s.mem", name_prefix);
    memory_region_init_alias(core_mem, OBJECT(s), name, system_memory,
                             0, UINT32_MAX);

    snprintf(name, sizeof(name), "%s.itcm", name_prefix);
    memory_region_init_ram(itcm, NULL, name, INT_ITCM_SIZE, &error_fatal);
    memory_region_add_subregion_overlap(core_mem, INT_ITCM_BASE, itcm, 1);

    snprintf(name, sizeof(name), "%s.dtcm", name_prefix);
    memory_region_init_ram(dtcm, NULL, name, INT_DTCM_SIZE, &error_fatal);
    memory_region_add_subregion_overlap(core_mem, INT_DTCM_BASE, dtcm, 1);

    snprintf(name, sizeof(name), "%s.dtcm_stack", name_prefix);
    memory_region_init_ram(dtcm_stack, NULL, name, INT_DTCM_STACK_SIZE,
                           &error_fatal);
    memory_region_add_subregion_overlap(core_mem, INT_DTCM_STACK_BASE,
                                        dtcm_stack, 1);

    object_initialize_child(OBJECT(s), name_prefix, core, TYPE_ARMV7M);
    qdev_prop_set_string(DEVICE(core), "cpu-type", ARM_CPU_TYPE_NAME("cortex-m7"));
    qdev_prop_set_uint32(DEVICE(core), "init-svtor", INT_CODE_FLASH0_CORE0_VTOR);
    qdev_prop_set_uint32(DEVICE(core), "init-nsvtor", INT_CODE_FLASH0_CORE0_VTOR);
    qdev_prop_set_uint32(DEVICE(core), "mpu-ns-regions", 0);
    qdev_prop_set_uint32(DEVICE(core), "mpu-s-regions", 0);
    qdev_prop_set_uint8(DEVICE(core), "num-prio-bits", 4);
    qdev_prop_set_uint32(DEVICE(core), "num-irq", 240);

    object_property_set_link(OBJECT(core), "memory", OBJECT(core_mem), &error_abort);
    qdev_connect_clock_in(DEVICE(core), "cpuclk", s->sysclk);

    if (!sysbus_realize(SYS_BUS_DEVICE(core), &local_err)) {
        error_reportf_err(local_err, "Failed to realize core %d: ", core_num);
        return;
    }

    /* kernel_filename=NULL: the shared flash image was already loaded by
     * core 0; this call's real job is registering this CPU's own
     * qemu_register_reset() handler, which every M-profile CPU needs. */
    armv7m_load_kernel(core->cpu, NULL, INT_CODE_FLASH0_BASE, FLASH_SIZE);

    qemu_log_mask(CPU_LOG_INT, "Core %d (%s) initialized\n", core_num, name_prefix);
}

static bool s32k389_realize_sysbus_device(DeviceState *dev,
                                           ARMv7MState *armv7m,
                                           hwaddr base, int irq,
                                           const char *peripheral_name)
{
    Error *local_err = NULL;

    /*
     * This is the common board-level hookup for a peripheral that lives on
     * the Cortex-M7 system bus: realize the model, expose its MMIO window at
     * the S32K389 address from the manual, and connect it to the CPU IRQ line.
     */
    if (!sysbus_realize_and_unref(SYS_BUS_DEVICE(dev), &local_err)) {
        error_reportf_err(local_err, "Failed to realize %s: ", peripheral_name);
        return false;
    }

    /*
     * The board has a low-priority catch-all peripheral aperture. Use an
     * explicit higher-priority mapping for concrete devices so their MMIO
     * handlers receive accesses in overlapping regions.
     */
    sysbus_mmio_map_overlap(SYS_BUS_DEVICE(dev), 0, base, 1);

    if (irq >= 0) {
        sysbus_connect_irq(SYS_BUS_DEVICE(dev), 0,
                           qdev_get_gpio_in(DEVICE(armv7m), irq));
    }

    return true;
}

static void s32k389_init_flexcan(S32K389State *s, ARMv7MState *armv7m) {
    /*
     * Board glue for FlexCAN: each emulated controller is created as a
     * sysbus device, assigned its instance ID, mapped into the peripheral
     * address space, and tied to the matching message-buffer IRQ line.
     */
    static const hwaddr flexcan_bases[S32K389_CAN_COUNT] = {
        S32K3_FLEXCAN0_BASE,
        S32K3_FLEXCAN1_BASE,
        S32K3_FLEXCAN2_BASE,
        S32K3_FLEXCAN3_BASE,
        S32K3_FLEXCAN4_BASE,
        S32K3_FLEXCAN5_BASE,
        S32K3_FLEXCAN6_BASE,
        S32K3_FLEXCAN7_BASE,
        S32K3_FLEXCAN8_BASE,
        S32K3_FLEXCAN9_BASE,
        S32K3_FLEXCAN10_BASE,
        S32K3_FLEXCAN11_BASE,
    };
    /*
     * Verified against S32K3xx_interrupt_map.xlsx (Interrupts sheet, S32K389
     * column). All 12 instances now have confirmed IRQ numbers - see the
     * S32K3_FLEXCANn_MB_IRQ comments in the header for details.
     */
    static const int flexcan_mb_irq[S32K389_CAN_COUNT] = {
        S32K3_FLEXCAN0_MB_IRQ,
        S32K3_FLEXCAN1_MB_IRQ,
        S32K3_FLEXCAN2_MB_IRQ,
        S32K3_FLEXCAN3_MB_IRQ,
        S32K3_FLEXCAN4_MB_IRQ,
        S32K3_FLEXCAN5_MB_IRQ,
        S32K3_FLEXCAN6_MB_IRQ,
        S32K3_FLEXCAN7_MB_IRQ,
        S32K3_FLEXCAN8_MB_IRQ,
        S32K3_FLEXCAN9_MB_IRQ,
        S32K3_FLEXCAN10_MB_IRQ,
        S32K3_FLEXCAN11_MB_IRQ,
    };
    static const uint32_t flexcan_instance[S32K389_CAN_COUNT] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
    };
    Error *local_err = NULL;
 
    qemu_log_mask(CPU_LOG_INT, "Initializing FlexCAN instances\n");
 
    for (int i = 0; i < S32K389_CAN_COUNT; i++) {
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
 
        sysbus_connect_irq(SYS_BUS_DEVICE(dev), 0,
                            qdev_get_gpio_in(DEVICE(armv7m), flexcan_mb_irq[i]));
    }
 
    qemu_log_mask(CPU_LOG_INT, "FlexCAN instances initialized\n");
}
 
static void s32k389_init_lpspi(S32K389State *s, ARMv7MState *armv7m) {
    /*
     * LPSPI is instantiated here in the same board-level style as FlexCAN:
     * each controller gets its own MMIO window and IRQ line on the Cortex-M7.
     */
    static const hwaddr lpspi_bases[S32K389_NUM_LPSPI] = {
        S32K3_LPSPI0_BASE,
        S32K3_LPSPI1_BASE,
        S32K3_LPSPI2_BASE,
        S32K3_LPSPI3_BASE,
        S32K3_LPSPI4_BASE,
        S32K3_LPSPI5_BASE,
    };
    static const int lpspi_irqs[S32K389_NUM_LPSPI] = {
        S32K3_LPSPI0_IRQ,
        S32K3_LPSPI1_IRQ,
        S32K3_LPSPI2_IRQ,
        S32K3_LPSPI3_IRQ,
        S32K3_LPSPI4_IRQ,
        S32K3_LPSPI5_IRQ,
    };
    qemu_log_mask(CPU_LOG_INT, "Initializing LPSPI instances\n");

    for (int i = 0; i < S32K389_NUM_LPSPI; i++) {
        DeviceState *dev = qdev_new(TYPE_S32K3_LPSPI);
        s->lpspi[i] = dev;

        /* The instance ID is set here so the model can distinguish one
         * controller from the next when the guest accesses the peripheral. */
        qdev_prop_set_uint32(dev, "lpspi-id", i);

        if (!s32k389_realize_sysbus_device(dev, armv7m, lpspi_bases[i],
                                            lpspi_irqs[i], "LPSPI")) {
            return;
        }
    }

    qemu_log_mask(CPU_LOG_INT, "LPSPI instances initialized\n");
}

static void s32k389_init_lpi2c(S32K389State *s, ARMv7MState *armv7m) {
    /*
     * LPI2C is wired into the board in the same way as the other system-bus
     * peripherals: one MMIO window per instance and one interrupt line per
     * instance.
     */
    static const hwaddr lpi2c_bases[S32K389_NUM_LPI2C] = {
        S32K3_LPI2C0_BASE,
        S32K3_LPI2C1_BASE,
    };
    static const int lpi2c_irqs[S32K389_NUM_LPI2C] = {
        S32K3_LPI2C0_IRQ,
        S32K3_LPI2C1_IRQ,
    };
    qemu_log_mask(CPU_LOG_INT, "Initializing LPI2C instances\n");

    for (int i = 0; i < S32K389_NUM_LPI2C; i++) {
        DeviceState *dev = qdev_new(TYPE_S32K3_LPI2C);
        s->lpi2c[i] = dev;

        qdev_prop_set_uint32(dev, "lpi2c-id", i);

        if (!s32k389_realize_sysbus_device(dev, armv7m, lpi2c_bases[i],
                                            lpi2c_irqs[i], "LPI2C")) {
            return;
        }
    }

    qemu_log_mask(CPU_LOG_INT, "LPI2C instances initialized\n");
}

static void s32k389_init_swt(S32K389State *s, ARMv7MState *armv7m) {
    /*
     * SWT is added as a simple watchdog controller on the system bus so the
     * board exposes the same kind of MMIO + interrupt wiring used by the
     * other peripheral drivers.
     */
    static const hwaddr swt_bases[S32K389_NUM_SWT] = {
        S32K3_SWT0_BASE,
        S32K3_SWT1_BASE,
        S32K3_SWT2_BASE,
        S32K3_SWT3_BASE,
    };
    static const int swt_irqs[S32K389_NUM_SWT] = {
        S32K3_SWT0_IRQ,
        S32K3_SWT1_IRQ,
        S32K3_SWT2_IRQ,
        S32K3_SWT3_IRQ,
    };
    qemu_log_mask(CPU_LOG_INT, "Initializing SWT instances\n");

    for (int i = 0; i < S32K389_NUM_SWT; i++) {
        DeviceState *dev = qdev_new(TYPE_S32K3_SWT);
        s->swt[i] = dev;

        qdev_prop_set_uint32(dev, "swt-id", i);

        if (!s32k389_realize_sysbus_device(dev, armv7m, swt_bases[i],
                                            swt_irqs[i], "SWT")) {
            return;
        }
    }

    qemu_log_mask(CPU_LOG_INT, "SWT instances initialized\n");
}

static void s32k389_init_adc(S32K389State *s, ARMv7MState *armv7m) {
    /*
     * ADC instances are attached to the board in the same way as the other
     * peripheral blocks: one device object, one MMIO window, and one IRQ line.
     */
    static const hwaddr adc_bases[S32K389_NUM_ADC] = {
        S32K3_ADC0_BASE,
        S32K3_ADC1_BASE,
        S32K3_ADC2_BASE,
    };
    static const int adc_irqs[S32K389_NUM_ADC] = {
        S32K3_ADC0_IRQ,
        S32K3_ADC1_IRQ,
        S32K3_ADC2_IRQ,
    };
    qemu_log_mask(CPU_LOG_INT, "Initializing ADC instances\n");

    for (int i = 0; i < S32K389_NUM_ADC; i++) {
        DeviceState *dev = qdev_new(TYPE_S32K3_ADC);
        s->adc[i] = dev;

        qdev_prop_set_uint32(dev, "adc-id", i);

        if (!s32k389_realize_sysbus_device(dev, armv7m, adc_bases[i],
                                            adc_irqs[i], "ADC")) {
            return;
        }
    }

    qemu_log_mask(CPU_LOG_INT, "ADC instances initialized\n");
}

static void s32k389_init_emios(S32K389State *s, ARMv7MState *armv7m) {
    /*
     * eMIOS is registered as another board-level timer peripheral, with the
     * same MMIO/IRQ connection pattern used throughout this machine model.
     */
    static const hwaddr emios_bases[S32K389_NUM_EMIOS] = {
        S32K3_EMIOS0_BASE,
        S32K3_EMIOS1_BASE,
        S32K3_EMIOS2_BASE,
    };
    static const int emios_irqs[S32K389_NUM_EMIOS] = {
        S32K3_EMIOS0_IRQ,
        S32K3_EMIOS1_IRQ,
        S32K3_EMIOS2_IRQ,
    };
    qemu_log_mask(CPU_LOG_INT, "Initializing eMIOS instances\n");

    for (int i = 0; i < S32K389_NUM_EMIOS; i++) {
        DeviceState *dev = qdev_new(TYPE_S32K3_EMIOS);
        s->emios[i] = dev;

        qdev_prop_set_uint32(dev, "emios-id", i);

        if (!s32k389_realize_sysbus_device(dev, armv7m, emios_bases[i],
                                            emios_irqs[i], "eMIOS")) {
            return;
        }
    }

    qemu_log_mask(CPU_LOG_INT, "eMIOS instances initialized\n");
}

static void s32k389_init_edma(S32K389State *s, ARMv7MState *armv7m) {
    /*
     * Base addresses verified against S32K3xx Reference Manual sections
     * 15.6.1.1 (management page) and 15.6.2.1 (TCD/channel page). IRQ
     * numbers are an unverified placeholder - see the
     * S32K3_EDMA_IRQ_BASE comment in the header.
     */
    Error *local_err = NULL;
    DeviceState *dev = qdev_new(TYPE_S32K3_EDMA);

    s->edma = dev;

    qemu_log_mask(CPU_LOG_INT, "Initializing eDMA\n");

    if (!sysbus_realize_and_unref(SYS_BUS_DEVICE(dev), &local_err)) {
        error_reportf_err(local_err, "Failed to realize eDMA: ");
        return;
    }

    sysbus_mmio_map(SYS_BUS_DEVICE(dev), 0, S32K3_EDMA_MGMT_BASE);
    sysbus_mmio_map(SYS_BUS_DEVICE(dev), 1, S32K3_EDMA_CH_BASE);

    for (int i = 0; i < S32K3_EDMA_NUM_CHANNELS; i++) {
        sysbus_connect_irq(SYS_BUS_DEVICE(dev), i,
                            qdev_get_gpio_in(DEVICE(armv7m),
                                             S32K3_EDMA_IRQ_BASE + i));
    }

    qemu_log_mask(CPU_LOG_INT, "eDMA initialized\n");
}

static void s32k389_init_gmac(S32K389State *s, MachineState *machine)
{
    /*
     * Base addresses/instance count reused from the already-verified
     * S32K388 GMAC model on the strength of the manual grouping both
     * chips together for this peripheral - see S32K389_GMAC0_BASE
     * comment in the header.
     */
    static const hwaddr gmac_bases[S32K389_GMAC_COUNT] = {
        S32K389_GMAC0_BASE,
        S32K389_GMAC1_BASE,
    };
    static const int gmac_irqs[S32K389_GMAC_COUNT] = {
        S32K389_GMAC0_IRQ,
        S32K389_GMAC1_IRQ,
    };
    char name[16];

    qemu_log_mask(CPU_LOG_INT, "Initializing GMAC Ethernet instances\n");

    for (int i = 0; i < S32K389_GMAC_COUNT; i++) {
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

static void s32k389_init_qspi(S32K389State *s, ARMv7MState *armv7m) {
    /*
     * Controller base verified against manual section 80.13.2.1; ARDB
     * base against section 80.13.4.1. IRQ is an unverified placeholder -
     * see the S32K3_QSPI_IRQ comment in the header.
     */
    Error *local_err = NULL;
    DeviceState *dev = qdev_new(TYPE_S32K3_QSPI);

    s->qspi = dev;

    qemu_log_mask(CPU_LOG_INT, "Initializing QuadSPI\n");

    if (!sysbus_realize_and_unref(SYS_BUS_DEVICE(dev), &local_err)) {
        error_reportf_err(local_err, "Failed to realize QuadSPI: ");
        return;
    }

    sysbus_mmio_map(SYS_BUS_DEVICE(dev), 0, S32K3_QSPI_BASE);
    sysbus_mmio_map(SYS_BUS_DEVICE(dev), 1, S32K3_QSPI_ARDB_BASE);
    sysbus_connect_irq(SYS_BUS_DEVICE(dev), 0,
                        qdev_get_gpio_in(DEVICE(armv7m), S32K3_QSPI_IRQ));

    qemu_log_mask(CPU_LOG_INT, "QuadSPI initialized\n");
}

static void s32k389_init_sai(S32K389State *s, ARMv7MState *armv7m) {
    /*
     * SAI is attached as a board-level audio peripheral using the same basic
     * composition as the other sysbus models: a model object, per-instance
     * register state, and a CPU IRQ hookup.
     */
    static const hwaddr sai_bases[S32K389_NUM_SAI] = {
        S32K3_SAI0_BASE, S32K3_SAI1_BASE,
    };
    static const uint32_t sai_param_resets[S32K389_NUM_SAI] = {
        S32K3_SAI0_PARAM_RESET, S32K3_SAI1_PARAM_RESET,
    };
    static const int sai_irqs[S32K389_NUM_SAI] = {
        S32K3_SAI0_IRQ, S32K3_SAI1_IRQ,
    };
    int i;

    qemu_log_mask(CPU_LOG_INT, "Initializing SAI\n");

    for (i = 0; i < S32K389_NUM_SAI; i++) {
        DeviceState *dev = qdev_new(TYPE_S32K3_SAI);

        s->sai[i] = dev;
        qdev_prop_set_uint32(dev, "param-reset", sai_param_resets[i]);

        if (!s32k389_realize_sysbus_device(dev, armv7m, sai_bases[i],
                                            sai_irqs[i], "SAI")) {
            return;
        }
    }

    qemu_log_mask(CPU_LOG_INT, "SAI instances initialized\n");
}

static void s32k389_init(MachineState* machine) {
    S32K389State* s = S32K389(machine);
    Error* error_local = NULL;
    DeviceState* dev;
    
    qemu_log_mask(CPU_LOG_INT, "Initializing S32K389\n");
 
    // Get system memory
    MemoryRegion* system_memory = get_system_memory();
 
    // Initialize memory
    qemu_log_mask(CPU_LOG_INT, "Initializing memory regions\n");
    // ITCM
    memory_region_init_ram(&s->itcm, NULL, "S32K389.itcm", INT_ITCM_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_ITCM_BASE, &s->itcm);
 
    // DTCM
    memory_region_init_ram(&s->dtcm, NULL, "S32K389.dtcm", INT_DTCM_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_DTCM_BASE, &s->dtcm);
 
    // DTCM Stack
    memory_region_init_ram(&s->dtcm_stack, NULL, "S32K389.dtcm_stack", INT_DTCM_STACK_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_DTCM_STACK_BASE, &s->dtcm_stack);
 
    // Flash - 8 blocks across two controllers (PFC0 + PFC1), 12MB total
    memory_region_init_rom(&s->flash0, NULL, "S32K389.flash0", INT_CODE_FLASH0_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_CODE_FLASH0_BASE, &s->flash0);
    memory_region_init_rom(&s->flash1, NULL, "S32K389.flash1", INT_CODE_FLASH1_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_CODE_FLASH1_BASE, &s->flash1);
    memory_region_init_rom(&s->flash2, NULL, "S32K389.flash2", INT_CODE_FLASH2_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_CODE_FLASH2_BASE, &s->flash2);
    memory_region_init_rom(&s->flash3, NULL, "S32K389.flash3", INT_CODE_FLASH3_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_CODE_FLASH3_BASE, &s->flash3);
    memory_region_init_rom(&s->flash4, NULL, "S32K389.flash4", INT_CODE_FLASH4_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_CODE_FLASH4_BASE, &s->flash4);
    memory_region_init_rom(&s->flash5, NULL, "S32K389.flash5", INT_CODE_FLASH5_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_CODE_FLASH5_BASE, &s->flash5);
    memory_region_init_rom(&s->flash6, NULL, "S32K389.flash6", INT_CODE_FLASH6_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_CODE_FLASH6_BASE, &s->flash6);
    memory_region_init_rom(&s->flash7, NULL, "S32K389.flash7", INT_CODE_FLASH7_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_CODE_FLASH7_BASE, &s->flash7);
    memory_region_init_rom(&s->Dflash, NULL, "S32K389.Dflash", INT_DATA_FLASH_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_DATA_FLASH_BASE, &s->Dflash);
    memory_region_init_rom(&s->UNVMflash, NULL, "S32K389.UNVMflash", INT_UTEST_NVM_FLASH_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_UTEST_NVM_FLASH_BASE, &s->UNVMflash);
 
    // SRAM
    memory_region_init_ram(&s->sram_standby, NULL, "S32K389.sram_standby", INT_SRAM_STANDBY_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_SRAM_STANDBY_BASE, &s->sram_standby);
    memory_region_init_ram(&s->sram0, NULL, "S32K389.sram0", INT_SRAM_0_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_SRAM_0_BASE, &s->sram0);
    memory_region_init_ram(&s->sram1, NULL, "S32K389.sram1", INT_SRAM_1_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_SRAM_1_BASE, &s->sram1);
    memory_region_init_ram(&s->sram2, NULL, "S32K389.sram2", INT_SRAM_2_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_SRAM_2_BASE, &s->sram2);
    memory_region_init_ram(&s->sram3, NULL, "S32K389.sram3", INT_SRAM_3_SIZE, &error_fatal);
    memory_region_add_subregion(system_memory, INT_SRAM_3_BASE, &s->sram3);
 
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

    /*
     * Install the catch-all peripheral aperture before concrete devices.
     * Specific MMIO regions added below must take precedence over this
     * fallback; mapping it last would swallow guest accesses to real devices.
     */
    create_unimplemented_device("s32k3x8.peripherals", S32K3_PERIPH_BASE,
                                16 * MiB);

    // Initialize the board's console and simple serial helpers first so the
    // machine can expose UART traffic before the rest of the peripheral set is
    // brought up.
    qemu_log_mask(CPU_LOG_INT, "Initializing UART\n");
    dev = qdev_new(TYPE_S32E8_LPUART);
 
    // Configure UART
    qdev_prop_set_chr(dev, "chardev", serial_hd(0));
    qdev_prop_set_uint32(dev, "lpuart_id", 3);
    s->uart = dev;
 
    if (!s32k389_realize_sysbus_device(dev, &s->armv7m,
                                        S32K3_CONSOLE_LPUART_BASE,
                                        S32K3_CONSOLE_LPUART_IRQ,
                                        "console UART")) {
        return;
    }
 
    // Initialize the FlexIO UART channels used for board-level loopback
    dev = qdev_new(TYPE_S32K3_FLEXIO_UART);
    s->flexio = dev;
    s32k3_flexio_uart_connect_lpuart(S32K3_FLEXIO_UART(dev), S32K3X8_LPUART(s->uart));
    if (!s32k389_realize_sysbus_device(dev, &s->armv7m, S32K3_FLEXIO_BASE,
                                        S32K3_FLEXIO_IRQ, "FlexIO UART")) {
        return;
    }
 
    // Initialize the peripheral blocks next. Each one follows the same high-
    // level pattern: create the model, map it into the S32K389 address space,
    // and connect the CPU interrupt line that the firmware expects.
    s32k389_init_flexcan(s, &s->armv7m);

    // Initialize LPSPI devices
    s32k389_init_lpspi(s, &s->armv7m);

    // Initialize LPI2C devices
    s32k389_init_lpi2c(s, &s->armv7m);

    // Initialize SWT (watchdog) devices
    s32k389_init_swt(s, &s->armv7m);

    // Initialize CRC device (no interrupt line, manual 58.3.6)
    dev = qdev_new(TYPE_S32K3_CRC);
    s->crc = dev;
    if (!s32k389_realize_sysbus_device(dev, &s->armv7m, S32K3_CRC_BASE,
                                        -1, "CRC")) {
        return;
    }

    // Initialize ADC devices
    s32k389_init_adc(s, &s->armv7m);
    s32k389_init_emios(s, &s->armv7m);
    s32k389_init_edma(s, &s->armv7m);
    s32k389_init_gmac(s, machine);
    s32k389_init_qspi(s, &s->armv7m);
    s32k389_init_sai(s, &s->armv7m);
 
    // Real MSCM aperture. This must overlay the broad eDMA channel mapping
    // too, because the older eDMA model exposes all 32 TCD windows as one
    // contiguous block starting at 0x40210000.
    memory_region_init_io(&s->mscm, NULL, &s32k389_mscm_ops, s,
                          "s32k389.mscm", S32K3_MSCM_SIZE);
    memory_region_add_subregion_overlap(system_memory, S32K3_MSCM_BASE,
                                        &s->mscm, 2);
    // Generic stub for FIRC/FXOSC/MC_CGM range (0x402D0000-0x402DBFFF, 48KB).
    // Still needs _overlap since it sits inside the 16MiB catch-all above.
    memory_region_init_io(&s->clkgen_stub, NULL, &s32k389_clkgen_ops, s,
                          "s32k389.clkgen_stub", S32K3_CLKGEN_STUB_SIZE);
    memory_region_add_subregion_overlap(system_memory, S32K3_CLKGEN_STUB_BASE,
                                        &s->clkgen_stub, 1);
    // Real MC_ME peripheral (0x402DC000-0x402DFFFF, 16KB) - immediately
    // follows the clkgen stub with no overlap between the two of them, but
    // still needs _overlap against the 16MiB catch-all above.
    memory_region_init_io(&s->mc_me, NULL, &s32k389_mc_me_ops, s,
                          "s32k389.mc_me", S32K3_MC_ME_SIZE);
    memory_region_add_subregion_overlap(system_memory, S32K3_MC_ME_BASE,
                                        &s->mc_me, 1);

    // STCU2 (Self-Test Control Unit) minimal stub - see S32K3_STCU2_BASE
    // comment in the header. UNVERIFIED PLACEHOLDER base address.
    memory_region_init_io(&s->stcu2, NULL, &s32k389_stcu2_ops, s,
                          "s32k389.stcu2", S32K3_STCU2_SIZE);
    memory_region_add_subregion_overlap(system_memory, S32K3_STCU2_BASE,
                                        &s->stcu2, 1);

    // Enabling semihosting for guest BKPT operations
    qemu_semihosting_enable();

    // Load firmware - FLASH_SIZE covers the full 12MB contiguous flash
    // region (flash0-flash7), not just the first block, since firmware can
    // legitimately span multiple physical flash blocks.
    armv7m_load_kernel(s->armv7m.cpu, machine->kernel_filename, INT_CODE_FLASH0_BASE, FLASH_SIZE);

    // Cores 1-3 (CM7_1/CM7_2/CM7_3) - see S32K389_NUM_CORES comment in
    // the header. Each gets its own private ITCM/DTCM and its own
    // qemu_register_reset() handler; they all share the same flash image
    // core 0 just loaded above.
    s32k389_init_extra_core(s, system_memory, &s->core1, &s->core1_mem,
                            &s->core1_itcm, &s->core1_dtcm,
                            &s->core1_dtcm_stack, "core1", 1);
    s32k389_init_extra_core(s, system_memory, &s->core2, &s->core2_mem,
                            &s->core2_itcm, &s->core2_dtcm,
                            &s->core2_dtcm_stack, "core2", 2);
    s32k389_init_extra_core(s, system_memory, &s->core3, &s->core3_mem,
                            &s->core3_itcm, &s->core3_dtcm,
                            &s->core3_dtcm_stack, "core3", 3);
}
 
static void s32k389_class_init(ObjectClass* oc, const void* data) {
    MachineClass* mc = MACHINE_CLASS(oc);
    mc->desc = "NXP S32K389 Development Board (Cortex-M7)";
    mc->init = s32k389_init;
    /* 4 Cortex-M7 cores are unconditionally created in s32k389_init()
     * (not driven by -smp) - see S32K389_NUM_CORES in the header. These
     * fields still must reflect the true CPU count: TCG sizes its
     * per-thread context pool from machine->smp.max_cpus at startup
     * regardless of how the CPU objects were created, and leaving this
     * at 1 causes "tcg_register_thread: assertion failed: (n <
     * tcg_max_ctxs)" once cores 1-3 spin up their own TCG threads. */
    mc->default_cpus = S32K389_NUM_CORES;
    mc->min_cpus = S32K389_NUM_CORES;
    mc->max_cpus = S32K389_NUM_CORES;
    mc->default_ram_size = SRAM_SIZE;
}
 
static void s32k389_instance_init(Object *obj)
{
    S32K389State *s = S32K389(obj);
 
    /* S32K389_CAN_COUNT is 12 (vs. 6 on the earlier S32K388-derived model),
     * so register a link property "canbusN" for each of the 12 instances. */
    for (int i = 0; i < S32K389_CAN_COUNT; i++) {
        g_autofree char *prop_name = g_strdup_printf("canbus%d", i);
        object_property_add_link(obj, prop_name, TYPE_CAN_BUS,
                                 (Object **)&s->canbus[i],
                                 object_property_allow_set_link, 0);
    }
}
 
static const TypeInfo s32k389_type = {
    .name = TYPE_S32K389,
    .parent = TYPE_MACHINE,
    .instance_size = sizeof(S32K389State),
    .instance_init = s32k389_instance_init,
    .class_init = s32k389_class_init,
    .interfaces = arm_machine_interfaces,
};
 
// Register machine type
static void s32k389_machine_init(void) {
    qemu_log_mask(CPU_LOG_INT, "Registering S32K389 machine type\n");
    type_register_static(&s32k389_type);
}
 
type_init(s32k389_machine_init);
 
