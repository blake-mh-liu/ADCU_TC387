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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_AEADENCRYPT_AES_GCM.c/0001,1 */

/*==================[deviations]==================================================================*/

/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.4 (advisory)
 * A conversion should not be performed between a pointer to object
 * and an integer type.
 *
 * Reason:
 * The memory routines are optimized for dealing with aligned memory
 * sections and need to check the correct alignment before the operation.
 *
 * MISRAC2012-2) Deviated Rule: 11.5 (advisory)
 * A conversion should not be performed from pointer to void into pointer to object.
 *
 * Reason:
 * The memory routines are optimized for dealing with aligned memory
 * sections.
 *
 * MISRAC2012-3) Deviated Rule: 2.1 (required)
 * A project shall not contain unreachable code.
 *
 * Reason:
 * The given warnings at this point are false positives, as the macro itself is fully tested
 * for all possible paths of a ternary operator. But a given call of the macro will always go either
 * way of checking the length of the shift width.
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
 * CODEMETRIC-1) Deviated Rule: HIS_VOCF
 * not 24.48 <= 12
 *
 * CODEMETRIC-2) Deviated Rule: HIS_PATH
 * not 8388609 <= 2000
 *
 * CODEMETRIC-3) Deviated Rule: HIS_V(G)
 * not 27 <= 20
 *
 * Reason:
 * Improving this software quality metric is only possible by splitting up the function
 * which would adversely effect the performance of the primitive. For cryptographic algorithms,
 * a high number of operators/operands are needed for the implementation.
 */

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int.h>                              /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_AEADENCRYPT_AES_GCM.c/0002,1 */
#include <Crypto_xVIx_xAIx_Int_KeyManagement.h>                /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_AEADENCRYPT_AES_GCM.c/0003,1 */
#include <Crypto_xVIx_xAIx_Int_CPr_AEADENCRYPT_AES_GCM.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_AEADENCRYPT_AES_GCM.c/0004,1 */

/*==================[macros]======================================================================*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
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

#if (defined CRYPTO_XVIX_XAIX_INT_CPR_GCM_RMS)
#error CRYPTO_XVIX_XAIX_INT_CPR_GCM_RMS already defined
#endif
/** \brief  Macro used in bit reversing a 32 bit value. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_GCM_RMS(x, m, s)                                            \
do                                                                                           \
{                                                                                            \
  (x) = CRYPTO_XVIX_XAIX_OR64(CRYPTO_XVIX_XAIX_SHL64(CRYPTO_XVIX_XAIX_AND64((x), (m)), (s)), \
                              CRYPTO_XVIX_XAIX_AND64(CRYPTO_XVIX_XAIX_SHR64((x), (s)), (m))  \
                             );                                                              \
}                                                                                            \
while (0U)

#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(boolean, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetNextState
(
  P2VAR(uint8,                                         AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) smStateIndx,
        Crypto_xVIx_xAIx_PrimitiveStateIdentifierType                                         curState,
        Std_ReturnType                                                                        resultAction,
        Crypto_ProcessingType                                                                 jobProcessing,
  P2VAR(Crypto_xVIx_xAIx_PrimitiveStateIdentifierType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) nxtState
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */
/** \brief  Hashing using the GHASH algorithm.
 **
 ** Calculate Y = GHASH(data)
 ** GHASH implemented based on the following approach:
 ** www.bearssl.org/constanttime.html#ghash-for-gcm
 ** This hashing function contains a padding function in case the data is not block size aligned.
 **
 ** \param[in,out]  Y     Array to be updated.
 ** \param[in]      H     The GHASH key.
 ** \param[in]      data  Input data.
 ** \param[in]      len   Input data length.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous}
 **/
/* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_GCM/GENERAL/0005,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_AEAD_GCMGHashCTMul
(
    P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) Y,
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) H,
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) data,
          uint32                              len
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

/** \brief  Increment the IV.
 **
 ** Increments the IV stored in a 16 Byte array.
 **
 ** \param[in]  IV  The initialization vector.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_AEAD_GCMInc
(
  P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) IV
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

/** \brief  Multiplication in GF(2)[x] with truncation to the lower 64 bits.
 **
 ** Multiply two uint64s and keep only the low 64 bits.
 **
 ** \param[in]  multiplicator  The multiplicator.
 ** \param[in]  multiplicand   The multiplicand.
 **
 ** \return  Result of the multiplication.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(uint64, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_AEAD_GCMBmul64
(
  uint64 multiplicator,
  uint64 multiplicand
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

/** \brief  Bit-reverse a 64-bit word.
 **
 ** Algorithm based on Chapter 7-1 from "Hackers Delight" by Henry S. Warren.
 **
 ** \param[in]  reverseValue  Value to be reversed.
 **
 ** \return  Reversed value.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(uint64, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_AEAD_GCMRev64
(
  uint64 reverseValue
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS'
 **         to state   'CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS'
 **         or
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS'
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateFinishProcess2Self
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

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
 ** \retval  E_OK      request successful
 ** \retval  E_NOT_OK  request failed
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishProcess2FinishProcessLastBlock
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishProcessLastBlock2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

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
 ** \retval  E_OK      Request successful.
 ** \retval  E_NOT_OK  Request failed.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateFinishProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal constants]==========================================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_8
#include <Crypto_xVIx_xAIx_MemMap.h>

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static CONST(uint8, CRYPTO_xVIx_xAIx_CONST)
Crypto_xVIx_xAIx_CPr_GCMZeroBlock[CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES] =
{
  0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
  0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U
};
#endif /* ((CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_8
#include <Crypto_xVIx_xAIx_MemMap.h>

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  The primitives state transition table. **/

/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_StateTransitionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateTransitionType, CRYPTO_xVIx_xAIx_CONST)
Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Process_StateTransitionTable[CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT] =
{
  { NULL_PTR,                                                           CRYPTO_XVIX_XAIX_STATE_STARTIDLE,              CRYPTO_XVIX_XAIX_STATE_STARTIDLE,              CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE_TO_CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1               */
  { Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle,                 CRYPTO_XVIX_XAIX_STATE_STARTEXEC,              CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,             CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishProcess,             CRYPTO_XVIX_XAIX_STATE_FINISHEXEC,             CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS,          CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { Crypto_xVIx_xAIx_StateMachine_FinishProcess2FinishProcessLastBlock, CRYPTO_XVIX_XAIX_STATE_FINISHPROCESS,          CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSLASTBLOCK, CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { Crypto_xVIx_xAIx_StateMachine_FinishProcessLastBlock2StartIdle,     CRYPTO_XVIX_XAIX_STATE_FINISHPROCESSLASTBLOCK, CRYPTO_XVIX_XAIX_STATE_STARTIDLE,              CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { NULL_PTR,                                                           CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,             CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,             CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE_TO_CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE/0001,1             */
  { Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess,             CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC,             CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,          CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { Crypto_xVIx_xAIx_StateMachine_UpdateFinishProcess2Self,             CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,          CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,          CRYPTO_XVIX_XAIX_PROCESSING_BOTH, CRYPTO_E_BUSY },
  { Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle,       CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,          CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,       CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { NULL_PTR,                                                           CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,       CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,       CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE_TO_CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE/0001,1 */

  { Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle,                     CRYPTO_XVIX_XAIX_STATE_CANCEL,                 CRYPTO_XVIX_XAIX_STATE_STARTIDLE,              CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { Crypto_xVIx_xAIx_StateMachine_Error2StartIdle,                      CRYPTO_XVIX_XAIX_STATE_ERROR,                  CRYPTO_XVIX_XAIX_STATE_STARTIDLE,              CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          }
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

/** \brief  The primitives state action table. **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_StateActionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateActionType, CRYPTO_xVIx_xAIx_CONST)
Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Process_StateActionTable[CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT] =
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Process -------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Process/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Process
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType);

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
    (void) Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Reset(workspace->paObjectId, job, primitive);
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
        (void) Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Main(objectId, job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Main ----------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Main/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Main
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType);

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
    if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Process_StateActionTable[curState].fcnAction))
    {
      resultAction = Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Process_StateActionTable[curState].fcnAction(job, primitive);
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
      if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Process_StateTransitionTable[smStateIndx].fcnTransition))
      {
        /* transition function returns using workspace->smResult */
        (void) Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Process_StateTransitionTable[smStateIndx].fcnTransition(job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Cancel --------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Cancel/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Cancel
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType);

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
      (void) Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Main(objectId, job, primitive);
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Reset ---------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Reset/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Reset
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as
   * secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESET(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType));
    result = E_OK;
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Restart ---------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Restart/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Restart
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESTART(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType));
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Callback ------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Callback/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType);

  TS_PARAM_UNUSED(objectId);
  TS_PARAM_UNUSED(job);
  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Callback/0002,1 */
  workspace->notifyType   = cbkType;
  workspace->notifyResult = cbkResult;

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_StateMachine_Error2StartIdle ----------------------------------------------*/

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveError2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType);

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
  result              = Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Reset(workspace->paObjectId, job, primitive);
  workspace->smResult = smResult;

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

/*--- Crypto_xVIx_xAIx_GetNextState --------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
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
    if (   (Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx   = i;
      break;
    }
  }

  /* 2) iterate from first table entry to last found entry in table */
  for (i = 0U; (FALSE == nxtStateFound) && (i < *smStateIndx); i++)
  {
    if (   (Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx  = i;
      break;
    }
  }

  return nxtStateFound;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */
/* --- Crypto_xVIx_xAIx_CPr_AEAD_GCMGHashCTMul -------------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
/* Deviation CODEMETRIC-2 */
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_AEAD_GCMGHashCTMul
(
    P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) Y,
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) H,
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) data,
          uint32                                        len
)
{
  uint64 Y1  = CRYPTO_XVIX_XAIX_UINT64_UINT8_TO_UINT64_BE(&Y[0U]);
  uint64 Y0  = CRYPTO_XVIX_XAIX_UINT64_UINT8_TO_UINT64_BE(&Y[8U]);
  uint64 H1  = CRYPTO_XVIX_XAIX_UINT64_UINT8_TO_UINT64_BE(&H[0U]);
  uint64 H0  = CRYPTO_XVIX_XAIX_UINT64_UINT8_TO_UINT64_BE(&H[8U]);
  uint64 H1r = Crypto_xVIx_xAIx_CPr_AEAD_GCMRev64(H1);
  uint64 H0r = Crypto_xVIx_xAIx_CPr_AEAD_GCMRev64(H0);
  uint64 H2  = CRYPTO_XVIX_XAIX_XOR64(H0,  H1 );
  uint64 H2r = CRYPTO_XVIX_XAIX_XOR64(H0r, H1r);
  uint32 templen = len;
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tempdata = data;

  templen = len;
  while (0U < templen)
  {
    const uint8  *Src;
          uint8  Tmp[16U] = { 0U };
          uint64 Y0r, Y1r, Y2, Y2r;
          uint64 Z0, Z1, Z2, Z0h, Z1h, Z2h;
          uint64 V0, V1, V2, V3;

    if (16U <= templen)
    {
      Src = tempdata;
      tempdata = &tempdata[16U];
      templen -= 16U;
    }
    else
    {
      TS_MemCpy(Tmp, tempdata, templen);
      Src = Tmp;
      templen = 0U;
    }
    Y1 = CRYPTO_XVIX_XAIX_XOR64(Y1, CRYPTO_XVIX_XAIX_UINT64_UINT8_TO_UINT64_BE(&Src[0U]));
    Y0 = CRYPTO_XVIX_XAIX_XOR64(Y0, CRYPTO_XVIX_XAIX_UINT64_UINT8_TO_UINT64_BE(&Src[8U]));

    Y0r = Crypto_xVIx_xAIx_CPr_AEAD_GCMRev64(Y0);
    Y1r = Crypto_xVIx_xAIx_CPr_AEAD_GCMRev64(Y1);
    Y2  = CRYPTO_XVIX_XAIX_XOR64(Y0,  Y1 );
    Y2r = CRYPTO_XVIX_XAIX_XOR64(Y0r, Y1r);

    Z0  = Crypto_xVIx_xAIx_CPr_AEAD_GCMBmul64(Y0,  H0 );
    Z1  = Crypto_xVIx_xAIx_CPr_AEAD_GCMBmul64(Y1,  H1 );
    Z2  = Crypto_xVIx_xAIx_CPr_AEAD_GCMBmul64(Y2,  H2 );
    Z0h = Crypto_xVIx_xAIx_CPr_AEAD_GCMBmul64(Y0r, H0r);
    Z1h = Crypto_xVIx_xAIx_CPr_AEAD_GCMBmul64(Y1r, H1r);
    Z2h = Crypto_xVIx_xAIx_CPr_AEAD_GCMBmul64(Y2r, H2r);
    Z2  = CRYPTO_XVIX_XAIX_XOR64(Z2,  CRYPTO_XVIX_XAIX_XOR64(Z0,  Z1 ));
    Z2h = CRYPTO_XVIX_XAIX_XOR64(Z2h, CRYPTO_XVIX_XAIX_XOR64(Z0h, Z1h));
    /* Deviation MISRAC2012-3 <START> */
    Z0h = CRYPTO_XVIX_XAIX_SHR64(Crypto_xVIx_xAIx_CPr_AEAD_GCMRev64(Z0h), 1U);
    Z1h = CRYPTO_XVIX_XAIX_SHR64(Crypto_xVIx_xAIx_CPr_AEAD_GCMRev64(Z1h), 1U);
    Z2h = CRYPTO_XVIX_XAIX_SHR64(Crypto_xVIx_xAIx_CPr_AEAD_GCMRev64(Z2h), 1U);
    /* Deviation MISRAC2012-3 <STOP> */
    V0 = Z0;
    V1 = CRYPTO_XVIX_XAIX_XOR64(Z0h, Z2 );
    V2 = CRYPTO_XVIX_XAIX_XOR64(Z1,  Z2h);
    V3 = Z1h;
    /* Deviation MISRAC2012-3 <START> */
    V3 = CRYPTO_XVIX_XAIX_OR64(CRYPTO_XVIX_XAIX_SHL64(V3, 1U), CRYPTO_XVIX_XAIX_SHR64(V2, 63U));
    V2 = CRYPTO_XVIX_XAIX_OR64(CRYPTO_XVIX_XAIX_SHL64(V2, 1U), CRYPTO_XVIX_XAIX_SHR64(V1, 63U));
    V1 = CRYPTO_XVIX_XAIX_OR64(CRYPTO_XVIX_XAIX_SHL64(V1, 1U), CRYPTO_XVIX_XAIX_SHR64(V0, 63U));
    V0 = CRYPTO_XVIX_XAIX_SHL64(V0, 1U);

    V2 = CRYPTO_XVIX_XAIX_XOR64(V2,
                                CRYPTO_XVIX_XAIX_XOR64(CRYPTO_XVIX_XAIX_XOR64(V0,                             CRYPTO_XVIX_XAIX_SHR64(V0, 1U)),
                                                       CRYPTO_XVIX_XAIX_XOR64(CRYPTO_XVIX_XAIX_SHR64(V0, 2U), CRYPTO_XVIX_XAIX_SHR64(V0, 7U))
                                                      )
                               );
    V1 = CRYPTO_XVIX_XAIX_XOR64(CRYPTO_XVIX_XAIX_XOR64(V1,                              CRYPTO_XVIX_XAIX_SHL64(V0, 63U)),
                                CRYPTO_XVIX_XAIX_XOR64(CRYPTO_XVIX_XAIX_SHL64(V0, 62U), CRYPTO_XVIX_XAIX_SHL64(V0, 57U))
                               );
    V3 = CRYPTO_XVIX_XAIX_XOR64(V3,
                                CRYPTO_XVIX_XAIX_XOR64(CRYPTO_XVIX_XAIX_XOR64(V1,                             CRYPTO_XVIX_XAIX_SHR64(V1, 1U)),
                                                       CRYPTO_XVIX_XAIX_XOR64(CRYPTO_XVIX_XAIX_SHR64(V1, 2U), CRYPTO_XVIX_XAIX_SHR64(V1, 7U))
                                                      )
                               );
    V2 = CRYPTO_XVIX_XAIX_XOR64(CRYPTO_XVIX_XAIX_XOR64(V2,                              CRYPTO_XVIX_XAIX_SHL64(V1, 63U)),
                                CRYPTO_XVIX_XAIX_XOR64(CRYPTO_XVIX_XAIX_SHL64(V1, 62U), CRYPTO_XVIX_XAIX_SHL64(V1, 57U))
                               );
    /* Deviation MISRAC2012-3 <STOP> */
    Y0 = V2;
    Y1 = V3;
  }
  CRYPTO_XVIX_XAIX_UINT64_UINT64_TO_UINT8_BE(Y1, &Y[0U]);
  CRYPTO_XVIX_XAIX_UINT64_UINT64_TO_UINT8_BE(Y0, &Y[8U]);
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

/* --- Crypto_xVIx_xAIx_CPr_AEAD_GCMInc --------------------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_AEAD_GCMInc
(
  P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) IV
)
{
  uint8 i;

  /* CHECK: NOPARSE
   * The for loop has a fixed condition which cannot fail at the start, also the IV is always
   * initialized in the beginning which results in the if condition to be always true.
   */
  for (i  = CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES;
       i != CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_IV_LEN_BYTES;
       i--
      )
  {
    ++IV[i - 1U];

    if (IV[i - 1U] != 0x00U)
    {
      break;
    }
  }
  /* CHECK: PARSE */

}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

/* --- Crypto_xVIx_xAIx_CPr_AEAD_GCMBmul64 ------------------------------------------------------ */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
/* Deviation CODEMETRIC-1 */
static FUNC(uint64, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_AEAD_GCMBmul64
(
  uint64 multiplicator,
  uint64 multiplicand
)
{
  uint64 x0, x1, x2, x3;
  uint64 y0, y1, y2, y3;
  uint64 z0, z1, z2, z3;

  x0 = CRYPTO_XVIX_XAIX_AND64(multiplicator, 0x1111111111111111ULL);
  x1 = CRYPTO_XVIX_XAIX_AND64(multiplicator, 0x2222222222222222ULL);
  x2 = CRYPTO_XVIX_XAIX_AND64(multiplicator, 0x4444444444444444ULL);
  x3 = CRYPTO_XVIX_XAIX_AND64(multiplicator, 0x8888888888888888ULL);
  y0 = CRYPTO_XVIX_XAIX_AND64(multiplicand,  0x1111111111111111ULL);
  y1 = CRYPTO_XVIX_XAIX_AND64(multiplicand,  0x2222222222222222ULL);
  y2 = CRYPTO_XVIX_XAIX_AND64(multiplicand,  0x4444444444444444ULL);
  y3 = CRYPTO_XVIX_XAIX_AND64(multiplicand,  0x8888888888888888ULL);

  z0 = CRYPTO_XVIX_XAIX_XOR64(CRYPTO_XVIX_XAIX_XOR64(CRYPTO_XVIX_XAIX_MUL64(x0, y0),
                                                     CRYPTO_XVIX_XAIX_MUL64(x1, y3)
                                                    ),
                              CRYPTO_XVIX_XAIX_XOR64(CRYPTO_XVIX_XAIX_MUL64(x2, y2),
                                                     CRYPTO_XVIX_XAIX_MUL64(x3, y1)
                                                    )
                             );
  z1 = CRYPTO_XVIX_XAIX_XOR64(CRYPTO_XVIX_XAIX_XOR64(CRYPTO_XVIX_XAIX_MUL64(x0, y1),
                                                     CRYPTO_XVIX_XAIX_MUL64(x1, y0)
                                                    ),
                              CRYPTO_XVIX_XAIX_XOR64(CRYPTO_XVIX_XAIX_MUL64(x2, y3),
                                                     CRYPTO_XVIX_XAIX_MUL64(x3, y2)
                                                    )
                             );
  z2 = CRYPTO_XVIX_XAIX_XOR64(CRYPTO_XVIX_XAIX_XOR64(CRYPTO_XVIX_XAIX_MUL64(x0, y2),
                                                     CRYPTO_XVIX_XAIX_MUL64(x1, y1)
                                                    ),
                              CRYPTO_XVIX_XAIX_XOR64(CRYPTO_XVIX_XAIX_MUL64(x2, y0),
                                                     CRYPTO_XVIX_XAIX_MUL64(x3, y3)
                                                    )
                             );
  z3 = CRYPTO_XVIX_XAIX_XOR64(CRYPTO_XVIX_XAIX_XOR64(CRYPTO_XVIX_XAIX_MUL64(x0, y3),
                                                     CRYPTO_XVIX_XAIX_MUL64(x1, y2)
                                                    ),
                              CRYPTO_XVIX_XAIX_XOR64(CRYPTO_XVIX_XAIX_MUL64(x2, y1),
                                                     CRYPTO_XVIX_XAIX_MUL64(x3, y0)
                                                    )
                             );

  z0 = CRYPTO_XVIX_XAIX_AND64(z0, 0x1111111111111111ULL);
  z1 = CRYPTO_XVIX_XAIX_AND64(z1, 0x2222222222222222ULL);
  z2 = CRYPTO_XVIX_XAIX_AND64(z2, 0x4444444444444444ULL);
  z3 = CRYPTO_XVIX_XAIX_AND64(z3, 0x8888888888888888ULL);

  return CRYPTO_XVIX_XAIX_OR64(CRYPTO_XVIX_XAIX_OR64(z0, z1), CRYPTO_XVIX_XAIX_OR64(z2, z3));
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

/* --- Crypto_xVIx_xAIx_CPr_AEAD_GCMRev64 ------------------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
/* Deviation CODEMETRIC-3 */
static FUNC(uint64, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_AEAD_GCMRev64
(
  uint64 reverseValue
)
{
  uint64 tempreverseValue;

  tempreverseValue = reverseValue;
  /* Deviation MISRAC2012-3 <START> */
  CRYPTO_XVIX_XAIX_INT_CPR_GCM_RMS(tempreverseValue, 0x5555555555555555ULL,  1U);
  CRYPTO_XVIX_XAIX_INT_CPR_GCM_RMS(tempreverseValue, 0x3333333333333333ULL,  2U);
  CRYPTO_XVIX_XAIX_INT_CPR_GCM_RMS(tempreverseValue, 0x0F0F0F0F0F0F0F0FULL,  4U);
  CRYPTO_XVIX_XAIX_INT_CPR_GCM_RMS(tempreverseValue, 0x00FF00FF00FF00FFULL,  8U);
  CRYPTO_XVIX_XAIX_INT_CPR_GCM_RMS(tempreverseValue, 0x0000FFFF0000FFFFULL, 16U);

  return CRYPTO_XVIX_XAIX_OR64(CRYPTO_XVIX_XAIX_SHL64(tempreverseValue, 32U),
                               CRYPTO_XVIX_XAIX_SHR64(tempreverseValue, 32U)
                              );
  /* Deviation MISRAC2012-3 <STOP> */
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle --------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Start2Update,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{

  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  /* create secondary job */
  CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB();
  CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_KEY();
  primitive->P2->data->P1 = primitive;

  /* Calling the secondary primitive START. */
  result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                        &(workspace->secondaryJob),
                                                         workspace->paPrimitive->P2
                                                       );

  if(E_OK == result)
  {
    workspace->AADProcessed                                               = FALSE;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode = CRYPTO_OPERATIONMODE_UPDATE;
    workspace->outputLength                                               = 0U;

    workspace->counter[CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES - 1U] = 1U;

    TS_MemBZero(workspace->tag, CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES);
    workspace->secondaryOutputLength                                                 = CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        = Crypto_xVIx_xAIx_CPr_GCMZeroBlock;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     = CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       = workspace->H;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &workspace->secondaryOutputLength;

    /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_GCM/GENERAL/0008,1 */
    /* Encrypt the block using the secondary primitive UPDATE. This call shall never fail because
     * the key is already proved to be valid in START, and the buffers and their sizes are set
     * to valid values before this call.
     */
    (void) primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                        &(workspace->secondaryJob),
                                                         workspace->paPrimitive->P2
                                                       );

    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr    = workspace->counter;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength = CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr   = workspace->first;
    workspace->secondaryOutputLength                                             = CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES;

    /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_GCM/GENERAL/0009,1 */
    /* Encrypt the block using the secondary primitive UPDATE. This call shall never fail because
     * the key is already proved to be valid in START, and the buffers and their sizes are set to
     * valid values before this call.
     */
    (void) primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                        &(workspace->secondaryJob),
                                                         workspace->paPrimitive->P2
                                                       );
  }

  CRYPTO_XVIX_XAIX_SET_SMRESULT_START(result, sizeof(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType));
  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess------------------------------------ */

/* Crypto.Dsn.JobTransition.Update2Update,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType);

  Std_ReturnType result       = E_NOT_OK;

  /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_GCM/UPDATE/0001,2 */
  workspace->AADLength      =  job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputLength;
  workspace->inputPtr       =  job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr;
  workspace->inputLength    =  job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength;
  workspace->outputPtr      =  job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr;
  workspace->availOutputLen = *job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr;
  *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr) = 0U;

  /* CHECK: NOPARSE
   * The workspace->AADProcessed is set to false by default and also in the previous step its again set
   * to false. So this check will always be true.
   */
  if(FALSE == workspace->AADProcessed)
  {
    /* only once for the Hash AAD */
    workspace->AADProcessed       = TRUE;
    workspace->bytesStoredInBlock = 0U;
    /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_GCM/GENERAL/0003,2 */
    /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_GCM/GENERAL/0011,1 */
    Crypto_xVIx_xAIx_CPr_AEAD_GCMGHashCTMul(workspace->tag,
                                            workspace->H,
                                            job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputPtr,
                                            workspace->AADLength
                                           );

    /* Increment the CTR
     * Part of step 3: inc32(J0)
     */
    /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_GCM/GENERAL/0010,1 */
    Crypto_xVIx_xAIx_CPr_AEAD_GCMInc(workspace->counter);
    workspace->secondaryOutputLength                                                 = CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        = workspace->counter;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     = CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       = workspace->ctrKey;
    workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &workspace->secondaryOutputLength;

    /* call the secondary primitive. */
    result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                          &(workspace->secondaryJob),
                                                           workspace->paPrimitive->P2
                                                         );
    workspace->bytesStoredInBlock = 0U;
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  workspace->notifyResult = CRYPTO_E_BUSY;

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle ----------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Update2Finish,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType);

  CRYPTO_XVIX_XAIX_SET_SMRESULT_UPDATE(workspace->smResult, sizeof(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType));

  return E_OK;
}
#endif /*CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON*/

/* --- Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishProcess ----------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec2FinishProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  if (CRYPTO_OPERATIONMODE_SINGLECALL == job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode)
  {
    job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr    = NULL_PTR;
    job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength = 0U;
  }
  else
  {
    *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr) = 0U;
  }
  if (12U > *job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryOutputLengthPtr)
  {
    /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_GCM/GENERAL/0023,1 */

    result = CRYPTO_E_SMALL_BUFFER;
    /* Deviation TASKING-2 */
    CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH(result, sizeof(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType));
  }
  else
  {
    result = E_OK;
    if (16U < *job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryOutputLengthPtr)
    {
      *job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryOutputLengthPtr = 16U;
    }
  }

  return result;
}
#endif /*CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON*/

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateFinishProcess2Self ----------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateFinishProcess2Self
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType);

  workspace->bytesStoredInBlock = 0U;
  TS_PARAM_UNUSED(job);

  return E_OK;
}
#endif /*CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON*/

/* --- Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle ------------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveCancel2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType);
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
  CRYPTO_XVIX_XAIX_SET_SMRESULT_CANCEL(CRYPTO_E_JOB_CANCELED, sizeof(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishProcess2FinishProcessLastBlock ----------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishProcess2FinishProcessLastBlock
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  if (  (uint32) (workspace->availOutputLen - workspace->bytesStoredInBlock)
      < (uint32) (0xFFFFFFFFUL - workspace->bytesStoredInBlock)
     )
  {
    uint8 encLen[CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES];
    /* check if last block was complete block */
    if (0U != workspace->bytesStoredInBlock)
    {
      /* Input = Ek ^ Output on last partial block */
      Crypto_xVIx_xAIx_CommonXOR(workspace->block,
                                 workspace->ctrKey,
                                 workspace->bytesStoredInBlock
                                );
      /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_GCM/GENERAL/0013,1 */
      /* Copy to output the Output */
      TS_MemCpy(workspace->outputPtr,
                workspace->block,
                workspace->bytesStoredInBlock
               );
      workspace->outputPtr                                              = &(workspace->outputPtr[workspace->bytesStoredInBlock]);
      workspace->outputLength                                          += workspace->bytesStoredInBlock;
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00135,1 */
      *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr) += workspace->bytesStoredInBlock;

      /* Pad the CT with 0^u */
      TS_MemBZero
      (
        &workspace->block[workspace->bytesStoredInBlock],
        (CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES - workspace->bytesStoredInBlock)
      );
     /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_GCM/GENERAL/0011,1 */
      /* Step 5 in GCM algo. Calculate GHASH(C || 0^u) */
      Crypto_xVIx_xAIx_CPr_AEAD_GCMGHashCTMul(workspace->tag,
                                              workspace->H,
                                             workspace->block,
                                              CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES
                                             );
    }
    TS_MemCpy(workspace->block, workspace->tag, CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES);
    TS_MemBZero(encLen, CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES);
    /* Lengths are in bits */
    CRYPTO_XVIX_XAIX_INT_LIB_UINT32_TO_BYTEARRAY(&encLen[ 4U], (workspace->AADLength    * 8U));
    CRYPTO_XVIX_XAIX_INT_LIB_UINT32_TO_BYTEARRAY(&encLen[12U], (workspace->outputLength * 8U));
    /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_GCM/GENERAL/0011,1 */
    /* Step 5 in GCM algo. Calculate GHASH(len(A) || len(C)) */
    Crypto_xVIx_xAIx_CPr_AEAD_GCMGHashCTMul(workspace->tag,
                                            workspace->H,
                                            encLen,
                                            CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES
                                           );
    /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_GCM/GENERAL/0012,1 */
    /* tag is the GHASH output XORed with the encryption of the
     * nonce with the initial counter value.
     */
    Crypto_xVIx_xAIx_CommonXOR(workspace->tag,
                               workspace->first,
                               CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES
                              );
    /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_GCM/GENERAL/0013,1 */
    /* Copy the tag */
    TS_MemCpy(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryOutputPtr,
              workspace->tag,
              *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryOutputLengthPtr)
             );
    result = E_OK;
  }
  else
  {
    /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_GCM/GENERAL/0023,1 */

     result = CRYPTO_E_SMALL_BUFFER;
    /* Deviation TASKING-2 */
    CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH(result, sizeof(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType));
  }
  return result;
}
#endif /*CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON*/

/* --- Crypto_xVIx_xAIx_StateMachine_FinishProcessLastBlock2StartIdle --------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Finish2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishProcessLastBlock2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode = CRYPTO_OPERATIONMODE_FINISH;
  result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                        &(workspace->secondaryJob),
                                                         workspace->paPrimitive->P2
                                                       );

  CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH(result, sizeof(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType));

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateFinishProcess ---------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateFinishProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType);

  Std_ReturnType result  = E_NOT_OK;

  /* Fill the next block to encrypt with input data and, if there is enough data,
   * XOR it with the last encrypted block and start encrypting it.
   */
  if ((workspace->bytesStoredInBlock + workspace->inputLength) >= sizeof(workspace->block))
  {
    if (  (uint32) (workspace->availOutputLen - CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES)
        < (uint32) (0xFFFFFFFFUL              - CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES)
       )
    {
      /* We have enough data to fill a complete block to encrypt and we know that the
       * block will not be the last.
       */
       /* Copy input data to the block until it is full. */
      uint32 newLen = CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES - workspace->bytesStoredInBlock;
      TS_MemCpy(&(workspace->block[workspace->bytesStoredInBlock]),
                workspace->inputPtr,
                newLen
               );
      workspace->bytesStoredInBlock = sizeof(workspace->block);
      /* Skip the bytes we have read in the input data. */
      workspace->inputPtr     = &(workspace->inputPtr[newLen]);
      workspace->inputLength -= newLen;

       /* Output = Ek ^ Input */
      Crypto_xVIx_xAIx_CommonXOR(workspace->block,
                                 workspace->ctrKey,
                                 CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES
                                );
      /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_GCM/GENERAL/0013,1 */
      /* Copy to output the Output */
      TS_MemCpy(workspace->outputPtr,
                workspace->block,
                CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES
               );
      workspace->outputPtr       = &(workspace->outputPtr[CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES]);
      workspace->outputLength   += CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES;
      workspace->availOutputLen -= CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES;
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00135,1 */
      *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr) += CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES;
      /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_GCM/GENERAL/0011,1 */
      Crypto_xVIx_xAIx_CPr_AEAD_GCMGHashCTMul(workspace->tag,
                                              workspace->H,
                                              workspace->block,
                                              CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES
                                             );
      /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_GCM/GENERAL/0006,1 */
      /* Increment the CTR */
      Crypto_xVIx_xAIx_CPr_AEAD_GCMInc(workspace->counter);
      workspace->secondaryOutputLength                                                 = CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        = workspace->counter;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     = CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_BLOCK_LEN_BYTES;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       = workspace->ctrKey;
      workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &workspace->secondaryOutputLength;

      primitive->P2->data->P1 = primitive;
      workspace->notifyResult = CRYPTO_E_BUSY;
      /*call to the secondary primitive shall never fail because all the parameters provided to the
       * secondary primitive are valid.
       */
      (void) primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                          &(workspace->secondaryJob),
                                                           workspace->paPrimitive->P2
                                                         );
      result = CRYPTO_E_BUSY;
    }
    else
    {
      /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_GCM/GENERAL/0023,1 */
      /*error case handling. small buffer*/

      result = CRYPTO_E_SMALL_BUFFER;
      *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr) = workspace->availOutputLen;
      /* Deviation TASKING-2 */
      CRYPTO_XVIX_XAIX_SET_SMRESULT_UPDATE(result, sizeof(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType));
    }
  }
  else
  {
    /* We do not have enough input data to fill a complete block or we do not know
     * whether the block will be the last one.
     */

    /* Copy the rest of the input data to the block. */
    TS_MemCpy(&(workspace->block[workspace->bytesStoredInBlock]),
              workspace->inputPtr,
              workspace->inputLength
             );
    workspace->bytesStoredInBlock += workspace->inputLength;
    /* We are finished with the current update and wait for more input data or the
     * end of the GCM computation.
     */
    result = E_OK;
  }

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_StartProcess ----------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_GCM_WorkspaceType);

         Std_ReturnType                                                           result          = E_NOT_OK;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) counterPtr;
  boolean                                                                         fromPrimitive   = FALSE;

  /* key element is read in the secondary primitive */
  result = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet(job->cryptoKeyId,
                                                     CRYPTO_KE_CIPHER_IV,
                                                     &counterPtr,
                                                     FALSE,
                                                     CRYPTO_XVIX_XAIX_SID_EMPTY
                                                     );

  if(E_OK == result)
  {
    fromPrimitive = TRUE;
    /* Deviation TASKING-1 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(result, counterPtr, fromPrimitive);
    if (E_OK == result)
    {
      /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_GCM/GENERAL/0004,1 */
      if (CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_GCM_IV_LEN_BYTES != counterPtr->data->size)
      {
        workspace->smResult         = CRYPTO_E_KEY_SIZE_MISMATCH;
        workspace->smOperationDone |= CRYPTO_OPERATIONMODE_START;
        result                      = E_NOT_OK;
      }
      else
      {
        TS_MemCpy(workspace->counter, counterPtr->data->data, counterPtr->data->size);
        result = E_OK;
      }
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(counterPtr);
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_GCM == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[end of file]=================================================================*/

