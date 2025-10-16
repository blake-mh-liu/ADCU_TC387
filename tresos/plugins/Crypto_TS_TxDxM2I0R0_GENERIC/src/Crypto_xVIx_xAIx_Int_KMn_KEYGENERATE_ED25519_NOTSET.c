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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KMn_KEYGENERATE_ED25519_NOTSET.c/0001,1 */

/*==================[deviations]==================================================================*/

/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.3 (required)
 * A cast shall not be performed between a pointer to object type
 * and a pointer to a different object type.
 *
 * Reason:
 * Problems could arise on little and big endian platform. But tests are successful on little and
 * big endian platform.
 *
 */

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always false
 *
 * Reason:
 * False positive from the tasking compiler.
 */

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int.h>                                     /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KMn_KEYGENERATE_ED25519_NOTSET.c/0002,1 */
#include <Crypto_xVIx_xAIx_Int_KeyManagement.h>                       /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KMn_KEYGENERATE_ED25519_NOTSET.c/0003,1 */
#include <Crypto_xVIx_xAIx_Int_KMn_KEYGENERATE_ED25519_NOTSET.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KMn_KEYGENERATE_ED25519_NOTSET.c/0004,1 */
#include <Crypto_xVIx_xAIx_Int_Lib_LN.h>
#include <Crypto_xVIx_xAIx_Int_Lib_Ecc.h>
#include <Crypto_xVIx_xAIx_Int_KMn_KEYGENERATE_ED25519_NOTSET_Cfg.h>

/*==================[macros]======================================================================*/

#if (defined CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_PRIVKEY_LENGTH)
#error CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_PRIVKEY_LENGTH is already defined
#endif
/** \brief The private key length of the Ed25519yy curve in bytes. */
#define CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_PRIVKEY_LENGTH 32U

#if(defined CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_PUBKEY_LENGTH)
  #error CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_PUBKEY_LENGTH is already defined
#endif
/** \brief The public key length of the Ed25519yy curve in bytes. */
#define CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_PUBKEY_LENGTH 32U

#if(defined CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_BYTEARRAY_LENGTH)
#error CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_BYTEARRAY_LENGTH is already defined
#endif
/** \brief The maximum length, which is needed for byte array representation **/
#define CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_BYTEARRAY_LENGTH 32U

#if (defined CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_HASH_LENGTH)
#error CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_HASH_LENGTH is already defined
#endif
/** \brief The maximal allowed length for a hash digest in bytes. **/
#define CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_HASH_LENGTH 64U

#if (defined CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_NUM_LEN_WORDS)
#error CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_NUM_LEN_WORDS is already defined
#endif
/** \brief The length, in words, which is needed for the long number representation of
 *         the longest possible stored number. This length depends on the configured curve.
 */
#define CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_NUM_LEN_WORDS                                    \
(                                                                                    \
   (Crypto_xVIx_xAIx_LNWordType)                                                     \
   (                                                                                 \
      CRYPTO_XVIX_XAIX_LN_NUMBER_LEN(CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_BYTEARRAY_LENGTH) + \
      (Crypto_xVIx_xAIx_LNWordType)1UL                                               \
   )                                                                                 \
)

#if (defined CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_TEMP_LEN_WORDS)
#error CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_TEMP_LEN_WORDS is already defined
#endif
/** \brief The length, in words, which is needed for the long number representation of
 *         the longest possible temporary number. This length depends on the
 *         configured curve.
 */
#define CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_TEMP_LEN_WORDS                                     \
(                                                                                      \
   (Crypto_xVIx_xAIx_LNWordType)                                                       \
   (                                                                                   \
      (CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_NUM_LEN_WORDS * (Crypto_xVIx_xAIx_LNWordType)2UL) - \
      (Crypto_xVIx_xAIx_LNWordType)1UL                                                 \
   )                                                                                   \
)

/*==================[type definitions]============================================================*/

/*==================[internal function declarations]==============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>
#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET == STD_ON)
/** \brief  Processes the job on the driver object.
 **
 ** This functions calls the processJob function of the primitive given by the job. The primitive
 ** is executed on the given driver object. The primitive will be executed as secondary primitive
 ** and hence will not release the driver object after processing is done.
 **
 ** \params[in]  objectId  The Id of the driver object the job shall be executed on.
 ** \params[in]  job       The job that shall be executed.
 **
 ** \returns  The result of the process function.
 **
 ** \retval  E_OK                   Process function successful.
 ** \retval  E_NOT_OK               Process function failed.
 ** \retval  CRYPTO_E_JOB_CANCELED  Process function failed, because job using this primitive
 **                                 was cancelled.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_ProcessSecondaryJob
(
        uint32                                                 objectId,
  P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET == STD_ON) */
/** \brief Calculte the public key as the point and ecoded this to a little endian byte array.
 **
 ** This function swaps two numbers with using third variable and bitwise XOR as described
 ** in RFC 7748. The cswap function SHOULD be implemented in constant time.
 **
 ** \param[in]     scalarS    Pointer to the memory location, where the secret scalar S value is stored.
 ** \param[in,out] byteArray  Pointer to the memory location, where digest of the private key is stored.
 ** \param[in,out] tmp        Pointer to a temporary buffer for the calculation.
 ** \param[in]     curveIndex Index of the corresponding elliptic curve, which shall be used.
 **
 ** \Reentrancy {Nonreentrant}
 ** \Synchronicity {Synchronous/Asynchronous}
 **
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KEYGENERATE_ED25519_NOTSET_GeneratePublicKey
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) scalarS,
  P2VAR(uint8,                       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) byteArray,
  P2VAR(uint8,                       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
        uint8                                                               curveIndex
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET == STD_ON) */

/** \brief  This is a dummy callback for the primitives executed in KeyManagement.
 **
 ** This function is used as callback for primitives, that are executed as secondary primitive
 ** inside the KeyManagement because additional primitives will be executed aftewards.
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
 ** \retval  E_OK  Always returns this value.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KEYGENERATE_ED25519_NOTSET_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal constants]==========================================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET == STD_ON)

/** \brief  The PrimitiveType for the dummy primitive. **/
CONST(Crypto_xVIx_xAIx_PrimitiveDescriptionType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_KEYGENERATE_ED25519_NOTSET_Primitive =
{
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  Crypto_xVIx_xAIx_Int_KMn_KEYGENERATE_ED25519_NOTSET_Callback,
  0U,
  0U,
  0U
};

/** \brief  The CDOPrimitiveCnfgType for the dummy primitive. **/
CONST(Crypto_xVIx_xAIx_CDOPrimitiveCnfgType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_KEYGENERATE_ED25519_NOTSET_PrimitiveCnfg =
{
  &Crypto_xVIx_xAIx_KEYGENERATE_ED25519_NOTSET_Primitive,
  NULL_PTR,
  0U,
  NULL_PTR,
  0U
};

/** \brief  The dummy primitive used if a KeyManagement job shall be executed as secondary job. **/
CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_KEYGENERATE_ED25519_NOTSET_DummyPrimitive =
{
  &Crypto_xVIx_xAIx_KEYGENERATE_ED25519_NOTSET_PrimitiveCnfg,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR
};

#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>
/* --- Crypto_xVIx_xAIx_Int_KMn_KEYGENERATE_ED25519_NOTSET_Process ------------------------ */

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_KMn_KEYGENERATE_ED25519_NOTSET_Process/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KEYGENERATE_ED25519_NOTSET_Process
(
          uint32                                                 objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) jobs,
          uint32                                                 jobsLength,
    P2VAR(uint8,          AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) wkspDataPtr,
          uint32                                                 wkspDataLen,
          uint32                                                 cryptoKeyId
)
{
  Std_ReturnType retVal       = E_NOT_OK;
  /* Set the curve index */
  uint8          curveIndex   = CRYPTO_XVIX_XAIX_KEYGENERATE_ED25519YY_DEFAULT_CURVE;

  uint8          tmpByteArray[CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_HASH_LENGTH] = { 0U };
  uint32         tmpByteArrayLength                                    =   0U;
  boolean        fromPrimitive                                         = FALSE;

  Crypto_xVIx_xAIx_LNWordType scalarS[CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_NUM_LEN_WORDS] = { 0U };

  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) privateKeyPtr = NULL_PTR;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) publicKeyPtr  = NULL_PTR;

  TS_PARAM_UNUSED(jobsLength);
  TS_PARAM_UNUSED(wkspDataLen);

  /* Get the private key from key element */
  retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet(cryptoKeyId,
                                                     CRYPTO_KE_KEYGENERATE_SEED,
                                                    &privateKeyPtr,
                                                     FALSE,
                                                     CRYPTO_XVIX_XAIX_SID_EMPTY
                                                    );
  /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519_NOTSET/GENERAL/0003,1 */
  if (E_OK == retVal)
  {
    fromPrimitive = FALSE;
    /* Deviation TASKING-1 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(retVal, privateKeyPtr, fromPrimitive);
  }
  /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519_NOTSET/GENERAL/0004,1 */
  if (E_OK == retVal)
  {
    /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519_NOTSET/GENERAL/0005,1 */
    if (Crypto_xVIx_xAIx_EllipticCurveInfo[curveIndex].privateKeyLength != privateKeyPtr->data->size)
    {
      retVal = E_NOT_OK;
    }
    else
    {
      /* Set the hash result Length */
      tmpByteArrayLength = CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_HASH_LENGTH;
      /* Hash the private key */
      jobs->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        = privateKeyPtr->data->data;
      jobs->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     = CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_PRIVKEY_LENGTH;
      jobs->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       = tmpByteArray;
      jobs->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &tmpByteArrayLength;
      /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519_NOTSET/GENERAL/0006,1 */
      /* The key length is already checked hence this function always returns E_OK. */
      (void) Crypto_xVIx_xAIx_Int_KMn_ProcessSecondaryJob(objectId, jobs);

      /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519_NOTSET/GENERAL/0007,1 */
      /* Construct the secret scalarS from the first half of the hash digest */
      /* Clear the first 3 bits */
      tmpByteArray[0U]  &= (uint8)0xf8U;

      /* Clear the highest bit of the last octet from the first hash half */
      tmpByteArray[31U] &=  (uint8)(~(uint8)((uint8)1U << (uint8)7U));

      /* Set the second highest bit of the final octet from the first hash half */
      tmpByteArray[31U] |= (uint8)((uint8)1U << (uint8)6U);

      /* Set the expected length of the Long Number before converting the bytearray to a little-endian integer */
      scalarS[0U]        = CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_NUM_LEN_WORDS;

      /* Calculate the public key */
      Crypto_xVIx_xAIx_KEYGENERATE_ED25519_NOTSET_GeneratePublicKey(scalarS,
                                            tmpByteArray,
                                            wkspDataPtr,
                                            curveIndex
                                           );

      /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519_NOTSET/GENERAL/0008,1 */
      /* Store the public key in the key element */
      retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( cryptoKeyId,
                                                          CRYPTO_KE_KEYGENERATE_KEY,
                                                         &(publicKeyPtr),
                                                          FALSE,
                                                          CRYPTO_XVIX_XAIX_SID_EMPTY
                                                        );

      /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519_NOTSET/GENERAL/0009,1 */
      if (E_OK == retVal)
      {
        fromPrimitive = FALSE;
        /* Deviation TASKING-1 */
        CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_LOCK(retVal, publicKeyPtr, fromPrimitive);
        /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519_NOTSET/GENERAL/0010,1 */
        if (E_OK == retVal)
        {
          /* Set the size */
          publicKeyPtr->data->size = CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_PUBKEY_LENGTH;
          /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519_NOTSET/COMMON/0001,1 */
          /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519_NOTSET/COMMON/0002,1 */
          /* The encoded public key is stored in the second half of the byte array */
          CRYPTO_XVIX_XAIX_KEY_ELEMENT_STORE(
                                              cryptoKeyId,
                                              CRYPTO_KE_KEYGENERATE_KEY,
                                              publicKeyPtr,
                                             &tmpByteArray[CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_BYTEARRAY_LENGTH],
                                              publicKeyPtr->data->size,
                                              retVal
                                            );
          CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE(publicKeyPtr);
        }
        else
        {
          retVal = E_NOT_OK;
        }
      }
    }
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(privateKeyPtr);
  }
  else
  {
    retVal = E_NOT_OK;
  }

  return retVal;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_ProcessSecondaryJob
(
        uint32                                                 objectId,
  P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job
)
{
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitivePtr;

  /* This function can not fail because it will only be called if the primitive exists in the CDO */
  (void) Crypto_xVIx_xAIx_CheckJobPrimitive(objectId, job, &primitivePtr);
  primitivePtr->data->P1 = &Crypto_xVIx_xAIx_KEYGENERATE_ED25519_NOTSET_DummyPrimitive;

  Crypto_xVIx_xAIx_CDOs[objectId].data->jobCurrent       = job;

  /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Job/0001,1 */
  SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
  Crypto_xVIx_xAIx_CDOs[objectId].data->primitiveCurrent = primitivePtr;
  SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();

  return primitivePtr->cnfg->description->fcnProcess(objectId, job, primitivePtr);
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET == STD_ON) */
/*--- Crypto_xVIx_xAIx_KEYGENERATE_ED25519_NOTSET_GeneratePublicKey ----------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET == STD_ON)

static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KEYGENERATE_ED25519_NOTSET_GeneratePublicKey
(
  P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) scalarS,
  P2VAR(uint8,                       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) byteArray,
  P2VAR(uint8,                       AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) tmp,
        uint8                                                               curveIndex
)
{
  Crypto_xVIx_xAIx_ECPointType publicKeyPoint;
  Crypto_xVIx_xAIx_ECCtxType   curveCtx;

  uint32       length = CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_BYTEARRAY_LENGTH;
  /* Set the index */
  curveCtx.curveIndex = curveIndex;

  /* The return value is ignored because the parameters are either from the context where they are
   * properly defined or local variables which are properly defined before passing them to the function.
   */
   /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519_NOTSET/GENERAL/0011,1 */
  (void)Crypto_xVIx_xAIx_LNLEByteArrayToNumber(
                                                byteArray,
                                                length,
                                                scalarS,
                                                scalarS[0U]
                                              );

  /* Calculate the public key as a point */
  /* Deviation MISRAC2012-1 <+4> */
  Crypto_xVIx_xAIx_Procedure_EdDSAPointMultiplication(&publicKeyPoint,
                                                      &(Crypto_xVIx_xAIx_EllipticCurveInfo[curveCtx.curveIndex].basePoint),
                                                       scalarS,
                                                       (P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)) tmp,
                                                      &curveCtx
                                                     );

  /* Converting and encoding the point to a byte array */
  /* Deviation MISRAC2012-1 <+2> */
  Crypto_xVIx_xAIx_Procedure_EccPointConvertProj2Aff(&publicKeyPoint,
                                                      (P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)) tmp,
                                                     &curveCtx
                                                    );

  /* Convert the yValue of the point in little endian byte array */
  /* Call shall never fail because we have enough memory allocated in the context
   * to store the byte representation of the LN. */
  /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519_NOTSET/GENERAL/0013,1 */
  (void)Crypto_xVIx_xAIx_LNNumberToLEByteArray( publicKeyPoint.yValue,
                                               &byteArray[length],
                                               &length
                                              );

  /* Convert the xValue of the point in little endian byte array */
  /* Call shall never fail because we have enough memory allocated in the context
   * to store the byte representation of the LN. */
  (void) Crypto_xVIx_xAIx_LNNumberToLEByteArray( publicKeyPoint.xValue,
                                                 byteArray,
                                                &length
                                               );
  /* The least significant bit of the x-coordinate */
  curveCtx.x0 = (uint8)(byteArray[0U] & (uint8)(0x01U));

  /* Form the encoding of the point - encoded public key */
  if((uint8)0U != curveCtx.x0)
  {
    /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519_NOTSET/GENERAL/0014,1 */
    byteArray[(CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519_NOTSET_HASH_LENGTH) - 1U] |= (uint8)((uint8)curveCtx.x0 << 7U);
  }

}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET == STD_ON) */

/* --- Crypto_xVIx_xAIx_Int_KMn_KEYGENERATE_ED25519_NOTSET_Callback ----------------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KEYGENERATE_ED25519_NOTSET_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
)
{
  TS_PARAM_UNUSED(objectId);
  TS_PARAM_UNUSED(job);
  TS_PARAM_UNUSED(primitive);
  TS_PARAM_UNUSED(cbkType);
  TS_PARAM_UNUSED(cbkResult);

  return E_OK;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[end of file]=================================================================*/

