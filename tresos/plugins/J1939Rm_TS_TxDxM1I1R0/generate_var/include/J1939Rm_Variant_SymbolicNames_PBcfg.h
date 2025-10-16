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

[!IF "var:defined('postBuildVariant')"!]
  [!/* Current PB variant Sufix
  */!][!VAR "J1939RM_VARIANT_SUFIX"="concat('_',$postBuildVariant)"!]

#ifndef J1939RM_SYMBOLICNAMES_[!"$postBuildVariant"!]_PBCFG_H
#define J1939RM_SYMBOLICNAMES_[!"$postBuildVariant"!]_PBCFG_H
[!ELSE!]
  [!/* Current PB variant Sufix
  */!][!VAR "J1939RM_VARIANT_SUFIX"="string("")"!]
#ifndef J1939RM_SYMBOLICNAMES_PBCFG_H
#define J1939RM_SYMBOLICNAMES_PBCFG_H
[!ENDIF!]

/*==================[includes]===============================================*/
[!INCLUDE "include/J1939Rm_Vars.m"!]
/*==================[macros]=================================================*/

/*------------------[symbolic name values]----------------------------------*/
[!IF "var:defined('postBuildVariant')"!]
#define J1939RM_NrOfChannels_[!"$postBuildVariant"!]                [!"num:i(($TotalNumberOfJ1939RmChannels))"!]U
#define J1939RM_NrOfUsers_[!"$postBuildVariant"!]                   [!"num:i(($TotalNumberOfJ1939RmUser))"!]U
#define J1939RM_AckQueueSizeTotal_[!"$postBuildVariant"!]           [!"num:i(($J1939RmAckQueueSizeTotal))"!]U
#define J1939RM_RequestQueueSizeTotal_[!"$postBuildVariant"!]       [!"num:i(($J1939RmRequestQueueSizeTotal))"!]U
#define J1939RM_RequestTimeoutMonitorsTotal_[!"$postBuildVariant"!] [!"num:i(($J1939RmRequestTimeoutMonitorsTotal))"!]U
[!ENDIF!]

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
#endif /* ifndef J1939RM_SYMBOLICNAMES_[!"$postBuildVariant"!]_PBCFG_H */
[!ELSE!]
#endif /* ifndef J1939RM_SYMBOLICNAMES_PBCFG_H */
[!ENDIF!]
/*==================[end of file]============================================*/
[!ENDCODE!]
