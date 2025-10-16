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

#include <Cal_AsymPublicKeyExtract.h>
#include <Cal_AsymPublicKeyExtract_Cfg.h>

#if (CAL_ASYM_PUB_KEY_EXTRACT_ENABLED == TRUE)

/* !LINKSTO CAL0008, 1
 */
[!VAR "CalInclude" = "''"!][!//
[!LOOP "node:order(as:modconf('Cal')/CalAsymPublicKeyExtract/CalAsymPublicKeyExtractConfig/*,'node:value(./CalAsymPublicKeyExtractPrimitiveName)')"!][!//
[!IF "$CalInclude != node:value(./CalAsymPublicKeyExtractPrimitiveName)"!][!//
[!VAR "CalInclude" = "node:value(./CalAsymPublicKeyExtractPrimitiveName)"!][!//
#include <Cpl_[!"node:value(./CalAsymPublicKeyExtractPrimitiveName)"!].h>
[!ENDIF!][!//
[!ENDLOOP!][!//

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

#define CAL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

CONST(Cal_AsymPublicKeyExtractConfigType, CAL_CONST)
  Cal_AsymPublicKeyExtractConfigs[CAL_ASYMPUBKEYEXTRACT_CFG_COUNT] =
{
[!LOOP "as:modconf('Cal')/CalAsymPublicKeyExtract/CalAsymPublicKeyExtractConfig/*"!][!//
  {
    [!"node:name(.)"!],
    &Cpl_[!"node:value(./CalAsymPublicKeyExtractPrimitiveName)"!]Start,
    &Cpl_[!"node:value(./CalAsymPublicKeyExtractPrimitiveName)"!]Update,
    &Cpl_[!"node:value(./CalAsymPublicKeyExtractPrimitiveName)"!]Finish,
    &([!"node:value(./CalAsymPublicKeyExtractInitConfiguration)"!])
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
#else /* #if (CAL_ASYM_PUB_KEY_EXTRACT_ENABLED == TRUE) */

/** Dummy definition preventing this file from being empty, if there is no AsymPublicKeyExtract
 * configuration.
 */
typedef void CalPrvntEmptyTranslationUnit_t;


#endif /* #if (CAL_ASYM_PUB_KEY_EXTRACT_ENABLED == TRUE) #else */

/*==================[end of file]=================================================================*/

