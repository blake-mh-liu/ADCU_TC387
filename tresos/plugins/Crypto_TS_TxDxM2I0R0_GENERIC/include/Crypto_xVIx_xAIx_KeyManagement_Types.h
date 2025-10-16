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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_KeyManagement_Types.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_KEYMANAGEMENT_TYPES_H
#define CRYPTO_XVIX_XAIX_KEYMANAGEMENT_TYPES_H

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

#include <TSAutosar.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_KeyManagement_Types.h/0002,1 */

#include <Crypto_xVIx_xAIx_Version.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_KeyManagement_Types.h/0003,1 */

/*==================[macros]======================================================================*/

#if(defined CRYPTO_XVIX_XAIX_KE_AES_EXPANDEDKEY)
#error CRYPTO_XVIX_XAIX_KE_AES_EXPANDEDKEY is already defined
#endif
/** \brief Key element to which can be used together with the key element CRYPTO_KE_MAC_KEY to
 *         precalculate the expanded AES key
 */
#define CRYPTO_XVIX_XAIX_KE_AES_EXPANDEDKEY 1000U

#if(defined CRYPTO_XVIX_XAIX_KE_MAC_AESCMAC_SUBKEY1)
#error CRYPTO_XVIX_XAIX_KE_MAC_AESCMAC_SUBKEY1 is already defined
#endif
/** \brief Key element to which can be used together with the key element CRYPTO_KE_MAC_KEY to
 *         precalculate the AES-CMAC subkey K1
 */
#define CRYPTO_XVIX_XAIX_KE_MAC_AESCMAC_SUBKEY1 1001U

#if(defined CRYPTO_XVIX_XAIX_KE_MAC_AESCMAC_SUBKEY2)
#error CRYPTO_XVIX_XAIX_KE_MAC_AESCMAC_SUBKEY2 is already defined
#endif
/** \brief Key element to which can be used together with the key element CRYPTO_KE_MAC_KEY to
 *         precalculate the AES-CMAC subkey K2
 */
#define CRYPTO_XVIX_XAIX_KE_MAC_AESCMAC_SUBKEY2 1002U

#if(defined CRYPTO_XVIX_XAIX_KE_SIGNATURE_BARRETT)
#error CRYPTO_XVIX_XAIX_KE_SIGNATURE_BARRETT is already defined
#endif
/** \brief Key element which can be used to store the barrett of an RSA key. */
#define CRYPTO_XVIX_XAIX_KE_SIGNATURE_BARRETT 1003U

#if (defined CRYPTO_XVIX_XAIX_KE_RSA_ADDITIONAL_INPUT)
#error CRYPTO_XVIX_XAIX_KE_RSA_ADDITIONAL_INPUT is already defined
#endif
/** \brief Key element which can be used to store the RSA additional input. */
#define CRYPTO_XVIX_XAIX_KE_RSA_ADDITIONAL_INPUT 1004U

#if(defined CRYPTO_XVIX_XAIX_KE_AES_CTRDRBG_SEED_COUNT)
#error CRYPTO_XVIX_XAIX_KE_AES_CTRDRBG_SEED_COUNT is already defined
#endif
/** \brief Key element which can be used together with the key element CRYPTO_KE_RANDOM_SEED_STATE
 *         to store the seed count.
 */
#define CRYPTO_XVIX_XAIX_KE_AES_CTRDRBG_SEED_COUNT 1005U

#if (defined CRYPTO_XVIX_XAIX_KE_KMNCOMMON_WORKSPACE)
#error CRYPTO_XVIX_XAIX_KE_KMNCOMMON_WORKSPACE is already defined
#endif
/** \brief The KeyElementID of the workspace, which is used as a buffer for key exchange/key generate */
#define CRYPTO_XVIX_XAIX_KE_KMNCOMMON_WORKSPACE 1006U

#if (defined CRYPTO_XVIX_XAIX_KE_KEYDERIVATION_FIXEDINFOID)
#error CRYPTO_XVIX_XAIX_KE_KEYDERIVATION_FIXEDINFOID is already defined
#endif
/** \brief Key element which can be used to store the Key Derived Fixed Information input. */
#define CRYPTO_XVIX_XAIX_KE_KEYDERIVATION_FIXEDINFOID 1007U

/** \brief Macro representing the key derive element id
 **/
#if (defined CRYPTO_XVIX_XAIX_KDF_DERIVED_KEY_ELEMENT_ID)
#error CRYPTO_XVIX_XAIX_KDF_DERIVED_KEY_ELEMENT_ID is already defined
#endif
#define CRYPTO_XVIX_XAIX_KDF_DERIVED_KEY_ELEMENT_ID 1U

#if(defined CRYPTO_XVIX_XAIX_KE_CCM_MAC_LEN)
#error CRYPTO_XVIX_XAIX_KE_CCM_MAC_LEN is already defined
#endif
/** \brief Key element which can be used together with the key element CRYPTO_XVIX_XAIX_KE_CCM_MAC_LEN
 *         to store the MAC length.
 */
#define CRYPTO_XVIX_XAIX_KE_CCM_MAC_LEN 1008U

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_KEYMANAGEMENT_TYPES_H */

/*==================[end of file]=================================================================*/

