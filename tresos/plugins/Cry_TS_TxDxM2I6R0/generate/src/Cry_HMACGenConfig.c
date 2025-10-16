/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0006,1 */

/*==[Includes]================================================================*/

#include <Std_Types.h>
#include <Csm_Types.h>
#include <Csm_Hash.h>
#include <Cry_HMAC.h>
#include <Cry_HMACGen.h>  /* !LINKSTO EB_CRY_0007,1 */

#if (CRY_HMAC_GEN_ENABLED == TRUE)

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
 * \brief HMAC generation configuration
 *
 * One of the configurations of the HMAC generation.
 *
 */

[!LOOP "as:modconf('Cry')/CryHMACGen/CryHMACGenConfig/*"!][!//
CONST(Cry_HMACGenConfigType, CRY_CONST) [!"node:name(.)"!] =
{
   [!"node:name(as:ref(./CryHMACGenHashCfgRef))"!]
};

[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

/*==[Definition of functions with internal linkage]===========================*/

#else /* #if (CRY_HMAC_GEN_ENABLED == TRUE) */

#define CRY_START_SEC_CONST_8
#include <MemMap.h>

typedef uint8 Cry_HMACGenConfig_PrvtEmptyTranslationUnitType;

#define CRY_STOP_SEC_CONST_8
#include <MemMap.h>

#endif /* #if (CRY_HMAC_GEN_ENABLED == TRUE) #else */
