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

#ifndef SECOC_RX_H
#define SECOC_RX_H

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

#include <SecOC_Rx_Int.h>

#if (STD_ON == SECOC_ENABLE_SEC_EVENT_REPORTING)
#include <IdsM.h>
#endif /* #if (STD_ON == SECOC_ENABLE_SEC_EVENT_REPORTING) */

#if (SECOC_NUMBER_RX_PDUS > 0)

/*==================[macros]======================================================================*/

/** \brief Macro which indicates the number of states that the Rx side state machine has
 */
#if (defined SECOC_NUMBER_OF_RXSTATES)
#error SECOC_NUMBER_OF_RXSTATES already defined
#endif /* #if (defined SECOC_NUMBER_OF_RXSTATES) */
#if (SECOC_RX_CSM_ASYNC == STD_ON)
#define SECOC_NUMBER_OF_RXSTATES                                                         7U
#else /* #if (SECOC_RX_CSM_ASYNC == STD_ON) */
#define SECOC_NUMBER_OF_RXSTATES                                                         6U
#endif /* #if (SECOC_RX_CSM_ASYNC == STD_ON) #else */

/** \brief SecOC Rx state machine index for SecOC_RxIdle function
 */
#if (defined SECOC_RX_STATE_IDLE)
#error SECOC_RX_STATE_IDLE already defined
#endif /* #if (defined SECOC_RX_STATE_IDLE) */
#define SECOC_RX_STATE_IDLE                                                              0U

/** \brief SecOC Rx state machine index for SecOC_RxConstructDataToAuthenticator function
 */
#if (defined SECOC_RX_STATE_CONSTRUCTDATATOAUTHENTICATOR)
#error SECOC_RX_STATE_CONSTRUCTDATATOAUTHENTICATOR already defined
#endif /* #if (defined SECOC_RX_STATE_CONSTRUCTDATATOAUTHENTICATOR) */
#define SECOC_RX_STATE_CONSTRUCTDATATOAUTHENTICATOR                                      1U

/** \brief SecOC Rx state machine index for SecOC_RxVerification function
 */
#if (defined SECOC_RX_STATE_VERIFICATION)
#error SECOC_RX_STATE_VERIFICATION already defined
#endif /* #if (defined SECOC_RX_STATE_VERIFICATION) */
#define SECOC_RX_STATE_VERIFICATION                                                      2U

/** \brief SecOC Rx state machine index for SecOC_Rx_StateCheckVerificationResult function
 */
#if (defined SECOC_RX_STATE_CHECKVERIFICATIONRESULT)
#error SECOC_RX_STATE_CHECKVERIFICATIONRESULT already defined
#endif /* #if (defined SECOC_RX_STATE_CHECKVERIFICATIONRESULT) */
#define SECOC_RX_STATE_CHECKVERIFICATIONRESULT                                           3U

/** \brief SecOC Rx state machine index for SecOC_Rx_StateBroadcastPdu function
 */
#if (defined SECOC_RX_STATE_BROADCASTPDU)
#error SECOC_RX_STATE_BROADCASTPDU already defined
#endif /* #if (defined SECOC_RX_STATE_BROADCASTPDU) */
#define SECOC_RX_STATE_BROADCASTPDU                                                      4U

/** \brief SecOC Rx state machine index for SecOC_Rx_StateRetryToObtainFreshness function
 */
#if (defined SECOC_RX_STATE_RETRYTOOBTAINFRESHNESS)
#error SECOC_RX_STATE_RETRYTOOBTAINFRESHNESS already defined
#endif /* #if (defined SECOC_RX_STATE_RETRYTOOBTAINFRESHNESS) */
#define SECOC_RX_STATE_RETRYTOOBTAINFRESHNESS                                            5U

#if (SECOC_RX_CSM_ASYNC == STD_ON)
/** \brief SecOC Rx state machine index for SecOC_RxWaitForVerificationCallback function
 */
#if (defined SECOC_RX_STATE_WAITFORVERIFICATIONCALLBACK)
#error SECOC_RX_STATE_WAITFORVERIFICATIONCALLBACK already defined
#endif /* #if (defined SECOC_RX_STATE_WAITFORVERIFICATIONCALLBACK) */
#define SECOC_RX_STATE_WAITFORVERIFICATIONCALLBACK                                       6U
#endif /* #if (SECOC_RX_CSM_ASYNC == STD_ON) */

/** \brief SecOC Rx state machine event, which indicates, that no event occurred
 */
#if (defined SECOC_RXEVENT_NONE)
#error SECOC_RXEVENT_NONE already defined
#endif /* #if (defined SECOC_RXEVENT_NONE) */
#define SECOC_RXEVENT_NONE                                                               0U

/** \brief SecOC Rx state machine event, which occurs on an RX indication
 */
#if (defined SECOC_RXEVENT_RXINDICATION)
#error SECOC_RXEVENT_RXINDICATION already defined
#endif /* #if (defined SECOC_RXEVENT_RXINDICATION) */
#define SECOC_RXEVENT_RXINDICATION                                                       1U

/** \brief SecOC Rx state machine event, which occurs on a StartOfReception
 */
#if (defined SECOC_RXEVENT_STARTRECEPTION)
#error SECOC_RXEVENT_STARTRECEPTION already defined
#endif /* #if (defined SECOC_RXEVENT_STARTRECEPTION) */
#define SECOC_RXEVENT_STARTRECEPTION                                                     2U

#if (SECOC_RX_CSM_ASYNC == STD_ON)
/** \brief SecOC Rx state machine event, which is emitted by a Csm Callback with the MAC
 *         verification result, which is E_OK
 */
#if (defined SECOC_RXEVENT_VERCALLBACK_OK)
#error SECOC_RXEVENT_VERCALLBACK_OK already defined
#endif /* #if (defined SECOC_RXEVENT_VERCALLBACK_OK) */
#define SECOC_RXEVENT_VERCALLBACK_OK                                                     3U

/** \brief SecOC Rx state machine event, which is emitted by a Csm Callback with the MAC
 *         verification result, which is not E_OK
 */
#if (defined SECOC_RXEVENT_VERCALLBACK_NOT_OK)
#error SECOC_RXEVENT_VERCALLBACK_NOT_OK already defined
#endif /* #if (defined SECOC_RXEVENT_VERCALLBACK_NOT_OK) */
#define SECOC_RXEVENT_VERCALLBACK_NOT_OK                                                 4U
#endif /* #if (SECOC_RX_CSM_ASYNC == STD_ON) */

#if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON)

/** \brief Macro, which is used to check if the received secured PDU buffer
 *          of a given PDU instance is full or not.
 */
#if (defined SECOC_IS_RX_RECEIVED_SECURED_PDU_BUFFER_FULL)
#error SECOC_IS_RX_RECEIVED_SECURED_PDU_BUFFER_FULL already defined
#endif /* #if (defined SECOC_IS_RX_RECEIVED_SECURED_PDU_BUFFER_FULL) */
#define SECOC_IS_RX_RECEIVED_SECURED_PDU_BUFFER_FULL(pduIdx)  (SecOC_RxData[pduIdx].Queue.Count == SecOC_RxData[pduIdx].Queue.QueueSize)

/** \brief Macro, which is used to check if the received secured PDU buffer
 *          of a given PDU instance is emptry or not.
 */
#if (defined SECOC_IS_RX_RECEIVED_SECURED_PDU_BUFFER_EMPTY)
#error SECOC_IS_RX_RECEIVED_SECURED_PDU_BUFFER_EMPTY already defined
#endif /* #if (defined SECOC_IS_RX_RECEIVED_SECURED_PDU_BUFFER_EMPTY) */
#define SECOC_IS_RX_RECEIVED_SECURED_PDU_BUFFER_EMPTY(pduIdx) (SecOC_RxData[pduIdx].Queue.Count == 0U)

#endif /* #if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON) */

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

/**
 * \brief This functions performs the initialization for the Rx side of SecOC.
 */
extern FUNC(void, SECOC_CODE) SecOC_Rx_Init
(
  void
);

/**
 * \brief This functions performs the deinitialization for the Rx side of SecOC.
 */
extern FUNC(void, SECOC_CODE) SecOC_Rx_DeInit
(
  void
);

/* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00016,1 */
/**
 * \brief This function performs the processing of the SecOC module's
 *        authentication and verification for the Rx path Pdu processing. In
 *        case of synchronous Pdu processing it is called directly by the PduR
 *        calls of SecOC interface or, in case of asynchronous Pdu processing,
 *        by SecOC_MainFunctionRx respectively.
 *
 * \param[in]  pduIdx  the index of the processed Pdu
 */
extern FUNC(void, SECOC_CODE) SecOC_Rx_ProcessPduStates
(
  uint16 pduIdx
);

#if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON)

/** \brief Function used to initialize the relevant data related to queue mechanism
  * \param[in] instId     Contains the instance ID
 */
extern FUNC(void, SECOC_CODE) SecOC_Rx_InitQueue
(
        uint16                                instId
);

/** \brief Function used to read the secured PDU from the reception queue
  * \param[in] instId     Contains the instance ID
  * \param[in] dataPtr    Pointer to the location where the secured PDU will be copied from the queue
  * \param[out] dataLen   Stored number of bytes in the received secured PDU buffer
  *
  * \returns whether the request was successful or not.
  * \retval E_OK     Request successful.
  * \retval E_NOT_OK Request failed.
 */
extern FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_ReadPduFromQueue
(
        uint16                                       instId,
  P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA)           dataPtr,
  P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA)   dataLenPtr
);

/** \brief Function used to write the secured PDU to the reception queue
  * \param[in] instId     Contains the instance ID
  * \param[in] dataPtr    Pointer to the location from where the secured PDU will be copied to the queue
  * \param[in] dataLen    Number of bytes to write to the received secured PDU buffer
  * \param[in] expectedTotalDataLen The total number of expected bytes for the incoming PDU instance
  *
  * \returns whether the request was successful or not.
  * \retval BUFREQ_OK     Request successful.
  * \retval BUFREQ_E_OVFL Request failed, there is not enough space in the buffer to store the incoming PDU instance
 */
extern FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_Rx_WritePduToQueue
(
        uint16                                instId,
  P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA)    dataPtr,
        PduLengthType                         dataLen,
        PduLengthType                         expectedTotalDataLen
);

/** \brief Function used to get the available length in the received secured PDU buffer
  * \param[in] instId     Contains the instance ID
 */
extern FUNC(PduLengthType, SECOC_CODE) SecOC_Rx_GetQueueCapacity
(
  uint16 instId
);

/** \brief Function used to drop the current or the last received PDU in the received secured PDU buffer
  * \param[in] instId     Contains the instance ID
 */
extern FUNC(void, SECOC_CODE) SecOC_Rx_DropPduFromQueue
(
  uint16 instId
);

#endif /* #if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON) */

#if (SECOC_RX_CSM_ASYNC == STD_ON)
/** \brief The generic callback function used to search and set the result of the Csm job
 *         for the coresponding Rx PDU, for which the verification was performed
 *
 * \param[in] job       Holds a pointer to the job, which has finished.
 * \param[in] startIdx  The start index in the callback to PDU ctx lookup table.
 * \param[in] endIdx    The end index in the callback to PDU ctx lookup table.
 * \param[in] result    Contains the result of the cryptographic operation.
 *
 */
extern FUNC(void, SECOC_CODE) SecOC_Rx_CsmCallbackNotification
(
  P2CONST(Crypto_JobType, AUTOMATIC, SECOC_APPL_DATA) job,
          uint16                                      startIdx,
          uint16                                      endIdx,
          Std_ReturnType                              result
);
#endif /* #if (SECOC_RX_CSM_ASYNC == STD_ON) */

#if (SECOC_USER_DEFINED_RX_MAINFUNCTIONS == STD_ON)
/** \brief  MainFunction execution for a list of RX PDUs
 **
 ** This function is to be called from cyclically called MainFunction to process the requested PDUs.
 ** The SecOC_MainFunctionRx shall process the PDU.
 **
 ** \param[in]  rxInstIdxList a list consisting of the index of the processed PDUs
 ** \param[in]  numberOfRxInstances the number of RX instances in the list
 **/
extern FUNC(void, SECOC_CODE) SecOC_MainFunctionRx
(
  P2CONST(uint16, AUTOMATIC, SECOC_APPL_CONST) rxInstIdxList,
          uint16                               numberOfRxInstances
);
#endif /* #ifdef (SECOC_USER_DEFINED_RX_MAINFUNCTIONS == STD_ON) */

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/*================================================================================================*/

#endif /* #if (SECOC_NUMBER_RX_PDUS > 0) */
#endif /* #ifndef SECOC_RX_H */

/*==================[end of file]=================================================================*/

