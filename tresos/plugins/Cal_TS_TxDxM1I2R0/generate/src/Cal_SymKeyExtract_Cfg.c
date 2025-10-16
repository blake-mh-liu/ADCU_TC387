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

/*==================[includes]====================================================================*/

#include <Cal_Types.h>

#include <Cal_SymKeyExtract.h>
#include <Cal_SymKeyExtract_Cfg.h>

#if (CAL_SYM_KEY_EXTRACT_ENABLED == TRUE)

/* !LINKSTO CAL0008, 1
 */
[!VAR "CalInclude" = "''"!][!//
[!LOOP "node:order(as:modconf('Cal')/CalSymKeyExtract/CalSymKeyExtractConfig/*,'node:value(./CalSymKeyExtractPrimitiveName)')"!][!//
[!IF "$CalInclude != node:value(./CalSymKeyExtractPrimitiveName)"!][!//
[!VAR "CalInclude" = "node:value(./CalSymKeyExtractPrimitiveName)"!][!//
#include <Cpl_[!"node:value(./CalSymKeyExtractPrimitiveName)"!].h>
[!ENDIF!][!//
[!ENDLOOP!][!//

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

#define CAL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

CONST(Cal_SymKeyExtractConfigType, CAL_CONST)
  Cal_SymKeyExtractConfigurations[CAL_SYMKEYEX_CONFIG_COUNT] =
{
[!LOOP "as:modconf('Cal')/CalSymKeyExtract/CalSymKeyExtractConfig/*"!][!//
  {
    [!"node:name(.)"!],
    &Cpl_[!"node:value(./CalSymKeyExtractPrimitiveName)"!]Start,
    &Cpl_[!"node:value(./CalSymKeyExtractPrimitiveName)"!]Update,
    &Cpl_[!"node:value(./CalSymKeyExtractPrimitiveName)"!]Finish,
    &([!"node:value(./CalSymKeyExtractInitConfiguration)"!])
  },
[!ENDLOOP!][!//
};

#define CAL_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

/*==================[internal function definitions]===============================================*/
#else /* #if (CAL_SYM_KEY_EXTRACT_ENABLED == TRUE)*/


/** Dummy definition preventing this file from being empty, if there is no SymKeyExtract
 *  configuration.
 */
typedef void CalPrvntEmptyTranslationUnit_t;

#endif /* #if (CAL_SYM_KEY_EXTRACT_ENABLED == TRUE) #else */

/*==================[end of file]=================================================================*/

