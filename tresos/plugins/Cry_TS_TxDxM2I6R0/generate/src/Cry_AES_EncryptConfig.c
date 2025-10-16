/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0006,1 */

/*==================[includes]====================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm.h>
#include <Cry_AES_EncryptConfig.h>

#if (CRY_AES_ENCRYPT_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/
[!IF "count(as:modconf('Cry')/CryAESEncrypt/CryAESEncryptConfig/*) > 0"!][!//

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!LOOP "as:modconf('Cry')/CryAESEncrypt/CryAESEncryptConfig/*"!][!//
CONST(Cry_AES_ConfigType, CRY_CONST) [!"node:name(.)"!] =
{
  [!"node:value(./CryAESEncryptType)"!]
};

[!ENDLOOP!][!//
#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>
[!ENDIF!][!//

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

/*==================[internal function definitions]===============================================*/

#else /* #if (CRY_AES_ENCRYPT_ENABLED == STD_ON) */

typedef uint8 Cry_AES_EncryptConfig_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_AES_ENCRYPT_ENABLED == STD_ON) #else */

/*==================[end of file]=================================================================*/
