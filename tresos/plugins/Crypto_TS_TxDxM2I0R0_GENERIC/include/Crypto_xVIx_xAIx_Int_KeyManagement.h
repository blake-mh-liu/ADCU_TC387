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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KeyManagement.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_INT_KEYMANAGEMENT_H
#define CRYPTO_XVIX_XAIX_INT_KEYMANAGEMENT_H

/*==================[deviations]==================================================================*/

/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 20.7 (required)
 * Expressions resulting from the expansion of macro parameters shall be
 * enclosed in parentheses.
 *
 * Reason:
 * The AUTOSAR compiler abstraction requires these definitions in this way
 * and the arguments cannot be enclosed in parentheses due to C syntax.
 *
 */

/*==================[includes]====================================================================*/

#include <SchM_Crypto_xVIx_xAIx.h>       /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KeyManagement.h/0004,1 */

#include <Crypto_xVIx_xAIx_Int_Types.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KeyManagement.h/0005,1 */
#include <Crypto_xVIx_xAIx_Int_Cfg.h>    /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KeyManagement.h/0002,1 */
#include <Crypto_xVIx_xAIx_Cfg.h>        /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KeyManagement.h/0006,1 */

/* !LINKSTO Crypto.Asr.SWS_Crypto_00126,1 */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
#include <Det.h>                         /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KeyManagement.h/0003,1 */
#endif

/* !LINKSTO Crypto.Dsn.Gen/KMn_GenerationPhase/0001,2 */
#if (CRYPTO_XVIX_XAIX_KEYMNGMT_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

#if(defined CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_LOCK)
#error CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_LOCK is already defined
#endif
/** \brief This macro is used to lock a key element for writing. */
#define CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_LOCK(retVal, keyElementPtr, fromPrimitive)         \
do                                                                                            \
{                                                                                             \
  /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Key/0002,1 */               \
  SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();            \
  if ((FALSE == (keyElementPtr)->data->writeLock) && (0U == (keyElementPtr)->data->readLock)) \
  {                                                                                           \
    (keyElementPtr)->data->writeLock = TRUE;                                                  \
    (retVal)                         = E_OK;                                                  \
  }                                                                                           \
  else                                                                                        \
  {                                                                                           \
    if (TRUE == fromPrimitive)                                                                \
    {                                                                                         \
      (retVal) = CRYPTO_XVIX_XAIX_INTERNAL_E_KEY_NOT_AVAILABLE;                               \
    }                                                                                         \
    else                                                                                      \
    {                                                                                         \
      (retVal) = CRYPTO_E_KEY_NOT_AVAILABLE;                                                  \
    }                                                                                         \
  }                                                                                           \
  SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();             \
}                                                                                             \
while (0U)

#if(defined CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE)
#error CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE is already defined
#endif
/** \brief This macro is used to release a key element from writing. */
#define CRYPTO_XVIX_XAIX_KEY_ELEMENT_WRITE_RELEASE(keyElementPtr)                  \
do                                                                                 \
{                                                                                  \
  /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Key/0002,1 */    \
  SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT(); \
  (keyElementPtr)->data->writeLock = FALSE;                                        \
  SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();  \
}                                                                                  \
while (0U)

#if(defined CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK)
#error CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK is already defined
#endif
/** \brief This macro is used to lock a key element for reading. */
#define CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_LOCK(retVal, keyElementPtr, fromPrimitive) \
do                                                                                   \
{                                                                                    \
  /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Key/0001,1 */      \
  SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();   \
  if (FALSE == (keyElementPtr)->data->writeLock)                                     \
  {                                                                                  \
    (keyElementPtr)->data->readLock++;                                               \
    (retVal) = E_OK;                                                                 \
  }                                                                                  \
  else                                                                               \
  {                                                                                  \
    if (TRUE == fromPrimitive)                                                       \
    {                                                                                \
      (retVal) = CRYPTO_XVIX_XAIX_INTERNAL_E_KEY_NOT_AVAILABLE;                      \
    }                                                                                \
    else                                                                             \
    {                                                                                \
      (retVal) = CRYPTO_E_KEY_NOT_AVAILABLE;                                         \
    }                                                                                \
  }                                                                                  \
  SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();    \
}                                                                                    \
while (0U)

#if(defined CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE)
#error CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE is already defined
#endif
/** \brief This macro is used to release a key element from reading. */
#define CRYPTO_XVIX_XAIX_KEY_ELEMENT_READ_RELEASE(keyElementPtr)                   \
do                                                                                 \
{                                                                                  \
  /* !LINKSTO Crypto.Dsn.Api/SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA/Key/0001,1 */    \
  SchM_Enter_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT(); \
  if (0U < (keyElementPtr)->data->readLock)                                        \
  {                                                                                \
    (keyElementPtr)->data->readLock--;                                             \
  }                                                                                \
  SchM_Exit_Crypto_xVIx_xAIx_SCHM_CRYPTO_XVIX_XAIX_EXCLUSIVE_AREA_DRIVEROBJECT();  \
}                                                                                  \
while (0U)

#if(defined CRYPTO_XVIX_XAIX_KEY_ELEMENT_STORE)
#error CRYPTO_XVIX_XAIX_KEY_ELEMENT_STORE is already defined
#endif
/** \brief This macro is used to store a key element. */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_SETDATA == STD_ON)
#define CRYPTO_XVIX_XAIX_KEY_ELEMENT_STORE(targetKeyId, targetKeyElemId, targetPtr, sourcePtr, sourceSize, retVal) \
do                                                                                                                 \
{                                                                                                                  \
  TS_MemCpy(                                                                                                       \
             targetPtr->data->data,                                                                                \
             sourcePtr,                                                                                            \
             sourceSize                                                                                            \
           );                                                                                                      \
  /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementCopy/0008,1 */                                            \
  if (TRUE == targetPtr->cnfg->description->persistent)                                                            \
  {                                                                                                                \
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementCopy/0009,1 */                                          \
    retVal = Crypto_xVIx_xAIx_KeyElement_SetData                                                                   \
    (                                                                                                              \
      targetKeyId,                                                                                                 \
      targetKeyElemId,                                                                                             \
      targetPtr->data->data,                                                                                       \
      sourceSize                                                                                                   \
    );                                                                                                             \
  }                                                                                                                \
}                                                                                                                  \
while (0U)
#else /* CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_SETDATA == STD_ON */
#define CRYPTO_XVIX_XAIX_KEY_ELEMENT_STORE(targetKeyId, targetKeyElemId, targetPtr, sourcePtr, sourceSize, retVal) \
do                                                                                                         \
{                                                                                                          \
  TS_MemCpy(                                                                                               \
             targetPtr->data->data,                                                                        \
             sourcePtr,                                                                                    \
             sourceSize                                                                                    \
           );                                                                                              \
}                                                                                                          \
while (0U)
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_SETDATA == STD_ON) */

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  Get a pointer to a key element's data.
 **
 ** This functions searches for a key element and returns a pointer to its data and corresponding
 ** length.
 **
 ** \param[in]     cryptoKeyId      The id of the key
 ** \param[in]     keyElementId     The id of the key element  Holds the pointer of the buffer for the returned key element
 ** \param[inout]  keyElementPtr    Pointer of the buffer for the returned key element
 ** \param[in]     calledFromExt    Indicated whether this function is called in the context of a public AUTOSAR API or not
 ** \param[in]     callerSID        The SID of the calling function, this is only relevant if 'calledFromExt' is TRUE
 **
 ** \returns  Result of the request.
 **
 ** \retval  E_OK      Request successful.
 ** \retval  E_NOT_OK  Request failed.
 **
 ** \Reentrancy {Nonreentrant}
 ** \Synchronicity {Synchronous/Asynchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeyElementPtrGet
(
        uint32                                                                                                                  cryptoKeyId,
        uint32                                                                                                                  keyElementId,
        /* Deviation MISRAC2012-1 */
  P2VAR(P2CONST(Crypto_xVIx_xAIx_KeyElementType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA), AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyElementPtr,
        boolean                                                                                                                 calledFromExt,
        uint8                                                                                                                   callerSID
);

/** \brief  Set a key element
 **
 ** This function attempts to set the requested key element within the crypto engine
 **
 ** \param[in]  cryptoKeyId   Identifier of the crypto key whose key element shall be set
 ** \param[in]  keyElementId  Identifier of the key element that shall be set
 ** \param[in]  keyPtr        Pointer to the key data that shall be set as the key element
 ** \param[in]  keyLength     Length of the key element in bytes
 **
 ** \returns  Result of the request.
 **
 ** \retval  E_OK                        Request successful.
 ** \retval  E_NOT_OK                    Request failed.
 ** \retval  CRYPTO_E_KEY_SIZE_MISMATCH  Key element size is not compatible.
 ** \retval  CRYPTO_E_KEY_WRITE_FAIL     Write access was denied.
 ** \retval  CRYPTO_E_KEY_NOT_AVAILABLE  The requested key is not available.
 **
 ** \Reentrancy {Nonreentrant}
 ** \Synchronicity {Synchronous/Asynchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeyElementSet
(
          uint32                              cryptoKeyId,
          uint32                              keyElementId,
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyPtr,
          uint32                              keyLength
);

/** \brief  Set a key to valid
 **
 ** This function sets a key to the state valid.
 **
 ** \param[in]  cryptoKeyId  Identifier of the crypto key whose key element shall be set to valid.
 **
 ** \returns  Result of the request.
 **
 ** \retval  E_OK      Request successful.
 ** \retval  E_NOT_OK  Request failed.
 **
 ** \Reentrancy {Nonreentrant}
 ** \Synchronicity {Synchronous/Asynchronous}
 **/
#if (   (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) \
     || (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_EB ) \
    )
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeyValidSet
#else /* #if (   (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) ... */
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeySetValid
#endif /* #if (   (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) ... */
(
  uint32 cryptoKeyId
);

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KEYSETINVALID == STD_ON)
/** \brief  Set a key to invalid
 **
 ** This function sets a key to the state invalid.
 **
 ** \param[in]  cryptoKeyId  Identifier of the crypto key whose key element shall be set to invalid.
 **
 ** \returns  Result of the request.
 **
 ** \retval  E_OK      Request successful.
 ** \retval  E_NOT_OK  Request failed.
 **
 ** \Reentrancy {Nonreentrant}
 ** \Synchronicity {Synchronous/Asynchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeySetInvalid
(
  uint32 cryptoKeyId
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KEYSETINVALID == STD_ON) */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KEYGETSTATUS == STD_ON)
/** \brief  Returns the key state of the key identified by cryptoKeyId.
 **
 ** This function copies the state of the requested key element to the provided buffer
 **
 ** \param[in]      cryptoKeyId      Holds the identifier of the key for which the key state shall
 **                                  be returned.
 ** \param[in,out]  keyStatusPtr     Contains the pointer to the data where the status of the key
 **                                  shall be stored.
 **
 ** \returns  Result of the request.
 **
 ** \retval  E_OK                        Request successful
 ** \retval  E_NOT_OK                    Request failed
 **
 ** \Reentrancy {Nonreentrant}
 ** \Synchronicity {Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeyGetStatus
(
        uint32                                                       cryptoKeyId,
  P2VAR(Crypto_KeyStatusType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyStatusPtr
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KEYGETSTATUS == STD_ON) */

/** \brief  Retrieve the value of a key element
 **
 ** This function copies the requested key element to the provided buffer
 **
 ** \param[in]      cryptoKeyId      Identifier of the crypto key whose element shall be retrieved.
 ** \param[in]      keyElementId     Identifier of the key element that shall be retrieved.
 ** \param[out]     resultPtr        Pointer to the memory location where the key element data
 **                                  shall be stored.
 ** \param[in,out]  resultLengthPtr  Pointer to the location where the length
 **                                  information is stored. Shall contain the
 **                                  amount of bytes that shall be read.
 **                                  After finishing the request, it contains the
 **                                  amount of bytes that has been stored in the result.
 **
 ** \returns  Result of the request.
 **
 ** \retval  E_OK                        Request successful
 ** \retval  E_NOT_OK                    Request failed
 ** \retval  CRYPTO_E_KEY_READ_FAIL      Read access was denied
 ** \retval  CRYPTO_E_KEY_NOT_AVAILABLE  The requested key is not available
 ** \retval  CRYPTO_E_SMALL_BUFFER       The provided buffer is too small to store the result
 **
 ** \Reentrancy {Nonreentrant}
 ** \Synchronicity {Synchronous/Asynchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeyElementGet
(
        uint32                               cryptoKeyId,
        uint32                               keyElementId,
  P2VAR(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) resultPtr,
  P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) resultLengthPtr
);

/** \brief  Copy a key element
 **
 ** This function copies the requested key element to the destination key element
 **
 ** \param[in]  cryptoKeyId         Identifier of the key whose element shall be copied
 ** \param[in]  keyElementId        Identifier of the key element that shall be copied
 ** \param[in]  targetCryptoKeyId   Identifier of the destination key
 ** \param[in]  targetKeyElementId  Identifier of the destination key element
 **
 ** \returns Result of the request.
 **
 ** \retval  E_OK                        Request successful
 ** \retval  E_NOT_OK                    Request failed
 ** \retval  CRYPTO_E_KEY_READ_FAIL      Read access was denied
 ** \retval  CRYPTO_E_KEY_WRITE_FAIL     Write access was denied
 ** \retval  CRYPTO_E_KEY_NOT_AVAILABLE  The requested key is not available
 ** \retval  CRYPTO_E_KEY_SIZE_MISMATCH  Key element sizes are not compatible
 **
 ** \Reentrancy {Nonreentrant}
 ** \Synchronicity {Synchronous/Asynchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeyElementCopy
(
  uint32 cryptoKeyId,
  uint32 keyElementId,
  uint32 targetCryptoKeyId,
  uint32 targetKeyElementId
);

/** \brief  Copy all key elements of a key
 **
 ** This function copies the key elements of the requested key to the destination key
 **
 ** \param[in]  cryptoKeyId        Identifier of the key whose elements shall be copied.
 ** \param[in]  targetCryptoKeyId  Identifier of the destination key
 **
 ** \returns  Result of the request.
 **
 ** \retval  E_OK                        Request successful
 ** \retval  E_NOT_OK                    Request failed
 ** \retval  CRYPTO_E_KEY_READ_FAIL      Read access was denied
 ** \retval  CRYPTO_E_KEY_WRITE_FAIL     Write access was denied
 ** \retval  CRYPTO_E_KEY_NOT_AVAILABLE  The requested key is not available
 ** \retval  CRYPTO_E_KEY_SIZE_MISMATCH  Key element sizes are not compatible
 **
 ** \Reentrancy {Nonreentrant}
 ** \Synchronicity {Synchronous/Asynchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeyCopy
(
  uint32 cryptoKeyId,
  uint32 targetCryptoKeyId
);

/** \brief  Get the Ids of the key elements available within the requested key
 **
 ** This function copies the Ids of the  key elements available within the requested key
 ** to the provided buffer.
 **
 ** \param[in]      cryptoKeyId             Identifier of the crypto key whose key element ids shall be
 **                                         retrieved
 ** \param[out]     keyElementIdsPtr        Memory location, where the key element ids shall be stored
 ** \param[in,out]  keyElementIdsLengthPtr  Memory location, where the number of key elements shall be
 **                                         stored. On calling this function it shall contain the
 **                                         number of element Ids that can be stored within the
 **                                         provided buffer.
 **
 ** \returns  Result of the request.
 **
 ** \retval  E_OK                   Request successful
 ** \retval  E_NOT_OK               Request failed
 ** \retval  CRYPTO_E_SMALL_BUFFER  The provided buffer is too small to store the result
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeyElementIdsGet
(
        uint32                               cryptoKeyId,
  P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyElementIdsPtr,
  P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyElementIdsLengthPtr
);

/** \brief  Generate internal seed state for requested key
 **
 ** This function generates a random seed by using the provided entropy
 **
 ** \param[in]  cryptoKeyId    Identifier of the crypto key for which a seed shall be generated.
 ** \param[in]  entropyPtr     Pointer to the memory location which contains the entropy data.
 ** \param[in]  entropyLength  Length of the entropy in bytes
 **
 ** \returns  Result of the request
 **
 ** \retval  E_OK      Request successful
 ** \retval  E_NOT_OK  Request failed
 **
 ** \Reentrancy {Nonreentrant}
 ** \Synchronicity {Synchronous/Asynchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_RandomSeed
(
          uint32                              cryptoKeyId,
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) entropyPtr,
          uint32                              entropyLength
);

/** \brief  Generate a new key
 **
 ** This function generates new key material for the referenced key
 **
 ** \param[in]  cryptoKeyId  Identifier of the crypto key for which key material
 **                          shall be generated.
 **
 ** \returns  Result of the request
 **
 ** \retval  E_OK      Request successful
 ** \retval  E_NOT_OK  Request failed
 **
 ** \Reentrancy {Nonreentrant}
 ** \Synchronicity {Synchronous/Asynchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeyGenerate
(
  uint32 cryptoKeyId
);

/** \brief  Derive a key from another key
 **
 ** This function generates new key material for the referenced key by deriving it
 ** from the key material of the referenced source key
 **
 ** \param[in]  cryptoKeyId        Identifier of the crypto key that shall
 **                                be used for derivation.
 ** \param[in]  targetCryptoKeyId  Identifier of the crypto key where the
 **                                derived key shall be stored.
 **
 ** \returns  Result of the request
 **
 ** \retval E_OK      Request successful
 ** \retval E_NOT_OK  Request failed
 **
 ** \Reentrancy {Nonreentrant}
 ** \Synchronicity {Synchronous/Asynchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeyDerive
(
  uint32 cryptoKeyId,
  uint32 targetCryptoKeyId
);

/** \brief  Calculate the public value for the key exchange
 **
 ** This function calculates the public value for the key exchange and stores the calculated
 ** value within the result buffer
 **
 ** \param[in]      cryptoKeyId           Identifier of the crypto key that shall be used for
 **                                       the key exchange.
 ** \param[out]     publicValuePtr        Pointer to the memory location where the public value
 **                                       shall be stored.
 ** \param[in,out]  publicValueLengthPtr  Pointer to the memory location where the length
 **                                       information shall be stored.
 **                                       On calling this function, this location
 **                                       shall contain the size of the provided buffer.
 **
 ** \returns  Result of the request
 **
 ** \retval  E_OK                   Request successful
 ** \retval  E_NOT_OK               Request failed
 ** \retval  CRYPTO_E_SMALL_BUFFER  The provided buffer is too small to store the result
 **
 ** \Reentrancy {Nonreentrant}
 ** \Synchronicity {Synchronous/Asynchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcPubVal
(
        uint32                               cryptoKeyId,
  P2VAR(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) publicValuePtr,
  P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) publicValueLengthPtr
);

/** \brief  Calculate the shared secret for the key exchange
 **
 ** This function calculates the shared secret for the key exchange using the partners
 ** public value. The result is stored in a key element within the referenced key.
 **
 ** \param[in]   cryptoKeyId               Identifier of the crypto key that shall
 **                                        be used for the key exchange.
 ** \param[out]  partnerPublicValuePtr     Pointer to the memory where the public
 **                                        value of the partner is located.
 ** \param[in]   partnerPublicValueLength  Length of the partner's public value in bytes.
 **
 ** \returns  Result of the request
 **
 ** \retval E_OK      Request successful
 ** \retval E_NOT_OK  Request failed
 **
 ** \Reentrancy {Nonreentrant}
 ** \Synchronicity {Synchronous/Asynchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcSecret
(
          uint32                              cryptoKeyId,
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) partnerPublicValuePtr,
          uint32                              partnerPublicValueLength
);

/** \brief  Parse a certificate
 **
 ** This function parses the certificate data stored in the key element
 ** CRYPTO_KE_CERT_DATA and fills the key elements CRYPTO_KE_CERT_SIGNEDDATA,
 ** CRYPTO_KE_CERT_PARSEDPUBLICKEY and CRYPTO_KE_CERT_SIGNATURE
 **
 ** \param[in]  cryptoKeyId  Identifier of the key that contains the certificate
 **
 ** \returns  Result of the request
 **
 ** \retval  E_OK      Request successful
 ** \retval  E_NOT_OK  Request failed
 **
 ** \Reentrancy {Nonreentrant}
 ** \Synchronicity {Synchronous/Asynchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_CertificateParse
(
  uint32 cryptoKeyId
);

/** \brief  Verify a certificate
 **
 ** This function verifies the certificate stored in the key verifyCryptoKeyId with
 ** the certificate stored in the key referenced by cryptoKeyId
 **
 ** \param[in]   cryptoKeyId        Identifier of the key that shall be
 **                                 used for verification.
 ** \param[in]   verifyCryptoKeyId  Identifier of the key that contains
 **                                 the certificate.
 ** \param[out]  verifyPtr          Pointer to the memory location where
 **                                 the result of the verification shall be stored.
 **
 ** \returns  Result of the request
 **
 ** \retval  E_OK      Request successful
 ** \retval  E_NOT_OK  Request failed
 **
 ** \Reentrancy {Nonreentrant}
 ** \Synchronicity {Synchronous/Asynchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_CertificateVerify
(
        uint32                                                cryptoKeyId,
        uint32                                                verifyCryptoKeyId,
  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) verifyPtr
);

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*================================================================================================*/

#endif /*#if (CRYPTO_XVIX_XAIX_KEYMNGMT_ENABLED == STD_ON) */

#endif /* #ifndef CRYPTO_XVIX_XAIX_INT_KEYMANAGEMENT_H */

/*==================[end of file]=================================================================*/

