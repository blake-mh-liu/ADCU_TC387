/* --------{ EB Automotive C Source File }-------- */

/*==================[includes]==============================================*/
[!INCLUDE "../../generate_macros/EthTSyn_Macros.m"!][!//
/*==================[macros]================================================*/
[!IF "var:defined('postBuildVariant')"!]
[!/* Current postbuild configuration name
*/!][!VAR "initPredefinedCfgName"="concat('EthTSyn','_',$postBuildVariant,'_')"!]
#ifndef ETHTSYN_[!"text:toupper($postBuildVariant)"!]_PBCFG_H
#define ETHTSYN_[!"text:toupper($postBuildVariant)"!]_PBCFG_H
[!ELSE!]
[!/* Current postbuild name
*/!][!VAR "initPredefinedCfgName"="string("EthTSyn")"!]
#ifndef ETHTSYN_VARIANT_PBCFG_H
#define ETHTSYN_VARIANT_PBCFG_H
[!ENDIF!]

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/


/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/


#define ETHTSYN_START_SEC_CONFIG_DATA_UNSPECIFIED
#include <EthTSyn_MemMap.h>


extern CONST(EthTSyn_ConfigType, ETHTSYN_APPL_CONST) [!"concat($initPredefinedCfgName,'Config_0')"!];

#if(ETHTSYN_SWITCH_USED == STD_ON)
extern CONST(EthTSyn_SwitchConfigType, ETHTSYN_APPL_CONST) [!"concat($initPredefinedCfgName,'SwitchConfig_0')"!][[!"$SwtPortsConfigured"!]];
#endif

#define ETHTSYN_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include <EthTSyn_MemMap.h>

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* ETHTSYN_[!"text:toupper($postBuildVariant)"!]_PBCFG_H */

/*==================[end of file]===========================================*/