/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0006,1 */

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm_Hash.h>
#include <Csm.h>

#include <Cry_SHA3.h>
#include <Cry_Common.h>

#if (CRY_SHA3_ENABLED == STD_ON)

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Declaration of functions with internal linkage]==========================*/

/*==[Constants with internal linkage]=========================================*/

#define CRY_START_SEC_CONST_8
#include <MemMap.h>

/** \brief The algorithm identifier
 **
 ** This constant contains the algorithm identifier for each SHA1 configuration.
 **
 **/
[!LOOP "as:modconf('Cry')/CrySHA3/CrySHA3Config/*"!][!//

static CONST(uint8, CRY_CONST) [!"node:name(.)"!]_AlgorithmId[] = { [!"node:value(./CrySHA3Type)"!]_ALGORITHM_ID };

[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_8
#include <MemMap.h>

/*==[Variables with internal linkage]=========================================*/

/*==[Constants with external linkage]=========================================*/

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief SHA3 Configuration
 **
 ** One of the configurations of the SHA3 computation
 **
 **/

[!LOOP "as:modconf('Cry')/CrySHA3/CrySHA3Config/*"!][!//
CONST(Cry_SHAConfigType, CRY_CONST) [!"node:name(.)"!] =
{
   sizeof([!"node:name(.)"!]_AlgorithmId),
   [!"node:value(./CrySHA3Type)"!]_HASH_LEN_BYTES,
   [!"node:name(.)"!]_AlgorithmId,
   1U,
   [!IF "(node:value(./CrySHA3SupportRestart)) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!]
};

[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#else /* #if (CRY_SHA3_ENABLED == STD_ON) */

#endif /* #if (CRY_SHA3_ENABLED == STD_ON) #else */
