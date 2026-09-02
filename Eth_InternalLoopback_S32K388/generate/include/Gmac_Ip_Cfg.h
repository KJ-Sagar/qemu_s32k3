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

#ifndef GMAC_IP_CFG_H
#define GMAC_IP_CFG_H

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
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Gmac_Ip_VS_0_PBcfg.h"

#include "Std_Types.h"
#include "Reg_eSys.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define GMAC_IP_CFG_VENDOR_ID                    43
#define GMAC_IP_CFG_AR_RELEASE_MAJOR_VERSION     4
#define GMAC_IP_CFG_AR_RELEASE_MINOR_VERSION     9
#define GMAC_IP_CFG_AR_RELEASE_REVISION_VERSION  0
#define GMAC_IP_CFG_SW_MAJOR_VERSION             7
#define GMAC_IP_CFG_SW_MINOR_VERSION             0
#define GMAC_IP_CFG_SW_PATCH_VERSION             1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Gmac_Ip_VS_0_PBcfg.h */
#if (GMAC_IP_CFG_VENDOR_ID != GMAC_IP_VS_0_PBCFG_VENDOR_ID)
    #error "Gmac_Ip_Cfg.h and Gmac_Ip_VS_0_PBcfg.h have different vendor ids"
#endif
#if ((GMAC_IP_CFG_AR_RELEASE_MAJOR_VERSION    != GMAC_IP_VS_0_PBCFG_AR_RELEASE_MAJOR_VERSION) || \
     (GMAC_IP_CFG_AR_RELEASE_MINOR_VERSION    != GMAC_IP_VS_0_PBCFG_AR_RELEASE_MINOR_VERSION) || \
     (GMAC_IP_CFG_AR_RELEASE_REVISION_VERSION != GMAC_IP_VS_0_PBCFG_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Gmac_Ip_Cfg.h and Gmac_Ip_VS_0_PBcfg.h are different"
#endif
#if ((GMAC_IP_CFG_SW_MAJOR_VERSION != GMAC_IP_VS_0_PBCFG_SW_MAJOR_VERSION) || \
     (GMAC_IP_CFG_SW_MINOR_VERSION != GMAC_IP_VS_0_PBCFG_SW_MINOR_VERSION) || \
     (GMAC_IP_CFG_SW_PATCH_VERSION != GMAC_IP_VS_0_PBCFG_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Gmac_Ip_Cfg.h and Gmac_Ip_VS_0_PBcfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Checks against Std_Types.h */
    #if ((GMAC_IP_CFG_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
         (GMAC_IP_CFG_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AUTOSAR Version Numbers of Gmac_Ip_Cfg.h and Std_Types.h are different"
    #endif
    /* Checks against Reg_eSys.h */
    #if ((GMAC_IP_CFG_AR_RELEASE_MAJOR_VERSION != REG_ESYS_AR_RELEASE_MAJOR_VERSION) || \
         (GMAC_IP_CFG_AR_RELEASE_MINOR_VERSION != REG_ESYS_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AUTOSAR Version Numbers of Gmac_Ip_Cfg.h and Reg_eSys.h are different"
    #endif
#endif
/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
#define GMAC_CONFIG_EXT \
    GMAC_CONFIG_VS_0_PB 

#define GMAC_IP_DEV_ERROR_DETECT            (STD_OFF)

#define GMAC_TIMEOUT_TYPE                (OSIF_COUNTER_DUMMY)

#define GMAC_TIMEOUT_VALUE_US            (1000U)

#define GMAC_ENABLE_USER_MODE_SUPPORT    (STD_OFF)

#ifndef MCAL_ENABLE_USER_MODE_SUPPORT
    #if (STD_ON == GMAC_ENABLE_USER_MODE_SUPPORT)
        #error MCAL_ENABLE_USER_MODE_SUPPORT is not enabled. For running GMAC in user mode, MCAL_ENABLE_USER_MODE_SUPPORT needs to be defined.
    #endif /* (STD_ON == GMAC_ENABLE_USER_MODE_SUPPORT */
#endif /* ifndef MCAL_ENABLE_USER_MODE_SUPPORT */

#if ((STD_ON == GMAC_ENABLE_USER_MODE_SUPPORT) && defined(MCAL_GMAC_REG_PROT_AVAILABLE))
    #if (STD_ON == MCAL_GMAC_REG_PROT_AVAILABLE)
        #define GMAC_SET_USER_ACCESS_ALLOWED_AVAILABLE      (STD_ON)
    #else
        #define GMAC_SET_USER_ACCESS_ALLOWED_AVAILABLE      (STD_OFF)
    #endif
#else
    #define GMAC_SET_USER_ACCESS_ALLOWED_AVAILABLE      (STD_OFF)
#endif

/* @brief Enables / Disables the allocation of the TX data buffers. */
#define GMAC_IP_HAS_EXTERNAL_TX_BUFFERS  (STD_OFF)

#if (STD_ON == GMAC_IP_HAS_EXTERNAL_TX_BUFFERS)
    /* @brief Array of the feature of external buffers support indexed at controller level. */
    #define GMAC_IP_INST_HAS_EXTERNAL_TX_BUFFERS  {(boolean) FALSE, (boolean) FALSE}
#endif

/*! @brief Enables / Disables Layer 3 and Layer 4 Filter for received packets */
#define GMAC_IP_HAS_RX_L3_L4_FILTERS  (STD_OFF)

#if (STD_ON == GMAC_IP_HAS_RX_L3_L4_FILTERS)
/*! @brief Array of the feature of Layer 3 and Layer 4 Filter support indexed at controller level */
    #define GMAC_IP_INST_HAS_RX_L3_L4_FILTERS  {(boolean) FALSE, (boolean) FALSE}
#endif

/*! @brief Enables/Disables internal cache management */
#define  GMAC_HAS_CACHE_MANAGEMENT  (STD_OFF)
/*! @brief Enables / Disables the feature of Pulse Per Second support. */
#define  GMAC_IP_PPS_OUTPUT_SUPPORT (STD_OFF)

/*! @brief Enables / Disables the feature of Low Power Idle mode. */
#define  GMAC_IP_LPI_ENABLE         (STD_OFF)

/*! @brief Enables / Disables the combined interrupt */
#define  GMAC_IP_COMBINED_IRQ       (STD_OFF)

/*! @brief Enables/Disables receive split header feature. */
#define GMAC_IP_RX_HEADER_SPLIT                 (STD_OFF)
/*! @brief Enables / Disables the feature of configuring the dma priorities for GMAC */
#define GMAC_IP_DMA_PRIORITY_CONFIGURATION_ENABLE     (STD_OFF)
/*! @brief Enables / Disables the feature of using scatter gather feature for both TX and RX */
#define GMAC_IP_SCATTER_GATHER_ENABLE (STD_OFF)
/*! @brief Enables/Disables Frame Preemption feature. */
#define GMAC_IP_FRAME_PREEMPTION_ENABLE               (STD_OFF)
/*! @brief Enables / Disables MAC Tx Rx Clock Mux Bypass */
#define GMAC_IP_MAC_TXRX_CLK_MUX_BYPASS     (STD_OFF)
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/* Forward GMAC structure declarations */
struct sGmac_Ip_StateType;
struct sGmac_Ip_ConfigType;
struct sGmac_Ip_RxRingConfigType;
struct sGmac_Ip_TxRingConfigType;
struct sGmac_Ip_TxTimeAwareShaper;
#if (STD_ON == GMAC_IP_PPS_OUTPUT_SUPPORT)
struct sGmac_Ip_FlexiblePPSOutput;
#endif
#if (STD_ON == GMAC_IP_HAS_RX_L3_L4_FILTERS)
struct sGmac_Ip_RxL3L4FilterConfigType;
#endif
#if defined(GMAC_IP_FRAME_PREEMPTION_ENABLE) && (STD_ON == GMAC_IP_FRAME_PREEMPTION_ENABLE)
struct sGmac_Ip_FramePreemption;
#endif

/**
* @brief   The structure contains the hardware controller configuration type.
*/
typedef struct sGmac_CtrlConfigType
{
    struct sGmac_Ip_StateType                 *Gmac_pCtrlState;
    const struct sGmac_Ip_ConfigType          *Gmac_pCtrlConfig;
    const struct sGmac_Ip_RxRingConfigType    *Gmac_paCtrlRxRingConfig;
    const struct sGmac_Ip_TxRingConfigType    *Gmac_paCtrlTxRingConfig;
    const uint8                               *Gmac_pau8CtrlPhysAddr;
    const struct sGmac_Ip_TxTimeAwareShaper   *Gmac_pCtrlTxTimeAwareShaper;
#if (STD_ON == GMAC_IP_HAS_RX_L3_L4_FILTERS)
    const struct sGmac_Ip_RxL3L4FilterConfigType   *Gmac_paCtrlRxL3L4FilterConfig;
#endif
#if defined(GMAC_IP_FRAME_PREEMPTION_ENABLE) && (STD_ON == GMAC_IP_FRAME_PREEMPTION_ENABLE)
    const struct sGmac_Ip_FramePreemption          *Gmac_pCtrlFramePreemption;
#endif
} Gmac_CtrlConfigType;

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* GMAC_IP_CFG_H */

