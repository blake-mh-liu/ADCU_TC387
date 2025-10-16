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

#ifndef SECOC_TX_H
#define SECOC_TX_H

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

#include <SecOC_Tx_Int.h>

#if (STD_ON == SECOC_ENABLE_SEC_EVENT_REPORTING)
#include <IdsM.h>
#endif /* #if (STD_ON == SECOC_ENABLE_SEC_EVENT_REPORTING) */

#if (SECOC_NUMBER_TX_PDUS > 0)

/*==================[macros]======================================================================*/

/** \brief Macro which indicates the number of states that the Tx side state machine has
 */
#if (defined SECOC_NUMBER_OF_TXSTATES)
#error SECOC_NUMBER_OF_TXSTATES already defined
#endif
#if (SECOC_TX_CSM_ASYNC == STD_ON)
#define SECOC_NUMBER_OF_TXSTATES                                                        7U
#else
#define SECOC_NUMBER_OF_TXSTATES                                                        6U
#endif

/** \brief SecOC Tx state machine index for SecOC_TxIdle function
 */
#if (defined SECOC_TX_STATE_IDLE)
#error SECOC_TX_STATE_IDLE already defined
#endif
#define SECOC_TX_STATE_IDLE                                                            0U

/** \brief SecOC Tx state machine index for SecOC_Tx_GetFreshness function
 */
#if (defined SECOC_TX_STATE_GETFRESHNESS)
#error SECOC_TX_STATE_GETFRESHNESS already defined
#endif
#define SECOC_TX_STATE_GETFRESHNESS                                                    1U

/** \brief SecOC Tx state machine index for SecOC_TxAuthentication function
 */
#if (defined SECOC_TX_STATE_AUTHENTICATION)
#error SECOC_TX_STATE_AUTHENTICATION already defined
#endif
#define SECOC_TX_STATE_AUTHENTICATION                                                  2U

/** \brief SecOC Tx state machine index for SecOC_TxConstructSecuredPdu function
 */
#if (defined SECOC_TX_STATE_CONSTRUCTSECUREDPDU)
#error SECOC_TX_STATE_CONSTRUCTSECUREDPDU already defined
#endif
#define SECOC_TX_STATE_CONSTRUCTSECUREDPDU                                             3U

/** \brief SecOC Tx state machine index for SecOC_TxBroadcastSecuredPdu function
 */
#if (defined SECOC_TX_STATE_BROADCASTSECUREDPDU)
#error SECOC_TX_STATE_BROADCASTSECUREDPDU already defined
#endif
#define SECOC_TX_STATE_BROADCASTSECUREDPDU                                             4U

/** \brief SecOC Tx state machine index for SecOC_Tx_StateWaitForConfirmation function
 */
#if (defined SECOC_TX_STATE_WAITFORCONFIRMATION)
#error SECOC_TX_STATE_WAITFORCONFIRMATION already defined
#endif
#define SECOC_TX_STATE_WAITFORCONFIRMATION                                             5U

#if (SECOC_TX_CSM_ASYNC == STD_ON)
/** \brief SecOC Tx state machine index for SecOC_TxWaitForAuthenticationCallback function
 */
#if (defined SECOC_TX_STATE_WAITFORAUTHENTICATIONCALLBACK)
#error SECOC_TX_STATE_WAITFORAUTHENTICATIONCALLBACK already defined
#endif
#define SECOC_TX_STATE_WAITFORAUTHENTICATIONCALLBACK                                   6U
#endif /* #if (SECOC_TX_CSM_ASYNC == STD_ON) */

/** \brief SecOC Tx state machine event, which indicates, that no event occurred
 */
#if (defined SECOC_TXEVENT_NONE)
#error SECOC_TXEVENT_NONE already defined
#endif
#define SECOC_TXEVENT_NONE                                                             0U

/** \brief SecOC Tx state machine event, which is emitted, when SecOC_Transmit is called.
 */
#if (defined SECOC_TXEVENT_TRANSMIT)
#error SECOC_TXEVENT_TRANSMIT already defined
#endif
#define SECOC_TXEVENT_TRANSMIT                                                         1U

/** \brief SecOC Tx state machine event, which is emitted, when reauthntication has to be performed.
 */
#if (defined SECOC_TXEVENT_REAUTHENTICATE)
#error SECOC_TXEVENT_REAUTHENTICATE already defined
#endif
#define SECOC_TXEVENT_REAUTHENTICATE                                                   2U

/** \brief SecOC Tx state machine event, which is emitted on a TxConfirmation
 */
#if (defined SECOC_TXEVENT_TXCONFIRMATION_OK)
#error SECOC_TXEVENT_TXCONFIRMATION_OK already defined
#endif
#define SECOC_TXEVENT_TXCONFIRMATION_OK                                                3U

/** \brief SecOC Tx state machine event, which is emitted on a TxConfirmation
 */
#if (defined SECOC_TXEVENT_TXCONFIRMATION_NOT_OK)
#error SECOC_TXEVENT_TXCONFIRMATION_NOT_OK already defined
#endif
#define SECOC_TXEVENT_TXCONFIRMATION_NOT_OK                                            4U

/** \brief SecOC Tx state machine event, which cancels a transmission
 */
#if (defined SECOC_TXEVENT_CANCEL)
#error SECOC_TXEVENT_CANCEL already defined
#endif
#define SECOC_TXEVENT_CANCEL                                                           5U

#if (SECOC_TX_CSM_ASYNC == STD_ON)
/** \brief SecOC Tx state machine event, which is emitted by a Csm Callback with the MAC
 *         authentication result, which is E_OK
 */
#if (defined SECOC_TXEVENT_AUTHCALLBACK_OK)
#error SECOC_TXEVENT_AUTHCALLBACK_OK already defined
#endif
#define SECOC_TXEVENT_AUTHCALLBACK_OK                                                  6U

/** \brief SecOC Tx state machine event, which is emitted by a Csm Callback with the MAC
 *         authentication result, which is not E_OK
 */
#if (defined SECOC_TXEVENT_AUTHCALLBACK_NOT_OK)
#error SECOC_TXEVENT_AUTHCALLBACK_NOT_OK already defined
#endif
#define SECOC_TXEVENT_AUTHCALLBACK_NOT_OK                                              7U

#endif /* #if (SECOC_TX_CSM_ASYNC == STD_ON) */

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

/**
 * \brief This functions performs the initialization for the Tx side of SecOC.
 */
extern FUNC(void, SECOC_CODE) SecOC_Tx_Init
(
  void
);

/**
 * \brief This functions performs the deinitialization for the Tx side of SecOC.
 */
extern FUNC(void, SECOC_CODE) SecOC_Tx_DeInit
(
  void
);

/* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00022,1 */
/**
 * \brief This function performs the processing of the SecOC module's
 *        authentication for the Tx path Pdu processing. In case of synchronous
 *        Pdu processing it is called directly by the PduR calls of SecOC
 *        interface or, in case of asynchronous Pdu processing, by
 *        SecOC_MainFunctionTx respectively.
 *
 * \param[in]  pduIdx  the index of the processed Pdu
 */
extern FUNC(void, SECOC_CODE) SecOC_Tx_ProcessPduStates
(
  uint16 pduIdx
);

#if (SECOC_TX_CSM_ASYNC == STD_ON)
/** \brief The generic callback function used to search and set the result of the Csm job
 *         for the coresponding Tx PDU, for which the verification was performed
 *
 * \param[in] job       Holds a pointer to the job, which has finished.
 * \param[in] startIdx  The start index in the callback to PDU ctx lookup table.
 * \param[in] endIdx    The end index in the callback to PDU ctx lookup table.
 * \param[in] result    Contains the result of the cryptographic operation.
 *
 */
extern FUNC(void, SECOC_CODE) SecOC_Tx_CsmCallbackNotification
(
  P2CONST(Crypto_JobType, AUTOMATIC, SECOC_APPL_DATA) job,
          uint16                                      startIdx,
          uint16                                      endIdx,
          Std_ReturnType                              result
);
#endif /* #if (SECOC_TX_CSM_ASYNC == STD_ON) */

#if (SECOC_USER_DEFINED_TX_MAINFUNCTIONS == STD_ON)
/** \brief  MainFunction execution for a list of TX PDUs
 **
 ** This function is to be called from cyclically called MainFunction to process the requested PDUs.
 ** The SecOC_MainFunctionTx shall process the PDU.
 **
 ** \param[in]  txInstIdxList a list consisting of the index of the processed PDUs
 ** \param[in]  numberOfTxInstances the number of TX instances in the list
 **/
extern FUNC(void, SECOC_CODE) SecOC_MainFunctionTx
(
  P2CONST(uint16, AUTOMATIC, SECOC_APPL_CONST) txInstIdxList,
          uint16                               numberOfTxInstances
);
#endif /* #ifdef (SECOC_USER_DEFINED_TX_MAINFUNCTIONS == STD_ON) */

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/*================================================================================================*/

#endif /* #if (SECOC_NUMBER_TX_PDUS > 0) */
#endif /* #ifndef SECOC_TX_H */

/*==================[end of file]=================================================================*/

