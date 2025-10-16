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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KeyManagement.c/0001,1 */

/*==================[deviations]==================================================================*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 20.7 (required)
 * Expressions resulting from the expansion of macro parameters shall be
 * enclosed in parentheses.
 *
 * Reason:
 * The AUTOSAR compiler abstraction requires these definitions in this way
 * and the arguments cannot be enclosed in parentheses due to C syntax.
 *
 * MISRAC2012-2) Deviated Rule: 11.3 (required)
 * A cast shall not be performed between a pointer to object type
 * and a pointer to a different object type.
 *
 * Reason:
 * The Key buffer is defined as cpu type and later downcasted in Crypto_xVIx_xAIx_KeyElementDataType,
 * so there will be no problems with the alignment.
 * The key is needed in long number representation format.
 *
 */

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
 * CODEMETRIC-1) Deviated Rule: HIS_PATH
 * not 39331 <= 2000
 *
 * Reason:
 * Improving this software quality metric would adversely effect the performance
 * of the keymanagement function.
 *
 * CODEMETRIC-2) Deviated Rule: HIS_STMT
 * not 104 <= 75
 *
 * Reason:
 * Improving this software quality metric would adversely effect the performance
 * of the keymanagement function.
 *
 * CODEMETRIC-3) Deviated Rule: HIS_V(G)
 * not 37 <= 20
 *
 * Reason:
 * Improving this software quality metric would adversely effect the performance
 * of the keymanagement function.
 *
 * CODEMETRIC-4) Deviated Rule: HIS_VOCF
 * not 13.15 <= 12
 *
 * Reason:
 * Improving this software quality metric would adversely effect the performance
 * of the keymanagement function.
 *
 */

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int.h>                /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KeyManagement.c/0002,1 */
#include <Crypto_xVIx_xAIx_Int_KeyManagement.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KeyManagement.c/0003,1 */
#include <Crypto_xVIx_xAIx_Int_Lib_LN.h>

#include <Crypto_xVIx_xAIx_Int_KMn_RANDOMSEED_AES_CTRDRBG.h>
#include <Crypto_xVIx_xAIx_Int_KMn_KEYEXCHANGE_X25519_NOTSET.h>
#include <Crypto_xVIx_xAIx_Int_KMn_KEYGENERATE_ED25519_NOTSET.h>
#include <Crypto_xVIx_xAIx_Int_KMn_KEYGENERATE_ED25519PH_NOTSET.h>
#include <Crypto_xVIx_xAIx_Int_KMn_KEYDERIVE_SINGLESTEPKDF_NOTSET.h>

/* !LINKSTO Crypto.Dsn.Gen/KMn_GenerationPhase/0001,2 */
/* !LINKSTO Crypto.Dsn.Gen/KMn_GenerationPhase/0002,2 */

#if (CRYPTO_XVIX_XAIX_KEYMNGMT_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

#if (defined CRYPTO_XVIX_XAIX_KMN_PRIPRIMITIVE)
#error CRYPTO_XVIX_XAIX_KMN_PRIPRIMITIVE already defined
#endif
/** \brief  Encodes a key management 'primitive' as a single uint32 that can be checked against
 **         the value of the corresponding part of the algorithm key element.
 **/
#define  CRYPTO_XVIX_XAIX_KMN_PRIPRIMITIVE(srv, fam, mod)  (((uint32)(srv) << 16) | ((uint32)(fam) << 8) | ((uint32)(mod)))

/*==================[type definitions]============================================================*/

/*==================[internal function declarations]==============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  Checks if there is a driver object available that can process all needed jobs and is
            enabled for KeyManagement processing.
 **
 ** Search over all driver objects if there is one available that is able to process all jobs and
 ** is enabled for KeyManagement. If one is found that is currently not processing anything else,
 ** it is locked and the object Id is returned.
 **
 ** \param[in]   jobs        A pointer to an array of jobs that shall be processed by
 **                          the driver object.
 ** \param[in]   jobsLength  The length of the jobs array.
 ** \param[out]  objectId    The driver object Id of the locked driver object.
 **
 ** \returns  Error value.
 **
 ** \retval E_OK      If a driver object was found and could be locked.
 ** \retval E_NOT_OK  If no driver object was found or the driver object was busy.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (   (FALSE                                                                  ) \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG      ) \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET  ) \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519PH_NOTSET) \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYDERIVE_SINGLESTEPKDF_NOTSET) \
    )
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_DriverObjectGetAndLock
(
  P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) jobs,
        uint32                                                 jobsLength,
  P2VAR(uint32,         AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) objectId
);
#endif /* #if (   (FALSE) ... */

/** \brief  Releases the driver object.
 **
 ** \param[out]  objectId    The driver object Id of the locked driver object.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (   (FALSE                                                                  ) \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG      ) \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET  ) \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519PH_NOTSET) \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYDERIVE_SINGLESTEPKDF_NOTSET) \
    )
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_DriverObjectRelease
(
  uint32 objectId
);
#endif /* #if (   (FALSE) ... */

/** \brief  Create key derive jobs
 **
 ** \param[in]   keyDeriveAlgorithm              Key derive algorithm .
 ** \param[out]  keyDeriveJobPrimitiveInfo       Key derive job primitives information.
 ** \param[out]  keyDeriveJobs                   Key derive jobs.
 ** \param[out]  keyDerivePrimitiveOutputLength  Key derive primitive output length.
 ** \param[out]  keyDeriveJobsLength             Key derive jobs length.
 ** \param[out]  keyDeriveJobsProcessIndex       Key derive process index.
 **
 ** \returns  Error value.
 **
 ** \retval E_OK      If Key derived jobs are created succesfully.
 ** \retval E_NOT_OK  If Key derived jobs are created fail.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (   (FALSE                                                                  ) \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYDERIVE_SINGLESTEPKDF_NOTSET) \
    )
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_CreateKeyDeriveJobs
(
        uint8                                                                keyDeriveAlgorithm,
  P2VAR(Crypto_JobPrimitiveInfoType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyDeriveJobPrimitiveInfo,
  P2VAR(Crypto_JobType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)              keyDeriveJobs,
  P2VAR(uint32,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)                      keyDerivePrimitiveOutputLength,
  P2VAR(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)                       keyDeriveJobsLength,
  P2VAR(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)                       keyDeriveJobsProcessIndex
);
#endif /* #if (   (FALSE) ... */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal constants]==========================================================*/

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/* --- Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet ------------------------------------------------ */

/* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet
(
        uint32                                                                                                                  cryptoKeyId,
        uint32                                                                                                                  keyElementId,
  /* Deviation MISRAC2012-1 */
  P2VAR(P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA), AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyElementPtr,
        boolean                                                                                                                 calledFromExt,
        uint8                                                                                                                   callerSID
)
{
  Std_ReturnType retVal;
  boolean        foundKeyElement = FALSE;
  uint32         keyElementIndex;

  if (CRYPTO_XVIX_XAIX_KEY_COUNT <= cryptoKeyId)
  {
    retVal = E_NOT_OK;
  }
  else
  {
    /* Find referenced keyElement within the cryptoKey */
    for (keyElementIndex = 0U;
         keyElementIndex < Crypto_xVIx_xAIx_Keys[cryptoKeyId].cnfg->keyElementsCount;
         keyElementIndex++
        )
    {
      if (Crypto_xVIx_xAIx_Keys[cryptoKeyId].cnfg->keyElements[keyElementIndex].cnfg->description->id == keyElementId)
      {
        foundKeyElement = TRUE;
        break;
      }
    }
    if (FALSE == foundKeyElement)
    {
#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
      if (TRUE == calledFromExt)
      {
        /* Referenced keyElement is not contained within the cryptoKey */
        /* !LINKSTO Crypto.Asr.SWS_Crypto_00077,1 */
        /* !LINKSTO Crypto.Asr.SWS_Crypto_00087,2 */
        /* !LINKSTO Crypto.Asr.SWS_Crypto_00152,1 */
        /* !LINKSTO Crypto.Asr.SWS_Crypto_00153,1 */
        (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                               CRYPTO_XVIX_XAIX_INSTANCE_ID,
                               callerSID,
                               CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                              );
      }
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
      retVal = E_NOT_OK;
    }
    else
    {
      *keyElementPtr = &Crypto_xVIx_xAIx_Keys[cryptoKeyId].cnfg->keyElements[keyElementIndex];
      retVal         = E_OK;
    }
  }
#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_OFF)
  TS_PARAM_UNUSED(calledFromExt);
  TS_PARAM_UNUSED(callerSID);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_OFF) */
  return retVal;
}

/* --- Crypto_xVIx_xAIx_Int_KMn_KeyElementSet --------------------------------------------------- */

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_Int_KMn_KeyElementSet/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeyElementSet
(
          uint32                                        cryptoKeyId,
          uint32                                        keyElementId,
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyPtr,
          uint32                                        keyLength
)
{
          Std_ReturnType                                                          retVal         = E_NOT_OK;
          boolean                                                                 fromPrimitive  = FALSE;
          uint32 tempkeyLength;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyElementPtr;

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTSET_ENTRY(cryptoKeyId,keyElementId,keyPtr,keyLength);

  tempkeyLength = keyLength;

  retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( cryptoKeyId,
                                                      keyElementId,
                                                     &keyElementPtr,
                                                      TRUE,
                                                      CRYPTO_XVIX_XAIX_SID_KEYELEMENTSET
                                                    );

  if (E_OK == retVal)
  {
    if (   (CRYPTO_XVIX_XAIX_WA_DENIED        == keyElementPtr->cnfg->description->writeAccess)
        || (CRYPTO_XVIX_XAIX_WA_INTERNAL_COPY == keyElementPtr->cnfg->description->writeAccess)
       )
    {
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementSet/0003,1 */
      /* Writing the keyElement is not allowed by the configuration */
      retVal = CRYPTO_E_KEY_WRITE_FAIL;
    }
    else
    {
      fromPrimitive = FALSE;
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementSet/0006,1 */
      /* Deviation TASKING-2 */
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_LOCK(retVal, keyElementPtr, fromPrimitive);
      if (E_OK == retVal)
      {
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementSet/0005,1 */
        if (keyElementPtr->cnfg->description->maxSize < tempkeyLength)
        {
          tempkeyLength = keyElementPtr->cnfg->description->maxSize;
        }
        /* Set key state to invalid before forwarding the request */
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementSet/0007,1 */
        Crypto_xVIx_xAIx_Keys[cryptoKeyId].data->keyState = CRYPTO_XVIX_XAIX_KEYSTATE_INVALID;
#if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_SETVALID == STD_ON)
        if (Crypto_xVIx_xAIx_Keys[cryptoKeyId].cnfg->persistentKeyElementsCount > 0U)
        {
          /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementSet/0008,1 */
          retVal = Crypto_xVIx_xAIx_Key_SetValid(cryptoKeyId, FALSE);
        }
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementSet/0009,1 */
        if (E_OK == retVal)
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_SETVALID == STD_ON) */
        {
          /* !LINKSTO Crypto.Asr.SWS_Crypto_00189,1 */
          if(keyElementPtr->cnfg->description->format == CRYPTO_XVIX_XAIX_KE_FORMAT_BIN_OCTET)
          {
            if (   (keyElementPtr->cnfg->description->maxSize            != keyLength)
                && (keyElementPtr->cnfg->description->allowPartialAccess == FALSE    )
               )
            {
              /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementSet/0004,2 */
              /* !LINKSTO Crypto.Asr.SWS_Crypto_00146, 2 */
              retVal = CRYPTO_E_KEY_SIZE_MISMATCH;
            }
            else
            {
              keyElementPtr->data->size = tempkeyLength;
              /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementSet/0010,1 */
              /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementSet/0011,1 */
              /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementSet/0012,1 */
              CRYPTO_XVIX_XAIX_KEY_ELEMENT_STORE(cryptoKeyId,
                                                 keyElementId,
                                                 keyElementPtr,
                                                 keyPtr,
                                                 tempkeyLength,
                                                 retVal
                                                );

            }
          }
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_DECODERSAKEY == STD_ON)
          /* !LINKSTO Crypto.Asr.SWS_Crypto_00185,1 */
          else
          if (keyElementPtr->cnfg->description->format == CRYPTO_XVIX_XAIX_KE_FORMAT_BIN_RSA_PRIVATEKEY)
          {
            /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementSet/0013,1 */
            /* Deviation MISRAC2012-2 <+6> */
            retVal = Crypto_xVIx_xAIx_DecodeKey
                          (
                            keyPtr,
                            keyLength,
                            TRUE,
                            (P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))keyElementPtr->data->data,
                            &keyElementPtr->data->size,
                            keyElementPtr->cnfg->description->maxSize
                          );

          }
          /* CHECK: NOPARSE
           * If non supported KeyElementFormat is chosen, an error will be reported by tresos.
           * Therefore, of the three supported formats, only two key formats can be tested for both true and false check
           * while the remaining one can only be tested for true check.
           */
          /* !LINKSTO Crypto.Asr.SWS_Crypto_00186,1 */
          else
          if (keyElementPtr->cnfg->description->format == CRYPTO_XVIX_XAIX_KE_FORMAT_BIN_RSA_PUBLICKEY)
          {
            /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementSet/0015,1 */
            /* Deviation MISRAC2012-2 <+6> */
            retVal = Crypto_xVIx_xAIx_DecodeKey
                          (
                            keyPtr,
                            keyLength,
                            FALSE,
                            (P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))keyElementPtr->data->data,
                            &keyElementPtr->data->size,
                            keyElementPtr->cnfg->description->maxSize
                          );
          }
          /* CHECK: PARSE */
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_DECODERSAKEY == STD_ON) */
          else
          {
            /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementSet/0019,1 */
            retVal = E_NOT_OK;
          }
        }
        CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE(keyElementPtr);
      }
    }
  }

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTSET_EXIT(retVal,cryptoKeyId,keyElementId,keyPtr,keyLength);

  return retVal;
}

/* --- Crypto_xVIx_xAIx_Int_KMn_KeyValidSet ----------------------------------------------------- */

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_Int_KMn_KeyValidSet/0001,1 */

#if (   (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) \
     || (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_EB ) \
    )
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeyValidSet
#else /* #if (   (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) ... */
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeySetValid
#endif /* #if (   (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) ... */
(
  uint32 cryptoKeyId
)
{
  Std_ReturnType retVal        = E_NOT_OK;
  uint32         i             = 0U;
  boolean        fromPrimitive = FALSE;

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYSETVALID_ENTRY(cryptoKeyId);

  if (CRYPTO_XVIX_XAIX_KEYSTATE_VALID == Crypto_xVIx_xAIx_Keys[cryptoKeyId].data->keyState)
  {
    retVal = E_OK;
  }
  else
  {
    for (i = 0U; i < Crypto_xVIx_xAIx_Keys[cryptoKeyId].cnfg->keyElementsCount; i++)
    {
      fromPrimitive = FALSE;
      /* Deviation TASKING-2 */
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_LOCK(retVal, &Crypto_xVIx_xAIx_Keys[cryptoKeyId].cnfg->keyElements[i], fromPrimitive);
      if (E_OK != retVal)
      {
        #if (   (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) \
              || (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_EB ) \
            )
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyValidSet/0003,2 */
        #else /* #if (   (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) ... */
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeySetValid/0003,2 */
        #endif /* #if (   (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) ... */
        retVal = E_NOT_OK;
        break;
      }
    }
    if (E_OK == retVal)
    {
#if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_SETVALID == STD_ON)
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeySetValid/0004,1 */
      if (Crypto_xVIx_xAIx_Keys[cryptoKeyId].cnfg->persistentKeyElementsCount > 0U)
      {
        retVal = Crypto_xVIx_xAIx_Key_SetValid(cryptoKeyId, TRUE);
      }
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeySetValid/0005,1 */
      if (E_OK == retVal)
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_SETVALID == STD_ON) */
      {
        Crypto_xVIx_xAIx_Keys[cryptoKeyId].data->keyState = CRYPTO_XVIX_XAIX_KEYSTATE_VALID;
      }
    }
    for (; i > 0U; i--)
    {
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE(&Crypto_xVIx_xAIx_Keys[cryptoKeyId].cnfg->keyElements[i - 1U]);
    }
  }

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYSETVALID_EXIT(retVal, cryptoKeyId);

  return retVal;
}

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KEYSETINVALID == STD_ON)
/* --- Crypto_xVIx_xAIx_Int_KMn_KeySetInvalid --------------------------------------------------- */

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_Int_KMn_KeySetInvalid/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeySetInvalid
(
  uint32 cryptoKeyId
)
{
  Std_ReturnType retVal        = E_NOT_OK;
  uint32         i             = 0U;
  boolean        fromPrimitive = FALSE;

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYSETINVALID_ENTRY(cryptoKeyId);

  if (CRYPTO_XVIX_XAIX_KEYSTATE_INVALID == Crypto_xVIx_xAIx_Keys[cryptoKeyId].data->keyState)
  {
    retVal = E_OK;
  }
  else
  {
    for (i = 0U; i < Crypto_xVIx_xAIx_Keys[cryptoKeyId].cnfg->keyElementsCount; i++)
    {
      fromPrimitive = FALSE;
      /* Deviation TASKING-2 */
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_LOCK(retVal, &Crypto_xVIx_xAIx_Keys[cryptoKeyId].cnfg->keyElements[i], fromPrimitive);
      if (E_OK != retVal)
      {
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeySetInvalid/0003,1 */
        retVal = E_NOT_OK;
        break;
      }
    }
    if (E_OK == retVal)
    {
#if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_SETVALID == STD_ON)
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeySetInvalid/0004,1 */
      if (Crypto_xVIx_xAIx_Keys[cryptoKeyId].cnfg->persistentKeyElementsCount > 0U)
      {
        retVal = Crypto_xVIx_xAIx_Key_SetValid(cryptoKeyId, FALSE);
      }
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeySetInvalid/0005,1 */
      if (E_OK == retVal)
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_SETVALID == STD_ON) */
      {
        Crypto_xVIx_xAIx_Keys[cryptoKeyId].data->keyState = CRYPTO_XVIX_XAIX_KEYSTATE_INVALID;
      }
    }
    for (; i > 0U; i--)
    {
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE(&Crypto_xVIx_xAIx_Keys[cryptoKeyId].cnfg->keyElements[i - 1U]);
    }
  }

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYSETINVALID_EXIT(retVal, cryptoKeyId);

  return retVal;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KEYSETINVALID == STD_ON) */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KEYGETSTATUS == STD_ON)
/*----[Crypto_xVIx_xAIx_Int_KMn_KeyGetStatus]-----------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_Int_KMn_KeyGetStatus/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeyGetStatus
(
        uint32                                                       cryptoKeyId,
  P2VAR(Crypto_KeyStatusType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyStatusPtr
)
{
  Std_ReturnType retVal = E_OK;

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYGETSTATUS_ENTRY(cryptoKeyId, keyStatusPtr);

  /* !LINKSTO Crypto.Asr.SWS_Crypto_00235,1 */
  *keyStatusPtr = Crypto_xVIx_xAIx_Keys[cryptoKeyId].data->keyState;

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYGETSTATUS_EXIT(retVal, cryptoKeyId, keyStatusPtr);

  return retVal;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KEYGETSTATUS == STD_ON) */

/* --- Crypto_xVIx_xAIx_Int_KMn_KeyElementGet --------------------------------------------------- */

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_Int_KMn_KeyElementGet/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeyElementGet
(
        uint32                                         cryptoKeyId,
        uint32                                         keyElementId,
  P2VAR(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) resultPtr,
  P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) resultLengthPtr
)
{
          Std_ReturnType                                                          retVal         = E_NOT_OK;
          boolean                                                                 fromPrimitive  = TRUE;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyElementPtr;

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTGET_ENTRY(cryptoKeyId,keyElementId,resultPtr,resultLengthPtr);

  retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( cryptoKeyId,
                                                      keyElementId,
                                                     &keyElementPtr,
                                                      TRUE,
                                                      CRYPTO_XVIX_XAIX_SID_KEYELEMENTGET
                                                    );

  if (E_OK == retVal)
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementGet/0005,1 */
    fromPrimitive = FALSE;
    /* Deviation TASKING-2 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(retVal, keyElementPtr, fromPrimitive);
  }
  if (E_OK == retVal)
  {
    if (   (CRYPTO_XVIX_XAIX_RA_DENIED        == keyElementPtr->cnfg->description->readAccess)
        || (CRYPTO_XVIX_XAIX_RA_INTERNAL_COPY == keyElementPtr->cnfg->description->readAccess)
       )
    {
      /* Reading the keyElement is not allowed by the configuration */
#if ((CRYPTO_XVIX_XAIX_API_ENABLED_DETRUNTIMECHECKS == STD_ON) && (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_431))
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00139,1 */
      (void) Det_ReportRuntimeError(CRYPTO_XVIX_XAIX_MODULE_ID,
                                    CRYPTO_XVIX_XAIX_INSTANCE_ID,
                                    CRYPTO_XVIX_XAIX_SID_KEYELEMENTGET,
                                    CRYPTO_XVIX_XAIX_E_RE_KEY_READ_FAIL
                                   );
#endif /* #if ((CRYPTO_XVIX_XAIX_API_ENABLED_DETRUNTIMECHECKS == STD_ON) && (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_431)) */
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementGet/0004,1 */
      retVal = CRYPTO_E_KEY_READ_FAIL;
    }
    else
    if (   (*resultLengthPtr < keyElementPtr->data->size)
        && (FALSE           == keyElementPtr->cnfg->description->allowPartialAccess)
       )
    {
#if ((CRYPTO_XVIX_XAIX_API_ENABLED_DETRUNTIMECHECKS == STD_ON) && (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_431))
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00110,1 */
      (void) Det_ReportRuntimeError(CRYPTO_XVIX_XAIX_MODULE_ID,
                                    CRYPTO_XVIX_XAIX_INSTANCE_ID,
                                    CRYPTO_XVIX_XAIX_SID_KEYELEMENTGET,
                                    CRYPTO_XVIX_XAIX_E_RE_SMALL_BUFFER
                                   );
      retVal = CRYPTO_E_SMALL_BUFFER;
#else /* #if ((CRYPTO_XVIX_XAIX_API_ENABLED_DETRUNTIMECHECKS == STD_ON) && (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_431)) */
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00093,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
      (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                             CRYPTO_XVIX_XAIX_INSTANCE_ID,
                             CRYPTO_XVIX_XAIX_SID_KEYELEMENTGET,
                             CRYPTO_E_SMALL_BUFFER
                            );
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
      retVal = CRYPTO_E_SMALL_BUFFER;
#endif /* #if ((CRYPTO_XVIX_XAIX_API_ENABLED_DETRUNTIMECHECKS == STD_ON) && (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_431)) */
    }
    else
    {
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00092,1 */
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementGet/0006,1 */
      if(keyElementPtr->cnfg->description->format == CRYPTO_XVIX_XAIX_KE_FORMAT_BIN_OCTET)
      {
        /* !LINKSTO Crypto.Asr.SWS_Crypto_00092,1 */
        if (*resultLengthPtr > keyElementPtr->data->size)
        {
          *resultLengthPtr = keyElementPtr->data->size;
        }
        TS_MemCpy(resultPtr, keyElementPtr->data->data, *resultLengthPtr);
      }
#if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_ENCODERSAKEY == STD_ON)
      else
      if (keyElementPtr->cnfg->description->format == CRYPTO_XVIX_XAIX_KE_FORMAT_BIN_RSA_PRIVATEKEY)
      {
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementGet/0007,1 */
        /* Deviation MISRAC2012-2 <+6> */
        retVal = Crypto_xVIx_xAIx_EncodeKey
                    (
                      resultPtr,
                      resultLengthPtr,
                      TRUE,
                      (P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))keyElementPtr->data->data,
                      CRYPTO_XVIX_XAIX_LN_NUMBER_LEN(keyElementPtr->data->size)
                    );
      }
      /* CHECK: NOPARSE
       * If non supported KeyElementFormat is chosen, an error will be reported by tresos.
       * Therefore, of the three supported formats, only two key formats can be tested for both true and false check
       * while the remaining one can only be tested for true check.
       */
      else
      if (keyElementPtr->cnfg->description->format == CRYPTO_XVIX_XAIX_KE_FORMAT_BIN_RSA_PUBLICKEY)
      {
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementGet/0009,1 */
        /* Deviation MISRAC2012-2 <+6> */
        retVal = Crypto_xVIx_xAIx_EncodeKey
                    (
                      resultPtr,
                      resultLengthPtr,
                      FALSE,
                      (P2VAR(Crypto_xVIx_xAIx_LNWordType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA))keyElementPtr->data->data,
                      CRYPTO_XVIX_XAIX_LN_NUMBER_LEN(keyElementPtr->data->size)
                    );
      }
      /* CHECK: PARSE */
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_ENCODERSAKEY == STD_ON) */
      else
      {
        retVal = E_NOT_OK;
      }
    }
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(keyElementPtr);
  }
#if ((CRYPTO_XVIX_XAIX_API_ENABLED_DETRUNTIMECHECKS == STD_ON) && (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_431))
  if (CRYPTO_E_KEY_NOT_AVAILABLE == retVal)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00140,1 */
    (void) Det_ReportRuntimeError(CRYPTO_XVIX_XAIX_MODULE_ID,
                                  CRYPTO_XVIX_XAIX_INSTANCE_ID,
                                  CRYPTO_XVIX_XAIX_SID_KEYELEMENTGET,
                                  CRYPTO_XVIX_XAIX_E_RE_KEY_NOT_AVAILABLE
                                 );
  }
#endif /* #if ((CRYPTO_XVIX_XAIX_API_ENABLED_DETRUNTIMECHECKS == STD_ON) && (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_431)) */

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTGET_EXIT(retVal, cryptoKeyId,keyElementId,resultPtr,resultLengthPtr);

  return retVal;
}

/* --- Crypto_xVIx_xAIx_Int_KMn_KeyElementCopy -------------------------------------------------- */

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_Int_KMn_KeyElementCopy/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeyElementCopy
(
  uint32 cryptoKeyId,
  uint32 keyElementId,
  uint32 targetCryptoKeyId,
  uint32 targetKeyElementId
)
{
          Std_ReturnType                                                          retVal               = E_NOT_OK;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) sourceKeyElementPtr  = NULL_PTR;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) targetKeyElementPtr  = NULL_PTR;
          boolean                                                                 fromPrimitive        = FALSE;

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTCOPY_ENTRY(cryptoKeyId,keyElementId,targetCryptoKeyId,targetKeyElementId);

  retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( cryptoKeyId,
                                                      keyElementId,
                                                     &sourceKeyElementPtr,
                                                      TRUE,
                                                      CRYPTO_XVIX_XAIX_SID_KEYELEMENTCOPY
                                                    );

  if (retVal == E_OK)
  {
    if (CRYPTO_XVIX_XAIX_RA_DENIED == sourceKeyElementPtr->cnfg->description->readAccess)
    {
      /* Reading the source keyElement is not allowed by the configuration */
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementCopy/0003,1 */
      retVal = CRYPTO_E_KEY_READ_FAIL;
    }
    else
    {
      retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( targetCryptoKeyId,
                                                          targetKeyElementId,
                                                         &targetKeyElementPtr,
                                                          TRUE,
                                                          CRYPTO_XVIX_XAIX_SID_KEYELEMENTCOPY
                                                        );
    }
  }
  if (retVal == E_OK)
  {
    if (   (CRYPTO_XVIX_XAIX_WA_DENIED        == targetKeyElementPtr->cnfg->description->writeAccess)
        || (   (CRYPTO_XVIX_XAIX_RA_INTERNAL_COPY == sourceKeyElementPtr->cnfg->description->readAccess )
            && (CRYPTO_XVIX_XAIX_RA_ALLOWED == targetKeyElementPtr->cnfg->description->readAccess)
           )
       )
    {
      /* Writing the target keyElement is not allowed by the configuration */
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementCopy/0004,2 */
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementCopy/0008,1 */
      retVal = CRYPTO_E_KEY_WRITE_FAIL;
    }
    else
    {
      fromPrimitive = FALSE;
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementCopy/0005, 1 */
      /* Deviation TASKING-2 */
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(retVal, sourceKeyElementPtr, fromPrimitive);
      if (E_OK == retVal)
      {
        fromPrimitive = FALSE;
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementCopy/0006, 1 */
        /* Deviation TASKING-2 */
        CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_LOCK(retVal, targetKeyElementPtr, fromPrimitive);
        if (E_OK == retVal)
        {
          if (   (sourceKeyElementPtr->data->size == targetKeyElementPtr->cnfg->description->maxSize)
              || (   (  sourceKeyElementPtr->data->size
                      < targetKeyElementPtr->cnfg->description->maxSize
                     )
                  && (   TRUE
                      == targetKeyElementPtr->cnfg->description->allowPartialAccess
                     )
                 )
             )
          {
            targetKeyElementPtr->data->size = sourceKeyElementPtr->data->size;
            /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementCopy/0009, 1 */
            /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementCopy/0010, 1 */
            CRYPTO_XVIX_XAIX_KEY_ELEMENT_STORE(targetCryptoKeyId,
                                               targetKeyElementId,
                                               targetKeyElementPtr,
                                               sourceKeyElementPtr->data->data,
                                               sourceKeyElementPtr->data->size,
                                               retVal
                                              );
          }
          else
          {
            /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementCopy/0007, 1 */
            retVal = CRYPTO_E_KEY_SIZE_MISMATCH;
          }
          CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE(targetKeyElementPtr);
        }
        CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(sourceKeyElementPtr);
      }
    }
  }

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTCOPY_EXIT(retVal, cryptoKeyId,keyElementId,targetCryptoKeyId,targetKeyElementId);

  return retVal;
}

/* --- Crypto_xVIx_xAIx_Int_KMn_KeyCopy --------------------------------------------------------- */

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_Int_KMn_KeyCopy/0001,1 */

/* Deviation CODEMETRIC-1, CODEMETRIC-2, CODEMETRIC-3, CODEMETRIC-4 */
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeyCopy
(
  uint32 cryptoKeyId,
  uint32 targetCryptoKeyId
)
{
          Std_ReturnType                                                          retVal               = E_NOT_OK;
          uint32                                                                  i                    = 0U;
          uint32                                                                  j                    = 0U;
          boolean                                                                 fromPrimitive        = FALSE;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) sourceKeyElementPtr  = NULL_PTR;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) targetKeyElementPtr  = NULL_PTR;

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYCOPY_ENTRY(cryptoKeyId,targetCryptoKeyId);

  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyCopy/0003,1 */
  if (CRYPTO_XVIX_XAIX_KEYSTATE_INVALID != Crypto_xVIx_xAIx_Keys[cryptoKeyId].data->keyState)
  {
    /* check that all the elements in the source key are readable. */
    for (i = 0U; i < Crypto_xVIx_xAIx_Keys[cryptoKeyId].cnfg->keyElementsCount; i++)
    {
      sourceKeyElementPtr = &Crypto_xVIx_xAIx_Keys[cryptoKeyId].cnfg->keyElements[i];
      fromPrimitive = FALSE;
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyCopy/0005,1 */
      /* Deviation TASKING-2 */
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(retVal, sourceKeyElementPtr, fromPrimitive);
      if (E_OK == retVal)
      {
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyCopy/0011,1 */
        retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( targetCryptoKeyId,
                                                            sourceKeyElementPtr->cnfg->description->id,
                                                           &targetKeyElementPtr,
                                                            TRUE,
                                                            CRYPTO_XVIX_XAIX_SID_KEYCOPY
                                                          );
        if (E_OK == retVal)
        {
          fromPrimitive = FALSE;
          /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyCopy/0006,1 */
          /* Deviation TASKING-2 */
          CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_LOCK(retVal, targetKeyElementPtr, fromPrimitive);
        }
        /* if lock of targetElement could not be retrieved the source lock has to be released */
        if (E_OK != retVal)
        {
          CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(sourceKeyElementPtr);
        }
      }

      if (E_OK == retVal)
      {
        /* check access rigths and sizes */
        if (CRYPTO_XVIX_XAIX_RA_DENIED == sourceKeyElementPtr->cnfg->description->readAccess)
        {
          /* Reading the source keyElement is not allowed by the configuration */
          /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyCopy/0007,1 */
          retVal = CRYPTO_E_KEY_READ_FAIL;
          CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE(targetKeyElementPtr);
          CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(sourceKeyElementPtr);
        }
        if (   (E_OK == retVal)
            && ((CRYPTO_XVIX_XAIX_WA_DENIED == targetKeyElementPtr->cnfg->description->writeAccess)
            || (   (CRYPTO_XVIX_XAIX_RA_INTERNAL_COPY == sourceKeyElementPtr->cnfg->description->readAccess)
                && (CRYPTO_XVIX_XAIX_RA_ALLOWED == targetKeyElementPtr->cnfg->description->readAccess)
               ))
           )
        {
          /* Writing the target keyElement is not allowed by the configuration */
          /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyCopy/0008,2 */
          /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyCopy/0012,1 */
          retVal = CRYPTO_E_KEY_WRITE_FAIL;
          CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE(targetKeyElementPtr);
          CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(sourceKeyElementPtr);
        }
        if (   (E_OK == retVal)
            && (sourceKeyElementPtr->data->size != targetKeyElementPtr->cnfg->description->maxSize)
            && (
                   (    (sourceKeyElementPtr->data->size > targetKeyElementPtr->cnfg->description->maxSize)
                     && (FALSE == sourceKeyElementPtr->cnfg->description->allowPartialAccess)
                   )
                || (    (sourceKeyElementPtr->data->size < targetKeyElementPtr->cnfg->description->maxSize)
                     && (FALSE == targetKeyElementPtr->cnfg->description->allowPartialAccess)
                   )
               )
           )
        {
          /* Writing the target keyElement with this size is not allowed by the configuration */
          /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyCopy/0009,1 */
          /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyCopy/0010,1 */
          retVal = CRYPTO_E_KEY_SIZE_MISMATCH;
          CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE(targetKeyElementPtr);
          CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(sourceKeyElementPtr);
        }
      }
      if (E_OK != retVal)
      {
        break;
      }
    }
    if (E_OK == retVal)
    {
      /* dry run was ok so copy the keyElements */
      for (j = 0U; j < Crypto_xVIx_xAIx_Keys[cryptoKeyId].cnfg->keyElementsCount; j++)
      {
        sourceKeyElementPtr = &Crypto_xVIx_xAIx_Keys[cryptoKeyId].cnfg->keyElements[j];
        /* dry run was successful so this function can not fail */
        (void) Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( targetCryptoKeyId,
                                                          sourceKeyElementPtr->cnfg->description->id,
                                                         &targetKeyElementPtr,
                                                          TRUE,
                                                          CRYPTO_XVIX_XAIX_SID_KEYCOPY
                                                        );
        if (sourceKeyElementPtr->data->size > targetKeyElementPtr->cnfg->description->maxSize)
        {
          targetKeyElementPtr->data->size = targetKeyElementPtr->cnfg->description->maxSize;
        }
        else
        {
          targetKeyElementPtr->data->size = sourceKeyElementPtr->data->size;
        }
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyCopy/0013,1 */
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyCopy/0014,1 */
        CRYPTO_XVIX_XAIX_KEY_ELEMENT_STORE(targetCryptoKeyId,
                                           sourceKeyElementPtr->cnfg->description->id,
                                           targetKeyElementPtr,
                                           sourceKeyElementPtr->data->data,
                                           targetKeyElementPtr->data->size,
                                           retVal
                                          );
      }
    }
    /* release open locks */
    for (; i > 0U; i--)
    {
      sourceKeyElementPtr = &Crypto_xVIx_xAIx_Keys[cryptoKeyId].cnfg->keyElements[i - 1U];
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(sourceKeyElementPtr);
      /* this function was already run succesfully some lines above */
      (void) Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( targetCryptoKeyId,
                                                        sourceKeyElementPtr->cnfg->description->id,
                                                       &targetKeyElementPtr,
                                                        TRUE,
                                                        CRYPTO_XVIX_XAIX_SID_KEYCOPY
                                                      );
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE(targetKeyElementPtr);
    }
  }

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYCOPY_EXIT(retVal, cryptoKeyId,targetCryptoKeyId);

  return retVal;
}

/* --- Crypto_xVIx_xAIx_Int_KMn_KeyElementIdsGet ------------------------------------------------ */

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_Int_KMn_KeyElementIdsGet/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeyElementIdsGet
(
        uint32                                         cryptoKeyId,
  P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyElementIdsPtr,
  P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyElementIdsLengthPtr
)
{
  uint32 i = 0U;

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTIDSGET_ENTRY(cryptoKeyId,keyElementIdsPtr,keyElementIdsLengthPtr);

  for (i = 0U; i < Crypto_xVIx_xAIx_Keys[cryptoKeyId].cnfg->keyElementsCount; i++)
  {
    keyElementIdsPtr[i] = Crypto_xVIx_xAIx_Keys[cryptoKeyId].cnfg->keyElements[i].cnfg->description->id;
  }
  *keyElementIdsLengthPtr = Crypto_xVIx_xAIx_Keys[cryptoKeyId].cnfg->keyElementsCount;

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTIDSGET_EXIT(retVal, cryptoKeyId,keyElementIdsPtr,keyElementIdsLengthPtr);

  return E_OK;
}

/* --- Crypto_xVIx_xAIx_Int_KMn_RandomSeed ------------------------------------------------------ */

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_Int_KMn_RandomSeed/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_RandomSeed
(
          uint32                                        cryptoKeyId,
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) entropyPtr,
          uint32                                        entropyLength
)
{

#if (   FALSE                                                                  \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG   ) \
    )
          Std_ReturnType                                                          result             = E_NOT_OK;
          Std_ReturnType                                                          retVal             = E_NOT_OK;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) algoPtr            = NULL_PTR;
          uint32                                                                  objectId;
          uint32                                                                  primaryPrimitive   = 0xFFFFFFFFU;
    P2VAR(uint8,                           AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) wkspDataPtr        = NULL_PTR;
          uint32                                                                  wkspDataLen        = 0U;
          boolean                                                                 fromPrimitive      = FALSE;

#if (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG)
  Crypto_PrimitiveInfoType tmpl_RANDOMSEED_AES_CTRDRBG_primitiveInfo =
  {
    16U,
    CRYPTO_ENCRYPT,
    { CRYPTO_ALGOFAM_AES, CRYPTO_ALGOFAM_NOT_SET, 32U, CRYPTO_ALGOMODE_ECB }
  };
  Crypto_JobPrimitiveInfoType tmpl_RANDOMSEED_AES_CTRDRBG_jobPrimitiveInfo =
  {
    0U,
    NULL_PTR,
    0U,
    0U,
    CRYPTO_PROCESSING_SYNC,
    FALSE
  };
#endif /* #if (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG) */

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_RANDOMSEED_ENTRY(cryptoKeyId,seedPtr,seedLength);

  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_RandomSeed/0002,1 */
  if (CRYPTO_XVIX_XAIX_KEYSTATE_VALID == Crypto_xVIx_xAIx_Keys[cryptoKeyId].data->keyState)
  {
    retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( cryptoKeyId,
                                                        CRYPTO_KE_RANDOM_ALGORITHM,
                                                       &algoPtr,
                                                        FALSE,
                                                        CRYPTO_XVIX_XAIX_SID_EMPTY
                                                      );

    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_RandomSeed/0003,1,
                Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_RandomSeed/0004,1
    */
    if (   (E_OK == retVal)
        && (   (2U == algoPtr->cnfg->description->maxSize)
            || (6U == algoPtr->cnfg->description->maxSize)
           )
       )
    {
      fromPrimitive = FALSE;
      /* Deviation TASKING-2 */
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(retVal, algoPtr, fromPrimitive);

      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_RandomSeed/0005,2 */
      if (E_OK == retVal)
      {
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_RandomSeed/0006,1 */
        if (2U <= algoPtr->data->size)
        {
          primaryPrimitive = CRYPTO_XVIX_XAIX_KMN_PRIPRIMITIVE(CRYPTO_RANDOMSEED, algoPtr->data->data[0U], algoPtr->data->data[1U]);
        }

        switch (primaryPrimitive)
        {

#if (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG)
          case CRYPTO_XVIX_XAIX_KMN_PRIPRIMITIVE(CRYPTO_RANDOMSEED, CRYPTO_ALGOFAM_AES, CRYPTO_ALGOMODE_CTRDRBG):
          case CRYPTO_XVIX_XAIX_KMN_PRIPRIMITIVE(CRYPTO_RANDOMSEED, CRYPTO_ALGOFAM_AES, CRYPTO_ALGOMODE_NOT_SET):
          {
            Crypto_JobType jobs[1U];

            tmpl_RANDOMSEED_AES_CTRDRBG_jobPrimitiveInfo.primitiveInfo = &tmpl_RANDOMSEED_AES_CTRDRBG_primitiveInfo;
            jobs[0U].jobPrimitiveInfo                                  = &tmpl_RANDOMSEED_AES_CTRDRBG_jobPrimitiveInfo;
            jobs[0U].cryptoKeyId                                       = cryptoKeyId;
            jobs[0U].CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode     = CRYPTO_OPERATIONMODE_SINGLECALL;

            retVal = Crypto_xVIx_xAIx_Int_KMn_DriverObjectGetAndLock(jobs, 1U, &objectId);

            /* !LINKSTO Crypto.Req.KMn/RANDOMSEED_AES_CTRDRBG/GENERAL/0002,1 */
            /* !LINKSTO Crypto.Req.KMn/RANDOMSEED_AES_CTRDRBG/GENERAL/0003,1 */
            /* !LINKSTO Crypto.Req.KMn/RANDOMSEED_AES_CTRDRBG/GENERAL/0004,1 */
            if (E_OK == retVal)
            {
              /* !LINKSTO Crypto.Req.KMn/RANDOMSEED_AES_CTRDRBG/GENERAL/0005,1 */
              result = Crypto_xVIx_xAIx_Int_KMn_RANDOMSEED_AES_CTRDRBG_Process(objectId, jobs, 1U, wkspDataPtr, wkspDataLen, cryptoKeyId, entropyPtr, entropyLength);
              Crypto_xVIx_xAIx_Int_KMn_DriverObjectRelease(objectId);
            }
          }
          break;
#endif /* #if (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG) */

          default:
          {
            /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_RandomSeed/0100,1 */
          }
          break;
        }

        CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(algoPtr);
      }
    }
  }

#else /* #if (   FALSE... */
  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_RandomSeed/0001,1 */
  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(cryptoKeyId);
  TS_PARAM_UNUSED(entropyPtr);
  TS_PARAM_UNUSED(entropyLength);

#endif /* #if (   FALSE... */

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_RANDOMSEED_EXIT(result, cryptoKeyId,seedPtr,seedLength);

  return result;
}

/* --- Crypto_xVIx_xAIx_Int_KMn_KeyGenerate ----------------------------------------------------- */

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_Int_KMn_KeyGenerate/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeyGenerate
(
  uint32 cryptoKeyId
)
{

#if (   FALSE                                                                       \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET)     \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519PH_NOTSET  ) \
    )
          Std_ReturnType                                                          result             = E_NOT_OK;
          Std_ReturnType                                                          retVal             = E_NOT_OK;
          boolean                                                                 fromPrimitive      = FALSE;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) algoPtr            = NULL_PTR;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) wkspPtr            = NULL_PTR;
          uint32                                                                  objectId;
          uint32                                                                  primaryPrimitive   = 0xFFFFFFFFU;
          uint32                                                                  wkspDataLen        = 0U;

#if (   FALSE                                                                       \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET)     \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519PH_NOTSET  ) \
    )
  Crypto_PrimitiveInfoType tmpl_HASH_SHA2512_NOTSET_primitiveInfo =
  {
    64U,
    CRYPTO_HASH,
    { CRYPTO_ALGOFAM_SHA2_512, CRYPTO_ALGOFAM_NOT_SET, 0U, CRYPTO_ALGOFAM_NOT_SET }
  };
  Crypto_JobPrimitiveInfoType tmpl_HASH_SHA2512_NOTSET_jobPrimitiveInfo =
  {
    0U,
    NULL_PTR,
    0U,
    0U,
    CRYPTO_PROCESSING_SYNC,
    FALSE
  };
#endif /* #if (   FALSE ... */

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ENTRY(cryptoKeyId);

  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyGenerate/0002,1 */
  if (CRYPTO_XVIX_XAIX_KEYSTATE_VALID == Crypto_xVIx_xAIx_Keys[cryptoKeyId].data->keyState)
  {
    retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( cryptoKeyId,
                                                        CRYPTO_KE_KEYGENERATE_ALGORITHM,
                                                       &algoPtr,
                                                        FALSE,
                                                        CRYPTO_XVIX_XAIX_SID_EMPTY
                                                      );

    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyGenerate/0003,1,
                Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyGenerate/0004,1
    */
    if (   (E_OK == retVal)
        && (   (2U == algoPtr->cnfg->description->maxSize)
            || (6U == algoPtr->cnfg->description->maxSize)
           )
       )
    {
      fromPrimitive = FALSE;
      /* Deviation TASKING-2 */
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(retVal, algoPtr, fromPrimitive);

      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyGenerate/0005,1 */
      if (E_OK == retVal)
      {
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyGenerate/0006,1 */
        if (2U <= algoPtr->data->size)
        {
          primaryPrimitive = CRYPTO_XVIX_XAIX_KMN_PRIPRIMITIVE(CRYPTO_KEYGENERATE, algoPtr->data->data[0U], algoPtr->data->data[1U]);
        }

        switch (primaryPrimitive)
        {
#if (   FALSE                                                                       \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET)     \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519PH_NOTSET  ) \
    )
          case CRYPTO_XVIX_XAIX_KMN_PRIPRIMITIVE(CRYPTO_KEYGENERATE, CRYPTO_ALGOFAM_ED25519, CRYPTO_ALGOMODE_NOT_SET):
          case CRYPTO_XVIX_XAIX_KMN_PRIPRIMITIVE(CRYPTO_KEYGENERATE, CRYPTO_ALGOFAM_ED25519PH, CRYPTO_ALGOMODE_NOT_SET):
          {
            retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( cryptoKeyId,
                                                                CRYPTO_XVIX_XAIX_KE_KMNCOMMON_WORKSPACE,
                                                               &wkspPtr,
                                                                FALSE,
                                                                CRYPTO_XVIX_XAIX_SID_EMPTY
                                                              );
            /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519_NOTSET/GENERAL/0002,1   */
            /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519PH_NOTSET/GENERAL/0002,1 */
#if (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET)
            /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519_NOTSET/GENERAL/0015,1 */
#endif /* #if (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET) */
#if (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519PH_NOTSET)
            /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519PH_NOTSET/GENERAL/0015,1 */
#endif /* #if (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519PH_NOTSET) */
            if (   (E_OK == retVal)
                && (408U <= wkspPtr->data->size)
               )
            {
              fromPrimitive = FALSE;
              /* Deviation TASKING-2 */
              CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_LOCK(retVal, wkspPtr, fromPrimitive);

              /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519_NOTSET/GENERAL/0016,1   */
              /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519PH_NOTSET/GENERAL/0016,1 */
              if (E_OK == retVal)
              {
                Crypto_JobType jobs[1U];

                tmpl_HASH_SHA2512_NOTSET_jobPrimitiveInfo.primitiveInfo = &tmpl_HASH_SHA2512_NOTSET_primitiveInfo;
                jobs[0U].jobPrimitiveInfo                               = &tmpl_HASH_SHA2512_NOTSET_jobPrimitiveInfo;
                jobs[0U].cryptoKeyId                                    = cryptoKeyId;
                jobs[0U].CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.mode  = CRYPTO_OPERATIONMODE_SINGLECALL;

                retVal = Crypto_xVIx_xAIx_Int_KMn_DriverObjectGetAndLock(jobs, 1U, &objectId);

#if (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET)
                /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519_NOTSET/GENERAL/0017,1 */
                /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519_NOTSET/GENERAL/0018,1 */
                /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519_NOTSET/GENERAL/0019,1 */
#endif /* #if (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET) */
#if (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519PH_NOTSET)
                /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519PH_NOTSET/GENERAL/0017,1 */
                /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519PH_NOTSET/GENERAL/0018,1 */
                /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519PH_NOTSET/GENERAL/0019,1 */
#endif /* #if (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519PH_NOTSET) */
                if (E_OK == retVal)
                {
#if (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET)
                  /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519_NOTSET/GENERAL/0020,1 */
                  result = Crypto_xVIx_xAIx_Int_KMn_KEYGENERATE_ED25519_NOTSET_Process(objectId, jobs, 1U, wkspPtr->data->data, wkspDataLen, cryptoKeyId);
#endif /* #if (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET) */
#if (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519PH_NOTSET)
                  /* !LINKSTO Crypto.Req.KMn/KEYGENERATE_ED25519PH_NOTSET/GENERAL/0020,1 */
                  result = Crypto_xVIx_xAIx_Int_KMn_KEYGENERATE_ED25519PH_NOTSET_Process(objectId, jobs, 1U, wkspPtr->data->data, wkspDataLen, cryptoKeyId);
#endif /* #if (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519PH_NOTSET) */
                  Crypto_xVIx_xAIx_Int_KMn_DriverObjectRelease(objectId);

                  CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE(wkspPtr);
                }
              }
            }
          }
          break;
#endif /* #if (   FALSE ... */

          default:
          {
            /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyGenerate/0100,1 */
          }
          break;
        }

        CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(algoPtr);
      }
    }
  }

#else /* #if (   FALSE... */

  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyGenerate/0001,1 */
  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(cryptoKeyId);

#endif /* #if (   FALSE... */

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_EXIT(result, cryptoKeyId);

  return result;
}

/* --- Crypto_xVIx_xAIx_Int_KMn_KeyDerive ------------------------------------------------------- */

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_Int_KMn_KeyDerive/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeyDerive
(
  uint32 cryptoKeyId,
  uint32 targetCryptoKeyId
)
{

#if (   (FALSE                                                                  ) \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYDERIVE_SINGLESTEPKDF_NOTSET) \
    )
  uint32 keyDeriveObjectId;
  Crypto_JobType keyDeriveJobs[CRYPTO_XVIX_XAIX_KDF_JOBLIST_MAXLEN];
  uint8 keyDeriveJobsLength;
  uint8 keyDeriveJobsProcessIndex;
  uint32 keyDerivePrimitiveOutputLength[CRYPTO_XVIX_XAIX_KDF_JOBLIST_MAXLEN];
  Crypto_JobPrimitiveInfoType keyDeriveJobPrimitiveInfo[CRYPTO_XVIX_XAIX_KDF_JOBLIST_MAXLEN] =
  {
    {0U, NULL_PTR, 0U, 0U, CRYPTO_PROCESSING_SYNC, FALSE},
    {0U, NULL_PTR, 0U, 0U, CRYPTO_PROCESSING_SYNC, FALSE}
  };
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyDeriveAlgorithmPtr = NULL_PTR;
                                                                   Std_ReturnType retVal                = E_NOT_OK;
                                                                   Std_ReturnType lockResult            = E_NOT_OK;
                                                                   boolean        fromPrimitive         = FALSE;

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYDERIVE_ENTRY(cryptoKeyId,targetCryptoKeyId);

  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyDerive/0003,1 */
  if (CRYPTO_XVIX_XAIX_KEYSTATE_VALID == Crypto_xVIx_xAIx_Keys[cryptoKeyId].data->keyState)
  {
    /* !LINKSTO Crypto.Req.KMn/KEYDERIVE_SINGLESTEPKDF_NOTSET/GENERAL/0003,1 */
    /* !LINKSTO Crypto.Req.KMn/KEYDERIVE_SINGLESTEPKDF_NOTSET/GENERAL/0004,1 */
    retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( cryptoKeyId,
                                                        CRYPTO_KE_KEYDERIVATION_ALGORITHM,
                                                       &keyDeriveAlgorithmPtr,
                                                        FALSE,
                                                        CRYPTO_XVIX_XAIX_SID_EMPTY
                                                      );
  }
  if (E_OK == retVal)
  {
    /* Deviation TASKING-2 */
    CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(lockResult, keyDeriveAlgorithmPtr, fromPrimitive);
    if (E_OK == lockResult)
    {
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyDerive/0010,1 */
      /* !LINKSTO Crypto.Req.KMn/KEYDERIVE_SINGLESTEPKDF_NOTSET/GENERAL/0005,1 */
      retVal = Crypto_xVIx_xAIx_Int_CreateKeyDeriveJobs( keyDeriveAlgorithmPtr->data->data[0U],
                                                         keyDeriveJobPrimitiveInfo,
                                                         keyDeriveJobs,
                                                         keyDerivePrimitiveOutputLength,
                                                        &keyDeriveJobsLength,
                                                        &keyDeriveJobsProcessIndex
                                                        );
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(keyDeriveAlgorithmPtr);

      if (E_OK == retVal)
      {
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyDerive/0012,1 */
        retVal = Crypto_xVIx_xAIx_Int_KMn_DriverObjectGetAndLock(keyDeriveJobs, keyDeriveJobsLength, &keyDeriveObjectId);
        if (E_OK == retVal)
        {
          /* CHECK: NOPARSE */
          /* Defensive programming:
           * Key Derived Process function address shall not be NULLPTR.
           */
          if (NULL_PTR != Crypto_xVIx_xAIx_Int_KDF_Primitives[keyDeriveJobsProcessIndex])
          {
            /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyDerive/0011,1 */
            /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyDerive/0014,1 */
            retVal = Crypto_xVIx_xAIx_Int_KDF_Primitives[keyDeriveJobsProcessIndex]( keyDeriveObjectId,
                                                                                    keyDeriveJobs,
                                                                                    keyDeriveJobsLength,
                                                                                    NULL_PTR,
                                                                                    0U,
                                                                                    cryptoKeyId,
                                                                                    targetCryptoKeyId
                                                                                    );
          }
          /* CHECK: PARSE */
          Crypto_xVIx_xAIx_Int_KMn_DriverObjectRelease(keyDeriveObjectId);
        }
      }
    }
    else
    {
      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyDerive/0008,2 */
      retVal = E_NOT_OK;
    }
  }
#else /* #if (   FALSE... */
  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyDerive/0002,1 */
  Std_ReturnType retVal = E_NOT_OK;

  TS_PARAM_UNUSED(cryptoKeyId);
  TS_PARAM_UNUSED(targetCryptoKeyId);

#endif /* #if (   FALSE... */
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00166,1 */

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYDERIVE_EXIT(retVal, cryptoKeyId,targetCryptoKeyId);

  return retVal;
}

/* --- Crypto_xVIx_xAIx_Int_CreateKeyDeriveJobs --------------------------------------------- */

#if (   (FALSE                                                                  ) \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYDERIVE_SINGLESTEPKDF_NOTSET) \
    )
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_CreateKeyDeriveJobs
(
        uint8                                                                keyDeriveAlgorithm,
  P2VAR(Crypto_JobPrimitiveInfoType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyDeriveJobPrimitiveInfo,
  P2VAR(Crypto_JobType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)              keyDeriveJobs,
  P2VAR(uint32,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)                      keyDerivePrimitiveOutputLength,
  P2VAR(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)                       keyDeriveJobsLength,
  P2VAR(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)                       keyDeriveJobsProcessIndex
)
{
  uint8 i;
  uint8 primitiveIndex;
  Std_ReturnType retVal = E_NOT_OK;

  if (keyDeriveAlgorithm < CRYPTO_XVIX_XAIX_KDF_ALGORITHMLIST_MAXLEN)
  {
    *keyDeriveJobsLength       = Crypto_xVIx_xAIx_Int_KDF_ConfigKmnInterface[keyDeriveAlgorithm].keyDeriveJobsLength;
    *keyDeriveJobsProcessIndex = Crypto_xVIx_xAIx_Int_KDF_ConfigKmnInterface[keyDeriveAlgorithm].keyDeriveProcessJobsIndex;
    for (i = 0U; i < *keyDeriveJobsLength; i++)
    {
      primitiveIndex = Crypto_xVIx_xAIx_Int_KDF_ConfigKmnInterface[keyDeriveAlgorithm].keyDeriveJobs[i].primitiveIndex;
      keyDerivePrimitiveOutputLength[i] = Crypto_xVIx_xAIx_Int_KDF_ConfigKmnInterface[keyDeriveAlgorithm].keyDeriveJobs[i].primitiveOutputLength;
      keyDeriveJobPrimitiveInfo[i].primitiveInfo = &Crypto_xVIx_xAIx_Int_KDF_SupportedPrimitives[primitiveIndex];
      keyDeriveJobs[i].jobPrimitiveInfo = &keyDeriveJobPrimitiveInfo[i];
      keyDeriveJobs[i].CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT.outputLengthPtr = &keyDerivePrimitiveOutputLength[i];
    }
    retVal = E_OK;
  }
  return retVal;
}
#endif /* #if (   (FALSE) ... */

/* --- Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcPubVal ------------------------------------------- */

/* !LINKSTO Crypto.Asr.SWS_Crypto_00167,1, Crypto.Dsn.Api/Interfaces/Crypto_Int_KMn_KeyExchangeCalcPubVal/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcPubVal
(
        uint32                                         cryptoKeyId,
  P2VAR(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) publicValuePtr,
  P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) publicValueLengthPtr
)
{
#if (   FALSE                                                                  \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYEXCHANGE_X25519_NOTSET) \
    )

          Std_ReturnType                                                          result             = E_NOT_OK;
          Std_ReturnType                                                          retVal             = E_NOT_OK;
          boolean                                                                 fromPrimitive      = FALSE;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) algoPtr            = NULL_PTR;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) wkspPtr            = NULL_PTR;
          uint32                                                                  primaryPrimitive   = 0xFFFFFFFFU;
          uint32                                                                  wkspDataLen        = 0U;

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGECALCPUBVAL_ENTRY(cryptoKeyId,publicValuePtr,publicValueLengthPtr);

  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcPubVal/0002,1 */
  if (CRYPTO_XVIX_XAIX_KEYSTATE_VALID == Crypto_xVIx_xAIx_Keys[cryptoKeyId].data->keyState)
  {
    retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( cryptoKeyId,
                                                        CRYPTO_KE_KEYEXCHANGE_ALGORITHM,
                                                       &algoPtr,
                                                        FALSE,
                                                        CRYPTO_XVIX_XAIX_SID_EMPTY
                                                      );

    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcPubVal/0003,1,
                Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcPubVal/0004,1
    */
    if (   (E_OK == retVal)
        && (   (2U == algoPtr->cnfg->description->maxSize)
            || (6U == algoPtr->cnfg->description->maxSize)
           )
       )
    {
      fromPrimitive = FALSE;
      /* Deviation TASKING-2 */
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(retVal, algoPtr, fromPrimitive);

      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcPubVal/0005,2 */
      if (E_OK == retVal)
      {
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcPubVal/0006,1 */
        if (2U <= algoPtr->data->size)
        {
          primaryPrimitive = CRYPTO_XVIX_XAIX_KMN_PRIPRIMITIVE(CRYPTO_KEYEXCHANGECALCPUBVAL, algoPtr->data->data[0U], algoPtr->data->data[1U]);
        }

        switch (primaryPrimitive)
        {

#if (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYEXCHANGE_X25519_NOTSET)
          case CRYPTO_XVIX_XAIX_KMN_PRIPRIMITIVE(CRYPTO_KEYEXCHANGECALCPUBVAL, CRYPTO_ALGOFAM_X25519, CRYPTO_ALGOMODE_NOT_SET):
          {
            retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( cryptoKeyId,
                                                                CRYPTO_XVIX_XAIX_KE_KMNCOMMON_WORKSPACE,
                                                               &wkspPtr,
                                                                FALSE,
                                                                CRYPTO_XVIX_XAIX_SID_EMPTY
                                                              );

            /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcPubVal/0014,1 */
            /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcPubVal/0015,1 */
            if (   (E_OK == retVal)
                && (408U <= wkspPtr->data->size)
               )
            {
              fromPrimitive = FALSE;
              /* Deviation TASKING-2 */
              CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_LOCK(retVal, wkspPtr, fromPrimitive);

              /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcPubVal/0016,1 */
              if (E_OK == retVal)
              {
                wkspDataLen = wkspPtr->data->size;

                /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcPubVal/0013,1 */
                result = Crypto_xVIx_xAIx_Int_KMn_KEYEXCHANGECALCPUBVAL_X25519_NOTSET_Process(0U, NULL_PTR, 0U, wkspPtr->data->data, wkspDataLen, cryptoKeyId, publicValuePtr, publicValueLengthPtr);

                CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE(wkspPtr);
              }
            }
          }
          break;
#endif /* #if (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYEXCHANGE_X25519_NOTSET) */

          default:
          {
            /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcPubVal/0100,1 */
          }
          break;
        }

        CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(algoPtr);
      }
    }
  }

#else /* #if (   FALSE... */
  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcPubVal/0001,1 */
  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(cryptoKeyId);
  TS_PARAM_UNUSED(publicValuePtr);
  TS_PARAM_UNUSED(publicValueLengthPtr);

#endif /* #if (   FALSE... */

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGECALCPUBVAL_EXIT(result, cryptoKeyId,publicValuePtr,publicValueLengthPtr);

  return result;
}

/* --- Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcSecret ------------------------------------------- */

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_Int_KMn_KeyExchangeCalcSecret/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcSecret
(
          uint32                                        cryptoKeyId,
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) partnerPublicValuePtr,
          uint32                                        partnerPublicValueLength
)
{

#if (   FALSE                                                                  \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYEXCHANGE_X25519_NOTSET) \
    )

          Std_ReturnType                                                          result             = E_NOT_OK;
          Std_ReturnType                                                          retVal             = E_NOT_OK;
          boolean                                                                 fromPrimitive      = FALSE;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) algoPtr            = NULL_PTR;
  P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) wkspPtr            = NULL_PTR;
          uint32                                                                  primaryPrimitive   = 0xFFFFFFFFU;
          uint32                                                                  wkspDataLen        = 0U;

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGECALCSECRET_ENTRY(cryptoKeyId,partnerPublicValuePtr,partnerPublicValueLength);

  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcSecret/0002,1 */
  if (CRYPTO_XVIX_XAIX_KEYSTATE_VALID == Crypto_xVIx_xAIx_Keys[cryptoKeyId].data->keyState)
  {
    retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( cryptoKeyId,
                                                        CRYPTO_KE_KEYEXCHANGE_ALGORITHM,
                                                       &algoPtr,
                                                        FALSE,
                                                        CRYPTO_XVIX_XAIX_SID_EMPTY
                                                      );

    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcSecret/0003,1,
                Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcSecret/0004,1
    */
    if (   (E_OK == retVal)
        && (   (2U == algoPtr->cnfg->description->maxSize)
            || (6U == algoPtr->cnfg->description->maxSize)
           )
       )
    {
      fromPrimitive = FALSE;
      /* Deviation TASKING-2 */
      CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(retVal, algoPtr, fromPrimitive);

      /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcSecret/0005,2 */
      if (E_OK == retVal)
      {
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcSecret/0006,1 */
        if (2U <= algoPtr->data->size)
        {
          primaryPrimitive = CRYPTO_XVIX_XAIX_KMN_PRIPRIMITIVE(CRYPTO_KEYEXCHANGECALCSECRET, algoPtr->data->data[0U], algoPtr->data->data[1U]);
        }

        switch (primaryPrimitive)
        {

#if (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYEXCHANGE_X25519_NOTSET)
          case CRYPTO_XVIX_XAIX_KMN_PRIPRIMITIVE(CRYPTO_KEYEXCHANGECALCSECRET, CRYPTO_ALGOFAM_X25519, CRYPTO_ALGOMODE_NOT_SET):
          {
            retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet( cryptoKeyId,
                                                                CRYPTO_XVIX_XAIX_KE_KMNCOMMON_WORKSPACE,
                                                               &wkspPtr,
                                                                FALSE,
                                                                CRYPTO_XVIX_XAIX_SID_EMPTY
                                                              );

            /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcSecret/0014,1 */
            /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcSecret/0015,1 */
            if (   (E_OK == retVal)
                && (408U <= wkspPtr->data->size)
               )
            {
              fromPrimitive = FALSE;
              /* Deviation TASKING-2 */
              CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_LOCK(retVal, wkspPtr, fromPrimitive);

              /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcSecret/0016,1 */
              if (E_OK == retVal)
              {
                wkspDataLen = wkspPtr->data->size;

                /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcSecret/0013,1 */
                result = Crypto_xVIx_xAIx_Int_KMn_KEYEXCHANGECALCSECRET_X25519_NOTSET_Process(0U, NULL_PTR, 0U, wkspPtr->data->data, wkspDataLen, cryptoKeyId, partnerPublicValuePtr, partnerPublicValueLength);

                CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE(wkspPtr);
              }
            }
          }
          break;
#endif /* #if (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYEXCHANGE_X25519_NOTSET) */

          default:
          {
            /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcSecret/0100,1 */
          }
          break;
        }

        CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(algoPtr);
      }
    }
  }

#else /* #if (   FALSE... */
  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcSecret/0001,1 */
  Std_ReturnType result = E_NOT_OK;

  TS_PARAM_UNUSED(cryptoKeyId);
  TS_PARAM_UNUSED(partnerPublicValuePtr);
  TS_PARAM_UNUSED(partnerPublicValueLength);

#endif /* #if (   FALSE... */

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGECALCSECRET_EXIT(result,cryptoKeyId,partnerPublicValuePtr,partnerPublicValueLength);

  return result;
}

/* --- Crypto_xVIx_xAIx_Int_KMn_CertificateParse ------------------------------------------------ */

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_Int_KMn_CertificateParse/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_CertificateParse
(
  uint32 cryptoKeyId
)
{
  /*
   * Certificate parsing and validation is not supported,
   * see deviation Crypto.Dev.Certificate
   */
  Std_ReturnType result = E_NOT_OK;

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_CERTIFICATEPARSE_ENTRY(cryptoKeyId);

  TS_PARAM_UNUSED(cryptoKeyId);

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_CERTIFICATEPARSE_EXIT(result, cryptoKeyId);

  return result;
}

/* --- Crypto_xVIx_xAIx_Int_KMn_CertificateVerify ----------------------------------------------- */

/* !LINKSTO Crypto.Dsn.Api/Interfaces/Crypto_Int_KMn_CertificateVerify/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_CertificateVerify
(
        uint32                                                cryptoKeyId,
        uint32                                                verifyCryptoKeyId,
  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) verifyPtr
)
{
  /*
   * Certificate parsing and validation is not supported,
   * see deviation Crypto.Dev.Certificate
   */
  /* !LINKSTO Crypto.Asr.SWS_Crypto_00177,1 */
  Std_ReturnType result = E_NOT_OK;

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_CERTIFICATEVERIFY_ENTRY(cryptoKeyId,verifyCryptoKeyId,verifyPtr);

  TS_PARAM_UNUSED(cryptoKeyId);
  TS_PARAM_UNUSED(verifyCryptoKeyId);
  TS_PARAM_UNUSED(verifyPtr);

  DBG_CRYPTO_XVIX_XAIX_INT_KMN_CERTIFICATEVERIFY_EXIT(result, cryptoKeyId,verifyCryptoKeyId,verifyPtr);

  return result;
}

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/* --- Crypto_xVIx_xAIx_Int_KMn_DriverObjectGetAndLock ------------------------------------------ */

/* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_DriverObjectGetAndLock/0001,1 */

#if (   (FALSE                                                                  ) \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG      ) \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET  ) \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519PH_NOTSET) \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYDERIVE_SINGLESTEPKDF_NOTSET) \
    )
static FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_DriverObjectGetAndLock
(
  P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) jobs,
        uint32                                                 jobsLength,
  P2VAR(uint32,         AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) objectId
)
{
          Std_ReturnType                                                            retVal = E_NOT_OK;
          uint32                                                                    i;
          uint32                                                                    j;
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitivePtr = NULL_PTR;

  /* Deviation TASKING-1 */
  for (i = 0U; i < CRYPTO_XVIX_XAIX_CDO_COUNT; i++)
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_DriverObjectGetAndLock/0002,1 */
    if (TRUE == Crypto_xVIx_xAIx_CDOs[i].cnfg->useForKMn)
    {
      for (j = 0U; j < jobsLength; j++)
      {
        retVal = Crypto_xVIx_xAIx_CheckJobService(i, &jobs[j]);
        if (E_OK == retVal)
        {
          retVal = Crypto_xVIx_xAIx_CheckJobPrimitive(i, &jobs[j], &primitivePtr);
        }
        if (E_OK != retVal)
        {
          /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_DriverObjectGetAndLock/0003,1 */
          break;
        }
      }
      if (E_OK == retVal)
      {
        /* lock CDO */
        if (CRYPTO_XVIX_XAIX_CDOSTATE_IDLE == Crypto_xVIx_xAIx_CDOs[i].data->state)
        {
          /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_DriverObjectGetAndLock/0005,1 */
          Crypto_xVIx_xAIx_CDOs[i].data->state            = CRYPTO_XVIX_XAIX_CDOSTATE_BUSY;

          /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_DriverObjectGetAndLock/0006,1 */
          Crypto_xVIx_xAIx_CDOs[i].data->jobCurrent       = &jobs[0U];

          /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_DriverObjectGetAndLock/0007,1 */
          /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Job/0001,1 */
          SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
          Crypto_xVIx_xAIx_CDOs[i].data->primitiveCurrent = primitivePtr;
          SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
        }
        else
        {
          retVal = CRYPTO_E_BUSY;
        }

        if (E_OK == retVal)
        {
          /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_DriverObjectGetAndLock/0008,1 */
          *objectId = i;
          break;
        }
      }
    }
  }
  return retVal;
}
#endif /* #if (   (FALSE) ... */

/* --- Crypto_xVIx_xAIx_Int_KMn_DriverObjectRelease --------------------------------------------- */

/* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_Int_KMn_DriverObjectRelease/0001,1 */

#if (   (FALSE                                                                  ) \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG      ) \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519_NOTSET  ) \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519PH_NOTSET) \
     || (STD_ON == CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYDERIVE_SINGLESTEPKDF_NOTSET) \
    )
static FUNC(void, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_DriverObjectRelease
(
  uint32 objectId
)
{
  Crypto_xVIx_xAIx_CDOs[objectId].data->state            = CRYPTO_XVIX_XAIX_CDOSTATE_IDLE;
  Crypto_xVIx_xAIx_CDOs[objectId].data->jobCurrent       = NULL_PTR;

  /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Job/0001,1 */
  SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
  Crypto_xVIx_xAIx_CDOs[objectId].data->primitiveCurrent = NULL_PTR;
  SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();
}
#endif /* #if (   (FALSE) ... */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

#endif /*#if (CRYPTO_XVIX_XAIX_KEYMNGMT_ENABLED == STD_ON) */

/*==================[end of file]=================================================================*/

