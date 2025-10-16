/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0006,1 */

/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm_RandomGenerate.h>
#include <Csm.h>
#include <Cry_SSGGenerate.h>        /* !LINKSTO EB_CRY_0007,1 */
#include <Cry_SSGGenerateConfig.h>
#include <Cry_SSGStateConfig.h>
#include <Cry_Common.h>

#if (CRY_SSGGENERATE_ENABLED == STD_ON)

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Declaration of functions with internal linkage]==========================*/

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

/*==[Constants with external linkage]=========================================*/

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief SSSG Generate Configuration
 **
 ** One of the configurations of the self shrinking generator
 **
 **/

[!VAR "CrySSGGenerateConfigIndex" = "'0'"!][!//
[!LOOP "as:modconf('Cry')/CrySSGGenerate/CrySSGGenerateConfig/*"!][!//
CONST(Cry_SSGGenerateConfigType, CRY_CONST) [!"node:name(.)"!] =
{
   (P2VAR(uint8, AUTOMATIC, CRY_VAR)) [!"node:name(as:ref(./CrySSGRandomStateRef))"!],
   [!"node:value(as:ref(./CrySSGRandomStateRef)/CrySSGStateSize)"!],
   [!"num:i($CrySSGGenerateConfigIndex)"!]
};

[!VAR "CrySSGGenerateConfigIndex" = "$CrySSGGenerateConfigIndex + 1"!][!//
[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#else /* #if (CRY_SSGGENERATE_ENABLED == STD_ON) */

typedef uint8 Cry_SSGGenerateConfig_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_SSGGENERATE_ENABLED == STD_ON) #else */
