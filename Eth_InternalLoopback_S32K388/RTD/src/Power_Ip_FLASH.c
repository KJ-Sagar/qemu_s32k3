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
/**
*   @file       Power_Ip_FLASH.c
*   @version    7.0.1
*
*   @brief   POWER driver implementations.
*   @details POWER driver implementations.
*
*   @addtogroup POWER_DRIVER Power Ip Driver
*   @{
*/

#ifdef __cplusplus
extern "C"
{
#endif




/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Power_Ip_FLASH.h"

#if (defined(POWER_IP_ENABLE_USER_MODE_SUPPORT) && (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT))
  #if (defined(MCAL_PMC_REG_PROT_AVAILABLE))
    #if (STD_ON == MCAL_PMC_REG_PROT_AVAILABLE)
      #define USER_MODE_REG_PROT_ENABLED      (STD_ON)
      #include "RegLockMacros.h"
    #endif /* (STD_ON == MCAL_PMC_REG_PROT_AVAILABLE) */
  #endif
#endif /* (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT) */
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define POWER_IP_FLASH_VENDOR_ID_C                      43
#define POWER_IP_FLASH_AR_RELEASE_MAJOR_VERSION_C       4
#define POWER_IP_FLASH_AR_RELEASE_MINOR_VERSION_C       9
#define POWER_IP_FLASH_AR_RELEASE_REVISION_VERSION_C    0
#define POWER_IP_FLASH_SW_MAJOR_VERSION_C               7
#define POWER_IP_FLASH_SW_MINOR_VERSION_C               0
#define POWER_IP_FLASH_SW_PATCH_VERSION_C               1

/*==================================================================================================
                                     FILE VERSION CHECKS
=================================================================================================*/
/* Check if current file and Power_Ip_FLASH header file are of the same vendor */
#if (POWER_IP_FLASH_VENDOR_ID_C != POWER_IP_FLASH_VENDOR_ID)
    #error "Power_Ip_FLASH.c and Power_Ip_FLASH.h have different vendor ids"
#endif
/* Check if current file and Power_Ip_FLASH header file are of the same Autosar version */
#if ((POWER_IP_FLASH_AR_RELEASE_MAJOR_VERSION_C    != POWER_IP_FLASH_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_FLASH_AR_RELEASE_MINOR_VERSION_C    != POWER_IP_FLASH_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_FLASH_AR_RELEASE_REVISION_VERSION_C != POWER_IP_FLASH_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip_FLASH.c and Power_Ip_FLASH.h are different"
#endif
/* Check if current file and Power_Ip_FLASH header file are of the same Software version */
#if ((POWER_IP_FLASH_SW_MAJOR_VERSION_C != POWER_IP_FLASH_SW_MAJOR_VERSION) || \
     (POWER_IP_FLASH_SW_MINOR_VERSION_C != POWER_IP_FLASH_SW_MINOR_VERSION) || \
     (POWER_IP_FLASH_SW_PATCH_VERSION_C != POWER_IP_FLASH_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip_FLASH.c and Power_Ip_FLASH.h are different"
#endif

#if (defined(POWER_IP_ENABLE_USER_MODE_SUPPORT) && (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT))
  #if (defined(MCAL_PMC_REG_PROT_AVAILABLE))
    #if (STD_ON == MCAL_PMC_REG_PROT_AVAILABLE)
        #ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
        /* Check if Power_Ip_FLASH.c file and RegLockMacros.h file are of the same Autosar version */
            #if ((POWER_IP_FLASH_AR_RELEASE_MAJOR_VERSION_C    != REGLOCKMACROS_AR_RELEASE_MAJOR_VERSION) || \
                (POWER_IP_FLASH_AR_RELEASE_MINOR_VERSION_C    != REGLOCKMACROS_AR_RELEASE_MINOR_VERSION))
                #error "AutoSar Version Numbers of Power_Ip_FLASH.c and RegLockMacros.h are different"
            #endif
        #endif
    #endif /* (STD_ON == MCAL_PMC_REG_PROT_AVAILABLE) */
  #endif
#endif /* (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT) */


/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                        LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
#define MCU_START_SEC_CODE

#include "Mcu_MemMap.h"

#if (defined(POWER_IP_ENTER_LOW_POWER_MODE) && (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON))

#if (defined(POWER_IP_ENABLE_USER_MODE_SUPPORT) && (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT))
  #if (defined(MCAL_C40ASF_REG_PROT_AVAILABLE))
    #if (STD_ON == MCAL_C40ASF_REG_PROT_AVAILABLE)
/**
* @brief            This function will enable writing in User mode by configuring REG_PROT
*/
void Power_Ip_FLASH_C40ASF_SetUserAccessAllowed(void)
{
#if (defined(IP_FLASH_BASE))
    SET_USER_ACCESS_ALLOWED(IP_FLASH_BASE, C40ASF_PROT_MEM_U32);
#endif
}
    #endif /* (STD_ON == MCAL_C40ASF_REG_PROT_AVAILABLE) */
  #endif /* (MCAL_C40ASF_REG_PROT_AVAILABLE) */
#endif /* (STD_ON == POWER_IP_ENABLE_USER_MODE_SUPPORT) */

/**
* @brief            This function checks if there is an ongoing Flash high voltage operation.
* @details          Checks whether the embedded flash array is idle or not.
*                   Called by:
*                       - Power_Ip_SetMode() from IPW.
*
* @param[in]        void
*
* @return           boolean
* @retval           TRUE        The embedded flash array is executing a high-voltage operation.
* @retval           FALSE       The embedded flash array is idle.
*
*/
boolean Power_Ip_FLASH_HighVoltageOperationOngoing(void)
{
    boolean FlashBusy = FALSE;
    uint32 McrReg;
    uint32 McrReg1 = 0U;

    /* Read value of Flash Module Configuration */
#ifdef IP_FLASH0

    McrReg = IP_FLASH0->MCR;
    McrReg1 = IP_FLASH1->MCR;

    if ( 0U != (McrReg & FLASH_MCR_EHV_MASK) || 0U != (McrReg1 & FLASH_MCR_EHV_MASK))
    {
        FlashBusy = TRUE;
    }
#else
    McrReg = IP_FLASH->MCR;
    (void) McrReg1;

    if ( 0U != (McrReg & FLASH_MCR_EHV_MASK) )
    {
        FlashBusy = TRUE;
    }
#endif

    return FlashBusy;
}
#endif /* (POWER_IP_ENTER_LOW_POWER_MODE == STD_ON) */

#define MCU_STOP_SEC_CODE

#include "Mcu_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */

