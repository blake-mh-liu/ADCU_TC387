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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KMn_RANDOMSEED_AES_CTRDRBG_Cfg.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_INT_KMN_RANDOMSEED_AES_CTRDRBG_CFG_H
#define CRYPTO_XVIX_XAIX_INT_KMN_RANDOMSEED_AES_CTRDRBG_CFG_H

[!AUTOSPACING!]
[!/* ====================================================================================== */!][!//
[!//
/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

/*==================[macros]======================================================================*/

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG/0001,1 */
#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG)
#error CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG is already defined
#endif
/** \brief  Macro representing whether the RANDOMSEED_AES_CTRDRBG operation is configured to be used.
 **/
[!IF "node:exists(./CryptoKeys) and node:containsValue(CryptoEbGeneral/CryptoEbMisc/CryptoEbKeyManagementAlgorithm/eb-list::*, 'CRYPTO_KMN_RANDOMSEED_AES_CTRDRBG')"!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG STD_ON
[!ELSE!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_KMN_RANDOMSEED_AES_CTRDRBG STD_OFF
[!ENDIF!][!//

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_INT_KMN_RANDOMSEED_AES_CTRDRBG_CFG_H */

/*==================[end of file]=================================================================*/

