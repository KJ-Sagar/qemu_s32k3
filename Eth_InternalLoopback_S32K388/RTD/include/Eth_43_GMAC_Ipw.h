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

#ifndef ETH_43_GMAC_IPW_H
#define ETH_43_GMAC_IPW_H

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
#include "Eth_43_GMAC_Ipw_Cfg.h"
#include "EthIf.h"
#include "Gmac_Ip_Types.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ETH_43_GMAC_IPW_VENDOR_ID                    43
#define ETH_43_GMAC_IPW_AR_RELEASE_MAJOR_VERSION     4
#define ETH_43_GMAC_IPW_AR_RELEASE_MINOR_VERSION     9
#define ETH_43_GMAC_IPW_AR_RELEASE_REVISION_VERSION  0
#define ETH_43_GMAC_IPW_SW_MAJOR_VERSION             7
#define ETH_43_GMAC_IPW_SW_MINOR_VERSION             0
#define ETH_43_GMAC_IPW_SW_PATCH_VERSION             1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Eth_43_GMAC_Ipw_Cfg.h */
#if (ETH_43_GMAC_IPW_VENDOR_ID != ETH_43_GMAC_IPW_CFG_VENDOR_ID)
    #error "Eth_43_GMAC_Ipw.h and Eth_43_GMAC_Ipw_Cfg.h have different vendor ids"
#endif
#if ((ETH_43_GMAC_IPW_AR_RELEASE_MAJOR_VERSION    != ETH_43_GMAC_IPW_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (ETH_43_GMAC_IPW_AR_RELEASE_MINOR_VERSION    != ETH_43_GMAC_IPW_CFG_AR_RELEASE_MINOR_VERSION) || \
     (ETH_43_GMAC_IPW_AR_RELEASE_REVISION_VERSION != ETH_43_GMAC_IPW_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AUTOSAR Version Numbers of Eth_43_GMAC_Ipw.h and Eth_43_GMAC_Ipw_Cfg.h are different"
#endif
#if ((ETH_43_GMAC_IPW_SW_MAJOR_VERSION != ETH_43_GMAC_IPW_CFG_SW_MAJOR_VERSION) || \
     (ETH_43_GMAC_IPW_SW_MINOR_VERSION != ETH_43_GMAC_IPW_CFG_SW_MINOR_VERSION) || \
     (ETH_43_GMAC_IPW_SW_PATCH_VERSION != ETH_43_GMAC_IPW_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Eth_43_GMAC_Ipw.h and Eth_43_GMAC_Ipw_Cfg.h are different"
#endif
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
   /* Checks against EthIf.h */
    #if ((ETH_43_GMAC_IPW_AR_RELEASE_MAJOR_VERSION != ETHIF_AR_RELEASE_MAJOR_VERSION) || \
         (ETH_43_GMAC_IPW_AR_RELEASE_MINOR_VERSION != ETHIF_AR_RELEASE_MINOR_VERSION))
        #error "AUTOSAR Version Numbers of Eth_43_GMAC_Ipw.h and EthIf.h are different"
    #endif
#endif
/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/
#define ETH_43_GMAC_START_SEC_VAR_CLEARED_32
#include "Eth_43_GMAC_MemMap.h"

extern Eth_43_GMAC_axTxBufferIdxMapType Eth_43_GMAC_axTxBufferIdxMap[ETH_43_GMAC_MAX_CTRLIDX_SUPPORTED][ETH_43_GMAC_MAX_TXFIFO_SUPPORTED * ETH_43_GMAC_MAX_TXBUFF_SUPPORTED];

#define ETH_43_GMAC_STOP_SEC_VAR_CLEARED_32
#include "Eth_43_GMAC_MemMap.h"

#define ETH_43_GMAC_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Eth_43_GMAC_MemMap.h"

/* Pointers to IPW configuration structures stored for later use */
extern const Eth_43_GMAC_Ipw_CtrlConfigType *Eth_43_GMAC_Ipw_apxInternalCfg[ETH_43_GMAC_MAX_CTRLIDX_SUPPORTED];


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

extern Eth_43_GMAC_QueueInfo Eth_43_GMAC_axTransmissionRequests[ETH_43_GMAC_MAX_CTRLIDX_SUPPORTED][ETH_43_GMAC_MAX_TXFIFO_SUPPORTED];

/**
 * @brief        Last queue tail updated in the transmission requests
 * @details      Keeps track of the last queue tail updated in the "Eth_43_GMAC_axTransmissionRequests"
 *               in its state before the update.
*/
extern Eth_43_GMAC_axTxBufferIdxMapType *Eth_43_GMAC_pLastTransmissionRequestQueueTail;

#define ETH_43_GMAC_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Eth_43_GMAC_MemMap.h"

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
#define ETH_43_GMAC_START_SEC_CODE
#include "Eth_43_GMAC_MemMap.h"

void Eth_43_GMAC_Ipw_SafetyIrqCallback(const uint8 CtrlIdx, const Gmac_Ip_SafetyErrorType Error);

extern boolean Eth_43_GMAC_Ipw_CheckAccessToController(const uint8 CtrlIdx);
extern Std_ReturnType Eth_43_GMAC_Ipw_TxTimeAwareShaperInit ( \
                                    uint8 CtrlIdx, \
                                    const Eth_43_GMAC_Ipw_CtrlConfigType *IpwCtrlCfg \
                                    );
extern Eth_ModeType Eth_43_GMAC_Ipw_GetControllerMode(const uint8 CtrlIdx);
extern Std_ReturnType Eth_43_GMAC_Ipw_ConfigureController  ( \
                                    const uint8 CtrlIdx, \
                                    const Eth_43_GMAC_Ipw_CtrlConfigType *IpwCtrlCfg, \
                                    const Eth_43_GMAC_ClockCfgType *ClkCfg \
                                         );
extern Std_ReturnType Eth_43_GMAC_Ipw_EnableController(const uint8 CtrlIdx);
extern Std_ReturnType Eth_43_GMAC_Ipw_DisableController(const uint8 CtrlIdx);
extern void Eth_43_GMAC_Ipw_GetPhysicalAddress  ( \
                                        const uint8 CtrlIdx, \
                                        uint8 *PhysAddrPtr \
                                         );

extern void Eth_43_GMAC_Ipw_SetPhysicalAddress ( \
                                        const uint8 CtrlIdx, \
                                        const uint8 *PhysAddrPtr \
                                        );

#if STD_ON == ETH_43_GMAC_GET_COUNTER_API
extern Std_ReturnType Eth_43_GMAC_Ipw_GetCounterValues  ( \
                               uint8 CtrlIdx, \
                               Eth_CounterType *CounterPtr \
                                           );
#endif
#if STD_ON == ETH_43_GMAC_GET_RXSTATS_API
extern Std_ReturnType Eth_43_GMAC_Ipw_GetRxStats ( \
                       uint8 CtrlIdx, \
                       Eth_RxStatsType *RxStatsPtr \
                                         );
#endif

#if STD_ON == ETH_43_GMAC_UPDATE_PHYS_ADDR_FILTER_API
extern Std_ReturnType Eth_43_GMAC_Ipw_UpdatePhysAddrFilter ( \
                                    uint8 CtrlIdx, \
                                    const uint8 *PhysAddr, \
                                    Eth_FilterActionType Action \
                                    );
#endif

extern BufReq_ReturnType Eth_43_GMAC_Ipw_ProvideTxBuffer (  \
                                    const uint8 CtrlIdx, \
                                    const uint8 FifoIdx, \
                                    Eth_BufIdxType * const BufferIdx, \
                                    uint8 **FrameBuffer, \
                                    uint16 * const FrameLength \
                                          );

#if (STD_ON == ETH_43_GMAC_HAS_EXTERNAL_RX_BUFFERS)
extern void Eth_43_GMAC_Ipw_ProvideRxBuffer(uint8 CtrlIdx, \
          uint8 FifoIdx, \
          uint8 *BufferData);
#endif

extern Std_ReturnType Eth_43_GMAC_Ipw_Transmit ( \
                                        const uint8 CtrlIdx, \
                                        const uint8 FifoIdx, \
                                        uint8 *Buffer, \
                                        const uint16 Length, \
                                        const Eth_BufIdxType u32BufferIdx
                                       );
#if (STD_ON == ETH_43_GMAC_SEND_MULTI_BUFFER_FRAME_API)
BufReq_ReturnType Eth_43_GMAC_Ipw_SendMultiBufferFrame(uint8 CtrlIdx,
                                                uint8 FifoIdx,
                                                Eth_43_GMAC_MultiBufferFrameType Frame, \
                                                Eth_BufIdxType* BufIdxPtr, \
                                                boolean TxConfirmation);
#endif
extern Eth_RxStatusType Eth_43_GMAC_Ipw_ReceiveFrame ( \
                                                const uint8 CtrlIdx, \
                                                const uint8 FifoIdx, \
                                                uint8 **FrameData, \
                                                uint16 *FrameLength, \
                                                boolean *FrameHasError
                                             );

extern void Eth_43_GMAC_Ipw_ReleaseResources ( \
                                const uint8 CtrlIdx, \
                                const uint8 QueueIdx,  \
                                uint8 * FrameData  \
                                     );

#if STD_ON == ETH_43_GMAC_MDIO_CLAUSE22_API
extern boolean Eth_43_GMAC_Ipw_WriteMii    ( \
                    const uint8 CtrlIdx, \
                    const uint8 Trcv, \
                    const uint8 Reg, \
                    const uint16 Data
                                   );
extern boolean Eth_43_GMAC_Ipw_ReadMii ( \
                        const uint8 CtrlIdx, \
                        const uint8 Trcv, \
                        const uint8 Reg, \
                        uint16 * const Data
                               );
#endif /* ETH_43_GMAC_MDIO_CLAUSE22_API */

#if STD_ON == ETH_43_GMAC_MDIO_CLAUSE45_API
extern boolean Eth_43_GMAC_Ipw_ReadMmd ( \
                             const uint8 CtrlIdx,\
                             const uint8 TrcvIdx, \
                             const uint8 Mmd, \
                             const uint16 RegAddress,\
                             uint16 * RegValPtr
                        );
extern boolean Eth_43_GMAC_Ipw_WriteMmd ( \
                                    const uint8 CtrlIdx,\
                                    const uint8 TrcvIdx, \
                                    const uint8 Mmd, \
                                    const uint16 RegAddress,\
                                    const uint16 RegVal
                                );
#endif

#if STD_ON == ETH_43_GMAC_GET_TXSTATS_API
extern Std_ReturnType Eth_43_GMAC_Ipw_GetTxStats ( \
                       uint8 CtrlIdx, \
                       Eth_TxStatsType *TxStatsPtr \
                                         );
#endif

#if STD_ON == ETH_43_GMAC_GET_TXERROR_COUNTER_API
extern Std_ReturnType Eth_43_GMAC_Ipw_GetTxErrorCounterValues ( \
                       uint8 CtrlIdx, \
                       Eth_TxErrorCounterValuesType *TxErrorCounterValuesPtr \
                                               );
#endif

#if STD_ON == ETH_43_GMAC_GLOBAL_TIME_API
/*================================================================================================*/
/**
* @brief        Allows the Time Master to adjust the global ETH Reference clock in HW.
* @details      We can use this method to set a global time base on ETH in general or to
*               synchronize the global ETH time base with another time base, e.g. FlexRay.
* @param[in]    CtrlIdx Index of the TM controller which time shall be adjusted.
* @param[in]    ClkCfg Clock for timestamp
* @param[in]    timeStampPtr Pointer to new time stamp.
*/
extern Std_ReturnType Eth_43_GMAC_Ipw_SetGlobalTime( \
                      uint8 CtrlIdx, \
                      const Eth_43_GMAC_ClockCfgType *ClkCfg, \
                      const Eth_TimeStampType *TimeStampPtr);

extern Std_ReturnType Eth_43_GMAC_Ipw_SetCorrectionTime ( \
                        uint8 CtrlIdx, \
                        const Eth_43_GMAC_ClockCfgType *ClkCfg, \
                        const Eth_TimeIntDiffType *TimeOffsetPtr, \
                        const Eth_RateRatioType* RateRatioPtr \
                            );
extern Std_ReturnType Eth_43_GMAC_Ipw_GetCurrentTime    ( \
                                uint8 CtrlIdx, \
                                Eth_TimeStampQualType *TimeQualPtr, \
                                Eth_TimeStampType *TimeStampPtr \
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
* @param[out]    pCurrentTimeTuplePtr Current time tuple with the value of the clock used for timestamping and the value of adjustable PHC.
* @return        Error status
* @retval        E_OK: successfully read the timestamp
* @retval        E_NOT_OK: development error was detected or fail to read the TimeStamp.
*/
extern Std_ReturnType Eth_43_GMAC_Ipw_GetCurrentTimeTuple(uint8 CtrlIdx, \
                                                uint8 ClkUnitIdx, \
                                                const Eth_43_GMAC_CtrlCfgType *CtrlConfig, \
                                                TimeTupleType *pCurrentTimeTuplePtr);

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
* @param[out]    pTimeQualPtr Quality of HW time stamp, e.g. based on current drift
* @param[out]    pTimeStampPtr Current time stamp
* @return        Error status
* @retval        E_OK: successfully read the timestamp
* @retval        E_NOT_OK: development error was detected or fail to read the TimeStamp.
*/
extern Std_ReturnType Eth_43_GMAC_Ipw_GetPhcTime(uint8 CtrlIdx, \
                                            uint8 ClkUnitIdx, \
                                            const Eth_43_GMAC_CtrlCfgType *CtrlConfig, \
                                            TimeStampQualType *pTimeQualPtr, \
                                            TimeStampType *pTimeStampPtr);

/**
* @brief         Sets the absolute time of the PHC.
*
* @note          Sets the absolute time of the PHC.

* @api
* @param[in]     CtrlIdx Index of the controller shall be read the time value.
* @param[in]     ClkUnitIdx Index of the Clock Unit within the context of the Ethernet driver to provide the time tuple.
* @param[in]    pTimeStampPtr Current time stamp
* @return        Error status
* @retval        E_OK: successfully read the timestamp
* @retval        E_NOT_OK: development error was detected or fail to read the TimeStamp.
*/
extern Std_ReturnType Eth_43_GMAC_Ipw_SetPhcTime(uint8 CtrlIdx, \
                                            uint8 ClkUnitIdx, \
                                            const Eth_43_GMAC_CtrlCfgType *CtrlConfig, \
                                            const TimeStampType *pTimeStampPtr);

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
*/
extern Std_ReturnType Eth_43_GMAC_Ipw_SetPhcCorrection(uint8 CtrlIdx, \
                                            uint8 ClkUnitIdx, \
                                            const Eth_43_GMAC_CtrlCfgType *CtrlConfig, \
                                            sint32 rateDeviation,
                                            sint32 offset);
#endif /* (STD_ON == ETH_43_GMAC_PHC_ENABLED) */
/**
* @brief        Enable egress time stamping on a transmission message.
* @details      For GMAC IP the timestamp feature is enabled from configuration - after the call of Eth_43_GMAC__Init the timestamp will be enabled for all packets.
*               There will be no "disable" functionality, due to the fact, that the message type is always "time stamped" by network design.
* @param[in]    CtrlIdx Index of controller to be update the filter
* @param[in]    BufIdx Index of the message buffer, where Application expects egress time stamping.
*/
extern void Eth_43_GMAC_Ipw_EnableEgressTimeStamp( \
                                uint8 CtrlIdx, \
                                Eth_BufIdxType BufIdx \
                                            );

extern void Eth_43_GMAC_Ipw_GetEgressTimeStamp  ( \
                                        const uint8 CtrlIdx, \
                                        const Eth_BufIdxType BufIdx, \
                                        Eth_TimeStampQualType *TimeQual, \
                                        Eth_TimeStampType *TimeStamp \
                                        );

extern void Eth_43_GMAC_Ipw_GetIngressTimeStamp ( \
                                        const uint8 CtrlIdx, \
                                        const uint8 FifoIdx, \
                                        const uint8 *FrameData, \
                                        Eth_TimeStampQualType *TimeQual, \
                                        Eth_TimeStampType *TimeStamp \
                                        );
#endif

#if (STD_ON == ETH_43_GMAC_DEM_EVENT_DETECT)
extern boolean Eth_43_GMAC_Ipw_ErrorDetected( \
                                    const uint8 CtrlIdx, \
                                    const Eth_43_GMAC_DemErrorIdType DemErrorId \
                                    );
#endif

extern void Eth_43_GMAC_Ipw_ReportTransmission(
                                const Eth_43_GMAC_CtrlCfgType *EthControllerConfig, \
                                const uint8 FifoIdx \
                           );

#if (STD_ON == ETH_43_GMAC_TIME_AWARE_SHAPER)
/**
 * @brief           Start Time-Aware Shaper
 * @details         This function starts the Time-Aware Shaper (TAS, IEEE 802.1Qbv) for the given ethernet controller
 *
 * @param[in]       CtrlIndex Index of the ethernet controller
 *
 * @return          Result of the operation
 * @retval          E_OK        successful.
 * @retval          E_NOT_OK    failed.
 *
 * @api
 *
 */
Std_ReturnType  Eth_43_GMAC_Ipw_StartTas( uint8 CtrlIndex );

/**
 * @brief           Stop Time-Aware Shaper
 * @details         This function stops the Time-Aware Shaper (TAS, IEEE 802.1Qbv) for the given ethernet controller
 *
 * @param[in]       CtrlIndex Index of the ethernet controller
 *
 * @return          Result of the operation
 * @retval          E_OK        successful.
 * @retval          E_NOT_OK    failed.
 *
 * @api
 *
 */
Std_ReturnType  Eth_43_GMAC_Ipw_StopTas( uint8 CtrlIndex );
#endif

#if (STD_ON == ETH_43_GMAC_PPS_OUTPUT_SUPPORT)
/**
 * @brief           Set Pulse-per-second (PPS) output signal mode
 * @details         This function set Pulse-per-second (PPS) output signal mode for the given ethernet controller
 *
 * @param[in]       CtrlIdx Index of the ethernet controller
 * @param[in]       SignalMode TRUE: PPS signal generation is enabled. FALSE: PPS signal generation is disabled
 * @param[in]       CtrlConfig Store controller configuration
 *
 * @return          Result of the operation
 * @retval          E_OK        successful.
 * @retval          E_NOT_OK    failed.
 *
 * @api
 *
 */
Std_ReturnType Eth_43_GMAC_Ipw_SetPpsSignalMode(const uint8 CtrlIdx, const Eth_43_GMAC_CtrlCfgType *CtrlConfig, uint8 ClkUnitIdx, boolean SignalMode);

/*!
 * @brief Initialize PPS outputs signal.
 *
 *
 * @param[in] CtrlIdx             Instance number
 * @param[in] CtrlConfig          Store controller configuration
 * @param[in] PPSOutputsNum       The number of PPS outputs
 * @param[in] PPSOutputConfig     The configuration of PPS outputs
 */
Std_ReturnType Eth_43_GMAC_Ipw_PPSOutputSignalInit(uint8 CtrlIdx, const Eth_43_GMAC_CtrlCfgType *CtrlConfig, uint8 PPSOutputsNum, const Eth_43_GMAC_FlexiblePPSOutputType PPSOutputConfig[]);

/**
 * @brief           Update Pulse-per-second (PPS) output signal configuration
 * @details         This function update Pulse-per-second (PPS) output signal configuration for the given ethernet controller
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
Std_ReturnType Eth_43_GMAC_Ipw_UpdatePpsConfig(uint8 CtrlIdx, uint8 PPSOutputIdx, Eth_43_GMAC_PPSConfigType * PPSConfig);
#endif /* (STD_ON == ETH_43_GMAC_PPS_OUTPUT_SUPPORT) */

#define ETH_43_GMAC_STOP_SEC_CODE
#include "Eth_43_GMAC_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* ETH_43_GMAC_IPW_H */
