/*
 * NXP S32K3xx Cyclic Redundancy Check (CRC) Emulation
 *
 * Register map and bit definitions verified against the S32K3xx Reference
 * Manual, Rev. 11 (2025-07-11), Chapter 58 "Cyclic Redundancy Check (CRC)"
 * (manual pages 2304-2314). One instance, base 0x4038_0000.
 *
 * This model implements the real bit-serial CRC engine (16-bit or 32-bit,
 * configurable polynomial and seed via GPOLY/DATA+CTRL[WAS], per manual
 * 58.3.2), plus the TOT/TOTR transpose options (58.3.3) and the FXOR read
 * complement (58.3.4) for full 32-bit accesses to DATA. Sub-word (8/16-bit)
 * accesses to DATA are supported for feeding data into the CRC (the common
 * "write one byte at a time" usage), but the exact zero-pad-then-transpose
 * corner case the manual describes for sub-word accesses combined with a
 * non-zero transpose setting is not reproduced bit-for-bit - see the
 * s32k3_crc_write() comment for the simplification.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#ifndef HW_MISC_S32K3_CRC_H
#define HW_MISC_S32K3_CRC_H

#include "hw/core/sysbus.h"
#include "qom/object.h"

/* CRC register offsets (manual section 58.7.1.1, "CRC memory map") */
#define S32K3_CRC_DATA   0x00
#define S32K3_CRC_GPOLY  0x04
#define S32K3_CRC_CTRL   0x08

#define S32K3_CRC_REGS_MEM_SIZE 0x0C

/* CTRL (Control, offset 0x08) - manual section 58.7.1.4 */
#define S32K3_CRC_CTRL_TCRC       BIT(24)
#define S32K3_CRC_CTRL_WAS        BIT(25)
#define S32K3_CRC_CTRL_FXOR       BIT(26)
#define S32K3_CRC_CTRL_TOT_SHIFT  30
#define S32K3_CRC_CTRL_TOT_MASK   (0x3u << S32K3_CRC_CTRL_TOT_SHIFT)
#define S32K3_CRC_CTRL_TOTR_SHIFT 28
#define S32K3_CRC_CTRL_TOTR_MASK  (0x3u << S32K3_CRC_CTRL_TOTR_SHIFT)

#define TYPE_S32K3_CRC "s32k3-crc"
OBJECT_DECLARE_SIMPLE_TYPE(S32K3CRCState, S32K3_CRC)

struct S32K3CRCState {
    SysBusDevice parent_obj;

    MemoryRegion iomem;

    uint32_t data;  /* current CRC accumulator / seed, raw (untransposed) */
    uint32_t gpoly;
    uint32_t ctrl;
};

#endif /* HW_MISC_S32K3_CRC_H */
