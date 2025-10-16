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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_H
#define CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_H

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Cfg.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15.h/0002,1 */
#include <Crypto_xVIx_xAIx_Int_Lib_LN.h>

#if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA1_NOTSET  )
#if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA1_NOTSET == STD_ON)
#include <Crypto_xVIx_xAIx_Int_CPr_HASH_SHA1_NOTSET.h>
#endif /* #if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA1_NOTSET  )*/
#endif /* #if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA1_NOTSET == STD_ON) */

#if    (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2224_NOTSET  )
#if    (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2224_NOTSET == STD_ON)
#include <Crypto_xVIx_xAIx_Int_CPr_HASH_SHA2224_NOTSET.h>
#endif /* #if    (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2224_NOTSET  ) */
#endif /* #if    (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2224_NOTSET == STD_ON) */

#if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2256_NOTSET  )
#if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2256_NOTSET == STD_ON)
#include <Crypto_xVIx_xAIx_Int_CPr_HASH_SHA2256_NOTSET.h>
#endif /* #if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2256_NOTSET  ) */
#endif /* #if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2256_NOTSET == STD_ON) */

#if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2384_NOTSET  )
#if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2384_NOTSET == STD_ON)
#include <Crypto_xVIx_xAIx_Int_CPr_HASH_SHA2384_NOTSET.h>
#endif /* #if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2384_NOTSET  ) */
#endif /* #if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2384_NOTSET == STD_ON) */

#if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2512_NOTSET  )
#if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2512_NOTSET == STD_ON)
#include <Crypto_xVIx_xAIx_Int_CPr_HASH_SHA2512_NOTSET.h>
#endif /* #if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2512_NOTSET  ) */
#endif /* #if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA2512_NOTSET == STD_ON) */

#if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3224_NOTSET  )
#if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3224_NOTSET == STD_ON)
#include <Crypto_xVIx_xAIx_Int_CPr_HASH_SHA3224_NOTSET.h>
#endif /* #if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3224_NOTSET  ) */
#endif /* #if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3224_NOTSET == STD_ON) */

#if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3256_NOTSET  )
#if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3256_NOTSET == STD_ON)
#include <Crypto_xVIx_xAIx_Int_CPr_HASH_SHA3256_NOTSET.h>
#endif /* #if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3256_NOTSET  ) */
#endif /* #if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3256_NOTSET == STD_ON) */

#if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3384_NOTSET  )
#if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3384_NOTSET == STD_ON)
#include <Crypto_xVIx_xAIx_Int_CPr_HASH_SHA3384_NOTSET.h>
#endif /* #if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3384_NOTSET  ) */
#endif /* #if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3384_NOTSET == STD_ON) */

#if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3512_NOTSET  )
#if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3512_NOTSET == STD_ON)
#include <Crypto_xVIx_xAIx_Int_CPr_HASH_SHA3512_NOTSET.h>
#endif /* #if (defined CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3512_NOTSET  ) */
#endif /* #if (CRYPTO_XVIX_XAIX_INC_ENABLED_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASH_SHA3512_NOTSET == STD_ON) */

/*==================[macros]======================================================================*/

#if (defined CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_DER_HEADER_MAX_LEN)
#error CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_DER_HEADER_MAX_LEN already defined
#endif
/** \brief The maximal possible length of a DER header as returned by
 **        Crypto_xVIx_xAIx_CommonDerHeaderSequence() or Crypto_xVIx_xAIx_CommonDerHeaderOctetString().
 **/
#define CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_DER_HEADER_MAX_LEN 6U

#if (defined CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_EM_STATIC_FIELDS_LEN)
#error CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_EM_STATIC_FIELDS_LEN is already defined
#endif
/** \brief The length of the static EM fields, as described in Chapter 9.2 of the standard
 **        PKCS #1 v2.2: RSA Cryptography Standard
 **/
#define CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_EM_STATIC_FIELDS_LEN 11U

/*--SHA1------------------------------------------------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/GENERAL/0003,1 */
#if (defined CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA1_ID)
#error CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA1_ID is already defined
#endif
/** \brief  The X.509 algorithm identifier of the SHA1 hash algorithm. Trailing zeros are added to
            match the size of the Crypto_xVIx_xAIx_AlgorithmId. The required size is 11 only. */
#define CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA1_ID                       \
{                                                         \
  0x30, 0x09, 0x06, 0x05, 0x2b, 0x0e, 0x03, 0x02,         \
  0x1a, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00                \
}

#if (defined CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA1_ID_LENGTH)
#error CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA1_ID_LENGTH is already defined
#endif
/** \brief The X.509 algorithm identifier length of the SHA1 hash algorithm */
#define CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA1_ID_LENGTH 11U

/*--SHA2------------------------------------------------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/GENERAL/0004,1 */
#if (defined CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2224_ID)
#error CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2224_ID is already defined
#endif
/** \brief The X.509 algorithm identifier of the SHA-224 hash algorithm */
#define CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2224_ID                    \
{                                                         \
  0x30U, 0x0dU, 0x06U, 0x09U, 0x60U, 0x86U, 0x48U, 0x01U, \
  0x65U, 0x03U, 0x04U, 0x02U, 0x04U, 0x05U, 0x00U         \
}

#if (defined CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2224_ID_LENGTH)
#error CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2224_ID_LENGTH is already defined
#endif
/** \brief The X.509 algorithm identifier length of the SHA-224 hash algorithm */
#define CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2224_ID_LENGTH 15U

/* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/GENERAL/0005,1 */
#if (defined CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2256_ID)
#error CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2256_ID is already defined
#endif
/** \brief The X.509 algorithm identifier of the SHA-256 hash algorithm */
#define CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2256_ID                    \
{                                                         \
  0x30U, 0x0dU, 0x06U, 0x09U, 0x60U, 0x86U, 0x48U, 0x01U, \
  0x65U, 0x03U, 0x04U, 0x02U, 0x01U, 0x05U, 0x00U         \
}

#if (defined CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2256_ID_LENGTH)
#error CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2256_ID_LENGTH is already defined
#endif
/** \brief The X.509 algorithm identifier length of the SHA-256 hash algorithm */
#define CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2256_ID_LENGTH 15U

/* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/GENERAL/0006,1 */
#if (defined CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2384_ID)
#error CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2384_ID is already defined
#endif
/** \brief The X.509 algorithm identifier of the SHA-384 hash algorithm */
#define CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2384_ID                    \
{                                                         \
  0x30U, 0x0dU, 0x06U, 0x09U, 0x60U, 0x86U, 0x48U, 0x01U, \
  0x65U, 0x03U, 0x04U, 0x02U, 0x02U, 0x05U, 0x00U         \
}

#if (defined CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2384_ID_LENGTH)
#error CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2384_ID_LENGTH is already defined
#endif
/** \brief The X.509 algorithm identifier length of the SHA-384 hash algorithm */
#define CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2384_ID_LENGTH 15U

/* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/GENERAL/0007,1 */
#if (defined CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2512_ID)
#error CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2512_ID is already defined
#endif
/** \brief The X.509 algorithm identifier of the SHA-512 hash algorithm */
#define CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2512_ID                    \
{                                                         \
  0x30U, 0x0dU, 0x06U, 0x09U, 0x60U, 0x86U, 0x48U, 0x01U, \
  0x65U, 0x03U, 0x04U, 0x02U, 0x03U, 0x05U, 0x00U         \
}

#if (defined CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2512_ID_LENGTH)
#error CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2512_ID_LENGTH is already defined
#endif
/** \brief The X.509 algorithm identifier length of the SHA-512 hash algorithm */
#define CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA2512_ID_LENGTH 15U

/*--SHA3------------------------------------------------------------------------------------------*/

/* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/GENERAL/0008,1 */
#if (defined CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3224_ID)
#error CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3224_ID is already defined
#endif
/** \brief The X.509 algorithm identifier of the SHA3-224 hash algorithm */
#define CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3224_ID                    \
{                                                         \
  0x30U, 0x0dU, 0x06U, 0x09U, 0x60U, 0x86U, 0x48U, 0x01U, \
  0x65U, 0x03U, 0x04U, 0x02U, 0x07U, 0x05U, 0x00U         \
}

#if (defined CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3224_ID_LENGTH)
#error CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3224_ID_LENGTH is already defined
#endif
/** \brief The X.509 algorithm identifier length of the SHA3-224 hash algorithm */
#define CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3224_ID_LENGTH 15U

/* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/GENERAL/0009,1 */
#if (defined CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3256_ID)
#error CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3256_ID is already defined
#endif
/** \brief The X.509 algorithm identifier of the SHA3-256 hash algorithm */
#define CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3256_ID                    \
{                                                         \
  0x30U, 0x0dU, 0x06U, 0x09U, 0x60U, 0x86U, 0x48U, 0x01U, \
  0x65U, 0x03U, 0x04U, 0x02U, 0x08U, 0x05U, 0x00U         \
}

#if (defined CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3256_ID_LENGTH)
#error CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3256_ID_LENGTH is already defined
#endif
/** \brief The X.509 algorithm identifier length of the SHA3-256 hash algorithm */
#define CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3256_ID_LENGTH 15U

/* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/GENERAL/0010,1 */
#if (defined CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3384_ID)
#error CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3384_ID is already defined
#endif
/** \brief The X.509 algorithm identifier of the SHA3-384 hash algorithm */
#define CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3384_ID                    \
{                                                         \
  0x30U, 0x0dU, 0x06U, 0x09U, 0x60U, 0x86U, 0x48U, 0x01U, \
  0x65U, 0x03U, 0x04U, 0x02U, 0x09U, 0x05U, 0x00U         \
}

#if (defined CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3384_ID_LENGTH)
#error CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3384_ID_LENGTH is already defined
#endif
/** \brief The X.509 algorithm identifier length of the SHA3-384 hash algorithm */
#define CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3384_ID_LENGTH 15U

/* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/GENERAL/0011,1 */
#if (defined CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3512_ID)
#error CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3512_ID is already defined
#endif
/** \brief The X.509 algorithm identifier of the SHA3-512 hash algorithm */
#define CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3512_ID                    \
{                                                         \
  0x30U, 0x0dU, 0x06U, 0x09U, 0x60U, 0x86U, 0x48U, 0x01U, \
  0x65U, 0x03U, 0x04U, 0x02U, 0x0aU, 0x05U, 0x00U         \
}

#if (defined CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3512_ID_LENGTH)
#error CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3512_ID_LENGTH is already defined
#endif
/** \brief The X.509 algorithm identifier length of the SHA3-512 hash algorithm */
#define CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_SHA3512_ID_LENGTH 15U

/*==================[type definitions]============================================================*/

/** \brief  Workspace of primitive SIGNATUREGENERATE_RSA_RSASSAPKCS1V15.
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
 **         Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Callback().
 **
 ** \var    notifyResult
 ** \brief  The value of the callback result received from a secondary primitive via
 **         Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Callback().
 **
 ** \var    lockMain
 ** \brief  Flag to lock multiple parallel executions of Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Main().
 **
 ** ---specific-------------------------------------------------------------------
 **
 ** \brief  Context for the SIGNATUREGENERATE_RSA_RSASSAPKCS1V15
 ** \var  priExp
 ** \brief  A pointer to a buffer which is used for private exponent.
 **
 ** \var  modulus
 ** \brief  A pointer to a buffer which is used for modulus.
 **
 ** \var  signature
 ** \brief  A pointer to the heap where the signature will be stored.
 **
 ** \var  heapTmp1
 ** \brief  A pointer to the heap which is used as a buffer for intermediate result in LN representation.
 **
 ** \var  algorithmId
 ** \brief  A pointer to a buffer which is used for the Hash algorithm Id.
 **
 ** \var  EM
 ** \brief  A pointer to the heap which is used as a buffer for the Encoded Message "EM" during
 **         the signature generation and verification.
 **
 ** \var  pubExpLen
 ** \brief  The length of the public exponent
 **
 ** \var  priExpLen
 ** \brief  The length of the private exponent
 **
 ** \var  modulusLen
 ** \brief  The length of the modulus.
 **
 ** \var  algorithmIdLength
 ** \brief  The length of Id of the used HASH service.
 **
 ** \var  hashLength
 ** \brief  The length of the hash algorithm.
 **
 ** \var  msgDigest
 ** \brief  A buffer where the hash value of message will be stored.
 **
 ** \var  DERHeaderMsgDigestBuffer
 ** \brief  A buffer where the length of message digest will be stored.
 **
 ** \var  DERHeaderDigestInfoBuffer
 ** \brief  A buffer where the length of digest info will be stored.
 **
 ** \var  lnCtx
 ** \brief  The context which has to be used for long number arithmetic.
 **
 ** \var  secondaryJob_primitiveInfo
 ** \brief  The Crypto_xVIx_xAIx_NonConstPrimitiveInfoType instance of the HASH service job used by SIGNATUREGENERATE_RSA_RSASSAPKCS1V15.
 **
 ** \var  secondaryJob_jobPrimitiveInfo
 ** \brief  The Crypto_JobPrimitiveInfoType instance of the HASH service job used by SIGNATUREGENERATE_RSA_RSASSAPKCS1V15.
 **
 ** \var  secondaryJob_jobInfo
 ** \brief  The Crypto_JobInfoType instance of the HASH service job used by SIGNATUREGENERATE_RSA_RSASSAPKCS1V15.
 **
 ** \var  secondaryJob
 ** \brief  The Crypto_JobType instance of the HASH service job used by SIGNATUREGENERATE_RSA_RSASSAPKCS1V15.
 **/

/* !LINKSTO Crypto.Dsn.Api/Types/Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType/0001,1 */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
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
  P2CONST(Crypto_xVIx_xAIx_LNWordType,      AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) priExp;
  P2CONST(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) modulus;
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) signature;
    P2VAR(Crypto_xVIx_xAIx_LNWordType,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) heapTmp1;

  P2CONST(uint8,                        AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) algorithmId;
    P2VAR(uint8,                        AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) EM;

  Crypto_xVIx_xAIx_LNWordType     pubExpLen;
  Crypto_xVIx_xAIx_LNWordType     priExpLen;
  Crypto_xVIx_xAIx_LNWordType     modulusLen;
  uint32                          algorithmIdLength;
  uint32                          hashLength;

  uint8                           msgDigest[CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASHRESULTSIZE];
  uint8                           DERHeaderMsgDigestBuffer[CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_DER_HEADER_MAX_LEN];
  uint8                           DERHeaderDigestInfoBuffer[CRYPTO_XVIX_XAIX_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_DER_HEADER_MAX_LEN];

  Crypto_xVIx_xAIx_LNCtxType      lnCtx;

  Crypto_xVIx_xAIx_NonConstPrimitiveInfoType secondaryJob_primitiveInfo;
  Crypto_JobPrimitiveInfoType                secondaryJob_jobPrimitiveInfo;

  Crypto_JobInfoType              secondaryJob_jobInfo;
  Crypto_JobType                  secondaryJob;
}
Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_WorkspaceType;
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Process
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Main
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Cancel
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Reset
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Restart
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

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
#if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Callback
(
          uint32                                                                    objectId,
    P2VAR(Crypto_JobType,                    AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) job,
  P2CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) primitive,
          Crypto_xVIx_xAIx_CallbackType                                             cbkType,
          Std_ReturnType                                                            cbkResult
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_H */

/*==================[end of file]=================================================================*/

