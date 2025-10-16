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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_SIGNATUREGENERATE_ED25519_NOTSET.c/0001,1 */

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
 Deviated Rule: HIS_STMT
 * not 114 <= 75
 *
 * CODEMETRIC-2) Deviated Rule: HIS_STMT
 * not 116 <= 75
 *
 * Reason:
 * SingleCall functions are adjusted for performance and have a reduced amount of function calls
 * on purpose which leads to metric violations.
 *
 * CODEMETRIC-3) Deviated Rule: HIS_VOCF
 * not 16.50 <= 12
 *
 * CODEMETRIC-4) Deviated Rule: HIS_VOCF
 * not 16.32 <= 12
 *
 * Reason:
 * Improving this software quality metric is only possible by splitting up the function
 * which would adversely effect the performance of the primitive. For cryptographic algorithms,
 * a high number of operators/operands are needed for the implementation.
 *
, * CODEMETRIC-1) Deviated Rule: HIS_STMT
 * not 102 <= 75
 *
 * CODEMETRIC-2) Deviated Rule: HIS_STMT
 * not 100 <= 75
 *
 * Reason:
 * SingleCall functions are adjusted for performance and have a reduced amount of function calls
 * on purpose which leads to metric violations.
 *
 * CODEMETRIC-3) Deviated Rule: HIS_VOCF
 * not 15.47 <= 12
 *
 * CODEMETRIC-4) Deviated Rule: HIS_VOCF
 * not 15.03 <= 12
 *
 * Reason:
 * Improving this software quality metric is only possible by splitting up the function
 * which would adversely effect the performance of the primitive. For cryptographic algorithms,
 * a high number of operators/operands are needed for the implementation.
 *
) */

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int.h>                                           /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_SIGNATUREGENERATE_ED25519_NOTSET.c/0002,1 */
#include <Crypto_xVIx_xAIx_Int_KeyManagement.h>                             /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_SIGNATUREGENERATE_ED25519_NOTSET.c/0003,1 */
#include <Crypto_xVIx_xAIx_Int_CPr_SIGNATUREGENERATE_ED25519_NOTSET.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_SIGNATUREGENERATE_ED25519_NOTSET.c/0004,1 */

/*==================[macros]======================================================================*/

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT,1 */
#if (defined CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT)
#error CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT already defined
#endif
/** \brief  Number of entries in the primitives state transition table. **/
#define CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT 16U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT,1 */
#if (defined CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT)
#error CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT already defined
#endif
/** \brief  Number of entries in the primitives state action table. **/
#define CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT 16U

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

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE)
#error CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE already defined
#endif
/** \brief  The UpdateFinishIdle state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE 4U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_FINISHEXEC,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHEXEC)
#error CRYPTO_XVIX_XAIX_STATE_FINISHEXEC already defined
#endif
/** \brief  The FinishExec state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHEXEC 5U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSHASH)
#error CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSHASH already defined
#endif
/** \brief  The FinishProcessHash state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSHASH 6U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHHASH1)
#error CRYPTO_XVIX_XAIX_STATE_FINISHHASH1 already defined
#endif
/** \brief  The FinishHash1 state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHHASH1 7U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHCALCR)
#error CRYPTO_XVIX_XAIX_STATE_FINISHCALCR already defined
#endif
/** \brief  The FinishCalcR state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHCALCR 8U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSENCODER)
#error CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSENCODER already defined
#endif
/** \brief  The FinishProcessEncodeR state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSENCODER 9U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHHASHUPDATE)
#error CRYPTO_XVIX_XAIX_STATE_FINISHHASHUPDATE already defined
#endif
/** \brief  The FinishHashUpdate state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHHASHUPDATE 10U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHHASH2)
#error CRYPTO_XVIX_XAIX_STATE_FINISHHASH2 already defined
#endif
/** \brief  The FinishHash2 state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHHASH2 11U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSHASHRESULT)
#error CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSHASHRESULT already defined
#endif
/** \brief  The FinishProcessHashResult state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSHASHRESULT 12U

#if (defined CRYPTO_XVIX_XAIX_STATE_SINGLECALL)
#error CRYPTO_XVIX_XAIX_STATE_SINGLECALL already defined
#endif
/** \brief  The SingleCall state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_SINGLECALL 13U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_CANCEL,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_CANCEL)
#error CRYPTO_XVIX_XAIX_STATE_CANCEL already defined
#endif
/** \brief  The Cancel state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_CANCEL 14U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_ERROR,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_ERROR)
#error CRYPTO_XVIX_XAIX_STATE_ERROR already defined
#endif
/** \brief  The Error state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_ERROR 15U

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(boolean, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetNextState
(
  P2VAR(uint8,                                         AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) smStateIndx,
        Crypto_xVIx_xAIx_PrimitiveStateIdentifierType                                         curState,
        Std_ReturnType                                                                        resultAction,
        Crypto_ProcessingType                                                                 jobProcessing,
  P2VAR(Crypto_xVIx_xAIx_PrimitiveStateIdentifierType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) nxtState
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */
/* -----------------------------------------------------------------------------------------------*/
/* state action functions */

/** \brief  State action function for states
 **         'CRYPTO_XVIX_XAIX_STATE_STARTEXEC'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      Request successful.
 ** \retval  E_NOT_OK  Request failed.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/* -----------------------------------------------------------------------------------------------*/
/* state transition functions */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_STARTEXEC'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE'
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC
 **         to state   CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHEXEC'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSHASH'
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishProcessPubKey2FinishProcessHash
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSHASH'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHHASH1'
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishProcessHash2FinishHash
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHHASH1'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHCALCR'
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishHash2FinishCalcR
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHCALCR'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSENCODER'
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishCalcR2FinishEncodeR
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSENCODER'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHHASHUPDATE'
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishEncodeR2FinishHashUpdate
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHHASHUPDATE'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHHASH2'
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishHashUpdate2FinishHash
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHHASH2'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSHASHRESULT'.
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishHash2FinishProcessHashResult
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSHASHRESULT'
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishProcessHashResult2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/* ---misc procedures---------------------------------------------------------------------------- */

/** \brief  Update the message/message digest to the hash.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in,out]  workspace  Pointer to the primitives workspace instance.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_UpdateMsgDigest
(
    P2VAR(Crypto_JobType,                             AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
    P2VAR(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType,                                   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/** \brief  Helper function to read key and get the curve index.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns Error value.
 **
 ** \retval  E_OK                         Request successful.
 ** \retval  E_NOT_OK                     Request failed.
 ** \retval  CRYPTO_E_KEY_SIZE_MISMATCH   key element has the wrong size.
 ** \retval  CRYPTO_E_SMALL_BUFFER        Buffer too small to store the result.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetCurveIndex
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal constants]==========================================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  The primitives state transition table. **/

/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_StateTransitionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateTransitionType, CRYPTO_xVIx_xAIx_CONST)
Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Process_StateTransitionTable[CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT] =
{
  { NULL_PTR,                                                            CRYPTO_XVIX_XAIX_STATE_STARTIDLE,               CRYPTO_XVIX_XAIX_STATE_STARTIDLE,               CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE_TO_CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1               */
  { Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle,                  CRYPTO_XVIX_XAIX_STATE_STARTEXEC,               CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,              CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },

  { NULL_PTR,                                                            CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,              CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,              CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE_TO_CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE/0001,1             */
  {Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateFinishIdle,            CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC,              CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,        CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },

  { NULL_PTR,                                                            CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,        CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,        CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },

  { Crypto_xVIx_xAIx_StateMachine_FinishProcessPubKey2FinishProcessHash, CRYPTO_XVIX_XAIX_STATE_FINISHEXEC,     CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSHASH,       CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },
  { Crypto_xVIx_xAIx_StateMachine_FinishProcessHash2FinishHash,          CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSHASH,       CRYPTO_XVIX_XAIX_STATE_FINISHHASH1,             CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },

  { Crypto_xVIx_xAIx_StateMachine_FinishHash2FinishCalcR,                CRYPTO_XVIX_XAIX_STATE_FINISHHASH1,             CRYPTO_XVIX_XAIX_STATE_FINISHCALCR,             CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },
  { Crypto_xVIx_xAIx_StateMachine_FinishCalcR2FinishEncodeR,             CRYPTO_XVIX_XAIX_STATE_FINISHCALCR,             CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSENCODER,    CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },

  { Crypto_xVIx_xAIx_StateMachine_FinishEncodeR2FinishHashUpdate,        CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSENCODER,    CRYPTO_XVIX_XAIX_STATE_FINISHHASHUPDATE,        CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },
  { Crypto_xVIx_xAIx_StateMachine_FinishHashUpdate2FinishHash,           CRYPTO_XVIX_XAIX_STATE_FINISHHASHUPDATE,        CRYPTO_XVIX_XAIX_STATE_FINISHHASH2,             CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },
  { Crypto_xVIx_xAIx_StateMachine_FinishHash2FinishProcessHashResult,    CRYPTO_XVIX_XAIX_STATE_FINISHHASH2,             CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSHASHRESULT, CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },
  { Crypto_xVIx_xAIx_StateMachine_FinishProcessHashResult2StartIdle,     CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSHASHRESULT, CRYPTO_XVIX_XAIX_STATE_STARTIDLE,               CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },

  { Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle,                  CRYPTO_XVIX_XAIX_STATE_SINGLECALL,              CRYPTO_XVIX_XAIX_STATE_STARTIDLE,               CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },

  { Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle,                      CRYPTO_XVIX_XAIX_STATE_CANCEL,                  CRYPTO_XVIX_XAIX_STATE_STARTIDLE,               CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },
  { Crypto_xVIx_xAIx_StateMachine_Error2StartIdle,                       CRYPTO_XVIX_XAIX_STATE_ERROR,                   CRYPTO_XVIX_XAIX_STATE_STARTIDLE,               CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK }
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/** \brief  The primitives state action table. **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_StateActionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateActionType, CRYPTO_xVIx_xAIx_CONST)
Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Process_StateActionTable[CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT] =
{
  /* CRYPTO_XVIX_XAIX_STATE_STARTIDLE               */ { NULL_PTR                                }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1        */
  /* CRYPTO_XVIX_XAIX_STATE_STARTEXEC               */ { Crypto_xVIx_xAIx_StateMachine_StartExec }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTEXEC/0001,1        */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE              */ { NULL_PTR                                }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC              */ { NULL_PTR                                }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE        */ { NULL_PTR                                }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE/0001,1 */
  /* CRYPTO_XVIX_XAIX_STATE_FINISHEXEC              */ { NULL_PTR                                }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_FINISHEXEC/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSHASH       */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_FINISHHASH1             */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_FINISHCALCR             */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSENCODER    */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_FINISHHASHUPDATE        */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_FINISHHASH2             */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSHASHRESULT */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_SINGLECALL              */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_CANCEL                  */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_ERROR                   */ { NULL_PTR                                }
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Process ------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Process/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Process
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType);

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
    (void) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Reset(workspace->paObjectId, job, primitive);
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
        (void) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Main(objectId, job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Main ---------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Main/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Main
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType);

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
    if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Process_StateActionTable[curState].fcnAction))
    {
      resultAction = Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Process_StateActionTable[curState].fcnAction(job, primitive);
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
      if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Process_StateTransitionTable[smStateIndx].fcnTransition))
      {
        /* transition function returns using workspace->smResult */
        (void) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Process_StateTransitionTable[smStateIndx].fcnTransition(job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Cancel -------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Cancel/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Cancel
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType);

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
      (void) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Main(objectId, job, primitive);
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Reset --------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Reset/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Reset
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as
   * secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESET(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType));
    result = E_OK;
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Restart --------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Restart/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Restart
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESTART(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType));
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Callback -----------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Callback/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(objectId);
  TS_PARAM_UNUSED(job);
  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Callback/0002,1 */
  workspace->notifyType   = cbkType;
  workspace->notifyResult = cbkResult;

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_StateMachine_Error2StartIdle ----------------------------------------------*/

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveError2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType);

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
  result              = Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Reset(workspace->paObjectId, job, primitive);
  workspace->smResult = smResult;

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_GetNextState --------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
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
    if (   (Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx   = i;
      break;
    }
  }

  /* CHECK: NOPARSE
   * The FOR loop condition (i < *smStateIndx) is always FALSE for SIGNATUREGENERATE_ED25519_NOTSET, because the state
   * transition table of this cryptographic primitive is complete, except for the case when the
   * CRYPTO_XVIX_XAIX_STATE_STARTEXEC returns an action result of not E_OK. In this case the
   * previous FOR loop always iterates from i = 0 to CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT.
   */
  /* 2) iterate from first table entry to last found entry in table */
  for (i = 0U; (FALSE == nxtStateFound) && (i < *smStateIndx); i++)
  {
    if (   (Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx  = i;
      break;
    }
  }
  /* CHECK: PARSE */

  return nxtStateFound;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */
/* --- Crypto_xVIx_xAIx_StateMachine_StartExec -------------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  Std_ReturnType result            = E_NOT_OK;
  uint8          curveIndex        = 0U;
  boolean        fromPrimitive     = FALSE;
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType);

  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) key;

  TS_PARAM_UNUSED(primitive);

  /* !LINKSTO Crypto.Asr.SWS_Crypto_00193,1 */
  result = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( job->cryptoKeyId,
                                                      CRYPTO_KE_SIGNATURE_KEY,
                                                     &(key),
                                                      FALSE,
                                                      CRYPTO_XVIX_XAIX_SID_EMPTY
                                                    );

  if (E_OK == result)
  {
    fromPrimitive = TRUE;
    /* Deviation TASKING-1 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(result, key, fromPrimitive);
  }

  if (E_OK == result)
  {
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_ED25519_NOTSET/GENERAL/0018,2 */
    if (CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_PRIVATEKEY_LENGTH != key->data->size)
    {
      workspace->smResult         = CRYPTO_E_KEY_SIZE_MISMATCH;
      workspace->smOperationDone |= CRYPTO_OPERATIONMODE_START;
      result                      = E_NOT_OK;
    }
    else
    {
      /* Get the index of the used curve */
      /* The function can only return E_OK here. */
      (void)Crypto_xVIx_xAIx_GetECIndex( job->jobPrimitiveInfo->primitiveInfo->service,
                                         job->jobPrimitiveInfo->primitiveInfo->algorithm.family,
                                         NULL_PTR,
                                         0U,
                                        &curveIndex
                                       );

      workspace->edCtx.curveIndex  = curveIndex;
      /* The private key is the first 32 bytes of the key element */
      workspace->tmp1ArrayLength   = CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_BYTEARRAY_LENGTH;
      TS_MemCpy(workspace->tmp1Array, key->data->data, CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_BYTEARRAY_LENGTH);

      /* The public key is the last 32 bytes of the key element */
      TS_MemCpy(workspace->tmp2Array,
                &key->data->data[CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_BYTEARRAY_LENGTH],
                CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_BYTEARRAY_LENGTH
               );

      result = E_OK;
    }
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(key);
  }
  else
  {
    workspace->smResult         = result;
    workspace->smOperationDone |= CRYPTO_OPERATIONMODE_START;
  }
  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle --------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Start2Update,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  Std_ReturnType result = E_NOT_OK;
  uint8 bitset = 1U;
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType);

  /* create secondary job */
  CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB();
  CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_KEY();
  CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_SRV();

  /* set the hash result Length */
  workspace->hashResultLength = CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_HASH_LENGTH;
  /* Hash the private key */
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        = workspace->tmp1Array;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     = workspace->tmp1ArrayLength;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       = workspace->hashResult;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &workspace->hashResultLength;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode            = CRYPTO_OPERATIONMODE_SINGLECALL;

  /* start secondary primitive (hash sha2 512) */

  CRYPTO_XVIX_XAIX_RESET_CALLBACK();
  primitive->P2->data->P1 = primitive;
  result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                        &(workspace->secondaryJob),
                                                         workspace->paPrimitive->P2
                                                       );

  if (E_OK == result)
  {
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_ED25519_NOTSET/GENERAL/0012,1 */
    /* Construct the secret scalar s from the first half of the hash digest */
    /* clear the first 3 bits */
    workspace->hashResult[0U] &= (uint8)0xf8U;

    /* clear the highest bit of the last octet from the first hash half */
    workspace->hashResult[31U] = workspace->hashResult[31U] & (~(bitset <<7U));

    /* set the second highest bit of the final octet from the first hash half */
    workspace->hashResult[31U] |= (uint8)((uint8)1U << (uint8)6U);

    /* Set the expected length of the Long Number before converting the bytearray to a little-endian integer */
    workspace->scalar2[0U] = CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_NUM_LEN_WORDS;

    /* The return value is ignored because the parameters are either from the context where they are
     * properly defined or local variables which are properly defined before passing them to the function.
     */
    (void)Crypto_xVIx_xAIx_LNLEByteArrayToNumber(
                                                  workspace->hashResult,
                                                  (CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_HASH_LENGTH >> 1U),
                                                  workspace->scalar2,
                                                  workspace->scalar2[0U]
                                                );
  }

  CRYPTO_XVIX_XAIX_SET_SMRESULT_START(result, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateFinishIdle -------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Update2Finish,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(job);
  TS_PARAM_UNUSED(primitive);

  CRYPTO_XVIX_XAIX_SET_SMRESULT_UPDATE(workspace->smResult, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishProcessPubKey2FinishProcessHash ---------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishProcessPubKey2FinishProcessHash
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(job);

    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode = CRYPTO_OPERATIONMODE_START;
    primitive->P2->data->P1                                               = primitive;

    /* Start secondary primitive */
    result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                          &(workspace->secondaryJob),
                                                          workspace->paPrimitive->P2
                                                        );

  if (E_OK == result)
  {

    /* Update the Hashfunction h_b to h_(2*b-1) */
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr     = &(workspace->hashResult[CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_HASH_LENGTH >> 1U]);
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength  = (CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_HASH_LENGTH >> 1U);
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode         = CRYPTO_OPERATIONMODE_UPDATE;
    /* Hash the input using the secondary primitive UPDATE. This call shall never fail because
     * the buffers and their sizes are set to valid values before this call.
     */
    (void) primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                        &(workspace->secondaryJob),
                                                         workspace->paPrimitive->P2
                                                       );
  }

  workspace->smResult = result;
  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishProcessHash2FinishHash ------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishProcessHash2FinishHash
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  Std_ReturnType result = E_NOT_OK;

  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(job);

  Crypto_xVIx_xAIx_Procedure_UpdateMsgDigest(job,workspace, primitive);

  /* Finish the secondary primitive */
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       = workspace->hashResult;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &workspace->hashResultLength;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode            = CRYPTO_OPERATIONMODE_FINISH;

  CRYPTO_XVIX_XAIX_RESET_CALLBACK();
  result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                        &(workspace->secondaryJob),
                                                         workspace->paPrimitive->P2
                                                       );

  workspace->smResult = result;
  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishHash2FinishCalcR ------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishHash2FinishCalcR
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(primitive);

  if (CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_SIGN_LENGTH > *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr))
  {
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_ED25519_NOTSET/GENERAL/0010,1 */

    workspace->smResult         = CRYPTO_E_SMALL_BUFFER;
    workspace->smOperationDone |= CRYPTO_OPERATIONMODE_FINISH;
  }
  else
  {
    /* scalar r to LN */
    /* This call can never fail because we have enough memory allocated in the context
     * to store the byte representation of the LN. */
    (void)Crypto_xVIx_xAIx_LNLEByteArrayToNumber(workspace->hashResult,
                                                 workspace->hashResultLength,
                                                 workspace->scalar1,
                                                 CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_TEMP_LEN_WORDS
                                                );
    /* r = r mod lValue */
    Crypto_xVIx_xAIx_LNModulo(workspace->scalar1,
                              Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->edCtx.curveIndex].modulus,
                              &workspace->edCtx.lnCtx
                             );

    /* R = r * basePoint */
    Crypto_xVIx_xAIx_Procedure_EdDSAPointMultiplication(&(workspace->point1),
                                                        &(Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->edCtx.curveIndex].basePoint),
                                                        workspace->scalar1,
                                                        workspace->tmp,
                                                        &(workspace->edCtx)
                                                       );
  }

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishCalcR2FinishEncodeR ---------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishCalcR2FinishEncodeR
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  uint32 length   = CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_BYTEARRAY_LENGTH;

  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(primitive);
  TS_PARAM_UNUSED(job);

  /* converting the point to a byte array and encoding it for the HashUpdate function */
  Crypto_xVIx_xAIx_Procedure_EccPointConvertProj2Aff(&(workspace->point1),
                                                     workspace->tmp,
                                                     &(workspace->edCtx)
                                                    );

  /* Encode the point */
  /* convert the yValue in little endian byte array */
  /* Call shall never fail because we have enough memory allocated in the context
   * to store the byte representation of the LN. */
  (void)Crypto_xVIx_xAIx_LNNumberToLEByteArray(workspace->point1.yValue,
                                               workspace->tmp1Array,
                                               &length
                                              );

  /* Call shall never fail because we have enough memory allocated in the context
   * to store the byte representation of the LN. */
  (void) Crypto_xVIx_xAIx_LNNumberToLEByteArray(workspace->point1.xValue,
                                                workspace->tmp3Array,
                                                &length
                                               );
  /* the least significant bit of the x-coordinate */
  workspace->edCtx.x0 = (uint8)(workspace->tmp3Array[0U] & (uint8)0x01U);

  if((uint8)0U != workspace->edCtx.x0)
  {
    workspace->tmp1Array[CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_BYTEARRAY_LENGTH - 1U] |= (uint8)((uint8)workspace->edCtx.x0 << 7U);
  }

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishEncodeR2FinishHashUpdate ---------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishEncodeR2FinishHashUpdate
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(job);

  /* start Hash(ENC(R) || ENC(A) || PH(M)) */
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode = CRYPTO_OPERATIONMODE_START;
  primitive->P2->data->P1                                 = primitive;

  /* Start secondary primitive */
  result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                        &(workspace->secondaryJob),
                                                         workspace->paPrimitive->P2
                                                       );

  if (E_OK == result)
  {

    /* Update ENC(R) : tmp1Array */
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr     = workspace->tmp1Array;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength  = CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_BYTEARRAY_LENGTH;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode         = CRYPTO_OPERATIONMODE_UPDATE;

    /* Hash the input using the secondary primitive UPDATE. This call shall never fail because
     * the buffers and their sizes are set to valid values before this call.
     */
    (void) primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                        &(workspace->secondaryJob),
                                                         workspace->paPrimitive->P2
                                                       );

    /* Update ENC(A) : tmp2Array */
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr     = workspace->tmp2Array;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength  = CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_BYTEARRAY_LENGTH;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode         = CRYPTO_OPERATIONMODE_UPDATE;

    /* Hash the input using the secondary primitive UPDATE. This call shall never fail because
     * the buffers and their sizes are set to valid values before this call.
     */
    (void) primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                        &(workspace->secondaryJob),
                                                         workspace->paPrimitive->P2
                                                       );
  }

  workspace->smResult = result;
  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishHashUpdate2FinishHash ------------------------------------ */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishHashUpdate2FinishHash
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  Std_ReturnType result = E_NOT_OK;

  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(job);

  Crypto_xVIx_xAIx_Procedure_UpdateMsgDigest(job,workspace, primitive);

  /* Finish the secondary primitive */
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       = workspace->hashResult;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &workspace->hashResultLength;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode            = CRYPTO_OPERATIONMODE_FINISH;

  CRYPTO_XVIX_XAIX_RESET_CALLBACK();
  result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                        &(workspace->secondaryJob),
                                                         workspace->paPrimitive->P2
                                                       );

  workspace->smResult = result;
  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishHash2FinishProcessHashResult ----------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishHash2FinishProcessHashResult
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(job);
  TS_PARAM_UNUSED(primitive);

  /* This call can never fail because we have enough memory allocated in the context
   * to store the byte representation of the LN. */
  (void)Crypto_xVIx_xAIx_LNLEByteArrayToNumber(workspace->hashResult,
                                               workspace->hashResultLength,
                                               &workspace->tmp[CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_TEMP_LEN_WORDS],
                                               CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_TEMP_LEN_WORDS
                                              );

  /* Tmp1 = HashResult % LValue */
  Crypto_xVIx_xAIx_LNModulo(&workspace->tmp[CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_TEMP_LEN_WORDS],
                            Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->edCtx.curveIndex].modulus,
                            &workspace->edCtx.lnCtx
                            );

  /* Tmp1 = HashResult * Scalar s */
  Crypto_xVIx_xAIx_LNMultiplyNumbers(&workspace->tmp[CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_TEMP_LEN_WORDS],
                                     &workspace->tmp[CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_TEMP_LEN_WORDS],
                                     workspace->scalar2,
                                     &workspace->edCtx.lnCtx
                                    );

  /* Tmp1 = (HashResult * Scalar s) % LValue */
  Crypto_xVIx_xAIx_LNModulo(&workspace->tmp[CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_TEMP_LEN_WORDS],
                            Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->edCtx.curveIndex].modulus,
                            &workspace->edCtx.lnCtx
                           );

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishProcessHashResult2StartIdle -------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Finish2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishProcessHashResult2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType);
  uint32 length         = CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_BYTEARRAY_LENGTH;
  uint8 ret = E_NOT_OK;
  TS_PARAM_UNUSED(primitive);

  /* Tmp2: s = (Scalar r + (HashResult * Scalar s)) % LValue */
  Crypto_xVIx_xAIx_LNAdditionModular(&workspace->tmp[2U * CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_TEMP_LEN_WORDS],
                                     workspace->scalar1,
                                     &workspace->tmp[CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_TEMP_LEN_WORDS],
                                     Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->edCtx.curveIndex].modulus
                                    );

  /* ENC(R): tmp1Array - Little endian byte Array */
  TS_MemCpy(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr,
            workspace->tmp1Array,
            CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_BYTEARRAY_LENGTH
           );

  /* S: Tmp2 in little endian byte array */
  /* The return value is ignored because the parameters are either from the context where they are
     properly defined or local variables which are properly defined before passing them to
     the function.*/
  (void)Crypto_xVIx_xAIx_LNNumberToLEByteArray(&workspace->tmp[2U * CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_TEMP_LEN_WORDS],
                                               &job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr[length],
                                               &length
                                              );
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00135,1 */
  *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr) = (length << 1U);
  ret = E_OK;
  /* Deviation TASKING-1 */
  CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH(ret, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType));

  return ret;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_GetCurveIndex --------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetCurveIndex
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  Std_ReturnType result            = E_NOT_OK;
  uint8          curveIndex        = 0U;
  boolean        fromPrimitive     = FALSE;
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType);

  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) key;

  /* !LINKSTO Crypto.Asr.SWS_Crypto_00193,1 */
  result = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( job->cryptoKeyId,
                                                      CRYPTO_KE_SIGNATURE_KEY,
                                                     &(key),
                                                      FALSE,
                                                      CRYPTO_XVIX_XAIX_SID_EMPTY
                                                    );

  if (E_OK == result)
  {
    fromPrimitive = TRUE;
    /* Deviation TASKING-1 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(result, key, fromPrimitive);
  }

  if (E_OK == result)
  {
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_ED25519_NOTSET/GENERAL/0018,2 */
    if (CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_PRIVATEKEY_LENGTH != key->data->size)
    {
      result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else
    {
      if (CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_SIGN_LENGTH > *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr))
      {
        /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_ED25519_NOTSET/GENERAL/0010,1 */

        result = CRYPTO_E_SMALL_BUFFER;
      }
      else
      {
        /* Get the index of the used curve */
        /* The function can only return E_OK here. */
        (void)Crypto_xVIx_xAIx_GetECIndex( job->jobPrimitiveInfo->primitiveInfo->service,
                                           job->jobPrimitiveInfo->primitiveInfo->algorithm.family,
                                           NULL_PTR,
                                           0U,
                                          &curveIndex
                                        );

        workspace->edCtx.curveIndex  = curveIndex;
        /* !LINKSTO Crypto.Asr.SWS_Crypto_00193,1 */
        /* The private key is the first 32 bytes of the key element */
        workspace->tmp1ArrayLength   = CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_BYTEARRAY_LENGTH;
        TS_MemCpy(workspace->tmp1Array, key->data->data, CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_BYTEARRAY_LENGTH);

        /* The public key is the last 32 bytes of the key element */
        TS_MemCpy(workspace->tmp2Array,
                  &key->data->data[CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_BYTEARRAY_LENGTH],
                  CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_BYTEARRAY_LENGTH
                );
      }
    }
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(key);
  }
  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle --------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
/* Deviation CODEMETRIC-1, CODEMETRIC-2, CODEMETRIC-3, CODEMETRIC-4 */
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  Std_ReturnType result     = E_NOT_OK;
  uint32         length     = CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_BYTEARRAY_LENGTH;
  uint8 bitreset = 1U;
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType);

  result =  Crypto_xVIx_xAIx_GetCurveIndex(job, primitive);

  if (E_OK == result)
  {
    /* create secondary job */
    CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB();
    CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_KEY();
    CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_SRV();

    /* set the hash result Length */
    workspace->hashResultLength = CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_HASH_LENGTH;
    /* Hash the private key */
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        = workspace->tmp1Array;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     = workspace->tmp1ArrayLength;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       = workspace->hashResult;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &workspace->hashResultLength;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode            = CRYPTO_OPERATIONMODE_SINGLECALL;

    CRYPTO_XVIX_XAIX_RESET_CALLBACK();
    primitive->P2->data->P1 = primitive;
    result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                          &(workspace->secondaryJob),
                                                           workspace->paPrimitive->P2
                                                         );

    if (E_OK == result)
    {
      /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_ED25519_NOTSET/GENERAL/0012,1 */
      /* Construct the secret scalar s from the first half of the hash digest */
      /* clear the first 3 bits */
      workspace->hashResult[0U] &= (uint8)0xf8U;

      /* clear the highest bit of the last octet from the first hash half */
      workspace->hashResult[31U] = workspace->hashResult[31U] & (~(bitreset << 7U));

      /* set the second highest bit of the final octet from the first hash half */
      workspace->hashResult[31U] = workspace->hashResult[31U] |(bitreset << 6U);

      /* Set the expected length of the Long Number before converting the bytearray to a little-endian integer */
      workspace->scalar2[0U] = CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_NUM_LEN_WORDS;

      /* The return value is ignored because the parameters are either from the context where they are
        properly defined or local variables which are properly defined before passing them to the function.*/
      (void)Crypto_xVIx_xAIx_LNLEByteArrayToNumber(workspace->hashResult,
                                                   (CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_HASH_LENGTH >> 1U),
                                                   workspace->scalar2,
                                                   workspace->scalar2[0U]
                                                  );

      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode          = CRYPTO_OPERATIONMODE_START;

      /* Start secondary primitive */
      primitive->P2->data->P1 = primitive;
      result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                            &(workspace->secondaryJob),
                                                             workspace->paPrimitive->P2
                                                           );
    }

    if (E_OK == result)
    {

      /* Update the Hashfunction h_b to h_(2*b-1) */
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr     = &(workspace->hashResult[CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_HASH_LENGTH >> 1U]);
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength  = (CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_HASH_LENGTH >> 1U);
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode         = CRYPTO_OPERATIONMODE_UPDATE;
      /* Hash the input using the secondary primitive UPDATE. This call shall never fail because
       * the buffers and their sizes are set to valid values before this call.
       */
      (void) primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                          &(workspace->secondaryJob),
                                                           workspace->paPrimitive->P2
                                                         );
      Crypto_xVIx_xAIx_Procedure_UpdateMsgDigest(job,workspace, primitive);

      /* Finish the secondary primitive */
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       = workspace->hashResult;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &workspace->hashResultLength;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode            = CRYPTO_OPERATIONMODE_FINISH;

      CRYPTO_XVIX_XAIX_RESET_CALLBACK();
      result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                            &(workspace->secondaryJob),
                                                             workspace->paPrimitive->P2
                                                           );

      workspace->smResult = result;
    }

    if (E_OK == result)
    {
      /* scalar r to LN */
      /* This call can never fail because we have enough memory allocated in the context
        * to store the byte representation of the LN. */
      (void)Crypto_xVIx_xAIx_LNLEByteArrayToNumber(workspace->hashResult,
                                                    workspace->hashResultLength,
                                                    workspace->scalar1,
                                                    CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_TEMP_LEN_WORDS
                                                  );
      /* r = r mod lValue */
      Crypto_xVIx_xAIx_LNModulo(workspace->scalar1,
                                Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->edCtx.curveIndex].modulus,
                                &workspace->edCtx.lnCtx
                                );

      /* R = r * basePoint */
      Crypto_xVIx_xAIx_Procedure_EdDSAPointMultiplication(&(workspace->point1),
                                                          &(Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->edCtx.curveIndex].basePoint),
                                                          workspace->scalar1,
                                                          workspace->tmp,
                                                          &(workspace->edCtx)
                                                         );

      /* converting the point to a byte array and encoding it for the HashUpdate function */
      Crypto_xVIx_xAIx_Procedure_EccPointConvertProj2Aff(&(workspace->point1),
                                                          workspace->tmp,
                                                          &(workspace->edCtx)
                                                        );

      /* Encode the point */
      /* convert the yValue in little endian byte array */
      /* Call shall never fail because we have enough memory allocated in the context
        * to store the byte representation of the LN. */
      (void)Crypto_xVIx_xAIx_LNNumberToLEByteArray(workspace->point1.yValue,
                                                   workspace->tmp1Array,
                                                   &length
                                                  );

      /* Call shall never fail because we have enough memory allocated in the context
        * to store the byte representation of the LN. */
      (void) Crypto_xVIx_xAIx_LNNumberToLEByteArray(workspace->point1.xValue,
                                                    workspace->tmp3Array,
                                                    &length
                                                   );
      /* the least significant bit of the x-coordinate */
      workspace->edCtx.x0 = (uint8)(workspace->tmp3Array[0U] & (uint8)0x01U);

      if((uint8)0U != workspace->edCtx.x0)
      {
        workspace->tmp1Array[(CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_BYTEARRAY_LENGTH) - 1U] |= (uint8)((uint8)workspace->edCtx.x0 << 7U);
      }

      /* start Hash(ENC(R) || ENC(A) || PH(M)) */
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode = CRYPTO_OPERATIONMODE_START;
      primitive->P2->data->P1                                               = primitive;

      /* Start secondary primitive */
      result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                            &(workspace->secondaryJob),
                                                             workspace->paPrimitive->P2
                                                           );
    }

    if (E_OK == result)
    {

      /* Update ENC(R) : tmp1Array */
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr     = workspace->tmp1Array;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength  = CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_BYTEARRAY_LENGTH;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode         = CRYPTO_OPERATIONMODE_UPDATE;

      /* Hash the input using the secondary primitive UPDATE. This call shall never fail because
       * the buffers and their sizes are set to valid values before this call.
       */
      (void) primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                          &(workspace->secondaryJob),
                                                           workspace->paPrimitive->P2
                                                         );

      /* Update ENC(A) : tmp2Array */
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr     = workspace->tmp2Array;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength  = CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_BYTEARRAY_LENGTH;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode         = CRYPTO_OPERATIONMODE_UPDATE;

      /* Hash the input using the secondary primitive UPDATE. This call shall never fail because
       * the buffers and their sizes are set to valid values before this call.
       */
      (void) primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                          &(workspace->secondaryJob),
                                                           workspace->paPrimitive->P2
                                                         );
      Crypto_xVIx_xAIx_Procedure_UpdateMsgDigest(job,workspace, primitive);

      /* Finish the secondary primitive */
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       = workspace->hashResult;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &workspace->hashResultLength;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode            = CRYPTO_OPERATIONMODE_FINISH;

      CRYPTO_XVIX_XAIX_RESET_CALLBACK();
      result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                            &(workspace->secondaryJob),
                                                             workspace->paPrimitive->P2
                                                           );

    }

    if (E_OK == result)
    {
      /* This call can never fail because we have enough memory allocated in the context
      * to store the byte representation of the LN. */
      (void)Crypto_xVIx_xAIx_LNLEByteArrayToNumber(workspace->hashResult,
                                                   workspace->hashResultLength,
                                                   &workspace->tmp[CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_TEMP_LEN_WORDS],
                                                   CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_TEMP_LEN_WORDS
                                                  );
      /* Tmp1 = HashResult % LValue */
      Crypto_xVIx_xAIx_LNModulo(&workspace->tmp[CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_TEMP_LEN_WORDS],
                                Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->edCtx.curveIndex].modulus,
                                &workspace->edCtx.lnCtx
                               );

      /* Tmp1 = HashResult * Scalar s */
      Crypto_xVIx_xAIx_LNMultiplyNumbers(&workspace->tmp[CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_TEMP_LEN_WORDS],
                                         &workspace->tmp[CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_TEMP_LEN_WORDS],
                                         workspace->scalar2,
                                         &workspace->edCtx.lnCtx
                                        );

      /* Tmp1 = (HashResult * Scalar s) % LValue */
      Crypto_xVIx_xAIx_LNModulo(&workspace->tmp[CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_TEMP_LEN_WORDS],
                                Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->edCtx.curveIndex].modulus,
                                &workspace->edCtx.lnCtx
                               );

      /* Tmp2: s = (Scalar r + (HashResult * Scalar s)) % LValue */
      Crypto_xVIx_xAIx_LNAdditionModular(&workspace->tmp[2U * CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_TEMP_LEN_WORDS],
                                         workspace->scalar1,
                                         &workspace->tmp[CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_TEMP_LEN_WORDS],
                                         Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->edCtx.curveIndex].modulus
                                        );

      /* ENC(R): tmp1Array - Little endian byte Array */
      TS_MemCpy(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr,
                workspace->tmp1Array,
                CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_BYTEARRAY_LENGTH
               );

      /* S: Tmp2 in little endian byte array */
      /* The return value is ignored because the parameters are either from the context where they are
       * properly defined or local variables which are properly defined before passing them to the function.
       */
      (void)Crypto_xVIx_xAIx_LNNumberToLEByteArray(&workspace->tmp[2U * CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_ED25519_NOTSET_TEMP_LEN_WORDS],
                                                   &job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr[length],
                                                   &length
                                                  );
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00135,1 */
      *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr) = (length << 1U);
    }
  }

  CRYPTO_XVIX_XAIX_SET_SMRESULT_SINGLECALL(result, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle ------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType);
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
  CRYPTO_XVIX_XAIX_SET_SMRESULT_CANCEL(CRYPTO_E_JOB_CANCELED, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_Procedure_UpdateMsgDigest ----------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_UpdateMsgDigest
(
    P2VAR(Crypto_JobType,                             AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
    P2VAR(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_ED25519_NOTSET_WorkspaceType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType,                                   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  /* Update the hashfunction, PH(M) */
  /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_ED25519_NOTSET/GENERAL/0014,1 */
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode            = CRYPTO_OPERATIONMODE_UPDATE;
  /* Hash the input using the secondary primitive UPDATE. This call shall never fail because
   * the buffers and their sizes are set to valid values before this call.
   */
  (void) primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                      &(workspace->secondaryJob),
                                                       workspace->paPrimitive->P2
                                                     );
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_ED25519_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[end of file]=================================================================*/

