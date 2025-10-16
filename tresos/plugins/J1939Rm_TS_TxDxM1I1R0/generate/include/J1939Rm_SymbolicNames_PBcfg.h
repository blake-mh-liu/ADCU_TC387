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


#ifndef J1939RM_SYMBOLICNAMES_PBCFG_H
#define J1939RM_SYMBOLICNAMES_PBCFG_H

/*==================[includes]===============================================*/

[!LOOP "variant:all()"!][!//
#include <J1939Rm_SymbolicNames[!"."!]_PBcfg.h>
[!ENDLOOP!][!//
[!LOOP "variant:all()"!][!//
#include <J1939Rm_[!"."!]_PBcfg.h>
[!ENDLOOP!][!//
/*==================[macros]=================================================*/

/*------------------[symbolic name values]----------------------------------*/
/*Calculate maximum size of J1939RmAckQueueSize based on configured variants, for ram allocation*/
#define J1939RM_AckQueueSizeTotal_Max 0
[!LOOP "variant:all()"!][!//
#if (J1939RM_AckQueueSizeTotal_[!"."!] > J1939RM_AckQueueSizeTotal_Max)
#undef J1939RM_AckQueueSizeTotal_Max
#define J1939RM_AckQueueSizeTotal_Max  J1939RM_AckQueueSizeTotal_[!"."!]
#endif
[!ENDLOOP!][!//
/*Calculate maximum size of J1939RmRequestQueueSize based on configured variants, for ram allocation*/
#define J1939RM_RequestQueueSizeTotal_Max 0
[!LOOP "variant:all()"!][!//
#if (J1939RM_RequestQueueSizeTotal_[!"."!] > J1939RM_RequestQueueSizeTotal_Max)
#undef J1939RM_RequestQueueSizeTotal_Max
#define J1939RM_RequestQueueSizeTotal_Max  J1939RM_RequestQueueSizeTotal_[!"."!]
#endif
[!ENDLOOP!][!//
/*Calculate maximum size of J1939RmRequestTimeoutMonitors based on configured variants, for ram allocation*/
#define J1939RM_RequestTimeoutMonitorsTotal_Max 0
[!LOOP "variant:all()"!][!//
#if (J1939RM_RequestTimeoutMonitorsTotal_[!"."!] > J1939RM_RequestTimeoutMonitorsTotal_Max)
#undef J1939RM_RequestTimeoutMonitorsTotal_Max
#define J1939RM_RequestTimeoutMonitorsTotal_Max  J1939RM_RequestTimeoutMonitorsTotal_[!"."!]
#endif
[!ENDLOOP!][!//
/*Calculate maximum number of channels based on configured variants , for ram allocation*/
#define J1939RM_NrOfChannels_Max 0
[!LOOP "variant:all()"!][!//
#if (J1939RM_NrOfChannels_[!"."!] > J1939RM_NrOfChannels_Max)
#undef J1939RM_NrOfChannels_Max
#define J1939RM_NrOfChannels_Max  J1939RM_NrOfChannels_[!"."!]
#endif
[!ENDLOOP!][!//
/*Calculate maximum number of users based on configured variants , for ram allocation*/
#define J1939RM_NrOfUsers_Max 0
[!LOOP "variant:all()"!][!//
#if (J1939RM_NrOfUsers_[!"."!] > J1939RM_NrOfUsers_Max)
#undef J1939RM_NrOfUsers_Max
#define J1939RM_NrOfUsers_Max  J1939RM_NrOfUsers_[!"."!]
#endif
[!ENDLOOP!][!//
/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

#endif /* ifndef J1939RM_SYMBOLICNAMES_PBCFG_H */
/*==================[end of file]============================================*/
[!ENDCODE!]
