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

#ifndef GMAC_IP_IRQ_H
#define GMAC_IP_IRQ_H

/**
*   @file
*
*   @addtogroup GMAC_DRIVER GMAC Driver
*   @{
*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Gmac_Ip_Features.h"
#include "OsIf.h"
#include "Gmac_Ip_Cfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define GMAC_IP_IRQ_VENDOR_ID                      43
#define GMAC_IP_IRQ_AR_RELEASE_MAJOR_VERSION       4
#define GMAC_IP_IRQ_AR_RELEASE_MINOR_VERSION       9
#define GMAC_IP_IRQ_AR_RELEASE_REVISION_VERSION    0
#define GMAC_IP_IRQ_SW_MAJOR_VERSION               7
#define GMAC_IP_IRQ_SW_MINOR_VERSION               0
#define GMAC_IP_IRQ_SW_PATCH_VERSION               1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Gmac_Ip_Features.h */
#if (GMAC_IP_IRQ_VENDOR_ID != GMAC_IP_FEATURES_VENDOR_ID)
    #error "Gmac_Ip_Irq.h and Gmac_Ip_Features.h have different vendor ids"
#endif
#if (( GMAC_IP_IRQ_AR_RELEASE_MAJOR_VERSION    != GMAC_IP_FEATURES_AR_RELEASE_MAJOR_VERSION) || \
     ( GMAC_IP_IRQ_AR_RELEASE_MINOR_VERSION    != GMAC_IP_FEATURES_AR_RELEASE_MINOR_VERSION) || \
     ( GMAC_IP_IRQ_AR_RELEASE_REVISION_VERSION != GMAC_IP_FEATURES_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Gmac_Ip_Irq.h and Gmac_Ip_Features.h are different"
#endif
#if (( GMAC_IP_IRQ_SW_MAJOR_VERSION != GMAC_IP_FEATURES_SW_MAJOR_VERSION) || \
     ( GMAC_IP_IRQ_SW_MINOR_VERSION != GMAC_IP_FEATURES_SW_MINOR_VERSION) || \
     ( GMAC_IP_IRQ_SW_PATCH_VERSION != GMAC_IP_FEATURES_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Gmac_Ip_Irq.h and Gmac_Ip_Features.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Checks against OsIf.h */
    #if (( GMAC_IP_IRQ_AR_RELEASE_MAJOR_VERSION    != OSIF_AR_RELEASE_MAJOR_VERSION) || \
         ( GMAC_IP_IRQ_AR_RELEASE_MINOR_VERSION    != OSIF_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AUTOSAR Version Numbers of Gmac_Ip_Irq.h and OsIf.h are different"
    #endif
#endif


/*******************************************************************************
 * API
 ******************************************************************************/
#define ETH_43_GMAC_START_SEC_CODE
#include "Eth_43_GMAC_MemMap.h"

#if (FEATURE_GMAC_NUM_INSTANCES > 0U)
/* Handle common interrupt for channel 0 */
ISR(GMAC0_Common_IRQHandler);


  #if (FEATURE_GMAC_ASP_ALL || FEATURE_GMAC_ASP_ECC)
  /* Handle safety interrupt */
  ISR(GMAC0_Safety_IRQHandler);
  #endif

  #if FEATURE_GMAC_INDIVIDUAL_CH_IRQS

    #if (FEATURE_GMAC_TX_NUM_CHANNELS > 0U)
    /* Handle Tx interrupt for channel 0 */
    ISR(GMAC0_CH0_TX_IRQHandler);
    #endif /* (FEATURE_GMAC_TX_NUM_CHANNELS > 0U) */

    #if (FEATURE_GMAC_TX_NUM_CHANNELS > 1U)
    /* Handle Tx interrupt for channel 1 */
    ISR(GMAC0_CH1_TX_IRQHandler);
    #endif /* (FEATURE_GMAC_TX_NUM_CHANNELS > 1U) */

    #if (FEATURE_GMAC_TX_NUM_CHANNELS > 2U)
    /* Handle Tx interrupt for channel 2 */
    ISR(GMAC0_CH2_TX_IRQHandler);
    #endif /* (FEATURE_GMAC_TX_NUM_CHANNELS > 2U) */



    #if (FEATURE_GMAC_RX_NUM_CHANNELS > 0U)
    /* Handle Rx interrupt for channel 0 */
    ISR(GMAC0_CH0_RX_IRQHandler);
    #endif /* (FEATURE_GMAC_RX_NUM_CHANNELS > 0U) */

    #if (FEATURE_GMAC_RX_NUM_CHANNELS > 1U)
    /* Handle Rx interrupt for channel 1 */
    ISR(GMAC0_CH1_RX_IRQHandler);
    #endif /* (FEATURE_GMAC_RX_NUM_CHANNELS > 1U) */

    #if (FEATURE_GMAC_RX_NUM_CHANNELS > 2U)
    /* Handle Rx interrupt for channel 2 */
    ISR(GMAC0_CH2_RX_IRQHandler);
    #endif /* (FEATURE_GMAC_RX_NUM_CHANNELS > 2U) */



  #elif FEATURE_GMAC_UNIFIED_CH_IRQS
    /* Find Tx channel flag raised */
    ISR(GMAC0_CH_TX_IRQHandler);

    /* Find Rx channel flag raised */
    ISR(GMAC0_CH_RX_IRQHandler);
  #endif /* FEATURE_GMAC_INDIVIDUAL_CH_IRQS */
#endif /* FEATURE_GMAC_NUM_INSTANCES > 0U*/

#if (FEATURE_GMAC_NUM_INSTANCES > 1U)
/* Handle common interrupt for channel 1*/
ISR(GMAC1_Common_IRQHandler);

  #if (FEATURE_GMAC_ASP_ALL || FEATURE_GMAC_ASP_ECC)
  ISR(GMAC1_Safety_IRQHandler);
  #endif

  #if FEATURE_GMAC_INDIVIDUAL_CH_IRQS

    #if (FEATURE_GMAC_TX_NUM_CHANNELS > 0U)
    /* Handle Tx interrupt for channel 0 */
    ISR(GMAC1_CH0_TX_IRQHandler);
    #endif /* (FEATURE_GMAC_TX_NUM_CHANNELS > 0U) */

    #if (FEATURE_GMAC_TX_NUM_CHANNELS > 1U)
    /* Handle Tx interrupt for channel 1 */
    ISR(GMAC1_CH1_TX_IRQHandler);
    #endif /* (FEATURE_GMAC_TX_NUM_CHANNELS > 1U) */

    #if (FEATURE_GMAC_TX_NUM_CHANNELS > 2U)
    ISR(GMAC1_CH2_TX_IRQHandler);
    #endif /* (FEATURE_GMAC_TX_NUM_CHANNELS > 2U) */



    #if (FEATURE_GMAC_RX_NUM_CHANNELS > 0U)
    /* Handle Rx interrupt for channel 1 */
    ISR(GMAC1_CH0_RX_IRQHandler);
    #endif /* (FEATURE_GMAC_RX_NUM_CHANNELS > 0U) */

    #if (FEATURE_GMAC_RX_NUM_CHANNELS > 1U)
    /* Handle Rx interrupt for channel 1 */
    ISR(GMAC1_CH1_RX_IRQHandler);
    #endif /* (FEATURE_GMAC_RX_NUM_CHANNELS > 1U) */

    #if (FEATURE_GMAC_RX_NUM_CHANNELS > 2U)
    ISR(GMAC1_CH2_RX_IRQHandler);
    #endif /* (FEATURE_GMAC_RX_NUM_CHANNELS > 2U) */



  #elif FEATURE_GMAC_UNIFIED_CH_IRQS
    ISR(GMAC1_CH_TX_IRQHandler);

    ISR(GMAC1_CH_RX_IRQHandler);
  #endif /* FEATURE_GMAC_INDIVIDUAL_CH_IRQS */
#endif /* (FEATURE_GMAC_NUM_INSTANCES > 1U) */


#define ETH_43_GMAC_STOP_SEC_CODE
#include "Eth_43_GMAC_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* GMAC_IP_IRQ_H */
