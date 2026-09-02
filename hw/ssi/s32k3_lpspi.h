/*
 * NXP S32K3xx Low Power Serial Peripheral Interface (LPSPI) Emulation
 *
 * Register map and bit definitions verified against the S32K3xx Reference
 * Manual, Rev. 11 (2025-07-11), Chapter 70 "Low Power Serial Peripheral
 * Interface (LPSPI)" (manual pages 2867-2920).
 *
 * All six LPSPI instances (0-5) on S32K344/S32K388/S32K389 share the same
 * register map and a 4x32-bit TX and RX FIFO (Table 439 "LPSPI instances
 * configuration"). Only the number of Peripheral Chip Selects differs per
 * instance (Table 439: LPSPI0=8, LPSPI1=6, LPSPI2-5=4); that is modeled here
 * only as a cosmetic PARAM/PCS-count value, since guest firmware generally
 * only reads it for informational purposes.
 *
 * This model implements Controller (master) mode functionally: writes to
 * TDR are shifted out over a QEMU SSI bus via ssi_transfer() and the
 * response is captured into the RX FIFO, exactly like a real SPI transfer
 * would clock data in both directions simultaneously. Peripheral (target)
 * mode, the circular-FIFO feature, and multi-word (>32 bit) FRAMESZ
 * spanning are not modeled (SPDX comment blocks below call out each
 * simplification at the point it applies).
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#ifndef HW_SSI_S32K3_LPSPI_H
#define HW_SSI_S32K3_LPSPI_H

#include "hw/core/sysbus.h"
#include "hw/ssi/ssi.h"
#include "qom/object.h"

/* LPSPI register offsets (manual section 70.6.1.1, "LPSPI memory map") */
#define S32K3_LPSPI_VERID    0x00
#define S32K3_LPSPI_PARAM    0x04
#define S32K3_LPSPI_CR       0x10
#define S32K3_LPSPI_SR       0x14
#define S32K3_LPSPI_IER      0x18
#define S32K3_LPSPI_DER      0x1C
#define S32K3_LPSPI_CFGR0    0x20
#define S32K3_LPSPI_CFGR1    0x24
#define S32K3_LPSPI_DMR0     0x30
#define S32K3_LPSPI_DMR1     0x34
#define S32K3_LPSPI_CCR      0x40
#define S32K3_LPSPI_CCR1     0x44
#define S32K3_LPSPI_FCR      0x58
#define S32K3_LPSPI_FSR      0x5C
#define S32K3_LPSPI_TCR      0x60
#define S32K3_LPSPI_TDR      0x64
#define S32K3_LPSPI_RSR      0x70
#define S32K3_LPSPI_RDR      0x74
#define S32K3_LPSPI_RDROR    0x78

#define S32K3_LPSPI_REGS_MEM_SIZE 0x80

/* CR (Control, offset 0x10) - manual section 70.6.1.4 */
#define S32K3_LPSPI_CR_MEN    BIT(0)  /* Module Enable */
#define S32K3_LPSPI_CR_RST    BIT(1)  /* Software Reset */
#define S32K3_LPSPI_CR_DBGEN  BIT(3)  /* Debug Enable */
#define S32K3_LPSPI_CR_RTF    BIT(8)  /* Reset Transmit FIFO (self-clearing, always reads 0) */
#define S32K3_LPSPI_CR_RRF    BIT(9)  /* Reset Receive FIFO (self-clearing, always reads 0) */

/* SR (Status, offset 0x14) - manual section 70.6.1.5 */
#define S32K3_LPSPI_SR_TDF    BIT(0)  /* Transmit Data Flag */
#define S32K3_LPSPI_SR_RDF    BIT(1)  /* Receive Data Flag */
#define S32K3_LPSPI_SR_WCF    BIT(8)  /* Word Complete Flag (W1C) */
#define S32K3_LPSPI_SR_FCF    BIT(9)  /* Frame Complete Flag (W1C) */
#define S32K3_LPSPI_SR_TCF    BIT(10) /* Transfer Complete Flag (W1C) */
#define S32K3_LPSPI_SR_TEF    BIT(11) /* Transmit Error Flag (W1C) */
#define S32K3_LPSPI_SR_REF    BIT(12) /* Receive Error Flag (W1C) */
#define S32K3_LPSPI_SR_DMF    BIT(13) /* Data Match Flag (W1C) */
#define S32K3_LPSPI_SR_MBF    BIT(24) /* Module Busy Flag */
#define S32K3_LPSPI_SR_W1C_MASK (S32K3_LPSPI_SR_WCF | S32K3_LPSPI_SR_FCF | \
                                  S32K3_LPSPI_SR_TCF | S32K3_LPSPI_SR_TEF | \
                                  S32K3_LPSPI_SR_REF | S32K3_LPSPI_SR_DMF)
#define S32K3_LPSPI_SR_RESET  S32K3_LPSPI_SR_TDF /* TX FIFO empty at reset */

/* IER (Interrupt Enable, offset 0x18) - manual section 70.6.1.6 */
#define S32K3_LPSPI_IER_TDIE  BIT(0)
#define S32K3_LPSPI_IER_RDIE  BIT(1)
#define S32K3_LPSPI_IER_WCIE  BIT(8)
#define S32K3_LPSPI_IER_FCIE  BIT(9)
#define S32K3_LPSPI_IER_TCIE  BIT(10)
#define S32K3_LPSPI_IER_TEIE  BIT(11)
#define S32K3_LPSPI_IER_REIE  BIT(12)
#define S32K3_LPSPI_IER_DMIE  BIT(13)

/* CFGR1 (Configuration 1, offset 0x24) - manual section 70.6.1.9 */
#define S32K3_LPSPI_CFGR1_MASTER   BIT(0)  /* 1 = Controller mode, 0 = Peripheral mode */
#define S32K3_LPSPI_CFGR1_SAMPLE   BIT(1)
#define S32K3_LPSPI_CFGR1_AUTOPCS  BIT(2)
#define S32K3_LPSPI_CFGR1_NOSTALL  BIT(3)
#define S32K3_LPSPI_CFGR1_MATCFG_SHIFT 16
#define S32K3_LPSPI_CFGR1_MATCFG_MASK  (0x7 << S32K3_LPSPI_CFGR1_MATCFG_SHIFT)

/* TCR (Transmit Command, offset 0x60) - manual section 70.6.1.16 */
#define S32K3_LPSPI_TCR_FRAMESZ_MASK  0xFFF
#define S32K3_LPSPI_TCR_WIDTH_SHIFT   16
#define S32K3_LPSPI_TCR_WIDTH_MASK    (0x3 << S32K3_LPSPI_TCR_WIDTH_SHIFT)
#define S32K3_LPSPI_TCR_TXMSK         BIT(18)
#define S32K3_LPSPI_TCR_RXMSK         BIT(19)
#define S32K3_LPSPI_TCR_CONTC         BIT(20)
#define S32K3_LPSPI_TCR_CONT          BIT(21)
#define S32K3_LPSPI_TCR_BYSW          BIT(22)
#define S32K3_LPSPI_TCR_LSBF          BIT(23)
#define S32K3_LPSPI_TCR_PCS_SHIFT     24
#define S32K3_LPSPI_TCR_PCS_MASK      (0x7 << S32K3_LPSPI_TCR_PCS_SHIFT)
#define S32K3_LPSPI_TCR_PRESCALE_SHIFT 27
#define S32K3_LPSPI_TCR_PRESCALE_MASK (0x7 << S32K3_LPSPI_TCR_PRESCALE_SHIFT)
#define S32K3_LPSPI_TCR_CPHA          BIT(30)
#define S32K3_LPSPI_TCR_CPOL          BIT(31)
#define S32K3_LPSPI_TCR_RESET         0x1F /* FRAMESZ = 0x1F (32-bit frame) at reset */

/* FCR (FIFO Control, offset 0x58) - manual section 70.6.1.14 */
#define S32K3_LPSPI_FCR_TXWATER_MASK  0x3
#define S32K3_LPSPI_FCR_RXWATER_SHIFT 16
#define S32K3_LPSPI_FCR_RXWATER_MASK  (0x3 << S32K3_LPSPI_FCR_RXWATER_SHIFT)

/* FSR (FIFO Status, offset 0x5C) - manual section 70.6.1.15 */
#define S32K3_LPSPI_FSR_TXCOUNT_SHIFT 0
#define S32K3_LPSPI_FSR_RXCOUNT_SHIFT 16

/* RSR (Receive Status, offset 0x70) - manual section 70.6.1.18 */
#define S32K3_LPSPI_RSR_SOF     BIT(0)
#define S32K3_LPSPI_RSR_RXEMPTY BIT(1)

#define S32K3_LPSPI_FIFO_DEPTH 4 /* words - uniform across all 6 instances, Table 439 */

#define TYPE_S32K3_LPSPI "s32k3-lpspi"
OBJECT_DECLARE_SIMPLE_TYPE(S32K3LPSPIState, S32K3_LPSPI)

struct S32K3LPSPIState {
    SysBusDevice parent_obj;

    MemoryRegion iomem;
    qemu_irq irq;
    SSIBus *spi;

    uint32_t instance_id;
    uint32_t num_pcs; /* cosmetic: chip-select count reported via PARAM */

    /* Registers */
    uint32_t verid;
    uint32_t param;
    uint32_t cr;
    uint32_t sr;
    uint32_t ier;
    uint32_t der;
    uint32_t cfgr0;
    uint32_t cfgr1;
    uint32_t dmr0;
    uint32_t dmr1;
    uint32_t ccr;
    uint32_t ccr1;
    uint32_t fcr;
    uint32_t tcr;
    uint32_t rdror;

    /* TX/RX FIFOs, 4x32-bit each (Table 439) */
    uint32_t tx_fifo[S32K3_LPSPI_FIFO_DEPTH];
    uint32_t tx_count;
    uint32_t rx_fifo[S32K3_LPSPI_FIFO_DEPTH];
    uint32_t rx_count;
    bool sof_pending; /* next received word is the start of a new frame */
};

#endif /* HW_SSI_S32K3_LPSPI_H */
