/*
 * NXP S32K3xx Synchronous Audio Interface (SAI) - Chapter 74
 *
 * Scope notes:
 *  - S32K389 has 2 instances: SAI_0 (base 0x4036C000, 4 data lines wired in
 *    the register map, PARAM reset 0x0004_0304) and SAI_1 (base
 *    0x404DC000, 1 data line, PARAM reset 0x0004_0301). Per Table 547 of
 *    the reference manual, only 1 channel/data-line is actually used in
 *    this chip's configuration even though SAI_0's register map exposes
 *    TDR0-3/TFR0-3/RDR0-3/RFR0-3; all 4 slots are modeled generically for
 *    both instances (harmless - unused slots on SAI_1 simply go unused).
 *  - TX path is genuinely functional: TDR writes push into a real
 *    circular FIFO (depth = 2^FIFO from PARAM, i.e. 8 words), FRF/FWF
 *    flags are computed live from FIFO occupancy vs the TFW watermark,
 *    and a QEMU timer drains the FIFO at a rate derived from TCR2[DIV]
 *    to produce genuine underflow (FEF) behavior once TE is enabled with
 *    an empty FIFO - not just a stub.
 *  - The drain-rate calculation assumes the audio MCLK is 24.576 MHz,
 *    which is the "Master Clock Frequency" documented in Table 547 for
 *    this chip's SAI configuration (not a guess, unlike the eMIOS clock
 *    assumption) and assumes 32 bits/word, since decoding the exact
 *    frame/word-width fields (TCR4/TCR5) precisely is not required to
 *    demonstrate correct FIFO/flag/interrupt semantics.
 *  - RX path is structurally complete (RCSR/RCR1-5/RDR/RFR/RMR all
 *    readable/writable with correct reset values) but there is no
 *    external audio source wired up in this model, so the RX FIFO
 *    genuinely stays empty - matching real hardware behavior with an
 *    unconnected/idle input, rather than faking loopback data that would
 *    not occur on real silicon.
 */
#ifndef HW_AUDIO_S32K3_SAI_H
#define HW_AUDIO_S32K3_SAI_H

#include "hw/core/sysbus.h"
#include "qom/object.h"

#define TYPE_S32K3_SAI "s32k3-sai"
OBJECT_DECLARE_SIMPLE_TYPE(S32K3SaiState, S32K3_SAI)

#define S32K3_SAI_NUM_DATALINE 4
#define S32K3_SAI_FIFO_DEPTH   8
#define S32K3_SAI_FIFO_DEPTH_LOG2 3

#define S32K3_SAI_MEM_SIZE 0x100

#define S32K3_SAI_VERID 0x00
#define S32K3_SAI_PARAM 0x04
#define S32K3_SAI_TCSR  0x08
#define S32K3_SAI_TCR1  0x0C
#define S32K3_SAI_TCR2  0x10
#define S32K3_SAI_TCR3  0x14
#define S32K3_SAI_TCR4  0x18
#define S32K3_SAI_TCR5  0x1C
#define S32K3_SAI_TDR0  0x20
#define S32K3_SAI_TDR3  0x2C
#define S32K3_SAI_TFR0  0x40
#define S32K3_SAI_TFR3  0x4C
#define S32K3_SAI_TMR   0x60
#define S32K3_SAI_RCSR  0x88
#define S32K3_SAI_RCR1  0x8C
#define S32K3_SAI_RCR2  0x90
#define S32K3_SAI_RCR3  0x94
#define S32K3_SAI_RCR4  0x98
#define S32K3_SAI_RCR5  0x9C
#define S32K3_SAI_RDR0  0xA0
#define S32K3_SAI_RDR3  0xAC
#define S32K3_SAI_RFR0  0xC0
#define S32K3_SAI_RFR3  0xCC
#define S32K3_SAI_RMR   0xE0

#define S32K3_SAI_VERID_RESET 0x03010000u

/* xCSR bit layout (identical for TCSR and RCSR) */
#define S32K3_SAI_XCSR_TE_RE   BIT(31)
#define S32K3_SAI_XCSR_DBGE    BIT(29)
#define S32K3_SAI_XCSR_BCE     BIT(28)
#define S32K3_SAI_XCSR_FR      BIT(25)
#define S32K3_SAI_XCSR_SR      BIT(24)
#define S32K3_SAI_XCSR_WSF     BIT(20)
#define S32K3_SAI_XCSR_SEF     BIT(19)
#define S32K3_SAI_XCSR_FEF     BIT(18)
#define S32K3_SAI_XCSR_FWF     BIT(17)
#define S32K3_SAI_XCSR_FRF     BIT(16)
#define S32K3_SAI_XCSR_W1C_MASK (S32K3_SAI_XCSR_WSF | S32K3_SAI_XCSR_SEF | \
                                  S32K3_SAI_XCSR_FEF)
#define S32K3_SAI_XCSR_WSIE    BIT(12)
#define S32K3_SAI_XCSR_SEIE    BIT(11)
#define S32K3_SAI_XCSR_FEIE    BIT(10)
#define S32K3_SAI_XCSR_FWIE    BIT(9)
#define S32K3_SAI_XCSR_FRIE    BIT(8)
#define S32K3_SAI_XCSR_FWDE    BIT(1)
#define S32K3_SAI_XCSR_FRDE    BIT(0)

#define S32K3_SAI_XCR1_TFW_MASK 0x7u

#define S32K3_SAI_XCR2_DIV_MASK 0xFFu

#define S32K3_SAI_AUDIO_MCLK_HZ 24576000u /* Table 547: 24.576 MHz MCLK */

typedef struct S32K3SaiFifo {
    uint32_t data[S32K3_SAI_FIFO_DEPTH];
    /* wp/rp range over 0..2*DEPTH-1; MSB-compare distinguishes full/empty,
     * matching the real WFP/RFP pointer scheme described in the manual. */
    uint8_t wp, rp;
} S32K3SaiFifo;

typedef struct S32K3SaiState {
    SysBusDevice parent_obj;

    MemoryRegion iomem;
    qemu_irq irq;

    uint32_t param_reset; /* per-instance PARAM reset value (set via prop) */

    uint32_t tcsr, tcr1, tcr2, tcr3, tcr4, tcr5, tmr;
    uint32_t rcsr, rcr1, rcr2, rcr3, rcr4, rcr5, rmr;

    S32K3SaiFifo tx_fifo[S32K3_SAI_NUM_DATALINE];
    S32K3SaiFifo rx_fifo[S32K3_SAI_NUM_DATALINE];

    QEMUTimer *tx_drain_timer;
} S32K3SaiState;

#endif
