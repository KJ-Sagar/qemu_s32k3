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
*
*   @addtogroup ETH_43_GMAC_DRIVER_CONFIGURATION Ethernet Driver Configurations
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
#include "Eth_43_GMAC_Ipw_Cfg.h"
#include "Gmac_Ip_Cfg.h"
#include "Gmac_Ip_Features.h"

#if STD_ON == ETH_43_GMAC_DEM_EVENT_DETECT
    #include "Dem.h"
#endif
#if defined(GMAC_IP_MAC_TXRX_CLK_MUX_BYPASS) && (STD_ON == GMAC_IP_MAC_TXRX_CLK_MUX_BYPASS)
#include "Gmac_Ip_Device_Registers.h"
#endif

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ETH_43_GMAC_IPW_PBCFG_VS_0_VENDOR_ID_C                     43
#define ETH_43_GMAC_IPW_PBCFG_VS_0_AR_RELEASE_MAJOR_VERSION_C      4
#define ETH_43_GMAC_IPW_PBCFG_VS_0_AR_RELEASE_MINOR_VERSION_C      9
#define ETH_43_GMAC_IPW_PBCFG_VS_0_AR_RELEASE_REVISION_VERSION_C   0
#define ETH_43_GMAC_IPW_PBCFG_VS_0_SW_MAJOR_VERSION_C              7
#define ETH_43_GMAC_IPW_PBCFG_VS_0_SW_MINOR_VERSION_C              0
#define ETH_43_GMAC_IPW_PBCFG_VS_0_SW_PATCH_VERSION_C              1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Eth_43_GMAC_Ipw_Cfg.h */
#if (ETH_43_GMAC_IPW_PBCFG_VS_0_VENDOR_ID_C != ETH_43_GMAC_IPW_CFG_VENDOR_ID)
    #error "Eth_43_GMAC_Ipw_VS_0_PBcfg.c and Eth_43_GMAC_Ipw_Cfg.h have different vendor ids"
#endif
#if ((ETH_43_GMAC_IPW_PBCFG_VS_0_AR_RELEASE_MAJOR_VERSION_C    != ETH_43_GMAC_IPW_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (ETH_43_GMAC_IPW_PBCFG_VS_0_AR_RELEASE_MINOR_VERSION_C    != ETH_43_GMAC_IPW_CFG_AR_RELEASE_MINOR_VERSION) || \
     (ETH_43_GMAC_IPW_PBCFG_VS_0_AR_RELEASE_REVISION_VERSION_C != ETH_43_GMAC_IPW_CFG_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of Eth_43_GMAC_Ipw_VS_0_PBcfg.c and Eth_43_GMAC_Ipw_Cfg.h are different"
#endif
#if ((ETH_43_GMAC_IPW_PBCFG_VS_0_SW_MAJOR_VERSION_C != ETH_43_GMAC_IPW_CFG_SW_MAJOR_VERSION) || \
     (ETH_43_GMAC_IPW_PBCFG_VS_0_SW_MINOR_VERSION_C != ETH_43_GMAC_IPW_CFG_SW_MINOR_VERSION) || \
     (ETH_43_GMAC_IPW_PBCFG_VS_0_SW_PATCH_VERSION_C != ETH_43_GMAC_IPW_CFG_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Eth_43_GMAC_Ipw_VS_0_PBcfg.c and Eth_43_GMAC_Ipw_Cfg.h are different"
#endif

/* Checks against Gmac_Ip_Cfg.h */
#if (ETH_43_GMAC_IPW_PBCFG_VS_0_VENDOR_ID_C != GMAC_IP_CFG_VENDOR_ID)
    #error "Eth_43_GMAC_Ipw_VS_0_PBcfg.c and Gmac_Ip_Cfg.h have different vendor ids"
#endif
#if ((ETH_43_GMAC_IPW_PBCFG_VS_0_AR_RELEASE_MAJOR_VERSION_C    != GMAC_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (ETH_43_GMAC_IPW_PBCFG_VS_0_AR_RELEASE_MINOR_VERSION_C    != GMAC_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (ETH_43_GMAC_IPW_PBCFG_VS_0_AR_RELEASE_REVISION_VERSION_C != GMAC_IP_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AUTOSAR Version Numbers of Eth_43_GMAC_Ipw_VS_0_PBcfg.c and Gmac_Ip_Cfg.h are different"
#endif
#if ((ETH_43_GMAC_IPW_PBCFG_VS_0_SW_MAJOR_VERSION_C != GMAC_IP_CFG_SW_MAJOR_VERSION) || \
     (ETH_43_GMAC_IPW_PBCFG_VS_0_SW_MINOR_VERSION_C != GMAC_IP_CFG_SW_MINOR_VERSION) || \
     (ETH_43_GMAC_IPW_PBCFG_VS_0_SW_PATCH_VERSION_C != GMAC_IP_CFG_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Eth_43_GMAC_Ipw_VS_0_PBcfg.c and Gmac_Ip_Cfg.h are different"
#endif

/* Checks against Gmac_Ip_Features.h */
#if (ETH_43_GMAC_IPW_PBCFG_VS_0_VENDOR_ID_C != GMAC_IP_FEATURES_VENDOR_ID)
    #error "Eth_43_GMAC_Ipw_VS_0_PBcfg.c and Gmac_Ip_Features.h have different vendor ids"
#endif
#if ((ETH_43_GMAC_IPW_PBCFG_VS_0_AR_RELEASE_MAJOR_VERSION_C    != GMAC_IP_FEATURES_AR_RELEASE_MAJOR_VERSION) || \
     (ETH_43_GMAC_IPW_PBCFG_VS_0_AR_RELEASE_MINOR_VERSION_C    != GMAC_IP_FEATURES_AR_RELEASE_MINOR_VERSION) || \
     (ETH_43_GMAC_IPW_PBCFG_VS_0_AR_RELEASE_REVISION_VERSION_C != GMAC_IP_FEATURES_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of Eth_43_GMAC_Ipw_VS_0_PBcfg.c and Gmac_Ip_Features.h are different"
#endif
#if ((ETH_43_GMAC_IPW_PBCFG_VS_0_SW_MAJOR_VERSION_C != GMAC_IP_FEATURES_SW_MAJOR_VERSION) || \
     (ETH_43_GMAC_IPW_PBCFG_VS_0_SW_MINOR_VERSION_C != GMAC_IP_FEATURES_SW_MINOR_VERSION) || \
     (ETH_43_GMAC_IPW_PBCFG_VS_0_SW_PATCH_VERSION_C != GMAC_IP_FEATURES_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Eth_43_GMAC_Ipw_VS_0_PBcfg.c and Gmac_Ip_Features.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
  #if STD_ON == ETH_43_GMAC_DEM_EVENT_DETECT
    /* Checks against Dem.h */
    #if ((ETH_43_GMAC_IPW_PBCFG_VS_0_AR_RELEASE_MAJOR_VERSION_C != DEM_AR_RELEASE_MAJOR_VERSION) || \
         (ETH_43_GMAC_IPW_PBCFG_VS_0_AR_RELEASE_MINOR_VERSION_C != DEM_AR_RELEASE_MINOR_VERSION)    \
         )
        #error "AUTOSAR Version Numbers of Eth_43_GMAC_Ipw_VS_0_PBcfg.c and Dem.h are different"
    #endif
  #endif
#endif
/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
#define ETH_43_GMAC_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_43_GMAC_MemMap.h"

/**
* @brief   Export GMAC configurations.
*/
GMAC_CONFIG_EXT

#define ETH_43_GMAC_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_43_GMAC_MemMap.h"

#define ETH_43_GMAC_START_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Eth_43_GMAC_MemMap.h"

VAR_ALIGN(extern uint8 GMAC_0_RxRing_0_DataBuffer[(GMAC_0_MAX_RXBUFF_SUPPORTED * GMAC_0_MAX_RXBUFFLEN_SUPPORTED)], FEATURE_GMAC_BUFF_ALIGNMENT_BYTES)

#define ETH_43_GMAC_STOP_SEC_VAR_CLEARED_UNSPECIFIED_NO_CACHEABLE
#include "Eth_43_GMAC_MemMap.h"

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/



/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

#define ETH_43_GMAC_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_43_GMAC_MemMap.h"

static Eth_43_GMAC_Ipw_axRxBuffAddrMapType Eth_43_GMAC_Ipw_0_apListOfRxBuffAddrConfigPB_VS_0[4U] =
{
		{ 0U, GMAC_0_RxRing_0_DataBuffer + (0U * 64U) }, /* Map to queue 0 */
		{ 0U, GMAC_0_RxRing_0_DataBuffer + (1U * 64U) }, /* Map to queue 0 */
		{ 0U, GMAC_0_RxRing_0_DataBuffer + (2U * 64U) }, /* Map to queue 0 */
		{ 0U, GMAC_0_RxRing_0_DataBuffer + (3U * 64U) } /* Map to queue 0 */

};

#define ETH_43_GMAC_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_43_GMAC_MemMap.h"

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/
#define ETH_43_GMAC_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_43_GMAC_MemMap.h"

const Eth_43_GMAC_Ipw_CtrlConfigType Eth_43_GMAC_Ipw_aCtrlConfigPB_VS_0[1U] =
{
    /* The configuration structure for Eth_43_GMAC_Ipw_aCtrlConfig[0U] */
    {
        &Gmac_aCtrlConfigPB_VS_0[0U]
#if (STD_ON == ETH_43_GMAC_DEM_EVENT_DETECT)
       ,{
            { (uint32)STD_OFF , 0 }
        }
#endif
#if defined(GMAC_IP_MAC_TXRX_CLK_MUX_BYPASS) && (STD_ON == GMAC_IP_MAC_TXRX_CLK_MUX_BYPASS)
       ,{
      (uint32)0U,
      (uint32)0U,
      (uint32)0U
        }
#endif
		#if (STD_ON == ETH_43_GMAC_PPS_OUTPUT_SUPPORT)
        ,0U
        #endif
        ,4U
        ,&Eth_43_GMAC_Ipw_0_apListOfRxBuffAddrConfigPB_VS_0[0U]
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

