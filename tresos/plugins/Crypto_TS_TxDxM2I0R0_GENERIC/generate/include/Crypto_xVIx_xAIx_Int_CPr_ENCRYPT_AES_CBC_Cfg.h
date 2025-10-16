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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_CPr_ENCRYPT_AES_CBC_Cfg.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_CBC_CFG_H
#define CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_CBC_CFG_H

[!AUTOSPACING!]
[!/* ====================================================================================== */!][!//
[!INCLUDE "Crypto_xVIx_xAIx_Macros.m"!]
[!/* ====================================================================================== */!][!//
[!//
/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

/*==================[macros]======================================================================*/

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_CBC/0001,1 */
#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_CBC)
#error CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_CBC is already defined
#endif
/** \brief  Macro representing whether the ENCRYPT_AES_CBC
 **         primitive is directly or indirectly assigned to a Crypto Driver Object.
 **/
[!CALL "GetPrimitivesPoolList", "ctr" = "node:path(CryptoDriverObjects)"!][!//
[!IF "contains($PrimitivesPoolListShrt, 'ENCRYPT_AES_CBC') and lic:feature(Crypto:GetCprFeatureName('ENCRYPT_AES_CBC', 'EB_SEC_CPR'))"!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_CBC STD_ON
[!ELSE!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_CPR_ENCRYPT_AES_CBC STD_OFF
[!ENDIF!][!//

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_INT_CPR_ENCRYPT_AES_CBC_CFG_H */

/*==================[end of file]=================================================================*/

