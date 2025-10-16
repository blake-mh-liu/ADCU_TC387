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

/* !LINKSTO Dcm.Dsn.File.SEVReportingServices.PublicApi,1 */
/* This file contains the public API of the SEV Reporting Services SW unit. */

#if (!defined DCM_SEVREPORTINGSERVICES_H)
#define DCM_SEVREPORTINGSERVICES_H

/*==================[inclusions]==================================================================*/

#include <Std_Types.h>                                   /* AUTOSAR standard types */
#include <Dcm_Types.h>
#include <Dcm_SecurityAccess_Cfg.h>

#if (DCM_SECURITY_EVENT_REPORTING == STD_ON)

/*==================[macro definitions]===========================================================*/

/*==================[type declarations]===========================================================*/

/*==================[external constant declarations]==============================================*/

/*==================[external data declarations]==================================================*/

/*==================[external function declarations]==============================================*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/** \brief Report security event with NRC
 **
 ** This function initialises the SEV Reporting Event unit.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, DCM_CODE) Dcm_SEVReportingServices_Init(void);


/** \brief Report security event with NRC
 **
 ** This function informs the SEV Reporting Event unit that an event with an error code has occurred.
 **
 ** \param[in]    instIdx       HSM instance index
 ** \param[in]    ServiceId     Service ID reporting the SEV event
 ** \param[in]    ErrorCode     NRC error code to be reported with event
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, DCM_CODE) Dcm_SEVReportingServices_IdsMSetSecurityEvent_NRC(
  uint8                         instIdx,
  uint8                         ServiceId,
  Dcm_NegativeResponseCodeType  ErrorCode
);

/** \brief Report security event with no extra data
 **
 ** This function informs the SEV Reporting Event unit that an event has occurred.
 **
 ** \param[in]    instIdx       HSM instance index
 ** \param[in]    ServiceId     Service ID reporting the SEV event
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, DCM_CODE) Dcm_SEVReportingServices_IdsMSetSecurityEvent(
  uint8                         instIdx,
  uint8                         ServiceId
);

#if (DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED != DCM_SEV_INVALID_SEV_REF)
#if (DCM_NUM_CONFIGURED_SECURITY_LEVELS > 0U)
#if (DCM_DSP_SECURITYACCESS_DELAY_TIMERS_ENABLED == STD_ON)
/** \brief Report security event with attempt counter
 **
 ** This function informs the SEV Reporting Event unit that an event with an attempt counter has occurred.
 **
 ** \param[in]    AttemptCounter    Attempt counter keeping track how many consecutive
                                    failed attempts were made to access the current
                                    security level to be reported with event
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, DCM_CODE) Dcm_SEVReportingServices_IdsMSetSecurityEvent_AttemptCounter(
  uint8                         AttemptCounter
);
#endif /* #if (DCM_DSP_SECURITYACCESS_DELAY_TIMERS_ENABLED == STD_ON) */
#endif /* #if (DCM_NUM_CONFIGURED_SECURITY_LEVELS > 0U) */
#endif /* #if (DIAG_SEV_SECURITY_ACCESS_NUMBER_OF_ATTEMPTS_EXCEEDED != DCM_SEV_INVALID_SEV_REF) */

#if ((DCM_AUTHENTICATION_CONNECTION == STD_ON) && (DIAG_SEV_CERTIFICATE_FAILURE != DCM_SEV_INVALID_SEV_REF))
/** \brief Report security event with NRC for Authentication Certificate Failure
 **
 ** This function informs the SEV Reporting Event unit that an event with an error code has occurred.
 **
 ** \param[in]    ErrorCode     NRC error code to be reported with event
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, DCM_CODE) Dcm_SEVReportingServices_IdsMSetSecurityEvent_CertificateFailure_NRC(
  Dcm_NegativeResponseCodeType  ErrorCode
);
#endif /* #if ((DCM_AUTHENTICATION_CONNECTION == STD_ON) && (DIAG_SEV_CERTIFICATE_FAILURE != DCM_SEV_INVALID_SEV_REF)) */

#if ((DIAG_SEV_WRITE_INV_DATA != DCM_SEV_INVALID_SEV_REF) || (DIAG_SEV_DID_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF))
#if (DCM_DSP_USE_SERVICE_0X2E == STD_ON)
/** \brief Report security event with NRC for WriteIdentifierById DID Not Supported
 **
 ** This function informs the SEV Reporting Event unit that an event with an error code has occurred.
 **
 ** \param[in]    ErrorCode     NRC error code to be reported with event
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, DCM_CODE) Dcm_SEVReportingServices_IdsMSetSecurityEvent_WriteDidNotSupported_NRC(
  Dcm_NegativeResponseCodeType  ErrorCode
);
#endif /* (DCM_DSP_USE_SERVICE_0X2E == STD_ON) */
#endif /* #if ((DIAG_SEV_WRITE_INV_DATA != DCM_SEV_INVALID_SEV_REF) || (DIAG_SEV_DID_NOT_SUPPORTED != DCM_SEV_INVALID_SEV_REF)) */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif /* #if (DCM_SECURITY_EVENT_REPORTING == STD_ON) */

#endif /* if !defined(DCM_SEVREPORTINGSERVICES_H) */
/*==================[end of file]=================================================================*/
