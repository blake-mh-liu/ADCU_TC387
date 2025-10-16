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

#include <Cal_KeyDerive.h>
#include <Cal_KeyDerive_Cfg.h>

#if (CAL_KEY_DERIVE_ENABLED == TRUE)

/* !LINKSTO CAL0008, 1
 */
[!VAR "CalInclude" = "''"!][!//
[!LOOP "node:order(as:modconf('Cal')/CalKeyDerive/CalKeyDeriveConfig/*,'node:value(./CalKeyDerivePrimitiveName)')"!][!//
[!IF "$CalInclude != node:value(./CalKeyDerivePrimitiveName)"!][!//
[!VAR "CalInclude" = "node:value(./CalKeyDerivePrimitiveName)"!][!//
#include <Cpl_[!"node:value(./CalKeyDerivePrimitiveName)"!].h>
[!ENDIF!][!//
[!ENDLOOP!][!//

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

#define CAL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

CONST(Cal_KeyDeriveConfigType, CAL_CONST)
  Cal_KeyDeriveConfigurations[CAL_KEYDERIVE_CONFIG_COUNT] =
{
[!LOOP "as:modconf('Cal')/CalKeyDerive/CalKeyDeriveConfig/*"!][!//
  {
    [!"node:name(.)"!],
    &Cpl_[!"node:value(./CalKeyDerivePrimitiveName)"!]Start,
    &Cpl_[!"node:value(./CalKeyDerivePrimitiveName)"!]Update,
    &Cpl_[!"node:value(./CalKeyDerivePrimitiveName)"!]Finish,
    &([!"node:value(./CalKeyDeriveInitConfiguration)"!])
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
#else /* #if (CAL_KEY_DERIVE_ENABLED == TRUE)*/

/** Dummy definition preventing this file from being empty, if there is no KeyDerive configuration.
 */
typedef void CalPrvntEmptyTranslationUnit_t;


#endif /* #if (CAL_KEY_DERIVE_ENABLED == TRUE) #else */

/*==================[end of file]=================================================================*/

