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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_RANDOMGENERATE_AES_CTRDRBG.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_H
#define CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_H

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int_CPr_RANDOMGENERATE_AES_CTRDRBG_Cfg.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_RANDOMGENERATE_AES_CTRDRBG.h/0002,1 */

/*==================[macros]======================================================================*/

#if (defined CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_KEYLEN)
#error CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_KEYLEN already defined
#endif
/** \brief The key length for the CTRDRBG according to NIST SP-800-90A */
#define CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_KEYLEN            32U

#if (defined CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_BLOCKLEN)
#error CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_BLOCKLEN already defined
#endif
/** \brief The block length for the CTRDRBG according to NIST SP-800-90A */
#define CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_BLOCKLEN          16U

#if(defined CRYPTO_XVIX_XAIX_KE_RANDOM_SEED_COUNT)
#error CRYPTO_XVIX_XAIX_KE_RANDOM_SEED_COUNT is already defined
#endif
/** \brief Key element which can be used together with the key element CRYPTO_KE_RANDOM_SEED_STATE
 *         to store the seed count.
 */
#define CRYPTO_XVIX_XAIX_KE_RANDOM_SEED_COUNT         1005U

#if (defined CRYPTO_XVIX_XAIX_MAX_SEED_COUNT)
#error CRYPTO_XVIX_XAIX_MAX_SEED_COUNT already defined
#endif
/** \brief The reseed counter limit 2^32-1 */
#define CRYPTO_XVIX_XAIX_MAX_SEED_COUNT               0xFFFFFFFFU

#if (defined CRYPTO_XVIX_XAIX_AES_CTRDRBG_SEED_COUNTLEN)
#error CRYPTO_XVIX_XAIX_AES_CTRDRBG_SEED_COUNTLEN already defined
#endif
/** \brief The length of seed count in bytes to store 2^32-1 */
#define CRYPTO_XVIX_XAIX_AES_CTRDRBG_SEED_COUNTLEN    4U

#if (defined CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_INT_STATELEN)
#error CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_STATELEN already defined
#endif
/** \brief The length of the internal state for the CTRDRBG which consists of Key || Block. */
#define CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_STATELEN                      \
((CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_KEYLEN) + (CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_BLOCKLEN))

/*==================[type definitions]============================================================*/

/** \brief  Workspace of primitive RANDOMGENERATE_AES_CTRDRBG.
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
 **         Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Callback().
 **
 ** \var    notifyResult
 ** \brief  The value of the callback result received from a secondary primitive via
 **         Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Callback().
 **
 ** \var    lockMain
 ** \brief  Flag to lock multiple parallel executions of Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Main().
 **
 ** ---specific-------------------------------------------------------------------
 **
 ** \brief  Context for the RANDOMGENERATE_AES_CTRDRBG
 **
 ** \var  blockLength
 ** \brief  The number of bytes in current block.
 **
 ** \var  block
 ** \brief  The buffer representing the current block (V) of the block cipher,
 **         which is updated each time another block of output is produced.
 **         It is also provided as input for the ENCRYPT_AES_ECB job used by RANDOMGENERATE_AES_CTRDRBG.
 **
 ** \var  secondaryJob_primitiveInfo
 ** \brief  The Crypto_xVIx_xAIx_NonConstPrimitiveInfoType instance of the ENCRYPT_AES_ECB job used by RANDOMGENERATE_AES_CTRDRBG.
 **
 ** \var  secondaryJob_jobPrimitiveInfo
 ** \brief  The Crypto_JobPrimitiveInfoType instance of the ENCRYPT_AES_ECB job used by RANDOMGENERATE_AES_CTRDRBG.
 **
 ** \var  secondaryJob_jobInfo
 ** \brief  The Crypto_JobInfoType instance of the ENCRYPT_AES_ECB job used by RANDOMGENERATE_AES_CTRDRBG.
 **
 ** \var  secondaryJob
 ** \brief  The Crypto_JobType instance of the ENCRYPT_AES_ECB job used by RANDOMGENERATE_AES_CTRDRBG.
 **/

/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_WorkspaceType/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON)
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

  uint32 blockLength;

  uint8 block[CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_BLOCKLEN];

  Crypto_xVIx_xAIx_NonConstPrimitiveInfoType secondaryJob_primitiveInfo;
  Crypto_JobPrimitiveInfoType                secondaryJob_jobPrimitiveInfo;

  Crypto_JobInfoType          secondaryJob_jobInfo;
  Crypto_JobType              secondaryJob;
}
Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_WorkspaceType;
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Process
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Main
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Cancel
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Reset
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Restart
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_RANDOMGENERATE_AES_CTRDRBG_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_RANDOMGENERATE_AES_CTRDRBG == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_INT_CPR_RANDOMGENERATE_AES_CTRDRBG_H */

/*==================[end of file]=================================================================*/

