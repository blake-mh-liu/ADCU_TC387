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
#include <Cal_Hash.h>
#include <Cal_Hash_Cfg.h>

#if (CAL_HASH_ENABLED == TRUE)

/* !LINKSTO CAL0008, 1
 */
[!VAR "CalInclude" = "''"!][!//
[!LOOP "node:order(as:modconf('Cal')/CalHash/CalHashConfig/*,'node:value(./CalHashPrimitiveName)')"!][!//
  [!IF "$CalInclude != node:value(./CalHashPrimitiveName)"!][!//
    [!VAR "CalInclude" = "node:value(./CalHashPrimitiveName)"!][!//

#include <Cpl_[!"node:value(./CalHashPrimitiveName)"!].h>

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

/** \brief Hash configuration
 *
 * Struct containing the configurations of the hash service.
 */
CONST(Cal_HashConfigType, CAL_CONST) Cal_HashConfigurations[CAL_HASH_CONFIG_COUNT] =
{
[!LOOP "as:modconf('Cal')/CalHash/CalHashConfig/*"!][!//
   {
      [!"node:name(.)"!],
      &Cpl_[!"node:value(./CalHashPrimitiveName)"!]Start,
      &Cpl_[!"node:value(./CalHashPrimitiveName)"!]Update,
      &Cpl_[!"node:value(./CalHashPrimitiveName)"!]Finish,
      &([!"node:value(./CalHashInitConfiguration)"!])
   },
[!ENDLOOP!][!//
};

#define CAL_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

#else /* #if (CAL_HASH_ENABLED == TRUE) */

/** Dummy definition preventing this file from being empty, if there is no Hash configuration.
 */
typedef void CalPrvntEmptyTranslationUnit_t;


#endif /* #if (CAL_HASH_ENABLED == TRUE) 'else */

/*==[Definition of functions with external linkage]===========================*/



/*==[Definition of functions with internal linkage]===========================*/

