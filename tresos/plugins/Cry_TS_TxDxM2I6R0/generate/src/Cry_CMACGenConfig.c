/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0006,1 */

/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Csm.h>
#include <Cry_CMAC.h>
#include <Cry_CMACGen.h>  /* !LINKSTO EB_CRY_0007,1 */

#if (CRY_CMAC_GEN_ENABLED == STD_ON)

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Declaration of functions with internal linkage]==========================*/

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

/*==[Constants with external linkage]=========================================*/

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/**
 *
 * \brief CMAC generation configuration
 *
 * One of the configurations of the CMAC generation.
 *
 */

[!LOOP "as:modconf('Cry')/CryCMACGen/CryCMACGenConfig/*"!][!//
CONST(Cry_CMACGenConfigType, CRY_CONST) [!"node:name(.)"!] =
{
  [!"node:name(as:ref(./CryCMACGenSymBlockEncryptCfgRef))"!],
[!IF "CryCMACGenType = 'CMAC'"!][!//
  CRY_CMAC_TYPE_CMAC
[!ELSE!][!//
  CRY_CMAC_TYPE_OMAC2
[!ENDIF!][!//
};

[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

/*==[Definition of functions with internal linkage]===========================*/

#else /* #if (CRY_CMAC_GEN_ENABLED == STD_ON) */

typedef uint8 Cry_CMACGenConfig_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_CMAC_GEN_ENABLED == STD_ON) #else */
