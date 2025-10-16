/* --------{ EB Automotive C Source File }-------- */

/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm_RandomGenerate.h>
#include <Csm.h>
#include <Cry_SSGStateConfig.h>
#include <Cry_Common.h>

#if (CRY_SSGSTATE_ENABLED == STD_ON)

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Declaration of functions with internal linkage]==========================*/

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

/*==[Constants with external linkage]=========================================*/

#define CRY_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

[!LOOP "as:modconf('Cry')/CrySSGState/CrySSGStateConfig/*"!][!//
VAR(Cry_SSGStateType, CRY_VAR) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CRY_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#else /* #if (CRY_SSGSTATE_ENABLED == STD_ON) */

typedef uint8 Cry_SSGState_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_SSGSTATE_ENABLED == STD_ON) #else */
