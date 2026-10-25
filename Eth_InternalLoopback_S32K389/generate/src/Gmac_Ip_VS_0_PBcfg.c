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

/**
*   @file
*   @implements Gmac_Ip_PBcfg.c_Artifact
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
#include "Gmac_Ip_Types.h"
#include "Gmac_Ip_Cfg.h"
#include "Mcal.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define GMAC_IP_VS_0_PBCFG_VENDOR_ID_C                     43
#define GMAC_IP_VS_0_PBCFG_AR_RELEASE_MAJOR_VERSION_C      4
#define GMAC_IP_VS_0_PBCFG_AR_RELEASE_MINOR_VERSION_C      9
#define GMAC_IP_VS_0_PBCFG_AR_RELEASE_REVISION_VERSION_C   0
#define GMAC_IP_VS_0_PBCFG_SW_MAJOR_VERSION_C              7
#define GMAC_IP_VS_0_PBCFG_SW_MINOR_VERSION_C              0
#define GMAC_IP_VS_0_PBCFG_SW_PATCH_VERSION_C              1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Gmac_Ip_Types.h */
#if (GMAC_IP_VS_0_PBCFG_VENDOR_ID_C != GMAC_IP_TYPES_VENDOR_ID)
    #error "Gmac_Ip_VS_0_PBcfg.c and Gmac_Ip_Types.h have different vendor ids"
#endif
#if ((GMAC_IP_VS_0_PBCFG_AR_RELEASE_MAJOR_VERSION_C    != GMAC_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (GMAC_IP_VS_0_PBCFG_AR_RELEASE_MINOR_VERSION_C    != GMAC_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (GMAC_IP_VS_0_PBCFG_AR_RELEASE_REVISION_VERSION_C != GMAC_IP_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Gmac_Ip_VS_0_PBcfg.c and Gmac_Ip_Types.h are different"
#endif
#if ((GMAC_IP_VS_0_PBCFG_SW_MAJOR_VERSION_C != GMAC_IP_TYPES_SW_MAJOR_VERSION) || \
     (GMAC_IP_VS_0_PBCFG_SW_MINOR_VERSION_C != GMAC_IP_TYPES_SW_MINOR_VERSION) || \
     (GMAC_IP_VS_0_PBCFG_SW_PATCH_VERSION_C != GMAC_IP_TYPES_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Gmac_Ip_VS_0_PBcfg.c and Gmac_Ip_Types.h are different"
#endif

/* Checks against Gmac_Ip_Cfg.h */
#if (GMAC_IP_VS_0_PBCFG_VENDOR_ID_C != GMAC_IP_CFG_VENDOR_ID)
    #error "Gmac_Ip_VS_0_PBcfg.c and Gmac_Ip_Cfg.h have different vendor ids"
#endif
#if ((GMAC_IP_VS_0_PBCFG_AR_RELEASE_MAJOR_VERSION_C    != GMAC_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (GMAC_IP_VS_0_PBCFG_AR_RELEASE_MINOR_VERSION_C    != GMAC_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (GMAC_IP_VS_0_PBCFG_AR_RELEASE_REVISION_VERSION_C != GMAC_IP_CFG_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Gmac_Ip_VS_0_PBcfg.c and Gmac_Ip_Cfg.h are different"
#endif
#if ((GMAC_IP_VS_0_PBCFG_SW_MAJOR_VERSION_C != GMAC_IP_CFG_SW_MAJOR_VERSION) || \
     (GMAC_IP_VS_0_PBCFG_SW_MINOR_VERSION_C != GMAC_IP_CFG_SW_MINOR_VERSION) || \
     (GMAC_IP_VS_0_PBCFG_SW_PATCH_VERSION_C != GMAC_IP_CFG_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Gmac_Ip_VS_0_PBcfg.c and Gmac_Ip_Cfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Checks against Mcal.h */
    #if ((GMAC_IP_VS_0_PBCFG_AR_RELEASE_MAJOR_VERSION_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (GMAC_IP_VS_0_PBCFG_AR_RELEASE_MINOR_VERSION_C != MCAL_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AUTOSAR Version Numbers of Gmac_Ip_VS_0_PBcfg.c and Mcal.h are different"
    #endif
#endif

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
#define GMAC_MAC_ADDR_LENGTH        (6U)

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
#define ETH_43_GMAC_START_SEC_CODE
#include "Eth_43_GMAC_MemMap.h"

/*! @brief Channel callbacks external declarations */

#define ETH_43_GMAC_STOP_SEC_CODE
#include "Eth_43_GMAC_MemMap.h"

/*==================================================================================================
*                                      BUFFER DECLARATIONS
==================================================================================================*/
#define ETH_43_GMAC_START_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Eth_43_GMAC_MemMap.h"

VAR_ALIGN(extern Gmac_Ip_BufferDescriptorType GMAC_0_RxRing_0_DescBuffer[GMAC_0_MAX_RXBUFF_SUPPORTED], FEATURE_GMAC_BUFFDESCR_ALIGNMENT_BYTES)
VAR_ALIGN(extern uint8 GMAC_0_RxRing_0_DataBuffer[(GMAC_0_MAX_RXBUFF_SUPPORTED * GMAC_0_MAX_RXBUFFLEN_SUPPORTED)], FEATURE_GMAC_BUFF_ALIGNMENT_BYTES)
VAR_ALIGN(extern Gmac_Ip_BufferDescriptorType GMAC_0_TxRing_0_DescBuffer[GMAC_0_MAX_TXBUFF_SUPPORTED], FEATURE_GMAC_BUFFDESCR_ALIGNMENT_BYTES)
VAR_ALIGN(extern uint8 GMAC_0_TxRing_0_DataBuffer[(GMAC_0_MAX_TXBUFF_SUPPORTED * GMAC_0_MAX_TXBUFFLEN_SUPPORTED)], FEATURE_GMAC_BUFF_ALIGNMENT_BYTES)

#define ETH_43_GMAC_STOP_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Eth_43_GMAC_MemMap.h"

/*==================================================================================================
*                                   STATE STRUCTURE DECLARATIONS
==================================================================================================*/
#define ETH_43_GMAC_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Eth_43_GMAC_MemMap.h"

extern Gmac_Ip_StateType GMAC_0_StateStructure;
static Gmac_Ip_TxGateControl GMAC_0_aGateControlListPB_VS_0[1U]  =
{
    {
        /*.timeInterval = */0U,
        /*.gateControlFifo = */0U
    }
};

#define ETH_43_GMAC_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Eth_43_GMAC_MemMap.h"

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/
#define ETH_43_GMAC_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_43_GMAC_MemMap.h"


/*! @brief The MAC address(es) of the configured controller(s) */
static const uint8 GMAC_0_au8MacAddrPB_VS_0[GMAC_MAC_ADDR_LENGTH] = { 0x66U, 0x55U, 0x44U, 0x33U, 0x22U, 0x11U };

/*! @brief Reception ring configuration structures */
static const Gmac_Ip_RxRingConfigType GMAC_0_aRxRingConfigPB_VS_0[1U] =
{
    /* The configuration structure for Rx Ring 0 */
    {
        /*.ringDesc = */GMAC_0_RxRing_0_DescBuffer,
        /*.callback = */NULL_PTR,
        /*.buffer = */GMAC_0_RxRing_0_DataBuffer,
        /*.interrupts = */(uint32)0U,
        /*.bufferLen = */64U,
        /*.ringSize = */4U,
        /*.MTLQueueSize = */256U,
        /*.priorityMask = */0U,
		/*.dmaBurstLength = */8U
    }
};

/*! @brief Transmission ring configuration structures */
static const Gmac_Ip_TxRingConfigType GMAC_0_aTxRingConfigPB_VS_0[1U] =
{
    /* The configuration structure for Tx Ring 0 */
    {
        /*.weight = */0U,
        /*.idleSlopeCredit = */0U,
        /*.sendSlopeCredit = */0U,
        /*.hiCredit = */0U,
        /*.loCredit = */0,
        /*.TxSelecAlgoType = */GMAC_TRANSMISSION_SELECTION_UNSHAPED,
        /*.ringDesc = */GMAC_0_TxRing_0_DescBuffer,
        /*.callback = */NULL_PTR,
        /*.buffer = */GMAC_0_TxRing_0_DataBuffer,
        /*.interrupts = */(uint32)0U,
        /*.bufferLen = */64U,
        /*.ringSize = */4U,
        /*.MTLQueueSize = */256U,
        /*.priorityMask = */0U,
        /*.dmaBurstLength = */8U,
        /*.queueOpMode = */GMAC_OP_MODE_DCB_GEN
#ifdef GMAC_IP_DMA_PRIORITY_CONFIGURATION_ENABLE
    #if (GMAC_IP_DMA_PRIORITY_CONFIGURATION_ENABLE == STD_ON)
        ,/*.TransmitChannelWeight = */0U
    #endif
#endif
    }
};

/*! @brief Module configuration structures */
static const Gmac_Ip_ConfigType GMAC_0_InitConfigPB_VS_0 =
{
    /*.rxRingCount = */1U,
    /*.txRingCount = */1U,
#if (FEATURE_GMAC_ASP_ALL || FEATURE_GMAC_ASP_ECC)
    /*.safetyInterrupts = */0U,
    /*.safetyCallback = */NULL_PTR,
#endif
    /*.interrupts = */0U,
    /*.callback = */NULL_PTR,
    /*.miiMode = */GMAC_MII_MODE,
    /*.txSchedAlgo = */GMAC_SCHED_ALGO_SP,
    /*.speed = */GMAC_SPEED_100M,
    /*.duplex = */GMAC_FULL_DUPLEX,
    /*.macConfig = */0U | (uint32)GMAC_MAC_CONFIG_CRC_STRIPPING | (uint32)GMAC_MAC_CONFIG_AUTO_PAD | (uint32)GMAC_MAC_CONFIG_LOOPBACK | ((uint32)0U << GMAC_MAC_CONFIGURATION_IPG_SHIFT),
    /*.extendedMacConfig = */ (uint32)0U,
#if (STD_ON == GMAC_IP_RX_HEADER_SPLIT)
    /*.extendedMacConfig1 = */ (uint32)0U,
#endif
    /*.macPktFilterConfig = */0U | (uint32)GMAC_PKT_FILTER_HASH_OR_PERFECT_FILTER,
    /*.enableCtrl = */(boolean)FALSE,
    /* DMA Burst configuration */
    {
        /* .EnFixedBurstLength */ FALSE
    }
#ifdef GMAC_IP_DMA_PRIORITY_CONFIGURATION_ENABLE
    #if (GMAC_IP_DMA_PRIORITY_CONFIGURATION_ENABLE == STD_ON)
    ,/*.DMATransmitPriority = */ FALSE
    ,/*.DMAArbitrationScheme = */  GMAC_DMA_FIXED_PRIORITY
    ,/*.DMATransmitArbitrationAlgorithm = */ GMAC_DMA_TX_FIXED_PRIORITY
    ,/*.DMAPriorityRatio = */ R_1_1
    #endif
#endif
#ifdef GMAC_IP_LPI_ENABLE
    #if (STD_ON == GMAC_IP_LPI_ENABLE)
    ,/*.LPILSTimer = */ 0U
    ,/*.LPITWTimer = */  0U
    ,/*.LPITWTimer = */ 0U
    ,/*.LPIConfig = */ 0U
    ,/*.LPICallback = */ NULL_PTR
    #endif
#endif
#if (STD_ON == GMAC_IP_HAS_RX_L3_L4_FILTERS)
    ,/*.RxL3L4FilterCount = */0U
#endif
};

static const Gmac_Ip_TxTimeAwareShaper GMAC_0_pTxTimeShaperPB_VS_0 =
{
    /*.baseTimeSecond = */0U,
    /*.baseTimenanoSecond = */0U,
    /*.cycleTimeSecond = */0U,
    /*.cycleTimeNanoSecond = */0U,
    /*.extendedTime = */0U,
    /*.gateControlListDepth = */0U,
    /*.GateControlList = */&GMAC_0_aGateControlListPB_VS_0[0U]
};

#if (STD_ON == GMAC_IP_HAS_RX_L3_L4_FILTERS)
static const Gmac_Ip_RxL3L4FilterConfigType GMAC_0_aRxL3L4FilterConfigPB_VS_0[1U]  =
{
    {
        /*.DMAChannel = */0U,
        /*.RxQueueMap = */{0U},
        /*.Layer3IPv4DestBitsMatch = */0U,
        /*.Layer3IPv4SourceBitsMatch = */0U,
        /*.Layer3IPv6BitsMatch = */0U,
        /*.Layer3IPv4SourceAddress = */{ 0U, 0U, 0U, 0U },
        /*.Layer3IPv4DestinationAddress = */{ 0U, 0U, 0U, 0U },
        /*.Layer3IPv6SourceAddress = */{ 0x0U, 0x0U, 0x0U, 0x0U, 0x0U, 0x0U, 0x0U, 0x0U },
        /*.Layer3IPv6DestinationAddress = */{ 0x0U, 0x0U, 0x0U, 0x0U, 0x0U, 0x0U, 0x0U, 0x0U },
        /*.Layer4SourcePortNumber = */0U,
        /*.Layer4DestinationPortNumber = */0U,
        /*.MacL3L4FilterEnable = */0U,
    }
};
#endif


#define ETH_43_GMAC_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_43_GMAC_MemMap.h"
/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/
#define ETH_43_GMAC_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_43_GMAC_MemMap.h"

const Gmac_CtrlConfigType Gmac_aCtrlConfigPB_VS_0[1U] =
{
    /* The configuration structure for Gmac_aCtrlConfig[0U] */
    {
        &GMAC_0_StateStructure,
        &GMAC_0_InitConfigPB_VS_0,
        &GMAC_0_aRxRingConfigPB_VS_0[0U],
        &GMAC_0_aTxRingConfigPB_VS_0[0U],
        &GMAC_0_au8MacAddrPB_VS_0[0U],
        &GMAC_0_pTxTimeShaperPB_VS_0
#if (STD_ON == GMAC_IP_HAS_RX_L3_L4_FILTERS)
        ,&GMAC_0_aRxL3L4FilterConfigPB_VS_0[0U]
#endif
#if defined(GMAC_IP_FRAME_PREEMPTION_ENABLE) && (STD_ON == GMAC_IP_FRAME_PREEMPTION_ENABLE)
        ,NULL_PTR
#endif
    }
};

#define ETH_43_GMAC_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_43_GMAC_MemMap.h"

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/


/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

