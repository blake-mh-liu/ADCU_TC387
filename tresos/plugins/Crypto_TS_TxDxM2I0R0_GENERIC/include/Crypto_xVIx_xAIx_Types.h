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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Types.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_TYPES_H
#define CRYPTO_XVIX_XAIX_TYPES_H

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

#include <TSAutosar.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Types.h/0002,1 */

#include <Crypto_xVIx_xAIx_Version.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Types.h/0003,1 */

/*==================[macros]======================================================================*/

/* --- Service IDs ------------------------------------------------------------------------------ */

#if (defined CRYPTO_XVIX_XAIX_SID_INIT)
#error CRYPTO_XVIX_XAIX_SID_INIT is already defined
#endif
/** \brief  AUTOSAR API service ID for Crypto_xVIx_xAIx_Init. **/
#define CRYPTO_XVIX_XAIX_SID_INIT 0x00U

#if (defined CRYPTO_XVIX_XAIX_SID_GETVERSIONINFO)
#error CRYPTO_XVIX_XAIX_SID_GETVERSIONINFO is already defined
#endif
/** \brief  AUTOSAR API service ID for Crypto_xVIx_xAIx_GetVersionInfo. **/
#define CRYPTO_XVIX_XAIX_SID_GETVERSIONINFO 0x01U

#if (defined CRYPTO_XVIX_XAIX_SID_PROCESSJOB)
#error CRYPTO_XVIX_XAIX_SID_PROCESSJOB is already defined
#endif
/** \brief  AUTOSAR API service ID for Crypto_xVIx_xAIx_ProcessJob. **/
#define CRYPTO_XVIX_XAIX_SID_PROCESSJOB 0x03U

#if (defined CRYPTO_XVIX_XAIX_SID_CANCELJOB)
#error CRYPTO_XVIX_XAIX_SID_CANCELJOB is already defined
#endif
/** \brief  AUTOSAR API service ID for Crypto_xVIx_xAIx_CancelJob. **/
#define CRYPTO_XVIX_XAIX_SID_CANCELJOB 0x0EU

#if (defined CRYPTO_XVIX_XAIX_SID_KEYELEMENTSET)
#error CRYPTO_XVIX_XAIX_SID_KEYELEMENTSET is already defined
#endif
/** \brief  AUTOSAR API service ID for Crypto_xVIx_xAIx_KeyElementSet. **/
#define CRYPTO_XVIX_XAIX_SID_KEYELEMENTSET 0x04U

#if (defined CRYPTO_XVIX_XAIX_SID_KEYVALIDSET)
#error CRYPTO_XVIX_XAIX_SID_KEYVALIDSET is already defined
#endif
/** \brief  AUTOSAR API service ID for Crypto_xVIx_xAIx_KeyValidSet. **/
#define CRYPTO_XVIX_XAIX_SID_KEYVALIDSET 0x05U

#if (defined CRYPTO_XVIX_XAIX_SID_KEYSETINVALID)
#error CRYPTO_XVIX_XAIX_SID_KEYSETINVALID is already defined
#endif
/** \brief  AUTOSAR API service ID for Crypto_xVIx_xAIx_KeySetInvalid. **/
#define CRYPTO_XVIX_XAIX_SID_KEYSETINVALID 0x15U

#if (defined CRYPTO_XVIX_XAIX_SID_KEYGETSTATUS)
#error CRYPTO_XVIX_XAIX_SID_KEYGETSTATUS is already defined
#endif
/** \brief  AUTOSAR API service ID for Crypto_xVIx_xAIx_KeyGetStatus. **/
#define CRYPTO_XVIX_XAIX_SID_KEYGETSTATUS 0x14U

#if (defined CRYPTO_XVIX_XAIX_SID_KEYELEMENTGET)
#error CRYPTO_XVIX_XAIX_SID_KEYELEMENTGET is already defined
#endif
/** \brief  AUTOSAR API service ID for Crypto_xVIx_xAIx_KeyElementGet. **/
#define CRYPTO_XVIX_XAIX_SID_KEYELEMENTGET 0x06U

#if (defined CRYPTO_XVIX_XAIX_SID_KEYELEMENTCOPY)
#error CRYPTO_XVIX_XAIX_SID_KEYELEMENTCOPY is already defined
#endif
/** \brief  AUTOSAR API service ID for Crypto_xVIx_xAIx_KeyElementCopy. **/
#define CRYPTO_XVIX_XAIX_SID_KEYELEMENTCOPY 0x0FU

#if (defined CRYPTO_XVIX_XAIX_SID_KEYCOPY)
#error CRYPTO_XVIX_XAIX_SID_KEYCOPY is already defined
#endif
/** \brief  AUTOSAR API service ID for Crypto_xVIx_xAIx_KeyCopy. **/
#define CRYPTO_XVIX_XAIX_SID_KEYCOPY 0x10U

#if (defined CRYPTO_XVIX_XAIX_SID_KEYELEMENTIDSGET)
#error CRYPTO_XVIX_XAIX_SID_KEYELEMENTIDSGET is already defined
#endif
/** \brief  AUTOSAR API service ID for Crypto_xVIx_xAIx_KeyElementIdsGet. **/
#define CRYPTO_XVIX_XAIX_SID_KEYELEMENTIDSGET 0x11U

#if (defined CRYPTO_XVIX_XAIX_SID_RANDOMSEED)
#error CRYPTO_XVIX_XAIX_SID_RANDOMSEED is already defined
#endif
/** \brief  AUTOSAR API service ID for Crypto_xVIx_xAIx_RandomSeed. **/
#define CRYPTO_XVIX_XAIX_SID_RANDOMSEED 0x0DU

#if (defined CRYPTO_XVIX_XAIX_SID_KEYGENERATE)
#error CRYPTO_XVIX_XAIX_SID_KEYGENERATE is already defined
#endif
/** \brief  AUTOSAR API service ID for Crypto_xVIx_xAIx_KeyGenerate. **/
#define CRYPTO_XVIX_XAIX_SID_KEYGENERATE 0x07U

#if (defined CRYPTO_XVIX_XAIX_SID_KEYDERIVE)
#error CRYPTO_XVIX_XAIX_SID_KEYDERIVE is already defined
#endif
/** \brief  AUTOSAR API service ID for Crypto_xVIx_xAIx_KeyDerive. **/
#define CRYPTO_XVIX_XAIX_SID_KEYDERIVE 0x08U

#if (defined CRYPTO_XVIX_XAIX_SID_KEYEXCHANGECALCPUBVAL)
#error CRYPTO_XVIX_XAIX_SID_KEYEXCHANGECALCPUBVAL is already defined
#endif
/** \brief  AUTOSAR API service ID for Crypto_xVIx_xAIx_KeyExchangeCalcPubVal. **/
#define CRYPTO_XVIX_XAIX_SID_KEYEXCHANGECALCPUBVAL 0x09U

#if (defined CRYPTO_XVIX_XAIX_SID_KEYEXCHANGECALCSECRET)
#error CRYPTO_XVIX_XAIX_SID_KEYEXCHANGECALCSECRET is already defined
#endif
/** \brief  AUTOSAR API service ID for Crypto_xVIx_xAIx_KeyExchangeCalcSecret. **/
#define CRYPTO_XVIX_XAIX_SID_KEYEXCHANGECALCSECRET 0x0AU

#if (defined CRYPTO_XVIX_XAIX_SID_CERTIFICATEPARSE)
#error CRYPTO_XVIX_XAIX_SID_CERTIFICATEPARSE is already defined
#endif
/** \brief  AUTOSAR API service ID for Crypto_xVIx_xAIx_CertificateParse. **/
#define CRYPTO_XVIX_XAIX_SID_CERTIFICATEPARSE 0x0BU

#if (defined CRYPTO_XVIX_XAIX_SID_CERTIFICATEVERIFY)
#error CRYPTO_XVIX_XAIX_SID_CERTIFICATEVERIFY is already defined
#endif
/** \brief  AUTOSAR API service ID for Crypto_CertificateVerify. **/
#define CRYPTO_XVIX_XAIX_SID_CERTIFICATEVERIFY 0x12U

#if (defined CRYPTO_XVIX_XAIX_SID_KEYELEMENTCOPYPARTIAL)
#error CRYPTO_XVIX_XAIX_SID_KEYELEMENTCOPYPARTIAL is already defined
#endif
/** \brief  AUTOSAR API service ID for Crypto_KeyElementCopyPartial. **/
#define CRYPTO_XVIX_XAIX_SID_KEYELEMENTCOPYPARTIAL 0x13U

#if (defined CRYPTO_XVIX_XAIX_SID_MAINFUNCTION)
#error CRYPTO_XVIX_XAIX_SID_MAINFUNCTION is already defined
#endif
/** \brief  AUTOSAR API service ID for Crypto_xVIx_xAIx_MainFunction. **/
#define CRYPTO_XVIX_XAIX_SID_MAINFUNCTION 0x0CU

/* --- Development error codes ------------------------------------------------------------------ */

/* !LINKSTO Crypto.Asr.SWS_Crypto_00040_43x,1 */

#if (defined CRYPTO_XVIX_XAIX_E_UNINIT)
#error CRYPTO_XVIX_XAIX_E_UNINIT is already defined
#endif
/** \brief  Crypto driver is not initialized. **/
#define CRYPTO_XVIX_XAIX_E_UNINIT 0x00U

#if (defined CRYPTO_XVIX_XAIX_E_INIT_FAILED)
#error CRYPTO_XVIX_XAIX_E_INIT_FAILED is already defined
#endif
/** \brief  Initialization of crypto driver failed. **/
#define CRYPTO_XVIX_XAIX_E_INIT_FAILED 0x01U

#if (defined CRYPTO_XVIX_XAIX_E_PARAM_POINTER)
#error CRYPTO_XVIX_XAIX_E_PARAM_POINTER is already defined
#endif
/** \brief  Pointer parameter has an invalid value. **/
#define CRYPTO_XVIX_XAIX_E_PARAM_POINTER 0x02U

#if (defined CRYPTO_XVIX_XAIX_E_PARAM_HANDLE)
#error CRYPTO_XVIX_XAIX_E_PARAM_HANDLE is already defined
#endif
/** \brief Handle parameter has an invalid value. **/
#define CRYPTO_XVIX_XAIX_E_PARAM_HANDLE 0x04U

#if (defined CRYPTO_XVIX_XAIX_E_PARAM_VALUE)
#error CRYPTO_XVIX_XAIX_E_PARAM_VALUE is already defined
#endif
/** \brief  Value parameter has an invalid value. **/
#define CRYPTO_XVIX_XAIX_E_PARAM_VALUE 0x05U

/* --- Runtime error codes ---------------------------------------------------------------------- */

/* !LINKSTO Crypto.Asr.SWS_Crypto_00194_43x,1 */

#if (defined CRYPTO_XVIX_XAIX_E_RE_SMALL_BUFFER)
#error CRYPTO_XVIX_XAIX_E_RE_SMALL_BUFFER is already defined
#endif /* #if (defined CRYPTO_XVIX_XAIX_E_RE_SMALL_BUFFER) */
/** \brief  Buffer is too small for operation. **/
#define CRYPTO_XVIX_XAIX_E_RE_SMALL_BUFFER 0x00U

#if (defined CRYPTO_XVIX_XAIX_E_RE_KEY_NOT_AVAILABLE)
#error CRYPTO_XVIX_XAIX_E_RE_KEY_NOT_AVAILABLE is already defined
#endif /* #if (defined CRYPTO_XVIX_XAIX_E_RE_KEY_NOT_AVAILABLE) */
/** \brief  BRequested key is not available. **/
#define CRYPTO_XVIX_XAIX_E_RE_KEY_NOT_AVAILABLE 0x01U

#if (defined CRYPTO_XVIX_XAIX_E_RE_KEY_READ_FAIL)
#error CRYPTO_XVIX_XAIX_E_RE_KEY_READ_FAIL is already defined
#endif /* #if (defined CRYPTO_XVIX_XAIX_E_RE_KEY_READ_FAIL) */
/** \brief  Key cannot be read. **/
#define CRYPTO_XVIX_XAIX_E_RE_KEY_READ_FAIL 0x02U

#if (defined CRYPTO_XVIX_XAIX_E_RE_ENTROPY_EXHAUSTED)
#error CRYPTO_XVIX_XAIX_E_RE_ENTROPY_EXHAUSTED is already defined
#endif /* #if (defined CRYPTO_XVIX_XAIX_E_RE_ENTROPY_EXHAUSTED) */
/** \brief  Entropy is too low. **/
#define CRYPTO_XVIX_XAIX_E_RE_ENTROPY_EXHAUSTED 0x03U

/* --- API versions ----------------------------------------------------------------------------- */

/* !LINKSTO Crypto.Req.Api/CRYPTO_API_VERSION_430/0001,2 */
#if !(defined CRYPTO_API_VERSION_430)
/** \brief  Macro representing the value for Api version CRYPTO_API_VERSION_430 **/
#define  CRYPTO_API_VERSION_430  0x00U
#endif /* #if !(defined CRYPTO_API_VERSION_430) */

/* !LINKSTO Crypto.Req.Api/CRYPTO_API_VERSION_431/0001,2 */
#if !(defined CRYPTO_API_VERSION_431)
/** \brief  Macro representing the value for Api version CRYPTO_API_VERSION_431 **/
#define  CRYPTO_API_VERSION_431  0x01U
#endif /* #if !(defined CRYPTO_API_VERSION_431) */

/* !LINKSTO Crypto.Req.Api/CRYPTO_API_VERSION_EB/0001,2 */
#if !(defined CRYPTO_API_VERSION_EB)
/** \brief  Macro representing the value for Api version CRYPTO_API_VERSION_EB **/
#define  CRYPTO_API_VERSION_EB  0x02U
#endif /* #if !(defined CRYPTO_API_VERSION_EB) */

/* --- Custom algorithm services ---------------------------------------------------------------- */

/* !LINKSTO Crypto.Req.Api/CRYPTO_ALGOSRV_RANDOMSEED/0001,1 */
#if !(defined CRYPTO_RANDOMSEED)
#define  CRYPTO_RANDOMSEED  0x0CU
#endif /* #if !(defined CRYPTO_RANDOMSEED) */

/* !LINKSTO Crypto.Req.Api/CRYPTO_ALGOSRV_KEYGENERATE/0001,1 */
#if !(defined CRYPTO_KEYGENERATE)
#define  CRYPTO_KEYGENERATE  0x0DU
#endif /* #if !(defined CRYPTO_KEYGENERATE) */

/* !LINKSTO Crypto.Req.Api/CRYPTO_ALGOSRV_KEYDERIVE/0001,1 */
#if !(defined CRYPTO_KEYDERIVE)
#define  CRYPTO_KEYDERIVE  0x0EU
#endif /* #if !(defined CRYPTO_KEYDERIVE) */

/* !LINKSTO Crypto.Req.Api/CRYPTO_ALGOSRV_KEYEXCHANGECALCPUBVAL/0001,1 */
#if !(defined CRYPTO_KEYEXCHANGECALCPUBVAL)
#define  CRYPTO_KEYEXCHANGECALCPUBVAL  0x0FU
#endif /* #if !(defined CRYPTO_KEYEXCHANGECALCPUBVAL) */

/* !LINKSTO Crypto.Req.Api/CRYPTO_ALGOSRV_KEYEXCHANGECALCSECRET/0001,1 */
#if !(defined CRYPTO_KEYEXCHANGECALCSECRET)
#define  CRYPTO_KEYEXCHANGECALCSECRET  0x10U
#endif /* #if !(defined CRYPTO_KEYEXCHANGECALCSECRET) */
/* --- Custom algorithm families ---------------------------------------------------------------- */

/* !LINKSTO Crypto.Req.Api/CRYPTO_ALGOFAM_PADDING_PKCS7/0001,1 */
#if !(defined CRYPTO_ALGOFAM_PADDING_PKCS7)
#define CRYPTO_ALGOFAM_PADDING_PKCS7  0x22U
#endif /* #if !(defined CRYPTO_ALGOFAM_PADDING_PKCS7) */

/* !LINKSTO Crypto.Req.Api/CRYPTO_ALGOFAM_ECDSA/0001,1 */
#if !(defined CRYPTO_ALGOFAM_ECDSA)
#define  CRYPTO_ALGOFAM_ECDSA  0x2CU
#endif /* #if !(defined CRYPTO_ALGOFAM_ECDSA) */

/* !LINKSTO Crypto.Req.Api/CRYPTO_ALGOFAM_X25519/0001,1 */
#if !(defined CRYPTO_ALGOFAM_X25519)
#define  CRYPTO_ALGOFAM_X25519  0x2EU
#endif /* #if !(defined CRYPTO_ALGOFAM_X25519) */

/* !LINKSTO Crypto.Req.Api/CRYPTO_ALGOFAM_ED25519PH/0001,1 */
#if !(defined CRYPTO_ALGOFAM_ED25519PH)
#define  CRYPTO_ALGOFAM_ED25519PH  0xA1U
#endif /* #if !(defined CRYPTO_ALGOFAM_ED25519PH) */

/* !LINKSTO Crypto.Req.Api/CRYPTO_ALGOFAM_PADDING_TLS12/0001,1 */
#if !(defined CRYPTO_ALGOFAM_PADDING_TLS12)
#define CRYPTO_ALGOFAM_PADDING_TLS12  0xA2U
#endif /* #if !(defined CRYPTO_ALGOFAM_PADDING_TLS12) */

/* !LINKSTO Crypto.Req.Api/CRYPTO_ALGOFAM_LZSS/0001,1 */
#if !(defined CRYPTO_ALGOFAM_LZSS)
#define  CRYPTO_ALGOFAM_LZSS  0xA3U
#endif /* #if !(defined CRYPTO_ALGOFAM_LZSS) */

/* --- Custom algorithm modes ------------------------------------------------------------------- */

/* !LINKSTO Crypto.Req.Api/CRYPTO_ALGOMODE_STREAMBYTE/0001,1 */
#if !(defined CRYPTO_ALGOMODE_STREAMBYTE)
#define  CRYPTO_ALGOMODE_STREAMBYTE  0xA3U
#endif /* #if !(defined CRYPTO_ALGOMODE_STREAMBYTE) */

/* !LINKSTO Crypto.Req.Api/CRYPTO_ALGOMODE_STREAMBIT/0001,1 */
#if !(defined CRYPTO_ALGOMODE_STREAMBIT)
#define  CRYPTO_ALGOMODE_STREAMBIT  0xA5U
#endif /* #if !(defined CRYPTO_ALGOMODE_STREAMBIT) */

/* !LINKSTO Crypto.Req.Api/CRYPTO_ALGOMODE_CCM/0001,1 */
#if !(defined CRYPTO_ALGOMODE_CCM)
#define  CRYPTO_ALGOMODE_CCM  0xA4U
#endif /* #if !(defined CRYPTO_ALGOMODE_CCM) */

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_TYPES_H */

/*==================[end of file]=================================================================*/

