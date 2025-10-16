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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_DECRYPT_AES_ECB.c/0001,1 */

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
 * CODEMETRIC-1) Deviated Rule: HIS_VOCF
 * not 25.19 <= 12
 *
 * Reason:
 * Improving this software quality metric is only possible by splitting up the function
 * which would adversely effect the performance of the primitive. For cryptographic algorithms,
 * a high number of operators/operands are needed for the implementation.
 *
 * CODEMETRIC-2) Deviated Rule: HIS_V(G)
 * not 21 <= 12
 *
 * Reason:
 * SingleCall functions are adjusted for performance and have a reduced amount of function calls
 * on purpose which leads to metric violations.
 */

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int.h>                          /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_DECRYPT_AES_ECB.c/0002,1 */
#include <Crypto_xVIx_xAIx_Int_KeyManagement.h>            /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_DECRYPT_AES_ECB.c/0003,1 */
#include <Crypto_xVIx_xAIx_Int_CPr_DECRYPT_AES_ECB.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_DECRYPT_AES_ECB.c/0004,1 */

/*==================[macros]======================================================================*/

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT,1 */
#if (defined CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT)
#error CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT already defined
#endif
/** \brief  Number of entries in the primitives state transition table. **/
#define CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT 9U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT,1 */
#if (defined CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT)
#error CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT already defined
#endif
/** \brief  Number of entries in the primitives state action table. **/
#define CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT 9U

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

#if (defined CRYPTO_XVIX_XAIX_STATE_SINGLECALL)
#error CRYPTO_XVIX_XAIX_STATE_SINGLECALL already defined
#endif
/** \brief  The SingleCall state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_SINGLECALL 6U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_CANCEL,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_CANCEL)
#error CRYPTO_XVIX_XAIX_STATE_CANCEL already defined
#endif
/** \brief  The Cancel state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_CANCEL 7U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_ERROR,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_ERROR)
#error CRYPTO_XVIX_XAIX_STATE_ERROR already defined
#endif
/** \brief  The Error state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_ERROR 8U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_INT_CPR_SERVICE_AES_ECB_SBOXLEN,1 */
#if (defined CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_SBOXLEN)
#error CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_SBOXLEN already defined
#endif
/** \brief  Defines the length of the SBox and SBoxInv lookup tables. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_SBOXLEN 256U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_INT_CPR_SERVICE_AES_ECB_TETDLEN,1 */
#if (defined CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_TETDLEN)
#error CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_TETDLEN already defined
#endif
/** \brief  Defines the length of the Te/Td lookup tables. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_TETDLEN 256U

/* !LINKSTO Crypto.Req.CPr/DECRYPT_AES_ECB/GENERAL/0009,1 */
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_INT_CPR_SERVICE_AES_ECB_RCONFASTLEN,1 */
#if (defined CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_RCONFASTLEN)
#error CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_RCONFASTLEN already defined
#endif
/** \brief  Defines the length of the Round Constants table used by
 **         the fast implementation variant.
 **/
#define CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_RCONFASTLEN 10U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_INT_CPR_SERVICE_AES_ECB_KEYLEN_128,1 */
#if (defined CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_KEYLEN_128)
#error CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_KEYLEN_128 already defined
#endif
/** \brief  Crypto_xVIx_xAIx_AES_KeyType 128 bits key. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_KEYLEN_128 16U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_INT_CPR_SERVICE_AES_ECB_KEYLEN_192,1 */
#if (defined CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_KEYLEN_192)
#error CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_KEYLEN_192 already defined
#endif
/** \brief  Crypto_xVIx_xAIx_AES_KeyType 192 bits key. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_KEYLEN_192 24U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_INT_CPR_SERVICE_AES_ECB_KEYLEN_256,1 */
#if (defined CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_KEYLEN_256)
#error CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_KEYLEN_256 already defined
#endif
/** \brief  Crypto_xVIx_xAIx_AES_KeyType 256 bits key. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_KEYLEN_256 32U

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static FUNC(boolean, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetNextState
(
  P2VAR(uint8,                                         AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) smStateIndx,
        Crypto_xVIx_xAIx_PrimitiveStateIdentifierType                                         curState,
        Std_ReturnType                                                                        resultAction,
        Crypto_ProcessingType                                                                 jobProcessing,
  P2VAR(Crypto_xVIx_xAIx_PrimitiveStateIdentifierType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) nxtState
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

/* ---state action functions--------------------------------------------------------------------- */

/* None */

/* ---state transition functions----------------------------------------------------------------- */

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
 ** \retval  E_OK      request successful
 ** \retval  E_NOT_OK  request failed
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHEXEC'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_STARTIDLE'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

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
 ** \retval  E_OK      request successful
 ** \retval  E_NOT_OK  request failed
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

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
 ** \retval  E_OK      request successful
 ** \retval  E_NOT_OK  request failed
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

/* ---misc procedures---------------------------------------------------------------------------- */

/** \brief  Setup an AES ECB encryption.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in,out]  workspace  Pointer to the primitives workspace instance.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      request successful
 ** \retval  E_NOT_OK  request failed
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_Setup
(
  P2VAR(Crypto_JobType,                                     AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2VAR(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_WorkspaceType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

/** \brief  Rijndael's key schedule expands an 128/192/256 bit key into an 176/208/240 bytes key.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in,out]  workspace  Pointer to the primitives workspace instance.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_AesKeyExpansion
(
  P2VAR(Crypto_JobType,                                     AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2VAR(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_WorkspaceType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

/** \brief  Encrypts the ciphertext based on the extended key and on lookup tables which combine
 **         the ByteSub, ShiftRow and MixColumn transformations.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in,out]  workspace  Pointer to the primitives workspace instance.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_AesOperateRounds
(
  P2VAR(Crypto_JobType,                                     AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2VAR(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_WorkspaceType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

/** \brief  Maps the input byte array stored in the AES state variable to the intermediate
 **         variables used to perform the calculation.
 **
 ** \param[out]  colFirst   Pointer to the variable where the values corresponding
 **                         to the first column will be stored.
 ** \param[out]  colSecond  Pointer to the variable where the values corresponding
 **                         to the second column will be stored.
 ** \param[out]  colThird   Pointer to the variable where the values corresponding
 **                         to the third column will be stored.
 ** \param[out]  colFourth  Pointer to the variable where the values corresponding
 **                         to the fourth column will be stored.
 ** \param[in]   aesState   Pointer to AES state.
 **
 ** \Reentrancy{Non-reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_AesMapState
(
    P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) colFirst,
    P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) colSecond,
    P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) colThird,
    P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) colFourth,
  P2CONST(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) aesState
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

/** \brief  Unmaps the input byte array stored in the intermediate variables to the
 **         AES state variable.
 **
 ** \param[in]   colFirst   Pointer to the variable where the values corresponding
 **                         to the first column will be stored.
 ** \param[in]   colSecond  Pointer to the variable where the values corresponding
 **                         to the second column will be stored.
 ** \param[in]   colThird   Pointer to the variable where the values corresponding
 **                         to the third column will be stored.
 ** \param[in]   colFourth  Pointer to the variable where the values corresponding
 **                         to the fourth column will be stored.
 ** \param[out]  aesState   Pointer to AES state.
 **
 ** \Reentrancy{Non-reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_AesUnmapState
(
  P2CONST(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) colFirst,
  P2CONST(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) colSecond,
  P2CONST(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) colThird,
  P2CONST(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) colFourth,
    P2VAR(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) aesState
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal constants]==========================================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  The primitives state transition table. **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_StateTransitionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateTransitionType, CRYPTO_xVIx_xAIx_CONST)
Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Process_StateTransitionTable[CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT] =
{
  { NULL_PTR,                                                  CRYPTO_XVIX_XAIX_STATE_STARTIDLE,        CRYPTO_XVIX_XAIX_STATE_STARTIDLE,        CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE_TO_CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1               */
  { Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle,        CRYPTO_XVIX_XAIX_STATE_STARTEXEC,        CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,       CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },

  { NULL_PTR,                                                  CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,       CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,       CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE_TO_CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE/0001,1             */
  { Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateFinishIdle, CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC,       CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE, CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },

  { NULL_PTR,                                                  CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE, CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE, CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE_TO_CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE/0001,1 */
  { Crypto_xVIx_xAIx_StateMachine_FinishExec2StartIdle,        CRYPTO_XVIX_XAIX_STATE_FINISHEXEC,       CRYPTO_XVIX_XAIX_STATE_STARTIDLE,        CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },

  { Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle,        CRYPTO_XVIX_XAIX_STATE_SINGLECALL,       CRYPTO_XVIX_XAIX_STATE_STARTIDLE,        CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },

  { Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle,            CRYPTO_XVIX_XAIX_STATE_CANCEL,           CRYPTO_XVIX_XAIX_STATE_STARTIDLE,        CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },
  { Crypto_xVIx_xAIx_StateMachine_Error2StartIdle,             CRYPTO_XVIX_XAIX_STATE_ERROR,            CRYPTO_XVIX_XAIX_STATE_STARTIDLE,        CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK }
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

/** \brief  The primitives state action table. **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_StateActionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateActionType, CRYPTO_xVIx_xAIx_CONST)
Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Process_StateActionTable[CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT] =
{
  /* CRYPTO_XVIX_XAIX_STATE_STARTIDLE        */ { NULL_PTR }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1        */
  /* CRYPTO_XVIX_XAIX_STATE_STARTEXEC        */ { NULL_PTR }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTEXEC/0001,1        */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE       */ { NULL_PTR }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC       */ { NULL_PTR }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE */ { NULL_PTR }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE/0001,1 */
  /* CRYPTO_XVIX_XAIX_STATE_FINISHEXEC       */ { NULL_PTR }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_FINISHEXEC/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_SINGLECALL       */ { NULL_PTR },
  /* CRYPTO_XVIX_XAIX_STATE_CANCEL           */ { NULL_PTR },
  /* CRYPTO_XVIX_XAIX_STATE_ERROR            */ { NULL_PTR }
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_32
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  Constant array which holds the Td0 lookup table  **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static CONST(uint32, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_TETDLEN] =
{
  0x51F4A750U, 0x7E416553U, 0x1A17A4C3U, 0x3A275E96U,
  0x3BAB6BCBU, 0x1F9D45F1U, 0xACFA58ABU, 0x4BE30393U,
  0x2030FA55U, 0xAD766DF6U, 0x88CC7691U, 0xF5024C25U,
  0x4FE5D7FCU, 0xC52ACBD7U, 0x26354480U, 0xB562A38FU,
  0xDEB15A49U, 0x25BA1B67U, 0x45EA0E98U, 0x5DFEC0E1U,
  0xC32F7502U, 0x814CF012U, 0x8D4697A3U, 0x6BD3F9C6U,
  0x038F5FE7U, 0x15929C95U, 0xBF6D7AEBU, 0x955259DAU,
  0xD4BE832DU, 0x587421D3U, 0x49E06929U, 0x8EC9C844U,
  0x75C2896AU, 0xF48E7978U, 0x99583E6BU, 0x27B971DDU,
  0xBEE14FB6U, 0xF088AD17U, 0xC920AC66U, 0x7DCE3AB4U,
  0x63DF4A18U, 0xE51A3182U, 0x97513360U, 0x62537F45U,
  0xB16477E0U, 0xBB6BAE84U, 0xFE81A01CU, 0xF9082B94U,
  0x70486858U, 0x8F45FD19U, 0x94DE6C87U, 0x527BF8B7U,
  0xAB73D323U, 0x724B02E2U, 0xE31F8F57U, 0x6655AB2AU,
  0xB2EB2807U, 0x2FB5C203U, 0x86C57B9AU, 0xD33708A5U,
  0x302887F2U, 0x23BFA5B2U, 0x02036ABAU, 0xED16825CU,
  0x8ACF1C2BU, 0xA779B492U, 0xF307F2F0U, 0x4E69E2A1U,
  0x65DAF4CDU, 0x0605BED5U, 0xD134621FU, 0xC4A6FE8AU,
  0x342E539DU, 0xA2F355A0U, 0x058AE132U, 0xA4F6EB75U,
  0x0B83EC39U, 0x4060EFAAU, 0x5E719F06U, 0xBD6E1051U,
  0x3E218AF9U, 0x96DD063DU, 0xDD3E05AEU, 0x4DE6BD46U,
  0x91548DB5U, 0x71C45D05U, 0x0406D46FU, 0x605015FFU,
  0x1998FB24U, 0xD6BDE997U, 0x894043CCU, 0x67D99E77U,
  0xB0E842BDU, 0x07898B88U, 0xE7195B38U, 0x79C8EEDBU,
  0xA17C0A47U, 0x7C420FE9U, 0xF8841EC9U, 0x00000000U,
  0x09808683U, 0x322BED48U, 0x1E1170ACU, 0x6C5A724EU,
  0xFD0EFFFBU, 0x0F853856U, 0x3DAED51EU, 0x362D3927U,
  0x0A0FD964U, 0x685CA621U, 0x9B5B54D1U, 0x24362E3AU,
  0x0C0A67B1U, 0x9357E70FU, 0xB4EE96D2U, 0x1B9B919EU,
  0x80C0C54FU, 0x61DC20A2U, 0x5A774B69U, 0x1C121A16U,
  0xE293BA0AU, 0xC0A02AE5U, 0x3C22E043U, 0x121B171DU,
  0x0E090D0BU, 0xF28BC7ADU, 0x2DB6A8B9U, 0x141EA9C8U,
  0x57F11985U, 0xAF75074CU, 0xEE99DDBBU, 0xA37F60FDU,
  0xF701269FU, 0x5C72F5BCU, 0x44663BC5U, 0x5BFB7E34U,
  0x8B432976U, 0xCB23C6DCU, 0xB6EDFC68U, 0xB8E4F163U,
  0xD731DCCAU, 0x42638510U, 0x13972240U, 0x84C61120U,
  0x854A247DU, 0xD2BB3DF8U, 0xAEF93211U, 0xC729A16DU,
  0x1D9E2F4BU, 0xDCB230F3U, 0x0D8652ECU, 0x77C1E3D0U,
  0x2BB3166CU, 0xA970B999U, 0x119448FAU, 0x47E96422U,
  0xA8FC8CC4U, 0xA0F03F1AU, 0x567D2CD8U, 0x223390EFU,
  0x87494EC7U, 0xD938D1C1U, 0x8CCAA2FEU, 0x98D40B36U,
  0xA6F581CFU, 0xA57ADE28U, 0xDAB78E26U, 0x3FADBFA4U,
  0x2C3A9DE4U, 0x5078920DU, 0x6A5FCC9BU, 0x547E4662U,
  0xF68D13C2U, 0x90D8B8E8U, 0x2E39F75EU, 0x82C3AFF5U,
  0x9F5D80BEU, 0x69D0937CU, 0x6FD52DA9U, 0xCF2512B3U,
  0xC8AC993BU, 0x10187DA7U, 0xE89C636EU, 0xDB3BBB7BU,
  0xCD267809U, 0x6E5918F4U, 0xEC9AB701U, 0x834F9AA8U,
  0xE6956E65U, 0xAAFFE67EU, 0x21BCCF08U, 0xEF15E8E6U,
  0xBAE79BD9U, 0x4A6F36CEU, 0xEA9F09D4U, 0x29B07CD6U,
  0x31A4B2AFU, 0x2A3F2331U, 0xC6A59430U, 0x35A266C0U,
  0x744EBC37U, 0xFC82CAA6U, 0xE090D0B0U, 0x33A7D815U,
  0xF104984AU, 0x41ECDAF7U, 0x7FCD500EU, 0x1791F62FU,
  0x764DD68DU, 0x43EFB04DU, 0xCCAA4D54U, 0xE49604DFU,
  0x9ED1B5E3U, 0x4C6A881BU, 0xC12C1FB8U, 0x4665517FU,
  0x9D5EEA04U, 0x018C355DU, 0xFA877473U, 0xFB0B412EU,
  0xB3671D5AU, 0x92DBD252U, 0xE9105633U, 0x6DD64713U,
  0x9AD7618CU, 0x37A10C7AU, 0x59F8148EU, 0xEB133C89U,
  0xCEA927EEU, 0xB761C935U, 0xE11CE5EDU, 0x7A47B13CU,
  0x9CD2DF59U, 0x55F2733FU, 0x1814CE79U, 0x73C737BFU,
  0x53F7CDEAU, 0x5FFDAA5BU, 0xDF3D6F14U, 0x7844DB86U,
  0xCAAFF381U, 0xB968C43EU, 0x3824342CU, 0xC2A3405FU,
  0x161DC372U, 0xBCE2250CU, 0x283C498BU, 0xFF0D9541U,
  0x39A80171U, 0x080CB3DEU, 0xD8B4E49CU, 0x6456C190U,
  0x7BCB8461U, 0xD532B670U, 0x486C5C74U, 0xD0B85742U
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_32
#include <Crypto_xVIx_xAIx_MemMap.h>

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_8
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  Constant array which contains one-dimensional State array of 32 bit words for the AES_ECB Primitive **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static CONST(uint8, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxNrm[CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_SBOXLEN] =
{
  0x63U, 0x7CU, 0x77U, 0x7BU, 0xF2U, 0x6BU, 0x6FU, 0xC5U,
  0x30U, 0x01U, 0x67U, 0x2BU, 0xFEU, 0xD7U, 0xABU, 0x76U,
  0xCAU, 0x82U, 0xC9U, 0x7DU, 0xFAU, 0x59U, 0x47U, 0xF0U,
  0xADU, 0xD4U, 0xA2U, 0xAFU, 0x9CU, 0xA4U, 0x72U, 0xC0U,
  0xB7U, 0xFDU, 0x93U, 0x26U, 0x36U, 0x3FU, 0xF7U, 0xCCU,
  0x34U, 0xA5U, 0xE5U, 0xF1U, 0x71U, 0xD8U, 0x31U, 0x15U,
  0x04U, 0xC7U, 0x23U, 0xC3U, 0x18U, 0x96U, 0x05U, 0x9AU,
  0x07U, 0x12U, 0x80U, 0xE2U, 0xEBU, 0x27U, 0xB2U, 0x75U,
  0x09U, 0x83U, 0x2CU, 0x1AU, 0x1BU, 0x6EU, 0x5AU, 0xA0U,
  0x52U, 0x3BU, 0xD6U, 0xB3U, 0x29U, 0xE3U, 0x2FU, 0x84U,
  0x53U, 0xD1U, 0x00U, 0xEDU, 0x20U, 0xFCU, 0xB1U, 0x5BU,
  0x6AU, 0xCBU, 0xBEU, 0x39U, 0x4AU, 0x4CU, 0x58U, 0xCFU,
  0xD0U, 0xEFU, 0xAAU, 0xFBU, 0x43U, 0x4DU, 0x33U, 0x85U,
  0x45U, 0xF9U, 0x02U, 0x7FU, 0x50U, 0x3CU, 0x9FU, 0xA8U,
  0x51U, 0xA3U, 0x40U, 0x8FU, 0x92U, 0x9DU, 0x38U, 0xF5U,
  0xBCU, 0xB6U, 0xDAU, 0x21U, 0x10U, 0xFFU, 0xF3U, 0xD2U,
  0xCDU, 0x0CU, 0x13U, 0xECU, 0x5FU, 0x97U, 0x44U, 0x17U,
  0xC4U, 0xA7U, 0x7EU, 0x3DU, 0x64U, 0x5DU, 0x19U, 0x73U,
  0x60U, 0x81U, 0x4FU, 0xDCU, 0x22U, 0x2AU, 0x90U, 0x88U,
  0x46U, 0xEEU, 0xB8U, 0x14U, 0xDEU, 0x5EU, 0x0BU, 0xDBU,
  0xE0U, 0x32U, 0x3AU, 0x0AU, 0x49U, 0x06U, 0x24U, 0x5CU,
  0xC2U, 0xD3U, 0xACU, 0x62U, 0x91U, 0x95U, 0xE4U, 0x79U,
  0xE7U, 0xC8U, 0x37U, 0x6DU, 0x8DU, 0xD5U, 0x4EU, 0xA9U,
  0x6CU, 0x56U, 0xF4U, 0xEAU, 0x65U, 0x7AU, 0xAEU, 0x08U,
  0xBAU, 0x78U, 0x25U, 0x2EU, 0x1CU, 0xA6U, 0xB4U, 0xC6U,
  0xE8U, 0xDDU, 0x74U, 0x1FU, 0x4BU, 0xBDU, 0x8BU, 0x8AU,
  0x70U, 0x3EU, 0xB5U, 0x66U, 0x48U, 0x03U, 0xF6U, 0x0EU,
  0x61U, 0x35U, 0x57U, 0xB9U, 0x86U, 0xC1U, 0x1DU, 0x9EU,
  0xE1U, 0xF8U, 0x98U, 0x11U, 0x69U, 0xD9U, 0x8EU, 0x94U,
  0x9BU, 0x1EU, 0x87U, 0xE9U, 0xCEU, 0x55U, 0x28U, 0xDFU,
  0x8CU, 0xA1U, 0x89U, 0x0DU, 0xBFU, 0xE6U, 0x42U, 0x68U,
  0x41U, 0x99U, 0x2DU, 0x0FU, 0xB0U, 0x54U, 0xBBU, 0x16U
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

/** \brief  Constant which contains the inverse of the one-dimensional State array of 32 bit words
 **         for the AES_ECB Primitive
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static CONST(uint8, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxInv[CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_SBOXLEN] =
{
  0x52U, 0x09U, 0x6AU, 0xD5U, 0x30U, 0x36U, 0xA5U, 0x38U,
  0xBFU, 0x40U, 0xA3U, 0x9EU, 0x81U, 0xF3U, 0xD7U, 0xFBU,
  0x7CU, 0xE3U, 0x39U, 0x82U, 0x9BU, 0x2FU, 0xFFU, 0x87U,
  0x34U, 0x8EU, 0x43U, 0x44U, 0xC4U, 0xDEU, 0xE9U, 0xCBU,
  0x54U, 0x7BU, 0x94U, 0x32U, 0xA6U, 0xC2U, 0x23U, 0x3DU,
  0xEEU, 0x4CU, 0x95U, 0x0BU, 0x42U, 0xFAU, 0xC3U, 0x4EU,
  0x08U, 0x2EU, 0xA1U, 0x66U, 0x28U, 0xD9U, 0x24U, 0xB2U,
  0x76U, 0x5BU, 0xA2U, 0x49U, 0x6DU, 0x8BU, 0xD1U, 0x25U,
  0x72U, 0xF8U, 0xF6U, 0x64U, 0x86U, 0x68U, 0x98U, 0x16U,
  0xD4U, 0xA4U, 0x5CU, 0xCCU, 0x5DU, 0x65U, 0xB6U, 0x92U,
  0x6CU, 0x70U, 0x48U, 0x50U, 0xFDU, 0xEDU, 0xB9U, 0xDAU,
  0x5EU, 0x15U, 0x46U, 0x57U, 0xA7U, 0x8DU, 0x9DU, 0x84U,
  0x90U, 0xD8U, 0xABU, 0x00U, 0x8CU, 0xBCU, 0xD3U, 0x0AU,
  0xF7U, 0xE4U, 0x58U, 0x05U, 0xB8U, 0xB3U, 0x45U, 0x06U,
  0xD0U, 0x2CU, 0x1EU, 0x8FU, 0xCAU, 0x3FU, 0x0FU, 0x02U,
  0xC1U, 0xAFU, 0xBDU, 0x03U, 0x01U, 0x13U, 0x8AU, 0x6BU,
  0x3AU, 0x91U, 0x11U, 0x41U, 0x4FU, 0x67U, 0xDCU, 0xEAU,
  0x97U, 0xF2U, 0xCFU, 0xCEU, 0xF0U, 0xB4U, 0xE6U, 0x73U,
  0x96U, 0xACU, 0x74U, 0x22U, 0xE7U, 0xADU, 0x35U, 0x85U,
  0xE2U, 0xF9U, 0x37U, 0xE8U, 0x1CU, 0x75U, 0xDFU, 0x6EU,
  0x47U, 0xF1U, 0x1AU, 0x71U, 0x1DU, 0x29U, 0xC5U, 0x89U,
  0x6FU, 0xB7U, 0x62U, 0x0EU, 0xAAU, 0x18U, 0xBEU, 0x1BU,
  0xFCU, 0x56U, 0x3EU, 0x4BU, 0xC6U, 0xD2U, 0x79U, 0x20U,
  0x9AU, 0xDBU, 0xC0U, 0xFEU, 0x78U, 0xCDU, 0x5AU, 0xF4U,
  0x1FU, 0xDDU, 0xA8U, 0x33U, 0x88U, 0x07U, 0xC7U, 0x31U,
  0xB1U, 0x12U, 0x10U, 0x59U, 0x27U, 0x80U, 0xECU, 0x5FU,
  0x60U, 0x51U, 0x7FU, 0xA9U, 0x19U, 0xB5U, 0x4AU, 0x0DU,
  0x2DU, 0xE5U, 0x7AU, 0x9FU, 0x93U, 0xC9U, 0x9CU, 0xEFU,
  0xA0U, 0xE0U, 0x3BU, 0x4DU, 0xAEU, 0x2AU, 0xF5U, 0xB0U,
  0xC8U, 0xEBU, 0xBBU, 0x3CU, 0x83U, 0x53U, 0x99U, 0x61U,
  0x17U, 0x2BU, 0x04U, 0x7EU, 0xBAU, 0x77U, 0xD6U, 0x26U,
  0xE1U, 0x69U, 0x14U, 0x63U, 0x55U, 0x21U, 0x0CU, 0x7DU
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_8
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Process -----------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Process/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Process
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_WorkspaceType);

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
    (void) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Reset(workspace->paObjectId, job, primitive);
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
        (void) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Main(objectId, job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Main --------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Main/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Main
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_WorkspaceType);

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

    /* CHECK: NOPARSE
     * The call of state machine action functions is not reachable for DECRYPT_AES_ECB, because this
     * cryptographic primitive does not use action states.
     */
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0007,1 */
    if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Process_StateActionTable[curState].fcnAction))
    {
      resultAction = Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Process_StateActionTable[curState].fcnAction(job, primitive);
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
     * The return value of GetNextState cannot be FALSE for DECRYPT_AES_ECB, because the state machine
     * transition table for this cryptographic primitive is complete.
     */
    if (TRUE == nxtStateFound)
    /* CHECK: PARSE */
    {
      workspace->smStateIndx = smStateIndx;
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0010,1 */
      if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Process_StateTransitionTable[smStateIndx].fcnTransition))
      {
        /* transition function returns using workspace->smResult */
        (void) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Process_StateTransitionTable[smStateIndx].fcnTransition(job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Cancel ------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Cancel/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Cancel
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_WorkspaceType);

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
      (void) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Main(objectId, job, primitive);
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Reset -------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Reset/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Reset
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESET(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_WorkspaceType));
    result = E_OK;
  }
  else
  {
    result = E_OK;
  }

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Restart -------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Restart/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Restart
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESTART(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_WorkspaceType));
  }
  else
  {
    result = E_OK;
  }

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Callback ----------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Callback/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
/* CHECK: NOPARSE
 * This API is only reachable for cryptographic primitives that are using a secondary primitive.
 */
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_WorkspaceType);

  TS_PARAM_UNUSED(objectId);
  TS_PARAM_UNUSED(job);
  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Callback/0002,1 */
  workspace->notifyType   = cbkType;
  workspace->notifyResult = cbkResult;

  return E_OK;
}
/* CHECK: PARSE */
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_StateMachine_Error2StartIdle ----------------------------------------------*/

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveError2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_WorkspaceType);

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
  result              = Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Reset(workspace->paObjectId, job, primitive);
  workspace->smResult = smResult;

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

/*--- Crypto_xVIx_xAIx_GetNextState --------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
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
   * The FOR loop condition can not fail for DECRYPT_AES_ECB, because the state transition table of this
   * cryptographic primitive is straight.
   */
  /* 1) iterate from last found entry in table to last table entry */
  for (i = *smStateIndx; i < CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT; i++)
  /* CHECK: PARSE */
  {
    if (   (Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx   = i;
      break;
    }
  }

  /* CHECK: NOPARSE
   * The FOR loop condition (FALSE == nxtStateFound) is always FALSE for DECRYPT_AES_ECB, because the state
   * transition table of this cryptographic primitive is straight and that is why the previous
   * FOR loop always already finds a next state.
   */
  /* 2) iterate from first table entry to last found entry in table */
  for (i = 0U; (FALSE == nxtStateFound) && (i < *smStateIndx); i++)
  {
    if (   (Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx  = i;
      break;
    }
  }
  /* CHECK: PARSE */

  return nxtStateFound;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */
/* --- Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle --------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Start2Update,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_WorkspaceType);

          Std_ReturnType                                                          result        = E_NOT_OK;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyExpdPtr;
          boolean                                                                 fromPrimitive = FALSE;

  result = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( job->cryptoKeyId,
                                                      CRYPTO_KE_CIPHER_KEY,
                                                     &workspace->keySeedPtr,
                                                      FALSE,
                                                      CRYPTO_XVIX_XAIX_SID_EMPTY
                                                    );
  if (E_OK == result)
  {
    fromPrimitive = TRUE;
    /* Deviation TASKING-1 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(result, workspace->keySeedPtr, fromPrimitive);
  }
  if (E_OK == result)
  {
    result = Crypto_xVIx_xAIx_Procedure_Setup(job, workspace);
    if (E_OK == result)
    {
      if (!(   (E_OK == Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( job->cryptoKeyId,
                                                                   CRYPTO_XVIX_XAIX_KE_AES_EXPANDEDKEY,
                                                                  &keyExpdPtr,
                                                                   FALSE,
                                                                   CRYPTO_XVIX_XAIX_SID_EMPTY
                                                                 )
               )
            && (240U == keyExpdPtr->data->size)
           )
         )
      {
        Crypto_xVIx_xAIx_Procedure_AesKeyExpansion(job, workspace);
      }
      else
      {
        fromPrimitive = TRUE;
        /* Deviation TASKING-1 */
        CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(result, keyExpdPtr, fromPrimitive);
        if (E_OK == result)
        {
          workspace->keyExpdLen = keyExpdPtr->data->size;
          TS_MemCpy(workspace->keyExpd, keyExpdPtr->data->data, workspace->keyExpdLen);
          CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(keyExpdPtr);
        }
      }
    }
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(workspace->keySeedPtr);
  }

  CRYPTO_XVIX_XAIX_SET_SMRESULT_START(result, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateFinishIdle -------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Update2Finish,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  if (CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_BLOCKSIZE == job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength)
  {
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_AES_ECB/GENERAL/0007,1 */
    /* get input data */
    TS_MemCpy(workspace->aesState,
              job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr,
              CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_BLOCKSIZE
             );

    /* process data */
    Crypto_xVIx_xAIx_Procedure_AesOperateRounds(job, workspace);

    if (CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_BLOCKSIZE > *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr))
    {
      /* !LINKSTO Crypto.Req.CPr/DECRYPT_AES_ECB/GENERAL/0017,1 */

      result = CRYPTO_E_SMALL_BUFFER;
    }
    else
    {
      /* write output data */
      TS_MemCpy(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr,
                workspace->aesState,
                CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_BLOCKSIZE
               );
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00135,1 */
      /* !LINKSTO Crypto.Req.CPr/DECRYPT_AES_ECB/GENERAL/0003,1 */
      *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr) = CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_BLOCKSIZE;

      result = E_OK;
    }
  }

  CRYPTO_XVIX_XAIX_SET_SMRESULT_UPDATE(result, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishExec2StartIdle --------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Finish2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_WorkspaceType);

  *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr) = 0U;

  CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH(workspace->smResult, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle --------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_WorkspaceType);

          Std_ReturnType                                                          result        = E_NOT_OK;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyExpdPtr;
          boolean                                                                 fromPrimitive = FALSE;

  result = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( job->cryptoKeyId,
                                                      CRYPTO_KE_CIPHER_KEY,
                                                     &workspace->keySeedPtr,
                                                      FALSE,
                                                      CRYPTO_XVIX_XAIX_SID_EMPTY
                                                    );
  if (E_OK == result)
  {
    fromPrimitive = TRUE;
    /* Deviation TASKING-1 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(result, workspace->keySeedPtr, fromPrimitive);
  }
  if (E_OK == result)
  {
    if (   (E_OK                                  == Crypto_xVIx_xAIx_Procedure_Setup(job, workspace)         )
        && (CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_BLOCKSIZE == job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength)
       )
    {
      if (!(   (E_OK == Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( job->cryptoKeyId,
                                                                   CRYPTO_XVIX_XAIX_KE_AES_EXPANDEDKEY,
                                                                  &keyExpdPtr,
                                                                   FALSE,
                                                                   CRYPTO_XVIX_XAIX_SID_EMPTY
                                                                 )
               )
            && (240U == keyExpdPtr->data->size)
           )
         )
      {
        Crypto_xVIx_xAIx_Procedure_AesKeyExpansion(job, workspace);
      }
      else
      {
        fromPrimitive = TRUE;
        /* Deviation TASKING-1 */
        CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(result, keyExpdPtr, fromPrimitive);
        if (E_OK == result)
        {
          workspace->keyExpdLen = keyExpdPtr->data->size;
          TS_MemCpy(workspace->keyExpd, keyExpdPtr->data->data, workspace->keyExpdLen);
          CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(keyExpdPtr);
        }
      }
    }
    else
    {
      result = E_NOT_OK;
    }
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(workspace->keySeedPtr);
  }
  if (E_OK == result)
  {
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_AES_ECB/GENERAL/0007,1 */
    /* get input data */
    TS_MemCpy(workspace->aesState,
              job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr,
              CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_BLOCKSIZE
             );

    /* process data */
    Crypto_xVIx_xAIx_Procedure_AesOperateRounds(job, workspace);

    if (CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_BLOCKSIZE > *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr))
    {
      /* !LINKSTO Crypto.Req.CPr/DECRYPT_AES_ECB/GENERAL/0017,1 */

      result = CRYPTO_E_SMALL_BUFFER;
    }
    else
    {
      /* write output data */
      TS_MemCpy(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr,
                workspace->aesState,
                CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_BLOCKSIZE
               );
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00135,1 */
      *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr) = CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_BLOCKSIZE;

      result = E_OK;
    }
  }

  CRYPTO_XVIX_XAIX_SET_SMRESULT_SINGLECALL(result, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle ------------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveCancel2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_WorkspaceType);

  /* !LINKSTO Crypto.Asr.SWS_Crypto_00183,2 */
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00144,1 */
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00181_1,1 */
  CRYPTO_XVIX_XAIX_SET_SMRESULT_CANCEL(CRYPTO_E_JOB_CANCELED, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

/* --- Crypto_xVIx_xAIx_Procedure_Setup --------------------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_Setup
(
  P2VAR(Crypto_JobType,                                     AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2VAR(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_WorkspaceType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace
)
{
  Std_ReturnType result      = E_NOT_OK;

  /* !LINKSTO Crypto.Req.CPr/DECRYPT_AES_ECB/GENERAL/0005,1 */
  switch (job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength)
  {
    case CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_KEYLEN_128:
    {
      if (CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_KEYLEN_128 <= workspace->keySeedPtr->data->size)
      {
        workspace->keyLen =  4U;
        workspace->trnNum = 10U;
        result            = E_OK;
      }
    }
    break;

    case CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_KEYLEN_192:
    {
      if (CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_KEYLEN_192 <= workspace->keySeedPtr->data->size)
      {
        workspace->keyLen = 6U;
        workspace->trnNum = 12U;
        result            = E_OK;
      }
    }
    break;

    case CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_KEYLEN_256:
    {
      if (CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_KEYLEN_256 <= workspace->keySeedPtr->data->size)
      {
        workspace->keyLen = 8U;
        workspace->trnNum = 14U;
        result            = E_OK;
      }
    }
    break;

    default:
    {
      /* Nothing to do (MISRA) */
    }
    break;
  }

  workspace->trnCnt = 0U;

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

/* --- Crypto_xVIx_xAIx_Procedure_AesKeyExpansion ----------------------------------------------- */

/* !LINKSTO Crypto.Req.CPr/DECRYPT_AES_ECB/GENERAL/0014,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_AesKeyExpansion
(
  P2VAR(Crypto_JobType,                                     AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2VAR(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_WorkspaceType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace
)
{
  uint32 i;
  uint32 temp;
  uint32 locKeySeedLen = workspace->keySeedPtr->data->size / 4U;

  CONSTP2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) locKeyExpd = workspace->keyExpd;

  CONST(uint32, CRYPTO_xVIx_xAIx_CONST) rconFast[CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_AES_ECB_RCONFASTLEN] =
  {
    0x01000000U, 0x02000000U, 0x04000000U, 0x08000000U,
    0x10000000U, 0x20000000U, 0x40000000U, 0x80000000U,
    0x1B000000U, 0x36000000U
  };

  TS_PARAM_UNUSED(job);

  /* Copy the first key elements */
  for (i = 0U; i < locKeySeedLen; i++)
  {
    locKeyExpd[i] = CRYPTO_XVIX_XAIX_INT_LIB_BYTEARRAY_TO_UINT32(&(workspace->keySeedPtr->data->data[i * 4U]));
  }
  workspace->keyExpdLen = workspace->keySeedPtr->data->size + (16U * workspace->trnNum);

  /* Calculate the rest of the subkeys */
  for (i = locKeySeedLen; i < (4U * (workspace->trnNum + 1U)); i++)
  {
    temp = locKeyExpd[i - 1U];

    if (0U == (i % locKeySeedLen))
    {
      /* Leftmost word (includes the g() function) */
      temp =   (  ((uint32) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxNrm[(temp >> 16U) & 0xFFU] << 24U)
                ^ ((uint32) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxNrm[(temp >>  8U) & 0xFFU] << 16U)
                ^ ((uint32) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxNrm[(temp       ) & 0xFFU] <<  8U)
                ^ ((uint32) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxNrm[(temp >> 24U)        ]       )
                )
              ^ rconFast[(i / locKeySeedLen) - 1U];
    }
    else
    if ((6U < locKeySeedLen) && (4U == (i % locKeySeedLen)))
    {
      /* Fifth word (includes the f() function), only used for 256 bit keys */
      temp =   ((uint32) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxNrm[(temp >> 24U)        ] << 24U)
              ^ ((uint32) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxNrm[(temp >> 16U) & 0xFFU] << 16U)
              ^ ((uint32) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxNrm[(temp >>  8U) & 0xFFU] <<  8U)
              ^ ((uint32) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxNrm[(temp       ) & 0xFFU]       );
    }
    else
    {
      /* Nothing to do (MISRA) */
    }

    locKeyExpd[i] = locKeyExpd[i - locKeySeedLen] ^ temp;
  }

  /* Apply the InvMixColumn transformation to the expanded key */
  for (i = 1U; i < workspace->trnNum; i++)
  {
    uint8 j = 0U;

    temp = ((uint32) i * (uint32) 4U) & (uint32) 0xFFU;

    for (j = 0U; j < 4U; j++)
    {
      locKeyExpd[temp]
      =                          Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxNrm[(locKeyExpd[temp] >> 24U)        ] & 0xFFU]
        ^ CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxNrm[(locKeyExpd[temp] >> 16U) & 0xFFU] & 0xFFU], 24U)
        ^ CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxNrm[(locKeyExpd[temp] >>  8U) & 0xFFU] & 0xFFU], 16U)
        ^ CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxNrm[(locKeyExpd[temp]       ) & 0xFFU] & 0xFFU],  8U);
      temp++;
    }
  }
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

/* --- Crypto_xVIx_xAIx_Procedure_AesOperateRounds ---------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
/* Deviation CODEMETRIC-1 */
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_AesOperateRounds
(
  P2VAR(Crypto_JobType,                                     AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2VAR(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_WorkspaceType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace
)
{
  uint32 t0   = 0U;
  uint32 t1   = 0U;
  uint32 t2   = 0U;
  uint32 t3   = 0U;
  uint32 s0   = 0U;
  uint32 s1   = 0U;
  uint32 s2   = 0U;
  uint32 s3   = 0U;
  uint8  i    = 0U;
  uint32 temp = 0U;

  P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) locKeyExpd = workspace->keyExpd;

  /* Each loop calculates two turns, hence the number of loops is half of the number of turns */
  CONST(uint8, CRYPTO_xVIx_xAIx_CONST) numberOfLoops     = (uint8) (workspace->trnNum / 2U);
  /* Start i of the last sub-key */
  CONST(uint8, CRYPTO_xVIx_xAIx_CONST) keyExpdFastOffset = (uint8) (workspace->trnNum * 4U);

  TS_PARAM_UNUSED(job);

  /* Initial turn */
  /* Map the input byte array to the state */
  Crypto_xVIx_xAIx_Procedure_AesMapState(&s0, &s1, &s2, &s3, workspace->aesState);

  /* !LINKSTO Crypto.Req.CPr/DECRYPT_AES_ECB/GENERAL/0015,1 */
  /* KeyAddition */
  s0 ^= locKeyExpd[keyExpdFastOffset     ];
  s1 ^= locKeyExpd[keyExpdFastOffset + 1U];
  s2 ^= locKeyExpd[keyExpdFastOffset + 2U];
  s3 ^= locKeyExpd[keyExpdFastOffset + 3U];

  /* !LINKSTO Crypto.Req.CPr/DECRYPT_AES_ECB/GENERAL/0010,1 */
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_AES_ECB/GENERAL/0011,1 */
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_AES_ECB/GENERAL/0012,1 */
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_AES_ECB/GENERAL/0013,1 */
  /* Main turns */
  for (i = 0U; i < numberOfLoops; i++)
  {
    temp = ((uint32)keyExpdFastOffset - ((uint32) i * (uint32) 8U));

    t0 =                           Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(s0 >> 24U)        ]
         ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(s3 >> 16U) & 0xFFU], 24U))
         ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(s2 >>  8U) & 0xFFU], 16U))
         ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(s1       ) & 0xFFU],  8U))
         ^ locKeyExpd[temp - 4U];
    t1 =                           Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(s1 >> 24U)        ]
         ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(s0 >> 16U) & 0xFFU], 24U))
         ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(s3 >>  8U) & 0xFFU], 16U))
         ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(s2       ) & 0xFFU],  8U))
         ^ locKeyExpd[temp - 3U];
    t2 =                           Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(s2 >> 24U)        ]
         ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(s1 >> 16U) & 0xFFU], 24U))
         ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(s0 >>  8U) & 0xFFU], 16U))
         ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(s3       ) & 0xFFU],  8U))
         ^ locKeyExpd[temp - 2U];
    t3 =                           Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(s3 >> 24U)        ]
         ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(s2 >> 16U) & 0xFFU], 24U))
         ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(s1 >>  8U) & 0xFFU], 16U))
         ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(s0       ) & 0xFFU],  8U))
         ^ locKeyExpd[temp - 1U];

    /* The last turn does not use the InvMixColumn layer */
    if (i < (numberOfLoops - 1U))
    {
      s0 =                           Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(t0 >> 24U)        ]
           ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(t3 >> 16U) & 0xFFU], 24U))
           ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(t2 >>  8U) & 0xFFU], 16U))
           ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(t1       ) & 0xFFU],  8U))
           ^ locKeyExpd[temp - 8U];
      s1 =                           Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(t1 >> 24U)        ]
           ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(t0 >> 16U) & 0xFFU], 24U))
           ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(t3 >>  8U) & 0xFFU], 16U))
           ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(t2       ) & 0xFFU],  8U))
           ^ locKeyExpd[temp - 7U];
      s2 =                           Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(t2 >> 24U)        ]
           ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(t1 >> 16U) & 0xFFU], 24U))
           ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(t0 >>  8U) & 0xFFU], 16U))
           ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(t3       ) & 0xFFU],  8U))
           ^ locKeyExpd[temp - 6U];
      s3 =                           Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(t3 >> 24U)        ]
           ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(t2 >> 16U) & 0xFFU], 24U))
           ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(t1 >>  8U) & 0xFFU], 16U))
           ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_Td0[(t0       ) & 0xFFU],  8U))
           ^ locKeyExpd[temp - 5U];
    }
  }

  /* !LINKSTO Crypto.Req.CPr/DECRYPT_AES_ECB/GENERAL/0016,1 */
  /* Final turn */
  s0 =   ((uint32)   ((uint32) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxInv[(t0 >> 24U)        ] << 24U)
                   ^ ((uint32) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxInv[(t3 >> 16U) & 0xFFU] << 16U)
                   ^ ((uint32) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxInv[(t2 >>  8U) & 0xFFU] <<  8U)
                   ^ ((uint32) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxInv[(t1       ) & 0xFFU]       )
         )
       ^ locKeyExpd[0U];
  s1 =   ((uint32)   ((uint32) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxInv[(t1 >> 24U)        ] << 24U)
                   ^ ((uint32) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxInv[(t0 >> 16U) & 0xFFU] << 16U)
                   ^ ((uint32) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxInv[(t3 >>  8U) & 0xFFU] <<  8U)
                   ^ ((uint32) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxInv[(t2       ) & 0xFFU]       )
         )
       ^ locKeyExpd[1U];
  s2 =   ((uint32)   ((uint32) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxInv[(t2 >> 24U)        ] << 24U)
                   ^ ((uint32) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxInv[(t1 >> 16U) & 0xFFU] << 16U)
                   ^ ((uint32) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxInv[(t0 >>  8U) & 0xFFU] <<  8U)
                   ^ ((uint32) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxInv[(t3       ) & 0xFFU]       )
         )
       ^ locKeyExpd[2U];
  s3 =   ((uint32)   ((uint32) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxInv[(t3 >> 24U)        ] << 24U)
                   ^ ((uint32) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxInv[(t2 >> 16U) & 0xFFU] << 16U)
                   ^ ((uint32) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxInv[(t1 >>  8U) & 0xFFU] <<  8U)
                   ^ ((uint32) Crypto_xVIx_xAIx_CPr_DECRYPT_AES_ECB_SboxInv[(t0       ) & 0xFFU]       )
         )
       ^ locKeyExpd[3U];

  /* Computation is finished, unmap the state to the byte array */
  Crypto_xVIx_xAIx_Procedure_AesUnmapState(&s0, &s1, &s2, &s3, workspace->aesState);
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

/* --- Crypto_xVIx_xAIx_Procedure_AesMapState --------------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_AesMapState
(
    P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) colFirst,
    P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) colSecond,
    P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) colThird,
    P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) colFourth,
  P2CONST(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) aesState
)
{
  *colFirst  = CRYPTO_XVIX_XAIX_INT_LIB_BYTEARRAY_TO_UINT32(  aesState      );
  *colSecond = CRYPTO_XVIX_XAIX_INT_LIB_BYTEARRAY_TO_UINT32(&(aesState[ 4U]));
  *colThird  = CRYPTO_XVIX_XAIX_INT_LIB_BYTEARRAY_TO_UINT32(&(aesState[ 8U]));
  *colFourth = CRYPTO_XVIX_XAIX_INT_LIB_BYTEARRAY_TO_UINT32(&(aesState[12U]));
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

/* --- Crypto_xVIx_xAIx_Procedure_AesUnmapState ------------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON)
/* Deviation CODEMETRIC-2 */
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_AesUnmapState
(
  P2CONST(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) colFirst,
  P2CONST(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) colSecond,
  P2CONST(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) colThird,
  P2CONST(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) colFourth,
    P2VAR(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) aesState
)
{
  CRYPTO_XVIX_XAIX_INT_LIB_UINT32_TO_BYTEARRAY(  aesState,       *colFirst );
  CRYPTO_XVIX_XAIX_INT_LIB_UINT32_TO_BYTEARRAY(&(aesState[ 4U]), *colSecond);
  CRYPTO_XVIX_XAIX_INT_LIB_UINT32_TO_BYTEARRAY(&(aesState[ 8U]), *colThird );
  CRYPTO_XVIX_XAIX_INT_LIB_UINT32_TO_BYTEARRAY(&(aesState[12U]), *colFourth);
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_AES_ECB == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[end of file]=================================================================*/

