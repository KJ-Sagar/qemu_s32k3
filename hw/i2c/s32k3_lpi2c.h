/*
 * NXP S32K3xx Low Power Inter-Integrated Circuit (LPI2C) Emulation
 *
 * Register map and bit definitions verified against the S32K3xx Reference
 * Manual, Rev. 11 (2025-07-11), Chapter 71 "Low Power Inter-Integrated
 * Circuit (LPI2C)" (manual pages 2921-2982). Both instances (LPI2C0 at
 * 4035_0000h, LPI2C1 at 4035_4000h) share the same register map, each with
 * a 4x32-bit controller TX and RX FIFO (PARAM reset value 0000_0202h).
 *
 * This model implements Controller (master) mode functionally: command
 * words written to MTDR (manual 71.7.1.17, MTDR[CMD]) are executed against
 * a real QEMU I2CBus via i2c_start_transfer()/i2c_send()/i2c_recv()/
 * i2c_end_transfer(), so an emulated I2C slave device attached to the bus
 * will genuinely see Start/Address/Data/Stop traffic. Target (slave) mode
 * registers (SCR/SSR/SIER/... at offset 0x110+) are not modeled; this MCU
 * is essentially always used as an I2C controller talking to sensors, so
 * that is the mode worth emulating.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#ifndef HW_I2C_S32K3_LPI2C_H
#define HW_I2C_S32K3_LPI2C_H

#include "hw/core/sysbus.h"
#include "hw/i2c/i2c.h"
#include "qom/object.h"

/* LPI2C register offsets (manual section 71.7.1.1, "LPI2C memory map") */
#define S32K3_LPI2C_VERID   0x00
#define S32K3_LPI2C_PARAM   0x04
#define S32K3_LPI2C_MCR     0x10
#define S32K3_LPI2C_MSR     0x14
#define S32K3_LPI2C_MIER    0x18
#define S32K3_LPI2C_MDER    0x1C
#define S32K3_LPI2C_MCFGR0  0x20
#define S32K3_LPI2C_MCFGR1  0x24
#define S32K3_LPI2C_MCFGR2  0x28
#define S32K3_LPI2C_MCFGR3  0x2C
#define S32K3_LPI2C_MDMR    0x40
#define S32K3_LPI2C_MCCR0   0x48
#define S32K3_LPI2C_MCCR1   0x50
#define S32K3_LPI2C_MFCR    0x58
#define S32K3_LPI2C_MFSR    0x5C
#define S32K3_LPI2C_MTDR    0x60
#define S32K3_LPI2C_MRDR    0x70

#define S32K3_LPI2C_REGS_MEM_SIZE 0x74

/* MCR (Controller Control, offset 0x10) - manual section 71.7.1.4 */
#define S32K3_LPI2C_MCR_MEN    BIT(0)
#define S32K3_LPI2C_MCR_RST    BIT(1)
#define S32K3_LPI2C_MCR_DOZEN  BIT(2)
#define S32K3_LPI2C_MCR_DBGEN  BIT(3)
#define S32K3_LPI2C_MCR_RTF    BIT(8) /* self-clearing, always reads 0 */
#define S32K3_LPI2C_MCR_RRF    BIT(9) /* self-clearing, always reads 0 */

/* MSR (Controller Status, offset 0x14) - manual section 71.7.1.5 */
#define S32K3_LPI2C_MSR_TDF    BIT(0)
#define S32K3_LPI2C_MSR_RDF    BIT(1)
#define S32K3_LPI2C_MSR_EPF    BIT(8)  /* W1C */
#define S32K3_LPI2C_MSR_SDF    BIT(9)  /* W1C */
#define S32K3_LPI2C_MSR_NDF    BIT(10) /* W1C */
#define S32K3_LPI2C_MSR_ALF    BIT(11) /* W1C */
#define S32K3_LPI2C_MSR_FEF    BIT(12) /* W1C */
#define S32K3_LPI2C_MSR_PLTF   BIT(13) /* W1C */
#define S32K3_LPI2C_MSR_DMF    BIT(14) /* W1C */
#define S32K3_LPI2C_MSR_MBF    BIT(24)
#define S32K3_LPI2C_MSR_BBF    BIT(25)
#define S32K3_LPI2C_MSR_W1C_MASK (S32K3_LPI2C_MSR_EPF | S32K3_LPI2C_MSR_SDF | \
                                   S32K3_LPI2C_MSR_NDF | S32K3_LPI2C_MSR_ALF | \
                                   S32K3_LPI2C_MSR_FEF | S32K3_LPI2C_MSR_PLTF | \
                                   S32K3_LPI2C_MSR_DMF)
#define S32K3_LPI2C_MSR_RESET  S32K3_LPI2C_MSR_TDF

/* MIER (Controller Interrupt Enable, offset 0x18) - manual section 71.7.1.6 */
#define S32K3_LPI2C_MIER_TDIE  BIT(0)
#define S32K3_LPI2C_MIER_RDIE  BIT(1)
#define S32K3_LPI2C_MIER_EPIE  BIT(8)
#define S32K3_LPI2C_MIER_SDIE  BIT(9)
#define S32K3_LPI2C_MIER_NDIE  BIT(10)
#define S32K3_LPI2C_MIER_ALIE  BIT(11)
#define S32K3_LPI2C_MIER_FEIE  BIT(12)
#define S32K3_LPI2C_MIER_PLTIE BIT(13)
#define S32K3_LPI2C_MIER_DMIE  BIT(14)

/* MFCR / MFSR (FIFO control/status, offsets 0x58/0x5C) - sections
 * 71.7.1.15-16, same bit layout convention as LPSPI FCR/FSR. */
#define S32K3_LPI2C_MFCR_TXWATER_MASK  0x3
#define S32K3_LPI2C_MFCR_RXWATER_SHIFT 16
#define S32K3_LPI2C_MFCR_RXWATER_MASK  (0x3 << S32K3_LPI2C_MFCR_RXWATER_SHIFT)
#define S32K3_LPI2C_MFSR_TXCOUNT_SHIFT 0
#define S32K3_LPI2C_MFSR_RXCOUNT_SHIFT 16

/* MTDR (Controller Transmit Data, offset 0x60) - manual section 71.7.1.17 */
#define S32K3_LPI2C_MTDR_DATA_MASK 0xFF
#define S32K3_LPI2C_MTDR_CMD_SHIFT 8
#define S32K3_LPI2C_MTDR_CMD_MASK  (0x7 << S32K3_LPI2C_MTDR_CMD_SHIFT)

enum {
    S32K3_LPI2C_CMD_TRANSMIT       = 0,
    S32K3_LPI2C_CMD_RECEIVE        = 1,
    S32K3_LPI2C_CMD_STOP           = 2,
    S32K3_LPI2C_CMD_RECEIVE_DISCARD = 3,
    S32K3_LPI2C_CMD_START_ACK      = 4,
    S32K3_LPI2C_CMD_START_NACK     = 5,
    S32K3_LPI2C_CMD_START_HS_ACK   = 6,
    S32K3_LPI2C_CMD_START_HS_NACK  = 7,
};

/* MRDR (Controller Receive Data, offset 0x70) - manual section 71.7.1.18 */
#define S32K3_LPI2C_MRDR_DATA_MASK 0xFF
#define S32K3_LPI2C_MRDR_RXEMPTY   BIT(14)

#define S32K3_LPI2C_FIFO_DEPTH 4 /* words - PARAM reset 0000_0202h => 2^2 */

#define TYPE_S32K3_LPI2C "s32k3-lpi2c"
OBJECT_DECLARE_SIMPLE_TYPE(S32K3LPI2CState, S32K3_LPI2C)

struct S32K3LPI2CState {
    SysBusDevice parent_obj;

    MemoryRegion iomem;
    qemu_irq irq;
    I2CBus *bus;

    uint32_t instance_id;

    /* Registers */
    uint32_t verid;
    uint32_t param;
    uint32_t mcr;
    uint32_t msr;
    uint32_t mier;
    uint32_t mder;
    uint32_t mcfgr0;
    uint32_t mcfgr1;
    uint32_t mcfgr2;
    uint32_t mcfgr3;
    uint32_t mdmr;
    uint32_t mccr0;
    uint32_t mccr1;
    uint32_t mfcr;

    /* Command/transmit and receive FIFOs, 4x32-bit each */
    uint32_t tx_fifo[S32K3_LPI2C_FIFO_DEPTH];
    uint32_t tx_count;
    uint32_t rx_fifo[S32K3_LPI2C_FIFO_DEPTH];
    uint32_t rx_count;

    bool started; /* true while a Start condition is open on the bus */
};

#endif /* HW_I2C_S32K3_LPI2C_H */
