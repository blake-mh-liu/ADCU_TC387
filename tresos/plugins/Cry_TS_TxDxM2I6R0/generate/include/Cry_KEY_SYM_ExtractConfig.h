/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0003,1 */

#ifndef CRY_KEY_SYM_EXTRACTCONFIG_H
#define CRY_KEY_SYM_EXTRACTCONFIG_H

/*==================[includes]====================================================================*/

#include <Std_Types.h>

/*==================[macros]======================================================================*/

#if (defined CRY_KEY_SYM_EXTRACT_ENABLED)
#error CRY_KEY_SYM_EXTRACT_ENABLED is already defined
#endif
/* !LINKSTO EB_CRY_0018,1 */
[!IF "num:i(0) != num:i(count(as:modconf('Cry')/CryKeyExtractSym/CryKeyExtractSymConfig/*))"!][!//
#define CRY_KEY_SYM_EXTRACT_ENABLED STD_ON
[!ELSE!][!//
#define CRY_KEY_SYM_EXTRACT_ENABLED STD_OFF
[!ENDIF!][!//

#if (CRY_KEY_SYM_EXTRACT_ENABLED == STD_ON)

[!VAR "CryKeyExtractSymMax" = "'0'"!][!//
[!VAR "CryKeyExtractSymTmp" = "'0'"!][!//
[!//
[!LOOP "as:modconf('Cry')/CryKeyExtractSym/CryKeyExtractSymConfig/*"!][!//
[!IF "(node:value(./CryKeyExtractSymType)) = 'CRY_KEY_SYM_128'"!][!VAR "CryKeyExtractSymTmp" = "'16'"!][!ENDIF!][!//
[!IF "(node:value(./CryKeyExtractSymType)) = 'CRY_KEY_SYM_192'"!][!VAR "CryKeyExtractSymTmp" = "'24'"!][!ENDIF!][!//
[!IF "(node:value(./CryKeyExtractSymType)) = 'CRY_KEY_SYM_256'"!][!VAR "CryKeyExtractSymTmp" = "'32'"!][!ENDIF!][!//
[!IF "$CryKeyExtractSymTmp              > $CryKeyExtractSymMax"!][!VAR "CryKeyExtractSymMax" = "$CryKeyExtractSymTmp"!][!ENDIF!][!//
[!ENDLOOP!][!//
[!//
#if (defined CRY_KEY_BUFLEN)
#error CRY_KEY_BUFLEN is already defined
#endif
#define  CRY_KEY_BUFLEN  [!"$CryKeyExtractSymMax"!]U

#if (defined CRY_SYMKEYEXTRACT_IMMEDIATE_RESTART_ENABLED)
#error CRY_SYMKEYEXTRACT_IMMEDIATE_RESTART_ENABLED is already defined
#endif
/** \brief Flag to indicate if the immediate restart of the service regardless of the configuration ID is enabled. */
[!IF "node:exists(as:modconf('Csm')[1]/CsmSymKeyExtract/CsmSymKeyExtractImmediateRestart)"!][!//
[!IF "(node:value(as:modconf('Cry')/CryKeyExtractSym/CryKeyExtractSymImmediateRestartEnabled)) = 'true'"!][!//
#define CRY_SYMKEYEXTRACT_IMMEDIATE_RESTART_ENABLED STD_ON
[!ELSE!][!//
#define CRY_SYMKEYEXTRACT_IMMEDIATE_RESTART_ENABLED STD_OFF
[!ENDIF!][!//
[!ELSE!][!//
#define CRY_SYMKEYEXTRACT_IMMEDIATE_RESTART_ENABLED STD_OFF
[!ENDIF!][!//

/*==================[type definitions]============================================================*/

/*---[enum]---------------------------------------------------------------------------------------*/

/** \brief  Type of the configured symmetrical key.
 **/
typedef enum
{
  CRY_KEY_SYM_128 = 16U,
  CRY_KEY_SYM_192 = 24U,
  CRY_KEY_SYM_256 = 32U
}
Cry_KEY_SYM_Type;

/*---[struct]-------------------------------------------------------------------------------------*/

/* !LINKSTO EB_CRY_0017,1 */
/** \brief  Configuration type for representing a configured symmetrical key extraction.
 **/
typedef struct
{
  Cry_KEY_SYM_Type typeKey;
}
Cry_KEY_SYM_ConfigType;

/*==================[external function declarations]==============================================*/

/*==================[external constants]==========================================================*/
[!IF "count(as:modconf('Cry')/CryKeyExtractSym/CryKeyExtractSymConfig/*) > 0"!][!//

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO EB_CRY_0023,1 */

[!LOOP "as:modconf('Cry')/CryKeyExtractSym/CryKeyExtractSymConfig/*"!][!//
extern CONST(Cry_KEY_SYM_ConfigType, CRY_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!ELSE!][!//

[!ENDIF!][!//
/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CRY_KEY_SYM_EXTRACT_ENABLED == STD_ON) */

#endif /* #ifndef CRY_KEY_SYM_EXTRACTCONFIG_H */
