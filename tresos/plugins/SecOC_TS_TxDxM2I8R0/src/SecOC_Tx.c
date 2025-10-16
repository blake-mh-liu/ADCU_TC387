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

/*==================[deviations]==================================================================*/

/*  Misra-C:2012 Deviations:
 *
 * MISRAC2012-1) Deviated Rule: 8.9 (Advisory)
 * An object should be defined at block scope if its identifier only appears in a single function.
 *
 * Reason:
 * The AUTOSAR memory mapping requires that functions are mapped to SEC_CODE memory sections.
 * Objects at block scope require a different mapping, e.g. to a SEC_CONST section,
 * which leads to nested memory sections, which is not supported by some compilers.
 *
 * MISRAC2012-2) Deviated Rule: 2.1 (required)
 * A project shall not contain unreachable code.
 *
 * Reason:
 * Function like macro leads to unreachable code compiler.
 */

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * This is a bug in the tasking compiler and should be fixed with v6.1r1.
 */

/*==================[includes]====================================================================*/

#include <SecOC_Tx.h>

#if (STD_ON == SECOC_INCLUDE_RTE)
#if (SECOC_NR_PARTITIONS == 0U)
#include <Rte_SecOC.h>
#endif
#endif /* #if (STD_ON == SECOC_INCLUDE_RTE) */

#if (SECOC_NUMBER_TX_PDUS > 0)

/*==================[macros]======================================================================*/

/** \brief Macro to calculate the sum of the Tx authentication information length that is comprised
 *         of the truncated authenticator value and the truncated freshness value
 */
#if (defined SECOC_TX_AUTHENTICATION_INFO_LEN)
#error SECOC_TX_AUTHENTICATION_INFO_LEN already defined
#endif /* #if (defined SECOC_TX_AUTHENTICATION_INFO_LEN) */
#define SECOC_TX_AUTHENTICATION_INFO_LEN(Id) ((uint32)(SECOC_GET_TX_AUTHINFOTX_LEN((Id))) + \
                                              (uint32)(SECOC_GET_TX_FRESHNESSTX_LEN((Id))))

/*==================[type definitions]============================================================*/

/*==================[internal function declarations]==============================================*/

#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

/** \brief Idle state of the SecOC Tx state machine
 * \param[in] instId ID of the state machine instance (i.e. TX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Tx_StateIdle
(
  uint16 instId
);

/** \brief State of the SecOC Tx state machine, which gets the freshness value
 * \param[in] instId ID of the state machine instance (i.e. TX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Tx_StateGetFreshness
(
  uint16 instId
);

/** \brief State of the SecOC Tx state machine, which starts an authentication
 * \param[in] instId ID of the state machine instance (i.e. TX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Tx_StateAuthentication
(
  uint16 instId
);

#if (SECOC_TX_CSM_ASYNC == STD_ON)
/** \brief State of the SecOC Tx state machine, which waits
 *         for the callback and evaluates the result
 * \param[in] instId ID of the state machine instance (i.e. TX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Tx_StateWaitForAuthenticationCallback
(
  uint16 instId
);
#endif /* #if (SECOC_TX_CSM_ASYNC == STD_ON) */

/** \brief State of the SecOC Tx state machine, which constructs the secured Pdu
 * \param[in] instId ID of the state machine instance (i.e. TX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Tx_StateConstructPdu
(
  uint16 instId
);

/** \brief State of the SecOC Tx state machine, which transmits the secured Pdu
 * \param[in] instId ID of the state machine instance (i.e. TX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Tx_StateBroadcastPdu
(
  uint16 instId
);

/** \brief State of the SecOC Tx state machine, where CanTp/PduR can copy the secured Pdu
 * \param[in] instId ID of the state machine instance (i.e. TX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Tx_StateWaitForConfirmation
(
  uint16 instId
);

/** \brief Function used to reset the state machine
 * \param[in] instId ID of the state machine instance (i.e. TX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Tx_ResetSm
(
  uint16 instId
);

/** \brief Function used to handle the authentication retry
 * \param[in] instId ID of the state machine instance (i.e. TX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Tx_CheckForCsmRetry
(
  uint16 instId
);

/** \brief Function used to copy the freshness value to the secured Pdu
 * \param[in] instId ID of the state machine instance (i.e. TX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Tx_CopyFreshnessToSecuredPdu
(
  uint16 instId
);

/** \brief Function used to copy the MAC to the secured Pdu
 * \param[in] instId ID of the state machine instance (i.e. TX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Tx_CopyMacToSecuredPdu
(
  uint16 instId
);

#if (SECOC_TX_SHAPE_SEC_PDU == STD_ON)
/** \brief Function used to update the secured Pdu layout to a fix one
 * \param[in] instId ID of the state machine instance (i.e. TX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Tx_UpdateLayoutSecuredPdu
(
  uint16 instId
);
#endif /* #if (SECOC_TX_SHAPE_SEC_PDU == STD_ON) */

#if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON)
/** \brief Function used to broadcast the cryptographic PDU to the lower layer
 * \param[in] instId ID of the state machine instance (i.e. TX PDU)
 */
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Tx_BroadcastCryptoPdu
(
  uint16 instId
);

/** \brief Function used to broadcast the authentic PDU to the lower layer
 * \param[in] instId ID of the state machine instance (i.e. TX PDU)
 */
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Tx_BroadcastAuthenticPdu
(
  uint16 instId
);

#if (SECOC_TX_USE_MESS_LINKER == STD_ON)
/** \brief Function used to copy the message link to the cryptographic Pdu
 * \param[in] instId ID of the state machine instance (i.e. TX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Tx_CopyMessageLinkToCryptoPdu
(
  uint16 instId
);
#endif /* #if (SECOC_TX_USE_MESS_LINKER == STD_ON) */
#endif /* #if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON) */

#if (SECOC_TX_USE_SEC_PDU_HEADER == STD_ON)
/** \brief Function used to copy the secured header to the authentic PDU
 * \param[in] instId ID of the state machine instance (i.e. TX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Tx_CopySecuredHeaderToPdu
(
  uint16 instId
);
#endif /* #if (SECOC_TX_USE_SEC_PDU_HEADER == STD_ON) */

#if (STD_ON == SECOC_MACGENERATE_STATUS_PROP_ENABLED)
/** \brief Function which propagates the MAC Generate status to the configured callout
 *         functions
 * \param[in] instId ID of the state machine instance (i.e. TX PDU)
 *
 */
static FUNC(void, SECOC_CODE) SecOC_Tx_PropagateMacGenerateStatus
(
  uint16  instId
);
#endif /* #if (STD_ON == SECOC_MACGENERATE_STATUS_PROP_ENABLED) */

/** \brief Function to shift all bits of an array left
 *
 * The function shifts all bits of an array left and fills
 * the LSB with zeros (arithmetic shift left)
 *
 * \param[in,out] array       pointer to the data which needs to be shifted
 * \param[in]     bitLength   length in bits starting from the LSB of the array
 * \param[in]     shift       number with which the shift will be done (must be smaller than 8)
 *
 */
static FUNC(void, SECOC_CODE) SecOC_Tx_ShiftLeft
(
  P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) array,
        uint32                             bitLength,
        uint8                              shift
);

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/*==================[internal constants]==========================================================*/

#define SECOC_START_SEC_CONST_UNSPECIFIED
#include <SecOC_MemMap.h>

/**
 * \brief Variable which holds the states of the SecOC Tx state machine
 */
/* Deviation MISRAC2012-1 */
static CONST(SecOC_SmStateType, SECOC_CONST) SecOC_Tx_StateMachine[SECOC_NUMBER_OF_TXSTATES] =
{
  &SecOC_Tx_StateIdle,
  &SecOC_Tx_StateGetFreshness,
  &SecOC_Tx_StateAuthentication,
  &SecOC_Tx_StateConstructPdu,
  &SecOC_Tx_StateBroadcastPdu,
  &SecOC_Tx_StateWaitForConfirmation,
#if (SECOC_TX_CSM_ASYNC == STD_ON)
  &SecOC_Tx_StateWaitForAuthenticationCallback
#endif /* #if (SECOC_TX_CSM_ASYNC == STD_ON) */
};

#define SECOC_STOP_SEC_CONST_UNSPECIFIED
#include <SecOC_MemMap.h>

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

FUNC(void, SECOC_CODE) SecOC_Tx_Init
(
  void
)
{
  uint16 pduIdx;

#if (SECOC_BYPASS_AUTHENTICATION_ROUTINE == STD_ON)
  SecOC_TxBypassAuthRoutineState = FALSE;
#endif /* #if (SECOC_BYPASS_AUTHENTICATION_ROUTINE == STD_ON) */

  /* Deviation TASKING-1 */
  for (pduIdx = 0U; pduIdx < SECOC_NUMBER_TX_PDUS; pduIdx++)
  {
    /* Reset the state machine */
    SecOC_TxData[pduIdx].State = SECOC_TX_STATE_IDLE;

    /* Clear the events */

    /* Clear the events which are indicating functions calls like SecOC_CancelTransmit */
    SecOC_TxData[pduIdx].PduREvent     = SECOC_TXEVENT_NONE;
#if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON)
    /* Clear the events which are indicating functions calls like SecOC_TxConfirmation */
    SecOC_TxData[pduIdx].PduRConfirmationForAuth = SECOC_TXEVENT_NONE;
    SecOC_TxData[pduIdx].PduRConfirmationForCrypto = SECOC_TXEVENT_NONE;
#endif /* #if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON) */
    /* Clear the events which are indicating functions calls like SecOC_Transmit */
    SecOC_TxData[pduIdx].TransmitEvent = SECOC_TXEVENT_NONE;
#if (SECOC_TX_CSM_ASYNC == STD_ON)
    /* Clear the events which are indicating functions calls like SecOC_CsmCallbackNotification */
    SecOC_TxData[pduIdx].CsmEvent = SECOC_TXEVENT_NONE;
#endif /* #if (SECOC_TX_CSM_ASYNC == STD_ON) */
#if (STD_ON == SECOC_TX_USE_SAME_BUFFER)
    /* CHECK: NOPARSE
     * Function like macro leads to unreachable code compiler (Wind River Diab) warning
     */
    /* Clear the buffer busy flags */
    /* Deviation MISRAC2012-2 */
    SECOC_TX_SET_BUFFER_LVL1_STATUS(pduIdx, SECOC_BUFFER_FREE);
    /* Deviation MISRAC2012-2 */
    SECOC_TX_SET_BUFFER_LVL2_STATUS(pduIdx, SECOC_BUFFER_FREE);
    /* CHECK: PARSE */
#endif /* #if (STD_ON == SECOC_TX_USE_SAME_BUFFER) */
#if (SECOC_USE_DEFAULT_AUTH_INFO_PATTERN == STD_ON)
    /* Clear the flag used for using the default authentication information pattern state */
    SecOC_TxData[pduIdx].DefaultAuthInfoPatternState = SECOC_DEFAULT_AUTH_INFO_PATTERN_STATE_DISABLED;
#endif /* #if (SECOC_USE_DEFAULT_AUTH_INFO_PATTERN == STD_ON) */

    /* Clear the flag used for continuous processing */
    SecOC_TxData[pduIdx].ProcessingAuthentication = FALSE;

    /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00226,1 */
    /* Clear the counters used for authentication build retries */
    SecOC_TxData[pduIdx].AuthAttempts = 0U;
#if (STD_ON == SECOC_MACGENERATE_STATUS_PROP_ENABLED)
    /* Clear the MAC generate result */
    SecOC_TxData[pduIdx].MacGenerateResult = E_NOT_OK;
#endif /* #if (STD_ON == SECOC_MACGENERATE_STATUS_PROP_ENABLED) */
#if (SECOC_USE_TX_CONFIRMATION_TIMEOUT == STD_ON)
    /* Clear the timeout counter used for skipping the call of SecOC_TpTxConfirmation */
    SecOC_TxData[pduIdx].ConfirmationTimeoutCounter = 0U;
#endif /* #if (SECOC_USE_TX_CONFIRMATION_TIMEOUT == STD_ON) */

    /* Set pointers to buffers, used for storing the PDUs and for internal processing */
    SecOC_TxData[pduIdx].ReceivedAuthPdu.SduDataPtr = SECOC_GET_TX_ULAUTH_PDU_ADR(pduIdx);
    SecOC_TxData[pduIdx].SecuredPdu.SduDataPtr = SECOC_GET_TX_SECURED_PDU_ADR(pduIdx);
#if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON)
    SecOC_TxData[pduIdx].SentAuthPdu.SduDataPtr = SECOC_GET_TX_SECURED_PDU_ADR(pduIdx);
#endif /* #if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON) */
    SecOC_TxData[pduIdx].Authenticator = SECOC_GET_TX_AUTHENTICATOR_ADR(pduIdx);
    SecOC_TxData[pduIdx].DataToAuthenticator = SECOC_GET_TX_DATATOAUTH_ADR(pduIdx);

    /* Clear the dynamic length of the received data */
    SecOC_TxData[pduIdx].DataLength = 0U;
    SecOC_TxData[pduIdx].ReceivedAuthPdu.SduLength = 0U;
    SecOC_TxData[pduIdx].SecuredPdu.SduLength = 0U;
#if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON)
    SecOC_TxData[pduIdx].SentAuthPdu.SduLength = 0U;
    SecOC_TxData[pduIdx].CryptoPdu.SduLength = 0U;
#endif /* #if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON) */
    SecOC_TxData[pduIdx].CopiedDataFromSecLength = 0U;
#if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON)
    SecOC_TxData[pduIdx].CopiedDataFromAuthLength = 0U;
    SecOC_TxData[pduIdx].CopiedDataFromCryptoLength = 0U;
#endif /* #if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON) */

#if (SECOC_USE_CSMJOBREF_CALLOUT == STD_ON)
    /* !LINKSTO  SecOC.EB.Tx.SWS_SecOC_00032,1, SecOC.EB.Tx.SWS_SecOC_00033,1 */
    /* Get the new Csm job ID based on the configured one */
    SecOC_TxData[pduIdx].CsmJobIdPostDefined =
      SECOC_CSMJOBREF_CALLOUT(SecOC_TxConfig[pduIdx].CsmJobId);
#endif /* #if (SECOC_USE_CSMJOBREF_CALLOUT == STD_ON) */
  }
}

FUNC(void, SECOC_CODE) SecOC_Tx_DeInit
(
  void
)
{
  uint16 pduIdx;

  /* Deviation TASKING-1 */
  for (pduIdx = 0U; pduIdx < SECOC_NUMBER_TX_PDUS; pduIdx++)
  {
    /* Release pointers to buffers, used for storing the PDUs and for internal processing */
    SecOC_TxData[pduIdx].ReceivedAuthPdu.SduDataPtr = NULL_PTR;
    SecOC_TxData[pduIdx].SecuredPdu.SduDataPtr = NULL_PTR;
#if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON)
    SecOC_TxData[pduIdx].SentAuthPdu.SduDataPtr = NULL_PTR;
    SecOC_TxData[pduIdx].CryptoPdu.SduDataPtr = NULL_PTR;
#endif /* #if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON) */
    SecOC_TxData[pduIdx].Authenticator = NULL_PTR;
    SecOC_TxData[pduIdx].DataToAuthenticator = NULL_PTR;

    /* Clear the dynamic length of the received data */
    SecOC_TxData[pduIdx].DataLength = 0U;
    SecOC_TxData[pduIdx].ReceivedAuthPdu.SduLength = 0U;
    SecOC_TxData[pduIdx].SecuredPdu.SduLength = 0U;
#if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON)
    SecOC_TxData[pduIdx].SentAuthPdu.SduLength = 0U;
    SecOC_TxData[pduIdx].CryptoPdu.SduLength = 0U;
#endif /* #if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON) */
    SecOC_TxData[pduIdx].CopiedDataFromSecLength = 0U;
#if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON)
    SecOC_TxData[pduIdx].CopiedDataFromAuthLength = 0U;
    SecOC_TxData[pduIdx].CopiedDataFromCryptoLength = 0U;
#endif /* #if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON) */
  }
}

FUNC(void, SECOC_CODE) SecOC_Tx_ProcessPduStates
(
  uint16 pduIdx
)
{
  /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00026,1 */
  do
  {
    SecOC_TxData[pduIdx].ProcessingAuthentication = FALSE;
    SecOC_Tx_StateMachine[SecOC_TxData[pduIdx].State](pduIdx);
  }
  while (TRUE == SecOC_TxData[pduIdx].ProcessingAuthentication);
}

#if (SECOC_USER_DEFINED_TX_MAINFUNCTIONS == STD_ON)
#if (SECOC_NUMBER_TX_PDUS > 0)
/* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00176,1 */
FUNC(void, SECOC_CODE) SecOC_MainFunctionTx
(
  P2CONST(uint16, AUTOMATIC, SECOC_APPL_CONST) txInstIdxList,
          uint16                               numberOfTxInstances
)
{
  /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00177,1 */
  if (SECOC_INIT == SecOC_InitStatus)
  {
    uint16 instIdx;
    uint16 i;

    /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00179,1 */
    for (i = 0U; numberOfTxInstances > i; i++)
    {
      instIdx = txInstIdxList[i];
/* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00024,1 */
#if (SECOC_TX_SYNC_PDU_PROCESSING == STD_ON)
      /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00023,2 */
      if (
          (SecOC_TxConfig[instIdx].UseSyncProcessing == FALSE                             ) ||
          (SecOC_TxData[instIdx].State               == SECOC_TX_STATE_WAITFORCONFIRMATION)
         )
#endif /* #if (SECOC_TX_SYNC_PDU_PROCESSING == STD_ON) */
      {
        /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00001,1 */
        SecOC_Tx_ProcessPduStates(instIdx);
      }
    }
  }
}
#endif /* #if (SECOC_NUMBER_TX_PDUS > 0) */
#endif /* #if (SECOC_USER_DEFINED_TX_MAINFUNCTIONS == STD_ON) */

#if (SECOC_TX_CSM_ASYNC == STD_ON)
FUNC(void, SECOC_CODE) SecOC_Tx_CsmCallbackNotification
(
  P2CONST(Crypto_JobType, AUTOMATIC, SECOC_APPL_DATA) job,
          uint16                                      startIdx,
          uint16                                      endIdx,
          Std_ReturnType                              result
)
{
  uint16         pduIdx;

  if (
      (SECOC_INIT == SecOC_InitStatus) &&
      (NULL_PTR   != job             )
     )
  {
    /* Check if the Csm callback is for the authentication service */
    for (pduIdx = startIdx; pduIdx < endIdx; pduIdx++)
    {
      if ((SECOC_TX_CSM_JOB_ID(SECOC_TX_CBK_ID(pduIdx)) == job->jobId                                   ) &&
          (SECOC_TX_STATE_WAITFORAUTHENTICATIONCALLBACK == SecOC_TxData[SECOC_TX_CBK_ID(pduIdx)].State)
         )
      {
        if (E_OK == result)
        {
          SecOC_TxData[SECOC_TX_CBK_ID(pduIdx)].CsmEvent = SECOC_TXEVENT_AUTHCALLBACK_OK;
        }
        else
        {
          SecOC_TxData[SECOC_TX_CBK_ID(pduIdx)].CsmEvent = SECOC_TXEVENT_AUTHCALLBACK_NOT_OK;

#if (STD_ON == SECOC_MACGENERATE_STATUS_PROP_ENABLED)
          SecOC_TxData[SECOC_TX_CBK_ID(pduIdx)].MacGenerateResult = result;
#endif /* #if (STD_ON == SECOC_MACGENERATE_STATUS_PROP_ENABLED) */
        }
        break;
      }
    }
  }
}
#endif /* #if (SECOC_TX_CSM_ASYNC == STD_ON) */

#if (SECOC_USE_DEFAULT_AUTH_INFO_PATTERN == STD_ON)
/* !LINKSTO SecOC.ASR20-11.Tx.SWS_SecOC_91013,1 */
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Tx_SendDefaultAuthenticationInformation
(
    P2CONST(uint16, AUTOMATIC, SECOC_APPL_CONST) txInstIdxList,
            uint16                               numberOfTxPdus,
            uint16                               FreshnessValueID,
            boolean                              sendDefaultAuthenticationInformation
)
{
  Std_ReturnType retVal = E_NOT_OK;
  uint16         pduIdx  = 0U;
  uint16         i = 0U;

#if !((SECOC_USER_DEFINED_TX_MAINFUNCTIONS == STD_ON) && (SECOC_INCLUDE_RTE == STD_ON))
  SECOC_PARAM_UNUSED(txInstIdxList);
#endif

  if (SECOC_INIT == SecOC_InitStatus)
  {
    for (i = 0U; i < numberOfTxPdus; i++)
    {
#if !((SECOC_USER_DEFINED_TX_MAINFUNCTIONS == STD_ON) && (SECOC_INCLUDE_RTE == STD_ON))
      pduIdx = i;
#else
      pduIdx = txInstIdxList[i];
#endif
      if (FreshnessValueID == SECOC_GET_TX_FRESHNESS_ID(pduIdx))
      {
        retVal = E_OK;
        if (FALSE == sendDefaultAuthenticationInformation)
        {
          SecOC_TxData[pduIdx].DefaultAuthInfoPatternState = SECOC_DEFAULT_AUTH_INFO_PATTERN_STATE_DISABLED;
        }
        else
        {
          SecOC_TxData[pduIdx].DefaultAuthInfoPatternState = SECOC_DEFAULT_AUTH_INFO_PATTERN_STATE_ENABLED;
        }
      }
    }
  }

  return retVal;
}
#endif /* #if (SECOC_USE_DEFAULT_AUTH_INFO_PATTERN == STD_ON) */

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/*==================[internal function definitions]===============================================*/

/*==================[state machine states]========================================================*/

#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

static FUNC(void, SECOC_CODE) SecOC_Tx_StateIdle
(
  uint16 instId
)
{
  /* !LINKSTO SecOC.ASR20-11.Tx.SWS_SecOC_00069,1 */
  if (
      (SECOC_TXEVENT_TRANSMIT       == SecOC_TxData[instId].TransmitEvent) ||
      (SECOC_TXEVENT_REAUTHENTICATE == SecOC_TxData[instId].TransmitEvent)
     )
  {
#if (STD_ON == SECOC_TX_USE_SAME_BUFFER)
    uint8 bufferStatus;
    /* CHECK: NOPARSE
     * Function like macro leads to unreachable code compiler (Wind River Diab) warning
     */
    SECOC_TX_GET_BUFFER_LVL2_STATUS(instId, bufferStatus);
    /* CHECK: PARSE */
    if (bufferStatus == SECOC_BUFFER_FREE)
#endif /* #if (STD_ON == SECOC_TX_USE_SAME_BUFFER) */
    {
      SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_1();
#if (STD_ON == SECOC_TX_USE_SAME_BUFFER)
      /* CHECK: NOPARSE
       * Function like macro leads to unreachable code compiler (Wind River Diab) warning
       */
      /* Deviation MISRAC2012-2 */
      SECOC_TX_SET_BUFFER_LVL2_STATUS(instId, SECOC_BUFFER_USED);
      /* CHECK: PARSE */
#endif /* #if (STD_ON == SECOC_TX_USE_SAME_BUFFER) */
      SecOC_TxData[instId].DataLength = SecOC_TxData[instId].ReceivedAuthPdu.SduLength;
      TS_MemCpy
      (
        SecOC_TxData[instId].SecuredPdu.SduDataPtr,
        SecOC_TxData[instId].ReceivedAuthPdu.SduDataPtr,
        SecOC_TxData[instId].DataLength
      );

      SecOC_TxData[instId].TransmitEvent = SECOC_TXEVENT_NONE;
      SecOC_TxData[instId].PduREvent     = SECOC_TXEVENT_NONE;

#if (STD_ON == SECOC_TX_USE_SAME_BUFFER)
        /* CHECK: NOPARSE
         * Function like macro leads to unreachable code compiler (Wind River Diab) warning
         */
      /* Deviation MISRAC2012-2 */
      SECOC_TX_SET_BUFFER_LVL1_STATUS(instId, SECOC_BUFFER_FREE);
      /* CHECK: PARSE */
#endif /* #if (STD_ON == SECOC_TX_USE_SAME_BUFFER) */
      SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_1();

#if (SECOC_BYPASS_AUTHENTICATION_ROUTINE == STD_ON)
      /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00030,1 */
      if (TRUE == SecOC_TxBypassAuthRoutineState)
      {
        TS_MemSet
        (
          &SecOC_TxData[instId].SecuredPdu.SduDataPtr[SecOC_TxData[instId].DataLength],
          SECOC_BYPASS_DEFAULT_AUTHINFO_VALUE,
          SECOC_REQUIREDBYTES(SECOC_TX_AUTHENTICATION_INFO_LEN(instId))
        );

        if ((SECOC_TX_AUTHENTICATION_INFO_LEN(instId) % 8U) != 0U)
        {
          SecOC_TxData[instId].SecuredPdu.SduDataPtr
            [
              SecOC_TxData[instId].DataLength +
              SECOC_REQUIREDBYTES(SECOC_TX_AUTHENTICATION_INFO_LEN(instId)) - 1U
            ] &= ~((1U << (8U - (SECOC_TX_AUTHENTICATION_INFO_LEN(instId) % 8U))) - 1U);
        }

        SecOC_TxData[instId].State = SECOC_TX_STATE_CONSTRUCTSECUREDPDU;
      }
      else
#endif /* #if (SECOC_BYPASS_AUTHENTICATION_ROUTINE == STD_ON) */
      {
        /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00031,1, SecOC.ASR430.Tx.SWS_SecOC_00034_1,2, SecOC.ASR430.Tx.SWS_SecOC_00034_2,1,
               SecOC.EB.RxTx.SWS_SecOC_00003,1*/
        /* DataId */
        {
          uint8 index;
          /* Deviation TASKING-1 */
          for (index = 0U; index < SECOC_DATAID_LENGTH; index++)
          {
           SecOC_TxData[instId].DataToAuthenticator[SECOC_DATAID_LENGTH - index - 1U] =
           (uint8) (SECOC_GET_TX_DATA_ID(instId) >> (index * 8U));
          }
        }

        /* Authentic data or the secured authentic data part */
#if (STD_ON == SECOC_PDU_SECURED_AREA)
        /* !LINKSTO SecOC.ASR431.RxTx.SWS_SecOC_00311,1, SecOC.ASR431.RxTx.SWS_SecOC_00312,1 */
        if (TRUE == SECOC_GET_TX_USE_SECURED_AREA(instId))
        {
          /* Copy the secured authentic part from the secured PDU */
          TS_MemCpy
          (
            &SecOC_TxData[instId].DataToAuthenticator[SECOC_DATAID_LENGTH],
            &SecOC_TxData[instId].SecuredPdu.SduDataPtr[SECOC_GET_TX_SECURED_AREA_OFFSET(instId)],
            SECOC_GET_TX_SECURED_AREA_LEN(instId)
          );
        }
        else
#endif /* #if (STD_ON == SECOC_PDU_SECURED_AREA) */
        {
          /* Authentic data */
          TS_MemCpy
          (
            &SecOC_TxData[instId].DataToAuthenticator[SECOC_DATAID_LENGTH],
            SecOC_TxData[instId].SecuredPdu.SduDataPtr,
            SecOC_TxData[instId].DataLength
          );
        }

        SecOC_TxData[instId].State = SECOC_TX_STATE_GETFRESHNESS;
      }

      /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00226,1 */
      SecOC_TxData[instId].AuthAttempts = 0U;

      /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00001,1 */
      SecOC_TxData[instId].ProcessingAuthentication = TRUE;
    }
  }
}

static FUNC(void, SECOC_CODE) SecOC_Tx_StateGetFreshness
(
  uint16 instId
)
{
  if (SECOC_TXEVENT_CANCEL == SecOC_TxData[instId].PduREvent)
  {
    SecOC_Tx_ResetSm(instId);
  }
  else
  {
#if (SECOC_QUERY_FRESHNESS_VALUE != SECOC_FRESHNESS_NONE)
    Std_ReturnType retVal = E_NOT_OK;
#endif /* #if (SECOC_QUERY_FRESHNESS_VALUE != SECOC_FRESHNESS_NONE) */
#if ((SECOC_TX_FRESHNESS_TRUNC_DATA == STD_ON) && (SECOC_QUERY_FRESHNESS_VALUE == SECOC_FRESHNESS_RTE))
    uint8 tempFreshnessValueBuffer[8U] = { 0U };
#endif /* #if ((SECOC_TX_FRESHNESS_TRUNC_DATA == STD_ON) && (SECOC_QUERY_FRESHNESS_VALUE == SECOC_FRESHNESS_RTE)) */

    /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00001,1 */
    SecOC_TxData[instId].ProcessingAuthentication = TRUE;

    /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00031,1, SecOC.ASR430.Tx.SWS_SecOC_00033,1, SecOC.ASR430.Tx.SWS_SecOC_00061,1,
                SecOC.ASR430.Tx.SWS_SecOC_00066,1, SecOC.ASR430.Tx.SWS_SecOC_00071,1 */
    /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00007,1 */

#if (SECOC_QUERY_FRESHNESS_VALUE != SECOC_FRESHNESS_NONE)
    if (0U != SECOC_GET_TX_FRESHNESS_LEN(instId))
    {
      uint32 freshnessValueLength = SECOC_GET_TX_FRESHNESS_LEN(instId);
      P2VAR(uint8, AUTOMATIC, SECOC_VAR) freshnessValuePtr = NULL_PTR;

#if (STD_ON == SECOC_PDU_SECURED_AREA)
      if (TRUE == SECOC_GET_TX_USE_SECURED_AREA(instId))
      {
        freshnessValuePtr = &SecOC_TxData[instId].DataToAuthenticator
                            [SECOC_DATAID_LENGTH + SECOC_GET_TX_SECURED_AREA_LEN(instId)];
      }
      else
#endif /* #if (STD_ON == SECOC_PDU_SECURED_AREA) */
      {
        freshnessValuePtr = &SecOC_TxData[instId].DataToAuthenticator
                            [SECOC_DATAID_LENGTH + SecOC_TxData[instId].DataLength];
      }

      /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00070,2 */
      switch(SecOC_TxConfig[instId].GetTxFreshnessFuncType)
      {
#if (SECOC_TX_FRESHNESS == STD_ON)
        case SECOC_GET_TX_FRESHNESS_FUNC_TYPE:
        {
          /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00222,3 */
          /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00224,3 */
          retVal = SecOC_Tx_Get_Freshness
                   (
                     instId,
                     SECOC_GET_TX_FRESHNESS_ID(instId),
                     freshnessValuePtr,
                     &freshnessValueLength
                   );
        }
        break;
#endif /* #if (SECOC_TX_FRESHNESS == STD_ON) */
#if (SECOC_TX_FRESHNESS_TRUNC_DATA == STD_ON)
        case SECOC_GET_TX_FRESHNESS_TRUNCDATA_FUNC_TYPE:
        {
          uint32 freshnessValueTxLength = SECOC_GET_TX_FRESHNESSTX_LEN(instId);

          /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00221,1 */
          /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00223,1 */
          retVal = SecOC_Tx_Get_Freshness_TruncData
                   (
                     instId,
                     SECOC_GET_TX_FRESHNESS_ID(instId),
                     freshnessValuePtr,
                     &freshnessValueLength,
#if (SECOC_QUERY_FRESHNESS_VALUE == SECOC_FRESHNESS_RTE)
                    tempFreshnessValueBuffer,
#else /* #if (SECOC_QUERY_FRESHNESS_VALUE == SECOC_FRESHNESS_RTE) */
                    &SecOC_TxData[instId].SecuredPdu.SduDataPtr[SecOC_TxData[instId].DataLength],
#endif /* #if (SECOC_QUERY_FRESHNESS_VALUE == SECOC_FRESHNESS_RTE) #else */
                     &freshnessValueTxLength
                   );
        }
        break;
#endif /* #if (SECOC_TX_FRESHNESS_TRUNC_DATA == STD_ON) */
        /* CHECK: NOPARSE */
        default:
        {
          /* Nothing to do. */
        }
        break;
        /* CHECK: PARSE */
      }

      SECOC_PARAM_UNUSED(freshnessValuePtr);
      SECOC_PARAM_UNUSED(freshnessValueLength);
    }
    else
    {
      retVal = E_OK;
    }

    if (retVal != E_OK)
    {
      if (SecOC_TxConfig[instId].MaxAuthAttempts > SecOC_TxData[instId].AuthAttempts)
      {
        /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00227,1 */
        SecOC_TxData[instId].AuthAttempts++;

#if (SECOC_TX_SYNC_PDU_PROCESSING == STD_ON)
        if (FALSE == SecOC_TxConfig[instId].UseSyncProcessing)
#endif /* #if (SECOC_TX_SYNC_PDU_PROCESSING == STD_ON) */
        {
          /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00002,2 */
          SecOC_TxData[instId].ProcessingAuthentication = FALSE;
        }
      }
      else
      {
#if (SECOC_ENABLE_SEC_EVENT_REPORTING == STD_ON)
        /* Failed to get Freshness Value. Report to IdsM */
        IdsM_SetSecurityEvent(SECOC_SEV_FRESHNESS_NOT_AVAILABLE);
#endif /* #if (SECOC_ENABLE_SEC_EVENT_REPORTING == STD_ON) */

#if (SECOC_USE_DEFAULT_AUTH_INFO_PATTERN == STD_ON)
        /* !LINKSTO SecOC.ASR20-11.Tx.SWS_SecOC_00229,1 */
        if (SECOC_DEFAULT_AUTH_INFO_PATTERN_STATE_ENABLED == SecOC_TxData[instId].DefaultAuthInfoPatternState)
        {
          SecOC_TxData[instId].DefaultAuthInfoPatternState = SECOC_DEFAULT_AUTH_INFO_PATTERN_STATE_USE;
          SecOC_TxData[instId].State = SECOC_TX_STATE_CONSTRUCTSECUREDPDU;
        }
        else
#endif /* #if (SECOC_USE_DEFAULT_AUTH_INFO_PATTERN == STD_ON) */
        {
          /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00155,1 */
          SecOC_Tx_ResetSm(instId);
        }
      }
    }
    else
#endif /* #if (SECOC_QUERY_FRESHNESS_VALUE != SECOC_FRESHNESS_NONE) */
    {
#if ((SECOC_TX_FRESHNESS_TRUNC_DATA == STD_ON) && (SECOC_QUERY_FRESHNESS_VALUE == SECOC_FRESHNESS_RTE))
      if (SECOC_GET_TX_FRESHNESS_TRUNCDATA_FUNC_TYPE == SecOC_TxConfig[instId].GetTxFreshnessFuncType)
      {
        TS_MemCpy
        (
          &SecOC_TxData[instId].SecuredPdu.SduDataPtr[SecOC_TxData[instId].DataLength],
          tempFreshnessValueBuffer,
          SECOC_REQUIREDBYTES(SECOC_GET_TX_FRESHNESSTX_LEN(instId))
        );
      }
#endif /* #if ((SECOC_TX_FRESHNESS_TRUNC_DATA == STD_ON) && (SECOC_QUERY_FRESHNESS_VALUE == SECOC_FRESHNESS_RTE)) */
      SecOC_TxData[instId].State = SECOC_TX_STATE_AUTHENTICATION;
    }
  }
}

static FUNC(void, SECOC_CODE) SecOC_Tx_StateAuthentication
(
  uint16 instId
)
{
  if (SECOC_TXEVENT_CANCEL == SecOC_TxData[instId].PduREvent)
  {
    SecOC_Tx_ResetSm(instId);
  }
  else
  {
    Std_ReturnType retVal = E_NOT_OK;
    uint32 dataLength = 0U;

    /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00001,1 */
    SecOC_TxData[instId].ProcessingAuthentication = TRUE;

    /* Length of the data based on which the MAC shall be calculate */
#if (STD_ON == SECOC_PDU_SECURED_AREA)
    if (TRUE == SECOC_GET_TX_USE_SECURED_AREA(instId))
    {
      dataLength =
      (
       (uint32) SECOC_GET_TX_SECURED_AREA_LEN(instId)          +
       (uint32) SECOC_DATAID_LENGTH                            +
       SECOC_REQUIREDBYTES(SECOC_GET_TX_FRESHNESS_LEN(instId))
      );
    }
    else
#endif /* #if (STD_ON == SECOC_PDU_SECURED_AREA) */
    {
      dataLength =
      (
       (uint32) SecOC_TxData[instId].DataLength              +
       (uint32) SECOC_DATAID_LENGTH                            +
       SECOC_REQUIREDBYTES(SECOC_GET_TX_FRESHNESS_LEN(instId))
      );
    }

#if (SECOC_TX_CSM_ASYNC == STD_ON)
    if (TRUE == SecOC_TxConfig[instId].UseCsmAsync)
    {
      /* Set the next execution state */
      SecOC_TxData[instId].State = SECOC_TX_STATE_WAITFORAUTHENTICATIONCALLBACK;
      /* Prepare the Csm callback event flag */
      SecOC_TxData[instId].CsmEvent = SECOC_TXEVENT_NONE;
    }
    else
    {
      /* Set the next execution state */
      SecOC_TxData[instId].State = SECOC_TX_STATE_CONSTRUCTSECUREDPDU;
    }
#else /* #if (SECOC_TX_CSM_ASYNC == STD_ON) */
    /* Set the next execution state */
    SecOC_TxData[instId].State = SECOC_TX_STATE_CONSTRUCTSECUREDPDU;
#endif /* #if (SECOC_TX_CSM_ASYNC == STD_ON) #else */

    SecOC_TxData[instId].AuthenticatorLength =
                                       SECOC_REQUIREDBYTES(SECOC_GET_TX_AUTHINFOTX_LEN(instId));

    switch(SecOC_TxConfig[instId].CsmFuncType)
    {
#if (SECOC_TX_USE_MACGENERATE == STD_ON)
      case SECOC_TX_MACGENERATE_FUNC_TYPE:
      {
        /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00060,1, SecOC.ASR430.Tx.SWS_SecOC_00065,1, SecOC.ASR430.Tx.SWS_SecOC_00070,2 */
        /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00035,2, SecOC.ASR430.Tx.SWS_SecOC_00031,1 */
        retVal = Csm_MacGenerate
                 (
                  (Csm_ConfigIdType)SECOC_TX_CSM_JOB_ID(instId),
                  CRYPTO_OPERATIONMODE_SINGLECALL,
                  SecOC_TxData[instId].DataToAuthenticator,
                  dataLength,
                  SecOC_TxData[instId].Authenticator,
                  &SecOC_TxData[instId].AuthenticatorLength
                 );
      }
      break;
#endif /* #if (SECOC_TX_USE_MACGENERATE == STD_ON) */
#if (SECOC_TX_USE_SIGNATUREGENERATE == STD_ON)
      case SECOC_TX_SIGNATUREGENERATE_FUNC_TYPE:
      {
        /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00060,1, SecOC.ASR430.Tx.SWS_SecOC_00065,1, SecOC.ASR430.Tx.SWS_SecOC_00070,2 */
        /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00035,2, SecOC.ASR430.Tx.SWS_SecOC_00031,1 */
        retVal = Csm_SignatureGenerate
                 (
                  (Csm_ConfigIdType)SECOC_TX_CSM_JOB_ID(instId),
                  CRYPTO_OPERATIONMODE_SINGLECALL,
                  SecOC_TxData[instId].DataToAuthenticator,
                  dataLength,
                  SecOC_TxData[instId].Authenticator,
                  &SecOC_TxData[instId].AuthenticatorLength
                 );
      }
      break;
#endif /* #if (SECOC_TX_USE_SIGNATUREGENERATE == STD_ON) */
      /* CHECK: NOPARSE */
      default:
      {
        /* Nothing to do. */
      }
      break;
      /* CHECK: PARSE */
    }

#if (STD_ON == SECOC_MACGENERATE_STATUS_PROP_ENABLED)
    SecOC_TxData[instId].MacGenerateResult = retVal;
#endif /* #if (STD_ON == SECOC_MACGENERATE_STATUS_PROP_ENABLED) */

    if (E_OK != retVal)
    {
      /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00228,1 */
      SecOC_Tx_CheckForCsmRetry(instId);
    }
  }
}

#if (SECOC_TX_CSM_ASYNC == STD_ON)
static FUNC(void, SECOC_CODE) SecOC_Tx_StateWaitForAuthenticationCallback
(
  uint16 instId
)
{
  /* Set the authentication procedure status */
  /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00001,1 */
  SecOC_TxData[instId].ProcessingAuthentication = TRUE;

  if (SECOC_TXEVENT_AUTHCALLBACK_OK == SecOC_TxData[instId].CsmEvent)
  {
    /* Clear authentication result */
    SecOC_TxData[instId].CsmEvent = SECOC_TXEVENT_NONE;

    /* Trigger a transition from state Wait to ConstructSecuredPdu */
    SecOC_TxData[instId].State = SECOC_TX_STATE_CONSTRUCTSECUREDPDU;
  }
  else
  if (SECOC_TXEVENT_AUTHCALLBACK_NOT_OK == SecOC_TxData[instId].CsmEvent)
  {
    /* Clear authentication result */
    SecOC_TxData[instId].CsmEvent = SECOC_TXEVENT_NONE;

    /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00228,1 */
    SecOC_Tx_CheckForCsmRetry(instId);
  }
  else
  {
    /* Wait for the Csm callback */
    /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00002,2 */
    SecOC_TxData[instId].ProcessingAuthentication = FALSE;
  }
}
#endif /* #if (SECOC_TX_CSM_ASYNC == STD_ON) */

static FUNC(void, SECOC_CODE) SecOC_Tx_StateConstructPdu
(
  uint16 instId
)
{
  if (SECOC_TXEVENT_CANCEL == SecOC_TxData[instId].PduREvent)
  {
    SecOC_Tx_ResetSm(instId);
  }
  else
  {
    /* Set the authentication procedure status */
    /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00001,1 */
    SecOC_TxData[instId].ProcessingAuthentication = TRUE;

    /* Set the next execution state */
    SecOC_TxData[instId].State = SECOC_TX_STATE_BROADCASTSECUREDPDU;

#if (STD_ON == SECOC_BYPASS_AUTHENTICATION_ROUTINE)
    if (FALSE == SecOC_TxBypassAuthRoutineState)
#endif /* #if (STD_ON == SECOC_BYPASS_AUTHENTICATION_ROUTINE) */
    {
      /* Copy the (truncated) freshness value to the secured PDU */
      SecOC_Tx_CopyFreshnessToSecuredPdu(instId);

      /* Copy the (truncated) MAC to the secured PDU */
      SecOC_Tx_CopyMacToSecuredPdu(instId);
    }

#if (SECOC_TX_USE_MESS_LINKER == STD_ON)
    if (0U != SecOC_TxConfig[instId].MessageLinkLength)
    {
      /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00209,1 */
      SecOC_Tx_CopyMessageLinkToCryptoPdu(instId);

      /* Combined length of Pdu Payload, FV, MAC and Message link */
      SecOC_TxData[instId].SecuredPdu.SduLength =
        SecOC_TxData[instId].DataLength + SECOC_GET_TX_CRYPTO_PDU_LEN(instId);
    }
    else
#endif /* #if (SECOC_TX_USE_MESS_LINKER == STD_ON) */
    {
      /* Combined length of Pdu Payload, FV, MAC */
      SecOC_TxData[instId].SecuredPdu.SduLength =
        SecOC_TxData[instId].DataLength +
        (uint16)SECOC_REQUIREDBYTES(SECOC_TX_AUTHENTICATION_INFO_LEN(instId));
    }

#if (SECOC_TX_USE_SEC_PDU_HEADER == STD_ON)
    if (SecOC_TxConfig[instId].SecuredPduHeaderLength != 0U)
    {
      /* !LINKSTO SecOC.ASR20-11.Tx.SWS_SecOC_00262,1 */
      SecOC_Tx_CopySecuredHeaderToPdu(instId);
    }
#endif /* #if (SECOC_TX_USE_SEC_PDU_HEADER == STD_ON) */

#if (SECOC_TX_SHAPE_SEC_PDU == STD_ON)
    SecOC_Tx_UpdateLayoutSecuredPdu(instId);
#endif /* #if (SECOC_TX_SHAPE_SEC_PDU == STD_ON) */
  }
}

static FUNC(void, SECOC_CODE) SecOC_Tx_StateBroadcastPdu
(
  uint16 instId
)
{
  /* CHECK: NOPARSE */
  if (SECOC_TXEVENT_CANCEL == SecOC_TxData[instId].PduREvent)
  {
    SecOC_Tx_ResetSm(instId);
  }
  /* CHECK: PARSE */
  else
  {
    Std_ReturnType retVal = E_NOT_OK;

    /* Set the next execution state */
    SecOC_TxData[instId].State = SECOC_TX_STATE_WAITFORCONFIRMATION;

#if (SECOC_BYPASS_AUTHENTICATION_ROUTINE == STD_ON)
    if (FALSE == SecOC_TxBypassAuthRoutineState)
#endif /* #if (SECOC_BYPASS_AUTHENTICATION_ROUTINE == STD_ON) */
    {
#if (STD_ON == SECOC_MACGENERATE_STATUS_PROP_ENABLED)
      SecOC_Tx_PropagateMacGenerateStatus(instId);
#endif /* #if (STD_ON == SECOC_MACGENERATE_STATUS_PROP_ENABLED) */
    }

#if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON)
    /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00202,1 */
    if (TRUE == SecOC_TxConfig[instId].UseSecPduCollection)
    {
      /* Transmit the authentic and cryptographic PDUs to the lower layer */

      retVal = SecOC_Tx_BroadcastAuthenticPdu(instId);

      if (E_OK == retVal)
      {
        retVal = SecOC_Tx_BroadcastCryptoPdu(instId);
      }
    }
    else
#endif /* #if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON) */
    {
      SecOC_TxData[instId].CopiedDataFromSecLength = 0U;

      /* Broadcast secured Pdu */
#if (STD_ON == SECOC_TX_USETP)
      if (TRUE == SecOC_TxConfig[instId].UseTp)
      {
        /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00180,1, SecOC.ASR430.Tx.SWS_SecOC_00031,1, SecOC.ASR430.Tx.SWS_SecOC_00072,1 */
        retVal = PduR_SecOCTpTransmit
                             (
                               (PduIdType) SECOC_GET_TX_SEC_PDU_ID_AT_PDUR(instId),
                               &SecOC_TxData[instId].SecuredPdu
                             );
      }
      else
#endif /* if (STD_ON == SECOC_TX_USETP) */
      {
        /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00180,1, SecOC.ASR430.Tx.SWS_SecOC_00031,1, SecOC.ASR430.Tx.SWS_SecOC_00062,1,
                    SecOC.ASR430.Tx.SWS_SecOC_00067,2, SecOC.ASR430.Tx.SWS_SecOC_00137,4 */
        retVal = PduR_SecOCTransmit
                             (
                               (PduIdType) SECOC_GET_TX_SEC_PDU_ID_AT_PDUR(instId),
                               &SecOC_TxData[instId].SecuredPdu
                             );
      }
    }

    if (E_OK == retVal)
    {
      if (0U != SECOC_GET_TX_FRESHNESS_LEN(instId))
      {
#if (SECOC_BYPASS_AUTHENTICATION_ROUTINE == STD_ON)
        if (FALSE == SecOC_TxBypassAuthRoutineState)
#endif /* #if (SECOC_BYPASS_AUTHENTICATION_ROUTINE == STD_ON) */
        {
        /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00232,3 */
        /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00233_1,3 */
#if (SECOC_USE_TX_SPDU_CONFIRMATION == STD_ON)
          if (FALSE != SecOC_TxConfig[instId].UseTxConfirmation)
          {
            SecOC_Tx_SPDU_Confirmation(instId, SECOC_GET_TX_FRESHNESS_ID(instId));
          }
#endif /* #if (SECOC_USE_TX_SPDU_CONFIRMATION == STD_ON) */
        }
      }
    }
    else
    {
      /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00229,1 */
      /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00078,1 */
      SecOC_Tx_ResetSm(instId);
    }
  }
}

static FUNC(void, SECOC_CODE) SecOC_Tx_StateWaitForConfirmation
(
  uint16 instId
)
{
  /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00063,1, SecOC.ASR430.Tx.SWS_SecOC_00064,1, SecOC.ASR430.Tx.SWS_SecOC_00075,1 */
  if (
      (SECOC_TXEVENT_TXCONFIRMATION_OK == SecOC_TxData[instId].PduREvent) ||
      (SECOC_TXEVENT_CANCEL            == SecOC_TxData[instId].PduREvent)
     )
  {
    /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00003,1 */
    if (SecOC_TxData[instId].TransmitEvent == SECOC_TXEVENT_TRANSMIT)
    {
      SecOC_TxData[instId].ProcessingAuthentication = TRUE;
    }
    else
    if (
        (SecOC_TxData[instId].PduREvent          == SECOC_TXEVENT_TXCONFIRMATION_OK) &&
        (SECOC_GET_TX_USE_REAUTHENTICATE(instId) == TRUE                           )
       )
    {
      /* !LINKSTO SecOC.ASR20-11.Tx.SWS_SecOC_00069,1 */
      SecOC_TxData[instId].TransmitEvent = SECOC_TXEVENT_REAUTHENTICATE;
    }
    else
    {
      /* Nothing to do. */
    }

#if (SECOC_USE_TX_CONFIRMATION_TIMEOUT == STD_ON)
    SecOC_TxData[instId].ConfirmationTimeoutCounter = 0U;
#endif /* #if (SECOC_USE_TX_CONFIRMATION_TIMEOUT == STD_ON) */

    SecOC_TxData[instId].State     = SECOC_TX_STATE_IDLE;
    SecOC_TxData[instId].PduREvent = SECOC_TXEVENT_NONE;
  }
#if (SECOC_USE_TX_CONFIRMATION_TIMEOUT == STD_ON)
  else
  {
    if (SecOC_TxConfig[instId].ConfirmationTimeoutThreshold > 0U)
    {
      SecOC_TxData[instId].ConfirmationTimeoutCounter++;

      /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00005,1 */
      if (
          SecOC_TxData[instId].ConfirmationTimeoutCounter ==
          SecOC_TxConfig[instId].ConfirmationTimeoutThreshold
         )
      {
        SecOC_TxData[instId].ConfirmationTimeoutCounter = 0U;
        SecOC_Tx_ResetSm(instId);
      }
    }
  }
#endif /* #if (SECOC_USE_TX_CONFIRMATION_TIMEOUT == STD_ON) */
}

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/*==================[helper functions]============================================================*/

#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

static FUNC(void, SECOC_CODE) SecOC_Tx_ResetSm
(
  uint16 instId
)
{
  SecOC_TxData[instId].State     = SECOC_TX_STATE_IDLE;
  SecOC_TxData[instId].PduREvent = SECOC_TXEVENT_NONE;
  TS_MemBZero(SecOC_TxData[instId].SecuredPdu.SduDataPtr, SECOC_GET_TX_SECURED_PDU_LEN(instId));
  /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00002,2 */
  SecOC_TxData[instId].ProcessingAuthentication = FALSE;
  /* Set the buffer used flag to false, to be able to receive authentic PDUs */
#if (STD_ON == SECOC_TX_USE_SAME_BUFFER)
  SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_1();
  /* CHECK: NOPARSE
   * Function like macro leads to unreachable code compiler (Wind River Diab) warning
   */
  /* Deviation MISRAC2012-2 */
  SECOC_TX_SET_BUFFER_LVL2_STATUS(instId, SECOC_BUFFER_FREE);
  /* CHECK: PARSE */
  SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_1();
#endif /* #if (STD_ON == SECOC_TX_USE_SAME_BUFFER) */
}

static FUNC(void, SECOC_CODE) SecOC_Tx_CheckForCsmRetry
(
  uint16 instId
)
{
  /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00228,1 */
  if (SecOC_TxConfig[instId].MaxAuthAttempts > SecOC_TxData[instId].AuthAttempts)
  {
    /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00227,1 */
    SecOC_TxData[instId].AuthAttempts++;
    SecOC_TxData[instId].State = SECOC_TX_STATE_AUTHENTICATION;

#if (SECOC_TX_SYNC_PDU_PROCESSING == STD_ON)
    if (FALSE == SecOC_TxConfig[instId].UseSyncProcessing)
#endif /* #if (SECOC_TX_SYNC_PDU_PROCESSING == STD_ON) */
    {
      /* Set the authentication procedure status */
      /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00002,2 */
      SecOC_TxData[instId].ProcessingAuthentication = FALSE;
    }
  }
#if (SECOC_USE_DEFAULT_AUTH == STD_OFF)
  else
  {
#if (SECOC_USE_DEFAULT_AUTH_INFO_PATTERN == STD_ON)
    /* !LINKSTO SecOC.ASR20-11.Tx.SWS_SecOC_00229,1 */
    if (SECOC_DEFAULT_AUTH_INFO_PATTERN_STATE_ENABLED == SecOC_TxData[instId].DefaultAuthInfoPatternState)
    {
      SecOC_TxData[instId].DefaultAuthInfoPatternState = SECOC_DEFAULT_AUTH_INFO_PATTERN_STATE_USE;
      SecOC_TxData[instId].State = SECOC_TX_STATE_CONSTRUCTSECUREDPDU;
    }
    else
#endif /* #if (SECOC_USE_DEFAULT_AUTH_INFO_PATTERN == STD_ON) */
    {
#if (STD_ON == SECOC_MACGENERATE_STATUS_PROP_ENABLED)
      SecOC_Tx_PropagateMacGenerateStatus(instId);
#endif /* #if (STD_ON == SECOC_MACGENERATE_STATUS_PROP_ENABLED) */

      /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00155,1 */
      /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00229,1 */
      SecOC_Tx_ResetSm(instId);
    }
  }
#else /* #if (SECOC_USE_DEFAULT_AUTH == STD_OFF) */
  else
  {
    /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00017,1 */
    TS_MemSet
    (
      SecOC_TxData[instId].Authenticator,
      SECOC_DEFAULT_AUTH_VALUE,
      SECOC_REQUIREDBYTES(SECOC_GET_TX_AUTHINFOTX_LEN(instId))
     );

    /* Set the next execution state */
    SecOC_TxData[instId].State = SECOC_TX_STATE_CONSTRUCTSECUREDPDU;
  }
#endif /* #if (SECOC_USE_DEFAULT_AUTH == STD_OFF) #else */
}

static FUNC(void, SECOC_CODE) SecOC_Tx_CopyFreshnessToSecuredPdu
(
  uint16 instId
)
{
  boolean skipProcessing = FALSE;

#if (SECOC_TX_FRESHNESS_TRUNC_DATA == STD_ON)
  /* If the GetTxFreshnessTruncData is used then there is no need to move and shift
   * the freshness value to the secured PDU because this is done by this API
   */
  if (SECOC_GET_TX_FRESHNESS_TRUNCDATA_FUNC_TYPE == SecOC_TxConfig[instId].GetTxFreshnessFuncType)
  {
    skipProcessing = TRUE;
  }
#endif /* #if (SECOC_TX_FRESHNESS_TRUNC_DATA == STD_ON) */

#if (STD_ON == SECOC_USE_DEFAULT_AUTH_INFO_PATTERN)
  if (SecOC_TxData[instId].DefaultAuthInfoPatternState == SECOC_DEFAULT_AUTH_INFO_PATTERN_STATE_USE)
  {
    /* Even if GetTxFreshnessTruncData is used, this is a failure state and this function is needed */
    skipProcessing = FALSE;
  }
#endif /* #if (STD_ON == SECOC_USE_DEFAULT_AUTH_INFO_PATTERN) */

  /* Deviation TASKING-1 */
  if(FALSE == skipProcessing)
  {
    const uint32 freshnessTxBits = SECOC_GET_TX_FRESHNESSTX_LEN(instId);

    /* least significant Bits of Freshness Value */
    /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00094,1 */
    if (0U < freshnessTxBits)
    {
      const uint32 freshnessDiffBits = (uint32)SECOC_GET_TX_FRESHNESS_LEN(instId) - freshnessTxBits;
      const uint32 freshnessDiffBytes = freshnessDiffBits / 8U;
      uint32 freshnessStartPos = 0U;

#if (STD_ON == SECOC_PDU_SECURED_AREA)
      if (TRUE == SECOC_GET_TX_USE_SECURED_AREA(instId))
      {
        freshnessStartPos = SECOC_DATAID_LENGTH +
                            (uint32) SECOC_GET_TX_SECURED_AREA_LEN(instId) +
                            freshnessDiffBytes;
      }
      else
#endif /* #if (STD_ON == SECOC_PDU_SECURED_AREA) */
      {
        freshnessStartPos = SECOC_DATAID_LENGTH +
                            (uint32) SecOC_TxData[instId].DataLength +
                            freshnessDiffBytes;
      }

      /* !LINKSTO SecOC.ASR20-11.Tx.SWS_SecOC_00037,1, SecOC.ASR430.Tx.SWS_SecOC_00061,1, SecOC.ASR430.Tx.SWS_SecOC_00066,1 */
      {
        P2VAR(uint8, AUTOMATIC, SECOC_VAR) da =
            &SecOC_TxData[instId].SecuredPdu.SduDataPtr[SecOC_TxData[instId].DataLength];

        uint32 copyLen = SECOC_REQUIREDBYTES(freshnessTxBits);

#if (STD_ON == SECOC_USE_DEFAULT_AUTH_INFO_PATTERN)
        if (SecOC_TxData[instId].DefaultAuthInfoPatternState == SECOC_DEFAULT_AUTH_INFO_PATTERN_STATE_USE)
        {
          TS_MemSet
          (
            &SecOC_TxData[instId].DataToAuthenticator[freshnessStartPos - freshnessDiffBytes],
            SECOC_DEFAULT_AUTH_INFO_PATTERN_VALUE,
            SECOC_REQUIREDBYTES(SECOC_GET_TX_FRESHNESS_LEN(instId))
          );
        }
#endif /* #if (STD_ON == SECOC_USE_DEFAULT_AUTH_INFO_PATTERN) */

        if (0U != (freshnessDiffBits % 8U))
        {
          /* FreshnessValueTxLength starts from Bit position 0 of a byte in the secured Pdu */
          SecOC_Tx_ShiftLeft
          (
            &SecOC_TxData[instId].DataToAuthenticator[freshnessStartPos],
            (SECOC_GET_TX_FRESHNESS_LEN(instId) - (freshnessDiffBytes * 8U)),
            (uint8) (freshnessDiffBits % 8U)
          );
        }

        TS_MemCpy
        (
          da,
          &SecOC_TxData[instId].DataToAuthenticator[freshnessStartPos],
          copyLen
        );

        if (0U != (freshnessTxBits % 8U))
        {
          da[copyLen - 1U] =
             (uint8)(da[copyLen- 1U] >> (8U - (freshnessTxBits % 8U)))
                                     << (8U - (freshnessTxBits % 8U));
        }
      }
    }
  }
}

static FUNC(void, SECOC_CODE) SecOC_Tx_CopyMacToSecuredPdu
(
  uint16 instId
)
{
  const uint32 freshnessRemainingBitsLen = (uint32)SECOC_GET_TX_FRESHNESSTX_LEN(instId) % 8U;
  const uint32 macStartPos = (uint32)(SecOC_TxData[instId].DataLength +
                                           ((uint32)SECOC_GET_TX_FRESHNESSTX_LEN(instId) / 8U));
  const uint32 authBitsLen = SECOC_GET_TX_AUTHINFOTX_LEN(instId);
  uint8 *authPtr = SecOC_TxData[instId].Authenticator;
  uint8 *secPduPtr = SecOC_TxData[instId].SecuredPdu.SduDataPtr;

#if (STD_ON == SECOC_USE_DEFAULT_AUTH_INFO_PATTERN)
      if (SECOC_DEFAULT_AUTH_INFO_PATTERN_STATE_USE == SecOC_TxData[instId].DefaultAuthInfoPatternState)
      {
        TS_MemSet
        (
          &authPtr[0],
          SECOC_DEFAULT_AUTH_INFO_PATTERN_VALUE,
          SECOC_REQUIREDBYTES(SECOC_GET_TX_AUTHINFOTX_LEN(instId))
        );
        /* This transmission cycle is completed */
        SecOC_TxData[instId].DefaultAuthInfoPatternState = SECOC_DEFAULT_AUTH_INFO_PATTERN_STATE_ENABLED;
      }
#endif /* #if (STD_ON == SECOC_USE_DEFAULT_AUTH_INFO_PATTERN) */

  /* Clear unused bits from the authenticator (MAC) */
  authPtr[authBitsLen / 8U] &= 0xFFU << (8U - (authBitsLen % 8U));

  if (0U == freshnessRemainingBitsLen)
  {
    /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00031,1, SecOC.ASR20-11.Tx.SWS_SecOC_00037,1, SecOC.ASR430.Tx.SWS_SecOC_00061,1,
                SecOC.ASR430.Tx.SWS_SecOC_00066,1, SecOC.ASR430.Tx.SWS_SecOC_00071,1 */
    TS_MemCpy
    (
      &secPduPtr[macStartPos],
      authPtr,
      SECOC_REQUIREDBYTES(authBitsLen)
    );
  }
  else
  {
    /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00031,1, SecOC.ASR20-11.Tx.SWS_SecOC_00037,1, SecOC.ASR430.Tx.SWS_SecOC_00061,1,
                SecOC.ASR430.Tx.SWS_SecOC_00066,1, SecOC.ASR430.Tx.SWS_SecOC_00071,1 */
    /* construct the 'merged' byte (least bits of Freshness Value, First Bits of Authenticator) */
    secPduPtr[macStartPos] |= (authPtr[0U] >> freshnessRemainingBitsLen);

    if (authBitsLen > (8U - freshnessRemainingBitsLen))
    {
      /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00036,1 */
      /* The authenticator and therefore also AuthInfoTxLength starts from the LSB */
      SecOC_Tx_ShiftLeft
      (
        authPtr,
        (uint32)authBitsLen,
        (uint8) (8U - freshnessRemainingBitsLen)
      );

      TS_MemCpy
      (
        &secPduPtr[
                   SecOC_TxData[instId].DataLength +
                   SECOC_REQUIREDBYTES(SECOC_GET_TX_FRESHNESSTX_LEN(instId))
                  ],
        authPtr,
        SECOC_REQUIREDBYTES(authBitsLen - (8U - freshnessRemainingBitsLen))
      );
    }
  }
}

#if (SECOC_TX_SHAPE_SEC_PDU == STD_ON)
static FUNC(void, SECOC_CODE) SecOC_Tx_UpdateLayoutSecuredPdu
(
 uint16 instId
)
{
  if (TRUE == SecOC_TxConfig[instId].UseShapeSecuredPdu)
  {
    PduLengthType secPduLen = SECOC_GET_TX_SECURED_PDU_LEN(instId);
    PduLengthType authInfo;

#if (SECOC_TX_USE_MESS_LINKER == STD_ON)
    if (0U != SecOC_TxConfig[instId].MessageLinkLength)
    {
      authInfo = SECOC_GET_TX_CRYPTO_PDU_LEN(instId);
    }
    else
#endif /* #if (SECOC_TX_USE_MESS_LINKER == STD_ON) */
    {
      authInfo = (PduLengthType)SECOC_REQUIREDBYTES(SECOC_TX_AUTHENTICATION_INFO_LEN(instId));
    }

    /* Add the padding to the secured PDU */
    /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00010,2 */
    SECOC_TX_SHAPE_FUNC
    (
      instId,
      SecOC_TxData[instId].SecuredPdu.SduDataPtr,
      &SecOC_TxData[instId].SecuredPdu.SduLength,
      &secPduLen,
      authInfo
    );

    SecOC_TxData[instId].SecuredPdu.SduLength = secPduLen;

    SecOC_TxData[instId].DataLength = SecOC_TxData[instId].SecuredPdu.SduLength - authInfo;
  }
}
#endif /* #if (SECOC_TX_SHAPE_SEC_PDU == STD_ON) */

#if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON)
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Tx_BroadcastAuthenticPdu
(
  uint16 instId
)
{
  Std_ReturnType retVal = E_NOT_OK;

#if (SECOC_TX_SHAPE_SEC_PDU == STD_ON)
  if (TRUE == SecOC_TxConfig[instId].UseShapeSecuredPdu)
  {
    SecOC_TxData[instId].SentAuthPdu.SduLength = SECOC_GET_TX_AUTH_PDU_LEN(instId);
  }
  else
#endif /* #if (SECOC_TX_SHAPE_SEC_PDU == STD_ON) */
  {
    SecOC_TxData[instId].SentAuthPdu.SduLength = SecOC_TxData[instId].DataLength;
#if (SECOC_TX_USE_SEC_PDU_HEADER == STD_ON)
    if (SecOC_TxConfig[instId].SecuredPduHeaderLength != 0U)
    {
      SecOC_TxData[instId].SentAuthPdu.SduLength = SECOC_GET_TX_AUTH_PDU_LEN(instId) +
                                                   SecOC_TxConfig[instId].SecuredPduHeaderLength;
    }
#endif /* #if (SECOC_TX_USE_SEC_PDU_HEADER == STD_ON) */
  }

  SecOC_TxData[instId].CopiedDataFromAuthLength = 0U;

#if (STD_ON == SECOC_TX_USETP)
  if (TRUE == SecOC_TxConfig[instId].UseTp)
  {
    /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00201,1 */
    retVal = PduR_SecOCTpTransmit
             (
               (PduIdType) SECOC_GET_TX_SENT_AUTH_PDU_ID_AT_PDUR(instId),
               &SecOC_TxData[instId].SentAuthPdu
             );
  }
  else
#endif /* #if (STD_ON == SECOC_TX_USETP) */
  {
    /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00201,1 */
    retVal = PduR_SecOCTransmit
             (
               (PduIdType) SECOC_GET_TX_SENT_AUTH_PDU_ID_AT_PDUR(instId),
               &SecOC_TxData[instId].SentAuthPdu
             );
  }

  return retVal;
}

static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Tx_BroadcastCryptoPdu
(
  uint16 instId
)
{
  Std_ReturnType retVal = E_NOT_OK;

  SecOC_TxData[instId].CryptoPdu.SduLength = SECOC_GET_TX_CRYPTO_PDU_LEN(instId);

  SecOC_TxData[instId].CryptoPdu.SduDataPtr =
    &SecOC_TxData[instId].SecuredPdu.SduDataPtr[SecOC_TxData[instId].SentAuthPdu.SduLength];

  SecOC_TxData[instId].CopiedDataFromCryptoLength = 0U;

#if (STD_ON == SECOC_TX_USETP)
  if (TRUE == SecOC_TxConfig[instId].UseTp)
  {
    /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00201,1 */
    retVal = PduR_SecOCTpTransmit
             (
               (PduIdType) SECOC_GET_TX_CRYPTO_PDU_ID_AT_PDUR(instId),
               &SecOC_TxData[instId].CryptoPdu
             );
  }
  else
#endif /* #if (STD_ON == SECOC_TX_USETP) */
  {
    /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00201,1 */
    retVal = PduR_SecOCTransmit
             (
               (PduIdType) SECOC_GET_TX_CRYPTO_PDU_ID_AT_PDUR(instId),
               &SecOC_TxData[instId].CryptoPdu
             );
  }

  return retVal;
}

#if (SECOC_TX_USE_MESS_LINKER == STD_ON)
static FUNC(void, SECOC_CODE) SecOC_Tx_CopyMessageLinkToCryptoPdu
(
  uint16 instId
)
{
  P2CONST(uint8, AUTOMATIC, SECOC_VAR) src = &SecOC_TxData[instId].SecuredPdu.SduDataPtr[SecOC_TxConfig[instId].MessageLinkPos / 8U];
  P2VAR(uint8, AUTOMATIC, SECOC_VAR) dst = &SecOC_TxData[instId].SecuredPdu.SduDataPtr[SecOC_TxData[instId].DataLength + (SECOC_TX_AUTHENTICATION_INFO_LEN(instId) / 8U)];
  uint32 size = SecOC_TxConfig[instId].MessageLinkLength;

  uint8 srcMaskBitsReq = 0x00U;
  uint8 srcDataMask = 0x00U;
  uint8 dstBitsSpace = 0x00U;

  uint8 srcBitPos = (uint8)(SecOC_TxConfig[instId].MessageLinkPos % 8U);
  uint32 srcBytePos = 0U;

  uint8 dstBitPos = (uint8)(SECOC_TX_AUTHENTICATION_INFO_LEN(instId) % 8U);
  uint32 dstBytePos = 0U;

  /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00210,1 */
  while (size > 0U)
  {
    /* Set the numbers of bits to be transferred this while cycle */
    if (size < ((uint32)8U - dstBitPos))
    {
      srcMaskBitsReq = (uint8)size;
    }
    else
    {
      srcMaskBitsReq = 8U - dstBitPos;
    }

    /* Clear unused bits from the source */
    srcDataMask = src[srcBytePos] << srcBitPos;

    /* Check if we must take other bits from the next byte in the source buffer */
    if (srcMaskBitsReq > (8U - srcBitPos))
    {
      srcDataMask |= (uint8)(src[srcBytePos + 1U] >> (8U - srcBitPos));
    }

    /* Check the current destination bit position is the start of the current destination byte */
    if (dstBitPos == 0U)
    {
      /* Check whether the number of bits to transfer is more than byte size */
      if (size >= 8U)
      {
        /* Transfer one full byte */
        dst[dstBytePos] = srcDataMask;
        /* Update the byte positions */
        srcBytePos++;
        dstBytePos++;

        /* Decrement the number of bits to be copied by 8 */
        size = size - 8U;
      }
      else
      {
        /* Transfer the required bits and clear the unused bits */
        dst[dstBytePos] = srcDataMask & (0xFFU << (8U - size));

        /* Nothing left to transfer */
        size = 0U;
      }
    }
    else
    {
      /* Count space in current destination byte to data storage */
      dstBitsSpace = 8U - dstBitPos;

      if (size <= dstBitsSpace)
      {
        /* Clear the bits that has to transfer in destination buffer */
        dst[dstBytePos] &= (uint8)(0xFFU << dstBitsSpace);
        /* Transfer the number of remaining bits to current destination */
        dst[dstBytePos] |= (uint8)(srcDataMask >> dstBitPos) & (0xFFU << (dstBitsSpace - size));
        /* Nothing left to transfer */
        size = 0U;
      }
      else
      {
        /* Clear the bits that has to transfer in destination buffer */
        dst[dstBytePos] &= (uint8)(0xFFU << (8U - dstBitPos));
        /* Fill the current byte of dst using srcDataMask*/
        dst[dstBytePos] |= (uint8)(srcDataMask >> dstBitPos);

        /* Update the source Byte and Bit Positions accordingly */
        if (dstBitsSpace > (8U - srcBitPos))
        {
          srcBytePos++;
          srcBitPos -= dstBitPos;
        }
        else
        if (dstBitsSpace < (8U - srcBitPos))
        {
          srcBitPos += dstBitsSpace;
        }
        else
        {
          srcBytePos++;
          srcBitPos = 0U;
        }

        /* Updated the Destination Byte and Bit Positions accordingly */
        dstBytePos++;
        dstBitPos = 0U;
        /* Decrement the number of bits to be copied by dstBitsSpace */
        size -= dstBitsSpace;
      }
    }
  }
}
#endif /* #if (SECOC_TX_USE_MESS_LINKER == STD_ON) */
#endif /* #if (SECOC_TX_USE_SECURED_PDU_COL == STD_ON) */

#if (SECOC_TX_USE_SEC_PDU_HEADER == STD_ON)
static FUNC(void, SECOC_CODE) SecOC_Tx_CopySecuredHeaderToPdu
(
  uint16 instId
)
{
  PduLengthType index;
  /* Combined length of Secured Header, PDU Payload, FV, MAC */
  SecOC_TxData[instId].SecuredPdu.SduLength += SecOC_TxConfig[instId].SecuredPduHeaderLength +
                                (SECOC_GET_TX_AUTH_PDU_LEN(instId)-SecOC_TxData[instId].DataLength);
  if (
      (SecOC_TxConfig[instId].UseDynamicLength == TRUE)
      &&
      (SecOC_TxData[instId].DataLength         < SECOC_GET_TX_AUTH_PDU_LEN(instId))
     )
  {
    for (index = SecOC_TxData[instId].SecuredPdu.SduLength; index > (SECOC_GET_TX_AUTH_PDU_LEN(instId) + SecOC_TxConfig[instId].SecuredPduHeaderLength); index--)
    {
      SecOC_TxData[instId].SecuredPdu.SduDataPtr[index - 1U] =
        SecOC_TxData[instId].SecuredPdu.SduDataPtr[index - SecOC_TxConfig[instId].SecuredPduHeaderLength - 1U -(SECOC_GET_TX_AUTH_PDU_LEN(instId)-SecOC_TxData[instId].DataLength)];
    }
    for (index = (SECOC_GET_TX_AUTH_PDU_LEN(instId) + SecOC_TxConfig[instId].SecuredPduHeaderLength); index > (SecOC_TxConfig[instId].SecuredPduHeaderLength + SecOC_TxData[instId].DataLength); index--)
    {
      SecOC_TxData[instId].SecuredPdu.SduDataPtr[index - 1U] = 0U;
    }
    for (index = (SecOC_TxData[instId].DataLength + SecOC_TxConfig[instId].SecuredPduHeaderLength); index > SecOC_TxConfig[instId].SecuredPduHeaderLength; index--)
    {
      SecOC_TxData[instId].SecuredPdu.SduDataPtr[index - 1U] =
        SecOC_TxData[instId].SecuredPdu.SduDataPtr[index - SecOC_TxConfig[instId].SecuredPduHeaderLength - 1U];
    }
  }
  else
  {
    for (index = SecOC_TxData[instId].SecuredPdu.SduLength; index > SecOC_TxConfig[instId].SecuredPduHeaderLength; index--)
    {
      SecOC_TxData[instId].SecuredPdu.SduDataPtr[index - 1U] =
        SecOC_TxData[instId].SecuredPdu.SduDataPtr[index - SecOC_TxConfig[instId].SecuredPduHeaderLength - 1U];
    }
  }

  for (index = 0U; index < SecOC_TxConfig[instId].SecuredPduHeaderLength; index++)
  {
    SecOC_TxData[instId].SecuredPdu.SduDataPtr[SecOC_TxConfig[instId].SecuredPduHeaderLength - index - 1U] =
      (uint8) (SecOC_TxData[instId].DataLength >> (index * 8U));
  }

}
#endif /* #if (SECOC_TX_USE_SEC_PDU_HEADER == STD_ON) */

#if (STD_ON == SECOC_MACGENERATE_STATUS_PROP_ENABLED)
static FUNC(void, SECOC_CODE) SecOC_Tx_PropagateMacGenerateStatus
(
  uint16 instId
)
{
  /* Variable used for holding the MAC Generate status to propagate */
  SecOC_MacGenerateStatusType SecOC_TxMacGenerateStatus;
#if (SECOC_NUMBER_FUNC_MACGENERATE_STATUS_PROP > 0)
  /* Variable used for holding the index of the pointer to MAC Generate status callout function */
  uint32 calloutIdx;
#endif /* #if (SECOC_NUMBER_FUNC_MACGENERATE_STATUS_PROP > 0) */

  /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00013,2 */
  if (
      (SECOC_STATUS_PROP_BOTH == SecOC_TxConfig[instId].MacGenerateStatusPropagationMode) ||
      (
        (SECOC_STATUS_PROP_FAILURE_ONLY == SecOC_TxConfig[instId].MacGenerateStatusPropagationMode) &&
        (E_OK                           != SecOC_TxData[instId].MacGenerateResult)
      )
     )
  {
    SecOC_TxMacGenerateStatus.freshnessValueID    = SECOC_GET_TX_FRESHNESS_ID(instId);
    SecOC_TxMacGenerateStatus.macGenerateStatus = SecOC_TxData[instId].MacGenerateResult;
    SecOC_TxMacGenerateStatus.secOCDataId         = SECOC_GET_TX_DATA_ID(instId);

#if (SECOC_NUMBER_FUNC_MACGENERATE_STATUS_PROP > 0)
    /* !LINKSTO SecOC.EB.Tx.SWS_SecOC_00013,2 */
    for (calloutIdx = 0U; calloutIdx < SECOC_NUMBER_FUNC_MACGENERATE_STATUS_PROP; calloutIdx++)
    {
      SecOC_TxMacGenerateStatusCallout[calloutIdx](SecOC_TxMacGenerateStatus);
    }
#endif /* #if (SECOC_NUMBER_FUNC_MACGENERATE_STATUS_PROP > 0) */

    /* call the Rte, if configured */
#if (STD_ON == SECOC_INCLUDE_RTE)
    SecOC_Tx_Write_MacGenerateStatus(instId, &SecOC_TxMacGenerateStatus);
#endif /* #if (STD_ON == SECOC_INCLUDE_RTE) */
  }
}
#endif /* #if (STD_ON == SECOC_MACGENERATE_STATUS_PROP_ENABLED) */

static FUNC(void, SECOC_CODE) SecOC_Tx_ShiftLeft
(
  P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) array,
        uint32                             bitLength,
        uint8                              shift
)
{
  uint16 arrayIdx;

  /* length of complete bytes after the shift */
  const uint32 byteLength_shifted = (bitLength - shift) / 8U;

  for (arrayIdx = 0U; arrayIdx < byteLength_shifted; arrayIdx++)
  {
    array[arrayIdx] = ((uint8) (array[arrayIdx]      << shift       )) |
                          ((uint8) (array[arrayIdx + 1U] >> (8U - shift)));
  }

  if (((bitLength % 8U) >= shift) || (0U == (bitLength % 8U)))
  {
    array[byteLength_shifted] = array[byteLength_shifted] << shift;
  }
  else
  {
    array[byteLength_shifted] = ((uint8) (array[byteLength_shifted] << shift)  ) |
                                (array[byteLength_shifted + 1U] >> (8U - shift));
  }
}

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

#endif /* #if (SECOC_NUMBER_TX_PDUS > 0) */

/*==================[end of file]=================================================================*/

