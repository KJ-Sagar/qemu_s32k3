/*
 * NXP S32K3xx Software Watchdog Timer (SWT) Emulation
 *
 * Register map and bit definitions verified against the S32K3xx Reference
 * Manual, Rev. 11 (2025-07-11), Chapter 66 "Software Watchdog Timer (SWT)"
 * (manual pages 2802-2829). S32K389 has 4 SWT instances, one per Cortex-M7
 * core (manual Table 430 "SWT instances"): SWT_0 (0x4027_0000), SWT_1
 * (0x4046_C000), SWT_2 (0x4047_0000), SWT_3 (0x4007_0000).
 *
 * This model implements a real countdown: the counter clock is SIRC
 * (32 kHz, manual Table 431), so TO (Timeout, manual 66.6.4) counts in
 * 1/32768 s ticks. When enabled (CR[WEN]=1) and not serviced before the
 * timer reaches TO, the timeout genuinely fires: it raises the IRQ (in
 * ITR/interrupt-then-reset mode, per manual 66.6.2 CR[ITR]) and/or invokes
 * QEMU's generic watchdog_perform_action() (the same mechanism used by
 * other watchdog models such as hw/watchdog/wdt_i6300esb.c), respecting
 * the user's "-watchdog-action" choice. Writing the fixed service sequence
 * (0xA602 then 0xB480 to SR, manual 66.6.6) reloads the counter.
 *
 * Simplifications: Keyed service mode (CR[SMD]=01, manual 66.3.3 "Service
 * key generation") is not implemented - any two SR writes are accepted as
 * a service in that mode, logged as unimplemented. Window-mode
 * (CR[WND]/WN) early-service violations are stored/read back but not
 * enforced as a bus-error condition. STP (stop-mode freeze) and FRZ
 * (debug-mode freeze) are stored but have no behavioral effect, since this
 * machine model does not implement chip stop/standby modes or a
 * core-halt notification hook.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#ifndef HW_WATCHDOG_S32K3_SWT_H
#define HW_WATCHDOG_S32K3_SWT_H

#include "hw/core/sysbus.h"
#include "qemu/timer.h"
#include "qom/object.h"

/* SWT register offsets (manual section 66.6.1, "SWT memory map") */
#define S32K3_SWT_CR   0x00
#define S32K3_SWT_IR   0x04
#define S32K3_SWT_TO   0x08
#define S32K3_SWT_WN   0x0C
#define S32K3_SWT_SR   0x10
#define S32K3_SWT_CO   0x14
#define S32K3_SWT_SK   0x18
#define S32K3_SWT_RRR  0x1C

#define S32K3_SWT_REGS_MEM_SIZE 0x20

/* CR (Control, offset 0x00) - manual section 66.6.2 */
#define S32K3_SWT_CR_WEN        BIT(0)
#define S32K3_SWT_CR_FRZ        BIT(1)
#define S32K3_SWT_CR_STP        BIT(2)
#define S32K3_SWT_CR_SLK        BIT(4)
#define S32K3_SWT_CR_HLK        BIT(5)
#define S32K3_SWT_CR_ITR        BIT(6)
#define S32K3_SWT_CR_WND        BIT(7)
#define S32K3_SWT_CR_RIA        BIT(8)
#define S32K3_SWT_CR_SMD_SHIFT  9
#define S32K3_SWT_CR_SMD_MASK   (0x3 << S32K3_SWT_CR_SMD_SHIFT)
#define S32K3_SWT_CR_RESET      0xFF00010Au /* manual 66.6.1: all MAPn=1, RIA=1, WEN=0 */
#define S32K3_SWT_CR_LOCKED     (S32K3_SWT_CR_HLK | S32K3_SWT_CR_SLK)

/* IR (Interrupt, offset 0x04) - manual section 66.6.3 */
#define S32K3_SWT_IR_TIF  BIT(0) /* W1C */

/* SR (Service, offset 0x10) - manual section 66.6.6 */
#define S32K3_SWT_SERVICE_KEY1 0xA602
#define S32K3_SWT_SERVICE_KEY2 0xB480
#define S32K3_SWT_UNLOCK_KEY1  0xC520
#define S32K3_SWT_UNLOCK_KEY2  0xD928

/* SIRC-derived counter clock, per manual Table 431 ("Clock Source: SIRC
 * (32K)"). */
#define S32K3_SWT_COUNTER_HZ 32768

#define TYPE_S32K3_SWT "s32k3-swt"
OBJECT_DECLARE_SIMPLE_TYPE(S32K3SWTState, S32K3_SWT)

struct S32K3SWTState {
    SysBusDevice parent_obj;

    MemoryRegion iomem;
    qemu_irq irq;
    QEMUTimer *timer;

    uint32_t instance_id;

    uint32_t cr;
    uint32_t ir;
    uint32_t to;
    uint32_t wn;
    uint32_t co_latched; /* latched counter value while WEN=0 (manual 66.6.7) */
    uint32_t sk;

    uint16_t service_seen_first; /* 0 = none pending, else first key word seen */
    bool timed_out_once;         /* for CR[ITR]: first timeout -> IRQ, second -> reset */
};

#endif /* HW_WATCHDOG_S32K3_SWT_H */
