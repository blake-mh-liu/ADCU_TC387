/**
 * \file
 *
 * \brief AUTOSAR J1939Rm
 *
 * This file contains the implementation of the AUTOSAR
 * module J1939Rm.
 *
 * \version 1.1.15
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
[!CODE!]
[!AUTOSPACING!]

/*==================[inclusions]============================================*/
[!//Check if PbcfgM is not used for J1939Rm
[!VAR "usingpbcfgm" = "node:contains(node:refs(as:modconf('PbcfgM')/PbcfgMBswModules/eb-list::*/PbcfgMBswModuleRef), as:modconf('J1939Rm'))"!]
[!IF "$usingpbcfgm = 'false'"!]

  [!LOOP "variant:all()"!][!//
#undef TS_RELOCATABLE_CFG_ENABLE
#undef TS_PB_CFG_NAME
#undef TS_PB_CFG_LAYOUT_TYPE
#include "J1939Rm_[!"."!]_PBcfg.c"

  [!ENDLOOP!][!//

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal function definitions]==========================*/
[!ELSE!][!//PbcfgM is used to generate the config, this file remains empty
#include <TSCompiler.h>

/* Avoid empty translation unit according to ISO C90 */
TS_PREVENTEMPTYTRANSLATIONUNIT

[!ENDIF!][!//node:existsAndTrue(node:contains(node:refs(as:modconf('PbcfgM')/PbcfgMBswModules/eb-list::*/PbcfgMBswModuleRef), as:modconf('J1939Rm')))
/*==================[end of file]===========================================*/
[!ENDCODE!][!//
