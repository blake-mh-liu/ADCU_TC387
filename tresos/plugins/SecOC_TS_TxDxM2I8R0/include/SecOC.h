/**
 * \file
 *
 * \brief AUTOSAR SecOC
 *
 * This file contains the implementation of the AUTOSAR
 * module SecOC.
 *
 * \version 2.8.14
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef SECOC_H
#define SECOC_H

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

/* !LINKSTO SecOC.ASR430.RxTx.SWS_SecOC_00001,1 */
#include <SecOC_Cfg.h>
#include <SecOC_Lcfg.h>
#include <SecOC_PBcfg.h>

/*==================[macros]======================================================================*/

#if !(defined SECOC_API_VERSION_430)
/** \brief  Macro representing the value for Api version SECOC_API_VERSION_430 **/
#define SECOC_API_VERSION_430   0x00U
#endif /* #if !(defined SECOC_API_VERSION_430) */

#if !(defined SECOC_API_VERSION_20_11)
/** \brief  Macro representing the value for Api version SECOC_API_VERSION_20_11 **/
#define SECOC_API_VERSION_20_11   0x01U
#endif /* #if !(defined SECOC_API_VERSION_20_11) */

#if (defined SECOC_INSTANCE_ID)
#error SECOC_INSTANCE_ID already defined
#endif /* #if (defined SECOC_INSTANCE_ID) */
/** \brief Id of instance of SecOC */
#define SECOC_INSTANCE_ID                 0U

/** \brief Macro to calculate the number of bytes required for a number of bits
 */
#if (defined SECOC_REQUIREDBYTES)
#error SECOC_REQUIREDBYTES already defined
#endif /* #if (defined SECOC_REQUIREDBYTES) */
#define SECOC_REQUIREDBYTES(Bits)  (uint32) (((uint32)(Bits) / 8U) +        \
                                            ((((uint32)(Bits) % 8U) > 0U)? 1U : 0U))

/** \brief This macro is used to avoid compiler warnings for unused parameters.
 *
 * In some cases, parameters are specified by AUTOSAR for an interface but are not used.
 */
#if (defined SECOC_PARAM_UNUSED)
#error SECOC_PARAM_UNUSED already defined
#endif /* #if (defined SECOC_PARAM_UNUSED) */
#define SECOC_PARAM_UNUSED(x) ((void)(x))

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/* \cond DONTDOCUMENT */

#define SECOC_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <SecOC_MemMap.h>

/** \brief Pointer used to access the initialization structure that it is used during
 *         the init phase, when the SecOC_Init is called
 */
extern P2CONST(SecOC_ConfigType, AUTOMATIC, SECOC_APPL_CONST) SecOC_ConfigPtr;

#define SECOC_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <SecOC_MemMap.h>

#define SECOC_START_SEC_VAR_INIT_8
#include <SecOC_MemMap.h>

/**
 * \brief Initialization status of the SecOC. It is declared as volatile to
 *        prevent the compiler from reordering accesses to this variable because
 *        we rely on the sequence of assignments in SecOC_Init() and SecOC_DeInit()
 */
extern volatile VAR(SecOC_StateType, SECOC_VAR) SecOC_InitStatus;

#define SECOC_STOP_SEC_VAR_INIT_8
#include <SecOC_MemMap.h>

#define SECOC_START_SEC_VAR_CLEARED_8
#include <SecOC_MemMap.h>

/** \brief Array used for holding the received and transmitted PDUs
 */
extern VAR(uint8, SECOC_VAR) SecOC_PB_PduBuffer[SECOC_PB_PDU_MEM_SIZE];

/** \brief Array used for holding the internal data that is required for processing the verification
 *         and the authentication
 */
extern VAR(uint8, SECOC_VAR) SecOC_PB_IntBuffer[SECOC_PB_INT_MEM_SIZE];

#define SECOC_STOP_SEC_VAR_CLEARED_8
#include <SecOC_MemMap.h>

/* \endcond */

/*==================[external function declarations]==============================================*/

#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

/**
 *
 * \brief Validates the post-build configuration data structure
 *
 * This function validates the post-build configuration data structure
 * passed to the SecOC_Init function.
 *
 * \param[in] voidConfigPtr  pointer to a SecOC post-build data structure. If a NULL_PTR is passed,
 *                           the SecOC will attempt to retrieve the SecOC post-build
 *                           configuration from the PbcfgM module.
 *
 * \returns the status of the request
 * \retval E_OK       When the pre-compile, link-time and platform hash values stored
 *                    within the post-build structure correspond to the hash values of the
 *                    compiled source files.
 * \retval E_NOT_OK   Otherwise, E_NOT_OK will be returned.
 *
 */
extern FUNC(Std_ReturnType, SECOC_CODE) SecOC_IsValidConfig
(
  P2CONST(void, AUTOMATIC, SECOC_APPL_CONST) voidConfigPtr
);

/* !LINKSTO SecOC.ASR430.RxTx.SWS_SecOC_00106,1 */
/**
 *
 * \brief Init Function
 *
 * This function initializes the SecOC module.
 *
 * \param[in]  config        Pointer to a selected configuration structure.
 */
extern FUNC(void, SECOC_CODE) SecOC_Init
(
  P2CONST(SecOC_ConfigType, AUTOMATIC, SECOC_APPL_CONST) config
);

/* !LINKSTO SecOC.ASR430.RxTx.SWS_SecOC_00161,1 */
/**
 *
 * \brief DeInit Function
 *
 * This service stops the secure onboard communication.
 * All I-PDU buffers are cleared and have to be obtained again, if needed,
 * after SecOC_Init has been called.
 * By a call to SecOC_DeInit the AUTOSAR SecOC module is put into an not initialized state.
 *
 */
extern FUNC(void, SECOC_CODE) SecOC_DeInit
(
  void
);

#if (STD_ON == SECOC_VERSION_INFO_API)
/* !LINKSTO SecOC.ASR430.RxTx.SWS_SecOC_00107,1 */
/**
 *
 * \brief Function for SecOC version information
 *
 * \param[out]  versioninfo Pointer to a location where the version information of
 *                          this module is stored.
 *
 */
extern FUNC(void, SECOC_CODE) SecOC_GetVersionInfo
(
  P2VAR(Std_VersionInfoType, AUTOMATIC, SECOC_APPL_DATA) versioninfo
);
#endif /* #if (STD_ON == SECOC_VERSION_INFO_API) */

#if (STD_OFF == SECOC_INCLUDE_RTE)
#if (SECOC_NUMBER_RX_PDUS > 0)
#if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION)
/* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00122,3 */
/**
 * \brief This service enables the user to set the override verification status of a an I-PDU
 *        and to skip the verification procedure.(Compatible with AUTOSAR 4.3.0)
 *
 * This Service provides the ability to override the VerifyStatus with 'Fail'/'Pass' or
 * to skip the verification when using a specific Freshness Value ID to verify authenticity
 * of data making up an I-PDU.
 * Using this interface, VerifyStatus may be overridden
 * 1.  Indefinitely for received I-PDUs which use the specific Freshness Value ID for authentication
 *     verification
 * 2.  For a number of sequentially received I-PDUs which use the specific Freshness Value ID for
 *     authentication verification.
 * 3.  To skip the verification procedure for received I-PDUs which use the specific Freshness
 *     Value ID for authentication verification
 *
 *
 * \param[in] freshnessValueId            Identifier of a specific Freshness Value ID where override
 *                                        shall be applied to
 * \param[in] overrideStatus              0 = Override VerifyStatus to 'Fail' until further notice;
 *                                        1 = Override VerifyStatus to 'Fail' until
 *                                            NumberOfMessagesToOverride is reached
 *                                        2 = Cancel Override of VerifyStatus
 *                                        41 = Override VerifyStatus to "Pass" until
 *                                             NumberOfMessagesToOverride is reached; only available
 *                                             if SecOCEnableForcedPassOverride is set to TRUE
 *                                        43 = The verification procedure is skipped until
 *                                             further notice; only available
 *                                             if SecOCEnableForcedPassOverride is set to TRUE
 * \param[in] numberOfMessagesToOverride  Number of sequential VerifyStatus to override when using
 *                                        a specific counter for authentication verification.This
 *                                        is only considered when OverrideStatus is equal to 1/41
 *
 * \returns the status of the request
 * \retval E_OK     request successful
 * \retval E_NOT_OK request failed
 */
extern FUNC(Std_ReturnType, SECOC_CODE) SecOC_VerifyStatusOverride
(
  uint16 freshnessValueId,
  uint8  overrideStatus,
  uint8  numberOfMessagesToOverride
);
#else /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) */
/* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00122,1 */
/**
 * \brief This service enables the user to set the override verification status of a an I-PDU
 *        and to skip the verification procedure.(Compatible with AUTOSAR 20-11)
 *
 * This Service provides the ability to override the VerifyStatus with 'Fail'/'Pass' or
 * to skip the verification when using a specific Freshness Value ID/Data ID to verify authenticity
 * of data making up an I-PDU.
 * Using this interface, VerifyStatus may be overridden
 * 1.  Indefinitely for received I-PDUs which use the specific Freshness Value ID/Data ID for
 *     authentication verification
 * 2.  For a number of sequentially received I-PDUs which use the specific Freshness Value ID/Data
 *     ID for authentication verification.
 * 3.  To skip the verification procedure for received I-PDUs which use the specific Freshness
 *     Value ID/Data ID for authentication verification
 *
 *
 * \param[in] ValueId                     Identifier of the Value ID where override shall be applied
 *                                        to. If configuration option SecOCOverrideStatusWithDataId
 *                                        is set to TRUE,this value shall provide the DataID of the
 *                                        secured I-PDU. If SecOCOverrideStatusWithDataId is set to
 *                                        FALSE, this parameter shall provide the Identifier of a
 *                                        specific Freshness Value
 * \param[in] overrideStatus              0x00 = Override VerifyStatus to 'Fail' until further notice;
 *                                        0x01 = Override VerifyStatus to 'Fail' until
 *                                            NumberOfMessagesToOverride is reached
 *                                        0x02 = Cancel Override of VerifyStatus
 *                                        0x40 = Override VerifyStatus to 'Pass' until further
 *                                               notice; only available if
 *                                               SecOCEnableForcedPassOverride is set to TRUE
 *                                        0x41 = The verification procedure is skipped until
 *                                             NumberOfMessagesToOverride is reached; only available
 *                                             if SecOCEnableForcedPassOverride is set to TRUE
 *                                        0x42 = Override VerifyStatus to "Pass" until
 *                                             NumberOfMessagesToOverride is reached; only available
 *                                             if SecOCEnableForcedPassOverride is set to TRUE
 *                                        0x43 = The verification procedure is skipped until
 *                                             further notice; only available
 *                                             if SecOCEnableForcedPassOverride is set to TRUE
 * \param[in] numberOfMessagesToOverride  Number of sequential VerifyStatus to override when using
 *                                        a specific counter for authentication verification.
 *                                        This is only considered when OverrideStatus is equal to
 *                                        0x01/0x41/0x42
 *
 * \returns the status of the request
 * \retval E_OK     request successful
 * \retval E_NOT_OK request failed
 */
extern FUNC(Std_ReturnType, SECOC_CODE) SecOC_VerifyStatusOverride
(
  uint16                   ValueId,
  SecOC_OverrideStatusType overrideStatus,
  uint8                    numberOfMessagesToOverride
);
#endif /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) */
#endif /* #if (SECOC_NUMBER_RX_PDUS > 0) */
#endif /* #if (STD_OFF == SECOC_INCLUDE_RTE) */

#if (STD_ON == SECOC_RX_USETP)
/* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00130,1 */
/**
 * \brief This function is called at the start of receiving a Secured I-PDU.
 *
 * This function is called at the start of receiving a Secured I-PDU.
 * The Secured I-PDU might be fragmented into multiple N-PDUs (FF with one or more following CFs) or
 * might consist of a single N-PDU (SF).
 *
 * \param[in]  id               ID of the received secured I-PDU.
 * \param[in]  info             A pointer to a structure with received Secured I-PDU related data:
 *                              data length and pointer to I-SDU buffer
 * \param[in]  TpSduLength      complete length of the TP I-PDU to be received
 * \param[out] bufferSizePtr    Available receive buffer in the receiving module.
 *                              This parameter will be used to compute the Block Size (BS) in the
 *                              transport protocol module.
 *
 * \returns the status of the request
 * \retval BUFREQ_OK       Connection has been accepted. RxBuffer-SizePtr indicates the available
 *                         receive buffer.
 * \retval BUFREQ_E_BUSY
 * \retval BUFREQ_E_NOT_OK Connection has been rejected. RxBufferSizePtr remains unchanged.
 */
extern FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_StartOfReception
(
  PduIdType                                        id,
#if (STD_OFF == SECOC_ASR403_API)
  P2VAR(PduInfoType,   AUTOMATIC, SECOC_APPL_DATA) info,
#endif /* #if (STD_OFF == SECOC_ASR403_API) */
  PduLengthType                                    TpSduLength,
  P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) bufferSizePtr
);

/* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00128,1 */
/**
 * \brief This function is called to provide the received data of a Secured  I-PDU segment (N-PDU)
 *        to the SecOC module.
 *
 * This function is called to provide the received data of a Secured  I-PDU segment (N-PDU) to the
 * SecOC module . Each call to this function provides the next part of the I-PDU data.
 * The size of the remaining data is written to the position indicated by bufferSizePtr.
 *
 * \param[in]  id            ID of the received secured I-PDU.
 * \param[in]  info          A pointer to a structure with received secured I-PDU related data:
 *                           data length and pointer to I-SDU buffer
 * \param[out] bufferSizePtr Available receive buffer size after data has been copied.
 *
 * \returns the status of the request
 * \retval BUFREQ_OK       Data copied successfully
 * \retval BUFREQ_E_NOT_OK Data was not copied because an error occurred.
 */
extern FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_CopyRxData
(
  PduIdType                                          id,
  P2CONST(PduInfoType,   AUTOMATIC, SECOC_APPL_DATA) info,
  P2VAR(  PduLengthType, AUTOMATIC, SECOC_APPL_DATA) bufferSizePtr
);

/* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00125,1 */
/**
 * \brief Service to indicate reception of a Secured I-PDU via the TP API.
 *
 * Called by the PduR after a Secured I-PDU has been received via the TP API,
 * the result indicates the success or failure of the reception.
 * If success is indicated by 'result',
 * this call triggers the completion of the verification of the received Secured I-PDU.
 * Otherwise, if a failure of reception is indicated, the verification is not performed or stopped.
 *
 * \param[in] id     ID of the received Secured I-PDU.
 * \param[in] result Result of reception.
 *
 */
extern FUNC(void, SECOC_CODE) SecOC_TpRxIndication
(
  PduIdType      id,
  Std_ReturnType result
);
#endif /* #if (STD_ON == SECOC_RX_USETP) */

/* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00124,1 */
/**
 * \brief Service to indicate direct reception of a Secured I-PDU from a lower layer communication
 *        interface.
 *
 * This call triggers the verification of the received Secured I-PDU. Called by the PduR.
 *
 *
 * \param[in] id     ID of the received Secured I-PDU.
 * \param[in] info   A pointer to a structure with Secured I-PDU related data that is received:
 *                   data length and pointer to I-SDU buffer
 *
 */
extern FUNC(void, SECOC_CODE) SecOC_RxIndication
(
  PduIdType                                        id,
#if (STD_ON == SECOC_ASR403_API)
  P2VAR(  PduInfoType, AUTOMATIC, SECOC_APPL_DATA) info
#else /* #if (STD_ON == SECOC_ASR403_API) */
  P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) info
#endif /* #if (STD_ON == SECOC_ASR403_API) #else*/
);

/* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00112,1 */
/**
 * \brief Function to request authentication and transmission of an authentic I-PDU.
 *
 * \param[in]  id   ID of the Authentic I-PDU to be transmitted.
 * \param[in]  info A pointer to a structure with Authentic I-PDU related data that shall be
 *                  transmitted: data length and pointer to I-SDU.
 *
 * \returns whether the request was successful or not.
 * \retval E_OK     Request successful.
 * \retval E_NOT_OK Request failed.
 *
 */
extern FUNC(Std_ReturnType, SECOC_CODE) SecOC_Transmit
(
  PduIdType                                        id,
  P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) info
);

/* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00113,1 */
/**
 * \brief Function to request the cancellation of an authentication and transmission of an Authentic
 *        I-PDU. If the Csm is used to authenticate the I-PDU, then the cancellation may take
 *        several main function cycles because the authentication sequence cannot be canceled
 *        at the CSM.
 *
 * \param[in]  id   ID of the Authentic I-PDU to be transmitted.
 *
 * \returns the status of the cancellation request
 * \retval E_OK     Cancellation request was performed successfully by the SecOC module.
 * \retval E_NOT_OK Cancellation request was rejected.
 */
extern FUNC(Std_ReturnType, SECOC_CODE) SecOC_CancelTransmit
(
  PduIdType                                         id
);

#if (STD_ON == SECOC_TX_USETP)
/* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00129,1 */
/**
 * \brief This function is called to acquire the transmit data of an I-PDU segment (N-PDU) for a
 *        Secured I-PDU
 *
 * This function is called to acquire the transmit data of an I-PDU segment (N-PDU) for a Secured
 * I-PDU. Each call to this function provides the next part of the Secured I-PDU data unless
 * retry->TpDataState is TP_DATARETRY.
 * In this case the function restarts to copy the data beginning at the offset from the current
 * position indicated by retry->TxTpDataCnt.
 * The size of the remaining data is written to the position indicated by availableDataPtr.
 *
 * \param[in]  id               ID of the secured I-PDU to be transmitted.
 * \param[in]  info             A pointer to a structure with Secured I-PDU related data that shall
 *                              be transmitted: data length and pointer to I-SDU buffer
 * \param[in]  retry            This parameter is used to acknowledge transmitted data or to
 *                              retransmit data after transmission problems.
 *                              If the retry parameter is a NULL_PTR, it indicates that the transmit
 *                              data can be removed from the buffer immediately after it has been
 *                              copied.
 *                              Otherwise, the retry parameter shall point to a valid RetryInfoType
 *                              element.
 *                              If TpDataState indicates TP_CONFPENDING,
 *                              the previously copied data shall remain in the TP buffer to be
 *                              available for error recovery.
 *                              TP_DATACONF indicates that all data that has been copied before this
 *                              call is confirmed and can be removed from the TP buffer.
 *                              Data copied by this API call is excluded and will be confirmed
 *                              later.
 *                              TP_DATARETRY indicates that this API call shall copy previously
 *                              copied data in order to recover from an error.
 *                              In this case TxTpDataCnt specifies the offset in bytes from the
 *                              current data copy position.
 * \param[out] availableDataPtr Indicates the remaining number of bytes that are available in the
 *                              upper layer module's Tx buffer.
 *                              availableDataPtr can be used by TP modules that support dynamic
 *                              payload lengths (e.g. FrIsoTp) to determine the size of the
 *                              following CFs.
 *
 * \returns the status of the request
 * \retval BUFREQ_OK       Data has been copied to the transmit buffer completely as requested
 * \retval BUFREQ_E_BUSY   Request could not be fulfilled, because the required amount of Tx data is
 *                         not available.
 *                         The LoTp module can either retry the request with the same PduInfoPtr or
 *                         treat the return value like BUFREQ_E_NOT_OK.
 * \retval BUFREQ_E_NOT_OK Data has not been copied. Request failed.
 */
extern FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_CopyTxData
(
  PduIdType                                        id,
  P2VAR(PduInfoType,   AUTOMATIC, SECOC_APPL_DATA) info,
  P2VAR(RetryInfoType, AUTOMATIC, SECOC_APPL_DATA) retry,
  P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) availableDataPtr
);

/* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00152,1 */
/**
 * \brief Service to confirm transmission via TP.
 *
 * The lower layer transport protocol module confirms the transmission of a Secured I-PDU via PduR.
 *
 * \param[in] id     ID of the transmitted Secured I-PDU.
 * \param[in] result Result of transmission.
 *
 */
extern FUNC(void, SECOC_CODE) SecOC_TpTxConfirmation
(
  PduIdType      id,
  Std_ReturnType result
);
#endif /* (STD_ON == SECOC_TX_USETP) */

/* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00127,1 */
/**
 * \brief Service to copy the Secured I-PDU to the lower layer.
 *
 * \param[in]    TxPduId     ID of the SDU that is requested to be transmitted.
 * \param[in,out] PduInfoPtr  A pointer to a buffer (SduDataPtr) to where the SDU data shall be
 *                           copied and the available buffer size in SduLength.
 *
 * \returns the result of the data copy process
 * \retval E_OK      SDU has been copied and SduLength indicates the number of copied bytes.
 * \retval E_NOT_OK  No SDU data has been copied. PduInfoPtr must not be used since it may contain
 *                   a NULL pointer or point to invalid data.
 *
 */
extern FUNC(Std_ReturnType, SECOC_CODE) SecOC_TriggerTransmit
(
  PduIdType TxPduId,
  P2VAR(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) PduInfoPtr
);

/* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00126,1 */
/**
 * \brief Service to confirm transmission.
 *
 * The lower layer communication interface module confirms the transmission of a Secured I-PDU via
 * PduR.
 *
 * \param[in] id     ID of the transmitted Secured I-PDU.
 *
 */
extern FUNC(void, SECOC_CODE) SecOC_TxConfirmation
(
  PduIdType id
);

#if (STD_OFF == SECOC_INCLUDE_RTE)
#if (SECOC_USER_DEFINED_RX_MAINFUNCTIONS == STD_OFF)
#if (SECOC_NUMBER_RX_PDUS > 0)
/* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00171,1 */
/**
 * \brief This function performs the processing of the SecOC module's
 *        verification for the Rx path.
 */
#ifndef RTE_SCHM_SWCBSW_SECOC_MAINFUNCTIONRX
#define RTE_SCHM_SWCBSW_SECOC_MAINFUNCTIONRX
extern FUNC(void, SECOC_CODE) SecOC_MainFunctionRx
(
  void
);
#endif /* #ifdef RTE_SCHM_SWCBSW_SECOC_MAINFUNCTIONRX */
#endif /* #if (SECOC_NUMBER_RX_PDUS > 0) */
#endif /* #if (SECOC_USER_DEFINED_RX_MAINFUNCTIONS == STD_OFF) */

#if (SECOC_USER_DEFINED_TX_MAINFUNCTIONS == STD_OFF)
#if (SECOC_NUMBER_TX_PDUS > 0)
/* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00176,1 */
/**
 * \brief This function performs the processing of the SecOC module's authentication
 *        for the Tx path.
 */
#ifndef RTE_SCHM_SWCBSW_SECOC_MAINFUNCTIONTX
#define RTE_SCHM_SWCBSW_SECOC_MAINFUNCTIONTX
extern FUNC(void, SECOC_CODE) SecOC_MainFunctionTx
(
  void
);
#endif /* #ifdef RTE_SCHM_SWCBSW_SECOC_MAINFUNCTIONTX */
#endif /* #if (SECOC_NUMBER_TX_PDUS > 0) */
#endif /* #if (SECOC_USER_DEFINED_TX_MAINFUNCTIONS == STD_OFF) */
#endif /* #if (STD_OFF == SECOC_INCLUDE_RTE) */

#if (SECOC_BYPASS_AUTHENTICATION_ROUTINE == STD_ON)
/** \brief Notifies the SecOC module about the bypass mechanism status
 *
 * \param[in]  state  Provided bypass state
 *                     The following state types can be used:
 *                      FALSE - the bypass mechanism is turn off(also set at initialization)
 *                      TRUE - the bypass mechanism is turn on
 */
extern FUNC(void, SECOC_CODE) SecOC_BypassAuthRoutine
(
  boolean state
);
#endif /* #if (SECOC_BYPASS_AUTHENTICATION_ROUTINE == STD_ON) */

#if (STD_OFF == SECOC_INCLUDE_RTE)
#if (SECOC_USE_DEFAULT_AUTH_INFO_PATTERN == STD_ON)
/* !LINKSTO SecOC.ASR20-11.Tx.SWS_SecOC_91013,1 */
/**
 * \brief Notifies the SecOC module about the default authentication pattern usage
 *
 * \param[in]  freshnessValueId                          ID of the Freshness Value for which sending
 *                                                       SecOCDefaultAuthenticationInformationPattern should be enabled.
 * \param[in]  sendDefaultAuthenticationInformation      FALSE - sending SecOCDefaultAuthenticationInformationPattern
 *                                                               shall be disabled for the given FreshnessValueID
 *                                                       TRUE  - sending SecOCDefaultAuthenticationInformationPattern
 *                                                               shall be enabled for the given FreshnessValueID
 *
 */
extern FUNC(Std_ReturnType, SECOC_CODE) SecOC_SendDefaultAuthenticationInformation
(
  uint16 FreshnessValueID,
  boolean sendDefaultAuthenticationInformation
);
#endif /* #if (SECOC_USE_DEFAULT_AUTH_INFO_PATTERN == STD_ON) */
#endif /* #if (STD_OFF == SECOC_INCLUDE_RTE) */

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/*================================================================================================*/

#endif /* #ifndef SECOC_H */

/*==================[end of file]=================================================================*/

