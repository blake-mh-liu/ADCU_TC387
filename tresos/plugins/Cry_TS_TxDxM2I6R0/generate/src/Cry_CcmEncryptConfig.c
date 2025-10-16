/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0006,1 */

/*==================[includes]====================================================================*/

#include <Cry_CcmEncryptConfig.h>

#if (CRY_CCM_ENC_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

[!IF "count(as:modconf('Cry')/CryCcmEncrypt/CryCcmEncryptConfig/*) > 0"!][!//
#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!LOOP "as:modconf('Cry')/CryCcmEncrypt/CryCcmEncryptConfig/*"!][!//
CONST(Cry_CcmCryptConfigType, CRY_CONST) [!"node:name(.)"!] =
{
  [!"node:value(./CryCCMAdataLen)"!]U,
  [!"node:value(./CryCCMMacLength)"!],
  [!"node:value(./CryCCMLengthFieldSize)"!],
  [!"node:name(as:ref(./CryCcmEncryptSymBlockEncryptCfgRef))"!]
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

#else /* #if (CRY_CCM_ENC_ENABLED == STD_ON) */

typedef uint8 Cry_CcmEncryptConfig_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_CCM_ENC_ENABLED == STD_ON) #else */

/*==================[end of file]=================================================================*/
