/**
 * \file
 *
 * \brief AUTOSAR CanNm
 *
 * This file contains the implementation of the AUTOSAR
 * module CanNm.
 *
 * \version 6.20.6
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* !LINKSTO CanNm.ASR403.CANNM304,1 */
#ifndef CANNM_CFG_H
#define CANNM_CFG_H

/*------------------[Defensive programming]---------------------------------*/
[!SELECT "CanNmDefensiveProgramming"!][!//

#if (defined CANNM_DEFENSIVE_PROGRAMMING_ENABLED)
#error CANNM_DEFENSIVE_PROGRAMMING_ENABLED is already defined
#endif
/** \brief Defensive programming usage
 **
 ** En- or disables the usage of the defensive programming */
#define CANNM_DEFENSIVE_PROGRAMMING_ENABLED   [!//
[!IF "(node:existsAndTrue(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmDevErrorDetect)) and (node:existsAndTrue(CanNmDefProgEnabled))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANNM_PRECONDITION_ASSERT_ENABLED)
#error CANNM_PRECONDITION_ASSERT_ENABLED is already defined
#endif
/** \brief Precondition assertion usage
 **
 ** En- or disables the usage of precondition assertion checks */
#define CANNM_PRECONDITION_ASSERT_ENABLED     [!//
[!IF "(node:existsAndTrue(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmDevErrorDetect)) and (node:existsAndTrue(CanNmDefProgEnabled)) and (node:existsAndTrue(CanNmPrecondAssertEnabled))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANNM_POSTCONDITION_ASSERT_ENABLED)
#error CANNM_POSTCONDITION_ASSERT_ENABLED is already defined
#endif
/** \brief Postcondition assertion usage
 **
 ** En- or disables the usage of postcondition assertion checks */
#define CANNM_POSTCONDITION_ASSERT_ENABLED    [!//
[!IF "(node:existsAndTrue(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmDevErrorDetect)) and (node:existsAndTrue(CanNmDefProgEnabled)) and (node:existsAndTrue(CanNmPostcondAssertEnabled))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANNM_UNREACHABLE_CODE_ASSERT_ENABLED)
#error CANNM_UNREACHABLE_CODE_ASSERT_ENABLED is already defined
#endif
/** \brief Unreachable code assertion usage
 **
 ** En- or disables the usage of unreachable code assertion checks */
#define CANNM_UNREACHABLE_CODE_ASSERT_ENABLED [!//
[!IF "(node:existsAndTrue(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmDevErrorDetect)) and (node:existsAndTrue(CanNmDefProgEnabled)) and (node:existsAndTrue(CanNmUnreachAssertEnabled))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANNM_INVARIANT_ASSERT_ENABLED)
#error CANNM_INVARIANT_ASSERT_ENABLED is already defined
#endif
/** \brief Invariant assertion usage
 **
 ** En- or disables the usage of invariant assertion checks */
#define CANNM_INVARIANT_ASSERT_ENABLED        [!//
[!IF "(node:existsAndTrue(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmDevErrorDetect)) and (node:existsAndTrue(CanNmDefProgEnabled)) and (node:existsAndTrue(CanNmInvariantAssertEnabled))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANNM_STATIC_ASSERT_ENABLED)
#error CANNM_STATIC_ASSERT_ENABLED is already defined
#endif
/** \brief Static assertion usage
 **
 ** En- or disables the usage of static assertion checks */
#define CANNM_STATIC_ASSERT_ENABLED           [!//
[!IF "(node:existsAndTrue(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmDevErrorDetect)) and (node:existsAndTrue(CanNmDefProgEnabled)) and (node:existsAndTrue(CanNmStaticAssertEnabled))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!ENDSELECT!][!//




[!SELECT "CanNmGeneral"!][!//

#if (defined CANNM_DET_RUNTIME_CHECKS)
#error CANNM_DET_RUNTIME_CHECKS is already defined
#endif
/** \brief DET runtime checks reporting
 **
 ** En- or disables the reporting of the DET runtime checks */
#define CANNM_DET_RUNTIME_CHECKS   [!//
[!IF "CanNmDetRuntimeChecks = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!ENDSELECT!][!//


[!/*  select first of the multiple config containers */!][!//
[!SELECT "CanNmGlobalConfig/eb-list::*[1]"!][!//

/*==================[includes]==============================================*/

#include <TSAutosar.h>    /* EB specific standard types      */
/* !LINKSTO CanNm.EB.CanNmNodeIdCallbackHeaderName,1 */
[!IF "node:exists(CanNmNodeIdCallback)"!]
#include <[!"CanNmNodeIdCallbackHeader"!]>  /* CanNm node Id callback header */
[!ENDIF!]

#ifndef CANNM_NO_CFGCLASSMIX_REQUIRED
#include <CanNm_SymbolicNames_PBcfg.h>
#endif /* CANNM_NO_CFGCLASSMIX_REQUIRED */

#undef CANNM_NO_CFGCLASSMIX_REQUIRED

[!INCLUDE "../../generate_macros/CanNm_Macros.m"!][!//

/*==================[macros]================================================*/
#if (defined CANNM_CFG_SIGNATURE)
#error CANNM_CFG_SIGNATURE is already defined
#endif

#define CANNM_CFG_SIGNATURE [!"asc:getConfigSignature(as:modconf('CanNm')[1]//eb-list::*[not(child::*) and (node:configclass() = 'PreCompile') ])"!]U /* Compile time verification value */

#if (defined CANNM_PUBLIC_INFO_SIGNATURE)
#error CANNM_PUBLIC_INFO_SIGNATURE is already defined
#endif

#define CANNM_PUBLIC_INFO_SIGNATURE [!"asc:getConfigSignature(node:difference(as:modconf('CanNm')[1]/CommonPublishedInformation//eb-list::*[not(child::*) and (node:configclass() = 'PublishedInformation') ], as:modconf('CanNm')[1]/CommonPublishedInformation/Release))"!]U /* PublicInfoSignature */

#if (defined CANNM_PBCFGM_SUPPORT_ENABLED)
#error CANNM_PBCFGM_SUPPORT_ENABLED is already defined
#endif
/* !LINKSTO CanNm.EB.Impl.PbCfgM,1 */
#define CANNM_PBCFGM_SUPPORT_ENABLED [!IF "node:existsAndTrue(node:contains(util:distinct(node:refs(as:modconf('PbcfgM')/PbcfgMBswModules/eb-list::*/PbcfgMBswModuleRef)), as:modconf('CanNm')))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/* ----- Pre-processor switch to enable/diable relocateable postbuild config ----- */
#if (defined CANNM_RELOCATABLE_CFG_ENABLE)
#error CANNM_RELOCATABLE_CFG_ENABLE is already defined
#endif

/* !LINKSTO CanNm.EB.Impl.Relocatable,1 */
#if (CANNM_PBCFGM_SUPPORT_ENABLED == STD_ON)
#define CANNM_RELOCATABLE_CFG_ENABLE [!IF "node:exists(as:modconf('PbcfgM')/PbcfgMGeneral/PbcfgMRelocatableCfgEnable) and (node:existsAndTrue(as:modconf('PbcfgM')/PbcfgMGeneral/PbcfgMRelocatableCfgEnable))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#else
#define CANNM_RELOCATABLE_CFG_ENABLE [!IF "node:existsAndTrue(as:modconf('CanNm')[1]/CanNmGeneral/CanNmRelocatablePbcfgEnable)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#endif

#if (defined CANNM_VERSION_INFO_API)
#error CANNM_VERSION_INFO_API is already defined
#endif
/* !LINKSTO CanNm.ECUC_CanNm_00003,1 */
#define CANNM_VERSION_INFO_API            [!//
[!IF "node:existsAndTrue(CanNmVersionInfoApi)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANNM_COM_CONTROL_ENABLED)
#error CANNM_COM_CONTROL_ENABLED is already defined
#endif
/* !LINKSTO CanNm.ECUC_CanNm_00013,1, CanNm.ASR403.CANNM168,1 */
#define CANNM_COM_CONTROL_ENABLED         [!//
[!IF "node:existsAndTrue(CanNmComControlEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANNM_STATE_CHANGE_IND_ENABLED)
#error CANNM_STATE_CHANGE_IND_ENABLED is already defined
#endif
/* !LINKSTO CanNm.ECUC_CanNm_00012,1 */
#define CANNM_STATE_CHANGE_IND_ENABLED    [!//
[!IF "node:existsAndTrue(CanNmStateChangeIndEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANNM_PASSIVE_MODE_ENABLED)
#error CANNM_PASSIVE_MODE_ENABLED is already defined
#endif
/* !LINKSTO CanNm.ECUC_CanNm_00010,1, CanNm.SWS_CanNm_00161,1 */
#define CANNM_PASSIVE_MODE_ENABLED        [!//
[!IF "node:existsAndTrue(CanNmPassiveModeEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANNM_PDU_RX_INDICATION_ENABLED)
#error CANNM_PDU_RX_INDICATION_ENABLED is already defined
#endif
/* !LINKSTO CanNm.ECUC_CanNm_00011,1 */
#define CANNM_PDU_RX_INDICATION_ENABLED   [!//
[!IF "node:existsAndTrue(CanNmPduRxIndicationEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANNM_IMMEDIATE_RESTART_ENABLED)
#error CANNM_IMMEDIATE_RESTART_ENABLED is already defined
#endif
/* !LINKSTO CanNm.ECUC_CanNm_00009,1 */
#define CANNM_IMMEDIATE_RESTART_ENABLED   [!//
[!IF "node:existsAndTrue(CanNmImmediateRestartEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANNM_IMMEDIATE_TXCONF_ENABLED)
#error CANNM_IMMEDIATE_TXCONF_ENABLED is already defined
#endif
/* !LINKSTO CanNm.ECUC_CanNm_00041,1, CanNm.SWS_CanNm_00071,1 */
#define CANNM_IMMEDIATE_TXCONF_ENABLED    [!//
[!IF "node:existsAndTrue(CanNmImmediateTxconfEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANNM_USER_DATA_ENABLED)
#error CANNM_USER_DATA_ENABLED is already defined
#endif
/* !LINKSTO CanNm.ECUC_CanNm_00004,1, CanNm.SWS_CanNm_00158,1 */
#define CANNM_USER_DATA_ENABLED           [!//
[!IF "node:existsAndTrue(CanNmUserDataEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANNM_COM_USER_DATA_SUPPORT)
#error CANNM_COM_USER_DATA_SUPPORT is already defined
#endif
/* !LINKSTO CanNm.ECUC_CanNm_00044,1 */
#define CANNM_COM_USER_DATA_SUPPORT       [!//
[!IF "node:existsAndTrue(CanNmComUserDataSupport)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANNM_REMOTE_SLEEP_IND_ENABLED)
#error CANNM_REMOTE_SLEEP_IND_ENABLED is already defined
#endif
/* !LINKSTO CanNm.ECUC_CanNm_00055,1, CanNm.SWS_CanNm_00149,1 */
#define CANNM_REMOTE_SLEEP_IND_ENABLED    [!//
[!IF "node:existsAndTrue(CanNmRemoteSleepIndEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANNM_NODE_ID_ENABLED)
#error CANNM_NODE_ID_ENABLED is already defined
#endif

/* !LINKSTO CanNm.EB.CanNmNodeIdEnabled,1 */
#define CANNM_NODE_ID_ENABLED             [!//
[!IF "count(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmChannelConfig/eb-list::*[node:existsAndTrue(CanNmNodeIdEnabled)]) > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANNM_REPEAT_MSG_IND_ENABLED)
#error CANNM_REPEAT_MSG_IND_ENABLED is already defined
#endif
/* !LINKSTO CanNm.ECUC_CanNm_00089,1 */
#define CANNM_REPEAT_MSG_IND_ENABLED      [!//
[!IF "count(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmChannelConfig/eb-list::*[node:existsAndTrue(CanNmRepeatMsgIndEnabled)]) > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANNM_NODE_DETECTION_ENABLED)
#error CANNM_NODE_DETECTION_ENABLED is already defined
#endif
/* !LINKSTO CanNm.ECUC_CanNm_00088,1 */
#define CANNM_NODE_DETECTION_ENABLED      [!//
[!IF "count(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmChannelConfig/eb-list::*[node:existsAndTrue(CanNmNodeDetectionEnabled)]) > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANNM_BUS_SYNCHRONIZATION_ENABLED)
#error CANNM_BUS_SYNCHRONIZATION_ENABLED is already defined
#endif
/* !LINKSTO CanNm.ECUC_CanNm_00006,1, CanNm.SWS_CanNm_00185,1 */
#define CANNM_BUS_SYNCHRONIZATION_ENABLED [!//
[!IF "node:existsAndTrue(CanNmBusSynchronizationEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANNM_BUS_LOAD_REDUCTION_ENABLED)
#error CANNM_BUS_LOAD_REDUCTION_ENABLED is already defined
#endif
/* !LINKSTO CanNm.ECUC_CanNm_00040,1, CanNm.SWS_CanNm_00052,1 */
#define CANNM_BUS_LOAD_REDUCTION_ENABLED  [!//
[!IF "node:existsAndTrue(CanNmBusLoadReductionEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANNM_IMMEDIATE_TRANSMISSION)
#error CANNM_IMMEDIATE_TRANSMISSION is already defined
#endif
#define CANNM_IMMEDIATE_TRANSMISSION  [!//
[!IF "num:i(count(CanNmChannelConfig/eb-list::*[CanNmImmediateNmTransmissions > 0])) > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANNM_DEV_ERROR_DETECT)
#error CANNM_DEV_ERROR_DETECT is already defined
#endif
/** \brief Switch for DET usage */
/* !LINKSTO CanNm.ECUC_CanNm_00002,1, CanNm.ASR403.CANNM188,1 */
#define CANNM_DEV_ERROR_DETECT            [!//
[!IF "node:existsAndTrue(CanNmDevErrorDetect)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANNM_NUMBER_OF_CHANNELS)
#error CANNM_NUMBER_OF_CHANNELS is already defined
#endif
/* !LINKSTO CanNm.ASR403.CANNM014_Conf,1 */
/** \brief Maximum number of channels */
#define CANNM_NUMBER_OF_CHANNELS               [!//
[!"num:i(count(CanNmChannelConfig/eb-list::*))"!]U

#if (defined CANNM_INDEXFROMNMCHANNELHANDLE_NUM)
#error CANNM_INDEXFROMNMCHANNELHANDLE_NUM is already defined
#endif
/** \brief Number of elements in array CanNm_IndexFromComMChannelHandle[] */
#define CANNM_INDEXFROMNMCHANNELHANDLE_NUM     [!//
[!"num:i(num:max(util:distinct(node:refs(CanNmChannelConfig/eb-list::*/CanNmComMNetworkHandleRef))/ComMChannelId)+1)"!]U

#if (defined CANNM_ACTIVE_WAKEUP_BIT_ENABLED)
#error CANNM_ACTIVE_WAKEUP_BIT_ENABLED is already defined
#endif
/* !LINKSTO CanNm.ECUC_CanNm_00084,1 */
/** \brief Macro to indicate if Active wake up bit is present in CBV */
#define CANNM_ACTIVE_WAKEUP_BIT_ENABLED        [!//
[!IF "node:existsAndTrue(CanNmActiveWakeupBitEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#if (defined CANNM_NODEID_CALLBACK_ENABLED)
#error CANNM_NODEID_CALLBACK_ENABLED is already defined
#endif
/* !LINKSTO CanNm.EB.CanNmNodeIdCallbackName,1 */
/** \brief Macro to indicate if Node Id callback is enabled */
#define CANNM_NODEID_CALLBACK_ENABLED          [!//
[!IF "node:exists(CanNmNodeIdCallback)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

[!IF "node:exists(CanNmNodeIdCallback)"!]
#if (defined CANNM_NODEID_CALLBACK_NAME)
#error CANNM_NODEID_CALLBACK_NAME is already defined
#endif
/** \brief Name of Node Id callback function */
#define CANNM_NODEID_CALLBACK_NAME   [!"CanNmNodeIdCallback"!]
[!ENDIF!]

#if (defined CANNM_CARWAKEUP_RX_ENABLED)
#error CANNM_CARWAKEUP_RX_ENABLED is already defined
#endif

#define CANNM_CARWAKEUP_RX_ENABLED        [!//
[!IF "count(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmChannelConfig/eb-list::*[node:existsAndTrue(CanNmCarWakeUpRxEnabled)]) > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/*------------------[PN Extensions]-------------------------------------*/
[!IF "node:existsAndTrue(as:modconf('CanNm')[1]/CanNmGeneral/CanNmPnSupported)"!]
/* !LINKSTO CanNm.SWS_CanNm_00415,1 */
/* !LINKSTO CanNm.ECUC_CanNm_00061,1 */
#if (defined CANNM_PN_INFO_LENGTH)
#error CANNM_PN_INFO_LENGTH is already defined
#endif
#define CANNM_PN_INFO_LENGTH    [!"CanNmPnInfo/CanNmPnInfoLength"!]U

/* Size of array for mapping PN EIRA timer */
[!//
[!// Calculate size of array required for EIRA timer
[!IF "(node:existsAndTrue(CanNmPnEiraCalcEnabled)) or  num:i(count(CanNmChannelConfig/eb-list::*[(node:exists(CanNmPnEraCalcEnabled)) and (node:existsAndTrue(CanNmPnEraCalcEnabled))])) > 0"!][!//
[!NOCODE!][!//
[!VAR "EiraMaxTimerSize" = "0"!][!//
[!IF "node:exists(as:modconf('CanNm')[1]/CanNmGeneral/CanNmMaxPn)"!][!//
[!VAR "EiraMaxTimerSize" = "node:value(as:modconf('CanNm')[1]/CanNmGeneral/CanNmMaxPn)"!][!//
[!ELSE!][!//
[!VAR "EiraMaxTimerSize" = "node:value(CanNmPnInfo/CanNmPnInfoLength) * 8"!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//

#if (defined CANNM_EIRA_MAX_TIMER_SIZE)
#error CANNM_EIRA_MAX_TIMER_SIZE is already defined
#endif

#define CANNM_EIRA_MAX_TIMER_SIZE    [!"num:i($EiraMaxTimerSize)"!]U  /* CanNm Eira Maximum Timer array size */
[!ENDIF!]

/* !LINKSTO CanNm.ECUC_CanNm_00060,1 */
#if (defined CANNM_PN_INFO_OFFSET)
#error CANNM_PN_INFO_OFFSET is already defined
#endif
#define CANNM_PN_INFO_OFFSET     [!//
              [!"CanNmPnInfo/CanNmPnInfoOffset"!]U

/** CanNmPnEiraCalcEnabled **/
/* !LINKSTO CanNm.ECUC_CanNm_00070,1 */
#if (defined CANNM_PN_EIRA_CALC_ENABLED)
#error CANNM_PN_EIRA_CALC_ENABLED is already defined
#endif
#define CANNM_PN_EIRA_CALC_ENABLED             [!//
[!IF "(node:existsAndTrue(CanNmPnEiraCalcEnabled))"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** CanNmPnEraCalcEnabled **/
/* !LINKSTO CanNm.ECUC_CanNm_00067,1 */
#if (defined CANNM_PN_ERA_CALC_ENABLED)
#error CANNM_PN_ERA_CALC_ENABLED is already defined
#endif

#define CANNM_PN_ERA_CALC_ENABLED              [!//
[!IF "num:i(count(CanNmChannelConfig/eb-list::*[node:existsAndTrue(CanNmPnEraCalcEnabled)])) > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** CanNmPnResetTime **/
#if (defined CANNM_PN_RESET_TIME)
#error CANNM_PN_RESET_TIME is already defined
#endif
#define CANNM_PN_RESET_TIME [!//
    [!"num:i((CanNmPnResetTime * 1000) div (CanNmMainFunctionPeriod * 1000))"!]U

[!/* get Eira PduId by EcuC reference from PduR, existence is checked in xdm */!][!//
[!IF "node:existsAndTrue(CanNmPnEiraCalcEnabled)"!][!//
#if (defined CANNM_PN_EIRA_PDUID)
#error CANNM_PN_EIRA_PDUID is already defined
#endif
#define CANNM_PN_EIRA_PDUID  [!//
    [!"as:modconf('PduR')[1]/PduRRoutingTables/eb-list::*/PduRRoutingTable/eb-list::*/PduRRoutingPath/eb-list::*/PduRSrcPdu[PduRSrcPduRef=node:current()/CanNmPnEiraRxNSduRef
]/PduRSourcePduHandleId"!]U/* CanNmPnEraRx Id*/
[!ENDIF!]

[!CALL "GetSynchronizedPncShutdownEnabled"!]
/** CanNmSynchronizedPncShutdownEnabled **/
/* !LINKSTO CanNm.ASRR2111.ECUC_CanNm_00097,1 */
#if (defined CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED)
#error CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED is already defined
#endif
#define CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED             [!//
[!IF "$SynchronizedPncShutdownEnabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** CanNmPnShutdownMessageRetransmissionDuration **/
#if (defined CANNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_DURATION)
#error CANNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_DURATION is already defined
#endif
[!IF "node:exists(CanNmPnShutdownMessageRetransmissionDuration) and (node:existsAndFalse(CanNmImmediateTxconfEnabled))"!]
#define CANNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_DURATION             [!//
    [!"num:i((CanNmPnShutdownMessageRetransmissionDuration * 1000) div (CanNmMainFunctionPeriod * 1000))"!]U
[!ELSE!]
#define CANNM_PN_SHUTDOWN_MESSAGE_RETRANSMISSION_DURATION 0
[!ENDIF!]

#if (defined CANNM_PN_SYNC_SHUTDOWN_ERROR_REACTION_ENABLED)
#error CANNM_PN_SYNC_SHUTDOWN_ERROR_REACTION_ENABLED is already defined
#endif
#define CANNM_PN_SYNC_SHUTDOWN_ERROR_REACTION_ENABLED             [!//
[!IF "node:existsAndTrue(CanNmPnSyncShutdownErrorReactionEnabled)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** Number of active gateways with synchronized shutdown enabled **/
#if (defined CANNM_PN_GATEWAY_TYPE_ACTIVE_NUM)
#error CANNM_PN_GATEWAY_TYPE_ACTIVE_NUM is already defined
#endif
#define CANNM_PN_GATEWAY_TYPE_ACTIVE_NUM             [!//
    [!"num:i(count(CanNmChannelConfig/eb-list::*[node:exists(node:ref(CanNmComMNetworkHandleRef)/ComMPncGatewayType) and (node:ref(CanNmComMNetworkHandleRef)/ComMPncGatewayType = 'COMM_GATEWAY_TYPE_ACTIVE') and (node:existsAndTrue(CanNmSynchronizedPncShutdownEnabled))]))"!]

/** Number of passive gateways with synchronized shutdown enabled **/
#if (defined CANNM_PN_GATEWAY_TYPE_PASSIVE_NUM)
#error CANNM_PN_GATEWAY_TYPE_PASSIVE_NUM is already defined
#endif
#define CANNM_PN_GATEWAY_TYPE_PASSIVE_NUM             [!//
    [!"num:i(count(CanNmChannelConfig/eb-list::*[node:exists(node:ref(CanNmComMNetworkHandleRef)/ComMPncGatewayType) and (node:ref(CanNmComMNetworkHandleRef)/ComMPncGatewayType = 'COMM_GATEWAY_TYPE_PASSIVE') and (node:existsAndTrue(CanNmSynchronizedPncShutdownEnabled))]))"!]

#define CANNM_PN_SUPPORTED  STD_ON
[!ELSE!]
#if (defined CANNM_PN_SUPPORTED)
#error CANNM_PN_SUPPORTED is already defined
#endif
#define CANNM_PN_SUPPORTED  STD_OFF

#if (defined CANNM_PN_EIRA_CALC_ENABLED)
#error CANNM_PN_EIRA_CALC_ENABLED is already defined
#endif
#define CANNM_PN_EIRA_CALC_ENABLED STD_OFF

#if (defined CANNM_PN_ERA_CALC_ENABLED)
#error CANNM_PN_ERA_CALC_ENABLED is already defined
#endif
#define CANNM_PN_ERA_CALC_ENABLED STD_OFF

#if (defined CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED)
#error CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED is already defined
#endif
#define CANNM_PN_SYNCHRONIZED_SHUTDOWN_ENABLED STD_OFF

[!ENDIF!]

/** \brief Enable multicore support*/
#if (defined CANNM_MULTICORE_ENABLED)
#error CANNM_MULTICORE_ENABLED already defined
#endif

/* !LINKSTO CanNm.EB.Config.CanNmMultiCoreSupport,1 */
#define CANNM_MULTICORE_ENABLED           [!//
[!IF "node:existsAndTrue(as:modconf('CanNm')[1]/CanNmGeneral/CanNmMultiCoreSupport)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief Specifies in single client server is used for CanNm_PassiveStartup, CanNm_NetworkRequest, CanNm_NetworkRelease and CanNm_NetworkGwEraRequest */
#if (defined CANNM_MULTICORE_USE_SINGLE_CS)
#error CANNM_MULTICORE_USE_SINGLE_CS already defined
#endif

/* !LINKSTO CanNm.EB.CanNmMultiCoreUseSingleCS,1 */
#define CANNM_MULTICORE_USE_SINGLE_CS           [!//
[!IF "node:existsAndTrue(as:modconf('CanNm')[1]/CanNmGeneral/CanNmMultiCoreUseSingleCS)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/* !LINKSTO CanNm.EB.Config.CanNmChannelMultiCoreSupport,1 */
/** \brief Enable multicore support*/
#if (defined CANNM_MULTICORE_CHANNEL_SUPPORT)
#error CANNM_MULTICORE_CHANNEL_SUPPORT already defined
#endif

[!CALL "GetMulticorePerChannelSupport"!][!//
#define CANNM_MULTICORE_CHANNEL_SUPPORT   [!//
[!IF "$MulticorePerChannelSupport = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/*------------------[Symbolic Name for CanNmRxPduId]------------------------*/
[!LOOP "CanNmChannelConfig/eb-list::*"!][!/*
*/!]
/* !LINKSTO CanNm.EB.SymbolicName.CanNmRxPduId.NoShortName,1, CanNm.EB.SymbolicName.ecuc_sws_2108_3,1 */
/* It is possible to change SHORT-NAME of containers with multiplicity
 * of one within EB tresos Studio. So, the symbolic name generation shall be
 * according to requirement [ecuc_sws_2108] if a SHORT-NAME for the container
 * is specified and the macro is defined as follows:
 *   #define CanNmConf_CanNmRxPdu_<CTR_SHORT_NAME>
 *
 * If a SHORT-NAME is not specified the macro is defined as follows:
 *   #define CanNmConf_CanNmChannelConfig_<CHANNEL_NAME>_<CTR_NAME>
 */
[!LOOP "CanNmRxPdu/eb-list::*"!][!//
[!CALL "GetSymbolNameRx","ShortNameRef"="'.'"!]
#if (defined [!"$SymbolName"!])
#error [!"$SymbolName"!] already defined
#endif

/** \brief Symbolic name for the CanNm channel "[!"as:name(../..)"!]" */
#define [!"$SymbolName"!]  [!"CanNmRxPduId"!]U

#if (defined CANNM_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined [!"as:name(../..)"!]_[!"as:name(.)"!])
#error [!"as:name(../..)"!]_[!"as:name(.)"!] already defined
#endif

/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) [!"CanNmRxPduId"!] */
#define [!"as:name(../..)"!]_[!"as:name(.)"!] [!"CanNmRxPduId"!]U

#if (defined CanNm_[!"as:name(../..)"!]_[!"as:name(.)"!])
#error CanNm_[!"as:name(../..)"!]_[!"as:name(.)"!] already defined
#endif

/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define CanNm_[!"as:name(../..)"!]_[!"as:name(.)"!] [!"CanNmRxPduId"!]U
#endif /* CANNM_PROVIDE_LEGACY_SYMBOLIC_NAMES */
[!ENDLOOP!][!//
[!ENDLOOP!][!//

/*------------[Symbolic Name for CanNmTxConfirmationPduId]-------------------*/
[!LOOP "CanNmChannelConfig/eb-list::*/CanNmTxPdu"!][!/*
*/!]
/* !LINKSTO CanNm.EB.SymbolicName.ecuc_sws_2108_1,2, CanNm.EB.SymbolicName.CanNmTxConfirmationPduId.NoShortName,1 */
/* It is possible to change short name values of containers with multiplicity
 * of one within EB tresos Studio. So, the symbolic name generation shall be
 * according to requirement [ecuc_sws_2108] if a SHORT-NAME for the container
 * is specified and the macro is defined as follows:
 *   #define CanNmConf_CanNmTxPdu_<CTR_SHORT_NAME>
 *
 * If a SHORT-NAME is not specified the macro is defined as follows:
 *   #define CanNmConf_CanNmChannelConfig_<CHANNEL_NAME>_<CTR_NAME>
 */
[!/* The LOOP over node-set excludes OPTIONAL containers from processing thus
   * the symbolic name macros should just be generated in case of their presence.
   */!]
[!CALL "GetSymbolNameTx","ShortNameRef"="'.'""!]
#if (defined [!"$SymbolName"!])
#error [!"$SymbolName"!] already defined
#endif

/** \brief Symbolic name for the CanNm channel "[!"as:name(..)"!]" */
#define [!"$SymbolName"!]  [!"CanNmTxConfirmationPduId"!]U

#if (defined CANNM_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined [!"as:name(..)"!]_[!"node:name(.)"!])
#error [!"as:name(..)"!]_[!"node:name(.)"!] already defined
#endif

/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) [!"CanNmTxConfirmationPduId"!] */
#define [!"as:name(..)"!]_[!"node:name(.)"!]  [!"CanNmTxConfirmationPduId"!]U

#if (defined CanNm_[!"as:name(..)"!]_[!"node:name(.)"!])
#error CanNm_[!"as:name(..)"!]_[!"node:name(.)"!] already defined
#endif

/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define CanNm_[!"as:name(..)"!]_[!"node:name(.)"!]  [!"CanNmTxConfirmationPduId"!]U
#endif /* CANNM_PROVIDE_LEGACY_SYMBOLIC_NAMES */
[!ENDLOOP!][!//

/*-------------[Symbolic Name for CanNmTxUserDataPduId]--------------------*/
[!LOOP "CanNmChannelConfig/eb-list::*/CanNmUserDataTxPdu"!][!/*
*/!]
/* !LINKSTO CanNm.EB.SymbolicName.ecuc_sws_2108_2,1 */
/* !LINKSTO CanNm.EB.SymbolicName.CanNmTxUserDataPduId.NoShortName,1 */
/* It is possible to change short name values of containers with multiplicity
 * of one within EB tresos Studio. So, the symbolic name generation shall be
 * according to requirement [ecuc_sws_2108] if a SHORT-NAME for the container
 * is specified and the macro is defined as follows:
 *   #define CanNmConf_CanNmUserDataTxPdu_<CTR_SHORT_NAME>
 *
 * If a SHORT-NAME is not specified the macro is defined as follows:
 *   #define CanNmConf_CanNmChannelConfig_<CHANNEL_NAME>_<CTR_NAME>
 */
[!/* The LOOP over node-set excludes OPTIONAL containers from processing thus
   * the symbolic name macros should just be generated in case of their presence.
   */!]
[!CALL "GetSymbolNameTx","ShortNameRef"="'.'""!]
#if (defined [!"$SymbolName"!])
#error [!"$SymbolName"!] already defined
#endif

/** \brief Symbolic name for the CanNm channel "[!"as:name(..)"!]" */
#define [!"$SymbolName"!]  [!"CanNmTxUserDataPduId"!]U

#if (defined CANNM_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined [!"as:name(..)"!]_[!"node:name(.)"!])
#error [!"as:name(..)"!]_[!"node:name(.)"!] already defined
#endif

/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) [!"CanNmTxUserDataPduId"!] */
#define [!"as:name(..)"!]_[!"node:name(.)"!]  [!"CanNmTxUserDataPduId"!]U

#if (defined CanNm_[!"as:name(..)"!]_[!"node:name(.)"!])
#error CanNm_[!"as:name(..)"!]_[!"node:name(.)"!] already defined
#endif

/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define CanNm_[!"as:name(..)"!]_[!"node:name(.)"!]  [!"CanNmTxUserDataPduId"!]U
#endif /* CANNM_PROVIDE_LEGACY_SYMBOLIC_NAMES */
[!ENDLOOP!][!//

/*------------------[Hsm configuration]-------------------------------------*/

#if (defined CANNM_HSM_INST_MULTI_ENABLED)
#error CANNM_HSM_INST_MULTI_ENABLED already defined
#endif

#if (CANNM_NUMBER_OF_CHANNELS > 1U)
#define CANNM_HSM_INST_MULTI_ENABLED STD_ON
#else
#define CANNM_HSM_INST_MULTI_ENABLED STD_OFF
#endif

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

[!ENDSELECT!][!//
#endif /* ifndef CANNM_CFG_H */
/*==================[end of file]===========================================*/
