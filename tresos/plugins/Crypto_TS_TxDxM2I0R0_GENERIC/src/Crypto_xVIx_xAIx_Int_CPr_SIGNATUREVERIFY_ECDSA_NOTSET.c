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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_SIGNATUREVERIFY_ECDSA_NOTSET.c/0001,1 */

/*==================[deviations]==================================================================*/

/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.3 (required)
 * A cast shall not be performed between a pointer to object type and a pointer to a different object type.
 *
 * Reason:
 * We are using memory from the heap, which is given as a void pointer. We have to cast that
 * pointer to a uint8 pointer to be able to do pointer arithmetic and we then have to cast the
 * pointer again to get the actual type that we need. And the second cast is what this deviation is
 * about.
 *
 * MISRAC2012-2) Deviated Rule: 2.1 (required)
 * A project shall not contain unreachable code.
 *
 * Reason:
 * The function-like macro which is used enters different paths depending on the value of one
 * of its inputs, but in this line of code, we hand over a fixed input.
 */
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
 * not 86 <= 75
 *
 * Reason:
 * SingleCall functions are adjusted for performance and have a reduced amount of function calls
 * on purpose which leads to metric violations.
*
 */

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int.h>                                       /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_SIGNATUREVERIFY_ECDSA_NOTSET.c/0002,1 */
#include <Crypto_xVIx_xAIx_Int_KeyManagement.h>                         /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_SIGNATUREVERIFY_ECDSA_NOTSET.c/0003,1 */
#include <Crypto_xVIx_xAIx_Int_CPr_SIGNATUREVERIFY_ECDSA_NOTSET.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_SIGNATUREVERIFY_ECDSA_NOTSET.c/0004,1 */

/*==================[macros]======================================================================*/

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT,1 */
#if (defined CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT)
#error CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT already defined
#endif
/** \brief  Number of entries in the primitives state transition table. **/
#define CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT 14U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT,1 */
#if (defined CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT)
#error CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT already defined
#endif
/** \brief  Number of entries in the primitives state action table. **/
#define CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT 15U

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
/** \brief  The UpdateProcess state of the primitive  **/
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

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHEXTRACTRS)
#error CRYPTO_XVIX_XAIX_STATE_FINISHEXTRACTRS already defined
#endif
/** \brief  The FinishDecodePK1 state of the primitive.. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHEXTRACTRS 7U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHCOMPUTEU1)
#error CRYPTO_XVIX_XAIX_STATE_FINISHCOMPUTEU1 already defined
#endif
/** \brief  The FinishDecodePK2 state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHCOMPUTEU1 8U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHCOMPUTEU2)
#error CRYPTO_XVIX_XAIX_STATE_FINISHCOMPUTEU2 already defined
#endif
/** \brief  The FinishDecodePKFinish state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHCOMPUTEU2 9U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHCOMPUTEX)
#error CRYPTO_XVIX_XAIX_STATE_FINISHCOMPUTEX already defined
#endif
/** \brief  The FinishValidS state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHCOMPUTEX 10U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATESIG)
#error CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATESIG already defined
#endif
/** \brief  The FinishValidateR1 state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATESIG 11U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_CANCEL,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_CANCEL)
#error CRYPTO_XVIX_XAIX_STATE_CANCEL already defined
#endif
/** \brief  The Cancel state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_CANCEL 12U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_ERROR,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_ERROR)
#error CRYPTO_XVIX_XAIX_STATE_ERROR already defined
#endif
/** \brief  The Error state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_ERROR 13U

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static FUNC(boolean, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetNextState
(
  P2VAR(uint8,                                         AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) smStateIndx,
        Crypto_xVIx_xAIx_PrimitiveStateIdentifierType                                         curState,
        Std_ReturnType                                                                        resultAction,
        Crypto_ProcessingType                                                                 jobProcessing,
  P2VAR(Crypto_xVIx_xAIx_PrimitiveStateIdentifierType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) nxtState
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC
 **         to state   CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHEXEC'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHEXTRACTRS'
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishExtractRS
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHEXTRACTRS'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHCOMPUTEU1'
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExtractRS2FinishComputeU1
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHCOMPUTEU1'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHCOMPUTEU2'
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishComputeU12FinishComputeU2
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHCOMPUTEU2'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHCOMPUTEX'
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishComputeU22FinishComputeX
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHCOMPUTEX'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATESIG'
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishComputeX2FinishValidateSig
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATESIG'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_STARTIDLE'
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishValidateSig2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal constants]==========================================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  The primitives state transition table. **/

/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_StateTransitionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateTransitionType, CRYPTO_xVIx_xAIx_CONST)
Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Process_StateTransitionTable[CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT] =
{
  { NULL_PTR,                                                       CRYPTO_XVIX_XAIX_STATE_STARTIDLE,         CRYPTO_XVIX_XAIX_STATE_STARTIDLE,         CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE_TO_CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1               */
  { Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle,             CRYPTO_XVIX_XAIX_STATE_STARTEXEC,         CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,        CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },
  { NULL_PTR,                                                       CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,        CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,        CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE_TO_CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE/0001,1             */
  { Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess,         CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC,        CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,     CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },
  { Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle,   CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,     CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,  CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },
  { NULL_PTR,                                                       CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,  CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,  CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE_TO_CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE/0001,1 */
  { Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishExtractRS,       CRYPTO_XVIX_XAIX_STATE_FINISHEXEC,        CRYPTO_XVIX_XAIX_STATE_FINISHEXTRACTRS,   CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },
  { Crypto_xVIx_xAIx_StateMachine_FinishExtractRS2FinishComputeU1,  CRYPTO_XVIX_XAIX_STATE_FINISHEXTRACTRS,   CRYPTO_XVIX_XAIX_STATE_FINISHCOMPUTEU1,   CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },
  { Crypto_xVIx_xAIx_StateMachine_FinishComputeU12FinishComputeU2,  CRYPTO_XVIX_XAIX_STATE_FINISHCOMPUTEU1,   CRYPTO_XVIX_XAIX_STATE_FINISHCOMPUTEU2,   CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },
  { Crypto_xVIx_xAIx_StateMachine_FinishComputeU22FinishComputeX,   CRYPTO_XVIX_XAIX_STATE_FINISHCOMPUTEU2,   CRYPTO_XVIX_XAIX_STATE_FINISHCOMPUTEX,    CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },
  { Crypto_xVIx_xAIx_StateMachine_FinishComputeX2FinishValidateSig, CRYPTO_XVIX_XAIX_STATE_FINISHCOMPUTEX,    CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATESIG, CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },
  { Crypto_xVIx_xAIx_StateMachine_FinishValidateSig2StartIdle,      CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATESIG, CRYPTO_XVIX_XAIX_STATE_STARTIDLE,         CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },
  { Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle,                 CRYPTO_XVIX_XAIX_STATE_CANCEL,            CRYPTO_XVIX_XAIX_STATE_STARTIDLE,         CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },
  { Crypto_xVIx_xAIx_StateMachine_Error2StartIdle,                  CRYPTO_XVIX_XAIX_STATE_ERROR,             CRYPTO_XVIX_XAIX_STATE_STARTIDLE,         CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK }
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

/** \brief  The primitives state action table. **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_StateActionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateActionType, CRYPTO_xVIx_xAIx_CONST)
Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Process_StateActionTable[CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT] =
{
  /* CRYPTO_XVIX_XAIX_STATE_STARTIDLE         */ { NULL_PTR                                }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1        */
  /* CRYPTO_XVIX_XAIX_STATE_STARTEXEC         */ { Crypto_xVIx_xAIx_StateMachine_StartExec }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTEXEC/0001,1        */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE        */ { NULL_PTR                                }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC        */ { NULL_PTR                                }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS     */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE  */ { NULL_PTR                                }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE/0001,1 */
  /* CRYPTO_XVIX_XAIX_STATE_FINISHEXEC        */ { NULL_PTR                                }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_FINISHEXEC/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_FINISHEXTRACTRS   */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_FINISHCOMPUTEU1   */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_FINISHCOMPUTEU2   */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_FINISHCOMPUTEX    */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_FINISHVALIDATESIG */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_SINGLECALL        */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_CANCEL            */ { NULL_PTR                                },
  /* CRYPTO_XVIX_XAIX_STATE_ERROR             */ { NULL_PTR                                }
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Process ----------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Process/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Process
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType);

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
    (void) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Reset(workspace->paObjectId, job, primitive);
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
        (void) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Main(objectId, job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Main -------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Main/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Main
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType);

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
    if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Process_StateActionTable[curState].fcnAction))
    {
      resultAction = Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Process_StateActionTable[curState].fcnAction(job, primitive);
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
      if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Process_StateTransitionTable[smStateIndx].fcnTransition))
      {
        /* transition function returns using workspace->smResult */
        (void) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Process_StateTransitionTable[smStateIndx].fcnTransition(job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Cancel -----------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Cancel/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Cancel
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType);

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
      (void) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Main(objectId, job, primitive);
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Reset ------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Reset/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Reset
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as
   * secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESET(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType));
    result = E_OK;
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Restart ------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Restart/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Restart
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESTART(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType));
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Callback ---------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Callback/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(objectId);
  TS_PARAM_UNUSED(job);
  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Callback/0002,1 */
  workspace->notifyType   = cbkType;
  workspace->notifyResult = cbkResult;

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_StateMachine_Error2StartIdle ----------------------------------------------*/

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveError2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType);

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
  result              = Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Reset(workspace->paObjectId, job, primitive);
  workspace->smResult = smResult;

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_GetNextState --------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
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
    if (   (Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx   = i;
      break;
    }
  }

  /* CHECK: NOPARSE
   * The FOR loop condition (i < *smStateIndx) is always FALSE for SIGNATUREVERIFY_ECDSA_NOTSET, because the state
   * transition table of this cryptographic primitive is complete, except for the case when the
   * CRYPTO_XVIX_XAIX_STATE_STARTEXEC returns an action result of not E_OK. In this case the
   * previous FOR loop always iterates from i = 0 to CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT.
   */
  /* 2) iterate from first table entry to last found entry in table */
  for (i = 0U; (FALSE == nxtStateFound) && (i < *smStateIndx); i++)
  {
    if (   (Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx  = i;
      break;
    }
  }
  /* CHECK: PARSE */

  return nxtStateFound;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */
/* --- Crypto_xVIx_xAIx_StateMachine_StartExec -------------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType);

  Std_ReturnType result            = E_NOT_OK;
  boolean        fromPrimitive     = FALSE;
  boolean        keyReadLock       = FALSE;
  boolean        curveTypeReadLock = FALSE;
  uint8 curveIndex = 0U;

  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) key = NULL_PTR;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) curveType = NULL_PTR;
  uint32 heapPosition = 0U;
  uint32 tempNumberLen = 0U;
  uint8  publicKeyComponentLength = 0U;

  /* it is needed for the cancelation of the primitive after Start */
  primitive->P2->data->P1 = primitive;

  result = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( job->cryptoKeyId,
                                                      CRYPTO_KE_SIGNATURE_KEY,
                                                     &key,
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
    keyReadLock = TRUE;

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ECDSA_NOTSET/GENERAL/0002,1 */
    result = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( job->cryptoKeyId,
                                                        CRYPTO_KE_SIGNATURE_CURVETYPE,
                                                       &curveType,
                                                        FALSE,
                                                        CRYPTO_XVIX_XAIX_SID_EMPTY
                                                      );
  }

  if (E_OK == result)
  {
    /* Deviation TASKING-1 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(result, curveType, fromPrimitive);
  }

  if (E_OK == result)
  {
    curveTypeReadLock = TRUE;

    result = Crypto_xVIx_xAIx_GetECIndex( job->jobPrimitiveInfo->primitiveInfo->service,
                                          job->jobPrimitiveInfo->primitiveInfo->algorithm.family,
                                          curveType->data->data,
                                          (uint8)curveType->data->size,
                                         &curveIndex
                                        );

  }

  if (E_OK == result)
  {
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ECDSA_NOTSET/START/0001,1 */
    if (((uint32)Crypto_xVIx_xAIx_EllipticCurveInfo[curveIndex].publicKeyLength) != key->data->size)
    {
      result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
  }

  if (E_OK == result)
  {

    tempNumberLen =
      sizeof(Crypto_xVIx_xAIx_LNWordType) *
      CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ECDSA_NOTSET_TEMP_LEN_WORDS(Crypto_xVIx_xAIx_EllipticCurveInfo[curveIndex].privateKeyLength);

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ECDSA_NOTSET/START/0002,1 */
    if (
         (NULL_PTR != primitive->cnfg->heap) &&
         (
           primitive->cnfg->heapSize >=
           (
             (6UL * tempNumberLen) +
             (3UL * sizeof(Crypto_xVIx_xAIx_ECPointType)) +
             sizeof(Crypto_xVIx_xAIx_ECCtxType) +
             CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ECDSA_NOTSET_HASH_LENGTH
           )
         )
       )
    {
      heapPosition = 0U;

      /* Deviation MISRAC2012-1 <+11> */
      workspace->tmp1 = (P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))&(((P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))primitive->cnfg->heap)[heapPosition]);
      heapPosition += tempNumberLen;
      workspace->tmp2 = (P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))&(((P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))primitive->cnfg->heap)[heapPosition]);
      heapPosition += tempNumberLen;
      workspace->tmp3 = (P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))&(((P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))primitive->cnfg->heap)[heapPosition]);
      heapPosition += tempNumberLen;
      workspace->tmp4 = (P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))&(((P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))primitive->cnfg->heap)[heapPosition]);
      heapPosition += tempNumberLen;
      workspace->tmp5 = (P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))&(((P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))primitive->cnfg->heap)[heapPosition]);
      heapPosition += tempNumberLen;
      workspace->R = (P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))&(((P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))primitive->cnfg->heap)[heapPosition]);
      heapPosition += tempNumberLen;

      /* Deviation MISRAC2012-1 */
      workspace->eccCtxPtr = (P2VAR(Crypto_xVIx_xAIx_ECCtxType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))&(((P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))primitive->cnfg->heap)[heapPosition]);
      heapPosition += sizeof(Crypto_xVIx_xAIx_ECCtxType);

      /* Deviation MISRAC2012-1 <+5> */
      workspace->xPtr = (P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))&(((P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))primitive->cnfg->heap)[heapPosition]);
      heapPosition += sizeof(Crypto_xVIx_xAIx_ECPointType);
      workspace->tmpPointPtr = (P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))&(((P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))primitive->cnfg->heap)[heapPosition]);
      heapPosition += sizeof(Crypto_xVIx_xAIx_ECPointType);
      workspace->pubKeyPtr = (P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))&(((P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))primitive->cnfg->heap)[heapPosition]);
      heapPosition += sizeof(Crypto_xVIx_xAIx_ECPointType);

      workspace->hashResult = &(((P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))primitive->cnfg->heap)[heapPosition]);
    }
    else
    {
      /* Not enough space on the heap for our temporary data. */
      result = E_NOT_OK;
    }
  }

  if (E_OK == result)
  {
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ECDSA_NOTSET/GENERAL/0003,1 */
    workspace->pubKeyPtr->xValue[0U] = 8U;
    workspace->pubKeyPtr->yValue[0U] = 8U;
    workspace->pubKeyPtr->zValue[0U] = 1U;
    workspace->pubKeyPtr->zValue[1U] = 1U;

    publicKeyComponentLength = Crypto_xVIx_xAIx_EllipticCurveInfo[curveIndex].publicKeyLength / (uint8)2U;

    /* Create public key point Q in pubKeyPtr. */
    /* The return value is ignored because the parameters are either from the context where they are
     * properly defined or local variables which are properly defined before passing them to
     * the function.*/
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ECDSA_NOTSET/GENERAL/0004,1 */
    (void)Crypto_xVIx_xAIx_LNBEByteArrayToNumber
    (
      &(key->data->data[0U]),
      publicKeyComponentLength,
      workspace->pubKeyPtr->xValue,
      CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ECDSA_NOTSET_NUM_LEN_WORDS(publicKeyComponentLength) + (Crypto_xVIx_xAIx_LNWordType)1U
    );
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ECDSA_NOTSET/GENERAL/0005,1 */
    (void)Crypto_xVIx_xAIx_LNBEByteArrayToNumber
    (
      &(key->data->data[publicKeyComponentLength]),
      publicKeyComponentLength,
      workspace->pubKeyPtr->yValue,
      CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ECDSA_NOTSET_NUM_LEN_WORDS(publicKeyComponentLength) + (Crypto_xVIx_xAIx_LNWordType)1U
    );

    workspace->eccCtxPtr->curveIndex = curveIndex;
  }
  else
  {
    workspace->smResult         = result;
    workspace->smOperationDone |= CRYPTO_OPERATIONMODE_START;
  }

  if(TRUE == keyReadLock)
  {
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(key);
  }

  if(TRUE == curveTypeReadLock)
  {
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(curveType);
  }

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle --------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Start2Update,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType);
  Std_ReturnType result = E_NOT_OK;
  /* create secondary job */
  CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB();
  CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_KEY();
  CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_SRV();

  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode            = CRYPTO_OPERATIONMODE_START;

  CRYPTO_XVIX_XAIX_RESET_CALLBACK();
  primitive->P2->data->P1 = primitive;
  result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                        &(workspace->secondaryJob),
                                                         workspace->paPrimitive->P2
                                                       );
  CRYPTO_XVIX_XAIX_SET_SMRESULT_START(result, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess ----------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Update2Update,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  Std_ReturnType result = E_NOT_OK;

  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType);

  /* Hash the Message */
  /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ECDSA_NOTSET/UPDATE/0001,1 */
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode            = CRYPTO_OPERATIONMODE_UPDATE;

  CRYPTO_XVIX_XAIX_RESET_CALLBACK();
  primitive->P2->data->P1 = primitive;
  result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                        &(workspace->secondaryJob),
                                                         workspace->paPrimitive->P2
                                                       );

  workspace->smResult = result;
  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle ----------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Update2Finish,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(job);
  TS_PARAM_UNUSED(primitive);

  CRYPTO_XVIX_XAIX_SET_SMRESULT_UPDATE(workspace->smResult, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishExtractRS --------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishExtractRS
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  Std_ReturnType result = E_NOT_OK;
  Crypto_xVIx_xAIx_LNCompareReturnType ComparisonZero;
  Crypto_xVIx_xAIx_LNCompareReturnType ComparisonModulus;
  uint32 signatureComponentLength = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputLength / (uint32)2U;

  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(job);

   /* Finish hashing the message. */
  workspace->hashResultLength = CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ECDSA_NOTSET_HASH_LENGTH;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       = workspace->hashResult;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &workspace->hashResultLength;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode            = CRYPTO_OPERATIONMODE_FINISH;

  CRYPTO_XVIX_XAIX_RESET_CALLBACK();
  primitive->P2->data->P1 = primitive;
  result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                        &(workspace->secondaryJob),
                                                         workspace->paPrimitive->P2
                                                       );

  if (E_OK == result)
  {
    if(workspace->hashResultLength >= Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->eccCtxPtr->curveIndex].privateKeyLength)
    {
      /* Only use the needed bytes from the hash result. */
      workspace->hashResultLength = Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->eccCtxPtr->curveIndex].privateKeyLength;
    }
    else
    {
      /* The length of the hash result is not large enough. We cannot continue. */
      result = E_NOT_OK;
    }
  }

  if (E_OK == result)
  {
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ECDSA_NOTSET/FINISH/0001,1 */
    if(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputLength != Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->eccCtxPtr->curveIndex].publicKeyLength)
    {
      *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.verifyPtr) = CRYPTO_E_VER_NOT_OK;
      workspace->smOperationDone |= CRYPTO_OPERATIONMODE_FINISH;
      workspace->smResult         = E_OK;
      /* Deviation TASKING-1 */
      CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH(result, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType));
    }
    else
    {
      /* tmp3   Offset of the temporary storage */

      /* r = first half of bytes of Signature */
      /* The return value is ignored because the parameters are either from the context where they are
       * properly defined or local variables which are properly defined before passing them to
       * the function.
       */
      (void)Crypto_xVIx_xAIx_LNBEByteArrayToNumber
      (
        job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputPtr,
        signatureComponentLength,
        workspace->R,
        CRYPTO_XVIX_XAIX_ECC_NUM_LEN_WORDS
      );

      /* Check the validity of r */
      /* Set tmp3 to zero */
      workspace->tmp3[0U] = 0U;

      /* Compare r with zero */
      ComparisonZero = Crypto_xVIx_xAIx_LNCompareNumbers
                      (
                        workspace->R,
                        workspace->tmp3
                      );
      /* Compare r with Modulus */
      ComparisonModulus = Crypto_xVIx_xAIx_LNCompareNumbers
                      (
                        workspace->R,
                        Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->eccCtxPtr->curveIndex].modulus
                      );

      /* Check if r is in the range [1, Modulus - 1] */
      /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ECDSA_NOTSET/FINISH/0002,1 */
      if (
          (CRYPTO_XVIX_XAIX_LN_E_LARGER == ComparisonZero)
          &&
          (CRYPTO_XVIX_XAIX_LN_E_SMALLER == ComparisonModulus)
         )
      {
        /* tmp1: s = last half of bytes of Signature */
        /* The return value is ignored because the parameters are either from the context where they are
         properly defined or local variables which are properly defined before passing them to
         the function.*/
        (void)Crypto_xVIx_xAIx_LNBEByteArrayToNumber
        (
          &(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputPtr[signatureComponentLength]),
          signatureComponentLength,
          workspace->tmp1,
          CRYPTO_XVIX_XAIX_ECC_NUM_LEN_WORDS
        );

        /* Check the validity of s */
        /* Compare s with zero */
        ComparisonZero = Crypto_xVIx_xAIx_LNCompareNumbers
                      (
                        workspace->tmp1,
                        workspace->tmp3
                      );
        /* Compare s with Modulus */
        ComparisonModulus = Crypto_xVIx_xAIx_LNCompareNumbers
                      (
                        workspace->tmp1,
                        Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->eccCtxPtr->curveIndex].modulus
                      );

        /* Check if s is in the range [1, Modulus - 1] */
        /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ECDSA_NOTSET/FINISH/0003,1 */
        if (
            (CRYPTO_XVIX_XAIX_LN_E_LARGER == ComparisonZero)
            &&
            (CRYPTO_XVIX_XAIX_LN_E_SMALLER == ComparisonModulus)
           )
        {
        }
        else
        {
          *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.verifyPtr) = CRYPTO_E_VER_NOT_OK;
          workspace->smOperationDone |= CRYPTO_OPERATIONMODE_FINISH;
          workspace->smResult         = E_OK;
          /* Deviation TASKING-1 */
          CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH(result, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType));
        }
      }
      else
      {
        *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.verifyPtr) = CRYPTO_E_VER_NOT_OK;
        workspace->smOperationDone |= CRYPTO_OPERATIONMODE_FINISH;
        workspace->smResult         = E_OK;
        /* Deviation TASKING-1 */
        CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH(result, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType));
      }
    }
  }

  workspace->smResult = result;

  return E_OK;

}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishExtractRS2FinishComputeU1 ---------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExtractRS2FinishComputeU1
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(job);
  TS_PARAM_UNUSED(primitive);

  /* tmpPointPtr->xValue = s^(-1) % Modulus */
  Crypto_xVIx_xAIx_LNInversion
  (
    workspace->tmpPointPtr->xValue,
    workspace->tmp1,
    workspace->tmp2,
    workspace->tmp3,
    workspace->tmp4,
    Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->eccCtxPtr->curveIndex].modulus,
    &(workspace->eccCtxPtr->lnCtx)
  );

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishComputeU12FinishComputeU2 ---------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishComputeU12FinishComputeU2
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  Std_ReturnType result   = E_OK;

  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(job);
  TS_PARAM_UNUSED(primitive);

  /* tmp2 = e = Hash(data) */
  /* The return value is ignored because the parameters are either from the context where they are
   properly defined or local variables which are properly defined before passing them to
   the function.*/
  (void)Crypto_xVIx_xAIx_LNBEByteArrayToNumber
  (
    workspace->hashResult,
    workspace->hashResultLength,
    workspace->tmp2,
    CRYPTO_XVIX_XAIX_ECC_NUM_LEN_WORDS
  );

  /* tmp5 = u = e*s^(-1) % Modulus */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    workspace->tmp5,
    workspace->tmp2,
    workspace->tmpPointPtr->xValue,
    &(workspace->eccCtxPtr->lnCtx)
  );
  Crypto_xVIx_xAIx_LNModulo
  (
    workspace->tmp5,
    Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->eccCtxPtr->curveIndex].modulus,
    &(workspace->eccCtxPtr->lnCtx)
  );

  workspace->smResult = result;

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishComputeU22FinishComputeX --------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishComputeU22FinishComputeX
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(primitive);
  TS_PARAM_UNUSED(job);

  /* xPtr = u*G */
  Crypto_xVIx_xAIx_ECPointMultiplication
  (
    workspace->xPtr,
    &(Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->eccCtxPtr->curveIndex].basePoint),
    workspace->tmp5,
    workspace->tmp1,
    workspace->tmp2,
    workspace->tmp3,
    workspace->tmp4,
    workspace->eccCtxPtr
  );

  /* tmp5 = r * s^(-1) */
  Crypto_xVIx_xAIx_LNMultiplyNumbers
  (
    workspace->tmp5,
    workspace->R,
    workspace->tmpPointPtr->xValue,
    &(workspace->eccCtxPtr->lnCtx)
  );

  /* tmp5 = v = r * s^(-1) % Modulus */
  Crypto_xVIx_xAIx_LNModulo
  (
    workspace->tmp5,
    Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->eccCtxPtr->curveIndex].modulus,
    &(workspace->eccCtxPtr->lnCtx)
  );

   /* tmpPointPtr = v*Q */
   Crypto_xVIx_xAIx_ECPointMultiplication
   (
     workspace->tmpPointPtr,
     workspace->pubKeyPtr,
     workspace->tmp5,
     workspace->tmp1,
     workspace->tmp2,
     workspace->tmp3,
     workspace->tmp4,
     workspace->eccCtxPtr
   );

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishComputeX2FinishValidateSig --------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishComputeX2FinishValidateSig
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(primitive);

  /* xPtr = R1 = u*G + v*Q */
  Crypto_xVIx_xAIx_ECPointAddition
  (
     workspace->xPtr,
     workspace->xPtr,
     workspace->tmpPointPtr,
     workspace->tmp1,
     workspace->tmp2,
     workspace->tmp3,
     workspace->tmp4,
     workspace->eccCtxPtr
  );

  /* CHECK: NOPARSE
   * There are no known test vectors which could provoke the error case which is checked here. This
   * check had been added to the official algorithm only as a precaution.
   */
  /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ECDSA_NOTSET/FINISH/0004,1 */
  if(
      TRUE ==
         Crypto_xVIx_xAIx_ECProjectivePointOfInfinity(workspace->xPtr)
    )
  {
    *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.verifyPtr) = CRYPTO_E_VER_NOT_OK;
    workspace->smOperationDone |= CRYPTO_OPERATIONMODE_FINISH;
    workspace->smResult         = E_OK;
    /* Deviation MISRAC2012-2 <+2> */
    /* Deviation TASKING-1 */
    CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType));
  }
  else
  {
    /* Since the calculation returns a point in standard projective
     * coordinates, a transformation to affine coordinates is needed.
     * After the transformation, xPtr->xValue = x_R = r1.
     */
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ECDSA_NOTSET/FINISH/0005,1 */
    Crypto_xVIx_xAIx_Procedure_EccPointConvertProj2Aff
    (
      workspace->xPtr,
      workspace->tmp1,
      workspace->eccCtxPtr
    );
    /* CHECK: PARSE */

  }
  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishValidateSig2StartIdle -------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishValidateSig2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  Std_ReturnType ret = E_NOT_OK;
  uint32                      i;
  Crypto_xVIx_xAIx_LNWordType CompareResult = 0U;
  Crypto_VerifyResultType     resultVerify        = CRYPTO_E_VER_OK;

  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(job);
  TS_PARAM_UNUSED(primitive);

  /* xPtr->xValue = r1 % Modulus */
  Crypto_xVIx_xAIx_LNModulo
  (
    workspace->xPtr->xValue,
    Crypto_xVIx_xAIx_EllipticCurveInfo[workspace->eccCtxPtr->curveIndex].modulus,
    &(workspace->eccCtxPtr->lnCtx)
  );

  /* Verify that r1 % Modulus = r
   * Please note that the first round of the for loop checks that both numbers have the same
   * length while the rest of the rounds check that the words of the numbers are identical.
   * If r1 % Modulus is shorter than r, the for loop will read array elements for the shorter
   * number which may contain garbage. But it does not matter because the signature verification has
   * already failed and we are guaranteed to not read beyond the actual length of the arrays.
   */
  /* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_ECDSA_NOTSET/FINISH/0006,1 */
  for(i = 0U; i <= workspace->R[0U]; i++)
  {
    CompareResult |= workspace->xPtr->xValue[i] ^ workspace->R[i];
  }
  if(0U != CompareResult)
  {
    resultVerify = CRYPTO_E_VER_NOT_OK;
  }

  *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.verifyPtr) = resultVerify;
  ret = E_OK;
  /* Deviation TASKING-1 */
  CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH(ret, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType));

  return ret;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle ------------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveCancel2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType);
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
  CRYPTO_XVIX_XAIX_SET_SMRESULT_CANCEL(CRYPTO_E_JOB_CANCELED, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[end of file]=================================================================*/

