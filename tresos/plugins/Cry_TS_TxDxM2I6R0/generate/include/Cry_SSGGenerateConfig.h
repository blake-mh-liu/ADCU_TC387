/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0003,1 */

#ifndef CRY_SSGGENERATECONFIG_H
#define CRY_SSGGENERATECONFIG_H

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm.h>

/*==[Macros]==================================================================*/

#if (defined CRY_SSGGENERATE_ENABLED)
#error CRY_SSGGENERATE_ENABLED is already defined
#endif
/* !LINKSTO EB_CRY_0018,1 */
[!IF "num:i(0) != num:i(count(as:modconf('Cry')/CrySSGGenerate/CrySSGGenerateConfig/*))"!][!//
#define CRY_SSGGENERATE_ENABLED STD_ON
[!ELSE!][!//
#define CRY_SSGGENERATE_ENABLED STD_OFF
[!ENDIF!][!//

#if (CRY_SSGGENERATE_ENABLED == STD_ON)

#if (defined CRY_SSGGENERATE_IMMEDIATE_RESTART_ENABLED)
#error CRY_SSGGENERATE_IMMEDIATE_RESTART_ENABLED is already defined
#endif
/** \brief Flag to indicate if the immediate restart of the service regardless of the configuration ID is enabled. */
[!IF "node:exists(as:modconf('Csm')[1]/CsmRandomGenerate/CsmRandomGenerateImmediateRestart)"!][!//
[!IF "(node:value(as:modconf('Cry')/CrySSGGenerate/CrySSGGenerateImmediateRestartEnabled)) = 'true'"!][!//
#define CRY_SSGGENERATE_IMMEDIATE_RESTART_ENABLED STD_ON
[!ELSE!][!//
#define CRY_SSGGENERATE_IMMEDIATE_RESTART_ENABLED STD_OFF
[!ENDIF!][!//
[!ELSE!][!//
#define CRY_SSGGENERATE_IMMEDIATE_RESTART_ENABLED STD_OFF
[!ENDIF!][!//

/*==[Types]===================================================================*/

/* !LINKSTO EB_CRY_0017,1 */
/** \brief The configuration of the SSG Generate
 **
 ** \var Cry_SSGGenerateConfigType::LfsrState
 **  \brief A pointer to the start of an array which contains a state of
 **   the linear feedback shift register which is the base for the SSG Generate
 **
 ** \var Cry_SSGGenerateConfigType::LfsrLen
 ** \brief The length in bytes of the linear shift register
 **
 ** \var Cry_SSGGenerateConfigType::CfgId
 ** \brief A number which identifies the configuration
 **
 **/
typedef struct
{
  P2VAR(uint8, TYPEDEF, CRY_APPL_DATA) LfsrState;
        uint8                          LfsrLen;
        uint8                          CfgId;
}
Cry_SSGGenerateConfigType;

/*==[Constants with external linkage]=========================================*/

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO EB_CRY_0023,1 */

[!LOOP "as:modconf('Cry')/CrySSGGenerate/CrySSGGenerateConfig/*"!][!//
extern CONST(Cry_SSGGenerateConfigType, CRY_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#endif /* #if (CRY_SSGGENERATE_ENABLED == STD_ON) */

#endif
