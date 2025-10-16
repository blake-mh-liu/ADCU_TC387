/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0006,1 */

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm_Hash.h>
#include <Csm.h>

#include <Cry_SHA1.h>
#include <Cry_Common.h>

#if (CRY_SHA1_ENABLED == STD_ON)

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Declaration of functions with internal linkage]==========================*/

/*==[Constants with internal linkage]=========================================*/

#define CRY_START_SEC_CONST_8
#include <MemMap.h>

/** \brief The algorithm identifier
 **
 ** This constant contains the algorithm identifier for each SHA1 configuration.
 **/
[!LOOP "as:modconf('Cry')/CrySHA1/CrySHA1Config/*"!][!//

static CONST(uint8, CRY_CONST) [!"node:name(.)"!]_AlgorithmId[] = { [!"node:value(./CrySHA1Type)"!]_ALGORITHM_ID };

[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_8
#include <MemMap.h>

/*==[Variables with internal linkage]=========================================*/

/*==[Constants with external linkage]=========================================*/

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief SHA1 Configuration
 **
 ** One of the configurations of the SHA1 computation
 **/

[!LOOP "as:modconf('Cry')/CrySHA1/CrySHA1Config/*"!][!//
CONST(Cry_SHAConfigType, CRY_CONST) [!"node:name(.)"!] =
{
  sizeof([!"node:name(.)"!]_AlgorithmId),
  CRY_SHA1_HASH_LEN_BYTES,
  [!"node:name(.)"!]_AlgorithmId,
[!IF "as:modconf('Cry')/CryGeneral/CrySHAOneAndTwoImplementation = 'CRY_SHAONEANDTWO_INTERRUPTABLE'"!][!//
  [!"node:value(CrySHA1IterationsPerMain)"!]U,
[!ENDIF!][!//
  FALSE
};
[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#else /* #if (CRY_SHA1_ENABLED == STD_ON) */

typedef uint8 Cry_SHA1Config_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_SHA1_ENABLED == STD_ON) #else */
