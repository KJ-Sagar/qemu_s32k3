/*
 * NXP S32K388/S32K389 Quad Serial Peripheral Interface (QuadSPI) Emulation
 *
 * Register map and bit definitions verified against the S32K3xx Reference
 * Manual, Rev. 11 (2025-07-11), Chapter 80 "Quad Serial Peripheral
 * Interface (QuadSPI) for S32K388 and S32K389" (manual pages 4929-5171,
 * register descriptions ~4973-5171). Manual section 80.1.1, Table 772:
 * one QuadSPI instance on S32K388/S32K389. Controller register base
 * 0x404C_C000 (section 80.13.2.1); the separate AHB RX Data Buffer
 * (ARDB) register base 0x6800_0000 (section 80.14.3.1).
 *
 * Scope: this is a full external-NOR-flash controller (LUT-programmable
 * command sequencer, AHB memory-mapped flash aperture, DMA, DLL/DQS
 * sampling, secure flash region descriptors). This model is "functional
 * where practical" for the IP-bus (register-triggered) command path,
 * which is what firmware flash drivers actually use to talk to the
 * flash chip:
 *   - MCR (module enable/disable, FIFO clear), SFAR (flash byte
 *     address), IPCR (SEQID/IDATSZ - writing SEQID triggers execution),
 *     SR/FR (busy + W1C completion/error flags), TBDR (TX FIFO push),
 *     RBDR0-31 (RX FIFO, 32 x 32-bit), LUT0-79 (80 registers = 16
 *     sequences x 5 registers x 2 instructions, per section 80.13.2.34's
 *     "up to 10 instructions per sequence" note) with LUTKEY/LCKCR
 *     lock/unlock enforcement, are all real.
 *   - A SEQID trigger walks that sequence's LUT instructions looking for
 *     a READ or WRITE opcode (see s32k3_qspi_lut_opcode_t): a WRITE
 *     command copies IDATSZ bytes from the TX FIFO into an internal
 *     backing "flash" byte array at the SFAR offset (i.e., performs a
 *     real program operation against emulated flash content); a READ
 *     command copies IDATSZ bytes from that same offset into the RX
 *     FIFO. Command-only sequences (e.g. write-enable, read-status)
 *     complete immediately with no data movement - there's no real NOR
 *     flash status-register/erase-cycle model behind this.
 *   - The internal flash backing array is 16 MiB, erased (0xFF) at
 *     reset, matching a typical external QSPI NOR part.
 *   - The ARDB shadow region at 0x6800_0000 mirrors the RX FIFO for
 *     32-bit AHB-side reads (real hardware also supports paired 64-bit
 *     reads across two RBDR entries at once - not modeled).
 *   - NOT modeled: the AHB memory-mapped flash aperture itself
 *     (QuadSPI_AMBA_BASE - reading flash content by addressing it
 *     directly as normal memory) - its base address is deferred by the
 *     manual to the missing system memory-map spreadsheet, and the
 *     IP-command path above is a complete, testable substitute. Also not
 *     modeled: DMA-triggered FIFO service, the DLL/DQS sampling and
 *     Flash Region Access Descriptor (FRAD) engines, and dual/octal DDR
 *     timing - these don't affect whether a byte gets sent/received
 *     correctly, only signal-level timing this emulation doesn't have.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#ifndef HW_SSI_S32K3_QSPI_H
#define HW_SSI_S32K3_QSPI_H

#include "hw/core/sysbus.h"
#include "qom/object.h"

/* Controller register offsets (manual section 80.13.2.1) */
#define S32K3_QSPI_MCR      0x000
#define S32K3_QSPI_IPCR     0x008
#define S32K3_QSPI_SFAR     0x100
#define S32K3_QSPI_RBSR     0x10C
#define S32K3_QSPI_TBSR     0x150
#define S32K3_QSPI_TBDR     0x154
#define S32K3_QSPI_SR       0x15C
#define S32K3_QSPI_FR       0x160
#define S32K3_QSPI_RSER     0x164
#define S32K3_QSPI_RBDR(n)  (0x200 + (n) * 4)  /* n = 0..31 */
#define S32K3_QSPI_LUTKEY   0x300
#define S32K3_QSPI_LCKCR    0x304
#define S32K3_QSPI_LUT(n)   (0x310 + (n) * 4)  /* n = 0..79 */

#define S32K3_QSPI_NUM_RBDR 32
#define S32K3_QSPI_NUM_LUT  80
#define S32K3_QSPI_LUT_SEQ_REGS 5  /* 10 instructions/sequence, 2 per reg */
#define S32K3_QSPI_REGS_MEM_SIZE 0x500

#define S32K3_QSPI_FLASH_SIZE (16 * 1024 * 1024)

/* ARDB (AHB RX Data Buffer) - separate MMIO region, base 0x6800_0000
 * (manual section 80.14.3.1). Mirrors the RX FIFO. */
#define S32K3_QSPI_ARDB_MEM_SIZE (S32K3_QSPI_NUM_RBDR * 4)

/* MCR (offset 0x000) - manual section 80.13.2.2 */
#define S32K3_QSPI_MCR_MDIS     BIT(14)
#define S32K3_QSPI_MCR_CLR_RXF  BIT(10)
#define S32K3_QSPI_MCR_CLR_TXF  BIT(11)
#define S32K3_QSPI_MCR_RESET    0x000F404Cu

/* IPCR (offset 0x008) - manual section 80.13.2.3 */
#define S32K3_QSPI_IPCR_SEQID_SHIFT 24
#define S32K3_QSPI_IPCR_SEQID_MASK  (0xFu << S32K3_QSPI_IPCR_SEQID_SHIFT)
#define S32K3_QSPI_IPCR_IDATSZ_MASK 0xFFFFu

/* SR (offset 0x15C) - manual section 80.13.2.25 */
#define S32K3_QSPI_SR_IP_ACC BIT(0)
#define S32K3_QSPI_SR_RESET  0x02003800u

/* FR (offset 0x160) - manual section 80.13.2.26; W1C */
#define S32K3_QSPI_FR_TFF     BIT(0)
#define S32K3_QSPI_FR_ILLINE  BIT(23)
#define S32K3_QSPI_FR_W1C_MASK 0x1D030001u
#define S32K3_QSPI_FR_RESET   0x08000000u

/* LCKCR (offset 0x304) - bit 0 LOCK, bit 1 UNLOCK (write-only pulses per
 * manual convention observed elsewhere in this codebase: writing either
 * bit performs the action; the register does not literally latch them). */
#define S32K3_QSPI_LCKCR_LOCK   BIT(0)
#define S32K3_QSPI_LCKCR_UNLOCK BIT(1)
#define S32K3_QSPI_LUTKEY_VALUE 0x5AF05AF0u

/* LUT instruction opcodes this model recognizes (manual Table 778,
 * "Instruction set": STOP=0, CMD=1, ADDR=2, DUMMY=3, MODE=4, MODE2=5,
 * MODE4=6, READ=7, WRITE=8, ...). Only READ/WRITE/STOP matter for
 * deciding what this model's SEQID trigger does; every other opcode
 * (CMD, ADDR, DUMMY, MODE*, JMP_ON_CS, ...) is a no-op here - this model
 * has no real SPI pin timing for them to affect. */
typedef enum {
    S32K3_QSPI_LUT_OP_STOP  = 0,
    S32K3_QSPI_LUT_OP_READ  = 7,
    S32K3_QSPI_LUT_OP_WRITE = 8,
} S32K3QspiLutOp;

#define TYPE_S32K3_QSPI "s32k3-qspi"
OBJECT_DECLARE_SIMPLE_TYPE(S32K3QspiState, S32K3_QSPI)

struct S32K3QspiState {
    SysBusDevice parent_obj;

    MemoryRegion iomem;      /* controller registers, 0x404C_C000 */
    MemoryRegion ardb_iomem; /* ARDB shadow, 0x6800_0000 */
    qemu_irq irq;

    uint32_t mcr;
    uint32_t ipcr;
    uint32_t sfar;
    uint32_t sr;
    uint32_t fr;
    uint32_t rser;
    uint32_t lckcr;
    bool locked;

    uint32_t rbdr[S32K3_QSPI_NUM_RBDR];
    uint32_t rbdr_count; /* valid entries, for RBSR[RDBFL] */

    uint32_t tx_fifo[S32K3_QSPI_NUM_RBDR];
    uint32_t tx_count;

    uint32_t lut[S32K3_QSPI_NUM_LUT];

    uint8_t *flash; /* S32K3_QSPI_FLASH_SIZE bytes, erased (0xFF) at reset */
};

#endif /* HW_SSI_S32K3_QSPI_H */
