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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_SIGNATUREVERIFY_ECDSA_NOTSET.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ECDSA_NOTSET_H
#define CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ECDSA_NOTSET_H

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Cfg.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_SIGNATUREVERIFY_ECDSA_NOTSET.h/0002,1 */
#include <Crypto_xVIx_xAIx_Int_Lib_LN.h>
#include <Crypto_xVIx_xAIx_Int_Lib_Ecc.h>

/*==================[macros]======================================================================*/

#if (defined CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ECDSA_NOTSET_HASH_LENGTH)
#error CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ECDSA_NOTSET_HASH_LENGTH is already defined
#endif
/** \brief The maximal allowed length for a hash digest in bytes. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ECDSA_NOTSET_HASH_LENGTH 64U

#if (defined CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ECDSA_NOTSET_NUM_LEN_WORDS)
#error CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ECDSA_NOTSET_NUM_LEN_WORDS is already defined
#endif
/** \brief The length, in words, which is needed for the long number representation of
 *         the number of bytes given as input.
 */
#define CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ECDSA_NOTSET_NUM_LEN_WORDS(byteLength)                        \
(                                                                                    \
   (Crypto_xVIx_xAIx_LNWordType)                                                     \
   (                                                                                 \
      CRYPTO_XVIX_XAIX_LN_NUMBER_LEN(byteLength) + \
      (Crypto_xVIx_xAIx_LNWordType)1UL                                               \
   )                                                                                 \
)

#if (defined CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ECDSA_NOTSET_TEMP_LEN_WORDS)
#error CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ECDSA_NOTSET_TEMP_LEN_WORDS is already defined
#endif
/** \brief The length, in words, which is needed for the long number representation of
 *         the a temporary number which is based on the number of bytes given as input.
 */
#define CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ECDSA_NOTSET_TEMP_LEN_WORDS(byteLength)                            \
(                                                                                         \
   (Crypto_xVIx_xAIx_LNWordType)                                                          \
   (                                                                                      \
      (                                                                                   \
        (CRYPTO_XVIX_XAIX_LN_NUMBER_LEN(byteLength) + (Crypto_xVIx_xAIx_LNWordType)1UL) * \
        (Crypto_xVIx_xAIx_LNWordType)2UL                                                  \
      ) -                                                                                 \
      (Crypto_xVIx_xAIx_LNWordType)1UL                                                    \
   )                                                                                      \
)

/*==================[type definitions]============================================================*/

/** \brief  Workspace of primitive SIGNATUREVERIFY_ECDSA_NOTSET.
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
 **         Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Callback().
 **
 ** \var    notifyResult
 ** \brief  The value of the callback result received from a secondary primitive via
 **         Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Callback().
 **
 ** \var    lockMain
 ** \brief  Flag to lock multiple parallel executions of Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Main().
 **
 ** ---specific-------------------------------------------------------------------
 **
 ** \brief  Context for the SIGNATUREVERIFY_ECDSA_NOTSET
 **
 ** \var  hashResultLength
 ** \brief  The length of the hash digest.
 **
 ** \var  hashResult
 ** \brief  Pointer to the buffer where the hash value of the data will be saved.
 **
 ** \var  tmp1
 ** \brief  Pointer to a buffer which will hold a temporary number during the computation.
 **
 ** \var  tmp2
 ** \brief  Pointer to a buffer which will hold a temporary number during the computation.
 **
 ** \var  tmp3
 ** \brief  Pointer to a buffer which will hold a temporary number during the computation.
 **
 ** \var  tmp4
 ** \brief  Pointer to a buffer which will hold a temporary number during the computation.
 **
 ** \var  tmp5
 ** \brief  Pointer to a buffer which will hold a temporary number during the computation.
 **
 ** \var  eccCtxPtr
 ** \brief  Pointer to the context which has to be used for elliptic curve arithmetic.
 **
 ** \var  secondaryJob_primitiveInfo
 ** \brief  The Crypto_xVIx_xAIx_NonConstPrimitiveInfoType instance of the hash job used by SIGNATUREVERIFY_ECDSA_NOTSET.
 **
 ** \var  secondaryJob_jobPrimitiveInfo
 ** \brief  The Crypto_JobPrimitiveInfoType instance of the hash job used by SIGNATUREVERIFY_ECDSA_NOTSET.
 **
 ** \var  secondaryJob_jobInfo
 ** \brief  The Crypto_JobInfoType instance of the hash job used by SIGNATUREVERIFY_ECDSA_NOTSET.
 **
 ** \var  secondaryJob
 ** \brief  The Crypto_JobType instance of the hash job used by SIGNATUREVERIFY_ECDSA_NOTSET.
 **
 ** \var  tmpPointPtr
 ** \brief  Pointer to a elliptic curve point which is used during the computation.
 **
 ** \var  R
 ** \brief  Pointer to the long number representation of the value "r".
 **
 ** \var  xPtr
 ** \brief  Pointer to the elliptic curve point "x".
 **
 ** \var  pubKeyPtr
 ** \brief  Pointer to the public key as an elliptic curve point.
 **/

/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
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
  uint32                                                                    hashResultLength;
  P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)                       hashResult;

  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp1;
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp2;
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp3;
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp4;
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp5;

  P2VAR(Crypto_xVIx_xAIx_ECCtxType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)  eccCtxPtr;

  Crypto_xVIx_xAIx_NonConstPrimitiveInfoType                                secondaryJob_primitiveInfo;
  Crypto_JobPrimitiveInfoType                                               secondaryJob_jobPrimitiveInfo;
  Crypto_JobInfoType                                                        secondaryJob_jobInfo;
  Crypto_JobType                                                            secondaryJob;

  P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmpPointPtr;

  P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) R;
  P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) xPtr;
  P2VAR(Crypto_xVIx_xAIx_ECPointType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) pubKeyPtr;
}
Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_WorkspaceType;
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Process
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Main
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Cancel
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Reset
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Restart
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREVERIFY_ECDSA_NOTSET_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_ECDSA_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_ECDSA_NOTSET_H */

/*==================[end of file]=================================================================*/

