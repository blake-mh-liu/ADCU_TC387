/* --------{ EB Automotive C Source File }-------- */

#ifndef CRY_COMMONCONFIG_H
#define CRY_COMMONCONFIG_H

/*==================[includes]====================================================================*/

#include <Std_Types.h>

/*==================[macros]======================================================================*/

[!VAR "CryRsaPubKeyLength" = "1"!][!//
[!VAR "CryRsaPrivKeyLength" = "1"!][!//
[!VAR "CryEdDSAKeyLength" = "1"!][!//
[!VAR "CryMaxKeyLength" = "1"!][!//

[!LOOP "as:modconf('Cry')/CryRsaSsaV15Generate/CryRsaSsaV15GenerateConfig/*"!][!//
   [!IF "($CryRsaPrivKeyLength < num:i(node:value(./CryRsaSsaV15GenerateKeyLength)))"!][!//
      [!VAR "CryRsaPrivKeyLength" = "num:i(node:value(./CryRsaSsaV15GenerateKeyLength))"!][!//
   [!ENDIF!][!//
[!ENDLOOP!][!//

[!LOOP "as:modconf('Cry')/CryRsaSsaPssVerify/CryRsaSsaPssVerifyConfig/*"!][!//
   [!IF "($CryRsaPubKeyLength < num:i(node:value(./CryRsaSsaPssVerifyKeyLength)))"!][!//
      [!VAR "CryRsaPubKeyLength" = "num:i(node:value(./CryRsaSsaPssVerifyKeyLength))"!][!//
   [!ENDIF!][!//
[!ENDLOOP!][!//

[!LOOP "as:modconf('Cry')/CryRsaSsaV15Verify/CryRsaSsaV15VerifyConfig/*"!][!//
   [!IF "($CryRsaPubKeyLength < num:i(node:value(./CryRsaSsaV15VerifyKeyLength)))"!][!//
      [!VAR "CryRsaPubKeyLength" = "num:i(node:value(./CryRsaSsaV15VerifyKeyLength))"!][!//
   [!ENDIF!][!//
[!ENDLOOP!][!//

[!LOOP "as:modconf('Cry')/CryCVCPublicKeyExtract/CryCVCPublicKeyExtractConfig/*"!][!//
   [!IF "($CryRsaPubKeyLength < num:i(node:value(./CryCVCPublicKeyExtractLength)))"!][!//
      [!VAR "CryRsaPubKeyLength" = "num:i(node:value(./CryCVCPublicKeyExtractLength))"!][!//
   [!ENDIF!][!//
[!ENDLOOP!][!//

[!LOOP "as:modconf('Cry')/CryExtractRsaPublicKey/CryExtractRsaPublicKeyConfig/*"!][!//
   [!IF "($CryRsaPubKeyLength < num:i(node:value(./CryExtractRsaPublicKeyLength)))"!][!//
      [!VAR "CryRsaPubKeyLength" = "num:i(node:value(./CryExtractRsaPublicKeyLength))"!][!//
   [!ENDIF!][!//
[!ENDLOOP!][!//

[!IF "(num:i(0) != num:i(count(as:modconf('Cry')/CryEdDSAGen/CryEdDSAGenConfig/*))) or (num:i(0) != num:i(count(as:modconf('Cry')/CryEdDSAVrfy/CryEdDSAVrfyConfig/*)))"!][!//
/* EdDSA key */
[!VAR "CryEdDSAKeyLength" = "32"!][!//
[!ENDIF!][!//

/* RSA key */
[!VAR "CryMaxKeyLength" = "$CryRsaPubKeyLength"!][!//
[!IF "($CryRsaPubKeyLength < $CryRsaPrivKeyLength)"!][!//
   [!VAR "CryMaxKeyLength" = "$CryRsaPrivKeyLength"!][!//
[!ENDIF!][!//

/* Max of RSA, EdDSA */
[!IF "($CryMaxKeyLength < $CryEdDSAKeyLength)"!][!//
   [!VAR "CryMaxKeyLength" = "$CryEdDSAKeyLength"!][!//
[!ENDIF!][!//

#if (defined CRY_RSAPUBKEY_NUM_LEN_WORDS)
#error CRY_RSAPUBKEY_NUM_LEN_WORDS is already defined
#endif
/** \brief The length, in words, which is needed for the long number representation of
 *         the longest possible stored public RSA key.
 *
 */
#define CRY_RSAPUBKEY_NUM_LEN_WORDS                           \
(                                                             \
  (Cry_LNWordType)                                            \
    (                                                         \
        Cry_LNNumberLen([!"num:i($CryRsaPubKeyLength)"!]U) +  \
    (Cry_LNWordType)1UL                                       \
  )                                                           \
)

#if (defined CRY_MAX_KEY_NUM_LEN_WORDS)
#error CRY_MAX_KEY_NUM_LEN_WORDS is already defined
#endif
/** \brief The max length, in words, which is needed for the long number representation of
 *         the longest possible stored key.
 *
 */
#define CRY_MAX_KEY_NUM_LEN_WORDS                             \
(                                                             \
  (Cry_LNWordType)                                            \
    (                                                         \
        Cry_LNNumberLen([!"num:i($CryMaxKeyLength)"!]U) +     \
    (Cry_LNWordType)1UL                                       \
  )                                                           \
)

#if (defined CRY_RSAPUBKEY_NUM_LEN_BYTES)
#error CRY_RSAPUBKEY_NUM_LEN_BYTES is already defined
#endif
/** \brief The length, in bytes, which is needed for the
 *         the longest possible stored public RSA key.
 */
#define CRY_RSAPUBKEY_NUM_LEN_BYTES [!"num:i($CryRsaPubKeyLength)"!]U

#if (defined CRY_RSAPRIVKEY_NUM_LEN_WORDS)
#error CRY_RSAPRIVKEY_NUM_LEN_WORDS is already defined
#endif
/**
 * \brief The length, in words, which is needed for the long number representation of
 *         the longest possible stored private RSA key.
 *
 */
#define CRY_RSAPRIVKEY_NUM_LEN_WORDS                           \
(                                                              \
  (Cry_LNWordType)                                             \
    (                                                          \
        Cry_LNNumberLen([!"num:i($CryRsaPrivKeyLength)"!]U) +  \
    (Cry_LNWordType)1UL                                        \
  )                                                            \
)

#if (defined CRY_RSA_PRIV_KEY_TEMP_LEN_WORDS)
#error CRY_RSA_PRIV_KEY_TEMP_LEN_WORDS is already defined
#endif
/** \brief The length, in words, which is needed for the long number representation of
 *         the longest possible temporary private RSA key.
 */
#define CRY_RSA_PRIV_KEY_TEMP_LEN_WORDS                      \
(                                                            \
   (Cry_LNWordType)                                          \
   (                                                         \
      (CRY_RSAPRIVKEY_NUM_LEN_WORDS * (Cry_LNWordType)2UL) - \
      (Cry_LNWordType)1UL                                    \
   )                                                         \
)

#if (defined CRY_RSAPRIVKEY_NUM_LEN_BYTES)
#error CRY_RSAPRIVKEY_NUM_LEN_BYTES is already defined
#endif
/** \brief The length, in bytes, which is needed for the
 *         the longest possible stored private RSA key.
 */
#define CRY_RSAPRIVKEY_NUM_LEN_BYTES [!"num:i($CryRsaPrivKeyLength)"!]U


[!IF "count(as:modconf('Cry')/CryRsaSsaV15Verify/CryRsaSsaV15VerifyConfig/*/CryRsaSsaV15VerifyUseBarrett[. = 'true']) > 0 or[!//
     count(as:modconf('Cry')/CryRsaSsaPssVerify/CryRsaSsaPssVerifyConfig/*/CryRsaSsaPssVerifyUseBarrett[. = 'true']) > 0"!][!//

#if (defined CRY_LN_USE_BARRETT)
#error CRY_LN_USE_BARRETT is already defined
#endif
/** \brief The value of this macro indicates whether Barrett reduction is enabled
 *         in at least one CryRsaSsaV15Verify or CryRsaSsaPssVerify configuration.
 */
#define CRY_LN_USE_BARRETT STD_ON

#if (defined CRY_RSA_PUB_KEY_TEMP_LEN_WORDS)
#error CRY_RSA_PUB_KEY_TEMP_LEN_WORDS is already defined
#endif
/** \brief The length, in words, which is needed for the long number representation of
 *         the longest possible temporary public RSA key.
 */
#define CRY_RSA_PUB_KEY_TEMP_LEN_WORDS                        \
(                                                             \
  (Cry_LNWordType)                                            \
    (                                                         \
        (CRY_RSAPUBKEY_NUM_LEN_WORDS * (Cry_LNWordType)3UL) + \
    (Cry_LNWordType)5UL                                       \
  )                                                           \
)

[!ELSE!][!//

#if (defined CRY_LN_USE_BARRETT)
#error CRY_LN_USE_BARRETT is already defined
#endif
/** \brief The value of this macro indicates whether Barrett reduction is enabled
 *         in at least one CryRsaSsaV15Verify or CryRsaSsaPssVerify configuration.
 */
#define CRY_LN_USE_BARRETT STD_OFF

#if (defined CRY_RSA_PUB_KEY_TEMP_LEN_WORDS)
#error CRY_RSA_PUB_KEY_TEMP_LEN_WORDS is already defined
#endif
/** \brief The length, in words, which is needed for the long number representation of
 *         the longest possible temporary public RSA key.
 */
#define CRY_RSA_PUB_KEY_TEMP_LEN_WORDS                        \
(                                                             \
  (Cry_LNWordType)                                            \
    (                                                         \
        (CRY_RSAPUBKEY_NUM_LEN_WORDS * (Cry_LNWordType)2UL) - \
    (Cry_LNWordType)1UL                                       \
  )                                                           \
)

[!ENDIF!][!//

#if (defined CRY_LN_INTERRUPTABLE_ENABLED)
#error CRY_LN_INTERRUPTABLE_ENABLED is already defined
#endif
/** \brief Preprocessor switch to select between interruptable/non-interruptable
 **        long number library implementation variants
 **/
#define CRY_LN_INTERRUPTABLE_ENABLED                       [!//
[!IF "((node:exists(as:modconf('Cry')/CryGeneral/CryInterruptableLN)) and ((node:value(as:modconf('Cry')/CryGeneral/CryInterruptableLN)) = 'true'))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CRY_LN_PLATFORM_DOUBLE_WORD_SUPPORT)
#error CRY_LN_PLATFORM_DOUBLE_WORD_SUPPORT is already defined
#endif
/** \brief Preprocessor switch to enable/disable support for double word data type */
#define CRY_LN_PLATFORM_DOUBLE_WORD_SUPPORT                [!//
[!IF "((node:exists(as:modconf('Cry')/CryGeneral/CryLNPlatformDoubleWordSupport)) and (node:value(as:modconf('Cry')/CryGeneral/CryLNPlatformDoubleWordSupport)) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CRY_LN_MEMORY_OPTIMIZED)
#error CRY_LN_MEMORY_OPTIMIZED is already defined
#endif
/** \brief Value indicating that the long number library "memory optimized" implementation variant
 **        shall be used
 **/
#define CRY_LN_MEMORY_OPTIMIZED                            0U

#if (defined CRY_LN_SPEED_OPTIMIZED)
#error CRY_LN_SPEED_OPTIMIZED is already defined
#endif
/** \brief Value indicating that the long number library "speed optimized" implementation variant
 **        shall be used
 **/
#define CRY_LN_SPEED_OPTIMIZED                             1U

#if (defined CRY_LN_ALGORITHM_VARIANT)
#error CRY_LN_ALGORITHM_VARIANT is already defined
#endif
/** \brief Preprocessor switch to select between "memory optimized"/"speed optimized" number library
 **        implementation variants
 **/
#define CRY_LN_ALGORITHM_VARIANT                           [!//
[!IF "((node:exists(as:modconf('Cry')/CryGeneral/CryLNAlgorithmImplementation)) and (as:modconf('Cry')/CryGeneral/CryLNAlgorithmImplementation = 'CRY_LN_MEMORY_OPTIMIZED'))"!]CRY_LN_MEMORY_OPTIMIZED[!ELSE!]CRY_LN_SPEED_OPTIMIZED[!ENDIF!]

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #ifndef CRY_COMMONCONFIG_H */
