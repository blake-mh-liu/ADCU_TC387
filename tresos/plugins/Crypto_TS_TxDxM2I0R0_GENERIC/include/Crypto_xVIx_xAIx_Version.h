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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Version.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_VERSION_H
#define CRYPTO_XVIX_XAIX_VERSION_H

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

/*==================[macros]======================================================================*/

/* AUTOSAR vendor identification */
#if (defined CRYPTO_XVIX_XAIX_VENDOR_ID)
#error CRYPTO_XVIX_XAIX_VENDOR_ID is already defined
#endif
/** \brief  AUTOSAR vendor identification: Elektrobit Automotive GmbH. **/
#define CRYPTO_XVIX_XAIX_VENDOR_ID 1U

/* AUTOSAR module identification */

#if (defined CRYPTO_XVIX_XAIX_MODULE_ID)
#error CRYPTO_XVIX_XAIX_MODULE_ID is already defined
#endif
/** \brief  AUTOSAR module identification. **/
#define CRYPTO_XVIX_XAIX_MODULE_ID 114U

/* AUTOSAR specification version identification */

#if (defined CRYPTO_XVIX_XAIX_AR_MAJOR_VERSION)
#error CRYPTO_XVIX_XAIX_AR_MAJOR_VERSION is already defined
#endif
/** \brief  AUTOSAR specification major version. **/
#define CRYPTO_XVIX_XAIX_AR_MAJOR_VERSION 4U

#if (defined CRYPTO_XVIX_XAIX_AR_MINOR_VERSION)
#error CRYPTO_XVIX_XAIX_AR_MINOR_VERSION is already defined
#endif
/** \brief  AUTOSAR specification minor version. **/
#define CRYPTO_XVIX_XAIX_AR_MINOR_VERSION 3U

#if (defined CRYPTO_XVIX_XAIX_AR_PATCH_VERSION)
#error CRYPTO_XVIX_XAIX_AR_PATCH_VERSION is already defined
#endif
/** \brief  AUTOSAR specification patch version. **/
#define CRYPTO_XVIX_XAIX_AR_PATCH_VERSION 0U

/* AUTOSAR module version identification */

#if (defined CRYPTO_XVIX_XAIX_SW_MAJOR_VERSION)
#error CRYPTO_XVIX_XAIX_SW_MAJOR_VERSION is already defined
#endif
/** \brief  AUTOSAR module major version. **/
#define CRYPTO_XVIX_XAIX_SW_MAJOR_VERSION 2U

#if (defined CRYPTO_XVIX_XAIX_SW_MINOR_VERSION)
#error CRYPTO_XVIX_XAIX_SW_MINOR_VERSION is already defined
#endif
/** \brief  AUTOSAR module minor version. **/
#define CRYPTO_XVIX_XAIX_SW_MINOR_VERSION 0U

#if (defined CRYPTO_XVIX_XAIX_SW_PATCH_VERSION)
#error CRYPTO_XVIX_XAIX_SW_PATCH_VERSION is already defined
#endif
/** \brief  AUTOSAR module patch version. **/
#define CRYPTO_XVIX_XAIX_SW_PATCH_VERSION 39U

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_VERSION_H */

/*==================[end of file]=================================================================*/

