/* --------{ EB Automotive C Source File }-------- */

#ifndef CRY_MD5CONFIG_H
#define CRY_MD5CONFIG_H


/*==[Includes]====================================================================================*/

#include <Std_Types.h>

/*==[Macros]======================================================================================*/

#if (defined CRY_MD5_ENABLED)
#error CRY_MD5_ENABLED is already defined
#endif
[!IF "num:i(0) != num:i(count(as:modconf('Cry')/CryMD5/CryMD5Config/*))"!][!//
#define CRY_MD5_ENABLED STD_ON
[!ELSE!][!//
#define CRY_MD5_ENABLED STD_OFF
[!ENDIF!][!//

#if (CRY_MD5_ENABLED == STD_ON)

#if (defined CRY_MD5_IMMEDIATE_RESTART_ENABLED)
#error CRY_MD5_IMMEDIATE_RESTART_ENABLED is already defined
#endif
/** \brief Flag to indicate if the immediate restart of the service regardless of the configuration ID is enabled. */
[!IF "node:exists(as:modconf('Csm')[1]/CsmHash/CsmHashImmediateRestart)"!][!//
[!IF "(node:value(as:modconf('Cry')/CryMD5/CryMD5ImmediateRestartEnabled)) = 'true'"!][!//
#define CRY_MD5_IMMEDIATE_RESTART_ENABLED STD_ON
[!ELSE!][!//
#define CRY_MD5_IMMEDIATE_RESTART_ENABLED STD_OFF
[!ENDIF!][!//
[!ELSE!][!//
#define CRY_MD5_IMMEDIATE_RESTART_ENABLED STD_OFF
[!ENDIF!][!//

/*==[Types]=======================================================================================*/

/** \brief MD5 Configuration type
 */
typedef uint16 Cry_MD5_ConfigType;

/*==[Constants with external linkage]=============================================================*/

#define CRY_START_SEC_CONST_16
#include <MemMap.h>

[!LOOP "as:modconf('Cry')/CryMD5/CryMD5Config/*"!][!//
/**
 * \brief MD5 Configuration Identifier
 */
extern CONST(Cry_MD5_ConfigType, CRY_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_16
#include <MemMap.h>

/*==[Variables with external linkage]=============================================================*/

/*==[Declaration of functions with external linkage]==============================================*/

#endif /* #if (CRY_MD5_ENABLED == STD_ON) */

#endif /* CRY_MD5CONFIG_H */
