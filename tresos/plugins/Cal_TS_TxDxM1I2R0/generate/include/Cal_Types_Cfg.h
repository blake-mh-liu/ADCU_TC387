/**
 * \file
 *
 * \brief AUTOSAR Cal
 *
 * This file contains the implementation of the AUTOSAR
 * module Cal.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef CAL_TYPES_CFG_H
#define CAL_TYPES_CFG_H


/*==[Includes]================================================================*/

#include <Std_Types.h>


/*==[Macros]==================================================================*/

/** \brief The length, in elements of type ::Cal_AlignType, of an array which
 *         can hold as many bytes as given as input.
 */
#define CAL_LEN_IN_ALIGN_TYPE(ByteLength)      \
(                                              \
  (uint32)                                     \
  (                                            \
    (uint32)                                   \
    (                                          \
      (uint32)                                 \
      (                                        \
        (uint32)(ByteLength) - (uint32)1UL     \
      ) /                                      \
      (uint32)sizeof(Cal_AlignType)            \
    ) +                                        \
    (uint32)1UL                                \
  )                                            \
)

[!VAR "CalSymKeyLength" = "1"!][!//

[!IF "$CalSymKeyLength < node:value(as:modconf('Cal')/CalSymBlockEncrypt/CalSymBlockEncryptMaxKeySize)"!][!//
  [!VAR "CalSymKeyLength" = "node:value(as:modconf('Cal')/CalSymBlockEncrypt/CalSymBlockEncryptMaxKeySize)"!][!//
[!ENDIF!][!//

[!IF "$CalSymKeyLength < node:value(as:modconf('Cal')/CalSymBlockDecrypt/CalSymBlockDecryptMaxKeySize)"!][!//
  [!VAR "CalSymKeyLength" = "node:value(as:modconf('Cal')/CalSymBlockDecrypt/CalSymBlockDecryptMaxKeySize)"!][!//
[!ENDIF!][!//

[!IF "$CalSymKeyLength < node:value(as:modconf('Cal')/CalSymDecrypt/CalSymDecryptMaxKeySize)"!][!//
  [!VAR "CalSymKeyLength" = "node:value(as:modconf('Cal')/CalSymDecrypt/CalSymDecryptMaxKeySize)"!][!//
[!ENDIF!][!//

[!IF "$CalSymKeyLength < node:value(as:modconf('Cal')/CalMacGenerate/CalMacGenerateMaxKeySize)"!][!//
  [!VAR "CalSymKeyLength" = "node:value(as:modconf('Cal')/CalMacGenerate/CalMacGenerateMaxKeySize)"!][!//
[!ENDIF!][!//

[!IF "$CalSymKeyLength < node:value(as:modconf('Cal')/CalMacVerify/CalMacVerifyMaxKeySize)"!][!//
  [!VAR "CalSymKeyLength" = "node:value(as:modconf('Cal')/CalMacVerify/CalMacVerifyMaxKeySize)"!][!//
[!ENDIF!][!//

[!IF "$CalSymKeyLength < node:value(as:modconf('Cal')/CalSymKeyExtract/CalSymKeyExtractMaxKeySize)"!][!//
  [!VAR "CalSymKeyLength" = "node:value(as:modconf('Cal')/CalSymKeyExtract/CalSymKeyExtractMaxKeySize)"!][!//
[!ENDIF!][!//

[!IF "$CalSymKeyLength < node:value(as:modconf('Cal')/CalKeyDerive/CalKeyDeriveMaxKeySize)"!][!//
  [!VAR "CalSymKeyLength" = "node:value(as:modconf('Cal')/CalKeyDerive/CalKeyDeriveMaxKeySize)"!][!//
[!ENDIF!][!//

/** \brief CAL_SYM_KEY_MAX_SIZE*sizeof(Cal_AlignType) defines the maximal size in bytes of all
 *         configured symmetrical keys
 */
#define CAL_SYM_KEY_MAX_SIZE CAL_LEN_IN_ALIGN_TYPE([!"num:i($CalSymKeyLength)"!]UL)





[!VAR "CalAsymPublicKeyLength" = "1"!][!//

[!IF "$CalAsymPublicKeyLength < node:value(as:modconf('Cal')/CalSignatureVerify/CalSignatureVerifyMaxKeySize)"!][!//
  [!VAR "CalAsymPublicKeyLength" = "node:value(as:modconf('Cal')/CalSignatureVerify/CalSignatureVerifyMaxKeySize)"!][!//
[!ENDIF!][!//

[!IF "$CalAsymPublicKeyLength < node:value(as:modconf('Cal')/CalAsymPublicKeyExtract/CalAsymPublicKeyExtractMaxKeySize)"!][!//
  [!VAR "CalAsymPublicKeyLength" = "node:value(as:modconf('Cal')/CalAsymPublicKeyExtract/CalAsymPublicKeyExtractMaxKeySize)"!][!//
[!ENDIF!][!//


/** \brief CAL_ASYM_PUB_KEY_MAX_SIZE*sizeof(Cal_AlignType) defines the maximal size in bytes of all
 *         configured asymmetrical public keys
 */
#define CAL_ASYM_PUB_KEY_MAX_SIZE CAL_LEN_IN_ALIGN_TYPE([!"num:i($CalAsymPublicKeyLength)"!]UL)



[!VAR "CalKeyExchangeBaseLength" = "1"!][!//

[!IF "$CalKeyExchangeBaseLength < node:value(as:modconf('Cal')/CalKeyExchangeCalcPubVal/CalKeyExchangeCalcPubValMaxBaseTypeSize)"!][!//
  [!VAR "CalKeyExchangeBaseLength" = "node:value(as:modconf('Cal')/CalKeyExchangeCalcPubVal/CalKeyExchangeCalcPubValMaxBaseTypeSize)"!][!//
[!ENDIF!][!//

[!IF "$CalKeyExchangeBaseLength < node:value(as:modconf('Cal')/CalKeyExchangeCalcSecret/CalKeyExchangeCalcSecretMaxBaseTypeSize)"!][!//
  [!VAR "CalKeyExchangeBaseLength" = "node:value(as:modconf('Cal')/CalKeyExchangeCalcSecret/CalKeyExchangeCalcSecretMaxBaseTypeSize)"!][!//
[!ENDIF!][!//

/** \brief CAL_KEY_EX_BASE_MAX_SIZE*sizeof(Cal_AlignType) defines the maximal size in bytes of all
 *         configured key exchange base types
 */
#define CAL_KEY_EX_BASE_MAX_SIZE CAL_LEN_IN_ALIGN_TYPE([!"num:i($CalKeyExchangeBaseLength)"!]UL)



[!VAR "CalKeyExchangePrivateLength" = "1"!][!//

[!IF "$CalKeyExchangePrivateLength < node:value(as:modconf('Cal')/CalKeyExchangeCalcPubVal/CalKeyExchangeCalcPubValMaxPrivateTypeSize)"!][!//
  [!VAR "CalKeyExchangePrivateLength" = "node:value(as:modconf('Cal')/CalKeyExchangeCalcPubVal/CalKeyExchangeCalcPubValMaxPrivateTypeSize)"!][!//
[!ENDIF!][!//

[!IF "$CalKeyExchangePrivateLength < node:value(as:modconf('Cal')/CalKeyExchangeCalcSecret/CalKeyExchangeCalcSecretMaxPrivateTypeSize)"!][!//
  [!VAR "CalKeyExchangePrivateLength" = "node:value(as:modconf('Cal')/CalKeyExchangeCalcSecret/CalKeyExchangeCalcSecretMaxPrivateTypeSize)"!][!//
[!ENDIF!][!//

/** \brief CAL_KEY_EX_PRIV_MAX_SIZE*sizeof(Cal_AlignType) defines the maximal size in bytes of all
 *         configured key exchange private types
 */
#define CAL_KEY_EX_PRIV_MAX_SIZE CAL_LEN_IN_ALIGN_TYPE([!"num:i($CalKeyExchangePrivateLength)"!]UL)



/*==[Types]===================================================================*/

/* !LINKSTO CAL0743, 1
 */
/** \brief An integer type with maximal alignment restrictions
 *
 * This is an integer type which has the maximal alignment restrictions. That
 * means that a pointer to a variable to this type can be cast to a pointer
 * to any other integer type without risking alignment problems.
 */
typedef [!"node:value(as:modconf('Cal')/CalGeneral/CalMaxAlignScalarType)"!] Cal_AlignType;


/*==[Constants with external linkage]=========================================*/



/*==[Variables with external linkage]=========================================*/



/*==[Declaration of functions with external linkage]==========================*/

#endif /* #ifndef CAL_TYPES_CFG_H */

