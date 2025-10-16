/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0006,1 */

/*==================[includes]====================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm.h>
#include <Cry_CbcPkcs7DecryptConfig.h>

#if (CRY_CBC_PKCS7_DEC_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

[!IF "count(as:modconf('Cry')/CryCbcPkcs7Decrypt/CryCbcPkcs7DecryptConfig/*) > 0"!][!//
#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!LOOP "as:modconf('Cry')/CryCbcPkcs7Decrypt/CryCbcPkcs7DecryptConfig/*"!][!//
CONST(Cry_CbcPkcs7DecryptConfigType, CRY_CONST) [!"node:name(.)"!] =
{
  [!"node:name(as:ref(./CryCbcPkcs7DecryptSymBlockDecryptCfgRef))"!]
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

#else /* #if (CRY_CBC_PKCS7_DEC_ENABLED == STD_ON) */

typedef uint8 Cry_CbcPkcs7DecryptConfig_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_CBC_PKCS7_DEC_ENABLED == STD_ON) #else */

/*==================[end of file]=================================================================*/
