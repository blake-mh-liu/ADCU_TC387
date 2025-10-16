/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0003,1 */

#ifndef CRY_RSASSAV15VERIFYCONFIG_H
#define CRY_RSASSAV15VERIFYCONFIG_H

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm.h>

#include <Csm_Hash.h>

#include <Cry_LN.h>

/*==[Macros]==================================================================*/

#if (defined CRY_RSASSAV15VERIFY_ENABLED)
#error CRY_RSASSAV15VERIFY_ENABLED is already defined
#endif
/* !LINKSTO EB_CRY_0018,1 */
[!IF "num:i(0) != num:i(count(as:modconf('Cry')/CryRsaSsaV15Verify/CryRsaSsaV15VerifyConfig/*))"!][!//
#define CRY_RSASSAV15VERIFY_ENABLED STD_ON
[!ELSE!][!//
#define CRY_RSASSAV15VERIFY_ENABLED STD_OFF
[!ENDIF!][!//

#if(CRY_RSASSAV15VERIFY_ENABLED == STD_ON)

#if (defined CRY_RSASSAV15VERIFY_USE_TIME_SLICES)
#error CRY_RSASSAV15VERIFY_USE_TIME_SLICES is already defined
#endif
[!IF "CryRsaSsaV15Verify/CryRsaSsaV15VerifyUseTimeSlices = 'true'"!][!//
#define CRY_RSASSAV15VERIFY_USE_TIME_SLICES STD_ON

[!IF "(CryRsaSsaV15Verify/CryRsaSsaV15VerifyUseCbk = 'false')"!][!//
#if (defined CRY_RSASSAV15VERIFY_NR_OF_TIME_SLICES)
#error CRY_RSASSAV15VERIFY_NR_OF_TIME_SLICES is already defined
#endif
#define CRY_RSASSAV15VERIFY_NR_OF_TIME_SLICES [!"num:i(CryRsaSsaV15Verify/CryRsaSsaV15VerifyNumberOfTimeSlices)"!]UL
[!ENDIF!][!//

[!ELSE!][!//
#define CRY_RSASSAV15VERIFY_USE_TIME_SLICES STD_OFF
[!ENDIF!][!//

#if (defined CRY_RSASSAV15VERIFY_USE_CBK)
#error CRY_RSASSAV15VERIFY_USE_CBK is already defined
#endif
[!IF "(CryRsaSsaV15Verify/CryRsaSsaV15VerifyUseTimeSlices = 'true') and (CryRsaSsaV15Verify/CryRsaSsaV15VerifyUseCbk = 'true')"!][!//
#define CRY_RSASSAV15VERIFY_USE_CBK STD_ON
[!ELSE!][!//
#define CRY_RSASSAV15VERIFY_USE_CBK STD_OFF
[!ENDIF!][!//

#if (defined CRY_RSASSAV15VERIFY_BARRETT)
#error CRY_RSASSAV15VERIFY_BARRETT is already defined
#endif
[!IF "count(as:modconf('Cry')/CryRsaSsaV15Verify/CryRsaSsaV15VerifyConfig/*/CryRsaSsaV15VerifyUseBarrett[. = 'true']) > 0"!][!//
#define CRY_RSASSAV15VERIFY_BARRETT STD_ON
[!ELSE!][!//
#define CRY_RSASSAV15VERIFY_BARRETT STD_OFF
[!ENDIF!][!//

#if (defined CRY_SIGN_VRFY_V15_IMMEDIATE_RESTART_ENABLED)
#error CRY_SIGN_VRFY_V15_IMMEDIATE_RESTART_ENABLED is already defined
#endif
/** \brief Flag to indicate if the immediate restart of the service regardless of the configuration ID is enabled. */
[!IF "node:exists(as:modconf('Csm')[1]/CsmSignatureVerify/CsmSignatureVerifyImmediateRestart)"!][!//
[!IF "(node:value(as:modconf('Cry')/CryRsaSsaV15Verify/CryRsaSsaV15VerifyImmediateRestartEnabled)) = 'true'"!][!//
#define CRY_SIGN_VRFY_V15_IMMEDIATE_RESTART_ENABLED STD_ON
[!ELSE!][!//
#define CRY_SIGN_VRFY_V15_IMMEDIATE_RESTART_ENABLED STD_OFF
[!ENDIF!][!//
[!ELSE!][!//
#define CRY_SIGN_VRFY_V15_IMMEDIATE_RESTART_ENABLED STD_OFF
[!ENDIF!][!//

/*==[Types]===================================================================*/

/* !LINKSTO EB_CRY_0017,1 */
/**
 * \struct Cry_RsaSsaV15VerifyConfigType
 * \brief The configuration of the RSASSA-PKCS1-v1_5 signature verification.
 *//**
 * \var Cry_RsaSsaV15VerifyConfigType::HashCfg
 * \brief The configuration of the underlying hash algorithm.
 *//**
 * \var Cry_RsaSsaV15VerifyConfigType::Base64Encoded
 * \brief Indicates whether the signature to verify is base64-encoded.
 *//**
 * \var Cry_RsaSsaV15VerifyConfigType::UseBarrett
 * \brief Indicates whether the signature verification uses Barrett reduction. This
 *        member only exists when Barrett reduction is enabled in a configuration.
 *//**
 * \var Cry_RsaSsaV15VerifyConfigType::SupportRestart
 * \brief Indicates whether restarting of the signature verification feature is
 *        enabled or not.
 */
typedef struct
{
  Csm_ConfigIdType HashCfg;
  boolean          Base64Encoded;
[!IF "count(as:modconf('Cry')/CryRsaSsaV15Verify/CryRsaSsaV15VerifyConfig/*/CryRsaSsaV15VerifyUseBarrett[. = 'true']) > 0"!][!//
  boolean          UseBarrett;
[!ENDIF!][!//
  boolean          SupportRestart;
}
Cry_RsaSsaV15VerifyConfigType;

/*==[Constants with external linkage]=========================================*/

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO EB_CRY_0023,1 */

[!LOOP "as:modconf('Cry')/CryRsaSsaV15Verify/CryRsaSsaV15VerifyConfig/*"!][!//

/** \brief Configuration of the RsaSsa V 1_5 verification primitive.
 */
extern CONST(Cry_RsaSsaV15VerifyConfigType, CRY_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/
#endif /* #if(CRY_RSASSAV15VERIFY_ENABLED == STD_ON) */

#endif /* CRY_RSASSAV15VERIFYCONFIG_H */
