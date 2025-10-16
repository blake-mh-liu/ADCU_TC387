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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_Cfg.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_CFG_H
#define CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_CFG_H

[!AUTOSPACING!]
[!/* ====================================================================================== */!][!//
[!INCLUDE "Crypto_xVIx_xAIx_Macros.m"!]
[!/* ====================================================================================== */!][!//
[!//
/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

/*==================[macros]======================================================================*/

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/0001,1 */
#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15)
#error CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 is already defined
#endif
/** \brief  Macro representing whether the SIGNATUREGENERATE_RSA_RSASSAPKCS1V15
 **         primitive is directly or indirectly assigned to a Crypto Driver Object.
 **/
[!CALL "GetPrimitivesPoolList", "ctr" = "node:path(CryptoDriverObjects)"!][!//
[!IF "contains($PrimitivesPoolListShrt, 'SIGNATUREGENERATE_RSA_RSASSAPKCS1V15') and lic:feature(Crypto:GetCprFeatureName('SIGNATUREGENERATE_RSA_RSASSAPKCS1V15', 'EB_SEC_CPR'))"!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 STD_ON
[!ELSE!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15 STD_OFF
[!ENDIF!][!//

[!LOOP "util:distinct(node:refs(./CryptoDriverObjects/CryptoDriverObject/eb-list::*/CryptoPrimitiveRef/eb-list::*))"!][!//
  [!VAR "psrv" = "text:replace(node:value(./CryptoPrimitiveService), '_', '')"!][!//
  [!VAR "pfam" = "text:toupper(text:replace(text:replace(node:value(./CryptoPrimitiveAlgorithmFamiliy/eb-list::*[node:pos(.)=0]), 'CRYPTO_ALGOFAM_', ''), '_', ''))"!][!//
  [!VAR "pmod" = "text:toupper(text:replace(text:replace(text:replace(text:replace(node:value(./CryptoPrimitiveAlgorithmMode/eb-list::*[node:pos(.)=0]), 'CRYPTO_ALGOMODE_', '' ), '_', ''), '_', ''), '_', ''))"!]
  [!VAR "sfam" = "text:toupper(text:replace(text:replace(node:value(./CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0]), 'CRYPTO_ALGOFAM_', ''), '_', ''))"!][!//
[!//
  [!IF "$psrv = 'SIGNATUREGENERATE' and $pfam = 'RSA' and $pmod = 'RSASSAPKCS1V15'"!]
#ifndef CRYPTO_XVIX_XAIX_INC_ENABLED_[!"$psrv"!]_[!"$pfam"!]_[!"$pmod"!]_HASH_[!"$sfam"!]_NOTSET
#define CRYPTO_XVIX_XAIX_INC_ENABLED_[!"$psrv"!]_[!"$pfam"!]_[!"$pmod"!]_HASH_[!"$sfam"!]_NOTSET       STD_ON
#endif

  [!ENDIF!][!//
[!ENDLOOP!][!//
[!CALL "GetMaxResultSizeOfSecondary", "ctr" = "node:path(CryptoDriverObjects)", "psrv" = "'SIGNATURE_GENERATE'", "pfam" = "'CRYPTO_ALGOFAM_RSA'", "pmod"= "'CRYPTO_ALGOMODE_RSASSA_PKCS1_v1_5'"!][!//
[!VAR "DgstResultSize" = "$HashResultSize"!][!//
/* !LINKSTO Crypto.Req.CPr/SIGNATUREGENERATE_RSA_RSASSAPKCS1V15/GENERAL/0002,1 */
#if    (defined CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASHRESULTSIZE)
#error  CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASHRESULTSIZE already defined
#endif
/** \brief  Macro indicating the length of the hash result in bytes. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_HASHRESULTSIZE [!"$DgstResultSize"!]

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREGENERATE_RSA_RSASSAPKCS1V15_CFG_H */

/*==================[end of file]=================================================================*/

