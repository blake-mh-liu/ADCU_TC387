/* --------{ EB Automotive C Source File }-------- */

/*==================[includes]====================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm.h>

#include <Cry_ExtractECPubKeyConfig.h>

#if (CRY_X_ELLIPTIC_KEY_ENABLED == TRUE)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

[!IF "count(as:modconf('Cry')/CryExtractECPubKey/CryExtractECPubKeyConfig/*) > 0"!][!//

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!LOOP "as:modconf('Cry')/CryExtractECPubKey/CryExtractECPubKeyConfig/*"!][!//
CONST(Cry_ExtractECPubKeyCfgType, CRY_CONST) [!"node:name(.)"!] =
{
  32U,
  [!"node:value(./CryEllipticCurve)"!]
};

[!ENDLOOP!][!//
[!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!ENDIF!][!//

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

/*==================[internal function definitions]===============================================*/

#else /* #if (CRY_X_ELLIPTIC_KEY_ENABLED == TRUE) */

typedef uint8 Cry_ExtractECPubKeyConfig_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_X_ELLIPTIC_KEY_ENABLED == TRUE) #else */

/*==================[end of file]=================================================================*/
