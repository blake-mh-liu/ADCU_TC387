/**
 * \file
 *
 * \brief AUTOSAR Cal
 *
 * This file contains the implementation of the AUTOSAR
 * module Cal.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==[Includes]================================================================*/

#include <Cal_Types.h>

#include <Cal_Random.h>
#include <Cal_Random_Cfg.h>

/* !LINKSTO CAL0008, 1
 */
[!VAR "CalInclude" = "''"!][!//
[!LOOP "node:order(as:modconf('Cal')/CalRandomGenerate/CalRandomGenerateConfig/*,'node:value(./CalRandomGeneratePrimitiveName)')"!][!//
[!IF "$CalInclude != node:value(./CalRandomGeneratePrimitiveName)"!][!//
[!VAR "CalInclude" = "node:value(./CalRandomGeneratePrimitiveName)"!][!//
#include <Cpl_[!"node:value(./CalRandomGeneratePrimitiveName)"!].h>
[!ENDIF!][!//
[!ENDLOOP!][!//

[!LOOP "node:order(as:modconf('Cal')/CalRandomSeed/CalRandomSeedConfig/*,'node:value(./CalRandomSeedPrimitiveName)')"!][!//
[!IF "$CalInclude != node:value(./CalRandomSeedPrimitiveName)"!][!//
[!VAR "CalInclude" = "node:value(./CalRandomSeedPrimitiveName)"!][!//
#include <Cpl_[!"node:value(./CalRandomSeedPrimitiveName)"!].h>
[!ENDIF!][!//
[!ENDLOOP!][!//

/*==[Macros]==================================================================*/



/*==[Types]===================================================================*/



/*==[Declaration of functions with internal linkage]==========================*/



/*==[Constants with internal linkage]=========================================*/



/*==[Variables with internal linkage]=========================================*/



/*==[Variables with external linkage]=========================================*/



/*==[Constants with external linkage]=========================================*/

#define CAL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

#if (CAL_RANDOMSEED_ENABLED == TRUE)

CONST(Cal_RandomSeedConfigType, CAL_CONST)
  Cal_RandomSeedConfigurations[CAL_RANDOMSEED_CONFIG_COUNT] =
{
[!LOOP "as:modconf('Cal')/CalRandomSeed/CalRandomSeedConfig/*"!][!//
  {
    [!"node:name(.)"!],
    &Cpl_[!"node:value(./CalRandomSeedPrimitiveName)"!]Start,
    &Cpl_[!"node:value(./CalRandomSeedPrimitiveName)"!]Update,
    &Cpl_[!"node:value(./CalRandomSeedPrimitiveName)"!]Finish,
    &([!"node:value(./CalRandomSeedInitConfiguration)"!])
},
[!ENDLOOP!][!//
};
#endif /* #if (CAL_RANDOMSEED_ENABLED == TRUE) */

#if (CAL_RANDOMGEN_ENABLED == TRUE)

CONST(Cal_RandomGenerateConfigType, CAL_CONST)
  Cal_RandomGenConfigurations[CAL_RANDOMGEN_CONFIG_COUNT] =
{
[!LOOP "as:modconf('Cal')/CalRandomGenerate/CalRandomGenerateConfig/*"!][!//
  {
    [!"node:name(.)"!],
    &Cpl_[!"node:value(./CalRandomGeneratePrimitiveName)"!],
    &([!"node:value(./CalRandomGenerateInitConfiguration)"!])
  },
[!ENDLOOP!][!//
};
#endif /* #if (CAL_RANDOMGEN_ENABLED == TRUE) */

#if ((CAL_RANDOMGEN_ENABLED == FALSE) && (CAL_RANDOMSEED_ENABLED == FALSE))

/** Dummy definition preventing this file from being empty, if there is no Random
 *  configuration.
 */
typedef void CalPrvntEmptyTranslationUnit_t;

#endif /*#if ((CAL_RANDOMGEN_ENABLED == FALSE) && (CAL_RANDOMSEED_ENABLED == FALSE))*/

#define CAL_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>



/*==[Definition of functions with external linkage]===========================*/


/*==[Definition of functions with internal linkage]===========================*/

