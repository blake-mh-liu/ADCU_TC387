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

/* tasking Deviation List
 *
 *  TASKING-1) Deviated Rule: W549
 *    W549: condition is always false
 *
 *    Reason:
 *    Condition depends on preprocessor settings that is configuration specific. Under certain configurations
 *    the conditions can be either always true or always false. This does not pose any functional risk.
 */

/* !LINKSTO Dcm.Dsn.File.SEVReportingServices.Impl,1 */
/* This file contains the implementation of the SEV Reporting Services SW unit. */

/*==================[includes]===================================================================*/

#include <Std_Types.h>                                   /* AUTOSAR standard types */
#include <TSAutosar.h>
#include <Dcm_Cfg.h>
#include <Dcm_Trace.h>
#include <Dcm_Int.h>

#if (DCM_SECURITY_EVENT_REPORTING == STD_ON)
#include <IdsM.h>
#include <Dcm_SEVReportingServices.h>

/*==================[macro definitions]==========================================================*/

/** \brief size of context data */
#if (defined DCM_SEV_CONTEXT_DATA_SIZE_FIVE_BYTES)
#error DCM_SEV_CONTEXT_DATA_SIZE_FIVE_BYTES already defined!
#endif /* #if( defined DCM_SEV_CONTEXT_DATA_SIZE_FIVE_BYTES)*/
#define DCM_SEV_CONTEXT_DATA_SIZE_FIVE_BYTES         5U

/** \brief size of context data */
#if (defined DCM_SEV_CONTEXT_DATA_SIZE_SIX_BYTES)
#error DCM_SEV_CONTEXT_DATA_SIZE_SIX_BYTES already defined!
#endif /* #if( defined DCM_SEV_CONTEXT_DATA_SIZE_SIX_BYTES)*/
#define DCM_SEV_CONTEXT_DATA_SIZE_SIX_BYTES          6U

/** \brief size of context data */
#if (defined DCM_SEV_CONTEXT_DATA_SIZE_SEVEN_BYTES)
#error DCM_SEV_CONTEXT_DATA_SIZE_SEVEN_BYTES already defined!
#endif /* #if( defined DCM_SEV_CONTEXT_DATA_SIZE_SEVEN_BYTES)*/
#define DCM_SEV_CONTEXT_DATA_SIZE_SEVEN_BYTES        7U

/** \brief Response message positive bit */
#if (defined DCM_SEV_POSITIVERESPONSEBIT)
#error DCM_SEV_POSITIVERESPONSEBIT already defined!
#endif /* #if( defined DCM_SEV_POSITIVERESPONSEBIT)*/
#define DCM_SEV_POSITIVERESPONSEBIT               0x40U

/** \brief invalid SEV event reference */
#if (defined DCM_DIDRELATED_SID)
#error DCM_DIDRELATED_SID already defined!
#endif /* #if( defined DCM_DIDRELATED_SID)*/

/** \brief Checks is Servce ID is for DID related service */
#define DCM_IS_DIDRELATED_SID(ServiceId) \
  ( ((ServiceId == DCM_SID_READDATABYID) || \
     (ServiceId == DCM_SID_READSCALINGDATABYID) || \
     (ServiceId == DCM_SID_DYNDEFDATAID) || \
     (ServiceId == DCM_SID_WRITEDATABYID) || \
     (ServiceId == DCM_SID_IOCONTROLBYID) || \
     (ServiceId == DCM_SID_READDATABYPERIODICID) ) \
   ? TRUE : FALSE)

/** \brief SEV events using ServiceId are all disabled for function Dcm_SEVReportingServices_IdsMSetSecurityEvent_NRC_CheckSEV */
#define DCM_NRCCHECKSEV_SIDNOTUSED  (DIAG_SEV_ECU_RESET == DCM_SEV_INVALID_SEV_REF) && \
                                    (DIAG_SEV_DID_NOT_SUPPORTED == DCM_SEV_INVALID_SEV_REF) && \
                                    (DIAG_SEV_RID_NOT_SUPPORTED == DCM_SEV_INVALID_SEV_REF) && \
                                    (DIAG_SEV_SECURITY_ACCESS_INVALID_KEY == DCM_SEV_INVALID_SEV_REF) && \
                                    (DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED == DCM_SEV_INVALID_SEV_REF) && \
                                    (DIAG_SEV_CERTIFICATE_FAILURE == DCM_SEV_INVALID_SEV_REF) && \
                                    (DIAG_SEV_WRITE_INV_DATA == DCM_SEV_INVALID_SEV_REF)

/** \brief SEV events using OutputType are all disabled for function Dcm_SEVReportingServices_IdsMSetSecurityEvent_NRC_CheckSEV */
#define DCM_NRCCHECKSEV_OUTPUTTYPENOTUSED (DIAG_SEV_DID_NOT_SUPPORTED == DCM_SEV_INVALID_SEV_REF) && \
                                          (DIAG_SEV_RID_NOT_SUPPORTED == DCM_SEV_INVALID_SEV_REF) && \
                                          (DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED == DCM_SEV_INVALID_SEV_REF)&& \
                                          (DIAG_SEV_WRITE_INV_DATA == DCM_SEV_INVALID_SEV_REF)

/** \brief Remove the switch statement in function Dcm_SEVReportingServices_IdsMSetSecurityEvent_NRC_CheckSEV when
 **        all cases are configured out. */
#define DCM_SEV_NRCCHECKSEV_ATLEASTONECASE ((DCM_AUTHENTICATION_CONNECTION == STD_ON) && (DIAG_SEV_CERTIFICATE_FAILURE != DCM_SEV_INVALID_SEV_REF)) || \
                                           (DIAG_SEV_SERVICE_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF) || \
                                           (DIAG_SEV_SUBFUNCTION_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF) || \
                                           (DIAG_SEV_INCORRECT_MESSAGE_LENGTH_OR_FORMAT != DCM_SEV_INVALID_SEV_REF) || \
                                           (DIAG_SEV_ECU_RESET != DCM_SEV_INVALID_SEV_REF) || \
                                           (DIAG_SEV_REQUEST_SEQUENCE_ERROR != DCM_SEV_INVALID_SEV_REF) || \
                                           ((DIAG_SEV_REQUEST_OUT_OF_RANGE != DCM_SEV_INVALID_SEV_REF) || \
                                            (DIAG_SEV_DID_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF) || \
                                            (DIAG_SEV_RID_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF) || \
                                            (DIAG_SEV_WRITE_INV_DATA != DCM_SEV_INVALID_SEV_REF) ) || \
                                           (DIAG_SEV_SECURITY_ACCESS_DENIED != DCM_SEV_INVALID_SEV_REF) || \
                                           (DIAG_SEV_REQUESTED_ACTIONS_REQUIRES_AUTHENTICATION != DCM_SEV_INVALID_SEV_REF) || \
                                           (DIAG_SEV_SECURITY_ACCESS_INVALID_KEY != DCM_SEV_INVALID_SEV_REF) || \
                                           ((DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED != DCM_SEV_INVALID_SEV_REF) && \
                                            (DCM_NUM_CONFIGURED_SECURITY_LEVELS > 0U) && \
                                            (DCM_DSP_SECURITYACCESS_DELAY_TIMERS_ENABLED == STD_ON) ) || \
                                           (DIAG_SEV_SECURITY_ACCESS_REQUIRED_TIME_DELAY_NOT_EXPIRED != DCM_SEV_INVALID_SEV_REF) || \
                                           ((DCM_AUTHENTICATION_CONNECTION == STD_ON) && (DIAG_SEV_CERTIFICATE_FAILURE != DCM_SEV_INVALID_SEV_REF)) || \
                                           (DIAG_SEV_WRITE_INV_DATA != DCM_SEV_INVALID_SEV_REF)

/** \brief Remove the switch statement in function Dcm_SEVReportingServices_IdsMSetSecurityEvent_CheckSEV when
 **        all cases are configured out. */
#define DCM_SEV_CHECKSEV_ATLEASTONECASE (DIAG_SEV_ECU_RESET != DCM_SEV_INVALID_SEV_REF) || \
                                        (DIAG_SEV_CLEAR_DTC_SUCCESSFUL != DCM_SEV_INVALID_SEV_REF) || \
                                        (DIAG_SEV_ECU_UNLOCK_SUCCESSFUL != DCM_SEV_INVALID_SEV_REF) || \
                                        (DIAG_SEV_COMMUNICATION_CONTROL_SWITCHED_OFF != DCM_SEV_INVALID_SEV_REF) || \
                                        ((DIAG_SEV_AUTHENTICATION_SUCCESSFUL != DCM_SEV_INVALID_SEV_REF) && \
                                         ((DCM_DSP_USE_SERVICE_0X29 == STD_ON) || (DCM_AUTHENTICATION_CONNECTION == STD_ON)) ) || \
                                        (DIAG_SEV_WRITE_DATA != DCM_SEV_INVALID_SEV_REF) || \
                                        (DIAG_SEV_REQUEST_DOWNLOAD != DCM_SEV_INVALID_SEV_REF) || \
                                        (DIAG_SEV_DTC_SETTING_SWITCHED_OFF != DCM_SEV_INVALID_SEV_REF)

/*==================[type declarations]==========================================================*/

/*==================[internal function declarations]=============================================*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/** \brief Checks if a security event with an NRC has occurred
 **
 ** \param[in]    ServiceId        Service ID reporting the SEV event
 ** \param[in]    ErrorCode        NRC error code to be reported with event
 ** \param[out]   OutputType       Ptr to type of output
                                   - Context data length
                                     - DCM_SEV_CONTEXT_DATA_SIZE_FIVE_BYTES
                                     - DCM_SEV_CONTEXT_DATA_SIZE_SIX_BYTES
                                     - DCM_SEV_CONTEXT_DATA_SIZE_SEVEN_BYTES
 **
 ** \retval SecurityEventId        Security Event ID
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(IdsM_SecurityEventIdType, DCM_CODE) Dcm_SEVReportingServices_IdsMSetSecurityEvent_NRC_CheckSEV(
  uint8                         ServiceId,
  Dcm_NegativeResponseCodeType  ErrorCode,
  P2VAR(uint8, AUTOMATIC, DCM_VAR)  OutputType
);

/** \brief Checks if a security event due to a positive response has occurred
 **
 ** \param[in]    instIdx          HSM instance index
 ** \param[in]    ServiceId        Service ID reporting the SEV event
 **
 ** \retval SecurityEventId        Security Event ID
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(IdsM_SecurityEventIdType, DCM_CODE) Dcm_SEVReportingServices_IdsMSetSecurityEvent_CheckSEV(
  uint8                         instIdx,
  uint8                         ServiceId
);


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
/*==================[internal constants]=========================================================*/

/*==================[internal data]==============================================================*/

#if (DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED != DCM_SEV_INVALID_SEV_REF)
#if (DCM_NUM_CONFIGURED_SECURITY_LEVELS > 0U)
#if (DCM_DSP_SECURITYACCESS_DELAY_TIMERS_ENABLED == STD_ON)
#define DCM_START_SEC_VAR_CLEARED_8
#include <Dcm_MemMap.h>

STATIC VAR(uint8, DCM_VAR) Dcm_SecurityAttemptCounter;

#define DCM_STOP_SEC_VAR_CLEARED_8
#include <Dcm_MemMap.h>
#endif /* #if (DCM_DSP_SECURITYACCESS_DELAY_TIMERS_ENABLED == STD_ON) */
#endif /* #if (DCM_NUM_CONFIGURED_SECURITY_LEVELS > 0U) */
#endif /* #if (DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED != DCM_SEV_INVALID_SEV_REF) */

#if ((DCM_AUTHENTICATION_CONNECTION == STD_ON) && (DIAG_SEV_CERTIFICATE_FAILURE != DCM_SEV_INVALID_SEV_REF))
#define DCM_START_SEC_VAR_CLEARED_8
#include <Dcm_MemMap.h>

STATIC VAR(boolean, DCM_VAR) Dcm_AuthenticationCertificateFailureGeneralRejectNRC;

#define DCM_STOP_SEC_VAR_CLEARED_8
#include <Dcm_MemMap.h>
#endif /* #if ((DCM_AUTHENTICATION_CONNECTION == STD_ON) && (DIAG_SEV_CERTIFICATE_FAILURE != DCM_SEV_INVALID_SEV_REF)) */

#if ( (DCM_DSP_USE_SERVICE_0X2E == STD_ON) && \
      ((DIAG_SEV_DID_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF) || \
       (DIAG_SEV_WRITE_INV_DATA != DCM_SEV_INVALID_SEV_REF) ) )
#define DCM_START_SEC_VAR_CLEARED_8
#include <Dcm_MemMap.h>

STATIC VAR(boolean, DCM_VAR) Dcm_WriteDidROORDidNotSupported;

#define DCM_STOP_SEC_VAR_CLEARED_8
#include <Dcm_MemMap.h>
#endif

/*==================[external constants]=========================================================*/

/*==================[external data]==============================================================*/

/*==================[external function definitions]==============================================*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/* !LINKSTO Dcm.Dsn.IB.SEVReportingServices.Init,1 */
FUNC(void, DCM_CODE) Dcm_SEVReportingServices_Init(void)
{
#if (DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED != DCM_SEV_INVALID_SEV_REF)
#if (DCM_NUM_CONFIGURED_SECURITY_LEVELS > 0U)
#if (DCM_DSP_SECURITYACCESS_DELAY_TIMERS_ENABLED == STD_ON)
  Dcm_SecurityAttemptCounter = 0U;
#endif /* #if (DCM_DSP_SECURITYACCESS_DELAY_TIMERS_ENABLED == STD_ON) */
#endif /* #if (DCM_NUM_CONFIGURED_SECURITY_LEVELS > 0U) */
#endif /* #if (DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED != DCM_SEV_INVALID_SEV_REF) */

#if ((DCM_AUTHENTICATION_CONNECTION == STD_ON) && (DIAG_SEV_CERTIFICATE_FAILURE != DCM_SEV_INVALID_SEV_REF))
  Dcm_AuthenticationCertificateFailureGeneralRejectNRC = FALSE;
#endif /* #if ((DCM_AUTHENTICATION_CONNECTION == STD_ON) && (DIAG_SEV_CERTIFICATE_FAILURE != DCM_SEV_INVALID_SEV_REF)) */

#if ((DCM_DSP_USE_SERVICE_0X2E == STD_ON) && \
     ((DIAG_SEV_DID_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF) || \
      (DIAG_SEV_WRITE_INV_DATA != DCM_SEV_INVALID_SEV_REF) ) )
  Dcm_WriteDidROORDidNotSupported = FALSE;
#endif
}

/* !LINKSTO Dcm.Dsn.IB.SEVReportingServices.ReportSEVEventWithNRC,1 */
FUNC(void, DCM_CODE) Dcm_SEVReportingServices_IdsMSetSecurityEvent_NRC(
  uint8                         instIdx,
  uint8                         ServiceId,
  Dcm_NegativeResponseCodeType  ErrorCode
)
{

  Dcm_ProtocolType              TesterType;
  Dcm_TesterSourceAddressType   TesterID;

  IdsM_SecurityEventIdType  SecurityEventId = DCM_SEV_INVALID_SEV_REF;
  uint8                     OutputType = DCM_SEV_CONTEXT_DATA_SIZE_FIVE_BYTES;

  /* Getter for TesterType and TesterID */
  Dcm_Dsp_GetTesterInformation( instIdx, &TesterType, &TesterID);

  DBG_DCM_SEVREPORTINGSERVICES_REPORTSEVEVENTWITHNRC_ENTRY(instIdx, ServiceId, ErrorCode);

  /* Check that the event shall be reported */
  /* This is the look-up table comparing the SID and NRC and the configured SEV events */
  SecurityEventId = Dcm_SEVReportingServices_IdsMSetSecurityEvent_NRC_CheckSEV(
                                        ServiceId,
                                        ErrorCode,
                                        &OutputType);

#if ((DIAG_SEV_DID_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF) || (DIAG_SEV_RID_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF))
  /* When SEV is to be reported format the context data and send the event to IdsM */
  if (((SecurityEventId == DIAG_SEV_DID_NOT_SUPPORTED) || (SecurityEventId == DIAG_SEV_RID_NOT_SUPPORTED)) &&
      (OutputType == DCM_SEV_CONTEXT_DATA_SIZE_SEVEN_BYTES))
  {
    uint8   ContextData[DCM_SEV_CONTEXT_DATA_SIZE_SEVEN_BYTES];
    uint8   ContextDataSize = DCM_SEV_CONTEXT_DATA_SIZE_SEVEN_BYTES;

    /* Format Context Data in context data buffer and send to IdsM */
    ContextData[0U] = TesterType;
    ContextData[1U] = (uint8)(TesterID & 0x00FFU);
    ContextData[2U] = (uint8)((TesterID & 0xFF00U)>> 8U);
    ContextData[3U] = ServiceId;
    ContextData[4U] = ErrorCode;

    /* For DIAG_SEV_DID_NOT_SUPPORTED and DIAG_SEV_RID_NOT_SUPPORTED the DID or RID must be fetched.
       This is copied to the last 2 bytes of the ContextData */
    Dcm_Dsp_GetRequestContextDataInformation (instIdx, &ContextData[5U]);

    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.DcmEnableSecurityEventReporting,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.DcmEnableSecurityEventReporting.SEVEvents,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.DidNotSupported.ReadDataByIdRejectedNRC0x31.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.DidNotSupported.ReadScalingDataByIdRejectedNRC0x31.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.DidNotSupported.ReadDataByPeriodicIdRejectedNRC0x31.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.DidNotSupported.DynamicallyDefineDataIdentifierRejectedNRC0x31.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.DidNotSupported.WriteDataByIdRejectedNRC0x31.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.DidNotSupported.IOControlDataByIdRejectedNRC0x31.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.RidNotSupported.SetSecurityEventWithContextData.Call,1 */
    IdsM_SetSecurityEventWithContextData (
                                SecurityEventId,
                                ContextData,
                                ContextDataSize);
  }
  else
#endif /* #if ((DIAG_SEV_DID_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF) || (DIAG_SEV_RID_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF)) */
#if (DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED != DCM_SEV_INVALID_SEV_REF)
#if (DCM_NUM_CONFIGURED_SECURITY_LEVELS > 0U)
#if (DCM_DSP_SECURITYACCESS_DELAY_TIMERS_ENABLED == STD_ON)
  if ((SecurityEventId == DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED) &&
      (OutputType == DCM_SEV_CONTEXT_DATA_SIZE_SIX_BYTES))
  {
     uint8   ContextData[DCM_SEV_CONTEXT_DATA_SIZE_SIX_BYTES];
     uint8   ContextDataSize = DCM_SEV_CONTEXT_DATA_SIZE_SIX_BYTES;

     /* Format Context Data in context data buffer and send to IdsM */
     ContextData[0U] = TesterType;
     ContextData[1U] = (uint8)(TesterID & 0x00FFU);
     ContextData[2U] = (uint8)((TesterID & 0xFF00U)>> 8U);
     ContextData[3U] = ServiceId;
     ContextData[4U] = ErrorCode;
     ContextData[5U] = Dcm_SecurityAttemptCounter;

    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.DcmEnableSecurityEventReporting,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.DcmEnableSecurityEventReporting.SEVEvents,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.AccessNumberOfAttemptsExceeded.SetSecurityEventWithContextData.Call,1 */
    IdsM_SetSecurityEventWithContextData (
                                SecurityEventId,
                                ContextData,
                                ContextDataSize);
  }
  else
#endif /* #if (DCM_DSP_SECURITYACCESS_DELAY_TIMERS_ENABLED == STD_ON) */
#endif /* #if (DCM_NUM_CONFIGURED_SECURITY_LEVELS > 0U) */
#endif /* #if (DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED != DCM_SEV_INVALID_SEV_REF) */
  /* Deviation TASKING-1 */
  if (SecurityEventId != DCM_SEV_INVALID_SEV_REF)
  {

    uint8   ContextData[DCM_SEV_CONTEXT_DATA_SIZE_FIVE_BYTES];
    uint8   ContextDataSize = DCM_SEV_CONTEXT_DATA_SIZE_FIVE_BYTES;

    /* Format Context Data in context data buffer and send to IdsM */
    ContextData[0U] = TesterType;
    ContextData[1U] = (uint8)(TesterID & 0x00FFU);
    ContextData[2U] = (uint8)((TesterID & 0xFF00U)>> 8U);
    ContextData[3U] = ServiceId;
    ContextData[4U] = ErrorCode;

    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.DcmEnableSecurityEventReporting,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.DcmEnableSecurityEventReporting.SEVEvents,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.SubfunctionNotSupported.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.ServiceNotSupported.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.ServiceNotSupportedInActiveSession.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.SecurityAccessDenied.ServiceNotSupportedInTheCurrentSecurityLevel.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.SecurityAccessDenied.SubServiceNotSupportedInTheCurrentSecurityLevel.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.SecurityAccessDenied.DidNotSupportedInTheCurrentSecurityLevel.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.SecurityAccessDenied.MemoryRangeNotSupportedInTheCurrentSecurityLevel.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.SecurityAccessDenied.RoutineNotSupportedInTheCurrentSecurityLevel.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.AuthenticationRequired.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.TesterWritesInvalidData.RequestOutOfRange0x31.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.TesterWritesInvalidData.GeneralProgrammingFailure0x72.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.SecurityAccessInvalidKey.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.AuthenticationWithAnInvalidCertficate.DcmKeyMAsyncCertificateVerifyFinished.ReturnsCertificateInvalid.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.AuthenticationWithAnInvalidCertficate.DcmKeyMAsyncCertificateVerifyFinished.ReturnsValidityPeriodFailed.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.AuthenticationWithAnInvalidCertficate.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidSignature.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.AuthenticationWithAnInvalidCertficate.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidChainOfTrust.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.AuthenticationWithAnInvalidCertficate.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidType.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.AuthenticationWithAnInvalidCertficate.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidFormat.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.AuthenticationWithAnInvalidCertficate.KeyMCertElementGet.InvalidContent.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.AuthenticationWithAnInvalidCertficate.DcmKeyMAsyncCertificateVerifyFinished.ReturnsInvalidContent.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.AuthenticationWithAnInvalidCertficate.DcmKeyMAsyncCertificateVerifyFinished.ReturnsCertificateRevoked.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.SecurityAccessRequiredTimeDelayNotExpired.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.RequestOutOfRange.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.EcuReset.NegativeResponse.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.RoutineControl.WrongSequenceOrder.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.SecurityAccess.WrongSequenceOrder.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.TransferData.WrongSequenceOrder.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.RequestTransferExit.WrongSequenceOrder.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.ResponseOnEvent.WrongSequenceOrder.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.AuthenticationServiceRequest.WrongSequenceOrder.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.LinkControl.WrongSequenceOrder.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.IncorrectMessageLengthOrInvalidFormat.SetSecurityEventWithContextData.Call,1 */
    IdsM_SetSecurityEventWithContextData (
                                SecurityEventId,
                                ContextData,
                                ContextDataSize);
  }
  else
  {
  /* Implicit else do not report a security event */
  }

  DBG_DCM_SEVREPORTINGSERVICES_REPORTSEVEVENTWITHNRC_EXIT(instIdx, ServiceId, ErrorCode);

}

/* !LINKSTO Dcm.Dsn.IB.SEVReportingServices.ReportSEVEvent,1 */
FUNC(void, DCM_CODE) Dcm_SEVReportingServices_IdsMSetSecurityEvent(
  uint8 instIdx,
  uint8 ServiceId
)
{
  Dcm_ProtocolType              TesterType;
  Dcm_TesterSourceAddressType   TesterID;

  IdsM_SecurityEventIdType      SecurityEventId = DCM_SEV_INVALID_SEV_REF;
  uint8                         ContextData[DCM_SEV_CONTEXT_DATA_SIZE_FIVE_BYTES];
  uint8                         ContextDataSize = DCM_SEV_CONTEXT_DATA_SIZE_FIVE_BYTES;

  /* Getter for TesterType and TesterID */
  Dcm_Dsp_GetTesterInformation( instIdx, &TesterType, &TesterID);

  DBG_DCM_SEVREPORTINGSERVICES_REPORTSEVEVENT_ENTRY(instIdx, ServiceId);

  /* Check that the event shall be reported */
  /* This is the look-up table comparing the SID and NRC and the configured SEV events */
  SecurityEventId = Dcm_SEVReportingServices_IdsMSetSecurityEvent_CheckSEV(instIdx, ServiceId);

  /* When SEV is to be reported format the context data and send the event to IdsM */
  /* Deviation TASKING-1 */
  if (SecurityEventId != DCM_SEV_INVALID_SEV_REF)
  {
    /* Format Context Data in context data buffer and send to IdsM */
    ContextData[0U] = TesterType;
    ContextData[1U] = (uint8)(TesterID & 0x00FFU);
    ContextData[2U] = (uint8)((TesterID & 0xFF00U)>> 8U);
    ContextData[3U] = ServiceId;
    ContextData[4U] = (ServiceId | DCM_SEV_POSITIVERESPONSEBIT);

    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.DcmEnableSecurityEventReporting,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.DcmEnableSecurityEventReporting.SEVEvents,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.AuthenticationSuccessful.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.DTCSettingSwitchedOff.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.DiagnosticDataIdentifierWritten.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.CommunicationControlSwitchedOff.EnableRxAndDisableTx.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.CommunicationControlSwitchedOff.DisableRxAndEnableTx.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.CommunicationControlSwitchedOff.DisableRxAndTx.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.CommunicationControlSwitchedOff.EnableRxAndDisableTxWithEnhancedAddressInformation.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.SecurityAccessEcuUnlockSuccessful.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.EcuReset.PositiveResponse.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.ClearDtcSuccessful.SetSecurityEventWithContextData.Call,1 */
    /* !LINKSTO Dcm.EB.IntrusionDetectionSystem.SEVReportingForDiagnostic.DataDownloadSequenceSuccessful.SetSecurityEventWithContextData.Call,1 */
    IdsM_SetSecurityEventWithContextData (
                                SecurityEventId,
                                ContextData,
                                ContextDataSize);
  }
  else
  {
  /* Implicit else do not report a security event */
  }

  DBG_DCM_SEVREPORTINGSERVICES_REPORTSEVEVENT_EXIT(instIdx, ServiceId);

}

#if (DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED != DCM_SEV_INVALID_SEV_REF)
#if (DCM_NUM_CONFIGURED_SECURITY_LEVELS > 0U)
#if (DCM_DSP_SECURITYACCESS_DELAY_TIMERS_ENABLED == STD_ON)
/* !LINKSTO Dcm.Dsn.IB.SEVReportingServices.ReportSEVEventWithAttemptCounter,1 */
FUNC(void, DCM_CODE) Dcm_SEVReportingServices_IdsMSetSecurityEvent_AttemptCounter(
  uint8  AttemptCounter
)
{

  DBG_DCM_SEVREPORTINGSERVICES_REPORTSEVEVENTWITHATTEMPTCOUNTER_ENTRY(AttemptCounter);

  /* Save Dcm_SecurityAttemptCounter for use in next call to
     Dcm_SEVReportingServices_IdsMSetSecurityEvent_NRC when
     SecurityEventId is DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED */
  Dcm_SecurityAttemptCounter = AttemptCounter;

  DBG_DCM_SEVREPORTINGSERVICES_REPORTSEVEVENTWITHATTEMPTCOUNTER_EXIT(AttemptCounter);

}
#endif /* #if (DCM_DSP_SECURITYACCESS_DELAY_TIMERS_ENABLED == STD_ON) */
#endif /* #if (DCM_NUM_CONFIGURED_SECURITY_LEVELS > 0U) */
#endif /* #if (DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED != DCM_SEV_INVALID_SEV_REF) */

#if ((DCM_AUTHENTICATION_CONNECTION == STD_ON) && (DIAG_SEV_CERTIFICATE_FAILURE != DCM_SEV_INVALID_SEV_REF))
/* !LINKSTO Dcm.Dsn.IB.SEVReportingServices.ReportSEVEventWithCertificateFailure,1 */
FUNC(void, DCM_CODE) Dcm_SEVReportingServices_IdsMSetSecurityEvent_CertificateFailure_NRC(
  Dcm_NegativeResponseCodeType  ErrorCode
)
{
    /* Set Flag to indicate ErrorCode from Certificate Failure NRC.
       This flag is used to identify Certificate Failure events when
       the NRC is DCM_E_GENERALREJECT */
    if (ErrorCode == DCM_E_GENERALREJECT)
    {
      Dcm_AuthenticationCertificateFailureGeneralRejectNRC = TRUE;
    }
}
#endif /* #if ((DCM_AUTHENTICATION_CONNECTION == STD_ON) && (DIAG_SEV_CERTIFICATE_FAILURE != DCM_SEV_INVALID_SEV_REF)) */

#if ((DIAG_SEV_WRITE_INV_DATA != DCM_SEV_INVALID_SEV_REF) || (DIAG_SEV_DID_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF))
#if (DCM_DSP_USE_SERVICE_0X2E == STD_ON)
/* !LINKSTO Dcm.Dsn.IB.SEVReportingServices.ReportSEVEventWithWriteDidNotSupported,1 */
FUNC(void, DCM_CODE) Dcm_SEVReportingServices_IdsMSetSecurityEvent_WriteDidNotSupported_NRC(
  Dcm_NegativeResponseCodeType  ErrorCode
)
{
  /* This is the case when WriteDataByIdentifer reject a request with NRC DCM_E_REQUESTOUTOFRANGE
     because the DID is not supported (not configured, not enabled, write access not allowed) */
  DCM_PRECONDITION_ASSERT(ErrorCode == DCM_E_REQUESTOUTOFRANGE, DCM_INTERNAL_API_ID);

  Dcm_WriteDidROORDidNotSupported = TRUE;

}
#endif /* (DCM_DSP_USE_SERVICE_0X2E == STD_ON) */
#endif /* #if ((DIAG_SEV_WRITE_INV_DATA != DCM_SEV_INVALID_SEV_REF) || (DIAG_SEV_DID_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF)) */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*==================[internal function definitions]==============================================*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

STATIC FUNC(IdsM_SecurityEventIdType, DCM_CODE) Dcm_SEVReportingServices_IdsMSetSecurityEvent_NRC_CheckSEV(
  uint8                         ServiceId,
  Dcm_NegativeResponseCodeType  ErrorCode,
  P2VAR(uint8, AUTOMATIC, DCM_VAR)  OutputType
)
{
  IdsM_SecurityEventIdType  SecurityEventId = DCM_SEV_INVALID_SEV_REF;

#if (DCM_NRCCHECKSEV_SIDNOTUSED || !(DCM_SEV_NRCCHECKSEV_ATLEASTONECASE))
  TS_PARAM_UNUSED(ServiceId);
#endif
#if (DCM_NRCCHECKSEV_OUTPUTTYPENOTUSED || !(DCM_SEV_NRCCHECKSEV_ATLEASTONECASE))
  TS_PARAM_UNUSED(OutputType);
#endif
#if (!(DCM_SEV_NRCCHECKSEV_ATLEASTONECASE))
  TS_PARAM_UNUSED(ErrorCode);
#endif

/* Developer Note - if you add a case to this switch statement, please also update DCM_SEV_NRCCHECKSEV_ATLEASTONECASE */
#if (DCM_SEV_NRCCHECKSEV_ATLEASTONECASE)
  /* Check Service ID and Error Code */
  switch (ErrorCode)
  {
#if ((DCM_AUTHENTICATION_CONNECTION == STD_ON) && (DIAG_SEV_CERTIFICATE_FAILURE != DCM_SEV_INVALID_SEV_REF))
    /* NRC DCM_E_GENERALREJECT* 0x10 */
    case DCM_E_GENERALREJECT:
    {
      if ((ServiceId == DCM_SID_AUTHENTICATION) &&
          (Dcm_AuthenticationCertificateFailureGeneralRejectNRC != FALSE))
      {
         SecurityEventId = DIAG_SEV_CERTIFICATE_FAILURE;
         /* Reset Information for Certificate Failed */
         Dcm_AuthenticationCertificateFailureGeneralRejectNRC = FALSE;
      }
      break;
    }
#endif /* #if ((DCM_AUTHENTICATION_CONNECTION == STD_ON) && (DIAG_SEV_CERTIFICATE_FAILURE != DCM_SEV_INVALID_SEV_REF)) */
#if (DIAG_SEV_SERVICE_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF)
    /* NRC DCM_E_SERVICENOTSUPPORTED 0x11 or DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION 0x7F */
    case DCM_E_SERVICENOTSUPPORTED:
    case DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION:
    {
      SecurityEventId = DIAG_SEV_SERVICE_NOT_SUPPORTED;
      break;
    }
#endif /*(DIAG_SEV_SERVICE_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF) */

#if (DIAG_SEV_SUBFUNCTION_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF)
    /* NRC DCM_E_SUBFUNCTIONNOTSUPPORTED 0x12 */
    case DCM_E_SUBFUNCTIONNOTSUPPORTED:
    {
      SecurityEventId = DIAG_SEV_SUBFUNCTION_NOT_SUPPORTED;
      break;
    }
#endif /*(DIAG_SEV_SUBFUNCTION_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF) */

#if (DIAG_SEV_INCORRECT_MESSAGE_LENGTH_OR_FORMAT != DCM_SEV_INVALID_SEV_REF)
    /* NRC DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT 0x13 */
    case DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT:
    {
      SecurityEventId = DIAG_SEV_INCORRECT_MESSAGE_LENGTH_OR_FORMAT;
      break;
    }
#endif /*(DIAG_SEV_INCORRECT_MESSAGE_LENGTH_OR_FORMAT != DCM_SEV_INVALID_SEV_REF) */

#if (DIAG_SEV_ECU_RESET != DCM_SEV_INVALID_SEV_REF)
    /* NRC DCM_E_CONDITIONSNOTCORRECT 0x22, SID 0x11 */
    case DCM_E_CONDITIONSNOTCORRECT:
    {
      if (ServiceId == DCM_SID_ECU_RESET)
      {
        SecurityEventId = DIAG_SEV_ECU_RESET;
      }
      break;
    }
#endif /*(DIAG_SEV_ECU_RESET != DCM_SEV_INVALID_SEV_REF) */

#if (DIAG_SEV_REQUEST_SEQUENCE_ERROR != DCM_SEV_INVALID_SEV_REF)
    /* NRC DCM_E_REQUESTSEQUENCEERROR 0x24 */
    case DCM_E_REQUESTSEQUENCEERROR:
    {
      SecurityEventId = DIAG_SEV_REQUEST_SEQUENCE_ERROR;
      break;
    }
#endif /*(DIAG_SEV_REQUEST_SEQUENCE_ERROR != DCM_SEV_INVALID_SEV_REF) */

#if ((DIAG_SEV_REQUEST_OUT_OF_RANGE != DCM_SEV_INVALID_SEV_REF) || \
     (DIAG_SEV_DID_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF) || \
     (DIAG_SEV_RID_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF) || \
     (DIAG_SEV_WRITE_INV_DATA != DCM_SEV_INVALID_SEV_REF) )
    /* NRC DCM_E_REQUESTOUTOFRANGE 0x31 */
    case DCM_E_REQUESTOUTOFRANGE:
    {
#if ((DIAG_SEV_WRITE_INV_DATA != DCM_SEV_INVALID_SEV_REF) && (DCM_DSP_USE_SERVICE_0X2E == STD_ON) )
      if ((ServiceId == DCM_SID_WRITEDATABYID) &&
          (Dcm_WriteDidROORDidNotSupported != TRUE))
      {
        SecurityEventId = DIAG_SEV_WRITE_INV_DATA;
        break;
      }
#endif /*(DIAG_SEV_WRITE_INV_DATA != DCM_SEV_INVALID_SEV_REF) */
#if (DIAG_SEV_DID_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF)
      if (TRUE == DCM_IS_DIDRELATED_SID(ServiceId) && (ServiceId != DCM_SID_WRITEDATABYID))
      {
        SecurityEventId = DIAG_SEV_DID_NOT_SUPPORTED;
        *OutputType = DCM_SEV_CONTEXT_DATA_SIZE_SEVEN_BYTES;
        break;
      }
#if (DCM_DSP_USE_SERVICE_0X2E == STD_ON)
      if ((ServiceId == DCM_SID_WRITEDATABYID) &&
          (Dcm_WriteDidROORDidNotSupported == TRUE))
      {
        SecurityEventId = DIAG_SEV_DID_NOT_SUPPORTED;
        *OutputType = DCM_SEV_CONTEXT_DATA_SIZE_SEVEN_BYTES;
        /* Reset Information for WriteDataByIdentifer due to DID not supported */
        Dcm_WriteDidROORDidNotSupported = FALSE;
        break;
      }
#endif /* #if (DCM_DSP_USE_SERVICE_0X2E == STD_ON) */
#endif /*(DIAG_SEV_DID_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF) */
#if (DIAG_SEV_RID_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF)
      if (ServiceId == DCM_SID_ROUTINE_CONTROL)
      {
        SecurityEventId = DIAG_SEV_RID_NOT_SUPPORTED;
        *OutputType = DCM_SEV_CONTEXT_DATA_SIZE_SEVEN_BYTES;
        break;
      }
#endif /*(DIAG_SEV_RID_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF) */
#if (DIAG_SEV_REQUEST_OUT_OF_RANGE != DCM_SEV_INVALID_SEV_REF)
      SecurityEventId = DIAG_SEV_REQUEST_OUT_OF_RANGE;
#endif /*(DIAG_SEV_REQUEST_OUT_OF_RANGE != DCM_SEV_INVALID_SEV_REF) */

      break;
    }
#endif /*((DIAG_SEV_SERVICE_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF) || \
          (DIAG_SEV_DID_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF) || \
          (DIAG_SEV_RID_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF)  \
          (DIAG_SEV_WRITE_INV_DATA != DCM_SEV_INVALID_SEV_REF) ) */

#if (DIAG_SEV_SECURITY_ACCESS_DENIED != DCM_SEV_INVALID_SEV_REF)
    /* NRC DCM_E_SECURITYACCESSDENIED 0x33 */
    case DCM_E_SECURITYACCESSDENIED:
    {
      SecurityEventId = DIAG_SEV_SECURITY_ACCESS_DENIED;
      break;
    }
#endif /*(DIAG_SEV_SECURITY_ACCESS_DENIED != DCM_SEV_INVALID_SEV_REF) */

#if (DIAG_SEV_REQUESTED_ACTIONS_REQUIRES_AUTHENTICATION != DCM_SEV_INVALID_SEV_REF)
    /* NRC DCM_E_AUTHENTICATIONREQUIRED 0x34 */
    case DCM_E_AUTHENTICATIONREQUIRED:
    {
      SecurityEventId = DIAG_SEV_REQUESTED_ACTIONS_REQUIRES_AUTHENTICATION;
      break;
    }
#endif /*(DIAG_SEV_REQUESTED_ACTIONS_REQUIRES_AUTHENTICATION != DCM_SEV_INVALID_SEV_REF) */

#if (DIAG_SEV_SECURITY_ACCESS_INVALID_KEY != DCM_SEV_INVALID_SEV_REF)
    /* NRC DCM_E_INVALIDKEY 0x35 SID 0x27 */
    case DCM_E_INVALIDKEY:
    {
      /* NRC 0x35 should always be due to service 0x27 */
      DCM_PRECONDITION_ASSERT((ServiceId == DCM_SID_SECURITYACCESS), DCM_INTERNAL_API_ID);

      SecurityEventId = DIAG_SEV_SECURITY_ACCESS_INVALID_KEY;
      break;
    }
#endif /*(DIAG_SEV_SECURITY_ACCESS_INVALID_KEY != DCM_SEV_INVALID_SEV_REF) */

#if (DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED != DCM_SEV_INVALID_SEV_REF)
#if (DCM_NUM_CONFIGURED_SECURITY_LEVELS > 0U)
#if (DCM_DSP_SECURITYACCESS_DELAY_TIMERS_ENABLED == STD_ON)
    /* NRC DCM_E_EXCEEDNUMBEROFATTEMPTS 0x36 SID 0x27 */
    case DCM_E_EXCEEDNUMBEROFATTEMPTS:
    {
      /* NRC 0x35 should always be due to service 0x27 */
      DCM_PRECONDITION_ASSERT((ServiceId == DCM_SID_SECURITYACCESS), DCM_INTERNAL_API_ID);

      SecurityEventId = DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED;
      *OutputType = DCM_SEV_CONTEXT_DATA_SIZE_SIX_BYTES;
      break;
    }
#endif /* #if (DCM_DSP_SECURITYACCESS_DELAY_TIMERS_ENABLED == STD_ON) */
#endif /* #if (DCM_NUM_CONFIGURED_SECURITY_LEVELS > 0U) */
#endif /*(DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED != DCM_SEV_INVALID_SEV_REF) */

#if (DIAG_SEV_SECURITY_ACCESS_REQUIRED_TIME_DELAY_NOT_EXPIRED != DCM_SEV_INVALID_SEV_REF)
    /* NRC DCM_E_REQUIREDTIMEDELAYNOTEXPIRED 0x37 */
    case DCM_E_REQUIREDTIMEDELAYNOTEXPIRED:
    {
      SecurityEventId = DIAG_SEV_SECURITY_ACCESS_REQUIRED_TIME_DELAY_NOT_EXPIRED;
      break;
    }
#endif /*(DIAG_SEV_SECURITY_ACCESS_REQUIRED_TIME_DELAY_NOT_EXPIRED != DCM_SEV_INVALID_SEV_REF) */

#if ((DCM_AUTHENTICATION_CONNECTION == STD_ON) && (DIAG_SEV_CERTIFICATE_FAILURE != DCM_SEV_INVALID_SEV_REF))
    /* NRC DCM_E_CERTIFICATEVERIFICATIONFAILED* 0x50- 0x57 */
    case DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDTIMEPERIOD:
    case DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDSIGNATURE:
    case DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDCHAINOFTRUST:
    case DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDTYPE:
    case DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDFORMAT:
    case DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDCONTENT:
    case DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDSCOPE:
    case DCM_E_CERTIFICATEVERIFICATIONFAILEDREVOKED:
    {
      SecurityEventId = DIAG_SEV_CERTIFICATE_FAILURE;
      /* Reset Information for Certificate Failed */
      Dcm_AuthenticationCertificateFailureGeneralRejectNRC = FALSE;
      break;
    }
#endif /* #if ((DCM_AUTHENTICATION_CONNECTION == STD_ON) && (DIAG_SEV_CERTIFICATE_FAILURE != DCM_SEV_INVALID_SEV_REF)) */

#if (DIAG_SEV_WRITE_INV_DATA != DCM_SEV_INVALID_SEV_REF)
    /* NRC DCM_E_GENERALPROGRAMMINGFAILURE 0x72 SID 0x2E */
    case DCM_E_GENERALPROGRAMMINGFAILURE:
    {
      if (ServiceId == DCM_SID_WRITEDATABYID)
      {
        SecurityEventId = DIAG_SEV_WRITE_INV_DATA;
      }
      break;
    }
#endif /*(DIAG_SEV_WRITE_INV_DATA != DCM_SEV_INVALID_SEV_REF) */
    default :
      /* No security event found */
      SecurityEventId = DCM_SEV_INVALID_SEV_REF;
      break;
  }
#endif /* #if (DCM_SEV_NRCCHECKSEV_ATLEASTONECASE) */

  return SecurityEventId;
}

STATIC FUNC(IdsM_SecurityEventIdType, DCM_CODE) Dcm_SEVReportingServices_IdsMSetSecurityEvent_CheckSEV(
  uint8                         instIdx,
  uint8                         ServiceId
)
{
  IdsM_SecurityEventIdType  SecurityEventId = DCM_SEV_INVALID_SEV_REF;

#if ((DIAG_SEV_COMMUNICATION_CONTROL_SWITCHED_OFF == DCM_SEV_INVALID_SEV_REF) && \
     (DIAG_SEV_ECU_UNLOCK_SUCCESSFUL == DCM_SEV_INVALID_SEV_REF) && \
     (DIAG_SEV_DTC_SETTING_SWITCHED_OFF == DCM_SEV_INVALID_SEV_REF) || \
     !(DCM_SEV_CHECKSEV_ATLEASTONECASE))
  TS_PARAM_UNUSED(instIdx);
#else
  uint8 SubServiceId;
#endif /*((DIAG_SEV_COMMUNICATION_CONTROL_SWITCHED_OFF != DCM_SEV_INVALID_SEV_REF) && \
          (DIAG_SEV_ECU_UNLOCK_SUCCESSFUL == DCM_SEV_INVALID_SEV_REF) && \
          (DIAG_SEV_DTC_SETTING_SWITCHED_OFF != DCM_SEV_INVALID_SEV_REF) || \
          !(DCM_SEV_CHECKSEV_ATLEASTONECASE)) */
#if (!(DCM_SEV_CHECKSEV_ATLEASTONECASE))
  TS_PARAM_UNUSED(ServiceId);
#endif /* #if (!(DCM_SEV_CHECKSEV_ATLEASTONECASE)) */

/* Developer Note - if you add a case to this switch statement, please also update DCM_SEV_CHECKSEV_ATLEASTONECASE */
#if (DCM_SEV_CHECKSEV_ATLEASTONECASE)
  /* Check Service ID*/
  switch (ServiceId)
  {
#if (DIAG_SEV_ECU_RESET != DCM_SEV_INVALID_SEV_REF)
     /* Service ID DCM_SID_ECU_RESET 0x11 */
     case DCM_SID_ECU_RESET:
     {
       SecurityEventId = DIAG_SEV_ECU_RESET;
       break;
     }
#endif /*(DIAG_SEV_ECU_RESET != DCM_SEV_INVALID_SEV_REF) */

#if (DIAG_SEV_CLEAR_DTC_SUCCESSFUL != DCM_SEV_INVALID_SEV_REF)
     /* Service ID DCM_SID_CLR_DIAG_INFORMATION 0x14 */
     case DCM_SID_CLR_DIAG_INFORMATION:
     {
       SecurityEventId = DIAG_SEV_CLEAR_DTC_SUCCESSFUL;
       break;
     }
#endif /*(DIAG_SEV_CLEAR_DTC_SUCCESSFUL != DCM_SEV_INVALID_SEV_REF) */

#if (DIAG_SEV_ECU_UNLOCK_SUCCESSFUL != DCM_SEV_INVALID_SEV_REF)
     /* Service ID DCM_SID_SECURITYACCESS 0x27, SSID sendKey */
     case DCM_SID_SECURITYACCESS:
     {
       /* Check of SSID */
       SubServiceId = Dcm_Dsp_GetSubServiceID(instIdx);

       /* The event is reported for subservice sendKey.
          Any even numbered subfunction from 0x02 to 0x7E
          represents the sendKey subfunction.
          Check subservice is an even number. */
       if ((SubServiceId & 1U) == 0U)
       {
         SecurityEventId = DIAG_SEV_ECU_UNLOCK_SUCCESSFUL;
       }
       break;
     }
#endif /*(DIAG_SEV_ECU_UNLOCK_SUCCESSFUL != DCM_SEV_INVALID_SEV_REF) */

#if (DIAG_SEV_COMMUNICATION_CONTROL_SWITCHED_OFF != DCM_SEV_INVALID_SEV_REF)
     /* Service ID DCM_SID_COMMUNICATIONCONTROL 0x28 , SSID 0x01, 0x02, 0x03, 0x04 */
     case DCM_SID_COMMUNICATIONCONTROL:
     {
       /* Check of SSID 0x01, 0x02, 0x03, 0x04 */
       SubServiceId = Dcm_Dsp_GetSubServiceID(instIdx);

       if ((SubServiceId == DCM_SSID_COMMUNICATIONCONTROL_ENABLERXANDDISABLETX) ||
           (SubServiceId == DCM_SSID_COMMUNICATIONCONTROL_DISABLERXANDENABLETX) ||
           (SubServiceId == DCM_SSID_COMMUNICATIONCONTROL_DISABLERXANDTX) ||
           (SubServiceId == DCM_SSID_COMMUNICATIONCONTROL_ENABLERXANDDISABLETXWITHENHANCEDADDRESSINFORMATION))
       {
         SecurityEventId = DIAG_SEV_COMMUNICATION_CONTROL_SWITCHED_OFF;
       }
       break;
     }
#endif /*(DIAG_SEV_COMMUNICATION_CONTROL_SWITCHED_OFF != DCM_SEV_INVALID_SEV_REF) */

#if (DIAG_SEV_AUTHENTICATION_SUCCESSFUL != DCM_SEV_INVALID_SEV_REF)
#if ((DCM_DSP_USE_SERVICE_0X29 == STD_ON) || (DCM_AUTHENTICATION_CONNECTION == STD_ON))
     /* Service ID DCM_SID_AUTHENTICATION 0x29 */
     case DCM_SID_AUTHENTICATION:
     {
       SecurityEventId = DIAG_SEV_AUTHENTICATION_SUCCESSFUL;
       break;
     }
#endif /* ((DCM_DSP_USE_SERVICE_0X29 == STD_ON) || (DCM_AUTHENTICATION_CONNECTION == STD_ON)) */
#endif /*(DIAG_SEV_AUTHENTICATION_SUCCESSFUL != DCM_SEV_INVALID_SEV_REF) */

#if (DIAG_SEV_WRITE_DATA != DCM_SEV_INVALID_SEV_REF)
     /* Service ID DCM_SID_WRITEDATABYID 0x2E */
     case DCM_SID_WRITEDATABYID:
     {
       SecurityEventId = DIAG_SEV_WRITE_DATA;
       break;
     }
#endif /*(DIAG_SEV_WRITE_DATA != DCM_SEV_INVALID_SEV_REF) */

#if (DIAG_SEV_REQUEST_DOWNLOAD != DCM_SEV_INVALID_SEV_REF)
     /* Service ID DCM_SID_REQUEST_DOWNLOAD 0x34 */
     case DCM_SID_REQUEST_DOWNLOAD:
     {
       SecurityEventId = DIAG_SEV_REQUEST_DOWNLOAD;
       break;
     }
#endif /*(DIAG_SEV_REQUEST_DOWNLOAD != DCM_SEV_INVALID_SEV_REF) */

#if (DIAG_SEV_DTC_SETTING_SWITCHED_OFF != DCM_SEV_INVALID_SEV_REF)
     /* Service ID DCM_SID_CONTROLDTCSETTING 0x85 */
     case DCM_SID_CONTROLDTCSETTING:
     {
       /* Check of SSID DCM_SSID_CONTROLDTCSETTING_OFF 0x02 */
       SubServiceId = Dcm_Dsp_GetSubServiceID(instIdx);

       if (SubServiceId == DCM_SSID_CONTROLDTCSETTING_OFF)
       {
         SecurityEventId = DIAG_SEV_DTC_SETTING_SWITCHED_OFF;
       }
       break;
     }
#endif /*(DIAG_SEV_DTC_SETTING_SWITCHED_OFF != DCM_SEV_INVALID_SEV_REF) */

    default :
      /* No security event found */
      SecurityEventId = DCM_SEV_INVALID_SEV_REF;
      break;
  }
#endif /* #if (DCM_SEV_CHECKSEV_ATLEASTONECASE) */

  return SecurityEventId;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>


#endif /* #if (DCM_SECURITY_EVENT_REPORTING == STD_ON) */

/*==================[end of file]================================================================*/
