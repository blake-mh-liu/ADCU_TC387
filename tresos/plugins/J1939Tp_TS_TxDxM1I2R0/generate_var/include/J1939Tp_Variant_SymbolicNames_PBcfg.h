/**
 * \file
 *
 * \brief AUTOSAR J1939Tp
 *
 * This file contains the implementation of the AUTOSAR
 * module J1939Tp.
 *
 * \version 1.2.14
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
  */!][!VAR "J1939TP_VARIANT_SUFIX"="concat('_',$postBuildVariant)"!]

#ifndef J1939TP_SYMBOLICNAMES_[!"$postBuildVariant"!]_PBCFG_H
#define J1939TP_SYMBOLICNAMES_[!"$postBuildVariant"!]_PBCFG_H
[!ELSE!]
  [!/* Current PB variant Sufix
  */!][!VAR "J1939TP_VARIANT_SUFIX"="string("")"!]
#ifndef J1939TP_SYMBOLICNAMES_PBCFG_H
#define J1939TP_SYMBOLICNAMES_PBCFG_H
[!ENDIF!]

/*==================[includes]===============================================*/
/*==================[macros]=================================================*/

/*------------------[symbolic name values]----------------------------------*/

[!LOOP "as:modconf('J1939Tp')[1]/J1939TpConfiguration/eb-list::*[1]/J1939TpManagerNetwork/eb-list::*"!]

#if (defined J1939TP_PROVIDE_LEGACY_SYMBOLIC_NAMES)

#if (defined J1939Tp_[!"as:name(.)"!][!"$J1939TP_VARIANT_SUFIX"!] )
#error J1939Tp_[!"as:name(.)"!][!"$J1939TP_VARIANT_SUFIX"!] is already defined
#endif /* #if (defined J1939Tp_[!"as:name(.)"!][!"$J1939TP_VARIANT_SUFIX"!] ) */

/** \brief Export symbolic name value */
#define J1939Tp_[!"as:name(.)"!][!"$J1939TP_VARIANT_SUFIX"!] [!"as:ref(J1939TpComMNetworkHandleRef)/ComMChannelId"!]U

#endif /* #if (defined J1939TP_PROVIDE_LEGACY_SYMBOLIC_NAMES) */

[!ENDLOOP!]

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
#endif /* ifndef J1939TP_SYMBOLICNAMES_[!"$postBuildVariant"!]_PBCFG_H */
[!ELSE!]
#endif /* ifndef J1939TP_SYMBOLICNAMES_PBCFG_H */
[!ENDIF!]
/*==================[end of file]============================================*/
[!ENDCODE!]
