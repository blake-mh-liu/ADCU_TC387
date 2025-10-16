/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0003,1 */
#ifndef CRY_CCMENCRYPTCONFIG_H
#define CRY_CCMENCRYPTCONFIG_H

/*==================[includes]====================================================================*/

#include <Std_Types.h>

#include <Csm.h>
#include <Cry_CCM_CommonConfig.h>

/*==================[macros]======================================================================*/

#if (defined CRY_CCM_ENC_ENABLED)
#error CRY_CCM_ENC_ENABLED is already defined
#endif
/* !LINKSTO EB_CRY_0018,1 */
[!IF "num:i(0) != num:i(count(as:modconf('Cry')/CryCcmEncrypt/CryCcmEncryptConfig/*))"!][!//
#define CRY_CCM_ENC_ENABLED STD_ON
[!ELSE!][!//
#define CRY_CCM_ENC_ENABLED STD_OFF
[!ENDIF!][!//

#if (CRY_CCM_ENC_ENABLED == STD_ON)

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[external constants]==========================================================*/

[!IF "count(as:modconf('Cry')/CryCcmEncrypt/CryCcmEncryptConfig/*) > 0"!][!//

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO EB_CRY_0023,1 */
[!LOOP "as:modconf('Cry')/CryCcmEncrypt/CryCcmEncryptConfig/*"!][!//
extern CONST(Cry_CcmCryptConfigType, CRY_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>
[!ENDIF!][!//

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CRY_CCM_ENC_ENABLED == STD_ON) */

#endif /* #ifndef CRY_CCM_ENCCONFIG_H */
