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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_ENCRYPT_RSA_RSAESOAEP_Cfg.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_RSA_RSAESOAEP_CFG_H
#define CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_RSA_RSAESOAEP_CFG_H

[!AUTOSPACING!]
[!/* ====================================================================================== */!][!//
[!INCLUDE "Crypto_xVIx_xAIx_Macros.m"!]
[!/* ====================================================================================== */!][!//
[!//
/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

/*==================[macros]======================================================================*/

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_RSA_RSAESOAEP/0001,1 */
#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_RSA_RSAESOAEP)
#error CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_RSA_RSAESOAEP is already defined
#endif
/** \brief  Macro representing whether the ENCRYPT_RSA_RSAESOAEP
 **         primitive is directly or indirectly assigned to a Crypto Driver Object.
 **/
[!CALL "GetPrimitivesPoolList", "ctr" = "node:path(CryptoDriverObjects)"!][!//
[!IF "contains($PrimitivesPoolListShrt, 'ENCRYPT_RSA_RSAESOAEP') and lic:feature(Crypto:GetCprFeatureName('ENCRYPT_RSA_RSAESOAEP', 'EB_SEC_CPR'))"!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_RSA_RSAESOAEP STD_ON
[!ELSE!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_RSA_RSAESOAEP STD_OFF
[!ENDIF!][!//

[!CALL "GetMaxResultSizeOfSecondary", "ctr" = "node:path(CryptoDriverObjects)", "psrv" = "'ENCRYPT'", "pfam" = "'CRYPTO_ALGOFAM_RSA'", "pmod"= "'CRYPTO_ALGOMODE_RSAES_OAEP'"!][!//
[!VAR "DgstResultSize" = "$HashResultSize"!][!//
/* !LINKSTO Crypto.Req.CPr/ENCRYPT_RSA_RSAESOAEP/GENERAL/0002,1 */
#if    (defined CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_RSA_RSAESOAEP_HASHRESULTSIZE)
#error  CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_RSA_RSAESOAEP already defined
#endif
/** \brief  Macro indicating the length of the hash result in bytes. **/
#define CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_RSA_RSAESOAEP_HASHRESULTSIZE [!"$DgstResultSize"!]

#if (defined CRYPTO_XVIX_XAIX_ENCRYPT_RSA_RSAESOAEP_MAX_RSA_KEY_SIZE)
#error CRYPTO_XVIX_XAIX_MAX_ENCRYPT_RSA_RSAESOAEP_RSA_KEY_SIZE is already defined
#endif
/** \brief  macro identifying the max RSA key size **/
[!VAR "MaxRSAKeySize" = "num:i(0)"!][!//
[!LOOP "util:distinct(node:order(node:filter(util:distinct(node:refs(util:distinct(node:refs(CryptoKeys/CryptoKey/eb-list::*/CryptoKeyTypeRef))/CryptoKeyElementRef/eb-list::*)), '1 = ./CryptoKeyElementId')))"!]
  [!IF "'CRYPTO_KE_FORMAT_BIN_RSA_PUBLICKEY' = ./CryptoKeyElementFormat and ./CryptoKeyElementSize > number($MaxRSAKeySize)"!]
    [!VAR "MaxRSAKeySize" = "./CryptoKeyElementSize"!]
  [!ENDIF!]
[!ENDLOOP!]
#define CRYPTO_XVIX_XAIX_ENCRYPT_RSA_RSAESOAEP_MAX_RSA_KEY_SIZE [!"$MaxRSAKeySize"!]U

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_RSA_RSAESOAEP_CFG_H */

/*==================[end of file]=================================================================*/

