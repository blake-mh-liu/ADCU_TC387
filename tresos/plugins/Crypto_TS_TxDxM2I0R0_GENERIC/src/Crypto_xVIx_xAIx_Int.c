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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int.c/0001,1 */

/*==================[deviations]==================================================================*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 20.7 (required)
 * Expressions resulting from the expansion of macro parameters shall be
 * enclosed in parentheses.
 *
 * Reason:
 * The AUTOSAR compiler abstraction requires these definitions in this way
 * and the arguments cannot be enclosed in parentheses due to C syntax.
 *
 * MISRAC2012-2) Deviated Rule: 2.1 (required)
 * A project shall not contain unreachable code.
 *
 * Reason:
 * The given warnings at this point are false positives, as the macro itself is fully tested
 * for all possible paths of a ternary operator. But a given call of the macro will always go either
 * way of checking the length of the shift width.
 */

/*==================[includes]====================================================================*/

#include <CryIf_Cbk.h>             /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int.c/0002,1 */

#include <Crypto_xVIx_xAIx_Int.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int.c/0003,1 */

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[internal function declarations]==============================================*/

/*==================[internal constants]==========================================================*/

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*---Crypto_xVIx_xAIx_GetHashLen------------------------------------------------------- */

FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetHashLen
(
  uint8 secondaryfamily
)
{
  uint32 hashlen = 0U;

  switch(secondaryfamily)
  {
    case CRYPTO_ALGOFAM_SHA1:
    {
      hashlen = CRYPTO_XVIX_XAIX_INT_CPR_SHA1_HASHSIZE;
    }
    break;
    case CRYPTO_ALGOFAM_SHA2_224:
    case CRYPTO_ALGOFAM_SHA3_224:
    {
      hashlen = CRYPTO_XVIX_XAIX_INT_CPR_SHA224_HASHSIZE;
    }
    break;
    case CRYPTO_ALGOFAM_SHA2_256:
    case CRYPTO_ALGOFAM_SHA3_256:
    {
      hashlen = CRYPTO_XVIX_XAIX_INT_CPR_SHA256_HASHSIZE;
    }
    break;
    case CRYPTO_ALGOFAM_SHA2_384:
    case CRYPTO_ALGOFAM_SHA3_384:
    {
      hashlen = CRYPTO_XVIX_XAIX_INT_CPR_SHA384_HASHSIZE;
    }
    break;
    case CRYPTO_ALGOFAM_SHA2_512:
    case CRYPTO_ALGOFAM_SHA3_512:
    {
      hashlen = CRYPTO_XVIX_XAIX_INT_CPR_SHA512_HASHSIZE;
    }
    break;
    /* CHECK: NOPARSE */
    /* All the possible internal check necessary for the hash algorithm have been addressed before calling this function.*/
    default:
    {
      /* Nothing to do (MISRA) */
    }
    break;
    /* CHECK: PARSE */
  }
  return hashlen;
}

/*---Crypto_xVIx_xAIx_SetJobRunning-------------------------------------------------------------- */

/* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_SetJobRunning/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_SetJobRunning
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          boolean                                                                   value
)
{
  Std_ReturnType  result = E_NOT_OK;

  if (   (NULL_PTR != job                                                      )
      && (NULL_PTR != Crypto_xVIx_xAIx_CDOs[objectId].data->jobCurrent)
      && (NULL_PTR != primitive                                                )
     )
  {
    /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Job/0001,1 */
    SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
    if (job == Crypto_xVIx_xAIx_CDOs[objectId].data->jobCurrent)
    {
      Crypto_xVIx_xAIx_CDOs[objectId].data->jobCurrentIsProcessed = value;
      result                                                      = E_OK;
    }
    else
    if (primitive == Crypto_xVIx_xAIx_CDOs[objectId].data->primitiveCurrent->P2)
    {
      Crypto_xVIx_xAIx_CDOs[objectId].data->jobCurrentSecondaryIsProcessed = value;
      result                                                               = E_OK;
    }
    else
    if (primitive == Crypto_xVIx_xAIx_CDOs[objectId].data->primitiveCurrent->R1)
    {
      Crypto_xVIx_xAIx_CDOs[objectId].data->jobCurrentDefaultRandomIsProcessed = value;
      result                                                                   = E_OK;
    }
    else
    {
      /* empty by intent */
    }
    SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
  }

  return result;
}

/*---Crypto_xVIx_xAIx_GetJobRunning-------------------------------------------------------------- */

/* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_GetJobRunning/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetJobRunning
(
          uint32                                                                    objectId,
  P2CONST(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
    P2VAR(boolean,                           AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value
)
{
  Std_ReturnType result = E_NOT_OK;

  if (   (NULL_PTR != job                                             )
      && (NULL_PTR != Crypto_xVIx_xAIx_CDOs[objectId].data->jobCurrent)
      && (NULL_PTR != primitive                                       )
     )
  {
    /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Job/0001,1 */
    SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
    if (   (job       == Crypto_xVIx_xAIx_CDOs[objectId].data->jobCurrent      )
        && (primitive == Crypto_xVIx_xAIx_CDOs[objectId].data->primitiveCurrent)
       )
    {
      *value  = Crypto_xVIx_xAIx_CDOs[objectId].data->jobCurrentIsProcessed;
       result = E_OK;
    }
    else
    if (primitive == Crypto_xVIx_xAIx_CDOs[objectId].data->primitiveCurrent->P2)
    {
      *value  = Crypto_xVIx_xAIx_CDOs[objectId].data->jobCurrentSecondaryIsProcessed;
       result = E_OK;
    }
    else
    if (primitive == Crypto_xVIx_xAIx_CDOs[objectId].data->primitiveCurrent->R1)
    {
      *value  = Crypto_xVIx_xAIx_CDOs[objectId].data->jobCurrentDefaultRandomIsProcessed;
       result = E_OK;
    }
    else
    {
      /* empty by intent */
    }
    SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
  }
  else
  {
    *value = FALSE;
    result = E_OK;
  }

  return result;
}

/*--- Crypto_xVIx_xAIx_CallbackNotification_Start ----------------------------------------------- */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CallbackNotification_Start
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_OperationModeType                                                  smOperationDone,
          Std_ReturnType                                                            cbkResult,
          uint32                                                                    workspaceSize
)
{
          Crypto_OperationModeType                                                  jobMode = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode;
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) priCPr  = primitive->data->P1;
          Std_ReturnType                                                            result  = E_NOT_OK;

  TS_PARAM_UNUSED(workspaceSize);

  /* filter internal operation mode callbacks that shall not be visible to the application */
  if (   (E_OK == cbkResult)
      && (   (CRYPTO_OPERATIONMODE_SINGLECALL  == jobMode)
          || (CRYPTO_OPERATIONMODE_STREAMSTART == jobMode)
         )
     )
  {
    result = E_OK;
  }
  else
  {
    /* CHECK: NOPARSE
     * This condition will always be true as cbkResult is already checked before this function call
     * and the jobMode is set when the primitive starts executing and cannot be changed internally.
     */
    if (   (E_OK    == cbkResult      )
        && (jobMode == smOperationDone)
      )
    {
      result = Crypto_xVIx_xAIx_SetJobRunning(objectId, job, primitive, FALSE);
    }
    else
    {
      /* code */
    }
    /* CHECK: PARSE */

    /* CHECK: NOPARSE
     * The call to function Crypto_xVIx_xAIx_SetJobRunning() cannot fail since the parameters to this
     * function cannot be changed once the job is started.
     */
    if (E_OK == result)
    /* CHECK: PARSE */
    {
      /* check whether to call CryIf callback or primary primitive callback */
      if (NULL_PTR != priCPr)
      {
        result = priCPr->cnfg->description->fcnCallback(objectId,
                                                        job,
                                                        priCPr,
                                                        CRYPTO_XVIX_XAIX_CALLBACK_START,
                                                        cbkResult
                                                      );
      }
      else
      {
        if (CRYPTO_PROCESSING_ASYNC == job->jobPrimitiveInfo->processingType)
        {
          /* !LINKSTO Crypto.Asr.SWS_Crypto_00028,1 */
          CryIf_CallbackNotification(job, cbkResult);
        }

        result = E_OK;
      }
    }
  }

  return result;
}

/*--- Crypto_xVIx_xAIx_CallbackNotification_Update ---------------------------------------------- */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CallbackNotification_Update
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_OperationModeType                                                  smOperationDone,
          Std_ReturnType                                                            cbkResult,
          uint32                                                                    workspaceSize
)
{
          Crypto_OperationModeType                                                  jobMode = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode;
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) priCPr  = primitive->data->P1;
          Std_ReturnType                                                            result  = E_NOT_OK;

  TS_PARAM_UNUSED(workspaceSize);

  /* filter internal operation mode callbacks that shall not be visible to the application */
  if (   (E_OK                            == cbkResult)
      && (CRYPTO_OPERATIONMODE_SINGLECALL == jobMode  )
     )
  {
    result = E_OK;
  }
  else
  {
    /* CHECK: NOPARSE
     * This condition will always be true as cbkResult is already checked before this function call
     * and the jobMode is set when the primitive starts executing and cannot be changed internally.
     */
    if (   (E_OK    == cbkResult      )
        && (jobMode == smOperationDone)
      )
    {
      result = Crypto_xVIx_xAIx_SetJobRunning(objectId, job, primitive, FALSE);
    }
    else
    {
      /* code */
    }
    /* CHECK: PARSE */

    /* CHECK: NOPARSE
     * The call to function Crypto_xVIx_xAIx_SetJobRunning() cannot fail since the parameters to this
     * function cannot be changed once the job is started.
     */
    if (E_OK == result)
    /* CHECK: PARSE */
    {
      /* check whether to call CryIf callback or primary primitive callback */
      if (NULL_PTR != priCPr)
      {
        result = priCPr->cnfg->description->fcnCallback(objectId,
                                                        job,
                                                        priCPr,
                                                        CRYPTO_XVIX_XAIX_CALLBACK_UPDATE,
                                                        cbkResult
                                                      );
      }
      else
      {
        if (CRYPTO_PROCESSING_ASYNC == job->jobPrimitiveInfo->processingType)
        {
          /* !LINKSTO Crypto.Asr.SWS_Crypto_00028,1 */
          CryIf_CallbackNotification(job, cbkResult);
        }

        result = E_OK;
      }
    }
  }

  return result;
}

/*--- Crypto_xVIx_xAIx_CallbackNotification_Finish ---------------------------------------------- */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CallbackNotification_Finish
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_OperationModeType                                                  smOperationDone,
          Std_ReturnType                                                            cbkResult,
          uint32                                                                    workspaceSize
)
{
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) priCPr = primitive->data->P1;
          Std_ReturnType                                                            result = E_NOT_OK;

  result = Crypto_xVIx_xAIx_SetJobRunning(objectId, job, primitive, FALSE);

  /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/INITIAL_TO_CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1 */
  TS_MemBZero(primitive->cnfg->workspace, workspaceSize);

  if (NULL_PTR != priCPr)
  {
    result = priCPr->cnfg->description->fcnCallback(objectId,
                                                    job,
                                                    priCPr,
                                                    CRYPTO_XVIX_XAIX_CALLBACK_FINISH,
                                                    cbkResult
                                                   );
  }
  else
  {
    Crypto_xVIx_xAIx_CDOs[objectId].data->jobCurrent->CRYPTO_XVIX_XAIX_JOBSTATE = CRYPTO_JOBSTATE_ACTIVE;
    Crypto_xVIx_xAIx_CDOs[objectId].data->state                                 = CRYPTO_XVIX_XAIX_CDOSTATE_IDLE;
    /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Job/0001,1 */
    SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
    Crypto_xVIx_xAIx_CDOs[objectId].data->primitiveCurrent = NULL_PTR;
    SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
    Crypto_xVIx_xAIx_CDOs[objectId].data->jobCurrent       = NULL_PTR;

    if (CRYPTO_PROCESSING_ASYNC == job->jobPrimitiveInfo->processingType)
    {
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00028,1 */
      CryIf_CallbackNotification(job, cbkResult);
    }
  }

  primitive->data->P1            = NULL_PTR;
  job->CRYPTO_XVIX_XAIX_JOBSTATE = CRYPTO_JOBSTATE_IDLE;

  TS_PARAM_UNUSED(smOperationDone);

  return result;
}

/*--- Crypto_xVIx_xAIx_CallbackNotification_Cancel ---------------------------------------------- */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CallbackNotification_Cancel
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_OperationModeType                                                  smOperationDone,
          Std_ReturnType                                                            cbkResult,
          uint32                                                                    workspaceSize
)
{
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) priCPr = primitive->data->P1;
          Std_ReturnType                                                            result = E_NOT_OK;

  result = Crypto_xVIx_xAIx_SetJobRunning(objectId, job, primitive, FALSE);

  /* !LINKSTO Crypto.Asr.SWS_Crypto_00181_1,1 */
  /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/INITIAL_TO_CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1 */
  TS_MemBZero(primitive->cnfg->workspace, workspaceSize);

  if (NULL_PTR != priCPr)
  {
    result = priCPr->cnfg->description->fcnCallback(objectId,
                                                    job,
                                                    priCPr,
                                                    CRYPTO_XVIX_XAIX_CALLBACK_CANCEL,
                                                    cbkResult
                                                   );
  }
  else
  {
    Crypto_xVIx_xAIx_CDOs[objectId].data->jobCurrent->CRYPTO_XVIX_XAIX_JOBSTATE = CRYPTO_JOBSTATE_ACTIVE;
    Crypto_xVIx_xAIx_CDOs[objectId].data->state                                 = CRYPTO_XVIX_XAIX_CDOSTATE_IDLE;
    /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Job/0001,1 */
    SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
    Crypto_xVIx_xAIx_CDOs[objectId].data->primitiveCurrent = NULL_PTR;
    SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
    Crypto_xVIx_xAIx_CDOs[objectId].data->jobCurrent       = NULL_PTR;

    if (CRYPTO_PROCESSING_ASYNC == job->jobPrimitiveInfo->processingType)
    {
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00028,1 */
      CryIf_CallbackNotification(job, cbkResult);
    }
  }

  primitive->data->P1            = NULL_PTR;
  job->CRYPTO_XVIX_XAIX_JOBSTATE = CRYPTO_JOBSTATE_IDLE;

  TS_PARAM_UNUSED(smOperationDone);

  return result;
}

/*--- Crypto_xVIx_xAIx_CallbackNotification_Reset ----------------------------------------------- */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CallbackNotification_Reset
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_OperationModeType                                                  smOperationDone,
          Std_ReturnType                                                            cbkResult,
          uint32                                                                    workspaceSize
)
{
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) priCPr = primitive->data->P1;
          Std_ReturnType                                                            result = E_NOT_OK;

  /* check whether to call a secondary's reset function */
  if (NULL_PTR != primitive->P2)
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Reset/0003,1 */
    result = primitive->P2->cnfg->description->fcnReset(objectId, job, primitive->P2);
  }
  else
  {
    result = E_OK;
  }

  if (E_OK == result)
  {
    result = Crypto_xVIx_xAIx_SetJobRunning(objectId, job, primitive, FALSE);

    /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/INITIAL_TO_CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1 */
    TS_MemBZero(primitive->cnfg->workspace, workspaceSize);

    if (   (NULL_PTR != priCPr)
        && (E_OK     == result)
       )
    {
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Reset/0004,1 */
      result = priCPr->cnfg->description->fcnCallback(objectId,
                                                      job,
                                                      priCPr,
                                                      CRYPTO_XVIX_XAIX_CALLBACK_FINISH,
                                                      cbkResult
                                                     );
    }
    else
    {
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Reset/0005,1 */
      Crypto_xVIx_xAIx_CDOs[objectId].data->jobCurrent->CRYPTO_XVIX_XAIX_JOBSTATE = CRYPTO_JOBSTATE_ACTIVE;
      Crypto_xVIx_xAIx_CDOs[objectId].data->state                                 = CRYPTO_XVIX_XAIX_CDOSTATE_IDLE;
      /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Job/0001,1 */
      SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
      Crypto_xVIx_xAIx_CDOs[objectId].data->primitiveCurrent     = NULL_PTR;
      SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
      Crypto_xVIx_xAIx_CDOs[objectId].data->jobCurrent           = NULL_PTR;

      if (CRYPTO_PROCESSING_ASYNC == job->jobPrimitiveInfo->processingType)
      {
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Reset/0006,1 */
        /* !LINKSTO Crypto.Asr.SWS_Crypto_00028,1 */
        CryIf_CallbackNotification(job, cbkResult);
      }
    }
  }

  primitive->data->P1            = NULL_PTR;
  job->CRYPTO_XVIX_XAIX_JOBSTATE = CRYPTO_JOBSTATE_IDLE;

  TS_PARAM_UNUSED(smOperationDone);

  return result;
}

/*--- Crypto_xVIx_xAIx_CallbackNotification_Restart --------------------------------------------- */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CallbackNotification_Restart
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_OperationModeType                                                  smOperationDone,
          Std_ReturnType                                                            cbkResult,
          uint32                                                                    workspaceSize
)
{
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) priCPr = primitive->data->P1;
          Std_ReturnType                                                            result = E_NOT_OK;

  /* check whether to call a secondary's restart function */
  if (NULL_PTR != primitive->P2)
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Restart/0003,1 */
    result = primitive->P2->cnfg->description->fcnRestart(objectId, job, primitive->P2);
  }
  else
  {
    result = E_OK;
  }

  if (E_OK == result)
  {
    result = Crypto_xVIx_xAIx_SetJobRunning(objectId, job, primitive, FALSE);

    /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/INITIAL_TO_CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1 */
    TS_MemBZero(primitive->cnfg->workspace, workspaceSize);

    if (   (NULL_PTR != priCPr)
        && (E_OK     == result)
       )
    {
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Restart/0004,1 */
      result = priCPr->cnfg->description->fcnCallback(objectId,
                                                      job,
                                                      priCPr,
                                                      CRYPTO_XVIX_XAIX_CALLBACK_FINISH,
                                                      cbkResult
                                                      );
    }
  }

  TS_PARAM_UNUSED(smOperationDone);

  return result;
}

/*--- Crypto_xVIx_xAIx_CheckJobPrimitive -------------------------------------------------------- */

/* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CheckJobPrimitive/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CheckJobPrimitive
(
          uint32                                                                                                                    objectId,
  P2CONST(Crypto_JobType,                                                                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  /* Deviation MISRAC2012-1 */
    P2VAR(P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA), AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitivePtr
)
{
  Std_ReturnType result = E_NOT_OK;
  uint32         listId = 0U;

  *primitivePtr = NULL_PTR;

  for (listId = 0U; listId < Crypto_xVIx_xAIx_CDOs[objectId].cnfg->primitiveListLength; listId++)
  {
    if (   (   CRYPTO_XVIX_XAIX_CDOPL(objectId, listId).cnfg->description->service
            == CRYPTO_XVIX_XAIX_JOBPI(job)->service
           )
        && (   CRYPTO_XVIX_XAIX_CDOPL(objectId, listId).cnfg->description->family
            == CRYPTO_XVIX_XAIX_JOBPI(job)->algorithm.family
           )
        && (   CRYPTO_XVIX_XAIX_CDOPL(objectId, listId).cnfg->description->mode
            == CRYPTO_XVIX_XAIX_JOBPI(job)->algorithm.mode
           )
        && (   (CRYPTO_ALGOFAM_NOT_SET == CRYPTO_XVIX_XAIX_JOBPI(job)->algorithm.secondaryFamily)
            || (   CRYPTO_XVIX_XAIX_CDOPL(objectId, listId).P2->cnfg->description->family
                == CRYPTO_XVIX_XAIX_JOBPI(job)->algorithm.secondaryFamily
               )
            || (   (   (CRYPTO_DECRYPT == CRYPTO_XVIX_XAIX_JOBPI(job)->service)
                    || (CRYPTO_ENCRYPT == CRYPTO_XVIX_XAIX_JOBPI(job)->service)
                   )
                && (CRYPTO_ALGOMODE_CBC == CRYPTO_XVIX_XAIX_JOBPI(job)->algorithm.mode)
                && (   ((boolean) FALSE)
                    || (CRYPTO_ALGOFAM_PADDING_PKCS7 == CRYPTO_XVIX_XAIX_JOBPI(job)->algorithm.secondaryFamily)
                    || (CRYPTO_ALGOFAM_PADDING_TLS12 == CRYPTO_XVIX_XAIX_JOBPI(job)->algorithm.secondaryFamily)
                   )
               )
           )
       )
      {
        *primitivePtr = &(CRYPTO_XVIX_XAIX_CDOPL(objectId, listId));
         result       = E_OK;
        break;
      }
  }

  return result;
}

/*--- Crypto_xVIx_xAIx_CheckJobService ---------------------------------------------------------- */

/* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CheckJobService/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CheckJobService
(
          uint32                                       objectId,
  P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job
)
{
  Std_ReturnType result = E_NOT_OK;
  uint32         listId = 0U;

  for (listId = 0U; listId < Crypto_xVIx_xAIx_CDOs[objectId].cnfg->primitiveListLength; listId++)
  {
    if (   CRYPTO_XVIX_XAIX_CDOPL(objectId, listId).cnfg->description->service
        == CRYPTO_XVIX_XAIX_JOBPI(job)->service
       )
    {
      result = E_OK;
      break;
    }
  }

  return result;
}

/*--- Crypto_xVIx_xAIx_CommonXOR ---------------------------------------------------------------- */

/* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CommonXOR/0001,1 */

FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CommonXOR
(
    P2VAR(void, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) destination,
  P2CONST(void, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) source,
          uint32                             byteLength
)
{
  uint32_least len; /* internal length value */

  /* loop over the block length */
  for (len = 0U; len < byteLength; ++len)
  {
    /* XOR byte-wise */
    ((P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)) destination)[len]
    ^= ((P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)) source)[len];
  }
}

/*--- Crypto_xVIx_xAIx_ShiftBufUint8Left -------------------------------------------------------- */

/* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_ShiftBufUint8Left/0001,1 */

/*
 *  bufferPtr[0]         = most significant byte
 *  bufferPtr[bufferLen] = least significant byte
 */
FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_ShiftBufUint8Left
(
  P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) bufferPtr,
        uint32                              bufferLen,
        uint32                              count
)
{
  uint32 i          = 0U;
  uint32 shiftBytes = count / 8U;
  uint8  shiftBits  = count % 8U;

  if (shiftBytes >= bufferLen)
  {
    shiftBytes = bufferLen;
    shiftBits = 0U;
  }

  if (shiftBytes != 0U)
  {
    /* shift full bytes */
    for (i = 0U; i < (bufferLen - shiftBytes); i++)
    {
      bufferPtr[i] = bufferPtr[i + 1U];
    }

    TS_MemBZero(&(bufferPtr[bufferLen - shiftBytes]), shiftBytes);
  }

  if (shiftBits != 0U)
  {
    /* shift remaining bits */
    for (i = 0U; i < (bufferLen - shiftBytes - 1U); i++)
    {
      bufferPtr[i] =   (uint8) (bufferPtr[i] << shiftBits)
                     | (uint8) (bufferPtr[i + 1U] >> (8U - shiftBits));
    }
    bufferPtr[i] = (uint8) (bufferPtr[i] << shiftBits);
  }
}

/* --- Crypto_xVIx_xAIx_BufUint8ToBufUint32 ----------------------------------------------------- */

/* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_BufUint8ToBufUint32/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_BufUint8ToBufUint32
(
  P2VAR(uint8 , AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buf,
        uint32                               buflen
)
{
  Std_ReturnType result = E_NOT_OK;
  uint32         i      = 0U;
  uint32         v      = 0U;

  if ((buflen % sizeof(uint32)) == 0U)
  {
    for (i = 0U; i < buflen; i += sizeof(uint32))
    {
      /* CHECK: NOPARSE
       * This is a platform specific check and both paths cannot be covered on the same platform.
       */
#if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
      {
        v = (v << 8U) | buf[i + 3U];
        v = (v << 8U) | buf[i + 2U];
        v = (v << 8U) | buf[i + 1U];
        v = (v << 8U) | buf[i];
      }
#else /* (CPU_BYTE_ORDER == HIGH_BYTE_FIRST) */
      {
        v = (v << 8U) | buf[i];
        v = (v << 8U) | buf[i + 1U];
        v = (v << 8U) | buf[i + 2U];
        v = (v << 8U) | buf[i + 3U];
      }
#endif /* (CPU_BYTE_ORDER == HIGH_BYTE_FIRST) */
      /* CHECK: PARSE */
      TS_MemCpy(&(buf[i]), &v, sizeof(uint32));
    }
    result = E_OK;
  }

  return result;
}

/*--- Crypto_xVIx_xAIx_BufUint32ToBufUint8 ------------------------------------------------------ */

/* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_BufUint32ToBufUint8/0001,1 */

FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_BufUint32ToBufUint8
(
  P2VAR(uint32 , AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buf,
        uint32                                buflen
)
{
  uint32         i      = 0U;
  uint32         j      = 0U;
  uint32         v      = 0U;

  for (i = 0U; i < buflen; i++)
  {
    v = 0U;
    for (j = 0U; j < sizeof(uint32); j++)
    {
      v        = (v << 8U) | (buf[i] & 0xFFU);
      buf[i] >>= 8U;
    }
    TS_MemCpy(&(buf[i]), &v, sizeof(uint32));
  }
}

/*--- Crypto_xVIx_xAIx_BufUint8ToBufUint64 ------------------------------------------------------ */

/* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_BufUint8ToBufUint64/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_BufUint8ToBufUint64
(
  P2VAR(uint8 , AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buf,
        uint32                               buflen
)
{
  Std_ReturnType result = E_NOT_OK;
  uint32         i      = 0U;
  uint32         j      = 0U;
  uint64         t      = 0ULL;
  uint64         v      = 0ULL;

  if ((buflen % sizeof(uint64)) == 0U)
  {
    for (i = 0U; i < buflen; i += sizeof(uint64))
    {
      /* CHECK: NOPARSE
       * This is a platform specific check and both paths cannot be covered on the same platform.
       */
#if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
      {
        j = sizeof(uint64);
        do
        {
          j--;
          t = buf[i + j];
          /* Deviation MISRAC2012-2 */
          v = CRYPTO_XVIX_XAIX_OR64(CRYPTO_XVIX_XAIX_SHL64(v, 8U), t);
        }
        while (j != 0U);
      }
#else /* (CPU_BYTE_ORDER == HIGH_BYTE_FIRST) */
      {
        for (j = 0U; j < 8U; j++)
        {
          t = buf[i + j];
          /* Deviation MISRAC2012-2 */
          v = CRYPTO_XVIX_XAIX_OR64(CRYPTO_XVIX_XAIX_SHL64(v, 8U), t);
        }
      }
#endif /* (CPU_BYTE_ORDER == HIGH_BYTE_FIRST) */
      /* CHECK: PARSE */
      TS_MemCpy(&(buf[i]), &v, sizeof(uint64));
    }
    result = E_OK;
  }

  return result;
}

/*--- Crypto_xVIx_xAIx_BufUint64ToBufUint8 ------------------------------------------------------ */

/* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_BufUint64ToBufUint8/0001,1 */

FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_BufUint64ToBufUint8
(
  P2VAR(uint64, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buf,
        uint32                                         buflen
)
{
        uint32 i = 0U;
        uint32 j = 0U;
        uint64 v = 0ULL;
  const uint64 m  = 0x00000000000000FFULL;

  for (i = 0U; i < buflen; i++)
  {
    v = 0ULL;
    for (j = 0U; j < sizeof(uint64); j++)
    {
      /* Deviation MISRAC2012-2 <START> */
      v      = CRYPTO_XVIX_XAIX_OR64(CRYPTO_XVIX_XAIX_SHL64(v, 8U), CRYPTO_XVIX_XAIX_AND64(buf[i], m));
      buf[i] = CRYPTO_XVIX_XAIX_SHR64(buf[i], 8U);
      /* Deviation MISRAC2012-2 <STOP> */
    }
    TS_MemCpy(&(buf[i]), &v, sizeof(uint64));
  }
}

/*--- Crypto_xVIx_xAIx_MemCmp ------------------------------------------------------------------- */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_MemCmp
(
  P2CONST(void,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buf1,
  P2CONST(void,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buf2,
          uint32                                         len
)
{
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) b1 = (P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)) buf1;
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) b2 = (P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)) buf2;

  return TS_MemCmp(b1, b2, len);
}

/*--- Crypto_xVIx_xAIx_MemCmpSec ---------------------------------------------------------------- */

/* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_MemCmpSec/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_MemCmpSec
(
  P2CONST(void,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buf1,
  P2CONST(void,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buf2,
          uint32                                         len
)
{
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) b1 = (P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)) buf1;
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) b2 = (P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)) buf2;

  Std_ReturnType result = E_NOT_OK;
  uint8          cmpval = 0U;
  uint32         i      = 0U;

  for (i = 0U; i < len; i++)
  {
    cmpval |= (b1[i] ^ b2[i]);
  }

  if (0U == cmpval)
  {
    result = E_OK;
  }
  else
  {
    result = E_NOT_OK;
  }

  return result;
}

/*--- Crypto_xVIx_xAIx_Padding_Chk -------------------------------------------------------------- */

/* !LINKSTO Crypto.Dsn.Api/Padding/Crypto_xVIx_xAIx_Padding_Chk/0001,1 */

#if (   (FALSE                                                   )  \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_INT_PADDING_PKCS7)  \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_INT_PADDING_TLS12)  \
    )
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Padding_Chk
(
               uint8                                         padType,
  CONSTP2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) padPtr,
               uint32                                        padLength
)
{
  Std_ReturnType result = E_NOT_OK;

  switch (padType)
  {
    case CRYPTO_ALGOFAM_PADDING_PKCS7:
    {
      uint8    lastByte   = padPtr[padLength - 1U];
      boolean  errorFlag  = FALSE;
      uint8    i          = 0U;
      for (i = 0; i < (lastByte - 1U); i++)
      {
        if (padPtr[i] != lastByte)
        {
          errorFlag = TRUE;
        }
      }
      if (FALSE == errorFlag)
      {
        result = E_OK;
      }
    }
    break;

    case CRYPTO_ALGOFAM_PADDING_TLS12:
    {
      uint8    lastByte = padPtr[padLength - 1U];
      boolean  errorFlag    = FALSE;
      uint8    i        = 0U;
      for (i = 0; i < (lastByte + 1U); i++)
      {
        if (padPtr[i] != lastByte)
        {
          errorFlag = TRUE;
        }
      }
      if (FALSE == errorFlag)
      {
        result = E_OK;
      }
    }
    break;

    default:
    {
      /* Nothing to do (MISRA) */
    }
    break;
  }

  return result;
}
#endif /* #if (   (FALSE) ... */

/*--- Crypto_xVIx_xAIx_Padding_Add -------------------------------------------------------------- */

/* !LINKSTO Crypto.Dsn.Api/Padding/Crypto_xVIx_xAIx_Padding_Add/0001,1 */

#if (   (FALSE                                                   )  \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_INT_PADDING_PKCS7)  \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_INT_PADDING_TLS12)  \
    )
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Padding_Add
(
          uint8                                               padType,
  P2CONST(uint8,                    AUTOMATIC, CSM_APPL_DATA) dataPtr,
          uint32                                              dataLength,
    P2VAR(uint8,                    AUTOMATIC, CSM_APPL_DATA) resultPtr,
    P2VAR(uint32,                   AUTOMATIC, CSM_APPL_DATA) resultLengthPtr,
          uint8                                               blockSize
)
{
  Std_ReturnType result     = E_NOT_OK;
  uint8          bytestoadd = blockSize - (uint8)(dataLength % blockSize);

  TS_PARAM_UNUSED(dataPtr);

  /* This condition will never be false as equation that calculates the variable bytestoadd ensures that this variable is always
   * less than or equal to blockSize and resultLengthPtr is also defined as block size in StateMachine_FinishExec().
   */
  if (*resultLengthPtr >= bytestoadd)
  {
    switch (padType)
    {
      case CRYPTO_ALGOFAM_PADDING_PKCS7:
      {
        TS_MemSet(resultPtr, bytestoadd, bytestoadd);
        *resultLengthPtr = bytestoadd;
        result = E_OK;
      }
      break;

      case CRYPTO_ALGOFAM_PADDING_TLS12:
      {
        TS_MemSet(resultPtr, bytestoadd - 1U, bytestoadd);
        *resultLengthPtr = bytestoadd;
        result = E_OK;
      }
      break;

      default:
      {
        *resultLengthPtr = 0;
        result = E_OK;
      }
      break;
    }
  }
  else
  {
    result = CRYPTO_E_SMALL_BUFFER;
  }

  return result;
}
#endif /* #if (   (FALSE) ... */

/*--- Crypto_xVIx_xAIx_Padding_Del -------------------------------------------------------------- */

/* !LINKSTO Crypto.Dsn.Api/Padding/Crypto_xVIx_xAIx_Padding_Del/0001,1 */

#if (   (FALSE                                                   )  \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_INT_PADDING_PKCS7)  \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_INT_PADDING_TLS12)  \
    )
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Padding_Del
(
        uint8                                          padType,
  P2VAR(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) dataPtr,
  P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) outputLengthPtr,
        uint8                                          blockSize
)
{
  Std_ReturnType result     =  E_NOT_OK;

  /* This condition will never be false as dataLength is assigned to block size in StateMachine_FinishExec() and if last byte of
   * dataPtr(padding values) is greater than 16U, that value is changed to 16(pkcs7) or 15(tls12)
   */
  if(dataPtr[blockSize - 1U] <= blockSize)
  {
    switch (padType)
    {
      case CRYPTO_ALGOFAM_PADDING_PKCS7:
      {
        if(dataPtr[blockSize - 1U] != 0U)
        {
          if (*outputLengthPtr < (blockSize - (uint32)dataPtr[blockSize - 1U]))
          {
            result = CRYPTO_E_SMALL_BUFFER;
          }
          else
          {
            if (E_OK == Crypto_xVIx_xAIx_Padding_Chk(padType, &(dataPtr[blockSize - dataPtr[blockSize - 1U]]), dataPtr[blockSize - 1U]))
            {
              *outputLengthPtr = blockSize - (uint32)dataPtr[blockSize - 1U];
              result = E_OK;
            }
          }
        }
      }
      break;

      case CRYPTO_ALGOFAM_PADDING_TLS12:
      {
        if(dataPtr[blockSize - 1U] < blockSize)
        {
          if (*outputLengthPtr < (blockSize - ((uint32)dataPtr[blockSize - 1U] + 1U)))
          {
            result = CRYPTO_E_SMALL_BUFFER;
          }
          else
          {
            if(E_OK == Crypto_xVIx_xAIx_Padding_Chk(padType, &(dataPtr[blockSize - dataPtr[blockSize - 1U] - 1U]), ((uint32) dataPtr[blockSize - 1U] + 1U)))
            {
            *outputLengthPtr = (blockSize - ((uint32)dataPtr[blockSize - 1U] + 1U));
              result = E_OK;
            }
          }
        }
      }
      break;

      default:
      {
        /* Nothing to do (MISRA) */
      }
      break;
    }
  }

  return result;
}
#endif /* #if (   (FALSE) ... */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

/*==================[end of file]=================================================================*/

