/*
 * NXP S32K3xx Analog-to-Digital Converter (ADC) Emulation
 *
 * Register map and bit definitions verified against the S32K3xx Reference
 * Manual, Rev. 11 (2025-07-11), Chapter 60 "Analog-to-Digital Converter
 * (ADC)" (manual pages 2332-2494). 3 instances on S32K389: ADC_0
 * (0x400A_0000), ADC_1 (0x400A_4000), ADC_2 (0x400A_8000).
 *
 * Scope: this is one of the largest and most feature-rich peripherals on
 * the chip (precision/standard/external input groups, injected
 * conversions, DMA, analog watchdogs, presampling, self-test/calibration).
 * This model implements the part that matters for firmware reading a
 * "sensor" value - software-triggered normal conversions:
 *   - MCR/MSR (main config/status), ISR/IMR (top-level interrupt),
 *     CEOCFR0-2 (per-channel end-of-conversion flags), NCMR0-2 (which
 *     channels get converted).
 *   - The 3 channel groups' data registers: PCDR0-7 (Precision, 8 ch),
 *     ICDR0-23 (Standard, 24 ch - this is the group the datasheet's
 *     "3 x 24-channel" figure most likely refers to), ECDR0-31 (External,
 *     32 ch). Writing MCR[NSTART]=1 immediately ("instantly", no real
 *     conversion-time model) converts every channel enabled in the
 *     matching NCMR group and posts VALID + EOC/ECH, exactly like real
 *     hardware but without the clock-cycle delay.
 * Since there's no physical analog signal in emulation, every channel
 * converts to a fixed mid-scale 12-bit value (0x800) - there is no
 * mechanism here to feed a "real" sensor reading in. Injected conversions
 * (JCMR/JSTART), DMA requests, analog watchdogs, presampling, and
 * self-test/calibration registers are present as plain read/write storage
 * (so firmware probing/configuring them doesn't fault) but have no
 * behavioral effect - see s32k3_adc_reset() for their documented reset
 * values, taken directly from the manual's memory-map table.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#ifndef HW_ADC_S32K3_ADC_H
#define HW_ADC_S32K3_ADC_H

#include "hw/core/sysbus.h"
#include "qom/object.h"

/* Functional register offsets (manual section 60.6.2.1, "ADC memory map") */
#define S32K3_ADC_MCR      0x000
#define S32K3_ADC_MSR      0x004
#define S32K3_ADC_ISR      0x010
#define S32K3_ADC_CEOCFR0  0x014
#define S32K3_ADC_CEOCFR1  0x018
#define S32K3_ADC_CEOCFR2  0x01C
#define S32K3_ADC_IMR      0x020
#define S32K3_ADC_CIMR0    0x024
#define S32K3_ADC_CIMR1    0x028
#define S32K3_ADC_CIMR2    0x02C
#define S32K3_ADC_NCMR0    0x0A4
#define S32K3_ADC_NCMR1    0x0A8
#define S32K3_ADC_NCMR2    0x0AC
#define S32K3_ADC_PCDR(n)  (0x100 + (n) * 4)  /* n = 0..7 */
#define S32K3_ADC_ICDR(n)  (0x180 + (n) * 4)  /* n = 0..23 */
#define S32K3_ADC_ECDR(n)  (0x200 + (n) * 4)  /* n = 0..31 */

#define S32K3_ADC_NUM_PRECISION 8
#define S32K3_ADC_NUM_STANDARD  24
#define S32K3_ADC_NUM_EXTERNAL  32

#define S32K3_ADC_REGS_MEM_SIZE 0x3C0

/* MCR (Main Configuration, offset 0x000) - manual section 60.6.2.2 */
#define S32K3_ADC_MCR_PWDN        BIT(0)
#define S32K3_ADC_MCR_ABORT       BIT(6)  /* pulse, always reads 0 */
#define S32K3_ADC_MCR_ABORTCHAIN  BIT(7)  /* pulse, always reads 0 */
#define S32K3_ADC_MCR_JSTART      BIT(20) /* pulse */
#define S32K3_ADC_MCR_NSTART      BIT(24)
#define S32K3_ADC_MCR_MODE        BIT(29) /* 0 = single, 1 = continuous */
#define S32K3_ADC_MCR_RESET       0x00000001u

/* MSR (Main Status, offset 0x004) - manual section 60.6.2.3 */
#define S32K3_ADC_MSR_ADCSTATUS_IDLE BIT(0) /* 001b = Power Down, matches PWDN reset default */
#define S32K3_ADC_MSR_NSTART      BIT(24)
#define S32K3_ADC_MSR_CALIBRTD    BIT(31)

/* ISR (Interrupt Status, offset 0x010) - manual section 60.6.2.4 */
#define S32K3_ADC_ISR_ECH    BIT(0) /* W1C */
#define S32K3_ADC_ISR_EOC    BIT(1) /* W1C */
#define S32K3_ADC_ISR_JECH   BIT(2) /* W1C */
#define S32K3_ADC_ISR_JEOC   BIT(3) /* W1C */
#define S32K3_ADC_ISR_EOBCTU BIT(4) /* W1C */
#define S32K3_ADC_ISR_W1C_MASK 0x1F

/* IMR (Interrupt Mask, offset 0x020) - manual section 60.6.2.8 */
#define S32K3_ADC_IMR_MSKECH    BIT(0)
#define S32K3_ADC_IMR_MSKEOC    BIT(1)
#define S32K3_ADC_IMR_MSKJECH   BIT(2)
#define S32K3_ADC_IMR_MSKJEOC   BIT(3)
#define S32K3_ADC_IMR_MSKEOBCTU BIT(4)

/* *CDRn conversion data registers - manual section 60.6.2.34 (PCDR),
 * ICDR/ECDR follow the identical layout. */
#define S32K3_ADC_CDR_CDATA_MASK   0xFFFF
#define S32K3_ADC_CDR_RESULT_SHIFT 16
#define S32K3_ADC_CDR_RESULT_MASK  (0x3u << S32K3_ADC_CDR_RESULT_SHIFT)
#define S32K3_ADC_CDR_OVERW        BIT(18)
#define S32K3_ADC_CDR_VALID        BIT(19)

/* Fixed conversion result used for every channel (manual header comment:
 * no real analog input model exists, so every conversion returns the
 * 12-bit mid-scale code). */
#define S32K3_ADC_FIXED_SAMPLE 0x800

#define TYPE_S32K3_ADC "s32k3-adc"
OBJECT_DECLARE_SIMPLE_TYPE(S32K3ADCState, S32K3_ADC)

struct S32K3ADCState {
    SysBusDevice parent_obj;

    MemoryRegion iomem;
    qemu_irq irq;

    uint32_t instance_id;

    /* Generic backing store for the whole register file (0x000-0x3B7).
     * Registers with real behavior are intercepted explicitly in
     * s32k3_adc_read()/write(); everything else (self-test, calibration,
     * watchdogs, presampling, DMA config, injected-conversion config) is
     * plain storage so firmware read/modify/write sequences on those
     * registers behave sanely without faulting. */
    uint32_t regs[S32K3_ADC_REGS_MEM_SIZE / 4];
};

#endif /* HW_ADC_S32K3_ADC_H */
