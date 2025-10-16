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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_SIGNATUREVERIFY_RSA_RSASSAPSS_Cfg.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_RSA_RSASSAPSS_CFG_H
#define CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_RSA_RSASSAPSS_CFG_H

[!AUTOSPACING!]
[!/* ====================================================================================== */!][!//
[!INCLUDE "Crypto_xVIx_xAIx_Macros.m"!]
[!/* ====================================================================================== */!][!//
[!//
/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

/*==================[macros]======================================================================*/

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_RSA_RSASSAPSS/0001,1 */
#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_RSA_RSASSAPSS)
#error CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_RSA_RSASSAPSS is already defined
#endif
/** \brief  Macro representing whether the SIGNATUREVERIFY_RSA_RSASSAPSS
 **         primitive is directly or indirectly assigned to a Crypto Driver Object.
 **/
[!CALL "GetPrimitivesPoolList", "ctr" = "node:path(CryptoDriverObjects)"!][!//
[!IF "contains($PrimitivesPoolListShrt, 'SIGNATUREVERIFY_RSA_RSASSAPSS') and lic:feature(Crypto:GetCprFeatureName('SIGNATUREVERIFY_RSA_RSASSAPSS', 'EB_SEC_CPR'))"!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_RSA_RSASSAPSS STD_ON
[!ELSE!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_CPR_SIGNATUREVERIFY_RSA_RSASSAPSS STD_OFF
[!ENDIF!][!//

[!LOOP "util:distinct(node:refs(./CryptoDriverObjects/CryptoDriverObject/eb-list::*/CryptoPrimitiveRef/eb-list::*))"!][!//
  [!VAR "psrv" = "text:replace(node:value(./CryptoPrimitiveService), '_', '')"!][!//
  [!VAR "pfam" = "text:toupper(text:replace(text:replace(node:value(./CryptoPrimitiveAlgorithmFamiliy/eb-list::*[node:pos(.)=0]), 'CRYPTO_ALGOFAM_', ''), '_', ''))"!][!//
  [!VAR "pmod" = "text:toupper(text:replace(text:replace(text:replace(text:replace(node:value(./CryptoPrimitiveAlgorithmMode/eb-list::*[node:pos(.)=0]), 'CRYPTO_ALGOMODE_', '' ), '_', ''), '_', ''), '_', ''))"!]
  [!VAR "sfam" = "text:toupper(text:replace(text:replace(node:value(./CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*[node:pos(.)=0]), 'CRYPTO_ALGOFAM_', ''), '_', ''))"!][!//
[!//
  [!IF "$psrv = 'SIGNATUREVERIFY' and $pfam = 'RSA' and $pmod = 'RSASSAPSS'"!]
#ifndef CRYPTO_XVIX_XAIX_INC_ENABLED_[!"$psrv"!]_[!"$pfam"!]_[!"$pmod"!]_HASH_[!"$sfam"!]_NOTSET
#define CRYPTO_XVIX_XAIX_INC_ENABLED_[!"$psrv"!]_[!"$pfam"!]_[!"$pmod"!]_HASH_[!"$sfam"!]_NOTSET       STD_ON
#endif

  [!ENDIF!][!//
[!ENDLOOP!][!//
[!CALL "GetMaxResultSizeOfSecondary", "ctr" = "node:path(CryptoDriverObjects)", "psrv" = "'SIGNATURE_VERIFY'", "pfam" = "'CRYPTO_ALGOFAM_RSA'", "pmod"= "'CRYPTO_ALGOMODE_RSASSA_PSS'"!][!//
[!VAR "DgstResultSize" = "$HashResultSize"!][!//
/* !LINKSTO Crypto.Req.CPr/SIGNATUREVERIFY_RSA_RSASSAPSS/GENERAL/0002,1 */
#if    (defined CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_RSA_RSASSAPSS_HASHRESULTSIZE)
#error  CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_RSA_RSASSAPSS_HASHRESULTSIZE already defined
#endif
/** \brief  Macro indicating the length of the hash result in bytes. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_RSA_RSASSAPSS_HASHRESULTSIZE [!"$DgstResultSize"!]

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_INT_CPR_SIGNATUREVERIFY_RSA_RSASSAPSS_CFG_H */

/*==================[end of file]=================================================================*/

