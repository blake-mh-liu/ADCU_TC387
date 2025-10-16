/**
 * \file
 *
 * \brief AUTOSAR Crypto
 *
 * This file contains the implementation of the AUTOSAR
 * module Crypto.
 *
 * \version 2.0.39
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_H
#define CRYPTO_XVIX_XAIX_H

/*==================[deviations]==================================================================*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 8.5 (Required)
 * An external object or function shall be declared once in one and only one file.
 *
 * Reason:
 * AUTOSAR declares Crypto_xVIx_xAIx_MainFunction also in SchM_Crypto_xVIx_xAIx.h
 *
 */

/*==================[includes]====================================================================*/

/* !LINKSTO Crypto.Asr.SWS_Crypto_00042_43x,1 */
/* !LINKSTO Crypto.Asr.SWS_Crypto_00043,1 */

#include <Csm_Types.h>                      /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx.h/0002,1 */

#include <Crypto_xVIx_xAIx_Version.h>       /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx.h/0004,1 */
#include <Crypto_xVIx_xAIx_Types.h>         /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx.h/0005,1 */
#include <Crypto_xVIx_xAIx_Cfg.h>           /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx.h/0003,1 */
#include <Crypto_xVIx_xAIx_KeyManagement.h> /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx.h/0006,1 */

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  Init function of the Crypto Driver.
 **
 ** This function initializes the AUTOSAR layer and forwards the initialization request to the
 ** process layer.
 **
 ** \ServiceID{::CRYPTO_XVIX_XAIX_SID_INIT}
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous}
 **/
#ifndef RTE_SCHM_SWCBSW_CRYPTO_XVIX_XAIX_INIT
#define RTE_SCHM_SWCBSW_CRYPTO_XVIX_XAIX_INIT
extern FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Init
(
  void
);
#endif /* #ifndef RTE_SCHM_SWCBSW_CRYPTO_XVIX_XAIX_INIT */

/** \brief  Retrieves version info for the crypto driver module.
 **
 ** This function copies the version information to the passed VersionInfo struct.
 **
 ** \param[out]  versioninfo  Pointer to the VersionInfo structure that shall be filled with data.
 **
 ** \ServiceID{::CRYPTO_XVIX_XAIX_SID_GETVERSIONINFO}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_VERSIONINFO == STD_ON)
extern FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetVersionInfo
(
  P2VAR(Std_VersionInfoType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) versioninfo
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_VERSIONINFO == STD_ON) */

/** \brief  Process function of the crypto driver.
 **
 ** This function accepts the process requests. It checks the parameters for correctness and
 ** dispatches according to service, algorithm family and algorithm mode of the requested job.
 ** If the requested driver object is idle and if it supports the requested primitive the job is
 ** accepted and processed.
 ** If the driver object is busy, the function indicates an error.
 **
 ** \param[in]  objectId  Identifier of the crypto driver object that shall process the job.
 ** \param[in]  job       Reference to the job that shall be processed.
 **
 ** \returns  Result of the job processing.
 **
 ** \retval  E_OK                         Job has been accepted and was sucessfully processed
 **                                       (synchronous job) or processing was successfully started
 **                                       (asynchronous job).
 ** \retval  E_NOT_OK                     Job could not be processed.
 ** \retval  CRYPTO_E_BUSY                Request failed, the crypto driver object is busy.
 ** \retval  CRYPTO_E_KEY_NOT_VALID       Request failed, the key to be used is not valid.
 ** \retval  CRYPTO_E_KEY_SIZE_MISMATCH   Request failed, a key element has the wrong size.
 ** \retval  CRYPTO_E_QUEUE_FULL          (not supported)
 ** \retval  CRYPTO_E_ENTROPY_EXHAUSTION  Request failed, the entropy is exhausted.
 ** \retval  CRYPTO_E_SMALL_BUFFER        Request failed, the provided buffer is too small to store
 **                                       the result.
 ** \retval  CRYPTO_E_JOB_CANCELED        Request failed, the synchronous job was canceled.
 **
 ** \ServiceID{::CRYPTO_XVIX_XAIX_SID_PROCESSJOB}
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ProcessJob
(
        uint32                                                 objectId,
  P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job
);

/** \brief  Cancel function of the crypto driver.
 **
 ** This function is used to cancel a requested job.
 **
 ** \param[in]  objectId  Identifier of the crypto driver object that processes the job.
 ** \param[in]  job       Reference to the job that shall be cancelled.
 **
 ** \returns  Result of the job cancellation attempt.
 **
 ** \retval  E_OK               Job was successfully canceled.
 ** \retval  E_NOT_OK           Job could not be cancelled.
 ** \retval  CRYPTO_E_CANCELED  Job has been canceled successfully.
 **
 ** \ServiceID{::CRYPTO_XVIX_XAIX_SID_CANCELJOB}
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CancelJob
(
        uint32                                            objectId,
#if (    (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) \
      || (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_431) \
    )
    P2VAR(Crypto_JobInfoType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job
#else /* #if (   (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) ... */
    P2VAR(Crypto_JobType,     AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job
#endif /* #if (   (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) ... */
);

/** \brief  Cyclic main function of the crypto driver.
 **
 ** This function calls the main functions of the configured primitives for each crypto driver
 ** object.
 **
 ** \ServiceID{::CRYPTO_XVIX_XAIX_SID_MAINFUNCTION}
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_CRYPTO_MAIN_FUNCTION_EXISTS == STD_ON)
#ifndef RTE_SCHM_SWCBSW_CRYPTO_XVIX_XAIX_MAINFUNCTION
#define RTE_SCHM_SWCBSW_CRYPTO_XVIX_XAIX_MAINFUNCTION
/* Deviation MISRAC2012-1 */
extern FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_MainFunction
(
  void
);
#endif /* #ifndef RTE_SCHM_SWCBSW_CRYPTO_XVIX_XAIX_MAINFUNCTION */
#endif /* #if (CRYPTO_XVIX_XAIX_CRYPTO_MAIN_FUNCTION_EXISTS == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_H */

/*==================[end of file]=================================================================*/

