/**
 * \file
 *
 * \brief AUTOSAR Nm
 *
 * This file contains the implementation of the AUTOSAR
 * module Nm.
 *
 * \version 5.12.16
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* !LINKSTO Nm.EB_Ref.SWS_Nm_00247,1 */

/*==================[inclusions]============================================*/

[!AUTOSPACING!][!//
[!INCLUDE "../include/Nm_Cfg.m"!][!//

#include <Nm_Cfg.h>
#include <Nm.h>                 /* Nm public API (own interface) */
#include <Nm_Int.h>             /* Nm internal symbols (own interface) */

[!IF "not(($BusNmNum > 1)
or (node:existsAndFalse(NmGlobalConfig/NmGlobalFeatures/NmCoordinatorSupportEnabled)))"!][!//
#include <TSCompiler.h>
/* For the given configuration this translation unit is empty.  The following
 * macro prevents compiler errors or warnings in this case */
TS_PREVENTEMPTYTRANSLATIONUNIT
[!ENDIF!][!//

#include <SchM_Nm.h>

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

#define NM_START_SEC_CONST_UNSPECIFIED
#include <Nm_MemMap.h>

[!INDENT "0"!][!//
[!IF "($BusNmNum > 1) or
      (node:existsAndTrue(NmGlobalConfig/NmGlobalFeatures/NmCoordinatorSupportEnabled)) or
      (count(NmChannelConfig/eb-list::*[node:existsAndTrue(NmStateReportEnabled)]) != 0) or
      (num:i(count(NmChannelConfig/eb-list::*)) > 1)"!][!//
/* Array holding the channel configurations */
CONST(Nm_ChannelConfigType, NM_CONST) Nm_ChannelConfig[NM_CHANNEL_NUM] =
{
  [!LOOP "NmChannelConfig/eb-list::*"!][!//
    [!WS "2"!]{
      [!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]
        [!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreUseSingleCS = 'true')"!]    
          [!IF "(node:exists(NmBusType/eb-choice::*[1]/NmStandardBusType)) and
                ((NmBusType/eb-choice::*[1]/NmStandardBusType='NM_BUSNM_CANNM') or
                 (NmBusType/eb-choice::*[1]/NmStandardBusType='NM_BUSNM_FRNM') or
                 (NmBusType/eb-choice::*[1]/NmStandardBusType='NM_BUSNM_UDPNM')
                )"!]
              [!WS "4"!]&SchM_Call_Nm_RequiredCSEntry_Nm_MultipleNetworkOperations_[!"node:name(.)"!],
              [!IF "$GenericNmEnabled = 'true'"!]
                [!WS "4"!]NULL_PTR,
                [!IF "count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:exists(NmBusType/eb-choice::*[1]/NmGenericBusNmPrefix) and node:existsAndFalse(NmPassiveModeEnabled)]) != 0"!]
                [!WS "4"!]NULL_PTR,
                [!WS "4"!]NULL_PTR,
                [!ENDIF!]
              [!ENDIF!]            
          [!ELSE!]
            [!WS "4"!]NULL_PTR, 
            [!WS "4"!]&[!"NmBusType/eb-choice::*[1]/NmGenericBusNmPrefix"!]_PassiveStartUp,
            [!IF "count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:exists(NmBusType/eb-choice::*[1]/NmGenericBusNmPrefix) and node:existsAndFalse(NmPassiveModeEnabled)]) != 0"!]
              [!IF "node:existsAndFalse(NmPassiveModeEnabled)"!]
                [!WS "4"!]&[!"NmBusType/eb-choice::*[1]/NmGenericBusNmPrefix"!]_NetworkRequest,
                [!WS "4"!]&[!"NmBusType/eb-choice::*[1]/NmGenericBusNmPrefix"!]_NetworkRelease,
              [!ELSE!]
                [!WS "4"!]NULL_PTR,
                [!WS "4"!]NULL_PTR,
              [!ENDIF!]
            [!ENDIF!]
          [!ENDIF!]
        [!ELSE!] [!/*[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreUseSingleCS = 'true'")!] */!]
          [!IF "(node:exists(NmBusType/eb-choice::*[1]/NmStandardBusType)) and
                ((NmBusType/eb-choice::*[1]/NmStandardBusType='NM_BUSNM_CANNM') or
                 (NmBusType/eb-choice::*[1]/NmStandardBusType='NM_BUSNM_FRNM') or
                 (NmBusType/eb-choice::*[1]/NmStandardBusType='NM_BUSNM_UDPNM')
                )"!]
            [!WS "4"!]&SchM_Call_Nm_RequiredCSEntry_Nm_PassiveStartUp_[!"node:name(.)"!],
            [!IF "count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:existsAndFalse(NmPassiveModeEnabled)]) != 0"!]
              [!IF "node:existsAndFalse(NmPassiveModeEnabled)"!]
                [!WS "4"!]&SchM_Call_Nm_RequiredCSEntry_Nm_NetworkRequest_[!"node:name(.)"!],
                [!WS "4"!]&SchM_Call_Nm_RequiredCSEntry_Nm_NetworkRelease_[!"node:name(.)"!],
#if (EB_NM_STACK == STD_ON)
                [!WS "4"!]&SchM_Call_Nm_RequiredCSEntry_Nm_NetworkGwEraRequest_[!"node:name(.)"!],
#endif /* (EB_NM_STACK == STD_ON) */
              [!ELSE!]
                [!WS "4"!]NULL_PTR,
                [!WS "4"!]NULL_PTR,
#if (EB_NM_STACK == STD_ON)
                [!WS "4"!]NULL_PTR,
#endif /* (EB_NM_STACK == STD_ON) */
              [!ENDIF!]
            [!ENDIF!]
          [!ELSE!]
            [!WS "4"!]&[!"NmBusType/eb-choice::*[1]/NmGenericBusNmPrefix"!]_PassiveStartUp,
            [!IF "count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:existsAndFalse(NmPassiveModeEnabled)]) != 0"!]
              [!IF "node:existsAndFalse(NmPassiveModeEnabled)"!]
                [!WS "4"!]&[!"NmBusType/eb-choice::*[1]/NmGenericBusNmPrefix"!]_NetworkRequest,
                [!WS "4"!]&[!"NmBusType/eb-choice::*[1]/NmGenericBusNmPrefix"!]_NetworkRelease,
              [!ELSE!]
                [!WS "4"!]NULL_PTR,
                [!WS "4"!]NULL_PTR,
              [!ENDIF!]
            [!ENDIF!]
          [!ENDIF!]
        [!ENDIF!] [!/* [!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreUseSingleCS = 'true')"!] */!]
        [!IF "count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:existsAndFalse(NmPassiveModeEnabled)]) != 0"!]
          [!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmBusSynchronizationEnabled)"!]
            [!IF "node:existsAndFalse(NmPassiveModeEnabled)"!]
              [!IF "(node:exists(NmBusType/eb-choice::*[1]/NmStandardBusType)) and (NmBusType/eb-choice::*[1]/NmStandardBusType='NM_BUSNM_FRNM')"!]
			     [!IF "(node:existsAndTrue(as:modconf('FrNm')[1]/FrNmGlobalConfig/FrNmGlobalFeatures/FrNmBusSynchronizationEnabled))"!]
                   [!WS "4"!]&SchM_Call_Nm_RequiredCSEntry_Nm_BusNm_RequestBusSynchronization_[!"node:name(.)"!],
                 [!ELSE!]
                   [!WS "4"!]NULL_PTR,
                 [!ENDIF!]
              [!ELSE!]
                 [!IF "(node:exists(NmBusType/eb-choice::*[1]/NmStandardBusType)) and
                       ((NmBusType/eb-choice::*[1]/NmStandardBusType='NM_BUSNM_CANNM') or
                        (NmBusType/eb-choice::*[1]/NmStandardBusType='NM_BUSNM_UDPNM')
                       )"!]
                   [!WS "4"!]&SchM_Call_Nm_RequiredCSEntry_Nm_BusNm_RequestBusSynchronization_[!"node:name(.)"!],
                 [!ELSE!]
                   [!WS "4"!]&[!"NmBusType/eb-choice::*[1]/NmGenericBusNmPrefix"!]_RequestBusSynchronization,
                 [!ENDIF!]
              [!ENDIF!]
            [!ELSE!]
              [!WS "4"!]NULL_PTR,
            [!ENDIF!]
          [!ENDIF!]
        [!ENDIF!]
      [!ENDIF!]
      [!IF "node:existsAndTrue(../../NmGlobalConfig/NmGlobalFeatures/NmCoordinatorSupportEnabled)"!][!//
        [!VAR "ShutdownTimer" = "num:i((NmShutdownDelayTimer * 1000) div (../../NmGlobalConfig/NmGlobalProperties/NmCycletimeMainFunction * 1000))"!]
        [!IF "$ShutdownTimer != 0"!]
          [!WS "4"!][!"$ShutdownTimer"!]U, /* shutdown time in main func cycles */
        [!ELSE!]
          [!/* If NmShutdownDelayTimer = 0, we set the timer value to 1.
               This is to ensure that BusNm_NetworkRelease is called once
               and only once.*/!]
          [!WS "4"!]1U,  /* shutdown time in main func cycles */
        [!ENDIF!][!//
        [!IF "node:exists(NmWaitForShutdownTime)"!]
          [!WS "4"!][!"num:i((NmWaitForShutdownTime * 1000) div (../../NmGlobalConfig/NmGlobalProperties/NmCycletimeMainFunction * 1000))"!]U, /* WaitForShutdownTime */
        [!ELSE!]
          [!WS "4"!]0U, /* WaitForShutdownTime */
        [!ENDIF!]
      [!ENDIF!][!//
      [!IF "count(../eb-list::*[node:existsAndTrue(NmStateReportEnabled)]) != 0"!]
        [!IF "(node:existsAndTrue(NmStateReportEnabled)) and (node:exists(as:ref(NmStateReportSignalRef)/ComHandleId))"!]
          [!WS "4"!][!"num:i(as:ref(NmStateReportSignalRef)/ComHandleId)"!]U,  /* ComHandleId */
        [!ELSE!]
          [!WS "4"!]NM_COM_SIGNAL_INVALID,  /* No Com Signal reference */
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!IF "$BusNmNum > 1"!][!//
        [!IF "node:exists(NmBusType/eb-choice::*[1]/NmStandardBusType)"!][!//
          [!IF "(NmBusType/eb-choice::*[1]/NmStandardBusType = 'NM_BUSNM_CANNM')"!][!//
            [!WS "4"!][!"num:i($CanNmId)"!]U, /* CanNm Id */
          [!ELSE!][!//
            [!IF "(NmBusType/eb-choice::*[1]/NmStandardBusType = 'NM_BUSNM_FRNM')"!][!//
              [!WS "4"!][!"num:i($FrNmId)"!]U, /* FrNm Id */
            [!ELSE!][!//
              [!/* here the condition NmBusType/eb-choice::*[1]/NmStandardBusType =
                  NM_BUSNM_UDPNM is assured by the xdm check on the
                  NmStandardBusType parameter */!][!//
              [!WS "4"!][!"num:i($UdpNmId)"!]U, /* UdpNm Id */
            [!ENDIF!][!//
          [!ENDIF!][!//
        [!ELSE!][!//
        [!/* generic Nm */!][!//
        [!VAR "GenericBusNmName" = "''"!][!//
        [!FOR "arrIndx" = "1" TO "count(text:split($GenericUniqNm))"!][!//
          [!VAR "GenericBusNmName" = "text:split($GenericUniqNm)[position() = $arrIndx]"!][!//
          [!IF "$GenericBusNmName = node:value(NmBusType/eb-choice::*[1]/NmGenericBusNmPrefix)"!][!//
            [!WS "4"!][!"num:i(number(text:split($GenericNmId)[position() = $arrIndx]))"!]U, /* [!"$GenericBusNmName"!] Id (Generic Bus)*/
          [!ENDIF!][!//
        [!ENDFOR!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!IF "node:existsAndTrue(../../NmGlobalConfig/NmGlobalFeatures/NmCoordinatorSupportEnabled)"!][!//
        [!IF "node:exists(NmCoordClusterIndex)"!][!//
          [!WS "4"!][!"NmCoordClusterIndex"!]U, /* cluster index */
        [!ELSE!][!//
          [!WS "4"!]NM_CC_IDX_INVALID, /* network is not part of cluster */
        [!ENDIF!][!//
        [!IF "node:existsAndTrue(NmChannelSleepMaster)"!][!//
          [!WS "4"!]TRUE,    /* NmChannelSleepMaster State */
        [!ELSE!][!//
          [!WS "4"!]FALSE,   /* NmChannelSleepMaster State */
        [!ENDIF!][!//
        [!IF "node:existsAndTrue(NmSynchronizingNetwork)"!][!//
          [!WS "4"!]TRUE,    /* NmSynchronizingNetwork */
        [!ELSE!][!//
          [!WS "4"!]FALSE,   /* NmSynchronizingNetwork */
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!IF "node:existsAndTrue(NmPassiveModeEnabled)"!][!//
        [!WS "4"!]TRUE,      /* Passive mode */
      [!ELSE!]
        [!WS "4"!]FALSE,     /* Passive mode */
      [!ENDIF!][!//
      [!IF "node:existsAndTrue(NmNodeIdEnabled)"!][!//
        [!WS "4"!]TRUE,      /* NmNodeIdEnabled */
      [!ELSE!]
        [!WS "4"!]FALSE,     /* NmNodeIdEnabled */
      [!ENDIF!][!//
      [!IF "node:existsAndTrue(NmNodeDetectionEnabled)"!][!//
        [!WS "4"!]TRUE,      /* NmNodeDetectionEnabled */
      [!ELSE!]
        [!WS "4"!]FALSE,     /* NmNodeDetectionEnabled */
      [!ENDIF!][!//
[!IF "(node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmSynchronizedPncShutdownEnabled))"!]
[!IF "node:exists(NmBusType/eb-choice::*[1]/NmStandardBusType)"!]     
      [!WS "4"!]FALSE,      /* IsGenericBus; */
[!ELSE!] [!/*[!IF "node:exists(NmBusType/eb-choice::*[1]/NmStandardBusType)"!]*/!]
      [!WS "4"!]TRUE,      /* IsGenericBus; */
[!ENDIF!] [!/*[!IF "node:exists(NmBusType/eb-choice::*[1]/NmStandardBusType)"!]*/!]      
[!ENDIF!] [!/*[!IF "(node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmSynchronizedPncShutdownEnabled))"!]*/!]
    [!WS "2"!]},
  [!ENDLOOP!][!//
};
[!ENDIF!][!//
[!ENDINDENT!][!//

[!IF "node:existsAndTrue(NmGlobalConfig/NmGlobalFeatures/NmCoordinatorSupportEnabled)"!][!//

[!// take greatest cluster index for all coordinated Nm channels
[!VAR "HighestClusterIndex"
 = "num:order(NmChannelConfig/eb-list::*[node:exists(NmCoordClusterIndex)]/NmCoordClusterIndex)[last()]"!][!//
[!FOR "ClusterIndex" = "0" TO "$HighestClusterIndex"!][!//
STATIC CONST(NetworkHandleType, NM_CONST) Nm_CcNmChannels_[!"$ClusterIndex"!][!//
[[!"num:i(count(NmChannelConfig/eb-list::*[(node:exists(NmCoordClusterIndex)) and (NmCoordClusterIndex = number($ClusterIndex))]))"!]] =
{
[!/* ordered list of channel IDs for channels belonging to given cluster
*/!][!//
  [!"text:join(num:order(
NmChannelConfig/eb-list::*[(node:exists(NmCoordClusterIndex)) and (NmCoordClusterIndex = number($ClusterIndex))]/NmChannelId),'U, ')"!]U
};
[!ENDFOR!][!//

CONSTP2CONST(NetworkHandleType, NM_CONST, NM_CONST) Nm_CcNmChannels[NM_CC_NUM]=
{
[!FOR "ClusterIndex" = "0" TO "$HighestClusterIndex"!][!//
  Nm_CcNmChannels_[!"$ClusterIndex"!],
[!ENDFOR!][!//
};

[!ENDIF!][!//
[!//
[!SELECT "NmGlobalConfig/NmGlobalFeatures"!][!//
[!IF "($BusNmNum > 1)"!][!//

/* Array of pointers to BusNm functions */
CONST(Nm_BusNmFpType, NM_CONST) Nm_BusNmFp[NM_BUSNM_NUM] =
{
[!FOR "BusId" = "1" TO "count(text:split($BusNmList))"!][!//
[!VAR "BusNmName" = "text:split($BusNmList)[position() = $BusId]"!][!//
[!VAR "BusNmNameFull" = "text:split($BusNmListFullName)[position() = $BusId]"!][!//
[!VAR "PassiveMode" = "text:split($BusNmPassiveMode)[position() = $BusId]"!][!//
[!VAR "IsGeneric" = "text:split($BusNmIsGeneric)[position() = $BusId]"!][!//

  {
[!IF "node:existsAndFalse(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]
    &[!"$BusNmName"!]_PassiveStartUp,
[!ENDIF!] [!/*[!IF "node:existsAndFalse(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]*/!]

    &[!"$BusNmName"!]_GetState,
/* !LINKSTO Nm.ASR403.SWS_Nm_00244,1 */
[!IF "node:existsAndFalse(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]
[!IF "count(../../NmChannelConfig/eb-list::*[node:existsAndFalse(NmPassiveModeEnabled)]) != 0"!]
[!IF "$PassiveMode = 'false'"!][!//
    &[!"$BusNmName"!]_NetworkRequest,
    &[!"$BusNmName"!]_NetworkRelease,
#if (EB_NM_STACK == STD_ON)
    &[!"$BusNmName"!]_NetworkGwEraRequest,
#endif /* (EB_NM_STACK == STD_ON) */
[!ELSE!][!//
    NULL_PTR,
    NULL_PTR,
#if (EB_NM_STACK == STD_ON)
    NULL_PTR,
#endif /* (EB_NM_STACK == STD_ON) */
[!ENDIF!][!//
[!ENDIF!]
[!ENDIF!]
[!IF "node:existsAndTrue(NmUserDataEnabled)"!][!//
    &[!"$BusNmName"!]_GetUserData,
[!IF "(count(../../NmChannelConfig/eb-list::*[node:existsAndFalse(NmPassiveModeEnabled)]) != 0) and (node:existsAndFalse(NmComUserDataSupport))"!]
[!IF "$PassiveMode = 'false'"!][!//
    &[!"$BusNmName"!]_SetUserData,
[!ELSE!][!//
    NULL_PTR,
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "(count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:existsAndTrue(NmNodeIdEnabled)]) > 0)"!][!//
[!IF "(count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[((node:exists(NmBusType/eb-choice::*[1]/NmStandardBusType) and (NmBusType/eb-choice::*[1]/NmStandardBusType = string($BusNmNameFull))) or (node:exists(NmBusType/eb-choice::*[1]/NmGenericBusNmPrefix) and (NmBusType/eb-choice::*[1]/NmGenericBusNmPrefix = string($BusNmNameFull)))) and (node:existsAndTrue(NmNodeIdEnabled))]) > 0)"!]
    &[!"$BusNmName"!]_GetNodeIdentifier,
    &[!"$BusNmName"!]_GetLocalNodeIdentifier,
[!ELSE!]
    NULL_PTR,
    NULL_PTR,
[!ENDIF!]
[!ENDIF!][!//
[!IF "count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:existsAndTrue(NmNodeDetectionEnabled)]) > 0"!]
[!IF "count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[(((node:exists(NmBusType/eb-choice::*[1]/NmStandardBusType)) and (NmBusType/eb-choice::*[1]/NmStandardBusType = string($BusNmNameFull))) or (NmBusType/eb-choice::*[1]/NmGenericBusNmPrefix = string($BusNmNameFull))) and (node:existsAndTrue(NmNodeDetectionEnabled))]) > 0"!]
    &[!"$BusNmName"!]_RepeatMessageRequest,
[!ELSE!]
    NULL_PTR,
[!ENDIF!][!//
[!ENDIF!]

[!IF "(count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:existsAndTrue(NmNodeIdEnabled)]) > 0) or
      (count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:existsAndTrue(NmNodeDetectionEnabled)]) > 0) or
      (node:existsAndTrue(NmUserDataEnabled))"!]
[!IF "(count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[(((node:exists(NmBusType/eb-choice::*[1]/NmStandardBusType)) and (NmBusType/eb-choice::*[1]/NmStandardBusType = string($BusNmNameFull))) or (NmBusType/eb-choice::*[1]/NmGenericBusNmPrefix = string($BusNmNameFull))) and (node:existsAndTrue(NmNodeIdEnabled))]) > 0) or
      (count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[(((node:exists(NmBusType/eb-choice::*[1]/NmStandardBusType)) and (NmBusType/eb-choice::*[1]/NmStandardBusType = string($BusNmNameFull))) or (NmBusType/eb-choice::*[1]/NmGenericBusNmPrefix = string($BusNmNameFull))) and (node:existsAndTrue(NmNodeDetectionEnabled))]) > 0) or
      (node:existsAndTrue(NmUserDataEnabled))"!]
    &[!"$BusNmName"!]_GetPduData,
[!ELSE!]
    NULL_PTR,
[!ENDIF!][!//
[!ENDIF!]

[!IF "node:existsAndTrue(NmBusSynchronizationEnabled)"!][!//
    &[!"$BusNmName"!]_RequestBusSynchronization,
[!ENDIF!][!//
[!IF "node:existsAndTrue(NmRemoteSleepIndEnabled)"!][!//
    &[!"$BusNmName"!]_CheckRemoteSleepIndication,
[!ENDIF!][!//
[!IF "node:existsAndTrue(NmComControlEnabled)"!][!//
    &[!"$BusNmName"!]_DisableCommunication,
    &[!"$BusNmName"!]_EnableCommunication,
[!ENDIF!][!//
[!IF "(node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmSynchronizedPncShutdownEnabled))"!]
  [!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]
    [!IF "($CanNmEnabled = 'true') or ($FrNmEnabled = 'true') or ($UdpNmEnabled = 'true')"!]
      [!IF "($BusNmNameFull = 'NM_BUSNM_CANNM') or ($BusNmNameFull = 'NM_BUSNM_FRNM') or ($BusNmNameFull = 'NM_BUSNM_UDPNM')"!]
  &SchM_Send_Nm_Nm_RequestSynchronizedPncShutdown_Nm_To_[!"$BusNmName"!]_DataSet,
      [!ELSE!] [!/*[!IF "($BusNmNameFull = 'NM_BUSNM_CANNM') or ($BusNmNameFull = 'NM_BUSNM_FRNM') or ($BusNmNameFull = 'NM_BUSNM_UDPNM')"!]*/!]
  NULL_PTR,
      [!ENDIF!] [!/*[!IF "($BusNmNameFull = 'NM_BUSNM_CANNM') or ($BusNmNameFull = 'NM_BUSNM_FRNM') or ($BusNmNameFull = 'NM_BUSNM_UDPNM')"!]*/!]
    [!ENDIF!] [!/*[!IF "($CanNmEnabled = 'true') or ($FrNmEnabled = 'true') or ($UdpNmEnabled = 'true')"!]*/!]
    [!IF "$GenericNmEnabled = 'true'"!]
      [!IF "($BusNmNameFull != 'NM_BUSNM_CANNM') and ($BusNmNameFull != 'NM_BUSNM_FRNM') and ($BusNmNameFull != 'NM_BUSNM_UDPNM')"!]    
  &[!"$BusNmName"!]_RequestSynchronizedPncShutdown,  
      [!ELSE!] [!/*[!IF "($BusNmNameFull != 'NM_BUSNM_CANNM') and ($BusNmNameFull != 'NM_BUSNM_FRNM') and ($BusNmNameFull != 'NM_BUSNM_UDPNM')"!]*/!]
  NULL_PTR, 
      [!ENDIF!]
    [!ENDIF!] [!/*[!IF "$GenericNmEnabled = 'true'!"]*/!]
  [!ELSE!] [!/*[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]*/!]
  &[!"$BusNmName"!]_RequestSynchronizedPncShutdown,      
  [!ENDIF!] [!/*[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]*/!]
[!ENDIF!] [!/* [!IF "(node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmSynchronizedPncShutdownEnabled))"!]*/!]
  },
[!ENDFOR!][!//
};

[!ENDIF!][!//
[!ENDSELECT!][!//

#define NM_STOP_SEC_CONST_UNSPECIFIED
#include <Nm_MemMap.h>

#define NM_START_SEC_CONST_8
#include <Nm_MemMap.h>

[!IF "($BusNmNum > 1) or
      (node:existsAndTrue(NmGlobalConfig/NmGlobalFeatures/NmCoordinatorSupportEnabled)) or
      (node:existsAndTrue(NmGlobalConfig/NmGlobalProperties/NmDevErrorDetect)) or
      (count(NmChannelConfig/eb-list::*[node:existsAndTrue(NmStateReportEnabled)]) != 0) or
      (num:i(count(NmChannelConfig/eb-list::*)) > 1)"!][!//
/* Array which translates between the NetworkHandle and the Nm channel index  */
CONST(uint8, NM_CONST) Nm_ChanIdxFromNetworkHandle[NM_MAX_CHANNELID + 1U] =
{
[!FOR "Index" = "0" TO "num:max(NmChannelConfig/eb-list::*/NmChannelId)"!][!//
  [!IF "count(NmChannelConfig/eb-list::*[NmChannelId = number($Index)]) > 0"!]
  [!"NmChannelConfig/eb-list::*[NmChannelId = number($Index)]/@index"!]U, /* Nm channel index of NetworkHandle [!"$Index"!] */
  [!ELSE!]
  NM_INVALID_CHANNEL_ID, /* NetworkHandle [!"$Index"!] is not mapped to a Nm channel */
  [!ENDIF!]
[!ENDFOR!]
};
[!ENDIF!][!//

[!IF "node:existsAndTrue(NmGlobalConfig/NmGlobalFeatures/NmCoordinatorSupportEnabled)"!][!//

CONST(uint8, NM_CONST) Nm_CcNmChannelsNum[NM_CC_NUM]=
{
[!FOR "ClusterIndex" = "0" TO "$HighestClusterIndex"!][!//
  [!"num:i(count(NmChannelConfig/eb-list::*[(node:exists(NmCoordClusterIndex)) and (NmCoordClusterIndex = number($ClusterIndex))]))"!]U,
[!ENDFOR!][!//
};

[!ENDIF!][!//

#define NM_STOP_SEC_CONST_8
#include <Nm_MemMap.h>

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
