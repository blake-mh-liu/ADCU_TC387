#ifndef NM_CFG_H
#define NM_CFG_H
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

[!AUTOSPACING!][!//
[!INCLUDE "Nm_Cfg.m"!][!//
[!SELECT "NmGlobalConfig/NmGlobalProperties"!][!//

/*==================[includes]==============================================*/

#include <NmStack_Types.h>  /* Nm stack specific types, includes stdtypes.h */
[!IF "count(../../NmChannelConfig/eb-list::*[node:existsAndTrue(NmStateReportEnabled)]) != 0"!][!//
/* !LINKSTO Nm.SWS_Nm_00166,1 */
#include <Com.h>        /* Com interface */
[!ENDIF!][!//

[!IF "$CanNmEnabled = 'true'"!]
/* !LINKSTO Nm.SWS_Nm_00166,1 */
#include <CanNm.h>                                        /* Can Nm header */
[!ENDIF!]

[!IF "$FrNmEnabled = 'true'"!]
/* !LINKSTO Nm.SWS_Nm_00166,1 */
#include <FrNm.h>                                     /* FlexRay Nm header */
[!ENDIF!]

[!IF "$UdpNmEnabled = 'true'"!]
/* !LINKSTO Nm.SWS_Nm_00166,1 */
#include <UdpNm.h>                                     /* UDP Nm header */
[!ENDIF!]


/* Include header files for Generic NMs*/
[!IF "$GenericNmEnabled = 'true'"!][!//
[!FOR "arrIndx" = "1" TO "count(text:split($GenericUniqNm))"!][!//
#include<[!"text:split($GenericUniqNm)[position() = $arrIndx]"!].h>
[!ENDFOR!][!//
[!ENDIF!][!//

/*==================[macros]================================================*/
/** \brief Macro to indicate the value of operation passive startup
 */
#if (defined NM_MULTI_CORE_USE_SINGLE_CS_PASSIVE_STARTUP)
#error NM_MULTI_CORE_USE_SINGLE_CS_PASSIVE_STARTUP is already defined
#endif
#define NM_MULTI_CORE_USE_SINGLE_CS_PASSIVE_STARTUP 0U

/** \brief Macro to indicate the value of operation network request
 */
#if (defined NM_MULTI_CORE_USE_SINGLE_CS_NETWORK_REQUEST)
#error NM_MULTI_CORE_USE_SINGLE_CS_NETWORK_REQUEST is already defined
#endif
#define NM_MULTI_CORE_USE_SINGLE_CS_NETWORK_REQUEST 1U

/** \brief Macro to indicate the value of operation network release
 */
#if (defined NM_MULTI_CORE_USE_SINGLE_CS_NETWORK_RELEASE)
#error NM_MULTI_CORE_USE_SINGLE_CS_NETWORK_RELEASE is already defined
#endif
#define NM_MULTI_CORE_USE_SINGLE_CS_NETWORK_RELEASE 2U
/** \brief Macro to indicate the value of operation Network Gw Era Request
 */
#if (defined NM_MULTI_CORE_USE_SINGLE_CS_GW_ERA_NETWORK_REQUEST)
#error NM_MULTI_CORE_USE_SINGLE_CS_GW_ERA_NETWORK_REQUEST is already defined
#endif
#define NM_MULTI_CORE_USE_SINGLE_CS_GW_ERA_NETWORK_REQUEST 3U

/** \brief Switch for DET usage */
#if (defined NM_DEV_ERROR_DETECT)
#error NM_DEV_ERROR_DETECT already defined
#endif
#define NM_DEV_ERROR_DETECT            [!//
[!IF "node:existsAndTrue(NmDevErrorDetect)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Provide API function Nm_GetVersionInfo() */
#if (defined NM_VERSION_INFO_API)
#error NM_VERSION_INFO_API already defined
#endif
#define NM_VERSION_INFO_API            [!//
[!IF "node:existsAndTrue(NmVersionInfoApi)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
[!ENDSELECT!][!//
[!//
[!SELECT "NmGlobalConfig/NmGlobalFeatures"!][!//
/** \brief enable support of the Passive Mode. */
#if (defined NM_PASSIVE_MODE_ENABLED)
#error NM_PASSIVE_MODE_ENABLED already defined
#endif
#define NM_PASSIVE_MODE_ENABLED        [!//
[!IF "count(../../NmChannelConfig/eb-list::*[node:existsAndFalse(NmPassiveModeEnabled)]) = 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Provide API for getting/setting user data of Nm messages*/
#if (defined NM_USER_DATA_ENABLED)
#error NM_USER_DATA_ENABLED already defined
#endif
#define NM_USER_DATA_ENABLED           [!//
[!IF "node:existsAndTrue(NmUserDataEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/* !LINKSTO Nm.EB.Config.NmMultiCoreSupport,1 */
/** \brief Enable multicore support*/
#if (defined NM_MULTICORE_ENABLED)
#error NM_MULTICORE_ENABLED already defined
#endif
#define NM_MULTICORE_ENABLED           [!//
[!IF "node:existsAndTrue(NmMultiCoreSupport)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Enable/Disable setting of NMUserData via SW-C */
#if (defined NM_COM_USER_DATA_ENABLED)
#error NM_COM_USER_DATA_ENABLED already defined
#endif
#define NM_COM_USER_DATA_ENABLED           [!//
[!IF "node:existsAndTrue(NmComUserDataSupport)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief enable the source node identifier. */
#if (defined NM_NODE_ID_ENABLED)
#error NM_NODE_ID_ENABLED already defined
#endif
#define NM_NODE_ID_ENABLED             [!//
[!IF "count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:existsAndTrue(NmNodeIdEnabled)]) > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Check if all channels have NmNodeIdEnabled set to true */
#if (defined NM_NODE_ID_ENABLED_ON_ALL_CHANNELS)
#error NM_NODE_ID_ENABLED_ON_ALL_CHANNELS already defined
#endif
#define NM_NODE_ID_ENABLED_ON_ALL_CHANNELS             [!//
[!IF "num:i(count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*)) =
      num:i(count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:existsAndTrue(NmNodeIdEnabled)]))"!] [!//
      STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief enable the Request Repeat Message Request support. */
#if (defined NM_NODE_DETECTION_ENABLED)
#error NM_NODE_DETECTION_ENABLED already defined
#endif
#define NM_NODE_DETECTION_ENABLED      [!//
[!IF "count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:existsAndTrue(NmNodeDetectionEnabled)]) > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]


/** \brief Check if all channels have NmNodeDetectionEnabled set to true */
#if (defined NM_NODE_DETECTION_ENABLED_ON_ALL_CHANNELS)
#error NM_NODE_DETECTION_ENABLED_ON_ALL_CHANNELS already defined
#endif
#define NM_NODE_DETECTION_ENABLED_ON_ALL_CHANNELS             [!//
[!IF "num:i(count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*)) =
      num:i(count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:existsAndTrue(NmNodeDetectionEnabled)]))"!] [!//
      STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief enable remote sleep indication support. This
 * feature is required for gateway nodes only */
#if (defined NM_REMOTE_SLEEP_IND_ENABLED)
#error NM_REMOTE_SLEEP_IND_ENABLED already defined
#endif
#define NM_REMOTE_SLEEP_IND_ENABLED    [!//
[!IF "node:existsAndTrue(NmRemoteSleepIndEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief enable the Communication Control support. */
#if (defined NM_COM_CONTROL_ENABLED)
#error NM_COM_CONTROL_ENABLED already defined
#endif
#define NM_COM_CONTROL_ENABLED         [!//
[!IF "node:existsAndTrue(NmComControlEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Enable bus synchronization support */
#if (defined NM_BUS_SYNCHRONIZATION_ENABLED)
#error NM_BUS_SYNCHRONIZATION_ENABLED already defined
#endif
#define NM_BUS_SYNCHRONIZATION_ENABLED [!//
[!IF "node:existsAndTrue(NmBusSynchronizationEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Enable Nm coordinator functionality */
#if (defined NM_COORDINATOR_SUPPORT_ENABLED)
#error NM_COORDINATOR_SUPPORT_ENABLED already defined
#endif
#define NM_COORDINATOR_SUPPORT_ENABLED [!//
[!IF "node:existsAndTrue(NmCoordinatorSupportEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Enable Nm coordinator sync support */
#if (defined NM_COORDINATOR_SYNC_SUPPORT_ENABLE)
#error NM_COORDINATOR_SYNC_SUPPORT_ENABLE already defined
#endif
#define NM_COORDINATOR_SYNC_SUPPORT_ENABLE [!//
[!IF "(node:existsAndTrue(NmCoordinatorSyncSupport))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Enable optional interface Nm_StateChangeNotification() */
#if (defined NM_STATE_CHANGE_IND_ENABLED)
#error NM_STATE_CHANGE_IND_ENABLED already defined
#endif
#define NM_STATE_CHANGE_IND_ENABLED [!//
[!IF "node:existsAndTrue(NmStateChangeIndEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Enable optional interface Nm_PduRxIndication() */
#if (defined NM_PDU_RX_INDICATION_ENABLED)
#error NM_PDU_RX_INDICATION_ENABLED already defined
#endif
#define NM_PDU_RX_INDICATION_ENABLED [!//
[!IF "node:existsAndTrue(NmPduRxIndicationEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Enable optional interface Nm_RepeatMessageIndication() */
#if (defined NM_REPEAT_MESSAGE_INDICATION)
#error NM_REPEAT_MESSAGE_INDICATION already defined
#endif

/* !LINKSTO Nm.ASR403.SWS_Nm_00231,2, Nm.ASR403.SWS_Nm_00231,2 */
#define NM_REPEAT_MESSAGE_INDICATION [!//
[!IF "count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:existsAndTrue(NmRepeatMsgIndEnabled)]) > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Enable optional interface Nm_RepeatMessageIndication() */
#if (defined NM_CAR_WAKEUPRX_INDICATION)
#error NM_CAR_WAKEUPRX_INDICATION already defined
#endif
#define NM_CAR_WAKEUPRX_INDICATION [!//
[!IF "(node:existsAndTrue(NmCarWakeUpRxEnabled))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]


#if (defined NM_NM_INCLUDE_BSWM_HEADER)
#error NM_NM_INCLUDE_BSWM_HEADER already defined
#endif
/** \brief Define for Car wakeup callout */
[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmCarWakeUpRxEnabled)"!]

#if (defined NM_NM_CAR_WAKEUP_CALLBACK)
#error NM_NM_CAR_WAKEUP_CALLBACK already defined
#endif

[!IF "node:exists(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmCarWakeUpCallback)"!]
/* !LINKSTO Nm.SWS_Nm_00252,1, Nm.SWS_Nm_00291,1, Nm.ECUC_Nm_00234,1 */
#define NM_NM_CAR_WAKEUP_CALLBACK [!"(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmCarWakeUpCallback)"!]
#define NM_NM_INCLUDE_BSWM_HEADER STD_OFF
[!ELSE!]
/* !LINKSTO Nm.SWS_Nm_00285,1 */
#define NM_NM_CAR_WAKEUP_CALLBACK BswM_NmIf_CarWakeUpIndication
#define NM_NM_INCLUDE_BSWM_HEADER STD_ON
[!ENDIF!]

[!ELSE!] /* node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmCarWakeUpRxEnabled)" */
#define NM_NM_INCLUDE_BSWM_HEADER STD_OFF
[!ENDIF!]

#if (defined NM_PROVIDE_REMOTE_SLEEP_CALLBACKS)
#error NM_PROVIDE_REMOTE_SLEEP_CALLBACKS already defined
#endif
[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmProvideRemoteSleepCallbacks)"!]

#define NM_PROVIDE_REMOTE_SLEEP_CALLBACKS STD_ON

#if (defined NM_REMOTE_SLEEP_INDICATION_CALLBACK)
#error NM_REMOTE_SLEEP_INDICATION_CALLBACK already defined
#endif
#define NM_REMOTE_SLEEP_INDICATION_CALLBACK [!"as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmRemoteSleepIndicationCallback"!]

#if (defined NM_REMOTE_SLEEP_CANCELLATION_CALLBACK)
#error NM_REMOTE_SLEEP_CANCELLATION_CALLBACK already defined
#endif
#define NM_REMOTE_SLEEP_CANCELLATION_CALLBACK [!"as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmRemoteSleepCancellationCallback"!]

[!ELSE!]
#define NM_PROVIDE_REMOTE_SLEEP_CALLBACKS STD_OFF
[!ENDIF!]

/** \brief Enable State change notification callout */
#if (defined NM_STATE_CHANGE_NOTIFICATION_CALLOUT)
#error NM_STATE_CHANGE_NOTIFICATION_CALLOUT already defined
#endif
#define NM_STATE_CHANGE_NOTIFICATION_CALLOUT [!//
[!IF "(node:existsAndTrue(NmStateChangeNotificationCallout)) "!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined NM_STATE_REPORT_ENABLED)
#error NM_STATE_REPORT_ENABLED already defined
#endif
#define NM_STATE_REPORT_ENABLED [!//
[!IF "count(../../NmChannelConfig/eb-list::*[node:existsAndTrue(NmStateReportEnabled)]) != 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]


/** \brief Enable Synchronized pnc shutdown */
#if (defined NM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED)
#error NM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED already defined
#endif
[!IF "(node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmSynchronizedPncShutdownEnabled))"!]
#define NM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED STD_ON     
[!ELSE!]
#define NM_SYNCHRONIZED_PNC_SHUTDOWN_ENABLED STD_OFF
[!ENDIF!]     

[!ENDSELECT!][!//

[!//
[!LOOP "NmChannelConfig/eb-list::*"!][!//
#if (defined NmConf_[!"node:name(..)"!]_[!"as:name(.)"!])
#error NmConf_[!"node:name(..)"!]_[!"as:name(.)"!] already defined
#endif
/** \brief Symbolic name for the NM channel "[!"node:name(.)"!]" */
#define NmConf_[!"node:name(..)"!]_[!"as:name(.)"!]   [!"NmChannelId"!]U

#if (defined NM_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined [!"as:name(.)"!])
#error [!"as:name(.)"!] already defined
#endif

/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) [!"NmChannelId"!] */
#define [!"as:name(.)"!]                     [!"NmChannelId"!]U

#if (defined Nm_[!"as:name(.)"!])
#error Nm_[!"as:name(.)"!] already defined
#endif

/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define Nm_[!"as:name(.)"!]   [!"NmChannelId"!]U
#endif /* NM_PROVIDE_LEGACY_SYMBOLIC_NAMES */
[!ENDLOOP!][!//

/** \brief greatest value of configured Nm Channel ID */
#if (defined NM_MAX_CHANNELID)
#error NM_MAX_CHANNELID already defined
#endif
#define NM_MAX_CHANNELID [!"num:max(NmChannelConfig/eb-list::*/NmChannelId)"!]U

/** \brief Number of Nm channels */
#if (defined NM_CHANNEL_NUM)
#error NM_CHANNEL_NUM already defined
#endif
#define NM_CHANNEL_NUM                 [!"num:i(count(NmChannelConfig/eb-list::*))"!]U

[!IF "node:existsAndTrue(NmGlobalConfig/NmGlobalFeatures/NmCoordinatorSupportEnabled)"!][!//
[!/* Though this symbol is only used internally we generate it in this
   * header to eliminate the need for a dedicated Nm_Int_Cfg.h file */!][!//
/** \brief Number of coordinated clusters */
#if (defined NM_CC_NUM)
#error NM_CC_NUM already defined
#endif
/* !LINKSTO Nm.SWS_Nm_00167,1 */
#define NM_CC_NUM                      [!//
[!"num:i(num:order(NmChannelConfig/eb-list::*[node:exists(NmCoordClusterIndex)]/NmCoordClusterIndex)[last()] + 1)"!]U
[!/* NmCoordClusterIndex is zero based and consecutive, order the indices and
   * take largest index plus 1 */!][!//
[!ENDIF!][!//

/** \brief Number of used underlying BusNm modules */
#if (defined NM_BUSNM_NUM)
#error NM_BUSNM_NUM already defined
#endif
#define NM_BUSNM_NUM                   [!"num:i($BusNmNum)"!]U

/** \brief Flag indicating if CanNm is used */
#if (defined NM_CANNM_USED)
#error NM_CANNM_USED already defined
#endif
#define NM_CANNM_USED                  [!//
[!IF "$CanNmEnabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
/** \brief Flag indicating if FrNm is used */
#if (defined NM_FRNM_USED)
#error NM_FRNM_USED already defined
#endif
#define NM_FRNM_USED                   [!//
[!IF "$FrNmEnabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
/** \brief Flag indicating if UdpNm is used */
#if (defined NM_UDPNM_USED)
#error NM_UDPNM_USED already defined
#endif
#define NM_UDPNM_USED                   [!//
[!IF "$UdpNmEnabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
/** \brief Flag indicating the use of generic NMs */
#if (defined NM_GENERICNM_USED)
#error NM_GENERICNM_USED already defined
#endif
#define NM_GENERICNM_USED                   [!//
[!IF "$GenericNmEnabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Specifies in single client server is used for Nm_PassiveStartup, Nm_NetworkRequest, Nm_NetworkRelease and Nm_NetworkGwEraRequest */
#if (defined NM_MULTICORE_USE_SINGLE_CS)
#error NM_MULTICORE_USE_SINGLE_CS already defined
#endif
#define NM_MULTICORE_USE_SINGLE_CS                   [!//
[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreUseSingleCS = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]


/** \brief Check if Nm stack is provided by EB */
#if (defined EB_NM_STACK)
#error EB_NM_STACK already defined
#endif

/* !LINKSTO Nm.EB.EB_NM_STACK,1 */
#if (((NM_CANNM_USED == STD_ON) && (!defined EB_CANNM)) || \
     ((NM_FRNM_USED == STD_ON)  && (!defined EB_FRNM)) || \
     ((NM_UDPNM_USED == STD_ON) && (!defined EB_UDPNM)) || \
     (NM_GENERICNM_USED == STD_ON))
#define EB_NM_STACK STD_OFF
#else
#define EB_NM_STACK STD_ON
#endif /* (((CANNM_USED == STD_ON) && (!defined EB_CANNM)) || \
        *  ((FRNM_USED == STD_ON)  && (!defined EB_FRNM)) || \
        *  ((UDPNM_USED == STD_ON) && (!defined EB_UDPNM)) || \
        *  (NM_GENERICNM_USED == STD_ON))
        */


[!SELECT "NmGlobalConfig/NmGlobalFeatures"!]
[!IF "$BusNmNum = 1"!][!//
[!VAR "BusNmName" = "text:split($BusNmList)[position() = 1]"!][!//

#if (defined NM_MULTIPLE_BUS_TYPES)
#error NM_MULTIPLE_BUS_TYPES already defined
#endif
#define NM_MULTIPLE_BUS_TYPES STD_OFF

#if (defined NM_BUSNM_PASSIVE_START_UP)
#error NM_BUSNM_PASSIVE_START_UP already defined
#endif
/* !LINKSTO Nm.EB.SchM_Call_CanNm_PassiveStartUp,1, Nm.EB.SchM_Call_UdpNm_PassiveStartUp,1 */
/* !LINKSTO Nm.EB.SchM_Call_FrNm_PassiveStartUp,1 */
[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]
  [!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreUseSingleCS)"!]
    [!IF "num:i(count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*)) = 1"!]
#define NM_BUSNM_PASSIVE_START_UP(nmNetworkHandle)      \
  SchM_Call_Nm_RequiredCSEntry_Nm_MultipleNetworkOperations_[!"node:name(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[1])"!](nmNetworkHandle, NM_MULTI_CORE_USE_SINGLE_CS_PASSIVE_STARTUP)
    [!ELSE!] [!/* [!IF "num:i(count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*)) = 1"!] */!]
#define NM_BUSNM_PASSIVE_START_UP(nmNetworkHandle)      \
  Nm_MultipleNetworkOperations(nmNetworkHandle, NM_MULTI_CORE_USE_SINGLE_CS_PASSIVE_STARTUP)
    [!ENDIF!] [!/* [!IF "num:i(count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*)) = 1"!] */!]
  [!ELSE!] [!/* [!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreUseSingleCS)"!] */!]
/** \brief SchM call for BusNm_PassiveStartup */
#define NM_BUSNM_PASSIVE_START_UP(nmNetworkHandle)      \
  SchM_Call_Nm_RequiredCSEntry_Nm_PassiveStartUp_[!"node:name(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[1])"!](nmNetworkHandle)
  [!ENDIF!] [!/* [!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreUseSingleCS)"!] */!]
[!ELSE!]
#define NM_BUSNM_PASSIVE_START_UP(nmNetworkHandle)      \
  [!"$BusNmName"!]_PassiveStartUp(nmNetworkHandle)
[!ENDIF!]

#if (defined NM_BUSNM_GET_STATE)
#error NM_BUSNM_GET_STATE already defined
#endif
#define NM_BUSNM_GET_STATE(nmNetworkHandle, nmStatePtr, nmModePtr)      \
  [!"$BusNmName"!]_GetState((nmNetworkHandle), (nmStatePtr), (nmModePtr))
[!IF "count(../../NmChannelConfig/eb-list::*[node:existsAndFalse(NmPassiveModeEnabled)]) != 0"!][!//
#if (defined NM_BUSNM_NETWORK_REQUEST)
#error NM_BUSNM_NETWORK_REQUEST already defined
#endif

#if (defined NM_BUSNM_NETWORK_RELEASE)
#error NM_BUSNM_NETWORK_RELEASE already defined
#endif

#if (EB_NM_STACK == STD_ON)
#if (defined NM_BUSNM_NETWORK_GW_ERA_REQUEST)
#error NM_BUSNM_NETWORK_GW_ERA_REQUEST already defined
#endif
#endif /* (EB_NM_STACK == STD_ON) */

/* !LINKSTO Nm.EB.SchM_Call_UdpNm_NetworkRequest,1, Nm.EB.SchM_Call_FrNm_NetworkRequest,1 */
/* !LINKSTO Nm.EB.SchM_Call_CanNm_NetworkRequest,1 */
[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]
  [!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreUseSingleCS)"!]
    [!IF "num:i(count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*)) = 1"!]
#define NM_BUSNM_NETWORK_REQUEST(nmNetworkHandle)      \
  SchM_Call_Nm_RequiredCSEntry_Nm_MultipleNetworkOperations_[!"node:name(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[1])"!](nmNetworkHandle, NM_MULTI_CORE_USE_SINGLE_CS_NETWORK_REQUEST)

#define NM_BUSNM_NETWORK_RELEASE(nmNetworkHandle)      \
  SchM_Call_Nm_RequiredCSEntry_Nm_MultipleNetworkOperations_[!"node:name(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[1])"!](nmNetworkHandle, NM_MULTI_CORE_USE_SINGLE_CS_NETWORK_RELEASE)

#if (EB_NM_STACK == STD_ON)
/** \brief SchM call for BusNm_NetworkGwEraRequest */
#define NM_BUSNM_NETWORK_GW_ERA_REQUEST(nmNetworkHandle)      \
  SchM_Call_Nm_RequiredCSEntry_Nm_MultipleNetworkOperations_[!"node:name(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[1])"!](nmNetworkHandle, NM_MULTI_CORE_USE_SINGLE_CS_GW_ERA_NETWORK_REQUEST)
#endif  /* (EB_NM_STACK == STD_ON) */
    [!ELSE!] [!/* [!IF "num:i(count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*)) = 1"!] */!]
#define NM_BUSNM_NETWORK_REQUEST(nmNetworkHandle)      \
  Nm_MultipleNetworkOperations(nmNetworkHandle, NM_MULTI_CORE_USE_SINGLE_CS_NETWORK_REQUEST)

#define NM_BUSNM_NETWORK_RELEASE(nmNetworkHandle)      \
  Nm_MultipleNetworkOperations(nmNetworkHandle, NM_MULTI_CORE_USE_SINGLE_CS_NETWORK_RELEASE)
#if (EB_NM_STACK == STD_ON)
/** \brief SchM call for BusNm_NetworkGwEraRequest */
#define NM_BUSNM_NETWORK_GW_ERA_REQUEST(nmNetworkHandle)      \
  Nm_MultipleNetworkOperations(nmNetworkHandle, NM_MULTI_CORE_USE_SINGLE_CS_GW_ERA_NETWORK_REQUEST)
#endif  /* (EB_NM_STACK == STD_ON) */
    [!ENDIF!] [!/* [!IF "num:i(count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*)) = 1"!] */!]
  [!ELSE!] [!/* [!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreUseSingleCS)"!] */!]
/** \brief SchM call for BusNm_NetworkRequest */
#define NM_BUSNM_NETWORK_REQUEST(NetworkHandle)         \
  SchM_Call_Nm_RequiredCSEntry_Nm_NetworkRequest_[!"node:name(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[1])"!](NetworkHandle)
/* !LINKSTO Nm.EB.SchM_Call_CanNm_NetworkRelease,1, Nm.EB.SchM_Call_UdpNm_NetworkRelease,1 */
/* !LINKSTO Nm.EB.SchM_Call_FrNm_NetworkRelease,1 */
/** \brief SchM call for BusNm_NetworkRelease */
#define NM_BUSNM_NETWORK_RELEASE(NetworkHandle)         \
  SchM_Call_Nm_RequiredCSEntry_Nm_NetworkRelease_[!"node:name(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[1])"!](NetworkHandle)

#if (EB_NM_STACK == STD_ON)
/** \brief SchM call for BusNm_NetworkGwEraRequest */
#define NM_BUSNM_NETWORK_GW_ERA_REQUEST(NetworkHandle)         \
  SchM_Call_Nm_RequiredCSEntry_Nm_NetworkGwEraRequest_[!"node:name(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[1])"!](NetworkHandle)
#endif  /* (EB_NM_STACK == STD_ON) */
  [!ENDIF!] [!/* [!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreUseSingleCS)"!] */!]
[!ELSE!]
#define NM_BUSNM_NETWORK_REQUEST(NetworkHandle)         \
  [!"$BusNmName"!]_NetworkRequest(NetworkHandle)

#define NM_BUSNM_NETWORK_RELEASE(NetworkHandle)         \
  [!"$BusNmName"!]_NetworkRelease(NetworkHandle)

#if (EB_NM_STACK == STD_ON)
 #define NM_BUSNM_NETWORK_GW_ERA_REQUEST(NetworkHandle)         \
  [!"$BusNmName"!]_NetworkGwEraRequest(NetworkHandle)
#endif /* (EB_NM_STACK == STD_ON) */

[!ENDIF!]
[!ENDIF!]

[!IF "node:existsAndTrue(NmUserDataEnabled)"!][!//
#if (defined NM_BUSNM_GET_USER_DATA)
#error NM_BUSNM_GET_USER_DATA already defined
#endif
#define NM_BUSNM_GET_USER_DATA(nmNetworkHandle, nmUserDataPtr)          \
  [!"$BusNmName"!]_GetUserData((nmNetworkHandle), (nmUserDataPtr))

[!IF "(count(../../NmChannelConfig/eb-list::*[node:existsAndFalse(NmPassiveModeEnabled)]) != 0) and (node:existsAndFalse(NmComUserDataSupport))"!][!//
#if (defined NM_BUSNM_SET_USER_DATA)
#error NM_BUSNM_SET_USER_DATA already defined
#endif
#define NM_BUSNM_SET_USER_DATA(NetworkHandle, nmUserDataPtr) \
  [!"$BusNmName"!]_SetUserData((NetworkHandle), (nmUserDataPtr))
[!ENDIF!][!//
[!ENDIF!][!//

[!IF "count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:existsAndTrue(NmNodeIdEnabled)]) > 0"!][!//
#if (defined NM_BUSNM_GET_NODE_IDENTIFIER)
#error NM_BUSNM_GET_NODE_IDENTIFIER already defined
#endif
#define NM_BUSNM_GET_NODE_IDENTIFIER(NetworkHandle, nmNodeIdPtr)        \
  [!"$BusNmName"!]_GetNodeIdentifier((NetworkHandle), (nmNodeIdPtr))

#if (defined NM_BUSNM_GET_LOCAL_NODE_IDENTIFIER)
#error NM_BUSNM_GET_LOCAL_NODE_IDENTIFIER already defined
#endif
#define NM_BUSNM_GET_LOCAL_NODE_IDENTIFIER(NetworkHandle, nmNodeIdPtr)  \
  [!"$BusNmName"!]_GetLocalNodeIdentifier((NetworkHandle), (nmNodeIdPtr))
[!ENDIF!][!//
[!IF "count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:existsAndTrue(NmNodeDetectionEnabled)]) > 0"!][!//
#if (defined NM_BUSNM_REPEAT_MESSAGE_REQUEST)
#error NM_BUSNM_REPEAT_MESSAGE_REQUEST already defined
#endif
#define NM_BUSNM_REPEAT_MESSAGE_REQUEST(NetworkHandle)  \
  [!"$BusNmName"!]_RepeatMessageRequest(NetworkHandle)
[!ENDIF!][!//
[!IF "(count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:existsAndTrue(NmNodeIdEnabled)]) > 0) or
      (count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:existsAndTrue(NmNodeDetectionEnabled)]) > 0) or
      (node:existsAndTrue(NmUserDataEnabled))"!]
#if (defined NM_BUSNM_GET_PDU_DATA)
#error NM_BUSNM_GET_PDU_DATA already defined
#endif
#define NM_BUSNM_GET_PDU_DATA(NetworkHandle, nmPduData) \
  [!"$BusNmName"!]_GetPduData((NetworkHandle), (nmPduData))
[!ENDIF!][!//

[!IF "node:existsAndTrue(NmRemoteSleepIndEnabled)"!][!//
#if (defined NM_BUSNM_CHECK_REMOTE_SLEEP_INDICATION)
#error NM_BUSNM_CHECK_REMOTE_SLEEP_INDICATION already defined
#endif
#define NM_BUSNM_CHECK_REMOTE_SLEEP_INDICATION(                         \
  nmNetworkHandle, nmRemoteSleepIndPtr)                                 \
  [!"$BusNmName"!]_CheckRemoteSleepIndication(                          \
    (nmNetworkHandle), (nmRemoteSleepIndPtr))
[!ENDIF!][!//

[!IF "node:existsAndTrue(NmBusSynchronizationEnabled)"!][!//
#if (defined NM_BUSNM_REQUEST_BUS_SYNCHRONIZATION)
#error NM_BUSNM_REQUEST_BUS_SYNCHRONIZATION already defined
#endif
#define NM_BUSNM_REQUEST_BUS_SYNCHRONIZATION(NetworkHandle,ReqBusSynch_RetVal)

[!ENDIF!][!//

/* Since only one underlaying device is configured, the parameter NetworkHandle is not used therefore
 * it is cast to void.
 * Direct cast to void is done in Nm to avoid compilation errors in case of static code checking
 * enabled (EB_STATIC_CHECK is defined).
 */

[!IF "node:existsAndTrue(NmComControlEnabled)"!][!//
#if (defined NM_BUSNM_DISABLE_COMMUNICATION)
#error NM_BUSNM_DISABLE_COMMUNICATION already defined
#endif
/* !LINKSTO Nm.SWS_Nm_00134,1 */
#define NM_BUSNM_DISABLE_COMMUNICATION(NetworkHandle)   \
  [!"$BusNmName"!]_DisableCommunication(NetworkHandle)

#if (defined NM_BUSNM_ENABLE_COMMUNICATION)
#error NM_BUSNM_ENABLE_COMMUNICATION already defined
#endif
/* !LINKSTO Nm.SWS_Nm_00136,1 */
#define NM_BUSNM_ENABLE_COMMUNICATION(NetworkHandle)    \
  [!"$BusNmName"!]_EnableCommunication(NetworkHandle)
[!ENDIF!][!//

[!ELSE!][!/* $BusNmNum = 1 */!][!//
/* multiple BusNm */

#if (defined NM_MULTIPLE_BUS_TYPES)
#error NM_MULTIPLE_BUS_TYPES already defined
#endif
#define NM_MULTIPLE_BUS_TYPES STD_ON

/** \brief Retrieve the index of the BusNm
 **
 ** The macro evaluates to the index of the underlying bus being looked up.
 **
 ** \param[in] NmChannelId Nm Channel ID */
#if (defined NM_GET_BUSNM_IDX)
#error NM_GET_BUSNM_IDX already defined
#endif
#define NM_GET_BUSNM_IDX(NmChannelId) (Nm_ChannelConfig[(Nm_ChanIdxFromNetworkHandle[(NmChannelId)])].BusNmId)

#if (defined NM_BUSNM_PASSIVE_START_UP)
#error NM_BUSNM_PASSIVE_START_UP already defined
#endif
[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]
[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreUseSingleCS = 'true')"!]
#define NM_BUSNM_PASSIVE_START_UP(nmNetworkHandle)              \
  Nm_MultipleNetworkOperations(nmNetworkHandle, NM_MULTI_CORE_USE_SINGLE_CS_PASSIVE_STARTUP)
[!ELSE!]
/** \brief SchM call for BusNm_PassiveStartup */
#define NM_BUSNM_PASSIVE_START_UP(nmNetworkHandle)              \
  Nm_ChannelConfig[Nm_ChanIdxFromNetworkHandle[(nmNetworkHandle)]].PassiveStartUp( \
    nmNetworkHandle)
[!ENDIF!]
[!ELSE!]
#define NM_BUSNM_PASSIVE_START_UP(nmNetworkHandle)              \
  Nm_BusNmFp[NM_GET_BUSNM_IDX(nmNetworkHandle)].PassiveStartUp( \
    nmNetworkHandle)
[!ENDIF!]

#if (defined NM_BUSNM_GET_STATE)
#error NM_BUSNM_GET_STATE already defined
#endif
#define NM_BUSNM_GET_STATE(nmNetworkHandle, nmStatePtr, nmModePtr)      \
  Nm_BusNmFp[NM_GET_BUSNM_IDX(nmNetworkHandle)].GetState(               \
    (nmNetworkHandle), (nmStatePtr), (nmModePtr))
[!IF "count(../../NmChannelConfig/eb-list::*[node:existsAndFalse(NmPassiveModeEnabled)]) != 0"!]
#if (defined NM_BUSNM_NETWORK_REQUEST)
#error NM_BUSNM_NETWORK_REQUEST already defined
#endif
[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]
[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreUseSingleCS = 'true')"!]
#define NM_BUSNM_NETWORK_REQUEST(nmNetworkHandle)              \
  Nm_MultipleNetworkOperations(nmNetworkHandle, NM_MULTI_CORE_USE_SINGLE_CS_NETWORK_REQUEST)
[!ELSE!]
/** \brief SchM call for BusNm_NetworkRequest */
#define NM_BUSNM_NETWORK_REQUEST(nmNetworkHandle)               \
  Nm_ChannelConfig[Nm_ChanIdxFromNetworkHandle[(nmNetworkHandle)]].NetworkRequest( \
    nmNetworkHandle)
[!ENDIF!]
[!ELSE!]
#define NM_BUSNM_NETWORK_REQUEST(nmNetworkHandle)               \
  Nm_BusNmFp[NM_GET_BUSNM_IDX(nmNetworkHandle)].NetworkRequest( \
    nmNetworkHandle)
[!ENDIF!]

#if (defined NM_BUSNM_NETWORK_RELEASE)
#error NM_BUSNM_NETWORK_RELEASE already defined
#endif
[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]
[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreUseSingleCS = 'true')"!]
#define NM_BUSNM_NETWORK_RELEASE(nmNetworkHandle)              \
  Nm_MultipleNetworkOperations(nmNetworkHandle, NM_MULTI_CORE_USE_SINGLE_CS_NETWORK_RELEASE)
[!ELSE!]
/** \brief SchM call for BusNm_NetworkRelease */
#define NM_BUSNM_NETWORK_RELEASE(nmNetworkHandle)               \
  Nm_ChannelConfig[Nm_ChanIdxFromNetworkHandle[(nmNetworkHandle)]].NetworkRelease( \
    nmNetworkHandle)
[!ENDIF!]
[!ELSE!]
#define NM_BUSNM_NETWORK_RELEASE(nmNetworkHandle)               \
  Nm_BusNmFp[NM_GET_BUSNM_IDX(nmNetworkHandle)].NetworkRelease( \
    nmNetworkHandle)
[!ENDIF!]

#if (EB_NM_STACK == STD_ON)
#if (defined NM_BUSNM_NETWORK_GW_ERA_REQUEST)
#error NM_BUSNM_NETWORK_GW_ERA_REQUEST already defined
#endif

[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]
[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreUseSingleCS = 'true')"!]
#define NM_BUSNM_NETWORK_GW_ERA_REQUEST(nmNetworkHandle)              \
  Nm_MultipleNetworkOperations(nmNetworkHandle, NM_MULTI_CORE_USE_SINGLE_CS_GW_ERA_NETWORK_REQUEST)
[!ELSE!]
/** \brief SchM call for BusNm_NetworkGwEraRequest */
#define NM_BUSNM_NETWORK_GW_ERA_REQUEST(nmNetworkHandle)               \
  Nm_ChannelConfig[Nm_ChanIdxFromNetworkHandle[(nmNetworkHandle)]].NetworkGwEraRequest( \
    nmNetworkHandle)
[!ENDIF!]
[!ELSE!]
#define NM_BUSNM_NETWORK_GW_ERA_REQUEST(nmNetworkHandle)               \
  Nm_BusNmFp[NM_GET_BUSNM_IDX(nmNetworkHandle)].NetworkGwEraRequest( \
    nmNetworkHandle)
[!ENDIF!]
#endif /* (EB_NM_STACK == STD_ON) */

[!ENDIF!][!//
[!IF "node:existsAndTrue(NmUserDataEnabled)"!][!//
#if (defined NM_BUSNM_GET_USER_DATA)
#error NM_BUSNM_GET_USER_DATA already defined
#endif
#define NM_BUSNM_GET_USER_DATA(nmNetworkHandle, nmUserDataPtr)          \
  Nm_BusNmFp[NM_GET_BUSNM_IDX(nmNetworkHandle)].GetUserData(            \
    (nmNetworkHandle), (nmUserDataPtr))
[!IF "(count(../../NmChannelConfig/eb-list::*[node:existsAndFalse(NmPassiveModeEnabled)]) != 0) and (node:existsAndFalse(NmComUserDataSupport))"!]

#if (defined NM_BUSNM_SET_USER_DATA_FCT_PTR)
#error NM_BUSNM_SET_USER_DATA_FCT_PTR already defined
#endif
#define NM_BUSNM_SET_USER_DATA_FCT_PTR(NetworkHandle)    \
  Nm_BusNmFp[NM_GET_BUSNM_IDX(NetworkHandle)].SetUserData

#if (defined NM_BUSNM_SET_USER_DATA)
#error NM_BUSNM_SET_USER_DATA already defined
#endif
#define NM_BUSNM_SET_USER_DATA(NetworkHandle, nmUserDataPtr)    \
  Nm_BusNmFp[NM_GET_BUSNM_IDX(NetworkHandle)].SetUserData(      \
    (NetworkHandle), (nmUserDataPtr))
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:existsAndTrue(NmNodeIdEnabled)]) > 0"!][!//
#if (defined NM_BUSNM_GET_NODE_IDENTIFIER)
#error NM_BUSNM_GET_NODE_IDENTIFIER already defined
#endif
#define NM_BUSNM_GET_NODE_IDENTIFIER(NetworkHandle, nmNodeIdPtr)      \
  Nm_BusNmFp[NM_GET_BUSNM_IDX(NetworkHandle)].GetNodeIdentifier(      \
    (NetworkHandle), (nmNodeIdPtr))

#if (defined NM_BUSNM_GET_LOCAL_NODE_IDENTIFIER)
#error NM_BUSNM_GET_LOCAL_NODE_IDENTIFIER already defined
#endif
#define NM_BUSNM_GET_LOCAL_NODE_IDENTIFIER(NetworkHandle, nmNodeIdPtr)  \
  Nm_BusNmFp[NM_GET_BUSNM_IDX(NetworkHandle)].GetLocalNodeIdentifier(   \
    (NetworkHandle), (nmNodeIdPtr))
[!ENDIF!][!//
[!IF "count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:existsAndTrue(NmNodeDetectionEnabled)]) > 0"!][!//
#if (defined NM_BUSNM_REPEAT_MESSAGE_REQUEST)
#error NM_BUSNM_REPEAT_MESSAGE_REQUEST already defined
#endif
#define NM_BUSNM_REPEAT_MESSAGE_REQUEST(NetworkHandle)                \
  Nm_BusNmFp[NM_GET_BUSNM_IDX(NetworkHandle)].RepeatMessageRequest(   \
    NetworkHandle)
[!ENDIF!][!//
[!IF "(count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:existsAndTrue(NmNodeIdEnabled)]) > 0) or
      (count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:existsAndTrue(NmNodeDetectionEnabled)]) > 0) or
      (node:existsAndTrue(NmUserDataEnabled))"!]
#if (defined NM_BUSNM_GET_PDU_DATA)
#error NM_BUSNM_GET_PDU_DATA already defined
#endif
#define NM_BUSNM_GET_PDU_DATA(NetworkHandle, nmPduData)       \
  Nm_BusNmFp[NM_GET_BUSNM_IDX(NetworkHandle)].GetPduData(     \
    (NetworkHandle), (nmPduData))
[!ENDIF!][!//

[!IF "node:existsAndTrue(NmRemoteSleepIndEnabled)"!][!//
#if (defined NM_BUSNM_CHECK_REMOTE_SLEEP_INDICATION)
#error NM_BUSNM_CHECK_REMOTE_SLEEP_INDICATION already defined
#endif
#define NM_BUSNM_CHECK_REMOTE_SLEEP_INDICATION(                         \
  nmNetworkHandle, nmRemoteSleepIndPtr)                                 \
  Nm_BusNmFp[NM_GET_BUSNM_IDX(nmNetworkHandle)].CheckRemoteSleepIndication( \
    (nmNetworkHandle), (nmRemoteSleepIndPtr))
[!ENDIF!][!//

[!IF "node:existsAndTrue(NmBusSynchronizationEnabled)"!][!//

#if (defined NM_BUSNM_REQUEST_BUS_SYNCHRONIZATION)
#error NM_BUSNM_REQUEST_BUS_SYNCHRONIZATION already defined
#endif

/* !LINKSTO Nm.EB.SchM_Call_CanNm_RequestBusSynchronization,1 */
/* !LINKSTO Nm.EB.SchM_Call_FrNm_RequestBusSynchronization,1 */
/* !LINKSTO Nm.EB.SchM_Call_UdpNm_RequestBusSynchronization,1 */
[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]
/** \brief SchM call for BusNm_RequestBusSynchronization */
#define NM_BUSNM_REQUEST_BUS_SYNCHRONIZATION(NetworkHandle,ReqBusSynch_RetVal)               \
do\
{\
  if (Nm_ChannelConfig[Nm_ChanIdxFromNetworkHandle[(NetworkHandle)]].RequestBusSynchronization != NULL_PTR)\
  {\
    if(SCHM_E_OK == Nm_ChannelConfig[Nm_ChanIdxFromNetworkHandle[(NetworkHandle)]].RequestBusSynchronization(\
      NetworkHandle))\
    {\
      ReqBusSynch_RetVal = E_OK; \
    }\
  }\
}\
while(0);
[!ELSE!]
#define NM_BUSNM_REQUEST_BUS_SYNCHRONIZATION(NetworkHandle,ReqBusSynch_RetVal) \
  (void)Nm_BusNmFp[NM_GET_BUSNM_IDX(NetworkHandle)].RequestBusSynchronization( \
    NetworkHandle)
[!ENDIF!]
[!ENDIF!][!//

[!IF "node:existsAndTrue(NmComControlEnabled)"!][!//
#if (defined NM_BUSNM_DISABLE_COMMUNICATION)
#error NM_BUSNM_DISABLE_COMMUNICATION already defined
#endif
#define NM_BUSNM_DISABLE_COMMUNICATION(NetworkHandle)                   \
  Nm_BusNmFp[NM_GET_BUSNM_IDX(NetworkHandle)].DisableCommunication(     \
    NetworkHandle)
#if (defined NM_BUSNM_ENABLE_COMMUNICATION)
#error NM_BUSNM_ENABLE_COMMUNICATION already defined
#endif
#define NM_BUSNM_ENABLE_COMMUNICATION(NetworkHandle)                    \
  Nm_BusNmFp[NM_GET_BUSNM_IDX(NetworkHandle)].EnableCommunication(      \
    NetworkHandle)
[!ENDIF!][!//
[!ENDIF!][!/* $BusNmNum = 1 */!][!//


[!IF "(node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmSynchronizedPncShutdownEnabled))"!]
  [!IF "$BusNmNum = 1"!][!//
    [!VAR "BusNmName" = "text:split($BusNmList)[position() = 1]"!][!//
    [!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]
      [!IF "node:exists(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[1]/NmBusType/eb-choice::*[1]/NmGenericBusNmPrefix)"!]
#if (defined NM_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN_MC_OFF_OR_GENERIC)
#error NM_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN_MC_OFF_OR_GENERIC already defined
#endif
#define NM_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN_MC_OFF_OR_GENERIC(nmNetworkHandle, PncId) \
 [!"$BusNmName"!]_RequestSynchronizedPncShutdown(nmNetworkHandle, PncId)    
      [!ELSE!] [!/*[!IF "node:exists(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[1]/NmBusType/eb-choice::*[1]/NmGenericBusNmPrefix")!]*/!]
#if (defined NM_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN_MC)
#error NM_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN_MC already defined
#endif
#define NM_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN_MC(data) \
 SchM_Send_Nm_Nm_RequestSynchronizedPncShutdown_Nm_To_[!"$BusNmName"!]_DataSet(data)
      [!ENDIF!] [!/*[!IF "node:exists(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[1]/NmBusType/eb-choice::*[1]/NmGenericBusNmPrefix")!]*/!]
    [!ELSE!]  [!/* [!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]*/!]
#if (defined NM_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN_MC_OFF_OR_GENERIC)
#error NM_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN_MC_OFF_OR_GENERIC already defined
#endif
#define NM_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN_MC_OFF_OR_GENERIC(nmNetworkHandle, PncId) \
 [!"$BusNmName"!]_RequestSynchronizedPncShutdown(nmNetworkHandle, PncId)
    [!ENDIF!] [!/* [!/*[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]*/!]
  [!ELSE!] [!/*  [!IF "$BusNmNum = 1"!] */!] [!//
    [!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]
      [!IF "($CanNmEnabled = 'true') or ($FrNmEnabled = 'true') or ($UdpNmEnabled = 'true')"!]
#if (defined NM_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN_MC)
#error NM_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN_MC already defined
#endif
#define NM_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN_MC(nmNetworkHandle, data) \
 Nm_BusNmFp[NM_GET_BUSNM_IDX(nmNetworkHandle)].RequestSynchronizedPncShutdownMulticore(data)
      [!ENDIF!][!/*[!IF "($CanNmEnabled = 'true') or ($FrNmEnabled = 'true') or ($UdpNmEnabled = 'true')"!]*/!]
      [!IF "$GenericNmEnabled = 'true'"!]      
#if (defined NM_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN_MC_OFF_OR_GENERIC)
#error NM_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN_MC_OFF_OR_GENERIC already defined
#endif
#define NM_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN_MC_OFF_OR_GENERIC(nmNetworkHandle, PncId) \
 Nm_BusNmFp[NM_GET_BUSNM_IDX(nmNetworkHandle)].RequestSynchronizedPncShutdownMcOffOrGeneric(nmNetworkHandle, PncId)
      [!ENDIF!]
    [!ELSE!] [!/*[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]*/!]
#if (defined NM_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN_MC_OFF_OR_GENERIC)
#error NM_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN_MC_OFF_OR_GENERIC already defined
#endif
#define NM_REQUEST_SYNCHRONIZED_PNC_SHUTDOWN_MC_OFF_OR_GENERIC(nmNetworkHandle, PncId) \
 Nm_BusNmFp[NM_GET_BUSNM_IDX(nmNetworkHandle)].RequestSynchronizedPncShutdownMcOffOrGeneric(nmNetworkHandle, PncId)
    [!ENDIF!] [!/*[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]*/!]
  [!ENDIF!] [!/* [!IF "$BusNmNum = 1"!]*/!][!//
[!ENDIF!] [!/* [!IF "node:exists(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmSynchronizedPncShutdownEnabled) and 
             * (node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmSynchronizedPncShutdownEnabled))"!]
             */!]


/*==================[type definitions]======================================*/

[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]
  /** \brief Type for BusNm function pointers */
typedef Std_ReturnType (*Nm_BusNm_CallsFctPtrType1)(uint8 data0);
typedef Std_ReturnType (*Nm_BusNm_CallsFctPtrType2)(uint8 data0,uint8 data1);
[!ENDIF!]

[!INDENT "0"!]
  [!IF "(num:i($BusNmNum) > 1) or
        (node:existsAndTrue(NmCoordinatorSupportEnabled)) or
        (count(../../NmChannelConfig/eb-list::*[node:existsAndTrue(NmStateReportEnabled)]) != 0) or
        (num:i(count(../../NmChannelConfig/eb-list::*)) > 1)"!]
  /** \brief Type holding a channel configuration */
    typedef struct
    {
[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!]
[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreUseSingleCS = 'true')"!]
        [!WS "2"!]Nm_BusNm_CallsFctPtrType2 MultipleNetworkOperations;
    [!IF "$GenericNmEnabled = 'true'"!]
        [!WS "2"!]Nm_BusNm_CallsFctPtrType1 PassiveStartUp;
      [!IF "count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:exists(NmBusType/eb-choice::*[1]/NmGenericBusNmPrefix) and node:existsAndFalse(NmPassiveModeEnabled)]) != 0"!]        
        [!WS "2"!]Nm_BusNm_CallsFctPtrType1 NetworkRequest;
        [!WS "2"!]Nm_BusNm_CallsFctPtrType1 NetworkRelease;
      [!ENDIF!]
    [!ENDIF!]        
[!ELSE!] [!/*[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreUseSingleCS = 'true')"!]*/!]
        [!WS "2"!]Nm_BusNm_CallsFctPtrType1 PassiveStartUp;
[!IF "count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:existsAndFalse(NmPassiveModeEnabled)]) != 0"!]
        [!WS "2"!]Nm_BusNm_CallsFctPtrType1 NetworkRequest;
        [!WS "2"!]Nm_BusNm_CallsFctPtrType1 NetworkRelease;
#if (EB_NM_STACK == STD_ON)
        [!WS "2"!]Nm_BusNm_CallsFctPtrType1 NetworkGwEraRequest;
#endif /* (EB_NM_STACK == STD_ON) */
[!ENDIF!] [!/* [!IF "count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:existsAndFalse(NmPassiveModeEnabled)]) != 0"!] */!]
[!ENDIF!] [!/*[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreUseSingleCS = 'true')"!]*/!]

[!IF "count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:existsAndFalse(NmPassiveModeEnabled)]) != 0"!]
[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmBusSynchronizationEnabled)"!]
        [!WS "2"!]Nm_BusNm_CallsFctPtrType1 RequestBusSynchronization;
[!ENDIF!] [!/* [!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmBusSynchronizationEnabled)"!] */!]
[!ENDIF!] [!/* [!IF "count(as:modconf('Nm')[1]/NmChannelConfig/eb-list::*[node:existsAndFalse(NmPassiveModeEnabled)]) != 0"!] */!]
[!ENDIF!] [!/* [!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmMultiCoreSupport)"!] */!]
      [!IF "node:existsAndTrue(NmCoordinatorSupportEnabled)"!]
        [!WS "2"!]uint16            ShutdownDelayTimer;
        [!WS "2"!]uint16            WaitForShutdownTime;
      [!ENDIF!]
      [!IF "count(../../NmChannelConfig/eb-list::*[node:existsAndTrue(NmStateReportEnabled)]) != 0"!]
        [!WS "2"!]Com_SignalIdType  NmComHandleId;
      [!ENDIF!]
      [!IF "num:i($BusNmNum) > 1"!]
        [!WS "2"!]/** Index of underlying BusNm module */
        [!WS "2"!]uint8             BusNmId;
      [!ENDIF!]
      [!IF "node:existsAndTrue(NmCoordinatorSupportEnabled)"!]
        [!WS "2"!]uint8             CoordClusterIndex;
        [!WS "2"!]boolean           NmChannelSleepMaster;
        [!WS "2"!]boolean           NmSynchronizingNetwork;
      [!ENDIF!]
      [!WS "2"!]boolean             PassiveModeEnabled;
      [!WS "2"!]boolean             NmNodeIdEnabled;
      [!WS "2"!]boolean             NmNodeDetectionEnabled;
[!IF "node:exists(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmSynchronizedPncShutdownEnabled) and 
     (node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmSynchronizedPncShutdownEnabled))"!]      
      [!WS "2"!]boolean             IsGenericBus;      
[!ENDIF!] [!/*[!IF "node:exists(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmSynchronizedPncShutdownEnabled) and 
             *(node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmSynchronizedPncShutdownEnabled))"!]*/!]            
             
    } Nm_ChannelConfigType;
  [!ENDIF!]
[!ENDINDENT!]
[!ENDSELECT!]
/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

[!/* though Nm_ChannelConfig[] does not need to be generated it is a array
   * needed by Nm.h and Nm_Cbk.h.  Instead of creating a common header
   * included by Nm.h and Nm_Cbk.h we simply declare the array here */!][!//

#define NM_START_SEC_CONST_UNSPECIFIED
#include <Nm_MemMap.h>

#if ( (NM_BUSNM_NUM > 1U)                        ||     \
      (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) ||     \
      (NM_STATE_REPORT_ENABLED == STD_ON)        ||     \
      (NM_CHANNEL_NUM > 1U)                             \
    )
/** \brief Array holding the configuration of each channel */
extern CONST(Nm_ChannelConfigType, NM_CONST) Nm_ChannelConfig[NM_CHANNEL_NUM];
#endif

#define NM_STOP_SEC_CONST_UNSPECIFIED
#include <Nm_MemMap.h>

#define NM_START_SEC_CONST_8
#include <Nm_MemMap.h>

#if ( (NM_BUSNM_NUM > 1U)                         ||    \
      (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)  ||    \
      (NM_DEV_ERROR_DETECT == STD_ON)             ||    \
      (NM_STATE_REPORT_ENABLED == STD_ON)         ||    \
      (NM_CHANNEL_NUM > 1U)                             \
    )
extern CONST(uint8, NM_CONST) Nm_ChanIdxFromNetworkHandle[NM_MAX_CHANNELID + 1U];
#endif

#define NM_STOP_SEC_CONST_8
#include <Nm_MemMap.h>

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmCarWakeUpRxEnabled)"!]

[!IF "node:exists(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmCarWakeUpCallback)"!]
#define NM_START_SEC_CODE
#include <Nm_MemMap.h>

/** \brief Car Wakeup Callout
 **
 ** Callout function for NmCarWakeUp
 **
 ** \param[in] nmNetworkHandle */
extern FUNC(void, NM_CODE) [!"(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmCarWakeUpCallback)"!]
(
  NetworkHandleType  nmNetworkHandle
);

#define NM_STOP_SEC_CODE
#include <Nm_MemMap.h>
[!ENDIF!]
[!ENDIF!]

[!IF "node:existsAndTrue(as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmProvideRemoteSleepCallbacks)"!]
#define NM_START_SEC_CODE
#include <Nm_MemMap.h>

/** \brief Remote Sleep Indication Callout
 **
 ** Callout function for Nm Remote Sleep Indication
 **
 ** \param[in] nmNetworkHandle */
extern FUNC(void, NM_CODE) [!"as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmRemoteSleepIndicationCallback"!]
(
  NetworkHandleType  nmNetworkHandle
);

/** \brief Remote Sleep Cancellation Callout
 **
 ** Callout function for Nm Remote Sleep Cancellation
 **
 ** \param[in] nmNetworkHandle */
extern FUNC(void, NM_CODE) [!"as:modconf('Nm')[1]/NmGlobalConfig/NmGlobalFeatures/NmRemoteSleepCancellationCallback"!]
(
  NetworkHandleType  nmNetworkHandle
);

#define NM_STOP_SEC_CODE
#include <Nm_MemMap.h>
[!ENDIF!]

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
#endif /* ifndef NM_CFG_H */
