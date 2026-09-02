/*
 * NXP S32K3xx Enhanced Direct Memory Access (eDMA) Emulation
 *
 * Register map and bit definitions verified against the S32K3xx Reference
 * Manual, Rev. 11 (2025-07-11), Chapter 15 "Enhanced Direct Memory Access
 * (eDMA)" (manual pages 530-633; register descriptions 551-666). Manual
 * section 15.1.1: "This chip has one instance of eDMA without any
 * lockstep" with 32 channels (section 15.1.2, Table 54).
 *
 * Two separate MMIO regions, matching the manual's memory maps exactly:
 *   - Management page (section 15.6.1.1), base 0x4020_C000: global CSR,
 *     read-only ES/INT/HRS, and the 32 CHn_GRPRI registers.
 *   - TCD/channel page (section 15.6.2.1), base 0x4021_0000: each of the
 *     32 channels gets its own 0x4000-byte (16 KB) window containing
 *     CHn_CSR/ES/INT/SBR/PRI at 0x00-0x13 followed by the classic 32-byte
 *     eDMA transfer control descriptor (TCDn_SADDR..BITER) at 0x20-0x3F.
 *
 * Scope - this is a large, feature-rich engine (channel-to-channel
 * linking, scatter/gather, minor-loop address offsets, bandwidth control,
 * modulo addressing, hardware request signaling from every other
 * peripheral). This model is "functional where practical" for the
 * software-initiated single-shot transfer case, which is what firmware
 * bring-up/testing actually exercises:
 *   - A real 32-byte TCD is stored per channel with real field decode
 *     (SADDR/SOFF/ATTR/NBYTES/SLAST/DADDR/DOFF/CITER/DLAST_SGA/CSR/BITER).
 *   - Writing TCDn_CSR[START]=1 synchronously performs the ENTIRE major
 *     loop (CITER minor-loop iterations of NBYTES bytes each) right away,
 *     using QEMU's system address space for the actual reads/writes -
 *     this really moves guest memory/MMIO data, unlike a no-op stub.
 *     SSIZE/DSIZE are honored for the common SSIZE==DSIZE case (8/16/32
 *     bit CPU-supported sizes); on any other combination the model still
 *     moves the correct total byte count but logs LOG_UNIMP for the
 *     unmodeled size-conversion packing behavior.
 *   - NBYTES==0 or a non-multiple-of-size NBYTES sets CHn_ES[NCE]/[ERR]
 *     (and the management page's read-only ES mirror) exactly like real
 *     hardware, and skips the transfer.
 *   - CHn_CSR[DONE], TCDn_CSR[INTMAJOR] -> CHn_INT[INT] -> the channel's
 *     IRQ line, and TCDn_CSR[DREQ] auto-clearing CHn_CSR[ERQ] are real.
 *   - NOT modeled (stored as plain read/write state only, with LOG_UNIMP
 *     if a guest tries to use them): hardware-triggered service requests
 *     (no peripheral in this machine drives an eDMA request line yet -
 *     CHn_CSR[ERQ]/HRS are inert), scatter/gather (TCDn_CSR[ESG]),
 *     channel-to-channel linking (TCDn_CSR[MAJORELINK], CITER/BITER
 *     [ELINK]), minor-loop address offsets (NBYTES_MLOFFYES format - all
 *     NBYTES writes are treated as the plain MLOFFNO 32-bit byte count),
 *     modulo addressing (ATTR[SMOD]/[DMOD]), bandwidth throttling (BWC),
 *     channel preemption/arbitration (CHn_PRI/CHn_GRPRI/CSR[ERCA] are
 *     just storage - since transfers complete synchronously there is
 *     never real contention to arbitrate), and the separate summed
 *     "management page" error interrupt (only the per-channel INT-based
 *     IRQ is wired, which the manual states already OR's in enabled
 *     per-channel errors).
 *   - Per-channel IRQ numbers are an UNVERIFIED PLACEHOLDER (interrupt
 *     map spreadsheet not available) - see the S32K3_EDMA_CHn_IRQ
 *     comments in s32k389.h.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#ifndef HW_DMA_S32K3_EDMA_H
#define HW_DMA_S32K3_EDMA_H

#include "hw/core/sysbus.h"
#include "qom/object.h"

#define S32K3_EDMA_NUM_CHANNELS 32

/* ---- Management page (base 0x4020C000) - section 15.6.1 ---- */
#define S32K3_EDMA_MGMT_CSR   0x00
#define S32K3_EDMA_MGMT_ES    0x04
#define S32K3_EDMA_MGMT_INT   0x08
#define S32K3_EDMA_MGMT_HRS   0x0C
#define S32K3_EDMA_MGMT_GRPRI(n) (0x100 + (n) * 4) /* n = 0..31 */
#define S32K3_EDMA_MGMT_REGS_MEM_SIZE 0x180

#define S32K3_EDMA_MGMT_CSR_GMRC  BIT(7)
#define S32K3_EDMA_MGMT_CSR_GCLC  BIT(6)
#define S32K3_EDMA_MGMT_CSR_HALT  BIT(5)
#define S32K3_EDMA_MGMT_CSR_HAE   BIT(4)
#define S32K3_EDMA_MGMT_CSR_ERCA  BIT(2)
#define S32K3_EDMA_MGMT_CSR_EDBG  BIT(1)
#define S32K3_EDMA_MGMT_CSR_RW_MASK \
    (S32K3_EDMA_MGMT_CSR_GMRC | S32K3_EDMA_MGMT_CSR_GCLC | \
     S32K3_EDMA_MGMT_CSR_HALT | S32K3_EDMA_MGMT_CSR_HAE | \
     S32K3_EDMA_MGMT_CSR_ERCA | S32K3_EDMA_MGMT_CSR_EDBG)

#define S32K3_EDMA_MGMT_ES_VLD_SHIFT    31
#define S32K3_EDMA_MGMT_ES_ERRCHN_SHIFT 24
#define S32K3_EDMA_MGMT_ES_ERRCHN_MASK  (0x1Fu << S32K3_EDMA_MGMT_ES_ERRCHN_SHIFT)

/* ---- TCD/channel page (base 0x40210000) - section 15.6.2 ----
 * Per-channel window stride is 0x4000 bytes; within a channel's window: */
#define S32K3_EDMA_CH_STRIDE 0x4000

#define S32K3_EDMA_CH_CSR      0x00
#define S32K3_EDMA_CH_ES       0x04
#define S32K3_EDMA_CH_INT      0x08
#define S32K3_EDMA_CH_SBR      0x0C
#define S32K3_EDMA_CH_PRI      0x10
#define S32K3_EDMA_TCD_SADDR      0x20
#define S32K3_EDMA_TCD_SOFF       0x24 /* 16-bit signed */
#define S32K3_EDMA_TCD_ATTR       0x26 /* 16-bit */
#define S32K3_EDMA_TCD_NBYTES     0x28 /* MLOFFNO format only - see scope note */
#define S32K3_EDMA_TCD_SLAST      0x2C
#define S32K3_EDMA_TCD_DADDR      0x30
#define S32K3_EDMA_TCD_DOFF       0x34 /* 16-bit signed */
#define S32K3_EDMA_TCD_CITER      0x36 /* 16-bit, ELINKNO format only */
#define S32K3_EDMA_TCD_DLAST_SGA  0x38
#define S32K3_EDMA_TCD_CSR        0x3C /* 16-bit */
#define S32K3_EDMA_TCD_BITER      0x3E /* 16-bit, ELINKNO format only */

#define S32K3_EDMA_CH_REGS_MEM_SIZE \
    (S32K3_EDMA_NUM_CHANNELS * S32K3_EDMA_CH_STRIDE)

/* CHn_CSR (offset 0x00) - manual section 15.6.2.2 */
#define S32K3_EDMA_CH_CSR_ACTIVE BIT(31) /* RO, always reads 0 - see scope note */
#define S32K3_EDMA_CH_CSR_DONE   BIT(30) /* W1C */
#define S32K3_EDMA_CH_CSR_EBW    BIT(3)
#define S32K3_EDMA_CH_CSR_EEI    BIT(2)
#define S32K3_EDMA_CH_CSR_EARQ   BIT(1)
#define S32K3_EDMA_CH_CSR_ERQ    BIT(0)

/* CHn_ES (offset 0x04) - manual section 15.6.2.3 */
#define S32K3_EDMA_CH_ES_ERR BIT(31)
#define S32K3_EDMA_CH_ES_SAE BIT(7)
#define S32K3_EDMA_CH_ES_SOE BIT(6)
#define S32K3_EDMA_CH_ES_DAE BIT(5)
#define S32K3_EDMA_CH_ES_DOE BIT(4)
#define S32K3_EDMA_CH_ES_NCE BIT(3)
#define S32K3_EDMA_CH_ES_SGE BIT(2)
#define S32K3_EDMA_CH_ES_SBE BIT(1)
#define S32K3_EDMA_CH_ES_DBE BIT(0)
#define S32K3_EDMA_CH_ES_W1C_MASK 0xFF

/* CHn_INT (offset 0x08) - manual section 15.6.2.4 */
#define S32K3_EDMA_CH_INT_INT BIT(0) /* W1C */

/* CHn_PRI (offset 0x10) - manual section 15.6.2.6 */
#define S32K3_EDMA_CH_PRI_ECP BIT(31)
#define S32K3_EDMA_CH_PRI_DPA BIT(30)
#define S32K3_EDMA_CH_PRI_APL_MASK 0x1F

/* TCDn_ATTR (offset 0x26) - manual section 15.6.2.9 */
#define S32K3_EDMA_ATTR_SMOD_SHIFT  11
#define S32K3_EDMA_ATTR_SSIZE_SHIFT 8
#define S32K3_EDMA_ATTR_SSIZE_MASK  (0x7u << S32K3_EDMA_ATTR_SSIZE_SHIFT)
#define S32K3_EDMA_ATTR_DMOD_SHIFT  3
#define S32K3_EDMA_ATTR_DSIZE_MASK  0x7u

/* TCDn_CSR (offset 0x3C) - manual section 15.6.2.18 */
#define S32K3_EDMA_TCD_CSR_BWC_SHIFT   14
#define S32K3_EDMA_TCD_CSR_MAJORLINKCH_SHIFT 8
#define S32K3_EDMA_TCD_CSR_MAJORLINKCH_MASK  (0x1Fu << S32K3_EDMA_TCD_CSR_MAJORLINKCH_SHIFT)
#define S32K3_EDMA_TCD_CSR_ESDA      BIT(7)
#define S32K3_EDMA_TCD_CSR_MAJORELINK BIT(5)
#define S32K3_EDMA_TCD_CSR_ESG       BIT(4)
#define S32K3_EDMA_TCD_CSR_DREQ      BIT(3)
#define S32K3_EDMA_TCD_CSR_INTHALF   BIT(2)
#define S32K3_EDMA_TCD_CSR_INTMAJOR  BIT(1)
#define S32K3_EDMA_TCD_CSR_START     BIT(0)

/* CITER/BITER ELINKNO format (offset 0x36 / 0x3E) - manual sections
 * 15.6.2.15/19. Bit 15 is ELINK; channel linking is not modeled (see
 * scope note), so this model only ever reads/writes the 15-bit count. */
#define S32K3_EDMA_ITER_ELINK BIT(15)
#define S32K3_EDMA_ITER_COUNT_MASK 0x7FFF

#define TYPE_S32K3_EDMA "s32k3-edma"
OBJECT_DECLARE_SIMPLE_TYPE(S32K3EdmaState, S32K3_EDMA)

typedef struct S32K3EdmaChannel {
    uint32_t csr;
    uint32_t es;
    uint32_t intr;
    uint32_t sbr;
    uint32_t pri;

    uint32_t saddr;
    uint32_t soff;     /* stored raw 16-bit; sign-extend on use */
    uint32_t attr;
    uint32_t nbytes;
    uint32_t slast;
    uint32_t daddr;
    uint32_t doff;     /* stored raw 16-bit; sign-extend on use */
    uint32_t citer;
    uint32_t dlast_sga;
    uint32_t tcd_csr;
    uint32_t biter;

    struct S32K3EdmaState *owner;
    int index;
} S32K3EdmaChannel;

struct S32K3EdmaState {
    SysBusDevice parent_obj;

    MemoryRegion mgmt_iomem;
    MemoryRegion ch_iomem;
    qemu_irq irq[S32K3_EDMA_NUM_CHANNELS];

    uint32_t mgmt_csr;
    uint32_t mgmt_es;
    uint32_t grpri[S32K3_EDMA_NUM_CHANNELS];

    S32K3EdmaChannel ch[S32K3_EDMA_NUM_CHANNELS];
};

#endif /* HW_DMA_S32K3_EDMA_H */
