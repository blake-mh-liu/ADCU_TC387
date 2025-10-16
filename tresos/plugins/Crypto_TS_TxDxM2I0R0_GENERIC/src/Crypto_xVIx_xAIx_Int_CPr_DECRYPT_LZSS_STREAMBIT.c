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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_DECRYPT_LZSS_STREAMBIT.c/0001,1 */

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

#include <Crypto_xVIx_xAIx_Int.h>                                 /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_DECRYPT_LZSS_STREAMBIT.c/0002,1 */
#include <Crypto_xVIx_xAIx_Int_KeyManagement.h>                   /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_DECRYPT_LZSS_STREAMBIT.c/0003,1 */
#include <Crypto_xVIx_xAIx_Int_CPr_DECRYPT_LZSS_STREAMBIT.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_DECRYPT_LZSS_STREAMBIT.c/0004,1 */

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
#define CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT 10U

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

#if (defined CRYPTO_XVIX_XAIX_STATE_UPDATEDECOMPRESS)
#error CRYPTO_XVIX_XAIX_STATE_UPDATEDECOMPRESS already defined
#endif
/** \brief  The UpdateDecompress state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_UPDATEDECOMPRESS 5U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE)
#error CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE already defined
#endif
/** \brief  The UpdateFinishIdle state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE 6U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_FINISHEXEC,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_FINISHEXEC)
#error CRYPTO_XVIX_XAIX_STATE_FINISHEXEC already defined
#endif
/** \brief  The FinishExec state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_FINISHEXEC 7U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_CANCEL,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_CANCEL)
#error CRYPTO_XVIX_XAIX_STATE_CANCEL already defined
#endif
/** \brief  The Cancel state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_CANCEL 8U

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_STATE_ERROR,1 */
#if (defined CRYPTO_XVIX_XAIX_STATE_ERROR)
#error CRYPTO_XVIX_XAIX_STATE_ERROR already defined
#endif
/** \brief  The Error state of the primitive. **/
#define CRYPTO_XVIX_XAIX_STATE_ERROR 9U

/** \brief  A byte with its most significant bit set
 **/
#if (defined CRYPTO_XVIX_XAIX_DECOMPRESS_SET_BYTE_MSB)
#error CRYPTO_XVIX_XAIX_DECOMPRESS_SET_BYTE_MSB already defined
#endif
#define  CRYPTO_XVIX_XAIX_DECOMPRESS_SET_BYTE_MSB ((uint8)0x80U)

/** \brief  Internal states of the DECRYPT_LZSS_STREAMBIT_Decompress.
 **/
#if (defined CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_DECOMPRESS_S_IDLE)
#error CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_DECOMPRESS_S_IDLE already defined
#endif
/** \brief  The Idle state of the DECOMPRESS. **/
#define CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_DECOMPRESS_S_IDLE 0x01U

#if (defined CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_DECOMPRESS_S_ILLEGAL)
#error CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_DECOMPRESS_S_ILLEGAL already defined
#endif
/** \brief  The Error state of the DECOMPRESS. **/
#define CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_DECOMPRESS_S_ILLEGAL 0x02U

#if (defined CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_DECOMPRESS_S_INITIALIZED)
#error CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_DECOMPRESS_S_INITIALIZED already defined
#endif
/** \brief  The Initialized state of the DECOMPRESS. **/
#define CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_DECOMPRESS_S_INITIALIZED 0x03U

#if (defined CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_MAX_CONFIG_VALUE)
#error CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_MAX_CONFIG_VALUE already defined
#endif
/** \brief The maximal size of the configuration value */
#define CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_MAX_CONFIG_VALUE    0x7FFFUL

#if (defined CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_EMPTY)
#error CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_EMPTY already defined
#endif
/** \brief We do not have an incomplete encoding at the moment */
#define CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_EMPTY           0U

#if (defined CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_INCOMPLETE_BYTE)
#error CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_INCOMPLETE_BYTE already defined
#endif
/** \brief We have an incomplete encoding of a byte */
#define CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_INCOMPLETE_BYTE 1U

#if (defined CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_INCOMPLETE_TOKEN)
#error CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_INCOMPLETE_TOKEN already defined
#endif
/** \brief We have an incomplete encoding of a compression token */
#define CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_INCOMPLETE_TOKEN 2U

#if (defined CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_NR_OF_BITS_IN_BYTE)
#error CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_NR_OF_BITS_IN_BYTE already defined
#endif
/** \brief the number of bits in a byte */
#define CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_NR_OF_BITS_IN_BYTE 8UL

#if (defined CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_CREATE_BITMASK)
#error CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_CREATE_BITMASK already defined
#endif
/** \brief Create a bitmask for a given amount of bits
 **
 ** \param[in]  nrOfBits   How many bits shall the mask contain
 **
 ** \returns A bitmask which contains as many set bits as requested
 **/
#define CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_CREATE_BITMASK(nrOfBits) (((uint32)1UL << (nrOfBits)) - (uint32)1UL)

#if (defined CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_IS_EOS_TOKEN)
#error CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_IS_EOS_TOKEN already defined
#endif
/** \brief Is a given token (or token fragment) the end of stream (EOS) token?
 **
 ** The end of stream is indicated by a decompression token (or a fragment of a token) which at
 ** least is long enough to contain a full "position" element and whose position element has the value
 ** zero. This is checked here
 **
 ** \param[in]  token   The contents of the token (fragment)
 ** \param[in]  length  The length of the token (fragment)
 **
 ** \returns  Is this an EOS token (fragment)
 **
 ** \retval  TRUE  This is an EOS token (fragment)
 ** \retval  FALSE This is not an EOS token (fragment)
 **/
#define CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_IS_EOS_TOKEN(token, length)                                          \
(boolean)                                                                                            \
(                                                                                                    \
  ((length) >= workspace->tokenPositionSize) &&                                                      \
  ((((uint32)(token) >> ((length) - workspace->tokenPositionSize)) & workspace->positionMask) == 0U) \
)

#if (defined CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_GET_BITS_FROM_BYTE)
#error CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_GET_BITS_FROM_BYTE already defined
#endif
/** \brief Get a given amount of bits from a byte
 **
 ** Please note that this macro expects the order of bits in the bytes such that the first bit,
 ** i.e. bit position 0, is the most significant bit in the byte
 **
 ** \param[in]  byte      The byte to read from
 ** \param[in]  position  The bit position of the first bit to get from the byte
 ** \param[in]  length    The number of bits to get from the byte
 **
 ** \returns  The requested bits in the given byte, shifted to the right
 **/
#define CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_GET_BITS_FROM_BYTE(byte, position, length)                                     \
(                                                                                                              \
  ((uint32)(byte) >> (CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_NR_OF_BITS_IN_BYTE - ((uint32)(length) + (uint32)(position)))) & \
  CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_CREATE_BITMASK(length)                                                               \
)

#if (defined CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_RINGBUFFER_READ_FROM_POS)
#error CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_RINGBUFFER_READ_FROM_POS already defined
#endif
/** \brief Read a byte from a given position in a ring buffer
 **
 ** \param[in]  buffer    The ring buffer to read from
 ** \param[in]  position  The position of the byte in the ring buffer
 **
 ** \returns  The requested byte in the ring buffer
 **/
#define CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_RINGBUFFER_READ_FROM_POS(buffer, position) \
(                                                                          \
  (buffer)->array[(position) % (buffer)->size]                             \
)

#if (defined CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_RINGBUFFER_IS_POS_FILLED)
#error CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_RINGBUFFER_IS_POS_FILLED already defined
#endif
/** \brief Is the ring buffer filled up to the given position?
 **
 ** \param[in]  buffer    The ring buffer to check
 ** \param[in]  position  The position in the ring buffer to check
 **
 ** \returns  Is the ring buffer already filled up to the given position
 **
 ** \retval  TRUE  The ring buffer is filled
 ** \retval  FALSE The ring buffer is not yet filled
 **/
#define CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_RINGBUFFER_IS_POS_FILLED(buffer, position) \
(                                                                          \
  ((buffer)->level + (buffer)->start > (position))                         \
    ? (boolean)TRUE                                                        \
    : (boolean)FALSE                                                       \
)

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(boolean, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetNextState
(
  P2VAR(uint8,                                         AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) smStateIndx,
        Crypto_xVIx_xAIx_PrimitiveStateIdentifierType                                         curState,
        Std_ReturnType                                                                        resultAction,
        Crypto_ProcessingType                                                                 jobProcessing,
  P2VAR(Crypto_xVIx_xAIx_PrimitiveStateIdentifierType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) nxtState
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */
/** \brief  State action function for state
 **         'CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS'.
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK           Request successful.
 ** \retval  CRYPTO_E_BUSY  Further processing is needed.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/** \brief  State action function for state
 **         'CRYPTO_XVIX_XAIX_STATE_UPDATEDECOMPRESS'
 **
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK           Request successful, trigger state transition function.
 ** \retval  CRYPTO_E_BUSY  Request not yet done.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateDecompress
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

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
 ** \retval  E_OK  Request successful.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

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
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

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
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_UPDATEDECOMPRESS'
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
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateDecompress2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/** \brief  State transition function
 **         from state 'CRYPTO_XVIX_XAIX_STATE_FINISHEXEC'
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/** \brief  Append a new element of type 'uint8' to a ring buffer with elements of type 'uint8'.
 **         Adds a new element at the end of the ring buffer, after its current last element.
 **         The content of this new element is initialized to a copy of 'byte'.
 **
 ** \param[in]  buffer  A pointer to a ring buffer data structure variable that describes a
 **                     ring buffer.
 ** \param[in]  byte    Value to be append.
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_CommonRingBufferPush
(
  P2VAR(Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_RingBuffer_Type, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer,
  VAR(uint8,                                 AUTOMATIC                            ) byte
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/** \brief  Initializes ring buffer with elements of type 'uint8'.
 **         Constructs a ring buffer data structure variable with initialized members.
 **
 ** \param[in]   array      A pointer to the memory area which shall hold the ring buffer.
 ** \param[in]   arrayLen   The size of 'array'.
 ** \param[out]  buffer     A pointer to a ring buffer data structure variable that shall
 **                         describe the ring buffer.
 ** \param[in]   bufferLen  The size 'buffer' shall have..
 **
 ** \returns     Information about whether the initialization was successful or not.
 **
 ** \retval      E_OK      Initialization was successful.
 ** \retval      E_NOT_OK  Initialization wasn't successful.
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_CommonRingBufferInit
(
  P2VAR(uint8,                                  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) array,
    VAR(uint32,                                 AUTOMATIC                            ) arrayLen,
  P2VAR(Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_RingBuffer_Type,    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer,
    VAR(uint32,                                 AUTOMATIC                            ) bufferLen,
    VAR(uint32,                                 AUTOMATIC                            ) bufferStart
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/** \brief  Write out decompressed data into output buffer.
 **
 ** \param[in]      primitive           Pointer to the data structure describes the current primitive.
 ** \param[in,out]  outputBuffer        Holds a pointer to the memory location where the
 **                                     decompressed data shall be stored.
 ** \param[in]      outputBufferLen     Holds a pointer to a memory location in which the length
 **                                     information is stored.
 ** \param[in]      outputBufferPos     The current position in outputBuffer where to insert
 **                                     decompressed data.
 **
 ** \returns  The new position in outputBuffer where to insert further decompressed data.
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_CopyBytesFromLookBack
(
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType,       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
  P2VAR(uint8,                                     AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) outputBuffer,
  VAR(uint32,                                      AUTOMATIC                            ) outputBufferLen,
  VAR(uint32,                                      AUTOMATIC                            ) outputBufferPos
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/** \brief  Interprets a two byte block of compressed data as tuple of position and length and
 **         calls Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_CopyBytesFromLookBack.
 **
 ** \param[in]      primitive           Pointer to the data structure describes the current primitive.
 ** \param[in,out]  outputBuffer        Holds a pointer to the memory location where the
 **                                     decompressed data shall be stored.
 ** \param[in]      outputBufferLen     Holds a pointer to a memory location in which the length
 **                                     information is stored.
 ** \param[in]      outputBufferPos     The current position in outputBuffer where to insert
 **                                     decompressed data.
 ** \param[in]      token               The current compressed data token.
 **
 ** \returns  The new position in outputBuffer where to insert further decompressed data.
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_DecodeEncoding
(
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType,       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
  P2VAR(uint8,                                     AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) outputBuffer,
  VAR(uint32,                                      AUTOMATIC                            ) outputBufferLen,
  VAR(uint32,                                      AUTOMATIC                            ) outputBufferPos,
  VAR(uint32,                                      AUTOMATIC                            ) token
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/** \brief  Complete DECRYPT_LZSS_STREAMBIT decompression computation and reset parts of the context.
 **
 ** \param[in]      primitive           Pointer to the data structure describes the current primitive.

 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                      Request successful.
 ** \retval   E_NOT_OK                  Request failed.
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_DecompressEnd
(
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType,       AUTOMATIC,      CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/** \brief  Try to read a requested number of bits from an input byte array.
 **
 ** \param[in]     input                 The byte array to read from
 ** \param[in,out] inputBitPosPtr        The current bit position in the first byte of the input array
 **                                      when the function is called and the new bit position in the
 **                                      input array after the bits have been read
 ** \param[in]     inputByteLen          The byte length of the input array
 ** \param[in]     nrOfBitsToRead        How many bits shall be read from the input array
 ** \param[in,out] inputBytePosPtr       The current byte position in the input array
 ** \param[out]    outputBitsPtr         The bits that have been read from the input array

 **
 ** \returns  Number of bits that have actually been read from the input array. This value may be
 **           lower than nrOfBitsToRead if the input array was not large enough
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(uint8, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_ReadBitsFromArray
(
  P2CONST(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) input,
    P2VAR(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) inputBitPosPtr,
      VAR(uint32, AUTOMATIC                            ) inputByteLen,
      VAR(uint8,  AUTOMATIC                            ) nrOfBitsToRead,
    P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) inputBytePosPtr,
    P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) outputBitsPtr
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal constants]==========================================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  The primitives state transition table. **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_StateTransitionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateTransitionType, CRYPTO_xVIx_xAIx_CONST)
Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Process_StateTransitionTable[CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT] =
{
  { NULL_PTR,                                                                                 CRYPTO_XVIX_XAIX_STATE_STARTIDLE,                     CRYPTO_XVIX_XAIX_STATE_STARTIDLE,                     CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE_TO_CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1               */
  { Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle,                                       CRYPTO_XVIX_XAIX_STATE_STARTEXEC,                     CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,                    CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { NULL_PTR,                                                                                 CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,                    CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE,                    CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE_TO_CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE/0001,1             */
  { Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess,                                   CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC,                    CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,                 CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { NULL_PTR,                                                                                 CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,                 CRYPTO_XVIX_XAIX_STATE_UPDATEDECOMPRESS,              CRYPTO_XVIX_XAIX_PROCESSING_BOTH, CRYPTO_E_BUSY },
  { Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle,                             CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,                 CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,              CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { NULL_PTR,                                                                                 CRYPTO_XVIX_XAIX_STATE_UPDATEDECOMPRESS,              CRYPTO_XVIX_XAIX_STATE_UPDATEDECOMPRESS,              CRYPTO_XVIX_XAIX_PROCESSING_BOTH, CRYPTO_E_BUSY },
  { Crypto_xVIx_xAIx_StateMachine_UpdateDecompress2UpdateProcess,                             CRYPTO_XVIX_XAIX_STATE_UPDATEDECOMPRESS,              CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS,                 CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },

  { NULL_PTR,                                                                                 CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,              CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE,              CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE_TO_CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE/0001,1 */

  { Crypto_xVIx_xAIx_StateMachine_FinishExec2StartIdle,                                       CRYPTO_XVIX_XAIX_STATE_FINISHEXEC,                    CRYPTO_XVIX_XAIX_STATE_STARTIDLE,                     CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK },

  { Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle,                                           CRYPTO_XVIX_XAIX_STATE_CANCEL,                        CRYPTO_XVIX_XAIX_STATE_STARTIDLE,                     CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          },
  { Crypto_xVIx_xAIx_StateMachine_Error2StartIdle,                                            CRYPTO_XVIX_XAIX_STATE_ERROR,                         CRYPTO_XVIX_XAIX_STATE_STARTIDLE,                     CRYPTO_XVIX_XAIX_PROCESSING_BOTH, E_OK          }
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/** \brief  The primitives state action table. **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_StateActionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateActionType, CRYPTO_xVIx_xAIx_CONST)
Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Process_StateActionTable[CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT] =
{
  /* CRYPTO_XVIX_XAIX_STATE_STARTIDLE                     */ { NULL_PTR                                       }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTIDLE/0001,1        */
  /* CRYPTO_XVIX_XAIX_STATE_STARTEXEC                     */ { NULL_PTR                                       }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_STARTEXEC/0001,1        */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE                    */ { NULL_PTR                                       }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEIDLE/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC                    */ { NULL_PTR                                       }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEEXEC/0001,1       */
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEPROCESS                 */ { Crypto_xVIx_xAIx_StateMachine_UpdateProcess    },
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEDECOMPRESS              */ { Crypto_xVIx_xAIx_StateMachine_UpdateDecompress },
  /* CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE              */ { NULL_PTR                                       }, /* !LINKSTO Crypto.Dsn.Alg/CryptographicPrimitives/CRYPTO_XVIX_XAIX_STATE_UPDATEFINISHIDLE/0001,1 */
  /* CRYPTO_XVIX_XAIX_STATE_FINISHEXEC                    */ { NULL_PTR                                       },
  /* CRYPTO_XVIX_XAIX_STATE_CANCEL                        */ { NULL_PTR                                       },
  /* CRYPTO_XVIX_XAIX_STATE_ERROR                         */ { NULL_PTR                                       }
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Process ----------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Process/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Process
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_WorkspaceType);

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
    (void) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Reset(workspace->paObjectId, job, primitive);
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
        (void) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Main(objectId, job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Main -------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Main/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Main
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_WorkspaceType);

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
    if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Process_StateActionTable[curState].fcnAction))
    {
      resultAction = Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Process_StateActionTable[curState].fcnAction(job, primitive);
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
      if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Process_StateTransitionTable[smStateIndx].fcnTransition))
      {
        /* transition function returns using workspace->smResult */
        (void) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Process_StateTransitionTable[smStateIndx].fcnTransition(job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Cancel -----------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Cancel/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Cancel
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_WorkspaceType);

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
      (void) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Main(objectId, job, primitive);
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Reset ------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Reset/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Reset
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as
   * secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESET(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_WorkspaceType));
    result = E_OK;
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Restart ------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Restart/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Restart
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESTART(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_WorkspaceType));
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Callback ---------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Callback/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
/* CHECK: NOPARSE
 * This API is only reachable for cryptographic primitives that are using a secondary primitive.
 */
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_WorkspaceType);

  TS_PARAM_UNUSED(objectId);
  TS_PARAM_UNUSED(job);
  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Callback/0002,1 */
  workspace->notifyType   = cbkType;
  workspace->notifyResult = cbkResult;

  return E_OK;
}
/* CHECK: PARSE */
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_StateMachine_Error2StartIdle ----------------------------------------------*/

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveError2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_WorkspaceType);

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
  result              = Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Reset(workspace->paObjectId, job, primitive);
  workspace->smResult = smResult;

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/*--- Crypto_xVIx_xAIx_GetNextState --------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
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
    if (   (Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx   = i;
      break;
    }
  }

  /* 2) iterate from first table entry to last found entry in table */
  for (i = 0U; (FALSE == nxtStateFound) && (i < *smStateIndx); i++)
  {
    if (   (Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx  = i;
      break;
    }
  }

  return nxtStateFound;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateProcess ---------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_WorkspaceType);

  Std_ReturnType                            result      = E_NOT_OK;
  uint32                                    bytesRemain = 0U;
  uint8                                     bytesFetch  = 0U;
  P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) m = (P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)) workspace->M;

  /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/UPDATE/0001,1 */
  bytesRemain = (job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength - workspace->inputBytesFetched);
  bytesFetch  = (uint8) CRYPTO_XVIX_XAIX_MIN(((uint32) CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_LZSS_STREAMBIT_BLOCKSIZE - workspace->mLvl),
                                             bytesRemain
                                            );

  if (0U != bytesFetch)
  {
    TS_MemCpy(&(m[workspace->mLvl]),
              &(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr[workspace->inputBytesFetched]),
              bytesFetch
             );
    workspace->mLvl              += bytesFetch;
    workspace->inputBytesFetched += bytesFetch;

    result = CRYPTO_E_BUSY;
  }
  else
  {
    result = E_OK;
  }

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateDecompress --------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateDecompress
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_WorkspaceType);

  Std_ReturnType result            = E_NOT_OK;
  uint32 localInputBufferByteLen   = workspace->mLvl;
  uint32 localOutputBufferByteLen  = workspace->outputLength;
  uint32 localInputBufferBytePos   = 0U;
  uint32 localOutputBufferBytePos  = 0U;
  uint8  localInputBufferBitPos    = 0U;
  uint8  nrOfBitsRequested         = 0U;
  uint8  nrOfBitsReceived          = 0U;
  uint32 bitsReadFromInput         = 0U;

  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) localInputBuffer;
  P2VAR(uint8,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) localOutputBuffer;

  /* We start at the beginning of input and output buffers. */
  localInputBuffer  = workspace->M;
  localOutputBuffer = &job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr[workspace->blockOutputLength];

  /* Determine if an incomplete encoding was detected during the last update call. */
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/UPDATE/0002,1 */
  switch(workspace->lastEncodingType)
  {
    case CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_INCOMPLETE_BYTE:
    {
      /* We had an incomplete byte. Read the missing bits from the current input to complete the byte. */
      nrOfBitsRequested = (uint8)CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_NR_OF_BITS_IN_BYTE - workspace->lastEncodingBitLen;
      nrOfBitsReceived =
        Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_ReadBitsFromArray
        (
          localInputBuffer,
          &localInputBufferBitPos,
          localInputBufferByteLen,
          nrOfBitsRequested,
          &localInputBufferBytePos,
          &bitsReadFromInput
        );

      /* Since we have at least one byte of input and we had to read less than one byte, we
       * can be sure that the read succeeded and that the byte is now complete.
       */
      workspace->lastEncodingBits =
        (workspace->lastEncodingBits << nrOfBitsReceived) | bitsReadFromInput;

      /* Copy the current byte to the end of the dictionary. */
      Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_CommonRingBufferPush
      (
        &(workspace->ringBuffer),
        (uint8)workspace->lastEncodingBits
      );
      /* Copy the current byte to the end of the output buffer. */
      /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/UPDATE/0004,1 */
      localOutputBuffer[localOutputBufferBytePos] = (uint8)workspace->lastEncodingBits;
      localOutputBufferBytePos++;

      workspace->lastEncodingType = CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_EMPTY;
    }
    break;

    case CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_INCOMPLETE_TOKEN:
    {
      /* We had an incomplete decompression token. Try to read the missing bits. Please note that it
       * is possible that we do not have enough input bits to complete the token.
       */
      nrOfBitsRequested = workspace->tokenSize - workspace->lastEncodingBitLen;
      nrOfBitsReceived =
        Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_ReadBitsFromArray
        (
          localInputBuffer,
          &localInputBufferBitPos,
          localInputBufferByteLen,
          nrOfBitsRequested,
          &localInputBufferBytePos,
          &bitsReadFromInput
        );

      /* Add the read bits to the incomplete token. */
      workspace->lastEncodingBits =
        (workspace->lastEncodingBits << nrOfBitsReceived) | bitsReadFromInput;
      workspace->lastEncodingBitLen += nrOfBitsReceived;

      /* Were we able to complete the token? */
      if(nrOfBitsRequested == nrOfBitsReceived)
      {
        /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/UPDATE/0005,1 */

        /* The token is complete. */
        workspace->lastEncodingType = CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_EMPTY;

        /* Check if this is the EOS token. Otherwise, try to decode the token and write the
         * decompressed bytes to the output buffer.
         */
        if(CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_IS_EOS_TOKEN(workspace->lastEncodingBits, workspace->tokenSize))
        {
          /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/UPDATE/0006,1 */
          workspace->EOSFound = TRUE;
        }
        else
        {
          localOutputBufferBytePos =
            Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_DecodeEncoding
            (
              primitive,
              localOutputBuffer,
              localOutputBufferByteLen,
              localOutputBufferBytePos,
              workspace->lastEncodingBits
            );
        }
      }
    }
    break;

    default:
      break;
  }

  /* Main decompression loop */
  while
  (
    (localInputBufferBytePos      <  localInputBufferByteLen                     ) &&
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/UPDATE/0007,1 */
    (FALSE                        == workspace->EOSFound                         ) &&
    (workspace->curLength         == 0U                                          ) &&
    (workspace->state             != CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_DECOMPRESS_S_ILLEGAL) &&
    (workspace->lastEncodingType  == CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_EMPTY               )
  )
  {
    /* Get the indicator bit from the input. */
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/UPDATE/0003,1 */
    bitsReadFromInput =
      CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_GET_BITS_FROM_BYTE
      (
        localInputBuffer[localInputBufferBytePos],
        localInputBufferBitPos,
        1U
      );

    localInputBufferBitPos++;
    if(CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_NR_OF_BITS_IN_BYTE == localInputBufferBitPos)
    {
      localInputBufferBitPos = 0;
      localInputBufferBytePos++;
    }

    /* Check the indicator bit. */
    if ( bitsReadFromInput == 1U )
    {
      /* The indicator bit tells us that there is a single byte at the
       * current position in the input buffer.
       */

      /* Try to read the byte from the input buffer. */
      nrOfBitsRequested = CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_NR_OF_BITS_IN_BYTE;
      nrOfBitsReceived =
        Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_ReadBitsFromArray
        (
          localInputBuffer,
          &localInputBufferBitPos,
          localInputBufferByteLen,
          nrOfBitsRequested,
          &localInputBufferBytePos,
          &bitsReadFromInput
        );

      /* Check if the byte could be read completely. */
      if(nrOfBitsRequested == nrOfBitsReceived)
      {
        /* The byte was read completely. Check if there is space left in the output buffer. */
        if(localOutputBufferBytePos < localOutputBufferByteLen)
        {
          /* Copy the current byte to the end of the dictionary. */
          Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_CommonRingBufferPush( &(workspace->ringBuffer), (uint8)bitsReadFromInput );
          /* Copy the current byte to the end of the output buffer. */
          /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/UPDATE/0004,1 */
          localOutputBuffer[localOutputBufferBytePos] = (uint8)bitsReadFromInput;
          localOutputBufferBytePos++;
        }
        else
        {
          /* We do not have space in the buffer to write the byte. Make sure that we immediately
           * leave the main decompression loop and that the error "SMALL_BUFFER" is returned.
           */
          workspace->curLength = 1U;
        }
      }
      else
      {
        /* Save incomplete input byte. */
        /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/UPDATE/0008,1 */
        workspace->lastEncodingBits   = bitsReadFromInput;
        workspace->lastEncodingBitLen = nrOfBitsReceived;
        workspace->lastEncodingType   = CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_INCOMPLETE_BYTE;
      }
    }
    else
    {
      /* The indicator bit tells us that we have a compression token at
       * the current input buffer position.
       */

      /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/UPDATE/0005,1 */

      /* Try to read the token from the input buffer. */
      nrOfBitsRequested = workspace->tokenSize;
      nrOfBitsReceived =
        Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_ReadBitsFromArray
        (
          localInputBuffer,
          &localInputBufferBitPos,
          localInputBufferByteLen,
          nrOfBitsRequested,
          &localInputBufferBytePos,
          &bitsReadFromInput
        );

      /* Check if the token could be read completely. */
      if(nrOfBitsRequested == nrOfBitsReceived)
      {
        /* The token was read completely. Check if it is the EOS token. Otherwise, try to decode
         * the token and write the decompressed bytes to the output buffer.
         */
        if(CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_IS_EOS_TOKEN(bitsReadFromInput, nrOfBitsReceived))
        {
          /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/UPDATE/0006,1 */
          workspace->EOSFound = TRUE;
        }
        else
        {
          localOutputBufferBytePos =
            Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_DecodeEncoding
            (
               primitive,
               localOutputBuffer,
               localOutputBufferByteLen,
               localOutputBufferBytePos,
               bitsReadFromInput
            );
        }
      }
      else
      {
        /* Save incomplete token. */
        /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/UPDATE/0008,1 */
        workspace->lastEncodingBits   = bitsReadFromInput;
        workspace->lastEncodingBitLen = nrOfBitsReceived;
        workspace->lastEncodingType   = CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_INCOMPLETE_TOKEN;
      }
    }
  } /* end of main decompression loop */

  if ( workspace->state == CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_DECOMPRESS_S_ILLEGAL )
  {
    /* An error occurred during decompression. */
    result = E_NOT_OK;
  }
  else
  if
  (
    (
       (localInputBufferBytePos >= localInputBufferByteLen) ||
       (TRUE == workspace->EOSFound)
    ) &&
    (workspace->curLength == 0U)
  )
  {
    /* We have processed the whole input buffer (or we have encountered the EOS token) and we have
     * written all decoded bytes to the output buffer.
     */
    result = E_OK;
  }
  else
  {
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/UPDATE/0009,1 */
    result = CRYPTO_E_SMALL_BUFFER;
  }

  if (E_OK != result)
  {
    (void) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_DecompressEnd(primitive);
  }

  workspace->blockOutputLength += localOutputBufferBytePos;

  /* Return the size of compressed data (the result) which was written to the output buffer. */
  *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr) = workspace->blockOutputLength;

  workspace->smResult = result;

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle --------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Start2Update,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_WorkspaceType);

  Std_ReturnType result      = E_NOT_OK;

  /* Get the configuration information from the key length and parse the configuration bits. */
  uint32  configurationBits          =  job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength;
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/START/0002,1 */
  uint8   tokenLengthElementSize     =  (configurationBits & 0x000FUL);
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/START/0005,1 */
  boolean lengthInFrontOfPosition    =  (configurationBits & 0x1000UL) >> 12;
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/START/0006,1 */
  boolean posCountsFromStartOfBuffer =  (configurationBits & 0x2000UL) >> 13;
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/START/0007,1 */
  boolean useEOSToken                =  (configurationBits & 0x4000UL) >> 14;

  /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/START/0003,1 */
  workspace->tokenSize           = ((configurationBits & 0x00F0UL) >> 4) + 8UL;

  /* Our code expects that the EOS token is used, that the length information is in front of
   * the position information in the compression token, and that the "position" element of the token
   * contains the position from the start of the array which contains the ring buffer. We also
   * expect that only the actually used configuration bits are set and we expect that the size of
   * the length element in the token is smaller than the complete token size, so that there is at
   * least one bit left in the token to store the position.
   */
  if
  (
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/START/0009,1 */
    (1U                     == useEOSToken                             ) &&
    (1U                     == lengthInFrontOfPosition                 ) &&
    (1U                     == posCountsFromStartOfBuffer              ) &&
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/START/0001,1 */
    (configurationBits      <= CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_MAX_CONFIG_VALUE) &&
    (tokenLengthElementSize <  workspace->tokenSize                    )
  )
  {
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/START/0004,1 */
    workspace->lengthThreshold = ((configurationBits & 0x0F00UL) >> 8);

    workspace->tokenPositionSize = workspace->tokenSize - tokenLengthElementSize;

    workspace->lengthMask = CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_CREATE_BITMASK(tokenLengthElementSize);
    workspace->positionMask = CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_CREATE_BITMASK(workspace->tokenPositionSize);

    workspace->lookBackBufferSize = ((uint32)1UL << workspace->tokenPositionSize);

    /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/START/0008,1 */
    if (    (NULL_PTR != primitive->cnfg->heap)
         && (primitive->cnfg->heapSize >= workspace->lookBackBufferSize)
       )
    {
      workspace->rawBufferPtr = (P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))primitive->cnfg->heap;
      result = E_OK;
    }

    if (E_OK == result)
    {
        workspace->state              = CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_DECOMPRESS_S_INITIALIZED;
        workspace->curPosition        = 0x00U;
        workspace->curLength          = 0x00U;
        workspace->outputLength       = 0U;
        workspace->blockOutputLength  = 0U;
        workspace->inputBytesFetched  = 0U;
        workspace->lastEncodingBits   = 0U;
        workspace->lastEncodingBitLen = 0U;
        workspace->lastEncodingType   = CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_EMPTY;
        workspace->EOSFound           = FALSE;

        (void) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_CommonRingBufferInit
               (
                 workspace->rawBufferPtr,
                 primitive->cnfg->heapSize,
                 &(workspace->ringBuffer),
                 workspace->lookBackBufferSize,
                 1U
               );
    }
  }

  CRYPTO_XVIX_XAIX_SET_SMRESULT_START(result, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_WorkspaceType));

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess ----------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Update2Update,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_WorkspaceType);

  TS_PARAM_UNUSED(job);

  workspace->inputBytesFetched = 0U;
  workspace->outputLength = *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr);

  workspace->blockOutputLength = 0U;

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle ----------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Update2Finish,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_WorkspaceType);

  CRYPTO_XVIX_XAIX_SET_SMRESULT_UPDATE(workspace->smResult, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateDecompress2UpdateProcess ------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateDecompress2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_WorkspaceType);

  TS_PARAM_UNUSED(job);

  workspace->mLvl  = 0U;

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishExec2StartIdle --------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Finish2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) oputBufLenPtr;

  oputBufLenPtr = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr;

  result = Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_DecompressEnd(primitive);

  /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/FINISH/0005,1 */
  if (CRYPTO_OPERATIONMODE_SINGLECALL != job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode)
  {
    *oputBufLenPtr = 0;
  }

  TS_MemBZero(workspace->M, CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_LZSS_STREAMBIT_BLOCKSIZE);

  CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH(workspace->smResult, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_WorkspaceType));

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle ------------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveCancel2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_WorkspaceType);

  /* !LINKSTO Crypto.Asr.SWS_Crypto_00183,2 */
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00144,1 */
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00181_1,1 */
  CRYPTO_XVIX_XAIX_SET_SMRESULT_CANCEL(CRYPTO_E_JOB_CANCELED, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/*----[Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_CopyBytesFromLookBack]---------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_CopyBytesFromLookBack
(
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType,       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
  P2VAR(uint8,                                     AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) outputBuffer,
  VAR(uint32,                                      AUTOMATIC                            ) outputBufferLen,
  VAR(uint32,                                      AUTOMATIC                            ) outputBufferPos
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_WorkspaceType);

  uint32 localLength              = workspace->curLength;
  uint32 localOutputBufferBytePos = outputBufferPos;
  uint32 currentPos               = workspace->curPosition;

  /* Loop while we still have bytes to copy and we still have space left in the output buffer. */
  while ( (localLength              > 0U             ) &&
          (localOutputBufferBytePos < outputBufferLen)
        )
  {
    outputBuffer[localOutputBufferBytePos] =
      CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_RINGBUFFER_READ_FROM_POS(&(workspace->ringBuffer), currentPos);

    /* Push the byte to the lookback buffer. */
    Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_CommonRingBufferPush
    (
      &(workspace->ringBuffer),
        outputBuffer[localOutputBufferBytePos]
    );

    localLength--;
    localOutputBufferBytePos++;
    currentPos++;
  }

  workspace->curLength = localLength;

  return localOutputBufferBytePos;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/*----[Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_DecodeEncoding]----------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_DecodeEncoding
(
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType,       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
  P2VAR(uint8,                                     AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) outputBuffer,
  VAR(uint32,                                      AUTOMATIC                            ) outputBufferLen,
  VAR(uint32,                                      AUTOMATIC                            ) outputBufferPos,
  VAR(uint32,                                      AUTOMATIC                            ) token
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_WorkspaceType);

  uint32 localOutputBufferBytePos = 0U;

  /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/GENERAL/0005,1 */
  /* Extract the length from the encoding. */
  workspace->curLength = (token & workspace->lengthMask) + workspace->lengthThreshold;

  /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/GENERAL/0005,1 */
  /* Extract the position from the encoding. */
  workspace->curPosition =
    (token >> (workspace->tokenSize - workspace->tokenPositionSize)) & workspace->positionMask;

  /* Was the decoding correct? */
  /* Deviation MISRAC2012-2 <START> */
  if(CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_RINGBUFFER_IS_POS_FILLED(&(workspace->ringBuffer), workspace->curPosition))
  /* Deviation MISRAC2012-2 <STOP> */
  {
    localOutputBufferBytePos =
      Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_CopyBytesFromLookBack
      (
        primitive,
        outputBuffer,
        outputBufferLen,
        outputBufferPos
      );
  }
  else
  {
    /* The position is greater than the fill size of the ring buffer. This is an error. The data
     * seems to be corrupt. The decompression has failed.
     */
    workspace->state = CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_DECOMPRESS_S_ILLEGAL;
    localOutputBufferBytePos = outputBufferLen;
  }

  return localOutputBufferBytePos;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/*----[Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_DecompressEnd]-----------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_DecompressEnd
(
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType,       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBIT_WorkspaceType);

  Std_ReturnType locRetVal = E_NOT_OK;

  /* Check if there is an incomplete token left to process and if that incomplete token
   * indicates the end of the stream.
   */
  /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/FINISH/0001,1 */
  if
  (
    (FALSE == workspace->EOSFound) &&
    (CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_INCOMPLETE_TOKEN == workspace->lastEncodingType) &&
    (CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_IS_EOS_TOKEN(workspace->lastEncodingBits, workspace->lastEncodingBitLen))
  )
  {
    workspace->EOSFound = TRUE;
    workspace->lastEncodingType = CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_EMPTY;
  }

  if
  (
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/FINISH/0002,1 */
    (workspace->lastEncodingType == CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_EMPTY ) &&
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/FINISH/0003,1 */
    (workspace->EOSFound == TRUE )
  )
  {
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBIT/FINISH/0004,1 */
    locRetVal= E_OK;
  }

  workspace->state = CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_DECOMPRESS_S_IDLE;

  workspace->smResult = locRetVal;

  return locRetVal;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/*----[Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_CommonRingBufferPush]------------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_CommonRingBufferPush
(
  P2VAR(Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_RingBuffer_Type, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer,
  VAR(uint8,                                 AUTOMATIC                            ) byte
)
{
  uint32 end = 0U;

  /* new end position where to insert 'byte' */
  end = (buffer->start + buffer->level) % buffer->size;

  buffer->array[end] = byte;

  if (buffer->level == buffer->size)
  {
    buffer->start = (buffer->start + 1U) % buffer->size;
  }
  else
  {
    buffer->level++;
  }
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/*----[Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_CommonRingBufferInit]------------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_CommonRingBufferInit
(
  P2VAR(uint8,                                  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) array,
    VAR(uint32,                                 AUTOMATIC                            ) arrayLen,
  P2VAR(Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_RingBuffer_Type,    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer,
    VAR(uint32,                                 AUTOMATIC                            ) bufferLen,
    VAR(uint32,                                 AUTOMATIC                            ) bufferStart
)
{
  Std_ReturnType retVal = E_NOT_OK;
  uint32        locLoop = 0U;

  Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_RingBuffer_Type locBuffer;

  /* The FALSE branch cannot be covered as this function is called only from LZSS_STREAMBIT algorithm in which
   * enough space is reserved at compile time, therefore arrayLen is always bigger than bufferLen.
   * Nevertheless, for completness and further uses this check needs to be kept. */
  /* CHECK: NOPARSE */
  if ( bufferLen <= arrayLen )
  /* CHECK: PARSE */
  {
    for ( locLoop=0U; locLoop<bufferLen; locLoop++ )
    {
      array[locLoop] = 0U;
    }

    locBuffer.array = array;
    locBuffer.size  = bufferLen;
    locBuffer.level = 0U;
    locBuffer.start = bufferStart;

    *buffer         = locBuffer;

    retVal = E_OK;
  }

  return retVal;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

/*----[Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_ReadBitsFromArray]------------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON)
static FUNC(uint8, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBIT_ReadBitsFromArray
(
  P2CONST(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) input,
    P2VAR(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) inputBitPosPtr,
      VAR(uint32, AUTOMATIC                            ) inputByteLen,
      VAR(uint8,  AUTOMATIC                            ) nrOfBitsToRead,
    P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) inputBytePosPtr,
    P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) outputBitsPtr
)
{
  uint32 outputBits                = 0U;
  uint8  outputBitPos              = 0U;
  uint8  nrOfBitsToReadLeft        = 0U;
  uint8  nrOfBitsToReadInFirstByte = 0U;
  uint32 inputBytePos              = *inputBytePosPtr;
  uint8  inputBitPos               = *inputBitPosPtr;

  /* Check if we have enough input bits to completely fufill the request and, if not, shorten the
   * request.
   */
  nrOfBitsToRead =
    (uint8)CRYPTO_XVIX_XAIX_MIN
    (
      nrOfBitsToRead,
      ((uint32)(inputByteLen - inputBytePos) * CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_NR_OF_BITS_IN_BYTE) - (uint32)inputBitPos
    );

  /* Check whether we even have to read any bits. */
  if(nrOfBitsToRead > 0U)
  {
    nrOfBitsToReadLeft = nrOfBitsToRead;

    /* Compute how many bits to read from the first input byte. */
    nrOfBitsToReadInFirstByte =
      (uint8)CRYPTO_XVIX_XAIX_MIN(nrOfBitsToReadLeft, (CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_NR_OF_BITS_IN_BYTE - inputBitPos));

    /* Read the bits from the first input byte and use them as the most significant bits of outputBits. */
    outputBitPos = nrOfBitsToRead - nrOfBitsToReadInFirstByte;
    outputBits |=
      CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_GET_BITS_FROM_BYTE
      (
        input[inputBytePos],
        inputBitPos,
        nrOfBitsToReadInFirstByte
      ) << outputBitPos;

    /* Now we have read the bits from the first byte. Adapt the position in the input byte and the
     * number of bits still to read.
     */
    inputBitPos += nrOfBitsToReadInFirstByte;
    nrOfBitsToReadLeft -= nrOfBitsToReadInFirstByte;

    /* Check if we have used up all bits of the first input byte. If we have not done so, the request
     * is already completely fulfilled and we do not need to read any more input bits.
     */
    if(CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_NR_OF_BITS_IN_BYTE == inputBitPos)
    {
      /* We still have to read further input bits. */

      /* We have completely used up the first input byte. Go to the next input byte. */
      inputBitPos = 0;
      inputBytePos++;

      while(nrOfBitsToReadLeft >= CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_NR_OF_BITS_IN_BYTE)
      {
        /* As long as we have at least 8 bits to read from the input, we can simply read complete bytes
         * and shift them to the correct position in the outputBits.
         */
        outputBitPos -= (uint8)CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_NR_OF_BITS_IN_BYTE;
        outputBits |= (uint32)input[inputBytePos] << outputBitPos;
        nrOfBitsToReadLeft -= (uint8)CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_NR_OF_BITS_IN_BYTE;
        inputBytePos++;
      }

      /* Do we still have to read bits from the last input byte? */
      if(nrOfBitsToReadLeft > 0U)
      {
        outputBits |=
          CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBIT_GET_BITS_FROM_BYTE
          (
            input[inputBytePos],
            inputBitPos,
            nrOfBitsToReadLeft
          );

        inputBitPos += nrOfBitsToReadLeft;
      }
    }
  }

  /* Store the bits that we have read, the new bit position in the current input byte and the
   * new byte position in the input array.
   */
  *outputBitsPtr   = outputBits;
  *inputBitPosPtr  = inputBitPos;
  *inputBytePosPtr = inputBytePos;

  /* The return value is the number of bits that we have actually read from the input. */
  return nrOfBitsToRead;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBIT == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[end of file]=================================================================*/

