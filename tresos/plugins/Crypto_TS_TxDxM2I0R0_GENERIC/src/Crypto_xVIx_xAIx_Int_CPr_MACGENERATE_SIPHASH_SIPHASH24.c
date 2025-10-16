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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_MACGENERATE_SIPHASH_SIPHASH24.c/0001,1 */

/*==================[deviations]==================================================================*/

/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 2.1 (required)
 * A project shall not contain unreachable code.
 *
 * Reason:
 * The given warnings at this point are false positives, as the macro itself is fully tested
 * for all possible paths of a ternary operator. But a given call of the macro will always go either
 * way of checking the length of the shift width.
 *
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
 * CODEMETRIC-1) Deviated Rule: HIS_VOCF
 * not 23.36 <= 12
 *
 * Reason:
 * Improving this software quality metric is only possible by splitting up the function
 * which would adversely effect the performance of the primitive. For cryptographic algorithms,
 * a high number of operators/operands are needed for the implementation.
 */

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int.h>                                        /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_MACGENERATE_SIPHASH_SIPHASH24.c/0002,1 */
#include <Crypto_xVIx_xAIx_Int_KeyManagement.h>                          /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_MACGENERATE_SIPHASH_SIPHASH24.c/0003,1 */
#include <Crypto_xVIx_xAIx_Int_CPr_MACGENERATE_SIPHASH_SIPHASH24.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_MACGENERATE_SIPHASH_SIPHASH24.c/0004,1 */

/*==================[macros]======================================================================*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
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

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS)
#error CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS already defined
#endif
/** \brief  The FinishProcess state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS 7U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSLASTBLOCK)
#error CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSLASTBLOCK already defined
#endif
/** \brief  The FinishProcessLastBlock state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSLASTBLOCK 8U

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

/* !LINKSTO Crypto.Req.CPr/MACGENERATE_SIPHASH_SIPHASH24/GENERAL/0002,1 */
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_SIPHASH_SIPHASH_2_4_C_ITERATIONS,1 */
#if (defined CRYPTO_XVIX_XAIX_SIPHASH_SIPHASH_2_4_C_ITERATIONS)
#error CRYPTO_XVIX_XAIX_SIPHASH_SIPHASH_2_4_C_ITERATIONS already defined
#endif
/** \brief  The number of C iterations for the SipHash-2-4. **/
#define CRYPTO_XVIX_XAIX_SIPHASH_SIPHASH_2_4_C_ITERATIONS 2U

/* !LINKSTO Crypto.Req.CPr/MACGENERATE_SIPHASH_SIPHASH24/GENERAL/0003,1 */
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_SIPHASH_SIPHASH_2_4_D_ITERATIONS,1 */
#if (defined CRYPTO_XVIX_XAIX_SIPHASH_SIPHASH_2_4_D_ITERATIONS)
#error CRYPTO_XVIX_XAIX_SIPHASH_SIPHASH_2_4_D_ITERATIONS already defined
#endif
/** \brief  The number of D iterations for the SipHash-2-4. **/
#define CRYPTO_XVIX_XAIX_SIPHASH_SIPHASH_2_4_D_ITERATIONS 4U

/* !LINKSTO Crypto.Req.CPr/MACGENERATE_SIPHASH_SIPHASH24/GENERAL/0008,1 */
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_SIPHASH_INITV0,1 */
#if (defined CRYPTO_XVIX_XAIX_SIPHASH_INITV0)
#error CRYPTO_XVIX_XAIX_SIPHASH_INITV0 already defined
#endif
/** \brief  One part of the initialization value for state v0. **/
#define CRYPTO_XVIX_XAIX_SIPHASH_INITV0 0x736F6D6570736575ULL

/* !LINKSTO Crypto.Req.CPr/MACGENERATE_SIPHASH_SIPHASH24/GENERAL/0009,1 */
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_SIPHASH_INITV1,1 */
#if (defined CRYPTO_XVIX_XAIX_SIPHASH_INITV1)
#error CRYPTO_XVIX_XAIX_SIPHASH_INITV1 already defined
#endif
/** \brief  One part of the initialization value for state v1. **/
#define CRYPTO_XVIX_XAIX_SIPHASH_INITV1 0x646F72616E646F6DULL

/* !LINKSTO Crypto.Req.CPr/MACGENERATE_SIPHASH_SIPHASH24/GENERAL/0010,1 */
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_SIPHASH_INITV2,1 */
#if (defined CRYPTO_XVIX_XAIX_SIPHASH_INITV2)
#error CRYPTO_XVIX_XAIX_SIPHASH_INITV2 already defined
#endif
/** \brief  One part of the initialization value for state v2. **/
#define CRYPTO_XVIX_XAIX_SIPHASH_INITV2 0x6C7967656E657261ULL

/* !LINKSTO Crypto.Req.CPr/MACGENERATE_SIPHASH_SIPHASH24/GENERAL/0011,1 */
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_SIPHASH_INITV3,1 */
#if (defined CRYPTO_XVIX_XAIX_SIPHASH_INITV3)
#error CRYPTO_XVIX_XAIX_SIPHASH_INITV3 already defined
#endif
/** \brief  One part of the initialization value for state v3. **/
#define CRYPTO_XVIX_XAIX_SIPHASH_INITV3 0x7465646279746573ULL

/* !LINKSTO Crypto.Req.CPr/MACGENERATE_SIPHASH_SIPHASH24/GENERAL/0016,1 */
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_SIPHASH_SIPROUND,1 */
#if (defined CRYPTO_XVIX_XAIX_SIPHASH_SIPROUND)
#error CRYPTO_XVIX_XAIX_SIPHASH_SIPROUND already defined
#endif
/** \brief  Transformation of the internal states V0, V1, V2, V3 using an ARX network. **/
#define CRYPTO_XVIX_XAIX_SIPHASH_SIPROUND(V0, V1, V2, V3) \
do                                                        \
{                                                         \
    (V0)  = CRYPTO_XVIX_XAIX_ADD64((V0), (V1));           \
    (V1)  = CRYPTO_XVIX_XAIX_ROL64((V1), 13U );           \
    (V1)  = CRYPTO_XVIX_XAIX_XOR64((V1), (V0));           \
    (V0)  = CRYPTO_XVIX_XAIX_ROL64((V0), 32U );           \
                                                          \
    (V2)  = CRYPTO_XVIX_XAIX_ADD64((V2), (V3));           \
    (V3)  = CRYPTO_XVIX_XAIX_ROL64((V3), 16U );           \
    (V3)  = CRYPTO_XVIX_XAIX_XOR64((V3), (V2));           \
                                                          \
    (V0)  = CRYPTO_XVIX_XAIX_ADD64((V0), (V3));           \
    (V3)  = CRYPTO_XVIX_XAIX_ROL64((V3), 21U );           \
    (V3)  = CRYPTO_XVIX_XAIX_XOR64((V3), (V0));           \
                                                          \
    (V2)  = CRYPTO_XVIX_XAIX_ADD64((V2), (V1));           \
    (V1)  = CRYPTO_XVIX_XAIX_ROL64((V1), 17U );           \
    (V1)  = CRYPTO_XVIX_XAIX_XOR64((V1), (V2));           \
    (V2)  = CRYPTO_XVIX_XAIX_ROL64((V2), 32U );           \
}                                                         \
while (0U)

#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
static FUNC(boolean, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetNextState
(
  P2VAR(uint8,                                         AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) smStateIndx,
        Crypto_xVIx_xAIx_PrimitiveStateIdentifierType                                         curState,
        Std_ReturnType                                                                        resultAction,
        Crypto_ProcessingType                                                                 jobProcessing,
  P2VAR(Crypto_xVIx_xAIx_PrimitiveStateIdentifierType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) nxtState
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */
/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_STARTEXEC'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE'.
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

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK  Request successful.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE'.
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHEXEC'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS'.
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

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
 ** \retval  CRYPTO_E_JOB_CANCELED  Job has been canceled.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

/** \brief  State action function for states
 **         'CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS' or
 **         'CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK           Request successful.
 ** \retval  CRYPTO_E_BUSY  Processing still ongoing.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateFinishProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSLASTBLOCK'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK Request successful.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishProcess2FinishProcessLastBlock
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSLASTBLOCK'
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
 ** \retval  E_NOT_OK  Request failed.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishProcessLastBlock2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal constants]==========================================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  The primitives state transition table. **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_StateTransitionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateTransitionType, CRYPTO_xVIx_xAIx_CONST)
Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Process_StateTransitionTable[CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT] =
{
  { NULL_PTR,                                                           CRYPTO_XVIX_XAIX_STATE_STARTIDLE,              CRYPTO_XVIX_XAIX_STATE_STARTIDLE,              CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE_TO_CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1               */
  { Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle,                 CRYPTO_XVIX_XAIX_STATE_STARTEXEC,              CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,             CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { NULL_PTR,                                                           CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,             CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,             CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE_TO_CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE/0001,1             */

  { Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess,             CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC,             CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,          CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { NULL_PTR,                                                           CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,          CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,          CRYPTO_XVIX_XAIX_PROCESSING_BOTH, CRYPTO_E_BUSY },
  { Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle,       CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,          CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,       CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { NULL_PTR,                                                           CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,       CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,       CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE_TO_CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE/0001,1 */

  { Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishProcess,             CRYPTO_XVIX_XAIX_STATE_FINISHEXEC,             CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS,          CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { Crypto_xVIx_xAIx_StateMachine_FinishProcess2FinishProcessLastBlock, CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS,          CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSLASTBLOCK, CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { Crypto_xVIx_xAIx_StateMachine_FinishProcessLastBlock2StartIdle,     CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSLASTBLOCK, CRYPTO_XVIX_XAIX_STATE_STARTIDLE,              CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle,                     CRYPTO_XVIX_XAIX_STATE_CANCEL,                 CRYPTO_XVIX_XAIX_STATE_STARTIDLE,              CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { Crypto_xVIx_xAIx_StateMachine_Error2StartIdle,                      CRYPTO_XVIX_XAIX_STATE_ERROR,                  CRYPTO_XVIX_XAIX_STATE_STARTIDLE,              CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          }
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

/** \brief  The primitives state action table. **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_StateActionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateActionType, CRYPTO_xVIx_xAIx_CONST)
Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Process_StateActionTable[CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT] =
{
  /* CRYPTO_XVIX_XAIX_STATE_STARTIDLE              */ { NULL_PTR                                          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1        */
  /* CRYPTO_XVIX_XAIX_STATE_STARTEXEC              */ { Crypto_xVIx_xAIx_StateMachine_StartProcess        }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTEXEC/0001,1        */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE             */ { NULL_PTR                                          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC             */ { NULL_PTR                                          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS          */ { Crypto_xVIx_xAIx_StateMachine_UpdateFinishProcess },
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE       */ { NULL_PTR                                          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE/0001,1 */
  /* CRYPTO_XVIX_XAIX_STATE_FINISHEXEC             */ { NULL_PTR                                          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_FINISHEXEC/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS          */ { NULL_PTR                                          },
  /* CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSLASTBLOCK */ { NULL_PTR                                          },
  /* CRYPTO_XVIX_XAIX_STATE_CANCEL                 */ { NULL_PTR                                          },
  /* CRYPTO_XVIX_XAIX_STATE_ERROR                  */ { NULL_PTR                                          },
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Process ---------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Process/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Process
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_WorkspaceType);

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
    (void) Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Reset(workspace->paObjectId, job, primitive);
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
        (void) Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Main(objectId, job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Main ------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Main/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Main
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_WorkspaceType);

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
    if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Process_StateActionTable[curState].fcnAction))
    {
      resultAction = Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Process_StateActionTable[curState].fcnAction(job, primitive);
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
      if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Process_StateTransitionTable[smStateIndx].fcnTransition))
      {
        /* transition function returns using workspace->smResult */
        (void) Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Process_StateTransitionTable[smStateIndx].fcnTransition(job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Cancel ----------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Cancel/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Cancel
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_WorkspaceType);

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
      (void) Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Main(objectId, job, primitive);
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Reset -----------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Reset/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Reset
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as
   * secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESET(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_WorkspaceType));
    result = E_OK;
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Restart -----------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Restart/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Restart
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESTART(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_WorkspaceType));
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Callback --------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Callback/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
/* CHECK: NOPARSE
 * This API is only reachable for cryptographic primitives that are using a secondary primitive.
 */
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_WorkspaceType);

  TS_PARAM_UNUSED(objectId);
  TS_PARAM_UNUSED(job);
  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Callback/0002,1 */
  workspace->notifyType   = cbkType;
  workspace->notifyResult = cbkResult;

  return E_OK;
}
/* CHECK: PARSE */
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_StateMachine_Error2StartIdle ----------------------------------------------*/

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveError2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_WorkspaceType);

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
  result              = Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Reset(workspace->paObjectId, job, primitive);
  workspace->smResult = smResult;

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

/*--- Crypto_xVIx_xAIx_GetNextState --------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
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
    if (   (Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx   = i;
      break;
    }
  }

  /* CHECK: NOPARSE
   * The FOR loop condition (i < *smStateIndx) is always FALSE for MACGENERATE_SIPHASH_SIPHASH24, because the state
   * transition table of this cryptographic primitive is complete, except for the case when the
   * CRYPTO_XVIX_XAIX_STATE_STARTEXEC returns an action result of not E_OK. In this case the
   * previous FOR loop always iterates from i = 0 to CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT.
   */
  /* 2) iterate from first table entry to last found entry in table */
  for (i = 0U; (FALSE == nxtStateFound) && (i < *smStateIndx); i++)
  {
    if (   (Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx  = i;
      break;
    }
  }
  /* CHECK: PARSE */

  return nxtStateFound;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */
/* --- Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle --------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Start2Update,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;
  uint64         key0   = 0U;
  uint64         key1   = 0U;

  /* Extract key. */
  /* !LINKSTO Crypto.Req.CPr/MACGENERATE_SIPHASH_SIPHASH24/GENERAL/0006,1 */
  key0 = CRYPTO_XVIX_XAIX_UINT64_UINT8_TO_UINT64_LE(workspace->KeyData);
  /* !LINKSTO Crypto.Req.CPr/MACGENERATE_SIPHASH_SIPHASH24/GENERAL/0007,1 */
  key1 = CRYPTO_XVIX_XAIX_UINT64_UINT8_TO_UINT64_LE(&workspace->KeyData[CRYPTO_XVIX_XAIX_CPR_MACGENERATE_SIPHASH_SIPHASH24_KEY_LEN_BYTES >> 1U]);

  /* Initialize state variables. */
  /* !LINKSTO Crypto.Req.CPr/MACGENERATE_SIPHASH_SIPHASH24/GENERAL/0008,1 */
  /* !LINKSTO Crypto.Req.CPr/MACGENERATE_SIPHASH_SIPHASH24/GENERAL/0010,1 */
  /* !LINKSTO Crypto.Req.CPr/MACGENERATE_SIPHASH_SIPHASH24/GENERAL/0009,1 */
  /* !LINKSTO Crypto.Req.CPr/MACGENERATE_SIPHASH_SIPHASH24/GENERAL/0011,1 */
  workspace->V0 = CRYPTO_XVIX_XAIX_XOR64(key0, CRYPTO_XVIX_XAIX_SIPHASH_INITV0);
  workspace->V1 = CRYPTO_XVIX_XAIX_XOR64(key1, CRYPTO_XVIX_XAIX_SIPHASH_INITV1);
  workspace->V2 = CRYPTO_XVIX_XAIX_XOR64(key0, CRYPTO_XVIX_XAIX_SIPHASH_INITV2);
  workspace->V3 = CRYPTO_XVIX_XAIX_XOR64(key1, CRYPTO_XVIX_XAIX_SIPHASH_INITV3);

  workspace->TotalNumberOfBytes = 0U;
  workspace->RemainingBytes     = 0U;

  workspace->smResult         = E_OK;
  workspace->smOperationDone |= CRYPTO_OPERATIONMODE_START;
  CRYPTO_XVIX_XAIX_SET_SMRESULT_START(workspace->smResult, sizeof(Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_WorkspaceType));

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess------------------------------------ */

/* !LINKSTO Crypto.Dsn.JobTransition.Update2Update,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_WorkspaceType);

  workspace->DataPtr      = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr;
  workspace->DataLength   = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength;
  workspace->notifyResult = CRYPTO_E_BUSY;

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateFinishProcess ---------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
/* Deviation CODEMETRIC-2 */
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateFinishProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;
  uint64         shift  = 0ULL;
  uint64         i      = 0ULL;

  TS_PARAM_UNUSED(job);

  /* !LINKSTO Crypto.Req.CPr/MACGENERATE_SIPHASH_SIPHASH24/GENERAL/0012,1 */
  if (CRYPTO_XVIX_XAIX_CPR_MACGENERATE_SIPHASH_SIPHASH24_BLOCK_LEN_BYTES <= (workspace->DataLength + workspace->RemainingBytes))
  {
    /* We have enough data to fill a complete block to compress and we know that the
     * block will not be the last.
     */
    if (0U == workspace->RemainingBytes)
    {
      /* Extract single block (64 bit). */
      workspace->MessageBlock = CRYPTO_XVIX_XAIX_UINT64_UINT8_TO_UINT64_LE(workspace->DataPtr);
    }
    else
    {
      /* Consider remaining message bytes from previous update call. */
      /* Take further bytes to fill the block. */
      shift = (uint64) workspace->RemainingBytes << 3ULL;

      for (i = (uint64) CRYPTO_XVIX_XAIX_CPR_MACGENERATE_SIPHASH_SIPHASH24_BLOCK_LEN_BYTES - workspace->RemainingBytes; i > 0U; i--)
      {
      /* Deviation MISRAC2012-1 */
        workspace->MessageBlock = CRYPTO_XVIX_XAIX_OR64(workspace->MessageBlock,
                                                        CRYPTO_XVIX_XAIX_SHL64(workspace->DataPtr[i - 1ULL],
                                                                               shift + (((uint64) i - 1ULL ) << 3ULL)
                                                                              )
                                                       );
      }
    }
    /* Process a single block (64 bit). */
    /* !LINKSTO Crypto.Req.CPr/MACGENERATE_SIPHASH_SIPHASH24/GENERAL/0014,1 */
    workspace->V3 = CRYPTO_XVIX_XAIX_XOR64(workspace->V3, workspace->MessageBlock);
    for (i = 0U; i < CRYPTO_XVIX_XAIX_SIPHASH_SIPHASH_2_4_C_ITERATIONS; i++)
    {
      CRYPTO_XVIX_XAIX_SIPHASH_SIPROUND(workspace->V0,
                                        workspace->V1,
                                        workspace->V2,
                                        workspace->V3
                                       );
    }
    workspace->V0 = CRYPTO_XVIX_XAIX_XOR64(workspace->V0, workspace->MessageBlock);
    /* Skip the bytes we have read in the input data. */
    workspace->DataPtr = &workspace->DataPtr[CRYPTO_XVIX_XAIX_CPR_MACGENERATE_SIPHASH_SIPHASH24_BLOCK_LEN_BYTES - workspace->RemainingBytes];

    workspace->DataLength -= (CRYPTO_XVIX_XAIX_CPR_MACGENERATE_SIPHASH_SIPHASH24_BLOCK_LEN_BYTES - workspace->RemainingBytes);

    /* Increase the number of total bytes. */
    workspace->TotalNumberOfBytes += (  CRYPTO_XVIX_XAIX_CPR_MACGENERATE_SIPHASH_SIPHASH24_BLOCK_LEN_BYTES
                                      - workspace->RemainingBytes
                                     );

    /* Reset remaining message bytes. */
    workspace->RemainingBytes = 0U;
    workspace->notifyResult   = CRYPTO_E_BUSY;
    result                    = CRYPTO_E_BUSY;
  }
  else
  {
    /* We do not have enough input data to fill a complete block or we do not know
     * whether the block will be the last one.
     */
    /* Determine the number of total message bytes by adding the remaining message bytes. */
    workspace->TotalNumberOfBytes +=  workspace->DataLength;

    /* Clear block only if number of remaining bytes are zero, i.e. start case or a previous block
     * was completed. */
    if (0U == workspace->RemainingBytes)
    {
      workspace->MessageBlock = 0ULL;
    }

    /* Determine the number of remaining bytes. Consider remaining bytes from a previous update
     * call. */
    workspace->RemainingBytes += workspace->DataLength;

    /* Respect the data already written to the message block. */
    shift = ((uint64) workspace->RemainingBytes -  workspace->DataLength) << 3U;

    /* Fill block with remaining data bytes. */
    for (i = workspace->DataLength; i > 0U; i--)
    {
      /* Deviation MISRAC2012-1 */
      workspace->MessageBlock = CRYPTO_XVIX_XAIX_OR64(workspace->MessageBlock,
                                                        CRYPTO_XVIX_XAIX_SHL64(workspace->DataPtr[i - 1ULL],
                                                                               shift + (((uint64) i - 1ULL) << 3ULL)
                                                                              )
                                                     );
    }
    /* Reset data length. */
    workspace->DataLength = 0U;
    result                = E_OK;
  }

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle ----------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Update2Finish,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_WorkspaceType);

  workspace->smResult         = workspace->smResult;
  workspace->smOperationDone |= CRYPTO_OPERATIONMODE_UPDATE;
  CRYPTO_XVIX_XAIX_SET_SMRESULT_UPDATE(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_WorkspaceType));

  return E_OK;
}
#endif /*CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON*/

/* --- Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishProcess ----------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(primitive);

  /* Store data into context. */
  if (CRYPTO_XVIX_XAIX_CPR_MACGENERATE_SIPHASH_SIPHASH24_BLOCK_LEN_BYTES < *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr))
  {
    /* Set length of result. Limit to block length. */
    /* !LINKSTO Crypto.Req.CPr/MACGENERATE_SIPHASH_SIPHASH24/GENERAL/0020,1 */
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00135,1 */
    *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr) = CRYPTO_XVIX_XAIX_CPR_MACGENERATE_SIPHASH_SIPHASH24_BLOCK_LEN_BYTES;
  }
  result = E_OK;

  return result;
}
#endif /*CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON*/

/* --- Crypto_xVIx_xAIx_StateMachine_FinishProcess2FinishProcessLastBlock ----------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
/* Deviation CODEMETRIC-1 */
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishProcess2FinishProcessLastBlock
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_WorkspaceType);

        uint8  i    = 0U;
  const uint64 temp = 0xFFU;

  TS_PARAM_UNUSED(job);

  /* Process the last block. */
  /* Fill the number of total message bytes modulo 256. */
  /* !LINKSTO Crypto.Req.CPr/MACGENERATE_SIPHASH_SIPHASH24/GENERAL/0013,1 */
  /* Deviation MISRAC2012-1 */
  workspace->MessageBlock = CRYPTO_XVIX_XAIX_OR64(workspace->MessageBlock,
                                                  CRYPTO_XVIX_XAIX_SHL64((workspace->TotalNumberOfBytes),
                                                                         56U
                                                                        )
                                                 );

  /* Process a single block (64 bit). */
  /* !LINKSTO Crypto.Req.CPr/MACGENERATE_SIPHASH_SIPHASH24/GENERAL/0014,1 */
  workspace->V3 = CRYPTO_XVIX_XAIX_XOR64(workspace->V3, workspace->MessageBlock);

  for (i = 0U; i < CRYPTO_XVIX_XAIX_SIPHASH_SIPHASH_2_4_C_ITERATIONS; i++)
  {
    CRYPTO_XVIX_XAIX_SIPHASH_SIPROUND(workspace->V0,
                                      workspace->V1,
                                      workspace->V2,
                                      workspace->V3
                                     );
  }

  workspace->V0 = CRYPTO_XVIX_XAIX_XOR64(workspace->V0, workspace->MessageBlock);

  /* XOR the constant 0xFF to the state V2. Perform d x SipRound. */
  /* !LINKSTO Crypto.Req.CPr/MACGENERATE_SIPHASH_SIPHASH24/GENERAL/0015,1 */
  workspace->V2 = CRYPTO_XVIX_XAIX_XOR64(workspace->V2, temp);

  for (i = 0U; i < CRYPTO_XVIX_XAIX_SIPHASH_SIPHASH_2_4_D_ITERATIONS; i++)
  {
    CRYPTO_XVIX_XAIX_SIPHASH_SIPROUND(workspace->V0,
                                      workspace->V1,
                                      workspace->V2,
                                      workspace->V3
                                     );
  }

  /* XOR all state variables. Finally,the result is available in state variable V0. */
  workspace->V0 = CRYPTO_XVIX_XAIX_XOR64(workspace->V0, workspace->V1);
  workspace->V0 = CRYPTO_XVIX_XAIX_XOR64(workspace->V0, workspace->V2);
  workspace->V0 = CRYPTO_XVIX_XAIX_XOR64(workspace->V0, workspace->V3);
  if (CRYPTO_XVIX_XAIX_CPR_MACGENERATE_SIPHASH_SIPHASH24_BLOCK_LEN_BYTES == *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr))
  {
    CRYPTO_XVIX_XAIX_UINT64_UINT64_TO_UINT8_LE(workspace->V0,
                                               job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr
                                              );
  }
  else
  {
    /* !LINKSTO Crypto.Req.CPr/MACGENERATE_SIPHASH_SIPHASH24/GENERAL/0019,1 */
    for (i = 0U; i < *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr); i++)
    {
      /* Deviation MISRAC2012-1 */
      job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr[i] = (uint64) CRYPTO_XVIX_XAIX_UINT64_GET_LOW_BYTE(CRYPTO_XVIX_XAIX_SHR64(((uint64) workspace->V0), ((uint64) i << 3U)));
    }
  }

  return E_OK;
}
#endif /*CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON*/

/* --- Crypto_xVIx_xAIx_StateMachine_FinishProcessLastBlock2StartIdle --------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Finish2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishProcessLastBlock2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  workspace->smResult         = E_OK;
  workspace->smOperationDone |= CRYPTO_OPERATIONMODE_FINISH;
  CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH(workspace->smResult, sizeof(Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_WorkspaceType));

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle ------------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveCancel2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_WorkspaceType);

  /* !LINKSTO Crypto.Asr.SWS_Crypto_00183,2 */
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00144,1 */
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00181_1,1 */
  CRYPTO_XVIX_XAIX_SET_SMRESULT_CANCEL(CRYPTO_E_JOB_CANCELED, sizeof(Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_StartProcess ----------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_WorkspaceType);

          Std_ReturnType                                                          result        = E_NOT_OK;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyPtr        = NULL_PTR;
  boolean                                                                         fromPrimitive = FALSE;

  result = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( job->cryptoKeyId,
                                                      CRYPTO_KE_MAC_KEY,
                                                     &keyPtr,
                                                      FALSE,
                                                      CRYPTO_XVIX_XAIX_SID_EMPTY
                                                    );
  if (E_OK == result)
  {
    fromPrimitive = TRUE;
    /* Deviation TASKING-1 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(result, keyPtr, fromPrimitive);
    if (E_OK == result)
    {
      if (CRYPTO_XVIX_XAIX_CPR_MACGENERATE_SIPHASH_SIPHASH24_KEY_LEN_BYTES != keyPtr->data->size)
      {
        /* !LINKSTO Crypto.Req.CPr/MACGENERATE_SIPHASH_SIPHASH24/GENERAL/0021,1 */
        workspace->smResult         = E_NOT_OK;
        workspace->smOperationDone |= CRYPTO_OPERATIONMODE_START;
        result                      = E_NOT_OK;
      }
      else
      {
        TS_MemCpy(workspace->KeyData, keyPtr->data->data, keyPtr->data->size);
        result = E_OK;
      }
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(keyPtr);
    }
    else
    {
      workspace->smResult         = result;
      workspace->smOperationDone |= CRYPTO_OPERATIONMODE_START;
    }
  }
  else
  {
    workspace->smResult         = E_NOT_OK;
    workspace->smOperationDone |= CRYPTO_OPERATIONMODE_START;
    result                      = E_NOT_OK;
  }

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[end of file]=================================================================*/

