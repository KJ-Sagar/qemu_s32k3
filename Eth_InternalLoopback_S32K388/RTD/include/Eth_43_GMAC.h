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
/*   @implements Eth.h_Artifact */
#ifndef ETH_43_GMAC_H
#define ETH_43_GMAC_H

/**
*   @file
*   @implements Eth.h_Artifact
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
#include "Eth_GeneralTypes.h"  /* Mandatory include - see the SWS */
#include "Eth_43_GMAC_Cfg.h"
#include "Eth_43_GMAC_Ipw_Cfg.h"          /* Mandatory include - see the SWS */

#if defined(ETH_43_GMAC_MACSEC_SUPPORT)
#if (STD_ON == ETH_43_GMAC_MACSEC_SUPPORT)
#include "Eth_43_GMAC_MACsec.h"
#endif
#endif

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ETH_43_GMAC_MODULE_ID                    88
#define ETH_43_GMAC_VENDOR_ID                    43
#define ETH_43_GMAC_AR_RELEASE_MAJOR_VERSION     4
#define ETH_43_GMAC_AR_RELEASE_MINOR_VERSION     9
#define ETH_43_GMAC_AR_RELEASE_REVISION_VERSION  0
/* implements Eth_Version_define */
#define ETH_43_GMAC_SW_MAJOR_VERSION             7
#define ETH_43_GMAC_SW_MINOR_VERSION             0
#define ETH_43_GMAC_SW_PATCH_VERSION             1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Eth_43_GMAC_Cfg.h */
#if (ETH_43_GMAC_VENDOR_ID != ETH_43_GMAC_CFG_VENDOR_ID)
    #error "Eth_43_GMAC.h and Eth_43_GMAC_Cfg.h have different vendor ids"
#endif
#if ((ETH_43_GMAC_AR_RELEASE_MAJOR_VERSION    != ETH_43_GMAC_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (ETH_43_GMAC_AR_RELEASE_MINOR_VERSION    != ETH_43_GMAC_CFG_AR_RELEASE_MINOR_VERSION) || \
     (ETH_43_GMAC_AR_RELEASE_REVISION_VERSION != ETH_43_GMAC_CFG_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Eth_43_GMAC.h and Eth_43_GMAC_Cfg.h are different"
#endif
#if ((ETH_43_GMAC_SW_MAJOR_VERSION != ETH_43_GMAC_CFG_SW_MAJOR_VERSION) || \
     (ETH_43_GMAC_SW_MINOR_VERSION != ETH_43_GMAC_CFG_SW_MINOR_VERSION) || \
     (ETH_43_GMAC_SW_PATCH_VERSION != ETH_43_GMAC_CFG_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Eth_43_GMAC.h and Eth_43_GMAC_Cfg.h are different"
#endif

/* Checks against Eth_GeneralTypes.h */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((ETH_43_GMAC_AR_RELEASE_MAJOR_VERSION != ETH_GENERALTYPES_AR_RELEASE_MAJOR_VERSION) || \
         (ETH_43_GMAC_AR_RELEASE_MINOR_VERSION != ETH_GENERALTYPES_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AUTOSAR Version Numbers of Eth_43_GMAC.h and Eth_GeneralTypes.h are different"
    #endif

    #if defined(ETH_43_GMAC_MACSEC_SUPPORT)
    #if (STD_ON == ETH_43_GMAC_MACSEC_SUPPORT)
        /* Checks against Eth_43_GMAC_MACsec.h */
        #if ((ETH_43_GMAC_AR_RELEASE_MAJOR_VERSION != ETH_43_GMAC_MACSEC_AR_RELEASE_MAJOR_VERSION) || \
             (ETH_43_GMAC_AR_RELEASE_MINOR_VERSION != ETH_43_GMAC_MACSEC_AR_RELEASE_MINOR_VERSION)    \
            )
            #error "AUTOSAR Version Numbers of Eth_43_GMAC.h and Eth_43_GMAC_MACsec.h are different"
        #endif
    #endif
    #endif
#endif
/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/
/* Service IDs definition */
#if STD_ON == ETH_43_GMAC_DEV_ERROR_DETECT
/*! @brief Service ID of Eth_43_GMAC_Init */
#define ETH_43_GMAC_SID_INIT                        0x01
/*! @brief Service ID of Eth_43_GMAC_SetControllerMode */
#define ETH_43_GMAC_SID_SETCONTROLLERMODE           0x03
/*! @brief Service ID of Eth_43_GMAC_GetControllerMode */
#define ETH_43_GMAC_SID_GETCONTROLLERMODE           0x04

/*! @brief Service ID of Eth_43_GMAC_GetPhysAddr */
#define ETH_43_GMAC_SID_GETPHYSADDR                 0x08
/*! @brief Service ID of Eth_43_GMAC_ProvideTxBuffer */
#define ETH_43_GMAC_SID_PROVIDETXBUFFER             0x09
/*! @brief Service ID of Eth_43_GMAC_Transmit */
#define ETH_43_GMAC_SID_TRANSMIT                    0x0A
/*! @brief Service ID of Eth_43_GMAC_Receive */
#define ETH_43_GMAC_SID_RECEIVE                     0x0B
/*! @brief Service ID of Eth_43_GMAC_TxConfirmation */
#define ETH_43_GMAC_SID_TXCONFIRMATION              0x0C
/*! @brief Service ID of Eth_43_GMAC_ReleaseRxBuffer */
#define ETH_43_GMAC_SID_RELEASERXBUFFER             0x27

#if STD_ON == ETH_43_GMAC_VERSION_INFO_API
    /*! @brief Service ID of Eth_43_GMAC_GetVersionInfo */
    #define ETH_43_GMAC_SID_GETVERSIONINFO          0x0D
#endif

#if defined(ETH_43_GMAC_START_TSN_SUPPORT)
    #if (STD_ON == ETH_43_GMAC_START_TSN_SUPPORT)
/*! @brief Service ID of Eth_43_GMAC_StartTSN */
#define ETH_43_GMAC_SID_START_TSN                   0x0E
    #endif
#endif

#if STD_ON == ETH_43_GMAC_UPDATE_PHYS_ADDR_FILTER_API
    /*! @brief Service ID of Eth_43_GMAC_UpdatePhysAddrFilter */
    #define ETH_43_GMAC_SID_UPDATEADDRFILTER        0x12
#endif

/*! @brief Service ID of Eth_43_GMAC_SetPhysAddr */
#define ETH_43_GMAC_SID_SETPHYSADDR                 0x13

#if STD_ON == ETH_43_GMAC_GET_COUNTER_API
    /*! @brief Service ID of Eth_43_GMAC_GetCounterValues */
    #define ETH_43_GMAC_SID_GETCOUNTERVALUE         0x14
#endif

#if STD_ON == ETH_43_GMAC_GET_RXSTATS_API
    /*! @brief Service ID of Eth_43_GMAC_GetRxStats */
    #define ETH_43_GMAC_SID_GETRXSTATS              0x15
#endif

#if STD_ON == ETH_43_GMAC_GLOBAL_TIME_API
    /*! @brief Service ID of Eth_43_GMAC_GetCurrentTime */
    #define ETH_43_GMAC_SID_GETCURRENTTIME          0x16
    /*! @brief Service ID of Eth_43_GMAC_EnableEgressTimeStamp */
    #define ETH_43_GMAC_SID_ENABLEEGRESSTIMESTAMP   0x17
    /*! @brief Service ID of Eth_43_GMAC_GetEgressTimeStamp */
    #define ETH_43_GMAC_SID_GETEGRESSTIMESTAMP      0x18
    /*! @brief Service ID of Eth_43_GMAC_GetIngressTimeStamp */
    #define ETH_43_GMAC_SID_GETINGRESSTIMESTAMP     0x19
    /*! @brief Service ID of Eth_43_GMAC_SetCorrectionTime */
    #define ETH_43_GMAC_SID_SETCORRECTIONTIME       0x1A
    /*! @brief Service ID of Eth_43_GMAC_SetGlobalTime */
    #define ETH_43_GMAC_SID_SETGLOBALTIME           0x1B
    /*! @brief Service ID of Eth_43_GMAC_GetCurrentTimeTuple */
    #define ETH_43_GMAC_SID_GETCURRENTTIMETUPLE     0x21
#if (STD_ON == ETH_43_GMAC_PHC_ENABLED)
    /*! @brief Service ID of Eth_43_GMAC_SetPhcTime */
    #define ETH_43_GMAC_SID_SETPHCTIME              0x22
    /*! @brief Service ID of Eth_43_GMAC_SetPhcCorrection */
    #define ETH_43_GMAC_SID_SETPHCCORRECTION        0x23
    /*! @brief Service ID of Eth_43_GMAC_GetPhcTime */
    #define ETH_43_GMAC_SID_GETPHCTIME              0x24
#endif /* (STD_ON == ETH_43_GMAC_PHC_ENABLED) */
#endif /* STD_ON == ETH_43_GMAC_GLOBAL_TIME_API */

#if STD_ON == ETH_43_GMAC_GET_TXSTATS_API
    /*! @brief Service ID of Eth_43_GMAC_GetTxStats */
    #define ETH_43_GMAC_SID_GETTXSTATS              0x1C
#endif

#if STD_ON == ETH_43_GMAC_GET_TXERROR_COUNTER_API
    /*! @brief Service ID of Eth_43_GMAC_GetTxErrorCounterValues */
    #define ETH_43_GMAC_SID_GETTXERRORCOUNTERVALUE  0x1D
#endif

/*! @brief Service ID of Eth_43_GMAC_TxTimeAwareShaperInit */
#define ETH_43_GMAC_SID_TXTIMEAWARESHAPER       0x44

#if (STD_ON == ETH_43_GMAC_HAS_EXTERNAL_TX_BUFFERS)
/*! @brief Service ID of Eth_SendFrame */
#define ETH_43_GMAC_SID_SENDFRAME               0x45
#endif

#if (STD_ON == ETH_43_GMAC_HAS_EXTERNAL_RX_BUFFERS)
/*! @brief Service ID of Eth_ProvideRxBuffer */
#define ETH_43_GMAC_SID_PROVIDERXBUFFER         0x38
/*! @brief Service ID of Eth_ProvideRxBufferInfo */
#define ETH_43_GMAC_SID_PROVIDERXBUFFERINFO     0x37
#endif
#endif

#if STD_ON == ETH_43_GMAC_MDIO_CLAUSE22_API
    /*! @brief Service ID of Eth_43_GMAC_WriteMii */
    #define ETH_43_GMAC_SID_WRITEMII                0x05
    /*! @brief Service ID of Eth_43_GMAC_ReadMii */
    #define ETH_43_GMAC_SID_READMII                 0x06
#endif

#if STD_ON == ETH_43_GMAC_MDIO_CLAUSE45_API
    /*! @brief Service ID of Eth_43_GMAC_WriteMmd */
    #define ETH_43_GMAC_SID_WRITEMMD                0x42
    /*! @brief Service ID of Eth_43_GMAC_ReadMmd */
    #define ETH_43_GMAC_SID_READMMD                 0x43
#endif

#if (STD_ON == ETH_43_GMAC_SEND_MULTI_BUFFER_FRAME_API)
/*! @brief Service ID of Eth_SendMultiBufferFrame */
#define ETH_43_GMAC_SID_SENDMULTIBUFFERFRAME    0x26
#endif

#if (STD_ON == ETH_43_GMAC_COALESCING_INTERRUPT)
/*! @brief Service ID of Eth_ConfigureTxIntCoalescing */
#define ETH_43_GMAC_SID_CONFIGURETXCOALESCING    0x47

/*! @brief Service ID of Eth_ConfigureRxIntCoalescing */
#define ETH_43_GMAC_SID_CONFIGURERXCOALESCING    0x28
#endif

#if (STD_ON == ETH_43_GMAC_TIME_AWARE_SHAPER)
/*! @brief Service ID of Eth_StartTas */
#define ETH_43_GMAC_SID_START_TAS    0x29

/*! @brief Service ID of Eth_StopTas */
#define ETH_43_GMAC_SID_STOP_TAS    0x30
#endif


#if (STD_ON == ETH_43_GMAC_GET_SYNC_STATE_API)
/*! @brief Service ID of Eth_GetSyncState */
#define ETH_43_GMAC_SID_GET_SYNC_STATE      0x35
#endif

#if (STD_ON == ETH_43_GMAC_SET_SI_PHYS_ADDR_API)
/*! @brief Service ID of Eth_GetSIPhyAddr */
#define ETH_43_GMAC_SID_SET_SI_PHYADDR      0x36
#endif

#if defined(ETH_43_GMAC_FILL_LEVEL_API_ENABLE)
#if (ETH_43_GMAC_FILL_LEVEL_API_ENABLE == STD_ON)
/*! @brief Service ID of Eth_GetRxRingFillLevel */
#define ETH_43_GMAC_SID_GET_RX_RING_FILL_LEVEL  0x5D

/*! @brief Service ID of Eth_GetTxRingFillLevel */
#define ETH_43_GMAC_SID_GET_TX_RING_FILL_LEVEL  0x5E
#endif
#endif


#if (STD_ON == ETH_43_GMAC_PPS_OUTPUT_SUPPORT)
/*! @brief Service ID of Eth_SetPpsSignalMode */
#define ETH_43_GMAC_SID_SETPPSSIGNALMODE        0x25
/*! @brief Service ID of Eth_UpdatePpsConfig */
#define ETH_43_GMAC_SID_UPDATEPPSCONFIG         0x39
/*! @brief Service ID of PPSOutputSignalInit */
#define ETH_43_GMAC_PPSOUTPUTSIGNALINIT         0x46
#endif

#if STD_ON == ETH_43_GMAC_LPI_ENABLE
/*! @brief Service ID of Eth_EnteringTxLpi */
#define ETH_43_GMAC_SID_ENTERINGTXLPI        0x40
/*! @brief Service ID of Eth_ExitingTxLpi */
#define ETH_43_GMAC_SID_EXITINGTXLPI         0x41
#endif

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

#if (STD_ON == ETH_43_GMAC_HAS_EXTERNAL_RX_BUFFERS)
/**
* @brief         Type used to express the ethernet buffer with split header feature.
* @details       Variables of this type are used to express the ethernet buffer with split header feature.
* Implements     Eth_RxBufferInfo
*/
typedef struct
{
    uint8* HeaderBuffDataAddress;    /**< @brief Pointer to the ethernet header buffer address */
    uint8* PayloadBuffDataAddress;   /**< @brief Pointer to the ethernet payload data buffer address */
} Eth_43_GMAC_RxBufferInfo;
#endif

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

#define ETH_43_GMAC_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_43_GMAC_MemMap.h"

#if STD_OFF == ETH_43_GMAC_PRECOMPILE_SUPPORT
ETH_43_GMAC_CONFIG_EXT
#endif

#if (ETH_43_GMAC_PRECOMPILE_SUPPORT == STD_ON)
    #if STD_ON == ETH_43_GMAC_MULTIPARTITION_SUPPORT
        extern const Eth_43_GMAC_ConfigType * const Eth_43_GMAC_apxPredefinedConfig[ETH_43_GMAC_MAX_PARTITIONIDX_SUPPORTED];
    #else
        extern const Eth_43_GMAC_ConfigType Eth_43_GMAC_xPredefinedConfig;
    #endif
#endif /* #if (ETH_43_GMAC_PRECOMPILE_SUPPORT == STD_ON) */

#define ETH_43_GMAC_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Eth_43_GMAC_MemMap.h"


/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
#define ETH_43_GMAC_START_SEC_CODE
#include "Eth_43_GMAC_MemMap.h"


/**
* @brief         Initializes the Ethernet Driver
* @details       The configuration pointer is internally stored and
*                the driver is initialized. The Ethernet controller is
*                also reset.
* @note          Function should be called only once.
* @warning       Second call can cause undefined behavior.
*                Call the Eth_SetControllerMode() and pass ETH_MODE_DOWN to
*                the CtrlMode argument before the second Eth_Init call to avoid
*                problems.
* @api
* @param[in]     CfgPtr Points to the implementation specific structure containing
*                the Eth driver configuration
* Compiler_Warning: this warning due to behavior of compiler depend on configs.
* implements    Eth_Init_Activity
*/
void Eth_43_GMAC_Init(const Eth_43_GMAC_ConfigType *CfgPtr);


/**
* @brief         Enables or disables the given controller
* @warning       Disabling the controller clears all receive and transmit
*                buffers. The application should ensure that no data is lost.
* @api
* @param[in]     CtrlIdx Index of the controller to be enabled or disabled.
*                The index is valid within the context of the Ethernet Driver
*                only.
* @param[in]     CtrlMode Mode which shall be entered
*                - ETH_MODE_DOWN: disable the controller
*                - ETH_MODE_ACTIVE: enable the controller
* @return        Error status
* @retval        E_OK No error was detected during the function execution.
* @retval        E_NOT_OK Development error was detected and the function
*                failed.
* implements    Eth_SetControllerMode_Activity
*/
Std_ReturnType Eth_43_GMAC_SetControllerMode ( \
                                    uint8 CtrlIdx, \
                                    Eth_ModeType CtrlMode \
                                            );

/**
* @brief         Obtains the mode of the given controller
* @api
* @param[in]     CtrlIdx Index of the controller which state shall be read.
*                The index is valid within the context of the Ethernet Driver
*                only.
* @param[out]    CtrlModePtr Pointer where to store the current controller mode.
* @return        Error status
* @retval        E_OK No error was detected during the function execution.
* @retval        E_NOT_OK Development error was detected and the function
*                failed.
* implements    Eth_GetControllerMode_Activity
*/
Std_ReturnType Eth_43_GMAC_GetControllerMode ( \
                                    uint8 CtrlIdx, \
                                    Eth_ModeType *CtrlModePtr \
                                            );
/**
* @brief         Control transmit frame in duration time (This function is obsolete).
* @api
* @param[in]     CtrlIdx Index of the controller which state shall be read.
*                The index is valid within the context of the Ethernet Driver
*                only.
* @warning       This function is obsolete. If time aware shaper feature is intended to be used,
*                call @c Eth_StartTas and @c Eth_StopTas instead.
* @return        Std_ReturnType
*/
Std_ReturnType Eth_43_GMAC_TxTimeAwareShaperInit(uint8 CtrlIdx);

/**
* @brief         Obtains the physical source address used by the indexed
*                controller (the node MAC address).
* @api
* @param[in]     CtrlIdx Index of the controller whose MAC address should be
*                read. The index is valid within the context of the Ethernet
*                Driver only.
* @param[out]    PhysAddrPtr Pointer where to store the physical source address
*                (MAC address). The address in network byte order is stored into
*                6 bytes at the given memory address.
* implements    Eth_GetPhysAddr_Activity
*/
void Eth_43_GMAC_GetPhysAddr ( \
                        uint8 CtrlIdx, \
                        uint8 *PhysAddrPtr \
                            );

/**
* @brief         Set or change physical address to the defined controller.
* @api
* @param[in]     CtrlIdx Index of the controller whose MAC address should be
*                changed. The index is valid within the context of the Ethernet
*                Driver only.
* @param[in]     PhysAddrPtr Pointer to the physical source address which should be set to
*                the controller. The address is stored in 6 bytes of memory
*                in network byte order.
* @warning       This function may be called only when the controller is down.
*                Calling function @c Eth_Init will change the controller's MAC address
*                to the default value!
* implements    Eth_SetPhysAddr_Activity
*/
void Eth_43_GMAC_SetPhysAddr(uint8 CtrlIdx, const uint8 *PhysAddrPtr);


#if STD_ON == ETH_43_GMAC_UPDATE_PHYS_ADDR_FILTER_API
/**
* @brief         Adds or removes the specified PhysAddrPtr address to or from
*                a multicast address pool in the controller specified by CtrlIdx.
* @api
* @details       Enables or disables reception for the specified multicast
*                physical address. Unicast addresses are ignored.
*                Operations for special Physical addresses follow.
*                If Physical Address ff:ff:ff:ff:ff:ff is added into a filter
*                (Action=ETH_ADD_TO_FILTER) the filter is completely open
*                and any address is accepted at reception. Later on when
*                Physical Address ff:ff:ff:ff:ff:ff is removed from the filter
*                (Action=ETH_REMOVE_FROM_FILTER) the filtering is recovered
*                and the reception is allowed again only for addresses remaining
*                in the filter.
*                If Physical Address 00:00:00:00:00:00 is added into a filter,
*                (Action=ETH_ADD_TO_FILTER) the filter is completely close
*                have no any address is received. Later on when Physical Address 00:00:00:00:00:00
*                is removed from the filter (Action=ETH_REMOVE_FROM_FILTER) the filtering is recovered
*                and the reception is allowed again only for addresses remaining in the filter.
*                Note that operations of full open or close are in exclusive
*                disjunction. Operation of full open excludes full close and
*                vice versa.
* @param[in]     CtrlIdx Index of the controller. The index is valid within
*                the context of the Ethernet Driver only.
* @param[in]     PhysAddrPtr Pointer to PHY address which shall be added
*                or removed to or from multicast pool.
*                The address in network byte order stored into 6 bytes of
*                memory.
* @param[in]     Action Determine whenever the defined address will be added
*                to the pool ETH_ADD_TO_FILTER or removed from it
*                ETH_REMOVE_FROM_FILTER.
*implements    Eth_UpdatePhysAddrFilter_Activity
*/
Std_ReturnType Eth_43_GMAC_UpdatePhysAddrFilter  ( \
                                        uint8 CtrlIdx, \
                                        const uint8 *PhysAddrPtr, \
                                        Eth_FilterActionType Action \
                                                );
#endif /* ETH_43_GMAC_UPDATE_PHYS_ADDR_FILTER_API */

#if STD_ON == ETH_43_GMAC_GET_COUNTER_API
/**
* @brief            Reads a list with drop counter values of the corresponding controller.
* @api
* @param[in]        CtrlIdx    Index of the controller
* @param[out]       CounterPtr Pointer to Eth_CounterType where to store the read drop counter values
* @return           Error status
* @retval           E_OK No error was detected during the function execution.
* @retval           E_NOT_OK Development error was detected or inaccessible to counters register
*                   and the function.
* @details          Reads a list with drop counter values of the corresponding controller. The meaning
*                   of these values is hardware dependent. However, the list DropCount[] shall
*                   contain the following values in the given order, where the maximal possible value
*                   shall denote an invalid value, e.g. if this counter is not available:
*                   1. Dropped packets due to buffer overrun
*                   2. Dropped packets due to CRC errors
*                   3. Number of undersize packets which were less than 64 octets long (excluding
*                   framing bits, but including FCS octets) and were otherwise will formed. (see IETF
*                   RFC 1757)
*                   4. Number of oversize packets which are longer than 1518 octets (excluding
*                   framing bits, but including FCS octets) and were otherwise well formed. (see IETF
*                   RFC 1757)
*                   5. Number of alignment errors, i.e. packets which are received and are not an
*                   integral number of octets in length and do not pass the CRC.
*                   6. SQE test error according to IETF RFC1643 dot3StatsSQETestErrors
*                   7. The number of inbound packets which were chosen to be discarded even
*                   though no errors had been detected to prevent their being deliverable to a higher layer protocol.
*                   One possible reason for discarding such a packet could be to free
*                   up buffer space. (see IETF RFC 2233 ifInDiscards)
*                   8. Total number of erroneous inbound packets
*                   9. The number of outbound packets which were chosen to be discarded even
*                   though no errors had been detected to prevent their being transmitted. One
*                   possible reason for discarding such a packet could be to free up buffer space.
*                   (see IETF RFC 2233 ifOutDiscards)
*                   10. Total number of erroneous outbound packets
*                   11. Single collision frames: A count of successfully transmitted frames on a
*                   particular interface for which transmission is inhibited by exactly one collision. (see
*                   IETF RFC1643 dot3StatsSingleCollisionFrames)
*                   12. Multiple collision frames: A count of successfully transmitted frames on a
*                   particular interface for which transmission is inhibited by more than one collision.
*                   (see IETF RFC1643 dot3StatsMultipleCollisionFrames)
*                   13. Number of deferred transmission: A count of frames for which the first
*                   transmission attempt on a particular interface is delayed because the medium is
*                   busy. (see IETF RFC1643 dot3StatsDeferredTransmissions)
*                   14. Number of late collisions: The number of times that a collision is detected on
*                   a particular interface later than 512 bit times into the transmission of a packet.
*                   (see IETF RFC1643 dot3StatsLateCollisions)
*                   15. The following positions in the list can contain hardware dependent counter
*                   values
*implements       Eth_GetCounterValues_Activity
*/
Std_ReturnType Eth_43_GMAC_GetCounterValues ( \
                                        uint8 CtrlIdx, \
                                        Eth_CounterType *CounterPtr \
                                           );
#endif

#if STD_ON == ETH_43_GMAC_MDIO_CLAUSE45_API
/**
* @brief         Transfers management data over the MII
* @param[in]     CtrlIdx Index of controller to be transferred
* @param[in]     TrcvIdx Transceiver/Port to communicate with
* @param[in]     Mmd Device which shall be accessed
* @param[in]     RegAddress Register address which shall be accessed
* @param[out]    RegValPtr Data to be written to register
* @return        Failure status
* @retval        E_OK Success, no error has occurred.
* @retval        E_NOT_OK Failure, no response from the hardware within a timeout.
*/
Std_ReturnType Eth_43_GMAC_ReadMmd ( \
                              uint8 CtrlIdx,\
                              uint8 TrcvIdx, \
                              uint8 Mmd, \
                              uint16 RegAddress,\
                              uint16 *RegValPtr
                           );

/**
* @brief         Transfers management data over the MII
* @param[in]     CtrlIdx Index of controller to be transferred
* @param[in]     TrcvIdx Transceiver/Port to communicate with
* @param[in]     Mmd Device which shall be accessed
* @param[in]     RegAddress Register address which shall be accessed
* @param[in]     RegVal Data to be written to register
* @return        Failure status
* @retval        E_OK Success, no error has occurred.
* @retval        E_NOT_OK Failure, no response from the hardware within a timeout.
*/
Std_ReturnType Eth_43_GMAC_WriteMmd ( \
                                uint8 CtrlIdx,\
                                uint8 TrcvIdx, \
                                uint8 Mmd, \
                                uint16 RegAddress,\
                                uint16 RegVal
                            );
#endif /* ETH_43_GMAC_MDIO_CLAUSE45_API */

#if STD_ON == ETH_43_GMAC_MDIO_CLAUSE22_API
/**
* @brief         Writes to a transceiver (physical layer driver) register.
* @details       The management frame is assembled and the MII bus transaction
*                is issued in order to transfer the data. Function waits until
*                the bus transaction finishes.
* @warning       This function is blocking the execution until the MII bus
*                transaction is finished.
* @api
* @param[in]     CtrlIdx Index of the controller which transceiver register
*                shall be written. The index is valid within the context of
*                the Ethernet Driver only.
* @param[in]     TrcvIdx Index of the transceiver connected the MII. The value
*                shall be within the range 0..31.
* @param[in]     RegIdx Index of the transceiver register to be written. The
*                value shall be withing the range 0..31.
* @param[in]     RegVal Value to be written into the indexed register.
* @retval        E_OK No error was detected during the function execution.
* @retval        E_NOT_OK Development error or the function failed.
* implements    Eth_WriteMii_Activity
*/
Std_ReturnType Eth_43_GMAC_WriteMii  ( \
                                uint8 CtrlIdx, \
                                uint8 TrcvIdx, \
                                uint8 RegIdx, \
                                uint16 RegVal \
                                    );

/**
* @brief          Reads a transceiver (physical layer driver) register.
* @api
* @param[in]      CtrlIdx Index of the controller which transceiver register
*                 shall be read. The index is valid within the context of
*                 the Ethernet Driver only.
* @param[in]      TrcvIdx Index of the transceiver connected on the MII. The
*                 value shall be within the range 0..31.
* @param[in]      RegIdx Index of the transceiver register to be read. The
*                 Value shall be within the range 0..31.
* @param[out]     RegValPtr Filled with the register content of the indexed register
* @retval         E_OK No error was detected during the function execution.
* @retval         E_NOT_OK Development error or the function failed.
* @details        The management frame is assembled and the MII bus transaction
*                 is issued in order to transfer the data. Function waits until
*                 the bus transaction finishes and then returns the read data.
* @warning        This function is blocking the execution until the MII bus
*                 transaction is finished.
* implements     Eth_ReadMii_Activity
*/
Std_ReturnType Eth_43_GMAC_ReadMii   ( \
                                uint8 CtrlIdx, \
                                uint8 TrcvIdx, \
                                uint8 RegIdx, \
                                uint16 *RegValPtr \
                                    );
#endif /* ETH_43_GMAC_MDIO_CLAUSE22_API */

#if STD_ON == ETH_43_GMAC_GET_RXSTATS_API
/**
* @brief        Read the status of a controller
* @details      Returns the following list according to IETF RFC2819, where the maximal possible
*               value shall denote an invalid value, e.g. if this counter is not available:
*               1. etherStatsDropEvents
*               2. etherStatsOctets
*               3. etherStatsPkts
*               4. etherStatsBroadcastPkts
*               5. etherStatsMulticastPkts
*               6. etherStatsCrcAlignErrors
*               7. etherStatsUndersizePkts
*               8. etherStatsOversizePkts
*               9. etherStatsFragments
*               10. etherStatsJabbers
*               11. etherStatsCollisions
*               12. etherStatsPkts64Octets
*               13. etherStatsPkts65to127Octets
*               14. etherStatsPkts128to255Octets
*               15. etherStatsPkts256to511Octets
*               16. etherStatsPkts512to1023Octets
*               17. etherStatsPkts1024to1518Octets
* @api
* @param[in]    CtrlIdx Index of the controller which shall be read the status register.
* @param[out]   RxStats Pointer to 32 bit long memory space to be filled with
*               the list values according to IETF RFC 2819 (Remote Network
*               Monitoring Management Information Base).
* @return       Error status
* @retval       E_OK No error was detected during the function execution.
* @retval       E_NOT_OK Development error was detected or inaccessible to counters register
*               and the function.
* implements   Eth_GetRxStats_Activity
*/
Std_ReturnType Eth_43_GMAC_GetRxStats ( \
                                uint8 CtrlIdx, \
                                Eth_RxStatsType *RxStats \
                              );
#endif
#if STD_ON == ETH_43_GMAC_GET_TXSTATS_API
/**
* @brief         Return the list of Transmission Statistics.
* @param[in]     CtrlIdx Index of controller within the context of the Ethernet Driver.
* @param[out]    TxStats Pointer to 32 bit long memory space to be filled with
*                the list values according to IETF RFC 1213
* @details       Return the list of Transmission Statistics out of IETF RFC 1213
*                defined within Eth_TxStatsType, where the maximal possible value shall
*                denote an invalid value.
*                e.g. this counter is not available..
* @return        The search status
* @retval        E_OK Success
* @retval        E_NOT_OK Tx-statistics could not be obtained.
* implements    Eth_GetTxStats_Activity
*/
Std_ReturnType Eth_43_GMAC_GetTxStats ( \
                                uint8 CtrlIdx, \
                                Eth_TxStatsType *TxStats \
                              );
#endif
#if STD_ON == ETH_43_GMAC_GET_TXERROR_COUNTER_API
/**
* @brief         Return the list of Transmission Statistics.
* @param[in]     CtrlIdx Index of controller within the context of the Ethernet Driver.
* @param[out]    TxErrorCounterValues List of values to read statistic error counter values for transmission.
* @details       Return the list of Transmission Error Counters out of IETF RFC1213 and RFC1643
*                defined within Eth_TxErrorCounterValuesType, where the maximal possible value shall
*                denote an invalid value.
*                e.g. this counter is not available.
* @return        The search status
* @retval        E_OK Success
* @retval        E_NOT_OK Tx-statistics could not be obtained.
* implements    Eth_GetTxErrorCounterValues_Activity
*/
Std_ReturnType Eth_43_GMAC_GetTxErrorCounterValues ( \
                                uint8 CtrlIdx, \
                                Eth_TxErrorCounterValuesType *TxErrorCounterValues \
                                           );
#endif

#if STD_ON == ETH_43_GMAC_GLOBAL_TIME_API
/**
* @brief        Allows the Time Master to adjust the global ETH Reference clock in HW.
* @details      We can use this method to set a global time base on ETH in general or to
*               synchronize the global ETH time base with another time base, e.g. FlexRay.
* @param[in]    CtrlIdx Index of the TM controller which time shall be adjusted.
* @param[in]    timeStampPtr Pointer to new time stamp.
*/
Std_ReturnType Eth_43_GMAC_SetGlobalTime(uint8 CtrlIdx, \
                                                 const Eth_TimeStampType *TimeStampPtr);

/**
* @brief        Allows the Time Slave to adjust the local ETH Reference clock in HW.
* @details      Only use this function when this controller used as Time Slave.
*
* @param[in]    CtrlIdx        Index of the controller which time shall be corrected
* @param[in]    TimeOffsetPtr  Offset between time stamp grandmaster and time stamp by local
*               clock.
* @param[in]    RateRatioPtr   Time elements to calculate and to modify the ratio of the frequency
*                              of the grandmaster in relation to the frequency of the local clock
*                              with ratio = OriginTimeStampDelta / IngressTimeStampDelta, where
*                              Origin = Requester and Ingress = Responder.
*/
Std_ReturnType Eth_43_GMAC_SetCorrectionTime ( \
                            uint8 CtrlIdx, \
                            const Eth_TimeIntDiffType *TimeOffsetPtr, \
                            const Eth_RateRatioType *RateRatioPtr
                                );
/**
* @brief         Reads back the egress time stamp on a dedicated message object.
* @note          It must be called within the TxConfirmation() function.
* @api
* @param[in]     CtrlIdx Index of the controller which the egress timestamp shall be read.
* @param[in]     BufIdx Index of the message buffer, where Application expects egress time
*                stamping
* @param[out]    TimeQualPtr Quality of HW time stamp, e.g. based on current drift
* @param[out]    TimeStampPtr Current time stamp
* implements    Eth_GetEgressTimeStamp_Activity
*/
Std_ReturnType Eth_43_GMAC_GetEgressTimeStamp ( \
                                uint8 CtrlIdx, \
                                Eth_BufIdxType BufIdx, \
                                Eth_TimeStampQualType *TimeQualPtr, \
                                Eth_TimeStampType *TimeStampPtr \
                                            );
/**
* @brief         Reads back the egress time stamp on a dedicated message object.
* @note          It must be called within the TxConfirmation() function.
* @api
* @param[in]     CtrlIdx Index of the controller which the egress timestamp shall be
*                read.
* @param[in]     DataPtr Pointer to the message buffer, where Application expects ingress
*                time stamping
* @param[out]    TimeQualPtr Quality of HW time stamp, e.g. based on current drift
* @param[out]    TimeStampPtr Current time stamp
* implements    Eth_GetIngressTimeStamp_Activity
*/
Std_ReturnType Eth_43_GMAC_GetIngressTimeStamp ( \
                                uint8 CtrlIdx, \
                                const Eth_DataType *DataPtr, \
                                Eth_TimeStampQualType *TimeQualPtr, \
                                Eth_TimeStampType *TimeStampPtr \
                                             );
/**
* @brief         Returns a time value out of the HW registers according to the capability of the HW.
* @note          If the hardware timestamp timer's resolution is lower than the Eth_TimeStampType
*                resolution range, then the remaining bits will be filled with 0.
* @api
* @param[in]     CtrlIdx Index of the controller shall be read the time value.
* @param[out]    TimeQualPtr Quality of HW time stamp, e.g. based on current drift
* @param[out]    TimeStampPtr Current time stamp
* @return        Error status
* @retval        E_OK: successfully read the timestamp
* @retval        E_NOT_OK: development error was detected or fail to read the TimeStamp.
*/
Std_ReturnType Eth_43_GMAC_GetCurrentTime  ( \
                                uint8 CtrlIdx, \
                                Eth_TimeStampQualType *timeQualPtr, \
                                Eth_TimeStampType *timeStampPtr \
                                          );

/**
* @brief         Returns time values of Hw Timestamping clock and PHC.
*
* @note          Having the same value if only one Hw clock supported.
*                If the hardware timestamp timer's resolution is lower than the TimeStampType
*                resolution range, then the remaining bits will be filled with 0.
* @api
* @param[in]     CtrlIdx Index of the controller shall be read the time value.
* @param[in]     ClkUnitIdx Index of the Clock Unit within the context of the Ethernet driver to provide the time tuple.
* @param[out]    currentTimeTuplePtr Current time tuple with the value of the clock used for timestamping and the value of adjustable PHC.
* @return        Error status
* @retval        E_OK: successfully read the timestamp
* @retval        E_NOT_OK: development error was detected or fail to read the TimeStamp.
* implements     Eth_GetCurrentTimeTuple_Activity
*/
Std_ReturnType Eth_43_GMAC_GetCurrentTimeTuple
(
    uint8 CtrlIdx,
    uint8 ClkUnitIdx,
    TimeTupleType* currentTimeTuplePtr
);

#if (STD_ON == ETH_43_GMAC_PHC_ENABLED)
/**
* @brief         Returns time value of PHC.
*
* @note          Having the same value with Hw Timestamping clock if only one Hw clock supported.
*                If the hardware timestamp timer's resolution is lower than the TimeStampType
*                resolution range, then the remaining bits will be filled with 0.
* @api
* @param[in]     CtrlIdx Index of the controller shall be read the time value.
* @param[in]     ClkUnitIdx Index of the Clock Unit within the context of the Ethernet driver to provide the time tuple.
* @param[out]    TimeQualPtr Quality of HW time stamp, e.g. based on current drift
* @param[out]    TimeStampPtr Current time stamp
* @return        Error status
* @retval        E_OK: successfully read the timestamp
* @retval        E_NOT_OK: development error was detected or fail to read the TimeStamp.
* implements     Eth_GetPhcTime_Activity
*/
Std_ReturnType Eth_43_GMAC_GetPhcTime
(
    uint8 CtrlIdx,
    uint8 ClkUnitIdx,
    TimeStampQualType* timeQualPtr,
    TimeStampType* timeStampPtr
);

/**
* @brief         Sets the absolute time of the PHC.
*
* @note          Sets the absolute time of the PHC.

* @api
* @param[in]     CtrlIdx Index of the controller shall be read the time value.
* @param[in]     ClkUnitIdx Index of the Clock Unit within the context of the Ethernet driver to provide the time tuple.
* @param[in]     timeStampPtr Current time stamp
* @return        Error status
* @retval        E_OK: successfully read the timestamp
* @retval        E_NOT_OK: development error was detected or fail to read the TimeStamp.
* implements     Eth_SetPhcTime_Activity
*/
Std_ReturnType Eth_43_GMAC_SetPhcTime
(
    uint8 CtrlIdx,
    uint8 ClkUnitIdx,
    const TimeStampType* timeStampPtr
);

/**
* @brief         Sets PHC parameters to adapt rate and offset of the PHC.
*
* @note          Sets PHC parameters to adapt rate and offset of the PHC.

* @api
* @param[in]     CtrlIdx Index of the controller shall be read the time value.
* @param[in]     ClkUnitIdx Index of the Clock Unit within the context of the Ethernet driver to provide the time tuple.
* @param[in]     rateDeviation Rate deviation (resolution: 2-41), by which the PHC is requested to be corrected
* @param[in]     offset Time offset, by which the PHC is requested to be updated
* @return        Error status
* @retval        E_OK: successfully read the timestamp
* @retval        E_NOT_OK: development error was detected or fail to read the TimeStamp.
* implements     Eth_SetPhcCorrection_Activity
*/
Std_ReturnType Eth_43_GMAC_SetPhcCorrection
(
    uint8 CtrlIdx,
    uint8 ClkUnitIdx,
    sint32 rateDeviation,
    sint32 offset
);
#endif /* (STD_ON == ETH_43_GMAC_PHC_ENABLED) */

/**
* @brief         Activates egress time stamping on a dedicated message object.
* @note          Some HW does store once the egress time stamp marker and some HW needs it
*                always before transmission. There will be no disable functionality, due to the fact,
*                that the message type is always "time stamped" by network design.
* @api
* @param[in]     CtrlIdx Index of the controller which counter state shall be
*                enable the TimeStamp
* @param[in]     BufIdx Index of the message buffer, where Application expects egress time
*                stamping
* implements    Eth_EnableEgressTimeStamp_Activity
*/
void Eth_43_GMAC_EnableEgressTimeStamp   ( \
                                uint8 CtrlIdx, \
                                Eth_BufIdxType BufIdx \
                                        );
#endif
#if (STD_ON == ETH_43_GMAC_HAS_EXTERNAL_RX_BUFFERS)

/**
* @brief         Provides the next buffer in which data will be received on a given queue.
*
* @api
* @param[in]     CtrlIdx Index of the controller
* @param[in]     FifoIdx Index of the Fifo for which the current Buffer is provided.
* @param[in]     BufferDataAddress  Pointer to a continuous memory where the data buffer is located.
* implements    Eth_ProvideRxBuffer_Activity
*/
void Eth_43_GMAC_ProvideRxBuffer(uint8 CtrlIdx, \
                                        uint8 FifoIdx, \
                                        uint8* BufferDataAddress);

#endif /* ETH_43_GMAC_HAS_EXTERNAL_RX_BUFFERS  */

/**
* @brief         Provides access to a transmit buffer of the specified
*                controller.
* @warning       The application should handle possible difference between the
*                requested and granted buffer lengths. It is not necessary to
*                use whole granted buffer i.e. some space at the end may not
*                be written.
* @api
* @param[in]     CtrlIdx Index of the controller which buffer shall be provided.
*                The index is valid within the context of the Ethernet Driver
*                only.
* @param[in]     Priority Frame priority for transmit buffer FIFO selection
* @param[out]    BufIdxPtr Index to the granted transmit buffer resource.
*                It uniquely identifies the buffer in all subsequent calls of
*                functions Eth_Transmit() and Eth_TxConfirmation().
* @param[out]    BufPtr Pointer to the granted buffer. This is the space where
*                the data to be transmitted shall be stored.
* @param[in,out] LenBytePtr Buffer payload length
*                - In: desired length in bytes
*                - Out: granted length in bytes
* @return        Error and buffer status
* @retval        BUFREQ_OK: Buffer was successfully granted and no error has
*                occurred.
* @retval        BUFREQ_E_NOT_OK: A development error was detected and no buffer
*                was granted.
* @retval        BUFREQ_E_BUSY: All available buffers in use therefore no
*                buffer was granted. No error has been detected.
* implements    Eth_ProvideTxBuffer_Activity
*/
BufReq_ReturnType Eth_43_GMAC_ProvideTxBuffer( \
                            uint8 CtrlIdx, \
                            uint8 Priority, \
                            Eth_BufIdxType *BufIdxPtr, \
                            uint8 **BufPtr, \
                            uint16 *LenBytePtr \
                                     );

#if (STD_ON == ETH_43_GMAC_HAS_EXTERNAL_TX_BUFFERS)
/**
* @brief        Sends the given frame using a dedicated queue, decided based on the priority of the frame.
*               The frame is stored in an externally allocated buffer.
* @warning      The application provides a buffer with data which contains continuous
*                information from the header and the payload.
*                The buffer address must be placed in Non-cacheable memory in case no external cache operations are performed.
*                If cache management support is not explicitly handled, the external buffers need to be allocated in a non-cacheable memory region.
* @api
* @param[in]     CtrlIdx Index of the controller which buffer shall be provided.
*                The index is valid within the context of the Ethernet Driver
*                only.
* @param[in]     Priority Frame priority for transmit buffer FIFO selection
* @param[in]     BufferData Pointer to the data buffer.
* @param[in,out] BufferLength Pointer to the buffer length.
                 IN: Must contain the size of header + the size of payload.
                 OUT: The available buffer length (only in case of BUFREQ_E_OVFL return value)
* @param[out]    BufIdxPtr Index to the granted transmit buffer resource. It uniquely identifies the buffer in all subsequent calls of Eth_TxConfirmation()
* @param[in]     TxConfirmation Activates transmission confirmation.

* @return        BufReq_ReturnType Error and buffer status
* @retval        BUFREQ_OK: The frame was successfully enqueued for transmission.
* @retval        BUFREQ_E_NOT_OK: A development error was detected and no buffer
*                was granted.
* @retval        BUFREQ_E_BUSY: All available buffers in use therefore no buffer was granted. No error has been detected.
* @retval        BUFREQ_E_OVFL: The buffer length exceeds the dimension configured for the TX buffers.
* implements    Eth_SendFrame_Activity
*/
BufReq_ReturnType Eth_43_GMAC_SendFrame( \
                            uint8   CtrlIdx, \
                            uint8   Priority, \
                            uint8*  BufferData, \
                            uint16* BufferLength, \
                            Eth_BufIdxType* BufIdxPtr, \
                            boolean TxConfirmation\
                            );
#endif

#if (STD_ON == ETH_43_GMAC_SEND_MULTI_BUFFER_FRAME_API)
/**
* @brief        Sends the given frame, which is scattered in multiple buffers, using a dedicated queue, decided based on the priority of the frame.
* @warning      The application provides a list of buffers with data which contains continuous
*                information from the header and the payload.
*                The buffer address must be placed in Non-cacheable memory in case no external cache operations are performed.
*                If cache management support is not explicitly handled, the external buffers need to be allocated in a non-cacheable memory region.
* @api
* @param[in]     CtrlIdx Index of the controller which buffer shall be provided.
*                The index is valid within the context of the Ethernet Driver
*                only.
* @param[in]     Priority Frame priority for transmit buffer FIFO selection
* @param[in]     Frame A structure defining the multi buffer frame
* @param[out]    BufIdxPtr Index to the granted transmit buffer resource. It uniquely identifies the buffer in all subsequent calls of Eth_TxConfirmation().
* @param[in]     TxConfirmation Activates transmission confirmation.

* @return        BufReq_ReturnType Error and buffer status
* @retval        BUFREQ_OK: The frame was successfully enqueued for transmission.
* @retval        BUFREQ_E_NOT_OK: A development error was detected and no buffer
*                was granted.
* @retval        BUFREQ_E_BUSY: All available buffers in use therefore no
*                buffer was granted. No error has been detected.
* @retval        BUFREQ_E_OVFL: The buffer length exceeds the dimension configured for the TX buffers.
* implements    Eth_SendMultiBufferFrame_Activity
*/
BufReq_ReturnType Eth_43_GMAC_SendMultiBufferFrame( uint8 CtrlIdx, \
                                                            uint8 Priority, \
                                                            Eth_43_GMAC_MultiBufferFrameType Frame, \
                                                            Eth_BufIdxType* BufIdxPtr, \
                                                            boolean TxConfirmation);
#endif

/**
* @brief         Triggers transmission of a previously granted and then filled
*                transmit buffer.
* @api
* @param[in]     CtrlIdx Index of the controller which buffer shall be
*                transmitted. The index is valid within the context of
*                the Ethernet Driver only.
* @param[in]     BufIdx Index of the buffer resource to be transmitted.
* @param[in]     FrameType Desired value of the Ethernet frame type in the
*                frame header.
* @param[in]     TxConfirmation Activates transmission confirmation.
* @param[in]     LenByte Buffer data length in bytes (payload length).
* @param[in]     PhysAddrPtr Physical target address (MAC address) in network
*                byte order.
* @return        Error status
* @retval        E_OK No error was detected during the function execution.
* @retval        E_NOT_OK Development error was detected and the function
*                failed.
* implements    Eth_Transmit_Activity
*/
Std_ReturnType Eth_43_GMAC_Transmit     (
                           uint8 CtrlIdx,
                           Eth_BufIdxType BufIdx,
                           Eth_FrameType FrameType,
                           boolean TxConfirmation,
                           uint16 LenByte,
                           const uint8 *PhysAddrPtr
                            );

/**
* @brief         Triggers frames reception notifications.
* @details       All receive buffers are checked and the first received frame is
*                passed to the EthIf module. The caller is notified whether any
*                frame was received and whether more frames are available in the
*                receive queue.
* @api
* @param[in]     CtrlIdx Index of the controller which shall be checked whether
*                any new frames were received. The index is valid within
*                the context of the Ethernet Driver only.
* @param[in]     FifoIdx Specifies the related fifo
* @param[out]    RxStatusPtr Informs the caller whether a frame was received
*                (@c ETH_RECEIVED or @c ETH_NOT_RECEIVED) and whether more frames
*                are available in the queue (@c ETH_RECEIVED or
*                @c ETH_RECEIVED_MORE_DATA_AVAILABLE).
* implements    Eth_Receive_Activity
*/
void Eth_43_GMAC_Receive(uint8 CtrlIdx, \
                        uint8 FifoIdx,  \
                        Eth_RxStatusType *RxStatusPtr   \
                       );

/**
* @brief         Triggers frames reception notifications.
* @details       Indication from the upper layer to release the reception buffer
*                (ingress queue element) of the given physical Ethernet controller
* @api
* @param[in]     CtrlIdx Index of the controller within the context of the Driver
* @param[in]     RxHandleId Unique receive handle id provided by the Ethernet Driver in
*                a previous call of EthIf_RxIndication, to identify the ingress queue
*                element per physical Ethernet controller
*
* implements     Eth_ReleaseRxBuffer_Activity
*/
void Eth_43_GMAC_ReleaseRxBuffer (uint8 CtrlIdx, Eth_BufIdxType RxHandleId);

/**
* @brief         Triggers frame transmission confirmations.
* @api
* @param[in]     CtrlIdx Index of the controller which shall be checked whether
*                any frame transmission has finished. The index is valid within
*                the context of the Ethernet Driver only.
* @details       All transmit buffers are checked and upper layers are informed
*                about successfully transmitted frames. Buffers containing
*                transmitted frames are unlocked after the confirmation.
* implements    Eth_TxConfirmation_Activity
*/
void Eth_43_GMAC_TxConfirmation(uint8 CtrlIdx);

#if STD_ON == ETH_43_GMAC_VERSION_INFO_API
/**
* @brief         Returns the version information of this module.
* @api
* @param[out]    VersionInfoPtr Pointer where to store the version information
*                of this particular module instance.
* implements    Eth_GetVersionInfo_Activity
*/
void Eth_43_GMAC_GetVersionInfo(Std_VersionInfoType *VersionInfoPtr);
#endif /* ETH_43_GMAC_VERSION_INFO_API */


#if (STD_ON == ETH_43_GMAC_TIME_AWARE_SHAPER)
/**
 * @brief           Start Time-Aware Shaper
 * @details         This function starts the Time-Aware Shaper (TAS, IEEE 802.1Qbv) for the given ethernet controller
 *
 * @param[in]       CtrlIdx Index of the ethernet controller
 *
 * @return          Result of the operation
 * @retval          E_OK        successful.
 * @retval          E_NOT_OK    failed.
 *
 * @api
 *
 * @implements Eth_StartTas_Activity
 */
Std_ReturnType Eth_43_GMAC_StartTas( uint8 CtrlIdx);

/**
 * @brief           Stop Time-Aware Shaper
 * @details         This function stops the Time-Aware Shaper (TAS, IEEE 802.1Qbv) for the given ethernet controller
 *
 * @param[in]       CtrlIdx Index of the ethernet controller
 *
 * @return          Result of the operation
 * @retval          E_OK        successful.
 * @retval          E_NOT_OK    failed.
 *
 * @api
 *
 * @implements Eth_StopTas_Activity
 */
Std_ReturnType Eth_43_GMAC_StopTas( uint8 CtrlIdx);
#endif




#if (STD_ON == ETH_43_GMAC_PPS_OUTPUT_SUPPORT)
/**
 * @brief           Set Pulse-per-second (PPS) output signal mode
 * @details         This function set Pulse-per-second (PPS) output signal mode for the given ethernet controller
 *
 * @param[in]       CtrlIdx Index of the ethernet controller
 * @param[in]       ClkUnitIdx Index of the Clock Unit
 * @param[in]       SignalMode TRUE: PPS signal generation is enabled. FALSE: PPS signal generation is disabled
 *
 * @return          Result of the operation
 * @retval          E_OK        successful.
 * @retval          E_NOT_OK    failed.
 *
 * @api
 *
 */
 /* implements Eth_SetPpsSignalMode_Activity */
Std_ReturnType Eth_43_GMAC_SetPpsSignalMode(uint8 CtrlIdx, uint8 ClkUnitIdx, boolean SignalMode);

/**
 * @brief           Initialize PPS outputs signal.
 *
 * @details         This function works only with Flexible PPS mode selected(Eth_43_GMAC_SetPpsSignalMode(CtrlIdx, FALSE)).
 *
 * @param[in] CtrlIdx             Index of the ethernet controller
 * @param[in] PPSOutputsNum       The number of PPS outputs
 * @param[in] PPSOutputConfig     The configuration of PPS outputs
 *
 * @return          Result of the operation
 * @retval          E_OK        successful.
 * @retval          E_NOT_OK    failed.
 *
 * @api
 *
 */
Std_ReturnType Eth_43_GMAC_PPSOutputSignalInit(uint8 CtrlIdx, uint8 PPSOutputsNum, const Eth_43_GMAC_FlexiblePPSOutputType PPSOutputConfig[]);

/**
 * @brief           Update Pulse-per-second (PPS) output signal configuration
 * @details         This function update Flexible Pulse-per-second (PPS) output signal configuration for the given ethernet controller
 *                  This function works only with Flexible PPS mode selected(Eth_43_GMAC_SetPpsSignalMode(CtrlIdx, FALSE)).
 *
 * @param[in]       CtrlIdx Index of the ethernet controller
 * @param[in]       PPSOutputIdx The index of PPS output
 * @param[in]       PPSConfig The updated configuration
 *
 * @return          Result of the operation
 * @retval          E_OK        successful.
 * @retval          E_NOT_OK    failed.
 *
 * @api
 *
 */
Std_ReturnType Eth_43_GMAC_UpdatePpsConfig(uint8 CtrlIdx, uint8 PPSOutputIdx, Eth_43_GMAC_PPSConfigType * PPSConfig);
#endif /* STD_ON == ETH_43_GMAC_PPS_OUTPUT_SUPPORT */



#define ETH_43_GMAC_STOP_SEC_CODE
#include "Eth_43_GMAC_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* ETH_H */
