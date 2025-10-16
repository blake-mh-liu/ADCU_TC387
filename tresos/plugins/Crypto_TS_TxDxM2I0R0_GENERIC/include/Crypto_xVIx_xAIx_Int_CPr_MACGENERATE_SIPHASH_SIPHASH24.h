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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_MACGENERATE_SIPHASH_SIPHASH24.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_INT_CPR_MACGENERATE_SIPHASH_SIPHASH24_H
#define CRYPTO_XVIX_XAIX_INT_CPR_MACGENERATE_SIPHASH_SIPHASH24_H

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int_CPr_MACGENERATE_SIPHASH_SIPHASH24_Cfg.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_MACGENERATE_SIPHASH_SIPHASH24.h/0002,1 */

/*==================[macros]======================================================================*/

/* !LINKSTO Crypto.Req.CPr/MACGENERATE_SIPHASH_SIPHASH24/GENERAL/0005,1 */
#if (defined CRYPTO_XVIX_XAIX_CPR_MACGENERATE_SIPHASH_SIPHASH24_KEY_LEN_BYTES)
#error CRYPTO_XVIX_XAIX_CPR_MACGENERATE_SIPHASH_SIPHASH24_KEY_LEN_BYTES already defined
#endif
/** \brief  The length of the key for the SipHash. **/
#define CRYPTO_XVIX_XAIX_CPR_MACGENERATE_SIPHASH_SIPHASH24_KEY_LEN_BYTES 16U

/* !LINKSTO Crypto.Req.CPr/MACGENERATE_SIPHASH_SIPHASH24/GENERAL/0004,2 */
#if (defined CRYPTO_XVIX_XAIX_CPR_MACGENERATE_SIPHASH_SIPHASH24_BLOCK_LEN_BYTES)
#error CRYPTO_XVIX_XAIX_CPR_MACGENERATE_SIPHASH_SIPHASH24_BLOCK_LEN_BYTES already defined
#endif
/** \brief  The length of one encryption block for the SipHash. **/
#define CRYPTO_XVIX_XAIX_CPR_MACGENERATE_SIPHASH_SIPHASH24_BLOCK_LEN_BYTES 8U

/*==================[type definitions]============================================================*/

/** \brief  Workspace of primitive MACGENERATE_SIPHASH_SIPHASH24.
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
 **         Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Callback().
 **
 ** \var    notifyResult
 ** \brief  The value of the callback result received from a secondary primitive via
 **         Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Callback().
 **
 ** \var    lockMain
 ** \brief  Flag to lock multiple parallel executions of Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Main().
 **
 ** ---specific-------------------------------------------------------------------
 **
 ** \var  MessageBlock
 ** \brief  Containg the data of one message block.
 **
 ** \var  V0
 ** \brief  State variable V0 of the SipHash algorithm.
 **
 ** \var  V1
 ** \brief  State variable V1 of the SipHash algorithm.
 **
 ** \var  V2
 ** \brief  State variable V2 of the SipHash algorithm.
 **
 ** \var  V3
 ** \brief  State variable V3 of the SipHash algorithm.
 **
 ** \var  DataLength
 ** \brief  The length of the data over which the SipHash has to be computed.
 **
 ** \var  TotalNumberOfBytes
 ** \brief  The total number of data bytes already processed.
 **
 ** \var  RemainingBytes
 ** \brief  The number of remaining bytes, i.e. total data length modulo block size.
 **
 ** \var  DataPtr
 ** \brief  A pointer to the start of an array where the data is stored over which
 **         the SipHash has to be computed.
 **
 ** \var  KeyData
 ** \brief  A buffer to hold the key for the processing.
 **/

/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_WorkspaceType/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
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
  uint64 MessageBlock;
  uint64 V0;
  uint64 V1;
  uint64 V2;
  uint64 V3;

  uint32 DataLength;
  uint32 TotalNumberOfBytes;
  uint32 RemainingBytes;

  P2CONST(uint8, TYPEDEF, CRYPTO_xVIx_xAIx_APPL_DATA) DataPtr;

  uint8 KeyData[CRYPTO_XVIX_XAIX_CPR_MACGENERATE_SIPHASH_SIPHASH24_KEY_LEN_BYTES];
}
Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_WorkspaceType;
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Process
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Main
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Cancel
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Reset
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Restart
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_MACGENERATE_SIPHASH_SIPHASH24_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SIPHASH_SIPHASH24 == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_INT_CPR_MACGENERATE_SIPHASH_SIPHASH24_H */

/*==================[end of file]=================================================================*/

