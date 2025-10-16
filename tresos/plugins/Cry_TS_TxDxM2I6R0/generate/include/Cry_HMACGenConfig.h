/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0003,1 */

#ifndef CRY_HMAC_G_CFG_H
#define CRY_HMAC_G_CFG_H

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm.h>

#include <Csm_Hash.h>

/*==[Macros]==================================================================*/

#if (defined CRY_HMAC_GEN_ENABLED)
#error CRY_HMAC_GEN_ENABLED is already defined
#endif
/* !LINKSTO EB_CRY_0018,1 */
[!IF "num:i(0) != num:i(count(as:modconf('Cry')/CryHMACGen/CryHMACGenConfig/*))"!][!//
#define CRY_HMAC_GEN_ENABLED TRUE
[!ELSE!][!//
#define CRY_HMAC_GEN_ENABLED FALSE
[!ENDIF!][!//

#if (CRY_HMAC_GEN_ENABLED == TRUE)

#if (defined CRY_HMAC_GEN_IMMEDIATE_RESTART_ENABLED)
#error CRY_HMAC_GEN_IMMEDIATE_RESTART_ENABLED is already defined
#endif
/** \brief Flag to indicate if the immediate restart of the service regardless of the configuration ID is enabled. */
[!IF "node:exists(as:modconf('Csm')[1]/CsmMacGenerate/CsmMacGenerateImmediateRestart)"!][!//
[!IF "(node:value(as:modconf('Cry')/CryHMACGen/CryHMACGenImmediateRestartEnabled)) = 'true'"!][!//
#define CRY_HMAC_GEN_IMMEDIATE_RESTART_ENABLED STD_ON
[!ELSE!][!//
#define CRY_HMAC_GEN_IMMEDIATE_RESTART_ENABLED STD_OFF
[!ENDIF!][!//
[!ELSE!][!//
#define CRY_HMAC_GEN_IMMEDIATE_RESTART_ENABLED STD_OFF
[!ENDIF!][!//

/*==[Types]===================================================================*/

/* !LINKSTO EB_CRY_0017,1 */
/**
 *
 * \struct Cry_HMACGenConfigType
 * \brief The configuration of the HMAC generation
 *
 *
 * \var Cry_HMACGenConfigType::HashCfg
 * \brief The configuration of the underlying hash algorithm.
 */
typedef struct
{
   Csm_ConfigIdType HashCfg;
}
Cry_HMACGenConfigType;

/*==[Constants with external linkage]=========================================*/

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO EB_CRY_0023,1 */

[!LOOP "as:modconf('Cry')/CryHMACGen/CryHMACGenConfig/*"!][!//
extern CONST(Cry_HMACGenConfigType, CRY_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==[Variables with external linkage]=========================================*/

/*==[Declaration of functions with external linkage]==========================*/

#endif /* #if (CRY_HMAC_GEN_ENABLED == TRUE) */

#endif /* CRY_HMAC_G_CFG_H */
