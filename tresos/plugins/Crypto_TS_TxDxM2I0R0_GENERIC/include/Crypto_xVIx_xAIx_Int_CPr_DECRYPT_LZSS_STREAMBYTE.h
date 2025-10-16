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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_DECRYPT_LZSS_STREAMBYTE.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_LZSS_STREAMBYTE_H
#define CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_LZSS_STREAMBYTE_H

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int_CPr_DECRYPT_LZSS_STREAMBYTE_Cfg.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_DECRYPT_LZSS_STREAMBYTE.h/0002,1 */

/*==================[macros]======================================================================*/

/* !LINKSTO Crypto.Req.CPr/DECRYPT_LZSS_STREAMBYTE/GENERAL/0002,1 */
#if (defined CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_LZSS_STREAMBYTE_BLOCKSIZE)
#error CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_LZSS_STREAMBYTE_BLOCKSIZE already defined
#endif
/** \brief  Macro indicating the length of a block in bytes. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_LZSS_STREAMBYTE_BLOCKSIZE 64U

/*==================[type definitions]============================================================*/

/** \brief  Enumeration of the internal states of the DECRYPT_LZSS_STREAMBYTE_Decompress.
 **/
typedef uint8 Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_DecompressState_Type;

/** \brief  A ring buffer offset direction type.
 **/
typedef uint8 Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_RingBufferOffsetDirection_Type;

/** \brief  The structured data type that describes a ring buffer data for LZSS_STREAMBYTE Interface.
 **/
typedef struct
{
  P2VAR(uint8,  TYPEDEF, CRYPTO_xVIx_xAIx_APPL_DATA) array;
  uint32                          size;
  uint32                          level;
  uint32                          start;
}
Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_RingBuffer_Type;

/** \brief  Workspace of primitive DECRYPT_LZSS_STREAMBYTE.
 **
 ** ---common---------------------------------------------------------------------
 **
 ** \var    paObjectId
 ** \brief  Value of the Crypto Driver Object Id the primitive was started with.
 **
 ** \var    paPrimitive
 ** \brief  Pointer to crypto driver objects primitive description.
 **
  ** \var    smStateIndx
 ** \brief  The index of the last found entry in the state transition table.
 **
 ** \var    smState
 ** \brief  The current state of the primitive state machine.
 **
 ** \var    smResult
 ** \brief  The result returned to a calling instance.
 **
 ** \var    smOperationDone
 ** \brief  Value holding the flags of executed operation modes.
 **
 ** \var    notifyType
 ** \brief  The value of the callback type received from a secondary primitive via
 **         Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Callback().
 **
 ** \var    notifyResult
 ** \brief  The value of the callback result received from a secondary primitive via
 **         Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Callback().
 **
 ** \var    lockMain
 ** \brief  Flag to lock multiple parallel executions of Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Main().
 **
 ** ---specific-------------------------------------------------------------------
 **
** \var  shftLength
** \brief  The shift length to access the look back buffer.
**
** \var  maskLength
** \brief  The mask length to access the look back buffer.
**
** \var  maskOffset
** \brief  The mask offset for the look back buffer.
**
** \var  sizeBufLookBack
** \brief  The size of the look back buffer.
**
 ** \var  state
 ** \brief  The internal state machine state.
 **
 ** \var  rawBufferptr
 ** \brief  The DECRYPT_LZSS_STREAMBYTE decompression buffer pointer.
 **
 ** \var  rngBuffer
 ** \brief  The the DECRYPT_LZSS_STREAMBYTE decompression ring buffer where to search offset/length pairs and
 **         that is located in 'Buffer'.
 **
 ** \var  curOffset
 ** \brief  The offset of the current offset/length pair.
 **
 ** \var  curLength
 ** \brief  The length of the current offset/length pair.
 **
 ** \var  flgByte
 ** \brief  byte which indicates whether the next encodings  are literal bytes or
 **         offset/length pairs
 **
 ** \var  flgByteMask
 ** \brief  The current index in the 'flagByte'.
 **
 ** \var  encByte
 ** \brief  The first byte of an incomplete encoding.
 **
 ** \var  encIncomplete
 ** \brief  do we have an incomplete encoding left over from the last call of.
 **         'Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_DecompressUpdate()'?
 **
 ** \var  M
 ** \brief  The message block to process.
 **
 ** \var  mLvl
 ** \brief  The number of bytes in M.
 **
 ** \var  inputBytesFetched
 ** \brief  The number of bytes to take from the input given in an Update or Finish call to
 **         filling up M.
 **
 ** \var  outputLength
 ** \brief  The total output buffer length.
 **
 **  \var  blockOutputLength
 ** \brief  The block size of the decompressed bytes.
 **/

/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
typedef struct
{
  /* ---common--------------------------------------------------------------------- */
  uint32 paObjectId;

  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) paPrimitive;
  uint8                                         smStateIndx;
  boolean                                       lockMain;

  Crypto_xVIx_xAIx_PrimitiveStateIdentifierType smState;
  Std_ReturnType                                smResult;
  Crypto_OperationModeType                      smOperationDone;
  Crypto_xVIx_xAIx_CallbackType                 notifyType;
  Std_ReturnType                                notifyResult;
  /* ---specific------------------------------------------------------------------- */
  uint16                                         shftLength;
  uint16                                         maskLength;
  uint16                                         maskOffset;
  uint16                                         sizeBufLookBack;
  Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_DecompressState_Type       state;
  P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) rawBufferptr;
  Crypto_xVIx_xAIx_DECRYPT_LZSS_STREAMBYTE_RingBuffer_Type            rngBuffer;
  uint32                                         curOffset;
  uint32                                         curLength;
  uint8                                          flgByte;
  uint32                                         flgByteMask;
  uint8                                          encByte;
  boolean                                        encIncomplete;

  uint8                                          M[CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_LZSS_STREAMBYTE_BLOCKSIZE];
  uint8                                          mLvl;
  uint32                                         inputBytesFetched;
  uint32                                         outputLength;
  uint32                                         blockOutputLength;
}
Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_WorkspaceType;
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  Triggers the asynchronous or performs the synchronous processing of the primitive.
 **
 ** \param[in]      objectId   Holds the identifier of the Crypto Driver Object.
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK                   Request successful.
 ** \retval  E_NOT_OK               Request failed.
 ** \retval  CRYPTO_E_JOB_CANCELED  Request failed, because job using this primitive was cancelled.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Process
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/** \brief  Triggers the processing of the primitives state machine.
 **
 ** \param[in]      objectId   Holds the identifier of the Crypto Driver Object.
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Main
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/** \brief  Requests the cancelation of the processing of the primitive.
 **
 ** \param[in]      objectId   Holds the identifier of the Crypto Driver Object.
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Cancel
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/** \brief  Requests the hard reset of the processing of the primitive.
 **
 ** \param[in]      objectId   Holds the identifier of the Crypto Driver Object.
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Reset
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/** \brief  Requests the hard restart of the processing of the primitive.
 **
 ** \param[in]      objectId   Holds the identifier of the Crypto Driver Object.
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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Restart
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

/** \brief  Notifies the primitive about the completion of the request of a secondary primitive.
 **
 ** \param[in]      objectId   Holds the identifier of the Crypto Driver Object.
 ** \param[in,out]  job        Pointer to the configuration of the job this primitive shall be
 **                            processed for. This contains structures with job and primitive
 **                            relevant information but also pointers to result buffers.
 ** \param[in]      primitive  Pointer to the data structure describes the current primitive.
 ** \param[in]      cbkType    The type (none, start, update, finish, cancel) of the callback.
 ** \param[in]      cbkResult  The result of the callback.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK      Request successful.
 ** \retval  E_NOT_OK  Request failed.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_DECRYPT_LZSS_STREAMBYTE_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_DECRYPT_LZSS_STREAMBYTE == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_INT_CPR_DECRYPT_LZSS_STREAMBYTE_H */

/*==================[end of file]=================================================================*/

