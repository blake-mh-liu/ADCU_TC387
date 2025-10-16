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
/* This file generated from the configuration of J1939Tp module. */

[!CODE!]
[!INCLUDE "J1939Tp_Vars.m"!]

#ifndef J1939TP_CFG_H
#define J1939TP_CFG_H
/*==================[includes]===============================================*/

#include <J1939Tp_Typedefs.h>
#include <J1939Tp_Types_Int.h>

/*==================[macros]================================================*/
/* Public Macro Definitions */

#if (defined J1939Tp_TX_CHANNAEL_NUMB)
#error J1939Tp_TX_CHANNAEL_NUMB is already defined
#endif
#define J1939Tp_TX_CHANNAEL_NUMB  [!"num:i(count(as:modconf('J1939Tp')[1]/J1939TpConfiguration/eb-list::*[1]/J1939TpTxChannel/eb-list::*/J1939TpTxPg/eb-list::*))"!]U


#if (defined J1939TP_CFG_SIGNATURE)
#error J1939TP_CFG_SIGNATURE is already defined
#endif

#define J1939TP_CFG_SIGNATURE [!"asc:getConfigSignature(as:modconf('J1939Tp')[1]//eb-choice::*[not(child::*) and (node:configclass() = 'PreCompile') ])"!]U /* Compile time verification value */

#if (defined J1939TP_PUBLIC_INFO_SIGNATURE)
#error J1939TP_PUBLIC_INFO_SIGNATURE is already defined
#endif

#define J1939TP_PUBLIC_INFO_SIGNATURE [!"asc:getConfigSignature(node:difference(as:modconf('J1939Tp')[1]/CommonPublishedInformation//eb-choice::*[not(child::*) and (node:configclass() = 'PublishedInformation') ], as:modconf('J1939Tp')[1]/CommonPublishedInformation/Release))"!]U /* PublicInfoSignature */

#if (defined J1939TP_PBCFGM_SUPPORT_ENABLED)
#error J1939TP_PBCFGM_SUPPORT_ENABLED is already defined
#endif
#define J1939TP_PBCFGM_SUPPORT_ENABLED [!IF "node:contains(util:distinct(node:refs(as:modconf('PbcfgM')/PbcfgMBswModules/eb-list::*/PbcfgMBswModuleRef)), as:modconf('J1939Tp')) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/* ----- Pre-processor switch to enable/disable relocateable postbuild config ----- */
#if (defined J1939TP_RELOCATABLE_CFG_ENABLE)
#error J1939TP_RELOCATABLE_CFG_ENABLE is already defined
#endif

#if (J1939TP_PBCFGM_SUPPORT_ENABLED == STD_ON)
#define J1939TP_RELOCATABLE_CFG_ENABLE [!IF "node:existsAndTrue(as:modconf('PbcfgM')/PbcfgMGeneral/PbcfgMRelocatableCfgEnable)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#else
#define J1939TP_RELOCATABLE_CFG_ENABLE [!IF "node:existsAndTrue(as:modconf('J1939Tp')[1]/J1939TpGeneral/J1939TpRelocatablePbcfgEnable)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#endif

#if (defined J1939TP_DEV_ERROR_DETECT)
#error J1939TP_DEV_ERROR_DETECT already defined
#endif
/** \brief Switch, indicating whether the Development Error Detect is enabled or not */
#define J1939TP_DEV_ERROR_DETECT          [!//
STD_[!IF "node:existsAndTrue(J1939TpGeneral/J1939TpDevErrorDetect)"!]ON[!ELSE!]OFF[!ENDIF!]

#define J1939TP_MULTIPLE_SA_DA_CONNECTIONS_CLASSIC_CAN          [!//
STD_[!IF " text:tolower(J1939TpGeneral/J1939TpMultipleConectionSameSaDa) = 'true'"!]ON[!ELSE!]OFF[!ENDIF!]

#if (defined J1939TP_RELIABLE_TXCONFIRMATION)
#error J1939TP_RELIABLE_TXCONFIRMATION already defined
#endif
/** \brief Switch, indicating whether the Reliable TxConfirmation enabled or not */
#define J1939TP_RELIABLE_TXCONFIRMATION          [!//
STD_[!IF "node:existsAndTrue(J1939TpGeneral/J1939TpReliableTxConfirmation)"!]ON[!ELSE!]OFF[!ENDIF!]

#if (defined J1939TP_CANCELLATION_SUPPORT)
#error J1939TP_CANCELLATION_SUPPORT already defined
#endif
/** \brief Enable transmit and receive cancellation. */
#define J1939TP_CANCELLATION_SUPPORT          [!//
STD_[!IF "node:existsAndTrue(J1939TpGeneral/J1939TpCancellationSupport)"!]ON[!ELSE!]OFF[!ENDIF!]

#if (defined J1939TP_VERSION_INFO_API)
#error J1939TP_VERSION_INFO_API already defined
#endif
/** \brief Switch, indicating whether J1939Tp_GetVersionInfo API is enabled or not */
#define J1939TP_VERSION_INFO_API          [!//
STD_[!IF "node:existsAndTrue(J1939TpGeneral/J1939TpVersionInfoApi)"!]ON[!ELSE!]OFF[!ENDIF!]


#if (defined J1939TP_TX_PARALLEL_CHANNEL_HANDLING)
#error J1939TP_TX_PARALLEL_HANDLING defined
#endif
/** \brief Switch, indicating whether J1939TpTxChannelHandling is enabled or not */
#define J1939TP_TX_PARALLEL_CHANNEL_HANDLING          [!//
STD_[!IF "node:existsAndTrue(J1939TpGeneral/J1939TpTxChannelHandling)"!]ON[!ELSE!]OFF[!ENDIF!]


#if (defined J1939TP_TX_CANFD_SUPPORT)
#error J1939TP_TX_CANFD_SUPPORT already defined
#endif
/** \brief Switch, indicating whether CanFD message transmission is enabled or not */
#define J1939TP_TX_CANFD_SUPPORT          [!//
STD_[!IF "num:i($CanFDTxChannelCounter) > num:i(0)"!]ON[!ELSE!]OFF[!ENDIF!]

#if (defined J1939TP_RX_CANFD_SUPPORT)
#error J1939TP_RX_CANFD_SUPPORT already defined
#endif
/** \brief Switch, indicating whether CanFD message reception is enabled or not */
#define J1939TP_RX_CANFD_SUPPORT          [!//
STD_[!IF "num:i($CanFDRxChannelCounter) > num:i(0)"!]ON[!ELSE!]OFF[!ENDIF!]

[!VAR "ConfigIndex" = "'0'"!]
[!SELECT "util:distinct(node:order(J1939TpConfiguration/eb-list::*))"!][!//
/* Definition of SDU/PDU handles */
/* PDU Handles used by higher layer (PduR) */
[!LOOP "util:distinct(node:order(J1939TpTxChannel/eb-list::*))"!]
  [!LOOP "util:distinct(node:order(J1939TpTxPg/eb-list::*))"!]
    [!LOOP "util:distinct(node:order(J1939TpTxNSdu/eb-list::*))"!]

#if (defined J1939TpConf_J1939TpTxNSdu_[!"node:name(.)"!])
#error J1939TpConf_J1939TpTxNSdu_[!"node:name(.)"!] already defined
#endif
/** \brief Switch, indicating the TxNSdu configuration of [!"node:name(.)"!] of channel [!"node:name(../..)"!]. */
#define J1939TpConf_J1939TpTxNSdu_[!"node:name(.)"!]    [!"node:value(J1939TpTxNSduId)"!]U
    [!ENDLOOP!]
  [!ENDLOOP!]
[!ENDLOOP!]

/* Receive SDUs (J1939TpRxNSdu) for receive cancellation request, change parameters request*/
[!LOOP "util:distinct(node:order(J1939TpRxChannel/eb-list::*))"!]
  [!LOOP "util:distinct(node:order(J1939TpRxPg/eb-list::*))"!]
    [!LOOP "util:distinct(node:order(J1939TpRxNSdu/eb-list::*))"!]

#if (defined J1939TpConf_J1939TpRxNSdu_[!"node:name(.)"!])
#error J1939TpConf_J1939TpRxNSdu_[!"node:name(.)"!] already defined
#endif
/** \brief Switch, indicating the RxNSdu configuration of [!"node:name(.)"!] of channel [!"node:name(../..)"!]. */
#define J1939TpConf_J1939TpRxNSdu_[!"node:name(.)"!]    [!"node:value(J1939TpRxNSduId)"!]U
    [!ENDLOOP!]
  [!ENDLOOP!]
[!ENDLOOP!]

/* PDU Handles used by lower layer (CanIf) */
/* Reception handles for CM and DT frame */
[!LOOP "util:distinct(node:order(J1939TpRxChannel/eb-list::*))"!]

#if (defined J1939TpConf_J1939TpRxCmNPdu_[!"as:name(J1939TpRxCmNPdu)"!])
#error J1939TpConf_J1939TpRxCmNPdu_[!"as:name(J1939TpRxCmNPdu)"!] already defined
#endif
/** \brief Switch, indicating the RxCmNPdu configuration of channel [!"node:name(.)"!]. */
#define J1939TpConf_J1939TpRxCmNPdu_[!"as:name(J1939TpRxCmNPdu)"!]  [!"node:value(J1939TpRxCmNPdu/J1939TpRxCmNPduId)"!]U

#if (defined J1939TpConf_J1939TpRxDtNPdu_[!"as:name(J1939TpRxDtNPdu)"!])
#error J1939TpConf_J1939TpRxDtNPdu_[!"as:name(J1939TpRxDtNPdu)"!] already defined
#endif
/** \brief Switch, indicating the RxDtNPdu configuration of channel [!"node:name(.)"!]. */
#define J1939TpConf_J1939TpRxDtNPdu_[!"as:name(J1939TpRxDtNPdu)"!]  [!"node:value(J1939TpRxDtNPdu/J1939TpRxDtNPduId)"!]U
[!ENDLOOP!]

/* Reception handles for Direct Pg */
[!LOOP "util:distinct(node:order(J1939TpRxChannel/eb-list::*))"!]
  [!LOOP "util:distinct(node:order(J1939TpRxPg/eb-list::*))"!]
    [!IF "node:existsAndTrue(J1939TpRxPgDynLength)"!]

#if (defined J1939TpConf_J1939TpRxDirectNPdu_[!"as:name(J1939TpRxDirectNPdu)"!])
#error J1939TpConf_J1939TpRxDirectNPdu_[!"as:name(J1939TpRxDirectNPdu)"!] already defined
#endif
/** \brief Switch, indicating the RxDirectNPdu configuration of channel [!"node:name(../..)"!]. */
#define J1939TpConf_J1939TpRxDirectNPdu_[!"as:name(J1939TpRxDirectNPdu)"!]  [!"node:value(J1939TpRxDirectNPdu/J1939TpRxDirectNPduId)"!]U
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDLOOP!]

/* FlowControl handles */
[!LOOP "util:distinct(node:order(J1939TpRxChannel/eb-list::*))"!]
  [!IF "((node:exists(J1939TpRxProtocolType)) and (J1939TpRxProtocolType = 'J1939TP_PROTOCOL_CMDT')) or (not(node:exists(J1939TpRxProtocolType)))"!]

#if (defined J1939TpConf_J1939TpTxFcNPdu_[!"as:name(J1939TpTxFcNPdu)"!])
#error J1939TpConf_J1939TpTxFcNPdu_[!"as:name(J1939TpTxFcNPdu)"!] already defined
#endif
/** \brief Switch, indicating the TxFcNPdu configuration of channel [!"node:name(.)"!]. */
#define J1939TpConf_J1939TpTxFcNPdu_[!"as:name(J1939TpTxFcNPdu)"!]  [!"node:value(J1939TpTxFcNPdu/J1939TpTxFcNPduTxConfId)"!]U
  [!ENDIF!]
[!ENDLOOP!]

/* Confirmation for CM , DT frame and CTS reception */
[!LOOP "util:distinct(node:order(J1939TpTxChannel/eb-list::*))"!]
  [!IF "node:exists(J1939TpRxFcNPdu)"!]

#if (defined J1939TpConf_J1939TpRxFcNPdu_[!"as:name(J1939TpRxFcNPdu)"!])
#error J1939TpConf_J1939TpRxFcNPdu_[!"as:name(J1939TpRxFcNPdu)"!] already defined
#endif
/** \brief Switch, indicating the RxFcNPdu configuration of channel [!"node:name(.)"!]. */
#define J1939TpConf_J1939TpRxFcNPdu_[!"as:name(J1939TpRxFcNPdu)"!]  [!"node:value(J1939TpRxFcNPdu/J1939TpRxFcNPduId)"!]U
  [!ENDIF!]

#if (defined J1939TpConf_J1939TpTxCmNPdu_[!"as:name(J1939TpTxCmNPdu)"!])
#error J1939TpConf_J1939TpTxCmNPdu_[!"as:name(J1939TpTxCmNPdu)"!] already defined
#endif
/** \brief Switch, indicating the TxCmNPdu configuration of channel [!"node:name(.)"!]. */
#define J1939TpConf_J1939TpTxCmNPdu_[!"as:name(J1939TpTxCmNPdu)"!]  [!"node:value(J1939TpTxCmNPdu/J1939TpTxCmNPduTxConfId)"!]U

#if (defined J1939TpConf_J1939TpTxDtNPdu_[!"as:name(J1939TpTxDtNPdu)"!])
#error J1939TpConf_J1939TpTxDtNPdu_[!"as:name(J1939TpTxDtNPdu)"!] already defined
#endif
/** \brief Switch, indicating the TxDtNPdu configuration of channel [!"node:name(.)"!]. */
#define J1939TpConf_J1939TpTxDtNPdu_[!"as:name(J1939TpTxDtNPdu)"!]  [!"node:value(J1939TpTxDtNPdu/J1939TpTxDtNPduTxConfId)"!]U
[!ENDLOOP!]

/* Confirmation for Direct Pg */
[!LOOP "util:distinct(node:order(J1939TpTxChannel/eb-list::*))"!]
  [!LOOP "util:distinct(node:order(J1939TpTxPg/eb-list::*))"!]
    [!IF "node:existsAndTrue(J1939TpTxPgDynLength)"!]

#if (defined J1939TpConf_J1939TpTxDirectNPdu_[!"as:name(J1939TpTxDirectNPdu)"!])
#error J1939TpConf_J1939TpTxDirectNPdu_[!"as:name(J1939TpTxDirectNPdu)"!] already defined
#endif
/** \brief Switch, indicating the TxDirectNPdu configuration of channel [!"node:name(../..)"!]. */
#define J1939TpConf_J1939TpTxDirectNPdu_[!"as:name(J1939TpTxDirectNPdu)"!]    [!"node:value(J1939TpTxDirectNPdu/J1939TpTxDirectNPduTxConfId)"!]U
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDLOOP!]

/*==================[external function declarations]=========================*/

/* Public Data Declarations */
/* Public Constant Declarations */
/* Public Constants Declarations */
#define J1939TP_START_SEC_CONFIG_DATA_UNSPECIFIED
#include <J1939Tp_MemMap.h>

/* Definition for J1939TpConfiguration_0_config configuration */
extern CONST(J1939Tp_GeneralConfigType, J1939TP_CONST) J1939TpConfiguration_0_config;

#define J1939TP_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include <J1939Tp_MemMap.h>

[!VAR "ConfigIndex" = "num:i($ConfigIndex + 1)"!]
[!ENDSELECT!][!//

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

#endif/* ifndef J1939TP_CFG_H */
/*======================[end of file]============================================*/
[!ENDCODE!]
