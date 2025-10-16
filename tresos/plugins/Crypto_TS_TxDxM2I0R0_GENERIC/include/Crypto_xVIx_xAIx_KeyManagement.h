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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_KeyManagement.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_KEYMANAGEMENT_H
#define CRYPTO_XVIX_XAIX_KEYMANAGEMENT_H

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

#include <Csm_Types.h>                             /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_KeyManagement.h/0002,1 */

#include <Crypto_xVIx_xAIx_KeyManagement_Types.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_KeyManagement.h/0003,1 */
#include <Crypto_xVIx_xAIx_Cfg.h>                  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_KeyManagement.h/0004,1 */

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

/* !LINKSTO Crypto.Dsn.Gen/KMn_GenerationPhase/0001,2 */
/* !LINKSTO Crypto.Dsn.Gen/KMn_GenerationPhase/0002,2 */
#if (CRYPTO_XVIX_XAIX_KEYMNGMT_ENABLED == STD_ON)

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  Set a key element
 **
 ** This function checks the provided parameters and forwards the key setting request
 ** to the process layer
 **
 ** \param[in]  cryptoKeyId   Identifier of the crypto key whose key element shall be set
 ** \param[in]  keyElementId  Identifier of the key element that shall be set
 ** \param[in]  keyPtr        Pointer to the key data that shall be set as the key element
 ** \param[in]  keyLength     Length of the key element in bytes
 **
 ** \returns  Result of the key setting operation
 **
 ** \retval  E_OK                        Request successful
 ** \retval  E_NOT_OK                    Request failed
 ** \retval  CRYPTO_E_KEY_WRITE_FAIL     Write access was denied
 ** \retval  CRYPTO_E_KEY_NOT_AVAILABLE  The requested key is not available
 ** \retval  CRYPTO_E_KEY_SIZE_MISMATCH  Provided data size does not match key element size
 **
 ** \Reentrancy{Non Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeyElementSet
(
  uint32                                      cryptoKeyId,
  uint32                                      keyElementId,
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyPtr,
  uint32                                      keyLength
);

/** \brief  Set a key to valid
 **
 ** This function checks the provided parameters and forwards the request to the
 ** process layer.
 **
 ** ATTENTION: This API is only available if the configuration parameter "CryptoEbAutosarApiVersion"
 **            is set to CRYPTO_API_VERSION_430 or CRYPTO_API_VERSION_EB.
 **            See AUTOSAR Specification of Crypto Driver, v4.3.1, requirement SWS_Crypto_91005.
 **
 ** \param[in]  cryptoKeyId  Identifier of the crypto key that shall be set to valid
 **
 ** \returns  Result of the request
 **
 ** \retval  E_OK      Request successful
 ** \retval  E_NOT_OK  Request failed
 **
 ** \Reentrancy{Non Reentrant}
 ** \Synchronicity{Synchronous}
 **/
#if (   (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) \
     || (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_EB ) \
    )
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeyValidSet
(
  uint32 cryptoKeyId
);
#endif /* #if (   (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) ... */

/** \brief  Set a key to valid
 **
 ** This function checks the provided parameters and forwards the request to the
 ** process layer.
 **
 ** ATTENTION: This API is only available if the configuration parameter 'CryptoEbAutosarApiVersion'
 **            is set to CRYPTO_API_VERSION_431 or CRYPTO_API_VERSION_R2111.
 **            See AUTOSAR Specification of Crypto Driver, v4.3.1, or R2111 requirement SWS_Crypto_91014.
 **
 ** \param[in]  cryptoKeyId  Identifier of the crypto key that shall be set to valid
 **
 ** \returns  Result of the request
 **
 ** \retval  E_OK      Request successful
 ** \retval  E_NOT_OK  Request failed
 **
 ** \Reentrancy{Non Reentrant}
 ** \Synchronicity{Synchronous}
 **/
 #if (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_431)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeySetValid
(
  uint32 cryptoKeyId
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_431) */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KEYSETINVALID == STD_ON)
/** \brief  Set a key to invalid
 **
 ** This function checks the provided parameters and forwards the request to the
 ** process layer.
 **
 ** \param[in]  cryptoKeyId  Identifier of the crypto key that shall be set to invalid
 **
 ** \returns  Result of the request
 **
 ** \retval  E_OK      Request successful
 ** \retval  E_NOT_OK  Request failed
 **
 ** \Reentrancy{Non Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeySetInvalid
(
  uint32 cryptoKeyId
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KEYSETINVALID == STD_ON) */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KEYGETSTATUS == STD_ON)
/** \brief  Retrieve the status of a key.
 **
 ** This function returns the key state of the key identified by cryptoKeyId.
 **
 ** \param[in]   cryptoKeyId   Identifier of the crypto key whose element shall be retrieved.
 ** \param[out]  keyStatusPtr  Pointer to the location where the status of the key shall be stored.
 **
 ** \returns  Result of the request
 **
 ** \retval  E_OK                        Request successful
 ** \retval  E_NOT_OK                    Request failed
 **
 ** \Reentrancy{Non Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeyGetStatus
(
        uint32                                                       cryptoKeyId,
  P2VAR(Crypto_KeyStatusType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyStatusPtr
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KEYGETSTATUS == STD_ON) */

/** \brief  Retrieve the value of a key element
 **
 ** This function checks the provided parameters and forwards the request to the
 ** process layer
 **
 ** \param[in]      cryptoKeyId      Identifier of the crypto key whose element shall be retrieved.
 ** \param[in]      keyElementId     Identifier of the key element that shall be retrieved.
 ** \param[out]     resultPtr        Pointer to the memory location where the key element data
 **                                  shall be stored.
 ** \param[in,out]  resultLengthPtr  Pointer to the location where the length information is stored.
 **                                  Shall contain the amount of bytes that shall be read. After
 **                                  finishing the request, it contains the amount of bytes that has
 **                                  been stored in the result.
 **
 ** \returns  Result of the request
 **
 ** \retval  E_OK                        Request successful
 ** \retval  E_NOT_OK                    Request failed
 ** \retval  CRYPTO_E_KEY_READ_FAIL      Read access was denied
 ** \retval  CRYPTO_E_KEY_NOT_AVAILABLE  The requested key is not available
 ** \retval  CRYPTO_E_SMALL_BUFFER       The provided buffer is too small to store the result
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeyElementGet
(
  uint32                                     cryptoKeyId,
  uint32                                     keyElementId,
  P2VAR(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) resultPtr,
  P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) resultLengthPtr
);

/** \brief  Copy a key element
 **
 ** This function checks the provided parameters and forwards the request to the
 ** process layer
 **
 ** \param[in]  cryptoKeyId         Identifier of the key whose element shall be copied
 ** \param[in]  keyElementId        Identifier of the key element that shall be copied
 ** \param[in]  targetCryptoKeyId   Identifier of the destination key
 ** \param[in]  targetKeyElementId  Identifier of the destination key element
 **
 ** \returns  Result of the request
 **
 ** \retval  E_OK                        Request successful
 ** \retval  E_NOT_OK                    Request failed
 ** \retval  CRYPTO_E_KEY_READ_FAIL      Read access was denied
 ** \retval  CRYPTO_E_KEY_WRITE_FAIL     Write access was denied
 ** \retval  CRYPTO_E_KEY_NOT_AVAILABLE  The requested key is not available
 ** \retval  CRYPTO_E_KEY_SIZE_MISMATCH  Key element sizes are not compatible
 **
 ** \Reentrancy{Reentrant but not for the same cryptoKeyId}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeyElementCopy
(
  uint32 cryptoKeyId,
  uint32 keyElementId,
  uint32 targetCryptoKeyId,
  uint32 targetKeyElementId
);

/** \brief  Copy all key elements of a key
 **
 ** This function checks the provided parameters and forwards the request to the
 ** process layer
 **
 ** \param[in]  cryptoKeyId        Identifier of the key whose elements shall be copied
 ** \param[in]  targetCryptoKeyId  Identifier of the destination key
 *
 ** \returns  Result of the request
 **
 ** \retval  E_OK                        Request successful
 ** \retval  E_NOT_OK                    Request failed
 ** \retval  CRYPTO_E_KEY_READ_FAIL      Read access was denied
 ** \retval  CRYPTO_E_KEY_WRITE_FAIL     Write access was denied
 ** \retval  CRYPTO_E_KEY_NOT_AVAILABLE  The requested key is not available
 ** \retval  CRYPTO_E_KEY_SIZE_MISMATCH  Key element sizes are not compatible
 **
 ** \Reentrancy{Reentrant but not for the same cryptoKeyId}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeyCopy
(
  uint32 cryptoKeyId,
  uint32 targetCryptoKeyId
);

/** \brief  Get the Ids of the key elements available within the requested key
 **
 ** This function checks the provided parameters and forwards the request to the
 ** process layer
 **
 ** \param[in]      cryptoKeyId             Identifier of the crypto key whose key element ids shall be
 **                                         retrieved
 ** \param[out]     keyElementIdsPtr        Memory location, where the key element ids shall be stored
 ** \param[in,out]  keyElementIdsLengthPtr  Memory location, where the number of key elements shall be
 **                                         stored. On calling this function it shall contain the
 **                                         number of element Ids that can be stored within the
 **                                         provided buffer.
 **
 ** \returns  Result of the request
 **
 ** \retval  E_OK                   Request successful
 ** \retval  E_NOT_OK               Request failed
 ** \retval  CRYPTO_E_SMALL_BUFFER  The provided buffer is too small to store the result
 **
 ** \Reentrancy{Reentrant but not for the same cryptoKeyId}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeyElementIdsGet
(
  uint32                                     cryptoKeyId,
  P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyElementIdsPtr,
  P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyElementIdsLengthPtr
);

/** \brief  Generate internal seed state for requested key
 **
 ** This function checks the provided parameters and forwards the request to the
 ** process layer
 **
 ** \param[in]  cryptoKeyId    Identifier of the crypto key for which a seed shall be
 **                            generated
 ** \param[in]  seedPtr        Pointer to the memory location which contains the entropy
 **                            data
 ** \param[in]  seedLength     Length of the entropy in bytes
 **
 ** \returns  Result of the request
 **
 ** \retval  E_OK      Request successful
 ** \retval  E_NOT_OK  Request failed
 **
 ** \Reentrancy{Reentrant but not for the same cryptoKeyId}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_RandomSeed
(
  uint32                                      cryptoKeyId,
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) seedPtr,
  uint32                                      seedLength
);

/** \brief  Generate a new key
 **
 ** This function checks the provided parameters and forwards the request to the
 ** process layer
 **
 ** \param[in]  cryptoKeyId  Identifier of the crypto key for which key material shall
 **                          be generated
 **
 ** \returns  Result of the request
 **
 ** \retval  E_OK      Request successful
 ** \retval  E_NOT_OK  Request failed
 **
 ** \Reentrancy{Reentrant but not for the same cryptoKeyId}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeyGenerate
(
  uint32 cryptoKeyId
);

/** \brief  Derive a key from another key
 **
 ** This function checks the provided parameters and forwards the request to the
 ** process layer
 **
 ** \param[in]  cryptoKeyId        Identifier of the crypto key that shall be used for
 **                                derivation
 ** \param[in]  targetCryptoKeyId  Identifier of the crypto key where the derived key shall be
 **                                stored
 **
 ** \returns  Result of the request
 **
 ** \retval  E_OK      Request successful
 ** \retval  E_NOT_OK  Request failed
 **
 ** \Reentrancy{Reentrant but not for the same cryptoKeyId}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeyDerive
(
  uint32 cryptoKeyId,
  uint32 targetCryptoKeyId
);

/** \brief  Calculate the public value for the key exchange
 **
 ** This function checks the provided parameters and forwards the request to the
 ** process layer
 **
 ** \param[in]      cryptoKeyId           Identifier of the crypto key that shall be used for the
 **                                       key exchange
 ** \param[out]     publicValuePtr        Pointer to the memory location where the public value
 **                                       shall be stored
 ** \param[in,out]  publicValueLengthPtr  Pointer to the memory location where the length
 **                                       information shall be
 **                                       stored. On calling this function, this location shall
 **                                       contain the size of the provided buffer.
 **
 ** \returns  Result of the request
 **
 ** \retval  E_OK                   Request successful
 ** \retval  E_NOT_OK               Request failed
 ** \retval  CRYPTO_E_SMALL_BUFFER  The provided buffer is too small to store the result
 **
 ** \Reentrancy{Reentrant but not for the same cryptoKeyId}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeyExchangeCalcPubVal
(
  uint32                                     cryptoKeyId,
  P2VAR(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) publicValuePtr,
  P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) publicValueLengthPtr
);

/** \brief  Calculate the shared secret for the key exchange
 **
 ** This function checks the provided parameters and forwards the request to the
 ** process layer
 **
 ** \param[in]   cryptoKeyId               Identifier of the crypto key that shall be used for the
 **                                        key exchange
 ** \param[out]  partnerPublicValuePtr     Pointer to the memory where the public value of the
 **                                        partner is located
 ** \param[in]   partnerPublicValueLength  Length of the partner's public value in bytes
 **
 ** \returns  Result of the request
 **
 ** \retval  E_OK                   Request successful
 ** \retval  E_NOT_OK               Request failed
 ** \retval  CRYPTO_E_SMALL_BUFFER  The provided buffer is too small to store the result
 **
 ** \Reentrancy{Reentrant but not for the same cryptoKeyId}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeyExchangeCalcSecret
(
  uint32                                      cryptoKeyId,
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) partnerPublicValuePtr,
  uint32                                      partnerPublicValueLength
);

/** \brief  Parse a certificate
 **
 ** This function checks the provided parameters and forwards the request to the
 ** process layer
 **
 ** \param[in]  cryptoKeyId  Identifier of the key that contains the certificate
 **
 ** \returns  Result of the request
 **
 ** \retval  E_OK      Request successful
 ** \retval  E_NOT_OK  Request failed
 **
 ** \Reentrancy{Reentrant but not for the same cryptoKeyId}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CertificateParse
(
  uint32 cryptoKeyId
);

/** \brief  Verify a certificate
 **
 ** This function checks the provided parameters and forwards the request to the
 ** process layer
 **
 ** \param[in]   cryptoKeyId        Identifier of the key that shall be used for verification
 ** \param[in]   verifyCryptoKeyId  Identifier of the key that contains the certificate
 ** \param[out]  verifyPtr          Pointer to the memory location where the result of the
 **                                 verification shall be stored
 **
 ** \returns  Result of the request
 **
 ** \retval  E_OK      Request successful
 ** \retval  E_NOT_OK  Request failed
 **
 ** \Reentrancy{Reentrant but not for the same cryptoKeyId}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CertificateVerify
(
  uint32                                                      cryptoKeyId,
  uint32                                                      verifyCryptoKeyId,
  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) verifyPtr
);

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

#endif /*#if (CRYPTO_XVIX_XAIX_KEYMNGMT_ENABLED == STD_ON) */

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_KEYMANAGEMENT_H */

/*==================[end of file]=================================================================*/

