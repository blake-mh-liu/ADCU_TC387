/**
 * \file
 *
 * \brief AUTOSAR J1939Dcm
 *
 * This file contains the implementation of the AUTOSAR
 * module J1939Dcm.
 *
 * \version 1.1.14
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
  */!][!VAR "J1939DCM_VARIANT_SUFIX"="concat('_',$postBuildVariant)"!]

#ifndef J1939DCM_SYMBOLICNAMES_[!"$postBuildVariant"!]_PBCFG_H
#define J1939DCM_SYMBOLICNAMES_[!"$postBuildVariant"!]_PBCFG_H
[!ELSE!]
  [!/* Current PB variant Sufix
  */!][!VAR "J1939DCM_VARIANT_SUFIX"="string("")"!]
#ifndef J1939DCM_SYMBOLICNAMES_PBCFG_H
#define J1939DCM_SYMBOLICNAMES_PBCFG_H
[!ENDIF!]

/*==================[includes]===============================================*/
/*==================[macros]=================================================*/

/*------------------[symbolic name values]----------------------------------*/

#if (defined J1939DCM_PROVIDE_LEGACY_SYMBOLIC_NAMES)

#if (defined J1939Dcm_[!"@name"!][!"$J1939DCM_VARIANT_SUFIX"!] )
#error J1939Dcm_[!"@name"!][!"$J1939DCM_VARIANT_SUFIX"!] is already defined
#endif /* #if (defined J1939Dcm_[!"@name"!][!"$J1939DCM_VARIANT_SUFIX"!] ) */

/** \brief Export symbolic name value */
#endif /* #if (defined J1939DCM_PROVIDE_LEGACY_SYMBOLIC_NAMES) */


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
#endif /* ifndef J1939DCM_SYMBOLICNAMES_[!"$postBuildVariant"!]_PBCFG_H */
[!ELSE!]
#endif /* ifndef J1939DCM_SYMBOLICNAMES_PBCFG_H */
[!ENDIF!]
/*==================[end of file]============================================*/
[!ENDCODE!]
