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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx.c/0001,1 */

/*==================[deviations]==================================================================*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 13.5 (required)
 * The right hand operand of a logical && or || operator shall not contain persistent side effects.
 *
 * Reason:
 * Changing the order would increase the runtime in this case which is not acceptable.
 * The side effect can be tolerated in this case.
 */

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * False positive from the tasking compiler.
 *
 * TASKING-2) Deviated Rule: W549
 * W549: condition is always false
 *
 * Reason:
 * False positive from the tasking compiler.
 */

/* Code-Metric Deviation List
 *
 * CODEMETRIC-1) Deviated Rule: HIS_LEVEL
 * not 14 <= 12
 *
 * Reason:
 * The function consists of many DET checks which increase the metric.
 * Improving this software quality metric would adversely effect the performance.
 *
 * CODEMETRIC-2) Deviated Rule: HIS_V(G)
 * not 24 <= 20
 *
 * CODEMETRIC-3) Deviated Rule: HIS_V(G)
 * not 25 <= 20
 *
 * Reason:
 * Improving this software quality metric would adversely effect the performance of the primitives.
 */

/*==================[includes]====================================================================*/

#include <CryIf_Cbk.h>             /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx.c/0003,1 */
#include <Crypto_xVIx_xAIx.h>      /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx.c/0002,1 */
#include <Crypto_xVIx_xAIx_Int.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx.c/0004,1 */

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[internal function declarations]==============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  Check for valid Csm job operation mode.
 **
 ** Check if the operation mode of a job is valid.
 **
 ** \param[in]  job  Pointer to the Csm job whose operation mode shall be checked if it is valid.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      If the operation mode of the given job is valid.
 ** \retval  E_NOT_OK  If the operation mode of the given job is invalid.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CheckJobMode
(
  P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job
);

/** \brief  Check for valid Csm job argument pointers.
 **
 ** Check if the Csm job primitive input and output pointers related to the primitive
 ** of the Csm job are not NULL_PTR.
 **
 ** \param[in]  objectId  Numeric identifier of the CDO to check for a matching primitive.
 ** \param[in]  job       Pointer to the Csm job whose input and output pointers shall be checkeded.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      If the pointers are valid.
 ** \retval  E_NOT_OK  If the pointers are invalid.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CheckJobRequiredPointers
(
          uint32                                                 objectId,
  P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job
);

/** \brief  Check for valid Csm job argument lengths.
 **
 ** Check if the Csm job primitive input and output lengths related to the primitive
 ** of the Csm job are not NULL (primitive data type) or not NULL_PTR and not NULL (pointer to
 ** primitive data type).
 **
 ** \param[in]  objectId  Numeric identifier of the CDO to check for a matching primitive.
 ** \param[in]  job       Pointer to the Csm job whose input and output lengths shall be checkeded.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      If the lengths are valid.
 ** \retval  E_NOT_OK  If the lengths are invalid.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CheckJobRequiredLengths
(
          uint32                                                 objectId,
  P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job
);

/** \brief  Check for whether a key is necessary for the primitive of a job or not.
 **
 ** \param[in]  job  Pointer to the Csm job whose primitive shall be cheked if a key
 **                  is needed or not.
 **
 ** \returns  Error value.
 **
 ** \retval  TRUE   Key is necessary.
 ** \retval  FALSE  No key is necessay.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
/* !LINKSTO Crypto.Dsn.Gen/KMn_GenerationPhase/0001,2 */
#if (CRYPTO_XVIX_XAIX_KEYMNGMT_ENABLED == STD_ON)
static FUNC(boolean, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_IsKeyNecessary
(
  P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job
);
#endif /* #if (CRYPTO_XVIX_XAIX_KEYMNGMT_ENABLED == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal constants]==========================================================*/

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_VAR_INIT_8
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  Variable indicating whether the crypto driver has been initialized **/
/* !LINKSTO Crypto.Dsn.Api/Data/Crypto_xVIx_xAIx_Initialized/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
VAR(boolean, CRYPTO_xVIx_xAIx_VAR) Crypto_xVIx_xAIx_Initialized = FALSE;
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_VAR_INIT_8
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*---Crypto_xVIx_xAIx_Init------------------------------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/SWS_Crypto_91000/0001,1 */

FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Init
(
  void
)
{
  uint32         i                               = 0U;
  uint32         j                               = 0U;
#if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_GETDATA == STD_ON)
  uint32         persistentKeyElementsReadErrors = 0U;
  uint32         retLength                       = 0U;
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_GETDATA == STD_ON) */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_GETVALID == STD_ON)
  Std_ReturnType result                          = E_NOT_OK;
  boolean        validState                      = FALSE;
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_GETVALID == STD_ON) */
  boolean        errorVal                        = FALSE;

#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
  Crypto_xVIx_xAIx_Initialized = FALSE;
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */

  DBG_CRYPTO_XVIX_XAIX_INIT_ENTRY();

/* iterate over keys and the key elements */
/* !LINKSTO Crypto.Dsn.Gen/KMn_GenerationPhase/0002,2 */
#if (CRYPTO_XVIX_XAIX_KEYMNGMT_ENABLED == STD_ON)
  /* Deviation TASKING-1 */
  for (i = 0U; i < CRYPTO_XVIX_XAIX_KEY_COUNT; i++)
  {
    Crypto_xVIx_xAIx_Keys[i].data->keyState = CRYPTO_XVIX_XAIX_KEYSTATE_INVALID;
  }
  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Init/0004,1 */
  /* Deviation TASKING-1 */
  for (i = 0U; i < CRYPTO_XVIX_XAIX_KEY_COUNT; i++)
  {
#if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_GETDATA == STD_ON)
    persistentKeyElementsReadErrors = 0U;
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_GETDATA == STD_ON) */
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Init/0004,1 */
    for (j = 0U; j < Crypto_xVIx_xAIx_Keys[i].cnfg->keyElementsCount; j++)
    {
#if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_GETDATA == STD_ON)
      result = E_NOT_OK;
      /* if key element is persistent, get its data via callout */
      if (TRUE == Crypto_xVIx_xAIx_Keys[i].cnfg->keyElements[j].cnfg->description->persistent)
      {
        retLength = Crypto_xVIx_xAIx_Keys[i].cnfg->keyElements[j].cnfg->description->maxSize;
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Init/0006,1 */
        result = Crypto_xVIx_xAIx_KeyElement_GetData(i,
                                                     Crypto_xVIx_xAIx_Keys[i].cnfg->keyElements[j].cnfg->description->id,
                                                     Crypto_xVIx_xAIx_Keys[i].cnfg->keyElements[j].data->data,
                                                     &retLength
                                                    );

        /* if getting data failed, incremet counter */
        if (    (E_OK != result)
             || (Crypto_xVIx_xAIx_Keys[i].cnfg->keyElements[j].cnfg->description->maxSize != retLength)
           )
        {
          persistentKeyElementsReadErrors++;
        }
      }

      /* if if getting data of persistent key element failed OR key element is not
      * persistent, initialize with init value
      */
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Init/0007,1 */
      if (E_OK != result)
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_GETDATA == STD_ON) */
      {
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Init/0005,1 */
        TS_MemCpy(Crypto_xVIx_xAIx_Keys[i].cnfg->keyElements[j].data->data,
                  Crypto_xVIx_xAIx_Keys[i].cnfg->keyElements[j].cnfg->description->initValue,
                  Crypto_xVIx_xAIx_Keys[i].cnfg->keyElements[j].cnfg->description->maxSize
                 );
        Crypto_xVIx_xAIx_Keys[i].cnfg->keyElements[j].data->writeLock = FALSE;
      }
    }
/* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Init/0008,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_GETVALID == STD_ON)
    if (0U != Crypto_xVIx_xAIx_Keys[i].cnfg->persistentKeyElementsCount)
    {
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Init/0009,1 */
        result = Crypto_xVIx_xAIx_Key_GetValid(i, &validState);

        /* CHECK: NOPARSE
         * The else path in this check is never reached as the macro
         * CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_GETDATA is enabled at together with
         * CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_GETVALID.
         */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_GETDATA == STD_ON)
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Init/0010,1 */
      if (    (0U    == persistentKeyElementsReadErrors)
           && (E_OK == result                         )
           && (TRUE == validState                     )
         )
#else /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_GETDATA == STD_ON) */
      if (   (E_OK == result    )
          && (TRUE == validState)
         )
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_GETVALID == STD_ON) */
      {
        Crypto_xVIx_xAIx_Keys[i].data->keyState = CRYPTO_XVIX_XAIX_KEYSTATE_VALID;
      }
      /* CHECK: PARSE */

    }
    else
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_GETVALID == STD_ON) */
    {
      Crypto_xVIx_xAIx_Keys[i].data->keyState = CRYPTO_XVIX_XAIX_KEYSTATE_VALID;
    }
  }
#endif /* #if (CRYPTO_XVIX_XAIX_KEYMNGMT_ENABLED == STD_ON) */
  /* Initialize Driver Objects */
  /* Deviation TASKING-1 */
  for (i = 0U; i < CRYPTO_XVIX_XAIX_CDO_COUNT; i++)
  {
    /* !!!
    * this IF checks if CDOCP and CDOCJ are NULL and if CDOCS is IDLE
    * if not, the FOR loop is interrupted and Crypto_xVIx_xAIx_Initialized
    * will not be set to TRUE
    * !!!
    */
    if (   (NULL_PTR                       != CRYPTO_XVIX_XAIX_CDOCP(i))
        || (NULL_PTR                       != CRYPTO_XVIX_XAIX_CDOCJ(i))
        || (CRYPTO_XVIX_XAIX_CDOSTATE_IDLE != CRYPTO_XVIX_XAIX_CDOCS(i))
       )
    {
      errorVal = TRUE;
      break;
    }
  }
  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Init/0001,1 */
  if (FALSE == errorVal)
  {
    /* Deviation TASKING-1 */
    for (i = 0U; i < CRYPTO_XVIX_XAIX_CDO_COUNT; i++)
    {
      /* !!!
      * this resets CDOCP and CDOCJ to NULL and if CDOCS to IDLE only if
      * the IF above was never failed, means if no CDOCP, CDOCJ was not NULL etc.
      * so this will only set the values to NULL, if there were NULL before, etc.
      * !!!
      */
      CRYPTO_XVIX_XAIX_CDOCP(i) = NULL_PTR;
      CRYPTO_XVIX_XAIX_CDOCJ(i) = NULL_PTR;
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00019,1 */
      CRYPTO_XVIX_XAIX_CDOCS(i) = CRYPTO_XVIX_XAIX_CDOSTATE_IDLE;
      for (j = 0U; j < Crypto_xVIx_xAIx_CDOs[i].cnfg->primitiveListLength; j++)
      {
        CRYPTO_XVIX_XAIX_CDOPL(i, j).data->P1 = NULL_PTR;
      }
    }
#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Init/0003,1 */
    Crypto_xVIx_xAIx_Initialized = TRUE;
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
  }

#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
  /* CHECK: NOPARSE
   * Defensive Programming - unreachable code.
   */
  if (!Crypto_xVIx_xAIx_Initialized)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00045,2 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_INIT,
                           CRYPTO_XVIX_XAIX_E_INIT_FAILED
                          );
  }
  /* CHECK: PARSE */
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */

  DBG_CRYPTO_XVIX_XAIX_INIT_EXIT();
}

/*---Crypto_xVIx_xAIx_GetVersionInfo--------------------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/SWS_Crypto_91001/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_VERSIONINFO == STD_ON)
FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetVersionInfo
(
  P2VAR(Std_VersionInfoType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) versioninfo
)
{
  DBG_CRYPTO_XVIX_XAIX_GETVERSIONINFO_ENTRY(versioninfo);

#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (NULL_PTR == versioninfo)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00047,1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_GETVERSIONINFO,
                           CRYPTO_XVIX_XAIX_E_PARAM_POINTER
                          );
  }
  else
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* Copy version information to provided buffer */
    versioninfo->vendorID         = CRYPTO_XVIX_XAIX_VENDOR_ID;
    versioninfo->moduleID         = CRYPTO_XVIX_XAIX_MODULE_ID;
    versioninfo->sw_major_version = CRYPTO_XVIX_XAIX_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = CRYPTO_XVIX_XAIX_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = CRYPTO_XVIX_XAIX_SW_PATCH_VERSION;
  }

  DBG_CRYPTO_XVIX_XAIX_GETVERSIONINFO_EXIT(versioninfo);
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_VERSIONINFO == STD_ON) */

/*---Crypto_xVIx_xAIx_ProcessJob------------------------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/SWS_Crypto_91003/0001,1 */

/* Deviation CODEMETRIC-1, CODEMETRIC-2, CODEMETRIC-3 */
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ProcessJob
(
        uint32                                       objectId,
  P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job
)
{
          Std_ReturnType                                                            result        = E_NOT_OK;
          boolean                                                                   runProcessFcn = FALSE;
          boolean                                                                   runRestartFcn = FALSE;
          boolean                                                                   runResetFcn   = FALSE;
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitivePtr;
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) jobCurrent;
          Crypto_OperationModeType                                                  jobMode;

  DBG_CRYPTO_XVIX_XAIX_PROCESSJOB_ENTRY(objectId,job);

#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (FALSE == Crypto_xVIx_xAIx_Initialized)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00057,1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_PROCESSJOB,
                           CRYPTO_XVIX_XAIX_E_UNINIT
                          );
    result = E_NOT_OK;
  }
  else
  if (NULL_PTR == job)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00059,1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_PROCESSJOB,
                           CRYPTO_XVIX_XAIX_E_PARAM_POINTER
                          );
    result = E_NOT_OK;
  }
  else
  if (CRYPTO_XVIX_XAIX_CDO_COUNT <= objectId)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00058,1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_PROCESSJOB,
                           CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                          );
    result = E_NOT_OK;
  }
  else
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    primitivePtr = CRYPTO_XVIX_XAIX_CDOCP(objectId);
    jobCurrent   = CRYPTO_XVIX_XAIX_CDOCJ(objectId);
    jobMode      = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode;

    if (   (CRYPTO_RANDOMGENERATE           == CRYPTO_XVIX_XAIX_JOBPI(job)->service)
        && (CRYPTO_OPERATIONMODE_SINGLECALL != jobMode                             )
      )
    {
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_ProcessJob/0001,1 */
      job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode = CRYPTO_OPERATIONMODE_SINGLECALL;
      jobMode                                            = CRYPTO_OPERATIONMODE_SINGLECALL;
    }
#if (CRYPTO_XVIX_XAIX_KEYMNGMT_ENABLED == STD_ON)
    if (   (TRUE                       == Crypto_xVIx_xAIx_IsKeyNecessary(job))
        && (CRYPTO_XVIX_XAIX_KEY_COUNT <= job->cryptoKeyId                    )
       )
    {
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_ProcessJob/0006,1 */
      result = E_NOT_OK;
    }
    else
#endif /* #if (CRYPTO_XVIX_XAIX_KEYMNGMT_ENABLED == STD_ON) */
      /* Deviation MISRAC2012-1 <START>*/
    if (   (   (job      != jobCurrent)
      /* Deviation TASKING-2 */
            || (NULL_PTR == jobCurrent)
           )
        && (   (E_NOT_OK == Crypto_xVIx_xAIx_CheckJobService(objectId, job)                   )
            || (E_NOT_OK == Crypto_xVIx_xAIx_CheckJobPrimitive(objectId, job, &(primitivePtr)))
           )
       )
      /* Deviation MISRAC2012-1 <STOP>*/
    {
#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00064,1 */
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00067,1 */
      (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                             CRYPTO_XVIX_XAIX_INSTANCE_ID,
                             CRYPTO_XVIX_XAIX_SID_PROCESSJOB,
                             CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                            );
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
    }
    else
    if (E_NOT_OK == Crypto_xVIx_xAIx_CheckJobMode(job))
    {
#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00071,1 */
      (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                             CRYPTO_XVIX_XAIX_INSTANCE_ID,
                             CRYPTO_XVIX_XAIX_SID_PROCESSJOB,
                             CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                            );
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
      if (job == CRYPTO_XVIX_XAIX_CDOCJ(objectId))
      {
        runResetFcn = TRUE;
      }
    }
    else
    if (E_NOT_OK == Crypto_xVIx_xAIx_CheckJobRequiredPointers(objectId, job))
    {
#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00070,1, Crypto.Asr.SWS_Crypto_00071,1 */
      (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                             CRYPTO_XVIX_XAIX_INSTANCE_ID,
                             CRYPTO_XVIX_XAIX_SID_PROCESSJOB,
                             CRYPTO_XVIX_XAIX_E_PARAM_POINTER
                            );
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
      if (job == CRYPTO_XVIX_XAIX_CDOCJ(objectId))
      {
        runResetFcn = TRUE;
      }
    }
    else
    if (E_NOT_OK == Crypto_xVIx_xAIx_CheckJobRequiredLengths(objectId, job))
    {
#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00070,1, Crypto.Asr.SWS_Crypto_00071,1, Crypto.Asr.SWS_Crypto_00142,1 */
      (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                             CRYPTO_XVIX_XAIX_INSTANCE_ID,
                             CRYPTO_XVIX_XAIX_SID_PROCESSJOB,
                             CRYPTO_XVIX_XAIX_E_PARAM_VALUE
                            );
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
      if (job == CRYPTO_XVIX_XAIX_CDOCJ(objectId))
      {
        runResetFcn = TRUE;
      }
    }
/* !LINKSTO Crypto.Dsn.Gen/KMn_GenerationPhase/0002,2 */
#if (CRYPTO_XVIX_XAIX_KEYMNGMT_ENABLED == STD_ON)
    else
    if (   (TRUE                              == Crypto_xVIx_xAIx_IsKeyNecessary(job)                  )
        && (CRYPTO_XVIX_XAIX_KEYSTATE_INVALID == Crypto_xVIx_xAIx_Keys[job->cryptoKeyId].data->keyState)
       )
    {
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00039,1 */
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_ProcessJob/0002,1 */
      result = CRYPTO_E_KEY_NOT_VALID;
      if (job == jobCurrent)
      {
        runResetFcn = TRUE;
      }
    }
#endif /* #if (CRYPTO_XVIX_XAIX_KEYMNGMT_ENABLED == STD_ON) */
    else
    {
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00014,1 */
      if (   (CRYPTO_XVIX_XAIX_CDOSTATE_BUSY == CRYPTO_XVIX_XAIX_CDOCS(objectId)      )
          && (job                            != jobCurrent                            )
          && (CRYPTO_OPERATIONMODE_START     == (jobMode & CRYPTO_OPERATIONMODE_START))
         )
      {
        /* !LINKSTO Crypto.Asr.SWS_Crypto_00033,1 */
        /* !LINKSTO Crypto.Asr.SWS_Crypto_00034,2 */
        result = CRYPTO_E_BUSY;
      }
      else
      if (   (TRUE                       == CRYPTO_XVIX_XAIX_CDOCJIP(objectId)    )
          && (job                        == jobCurrent                            )
          && (CRYPTO_OPERATIONMODE_START != (jobMode & CRYPTO_OPERATIONMODE_START))
         )
      {
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_ProcessJob/0003,1 */
        runResetFcn = TRUE;
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_ProcessJob/0003,1 */
        result      = CRYPTO_E_BUSY;
      }
      else
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00117,1 */
      if (CRYPTO_XVIX_XAIX_CDOSTATE_IDLE == CRYPTO_XVIX_XAIX_CDOCS(objectId))
      {
        if (CRYPTO_OPERATIONMODE_START != (jobMode & CRYPTO_OPERATIONMODE_START))
        {
          /* !LINKSTO Crypto.Asr.SWS_Crypto_00118,1 */
          result = E_NOT_OK;
        }
        else
        {
          /* !LINKSTO Crypto.Asr.SWS_Crypto_00031,1 */
          CRYPTO_XVIX_XAIX_CDOCJ(objectId) = job;
          SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
          CRYPTO_XVIX_XAIX_CDOCP(objectId) = primitivePtr;
          SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
          runProcessFcn = TRUE;
        }
      }
      else
      {
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_ProcessJob/0005,1 */
        /* !LINKSTO Crypto.Asr.SWS_Crypto_00017,1 */
        if (CRYPTO_OPERATIONMODE_START == (jobMode & CRYPTO_OPERATIONMODE_START))
        {
          /* !LINKSTO Crypto.Asr.SWS_Crypto_00020,1 */
          /* !LINKSTO Crypto.Dsn.JobTransition.Finish2Start,1 */
          /* !LINKSTO Crypto.Dsn.JobTransition.Update2Start,1 */
          /* !LINKSTO Crypto.Dsn.JobTransition.Start2Start,1 */
          runRestartFcn = TRUE;
        }
        /* !LINKSTO Crypto.Asr.SWS_Crypto_00121,1 */
        runProcessFcn = TRUE;
      }
    }
    if (TRUE == runRestartFcn)
    {
      (void) CRYPTO_XVIX_XAIX_CDOCP(objectId)->cnfg->description->fcnRestart(objectId,
                                                                             job,
                                                                             CRYPTO_XVIX_XAIX_CDOCP(objectId)
                                                                            );
    }
    if (TRUE == runResetFcn)
    {
      (void) CRYPTO_XVIX_XAIX_CDOCP(objectId)->cnfg->description->fcnReset(objectId,
                                                                           job,
                                                                           CRYPTO_XVIX_XAIX_CDOCP(objectId)
                                                                          );
    }
    if (TRUE == runProcessFcn)
    {
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_ProcessJob/0004,1 */
      result = CRYPTO_XVIX_XAIX_CDOCP(objectId)->cnfg->description->fcnProcess(objectId,
                                                                               job,
                                                                               CRYPTO_XVIX_XAIX_CDOCP(objectId)
                                                                              );
    }
#if ((CRYPTO_XVIX_XAIX_API_ENABLED_DETRUNTIMECHECKS == STD_ON) && (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_431))
    if (CRYPTO_E_SMALL_BUFFER == result)
    {
        /* !LINKSTO Crypto.Asr.SWS_Crypto_00136,1 */
        (void) Det_ReportRuntimeError(CRYPTO_XVIX_XAIX_MODULE_ID,
                                      CRYPTO_XVIX_XAIX_INSTANCE_ID,
                                      CRYPTO_XVIX_XAIX_SID_PROCESSJOB,
                                      CRYPTO_XVIX_XAIX_E_RE_SMALL_BUFFER
                                     );
    }
#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
    /* CHECK: NOPARSE
     * Error value CRYPTO_E_COUNTER_OVERFLOW not yet implemented
     */
    else
    if (CRYPTO_E_COUNTER_OVERFLOW == result)
    {
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00137,1 */
      (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                             CRYPTO_XVIX_XAIX_INSTANCE_ID,
                             CRYPTO_XVIX_XAIX_SID_PROCESSJOB,
                             CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                            );
    }
    /* CHECK: PARSE */
    else
    {
      /* This else is needed by MISRA */
    }
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
#else /* #if ((CRYPTO_XVIX_XAIX_API_ENABLED_DETRUNTIMECHECKS == STD_ON) && (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_431)) */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
    if (CRYPTO_E_SMALL_BUFFER == result)
    {
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00136,1 */
      (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                             CRYPTO_XVIX_XAIX_INSTANCE_ID,
                             CRYPTO_XVIX_XAIX_SID_PROCESSJOB,
                             CRYPTO_E_SMALL_BUFFER
                            );
    }
    /* CHECK: NOPARSE
     * Error values not yet implemented
     */
    else
    if (CRYPTO_E_COUNTER_OVERFLOW == result)
    {
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00137,1 */
      (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                             CRYPTO_XVIX_XAIX_INSTANCE_ID,
                             CRYPTO_XVIX_XAIX_SID_PROCESSJOB,
                             CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                            );
    }
    /* CHECK: PARSE */
    else
    {
      /* This else is needed by MISRA */
    }
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
#endif /* #if ((CRYPTO_XVIX_XAIX_API_ENABLED_DETRUNTIMECHECKS == STD_ON) && (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_431)) */
  }

  DBG_CRYPTO_XVIX_XAIX_PROCESSJOB_EXIT(result,objectId,job);

  return result;
}

/*---Crypto_xVIx_xAIx_CancelJob-------------------------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/SWS_Crypto_00122/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CancelJob
(
          uint32                                                     objectId,
#if (    (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) \
      || (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_431) \
    )
    P2VAR(Crypto_JobInfoType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job
#else /* #if (   (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) ... */
    P2VAR(Crypto_JobType,     AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job
#endif /* #if (   (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) ... */
)
{
  Std_ReturnType result = E_NOT_OK;

  DBG_CRYPTO_XVIX_XAIX_CANCELJOB_ENTRY(objectId,job);

#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (FALSE == Crypto_xVIx_xAIx_Initialized)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00123,1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_CANCELJOB,
                           CRYPTO_XVIX_XAIX_E_UNINIT
                          );
  }
  else
  if (CRYPTO_XVIX_XAIX_CDO_COUNT <= objectId)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00124,1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_CANCELJOB,
                           CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                          );
  }
  else
  if (NULL_PTR == job)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00125,1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_CANCELJOB,
                           CRYPTO_XVIX_XAIX_E_PARAM_POINTER
                          );
  }
  else
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CancelJob/0001,1 */
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CancelJob/0002,1 */
#if (    (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) \
      || (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_431) \
    )
    if (   (CRYPTO_XVIX_XAIX_CDOSTATE_BUSY == CRYPTO_XVIX_XAIX_CDOCS(objectId)                )
        && (job->jobId                     == CRYPTO_XVIX_XAIX_CDOCJ(objectId)->jobInfo->jobId)
       )
    {
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00143,1 */
      result = CRYPTO_XVIX_XAIX_CDOCP(objectId)->cnfg->description->fcnCancel(objectId,
                                                                              CRYPTO_XVIX_XAIX_CDOCJ(objectId),
                                                                              CRYPTO_XVIX_XAIX_CDOCP(objectId)
                                                                             );
    }
#else /* #if (   (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) ... */
    if (   (CRYPTO_XVIX_XAIX_CDOSTATE_BUSY == CRYPTO_XVIX_XAIX_CDOCS(objectId))
        && (job                            == CRYPTO_XVIX_XAIX_CDOCJ(objectId))
       )
    {
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00143,1 */
      result = CRYPTO_XVIX_XAIX_CDOCP(objectId)->cnfg->description->fcnCancel(objectId,
                                                                              job,
                                                                              CRYPTO_XVIX_XAIX_CDOCP(objectId)
                                                                             );
    }
#endif /* #if (   (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) ... */
  }

  DBG_CRYPTO_XVIX_XAIX_CANCELJOB_EXIT(result,objectId,job);

  return result;
}

/*---Crypto_xVIx_xAIx_MainFunction----------------------------------------------------------------*/

#if CRYPTO_XVIX_XAIX_CRYPTO_MAIN_FUNCTION_EXISTS == STD_ON
/* !LINKSTO Crypto.Dsn.Api/Interfaces/SWS_Crypto_91012/0001,1 */
/* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_MainFunction/0001,1 */
FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_MainFunction
(
  void
)
{
  uint32 objectId = 0U;

  DBG_CRYPTO_XVIX_XAIX_MAINFUNCTION_ENTRY();

  /* Deviation TASKING-1 */
  for (objectId = 0U; objectId < CRYPTO_XVIX_XAIX_CDO_COUNT; objectId++)
  {
    if (   (CRYPTO_XVIX_XAIX_CDOSTATE_BUSY == CRYPTO_XVIX_XAIX_CDOCS(objectId)                                  )
        && (CRYPTO_PROCESSING_ASYNC        == CRYPTO_XVIX_XAIX_CDOCJ(objectId)->jobPrimitiveInfo->processingType)
       )
    {
      (void) CRYPTO_XVIX_XAIX_CDOCP(objectId)->cnfg->description->fcnMain(objectId,
                                                                          CRYPTO_XVIX_XAIX_CDOCJ(objectId),
                                                                          CRYPTO_XVIX_XAIX_CDOCP(objectId)
                                                                         );
    }
  }

  DBG_CRYPTO_XVIX_XAIX_MAINFUNCTION_EXIT();
}
#endif /* CRYPTO_XVIX_XAIX_CRYPTO_MAIN_FUNCTION_EXISTS == STD_ON */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*---Crypto_xVIx_xAIx_CheckJobMode----------------------------------------------------------------*/

static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CheckJobMode
(
  P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job
)
{
  Std_ReturnType           result  = E_NOT_OK;
  Crypto_ServiceInfoType   jobSrvc = CRYPTO_XVIX_XAIX_JOBPI(job)->service;
  Crypto_OperationModeType jobMode = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode;

  if (   (    (CRYPTO_HASH                == jobSrvc)
          ||  (CRYPTO_MACGENERATE         == jobSrvc)
          ||  (CRYPTO_MACVERIFY           == jobSrvc)
          ||  (CRYPTO_ENCRYPT             == jobSrvc)
          ||  (CRYPTO_DECRYPT             == jobSrvc)
          ||  (CRYPTO_AEADENCRYPT         == jobSrvc)
          ||  (CRYPTO_AEADDECRYPT         == jobSrvc)
          ||  (CRYPTO_SIGNATUREGENERATE   == jobSrvc)
          ||  (CRYPTO_SIGNATUREVERIFY     == jobSrvc)
          || !(CRYPTO_SECCOUNTERINCREMENT == jobSrvc)
      /* Deviation TASKING-2 */
          || !(CRYPTO_SECCOUNTERREAD      == jobSrvc)
      /* Deviation TASKING-2 */
          || !(CRYPTO_RANDOMGENERATE      == jobSrvc)
         )
      && (   (CRYPTO_OPERATIONMODE_START       != (jobMode & CRYPTO_OPERATIONMODE_SINGLECALL))
          && (CRYPTO_OPERATIONMODE_UPDATE      != (jobMode & CRYPTO_OPERATIONMODE_SINGLECALL))
          && (CRYPTO_OPERATIONMODE_FINISH      != (jobMode & CRYPTO_OPERATIONMODE_SINGLECALL))
          && (CRYPTO_OPERATIONMODE_STREAMSTART != (jobMode & CRYPTO_OPERATIONMODE_SINGLECALL))
          && (CRYPTO_OPERATIONMODE_SINGLECALL  != (jobMode & CRYPTO_OPERATIONMODE_SINGLECALL))
         )
     )
  {
    result = E_NOT_OK;
  }
  else
  {
    result = E_OK;
  }

  return result;
}

/*---Crypto_xVIx_xAIx_CheckJobRequiredPointers----------------------------------------------------*/

static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CheckJobRequiredPointers
(
          uint32                                       objectId,
  P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job
)
{
  /* Here the defensive programming schema shall be ignored becasue the result variable shall then
     be minipulated many times before finding if the required pointers are set or not. This would
     make the code complexer and less readable.*/
  Std_ReturnType                     result  = E_NOT_OK;
  Crypto_ServiceInfoType             jobSrvc = CRYPTO_XVIX_XAIX_JOBPI(job)->service;
  Crypto_JobPrimitiveInputOutputType jobPio  = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT;

  TS_PARAM_UNUSED(objectId);
  result  = E_OK;
  if (   (   (CRYPTO_HASH              == jobSrvc)
          || (CRYPTO_MACGENERATE       == jobSrvc)
          || (CRYPTO_MACVERIFY         == jobSrvc)
          || (CRYPTO_ENCRYPT           == jobSrvc)
          || (CRYPTO_DECRYPT           == jobSrvc)
          || (CRYPTO_AEADENCRYPT       == jobSrvc)
          || (CRYPTO_AEADDECRYPT       == jobSrvc)
          || (CRYPTO_SIGNATUREGENERATE == jobSrvc)
          || (CRYPTO_SIGNATUREVERIFY   == jobSrvc)
         )
      && (CRYPTO_OPERATIONMODE_UPDATE == (jobPio.mode & CRYPTO_OPERATIONMODE_UPDATE))
      && (NULL_PTR                    == jobPio.inputPtr                            )
     )
  {
    result = E_NOT_OK;
  }
  if (   (   (CRYPTO_MACVERIFY       == jobSrvc)
          || (CRYPTO_AEADENCRYPT     == jobSrvc)
          || (CRYPTO_AEADDECRYPT     == jobSrvc)
          || (CRYPTO_SIGNATUREVERIFY == jobSrvc)
         )
      && (CRYPTO_OPERATIONMODE_FINISH == (jobPio.mode & CRYPTO_OPERATIONMODE_FINISH))
      && (NULL_PTR                    == jobPio.secondaryInputPtr                   )
     )
  {
    result = E_NOT_OK;
  }
  if (   (CRYPTO_AEADDECRYPT          == jobSrvc                                    )
      && (CRYPTO_OPERATIONMODE_FINISH == (jobPio.mode & CRYPTO_OPERATIONMODE_FINISH))
      && (NULL_PTR                    == jobPio.tertiaryInputPtr                    )
     )
  {
    result = E_NOT_OK;
  }
  if (   (   (CRYPTO_ENCRYPT     == jobSrvc)
          || (CRYPTO_DECRYPT     == jobSrvc)
          || (CRYPTO_AEADENCRYPT == jobSrvc)
          || (CRYPTO_AEADDECRYPT == jobSrvc)
         )
      && (CRYPTO_OPERATIONMODE_UPDATE == (jobPio.mode & CRYPTO_OPERATIONMODE_UPDATE))
      && (   (NULL_PTR                == jobPio.outputPtr                           )
          || (NULL_PTR                == jobPio.outputLengthPtr                     )
         )
     )
  {
    result = E_NOT_OK;
  }
  if (   (   (CRYPTO_HASH              == jobSrvc)
          || (CRYPTO_MACGENERATE       == jobSrvc)
          || (CRYPTO_ENCRYPT           == jobSrvc)
          || (CRYPTO_DECRYPT           == jobSrvc)
          || (CRYPTO_AEADENCRYPT       == jobSrvc)
          || (CRYPTO_AEADDECRYPT       == jobSrvc)
          || (CRYPTO_SIGNATUREGENERATE == jobSrvc)
          || (CRYPTO_RANDOMGENERATE    == jobSrvc)
         )
      && (CRYPTO_OPERATIONMODE_FINISH == (jobPio.mode & CRYPTO_OPERATIONMODE_FINISH))
      && (   (NULL_PTR                == jobPio.outputPtr                           )
          || (NULL_PTR                == jobPio.outputLengthPtr                     )
         )
     )
  {
    result = E_NOT_OK;
  }
  if (   (CRYPTO_AEADENCRYPT          == jobSrvc                                    )
      && (CRYPTO_OPERATIONMODE_FINISH == (jobPio.mode & CRYPTO_OPERATIONMODE_FINISH))
      && (   (NULL_PTR                == jobPio.secondaryOutputPtr                  )
          || (NULL_PTR                == jobPio.secondaryOutputLengthPtr            )
         )
     )
  {
    result = E_NOT_OK;
  }
  if (   (   (CRYPTO_MACVERIFY       == jobSrvc)
          || (CRYPTO_AEADDECRYPT     == jobSrvc)
          || (CRYPTO_SIGNATUREVERIFY == jobSrvc)
         )
      && (CRYPTO_OPERATIONMODE_FINISH == (jobPio.mode & CRYPTO_OPERATIONMODE_FINISH))
      && (NULL_PTR                    == jobPio.verifyPtr                           )
     )
  {
    result = E_NOT_OK;
  }

  return result;
}

/*---Crypto_xVIx_xAIx_CheckJobRequiredLengths-----------------------------------------------------*/

static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CheckJobRequiredLengths
(
          uint32                                       objectId,
  P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job
)
{
  /* Here the defensive programming schema shall be ignored becasue the result variable shall then
   be minipulated many times before finding if the required pointers are set or not. This would
   make the code complexer and less readable.*/
  Std_ReturnType                     result  = E_NOT_OK;
  Crypto_ServiceInfoType             jobSrvc = CRYPTO_XVIX_XAIX_JOBPI(job)->service;
  Crypto_JobPrimitiveInputOutputType jobPio  = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT;

  TS_PARAM_UNUSED(objectId);
  result  = E_OK;
  if (   (   (CRYPTO_HASH              == jobSrvc)
          || (CRYPTO_MACGENERATE       == jobSrvc)
          || (CRYPTO_MACVERIFY         == jobSrvc)
          || (CRYPTO_ENCRYPT           == jobSrvc)
          || (CRYPTO_DECRYPT           == jobSrvc)
          || (CRYPTO_AEADENCRYPT       == jobSrvc)
          || (CRYPTO_AEADDECRYPT       == jobSrvc)
          || (CRYPTO_SIGNATUREGENERATE == jobSrvc)
          || (CRYPTO_SIGNATUREVERIFY   == jobSrvc)
         )
      && (CRYPTO_OPERATIONMODE_UPDATE == (jobPio.mode & CRYPTO_OPERATIONMODE_UPDATE))
      && (0U                          == jobPio.inputLength                         )
     )
  {
    result = E_NOT_OK;
  }
  if (   (CRYPTO_AEADDECRYPT          == jobSrvc                                    )
      && (CRYPTO_OPERATIONMODE_FINISH == (jobPio.mode & CRYPTO_OPERATIONMODE_FINISH))
      && (0U                          == jobPio.tertiaryInputLength                 )
     )
  {
    result = E_NOT_OK;
  }
  if (   (   (CRYPTO_ENCRYPT     == jobSrvc)
          || (CRYPTO_DECRYPT     == jobSrvc)
          || (CRYPTO_AEADENCRYPT == jobSrvc)
          || (CRYPTO_AEADDECRYPT == jobSrvc)
         )
      && (CRYPTO_OPERATIONMODE_UPDATE == (jobPio.mode & CRYPTO_OPERATIONMODE_UPDATE))
      && (   (NULL_PTR                != jobPio.outputLengthPtr                     )
          && (0U                      == *(jobPio.outputLengthPtr)                  )
         )
     )
  {
    result = E_NOT_OK;
  }
  if (   (   (CRYPTO_HASH              == jobSrvc)
          || (CRYPTO_MACGENERATE       == jobSrvc)
          || (CRYPTO_ENCRYPT           == jobSrvc)
          || (CRYPTO_DECRYPT           == jobSrvc)
          || (CRYPTO_AEADENCRYPT       == jobSrvc)
          || (CRYPTO_AEADDECRYPT       == jobSrvc)
          || (CRYPTO_SIGNATUREGENERATE == jobSrvc)
          || (CRYPTO_RANDOMGENERATE    == jobSrvc)
         )
      && (CRYPTO_OPERATIONMODE_FINISH == (jobPio.mode & CRYPTO_OPERATIONMODE_FINISH))
      && (   (NULL_PTR                != jobPio.outputLengthPtr                     )
          && (0U                      == *(jobPio.outputLengthPtr)                  )
         )
     )
  {
    result = E_NOT_OK;
  }
  if (   (CRYPTO_AEADENCRYPT          == jobSrvc                                    )
      && (CRYPTO_OPERATIONMODE_FINISH == (jobPio.mode & CRYPTO_OPERATIONMODE_FINISH))
      && (   (NULL_PTR                != jobPio.secondaryOutputLengthPtr            )
          && (0U                      == *(jobPio.secondaryOutputLengthPtr)         )
         )
     )
  {
    result = E_NOT_OK;
  }

  return result;
}

/*---Crypto_xVIx_xAIx_IsKeyNecessary--------------------------------------------------------------*/
/* !LINKSTO Crypto.Dsn.Gen/KMn_GenerationPhase/0001,2 */
#if (CRYPTO_XVIX_XAIX_KEYMNGMT_ENABLED == STD_ON)
static FUNC(boolean, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_IsKeyNecessary
(
  P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job
)
{
  boolean                result = TRUE;
  Crypto_ServiceInfoType jobSrvc = CRYPTO_XVIX_XAIX_JOBPI(job)->service;

  if (   (CRYPTO_HASH                == jobSrvc                                      )
      || (CRYPTO_SECCOUNTERINCREMENT == jobSrvc                                      )
      || (CRYPTO_SECCOUNTERREAD      == jobSrvc                                      )
      || (   (CRYPTO_RANDOMGENERATE  == jobSrvc                                      )
          && (CRYPTO_ALGOFAM_RNG     == CRYPTO_XVIX_XAIX_JOBPI(job)->algorithm.family)
         )
      || (   (CRYPTO_DECRYPT  == jobSrvc                                      )
          && (CRYPTO_ALGOFAM_LZSS     == CRYPTO_XVIX_XAIX_JOBPI(job)->algorithm.family)
         )
     )
  {
    result = FALSE;
  }

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_KEYMNGMT_ENABLED == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[end of file]=================================================================*/

