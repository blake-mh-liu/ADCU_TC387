/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0003,1 */

#ifndef CRY_RSASSAPSSVERIFYCONFIG_H
#define CRY_RSASSAPSSVERIFYCONFIG_H

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm.h>

#include <Csm_Hash.h>

#include <Cry_LN.h>


/*==[Macros]==================================================================*/

#if (defined CRY_RSASSAPSSVERIFY_ENABLED)
#error CRY_RSASSAPSSVERIFY_ENABLED is already defined
#endif
/* !LINKSTO EB_CRY_0018,1 */
[!IF "num:i(0) != num:i(count(as:modconf('Cry')/CryRsaSsaPssVerify/CryRsaSsaPssVerifyConfig/*))"!][!//
#define CRY_RSASSAPSSVERIFY_ENABLED STD_ON
[!ELSE!][!//
#define CRY_RSASSAPSSVERIFY_ENABLED STD_OFF
[!ENDIF!][!//

#if(CRY_RSASSAPSSVERIFY_ENABLED == STD_ON)

#if (defined CRY_RSASSAPSSVERIFY_USE_TIME_SLICES)
#error CRY_RSASSAPSSVERIFY_USE_TIME_SLICES is already defined
#endif
[!IF "CryRsaSsaPssVerify/CryRsaSsaPssVerifyUseTimeSlices = 'true'"!][!//
#define CRY_RSASSAPSSVERIFY_USE_TIME_SLICES STD_ON

[!IF "(CryRsaSsaPssVerify/CryRsaSsaPssVerifyUseCbk = 'false')"!][!//
#if (defined CRY_RSASSAPSSVERIFY_NR_OF_TIME_SLICES)
#error CRY_RSASSAPSSVERIFY_NR_OF_TIME_SLICES is already defined
#endif
#define CRY_RSASSAPSSVERIFY_NR_OF_TIME_SLICES [!"num:i(CryRsaSsaPssVerify/CryRsaSsaPssVerifyNumberOfTimeSlices)"!]UL
[!ENDIF!][!//

[!ELSE!][!//
#define CRY_RSASSAPSSVERIFY_USE_TIME_SLICES STD_OFF
[!ENDIF!][!//

#if (defined CRY_RSASSAPSSVERIFY_USE_CBK)
#error CRY_RSASSAPSSVERIFY_USE_CBK is already defined
#endif
[!IF "(CryRsaSsaPssVerify/CryRsaSsaPssVerifyUseTimeSlices = 'true') and (CryRsaSsaPssVerify/CryRsaSsaPssVerifyUseCbk = 'true')"!][!//
#define CRY_RSASSAPSSVERIFY_USE_CBK STD_ON
[!ELSE!][!//
#define CRY_RSASSAPSSVERIFY_USE_CBK STD_OFF
[!ENDIF!][!//

#if (defined CRY_RSASSAPSSVERIFY_BARRETT)
#error CRY_RSASSAPSSVERIFY_BARRETT is already defined
#endif
[!IF "count(as:modconf('Cry')/CryRsaSsaPssVerify/CryRsaSsaPssVerifyConfig/*/CryRsaSsaPssVerifyUseBarrett[. = 'true']) > 0"!][!//
#define CRY_RSASSAPSSVERIFY_BARRETT STD_ON
[!ELSE!][!//
#define CRY_RSASSAPSSVERIFY_BARRETT STD_OFF
[!ENDIF!][!//

#if (defined CRY_SIGN_VRFY_PSS_IMMEDIATE_RESTART_ENABLED)
#error CRY_SIGN_VRFY_PSS_IMMEDIATE_RESTART_ENABLED is already defined
#endif
/** \brief Flag to indicate if the immediate restart of the service regardless of the configuration ID is enabled. */
[!IF "node:exists(as:modconf('Csm')[1]/CsmSignatureVerify/CsmSignatureVerifyImmediateRestart)"!][!//
[!IF "(node:value(as:modconf('Cry')/CryRsaSsaPssVerify/CryRsaSsaPssVerifyImmediateRestartEnabled)) = 'true'"!][!//
#define CRY_SIGN_VRFY_PSS_IMMEDIATE_RESTART_ENABLED STD_ON
[!ELSE!][!//
#define CRY_SIGN_VRFY_PSS_IMMEDIATE_RESTART_ENABLED STD_OFF
[!ENDIF!][!//
[!ELSE!][!//
#define CRY_SIGN_VRFY_PSS_IMMEDIATE_RESTART_ENABLED STD_OFF
[!ENDIF!][!//

/*==[Types]===================================================================*/

/* !LINKSTO EB_CRY_0017,1 */
/**
 * \struct Cry_RsaSsaPssVerifyConfigType
 * \brief The configuration of the RSASSA-PSS signature verification.
 *//**
 * \var Cry_RsaSsaPssVerifyConfigType::SaltLength
 * \brief Indicates the length of the output of the hash function.
 *//**
 * \var Cry_RsaSsaPssVerifyConfigType::HashCfg
 * \brief The configuration of the underlying hash algorithm.
 *//**
 * \var Cry_RsaSsaPssVerifyConfigType::Base64Encoded
 * \brief Indicates whether the signature to verify is base64-encoded.
 *//**
 * \var Cry_RsaSsaPssVerifyConfigType::UseBarrett
 * \brief Indicates whether the signature verification uses Barrett reduction. This
 *        member only exists when Barrett reduction is enabled in a configuration.
 *//**
 * \var Cry_RsaSsaPssVerifyConfigType::SupportRestart
 * \brief Indicates whether restarting of the signature verification feature is
 *        enabled or not.
 */
typedef struct
{
  uint32           SaltLength;
  Csm_ConfigIdType HashCfg;
  boolean          Base64Encoded;
[!IF "count(as:modconf('Cry')/CryRsaSsaPssVerify/CryRsaSsaPssVerifyConfig/*/CryRsaSsaPssVerifyUseBarrett[. = 'true']) > 0"!][!//
  boolean          UseBarrett;
[!ENDIF!][!//
  boolean          SupportRestart;
}
Cry_RsaSsaPssVerifyConfigType;

/*==[Constants with external linkage]=========================================*/

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO EB_CRY_0023,1 */

[!LOOP "as:modconf('Cry')/CryRsaSsaPssVerify/CryRsaSsaPssVerifyConfig/*"!][!//

/** \brief Configuration of the RsaSsa Pss verification primitive.
 */
extern CONST(Cry_RsaSsaPssVerifyConfigType, CRY_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/
#endif /* #if(CRY_RSASSAPSSVERIFY_ENABLED == STD_ON) */

#endif /* CRY_RSASSAPSSVERIFYCONFIG_H */
