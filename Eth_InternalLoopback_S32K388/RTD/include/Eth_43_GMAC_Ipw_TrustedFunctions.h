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

#ifndef ETH_43_GMAC_IPW_TRUSTEDFUNCTIONS_H
#define ETH_43_GMAC_IPW_TRUSTEDFUNCTIONS_H

/**
*   @file
*
*   @addtogroup ETH_43_GMAC_DRIVER Ethernet Driver
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
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ETH_43_GMAC_IPW_TRUSTEDFUNCTIONS_VENDOR_ID                    43
#define ETH_43_GMAC_IPW_TRUSTEDFUNCTIONS_AR_RELEASE_MAJOR_VERSION     4
#define ETH_43_GMAC_IPW_TRUSTEDFUNCTIONS_AR_RELEASE_MINOR_VERSION     9
#define ETH_43_GMAC_IPW_TRUSTEDFUNCTIONS_AR_RELEASE_REVISION_VERSION  0
#define ETH_43_GMAC_IPW_TRUSTEDFUNCTIONS_SW_MAJOR_VERSION             7
#define ETH_43_GMAC_IPW_TRUSTEDFUNCTIONS_SW_MINOR_VERSION             0
#define ETH_43_GMAC_IPW_TRUSTEDFUNCTIONS_SW_PATCH_VERSION             1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/* Checks against Gmac_Ip_Types.h */
#if (ETH_43_GMAC_IPW_TRUSTEDFUNCTIONS_VENDOR_ID != GMAC_IP_TYPES_VENDOR_ID)
    #error "Eth_43_GMAC_Ipw_TrustedFunctions.h and Gmac_Ip_Types.h have different vendor ids"
#endif
#if (( ETH_43_GMAC_IPW_TRUSTEDFUNCTIONS_AR_RELEASE_MAJOR_VERSION    != GMAC_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     ( ETH_43_GMAC_IPW_TRUSTEDFUNCTIONS_AR_RELEASE_MINOR_VERSION    != GMAC_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     ( ETH_43_GMAC_IPW_TRUSTEDFUNCTIONS_AR_RELEASE_REVISION_VERSION != GMAC_IP_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Eth_43_GMAC_Ipw_TrustedFunctions.h and Gmac_Ip_Types.h are different"
#endif
#if (( ETH_43_GMAC_IPW_TRUSTEDFUNCTIONS_SW_MAJOR_VERSION != GMAC_IP_TYPES_SW_MAJOR_VERSION) || \
     ( ETH_43_GMAC_IPW_TRUSTEDFUNCTIONS_SW_MINOR_VERSION != GMAC_IP_TYPES_SW_MINOR_VERSION) || \
     ( ETH_43_GMAC_IPW_TRUSTEDFUNCTIONS_SW_PATCH_VERSION != GMAC_IP_TYPES_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Eth_43_GMAC_Ipw_TrustedFunctions.h and Gmac_Ip_Types.h are different"
#endif


/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

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
#define ETH_43_GMAC_START_SEC_CODE
#include "Eth_43_GMAC_MemMap.h"

extern void Eth_43_GMAC_Ipw_SelectPhyInterface(uint8 CtrlIdx, Gmac_Ip_MiiModeType ModeSelect);
#if defined(GMAC_IP_MAC_TXRX_CLK_MUX_BYPASS) && (STD_ON == GMAC_IP_MAC_TXRX_CLK_MUX_BYPASS)
extern void Eth_43_GMAC_Ipw_TxRxClkMuxBypass(uint8 CtrlIdx, const Gmac_Ip_TxRxClkMuxBypassType TxRxClkMuxBypass);
#endif

#define ETH_43_GMAC_STOP_SEC_CODE
#include "Eth_43_GMAC_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* ETH_43_GMAC_IPW_TRUSTEDFUNCTIONS_H */
