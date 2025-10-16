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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KMn_RANDOMSEED_AES_CTRDRBG.c/0001,1 */

/*==================[deviations]==================================================================*/
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
 * CODEMETRIC-1) Deviated Rule: HIS_STMT
 * not 85 <= 75
 *
 * Reason:
 * Improving this software quality metric would adversely effect the performance
 * of the keymanagement function.
 *
 * CODEMETRIC-2) Deviated Rule: HIS_V(G)
 * not 26 <= 20
 *
 * Reason:
 * SingleCall functions are adjusted for performance and have a reduced amount of function calls
 * on purpose which leads to metric violations.
 */

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int.h>                                 /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KMn_RANDOMSEED_AES_CTRDRBG.c/0002,1 */
#include <Crypto_xVIx_xAIx_Int_KeyManagement.h>                   /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KMn_RANDOMSEED_AES_CTRDRBG.c/0003,1 */
#include <Crypto_xVIx_xAIx_Int_KMn_RANDOMSEED_AES_CTRDRBG.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KMn_RANDOMSEED_AES_CTRDRBG.c/0004,1 */

#include <Crypto_xVIx_xAIx_Int_CPr_RANDOMGENERATE_AES_CTRDRBG.h>

/*==================[macros]======================================================================*/

#if (defined CRYPTO_XVIX_XAIX_AES_CTRDRBG_KEYLEN)
#error CRYPTO_XVIX_XAIX_AES_CTRDRBG_KEYLEN already defined
#endif
/** \brief The key length for the CTRDRBG according to NIST SP-800-90A */
#define CRYPTO_XVIX_XAIX_AES_CTRDRBG_KEYLEN 32U

#if (defined CRYPTO_XVIX_XAIX_AES_CTRDRBG_BLOCKLEN)
#error CRYPTO_XVIX_XAIX_AES_CTRDRBG_BLOCKLEN already defined
#endif
/** \brief The block length for the CTRDRBG according to NIST SP-800-90A */
#define CRYPTO_XVIX_XAIX_AES_CTRDRBG_BLOCKLEN 16U

#if (defined CRYPTO_XVIX_XAIX_RANDOMGENERATE_SEED_COUNTLEN)
#error CRYPTO_XVIX_XAIX_RANDOMGENERATE_SEED_COUNTLEN already defined
#endif
/** \brief The length of seed count in bytes to store 2^32-1 */
#define CRYPTO_XVIX_XAIX_RANDOMGENERATE_SEED_COUNTLEN 4U

#if (defined CRYPTO_XVIX_XAIX_AES_CTRDRBG_INT_STATELEN)
#error CRYPTO_XVIX_XAIX_AES_CTRDRBG_INT_STATELEN already defined
#endif
/** \brief  The length internal state length for the CTRDRBG. A concatination of the key and
 **         one block.
 **/
#define CRYPTO_XVIX_XAIX_AES_CTRDRBG_INT_STATELEN (CRYPTO_XVIX_XAIX_AES_CTRDRBG_KEYLEN + CRYPTO_XVIX_XAIX_AES_CTRDRBG_BLOCKLEN)

/*==================[type definitions]============================================================*/

/*==================[internal function declarations]==============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON)
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON) */

/** \brief AES-CTRDRBG BCC function
 *
 *  This function is an auxiliary internal function that is used during DRBG
 *  instantiation and reseeding to either derive internal state values or
 *  to distribute entropy throughout a bitstring as described in NIST SP-800-90A.
 *
 *  \param[in]     Buf                The IV || L || N
 *  \param[in]     InputString        The Entropy for the RandomSeed
 *  \param[in]     InputStringLength  The length of the Entropy
 *  \param[in]     ObjectId           Identifier of the crypto driver object that shall
 *                                    process the request.
 *  \param[in,out] Job                Reference to the job that shall be processed.
 *
 *  \Reentrancy{Nonreentrant}
 *  \Synchronicity{Synchronous}
 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_RANDOMSEED_AES_CTRDRBG_BCC
(
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)         buf,
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)         inputString,
  uint32                                                        inputStringLength,
  P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)           outputBlock,
  uint32                                                        objectId,
  P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)  job
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON) */

/** \brief  AES-CTRDRBG seed derivation function
 **
 ** This function is an auxiliary internal function that is used during
 ** DRBG instantiation and reseeding to either derive internal state values
 ** or to distribute entropy throughout a bitstring as described in NIST SP-800-90A.
 **
 ** \param[in]   inputString        Holds a pointer to the memory location which contains
 **                                 the data to feed the Seed (seed value).
 ** \param[in]   inputStringLength  Contains the length of the entropy in bytes.
 ** \param[out]  outputString       Holds a pointer to the memory location where
 **                                 the result shall be stored.
 ** \param[in]   objectId           Identifier of the crypto driver object that shall
 **                                 process the request.
 ** \param[in]   job                Reference to the job that shall be processed.
 **
 ** \Reentrancy{Nonreentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_RANDOMSEED_AES_CTRDRBG_DF
(
  P2CONST(uint8,          AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) inputString,
          uint32                                                 inputStringLength,
    P2VAR(uint8,          AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) outputString,
          uint32                                                 objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_RANDOMSEED_AES_CTRDRBG_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON) */

/* -----------------------------------------------------------------------------------------------*/
/* static functions */

/** \brief  AES-CTRDRBG seed update function
 **         This function updates the internal state of the CTRDRBG using the
 **         seed value as described in NIST SP-800-90A.
 **
 ** \param[in]      objectId      Identifier of the crypto driver object that shall
 *                                process the request.
 ** \param[in]      providedData  Holds a pointer to the memory location which contains
 **                               the data to feed the Seed (seed value).
 ** \param[in]      block         Holds a pointer to the memory location which contains
 **                               the Block (V) of the block cipher.
 ** \param[in,out]  job           Pointer to the configuration of the job this primitive shall be
 **                               processed for. This contains structures with job and primitive
 **                               relevant information but also pointers to result buffers.
 ** \param[in]      primitive     Pointer to the data structure describes the current primitive.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK                        Request successful.
 ** \retval  E_NOT_OK                    Request failed.
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_RandomAESCTRDRBGUpdate
(
          uint32                                                                    objectId,
  P2CONST(uint8,                             AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) providedData,
    P2VAR(uint8,                             AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) block,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal constants]==========================================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  The PrimitiveType for the dummy primitive. **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON)
CONST(Crypto_xVIx_xAIx_PrimitiveDescriptionType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_RANDOMSEED_AES_CTRDRBG_Primitive =
{
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  Crypto_xVIx_xAIx_Int_KMn_RANDOMSEED_AES_CTRDRBG_Callback,
  0U,
  0U,
  0U
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON) */

/** \brief  The DriverObjectPrimitiveCnfgType for the dummy primitive. **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON)
CONST(Crypto_xVIx_xAIx_CDOPrimitiveCnfgType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_RANDOMSEED_AES_CTRDRBG_PrimitiveCnfg =
{
  &Crypto_xVIx_xAIx_RANDOMSEED_AES_CTRDRBG_Primitive,
  NULL_PTR,
  0U,
  NULL_PTR,
  0U
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON) */

/** \brief  The dummy primitive used if a KeyManagement job shall be executed as secondary job. **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON)
CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_RANDOMSEED_AES_CTRDRBG_DummyPrimitive =
{
  &Crypto_xVIx_xAIx_RANDOMSEED_AES_CTRDRBG_PrimitiveCnfg,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR
};
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/* --- Crypto_xVIx_xAIx_Int_KMn_RANDOMSEED_AES_CTRDRBG_Process ---------------------------------- */

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_xVIx_xAIx_KMn_RANDOMSEED_AES_CTRDRBG_Process/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON)
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_RANDOMSEED_AES_CTRDRBG_Process
(
          uint32                                                 objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) jobs,
          uint32                                                 jobsLength,
    P2VAR(uint8,          AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) wkspDataPtr,
          uint32                                                 wkspDataLen,
          uint32                                                 cryptoKeyId,
  P2CONST(uint8,          AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) seedPtr,
          uint32                                                 seedLength
)
{
          Std_ReturnType                                                            retVal;
          Std_ReturnType                                                            retValTmp;
          boolean                                                                   fromPrimitive                                         = FALSE;
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitivePtr                                          = NULL_PTR;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyPtr                                                = NULL_PTR;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keySeedPtr                                            = NULL_PTR;
          uint32                                                                    SeedCount                                             =   0U;
          uint8                                                                     newEntropy[CRYPTO_XVIX_XAIX_AES_CTRDRBG_INT_STATELEN] = { 0U };
          uint8                                                                     block[CRYPTO_XVIX_XAIX_AES_CTRDRBG_BLOCKLEN]          = { 0U };

  TS_PARAM_UNUSED(jobsLength);
  TS_PARAM_UNUSED(wkspDataPtr);
  TS_PARAM_UNUSED(wkspDataLen);

  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_RandomSeed/0006,1 */
  /* 2. seed_material = Block_Cipher_df(seed_material, seedlen) */
  retVal = Crypto_xVIx_xAIx_Int_KMn_RANDOMSEED_AES_CTRDRBG_DF(seedPtr,
                                                              seedLength,
                                                              newEntropy,
                                                              objectId,
                                                              jobs
                                                             );
  if (E_OK == retVal)
  {
    /* step 3 & 4 */
    /* This function was already called in the AESCTRDRBGDF function and hence can
      not fail here */
    (void) Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( cryptoKeyId,
                                                      CRYPTO_KE_CIPHER_KEY,
                                                     &keyPtr,
                                                      FALSE,
                                                      CRYPTO_XVIX_XAIX_SID_EMPTY
                                                    );

    fromPrimitive = FALSE;
    /* !LINKSTO Crypto.Req.KMn/RANDOMSEED_AES_CTRDRBG/GENERAL/0008,1 */
    /* Deviation TASKING-2 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_LOCK(retVal, keyPtr, fromPrimitive);

    if (E_OK == retVal)
    {
      /* size was already checked in the above function */
      TS_MemBZero(keyPtr->data->data, CRYPTO_XVIX_XAIX_AES_CTRDRBG_KEYLEN);
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE(keyPtr);
      /* This function can not fail because it will only be called if the primitive exists in the CDO */
      (void) Crypto_xVIx_xAIx_CheckJobPrimitive(objectId, jobs, &primitivePtr);
      primitivePtr->data->P1 = &Crypto_xVIx_xAIx_RANDOMSEED_AES_CTRDRBG_DummyPrimitive;
      /* check size of seed */
      retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( cryptoKeyId,
                                                          CRYPTO_KE_RANDOM_SEED_STATE,
                                                         &keyPtr,
                                                          FALSE,
                                                          CRYPTO_XVIX_XAIX_SID_EMPTY
                                                        );
    }

    if (E_OK == retVal)
    {
      fromPrimitive = FALSE;
      /* !LINKSTO Crypto.Req.KMn/RANDOMSEED_AES_CTRDRBG/GENERAL/0009,1 */
      /* Deviation TASKING-2 */
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(retVal, keyPtr, fromPrimitive);

      if (E_OK == retVal)
      {
        /* !LINKSTO Crypto.Req.KMn/RANDOMSEED_AES_CTRDRBG/GENERAL/0007,1 */
        if (   (CRYPTO_XVIX_XAIX_AES_CTRDRBG_BLOCKLEN     == keyPtr->data->size                           )
            || (   (CRYPTO_XVIX_XAIX_AES_CTRDRBG_BLOCKLEN <= keyPtr->cnfg->description->maxSize           )
                && (TRUE                                  == keyPtr->cnfg->description->allowPartialAccess)
              )
            )
        {
          CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(keyPtr);
          /* 5. (Key, V) = CTRDRBG_Update(seed_material, Key, V) */
          retVal = Crypto_xVIx_xAIx_RandomAESCTRDRBGUpdate(objectId,
                                                          newEntropy,
                                                          block,
                                                          jobs,
                                                          primitivePtr
                                                          );
          retValTmp = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( cryptoKeyId,
                                                                  CRYPTO_XVIX_XAIX_KE_AES_CTRDRBG_SEED_COUNT,
                                                                  &keySeedPtr,
                                                                  FALSE,
                                                                  CRYPTO_XVIX_XAIX_SID_EMPTY
                                                                );
          if (   (E_OK == retVal)
              && (E_OK == retValTmp)
              )
          {
            fromPrimitive = FALSE;
            /* !LINKSTO Crypto.Req.KMn/RANDOMSEED_AES_CTRDRBG/GENERAL/0010,1 */
            /* Deviation TASKING-2 */
            CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_LOCK(retVal, keySeedPtr, fromPrimitive);
            if (E_OK == retVal)
            {
              if (CRYPTO_XVIX_XAIX_RANDOMGENERATE_SEED_COUNTLEN != keySeedPtr->data->size)
              {
                retVal = E_NOT_OK;
              }
              else
              {
                /* !LINKSTO Crypto.Req.KMn/RANDOMSEED_AES_CTRDRBG/COMMON/0001,1 */
                /* !LINKSTO Crypto.Req.KMn/RANDOMSEED_AES_CTRDRBG/COMMON/0002,1 */
                /* Reset the seed count and store it in the key Element */
                CRYPTO_XVIX_XAIX_KEY_ELEMENT_STORE( cryptoKeyId,
                                                    CRYPTO_XVIX_XAIX_KE_AES_CTRDRBG_SEED_COUNT,
                                                    keySeedPtr,
                                                   &SeedCount,
                                                    CRYPTO_XVIX_XAIX_RANDOMGENERATE_SEED_COUNTLEN,
                                                    retVal
                                                  );
              }
              CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE(keySeedPtr);
            }
            else
            {
              retVal = E_NOT_OK;
            }
          }
        }
        else
        {
          retVal = E_NOT_OK;
          CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(keyPtr);
        }
      }
      else
      {
        retVal = E_NOT_OK;
      }
    }
    else
    {
      retVal = E_NOT_OK;
    }
  }

  return retVal;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_ProcessSecondaryJob
(
        uint32                                                 objectId,
  P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job
)
{
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitivePtr;

  /* This function can not fail because it will only be called if the primitive exists in the CDO */
  (void) Crypto_xVIx_xAIx_CheckJobPrimitive(objectId, job, &primitivePtr);
  primitivePtr->data->P1 = &Crypto_xVIx_xAIx_RANDOMSEED_AES_CTRDRBG_DummyPrimitive;

  Crypto_xVIx_xAIx_CDOs[objectId].data->jobCurrent       = job;

  /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Job/0001,1 */
  SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
  Crypto_xVIx_xAIx_CDOs[objectId].data->primitiveCurrent = primitivePtr;
  SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();

  return primitivePtr->cnfg->description->fcnProcess(objectId, job, primitivePtr);
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON) */

/*--- Crypto_xVIx_xAIx_Int_KMn_RANDOMSEED_AES_CTRDRBG_BCC ----------------------------------------*/

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON)
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_RANDOMSEED_AES_CTRDRBG_BCC
(
  P2CONST(uint8,          AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) buf,
  P2CONST(uint8,          AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) inputString,
          uint32                                                 inputStringLength,
    P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)          outputBlock,
          uint32                                                 objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job
)
{
  uint32 i                                                    = 0U;
  uint32 j                                                    = 0U;
  uint32 outputLength                                         = CRYPTO_XVIX_XAIX_AES_CTRDRBG_BLOCKLEN;
  uint8  chainingValue[CRYPTO_XVIX_XAIX_AES_CTRDRBG_BLOCKLEN] = { 0U };

  /* step 1: chaining_value = 0 */

  /* the input data consists of
     buf: contains IV + L + N so size is constant 24 Bytes
     inputString: the rest of the input data
     step 4 is therefore split into three parts */

  /* step 4.1: input_block = chaining_value ^ block */
  /* since chaining value is set to 0 for the first block the result will always be the block */
  TS_MemCpy(chainingValue, buf, CRYPTO_XVIX_XAIX_AES_CTRDRBG_BLOCKLEN);
  /* step 4.2: chaining_value = Block_Encrypt(Key, input_block) */
  /* The KeyLength is hardcoded to CRYPTO_XVIX_XAIX_AES_CTRDRBG_KEYLEN which is valid input size
     and result in this function always returning E_OK. */
  job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        = chainingValue;
  job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     = CRYPTO_XVIX_XAIX_AES_CTRDRBG_BLOCKLEN;
  job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       = outputBlock;
  job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &outputLength;
  /* The key length is already checked hence this function always returns E_OK. */
  (void) Crypto_xVIx_xAIx_Int_KMn_ProcessSecondaryJob(objectId, job);

  /* next block is L + N + first 8 Bytes of InputString */
  /* step 4.1: input_block = chaining_value ^ block */
  for (i = 0U; i < CRYPTO_XVIX_XAIX_AES_CTRDRBG_BLOCKLEN; i++)
  {
    if (i < (CRYPTO_XVIX_XAIX_AES_CTRDRBG_BLOCKLEN >> 1U))
    {
      chainingValue[i] = outputBlock[i] ^ buf[CRYPTO_XVIX_XAIX_AES_CTRDRBG_BLOCKLEN + i];
    }
    else
    {
      chainingValue[i] = outputBlock[i] ^ inputString[j];
      j++;
    }
  }
  /* step 4.2: chaining_value = Block_Encrypt(Key, input_block) */
  /* The KeyLength is hardcoded to CRYPTO_XVIX_XAIX_AES_CTRDRBG_KEYLEN which is valid input size
     and result in this function always returning E_OK. */
  job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        = chainingValue;
  job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     = CRYPTO_XVIX_XAIX_AES_CTRDRBG_BLOCKLEN;
  job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       = outputBlock;
  job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &outputLength;
  /* The key length is already checked hence this function always returns E_OK. */
  (void) Crypto_xVIx_xAIx_Int_KMn_ProcessSecondaryJob(objectId, job);

  /* process for all complete blocks */
  while(CRYPTO_XVIX_XAIX_AES_CTRDRBG_BLOCKLEN <= (inputStringLength - j))
  {
    /* step 4.1: input_block = chaining_value ^ block */
    for (i = 0U; i < CRYPTO_XVIX_XAIX_AES_CTRDRBG_BLOCKLEN; i++)
    {
      chainingValue[i] = outputBlock[i] ^ inputString[j];
      j++;
    }

    /* step 4.2: chaining_value = Block_Encrypt(Key, input_block) */
    /* The KeyLength is hardcoded to CRYPTO_XVIX_XAIX_AES_CTRDRBG_KEYLEN which is valid input size
       and result in this function always returning E_OK. */
    job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        = chainingValue;
    job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     = CRYPTO_XVIX_XAIX_AES_CTRDRBG_BLOCKLEN;
    job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       = outputBlock;
    job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &outputLength;
    /* The key length is already checked hence this function always returns E_OK. */
  (void) Crypto_xVIx_xAIx_Int_KMn_ProcessSecondaryJob(objectId, job);
  };
  /* copy remaining Bytes */
  for (i = 0U; i < (inputStringLength - j); i++)
  {
    chainingValue[i] = outputBlock[i] ^ inputString[j + i];
  }
  /* append 0x80 */
  chainingValue[i] = outputBlock[i] ^ 0x80U;
  /* The rest of the next block is the last block XOR 0U */
  for (i = (inputStringLength - j) + 1U; i < CRYPTO_XVIX_XAIX_AES_CTRDRBG_BLOCKLEN; i++)
  {
    chainingValue[i] = outputBlock[i];
  }
  /* job parameters are already correctly set above */
  /* The key length is already checked hence this function always returns E_OK. */
  (void) Crypto_xVIx_xAIx_Int_KMn_ProcessSecondaryJob(objectId, job);
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON) */

/* --- Crypto_xVIx_xAIx_Int_KMn_RANDOMSEED_AES_CTRDRBG_DF ------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON)
/* Deviation CODEMETRIC-1, CODEMETRIC-2 */
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_RANDOMSEED_AES_CTRDRBG_DF
(
  P2CONST(uint8,          AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) inputString,
          uint32                                                 inputStringLength,
    P2VAR(uint8,          AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) outputString,
          uint32                                                 objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job
)
{
          Std_ReturnType                                                          retVal                                          = E_NOT_OK;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyPtr                                          = NULL_PTR;
          uint8                                                                   temp[CRYPTO_XVIX_XAIX_AES_CTRDRBG_INT_STATELEN] = { 0U }; /* the temporary String - 48 Byte */
          uint32                                                                  tempLength                                      = 0U;

  /* Buf - 16 Bytes IV + 4 Bytes L + 4 Bytes N */
  uint8                                  buf[CRYPTO_XVIX_XAIX_AES_CTRDRBG_BLOCKLEN + 8U] = { 0U };
  uint32                                 i;
  uint32                                 outputLength                                    = CRYPTO_XVIX_XAIX_AES_CTRDRBG_BLOCKLEN;
  boolean                                fromPrimitive                                   = FALSE;

  /* 2. L = len(input_string) */
  buf[16U] = (uint8)(inputStringLength >> 24U);
  buf[17U] = (uint8)(inputStringLength >> 16U);
  buf[18U] = (uint8)(inputStringLength >> 8U );
  buf[19U] = (uint8)(inputStringLength       );

  /* 3. N = number_of_bits_to_return/8 */
  buf[20U] = (uint8)((uint32)CRYPTO_XVIX_XAIX_AES_CTRDRBG_INT_STATELEN >> 24U);
  buf[21U] = (uint8)((uint32)CRYPTO_XVIX_XAIX_AES_CTRDRBG_INT_STATELEN >> 16U);
  buf[22U] = (uint8)((uint32)CRYPTO_XVIX_XAIX_AES_CTRDRBG_INT_STATELEN >>  8U);
  buf[23U] =        (        CRYPTO_XVIX_XAIX_AES_CTRDRBG_INT_STATELEN       );

  /* 4. S = L || N || input_string || 0x80 is done in the BCC function */

  /* 5. While(len(S) mod outlen) != 0 S = S || 0x00 is done in the BCC function */

  /* 8. K = Leftmost keylen bits of 0x00010203...1E1F */
  retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( job->cryptoKeyId,
                                                      CRYPTO_KE_CIPHER_KEY,
                                                     &keyPtr,
                                                      FALSE,
                                                      CRYPTO_XVIX_XAIX_SID_EMPTY
                                                    );

  if (E_OK == retVal)
  {
    fromPrimitive = FALSE;
    /* !LINKSTO Crypto.Req.KMn/RANDOMSEED_AES_CTRDRBG/GENERAL/0008,1 */
    /* Deviation TASKING-2 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_LOCK(retVal, keyPtr, fromPrimitive);
    if (E_OK == retVal)
    {
      /* !LINKSTO Crypto.Req.KMn/RANDOMSEED_AES_CTRDRBG/GENERAL/0006,1 */
      /* check for correct size */
      if (   (CRYPTO_XVIX_XAIX_AES_CTRDRBG_KEYLEN     == keyPtr->data->size                           )
          || (   (CRYPTO_XVIX_XAIX_AES_CTRDRBG_KEYLEN <= keyPtr->cnfg->description->maxSize           )
              && (TRUE                                == keyPtr->cnfg->description->allowPartialAccess)
             )
         )
      {
        for (i = 0U; i < CRYPTO_XVIX_XAIX_AES_CTRDRBG_KEYLEN; i++)
        {
          keyPtr->data->data[i] = (uint8)i;
        }
        keyPtr->data->size = CRYPTO_XVIX_XAIX_AES_CTRDRBG_KEYLEN;
      }
      else
      {
        retVal = E_NOT_OK;
      }

      CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE(keyPtr);
    }
    else
    {
      retVal = E_NOT_OK;
    }
  }

  if (E_OK == retVal)
  {
    /* 7. i = 0 */
    i = 0U;

    /* 9: while len(temp) < keylen + outlen */
    while (tempLength < CRYPTO_XVIX_XAIX_AES_CTRDRBG_INT_STATELEN)
    {
      /* 9.1 IV = i */
      buf[0U] = (uint8)(i >> 24U);
      buf[1U] = (uint8)(i >> 16U);
      buf[2U] = (uint8)(i >> 8U);
      buf[3U] = (uint8)(i);

      /* 9.2 temp = temp || BCC(K, (IV||S)) */
      Crypto_xVIx_xAIx_Int_KMn_RANDOMSEED_AES_CTRDRBG_BCC(buf,
                                                          inputString,
                                                          inputStringLength,
                                                          &temp[tempLength],
                                                          objectId,
                                                          job
                                                         );
      tempLength += CRYPTO_XVIX_XAIX_AES_CTRDRBG_BLOCKLEN;
      i++;
    }

    fromPrimitive = FALSE;
    /* 10 K = Leftmost keylen bits of temp */
    /* Deviation TASKING-2 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_LOCK(retVal, keyPtr, fromPrimitive);
    if (E_OK == retVal)
    {
      /* !LINKSTO Crypto.Req.KMn/RANDOMSEED_AES_CTRDRBG/COMMON/0001,1 */
      /* !LINKSTO Crypto.Req.KMn/RANDOMSEED_AES_CTRDRBG/COMMON/0002,1 */
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_STORE(job->cryptoKeyId,
                                         CRYPTO_KE_CIPHER_KEY,
                                         keyPtr,
                                         temp,
                                         CRYPTO_XVIX_XAIX_AES_CTRDRBG_KEYLEN,
                                         retVal
                                        );
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE(keyPtr);
    }
    else
    {
      retVal = E_NOT_OK;
    }
  }

  if (E_OK == retVal)
  {
    /* 11 X = Next outlen bits of temp*/
    TS_MemCpy(temp,
              &temp[CRYPTO_XVIX_XAIX_AES_CTRDRBG_KEYLEN],
              CRYPTO_XVIX_XAIX_AES_CTRDRBG_INT_STATELEN - CRYPTO_XVIX_XAIX_AES_CTRDRBG_KEYLEN
             );

    inputStringLength = 0U;
    /* 13 While len(temp) < number_of_bits_to_return */
    while (inputStringLength < CRYPTO_XVIX_XAIX_AES_CTRDRBG_INT_STATELEN)
    {
      /* 13.1 X = Block_Encrypt(K, X) */
      /* 13.2 temp = temp || X */
      job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        = temp;
      job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     = CRYPTO_XVIX_XAIX_AES_CTRDRBG_BLOCKLEN;
      job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       = &outputString[inputStringLength];
      job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &outputLength;
      /* The key length is already checked hence this function always returns E_OK. */
      (void) Crypto_xVIx_xAIx_Int_KMn_ProcessSecondaryJob(objectId, job);
      TS_MemCpy(temp,
                &outputString[inputStringLength],
                CRYPTO_XVIX_XAIX_AES_CTRDRBG_BLOCKLEN
               );
      inputStringLength += CRYPTO_XVIX_XAIX_AES_CTRDRBG_BLOCKLEN;
    }
  }
  return retVal;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON) */

/* --- Crypto_xVIx_xAIx_Int_KMn_RANDOMSEED_AES_CTRDRBG_Callback ----------------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON)
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_RANDOMSEED_AES_CTRDRBG_Callback
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
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON) */

/* --- Crypto_xVIx_xAIx_RandomSeedAESCTRDRBGUpdate ------------------------------------------- */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON)

static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_RandomAESCTRDRBGUpdate
(
          uint32                                                                             objectId,
  P2CONST(uint8,                                      AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) providedData,
    P2VAR(uint8,                                      AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) block,
    P2VAR(Crypto_JobType,                             AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
)
{
          Std_ReturnType                                                            result                                    = E_NOT_OK;
          uint8                                                                     temp[CRYPTO_XVIX_XAIX_INT_KMN_RANDOMSEED_AES_CTRDRBG_STATELEN] = { 0U }; /* buffer which will be used as temporary storage */
          uint32                                                                    i                                         = 0U;
          uint32                                                                    j;
          uint32                                                                    blockLength                               = CRYPTO_XVIX_XAIX_INT_KMN_RANDOMSEED_AES_CTRDRBG_BLOCKLEN;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType,   AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keySeedPtr;
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primaryPrimitive                          = primitive->data->P1;
          boolean                                                                   fromPrimitive                             = TRUE;

  /* 2 While(len(temp) < seedlen) */
  while (i < CRYPTO_XVIX_XAIX_INT_KMN_RANDOMSEED_AES_CTRDRBG_STATELEN)
  {
    /* 2.1 V = (V + 1) mod 2^outlen*/
    /* it is hard to simulate with test that encryption gives all 16 bytes as 0xFF */
    /* CHECK: NOPARSE
     * The for loop condition cannot fail at start as it is initialized with a constant.
     */
    for (j = CRYPTO_XVIX_XAIX_INT_KMN_RANDOMSEED_AES_CTRDRBG_BLOCKLEN - 1U; j != 0U; j--)
    {
      if (0xFFUL != block[j])
      {
        block[j] += 1U;
        break;
      }
      else
      {
        block[j] = 0U;
      }
    }
    /* CHECK: PARSE */

    /* 4.2 output_block = Block_Encrypt(Key, V) */
    job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode            = CRYPTO_OPERATIONMODE_SINGLECALL;
    job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputPtr        = block;
    job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputPtr       = &temp[i];
    job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.inputLength     = CRYPTO_XVIX_XAIX_INT_KMN_RANDOMSEED_AES_CTRDRBG_BLOCKLEN;
    job->CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &blockLength;

    /* start secondary primitive (encrypt aes ecb), including key expansion */
    primitive->data->P1 = primaryPrimitive;
    /* The KeyLength is already checked before update function call for valid
       input size so the result in this function is always returning E_OK. */
    (void) primitive->cnfg->description->fcnProcess(objectId,
                                                    job,
                                                    primitive
                                                   );

    /* 2.3 temp = temp || output_block */
    i += CRYPTO_XVIX_XAIX_INT_KMN_RANDOMSEED_AES_CTRDRBG_BLOCKLEN;
  }

  /* CHECK: NOPARSE
   * One path of this check is covered in CTRDRBG primitive file and the other in Keymanagement file,
   * because this function exists separately in both files as a static function.
   */
  /* step 4: temp XOR providedData */
  if(NULL_PTR != providedData)
  {
    for(i = 0U; i < CRYPTO_XVIX_XAIX_INT_KMN_RANDOMSEED_AES_CTRDRBG_STATELEN; i++)
    {
      temp[i] ^= providedData[i];
    }
  }
  /* CHECK: PARSE */

  /* step 5 & 6: symKey is the first 32 elements of temp and V is the last 16 elements of temp */
  /* Store the new symKey from temp in key Element */
  result = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( job->cryptoKeyId,
                                                      CRYPTO_KE_CIPHER_KEY,
                                                     &keySeedPtr,
                                                      FALSE,
                                                      CRYPTO_XVIX_XAIX_SID_EMPTY
                                                    );

  /* CHECK: NOPARSE
   * The key element is already checked before in the calling function, hence
   * this check cannot fail here.
   */
  if (E_OK == result)
  {
    fromPrimitive = TRUE;
    /* Deviation TASKING-1 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_LOCK(result, keySeedPtr, fromPrimitive);
  }
  /* CHECK: PARSE */

  if(E_OK == result)
  {
    /* !LINKSTO Crypto.Req.KMn/RANDOMGENERATE_AES_CTRDRBG/COMMON/0001,1 */
    /* !LINKSTO Crypto.Req.KMn/RANDOMGENERATE_AES_CTRDRBG/COMMON/0002,1 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_STORE(job->cryptoKeyId,
                                       CRYPTO_KE_CIPHER_KEY,
                                       keySeedPtr,
                                       temp,
                                       CRYPTO_XVIX_XAIX_INT_KMN_RANDOMSEED_AES_CTRDRBG_KEYLEN,
                                       result
                                      );
    keySeedPtr->data->size = CRYPTO_XVIX_XAIX_INT_KMN_RANDOMSEED_AES_CTRDRBG_KEYLEN;
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE(keySeedPtr);
  }

  if (E_OK == result)
  {
    /* Store the new V from temp in key Element */
    result = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( job->cryptoKeyId,
                                                        CRYPTO_KE_RANDOM_SEED_STATE,
                                                       &keySeedPtr,
                                                        FALSE,
                                                        CRYPTO_XVIX_XAIX_SID_EMPTY
                                                      );
    /* CHECK: NOPARSE
     * The key element is already checked before in the calling function, hence
     * this check cannot fail here.
     */
    if (E_OK == result)
    {
      fromPrimitive = TRUE;
      /* Deviation TASKING-1 */
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_LOCK(result, keySeedPtr, fromPrimitive);
    }
    /* CHECK: PARSE */

    if(E_OK == result)
    {
      /* !LINKSTO Crypto.Req.KMn/RANDOMGENERATE_AES_CTRDRBG/COMMON/0001,1 */
      /* !LINKSTO Crypto.Req.KMn/RANDOMGENERATE_AES_CTRDRBG/COMMON/0002,1 */
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_STORE( job->cryptoKeyId,
                                          CRYPTO_KE_RANDOM_SEED_STATE,
                                          keySeedPtr,
                                         &temp[CRYPTO_XVIX_XAIX_INT_KMN_RANDOMSEED_AES_CTRDRBG_KEYLEN],
                                          CRYPTO_XVIX_XAIX_INT_KMN_RANDOMSEED_AES_CTRDRBG_BLOCKLEN,
                                          result
                                        );
      keySeedPtr->data->size = CRYPTO_XVIX_XAIX_INT_KMN_RANDOMSEED_AES_CTRDRBG_BLOCKLEN;
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE(keySeedPtr);
    }
  }
  return result;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[end of file]=================================================================*/

