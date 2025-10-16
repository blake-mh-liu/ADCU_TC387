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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_DECRYPT_RSA_RSAESOAEP.c/0001,1 */

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
 * For DECRYPT_RSA_RSAESOAEP the key is needed in long number representation format.
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
 * CODEMETRIC-1 Deviated Rule: HIS_STMT
 * not 95 <= 75
 *
 * CODEMETRIC-2) Deviated Rule: HIS_STMT
 * not 97 <= 75
 *
 * Reason:
 * SingleCall functions are adjusted for performance and have a reduced amount of function calls
 * on purpose which leads to metric violations.
 *
 * CODEMETRIC-3) Deviated Rule: HIS_PATH
 * not 82944 <= 2000
 *
 * Reason:
 * SingleCall functions are adjusted for performance and have a reduced amount of function calls
 * on purpose which leads to metric violations.
 *
 * CODEMETRIC-4) Deviated Rule: HIS_V(G)
 * not 27 <= 20
 *
 * Reason:
 * SingleCall functions are adjusted for performance and have a reduced amount of function calls
 * on purpose which leads to metric violations.
 *
, * CODEMETRIC-1) Deviated Rule: HIS_STMT
 * not 127 <= 75
 *
 * CODEMETRIC-2) Deviated Rule: HIS_STMT
 * not 131 <= 75
 *
 * Reason:
 * SingleCall functions are adjusted for performance and have a reduced amount of function calls
 * on purpose which leads to metric violations.
 *
 * CODEMETRIC-3) Deviated Rule: HIS_PATH
 * not 93312 <= 2000
 *
 * Reason:
 * SingleCall functions are adjusted for performance and have a reduced amount of function calls
 * on purpose which leads to metric violations.
 *
 * CODEMETRIC-4) Deviated Rule: HIS_V(G)
 * not 30 <= 20
 *
 * Reason:
 * SingleCall functions are adjusted for performance and have a reduced amount of function calls
 * on purpose which leads to metric violations.
 *
 ) */

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int.h>                                /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_DECRYPT_RSA_RSAESOAEP.c/0002,1 */
#include <Crypto_xVIx_xAIx_Int_KeyManagement.h>                  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_DECRYPT_RSA_RSAESOAEP.c/0003,1 */
#include <Crypto_xVIx_xAIx_Int_CPr_DECRYPT_RSA_RSAESOAEP.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_DECRYPT_RSA_RSAESOAEP.c/0004,1 */

/*==================[macros]======================================================================*/

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT,1 */
#if (defined CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT)
#error CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT already defined
#endif
/** \brief  Number of entries in the primitives state transition table. **/
#define CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT     0x12U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT,1 */
#if (defined CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT)
#error CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT already defined
#endif
/** \brief  Number of entries in the primitives state action table. **/
#define CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT         0x0CU

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_STARTIDLE,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_STARTIDLE)
#error CRYPTO_XVIX_XAIX_STATE_STARTIDLE already defined
#endif
/** \brief  The StartIdle state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_STARTIDLE                0x00U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_STARTEXEC,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_STARTEXEC)
#error CRYPTO_XVIX_XAIX_STATE_STARTEXEC already defined
#endif
/** \brief  The StartExec state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_STARTEXEC                0x01U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE)
#error CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE already defined
#endif
/** \brief  The UpdateIdle state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE               0x02U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC)
#error CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC already defined
#endif
/** \brief  The UpdateExec state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC               0x03U

#if (defined CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESSFIRSTMASK)
#error CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESSFIRSTMASK already defined
#endif
/** \brief  The UpdateProcessFirstMark state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESSFIRSTMASK   0x04U

#if (defined CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESSSECONDMASK)
#error CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESSSECONDMASK already defined
#endif
/** \brief  The UpdateProcessSecondMask state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESSSECONDMASK  0x05U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE)
#error CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE already defined
#endif
/** \brief  The UpdateFinishIdle state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE         0x06U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_FINISHEXEC,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHEXEC)
#error CRYPTO_XVIX_XAIX_STATE_FINISHEXEC already defined
#endif
/** \brief  The FinishExec state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHEXEC               0x07U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS)
#error CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS already defined
#endif
/** \brief  The FinishProcess state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS            0x08U

#if (defined CRYPTO_XVIX_XAIX_STATE_SINGLECALL)
#error CRYPTO_XVIX_XAIX_STATE_SINGLECALL already defined
#endif
/** \brief  The SingleCall state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_SINGLECALL               0x09U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_CANCEL,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_CANCEL)
#error CRYPTO_XVIX_XAIX_STATE_CANCEL already defined
#endif
/** \brief  The Cancel state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_CANCEL                   0x0AU

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_ERROR,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_ERROR)
#error CRYPTO_XVIX_XAIX_STATE_ERROR already defined
#endif
/** \brief  The Error state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_ERROR                    0x0BU

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)
static FUNC(boolean, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetNextState
(
  P2VAR(uint8,                                         AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) smStateIndx,
        Crypto_xVIx_xAIx_PrimitiveStateIdentifierType                                         curState,
        Std_ReturnType                                                                        resultAction,
        Crypto_ProcessingType                                                                 jobProcessing,
  P2VAR(Crypto_xVIx_xAIx_PrimitiveStateIdentifierType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) nxtState
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */
/** \brief  State transition function
 **           from state 'CRYPTO_XVIX_XAIX_STATE_STARTEXEC'
 **           to state   'CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE'
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK      request successful
 ** \retval   E_NOT_OK  request failed
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

/** \brief  State transition function
 **           from state 'CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC'
 **           to state   'CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESSFIRSTMASK'
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK      request successful
 ** \retval   E_NOT_OK  request failed
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcessFirstMask
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

/** \brief  State transition function
 **           from state 'CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESSFIRSTMASK'
 **           to state   'CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESSSECONDMASK'
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK      request successful
 ** \retval   E_NOT_OK  request failed
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcessFirstMask2UpdateProcessSecondMask
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

/** \brief  State transition function
 **           from state 'CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESSSECONDMASK'
 **           to state   'CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE'
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK      request successful
 ** \retval   E_NOT_OK  request failed
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcessSecondMask2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

/** \brief  State transition function
 **           from state 'CRYPTO_XVIX_XAIX_STATE_FINISHEXEC'
 **           to state   'CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS'
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK      request successful
 ** \retval   E_NOT_OK  request failed
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

/** \brief  State transition function
 **           from state 'CRYPTO_XVIX_XAIX_STATE_CANCEL'
 **           to state   'CRYPTO_XVIX_XAIX_STATE_STARTIDLE'
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK      request successful
 ** \retval   E_NOT_OK  request failed
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

/** \brief  State transition function
 **           from state 'CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS'
 **           to state   'CRYPTO_XVIX_XAIX_STATE_STARTIDLE'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK      request successful
 ** \retval   E_NOT_OK  request failed
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishProcess2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

/** \brief  State action function for states
 **           'CRYPTO_XVIX_XAIX_STATE_STARTEXEC'
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK      request successful
 ** \retval   E_NOT_OK  request failed
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

/** \brief  State action function for states
 **               'CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESSFIRSTMASK'
 **           and 'CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESSSECONDMASK'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval   E_OK      request successful
 ** \retval   E_NOT_OK  request failed
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Mgf
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal constants]==========================================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  The primitives state transition table. **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_StateTransitionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateTransitionType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Process_StateTransitionTable[CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT] =
{
  { NULL_PTR,                                                                     CRYPTO_XVIX_XAIX_STATE_STARTIDLE,               CRYPTO_XVIX_XAIX_STATE_STARTIDLE,               CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle,                           CRYPTO_XVIX_XAIX_STATE_STARTEXEC,               CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,              CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { Crypto_xVIx_xAIx_StateMachine_Error2StartIdle,                                CRYPTO_XVIX_XAIX_STATE_STARTEXEC,               CRYPTO_XVIX_XAIX_STATE_STARTIDLE,               CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_NOT_OK      },

  { NULL_PTR,                                                                     CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,              CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,              CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcessFirstMask,              CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC,              CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESSFIRSTMASK,  CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { NULL_PTR,                                                                     CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESSFIRSTMASK,  CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESSFIRSTMASK,  CRYPTO_XVIX_XAIX_PROCESSING_BOTH, CRYPTO_E_BUSY },
  { Crypto_xVIx_xAIx_StateMachine_UpdateProcessFirstMask2UpdateProcessSecondMask, CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESSFIRSTMASK,  CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESSSECONDMASK, CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { NULL_PTR,                                                                     CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESSSECONDMASK, CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESSSECONDMASK, CRYPTO_XVIX_XAIX_PROCESSING_BOTH, CRYPTO_E_BUSY },
  { Crypto_xVIx_xAIx_StateMachine_UpdateProcessSecondMask2UpdateFinishIdle,       CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESSSECONDMASK, CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,        CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { Crypto_xVIx_xAIx_StateMachine_Error2StartIdle,                                CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC,              CRYPTO_XVIX_XAIX_STATE_STARTIDLE,               CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_NOT_OK      },
  { Crypto_xVIx_xAIx_StateMachine_Error2StartIdle,                                CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESSFIRSTMASK,  CRYPTO_XVIX_XAIX_STATE_STARTIDLE,               CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_NOT_OK      },
  { Crypto_xVIx_xAIx_StateMachine_Error2StartIdle,                                CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESSSECONDMASK, CRYPTO_XVIX_XAIX_STATE_STARTIDLE,               CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_NOT_OK      },

  { NULL_PTR,                                                                     CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,        CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,        CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishProcess,                       CRYPTO_XVIX_XAIX_STATE_FINISHEXEC,              CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS,           CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { Crypto_xVIx_xAIx_StateMachine_FinishProcess2StartIdle,                        CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS,           CRYPTO_XVIX_XAIX_STATE_STARTIDLE,               CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle,                           CRYPTO_XVIX_XAIX_STATE_SINGLECALL,              CRYPTO_XVIX_XAIX_STATE_STARTIDLE,               CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle,                               CRYPTO_XVIX_XAIX_STATE_CANCEL,                  CRYPTO_XVIX_XAIX_STATE_STARTIDLE,               CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { Crypto_xVIx_xAIx_StateMachine_Error2StartIdle,                                CRYPTO_XVIX_XAIX_STATE_ERROR,                   CRYPTO_XVIX_XAIX_STATE_STARTIDLE,               CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

/** \brief  The primitives state action table. **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_StateActionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateActionType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Process_StateActionTable[CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT] =
{
  /* CRYPTO_XVIX_XAIX_STATE_STARTIDLE               */ { NULL_PTR                                   }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1        */
  /* CRYPTO_XVIX_XAIX_STATE_STARTEXEC               */ { Crypto_xVIx_xAIx_StateMachine_StartProcess }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTEXEC/0001,1 */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE              */ { NULL_PTR                                   }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC              */ { NULL_PTR                                   }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESSFIRSTMASK  */ { Crypto_xVIx_xAIx_StateMachine_Mgf          },
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESSSECONDMASK */ { Crypto_xVIx_xAIx_StateMachine_Mgf          },
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE        */ { NULL_PTR                                   }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE/0001,1 */
  /* CRYPTO_XVIX_XAIX_STATE_FINISHEXEC              */ { NULL_PTR                                   }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_FINISHEXEC/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS           */ { NULL_PTR                                   },
  /* CRYPTO_XVIX_XAIX_STATE_SINGLECALL              */ { Crypto_xVIx_xAIx_StateMachine_StartProcess },
  /* CRYPTO_XVIX_XAIX_STATE_CANCEL                  */ { NULL_PTR                                   },
  /* CRYPTO_XVIX_XAIX_STATE_ERROR                   */ { NULL_PTR                                   },
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Process -----------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Process/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Process
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_WorkspaceType);

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
    (void) Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Reset(workspace->paObjectId, job, primitive);
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
        (void) Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Main(objectId, job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Main --------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Main/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Main
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_WorkspaceType);

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
    if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Process_StateActionTable[curState].fcnAction))
    {
      resultAction = Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Process_StateActionTable[curState].fcnAction(job, primitive);
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
    /* CHECK: NOPARSE
     * The return value of GetNextState cannot be FALSE for DECRYPT_RSA_RSAESOAEP, because the state machine
     * transition table for this cryptographic primitive is complete.
     */
    if (TRUE == nxtStateFound)
    /* CHECK: PARSE */
    {
      workspace->smStateIndx = smStateIndx;
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0010,1 */
      if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Process_StateTransitionTable[smStateIndx].fcnTransition))
      {
        /* transition function returns using workspace->smResult */
        (void) Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Process_StateTransitionTable[smStateIndx].fcnTransition(job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Cancel ------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Cancel/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Cancel
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_WorkspaceType);

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
      (void) Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Main(objectId, job, primitive);
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Reset -------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Reset/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Reset
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as
   * secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESET(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_WorkspaceType));
    result = E_OK;
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Restart -------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Restart/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Restart
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESTART(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_WorkspaceType));
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Callback ----------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Callback/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)
/* CHECK: NOPARSE
 * This API is only reachable for cryptographic primitives that are using a secondary primitive.
 */
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_WorkspaceType);

  TS_PARAM_UNUSED(objectId);
  TS_PARAM_UNUSED(job);
  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Callback/0002,1 */
  workspace->notifyType   = cbkType;
  workspace->notifyResult = cbkResult;

  return E_OK;
}
/* CHECK: PARSE */
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_StateMachine_Error2StartIdle ----------------------------------------------*/

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveError2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_WorkspaceType);

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
  result              = Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Reset(workspace->paObjectId, job, primitive);
  workspace->smResult = smResult;

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

/*--- Crypto_xVIx_xAIx_GetNextState --------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)
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
   * The FOR loop condition can not fail for DECRYPT_RSA_RSAESOAEP, because the state transition table of this
   * cryptographic primitive is straight.
   */
  /* 1) iterate from last found entry in table to last table entry */
  for (i = *smStateIndx; i < CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT; i++)
  /* CHECK: PARSE */
  {
    if (   (Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx   = i;
      break;
    }
  }

  /* CHECK: NOPARSE
   * The FOR loop condition (FALSE == nxtStateFound) is always FALSE for DECRYPT_RSA_RSAESOAEP, because the state
   * transition table of this cryptographic primitive is straight and that is why the previous
   * FOR loop always already finds a next state.
   */
  /* 2) iterate from first table entry to last found entry in table */
  for (i = 0U; (FALSE == nxtStateFound) && (i < *smStateIndx); i++)
  {
    if (   (Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx  = i;
      break;
    }
  }
  /* CHECK: PARSE */

  return nxtStateFound;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */
/* --- Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle --------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)

static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  Std_ReturnType result = E_NOT_OK;

  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_WorkspaceType);

  /* setup secondary job */
  CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB();
  CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_KEY();
  CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_SRV();

  primitive->P2->data->P1 = primitive;

  result = E_OK;
  /* Deviation TASKING-1 */
  CRYPTO_XVIX_XAIX_SET_SMRESULT_START(result, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_WorkspaceType));
  return result;
}

#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcessFirstMask -------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)

static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcessFirstMask
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_WorkspaceType);

  Std_ReturnType  result = E_NOT_OK;

  Crypto_xVIx_xAIx_LNWordType TmpLnWord[2U] = {1U, 1U};
  uint32                      NumberLength  = workspace->NLength;

  /* 2. a) len(C) != nlLen => error */
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0032, 1 */
  if (job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength == workspace->NLength)
  {
    /* 2. b) c = BS2I(C) */
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0033, 1 */
    result = Crypto_xVIx_xAIx_LNBEByteArrayToNumber(
               job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr,
               job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength,
               workspace->Tmp1Value,
               (Crypto_xVIx_xAIx_LNWordType)(sizeof(workspace->Tmp1Value) / sizeof(workspace->Tmp1Value[0U]))
             );
  }

  /* 2. c) 1 < c < n - 1 */
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0034, 1 */
  if (E_OK == result)
  {
    /* CHECK: NOPARSE
     * Test input leading to c<=1 is not trivial and would require a huge effort, thus this path cannot
     * be reached with tests.
     */
    if (
         CRYPTO_XVIX_XAIX_LN_E_LARGER != Crypto_xVIx_xAIx_LNCompareNumbers(
                                                                            workspace->Tmp1Value, /* c */
                                                                            TmpLnWord /* 1 */
                                                                          )
       )
    {
      /* c <= 1 */
      result = E_NOT_OK;
    }
    /* CHECK: PARSE */
  }

  if (E_OK == result)
  {
    Crypto_xVIx_xAIx_LNSubtraction(
                                    workspace->modulus,
                                    workspace->modulus,
                                    TmpLnWord
                                  );

    if (
         CRYPTO_XVIX_XAIX_LN_E_SMALLER != Crypto_xVIx_xAIx_LNCompareNumbers(
                                                                             workspace->Tmp1Value, /* c */
                                                                             workspace->modulus /* n - 1 */
                                                                           )
       )
    {
      /* c >= n - 1 */
      result = E_NOT_OK;
    }
    else
    {
      /* Return value (carry) can be discarded as we just add the previous subtracted 1 again */
      (void) Crypto_xVIx_xAIx_LNAddition(
                                          workspace->modulus,
                                          workspace->modulus,
                                          TmpLnWord
                                        );
    }
  }

  /* 3. RSA decryption */
  /* 3. a) em = RSADP((n,d),c) */
  if (E_OK == result)
  {
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0035, 1 */
    Crypto_xVIx_xAIx_LNModExp(
                               workspace->Tmp2Value, /* em */
                               workspace->Tmp1Value, /* c */
                               workspace->modulus, /* n */
                               workspace->priExp, /* d */
                               &workspace->lnCtx
                             );

    /* 3. b) EM = I2BS(em,nLen) */
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0036, 1 */
    result = Crypto_xVIx_xAIx_LNNumberToBEByteArray(
                                                     workspace->Tmp2Value,
                                                     workspace->EM,
                                                     &NumberLength
                                                   );
    workspace->EMLength = NumberLength;
  }

  /* 4. OAEP decoding */
  /* 4. a) HA = H(A) */
  /* Next state will start the hash */
  if (E_OK == result)
  {
    workspace->HashResultLength = workspace->HashLength;

    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        = workspace->AdditionalInput;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     = workspace->AdditionalInputLength;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       = workspace->HashResult;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &workspace->HashResultLength;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode            = CRYPTO_OPERATIONMODE_SINGLECALL;

    CRYPTO_XVIX_XAIX_RESET_CALLBACK();
    primitive->P2->data->P1 = primitive;
    result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                          &(workspace->secondaryJob),
                                                           workspace->paPrimitive->P2
                                                         );
  }

  if (E_OK == result)
  {
    /* 4. b) EM = Y || maskedMgfSeed' || maskedDB' */
    /* 4. c) mgfSeedMask' = MGF(maskedDB', HLen) */
    workspace->DbLength = workspace->NLength - workspace->HashLength - 1U;

    /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0040, 1 */
    workspace->Mgf1Ctx.Cnt = 0U;
    workspace->Mgf1Ctx.Itr = 1U;
    workspace->Mgf1Ctx.MaskOutputPtr    = &workspace->MgfSeedMask[0U];
    workspace->Mgf1Ctx.MaskOutputLength = workspace->HashLength;
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0039, 1 */
    workspace->Mgf1Ctx.MaskInputPtr     = &workspace->EM[1U + workspace->HashLength];
    workspace->Mgf1Ctx.MaskInputLength  = workspace->DbLength;
  }

  workspace->smResult = result;
  return result;
}

#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateProcessFirstMask2UpdateProcessSecondMask ------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)

static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcessFirstMask2UpdateProcessSecondMask
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_WorkspaceType);

  TS_PARAM_UNUSED(job);

  /* 4. */
  /* 4. d) mgfSeed' = maskedMGFSeed' XOR mgfSeedMask' */
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0041, 1 */
  Crypto_xVIx_xAIx_CommonXOR(
                              workspace->MgfSeedMask, /* mgfSeedMask' */
                              /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0038, 1 */
                              &workspace->EM[1U], /* maskedMGFSeed'*/
                              workspace->HashLength
                            );

  /* 4. e) dbMask' = MGF(mgfSeed', nlen-HLen-1) */
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0042, 1 */
  workspace->Mgf1Ctx.Cnt = 0U;
  workspace->Mgf1Ctx.Itr = ((workspace->DbLength + workspace->HashLength) - 1U) / workspace->HashLength;
  workspace->Mgf1Ctx.MaskOutputPtr = &workspace->DbMask[0U];
  workspace->Mgf1Ctx.MaskOutputLength = workspace->DbLength;
  workspace->Mgf1Ctx.MaskInputPtr = &workspace->MgfSeedMask[0U]; /* mgfSeed' */
  workspace->Mgf1Ctx.MaskInputLength = workspace->HashLength;

  return E_OK;
}

#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateProcessSecondMask2UpdateFinishIdle ------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)

static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcessSecondMask2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_WorkspaceType);

  Std_ReturnType              result        = E_NOT_OK;

  /* 4. f) DB' = maskedDB' XOR dbMask' */
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0043, 1 */
  Crypto_xVIx_xAIx_CommonXOR(
                              workspace->DbMask, /* dbMask' */
                              /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0039, 1 */
                              &workspace->EM[1U + workspace->HashLength],
                              workspace->DbLength
                            );

  result = E_OK;

  /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0006, 1 */
  *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr) = 0U;

  workspace->smResult = result;
  CRYPTO_XVIX_XAIX_SET_SMRESULT_UPDATE(workspace->smResult, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_WorkspaceType));

  return result;
}

#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishProcess ----------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)

static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;
  uint32 i;
  uint32 Index = 0U;
  boolean SeparatorFound = FALSE;
  boolean DecryptErrorFlag = FALSE;

  /* 4. g) DB' = HA' || X */
  /* 5. check for decryption errors, do not abort - set DecryptErrorFlag */
  /* 5. a) check Y == 0x00 */
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0037, 1 */
  if (workspace->EM[0U] != 0x00U)
  {
    /* Invalid Y */
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0047, 1 */
    DecryptErrorFlag = TRUE;
  }

  /* 5. b) check HA' == HA */
  if (E_NOT_OK == Crypto_xVIx_xAIx_MemCmpSec(
                                              /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0045, 1 */
                                              workspace->DbMask,
                                              workspace->HashResult,
                                              workspace->HashLength
                                            )
     )
  {
    /* Invalid HA' */
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0048, 1 */
    DecryptErrorFlag = TRUE;
  }

  /* 5. c) check format of X, should be PS||0x01||K */
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0049, 1 */
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0045, 1 */
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0046, 1 */
  for (i = workspace->HashLength; (i < workspace->DbLength); i++)
  {
    /* PS can be 0 or more 0x00 bytes */
    if ((SeparatorFound == FALSE) &&(workspace->DbMask[i] > 0x01U))
    {
      /* Invalid X */
      DecryptErrorFlag = TRUE;
    }
    else
    {
      if ((SeparatorFound == FALSE) && (workspace->DbMask[i] == 0x01U))
      {
        SeparatorFound = TRUE;
        Index = i + 1U;
      }
    }
  }

  if ((SeparatorFound == FALSE) || (Index == workspace->DbLength))
  {
    /* No Separator or K found */
    DecryptErrorFlag = TRUE;
  }

  /* 6. output */
  /* 6. a) only output if no error was detected */
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0050, 1 */
  if (DecryptErrorFlag == FALSE)
  {
    if (*job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr >= (workspace->DbLength - Index))
    {
      /* 6. b) output K */
      /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0051, 1 */
      TS_MemCpy(
                 job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr,
                 &workspace->DbMask[Index],
                 workspace->DbLength - Index
               );
      *job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = workspace->DbLength - Index;
      result = E_OK;
    }
    else
    {
      /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0005, 1 */
      result = CRYPTO_E_SMALL_BUFFER;
      workspace->smResult = result;
    }
  }
  else
  {
    result = E_NOT_OK;
    workspace->smResult = result;
  }

  return result;
}

#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishProcess2StartIdle ------------------------------------ */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)

static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishProcess2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_WorkspaceType);

  workspace->smResult = E_OK;
  CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH(workspace->smResult, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_WorkspaceType));

  return E_OK;
}

#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle --------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)

/* Deviation CODEMETRIC-1, CODEMETRIC-2, CODEMETRIC-3, CODEMETRIC-4 */
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_WorkspaceType);

  Std_ReturnType              result           = E_NOT_OK;
  Crypto_xVIx_xAIx_LNWordType TmpLnWord[2U]    = {1U, 1U};
  uint32                      NumberLength     = workspace->NLength;
  uint32                      i;
  uint32                      Index            = 0U;
  boolean                     SeparatorFound   = FALSE;
  boolean                     DecryptErrorFlag = FALSE;

  /* setup secondary job */
  CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB();
  CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_KEY();
  CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_SRV();

  primitive->P2->data->P1 = primitive;

  /* 2. a) len(C) != nlLen => error */
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0032, 1 */
  if (job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength == workspace->NLength)
  {
    /* 2. b) c = BS2I(C) */
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0033, 1 */
    result = Crypto_xVIx_xAIx_LNBEByteArrayToNumber(
               job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr,
               job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength,
               workspace->Tmp1Value,
               (Crypto_xVIx_xAIx_LNWordType)(sizeof(workspace->Tmp1Value) / sizeof(workspace->Tmp1Value[0U]))
             );
  }

  /* 2. c) 1 < c < n - 1 */
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0034, 1 */
  if (E_OK == result)
  {
    /* CHECK: NOPARSE
     * Test input leading to c<=1 is not trivial and would require a huge effort, thus this path cannot
     * be reached with tests.
     */
    if (
         CRYPTO_XVIX_XAIX_LN_E_LARGER != Crypto_xVIx_xAIx_LNCompareNumbers(
                                                                            workspace->Tmp1Value, /* c */
                                                                            TmpLnWord /* 1 */
                                                                          )
       )
    {
      /* c <= 1 */
      result = E_NOT_OK;
    }
    /* CHECK: PARSE */
  }

  if (E_OK == result)
  {
    Crypto_xVIx_xAIx_LNSubtraction(
                                    workspace->modulus,
                                    workspace->modulus,
                                    TmpLnWord
                                  );

    if (
         CRYPTO_XVIX_XAIX_LN_E_SMALLER != Crypto_xVIx_xAIx_LNCompareNumbers(
                                                                             workspace->Tmp1Value, /* c */
                                                                             workspace->modulus /* n - 1 */
                                                                           )
       )
    {
      /* c >= n - 1 */
      result = E_NOT_OK;
    }
    else
    {
      /* Return value (carry) can be discarded as we just add the previous subtracted 1 again */
      (void) Crypto_xVIx_xAIx_LNAddition(
                                          workspace->modulus,
                                          workspace->modulus,
                                          TmpLnWord
                                        );
    }
  }

  /* 3. RSA decryption */
  /* 3. a) em = RSADP((n,d),c) */
  if (E_OK == result)
  {
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0035, 1 */
    Crypto_xVIx_xAIx_LNModExp(
                               workspace->Tmp2Value, /* em */
                               workspace->Tmp1Value, /* c */
                               workspace->modulus, /* n */
                               workspace->priExp, /* d */
                               &workspace->lnCtx
                             );

    /* 3. b) EM = I2BS(em,nLen) */
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0036, 1 */
    result = Crypto_xVIx_xAIx_LNNumberToBEByteArray(
                                                     workspace->Tmp2Value,
                                                     workspace->EM,
                                                     &NumberLength
                                                   );
    workspace->EMLength = NumberLength;
  }

  /* 4. OAEP decoding */
  /* 4. a) HA = H(A) */
  /* Next state will start the hash */
  if (E_OK == result)
  {
    workspace->HashResultLength = workspace->HashLength;

    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        = workspace->AdditionalInput;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     = workspace->AdditionalInputLength;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       = workspace->HashResult;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &workspace->HashResultLength;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode            = CRYPTO_OPERATIONMODE_SINGLECALL;

    CRYPTO_XVIX_XAIX_RESET_CALLBACK();
    primitive->P2->data->P1 = primitive;
    result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                          &(workspace->secondaryJob),
                                                           workspace->paPrimitive->P2
                                                         );
  }

  if (E_OK == result)
  {
    /* 4. b) EM = Y || maskedMgfSeed' || maskedDB' */
    /* 4. c) mgfSeedMask' = MGF(maskedDB', HLen) */
    workspace->DbLength = workspace->NLength - workspace->HashLength - 1U;

    /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0040, 1 */
    workspace->Mgf1Ctx.Cnt = 0U;
    workspace->Mgf1Ctx.Itr = 1U;
    workspace->Mgf1Ctx.MaskOutputPtr    = &workspace->MgfSeedMask[0U];
    workspace->Mgf1Ctx.MaskOutputLength = workspace->HashLength;
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0039, 1 */
    workspace->Mgf1Ctx.MaskInputPtr     = &workspace->EM[1U + workspace->HashLength];
    workspace->Mgf1Ctx.MaskInputLength  = workspace->DbLength;

    /* CHECK: NOPARSE
     * Condition is called only once for trivial input.
     */
    do
    {
      result = Crypto_xVIx_xAIx_StateMachine_Mgf(job, primitive);
    }
    while (CRYPTO_E_BUSY == result);
    /* CHECK: PARSE */
  }

  if (E_OK == result)
  {
    /* 4. */
    /* 4. d) mgfSeed' = maskedMGFSeed' XOR mgfSeedMask' */
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0041, 1 */
    Crypto_xVIx_xAIx_CommonXOR(
                                workspace->MgfSeedMask, /* mgfSeedMask' */
                                /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0038, 1 */
                                &workspace->EM[1U], /* maskedMGFSeed'*/
                                workspace->HashLength
                              );

    /* 4. e) dbMask' = MGF(mgfSeed', nlen-HLen-1) */
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0042, 1 */
    workspace->Mgf1Ctx.Cnt = 0U;
    workspace->Mgf1Ctx.Itr = ((workspace->DbLength + workspace->HashLength) - 1U) / workspace->HashLength;
    workspace->Mgf1Ctx.MaskOutputPtr = &workspace->DbMask[0U];
    workspace->Mgf1Ctx.MaskOutputLength = workspace->DbLength;
    workspace->Mgf1Ctx.MaskInputPtr = &workspace->MgfSeedMask[0U]; /* mgfSeed' */
    workspace->Mgf1Ctx.MaskInputLength = workspace->HashLength;

    do
    {
      result = Crypto_xVIx_xAIx_StateMachine_Mgf(job, primitive);
    }
    while (CRYPTO_E_BUSY == result);
  }

  /* 4. f) DB' = maskedDB' XOR dbMask' */
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0043, 1 */
  Crypto_xVIx_xAIx_CommonXOR(
                              workspace->DbMask, /* dbMask' */
                              /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0039, 1 */
                              &workspace->EM[1U + workspace->HashLength],
                              workspace->DbLength
                            );

  /* 4. g) DB' = HA' || X */
  /* 5. check for decryption errors, do not abort - set DecryptErrorFlag */
  /* 5. a) check Y == 0x00 */
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0037, 1 */
  if (workspace->EM[0U] != 0x00U)
  {
    /* Invalid Y */
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0047, 1 */
    DecryptErrorFlag = TRUE;
  }

  /* 5. b) check HA' == HA */
  if (E_NOT_OK == Crypto_xVIx_xAIx_MemCmpSec(
                                              /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0045, 1 */
                                              workspace->DbMask,
                                              workspace->HashResult,
                                              workspace->HashLength
                                            )
     )
  {
    /* Invalid HA' */
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0048, 1 */
    DecryptErrorFlag = TRUE;
  }

  /* 5. c) check format of X, should be PS||0x01||K */
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0049, 1 */
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0045, 1 */
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0046, 1 */
  for (i = workspace->HashLength; (i < workspace->DbLength); i++)
  {
    /* PS can be 0 or more 0x00 bytes */
    if ((SeparatorFound == FALSE) &&(workspace->DbMask[i] > 0x01U))
    {
      /* Invalid X */
      DecryptErrorFlag = TRUE;
    }
    else
    {
      if ((SeparatorFound == FALSE) && (workspace->DbMask[i] == 0x01U))
      {
        SeparatorFound = TRUE;
        Index = i + 1U;
      }
    }
  }

  if ((SeparatorFound == FALSE) || (Index == workspace->DbLength))
  {
    /* No Separator or K found */
    DecryptErrorFlag = TRUE;
  }

  /* 6. output */
  /* 6. a) only output if no error was detected */
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0050, 1 */
  if (DecryptErrorFlag == FALSE)
  {
    if (*job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr >= (workspace->DbLength - Index))
    {
      /* 6. b) output K */
      /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0051, 1 */
      TS_MemCpy(
                 job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr,
                 &workspace->DbMask[Index],
                 workspace->DbLength - Index
               );
      *job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = workspace->DbLength - Index;
      result = E_OK;
    }
    else
    {
      /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0005, 1 */
      result = CRYPTO_E_SMALL_BUFFER;
      workspace->smResult = result;
    }
  }
  else
  {
    result = E_NOT_OK;
    workspace->smResult = result;
  }

  workspace->smResult = result;
  CRYPTO_XVIX_XAIX_SET_SMRESULT_SINGLECALL(workspace->smResult, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_WorkspaceType));
  return result;
}

#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle ------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)

static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_WorkspaceType);

  if (NULL_PTR != workspace->secondaryJob.jobInfo)
  {
    /* CHECK: NOPARSE
     * In order to cancel the secondaryjob the job has to be running so this check is always true.
     */
    primitive->P2->data->P1 = primitive;

    if (E_OK == workspace->paPrimitive->P2->cnfg->description->fcnCancel(  workspace->paObjectId,
                                                                         &(workspace->secondaryJob),
                                                                           workspace->paPrimitive->P2
                                                                        )
       )
    {
      workspace->notifyType = CRYPTO_XVIX_XAIX_CALLBACK_NONE;
      do
      {
        (void) workspace->paPrimitive->P2->cnfg->description->fcnMain(  workspace->paObjectId,
                                                                      &(workspace->secondaryJob),
                                                                        workspace->paPrimitive->P2
                                                                     );
      }
      while (CRYPTO_XVIX_XAIX_CALLBACK_CANCEL == workspace->notifyType);
    }
    /* CHECK: PARSE */

    primitive->P2->data->P1 = NULL_PTR;
  }

  /* !LINKSTO Crypto.Asr.SWS_Crypto_00183,2 */
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00144,1 */
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00181_1,1 */
  CRYPTO_XVIX_XAIX_SET_SMRESULT_CANCEL(CRYPTO_E_JOB_CANCELED, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_WorkspaceType));

  return E_OK;
}

#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_StartProcess ----------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)

static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_WorkspaceType);

  Std_ReturnType result          = E_NOT_OK;
  boolean        fromPrimitive   = TRUE;
  boolean        IsExponentValid = FALSE;
  boolean        IsModuloValid   = FALSE;

  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyPtr = NULL_PTR;

  /* Get the secondary family hash algorithm length */
  workspace->HashLength = Crypto_xVIx_xAIx_GetHashLen(job->jobPrimitiveInfo->primitiveInfo->algorithm.secondaryFamily);

  /* CHECK: NOPARSE
   * In order to avoid the incorrect secondaryFamily configuration in Csm check is needed. This check is always true.
   */
  if(0U != workspace->HashLength)
  {
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0008, 1 */
    result = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( job->cryptoKeyId,
                                                        CRYPTO_KE_CIPHER_KEY,
                                                       &keyPtr,
                                                        fromPrimitive,
                                                        CRYPTO_XVIX_XAIX_SID_EMPTY
                                                      );
  }
  /* CHECK: PARSE */

  if (E_OK == result)
  {
    /* Deviation TASKING-1 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(result, keyPtr, fromPrimitive);

    if (E_OK == result)
    {
      if (CRYPTO_XVIX_XAIX_KE_FORMAT_BIN_RSA_PRIVATEKEY == keyPtr->cnfg->description->format)
      {
        /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0009, 1 */
        /* Deviation MISRAC2012-1 <+20> */
        workspace->modulusLen =
            ((P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))keyPtr->data->data)[2U] + 1U;

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
                &((P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))keyPtr->data->data)[2U];
            workspace->priExp  =
                &((P2CONST(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))keyPtr->data->data)[2U + workspace->modulusLen + workspace->pubExpLen];

            IsExponentValid = Crypto_xVIx_xAIx_LNIsValid(
                                workspace->priExp,
                                CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_RSA_RSAESOAEP_RSA_PUBLIC_MAX_KEY_SIZE_WORD
                              );
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
      }
      else
      {
        result = E_NOT_OK;
      }

      CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(keyPtr);
    }

    if (E_OK == result)
    {
      /* Check if key is valid */
      IsModuloValid = Crypto_xVIx_xAIx_LNIsValid(
                        workspace->modulus,
                        CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_RSA_RSAESOAEP_RSA_PUBLIC_MAX_KEY_SIZE_WORD
                      );

      /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0009, 1 */
      /* CHECK: NOPARSE
       * Validity of LN is already ensured in KeyElementSet.
       */
      if ((TRUE == IsExponentValid) && (TRUE == IsModuloValid))
      {
        workspace->NLength = workspace->modulus[0U] * CRYPTO_XVIX_XAIX_LN_WORD_LEN_BYTES;
        result = E_OK;
      }
      /* CHECK: PARSE */
    }
  }

  if (E_OK == result)
  {
    /* reset heap */
/*    TS_MemBZero(primitive->cnfg->heap, primitive->cnfg->heapSize);
    workspace->heapTmp1 =
        (P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))(primitive->cnfg->heap);
    workspace->heapTmp2 =
        &(((P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))
      (primitive->cnfg->heap))[CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_RSA_RSAESOAEP_RSA_PUBLIC_MAX_KEY_SIZE_WORD]);
*/
    /* Check for additional input */
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0003, 1 */
    if (E_OK == Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( job->cryptoKeyId,
                                                           CRYPTO_XVIX_XAIX_KE_RSA_ADDITIONAL_INPUT,
                                                          &keyPtr,
                                                           FALSE,
                                                           CRYPTO_XVIX_XAIX_SID_EMPTY
                                                         )
       )
    {
      TS_MemCpy(workspace->AdditionalInput, keyPtr->data->data, keyPtr->data->size);
      workspace->AdditionalInputLength = keyPtr->data->size;
    }
    else
    {
      /* Additional input does not exist. Use empty additional input */
      /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0004, 1 */
      workspace->AdditionalInputLength = 0U;
    }
  }

  workspace->smResult = result;
  return result;
}

#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_Mgf -------------------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON)

static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Mgf
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_RSA_RSAESOAEP_WorkspaceType);

  Std_ReturnType  result = E_NOT_OK;
  TS_PARAM_UNUSED(job);

  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr = workspace->Mgf1Ctx.MaskInputPtr;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength = workspace->Mgf1Ctx.MaskInputLength;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode = CRYPTO_OPERATIONMODE_STREAMSTART;

  CRYPTO_XVIX_XAIX_RESET_CALLBACK();
  primitive->P2->data->P1 = primitive;
  result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                        &(workspace->secondaryJob),
                                                         workspace->paPrimitive->P2
                                                       );

  if (E_OK == result)
  {
    /* D = I2BS(counter, 4) */
    workspace->Mgf1Ctx.MaskCntStr[0U] = (uint8)((workspace->Mgf1Ctx.Cnt >> 24U) & (uint8)0xFFU);
    workspace->Mgf1Ctx.MaskCntStr[1U] = (uint8)((workspace->Mgf1Ctx.Cnt >> 16U) & (uint8)0xFFU);
    workspace->Mgf1Ctx.MaskCntStr[2U] = (uint8)((workspace->Mgf1Ctx.Cnt >>  8U) & (uint8)0xFFU);
    workspace->Mgf1Ctx.MaskCntStr[3U] = (uint8)((workspace->Mgf1Ctx.Cnt       ) & (uint8)0xFFU);
    workspace->Mgf1Ctx.Cnt++;

    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr = workspace->Mgf1Ctx.MaskCntStr;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength = CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_RSA_RSAESOAEP_MGF_CNTLEN;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode = CRYPTO_OPERATIONMODE_UPDATE;

    CRYPTO_XVIX_XAIX_RESET_CALLBACK();
    primitive->P2->data->P1 = primitive;
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0010, 1 */
    result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                          &(workspace->secondaryJob),
                                                           workspace->paPrimitive->P2
                                                         );
  }

  if (E_OK == result)
  {
    if (workspace->Mgf1Ctx.Cnt < workspace->Mgf1Ctx.Itr)
    {
      workspace->Mgf1Ctx.MaskHashResultLength = workspace->HashLength;
    }
    else
    {
      /* Truncate last hash block if needed */
      /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0012, 1 */
      workspace->Mgf1Ctx.MaskHashResultLength = workspace->Mgf1Ctx.MaskOutputLength - ((workspace->Mgf1Ctx.Cnt - 1U) * workspace->HashLength);
    }

    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr = NULL_PTR;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength = 0U;
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0011, 1 */
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr = &workspace->Mgf1Ctx.MaskOutputPtr[(workspace->Mgf1Ctx.Cnt - 1U) * workspace->HashLength];
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0012, 1 */
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &workspace->Mgf1Ctx.MaskHashResultLength;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode = CRYPTO_OPERATIONMODE_FINISH;

    CRYPTO_XVIX_XAIX_RESET_CALLBACK();
    primitive->P2->data->P1 = primitive;
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0010, 1 */
    result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                          &(workspace->secondaryJob),
                                                           workspace->paPrimitive->P2
                                                         );
  }

  /* !LINKSTO Crypto.Req.CPr/DECRYPT_RSA_RSAESOAEP/GENERAL/0099, 1 */
  if ((E_OK == result) && (workspace->Mgf1Ctx.Cnt < workspace->Mgf1Ctx.Itr))
  {
    /* Mask is not finished. Start next hash. */
    result = CRYPTO_E_BUSY;
  }
  else
  {
    workspace->smResult = result;
  }

  return result;
}

#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_RSA_RSAESOAEP == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[end of file]=================================================================*/

