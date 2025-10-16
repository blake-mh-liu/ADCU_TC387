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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_AEADENCRYPT_AES_CCM.c/0001,1 */

/*==================[deviations]==================================================================*/

/*
 * MISRA-C:2012 Deviation List
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
 */

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int.h>                              /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_AEADENCRYPT_AES_CCM.c/0002,1 */
#include <Crypto_xVIx_xAIx_Int_KeyManagement.h>                /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_AEADENCRYPT_AES_CCM.c/0003,1 */
#include <Crypto_xVIx_xAIx_Int_CPr_AEADENCRYPT_AES_CCM.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_AEADENCRYPT_AES_CCM.c/0004,1 */

/*==================[macros]======================================================================*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT,1 */
#if (defined CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT)
#error CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT already defined
#endif
/** \brief  Number of entries in the primitives state transition table. **/
#define CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT 10U

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

#if (defined CRYPTO_XVIX_XAIX_STATE_PROCESS_IDLE)
#error CRYPTO_XVIX_XAIX_STATE_PROCESS_IDLE already defined
#endif
/** \brief  The process Idle state **/
#define CRYPTO_XVIX_XAIX_STATE_PROCESS_IDLE 0U

#if (defined CRYPTO_XVIX_XAIX_STATE_PROCESS_MAC_B0)
#error CRYPTO_XVIX_XAIX_STATE_PROCESS_MAC_B0 already defined
#endif
/** \brief  The process Mac B0 state. **/
#define CRYPTO_XVIX_XAIX_STATE_PROCESS_MAC_B0 1U

#if (defined CRYPTO_XVIX_XAIX_STATE_PROCESS_MAC_ADATA)
#error CRYPTO_XVIX_XAIX_STATE_PROCESS_MAC_ADATA already defined
#endif
/** \brief  The process Mac Associate Data state. **/
#define CRYPTO_XVIX_XAIX_STATE_PROCESS_MAC_ADATA 2U

#if (defined CRYPTO_XVIX_XAIX_STATE_PROCESS_MAC_MSG)
#error CRYPTO_XVIX_XAIX_STATE_PROCESS_MAC_ADATA already defined
#endif
/** \brief  The process Mac Message state. **/
#define CRYPTO_XVIX_XAIX_STATE_PROCESS_MAC_MSG 3U

#if (defined CRYPTO_XVIX_XAIX_STATE_PROCESS_AEADENCRYPT_AES_CCM_MSG)
#error CRYPTO_XVIX_XAIX_STATE_PROCESS_AEADENCRYPT_AES_CCM_MSG already defined
#endif
/** \brief  The process AEADENCRYPT_AES_CCM state. **/
#define CRYPTO_XVIX_XAIX_STATE_PROCESS_AEADENCRYPT_AES_CCM_MSG 4U

#if (defined CRYPTO_XVIX_XAIX_STATE_PROCESS_FINISH)
#error CRYPTO_XVIX_XAIX_STATE_PROCESS_FINISH already defined
#endif
/** \brief  The process finish state. **/
#define CRYPTO_XVIX_XAIX_STATE_PROCESS_FINISH 5U

#if (defined CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_ENCODELEN_THRESHOLD)
#error CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_ENCODELEN_THRESHOLD already defined
#endif
/** \brief  The encode length threshold. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_ENCODELEN_THRESHOLD  65280U /* 2^16 - 2^8*/

#if (defined CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_NOUNCE_SIZE_MIN)
#error CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_NOUNCE_SIZE_MIN already defined
#endif
/** \brief  The minimum nounce size in bytes. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_NOUNCE_SIZE_MIN  7U

#if (defined CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_NOUNCE_SIZE_MAX)
#error CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_NOUNCE_SIZE_MAX already defined
#endif
/** \brief  The maximum nounce size in bytes. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_NOUNCE_SIZE_MAX  13U

#if (defined CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_ADATA_ENCODELEN_2BYTES)
#error CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_ADATA_ENCODELEN_2BYTES already defined
#endif
/** \brief  The 2 bytes encode len for Associate Data. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_ADATA_ENCODELEN_2BYTES  2U

#if (defined CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_ADATA_ENCODELEN_6BYTES)
#error CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_ADATA_ENCODELEN_6BYTES already defined
#endif
/** \brief  The 6 bytes encode len for Associate Data. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_ADATA_ENCODELEN_6BYTES  6U

#if (defined CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_ADATA_BYTESIZE_MAX)
#error CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_ADATA_BYTESIZE_MAX already defined
#endif
/** \brief  The maximum Associate Data length in bytes. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_ADATA_BYTESIZE_MAX  4U

#if (defined CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_MSG_BYTESIZE_MAX)
#error CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_MSG_BYTESIZE_MAX already defined
#endif
/** \brief  The maximum Payload length in bytes. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_MSG_BYTESIZE_MAX  4U

#if (defined CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_ENCODE_MAC_INDEX)
#error CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_ENCODE_MAC_INDEX already defined
#endif
/** \brief  The encode Max LSB index in Flag byte. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_ENCODE_MAC_INDEX  3U

#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(boolean, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetNextState
(
  P2VAR(uint8,                                         AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) smStateIndx,
        Crypto_xVIx_xAIx_PrimitiveStateIdentifierType                                         curState,
        Std_ReturnType                                                                        resultAction,
        Crypto_ProcessingType                                                                 jobProcessing,
  P2VAR(Crypto_xVIx_xAIx_PrimitiveStateIdentifierType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) nxtState
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */
/* ---state action functions--------------------------------------------------------------------- */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateFinishProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/** \brief  State action function for states
 **         'CRYPTO_XVIX_XAIX_STATE_FINISHEXEC'
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExecProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

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
 ** \retval  E_OK      Request successful.
 ** \retval  E_NOT_OK  Request failed.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

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
 ** \retval  E_OK      Request successful.
 ** \retval  E_NOT_OK  Request failed.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/* ---misc procedures---------------------------------------------------------------------------- */

/** \brief  AEADENCRYPT_AES_CCM MAC B0 process
 **
 ** Process AEADENCRYPT_AES_CCM MAC B0 and return the error.
 **
 ** \param[in]      associatedDataLength  Associate Data Length.
 ** \param[in]      msgLength             Message Length
 ** \param[in]      primitive             Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  CRYPTO_E_BUSY  Process is on going.
 ** \retval  E_NOT_OK       Process is failed.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_Mac_B0Process
(
          uint32                                                                    associatedDataLength,
          uint32                                                                    msgLength,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/** \brief  AEADENCRYPT_AES_CCM MAC Associate Data process
 **
 ** Process AEADENCRYPT_AES_CCM MAC Associate Data process and return the error.
 **
 ** \param[in]      associatedDataLength  Associate Data Length.
 ** \param[in]      associatedDataPtr     Associate Data Pointer
 ** \param[in]      primitive             Pointer to the data structure describes the current primitive.
 **
 ** \returns  void.
 **
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_Mac_AsscDataProcess
(
          uint32                                                                    associatedDataLength,
  P2CONST(uint8,                             AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) associatedDataPtr,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/** \brief  AEADENCRYPT_AES_CCM MAC Message process
 **
 ** Process AEADENCRYPT_AES_CCM MAC Message and return the error.
 **
 ** \param[in]      msgLength  Message Length.
 ** \param[in]      msgDataPtr Message Data Pointer
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  CRYPTO_E_BUSY  Process is on going.
 ** \retval  E_OK           Process is finished.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_Mac_MsgProcess
(
          uint32                                                                    msgLength,
  P2CONST(uint8,                             AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) msgDataPtr,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/** \brief  AEADENCRYPT_AES_CCM Message process
 **
 ** Process AEADENCRYPT_AES_CCM Message and return the error.
 **
 ** \param[in]      msgLength            Message Length.
 ** \param[in]      msgDataPtr           Message Data Pointer
 ** \param[out]     outputDataPtr        Ouput Data Buffer Pointer
 ** \param[out]     outputDataLengthPtr  Output Data Lenght Pointer
 ** \param[in]      primitive            Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  CRYPTO_E_BUSY  Process is on going.
 ** \retval  E_OK           Process is finished.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_MsgProcess
(
          uint32                                                                    msgLength,
  P2CONST(uint8,                             AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) msgDataPtr,
    P2VAR(uint8,                             AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) outputDataPtr,
    P2VAR(uint32,                            AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) outputDataLengthPtr,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/** \brief  AEADENCRYPT_AES_CCM Second Primitive Process
 **
 ** Process AEADENCRYPT_AES_CCM Second Primitive.
 **
 ** \param[in]      inputDataPtr  Input Data Buffer Pointer
 ** \param[out]     outputDataPtr Ouput Data Buffer Pointer
 ** \param[in]      primitive     Pointer to the data structure describes the current primitive.
 **
 ** \returns  None.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_SecondPrimitiveUpdateProcess
(
  P2CONST(uint8,                             AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) inputDataPtr,
    P2VAR(uint8,                             AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) outputDataPtr,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/** \brief  Avaliable Data Copy Len to current buffer
 **
 ** Check and return available data copy len in current buffer.
 **
 ** \param[in]  dataLength  The data length.
 ** \param[in]  availableBuffLen  The available buffer length.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_DataCopyLen
(
  uint32  dataLength,
  uint8   availableBuffLen
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/** \brief  Increment the IV.
 **
 ** Increments the IV stored in a 16 Byte array.
 **
 ** \param[in]  IV  The initialization vector.
 ** \param[in]  IV_Index  The initialization vector size index.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous/Asynchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_CCMInc
(
  P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) IV,
        uint8                                         IV_Index
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal constants]==========================================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  The primitives state transition table. **/

/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_StateTransitionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateTransitionType, CRYPTO_xVIx_xAIx_CONST)
Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Process_StateTransitionTable[CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT] =
{
  { NULL_PTR,                                                           CRYPTO_XVIX_XAIX_STATE_STARTIDLE,              CRYPTO_XVIX_XAIX_STATE_STARTIDLE,              CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE_TO_CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1               */
  { Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle,                 CRYPTO_XVIX_XAIX_STATE_STARTEXEC,              CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,             CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { Crypto_xVIx_xAIx_StateMachine_FinishExec2StartIdle,                 CRYPTO_XVIX_XAIX_STATE_FINISHEXEC,             CRYPTO_XVIX_XAIX_STATE_STARTIDLE,              CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { NULL_PTR,                                                           CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,             CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,             CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE_TO_CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE/0001,1             */
  { Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess,             CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC,             CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,          CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { NULL_PTR,                                                           CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,          CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,          CRYPTO_XVIX_XAIX_PROCESSING_BOTH, CRYPTO_E_BUSY },
  { Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle,       CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,          CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,       CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { NULL_PTR,                                                           CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,       CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,       CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE_TO_CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE/0001,1 */

  { Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle,                     CRYPTO_XVIX_XAIX_STATE_CANCEL,                 CRYPTO_XVIX_XAIX_STATE_STARTIDLE,              CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { Crypto_xVIx_xAIx_StateMachine_Error2StartIdle,                      CRYPTO_XVIX_XAIX_STATE_ERROR,                  CRYPTO_XVIX_XAIX_STATE_STARTIDLE,              CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          }
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/** \brief  The primitives state action table. **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_StateActionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateActionType, CRYPTO_xVIx_xAIx_CONST)
Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Process_StateActionTable[CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT] =
{
  /* CRYPTO_XVIX_XAIX_STATE_STARTIDLE              */ { NULL_PTR                                          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1        */
  /* CRYPTO_XVIX_XAIX_STATE_STARTEXEC              */ { Crypto_xVIx_xAIx_StateMachine_StartProcess        }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTEXEC/0001,1        */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE             */ { NULL_PTR                                          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC             */ { NULL_PTR                                          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS          */ { Crypto_xVIx_xAIx_StateMachine_UpdateFinishProcess },
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE       */ { NULL_PTR                                          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE/0001,1 */
  /* CRYPTO_XVIX_XAIX_STATE_FINISHEXEC             */ { Crypto_xVIx_xAIx_StateMachine_FinishExecProcess   }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_FINISHEXEC/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_CANCEL                 */ { NULL_PTR                                          },
  /* CRYPTO_XVIX_XAIX_STATE_ERROR                  */ { NULL_PTR                                          },
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Process -------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Process/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Process
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType);

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
    (void) Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Reset(workspace->paObjectId, job, primitive);
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
        (void) Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Main(objectId, job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Main ----------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Main/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Main
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType);

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
    if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Process_StateActionTable[curState].fcnAction))
    {
      resultAction = Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Process_StateActionTable[curState].fcnAction(job, primitive);
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
      if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Process_StateTransitionTable[smStateIndx].fcnTransition))
      {
        /* transition function returns using workspace->smResult */
        (void) Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Process_StateTransitionTable[smStateIndx].fcnTransition(job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Cancel --------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Cancel/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Cancel
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType);

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
      (void) Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Main(objectId, job, primitive);
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Reset ---------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Reset/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Reset
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as
   * secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESET(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType));
    result = E_OK;
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Restart ---------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Restart/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Restart
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESTART(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType));
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Callback ------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Callback/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType);

  TS_PARAM_UNUSED(objectId);
  TS_PARAM_UNUSED(job);
  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Callback/0002,1 */
  workspace->notifyType   = cbkType;
  workspace->notifyResult = cbkResult;

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_StateMachine_Error2StartIdle ----------------------------------------------*/

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveError2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType);

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
  result              = Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Reset(workspace->paObjectId, job, primitive);
  workspace->smResult = smResult;

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/*--- Crypto_xVIx_xAIx_GetNextState --------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
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
    if (   (Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx   = i;
      break;
    }
  }

  /* 2) iterate from first table entry to last found entry in table */
  for (i = 0U; (FALSE == nxtStateFound) && (i < *smStateIndx); i++)
  {
    if (   (Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx  = i;
      break;
    }
  }

  return nxtStateFound;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */
/* --- Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_CCMGHashCTMul -------------------------------------------------- */

/* --- Crypto_xVIx_xAIx_Procedure_CCMInc --------------------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_CCMInc
(
  P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) IV,
        uint8                                         IV_Index
)
{
  uint8 i;

  /* CHECK: NOPARSE
   * The for loop has a fixed condition which cannot fail at the start, also the IV is always
   * initialized in the beginning which results in the if condition to be always true.
   */
  for (i  = CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_BLOCK_LEN_BYTES;
       i != IV_Index;
       i--
      )
  {
    ++IV[i - 1U];

    if ( 0x00U != IV[i - 1U])
    {
      break;
    }
  }
  /* CHECK: PARSE */

}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle --------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Start2Update,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{

  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType);

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

  CRYPTO_XVIX_XAIX_SET_SMRESULT_START(result, sizeof(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType));
  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess------------------------------------ */

/* Crypto.Dsn.JobTransition.Update2Update,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType);

  Std_ReturnType result  = E_NOT_OK;

  if (CRYPTO_XVIX_XAIX_STATE_PROCESS_IDLE == workspace->currProcessState)
  {
    if (job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength > *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr))
    {
      /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_CCM/UPDATE/0001,1 */

      result = CRYPTO_E_SMALL_BUFFER;
      /* Deviation TASKING-2 */
      CRYPTO_XVIX_XAIX_SET_SMRESULT_UPDATE(result, sizeof(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType));
    }
    else
    {
      *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr) = 0U;

      workspace->currProcessState = CRYPTO_XVIX_XAIX_STATE_PROCESS_MAC_B0;

      result = E_OK;

      workspace->notifyResult = CRYPTO_E_BUSY;
    }
  }
  else
  {
    /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_CCM/UPDATE/0003,1 */
    /* Only 1 single UPDATE call is allowed*/
    workspace->smResult = E_NOT_OK;
  }

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle ----------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Update2Finish,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType);

  CRYPTO_XVIX_XAIX_SET_SMRESULT_UPDATE(workspace->smResult, sizeof(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType));

  return E_OK;
}
#endif /*CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON*/

/* --- Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle ------------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveCancel2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType);
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
  CRYPTO_XVIX_XAIX_SET_SMRESULT_CANCEL(CRYPTO_E_JOB_CANCELED, sizeof(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateFinishProcess ---------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateFinishProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  switch (workspace->currProcessState)
  {
    case CRYPTO_XVIX_XAIX_STATE_PROCESS_MAC_B0:
    {
      result = Crypto_xVIx_xAIx_Procedure_Mac_B0Process(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputLength,
                                                     job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength,
                                                     primitive
                                                    );
      break;
    }
    case CRYPTO_XVIX_XAIX_STATE_PROCESS_MAC_ADATA:
    {
      result = CRYPTO_E_BUSY;
      Crypto_xVIx_xAIx_Procedure_Mac_AsscDataProcess(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputLength,
                                                 job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryInputPtr,
                                                 primitive
                                                );
      break;
    }
    case CRYPTO_XVIX_XAIX_STATE_PROCESS_MAC_MSG:
    {
      result = Crypto_xVIx_xAIx_Procedure_Mac_MsgProcess(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength,
                                                      job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr,
                                                      primitive
                                                      );
      break;
    }
    case CRYPTO_XVIX_XAIX_STATE_PROCESS_AEADENCRYPT_AES_CCM_MSG:
    {
      result = Crypto_xVIx_xAIx_Procedure_MsgProcess(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength,
                                                  job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr,
                                                  job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr,
                                                  job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr,
                                                  primitive
                                                  );
      break;
    }
    /* CHECK: NOPARSE */
    /* All the possible internal procedures necessary for the algorithm have been addressed in the cases above.*/
    default:
    {
      /* Nothing to do (MISRA) */
      break;
    }
    /* CHECK: PARSE */
  }
  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_StartProcess ----------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType);

  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) counterPtr    = NULL_PTR;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) macLenPtr     = NULL_PTR;
  Std_ReturnType                                                                  result        = E_NOT_OK;
  boolean                                                                         fromPrimitive = FALSE;

  /* key mac len element read */
  result = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet(job->cryptoKeyId,
                                                     CRYPTO_XVIX_XAIX_KE_CCM_MAC_LEN,
                                                     &macLenPtr,
                                                     FALSE,
                                                     CRYPTO_XVIX_XAIX_SID_EMPTY
                                                     );
  if(E_OK == result)
  {
    fromPrimitive = TRUE;
    /* Deviation TASKING-1 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(result, macLenPtr, fromPrimitive);
    if (E_OK == result)
    {
      workspace->macLen = macLenPtr->data->data[0U];

      if (   ( 4U != workspace->macLen)
          && ( 6U != workspace->macLen)
          && ( 8U != workspace->macLen)
          && (10U != workspace->macLen)
          && (12U != workspace->macLen)
          && (14U != workspace->macLen)
          && (16U != workspace->macLen)
        )
      {
        /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_CCM/START/0002,1 */
        workspace->smResult         = CRYPTO_E_KEY_SIZE_MISMATCH;
        workspace->smOperationDone |= CRYPTO_OPERATIONMODE_START;
        result                      = E_NOT_OK;
      }
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(macLenPtr);
    }
    else
    {
      workspace->smResult         = result;
      workspace->smOperationDone |= CRYPTO_OPERATIONMODE_START;
    }
  }

  if(E_OK == result)
  {
    /* key element is read in the secondary primitive */
    result = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet(job->cryptoKeyId,
                                                      CRYPTO_KE_CIPHER_IV,
                                                      &counterPtr,
                                                      FALSE,
                                                      CRYPTO_XVIX_XAIX_SID_EMPTY
                                                      );
  }

  if (E_OK == result)
  {
    fromPrimitive = TRUE;
    /* Deviation TASKING-1 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(result, counterPtr, fromPrimitive);
    if (E_OK == result)
    {
      if (   (CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_NOUNCE_SIZE_MIN > counterPtr->data->size)
          || (CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_NOUNCE_SIZE_MAX < counterPtr->data->size)
         )
      {
        /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_CCM/START/0004,1 */
        workspace->smResult         = CRYPTO_E_KEY_SIZE_MISMATCH;
        workspace->smOperationDone |= CRYPTO_OPERATIONMODE_START;
        result                      = E_NOT_OK;
      }
      else
      {
        workspace->nounceSize = (uint8)(counterPtr->data->size);
        /* AES CCM Ctr0 Update*/
        TS_MemBZero(workspace->Ctr, CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_BLOCK_LEN_BYTES);
        workspace->Ctr[0U] = (uint8)(15U - workspace->nounceSize - 1U);
        TS_MemCpy(&workspace->Ctr[1U], counterPtr->data->data, counterPtr->data->size);

        workspace->currProcessState = CRYPTO_XVIX_XAIX_STATE_PROCESS_IDLE;
        workspace->currentDataProcessIndex = 0U;

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
    if( workspace->smResult  != CRYPTO_E_KEY_SIZE_MISMATCH)
      {
        /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_CCM/START/0001,1 */
        /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_CCM/START/0003,1 */
         workspace->smResult  = E_NOT_OK;
      }
    workspace->smOperationDone |= CRYPTO_OPERATIONMODE_START;
    result                      = E_NOT_OK;
  }

 return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishExecProcess ---------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExecProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_CCM/FINISH/0001,1 */
  if (CRYPTO_OPERATIONMODE_SINGLECALL == job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode)
  {
    job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr    = NULL_PTR;
    job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength = 0U;
  }
  else
  {
    *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr) = 0U;
  }
  /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_CCM/FINISH/0002,1 */
  if (workspace->macLen > *job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryOutputLengthPtr)
  {

    result = CRYPTO_E_SMALL_BUFFER;

    /* Deviation TASKING-2 */
    CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH(result, sizeof(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType));
  }
  else
  {
    /* Copy the tag */
    TS_MemCpy(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryOutputPtr,
              workspace->T,
              workspace->macLen
              );
    *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.secondaryOutputLengthPtr) = workspace->macLen;
    TS_MemBZero(workspace->T, CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_BLOCK_LEN_BYTES);

    result = E_OK;
  }

  return result;
}
#endif /*CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON*/

/* --- Crypto_xVIx_xAIx_StateMachine_FinishExec2StartIdle ---------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType);

  Std_ReturnType result  = E_NOT_OK;

  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode = CRYPTO_OPERATIONMODE_FINISH;

  result = primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                        &(workspace->secondaryJob),
                                                         workspace->paPrimitive->P2
                                                       );

  CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH(result, sizeof(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType));

  return result;
}
#endif /*CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON*/

/* --- Crypto_xVIx_xAIx_Procedure_Mac_B0Process ---------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_Mac_B0Process
(
          uint32                                                                    associatedDataLength,
          uint32                                                                    msgLength,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType);

  uint8          index   = 0U;
  uint8          msgSize = CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_MSG_BYTESIZE_MAX;
  uint8          Q[CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_MSG_BYTESIZE_MAX] = {0U};
  uint8          B0[CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_BLOCK_LEN_BYTES] = {0U};

  Std_ReturnType result = E_NOT_OK;

  if (0U != associatedDataLength)
  {
    /* Assign the associated data bit index in flagbyte with value 1 */
    B0[0U] = 0x40U;
  }
  else
  {
    /* Assign the associated data bit index in flagbyte with value 0 */
    B0[0U] = 0x00U;
  }
  B0[0U] |= (uint8)(((workspace->macLen - 2U)/2U) << CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_ENCODE_MAC_INDEX);
  B0[0U] |= (uint8)(15U - workspace->nounceSize - 1U);
  TS_MemCpy(&B0[1U], &workspace->Ctr[1U], workspace->nounceSize);

  CRYPTO_XVIX_XAIX_INT_LIB_UINT32_TO_BYTEARRAY(Q, msgLength);

  /* CHECK: NOPARSE */
  /*The FOR loop condition can not fail, as the minimum input length is 1. As a result index will never reach the value CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_MSG_BYTESIZE_MAX*/
  for (index = 0U; index < CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_MSG_BYTESIZE_MAX; index++)
  /* CHECK: PARSE */
  {
    if (Q[index] != 0U)
    {
      break;
    }
    else
    {
      msgSize--;
    }
  }

  if ((workspace->nounceSize + msgSize) <= 15U)
  {
    TS_MemCpy(&B0[CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_BLOCK_LEN_BYTES - msgSize], &Q[CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_MSG_BYTESIZE_MAX - msgSize], msgSize);
    TS_MemCpy(workspace->Block, B0, CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_BLOCK_LEN_BYTES);

    Crypto_xVIx_xAIx_Procedure_SecondPrimitiveUpdateProcess(workspace->Block,
                                                         workspace->T,
                                                         primitive
                                                        );

    workspace->currentDataProcessIndex = 0U;

    workspace->currProcessState = CRYPTO_XVIX_XAIX_STATE_PROCESS_MAC_ADATA;

    result = CRYPTO_E_BUSY;
  }
  else
  {
    /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_CCM/UPDATE/0002,1 */
    /* Invalid Message Length*/
    workspace->smResult = E_NOT_OK;
  }
  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/* --- Crypto_xVIx_xAIx_Procedure_Mac_AsscDataProcess ---------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_Mac_AsscDataProcess
(
          uint32                                                                    associatedDataLength,
  P2CONST(uint8,                             AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) associatedDataPtr,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType);

  uint8  dataBlocBuff[CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_BLOCK_LEN_BYTES]         = {0U};
  uint8  encodeLenBuff[CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_ADATA_ENCODELEN_6BYTES] = {0U};
  uint8  assDataLenBuff[CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_ADATA_BYTESIZE_MAX]    = {0U};
  uint8  availableBuffLen = CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_BLOCK_LEN_BYTES;
  uint8  encodeLen        = 0U;
  uint8  copyDataLen      = 0U;

  /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_CCM/UPDATE/0004,1 */
  if (0U != associatedDataLength)
  {
    if (0U == workspace->currentDataProcessIndex)
    {
      CRYPTO_XVIX_XAIX_INT_LIB_UINT32_TO_BYTEARRAY(assDataLenBuff, associatedDataLength);

      /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_CCM/UPDATE/0005,1 */
      if (associatedDataLength < CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_ENCODELEN_THRESHOLD)
      {
        encodeLen = CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_ADATA_ENCODELEN_2BYTES;
        TS_MemCpy(&encodeLenBuff, &assDataLenBuff[2U], CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_ADATA_ENCODELEN_2BYTES);
      }
      else
      {
        encodeLen = CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_ADATA_ENCODELEN_6BYTES;
        /* Assign first two octets with appropriate bytes according to length encoding convention, followed by actual associatedDataLength value */
        encodeLenBuff[0U] = 0xFFU;
        encodeLenBuff[1U] = 0xFEU;
        TS_MemCpy(&encodeLenBuff[2U], assDataLenBuff, CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_ADATA_BYTESIZE_MAX);
      }
      TS_MemCpy(dataBlocBuff, encodeLenBuff, encodeLen);

      availableBuffLen = CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_BLOCK_LEN_BYTES - encodeLen;
    }

    copyDataLen = (uint8)Crypto_xVIx_xAIx_Procedure_DataCopyLen(associatedDataLength - workspace->currentDataProcessIndex, availableBuffLen);
    TS_MemCpy(&dataBlocBuff[encodeLen], &associatedDataPtr[workspace->currentDataProcessIndex], copyDataLen);
    workspace->currentDataProcessIndex += copyDataLen;

    Crypto_xVIx_xAIx_CommonXOR(dataBlocBuff, workspace->T, CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_BLOCK_LEN_BYTES);

    TS_MemCpy(workspace->Block, dataBlocBuff, CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_BLOCK_LEN_BYTES);

    Crypto_xVIx_xAIx_Procedure_SecondPrimitiveUpdateProcess(workspace->Block,
                                                           workspace->T,
                                                           primitive
                                                          );

    if(workspace->currentDataProcessIndex >= associatedDataLength)
    {
      workspace->currentDataProcessIndex = 0U;
      workspace->currProcessState = CRYPTO_XVIX_XAIX_STATE_PROCESS_MAC_MSG;
    }
  }
  else
  {
    /* !LINKSTO Crypto.Req.CPr/AEADENCRYPT_AES_CCM/UPDATE/0006,1 */
    workspace->currProcessState = CRYPTO_XVIX_XAIX_STATE_PROCESS_MAC_MSG;
  }
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/* --- Crypto_xVIx_xAIx_Procedure_Mac_MsgProcess ---------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_Mac_MsgProcess
(
          uint32                                                                    msgLength,
  P2CONST(uint8,                             AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) msgDataPtr,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType);

  uint8  availableBuffLen = CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_BLOCK_LEN_BYTES;
  uint8  copyDataLen      = 0U;
  uint8  dataBlocBuff[CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_BLOCK_LEN_BYTES] = {0U};

  Std_ReturnType result = CRYPTO_E_BUSY;

  copyDataLen = (uint8)Crypto_xVIx_xAIx_Procedure_DataCopyLen(msgLength - workspace->currentDataProcessIndex, availableBuffLen);

  TS_MemCpy(dataBlocBuff, &msgDataPtr[workspace->currentDataProcessIndex], copyDataLen);

  workspace->currentDataProcessIndex += copyDataLen;

  Crypto_xVIx_xAIx_CommonXOR(dataBlocBuff, workspace->T, CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_BLOCK_LEN_BYTES);

  TS_MemCpy(workspace->Block, dataBlocBuff, CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_BLOCK_LEN_BYTES);

  Crypto_xVIx_xAIx_Procedure_SecondPrimitiveUpdateProcess(workspace->Block,
                                                       workspace->T,
                                                       primitive
                                                       );

  if(workspace->currentDataProcessIndex >= msgLength)
  {
    workspace->currentDataProcessIndex = 0U;

   Crypto_xVIx_xAIx_Procedure_SecondPrimitiveUpdateProcess(
                                                        workspace->Ctr,
                                                        workspace->Block,
                                                        primitive
                                                        );

    Crypto_xVIx_xAIx_CommonXOR(workspace->T, workspace->Block, CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_BLOCK_LEN_BYTES);

    workspace->currProcessState = CRYPTO_XVIX_XAIX_STATE_PROCESS_AEADENCRYPT_AES_CCM_MSG;

    Crypto_xVIx_xAIx_Procedure_CCMInc(workspace->Ctr, workspace->nounceSize + 1U);
  }
  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/* --- Crypto_xVIx_xAIx_Procedure_MsgProcess ---------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_MsgProcess
(
          uint32                                                                    msgLength,
  P2CONST(uint8,                             AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) msgDataPtr,
    P2VAR(uint8,                             AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) outputDataPtr,
    P2VAR(uint32,                            AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) outputDataLengthPtr,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType);

  uint8  availableBuffLen = CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_BLOCK_LEN_BYTES;
  uint8  copyDataLen      = 0U;
  uint8  dataBlocBuff[CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_BLOCK_LEN_BYTES] = {0U};

  Std_ReturnType result = E_NOT_OK;

  Crypto_xVIx_xAIx_Procedure_SecondPrimitiveUpdateProcess(workspace->Ctr,
                                                       workspace->Block,
                                                       primitive
                                                       );

  copyDataLen = (uint8)Crypto_xVIx_xAIx_Procedure_DataCopyLen(msgLength - workspace->currentDataProcessIndex, availableBuffLen);

  TS_MemCpy(dataBlocBuff, &msgDataPtr[workspace->currentDataProcessIndex], copyDataLen);

  Crypto_xVIx_xAIx_CommonXOR(dataBlocBuff, workspace->Block, CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_BLOCK_LEN_BYTES);

  TS_MemCpy(&outputDataPtr[workspace->currentDataProcessIndex], dataBlocBuff, copyDataLen);

  workspace->currentDataProcessIndex += copyDataLen;

  if(workspace->currentDataProcessIndex >= msgLength)
  {
    *(outputDataLengthPtr) = workspace->currentDataProcessIndex;
    workspace->currentDataProcessIndex = 0U;
    workspace->currProcessState        = CRYPTO_XVIX_XAIX_STATE_PROCESS_FINISH;
    result = E_OK;
  }
  else
  {
    Crypto_xVIx_xAIx_Procedure_CCMInc(workspace->Ctr, workspace->nounceSize + 1U);
    result = CRYPTO_E_BUSY;
  }
  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/* --- Crypto_xVIx_xAIx_Procedure_SecondPrimitiveUpdateProcess ---------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_SecondPrimitiveUpdateProcess
(
  P2CONST(uint8,                             AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) inputDataPtr,
    P2VAR(uint8,                             AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) outputDataPtr,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_AEADENCRYPT_AES_CCM_WorkspaceType);

  workspace->secondaryOutputLength = CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_BLOCK_LEN_BYTES;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode            = CRYPTO_OPERATIONMODE_UPDATE;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &workspace->secondaryOutputLength;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        = inputDataPtr;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     = CRYPTO_XVIX_XAIX_INT_CPR_AEADENCRYPT_AES_CCM_BLOCK_LEN_BYTES;
  workspace->secondaryJob.CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       = outputDataPtr;

  /* Encrypt the block using the secondary primitive UPDATE. This call shall never fail because
   * the key is already proved to be valid in START, and the buffers and their sizes are set to
   * valid values before this call.
   */
  (void) primitive->P2->cnfg->description->fcnProcess( workspace->paObjectId,
                                                      &(workspace->secondaryJob),
                                                       workspace->paPrimitive->P2
                                                     );
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

/* --- Crypto_xVIx_xAIx_Procedure_DataCopyLen ---------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON)
static FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Procedure_DataCopyLen
(
  uint32 dataLength,
  uint8  availableBuffLen
)
{
  uint32 retVal = dataLength;

  if (dataLength >= availableBuffLen)
  {
    retVal = availableBuffLen;
  }

  return retVal;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_AEADENCRYPT_AES_CCM == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[end of file]=================================================================*/

