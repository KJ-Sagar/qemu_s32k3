#ifndef HW_ARM_S32K388_H
#define HW_ARM_S32K388_H

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

#define TYPE_S32K388 MACHINE_TYPE_NAME("s32k388")
OBJECT_DECLARE_SIMPLE_TYPE(S32K388State, S32K388)

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
#define FLASH_SIZE                  0x00822000
#define INT_CODE_FLASH0_BASE        0x00400000
#define INT_CODE_FLASH0_SIZE        0x00200000  // 2 MB
/* The FlexCAN example firmware places its reset vector table at 0x00402000. */
#define INT_CODE_FLASH0_CORE0_VTOR  0x00402000
#define INT_CODE_FLASH1_BASE        0x00600000
#define INT_CODE_FLASH1_SIZE        0x00200000  // 2 MB
#define INT_CODE_FLASH2_BASE        0x00800000
#define INT_CODE_FLASH2_SIZE        0x00200000  // 2 MB
#define INT_CODE_FLASH3_BASE        0x00A00000
#define INT_CODE_FLASH3_SIZE        0x00200000  // 2 MB
#define INT_DATA_FLASH_BASE         0x10000000
#define INT_DATA_FLASH_SIZE         0x00020000  // 128 KB
#define INT_UTEST_NVM_FLASH_BASE    0x1B000000
#define INT_UTEST_NVM_FLASH_SIZE    0x00002000  // 8 KB

// SRAM
#define SRAM_SIZE                   0xC0000
#define INT_SRAM_STANDBY_BASE       0x20400000  // SRAM_standby, SPLIT FROM SRAM0
#define INT_SRAM_STANDBY_SIZE       0x10000     // 64KB
#define INT_SRAM_0_BASE             0x20410000
#define INT_SRAM_0_SIZE             0x30000     // 256KB-64KB = 192KB
#define INT_SRAM_1_BASE             0x20440000
#define INT_SRAM_1_SIZE             0x40000     // 256KB
#define INT_SRAM_2_BASE             0x20480000
#define INT_SRAM_2_SIZE             0x40000     // 256KB

// Peripheral definitions
#define S32K3_PERIPH_BASE           0x40000000

// Early boot support stubs used by NXP RTD initialization
#define S32K3_MSCM_BASE             0x40260000
#define S32K3_MSCM_SIZE             0x4000
#define S32K3_RTC_BASE              0x40288000
#define S32K3_RTC_SIZE              0x4000
#define S32K3_MC_RGM_BASE           0x4028C000
#define S32K3_MC_RGM_SIZE           0x4000
#define S32K3_DCM_BASE              0x402AC000
#define S32K3_DCM_SIZE              0x4000
#define S32K3_SXOSC_BASE            0x402CC000
#define S32K3_SXOSC_SIZE            0x4000

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
#define S32K3_CONSOLE_LPUART_IRQ  144

// FlexIO instance used by the UART loopback example
#define S32K3_FLEXIO_BASE          0x40324000
#define S32K3_FLEXIO_IRQ           139

// LPSPI
#define S32K388_NUM_LPSPI 6
#define S32K3_LPSPI0_BASE (S32K3_PERIPH_BASE + 0x358000)  // 0x40358000
#define S32K3_LPSPI1_BASE (S32K3_PERIPH_BASE + 0x35C000)  // 0x4035C000
#define S32K3_LPSPI2_BASE (S32K3_PERIPH_BASE + 0x360000)  // 0x40360000
#define S32K3_LPSPI3_BASE (S32K3_PERIPH_BASE + 0x364000)  // 0x40364000
#define S32K3_LPSPI4_BASE (S32K3_PERIPH_BASE + 0x4BC000)  // 0x404BC000
#define S32K3_LPSPI5_BASE (S32K3_PERIPH_BASE + 0x4C0000)  // 0x404C0000
// LPSPI Interrupts
#define S32K3_LPSPI0_IRQ 165
#define S32K3_LPSPI1_IRQ 166
#define S32K3_LPSPI2_IRQ 167
#define S32K3_LPSPI3_IRQ 168
#define S32K3_LPSPI4_IRQ 169
#define S32K3_LPSPI5_IRQ 170

#define S32K388_NUM_LPI2C 2
#define S32K3_LPI2C0_BASE (S32K3_PERIPH_BASE + 0x350000)
#define S32K3_LPI2C1_BASE (S32K3_PERIPH_BASE + 0x354000)
#define S32K3_LPI2C0_IRQ 161
#define S32K3_LPI2C1_IRQ 162

#define S32K388_NUM_SWT 4
#define S32K3_SWT0_BASE 0x40270000
#define S32K3_SWT1_BASE 0x4046C000
#define S32K3_SWT2_BASE 0x40470000
#define S32K3_SWT3_BASE 0x40070000
#define S32K3_SWT0_IRQ 42
#define S32K3_SWT1_IRQ 43
#define S32K3_SWT2_IRQ 44
#define S32K3_SWT3_IRQ 58

#define S32K3_CRC_BASE 0x40380000

#define S32K388_NUM_ADC 3
#define S32K3_ADC0_BASE 0x400A0000
#define S32K3_ADC1_BASE 0x400A4000
#define S32K3_ADC2_BASE 0x400A8000
#define S32K3_ADC0_IRQ 180
#define S32K3_ADC1_IRQ 181
#define S32K3_ADC2_IRQ 182

#define S32K388_NUM_EMIOS 3
#define S32K3_EMIOS0_BASE 0x40088000
#define S32K3_EMIOS1_BASE 0x4008C000
#define S32K3_EMIOS2_BASE 0x40090000
#define S32K3_EMIOS0_IRQ 61
#define S32K3_EMIOS1_IRQ 69
#define S32K3_EMIOS2_IRQ 77

#define S32K3_EDMA_MGMT_BASE 0x4020C000
#define S32K3_EDMA_CH_BASE   0x40210000
#define S32K3_EDMA_IRQ_BASE  4

// FlexCAN
#define S32K388_CAN_COUNT   8
#define S32K3_FLEXCAN0_BASE      (S32K3_PERIPH_BASE + 0x304000) /* 0x40304000 */
#define S32K3_FLEXCAN1_BASE      (S32K3_PERIPH_BASE + 0x308000) /* 0x40308000 */
#define S32K3_FLEXCAN2_BASE      (S32K3_PERIPH_BASE + 0x30C000) /* 0x4030C000 */
#define S32K3_FLEXCAN3_BASE      (S32K3_PERIPH_BASE + 0x310000) /* 0x40310000 */
#define S32K3_FLEXCAN4_BASE      (S32K3_PERIPH_BASE + 0x314000) /* 0x40314000 */
#define S32K3_FLEXCAN5_BASE      (S32K3_PERIPH_BASE + 0x318000) /* 0x40318000 */
#define S32K3_FLEXCAN6_BASE      (S32K3_PERIPH_BASE + 0x31C000) /* 0x4031C000 */
#define S32K3_FLEXCAN7_BASE      (S32K3_PERIPH_BASE + 0x320000) /* 0x40320000 */
#define S32K3_FLEXCAN0_MB_IRQ    110
#define S32K3_FLEXCAN1_MB_IRQ    114
#define S32K3_FLEXCAN2_MB_IRQ    117
#define S32K3_FLEXCAN3_MB_IRQ    120
#define S32K3_FLEXCAN4_MB_IRQ    122
#define S32K3_FLEXCAN5_MB_IRQ    124
#define S32K3_FLEXCAN6_MB_IRQ    126
#define S32K3_FLEXCAN7_MB_IRQ    128

// GMAC Ethernet
#define S32K388_GMAC_COUNT       2
#define S32K388_GMAC_DMA_CHANNELS NPCM_GMAC_DMA_CHANNELS
#define S32K388_GMAC0_BASE       0x40484000
#define S32K388_GMAC1_BASE       0x40488000
#define S32K388_GMAC0_IRQ        224
#define S32K388_GMAC1_IRQ        171
#define S32K388_GMAC0_CH0_TX_IRQ 225
#define S32K388_GMAC0_CH0_RX_IRQ 226
#define S32K388_GMAC0_CH1_TX_IRQ 227
#define S32K388_GMAC0_CH1_RX_IRQ 228
#define S32K388_GMAC0_CH2_TX_IRQ 229
#define S32K388_GMAC0_CH2_RX_IRQ 230
#define S32K388_GMAC1_CH0_TX_IRQ 172
#define S32K388_GMAC1_CH0_RX_IRQ 233
#define S32K388_GMAC1_CH1_TX_IRQ 234
#define S32K388_GMAC1_CH1_RX_IRQ 235
#define S32K388_GMAC1_CH2_TX_IRQ 236
#define S32K388_GMAC1_CH2_RX_IRQ 237

#define S32K3_QSPI_BASE      0x404CC000
#define S32K3_QSPI_ARDB_BASE 0x68000000
#define S32K3_QSPI_IRQ       173

#define S32K388_NUM_SAI 2
#define S32K3_SAI0_BASE 0x4036C000
#define S32K3_SAI1_BASE 0x404DC000
#define S32K3_SAI0_PARAM_RESET 0x00040304
#define S32K3_SAI1_PARAM_RESET 0x00040301
#define S32K3_SAI0_IRQ 174
#define S32K3_SAI1_IRQ 175

// Boot state
#define S32K3_MC_ME_BASE        0x402D0000
#define S32K3_MC_ME_SIZE        0x20000
#define S32K3_BOOT_STATUS_BASE   0x402DC000
#define S32K3_BOOT_STATUS_SIZE   0x1000
#define S32K3_BOOT_STATUS_GS     0x310
#define S32K3_BOOT_STATUS_PCS    0x510
#define S32K3_BOOT_STATUS_CTL_STAT 0x504
#define S32K3_BOOT_STATUS_CLOCK_READY BIT(24)

typedef struct S32K388State {
  MachineState parent_obj;

  ARMv7MState armv7m;

  Clock* sysclk;

  DeviceState* uart;
  DeviceState* flexio;
  DeviceState* lpspi[S32K388_NUM_LPSPI];
  DeviceState* lpi2c[S32K388_NUM_LPI2C];
  DeviceState* swt[S32K388_NUM_SWT];
  DeviceState* crc;
  DeviceState* adc[S32K388_NUM_ADC];
  DeviceState* emios[S32K388_NUM_EMIOS];
  DeviceState* edma;
  DeviceState *flexcan[S32K388_CAN_COUNT];
  CanBusState *canbus[S32K388_CAN_COUNT];
  NPCMGMACState gmac[S32K388_GMAC_COUNT];
  DeviceState* qspi;
  DeviceState* sai[S32K388_NUM_SAI];

  MemoryRegion itcm;
  MemoryRegion dtcm;
  MemoryRegion dtcm_stack;
  MemoryRegion C0flash;
  MemoryRegion C1flash;
  MemoryRegion C2flash;
  MemoryRegion C3flash;
  MemoryRegion Dflash;
  MemoryRegion UNVMflash;

  MemoryRegion sram_standby;
  MemoryRegion sram0;
  MemoryRegion sram1;
  MemoryRegion sram2;

  MemoryRegion boot_status;
  MemoryRegion mc_me;
  MemoryRegion mscm;
  MemoryRegion rtc;
  MemoryRegion mc_rgm;
  MemoryRegion dcm;
  MemoryRegion sxosc;
  uint32_t mc_me_regs[S32K3_MC_ME_SIZE / sizeof(uint32_t)];
} S32K388State;

#endif
