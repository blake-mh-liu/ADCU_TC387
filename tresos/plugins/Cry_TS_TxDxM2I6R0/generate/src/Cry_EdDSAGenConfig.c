/* --------{ EB Automotive C Source File }-------- */

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm_Hash.h>
#include <Csm_Types.h>
#include <Csm_SignatureGenerate.h>

#include <Cry_LN.h>
#include <Cry_EdDSA.h>
#include <Cry_EdDSAGenConfig.h>

#if (CRY_EDDSA_GEN_ENABLED == STD_ON)

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Declaration of functions with internal linkage]==========================*/

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

/*==[Constants with external linkage]=========================================*/

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

[!LOOP "as:modconf('Cry')/CryEdDSAGen/CryEdDSAGenConfig/*"!][!//
CONST(Cry_EdDSAGenConfigType, CRY_CONST) [!"node:name(.)"!] =
{
  [!"node:name(as:ref(./CryEdDSAGenHashCfgRef))"!],
  [!IF "(node:value(./CryEdDSAGenSupportRestart)) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!],
  /* !LINKSTO EB_Cry_Slicing_Cfg_CryEdDSASignatureGenerateTimeSlices,1 */
[!IF "node:exists(./CryEdDSAGenNumberOfTimeSlices)"!][!//
  [!"node:value(./CryEdDSAGenNumberOfTimeSlices)"!]U
[!ELSE!][!//
  1U
[!ENDIF!][!//
};

[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

/*==[Definition of functions with internal linkage]===========================*/

#else  /* #if (CRY_EDDSA_GEN_ENABLED == STD_ON) */

typedef uint8 Cry_EdDSAGenConfigDummyType_PrvtEmptyTranslationUnitType;
#endif /* #if (CRY_EDDSA_GEN_ENABLED == STD_ON) */
