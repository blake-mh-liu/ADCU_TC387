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

/* !LINKSTO Dcm.Dsn.File.CryptoStackFacade.Impl,1 */
/* This file contains the implementation of the CryptoStackFacade SW unit. */

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

#include <Dcm_Authentication_CryptoStackFacade.h>
#include <Dcm_Authentication_AuthenticationHandler.h>

#if (DCM_AUTHENTICATION_CONNECTION == STD_ON)

#include <Dcm_Int.h>
#include <Std_Types.h>                                                 /* AUTOSAR standard types */
#include <TSAutosar.h>
#include <TSMem.h>
#include <Dcm_Trace.h>
#include <Dcm_Types.h>
#include <KeyM.h>
#include <KeyM_Externals.h>                                            /* KeyM callback function */
#include <Csm.h>

/*==================[macro definitions]==========================================================*/

/** \brief Definition of maximum value of a 2-byte variable. */
#if (defined DCM_MAXVALUE_2BYTES)
  #error "DCM_MAXVALUE_2BYTES is already defined"
#endif
#define DCM_MAXVALUE_2BYTES                         65535U

/** \brief This abstraction is needed because both ACG-8 and ACG-9 are present on the same branch. */
#if (DCM_DSP_AUTHENTICATION_CRYPTO_VARIANT == DCM_AUTHENTICATION_CRYPTO_VARIANT_BEFORE_AUTOSAR_R20_11)
typedef Std_ReturnType Dcm_CryptoResultType;
#define DCM_JOBID_FROM_JOB(job) job->jobId
#define DCM_TRACE_JOB_PARAMETER(job) job
#else
typedef Crypto_ResultType Dcm_CryptoResultType;
#define DCM_JOBID_FROM_JOB(job) jobId
#define DCM_TRACE_JOB_PARAMETER(job) jobId
#endif

/*==================[type declarations]==========================================================*/

/*==================[internal function declarations]=============================================*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/** \brief Error handling for the return values of the asynchronous job: Csm_RandomGenerate
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 ** \param[in]    OperationResult                Return value of the asynchronous job.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Dcm_NegativeResponseCodeType, CSM_APPL_CODE) Dcm_CryptoStackFacade_JobFinished_RandomGenerate(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  Dcm_CryptoResultType OperationResult);

/** \brief Error handling for the return values of the asynchronous job: Csm_SignatureVerify
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 ** \param[in]    OperationResult                Return value of the asynchronous job.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Dcm_NegativeResponseCodeType, CSM_APPL_CODE) Dcm_CryptoStackFacade_JobFinished_SignatureVerify(
    Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
    Dcm_CryptoResultType OperationResult);

#if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON)
/** \brief Error handling for the return values of the asynchronous job: Csm_SignatureGenerate
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 ** \param[in]    OperationResult                Return value of the asynchronous job.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Dcm_NegativeResponseCodeType, CSM_APPL_CODE) Dcm_CryptoStackFacade_JobFinished_SignatureGenerate(
    Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
    Dcm_CryptoResultType OperationResult);
#endif /* #if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON) */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*==================[internal constants]=========================================================*/

/*==================[internal data]==============================================================*/


#define DCM_START_SEC_VAR_CLEARED_32
#include <Dcm_MemMap.h>

STATIC VAR(uint32, DCM_VAR) Dcm_Authentication_GeneratedLength[DCM_NUM_AUTHENTICATION_CONNECTIONS];

#define DCM_STOP_SEC_VAR_CLEARED_32
#include <Dcm_MemMap.h>

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dcm_MemMap.h>

STATIC VAR(Crypto_VerifyResultType, DCM_VAR) Dcm_Authentication_VerificationResult[DCM_NUM_AUTHENTICATION_CONNECTIONS];

#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dcm_MemMap.h>

/*==================[external constants]=========================================================*/

/*==================[external data]==============================================================*/

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dcm_MemMap.h>

VAR(Dcm_CryptoStackFacadeType, DCM_VAR) Dcm_CryptoStackFacade[DCM_NUM_AUTHENTICATION_CONNECTIONS];

#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dcm_MemMap.h>

/*==================[external function definitions]==============================================*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

FUNC(void, DCM_CODE) Dcm_CryptoStackFacade_Init(void)
{
  uint16_least AuthenticationConnectionIndex;

  DBG_DCM_CRYPTOSTACKFACADE_INIT_ENTRY();

  /* Deviation TASKING-1 <+2> */
  for (AuthenticationConnectionIndex = 0U;
       AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS;
       AuthenticationConnectionIndex++)
  {
    Dcm_CryptoStackFacade[AuthenticationConnectionIndex].AuthenticationResult = E_NOT_OK;
    Dcm_CryptoStackFacade[AuthenticationConnectionIndex].KeyMCallbackPending = FALSE;
    Dcm_CryptoStackFacade[AuthenticationConnectionIndex].CsmCallbackPending = FALSE;
    Dcm_Authentication_GeneratedLength[AuthenticationConnectionIndex] = 0U;
    Dcm_Authentication_VerificationResult[AuthenticationConnectionIndex] = CRYPTO_E_VER_NOT_OK;
  }

  DBG_DCM_CRYPTOSTACKFACADE_INIT_EXIT();
}

/* !LINKSTO Dcm.Dsn.IB.CryptoStackFacade.CancelOperation,1 */
FUNC(void, DCM_CODE) Dcm_CryptoStackFacade_CancelOperation(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  Dcm_CryptoOperationType Operation
)
{
  uint32 JobId = 0U;

  DBG_DCM_CRYPTOSTACKFACADE_CANCELOPERATION_ENTRY(AuthenticationConnectionIndex, Operation);

  DCM_PRECONDITION_ASSERT((AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS),
                           DCM_INTERNAL_API_ID);

  if (DCM_CRYPTOOPERATION_VERIFYCERTIFICATE != Operation)
  {
    /* Check if callback Dcm_CsmAsyncJobFinished() is in a meanwhile received
       in order to avoid calling Csm_CancelJob() for the RandomGenerate job which does not run anymore. */
    if ((DCM_CRYPTOOPERATION_CREATECHALLENGE == Operation) &&
        (Dcm_CryptoStackFacade[AuthenticationConnectionIndex].CsmCallbackPending == TRUE))
    {
      JobId = Dcm_AuthenticationConfigPtr->AuthenticationConnection[AuthenticationConnectionIndex].RandomGenerateJobId;
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.LimitRCRRP.CsmJobRandomGenerateCancellation.InvokeCsmCancelJob,1
         !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.ProtocolPreemption.CsmJobRandomGenerateCancellation.InvokeCsmCancelJob,1
         !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.LimitRCRRP.CsmJobRandomGenerateCancellation.InvokeCsmCancelJob,1
         !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.ProtocolPreemption.CsmJobRandomGenerateCancellation.InvokeCsmCancelJob,1 */
      (void)Csm_CancelJob(JobId, 0U/* unused parameter */);
    }
    /* Check if callback Dcm_CsmAsyncJobFinished() is in a meanwhile received
       in order to avoid calling Csm_CancelJob() for the VerifySignature job which does not run anymore. */
    else if ((DCM_CRYPTOOPERATION_VERIFYSIGNATURE == Operation) &&
             (Dcm_CryptoStackFacade[AuthenticationConnectionIndex].CsmCallbackPending == TRUE))
    {
      JobId = Dcm_AuthenticationConfigPtr->AuthenticationConnection[AuthenticationConnectionIndex].SignatureVerifyJobId;
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.LimitRCRRP.CsmJobSignatureVerifyCancellation.InvokeCsmCancelJob,1
         !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.ProtocolPreemption.CsmJobSignatureVerifyCancellation.InvokeCsmCancelJob,1 */
      (void)Csm_CancelJob(JobId, 0U/* unused parameter */);
    }
#if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON)
    /* Check if callback Dcm_CsmAsyncJobFinished() is in a meanwhile received
       in order to avoid calling Csm_CancelJob() for the SignatureGenerate job which does not run anymore. */
    else if ((DCM_CRYPTOOPERATION_SIGNCHALLENGE == Operation) &&
             (Dcm_CryptoStackFacade[AuthenticationConnectionIndex].CsmCallbackPending == TRUE))
    {
      JobId = Dcm_SignatureGenerateJobDescriptor[Dcm_AuthenticationConfigPtr->AuthenticationConnection[AuthenticationConnectionIndex].SignatureGenerateJobDescriptorIndex].SignatureGenerateJobId;
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.LimitRCRRP.CsmJobSignatureGenerateCancellation.InvokeCsmCancelJob,1
         !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.ProtocolPreemption.CsmJobSignatureGenerateCancellation.InvokeCsmCancelJob,1 */
      (void)Csm_CancelJob(JobId, 0U/* unused parameter */);
    }
#endif /* #if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON) */
    else
    {
#if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON)
      DCM_PRECONDITION_ASSERT((DCM_CRYPTOOPERATION_CREATECHALLENGE == Operation) ||
                              (DCM_CRYPTOOPERATION_SIGNCHALLENGE == Operation) ||
                              (DCM_CRYPTOOPERATION_VERIFYSIGNATURE == Operation),
                              DCM_INTERNAL_API_ID);
#else
      DCM_PRECONDITION_ASSERT((DCM_CRYPTOOPERATION_CREATECHALLENGE == Operation) ||
                              (DCM_CRYPTOOPERATION_VERIFYSIGNATURE == Operation),
                              DCM_INTERNAL_API_ID);
#endif /* #if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON) */

      /* Csm callback is meanwhile received, no need to call Csm_CancelJob */
    }
  }
  else
  {
    /* Other job cannot be cancelled */
    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.ProtocolPreemption.KeyMJobCancellation.Discard,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.ProtocolPreemption.KeyMJobCancellation.Discard,1 */
  }

  DBG_DCM_CRYPTOSTACKFACADE_CANCELOPERATION_EXIT(AuthenticationConnectionIndex, Operation);
}

/* !LINKSTO Dcm.Dsn.IB.CryptoStackFacade.CreateChallenge,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_CryptoStackFacade_CreateChallenge(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  uint16 LengthOfChallenge,
  P2VAR(uint8, AUTOMATIC, DCM_VAR) ChallengeServer,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode
)
{
  Std_ReturnType OperationResult = E_NOT_OK;
  Std_ReturnType RetVal = E_NOT_OK;
  uint32 JobId = 0U;

  DBG_DCM_CRYPTOSTACKFACADE_CREATECHALLENGE_ENTRY(AuthenticationConnectionIndex, LengthOfChallenge, ChallengeServer, ErrorCode);

  DCM_PRECONDITION_ASSERT((AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS),
                           DCM_INTERNAL_API_ID);

  JobId = Dcm_AuthenticationConfigPtr->AuthenticationConnection[AuthenticationConnectionIndex].RandomGenerateJobId;

  /* create server challenge is an asynchronous job */
  Dcm_Authentication_GeneratedLength[AuthenticationConnectionIndex] = LengthOfChallenge;
  /* Set flag now to avoid concurrency issue. Flag will be changed in context of
     callback Dcm_CsmAsyncJobFinished() after api Csm_RadnomGenerate() returns E_OK */
  Dcm_CryptoStackFacade[AuthenticationConnectionIndex].CsmCallbackPending = TRUE;
  /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsCertificateValid.InvokeCsmRandomGenerate,1 */
  /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsCertificateValid.InvokeCsmRandomGenerate,1 */
  OperationResult = Csm_RandomGenerate(JobId, ChallengeServer,
                                       &Dcm_Authentication_GeneratedLength[AuthenticationConnectionIndex]);

  switch (OperationResult)
  {
    case E_OK:
      /* E_OK: request successful */
      RetVal = E_OK;
      break;

    case E_NOT_OK:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.CsmRandomGenerate.ReturnsNotOK.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.CsmRandomGenerate.ReturnsNotOK.TransmitNRC0x10,1*/
      /* E_NOT_OK: request failed */
#if (DCM_DSP_AUTHENTICATION_CRYPTO_VARIANT == DCM_AUTHENTICATION_CRYPTO_VARIANT_BEFORE_AUTOSAR_R20_11)
    case CRYPTO_E_QUEUE_FULL:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateUnidirectional.CsmRandomGenerate.ReturnsQueueFull.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.CsmRandomGenerate.ReturnsQueueFull.TransmitNRC0x10,1 */
      /* CRYPTO_E_QUEUE_FULL: request failed, the queue is full */
    case CRYPTO_E_ENTROPY_EXHAUSTION:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateUnidirectional.CsmRandomGenerate.ReturnsEntropyExhaustion.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.CsmRandomGenerate.ReturnsEntropyExhaustion.TransmitNRC0x10,1 */
      /* CRYPTO_E_ENTROPY_EXHAUSTION: request failed, entropy of random number generator is exhausted -> reseed */
#else
    case CRYPTO_E_ENTROPY_EXHAUSTED:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateUnidirectional.CsmRandomGenerate.ReturnsEntropyExhausted.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.CsmRandomGenerate.ReturnsEntropyExhausted.TransmitNRC0x10,1 */
      /* CRYPTO_E_ENTROPY_EXHAUSTED: request failed, entropy of random number generator is exhausted -> reseed */
#endif
      Dcm_CryptoStackFacade[AuthenticationConnectionIndex].CsmCallbackPending = FALSE;
      *ErrorCode = DCM_E_GENERALREJECT;
      RetVal = E_NOT_OK;
      break;

    case CRYPTO_E_BUSY:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.CsmRandomGenerate.ReturnsBusy.TransmitNRC0x21,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.CsmRandomGenerate.ReturnsBusy.TransmitNRC0x21,1 */
      /* CRYPTO_E_BUSY: request failed, service is still busy */
      Dcm_CryptoStackFacade[AuthenticationConnectionIndex].CsmCallbackPending = FALSE;
      *ErrorCode = DCM_E_BUSYREPEATREQUEST;
      RetVal = E_NOT_OK;
      break;

    default:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateUnidirectional.CsmRandomGenerate.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.CsmRandomGenerate.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateUnidirectional.CsmRandomGenerate.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.CsmRandomGenerate.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
      Dcm_CryptoStackFacade[AuthenticationConnectionIndex].CsmCallbackPending = FALSE;
      *ErrorCode = DCM_E_GENERALREJECT;
      RetVal = E_NOT_OK;
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateUnidirectional.CsmRandomGenerate.ReturnsUnsupportedCode.ReportDETError,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.CsmRandomGenerate.ReturnsUnsupportedCode.ReportDETError,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateUnidirectional.CsmRandomGenerate.ReturnsUnsupportedCode.ReportDETError,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.CsmRandomGenerate.ReturnsUnsupportedCode.ReportDETError,1 */
      DCM_DET_REPORT_ERROR(DCM_SVCID_CSMRANDOMGENERATE, DCM_E_INTERFACE_RETURN_VALUE);
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
      break;
  }

  DBG_DCM_CRYPTOSTACKFACADE_CREATECHALLENGE_EXIT(RetVal, AuthenticationConnectionIndex, LengthOfChallenge, ChallengeServer, ErrorCode);
  return RetVal;
}

/* !LINKSTO Dcm.Dsn.IB.CryptoStackFacade.GetAuthenticationRole,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_CryptoStackFacade_GetAuthenticationRole(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  P2VAR(uint8, AUTOMATIC, DCM_VAR) AuthenticationRole,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode
)
{
  Std_ReturnType OperationResult = E_NOT_OK;
  Std_ReturnType RetVal = E_NOT_OK;
  uint16 CertificateId = 0U;
  uint16 RoleElementId = 0U;
  uint32 CertElementDataLength = DCM_DSP_AUTHENTICATION_ROLE_SIZE;
  uint8 CertAuthenticationRole[DCM_DSP_AUTHENTICATION_ROLE_SIZE];

  DBG_DCM_CRYPTOSTACKFACADE_GETAUTHENTICATIONROLE_ENTRY(AuthenticationConnectionIndex, AuthenticationRole, ErrorCode);

  DCM_PRECONDITION_ASSERT((AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS),
                           DCM_INTERNAL_API_ID);

  CertificateId = Dcm_AuthenticationConfigPtr->AuthenticationConnection[AuthenticationConnectionIndex].KeyMCertificateId;
  RoleElementId = Dcm_AuthenticationConfigPtr->AuthenticationConnection[AuthenticationConnectionIndex].RoleElementId;

  /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsOK.VerifyResult.VerOK.InvokeKeyMCertElementGet,1 */
  OperationResult = KeyM_CertElementGet(CertificateId,
                                        RoleElementId,
                                        &CertAuthenticationRole[0U],
                                        &CertElementDataLength);

  switch (OperationResult)
  {
    case E_OK:
      /* E_OK: Element found and data provided in the buffer */
      if (DCM_DSP_AUTHENTICATION_ROLE_SIZE == CertElementDataLength)
      {
        TS_MemCpy(AuthenticationRole, CertAuthenticationRole, DCM_DSP_AUTHENTICATION_ROLE_SIZE);
        RetVal = E_OK;
      }
      else
      {
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.KeyMCertElementGet.ReturnsOK.InvalidRoleSize.DcmDspAuthenticationGeneralNRCModeRuleRefNotConfigured.TransmitNRC0x55,1 */
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.KeyMCertElementGet.ReturnsOK.InvalidRoleSize.DcmDspAuthenticationGeneralNRCModeRuleFalse.TransmitNRC0x55,1 */
        *ErrorCode = DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDCONTENT;
        RetVal = E_NOT_OK;
      }
      break;

    case E_NOT_OK:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.KeyMCertElementGet.ReturnsNotOK.DcmDspAuthenticationGeneralNRCModeRuleRefNotConfigured.TransmitNRC0x55,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.KeyMCertElementGet.ReturnsNotOK.DcmDspAuthenticationGeneralNRCModeRuleFalse.TransmitNRC0x55,1 */
      /* E_NOT_OK: Element data not found */
      *ErrorCode = DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDCONTENT;
      RetVal = E_NOT_OK;
      break;

    case KEYM_E_PARAMETER_MISMATCH:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.KeyMCertElementGet.ReturnsParameterMismatch.TransmitNRC0x10,1 */
      /* KEYM_E_PARAMETER_MISMATCH: Certificate ID or certificate element ID invalid */
    case KEYM_E_KEY_CERT_SIZE_MISMATCH:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.KeyMCertElementGet.ReturnsCertificateSizeMismatch.TransmitNRC0x10,1 */
      /* KEYM_E_KEY_CERT_SIZE_MISMATCH: Provided buffer for the certificate element too small */
    case KEYM_E_KEY_CERT_EMPTY:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.KeyMCertElementGet.ReturnsCertificateEmpty.TransmitNRC0x10,1 */
      /* KEYM_E_KEY_CERT_EMPTY: No certificate data available, the certificate slot is empty */
    case KEYM_E_KEY_CERT_INVALID:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.KeyMCertElementGet.ReturnsCertificateInvalid.TransmitNRC0x10,1 */
      /* KEYM_E_KEY_CERT_INVALID: The certificate is not valid or has not yet been verified */
      *ErrorCode = DCM_E_GENERALREJECT;
      RetVal = E_NOT_OK;
      break;

    default:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.KeyMCertElementGet.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
      *ErrorCode = DCM_E_GENERALREJECT;
      RetVal = E_NOT_OK;
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.KeyMCertElementGet.ReturnsUnsupportedCode.ReportDETError,1 */
      DCM_DET_REPORT_ERROR(DCM_SVCID_KEYMCERTELEMENTGET, DCM_E_INTERFACE_RETURN_VALUE);
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
      break;
  }

  DBG_DCM_CRYPTOSTACKFACADE_GETAUTHENTICATIONROLE_EXIT(RetVal, AuthenticationConnectionIndex, AuthenticationRole, ErrorCode);
  return RetVal;
}

/* !LINKSTO Dcm.Dsn.IB.CryptoStackFacade.SetCertificate,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_CryptoStackFacade_SetCertificate(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  P2VAR(uint8, AUTOMATIC, DCM_VAR) Certificate,
  uint32 LengthOfCertificate,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode
)
{
  Std_ReturnType OperationResult = E_NOT_OK;
  Std_ReturnType RetVal = E_NOT_OK;
  uint16 CertificateId = 0U;
  KeyM_CertDataType CertificateData;

  DBG_DCM_CRYPTOSTACKFACADE_SETCERTIFICATE_ENTRY(AuthenticationConnectionIndex, Certificate, LengthOfCertificate, ErrorCode);

  DCM_PRECONDITION_ASSERT((AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS),
                           DCM_INTERNAL_API_ID);

  CertificateId = Dcm_AuthenticationConfigPtr->AuthenticationConnection[AuthenticationConnectionIndex].KeyMCertificateId;

  CertificateData.certData = Certificate;
  CertificateData.certDataLength = LengthOfCertificate;

  /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.InvokeKeyMSetCertificate,1 */
  /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.InvokeKeyMSetCertificate,1 */
  OperationResult = KeyM_SetCertificate(CertificateId, &CertificateData);

  switch (OperationResult)
  {
    case E_OK:
      /* E_OK: Certificate accepted */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.KeyMSetCertificate.ReturnsOK.InvokeKeyMVerifyCertificate,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMSetCertificate.ReturnsOK.InvokeKeyMVerifyCertificate,1 */
      RetVal = E_OK;
      break;

    case E_NOT_OK:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.KeyMSetCertificate.ReturnsNotOK.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMSetCertificate.ReturnsNotOK.TransmitNRC0x10,1 */
      /* E_NOT_OK: Certificate could not be set */
    case KEYM_E_PARAMETER_MISMATCH:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.KeyMSetCertificate.ReturnsInvalidCertId.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMSetCertificate.ReturnsInvalidCertId.TransmitNRC0x10,1 */
      /* KEYM_E_PARAMETER_MISMATCH: Parameter do not match with expected value */
      *ErrorCode = DCM_E_GENERALREJECT;
      RetVal = E_NOT_OK;
      break;

    case KEYM_E_KEY_CERT_SIZE_MISMATCH:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.KeyMSetCertificate.ReturnsInvalidCertSize.TransmitNRC0x13,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMSetCertificate.ReturnsInvalidCertSize.TransmitNRC0x13,1 */
      /* KEYM_E_KEY_CERT_SIZE_MISMATCH: Parameter size doesn't match */
      *ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
      RetVal = E_NOT_OK;
      break;

    case KEYM_E_BUSY:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.KeyMSetCertificate.ReturnsBusy.TransmitNRC0x21,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMSetCertificate.ReturnsBusy.TransmitNRC0x21,1 */
      /* KEYM_E_BUSY: Request failed, service is still busy */
      *ErrorCode = DCM_E_BUSYREPEATREQUEST;
      RetVal = E_NOT_OK;
      break;

    default:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.KeyMSetCertificate.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMSetCertificate.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
      *ErrorCode = DCM_E_GENERALREJECT;
      RetVal = E_NOT_OK;
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.KeyMSetCertificate.ReturnsUnsupportedCode.ReportDETError,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMSetCertificate.ReturnsUnsupportedCode.ReportDETError,1 */
      DCM_DET_REPORT_ERROR(DCM_SVCID_KEYMSETCERTIFICATE, DCM_E_INTERFACE_RETURN_VALUE);
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
      break;
  }

  DBG_DCM_CRYPTOSTACKFACADE_SETCERTIFICATE_EXIT(RetVal, AuthenticationConnectionIndex, Certificate, LengthOfCertificate, ErrorCode);
  return RetVal;
}

#if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON)
/* !LINKSTO Dcm.Dsn.IB.CryptoStackFacade.GetCertificate,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_CryptoStackFacade_GetCertificate(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  P2VAR(Dcm_AuthenticationCertificateType, AUTOMATIC, DCM_VAR) CertificateServer,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode
)
{
  Std_ReturnType OperationResult = E_NOT_OK;
  Std_ReturnType RetVal = E_NOT_OK;
  uint16 CertificateServerId = 0U;
  KeyM_CertDataType CertificateData;

  DCM_PRECONDITION_ASSERT((AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS),DCM_INTERNAL_API_ID);

  CertificateServerId = Dcm_AuthenticationConfigPtr->AuthenticationConnection[AuthenticationConnectionIndex].KeyMServerCertificateId;

  DBG_DCM_CRYPTOSTACKFACADE_GETCERTIFICATE_ENTRY(AuthenticationConnectionIndex, ErrorCode);

  CertificateData.certData = CertificateServer->Certificate;
  CertificateData.certDataLength = CertificateServer->LengthOfCertificate;

  /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsOK.NonZeroLengthOfProofOfOwnershipServer.InvokeKeyMGetCertificate,1 */
  OperationResult = KeyM_GetCertificate(CertificateServerId, &CertificateData);

  switch (OperationResult)
  {
    case E_OK:
      if (0U != CertificateData.certDataLength)
      {
        /* E_OK: Certificate data available and provided. */
        CertificateServer->LengthOfCertificate = CertificateData.certDataLength;
        RetVal = E_OK;
      }
      else
      {
        /* E_OK: Certificate data not provided. */
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMGetCertificate.ReturnsOK.ZeroLengthOfCertificateServer.TransmitNRC0x10,1 */
        *ErrorCode = DCM_E_GENERALREJECT;
        RetVal = E_NOT_OK;
#if (DCM_DEV_ERROR_DETECT == STD_ON)
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMGetCertificate.ReturnsOK.ZeroLengthOfCertificateServer.ReportDETError,1 */
        DCM_DET_REPORT_ERROR(DCM_SVCID_KEYMGETCERTIFICATE, DCM_E_INVALID_VALUE);
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
      }
      break;

    case E_NOT_OK:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMGetCertificate.ReturnsNotOK.TransmitNRC0x10,1 */
      /* E_NOT_OK: Operation not accepted due to an internal error. */
    case KEYM_E_PARAMETER_MISMATCH:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMGetCertificate.ReturnsParameterMismatch.TransmitNRC0x10,1 */
      /* KEYM_E_PARAMETER_MISMATCH: Certificate ID invalid. */
    case KEYM_E_KEY_CERT_SIZE_MISMATCH:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMGetCertificate.ReturnsCertificateSizeMismatch.TransmitNRC0x10,1 */
      /* KEYM_E_KEY_CERT_SIZE_MISMATCH: Provided buffer for the certificate too small. */
    case KEYM_E_KEY_CERT_EMPTY:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMGetCertificate.ReturnsCertificateEmpty.TransmitNRC0x10,1 */
      /* KEYM_E_KEY_CERT_EMPTY: No certificate data available, the certificate slot is empty. */
    case KEYM_E_KEY_CERT_READ_FAIL:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMGetCertificate.ReturnsCertificateReadFail.TransmitNRC0x10,1 */
      /* KEYM_E_KEY_CERT_READ_FAIL: Certificate cannot be provided, access denied. */
      *ErrorCode = DCM_E_GENERALREJECT;
      RetVal = E_NOT_OK;
      break;

    case KEYM_E_BUSY:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMGetCertificate.ReturnsBusy.TransmitNRC0x21,1 */
      /* KEYM_E_BUSY: KeyM busy with other operation. */
      *ErrorCode = DCM_E_BUSYREPEATREQUEST;
      RetVal = E_NOT_OK;
      break;

    default:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMGetCertificate.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
      *ErrorCode = DCM_E_GENERALREJECT;
      RetVal = E_NOT_OK;
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMGetCertificate.ReturnsUnsupportedCode.ReportDETError,1 */
      DCM_DET_REPORT_ERROR(DCM_SVCID_KEYMGETCERTIFICATE, DCM_E_INTERFACE_RETURN_VALUE);
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
      break;
  }

  DBG_DCM_CRYPTOSTACKFACADE_GETCERTIFICATE_EXIT(RetVal, AuthenticationConnectionIndex, ErrorCode);
  return RetVal;
}

/* !LINKSTO Dcm.Dsn.IB.CryptoStackFacade.SignChallenge,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_CryptoStackFacade_SignChallenge(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  P2CONST(uint8, AUTOMATIC, DCM_VAR) ChallengeClient,
  uint32 LengthOfChallenge,
  P2VAR(uint8, AUTOMATIC, DCM_VAR) SignedChallenge,
  uint32 LengthOfSignedChallenge,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode
)
{
  Std_ReturnType OperationResult = E_NOT_OK;
  Std_ReturnType RetVal = E_NOT_OK;
  uint32 JobId = 0U;

  DBG_DCM_CRYPTOSTACKFACADE_SIGNCHALLENGE_ENTRY(AuthenticationConnectionIndex, ChallengeClient, LengthOfChallenge, SignedChallenge, LengthOfSignedChallenge, ErrorCode);

  DCM_PRECONDITION_ASSERT((AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS),
                           DCM_INTERNAL_API_ID);

  JobId = Dcm_SignatureGenerateJobDescriptor[Dcm_AuthenticationConfigPtr->
                     AuthenticationConnection[AuthenticationConnectionIndex].
                     SignatureGenerateJobDescriptorIndex].SignatureGenerateJobId;

  /* sign client challenge is an asynchronous job */
  Dcm_Authentication_GeneratedLength[AuthenticationConnectionIndex] = LengthOfSignedChallenge;
  /* Set flag now to avoid concurrency issue. Flag will be changed in context of
     callback Dcm_CsmAsyncJobFinished() after api Csm_SignatureGenerate() returns E_OK */
  Dcm_CryptoStackFacade[AuthenticationConnectionIndex].CsmCallbackPending = TRUE;

  /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsOK.LengthOfGeneratedRandomNumberSmaller.InvokeCsmSignatureGenerate,1 */
  /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsOK.LengthOfGeneratedRandomNumberPrecise.InvokeCsmSignatureGenerate,1 */
  OperationResult = Csm_SignatureGenerate(JobId, CRYPTO_OPERATIONMODE_SINGLECALL,
                                          ChallengeClient, LengthOfChallenge,
                                          SignedChallenge,
                                          &Dcm_Authentication_GeneratedLength[AuthenticationConnectionIndex]);

  switch (OperationResult)
  {
    case E_OK:
      /* E_OK: request successful */
      RetVal = E_OK;
      break;

    case CRYPTO_E_BUSY:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.CsmSignatureGenerate.ReturnsBusy.TransmitNRC0x21,1 */
      /* CRYPTO_E_BUSY: request failed, service is still busy */
      Dcm_CryptoStackFacade[AuthenticationConnectionIndex].CsmCallbackPending = FALSE;
      *ErrorCode = DCM_E_BUSYREPEATREQUEST;
      RetVal = E_NOT_OK;
      break;

    case E_NOT_OK:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.CsmSignatureGenerate.ReturnsNotOK.TransmitNRC0x10,1 */
      /* E_NOT_OK: request failed */
    case CRYPTO_E_KEY_NOT_VALID:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.CsmSignatureGenerate.ReturnsKeyNotValid.TransmitNRC0x10,1 */
      /* CRYPTO_E_KEY_NOT_VALID: request failed, the key's state is "invalid" */
#if (DCM_DSP_AUTHENTICATION_CRYPTO_VARIANT == DCM_AUTHENTICATION_CRYPTO_VARIANT_BEFORE_AUTOSAR_R20_11)
    case CRYPTO_E_QUEUE_FULL:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.CsmSignatureGenerate.ReturnsQueueFull.TransmitNRC0x10,1 */
      /* CRYPTO_E_QUEUE_FULL: request failed, the queue is full */
    case CRYPTO_E_SMALL_BUFFER:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.CsmSignatureGenerate.ReturnsSmallBuffer.TransmitNRC0x10,1 */
      /* CRYPTO_E_SMALL_BUFFER: the provided buffer is too small to store the result */
#else
    case CRYPTO_E_KEY_SIZE_MISMATCH:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.CsmSignatureGenerate.ReturnsKeySizeMismatch.TransmitNRC0x10,1 */
      /* CRYPTO_E_KEY_SIZE_MISMATCH: request failed, a key element has the wrong size */
    case CRYPTO_E_KEY_EMPTY:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.CsmSignatureGenerate.ReturnsKeyEmpty.TransmitNRC0x10,1 */
      /* CRYPTO_E_KEY_EMPTY: request failed because of uninitialized source key element */
#endif
      Dcm_CryptoStackFacade[AuthenticationConnectionIndex].CsmCallbackPending = FALSE;
      *ErrorCode = DCM_E_GENERALREJECT;
      RetVal = E_NOT_OK;
      break;

    default:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.CsmSignatureGenerate.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.CsmSignatureGenerate.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
      Dcm_CryptoStackFacade[AuthenticationConnectionIndex].CsmCallbackPending = FALSE;
      *ErrorCode = DCM_E_GENERALREJECT;
      RetVal = E_NOT_OK;
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.CsmSignatureGenerate.ReturnsUnsupportedCode.ReportDETError,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.CsmSignatureGenerate.ReturnsUnsupportedCode.ReportDETError,1 */
      DCM_DET_REPORT_ERROR(DCM_SVCID_CSMSIGNATUREGENERATE, DCM_E_INTERFACE_RETURN_VALUE);
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
      break;
  }

  DBG_DCM_CRYPTOSTACKFACADE_SIGNCHALLENGE_EXIT(RetVal, AuthenticationConnectionIndex, ChallengeClient, LengthOfChallenge, SignedChallenge, LengthOfSignedChallenge, ErrorCode)
  return RetVal;
}
#endif /* #if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON) */

/* !LINKSTO Dcm.Dsn.IB.CryptoStackFacade.VerifyCertificate,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_CryptoStackFacade_VerifyCertificate(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode
)
{
  Std_ReturnType OperationResult = E_NOT_OK;
  Std_ReturnType RetVal = E_NOT_OK;
  uint16 CertificateId = 0U;

  DBG_DCM_CRYPTOSTACKFACADE_VERIFYCERTIFICATE_ENTRY(AuthenticationConnectionIndex, ErrorCode);

  DCM_PRECONDITION_ASSERT((AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS),
                           DCM_INTERNAL_API_ID);

  CertificateId = Dcm_AuthenticationConfigPtr->AuthenticationConnection[AuthenticationConnectionIndex].KeyMCertificateId;

  /* Set flag now to avoid concurrency issue. Flag will be changed in context of
     callback Dcm_KeyMAsyncCertificateVerifyFinished() after api KeyM_VerifyCertificate() returns E_OK */
  Dcm_CryptoStackFacade[AuthenticationConnectionIndex].KeyMCallbackPending = TRUE;
  /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.KeyMSetCertificate.ReturnsOK.InvokeKeyMVerifyCertificate,1 */
  /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMSetCertificate.ReturnsOK.InvokeKeyMVerifyCertificate,1 */
  OperationResult = KeyM_VerifyCertificate(CertificateId);

  switch (OperationResult)
  {
    case E_OK:
      /* E_OK: Certificate verification request accepted */
      RetVal = E_OK;
      break;

    case E_NOT_OK:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.KeyMVerifyCertificate.ReturnsNotOK.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMVerifyCertificate.ReturnsNotOK.TransmitNRC0x10,1 */
      /* E_NOT_OK: Operation not accepted due to an internal error */
    case KEYM_E_PARAMETER_MISMATCH:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.KeyMVerifyCertificate.ReturnsMismatch.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMVerifyCertificate.ReturnsMismatch.TransmitNRC0x10,1 */
      /* KEYM_E_PARAMETER_MISMATCH: Certificate ID invalid */
    case KEYM_E_KEY_CERT_EMPTY:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.KeyMVerifyCertificate.ReturnsEmptySlot.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMVerifyCertificate.ReturnsEmptySlot.TransmitNRC0x10,1 */
      /* KEYM_E_KEY_CERT_EMPTY: One of the certificate slots are empty */
    case KEYM_E_CERT_INVALID_CHAIN_OF_TRUST:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.KeyMVerifyCertificate.ReturnsInvalidChainOfTrust.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMVerifyCertificate.ReturnsInvalidChainOfTrust.TransmitNRC0x10,1 */
      /* KEYM_E_CERT_INVALID_CHAIN_OF_TRUST: An upper certificate is not valid */
      Dcm_CryptoStackFacade[AuthenticationConnectionIndex].KeyMCallbackPending = FALSE;
      *ErrorCode = DCM_E_GENERALREJECT;
      RetVal = E_NOT_OK;
      break;

    case KEYM_E_BUSY:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.KeyMVerifyCertificate.ReturnsBusy.TransmitNRC0x21,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMVerifyCertificate.ReturnsBusy.TransmitNRC0x21,1 */
      /* KEYM_E_BUSY: Validation cannot be performed yet. KeyM is currently busy with other jobs */
      Dcm_CryptoStackFacade[AuthenticationConnectionIndex].KeyMCallbackPending = FALSE;
      *ErrorCode = DCM_E_BUSYREPEATREQUEST;
      RetVal = E_NOT_OK;
      break;

    default:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.KeyMVerifyCertificate.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMVerifyCertificate.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
      Dcm_CryptoStackFacade[AuthenticationConnectionIndex].KeyMCallbackPending = FALSE;
      *ErrorCode = DCM_E_GENERALREJECT;
      RetVal = E_NOT_OK;
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.KeyMVerifyCertificate.ReturnsUnsupportedCode.ReportDETError,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMVerifyCertificate.ReturnsUnsupportedCode.ReportDETError,1 */
      DCM_DET_REPORT_ERROR(DCM_SVCID_KEYMVERIFYCERTIFICATE, DCM_E_INTERFACE_RETURN_VALUE);
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
      break;
  }

  DBG_DCM_CRYPTOSTACKFACADE_VERIFYCERTIFICATE_EXIT(RetVal, AuthenticationConnectionIndex, ErrorCode);
  return RetVal;
}

/* !LINKSTO Dcm.Dsn.IB.CryptoStackFacade.VerifySignature,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_CryptoStackFacade_VerifySignature(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  P2CONST(uint8, AUTOMATIC, DCM_VAR) Data,
  uint16 LengthOfData,
  P2CONST(uint8, AUTOMATIC, DCM_VAR) Signature,
  uint16 LengthOfSignature,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode
)
{
  Std_ReturnType OperationResult = E_NOT_OK;
  Std_ReturnType RetVal = E_NOT_OK;
  uint32 JobId = 0U;

  DBG_DCM_CRYPTOSTACKFACADE_VERIFYSIGNATURE_ENTRY(AuthenticationConnectionIndex, Data, LengthOfData, Signature, LengthOfSignature, ErrorCode);

  DCM_PRECONDITION_ASSERT((AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS),
                           DCM_INTERNAL_API_ID);

  JobId = Dcm_AuthenticationConfigPtr->AuthenticationConnection[AuthenticationConnectionIndex].SignatureVerifyJobId;

  /* proof of ownership verification is an asynchronous job; the verification result will be provided by the callback */
  /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.InvokeCsmSignatureVerify,1 */
  Dcm_Authentication_VerificationResult[AuthenticationConnectionIndex] = CRYPTO_E_VER_NOT_OK;
  /* Set flag now to avoid concurrency issue. Flag will be changed in context of
     callback Dcm_CsmAsyncJobFinished() after api Csm_SignatureVerify() returns E_OK */
  Dcm_CryptoStackFacade[AuthenticationConnectionIndex].CsmCallbackPending = TRUE;
  OperationResult = Csm_SignatureVerify(JobId, CRYPTO_OPERATIONMODE_SINGLECALL, Data, LengthOfData,
                                        Signature, LengthOfSignature,
                                        &Dcm_Authentication_VerificationResult[AuthenticationConnectionIndex]);

  switch (OperationResult)
  {
    case E_OK:
      /* E_OK: request successful; set pending flag */
      RetVal = E_OK;
      break;

    case CRYPTO_E_BUSY:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.CsmSignatureVerify.ReturnsBusy.TransmitNRC0x21,1 */
      /* CRYPTO_E_BUSY: request failed, service is still busy */
      Dcm_CryptoStackFacade[AuthenticationConnectionIndex].CsmCallbackPending = FALSE;
      *ErrorCode = DCM_E_BUSYREPEATREQUEST;
      RetVal = E_NOT_OK;
      break;

    case E_NOT_OK:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.CsmSignatureVerify.ReturnsNotOK.TransmitNRC0x10,1 */
      /* E_NOT_OK: request failed */
    case CRYPTO_E_KEY_NOT_VALID:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.CsmSignatureVerify.ReturnsKeyNotValid.TransmitNRC0x10,1 */
      /* CRYPTO_E_KEY_NOT_VALID: request failed, the key's state is "invalid" */
#if (DCM_DSP_AUTHENTICATION_CRYPTO_VARIANT == DCM_AUTHENTICATION_CRYPTO_VARIANT_BEFORE_AUTOSAR_R20_11)
    case CRYPTO_E_QUEUE_FULL:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.ProofOfOwnership.CsmSignatureVerify.ReturnsQueueFull.TransmitNRC0x10,1 */
      /* CRYPTO_E_QUEUE_FULL: request failed, the queue is full */
    case CRYPTO_E_SMALL_BUFFER:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.ProofOfOwnership.CsmSignatureVerify.ReturnsSmallBuffer.TransmitNRC0x10,1 */
      /* CRYPTO_E_SMALL_BUFFER: the provided buffer is too small to store the result */
#else
    case CRYPTO_E_KEY_SIZE_MISMATCH:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.ProofOfOwnership.CsmSignatureVerify.ReturnsKeySizeMismatch.TransmitNRC0x10,1 */
      /* CRYPTO_E_KEY_SIZE_MISMATCH: request failed, a key element has the wrong size */
    case CRYPTO_E_KEY_EMPTY:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.ProofOfOwnership.CsmSignatureVerify.ReturnsKeyEmpty.TransmitNRC0x10,1 */
      /* CRYPTO_E_KEY_EMPTY: request failed because of uninitialized source key element */
#endif
      Dcm_CryptoStackFacade[AuthenticationConnectionIndex].CsmCallbackPending = FALSE;
      *ErrorCode = DCM_E_GENERALREJECT;
      RetVal = E_NOT_OK;
      break;

    default:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.ProofOfOwnership.CsmSignatureVerify.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.ProofOfOwnership.CsmSignatureVerify.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
      Dcm_CryptoStackFacade[AuthenticationConnectionIndex].CsmCallbackPending = FALSE;
      *ErrorCode = DCM_E_GENERALREJECT;
      RetVal = E_NOT_OK;
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.ProofOfOwnership.CsmSignatureVerify.ReturnsUnsupportedCode.ReportDETError,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.ProofOfOwnership.CsmSignatureVerify.ReturnsUnsupportedCode.ReportDETError,1 */
      DCM_DET_REPORT_ERROR(DCM_SVCID_CSMSIGNATUREVERIFY, DCM_E_INTERFACE_RETURN_VALUE);
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
      break;
  }

  DBG_DCM_CRYPTOSTACKFACADE_VERIFYSIGNATURE_EXIT(RetVal, AuthenticationConnectionIndex, Data, LengthOfData, Signature, LengthOfSignature, ErrorCode);
  return RetVal;
}

/* !LINKSTO Dcm.EB.UDSServices.AuthenticationService.DcmKeyMAsyncCertificateVerifyFinished.API,1 */
/* !LINKSTO Dcm.Dsn.IB.CryptoStackFacade.KeyMAsynJobFinishedCallback,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_KeyMAsyncCertificateVerifyFinished(
  KeyM_CertificateIdType CertId,
  KeyM_CertificateStatusType Result
)
{
  /* return value E_OK is expected (SWS_Dcm_91077) */
  const Std_ReturnType RetVal = E_OK;
  Dcm_NegativeResponseCodeType ErrorCode = DCM_E_GENERALREJECT;
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex = DCM_NUM_AUTHENTICATION_CONNECTIONS;

  DBG_DCM_KEYMASYNCCERTIFICATEVERIFYFINISHED_ENTRY(CertId, Result);

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized != TRUE)
  {
    /* !LINKSTO Dcm.EB.UDSServices.DcmKeyMAsyncCertificateVerifyFinished.DcmNotInitialized.ReportDETError,1 */
    DCM_DET_REPORT_ERROR(DCM_SVCID_KEYMASYNCCERTIFICATEVERIFYFINISHED, DCM_E_UNINIT);
  }
  else
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* search for pending callbacks and compare the CertId */
    /* Deviation TASKING-1 <+2> */
    for (AuthenticationConnectionIndex = 0U; AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS; AuthenticationConnectionIndex++)
    {
      if ((TRUE == Dcm_CryptoStackFacade[AuthenticationConnectionIndex].KeyMCallbackPending) &&
          (Dcm_AuthenticationConfigPtr->AuthenticationConnection[AuthenticationConnectionIndex].KeyMCertificateId == CertId))
      {
#if (DCM_DSP_AUTHENTICATION_CRYPTO_VARIANT == DCM_AUTHENTICATION_CRYPTO_VARIANT_AFTER_AUTOSAR_R20_11)
        /* KEYM_CERTIFICATE_PARSED_NOT_VALIDATED is an intermediate Result, not a final one. No action is taken. */
        if (Result != KEYM_CERTIFICATE_PARSED_NOT_VALIDATED)
#endif
        {
          /* clear pending flag */
          Dcm_CryptoStackFacade[AuthenticationConnectionIndex].KeyMCallbackPending = FALSE;

          switch (Result)
          {
            case KEYM_CERTIFICATE_VALID:
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsCertificateValid.InvokeCsmRandomGenerate,1 */
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsCertificateValid.InvokeCsmRandomGenerate,1 */
              /* Certificate successfully parsed and verified */
              ErrorCode = DCM_E_POSITIVERESPONSE;
              break;

            case KEYM_CERTIFICATE_INVALID:
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsCertificateInvalid.TransmitNRC0x10,1 */
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsCertificateInvalid.TransmitNRC0x10,1 */
              /* The certificate is invalid (unspedified failure) */
              ErrorCode = DCM_E_GENERALREJECT;
              break;

            case KEYM_E_CERTIFICATE_VALIDITY_PERIOD_FAIL:
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsValidityPeriodFailed.DcmDspAuthenticationGeneralNRCModeRuleRefNotConfigured.TransmitNRC0x50,1 */
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsValidityPeriodFailed.DcmDspAuthenticationGeneralNRCModeRuleFalse.TransmitNRC0x50,1 */
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsValidityPeriodFailed.DcmDspAuthenticationGeneralNRCModeRuleRefNotConfigured.TransmitNRC0x50,1 */
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsValidityPeriodFailed.DcmDspAuthenticationGeneralNRCModeRuleFalse.TransmitNRC0x50,1 */
              /* Certificate verification failed - Invalid Time Period */
              ErrorCode = DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDTIMEPERIOD;
              break;

            case KEYM_E_CERTIFICATE_SIGNATURE_FAIL:
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidSignature.DcmDspAuthenticationGeneralNRCModeRuleRefNotConfigured.TransmitNRC0x51,1 */
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidSignature.DcmDspAuthenticationGeneralNRCModeRuleFalse.TransmitNRC0x51,1 */
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidSignature.DcmDspAuthenticationGeneralNRCModeRuleRefNotConfigured.TransmitNRC0x51,1 */
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidSignature.DcmDspAuthenticationGeneralNRCModeRuleFalse.TransmitNRC0x51,1 */
              /* Certificate verification failed - Invalid Signature */
              ErrorCode = DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDSIGNATURE;
              break;

            case KEYM_E_CERTIFICATE_INVALID_CHAIN_OF_TRUST:
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidChainOfTrust.DcmDspAuthenticationGeneralNRCModeRuleRefNotConfigured.TransmitNRC0x52,1 */
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidChainOfTrust.DcmDspAuthenticationGeneralNRCModeRuleFalse.TransmitNRC0x52,1 */
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidChainOfTrust.DcmDspAuthenticationGeneralNRCModeRuleRefNotConfigured.TransmitNRC0x52,1 */
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidChainOfTrust.DcmDspAuthenticationGeneralNRCModeRuleFalse.TransmitNRC0x52,1 */
              /* Certificate verification failed - Invalid Chain of Trust */
              ErrorCode = DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDCHAINOFTRUST;
              break;

            case KEYM_E_CERTIFICATE_INVALID_TYPE:
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidType.DcmDspAuthenticationGeneralNRCModeRuleRefNotConfigured.TransmitNRC0x53,1 */
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidType.DcmDspAuthenticationGeneralNRCModeRuleFalse.TransmitNRC0x53,1 */
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidType.DcmDspAuthenticationGeneralNRCModeRuleRefNotConfigured.TransmitNRC0x53,1 */
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidType.DcmDspAuthenticationGeneralNRCModeRuleFalse.TransmitNRC0x53,1 */
              /* Certificate verification failed - Invalid Type */
              ErrorCode = DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDTYPE;
              break;

            case KEYM_E_CERTIFICATE_INVALID_FORMAT:
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidFormat.DcmDspAuthenticationGeneralNRCModeRuleRefNotConfigured.TransmitNRC0x54,1 */
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidFormat.DcmDspAuthenticationGeneralNRCModeRuleFalse.TransmitNRC0x54,1 */
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidFormat.DcmDspAuthenticationGeneralNRCModeRuleRefNotConfigured.TransmitNRC0x54,1 */
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidFormat.DcmDspAuthenticationGeneralNRCModeRuleFalse.TransmitNRC0x54,1 */
              /* Certificate verification failed - Invalid Format */
              ErrorCode = DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDFORMAT;
              break;

            case KEYM_E_CERTIFICATE_INVALID_CONTENT:
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidContent.DcmDspAuthenticationGeneralNRCModeRuleRefNotConfigured.TransmitNRC0x56,1 */
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidContent.DcmDspAuthenticationGeneralNRCModeRuleFalse.TransmitNRC0x56,1 */
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidContent.DcmDspAuthenticationGeneralNRCModeRuleRefNotConfigured.TransmitNRC0x56,1 */
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidContent.DcmDspAuthenticationGeneralNRCModeRuleFalse.TransmitNRC0x56,1 */
              /* Certificate verification failed - Invalid Content */
              ErrorCode = DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDSCOPE;
              break;

            case KEYM_E_CERTIFICATE_REVOKED:
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsCertificateRevoked.DcmDspAuthenticationGeneralNRCModeRuleRefNotConfigured.TransmitNRC0x57,1 */
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsCertificateRevoked.DcmDspAuthenticationGeneralNRCModeRuleFalse.TransmitNRC0x57,1 */
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsCertificateRevoked.DcmDspAuthenticationGeneralNRCModeRuleRefNotConfigured.TransmitNRC0x57,1 */
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsCertificateRevoked.DcmDspAuthenticationGeneralNRCModeRuleFalse.TransmitNRC0x57,1 */
              /* Certificate verification failed - Invalid Scope */
              ErrorCode = DCM_E_CERTIFICATEVERIFICATIONFAILEDREVOKED;
              break;

            default:
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
              /* KEYM_CERTIFICATE_NOT_PARSED, KEYM_CERTIFICATE_NOT_AVAILABLE are not expected results from the callback */
              ErrorCode = DCM_E_GENERALREJECT;
#if (DCM_DEV_ERROR_DETECT == STD_ON)
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsUnsupportedCode.ReportDETError,1 */
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmKeyMAsyncCertificateVerifyFinished.ReturnsUnsupportedCode.ReportDETError,1 */
              DCM_DET_REPORT_ERROR(DCM_SVCID_KEYMASYNCCERTIFICATEVERIFYFINISHED, DCM_E_PARAM);
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
              break;
          }

          Dcm_AuthenticationHandler_CryptoOperationDone(AuthenticationConnectionIndex, 0U, ErrorCode);
        }
        break;
      }
    } /* for-loop */

#if (DCM_DEV_ERROR_DETECT == STD_ON)
    if (DCM_NUM_AUTHENTICATION_CONNECTIONS == AuthenticationConnectionIndex)
    {
      /* Certificate not found */
      /* !LINKSTO Dcm.EB.UDSServices.DcmKeyMAsyncCertificateVerifyFinished.InvalidCertificateId.ReportDETError,1 */
      DCM_DET_REPORT_ERROR(DCM_SVCID_KEYMASYNCCERTIFICATEVERIFYFINISHED, DCM_E_PARAM);
    }
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
  }

  DBG_DCM_KEYMASYNCCERTIFICATEVERIFYFINISHED_EXIT(RetVal, CertId, Result);
  return RetVal;
}

STATIC FUNC(Dcm_NegativeResponseCodeType, CSM_APPL_CODE) Dcm_CryptoStackFacade_JobFinished_RandomGenerate(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  Dcm_CryptoResultType OperationResult)
{
  Dcm_NegativeResponseCodeType ErrorCode = DCM_E_GENERALREJECT;

  switch (OperationResult)
  {
    case E_OK:
      /* E_OK: request successful */
      if (Dcm_AuthenticationConfigPtr->AuthenticationConnection[AuthenticationConnectionIndex].ChallengeLength ==
          Dcm_Authentication_GeneratedLength[AuthenticationConnectionIndex])
      {
        ErrorCode = DCM_E_POSITIVERESPONSE;
      }
      else if (Dcm_AuthenticationConfigPtr->AuthenticationConnection[AuthenticationConnectionIndex].ChallengeLength >
               Dcm_Authentication_GeneratedLength[AuthenticationConnectionIndex])
      {
        /* Dcm_CryptoStackFacade_CreateChallenge has received a zero out memory location for ChallengeServer */
        ErrorCode = DCM_E_POSITIVERESPONSE;
      }
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      else
      {
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsOK.LengthOfGeneratedRandomNumberLarger.ReportDETError,1 */
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsOK.LengthOfGeneratedRandomNumberLarger.ReportDETError,1 */
        DCM_DET_REPORT_ERROR(DCM_SVCID_CSMASYNCJOBFINISHED, DCM_E_INVALID_VALUE);
      }
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
      break;

    case E_NOT_OK:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsNotOK.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsNotOK.TransmitNRC0x10,1 */
      /* E_NOT_OK: request failed */
    case CRYPTO_E_KEY_NOT_VALID:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsKeyNotValid.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsKeyNotValid.TransmitNRC0x10,1 */
      /* CRYPTO_E_KEY_NOT_VALID: request failed because the the key's state is "invalid" */
    case CRYPTO_E_KEY_SIZE_MISMATCH:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsKeySizeMismatch.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsKeySizeMismatch.TransmitNRC0x10,1 */
      /* CRYPTO_E_KEY_SIZE_MISMATCH: request failed because the size of key is wrong */
#if (DCM_DSP_AUTHENTICATION_CRYPTO_VARIANT == DCM_AUTHENTICATION_CRYPTO_VARIANT_BEFORE_AUTOSAR_R20_11)
    case CRYPTO_E_QUEUE_FULL:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsQueueFull.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsQueueFull.TransmitNRC0x10,1 */
      /* CRYPTO_E_QUEUE_FULL: request failed because the queue is full */
    case CRYPTO_E_ENTROPY_EXHAUSTION:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsEntropyExhaustion.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsEntropyExhaustion.TransmitNRC0x10,1 */
      /* CRYPTO_E_ENTROPY_EXHAUSTION: request failed because the entropy of the random number generator is exhausted -> reseed */
    case CRYPTO_E_SMALL_BUFFER:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsSmallBuffer.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsSmallBuffer.TransmitNRC0x10,1 */
      /* CRYPTO_E_SMALL_BUFFER: request failed because the provided buffer is too small to store the result */
#else
    case CRYPTO_E_ENTROPY_EXHAUSTED:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsEntropyExhausted.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsEntropyExhausted.TransmitNRC0x10,1 */
      /* CRYPTO_E_ENTROPY_EXHAUSTED: request failed, entropy of random number generator is exhausted -> reseed */
    case CRYPTO_E_KEY_READ_FAIL:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsKeyReadFail.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsKeyReadFail.TransmitNRC0x10,1 */
      /* CRYPTO_E_KEY_READ_FAIL: request failed because read access was denied */
    case CRYPTO_E_KEY_WRITE_FAIL:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsKeyWriteFail.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsKeyWriteFail.TransmitNRC0x10,1 */
      /* CRYPTO_E_KEY_WRITE_FAIL: request failed because the writing access failed */
    case CRYPTO_E_KEY_NOT_AVAILABLE:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsKeyNotAvailable.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsKeyNotAvailable.TransmitNRC0x10,1 */
      /* CRYPTO_E_KEY_NOT_AVAILABLE: request failed because the key is not available */
    case CRYPTO_E_KEY_EMPTY:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsKeyEmpty.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsKeyEmpty.TransmitNRC0x10,1 */
      /* CRYPTO_E_KEY_EMPTY: request failed because of uninitialized source key element. */
#endif
    case CRYPTO_E_BUSY:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsBusy.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsBusy.TransmitNRC0x10,1 */
      /* CRYPTO_E_BUSY: request failed because the service is still busy */
    case CRYPTO_E_JOB_CANCELED:
      /* Note: In case the crypto driver does not support an instant cancelation of the job, the
               application need to wait for the job's closing callback to free the buffers. The crypto
               driver could potentially still write to the output buffer(s).
      */
      /* CRYPTO_E_JOB_CANCELED: request failed because the Job has been canceled */
      ErrorCode = DCM_E_GENERALREJECT;
      break;

    default:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
      ErrorCode = DCM_E_GENERALREJECT;
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsUnsupportedCode.ReportDETError,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsUnsupportedCode.ReportDETError,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsUnsupportedCode.ReportDETError,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmRandomGenerateAsyncJobFinished.ReturnsUnsupportedCode.ReportDETError,1 */
      DCM_DET_REPORT_ERROR(DCM_SVCID_CSMASYNCJOBFINISHED, DCM_E_PARAM);
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
      break;
  }

  return ErrorCode;
}

STATIC FUNC(Dcm_NegativeResponseCodeType, CSM_APPL_CODE) Dcm_CryptoStackFacade_JobFinished_SignatureVerify(
    Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
    Dcm_CryptoResultType OperationResult)
{
  Dcm_NegativeResponseCodeType ErrorCode = DCM_E_GENERALREJECT;

  switch (OperationResult)
  {
    case E_OK:
      /* E_OK: request successful */
      if (CRYPTO_E_VER_OK == Dcm_Authentication_VerificationResult[AuthenticationConnectionIndex])
      {
        ErrorCode = DCM_E_POSITIVERESPONSE;
      }
      else if (CRYPTO_E_VER_NOT_OK == Dcm_Authentication_VerificationResult[AuthenticationConnectionIndex])
      {
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsOK.VerifyResult.VerNotOK.TransmitNRC0x58,1 */
        ErrorCode = DCM_E_OWNERSHIPVERIFICATIONFAILED;
      }
      else
      {
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsOK.VerifyResult.VerUnsupportedCode.TransmitNRC0x10,1 */
        ErrorCode = DCM_E_GENERALREJECT;
#if (DCM_DEV_ERROR_DETECT == STD_ON)
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsOK.VerifyResult.VerUnsupportedCode.ReportDETError,1 */
        DCM_DET_REPORT_ERROR(DCM_SVCID_CSMASYNCJOBFINISHED, DCM_E_INVALID_VALUE);
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
      }
      break;

    case E_NOT_OK:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsNotOK.TransmitNRC0x10,1 */
      /* E_NOT_OK: request failed */
    case CRYPTO_E_BUSY:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsBusy.TransmitNRC0x10,1 */
      /* CRYPTO_E_BUSY: request failed because the service is still busy */
    case CRYPTO_E_KEY_NOT_VALID:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsKeyNotValid.TransmitNRC0x10,1 */
      /* CRYPTO_E_KEY_NOT_VALID: request failed because the key is invalid */
    case CRYPTO_E_KEY_SIZE_MISMATCH:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsKeySizeMismatch.TransmitNRC0x10,1 */
      /* CRYPTO_E_KEY_SIZE_MISMATCH: request failed because the size of key is wrong */
#if (DCM_DSP_AUTHENTICATION_CRYPTO_VARIANT == DCM_AUTHENTICATION_CRYPTO_VARIANT_BEFORE_AUTOSAR_R20_11)
    case CRYPTO_E_QUEUE_FULL:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsQueueFull.TransmitNRC0x10,1 */
      /* CRYPTO_E_QUEUE_FULL: request failed because the queue is full */
    case CRYPTO_E_SMALL_BUFFER:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsSmallBuffer.TransmitNRC0x10,1 */
      /* CRYPTO_E_SMALL_BUFFER: request failed because the provided buffer is too small to store the result */
#else
    case CRYPTO_E_ENTROPY_EXHAUSTED:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsEntropyExhausted.TransmitNRC0x10,1 */
      /* CRYPTO_E_ENTROPY_EXHAUSTED: request failed, entropy of random number generator is exhausted -> reseed */
    case CRYPTO_E_KEY_READ_FAIL:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsKeyReadFail.TransmitNRC0x10,1 */
      /* CRYPTO_E_KEY_READ_FAIL: request failed because read access was denied */
    case CRYPTO_E_KEY_WRITE_FAIL:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsKeyWriteFail.TransmitNRC0x10,1 */
      /* CRYPTO_E_KEY_WRITE_FAIL: request failed because the writing access failed */
    case CRYPTO_E_KEY_NOT_AVAILABLE:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsKeyNotAvailable.TransmitNRC0x10,1 */
      /* CRYPTO_E_KEY_NOT_AVAILABLE: request failed because the key is not available */
    case CRYPTO_E_KEY_EMPTY:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsKeyEmpty.TransmitNRC0x10,1 */
      /* CRYPTO_E_KEY_EMPTY: request failed because of uninitialized source key element */
#endif
    case CRYPTO_E_JOB_CANCELED:
      /* Note: In case the crypto driver does not support an instant cancelation of the job, the
               application need to wait for the job's closing callback to free the buffers. The crypto
               driver could potentially still write to the output buffer(s).
      */
      /* CRYPTO_E_JOB_CANCELED: request failed because the Job has been canceled */
      ErrorCode = DCM_E_GENERALREJECT;
      break;

    default:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
      ErrorCode = DCM_E_GENERALREJECT;
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsUnsupportedCode.ReportDETError,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.ProofOfOwnership.DcmCsmAsyncJobFinished.ReturnsUnsupportedCode.ReportDETError,1 */
      DCM_DET_REPORT_ERROR(DCM_SVCID_CSMASYNCJOBFINISHED, DCM_E_PARAM);
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
      break;
  }

  return ErrorCode;
}

#if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON)
STATIC FUNC(Dcm_NegativeResponseCodeType, CSM_APPL_CODE) Dcm_CryptoStackFacade_JobFinished_SignatureGenerate(
    Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
    Dcm_CryptoResultType OperationResult)
{
  Dcm_NegativeResponseCodeType ErrorCode = DCM_E_GENERALREJECT;

  switch (OperationResult)
  {
    case E_OK:
      /* E_OK: request successful */
      /* The generated length must fit in 2-bytes */
      if ((Dcm_Authentication_GeneratedLength[AuthenticationConnectionIndex] != 0U) &&
          (Dcm_Authentication_GeneratedLength[AuthenticationConnectionIndex] <= DCM_MAXVALUE_2BYTES))
      {
        ErrorCode = DCM_E_POSITIVERESPONSE;
      }
      else
      {
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsOK.ZeroLengthOfProofOfOwnershipServer.TransmitNRC0x10,1 */
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsOK.OversizedLengthOfProofOfOwnershipServer.TransmitNRC0x10,1 */
        ErrorCode = DCM_E_GENERALREJECT;
#if (DCM_DEV_ERROR_DETECT == STD_ON)
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsOK.ZeroLengthOfProofOfOwnershipServer.ReportDETError,1 */
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsOK.OversizedLengthOfProofOfOwnershipServer.ReportDETError,1 */
        DCM_DET_REPORT_ERROR(DCM_SVCID_CSMASYNCJOBFINISHED, DCM_E_INVALID_VALUE);
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
      }
      break;

    case E_NOT_OK:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsNotOK.TransmitNRC0x10,1 */
      /* E_NOT_OK: Request failed */
    case CRYPTO_E_BUSY:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsBusy.TransmitNRC0x10,1 */
      /* CRYPTO_E_BUSY: Request failed, service is still busy */
    case CRYPTO_E_KEY_NOT_VALID:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsKeyNotValid.TransmitNRC0x10,1 */
      /* CRYPTO_E_KEY_NOT_VALID: Request failed, the key's state is "invalid" */
    case CRYPTO_E_KEY_SIZE_MISMATCH:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsKeySizeMismatch.TransmitNRC0x10,1 */
      /* CRYPTO_E_KEY_SIZE_MISMATCH: request failed because the size of key is wrong */
#if (DCM_DSP_AUTHENTICATION_CRYPTO_VARIANT == DCM_AUTHENTICATION_CRYPTO_VARIANT_BEFORE_AUTOSAR_R20_11)
    case CRYPTO_E_QUEUE_FULL:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsQueueFull.TransmitNRC0x10,1 */
      /* CRYPTO_E_QUEUE_FULL: Request failed, the queue is full */
    case CRYPTO_E_SMALL_BUFFER:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsSmallBuffer.TransmitNRC0x10,1 */
      /* CRYPTO_E_SMALL_BUFFER: Request failed, the provided buffer is too small to store the result */
#else
    case CRYPTO_E_ENTROPY_EXHAUSTED:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsEntropyExhausted.TransmitNRC0x10,1 */
      /* CRYPTO_E_ENTROPY_EXHAUSTED: request failed, entropy of random number generator is exhausted -> reseed */
    case CRYPTO_E_KEY_READ_FAIL:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsKeyReadFail.TransmitNRC0x10,1 */
      /* CRYPTO_E_KEY_READ_FAIL: request failed because read access was denied */
    case CRYPTO_E_KEY_WRITE_FAIL:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsKeyWriteFail.TransmitNRC0x10,1 */
      /* CRYPTO_E_KEY_WRITE_FAIL: request failed because the writing access failed */
    case CRYPTO_E_KEY_NOT_AVAILABLE:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsKeyNotAvailable.TransmitNRC0x10,1 */
      /* CRYPTO_E_KEY_NOT_AVAILABLE: request failed because the key is not available */
    case CRYPTO_E_KEY_EMPTY:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsKeyEmpty.TransmitNRC0x10,1 */
      /* CRYPTO_E_KEY_EMPTY: request failed because of uninitialized source key element */
#endif
    case CRYPTO_E_JOB_CANCELED:
      /* Note: In case the crypto driver does not support an instant cancelation of the job, the
               application need to wait for the job's closing callback to free the buffers. The crypto
               driver could potentially still write to the output buffer(s).
      */
      /* CRYPTO_E_JOB_CANCELED: request failed because the Job has been canceled */
      ErrorCode = DCM_E_GENERALREJECT;
      break;

    default:
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsUnsupportedCode.TransmitNRC0x10,1 */
      ErrorCode = DCM_E_GENERALREJECT;
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantBeforeAutosarR20-11.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsUnsupportedCode.ReportDETError,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.CryptoVariantAfterAutosarR20-11.VerifyCertificateBidirectional.DcmCsmSignatureGenerateAsyncJobFinished.ReturnsUnsupportedCode.ReportDETError,1 */
      DCM_DET_REPORT_ERROR(DCM_SVCID_CSMASYNCJOBFINISHED, DCM_E_PARAM);
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
      break;
  }

  return ErrorCode;
}
#endif /* #if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON) */

/* This function is called when Csm terminates Csm_SignatureVerify or Csm_RandomGenerate job */
/* !LINKSTO Dcm.EB.UDSServices.AuthenticationService.CryptoVariantBeforeAutosarR20-11.CsmAsyncJobFinished.API,1 */
/* !LINKSTO Dcm.Dsn.IB.CryptoStackFacade.CsmAsynJobFinishedCallback,1 */
#if (DCM_DSP_AUTHENTICATION_CRYPTO_VARIANT == DCM_AUTHENTICATION_CRYPTO_VARIANT_BEFORE_AUTOSAR_R20_11)
FUNC(void, CSM_APPL_CODE) Dcm_CsmAsyncJobFinished(
  P2CONST(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) job,
  Std_ReturnType result)
#else
/* !LINKSTO Dcm.EB.UDSServices.AuthenticationService.CryptoVariantAfterAutosarR20-11.CsmAsyncJobFinished.API,1 */
FUNC(void, CSM_APPL_CODE) Dcm_CsmAsyncJobFinished(
  uint32 jobId,
  Crypto_ResultType result)
#endif
{
  /* return value E_OK is expected (SWS_Dcm_91076) */
  Dcm_NegativeResponseCodeType ErrorCode = DCM_E_GENERALREJECT;
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex = DCM_NUM_AUTHENTICATION_CONNECTIONS;

  DBG_DCM_CSMASYNCJOBFINISHED_ENTRY(DCM_TRACE_JOB_PARAMETER(job), result);

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized != TRUE)
  {
    /* !LINKSTO Dcm.EB.UDSServices.DcmCsmAsyncJobFinished.DcmNotInitialized.ReportDETError,1 */
    DCM_DET_REPORT_ERROR(DCM_SVCID_CSMASYNCJOBFINISHED, DCM_E_UNINIT);
  }
#if (DCM_DSP_AUTHENTICATION_CRYPTO_VARIANT == DCM_AUTHENTICATION_CRYPTO_VARIANT_BEFORE_AUTOSAR_R20_11)
  else if (NULL_PTR == job)
  {
    /* !LINKSTO Dcm.EB.UDSServices.CryptoVariantBeforeAutosarR20-11.DcmCsmAsyncJobFinished.NullPointer.ReportDETError,1 */
    DCM_DET_REPORT_ERROR(DCM_SVCID_CSMASYNCJOBFINISHED, DCM_E_PARAM_POINTER);
  }
#endif /* #if (DCM_DSP_AUTHENTICATION_CRYPTO_VARIANT == DCM_AUTHENTICATION_CRYPTO_VARIANT_BEFORE_AUTOSAR_R20_11) */
  else
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* search for pending callbacks and compare the jobId */
    /* Deviation TASKING-1 <+2> */
    for (AuthenticationConnectionIndex = 0U; AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS; AuthenticationConnectionIndex++)
    {
      if (TRUE == Dcm_CryptoStackFacade[AuthenticationConnectionIndex].CsmCallbackPending)
      {
        if (Dcm_AuthenticationConfigPtr->AuthenticationConnection[AuthenticationConnectionIndex].
              RandomGenerateJobId == DCM_JOBID_FROM_JOB(job))
        {
          ErrorCode = Dcm_CryptoStackFacade_JobFinished_RandomGenerate(
                        AuthenticationConnectionIndex, result);
          break;
        }
        if (Dcm_AuthenticationConfigPtr->AuthenticationConnection[AuthenticationConnectionIndex].
              SignatureVerifyJobId == DCM_JOBID_FROM_JOB(job))
        {
          ErrorCode = Dcm_CryptoStackFacade_JobFinished_SignatureVerify(AuthenticationConnectionIndex, result);
          break;
        }
#if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON)
        if (Dcm_SignatureGenerateJobDescriptor[Dcm_AuthenticationConfigPtr->
              AuthenticationConnection[AuthenticationConnectionIndex].
              SignatureGenerateJobDescriptorIndex].SignatureGenerateJobId == DCM_JOBID_FROM_JOB(job))
        {
          ErrorCode = Dcm_CryptoStackFacade_JobFinished_SignatureGenerate(AuthenticationConnectionIndex, result);
          break;
        }
#endif /* #if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON) */
      }
    } /* for-loop */

    if (DCM_NUM_AUTHENTICATION_CONNECTIONS != AuthenticationConnectionIndex)
    {
      /* Job found */
      Dcm_CryptoStackFacade[AuthenticationConnectionIndex].CsmCallbackPending = FALSE;
      Dcm_AuthenticationHandler_CryptoOperationDone(AuthenticationConnectionIndex,
                                                    (uint16)(Dcm_Authentication_GeneratedLength[AuthenticationConnectionIndex]),
                                                    ErrorCode);
    }
#if (DCM_DEV_ERROR_DETECT == STD_ON)
    else
    {
      /* Job not found */
      /* !LINKSTO Dcm.EB.UDSServices.DcmCsmAsyncJobFinished.InvalidJobId.ReportDETError,2 */
      /* !LINKSTO Dcm.EB.UDSServices.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.InvalidJobId.ReportDETError,1 */
      /* !LINKSTO Dcm.EB.UDSServices.VerifyCertificateBidirectional.DcmCsmAsyncJobFinished.InvalidJobId.ReportDETError,1 */
      /* !LINKSTO Dcm.EB.UDSServices.ProofOfOwnership.DcmCsmAsyncJobFinished.InvalidJobId.ReportDETError,1 */
      DCM_DET_REPORT_ERROR(DCM_SVCID_CSMASYNCJOBFINISHED, DCM_E_PARAM);
    }
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
  }

  DBG_DCM_CSMASYNCJOBFINISHED_EXIT(DCM_TRACE_JOB_PARAMETER(job), result);
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*==================[internal function definitions]==============================================*/

#endif /* #if (DCM_AUTHENTICATION_CONNECTION == STD_ON) */

/*==================[end of file]================================================================*/
