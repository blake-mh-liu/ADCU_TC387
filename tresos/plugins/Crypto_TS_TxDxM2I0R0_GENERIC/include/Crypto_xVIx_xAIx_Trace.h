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

#ifndef CRYPTO_XVIX_XAIX_TRACE_H
#define CRYPTO_XVIX_XAIX_TRACE_H

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

#include <Std_Types.h>

/* Check if BASE_DBG_ENABLE is defined and set to STD_ON.
 * If so, include Base_Dbg.h which includes a custom header file */
#if (defined BASE_DBG_ENABLE)
#if (BASE_DBG_ENABLE == STD_ON)

#include <Base_Dbg.h>

#endif
#endif

/*==================[macros]======================================================================*/

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INIT_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_Init()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_INIT_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INIT_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_Init()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_INIT_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_GETVERSIONINFO_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_GetVersionInfo()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_GETVERSIONINFO_ENTRY(versioninfo)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_GETVERSIONINFO_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_GetVersionInfo()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_GETVERSIONINFO_EXIT(versioninfo)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_PROCESSJOB_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_ProcessJob()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_PROCESSJOB_ENTRY(objectId,job)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_PROCESSJOB_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_ProcessJob()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_PROCESSJOB_EXIT(Retval,objectId,job)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_CANCELJOB_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_CancelJob()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_CANCELJOB_ENTRY(objectId,job)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_CANCELJOB_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_CancelJob()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_CANCELJOB_EXIT(Retval,objectId,job)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_MAINFUNCTION_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_MainFunction()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_MAINFUNCTION_ENTRY()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_MAINFUNCTION_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_MainFunction()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_MAINFUNCTION_EXIT()
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_KEYELEMENTSET_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_KeyElementSet()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_KEYELEMENTSET_ENTRY(cryptoKeyId,keyElementId,keyPtr,keyLength)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_KEYELEMENTSET_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_KeyElementSet()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_KEYELEMENTSET_EXIT(Retval,cryptoKeyId,keyElementId,keyPtr,keyLength)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_KEYSETVALID_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_KeySetValid()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_KEYSETVALID_ENTRY(cryptoKeyId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_KEYSETVALID_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_KeySetValid()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_KEYSETVALID_EXIT(Retval,cryptoKeyId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_KEYSETINVALID_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_KeySetInvalid()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_KEYSETINVALID_ENTRY(cryptoKeyId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_KEYSETINVALID_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_KeySetInvalid()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_KEYSETINVALID_EXIT(Retval,cryptoKeyId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_KEYGETSTATUS_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_KeyGetStatus()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_KEYGETSTATUS_ENTRY(cryptoKeyId,keyStatusPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_KEYGETSTATUS_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_KeyGetStatus()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_KEYGETSTATUS_EXIT(Retval,cryptoKeyId,keyStatusPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_KEYELEMENTGET_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_KeyElementGet()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_KEYELEMENTGET_ENTRY(cryptoKeyId,keyElementId,resultPtr,resultLengthPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_KEYELEMENTGET_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_KeyElementGet()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_KEYELEMENTGET_EXIT(Retval,cryptoKeyId,keyElementId,resultPtr,resultLengthPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_KEYELEMENTCOPY_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_KeyElementCopy()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_KEYELEMENTCOPY_ENTRY(cryptoKeyId,keyElementId,targetCryptoKeyId,targetKeyElementId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_KEYELEMENTCOPY_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_KeyElementCopy()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_KEYELEMENTCOPY_EXIT(Retval,cryptoKeyId,keyElementId,targetCryptoKeyId,targetKeyElementId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_KEYCOPY_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_KeyCopy()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_KEYCOPY_ENTRY(cryptoKeyId,targetCryptoKeyId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_KEYCOPY_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_KeyCopy()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_KEYCOPY_EXIT(Retval,cryptoKeyId,targetCryptoKeyId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_KEYELEMENTIDSGET_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_KeyElementIdsGet()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_KEYELEMENTIDSGET_ENTRY(cryptoKeyId,keyElementIdsPtr,keyElementIdsLengthPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_KEYELEMENTIDSGET_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_KeyElementIdsGet()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_KEYELEMENTIDSGET_EXIT(Retval,cryptoKeyId,keyElementIdsPtr,keyElementIdsLengthPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_RANDOMSEED_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_RandomSeed()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_RANDOMSEED_ENTRY(cryptoKeyId,seedPtr,seedLength)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_RANDOMSEED_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_RandomSeed()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_RANDOMSEED_EXIT(Retval,cryptoKeyId,seedPtr,seedLength)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_KEYGENERATE_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_KeyGenerate()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_KEYGENERATE_ENTRY(cryptoKeyId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_KEYGENERATE_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_KeyGenerate()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_KEYGENERATE_EXIT(Retval,cryptoKeyId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_KEYDERIVE_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_KeyDerive()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_KEYDERIVE_ENTRY(cryptoKeyId,targetCryptoKeyId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_KEYDERIVE_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_KeyDerive()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_KEYDERIVE_EXIT(Retval,cryptoKeyId,targetCryptoKeyId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_KEYEXCHANGECALCPUBVAL_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_KeyExchangeCalcPubVal()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_KEYEXCHANGECALCPUBVAL_ENTRY(cryptoKeyId,publicValuePtr,publicValueLengthPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_KEYEXCHANGECALCPUBVAL_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_KeyExchangeCalcPubVal()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_KEYEXCHANGECALCPUBVAL_EXIT(Retval,cryptoKeyId,publicValuePtr,publicValueLengthPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_KEYEXCHANGECALCSECRET_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_KeyExchangeCalcSecret()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_KEYEXCHANGECALCSECRET_ENTRY(cryptoKeyId,partnerPublicValuePtr,partnerPublicValueLength)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_KEYEXCHANGECALCSECRET_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_KeyExchangeCalcSecret()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_KEYEXCHANGECALCSECRET_EXIT(Retval,cryptoKeyId,partnerPublicValuePtr,partnerPublicValueLength)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_CERTIFICATEPARSE_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_CertificateParse()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_CERTIFICATEPARSE_ENTRY(cryptoKeyId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_CERTIFICATEPARSE_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_CertificateParse()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_CERTIFICATEPARSE_EXIT(Retval,cryptoKeyId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_CERTIFICATEVERIFY_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_CertificateVerify()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_CERTIFICATEVERIFY_ENTRY(cryptoKeyId,verifyCryptoKeyId,verifyPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_CERTIFICATEVERIFY_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_CertificateVerify()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_CERTIFICATEVERIFY_EXIT(Retval,cryptoKeyId,verifyCryptoKeyId,verifyPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTSET_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_Int_KMn_KeyElementSet()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTSET_ENTRY(cryptoKeyId,keyElementId,keyPtr,keyLength)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTSET_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_Int_KMn_KeyElementSet()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTSET_EXIT(Retval,cryptoKeyId,keyElementId,keyPtr,keyLength)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYSETVALID_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_Int_KMn_KeySetValid()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYSETVALID_ENTRY(cryptoKeyId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYSETVALID_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_Int_KMn_KeySetValid()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYSETVALID_EXIT(Retval,cryptoKeyId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYSETINVALID_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_Int_KMn_KeySetInvalid()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYSETINVALID_ENTRY(cryptoKeyId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYSETINVALID_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_Int_KMn_KeySetInvalid()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYSETINVALID_EXIT(Retval,cryptoKeyId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYGETSTATUS_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_Int_KMn_KeyGetStatus()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYGETSTATUS_ENTRY(cryptoKeyId,keyStatusPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYGETSTATUS_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_Int_KMn_KeyGetStatus()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYGETSTATUS_EXIT(Retval,cryptoKeyId,keyStatusPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTGET_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_Int_KMn_KeyElementGet()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTGET_ENTRY(cryptoKeyId,keyElementId,resultPtr,resultLengthPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTGET_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_Int_KMn_KeyElementGet()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTGET_EXIT(Retval,cryptoKeyId,keyElementId,resultPtr,resultLengthPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTCOPY_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_Int_KMn_KeyElementCopy()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTCOPY_ENTRY(cryptoKeyId,keyElementId,targetCryptoKeyId,targetKeyElementId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTCOPY_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_Int_KMn_KeyElementCopy()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTCOPY_EXIT(Retval,cryptoKeyId,keyElementId,targetCryptoKeyId,targetKeyElementId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYCOPY_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_Int_KMn_KeyCopy()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYCOPY_ENTRY(cryptoKeyId,targetCryptoKeyId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYCOPY_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_Int_KMn_KeyCopy()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYCOPY_EXIT(Retval,cryptoKeyId,targetCryptoKeyId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTIDSGET_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_Int_KMn_KeyElementIdsGet()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTIDSGET_ENTRY(cryptoKeyId,keyElementIdsPtr,keyElementIdsLengthPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTIDSGET_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_Int_KMn_KeyElementIdsGet()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTIDSGET_EXIT(Retval,cryptoKeyId,keyElementIdsPtr,keyElementIdsLengthPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_RANDOMSEED_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_Int_KMn_RandomSeed()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_RANDOMSEED_ENTRY(cryptoKeyId,seedPtr,seedLength)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_RANDOMSEED_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_Int_KMn_RandomSeed()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_RANDOMSEED_EXIT(Retval,cryptoKeyId,seedPtr,seedLength)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_Int_KMn_KeyGenerate()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ENTRY(cryptoKeyId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_Int_KMn_KeyGenerate()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_EXIT(Retval,cryptoKeyId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYDERIVE_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_Int_KMn_KeyDerive()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYDERIVE_ENTRY(cryptoKeyId,targetCryptoKeyId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYDERIVE_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_Int_KMn_KeyDerive()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYDERIVE_EXIT(Retval,cryptoKeyId,targetCryptoKeyId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGECALCPUBVAL_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcPubVal()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGECALCPUBVAL_ENTRY(cryptoKeyId,publicValuePtr,publicValueLengthPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGECALCPUBVAL_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcPubVal()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGECALCPUBVAL_EXIT(Retval,cryptoKeyId,publicValuePtr,publicValueLengthPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGECALCSECRET_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcSecret()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGECALCSECRET_ENTRY(cryptoKeyId,partnerPublicValuePtr,partnerPublicValueLength)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGECALCSECRET_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcSecret()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYEXCHANGECALCSECRET_EXIT(Retval,cryptoKeyId,partnerPublicValuePtr,partnerPublicValueLength)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_CERTIFICATEPARSE_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_Int_KMn_CertificateParse()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_CERTIFICATEPARSE_ENTRY(cryptoKeyId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_CERTIFICATEPARSE_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_Int_KMn_CertificateParse()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_CERTIFICATEPARSE_EXIT(Retval,cryptoKeyId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_CERTIFICATEVERIFY_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_Int_KMn_CertificateVerify()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_CERTIFICATEVERIFY_ENTRY(cryptoKeyId,verifyCryptoKeyId,verifyPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_CERTIFICATEVERIFY_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_Int_KMn_CertificateVerify()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_CERTIFICATEVERIFY_EXIT(Retval,cryptoKeyId,verifyCryptoKeyId,verifyPtr)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTCOPYPARTIAL_ENTRY
/** \brief Entry point of function Crypto_xVIx_xAIx_Int_KMn_KeyElementCopyPartial()
 **
 ** The macro takes the function arguments as parameters.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTCOPYPARTIAL_ENTRY(cryptoKeyId,keyElementId,keyElementSourceOffset,keyElementTargetOffset,keyElementCopyLength,targetCryptoKeyId,targetKeyElementId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/** @cond
 ** \brief Exclude section from doxygen */
#ifndef DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTCOPYPARTIAL_EXIT
/** \brief Exit point of function Crypto_xVIx_xAIx_Int_KMn_KeyElementCopyPartial()
 **
 ** The first parameter of the macro is the return
 ** value of the function, followed by the arguments
 ** of the function.
 */
#define DBG_CRYPTO_XVIX_XAIX_INT_KMN_KEYELEMENTCOPYPARTIAL_EXIT(Retval,cryptoKeyId,keyElementId,keyElementSourceOffset,keyElementTargetOffset,keyElementCopyLength,targetCryptoKeyId,targetKeyElementId)
#endif
/** \brief Exclude section from doxygen
 ** @endcond */

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

/*================================================================================================*/

#endif /* ifndef CRYPTO_XVIX_XAIX_TRACE_H */

/*==================[end of file]=================================================================*/

