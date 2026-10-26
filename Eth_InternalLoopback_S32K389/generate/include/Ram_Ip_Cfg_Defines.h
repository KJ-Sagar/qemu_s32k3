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

#ifndef RAM_IP_CFG_DEFINES_H
#define RAM_IP_CFG_DEFINES_H

/**
*   @file       Ram_Ip_Cfg_Defines.h
*   @version    7.0.1
*
*   @brief   AUTOSAR Mcu - Post-Build(PB) configuration file code template.
*   @details Code template for Post-Build(PB) configuration file generation.
*
*   @addtogroup RAM_DRIVER_CONFIGURATION Ram Ip Driver
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "S32K389_MC_ME.h"
#include "S32K389_STCU.h"
/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define RAM_IP_CFG_DEFINES_VENDOR_ID                       43
#define RAM_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION        4
#define RAM_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION        9
#define RAM_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION     0
#define RAM_IP_CFG_DEFINES_SW_MAJOR_VERSION                7
#define RAM_IP_CFG_DEFINES_SW_MINOR_VERSION                0
#define RAM_IP_CFG_DEFINES_SW_PATCH_VERSION                1

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/**
* @brief            Pre-processor switch to enable/disable the API Ram_Ip_GetRamState.
*/

#define RAM_IP_GET_RAM_STATE_API        (STD_ON)

/**
* @brief        Support for MultiPartition.
*/
#define RAM_IP_MULTIPARTITION_SUPPORT            (STD_OFF)
#define RAM_IP_PARTITION_0                       ((uint8)0UL)

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


#ifdef __cplusplus
}
#endif

/** @} */
#endif /* #ifndef RAM_IP_CFG_DEFINES_H */


