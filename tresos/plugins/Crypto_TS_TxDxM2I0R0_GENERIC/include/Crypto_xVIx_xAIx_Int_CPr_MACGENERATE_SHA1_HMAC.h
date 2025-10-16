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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_MACGENERATE_SHA1_HMAC.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_INT_CPR_MACGENERATE_SHA1_HMAC_H
#define CRYPTO_XVIX_XAIX_INT_CPR_MACGENERATE_SHA1_HMAC_H

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int_CPr_MACGENERATE_SHA1_HMAC_Cfg.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_MACGENERATE_SHA1_HMAC.h/0002,1 */
#include <Crypto_xVIx_xAIx_Int_CPr_HASH_SHA1_NOTSET.h>

/*==================[macros]======================================================================*/

/* !LINKSTO Crypto.Req.CPr/MACGENERATE_SHA1_HMAC/GENERAL/0002,1 */
#if (defined CRYPTO_XVIX_XAIX_INT_CPR_MACGENERATE_SHA1_HMAC_BLOCKSIZE)
#error CRYPTO_XVIX_XAIX_INT_CPR_MACGENERATE_SHA1_HMAC_BLOCKSIZE already defined
#endif
/** \brief  Macro indicating the length of a block in bytes. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_MACGENERATE_SHA1_HMAC_BLOCKSIZE CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA1_NOTSET_BLOCKSIZE_BYTE

/* !LINKSTO Crypto.Req.CPr/MACGENERATE_SHA1_HMAC/GENERAL/0003,1 */
#if (defined CRYPTO_XVIX_XAIX_INT_CPR_MACGENERATE_SHA1_HMAC_RESULTSIZE)
#error CRYPTO_XVIX_XAIX_INT_CPR_MACGENERATE_SHA1_HMAC_RESULTSIZE already defined
#endif
/** \brief  Macro indicating the length of a result in bytes. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_MACGENERATE_SHA1_HMAC_RESULTSIZE CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA1_NOTSET_RESULTSIZE

/*==================[type definitions]============================================================*/

/** \brief  Workspace of primitive MACGENERATE_SHA1_HMAC.
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
 **         Crypto_xVIx_xAIx_CPr_MACGENERATE_SHA1_HMAC_Callback().
 **
 ** \var    notifyResult
 ** \brief  The value of the callback result received from a secondary primitive via
 **         Crypto_xVIx_xAIx_CPr_MACGENERATE_SHA1_HMAC_Callback().
 **
 ** \var    lockMain
 ** \brief  Flag to lock multiple parallel executions of Crypto_xVIx_xAIx_CPr_MACGENERATE_SHA1_HMAC_Main().
 **
 ** ---specific-------------------------------------------------------------------
 **
 ** \var    inputActPtr
 ** \brief  Pointer to the current position in job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr
 **         related to a main call within an API update call.
 **
 ** \var    inputEndPtr
 ** \brief  Pointer to the end of the input data pointed by job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr.
 **
 ** \var    H6Len
 ** \brief  On calling the hash function according to FIPS PUB 198-1 Steps 2 and 6, this parameter
 **         contains the size of the buffer 'H1'. When the hash function returns, the actual length
 **         of the returned value is stored.
 **
 ** \var    H9Len
 ** \brief  On calling the hash function according to FIPS PUB 198-1 Step 9, this parameter contains
 **         the size of the buffer 'H2'. When the hash function returns, the actual length of the
 **         returned value is stored.
 **
 ** \var    K0
 ** \brief  The key K after any necessary pre-processing to form a key of length of the block size
 **         (in bytes) of the input to the approved hash function.
 **
 ** \var    H1
 ** \brief  The buffer that shall store the digest of calls of the approved hash function according
 **         to FIPS PUB 198-1 Steps 2 and 6.
 **
 ** \var    H2
 ** \brief  The buffer that shall store the digest of calls of the approved hash function according
 **         to FIPS PUB 198-1 Step 9.
 **
 **
 ** \var    BF
 ** \brief  A buffer for internal operations, e.g. to pre-process the key K into K0;
 **         the size must be >= CRYPTO_XVIX_XAIX_INT_CPR_MACGENERATE_SHA1_HMAC_BLOCKSIZE.
 **
 ** \var    secondaryJob_primitiveInfo
 ** \brief  The Crypto_xVIx_xAIx_NonConstPrimitiveInfoType instance of the MACGENERATE_SHA1_HMAC job used by MACGENERATE_SHA1_HMAC.
 **
 ** \var    secondaryJob_jobPrimitiveInfo
 ** \brief  The Crypto_JobPrimitiveInfoType instance of the MACGENERATE_SHA1_HMAC job used by MACGENERATE_SHA1_HMAC.
 **
 ** \var    secondaryJob_jobInfo
 ** \brief  The Crypto_JobInfoType instance of the MACGENERATE_SHA1_HMAC job used by MACGENERATE_SHA1_HMAC.
 **
 ** \var    secondaryJob
 ** \brief  The Crypto_JobType instance of the MACGENERATE_SHA1_HMAC job used by MACGENERATE_SHA1_HMAC.
 **/

/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_CPr_MACGENERATE_SHA1_HMAC_WorkspaceType/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SHA1_HMAC == STD_ON)
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
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) inputActPtr;
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) inputEndPtr;

  uint32                       H1Len;
  uint32                       H2Len;

  uint8                        K0[CRYPTO_XVIX_XAIX_INT_CPR_MACGENERATE_SHA1_HMAC_BLOCKSIZE ];
  uint8                        H1[CRYPTO_XVIX_XAIX_INT_CPR_MACGENERATE_SHA1_HMAC_RESULTSIZE];
  uint8                        H2[CRYPTO_XVIX_XAIX_INT_CPR_MACGENERATE_SHA1_HMAC_RESULTSIZE];

  uint8                        BF[CRYPTO_XVIX_XAIX_INT_CPR_MACGENERATE_SHA1_HMAC_BLOCKSIZE ];

  Crypto_xVIx_xAIx_NonConstPrimitiveInfoType secondaryJob_primitiveInfo;
  Crypto_JobPrimitiveInfoType                secondaryJob_jobPrimitiveInfo;

  Crypto_JobInfoType           secondaryJob_jobInfo;
  Crypto_JobType               secondaryJob;
}
Crypto_xVIx_xAIx_CPr_MACGENERATE_SHA1_HMAC_WorkspaceType;
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SHA1_HMAC == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SHA1_HMAC == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_MACGENERATE_SHA1_HMAC_Process
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SHA1_HMAC == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SHA1_HMAC == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_MACGENERATE_SHA1_HMAC_Main
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SHA1_HMAC == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SHA1_HMAC == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_MACGENERATE_SHA1_HMAC_Cancel
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SHA1_HMAC == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SHA1_HMAC == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_MACGENERATE_SHA1_HMAC_Reset
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SHA1_HMAC == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SHA1_HMAC == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_MACGENERATE_SHA1_HMAC_Restart
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SHA1_HMAC == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SHA1_HMAC == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_MACGENERATE_SHA1_HMAC_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_MACGENERATE_SHA1_HMAC == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_INT_CPR_MACGENERATE_SHA1_HMAC_H */

/*==================[end of file]=================================================================*/

