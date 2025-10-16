/* --------{ EB Automotive C Source File }-------- */

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Cry_MD5Config.h>

#if (CRY_MD5_ENABLED == STD_ON)

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Declaration of functions with internal linkage]==========================*/

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

/*==[Constants with external linkage]=========================================*/

#define CRY_START_SEC_CONST_16
#include <MemMap.h>

[!VAR "CryMD5ConfigIndex" = "'0'"!][!//
[!LOOP "as:modconf('Cry')/CryMD5/CryMD5Config/*"!][!//

CONST(Cry_MD5_ConfigType, CRY_CONST) [!"node:name(.)"!] =
  (Cry_MD5_ConfigType) [!"num:i($CryMD5ConfigIndex)"!]U;

[!VAR "CryMD5ConfigIndex" = "$CryMD5ConfigIndex + 1"!][!//
[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_16
#include <MemMap.h>

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#else /* #if (CRY_MD5_ENABLED == STD_ON) */


/** Dummy definition preventing this file from being empty, if there is no MD5 configuration.
 */
typedef void Cry_MD5Config_PrvtEmptyTranslationUnitType;


#endif /* #if (CRY_MD5_ENABLED == STD_ON) #else */

