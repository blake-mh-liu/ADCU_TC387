/**
 * \file
 *
 * \brief AUTOSAR Dcm
 *
 * This file contains the implementation of the AUTOSAR
 * module Dcm.
 *
 * \version 5.0.24
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* !LINKSTO Dcm.Dsn.File.AuthenticationHandler.Impl,1 */
/* This file contains the implementation of the AuthenticationHandler SW unit. */

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * This warnings is a false positive.
 * The compiler optimizes the 'for' loop (which has only 1 iteration) in the following way
 * - it prepares in advance the index for the next iteration
 * - if the index is equal to '0' it goes back to check the 'for' loop conditions, otherwise it just moves on
 * - since the index is already equal to '1', it never jumps back to check the exit condition
 */

/*==================[includes]===================================================================*/

#include <Dcm_Authentication_AuthenticationHandler.h>
#include <Dcm_Authentication_DiagnosticPolicyHandler.h>
#include <Dcm_Authentication_CryptoStackFacade.h>

#include <Std_Types.h> /* AUTOSAR standard types */
#include <TSAutosar.h>
#include <TSMem.h>
#include <Dcm_Trace.h>
#include <Dcm_Int.h>   /* Includes definition of DCM_INTERNAL_API_ID */
#include <SchM_Dcm.h>  /* SchM interface for Dcm */

#if (DCM_SECURITY_EVENT_REPORTING == STD_ON)
#include <Dcm_SEVReportingServices.h>
#endif

#if (DCM_AUTHENTICATION_CONNECTION == STD_ON)

/*==================[inclusions]=================================================================*/

/*==================[macro definitions]==========================================================*/
/** @defgroup Macro_Dcm_AuthenticationHandlerStateType macros for Dcm_AuthenticationHandlerStateType
 ** \brief    These macros are used as values for Dcm_AuthenticationHandlerStateType
 **  @{
 */
#if (defined DCM_AUTHENTICATIONHANDLERSTATE_UNINIT)
  #error DCM_AUTHENTICATIONHANDLERSTATE_UNINIT already defined
#endif /* if (defined DCM_AUTHENTICATIONHANDLERSTATE_UNINIT) */
#define DCM_AUTHENTICATIONHANDLERSTATE_UNINIT 0U

#if (defined DCM_AUTHENTICATIONHANDLERSTATE_CANCELLING)
  #error DCM_AUTHENTICATIONHANDLERSTATE_CANCELLING already defined
#endif /* if (defined DCM_AUTHENTICATIONHANDLERSTATE_CANCELLING) */
#define DCM_AUTHENTICATIONHANDLERSTATE_CANCELLING 1U

#if (defined DCM_AUTHENTICATIONHANDLERSTATE_IDLE)
  #error DCM_AUTHENTICATIONHANDLERSTATE_IDLE already defined
#endif /* if (defined DCM_AUTHENTICATIONHANDLERSTATE_IDLE) */
#define DCM_AUTHENTICATIONHANDLERSTATE_IDLE 2U

#if (defined DCM_AUTHENTICATIONHANDLERSTATE_APCE_CERTIFICATEVERIFICATION)
  #error DCM_AUTHENTICATIONHANDLERSTATE_APCE_CERTIFICATEVERIFICATION already defined
#endif /* if (defined DCM_AUTHENTICATIONHANDLERSTATE_APCE_CERTIFICATEVERIFICATION) */
#define DCM_AUTHENTICATIONHANDLERSTATE_APCE_CERTIFICATEVERIFICATION 3U

#if (defined DCM_AUTHENTICATIONHANDLERSTATE_APCE_SERVERCHALLENGEGENERATION)
  #error DCM_AUTHENTICATIONHANDLERSTATE_APCE_SERVERCHALLENGEGENERATION already defined
#endif /* if (defined DCM_AUTHENTICATIONHANDLERSTATE_APCE_SERVERCHALLENGEGENERATION) */
#define DCM_AUTHENTICATIONHANDLERSTATE_APCE_SERVERCHALLENGEGENERATION 4U

#if (defined DCM_AUTHENTICATIONHANDLERSTATE_APCE_CLIENTCHALLENGESIGNING)
  #error DCM_AUTHENTICATIONHANDLERSTATE_APCE_CLIENTCHALLENGESIGNING already defined
#endif /* if (defined DCM_AUTHENTICATIONHANDLERSTATE_APCE_CLIENTCHALLENGESIGNING) */
#define DCM_AUTHENTICATIONHANDLERSTATE_APCE_CLIENTCHALLENGESIGNING 5U

#if (defined DCM_AUTHENTICATIONHANDLERSTATE_CERTIFICATEVERIFIED)
  #error DCM_AUTHENTICATIONHANDLERSTATE_CERTIFICATEVERIFIED already defined
#endif /* if (defined DCM_AUTHENTICATIONHANDLERSTATE_CERTIFICATEVERIFIED) */
#define DCM_AUTHENTICATIONHANDLERSTATE_CERTIFICATEVERIFIED 6U

#if (defined DCM_AUTHENTICATIONHANDLERSTATE_PROOFOFOWNERSHIP)
  #error DCM_AUTHENTICATIONHANDLERSTATE_PROOFOFOWNERSHIP already defined
#endif /* if (defined DCM_AUTHENTICATIONHANDLERSTATE_PROOFOFOWNERSHIP) */
#define DCM_AUTHENTICATIONHANDLERSTATE_PROOFOFOWNERSHIP 7U
/* @} */
/* End of macro definitions for Dcm_AuthenticationHandlerStateType */

/*==================[type declarations]==========================================================*/

/* !LINKSTO Dcm.Dsn.Type.Dcm_AuthenticationHandlerStateType,1 */
typedef uint8 Dcm_AuthenticationHandlerStateType;

/*==================[internal function declarations]=============================================*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/** \brief Clean-up internal data elements
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DCM_CODE) Dcm_AuthenticationHandler_CleanUp(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex
);

/** \brief Invokes KeyM module to remove stored certificate
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DCM_CODE) Dcm_AuthenticationHandler_RemoveStoredCertificate(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex
);

/** \brief Processes an authentication request acording to APCE
 ** (Authentication with PKI Certificate Exchange) concept
 **
 ** This function continues with processing of the authentication request after receiving
 ** a KeyM callback Dcm_KeyMAsyncCertificateVerifyFinished().
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 **
 ** \return  Result of the authentication procedure
 ** \retval E_OK           Request completed
 ** \retval E_NOT_OK       Request failed, NRC is updated in AuthenticationContext
 ** \retval DCM_E_PENDING  Request is in progress, function needs to be called again
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Asynchronous}
 */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_AuthenticationHandler_ProcessVerifyCertificateDone(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex
);

/** \brief Processes an authentication request acording to APCE
 ** (Authentication with PKI Certificate Exchange) concept
 **
 ** This function continues with processing of the authentication request after receiving
 ** a Csm callback Dcm_CsmAsyncJobFinished() for a RandomGenerate job.
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 ** \param[in]    AuthenticationContext          Pointer to the context that holds all input
 **                                              and output data.
 **
 ** \return  Result of the authentication procedure
 ** \retval E_OK           Request completed
 ** \retval E_NOT_OK       Request failed, NRC is updated in AuthenticationContext
 ** \retval DCM_E_PENDING  Request is in progress, function needs to be called again
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Asynchronous}
 */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_AuthenticationHandler_ProcessRandomGenerateDone(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  P2VAR(Dcm_AuthenticationContextType, AUTOMATIC, DCM_VAR) AuthenticationContext
);

#if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON)
/** \brief Processes an authentication request acording to APCE
 ** (Authentication with PKI Certificate Exchange) concept
 **
 ** This function continues with processing of the authentication request after receiving
 ** a Csm callback Dcm_CsmAsyncJobFinished() for a SignatureGenerate job.
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 ** \param[in]    AuthenticationContext          Pointer to the context that holds all input
 **                                              and output data.
 ** \return  Result of the authentication procedure
 ** \retval E_OK           Request completed
 ** \retval E_NOT_OK       Request failed, NRC is updated in AuthenticationContext
 ** \retval DCM_E_PENDING  Request is in progress, function needs to be called again
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Asynchronous}
 */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_AuthenticationHandler_ProcessSignatureGenerateDone(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  P2VAR(Dcm_AuthenticationContextType, AUTOMATIC, DCM_VAR) AuthenticationContext
);
#endif /* #if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON) */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*==================[internal constants]=========================================================*/

/*==================[internal data]==============================================================*/

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dcm_MemMap.h>

STATIC VAR(Dcm_AccessControlDataType, DCM_VAR) Dcm_CurrentAccessControlData;

#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dcm_MemMap.h>

#define DCM_START_SEC_VAR_CLEARED_8
#include <Dcm_MemMap.h>

STATIC VAR(Dcm_AuthenticationHandlerStateType, DCM_VAR) Dcm_AuthenticationHandlerState[DCM_NUM_AUTHENTICATION_CONNECTIONS];
STATIC VAR(uint8, DCM_VAR) Dcm_AuthenticationChallengeServer[DCM_NUM_AUTHENTICATION_CONNECTIONS][DCM_MAX_CHALLENGE_LENGTH];
#if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON)
STATIC VAR(uint8, DCM_VAR) Dcm_AuthenticationSignedChallenge[DCM_SIGNEDCHALLENGEBUFFER_SIZE];
#endif /* #if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON) */
/* This flag indicates whether ResetAuthentication() was successfully called.
   The purpose of it is to delay execution of required actions from interrupt context to MF context. */
STATIC VAR(boolean, DCM_VAR) Dcm_AuthenticationHandlerResetAuthenticationFlag[DCM_NUM_AUTHENTICATION_CONNECTIONS];

#define DCM_STOP_SEC_VAR_CLEARED_8
#include <Dcm_MemMap.h>

#define DCM_START_SEC_VAR_CLEARED_32
#include <Dcm_MemMap.h>

#if (DCM_AUTHENTICATION_IDLECONNECTIONTIMER == STD_ON)
STATIC VAR(Dcm_AuthenticationIdleTimerValueType, DCM_VAR) Dcm_AuthenticationIdleTimerValue[DCM_NUM_AUTHENTICATION_CONNECTIONS];
#endif /* #if (DCM_AUTHENTICATION_IDLECONNECTIONTIMER == STD_ON) */

#define DCM_STOP_SEC_VAR_CLEARED_32
#include <Dcm_MemMap.h>

/*==================[external constants]=========================================================*/

/*==================[external data]==============================================================*/

/*==================[external function definitions]==============================================*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/* !LINKSTO Dcm.Dsn.IB.AuthenticationHandler.Init,1 */
FUNC(void, DCM_CODE) Dcm_AuthenticationHandler_Init(void)
{
  uint16_least AuthenticationConnectionIndex;

  DBG_DCM_AUTHENTICATIONHANDLER_INIT_ENTRY();

  TS_MemSet(Dcm_AuthenticationChallengeServer, 0x00U, sizeof(Dcm_AuthenticationChallengeServer));

  /* Deviation TASKING-1 <+2> */
  for (AuthenticationConnectionIndex = 0U;
       AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS;
       AuthenticationConnectionIndex++)
  {
    Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] = DCM_AUTHENTICATIONHANDLERSTATE_IDLE;
    Dcm_AuthenticationHandlerResetAuthenticationFlag[AuthenticationConnectionIndex] = FALSE;
#if (DCM_AUTHENTICATION_IDLECONNECTIONTIMER == STD_ON)
    Dcm_AuthenticationIdleTimerValue[AuthenticationConnectionIndex] = 0U;
#endif /* #if (DCM_AUTHENTICATION_IDLECONNECTIONTIMER == STD_ON) */
  }

  DBG_DCM_AUTHENTICATIONHANDLER_INIT_EXIT();
}

/* !LINKSTO Dcm.Dsn.IB.AuthenticationHandler.MainFunction,1 */
FUNC(void, DCM_CODE) Dcm_AuthenticationHandler_MainFunction(void)
{

  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex = DCM_NUM_AUTHENTICATION_CONNECTIONS;
#if (DCM_AUTHENTICATION_IDLECONNECTIONTIMER == STD_ON)
  boolean TimeoutOccured = FALSE;
#endif /* if (DCM_AUTHENTICATION_IDLECONNECTIONTIMER == STD_ON) */
  boolean ResetAuthenticationOccured = FALSE;

  DBG_DCM_AUTHENTICATIONHANDLER_MAINFUNCTION_ENTRY();

  /* Deviation TASKING-1 <+2> */
  for (AuthenticationConnectionIndex = 0U;
       AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS;
       AuthenticationConnectionIndex++)
  {
    if ((DCM_AUTHENTICATIONHANDLERSTATE_CANCELLING == Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex]) &&
        (DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING != Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult))
    {
      /* discard operation results if asynchronous operation was canceled */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.ProtocolPreemption.RemoveStoredCertificate,1
         !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.LimitRCRRP.RemoveStoredCertificate,1
         !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.ProtocolPreemption.RemoveStoredCertificate,1
         !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.LimitRCRRP.RemoveStoredCertificate,1
         !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.LimitRCRRP.RemoveStoredCertificate,1
         !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.ProtocolPreemption.RemoveStoredCertificate,1 */
      Dcm_AuthenticationHandler_RemoveStoredCertificate(AuthenticationConnectionIndex);
      Dcm_AuthenticationHandler_CleanUp(AuthenticationConnectionIndex);
      Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] = DCM_AUTHENTICATIONHANDLERSTATE_IDLE;
    }

    /* ENTER critical section */
    SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

#if (DCM_AUTHENTICATION_IDLECONNECTIONTIMER == STD_ON)
    /* Check if IdleConnectionTimer is running. */
    if (Dcm_AuthenticationIdleTimerValue[AuthenticationConnectionIndex] > 0U)
    {
      /* Decrease timer value */
      Dcm_AuthenticationIdleTimerValue[AuthenticationConnectionIndex] =
        Dcm_AuthenticationIdleTimerValue[AuthenticationConnectionIndex] - 1U;
     if (Dcm_AuthenticationIdleTimerValue[AuthenticationConnectionIndex] == 0U)
     {
       /* Timeout occured, set the flag. */
       TimeoutOccured = TRUE;
     }
    }
#endif /* #if (DCM_AUTHENTICATION_IDLECONNECTIONTIMER == STD_ON) */

    if (Dcm_AuthenticationHandlerResetAuthenticationFlag[AuthenticationConnectionIndex] == TRUE)
    {
      Dcm_AuthenticationHandlerResetAuthenticationFlag[AuthenticationConnectionIndex] = FALSE;
      /* ResetAuthentication() call occured, set the flag. */
      ResetAuthenticationOccured = TRUE;
    }

    /* LEAVE critical section */
    SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

    if (ResetAuthenticationOccured == TRUE)
    {
      Dcm_DiagnosticPolicyHandler_ResetAuthentication(AuthenticationConnectionIndex,
                                                      TRUE);
    }
#if (DCM_AUTHENTICATION_IDLECONNECTIONTIMER == STD_ON)
    /* Check if IdleConnectionTimer occured.
       If transition to deauthenticated state already happen due to ResetAuthentication call
       do not trigger it second time. */
    if ((TimeoutOccured == TRUE) && (ResetAuthenticationOccured == FALSE))
    {
      /* Reset authentication state */
      /* !LINKSTO Dcm.EB.AuthenticationStateHandling.Authenticated.IdleConnectionTimeout.TransitionToDeauthenticated,1 */
      /* !LINKSTO Dcm.EB.AuthenticationStateHandling.Authenticated.IdleConnectionTimeout.NewCurrentRole.ConfiguredDeauthenticatedRole,1 */
      /* !LINKSTO Dcm.EB.AuthenticationStateHandling.Authenticated.IdleConnectionTimeout.TransitionToDeauthenticated.RteModeSwitch,1 */
      Dcm_DiagnosticPolicyHandler_ResetAuthentication(AuthenticationConnectionIndex,
                                                      FALSE);
    }
    /* Reset TimeoutOccured flag, since it will be used in next iteration cycle. */
    TimeoutOccured = FALSE;
#endif /* #if (DCM_AUTHENTICATION_IDLECONNECTIONTIMER == STD_ON) */

  /* Reset ResetAuthenticationOccured flag, since it will be used in next iteration cycle. */
  ResetAuthenticationOccured = FALSE;

  }

  DBG_DCM_AUTHENTICATIONHANDLER_MAINFUNCTION_EXIT();
}

/* !LINKSTO Dcm.Dsn.IB.AuthenticationHandler.CancelAuthentication,1 */
FUNC(void, DCM_CODE) Dcm_AuthenticationHandler_CancelAuthentication(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex
)
{
  DBG_DCM_AUTHENTICATIONHANDLER_CANCELAUTHENTICATION_ENTRY(AuthenticationConnectionIndex);

  DCM_PRECONDITION_ASSERT((AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS),
                           DCM_INTERNAL_API_ID);

  /* states are ordered. States below or equal IDLE are not cancelable */
  if (Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] > DCM_AUTHENTICATIONHANDLERSTATE_IDLE)
  {
    /* set CANCELLING state before cancelling the operation! */
    const Dcm_AuthenticationHandlerStateType CurrentState = Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex];
    Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] = DCM_AUTHENTICATIONHANDLERSTATE_CANCELLING;

    switch (CurrentState)
    {
      case DCM_AUTHENTICATIONHANDLERSTATE_APCE_CERTIFICATEVERIFICATION:
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.ProtocolPreemption.KeyMJobCancellation.Discard,1
           !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.ProtocolPreemption.KeyMJobCancellation.Discard,1 */
        Dcm_CryptoStackFacade_CancelOperation(AuthenticationConnectionIndex, DCM_CRYPTOOPERATION_VERIFYCERTIFICATE);
        break;

      case DCM_AUTHENTICATIONHANDLERSTATE_APCE_SERVERCHALLENGEGENERATION:
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.LimitRCRRP.CsmJobRandomGenerateCancellation.InvokeCsmCancelJob,1
           !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.ProtocolPreemption.CsmJobRandomGenerateCancellation.InvokeCsmCancelJob,1
           !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.LimitRCRRP.CsmJobRandomGenerateCancellation.InvokeCsmCancelJob,1
           !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.ProtocolPreemption.CsmJobRandomGenerateCancellation.InvokeCsmCancelJob,1 */
        Dcm_CryptoStackFacade_CancelOperation(AuthenticationConnectionIndex, DCM_CRYPTOOPERATION_CREATECHALLENGE);
        break;

      case DCM_AUTHENTICATIONHANDLERSTATE_PROOFOFOWNERSHIP:
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.LimitRCRRP.CsmJobSignatureVerifyCancellation.InvokeCsmCancelJob,1
           !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.ProtocolPreemption.CsmJobSignatureVerifyCancellation.InvokeCsmCancelJob,1 */
        Dcm_CryptoStackFacade_CancelOperation(AuthenticationConnectionIndex, DCM_CRYPTOOPERATION_VERIFYSIGNATURE);
        break;

      case DCM_AUTHENTICATIONHANDLERSTATE_CERTIFICATEVERIFIED:
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.PositiveResponse.TransmissionFailed.RemoveStoredCertificate,1
           !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.ProtocolPreemption.PositiveResponse.TransmissionCancelled.RemoveStoredCertificate,1
           !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.TxBufferShort.RemoveStoredCertificate,1
           !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.TxBufferShort.RemoveStoredCertificate,1
           !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.PositiveResponse.TransmissionFailed.RemoveStoredCertificate,1
           !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.ProtocolPreemption.PositiveResponse.TransmissionCancelled.RemoveStoredCertificate,1 */
        Dcm_AuthenticationHandler_RemoveStoredCertificate(AuthenticationConnectionIndex);
        /* clean-up and set state to IDLE */
        Dcm_AuthenticationHandler_CleanUp(AuthenticationConnectionIndex);
        Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] = DCM_AUTHENTICATIONHANDLERSTATE_IDLE;
        break;

      case DCM_AUTHENTICATIONHANDLERSTATE_APCE_CLIENTCHALLENGESIGNING:
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.LimitRCRRP.CsmJobSignatureGenerateCancellation.InvokeCsmCancelJob,1
           !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.ProtocolPreemption.CsmJobSignatureGenerateCancellation.InvokeCsmCancelJob,1 */
        Dcm_CryptoStackFacade_CancelOperation(AuthenticationConnectionIndex, DCM_CRYPTOOPERATION_SIGNCHALLENGE);
        break;

      /* CHECK: NOPARSE */
      default:
        /* no asynchronous operation in progress; clean-up and set state to IDLE */
        Dcm_AuthenticationHandler_CleanUp(AuthenticationConnectionIndex);
        Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] = DCM_AUTHENTICATIONHANDLERSTATE_IDLE;
        /* Defensive branch. Default case at the end of the switch statement */
        DCM_UNREACHABLE_CODE_ASSERT(DCM_INTERNAL_API_ID);
        break;
      /* CHECK: PARSE */
    }
  }

  DBG_DCM_AUTHENTICATIONHANDLER_CANCELAUTHENTICATION_EXIT(AuthenticationConnectionIndex);
}

/* !LINKSTO Dcm.Dsn.IB.AuthenticationHandler.AuthenticationProcess,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_AuthenticationHandler_AuthenticationProcess(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  P2VAR(Dcm_AuthenticationContextType, AUTOMATIC, DCM_VAR) AuthenticationContext
)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DCM_AUTHENTICATIONHANDLER_AUTHENTICATIONPROCESS_ENTRY(AuthenticationConnectionIndex, AuthenticationContext);

  DCM_PRECONDITION_ASSERT((AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS),
                           DCM_INTERNAL_API_ID);

  if (Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] == DCM_AUTHENTICATIONHANDLERSTATE_CANCELLING)
  {

    /* report busy while asynchronous operations are still running */
    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.UnidirectionalKeyMJobPending.TransmitNRC0x21,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.UnidirectionalCsmJobRandomGeneratePending.TransmitNRC0x21,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.ProofOfOwnershipCsmJobSignatureVerifyPending.TransmitNRC0x21,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.BidirectionalKeyMJobPending.TransmitNRC0x21,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.BidirectionalCsmJobRandomGeneratePending.TransmitNRC0x21,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.BidirectionalCsmJobSignatureGeneratePending.TransmitNRC0x21,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.UnidirectionalKeyMJobPending.TransmitNRC0x21,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.UnidirectionalCsmJobRandomGeneratePending.TransmitNRC0x21,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.ProofOfOwnershipCsmJobSignatureVerifyPending.TransmitNRC0x21,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.BidirectionalKeyMJobPending.TransmitNRC0x21,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.BidirectionalCsmJobRandomGeneratePending.TransmitNRC0x21,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.BidirectionalCsmJobSignatureGeneratePending.TransmitNRC0x21,1 */
    AuthenticationContext->ErrorCode = DCM_E_BUSYREPEATREQUEST;
  }
  else
  {
    switch (Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex])
    {
      case DCM_AUTHENTICATIONHANDLERSTATE_IDLE:
      case DCM_AUTHENTICATIONHANDLERSTATE_CERTIFICATEVERIFIED:
        Result = Dcm_CryptoStackFacade_SetCertificate(AuthenticationConnectionIndex,
                                                      AuthenticationContext->CertificateClient.Certificate,
                                                      AuthenticationContext->CertificateClient.LengthOfCertificate,
                                                      &Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult);
        if (E_OK == Result)
        {
          Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
          /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.KeyMSetCertificate.ReturnsOK.InvokeKeyMVerifyCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMSetCertificate.ReturnsOK.InvokeKeyMVerifyCertificate,1 */
          Result = Dcm_CryptoStackFacade_VerifyCertificate(AuthenticationConnectionIndex,
                                                           &Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult);

          if (E_OK == Result)
          {
            Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] = DCM_AUTHENTICATIONHANDLERSTATE_APCE_CERTIFICATEVERIFICATION;
            Result = DCM_E_PENDING;
          }
          else
          {
            /* Synchronous call Csm_VerifyCertificate() returns an error. */
            /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.KeyMVerifyCertificate.ReturnsNotOK.RemoveStoredCertificate,1
               !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.KeyMVerifyCertificate.ReturnsBusy.RemoveStoredCertificate,1
               !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.KeyMVerifyCertificate.ReturnsMismatch.RemoveStoredCertificate,1
               !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.KeyMVerifyCertificate.ReturnsEmptySlot.RemoveStoredCertificate,1
               !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.KeyMVerifyCertificate.ReturnsInvalidChainOfTrust.RemoveStoredCertificate,1
               !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.KeyMVerifyCertificate.ReturnsUnsupportedCode.RemoveStoredCertificate,1
               !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMVerifyCertificate.ReturnsNotOK.RemoveStoredCertificate,1
               !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMVerifyCertificate.ReturnsBusy.RemoveStoredCertificate,1
               !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMVerifyCertificate.ReturnsMismatch.RemoveStoredCertificate,1
               !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMVerifyCertificate.ReturnsEmptySlot.RemoveStoredCertificate,1
               !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMVerifyCertificate.ReturnsInvalidChainOfTrust.RemoveStoredCertificate,1
               !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMVerifyCertificate.ReturnsUnsupportedCode.RemoveStoredCertificate,1 */
            Dcm_AuthenticationHandler_RemoveStoredCertificate(AuthenticationConnectionIndex);
            Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] = DCM_AUTHENTICATIONHANDLERSTATE_IDLE;
          }
        }
        break;

      case DCM_AUTHENTICATIONHANDLERSTATE_APCE_CERTIFICATEVERIFICATION:
        if (DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING == Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult)
        {
          Result = DCM_E_PENDING;
        }
        else
        {
          Result = Dcm_AuthenticationHandler_ProcessVerifyCertificateDone(AuthenticationConnectionIndex);
        }
        break;

      case DCM_AUTHENTICATIONHANDLERSTATE_APCE_SERVERCHALLENGEGENERATION:
        if (DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING == Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult)
        {
          Result = DCM_E_PENDING;
        }
        else
        {
          Result = Dcm_AuthenticationHandler_ProcessRandomGenerateDone(AuthenticationConnectionIndex, AuthenticationContext);
        }
        break;

#if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON)
      case DCM_AUTHENTICATIONHANDLERSTATE_APCE_CLIENTCHALLENGESIGNING:
        if (DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING == Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult)
        {
          Result = DCM_E_PENDING;
        }
        else
        {
          Result = Dcm_AuthenticationHandler_ProcessSignatureGenerateDone(AuthenticationConnectionIndex, AuthenticationContext);
        }
        break;
#endif /* #if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON) */

      /* CHECK: NOPARSE */
      case DCM_AUTHENTICATIONHANDLERSTATE_PROOFOFOWNERSHIP:
        Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult = DCM_E_GENERALREJECT;
        /* Defensive branch. */
        DCM_UNREACHABLE_CODE_ASSERT(DCM_INTERNAL_API_ID);
        break;
      /* CHECK: PARSE */

      /* CHECK: NOPARSE */
    default:
        Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult = DCM_E_REQUESTSEQUENCEERROR;
        Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] = DCM_AUTHENTICATIONHANDLERSTATE_IDLE;
        /* Defensive branch. Default case at the end of the switch statement */
        DCM_UNREACHABLE_CODE_ASSERT(DCM_INTERNAL_API_ID);
        break;
      /* CHECK: PARSE */
    }

    if ((Result != DCM_E_PENDING) && (Result != E_OK))
    {
      AuthenticationContext->ErrorCode = Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult;
      /* cancel the authentication procedure on error */
      Dcm_AuthenticationHandler_CancelAuthentication(AuthenticationConnectionIndex);
    }
  }

  DBG_DCM_AUTHENTICATIONHANDLER_AUTHENTICATIONPROCESS_EXIT(Result, AuthenticationConnectionIndex, AuthenticationContext);
  return Result;
}

/* !LINKSTO Dcm.Dsn.IB.AuthenticationHandler.ProofOfOwnership,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_AuthenticationHandler_ProofOfOwnership(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  Dcm_AuthenticationProofOfOwnershipType ProofOfOwnershipClient,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode
)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DCM_AUTHENTICATIONHANDLER_PROOFOFOWNERSHIP_ENTRY(AuthenticationConnectionIndex, ProofOfOwnershipContext);

  DCM_PRECONDITION_ASSERT((AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS),
                           DCM_INTERNAL_API_ID);

  if (Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] == DCM_AUTHENTICATIONHANDLERSTATE_CANCELLING)
  {

    /* report busy while asynchronous operations are still running */
    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.UnidirectionalKeyMJobPending.TransmitNRC0x21,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.UnidirectionalCsmJobRandomGeneratePending.TransmitNRC0x21,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.ProofOfOwnershipCsmJobSignatureVerifyPending.TransmitNRC0x21,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.BidirectionalKeyMJobPending.TransmitNRC0x21,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.BidirectionalCsmJobRandomGeneratePending.TransmitNRC0x21,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.BidirectionalCsmJobSignatureGeneratePending.TransmitNRC0x21,1 */
    *ErrorCode = DCM_E_BUSYREPEATREQUEST;
  }
  else
  {
    switch (Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex])
    {
      case DCM_AUTHENTICATIONHANDLERSTATE_CERTIFICATEVERIFIED:
        Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;

        Result = Dcm_CryptoStackFacade_VerifySignature(
          AuthenticationConnectionIndex,
          Dcm_AuthenticationChallengeServer[AuthenticationConnectionIndex],
          Dcm_AuthenticationConfigPtr->AuthenticationConnection[AuthenticationConnectionIndex].ChallengeLength,
          ProofOfOwnershipClient.ProofOfOwnership,
          ProofOfOwnershipClient.LengthOfProofOfOwnership,
          &Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult);

        if (E_OK == Result)
        {
          Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] = DCM_AUTHENTICATIONHANDLERSTATE_PROOFOFOWNERSHIP;
          Result = DCM_E_PENDING;
        }
        else
        {
          /* Synchronous call Csm_VerifySignature reports an error */
          /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.CsmSignatureVerify.ReturnsNotOK.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.CsmSignatureVerify.ReturnsBusy.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.ProofOfOwnership.CsmSignatureVerify.ReturnsQueueFull.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.CsmSignatureVerify.ReturnsKeyNotValid.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.ProofOfOwnership.CsmSignatureVerify.ReturnsSmallBuffer.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.ProofOfOwnership.CsmSignatureVerify.ReturnsUnsupportedCode.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.ProofOfOwnership.CsmSignatureVerify.ReturnsKeySizeMismatch.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.ProofOfOwnership.CsmSignatureVerify.ReturnsKeyEmpty.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.ProofOfOwnership.CsmSignatureVerify.ReturnsUnsupportedCode.RemoveStoredCertificate,1 */
          Dcm_AuthenticationHandler_RemoveStoredCertificate(AuthenticationConnectionIndex);
          Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] = DCM_AUTHENTICATIONHANDLERSTATE_IDLE;
        }
        break;

      case DCM_AUTHENTICATIONHANDLERSTATE_PROOFOFOWNERSHIP:
        if (DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING == Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult)
        {
          Result = DCM_E_PENDING;
        }
        else
        {
          if (E_OK == Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult)
          {
            /* read certificate element(s) */
            Result = Dcm_CryptoStackFacade_GetAuthenticationRole(AuthenticationConnectionIndex,
                                                                 Dcm_CurrentAccessControlData.AuthenticationRole,
                                                                 &Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult);
            if (E_OK == Result)
            {
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.KeyMCertElementGet.ReturnsOK.ValidRoleSize.Deauthenticated.ConfiguredDeauthenticatedRole.SetNewRole,1
                 !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.KeyMCertElementGet.ReturnsOK.ValidRoleSize.Deauthenticated.ProvidedDeauthenticatedRole.SetNewRole,1
                 !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.KeyMCertElementGet.ReturnsOK.ValidRoleSize.Authenticated.SetNewRole,1 */
              Dcm_DiagnosticPolicyHandler_SetAuthentication(AuthenticationConnectionIndex, Dcm_CurrentAccessControlData.AuthenticationRole);
            }
          }
#if (AUTHENTICATION_GENERAL_NRC_MODERULE == STD_ON)
          if ((E_NOT_OK == Result) &&
              (DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDCONTENT == Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult))
          {
            Dcm_NegativeResponseCodeType Error = DCM_E_OK;
            /* "Certificate verification failed" NRC is in range DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDTIMEPERIOD (0x50) to DCM_E_CERTIFICATEVERIFICATIONFAILEDREVOKED (0x57) */
            if (TRUE == Dcm_AuthenticationConfigPtr->AuthenticationGeneralNRCModeRule(&Error))
            {
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.KeyMCertElementGet.ReturnsOK.InvalidRoleSize.DcmDspAuthenticationGeneralNRCModeRuleTrue.TransmitGeneralNrc,1
                 !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.KeyMCertElementGet.ReturnsNotOK.DcmDspAuthenticationGeneralNRCModeRuleTrue.TransmitGeneralNrc,1 */
              Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult = DCM_DSP_AUTHENTICATION_GENERAL_NRC;
            }
          }
#endif /* #if (AUTHENTICATION_GENERAL_NRC_MODERULE == STD_ON) */
          /* Remove stored certificate */
          /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsOK.VerifyResult.VerNotOK.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsOK.VerifyResult.VerUnsupportedCode.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsNotOK.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsBusy.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsQueueFull.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsKeyNotValid.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsKeySizeMismatch.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsSmallBuffer.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsUnsupportedCode.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsEntropyExhausted.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsKeyReadFail.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsKeyWriteFail.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsKeyNotAvailable.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsKeyEmpty.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsUnsupportedCode.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.AuthenticationStateUpdated.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.KeyMCertElementGet.ReturnsOK.InvalidRoleSize.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.KeyMCertElementGet.ReturnsNotOK.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.KeyMCertElementGet.ReturnsParameterMismatch.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.KeyMCertElementGet.ReturnsCertificateSizeMismatch.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.KeyMCertElementGet.ReturnsCertificateEmpty.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.KeyMCertElementGet.ReturnsCertificateInvalid.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.KeyMCertElementGet.ReturnsUnsupportedCode.RemoveStoredCertificate,1 */
          Dcm_AuthenticationHandler_RemoveStoredCertificate(AuthenticationConnectionIndex);
          Dcm_AuthenticationHandler_CleanUp(AuthenticationConnectionIndex);
          Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] = DCM_AUTHENTICATIONHANDLERSTATE_IDLE;
        }
        break;

      /* CHECK: NOPARSE */
      case DCM_AUTHENTICATIONHANDLERSTATE_APCE_CERTIFICATEVERIFICATION:
      case DCM_AUTHENTICATIONHANDLERSTATE_APCE_SERVERCHALLENGEGENERATION:
        Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult = DCM_E_REQUESTSEQUENCEERROR;
        /* Defensive branch. */
        DCM_UNREACHABLE_CODE_ASSERT(DCM_INTERNAL_API_ID);
        break;
      /* CHECK: PARSE */

      case DCM_AUTHENTICATIONHANDLERSTATE_IDLE:
      default:
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.VerifyCertificate.NotExecuted.RequestSequenceError,1
           !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.VerifyCertificateUnidirectional.Failed.RequestSequenceError,3
           !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.VerifyCertificateUnidirectional.Cancelled.KeyMJobDone.RequestSequenceError,2
           !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.VerifyCertificateUnidirectional.Cancelled.CsmJobDone.RequestSequenceError,2
           !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.VerifyCertificateUnidirectional.PositiveResponse.TransmissionFailed.RequestSequenceError,2
           !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.VerifyCertificateUnidirectional.PositiveResponse.TransmissionCancelled.RequestSequenceError,2
           !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.LastProofOfOwnershipFailed.RequestSequenceError,3
           !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.LastProofOfOwnershipPassed.RequestSequenceError,2
           !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.LastProofOfOwnershipCancelled.RequestSequenceError,2
           !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.VerifyCertificateBidirectional.Failed.RequestSequenceError,2
           !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.VerifyCertificateBidirectional.PositiveResponse.TransmissionFailed.RequestSequenceError,1
           !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.VerifyCertificateBidirectional.Cancelled.KeyMJobDone.RequestSequenceError,1
           !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.VerifyCertificateBidirectional.Cancelled.CsmJobRandomGenerateDone.RequestSequenceError,1
           !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.VerifyCertificateBidirectional.Cancelled.CsmJobSignatureGenerateDone.RequestSequenceError,1
           !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.VerifyCertificateBidirectional.PositiveResponse.TransmissionCancelled.RequestSequenceError,1 */
        Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult = DCM_E_REQUESTSEQUENCEERROR;
        Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] = DCM_AUTHENTICATIONHANDLERSTATE_IDLE;
        break;
    }

    if ((Result != DCM_E_PENDING) && (Result != E_OK))
    {
      *ErrorCode = Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult;
      /* cancel the authentication procedure on error */
      Dcm_AuthenticationHandler_CancelAuthentication(AuthenticationConnectionIndex);
    }
  }

  DBG_DCM_AUTHENTICATIONHANDLER_PROOFOFOWNERSHIP_EXIT(Result, AuthenticationConnectionIndex, ProofOfOwnershipContext);
  return Result;
}

/* !LINKSTO Dcm.Dsn.IB.AuthenticationHandler.CryptoOperationDoneCallback,1 */
FUNC(void, DCM_CODE) Dcm_AuthenticationHandler_CryptoOperationDone(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  uint16 GeneratedLength,
  Dcm_NegativeResponseCodeType ErrorCode
)
{
  DBG_DCM_AUTHENTICATIONHANDLER_CRYPTOOPERATIONDONE_ENTRY(AuthenticationConnectionIndex, ErrorCode);

  DCM_PRECONDITION_ASSERT((AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS),
                           DCM_INTERNAL_API_ID);

  switch (Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex])
  {
    case DCM_AUTHENTICATIONHANDLERSTATE_APCE_CERTIFICATEVERIFICATION:
    case DCM_AUTHENTICATIONHANDLERSTATE_APCE_SERVERCHALLENGEGENERATION:
    case DCM_AUTHENTICATIONHANDLERSTATE_APCE_CLIENTCHALLENGESIGNING:
    case DCM_AUTHENTICATIONHANDLERSTATE_PROOFOFOWNERSHIP:
    case DCM_AUTHENTICATIONHANDLERSTATE_CANCELLING:
      /* store job result */
      Dcm_CryptoStackFacade[AuthenticationConnectionIndex].GeneratedLength = GeneratedLength;
      Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult = ErrorCode;
      break;

    /* CHECK: NOPARSE */
    default:
      /* Defensive branch. Default case at the end of the switch statement */
      DCM_UNREACHABLE_CODE_ASSERT(DCM_INTERNAL_API_ID);
      break;
    /* CHECK: PARSE */
  }
  DBG_DCM_AUTHENTICATIONHANDLER_CRYPTOOPERATIONDONE_EXIT(AuthenticationConnectionIndex, ErrorCode);
}

/* This function is called from interrupt context. */
FUNC(void, DCM_CODE) Dcm_AuthenticationHandler_ResetAuthenticationCalledSetFlag(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex
)
{
  DBG_DCM_AUTHENTICATIONHANDLER_RESETAUTHENTICATIONCALLEDSETFLAG_ENTRY(AuthenticationConnectionIndex);

  DCM_PRECONDITION_ASSERT((AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS),
                           DCM_INTERNAL_API_ID);

  /* ENTER critical section */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* Every read/write/read modify write operation needs to be protected. */
  Dcm_AuthenticationHandlerResetAuthenticationFlag[AuthenticationConnectionIndex] = TRUE;

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  DBG_DCM_AUTHENTICATIONHANDLER_RESETAUTHENTICATIONCALLEDSETFLAG_EXIT();
}

#if (DCM_AUTHENTICATION_IDLECONNECTIONTIMER == STD_ON)
/* !LINKSTO Dcm.Dsn.IB.AuthenticationHandler.IdleConnectionTimerStart,1  */

/* This function must be called from critical section only. */
FUNC(void, DCM_CODE) Dcm_AuthenticationHandler_IdleConnectionTimerStart(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex
)
{
  DBG_DCM_AUTHENTICATIONHANDLER_IDLECONNECTIONTIMERSTART_ENTRY(AuthenticationConnectionIndex);

  DCM_PRECONDITION_ASSERT((AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS),
                           DCM_INTERNAL_API_ID);


  /* Check if connection is in the DCM_AUTHENTICATED state. */
  if (Dcm_DiagnosticPolicyHandler_GetAuthenticationState(AuthenticationConnectionIndex) == DCM_AUTHENTICATED)
  {
    /* Start IdleConnectionTimer. */
    Dcm_AuthenticationIdleTimerValue[AuthenticationConnectionIndex] =
      Dcm_AuthenticationConfigPtr->AuthenticationDefaultSessionTimeout;
  }

  DBG_DCM_AUTHENTICATIONHANDLER_IDLECONNECTIONTIMERSTART_EXIT();
}

/* !LINKSTO Dcm.Dsn.IB.AuthenticationHandler.IdleConnectionTimerStop,1  */

/* This function must be called from critical section only. */
FUNC(void, DCM_CODE) Dcm_AuthenticationHandler_IdleConnectionTimerStop(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex
)
{
  DBG_DCM_AUTHENTICATIONHANDLER_IDLECONNECTIONTIMERSTOP_ENTRY(AuthenticationConnectionIndex);

  DCM_PRECONDITION_ASSERT((AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS),
                           DCM_INTERNAL_API_ID);

  /* Stop IdleConnectionTimer. */
  Dcm_AuthenticationIdleTimerValue[AuthenticationConnectionIndex] = 0U;

  DBG_DCM_AUTHENTICATIONHANDLER_IDLECONNECTIONTIMERSTOP_EXIT();
}

#endif /* #if (DCM_AUTHENTICATION_IDLECONNECTIONTIMER == STD_ON) */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*==================[internal function definitions]==============================================*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

STATIC FUNC(void, DCM_CODE) Dcm_AuthenticationHandler_CleanUp(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex
)
{
  DCM_PRECONDITION_ASSERT((AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS),
                           DCM_INTERNAL_API_ID);

  TS_MemSet(Dcm_AuthenticationChallengeServer[AuthenticationConnectionIndex], 0x00U, DCM_MAX_CHALLENGE_LENGTH);

}

STATIC FUNC(void, DCM_CODE) Dcm_AuthenticationHandler_RemoveStoredCertificate(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex
)
{
  uint8 CertificateInvalidValue = 0U;
  Dcm_NegativeResponseCodeType Result = DCM_E_POSITIVERESPONSE;

  DCM_PRECONDITION_ASSERT((AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS),
                           DCM_INTERNAL_API_ID);

  /* !LINKSTO Dcm.EB.UDSServices.RemoveStoredCertificate.KeyMSetCertificate.IgnoreReturnCode,3 */
  (void)Dcm_CryptoStackFacade_SetCertificate(
      AuthenticationConnectionIndex,
      &CertificateInvalidValue,
      0x00U,
      &Result);
}

/* !LINKSTO Dcm.Dsn.IB.AuthenticationHandler.ProcessVerifyCertificateDone,1 */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_AuthenticationHandler_ProcessVerifyCertificateDone(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex
)
{
  Std_ReturnType ResultVerifyCertificateDone = E_NOT_OK;

  if (E_OK == Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult)
  {
    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsCertificateValid.InvokeCsmRandomGenerate,1 */
    Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;

    ResultVerifyCertificateDone = Dcm_CryptoStackFacade_CreateChallenge(
                                    AuthenticationConnectionIndex,
                                    Dcm_AuthenticationConfigPtr->AuthenticationConnection[AuthenticationConnectionIndex].ChallengeLength,
                                    Dcm_AuthenticationChallengeServer[AuthenticationConnectionIndex],
                                   &Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult);

    if (E_OK == ResultVerifyCertificateDone)
    {
      Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] = DCM_AUTHENTICATIONHANDLERSTATE_APCE_SERVERCHALLENGEGENERATION;
      ResultVerifyCertificateDone = DCM_E_PENDING;
    }
    else
    {
      /* Synchronous call Csm_RandomGenerate() returns an error. */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.CsmRandomGenerate.ReturnsNotOK.RemoveStoredCertificate,1
         !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.CsmRandomGenerate.ReturnsBusy.RemoveStoredCertificate,1
         !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateUnidirectional.CsmRandomGenerate.ReturnsQueueFull.RemoveStoredCertificate,1
         !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateUnidirectional.CsmRandomGenerate.ReturnsEntropyExhaustion.RemoveStoredCertificate,1
         !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateUnidirectional.CsmRandomGenerate.ReturnsUnsupportedCode.RemoveStoredCertificate,1
         !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateUnidirectional.CsmRandomGenerate.ReturnsEntropyExhausted.RemoveStoredCertificate,1
         !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateUnidirectional.CsmRandomGenerate.ReturnsUnsupportedCode.RemoveStoredCertificate,1
         !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.CsmRandomGenerate.ReturnsNotOK.RemoveStoredCertificate,1
         !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.CsmRandomGenerate.ReturnsBusy.RemoveStoredCertificate,1
         !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.CsmRandomGenerate.ReturnsQueueFull.RemoveStoredCertificate,1
         !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.CsmRandomGenerate.ReturnsEntropyExhaustion.RemoveStoredCertificate,1
         !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.CsmRandomGenerate.ReturnsUnsupportedCode.RemoveStoredCertificate,1
         !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.CsmRandomGenerate.ReturnsEntropyExhausted.RemoveStoredCertificate,1
         !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.CsmRandomGenerate.ReturnsUnsupportedCode.RemoveStoredCertificate,1 */
      Dcm_AuthenticationHandler_RemoveStoredCertificate(AuthenticationConnectionIndex);
      Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] = DCM_AUTHENTICATIONHANDLERSTATE_IDLE;
    }
  }
  else
  {
#if (AUTHENTICATION_GENERAL_NRC_MODERULE == STD_ON)
    if ((DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDTIMEPERIOD <= Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult) &&
        (Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult <= DCM_E_CERTIFICATEVERIFICATIONFAILEDREVOKED))
    {
      Dcm_NegativeResponseCodeType Error = DCM_E_OK;
      /* "Certificate verification failed" NRC is in range DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDTIMEPERIOD (0x50) to DCM_E_CERTIFICATEVERIFICATIONFAILEDREVOKED (0x57) */
      if (TRUE == Dcm_AuthenticationConfigPtr->AuthenticationGeneralNRCModeRule(&Error))
      {
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsValidityPeriodFailed.DcmDspAuthenticationGeneralNRCModeRuleTrue.TransmitGeneralNrc,1 */
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidSignature.DcmDspAuthenticationGeneralNRCModeRuleTrue.TransmitGeneralNrc,1 */
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidChainOfTrust.DcmDspAuthenticationGeneralNRCModeRuleTrue.TransmitGeneralNrc,1 */
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidType.DcmDspAuthenticationGeneralNRCModeRuleTrue.TransmitGeneralNrc,1 */
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidFormat.DcmDspAuthenticationGeneralNRCModeRuleTrue.TransmitGeneralNrc,1 */
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidContent.DcmDspAuthenticationGeneralNRCModeRuleTrue.TransmitGeneralNrc,1 */
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsCertificateRevoked.DcmDspAuthenticationGeneralNRCModeRuleTrue.TransmitGeneralNrc,1 */
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsValidityPeriodFailed.DcmDspAuthenticationGeneralNRCModeRuleTrue.TransmitGeneralNrc,1 */
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidSignature.DcmDspAuthenticationGeneralNRCModeRuleTrue.TransmitGeneralNrc,1 */
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidChainOfTrust.DcmDspAuthenticationGeneralNRCModeRuleTrue.TransmitGeneralNrc,1 */
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidType.DcmDspAuthenticationGeneralNRCModeRuleTrue.TransmitGeneralNrc,1 */
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidFormat.DcmDspAuthenticationGeneralNRCModeRuleTrue.TransmitGeneralNrc,1 */
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidContent.DcmDspAuthenticationGeneralNRCModeRuleTrue.TransmitGeneralNrc,1 */
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsCertificateRevoked.DcmDspAuthenticationGeneralNRCModeRuleTrue.TransmitGeneralNrc,1 */
        Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult = DCM_DSP_AUTHENTICATION_GENERAL_NRC;
      }
    }
#endif /* #if (AUTHENTICATION_GENERAL_NRC_MODERULE == STD_ON) */
    /* Callback for a job started with previous call Csm_VerifyCertificate() reports an error */
    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsCertificateInvalid.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsValidityPeriodFailed.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidSignature.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidChainOfTrust.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidType.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidFormat.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidContent.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsCertificateRevoked.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsUnsupportedCode.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsCertificateInvalid.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsValidityPeriodFailed.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidSignature.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidChainOfTrust.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidType.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidFormat.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidContent.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsCertificateRevoked.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsUnsupportedCode.RemoveStoredCertificate,1 */
    Dcm_AuthenticationHandler_RemoveStoredCertificate(AuthenticationConnectionIndex);
    Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] = DCM_AUTHENTICATIONHANDLERSTATE_IDLE;

#if ((DCM_SECURITY_EVENT_REPORTING == STD_ON) && (DIAG_SEV_CERTIFICATE_FAILURE != DCM_SEV_INVALID_SEV_REF))
    Dcm_SEVReportingServices_IdsMSetSecurityEvent_CertificateFailure_NRC(Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult);
#endif /* #if ((DCM_SECURITY_EVENT_REPORTING == STD_ON) && (DIAG_SEV_CERTIFICATE_FAILURE != DCM_SEV_INVALID_SEV_REF)) */
  }
  return ResultVerifyCertificateDone;
}

/* !LINKSTO Dcm.Dsn.IB.AuthenticationHandler.ProcessRandomGenerateDone,1 */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_AuthenticationHandler_ProcessRandomGenerateDone(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  P2VAR(Dcm_AuthenticationContextType, AUTOMATIC, DCM_VAR) AuthenticationContext
)
{
  Std_ReturnType ResultRandomGenerateDone = E_NOT_OK;

  if (E_OK == Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult)
  {
    const uint16 LengthOfChallenge =
      Dcm_AuthenticationConfigPtr->AuthenticationConnection[AuthenticationConnectionIndex].ChallengeLength;

    /* set output data in context */
    AuthenticationContext->ChallengeServer.Challenge = Dcm_AuthenticationChallengeServer[AuthenticationConnectionIndex];
    AuthenticationContext->ChallengeServer.LengthOfChallenge = LengthOfChallenge;

    switch (AuthenticationContext->AuthenticationDirection)
    {
      case DCM_AUTHENTICATIONDIRECTION_UNIDIRECTIONAL:
        /* In case of unidirectional authentication the APCE processing is done */
        Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] =
          DCM_AUTHENTICATIONHANDLERSTATE_CERTIFICATEVERIFIED;
        ResultRandomGenerateDone = E_OK;
      break;

#if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON)
      case DCM_AUTHENTICATIONDIRECTION_BIDIRECTIONAL:
      {
        Dcm_SignatureGenerateJobDescriptorType Job =
          Dcm_SignatureGenerateJobDescriptor[Dcm_AuthenticationConfigPtr->AuthenticationConnection[AuthenticationConnectionIndex].SignatureGenerateJobDescriptorIndex];
        /* In case of bidirectional authentication the client challenge needs to be signed */
        Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;

        ResultRandomGenerateDone = Dcm_CryptoStackFacade_SignChallenge(
          AuthenticationConnectionIndex,
          AuthenticationContext->ChallengeClient.Challenge,
          AuthenticationContext->ChallengeClient.LengthOfChallenge,
          &Dcm_AuthenticationSignedChallenge[Job.BufferIndex],
          Job.MaxLengthOfSignedChallenge,
          &Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult);

        if (E_OK == ResultRandomGenerateDone)
        {
          Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] = DCM_AUTHENTICATIONHANDLERSTATE_APCE_CLIENTCHALLENGESIGNING;
          ResultRandomGenerateDone = DCM_E_PENDING;
        }
        else
        {
          /* Asynchronous call Csm_SignatureGenerate() returns an error. */
          /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.CsmSignatureGenerate.ReturnsNotOK.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.CsmSignatureGenerate.ReturnsBusy.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.CsmSignatureGenerate.ReturnsQueueFull.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.CsmSignatureGenerate.ReturnsKeyNotValid.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.CsmSignatureGenerate.ReturnsSmallBuffer.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.CsmSignatureGenerate.ReturnsUnsupportedCode.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.CsmSignatureGenerate.ReturnsKeySizeMismatch.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.CsmSignatureGenerate.ReturnsKeyEmpty.RemoveStoredCertificate,1
             !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.CsmSignatureGenerate.ReturnsUnsupportedCode.RemoveStoredCertificate,1 */
          Dcm_AuthenticationHandler_RemoveStoredCertificate(AuthenticationConnectionIndex);
          Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] = DCM_AUTHENTICATIONHANDLERSTATE_IDLE;
        }
      }
      break;
#endif /* #if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON) */

      /* CHECK: NOPARSE */
      default:
        /* Defensive branch. Default case at the end of the switch statement */
        Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult = DCM_E_GENERALREJECT;
        Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] = DCM_AUTHENTICATIONHANDLERSTATE_IDLE;
        DCM_UNREACHABLE_CODE_ASSERT(DCM_INTERNAL_API_ID);
        break;
      /* CHECK: PARSE */
    }
  }
  else
  {
    /* Callback for a job started with previous call Csm_RandomGenerate() reports an error */
    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsNotOK.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsBusy.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsQueueFull.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsEntropyExhaustion.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsKeyNotValid.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsKeySizeMismatch.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsSmallBuffer.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsUnsupportedCode.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsNotOK.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsBusy.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsQueueFull.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsEntropyExhaustion.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsKeyNotValid.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsKeySizeMismatch.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsSmallBuffer.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsUnsupportedCode.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsEntropyExhausted.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsEntropyExhausted.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsKeyReadFail.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsKeyReadFail.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsKeyWriteFail.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsKeyWriteFail.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsKeyNotAvailable.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsKeyNotAvailable.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsKeyEmpty.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsKeyEmpty.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsUnsupportedCode.RemoveStoredCertificate,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsUnsupportedCode.RemoveStoredCertificate,1 */
    Dcm_AuthenticationHandler_RemoveStoredCertificate(AuthenticationConnectionIndex);
    Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] = DCM_AUTHENTICATIONHANDLERSTATE_IDLE;
  }

  return ResultRandomGenerateDone;
}

#if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON)
/* !LINKSTO Dcm.Dsn.IB.AuthenticationHandler.ProcessSignatureGenerateDone,1 */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_AuthenticationHandler_ProcessSignatureGenerateDone(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  P2VAR(Dcm_AuthenticationContextType, AUTOMATIC, DCM_VAR) AuthenticationContext
)
{
  Std_ReturnType ResultSignatureGenerateDone = E_NOT_OK;

  if (E_OK == Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult)
  {
    /* set output data in context */
    Dcm_SignatureGenerateJobDescriptorType Job =
      Dcm_SignatureGenerateJobDescriptor[Dcm_AuthenticationConfigPtr->AuthenticationConnection[AuthenticationConnectionIndex].SignatureGenerateJobDescriptorIndex];
    AuthenticationContext->ProofOfOwnershipServer.ProofOfOwnership = &Dcm_AuthenticationSignedChallenge[Job.BufferIndex];
    AuthenticationContext->ProofOfOwnershipServer.LengthOfProofOfOwnership = Dcm_CryptoStackFacade[AuthenticationConnectionIndex].GeneratedLength;

    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsOK.NonZeroLengthOfProofOfOwnershipServer.InvokeKeyMGetCertificate,1 */
    ResultSignatureGenerateDone = Dcm_CryptoStackFacade_GetCertificate(
                                   AuthenticationConnectionIndex,
                                   &AuthenticationContext->CertificateServer,
                                   &Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult);

    if (E_OK == ResultSignatureGenerateDone)
    {

      /* In case of bidirectional authentication the APCE processing is done */
      Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] = DCM_AUTHENTICATIONHANDLERSTATE_CERTIFICATEVERIFIED;
      ResultSignatureGenerateDone = E_OK;

    }
    else
    {
      /* Remove the client certificate stored in KeyM. */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMGetCertificate.ReturnsOK.ZeroLengthOfCertificateServer.RemoveStoredCertificate,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMGetCertificate.ReturnsNotOK.RemoveStoredCertificate,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMGetCertificate.ReturnsBusy.RemoveStoredCertificate,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMGetCertificate.ReturnsParameterMismatch.RemoveStoredCertificate,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMGetCertificate.ReturnsCertificateSizeMismatch.RemoveStoredCertificate,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMGetCertificate.ReturnsCertificateEmpty.RemoveStoredCertificate,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMGetCertificate.ReturnsCertificateReadFail.RemoveStoredCertificate,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMGetCertificate.ReturnsUnsupportedCode.RemoveStoredCertificate,1 */
      Dcm_AuthenticationHandler_RemoveStoredCertificate(AuthenticationConnectionIndex);
      Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] = DCM_AUTHENTICATIONHANDLERSTATE_IDLE;
    }
  }
  else
  {
    /* Callback for a job started with previous call Csm_SignatureGenerate() reports an error */
    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsOK.ZeroLengthOfProofOfOwnershipServer.RemoveStoredCertificate,1 */
    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsOK.OversizedLengthOfProofOfOwnershipServer.RemoveStoredCertificate,1 */
    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsNotOK.RemoveStoredCertificate,1 */
    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsBusy.RemoveStoredCertificate,1 */
    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsQueueFull.RemoveStoredCertificate,1 */
    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsKeyNotValid.RemoveStoredCertificate,1 */
    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsKeySizeMismatch.RemoveStoredCertificate,1 */
    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsSmallBuffer.RemoveStoredCertificate,1 */
    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsUnsupportedCode.RemoveStoredCertificate,1 */
    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsEntropyExhausted.RemoveStoredCertificate,1 */
    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsKeyReadFail.RemoveStoredCertificate,1 */
    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsKeyWriteFail.RemoveStoredCertificate,1 */
    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsKeyNotAvailable.RemoveStoredCertificate,1 */
    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsKeyEmpty.RemoveStoredCertificate,1 */
    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsUnsupportedCode.RemoveStoredCertificate,1 */
    Dcm_AuthenticationHandler_RemoveStoredCertificate(AuthenticationConnectionIndex);
    Dcm_AuthenticationHandlerState[AuthenticationConnectionIndex] = DCM_AUTHENTICATIONHANDLERSTATE_IDLE;
  }

  return ResultSignatureGenerateDone;
}
#endif /* #if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON) */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif /* #if (DCM_AUTHENTICATION_CONNECTION == STD_ON) */

/*==================[end of file]================================================================*/
