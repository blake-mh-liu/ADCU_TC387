/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0006,1 */

/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm_Hash.h>
#include <Cry_LN.h>
#include <Cry_CommonConfig.h>
#include <Cry_RsaSsaPssVerifyConfig.h>

#if(CRY_RSASSAPSSVERIFY_ENABLED == STD_ON)

#if (CRY_RSASSAPSSVERIFY_USE_CBK == STD_ON)
#include <Cry_RsaSsaPssVerifyCbk.h>
#endif

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Declaration of functions with internal linkage]==========================*/

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

/*==[Constants with external linkage]=========================================*/

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!VAR "numBarrettConfig" ="num:i(count(as:modconf('Cry')/CryRsaSsaPssVerify/CryRsaSsaPssVerifyConfig/*/CryRsaSsaPssVerifyUseBarrett[. = 'true']))"!][!//
[!LOOP "as:modconf('Cry')/CryRsaSsaPssVerify/CryRsaSsaPssVerifyConfig/*"!][!//
/** \brief RSASSA-PSS signature verification configuration
 *
 * One of the configurations of the RSASSA-PSS signature verification.
 */
CONST(Cry_RsaSsaPssVerifyConfigType, CRY_CONST) [!"node:name(.)"!] =
{
  [!"(node:value(./CryRsaSsaPssVerifySaltLength))"!]U,
  [!"node:name(as:ref(./CryRsaSsaPssVerifyHashCfgRef))"!],
  [!IF "(node:value(./CryRsaSsaPssVerifyB64Encoded)) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!],
[!IF "($numBarrettConfig > 0)"!][!//
  [!IF "(node:value(./CryRsaSsaPssVerifyUseBarrett)) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!],
[!ENDIF!][!//
  [!IF "(node:value(./CryRsaSsaPssVerifySupportRestart)) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!]
};

[!ENDLOOP!][!//

[!IF "(CryRsaSsaPssVerify/CryRsaSsaPssVerifyUseTimeSlices = 'true') and (CryRsaSsaPssVerify/CryRsaSsaPssVerifyUseCbk = 'true')"!][!//
CONST(Cry_RsaSsaPssVerifyTimeSliceCbkType, CRY_CONST) Cry_RsaSsaPssVerifyTimeSliceConfig =
{
  &[!"node:value(CryRsaSsaPssVerify/CryRsaSsaPssTimeSlicesCbk)"!]
};
[!ENDIF!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

/*==[Definition of functions with internal linkage]===========================*/

#else /* #if (CRY_RSASSAPSSVERIFY_ENABLED == STD_ON) */

/* Dummy type definition to prevent compiler warnings about empty translation units */
typedef uint8 Cry_RsaSsaPssVerifyConfig_PrvtEmptyTranslationUnitType;

#endif /* #if(CRY_RSASSAPSSVERIFY_ENABLED == STD_ON) */
