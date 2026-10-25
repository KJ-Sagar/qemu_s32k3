/*==================================================================================================
*   Project              : RTD AUTOSAR 4.9
*   Platform             : CORTEXM
*   Peripheral           :
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

#ifndef RAM_IP_TRUSTEDFUNCTIONS_H
#define RAM_IP_TRUSTEDFUNCTIONS_H

/**
*   @file    Ram_Ip_TrustedFunctions.h
*   @version    7.0.1
*
*   @brief   RAM IP type header file.
*   @details RAM IP type header file.

*   @{
*/

#if defined(__cplusplus)
extern "C"{
#endif
/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"
#include "Ram_Ip_Cfg.h"
#include "Ram_Ip_Types.h"
#include "Mcal.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define RAM_IP_TRUSTEDFUNCTIONS_VENDOR_ID                       43
#define RAM_IP_TRUSTEDFUNCTIONS_AR_RELEASE_MAJOR_VERSION        4
#define RAM_IP_TRUSTEDFUNCTIONS_AR_RELEASE_MINOR_VERSION        9
#define RAM_IP_TRUSTEDFUNCTIONS_AR_RELEASE_REVISION_VERSION     0
#define RAM_IP_TRUSTEDFUNCTIONS_SW_MAJOR_VERSION                7
#define RAM_IP_TRUSTEDFUNCTIONS_SW_MINOR_VERSION                0
#define RAM_IP_TRUSTEDFUNCTIONS_SW_PATCH_VERSION                1

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if source file and Std_Types.h file are of the same Autosar version */
#if ((RAM_IP_TRUSTEDFUNCTIONS_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
     (RAM_IP_TRUSTEDFUNCTIONS_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION) \
    )
    #error "AutoSar Version Numbers of Ram_Ip_TrustedFunctions.h  and Std_Types.h are different"
#endif
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if Ram_Ip_TrustedFunctions.h file and Mcal.h file are of the same Autosar version */
#if ((RAM_IP_TRUSTEDFUNCTIONS_AR_RELEASE_MAJOR_VERSION    != MCAL_AR_RELEASE_MAJOR_VERSION) || \
     (RAM_IP_TRUSTEDFUNCTIONS_AR_RELEASE_MINOR_VERSION    != MCAL_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Ram_Ip_TrustedFunctions.h and Mcal.h are different"
#endif
#endif

/* Check if Ram_Ip_TrustedFunctions.h file and Ram_Ip_Cfg.h file have same versions */
#if (RAM_IP_TRUSTEDFUNCTIONS_VENDOR_ID  != RAM_IP_CFG_VENDOR_ID)
    #error "Ram_Ip_TrustedFunctions.h and Ram_Ip_Cfg.h have different vendor IDs"
#endif

/* Check if Ram_Ip_TrustedFunctions.h file and Ram_Ip_Cfg.h file are of the same Autosar version */
#if ((RAM_IP_TRUSTEDFUNCTIONS_AR_RELEASE_MAJOR_VERSION    != RAM_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (RAM_IP_TRUSTEDFUNCTIONS_AR_RELEASE_MINOR_VERSION    != RAM_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (RAM_IP_TRUSTEDFUNCTIONS_AR_RELEASE_REVISION_VERSION != RAM_IP_CFG_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Ram_Ip_TrustedFunctions.h and Ram_Ip_Cfg.h are different"
#endif

/* Check if Ram_Ip_TrustedFunctions.h file and Ram_Ip_Cfg.h file are of the same Software version */
#if ((RAM_IP_TRUSTEDFUNCTIONS_SW_MAJOR_VERSION != RAM_IP_CFG_SW_MAJOR_VERSION) || \
     (RAM_IP_TRUSTEDFUNCTIONS_SW_MINOR_VERSION != RAM_IP_CFG_SW_MINOR_VERSION) || \
     (RAM_IP_TRUSTEDFUNCTIONS_SW_PATCH_VERSION != RAM_IP_CFG_SW_PATCH_VERSION))
    #error "Software Version Numbers of Ram_Ip_TrustedFunctions.h and Ram_Ip_Cfg.h are different"
#endif

/* Check if Ram_Ip_TrustedFunctions.h file and Ram_Ip_Types.h file have same versions */
#if (RAM_IP_TRUSTEDFUNCTIONS_VENDOR_ID  != RAM_IP_TYPES_VENDOR_ID)
    #error "Ram_Ip_TrustedFunctions.h and Ram_Ip_Types.h have different vendor IDs"
#endif

/* Check if Ram_Ip_TrustedFunctions.h file and Ram_Ip_Types.h file are of the same Autosar version */
#if ((RAM_IP_TRUSTEDFUNCTIONS_AR_RELEASE_MAJOR_VERSION    != RAM_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (RAM_IP_TRUSTEDFUNCTIONS_AR_RELEASE_MINOR_VERSION    != RAM_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (RAM_IP_TRUSTEDFUNCTIONS_AR_RELEASE_REVISION_VERSION != RAM_IP_TYPES_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Ram_Ip_TrustedFunctions.h and Ram_Ip_Types.h are different"
#endif

/* Check if Ram_Ip_TrustedFunctions.h file and Ram_Ip_Types.h file are of the same Software version */
#if ((RAM_IP_TRUSTEDFUNCTIONS_SW_MAJOR_VERSION != RAM_IP_TYPES_SW_MAJOR_VERSION) || \
     (RAM_IP_TRUSTEDFUNCTIONS_SW_MINOR_VERSION != RAM_IP_TYPES_SW_MINOR_VERSION) || \
     (RAM_IP_TRUSTEDFUNCTIONS_SW_PATCH_VERSION != RAM_IP_TYPES_SW_PATCH_VERSION))
    #error "Software Version Numbers of Ram_Ip_TrustedFunctions.h and Ram_Ip_Types.h are different"
#endif
/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/
/* Clock start section code */
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

#ifdef RAM_IP_ENABLE_USER_MODE_SUPPORT
  #if (STD_ON == RAM_IP_ENABLE_USER_MODE_SUPPORT)
#if (defined(MCAL_MC_ME_REG_PROT_AVAILABLE))
 #if (STD_ON == MCAL_MC_ME_REG_PROT_AVAILABLE)

/**
 * @brief        This function will enable writing in User mode by configuring REG_PROT
 *
 * @param        None
 * @return       None
 *
 */
extern void Ram_Ip_SetUserAccessAllowed(void);
 #endif /* (STD_ON == MCAL_MC_ME_REG_PROT_AVAILABLE) */
#endif
  #endif
#endif /* RAM_IP_ENABLE_USER_MODE_SUPPORT */

/* Clock stop section code */
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* RAM_IP_TRUSTEDFUNCTIONS_H */


