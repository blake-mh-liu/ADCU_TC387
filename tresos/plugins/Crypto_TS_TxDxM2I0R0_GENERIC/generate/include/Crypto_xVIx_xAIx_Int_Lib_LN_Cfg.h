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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Lib_LN_Cfg.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_INT_LIB_LN_CFG_H
#define CRYPTO_XVIX_XAIX_INT_LIB_LN_CFG_H
[!AUTOSPACING!][!//
[!/*========================================================================================*/!][!//
[!INCLUDE "Crypto_xVIx_xAIx_Macros.m"!]
[!CALL "GetPrimitivesPoolList", "ctr" = "node:path(CryptoDriverObjects)"!]
[!/*========================================================================================*/!][!//
[!//

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

/*==================[macros]======================================================================*/

/* --- LN --------------------------------------------------------------------------------------- */

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_ADDITIONMODULAR)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_ADDITIONMODULAR is already defined
#endif
/** \brief   Macro representing if addition modular is enabled **/
[!VAR "Enabled" = "'true'"!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_ADDITIONMODULAR [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_MAX_KEY_NUM_LEN_WORDS,1 */
#if (defined CRYPTO_XVIX_XAIX_MAX_KEY_NUM_LEN_WORDS)
#error CRYPTO_XVIX_XAIX_MAX_KEY_NUM_LEN_WORDS is already defined
#endif
/** \brief   Macro representing the biggest key length of a configured primitive **/
#define CRYPTO_XVIX_XAIX_MAX_KEY_NUM_LEN_WORDS [!WS "1"!][!IF "num:i(count(CryptoKeys/CryptoKey/eb-list::*)) != 0"!]   \
[!VAR "KeyElemCount" = "num:i(count(node:filter(util:distinct(node:refs(util:distinct(node:refs(CryptoKeys/CryptoKey/eb-list::*/CryptoKeyTypeRef))/CryptoKeyElementRef/eb-list::*)), '1 = ./CryptoKeyElementId')))"!][!//
[!VAR "MaxKeySize" = "num:i(0)"!][!//
[!IF "num:i(0) < num:i($KeyElemCount)"!][!//
  [!VAR "MaxKeySize" = "num:max(node:filter(util:distinct(node:refs(util:distinct(node:refs(CryptoKeys/CryptoKey/eb-list::*/CryptoKeyTypeRef))/CryptoKeyElementRef/eb-list::*)), '1 = ./CryptoKeyElementId')/CryptoKeyElementSize)"!][!//
[!ENDIF!][!//
[!IF "num:i(0) = num:i($MaxKeySize)"!][!//
  [!VAR "MaxKeySize" = "num:i(1)"!][!//
[!ENDIF!][!//
(                                                 \
  (Crypto_xVIx_xAIx_LNWordType)                   \
  (                                               \
    CRYPTO_XVIX_XAIX_LN_NUMBER_LEN([!"num:i($MaxKeySize)"!]) +                 \
    (Crypto_xVIx_xAIx_LNWordType)1UL              \
  )                                               \
)[!ELSE!]1U[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODEXP)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODEXP is already defined
#endif
/** \brief  Macro representing if Mod Exp is enabled **/
[!VAR "Enabled" = "'false'"!]
[!IF "   contains($PrimitivesPoolListShrt, 'ENCRYPT_RSA_RSAESOAEP')
      or contains($PrimitivesPoolListShrt, 'DECRYPT_RSA_RSAESOAEP')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_ED25519_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_ED25519PH_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_RSA_RSASSAPSS')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_RSA_RSASSAPKCS1V15')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREGENERATE_RSA_RSASSAPKCS1V15')
"!]
  [!VAR "Enabled" = "'true'"!]
[!ENDIF!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODEXP [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_INVERSION)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_INVERSION is already defined
#endif
/** \brief  Macro representing if inversion is enabled **/
[!VAR "Enabled" = "'true'"!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_INVERSION [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SUBTRACTIONMODULAR)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SUBTRACTIONMODULAR is already defined
#endif
/** \brief  Macro representing if subtraction modular is enabled **/
[!VAR "Enabled" = "'true'"!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SUBTRACTIONMODULAR [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_ADDITION)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_ADDITION is already defined
#endif
/** \brief  Macro representing if addition is enabled **/
[!VAR "Enabled" = "'true'"!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_ADDITION [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_NUMBERTOLEBYTEARRAY)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_NUMBERTOLEBYTEARRAY is already defined
#endif
/** \brief  Macro representing if conversation to a little endian byte array is enabled **/
[!VAR "Enabled" = "'true'"!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_NUMBERTOLEBYTEARRAY [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_LEBYTEARRAYTONUMBER)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_LEBYTEARRAYTONUMBER is already defined
#endif
/** \brief  Macro representing if conversation of a byte array which contains a number in little endian
 **         notation to long number is enabled **/
[!VAR "Enabled" = "'true'"!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_LEBYTEARRAYTONUMBER [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_NUMBERTOBEBYTEARRAY)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_NUMBERTOBEBYTEARRAY is already defined
#endif
/** \brief  Macro representing if conversation to a big endian byte array is enabled **/
[!VAR "Enabled" = "'true'"!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_NUMBERTOBEBYTEARRAY [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_BEBYTEARRAYTONUMBER)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_BEBYTEARRAYTONUMBER is already defined
#endif
/** \brief  Macro representing if conversation of a byte array which contains a number in big endian
 **         notation to long number is enabled **/
[!VAR "Enabled" = "'true'"!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_BEBYTEARRAYTONUMBER [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODULO)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODULO is already defined
#endif
/** \brief  Macro representing if modulo is enabled **/
[!VAR "Enabled" = "'true'"!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODULO [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_COMPARENUMBERS)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_COMPARENUMBERS is already defined
#endif
/** \brief  Macro representing if compare numbers is enabled **/
[!VAR "Enabled" = "'true'"!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_COMPARENUMBERS [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SUBTRACTION)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SUBTRACTION is already defined
#endif
/** \brief  Macro representing if subtraction is enabled **/
[!VAR "Enabled" = "'true'"!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SUBTRACTION [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SQUARECOMBA)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SQUARECOMBA is already defined
#endif
/** \brief  Macro representing if square comba is enabled **/
[!VAR "Enabled" = "'false'"!]
[!IF "   contains($PrimitivesPoolListShrt, 'ENCRYPT_RSA_RSAESOAEP')
      or contains($PrimitivesPoolListShrt, 'DECRYPT_RSA_RSAESOAEP')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREGENERATE_ED25519_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_ED25519_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREGENERATE_ED25519PH_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_ED25519PH_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_RSA_RSASSAPSS')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_RSA_RSASSAPKCS1V15')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREGENERATE_RSA_RSASSAPKCS1V15')
      or (
          node:exists(./CryptoKeys)
          and (    node:containsValue(CryptoEbGeneral/CryptoEbMisc/CryptoEbKeyManagementAlgorithm/eb-list::*, 'CRYPTO_KMN_KEYGENERATE_ED25519_NOTSET'  )
                or node:containsValue(CryptoEbGeneral/CryptoEbMisc/CryptoEbKeyManagementAlgorithm/eb-list::*, 'CRYPTO_KMN_KEYGENERATE_ED25519PH_NOTSET')
              )
         )
"!]
  [!VAR "Enabled" = "'true'"!]
[!ENDIF!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_SQUARECOMBA [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODEXPBARRETT)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODEXPBARRETT is already defined
#endif
/** \brief  Macro representing if mod exp barret is enabled **/
[!VAR "Enabled" = "'false'"!]
[!IF "   contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_RSA_RSASSAPSS')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_RSA_RSASSAPKCS1V15')
"!]
  [!VAR "Enabled" = "'true'"!]
[!ENDIF!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MODEXPBARRETT [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_ISVALID)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_ISVALID is already defined
#endif
/** \brief  Macro representing if LN is valid is enabled **/
[!VAR "Enabled" = "'false'"!]
[!IF "   contains($PrimitivesPoolListShrt, 'ENCRYPT_RSA_RSAESOAEP')
      or contains($PrimitivesPoolListShrt, 'DECRYPT_RSA_RSAESOAEP')
"!]
  [!VAR "Enabled" = "'true'"!]
[!ENDIF!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_ISVALID [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_BITLENGTHOFNUMBER)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_BITLENGTHOFNUMBER is already defined
#endif
/** \brief  Macro representing if bit length of number is enabled **/
[!VAR "Enabled" = "'true'"!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_BITLENGTHOFNUMBER [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MULTIPLYNUMBERS)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MULTIPLYNUMBERS is already defined
#endif
/** \brief  Macro representing if multiply numbers is enabled **/
[!VAR "Enabled" = "'true'"!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_MULTIPLYNUMBERS [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_NORMALIZENUMBER)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_NORMALIZENUMBER is already defined
#endif
/** \brief  Macro representing if normalize number is enabled **/
[!VAR "Enabled" = "'true'"!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_LN_NORMALIZENUMBER [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/* --- RSA -------------------------------------------------------------------------------------- */

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_DECODERSAKEY)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_DECODERSAKEY is already defined
#endif
/** \brief  Macro representing if decode RSA key is enabled **/
[!VAR "Enabled" = "'false'"!]
[!IF "   contains($PrimitivesPoolListShrt, 'ENCRYPT_RSA_RSAESOAEP')
      or contains($PrimitivesPoolListShrt, 'DECRYPT_RSA_RSAESOAEP')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_RSA_RSASSAPSS')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_RSA_RSASSAPKCS1V15')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREGENERATE_RSA_RSASSAPKCS1V15')
      and (
          node:exists(./CryptoKeys)
          and (
                ("num:i(count(util:distinct(node:refs(util:distinct(node:refs(./CryptoKeys/CryptoKey/eb-list::*/CryptoKeyTypeRef))/CryptoKeyElementRef/eb-list::*))/CryptoKeyElementFormat[. = 'CRYPTO_KE_FORMAT_BIN_RSA_PRIVATEKEY'])) > 0")
                or
                ("num:i(count(util:distinct(node:refs(util:distinct(node:refs(./CryptoKeys/CryptoKey/eb-list::*/CryptoKeyTypeRef))/CryptoKeyElementRef/eb-list::*))/CryptoKeyElementFormat[. = 'CRYPTO_KE_FORMAT_BIN_RSA_PUBLICKEY'])) > 0")
              )
          )
"!]
  [!VAR "Enabled" = "'true'"!]
[!ENDIF!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_DECODERSAKEY [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_ENCODERSAKEY)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_ENCODERSAKEY is already defined
#endif
/** \brief  Macro representing if encode RSA key is enabled **/
[!VAR "Enabled" = "'false'"!]
[!IF "   contains($PrimitivesPoolListShrt, 'ENCRYPT_RSA_RSAESOAEP')
      or contains($PrimitivesPoolListShrt, 'DECRYPT_RSA_RSAESOAEP')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_RSA_RSASSAPSS')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_RSA_RSASSAPKCS1V15')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREGENERATE_RSA_RSASSAPKCS1V15')
      and (
          node:exists(./CryptoKeys)
          and (
                ("num:i(count(util:distinct(node:refs(util:distinct(node:refs(./CryptoKeys/CryptoKey/eb-list::*/CryptoKeyTypeRef))/CryptoKeyElementRef/eb-list::*))/CryptoKeyElementFormat[. = 'CRYPTO_KE_FORMAT_BIN_RSA_PRIVATEKEY'])) > 0")
                or
                ("num:i(count(util:distinct(node:refs(util:distinct(node:refs(./CryptoKeys/CryptoKey/eb-list::*/CryptoKeyTypeRef))/CryptoKeyElementRef/eb-list::*))/CryptoKeyElementFormat[. = 'CRYPTO_KE_FORMAT_BIN_RSA_PUBLICKEY'])) > 0")
              )
          )
"!]
  [!VAR "Enabled" = "'true'"!]
[!ENDIF!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_RSA_ENCODERSAKEY [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/* --- DER -------------------------------------------------------------------------------------- */

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_HEADERSEQUENCE)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_HEADERSEQUENCE is already defined
#endif
/** \brief  Macro representing if header sequenece is enabled **/
[!VAR "Enabled" = "'false'"!]
[!IF "   contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_RSA_RSASSAPKCS1V15')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREGENERATE_RSA_RSASSAPKCS1V15')
"!]
  [!VAR "Enabled" = "'true'"!]
[!ENDIF!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_HEADERSEQUENCE [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_HEADEROCTETSTRING)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_HEADEROCTETSTRING is already defined
#endif
/** \brief  Macro representing if header octec string is enabled **/
[!VAR "Enabled" = "'false'"!]
[!IF "   contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_RSA_RSASSAPKCS1V15')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREGENERATE_RSA_RSASSAPKCS1V15')
      or contains($PrimitivesPoolListShrt, 'ENCRYPT_RSA_RSAESOAEP')
      or contains($PrimitivesPoolListShrt, 'DECRYPT_RSA_RSAESOAEP')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_RSA_RSASSAPSS')
"!]
  [!VAR "Enabled" = "'true'"!]
[!ENDIF!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_DER_HEADEROCTETSTRING [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_INT_LIB_LN_CFG_H */

/*==================[end of file]=================================================================*/

