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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_MACVERIFY_SHA2512_HMAC.c/0001,1 */

/*==================[deviations]==================================================================*/

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * False positive from the tasking compiler.
 */

/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 10.8 (required)
 * The value of a composite expression shall not be cast to a different essential type category or a
 * wider essential type.
 *
 * Reason:
 * This composite expression is a subtraction between two pointers, the subtraction is performed
 * according to the register width on the respective platform. The result is a signed integer, which
 * is then cast to an unsigned integer. The MISRA rule does not fit here, since it is already taken
 * into account that first the subtraction takes place regarding the specific register width and
 * then the cast from signed to unsinged follows.
 */

/*
 * Code-Metric Deviation List
 *
 Deviated Rule: HIS_PATH
 * not 14976 <= 2000
 *
 * CODEMETRIC-2) Deviated Rule: HIS_STMT
 * not 128 <= 75
 *
 * CODEMETRIC-3) Deviated Rule: HIS_STMT
 * not 126 <= 75
 *
 * CODEMETRIC-4) Deviated Rule: HIS_VOCF
 * not 13.89 <= 12
 *
 * CODEMETRIC-5) Deviated Rule: HIS_VOCF
 * not 14.04 <= 12
 *
 * CODEMETRIC-6) Deviated Rule: HIS_V(G)
 * not 32 <= 20
 *
 * Reason:
 * SingleCall functions are adjusted for performance and have a reduced amount of function calls
 * on purpose which leads to metric violations.
 *
, * CODEMETRIC-1) Deviated Rule: HIS_PATH
 * not 17472 <= 2000
 *
 * CODEMETRIC-2) Deviated Rule: HIS_STMT
 * not 133 <= 75
 *
 * CODEMETRIC-3) Deviated Rule: HIS_STMT
 * not 135 <= 75
 *
 * CODEMETRIC-4) Deviated Rule: HIS_VOCF
 * not 12.69 <= 12
 *
 * CODEMETRIC-5) Deviated Rule: HIS_VOCF
 * not 12.60 <= 12
 *
 * CODEMETRIC-6) Deviated Rule: HIS_V(G)
 * not 34 <= 20
 *
 * Reason:
 * SingleCall functions are adjusted for performance and have a reduced amount of function calls
 * on purpose which leads to metric violations.
) */

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int.h>                                 /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_MACVERIFY_SHA2512_HMAC.c/0002,1 */
#include <Crypto_xVIx_xAIx_Int_KeyManagement.h>                   /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_MACVERIFY_SHA2512_HMAC.c/0003,1 */
#include <Crypto_xVIx_xAIx_Int_CPr_MACVERIFY_SHA2512_HMAC.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_MACVERIFY_SHA2512_HMAC.c/0004,1 */

/*==================[macros]======================================================================*/

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT,1 */
#if (defined CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT)
#error CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT already defined
#endif
/** \brief  Number of entries in the primitives state transition table. **/
#define CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT 12U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT,1 */
#if (defined CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT)
#error CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT already defined
#endif
/** \brief  Number of entries in the primitives state action table. **/
#define CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT 11U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_STARTIDLE,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_STARTIDLE)
#error CRYPTO_XVIX_XAIX_STATE_STARTIDLE already defined
#endif
/** \brief  The StartIdle state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_STARTIDLE 0U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_STARTEXEC,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_STARTEXEC)
#error CRYPTO_XVIX_XAIX_STATE_STARTEXEC already defined
#endif
/** \brief  The StartExec state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_STARTEXEC 1U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE)
#error CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE already defined
#endif
/** \brief  The UpdateIdle state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE 2U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC)
#error CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC already defined
#endif
/** \brief  The UpdateExec state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC 3U

#if (defined CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS)
#error CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS already defined
#endif
/** \brief  The UpdateProcess state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS 4U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE)
#error CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE already defined
#endif
/** \brief  The UpdateFinishIdle state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE 5U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_FINISHEXEC,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHEXEC)
#error CRYPTO_XVIX_XAIX_STATE_FINISHEXEC already defined
#endif
/** \brief  The FinishExec state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHEXEC 6U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHFINALIZE)
#error CRYPTO_XVIX_XAIX_STATE_FINISHFINALIZE already defined
#endif
/** \brief  The FinishExec state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHFINALIZE 7U

#if (defined CRYPTO_XVIX_XAIX_STATE_SINGLECALL)
#error CRYPTO_XVIX_XAIX_STATE_SINGLECALL already defined
#endif
/** \brief  The SingleCall state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_SINGLECALL 8U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_CANCEL,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_CANCEL)
#error CRYPTO_XVIX_XAIX_STATE_CANCEL already defined
#endif
/** \brief  The Cancel state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_CANCEL 9U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_ERROR,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_ERROR)
#error CRYPTO_XVIX_XAIX_STATE_ERROR already defined
#endif
/** \brief  The Error state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_ERROR 10U

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
static FUNC(boolean, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetNextState
(
  P2VAR(uint8,                                         AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) smStateIndx,
        Crypto_xVIx_xAIx_PrimitiveStateIdentifierType                                         curState,
        Std_ReturnType                                                                        resultAction,
        Crypto_ProcessingType                                                                 jobProcessing,
  P2VAR(Crypto_xVIx_xAIx_PrimitiveStateIdentifierType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) nxtState
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */
/* -----------------------------------------------------------------------------------------------*/
/* state action functions */

/** \brief  State action function for state
 **         'CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure which describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK           Request successful.
 ** \retval  CRYPTO_E_BUSY  Further processing is needed.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

/* -----------------------------------------------------------------------------------------------*/
/* state transition functions */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_STARTEXEC'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure which describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      request successful
 ** \retval  E_NOT_OK  request failed
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure which describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      Request successful.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHIDLE'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure which describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      Request successful.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHEXEC'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHFINALIZE'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure which describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      request successful
 ** \retval  E_NOT_OK  request failed
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishFinalize
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHFINALIZE'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_STARTIDLE'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure which describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      request successful
 ** \retval  E_NOT_OK  request failed
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishFinalize2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_SINGLECALL'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_STARTIDLE'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure which describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      request successful
 ** \retval  E_NOT_OK  request failed
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_CANCEL'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_STARTIDLE'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure which describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      request successful
 ** \retval  E_NOT_OK  request failed
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal constants]==========================================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  The primitives state transition table. **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_StateTransitionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateTransitionType, CRYPTO_xVIx_xAIx_CONST)
Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Process_StateTransitionTable[CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT] =
{
  { NULL_PTR,                                                      CRYPTO_XVIX_XAIX_STATE_STARTIDLE,        CRYPTO_XVIX_XAIX_STATE_STARTIDLE,        CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE_TO_CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1               */
  { Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle,            CRYPTO_XVIX_XAIX_STATE_STARTEXEC,        CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,       CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishFinalize,       CRYPTO_XVIX_XAIX_STATE_FINISHEXEC,       CRYPTO_XVIX_XAIX_STATE_FINISHFINALIZE,   CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { Crypto_xVIx_xAIx_StateMachine_FinishFinalize2StartIdle,        CRYPTO_XVIX_XAIX_STATE_FINISHFINALIZE,   CRYPTO_XVIX_XAIX_STATE_STARTIDLE,        CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { NULL_PTR,                                                      CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,       CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,       CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE_TO_CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE/0001,1             */
  { Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess,        CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC,       CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,    CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { NULL_PTR,                                                      CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,    CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,    CRYPTO_XVIX_XAIX_PROCESSING_BOTH, CRYPTO_E_BUSY },
  { Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle,  CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,    CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE, CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { NULL_PTR,                                                      CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE, CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE, CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE_TO_CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE/0001,1 */

  { Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle,            CRYPTO_XVIX_XAIX_STATE_SINGLECALL,       CRYPTO_XVIX_XAIX_STATE_STARTIDLE,        CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle,                CRYPTO_XVIX_XAIX_STATE_CANCEL,           CRYPTO_XVIX_XAIX_STATE_STARTIDLE,        CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { Crypto_xVIx_xAIx_StateMachine_Error2StartIdle,                 CRYPTO_XVIX_XAIX_STATE_ERROR,            CRYPTO_XVIX_XAIX_STATE_STARTIDLE,        CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          }
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

/** \brief  The primitives state action table. **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_StateActionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateActionType, CRYPTO_xVIx_xAIx_CONST)
Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Process_StateActionTable[CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT] =
{
  /* CRYPTO_XVIX_XAIX_STATE_STARTIDLE        */ { NULL_PTR                                    }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1        */
  /* CRYPTO_XVIX_XAIX_STATE_STARTEXEC        */ { NULL_PTR                                    }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTEXEC/0001,1        */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE       */ { NULL_PTR                                    }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC       */ { NULL_PTR                                    }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS    */ { Crypto_xVIx_xAIx_StateMachine_UpdateProcess },
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE */ { NULL_PTR                                    }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE/0001,1 */
  /* CRYPTO_XVIX_XAIX_STATE_FINISHEXEC       */ { NULL_PTR                                    }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_FINISHEXEC/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_FINISHFINALIZE   */ { NULL_PTR                                    },
  /* CRYPTO_XVIX_XAIX_STATE_SINGLECALL       */ { NULL_PTR                                    },
  /* CRYPTO_XVIX_XAIX_STATE_CANCEL           */ { NULL_PTR                                    },
  /* CRYPTO_XVIX_XAIX_STATE_ERROR            */ { NULL_PTR                                    }
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Process ----------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Process/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Process
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_WorkspaceType);

  Std_ReturnType           result         = E_NOT_OK;
  Crypto_OperationModeType jobMode        = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode;
  Crypto_ProcessingType    jobProcessing  = job->jobPrimitiveInfo->processingType;
  boolean                  runPrimitive   = FALSE;
  boolean                  jobIsProcessed = FALSE;

  workspace->paPrimitive = primitive;

  if (workspace->smState == CRYPTO_XVIX_XAIX_STATE_CANCEL)
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Process/0002,1 */
    result = CRYPTO_E_JOB_CANCELED;
  }
  else
  if (   (CRYPTO_OPERATIONMODE_SINGLECALL == (jobMode & CRYPTO_OPERATIONMODE_SINGLECALL))
      && (CRYPTO_PROCESSING_SYNC          == jobProcessing                              )
     )
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
  if (CRYPTO_OPERATIONMODE_START == (jobMode & CRYPTO_OPERATIONMODE_START))
  {
    /* !LINKSTO Crypto.Dsn.JobTransition.Idle2Active,1 */
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Process/0003,1 */
    Crypto_xVIx_xAIx_CDOs[objectId].data->state                                 = CRYPTO_XVIX_XAIX_CDOSTATE_BUSY;
    Crypto_xVIx_xAIx_CDOs[objectId].data->jobCurrent->CRYPTO_XVIX_XAIX_JOBSTATE = CRYPTO_JOBSTATE_ACTIVE;
    workspace->paObjectId                                                       = objectId;
    workspace->smStateIndx                                                      = 0U;
    /* !LINKSTO Crypto.Dsn.JobTransition.InitialActive2Start,1 */
    /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE_TO_CRYPTO_XVIX_XAIX_STATE_STARTEXEC/0001,1 */
    /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Workspace/0002,1 */
    SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
    workspace->smState                                                          = CRYPTO_XVIX_XAIX_STATE_STARTEXEC;
    SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();

    runPrimitive                                                                = TRUE;
  }
  else
  if (   (CRYPTO_OPERATIONMODE_UPDATE == (jobMode & CRYPTO_OPERATIONMODE_UPDATE))
      && (   (CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE       == workspace->smState)
          || (CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE == workspace->smState)
         )
     )
  {
    /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Workspace/0002,1 */
    SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
    /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE_TO_CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC/0001,1 */
    /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE_TO_CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC/0001,1 */
    workspace->smState = CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC;
    SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
    runPrimitive       = TRUE;
  }
  else
  if (   (CRYPTO_OPERATIONMODE_FINISH             == (jobMode & CRYPTO_OPERATIONMODE_FINISH))
      && (CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE == workspace->smState                     )
     )
  {
    /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Workspace/0002,1 */
    SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00023,1 */
    /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE_TO_CRYPTO_XVIX_XAIX_STATE_FINISHEXEC/0001,1 */
    workspace->smState = CRYPTO_XVIX_XAIX_STATE_FINISHEXEC;
    SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
    runPrimitive       = TRUE;
  }
  else
  {
    (void) Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Reset(workspace->paObjectId, job, primitive);
  }

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
        (void) Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Main(objectId, job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Main -------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Main/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Main
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_WorkspaceType);

  Std_ReturnType                                resultAction  = E_NOT_OK;
  Crypto_ProcessingType                         jobProcessing = job->jobPrimitiveInfo->processingType;
  Crypto_OperationModeType                      jobMode       = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode;
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
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0004,1 */
    if (   (CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE == curState                               )
        && (CRYPTO_OPERATIONMODE_UPDATE       == (jobMode & CRYPTO_OPERATIONMODE_UPDATE))
       )
    {
      curState = CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC;
    }
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0005,1 */
    if (   (CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE == curState                               )
        && (CRYPTO_OPERATIONMODE_FINISH             == (jobMode & CRYPTO_OPERATIONMODE_FINISH))
       )
    {
      curState = CRYPTO_XVIX_XAIX_STATE_FINISHEXEC;
    }
    SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
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
    SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();

    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0007,1 */
    if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Process_StateActionTable[curState].fcnAction))
    {
      resultAction = Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Process_StateActionTable[curState].fcnAction(job, primitive);
    }
    else
    {
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0008,1 */
      resultAction = E_OK;
    }

    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0009,1 */
    /* search for entry in state transition table in 2 steps */
    nxtStateFound = Crypto_xVIx_xAIx_GetNextState(&smStateIndx,
                                                  curState,
                                                  resultAction,
                                                  jobProcessing,
                                                  &nxtState
                                                 );
    if (TRUE == nxtStateFound)
    {
      workspace->smStateIndx = smStateIndx;
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0010,1 */
      if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Process_StateTransitionTable[smStateIndx].fcnTransition))
      {
        /* transition function returns using workspace->smResult */
        (void) Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Process_StateTransitionTable[smStateIndx].fcnTransition(job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Cancel -----------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Cancel/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Cancel
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_WorkspaceType);

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
      (void) Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Main(objectId, job, primitive);
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Reset ------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Reset/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Reset
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as
   * secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESET(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_WorkspaceType));
    result = E_OK;
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Restart ------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Restart/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Restart
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESTART(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_WorkspaceType));
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Callback ---------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Callback/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
/* CHECK: NOPARSE
 * This API is only reachable for cryptographic primitives that are using a secondary primitive.
 */
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_WorkspaceType);

  TS_PARAM_UNUSED(objectId);
  TS_PARAM_UNUSED(job);
  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Callback/0002,1 */
  workspace->notifyType   = cbkType;
  workspace->notifyResult = cbkResult;

  return E_OK;
}
/* CHECK: PARSE */
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_StateMachine_Error2StartIdle ----------------------------------------------*/

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveError2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_WorkspaceType);

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
  result              = Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Reset(workspace->paObjectId, job, primitive);
  workspace->smResult = smResult;

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

/*--- Crypto_xVIx_xAIx_GetNextState --------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
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

  /* 1) iterate from last found entry in table to last table entry */
  for (i = *smStateIndx; i < CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT; i++)
  {
    if (   (Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx   = i;
      break;
    }
  }

  /* 2) iterate from first table entry to last found entry in table */
  for (i = 0U; (FALSE == nxtStateFound) && (i < *smStateIndx); i++)
  {
    if (   (Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx  = i;
      break;
    }
  }

  return nxtStateFound;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */
/* --- Crypto_xVIx_xAIx_StateMachine_UpdateProcess ---------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_WorkspaceType);

  Std_ReturnType result             = E_NOT_OK;
  /* Deviation MISRAC2012-1 <+3> */
  uint32         processInputLength = CRYPTO_XVIX_XAIX_MIN(CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_BLOCKSIZE,
                                                      (uint32)(workspace->inputEndPtr - workspace->inputActPtr)
                                                     );

  TS_PARAM_UNUSED(job);

  /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/UPDATE/0001,1 */
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr    = workspace->inputActPtr;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength = processInputLength;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode        = CRYPTO_OPERATIONMODE_UPDATE;

  CRYPTO_XVIX_XAIX_RESET_CALLBACK();
  primitive->P2->data->P1 = primitive;
  result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                        &(workspace->secondaryJob),
                                                         workspace->paPrimitive->P2
                                                       );

  if (E_OK == result)
  {
    if ((workspace->inputActPtr + processInputLength) < workspace->inputEndPtr)
    {
      workspace->inputActPtr += processInputLength;
      result                  = CRYPTO_E_BUSY;
    }
    else
    {
      result = E_OK;
    }
  }

  workspace->smResult = result;

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle --------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Start2Update,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_WorkspaceType);

          Std_ReturnType                                                          result        = E_NOT_OK;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyPtr        = NULL_PTR;
    P2VAR(uint8,                           AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) k0            = workspace->K0;
    P2VAR(uint8,                           AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) bf            = workspace->BF;
          uint32                                                                  i             = 0U;
          boolean                                                                 fromPrimitive = FALSE;

  TS_MemBZero(k0,            CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_BLOCKSIZE );
  TS_MemBZero(bf,            CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_BLOCKSIZE );
  TS_MemBZero(workspace->H1, CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_RESULTSIZE);
  TS_MemBZero(workspace->H2, CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_RESULTSIZE);

  /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/START/0001,1 */
  result = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( job->cryptoKeyId,
                                                      CRYPTO_KE_MAC_KEY,
                                                     &keyPtr,
                                                      FALSE,
                                                      CRYPTO_XVIX_XAIX_SID_EMPTY
                                                    );
  /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/START/0002,1 */

  if (E_OK == result)
  {
    fromPrimitive = TRUE;
    /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/START/0003,1 */
    /* Deviation TASKING-1 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(result, keyPtr, fromPrimitive);
  }

  /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/START/0004,1 */
  if (E_OK == result)
  {
    /* create secondary job */
    CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB();
    CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_SRV();

    if (CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_BLOCKSIZE < keyPtr->data->size)
    {
      /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/START/0005,1 */
      i = CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_RESULTSIZE;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        =  keyPtr->data->data;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     =  keyPtr->data->size;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       =  k0;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &i;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode            =  CRYPTO_OPERATIONMODE_SINGLECALL;

      CRYPTO_XVIX_XAIX_RESET_CALLBACK();
      primitive->P2->data->P1 = primitive;
      result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                            &(workspace->secondaryJob),
                                                             workspace->paPrimitive->P2
                                                           );
      /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/START/0006,1 */
    }
    else
    {
      /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/START/0007,1 */
      TS_MemCpy(k0, keyPtr->data->data, keyPtr->data->size);
      result = E_OK;
    }

    if (E_OK == result)
    {
      /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/START/0008,1 */
      for (i = 0; i<CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_BLOCKSIZE; i++)
      {
        bf[i] = k0[i] ^ 0x36U;
      }

      /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/START/0009,1 */
      workspace->H1Len = CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_RESULTSIZE;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        =  bf;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     =  CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_BLOCKSIZE;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       =  workspace->H1;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &workspace->H1Len;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode            =  CRYPTO_OPERATIONMODE_STREAMSTART ;

      CRYPTO_XVIX_XAIX_RESET_CALLBACK();
      primitive->P2->data->P1 = primitive;
      result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                            &(workspace->secondaryJob),
                                                             workspace->paPrimitive->P2
                                                           );
    }

    /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/START/0011,1 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(keyPtr);
  }

  CRYPTO_XVIX_XAIX_SET_SMRESULT_START(result, sizeof(Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess ----------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Update2Update,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_WorkspaceType);

  TS_PARAM_UNUSED(primitive);

  workspace->inputActPtr =   job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr;
  workspace->inputEndPtr =   job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr
                           + job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength;

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle ----------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Update2Finish,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_WorkspaceType);

  TS_PARAM_UNUSED(job);
  TS_PARAM_UNUSED(primitive);

  CRYPTO_XVIX_XAIX_SET_SMRESULT_UPDATE(workspace->smResult, sizeof(Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishFinalize ---------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Finish2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishFinalize
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_WorkspaceType);

        Std_ReturnType                                         result = E_NOT_OK;
  P2VAR(uint8,          AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) k0     = workspace->K0;
  P2VAR(uint8,          AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) bf     = workspace->BF;
        uint32                                                 i      = 0U;

  TS_PARAM_UNUSED(job);

  /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/FINISH/0001,1 */
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode = CRYPTO_OPERATIONMODE_FINISH;

  CRYPTO_XVIX_XAIX_RESET_CALLBACK();
  primitive->P2->data->P1 = primitive;
  result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                        &(workspace->secondaryJob),
                                                         workspace->paPrimitive->P2
                                                       );
  /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/FINISH/0002,1 */

  if (E_OK == result)
  {
    /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/FINISH/0003,1 */
    for (i = 0; i<CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_BLOCKSIZE; i++)
    {
      bf[i] = k0[i] ^ 0x5CU;
    }

    /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/FINISH/0004,1 */
    workspace->H2Len = CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_RESULTSIZE;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        =  bf;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     =  CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_BLOCKSIZE;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       =  workspace->H2;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &workspace->H2Len;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode            =  CRYPTO_OPERATIONMODE_STREAMSTART ;

    CRYPTO_XVIX_XAIX_RESET_CALLBACK();
    primitive->P2->data->P1 = primitive;
    result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                          &(workspace->secondaryJob),
                                                           workspace->paPrimitive->P2
                                                         );
  }

  workspace->smResult = result;

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishFinalize2StartIdle ----------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishFinalize2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_WorkspaceType);

  Std_ReturnType          result       = E_NOT_OK;
  Crypto_VerifyResultType resultVerify = CRYPTO_E_VER_NOT_OK;
  uint8                   mask         = 0x00U;

  /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/FINISH/0006,1 */
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr    = workspace->H1;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength = CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_RESULTSIZE;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode        = CRYPTO_OPERATIONMODE_UPDATE;

  CRYPTO_XVIX_XAIX_RESET_CALLBACK();
  primitive->P2->data->P1 = primitive;
  result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                        &(workspace->secondaryJob),
                                                         workspace->paPrimitive->P2
                                                       );

  /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/FINISH/0008,1 */
  if (E_OK == result)
  {
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode = CRYPTO_OPERATIONMODE_FINISH;

    CRYPTO_XVIX_XAIX_RESET_CALLBACK();
    primitive->P2->data->P1 = primitive;
    result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                          &(workspace->secondaryJob),
                                                           workspace->paPrimitive->P2
                                                         );

    /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/FINISH/0009,1 */
    if (E_OK == result)
    {
      if ((CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_RESULTSIZE * 8U) >= job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputLength)
      {
        /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/FINISH/0010,2 */
        /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/FINISH/0011,2 */
        mask = (~((1U << (((uint8) 8U) - (job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputLength % 8U))) - 1U));

        /* if check of full bytes of number of bits to verify is okay, check also remaining bits in the following byte */
        if (E_OK == Crypto_xVIx_xAIx_MemCmpSec(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputPtr,
                                               workspace->H2,
                                               (job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputLength / 8U)
                                              )
           )
        {
          if (0x00U != mask)
          {
            if (   (job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputPtr[job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputLength / 8U] & mask)
                == (workspace->H2[job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputLength / 8U]                                                   & mask)
               )
            {
              resultVerify = CRYPTO_E_VER_OK;
            }
          }
          else
          {
            resultVerify = CRYPTO_E_VER_OK;
          }
        }

        /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/FINISH/0012,2 */
        *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.verifyPtr) = resultVerify;
      }
      else
      {
        result = E_NOT_OK;
      }
    }
  }

  CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH(result, sizeof(Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle --------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
/* Deviation CODEMETRIC-1, CODEMETRIC-2, CODEMETRIC-3, CODEMETRIC-4, CODEMETRIC-5, CODEMETRIC-6 */
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_WorkspaceType);

          Std_ReturnType                                                          result        = E_NOT_OK;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyPtr        = NULL_PTR;
    P2VAR(uint8,                           AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) k0            = workspace->K0;
    P2VAR(uint8,                           AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) bf            = workspace->BF;
          uint32                                                                  i             = 0U;
          boolean                                                                 fromPrimitive = FALSE;
          Crypto_VerifyResultType                                                 resultVerify  = CRYPTO_E_VER_NOT_OK;
          uint8                                                                   mask          = 0x00U;

  TS_MemBZero(k0,            CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_BLOCKSIZE );
  TS_MemBZero(bf,            CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_BLOCKSIZE );
  TS_MemBZero(workspace->H1, CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_RESULTSIZE);
  TS_MemBZero(workspace->H2, CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_RESULTSIZE);

  /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/START/0001,1 */
  result = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( job->cryptoKeyId,
                                                      CRYPTO_KE_MAC_KEY,
                                                     &keyPtr,
                                                      FALSE,
                                                      CRYPTO_XVIX_XAIX_SID_EMPTY
                                                    );

  /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/START/0002,1 */
  if (E_OK == result)
  {
    fromPrimitive = TRUE;
    /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/START/0003,1 */
    /* Deviation TASKING-1 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(result, keyPtr, fromPrimitive);
  }

  /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/START/0004,1 */
  if (E_OK == result)
  {
    /* create secondary job */
    CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB();
    CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_SRV();

    if (CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_BLOCKSIZE < keyPtr->data->size)
    {
      /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/START/0005,1 */
      i = CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_RESULTSIZE;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        =  keyPtr->data->data;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     =  keyPtr->data->size;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       =  k0;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &i;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode            =  CRYPTO_OPERATIONMODE_SINGLECALL;

      CRYPTO_XVIX_XAIX_RESET_CALLBACK();
      primitive->P2->data->P1 = primitive;
      result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                            &(workspace->secondaryJob),
                                                             workspace->paPrimitive->P2
                                                           );
      /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/START/0006,1 */
    }
    else
    {
      /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/START/0007,1 */
      TS_MemCpy(k0, keyPtr->data->data, keyPtr->data->size);
      result = E_OK;
    }

    if (E_OK == result)
    {
      /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/START/0008,1 */
      for (i = 0; i<CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_BLOCKSIZE; i++)
      {
        bf[i] = k0[i] ^ 0x36U;
      }

      /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/START/0009,1 */
      workspace->H1Len = CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_RESULTSIZE;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        =  bf;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     =  CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_BLOCKSIZE;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       =  workspace->H1;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &workspace->H1Len;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode            =  CRYPTO_OPERATIONMODE_STREAMSTART ;

      CRYPTO_XVIX_XAIX_RESET_CALLBACK();
      primitive->P2->data->P1 = primitive;
      result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                            &(workspace->secondaryJob),
                                                             workspace->paPrimitive->P2
                                                           );
    }

    /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/START/0011,1 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(keyPtr);
  }

  if (E_OK == result)
  {
    /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/UPDATE/0001,1 */
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr    = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode        = CRYPTO_OPERATIONMODE_UPDATE;

    CRYPTO_XVIX_XAIX_RESET_CALLBACK();
    primitive->P2->data->P1 = primitive;
    result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                          &(workspace->secondaryJob),
                                                           workspace->paPrimitive->P2
                                                         );
  }

  if (E_OK == result)
  {
    /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/FINISH/0001,1 */
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode = CRYPTO_OPERATIONMODE_FINISH;

    CRYPTO_XVIX_XAIX_RESET_CALLBACK();
    primitive->P2->data->P1 = primitive;
    result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                          &(workspace->secondaryJob),
                                                           workspace->paPrimitive->P2
                                                         );
    /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/FINISH/0002,1 */

    if (E_OK == result)
    {
      /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/FINISH/0003,1 */
      for (i = 0; i<CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_BLOCKSIZE; i++)
      {
        bf[i] = k0[i] ^ 0x5CU;
      }

      /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/FINISH/0004,1 */
      workspace->H2Len = CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_RESULTSIZE;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        =  bf;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     =  CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_BLOCKSIZE;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       =  workspace->H2;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &workspace->H2Len;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode            =  CRYPTO_OPERATIONMODE_STREAMSTART;

      CRYPTO_XVIX_XAIX_RESET_CALLBACK();
      primitive->P2->data->P1 = primitive;
      result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                            &(workspace->secondaryJob),
                                                             workspace->paPrimitive->P2
                                                           );
    }
  }

  if (E_OK == result)
  {
    /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/FINISH/0006,1 */
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr    = workspace->H1;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength = CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_RESULTSIZE;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode        = CRYPTO_OPERATIONMODE_UPDATE;

    CRYPTO_XVIX_XAIX_RESET_CALLBACK();
    primitive->P2->data->P1 = primitive;
    result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                          &(workspace->secondaryJob),
                                                           workspace->paPrimitive->P2
                                                         );
  }

  if (E_OK == result)
  {
    /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/FINISH/0008,1 */
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode = CRYPTO_OPERATIONMODE_FINISH;

    CRYPTO_XVIX_XAIX_RESET_CALLBACK();
    primitive->P2->data->P1 = primitive;
    result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                          &(workspace->secondaryJob),
                                                           workspace->paPrimitive->P2
                                                         );
    /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/FINISH/0009,1 */

    if (E_OK == result)
    {
      if ((CRYPTO_XVIX_XAIX_INT_CPR_MACVERIFY_SHA2512_HMAC_RESULTSIZE * 8U) >= job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputLength)
      {
        /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/FINISH/0010,2 */
        /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/FINISH/0011,2 */
        mask = (~((1U << (((uint8) 8U) - (job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputLength % 8U))) - 1U));

        /* if check of full bytes of number of bits to verify is okay, check also remaining bits in the following byte */
        if (E_OK == Crypto_xVIx_xAIx_MemCmpSec(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputPtr,
                                               workspace->H2,
                                               (job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputLength / 8U)
                                              )
           )
        {
          if (0x00U != mask)
          {
            if (   (job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputPtr[job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputLength / 8U] & mask)
                == (workspace->H2[job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputLength / 8U]                                                   & mask)
              )
            {
              resultVerify = CRYPTO_E_VER_OK;
            }
          }
          else
          {
            resultVerify = CRYPTO_E_VER_OK;
          }
        }
        /* !LINKSTO Crypto.Req.CPr/MACVERIFY_SHA2512_HMAC/FINISH/0012,2 */

        *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.verifyPtr) = resultVerify;
      }
      else
      {
        result = E_NOT_OK;
      }
    }
  }

  CRYPTO_XVIX_XAIX_SET_SMRESULT_SINGLECALL(result, sizeof(Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle ------------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveCancel2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_WorkspaceType);
  if (NULL_PTR != workspace->secondaryJob.jobInfo)
  {
    primitive->P2->data->P1 = primitive;
    if (E_OK == workspace->paPrimitive->P2->cnfg->description->fcnCancel( workspace->paObjectId,
                                                                         &(workspace->secondaryJob),
                                                                          workspace->paPrimitive->P2
                                                                        )
       )
    {
      workspace->notifyType = CRYPTO_XVIX_XAIX_CALLBACK_NONE;
      /* CHECK: NOPARSE
       * workspace->notifyType is set to CRYPTO_XVIX_XAIX_CALLBACK_NONE
       * do-while loop will be executed just once
       */
      do
      {
        (void) workspace->paPrimitive->P2->cnfg->description->fcnMain( workspace->paObjectId,
                                                                      &(workspace->secondaryJob),
                                                                       workspace->paPrimitive->P2
                                                                     );
      }
      while (CRYPTO_XVIX_XAIX_CALLBACK_CANCEL == workspace->notifyType);
      /* CHECK: PARSE */
    }
    primitive->P2->data->P1 = NULL_PTR;
  }

  /* !LINKSTO Crypto.Asr.SWS_Crypto_00183,2 */
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00144,1 */
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00181_1,1 */
  CRYPTO_XVIX_XAIX_SET_SMRESULT_CANCEL(CRYPTO_E_JOB_CANCELED, sizeof(Crypto_xVIx_xAIx_CPr_MACVERIFY_SHA2512_HMAC_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACVERIFY_SHA2512_HMAC == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[end of file]=================================================================*/

