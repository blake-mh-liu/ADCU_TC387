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
 */

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * This is a bug in the tasking compiler and should be fixed with v6.1r1.
 *
 * TASKING-2) Deviated Rule: W549
 * W549: condition is always false
 *
 * Reason:
 * This is a bug in the tasking compiler.
 */

/*==================[includes]====================================================================*/

#include <SecOC_Rx.h>

#if (STD_ON == SECOC_INCLUDE_RTE)
#if (SECOC_NR_PARTITIONS == 0U)
#include <Rte_SecOC.h>
#endif
#endif /* #if (STD_ON == SECOC_INCLUDE_RTE) */

#if (SECOC_NUMBER_RX_PDUS > 0)

/*==================[macros]======================================================================*/

#if (STD_ON == SECOC_PDU_SECURED_AREA)
/** \brief Macro to calculate the sum of the Rx minimum required authentic data length
 *         that is comprised of the offset position and the length of the secured area,
 *         when the secured area is used
 */
#if (defined SECOC_RX_SECAREA_MIN_AUTHDATALEN)
#error SECOC_RX_SECAREA_MIN_AUTHDATALEN already defined
#endif /* #if (defined SECOC_RX_SECAREA_MIN_AUTHDATALEN) */
#define SECOC_RX_SECAREA_MIN_AUTHDATALEN(Id) ((uint32)(SECOC_GET_RX_SECURED_AREA_LEN((Id))) + \
                                              (uint32)(SECOC_GET_RX_SECURED_AREA_OFFSET((Id))))
#endif /* #if (STD_ON == SECOC_PDU_SECURED_AREA) */

#if (STD_ON == SECOC_RX_USE_MESS_LINKER)
/** \brief Macro to calculate the sum of the Rx minimum required authentic data length
 *         that is comprised of the offset position and the length of the message link,
 *         when the message link is used
 */
#if (defined SECOC_RX_MSGLINK_MIN_AUTHDATALEN)
#error SECOC_RX_MSGLINK_MIN_AUTHDATALEN already defined
#endif /* #if (defined SECOC_RX_MSGLINK_MIN_AUTHDATALEN) */
#define SECOC_RX_MSGLINK_MIN_AUTHDATALEN(Id) ((uint32)SecOC_RxConfig[(Id)].MessageLinkLength + \
                                              (uint32)SecOC_RxConfig[(Id)].MessageLinkPos)
#endif /* #if (STD_ON == SECOC_RX_USE_MESS_LINKER) */

#if (SECOC_API_VERSION_20_11 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION)
/** \brief Macro used to obtain the indentifier which based on the configuration can be
 *         freshness value ID or data ID
 */
#if (defined SECOC_GET_RX_ID)
#error SECOC_GET_RX_ID already defined
#endif /* #if (defined SECOC_GET_RX_ID) */
#if (STD_ON == SECOC_USE_DATA_ID_FOR_OVERRIDE)
#define SECOC_GET_RX_ID(Id) SECOC_GET_RX_DATA_ID(Id)
#else /* #if (STD_ON == SECOC_USE_DATA_ID_FOR_OVERRIDE) */
#define SECOC_GET_RX_ID(Id) SECOC_GET_RX_FRESHNESS_ID(Id)
#endif /* #if (STD_ON == SECOC_USE_DATA_ID_FOR_OVERRIDE) */
#endif /* #if (SECOC_API_VERSION_20_11 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) */

/*==================[type definitions]============================================================*/

/*==================[internal function declarations]==============================================*/

#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

/** \brief Idle state of the SecOC Rx state machine
 * \param[in] instId ID of the state machine instance (i.e. RX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Rx_StateIdle
(
  uint16 instId
);

/** \brief State of the SecOC Rx state machine, which constructs the data to authenticator
 * \param[in] instId ID of the state machine instance (i.e. RX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Rx_StateConstructDataToAuthenticator
(
  uint16 instId
);

/** \brief State of the SecOC Rx state machine, which starts a verification
 * \param[in] instId ID of the state machine instance (i.e. RX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Rx_StateVerification
(
  uint16 instId
);

#if (SECOC_RX_CSM_ASYNC == STD_ON)
/** \brief State of the SecOC Rx state machine, which waits
 *         for the callback and evaluates the result
 * \param[in] instId ID of the state machine instance (i.e. RX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Rx_StateWaitForVerificationCallback
(
  uint16 instId
);
#endif /* #if (SECOC_RX_CSM_ASYNC == STD_ON) */

/** \brief State of the SecOC Rx state machine which evaluates the verification result
 * \param[in] instId ID of the state machine instance (i.e. RX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Rx_StateCheckVerificationResult
(
  uint16 instId
);

/** \brief State of the SecOC Rx state machine which propagates the authenticated PDU
 *         to the upper layer
 * \param[in] instId ID of the state machine instance (i.e. RX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Rx_StateBroadcastPdu
(
  uint16 instId
);

/** \brief State of the SecOC Rx state machine which retries to obtain a new freshness value
 *         to retry to authenticate the secured PDU
 * \param[in] instId ID of the state machine instance (i.e. RX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Rx_StateRetryToObtainFreshness
(
  uint16 instId
);

/** \brief Resets the Rx state machine and frees the buffers
 * \param[in] instId            ID of the state machine instance (i.e. RX PDU)
 * \param[in] continueExec      Flag that indicates to the state machine that the next received PDU
 *                              with the same PDU Id shall be executed in the same main function
 * \param[in] notifyUpperLayer  Flag informing the upper layer that the current processed PDU
 *                              is/was dropped
 */
static FUNC(void, SECOC_CODE) SecOC_Rx_ResetSm
(
  uint16  instId,
  boolean continueExec,
  boolean notifyUpperLayer
);

/** \brief Function used to handle the verification retry
 * \param[in] instId ID of the state machine instance (i.e. RX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Rx_CheckForCsmRetry
(
  uint16 instId
);

/** \brief Prepare secured PDU buffer (SduDataPtr and SduLength)
 * \param[in] instId            ID of the state machine instance (i.e. RX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Rx_PrepareSecuredPdu
(
  uint16 instId
);

#if (STD_ON == SECOC_RX_USETP)
/** \brief Calls the upper layer if SecOC_PduType is SECOC_TPPDU
 * \param[in] instId            ID of the state machine instance (i.e. RX PDU)
 */
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_CallUpperLayer
(
  uint16 instId
);
#endif /* #if (STD_ON == SECOC_RX_USETP) */

#if (SECOC_RX_USE_MESS_LINKER == STD_ON)
/** \brief Function to determine if the message linker values are matching
 *
 * The function checks if the message link from the cryptographic PDU is matching
 * with the respective part from the authentic PDU
 *
 * \param[in] instId ID of the state machine instance (i.e. RX PDU)
 *
 * \returns Whether data from this two buffers is matching or not
 * \retval E_OK      The data from this two buffers is matching
 * \retval E_NOT_OK  The data from this two buffers is not matching
 */
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_CheckMessageLink
(
  uint16 instId
);
#endif /* #if (SECOC_RX_USE_MESS_LINKER == STD_ON) */

/** \brief Function to determine whether the received PDU is valid based on its length,
 *          i.e. whether its actual length corresponds to the required length.
 * \param[in] instId ID of the state machine instance (i.e. RX PDU)
 */
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_CheckPduContent
(
  uint16 instId
);

/** \brief Function to determine whether the received secured PDU is valid based on its length,
 *          i.e. whether its actual length corresponds to the required length.
 * \param[in] instId ID of the state machine instance (i.e. RX PDU)
 */
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_CheckSecPduContent
(
  uint16 instId
);

#if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON)
/** \brief Function to determine whether the received lower layer authentic or cryptographic PDU
 *         is valid based on its length, i.e. whether its actual length corresponds
 *         to the required length.
 * \param[in] instId ID of the state machine instance (i.e. RX PDU)
 */
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_CheckSecPduCollectionContent
(
  uint16 instId
);
#endif /* #if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON) */

#if (SECOC_RX_SHAPE_SEC_PDU == STD_ON)
/** \brief Function used to prepare and call the Rx side shaping function
 * \param[in] instId ID of the state machine instance (i.e. RX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Rx_CallShapeFunc
(
  uint16 instId
);
#endif /* #if (SECOC_RX_SHAPE_SEC_PDU == STD_ON) */

/** \brief Function used to extract the authentic data length from the received PDU
 * \param[in] instId ID of the state machine instance (i.e. RX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Rx_ExtractAuthenticDataLen
(
  uint16 instId
);

#if (SECOC_RX_USE_SEC_PDU_HEADER == STD_ON)
/** \brief Function used to extract the secured PDU header from the received PDU
 * \param[in] instId ID of the state machine instance (i.e. RX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Rx_ExtractSecuredPduHeader
(
  uint16 instId
);
#endif /* #if (SECOC_RX_USE_SEC_PDU_HEADER == STD_ON) */

#if ((STD_ON == SECOC_RX_AUTH_DATA_FRESHNESS) && (SECOC_QUERY_FRESHNESS_VALUE != SECOC_FRESHNESS_NONE))
/** \brief Function used to extract the secured PDU part that will be sent to the freshness SWC
 * \param[in] instId ID of the state machine instance (i.e. RX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Rx_ExtractAuthDataFreshnessValue
(
  uint16 instId
);
#endif /* #if ((STD_ON == SECOC_RX_AUTH_DATA_FRESHNESS) && (SECOC_QUERY_FRESHNESS_VALUE != SECOC_FRESHNESS_NONE)) */

#if (SECOC_QUERY_FRESHNESS_VALUE != SECOC_FRESHNESS_NONE)
/** \brief Function used to call the configured FvM functions to verify the received freshness
 *         value and obtain the complete freshness value
 * \param[in] instId ID of the state machine instance (i.e. RX PDU)
 */
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_CallFreshnessFunc
(
  uint16 instId
);
#endif /* #if (SECOC_QUERY_FRESHNESS_VALUE != SECOC_FRESHNESS_NONE) */

/** \brief Function used to check the retVal of the query for freshness
 * \param[in] instId ID of the state machine instance (i.e. RX PDU)
 * \param[in] retVal The return value of the freshness value SWC APIs
 */
static FUNC(void, SECOC_CODE) SecOC_Rx_CheckFreshnessFuncResult
(
  uint16         instId,
  Std_ReturnType retVal
);

/** \brief Function used to check if the verification status needs be changed
 *         (e.g. skip verification, drop PDU without verification)
 * \param[in] instId ID of the state machine instance (i.e. RX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Rx_CheckStatusOverridePreVerify
(
  uint16  instId
);

/** \brief Function used to renew the verify status override
 * \param[in]     instId    ID of the state machine instance (i.e. RX PDU)
 * \param[in,out] passData  verification result
 */
static FUNC(void, SECOC_CODE) SecOC_Rx_RenewStatusOverride
(
  uint16 instId,
  P2VAR(boolean, AUTOMATIC, SECOC_APPL_DATA) passData
);

/** \brief Function used to check if there are PDUs left for which the verification status
 *         needs to be overridden
 * \param[in] instId ID of the state machine instance (i.e. RX PDU)
 */
static FUNC(void, SECOC_CODE) SecOC_Rx_CheckStatusOverridePostVerify
(
  uint16  instId
);

#if ((SECOC_VERIFICATION_STATUS_PROP_NONE != SECOC_VERIFICATION_STATUS_PROP_ENABLED) || (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP))
/** \brief Function which propagates the verification attempt success to the configured callout
 *         functions
 * \param[in] instId ID of the state machine instance (i.e. RX PDU)
 *
 */
static FUNC(void, SECOC_CODE) SecOC_Rx_PropagateVerificationStatus
(
  uint16  instId
);
#endif /* #if ((SECOC_VERIFICATION_STATUS_PROP_NONE != SECOC_VERIFICATION_STATUS_PROP_ENABLED) || (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP)) */

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
static FUNC(void, SECOC_CODE) SecOC_Rx_ShiftLeft
(
  P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) array,
        uint32                             bitLength,
        uint8                              shift
);

#if ((STD_ON == SECOC_ENABLE_SEC_EVENT_REPORTING) && (STD_ON == SECOC_RX_USE_MACVERIFY))
/** \brief Function to report security events with context data.
 *
 * The function gets instId and creates context data with it.
 * Then the context data is reported to IdsM.
 *
 * \param[in]     securityEventId   Security Event ID
 * \param[in]     instId            Contains the instance ID
 *
 */
static FUNC(void, SECOC_CODE) SecOC_Rx_ReportSecurityEventWithContextData
(
  IdsM_SecurityEventIdType securityEventId,
  uint16 instId
);
#endif /* #if ((STD_ON == SECOC_ENABLE_SEC_EVENT_REPORTING) && (STD_ON == SECOC_RX_USE_MACVERIFY)) */

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/*==================[internal constants]==========================================================*/

#define SECOC_START_SEC_CONST_UNSPECIFIED
#include <SecOC_MemMap.h>

/**
 * \brief Variable which holds the state of the SecOC Rx state machine
 */
/* Deviation MISRAC2012-1 */
static CONST(SecOC_SmStateType, SECOC_CONST) SecOC_Rx_StateMachine[SECOC_NUMBER_OF_RXSTATES] =
{
  &SecOC_Rx_StateIdle,
  &SecOC_Rx_StateConstructDataToAuthenticator,
  &SecOC_Rx_StateVerification,
  &SecOC_Rx_StateCheckVerificationResult,
  &SecOC_Rx_StateBroadcastPdu,
  &SecOC_Rx_StateRetryToObtainFreshness,
#if (SECOC_RX_CSM_ASYNC == STD_ON)
  &SecOC_Rx_StateWaitForVerificationCallback
#endif /* #if (SECOC_RX_CSM_ASYNC == STD_ON) */
};

#define SECOC_STOP_SEC_CONST_UNSPECIFIED
#include <SecOC_MemMap.h>

/*==================[internal data]===============================================================*/

#if ((STD_ON == SECOC_ENABLE_SEC_EVENT_REPORTING) && (STD_ON == SECOC_RX_USE_MACVERIFY))

#define SECOC_START_SEC_VAR_CLEARED_8
#include <SecOC_MemMap.h>
/**
 * \brief Buffer to hold context data for IdsM security events.
 */
static VAR(uint8, SECOC_VAR) IdsmContextBuffer[SECOC_DATAID_LENGTH] = {0};

#define SECOC_STOP_SEC_VAR_CLEARED_8
#include <SecOC_MemMap.h>

#endif /* #if ((STD_ON == SECOC_ENABLE_SEC_EVENT_REPORTING) && (STD_ON == SECOC_RX_USE_MACVERIFY)) */

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

FUNC(void, SECOC_CODE) SecOC_Rx_Init
(
  void
)
{
  uint16 pduIdx;

  /* Deviation TASKING-1 */
  for (pduIdx = 0U; pduIdx < SECOC_NUMBER_RX_PDUS; pduIdx++)
  {
    /* Reset the state machine */
    SecOC_RxData[pduIdx].State     = SECOC_RX_STATE_IDLE;

    /* Clear the events */

    /* Clear the events which are indicating functions calls like SecOC_StartOfReception */
    SecOC_RxData[pduIdx].PduREvent = SECOC_RXEVENT_NONE;
#if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON)
    /* Clear the events which are indicating functions calls like SecOC_TpRxIndication */
    SecOC_RxData[pduIdx].PduRIndicationForAuth = SECOC_RXEVENT_NONE;
    SecOC_RxData[pduIdx].PduRIndicationForCrypto = SECOC_RXEVENT_NONE;
#endif /* #if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON) */
#if (SECOC_RX_CSM_ASYNC == STD_ON)
    /* Clear the events which are indicating functions calls like SecOC_CsmCallbackNotification */
    SecOC_RxData[pduIdx].CsmEvent = SECOC_RXEVENT_NONE;
#endif /* #if (SECOC_RX_CSM_ASYNC == STD_ON) */
    /* Clear the flag which is indicating if there is an ongoing verification procedure */
    SecOC_RxData[pduIdx].PduInProcess = FALSE;
    /* Clear the flag used for continues processing */
    SecOC_RxData[pduIdx].ProcessingVerification = FALSE;
    /* Reset the verification result */
    SecOC_RxData[pduIdx].CsmVerificationResult = CRYPTO_E_VER_NOT_OK;

    /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00235,1 */
    /* Clear the counters used for authentication build and verify retries */
    SecOC_RxData[pduIdx].AuthAttempts = 0U;
    SecOC_RxData[pduIdx].FVSyncAttempts = 0U;
    /* Clear the verification result */
    SecOC_RxData[pduIdx].VerificationResult = SECOC_VERIFICATIONFAILURE;
    /* Clear the variables used for overwriting the verification status */
#if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION)
    SecOC_RxData[pduIdx].VerifyStatusOverride = SECOC_OVERRIDESTATUS_CANCEL;
#else /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) */
    SecOC_RxData[pduIdx].VerifyStatusOverride = SECOC_OVERRIDE_CANCEL;
#endif /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) #else */
    SecOC_RxData[pduIdx].NumMsgToOverride = 0U;
#if (SECOC_VERIFICATION_STATUS_PROP_EB == SECOC_VERIFICATION_STATUS_PROP_ENABLED)
    SecOC_RxData[pduIdx].CsmVerificationReturn = E_NOT_OK;
#endif /* #if (SECOC_VERIFICATION_STATUS_PROP_EB == SECOC_VERIFICATION_STATUS_PROP_ENABLED) */

#if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION)
#if (STD_ON == SECOC_OVERRIDE_VERIFYSTATUS_PASS)
    /* Clear the flag which is indicating if the verification status was already overridden */
    SecOC_RxData[pduIdx].RenewedVerStatus = FALSE;
#endif /* #if (STD_ON == SECOC_OVERRIDE_VERIFYSTATUS_PASS)*/
#else /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) */
    SecOC_RxData[pduIdx].RenewedVerStatus = FALSE;
#endif /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) #else */
#if (STD_ON == SECOC_RX_USE_SAME_BUFFER)
    /* Clear the flags which is indicating if the same buffer is currently being used */
    if (SecOC_RxData[pduIdx].BufferUsed != NULL_PTR)
    {
      *SecOC_RxData[pduIdx].BufferUsed = FALSE;
    }
#endif /* #if (STD_ON == SECOC_RX_USE_SAME_BUFFER) */

    /* Set pointers to buffers, used for storing the PDUs and for internal processing */
    SecOC_RxData[pduIdx].ReceivedSecuredPdu.SduDataPtr = SECOC_GET_RX_RECVSECURED_PDU_ADR(pduIdx);
#if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON)
    SecOC_Rx_InitQueue(pduIdx);
#endif /* #if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON) */
#if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON)
    if (SecOC_RxConfig[pduIdx].UseSecPduCollection == TRUE)
    {
      SecOC_RxData[pduIdx].ReceivedAuthPdu.SduDataPtr = SECOC_GET_RX_RECVAUTH_PDU_ADR(pduIdx);
      SecOC_RxData[pduIdx].CryptoPdu.SduDataPtr = SECOC_GET_RX_CRYPTO_PDU_ADR(pduIdx);
    }
    else
    {
      SecOC_RxData[pduIdx].ReceivedAuthPdu.SduDataPtr = NULL_PTR;
      SecOC_RxData[pduIdx].CryptoPdu.SduDataPtr = NULL_PTR;
    }
#endif /* #if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON) */
    SecOC_RxData[pduIdx].SecuredPdu.SduDataPtr = SECOC_GET_RX_SECURED_PDU_ADR(pduIdx);
    SecOC_RxData[pduIdx].Authenticator = SECOC_GET_RX_AUTHENTICATOR_ADR(pduIdx);
#if (SECOC_USE_META_DATA == STD_ON)
    if (SecOC_RxConfig[pduIdx].UseMetaData == TRUE)
    {
      SecOC_RxData[pduIdx].SecuredPduMetaData = SECOC_GET_RX_SECURED_PDU_OFFSET_ADR(pduIdx, SECOC_GET_RX_SECURED_PDU_LEN(pduIdx));
    }
#endif /* #if (SECOC_USE_META_DATA == STD_ON) */
    SecOC_RxData[pduIdx].DataToAuthenticator = SECOC_GET_RX_DATATOAUTH_ADR(pduIdx);

    /* Clear the dynamic length of the received data */
    SecOC_RxData[pduIdx].SecuredPdu.SduLength = 0U;
    SecOC_RxData[pduIdx].DataLength = 0U;
    SecOC_RxData[pduIdx].ReceivedSecuredPdu.SduLength = 0U;
#if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON)
    SecOC_RxData[pduIdx].ReceivedAuthPdu.SduLength = 0U;
    SecOC_RxData[pduIdx].CryptoPdu.SduLength = 0U;
#endif /* #if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON) */

#if (SECOC_USE_CSMJOBREF_CALLOUT == STD_ON)
    /* !LINKSTO  SecOC.EB.Rx.SWS_SecOC_00022,1, SecOC.EB.Rx.SWS_SecOC_00023,1 */
    /* Get the new Csm job ID based on the configured one */
    SecOC_RxData[pduIdx].CsmJobIdPostDefined =
      SECOC_CSMJOBREF_CALLOUT(SecOC_RxConfig[pduIdx].CsmJobId);
#endif /* #if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON) */
  }
}

FUNC(void, SECOC_CODE) SecOC_Rx_DeInit
(
  void
)
{
  uint16 pduIdx;

  /* Deviation TASKING-1 */
  for (pduIdx = 0U; pduIdx < SECOC_NUMBER_RX_PDUS; pduIdx++)
  {
    /* Release pointers to buffers, used for storing the PDUs and for internal processing */

    SecOC_RxData[pduIdx].ReceivedSecuredPdu.SduDataPtr = NULL_PTR;
#if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON)
    if (SecOC_RxConfig[pduIdx].UseSecPduCollection == TRUE)
    {
      SecOC_RxData[pduIdx].ReceivedAuthPdu.SduDataPtr = NULL_PTR;
      SecOC_RxData[pduIdx].CryptoPdu.SduDataPtr = NULL_PTR;
    }
#endif /* #if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON) */
    SecOC_RxData[pduIdx].SecuredPdu.SduDataPtr = NULL_PTR;
    SecOC_RxData[pduIdx].Authenticator = NULL_PTR;
    SecOC_RxData[pduIdx].DataToAuthenticator = NULL_PTR;

    /* Clear the dynamic length of the received data */
    SecOC_RxData[pduIdx].SecuredPdu.SduLength = 0U;
    SecOC_RxData[pduIdx].DataLength = 0U;
    SecOC_RxData[pduIdx].ReceivedSecuredPdu.SduLength = 0U;
#if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON)
    SecOC_RxData[pduIdx].ReceivedAuthPdu.SduLength = 0U;
    SecOC_RxData[pduIdx].CryptoPdu.SduLength = 0U;
#endif /* #if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON) */
  }
}

FUNC(void, SECOC_CODE) SecOC_Rx_ProcessPduStates
(
  uint16 pduIdx
)
{
  /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00020,1 */
  do
  {
    SecOC_RxData[pduIdx].ProcessingVerification = FALSE;

    SecOC_Rx_StateMachine[SecOC_RxData[pduIdx].State](pduIdx);
  }
  while (TRUE == SecOC_RxData[pduIdx].ProcessingVerification);
}

#if (SECOC_USER_DEFINED_RX_MAINFUNCTIONS == STD_ON)
#if (SECOC_NUMBER_RX_PDUS > 0)
/* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00171,1 */
FUNC(void, SECOC_CODE) SecOC_MainFunctionRx
(
  P2CONST(uint16, AUTOMATIC, SECOC_APPL_CONST) rxInstIdxList,
          uint16                               numberOfRxInstances
)
{
  /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00172,1 */
  if (SECOC_INIT == SecOC_InitStatus)
  {
    uint16 instIdx;
    uint16 i;

    /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00174,1 */
    for (i = 0U; numberOfRxInstances > i; i++)
    {
      instIdx = rxInstIdxList[i];
/* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00018,1 */
#if (SECOC_RX_SYNC_PDU_PROCESSING == STD_ON)
      /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00017,1 */
      if (FALSE == SecOC_RxConfig[instIdx].UseSyncProcessing)
#endif /* #if (SECOC_RX_SYNC_PDU_PROCESSING == STD_ON) */
      {
        /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00001,1 */
        SecOC_Rx_ProcessPduStates(instIdx);
      }
    }
  }
}
#endif /* #if (SECOC_NUMBER_RX_PDUS > 0) */
#endif /* #if (SECOC_USER_DEFINED_RX_MAINFUNCTIONS == STD_ON) */

#if (SECOC_RX_CSM_ASYNC == STD_ON)
FUNC(void, SECOC_CODE) SecOC_Rx_CsmCallbackNotification
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
    /* Check if the Csm callback is for the verification service */
    for (pduIdx = startIdx; pduIdx < endIdx; pduIdx++)
    {
      if ((SECOC_RX_CSM_JOB_ID(SECOC_RX_CBK_ID(pduIdx)) == job->jobId                                 ) &&
          (SECOC_RX_STATE_WAITFORVERIFICATIONCALLBACK == SecOC_RxData[SECOC_RX_CBK_ID(pduIdx)].State)
         )
      {
        if (E_OK == result)
        {
          SecOC_RxData[SECOC_RX_CBK_ID(pduIdx)].CsmEvent = SECOC_RXEVENT_VERCALLBACK_OK;
        }
        else
        {
          SecOC_RxData[SECOC_RX_CBK_ID(pduIdx)].CsmEvent = SECOC_RXEVENT_VERCALLBACK_NOT_OK;
        }
#if (SECOC_VERIFICATION_STATUS_PROP_EB == SECOC_VERIFICATION_STATUS_PROP_ENABLED)
        SecOC_RxData[SECOC_RX_CBK_ID(pduIdx)].CsmVerificationReturn = result;
#endif /* #if (SECOC_VERIFICATION_STATUS_PROP_EB == SECOC_VERIFICATION_STATUS_PROP_ENABLED) */
        break;
      }
    }
  }
}
#endif /* #if (SECOC_RX_CSM_ASYNC == STD_ON) */

#if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION)
/* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00122,3 */
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_VerifyStatusOverride_43
(
  P2CONST(uint16, AUTOMATIC, SECOC_APPL_CONST) rxInstIdxList,
          uint16                               numberOfRxPdus,
          uint16                               freshnessValueId,
          uint8                                overrideStatus,
          uint8                                numberOfMessagesToOverride
)
{
  uint16         pduIdx  = 0U;
  uint16         i = 0U;
  Std_ReturnType idFound = E_NOT_OK;

#if !((SECOC_USER_DEFINED_RX_MAINFUNCTIONS == STD_ON) && (SECOC_INCLUDE_RTE == STD_ON))
  SECOC_PARAM_UNUSED(rxInstIdxList);
#endif

  if (SECOC_INIT == SecOC_InitStatus)
  {
#if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_OFF)
    if (SECOC_OVERRIDESTATUS_CANCEL >= overrideStatus)
#else
    if (
        (SECOC_OVERRIDESTATUS_SKIP_UNTIL_NOTICE == overrideStatus) ||
        (SECOC_OVERRIDESTATUS_PASS_MSG_NUMBER   == overrideStatus) ||
        (SECOC_OVERRIDESTATUS_CANCEL >= overrideStatus)
       )
#endif /* #if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_OFF) */
    {
      /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00006,1 */
      for (i = 0U; i < numberOfRxPdus; i++)
      {
#if !((SECOC_USER_DEFINED_RX_MAINFUNCTIONS == STD_ON) && (SECOC_INCLUDE_RTE == STD_ON))
        pduIdx = i;
#else
        pduIdx = rxInstIdxList[i];
#endif

        if (freshnessValueId == SECOC_GET_RX_FRESHNESS_ID(pduIdx))
        {
          SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
#if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_OFF)
          if (SECOC_OVERRIDESTATUS_FAIL_MSG_NUMBER == overrideStatus)
#else
          if ((SECOC_OVERRIDESTATUS_PASS_MSG_NUMBER == overrideStatus)||
              (SECOC_OVERRIDESTATUS_FAIL_MSG_NUMBER == overrideStatus)
             )
#endif /* #if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_OFF) */
          {
            SecOC_RxData[pduIdx].NumMsgToOverride = numberOfMessagesToOverride;
          }
          SecOC_RxData[pduIdx].VerifyStatusOverride = overrideStatus;
          SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
          idFound = E_OK;
        }
      }
    }
  }
  return idFound;
}
#else /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) */
/* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00122,1 */
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_VerifyStatusOverride_44
(
  P2CONST(uint16,                     AUTOMATIC, SECOC_APPL_CONST) rxInstIdxList,
          uint16                                                   numberOfRxPdus,
          uint16                                                   ValueId,
          SecOC_OverrideStatusType                                 overrideStatus,
          uint8                                                    numberOfMessagesToOverride
)
{
  uint16         pduIdx  = 0U;
  uint16         i  = 0U;
  Std_ReturnType idFound = E_NOT_OK;

#if !((SECOC_USER_DEFINED_RX_MAINFUNCTIONS == STD_ON) && (SECOC_INCLUDE_RTE == STD_ON))
  SECOC_PARAM_UNUSED(rxInstIdxList);
#endif

  if (SECOC_INIT == SecOC_InitStatus)
  {
#if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_OFF)
    if (SECOC_OVERRIDE_CANCEL >= overrideStatus)
#else
    if (
        (SECOC_OVERRIDE_SKIP_UNTIL_LIMIT  == overrideStatus) ||
        (SECOC_OVERRIDE_SKIP_UNTIL_NOTICE == overrideStatus) ||
        (SECOC_OVERRIDE_PASS_UNTIL_LIMIT  == overrideStatus) ||
        (SECOC_OVERRIDE_PASS_UNTIL_NOTICE == overrideStatus) ||
        (SECOC_OVERRIDE_CANCEL            >= overrideStatus)
       )
#endif /* #if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_OFF) */
    {
      for (i = 0U; i < numberOfRxPdus; i++)
      {
#if !((SECOC_USER_DEFINED_RX_MAINFUNCTIONS == STD_ON) && (SECOC_INCLUDE_RTE == STD_ON))
        pduIdx = i;
#else
        pduIdx = rxInstIdxList[i];
#endif

#if (STD_ON == SECOC_USE_DATA_ID_FOR_OVERRIDE)
        if (ValueId == SECOC_GET_RX_DATA_ID(pduIdx))
#else
        if (ValueId == SECOC_GET_RX_FRESHNESS_ID(pduIdx))
#endif
        {
          SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
#if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_OFF)
          if (SECOC_OVERRIDE_DROP_UNTIL_LIMIT == overrideStatus)
#else
          if ((SECOC_OVERRIDE_PASS_UNTIL_LIMIT == overrideStatus)||
              (SECOC_OVERRIDE_SKIP_UNTIL_LIMIT == overrideStatus)||
              (SECOC_OVERRIDE_DROP_UNTIL_LIMIT == overrideStatus)
             )
#endif /* #if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_OFF) */
          {
            SecOC_RxData[pduIdx].NumMsgToOverride = numberOfMessagesToOverride;
          }
          SecOC_RxData[pduIdx].VerifyStatusOverride = overrideStatus;
          SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
          idFound = E_OK;
        }
      }
    }
  }
  return idFound;
}
#endif /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) */

#if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON)

FUNC(void, SECOC_CODE) SecOC_Rx_InitQueue
(
  uint16 instId
)
{
  SecOC_RxQueueType* Queue = &SecOC_RxData[instId].Queue;

  /* Reset all elements */
  Queue->WritePtr = SECOC_GET_RX_RECVSECURED_PDU_ADR(instId);
  Queue->ReadPtr = SECOC_GET_RX_RECVSECURED_PDU_ADR(instId);
  Queue->ReadBufferIndex = 0U;
  Queue->WriteBufferIndex = 0U;
  Queue->WriteRemainingBytes = 0U;
  Queue->Count = 0U;
  Queue->WriteInProgress = FALSE;
}

FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_ReadPduFromQueue
(
        uint16                                       instId,
  P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA)           dataPtr,
  P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA)   dataLenPtr
)
{
  Std_ReturnType retVal = E_NOT_OK;
  SecOC_RxQueueType* Queue = &SecOC_RxData[instId].Queue;
  uint32 recvSecuredPduOffset = 0U;

  if (SECOC_IS_RX_RECEIVED_SECURED_PDU_BUFFER_EMPTY(instId) == FALSE)
  {
    *dataLenPtr = Queue->StoredPduLength[Queue->ReadBufferIndex];
    Queue->StoredPduLength[Queue->ReadBufferIndex] = 0U;

    TS_MemCpy(dataPtr, Queue->ReadPtr, *dataLenPtr);
#if (STD_ON == SECOC_USE_META_DATA)
    if (SecOC_RxConfig[instId].UseMetaData == TRUE)
    {
      SecOC_RxData[instId].SecuredPduMetaData = &Queue->ReadPtr[SECOC_GET_RX_SECURED_PDU_LEN(instId)];
    }
#endif /* #if (STD_ON == SECOC_USE_META_DATA) */
    retVal = E_OK;
    /* Shift the buffer index to the next slot */
    Queue->ReadBufferIndex++;
    Queue->ReadBufferIndex %= Queue->QueueSize;
    --Queue->Count;
#if (STD_ON == SECOC_USE_META_DATA)
    if (SecOC_RxConfig[instId].UseMetaData == TRUE)
    {
      recvSecuredPduOffset = (uint32)(Queue->ReadBufferIndex * ((uint32)SECOC_GET_RX_SECURED_PDU_LEN(instId) + SecOC_RxConfig[instId].MetaDataLength));
    }
    else
    {
      recvSecuredPduOffset = (uint32)Queue->ReadBufferIndex * SECOC_GET_RX_SECURED_PDU_LEN(instId);
    }
#else /* #if (STD_ON == SECOC_USE_META_DATA) */
    recvSecuredPduOffset = (uint32)Queue->ReadBufferIndex * SECOC_GET_RX_SECURED_PDU_LEN(instId);
#endif /* #if (STD_ON == SECOC_USE_META_DATA) #else */
    Queue->ReadPtr = SECOC_GET_RX_RECVSECURED_PDU_OFFSET_ADR(instId,recvSecuredPduOffset);
  }

  return retVal;
}

FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_Rx_WritePduToQueue
(
        uint16                                instId,
  P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA)    dataPtr,
        PduLengthType                         dataLen,
        PduLengthType                         expectedTotalDataLen
)
{
  BufReq_ReturnType bufReqRetVal = BUFREQ_E_OVFL;
  SecOC_RxQueueType* Queue = &SecOC_RxData[instId].Queue;
#if (STD_ON == SECOC_USE_META_DATA)
  PduInfoType PduInfoLocal;
  PduInfoLocal.SduDataPtr = dataPtr;
  PduInfoLocal.SduLength = dataLen;
#endif /* #if (STD_ON == SECOC_USE_META_DATA) */

  /* Write a buffer of the received secured PDU */
  if ((SECOC_GET_RX_SECURED_PDU_LEN(instId) >= expectedTotalDataLen) &&
      (SECOC_IS_RX_RECEIVED_SECURED_PDU_BUFFER_FULL(instId) == FALSE)
     )
  {
    /* Check if writing is in progress, if not initiate */
    if (
        (Queue->WriteInProgress == FALSE) &&
        (expectedTotalDataLen > 0U)
        )
    {
      Queue->StoredPduLength[Queue->WriteBufferIndex] = 0U;
      Queue->WriteRemainingBytes = expectedTotalDataLen;
      Queue->WriteInProgress = TRUE;

#if (STD_ON == SECOC_ASR403_API)
      bufReqRetVal = BUFREQ_OK;
#endif /* #if (STD_ON == SECOC_ASR403_API) */
    }

    if ((dataLen <= Queue->WriteRemainingBytes) &&
        (dataLen > 0U) &&
        (dataPtr != NULL_PTR)
       )
    {
      uint32 recvSecuredPduOffset = 0U;

      TS_MemCpy
      (
        Queue->WritePtr,
        dataPtr,
        dataLen
      );

      /* Move the WritePtr pointer forwards by dataLen */
      Queue->StoredPduLength[Queue->WriteBufferIndex] += dataLen;
#if (STD_ON == SECOC_USE_META_DATA)
      if (SecOC_RxConfig[instId].UseMetaData == TRUE)
      {
        recvSecuredPduOffset = (uint32)Queue->WriteBufferIndex * ((uint32)SecOC_RxConfig[instId].MetaDataLength + SECOC_GET_RX_SECURED_PDU_LEN(instId));
        recvSecuredPduOffset += Queue->StoredPduLength[Queue->WriteBufferIndex];
      }
      else
      {
        recvSecuredPduOffset = ((uint32)Queue->WriteBufferIndex * SECOC_GET_RX_SECURED_PDU_LEN(instId)) + Queue->StoredPduLength[Queue->WriteBufferIndex];
      }
#else /* #if (STD_ON == SECOC_USE_META_DATA) */
      recvSecuredPduOffset = ((uint32)Queue->WriteBufferIndex * SECOC_GET_RX_SECURED_PDU_LEN(instId)) + Queue->StoredPduLength[Queue->WriteBufferIndex];
#endif /* #if (STD_ON == SECOC_USE_META_DATA) #else */
      Queue->WritePtr = SECOC_GET_RX_RECVSECURED_PDU_OFFSET_ADR(instId, recvSecuredPduOffset);
      bufReqRetVal = BUFREQ_OK;
      Queue->WriteRemainingBytes -= dataLen;
      if (Queue->WriteRemainingBytes == 0U)
      {
#if (STD_ON == SECOC_USE_META_DATA)
        if (SecOC_RxConfig[instId].UseMetaData == TRUE)
        {
          /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00212,1 */
          (void)EcuC_CopyMetaDataTypeFromPdu
          (
            SecOC_RxConfig[instId].PduIdForSecuredPduAtEcuC,
            &PduInfoLocal,
            &Queue->WritePtr[SECOC_GET_RX_SECURED_PDU_LEN(instId) - Queue->StoredPduLength[Queue->WriteBufferIndex]]
          );
        }
#endif /* #if (STD_ON == SECOC_USE_META_DATA) */
        ++Queue->Count;
        Queue->WriteBufferIndex++;
        Queue->WriteBufferIndex %= Queue->QueueSize;
        /* Shift the address to the beginning of the next slot */
#if (STD_ON == SECOC_USE_META_DATA)
        if (SecOC_RxConfig[instId].UseMetaData == TRUE)
        {
          recvSecuredPduOffset = (uint32)(Queue->WriteBufferIndex * ((uint32)SECOC_GET_RX_SECURED_PDU_LEN(instId) + SecOC_RxConfig[instId].MetaDataLength));
        }
        else
        {
          recvSecuredPduOffset = (uint32)Queue->WriteBufferIndex * SECOC_GET_RX_SECURED_PDU_LEN(instId);
        }
#else /* #if (STD_ON == SECOC_USE_META_DATA) */
        recvSecuredPduOffset = (uint32)Queue->WriteBufferIndex * SECOC_GET_RX_SECURED_PDU_LEN(instId);
#endif /* #if (STD_ON == SECOC_USE_META_DATA) #else */
        Queue->WritePtr = SECOC_GET_RX_RECVSECURED_PDU_OFFSET_ADR(instId, recvSecuredPduOffset);
        Queue->WriteInProgress = FALSE;
      }
    }
  }

  return bufReqRetVal;
}

FUNC(PduLengthType, SECOC_CODE) SecOC_Rx_GetQueueCapacity
(
  uint16 instId
)
{
  PduLengthType availableBufferSize = 0U;
  SecOC_RxQueueType* Queue = &SecOC_RxData[instId].Queue;

  if (Queue->WriteInProgress == TRUE)
  {
    availableBufferSize = Queue->WriteRemainingBytes;
  }
  else
  if (Queue->QueueSize > Queue->Count)
  {
    availableBufferSize = SECOC_GET_RX_SECURED_PDU_LEN(instId);
  }
  else
  {
    /* do nothing */
  }

  return availableBufferSize;
}

FUNC(void, SECOC_CODE) SecOC_Rx_DropPduFromQueue
(
  uint16 instId
)
{
  SecOC_RxQueueType* Queue = &SecOC_RxData[instId].Queue;
  uint32 recvSecuredPduOffset = 0U;

  if (Queue->WriteInProgress == TRUE)
  {
    Queue->WriteRemainingBytes = 0U;
#if (STD_ON == SECOC_USE_META_DATA)
    if (SecOC_RxConfig[instId].UseMetaData == TRUE)
    {
      recvSecuredPduOffset = (uint32)(Queue->WriteBufferIndex * ((uint32)SECOC_GET_RX_SECURED_PDU_LEN(instId) + SecOC_RxConfig[instId].MetaDataLength));
    }
    else
    {
      recvSecuredPduOffset = (uint32)Queue->WriteBufferIndex * SECOC_GET_RX_SECURED_PDU_LEN(instId);
    }
#else /* #if (STD_ON == SECOC_USE_META_DATA) */
    recvSecuredPduOffset = (uint32)Queue->WriteBufferIndex * SECOC_GET_RX_SECURED_PDU_LEN(instId);
#endif /* #if (STD_ON == SECOC_USE_META_DATA) #endif */
    Queue->WritePtr = SECOC_GET_RX_RECVSECURED_PDU_OFFSET_ADR(instId, recvSecuredPduOffset);
    Queue->StoredPduLength[Queue->WriteBufferIndex] = 0U;
    Queue->WriteInProgress = FALSE;
  }
  else
  {
    Queue->Count--;
    if (Queue->WriteBufferIndex > 0U)
    {
      Queue->WriteBufferIndex--;
    }
    else
    {
      Queue->WriteBufferIndex = Queue->QueueSize - 1U;
    }
    /* Remove currently stored secured PDU length */
    Queue->StoredPduLength[Queue->WriteBufferIndex] = 0U;
#if (STD_ON == SECOC_USE_META_DATA)
    if (SecOC_RxConfig[instId].UseMetaData == TRUE)
    {
      recvSecuredPduOffset = (uint32)(Queue->WriteBufferIndex * ((uint32)SECOC_GET_RX_SECURED_PDU_LEN(instId) + SecOC_RxConfig[instId].MetaDataLength));
    }
    else
    {
      recvSecuredPduOffset = (uint32)Queue->WriteBufferIndex * SECOC_GET_RX_SECURED_PDU_LEN(instId);
    }
#else /* #if (STD_ON == SECOC_USE_META_DATA) */
    recvSecuredPduOffset = (uint32)Queue->WriteBufferIndex * SECOC_GET_RX_SECURED_PDU_LEN(instId);
#endif /* #if (STD_ON == SECOC_USE_META_DATA) #else */
    Queue->WritePtr = SECOC_GET_RX_RECVSECURED_PDU_OFFSET_ADR(instId, recvSecuredPduOffset);
  }
}

#endif /* #if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON) */

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/*==================[internal function definitions]===============================================*/

/*==================[state machine states]========================================================*/

#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

/* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00016,1 */
static FUNC(void, SECOC_CODE) SecOC_Rx_StateIdle
(
  uint16 instId
)
{
  /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00085,1, SecOC.ASR430.Rx.SWS_SecOC_00203,1 */
  if (SECOC_RXEVENT_RXINDICATION == SecOC_RxData[instId].PduREvent)
  {
    Std_ReturnType operationResult = E_NOT_OK;
    /* Set the verification procedure status */
    /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00001,1 */
    SecOC_RxData[instId].ProcessingVerification = TRUE;

    SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
    /* the Pdu is now processed and the buffers in use */
    SecOC_RxData[instId].PduInProcess = TRUE;
    SecOC_RxData[instId].PduREvent = SECOC_RXEVENT_NONE;

    /* Read the next secured PDU from its queue */
#if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON)
    if (SECOC_QUEUE_INCOMING_PDU == SecOC_RxConfig[instId].ReceptionStrategy)
    {
      (void)SecOC_Rx_ReadPduFromQueue(instId,
                                      SecOC_RxData[instId].SecuredPdu.SduDataPtr,
                                      &SecOC_RxData[instId].ReceivedSecuredPdu.SduLength
                                      );
    }
#endif /* #if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON) */

    /* Check PDU content */
    operationResult = SecOC_Rx_CheckPduContent(instId);

    /* Check if the message link from the cryptographic Pdu is matching the corresponding
      part from the received authentic Pdu */
#if (SECOC_RX_USE_MESS_LINKER == STD_ON)
    /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00211,1 */
#if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_ON)
#if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION)
  if(SECOC_OVERRIDESTATUS_SKIP_UNTIL_NOTICE == SecOC_RxData[instId].VerifyStatusOverride)
#else /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) */
  if(
      (SECOC_OVERRIDE_SKIP_UNTIL_NOTICE == SecOC_RxData[instId].VerifyStatusOverride) ||
      (SECOC_OVERRIDE_SKIP_UNTIL_LIMIT  == SecOC_RxData[instId].VerifyStatusOverride)
    )
#endif /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) #else */
  {
    /* do nothing */
  }
  else
#endif /* #if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_ON) */    /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00211,1 */
  {
    operationResult |= SecOC_Rx_CheckMessageLink(instId);
  }
#endif /* #if (SECOC_RX_USE_MESS_LINKER == STD_ON) */

    SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();

    if (E_OK == operationResult)
    {
      /* Prepare secured PDU buffer (SduDataPtr and SduLength) */
      SecOC_Rx_PrepareSecuredPdu(instId);

#if (SECOC_RX_SHAPE_SEC_PDU == STD_ON)
      SecOC_Rx_CallShapeFunc(instId);
#endif

      SecOC_Rx_ExtractAuthenticDataLen(instId);

#if (STD_ON == SECOC_RX_USETP)
      operationResult = SecOC_Rx_CallUpperLayer(instId);

      if (E_OK == operationResult)
#endif /* #if (STD_ON == SECOC_RX_USETP) */

      {
#if (SECOC_SKIP_RX_PDU_VERIFICATION == STD_ON)
        if (TRUE == SecOC_RxConfig[instId].SkipVerification)
        {
          SecOC_RxData[instId].CsmVerificationResult = CRYPTO_E_VER_OK;
          SecOC_RxData[instId].State     = SECOC_RX_STATE_CHECKVERIFICATIONRESULT;
        }
        else
#endif /* #if (SECOC_SKIP_RX_PDU_VERIFICATION == STD_ON) */
        {
          SecOC_RxData[instId].State = SECOC_RX_STATE_CONSTRUCTDATATOAUTHENTICATOR;
        }

        SecOC_Rx_CheckStatusOverridePreVerify(instId);
      }
    }

    /* There was a failure, reset state machine */
    if (SecOC_RxData[instId].State == SECOC_RX_STATE_IDLE)
    {
#if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON)
      SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
      SecOC_RxData[instId].PduRIndicationForAuth   = SECOC_RXEVENT_RXINDICATION;
      SecOC_RxData[instId].PduRIndicationForCrypto = SECOC_RXEVENT_RXINDICATION;
      SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
#endif /* #if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON) */
      SecOC_Rx_ResetSm(instId, FALSE, FALSE);
    }
  }
}

static FUNC(void, SECOC_CODE) SecOC_Rx_StateConstructDataToAuthenticator
(
  uint16 instId
)
{
  if (
      (SECOC_RXEVENT_RXINDICATION == SecOC_RxData[instId].PduREvent        ) &&
      (SECOC_REPLACE_CURRENT_PDU  == SecOC_RxConfig[instId].ReceptionStrategy)
     )
  {
    SecOC_Rx_ResetSm(instId, TRUE, TRUE);
  }
  else
  {
    Std_ReturnType retVal = SECOC_E_NOT_OK;

    if(SecOC_RxData[instId].AuthAttempts == 0U)
    {
      /* !LINKSTO SecOC.ASR430.RxTx.SWS_SecOC_00011,1, SecOC.ASR430.Rx.SWS_SecOC_00046_1,1,
                  SecOC.ASR430.Rx.SWS_SecOC_00046_2,1, SecOC.ASR430.Rx.SWS_SecOC_00040,1,
                  SecOC.EB.RxTx.SWS_SecOC_00003,1*/

      /* DataID loop */
      {
        uint8 index;
        /* Deviation TASKING-1 */
        for (index = 0U; index < SECOC_DATAID_LENGTH; index++)
        {
          SecOC_RxData[instId].DataToAuthenticator[SECOC_DATAID_LENGTH - index - 1U] =
          (uint8) (SECOC_GET_RX_DATA_ID(instId) >> (index * 8U));
        }
      }
      /* !LINKSTO SecOC.ASR431.RxTx.SWS_SecOC_00311,1, SecOC.ASR431.RxTx.SWS_SecOC_00312,1 */
      /* Copy the Secured authentic part from the secured PDU */
#if (STD_ON == SECOC_PDU_SECURED_AREA)
      if (TRUE == SECOC_GET_RX_USE_SECURED_AREA(instId))
      {
        TS_MemCpy
        (
          &SecOC_RxData[instId].DataToAuthenticator[SECOC_DATAID_LENGTH],
          &SecOC_RxData[instId].SecuredPdu.SduDataPtr[SECOC_GET_RX_SECURED_AREA_OFFSET(instId)],
          SECOC_GET_RX_SECURED_AREA_LEN(instId)
        );
      }
      else
#endif /* #if (STD_ON == SECOC_PDU_SECURED_AREA) */
      {
        TS_MemCpy
        (
          &SecOC_RxData[instId].DataToAuthenticator[SECOC_DATAID_LENGTH],
          SecOC_RxData[instId].SecuredPdu.SduDataPtr,
          SecOC_RxData[instId].DataLength
        );
      }

      /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00235,1 */
      SecOC_RxData[instId].FVSyncAttempts = 0U;

      /* The data length is dynamic, therefore the start position of the FreshnessVerifyValue
       * changes also.
       */
#if ((STD_ON == SECOC_RX_AUTH_DATA_FRESHNESS) && (SECOC_QUERY_FRESHNESS_VALUE != SECOC_FRESHNESS_RTE))
      if (0U != SECOC_GET_RX_FRESHNESS_LEN(instId))
      {
#endif /* #if ((STD_ON == SECOC_RX_AUTH_DATA_FRESHNESS) && (SECOC_QUERY_FRESHNESS_VALUE != SECOC_FRESHNESS_RTE)) */

#if (STD_ON == SECOC_PDU_SECURED_AREA)
        if (TRUE == SECOC_GET_RX_USE_SECURED_AREA(instId))
        {
          SecOC_RxData[instId].FreshnessVerifyValue =
            &(SecOC_RxData[instId].DataToAuthenticator)[
                                                          SECOC_DATAID_LENGTH               +
                                                          SECOC_GET_RX_SECURED_AREA_LEN(instId)
                                                         ];
        }
        else
#endif /* #if (STD_ON == SECOC_PDU_SECURED_AREA) */
        {
          SecOC_RxData[instId].FreshnessVerifyValue =
            &(SecOC_RxData[instId].DataToAuthenticator)[
                                                          SECOC_DATAID_LENGTH               +
                                                          SecOC_RxData[instId].DataLength
                                                         ];
        }
#if ((STD_ON == SECOC_RX_AUTH_DATA_FRESHNESS) && (SECOC_QUERY_FRESHNESS_VALUE != SECOC_FRESHNESS_RTE))
      }
      else
      {
        SecOC_RxData[instId].FreshnessVerifyValue = NULL_PTR;
      }
#endif /* #if ((STD_ON == SECOC_RX_AUTH_DATA_FRESHNESS) && (SECOC_QUERY_FRESHNESS_VALUE != SECOC_FRESHNESS_RTE)) */
    }

#if (SECOC_QUERY_FRESHNESS_VALUE != SECOC_FRESHNESS_NONE)
    retVal = SecOC_Rx_CallFreshnessFunc(instId);
#else
    retVal = SECOC_E_OK;
#endif /* #if (SECOC_QUERY_FRESHNESS_VALUE != SECOC_FRESHNESS_NONE) */

    SecOC_Rx_CheckFreshnessFuncResult(instId, retVal);
  }
}

static FUNC(void, SECOC_CODE) SecOC_Rx_StateVerification
(
  uint16 instId
)
{
  if (
      (SECOC_RXEVENT_RXINDICATION == SecOC_RxData[instId].PduREvent        ) &&
      (SECOC_REPLACE_CURRENT_PDU  == SecOC_RxConfig[instId].ReceptionStrategy)
     )
  {
    SecOC_Rx_ResetSm(instId, TRUE, TRUE);
  }
  else
  {
    Std_ReturnType retVal = E_NOT_OK;
#if ((STD_ON == SECOC_RX_USE_SIGNATUREVERIFY) || (STD_ON == SECOC_RX_USE_MACVERIFY))
    uint32 dataLength;

    /* Length of the authentic data */
#if (STD_ON == SECOC_PDU_SECURED_AREA)
    if (TRUE == SECOC_GET_RX_USE_SECURED_AREA(instId))
    {
      dataLength =
      (
       (uint32)SECOC_GET_RX_SECURED_AREA_LEN(instId)                    +
       (uint32)SECOC_DATAID_LENGTH                                      +
       SECOC_REQUIREDBYTES(SECOC_GET_RX_FRESHNESS_LEN(instId))
      );
    }
    else
#endif /* #if (STD_ON == SECOC_PDU_SECURED_AREA) */
    {
      dataLength =
      (
       (uint32)SecOC_RxData[instId].DataLength                        +
       (uint32)SECOC_DATAID_LENGTH                                      +
       SECOC_REQUIREDBYTES(SECOC_GET_RX_FRESHNESS_LEN(instId))
      );
    }
#endif /* #if ((STD_ON == SECOC_RX_USE_SIGNATUREVERIFY) || (STD_ON == SECOC_RX_USE_MACVERIFY)) */

#if (SECOC_RX_CSM_ASYNC == STD_ON)
    if (TRUE == SecOC_RxConfig[instId].UseCsmAsync)
    {
      /* Set the next execution state */
      SecOC_RxData[instId].State = SECOC_RX_STATE_WAITFORVERIFICATIONCALLBACK;
      /* Prepare the Csm callback event flag */
      SecOC_RxData[instId].CsmEvent = SECOC_RXEVENT_NONE;
    }
    else
    {
      /* Set the next execution state */
      SecOC_RxData[instId].State = SECOC_RX_STATE_CHECKVERIFICATIONRESULT;
    }
#else /* #if (SECOC_RX_CSM_ASYNC == STD_ON) */
    /* Set the next execution state */
    SecOC_RxData[instId].State = SECOC_RX_STATE_CHECKVERIFICATIONRESULT;
#endif /* #if (SECOC_RX_CSM_ASYNC == STD_ON) #else */

    /* Set the verification procedure status */
    /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00001,1 */
    SecOC_RxData[instId].ProcessingVerification = TRUE;

    switch(SecOC_RxConfig[instId].CsmFuncType)
    {
      case SECOC_RX_MACVERIFY_FUNC_TYPE:
      {
#if (STD_ON == SECOC_RX_USE_MACVERIFY)
        /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00040,1, SecOC.ASR430.Rx.SWS_SecOC_00047,2, SecOC.ASR430.Rx.SWS_SecOC_00079,1 */
        retVal = Csm_MacVerify
                 (
                  (Csm_ConfigIdType)SECOC_RX_CSM_JOB_ID(instId),
                  CRYPTO_OPERATIONMODE_SINGLECALL,
                  SecOC_RxData[instId].DataToAuthenticator,
                  dataLength,
                  SecOC_RxData[instId].Authenticator,
                  /* !LINKSTO SecOC.ASR430.SWS_SecOC_EB_RxTx_00003,1 */
#if (SECOC_AUTH_LENGTH_BITS == STD_ON)
                  SECOC_GET_RX_AUTHINFOTX_LEN(instId),
#else /* #if (SECOC_AUTH_LENGTH_BITS == STD_ON) */
                  SECOC_REQUIREDBYTES(SECOC_GET_RX_AUTHINFOTX_LEN(instId)),
#endif /* #if (SECOC_AUTH_LENGTH_BITS == STD_ON) #else */
                  &SecOC_RxData[instId].CsmVerificationResult
                 );
#endif /* #if (STD_ON == SECOC_RX_USE_MACVERIFY) */
      }
      break;
      case SECOC_RX_SIGNATUREVERIFY_FUNC_TYPE:
      {
#if (STD_ON == SECOC_RX_USE_SIGNATUREVERIFY)
        /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00040,1, SecOC.ASR430.Rx.SWS_SecOC_00047,2, SecOC.ASR430.Rx.SWS_SecOC_00079,1 */
        retVal = Csm_SignatureVerify
                 (
                  (Csm_ConfigIdType)SECOC_RX_CSM_JOB_ID(instId),
                  CRYPTO_OPERATIONMODE_SINGLECALL,
                  SecOC_RxData[instId].DataToAuthenticator,
                  dataLength,
                  SecOC_RxData[instId].Authenticator,
                  SECOC_REQUIREDBYTES(SECOC_GET_RX_AUTHINFOTX_LEN(instId)),
                  &SecOC_RxData[instId].CsmVerificationResult
                 );
#endif /* #if (STD_ON == SECOC_RX_USE_SIGNATUREVERIFY) */
      }
      break;
      /* CHECK: NOPARSE */
      default:
      {
        /* Nothing to do. */
      }
      break;
      /* CHECK: PARSE */
    }

#if (SECOC_VERIFICATION_STATUS_PROP_EB == SECOC_VERIFICATION_STATUS_PROP_ENABLED)
    SecOC_RxData[instId].CsmVerificationReturn = retVal;
#endif /* #if (SECOC_VERIFICATION_STATUS_PROP_EB == SECOC_VERIFICATION_STATUS_PROP_ENABLED) */

    /* !LINKSTO SecOC.ASR430.Tx.SWS_SecOC_00151,1 */
    /* Deviation TASKING-1 */
    if (E_OK != retVal)
    {
#if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_ON)
      boolean pass = FALSE;

#if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION)
      /* Check if the verification status can be overridden to pass */
      if (SECOC_OVERRIDESTATUS_PASS_MSG_NUMBER == SecOC_RxData[instId].VerifyStatusOverride)
#else /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) */
      if ((SECOC_OVERRIDE_PASS_UNTIL_LIMIT  == SecOC_RxData[instId].VerifyStatusOverride) ||
          (SECOC_OVERRIDE_PASS_UNTIL_NOTICE == SecOC_RxData[instId].VerifyStatusOverride)
         )
#endif /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) #else */
      {
        /* Try to override the verification status */
        SecOC_Rx_RenewStatusOverride(instId, &pass);
      }

      if (TRUE == pass)
      {
        SecOC_RxData[instId].CsmVerificationResult = CRYPTO_E_VER_OK;

        /* Set the next execution state as the verification status was successfully overridden */
        SecOC_RxData[instId].State = SECOC_RX_STATE_CHECKVERIFICATIONRESULT;
      }
      else
#endif /* #if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_ON) */
      {
        /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00238,1 */
        SecOC_Rx_CheckForCsmRetry(instId);
      }
    }
  }
}

#if (SECOC_RX_CSM_ASYNC == STD_ON)
static FUNC(void, SECOC_CODE) SecOC_Rx_StateWaitForVerificationCallback
(
  uint16 instId
)
{
  /* Set the verification procedure status */
  /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00001,1 */
  SecOC_RxData[instId].ProcessingVerification = TRUE;

  if (SECOC_RXEVENT_VERCALLBACK_OK == SecOC_RxData[instId].CsmEvent)
  {
    /* Clear verification result */
    SecOC_RxData[instId].CsmEvent = SECOC_RXEVENT_NONE;

    /* Trigger a transition from state Wait to VerificationResult */
    SecOC_RxData[instId].State = SECOC_RX_STATE_CHECKVERIFICATIONRESULT;
  }
  else
  if (SECOC_RXEVENT_VERCALLBACK_NOT_OK == SecOC_RxData[instId].CsmEvent)
  {
    /* Clear verification result */
    SecOC_RxData[instId].CsmEvent = SECOC_RXEVENT_NONE;

#if (SECOC_IGNORE_VER_RESULT == STD_ON)
    /* Set the verification result to a negative one */
    SecOC_RxData[instId].CsmVerificationResult = CRYPTO_E_VER_NOT_OK;

    /* Trigger a transition to the next state even if the verification result is a negative one */
    SecOC_RxData[instId].State = SECOC_RX_STATE_CHECKVERIFICATIONRESULT;
#else /* #if (SECOC_IGNORE_VER_RESULT == STD_ON) */
    {
#if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_ON)
      boolean pass = FALSE;

#if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION)
      /* Check if the verification status can be overridden to pass */
      if (SECOC_OVERRIDESTATUS_PASS_MSG_NUMBER == SecOC_RxData[instId].VerifyStatusOverride)
#else /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) */
      if ((SECOC_OVERRIDE_PASS_UNTIL_LIMIT  == SecOC_RxData[instId].VerifyStatusOverride) ||
          (SECOC_OVERRIDE_PASS_UNTIL_NOTICE == SecOC_RxData[instId].VerifyStatusOverride)
         )
#endif /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) #else */
      {
        /* Try to override the verification status */
        SecOC_Rx_RenewStatusOverride(instId, &pass);
      }

      /* Check if the verification status was overridden */
      if (TRUE == pass)
      {
        SecOC_RxData[instId].CsmVerificationResult = CRYPTO_E_VER_OK;

        /* Proceed with the execution */
        SecOC_RxData[instId].State = SECOC_RX_STATE_CHECKVERIFICATIONRESULT;
      }
      else
#endif /* #if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_ON) */
      {
        /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00238,1 */
        SecOC_Rx_CheckForCsmRetry(instId);
      }
    }
#endif /* #if (SECOC_IGNORE_VER_RESULT == STD_ON) #else */
  }
  else
  {
    /* Wait for the Csm callback */
    /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00002,2 */
    SecOC_RxData[instId].ProcessingVerification = FALSE;
  }
}
#endif /* #if (SECOC_RX_CSM_ASYNC == STD_ON) */

static FUNC(void, SECOC_CODE) SecOC_Rx_StateCheckVerificationResult
(
  uint16 instId
)
{
  if (
      (SECOC_RXEVENT_RXINDICATION == SecOC_RxData[instId].PduREvent        ) &&
      (SECOC_REPLACE_CURRENT_PDU  == SecOC_RxConfig[instId].ReceptionStrategy)
     )
  {
    SecOC_Rx_ResetSm(instId, TRUE, TRUE);
  }
  else
  {
    boolean passPdu;

#if (SECOC_IGNORE_FVM_FAILURES == STD_ON)
    /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00027,1 */
    if ((SecOC_RxData[instId].VerificationResult == SECOC_AUTHENTICATIONBUILDFAILURE) ||
        (SecOC_RxData[instId].VerificationResult == SECOC_FRESHNESSFAILURE)
       )
    {
      passPdu = TRUE;
    }
    else
#endif /* #if (SECOC_IGNORE_FVM_FAILURES == STD_ON) */
    {
#if (SECOC_VERIFICATION_STATUS_PROP_EB == SECOC_VERIFICATION_STATUS_PROP_ENABLED)
      SecOC_RxData[instId].CsmVerificationReturn = E_OK;
#endif /* #if (SECOC_VERIFICATION_STATUS_PROP_EB == SECOC_VERIFICATION_STATUS_PROP_ENABLED) */
      if (SecOC_RxData[instId].CsmVerificationResult == CRYPTO_E_VER_OK)
      {
        /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00242,1 */
        SecOC_RxData[instId].VerificationResult = (SecOC_RxData[instId].RenewedVerStatus == FALSE)?SECOC_VERIFICATIONSUCCESS:SecOC_RxData[instId].VerificationResult;
        passPdu = TRUE;
      }
      else
      {
        SecOC_RxData[instId].VerificationResult = (SecOC_RxData[instId].RenewedVerStatus == FALSE)?SECOC_VERIFICATIONFAILURE:SecOC_RxData[instId].VerificationResult;
        passPdu = FALSE;

#if ((STD_ON == SECOC_ENABLE_SEC_EVENT_REPORTING) && (STD_ON == SECOC_RX_USE_MACVERIFY))
        /* Csm did not verify. Report to IdsM. */
        SecOC_Rx_ReportSecurityEventWithContextData(SECOC_SEV_MAC_VERIFICATION_FAILED, instId);
#endif /* #if ((STD_ON == SECOC_ENABLE_SEC_EVENT_REPORTING) && (STD_ON == SECOC_RX_USE_MACVERIFY)) */
      }
    }

#if (SECOC_IGNORE_VER_RESULT == STD_ON)
    if (SecOC_RxData[instId].RenewedVerStatus == FALSE)
    {
      /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00081,1 */
      passPdu = TRUE;
    }
#endif /* #if (SECOC_IGNORE_VER_RESULT == STD_ON) */

    /* Check that the verification status was not renewed already */
    if (SecOC_RxData[instId].RenewedVerStatus == FALSE)
    {
      SecOC_Rx_RenewStatusOverride(instId, &passPdu);
    }

    if (TRUE == passPdu)
    {
      /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00048_2,1, SecOC.ASR430.Rx.SWS_SecOC_00048_1,1 */
#if ((SECOC_VERIFICATION_STATUS_PROP_NONE != SECOC_VERIFICATION_STATUS_PROP_ENABLED) || (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP))
      /* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00272,1 */
      SecOC_Rx_PropagateVerificationStatus(instId);
#endif /* #if ((SECOC_VERIFICATION_STATUS_PROP_NONE != SECOC_VERIFICATION_STATUS_PROP_ENABLED) || (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP)) */

      SecOC_RxData[instId].ProcessingVerification = TRUE;
      SecOC_RxData[instId].State = SECOC_RX_STATE_BROADCASTPDU;
    }
    else
    {
      /* SECOC_OVERRIDESTATUS_CANCEL and SECOC_OVERRIDE_CANCEL are equal to 0x02U
       * and the value is used instead of the macros in order to simplify the code
       */
      /* Data authentication failed. -> Try again if Max attempts not reached */
      if (
          (SecOC_RxConfig[instId].MaxFVSyncAttempts >  SecOC_RxData[instId].FVSyncAttempts) &&
          (0x02U                                                == SecOC_RxData[instId].VerifyStatusOverride      ) &&
          (0x00U                                                != SECOC_GET_RX_FRESHNESS_LEN(instId)             )
         )
      {
#if ((SECOC_VERIFICATION_STATUS_PROP_NONE != SECOC_VERIFICATION_STATUS_PROP_ENABLED) || (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP))
#if (STD_OFF == SECOC_PROPAGATEONLYFINALVERIFICATIONSTATUS)
        /* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00272,1 */
        SecOC_Rx_PropagateVerificationStatus(instId);
#endif /* #if (STD_OFF == SECOC_PROPAGATEONLYFINALVERIFICATIONSTATUS) */
#endif /* #if ((SECOC_VERIFICATION_STATUS_PROP_NONE != SECOC_VERIFICATION_STATUS_PROP_ENABLED) || (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP)) */

        SecOC_RxData[instId].ProcessingVerification = TRUE;
        SecOC_RxData[instId].State = SECOC_RX_STATE_RETRYTOOBTAINFRESHNESS;
      }
      else
      {
        boolean continueExec = FALSE;
        /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00048_2,1, SecOC.ASR430.Rx.SWS_SecOC_00048_1,1 */
#if ((SECOC_VERIFICATION_STATUS_PROP_NONE != SECOC_VERIFICATION_STATUS_PROP_ENABLED) || (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP))
        /* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00272,1 */
        SecOC_Rx_PropagateVerificationStatus(instId);
#endif /* #if ((SECOC_VERIFICATION_STATUS_PROP_NONE != SECOC_VERIFICATION_STATUS_PROP_ENABLED) || (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP)) */

#if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON)
        SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();

        if (TRUE == SecOC_RxConfig[instId].UseSecPduCollection)
        {
          if ((SECOC_RXEVENT_RXINDICATION == SecOC_RxData[instId].PduRIndicationForAuth) ||
              (SECOC_RXEVENT_RXINDICATION == SecOC_RxData[instId].PduRIndicationForCrypto) ||
              (SECOC_RXEVENT_RXINDICATION == SecOC_RxData[instId].PduREvent)
             )
          {
            SecOC_RxData[instId].PduREvent = SECOC_RXEVENT_RXINDICATION;
            SecOC_RxData[instId].PduRIndicationForAuth   = SECOC_RXEVENT_NONE;
            SecOC_RxData[instId].PduRIndicationForCrypto = SECOC_RXEVENT_NONE;
            continueExec = TRUE;
          }
          else
          {
            /* Verification of the secured PDU failed, prepare the state machine to restart the procedure
             * immediately after receiving new data for the authentic or cryptographic PDU
             */
            /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00208,1 */
            SecOC_RxData[instId].PduRIndicationForAuth   = SECOC_RXEVENT_RXINDICATION;
            SecOC_RxData[instId].PduRIndicationForCrypto = SECOC_RXEVENT_RXINDICATION;
          }
        }

        SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
#endif /* #if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON) */

        /* Drop Message */
        /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00087_2,1 */
        /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00241,1 */
        SecOC_Rx_ResetSm(instId, continueExec, TRUE);
      }
    }
  }
}

static FUNC(void, SECOC_CODE) SecOC_Rx_StateBroadcastPdu
(
  uint16 instId
)
{
  /* CHECK: NOPARSE */
  /* It is not possible to stop here the state machine execution */
  if (
      (SECOC_RXEVENT_RXINDICATION == SecOC_RxData[instId].PduREvent        ) &&
      (SECOC_REPLACE_CURRENT_PDU  == SecOC_RxConfig[instId].ReceptionStrategy)
     )
  {
    SecOC_Rx_ResetSm(instId, TRUE, TRUE);
  }
  /* CHECK: PARSE */
  else
  {
    PduInfoType SecOC_RxPduInfo;

    SecOC_RxPduInfo.SduLength  = SecOC_RxData[instId].DataLength;
    SecOC_RxPduInfo.SduDataPtr = SecOC_RxData[instId].SecuredPdu.SduDataPtr;

#if (STD_ON == SECOC_USE_META_DATA)
    if (SecOC_RxConfig[instId].UseMetaData == TRUE)
    {
      /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00212,1 */
      (void)EcuC_CopyMetaDataTypeToPdu(SecOC_RxConfig[instId].PduIdForAuthPduAtEcuC, &SecOC_RxPduInfo, SecOC_RxData[instId].SecuredPduMetaData);
      TS_MemBZero(SecOC_RxData[instId].SecuredPduMetaData, SecOC_RxConfig[instId].MetaDataLength);
    }
#endif /* #if (STD_ON == SECOC_USE_META_DATA) */

    /* Pass Data to 'upper layer' */
    /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00040,1, SecOC.ASR430.Rx.SWS_SecOC_00050,1, SecOC.ASR430.Rx.SWS_SecOC_00080,1 */
    /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00086,2, SecOC.ASR430.Rx.SWS_SecOC_00175,1, SecOC.ASR430.Rx.SWS_SecOC_00137,2    */
    /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00088,2, SecOC.ASR20-11.Rx.SWS_SecOC_00267,1 */
#if (STD_ON == SECOC_RX_USETP)
    if (TRUE == SecOC_RxConfig[instId].UseTp)
    {
      if(
          BUFREQ_OK ==
          PduR_SecOCTpCopyRxData(
                                  SECOC_GET_RX_AUTH_PDU_ID_AT_PDUR(instId),
                                  &SecOC_RxPduInfo,
                                  &SecOC_RxPduInfo.SduLength
                                )
        )
      {
        PduR_SecOCTpRxIndication(SECOC_GET_RX_AUTH_PDU_ID_AT_PDUR(instId), E_OK);
      }
      else
      {
        PduR_SecOCTpRxIndication(SECOC_GET_RX_AUTH_PDU_ID_AT_PDUR(instId), E_NOT_OK);
      }
    }
    else
#endif /* #if (STD_ON == SECOC_RX_USETP) */
    {
      /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00081,1 */
      PduR_SecOCRxIndication(SECOC_GET_RX_AUTH_PDU_ID_AT_PDUR(instId), &SecOC_RxPduInfo);
    }

#if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON)
    /* Clear the internal buffers where the authentic and cryptographic PDUs are stored */
    if (TRUE == SecOC_RxConfig[instId].UseSecPduCollection)
    {
      SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();

      /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00207,1 */
      TS_MemBZero(SecOC_RxData[instId].ReceivedAuthPdu.SduDataPtr, SECOC_GET_RX_AUTH_PDU_LEN(instId));
      TS_MemBZero(SecOC_RxData[instId].CryptoPdu.SduDataPtr, SECOC_GET_RX_CRYPTO_PDU_LEN(instId));

      SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
    }
#endif /* #if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON) */

    /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00087_1,2 */
    SecOC_Rx_ResetSm(instId, FALSE, FALSE);
  }
}

static FUNC(void, SECOC_CODE) SecOC_Rx_StateRetryToObtainFreshness
(
  uint16 instId
)
{
  /* CHECK: NOPARSE */
  if (
      (SECOC_RXEVENT_RXINDICATION == SecOC_RxData[instId].PduREvent        ) &&
      (SECOC_REPLACE_CURRENT_PDU  == SecOC_RxConfig[instId].ReceptionStrategy)
     )
  {
    SecOC_Rx_ResetSm(instId, TRUE, TRUE);
  }
  /* CHECK: PARSE */
  else
  {
    Std_ReturnType retVal = SECOC_E_NOT_OK;
#if (SECOC_QUERY_FRESHNESS_VALUE != SECOC_FRESHNESS_NONE)
    uint32 freshnessValueLength = SECOC_GET_RX_FRESHNESS_LEN(instId);

    /* The freshness interface is called with sync attempts + 1 because
     * the sync attempts counter will be incremented only if the call return value is SECOC_E_OK.
     * It shall be avoided, that the FVSyncAttempts counter is incremented more than
     * once in case the freshness function returns SECOC_E_BUSY.
     */

    /* !LINKSTO SecOC.ASR430.SWS_SecOC_00220,1 */
    switch(SecOC_RxConfig[instId].GetRxFreshnessFuncType)
    {
#if (STD_ON == SECOC_RX_FRESHNESS)
      case SECOC_GET_RX_FRESHNESS_FUNC_TYPE:
      {

        /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00245,3 */
        /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00247,3 */
        retVal = SecOC_Rx_Get_Freshness
                 (
                   instId,
                   SECOC_GET_RX_FRESHNESS_ID(instId),
                   &SecOC_RxData[instId].SecuredPdu.SduDataPtr[SecOC_RxData[instId].DataLength],
                   SECOC_GET_RX_FRESHNESSTX_LEN(instId),
                   (SecOC_RxData[instId].FVSyncAttempts + 1U),
                   SecOC_RxData[instId].FreshnessVerifyValue,
                   &freshnessValueLength
                 );
      }
      break;
#endif /* #if (STD_ON == SECOC_RX_FRESHNESS) */
#if (STD_ON == SECOC_RX_AUTH_DATA_FRESHNESS)
      case SECOC_GET_RX_FRESHNESS_AUTHDATA_FUNC_TYPE:
      {
        /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00219,1 */
        /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00244,2 */
        /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00246,2 */
        retVal = SecOC_Rx_Get_Freshness_AuthData
                 (
                   instId,
                   &SecOC_RxData[instId].SecuredPdu.SduDataPtr[SecOC_RxData[instId].DataLength],
                   SECOC_GET_RX_FRESHNESSTX_LEN(instId),
                   SecOC_RxData[instId].AuthDataFreshnessValueBuffer,
                   SecOC_RxConfig[instId].AuthDataFreshnessValueLength,
                   (SecOC_RxData[instId].FVSyncAttempts + 1U),
                   SecOC_RxData[instId].FreshnessVerifyValue,
                   &freshnessValueLength
                 );
      }
      break;
#endif /* #if (STD_ON == SECOC_RX_AUTH_DATA_FRESHNESS) */
      /* CHECK: NOPARSE */
      default:
      {
        /* Nothing to do. */
      }
      break;
      /* CHECK: PARSE */
    }
#endif /* #if (SECOC_QUERY_FRESHNESS_VALUE != SECOC_FRESHNESS_NONE) */

#if (SECOC_VERIFICATION_STATUS_PROP_EB == SECOC_VERIFICATION_STATUS_PROP_ENABLED)
    SecOC_RxData[instId].CsmVerificationReturn = retVal;
#endif /* #if (SECOC_VERIFICATION_STATUS_PROP_EB == SECOC_VERIFICATION_STATUS_PROP_ENABLED) */

    /* Deviation TASKING-2 */
    if (SECOC_E_BUSY == retVal)
    {
      if (SecOC_RxConfig[instId].MaxAuthAttempts > SecOC_RxData[instId].AuthAttempts)
      {
        /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00236,1 */
        /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00236_BUSY,1 */
        SecOC_RxData[instId].AuthAttempts++;

        /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00238,1 */
        /* try again, no change on SecOC_RxData[instId].State */
      }
      else
      {
        /* Report authentication status */
        /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00240,1 */
        SecOC_RxData[instId].VerificationResult = SECOC_AUTHENTICATIONBUILDFAILURE;
#if (SECOC_IGNORE_FVM_FAILURES == STD_ON)
        SecOC_RxData[instId].AuthAttempts = 0U;
        SecOC_RxData[instId].ProcessingVerification = TRUE;
        /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00027,1 */
        SecOC_RxData[instId].State = SECOC_RX_STATE_CHECKVERIFICATIONRESULT;
#else /* #if (SECOC_IGNORE_FVM_FAILURES == STD_ON) */
#if ((SECOC_VERIFICATION_STATUS_PROP_NONE != SECOC_VERIFICATION_STATUS_PROP_ENABLED) || (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP))
        /* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00272,1 */
        SecOC_Rx_PropagateVerificationStatus(instId);
#endif /* #if ((SECOC_VERIFICATION_STATUS_PROP_NONE != SECOC_VERIFICATION_STATUS_PROP_ENABLED) || (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP)) */
        SecOC_Rx_ResetSm(instId, FALSE, TRUE);
#endif /* #if (SECOC_IGNORE_FVM_FAILURES == STD_ON) */
      }
    }
    /* Deviation TASKING-2 */
    else
    if (SECOC_E_OK == retVal)
    {
      SecOC_RxData[instId].State = SECOC_RX_STATE_VERIFICATION;
      /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00239,1 */
      SecOC_RxData[instId].FVSyncAttempts++;

      /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00239,1 */
      SecOC_RxData[instId].AuthAttempts = 0U;
#if (SECOC_RX_SYNC_PDU_PROCESSING == STD_ON)
      if (TRUE == SecOC_RxConfig[instId].UseSyncProcessing)
      {
        SecOC_RxData[instId].ProcessingVerification = TRUE;
      }
#endif /* #if (SECOC_RX_SYNC_PDU_PROCESSING == STD_ON) */
    }
    else
    {
      /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00248_NOT_OK,1 */
      /* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00256,1 */
      SecOC_RxData[instId].VerificationResult = SECOC_FRESHNESSFAILURE;
#if (SECOC_IGNORE_FVM_FAILURES == STD_ON)
      SecOC_RxData[instId].State = SECOC_RX_STATE_CHECKVERIFICATIONRESULT;
      SecOC_RxData[instId].AuthAttempts = 0U;
      SecOC_RxData[instId].ProcessingVerification = TRUE;
#else /* #if (SECOC_IGNORE_FVM_FAILURES == STD_ON) */
#if ((SECOC_VERIFICATION_STATUS_PROP_NONE != SECOC_VERIFICATION_STATUS_PROP_ENABLED) || (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP))
      /* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00272,1 */
      SecOC_Rx_PropagateVerificationStatus(instId);
#endif /* #if ((SECOC_VERIFICATION_STATUS_PROP_NONE != SECOC_VERIFICATION_STATUS_PROP_ENABLED) || (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP)) */
      /* Drop Message */
      /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00087_2,1 */
      /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00240,1 */
      SecOC_Rx_ResetSm(instId, FALSE, TRUE);
#endif /* #if (SECOC_IGNORE_FVM_FAILURES == STD_ON) */
    }
  }
}
#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/*==================[helper functions]============================================================*/

#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

static FUNC(void, SECOC_CODE) SecOC_Rx_ResetSm
(
  uint16  instId,
  boolean continueExec,
  boolean notifyUpperLayer
)
{
  SecOC_RxData[instId].State = SECOC_RX_STATE_IDLE;
  /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00235,1 */
  SecOC_RxData[instId].AuthAttempts = 0U;
  SecOC_RxData[instId].FVSyncAttempts = 0U;
  SecOC_RxData[instId].VerificationResult = SECOC_NO_VERIFICATION;
  SecOC_RxData[instId].CsmVerificationResult = CRYPTO_E_VER_NOT_OK;
#if (SECOC_VERIFICATION_STATUS_PROP_ENABLED == SECOC_VERIFICATION_STATUS_PROP_EB)
  SecOC_RxData[instId].CsmVerificationReturn = E_NOT_OK;
#endif /* #if (SECOC_VERIFICATION_STATUS_PROP_ENABLED == SECOC_VERIFICATION_STATUS_PROP_EB) */

  if (TRUE == SecOC_RxData[instId].RenewedVerStatus)
  {
    SecOC_Rx_CheckStatusOverridePostVerify(instId);

    SecOC_RxData[instId].RenewedVerStatus = FALSE;
  }

  /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00213,1 */
#if (STD_ON == SECOC_RX_USETP)
  if ((TRUE == SecOC_RxConfig[instId].UseTp) && (TRUE == notifyUpperLayer))
  {
    PduR_SecOCTpRxIndication(SECOC_GET_RX_AUTH_PDU_ID_AT_PDUR(instId), E_NOT_OK);
  }
#else /* #if (STD_ON == SECOC_RX_USETP) */
  SECOC_PARAM_UNUSED(notifyUpperLayer);
#endif /* #if (STD_ON == SECOC_RX_USETP) #else */

  SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();

  if (TRUE == continueExec)
  {
    SecOC_RxData[instId].ProcessingVerification = TRUE;
  }
  else
  {
    SecOC_RxData[instId].ProcessingVerification = FALSE;

#if (STD_ON == SECOC_RX_USE_SAME_BUFFER)
    if (SecOC_RxData[instId].BufferUsed != NULL_PTR)
    {
      *SecOC_RxData[instId].BufferUsed = FALSE;
    }
#endif /* #if (STD_ON == SECOC_RX_USE_SAME_BUFFER) */
  }

#if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON)
  if (SECOC_QUEUE_INCOMING_PDU == SecOC_RxConfig[instId].ReceptionStrategy)
  {
    if (SECOC_IS_RX_RECEIVED_SECURED_PDU_BUFFER_EMPTY(instId) == FALSE)
    {
      SecOC_RxData[instId].PduREvent = SECOC_RXEVENT_RXINDICATION;
    }
  }
#endif /* #if (SECOC_QUEUE_INCOMING_PDU_ENABLED == STD_ON) */

  SecOC_RxData[instId].PduInProcess = FALSE;

  SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
}

static FUNC(void, SECOC_CODE) SecOC_Rx_CheckForCsmRetry
(
  uint16 instId
)
{

#if (SECOC_RX_SYNC_PDU_PROCESSING == STD_ON)
  if (FALSE == SecOC_RxConfig[instId].UseSyncProcessing)
#endif /* #if (SECOC_RX_SYNC_PDU_PROCESSING == STD_ON) */
  {
    /* Set the verification procedure status */
    /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00002,2 */
    SecOC_RxData[instId].ProcessingVerification = FALSE;
  }

#if (SECOC_VERIFICATION_STATUS_PROP_EB == SECOC_VERIFICATION_STATUS_PROP_ENABLED)
  /* EB custom error notification required by FvM to identify that the MAC service was rejected */
  SecOC_RxData[instId].VerificationResult = SECOC_MACSERVICEFAILURE;
#else /* #if (SECOC_VERIFICATION_STATUS_PROP_EB == SECOC_VERIFICATION_STATUS_PROP_ENABLED) */
  /* AUTOSAR compliant error notification */
  SecOC_RxData[instId].VerificationResult = SECOC_VERIFICATIONFAILURE;
#endif /* #if (SECOC_VERIFICATION_STATUS_PROP_EB == SECOC_VERIFICATION_STATUS_PROP_ENABLED) #else */

  if (
      SecOC_RxConfig[instId].MaxFVSyncAttempts >
      SecOC_RxData[instId].FVSyncAttempts
     )
  {
    /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00237,1 */
    SecOC_RxData[instId].FVSyncAttempts++;

#if ((SECOC_VERIFICATION_STATUS_PROP_NONE != SECOC_VERIFICATION_STATUS_PROP_ENABLED) || (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP))
#if (STD_OFF == SECOC_PROPAGATEONLYFINALVERIFICATIONSTATUS)
    /* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00272,1 */
    SecOC_Rx_PropagateVerificationStatus(instId);
#endif /* #if (STD_OFF == SECOC_PROPAGATEONLYFINALVERIFICATIONSTATUS) */
#endif /* #if ((SECOC_VERIFICATION_STATUS_PROP_NONE != SECOC_VERIFICATION_STATUS_PROP_ENABLED) || (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP)) */

    /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00121,2 */
    /* try again */
    SecOC_RxData[instId].State = SECOC_RX_STATE_VERIFICATION;
  }
  else
  {
    /* Failed to verify. Report to IdsM */
#if ((STD_ON == SECOC_ENABLE_SEC_EVENT_REPORTING) && (STD_ON == SECOC_RX_USE_MACVERIFY))
        SecOC_Rx_ReportSecurityEventWithContextData(SECOC_SEV_MAC_VERIFICATION_FAILED, instId);
#endif /* #if ((STD_ON == SECOC_ENABLE_SEC_EVENT_REPORTING) && (STD_ON == SECOC_RX_USE_MACVERIFY)) */

#if ((SECOC_VERIFICATION_STATUS_PROP_NONE != SECOC_VERIFICATION_STATUS_PROP_ENABLED) || (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP))
    /* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00272,1 */
    SecOC_Rx_PropagateVerificationStatus(instId);
#endif /* #if ((SECOC_VERIFICATION_STATUS_PROP_NONE != SECOC_VERIFICATION_STATUS_PROP_ENABLED) || (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP)) */
    SecOC_Rx_ResetSm(instId, FALSE, TRUE);
  }
}

static FUNC(void, SECOC_CODE) SecOC_Rx_PrepareSecuredPdu
(
  uint16 instId
)
{
  SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
#if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON)
  /* Check if SecuredPduCollection is configured for this PDU */
  if (SecOC_RxConfig[instId].UseSecPduCollection == TRUE)
  {
    /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00206,1 */
    /* Reconstruct the secured PDU from the received authentic and cryptographic PDUs */
    TS_MemCpy
    (
      SecOC_RxData[instId].SecuredPdu.SduDataPtr,
      SecOC_RxData[instId].ReceivedAuthPdu.SduDataPtr,
      SecOC_RxData[instId].ReceivedAuthPdu.SduLength
    );

    TS_MemCpy
    (
      &SecOC_RxData[instId].SecuredPdu.SduDataPtr[SecOC_RxData[instId].ReceivedAuthPdu.SduLength],
      SecOC_RxData[instId].CryptoPdu.SduDataPtr,
      SECOC_GET_RX_CRYPTO_PDU_LEN(instId)
    );

    SecOC_RxData[instId].SecuredPdu.SduLength = SecOC_RxData[instId].ReceivedAuthPdu.SduLength +
                                                SECOC_GET_RX_CRYPTO_PDU_LEN(instId);
  }
  else
#endif /* #if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON) */
  {
    if (SECOC_REPLACE_CURRENT_PDU == SecOC_RxConfig[instId].ReceptionStrategy)
    {
      TS_MemCpy
      (
        SecOC_RxData[instId].SecuredPdu.SduDataPtr,
        SecOC_RxData[instId].ReceivedSecuredPdu.SduDataPtr,
        SecOC_RxData[instId].ReceivedSecuredPdu.SduLength
      );
    }

    SecOC_RxData[instId].SecuredPdu.SduLength = SecOC_RxData[instId].ReceivedSecuredPdu.SduLength;
  }
  SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
}

#if (STD_ON == SECOC_RX_USETP)
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_CallUpperLayer
(
  uint16 instId
)
{
  Std_ReturnType retVal = E_NOT_OK;
  PduLengthType bufferSizeUpperLayer = 0U;
  BufReq_ReturnType upperBufReqRetVal = BUFREQ_E_NOT_OK;

  if (TRUE == SecOC_RxConfig[instId].UseTp)
  {
    /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00082,2 */
    upperBufReqRetVal = PduR_SecOCStartOfReception
                                          (
                                            SECOC_GET_RX_AUTH_PDU_ID_AT_PDUR(instId),
#if (STD_OFF == SECOC_ASR403_API)
                                            NULL_PTR,
#endif /* #if (STD_OFF == SECOC_ASR403_API) */
                                            SecOC_RxData[instId].DataLength,
                                            &bufferSizeUpperLayer
                                          );

  }
  else
  {
    upperBufReqRetVal = BUFREQ_OK;
  }

  if (BUFREQ_OK == upperBufReqRetVal)
  {
    retVal = E_OK;
  }

  return retVal;
}
#endif /* #if (STD_ON == SECOC_RX_USETP) */

#if (SECOC_RX_USE_MESS_LINKER == STD_ON)
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_CheckMessageLink
(
  uint16 instId
)
{
  P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) bufferAData = SecOC_RxData[instId].ReceivedAuthPdu.SduDataPtr;
          uint32                             bufferABitPos = SecOC_RxConfig[instId].MessageLinkPos;
  P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) bufferBData = SecOC_RxData[instId].CryptoPdu.SduDataPtr;
          uint32                             bufferBBitPos = SECOC_RX_AUTHENTICATION_INFO_LEN(instId);
          uint32                             bitLength = SecOC_RxConfig[instId].MessageLinkLength;

  uint32 bufferAIndex = bufferABitPos / 8U;
  uint32 bufferBIndex = bufferBBitPos / 8U;

  uint8 bufferAShift = bufferABitPos % 8U;
  uint8 bufferBShift = bufferBBitPos % 8U;

  uint32 intBitLength = bitLength;
  uint32 compareIndex = 0U;
  uint8 nextAIndex = 0U;
  uint8 nextBIndex = 0U;

  boolean isEqual = TRUE;

  if (0U != bitLength)
  {
    if (bufferAShift != 0U)
    {
      nextAIndex = 1U;
    }

    if (bufferBShift != 0U)
    {
      nextBIndex = 1U;
    }

    while((isEqual == TRUE) && (((compareIndex + 1U) * 8U) <= intBitLength))
    {
      if
      (
        (uint8)(
                (bufferAData[bufferAIndex + compareIndex             ] <<       bufferAShift ) |
                (bufferAData[bufferAIndex + compareIndex + nextAIndex] >> (8U - bufferAShift))
              ) !=
        (uint8)(
                (bufferBData[bufferBIndex + compareIndex             ] <<       bufferBShift ) |
                (bufferBData[bufferBIndex + compareIndex + nextBIndex] >> (8U - bufferBShift))
              )
      )
      {
        isEqual = FALSE;
      }

      compareIndex++;
    }

    intBitLength -= (compareIndex * 8U);

    if((intBitLength > 0U) && (isEqual == TRUE))
    {
      uint8 bufferALastCompareByte;
      uint8 bufferBLastCompareByte;

      uint8 i;

      bufferALastCompareByte = (uint8)(bufferAData[bufferAIndex + compareIndex] << bufferAShift);

      if((intBitLength + bufferAShift) > 8U)
      {
        bufferALastCompareByte |=
          (uint8)(bufferAData[bufferAIndex + compareIndex + 1U] >> (8U - bufferAShift));
      }

      bufferBLastCompareByte = (uint8)(bufferBData[bufferBIndex + compareIndex] << bufferBShift);

      if((intBitLength + bufferBShift) > 8U)
      {
        bufferBLastCompareByte |=
          (uint8)(bufferBData[bufferBIndex + compareIndex + 1U] >> (8U - bufferBShift));
      }

      for(i = 0U; i < intBitLength; i++)
      {
        if(((bufferALastCompareByte << i) & 0x80U) != ((bufferBLastCompareByte << i) & 0x80U))
        {
          isEqual = FALSE;
        }
      }
    }

  }
  return (isEqual == TRUE) ? E_OK : E_NOT_OK;
}
#endif /* #if (SECOC_RX_USE_MESS_LINKER == STD_ON) */

static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_CheckPduContent
(
  uint16 instId
)
{
  Std_ReturnType retVal = E_NOT_OK;

#if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON)
  if (SecOC_RxConfig[instId].UseSecPduCollection == TRUE)
  {
    retVal = SecOC_Rx_CheckSecPduCollectionContent(instId);
  }
  else
#endif /* #if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON) */
  {
    retVal = SecOC_Rx_CheckSecPduContent(instId);
  }

  return retVal;
}

static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_CheckSecPduContent
(
  uint16 instId
)
{
  Std_ReturnType retVal = E_NOT_OK;
  const uint32 authInfoLen = SECOC_REQUIREDBYTES(SECOC_RX_AUTHENTICATION_INFO_LEN(instId));

#if (SECOC_RX_USE_SEC_PDU_HEADER == STD_ON)
  /* !LINKSTO SecOC.ASR20-11.RxTx.SWS_SecOC_00261,1 */
  if (SecOC_RxConfig[instId].SecuredPduHeaderLength != 0U)
  {
    PduLengthType index = 0U;
    PduLengthType pduLength = 0U;

    for (index = 0U; index < SecOC_RxConfig[instId].SecuredPduHeaderLength; index++)
    {
      pduLength |= (PduLengthType)SecOC_RxData[instId].ReceivedSecuredPdu.SduDataPtr[index] << (index * 8U);
    }

    /* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00263,1 */
    if (pduLength <= (SecOC_RxData[instId].ReceivedSecuredPdu.SduLength - authInfoLen - SecOC_RxConfig[instId].SecuredPduHeaderLength))
    {
#if (STD_ON == SECOC_PDU_SECURED_AREA)
      /* !LINKSTO SecOC.ASR431.Rx.SWS_SecOC_00314,1 */
      if (SECOC_RX_SECAREA_MIN_AUTHDATALEN(instId) <= pduLength)
#endif /* #if (STD_ON == SECOC_PDU_SECURED_AREA) */
      {
        retVal = E_OK;
      }
    }
  }
  else
#endif /* #if (SECOC_RX_USE_SEC_PDU_HEADER == STD_ON) */
  {
    if (SecOC_RxData[instId].ReceivedSecuredPdu.SduLength > authInfoLen)
    {
#if (STD_ON == SECOC_PDU_SECURED_AREA)
      /* !LINKSTO SecOC.ASR431.Rx.SWS_SecOC_00314,1 */
      if (SECOC_RX_SECAREA_MIN_AUTHDATALEN(instId) <= (SecOC_RxData[instId].ReceivedSecuredPdu.SduLength - authInfoLen))
#endif /* #if (STD_ON == SECOC_PDU_SECURED_AREA) */
      {
        retVal = E_OK;
      }
    }
  }

  return retVal;
}

#if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON)
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_CheckSecPduCollectionContent
(
  uint16 instId
)
{
  Std_ReturnType retVal = E_NOT_OK;

#if (SECOC_RX_USE_SEC_PDU_HEADER == STD_OFF) && (SECOC_RX_USE_MESS_LINKER == STD_OFF) && (SECOC_PDU_SECURED_AREA == STD_OFF)
  SECOC_PARAM_UNUSED(instId);
#endif /* #if (SECOC_RX_USE_SEC_PDU_HEADER == STD_OFF) && (SECOC_RX_USE_MESS_LINKER == STD_OFF) && (SECOC_PDU_SECURED_AREA == STD_OFF) */

#if (SECOC_RX_USE_SEC_PDU_HEADER == STD_ON)
  /* !LINKSTO SecOC.ASR20-11.RxTx.SWS_SecOC_00261,1 */
  if (SecOC_RxConfig[instId].SecuredPduHeaderLength != 0U)
  {
    PduLengthType index = 0U;
    PduLengthType pduLength = 0U;

    for (index = 0U; index < SecOC_RxConfig[instId].SecuredPduHeaderLength; index++)
    {
      pduLength |= (PduLengthType)SecOC_RxData[instId].ReceivedAuthPdu.SduDataPtr[index] << (index * 8U);
    }

    /* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00263,1 */
    if (pduLength <= SECOC_GET_RX_AUTH_PDU_LEN(instId))
    {
#if (SECOC_RX_USE_MESS_LINKER == STD_ON)
      if (pduLength >= SECOC_REQUIREDBYTES(SECOC_RX_MSGLINK_MIN_AUTHDATALEN(instId)))
#endif /* #if (SECOC_RX_USE_MESS_LINKER == STD_ON) */
      {
#if (STD_ON == SECOC_PDU_SECURED_AREA)
        /* !LINKSTO SecOC.ASR431.Rx.SWS_SecOC_00314,1 */
        if (SECOC_RX_SECAREA_MIN_AUTHDATALEN(instId) <= pduLength)
#endif /* #if (STD_ON == SECOC_PDU_SECURED_AREA) */
        {
          retVal = E_OK;
        }
      }
    }
  }
  else
#endif /* #if (SECOC_RX_USE_SEC_PDU_HEADER == STD_ON) */
  {
#if (SECOC_RX_USE_MESS_LINKER == STD_ON)
    if (SecOC_RxData[instId].ReceivedAuthPdu.SduLength >= SECOC_REQUIREDBYTES(SECOC_RX_MSGLINK_MIN_AUTHDATALEN(instId)))
#endif /* #if (SECOC_RX_USE_MESS_LINKER == STD_ON) */
    {
#if (STD_ON == SECOC_PDU_SECURED_AREA)
      /* !LINKSTO SecOC.ASR431.Rx.SWS_SecOC_00314,1 */
      if (SECOC_RX_SECAREA_MIN_AUTHDATALEN(instId) <= SecOC_RxData[instId].ReceivedAuthPdu.SduLength)
#endif /* #if (STD_ON == SECOC_PDU_SECURED_AREA) */
      {
        retVal = E_OK;
      }
    }
  }

  return retVal;
}
#endif /* #if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON) */

#if (SECOC_RX_SHAPE_SEC_PDU == STD_ON)
static FUNC(void, SECOC_CODE) SecOC_Rx_CallShapeFunc
(
  uint16 instId
)
{
  if (TRUE == SecOC_RxConfig[instId].UseShapeSecuredPdu)
  {
    PduLengthType secPduLen = SECOC_GET_RX_SECURED_PDU_LEN(instId);
    uint32 authInfo;
    PduIdType pduIdx;

#if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON)
    if (TRUE == SecOC_RxConfig[instId].UseSecPduCollection)
    {
      pduIdx = SecOC_RxConfig[instId].PduIdForReceivedAuthPduAtSecOC;
      authInfo = SECOC_GET_RX_CRYPTO_PDU_LEN(instId);
    }
    else
#endif /* #if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON) */
    {
      pduIdx = SecOC_RxConfig[instId].PduIdForSecuredPduAtSecOC;
      authInfo = SECOC_REQUIREDBYTES(SECOC_RX_AUTHENTICATION_INFO_LEN(instId));
    }

    /* Remove the padding from the secured PDU */
    /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00009,2 */
    SECOC_RX_SHAPE_FUNC
    (
      pduIdx,
      SecOC_RxData[instId].SecuredPdu.SduDataPtr,
      &SecOC_RxData[instId].SecuredPdu.SduLength,
      &secPduLen,
      authInfo
    );

    SecOC_RxData[instId].SecuredPdu.SduLength = secPduLen;
  }
}
#endif /* #if (SECOC_RX_SHAPE_SEC_PDU == STD_ON) */

static FUNC(void, SECOC_CODE) SecOC_Rx_ExtractAuthenticDataLen
(
  uint16 instId
)
{
  SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
#if (SECOC_RX_USE_SEC_PDU_HEADER == STD_ON)
  if (SecOC_RxConfig[instId].SecuredPduHeaderLength != 0U)
  {
    /* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00259,1, SecOC.ASR20-11.Rx.SWS_SecOC_00264,1 */
    SecOC_Rx_ExtractSecuredPduHeader(instId);
  }
  else
#endif /* #if (SECOC_RX_USE_SEC_PDU_HEADER == STD_ON) */
  {
    /* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00257,1, SecOC.ASR20-11.Rx.SWS_SecOC_00258,1 */
#if (SECOC_RX_USE_MESS_LINKER == STD_ON)
    if (SecOC_RxConfig[instId].MessageLinkLength != 0U)
    {
      /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00004,1 */
      SecOC_RxData[instId].DataLength = SecOC_RxData[instId].SecuredPdu.SduLength -
                                          SECOC_GET_RX_CRYPTO_PDU_LEN(instId);
    }
    else
#endif /* #if (SECOC_RX_USE_MESS_LINKER == STD_ON) */
    {
      /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00004,1 */
      SecOC_RxData[instId].DataLength = SecOC_RxData[instId].SecuredPdu.SduLength -
                                          (uint16)SECOC_REQUIREDBYTES
                                            (SECOC_RX_AUTHENTICATION_INFO_LEN(instId));
    }
  }
  SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
}

#if (SECOC_RX_USE_SEC_PDU_HEADER == STD_ON)
static FUNC(void, SECOC_CODE) SecOC_Rx_ExtractSecuredPduHeader
(
  uint16 instId
)
{
  uint8 index;

  for (index = 0U; index < SecOC_RxConfig[instId].SecuredPduHeaderLength; index++)
  {
    SecOC_RxData[instId].DataLength |= (PduLengthType)SecOC_RxData[instId].SecuredPdu.SduDataPtr[index] << (index * 8U);
  }

  TS_MemCpy
  (
    SecOC_RxData[instId].SecuredPdu.SduDataPtr,
    &SecOC_RxData[instId].SecuredPdu.SduDataPtr[SecOC_RxConfig[instId].SecuredPduHeaderLength],
    SecOC_RxData[instId].DataLength
  );

#if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON)
  if (SecOC_RxConfig[instId].UseSecPduCollection == TRUE)
  {
    TS_MemCpy
    (
      &SecOC_RxData[instId].SecuredPdu.SduDataPtr[SecOC_RxData[instId].DataLength],
      &SecOC_RxData[instId].SecuredPdu.SduDataPtr[SecOC_RxData[instId].ReceivedAuthPdu.SduLength],
      SECOC_GET_RX_CRYPTO_PDU_LEN(instId)
    );
  }
  else
#endif /* #if (SECOC_RX_USE_SECURED_PDU_COL == STD_ON) */
  {
    TS_MemCpy
    (
      &SecOC_RxData[instId].SecuredPdu.SduDataPtr[SecOC_RxData[instId].DataLength],
      &SecOC_RxData[instId].SecuredPdu.SduDataPtr[SECOC_GET_RX_AUTH_PDU_LEN(instId) + SecOC_RxConfig[instId].SecuredPduHeaderLength],
      SECOC_REQUIREDBYTES (SECOC_RX_AUTHENTICATION_INFO_LEN(instId))
    );
  }
}
#endif /* #if (SECOC_RX_USE_SEC_PDU_HEADER == STD_ON) */

#if ((STD_ON == SECOC_RX_AUTH_DATA_FRESHNESS) && (SECOC_QUERY_FRESHNESS_VALUE != SECOC_FRESHNESS_NONE))
static FUNC(void, SECOC_CODE) SecOC_Rx_ExtractAuthDataFreshnessValue
(
  uint16 instId
)
{
  if (NULL_PTR != SecOC_RxData[instId].AuthDataFreshnessValueBuffer)
  {
    TS_MemCpy
    (
      SecOC_RxData[instId].AuthDataFreshnessValueBuffer,
      &SecOC_RxData[instId].SecuredPdu.SduDataPtr
        [SecOC_RxConfig[instId].AuthDataFreshnessValueStartPosition / 8U],
      SECOC_REQUIREDBYTES
      (
        (uint32)SecOC_RxConfig[instId].AuthDataFreshnessValueLength +
        ((uint32)SecOC_RxConfig[instId].AuthDataFreshnessValueStartPosition % 8U)
      )
    );

    if (0U != (SecOC_RxConfig[instId].AuthDataFreshnessValueStartPosition % 8U))
    {
      SecOC_Rx_ShiftLeft
      (
        SecOC_RxData[instId].AuthDataFreshnessValueBuffer,
        (
          (uint32)SecOC_RxConfig[instId].AuthDataFreshnessValueLength +
          ((uint32)SecOC_RxConfig[instId].AuthDataFreshnessValueStartPosition % 8U)
        ),
        (uint8) (SecOC_RxConfig[instId].AuthDataFreshnessValueStartPosition % 8U)
      );
    }
  }
}
#endif /* #if (STD_ON == SECOC_RX_AUTH_DATA_FRESHNESS) */

#if (SECOC_QUERY_FRESHNESS_VALUE != SECOC_FRESHNESS_NONE)
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_CallFreshnessFunc
(
  uint16 instId
)
{
  Std_ReturnType retVal = E_NOT_OK;

#if (STD_ON == SECOC_RX_AUTH_DATA_FRESHNESS)
  if (
      (0U != SECOC_GET_RX_FRESHNESS_LEN(instId)                 ) ||
      (0U != SecOC_RxConfig[instId].AuthDataFreshnessValueLength)
     )
#else /* #if (STD_ON == SECOC_RX_AUTH_DATA_FRESHNESS) */
  if (0U != SECOC_GET_RX_FRESHNESS_LEN(instId))
#endif /* #if (STD_ON == SECOC_RX_AUTH_DATA_FRESHNESS) #else */
  {
    uint32 freshnessValueLength = SECOC_GET_RX_FRESHNESS_LEN(instId);

#if (STD_ON == SECOC_RX_AUTH_DATA_FRESHNESS)
    /* Extract the secured PDU part that will be sent to the freshness SWC */
    SecOC_Rx_ExtractAuthDataFreshnessValue(instId);
#endif /* #if (STD_ON == SECOC_RX_AUTH_DATA_FRESHNESS) */
    /* !LINKSTO SecOC.ASR430.SWS_SecOC_00220,1 */
    switch(SecOC_RxConfig[instId].GetRxFreshnessFuncType)
    {
#if (STD_ON == SECOC_RX_FRESHNESS)
      case SECOC_GET_RX_FRESHNESS_FUNC_TYPE:
      {
        /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00245,3 */
        /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00247,3 */
        retVal = SecOC_Rx_Get_Freshness
                 (
                   instId,
                   SECOC_GET_RX_FRESHNESS_ID(instId),
                   &SecOC_RxData[instId].SecuredPdu.SduDataPtr[SecOC_RxData[instId].DataLength],
                   SECOC_GET_RX_FRESHNESSTX_LEN(instId),
                   SecOC_RxData[instId].FVSyncAttempts,
                   SecOC_RxData[instId].FreshnessVerifyValue,
                   &freshnessValueLength
                 );
      }
      break;
#endif /* #if (STD_ON == SECOC_RX_FRESHNESS) */
#if (STD_ON == SECOC_RX_AUTH_DATA_FRESHNESS)
      case SECOC_GET_RX_FRESHNESS_AUTHDATA_FUNC_TYPE:
      {
        /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00219,1 */
        /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00244,2 */
        /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00246,2 */
        retVal = SecOC_Rx_Get_Freshness_AuthData
                 (
                   instId,
                   &SecOC_RxData[instId].SecuredPdu.SduDataPtr[SecOC_RxData[instId].DataLength],
                   SECOC_GET_RX_FRESHNESSTX_LEN(instId),
                   SecOC_RxData[instId].AuthDataFreshnessValueBuffer,
                   SecOC_RxConfig[instId].AuthDataFreshnessValueLength,
                   SecOC_RxData[instId].FVSyncAttempts,
                   SecOC_RxData[instId].FreshnessVerifyValue,
                   &freshnessValueLength
                 );
      }
      break;
#endif /* #if (STD_ON == SECOC_RX_AUTH_DATA_FRESHNESS) */
      /* CHECK: NOPARSE */
      default:
      {
        /* Nothing to do. */
      }
      break;
      /* CHECK: PARSE */
    }
  }
  else
  {
    retVal = SECOC_E_OK;
  }

  return retVal;
}
#endif /* #if (SECOC_QUERY_FRESHNESS_VALUE != SECOC_FRESHNESS_NONE) */

static FUNC(void, SECOC_CODE) SecOC_Rx_CheckFreshnessFuncResult
(
  uint16         instId,
  Std_ReturnType retVal
)
{
#if (SECOC_VERIFICATION_STATUS_PROP_EB == SECOC_VERIFICATION_STATUS_PROP_ENABLED)
  SecOC_RxData[instId].CsmVerificationReturn = retVal;
#endif /* #if (SECOC_VERIFICATION_STATUS_PROP_EB == SECOC_VERIFICATION_STATUS_PROP_ENABLED) */

  if (SECOC_E_BUSY == retVal)
  {
#if (SECOC_RX_SYNC_PDU_PROCESSING == STD_ON)
    if (TRUE == SecOC_RxConfig[instId].UseSyncProcessing)
    {
      /* Set the verification procedure status */
      /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00002,2 */
      SecOC_RxData[instId].ProcessingVerification = TRUE;
    }
    else
#endif /* #if (SECOC_RX_SYNC_PDU_PROCESSING == STD_ON) */
    {
      /* Set the verification procedure status */
      /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00002,2 */
      SecOC_RxData[instId].ProcessingVerification = FALSE;
    }

    if (SecOC_RxConfig[instId].MaxAuthAttempts > SecOC_RxData[instId].AuthAttempts)
    {
      /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00236,1 */
      /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00236_BUSY,1 */
      SecOC_RxData[instId].AuthAttempts++;

      /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00121,2 */
      /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00238,1 */
      /* try again */
      SecOC_RxData[instId].State = SECOC_RX_STATE_CONSTRUCTDATATOAUTHENTICATOR;
    }
    else
    {
      /* Report authentication status */
      /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00240,1 */
      SecOC_RxData[instId].VerificationResult = SECOC_AUTHENTICATIONBUILDFAILURE;

      /* Failed to get Freshness Value. Report to IdsM */
#if (SECOC_ENABLE_SEC_EVENT_REPORTING == STD_ON)
      /* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00273,1 */
      IdsM_SetSecurityEvent(SECOC_SEV_FRESHNESS_NOT_AVAILABLE);
#endif /* #if (SECOC_ENABLE_SEC_EVENT_REPORTING == STD_ON) */

#if (SECOC_IGNORE_FVM_FAILURES == STD_ON)
      SecOC_RxData[instId].AuthAttempts = 0U;
      SecOC_RxData[instId].ProcessingVerification = TRUE;
      SecOC_RxData[instId].State = SECOC_RX_STATE_CHECKVERIFICATIONRESULT;
#else /* #if (SECOC_IGNORE_FVM_FAILURES == STD_ON) */
#if ((SECOC_VERIFICATION_STATUS_PROP_NONE != SECOC_VERIFICATION_STATUS_PROP_ENABLED) || (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP))
      SecOC_Rx_PropagateVerificationStatus(instId);
#endif /* #if ((SECOC_VERIFICATION_STATUS_PROP_NONE != SECOC_VERIFICATION_STATUS_PROP_ENABLED) || (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP)) */
      SecOC_Rx_ResetSm(instId, FALSE, TRUE);
#endif /* #if (SECOC_IGNORE_FVM_FAILURES == STD_ON) */
    }
  }
  else
  {
    if (SECOC_E_OK == retVal)
    {
      const uint32 freshnessRemainingBitsLen = (uint32)SECOC_GET_RX_FRESHNESSTX_LEN(instId) % 8U;
      /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00235,1 */
      SecOC_RxData[instId].AuthAttempts = 0U;

      /* authenticator */
      /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00040,1 */
      TS_MemCpy
      (
        SecOC_RxData[instId].Authenticator,
        &SecOC_RxData[instId].SecuredPdu.SduDataPtr
          [SecOC_RxData[instId].DataLength + ((PduLengthType)SECOC_GET_RX_FRESHNESSTX_LEN(instId) / 8U)],
        SECOC_REQUIREDBYTES(((uint32) SECOC_GET_RX_AUTHINFOTX_LEN(instId) + freshnessRemainingBitsLen))
      );

      if (0U !=freshnessRemainingBitsLen)
      {
        /* the length passed to the Shift function must be the length of the authenticator,
         * but additional with the offset,
         * which is caused by a bit length of the FreshnessValueTxLength
         */
        SecOC_Rx_ShiftLeft
        (
          SecOC_RxData[instId].Authenticator,
          (uint32)SECOC_GET_RX_AUTHINFOTX_LEN(instId) + freshnessRemainingBitsLen,
          (uint8) freshnessRemainingBitsLen
        );
      }
      /* Set the verification procedure status */
      SecOC_RxData[instId].ProcessingVerification = TRUE;

      SecOC_RxData[instId].State = SECOC_RX_STATE_VERIFICATION;
    }
    else
    {
      /* Report authentication status */
      /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00248_NOT_OK,1 */
      /* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00256,1 */
      SecOC_RxData[instId].VerificationResult = SECOC_FRESHNESSFAILURE;

      /* Failed to get Freshness Value. Report to IdsM */
#if (SECOC_ENABLE_SEC_EVENT_REPORTING == STD_ON)
      /* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00273,1 */
      IdsM_SetSecurityEvent(SECOC_SEV_FRESHNESS_NOT_AVAILABLE);
#endif /* #if (SECOC_ENABLE_SEC_EVENT_REPORTING == STD_ON) */

#if (SECOC_IGNORE_FVM_FAILURES == STD_ON)
      SecOC_RxData[instId].AuthAttempts = 0U;
      SecOC_RxData[instId].ProcessingVerification = TRUE;
      SecOC_RxData[instId].State = SECOC_RX_STATE_CHECKVERIFICATIONRESULT;
#else /* #if (SECOC_IGNORE_FVM_FAILURES == STD_ON) */
#if ((SECOC_VERIFICATION_STATUS_PROP_NONE != SECOC_VERIFICATION_STATUS_PROP_ENABLED) || (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP))
      /* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00272,1 */
      SecOC_Rx_PropagateVerificationStatus(instId);
#endif /* #if ((SECOC_VERIFICATION_STATUS_PROP_NONE != SECOC_VERIFICATION_STATUS_PROP_ENABLED) || (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP)) */
      /* Set the verification procedure status */
      /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00002,2 */
      SecOC_RxData[instId].ProcessingVerification = FALSE;
      /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00240,1 */
      SecOC_Rx_ResetSm(instId, FALSE, TRUE);
#endif /* #if (SECOC_IGNORE_FVM_FAILURES == STD_ON) */
    }
  }
}

static FUNC(void, SECOC_CODE) SecOC_Rx_CheckStatusOverridePreVerify
(
  uint16  instId
)
{
  switch(SecOC_RxData[instId].VerifyStatusOverride)
  {
#if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION)
    /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00040,1, SecOC.ASR430.Rx.SWS_SecOC_00042,1 */
    /* !LINKSTO SecOC.ASR431.Rx.SWS_SecOC_00265,1 */
    case SECOC_OVERRIDESTATUS_SKIP_UNTIL_NOTICE:
    {
      SecOC_RxData[instId].CsmVerificationResult = CRYPTO_E_VER_OK;
      SecOC_RxData[instId].State     = SECOC_RX_STATE_CHECKVERIFICATIONRESULT;
    }
    break;
#else /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) */
    case SECOC_OVERRIDE_DROP_UNTIL_LIMIT:
    case SECOC_OVERRIDE_DROP_UNTIL_NOTICE:
    {
      boolean pass = TRUE;
      SecOC_Rx_RenewStatusOverride(instId, &pass);
      /* CHECK: NOPARSE
       * The else part of this if can't be reached as long as SecOC_Rx_RenewStatusOverride
       * is succesfully executed
       */
      if (FALSE == pass)
      {
        SecOC_RxData[instId].CsmVerificationResult = CRYPTO_E_VER_NOT_OK;
        SecOC_RxData[instId].State     = SECOC_RX_STATE_CHECKVERIFICATIONRESULT;
      }
      /* CHECK: PARSE */
    }
    break;
#if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_ON)
    case SECOC_OVERRIDE_SKIP_UNTIL_NOTICE:
    case SECOC_OVERRIDE_SKIP_UNTIL_LIMIT:
    {
      boolean pass = FALSE;
      SecOC_Rx_RenewStatusOverride(instId, &pass);
      /* CHECK: NOPARSE
       * The else part of this if can't be reached as long as SecOC_Rx_RenewStatusOverride
       * is succesfully executed
       */
      if(TRUE == pass)
      {
        SecOC_RxData[instId].CsmVerificationResult = CRYPTO_E_VER_OK;
        SecOC_RxData[instId].State     = SECOC_RX_STATE_CHECKVERIFICATIONRESULT;
      }
      /* CHECK: PARSE */
    }
    break;
#endif /* #if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_ON) */
#endif /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) #else */
    /* CHECK: NOPARSE */
    default:
    {
      /* Do nothing */
    }
    break;
    /* CHECK: PARSE */
  }
}

static FUNC(void, SECOC_CODE) SecOC_Rx_RenewStatusOverride
(
  uint16 instId,
  P2VAR(boolean, AUTOMATIC, SECOC_APPL_DATA) passData
)
#if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION)
{
  uint16 pduIdx;

  /* Check if the overrideStatus option is enabled */
  if (SECOC_OVERRIDESTATUS_CANCEL != SecOC_RxData[instId].VerifyStatusOverride)
  {
    *passData = FALSE;

    /* Check overrideStatus is set to fail for a given number of messages */
    if (SECOC_OVERRIDESTATUS_FAIL_MSG_NUMBER == SecOC_RxData[instId].VerifyStatusOverride)
    {
      /* This will indicate that the status was already renewed once for the current secured PDU */
      SecOC_RxData[instId].RenewedVerStatus = TRUE;

      /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00005,1 */
      /* Check all freshness ID from the configuration */
      /* Deviation TASKING-1 */
      for (pduIdx = 0U; pduIdx < SECOC_NUMBER_RX_PDUS; pduIdx++)
      {
        /* Check if the freshness ID for the given PDU is equal with other PDUs freshness ID */
        if (SECOC_GET_RX_FRESHNESS_ID(instId) == SECOC_GET_RX_FRESHNESS_ID(pduIdx))
        {
          SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
          /* Decrease the number of messages for which the verification result will be overridden */
          SecOC_RxData[pduIdx].NumMsgToOverride--;
          SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
        }
      }
    }
#if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_ON)
    /* Check overrideStatus is set to pass for a given number of messages */
    else
    if (SECOC_OVERRIDESTATUS_PASS_MSG_NUMBER == SecOC_RxData[instId].VerifyStatusOverride)
    {
      /* This will indicate that the status was already renewed once for the current secured PDU */
      SecOC_RxData[instId].RenewedVerStatus = TRUE;

      /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00005,1 */
      /* Check all freshness ID from the configuration */
      /* Deviation TASKING-1 */
      for (pduIdx = 0U; pduIdx < SECOC_NUMBER_RX_PDUS; pduIdx++)
      {
        /* Check if the freshness ID for the given PDU is equal with other PDUs freshness ID */
        if (SECOC_GET_RX_FRESHNESS_ID(instId) == SECOC_GET_RX_FRESHNESS_ID(pduIdx))
        {
          SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
          /* Decrease the number of messages for which the verification result will be overridden */
          SecOC_RxData[pduIdx].NumMsgToOverride--;
          SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
        }
      }

      SecOC_RxData[instId].VerificationResult = SECOC_VERIFICATIONFAILURE;

      *passData = TRUE;
    }
    else
    if (SECOC_OVERRIDESTATUS_SKIP_UNTIL_NOTICE == SecOC_RxData[instId].VerifyStatusOverride)
    {
      /* This will indicate that the status was already renewed once for the current secured PDU */
      SecOC_RxData[instId].RenewedVerStatus = TRUE;

      SecOC_RxData[instId].VerificationResult = SECOC_NO_VERIFICATION;

      *passData = TRUE;
    }
    else
    {
      /* Do nothing for SECOC_OVERRIDESTATUS_FAIL as the passData is already set to FALSE */
    }
#endif /* #if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_ON) */
  }
}
#else /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) */
{
  uint16 pduIdx;

  /* Check if the overrideStatus option is enabled */
  if (SECOC_OVERRIDE_CANCEL != SecOC_RxData[instId].VerifyStatusOverride)
  {
    switch(SecOC_RxData[instId].VerifyStatusOverride)
    {
      case SECOC_OVERRIDE_DROP_UNTIL_LIMIT:
      {
        SecOC_RxData[instId].RenewedVerStatus = TRUE;

        /* Check all freshness/Data ID from the configuration */
        /* Deviation TASKING-1 */
        for (pduIdx = 0U; pduIdx < SECOC_NUMBER_RX_PDUS; pduIdx++)
        {
          /* Check if the Data ID for the given PDU is equal with other PDUs data ID */
          if (SECOC_GET_RX_ID(instId) == SECOC_GET_RX_ID(pduIdx))
          {
            SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
            /* Decrease the number of messages for which the verification result will be overridden */
            SecOC_RxData[pduIdx].NumMsgToOverride--;
            SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
          }
        }

        SecOC_RxData[instId].VerificationResult = SECOC_NO_VERIFICATION;

        *passData = FALSE;
      }
      break;

      case SECOC_OVERRIDE_DROP_UNTIL_NOTICE:
      {
        /* This will indicate that the status was already renewed once for the current secured PDU */
        SecOC_RxData[instId].RenewedVerStatus = TRUE;

        SecOC_RxData[instId].VerificationResult = SECOC_NO_VERIFICATION;

        *passData = FALSE;
      }
      break;

#if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_ON)
      case SECOC_OVERRIDE_PASS_UNTIL_LIMIT:
      {
        /* This will indicate that the status was already renewed once for the current secured PDU */
        SecOC_RxData[instId].RenewedVerStatus = TRUE;

        /* Check all freshness/Data ID from the configuration */
        for (pduIdx = 0U; pduIdx < SECOC_NUMBER_RX_PDUS; pduIdx++)
        {
          /* Check if the Data ID for the given PDU is equal with other PDUs data ID */
          if (SECOC_GET_RX_ID(instId) == SECOC_GET_RX_ID(pduIdx))
          {
            SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
            /* Decrease the number of messages for which the verification result will be overridden */
            SecOC_RxData[pduIdx].NumMsgToOverride--;
            SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
          }
        }

        SecOC_RxData[instId].VerificationResult = SECOC_VERIFICATIONFAILURE_OVERWRITTEN;

        *passData = TRUE;
      }
      break;

      case SECOC_OVERRIDE_PASS_UNTIL_NOTICE:
      {
        /* This will indicate that the status was already renewed once for the current secured PDU */
        SecOC_RxData[instId].RenewedVerStatus = TRUE;

        SecOC_RxData[instId].VerificationResult = SECOC_VERIFICATIONFAILURE_OVERWRITTEN;

        *passData = TRUE;
      }
      break;

      case SECOC_OVERRIDE_SKIP_UNTIL_LIMIT:
      {
        /* This will indicate that the status was already renewed once for the current secured PDU */
        SecOC_RxData[instId].RenewedVerStatus = TRUE;

        /* Check all freshness/Data ID from the configuration */
        for (pduIdx = 0U; pduIdx < SECOC_NUMBER_RX_PDUS; pduIdx++)
        {
          /* Check if the Data ID for the given PDU is equal with other PDUs data ID */
          if (SECOC_GET_RX_ID(instId) == SECOC_GET_RX_ID(pduIdx))
          {
            SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
            /* Decrease the number of messages for which the verification result will be overridden */
            SecOC_RxData[pduIdx].NumMsgToOverride--;
            SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
          }
        }

        SecOC_RxData[instId].VerificationResult = SECOC_NO_VERIFICATION;

        *passData = TRUE;
      }
      break;

      case SECOC_OVERRIDE_SKIP_UNTIL_NOTICE:
      {
        /* This will indicate that the status was already renewed once for the current secured PDU */
        SecOC_RxData[instId].RenewedVerStatus = TRUE;

        SecOC_RxData[instId].VerificationResult = SECOC_NO_VERIFICATION;

        *passData = TRUE;
      }
      break;
#endif /* #if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_ON) */
      /* CHECK: NOPARSE */
      default:
      {
        /* Do nothing */
      }
      break;
      /* CHECK: PARSE */
    }
  }
}
#endif /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) #else */

static FUNC(void, SECOC_CODE) SecOC_Rx_CheckStatusOverridePostVerify
(
  uint16  instId
)
#if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION)
{
#if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_OFF)
  if (
      (SECOC_OVERRIDESTATUS_FAIL_MSG_NUMBER == SecOC_RxData[instId].VerifyStatusOverride) &&
      (0U                                   == SecOC_RxData[instId].NumMsgToOverride    )
     )
#else /* #if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_OFF) */
  if (
      (
       (SECOC_OVERRIDESTATUS_FAIL_MSG_NUMBER == SecOC_RxData[instId].VerifyStatusOverride) ||
       (SECOC_OVERRIDESTATUS_PASS_MSG_NUMBER == SecOC_RxData[instId].VerifyStatusOverride)
      ) &&
      (0U                                    == SecOC_RxData[instId].NumMsgToOverride    )
     )
#endif /* #if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_OFF) #else */
  {
    uint16 pduIdx;

    /* !LINKSTO SecOC.EB.Rx.SWS_SecOC_00006,1 */
    /* Check all freshness ID from the configuration */
    /* Deviation TASKING-1 */
    for (pduIdx = 0U; pduIdx < SECOC_NUMBER_RX_PDUS; pduIdx++)
    {
      /* Check if the freshness ID for the given PDU is equal with other PDUs freshness ID */
      if (SECOC_GET_RX_FRESHNESS_ID(instId)== SECOC_GET_RX_FRESHNESS_ID(pduIdx))
      {
        SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
        SecOC_RxData[pduIdx].VerifyStatusOverride = SECOC_OVERRIDESTATUS_CANCEL;
        SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
      }
    }
  }
}
#else /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) */
{
#if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_OFF)
  if (
      (SECOC_OVERRIDE_DROP_UNTIL_LIMIT == SecOC_RxData[instId].VerifyStatusOverride) &&
      (0U                              == SecOC_RxData[instId].NumMsgToOverride    )
     )
#else /* #if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_OFF) */
  if (
      (
       (SECOC_OVERRIDE_DROP_UNTIL_LIMIT == SecOC_RxData[instId].VerifyStatusOverride) ||
       (SECOC_OVERRIDE_SKIP_UNTIL_LIMIT == SecOC_RxData[instId].VerifyStatusOverride) ||
       (SECOC_OVERRIDE_PASS_UNTIL_LIMIT == SecOC_RxData[instId].VerifyStatusOverride)
      ) &&
      (0U                               == SecOC_RxData[instId].NumMsgToOverride    )
     )
#endif /* #if (SECOC_OVERRIDE_VERIFYSTATUS_PASS == STD_OFF) #else*/
  {
    uint16 pduIdx;

    /* Check all freshness/Data ID from the configuration */
    /* Deviation TASKING-1 */
    for (pduIdx = 0U; pduIdx < SECOC_NUMBER_RX_PDUS; pduIdx++)
    {
      /* Check if the Data ID for the given PDU is equal with other PDUs data ID */
      if (SECOC_GET_RX_ID(instId) == SECOC_GET_RX_ID(pduIdx))
      {
        SchM_Enter_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
        SecOC_RxData[pduIdx].VerifyStatusOverride = SECOC_OVERRIDE_CANCEL;
        SchM_Exit_SecOC_SCHM_SECOC_EXCLUSIVE_AREA_0();
      }
    }
  }
}
#endif /* #if (SECOC_API_VERSION_430 == SECOC_VERIFY_STATUS_OVERRIDE_API_VERSION) #else */

#if ((SECOC_VERIFICATION_STATUS_PROP_NONE != SECOC_VERIFICATION_STATUS_PROP_ENABLED) || (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP))
static FUNC(void, SECOC_CODE) SecOC_Rx_PropagateVerificationStatus
(
  uint16  instId
)
{
  /* Variable used for holding the verification status to propagate */
  SecOC_VerificationStatusType SecOC_RxVerificationStatus;

#if (SECOC_VERIFICATION_STATUS_PROP_NONE != SECOC_VERIFICATION_STATUS_PROP_ENABLED)
#if (SECOC_NUMBER_FUNC_VERIFICATION_STATUS_PROP > 0)
  /* Variable used for holding the index of the pointer to verification status callout function */
  uint32 calloutIdx;
#endif /* #if (SECOC_NUMBER_FUNC_VERIFICATION_STATUS_PROP > 0) */

  /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00119,1 */
  if (
      (SECOC_STATUS_PROP_BOTH          == SECOC_GET_RX_VERSTATUS_PROP_MODE(instId)) ||
      (
       (SECOC_STATUS_PROP_FAILURE_ONLY == SECOC_GET_RX_VERSTATUS_PROP_MODE(instId)) &&
       (SECOC_VERIFICATIONSUCCESS      != SecOC_RxData[instId].VerificationResult)
      )
     )
  {

    SecOC_RxVerificationStatus.freshnessValueID   = SECOC_GET_RX_FRESHNESS_ID(instId);
    SecOC_RxVerificationStatus.verificationStatus = SecOC_RxData[instId].VerificationResult;
    SecOC_RxVerificationStatus.secOCDataId        = SECOC_GET_RX_DATA_ID(instId);
#if (SECOC_VERIFICATION_STATUS_PROP_EB == SECOC_VERIFICATION_STATUS_PROP_ENABLED)
    SecOC_RxVerificationStatus.verificationReturn = SecOC_RxData[instId].CsmVerificationReturn;
#endif /* #if (SECOC_VERIFICATION_STATUS_PROP_EB == SECOC_VERIFICATION_STATUS_PROP_ENABLED) */

#if (SECOC_NUMBER_FUNC_VERIFICATION_STATUS_PROP > 0)
    /* !LINKSTO SecOC.ASR430.Rx.SWS_SecOC_00119,1 */
    /* Deviation TASKING-1 */
    for (calloutIdx = 0U; calloutIdx < SECOC_NUMBER_FUNC_VERIFICATION_STATUS_PROP; calloutIdx++)
    {
      SecOC_RxVerificationStatusCallout[calloutIdx](SecOC_RxVerificationStatus);
    }
#endif /* #if (SECOC_NUMBER_FUNC_VERIFICATION_STATUS_PROP > 0) */

    /* call the Rte, if configured */
#if (STD_ON == SECOC_INCLUDE_RTE)
    SecOC_Rx_Write_VerificationStatus(instId, &SecOC_RxVerificationStatus);
#endif /* #if (STD_ON == SECOC_INCLUDE_RTE) */

  }
#endif /* #if (SECOC_VERIFICATION_STATUS_PROP_NONE != SECOC_VERIFICATION_STATUS_PROP_ENABLED) */

#if (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP)
  /* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00271,1 */
  if (
      (SECOC_STATUS_PROP_BOTH          == SECOC_GET_RX_CS_VERSTATUS_PROP_MODE(instId)) ||
      (
       (SECOC_STATUS_PROP_FAILURE_ONLY == SECOC_GET_RX_CS_VERSTATUS_PROP_MODE(instId)) &&
       (SECOC_VERIFICATIONSUCCESS      != SecOC_RxData[instId].VerificationResult)
      )
     )
  {
    SecOC_RxVerificationStatus.freshnessValueID   = SECOC_GET_RX_FRESHNESS_ID(instId);
    SecOC_RxVerificationStatus.verificationStatus = SecOC_RxData[instId].VerificationResult;
    SecOC_RxVerificationStatus.secOCDataId        = SECOC_GET_RX_DATA_ID(instId);

    SecOC_Rx_Call_VerificationStatusIndication(instId, &SecOC_RxVerificationStatus);

  }
#endif /* #if (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP) */
}
#endif /* #if ((SECOC_VERIFICATION_STATUS_PROP_NONE != SECOC_VERIFICATION_STATUS_PROP_ENABLED) || (STD_ON == SECOC_CS_VERIFICATION_STATUS_PROP)) */

static FUNC(void, SECOC_CODE) SecOC_Rx_ShiftLeft
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
    array[byteLength_shifted] = ((uint8) (array[byteLength_shifted] << shift));
  }
  else
  {
    array[byteLength_shifted] = ((uint8) (array[byteLength_shifted] << shift)  ) |
                                (array[byteLength_shifted + 1U] >> (8U - shift));
  }
}

#if ((STD_ON == SECOC_ENABLE_SEC_EVENT_REPORTING) && (STD_ON == SECOC_RX_USE_MACVERIFY))
static FUNC(void, SECOC_CODE) SecOC_Rx_ReportSecurityEventWithContextData
(
  IdsM_SecurityEventIdType securityEventId,
  uint16 instId
)
{
  P2CONST(uint8,  AUTOMATIC, SECOC_APPL_DATA) contextData = IdsmContextBuffer;

  uint8 index;
  /* Deviation TASKING-1 */
  for (index = 0U; index < SECOC_DATAID_LENGTH; index++)
  {
    IdsmContextBuffer[SECOC_DATAID_LENGTH - index - 1U] =
    (uint8) (SECOC_GET_RX_DATA_ID(instId) >> (index * 8U));
  }

  /* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00273,1 */
  /* !LINKSTO SecOC.ASR20-11.Rx.SWS_SecOC_00275,1 */
  IdsM_SetSecurityEventWithContextData(securityEventId, contextData, SECOC_DATAID_LENGTH);
}
#endif /* #if ((STD_ON == SECOC_ENABLE_SEC_EVENT_REPORTING) && (STD_ON == SECOC_RX_USE_MACVERIFY)) */

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

#endif /* #if (SECOC_NUMBER_RX_PDUS > 0) */

/*==================[end of file]=================================================================*/

