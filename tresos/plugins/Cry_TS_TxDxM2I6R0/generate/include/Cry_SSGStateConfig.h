/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0003,1 */

#ifndef CRY_SSGSTATECONFIG_H
#define CRY_SSGSTATECONFIG_H

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm.h>

#include <Cry_Common.h>

/*==[Macros]==================================================================*/

#if (defined CRY_SSGSTATE_ENABLED)
#error CRY_SSGSTATE_ENABLED is already defined
#endif
[!IF "num:i(0) != num:i(count(as:modconf('Cry')/CrySSGState/CrySSGStateConfig/*))"!][!//
#define CRY_SSGSTATE_ENABLED STD_ON
[!ELSE!][!//
#define CRY_SSGSTATE_ENABLED STD_OFF
[!ENDIF!][!//

#if (CRY_SSGSTATE_ENABLED == STD_ON)

/*==[Types]===================================================================*/

[!VAR "CrySSGStateMaxLength" = "1"!][!//
[!LOOP "as:modconf('Cry')/CrySSGState/CrySSGStateConfig/*"!][!//
[!IF "($CrySSGStateMaxLength < num:i(node:value(./CrySSGStateSize)))"!][!//
  [!VAR "CrySSGStateMaxLength" = "num:i(node:value(./CrySSGStateSize))"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//

typedef uint8 Cry_SSGStateType[[!"num:i($CrySSGStateMaxLength)"!]];

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

#define CRY_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO EB_CRY_0023,1 */

[!LOOP "as:modconf('Cry')/CrySSGState/CrySSGStateConfig/*"!][!//
extern VAR(Cry_SSGStateType, CRY_VAR) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CRY_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/*==[Declaration of functions with external linkage]==========================*/

#endif /* #if (CRY_SSG_ENABLED == STD_ON) */

#endif
