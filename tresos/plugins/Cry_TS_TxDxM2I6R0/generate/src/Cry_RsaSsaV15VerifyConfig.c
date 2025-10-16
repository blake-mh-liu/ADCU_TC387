/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0006,1 */

/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm_Hash.h>
#include <Cry_LN.h>
#include <Cry_CommonConfig.h>
#include <Cry_RsaSsaV15VerifyConfig.h>

#if(CRY_RSASSAV15VERIFY_ENABLED == STD_ON)

#if (CRY_RSASSAV15VERIFY_USE_CBK == STD_ON)
#include <Cry_RsaSsaV15VerifyCbk.h>
#endif

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Declaration of functions with internal linkage]==========================*/

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

/*==[Constants with external linkage]=========================================*/

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!VAR "numBarrettConfig" ="num:i(count(as:modconf('Cry')/CryRsaSsaV15Verify/CryRsaSsaV15VerifyConfig/*/CryRsaSsaV15VerifyUseBarrett[. = 'true']))"!][!//
[!LOOP "as:modconf('Cry')/CryRsaSsaV15Verify/CryRsaSsaV15VerifyConfig/*"!][!//
/** \brief RSASSA-PKCS1-v1_5 signature verification configuration
 *
 * One of the configurations of the RSASSA-PKCS1-v1_5 signature verification.
 */
CONST(Cry_RsaSsaV15VerifyConfigType, CRY_CONST) [!"node:name(.)"!] =
{
  [!"node:name(as:ref(./CryRsaSsaV15VerifyHashCfgRef))"!],
  [!IF "(node:value(./CryRsaSsaV15VerifyB64Encoded)) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!],
[!IF "($numBarrettConfig > 0)"!][!//
  [!IF "(node:value(./CryRsaSsaV15VerifyUseBarrett)) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!],
[!ENDIF!][!//
  [!IF "(node:value(./CryRsaSsaV15VerifySupportRestart)) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!]
};

[!ENDLOOP!][!//

[!IF "(CryRsaSsaV15Verify/CryRsaSsaV15VerifyUseTimeSlices = 'true') and (CryRsaSsaV15Verify/CryRsaSsaV15VerifyUseCbk = 'true')"!][!//
CONST(Cry_RsaSsaV15VerifyTimeSliceCbkType, CRY_CONST) Cry_RsaSsaV15VerifyTimeSliceConfig =
{
  &[!"node:value(CryRsaSsaV15Verify/CryRsaSsaV15TimeSlicesCbk)"!]
};
[!ENDIF!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

/*==[Definition of functions with internal linkage]===========================*/

#else /* #if(CRY_RSASSAV15VERIFY_ENABLED == STD_ON) */

typedef uint8 Cry_RsaSsaV15VerifyConfig_PrvtEmptyTranslationUnitType;

#endif /* #if(CRY_RSASSAV15VERIFY_ENABLED == STD_ON) else */
