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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_RANDOMGENERATE_AES_CTRDRBG.c/0001,1 */

/*==================[deviations]==================================================================*/

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * False positive from the tasking compiler.
 */

/* Code-Metric Deviation List
 *
 * CODEMETRIC-1) Deviated Rule: HIS_PATH
 * not 6116223 <= 2000
 *
 * CODEMETRIC-2) Deviated Rule: HIS_STMT
 * not 140 <= 75
 *
 * CODEMETRIC-3) Deviated Rule: HIS_STMT
 * not 138 <= 75
 *
 * CODEMETRIC-4) Deviated Rule: HIS_V(G)
 * not 47 <= 20
 *
 * Reason:
 * SingleCall functions are adjusted for performance and have a reduced amount of function calls
 * on purpose which leads to metric violations.
 */

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int.h>                                     /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_RANDOMGENERATE_AES_CTRDRBG.c/0002,1 */
#include <Crypto_xVIx_xAIx_Int_KeyManagement.h>                       /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_RANDOMGENERATE_AES_CTRDRBG.c/0003,1 */
#include <Crypto_xVIx_xAIx_Int_CPr_RANDOMGENERATE_AES_CTRDRBG.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_RANDOMGENERATE_AES_CTRDRBG.c/0004,1 */

/*==================[macros]======================================================================*/

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT,1 */
#if (defined CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT)
#error CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT already defined
#endif
/** \brief  Number of entries in the primitives state transition table. **/
#define CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT 4U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT,1 */
#if (defined CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT)
#error CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT already defined
#endif
/** \brief  Number of entries in the primitives state action table. **/
#define CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT 4U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_STARTIDLE,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_STARTIDLE)
#error CRYPTO_XVIX_XAIX_STATE_STARTIDLE already defined
#endif
/** \brief  The StartIdle state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_STARTIDLE 0U

#if (defined CRYPTO_XVIX_XAIX_STATE_SINGLECALL)
#error CRYPTO_XVIX_XAIX_STATE_SINGLECALL already defined
#endif
/** \brief  The SingleCall state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_SINGLECALL 1U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_CANCEL,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_CANCEL)
#error CRYPTO_XVIX_XAIX_STATE_CANCEL already defined
#endif
/** \brief  The Cancel state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_CANCEL 2U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_ERROR,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_ERROR)
#error CRYPTO_XVIX_XAIX_STATE_ERROR already defined
#endif
/** \brief  The Error state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_ERROR 3U

/*==================[type definitions]============================================================*/

/*==================[internal function declarations]==============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_ERROR'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_STARTIDLE'
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON) */

/** \brief Search the state transition table for the next state
 **
 ** This function searches the state trasition table for the next state that shall be processed.
 **
 ** \param[in,out]  smStateIndx    Pointer to the variable storing the index of the last processed
 **                                state. After the function call the index of the next state will
 **                                be stored in the variable.
 ** \param[in]      curState       Variable storing the current state.
 ** \parma[in]      resultAction   Variable storing the result of the previously called
 **                                action function.
 ** \parma[in]      jobProcessing  Variable stroing the processing type of the current job.
 ** \param[out]     nxtState       Pointer to the next state.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON)
static FUNC(boolean, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetNextState
(
  P2VAR(uint8,                                         AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) smStateIndx,
        Crypto_xVIx_xAIx_PrimitiveStateIdentifierType                                         curState,
        Std_ReturnType                                                                        resultAction,
        Crypto_ProcessingType                                                                 jobProcessing,
  P2VAR(Crypto_xVIx_xAIx_PrimitiveStateIdentifierType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) nxtState
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON) */

/* -----------------------------------------------------------------------------------------------*/
/* state action functions */

/* None */

/* -----------------------------------------------------------------------------------------------*/
/* state transition functions */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_SINGLECALL'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_STARTIDLE'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK      Request successful.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_CANCEL'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_STARTIDLE'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      Request successful.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON) */

/* -----------------------------------------------------------------------------------------------*/
/* static functions */

/** \brief  AES-CTRDRBG seed update function
 **         This function updates the internal state of the CTRDRBG using the
 **         seed value as described in NIST SP-800-90A.
 **
 ** \param[in]      objectId      Identifier of the crypto driver object that shall
 *                                process the request.
 ** \param[in]      providedData  Holds a pointer to the memory location which contains
 **                               the data to feed the Seed (seed value).
 ** \param[in]      block         Holds a pointer to the memory location which contains
 **                               the Block (V) of the block cipher.
 ** \param[in,out]  job           Pointer to the configuration of the job this primitive shall be
 **                               processed for. This contains structures with job and primitive
 **                               relevant information but also pointers to result buffers.
 ** \param[in]      primitive     Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK                        Request successful.
 ** \retval  E_NOT_OK                    Request failed.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_RandomAESCTRDRBGUpdate
(
          uint32                                                                    objectId,
  P2CONST(uint8,                             AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) providedData,
    P2VAR(uint8,                             AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) block,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal constants]==========================================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  The primitives state transition table.
 **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_StateTransitionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateTransitionType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Process_StateTransitionTable[CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT] =
{
  {NULL_PTR,                                                  CRYPTO_XVIX_XAIX_STATE_STARTIDLE,        CRYPTO_XVIX_XAIX_STATE_STARTIDLE,        CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK}, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE_TO_CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1               */
  {Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle,        CRYPTO_XVIX_XAIX_STATE_SINGLECALL,       CRYPTO_XVIX_XAIX_STATE_STARTIDLE,        CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK},
  {Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle,            CRYPTO_XVIX_XAIX_STATE_CANCEL,           CRYPTO_XVIX_XAIX_STATE_STARTIDLE,        CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK},
  {Crypto_xVIx_xAIx_StateMachine_Error2StartIdle,             CRYPTO_XVIX_XAIX_STATE_ERROR,            CRYPTO_XVIX_XAIX_STATE_STARTIDLE,        CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK}
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON) */

/** \brief  The primitives state action table.
 **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_StateActionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateActionType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Process_StateActionTable[CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT] =
{
  /* CRYPTO_XVIX_XAIX_STATE_STARTIDLE        */ {NULL_PTR},
  /* CRYPTO_XVIX_XAIX_STATE_SINGLECALL       */ {NULL_PTR},
  /* CRYPTO_XVIX_XAIX_STATE_CANCEL           */ {NULL_PTR},
  /* CRYPTO_XVIX_XAIX_STATE_ERROR            */ {NULL_PTR}
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Process ------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Process/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Process
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_WorkspaceType);

  Std_ReturnType           result         = E_NOT_OK;
  Crypto_OperationModeType jobMode        = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode;
  Crypto_ProcessingType    jobProcessing  = job->jobPrimitiveInfo->processingType;
  boolean                  runPrimitive   = FALSE;
  boolean                  jobIsProcessed = FALSE;

  workspace->paPrimitive = primitive;

  /* CHECK: NOPARSE
   * The IF and ELSE clauses are not reachable for randomgenerate primitives as the start
   * bit is always set.
   */
  if (workspace->smState == CRYPTO_XVIX_XAIX_STATE_CANCEL)
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Process/0002,1 */
    result = CRYPTO_E_JOB_CANCELED;
  }
  else
  if (CRYPTO_OPERATIONMODE_SINGLECALL == (jobMode & CRYPTO_OPERATIONMODE_SINGLECALL))
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Process/0003,1 */
    Crypto_xVIx_xAIx_CDOs[objectId].data->state                                 = CRYPTO_XVIX_XAIX_CDOSTATE_BUSY;
    Crypto_xVIx_xAIx_CDOs[objectId].data->jobCurrent->CRYPTO_XVIX_XAIX_JOBSTATE = CRYPTO_JOBSTATE_ACTIVE;
    workspace->paObjectId                                                       = objectId;
    workspace->smStateIndx                                                      = CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT - 3U;

    /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Workspace/0002,1 */
    SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
    workspace->smState                                                          = CRYPTO_XVIX_XAIX_STATE_SINGLECALL;
    SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();

    runPrimitive                                                                = TRUE;
  }
  else
  {
    (void) Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Reset(workspace->paObjectId, job, primitive);
  }
  /* CHECK: PARSE */

  if (TRUE == runPrimitive)
  {
    result = E_OK;
    /* all parameters given to this function are already checked in the ProcessJob function,
       hence this function can not fail in this case */
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00027,1 */
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Process/0004,1 */
    (void) Crypto_xVIx_xAIx_SetJobRunning(objectId, job, primitive, TRUE);

    workspace->smOperationDone = 0U;
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Process/0005,1 */
    if (CRYPTO_PROCESSING_SYNC == jobProcessing)
    {
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00026,1 */
      do
      {
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0013,1 */
        /* This function can only return E_OK */
        (void) Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Main(objectId, job, primitive);

        result = Crypto_xVIx_xAIx_GetJobRunning(objectId, job, primitive, &jobIsProcessed);
      }
      while (    (TRUE == jobIsProcessed)
              && (E_OK == result        )
            );
      result = workspace->smResult;
    }
  }

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Main ---------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Main/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Main
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_WorkspaceType);

  Std_ReturnType                                resultAction  = E_NOT_OK;
  Crypto_ProcessingType                         jobProcessing = job->jobPrimitiveInfo->processingType;
  Crypto_xVIx_xAIx_PrimitiveStateIdentifierType curState      = CRYPTO_XVIX_XAIX_STATE_ERROR;
  Crypto_xVIx_xAIx_PrimitiveStateIdentifierType nxtState      = CRYPTO_XVIX_XAIX_STATE_ERROR;
  boolean                                       nxtStateFound = FALSE;
  boolean                                       flgExecute    = FALSE;
  uint8                                         smStateIndx   = workspace->smStateIndx;

  TS_PARAM_UNUSED(objectId);

  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0002,1 */
  /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Workspace/0001,1 */
  /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Workspace/0002,1 */
  SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
  if (FALSE == workspace->lockMain)
  {
    workspace->lockMain = TRUE;
    flgExecute          = TRUE;
  }
  curState = workspace->smState;
  SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();

  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0003,1 */
  if (TRUE == flgExecute)
  {
    SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
    /* CHECK: NOPARSE
     * This condition is always false for RANDOMGENERATE_AES_CTRDRBG as primitive only has SINGLECALL mode.
     */
    if (   (curState                      != workspace->smState)
        && (CRYPTO_XVIX_XAIX_STATE_CANCEL != workspace->smState)
       )
    {
      workspace->smState = curState;
    }
    else
    {
      curState = workspace->smState;
    }
    /* CHECK: PARSE */
    SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();

    /* CHECK: NOPARSE
     * The call of state machine action functions is not reachable for RANDOMGENERATE_AES_CTRDRBG, because this
     * cryptographic primitive does not use action states.
     */
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0007,1 */
    if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Process_StateActionTable[curState].fcnAction))
    {
      resultAction = Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Process_StateActionTable[curState].fcnAction(job, primitive);
    }
    else
    {
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0008,1 */
      resultAction = E_OK;
    }
    /* CHECK: PARSE */

    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0009,1 */
    /* search for entry in state transition table in 2 steps */
    nxtStateFound = Crypto_xVIx_xAIx_GetNextState(&smStateIndx,
                                                  curState,
                                                  resultAction,
                                                  jobProcessing,
                                                  &nxtState
                                                 );
    /* CHECK: NOPARSE
     * The return value of GetNextState cannot be FALSE for RANDOMGENERATE_AES_CTRDRBG, because the state machine
     * transition table for this cryptographic primitive is complete.
     */
    if (TRUE == nxtStateFound)
    /* CHECK: PARSE */
    {
      workspace->smStateIndx = smStateIndx;
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0010,1 */
      if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Process_StateTransitionTable[smStateIndx].fcnTransition))
      {
        /* transition function returns using workspace->smResult */
        (void) Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Process_StateTransitionTable[smStateIndx].fcnTransition(job, primitive);

        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0011,1 */
        if (E_OK != workspace->smResult)
        {
          /* !LINKSTO Crypto.Asr.SWS_Crypto_00119,1 */
          nxtState = CRYPTO_XVIX_XAIX_STATE_ERROR;
        }
      }
    }
#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
    else
    {
      (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                             CRYPTO_XVIX_XAIX_INSTANCE_ID,
                             CRYPTO_XVIX_XAIX_SID_MAINFUNCTION,
                             CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                            );
    }
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */

    /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Workspace/0001,1 */
    /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Workspace/0002,1 */
    SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
    if (curState == workspace->smState)
    {
      workspace->smState = nxtState;
    }
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0012,1 */
    workspace->lockMain = FALSE;
    SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
  }

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Cancel -------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Cancel/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Cancel
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_WorkspaceType);

  Std_ReturnType                                result         = E_NOT_OK;
  Crypto_xVIx_xAIx_PrimitiveStateIdentifierType curState       = CRYPTO_XVIX_XAIX_STATE_ERROR;
  boolean                                       jobIsProcessed = FALSE;

  SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
  curState = workspace->smState;
  SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();

  if (   (CRYPTO_XVIX_XAIX_STATE_CANCEL != curState)
      && (CRYPTO_XVIX_XAIX_STATE_ERROR  != curState)
     )
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Cancel/0003,1 */
    SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
    workspace->smState = CRYPTO_XVIX_XAIX_STATE_CANCEL;
    SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();

    result             = CRYPTO_E_JOB_CANCELED;

    if (   (E_OK  == Crypto_xVIx_xAIx_GetJobRunning(objectId, job, primitive, &jobIsProcessed))
        && (FALSE == jobIsProcessed                                                           )
       )
    {
      /* If this path is reached the cancel function called by the main function will reset the
         workspace and set the state to StartIdle. This is why one Main call is sufficient */
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Cancel/0004,1 */
      /* This function can only return E_OK */
      (void) Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Main(objectId, job, primitive);
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Cancel/0005,1 */
      result = E_OK;
    }
  }
  /* CHECK: NOPARSE */
  else
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Cancel/0006,1 */
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Reset --------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Reset/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Reset
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as
   * secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESET(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_WorkspaceType));
    result = E_OK;
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Restart --------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Restart/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Restart
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESTART(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_WorkspaceType));
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Callback -----------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Callback/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_WorkspaceType);

  TS_PARAM_UNUSED(objectId);
  TS_PARAM_UNUSED(job);
  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Callback/0002,1 */
  workspace->notifyType   = cbkType;
  workspace->notifyResult = cbkResult;

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_StateMachine_Error2StartIdle ----------------------------------------------*/

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveError2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_WorkspaceType);

  Std_ReturnType result   = E_NOT_OK;
  Std_ReturnType smResult = E_NOT_OK;

  if (   (CRYPTO_XVIX_XAIX_STATE_ERROR == workspace->smState)
      && (                        E_OK == workspace->smResult ))
  {
    /* Unexpected error state reached, make sure to report E_NOT_OK back. */
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00119,1 */
    workspace->smResult = E_NOT_OK;
  }
  else
  {
    smResult            = workspace->smResult;
  }
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00025,1 */
  result              = Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Reset(workspace->paObjectId, job, primitive);
  workspace->smResult = smResult;

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON) */

/*--- Crypto_xVIx_xAIx_GetNextState --------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON)
static FUNC(boolean, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetNextState
(
  P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) smStateIndx,
  Crypto_xVIx_xAIx_PrimitiveStateIdentifierType curState,
  Std_ReturnType resultAction,
  Crypto_ProcessingType jobProcessing,
  P2VAR(Crypto_xVIx_xAIx_PrimitiveStateIdentifierType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) nxtState
)
{
  uint8   i             = 0U;
  boolean nxtStateFound = FALSE;

  /* CHECK: NOPARSE
   * The FOR loop condition can not fail for RANDOMGENERATE_AES_CTRDRBG, because the state transition table of this
   * cryptographic primitive is straight.
   */
  /* 1) iterate from last found entry in table to last table entry */
  for (i = *smStateIndx; i < CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT; i++)
  /* CHECK: PARSE */
  {
    if (   (Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx   = i;
      break;
    }
  }

  /* CHECK: NOPARSE
   * The FOR loop condition (FALSE == nxtStateFound) is always FALSE for RANDOMGENERATE_AES_CTRDRBG, because the state
   * transition table of this cryptographic primitive is straight and that is why the previous
   * FOR loop always already finds a next state.
   */
  /* 2) iterate from first table entry to last found entry in table */
  for (i = 0U; (FALSE == nxtStateFound) && (i < *smStateIndx); i++)
  {
    if (   (Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx  = i;
      break;
    }
  }
  /* CHECK: PARSE */

  return nxtStateFound;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle --------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON)
/* Deviation CODEMETRIC-1, CODEMETRIC-2, CODEMETRIC-3, CODEMETRIC-4 */
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_WorkspaceType);

         Std_ReturnType                                                           result                                     = E_NOT_OK;
         Std_ReturnType                                                           resultTmp                                  = E_NOT_OK;
          uint8                                                                   temp[CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_STATELEN] = { 0U }; /* Temporary buffer */
          uint32                                                                  keyLength                                  = CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_KEYLEN;
          uint32                                                                  j;
          uint32                                                                  SeedCount;
          boolean                                                                 fromPrimitive                              = FALSE;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keySeedPtr;

  result = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( job->cryptoKeyId,
                                                      CRYPTO_KE_CIPHER_KEY,
                                                     &keySeedPtr,
                                                      FALSE,
                                                      CRYPTO_XVIX_XAIX_SID_EMPTY
                                                    );
  if (E_OK == result)
  {
    fromPrimitive = TRUE;
    /* Check for correct seed state length */
    /* Deviation TASKING-1 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(result, keySeedPtr, fromPrimitive);
    if (E_OK == result)
    {
      if (CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_KEYLEN != keySeedPtr->data->size)
      {
        /* !LINKSTO Crypto.Req.CPr/RANDOMGENERATE_AES_CTRDRBG/GENERAL/0006,3 */
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
      }
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(keySeedPtr);
    }
    resultTmp = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( job->cryptoKeyId,
                                                            CRYPTO_XVIX_XAIX_KE_RANDOM_SEED_COUNT,
                                                            &keySeedPtr,
                                                            FALSE,
                                                            CRYPTO_XVIX_XAIX_SID_EMPTY
                                                          );
    if (   (E_OK == result)
        && (E_OK == resultTmp)
       )
    {
      fromPrimitive = TRUE;
      /* Deviation TASKING-1 */
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(result, keySeedPtr, fromPrimitive);
      if (E_OK == result)
      {
        /* Check for correct seed count length */
        if (CRYPTO_XVIX_XAIX_AES_CTRDRBG_SEED_COUNTLEN != keySeedPtr->data->size)
        {
            /* !LINKSTO Crypto.Req.CPr/RANDOMGENERATE_AES_CTRDRBG/GENERAL/0013,1 */
          result = CRYPTO_E_KEY_SIZE_MISMATCH;
        }
        else
        {
          TS_MemCpy((uint8 * const)&SeedCount, keySeedPtr->data->data, keySeedPtr->data->size);
          /* Check for correct entropy */
          if(SeedCount == CRYPTO_XVIX_XAIX_MAX_SEED_COUNT)
          {
            /* !LINKSTO Crypto.Asr.SWS_Crypto_00141,1 */
              /* !LINKSTO Crypto.Req.CPr/RANDOMGENERATE_AES_CTRDRBG/GENERAL/0011,1 */

            result = CRYPTO_E_ENTROPY_EXHAUSTION;
          }
        }
        CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(keySeedPtr);
      }
    }

    if(E_OK == result)
    {
      result = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( job->cryptoKeyId,
                                                          CRYPTO_KE_RANDOM_SEED_STATE,
                                                         &keySeedPtr,
                                                          FALSE,
                                                          CRYPTO_XVIX_XAIX_SID_EMPTY
                                                        );
      if (E_OK == result)
      {
        fromPrimitive = TRUE;
        /* Check for correct seed state length */
        /* Deviation TASKING-1 */
        CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(result, keySeedPtr, fromPrimitive);
        if (E_OK == result)
        {
          if (CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_BLOCKLEN == keySeedPtr->data->size)
          {
            TS_MemCpy(workspace->block, keySeedPtr->data->data, keySeedPtr->data->size);
            workspace->blockLength = keySeedPtr->data->size;
          }
          else
          {
            /* !LINKSTO Crypto.Req.CPr/RANDOMGENERATE_AES_CTRDRBG/GENERAL/0007,4 */
            result = CRYPTO_E_KEY_SIZE_MISMATCH;
          }
          CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(keySeedPtr);
        }
      }

      if (E_OK == result)
      {
        /* create secondary job */
        CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB();
        TS_MemCpy(&workspace->secondaryJob_primitiveInfo.algorithm.keyLength,
                  &keyLength,
                  sizeof(keyLength)
                 );
        TS_MemCpy(&workspace->secondaryJob.cryptoKeyId,
                  &job->cryptoKeyId,
                  sizeof(job->cryptoKeyId)
                 );

        /* !LINKSTO Crypto.Req.CPr/RANDOMGENERATE_AES_CTRDRBG/GENERAL/0001,1 */
        /* CHECK: NOPARSE
         * The for loop condition cannot fail at start as it is initialized with a constant.
        */
        /* 4.1 V = (V + 1) mod 2^outlen */
        /* it is hard to simulate with test that encryption gives all 16 bytes as 0xFF */
        for (j = CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_BLOCKLEN - 1U; j != 0U; j--)
        {
          if (workspace->block[j] != 0xFFUL)
          {
            workspace->block[j] += 1U;
            break;
          }
          else
          {
            workspace->block[j] = 0U;
          }
        }
         /* CHECK: PARSE */

        /* 4.2 output_block = Block_Encrypt(Key, V) */
        workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode            = CRYPTO_OPERATIONMODE_SINGLECALL;
        workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        = workspace->block;
        workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       = temp;
        workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     = CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_BLOCKLEN;
        workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &workspace->blockLength;

        /* start secondary primitive (encrypt aes ecb), including key expansion */
        CRYPTO_XVIX_XAIX_RESET_CALLBACK();
        primitive->P2->data->P1 = primitive;
        /* The KeyLength is already checked above for valid input size
           so the result in this function is always returning E_OK. */
        (void)primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                           &(workspace->secondaryJob),
                                                            workspace->paPrimitive->P2
                                                          );

        /* 5. returned_bits = Leftmost requested_number_of_bits of temp */
        for (j = 0U; j < CRYPTO_XVIX_XAIX_MIN(CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_BLOCKLEN, *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr)); j++)
        {
          (job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr)[j] = temp[j];
        }

        /* !LINKSTO Crypto.Asr.SWS_Crypto_00252,1 */
        /* !LINKSTO Crypto.Asr.SWS_Crypto_00135,1 */
        *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr) = CRYPTO_XVIX_XAIX_MIN(CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_BLOCKLEN,
                                                                                              *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr));
        primitive->P2->data->P1 = primitive;
        /* 6 (Key, V) = CTRDRBG_Update(additional_input, Key, V) */
        result = Crypto_xVIx_xAIx_RandomAESCTRDRBGUpdate
                 ( workspace->paObjectId,
                   NULL_PTR,
                   workspace->block,
                  &workspace->secondaryJob,
                   primitive->P2
                 );

        if(E_OK == result)
        {
          /* !LINKSTO Crypto.Req.CPr/RANDOMGENERATE_AES_CTRDRBG/GENERAL/0012,1 */
          /* Store the incremented seed count in key Element */
          if (E_OK == Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( job->cryptoKeyId,
                                                                 CRYPTO_XVIX_XAIX_KE_RANDOM_SEED_COUNT,
                                                                &keySeedPtr,
                                                                 FALSE,
                                                                 CRYPTO_XVIX_XAIX_SID_EMPTY
                                                               )
             )
          {
            fromPrimitive = TRUE;
            /* Deviation TASKING-1 */
            CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_LOCK(result, keySeedPtr, fromPrimitive);
            if(E_OK == result)
            {
              /* Read the actual seed count again from the key */
              TS_MemCpy((uint8 * const)&SeedCount, keySeedPtr->data->data, keySeedPtr->data->size);
              /* Updating the seed entropy count */
              SeedCount = SeedCount + 1U;
              /* !LINKSTO Crypto.Req.KMn/RANDOMGENERATE_AES_CTRDRBG/COMMON/0001,1 */
              /* !LINKSTO Crypto.Req.KMn/RANDOMGENERATE_AES_CTRDRBG/COMMON/0002,1 */
              CRYPTO_XVIX_XAIX_KEY_ELEMENT_STORE(job->cryptoKeyId,
                                                 CRYPTO_XVIX_XAIX_KE_RANDOM_SEED_COUNT,
                                                 keySeedPtr,
                                                 (const uint8 *)&SeedCount,
                                                 CRYPTO_XVIX_XAIX_AES_CTRDRBG_SEED_COUNTLEN,
                                                 result
                                                );
              keySeedPtr->data->size = CRYPTO_XVIX_XAIX_AES_CTRDRBG_SEED_COUNTLEN;
              CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE(keySeedPtr);
            }
          }
        }
      }
    }
#if ((CRYPTO_XVIX_XAIX_API_ENABLED_DETRUNTIMECHECKS == STD_ON) && (CRYPTO_XVIX_XAIX_API_VERSION != CRYPTO_API_VERSION_430))

    if (result == CRYPTO_E_ENTROPY_EXHAUSTION)
    {
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00141,1 */
      (void) Det_ReportRuntimeError(CRYPTO_XVIX_XAIX_MODULE_ID,
                                    CRYPTO_XVIX_XAIX_INSTANCE_ID,
                                    CRYPTO_XVIX_XAIX_SID_RANDOMSEED,
                                    CRYPTO_XVIX_XAIX_E_RE_ENTROPY_EXHAUSTED
                                   );
    }
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DETRUNTIMECHECKS == STD_ON) */
  }

  CRYPTO_XVIX_XAIX_SET_SMRESULT_SINGLECALL(result, sizeof(Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle ------------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveCancel2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_WorkspaceType);

  /* CHECK: NOPARSE
   * The Random CTRDRBG primitive does not support a secondary primitive.
   */
  if (NULL_PTR != workspace->secondaryJob.jobInfo)
  {
    if (E_OK == workspace->paPrimitive->P2->cnfg->description->fcnCancel( workspace->paObjectId,
                                                                         &(workspace->secondaryJob),
                                                                          workspace->paPrimitive->P2
                                                                        )
       )
    {
      workspace->notifyType = CRYPTO_XVIX_XAIX_CALLBACK_NONE;
      do
      {
        (void) workspace->paPrimitive->P2->cnfg->description->fcnMain( workspace->paObjectId,
                                                                      &(workspace->secondaryJob),
                                                                       workspace->paPrimitive->P2
                                                                     );
      }
      while (CRYPTO_XVIX_XAIX_CALLBACK_CANCEL == workspace->notifyType);
    }
  }
  /* CHECK: PARSE */

  /* !LINKSTO Crypto.Asr.SWS_Crypto_00183,2 */
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00144,1 */
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00181_1,1 */
  CRYPTO_XVIX_XAIX_SET_SMRESULT_CANCEL(CRYPTO_E_JOB_CANCELED, sizeof(Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON) */
/* --- Crypto_xVIx_xAIx_RandomSeedAESCTRDRBGUpdate ------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON)

static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_RandomAESCTRDRBGUpdate
(
          uint32                                                                             objectId,
  P2CONST(uint8,                                      AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) providedData,
    P2VAR(uint8,                                      AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) block,
    P2VAR(Crypto_JobType,                             AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
          Std_ReturnType                                                            result                                    = E_NOT_OK;
          uint8                                                                     temp[CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_STATELEN] = { 0U }; /* buffer which will be used as temporary storage */
          uint32                                                                    i                                         = 0U;
          uint32                                                                    j;
          uint32                                                                    blockLength                               = CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_BLOCKLEN;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keySeedPtr;
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primaryPrimitive                          = primitive->data->P1;
          boolean                                                                   fromPrimitive                             = TRUE;

  /* 2 While(len(temp) < seedlen) */
  while (i < CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_STATELEN)
  {
    /* 2.1 V = (V + 1) mod 2^outlen*/
    /* it is hard to simulate with test that encryption gives all 16 bytes as 0xFF */
    /* CHECK: NOPARSE
     * The for loop condition cannot fail at start as it is initialized with a constant.
     */
    for (j = CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_BLOCKLEN - 1U; j != 0U; j--)
    {
      if (0xFFUL != block[j])
      {
        block[j] += 1U;
        break;
      }
      else
      {
        block[j] = 0U;
      }
    }
    /* CHECK: PARSE */

    /* 4.2 output_block = Block_Encrypt(Key, V) */
    job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode            = CRYPTO_OPERATIONMODE_SINGLECALL;
    job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        = block;
    job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       = &temp[i];
    job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     = CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_BLOCKLEN;
    job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &blockLength;

    /* start secondary primitive (encrypt aes ecb), including key expansion */
    primitive->data->P1 = primaryPrimitive;
    /* The KeyLength is already checked before update function call for valid
       input size so the result in this function is always returning E_OK. */
    (void) primitive->cnfg->description->fcnProcess(objectId,
                                                    job,
                                                    primitive
                                                   );

    /* 2.3 temp = temp || output_block */
    i += CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_BLOCKLEN;
  }

  /* CHECK: NOPARSE
   * One path of this check is covered in CTRDRBG primitive file and the other in Keymanagement file,
   * because this function exists separately in both files as a static function.
   */
  /* step 4: temp XOR providedData */
  if(NULL_PTR != providedData)
  {
    for(i = 0U; i < CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_STATELEN; i++)
    {
      temp[i] ^= providedData[i];
    }
  }
  /* CHECK: PARSE */

  /* step 5 & 6: symKey is the first 32 elements of temp and V is the last 16 elements of temp */
  /* Store the new symKey from temp in key Element */
  result = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( job->cryptoKeyId,
                                                      CRYPTO_KE_CIPHER_KEY,
                                                     &keySeedPtr,
                                                      FALSE,
                                                      CRYPTO_XVIX_XAIX_SID_EMPTY
                                                    );

  /* CHECK: NOPARSE
   * The key element is already checked before in the calling function, hence
   * this check cannot fail here.
   */
  if (E_OK == result)
  {
    fromPrimitive = TRUE;
    /* Deviation TASKING-1 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_LOCK(result, keySeedPtr, fromPrimitive);
  }
  /* CHECK: PARSE */

  if(E_OK == result)
  {
    /* !LINKSTO Crypto.Req.KMn/RANDOMGENERATE_AES_CTRDRBG/COMMON/0001,1 */
    /* !LINKSTO Crypto.Req.KMn/RANDOMGENERATE_AES_CTRDRBG/COMMON/0002,1 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_STORE(job->cryptoKeyId,
                                       CRYPTO_KE_CIPHER_KEY,
                                       keySeedPtr,
                                       temp,
                                       CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_KEYLEN,
                                       result
                                      );
    keySeedPtr->data->size = CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_KEYLEN;
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE(keySeedPtr);
  }

  if (E_OK == result)
  {
    /* Store the new V from temp in key Element */
    result = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( job->cryptoKeyId,
                                                        CRYPTO_KE_RANDOM_SEED_STATE,
                                                       &keySeedPtr,
                                                        FALSE,
                                                        CRYPTO_XVIX_XAIX_SID_EMPTY
                                                      );
    /* CHECK: NOPARSE
     * The key element is already checked before in the calling function, hence
     * this check cannot fail here.
     */
    if (E_OK == result)
    {
      fromPrimitive = TRUE;
      /* Deviation TASKING-1 */
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_LOCK(result, keySeedPtr, fromPrimitive);
    }
    /* CHECK: PARSE */

    if(E_OK == result)
    {
      /* !LINKSTO Crypto.Req.KMn/RANDOMGENERATE_AES_CTRDRBG/COMMON/0001,1 */
      /* !LINKSTO Crypto.Req.KMn/RANDOMGENERATE_AES_CTRDRBG/COMMON/0002,1 */
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_STORE( job->cryptoKeyId,
                                          CRYPTO_KE_RANDOM_SEED_STATE,
                                          keySeedPtr,
                                         &temp[CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_KEYLEN],
                                          CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_BLOCKLEN,
                                          result
                                        );
      keySeedPtr->data->size = CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_BLOCKLEN;
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE(keySeedPtr);
    }
  }
  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[end of file]=================================================================*/

