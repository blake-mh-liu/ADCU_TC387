/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0006,1 */

/*==================[includes]====================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm.h>
#include <Cry_CVCPublicKeyExtractConfig.h>

#if (CRY_CVCPUBLICKEYEXTRACT_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!LOOP "as:modconf('Cry')/CryCVCPublicKeyExtract/CryCVCPublicKeyExtractConfig/*"!][!//

CONST(Cry_CVCPublicKeyExtractConfigType, CRY_CONST) [!"node:name(.)"!] =
{
[!IF "(node:value(./CryCVCPublicKeyExtractEnableCertChain )) = 'true'"!][!//
    [!"node:name(as:ref(./CryCVCPublicKeyExtractCfgRef))"!],
    TRUE
[!ELSE!][!//
    CRY_CVCPUBLICKEYEXTRACT_INVALID_CFG,
    FALSE
[!ENDIF!][!//
};

[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

/*==================[internal function definitions]===============================================*/

#else /* #if (CRY_CVCPUBLICKEYEXTRACT_ENABLED == STD_ON) */

typedef uint8 Cry_CVCPublicKeyExtract_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_CVCPUBLICKEYEXTRACT_ENABLED == STD_ON) #else */

/*==================[end of file]=================================================================*/
