#ifndef HW_ARM_S32K389_H
#define HW_ARM_S32K389_H
 
#include "hw/arm/armv7m.h"
#include "hw/core/boards.h"
#include "hw/core/sysbus.h"
#include "qemu/osdep.h"
#include "qemu/units.h"
#include "qom/object.h"
#include "net/can_emu.h"
#include "hw/ssi/s32k3_lpspi.h"
#include "hw/i2c/s32k3_lpi2c.h"
#include "hw/watchdog/s32k3_swt.h"
#include "hw/misc/s32k3_crc.h"
#include "hw/adc/s32k3_adc.h"
#include "hw/timer/s32k3_emios.h"
#include "hw/dma/s32k3_edma.h"
#include "hw/net/npcm_gmac.h"
#include "hw/ssi/s32k3_qspi.h"
#include "hw/audio/s32k3_sai.h"

#define TYPE_S32K389 MACHINE_TYPE_NAME("s32k389")
OBJECT_DECLARE_SIMPLE_TYPE(S32K389State, S32K389)
 
// System frequency definitions
#define S32K3_SYSCLK_FREQ           (320 * 1000 * 1000)  // 320MHz
 
// Memory definitions
#define INT_ITCM_BASE               0x00000000  // Instruction Tightly Coupled Memory
#define INT_ITCM_SIZE               (64 * KiB)  // 64KB
 
#define INT_DTCM_BASE               0x20000000  // Data Tightly Coupled Memory
#define INT_DTCM_SIZE               (124 * KiB) // 124KB
#define INT_DTCM_STACK_BASE         0x2001F000  // Stack area in DTCM
#define INT_DTCM_STACK_SIZE         (4 * KiB)   // 4KB
 
// Flash
// S32K389 has TWO program-flash controllers (PFC0 + PFC1), unlike S32K388's
// single controller - verified against S32K3xx_memory_map.xlsx. The 8 blocks
// below are contiguous (0x00400000-0x00FFFFFF) and sum to 12MB, matching the
// NXP datasheet block diagram ("Figure 16. S32K389: ASIL D 12MB MCU").
#define FLASH_SIZE                  0x00C00000  // 12 MB total, contiguous
#define INT_CODE_FLASH0_BASE        0x00400000  // PFC1 Block 0
#define INT_CODE_FLASH0_SIZE        0x00100000  // 1 MB
/* The FlexCAN example firmware places its reset vector table at 0x00402000. */
#define INT_CODE_FLASH0_CORE0_VTOR  0x00402000
#define INT_CODE_FLASH1_BASE        0x00500000  // PFC1 Block 1
#define INT_CODE_FLASH1_SIZE        0x00100000  // 1 MB
#define INT_CODE_FLASH2_BASE        0x00600000  // PFC0 Block 0
#define INT_CODE_FLASH2_SIZE        0x00200000  // 2 MB
#define INT_CODE_FLASH3_BASE        0x00800000  // PFC0 Block 1
#define INT_CODE_FLASH3_SIZE        0x00200000  // 2 MB
#define INT_CODE_FLASH4_BASE        0x00A00000  // PFC1 Block 2
#define INT_CODE_FLASH4_SIZE        0x00100000  // 1 MB
#define INT_CODE_FLASH5_BASE        0x00B00000  // PFC1 Block 3
#define INT_CODE_FLASH5_SIZE        0x00100000  // 1 MB
#define INT_CODE_FLASH6_BASE        0x00C00000  // PFC0 Block 2
#define INT_CODE_FLASH6_SIZE        0x00200000  // 2 MB
#define INT_CODE_FLASH7_BASE        0x00E00000  // PFC0 Block 3
#define INT_CODE_FLASH7_SIZE        0x00200000  // 2 MB
#define INT_DATA_FLASH_BASE         0x10000000
#define INT_DATA_FLASH_SIZE         0x00040000  // 256 KB (S32K389; S32K388 is 128KB)
#define INT_UTEST_NVM_FLASH_BASE    0x1B000000
#define INT_UTEST_NVM_FLASH_SIZE    0x00002000  // 8 KB (same on both chips)
 
// SRAM
// S32K389 has 4 SRAM banks (512+512+512+384 = 1920KB) vs S32K388's 3 banks
// (256+256+256 = 768KB) - verified against S32K3xx_memory_map.xlsx. The 64KB
// "standby" carve-out at the front of SRAM0 is preserved from the original
// model (a low-power retention RAM feature, independent of total SRAM grade,
// not broken out as its own row in the memory-map sheet).
#define SRAM_SIZE                   0x1E0000    // 1920KB (512+512+512+384)
#define INT_SRAM_STANDBY_BASE       0x20400000  // SRAM_standby, split from SRAM0
#define INT_SRAM_STANDBY_SIZE       0x10000     // 64KB
#define INT_SRAM_0_BASE             0x20410000
#define INT_SRAM_0_SIZE             0x70000     // 512KB - 64KB = 448KB
#define INT_SRAM_1_BASE             0x20480000
#define INT_SRAM_1_SIZE             0x80000     // 512KB
#define INT_SRAM_2_BASE             0x20500000
#define INT_SRAM_2_SIZE             0x80000     // 512KB
#define INT_SRAM_3_BASE             0x20580000  // S32K389-only bank (S32K388 has no SRAM3)
#define INT_SRAM_3_SIZE             0x60000     // 384KB
 
// Peripheral definitions
#define S32K3_PERIPH_BASE           0x40000000

// MSCM (Miscellaneous System Control Module), verified against
// S32K3xx_memory_map.xlsx. Early startup code reads CPXTYPE at offset 0x04
// for the running core ID and TCM mode at offset 0x14.
#define S32K3_MSCM_BASE             0x40260000
#define S32K3_MSCM_SIZE             0x4000
 
// LPUART
#define S32K3_UART_BASE             0x40328000
#define S32K3_LPUART1_BASE          0x4032C000
#define S32K3_LPUART2_BASE          0x40330000
#define S32K3_LPUART3_BASE          0x40334000
#define S32K3_LPUART4_BASE          0x40338000
#define S32K3_LPUART5_BASE          0x4033C000
#define S32K3_LPUART6_BASE          0x40340000
#define S32K3_LPUART7_BASE          0x40344000
#define S32K3_LPUART8_BASE          0x4048C000
#define S32K3_LPUART9_BASE          0x40490000
#define S32K3_LPUART10_BASE         0x40494000
#define S32K3_LPUART11_BASE         0x40498000
#define S32K3_LPUART12_BASE         0x4049C000
#define S32K3_LPUART13_BASE         0x404A0000
#define S32K3_LPUART14_BASE         0x404A4000
#define S32K3_LPUART15_BASE         0x404A8000
 
#define S32K3_CONSOLE_LPUART_BASE S32K3_LPUART3_BASE
#define S32K3_CONSOLE_LPUART_IRQ  144  // verified: LPUART 3 = IRQ 144 in interrupt map
 
// FlexIO instance used by the UART loopback example
#define S32K3_FLEXIO_BASE          0x40324000
#define S32K3_FLEXIO_IRQ           139  // verified: "Flexible IO" = IRQ 139 in interrupt map
 
// LPSPI
#define S32K389_NUM_LPSPI 6
#define S32K3_LPSPI0_BASE (S32K3_PERIPH_BASE + 0x358000)  // 0x40358000
#define S32K3_LPSPI1_BASE (S32K3_PERIPH_BASE + 0x35C000)  // 0x4035C000
#define S32K3_LPSPI2_BASE (S32K3_PERIPH_BASE + 0x360000)  // 0x40360000
#define S32K3_LPSPI3_BASE (S32K3_PERIPH_BASE + 0x364000)  // 0x40364000
#define S32K3_LPSPI4_BASE (S32K3_PERIPH_BASE + 0x4BC000)  // 0x404BC000
#define S32K3_LPSPI5_BASE (S32K3_PERIPH_BASE + 0x4C0000)  // 0x404C0000
// LPSPI Interrupts
// Verified against S32K3xx_interrupt_map.xlsx. NOTE: the previous values
// here (69-74) were wrong - those IRQs actually belong to eMIOS1 per the
// interrupt map, not LPSPI. Corrected below.
#define S32K3_LPSPI0_IRQ 165
#define S32K3_LPSPI1_IRQ 166
#define S32K3_LPSPI2_IRQ 167
#define S32K3_LPSPI3_IRQ 168
#define S32K3_LPSPI4_IRQ 169
#define S32K3_LPSPI5_IRQ 170
 
// LPI2C
// Base addresses verified against the S32K3xx Reference Manual, Rev. 11,
// section 71.7.1.1 "LPI2C memory map" (manual pages 2921-2982). S32K389 has
// 2 instances (Table in datasheet: "2 x LPI2C").
#define S32K389_NUM_LPI2C 2
#define S32K3_LPI2C0_BASE (S32K3_PERIPH_BASE + 0x350000)  // 0x40350000
#define S32K3_LPI2C1_BASE (S32K3_PERIPH_BASE + 0x354000)  // 0x40354000
// LPI2C Interrupts
// UNVERIFIED PLACEHOLDER: the S32K3xx_interrupt_map.xlsx spreadsheet that
// the LPSPI/FlexCAN IRQ numbers above were cross-checked against was not
// among the uploaded reference files, so these two numbers are only a
// best-effort placeholder (chosen from the range immediately after the
// verified LPSPI block) and have NOT been confirmed against the real
// interrupt map. Update these once that spreadsheet is available.
#define S32K3_LPI2C0_IRQ 175
#define S32K3_LPI2C1_IRQ 176

// SWT (Software Watchdog Timer) - one per Cortex-M7 core (manual Table 430:
// S32K389 populates all 4). Base addresses verified against S32K3xx
// Reference Manual section 66.6.1 "SWT memory map".
#define S32K389_NUM_SWT 4
#define S32K3_SWT0_BASE 0x40270000
#define S32K3_SWT1_BASE 0x4046C000
#define S32K3_SWT2_BASE 0x40470000
#define S32K3_SWT3_BASE 0x40070000
// SWT Interrupts
// UNVERIFIED PLACEHOLDER - see the S32K3_LPI2Cn_IRQ comment above; same
// caveat applies (interrupt map spreadsheet not available).
#define S32K3_SWT0_IRQ 177
#define S32K3_SWT1_IRQ 178
#define S32K3_SWT2_IRQ 179
#define S32K3_SWT3_IRQ 180

// CRC
// Single instance, no interrupt (manual 58.3.6: "This module has no
// interrupts"). Base address verified against section 58.7.1.1.
#define S32K3_CRC_BASE 0x40380000

// ADC
// Base addresses verified against S32K3xx Reference Manual section
// 60.6.2.1 "ADC memory map". 3 instances (datasheet: "3 x 24-channel
// 12-bit ADC").
#define S32K389_NUM_ADC 3
#define S32K3_ADC0_BASE 0x400A0000
#define S32K3_ADC1_BASE 0x400A4000
#define S32K3_ADC2_BASE 0x400A8000
// ADC Interrupts
// UNVERIFIED PLACEHOLDER - see the S32K3_LPI2Cn_IRQ comment above; same
// caveat applies (interrupt map spreadsheet not available).
#define S32K3_ADC0_IRQ 181
#define S32K3_ADC1_IRQ 182
#define S32K3_ADC2_IRQ 183

// eMIOS
// Base addresses verified against S32K3xx Reference Manual section
// 63.8.6.1 "eMIOS memory map". 3 instances (datasheet: "3 x 24-channel
// eMIOS Timer").
#define S32K389_NUM_EMIOS 3
#define S32K3_EMIOS0_BASE 0x40088000
#define S32K3_EMIOS1_BASE 0x4008C000
#define S32K3_EMIOS2_BASE 0x40090000
// eMIOS Interrupts
// UNVERIFIED PLACEHOLDER - see the S32K3_LPI2Cn_IRQ comment above; same
// caveat applies (interrupt map spreadsheet not available). Real silicon
// likely has one IRQ per channel or per small channel group rather than
// one per instance; this model exposes a single OR'd IRQ per instance
// (see s32k3_emios.h scope note), so only 3 placeholder numbers are used.
#define S32K3_EMIOS0_IRQ 184
#define S32K3_EMIOS1_IRQ 185
#define S32K3_EMIOS2_IRQ 186

// eDMA
// Base addresses verified against S32K3xx Reference Manual sections
// 15.6.1.1 (management page) and 15.6.2.1 (TCD/channel page). Manual
// section 15.1.1: "This chip has one instance of eDMA without any
// lockstep", 32 channels (section 15.1.2, Table 54).
#define S32K3_EDMA_MGMT_BASE 0x4020C000
#define S32K3_EDMA_CH_BASE   0x40210000
// eDMA per-channel Interrupts
// UNVERIFIED PLACEHOLDER - see the S32K3_LPI2Cn_IRQ comment above; same
// caveat applies (interrupt map spreadsheet not available). One IRQ per
// channel is modeled (32 total), consistent with how most Cortex-M NVIC
// based SoCs wire each DMA channel to its own vector.
#define S32K3_EDMA_IRQ_BASE 187 // channels 0..31 -> IRQ 187..218

// Multi-core
// Manual section 3.5 "Considerations related to TCM's implementation":
// "Each Cortex-M7 core is equipped with a 32 KB ITCM and 64 KB DTCM...
// In the lockstep operation, the checker core's TCM is added to the
// primary core." Manual section 3.4 (DCMRWF4/PRTN0_COREn_PCONF table)
// names the 4 physical cores CM7_0/CM7_1 (lockstep or split-lock pair 1)
// and CM7_2/CM7_3 (pair 2). Datasheet Figure 16 (S32K389) shows one
// "Lock-Step or Split-Lock" CPU box plus 3 further Cortex-M7 boxes.
//
// Scope: a real hardware lockstep checker core has no independently
// observable software behavior (that's the point of lockstep - it's a
// silent comparator, not a second programmable core), so there is
// nothing meaningful to emulate there. This model instead exposes all 4
// physical cores as independent, separately-programmable Cortex-M7 CPUs
// (equivalent to real silicon's "split-lock/decoupled" configuration,
// which is also the more useful configuration for firmware bring-up),
// each with its own private ITCM/DTCM at the same architectural local
// addresses (0x0 / 0x2000_0000) via a per-core memory container, and
// sharing the rest of the address space (flash, shared SRAM,
// peripherals) exactly like core 0 already did. All 4 cores default to
// the SAME shared boot vector table in flash (INT_CODE_FLASH0_CORE0_VTOR)
// since no per-core-partition boot address split was found in the
// available manual excerpts - real firmware for this topology is
// expected to branch on core ID early in its shared reset handler,
// which is the common pattern for this class of multi-core Cortex-M
// chip. Peripheral IRQ routing/distribution across cores is NOT
// modeled (no interrupt map spreadsheet available, as elsewhere in this
// file) - only core 0's NVIC has any peripheral IRQ lines connected;
// cores 1-3 have working, independent NVICs (SysTick/software
// exceptions all function normally) but no peripheral wired to them yet.
#define S32K389_NUM_CORES 4

// STCU2 (Self-Test Control Unit) - manual Chapter 54. UNVERIFIED
// PLACEHOLDER base address: the manual repeatedly defers STCU2's
// register memory map to the missing interrupt/memory-map spreadsheet,
// so no confirmed address was found in the available excerpts. This is
// a minimal read-only stub (BSTART/ALGOSEL storage + an always-pass
// lockstep/self-test status word) - not a real self-test engine.
#define S32K3_STCU2_BASE 0x40054000
#define S32K3_STCU2_SIZE 0x4000

// GMAC Ethernet
// Manual Chapter 76 section 76.1.1 "GMAC instances and configuration",
// Table 618: groups S32K388 and S32K389 together as having "two instances
// (GMAC_0 and GMAC_1)" in the SAME table column, distinct from the
// single-instance S32K358/356/348/338/328 column. Base addresses are
// reused directly from the already-verified S32K388 model
// (hw/arm/s32k388.h) on the strength of that grouping, rather than
// independently re-derived from a S32K389-specific memory-map excerpt.
// IRQ numbers carried over from the same source - same UNVERIFIED
// PLACEHOLDER caveat as elsewhere in this file (no interrupt map
// spreadsheet available).
#define S32K389_GMAC_COUNT 2
#define S32K389_GMAC0_BASE 0x40484000
#define S32K389_GMAC1_BASE 0x40488000
#define S32K389_GMAC0_IRQ  224
#define S32K389_GMAC1_IRQ  171

// QuadSPI
// Controller register base verified against manual section 80.13.2.1
// "QuadSPI memory map"; ARDB (AHB RX Data Buffer) base verified against
// section 80.14.3.1. Single instance (manual section 80.1.1, Table 772).
#define S32K3_QSPI_BASE      0x404CC000
#define S32K3_QSPI_ARDB_BASE 0x68000000
// UNVERIFIED PLACEHOLDER - see the S32K3_LPI2Cn_IRQ comment above; same
// caveat applies (interrupt map spreadsheet not available).
#define S32K3_QSPI_IRQ 219

// SAI (Synchronous Audio Interface)
// Base addresses verified against manual section 74.6.1.1 "SAI memory map".
// 2 instances (manual Table 546: SAI_0/SAI_1 both "Yes" for S32K389).
// PARAM reset values also verified there: SAI_0 has 4 data lines wired in
// its register map (0004_0304h), SAI_1 has 1 (0004_0301h) - see
// s32k3_sai.h scope note (only 1 channel is actually used per Table 547).
#define S32K389_NUM_SAI 2
#define S32K3_SAI0_BASE 0x4036C000
#define S32K3_SAI1_BASE 0x404DC000
#define S32K3_SAI0_PARAM_RESET 0x00040304
#define S32K3_SAI1_PARAM_RESET 0x00040301
// UNVERIFIED PLACEHOLDER - see the S32K3_LPI2Cn_IRQ comment above; same
// caveat applies (interrupt map spreadsheet not available).
#define S32K3_SAI0_IRQ 220
#define S32K3_SAI1_IRQ 221

// FlexCAN
// Per S32K3xx_memory_map.xlsx (Peripherals sheet): S32K389 populates FlexCAN
// 0-11 (12 instances total), vs. S32K388 which only populates FlexCAN 0-7.
// Addresses below are taken directly from that sheet's Start/End address
// columns for the S32K389 column.
#define S32K389_CAN_COUNT   12
#define S32K3_FLEXCAN0_BASE      (S32K3_PERIPH_BASE + 0x304000) /* 0x40304000 */
#define S32K3_FLEXCAN1_BASE      (S32K3_PERIPH_BASE + 0x308000) /* 0x40308000 */
#define S32K3_FLEXCAN2_BASE      (S32K3_PERIPH_BASE + 0x30C000) /* 0x4030C000 */
#define S32K3_FLEXCAN3_BASE      (S32K3_PERIPH_BASE + 0x310000) /* 0x40310000 */
#define S32K3_FLEXCAN4_BASE      (S32K3_PERIPH_BASE + 0x314000) /* 0x40314000 */
#define S32K3_FLEXCAN5_BASE      (S32K3_PERIPH_BASE + 0x318000) /* 0x40318000 */
#define S32K3_FLEXCAN6_BASE      (S32K3_PERIPH_BASE + 0x31C000) /* 0x4031C000 */
#define S32K3_FLEXCAN7_BASE      (S32K3_PERIPH_BASE + 0x320000) /* 0x40320000 */
#define S32K3_FLEXCAN8_BASE      0x40570000  /* S32K389-only */
#define S32K3_FLEXCAN9_BASE      0x40574000  /* S32K389-only */
#define S32K3_FLEXCAN10_BASE     0x40578000  /* S32K389-only */
#define S32K3_FLEXCAN11_BASE     0x4057C000  /* S32K389-only */
 
#define S32K3_FLEXCAN0_MB_IRQ    110
#define S32K3_FLEXCAN1_MB_IRQ    114
#define S32K3_FLEXCAN2_MB_IRQ    117
#define S32K3_FLEXCAN3_MB_IRQ    120
#define S32K3_FLEXCAN4_MB_IRQ    122
#define S32K3_FLEXCAN5_MB_IRQ    124
/*
* Verified against S32K3xx_interrupt_map.xlsx ("Interrupts" sheet, S32K389
* column). Each FlexCAN instance has multiple IRQ lines (Bus Off, MB line 0,
* MB line 32, MB line 64...); to match the convention already used for
* instances 0-5 above, these use the "Message Buffer Interrupt line 0" IRQ
* for each instance (i.e. the "_1" row for FlexCANn in that sheet).
*/
#define S32K3_FLEXCAN6_MB_IRQ    126
#define S32K3_FLEXCAN7_MB_IRQ    128
#define S32K3_FLEXCAN8_MB_IRQ    60
#define S32K3_FLEXCAN9_MB_IRQ    75
#define S32K3_FLEXCAN10_MB_IRQ   104
#define S32K3_FLEXCAN11_MB_IRQ   164
 
// Boot / clock-gen state
//
// NOTE ON NAMING (verified against manual chapter 46 "Mode Entry Module
// (MC_ME)" and S32K3xx_memory_map.xlsx):
//   - The real MC_ME peripheral's base address is 402D_C000h (manual
//     section 46.7.1 states this explicitly). That is what used to be
//     called S32K3_BOOT_STATUS_BASE in this file - it was the correct
//     address all along, just mislabeled.
//   - The address range 0x402D0000-0x402DBFFF (48 KB) that used to be
//     labeled S32K3_MC_ME_BASE/SIZE does NOT correspond to real MC_ME at
//     all. Per the memory map spreadsheet, that range actually belongs to
//     FIRC (0x402D0000), FXOSC (0x402D4000), and MC_CGM (0x402D8000) - three
//     separate clock-generation peripherals. It's kept here as a generic
//     read/write register stub (not a real model of those three modules)
//     so firmware probing those addresses doesn't fault.
#define S32K3_CLKGEN_STUB_BASE   0x402D0000  // covers FIRC/FXOSC/MC_CGM ranges
#define S32K3_CLKGEN_STUB_SIZE   0xC000      // 48KB, ends exactly where real MC_ME starts
#define S32K3_MC_ME_BASE         0x402DC000  // real MC_ME base per manual 46.7.1
#define S32K3_MC_ME_SIZE         0x4000      // 16KB per memory map spreadsheet
/*
* Offsets below are real MC_ME register offsets (see manual 46.7.1 "MC_ME
* memory map"), renamed from their previous generic "boot status" names.
* The values returned for them are still simplified stand-ins used to get
* guest firmware clock-ready checks to pass at boot - NOT the datasheet
* reset values - kept behaviorally unchanged from the original model so as
* not to alter existing boot behavior.
*/
#define S32K3_MC_ME_PRTN1_COFB0_STAT   0x310  // real reset value: 0x5E3F_0007
#define S32K3_MC_ME_PRTN2_PUPD         0x504  // real reset value: 0x0000_0000
#define S32K3_MC_ME_PRTN2_COFB0_STAT   0x510  // real reset value: 0x0600_000F
#define S32K3_MC_ME_CLOCK_READY_BIT    BIT(24) // simplified stand-in, not a real MC_ME bit
 
typedef struct S32K389State {
  MachineState parent_obj;
 
  ARMv7MState armv7m;
  // Cores 1-3 (CM7_1/CM7_2/CM7_3) - see S32K389_NUM_CORES comment above.
  ARMv7MState core1;
  ARMv7MState core2;
  ARMv7MState core3;
  // Per-core private memory container (system_memory alias + this core's
  // own ITCM/DTCM overlaid at the shared local addresses) for cores 1-3.
  // Core 0 keeps using system_memory directly, unchanged from before.
  MemoryRegion core1_mem;
  MemoryRegion core2_mem;
  MemoryRegion core3_mem;
  MemoryRegion core1_itcm, core1_dtcm, core1_dtcm_stack;
  MemoryRegion core2_itcm, core2_dtcm, core2_dtcm_stack;
  MemoryRegion core3_itcm, core3_dtcm, core3_dtcm_stack;
  MemoryRegion stcu2;
  uint32_t stcu2_bstart;
  uint32_t stcu2_algosel;

  Clock* sysclk;
 
  DeviceState* uart;
  DeviceState* flexio;
  DeviceState* lpspi[S32K389_NUM_LPSPI];
  DeviceState* lpi2c[S32K389_NUM_LPI2C];
  DeviceState* swt[S32K389_NUM_SWT];
  DeviceState* crc;
  DeviceState* adc[S32K389_NUM_ADC];
  DeviceState* emios[S32K389_NUM_EMIOS];
  DeviceState* edma;
  NPCMGMACState gmac[S32K389_GMAC_COUNT];
  DeviceState* qspi;
  DeviceState* sai[S32K389_NUM_SAI];
  DeviceState *flexcan[S32K389_CAN_COUNT];
  CanBusState *canbus[S32K389_CAN_COUNT];
 
  MemoryRegion itcm;
  MemoryRegion dtcm;
  MemoryRegion dtcm_stack;
  MemoryRegion flash0;
  MemoryRegion flash1;
  MemoryRegion flash2;
  MemoryRegion flash3;
  MemoryRegion flash4;
  MemoryRegion flash5;
  MemoryRegion flash6;
  MemoryRegion flash7;
  MemoryRegion Dflash;
  MemoryRegion UNVMflash;
 
  MemoryRegion sram_standby;
  MemoryRegion sram0;
  MemoryRegion sram1;
  MemoryRegion sram2;
  MemoryRegion sram3;
 
  MemoryRegion mc_me;         // real MC_ME peripheral (0x402DC000, switch-based ops)
  MemoryRegion clkgen_stub;   // generic stub for FIRC/FXOSC/MC_CGM range (0x402D0000)
  MemoryRegion mscm;          // real MSCM aperture (0x40260000)
  uint32_t clkgen_regs[S32K3_CLKGEN_STUB_SIZE / sizeof(uint32_t)];
} S32K389State;
 
#endif
 
