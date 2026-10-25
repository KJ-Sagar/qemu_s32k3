/*==================================================================================================
*   Project              : RTD AUTOSAR 4.9
*   Platform             : CORTEXM
*   Peripheral           : GMAC
*   Dependencies         : none
*
*   Autosar Version      : 4.9.0
*   Autosar Revision     : ASR_REL_4_9_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 7.0.1
*   Build Version        : S32K3_RTD_7_0_1_D2602_ASR_REL_4_9_REV_0000_20260206
*
*   Copyright 2020 - 2026 NXP
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be 
*   used strictly in accordance with the applicable license terms. By expressly 
*   accepting such terms or by downloading, installing, activating and/or otherwise 
*   using the software, you are agreeing that you have read, and that you agree to 
*   comply with and are bound by, such license terms. If you do not agree to be 
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef GMAC_IP_DEVICE_REGISTERS_H
#define GMAC_IP_DEVICE_REGISTERS_H

/**
*   @file
*
*   @addtogroup GMAC_DRIVER_CONFIGURATION GMAC Driver Configuration
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"
#include "S32K389_GMAC.h" 
#include "S32K389_DCM_GPR.h" 
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define GMAC_IP_DEVICE_REGISTERS_VENDOR_ID                    43
#define GMAC_IP_DEVICE_REGISTERS_AR_RELEASE_MAJOR_VERSION     4
#define GMAC_IP_DEVICE_REGISTERS_AR_RELEASE_MINOR_VERSION     9
#define GMAC_IP_DEVICE_REGISTERS_AR_RELEASE_REVISION_VERSION  0
#define GMAC_IP_DEVICE_REGISTERS_SW_MAJOR_VERSION             7
#define GMAC_IP_DEVICE_REGISTERS_SW_MINOR_VERSION             0
#define GMAC_IP_DEVICE_REGISTERS_SW_PATCH_VERSION             1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Checks against Std_Types.h */
    #if ((GMAC_IP_DEVICE_REGISTERS_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
         (GMAC_IP_DEVICE_REGISTERS_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AUTOSAR Version Numbers of Gmac_Ip_Device_Registers.h and Std_Types.h are different"
    #endif
#endif
/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
/** @cond DRIVER_INTERNAL_USE_ONLY */
#define DMA_CH0_CONTROL_ADDR16              0x1100U
#define DMA_CH1_CONTROL_ADDR16              0x1180U
#define DMA_CH2_CONTROL_ADDR16              0x1200U
#define MTL_TXQ0_OPERATION_MODE_ADDR16      0x0D00U
#define MTL_TXQ1_OPERATION_MODE_ADDR16      0x0D40U
#define MTL_TXQ2_OPERATION_MODE_ADDR16      0x0D80U

typedef struct
{
  volatile uint32 DMA_CONTROL;
  volatile uint32 DMA_TX_CONTROL;
  volatile uint32 DMA_RX_CONTROL;
  volatile uint8 RESERVED_1[8];
  volatile uint32 DMA_TXDESC_LIST_ADDRESS;
  volatile uint8 RESERVED_2[4];
  volatile uint32 DMA_RXDESC_LIST_ADDRESS;
  volatile uint32 DMA_TXDESC_TAIL_POINTER;
  volatile uint8 RESERVED_3[4];
  volatile uint32 DMA_RXDESC_TAIL_POINTER;
  volatile uint32 DMA_TXDESC_RING_LENGTH;
  volatile uint32 DMA_RXDESC_RING_LENGTH;
  volatile uint32 DMA_INTERRUPT_ENABLE;
  volatile uint32 DMA_RX_INTERRUPT_WATCHDOG_TIMER;
  volatile uint32 DMA_SLOT_FUNCTION_CONTROL_STATUS;
  volatile uint8 RESERVED_4[4];
  volatile uint32 DMA_CURRENT_APP_TXDESC;
  volatile uint8 RESERVED_5[4];
  volatile uint32 DMA_CURRENT_APP_RXDESC;
  volatile uint8 RESERVED_6[4];
  volatile uint32 DMA_CURRENT_APP_TXBUFFER;
  volatile uint8 RESERVED_7[4];
  volatile uint32 DMA_CURRENT_APP_RXBUFFER;
  volatile uint32 DMA_STATUS;
  volatile uint32 DMA_MISS_FRAME_CNT;
  volatile uint32 DMA_RXP_ACCEPT_CNT;
  volatile uint32 DMA_RX_ERI_CNT;
  volatile uint8 RESERVED_8[16];
} Gmac_Ip_ChannelType;
/** @endcond */

/* @internal @brief Macro for different between header files */
    #define MAC_VLAN_TAG_DATA_REG       MAC_VLAN_TAG_DATA.MAC_VLAN_TAG_DATA
    #define MAC_VLAN_TAG_CTRL_REG       MAC_VLAN_TAG_CTRL
    #define MAC_VLAN_INCL_REG           MAC_VLAN_INCL.MAC_VLAN_INCL
    
/* @internal @brief Base addresses for the DMA channels */
    #define DEV_REG_GMAC_CH_BASE \
    { { \
        (Gmac_Ip_ChannelType *)(IP_GMAC_0_BASE + (uint32)DMA_CH0_CONTROL_ADDR16), \
        (Gmac_Ip_ChannelType *)(IP_GMAC_0_BASE + (uint32)DMA_CH1_CONTROL_ADDR16), \
        (Gmac_Ip_ChannelType *)(IP_GMAC_0_BASE + (uint32)DMA_CH2_CONTROL_ADDR16) \
    }, \
    { \
        (Gmac_Ip_ChannelType *)(IP_GMAC_1_BASE + (uint32)DMA_CH0_CONTROL_ADDR16), \
        (Gmac_Ip_ChannelType *)(IP_GMAC_1_BASE + (uint32)DMA_CH1_CONTROL_ADDR16), \
        (Gmac_Ip_ChannelType *)(IP_GMAC_1_BASE + (uint32)DMA_CH2_CONTROL_ADDR16) \
    } } \

    
/** @cond DRIVER_INTERNAL_USE_ONLY */
typedef struct
{
  volatile uint32 MTL_TXQ_OPERATION_MODE;
  volatile const uint32 MTL_TXQ_UNDERFLOW;
  volatile const uint32 MTL_TXQ_DEBUG;
  uint8 RESERVED_1[4];
  volatile uint32 MTL_TXQ_ETS_CONTROL;        /* Not available for Q0 */
  volatile const uint32 MTL_TXQ_ETS_STATUS;
  volatile uint32 MTL_TXQ_QUANTUM_WEIGHT;
  volatile uint32 MTL_TXQ_SENDSLOPECREDIT;    /* Not available for Q0 */
  volatile uint32 MTL_TXQ_HICREDIT;           /* Not available for Q0 */
  volatile uint32 MTL_TXQ_LOCREDIT;           /* Not available for Q0 */
  uint8 RESERVED_2[4];
  volatile uint32 MTL_Q_INTERRUPT_CONTROL_STATUS;
  volatile uint32 MTL_RXQ_OPERATION_MODE;
  volatile const uint32 MTL_RXQ_MISSED_PACKET_OVERFLOW_CNT;
  volatile const uint32 MTL_RXQ_DEBUG;
  volatile uint32 MTL_RXQ_CONTROL;
} Gmac_Ip_QueueType;
/** @endcond */

/*! @internal @brief Base addresses for the MTL queues */
        #define DEV_REG_GMAC_QUEUE_BASE \
        { { \
            (Gmac_Ip_QueueType *)(IP_GMAC_0_BASE + (uint32)MTL_TXQ0_OPERATION_MODE_ADDR16), \
            (Gmac_Ip_QueueType *)(IP_GMAC_0_BASE + (uint32)MTL_TXQ1_OPERATION_MODE_ADDR16), \
            (Gmac_Ip_QueueType *)(IP_GMAC_0_BASE + (uint32)MTL_TXQ2_OPERATION_MODE_ADDR16) \
        }, \
        { \
            (Gmac_Ip_QueueType *)(IP_GMAC_1_BASE + (uint32)MTL_TXQ0_OPERATION_MODE_ADDR16), \
            (Gmac_Ip_QueueType *)(IP_GMAC_1_BASE + (uint32)MTL_TXQ1_OPERATION_MODE_ADDR16), \
            (Gmac_Ip_QueueType *)(IP_GMAC_1_BASE + (uint32)MTL_TXQ2_OPERATION_MODE_ADDR16) \
        } } \

        /*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* GMAC_IP_DEVICE_REGISTERS_H */

