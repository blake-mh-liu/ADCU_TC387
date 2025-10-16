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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_ENCRYPT_AES_ECB.c/0001,1 */

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
 * not 23.95 <= 12
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

#include <Crypto_xVIx_xAIx_Int.h>                          /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_ENCRYPT_AES_ECB.c/0002,1 */
#include <Crypto_xVIx_xAIx_Int_KeyManagement.h>            /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_ENCRYPT_AES_ECB.c/0003,1 */
#include <Crypto_xVIx_xAIx_Int_CPr_ENCRYPT_AES_ECB.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_ENCRYPT_AES_ECB.c/0004,1 */

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
#if (defined CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_SBOXLEN)
#error CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_SBOXLEN already defined
#endif
/** \brief  Defines the length of the SBox and SBoxInv lookup tables. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_SBOXLEN 256U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_INT_CPR_SERVICE_AES_ECB_TETDLEN,1 */
#if (defined CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_TETDLEN)
#error CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_TETDLEN already defined
#endif
/** \brief  Defines the length of the Te/Td lookup tables. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_TETDLEN 256U

/* !LINKSTO Crypto.Req.CPr/ENCRYPT_AES_ECB/GENERAL/0009,1 */
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_INT_CPR_SERVICE_AES_ECB_RCONFASTLEN,1 */
#if (defined CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_RCONFASTLEN)
#error CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_RCONFASTLEN already defined
#endif
/** \brief  Defines the length of the Round Constants table used by
 **         the fast implementation variant.
 **/
#define CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_RCONFASTLEN 10U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_INT_CPR_SERVICE_AES_ECB_KEYLEN_128,1 */
#if (defined CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_KEYLEN_128)
#error CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_KEYLEN_128 already defined
#endif
/** \brief  Crypto_xVIx_xAIx_AES_KeyType 128 bits key. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_KEYLEN_128 16U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_INT_CPR_SERVICE_AES_ECB_KEYLEN_192,1 */
#if (defined CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_KEYLEN_192)
#error CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_KEYLEN_192 already defined
#endif
/** \brief  Crypto_xVIx_xAIx_AES_KeyType 192 bits key. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_KEYLEN_192 24U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_INT_CPR_SERVICE_AES_ECB_KEYLEN_256,1 */
#if (defined CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_KEYLEN_256)
#error CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_KEYLEN_256 already defined
#endif
/** \brief  Crypto_xVIx_xAIx_AES_KeyType 256 bits key. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_KEYLEN_256 32U

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
static FUNC(boolean, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetNextState
(
  P2VAR(uint8,                                         AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) smStateIndx,
        Crypto_xVIx_xAIx_PrimitiveStateIdentifierType                                         curState,
        Std_ReturnType                                                                        resultAction,
        Crypto_ProcessingType                                                                 jobProcessing,
  P2VAR(Crypto_xVIx_xAIx_PrimitiveStateIdentifierType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) nxtState
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_Setup
(
  P2VAR(Crypto_JobType,                                     AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2VAR(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_WorkspaceType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_AesKeyExpansion
(
  P2VAR(Crypto_JobType,                                     AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2VAR(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_WorkspaceType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_AesOperateRounds
(
  P2VAR(Crypto_JobType,                                     AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2VAR(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_WorkspaceType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_AesMapState
(
    P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) colFirst,
    P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) colSecond,
    P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) colThird,
    P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) colFourth,
  P2CONST(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) aesState
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_AesUnmapState
(
  P2CONST(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) colFirst,
  P2CONST(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) colSecond,
  P2CONST(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) colThird,
  P2CONST(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) colFourth,
    P2VAR(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) aesState
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal constants]==========================================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  The primitives state transition table. **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_StateTransitionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateTransitionType, CRYPTO_xVIx_xAIx_CONST)
Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Process_StateTransitionTable[CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT] =
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

/** \brief  The primitives state action table. **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_StateActionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateActionType, CRYPTO_xVIx_xAIx_CONST)
Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Process_StateActionTable[CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT] =
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_32
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  Constant array which holds the Te0 lookup table **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
static CONST(uint32, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_TETDLEN] =
{
  0xC66363A5U, 0xF87C7C84U, 0xEE777799U, 0xF67B7B8DU,
  0xFFF2F20DU, 0xD66B6BBDU, 0xDE6F6FB1U, 0x91C5C554U,
  0x60303050U, 0x02010103U, 0xCE6767A9U, 0x562B2B7DU,
  0xE7FEFE19U, 0xB5D7D762U, 0x4DABABE6U, 0xEC76769AU,
  0x8FCACA45U, 0x1F82829DU, 0x89C9C940U, 0xFA7D7D87U,
  0xEFFAFA15U, 0xB25959EBU, 0x8E4747C9U, 0xFBF0F00BU,
  0x41ADADECU, 0xB3D4D467U, 0x5FA2A2FDU, 0x45AFAFEAU,
  0x239C9CBFU, 0x53A4A4F7U, 0xE4727296U, 0x9BC0C05BU,
  0x75B7B7C2U, 0xE1FDFD1CU, 0x3D9393AEU, 0x4C26266AU,
  0x6C36365AU, 0x7E3F3F41U, 0xF5F7F702U, 0x83CCCC4FU,
  0x6834345CU, 0x51A5A5F4U, 0xD1E5E534U, 0xF9F1F108U,
  0xE2717193U, 0xABD8D873U, 0x62313153U, 0x2A15153FU,
  0x0804040CU, 0x95C7C752U, 0x46232365U, 0x9DC3C35EU,
  0x30181828U, 0x379696A1U, 0x0A05050FU, 0x2F9A9AB5U,
  0x0E070709U, 0x24121236U, 0x1B80809BU, 0xDFE2E23DU,
  0xCDEBEB26U, 0x4E272769U, 0x7FB2B2CDU, 0xEA75759FU,
  0x1209091BU, 0x1D83839EU, 0x582C2C74U, 0x341A1A2EU,
  0x361B1B2DU, 0xDC6E6EB2U, 0xB45A5AEEU, 0x5BA0A0FBU,
  0xA45252F6U, 0x763B3B4DU, 0xB7D6D661U, 0x7DB3B3CEU,
  0x5229297BU, 0xDDE3E33EU, 0x5E2F2F71U, 0x13848497U,
  0xA65353F5U, 0xB9D1D168U, 0x00000000U, 0xC1EDED2CU,
  0x40202060U, 0xE3FCFC1FU, 0x79B1B1C8U, 0xB65B5BEDU,
  0xD46A6ABEU, 0x8DCBCB46U, 0x67BEBED9U, 0x7239394BU,
  0x944A4ADEU, 0x984C4CD4U, 0xB05858E8U, 0x85CFCF4AU,
  0xBBD0D06BU, 0xC5EFEF2AU, 0x4FAAAAE5U, 0xEDFBFB16U,
  0x864343C5U, 0x9A4D4DD7U, 0x66333355U, 0x11858594U,
  0x8A4545CFU, 0xE9F9F910U, 0x04020206U, 0xFE7F7F81U,
  0xA05050F0U, 0x783C3C44U, 0x259F9FBAU, 0x4BA8A8E3U,
  0xA25151F3U, 0x5DA3A3FEU, 0x804040C0U, 0x058F8F8AU,
  0x3F9292ADU, 0x219D9DBCU, 0x70383848U, 0xF1F5F504U,
  0x63BCBCDFU, 0x77B6B6C1U, 0xAFDADA75U, 0x42212163U,
  0x20101030U, 0xE5FFFF1AU, 0xFDF3F30EU, 0xBFD2D26DU,
  0x81CDCD4CU, 0x180C0C14U, 0x26131335U, 0xC3ECEC2FU,
  0xBE5F5FE1U, 0x359797A2U, 0x884444CCU, 0x2E171739U,
  0x93C4C457U, 0x55A7A7F2U, 0xFC7E7E82U, 0x7A3D3D47U,
  0xC86464ACU, 0xBA5D5DE7U, 0x3219192BU, 0xE6737395U,
  0xC06060A0U, 0x19818198U, 0x9E4F4FD1U, 0xA3DCDC7FU,
  0x44222266U, 0x542A2A7EU, 0x3B9090ABU, 0x0B888883U,
  0x8C4646CAU, 0xC7EEEE29U, 0x6BB8B8D3U, 0x2814143CU,
  0xA7DEDE79U, 0xBC5E5EE2U, 0x160B0B1DU, 0xADDBDB76U,
  0xDBE0E03BU, 0x64323256U, 0x743A3A4EU, 0x140A0A1EU,
  0x924949DBU, 0x0C06060AU, 0x4824246CU, 0xB85C5CE4U,
  0x9FC2C25DU, 0xBDD3D36EU, 0x43ACACEFU, 0xC46262A6U,
  0x399191A8U, 0x319595A4U, 0xD3E4E437U, 0xF279798BU,
  0xD5E7E732U, 0x8BC8C843U, 0x6E373759U, 0xDA6D6DB7U,
  0x018D8D8CU, 0xB1D5D564U, 0x9C4E4ED2U, 0x49A9A9E0U,
  0xD86C6CB4U, 0xAC5656FAU, 0xF3F4F407U, 0xCFEAEA25U,
  0xCA6565AFU, 0xF47A7A8EU, 0x47AEAEE9U, 0x10080818U,
  0x6FBABAD5U, 0xF0787888U, 0x4A25256FU, 0x5C2E2E72U,
  0x381C1C24U, 0x57A6A6F1U, 0x73B4B4C7U, 0x97C6C651U,
  0xCBE8E823U, 0xA1DDDD7CU, 0xE874749CU, 0x3E1F1F21U,
  0x964B4BDDU, 0x61BDBDDCU, 0x0D8B8B86U, 0x0F8A8A85U,
  0xE0707090U, 0x7C3E3E42U, 0x71B5B5C4U, 0xCC6666AAU,
  0x904848D8U, 0x06030305U, 0xF7F6F601U, 0x1C0E0E12U,
  0xC26161A3U, 0x6A35355FU, 0xAE5757F9U, 0x69B9B9D0U,
  0x17868691U, 0x99C1C158U, 0x3A1D1D27U, 0x279E9EB9U,
  0xD9E1E138U, 0xEBF8F813U, 0x2B9898B3U, 0x22111133U,
  0xD26969BBU, 0xA9D9D970U, 0x078E8E89U, 0x339494A7U,
  0x2D9B9BB6U, 0x3C1E1E22U, 0x15878792U, 0xC9E9E920U,
  0x87CECE49U, 0xAA5555FFU, 0x50282878U, 0xA5DFDF7AU,
  0x038C8C8FU, 0x59A1A1F8U, 0x09898980U, 0x1A0D0D17U,
  0x65BFBFDAU, 0xD7E6E631U, 0x844242C6U, 0xD06868B8U,
  0x824141C3U, 0x299999B0U, 0x5A2D2D77U, 0x1E0F0F11U,
  0x7BB0B0CBU, 0xA85454FCU, 0x6DBBBBD6U, 0x2C16163AU
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_32
#include <Crypto_xVIx_xAIx_MemMap.h>

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_8
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  Constant array which contains one-dimensional State array of 32 bit words for the AES_ECB Primitive **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
static CONST(uint8, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_SboxNrm[CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_SBOXLEN] =
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_8
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Process -----------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Process/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Process
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_WorkspaceType);

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
    (void) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Reset(workspace->paObjectId, job, primitive);
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
        (void) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Main(objectId, job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Main --------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Main/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Main
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_WorkspaceType);

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
     * The call of state machine action functions is not reachable for ENCRYPT_AES_ECB, because this
     * cryptographic primitive does not use action states.
     */
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0007,1 */
    if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Process_StateActionTable[curState].fcnAction))
    {
      resultAction = Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Process_StateActionTable[curState].fcnAction(job, primitive);
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
     * The return value of GetNextState cannot be FALSE for ENCRYPT_AES_ECB, because the state machine
     * transition table for this cryptographic primitive is complete.
     */
    if (TRUE == nxtStateFound)
    /* CHECK: PARSE */
    {
      workspace->smStateIndx = smStateIndx;
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0010,1 */
      if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Process_StateTransitionTable[smStateIndx].fcnTransition))
      {
        /* transition function returns using workspace->smResult */
        (void) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Process_StateTransitionTable[smStateIndx].fcnTransition(job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Cancel ------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Cancel/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Cancel
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_WorkspaceType);

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
      (void) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Main(objectId, job, primitive);
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Reset -------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Reset/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Reset
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESET(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_WorkspaceType));
    result = E_OK;
  }
  else
  {
    result = E_OK;
  }

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Restart -------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Restart/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Restart
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESTART(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_WorkspaceType));
  }
  else
  {
    result = E_OK;
  }

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Callback ----------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Callback/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
/* CHECK: NOPARSE
 * This API is only reachable for cryptographic primitives that are using a secondary primitive.
 */
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_WorkspaceType);

  TS_PARAM_UNUSED(objectId);
  TS_PARAM_UNUSED(job);
  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Callback/0002,1 */
  workspace->notifyType   = cbkType;
  workspace->notifyResult = cbkResult;

  return E_OK;
}
/* CHECK: PARSE */
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_StateMachine_Error2StartIdle ----------------------------------------------*/

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveError2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_WorkspaceType);

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
  result              = Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Reset(workspace->paObjectId, job, primitive);
  workspace->smResult = smResult;

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

/*--- Crypto_xVIx_xAIx_GetNextState --------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
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
   * The FOR loop condition can not fail for ENCRYPT_AES_ECB, because the state transition table of this
   * cryptographic primitive is straight.
   */
  /* 1) iterate from last found entry in table to last table entry */
  for (i = *smStateIndx; i < CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT; i++)
  /* CHECK: PARSE */
  {
    if (   (Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx   = i;
      break;
    }
  }

  /* CHECK: NOPARSE
   * The FOR loop condition (FALSE == nxtStateFound) is always FALSE for ENCRYPT_AES_ECB, because the state
   * transition table of this cryptographic primitive is straight and that is why the previous
   * FOR loop always already finds a next state.
   */
  /* 2) iterate from first table entry to last found entry in table */
  for (i = 0U; (FALSE == nxtStateFound) && (i < *smStateIndx); i++)
  {
    if (   (Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx  = i;
      break;
    }
  }
  /* CHECK: PARSE */

  return nxtStateFound;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */
/* --- Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle --------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Start2Update,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_WorkspaceType);

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

  CRYPTO_XVIX_XAIX_SET_SMRESULT_START(result, sizeof(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateFinishIdle -------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Update2Finish,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  if (CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_BLOCKSIZE == job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength)
  {
    /* !LINKSTO Crypto.Req.CPr/ENCRYPT_AES_ECB/GENERAL/0007,1 */
    /* get input data */
    TS_MemCpy(workspace->aesState,
              job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr,
              CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_BLOCKSIZE
             );

    /* process data */
    Crypto_xVIx_xAIx_Procedure_AesOperateRounds(job, workspace);

    if (CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_BLOCKSIZE > *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr))
    {
      /* !LINKSTO Crypto.Req.CPr/ENCRYPT_AES_ECB/GENERAL/0017,1 */

      result = CRYPTO_E_SMALL_BUFFER;
    }
    else
    {
      /* write output data */
      TS_MemCpy(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr,
                workspace->aesState,
                CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_BLOCKSIZE
               );
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00135,1 */
      /* !LINKSTO Crypto.Req.CPr/ENCRYPT_AES_ECB/GENERAL/0003,1 */
      *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr) = CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_BLOCKSIZE;

      result = E_OK;
    }
  }

  CRYPTO_XVIX_XAIX_SET_SMRESULT_UPDATE(result, sizeof(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishExec2StartIdle --------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Finish2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_WorkspaceType);

  *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr) = 0U;

  CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH(workspace->smResult, sizeof(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle --------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_SingleCall2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_WorkspaceType);

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
        && (CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_BLOCKSIZE == job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength)
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
    /* !LINKSTO Crypto.Req.CPr/ENCRYPT_AES_ECB/GENERAL/0007,1 */
    /* get input data */
    TS_MemCpy(workspace->aesState,
              job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr,
              CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_BLOCKSIZE
             );

    /* process data */
    Crypto_xVIx_xAIx_Procedure_AesOperateRounds(job, workspace);

    if (CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_BLOCKSIZE > *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr))
    {
      /* !LINKSTO Crypto.Req.CPr/ENCRYPT_AES_ECB/GENERAL/0017,1 */

      result = CRYPTO_E_SMALL_BUFFER;
    }
    else
    {
      /* write output data */
      TS_MemCpy(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr,
                workspace->aesState,
                CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_BLOCKSIZE
               );
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00135,1 */
      *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr) = CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_BLOCKSIZE;

      result = E_OK;
    }
  }

  CRYPTO_XVIX_XAIX_SET_SMRESULT_SINGLECALL(result, sizeof(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle ------------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveCancel2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_WorkspaceType);

  /* !LINKSTO Crypto.Asr.SWS_Crypto_00183,2 */
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00144,1 */
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00181_1,1 */
  CRYPTO_XVIX_XAIX_SET_SMRESULT_CANCEL(CRYPTO_E_JOB_CANCELED, sizeof(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

/* --- Crypto_xVIx_xAIx_Procedure_Setup --------------------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_Setup
(
  P2VAR(Crypto_JobType,                                     AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2VAR(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_WorkspaceType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace
)
{
  Std_ReturnType result      = E_NOT_OK;

  /* !LINKSTO Crypto.Req.CPr/ENCRYPT_AES_ECB/GENERAL/0005,1 */
  switch (job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength)
  {
    case CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_KEYLEN_128:
    {
      if (CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_KEYLEN_128 <= workspace->keySeedPtr->data->size)
      {
        workspace->keyLen =  4U;
        workspace->trnNum = 10U;
        result            = E_OK;
      }
    }
    break;

    case CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_KEYLEN_192:
    {
      if (CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_KEYLEN_192 <= workspace->keySeedPtr->data->size)
      {
        workspace->keyLen = 6U;
        workspace->trnNum = 12U;
        result            = E_OK;
      }
    }
    break;

    case CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_KEYLEN_256:
    {
      if (CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_KEYLEN_256 <= workspace->keySeedPtr->data->size)
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

/* --- Crypto_xVIx_xAIx_Procedure_AesKeyExpansion ----------------------------------------------- */

/* !LINKSTO Crypto.Req.CPr/ENCRYPT_AES_ECB/GENERAL/0014,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_AesKeyExpansion
(
  P2VAR(Crypto_JobType,                                     AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2VAR(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_WorkspaceType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace
)
{
  uint32 i;
  uint32 temp;
  uint32 locKeySeedLen = workspace->keySeedPtr->data->size / 4U;

  CONSTP2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) locKeyExpd = workspace->keyExpd;

  CONST(uint32, CRYPTO_xVIx_xAIx_CONST) rconFast[CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_ECB_RCONFASTLEN] =
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
      temp =   (  ((uint32) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_SboxNrm[(temp >> 16U) & 0xFFU] << 24U)
                ^ ((uint32) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_SboxNrm[(temp >>  8U) & 0xFFU] << 16U)
                ^ ((uint32) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_SboxNrm[(temp       ) & 0xFFU] <<  8U)
                ^ ((uint32) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_SboxNrm[(temp >> 24U)        ]       )
                )
              ^ rconFast[(i / locKeySeedLen) - 1U];
    }
    else
    if ((6U < locKeySeedLen) && (4U == (i % locKeySeedLen)))
    {
      /* Fifth word (includes the f() function), only used for 256 bit keys */
      temp =   ((uint32) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_SboxNrm[(temp >> 24U)        ] << 24U)
              ^ ((uint32) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_SboxNrm[(temp >> 16U) & 0xFFU] << 16U)
              ^ ((uint32) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_SboxNrm[(temp >>  8U) & 0xFFU] <<  8U)
              ^ ((uint32) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_SboxNrm[(temp       ) & 0xFFU]       );
    }
    else
    {
      /* Nothing to do (MISRA) */
    }

    locKeyExpd[i] = locKeyExpd[i - locKeySeedLen] ^ temp;
  }

}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

/* --- Crypto_xVIx_xAIx_Procedure_AesOperateRounds ---------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
/* Deviation CODEMETRIC-1 */
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_AesOperateRounds
(
  P2VAR(Crypto_JobType,                                     AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2VAR(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_WorkspaceType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace
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

  /* !LINKSTO Crypto.Req.CPr/ENCRYPT_AES_ECB/GENERAL/0015,1 */
  /* KeyAddition */
  s0 ^= locKeyExpd[0U];
  s1 ^= locKeyExpd[1U];
  s2 ^= locKeyExpd[2U];
  s3 ^= locKeyExpd[3U];

  /* !LINKSTO Crypto.Req.CPr/ENCRYPT_AES_ECB/GENERAL/0010,1 */
  /* !LINKSTO Crypto.Req.CPr/ENCRYPT_AES_ECB/GENERAL/0011,1 */
  /* !LINKSTO Crypto.Req.CPr/ENCRYPT_AES_ECB/GENERAL/0012,1 */
  /* !LINKSTO Crypto.Req.CPr/ENCRYPT_AES_ECB/GENERAL/0013,1 */
  /* Main turns */
  for (i = 0U; i < numberOfLoops; i++)
  {
    temp = ((uint32) i * (uint32) 8U) & (uint32) 0xFFU;

    t0 =                           Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(s0 >> 24U)        ]
         ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(s1 >> 16U) & 0xFFU], 24U))
         ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(s2 >>  8U) & 0xFFU], 16U))
         ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(s3       ) & 0xFFU],  8U))
         ^ locKeyExpd[temp + 4U];
    t1 =                           Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(s1 >> 24U)        ]
         ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(s2 >> 16U) & 0xFFU], 24U))
         ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(s3 >>  8U) & 0xFFU], 16U))
         ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(s0       ) & 0xFFU],  8U))
         ^ locKeyExpd[temp + 5U];
    t2 =                           Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(s2 >> 24U)        ]
         ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(s3 >> 16U) & 0xFFU], 24U))
         ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(s0 >>  8U) & 0xFFU], 16U))
         ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(s1       ) & 0xFFU],  8U))
         ^ locKeyExpd[temp + 6U];
    t3 =                           Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(s3 >> 24U)        ]
         ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(s0 >> 16U) & 0xFFU], 24U))
         ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(s1 >>  8U) & 0xFFU], 16U))
         ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(s2       ) & 0xFFU],  8U))
         ^ locKeyExpd[temp + 7U];

    /* The last turn does not use the MixColumn layer */
    if (i < (numberOfLoops - 1U))
    {
      s0 =                           Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(t0 >> 24U)        ]
           ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(t1 >> 16U) & 0xFFU], 24U))
           ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(t2 >>  8U) & 0xFFU], 16U))
           ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(t3       ) & 0xFFU],  8U))
           ^ locKeyExpd[temp + 8U];
      s1 =                           Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(t1 >> 24U)        ]
           ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(t2 >> 16U) & 0xFFU], 24U))
           ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(t3 >>  8U) & 0xFFU], 16U))
           ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(t0       ) & 0xFFU],  8U))
           ^ locKeyExpd[temp + 9U];
      s2 =                           Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(t2 >> 24U)        ]
           ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(t3 >> 16U) & 0xFFU], 24U))
           ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(t0 >>  8U) & 0xFFU], 16U))
           ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(t1       ) & 0xFFU],  8U))
           ^ locKeyExpd[temp + 10U];
      s3 =                           Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(t3 >> 24U)        ]
           ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(t0 >> 16U) & 0xFFU], 24U))
           ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(t1 >>  8U) & 0xFFU], 16U))
           ^ (CRYPTO_XVIX_XAIX_ROL32(Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_Te0[(t2       ) & 0xFFU],  8U))
           ^ locKeyExpd[temp + 11U];
    }
  }

  /* !LINKSTO Crypto.Req.CPr/ENCRYPT_AES_ECB/GENERAL/0016,1 */
  /* Final turn */
  s0 =   ((uint32)   ((uint32) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_SboxNrm[(t0 >> 24U)        ] << 24U)
                   ^ ((uint32) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_SboxNrm[(t1 >> 16U) & 0xFFU] << 16U)
                   ^ ((uint32) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_SboxNrm[(t2 >>  8U) & 0xFFU] <<  8U)
                   ^ ((uint32) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_SboxNrm[(t3       ) & 0xFFU]       )
         )
       ^ locKeyExpd[keyExpdFastOffset];
  s1 =   ((uint32)   ((uint32) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_SboxNrm[(t1 >> 24U)        ] << 24U)
                   ^ ((uint32) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_SboxNrm[(t2 >> 16U) & 0xFFU] << 16U)
                   ^ ((uint32) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_SboxNrm[(t3 >>  8U) & 0xFFU] <<  8U)
                   ^ ((uint32) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_SboxNrm[(t0       ) & 0xFFU]       )
         )
       ^ locKeyExpd[keyExpdFastOffset + 1U];
  s2 =   ((uint32)   ((uint32) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_SboxNrm[(t2 >> 24U)        ] << 24U)
                   ^ ((uint32) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_SboxNrm[(t3 >> 16U) & 0xFFU] << 16U)
                   ^ ((uint32) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_SboxNrm[(t0 >>  8U) & 0xFFU] <<  8U)
                   ^ ((uint32) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_SboxNrm[(t1       ) & 0xFFU]       )
         )
       ^ locKeyExpd[keyExpdFastOffset + 2U];
  s3 =   ((uint32)   ((uint32) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_SboxNrm[(t3 >> 24U)        ] << 24U)
                   ^ ((uint32) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_SboxNrm[(t0 >> 16U) & 0xFFU] << 16U)
                   ^ ((uint32) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_SboxNrm[(t1 >>  8U) & 0xFFU] <<  8U)
                   ^ ((uint32) Crypto_xVIx_xAIx_CPr_ENCRYPT_AES_ECB_SboxNrm[(t2       ) & 0xFFU]       )
         )
       ^ locKeyExpd[keyExpdFastOffset + 3U];

  /* Computation is finished, unmap the state to the byte array */
  Crypto_xVIx_xAIx_Procedure_AesUnmapState(&s0, &s1, &s2, &s3, workspace->aesState);
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

/* --- Crypto_xVIx_xAIx_Procedure_AesMapState --------------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

/* --- Crypto_xVIx_xAIx_Procedure_AesUnmapState ------------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON)
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_ECB == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[end of file]=================================================================*/

