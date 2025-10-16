/**
 * \file
 *
 * \brief AUTOSAR J1939Nm
 *
 * This file contains the implementation of the AUTOSAR
 * module J1939Nm.
 *
 * \version 1.1.13
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
[!CODE!]
[!AUTOSPACING!]

[!IF "var:defined('postBuildVariant')"!]
  [!/* Current PB variant Sufix
  */!][!VAR "J1939NM_VARIANT_SUFIX"="concat('_',$postBuildVariant)"!]

#ifndef J1939NM_SYMBOLICNAMES_[!"$postBuildVariant"!]_PBCFG_H
#define J1939NM_SYMBOLICNAMES_[!"$postBuildVariant"!]_PBCFG_H
[!ELSE!]
  [!/* Current PB variant Sufix
  */!][!VAR "J1939NM_VARIANT_SUFIX"="string("")"!]
#ifndef J1939NM_SYMBOLICNAMES_PBCFG_H
#define J1939NM_SYMBOLICNAMES_PBCFG_H
[!ENDIF!]

/*==================[includes]===============================================*/
/*==================[macros]=================================================*/

/*------------------[symbolic name values]----------------------------------*/

[!VAR "J1939NmMaxChannel" = "num:integer(count(J1939NmConfigSet/eb-list::*[1]/J1939NmChannel/eb-list::*))"!]


#if (defined J1939NM_PROVIDE_LEGACY_SYMBOLIC_NAMES)

#if (defined J1939Nm_[!"node:name(.)"!][!"$J1939NM_VARIANT_SUFIX"!] )
#error J1939Nm_[!"node:name(.)"!][!"$J1939NM_VARIANT_SUFIX"!] is already defined
#endif /* #if (defined J1939Nm_[!"node:name(.)"!][!"$J1939NM_VARIANT_SUFIX"!] ) */

/** \brief Export symbolic name value */
#define J1939NM[!"$J1939NM_VARIANT_SUFIX"!]_CHANNEL_NUMB  [!"$J1939NmMaxChannel"!]U
#endif /* #if (defined J1939NM_PROVIDE_LEGACY_SYMBOLIC_NAMES) */


/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/
[!IF "var:defined('postBuildVariant')"!]
#endif /* ifndef J1939NM_SYMBOLICNAMES_[!"$postBuildVariant"!]_PBCFG_H */
[!ELSE!]
#endif /* ifndef J1939NM_SYMBOLICNAMES_PBCFG_H */
[!ENDIF!]
/*==================[end of file]============================================*/
[!ENDCODE!]
