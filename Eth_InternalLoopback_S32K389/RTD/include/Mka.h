/*==================================================================================================
*   Project              : RTD AUTOSAR 4.9
*   Platform             : CORTEXM
*   Peripheral           :
*   Dependencies         :
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
#ifndef MKA_H
#define MKA_H

#ifdef __cplusplus
extern "C"{
#endif

 /*==================================================================================================
 *                                         INCLUDE FILES
 * 1) system and project includes
 * 2) needed interfaces from external units
 * 3) internal and external interfaces from this unit
 *================================================================================================*/
#include "Std_Types.h"

/*==================================================================================================
 *                              SOURCE FILE VERSION INFORMATION
 *================================================================================================*/
#define MKA_VENDOR_ID                    43
#define MKA_AR_RELEASE_MAJOR_VERSION     4
#define MKA_AR_RELEASE_MINOR_VERSION     9
#define MKA_AR_RELEASE_REVISION_VERSION  0
#define MKA_SW_MAJOR_VERSION             7
#define MKA_SW_MINOR_VERSION             0
#define MKA_SW_PATCH_VERSION             1

/*==================================================================================================
 *                                    FILE VERSION CHECKS
 *================================================================================================*/

/*==================================================================================================
 *                                     GLOBAL VARIABLES
 *================================================================================================*/

/*==================================================================================================
 *                                     GLOBAL CONSTANTS
 *================================================================================================*/

/*==================================================================================================
 *                                     GLOBAL FUNCTIONS
 *================================================================================================*/

/*==================================================================================================
 *                                     LOCAL VARIABLES
 *================================================================================================*/

/*==================================================================================================
 *                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 *================================================================================================*/
/*!
 * @brief Controls validation of received frames.
 */
typedef enum
{
    MKA_VALIDATE_DISABLED = 0U, /**< Disable validation, remove SecTAGs and ICVs (if present) from received frames. */
    MKA_VALIDATE_CHECKED,       /**< Enable validation, do not discard invalid frames. */
    MKA_VALIDATE_STRICT         /**< Enable validation and discard invalid frames. */
} Mka_ValidateFramesType;

/*!
 * @brief Indicates the offset in case of integrity with confidentiality.
 */
typedef enum
{
    MKA_CONFIDENTIALITY_NONE      = 0xFF,  /**< Confidentiality protection disabled. */
    MKA_CONFIDENTIALITY_OFFSET_0  = 0U,       /**< Zero initial octets of each user data without confidentiality protection. */
    MKA_CONFIDENTIALITY_OFFSET_30 = 30U,      /**< 30 initial octets of each user data without confidentiality protection. */
    MKA_CONFIDENTIALITY_OFFSET_50 = 50U      /**< 50 initial octets of each user data without confidentiality protection. */
} Mka_ConfidentialityOffsetType;

/*!
 * @brief SAK key reference.
 */
typedef struct
{
    const uint8 *HashKeyPtr; /**< Pointer to the Hash Key. */
    const uint8 *SakKeyPtr;  /**< Pointer to the SAK. */
    const uint8 *SaltKeyPtr; /**< Pointer to the Salt. */
} Mka_SakKeyPtrType;

/*!
 * @brief MACsec Entity (SecY) transmission statistics.
 */
typedef struct
{
    uint64 OutPkts_Untagged;    /**< The number of packets transmitted without a SecTAG. */
    uint64 OutPkts_TooLong;     /**< The number of transmitted packets discarded because their length is greater than the accepted maximum length (mtu) of the Port. */
    uint64 OutOctets_Protected; /**< The number of plain text octets integrity protected but not encrypted in transmitted frames. */
    uint64 OutOctets_Encrypted; /**< The number of plain text octets integrity protected and encrypted in transmitted frames. */
} Mka_Stats_Tx_SecYType;

/*!
 * @brief MACsec Entity (SecY) reception statistics.
 */
typedef struct
{
    uint64 InPkts_Untagged;    /**< The number of packets without the MACsec tag (SecTAG) received if ValidateFrames was not  VALIDATE_STRICT . */
    uint64 InPkts_NoTag;       /**< The number of received packets without a SecTAG discarded because ValidateFrames was  VALIDATE_STRICT . */
    uint64 InPkts_BadTag;      /**< The number of received packets discarded with an invalid SecTAG, zero value PN, or invalid ICV. */
    uint64 InPkts_NoSa;        /**< The number of received packets with an unknown SCI or for an unused SA by the security entity. */
    uint64 InPkts_NoSaError;   /**< The number of packets discarded because the received SCI is unknown or the SA is not in use. */
    uint64 InPkts_Overrun;     /**< The number of packets discarded because they exceeded cryptographic performance capabilities. */
    uint64 InOctets_Validated; /**< The number of plain text octets recovered from packets that were integrity protected but not encrypted. */
    uint64 InOctets_Decrypted; /**< The number of plain text octets recovered from packets that were integrity protected and encrypted. */
} Mka_Stats_Rx_SecYType;

/*!
 * @brief Secure Channel transmission statistics.
 */
typedef struct
{
    uint64 OutPkts_Protected; /**< The number of integrity protected but not encrypted packets for this transmit SC. */
    uint64 OutPkts_Encrypted; /**< The number of integrity protected and encrypted packets for this transmit SC. */
} Mka_Stats_Tx_ScType;

/*!
 * @brief Secure Channel reception statistics.
 */
typedef struct
{
    uint64 InPkts_Ok;        /**< The number of packets received for this secure channel successfully validated and within the replay window. */
    uint64 InPkts_Unchecked; /**< The number of packets received for this secure channel, if ValidateFrames was  VALIDATE_DISABLED . */
    uint64 InPkts_Delayed;   /**< The number of received packets, for this secure channel, with packet number (PN) lower than the lowest acceptable packet number (LowestPn) and ReplayProtect false. */
    uint64 InPkts_Late;      /**< The number of packets discarded, for this secure channel, because the received packet number (PN) was lower than the lowest acceptable packet number (LowestPn) and
                                  ReplayProtect was true. */
    uint64 InPkts_Invalid;   /**< The number of packets, for this secure channel, that failed validation but could be received because ValidateFrames was  VALIDATE_ CHECKED  and the data was not
                                  encrypted (so the original frame could be recovered). */
    uint64 InPkts_NotValid;  /**< The number of packets discarded, for this secure channel, because validation failed and ValidateFrames was  VALIDATE_STRICT  or the data was encrypted
                                  (so the original frame could not be recovered). */
} Mka_Stats_Rx_ScType;

/*!
 * @brief Security Entity statistics.
 */
typedef struct
{
    Mka_Stats_Tx_SecYType StatsTxPhy; /**< Set of statistics in the Security Entity Phy by transmission. */
    Mka_Stats_Rx_SecYType StatsRxPhy; /**< Set of statistics in the Security Entity Phy by reception. */
    Mka_Stats_Tx_ScType StatsTxSc;    /**< Set of statistics in the Security Entity s Secure Channel by reception. */
    Mka_Stats_Rx_ScType StatsRxSc;    /**< Set of statistics in the Security Entity s Secure Channel by reception. */
} Mka_Stats_SecYType;

/*!
 * @brief Structure to configure a referred SecY.
 */
typedef struct
{
    boolean ProtectFrames;                               /**< Indicates status if the MACsec protection of the frames is active or not. */
    boolean ReplayProtect;                               /**< Indicates status if replay protection is enable or disable. */
    uint32 ReplayWindow;                                 /**< If ReplayProtect is enable, indicates the used replay protect window. */
    Mka_ValidateFramesType ValidateFrames;               /**< Status of the validation of the frames. See Mka_ValidateFramesType for possible values. */
    uint64 CurrentCipherSuite;                           /**< Indicates which cipher suite is used in the SecY to update. */
    Mka_ConfidentialityOffsetType ConfidentialityOffset; /**< Set the Confidentiality Offset. See Mka_ConfidentialityOffsetType for possible values. */
    boolean ControlledPortEnabled;                       /**< Status if the controlled port is enabled or disabled. */
    const uint16 *BypassedVlanPtrs;                      /**< Pointer to the list of bypassed VLANs. */
    uint8 BypassedVlansLength;                           /**< Length of the list of bypassed VLANs. */
    const uint16 *BypassedEtherTypesPtr;                 /**< Pointer to the list of the bypassed Ethernet Types. */
    uint8 BypassedEtherTypesLength;                      /**< Length of the list of the bypassed Ethernet Types. */
} Mka_MacSecConfigType;

/*==================================================================================================
 *                                      LOCAL MACROS
 *================================================================================================*/

/*==================================================================================================
 *                                      LOCAL CONSTANTS
 *================================================================================================*/

/*==================================================================================================
 *                                      LOCAL FUNCTIONS
 *================================================================================================*/

/*==================================================================================================
 *                                   LOCAL FUNCTION PROTOTYPES
 *================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* MKA_H */

/** @} */
