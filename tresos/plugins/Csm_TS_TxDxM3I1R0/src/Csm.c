/**
 * \file
 *
 * \brief AUTOSAR Csm
 *
 * This file contains the implementation of the AUTOSAR
 * module Csm.
 *
 * \version 3.1.33
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/** \brief  Macro that specifies Csm source code.
 **/
#define CSM_SRC

/*==================[deviations]==================================================================*/

/*==================[misra deviations]============================================================*/

/*  MISRA-C:2012 Deviation List
 *
 *  MISRAC2012-1) Deviated Rule: 2.2 (required)
 *   There shall be no dead code.
 *
 *   Reason:
 *   The Csm SWS specifies unused API function parameters for interface compatibility reasons.
 *   That is why the TS_PARAM_UNUSED macro is used to prevent compiler warnings for unused
 *   variables.
 *
 *  MISRAC2012-2) Deviated Rule: 8.3 (required)
 *   All declarations of an object or function shall use the same names and type qualifiers.
 *
 *   Reason:
 *   Definition of RTE Interfaces and CSM interfaces does not match in the Autosar 4.4.0 specification.
 */

/*  Code-Metric Deviation List
 *
 *  CODEMETRIC-1) Deviated Rule: HIS_PARAM
 *   not 11 <= 8
 *
 *   Reason:
 *   The specification of Crypto Service Manager AUTOSAR CP Release 4.3.0 specifies API function
 *   Csm_AEADDecrypt (SWS_Csm_01026) with 11 parameters
 *
 *  CODEMETRIC-2) Deviated Rule: HIS_PARAM
 *   not 10 <= 8
 *
 *   Reason:
 *   The specification of Crypto Service Manager AUTOSAR CP Release 4.3.0 specifies API function
 *   Csm_AEADEncrypt (SWS_Csm_01023) with 10 parameters
 *
 *  CODEMETRIC-3) Deviated Rule: HIS_PARAM
 *   not 11 <= 8
 *
 *   Reason:
 *   This is a necessary wrapper function for the API function Csm_AEADDecrypt (SWS_Csm_01026) with
 *   11 parameters specified in Crypto Service Manager AUTOSAR CP Release 4.3.0
 *
 *  CODEMETRIC-4) Deviated Rule: HIS_PARAM
 *   not 10 <= 8
 *
 *   Reason:
 *   This is a necessary wrapper function for the API function Csm_AEADEncrypt (SWS_Csm_01023) with
 *   10 parameters specified in Crypto Service Manager AUTOSAR CP Release 4.3.0
 */

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W588
 * W588: dead assignment to "Csm_Initialized" eliminated
 *
 * Reason:
 * Usage of variable "Csm_Initialized" depends on preprocessor settings that are configuration
 * specific
 *
 * TASKING-2) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * The Csm specification demands that the number of configured jobs, CSM_JOB_COUNT, and the
 * number of configured queues, CSM_QUE_COUNT, are always bigger than zero.
 *
 * TASKING-3) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * In some cases checks which are never failing are necessary to fulfill certain autosar requirements.
 */

/*==================[includes]====================================================================*/

#include <CryIf.h>

#include <Csm.h>
#include <Csm_Int.h>

#include <SchM_Csm.h>

#include <TSAutosar.h>

/* !LINKSTO CSM.Req.Gen/Det/00001,1 */
#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
/* !LINKSTO SWS_Csm_00485,1 */
#include <Det.h>
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */

#if (CSM_RTE_ENABLED == STD_ON) && (CSM_PRT_COUNT == 0U)
#include <Rte_Csm.h>
#endif /* #if (CSM_RTE_ENABLED == STD_ON) && (CSM_PRT_COUNT == 0U) */

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[internal function declarations]==============================================*/

#define CSM_START_SEC_CODE
#include <Csm_MemMap.h>

/** \brief  Handle processing of queueing of asycronous job requests and forwarding of job requests
 **         to CryIf.
 **/
FUNC(Std_ReturnType, CSM_CODE) Csm_Process
(
  uint32 jobId,
  P2VAR(Crypto_JobPrimitiveInputOutputType, AUTOMATIC, CSM_APPL_DATA) jobPrimitiveInputOutput
);

#define CSM_STOP_SEC_CODE
#include <Csm_MemMap.h>

/*==================[internal constants]==========================================================*/

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

#define CSM_START_SEC_VAR_INIT_8
#include <Csm_MemMap.h>

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
/** \brief  Variable that represents whether the Csm module is fully initialized.
 **/
/* !LINKSTO CSM.Dsn.Api/Datas/00001,1 */
VAR(boolean, CSM_VAR) Csm_Initialized = FALSE;
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */

#define CSM_STOP_SEC_VAR_INIT_8
#include <Csm_MemMap.h>

/*==================[external function definitions]===============================================*/

#define CSM_START_SEC_CODE
#include <Csm_MemMap.h>

/* --- Csm_AEADDecrypt -------------------------------------------------------------------------- */

/* !LINKSTO CSM.Dsn.SWS_Csm_01026,1 */

#if (CSM_API_ENABLED_SERVICE_AEADDECRYPT == STD_ON)
/* Deviation CODEMETRIC-1 */
FUNC(Std_ReturnType, CSM_CODE) Csm_AEADDecrypt
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) ciphertextPtr,
          uint32                                              ciphertextLength,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) associatedDataPtr,
          uint32                                              associatedDataLength,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) tagPtr,
          uint32                                              tagLength,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) plaintextPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) plaintextLengthPtr,
    P2VAR(Crypto_VerifyResultType,  AUTOMATIC, CSM_APPL_DATA) verifyPtr
)
{
  Std_ReturnType                     result                  = E_NOT_OK;
  Crypto_JobPrimitiveInputOutputType jobPrimitiveInputOutput = {
                                                                 NULL_PTR, 0U,                    /* inputPtr,           inputLength              */
                                                                 NULL_PTR, 0U,                    /* secondaryInputPtr,  secondaryInputLength     */
                                                                 NULL_PTR, 0U,                    /* tertiaryInputPtr,   tertiaryInputLength      */
                                                                 NULL_PTR, NULL_PTR,              /* outputPtr,          outputLengthPtr          */
                                                                 NULL_PTR, NULL_PTR,              /* secondaryOutputPtr, secondaryOutputLengthPtr */
#if (   (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_440) \
    )
                                                                 0U,                              /* input64                                      */
#endif /* #if (   (CSM_API_VERSION == CSM_API_VERSION_431) ... */
                                                                 NULL_PTR,                        /* verifyPtr                                    */
#if (CSM_API_VERSION != CSM_API_VERSION_EB)
                                                                 NULL_PTR,                        /* output64Ptr                                  */
#endif /* #if (CSM_API_VERSION != CSM_API_VERSION_EB) */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL, /* mode                                         */
                                                                 0U,                              /* cryIfKeyId                                   */
                                                                 0U,                              /* targetCryIfKeyId                             */
#else /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL  /* mode                                         */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                               };

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_AEADDECRYPT,
                          CSM_E_UNINIT
                         );
  }
  else
  if (jobId >= CSM_JOB_COUNT)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00002,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_AEADDECRYPT,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (Csm_JobConfigurations[jobId].jobPrimitiveInfo->primitiveInfo->service != CRYPTO_AEADDECRYPT)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00003,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_AEADDECRYPT,
                          CSM_E_SERVICE_NOT_IDENTICAL
                         );
  }
  else
  if (ciphertextPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_AEADDECRYPT,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (associatedDataPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_AEADDECRYPT,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (tagPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_AEADDECRYPT,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (plaintextPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_AEADDECRYPT,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (plaintextLengthPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_AEADDECRYPT,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (verifyPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_AEADDECRYPT,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    if ( (  (mode & CRYPTO_OPERATIONMODE_SINGLECALL) ==
              (CRYPTO_OPERATIONMODE_START|CRYPTO_OPERATIONMODE_FINISH)
         ) ||
         ( ((mode & CRYPTO_OPERATIONMODE_SINGLECALL) == 0U                             ) ||
           ( mode                                     > CRYPTO_OPERATIONMODE_SINGLECALL)
         )
       )
    {
      /* !LINKSTO SWS_Csm_01045,1, CSM.Req.Api/Csm_Service/00001,1, CSM.Req.Api/Csm_Service/00002,1 */
      result = E_NOT_OK;
    }
    else
    {
      /* !LINKSTO CSM.Req.Correction.SWS_Csm_01027,1 */
      jobPrimitiveInputOutput.mode                 = mode;
      jobPrimitiveInputOutput.inputPtr             = ciphertextPtr;
      jobPrimitiveInputOutput.inputLength          = ciphertextLength;
      jobPrimitiveInputOutput.secondaryInputPtr    = associatedDataPtr;
      jobPrimitiveInputOutput.secondaryInputLength = associatedDataLength;
      jobPrimitiveInputOutput.tertiaryInputPtr     = tagPtr;
      jobPrimitiveInputOutput.tertiaryInputLength  = tagLength;
      jobPrimitiveInputOutput.outputPtr            = plaintextPtr;
      jobPrimitiveInputOutput.outputLengthPtr      = plaintextLengthPtr;
      jobPrimitiveInputOutput.verifyPtr            = verifyPtr;

      result = Csm_Process(jobId, &jobPrimitiveInputOutput);
    }
  }

  return result;
}
#endif /* #if (CSM_API_ENABLED_SERVICE_AEADDECRYPT == STD_ON) */

/* --- Csm_AEADEncrypt -------------------------------------------------------------------------- */

/* !LINKSTO CSM.Dsn.SWS_Csm_01023,1 */

#if (CSM_API_ENABLED_SERVICE_AEADENCRYPT == STD_ON)
/* Deviation CODEMETRIC-2 */
FUNC(Std_ReturnType, CSM_CODE) Csm_AEADEncrypt
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) plaintextPtr,
          uint32                                              plaintextLength,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) associatedDataPtr,
          uint32                                              associatedDataLength,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) ciphertextPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) ciphertextLengthPtr,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) tagPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) tagLengthPtr
)
{
  Std_ReturnType                     result                  = E_NOT_OK;
  Crypto_JobPrimitiveInputOutputType jobPrimitiveInputOutput = {
                                                                 NULL_PTR, 0U,                    /* inputPtr,           inputLength              */
                                                                 NULL_PTR, 0U,                    /* secondaryInputPtr,  secondaryInputLength     */
                                                                 NULL_PTR, 0U,                    /* tertiaryInputPtr,   tertiaryInputLength      */
                                                                 NULL_PTR, NULL_PTR,              /* outputPtr,          outputLengthPtr          */
                                                                 NULL_PTR, NULL_PTR,              /* secondaryOutputPtr, secondaryOutputLengthPtr */
#if (   (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_440) \
    )
                                                                 0U,                              /* input64                                      */
#endif /* #if (   (CSM_API_VERSION == CSM_API_VERSION_431) ... */
                                                                 NULL_PTR,                        /* verifyPtr                                    */
#if (CSM_API_VERSION != CSM_API_VERSION_EB)
                                                                 NULL_PTR,                        /* output64Ptr                                  */
#endif /* #if (CSM_API_VERSION != CSM_API_VERSION_EB) */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL, /* mode                                         */
                                                                 0U,                              /* cryIfKeyId                                   */
                                                                 0U,                              /* targetCryIfKeyId                             */
#else /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL  /* mode                                         */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                               };

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_AEADENCRYPT,
                          CSM_E_UNINIT
                         );
  }
  else
  if (jobId >= CSM_JOB_COUNT)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00002,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_AEADENCRYPT,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (Csm_JobConfigurations[jobId].jobPrimitiveInfo->primitiveInfo->service != CRYPTO_AEADENCRYPT)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00003,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_AEADENCRYPT,
                          CSM_E_SERVICE_NOT_IDENTICAL
                         );
  }
  else
  if (plaintextPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_AEADENCRYPT,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (associatedDataPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_AEADENCRYPT,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (ciphertextPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_AEADENCRYPT,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (ciphertextLengthPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_AEADENCRYPT,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (tagPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_AEADENCRYPT,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (tagLengthPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_AEADENCRYPT,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    if ( (  (mode & CRYPTO_OPERATIONMODE_SINGLECALL) ==
              (CRYPTO_OPERATIONMODE_START|CRYPTO_OPERATIONMODE_FINISH)
         ) ||
         ( ((mode & CRYPTO_OPERATIONMODE_SINGLECALL) == 0U                             ) ||
           ( mode                                     > CRYPTO_OPERATIONMODE_SINGLECALL)
         )
       )
    {
      /* !LINKSTO SWS_Csm_01045,1, CSM.Req.Api/Csm_Service/00001,1, CSM.Req.Api/Csm_Service/00002,1 */
      result = E_NOT_OK;
    }
    else
    {
      /* !LINKSTO CSM.Req.Correction.SWS_Csm_01025,1 */
      jobPrimitiveInputOutput.mode                     = mode;
      jobPrimitiveInputOutput.inputPtr                 = plaintextPtr;
      jobPrimitiveInputOutput.inputLength              = plaintextLength;
      jobPrimitiveInputOutput.secondaryInputPtr        = associatedDataPtr;
      jobPrimitiveInputOutput.secondaryInputLength     = associatedDataLength;
      jobPrimitiveInputOutput.outputPtr                = ciphertextPtr;
      jobPrimitiveInputOutput.outputLengthPtr          = ciphertextLengthPtr;
      jobPrimitiveInputOutput.secondaryOutputPtr       = tagPtr;
      jobPrimitiveInputOutput.secondaryOutputLengthPtr = tagLengthPtr;

      result = Csm_Process(jobId, &jobPrimitiveInputOutput);
    }
  }

  return result;
}
#endif /* #if (CSM_API_ENABLED_SERVICE_AEADENCRYPT == STD_ON) */

/* --- Csm_CallbackNotification ----------------------------------------------------------------- */

/* !LINKSTO CSM.Dsn.SWS_Csm_00970,1 */

FUNC(void, CSM_CODE) Csm_CallbackNotification
(
  P2CONST(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) job,
          Std_ReturnType                            result
)
{
#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_CALLBACKNOTIFICATION,
                          CSM_E_UNINIT
                         );
  }
  else
  if (job == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_CALLBACKNOTIFICATION,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    if(Csm_JobExtraCnfg[job->jobId].csmSWCCallback != NULL_PTR)
    {
      Csm_JobExtraData[job->jobId].callbackSWCResult = result;
      Csm_JobExtraCnfg[job->jobId].internalTrigger();
    }
#if (CSM_RTE_ENABLED_CALLBACK == STD_ON)
    else
    if (Csm_Callbacks[job->jobPrimitiveInfo->callbackId].internalTrigger != NULL_PTR)
    {
      Csm_CallbacksExtraData[job->jobPrimitiveInfo->callbackId].job = job;
      Csm_CallbacksExtraData[job->jobPrimitiveInfo->callbackId].result = result;
      Csm_Callbacks[job->jobPrimitiveInfo->callbackId].internalTrigger();
    }
#endif /* #if (CSM_RTE_ENABLED_CALLBACK == STD_ON) */
    else
    {
      Csm_Int_CallbackNotification(job, result);
    }
  }
}

/* --- Csm_CancelJob ---------------------------------------------------------------------------- */

/* !LINKSTO CSM.Dsn.SWS_Csm_00968,1 */

#if (CSM_API_ENABLED_SERVICE_GENERAL == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_CancelJob
(
  uint32                   job,
  Crypto_OperationModeType mode
)
{
  Std_ReturnType result = E_NOT_OK;

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_CANCELJOB,
                          CSM_E_UNINIT
                         );
  }
  else
  if (job >= CSM_JOB_COUNT)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00002,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_CANCELJOB,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    boolean run = FALSE;
    /* Deviation MISRAC2012-1 <+1> */
    TS_PARAM_UNUSED(mode);

    /* !LINKSTO CSM.Dsn.Api/ExAreas/00001,1, CSM.Dsn.Api/ExAreas/00002,1 */
    SchM_Enter_Csm_SCHM_CSM_EXCLUSIVE_AREA_0();
    /* !LINKSTO CSM.Req.Api/Csm_CancelJob/00001,1 */
    if (Csm_JobExtraData[job].csmLockFlag == FALSE)
    {
      Csm_JobExtraData[job].csmLockFlag = TRUE;
      run = TRUE;
    }
    SchM_Exit_Csm_SCHM_CSM_EXCLUSIVE_AREA_0();

    if (TRUE == run)
    {
      if (Csm_JobConfigurations[job].jobPrimitiveInfo->processingType == CRYPTO_PROCESSING_ASYNC)
      {
        /* !LINKSTO SWS_Csm_01021,1 */
        if (Csm_JobExtraData[job].csmQueueLevel == CSM_QL_CSM)
        {
          /* !LINKSTO CSM.Dsn.Api/ExAreas/00001,1, CSM.Dsn.Api/ExAreas/00002,1 */
          SchM_Enter_Csm_SCHM_CSM_EXCLUSIVE_AREA_0();
          result = Csm_QueueDelJob(Csm_JobExtraCnfg[job].csmQueue,
                                      &(Csm_JobConfigurations[job])
                                    );
          SchM_Exit_Csm_SCHM_CSM_EXCLUSIVE_AREA_0();
        }
        else
        if (Csm_JobExtraData[job].csmQueueLevel == CSM_QL_CRYPTO)
        {
          /* !LINKSTO SWS_Csm_00506,1, SWS_Csm_01021,1 */
          result = CryIf_CancelJob(Csm_JobExtraCnfg[job].csmQueue->cryIfChannelId,
                                  &(Csm_JobConfigurations[job])
                                  );
        }
        else
        {
          /* intentionally empty */
        }

        if (result == E_OK)
        {
          if((Csm_JobExtraData[job].csmQueueLevel == CSM_QL_CSM) &&
             (Csm_JobExtraCnfg[job].csmSWCCallback != NULL_PTR)
            )
          {
            Csm_JobExtraCnfg[job].csmSWCCallback(CRYPTO_E_JOB_CANCELED);
          }
          else
          {
#if (CSM_CBK_COUNT != 0U)
            if ((Csm_JobExtraData[job].csmQueueLevel == CSM_QL_CSM) &&
                (Csm_JobConfigurations[job].jobPrimitiveInfo->callbackId != CSM_CBK_EMPTY)
               )
            {
              /* !LINKSTO SWS_Csm_01030,1 */
              Csm_Callbacks[Csm_JobConfigurations[job].jobPrimitiveInfo->callbackId].callback
              (
                &(Csm_JobConfigurations[job]),
                CRYPTO_E_JOB_CANCELED
              );
            }
#endif /* #if (CSM_CBK_COUNT != 0U) */
          }
          Csm_JobExtraData[job].csmQueueLevel = CSM_QL_NONE;
        }
      }
      else
      {
        /* !LINKSTO SWS_Csm_00506,1 */
        result = CryIf_CancelJob(Csm_JobExtraCnfg[job].csmQueue->cryIfChannelId,
                                &(Csm_JobConfigurations[job])
                                );
      }
      /* !LINKSTO CSM.Dsn.Api/ExAreas/00001,1, CSM.Dsn.Api/ExAreas/00002,1 */
      SchM_Enter_Csm_SCHM_CSM_EXCLUSIVE_AREA_0();
      /* !LINKSTO CSM.Req.Api/Csm_CancelJob/00002,1 */
      Csm_JobExtraData[job].csmLockFlag = FALSE;
      SchM_Exit_Csm_SCHM_CSM_EXCLUSIVE_AREA_0();
    }
    else
    {
      /* !LINKSTO CSM.Req.Api/Csm_CancelJob/00001,1 */
      result = E_NOT_OK;
    }
  }

  return result;
}
#endif /* #if (CSM_API_ENABLED_SERVICE_GENERAL == STD_ON) */

/* --- Csm_CertificateParse --------------------------------------------------------------------- */

/* !LINKSTO SWS_Csm_01036,1, CSM.Req.Gen/CsmKeys/00002,1 */

#if (CSM_API_ENABLED_KEYMNGMNT == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_CertificateParse
(
  uint32 keyId
)
{
  Std_ReturnType result = E_NOT_OK;

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_CERTIFICATEPARSE,
                          CSM_E_UNINIT
                         );
  }
  else
  if (keyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_CERTIFICATEPARSE,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* !LINKSTO SWS_Csm_00506,1, SWS_Csm_01037,1 */
    result = CryIf_CertificateParse(Csm_Keys[keyId]);
  }

  return result;
}
#endif /* #if (CSM_API_ENABLED_KEYMNGMNT == STD_ON) */

/* --- Csm_CertificateVerify -------------------------------------------------------------------- */

/* !LINKSTO SWS_Csm_01038,1, CSM.Req.Gen/CsmKeys/00002,1 */

#if (CSM_API_ENABLED_KEYMNGMNT == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_CertificateVerify
(
        uint32                                             keyId,
        uint32                                             verifyCryIfKeyId,
  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_DATA) verifyPtr
)
{
  Std_ReturnType result = E_NOT_OK;

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_CERTIFICATEVERIFY,
                          CSM_E_UNINIT
                         );
  }
  else
  if (keyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_CERTIFICATEVERIFY,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (verifyCryIfKeyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_CERTIFICATEVERIFY,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (verifyPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_CERTIFICATEVERIFY,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* !LINKSTO SWS_Csm_00506,1, SWS_Csm_01040,1 */
    result = CryIf_CertificateVerify(Csm_Keys[keyId], Csm_Keys[verifyCryIfKeyId], verifyPtr);
  }

  return result;
}
#endif /* #if (CSM_API_ENABLED_KEYMNGMNT == STD_ON) */

/* --- Csm_Decrypt ------------------------------------------------------------------------------ */

/* !LINKSTO CSM.Dsn.SWS_Csm_00989,1 */

#if (CSM_API_ENABLED_SERVICE_DECRYPT == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_Decrypt
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                              dataLength,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) resultPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
)
{
  Std_ReturnType                     result                  = E_NOT_OK;
  Crypto_JobPrimitiveInputOutputType jobPrimitiveInputOutput = {
                                                                 NULL_PTR, 0U,                    /* inputPtr,           inputLength              */
                                                                 NULL_PTR, 0U,                    /* secondaryInputPtr,  secondaryInputLength     */
                                                                 NULL_PTR, 0U,                    /* tertiaryInputPtr,   tertiaryInputLength      */
                                                                 NULL_PTR, NULL_PTR,              /* outputPtr,          outputLengthPtr          */
                                                                 NULL_PTR, NULL_PTR,              /* secondaryOutputPtr, secondaryOutputLengthPtr */
#if (   (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_440) \
    )
                                                                 0U,                              /* input64                                      */
#endif /* #if (   (CSM_API_VERSION == CSM_API_VERSION_431) ... */
                                                                 NULL_PTR,                        /* verifyPtr                                    */
#if (CSM_API_VERSION != CSM_API_VERSION_EB)
                                                                 NULL_PTR,                        /* output64Ptr                                  */
#endif /* #if (CSM_API_VERSION != CSM_API_VERSION_EB) */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL, /* mode                                         */
                                                                 0U,                              /* cryIfKeyId                                   */
                                                                 0U,                              /* targetCryIfKeyId                             */
#else /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL  /* mode                                         */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                               };

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_DECRYPT,
                          CSM_E_UNINIT
                         );
  }
  else
  if (jobId >= CSM_JOB_COUNT)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00002,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_DECRYPT,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (Csm_JobConfigurations[jobId].jobPrimitiveInfo->primitiveInfo->service != CRYPTO_DECRYPT)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00003,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_DECRYPT,
                          CSM_E_SERVICE_NOT_IDENTICAL
                         );
  }
  else
  if (dataPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_DECRYPT,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (resultPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_DECRYPT,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (resultLengthPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_DECRYPT,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    if ( (  (mode & CRYPTO_OPERATIONMODE_SINGLECALL) ==
              (CRYPTO_OPERATIONMODE_START|CRYPTO_OPERATIONMODE_FINISH)
         ) ||
         ( ((mode & CRYPTO_OPERATIONMODE_SINGLECALL) == 0U                             ) ||
           ( mode                                     > CRYPTO_OPERATIONMODE_SINGLECALL)
         )
       )
    {
      /* !LINKSTO SWS_Csm_01045,1, CSM.Req.Api/Csm_Service/00001,1, CSM.Req.Api/Csm_Service/00002,1 */
      result = E_NOT_OK;
    }
    else
    {
      /* !LINKSTO SWS_Csm_00990,1 */
      jobPrimitiveInputOutput.mode            = mode;
      jobPrimitiveInputOutput.inputPtr        = dataPtr;
      jobPrimitiveInputOutput.inputLength     = dataLength;
      jobPrimitiveInputOutput.outputPtr       = resultPtr;
      jobPrimitiveInputOutput.outputLengthPtr = resultLengthPtr;

      result = Csm_Process(jobId, &jobPrimitiveInputOutput);
    }
  }
#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (result == CRYPTO_E_SMALL_BUFFER)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00830,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_DECRYPT,
                          CRYPTO_E_SMALL_BUFFER
                         );
  }
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */

  return result;
}
#endif /* #if (CSM_API_ENABLED_SERVICE_DECRYPT == STD_ON) */

/* --- Csm_Encrypt ------------------------------------------------------------------------------ */

/* !LINKSTO CSM.Dsn.SWS_Csm_00984,1 */

#if (CSM_API_ENABLED_SERVICE_ENCRYPT == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_Encrypt
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                              dataLength,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) resultPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
)
{
  Std_ReturnType                     result                  = E_NOT_OK;
  Crypto_JobPrimitiveInputOutputType jobPrimitiveInputOutput = {
                                                                 NULL_PTR, 0U,                    /* inputPtr,           inputLength              */
                                                                 NULL_PTR, 0U,                    /* secondaryInputPtr,  secondaryInputLength     */
                                                                 NULL_PTR, 0U,                    /* tertiaryInputPtr,   tertiaryInputLength      */
                                                                 NULL_PTR, NULL_PTR,              /* outputPtr,          outputLengthPtr          */
                                                                 NULL_PTR, NULL_PTR,              /* secondaryOutputPtr, secondaryOutputLengthPtr */
#if (   (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_440) \
    )
                                                                 0U,                              /* input64                                      */
#endif /* #if (   (CSM_API_VERSION == CSM_API_VERSION_431) ... */
                                                                 NULL_PTR,                        /* verifyPtr                                    */
#if (CSM_API_VERSION != CSM_API_VERSION_EB)
                                                                 NULL_PTR,                        /* output64Ptr                                  */
#endif /* #if (CSM_API_VERSION != CSM_API_VERSION_EB) */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL, /* mode                                         */
                                                                 0U,                              /* cryIfKeyId                                   */
                                                                 0U,                              /* targetCryIfKeyId                             */
#else /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL  /* mode                                         */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                               };

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_ENCRYPT,
                          CSM_E_UNINIT
                         );
  }
  else
  if (jobId >= CSM_JOB_COUNT)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00002,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_ENCRYPT,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (Csm_JobConfigurations[jobId].jobPrimitiveInfo->primitiveInfo->service != CRYPTO_ENCRYPT)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00003,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_ENCRYPT,
                          CSM_E_SERVICE_NOT_IDENTICAL
                         );
  }
  else
  if (dataPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_ENCRYPT,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (resultPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_ENCRYPT,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (resultLengthPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_ENCRYPT,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    if ( (  (mode & CRYPTO_OPERATIONMODE_SINGLECALL) ==
              (CRYPTO_OPERATIONMODE_START|CRYPTO_OPERATIONMODE_FINISH)
         ) ||
         ( ((mode & CRYPTO_OPERATIONMODE_SINGLECALL) == 0U                             ) ||
           ( mode                                     > CRYPTO_OPERATIONMODE_SINGLECALL)
         )
       )
    {
      /* !LINKSTO SWS_Csm_01045,1, CSM.Req.Api/Csm_Service/00001,1, CSM.Req.Api/Csm_Service/00002,1 */
      result = E_NOT_OK;
    }
    else
    {
      /* !LINKSTO SWS_Csm_00986,1 */
      jobPrimitiveInputOutput.mode            = mode;
      jobPrimitiveInputOutput.inputPtr        = dataPtr;
      jobPrimitiveInputOutput.inputLength     = dataLength;
      jobPrimitiveInputOutput.outputPtr       = resultPtr;
      jobPrimitiveInputOutput.outputLengthPtr = resultLengthPtr;

      result = Csm_Process(jobId, &jobPrimitiveInputOutput);
    }
  }
#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (result == CRYPTO_E_SMALL_BUFFER)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00830,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_ENCRYPT,
                          CRYPTO_E_SMALL_BUFFER
                         );
  }
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */

  return result;
}
#endif /* #if (CSM_API_ENABLED_SERVICE_ENCRYPT == STD_ON) */

/* --- Csm_GetVersionInfo ----------------------------------------------------------------------- */

/* !LINKSTO CSM.Dsn.SWS_Csm_00705,1 */

#if (CSM_API_ENABLED_VERSIONINFO == STD_ON)
FUNC(void, CSM_CODE) Csm_GetVersionInfo
(
  P2VAR(Std_VersionInfoType, AUTOMATIC, CSM_APPL_DATA) versioninfo
)
{
#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (versioninfo == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_GETVERSIONINFO,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    versioninfo->vendorID         = CSM_VENDOR_ID;
    versioninfo->moduleID         = CSM_MODULE_ID;
    versioninfo->sw_major_version = CSM_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = CSM_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = CSM_SW_PATCH_VERSION;
  }
}
#endif /* #if (CSM_API_ENABLED_VERSIONINFO == STD_ON) */

/* --- Csm_Hash --------------------------------------------------------------------------------- */

/* !LINKSTO CSM.Dsn.SWS_Csm_00980,1 */

#if (CSM_API_ENABLED_SERVICE_HASH == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_Hash
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                              dataLength,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) resultPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
)
{
  Std_ReturnType                     result                  = E_NOT_OK;
  Crypto_JobPrimitiveInputOutputType jobPrimitiveInputOutput = {
                                                                 NULL_PTR, 0U,                    /* inputPtr,           inputLength              */
                                                                 NULL_PTR, 0U,                    /* secondaryInputPtr,  secondaryInputLength     */
                                                                 NULL_PTR, 0U,                    /* tertiaryInputPtr,   tertiaryInputLength      */
                                                                 NULL_PTR, NULL_PTR,              /* outputPtr,          outputLengthPtr          */
                                                                 NULL_PTR, NULL_PTR,              /* secondaryOutputPtr, secondaryOutputLengthPtr */
#if (   (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_440) \
    )
                                                                 0U,                              /* input64                                      */
#endif /* #if (   (CSM_API_VERSION == CSM_API_VERSION_431) ... */
                                                                 NULL_PTR,                        /* verifyPtr                                    */
#if (CSM_API_VERSION != CSM_API_VERSION_EB)
                                                                 NULL_PTR,                        /* output64Ptr                                  */
#endif /* #if (CSM_API_VERSION != CSM_API_VERSION_EB) */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL, /* mode                                         */
                                                                 0U,                              /* cryIfKeyId                                   */
                                                                 0U,                              /* targetCryIfKeyId                             */
#else /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL  /* mode                                         */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                               };

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_HASH,
                          CSM_E_UNINIT
                         );
  }
  else
  if (jobId >= CSM_JOB_COUNT)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00002,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_HASH,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (Csm_JobConfigurations[jobId].jobPrimitiveInfo->primitiveInfo->service != CRYPTO_HASH)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00003,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_HASH,
                          CSM_E_SERVICE_NOT_IDENTICAL
                         );
  }
  else
  if (dataPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_HASH,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (resultPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_HASH,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (resultLengthPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_HASH,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    if ( (  (mode & CRYPTO_OPERATIONMODE_SINGLECALL) ==
              (CRYPTO_OPERATIONMODE_START|CRYPTO_OPERATIONMODE_FINISH)
         ) ||
         ( ((mode & CRYPTO_OPERATIONMODE_SINGLECALL) == 0U                             ) ||
           ( mode                                     > CRYPTO_OPERATIONMODE_SINGLECALL)
         )
       )
    {
      /* !LINKSTO SWS_Csm_01045,1, CSM.Req.Api/Csm_Service/00001,1, CSM.Req.Api/Csm_Service/00002,1 */
      result = E_NOT_OK;
    }
    else
    {
      /* !LINKSTO SWS_Csm_01015,1 */
      jobPrimitiveInputOutput.mode            = mode;
      jobPrimitiveInputOutput.inputPtr        = dataPtr;
      jobPrimitiveInputOutput.inputLength     = dataLength;
      jobPrimitiveInputOutput.outputPtr       = resultPtr;
      jobPrimitiveInputOutput.outputLengthPtr = resultLengthPtr;

      result = Csm_Process(jobId, &jobPrimitiveInputOutput);
    }
  }
#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (result == CRYPTO_E_SMALL_BUFFER)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00830,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_HASH,
                          CRYPTO_E_SMALL_BUFFER
                         );
  }
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */

  return result;
}
#endif /* #if (CSM_API_ENABLED_SERVICE_HASH == STD_ON) */

/* --- Csm_Init --------------------------------------------------------------------------------- */

/* !LINKSTO CSM.Dsn.SWS_Csm_00646,1 */

FUNC(void, CSM_CODE) Csm_Init
(
#if (CSM_API_VERSION == CSM_API_VERSION_440)
  P2CONST(Csm_ConfigType, AUTOMATIC, CSM_APPL_DATA) configPtr
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
#if (CSM_API_VERSION != CSM_API_VERSION_440)
  void
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
)
{
  uint32 i = 0U;
  uint32 j = 0U;

#if (CSM_API_VERSION == CSM_API_VERSION_440)
  TS_PARAM_UNUSED(configPtr);
#endif  /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  /* Deviation TASKING-1 */
  Csm_Initialized = FALSE;
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */

  /* Deviation TASKING-2 */
  for (i=0U; i<CSM_JOB_COUNT; i++)
  {
    /* !LINKSTO CSM.Req.Api/Csm_Init/00001,1 */
    Csm_JobConfigurations[i].CSM_API_JOBSTATE                                         = CRYPTO_JOBSTATE_IDLE;
    Csm_JobConfigurations[i].cryptoKeyId                                              = CSM_KEY_EMPTY;
    Csm_JobConfigurations[i].CSM_API_JOBPRIMITIVEINPUTOUTPUT.inputPtr                 = NULL_PTR;
    Csm_JobConfigurations[i].CSM_API_JOBPRIMITIVEINPUTOUTPUT.inputLength              = 0U;
    Csm_JobConfigurations[i].CSM_API_JOBPRIMITIVEINPUTOUTPUT.secondaryInputPtr        = NULL_PTR;
    Csm_JobConfigurations[i].CSM_API_JOBPRIMITIVEINPUTOUTPUT.secondaryInputLength     = 0U;
    Csm_JobConfigurations[i].CSM_API_JOBPRIMITIVEINPUTOUTPUT.tertiaryInputPtr         = NULL_PTR;
    Csm_JobConfigurations[i].CSM_API_JOBPRIMITIVEINPUTOUTPUT.tertiaryInputLength      = 0U;
    Csm_JobConfigurations[i].CSM_API_JOBPRIMITIVEINPUTOUTPUT.outputPtr                = NULL_PTR;
    Csm_JobConfigurations[i].CSM_API_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr          = NULL_PTR;
    Csm_JobConfigurations[i].CSM_API_JOBPRIMITIVEINPUTOUTPUT.secondaryOutputPtr       = NULL_PTR;
    Csm_JobConfigurations[i].CSM_API_JOBPRIMITIVEINPUTOUTPUT.secondaryOutputLengthPtr = NULL_PTR;
    Csm_JobConfigurations[i].CSM_API_JOBPRIMITIVEINPUTOUTPUT.verifyPtr                = NULL_PTR;
    Csm_JobConfigurations[i].CSM_API_JOBPRIMITIVEINPUTOUTPUT.mode                     = CRYPTO_OPERATIONMODE_SINGLECALL;

    /* !LINKSTO CSM.Req.Api/Csm_Init/00003,1 */
    Csm_JobExtraCnfg[i].csmQueue->lockMainQueueDelJob = FALSE;
    Csm_JobExtraCnfg[i].csmQueue->lockMainProcessJob  = FALSE;
    Csm_JobExtraCnfg[i].csmQueue->currentSize         = 0U;
    Csm_JobExtraCnfg[i].csmQueue->head                = NULL_PTR;

    for (j=0U; j<Csm_JobExtraCnfg[i].csmQueue->maxSize; j++)
    {
      Csm_JobExtraCnfg[i].csmQueue->data[j].job  = NULL_PTR;
      Csm_JobExtraCnfg[i].csmQueue->data[j].next = NULL_PTR;
    }

    /* !LINKSTO CSM.Req.Api/Csm_Init/00002,1 */
    Csm_JobExtraData[i].csmQueueLevel = CSM_QL_NONE;
  }

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  Csm_Initialized = TRUE;

  /* CHECK: NOPARSE
   * Defensive Programming - unreachable code.
   */
  /* Deviation TASKING-3 */
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00659,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_INIT,
                          CSM_E_INIT_FAILED
                         );
  }
  /* CHECK: PARSE */
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
}

/* --- Csm_KeyCopy ------------------------------------------------------------------------------ */

/* !LINKSTO CSM.Dsn.SWS_Csm_01034,1, CSM.Req.Gen/CsmKeys/00002,1 */

#if (CSM_API_ENABLED_KEYMNGMNT == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyCopy
(
  uint32 keyId,
  uint32 targetKeyId
)
{
  Std_ReturnType result = E_NOT_OK;

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYCOPY,
                          CSM_E_UNINIT
                         );
  }
  else
  if (keyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYCOPY,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (targetKeyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYCOPY,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* !LINKSTO SWS_Csm_00506,1, CSM.Req.Correction.SWS_Csm_01035,1 */
    result = CryIf_KeyCopy(Csm_Keys[keyId], Csm_Keys[targetKeyId]);
  }

  return result;
}
#endif /* #if (CSM_API_ENABLED_KEYMNGMNT == STD_ON) */

/* --- Csm_KeyDerive ---------------------------------------------------------------------------- */

/* !LINKSTO CSM.Dsn.SWS_Csm_00956,1, CSM.Req.Gen/CsmKeys/00002,1 */

#if (CSM_API_ENABLED_KEYMNGMNT == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyDerive
(
  uint32 keyId,
  uint32 targetKeyId
)
{
  Std_ReturnType result = E_NOT_OK;

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYDERIVE,
                          CSM_E_UNINIT
                         );
  }
  else
  if (keyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYDERIVE,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (targetKeyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYDERIVE,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* !LINKSTO SWS_Csm_00506,1, SWS_Csm_01018,1 */
    result = CryIf_KeyDerive(Csm_Keys[keyId], Csm_Keys[targetKeyId]);
  }

  return result;
}
#endif /* #if (CSM_API_ENABLED_KEYMNGMNT == STD_ON) */

/* --- Csm_KeyElementCopy ----------------------------------------------------------------------- */

/* !LINKSTO CSM.Dsn.SWS_Csm_00969,1, CSM.Req.Gen/CsmKeys/00002,1 */

#if (CSM_API_ENABLED_KEYMNGMNT == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementCopy
(
  uint32 keyId,
  uint32 keyElementId,
  uint32 targetKeyId,
  uint32 targetKeyElementId
)
{
  Std_ReturnType result = E_NOT_OK;

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYELEMENTCOPY,
                          CSM_E_UNINIT
                         );
  }
  else
  if (keyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYELEMENTCOPY,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (targetKeyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYELEMENTCOPY,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* !LINKSTO SWS_Csm_00506,1, SWS_Csm_01032,1 */
    result = CryIf_KeyElementCopy(Csm_Keys[keyId], keyElementId, Csm_Keys[targetKeyId], targetKeyElementId);
  }

  return result;
}
#endif /* #if (CSM_API_ENABLED_KEYMNGMNT == STD_ON) */

/* --- Csm_KeyElementGet ------------------------------------------------------------------------ */

/* !LINKSTO CSM.Dsn.SWS_Csm_00959,1, CSM.Req.Gen/CsmKeys/00002,1 */

#if (CSM_API_ENABLED_KEYMNGMNT == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementGet
(
        uint32                            keyId,
        uint32                            keyElementId,
  P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA) keyPtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) keyLengthPtr
)
{
  Std_ReturnType result = E_NOT_OK;

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYELEMENTGET,
                          CSM_E_UNINIT
                         );
  }
  else
  if (keyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYELEMENTGET,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (keyPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYELEMENTGET,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (keyLengthPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYELEMENTGET,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* !LINKSTO SWS_Csm_00506,1, SWS_Csm_01004,1 */
    result = CryIf_KeyElementGet(Csm_Keys[keyId], keyElementId, keyPtr, keyLengthPtr);
  }
#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (result == CRYPTO_E_SMALL_BUFFER)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00830,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYELEMENTGET,
                          CRYPTO_E_SMALL_BUFFER
                         );
  }
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */

  return result;
}
#endif /* #if (CSM_API_ENABLED_KEYMNGMNT == STD_ON) */

/* --- Csm_KeyElementSet ------------------------------------------------------------------------ */

/* !LINKSTO CSM.Dsn.SWS_Csm_00957,1, CSM.Req.Gen/CsmKeys/00002,1 */

#if (CSM_API_ENABLED_KEYMNGMNT == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementSet
(
          uint32                            keyId,
          uint32                            keyElementId,
  P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA) keyPtr,
          uint32                            keyLength
)
{
  Std_ReturnType result = E_NOT_OK;

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYELEMENTSET,
                          CSM_E_UNINIT
                         );
  }
  else
  if (keyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYELEMENTSET,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (keyPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYELEMENTSET,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* !LINKSTO SWS_Csm_00506,1, SWS_Csm_01002,1 */
    result = CryIf_KeyElementSet(Csm_Keys[keyId], keyElementId, keyPtr, keyLength);
  }

  return result;
}
#endif /* #if (CSM_API_ENABLED_KEYMNGMNT == STD_ON) */

/* --- Csm_KeyExchangeCalcPubVal ---------------------------------------------------------------- */

/* !LINKSTO CSM.Dsn.SWS_Csm_00966,1, CSM.Req.Gen/CsmKeys/00002,1 */

#if (CSM_API_ENABLED_KEYMNGMNT == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyExchangeCalcPubVal
(
        uint32                            keyId,
  P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA) publicValuePtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) publicValueLengthPtr
)
{
  Std_ReturnType result = E_NOT_OK;

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYEXCHANGECALCPUBVAL,
                          CSM_E_UNINIT
                         );
  }
  else
  if (keyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYEXCHANGECALCPUBVAL,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (publicValuePtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYEXCHANGECALCPUBVAL,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (publicValueLengthPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYEXCHANGECALCPUBVAL,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* !LINKSTO SWS_Csm_00506,1, SWS_Csm_01020,1 */
    result = CryIf_KeyExchangeCalcPubVal(Csm_Keys[keyId], publicValuePtr, publicValueLengthPtr);
  }
#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (result == CRYPTO_E_SMALL_BUFFER)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00830,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYEXCHANGECALCPUBVAL,
                          CRYPTO_E_SMALL_BUFFER
                         );
  }
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */

  return result;
}
#endif /* #if (CSM_API_ENABLED_KEYMNGMNT == STD_ON) */

/* --- Csm_KeyExchangeCalcSecret ---------------------------------------------------------------- */

/* !LINKSTO CSM.Dsn.SWS_Csm_00967,1, CSM.Req.Gen/CsmKeys/00002,1 */

#if (CSM_API_ENABLED_KEYMNGMNT == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyExchangeCalcSecret
(
          uint32                            keyId,
  P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA) partnerPublicValuePtr,
          uint32                            partnerPublicValueLength
)
{
  Std_ReturnType result = E_NOT_OK;

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYEXCHANGECALCSECRET,
                          CSM_E_UNINIT
                         );
  }
  else
  if (keyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYEXCHANGECALCSECRET,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (partnerPublicValuePtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYEXCHANGECALCSECRET,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* !LINKSTO SWS_Csm_00506,1, SWS_Csm_01006,1 */
    result = CryIf_KeyExchangeCalcSecret(Csm_Keys[keyId], partnerPublicValuePtr, partnerPublicValueLength);
  }
#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (result == CRYPTO_E_SMALL_BUFFER)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00830,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYEXCHANGECALCSECRET,
                          CRYPTO_E_SMALL_BUFFER
                         );
  }
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */

  return result;
}
#endif /* #if (CSM_API_ENABLED_KEYMNGMNT == STD_ON) */

/* --- Csm_KeyGenerate -------------------------------------------------------------------------- */

/* !LINKSTO CSM.Dsn.SWS_Csm_00955,1, CSM.Req.Gen/CsmKeys/00002,1 */

#if (CSM_API_ENABLED_KEYMNGMNT == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyGenerate
(
  uint32 keyId
)
{
  Std_ReturnType result = E_NOT_OK;

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYGENERATE,
                          CSM_E_UNINIT
                         );
  }
  else
  if (keyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYGENERATE,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* !LINKSTO SWS_Csm_00506,1, SWS_Csm_01005,1 */
    result = CryIf_KeyGenerate(Csm_Keys[keyId]);
  }

  return result;
}
#endif /* #if (CSM_API_ENABLED_KEYMNGMNT == STD_ON) */

/* --- Csm_KeySetValid -------------------------------------------------------------------------- */

/* !LINKSTO CSM.Dsn.SWS_Csm_00958,1, CSM.Req.Gen/CsmKeys/00002,1 */

#if (CSM_API_ENABLED_KEYMNGMNT == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_KeySetValid
(
  uint32 keyId
)
{
  Std_ReturnType result = E_NOT_OK;

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYSETVALID,
                          CSM_E_UNINIT
                         );
  }
  else
  if (keyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYSETVALID,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* !LINKSTO SWS_Csm_00506,1, SWS_Csm_01003,1 */
    result = CryIf_KeySetValid(Csm_Keys[keyId]);
  }

  return result;
}
#endif /* #if (CSM_API_ENABLED_KEYMNGMNT == STD_ON) */

/* --- Csm_KeySetInvalid ------------------------------------------------------------------------ */

/* !LINKSTO CSM.Dsn.SWS_Csm_91075,1, CSM.Req.Gen/CsmKeys/00002,1 */

#if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_API_ENABLED_KEYSETINVALID == STD_ON))
FUNC(Std_ReturnType, CSM_CODE) Csm_KeySetInvalid
(
  uint32 keyId
)
{
  Std_ReturnType result = E_NOT_OK;

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYSETINVALID,
                          CSM_E_UNINIT
                         );
  }
  else
  if (keyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYSETINVALID,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* !LINKSTO SWS_Csm_00506,1, Csm.ASR20-11.SWS_Csm_91050,1 */
    result = CryIf_KeySetInvalid(Csm_Keys[keyId]);
  }

  return result;
}
#endif /* #if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_API_ENABLED_KEYSETINVALID == STD_ON)) */

/* --- Csm_KeyGetStatus ------------------------------------------------------------------------- */

/* !LINKSTO CSM.Dsn.SWS_Csm_91047,1, CSM.Req.Gen/CsmKeys/00002,1 */

#if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_API_ENABLED_KEYGETSTATUS == STD_ON))
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyGetStatus
(
        uint32                                          keyId,
  P2VAR(Crypto_KeyStatusType, AUTOMATIC, CSM_APPL_DATA) keyStatusPtr
)
{
  Std_ReturnType result = E_NOT_OK;

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYGETSTATUS,
                          CSM_E_UNINIT
                         );
  }
  else
  if (keyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYGETSTATUS,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (keyStatusPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYGETSTATUS,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* !LINKSTO SWS_Csm_00506,1, Csm.ASR20-11.SWS_Csm_91048,1 */
    result = CryIf_KeyGetStatus(Csm_Keys[keyId], keyStatusPtr);
  }

  return result;
}
#endif /* #if ((CSM_API_ENABLED_KEYMNGMNT == STD_ON) && (CSM_API_ENABLED_KEYGETSTATUS == STD_ON)) */

/* --- Csm_MacGenerate -------------------------------------------------------------------------- */

/* !LINKSTO CSM.Dsn.SWS_Csm_00982,1 */

#if (CSM_API_ENABLED_SERVICE_MACGENERATE == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_MacGenerate
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                              dataLength,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) macPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) macLengthPtr
)
{
  Std_ReturnType                     result                  = E_NOT_OK;
  Crypto_JobPrimitiveInputOutputType jobPrimitiveInputOutput = {
                                                                 NULL_PTR, 0U,                    /* inputPtr,           inputLength              */
                                                                 NULL_PTR, 0U,                    /* secondaryInputPtr,  secondaryInputLength     */
                                                                 NULL_PTR, 0U,                    /* tertiaryInputPtr,   tertiaryInputLength      */
                                                                 NULL_PTR, NULL_PTR,              /* outputPtr,          outputLengthPtr          */
                                                                 NULL_PTR, NULL_PTR,              /* secondaryOutputPtr, secondaryOutputLengthPtr */
#if (   (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_440) \
    )
                                                                 0U,                              /* input64                                      */
#endif /* #if (   (CSM_API_VERSION == CSM_API_VERSION_431) ... */
                                                                 NULL_PTR,                        /* verifyPtr                                    */
#if (CSM_API_VERSION != CSM_API_VERSION_EB)
                                                                 NULL_PTR,                        /* output64Ptr                                  */
#endif /* #if (CSM_API_VERSION != CSM_API_VERSION_EB) */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL, /* mode                                         */
                                                                 0U,                              /* cryIfKeyId                                   */
                                                                 0U,                              /* targetCryIfKeyId                             */
#else /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL  /* mode                                         */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                               };

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_MACGENERATE,
                          CSM_E_UNINIT
                         );
  }
  else
  if (jobId >= CSM_JOB_COUNT)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00002,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_MACGENERATE,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (Csm_JobConfigurations[jobId].jobPrimitiveInfo->primitiveInfo->service != CRYPTO_MACGENERATE)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00003,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_MACGENERATE,
                          CSM_E_SERVICE_NOT_IDENTICAL
                         );
  }
  else
  if (dataPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_MACGENERATE,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (macPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_MACGENERATE,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (macLengthPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_MACGENERATE,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    if ( (  (mode & CRYPTO_OPERATIONMODE_SINGLECALL) ==
              (CRYPTO_OPERATIONMODE_START|CRYPTO_OPERATIONMODE_FINISH)
         ) ||
         ( ((mode & CRYPTO_OPERATIONMODE_SINGLECALL) == 0U                             ) ||
           ( mode                                     > CRYPTO_OPERATIONMODE_SINGLECALL)
         )
       )
    {
      /* !LINKSTO SWS_Csm_01045,1, CSM.Req.Api/Csm_Service/00001,1, CSM.Req.Api/Csm_Service/00002,1 */
      result = E_NOT_OK;
    }
    else
    {
      /* !LINKSTO SWS_Csm_01017,1 */
      jobPrimitiveInputOutput.mode            = mode;
      jobPrimitiveInputOutput.inputPtr        = dataPtr;
      jobPrimitiveInputOutput.inputLength     = dataLength;
      jobPrimitiveInputOutput.outputPtr       = macPtr;
      jobPrimitiveInputOutput.outputLengthPtr = macLengthPtr;

      result = Csm_Process(jobId, &jobPrimitiveInputOutput);
    }
  }
#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (result == CRYPTO_E_SMALL_BUFFER)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00830,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_MACGENERATE,
                          CRYPTO_E_SMALL_BUFFER
                         );
  }
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */

  return result;
}
#endif /* #if (CSM_API_ENABLED_SERVICE_MACGENERATE == STD_ON) */

/* --- Csm_MacVerify ---------------------------------------------------------------------------- */

/* !LINKSTO CSM.Dsn.SWS_Csm_01050,1 */

#if (CSM_API_ENABLED_SERVICE_MACVERIFY == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_MacVerify
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                              dataLength,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) macPtr,
          uint32                                              macLength,
    P2VAR(Crypto_VerifyResultType,  AUTOMATIC, CSM_APPL_DATA) verifyPtr
)
{
  Std_ReturnType                     result                  = E_NOT_OK;
  Crypto_JobPrimitiveInputOutputType jobPrimitiveInputOutput = {
                                                                 NULL_PTR, 0U,                    /* inputPtr,           inputLength              */
                                                                 NULL_PTR, 0U,                    /* secondaryInputPtr,  secondaryInputLength     */
                                                                 NULL_PTR, 0U,                    /* tertiaryInputPtr,   tertiaryInputLength      */
                                                                 NULL_PTR, NULL_PTR,              /* outputPtr,          outputLengthPtr          */
                                                                 NULL_PTR, NULL_PTR,              /* secondaryOutputPtr, secondaryOutputLengthPtr */
#if (   (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_440) \
    )
                                                                 0U,                              /* input64                                      */
#endif /* #if (   (CSM_API_VERSION == CSM_API_VERSION_431) ... */
                                                                 NULL_PTR,                        /* verifyPtr                                    */
#if (CSM_API_VERSION != CSM_API_VERSION_EB)
                                                                 NULL_PTR,                        /* output64Ptr                                  */
#endif /* #if (CSM_API_VERSION != CSM_API_VERSION_EB) */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL, /* mode                                         */
                                                                 0U,                              /* cryIfKeyId                                   */
                                                                 0U,                              /* targetCryIfKeyId                             */
#else /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL  /* mode                                         */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                               };

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_MACVERIFY,
                          CSM_E_UNINIT
                         );
  }
  else
  if (jobId >= CSM_JOB_COUNT)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00002,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_MACVERIFY,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (Csm_JobConfigurations[jobId].jobPrimitiveInfo->primitiveInfo->service != CRYPTO_MACVERIFY)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00003,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_MACVERIFY,
                          CSM_E_SERVICE_NOT_IDENTICAL
                         );
  }
  else
  if (dataPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_MACVERIFY,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (macPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_MACVERIFY,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (verifyPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_MACVERIFY,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    if ( (  (mode & CRYPTO_OPERATIONMODE_SINGLECALL) ==
              (CRYPTO_OPERATIONMODE_START|CRYPTO_OPERATIONMODE_FINISH)
         ) ||
         ( ((mode & CRYPTO_OPERATIONMODE_SINGLECALL) == 0U                             ) ||
           ( mode                                     > CRYPTO_OPERATIONMODE_SINGLECALL)
         )
       )
    {
      /* !LINKSTO SWS_Csm_01045,1, CSM.Req.Api/Csm_Service/00001,1, CSM.Req.Api/Csm_Service/00002,1 */
      result = E_NOT_OK;
    }
    else
    {
      /* !LINKSTO SWS_Csm_01016,1 */
      jobPrimitiveInputOutput.mode                 = mode;
      jobPrimitiveInputOutput.inputPtr             = dataPtr;
      jobPrimitiveInputOutput.inputLength          = dataLength;
      jobPrimitiveInputOutput.secondaryInputPtr    = macPtr;
      jobPrimitiveInputOutput.secondaryInputLength = macLength;
      jobPrimitiveInputOutput.verifyPtr            = verifyPtr;

      result = Csm_Process(jobId, &jobPrimitiveInputOutput);
    }
  }

  return result;
}
#endif /* #if (CSM_API_ENABLED_SERVICE_MACVERIFY == STD_ON) */

/* --- Csm_RandomGenerate ----------------------------------------------------------------------- */

/* !LINKSTO CSM.Dsn.SWS_Csm_01543,1 */

#if (CSM_API_ENABLED_SERVICE_RANDOMGENERATE == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_RandomGenerate
(
        uint32                            jobId,
  P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA) resultPtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
)
{
  Std_ReturnType                     result                  = E_NOT_OK;
  Crypto_JobPrimitiveInputOutputType jobPrimitiveInputOutput = {
                                                                 NULL_PTR, 0U,                    /* inputPtr,           inputLength              */
                                                                 NULL_PTR, 0U,                    /* secondaryInputPtr,  secondaryInputLength     */
                                                                 NULL_PTR, 0U,                    /* tertiaryInputPtr,   tertiaryInputLength      */
                                                                 NULL_PTR, NULL_PTR,              /* outputPtr,          outputLengthPtr          */
                                                                 NULL_PTR, NULL_PTR,              /* secondaryOutputPtr, secondaryOutputLengthPtr */
#if (   (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_440) \
    )
                                                                 0U,                              /* input64                                      */
#endif /* #if (   (CSM_API_VERSION == CSM_API_VERSION_431) ... */
                                                                 NULL_PTR,                        /* verifyPtr                                    */
#if (CSM_API_VERSION != CSM_API_VERSION_EB)
                                                                 NULL_PTR,                        /* output64Ptr                                  */
#endif /* #if (CSM_API_VERSION != CSM_API_VERSION_EB) */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL, /* mode                                         */
                                                                 0U,                              /* cryIfKeyId                                   */
                                                                 0U,                              /* targetCryIfKeyId                             */
#else /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL  /* mode                                         */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                               };

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_RANDOMGENERATE,
                          CSM_E_UNINIT
                         );
  }
  else
  if (jobId >= CSM_JOB_COUNT)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00002,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_RANDOMGENERATE,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (Csm_JobConfigurations[jobId].jobPrimitiveInfo->primitiveInfo->service != CRYPTO_RANDOMGENERATE)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00003,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_RANDOMGENERATE,
                          CSM_E_SERVICE_NOT_IDENTICAL
                         );
  }
  else
  if (resultPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_RANDOMGENERATE,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (resultLengthPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_RANDOMGENERATE,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    {
      /* !LINKSTO CSM.Req.Correction.SWS_Csm_01001,1 */
      jobPrimitiveInputOutput.outputPtr       = resultPtr;
      jobPrimitiveInputOutput.outputLengthPtr = resultLengthPtr;

      result = Csm_Process(jobId, &jobPrimitiveInputOutput);
    }
  }

  return result;
}
#endif /* #if (CSM_API_ENABLED_SERVICE_RANDOMGENERATE == STD_ON) */

/* --- Csm_RandomSeed --------------------------------------------------------------------------- */

/* !LINKSTO CSM.Dsn.SWS_Csm_01051,1, CSM.Req.Gen/CsmKeys/00002,1 */

#if (CSM_API_ENABLED_KEYMNGMNT == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_RandomSeed
(
          uint32                            keyId,
  P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA) seedPtr,
          uint32                            seedLength
)
{
  Std_ReturnType result = E_NOT_OK;

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_RANDOMSEED,
                          CSM_E_UNINIT
                         );
  }
  else
  if (keyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_RANDOMSEED,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (seedPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_RANDOMSEED,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* !LINKSTO SWS_Csm_00506,1, SWS_Csm_01052,1 */
    result = CryIf_RandomSeed(Csm_Keys[keyId], seedPtr, seedLength);
  }

  return result;
}
#endif /* #if (CSM_API_ENABLED_KEYMNGMNT == STD_ON) */

/* --- Csm_SignatureGenerate -------------------------------------------------------------------- */

/* !LINKSTO CSM.Dsn.SWS_Csm_00992,1 */

#if (CSM_API_ENABLED_SERVICE_SIGNATUREGENERATE == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_SignatureGenerate
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                              dataLength,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) resultPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
)
{
  Std_ReturnType                     result                  = E_NOT_OK;
  Crypto_JobPrimitiveInputOutputType jobPrimitiveInputOutput = {
                                                                 NULL_PTR, 0U,                    /* inputPtr,           inputLength              */
                                                                 NULL_PTR, 0U,                    /* secondaryInputPtr,  secondaryInputLength     */
                                                                 NULL_PTR, 0U,                    /* tertiaryInputPtr,   tertiaryInputLength      */
                                                                 NULL_PTR, NULL_PTR,              /* outputPtr,          outputLengthPtr          */
                                                                 NULL_PTR, NULL_PTR,              /* secondaryOutputPtr, secondaryOutputLengthPtr */
#if (   (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_440) \
    )
                                                                 0U,                              /* input64                                      */
#endif /* #if (   (CSM_API_VERSION == CSM_API_VERSION_431) ... */
                                                                 NULL_PTR,                        /* verifyPtr                                    */
#if (CSM_API_VERSION != CSM_API_VERSION_EB)
                                                                 NULL_PTR,                        /* output64Ptr                                  */
#endif /* #if (CSM_API_VERSION != CSM_API_VERSION_EB) */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL, /* mode                                         */
                                                                 0U,                              /* cryIfKeyId                                   */
                                                                 0U,                              /* targetCryIfKeyId                             */
#else /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL  /* mode                                         */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                               };

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_SIGNATUREGENERATE,
                          CSM_E_UNINIT
                         );
  }
  else
  if (jobId >= CSM_JOB_COUNT)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00002,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_SIGNATUREGENERATE,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (Csm_JobConfigurations[jobId].jobPrimitiveInfo->primitiveInfo->service != CRYPTO_SIGNATUREGENERATE)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00003,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_SIGNATUREGENERATE,
                          CSM_E_SERVICE_NOT_IDENTICAL
                         );
  }
  else
  if (dataPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_SIGNATUREGENERATE,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (resultPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_SIGNATUREGENERATE,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (resultLengthPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_SIGNATUREGENERATE,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    if ( (  (mode & CRYPTO_OPERATIONMODE_SINGLECALL) ==
              (CRYPTO_OPERATIONMODE_START|CRYPTO_OPERATIONMODE_FINISH)
         ) ||
         ( ((mode & CRYPTO_OPERATIONMODE_SINGLECALL) == 0U                             ) ||
           ( mode                                     > CRYPTO_OPERATIONMODE_SINGLECALL)
         )
       )
    {
      /* !LINKSTO SWS_Csm_01045,1, CSM.Req.Api/Csm_Service/00001,1, CSM.Req.Api/Csm_Service/00002,1 */
      result = E_NOT_OK;
    }
    else
    {
      /* !LINKSTO SWS_Csm_00993,1 */
      jobPrimitiveInputOutput.mode            = mode;
      jobPrimitiveInputOutput.inputPtr        = dataPtr;
      jobPrimitiveInputOutput.inputLength     = dataLength;
      jobPrimitiveInputOutput.outputPtr       = resultPtr;
      jobPrimitiveInputOutput.outputLengthPtr = resultLengthPtr;

      result = Csm_Process(jobId, &jobPrimitiveInputOutput);
    }
  }
#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (result == CRYPTO_E_SMALL_BUFFER)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00830,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_SIGNATUREGENERATE,
                          CRYPTO_E_SMALL_BUFFER
                         );
  }
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */

  return result;
}
#endif /* #if (CSM_API_ENABLED_SERVICE_SIGNATUREGENERATE == STD_ON) */

/* --- Csm_SignatureVerify ---------------------------------------------------------------------- */

/* !LINKSTO CSM.Dsn.SWS_Csm_00996,1 */

#if (CSM_API_ENABLED_SERVICE_SIGNATUREVERIFY == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_SignatureVerify
(
          uint32                                              jobId,
          Crypto_OperationModeType                            mode,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                              dataLength,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) signaturePtr,
          uint32                                              signatureLength,
    P2VAR(Crypto_VerifyResultType,  AUTOMATIC, CSM_APPL_DATA) verifyPtr
)
{
  Std_ReturnType                     result                  = E_NOT_OK;
  Crypto_JobPrimitiveInputOutputType jobPrimitiveInputOutput = {
                                                                 NULL_PTR, 0U,                    /* inputPtr,           inputLength              */
                                                                 NULL_PTR, 0U,                    /* secondaryInputPtr,  secondaryInputLength     */
                                                                 NULL_PTR, 0U,                    /* tertiaryInputPtr,   tertiaryInputLength      */
                                                                 NULL_PTR, NULL_PTR,              /* outputPtr,          outputLengthPtr          */
                                                                 NULL_PTR, NULL_PTR,              /* secondaryOutputPtr, secondaryOutputLengthPtr */
#if (   (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_440) \
    )
                                                                 0U,                              /* input64                                      */
#endif /* #if (   (CSM_API_VERSION == CSM_API_VERSION_431) ... */
                                                                 NULL_PTR,                        /* verifyPtr                                    */
#if (CSM_API_VERSION != CSM_API_VERSION_EB)
                                                                 NULL_PTR,                        /* output64Ptr                                  */
#endif /* #if (CSM_API_VERSION != CSM_API_VERSION_EB) */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL, /* mode                                         */
                                                                 0U,                              /* cryIfKeyId                                   */
                                                                 0U,                              /* targetCryIfKeyId                             */
#else /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL  /* mode                                         */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                               };

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_SIGNATUREVERIFY,
                          CSM_E_UNINIT
                         );
  }
  else
  if (jobId >= CSM_JOB_COUNT)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00002,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_SIGNATUREVERIFY,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (Csm_JobConfigurations[jobId].jobPrimitiveInfo->primitiveInfo->service != CRYPTO_SIGNATUREVERIFY)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00003,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_SIGNATUREVERIFY,
                          CSM_E_SERVICE_NOT_IDENTICAL
                         );
  }
  else
  if (dataPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_SIGNATUREVERIFY,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (signaturePtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_SIGNATUREVERIFY,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (verifyPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_SIGNATUREVERIFY,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    if ( (  (mode & CRYPTO_OPERATIONMODE_SINGLECALL) ==
              (CRYPTO_OPERATIONMODE_START|CRYPTO_OPERATIONMODE_FINISH)
         ) ||
         ( ((mode & CRYPTO_OPERATIONMODE_SINGLECALL) == 0U                             ) ||
           ( mode                                     > CRYPTO_OPERATIONMODE_SINGLECALL)
         )
       )
    {
      /* !LINKSTO SWS_Csm_01045,1, CSM.Req.Api/Csm_Service/00001,1, CSM.Req.Api/Csm_Service/00002,1 */
      result = E_NOT_OK;
    }
    else
    {
      /* !LINKSTO SWS_Csm_00997,1 */
      jobPrimitiveInputOutput.mode                 = mode;
      jobPrimitiveInputOutput.inputPtr             = dataPtr;
      jobPrimitiveInputOutput.inputLength          = dataLength;
      jobPrimitiveInputOutput.secondaryInputPtr    = signaturePtr;
      jobPrimitiveInputOutput.secondaryInputLength = signatureLength;
      jobPrimitiveInputOutput.verifyPtr            = verifyPtr;

      result = Csm_Process(jobId, &jobPrimitiveInputOutput);
    }
  }
#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (result == CRYPTO_E_SMALL_BUFFER)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00830,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_SIGNATUREVERIFY,
                          CRYPTO_E_SMALL_BUFFER
                         );
  }
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */

  return result;
}
#endif /* #if (CSM_API_ENABLED_SERVICE_SIGNATUREVERIFY == STD_ON) */

/* --- Csm_KeyElementCopyPartial ---------------------------------------------------------------- */

/* !LINKSTO Csm.Asr.SWS_Csm_91025,1 */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_API_ENABLED_KEYMNGMNT == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementCopyPartial
(
  uint32 keyId,
  uint32 keyElementId,
  uint32 keyElementSourceOffset,
  uint32 keyElementTargetOffset,
  uint32 keyElementCopyLength,
  uint32 targetKeyId,
  uint32 targetKeyElementId
)
{
  Std_ReturnType result = E_NOT_OK;

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYELEMENTCOPYPARTIAL,
                          CSM_E_UNINIT
                         );
  }
  else
  if (keyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYELEMENTCOPYPARTIAL,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (targetKeyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_KEYELEMENTCOPYPARTIAL,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    result = CryIf_KeyElementCopyPartial(Csm_Keys[keyId], keyElementId, keyElementSourceOffset, keyElementTargetOffset, keyElementCopyLength, Csm_Keys[targetKeyId], targetKeyElementId);
  }

  return result;
}
#endif /* #if (CSM_API_ENABLED_KEYMNGMNT == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_JobKeySetValid ----------------------------------------------------------------------- */

/* !LINKSTO Csm.Asr.SWS_Csm_91027,1 */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_API_ENABLED_SERVICE_JOBKEYSETVALID == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeySetValid
(
  uint32 jobId,
  uint32 keyId
)
{
  Std_ReturnType                     result                  = E_NOT_OK;
  Crypto_JobPrimitiveInputOutputType jobPrimitiveInputOutput = {
                                                                 NULL_PTR, 0U,                    /* inputPtr,           inputLength              */
                                                                 NULL_PTR, 0U,                    /* secondaryInputPtr,  secondaryInputLength     */
                                                                 NULL_PTR, 0U,                    /* tertiaryInputPtr,   tertiaryInputLength      */
                                                                 NULL_PTR, NULL_PTR,              /* outputPtr,          outputLengthPtr          */
                                                                 NULL_PTR, NULL_PTR,              /* secondaryOutputPtr, secondaryOutputLengthPtr */
#if (   (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_440) \
    )
                                                                 0U,                              /* input64                                      */
#endif /* #if (   (CSM_API_VERSION == CSM_API_VERSION_431) ... */
                                                                 NULL_PTR,                        /* verifyPtr                                    */
#if (CSM_API_VERSION != CSM_API_VERSION_EB)
                                                                 NULL_PTR,                        /* output64Ptr                                  */
#endif /* #if (CSM_API_VERSION != CSM_API_VERSION_EB) */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL, /* mode                                         */
                                                                 0U,                              /* cryIfKeyId                                   */
                                                                 0U,                              /* targetCryIfKeyId                             */
#else /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL  /* mode                                         */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                               };

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYSETVALID,
                          CSM_E_UNINIT
                         );
  }
  else
  if (jobId >= CSM_JOB_COUNT)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00002,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYSETVALID,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (Csm_JobConfigurations[jobId].jobPrimitiveInfo->primitiveInfo->service != CRYPTO_KEYSETVALID)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00003,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYSETVALID,
                          CSM_E_SERVICE_NOT_IDENTICAL
                         );
  }
  else
  if (keyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYSETVALID,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    {
      jobPrimitiveInputOutput.cryIfKeyId = keyId;

      result = Csm_Process(jobId, &jobPrimitiveInputOutput);
    }
  }

  return result;
}
#endif /* #if (CSM_API_ENABLED_SERVICE_JOBKEYSETVALID == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_JobRandomSeed ------------------------------------------------------------------------ */

/* !LINKSTO Csm.Asr.SWS_Csm_91028,1 */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_API_ENABLED_SERVICE_JOBRANDOMSEED == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_JobRandomSeed
(
          uint32                            jobId,
          uint32                            keyId,
  P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA) seedPtr,
          uint32                            seedLength
)
{
  Std_ReturnType                     result                  = E_NOT_OK;
  Crypto_JobPrimitiveInputOutputType jobPrimitiveInputOutput = {
                                                                 NULL_PTR, 0U,                    /* inputPtr,           inputLength              */
                                                                 NULL_PTR, 0U,                    /* secondaryInputPtr,  secondaryInputLength     */
                                                                 NULL_PTR, 0U,                    /* tertiaryInputPtr,   tertiaryInputLength      */
                                                                 NULL_PTR, NULL_PTR,              /* outputPtr,          outputLengthPtr          */
                                                                 NULL_PTR, NULL_PTR,              /* secondaryOutputPtr, secondaryOutputLengthPtr */
#if (   (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_440) \
    )
                                                                 0U,                              /* input64                                      */
#endif /* #if (   (CSM_API_VERSION == CSM_API_VERSION_431) ... */
                                                                 NULL_PTR,                        /* verifyPtr                                    */
#if (CSM_API_VERSION != CSM_API_VERSION_EB)
                                                                 NULL_PTR,                        /* output64Ptr                                  */
#endif /* #if (CSM_API_VERSION != CSM_API_VERSION_EB) */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL, /* mode                                         */
                                                                 0U,                              /* cryIfKeyId                                   */
                                                                 0U,                              /* targetCryIfKeyId                             */
#else /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL  /* mode                                         */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                               };

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBRANDOMSEED,
                          CSM_E_UNINIT
                         );
  }
  else
  if (jobId >= CSM_JOB_COUNT)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00002,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBRANDOMSEED,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (Csm_JobConfigurations[jobId].jobPrimitiveInfo->primitiveInfo->service != CRYPTO_RANDOMSEED)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00003,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBRANDOMSEED,
                          CSM_E_SERVICE_NOT_IDENTICAL
                         );
  }
  else
  if (keyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBRANDOMSEED,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (seedPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBRANDOMSEED,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    {
      jobPrimitiveInputOutput.cryIfKeyId  = keyId;
      jobPrimitiveInputOutput.inputPtr    = seedPtr;
      jobPrimitiveInputOutput.inputLength = seedLength;

      result = Csm_Process(jobId, &jobPrimitiveInputOutput);
    }
  }

  return result;
}
#endif /* #if (CSM_API_ENABLED_SERVICE_JOBRANDOMSEED == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_JobKeyGenerate ----------------------------------------------------------------------- */

/* !LINKSTO Csm.Asr.SWS_Csm_91029,1 */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_API_ENABLED_SERVICE_JOBKEYGENERATE == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyGenerate
(
  uint32 jobId,
  uint32 keyId
)
{
  Std_ReturnType                     result                  = E_NOT_OK;
  Crypto_JobPrimitiveInputOutputType jobPrimitiveInputOutput = {
                                                                 NULL_PTR, 0U,                    /* inputPtr,           inputLength              */
                                                                 NULL_PTR, 0U,                    /* secondaryInputPtr,  secondaryInputLength     */
                                                                 NULL_PTR, 0U,                    /* tertiaryInputPtr,   tertiaryInputLength      */
                                                                 NULL_PTR, NULL_PTR,              /* outputPtr,          outputLengthPtr          */
                                                                 NULL_PTR, NULL_PTR,              /* secondaryOutputPtr, secondaryOutputLengthPtr */
#if (   (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_440) \
    )
                                                                 0U,                              /* input64                                      */
#endif /* #if (   (CSM_API_VERSION == CSM_API_VERSION_431) ... */
                                                                 NULL_PTR,                        /* verifyPtr                                    */
#if (CSM_API_VERSION != CSM_API_VERSION_EB)
                                                                 NULL_PTR,                        /* output64Ptr                                  */
#endif /* #if (CSM_API_VERSION != CSM_API_VERSION_EB) */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL, /* mode                                         */
                                                                 0U,                              /* cryIfKeyId                                   */
                                                                 0U,                              /* targetCryIfKeyId                             */
#else /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL  /* mode                                         */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                               };

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYGENERATE,
                          CSM_E_UNINIT
                         );
  }
  else
  if (jobId >= CSM_JOB_COUNT)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00002,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYGENERATE,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (Csm_JobConfigurations[jobId].jobPrimitiveInfo->primitiveInfo->service != CRYPTO_KEYGENERATE)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00003,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYGENERATE,
                          CSM_E_SERVICE_NOT_IDENTICAL
                         );
  }
  else
  if (keyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYGENERATE,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    {
      jobPrimitiveInputOutput.cryIfKeyId = keyId;

      result = Csm_Process(jobId, &jobPrimitiveInputOutput);
    }
  }

  return result;
}
#endif /* #if (CSM_API_ENABLED_SERVICE_JOBKEYGENERATE == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_JobKeyDerive ------------------------------------------------------------------------- */

/* !LINKSTO Csm.Asr.SWS_Csm_91030,1 */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_API_ENABLED_SERVICE_JOBKEYDERIVE == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyDerive
(
  uint32 jobId,
  uint32 keyId,
  uint32 targetKeyId
)
{
  Std_ReturnType                     result                  = E_NOT_OK;
  Crypto_JobPrimitiveInputOutputType jobPrimitiveInputOutput = {
                                                                 NULL_PTR, 0U,                    /* inputPtr,           inputLength              */
                                                                 NULL_PTR, 0U,                    /* secondaryInputPtr,  secondaryInputLength     */
                                                                 NULL_PTR, 0U,                    /* tertiaryInputPtr,   tertiaryInputLength      */
                                                                 NULL_PTR, NULL_PTR,              /* outputPtr,          outputLengthPtr          */
                                                                 NULL_PTR, NULL_PTR,              /* secondaryOutputPtr, secondaryOutputLengthPtr */
#if (   (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_440) \
    )
                                                                 0U,                              /* input64                                      */
#endif /* #if (   (CSM_API_VERSION == CSM_API_VERSION_431) ... */
                                                                 NULL_PTR,                        /* verifyPtr                                    */
#if (CSM_API_VERSION != CSM_API_VERSION_EB)
                                                                 NULL_PTR,                        /* output64Ptr                                  */
#endif /* #if (CSM_API_VERSION != CSM_API_VERSION_EB) */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL, /* mode                                         */
                                                                 0U,                              /* cryIfKeyId                                   */
                                                                 0U,                              /* targetCryIfKeyId                             */
#else /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL  /* mode                                         */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                               };

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYDERIVE,
                          CSM_E_UNINIT
                         );
  }
  else
  if (jobId >= CSM_JOB_COUNT)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00002,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYDERIVE,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (Csm_JobConfigurations[jobId].jobPrimitiveInfo->primitiveInfo->service != CRYPTO_KEYDERIVE)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00003,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYDERIVE,
                          CSM_E_SERVICE_NOT_IDENTICAL
                         );
  }
  else
  if (keyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYDERIVE,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (targetKeyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYDERIVE,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    {
      jobPrimitiveInputOutput.cryIfKeyId       = keyId;
      jobPrimitiveInputOutput.targetCryIfKeyId = targetKeyId;

      result = Csm_Process(jobId, &jobPrimitiveInputOutput);
    }
  }

  return result;
}
#endif /* #if (CSM_API_ENABLED_SERVICE_JOBKEYDERIVE == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_JobKeyExchangeCalcPubVal ------------------------------------------------------------- */

/* !LINKSTO Csm.Asr.SWS_Csm_91031,1 */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_API_ENABLED_SERVICE_JOBKEYEXCHANGECALCPUBVAL == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyExchangeCalcPubVal
(
        uint32                            jobId,
        uint32                            keyId,
  P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA) publicValuePtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) publicValueLengthPtr
)
{
  Std_ReturnType                     result                  = E_NOT_OK;
  Crypto_JobPrimitiveInputOutputType jobPrimitiveInputOutput = {
                                                                 NULL_PTR, 0U,                    /* inputPtr,           inputLength              */
                                                                 NULL_PTR, 0U,                    /* secondaryInputPtr,  secondaryInputLength     */
                                                                 NULL_PTR, 0U,                    /* tertiaryInputPtr,   tertiaryInputLength      */
                                                                 NULL_PTR, NULL_PTR,              /* outputPtr,          outputLengthPtr          */
                                                                 NULL_PTR, NULL_PTR,              /* secondaryOutputPtr, secondaryOutputLengthPtr */
#if (   (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_440) \
    )
                                                                 0U,                              /* input64                                      */
#endif /* #if (   (CSM_API_VERSION == CSM_API_VERSION_431) ... */
                                                                 NULL_PTR,                        /* verifyPtr                                    */
#if (CSM_API_VERSION != CSM_API_VERSION_EB)
                                                                 NULL_PTR,                        /* output64Ptr                                  */
#endif /* #if (CSM_API_VERSION != CSM_API_VERSION_EB) */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL, /* mode                                         */
                                                                 0U,                              /* cryIfKeyId                                   */
                                                                 0U,                              /* targetCryIfKeyId                             */
#else /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL  /* mode                                         */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                               };

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYEXCHANGECALCPUBVAL,
                          CSM_E_UNINIT
                         );
  }
  else
  if (jobId >= CSM_JOB_COUNT)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00002,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYEXCHANGECALCPUBVAL,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (Csm_JobConfigurations[jobId].jobPrimitiveInfo->primitiveInfo->service != CRYPTO_KEYEXCHANGECALCPUBVAL)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00003,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYEXCHANGECALCPUBVAL,
                          CSM_E_SERVICE_NOT_IDENTICAL
                         );
  }
  else
  if (keyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYEXCHANGECALCPUBVAL,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (publicValuePtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYEXCHANGECALCPUBVAL,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
  if (publicValueLengthPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYEXCHANGECALCPUBVAL,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    {
      jobPrimitiveInputOutput.cryIfKeyId      = keyId;
      jobPrimitiveInputOutput.outputPtr       = publicValuePtr;
      jobPrimitiveInputOutput.outputLengthPtr = publicValueLengthPtr;

      result = Csm_Process(jobId, &jobPrimitiveInputOutput);
    }
  }
#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (result == CRYPTO_E_SMALL_BUFFER)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00830,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYEXCHANGECALCPUBVAL,
                          CRYPTO_E_SMALL_BUFFER
                         );
  }
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */

  return result;
}
#endif /* #if (CSM_API_ENABLED_SERVICE_JOBKEYEXCHANGECALCPUBVAL == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_JobKeyExchangeCalcSecret ------------------------------------------------------------- */

/* !LINKSTO Csm.Asr.SWS_Csm_91032,1 */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_API_ENABLED_SERVICE_JOBKEYEXCHANGECALCSECRET == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyExchangeCalcSecret
(
          uint32                            jobId,
          uint32                            keyId,
  P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA) partnerPublicValuePtr,
          uint32                            partnerPublicValueLength
)
{
  Std_ReturnType                     result                  = E_NOT_OK;
  Crypto_JobPrimitiveInputOutputType jobPrimitiveInputOutput = {
                                                                 NULL_PTR, 0U,                    /* inputPtr,           inputLength              */
                                                                 NULL_PTR, 0U,                    /* secondaryInputPtr,  secondaryInputLength     */
                                                                 NULL_PTR, 0U,                    /* tertiaryInputPtr,   tertiaryInputLength      */
                                                                 NULL_PTR, NULL_PTR,              /* outputPtr,          outputLengthPtr          */
                                                                 NULL_PTR, NULL_PTR,              /* secondaryOutputPtr, secondaryOutputLengthPtr */
#if (   (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_440) \
    )
                                                                 0U,                              /* input64                                      */
#endif /* #if (   (CSM_API_VERSION == CSM_API_VERSION_431) ... */
                                                                 NULL_PTR,                        /* verifyPtr                                    */
#if (CSM_API_VERSION != CSM_API_VERSION_EB)
                                                                 NULL_PTR,                        /* output64Ptr                                  */
#endif /* #if (CSM_API_VERSION != CSM_API_VERSION_EB) */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL, /* mode                                         */
                                                                 0U,                              /* cryIfKeyId                                   */
                                                                 0U,                              /* targetCryIfKeyId                             */
#else /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL  /* mode                                         */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                               };

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYEXCHANGECALCSECRET,
                          CSM_E_UNINIT
                         );
  }
  else
  if (jobId >= CSM_JOB_COUNT)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00002,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYEXCHANGECALCSECRET,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (Csm_JobConfigurations[jobId].jobPrimitiveInfo->primitiveInfo->service != CRYPTO_KEYEXCHANGECALCSECRET)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00003,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYEXCHANGECALCSECRET,
                          CSM_E_SERVICE_NOT_IDENTICAL
                         );
  }
  else
  if (keyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYEXCHANGECALCSECRET,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (partnerPublicValuePtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYEXCHANGECALCSECRET,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    {
      jobPrimitiveInputOutput.cryIfKeyId  = keyId;
      jobPrimitiveInputOutput.inputPtr    = partnerPublicValuePtr;
      jobPrimitiveInputOutput.inputLength = partnerPublicValueLength;

      result = Csm_Process(jobId, &jobPrimitiveInputOutput);
    }
  }
#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (result == CRYPTO_E_SMALL_BUFFER)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00830,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBKEYEXCHANGECALCSECRET,
                          CRYPTO_E_SMALL_BUFFER
                         );
  }
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */

  return result;
}
#endif /* #if (CSM_API_ENABLED_SERVICE_JOBKEYEXCHANGECALCSECRET == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_JobCertificateParse ------------------------------------------------------------------ */

/* !LINKSTO Csm.Asr.SWS_Csm_91033,1 */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_API_ENABLED_SERVICE_JOBCERTIFICATEPARSE == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_JobCertificateParse
(
  uint32 jobId,
  uint32 keyId
)
{
  Std_ReturnType                     result                  = E_NOT_OK;
  Crypto_JobPrimitiveInputOutputType jobPrimitiveInputOutput = {
                                                                 NULL_PTR, 0U,                    /* inputPtr,           inputLength              */
                                                                 NULL_PTR, 0U,                    /* secondaryInputPtr,  secondaryInputLength     */
                                                                 NULL_PTR, 0U,                    /* tertiaryInputPtr,   tertiaryInputLength      */
                                                                 NULL_PTR, NULL_PTR,              /* outputPtr,          outputLengthPtr          */
                                                                 NULL_PTR, NULL_PTR,              /* secondaryOutputPtr, secondaryOutputLengthPtr */
#if (   (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_440) \
    )
                                                                 0U,                              /* input64                                      */
#endif /* #if (   (CSM_API_VERSION == CSM_API_VERSION_431) ... */
                                                                 NULL_PTR,                        /* verifyPtr                                    */
#if (CSM_API_VERSION != CSM_API_VERSION_EB)
                                                                 NULL_PTR,                        /* output64Ptr                                  */
#endif /* #if (CSM_API_VERSION != CSM_API_VERSION_EB) */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL, /* mode                                         */
                                                                 0U,                              /* cryIfKeyId                                   */
                                                                 0U,                              /* targetCryIfKeyId                             */
#else /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL  /* mode                                         */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                               };

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBCERTIFICATEPARSE,
                          CSM_E_UNINIT
                         );
  }
  else
  if (jobId >= CSM_JOB_COUNT)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00002,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBCERTIFICATEPARSE,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (Csm_JobConfigurations[jobId].jobPrimitiveInfo->primitiveInfo->service != CRYPTO_CERTIFICATEPARSE)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00003,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBCERTIFICATEPARSE,
                          CSM_E_SERVICE_NOT_IDENTICAL
                         );
  }
  else
  if (keyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBCERTIFICATEPARSE,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    {
      jobPrimitiveInputOutput.cryIfKeyId = keyId;

      result = Csm_Process(jobId, &jobPrimitiveInputOutput);
    }
  }

  return result;
}
#endif /* #if (CSM_API_ENABLED_SERVICE_JOBCERTIFICATEPARSE == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_JobCertificateVerify ----------------------------------------------------------------- */

/* !LINKSTO Csm.Asr.SWS_Csm_91034,1 */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_API_ENABLED_SERVICE_JOBCERTIFICATEVERIFY == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_JobCertificateVerify
(
        uint32                                             jobId,
        uint32                                             keyId,
        uint32                                             verifyKeyId,
  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_DATA) verifyPtr
)
{
  Std_ReturnType                     result                  = E_NOT_OK;
  Crypto_JobPrimitiveInputOutputType jobPrimitiveInputOutput = {
                                                                 NULL_PTR, 0U,                    /* inputPtr,           inputLength              */
                                                                 NULL_PTR, 0U,                    /* secondaryInputPtr,  secondaryInputLength     */
                                                                 NULL_PTR, 0U,                    /* tertiaryInputPtr,   tertiaryInputLength      */
                                                                 NULL_PTR, NULL_PTR,              /* outputPtr,          outputLengthPtr          */
                                                                 NULL_PTR, NULL_PTR,              /* secondaryOutputPtr, secondaryOutputLengthPtr */
#if (   (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_440) \
    )
                                                                 0U,                              /* input64                                      */
#endif /* #if (   (CSM_API_VERSION == CSM_API_VERSION_431) ... */
                                                                 NULL_PTR,                        /* verifyPtr                                    */
#if (CSM_API_VERSION != CSM_API_VERSION_EB)
                                                                 NULL_PTR,                        /* output64Ptr                                  */
#endif /* #if (CSM_API_VERSION != CSM_API_VERSION_EB) */
#if (CSM_API_VERSION == CSM_API_VERSION_440)
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL, /* mode                                         */
                                                                 0U,                              /* cryIfKeyId                                   */
                                                                 0U,                              /* targetCryIfKeyId                             */
#else /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                                 CRYPTO_OPERATIONMODE_SINGLECALL  /* mode                                         */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */
                                                               };

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBCERTIFICATEVERIFY,
                          CSM_E_UNINIT
                         );
  }
  else
  if (jobId >= CSM_JOB_COUNT)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00002,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBCERTIFICATEVERIFY,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (Csm_JobConfigurations[jobId].jobPrimitiveInfo->primitiveInfo->service != CRYPTO_CERTIFICATEVERIFY)
  {
    /* !LINKSTO CSM.Req.Gen/Det/00003,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBCERTIFICATEVERIFY,
                          CSM_E_SERVICE_NOT_IDENTICAL
                         );
  }
  else
  if (keyId >= CSM_KEY_COUNT)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBCERTIFICATEVERIFY,
                          CSM_E_PARAM_HANDLE
                         );
  }
  else
  if (verifyPtr == NULL_PTR)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_JOBCERTIFICATEVERIFY,
                          CSM_E_PARAM_POINTER
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    {
      jobPrimitiveInputOutput.cryIfKeyId       = keyId;
      jobPrimitiveInputOutput.targetCryIfKeyId = verifyKeyId;
      jobPrimitiveInputOutput.verifyPtr        = verifyPtr;

      result = Csm_Process(jobId, &jobPrimitiveInputOutput);
    }
  }

  return result;
}
#endif /* #if (CSM_API_ENABLED_SERVICE_JOBCERTIFICATEVERIFY == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

#if (CSM_PRT_COUNT == 0U)
/* --- Csm_AEADDecrypt_OAW (R0440) --------------------------------------------------------------- */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_AEADDECRYPT_OAW == STD_ON)
/* Deviation CODEMETRIC-3 */
/* Deviation MISRAC2012-2 */
FUNC(Std_ReturnType, CSM_CODE) Csm_AEADDecrypt_OAW
(
        uint32                                              jobId,
        Crypto_OperationModeType                            mode,
        Csm_ConstDataPtr                                    ciphertextBuffer,
        uint32                                              ciphertextLength,
        Csm_ConstDataPtr                                    associatedDataBuffer,
        uint32                                              associatedDataLength,
        Csm_ConstDataPtr                                    tagBuffer,
        uint32                                              tagLength,
        Csm_DataPtr                                         plaintextBuffer,
  P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) plaintextLength,
  P2VAR(Crypto_VerifyResultType,  AUTOMATIC, CSM_APPL_DATA) resultBuffer
)
{
  return Csm_AEADDecrypt(                                                             jobId,
                                                                                      mode,
                         (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) ciphertextBuffer,
                                                                                      ciphertextLength,
                         (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) associatedDataBuffer,
                                                                                      associatedDataLength,
                         (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) tagBuffer,
                                                                                      tagLength,
                         (  P2VAR(uint8,                   AUTOMATIC, CSM_APPL_DATA)) plaintextBuffer,
                                                                                      plaintextLength,
                                                                                      resultBuffer
                        );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_AEADDECRYPT_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_AEADDecrypt_OAW (R2011) --------------------------------------------------------------- */

#if (   (CSM_API_VERSION == CSM_API_VERSION_430) \
     || (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_EB ) \
    )
#if (CSM_RTE_ENABLED_SERVICE_AEADDECRYPT_OAW == STD_ON)
/* Deviation CODEMETRIC-3 */
/* Deviation MISRAC2012-2 */
FUNC(Std_ReturnType, CSM_CODE) Csm_AEADDecrypt_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  ConstVoidPtr             ciphertextPtr,
  uint32                   ciphertextLength,
  ConstVoidPtr             associatedDataPtr,
  uint32                   associatedDataLength,
  ConstVoidPtr             tagPtr,
  uint32                   tagLength,
  VoidPtr                  plaintextPtr,
  Csm_LengthPtr            plaintextLengthPtr,
  Csm_VerifyResultPtr      verifyPtr
)
{
  return Csm_AEADDecrypt(                                                             jobId,
                                                                                      mode,
                         (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) ciphertextPtr,
                                                                                      ciphertextLength,
                         (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) associatedDataPtr,
                                                                                      associatedDataLength,
                         (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) tagPtr,
                                                                                      tagLength,
                         (  P2VAR(uint8,                   AUTOMATIC, CSM_APPL_DATA)) plaintextPtr,
                                                                                      plaintextLengthPtr,
                         (  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_DATA)) verifyPtr
                        );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_AEADDECRYPT_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_430) ... */

/* --- Csm_AEADEncrypt_OAW (R0440) --------------------------------------------------------------- */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_AEADENCRYPT_OAW == STD_ON)
/* Deviation CODEMETRIC-4 */
/* Deviation MISRAC2012-2 */
FUNC(Std_ReturnType, CSM_CODE) Csm_AEADEncrypt_OAW
(
        uint32                                              jobId,
        Crypto_OperationModeType                            mode,
        Csm_ConstDataPtr                                    plaintextBuffer,
        uint32                                              plaintextLength,
        Csm_ConstDataPtr                                    associatedDataBuffer,
        uint32                                              associatedDataLength,
        Csm_DataPtr                                         ciphertextBuffer,
  P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) ciphertextLengthPtr,
        Csm_DataPtr                                         tagBuffer,
  P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) tagLength
)
{
  return Csm_AEADEncrypt(                                            jobId,
                                                                     mode,
                         (P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA)) plaintextBuffer,
                                                                     plaintextLength,
                         (P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA)) associatedDataBuffer,
                                                                     associatedDataLength,
                         (  P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA)) ciphertextBuffer,
                                                                     ciphertextLengthPtr,
                         (  P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA)) tagBuffer,
                                                                     tagLength
                        );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_AEADENCRYPT_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_AEADEncrypt_OAW (R2011) --------------------------------------------------------------- */

#if (   (CSM_API_VERSION == CSM_API_VERSION_430) \
     || (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_EB ) \
    )
#if (CSM_RTE_ENABLED_SERVICE_AEADENCRYPT_OAW == STD_ON)
/* Deviation CODEMETRIC-4 */
/* Deviation MISRAC2012-2 */
FUNC(Std_ReturnType, CSM_CODE) Csm_AEADEncrypt_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  ConstVoidPtr             plaintextPtr,
  uint32                   plaintextLength,
  ConstVoidPtr             associatedDataPtr,
  uint32                   associatedDataLength,
  VoidPtr                  ciphertextPtr,
  Csm_LengthPtr            ciphertextLengthPtr,
  VoidPtr                  tagPtr,
  Csm_LengthPtr            tagLengthPtr
)
{
  return Csm_AEADEncrypt(                                           jobId,
                                                                    mode,
                         (P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA)) plaintextPtr,
                                                                    plaintextLength,
                         (P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA)) associatedDataPtr,
                                                                    associatedDataLength,
                         (  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA)) ciphertextPtr,
                                                                    ciphertextLengthPtr,
                         (  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA)) tagPtr,
                                                                    tagLengthPtr
                        );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_AEADENCRYPT_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_430) ... */

/* --- Csm_CancelJob_OAW (R0440) ----------------------------------------------------------------- */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_GENERAL_OAW == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_CancelJob_OAW
(
  uint32                   job,
  Crypto_OperationModeType mode
)
{
  return Csm_CancelJob(job,
                       mode
                      );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_GENERAL_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_CancelJob_OAW (R2011) ----------------------------------------------------------------- */

#if (   (CSM_API_VERSION == CSM_API_VERSION_430) \
     || (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_EB ) \
    )
#if (CSM_RTE_ENABLED_SERVICE_GENERAL_OAW == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_CancelJob_OAW
(
  uint32                   job,
  Crypto_OperationModeType mode
)
{
  return Csm_CancelJob(job,
                       mode
                      );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_GENERAL_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_430) ... */

/* --- Csm_Decrypt_OAW (R0440) ------------------------------------------------------------------- */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_DECRYPT_OAW == STD_ON)
/* Deviation MISRAC2012-2 */
FUNC(Std_ReturnType, CSM_CODE) Csm_Decrypt_OAW
(
        uint32                                              jobId,
        Crypto_OperationModeType                            mode,
        Csm_ConstDataPtr                                    dataBuffer,
        uint32                                              dataLength,
        Csm_DataPtr                                         resultBuffer,
  P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) resultLength
)
{
  return Csm_Decrypt(                                            jobId,
                                                                 mode,
                     (P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA)) dataBuffer,
                                                                 dataLength,
                     (  P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA)) resultBuffer,
                                                                 resultLength
                    );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_DECRYPT_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_Decrypt_OAW (R2011) ------------------------------------------------------------------- */

#if (   (CSM_API_VERSION == CSM_API_VERSION_430) \
     || (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_EB ) \
    )
#if (CSM_RTE_ENABLED_SERVICE_DECRYPT_OAW == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_Decrypt_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  ConstVoidPtr             dataPtr,
  uint32                   dataLength,
  VoidPtr                  resultPtr,
  Csm_LengthPtr            resultLengthPtr
)
{
  return Csm_Decrypt(                                           jobId,
                                                                mode,
                     (P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA)) dataPtr,
                                                                dataLength,
                     (  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA)) resultPtr,
                                                                resultLengthPtr
                    );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_DECRYPT_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_430) ... */

/* --- Csm_Encrypt_OAW (R0440) ------------------------------------------------------------------- */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_ENCRYPT_OAW == STD_ON)
/* Deviation MISRAC2012-2 */
FUNC(Std_ReturnType, CSM_CODE) Csm_Encrypt_OAW
(
        uint32                                              jobId,
        Crypto_OperationModeType                            mode,
        Csm_ConstDataPtr                                    dataBuffer,
        uint32                                              dataLength,
        Csm_DataPtr                                         resultBuffer,
  P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) resultLength
)
{
  return Csm_Encrypt(                                            jobId,
                                                                 mode,
                     (P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA)) dataBuffer,
                                                                 dataLength,
                     (  P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA)) resultBuffer,
                                                                 resultLength
                    );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_ENCRYPT_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_Encrypt_OAW (R2011) ------------------------------------------------------------------- */

#if (   (CSM_API_VERSION == CSM_API_VERSION_430) \
     || (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_EB ) \
    )
#if (CSM_RTE_ENABLED_SERVICE_ENCRYPT_OAW == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_Encrypt_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  ConstVoidPtr             dataPtr,
  uint32                   dataLength,
  VoidPtr                  resultPtr,
  Csm_LengthPtr            resultLengthPtr
)
{
  return Csm_Encrypt(                                           jobId,
                                                                mode,
                     (P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA)) dataPtr,
                                                                dataLength,
                     (  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA)) resultPtr,
                                                                resultLengthPtr
                    );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_ENCRYPT_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_430) ... */

/* --- Csm_Hash_OAW (R0440) ---------------------------------------------------------------------- */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_HASH_OAW == STD_ON)
/* Deviation MISRAC2012-2 */
FUNC(Std_ReturnType, CSM_CODE) Csm_Hash_OAW
(
        uint32                                              jobId,
        Crypto_OperationModeType                            mode,
        Csm_ConstDataPtr                                    dataBuffer,
        uint32                                              dataLength,
        Csm_DataPtr                                         resultBuffer,
  P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) resultLength
)
{
  return Csm_Hash(                                            jobId,
                                                              mode,
                  (P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA)) dataBuffer,
                                                              dataLength,
                  (  P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA)) resultBuffer,
                                                              resultLength
                 );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_HASH_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_Hash_OAW (R2011) ---------------------------------------------------------------------- */

#if (   (CSM_API_VERSION == CSM_API_VERSION_430) \
     || (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_EB ) \
    )
#if (CSM_RTE_ENABLED_SERVICE_HASH_OAW == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_Hash_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  ConstVoidPtr             dataPtr,
  uint32                   dataLength,
  VoidPtr                  resultPtr,
  Csm_LengthPtr            resultLengthPtr
)
{
  return Csm_Hash(                                           jobId,
                                                             mode,
                  (P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA)) dataPtr,
                                                             dataLength,
                  (  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA)) resultPtr,
                                                             resultLengthPtr
                 );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_HASH_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_430) ... */

/* --- Csm_MacGenerate_OAW (R0440) --------------------------------------------------------------- */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_MACGENERATE_OAW == STD_ON)
/* Deviation MISRAC2012-2 */
FUNC(Std_ReturnType, CSM_CODE) Csm_MacGenerate_OAW
(
        uint32                                              jobId,
        Crypto_OperationModeType                            mode,
        Csm_ConstDataPtr                                    dataBuffer,
        uint32                                              dataLength,
        Csm_DataPtr                                         compareBuffer,
  P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) macLength
)
{
  return Csm_MacGenerate(                                            jobId,
                                                                     mode,
                         (P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA)) dataBuffer,
                                                                     dataLength,
                         (  P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA)) compareBuffer,
                                                                     macLength
                        );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_MACGENERATE_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_MacGenerate_OAW (R2011) --------------------------------------------------------------- */

#if (   (CSM_API_VERSION == CSM_API_VERSION_430) \
     || (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_EB ) \
    )
#if (CSM_RTE_ENABLED_SERVICE_MACGENERATE_OAW == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_MacGenerate_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  ConstVoidPtr             dataPtr,
  uint32                   dataLength,
  VoidPtr                  macPtr,
  Csm_LengthPtr            macLengthPtr
)
{
  return Csm_MacGenerate(                                           jobId,
                                                                    mode,
                         (P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA)) dataPtr,
                                                                    dataLength,
                         (  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA)) macPtr,
                                                                    macLengthPtr
                        );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_MACGENERATE_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_430) ... */

/* --- Csm_MacVerify_OAW (R0440) ----------------------------------------------------------------- */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_MACVERIFY_OAW == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_MacVerify_OAW
(
        uint32                                              jobId,
        Crypto_OperationModeType                            mode,
        Csm_ConstDataPtr                                    dataBuffer,
        uint32                                              dataLength,
        Csm_ConstDataPtr                                    compareBuffer,
        uint32                                              compareLength,
  P2VAR(Crypto_VerifyResultType,  AUTOMATIC, CSM_APPL_DATA) resultBuffer
)
{
  return Csm_MacVerify(                                                             jobId,
                                                                                    mode,
                       (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) dataBuffer,
                                                                                    dataLength,
                       (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) compareBuffer,
                                                                                    compareLength,
                                                                                    resultBuffer
                      );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_MACVERIFY_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_MacVerify_OAW (R2011) ----------------------------------------------------------------- */

#if (   (CSM_API_VERSION == CSM_API_VERSION_430) \
     || (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_EB ) \
    )
#if (CSM_RTE_ENABLED_SERVICE_MACVERIFY_OAW == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_MacVerify_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  ConstVoidPtr             dataPtr,
  uint32                   dataLength,
  ConstVoidPtr             macPtr,
  uint32                   macLength,
  Csm_VerifyResultPtr      verifyPtr
)
{
  return Csm_MacVerify(                                                             jobId,
                                                                                    mode,
                       (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) dataPtr,
                                                                                    dataLength,
                       (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) macPtr,
                                                                                    macLength,
                       (  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_DATA)) verifyPtr
                      );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_MACVERIFY_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_430) ... */

/* --- Csm_RandomGenerate_OAW (R0440) ------------------------------------------------------------ */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_RANDOMGENERATE_OAW == STD_ON)
/* Deviation MISRAC2012-2 */
FUNC(Std_ReturnType, CSM_CODE) Csm_RandomGenerate_OAW
(
        uint32                                              jobId,
        Crypto_OperationModeType                            mode,
        Csm_DataPtr                                         resultBuffer,
  P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) resultLength
)
{
  /* Deviation MISRAC2012-X <+1> */
  TS_PARAM_UNUSED(mode);

  return Csm_RandomGenerate(                                          jobId,
                            (P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA)) resultBuffer,
                                                                      resultLength
                           );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_RANDOMGENERATE_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_RandomGenerate_OAW (R2011) ------------------------------------------------------------ */

#if (   (CSM_API_VERSION == CSM_API_VERSION_430) \
     || (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_EB ) \
    )
#if (CSM_RTE_ENABLED_SERVICE_RANDOMGENERATE_OAW == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_RandomGenerate_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  VoidPtr                  resultPtr,
  Csm_LengthPtr            resultLengthPtr
)
{
  /* Deviation MISRAC2012-X <+1> */
  TS_PARAM_UNUSED(mode);

  return Csm_RandomGenerate(                                         jobId,
                            (P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA)) resultPtr,
                                                                     resultLengthPtr
                           );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_RANDOMGENERATE_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_430) ... */

/* --- Csm_SignatureGenerate_OAW (R0440) --------------------------------------------------------- */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_SIGNATUREGENERATE_OAW == STD_ON)
/* Deviation MISRAC2012-2 */
FUNC(Std_ReturnType, CSM_CODE) Csm_SignatureGenerate_OAW
(
        uint32                                              jobId,
        Crypto_OperationModeType                            mode,
        Csm_ConstDataPtr                                    dataBuffer,
        uint32                                              dataLength,
        Csm_DataPtr                                         resultBuffer,
  P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) resultLength
)
{
  return Csm_SignatureGenerate(                                            jobId,
                                                                           mode,
                               (P2CONST(uint8,  AUTOMATIC, CSM_APPL_DATA)) dataBuffer,
                                                                           dataLength,
                               (  P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA)) resultBuffer,
                                                                           resultLength
                              );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_SIGNATUREGENERATE_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_SignatureGenerate_OAW (R2011) --------------------------------------------------------- */

#if (   (CSM_API_VERSION == CSM_API_VERSION_430) \
     || (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_EB ) \
    )
#if (CSM_RTE_ENABLED_SERVICE_SIGNATUREGENERATE_OAW == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_SignatureGenerate_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  ConstVoidPtr             dataPtr,
  uint32                   dataLength,
  VoidPtr                  resultPtr,
  Csm_LengthPtr            resultLengthPtr
)
{
  return Csm_SignatureGenerate(                                           jobId,
                                                                          mode,
                               (P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA)) dataPtr,
                                                                          dataLength,
                               (  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA)) resultPtr,
                                                                          resultLengthPtr
                              );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_SIGNATUREGENERATE_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_430) ... */

/* --- Csm_SignatureVerify_OAW (R0440) ----------------------------------------------------------- */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_SIGNATUREVERIFY_OAW == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_SignatureVerify_OAW
(
        uint32                                              jobId,
        Crypto_OperationModeType                            mode,
        Csm_ConstDataPtr                                    dataBuffer,
        uint32                                              dataLength,
        Csm_ConstDataPtr                                    compareBuffer,
        uint32                                              compareLength,
  P2VAR(Crypto_VerifyResultType,  AUTOMATIC, CSM_APPL_DATA) resultBuffer
)
{
  return Csm_SignatureVerify(                                                             jobId,
                                                                                          mode,
                             (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) dataBuffer,
                                                                                          dataLength,
                             (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) compareBuffer,
                                                                                          compareLength,
                                                                                          resultBuffer
                            );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_SIGNATUREVERIFY_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_SignatureVerify_OAW (R2011) ----------------------------------------------------------- */

#if (   (CSM_API_VERSION == CSM_API_VERSION_430) \
     || (CSM_API_VERSION == CSM_API_VERSION_431) \
     || (CSM_API_VERSION == CSM_API_VERSION_EB ) \
    )
#if (CSM_RTE_ENABLED_SERVICE_SIGNATUREVERIFY_OAW == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_SignatureVerify_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  ConstVoidPtr             dataPtr,
  uint32                   dataLength,
  ConstVoidPtr             signaturePtr,
  uint32                   signatureLength,
  Csm_VerifyResultPtr      verifyPtr
)
{
  return Csm_SignatureVerify(                                                             jobId,
                                                                                          mode,
                             (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) dataPtr,
                                                                                          dataLength,
                             (P2CONST(uint8,                   AUTOMATIC, CSM_APPL_DATA)) signaturePtr,
                                                                                          signatureLength,
                             (  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_DATA)) verifyPtr
                            );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_SIGNATUREVERIFY_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_430) ... */

/* --- Csm_JobKeySetValid_OAW (R0440) ------------------------------------------------------------ */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_JOBKEYSETVALID_OAW == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeySetValid_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  uint32                   key
)
{
  /* Deviation MISRAC2012-X <+1> */
  TS_PARAM_UNUSED(mode);

  return Csm_JobKeySetValid(jobId,
                            key
                           );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_JOBKEYSETVALID_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_JobRandomSeed_OAW (R0440) ------------------------------------------------------------- */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_JOBRANDOMSEED_OAW == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_JobRandomSeed_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  uint32                   key,
  Csm_ConstDataPtr         seedBuffer,
  uint32                   seedLength
)
{
  /* Deviation MISRAC2012-X <+1> */
  TS_PARAM_UNUSED(mode);

  return Csm_JobRandomSeed(                                           jobId,
                                                                      key,
                           (P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA)) seedBuffer,
                                                                      seedLength
                          );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_JOBRANDOMSEED_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_JobKeyGenerate_OAW (R0440) ------------------------------------------------------------ */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_JOBKEYGENERATE_OAW == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyGenerate_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  uint32                   key
)
{
  /* Deviation MISRAC2012-X <+1> */
  TS_PARAM_UNUSED(mode);

  return Csm_JobKeyGenerate(jobId,
                            key
                           );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_JOBKEYGENERATE_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_JobKeyDerive_OAW (R0440) -------------------------------------------------------------- */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_JOBKEYDERIVE_OAW == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyDerive_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  uint32                   key,
  uint32                   targetKeyId
)
{
  /* Deviation MISRAC2012-X <+1> */
  TS_PARAM_UNUSED(mode);

  return Csm_JobKeyDerive(jobId,
                          key,
                          targetKeyId
                         );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_JOBKEYDERIVE_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_JobKeyExchangeCalcPubVal_OAW (R0440) -------------------------------------------------- */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCPUBVAL_OAW == STD_ON)
/* Deviation MISRAC2012-2 */
FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyExchangeCalcPubVal_OAW
(
        uint32                                              jobId,
        Crypto_OperationModeType                            mode,
        uint32                                              key,
        Csm_DataPtr                                         publicValueBuffer,
  P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) publicValueLength
)
{
  /* Deviation MISRAC2012-X <+1> */
  TS_PARAM_UNUSED(mode);

  return Csm_JobKeyExchangeCalcPubVal(                                          jobId,
                                                                                key,
                                      (P2VAR(uint8,  AUTOMATIC, CSM_APPL_DATA)) publicValueBuffer,
                                                                                publicValueLength
                                     );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCPUBVAL_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_JobKeyExchangeCalcSecret_OAW (R0440) -------------------------------------------------- */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCSECRET_OAW == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyExchangeCalcSecret_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  uint32                   key,
  Csm_ConstDataPtr         partnerPublicValueBuffer,
  uint32                   partnerPublicValueLength
)
{
  /* Deviation MISRAC2012-X <+1> */
  TS_PARAM_UNUSED(mode);

  return Csm_JobKeyExchangeCalcSecret(                                           jobId,
                                                                                 key,
                                      (P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA)) partnerPublicValueBuffer,
                                                                                 partnerPublicValueLength
                                     );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_JOBKEYEXCHANGECALCSECRET_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_JobCertificateParse_OAW (R0440) ------------------------------------------------------- */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEPARSE_OAW == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_JobCertificateParse_OAW
(
  uint32                   jobId,
  Crypto_OperationModeType mode,
  uint32                   key
)
{
  /* Deviation MISRAC2012-X <+1> */
  TS_PARAM_UNUSED(mode);

  return Csm_JobCertificateParse(jobId,
                                 key
                                );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEPARSE_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

/* --- Csm_JobCertificateVerify_OAW (R0440) ------------------------------------------------------ */

#if (CSM_API_VERSION == CSM_API_VERSION_440)
#if (CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEVERIFY_OAW == STD_ON)
FUNC(Std_ReturnType, CSM_CODE) Csm_JobCertificateVerify_OAW
(
        uint32                                              jobId,
        Crypto_OperationModeType                            mode,
        uint32                                              key,
        uint32                                              verifyKeyId,
  P2VAR(Crypto_VerifyResultType,  AUTOMATIC, CSM_APPL_DATA) resultBuffer
)
{
  /* Deviation MISRAC2012-X <+1> */
  TS_PARAM_UNUSED(mode);

  return Csm_JobCertificateVerify(                                                      jobId,
                                                                                        key,
                                                                                        verifyKeyId,
                                                                                        resultBuffer
                                 );
}
#endif /* #if (CSM_RTE_ENABLED_SERVICE_JOBCERTIFICATEVERIFY_OAW == STD_ON) */
#endif /* #if (CSM_API_VERSION == CSM_API_VERSION_440) */

#endif /* #if (CSM_PRT_COUNT == 0U) */

#define CSM_STOP_SEC_CODE
#include <Csm_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define CSM_START_SEC_CODE
#include <Csm_MemMap.h>

FUNC(Std_ReturnType, CSM_CODE) Csm_Process
(
  uint32 jobId,
  P2VAR(Crypto_JobPrimitiveInputOutputType, AUTOMATIC, CSM_APPL_DATA) jobPrimitiveInputOutput
)
{
  Std_ReturnType result = E_NOT_OK;
  boolean run = FALSE;

  /* !LINKSTO CSM.Dsn.Api/ExAreas/00001,1, CSM.Dsn.Api/ExAreas/00002,1 */
  SchM_Enter_Csm_SCHM_CSM_EXCLUSIVE_AREA_0();
  /* !LINKSTO CSM.Req.Api/Csm_Service/00003,1 */
  if (Csm_JobExtraData[jobId].csmLockFlag == FALSE)
  {
    Csm_JobExtraData[jobId].csmLockFlag = TRUE;
    run = TRUE;
  }
  SchM_Exit_Csm_SCHM_CSM_EXCLUSIVE_AREA_0();

  if (TRUE == run)
  {
    if ( (Csm_JobConfigurations[jobId].CSM_API_JOBSTATE                == CRYPTO_JOBSTATE_ACTIVE) &&
        ((jobPrimitiveInputOutput->mode & CRYPTO_OPERATIONMODE_START) != 0U                    )
      )
    {
      /* !LINKSTO SWS_Csm_00017,1 */
      result = CRYPTO_E_BUSY;
    }
    else
    if (Csm_JobConfigurations[jobId].CSM_API_JOBSTATE == CRYPTO_JOBSTATE_ACTIVE)
    {
      Csm_JobConfigurations[jobId].CSM_API_JOBPRIMITIVEINPUTOUTPUT = *jobPrimitiveInputOutput;
      /* !LINKSTO SWS_Csm_00506,1 */
      result = CryIf_ProcessJob(Csm_JobExtraCnfg[jobId].csmQueue->cryIfChannelId,
                                &(Csm_JobConfigurations[jobId])
                              );
    }
    else
    {
      if (Csm_JobConfigurations[jobId].jobPrimitiveInfo->processingType == CRYPTO_PROCESSING_ASYNC)
      {
        if ( ((jobPrimitiveInputOutput->mode & CRYPTO_OPERATIONMODE_START) != 0U) &&
             ((Csm_JobExtraData[jobId].csmQueueLevel == CSM_QL_NONE))
           )
        {
          if (Csm_JobExtraCnfg[jobId].csmQueue->currentSize
                >= Csm_JobExtraCnfg[jobId].csmQueue->maxSize
             )
          {
            result = CRYPTO_E_QUEUE_FULL;
          }
          else
          if (Csm_JobExtraCnfg[jobId].csmQueue->currentSize == 0U)
          {
            Csm_JobConfigurations[jobId].CSM_API_JOBPRIMITIVEINPUTOUTPUT = *jobPrimitiveInputOutput;
            /* !LINKSTO SWS_Csm_00506,1 */
            result = CryIf_ProcessJob(Csm_JobExtraCnfg[jobId].csmQueue->cryIfChannelId,
                                      &(Csm_JobConfigurations[jobId])
                                     );
            if (result == E_OK)
            {
              Csm_JobExtraData[jobId].csmQueueLevel = CSM_QL_CRYPTO;
            }
            else
            if ((result == CRYPTO_E_BUSY) || (result == CRYPTO_E_QUEUE_FULL))
            {
              /* !LINKSTO CSM.Dsn.Api/ExAreas/00001,1, CSM.Dsn.Api/ExAreas/00002,1 */
              SchM_Enter_Csm_SCHM_CSM_EXCLUSIVE_AREA_0();
              /* !LINKSTO CSM.Req.Gen/Queueing/00001,1 */
              result = Csm_QueuePushJob(Csm_JobExtraCnfg[jobId].csmQueue,
                                           &Csm_JobConfigurations[jobId]
                                          );
              /* CHECK: NOPARSE */
              /* Defensive programming - unreachable code.
               * 1. Csm_QueuePushJob never returns E_NOT_OK because it is ensured that no NULL_PTRs
               *    are passed.
               * 2. Csm_QueuePushJob never returns CRYPTO_E_QUEUE_FULL because this is already checked
               *    in the leading IF of the parental IF-ELSE structure.
               */
              if ( result == E_OK )
              /* CHECK: PARSE */
              {
                Csm_JobExtraData[jobId].csmQueueLevel = CSM_QL_CSM;
              }
              SchM_Exit_Csm_SCHM_CSM_EXCLUSIVE_AREA_0();
            }
            else
            {
              /* intentionally empty */
            }
          }
          else
          {
            Csm_JobConfigurations[jobId].CSM_API_JOBPRIMITIVEINPUTOUTPUT = *jobPrimitiveInputOutput;
            /* !LINKSTO CSM.Dsn.Api/ExAreas/00001,1, CSM.Dsn.Api/ExAreas/00002,1 */
            SchM_Enter_Csm_SCHM_CSM_EXCLUSIVE_AREA_0();
            /* !LINKSTO CSM.Req.Gen/Queueing/00001,1 */
            result = Csm_QueuePushJob(Csm_JobExtraCnfg[jobId].csmQueue,
                                        &Csm_JobConfigurations[jobId]
                                        );
            /* CHECK: NOPARSE */
            /* Defensive programming - unreachable code.
             * 1. Csm_QueuePushJob never returns E_NOT_OK because it is ensured that no NULL_PTRs
             *    are passed.
             * 2. Csm_QueuePushJob never returns CRYPTO_E_QUEUE_FULL because this is already checked
             *    in the leading IF of this IF-ELSE structure.
             */
            if (result == E_OK)
            /* CHECK: PARSE */
            {
              Csm_JobExtraData[jobId].csmQueueLevel = CSM_QL_CSM;
            }
            SchM_Exit_Csm_SCHM_CSM_EXCLUSIVE_AREA_0();
          }
        }
        else
        if ( ((jobPrimitiveInputOutput->mode & CRYPTO_OPERATIONMODE_START) == 0U) &&
             ((Csm_JobExtraData[jobId].csmQueueLevel != CSM_QL_NONE))
           )
        {
          /* !LINKSTO CSM.Req.Gen/Queueing/00004,1 */
          result = CRYPTO_E_BUSY;
        }
        else
        {
          /* !LINKSTO CSM.Req.Gen/Queueing/00002,1 */
          /* intentionally empty */
        }
      }
      else
      {
        if ((Csm_JobExtraCnfg[jobId].csmQueue->head == NULL_PTR) ||
            (Csm_JobConfigurations[jobId].jobInfo->jobPriority
              > Csm_JobExtraCnfg[jobId].csmQueue->head->job->jobInfo->jobPriority
            )
          )
        {
          /* !LINKSTO SWS_Csm_00037,1 */
          Csm_JobExtraCnfg[jobId].csmQueue->lockMainQueueDelJob = TRUE;
          Csm_JobConfigurations[jobId].CSM_API_JOBPRIMITIVEINPUTOUTPUT = *jobPrimitiveInputOutput;
          /* !LINKSTO SWS_Csm_00506,1 */
          result = CryIf_ProcessJob(Csm_JobExtraCnfg[jobId].csmQueue->cryIfChannelId,
                                    &(Csm_JobConfigurations[jobId])
                                  );
        }
        else
        {
          /* !LINKSTO SWS_Csm_91007,1 */
          result = CRYPTO_E_BUSY;
        }
      }
    }
    /* !LINKSTO CSM.Dsn.Api/ExAreas/00001,1, CSM.Dsn.Api/ExAreas/00002,1 */
    SchM_Enter_Csm_SCHM_CSM_EXCLUSIVE_AREA_0();
    /* !LINKSTO CSM.Req.Api/Csm_Service/00004,1 */
    Csm_JobExtraData[jobId].csmLockFlag = FALSE;
    SchM_Exit_Csm_SCHM_CSM_EXCLUSIVE_AREA_0();
  }
  else
  {
    /* !LINKSTO CSM.Req.Api/Csm_Service/00003,1 */
    result = CRYPTO_E_BUSY;
  }

  return result;
}

#define CSM_STOP_SEC_CODE
#include <Csm_MemMap.h>

/*==================[end of file]=================================================================*/

