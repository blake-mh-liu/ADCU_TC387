/**
 * \file
 *
 * \brief AUTOSAR Csm
 *
 * This file contains the implementation of the AUTOSAR
 * module Csm.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*================================================================================================*/

/* !LINKSTO CSM0003, 1
 */

#ifndef CSM_CFG_H
#define CSM_CFG_H

/*==================[includes]====================================================================*/

/*==================[macros]======================================================================*/

#if (defined CSM_RTE_ENABLED)
#error CSM_RTE_ENABLED is already defined
#endif
/** \brief  tbd */
[!IF "(CsmGeneral/CsmRteUsage = 'true')"!][!//
#define  CSM_RTE_ENABLED             STD_ON
[!ELSE!][!//
#define  CSM_RTE_ENABLED             STD_OFF
[!ENDIF!][!//

#if (defined CSM_GETVERSIONINFO_ENABLED)
#error CSM_GETVERSIONINFO_ENABLED is already defined
#endif
/** \brief  tbd */
[!IF "node:value(as:modconf('Csm')/CsmGeneral/CsmVersionInfoApi) = 'true'"!][!//
#define  CSM_GETVERSIONINFO_ENABLED  STD_ON
[!ELSE!][!//
#define  CSM_GETVERSIONINFO_ENABLED  STD_OFF
[!ENDIF!][!//

/* !LINKSTO CSM0031, 1
 */
#if (defined CSM_SYNCJOBPROCESSING_ENABLED)
#error CSM_SYNCJOBPROCESSING_ENABLED is already defined
#endif
/** \brief  Pre-processor switch that enables or disables availability of synchronous job processing APIs. */
[!IF "node:value(as:modconf('Csm')/CsmGeneral/CsmUseSyncJobProcessing) = 'true'"!][!//
#define  CSM_SYNCJOBPROCESSING_ENABLED  STD_ON
[!ELSE!][!//
#define  CSM_SYNCJOBPROCESSING_ENABLED  STD_OFF
[!ENDIF!][!//

#if (defined CSM_USEPRIORITIES_ENABLED)
#error CSM_USEPRIORITIES_ENABLED is already defined
#endif
/** \brief  Pre-processor switch that enables or disables priority handling. */
[!IF "node:value(as:modconf('Csm')/CsmGeneral/CsmUseSyncJobProcessing) = 'false'"!][!//
[!IF "node:value(as:modconf('Csm')/CsmGeneral/CsmUsePriorities) = 'true'"!][!//
#define  CSM_USEPRIORITIES_ENABLED  STD_ON
[!ELSE!][!//
#define  CSM_USEPRIORITIES_ENABLED  STD_OFF
[!ENDIF!][!//
[!ELSE!][!//
#define  CSM_USEPRIORITIES_ENABLED  STD_OFF
[!ENDIF!][!//
[!IF "(CsmGeneral/CsmRteUsage = 'false')"!][!//
[!//
#if (defined CSM_ALIGN_BASE_TYPE)
#error CSM_ALIGN_BASE_TYPE is already defined
#endif
/** \brief  The standard type Csm_AlignType base upon. */
#define  CSM_ALIGN_BASE_TYPE         [!"node:value(as:modconf('Csm')/CsmGeneral/CsmMaxAlignScalarType)"!]

#if (defined CSM_LEN_IN_ALIGN_TYPE)
#error CSM_LEN_IN_ALIGN_TYPE is already defined
#endif
/** \brief  The length, in elements of type ::Csm_AlignType, of an array which can hold
 **         as many bytes as given as input.
 **/
#define  CSM_LEN_IN_ALIGN_TYPE(ByteLength)     \
(                                              \
   (uint32)                                    \
   (                                           \
      (uint32)                                 \
      (                                        \
         (uint32)                              \
         (                                     \
            (uint32)(ByteLength) - (uint32)1UL \
         ) /                                   \
         (uint32)sizeof(Csm_AlignType)         \
      ) +                                      \
      (uint32)1UL                              \
   )                                           \
)

[!//
[!/* The following parameters are not used for the calculation of the size of the type      */!][!//
[!/* Csm_AsymPublicKeyType/AsymPublicKeyType because the corresponding services             */!][!//
[!/* are not implemented                                                                    */!][!//
[!/*   CsmAsymEncryptMaxKeySize                                                             */!][!//
[!//
[!VAR "CsmAsymPublicKeyLength" = "1"!][!//
[!IF "$CsmAsymPublicKeyLength < node:value(as:modconf('Csm')/CsmSignatureVerify/CsmSignatureVerifyMaxKeySize)"!][!//
  [!VAR "CsmAsymPublicKeyLength" = "node:value(as:modconf('Csm')/CsmSignatureVerify/CsmSignatureVerifyMaxKeySize)"!][!//
[!ENDIF!][!//
[!IF "$CsmAsymPublicKeyLength < node:value(as:modconf('Csm')/CsmAsymPublicKeyExtract/CsmAsymPublicKeyExtractMaxKeySize)"!][!//
  [!VAR "CsmAsymPublicKeyLength" = "node:value(as:modconf('Csm')/CsmAsymPublicKeyExtract/CsmAsymPublicKeyExtractMaxKeySize)"!][!//
[!ENDIF!][!//
[!IF "$CsmAsymPublicKeyLength < node:value(as:modconf('Csm')/CsmSymKeyWrapAsym/CsmSymKeyWrapAsymMaxPubKeySize)"!][!//
  [!VAR "CsmAsymPublicKeyLength" = "node:value(as:modconf('Csm')/CsmSymKeyWrapAsym/CsmSymKeyWrapAsymMaxPubKeySize)"!][!//
[!ENDIF!][!//
[!IF "$CsmAsymPublicKeyLength < node:value(as:modconf('Csm')/CsmAsymPrivateKeyWrapAsym/CsmAsymPrivateKeyWrapAsymMaxPubKeySize)"!][!//
  [!VAR "CsmAsymPublicKeyLength" = "node:value(as:modconf('Csm')/CsmAsymPrivateKeyWrapAsym/CsmAsymPrivateKeyWrapAsymMaxPubKeySize)"!][!//
[!ENDIF!][!//
[!//
/* !LINKSTO EB_CSM0079_01, 1
 */
#if (defined CSM_ASYM_PUB_KEY_MAX_SIZE)
#error CSM_ASYM_PUB_KEY_MAX_SIZE is already defined
#endif
/** \brief  The maximum length of public asymmetric key key data
 **
 ** This length is used for the public asymmetric key of asymmetric cryptographic schemes like
 ** signature verification or asymmetric encryption.
 **/
#define  CSM_ASYM_PUB_KEY_MAX_SIZE   (CSM_LEN_IN_ALIGN_TYPE([!"num:i($CsmAsymPublicKeyLength)"!]UL))

[!//
[!/* The following parameters are not used for the calculation of the size of the type      */!][!//
[!/* Csm_AsymPrivateKeyType/AsymPrivateKeyType because the corresponding services           */!][!//
[!/* are not implemented                                                                    */!][!//
[!/*   CsmAsymDecryptMaxKeySize                                                             */!][!//
[!/*   CsmAsymPrivateKeyExtractMaxKeySize                                                   */!][!//
[!//
[!VAR "CsmAsymPrivateKeyLength" = "1"!][!//
[!IF "$CsmAsymPrivateKeyLength < node:value(as:modconf('Csm')/CsmSignatureGenerate/CsmSignatureGenerateMaxKeySize)"!][!//
  [!VAR "CsmAsymPrivateKeyLength" = "node:value(as:modconf('Csm')/CsmSignatureGenerate/CsmSignatureGenerateMaxKeySize)"!][!//
[!ENDIF!][!//
[!IF "$CsmAsymPrivateKeyLength < node:value(as:modconf('Csm')/CsmAsymPrivateKeyWrapSym/CsmAsymPrivateKeyWrapSymMaxPrivKeySize)"!][!//
  [!VAR "CsmAsymPrivateKeyLength" = "node:value(as:modconf('Csm')/CsmAsymPrivateKeyWrapSym/CsmAsymPrivateKeyWrapSymMaxPrivKeySize)"!][!//
[!ENDIF!][!//
[!IF "$CsmAsymPrivateKeyLength < node:value(as:modconf('Csm')/CsmAsymPrivateKeyWrapAsym/CsmAsymPrivateKeyWrapAsymMaxPrivKeySize)"!][!//
  [!VAR "CsmAsymPrivateKeyLength" = "node:value(as:modconf('Csm')/CsmAsymPrivateKeyWrapAsym/CsmAsymPrivateKeyWrapAsymMaxPrivKeySize)"!][!//
[!ENDIF!][!//
[!//
/* !LINKSTO EB_CSM0080_01, 1
 */
#if (defined CSM_ASYM_PRIV_KEY_MAX_SIZE)
#error CSM_ASYM_PRIV_KEY_MAX_SIZE is already defined
#endif
/** \brief  The maximum length of private asymmetric key key data
 **
 ** This length is used for the private asymmetric key of asymmetric cryptographic schemes like
 ** signature generation or asymmetric decryption.
 **/
#define  CSM_ASYM_PRIV_KEY_MAX_SIZE  (CSM_LEN_IN_ALIGN_TYPE([!"num:i($CsmAsymPrivateKeyLength)"!]UL))

[!//
[!/* The following parameters are not used for the calculation of the size of the type      */!][!//
[!/* Csm_SymKeyType/SymKeyType because the corresponding services                           */!][!//
[!/* are not implemented                                                                    */!][!//
[!/*   CsmKeyDeriveMaxKeySize                                                               */!][!//
[!/*   CsmKeyExchangeCalcSymKeyMaxSymKeySize                                                */!][!//
[!/*   CsmKeyDeriveSymKeyMaxSymKeySize                                                      */!][!//
[!//
[!VAR "CsmSymKeyLength" = "1"!][!//
[!IF "$CsmSymKeyLength < node:value(as:modconf('Csm')/CsmSymBlockEncrypt/CsmSymBlockEncryptMaxKeySize)"!][!//
  [!VAR "CsmSymKeyLength" = "node:value(as:modconf('Csm')/CsmSymBlockEncrypt/CsmSymBlockEncryptMaxKeySize)"!][!//
[!ENDIF!][!//
[!IF "$CsmSymKeyLength < node:value(as:modconf('Csm')/CsmSymBlockDecrypt/CsmSymBlockDecryptMaxKeySize)"!][!//
  [!VAR "CsmSymKeyLength" = "node:value(as:modconf('Csm')/CsmSymBlockDecrypt/CsmSymBlockDecryptMaxKeySize)"!][!//
[!ENDIF!][!//
[!IF "$CsmSymKeyLength < node:value(as:modconf('Csm')/CsmSymEncrypt/CsmSymEncryptMaxKeySize)"!][!//
  [!VAR "CsmSymKeyLength" = "node:value(as:modconf('Csm')/CsmSymEncrypt/CsmSymEncryptMaxKeySize)"!][!//
[!ENDIF!][!//
[!IF "$CsmSymKeyLength < node:value(as:modconf('Csm')/CsmSymDecrypt/CsmSymDecryptMaxKeySize)"!][!//
  [!VAR "CsmSymKeyLength" = "node:value(as:modconf('Csm')/CsmSymDecrypt/CsmSymDecryptMaxKeySize)"!][!//
[!ENDIF!][!//
[!IF "$CsmSymKeyLength < node:value(as:modconf('Csm')/CsmSymKeyExtract/CsmSymKeyExtractMaxKeySize)"!][!//
  [!VAR "CsmSymKeyLength" = "node:value(as:modconf('Csm')/CsmSymKeyExtract/CsmSymKeyExtractMaxKeySize)"!][!//
[!ENDIF!][!//
[!IF "$CsmSymKeyLength < node:value(as:modconf('Csm')/CsmMacGenerate/CsmMacGenerateMaxKeySize)"!][!//
  [!VAR "CsmSymKeyLength" = "node:value(as:modconf('Csm')/CsmMacGenerate/CsmMacGenerateMaxKeySize)"!][!//
[!ENDIF!][!//
[!IF "$CsmSymKeyLength < node:value(as:modconf('Csm')/CsmMacVerify/CsmMacVerifyMaxKeySize)"!][!//
  [!VAR "CsmSymKeyLength" = "node:value(as:modconf('Csm')/CsmMacVerify/CsmMacVerifyMaxKeySize)"!][!//
[!ENDIF!][!//
[!IF "$CsmSymKeyLength < node:value(as:modconf('Csm')/CsmSymKeyWrapSym/CsmSymKeyWrapSymMaxSymKeySize)"!][!//
  [!VAR "CsmSymKeyLength" = "node:value(as:modconf('Csm')/CsmSymKeyWrapSym/CsmSymKeyWrapSymMaxSymKeySize)"!][!//
[!ENDIF!][!//
[!IF "$CsmSymKeyLength < node:value(as:modconf('Csm')/CsmSymKeyWrapAsym/CsmSymKeyWrapAsymMaxSymKeySize)"!][!//
  [!VAR "CsmSymKeyLength" = "node:value(as:modconf('Csm')/CsmSymKeyWrapAsym/CsmSymKeyWrapAsymMaxSymKeySize)"!][!//
[!ENDIF!][!//
[!IF "$CsmSymKeyLength < node:value(as:modconf('Csm')/CsmAsymPrivateKeyWrapSym/CsmAsymPrivateKeyWrapSymMaxSymKeySize)"!][!//
  [!VAR "CsmSymKeyLength" = "node:value(as:modconf('Csm')/CsmAsymPrivateKeyWrapSym/CsmAsymPrivateKeyWrapSymMaxSymKeySize)"!][!//
[!ENDIF!][!//
[!//
/* !LINKSTO EB_CSM0082_01, 1
 */
#if (defined CSM_SYM_KEY_MAX_SIZE)
#error CSM_SYM_KEY_MAX_SIZE is already defined
#endif
/** \brief  The maximum length of symmetric key key data
 **
 ** This length is used for the symmetric key of symmetric cryptographic schemes like HMAC
 ** generation.
 **/
#define  CSM_SYM_KEY_MAX_SIZE        (CSM_LEN_IN_ALIGN_TYPE([!"num:i($CsmSymKeyLength)"!]UL))

[!ENDIF!][!//
[!//
/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #ifndef CSM_CFG_H */

/*==================[end of file]=================================================================*/

