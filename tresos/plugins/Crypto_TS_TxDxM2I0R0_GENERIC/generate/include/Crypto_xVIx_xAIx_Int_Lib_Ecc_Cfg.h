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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Lib_Ecc_Cfg.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_INT_LIB_ECC_CFG_H
#define CRYPTO_XVIX_XAIX_INT_LIB_ECC_CFG_H
[!AUTOSPACING!][!//
[!/*========================================================================================*/!][!//
[!INCLUDE "Crypto_xVIx_xAIx_Macros.m"!]
[!CALL "GetPrimitivesPoolList", "ctr" = "node:path(CryptoDriverObjects)"!]
[!/*========================================================================================*/!][!//
[!//

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

/*==================[macros]======================================================================*/

#if (defined CRYPTO_XVIX_XAIX_ALGOFAM_ED25519_ENABLED)
#error CRYPTO_XVIX_XAIX_ALGOFAM_ED25519_ENABLED is already defined
#endif
/** \brief  Macro representing if Ed25519 scheme is enabled **/
[!VAR "Enabled" = "'false'"!]
[!IF "node:containsValue(CryptoPrimitives/eb-list::*/CryptoPrimitive/eb-list::*/CryptoPrimitiveAlgorithmFamiliy/eb-list::*, 'CRYPTO_ALGOFAM_ED25519')
"!]
  [!VAR "Enabled" = "'true'"!]
[!ENDIF!]
#define CRYPTO_XVIX_XAIX_ALGOFAM_ED25519_ENABLED [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_ALGOFAM_ED25519PH_ENABLED)
#error CRYPTO_XVIX_XAIX_ALGOFAM_ED25519PH_ENABLED is already defined
#endif
/** \brief  Macro representing if Ed25519ph scheme is enabled **/
[!VAR "Enabled" = "'false'"!]
[!IF "node:containsValue(CryptoPrimitives/eb-list::*/CryptoPrimitive/eb-list::*/CryptoPrimitiveAlgorithmFamiliy/eb-list::*, 'CRYPTO_ALGOFAM_ED25519PH')
"!]
  [!VAR "Enabled" = "'true'"!]
[!ENDIF!]
#define CRYPTO_XVIX_XAIX_ALGOFAM_ED25519PH_ENABLED [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_ELLIPTICCURVEINFO)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_ELLIPTICCURVEINFO is already defined
#endif
/** \brief  Macro representing if elliptic curve info is enabled **/
[!VAR "Enabled" = "'false'"!]
[!IF "   contains($PrimitivesPoolListShrt, 'SIGNATUREGENERATE_ED25519_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_ED25519_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREGENERATE_ED25519PH_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_ED25519PH_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREGENERATE_ECDSA_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_ECDSA_NOTSET')
      or (
          node:exists(./CryptoKeys)
          and (    node:containsValue(CryptoEbGeneral/CryptoEbMisc/CryptoEbKeyManagementAlgorithm/eb-list::*, 'CRYPTO_KMN_KEYEXCHANGE_X25519_NOTSET'   )
                or node:containsValue(CryptoEbGeneral/CryptoEbMisc/CryptoEbKeyManagementAlgorithm/eb-list::*, 'CRYPTO_KMN_KEYGENERATE_ED25519_NOTSET'  )
                or node:containsValue(CryptoEbGeneral/CryptoEbMisc/CryptoEbKeyManagementAlgorithm/eb-list::*, 'CRYPTO_KMN_KEYGENERATE_ED25519PH_NOTSET')
              )
         )
"!]
  [!VAR "Enabled" = "'true'"!]
[!ENDIF!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_ELLIPTICCURVEINFO [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_GETECINDEX)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_GETECINDEX is already defined
#endif
/** \brief  Macro representing if get EC key is enabled **/
[!VAR "Enabled" = "'false'"!]
[!IF "   contains($PrimitivesPoolListShrt, 'SIGNATUREGENERATE_ED25519_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_ED25519_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREGENERATE_ED25519PH_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_ED25519PH_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREGENERATE_ECDSA_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_ECDSA_NOTSET')
"!]
  [!VAR "Enabled" = "'true'"!]
[!ENDIF!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_GETECINDEX [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTION)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTION is already defined
#endif
/** \brief  Macro representing if fast reduction is enabled **/
[!VAR "Enabled" = "'false'"!]
[!IF "   contains($PrimitivesPoolListShrt, 'SIGNATUREGENERATE_ED25519_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_ED25519_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREGENERATE_ED25519PH_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_ED25519PH_NOTSET')
      or (
          node:exists(./CryptoKeys)
          and (    node:containsValue(CryptoEbGeneral/CryptoEbMisc/CryptoEbKeyManagementAlgorithm/eb-list::*, 'CRYPTO_KMN_KEYEXCHANGE_X25519_NOTSET'   )
                or node:containsValue(CryptoEbGeneral/CryptoEbMisc/CryptoEbKeyManagementAlgorithm/eb-list::*, 'CRYPTO_KMN_KEYGENERATE_ED25519_NOTSET'  )
                or node:containsValue(CryptoEbGeneral/CryptoEbMisc/CryptoEbKeyManagementAlgorithm/eb-list::*, 'CRYPTO_KMN_KEYGENERATE_ED25519PH_NOTSET')
              )
         )
"!]
  [!VAR "Enabled" = "'true'"!]
[!ENDIF!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAFASTREDUCTION [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTMULTIPLICATION)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTMULTIPLICATION is already defined
#endif
/** \brief  Macro representing if point multiplication is enabled **/
[!VAR "Enabled" = "'false'"!]
[!IF "   contains($PrimitivesPoolListShrt, 'SIGNATUREGENERATE_ED25519_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_ED25519_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREGENERATE_ED25519PH_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_ED25519PH_NOTSET')
      or (
          node:exists(./CryptoKeys)
          and (    node:containsValue(CryptoEbGeneral/CryptoEbMisc/CryptoEbKeyManagementAlgorithm/eb-list::*, 'CRYPTO_KMN_KEYGENERATE_ED25519_NOTSET'  )
                or node:containsValue(CryptoEbGeneral/CryptoEbMisc/CryptoEbKeyManagementAlgorithm/eb-list::*, 'CRYPTO_KMN_KEYGENERATE_ED25519PH_NOTSET')
              )
         )
"!]
  [!VAR "Enabled" = "'true'"!]
[!ENDIF!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTMULTIPLICATION [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITION)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITION is already defined
#endif
/** \brief  Macro representing if point addition is enabled **/
[!VAR "Enabled" = "'false'"!]
[!IF "   contains($PrimitivesPoolListShrt, 'SIGNATUREGENERATE_ED25519_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_ED25519_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREGENERATE_ED25519PH_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_ED25519PH_NOTSET')
      or (
          node:exists(./CryptoKeys)
          and (    node:containsValue(CryptoEbGeneral/CryptoEbMisc/CryptoEbKeyManagementAlgorithm/eb-list::*, 'CRYPTO_KMN_KEYGENERATE_ED25519_NOTSET'  )
                or node:containsValue(CryptoEbGeneral/CryptoEbMisc/CryptoEbKeyManagementAlgorithm/eb-list::*, 'CRYPTO_KMN_KEYGENERATE_ED25519PH_NOTSET')
              )
         )
"!]
  [!VAR "Enabled" = "'true'"!]
[!ENDIF!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_EDDSAPOINTADDITION [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_POINTCONVERTPROJ2AFF)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_POINTCONVERTPROJ2AFF is already defined
#endif
/** \brief  Macro representing if point convertion from projective to affine is enabled **/
[!VAR "Enabled" = "'false'"!]
[!IF "   contains($PrimitivesPoolListShrt, 'SIGNATUREGENERATE_ED25519_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_ED25519_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREGENERATE_ED25519PH_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_ED25519PH_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREGENERATE_ECDSA_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_ECDSA_NOTSET')
      or (
          node:exists(./CryptoKeys)
          and (    node:containsValue(CryptoEbGeneral/CryptoEbMisc/CryptoEbKeyManagementAlgorithm/eb-list::*, 'CRYPTO_KMN_KEYGENERATE_ED25519_NOTSET'  )
                or node:containsValue(CryptoEbGeneral/CryptoEbMisc/CryptoEbKeyManagementAlgorithm/eb-list::*, 'CRYPTO_KMN_KEYGENERATE_ED25519PH_NOTSET')
              )
         )
"!]
  [!VAR "Enabled" = "'true'"!]
[!ENDIF!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_POINTCONVERTPROJ2AFF [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_FUNCTIONS)
#error CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_FUNCTIONS is already defined
#endif
/** \brief  Macro representing if ECC functions are enabled **/
[!VAR "Enabled" = "'false'"!]
[!IF "   contains($PrimitivesPoolListShrt, 'SIGNATUREGENERATE_ECDSA_NOTSET')
      or contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_ECDSA_NOTSET')
"!]
  [!VAR "Enabled" = "'true'"!]
[!ENDIF!]
#define CRYPTO_XVIX_XAIX_API_ENABLED_LIB_ECC_FUNCTIONS [!WS "1"!][!IF "$Enabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!CR!]

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_INT_LIB_ECC_CFG_H */

/*==================[end of file]=================================================================*/

