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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_HASH_SHA3224_NOTSET.c/0001,1 */

/*==================[deviations]==================================================================*/

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * False positive from the tasking compiler.
 */

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int.h>                              /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_HASH_SHA3224_NOTSET.c/0002,1 */
#include <Crypto_xVIx_xAIx_Int_KeyManagement.h>                /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_HASH_SHA3224_NOTSET.c/0003,1 */
#include <Crypto_xVIx_xAIx_Int_CPr_HASH_SHA3224_NOTSET.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_HASH_SHA3224_NOTSET.c/0004,1 */

/*==================[macros]======================================================================*/

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

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHPADDING)
#error CRYPTO_XVIX_XAIX_STATE_FINISHPADDING already defined
#endif
/** \brief  The FinishPadding state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHPADDING 7U

#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHSQUEEZE)
#error CRYPTO_XVIX_XAIX_STATE_FINISHSQUEEZE already defined
#endif
/** \brief  The FinishSqueeze state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHSQUEEZE 8U

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

/* !LINKSTO Crypto.Req.CPr/HASH_SHA3224_NOTSET/GENERAL/0011,1 */
#if (defined CRYPTO_XVIX_XAIX_SHA3_KECCAK_SUFFIX_AND_FIRST_PADDING_BIT)
#error CRYPTO_XVIX_XAIX_SHA3_KECCAK_SUFFIX_AND_FIRST_PADDING_BIT is already defined
#endif
/** \brief SHA-3: The domain separation suffix and the first bit of the padding */
#define CRYPTO_XVIX_XAIX_SHA3_KECCAK_SUFFIX_AND_FIRST_PADDING_BIT 0x06U

/* !LINKSTO Crypto.Req.CPr/HASH_SHA3224_NOTSET/GENERAL/0012,1 */
#if (defined CRYPTO_XVIX_XAIX_SHA3_KECCAK_FINAL_PADDING_BIT)
#error CRYPTO_XVIX_XAIX_SHA3_KECCAK_FINAL_PADDING_BIT is already defined
#endif
/** \brief SHA-3: The final padding bit */
#define CRYPTO_XVIX_XAIX_SHA3_KECCAK_FINAL_PADDING_BIT 0x80U

/* !LINKSTO Crypto.Req.CPr/HASH_SHA3224_NOTSET/GENERAL/0020,1 */
#if (defined CRYPTO_XVIX_XAIX_X_COORDINATE_INDEX)
#error CRYPTO_XVIX_XAIX_X_COORDINATE_INDEX is already defined
#endif
/** \brief The index for the x coordinate of the state array */
#define CRYPTO_XVIX_XAIX_X_COORDINATE_INDEX 5U

/* !LINKSTO Crypto.Req.CPr/HASH_SHA3224_NOTSET/GENERAL/0021,1 */
#if (defined CRYPTO_XVIX_XAIX_Y_COORDINATE_INDEX)
#error CRYPTO_XVIX_XAIX_Y_COORDINATE_INDEX is already defined
#endif
/** \brief The index for the y coordinate of the state array */
#define CRYPTO_XVIX_XAIX_Y_COORDINATE_INDEX 5U

/* !LINKSTO Crypto.Req.CPr/HASH_SHA3224_NOTSET/GENERAL/0022,1 */
#if (defined CRYPTO_XVIX_XAIX_Z_COORDINATE_INDEX)
#error CRYPTO_XVIX_XAIX_Z_COORDINATE_INDEX is already defined
#endif
/** \brief The index for the z coordinate of the state array */
#define CRYPTO_XVIX_XAIX_Z_COORDINATE_INDEX 64U

/* !LINKSTO Crypto.Req.CPr/HASH_SHA3224_NOTSET/GENERAL/0024,1 */
#if (defined CRYPTO_XVIX_XAIX_CONV_TO_STATE)
#error CRYPTO_XVIX_XAIX_CONV_TO_STATE is already defined
#endif
/** \brief Converting String to State Array **/
#define CRYPTO_XVIX_XAIX_CONV_TO_STATE(x, y) ((x) + (5U * (y)))

/* !LINKSTO Crypto.Req.CPr/HASH_SHA3224_NOTSET/GENERAL/0025,1 */
#if (defined CRYPTO_XVIX_XAIX_READ_LANE)
#error CRYPTO_XVIX_XAIX_READ_LANE is already defined
#endif
/** \brief Return a 64-bit value **/
#define CRYPTO_XVIX_XAIX_READ_LANE(x, y, array) ((array)[CRYPTO_XVIX_XAIX_CONV_TO_STATE(x, y)])

/* !LINKSTO Crypto.Req.CPr/HASH_SHA3224_NOTSET/GENERAL/0026,1 */
#if (defined CRYPTO_XVIX_XAIX_WRITE_LANE)
#error CRYPTO_XVIX_XAIX_WRITE_LANE is already defined
#endif
/** \brief Store a 64-bit value **/
#define CRYPTO_XVIX_XAIX_WRITE_LANE(x, y, array, lane) ((array)[CRYPTO_XVIX_XAIX_CONV_TO_STATE(x, y)]) = (lane)

/* !LINKSTO Crypto.Req.CPr/HASH_SHA3224_NOTSET/GENERAL/0019,1 */
#if (defined CRYPTO_XVIX_XAIX_XOR_LANE)
#error CRYPTO_XVIX_XAIX_XOR_LANE is already defined
#endif
/** \brief XOR into a 64-bit value **/
#define CRYPTO_XVIX_XAIX_XOR_LANE(x, y, array, lane) ((array)[CRYPTO_XVIX_XAIX_CONV_TO_STATE(x, y)]) ^= (lane)

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
static FUNC(boolean, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetNextState
(
  P2VAR(uint8,                                         AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) smStateIndx,
        Crypto_xVIx_xAIx_PrimitiveStateIdentifierType                                         curState,
        Std_ReturnType                                                                        resultAction,
        Crypto_ProcessingType                                                                 jobProcessing,
  P2VAR(Crypto_xVIx_xAIx_PrimitiveStateIdentifierType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) nxtState
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

/* -----------------------------------------------------------------------------------------------*/
/* state transition functions */

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
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

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
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishSqueeze2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

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
 ** \retval  E_OK  Request successful.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

/** \brief  State action function for state
 **         'CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS'
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK           Request successful, trigger state transition function.
 ** \retval  CRYPTO_E_BUSY  Request not yet finished, data pending to be absorbed.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Nonreentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_SHA3_SpongeAbsorb
(

    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

/** \brief  State action function for state
 **         'CRYPTO_XVIX_XAIX_STATE_FINISHPADDING'
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  E_OK
 **
 ** \retval  E_OK           Request successful, trigger state transition function.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_SHA3_SpongePadding
(

    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

/** \brief  State action function for state
 **         'CRYPTO_XVIX_XAIX_STATE_FINISHSQUEEZE'
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  E_OK
 **
 ** \retval  E_OK           Request successful, trigger state transition function.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_SHA3_SpongeSqueeze
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal constants]==========================================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  The primitives state transition table. **/

/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_StateTransitionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateTransitionType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Process_StateTransitionTable[CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT] =
{
  { NULL_PTR,                                                      CRYPTO_XVIX_XAIX_STATE_STARTIDLE,        CRYPTO_XVIX_XAIX_STATE_STARTIDLE,        CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle,            CRYPTO_XVIX_XAIX_STATE_STARTEXEC,        CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,       CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { NULL_PTR,                                                      CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,       CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,       CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess,        CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC,       CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,    CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { NULL_PTR,                                                      CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,    CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,    CRYPTO_XVIX_XAIX_PROCESSING_BOTH, CRYPTO_E_BUSY },
  { Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle,  CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,    CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE, CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { NULL_PTR,                                                      CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE, CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE, CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { NULL_PTR,                                                      CRYPTO_XVIX_XAIX_STATE_FINISHEXEC,       CRYPTO_XVIX_XAIX_STATE_FINISHPADDING,    CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { NULL_PTR,                                                      CRYPTO_XVIX_XAIX_STATE_FINISHPADDING,    CRYPTO_XVIX_XAIX_STATE_FINISHSQUEEZE,    CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { Crypto_xVIx_xAIx_StateMachine_FinishSqueeze2StartIdle,         CRYPTO_XVIX_XAIX_STATE_FINISHSQUEEZE,    CRYPTO_XVIX_XAIX_STATE_STARTIDLE,        CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle,                CRYPTO_XVIX_XAIX_STATE_CANCEL,           CRYPTO_XVIX_XAIX_STATE_STARTIDLE,        CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { Crypto_xVIx_xAIx_StateMachine_Error2StartIdle,                 CRYPTO_XVIX_XAIX_STATE_ERROR,            CRYPTO_XVIX_XAIX_STATE_STARTIDLE,        CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          }
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

/** \brief  The primitives state action table. **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_StateActionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateActionType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Process_StateActionTable[CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT] =
{
  /* CRYPTO_XVIX_XAIX_STATE_STARTIDLE                   */ { NULL_PTR }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1        */
  /* CRYPTO_XVIX_XAIX_STATE_STARTEXEC                   */ { NULL_PTR }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTEXEC/0001,1        */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE                  */ { NULL_PTR }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC                  */ { NULL_PTR }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS               */ { Crypto_xVIx_xAIx_SHA3_SpongeAbsorb },
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE            */ { NULL_PTR }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE/0001,1 */
  /* CRYPTO_XVIX_XAIX_STATE_FINISHEXEC                  */ { NULL_PTR }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_FINISHEXEC/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_FINISHPADDING               */ { Crypto_xVIx_xAIx_SHA3_SpongePadding },
  /* CRYPTO_XVIX_XAIX_STATE_FINISHSQUEEZE               */ { Crypto_xVIx_xAIx_SHA3_SpongeSqueeze },
  /* CRYPTO_XVIX_XAIX_STATE_CANCEL                      */ { NULL_PTR },
  /* CRYPTO_XVIX_XAIX_STATE_ERROR                       */ { NULL_PTR }
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

/* !LINKSTO Crypto.Req.CPr/HASH_SHA3224_NOTSET/GENERAL/0002,1 */
/** \brief SHA3 (Keccak) constants for 24 rounds.
 *
 *  This is the constant padding block used for the SHA3 last block.
 */
static CONST(uint64, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_KeccakF_RoundConstants[CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA3224_NOTSET_NUMBER_OF_ROUNDS] =
{
  (uint64)0x0000000000000001ULL, (uint64)0x0000000000008082ULL,
  (uint64)0x800000000000808AULL, (uint64)0x8000000080008000ULL,
  (uint64)0x000000000000808BULL, (uint64)0x0000000080000001ULL,
  (uint64)0x8000000080008081ULL, (uint64)0x8000000000008009ULL,
  (uint64)0x000000000000008AULL, (uint64)0x0000000000000088ULL,
  (uint64)0x0000000080008009ULL, (uint64)0x000000008000000AULL,
  (uint64)0x000000008000808BULL, (uint64)0x800000000000008BULL,
  (uint64)0x8000000000008089ULL, (uint64)0x8000000000008003ULL,
  (uint64)0x8000000000008002ULL, (uint64)0x8000000000000080ULL,
  (uint64)0x000000000000800AULL, (uint64)0x800000008000000AULL,
  (uint64)0x8000000080008081ULL, (uint64)0x8000000000008080ULL,
  (uint64)0x0000000080000001ULL, (uint64)0x8000000080008008ULL
};

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Process -------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Process/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Process
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType);

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
    (void) Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Reset(workspace->paObjectId, job, primitive);
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
        (void) Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Main(objectId, job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Main ----------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Main/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Main
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType);

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
    if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Process_StateActionTable[curState].fcnAction))
    {
      resultAction = Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Process_StateActionTable[curState].fcnAction(job, primitive);
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
     * The return value of GetNextState cannot be FALSE for HASH_SHA3224_NOTSET, because the state machine
     * transition table for this cryptographic primitive is complete.
     */
    if (TRUE == nxtStateFound)
    /* CHECK: PARSE */
    {
      workspace->smStateIndx = smStateIndx;
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0010,1 */
      if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Process_StateTransitionTable[smStateIndx].fcnTransition))
      {
        /* transition function returns using workspace->smResult */
        (void) Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Process_StateTransitionTable[smStateIndx].fcnTransition(job, primitive);

        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0011,1 */
        /* CHECK: NOPARSE
         * HASH primitives cannot reach error state as they can accept every input.
         */
        if (E_OK != workspace->smResult)
        {
          /* !LINKSTO Crypto.Asr.SWS_Crypto_00119,1 */
          nxtState = CRYPTO_XVIX_XAIX_STATE_ERROR;
        }
        /* CHECK: PARSE */
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Cancel --------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Cancel/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Cancel
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType);

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
      (void) Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Main(objectId, job, primitive);
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Reset ---------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Reset/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Reset
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as
   * secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESET(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType));
    result = E_OK;
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Restart ---------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Restart/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Restart
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESTART(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType));
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Callback ------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Callback/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
/* CHECK: NOPARSE
 * This API is only reachable for cryptographic primitives that are using a secondary primitive.
 */
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(objectId);
  TS_PARAM_UNUSED(job);
  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Callback/0002,1 */
  workspace->notifyType   = cbkType;
  workspace->notifyResult = cbkResult;

  return E_OK;
}
/* CHECK: PARSE */
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_StateMachine_Error2StartIdle ----------------------------------------------*/

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveError2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
/* CHECK: NOPARSE
 * HASH primitives cannot reach error state as they can accept every input.
 */
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType);

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
  result              = Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Reset(workspace->paObjectId, job, primitive);
  workspace->smResult = smResult;

  return result;
}
/* CHECK: PARSE */
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

/*--- Crypto_xVIx_xAIx_GetNextState --------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
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
    if (   (Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx   = i;
      break;
    }
  }

  /* 2) iterate from first table entry to last found entry in table */
  for (i = 0U; (FALSE == nxtStateFound) && (i < *smStateIndx); i++)
  {
    if (   (Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx  = i;
      break;
    }
  }

  return nxtStateFound;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_SHA3_Theta --------------------------------------- */

/* !LINKSTO Crypto.Req.CPr/HASH_SHA3224_NOTSET/GENERAL/0014,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_SHA3_Theta
(
  P2VAR(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace
)
{
  uint8  x;
  uint8  y;

  uint64 C[CRYPTO_XVIX_XAIX_X_COORDINATE_INDEX];
  uint64 D;

  /* Compute the parity of the columns */
  for (x = 0U; x < CRYPTO_XVIX_XAIX_X_COORDINATE_INDEX; x++)
  {
    C[x] =   CRYPTO_XVIX_XAIX_READ_LANE(x, 0U, workspace->hashState)
           ^ CRYPTO_XVIX_XAIX_READ_LANE(x, 1U, workspace->hashState)
           ^ CRYPTO_XVIX_XAIX_READ_LANE(x, 2U, workspace->hashState)
           ^ CRYPTO_XVIX_XAIX_READ_LANE(x, 3U, workspace->hashState)
           ^ CRYPTO_XVIX_XAIX_READ_LANE(x, 4U, workspace->hashState);
  }

  for (x = 0U; x < CRYPTO_XVIX_XAIX_X_COORDINATE_INDEX; x++)
  {
    /* Compute the Theta effect for a given column */
    D =  C[(x + 4U) % CRYPTO_XVIX_XAIX_X_COORDINATE_INDEX]
       ^ CRYPTO_XVIX_XAIX_ROL64(C[(x + 1U) % CRYPTO_XVIX_XAIX_X_COORDINATE_INDEX], 1U);

    /* Add the Theta effect to the whole column */
    for (y = 0U; y < CRYPTO_XVIX_XAIX_Y_COORDINATE_INDEX; y++)
    {
      CRYPTO_XVIX_XAIX_XOR_LANE(x, y, workspace->hashState, D);
    }
  }
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_SHA3_Rho_And_Pi --------------------------------------- */

/* !LINKSTO Crypto.Req.CPr/HASH_SHA3224_NOTSET/GENERAL/0015,1 */
/* !LINKSTO Crypto.Req.CPr/HASH_SHA3224_NOTSET/GENERAL/0016,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_SHA3_Rho_And_Pi
(
  P2VAR(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace
)
{
  uint8 t;
  uint8 x;
  uint8 y;
  uint8 yTmp;
  uint8 r;

  uint64 Current;
  uint64 Temp;

  /* start at coordinate (1 0) */
  x = 1U;
  y = 0U;
  Current = CRYPTO_XVIX_XAIX_READ_LANE(x, y, workspace->hashState);

  /* Iterate over ((0 1)(2 3)) ^ t * (1 0) for 0 <= t < 24 */
  for (t = 0U; t < CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA3224_NOTSET_NUMBER_OF_ROUNDS; t++)
  {
    /* Compute the rotation constant r = (t+1)(t+2)/2 */
    r = (((t + 1U) * (t + 2U)) / 2U) % CRYPTO_XVIX_XAIX_Z_COORDINATE_INDEX;
    /* Compute ((0 1)(2 3)) * (x y) */
    yTmp = ((2U * x) + (3U * y)) % CRYPTO_XVIX_XAIX_Y_COORDINATE_INDEX;
    /* x = ((0 * x) + (1 * y)) */
    x = y;
    y = yTmp;

    /* Swap current and state(x,y), and rotate */
    Temp = CRYPTO_XVIX_XAIX_READ_LANE(x, y, workspace->hashState);
    CRYPTO_XVIX_XAIX_WRITE_LANE(x, y, workspace->hashState, CRYPTO_XVIX_XAIX_ROL64(Current, r));
    Current = Temp;
  }
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_SHA3_Chi --------------------------------------- */

/* !LINKSTO Crypto.Req.CPr/HASH_SHA3224_NOTSET/GENERAL/0017,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_SHA3_Chi
(
  P2VAR(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace
)
{
  uint8  x;
  uint8  y;

  uint64 A;
  uint64 Temp[CRYPTO_XVIX_XAIX_X_COORDINATE_INDEX];

  for (y = 0U; y < CRYPTO_XVIX_XAIX_Y_COORDINATE_INDEX; y++)
  {
    /* Take a copy of the plane */
    for (x = 0U; x < CRYPTO_XVIX_XAIX_X_COORDINATE_INDEX; x++)
    {
      Temp[x] = CRYPTO_XVIX_XAIX_READ_LANE(x, y, workspace->hashState);
    }

    /* Compute Chi on the plane */
    for (x = 0U; x < CRYPTO_XVIX_XAIX_X_COORDINATE_INDEX; x++)
    {
      A = (~(uint64)(Temp[((x + 1U) % CRYPTO_XVIX_XAIX_X_COORDINATE_INDEX)]));
      A &= Temp[((x + 2U) % CRYPTO_XVIX_XAIX_X_COORDINATE_INDEX)];
      A ^= Temp[x];
      CRYPTO_XVIX_XAIX_WRITE_LANE(x, y, workspace->hashState, A);
    }
  }

}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_SHA3_Iota --------------------------------------- */

/* !LINKSTO Crypto.Req.CPr/HASH_SHA3224_NOTSET/GENERAL/0018,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_SHA3_Iota
(
  P2VAR(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace,
        uint8                                          Index

)
{
  /* Add the predefined RoundConstants[i] constant to the lane at location State[0U] */
  workspace->hashState[0U] ^= Crypto_xVIx_xAIx_KeccakF_RoundConstants[Index];
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_SHA3_KeccakF1600_StatePermute --------------------------------------- */

/* !LINKSTO Crypto.Req.CPr/HASH_SHA3224_NOTSET/GENERAL/0013,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_SHA3_KeccakF1600_StatePermute
(
  P2VAR(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) workspace
)
{
  uint8  i;

  /* Each round consists of a sequence of five transformations,
   * which are called the step mappings
   */
  for (i = 0U; i < CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA3224_NOTSET_NUMBER_OF_ROUNDS; i++)
  {
    /* Apply Theta step mapping */
    Crypto_xVIx_xAIx_SHA3_Theta(workspace);
    /* Apply Rho and Pi steps mapping */
    Crypto_xVIx_xAIx_SHA3_Rho_And_Pi(workspace);
    /* Apply Chi step mapping */
    Crypto_xVIx_xAIx_SHA3_Chi(workspace);
    /* Apply Iota step mapping */
    Crypto_xVIx_xAIx_SHA3_Iota(workspace, i);
  }
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_SHA3_SpongeAbsorb --------------------------------------- */

/* !LINKSTO Crypto.Req.CPr/HASH_SHA3224_NOTSET/GENERAL/0006,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_SHA3_SpongeAbsorb
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  Std_ReturnType retVal = E_NOT_OK;
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType);
  uint32 i;
  uint32 offset;

  TS_PARAM_UNUSED(job);

  /* Absorbing phase */

  /* !LINKSTO Crypto.Req.CPr/HASH_SHA3224_NOTSET/GENERAL/0010,1 */
  offset = CRYPTO_XVIX_XAIX_MIN(workspace->inputBytes2Fetch, CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA3224_NOTSET_BLOCKSIZE_BYTE);

  /* Absorb the input */
  for (
        i = 0U;
        ((i < offset) && (workspace->inputBytesFetched < CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA3224_NOTSET_BLOCKSIZE_BYTE));
        i++
      )
  {
    workspace->hashState[workspace->inputBytesFetched / sizeof(uint64)] ^=
        (uint64)(workspace->inputActPtr[i]) << (((workspace->inputBytesFetched) % sizeof(uint64)) * 8UL);
    workspace->inputBytesFetched++;
  }

  workspace->inputBytes2Fetch  -= i;
  workspace->inputActPtr = &workspace->inputActPtr[i];

  /* Check if a full block is absorbed */
  if (workspace->inputBytesFetched == CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA3224_NOTSET_BLOCKSIZE_BYTE)
  {
    /* Apply block permutation function */
    /* !LINKSTO Crypto.Req.CPr/HASH_SHA3224_NOTSET/GENERAL/0023,1 */
    Crypto_xVIx_xAIx_SHA3_KeccakF1600_StatePermute(workspace);
    workspace->inputBytesFetched = 0U;
  }

  /* Check if there is more data to be fetched */
  if (0U < workspace->inputBytes2Fetch)
  {
    retVal = CRYPTO_E_BUSY;
  }
  else
  {
    retVal = E_OK;
  }

  return retVal;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_SHA3_SpongePadding --------------------------------------- */

/* !LINKSTO Crypto.Req.CPr/HASH_SHA3224_NOTSET/GENERAL/0007,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_SHA3_SpongePadding
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(job);

  /* Add the domain separation suffix and the first padding bit */
  workspace->hashState[workspace->inputBytesFetched / sizeof(uint64)] ^=
      (uint64)(CRYPTO_XVIX_XAIX_SHA3_KECCAK_SUFFIX_AND_FIRST_PADDING_BIT) << (((workspace->inputBytesFetched) % sizeof(uint64)) * 8UL);

  /* Add the final padding bit */
  workspace->hashState[(CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA3224_NOTSET_BLOCKSIZE_BYTE - 1U) / sizeof(uint64)] ^=
      (uint64)(CRYPTO_XVIX_XAIX_SHA3_KECCAK_FINAL_PADDING_BIT) << (((CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA3224_NOTSET_BLOCKSIZE_BYTE - 1U) % sizeof(uint64)) * 8UL);

  /* Apply block permutation function */
  Crypto_xVIx_xAIx_SHA3_KeccakF1600_StatePermute(workspace);

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_SHA3_SpongeSqueeze --------------------------------------- */

/* !LINKSTO Crypto.Req.CPr/HASH_SHA3224_NOTSET/GENERAL/0009,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_SHA3_SpongeSqueeze
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType);
  uint32 i;

  /* !LINKSTO Crypto.Req.CPr/HASH_SHA3224_NOTSET/FINISH/0001,1 */
  uint32 ResultLength = CRYPTO_XVIX_XAIX_MIN(*( job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr), CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA3224_NOTSET_RESULTSIZE);

  for(i = 0U; i < ResultLength; i++)
  {
    job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr[i] = (uint8)(workspace->hashState[i / sizeof(uint64)] >> ((i % sizeof(uint64)) * 8UL));
  }

  *( job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr) = ResultLength;

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle --------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType);

  CRYPTO_XVIX_XAIX_SET_SMRESULT_START(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess -------------------------------- */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType);

  TS_PARAM_UNUSED(job);

  workspace->inputBytes2Fetch = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength;
  workspace->inputActPtr = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr;

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle -------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType);

  CRYPTO_XVIX_XAIX_SET_SMRESULT_UPDATE(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishSqueeze2StartIdle --------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishSqueeze2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  Std_ReturnType ret = E_NOT_OK;
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType);

  ret = E_OK;
  /* Deviation TASKING-1 */
  CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH(ret, sizeof(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType));

  return ret;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle ------------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveCancel2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType);

  /* !LINKSTO Crypto.Asr.SWS_Crypto_00183,2 */
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00144,1 */
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00181_1,1 */
  CRYPTO_XVIX_XAIX_SET_SMRESULT_CANCEL(CRYPTO_E_JOB_CANCELED, sizeof(Crypto_xVIx_xAIx_CPr_HASH_SHA3224_NOTSET_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3224_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[end of file]=================================================================*/

