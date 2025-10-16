/* --------{ EB Automotive C Source File }-------- */

/* !LINKSTO EB_CRY_0006,1 */

/*==[Includes]================================================================*/

#include <Std_Types.h>

#include <Csm_Types.h>
#include <Csm_Hash.h>
#include <Csm.h>

#include <Cry_SHA2.h>
#include <Cry_Common.h>

#if (CRY_SHA2_ENABLED == STD_ON)

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Declaration of functions with internal linkage]==========================*/

/*==[Constants with internal linkage]=========================================*/

#define CRY_START_SEC_CONST_8
#include <MemMap.h>

/** \brief The algorithm identifier
 **
 ** This constant contains the algorithm identifier for each SHA2 configuration.
 **/
[!LOOP "as:modconf('Cry')/CrySHA2/CrySHA2Config/*"!][!//

static CONST(uint8, CRY_CONST) [!"node:name(.)"!]_AlgorithmId[] = { [!"node:value(./CrySHA2Type)"!]_ALGORITHM_ID };

[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_8
#include <MemMap.h>

/*==[Variables with internal linkage]=========================================*/

/*==[Constants with external linkage]=========================================*/

#define CRY_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief SHA2 Configuration
 **
 ** One of the configurations of the SHA2 computation
 **/

[!LOOP "as:modconf('Cry')/CrySHA2/CrySHA2Config/*"!][!//
CONST(Cry_SHAConfigType, CRY_CONST) [!"node:name(.)"!] =
{
  sizeof([!"node:name(.)"!]_AlgorithmId),
[!IF "(node:value(./CrySHA2Type)) = 'CRY_SHA_224'"!]
  CRY_SHA224_HASH_LEN_BYTES,
[!ELSEIF "(node:value(./CrySHA2Type)) = 'CRY_SHA_256'"!]
  CRY_SHA256_HASH_LEN_BYTES,
[!ELSEIF "(node:value(./CrySHA2Type)) = 'CRY_SHA_384'"!]
  CRY_SHA384_HASH_LEN_BYTES,
[!ELSE!]
  CRY_SHA512_HASH_LEN_BYTES,
[!ENDIF!]
  [!"node:name(.)"!]_AlgorithmId,
[!IF "as:modconf('Cry')/CryGeneral/CrySHAOneAndTwoImplementation = 'CRY_SHAONEANDTWO_INTERRUPTABLE'"!][!//
  [!"node:value(CrySHA2IterationsPerMain)"!]U,
[!ENDIF!]
  [!IF "(node:value(./CrySHA2SupportRestart)) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!]
};
[!ENDLOOP!][!//

#define CRY_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==[Variables with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#else /* #if (CRY_SHA2_ENABLED == STD_ON) */

typedef uint8 Cry_SHA2Config_PrvtEmptyTranslationUnitType;

#endif /* #if (CRY_SHA2_ENABLED == STD_ON) #else */
