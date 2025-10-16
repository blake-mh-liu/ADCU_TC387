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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_SIGNATUREVERIFY_ED25519_NOTSET.c/0001,1 */

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
 * CODEMETRIC-1) Deviated Rule: HIS_STMT
 * not 82 <= 75
 *
 * Reason:
 * SingleCall functions are adjusted for performance and have a reduced amount of function calls
 * on purpose which leads to metric violations.
*
 */

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int.h>                                         /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_SIGNATUREVERIFY_ED25519_NOTSET.c/0002,1 */
#include <Crypto_xVIx_xAIx_Int_KeyManagement.h>                           /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_SIGNATUREVERIFY_ED25519_NOTSET.c/0003,1 */
#include <Crypto_xVIx_xAIx_Int_CPr_SIGNATUREVERIFY_ED25519_NOTSET.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_SIGNATUREVERIFY_ED25519_NOTSET.c/0004,1 */

/*==================[macros]======================================================================*/

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT,1 */
#if (defined CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT)
#error CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT already defined
#endif
/** \brief  Number of entries in the primitives state transition table. **/
#define CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT 20U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT,1 */
#if (defined CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT)
#error CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT already defined
#endif
/** \brief  Number of entries in the primitives state action table. **/
#define CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT 20U

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

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHDECODEPK1)
#error CRYPTO_XVIX_XAIX_STATE_FINISHDECODEPK1 already defined
#endif
/** \brief  The FinishDecodePK1 state of the primitive.. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHDECODEPK1 6U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHDECODEPK2)
#error CRYPTO_XVIX_XAIX_STATE_FINISHDECODEPK2 already defined
#endif
/** \brief  The FinishDecodePK2 state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHDECODEPK2 7U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHDECODEPK)
#error CRYPTO_XVIX_XAIX_STATE_FINISHDECODEPK already defined
#endif
/** \brief  The FinishDecodePKFinish state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHDECODEPK 8U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATES)
#error CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATES already defined
#endif
/** \brief  The FinishValidS state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATES 9U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATER1)
#error CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATER1 already defined
#endif
/** \brief  The FinishValidateR1 state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATER1 10U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATER2)
#error CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATER2 already defined
#endif
/** \brief  The FinishValidateR2 state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATER2 11U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATER)
#error CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATER already defined
#endif
/** \brief  The FinishValidateR state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATER 12U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHHASHUPDATE)
#error CRYPTO_XVIX_XAIX_STATE_FINISHHASHUPDATE already defined
#endif
/** \brief  The FinishHashUpdate state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHHASHUPDATE 13U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHHASH)
#error CRYPTO_XVIX_XAIX_STATE_FINISHHASH already defined
#endif
/** \brief  The FinishHash state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHHASH 14U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHSIG1)
#error CRYPTO_XVIX_XAIX_STATE_FINISHSIG1 already defined
#endif
/** \brief  The FinishSig1 state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHSIG1 15U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHSIG2)
#error CRYPTO_XVIX_XAIX_STATE_FINISHSIG2 already defined
#endif
/** \brief  The FinishSig2 state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHSIG2 16U

#if (defined CRYPTO_XVIX_XAIX_STATE_SINGLECALL)
#error CRYPTO_XVIX_XAIX_STATE_SINGLECALL already defined
#endif
/** \brief  The SingleCall state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_SINGLECALL 17U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_CANCEL,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_CANCEL)
#error CRYPTO_XVIX_XAIX_STATE_CANCEL already defined
#endif
/** \brief  The Cancel state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_CANCEL 18U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_ERROR,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_ERROR)
#error CRYPTO_XVIX_XAIX_STATE_ERROR already defined
#endif
/** \brief  The Error state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_ERROR 19U

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(boolean, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetNextState
(
  P2VAR(uint8,                                         AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) smStateIndx,
        Crypto_xVIx_xAIx_PrimitiveStateIdentifierType                                         curState,
        Std_ReturnType                                                                        resultAction,
        Crypto_ProcessingType                                                                 jobProcessing,
  P2VAR(Crypto_xVIx_xAIx_PrimitiveStateIdentifierType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) nxtState
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHEXEC'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHDECODEPK1'
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishDecodePK1
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHDECODEPK1'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHDECODEPK2'
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishDecodePK12FinishDecodePK2
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHDECODEPK2'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHDECODEPK'
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishDecodePK22FinishDecodePK3
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHDECODEPK'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATES'
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishDecodePK32FinishValidateS
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATES'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATER1'
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishValidateS2FinishValidateR1
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATER1'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATER2'
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishValidateR12FinishValidateR2
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATER2'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATER'.
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishValidateR22FinishValidateR
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATER'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHHASHUPDATE'.
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishValidateR32FinishHashUpdate
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHHASHUPDATE'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHHASH'.
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishHashUpdate2FinishHash
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHHASH'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHSIG1'.
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishHash2FinishProcessSig1
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHSIG1'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHSIG2'.
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishProcessSig12FinishProcessSig2
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHSIG2'
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishProcessSig22StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* ---misc procedures---------------------------------------------------------------------------- */

/** \brief  Update the message digest to the hash.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in,out]  workspace  Pointer to the primitives workspace instance.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      request successful
 ** \retval  E_NOT_OK  request failed
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_UpdateMsgDigest
(
    P2VAR(Crypto_JobType,                             AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
    P2VAR(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType,                                 AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/** \brief Point decoding.
 **
 **        This function decodes a given byte-array in a Point on edwards curve.
 **        The result is in projective coordinates.
 **
 ** \param[out]    result   Pointer to an edwards curve point where the result of the
 **                         decoding will be stored in projective coordinates.
 ** \param[in]     value    Pointer to a byte-array, which shall be decode to a point.
 ** \param[in,out] tmp      Pointer to a buffer which is used as temporary storage during the decoding.
 ** \param[in]     edCtx    Pointer the the context.
 **
 ** \returns Error value.
 **
 ** \retval E_OK      The yValue of the point is valid.
 ** \retval E_NOT_OK  The decoding is failed. The yValue of the point is invalid.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_EdDSAPointDecoding
(
  P2VAR(Crypto_xVIx_xAIx_ECPointType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) point,
  P2VAR(uint8,                         AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/** \brief Sub function of Pointdecoding.
 **
 **        This sub function calculates a part of decoding.
 **
 ** \param[in,out] tmp      Pointer to a buffer which is used as temporary storage during the decoding.
 ** \param[in]     edCtx    Pointer the the context.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingUV3
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/** \brief Sub function of Pointdecoding.
 **
 **        This sub function calculates a part of decoding.
 **
 ** \param[in,out] tmp      Pointer to a buffer which is used as temporary storage during the decoding.
 ** \param[in]     edCtx    Pointer the the context.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingUV7
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/** \brief Sub function of Pointdecoding.
 **
 **        This sub function calculates a part of decoding.
 **
 ** \param[in,out] tmp      Pointer to a buffer which is used as temporary storage during the decoding.
 ** \param[in]     edCtx    Pointer the the context.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingUV7Power
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/** \brief Sub function of Pointdecoding.
 **
 **        This sub function calculates a part of decoding.
 **
 ** \param[in,out] point    Pointer to a point where the result of the decoding will be stored in
 *                          projective coordinates.
 ** \param[in,out] tmp      Pointer to a buffer which is used as temporary storage during the decoding.
 ** \param[in]     edCtx    Pointer the the context.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingEQ1
(
  P2VAR(Crypto_xVIx_xAIx_ECPointType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) point,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/** \brief Sub function of Pointdecoding.
 **
 **        This sub function calculates a part of decoding.
 **
 ** \param[in,out] point    Pointer to a point where the result of the decoding will be stored in
 *                          projective coordinates.
 ** \param[in,out] tmp      Pointer to a buffer which is used as temporary storage during the decoding.
 ** \param[in]     edCtx    Pointer the the context.
 **
 ** \returns Error value.
 **
 ** \retval E_OK      The decoding is successful. Now, "point" contains the result
 **                   of the decoding in projektive coordinate.
 ** \retval E_NOT_OK  The decoding is failed. No square root exists.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingEQ2
(
  P2VAR(Crypto_xVIx_xAIx_ECPointType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) point,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/** \brief  Helper function to read key and get the curve index.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns Error value.
 **
 ** \retval  E_OK                        Request successful.
 ** \retval  E_NOT_OK                    Request failed.
 ** \retval  CRYPTO_E_KEY_SIZE_MISMATCH  Key element has the wrong size.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetCurveIndex
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/** \brief  Helper function to execute the Pointdecoding sub functions.
 **
 ** \param[in]      point      Boolean type flag to check which pointer to point is to be
 **                            used to store the result of the decoding in projective coordinates.
 ** \param[in,out]  workspace  Pointer to the primitives workspace instance.
 **
 ** \returns Error value.
 **
 ** \retval  E_OK      Request successful.
 ** \retval  E_NOT_OK  Request failed.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_HelperEdDSAPointDecoding
(
        boolean                                                                       point,
  P2VAR(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal constants]==========================================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  The primitives state transition table. **/

/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_StateTransitionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateTransitionType, CRYPTO_xVIx_xAIx_CONST)
Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Process_StateTransitionTable[CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT] =
{
  { NULL_PTR,                                                          CRYPTO_XVIX_XAIX_STATE_STARTIDLE,             CRYPTO_XVIX_XAIX_STATE_STARTIDLE,            CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE_TO_CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1               */
  { Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle,                CRYPTO_XVIX_XAIX_STATE_STARTEXEC,             CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,           CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },

  { NULL_PTR,                                                          CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,            CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,           CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE_TO_CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE/0001,1             */
  { Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateFinishIdle,         CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC,            CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,     CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },

  { NULL_PTR,                                                          CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,      CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,     CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE_TO_CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE/0001,1 */

  { Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishDecodePK1,          CRYPTO_XVIX_XAIX_STATE_FINISHEXEC,            CRYPTO_XVIX_XAIX_STATE_FINISHDECODEPK1,      CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },
  { Crypto_xVIx_xAIx_StateMachine_FinishDecodePK12FinishDecodePK2,     CRYPTO_XVIX_XAIX_STATE_FINISHDECODEPK1,       CRYPTO_XVIX_XAIX_STATE_FINISHDECODEPK2,      CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },
  { Crypto_xVIx_xAIx_StateMachine_FinishDecodePK22FinishDecodePK3,     CRYPTO_XVIX_XAIX_STATE_FINISHDECODEPK2,       CRYPTO_XVIX_XAIX_STATE_FINISHDECODEPK,       CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },

  { Crypto_xVIx_xAIx_StateMachine_FinishDecodePK32FinishValidateS,     CRYPTO_XVIX_XAIX_STATE_FINISHDECODEPK,        CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATES,      CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },

  { Crypto_xVIx_xAIx_StateMachine_FinishValidateS2FinishValidateR1,    CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATES,       CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATER1,     CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },
  { Crypto_xVIx_xAIx_StateMachine_FinishValidateR12FinishValidateR2,   CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATER1,      CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATER2,     CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },
  { Crypto_xVIx_xAIx_StateMachine_FinishValidateR22FinishValidateR,    CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATER2,      CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATER,      CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },

  { Crypto_xVIx_xAIx_StateMachine_FinishValidateR32FinishHashUpdate,   CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATER,       CRYPTO_XVIX_XAIX_STATE_FINISHHASHUPDATE,     CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },
  { Crypto_xVIx_xAIx_StateMachine_FinishHashUpdate2FinishHash,         CRYPTO_XVIX_XAIX_STATE_FINISHHASHUPDATE,      CRYPTO_XVIX_XAIX_STATE_FINISHHASH,           CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },

  { Crypto_xVIx_xAIx_StateMachine_FinishHash2FinishProcessSig1,        CRYPTO_XVIX_XAIX_STATE_FINISHHASH,            CRYPTO_XVIX_XAIX_STATE_FINISHSIG1,           CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },
  { Crypto_xVIx_xAIx_StateMachine_FinishProcessSig12FinishProcessSig2, CRYPTO_XVIX_XAIX_STATE_FINISHSIG1,            CRYPTO_XVIX_XAIX_STATE_FINISHSIG2,           CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },

  { Crypto_xVIx_xAIx_StateMachine_FinishProcessSig22StartIdle,         CRYPTO_XVIX_XAIX_STATE_FINISHSIG2,            CRYPTO_XVIX_XAIX_STATE_STARTIDLE,            CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },

  { Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle,                CRYPTO_XVIX_XAIX_STATE_SINGLECALL,            CRYPTO_XVIX_XAIX_STATE_STARTIDLE,            CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },

  { Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle,                    CRYPTO_XVIX_XAIX_STATE_CANCEL,                CRYPTO_XVIX_XAIX_STATE_STARTIDLE,            CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },
  { Crypto_xVIx_xAIx_StateMachine_Error2StartIdle,                     CRYPTO_XVIX_XAIX_STATE_ERROR,                 CRYPTO_XVIX_XAIX_STATE_STARTIDLE,            CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK }
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/** \brief  The primitives state action table. **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_StateActionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateActionType, CRYPTO_xVIx_xAIx_CONST)
Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Process_StateActionTable[CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT] =
{
  /* CRYPTO_XVIX_XAIX_STATE_STARTIDLE             */ { NULL_PTR                                }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1        */
  /* CRYPTO_XVIX_XAIX_STATE_STARTEXEC             */ { Crypto_xVIx_xAIx_StateMachine_StartExec }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTEXEC/0001,1        */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE            */ { NULL_PTR                                }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC            */ { NULL_PTR                                }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE      */ { NULL_PTR                                }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE/0001,1 */
  /* CRYPTO_XVIX_XAIX_STATE_FINISHEXEC            */ { NULL_PTR                                }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_FINISHEXEC/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_FINISHDECODEPK1       */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_FINISHDECODEPK2       */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_FINISHDECODEPK        */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATES       */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATER1      */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATER2      */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATER       */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_FINISHHASHUPDATE      */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_FINISHHASH            */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_FINISHSIG1            */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_FINISHSIG2            */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_SINGLECALL            */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_CANCEL                */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_ERROR                 */ { NULL_PTR                                }
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/** \brief Precalculated param for decoding
 **
 **        To compute the square root we use the special case ((prime - 5) / 8) during decoding or "decompression"
 **        during decoding or "decompression"
 **
 */
static CONST(Crypto_xVIx_xAIx_LNWordType, CRYPTO_xVIx_xAIx_CONST)
  Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_DecodingParam1[CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_NUM_LEN_WORDS] =
{
  0x00000008UL,
  0xFFFFFFFDUL, 0xFFFFFFFFUL, 0xFFFFFFFFUL, 0xFFFFFFFFUL,
  0xFFFFFFFFUL, 0xFFFFFFFFUL, 0xFFFFFFFFUL, 0x0FFFFFFFUL
};

/** \brief Precalculated param for decoding
 **
 **        To compute the square root we use the special case (2^((prime - 1) / 4)) during decoding or "decompression"
 **        during decoding or "decompression"
 **
 */
static CONST(Crypto_xVIx_xAIx_LNWordType, CRYPTO_xVIx_xAIx_CONST)
  Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_DecodingParam2[CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_NUM_LEN_WORDS] =
{
  0x00000008UL,
  0x4A0EA0B0UL, 0xC4EE1B27UL, 0xAD2FE478UL, 0x2F431806UL,
  0x3DFBD7A7UL, 0x2B4D0099UL, 0x4FC1DF0BUL, 0x2B832480UL
};

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Process --------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Process/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Process
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType);

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
    (void) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Reset(workspace->paObjectId, job, primitive);
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
        (void) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Main(objectId, job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Main -----------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Main/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Main
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType);

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
    if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Process_StateActionTable[curState].fcnAction))
    {
      resultAction = Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Process_StateActionTable[curState].fcnAction(job, primitive);
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
      if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Process_StateTransitionTable[smStateIndx].fcnTransition))
      {
        /* transition function returns using workspace->smResult */
        (void) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Process_StateTransitionTable[smStateIndx].fcnTransition(job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Cancel ---------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Cancel/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Cancel
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType);

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
      (void) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Main(objectId, job, primitive);
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Reset ----------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Reset/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Reset
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as
   * secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESET(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType));
    result = E_OK;
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Restart ----------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Restart/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Restart
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESTART(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType));
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Callback -------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Callback/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(objectId);
  TS_PARAM_UNUSED(job);
  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Callback/0002,1 */
  workspace->notifyType   = cbkType;
  workspace->notifyResult = cbkResult;

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_StateMachine_Error2StartIdle ----------------------------------------------*/

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveError2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType);

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
  result              = Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Reset(workspace->paObjectId, job, primitive);
  workspace->smResult = smResult;

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_GetNextState --------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
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
    if (   (Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx   = i;
      break;
    }
  }

  /* CHECK: NOPARSE
   * The FOR loop condition (i < *smStateIndx) is always FALSE for SIGNATUREVERIFY_ED25519_NOTSET, because the state
   * transition table of this cryptographic primitive is complete, except for the case when the
   * CRYPTO_XVIX_XAIX_STATE_STARTEXEC returns an action result of not E_OK. In this case the
   * previous FOR loop always iterates from i = 0 to CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT.
   */
  /* 2) iterate from first table entry to last found entry in table */
  for (i = 0U; (FALSE == nxtStateFound) && (i < *smStateIndx); i++)
  {
    if (   (Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx  = i;
      break;
    }
  }
  /* CHECK: PARSE */

  return nxtStateFound;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */
/* --- Crypto_xVIx_xAIx_StateMachine_StartExec -------------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType);

  Std_ReturnType result            = E_NOT_OK;
  uint8          curveIndex        = 0U;
  boolean        fromPrimitive     = FALSE;

  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) key;

  /* it is needed for the cancelation of the primitive after Start */
  primitive->P2->data->P1 = primitive;

  /* !LINKSTO Crypto.Asr.SWS_Crypto_00192,1 */
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
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0019,1 */
    if (CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_PUBLICKEY_LENGTH != key->data->size)
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
      workspace->tmp1ArrayLength   = key->data->size;
      TS_MemCpy(workspace->tmp1Array, key->data->data, key->data->size);
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle --------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Start2Update,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType);
  /* create secondary job */
  CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB();
  CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_KEY();
  CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_SRV();

  CRYPTO_XVIX_XAIX_SET_SMRESULT_START(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateFinishIdle -------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Update2Finish,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(job);
  TS_PARAM_UNUSED(primitive);

  CRYPTO_XVIX_XAIX_SET_SMRESULT_UPDATE(workspace->smResult, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishDecodePK1 --------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishDecodePK1
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  Std_ReturnType result = E_NOT_OK;

  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(job);

    /* Decode the public Key in a Point (Point1) */
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0020,1 */
    result = Crypto_xVIx_xAIx_Procedure_EdDSAPointDecoding(&(workspace->point1),
                                                          workspace->tmp1Array,
                                                          workspace->tmp,
                                                          &(workspace->edCtx)
                                                          );

  /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0025,1 */
  if (E_OK == result)
  {
    /* Calculate u * v^3 */
    Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingUV3(workspace->tmp, &(workspace->edCtx));
  }

  workspace->smResult = result;

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishDecodePK12FinishDecodePK2 ---------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishDecodePK12FinishDecodePK2
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(job);
  TS_PARAM_UNUSED(primitive);

  /* Calculate u * v^7 */
  Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingUV7(workspace->tmp, &(workspace->edCtx));

  /* tmp5 = (u * v^7)^((p - 5) / 8) */
  Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingUV7Power(workspace->tmp, &(workspace->edCtx));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishDecodePK22FinishDecodePK3 ---------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishDecodePK22FinishDecodePK3
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  Std_ReturnType result   = E_NOT_OK;

  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(job);
  TS_PARAM_UNUSED(primitive);

  /* Calculate x^2 */
  Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingEQ1(&(workspace->point1), workspace->tmp, &(workspace->edCtx));

  /* Calculate square root */
  /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0025,1 */
  result = Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingEQ2(&(workspace->point1), workspace->tmp, &(workspace->edCtx));

  workspace->smResult = result;

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishDecodePK32FinishValidateS --------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishDecodePK32FinishValidateS
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType);

  Crypto_xVIx_xAIx_LNCompareReturnType comparisonL;

  TS_PARAM_UNUSED(primitive);

  if (CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_SIGN_LENGTH != job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputLength)
  {
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0011,3 */
    *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.verifyPtr) = CRYPTO_E_VER_NOT_OK;
    workspace->smOperationDone |= CRYPTO_OPERATIONMODE_FINISH;
    workspace->smResult         = E_OK;
  }
  else
  {
    /* Convert S to Long Number format */
    /* we have enough memory allocated in the context to store the byte representation of the LN. */
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0021,1 */
    (void)Crypto_xVIx_xAIx_LNLEByteArrayToNumber
    (
      &(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputPtr[CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_BYTEARRAY_LENGTH]),
      CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_BYTEARRAY_LENGTH,
      workspace->scalar1,
      CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_TEMP_LEN_WORDS
    );

    /* Compare S with lValue */
    comparisonL = Crypto_xVIx_xAIx_LNCompareNumbers
                  (
                    workspace->scalar1,
                    &(Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->edCtx.curveIndex].modulus[0U])
                  );

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0022,1 */
    if (CRYPTO_XVIX_XAIX_LN_E_SMALLER == comparisonL)
    {
      /* Store the first part of the Signature (R) */
      TS_MemCpy(workspace->tmp2Array,
                job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputPtr,
                CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_BYTEARRAY_LENGTH
               );
    }
    else
    {
      *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.verifyPtr) = CRYPTO_E_VER_NOT_OK;
      workspace->smOperationDone |= CRYPTO_OPERATIONMODE_FINISH;
      workspace->smResult         = E_OK;
    }
  }

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishValidateS2FinishValidateR1 --------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishValidateS2FinishValidateR1
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(primitive);

  /* Decode first part of the Signature in a Point (Point2) */
  /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0023,1 */
  result = Crypto_xVIx_xAIx_Procedure_EdDSAPointDecoding(&(workspace->point2),
                                                         workspace->tmp2Array,
                                                         workspace->tmp,
                                                         &(workspace->edCtx)
                                                        );

  /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0024,1 */
  if (E_OK == result)
  {
    /* Calculate u * v^3 */
    Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingUV3(workspace->tmp, &(workspace->edCtx));
  }
  else
  {
    *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.verifyPtr) = CRYPTO_E_VER_NOT_OK;
    workspace->smOperationDone |= CRYPTO_OPERATIONMODE_FINISH;
    workspace->smResult         = E_OK;
  }

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishValidateR12FinishValidateR2 -------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishValidateR12FinishValidateR2
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(job);
  TS_PARAM_UNUSED(primitive);

  /* Calculate u * v^7 */
  Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingUV7(workspace->tmp, &(workspace->edCtx));

  /* tmp6 = (u * v^7)^((p - 5) / 8) */
  Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingUV7Power(workspace->tmp, &(workspace->edCtx));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishValidateR22FinishValidateR -------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishValidateR22FinishValidateR
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(primitive);

  /* Calculate x^2 */
  Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingEQ1(&(workspace->point2), workspace->tmp, &(workspace->edCtx));

  /* Calculate square root */
  result = Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingEQ2(&(workspace->point2), workspace->tmp, &(workspace->edCtx));

  /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0024,1 */
  if (E_OK != result)
  {
    *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.verifyPtr) = CRYPTO_E_VER_NOT_OK;
    workspace->smOperationDone |= CRYPTO_OPERATIONMODE_FINISH;
    workspace->smResult         = E_OK;
  }

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishValidateR32FinishHashUpdate ------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishValidateR32FinishHashUpdate
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  Std_ReturnType result = E_NOT_OK;

  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(job);

  /* start Hash(ENC(R) || ENC(A) || PH(M)) */
  /* set the hash result Length */
  workspace->hashResultLength = CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_HASH_LENGTH;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode = CRYPTO_OPERATIONMODE_START;
  primitive->P2->data->P1                                               = primitive;

  /* Start secondary primitive */
  result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                        &(workspace->secondaryJob),
                                                         workspace->paPrimitive->P2
                                                       );

  workspace->smResult = result;
  if (E_OK == result)
  {

    /* Update ENC(R) : tmp2Array */
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr     = workspace->tmp2Array;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength  = CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_BYTEARRAY_LENGTH;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode         = CRYPTO_OPERATIONMODE_UPDATE;

    /* Hash the input using the secondary primitive UPDATE. This call shall never fail because
     * the buffers and their sizes are set to valid values before this call.
     */
    (void) primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                        &(workspace->secondaryJob),
                                                         workspace->paPrimitive->P2
                                                       );

    /* Update ENC(A) : tmp1Array */
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr     = workspace->tmp1Array;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength  = CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_BYTEARRAY_LENGTH;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode         = CRYPTO_OPERATIONMODE_UPDATE;

    /* Hash the input using the secondary primitive UPDATE. This call shall never fail because
     * the buffers and their sizes are set to valid values before this call.
     */
    (void) primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                        &(workspace->secondaryJob),
                                                         workspace->paPrimitive->P2
                                                       );
  }

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishHashUpdate2FinishHash ------------------------------------ */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishHashUpdate2FinishHash
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  Std_ReturnType result = E_NOT_OK;

  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishHash2FinishProcessSig1 ------------------------------ */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishHash2FinishProcessSig1
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(job);
  TS_PARAM_UNUSED(primitive);

  /* Convert hashResult to LN number */
  /* This call can never fail because we have enough memory allocated in the context
   * to store the byte representation of the LN. */
  (void)Crypto_xVIx_xAIx_LNLEByteArrayToNumber(workspace->hashResult,
                                               workspace->hashResultLength,
                                               workspace->scalar2,
                                               CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_TEMP_LEN_WORDS
                                              );

  /* scalar = hashResult % LValue */
  Crypto_xVIx_xAIx_LNModulo(workspace->scalar2,
                            Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->edCtx.curveIndex].modulus,
                            &(workspace->edCtx.lnCtx)
                           );

  /* Calculate Point3 = Public Point A * hashResult k */
  Crypto_xVIx_xAIx_Procedure_EdDSAPointMultiplication(&(workspace->point3),
                                                      &(workspace->point1),
                                                      workspace->scalar2,
                                                      workspace->tmp,
                                                      &(workspace->edCtx)
                                                     );

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishProcessSig12FinishProcessSig2 ------------------------ */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishProcessSig12FinishProcessSig2
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(job);
  TS_PARAM_UNUSED(primitive);

  /* Point1 : R + (k * A): Point2 + Point3 */
  Crypto_xVIx_xAIx_Procedure_EdDSAPointAddition(
                                                &(workspace->point1),
                                                &(workspace->point2),
                                                &(workspace->point3),
                                                workspace->tmp,
                                                &(workspace->edCtx)
                                               );

  /* Convert the point R + (k * A) to affine coordinate */
  Crypto_xVIx_xAIx_Procedure_EccPointConvertProj2Aff(&(workspace->point1),
                                                     workspace->tmp,
                                                     &(workspace->edCtx)
                                                    );

  /* point2 = S * B: tmp6 * Base Point */
  Crypto_xVIx_xAIx_Procedure_EdDSAPointMultiplication(&(workspace->point2),
                                                      &(Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->edCtx.curveIndex].basePoint),
                                                      workspace->scalar1,
                                                      workspace->tmp,
                                                      &(workspace->edCtx)
                                                     );

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishProcessSig22StartIdle -------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Finish2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishProcessSig22StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  Std_ReturnType ret = E_NOT_OK;
  Crypto_VerifyResultType      resultVerify  =  CRYPTO_E_VER_OK;
  Crypto_xVIx_xAIx_LNWordType  compareResult = 0U;
  uint8                        i;

  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(primitive);

  /* Convert the point S * B to affine coordinate */
  Crypto_xVIx_xAIx_Procedure_EccPointConvertProj2Aff(&(workspace->point2),
                                                     workspace->tmp,
                                                     &(workspace->edCtx)
                                                    );

  /* CHECK: NOPARSE
   * Defensive Programming - unreachable code.
   */
  if (
         (workspace->point1.xValue[0U] != workspace->point2.xValue[0U])
      || (workspace->point1.yValue[0U] != workspace->point2.xValue[0U])
    )
  {
    resultVerify = CRYPTO_E_VER_NOT_OK;
  }
  /* CHECK: PARSE */
  else
  {
    for(i = 1U; i <= workspace->point1.xValue[0U]; i++)
    {
      compareResult |= workspace->point1.xValue[i] ^ workspace->point2.xValue[i];
    }

    for(i = 1U; i <= workspace->point1.yValue[0U]; i++)
    {
      compareResult |= workspace->point1.yValue[i] ^ workspace->point2.yValue[i];
    }

    if(0U != compareResult)
    {
      resultVerify = CRYPTO_E_VER_NOT_OK;
    }
    else
    {
      resultVerify = CRYPTO_E_VER_OK;
    }
  }

  *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.verifyPtr) = resultVerify;
  ret = E_OK;
  /* Deviation TASKING-1 */
  CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH(ret, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType));

  return ret;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_GetCurveIndex --------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetCurveIndex
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  Std_ReturnType result            = E_NOT_OK;
  uint8          curveIndex        = 0U;
  boolean        fromPrimitive     = FALSE;
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType);

  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) key;

  /* !LINKSTO Crypto.Asr.SWS_Crypto_00192,1 */
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
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0019,1 */
    if (CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_PUBLICKEY_LENGTH != key->data->size)
    {
      result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else
    {
      if (CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_SIGN_LENGTH != job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputLength)
      {
        /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0011,3 */
        *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.verifyPtr) = CRYPTO_E_VER_NOT_OK;
        workspace->smResult = E_OK;
        result              = E_NOT_OK;
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
        workspace->tmp1ArrayLength   = key->data->size;
        TS_MemCpy(workspace->tmp1Array, key->data->data, key->data->size);
      }
    }
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(key);
  }

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_HelperEdDSAPointDecoding--------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_HelperEdDSAPointDecoding
(
        boolean                                                                  point,
  P2VAR(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace
)
{
  Std_ReturnType result = E_NOT_OK;

 /* Calculate u * v^3 */
  Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingUV3(workspace->tmp, &(workspace->edCtx));

  /* Calculate u * v^7 */
  Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingUV7(workspace->tmp, &(workspace->edCtx));

  /* tmp5 = (u * v^7)^((p - 5) / 8) */
  Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingUV7Power(workspace->tmp, &(workspace->edCtx));

  if(point)
  {
    /* Calculate x^2 */
    Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingEQ1(&(workspace->point1), workspace->tmp, &(workspace->edCtx));

    /* Calculate square root */
    result = Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingEQ2(&(workspace->point1), workspace->tmp, &(workspace->edCtx));
  }
  else
  {
    /* Calculate x^2 */
    Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingEQ1(&(workspace->point2), workspace->tmp, &(workspace->edCtx));

    /* Calculate square root */
    result = Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingEQ2(&(workspace->point2), workspace->tmp, &(workspace->edCtx));
  }

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle --------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
/* Deviation CODEMETRIC-1 */
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  Crypto_VerifyResultType              resultVerify  = CRYPTO_E_VER_NOT_OK;
  Std_ReturnType                       result        = E_NOT_OK;
  Std_ReturnType                       intResult     = E_NOT_OK;
  Crypto_xVIx_xAIx_LNWordType          compareResult = 0U;
  uint8                                i;
  Crypto_xVIx_xAIx_LNCompareReturnType comparisonL;

  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType);

  result =  Crypto_xVIx_xAIx_GetCurveIndex(job, primitive);

  if (E_OK == result)
  {
    /* create secondary job */
    CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB();
    CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_KEY();
    CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_SRV();

    /* set the hash result Length */
    workspace->hashResultLength = CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_HASH_LENGTH;

      /* Decode the public Key in a Point (Point1) */
      /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0020,1 */
      result = Crypto_xVIx_xAIx_Procedure_EdDSAPointDecoding(&(workspace->point1),
                                                             workspace->tmp1Array,
                                                             workspace->tmp,
                                                             &(workspace->edCtx)
                                                            );

      /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0025,1 */
      if (E_OK == result)
      {
        /* Calculate EdDSAPointDecoding */
        result = Crypto_xVIx_xAIx_HelperEdDSAPointDecoding(TRUE, workspace);
      }
      else
      {
        workspace->smResult = E_NOT_OK;
      }

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0025,1 */
    if (result == E_OK)
    {
      /* Convert S to Long Number format */
      /* we have enough memory allocated in the context to store the byte representation of the LN. */
      /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0021,1 */
      (void)Crypto_xVIx_xAIx_LNLEByteArrayToNumber
      (
        &(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputPtr[CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_BYTEARRAY_LENGTH]),
        CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_BYTEARRAY_LENGTH,
        workspace->scalar1,
        CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_TEMP_LEN_WORDS
      );

      /* Compare S with lValue */
      comparisonL = Crypto_xVIx_xAIx_LNCompareNumbers
                    (
                      workspace->scalar1,
                      &(Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->edCtx.curveIndex].modulus[0U])
                    );

      /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0022,1 */
      if (CRYPTO_XVIX_XAIX_LN_E_SMALLER == comparisonL)
      {
        /* Store the first part of the Signature (R) */
        TS_MemCpy(workspace->tmp2Array,
                  job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputPtr,
                  CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_BYTEARRAY_LENGTH
                 );

        intResult = E_OK;
      }
      else
      {
        *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.verifyPtr) = CRYPTO_E_VER_NOT_OK;
      }
    }
    else
    {
      workspace->smResult = E_NOT_OK;
    }

    if (intResult == E_OK)
    {
      /* Decode first part of the Signature in a Point (Point2) */
      /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0023,1 */
      intResult = Crypto_xVIx_xAIx_Procedure_EdDSAPointDecoding(&(workspace->point2),
                                                                workspace->tmp2Array,
                                                                workspace->tmp,
                                                                &(workspace->edCtx)
                                                               );

      if (E_OK == intResult)
      {
        /* Calculate EdDSAPointDecoding */
        intResult = Crypto_xVIx_xAIx_HelperEdDSAPointDecoding(FALSE, workspace);
      }
      else
      {
        /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0024,1 */
        *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.verifyPtr) = CRYPTO_E_VER_NOT_OK;
      }

      if (E_OK == intResult)
      {
        /* start Hash(ENC(R) || ENC(A) || PH(M)) */
        workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode = CRYPTO_OPERATIONMODE_START;
        primitive->P2->data->P1                                               = primitive;

        /* Start secondary primitive */
        intResult = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                                 &(workspace->secondaryJob),
                                                                  workspace->paPrimitive->P2
                                                                );
        workspace->smResult = intResult;
      }
      else
      {
        /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0024,1 */
        *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.verifyPtr) = CRYPTO_E_VER_NOT_OK;
      }
    }

    if (E_OK == intResult)
    {

      /* Update ENC(R) : tmp2Array */
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr     = workspace->tmp2Array;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength  = CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_BYTEARRAY_LENGTH;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode         = CRYPTO_OPERATIONMODE_UPDATE;

      /* Hash the input using the secondary primitive UPDATE. This call shall never fail because
        * the buffers and their sizes are set to valid values before this call.
        */
      (void) primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                          &(workspace->secondaryJob),
                                                           workspace->paPrimitive->P2
                                                         );

      /* Update ENC(A) : tmp1Array */
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr     = workspace->tmp1Array;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength  = CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_BYTEARRAY_LENGTH;
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
      intResult = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                               &(workspace->secondaryJob),
                                                                workspace->paPrimitive->P2
                                                              );
      workspace->smResult = intResult;
    }

    if (E_OK == intResult)
    {
      /* Convert hashResult to LN number */
      /* This call can never fail because we have enough memory allocated in the context
      * to store the byte representation of the LN. */
      (void)Crypto_xVIx_xAIx_LNLEByteArrayToNumber(workspace->hashResult,
                                                    workspace->hashResultLength,
                                                    workspace->scalar2,
                                                    CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_TEMP_LEN_WORDS
                                                  );

      /* scalar = hashResult % LValue */
      Crypto_xVIx_xAIx_LNModulo(workspace->scalar2,
                                Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->edCtx.curveIndex].modulus,
                                &(workspace->edCtx.lnCtx)
                                );

      /* Calculate Point3 = Public Point A * hashResult k */
      Crypto_xVIx_xAIx_Procedure_EdDSAPointMultiplication(&(workspace->point3),
                                                          &(workspace->point1),
                                                          workspace->scalar2,
                                                          workspace->tmp,
                                                          &(workspace->edCtx)
                                                          );

      /* Point1 : R + (k * A): Point2 + Point3 */
      Crypto_xVIx_xAIx_Procedure_EdDSAPointAddition(
                                                    &(workspace->point1),
                                                    &(workspace->point2),
                                                    &(workspace->point3),
                                                    workspace->tmp,
                                                    &(workspace->edCtx)
                                                    );

      /* Convert the point R + (k * A) to affine coordinate */
      Crypto_xVIx_xAIx_Procedure_EccPointConvertProj2Aff(&(workspace->point1),
                                                          workspace->tmp,
                                                          &(workspace->edCtx)
                                                        );

      /* point2 = S * B: tmp6 * Base Point */
      Crypto_xVIx_xAIx_Procedure_EdDSAPointMultiplication(&(workspace->point2),
                                                          &(Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->edCtx.curveIndex].basePoint),
                                                          workspace->scalar1,
                                                          workspace->tmp,
                                                          &(workspace->edCtx)
                                                          );
      /* Convert the point S * B to affine coordinate */
      Crypto_xVIx_xAIx_Procedure_EccPointConvertProj2Aff(&(workspace->point2),
                                                          workspace->tmp,
                                                          &(workspace->edCtx)
                                                        );

     /* CHECK: NOPARSE
      * Defensive Programming - unreachable code.
      */
      if (
              (workspace->point1.xValue[0U] != workspace->point2.xValue[0U])
           || (workspace->point1.yValue[0U] != workspace->point2.xValue[0U])
         )
      {
        resultVerify = CRYPTO_E_VER_NOT_OK;
      }
      /* CHECK: PARSE */
      else
      {
        for(i = 1U; i <= workspace->point1.xValue[0U]; i++)
        {
          compareResult |= workspace->point1.xValue[i] ^ workspace->point2.xValue[i];
        }

        for(i = 1U; i <= workspace->point1.yValue[0U]; i++)
        {
          compareResult |= workspace->point1.yValue[i] ^ workspace->point2.yValue[i];
        }

        if(0U != compareResult)
        {
          resultVerify = CRYPTO_E_VER_NOT_OK;
        }
        else
        {
          resultVerify = CRYPTO_E_VER_OK;
        }
      }
      *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.verifyPtr) = resultVerify;
      workspace->smResult = E_OK;
    }
  }

  CRYPTO_XVIX_XAIX_SET_SMRESULT_SINGLECALL(workspace->smResult, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle ------------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveCancel2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType);
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
  CRYPTO_XVIX_XAIX_SET_SMRESULT_CANCEL(CRYPTO_E_JOB_CANCELED, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_Procedure_UpdateMsgDigest ----------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_UpdateMsgDigest
(
    P2VAR(Crypto_JobType,                             AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
    P2VAR(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_WorkspaceType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType,                                 AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  /* Update the hash function, PH(M) */
  /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ED25519_NOTSET/GENERAL/0014,1 */
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode         = CRYPTO_OPERATIONMODE_UPDATE;
  /* Hash the input using the secondary primitive UPDATE. This call shall never fail because
   * the buffers and their sizes are set to valid values before this call.
   */
  (void) primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                      &(workspace->secondaryJob),
                                                       workspace->paPrimitive->P2
                                                     );

}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_Procedure_EdDSAPointDecoding -------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_EdDSAPointDecoding
(
  P2VAR(Crypto_xVIx_xAIx_ECPointType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) point,
  P2VAR(uint8,                         AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) value,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
)
{
  Std_ReturnType result = E_NOT_OK;

  const uint32 tmp1 = (0U * CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_TEMP_LEN_WORDS);
  const uint32 tmp2 = (CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_TEMP_LEN_WORDS);

  point->zValue[0U] = 1U;
  point->zValue[1U] = 1U;

  /* bit 255 of value is the least significant bit of the x-coordinate */
  edCtx->x0 = (uint8)((uint8)(value[31U] & 0x80U) >> 7U);

  /* we have enough memory allocated in the context to store the byte representation of the LN. */
  (void)Crypto_xVIx_xAIx_LNLEByteArrayToNumber(
                                                value,
                                                CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_BYTEARRAY_LENGTH,
                                                point->yValue,
                                                CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_NUM_LEN_WORDS
                                              );

  /* y-coordinate is recovered by clearing the bit 255 */
  point->yValue[point->yValue[0U]] &= (uint32)(~(uint32)((uint32)1U << 31U));

  /* Check if the resulting value is < p */
  if (CRYPTO_XVIX_XAIX_LN_E_LARGER ==
            Crypto_xVIx_xAIx_LNCompareNumbers(Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].prime,
                                              point->yValue
                                             )
     )
  {   /* yValue is valid */

    /* tmp1 = y^2 */
    Crypto_xVIx_xAIx_LNSquareComba(&tmp[tmp1], point->yValue, &(edCtx->lnCtx));

    Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(&tmp[tmp1], edCtx);

    /* tmp2: u = (y^2) - 1 = tmp1 - 1 */
    Crypto_xVIx_xAIx_LNSubtractionModular(
                                            &tmp[tmp2],
                                            &tmp[tmp1],
                                            point->zValue,
                                            Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].prime
                                         );

    /* tmp1 = d * (y^2) */
    Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                        &tmp[tmp1],
                                        Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].coeff1,
                                        &tmp[tmp1],
                                        &(edCtx->lnCtx)
                                      );

    Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(&tmp[tmp1], edCtx);

    /* tmp1: v = (d * (y^2)) + 1 */
    Crypto_xVIx_xAIx_LNAdditionModular(
                                        &tmp[tmp1],
                                        &tmp[tmp1],
                                        point->zValue,
                                        Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].prime
                                      );

    result = E_OK;
  }
  else
  {  /* yValue is invalid */
    result = E_NOT_OK;
  }

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingUV3 ----------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingUV3
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
)
{

  const uint32 tmp1 = (0U * CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_TEMP_LEN_WORDS);
  const uint32 tmp2 = (CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_TEMP_LEN_WORDS);
  const uint32 tmp3 = (2U * CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_TEMP_LEN_WORDS);
  const uint32 tmp4 = (3U * CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_TEMP_LEN_WORDS);

  /* tmp3 = tmp1^2 : v^2 */
  Crypto_xVIx_xAIx_LNSquareComba(&tmp[tmp3], &tmp[tmp1], &(edCtx->lnCtx));

  Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(&tmp[tmp3], edCtx);

  /* tmp3 = tmp3 * tmp1 : v^3 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                      &tmp[tmp3],
                                      &tmp[tmp3],
                                      &tmp[tmp1],
                                      &(edCtx->lnCtx)
                                    );
  Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(&tmp[tmp3], edCtx);

  /* tmp4 = tmp2 * tmp3 : u * v^3 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                      &tmp[tmp4],
                                      &tmp[tmp2],
                                      &tmp[tmp3],
                                      &(edCtx->lnCtx)
                                    );
  Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(&tmp[tmp4], edCtx);
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingUV7 ----------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingUV7
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
)
{
  const uint32 tmp1 = (0U * CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_TEMP_LEN_WORDS);
  const uint32 tmp2 = (CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_TEMP_LEN_WORDS);
  const uint32 tmp3 = (2U * CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_TEMP_LEN_WORDS);

  /* tmp3: v^6 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                      &tmp[tmp3],
                                      &tmp[tmp3],
                                      &tmp[tmp3],
                                      &(edCtx->lnCtx)
                                    );
  Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(&tmp[tmp3], edCtx);

  /* tmp3: v^7 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                      &tmp[tmp3],
                                      &tmp[tmp3],
                                      &tmp[tmp1],
                                      &(edCtx->lnCtx)
                                    );
  Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(&tmp[tmp3], edCtx);

  /* tmp3: tmp2 * tmp3 = u * v^7 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                      &tmp[tmp3],
                                      &tmp[tmp2],
                                      &tmp[tmp3],
                                      &(edCtx->lnCtx)
                                    );
  Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(&tmp[tmp3], edCtx);
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingUV7Power ------------------------------------ */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingUV7Power
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
)
{
  const uint32 tmp3 = (2U * CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_TEMP_LEN_WORDS);
  const uint32 tmp5 = (4U * CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_TEMP_LEN_WORDS);

  uint32 bits = Crypto_xVIx_xAIx_LNBitLengthOfNumber(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_DecodingParam1);

  /* x^2 */
  (&tmp[tmp5])[0U] = 1U;
  (&tmp[tmp5])[1U] = 1U;

  /* calculate x^2 and reduce, recalculate the root candidate if necessary */
  while((Crypto_xVIx_xAIx_LNWordType)0U < bits)
  {
    --bits;

    /* calculate x^2 */
    Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                        &tmp[tmp5],
                                        &tmp[tmp5],
                                        &tmp[tmp5],
                                        &(edCtx->lnCtx)
                                      );

    Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(&tmp[tmp5], edCtx);

    if ((Crypto_xVIx_xAIx_LNWordType)1U == CRYPTO_XVIX_XAIX_LN_GET_BIT(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_DecodingParam1, bits))
    {
      /* calculate x^2 * (u * v^7) and reduce */
      Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                          &tmp[tmp5],
                                          &tmp[tmp5],
                                          &tmp[tmp3],
                                          &(edCtx->lnCtx)
                                        );

      Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(&tmp[tmp5], edCtx);
    }
  }
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingEQ1 ----------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingEQ1
(
  P2VAR(Crypto_xVIx_xAIx_ECPointType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) point,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
)
{
  const uint32 tmp3 = (2U * CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_TEMP_LEN_WORDS);
  const uint32 tmp4 = (3U * CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_TEMP_LEN_WORDS);
  const uint32 tmp5 = (4U * CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_TEMP_LEN_WORDS);

  /* calculate x = tmp4 * tmp5 : (u * v^3) * (u * v^7)^((p - 5) / 8) */
  Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                      point->xValue,
                                      &tmp[tmp4],
                                      &tmp[tmp5],
                                      &(edCtx->lnCtx)
                                    );
  Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(point->xValue, edCtx);

  /* tmp3 = xValue^2 */
  Crypto_xVIx_xAIx_LNSquareComba(&tmp[tmp3], point->xValue, &(edCtx->lnCtx));

  Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(&tmp[tmp3], edCtx);
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingEQ2 ----------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_EdDSAPointDecodingEQ2
(
  P2VAR(Crypto_xVIx_xAIx_ECPointType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) point,
  P2VAR(Crypto_xVIx_xAIx_LNWordType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
  P2VAR(Crypto_xVIx_xAIx_ECCtxType,    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) edCtx
)
{
  Std_ReturnType result = E_NOT_OK;

  /* vValue    Offset where v is stored. */
  const uint32 vValue    = (0U * CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_TEMP_LEN_WORDS);
  /* uValue    Offset where u is stored. */
  const uint32 uValue    = (CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_TEMP_LEN_WORDS);
  /* squareOfX Offset where the result of xValue^2 is stored. */
  const uint32 squareOfX = (2U * CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_TEMP_LEN_WORDS);
  /* Value1    Offset where the result of (v * xValue^2 - u) % prime is stored. */
  const uint32 value1    = (3U * CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_TEMP_LEN_WORDS);
  /* Value2    Offset where the result of (v * xValue^2 + u) % prime is stored. */
  const uint32 value2    = (4U * CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ED25519_NOTSET_TEMP_LEN_WORDS);

  uint8        sign;

  /* calculate v * squareOfX : v* xValue^2 */
  Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                      &tmp[squareOfX],
                                      &tmp[vValue],
                                      &tmp[squareOfX],
                                      &(edCtx->lnCtx)
                                    );

  Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(&tmp[squareOfX], edCtx);

  /* Value1 = (v * xValue^2 - u) % prime */
  Crypto_xVIx_xAIx_LNSubtractionModular(
                                         &tmp[value1],
                                         &tmp[squareOfX],
                                         &tmp[uValue],
                                         Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].prime
                                       );

  /* Value2 = (v * xValue^2 + u) % prime */
  Crypto_xVIx_xAIx_LNAdditionModular(&tmp[value2], &tmp[squareOfX], &tmp[uValue], Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].prime);

  /* v * xValue^2 == u */
  if(0U == (&tmp[value1])[0U])
  {
    /* check the sign */
    result = E_OK;

    /* CHECK: NOPARSE
     * Unable to cover as we need to fulfill both ((v * xValue^2 + u) % prime == 0) and
     * ((v * xValue^2 - u) % prime == 0) in the same time.
     * Nevertheless I think we need to keep this error check.
     */
    if(0U == (&tmp[value2])[0U])
    {
      /* invalid Point, exit with E_NOT_OK. */
      result = E_NOT_OK;
    }
    /* CHECK: PARSE */
  }
  else
  {
    /* v * xValue^2 == -u */
    if (0U == (&tmp[value2])[0U])
    {
      /* xValue = xValue * (2^(p - 1) / 4) */
      Crypto_xVIx_xAIx_LNMultiplyNumbers(
                                          point->xValue,
                                          point->xValue,
                                          Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ED25519_NOTSET_DecodingParam2,
                                          &(edCtx->lnCtx)
                                        );

      Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].fastReductionFun(point->xValue, edCtx);
      result = E_OK;
    }
  }

  if (E_OK == result)
  {
    sign = (uint8)(point->xValue[1U] & 0x01U);
    /* CHECK: NOPARSE
     * Unable to fulfill 0U == point->xValue[0U]
     */
    if ((0U == point->xValue[0U]) && (1U == edCtx->x0))
    {
      result = E_NOT_OK;
    }
    /* CHECK: PARSE */
    else
    {
      /* x = prime - x */
      if (sign != edCtx->x0)
      {
        Crypto_xVIx_xAIx_LNSubtractionModular(
                                               point->xValue,
                                               Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].prime,
                                               point->xValue,
                                               Crypto_xVIx_xAIx_EllipticCurveInfo[edCtx->curveIndex].prime
                                             );
      }
    }
  }
  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ED25519_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[end of file]=================================================================*/

