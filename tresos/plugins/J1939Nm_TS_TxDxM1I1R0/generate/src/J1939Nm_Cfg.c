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
/* This file is generated from the configuration of J1939Nm module */

[!CODE!]
[!INCLUDE "include/J1939Nm_Vars.m"!][!//
[!AUTOSPACING!][!//
/*==================[inclusions]============================================*/

#include <J1939Nm_Cfg.h>
#include <NmStack_Types.h>

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[internal constants]====================================*/
[!SELECT "(J1939NmConfigSet/eb-list::*)"!][!//
#define J1939NM_START_SEC_VAR_INIT_8
#include <J1939Nm_MemMap.h>

#define J1939NM_STOP_SEC_VAR_INIT_8
#include <J1939Nm_MemMap.h>

#define J1939NM_START_SEC_CONST_UNSPECIFIED
#include <J1939Nm_MemMap.h>

#define J1939NM_STOP_SEC_CONST_UNSPECIFIED
#include <J1939Nm_MemMap.h>

#define J1939NM_START_SEC_VAR_INIT_UNSPECIFIED
#include <J1939Nm_MemMap.h>

#define J1939NM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <J1939Nm_MemMap.h>

#define J1939NM_START_SEC_VAR_INIT_8
#include <J1939Nm_MemMap.h>

#define J1939NM_STOP_SEC_VAR_INIT_8
#include <J1939Nm_MemMap.h>

#define J1939NM_START_SEC_CONST_8
#include <J1939Nm_MemMap.h>

CONST(uint8, J1939NM_CONST) J1939Nm_ComMChannelIDs[J1939NM_NUMBER_OF_COMM_CHANNELS] =
{
[!VAR "ChannelCount" = "'0'"!]  
[!LOOP "util:distinct(node:order(J1939NmChannel/eb-list::*))"!]
[!VAR "ChannelCount" = "$ChannelCount + 1"!] 
[!VAR "ComMChannelIdValue" = "(as:ref(J1939NmComMNetworkHandleRef)/ComMChannelId)"!]
  [!"$ComMChannelIdValue"!]U, /* Reference to [!"as:name(.)"!] ID */
[!ENDLOOP!]
[!IF "(num:i($ChannelCount) < num:i($J1939NmChannelMapToComMChannel))"!]
  [!FOR "i" = "num:i($ChannelCount)" TO "num:i($J1939NmChannelMapToComMChannel) - 1"!]
    255U,                     /* Not Used ID */
  [!ENDFOR!]
[!ENDIF!]
};

CONST(uint8, J1939NM_CONST) J1939Nm_J1939TxPduIDs[J1939NM_NUMBER_OF_CHANNELS_MAX] =
{
[!VAR "ChannelCount" = "'0'"!]  
[!LOOP "util:distinct(node:order(J1939NmChannel/eb-list::*))"!]
[!VAR "ChannelCount" = "$ChannelCount + 1"!] 
  J1939NmConf_J1939NmTxPdu_[!"as:name(node:ref(J1939NmTxPdu/J1939NmTxPduRef))"!],
[!ENDLOOP!]
[!IF "(num:i($ChannelCount) < num:i($TotalMaxChannel))"!]
  [!FOR "i" = "num:i($ChannelCount)" TO "num:i($TotalMaxChannel) - 1"!]
    255U,                     /* Not Used ID */
  [!ENDFOR!]
[!ENDIF!]
};

CONST(uint8, J1939NM_CONST) J1939Nm_J1939RxPduIDs[J1939NM_NUMBER_OF_CHANNELS_MAX] =
{
[!VAR "ChannelCount" = "'0'"!]   
[!LOOP "util:distinct(node:order(J1939NmChannel/eb-list::*))"!]
[!VAR "ChannelCount" = "$ChannelCount + 1"!] 
  J1939NmConf_J1939NmRxPdu_[!"as:name(node:ref(J1939NmRxPdu/J1939NmRxPduRef))"!],
[!ENDLOOP!]
[!IF "(num:i($ChannelCount) < num:i($TotalMaxChannel))"!]
  [!FOR "i" = "num:i($ChannelCount)" TO "num:i($TotalMaxChannel) - 1"!]
    255U,                     /* Not Used ID */
  [!ENDFOR!]
[!ENDIF!]
};

#define J1939NM_STOP_SEC_CONST_8
#include <J1939Nm_MemMap.h>

#define J1939NM_START_SEC_VAR_INIT_UNSPECIFIED
#include <J1939Nm_MemMap.h>

#define J1939NM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <J1939Nm_MemMap.h>

[!ENDSELECT!][!//

#define J1939NM_START_SEC_CONFIG_DATA_UNSPECIFIED
#include <J1939Nm_MemMap.h>

[!IF "node:exists(J1939NmGeneral/J1939NmUserCallout)"!]
/* Pointer to J1939Nm Callout function */
CONST(J1939Nm_CalloutFunctionPointerType, J1939NM_CONST) J1939NmCalloutFunctionPtr  = &[!"J1939NmGeneral/J1939NmUserCallout"!];
[!ENDIF!]

#define J1939NM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include <J1939Nm_MemMap.h>

/*==================[end of file]============================================*/
[!ENDCODE!]
