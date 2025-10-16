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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Cfg.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_CFG_H
#define CRYPTO_XVIX_XAIX_CFG_H
[!AUTOSPACING!][!//
[!/*========================================================================================*/!][!//
[!/*========================================================================================*/!][!//
[!//

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

/*==================[macros]======================================================================*/

#if (defined CRYPTO_XVIX_XAIX_API_VERSION)
#error CRYPTO_XVIX_XAIX_API_VERSION is already defined
#endif
/** \brief  Macro indicating the API version of the Crypto driver **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_API_VERSION,1 */
#define CRYPTO_XVIX_XAIX_API_VERSION [!"node:value(CryptoEbGeneral/CryptoEbMisc/CryptoEbAutosarApiVersion)"!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT)
#error CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT is already defined
#endif
/** \brief  Macro indicating whether the development error detection shall be enabled **/
[!IF "(node:existsAndTrue(CryptoGeneral/CryptoDevErrorDetect))"!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT STD_ON
[!ELSE!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT STD_OFF
[!ENDIF!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_DETRUNTIMECHECKS)
#error CRYPTO_XVIX_XAIX_API_ENABLED_DETRUNTIMECHECKS is already defined
#endif
/** \brief  Macro indicating whether the runtime error detection shall be enabled **/
[!IF "(node:existsAndTrue(CryptoGeneral/CryptoDetRuntimeChecks))"!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_DETRUNTIMECHECKS STD_ON
[!ELSE!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_DETRUNTIMECHECKS STD_OFF
[!ENDIF!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_VERSIONINFO)
#error CRYPTO_XVIX_XAIX_API_ENABLED_VERSIONINFO is already defined
#endif
/** \brief  Macro indicating whether the version info API shall be enabled **/
[!IF "(node:existsAndTrue(CryptoGeneral/CryptoVersionInfoApi))"!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_VERSIONINFO STD_ON
[!ELSE!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_VERSIONINFO STD_OFF
[!ENDIF!]

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_KEYSETINVALID)
#error CRYPTO_XVIX_XAIX_API_ENABLED_KEYSETINVALID is already defined
#endif
/** \brief Configuration parameter CryptoEbEnhancementApiKeySetInvalid */
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_API_ENABLED_KEYSETINVALID,1 */
[!IF "(node:existsAndTrue(CryptoEbGeneral/CryptoEbMisc/CryptoEbEnhancementApiKeySetInvalid))"!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_KEYSETINVALID STD_ON
[!ELSE!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_KEYSETINVALID STD_OFF
[!ENDIF!][!//

#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_KEYGETSTATUS)
#error CRYPTO_XVIX_XAIX_API_ENABLED_KEYGETSTATUS is already defined
#endif
/** \brief Configuration parameter CryptoEbEnhancementApiKeyGetStatus */
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_API_ENABLED_KEYGETSTATUS,1 */
[!IF "(node:existsAndTrue(CryptoEbGeneral/CryptoEbMisc/CryptoEbEnhancementApiKeyGetStatus))"!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_KEYGETSTATUS STD_ON
[!ELSE!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_KEYGETSTATUS STD_OFF
[!ENDIF!][!//

#if (defined CRYPTO_XVIX_XAIX_KEYMNGMT_ENABLED)
#error CRYPTO_XVIX_XAIX_KEYMNGMT_ENABLED is already defined
#endif
/** \brief  Macro indicating whether the key management shall be enabled **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_KEYMNGMT_ENABLED,1 */
[!IF "node:exists(CryptoKeys)"!]
#define CRYPTO_XVIX_XAIX_KEYMNGMT_ENABLED STD_ON
[!ELSE!]
#define CRYPTO_XVIX_XAIX_KEYMNGMT_ENABLED STD_OFF
[!ENDIF!]

#if (defined CRYPTO_XVIX_XAIX_CRYPTO_MAIN_FUNCTION_EXISTS)
#error CRYPTO_XVIX_XAIX_CRYPTO_MAIN_FUNCTION_EXISTS is already defined
#endif
/** \brief Macro indicating if the MainFunction shall be scheduled */
[!IF "node:exists(CryptoGeneral/CryptoMainFunctionPeriod)"!]
#define CRYPTO_XVIX_XAIX_CRYPTO_MAIN_FUNCTION_EXISTS STD_ON
[!ELSE!]
#define CRYPTO_XVIX_XAIX_CRYPTO_MAIN_FUNCTION_EXISTS STD_OFF
[!ENDIF!]

#if (defined CRYPTO_XVIX_XAIX_INSTANCE_ID)
#error CRYPTO_XVIX_XAIX_INSTANCE_ID is already defined
#endif
/** \brief  Macro indicating the Instance ID of the crypto driver. **/
#define CRYPTO_XVIX_XAIX_INSTANCE_ID [!"num:i(node:value(CryptoGeneral/CryptoInstanceId))"!]U

[!LOOP "util:distinct(node:order(CryptoDriverObjects/CryptoDriverObject/eb-list::*,'node:value(CryptoDriverObjectId)'))"!][!//
#if (defined Crypto_xVIx_xAIxConf_CryptoDriverObject_[!"node:name(.)"!])
#error Crypto_xVIx_xAIxConf_CryptoDriverObject_[!"node:name(.)"!] is already defined
#endif
/** \brief Identifier of crypto driver object [!"node:name(.)"!] */
#define Crypto_xVIx_xAIxConf_CryptoDriverObject_[!"node:name(.)"!] [!"node:value(CryptoDriverObjectId)"!]U
[!ENDLOOP!][!//
[!//
[!LOOP "util:distinct(node:order(CryptoKeys/CryptoKey/eb-list::*, 'node:value(CryptoKeyId)'))"!]

#if (defined Crypto_xVIx_xAIxConf_CryptoKey_[!"node:name(.)"!])
#error Crypto_xVIx_xAIxConf_CryptoKey_[!"node:name(.)"!] is already defined
#endif
 /** \brief Identifier of crypto key [!"node:name(.)"!] */
#define Crypto_xVIx_xAIxConf_CryptoKey_[!"node:name(.)"!] [!"node:value(CryptoKeyId)"!]U
[!ENDLOOP!][!//
[!LOOP "util:distinct(node:order(CryptoKeyElements/CryptoKeyElement/eb-list::*, 'node:value(CryptoKeyElementId)'))"!]

#if (defined Crypto_xVIx_xAIxConf_CryptoKeyElement_[!"node:name(.)"!])
#error Crypto_xVIx_xAIxConf_CryptoKeyElement_[!"node:name(.)"!] is already defined
#endif
 /** \brief Identifier of crypto key element [!"node:name(.)"!] */
#define Crypto_xVIx_xAIxConf_CryptoKeyElement_[!"node:name(.)"!] [!"node:value(CryptoKeyElementId)"!]U
[!ENDLOOP!][!//

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_CFG_H */

/*==================[end of file]=================================================================*/

