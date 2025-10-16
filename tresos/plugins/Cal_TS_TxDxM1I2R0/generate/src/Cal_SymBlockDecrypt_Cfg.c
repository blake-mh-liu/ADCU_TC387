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

#include <Cal_SymBlockDecrypt.h>
#include <Cal_SymBlockDecrypt_Cfg.h>

#if (CAL_SYMBLOCKDECRYPT_ENABLED == TRUE)

/* !LINKSTO CAL0008, 1
 */
[!VAR "CalInclude" = "''"!][!//
[!LOOP "node:order(as:modconf('Cal')/CalSymBlockDecrypt/CalSymBlockDecryptConfig/*,'node:value(./CalSymBlockDecryptPrimitiveName)')"!][!//
[!IF "$CalInclude != node:value(./CalSymBlockDecryptPrimitiveName)"!][!//
[!VAR "CalInclude" = "node:value(./CalSymBlockDecryptPrimitiveName)"!][!//
#include <Cpl_[!"node:value(./CalSymBlockDecryptPrimitiveName)"!].h>
[!ENDIF!][!//
[!ENDLOOP!][!//

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

#define CAL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

CONST(Cal_SymBlockDecryptConfigType, CAL_CONST)
  Cal_SymBlockDecConfigurations[CAL_SYMBLOCKDECRYPT_CONFIG_COUNT] =
{
[!LOOP "as:modconf('Cal')/CalSymBlockDecrypt/CalSymBlockDecryptConfig/*"!][!//
  {
    [!"node:name(.)"!],
    &Cpl_[!"node:value(./CalSymBlockDecryptPrimitiveName)"!]Start,
    &Cpl_[!"node:value(./CalSymBlockDecryptPrimitiveName)"!]Update,
    &Cpl_[!"node:value(./CalSymBlockDecryptPrimitiveName)"!]Finish,
    &([!"node:value(./CalSymBlockDecryptInitConfiguration)"!])
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

#else /* #if (CAL_SYMBLOCKDECRYPT_ENABLED == TRUE) */

/** Dummy definition preventing this file from being empty, if there is no SymBlockDecrypt
 *  configuration.
 */
typedef void CalPrvntEmptyTranslationUnit_t;


#endif /* #if (CAL_SYMBLOCKDECRYPT_ENABLED == TRUE) #else */


/*==================[end of file]=================================================================*/

