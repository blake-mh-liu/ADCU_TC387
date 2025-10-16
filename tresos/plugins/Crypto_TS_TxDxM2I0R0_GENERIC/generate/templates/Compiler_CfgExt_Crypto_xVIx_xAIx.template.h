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

#if (!defined COMPILER_CFGEXT_CRYPTO_XVIX_XAIX_H)
#define COMPILER_CFGEXT_CRYPTO_XVIX_XAIX_H

/* This file is an user-specific file and will be delivered only as a template
 * which works together with all ACG-modules by EB.
 * The integrator needs to merge all Compiler_Cfg.h file of all module vendors.
 * Proposed process is specified in AUTOSAR_SWS_CompilerAbstraction
 * specification.
 */

/*==================[deviations]==================================================================*/

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/

/*------------------[memory and pointer class of a module]-------------------*/

#if (defined CRYPTO_xVIx_xAIx_CODE)
#error CRYPTO_xVIx_xAIx_CODE already defined
#endif
#define CRYPTO_xVIx_xAIx_CODE

#if (defined CRYPTO_xVIx_xAIx_APPL_DATA)
#error CRYPTO_xVIx_xAIx_APPL_DATA already defined
#endif
#define CRYPTO_xVIx_xAIx_APPL_DATA

#if (defined CRYPTO_xVIx_xAIx_APPL_CONST)
#error CRYPTO_xVIx_xAIx_APPL_CONST already defined
#endif
#define CRYPTO_xVIx_xAIx_APPL_CONST

#if (defined CRYPTO_xVIx_xAIx_CONST)
#error CRYPTO_xVIx_xAIx_CONST already defined
#endif
#define CRYPTO_xVIx_xAIx_CONST

#if (defined CRYPTO_xVIx_xAIx_VAR)
#error CRYPTO_xVIx_xAIx_VAR already defined
#endif
#define CRYPTO_xVIx_xAIx_VAR

#if (defined CRYPTO_xVIx_xAIx_APPL_CODE)
#error CRYPTO_xVIx_xAIx_APPL_CODE already defined
#endif
#define CRYPTO_xVIx_xAIx_APPL_CODE

#if (defined CRYPTO_xVIx_xAIx_VAR_CLEARED)
#error CRYPTO_xVIx_xAIx_VAR_CLEARED already defined
#endif
#define CRYPTO_xVIx_xAIx_VAR_CLEARED

#if (defined CRYPTO_xVIx_xAIx_VAR_POWER_ON_INIT)
#error CRYPTO_xVIx_xAIx_VAR_POWER_ON_INIT already defined
#endif
#define CRYPTO_xVIx_xAIx_VAR_POWER_ON_INIT

#if (defined CRYPTO_xVIx_xAIx_VAR_FAST)
#error CRYPTO_xVIx_xAIx_VAR_FAST already defined
#endif
#define CRYPTO_xVIx_xAIx_VAR_FAST

[!IF "num:i(0) < count(util:distinct(node:refs(util:distinct(node:refs(./CryptoKeys/CryptoKey/eb-list::*/CryptoKeyTypeRef))/CryptoKeyElementRef/eb-list::*))/CryptoKeyElementPersist[node:existsAndTrue(.)])"!][!//
#if (defined CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEYELEMENT_SETDATA_CODE)
#error CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEYELEMENT_SETDATA_CODE already defined
#endif
#define CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEYELEMENT_SETDATA_CODE

#if (defined CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEYELEMENT_SETDATA_APPL_DATA)
#error CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEYELEMENT_SETDATA_APPL_DATA already defined
#endif
#define CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEYELEMENT_SETDATA_APPL_DATA
[!ENDIF!][!//

[!IF "num:i(0) < count(util:distinct(node:refs(util:distinct(node:refs(./CryptoKeys/CryptoKey/eb-list::*/CryptoKeyTypeRef))/CryptoKeyElementRef/eb-list::*))/CryptoKeyElementPersist[node:existsAndTrue(.)])"!][!//
#if (defined CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEYELEMENT_GETDATA_CODE)
#error CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEYELEMENT_GETDATA_CODE already defined
#endif
#define CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEYELEMENT_GETDATA_CODE

#if (defined CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEYELEMENT_GETDATA_APPL_DATA)
#error CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEYELEMENT_GETDATA_APPL_DATA already defined
#endif
#define CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEYELEMENT_GETDATA_APPL_DATA
[!ENDIF!][!//

[!IF "num:i(0) < count(util:distinct(node:refs(util:distinct(node:refs(./CryptoKeys/CryptoKey/eb-list::*/CryptoKeyTypeRef))/CryptoKeyElementRef/eb-list::*))/CryptoKeyElementPersist[node:existsAndTrue(.)])"!][!//
#if (defined CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEY_SETVALID_CODE)
#error CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEY_SETVALID_CODE already defined
#endif
#define CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEY_SETVALID_CODE
[!ENDIF!][!//

[!IF "num:i(0) < count(util:distinct(node:refs(util:distinct(node:refs(./CryptoKeys/CryptoKey/eb-list::*/CryptoKeyTypeRef))/CryptoKeyElementRef/eb-list::*))/CryptoKeyElementPersist[node:existsAndTrue(.)])"!][!//
#if (defined CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEY_GETVALID_CODE)
#error CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEY_GETVALID_CODE already defined
#endif
#define CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEY_GETVALID_CODE

#if (defined CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEY_GETVALID_APPL_DATA)
#error CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEY_GETVALID_APPL_DATA already defined
#endif
#define CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEY_GETVALID_APPL_DATA
[!ENDIF!][!//
#endif /* if !defined( COMPILER_CFGEXT_CRYPTO_XVIX_XAIX_H ) */
/*==================[end of file]============================================*/
