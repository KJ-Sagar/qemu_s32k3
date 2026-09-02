/*
 * NXP S32K3xx Enhanced Modular IO Subsystem (eMIOS) Emulation
 *
 * Register map and bit definitions verified against the S32K3xx Reference
 * Manual, Rev. 11 (2025-07-11), Chapter 63 "Enhanced Modular IO Subsystem
 * (eMIOS)" (manual pages 2612-2698, register descriptions 2666-2703).
 * 3 instances on S32K389: eMIOS_0 (0x4008_8000), eMIOS_1 (0x4008_C000),
 * eMIOS_2 (0x4009_0000), each with 24 Unified Channels (UC).
 *
 * Scope: eMIOS has ~25 UC operating submodes (GPIO, SAIC, SAOC, IPWM, IPM,
 * DAOC, PEC, MC, MCB, OPWFMB, OPWMCB, OPWMB, OPWMT) selected by C[MODE],
 * several counter-bus routing options (C[BSL]), and per-channel double
 * buffering (A/ALTA shadow registers) - modeling every submode bit-exactly
 * would be disproportionate to what's testable in emulation (there is no
 * physical output pin or external edge source wired to anything in this
 * machine model). This implementation is "functional where practical":
 *   - MCR (module config incl. global prescaler), GFLAG (OR of all channel
 *     FLAG bits), OUDIS/UCDIS are real read/write registers.
 *   - Each UC's A/B/CNT/C/S/ALTA/C2 registers are real storage with real
 *     W1C semantics on S[FLAG]/S[OVR]/S[OVFL].
 *   - When a channel is configured for an autonomous counter-driven mode
 *     (MC, MCB, SAOC, DAOC, OPWFMB/OPWMCB/OPWMB, OPWMT - see
 *     s32k3_emios_mode_is_counted() in the .c file) AND C[BSL] selects the
 *     internal counter (0b11) AND C[UCPREN] is set, CNTn free-runs on a
 *     QEMU timer at the derived module-clock/prescaler rate, wraps/clears
 *     on a match against An, and sets S[FLAG] (raising the shared instance
 *     IRQ if C[FEN] is set) on every match against A or B. This is a
 *     deliberate simplification of the distinct MC/MCB/DAOC/OPWx submodes
 *     (e.g. true up/down triangle counting, dead-time insertion, and
 *     A/ALTA double buffering are not separately modeled) but gives real,
 *     observable periodic timer/PWM-flag behavior for firmware polling or
 *     IRQ-driven use, which is what these modes exist for.
 *   - Input-capture-only modes (GPIO in, SAIC, IPM, PEC) and any channel
 *     whose C[BSL] selects an external counter bus (A-F, shared with other
 *     channels) stay inert: there is no modeled input pin or cross-channel
 *     counter-bus routing to drive them from in this machine.
 *   - The eMIOS module clock rate used to derive counter tick timing is
 *     assumed at 80 MHz (a typical S32K3xx peripheral/AIPS bus clock
 *     configuration) - this has NOT been verified against a specific
 *     clock-tree chapter/value in the manual, so treat exact PWM
 *     frequency/period timing as approximate.
 *   - Per-channel interrupt routing: the manual states interrupt vector
 *     assignment is in a separate interrupt-map spreadsheet not provided.
 *     This model exposes ONE shared IRQ line per eMIOS instance (an OR of
 *     all 24 channels' FLAG&FEN conditions, mirroring GFLAG) rather than
 *     24 individual IRQ lines, as a documented simplification pending that
 *     spreadsheet - UNVERIFIED PLACEHOLDER, see s32k389.h IRQ numbers.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#ifndef HW_TIMER_S32K3_EMIOS_H
#define HW_TIMER_S32K3_EMIOS_H

#include "hw/core/sysbus.h"
#include "qemu/timer.h"
#include "qom/object.h"

#define S32K3_EMIOS_NUM_CHANNELS 24

/* Global registers (manual section 63.8.6.1, "eMIOS memory map") */
#define S32K3_EMIOS_MCR    0x00
#define S32K3_EMIOS_GFLAG  0x04
#define S32K3_EMIOS_OUDIS  0x08
#define S32K3_EMIOS_UCDIS  0x0C

/* Per-channel UC registers: base = 0x20 + n * 0x20, n = 0..23
 * (manual sections 63.8.6.6 - 63.8.6.12) */
#define S32K3_EMIOS_UC_STRIDE 0x20
#define S32K3_EMIOS_UC_BASE   0x20
#define S32K3_EMIOS_A_OFF     0x00
#define S32K3_EMIOS_B_OFF     0x04
#define S32K3_EMIOS_CNT_OFF   0x08
#define S32K3_EMIOS_C_OFF     0x0C
#define S32K3_EMIOS_S_OFF     0x10
#define S32K3_EMIOS_ALTA_OFF  0x14
#define S32K3_EMIOS_C2_OFF    0x18

#define S32K3_EMIOS_REGS_MEM_SIZE \
    (S32K3_EMIOS_UC_BASE + S32K3_EMIOS_NUM_CHANNELS * S32K3_EMIOS_UC_STRIDE)

/* MCR (Module Configuration, offset 0x00) - manual section 63.8.6.2 */
#define S32K3_EMIOS_MCR_MDIS   BIT(30)
#define S32K3_EMIOS_MCR_FRZ    BIT(29)
#define S32K3_EMIOS_MCR_GTBE   BIT(28)
#define S32K3_EMIOS_MCR_GPREN  BIT(26)
#define S32K3_EMIOS_MCR_GPRE_SHIFT 8
#define S32K3_EMIOS_MCR_GPRE_MASK  (0xFFu << S32K3_EMIOS_MCR_GPRE_SHIFT)

/* Cn (UC Control, offset 0x0C + n*0x20) - manual section 63.8.6.9 */
#define S32K3_EMIOS_C_FREN       BIT(31)
#define S32K3_EMIOS_C_ODIS       BIT(30)
#define S32K3_EMIOS_C_ODISSL_SHIFT 28
#define S32K3_EMIOS_C_ODISSL_MASK  (0x3u << S32K3_EMIOS_C_ODISSL_SHIFT)
#define S32K3_EMIOS_C_UCPRE_SHIFT  26
#define S32K3_EMIOS_C_UCPRE_MASK   (0x3u << S32K3_EMIOS_C_UCPRE_SHIFT)
#define S32K3_EMIOS_C_UCPREN     BIT(25)
#define S32K3_EMIOS_C_DMA        BIT(24)
#define S32K3_EMIOS_C_IF_SHIFT   19
#define S32K3_EMIOS_C_IF_MASK    (0xFu << S32K3_EMIOS_C_IF_SHIFT)
#define S32K3_EMIOS_C_FCK        BIT(18)
#define S32K3_EMIOS_C_FEN        BIT(17)
#define S32K3_EMIOS_C_FORCMA     BIT(13)
#define S32K3_EMIOS_C_FORCMB     BIT(12)
#define S32K3_EMIOS_C_BSL_SHIFT  9
#define S32K3_EMIOS_C_BSL_MASK   (0x3u << S32K3_EMIOS_C_BSL_SHIFT)
#define S32K3_EMIOS_C_BSL_INTERNAL 0x3u
#define S32K3_EMIOS_C_EDSEL      BIT(8)
#define S32K3_EMIOS_C_EDPOL      BIT(7)
#define S32K3_EMIOS_C_MODE_MASK  0x7Fu

/* MODE field values (Table 421) that this model treats specially */
#define S32K3_EMIOS_MODE_GPIO_IN  0x00
#define S32K3_EMIOS_MODE_GPIO_OUT 0x01
#define S32K3_EMIOS_MODE_SAIC     0x02
#define S32K3_EMIOS_MODE_SAOC     0x03
#define S32K3_EMIOS_MODE_IPWM     0x04
#define S32K3_EMIOS_MODE_IPM      0x05
#define S32K3_EMIOS_MODE_DAOC_B   0x06
#define S32K3_EMIOS_MODE_DAOC_AB  0x07
#define S32K3_EMIOS_MODE_OPWMT    0x26

/* Sn (UC Status, offset 0x10 + n*0x20) - manual section 63.8.6.10 */
#define S32K3_EMIOS_S_OVR   BIT(31) /* W1C */
#define S32K3_EMIOS_S_OVFL  BIT(15) /* W1C */
#define S32K3_EMIOS_S_UCIN  BIT(2)
#define S32K3_EMIOS_S_UCOUT BIT(1)
#define S32K3_EMIOS_S_FLAG  BIT(0) /* W1C */

/* Data fields (A/B/CNT) are 24 bits wide per manual section 63.8.6 intro */
#define S32K3_EMIOS_DATA_MASK 0x00FFFFFFu

/* Assumed eMIOS module clock - see scope note above: NOT verified against
 * a specific clock-tree value in the manual. */
#define S32K3_EMIOS_MODULE_CLK_HZ 80000000u

#define TYPE_S32K3_EMIOS "s32k3-emios"
OBJECT_DECLARE_SIMPLE_TYPE(S32K3EmiosState, S32K3_EMIOS)

typedef struct S32K3EmiosChannel {
    uint32_t a;
    uint32_t b;
    uint32_t cnt;
    uint32_t c;
    uint32_t s;
    uint32_t alta;
    uint32_t c2;

    /* Runtime state for the free-running-counter simplification (see
     * scope note above): epoch_ns is the QEMU_CLOCK_VIRTUAL time at which
     * the live counter value was last known to be 0 (mod period); "timer"
     * fires at the next A-match instant and reschedules itself. */
    int64_t epoch_ns;
    QEMUTimer *timer;
    struct S32K3EmiosState *owner;
    int index;
} S32K3EmiosChannel;

struct S32K3EmiosState {
    SysBusDevice parent_obj;

    MemoryRegion iomem;
    qemu_irq irq; /* shared instance IRQ - see scope note re: interrupt map */

    uint32_t instance_id;

    uint32_t mcr;
    uint32_t oudis;
    uint32_t ucdis;

    S32K3EmiosChannel ch[S32K3_EMIOS_NUM_CHANNELS];
};

#endif /* HW_TIMER_S32K3_EMIOS_H */
