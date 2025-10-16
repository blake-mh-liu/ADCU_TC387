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

#include <Cal_SymDecrypt.h>
#include <Cal_SymDecrypt_Cfg.h>

#if (CAL_SYM_DECRYPT_ENABLED == TRUE)

/* !LINKSTO CAL0008, 1
 */
[!VAR "CalInclude" = "''"!][!//
[!LOOP "node:order(as:modconf('Cal')/CalSymDecrypt/CalSymDecryptConfig/*,'node:value(./CalSymDecryptPrimitiveName)')"!][!//
[!IF "$CalInclude != node:value(./CalSymDecryptPrimitiveName)"!][!//
[!VAR "CalInclude" = "node:value(./CalSymDecryptPrimitiveName)"!][!//
#include <Cpl_[!"node:value(./CalSymDecryptPrimitiveName)"!].h>
[!ENDIF!][!//
[!ENDLOOP!][!//

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

#define CAL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief The Cal configurations for the SymDecrypt service.
*/
CONST(Cal_SymDecryptConfigType, CAL_CONST)
  Cal_SymDecryptConfigurations[CAL_SYMDECRYPT_CONFIG_COUNT] =
{
[!LOOP "as:modconf('Cal')/CalSymDecrypt/CalSymDecryptConfig/*"!][!//
  {
    [!"node:name(.)"!],
    &Cpl_[!"node:value(./CalSymDecryptPrimitiveName)"!]Start,
    &Cpl_[!"node:value(./CalSymDecryptPrimitiveName)"!]Update,
    &Cpl_[!"node:value(./CalSymDecryptPrimitiveName)"!]Finish,
    &([!"node:value(./CalSymDecryptInitConfiguration)"!])
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
#else /* #if (CAL_SYM_DECRYPT_ENABLED == TRUE) */


/** Dummy definition preventing this file from being empty, if there is no SymDecrypt
 *  configuration.
 */
typedef void CalPrvntEmptyTranslationUnit_t;


#endif /* #if (CAL_SYM_DECRYPT_ENABLED == TRUE) #else */

/*==================[end of file]=================================================================*/

