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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_HASH_SHA3256_NOTSET_Cfg.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA3256_NOTSET_CFG_H
#define CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA3256_NOTSET_CFG_H

[!AUTOSPACING!]
[!/* ====================================================================================== */!][!//
[!INCLUDE "Crypto_xVIx_xAIx_Macros.m"!]
[!/* ====================================================================================== */!][!//
[!//
/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

/*==================[macros]======================================================================*/

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3256_NOTSET/0001,1 */
#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3256_NOTSET)
#error CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3256_NOTSET is already defined
#endif
/** \brief  Macro representing whether the HASH_SHA3256_NOTSET
 **         primitive is directly or indirectly assigned to a Crypto Driver Object.
 **/
[!CALL "GetPrimitivesPoolList", "ctr" = "node:path(CryptoDriverObjects)"!][!//
[!IF "contains($PrimitivesPoolListShrt, 'HASH_SHA3256_NOTSET') and lic:feature(Crypto:GetCprFeatureName('HASH_SHA3256_NOTSET', 'EB_SEC_CPR'))"!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3256_NOTSET STD_ON
[!ELSE!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_CPR_HASH_SHA3256_NOTSET STD_OFF
[!ENDIF!][!//

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_INT_CPR_HASH_SHA3256_NOTSET_CFG_H */

/*==================[end of file]=================================================================*/

