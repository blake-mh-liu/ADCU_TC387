/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0003,1 */

#ifndef CRY_AES_DECRYPTCONFIG_H
#define CRY_AES_DECRYPTCONFIG_H

/*==================[includes]====================================================================*/

#include <Std_Types.h>

#include <Cry_AES_CommonConfig.h>

/*==================[macros]======================================================================*/

#if (defined CRY_AES_DECRYPT_ENABLED)
#error CRY_AES_DECRYPT_ENABLED is already defined
#endif
/* !LINKSTO EB_CRY_0018,1 */
[!IF "num:i(0) != num:i(count(as:modconf('Cry')/CryAESDecrypt/CryAESDecryptConfig/*))"!][!//
#define CRY_AES_DECRYPT_ENABLED STD_ON
[!ELSE!][!//
#define CRY_AES_DECRYPT_ENABLED STD_OFF
[!ENDIF!][!//

#if (CRY_AES_DECRYPT_ENABLED == STD_ON)
  
#if (defined PZ1A_CRY_OPTIM_AES_DECRY_EANABLED)
#error PZ1A_CRY_OPTIM_AES_DECRY_EANABLED is already defined
#endif

[!IF "(node:value(as:modconf('Cry')/CryAESDecrypt/PZ1ACryOptimDecry)) = 'true'"!][!//
#define PZ1A_CRY_OPTIM_AES_DECRY_EANABLED STD_ON
[!ELSE!][!//
#define PZ1A_CRY_OPTIM_AES_DECRY_EANABLED STD_OFF
[!ENDIF!][!//

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[external constants]==========================================================*/

[!IF "count(as:modconf('Cry')/CryAESDecrypt/CryAESDecryptConfig/*) > 0"!][!//

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO EB_CRY_0023,1 */

[!LOOP "as:modconf('Cry')/CryAESDecrypt/CryAESDecryptConfig/*"!][!//
extern CONST(Cry_AES_ConfigType, CRY_CONST) [!"node:name(.)"!];
[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!ELSE!][!//

[!ENDIF!][!//

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CRY_AES_DECRYPT_ENABLED == STD_ON) */

#endif /* #ifndef CRY_AES_DECRYPTCONFIG_H */
