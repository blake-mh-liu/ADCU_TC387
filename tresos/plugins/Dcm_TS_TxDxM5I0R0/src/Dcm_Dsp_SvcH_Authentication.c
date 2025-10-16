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

/* !LINKSTO Dcm.Dsn.File.AuthenticationSvcH.Impl,1 */
/* This file contains the implementation of the Diagnostic Service Authentication. */

/*==================[includes]===================================================================*/

#include <Dcm_Trace.h>
#include <Std_Types.h>                                                 /* AUTOSAR standard types */
#include <TSAutosar.h>
#include <TSMem.h>
#include <Dcm_Dsp_SvcH_Authentication.h>
#include <Dcm_Authentication_AuthenticationHandler.h>
#include <Dcm_Authentication_DiagnosticPolicyHandler.h>

/* !LINKSTO Dcm.Service.Authentication,1 */
#if (DCM_DSP_USE_SERVICE_0X29 == STD_ON)

/*==================[macro definitions]==========================================================*/

/** \brief Value definition for 'DeAuthenticate' subservice */
#if (defined DCM_AUTHENTICATION_DEAUTHENTICATE)
  #error "DCM_AUTHENTICATION_DEAUTHENTICATE is already defined"
#endif
#define DCM_AUTHENTICATION_DEAUTHENTICATE                     0x00U

/** \brief Value definition for 'VerifyCertificateUnidirectional' subservice */
#if (defined DCM_AUTHENTICATION_VERIFYCERTIFICATEUNIDIRECTIONAL)
  #error "DCM_AUTHENTICATION_VERIFYCERTIFICATEUNIDIRECTIONAL is already defined"
#endif
#define DCM_AUTHENTICATION_VERIFYCERTIFICATEUNIDIRECTIONAL    0x01U

/** \brief Value definition for 'VerifyCertificateBidirectional' subservice */
#if (defined DCM_AUTHENTICATION_VERIFYCERTIFICATEBIDIRECTIONAL)
  #error "DCM_AUTHENTICATION_VERIFYCERTIFICATEBIDIRECTIONAL is already defined"
#endif
#define DCM_AUTHENTICATION_VERIFYCERTIFICATEBIDIRECTIONAL     0x02U

/** \brief Value definition for 'ProofOfOwnership' subservice */
#if (defined DCM_AUTHENTICATION_PROOFOFOWNERSHIP)
  #error "DCM_AUTHENTICATION_PROOFOFOWNERSHIP is already defined"
#endif
#define DCM_AUTHENTICATION_PROOFOFOWNERSHIP                   0x03U

/** \brief Value definition for 'AuthenticationConfiguration' subservice */
#if (defined DCM_AUTHENTICATION_AUTHENTICATIONCONFIGURATION)
  #error "DCM_AUTHENTICATION_AUTHENTICATIONCONFIGURATION is already defined"
#endif
#define DCM_AUTHENTICATION_AUTHENTICATIONCONFIGURATION        0x08U


/** \brief Value definition for
           AuthenticationReturnParameter: AuthenticationConfiguration APCE */
#if (defined DCM_AUTHRESPONSE_ACAPCE)
  #error "DCM_AUTHRESPONSE_ACAPCE is already defined"
#endif
#define DCM_AUTHRESPONSE_ACAPCE        0x02U

/** \brief Value definition for
           AuthenticationReturnParameter: DeAuthentication successful */
#if (defined DCM_AUTHRESPONSE_DAS)
  #error "DCM_AUTHRESPONSE_DAS is already defined"
#endif
#define DCM_AUTHRESPONSE_DAS           0x10U

/** \brief Value definition for
           AuthenticationReturnParameter: CertificateVerified, OwnershipVerificationNecessary */
#if (defined DCM_AUTHRESPONSE_CVOVN)
  #error "DCM_AUTHRESPONSE_CVOVN is already defined"
#endif
#define DCM_AUTHRESPONSE_CVOVN         0x11U

/** \brief Value definition for
           AuthenticationReturnParameter: OwnershipVerified, AuthenticationComplete */
#if (defined DCM_AUTHRESPONSE_OVAC)
  #error "DCM_AUTHRESPONSE_OVAC is already defined"
#endif
#define DCM_AUTHRESPONSE_OVAC          0x12U


/** \brief Value definition for communicationConfiguration: no secure communication */
#if (defined DCM_AUTHENTICATION_COCO_NOSECURECOMMUNICATION)
  #error "DCM_AUTHENTICATION_COCO_NOSECURECOMMUNICATION is already defined"
#endif
#define DCM_AUTHENTICATION_COCO_NOSECURECOMMUNICATION        0x00U

/** \brief Definition of value used in subservices 0x01 and 0x02 for a minimun length check. */
#if (defined DCM_MINIMUM_LENGTH_OFFSET_SSVC_0X01_0x02)
  #error "DCM_MINIMUM_LENGTH_OFFSET_SSVC_0X01_0x02 is already defined"
#endif
#define DCM_MINIMUM_LENGTH_OFFSET_SSVC_0X01_0x02             0x03U

/** \brief Definition of value used in subservices 0x01 and 0x02 for a mandatory, variable and total
           length checks. */
#if (defined DCM_MANDATORY_LENGTH_OFFSET_SSVC_0X01_0x02)
  #error "DCM_MANDATORY_LENGTH_OFFSET_SSVC_0X01_0x02 is already defined"
#endif
#define DCM_MANDATORY_LENGTH_OFFSET_SSVC_0X01_0x02           0x05U

/** \brief Definition of value used in subservice 0x03 for a minimum length check. */
#if (defined DCM_MINIMUM_LENGTH_OFFSET_SSVC_0X03)
  #error "DCM_MINIMUM_LENGTH_OFFSET_SSVC_0X03 is already defined"
#endif
#define DCM_MINIMUM_LENGTH_OFFSET_SSVC_0X03                  0x02U

/** \brief Definition of value used in subservice 0x03 for a mandatory and total length checks. */
#if (defined DCM_MANDATORY_LENGTH_OFFSET_SSVC_0X03)
  #error "DCM_MANDATORY_LENGTH_OFFSET_SSVC_0X03 is already defined"
#endif
#define DCM_MANDATORY_LENGTH_OFFSET_SSVC_0X03                0x04U

/** \brief Definition of value used in subservice 0x00 and 0x08 for a total length checks. */
#if (defined DCM_TOTAL_LENGTH_OFFSET_SSVC_0X00)
  #error "DCM_TOTAL_LENGTH_OFFSET_SSVC_0X00 is already defined"
#endif
#define DCM_TOTAL_LENGTH_OFFSET_SSVC                         0x00U

/** \brief Definition of value used in subservice 0x01 for checking the response length.
           The service id byte is not included in the length definition. */
#if (defined DCM_MINIMUM_LENGTH_OFFSET_RESPONSE_SSVC_0X01)
  #error "DCM_MINIMUM_LENGTH_OFFSET_RESPONSE_SSVC_0X01 is already defined"
#endif
#define DCM_MINIMUM_LENGTH_OFFSET_RESPONSE_SSVC_0X01         0x06U

/** \brief Definition of value used in subservice 0x02 for checking the response length.
           The service id byte is not included in the length definition. */
#if (defined DCM_MINIMUM_LENGTH_OFFSET_RESPONSE_SSVC_0X02)
  #error "DCM_MINIMUM_LENGTH_OFFSET_RESPONSE_SSVC_0X02 is already defined"
#endif
#define DCM_MINIMUM_LENGTH_OFFSET_RESPONSE_SSVC_0X02         0x0AU

/*==================[type definitions]===========================================================*/

/*==================[external constants declarations]============================================*/

/*==================[internal constants declarations]============================================*/

/*==================[internal function declarations]=============================================*/
#if ((DCM_0X29_0X01_SSVC_ENABLED == STD_ON) || \
     (DCM_0X29_0X02_SSVC_ENABLED == STD_ON))

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/** \brief This function verifies the request parameters and fills the AuthenticationContext for
 **        subfunction 0x01 and 0x02
 **
 ** \param[in]    pMsgContext - Message related information for one diagnostic protocol identifier.
 ** \param[out]   AuthenticationContext .
 **
 ** \retval E_OK           Check passed
 ** \retval E_NOT_OK       Check failed */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_Authentication_VerifyCertificateRequestCheck(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext,
  P2VAR(Dcm_AuthenticationContextType, AUTOMATIC, DCM_VAR) AuthenticationContext);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif /* #if ((DCM_0X29_0X01_SSVC_ENABLED == STD_ON) || \
               (DCM_0X29_0X02_SSVC_ENABLED == STD_ON))  */

#if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON)

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/** \brief This function verifies the length of ChallengeClient
 **        and the length of the CertificateServer
 **
 ** \param[in]    pMsgContext - Message related information for one diagnostic protocol identifier.
 ** \param[out]   AuthenticationContext .
 **
 ** \retval E_OK                                              Checks passed
 ** \retval DCM_E_GENERALREJECT                               CertificateServer length check failed
 ** \retval DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT       ChallengeClient length check failed */
STATIC FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_Dsp_Authentication_KeyMLengthChecks(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif /* #if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON) */


/*==================[external data declarations]=================================================*/

/*==================[internal data declarations]=================================================*/

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dcm_MemMap.h>

/** \brief This global variable holds the sub-service handler, extracted from
 **        Authentication(0x29) request in the DCM_INITIAL state.
 **        This variable is used in each call of the Authentication handler to call the
 **        sub-service handler whether is external or internal.
 */
STATIC VAR(Dcm_GenericServiceHandlerType, DCM_VAR) Dcm_Authentication_SubServiceHandler;


/** \brief This global variable stores the input parameters extracted from an Authentication(0x29)
 **        request in the DCM_INITIAL state. It is also used to pass the output parameters from the
 **        Dcm_AuthenticationHandler_AuthenticationProcess function.
 */
STATIC VAR(Dcm_AuthenticationContextType, DCM_VAR) Dcm_Authentication_AuthenticationContext;

#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dcm_MemMap.h>

/*==================[internal function definitions]==============================================*/

#if ((DCM_0X29_0X01_SSVC_ENABLED == STD_ON) || \
     (DCM_0X29_0X02_SSVC_ENABLED == STD_ON))

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_Authentication_VerifyCertificateRequestCheck(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext,
  P2VAR(Dcm_AuthenticationContextType, AUTOMATIC, DCM_VAR) AuthenticationContext)
{
  Std_ReturnType ServiceProcessStatus = E_NOT_OK;

  /* SID and SSID have been removed from request message context. */
  if (pMsgContext->reqDataLen >= DCM_MINIMUM_LENGTH_OFFSET_SSVC_0X01_0x02)
  {
    uint8 HighByteCertLen = (uint8)pMsgContext->reqData[1U];
    uint8 LowByteCertLen  = (uint8)pMsgContext->reqData[2U];

    uint16 ClientCertificateLength =
      (uint16) DCM_COMPOSE_16BIT_WORD_FROM_MSB_AND_LSB(HighByteCertLen, LowByteCertLen);

    if ((pMsgContext->reqDataLen) >=
        (DCM_MANDATORY_LENGTH_OFFSET_SSVC_0X01_0x02 + (Dcm_MsgLenType)ClientCertificateLength))
    {
      uint8 HighByteChallengeLen = (uint8)pMsgContext->reqData[3U + ClientCertificateLength];
      uint8 LowByteChallengeLen  = (uint8)pMsgContext->reqData[4U + ClientCertificateLength];

      uint16 ClientChallengeLength =
        (uint16) DCM_COMPOSE_16BIT_WORD_FROM_MSB_AND_LSB(HighByteChallengeLen, LowByteChallengeLen);

      if ((pMsgContext->reqDataLen) ==
          (DCM_MANDATORY_LENGTH_OFFSET_SSVC_0X01_0x02 +
           (Dcm_MsgLenType)ClientCertificateLength + (Dcm_MsgLenType)ClientChallengeLength))
      {
        if (pMsgContext->reqData[0U] == DCM_AUTHENTICATION_COCO_NOSECURECOMMUNICATION)
        {
          if (ClientCertificateLength != 0U)
          {
            /* set up context for authentication */
            /* Position of certificate in the request:
                req[0]                                - communicationConfiguration
                req[1..2]                             - lengthOfCertificateClient
                req[3..3+lengthOfCertificateClient-1] - certificateClient
            */
            AuthenticationContext->CertificateClient.Certificate = &(pMsgContext->reqData[3U]);
            AuthenticationContext->CertificateClient.LengthOfCertificate = ClientCertificateLength;
#if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON)
            /* Position of challenge in the request:
                req[3+lengthOfCertificateClient..3+lengthOfCertificateClient+1]
               - lengthOfChallengeClient
                req[3+lengthOfCertificateClient+2..3+lengthOfCertificateClient+2+lengthOfChallengeClient-1]
               - challengeClient
            */
            AuthenticationContext->ChallengeClient.Challenge = &(pMsgContext->reqData[3U + ClientCertificateLength + 2U]);
            AuthenticationContext->ChallengeClient.LengthOfChallenge = ClientChallengeLength;
#endif /* #if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON) */
            AuthenticationContext->ErrorCode = E_NOT_OK;
            ServiceProcessStatus = E_OK;
          }
          else
          {
            /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.ZeroLengthOfCertificateClient.TransmitNRC0x13,1 */
            /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.ZeroLengthOfCertificateClient.TransmitNRC0x13,1 */
            Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
          }
        }
        else
        {
          /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.CommunicationConfigurationNotZero.TransmitNRC0x31,1 */
          /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.CommunicationConfigurationNotZero.TransmitNRC0x31,1 */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
        }
      }
      else
      {
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.TotalLengthCheckFailure.TransmitNRC0x13,1 */
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.TotalLengthCheckFailure.TransmitNRC0x13,1 */
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
      }
    }
    else
    {
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.MandatoryBytesLengthCheckFailure.TransmitNRC0x13,1 */
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.VariableLengthCheckFailure.TransmitNRC0x13,1 */
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
  }
  else
  {
    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.MinimumLengthCheckFailure.TransmitNRC0x13,1 */
    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.MinimumLengthCheckFailure.TransmitNRC0x13,1 */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
  }

  return ServiceProcessStatus;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif /* #if ((DCM_0X29_0X01_SSVC_ENABLED == STD_ON) || \
               (DCM_0X29_0X02_SSVC_ENABLED == STD_ON))  */

#if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON)

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

STATIC FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_Dsp_Authentication_KeyMLengthChecks(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext)
{
  Dcm_NegativeResponseCodeType CurrentNrc = E_NOT_OK;
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex = DCM_NUM_MAIN_CONNECTIONS;

  /* Set AuthenticationDirection to bidirectional */
  Dcm_Authentication_AuthenticationContext.AuthenticationDirection = DCM_AUTHENTICATIONDIRECTION_BIDIRECTIONAL;

  /* Find AuthenticationConnectionIndex */
  AuthenticationConnectionIndex = Dcm_MainConnectionConfig[Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].MainConnectionIndex].AuthenticatedIndex;

  if (Dcm_Authentication_AuthenticationContext.ChallengeClient.LengthOfChallenge > 0U)
  {
    if (pMsgContext->resMaxDataLen >
       (DCM_MINIMUM_LENGTH_OFFSET_RESPONSE_SSVC_0X02 +
       (Dcm_MsgLenType)Dcm_AuthenticationConfigPtr->AuthenticationConnection[AuthenticationConnectionIndex].ChallengeLength)
       )
    {
      CurrentNrc = E_OK;
    }
    else
    {
      /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.ZeroLengthOfCertificateServer.TransmitNRC0x10,1 */
      CurrentNrc = DCM_E_GENERALREJECT;
    }
  }
  else
  {
    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.ZeroLengthOfChallengeClient.TransmitNRC0x13,1 */
    CurrentNrc = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }

  return CurrentNrc;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif /* #if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON) */

/*==================[external function definitions]==============================================*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

FUNC(void, DCM_CODE) Dcm_Dsp_Authentication_Init(void)
{
  Dcm_Authentication_SubServiceHandler = NULL_PTR;
}

/* !LINKSTO Dcm.Dsn.IB.Authentication.SvcH,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_Authentication_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext)
{
  Std_ReturnType ServiceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSP_AUTHENTICATION_SVCH_ENTRY(OpStatus, pMsgContext);

  if (DCM_INITIAL == OpStatus)
  {
    /* Initial call of the sub-service handler */
    DCM_PRECONDITION_ASSERT(Dcm_Authentication_SubServiceHandler == NULL_PTR, DCM_SVCID_AUTHENTICATION);
    Dcm_Authentication_SubServiceHandler = Dcm_Dsp_ExtractSubServiceHandler(DCM_INITIAL, pMsgContext);
  }

  DCM_PRECONDITION_ASSERT(Dcm_Authentication_SubServiceHandler != NULL_PTR, DCM_SVCID_AUTHENTICATION);
  /* Call sub-service handler */
  ServiceProcessStatus = Dcm_Authentication_SubServiceHandler(OpStatus, pMsgContext);

  if ((DCM_CANCEL == OpStatus) || (DCM_CONFIRMED_OK == OpStatus) || (DCM_CONFIRMED_NOK == OpStatus))
  {
    /* Final call of the sub-service handler */
    Dcm_Authentication_SubServiceHandler = NULL_PTR;
  }

  /* Sub-service handlers return E_OK, so we must convert to DCM_E_DONE */
  if (E_OK == ServiceProcessStatus)
  {
    ServiceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSP_AUTHENTICATION_SVCH_EXIT(ServiceProcessStatus, OpStatus, pMsgContext);

  return ServiceProcessStatus;
}

#if (DCM_0X29_0X00_SSVC_ENABLED == STD_ON)
/* This is the UDS service 0x29-0x00 handler */
/* !LINKSTO Dcm.Dsn.IB.Authentication.DeAuthenticate.SSvcH,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_Authentication_DeAuthenticate_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext)
{
  Std_ReturnType ServiceProcessStatus = DCM_E_ABORT;
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex = DCM_NUM_MAIN_CONNECTIONS;

  DBG_DCM_DSP_AUTHENTICATION_DEAUTHENTICATE_SSVCH_ENTRY(OpStatus, pMsgContext);

  switch (OpStatus)
  {
    case DCM_INITIAL:
      /* SID and SSID have been removed from request message context. */
      if (pMsgContext->reqDataLen == DCM_TOTAL_LENGTH_OFFSET_SSVC)
      {
        /* Find AuthenticationConnectionIndex */
        AuthenticationConnectionIndex = Dcm_MainConnectionConfig[Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].MainConnectionIndex].AuthenticatedIndex;
        /* !LINKSTO Dcm.EB.AuthenticationStateHandling.AuthenticationServiceRequest.DeAuthenticate.Authenticated.TransitionToDeauthenticated.RteModeSwitch,1 */
        Dcm_DiagnosticPolicyHandler_ResetAuthentication(AuthenticationConnectionIndex, TRUE);

        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.DeAuthenticate.PositiveResponse,1 */
        /* authenticationTask */
        pMsgContext->resData[0U] = DCM_AUTHENTICATION_DEAUTHENTICATE;
        /* authenticationReturnParameter */
        pMsgContext->resData[1U] = DCM_AUTHRESPONSE_DAS;

        pMsgContext->resDataLen = 2U;
        ServiceProcessStatus = E_OK;
      }
      else
      {
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.DeAuthenticate.TotalLengthCheckFailure.TransmitNRC0x13,1 */
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        ServiceProcessStatus = E_NOT_OK;
      }
      break;

    case DCM_CONFIRMED_OK:
    case DCM_CONFIRMED_NOK:
      /* do nothing */
      ServiceProcessStatus = E_OK;
      break;

    /* CHECK: NOPARSE */
    default:
      /* Defensive branch. Default case at the end of the switch statement */
      DCM_UNREACHABLE_CODE_ASSERT(DCM_INTERNAL_API_ID);
      break;
    /* CHECK: PARSE */
  }

  DBG_DCM_DSP_AUTHENTICATION_DEAUTHENTICATE_SSVCH_EXIT(ServiceProcessStatus, OpStatus, pMsgContext);

  return ServiceProcessStatus;
}
#endif /* #if (DCM_0X29_0X00_SSVC_ENABLED == STD_ON) */

#if (DCM_0X29_0X01_SSVC_ENABLED == STD_ON)
/* This is the UDS service 0x29-0x01 handler */
/* !LINKSTO Dcm.Dsn.IB.Authentication.VerifyCertificateUnidirectional.SSvcH,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_Authentication_VerifyCertificateUnidirectional_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext)
{
  Std_ReturnType ServiceProcessStatus = DCM_E_ABORT;
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex = DCM_NUM_MAIN_CONNECTIONS;
  boolean ProcessAuthenticationCalled = FALSE;

  DBG_DCM_DSP_AUTHENTICATION_VERIFYCERTIFICATEUNIDIRECTIONAL_SSVCH_ENTRY(OpStatus, pMsgContext);

  /* Find AuthenticationConnectionIndex */
  AuthenticationConnectionIndex = Dcm_MainConnectionConfig[Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].MainConnectionIndex].AuthenticatedIndex;

  switch (OpStatus)
  {
    case DCM_INITIAL:
      ServiceProcessStatus = Dcm_Dsp_Authentication_VerifyCertificateRequestCheck(
                               pMsgContext, &Dcm_Authentication_AuthenticationContext);

      if (E_OK == ServiceProcessStatus)
      {
        Dcm_Authentication_AuthenticationContext.AuthenticationDirection =
          DCM_AUTHENTICATIONDIRECTION_UNIDIRECTIONAL;

        /* initial call to ProcessAuthentication */
        ServiceProcessStatus = Dcm_AuthenticationHandler_AuthenticationProcess(
                                 AuthenticationConnectionIndex,
                                 &Dcm_Authentication_AuthenticationContext);
        ProcessAuthenticationCalled = TRUE;
      }
      break;

    case DCM_PENDING:
      Dcm_Authentication_AuthenticationContext.ErrorCode = E_NOT_OK;
      ServiceProcessStatus = Dcm_AuthenticationHandler_AuthenticationProcess(
                               AuthenticationConnectionIndex,
                               &Dcm_Authentication_AuthenticationContext);
      ProcessAuthenticationCalled = TRUE;
      break;

    case DCM_CANCEL:
      Dcm_AuthenticationHandler_CancelAuthentication(AuthenticationConnectionIndex);
      ServiceProcessStatus = E_OK;
      break;

    case DCM_CONFIRMED_OK:
      /* do nothing */
      ServiceProcessStatus = E_OK;
      break;

    case DCM_CONFIRMED_NOK:
      /* remove certificate in case of failed or cancelled transmission of positive response */
      Dcm_AuthenticationHandler_CancelAuthentication(AuthenticationConnectionIndex);
      ServiceProcessStatus = E_OK;
      break;

    /* CHECK: NOPARSE */
    default:
      /* Defensive branch. Default case at the end of the switch statement */
      DCM_UNREACHABLE_CODE_ASSERT(DCM_INTERNAL_API_ID);
      break;
    /* CHECK: PARSE */
  }

  if (TRUE == ProcessAuthenticationCalled)
  {
    switch (ServiceProcessStatus)
    {
      case E_OK:
      {
        if((pMsgContext->resMaxDataLen) >=
           (DCM_MINIMUM_LENGTH_OFFSET_RESPONSE_SSVC_0X01 +
            (Dcm_MsgLenType)Dcm_Authentication_AuthenticationContext.ChallengeServer.LengthOfChallenge))
        {
          /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsOK.LengthOfGeneratedRandomNumberSmaller.PositiveResponse,2 */
          /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.DcmCsmAsyncJobFinished.ReturnsOK.LengthOfGeneratedRandomNumberPrecise.PositiveResponse,2 */
          uint32 ResDataOffset = 0U;

          /* authenticationTask */
          pMsgContext->resData[ResDataOffset] = DCM_AUTHENTICATION_VERIFYCERTIFICATEUNIDIRECTIONAL;
          ResDataOffset++;
          /* authenticationReturnParameter */
          pMsgContext->resData[ResDataOffset] = DCM_AUTHRESPONSE_CVOVN;
          ResDataOffset++;
          /* lengthOfChallengeServer */
          pMsgContext->resData[ResDataOffset] =
            DCM_HIBYTE(Dcm_Authentication_AuthenticationContext.ChallengeServer.LengthOfChallenge);
          ResDataOffset++;
          pMsgContext->resData[ResDataOffset] =
            DCM_LOBYTE(Dcm_Authentication_AuthenticationContext.ChallengeServer.LengthOfChallenge);
          ResDataOffset++;
          /* challengeServer */
          TS_MemCpy(&pMsgContext->resData[ResDataOffset],
                Dcm_Authentication_AuthenticationContext.ChallengeServer.Challenge,
                Dcm_Authentication_AuthenticationContext.ChallengeServer.LengthOfChallenge);
          ResDataOffset +=
            Dcm_Authentication_AuthenticationContext.ChallengeServer.LengthOfChallenge;
          /* lengthOfEphemeralPublicKeyServer */
          pMsgContext->resData[ResDataOffset] = 0U;
          ResDataOffset++;
          pMsgContext->resData[ResDataOffset] = 0U;
          ResDataOffset++;

          pMsgContext->resDataLen = ResDataOffset;
        }
        else
        {
          Dcm_AuthenticationHandler_CancelAuthentication(AuthenticationConnectionIndex);
          /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateUnidirectional.TxBufferShort.TransmitNRC0x10,2 */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
          ServiceProcessStatus = E_NOT_OK;
        }
        break;
      }

      case E_NOT_OK:
        Dcm_ExternalSetNegResponse(pMsgContext, Dcm_Authentication_AuthenticationContext.ErrorCode);
        break;

      case DCM_E_PENDING:
        /* do nothing */
        break;

      /* CHECK: NOPARSE */
      default:
        /* Defensive branch. Default case at the end of the switch statement */
        DCM_UNREACHABLE_CODE_ASSERT(DCM_INTERNAL_API_ID);
        break;
      /* CHECK: PARSE */
    }
  }

  DBG_DCM_DSP_AUTHENTICATION_VERIFYCERTIFICATEUNIDIRECTIONAL_SSVCH_EXIT(ServiceProcessStatus, OpStatus, pMsgContext);

  return ServiceProcessStatus;
}
#endif /* #if (DCM_0X29_0X01_SSVC_ENABLED == STD_ON) */

#if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON)
/* This is the UDS service 0x29-0x02 handler */
/* !LINKSTO Dcm.Dsn.IB.Authentication.VerifyCertificateBidirectional.SSvcH,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_Authentication_VerifyCertificateBidirectional_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext)
{
  boolean ProcessAuthenticationCalled = FALSE;
  Std_ReturnType ServiceProcessStatus = DCM_E_ABORT;
  Dcm_NegativeResponseCodeType CurrentNrc = E_NOT_OK;
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex = DCM_NUM_MAIN_CONNECTIONS;

  DBG_DCM_DSP_AUTHENTICATION_VERIFYCERTIFICATEBIDIRECTIONAL_SSVCH_ENTRY(OpStatus, pMsgContext);

  /* Find AuthenticationConnectionIndex */
  AuthenticationConnectionIndex = Dcm_MainConnectionConfig[Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].MainConnectionIndex].AuthenticatedIndex;

  switch (OpStatus)
  {
    case DCM_INITIAL:
      ServiceProcessStatus = Dcm_Dsp_Authentication_VerifyCertificateRequestCheck(
                               pMsgContext, &Dcm_Authentication_AuthenticationContext);

      if (E_OK == ServiceProcessStatus)
      {
        CurrentNrc = Dcm_Dsp_Authentication_KeyMLengthChecks(
                       pMsgContext);
        if (E_OK == CurrentNrc)
        {
          /* certificateServer is written directly from Authentication handler */
          /* set up context for authentication */
          /* SID is not part of response message context */
          /* Position of certificate in the response:
              rsp[0]                                                                                    - authenticationTask = verifyCertificateBidirectional
              rsp[1]                                                                                    - authenticationReturnParameter
              rsp[2..3]                                                                                 - lengthOfChallengeServer
              rsp[4..4+lengthOfChallengeServer-1]                                                       - challengeServer
              rsp[4+lengthOfChallengeServer..4+lengthOfChallengeServer+1]                               - lengthOfCertificateServer
              rsp[4+lengthOfChallengeServer+2..4+lengthOfChallengeServer+2+lengthOfCertificateServer-1] - certificateServer */
          Dcm_Authentication_AuthenticationContext.CertificateServer.LengthOfCertificate =
            (pMsgContext->resMaxDataLen) - DCM_MINIMUM_LENGTH_OFFSET_RESPONSE_SSVC_0X02 -
            Dcm_AuthenticationConfigPtr->AuthenticationConnection[AuthenticationConnectionIndex].ChallengeLength;

          Dcm_Authentication_AuthenticationContext.CertificateServer.Certificate = &(pMsgContext->resData[6U +
            Dcm_AuthenticationConfigPtr->AuthenticationConnection[AuthenticationConnectionIndex].ChallengeLength]);

          /* initial call to ProcessAuthentication */
          ServiceProcessStatus = Dcm_AuthenticationHandler_AuthenticationProcess(
                                   AuthenticationConnectionIndex,
                                   &Dcm_Authentication_AuthenticationContext);

          ProcessAuthenticationCalled = TRUE;
        }
        else
        {
          /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.ZeroLengthOfCertificateServer.TransmitNRC0x10,1 */
          /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.ZeroLengthOfChallengeClient.TransmitNRC0x13,1 */
          Dcm_ExternalSetNegResponse(pMsgContext, CurrentNrc);
          ServiceProcessStatus = E_NOT_OK;
        }
      }
      break;

    case DCM_PENDING:
      Dcm_Authentication_AuthenticationContext.ErrorCode = E_NOT_OK;
      ServiceProcessStatus = Dcm_AuthenticationHandler_AuthenticationProcess(
                               AuthenticationConnectionIndex,
                               &Dcm_Authentication_AuthenticationContext);
      ProcessAuthenticationCalled = TRUE;
      break;

    case DCM_CANCEL:
      Dcm_AuthenticationHandler_CancelAuthentication(AuthenticationConnectionIndex);
      ServiceProcessStatus = E_OK;
      break;

    case DCM_CONFIRMED_OK:
      /* do nothing */
      ServiceProcessStatus = E_OK;
      break;

    case DCM_CONFIRMED_NOK:
      /* remove certificate in case of failed or cancelled transmission of positive response */
      Dcm_AuthenticationHandler_CancelAuthentication(AuthenticationConnectionIndex);
      ServiceProcessStatus = E_OK;
      break;

    /* CHECK: NOPARSE */
    default:
      /* Defensive branch. Default case at the end of the switch statement */
      DCM_UNREACHABLE_CODE_ASSERT(DCM_INTERNAL_API_ID);
      break;
    /* CHECK: PARSE */
  }

  if (TRUE == ProcessAuthenticationCalled)
  {
    switch (ServiceProcessStatus)
    {
      case E_OK:
      {
        if((pMsgContext->resMaxDataLen) >=
           (DCM_MINIMUM_LENGTH_OFFSET_RESPONSE_SSVC_0X02 +
            (Dcm_MsgLenType)Dcm_Authentication_AuthenticationContext.ChallengeServer.LengthOfChallenge +
            (Dcm_MsgLenType)Dcm_Authentication_AuthenticationContext.CertificateServer.LengthOfCertificate +
            (Dcm_MsgLenType)Dcm_Authentication_AuthenticationContext.ProofOfOwnershipServer.LengthOfProofOfOwnership))
        {
          /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.KeyMGetCertificate.ReturnsOK.NonZeroLengthOfCertificateServer.PositiveResponse,1 */
          uint32 ResDataOffset = 0U;

          /* authenticationTask */
          pMsgContext->resData[ResDataOffset] = DCM_AUTHENTICATION_VERIFYCERTIFICATEBIDIRECTIONAL;
          ResDataOffset++;
          /* authenticationReturnParameter */
          pMsgContext->resData[ResDataOffset] = DCM_AUTHRESPONSE_CVOVN;
          ResDataOffset++;
          /* lengthOfChallengeServer */
          pMsgContext->resData[ResDataOffset] =
            DCM_HIBYTE(Dcm_Authentication_AuthenticationContext.ChallengeServer.LengthOfChallenge);
          ResDataOffset++;
          pMsgContext->resData[ResDataOffset] =
            DCM_LOBYTE(Dcm_Authentication_AuthenticationContext.ChallengeServer.LengthOfChallenge);
          ResDataOffset++;
          /* challengeServer */
          TS_MemCpy(&pMsgContext->resData[ResDataOffset],
                Dcm_Authentication_AuthenticationContext.ChallengeServer.Challenge,
                Dcm_Authentication_AuthenticationContext.ChallengeServer.LengthOfChallenge);
          ResDataOffset +=
            Dcm_Authentication_AuthenticationContext.ChallengeServer.LengthOfChallenge;
          /* lengthOfCertificateServer */
          pMsgContext->resData[ResDataOffset] =
            DCM_HIBYTE(Dcm_Authentication_AuthenticationContext.CertificateServer.LengthOfCertificate);
          ResDataOffset++;
          pMsgContext->resData[ResDataOffset] =
            DCM_LOBYTE(Dcm_Authentication_AuthenticationContext.CertificateServer.LengthOfCertificate);
          ResDataOffset++;
          /* certificateServer is written directly from Authentication handler */
          ResDataOffset +=
            Dcm_Authentication_AuthenticationContext.CertificateServer.LengthOfCertificate;
          /* lengthOfproofOfOwnershipServer */
          pMsgContext->resData[ResDataOffset] =
            DCM_HIBYTE(Dcm_Authentication_AuthenticationContext.ProofOfOwnershipServer.LengthOfProofOfOwnership);
          ResDataOffset++;
          pMsgContext->resData[ResDataOffset] =
            DCM_LOBYTE(Dcm_Authentication_AuthenticationContext.ProofOfOwnershipServer.LengthOfProofOfOwnership);
          ResDataOffset++;
          /* proofOfOwnershipServer */
          TS_MemCpy(&pMsgContext->resData[ResDataOffset],
                Dcm_Authentication_AuthenticationContext.ProofOfOwnershipServer.ProofOfOwnership,
                Dcm_Authentication_AuthenticationContext.ProofOfOwnershipServer.LengthOfProofOfOwnership);
          ResDataOffset +=
            Dcm_Authentication_AuthenticationContext.ProofOfOwnershipServer.LengthOfProofOfOwnership;
          /* lengthOfEphemeralPublicKeyServer */
          pMsgContext->resData[ResDataOffset] = 0U;
          ResDataOffset++;
          pMsgContext->resData[ResDataOffset] = 0U;
          ResDataOffset++;

          pMsgContext->resDataLen = ResDataOffset;
        }
        else
        {
          /* remove certificate in case of negative response */
          Dcm_AuthenticationHandler_CancelAuthentication(AuthenticationConnectionIndex);

          /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.VerifyCertificateBidirectional.TxBufferShort.TransmitNRC0x10,1 */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
          ServiceProcessStatus = E_NOT_OK;
        }
        break;
      }

      case E_NOT_OK:
        Dcm_ExternalSetNegResponse(pMsgContext, Dcm_Authentication_AuthenticationContext.ErrorCode);
        break;

      case DCM_E_PENDING:
        /* do nothing */
        break;

      /* CHECK: NOPARSE */
      default:
        /* Defensive branch. Default case at the end of the switch statement */
        DCM_UNREACHABLE_CODE_ASSERT(DCM_INTERNAL_API_ID);
        break;
      /* CHECK: PARSE */
    }
  }

  DBG_DCM_DSP_AUTHENTICATION_VERIFYCERTIFICATEBIDIRECTIONAL_SSVCH_EXIT(ServiceProcessStatus, OpStatus, pMsgContext);

  return ServiceProcessStatus;
}
#endif /* #if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON) */

#if (DCM_0X29_0X03_SSVC_ENABLED == STD_ON)
/* This is the UDS service 0x29-0x03 handler */
/* !LINKSTO Dcm.Dsn.IB.Authentication.ProofOfOwnership.SSvcH,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_Authentication_ProofOfOwnership_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext)
{
  Dcm_AuthenticationProofOfOwnershipType ProofOfOwnershipClient;
  Dcm_NegativeResponseCodeType ErrorCode = DCM_E_POSITIVERESPONSE;
  Std_ReturnType ServiceProcessStatus = DCM_E_ABORT;
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex = DCM_NUM_MAIN_CONNECTIONS;
  boolean ProofOfOwnershipCalled = FALSE;

  DBG_DCM_DSP_AUTHENTICATION_PROOFOFOWNERSHIP_SSVCH_ENTRY(OpStatus, pMsgContext);

  /* Find AuthenticationConnectionIndex */
  AuthenticationConnectionIndex = Dcm_MainConnectionConfig[Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].MainConnectionIndex].AuthenticatedIndex;

  switch (OpStatus)
  {
    case DCM_INITIAL:
      /* SID and SSID have been removed from request message context. */
      if (pMsgContext->reqDataLen >= DCM_MINIMUM_LENGTH_OFFSET_SSVC_0X03)
      {
        uint8 HighByteProofLen = (uint8)pMsgContext->reqData[0U];
        uint8 LowByteProofLen  = (uint8)pMsgContext->reqData[1U];

        uint16 ClientProofLength =
          (uint16) DCM_COMPOSE_16BIT_WORD_FROM_MSB_AND_LSB(HighByteProofLen, LowByteProofLen);

        if (ClientProofLength != 0U)
        {
          if ((pMsgContext->reqDataLen) >=
              (DCM_MANDATORY_LENGTH_OFFSET_SSVC_0X03 + (Dcm_MsgLenType)ClientProofLength))
          {
            uint8 HighByteKey = (uint8)pMsgContext->reqData[2U + ClientProofLength];
            uint8 LowByteKey  = (uint8)pMsgContext->reqData[3U + ClientProofLength];

            uint16 ClientKeyLength =
              (uint16) DCM_COMPOSE_16BIT_WORD_FROM_MSB_AND_LSB(HighByteKey, LowByteKey);

            if ((pMsgContext->reqDataLen) ==
                (DCM_MANDATORY_LENGTH_OFFSET_SSVC_0X03 +
                 (Dcm_MsgLenType)ClientProofLength + (Dcm_MsgLenType)ClientKeyLength))
            {
              /* set up context for authentication */
              ProofOfOwnershipClient.ProofOfOwnership = &(pMsgContext->reqData[2U]);
              ProofOfOwnershipClient.LengthOfProofOfOwnership = ClientProofLength;

              /* initial call to ProofOfOwnership */
              ServiceProcessStatus = Dcm_AuthenticationHandler_ProofOfOwnership(AuthenticationConnectionIndex,
                                                                                ProofOfOwnershipClient, &ErrorCode);
              ProofOfOwnershipCalled = TRUE;
            }
            else
            {
              /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.TotalLengthCheckFailure.TransmitNRC0x13,1 */
              Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
              ServiceProcessStatus = E_NOT_OK;
              Dcm_AuthenticationHandler_CancelAuthentication(AuthenticationConnectionIndex);
            }
          }
          else
          {
            /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.MandatoryBytesLengthCheckFailure.TransmitNRC0x13,1 */
            Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
            ServiceProcessStatus = E_NOT_OK;
            Dcm_AuthenticationHandler_CancelAuthentication(AuthenticationConnectionIndex);
          }
        }
        else
        {
          /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.ZeroLengthOfProofOfOwnershipClient.TransmitNRC0x13,1 */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
          ServiceProcessStatus = E_NOT_OK;
          Dcm_AuthenticationHandler_CancelAuthentication(AuthenticationConnectionIndex);
        }
      }
      else
      {
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.MinimumLengthCheckFailure.TransmitNRC0x13,1 */
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        ServiceProcessStatus = E_NOT_OK;
        Dcm_AuthenticationHandler_CancelAuthentication(AuthenticationConnectionIndex);
      }
      break;

    case DCM_PENDING:
      /* ProofOfOwnershipClient structure member is used just in DCM_INITIAL with authentication state
       * set to CERTIFICATEVERIFIED, after the initial call the authentication state is change in
       * PROOFOFOWNERSHIP and just the ErrorCode parameter is used */
      ProofOfOwnershipClient.ProofOfOwnership = NULL_PTR;
      ProofOfOwnershipClient.LengthOfProofOfOwnership = 0x00U;

      ServiceProcessStatus = Dcm_AuthenticationHandler_ProofOfOwnership(AuthenticationConnectionIndex,
                                                                        ProofOfOwnershipClient, &ErrorCode);
      ProofOfOwnershipCalled = TRUE;
      break;

    case DCM_CANCEL:
      Dcm_AuthenticationHandler_CancelAuthentication(AuthenticationConnectionIndex);
      ServiceProcessStatus = E_OK;
      break;

    case DCM_CONFIRMED_OK:
    case DCM_CONFIRMED_NOK:
      /* do nothing; certificate is already removed */
      ServiceProcessStatus = E_OK;
      break;

    /* CHECK: NOPARSE */
    default:
      /* Defensive branch. Default case at the end of the switch statement */
      DCM_UNREACHABLE_CODE_ASSERT(DCM_INTERNAL_API_ID);
      break;
    /* CHECK: PARSE */
  }

  if (TRUE == ProofOfOwnershipCalled)
  {
    switch (ServiceProcessStatus)
    {
      case E_OK:
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.AuthenticationStateUpdated.PositiveResponse,1 */
        /* authenticationTask */
        pMsgContext->resData[0U] = DCM_AUTHENTICATION_PROOFOFOWNERSHIP;
        /* authenticationReturnParameter */
        pMsgContext->resData[1U] = DCM_AUTHRESPONSE_OVAC;
        /* lengthOfSessionKeyInfo */
        pMsgContext->resData[2U] = 0U;
        pMsgContext->resData[3U] = 0U;

        pMsgContext->resDataLen = 4U;
        break;

      case E_NOT_OK:
        Dcm_ExternalSetNegResponse(pMsgContext, ErrorCode);
        break;

      case DCM_E_PENDING:
        /* do nothing */
        break;

      /* CHECK: NOPARSE */
      default:
        /* Defensive branch. Default case at the end of the switch statement */
        DCM_UNREACHABLE_CODE_ASSERT(DCM_INTERNAL_API_ID);
        break;
      /* CHECK: PARSE */
    }
  }

  DBG_DCM_DSP_AUTHENTICATION_PROOFOFOWNERSHIP_SSVCH_EXIT(ServiceProcessStatus, OpStatus, pMsgContext);

  return ServiceProcessStatus;
}
#endif /* #if (DCM_0X29_0X03_SSVC_ENABLED == STD_ON) */

#if (DCM_0X29_0X08_SSVC_ENABLED == STD_ON)
/* This is the UDS service 0x29-0x08 handler */
/* !LINKSTO Dcm.Dsn.IB.Authentication.AuthenticationConfiguration.SSvcH,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_Authentication_AuthenticationConfiguration_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext)
{
  Std_ReturnType ServiceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSP_AUTHENTICATION_AUTHENTICATIONCONFIGURATION_SSVCH_ENTRY(OpStatus, pMsgContext);

  switch (OpStatus)
  {
    case DCM_INITIAL:
      /* SID and SSID have been removed from request message context. */
      if (pMsgContext->reqDataLen == DCM_TOTAL_LENGTH_OFFSET_SSVC)
      {
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.AuthenticationConfiguration.PositiveResponse,1 */
        /* authenticationTask */
        pMsgContext->resData[0U] = DCM_AUTHENTICATION_AUTHENTICATIONCONFIGURATION;
        /* authenticationReturnParameter */
        pMsgContext->resData[1U] = DCM_AUTHRESPONSE_ACAPCE;

        pMsgContext->resDataLen = 2U;
        ServiceProcessStatus = E_OK;
      }
      else
      {
        /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.AuthenticationConfiguration.TotalLengthCheckFailure.TransmitNRC0x13,1 */
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        ServiceProcessStatus = E_NOT_OK;
      }
      break;

    case DCM_CONFIRMED_OK:
    case DCM_CONFIRMED_NOK:
      /* do nothing */
      ServiceProcessStatus = E_OK;
      break;

    /* CHECK: NOPARSE */
    default:
      /* Defensive branch. Default case at the end of the switch statement */
      DCM_UNREACHABLE_CODE_ASSERT(DCM_INTERNAL_API_ID);
      break;
    /* CHECK: PARSE */
  }

  DBG_DCM_DSP_AUTHENTICATION_AUTHENTICATIONCONFIGURATION_SSVCH_EXIT(ServiceProcessStatus, OpStatus, pMsgContext);

  return ServiceProcessStatus;
}
#endif /* #if (DCM_0X29_0X08_SSVC_ENABLED == STD_ON) */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif /* #if (DCM_DSP_USE_SERVICE_0X29 == STD_ON) */

/*==================[end of file]================================================================*/
