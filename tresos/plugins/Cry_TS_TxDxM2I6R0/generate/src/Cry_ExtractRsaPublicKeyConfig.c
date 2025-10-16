/* --------{ EB Automotive C Source File }-------- */

/*==================[includes]====================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm.h>

#include <Cry_ExtractRsaPublicKeyConfig.h>

#if (CRY_EXTRACTRSAPUBLICKEY_ENABLED == TRUE)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!LOOP "as:modconf('Cry')/CryExtractRsaPublicKey/CryExtractRsaPublicKeyConfig/*"!][!//

CONST(Cry_ExtractRsaPubKeyConfigType, CRY_CONST) [!"node:name(.)"!] =
{
  [!"node:value(./CryExtractRsaPublicKeyLength)"!]
};

[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

/*==================[internal function definitions]===============================================*/


#endif /* #if (CRY_EXTRACTRSAPUBLICKEY_ENABLED == TRUE) */


/*==================[end of file]=================================================================*/
