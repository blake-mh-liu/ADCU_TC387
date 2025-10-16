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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KMn_KEYGENERATE_ED25519PH_NOTSET.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519PH_NOTSET_H
#define CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519PH_NOTSET_H

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int_KMn_KEYGENERATE_ED25519PH_NOTSET_Cfg.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_KMn_KEYGENERATE_ED25519PH_NOTSET.h/0002,1 */

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_PTR
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  The PrimitiveType for the dummy primitive. **/
extern CONST(Crypto_xVIx_xAIx_PrimitiveDescriptionType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_KEYGENERATE_ED25519PH_NOTSET_Primitive;

/** \brief  The CDOPrimitiveCnfgType for the dummy primitive. **/
extern CONST(Crypto_xVIx_xAIx_CDOPrimitiveCnfgType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_KEYGENERATE_ED25519PH_NOTSET_PrimitiveCnfg;

/** \brief  The dummy primitive used if a KeyManagement job shall be executed as secondary job. **/
extern CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_KEYGENERATE_ED25519PH_NOTSET_DummyPrimitive;

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_PTR
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  Performs the processing of the KMn primitive KEYGENERATE_ED25519PH_NOTSET.
 **
 ** This function generates new key material.
KEYGENERAT, KEYDERIVE_, m4_dnl
 ** This function generates new derived key material.
) **
 ** \param[in]      objectId                  Holds the identifier of the Crypto Driver Object to
 **                                           be used for optional secondary primitives.
 ** \param[in,out]  jobs                      Pointer to a list of secondary jobs.
 ** \param[in]      jobsLength                The number of secondary jobs.
 ** \param[in,out]  wkspDataPtr               Pointer to the memory location that is allowed to be
 **                                           used as the workspace for the processing of the
 **                                           (primary part of the) KMn primitive KEYGENERATE_ED25519PH_NOTSET.
 ** \param[in]      wkspDataLen               The number of bytes available in the workspace memory
 **                                           location provided by wkspDataPtr.
 ** \param[in]      cryptoKeyId               Identifier of the crypto key that shall be used.
 **
 ** \returns  Error value.
 **
 ** \retval  E_OK                    Request successful.
 ** \retval  E_NOT_OK                Request failed.
 ** \retval  CRYPTO_E_KEY_EMPTY      Request failed because of uninitialized source key element.
 ** \retval  CRYPTO_E_KEY_NOT_VALID  Request failed, the key state of the key identified by
 **                                  cryptoKeyId is "invalid".
 **
 ** \Synchronicity{Sync}
 ** \Reentrancy{Reentrant}
 **/
#if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519PH_NOTSET == STD_ON)
extern FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_Int_KMn_KEYGENERATE_ED25519PH_NOTSET_Process
(
          uint32                                                 objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) jobs,
          uint32                                                 jobsLength,
    P2VAR(uint8,          AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) wkspDataPtr,
          uint32                                                 wkspDataLen,
          uint32                                                 cryptoKeyId
);
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KMN_KEYGENERATE_ED25519PH_NOTSET == STD_ON) */

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_INT_KMN_KEYGENERATE_ED25519PH_NOTSET_H */

/*==================[end of file]=================================================================*/

