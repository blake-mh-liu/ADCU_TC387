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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_DECRYPT_LZSS_STREAMBYTE.c/0001,1 */

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

#include <Crypto_xVIx_xAIx_Int.h>                                  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_DECRYPT_LZSS_STREAMBYTE.c/0002,1 */
#include <Crypto_xVIx_xAIx_Int_KeyManagement.h>                    /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_DECRYPT_LZSS_STREAMBYTE.c/0003,1 */
#include <Crypto_xVIx_xAIx_Int_CPr_DECRYPT_LZSS_STREAMBYTE.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_DECRYPT_LZSS_STREAMBYTE.c/0004,1 */

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

/** \brief  The  minimum number of bits of length in a two-byte (lenght/offset) encoding
 **/
#if (defined CRYPTO_XVIX_XAIX_MIN_LEN_BITS_DECOMPRESS)
#error CRYPTO_XVIX_XAIX_MIN_LEN_BITS_DECOMPRESS already defined
#endif
#define  CRYPTO_XVIX_XAIX_MIN_LEN_BITS_DECOMPRESS 2U

/** \brief  The  maximum number of bits of length in a two-byte (lenght/offset) encoding
 **/
#if (defined CRYPTO_XVIX_XAIX_MAX_LEN_BITS_DECOMPRESS)
#error CRYPTO_XVIX_XAIX_MIN_LEN_BITS_DECOMPRESS already defined
#endif
#define  CRYPTO_XVIX_XAIX_MAX_LEN_BITS_DECOMPRESS 8U

/** \brief  The  maximum number of bits of length and offset encoding
 **/
#if (defined CRYPTO_XVIX_XAIX_MAX_BITS_LEN_OFFSET)
#error CRYPTO_XVIX_XAIX_MAX_BITS_LEN_OFFSET already defined
#endif
#define  CRYPTO_XVIX_XAIX_MAX_BITS_LEN_OFFSET 16UL

/** \brief  Internal states of the DECRYPT_LZSS_STREAMBYTE_Decompress.
 **/
#if (defined CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBYTE_DECOMPRESS_S_IDLE)
#error CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBYTE_DECOMPRESS_S_IDLE already defined
#endif
/** \brief  The Idle state of the DECOMPRESS. **/
#define CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBYTE_DECOMPRESS_S_IDLE 0x01U

#if (defined CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBYTE_DECOMPRESS_S_ILLEGAL)
#error CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBYTE_DECOMPRESS_S_ILLEGAL already defined
#endif
/** \brief  The Error state of the DECOMPRESS. **/
#define CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBYTE_DECOMPRESS_S_ILLEGAL 0x02U

#if (defined CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBYTE_DECOMPRESS_S_INITIALIZED)
#error CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBYTE_DECOMPRESS_S_INITIALIZED already defined
#endif
/** \brief  The Initialized state of the DECOMPRESS. **/
#define CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBYTE_DECOMPRESS_S_INITIALIZED 0x03U

/** \brief  A ring buffer offset direction type.
 **/
#if (defined CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBYTE_D_POSITIVE)
#error CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBYTE_D_POSITIVE already defined
#endif
/** \brief  The Positive direction type. **/
#define CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBYTE_D_POSITIVE 0x01U

#if (defined CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBYTE_D_NEGATIVE)
#error CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBYTE_D_NEGATIVE already defined
#endif
/** \brief  The Negative direction type. **/
#define CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBYTE_D_NEGATIVE 0x02U

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(boolean, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_GetNextState
(
  P2VAR(uint8,                                         AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) smStateIndx,
        Crypto_xVIx_xAIx_PrimitiveStateIdentifierType                                         curState,
        Std_ReturnType                                                                        resultAction,
        Crypto_ProcessingType                                                                 jobProcessing,
  P2VAR(Crypto_xVIx_xAIx_PrimitiveStateIdentifierType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) nxtState
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateDecompress
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateDecompress2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/** \brief  Return the number of used elements in a ring buffer with elements of type 'uint8'.
 **
 ** \param[in]  buffer  A pointer to a ring buffer data structure variable that describes a
 **                     ring buffer.
 **
 ** \returns    The number of used elements.
 **
 ** \Reentrancy{Non-reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_CommonRingBufferGetLevel
(
  P2VAR(Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_RingBuffer_Type, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/** \brief  Return the element of type 'uint8' and offset 'Offset' in direction 'Dir' away from the
 **         youngest element in a ring buffer with elements of type 'uint8'.
 **
 ** \param[in]  buffer  A pointer to a ring buffer data structure variable that describes a
 **                     ring buffer.
 ** \param[in]  offset  The offset of the element to read based on the youngest element.
 ** \param[in]  dir     The direction to move through the ring buffer based on the youngest element.
 **
 ** \returns    The element.
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(uint8, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_CommonRingBufferReadFromEnd
(
  P2VAR(Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_RingBuffer_Type, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer,
  VAR(uint32,                                             AUTOMATIC               ) offset,
  VAR(Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_RingBufferOffsetDirection_Type,  AUTOMATIC              ) dir
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/** \brief  Append a new element of type 'uint8' to a ring buffer with elements of type 'uint8'.
 **         Adds a new element at the end of the ring buffer, after its current last element.
 **         The content of this new element is initialized to a copy of 'byte'.
 **
 ** \param[in]  buffer  A pointer to a ring buffer data structure variable that describes a
 **                     ring buffer.
 ** \param[in]  byte    Value to be append.
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_CommonRingBufferPush
(
  P2VAR(Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_RingBuffer_Type, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer,
  VAR(uint8,                                 AUTOMATIC                            ) byte
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_CommonRingBufferInit
(
  P2VAR(uint8,                                  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) array,
    VAR(uint32,                                 AUTOMATIC                            ) arrayLen,
  P2VAR(Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_RingBuffer_Type,    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer,
    VAR(uint32,                                 AUTOMATIC                            ) bufferLen
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/** \brief  Write out decompressed data into output buffer.
 **
 ** \param[in,out]  job                 Pointer to the configuration of the job this primitive shall be
 **                                     processed for. This contains structures with job and primitive
 **                                     relevant information but also pointers to result buffers.
 ** \param[in]      primitive           Pointer to the data structure describes the current primitive.
 ** \param[in,out]  argOputBuf          Holds a pointer to the memory location where the
 **                                     decompressed data shall be stored.
 ** \param[in]      argOputBufLen       Holds a pointer to a memory location in which the length
 **                                     information is stored.
 ** \param[in]      argOputBufPos       The current position in argOputBuf where to insert
 **                                     decompressed data.
 **
 ** \returns  The new position in argOputBuf where to insert further decompressed data.
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_CopyBytesFromLookBack
(
  P2VAR(Crypto_JobType,                            AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType,       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
  P2VAR(uint8,                                     AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) argOputBuf,
  VAR(uint32,                                      AUTOMATIC                            ) argOputBufLen,
  VAR(uint32,                                      AUTOMATIC                            ) argOputBufPos
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/** \brief  Interprets a two byte block of compressed data as tuple of offset and length and
 **         calls Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_CopyBytesFromLookBack.
 **
 ** \param[in,out]  job                 Pointer to the configuration of the job this primitive shall be
 **                                     processed for. This contains structures with job and primitive
 **                                     relevant information but also pointers to result buffers.
 ** \param[in]      primitive           Pointer to the data structure describes the current primitive.
 ** \param[in,out]  argOputBuf          Holds a pointer to the memory location where the
 **                                     decompressed data shall be stored.
 ** \param[in]      argOputBufLen       Holds a pointer to a memory location in which the length
 **                                     information is stored.
 ** \param[in]      argOputBufPos       The current position in argOputBuf where to insert
 **                                     decompressed data.
 ** \param[in]      argEncoding         The current two byte block of compressed data.
 **
 ** \returns  The new position in argOputBuf where to insert further decompressed data.
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_DecodeEncoding
(
  P2VAR(Crypto_JobType,                            AUTOMATIC,      CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType,       AUTOMATIC,      CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
  P2VAR(uint8,                                     AUTOMATIC,      CRYPTO_xVIx_xAIx_APPL_DATA) argOputBuf,
  VAR(uint32,                                      AUTOMATIC                            ) argOputBufLen,
  VAR(uint32,                                      AUTOMATIC                            ) argOputBufPos,
  VAR(uint16,                                      AUTOMATIC                            ) argEncoding
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/** \brief  Complete DECRYPT_LZSS_STREAMBYTE decompression computation and reset parts of the context.
 **
 ** \param[in,out]  job                 Pointer to the configuration of the job this primitive shall be
 **                                     processed for. This contains structures with job and primitive
 **                                     relevant information but also pointers to result buffers.
 ** \param[in]      primitive           Pointer to the data structure describes the current primitive.

 **
 ** \returns  Error value.
 **
 ** \retval   E_OK                      Request successful.
 ** \retval   E_NOT_OK                  Request failed.
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_DecompressEnd
(
  P2VAR(Crypto_JobType,                            AUTOMATIC,      CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType,       AUTOMATIC,      CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal constants]==========================================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  The primitives state transition table. **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_StateTransitionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateTransitionType, CRYPTO_xVIx_xAIx_CONST)
Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Process_StateTransitionTable[CRYPTO_XVIX_XAIX_STATETRANSITIONTABLE_COUNT] =
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/** \brief  The primitives state action table. **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_StateActionTable/0001,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static CONST(Crypto_xVIx_xAIx_PrimitiveStateActionType, CRYPTO_xVIx_xAIx_CONST)
Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Process_StateActionTable[CRYPTO_XVIX_XAIX_STATEACTIONTABLE_COUNT] =
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Process ---------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Process/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Process
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType);

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
    (void) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Reset(workspace->paObjectId, job, primitive);
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
        (void) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Main(objectId, job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Main ------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Main/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Main
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType);

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
    if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Process_StateActionTable[curState].fcnAction))
    {
      resultAction = Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Process_StateActionTable[curState].fcnAction(job, primitive);
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
     * The return value of GetNextState cannot be FALSE for DECRYPT_LZSS_STREAMBYTE, because the state machine
     * transition table for this cryptographic primitive is complete.
     */
    if (TRUE == nxtStateFound)
    /* CHECK: PARSE */
    {
      workspace->smStateIndx = smStateIndx;
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Main/0010,1 */
      if (NULL_PTR != (Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Process_StateTransitionTable[smStateIndx].fcnTransition))
      {
        /* transition function returns using workspace->smResult */
        (void) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Process_StateTransitionTable[smStateIndx].fcnTransition(job, primitive);

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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Cancel ----------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Cancel/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Cancel
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType);

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
      (void) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Main(objectId, job, primitive);
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Reset -----------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Reset/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Reset
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as
   * secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESET(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType));
    result = E_OK;
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Restart -----------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Restart/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Restart
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(objectId);

  /* CHECK: NOPARSE
   * The IF clause is only reachable for cryptographic primitives that are used as secondary primitives.
   */
  if (NULL_PTR != workspace->paPrimitive)
  {
    CRYPTO_XVIX_XAIX_SET_SMRESULT_RESTART(E_OK, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType));
  }
  else
  {
    result = E_OK;
  }
  /* CHECK: PARSE */

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/*--- Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Callback --------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Callback/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
/* CHECK: NOPARSE
 * This API is only reachable for cryptographic primitives that are using a secondary primitive.
 */
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType);

  TS_PARAM_UNUSED(objectId);
  TS_PARAM_UNUSED(job);
  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CPr_SERVICE_FAMILY_MODE_Callback/0002,1 */
  workspace->notifyType   = cbkType;
  workspace->notifyResult = cbkResult;

  return E_OK;
}
/* CHECK: PARSE */
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--- Crypto_xVIx_xAIx_StateMachine_Error2StartIdle ----------------------------------------------*/

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveError2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Error2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType);

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
  result              = Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Reset(workspace->paObjectId, job, primitive);
  workspace->smResult = smResult;

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/*--- Crypto_xVIx_xAIx_GetNextState --------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
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
    if (   (Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx   = i;
      break;
    }
  }

  /* 2) iterate from first table entry to last found entry in table */
  for (i = 0U; (FALSE == nxtStateFound) && (i < *smStateIndx); i++)
  {
    if (   (Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Process_StateTransitionTable[i].curState == curState    )
        && (Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Process_StateTransitionTable[i].event    == resultAction)
        && (   (Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Process_StateTransitionTable[i].processingType == jobProcessing                   )
            || (Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Process_StateTransitionTable[i].processingType == CRYPTO_XVIX_XAIX_PROCESSING_BOTH)
           )
       )
    {
      *nxtState      = Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Process_StateTransitionTable[i].nxtState;
       nxtStateFound = TRUE;
      *smStateIndx  = i;
      break;
    }
  }

  return nxtStateFound;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateProcess ---------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType);

  Std_ReturnType                            result      = E_NOT_OK;
  uint32                                    bytesRemain = 0U;
  uint8                                     bytesFetch  = 0U;
  P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) m = (P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)) workspace->M;

  /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBYTE/UPDATE/0001,1 */
  bytesRemain = (job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength - workspace->inputBytesFetched);
  bytesFetch  = (uint8) CRYPTO_XVIX_XAIX_MIN(((uint32) CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_LZSS_STREAMBYTE_BLOCKSIZE - workspace->mLvl),
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateDecompress --------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateDecompress
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType);

  Std_ReturnType result          = E_NOT_OK;
  uint32 locIputBufLen           = workspace->mLvl;
  uint32 locOputBufLen           = workspace->outputLength;
  uint32 locIputBufPos           = 0U;
  uint32 locOputBufPos           = 0U;

  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) argIputBuf;
  P2VAR(uint8,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) argOputBuf;

  /* We start at the beginning of input and output buffers. */
  argIputBuf = workspace->M;

  argOputBuf = &job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr[workspace->blockOutputLength];

  /* Determine if a incomplete encoding was detected the last run. */
  if ( workspace->encIncomplete == TRUE )
  {
    /* Combine the byte stored in the last run and the first byte of the
     * input buffer to create a complete encoding and decode that encoding.
     */
    locOputBufPos = Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_DecodeEncoding
                    (
                      job,
                      primitive,
                      argOputBuf,
                      locOputBufLen,
                      locOputBufPos,
                      ( (uint16)((uint16)workspace->encByte << 8U) | (uint16)argIputBuf[0U] )
                    );

    workspace->encIncomplete = FALSE;

    locIputBufPos = 1U;
  }
  else
  {
    /* Nothing to do. */
  }

  /* Main decompression loop */
  while ( (locIputBufPos < locIputBufLen) &&
          (locOputBufPos < locOputBufLen)
        )
  {
    /* Is the indicator byte fully processed? */
    if ( workspace->flgByteMask == 0U )
    {
       /* Get the next indicator byte from the input and reset the bit mask. */
       workspace->flgByteMask = CRYPTO_XVIX_XAIX_DECOMPRESS_SET_BYTE_MSB;
       workspace->flgByte     = argIputBuf[locIputBufPos];
       locIputBufPos++;
    }
    else
    {
      /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBYTE/UPDATE/0002,1 */
      /* Check the current bit of the indicator byte. */
      if ( (workspace->flgByte & workspace->flgByteMask) == 0U )
      {
        /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBYTE/UPDATE/0003,1 */
        /* The indicator byte tells us that there is a single byte at the
         * current position in the input buffer.
         */

        /* Simply copy the current byte to the end of the dictionary. */
        Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_CommonRingBufferPush( &(workspace->rngBuffer), argIputBuf[locIputBufPos] );

        /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBYTE/GENERAL/0003,1 */
        /* Simply copy the current byte to the end of the output buffer. */
        argOputBuf[locOputBufPos] = argIputBuf[locIputBufPos];
        locOputBufPos++;

        /* The current byte is processed, move one byte on. */
        locIputBufPos++;
      }
      else
      {
        /* The indicator byte tells us that we have a two-byte encoding at
         * the current input buffer position.
         */
        /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBYTE/UPDATE/0004,1 */
        if ( (locIputBufPos + 1U) < locIputBufLen )
        {
          /* We still have two bytes left in the input buffer. Decode those two bytes. */
          locOputBufPos = Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_DecodeEncoding
                          (
                             job,
                             primitive,
                             argOputBuf,
                             locOputBufLen,
                             locOputBufPos,
                             (
                               (uint16)((uint16)argIputBuf[locIputBufPos     ] << 8U) |
                               (uint16)         argIputBuf[locIputBufPos + 1U]
                             )
                          );

          /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBYTE/UPDATE/0005,1 */
          /* Two bytes were processed. */
          locIputBufPos += 2U;
        }
        else
        {
          /* We only have one byte left in the input buffer. Store that
           * byte for the next call of this function.
           */
          workspace->encByte        = argIputBuf[locIputBufPos];
          workspace->encIncomplete  = TRUE;
          locIputBufPos++;
        }
      }

      /* Go on to the next bit in the indicator byte which indicates an
       * encoding or a single byte.
       */
      workspace->flgByteMask >>= 1U;
    }
  } /* end of main decompression loop */

  if ( workspace->state == CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBYTE_DECOMPRESS_S_ILLEGAL )
  {
    /* An error occurred during decompression. */
    result = E_NOT_OK;
  }
  else
  if ( (locIputBufPos     >= locIputBufLen) &&
       (workspace->curLength == 0U           )
     )
  {
    /* We have processed the whole input buffer and we have written all
     * decoded bytes to the output buffer.
     */
    result = E_OK;
  }
  else
  {
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBYTE/UPDATE/0006,1 */
    result = CRYPTO_E_SMALL_BUFFER;
  }

  if (E_OK != result)
  {
    (void) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_DecompressEnd(job, primitive);
  }

  workspace->blockOutputLength += locOputBufPos;

  /* Return the size of compressed data (the result) which was written to the buffer oputBuf. */
  *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr) = workspace->blockOutputLength;

  workspace->smResult = result;

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle --------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Start2Update,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_StartExec2UpdateIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType);

  uint32 lengthBitsPerBlock  = job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength;
  uint16 maxSizeBufLookBack  = 0U;
  Std_ReturnType result      = E_NOT_OK;

  /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBYTE/START/0001,1 */
  if ( (lengthBitsPerBlock >= CRYPTO_XVIX_XAIX_MIN_LEN_BITS_DECOMPRESS) &&
       (lengthBitsPerBlock <= CRYPTO_XVIX_XAIX_MAX_LEN_BITS_DECOMPRESS)
     )
  {
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBYTE/GENERAL/0004,1 */
    maxSizeBufLookBack = (uint16)((1UL << (CRYPTO_XVIX_XAIX_MAX_BITS_LEN_OFFSET - (uint16)(lengthBitsPerBlock))) - 1UL);

    /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBYTE/START/0003,1 */
    if (     (NULL_PTR != primitive->cnfg->heap)
         && (primitive->cnfg->heapSize >= maxSizeBufLookBack)
       )
    {
      workspace->shftLength = (uint16)(CRYPTO_XVIX_XAIX_MAX_BITS_LEN_OFFSET - lengthBitsPerBlock);
      workspace->maskLength = (uint16)((1UL << lengthBitsPerBlock) - 1UL);
      workspace->maskOffset = (uint16)((1UL << (CRYPTO_XVIX_XAIX_MAX_BITS_LEN_OFFSET - lengthBitsPerBlock)) - 1UL);
      workspace->sizeBufLookBack = maxSizeBufLookBack;
      workspace->rawBufferptr = (P2VAR(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))primitive->cnfg->heap;
      result = E_OK;
    }
  }

  /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBYTE/START/0002,1 */
  if (E_OK == result)
  {
      workspace->state         = CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBYTE_DECOMPRESS_S_INITIALIZED;
      (void) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_CommonRingBufferInit
             (
               workspace->rawBufferptr,
               primitive->cnfg->heapSize,
               &(workspace->rngBuffer),
               workspace->sizeBufLookBack
             );

      workspace->curOffset             = 0x00U;
      workspace->curLength             = 0x00U;
      workspace->flgByte               = 0x00U;
      workspace->flgByteMask           = 0x00U;
      workspace->encByte               = 0x00U;
      workspace->encIncomplete         = FALSE;

      workspace->outputLength          = 0U;
      workspace->blockOutputLength     = 0U;
  }

  CRYPTO_XVIX_XAIX_SET_SMRESULT_START(result, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType));

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess ----------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Update2Update,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateExec2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType);

  TS_PARAM_UNUSED(job);

  workspace->inputBytesFetched = 0U;
  workspace->outputLength = *(job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr);

  workspace->blockOutputLength = 0U;

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle ----------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Update2Finish,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateProcess2UpdateFinishIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType);

  CRYPTO_XVIX_XAIX_SET_SMRESULT_UPDATE(workspace->smResult, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_UpdateDecompress2UpdateProcess ------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_UpdateDecompress2UpdateProcess
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType);

  TS_PARAM_UNUSED(job);

  workspace->mLvl  = 0U;

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_FinishExec2StartIdle --------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.Finish2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_FinishExec2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
    CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType);

  Std_ReturnType result = E_NOT_OK;

  P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) oputBufLenPtr;

  oputBufLenPtr = job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr;

  result = Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_DecompressEnd(job, primitive);

  /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBYTE/FINISH/0003,1 */
  if (CRYPTO_OPERATIONMODE_SINGLECALL != job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode)
  {
    *oputBufLenPtr = 0;
  }

  TS_MemBZero(workspace->M, CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_LZSS_STREAMBYTE_BLOCKSIZE);

  CRYPTO_XVIX_XAIX_SET_SMRESULT_FINISH(workspace->smResult, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType));

  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/* --- Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle ------------------------------------------- */

/* !LINKSTO Crypto.Dsn.JobTransition.ActiveCancel2Idle,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_StateMachine_Cancel2StartIdle
(
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType);

  /* !LINKSTO Crypto.Asr.SWS_Crypto_00183,2 */
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00144,1 */
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00181_1,1 */
  CRYPTO_XVIX_XAIX_SET_SMRESULT_CANCEL(CRYPTO_E_JOB_CANCELED, sizeof(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType));

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/*----[Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_CopyBytesFromLookBack]---------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_CopyBytesFromLookBack
(
  P2VAR(Crypto_JobType,                            AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType,       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
  P2VAR(uint8,                                     AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) argOputBuf,
  VAR(uint32,                                      AUTOMATIC                            ) argOputBufLen,
  VAR(uint32,                                      AUTOMATIC                            ) argOputBufPos
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType);

  uint32 locLength     = 0U;
  uint32 locOputBufPos = 0U;

  TS_PARAM_UNUSED(job);

  locLength     = workspace->curLength;
  locOputBufPos = argOputBufPos;

  while ( (locLength     > 0U           ) &&
          (locOputBufPos < argOputBufLen)
        )
  {
    argOputBuf[locOputBufPos] = Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_CommonRingBufferReadFromEnd
                                (
                                  &(workspace->rngBuffer),
                                    workspace->curOffset - 1U,
                                    CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBYTE_D_NEGATIVE
                                );
    Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_CommonRingBufferPush
                                (
                                  &(workspace->rngBuffer),
                                    argOputBuf[locOputBufPos]
                                );
    locLength--;
    locOputBufPos++;
  }

  workspace->curLength = locLength;

  return locOputBufPos;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/*----[Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_DecodeEncoding]----------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_DecodeEncoding
(
  P2VAR(Crypto_JobType,                            AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType,       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
  P2VAR(uint8,                                     AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) argOputBuf,
  VAR(uint32,                                      AUTOMATIC                            ) argOputBufLen,
  VAR(uint32,                                      AUTOMATIC                            ) argOputBufPos,
  VAR(uint16,                                      AUTOMATIC                            ) argEncoding
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType);

  uint32 locOputBufPos = 0U;

  /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBYTE/GENERAL/0005,1 */
  /* Extract the length from the encoding. */
  workspace->curLength = ((uint32)argEncoding >> workspace->shftLength)
                        & workspace->maskLength;

  /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBYTE/GENERAL/0005,1 */
  /* Extract the offset from the encoding. */
  workspace->curOffset = ((uint32)argEncoding                              )
                        & workspace->maskOffset;

  /* Was the decoding correct? */
  if ( (workspace->curLength <= workspace->curOffset                                 ) &&
       (workspace->curOffset <= Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_CommonRingBufferGetLevel(&(workspace->rngBuffer)))
     )
  {
    locOputBufPos = Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_CopyBytesFromLookBack
                    (
                      job,
                      primitive,
                      argOputBuf,
                      argOputBufLen,
                      argOputBufPos
                    );
  }
  else
  {
    /* The string length is greater than the offset or the offset is greater
     * than the actual ring buffer size. This is an error. The data seems to be corrupt.
     * The decompression has failed.
     */
    workspace->state = CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBYTE_DECOMPRESS_S_ILLEGAL;
    locOputBufPos = argOputBufLen;
  }

  return locOputBufPos;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/*----[Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_DecompressEnd]-----------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_DecompressEnd
(
  P2VAR(Crypto_JobType,                            AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType,       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
  CRYPTO_XVIX_XAIX_CAST_WORKSPACETYPE(Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType);

  Std_ReturnType locRetVal = E_NOT_OK;

  TS_PARAM_UNUSED(primitive);
  TS_PARAM_UNUSED(job);

  /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBYTE/FINISH/0001,1 */
  if ( workspace->encIncomplete == TRUE )
  {
    locRetVal= E_NOT_OK;
  }
  else
  if ( workspace->curLength == 0U )
  {
    /* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBYTE/FINISH/0002,1 */
    locRetVal= E_OK;
  }
  else
  {
    /* Do Nothing */
  }

  workspace->state = CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBYTE_DECOMPRESS_S_IDLE;

  workspace->smResult = locRetVal;

  return locRetVal;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/* --- Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_CommonRingBufferGetLevel ------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(uint32, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_CommonRingBufferGetLevel
(
  P2VAR(Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_RingBuffer_Type, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer
)
{
  return (uint32) buffer->level;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/* --- Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_CommonRingBufferReadFromEnd ---------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(uint8, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_CommonRingBufferReadFromEnd
(
  P2VAR(Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_RingBuffer_Type, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer,
  VAR(uint32,                                AUTOMATIC                            ) offset,
  VAR(Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_RingBufferOffsetDirection_Type, AUTOMATIC               ) dir
)
{
  uint8 byte = 0U;
  uint32 end = 0U;

  /* actual end position where to read from */
  end = ((buffer->start + buffer->level) - 1U) % buffer->size;

  /* The TRUE branch cannot be covered as this function is called only from DECRYPT_LZSS_STREAMBYTE algorithm in which
   * the algorithms always reads back with at least an
   * offset of 1(Dir == CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBYTE_D_NEGATIVE && Offset > 0).
   * Nevertheless, for completness and further uses this check needs to be kept. */
  /* CHECK: NOPARSE */
  if ( (offset == 0U            ) ||
       (dir    == CRYPTO_XVIX_XAIX_INT_DECRYPT_LZSS_STREAMBYTE_D_POSITIVE)
     )
  {
    byte = buffer->array[ ((end + offset) % buffer->level) ];
  }
  else
  {
    byte = ( end >= offset )
         ? buffer->array[ end - offset ]
         : buffer->array[ buffer->level - ((offset - end) % buffer->level) ];
  }
  /* CHECK: PARSE */

  return byte;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/*----[Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_CommonRingBufferPush]------------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_CommonRingBufferPush
(
  P2VAR(Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_RingBuffer_Type, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer,
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/*----[Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_CommonRingBufferInit]------------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_CommonRingBufferInit
(
  P2VAR(uint8,                                  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) array,
    VAR(uint32,                                 AUTOMATIC                            ) arrayLen,
  P2VAR(Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_RingBuffer_Type,    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buffer,
    VAR(uint32,                                 AUTOMATIC                            ) bufferLen
)
{
  Std_ReturnType retVal = E_NOT_OK;
  uint32        locLoop = 0U;

  Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_RingBuffer_Type locBuffer;

  /* The FALSE branch cannot be covered as this function is called only from LZSS_STREAMBYTE algorithm in which
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
    locBuffer.start = 0U;

    *buffer         = locBuffer;

    retVal = E_OK;
  }

  return retVal;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[end of file]=================================================================*/

