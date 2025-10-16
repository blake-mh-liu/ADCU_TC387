/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0006,1 */

/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm_RandomSeed.h>
#include <Csm.h>
#include <Cry_SSGStateConfig.h>
#include <Cry_SSGSeedConfig.h>
#include <Cry_Common.h>

#if (CRY_SSGSEED_ENABLED == STD_ON)

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Declaration of functions with internal linkage]==========================*/

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

/*==[Constants with external linkage]=========================================*/

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief SSG Seed Configuration
 **
 ** One of the configurations of the self shrinking generator
 **
 **/

[!VAR "CrySSGSeedConfigIndex" = "'0'"!][!//
[!LOOP "as:modconf('Cry')/CrySSGSeed/CrySSGSeedConfig/*"!][!//
CONST(Cry_SSGSeedConfigType, CRY_CONST) [!"node:name(.)"!] =
{
   (P2VAR(uint8, AUTOMATIC, CRY_VAR)) [!"node:name(as:ref(./CrySSGRandomStateRef))"!],
   [!"node:value(as:ref(./CrySSGRandomStateRef)/CrySSGStateSize)"!],
   [!"num:i($CrySSGSeedConfigIndex)"!]
};

[!VAR "CrySSGSeedConfigIndex" = "$CrySSGSeedConfigIndex + 1"!][!//
[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#else /* #if (CRY_SSGSEED_ENABLED == STD_ON) */

typedef uint8 Cry_SSGSeedConfig_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_SSGSEED_ENABLED == STD_ON) #else */
