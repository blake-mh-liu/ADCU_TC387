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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15.c/0001,1 */

/*==================[deviations]==================================================================*/

/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.3 (required)
 * A cast shall not be performed between a pointer to object type
 * and a pointer to a different object type.
 *
 * Reason:
 * The Key buffer is defined as cpu type and later downcasted in Crypto_xVIx_xAIx_KeyElementDataType,
 * so there will be no problems with the alignment.
 * For SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 the key is needed in long number representation format.
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
 * CODEMETRIC-1 Deviated Rule: HIS_STMT
 * not 95 <= 75
 *
 * CODEMETRIC-2) Deviated Rule: HIS_STMT
 * not 93 <= 75
 *
 * CODEMETRIC-3) Deviated Rule: HIS_PATH
 * not 4320 <= 2000
 *
 * CODEMETRIC-4) Deviated Rule: HIS_V(G)
 * not 23 <= 20
 *
 * Reason:
 * SingleCall functions are adjusted for performance and have a reduced amount of function calls
 * on purpose which leads to metric violations.
 *
, * CODEMETRIC-1) Deviated Rule: HIS_STMT
 * not 97 <= 75
 *
 * CODEMETRIC-2) Deviated Rule: HIS_STMT
 * not 95 <= 75
 *
 * CODEMETRIC-3) Deviated Rule: HIS_PATH
 * not 196560 <= 2000
 *
 * CODEMETRIC-4) Deviated Rule: HIS_V(G)
 * not 29 <= 20
 *
 * Reason:
 * SingleCall functions are adjusted for performance and have a reduced amount of function calls
 * on purpose which leads to metric violations.
 *
) */

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int.h>                                               /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15.c/0002,1 */
#include <Crypto_xVIx_xAIx_Int_KeyManagement.h>                                 /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15.c/0003,1 */
#include <Crypto_xVIx_xAIx_Int_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15.c/0004,1 */

/*==================[macros]======================================================================*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT,1 */
#if (defined CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT)
#error CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT already defined
#endif
/** \brief  Number of entries in the primitives state transition table. **/
#define CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT 11U

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
/** \brief  The FinishExec state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS 7U

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

#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
static FUNC(boolean, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetNextState
(
  P2VAR(uint8,                                         AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) smStateIndx,
        Crypto_xVIx_xAIx_PrimitiveStateIdentifierType                                         curState,
        Std_ReturnType                                                                        resultAction,
        Crypto_ProcessingType                                                                 jobProcessing,
  P2VAR(Crypto_xVIx_xAIx_PrimitiveStateIdentifierType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) nxtState
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

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
 ** \retval  E_OK      Request successful.
 ** \retval  E_NOT_OK  Request failed.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS'
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishProcess2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

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
 ** \retval  E_NOT_OK  Request failed.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

/** \brief  State action function for states
 **         'CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS'.
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

/* ---misc procedures---------------------------------------------------------------------------- */
/** \brief  Set the Algorithm Id and the Algorithm length.
 **
 ** \param[in]      job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in,out]  workspace  Pointer to the primitives workspace instance.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_SetAlgorithmId
(
  P2VAR(Crypto_JobType,                        AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2VAR(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal constants]==========================================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_8
#include <Crypto_xVIx_xAIx_MemMap.h>

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
/** \brief Array of X.509 algorithm identifiers, which the RSASSA-PKCS1-v1_5 signature generation/verification supports. **/
/* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/GENERAL/0012,1 */
static CONST(uint8, CRYPTO_xVIx_xAIx_CONST)
  Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HashAlgorithmId[9U][15U] =
{
  CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA1_ID,
  CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2224_ID,
  CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2256_ID,
  CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2384_ID,
  CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2512_ID,
  CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3224_ID,
  CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3256_ID,
  CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3384_ID,
  CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3512_ID
};
#endif /* ((CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_8
#include <Crypto_xVIx_xAIx_MemMap.h>

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  The primitives state transition table. **/

/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_StateTransitionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateTransitionType, CRYPTO_xVIx_xAIx_CONST)
Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Process_StateTransitionTable[CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT] =
{
  { NULL_PTR,                                                       CRYPTO_XVIX_XAIX_STATE_STARTIDLE,         CRYPTO_XVIX_XAIX_STATE_STARTIDLE,           CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK}, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE_TO_CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1               */
  { Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle,             CRYPTO_XVIX_XAIX_STATE_STARTEXEC,         CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,          CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK},

  { NULL_PTR,                                                       CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,        CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,          CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK}, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE_TO_CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE/0001,1             */

  { Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess,         CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC,        CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,       CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK},
  { Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle,   CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,     CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,    CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK},

  { NULL_PTR,                                                       CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,  CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,    CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK}, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE_TO_CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE/0001,1 */

  { Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishProcess,         CRYPTO_XVIX_XAIX_STATE_FINISHEXEC,        CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS,       CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK},
  { Crypto_xVIx_xAIx_StateMachine_FinishProcess2StartIdle,          CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS,     CRYPTO_XVIX_XAIX_STATE_STARTIDLE,           CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK},

  { Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle,             CRYPTO_XVIX_XAIX_STATE_SINGLECALL,        CRYPTO_XVIX_XAIX_STATE_STARTIDLE,           CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK},

  { Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle,                 CRYPTO_XVIX_XAIX_STATE_CANCEL,            CRYPTO_XVIX_XAIX_STATE_STARTIDLE,           CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK},
  { Crypto_xVIx_xAIx_StateMachine_Error2StartIdle,                  CRYPTO_XVIX_XAIX_STATE_ERROR,             CRYPTO_XVIX_XAIX_STATE_STARTIDLE,           CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK}
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

/** \brief  The primitives state action table. **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_StateActionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateActionType, CRYPTO_xVIx_xAIx_CONST)
Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Process_StateActionTable[CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT] =
{
  /* CRYPTO_XVIX_XAIX_STATE_STARTIDLE              */ { NULL_PTR                                    }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1        */
  /* CRYPTO_XVIX_XAIX_STATE_STARTEXEC              */ { Crypto_xVIx_xAIx_StateMachine_StartExec     }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTEXEC/0001,1        */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE             */ { NULL_PTR                                    }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC             */ { NULL_PTR                                    }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS          */ { NULL_PTR                                    },
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE       */ { NULL_PTR                                    }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE/0001,1 */
  /* CRYPTO_XVIX_XAIX_STATE_FINISHEXEC             */ { NULL_PTR                                    }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_FINISHEXEC/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS          */ { Crypto_xVIx_xAIx_StateMachine_FinishProcess },
  /* CRYPTO_XVIX_XAIX_STATE_SINGLECALL             */ { NULL_PTR                                    },
  /* CRYPTO_XVIX_XAIX_STATE_CANCEL                 */ { NULL_PTR                                    },
  /* CRYPTO_XVIX_XAIX_STATE_ERROR                  */ { NULL_PTR                                    }
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Process --------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Process/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Process
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType);

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
    (void) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Reset(workspace->paObjectId, job, primitive);
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
        (void) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Main(objectId, job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Main -----------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Main/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Main
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType);

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
    if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Process_StateActionTable[curState].fcnAction))
    {
      resultAction = Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Process_StateActionTable[curState].fcnAction(job, primitive);
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
      if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Process_StateTransitionTable[smStateIndx].fcnTransition))
      {
        /* transition function returns using workspace->smResult */
        (void) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Process_StateTransitionTable[smStateIndx].fcnTransition(job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Cancel ---------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Cancel/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Cancel
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType);

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
      (void) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Main(objectId, job, primitive);
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Reset ----------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Reset/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Reset
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as
   * secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESET(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType));
    result = E_OK;
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Restart ----------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Restart/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Restart
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESTART(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType));
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Callback -------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Callback/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
/* CHECK: NOPARSE
 * This API is only reachable for cryptographic primitives that are using a secondary primitive.
 */
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType);

  TS_PARAM_UNUSED(objectId);
  TS_PARAM_UNUSED(job);
  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Callback/0002,1 */
  workspace->notifyType   = cbkType;
  workspace->notifyResult = cbkResult;

  return E_OK;
}
/* CHECK: PARSE */
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_StateMachine_Error2StartIdle ----------------------------------------------*/

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveError2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType);

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
  result              = Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Reset(workspace->paObjectId, job, primitive);
  workspace->smResult = smResult;

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

/*--- Crypto_xVIx_xAIx_GetNextState --------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
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
    if (   (Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx   = i;
      break;
    }
  }

  /* 2) iterate from first table entry to last found entry in table */
  for (i = 0U; (FALSE == nxtStateFound) && (i < *smStateIndx); i++)
  {
    if (   (Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx  = i;
      break;
    }
  }

  return nxtStateFound;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */
/* --- Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle --------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Start2Update,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{

  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/GENERAL/0013,1 */
  if (     (NULL_PTR != primitive->cnfg->heap)
       && ((workspace->modulusLen * (2U + (2U * CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES))) < primitive->cnfg->heapSize)
     )
  {
    /* Reset heap */
    TS_MemBZero(primitive->cnfg->heap, primitive->cnfg->heapSize);

    /* create secondary job */
    CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB();
    CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_KEY();

    /* Get the secondary family hash algorithm length */
    workspace->hashLength = Crypto_xVIx_xAIx_GetHashLen(job->jobPrimitiveInfo->primitiveInfo->algorithm.secondaryFamily);

    /* CHECK: NOPARSE
     * In order to avoid the incorrect secondaryFamily configuration in Csm check is needed. This check is always true.
     */
    if(0U != workspace->hashLength)
    {
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode = CRYPTO_OPERATIONMODE_START;

      primitive->P2->data->P1 = primitive;
      /* calling the secondary primitive START. */
      result = primitive->P2->cnfg->description->fcnProcess(  workspace->paObjectId,
                                                            &(workspace->secondaryJob),
                                                              workspace->paPrimitive->P2
                                                          );
      /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/START/0007,1 */
    }
    /* CHECK: PARSE */
  }

  CRYPTO_XVIX_XAIX_SET_SMRESULT_START(result, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess------------------------------------ */

/* Crypto.Dsn.JobTransition.Update2Update,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(job);

  /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/UPDATE/0001,1 */
  /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/UPDATE/0002,1 */
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode            = CRYPTO_OPERATIONMODE_UPDATE;

  CRYPTO_XVIX_XAIX_RESET_CALLBACK();
  primitive->P2->data->P1 = primitive;
  /* calling the secondary primitive UPDATE. */
  result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                        &(workspace->secondaryJob),
                                                         workspace->paPrimitive->P2
                                                       );

  workspace->smResult = result;

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle ----------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Update2Finish,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType);

  TS_PARAM_UNUSED(job);
  TS_PARAM_UNUSED(primitive);

  CRYPTO_XVIX_XAIX_SET_SMRESULT_UPDATE(workspace->smResult, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType));

  return E_OK;
}
#endif /*CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON*/

/* --- Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishProcess --------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType);

  Std_ReturnType           result        = E_NOT_OK;
  /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0001,1 */
  uint32                   hashResultLength   = workspace->hashLength;

  TS_PARAM_UNUSED(job);

  if (    (workspace->modulus[0U] * CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES  )
      >  *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr)
     )
  {
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0015,1 */

    result              = CRYPTO_E_SMALL_BUFFER;
    workspace->smResult = result;
  }
  else
  {
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0002,1 */
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       =   workspace->msgDigest;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &(hashResultLength);
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode            =   CRYPTO_OPERATIONMODE_FINISH;

    CRYPTO_XVIX_XAIX_RESET_CALLBACK();
    primitive->P2->data->P1 = primitive;
    /* calling the secondary primitive FISNIH. */
    result = primitive->P2->cnfg->description->fcnProcess(  workspace->paObjectId,
                                                          &(workspace->secondaryJob),
                                                            workspace->paPrimitive->P2
                                                         );

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0003,1 */
    workspace->smResult = result;
  }

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishProcess2StartIdle ---------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishProcess2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType);

  workspace->signature = &(((P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))
    (primitive->cnfg->heap))[(workspace->modulus[0U] * 2U) + 1U]);
  workspace->signature[0U] = workspace->modulusLen;

  /* Signature = EM^SecretExponent mod modulus */
  /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0013,1 */
  Crypto_xVIx_xAIx_LNModExp
  (
      workspace->signature,
      workspace->heapTmp1,
      workspace->modulus,
      workspace->priExp,
    &(workspace->lnCtx)
  );

  /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0014,1 */
  /* this function can not fail.
   * the signature length is already checked in function Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishProcess.
   */
  (void) Crypto_xVIx_xAIx_LNNumberToBEByteArray
           (
             workspace->signature,
             job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr,
             job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr
           );

  workspace->smResult = E_OK;
  CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH(workspace->smResult, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle --------------------------------------- */
/* Deviation CODEMETRIC-1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)

static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType);

  Std_ReturnType          result           = E_NOT_OK;

  /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0001,1 */
  uint32                  hashResultLength          = 0U;
  uint32                  DERHeaderMsgDigestLength  = 0U;
  uint32                  DERHeaderDigestInfoLength = 0U;
  uint32                  tLength                   = 0U;
  boolean                 fromPrimitive             = TRUE;

  uint32                  numberLength;
  uint32                  i;

  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyPtr = NULL_PTR;

  /* Get the secondary family hash algorithm length */
  workspace->hashLength = Crypto_xVIx_xAIx_GetHashLen(job->jobPrimitiveInfo->primitiveInfo->algorithm.secondaryFamily);

  /* CHECK: NOPARSE
   * In order to avoid the incorrect secondaryFamily configuration in Csm check is needed. This check is always true.
   */
  if(0U != workspace->hashLength)
  {
    hashResultLength = workspace->hashLength;

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/START/0001,1 */
    result = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet(  job->cryptoKeyId,
                                                         CRYPTO_KE_SIGNATURE_KEY,
                                                       &(keyPtr),
                                                         FALSE,
                                                         CRYPTO_XVIX_XAIX_SID_EMPTY
                                                       );
  }
  /* CHECK: PARSE */

  /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/START/0002,1 */
  if(E_OK == result)
  {
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/START/0003,1 */
    /* Deviation TASKING-1 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(result, keyPtr, fromPrimitive);
  }

  if (E_OK == result)
  {
    /* create secondary job */
    CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB();
    CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_KEY();

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/UPDATE/0001,1 */
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/UPDATE/0002,1 */
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        =  job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     =  job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       =  workspace->msgDigest;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &(hashResultLength);
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode            =  CRYPTO_OPERATIONMODE_SINGLECALL;

    primitive->P2->data->P1 = primitive;
    /* calling the secondary primitive. */
    result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                          &(workspace->secondaryJob),
                                                           workspace->paPrimitive->P2
                                                         );
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/START/0007,1 */
  }

  /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/START/0004,1 */
  if (E_OK == result)
  {
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/START/0005,1 */
    /* The version has 2 elements in LN representation format */
    /* Deviation MISRAC2012-1 <+19> */
    workspace->modulusLen = ((P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))keyPtr->data->data)[2U] + 1U;
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/START/0008,1 */
    if (workspace->modulusLen <= (keyPtr->data->size/CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES))
    {
      workspace->pubExpLen  =
          ((P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))keyPtr->data->data)[workspace->modulusLen + 2U] + 1U;
      if ((workspace->modulusLen + workspace->pubExpLen) <= (keyPtr->data->size/CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES))
      {
        workspace->priExpLen  =
            ((P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))keyPtr->data->data)[
                                                                                                              2U
                                                                                                            + workspace->modulusLen
                                                                                                            + workspace->pubExpLen
                                                                                                           ]
                                                                                        + 1U;
        workspace->modulus =
            &((P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))keyPtr->data->data)[2U];
        workspace->priExp  =
            &((P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))keyPtr->data->data)[2U + workspace->modulusLen + workspace->pubExpLen];

        if (    (workspace->modulus[0U] * CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES  )
             > *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr)
           )
        {
          /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0015,1 */

          result = CRYPTO_E_SMALL_BUFFER;
        }
      }
      else
      {
        result = E_NOT_OK;
      }
    }
    else
    {
      result = E_NOT_OK;
    }

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/START/0006,1 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(keyPtr);
  }

  /* Crypto_xVIx_xAIx_StateMachine_FinishProcess */
  if (E_OK == result)
  {
    if (     (NULL_PTR != primitive->cnfg->heap)
         && ((workspace->modulusLen * (2U + (2U * CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES))) < primitive->cnfg->heapSize)
       )
    {
      /* Reset heap */
      TS_MemBZero(primitive->cnfg->heap, primitive->cnfg->heapSize);
      workspace->heapTmp1 =
        (P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))(primitive->cnfg->heap);
      workspace->EM =  &(((P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))
        (primitive->cnfg->heap))[workspace->modulusLen * CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES]);

      workspace->heapTmp1[0U] = workspace->modulusLen * 2U;

      /* get the length of the user-provided modulus in byte (which is equal to the signature length) */
      numberLength = (workspace->modulus[0U] * CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES);

      /* set the hash algorithm id and hash length */
      Crypto_xVIx_xAIx_Procedure_SetAlgorithmId(job, workspace);

      /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0004,1 */
      DERHeaderMsgDigestLength = Crypto_xVIx_xAIx_CommonDerHeaderOctetString
                                (
                                  workspace->DERHeaderMsgDigestBuffer,
                                  workspace->hashLength
                                );

      DERHeaderDigestInfoLength = Crypto_xVIx_xAIx_CommonDerHeaderSequence
                                  (
                                      workspace->DERHeaderDigestInfoBuffer,
                                      workspace->hashLength
                                    + DERHeaderMsgDigestLength
                                    + workspace->algorithmIdLength
                                  );

      /* calculate the length of the T field */
      tLength =   workspace->hashLength
                + workspace->algorithmIdLength
                + DERHeaderMsgDigestLength
                + DERHeaderDigestInfoLength;

      /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0006,1 */
      if (   (numberLength > (tLength + (uint32)CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_EM_STATIC_FIELDS_LEN))
          && (workspace->algorithmId != NULL_PTR)
        )
      {
        /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0007,1 */

        /* set the first two bytes */
        /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0008,1 */
        workspace->EM[0U] = (uint8)0x00U;
        workspace->EM[1U] = (uint8)0x01U;

        /* generate the PS field */
        /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0009,1 */
        for (i = 2U; i < (numberLength - tLength - 1U); i++)
        {
          workspace->EM[i] = (uint8)0xFFU;
        }

        /* add the zero byte after the PS field */
        /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0010,1 */
        workspace->EM[i] = (uint8)0x00U;
        i++;

        /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0011,1 */
        TS_MemCpy
        (
          &(workspace->EM[i]),
            workspace->DERHeaderDigestInfoBuffer,
            DERHeaderDigestInfoLength
        );
        i += DERHeaderDigestInfoLength;

        TS_MemCpy
        (
          &(workspace->EM[i]),
            workspace->algorithmId,
            workspace->algorithmIdLength
        );
        i += workspace->algorithmIdLength;

        TS_MemCpy
        (
          &(workspace->EM[i]),
            workspace->DERHeaderMsgDigestBuffer,
            DERHeaderMsgDigestLength
        );
        i += DERHeaderMsgDigestLength;

        TS_MemCpy
        (
          &(workspace->EM[i]),
            workspace->msgDigest,
            workspace->hashLength
        );

        /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0012,1 */
        /* call can not fail because enough space has been allocated to the buffers in context
        * and valid lengths are set.
        */
        (void) Crypto_xVIx_xAIx_LNBEByteArrayToNumber
        (
          workspace->EM,
          numberLength,
          workspace->heapTmp1,
          workspace->heapTmp1[0U]
        );
      }
      else
      {
        result = E_NOT_OK;
      }
    }
    else
    {
      /* heap not available or insufficient */
      /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/GENERAL/0013,1 */
      result = E_NOT_OK;
    }
  }

  /* Crypto_xVIx_xAIx_StateMachine_FinishProcess2StartIdle */
  if (E_OK == result)
  {
    workspace->signature = &(((P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))
      (primitive->cnfg->heap))[(workspace->modulus[0U] * 2U) + 1U]);
    workspace->signature[0U] = workspace->modulusLen;

    /* Signature = EM^SecretExponent mod modulus */
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0013,1 */
    Crypto_xVIx_xAIx_LNModExp
    (
        workspace->signature,
        workspace->heapTmp1,
        workspace->modulus,
        workspace->priExp,
      &(workspace->lnCtx)
    );

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0014,1 */
    /* this function can not fail.
     * the signature length is already checked.
     */
    (void) Crypto_xVIx_xAIx_LNNumberToBEByteArray
                (
                  workspace->signature,
                  job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr,
                  job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr
                );
  }
  CRYPTO_XVIX_XAIX_SET_SMRESULT_SINGLECALL(result, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle ------------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveCancel2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType);
  if (NULL_PTR != workspace->secondaryJob.jobInfo)
  {
    /* CHECK: NOPARSE
     * In order to cancel the secondaryjob the job has to be running so this check is always true.
     */
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
    /* CHECK: PARSE */

  }

  /* !LINKSTO Crypto.Asr.SWS_Crypto_00183,2 */
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00144,1 */
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00181_1,1 */
  CRYPTO_XVIX_XAIX_SET_SMRESULT_CANCEL(CRYPTO_E_JOB_CANCELED, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_StartExec ----------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType);

  Std_ReturnType result         = E_NOT_OK;
  boolean        fromPrimitive  = TRUE;

  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyPtr = NULL_PTR;

  /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/START/0001,1 */
  /* key element is read in the secondary primitive */
  result = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet(  job->cryptoKeyId,
                                                       CRYPTO_KE_SIGNATURE_KEY,
                                                     &(keyPtr),
                                                       FALSE,
                                                       CRYPTO_XVIX_XAIX_SID_EMPTY
                                                    );

  /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/START/0002,1 */
  if(E_OK == result)
  {
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/START/0003,1 */
    /* Deviation TASKING-1 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(result, keyPtr, fromPrimitive);
  }

  /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/START/0004,1 */
  if (E_OK == result)
  {
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/START/0005,1 */
    /* The version has 2 elements in LN representation format */
    /* Deviation MISRAC2012-1 <+19> */
    workspace->modulusLen = ((P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))keyPtr->data->data)[2U] + 1U;
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/START/0008,1 */
    if (workspace->modulusLen <= (keyPtr->data->size/CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES))
    {
      workspace->pubExpLen  =
          ((P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))keyPtr->data->data)[workspace->modulusLen + 2U] + 1U;
      if ((workspace->modulusLen + workspace->pubExpLen) <= (keyPtr->data->size/CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES))
      {
        workspace->priExpLen  =
            ((P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))keyPtr->data->data)[
                                                                                                              2U
                                                                                                            + workspace->modulusLen
                                                                                                            + workspace->pubExpLen
                                                                                                           ]
                                                                                        + 1U;
        workspace->modulus =
            &((P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))keyPtr->data->data)[2U];
        workspace->priExp  =
            &((P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))keyPtr->data->data)[2U + workspace->modulusLen + workspace->pubExpLen];
      }
      else
      {
        result = E_NOT_OK;
      }
    }
    else
    {
      result = E_NOT_OK;
    }

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/START/0006,1 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(keyPtr);
  }

  if (E_OK != result)
  {
    /* Deviation TASKING-2 */
    CRYPTO_XVIX_XAIX_SET_SMRESULT_START(result, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType));
  }

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishProcess ------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType);
  Std_ReturnType result                    = E_NOT_OK;
  uint32         DERHeaderMsgDigestLength  = 0U;
  uint32         DERHeaderDigestInfoLength = 0U;
  uint32         tLength                   = 0U;
  uint32         numberLength;
  uint32         i;

  workspace->heapTmp1 =
    (P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))(primitive->cnfg->heap);
  workspace->EM = &(((P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))
    (primitive->cnfg->heap))[workspace->modulusLen * CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES]);

  workspace->heapTmp1[0U] = workspace->modulusLen * 2U;

  /* get the length of the user-provided modulus in byte (which is equal to the signature length) */
  numberLength = (workspace->modulus[0U] * CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES);

  /* set the hash algorithm id and hash length */
  Crypto_xVIx_xAIx_Procedure_SetAlgorithmId(job, workspace);

  /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0004,1 */
  DERHeaderMsgDigestLength = Crypto_xVIx_xAIx_CommonDerHeaderOctetString
                             (
                               workspace->DERHeaderMsgDigestBuffer,
                               workspace->hashLength
                             );

  DERHeaderDigestInfoLength = Crypto_xVIx_xAIx_CommonDerHeaderSequence
                              (
                                  workspace->DERHeaderDigestInfoBuffer,
                                  workspace->hashLength
                                + DERHeaderMsgDigestLength
                                + workspace->algorithmIdLength
                              );

  /* calculate the length of the T field */
  tLength =   workspace->hashLength
            + workspace->algorithmIdLength
            + DERHeaderMsgDigestLength
            + DERHeaderDigestInfoLength;

  /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0006,1 */
  if (   (numberLength > (tLength + (uint32)CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_EM_STATIC_FIELDS_LEN))
      && (workspace->algorithmId != NULL_PTR)
     )
  {
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0007,1 */

    /* set the first two bytes */
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0008,1 */
    workspace->EM[0U] = (uint8)0x00U;
    workspace->EM[1U] = (uint8)0x01U;

    /* generate the PS field */
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0009,1 */
    for (i = 2U; i < (numberLength - tLength - 1U); i++)
    {
      workspace->EM[i] = (uint8)0xFFU;
    }

    /* add the zero byte after the PS field */
    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0010,1 */
    workspace->EM[i] = (uint8)0x00U;
    i++;

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0011,1 */
    TS_MemCpy
    (
      &(workspace->EM[i]),
        workspace->DERHeaderDigestInfoBuffer,
        DERHeaderDigestInfoLength
    );
    i += DERHeaderDigestInfoLength;

    TS_MemCpy
    (
      &(workspace->EM[i]),
        workspace->algorithmId,
        workspace->algorithmIdLength
    );
    i += workspace->algorithmIdLength;

    TS_MemCpy
    (
      &(workspace->EM[i]),
        workspace->DERHeaderMsgDigestBuffer,
        DERHeaderMsgDigestLength
    );
    i += DERHeaderMsgDigestLength;

    TS_MemCpy
    (
      &(workspace->EM[i]),
        workspace->msgDigest,
        workspace->hashLength
    );

    /* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/FINISH/0012,1 */
    /* call can not fail because enough space has been allocated to the buffers in context
     * and valid lengths are set.
     */
    (void) Crypto_xVIx_xAIx_LNBEByteArrayToNumber
    (
       workspace->EM,
       numberLength,
       workspace->heapTmp1,
       workspace->heapTmp1[0U]
    );

    result = E_OK;
  }
  else
  {
    result = E_NOT_OK;
    /* Deviation TASKING-2 */
    CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH(result, sizeof(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType));
  }
  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

/* ---misc procedures---------------------------------------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_SetAlgorithmId
(
  P2VAR(Crypto_JobType,                        AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2VAR(Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace
)
{
  switch (job->jobPrimitiveInfo->primitiveInfo->algorithm.secondaryFamily)
  {
#if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA1_NOTSET  )
#if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA1_NOTSET == STD_ON)
    case CRYPTO_ALGOFAM_SHA1:
    {
      workspace->algorithmId       = &Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HashAlgorithmId[0U][0U];
      workspace->algorithmIdLength =  CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA1_ID_LENGTH;
    }
    break;
#endif /* #if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA1_NOTSET  )*/
#endif /* #if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA1_NOTSET == STD_ON) */

#if    (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2224_NOTSET  )
#if    (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2224_NOTSET == STD_ON)
    case CRYPTO_ALGOFAM_SHA2_224:
    {
      workspace->algorithmId       = &Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HashAlgorithmId[1U][0U];
      workspace->algorithmIdLength =  CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2224_ID_LENGTH;
    }
    break;
#endif /* #if    (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2224_NOTSET  ) */
#endif /* #if    (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2224_NOTSET == STD_ON) */

#if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2256_NOTSET  )
#if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2256_NOTSET == STD_ON)
    case CRYPTO_ALGOFAM_SHA2_256:
    {
      workspace->algorithmId       = &Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HashAlgorithmId[2U][0U];
      workspace->algorithmIdLength =  CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2256_ID_LENGTH;
    }
    break;
#endif /* #if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2256_NOTSET  ) */
#endif /* #if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2256_NOTSET == STD_ON) */

#if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2384_NOTSET  )
#if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2384_NOTSET == STD_ON)
    case CRYPTO_ALGOFAM_SHA2_384:
    {
      workspace->algorithmId       = &Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HashAlgorithmId[3U][0U];
      workspace->algorithmIdLength =  CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2384_ID_LENGTH;
    }
    break;
#endif /* #if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2384_NOTSET  ) */
#endif /* #if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2384_NOTSET == STD_ON) */

#if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2512_NOTSET  )
#if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2512_NOTSET == STD_ON)
    case CRYPTO_ALGOFAM_SHA2_512:
    {
      workspace->algorithmId       = &Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HashAlgorithmId[4U][0U];
      workspace->algorithmIdLength =  CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2512_ID_LENGTH;
    }
    break;
#endif /* #if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2512_NOTSET  ) */
#endif /* #if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2512_NOTSET == STD_ON) */

#if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3224_NOTSET  )
#if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3224_NOTSET == STD_ON)
    case CRYPTO_ALGOFAM_SHA3_224:
    {
      workspace->algorithmId       = &Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HashAlgorithmId[5U][0U];
      workspace->algorithmIdLength =  CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3224_ID_LENGTH;
    }
    break;
#endif /* #if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3224_NOTSET  ) */
#endif /* #if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3224_NOTSET == STD_ON) */

#if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3256_NOTSET  )
#if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3256_NOTSET == STD_ON)
    case CRYPTO_ALGOFAM_SHA3_256:
    {
      workspace->algorithmId       = &Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HashAlgorithmId[6U][0U];
      workspace->algorithmIdLength =  CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3256_ID_LENGTH;
    }
    break;
#endif /* #if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3256_NOTSET  ) */
#endif /* #if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3256_NOTSET == STD_ON) */

#if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3384_NOTSET  )
#if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3384_NOTSET == STD_ON)
    case CRYPTO_ALGOFAM_SHA3_384:
    {
      workspace->algorithmId       = &Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HashAlgorithmId[7U][0U];
      workspace->algorithmIdLength =  CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3384_ID_LENGTH;
    }
    break;
#endif /* #if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3384_NOTSET  ) */
#endif /* #if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3384_NOTSET == STD_ON) */

#if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3512_NOTSET  )
#if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3512_NOTSET == STD_ON)
    case CRYPTO_ALGOFAM_SHA3_512:
    {
      workspace->algorithmId       = &Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HashAlgorithmId[8U][0U];
      workspace->algorithmIdLength =  CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3512_ID_LENGTH;
    }
    break;
#endif /* #if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3512_NOTSET  ) */
#endif /* #if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3512_NOTSET == STD_ON) */

    /* CHECK: NOPARSE */
    /* All the possible secondary family algorithms have been addressed in the cases above.*/
    default:
    {
      /* Nothing to do (MISRA) */
    }
    break;
    /* CHECK: PARSE */
  }
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[end of file]=================================================================*/

