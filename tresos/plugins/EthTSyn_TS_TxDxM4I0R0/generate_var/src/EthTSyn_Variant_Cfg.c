/**
 * \file
 *
 * \brief AUTOSAR EthTSyn
 *
 * This file contains the implementation of the AUTOSAR
 * module EthTSyn.
 *
 * \version 4.0.10
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
[!CODE!]
[!AUTOSPACING!]
/*==================[inclusions]============================================*/
#include <EthTSyn_CfgTypes.h>
#if (defined ETHTSYN_POSTBUILD_VARIANT_DISABLED)
#include "EthTSyn_PBcfg.h"
#else
[!LOOP "variant:all()"!][!//
#include <EthTSyn[!"."!]_PBcfg.h>
[!ENDLOOP!][!//
#endif
[!INCLUDE "../../generate_macros/EthTSyn_Macros.m"!][!//
/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[internal constants]====================================*/

/*==================[external constants]====================================*/

#define ETHTSYN_START_SEC_CONFIG_DATA_UNSPECIFIED
#include <EthTSyn_MemMap.h>

[!IF "var:defined('postBuildVariant')"!]
[!/* Current postbuild configuration name
*/!][!VAR "initPredefinedCfgName"="concat('EthTSyn','_',$postBuildVariant,'_')"!]
[!ELSE!]
[!/* Current postbuild name
*/!][!VAR "initPredefinedCfgName"="string("EthTSyn")"!]
[!ENDIF!]
[!VAR "OffsetSlaveArrIndex"="0"!][!//
CONST(EthTSyn_ConfigType, ETHTSYN_APPL_CONST) [!"concat($initPredefinedCfgName,'Config_0')"!] =
{
  ETHTSYN_MAX_CTRL, /* MaxEthTSynCtrlIdx */
  ETHTSYN_MAX_SLAVE, /* MaxEthTSynSlaveIdx */
  {
  [!VAR "IcvTxStart"="0"!][!//
  [!VAR "IcvRxStart"="0"!][!//
  [!VAR "PortStart"="0"!][!//
  [!VAR "StbMRef"="0"!][!//
  [!VAR "HostPort"="0"!][!//
  [!VAR "OfsGlobalTimeDomainId"="255"!][!//
  [!VAR "OffsetTimeBaseId"="255"!][!//
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
  [!VAR "SlavePort"="0"!][!//
#endif
  [!VAR "SwitchCount"="1"!][!//
  [!LOOP "as:modconf('EthTSyn')[1]/EthTSynGlobalTimeDomain/*"!][!//
    [!IF "node:exists(./EthTSynPortConfig)"!][!//
    [!LOOP "./EthTSynPortConfig/*"!][!//
      [!IF "node:containsValue(../../EthTSynPortRole, 'EthTSynGlobalTimeSlave')"!][!//
      {
        [!IF "node:exists(../../EthTSynGlobalTimeDebounceTime)"!][!//
        [!CALL "DebounceFloatToMFC", "value"="../../EthTSynGlobalTimeDebounceTime"!]U, /* EthTSynGlobalTimeDebounceTime */
        [!ELSE!][!//
        0xFFFFFFFFU,  /* Debouncing is configurable per Port (Slave) */
        [!ENDIF!][!//
        0xFFFFU, /* CyclicMsgResumeTime dummy value (Slave) */
        0xFFFFU, /* SyncTxInterval dummy value (Slave) */
        [!IF "node:exists(./EthTSynPdelayConfig)"!][!//
        [!CALL "TimeoutFloatToMFC", "value"="./EthTSynPdelayConfig/EthTSynGlobalTimeTxPdelayReqPeriod"!]U, /* PdelayReqTxInterval (Slave) */
        [!IF "node:exists(./EthTSynPdelayConfig/EthTSynInitialGlobalTimeTxPdelayReqPeriod)"!][!//
        [!CALL "TimeoutFloatToMFC", "value"="./EthTSynPdelayConfig/EthTSynInitialGlobalTimeTxPdelayReqPeriod"!]U, /* InitialPdelayReqTxInterval (Slave) */
        [!ELSE!][!//
        0U,  /* InitialPdelayReqTxInterval (Slave) */
        [!ENDIF!][!//
        [!CALL "TimeoutFloatToMFC", "value"="./EthTSynPdelayConfig/EthTSynPdelayRespAndRespFollowUpTimeout"!]U, /* PdelayRespAndRespFollowUpTimeout (Slave) */
        [!CALL "PdelayNanoseconds", "value"="./EthTSynPdelayConfig/EthTSynGlobalTimePropagationDelay"!]U, /* DefaultPdelayNs (Slave) */
        [!ELSE!][!//
        [!IF "node:exists(./EthTSynDelayE2EConfig)"!][!//
        [!IF "node:exists(./EthTSynDelayE2EConfig/EthTSynGlobalTimeTxDelayE2EReqPeriod)"!][!//
        [!CALL "TimeoutFloatToMFC", "value"="./EthTSynDelayE2EConfig/EthTSynGlobalTimeTxDelayE2EReqPeriod"!]U, /* DelayReqTxInterval (Slave) */
        0U, /* InitialPdelayReqTxInterval not used */
        [!ELSE!][!//
        0U, /* DelayReqTxInterval not used */
        0U, /* InitialPdelayReqTxInterval not used */
        [!ENDIF!][!//
        [!CALL "TimeoutFloatToMFC", "value"="./EthTSynDelayE2EConfig/EthTSynDelayE2ERespTimeout"!]U, /* DelayRespAndRespFollowUpTimeout (Slave) */
        [!CALL "PdelayNanoseconds", "value"="./EthTSynDelayE2EConfig/EthTSynGlobalTimeDelayE2E"!]U, /* DefaultDelayNs (Slave) */
        [!ELSE!][!//
        0xFFFFFFFFU,  /* PdelayReqTxInterval (Slave) */
        0U,  /* InitialPdelayReqTxInterval (Slave) */
        0U,  /* PdelayRespAndRespFollowUpTimeout (Slave) */
        0U,  /* DefaultPdelayNs (Slave) */
        [!ENDIF!][!//
        [!ENDIF!][!//
        [!CALL "TimeoutFloatToMFC", "value"="../../EthTSynPortRole/EthTSynGlobalTimeFollowUpTimeout"!]U, /* EthTSynGlobalTimeFollowUpTimeout */
        [!CALL "TimeoutFloatToMFC", "value"="../../EthTSynGlobalTimeRxDebounceTime"!]U, /* EthTSynGlobalTimeRxDebounceTime */
        #if (ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
        [!IF "node:value(../../EthTSynPortRole/EthTSynReceiveSyncFupPairsPeriod) > 0"!][!//
        [!CALL "TimeoutFloatToMFC", "value"="../../EthTSynPortRole/EthTSynReceiveSyncFupPairsPeriod"!]U, /* ReceiveSyncFupPairTimeout (Slave) */
        [!ELSE!]
        0xFFFFFFFFU, /* Not used value*/
        [!ENDIF!]
        #endif
        #if (ETHTSYN_PROD_ERR_HANDLING_PDELAY_FAILED != TS_PROD_ERR_DISABLE)
        [!IF "node:value(../../EthTSynPortRole/EthTSynReceivePdelayRespFupPairsPeriod) > 0"!][!//
        [!CALL "TimeoutFloatToMFC", "value"="../../EthTSynPortRole/EthTSynReceivePdelayRespFupPairsPeriod"!]U, /* PdelayRespFupPairsPeriod  */
        [!ELSE!]
        0xFFFFFFFFU, /* Not used value*/
        [!ENDIF!]
        #endif
        [!IF "node:exists(./EthTSynPdelayConfig/EthTSynPdelayLatencyThreshold)"!][!//
        [!CALL "PdelayNanoseconds", "value"="./EthTSynPdelayConfig/EthTSynPdelayLatencyThreshold"!]U, /* EthTSynPdelayLatencyThreshold */
        [!ELSE!][!//
        [!IF "node:exists(./EthTSynDelayE2EConfig/EthTSynDelayE2ELatencyThreshold)"!][!//
        [!CALL "PdelayNanoseconds", "value"="./EthTSynDelayE2EConfig/EthTSynDelayE2ELatencyThreshold"!]U, /* EthTSynDelayE2ELatencyThreshold */
        [!ELSE!][!//
        0xFFFFFFFFU, /* EthTSynPdelayLatencyThreshold */
        [!ENDIF!]
        [!ENDIF!]
#if(ETHTSYN_ICV_USED == STD_ON)
        [!IF "node:exists(../../EthTSynPortRole/EthTSynGlobalTimeRxIcvVerification)"!][!//
        0U, /* EthTSynIcvGenerationTimeout - Master relevant */
        [!CALL "TimeoutFloatToMFC", "value"="../../EthTSynPortRole/EthTSynGlobalTimeRxIcvVerification/EthTSynIcvVerificationTimeout"!]U, /* EthTSynIcvVerificationTimeout */
        [!"node:ref(../../EthTSynPortRole/EthTSynGlobalTimeRxIcvVerification/EthTSynIcvVerificationJobRef)/CsmJobId"!]U, /* CsmJobId */
        [!ELSE!][!//
        0U, /* EthTSynIcvGenerationTimeout - not configured */
        0xFFFFFFFFU, /* EthTSynIcvVerificationTimeout - not configured */
        0xFFFFFFFFU, /* CsmJobId - not configured */
        [!ENDIF!][!//
#endif
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
        [!IF "node:exists(../../EthTSynPortRole/EthTSynBridgeTxPeriod)"!][!//
        [!CALL "TimeoutFloatToMFC", "value"="node:value(../../EthTSynPortRole/EthTSynBridgeTxPeriod)"!]U, /* EthTSynBridgeTxPeriod */
        [!ELSE!][!//
        0xFFFFFFFFU, /* EthTSynBridgeTxPeriod not used */
        [!ENDIF!][!//
#endif
        [!"num:i(../../EthTSynPortRole/EthTSynGlobalTimeSequenceCounterJumpWidth)"!]U, /* EthTSynGlobalTimeSequenceCounterJumpWidth */
#if(ETHTSYN_ICV_USED == STD_ON)
        0xFFFFU, /* EthTSynIcvTxLength - Slave not used*/
        0xFFFFU, /* EthTSynIcvTxOffset - Slave not used*/
        [!IF "node:exists(../../EthTSynPortRole/EthTSynGlobalTimeRxIcvVerification)"!][!//
        [!"num:i(../../EthTSynPortRole/EthTSynGlobalTimeRxIcvVerification/EthTSynIcvRxLength)"!]U, /* EthTSynIcvRxLength */
        [!"num:i($IcvRxStart)"!]U, /* EthTSynIcvOffset */
        [!VAR "IcvRxStart"="$IcvRxStart + num:i(../../EthTSynPortRole/EthTSynGlobalTimeRxIcvVerification/EthTSynIcvRxLength)"!][!//
        [!"num:i(../../EthTSynPortRole/EthTSynGlobalTimeRxIcvVerification/EthTSynIcvVerificationAttempts)"!]U, /* EthTSynIcvVerificationAttempts */
        [!IF "node:exists(../../EthTSynPortRole/EthTSynGlobalTimeRxIcvVerification/EthTSynIcvVerificationFvIdRef)"!][!//
        [!"node:ref(../../EthTSynPortRole/EthTSynGlobalTimeRxIcvVerification/EthTSynIcvVerificationFvIdRef)/StbMFreshnessValueId"!]U, /* FreshnessValueId */
        [!"node:ref(../../EthTSynPortRole/EthTSynGlobalTimeRxIcvVerification/EthTSynIcvVerificationFvIdRef)/StbMFreshnessValueLength"!]U, /* FreshnessValueLength */
        [!"node:ref(../../EthTSynPortRole/EthTSynGlobalTimeRxIcvVerification/EthTSynIcvVerificationFvIdRef)/StbMFreshnessValueTruncLength"!]U, /* FreshnessValueTruncLength */
        [!ELSE!][!//
        0xFFFFU, /* FreshnessValueId - not configured */
        0xFFU, /* FreshnessValueLength - not configured */
        0xFFU, /* FreshnessValueTruncLength - not configured */
        [!ENDIF!][!//
        [!ELSE!][!//
        0xFFFFU, /* EthTSynIcvRxLength - not configured */
        0xFFFFU, /* EthTSynIcvOffset - not configured */
        0xFFFFU, /* EthTSynIcvVerificationAttempts - not configured */
        0xFFFFU, /* FreshnessValueId - not configured */
        0xFFU, /* FreshnessValueLength - not configured */
        0xFFU, /* FreshnessValueTruncLength - not configured */
        [!ENDIF!][!//
#endif
        [!VAR "CountOFSTimebase"="0"!]
        [!VAR "StbMRef"="(node:current()/../../EthTSynSynchronizedTimeBaseRef)"!]
        {
        [!LOOP "as:modconf('EthTSyn')[1]/EthTSynGlobalTimeDomain/*"!]
        [!IF "node:exists(node:ref(EthTSynSynchronizedTimeBaseRef)/StbMOffsetTimeBase)"!]
          [!IF "node:ref(EthTSynSynchronizedTimeBaseRef)/StbMOffsetTimeBase = string($StbMRef)"!]
            [!VAR "OfsGlobalTimeDomainId"="num:i(./EthTSynGlobalTimeDomainId)"!]
            [!VAR "OffsetTimeBaseId"="num:i(node:ref(EthTSynSynchronizedTimeBaseRef)/StbMSynchronizedTimeBaseIdentifier)"!]
          {[!"num:i($OfsGlobalTimeDomainId)"!]U, [!"num:i($OffsetTimeBaseId)"!]U},/* Configured OfsEthTSynTimeDomain -> [!"num:i($OfsGlobalTimeDomainId)"!] with the corresponding StbM OffsetTimeBaseId -> [!"num:i($OffsetTimeBaseId)"!]  */
             [!VAR "CountOFSTimebase"="$CountOFSTimebase + 1"!]
          [!ENDIF!]
        [!ENDIF!]
        [!ENDLOOP!]
        [!FOR "i"="$CountOFSTimebase" TO "15"!]
          {255U, 255U}, /* OFS timebase not configured */
        [!ENDFOR!]
        },
        [!"num:i(../../EthTSynPortRole/EthTSynGlobalTimeSequenceCounterHysteresis)"!]U, /* EthTSynGlobalTimeSequenceCounterHysteresis */
        [!"node:ref(../../EthTSynGlobalTimeEthIfRef)/EthIfCtrlIdx"!]U, /* EthIfCtrlIdx */
        [!"num:i(./../../EthTSynGlobalTimeDomainId)"!]U, /* SyncGlobalTimeDomainId */
        [!"num:i($CountOFSTimebase)"!]U, /* Number of configured Ofs time bases */
        [!"num:i($OffsetSlaveArrIndex)"!]U, /* Index to the element in the SaveOfsData array. */
        [!VAR "OffsetSlaveArrIndex"="num:i($CountOFSTimebase) + num:i($OffsetSlaveArrIndex)"!]
        [!"node:ref(./../../EthTSynSynchronizedTimeBaseRef)/StbMSynchronizedTimeBaseIdentifier"!]U, /* TimeBaseId */
        [!IF "node:exists(../../EthTSynPortRole/EthTSynUseCalculatedPdelay)"!]
        [!"num:i(as:ref(as:ref(../../EthTSynPortRole/EthTSynUseCalculatedPdelay)/EthTSynSynchronizedTimeBaseRef)/StbMSynchronizedTimeBaseIdentifier)"!]U, /* TimeBaseId used to identify the TimeDomain from where the pdelay is used */
        [!ELSE!]
        0xFFU, /* Calculates own pdelay if configured (Slave) */
        [!ENDIF!]
        0U, /* SyncTxMsgLogInterval dummy value (Slave) */
        [!IF "node:exists(./EthTSynPdelayConfig)"!][!//
        [!CALL "LogMsgInterval", "value"="./EthTSynPdelayConfig/EthTSynGlobalTimeTxPdelayReqPeriod"!]U, /* PdelayTxMsgLogInterval (Slave) */
        [!ELSE!][!//
        0U,  /* PdelayTxMsgLogInterval (Slave) */
        [!ENDIF!][!//
        [!IF "node:exists(../../EthTSynPortRole/EthTSynPdelayFilter)"!][!//
        [!"num:i(../../EthTSynPortRole/EthTSynPdelayFilter)"!]U, /* EthTSynPdelayFilter */
        [!ELSE!][!//
        0U, /* EthTSynPdelayFilter: Dummy value */
        [!ENDIF!][!//
        [!IF "node:exists(../../EthTSynFramePrio)"!][!//
        [!"num:i(../../EthTSynFramePrio)"!]U, /* EthTSynFramePrio */
        [!ELSE!][!//
        0U, /* EthTSynFramePrio: Dummy value */
        [!ENDIF!][!//
        FALSE, /* TxCrcSecured: Dummy value */
        [!IF "node:exists(../../EthTSynPortRole/EthTSynRxCrcValidated)"!][!//
        [!"concat("ETHTSYN_",node:value(../../EthTSynPortRole/EthTSynRxCrcValidated))"!], /* RxCrcValidated */
        [!ELSE!][!//
        FALSE, /* RxCrcValidated: Dummy value */
        [!ENDIF!][!//
#if(ETHTSYN_ICV_USED == STD_ON)
        [!IF "node:exists(../../EthTSynPortRole/EthTSynRxIcvVerificationType)"!][!//
        [!"concat("ETHTSYN_",node:value(../../EthTSynPortRole/EthTSynRxIcvVerificationType))"!], /* RxIcvValidated */
        [!ELSE!][!//
        FALSE, /* RxIcvValidated: Dummy value */
        [!ENDIF!][!//
#endif
[!IF "node:exists(./../../EthTSynGlobalTimeFollowUpDataIDList)"!]
        {[!LOOP "util:distinct(node:order(./../../EthTSynGlobalTimeFollowUpDataIDList/EthTSynGlobalTimeFollowUpDataIDListElement/* ,'node:value(EthTSynGlobalTimeFollowUpDataIDListIndex)'))"!][!//
[!"node:value(./EthTSynGlobalTimeFollowUpDataIDListValue)"!]U, [!//
[!ENDLOOP!]}, /* EthTSyn_DataIdList */
[!ELSE!][!//
        {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U}, /* EthTSyn_DataIdList */
[!ENDIF!][!//
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_OFF)
        0U, /* PortStart - Bridge only */
        0U, /* PortCount - Bridge only */
        0U, /* PortManagement - Bridge only */
#else
        [!IF "node:refvalid(./EthTSynSwitchManagementEthSwitchPortRef)"!][!//
        [!"num:i($PortStart)"!]U, /* PortStart */
        [!VAR "PortStart"="$SwitchCount + $PortStart + num:i(count(./../../EthTSynPortConfig/*))"!][!//
        [!"num:i(count(./../../EthTSynPortConfig/*) + 1)"!]U, /* PortCount */
        [!"num:i($HostPort)"!]U, /* Host Port */
        [!IF "(./../../EthTSynPortRole = 'EthTSynGlobalTimeSlave')"!][!//
        [!VAR "SlavePort"="$HostPort + 1"!][!//
        [!ELSE!][!//
        [!VAR "SlavePort"="0"!][!//
        [!ENDIF!][!//
        [!VAR "HostPort"="$SwitchCount + $HostPort + num:i(count(./../../EthTSynPortConfig/*))"!][!//
        [!ELSE!][!//
        0U, /* PortStart */
        0U, /* PortCount */
        0U, /* Host Port */
        [!ENDIF!][!//
        [!"num:i($SlavePort)"!]U, /* PortSlave */
       [!IF "node:exists(../../EthTSynPortRole/EthTSynSimpleBridge)"!][!//
        [!IF "node:value(../../EthTSynPortRole/EthTSynSimpleBridge) = 'true'"!][!//
        TRUE, /* Acts as transparent clock */
        [!ELSE!][!//
        FALSE, /* Acts as boundary clock */
        [!ENDIF!][!//
        [!ELSE!][!//
        FALSE, /* Acts as boundary clock */
        [!ENDIF!][!//
        [!IF "node:exists(../../EthTSynPortRole/EthTSynSynchronizeSimpleBridge)"!][!//
        [!IF "node:value(../../EthTSynPortRole/EthTSynSynchronizeSimpleBridge) = 'true'"!][!//
        TRUE, /* The timebase will be synchronized */
        [!ELSE!][!//
        FALSE, /* The timebase will not be synchronized */
        [!ENDIF!][!//
        [!ELSE!][!//
        FALSE, /* Acts as boundary clock */
        [!ENDIF!][!//
       [!IF "node:exists(../../EthTSynPortRole/EthTSynSimpleBridgeValidateSync)"!][!//
        [!IF "node:value(../../EthTSynPortRole/EthTSynSimpleBridgeValidateSync) = 'true'"!][!//
        TRUE, /* The validation of the sync frame is requested for the transparent clock */
        [!ELSE!][!//
        FALSE, /* EthTSynSimpleBridgeValidateSync*/
        [!ENDIF!][!//
        [!ELSE!][!//
        FALSE, /* Acts as boundary clock */
        [!ENDIF!][!//
        [!IF "node:exists(../../EthTSynPortRole/EthTSynSimpleBridgeTSynSendSync)"!][!//
        [!IF "node:value(../../EthTSynPortRole/EthTSynSimpleBridgeTSynSendSync) = 'true'"!][!//
        TRUE, /* EthTSyn will forward the sync frames */
        [!ELSE!][!//
        FALSE, /* EthSwt will forward the sync frames */
        [!ENDIF!][!//
        [!ELSE!][!//
        FALSE, /* Acts as boundary clock */
        [!ENDIF!][!//
#endif
#if(ETHTSYN_ICV_USED == STD_ON)
        FALSE, /* EthTSynIcvGenerationBase - only relevant for master */
        [!IF "node:exists(../../EthTSynPortRole/EthTSynGlobalTimeRxIcvVerification)"!][!//
        [!IF "../../EthTSynPortRole/EthTSynGlobalTimeRxIcvVerification/EthTSynIcvVerificationBase = 'ICV_MAC'"!][!//
        TRUE, /* EthTSynIcvVerificationBase - Symmetric cryptography */
        [!ELSE!][!//
        FALSE, /* EthTSynIcvVerificationBase - Asymmetric cryptography */
        [!ENDIF!][!//
        [!ELSE!][!//
        FALSE, /* EthTSynIcvVerificationBase - Asymmetric cryptography */
        [!ENDIF!][!//
#endif
        [!IF "node:exists(node:ref(./../../EthTSynSynchronizedTimeBaseRef)/StbMLocalTimeClock)"!]
        [!IF "contains(node:ref(./../../EthTSynSynchronizedTimeBaseRef)/StbMLocalTimeClock/StbMLocalTimeHardware,'/EthTSyn/')"!]
        TRUE,/* VirtualLocalTimeSource of StbM == ETH freerunning counter */
        [!ELSE!][!//
        FALSE,/* VirtualLocalTimeSource of StbM == ETH freerunning counter */
        [!ENDIF!][!//
        [!ELSE!][!//
        FALSE,/* VirtualLocalTimeSource of StbM == ETH freerunning counter */
        [!ENDIF!][!//
        FALSE, /* TimeSyncMaster: Slave */
        [!IF "node:exists(./EthTSynPdelayConfig)"!][!//
        [!IF "./EthTSynPdelayConfig/EthTSynGlobalTimePdelayRespEnable = 'true'"!][!//
        TRUE, /* PdelayRespEnable (Slave)*/
        [!ELSE!][!//
        FALSE, /* PdelayRespEnable (Slave)*/
        [!ENDIF!][!//
        [!ELSE!][!//
        [!IF "node:exists(./EthTSynDelayE2EConfig)"!][!//
        [!IF "./EthTSynDelayE2EConfig/EthTSynGlobalTimeDelayE2ERespEnable = 'true'"!][!//
        TRUE, /* DelayRespEnable (Slave)*/
        [!ELSE!][!//
        FALSE, /* DelayRespEnable (Slave)*/
        [!ENDIF!][!//
        [!ELSE!][!//
        FALSE, /* PdelayRespEnable/DelayRespEnable (Slave)*/
        [!ENDIF!][!//
        [!ENDIF!][!//
        FALSE, /* ImmediateTimeSync: Dummy value */
        FALSE, /* TLVFollowUpTimeSubTLV: Dummy value */
        FALSE, /* TLVFollowUpStatusSubTLV: Dummy value */
        FALSE, /* TLVFollowUpUserDataSubTLV: Dummy value */
        FALSE, /* TLVFollowUpOFSSubTLV: Dummy value */
#if(ETHTSYN_ICV_USED == STD_ON)
        FALSE, /* TLVFollowUpICVSubTLV: Dummy value */
#endif
      [!IF "node:exists(../../EthTSynPortRole/EthTSynCrcFlagsRxValidated)"!][!//
        [!IF "(node:value(../../EthTSynPortRole/EthTSynCrcFlagsRxValidated/EthTSynCrcMessageLength)) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!], /* CrcMessageLength */
        [!IF "(node:value(../../EthTSynPortRole/EthTSynCrcFlagsRxValidated/EthTSynCrcDomainNumber)) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!], /* CrcDomainNumber */
        [!IF "(node:value(../../EthTSynPortRole/EthTSynCrcFlagsRxValidated/EthTSynCrcCorrectionField)) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!], /* CrcCorrectionField */
        [!IF "(node:value(../../EthTSynPortRole/EthTSynCrcFlagsRxValidated/EthTSynCrcSourcePortIdentity)) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!], /* CrcSourcePortIdentity */
        [!IF "(node:value(../../EthTSynPortRole/EthTSynCrcFlagsRxValidated/EthTSynCrcSequenceId)) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!], /* CrcSequenceId */
        [!IF "(node:value(../../EthTSynPortRole/EthTSynCrcFlagsRxValidated/EthTSynCrcPreciseOriginTimestamp)) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!], /* CrcPreciseOriginTimestamp */
      [!ELSE!][!//
        FALSE, /* CrcMessageLength */
        FALSE, /* CrcDomainNumber */
        FALSE, /* CrcCorrectionField */
        FALSE, /* CrcSourcePortIdentity */
        FALSE, /* CrcSequenceId */
        FALSE, /* CrcPreciseOriginTimestamp */
        [!ENDIF!][!//
#if(ETHTSYN_SWITCH_USED == STD_ON)
        FALSE,  /* SwtPortIdxInCorrField: Dummy value */
        [!IF "node:exists(../../EthTSynEnableDebouncePerPort)"!][!//
        [!IF "(node:value(../../EthTSynEnableDebouncePerPort)) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!], /* EnableDebouncePerPort */
        [!ELSE!][!//
        FALSE, /* EnableDebouncePerPort disabled */
        [!ENDIF!][!//
#endif /* ETHTSYN_SWITCH_USED == STD_ON */
#if(ETHTSYN_TIME_RECORDING == STD_ON)
       [!IF "node:refvalid(../../EthTSynSwitchManagementEthSwitchPortHostRef)"!][!//
        FALSE, /* If switch is used the validation shall be done per port (Slave) */
       [!ELSE!][!//
         [!IF "node:value(./EthTSynEnableTimeValidation) = 'true'"!]
          TRUE, /* Timevalidation enabled (Slave) */
         [!ELSE!][!//
          FALSE, /* Timevalidation disabled (Slave) */
         [!ENDIF!][!//
       [!ENDIF!][!//
#endif
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
      [!IF "../../EthTSynEnablePTPCalculation = 'true'"!][!//
      TRUE, /* PTP mechanism is used (Slave)*/
      [!ELSE!][!//
      FALSE, /* gPTP mechanism is used (Slave)*/
      [!ENDIF!][!//
      [!IF "node:exists(./EthTSynDelayE2EConfig/EthTSynDelayReqAfterFup) and (./EthTSynDelayE2EConfig/EthTSynDelayReqAfterFup = 'true')"!][!//
      TRUE, /* Send delay_req immediately after a valid Sync\Fup pair is received(Slave)*/
      [!ELSE!][!//
      FALSE, /* Send delay_req after DelayReqTxPeriod expires. */
      [!ENDIF!]
#endif
#if(ETHTSYN_DEM_REPORTING == STD_ON)
      [!IF "node:exists(../../EthTSynPortRole/EthTSynDemEventParameterRefs/ETHTSYN_E_SYNC_FAILED)"!]
        [!"node:value(as:ref(../../EthTSynPortRole/EthTSynDemEventParameterRefs/ETHTSYN_E_SYNC_FAILED)/DemEventId)"!]U, /* DEM Event ETHTSYN_E_SYNC_FAILED */
      [!ELSE!]
        0U, /* Disabled DEM Event ETHTSYN_E_SYNC_FAILED */
      [!ENDIF!]
      [!IF "node:exists(../../EthTSynPortRole/EthTSynDemEventParameterRefs/ETHTSYN_E_PDELAY_FAILED)"!]
        [!"node:value(as:ref(../../EthTSynPortRole/EthTSynDemEventParameterRefs/ETHTSYN_E_PDELAY_FAILED)/DemEventId)"!]U, /* DEM Event ETHTSYN_E_PDELAY_FAILED */
      [!ELSE!]
        0U, /* Disabled DEM Event ETHTSYN_E_PDELAY_FAILED */
      [!ENDIF!]
        0U  /* EventIdUnexpectedSync - dummy value (Slave) */
#endif
      },
      [!BREAK!][!//
      [!ENDIF!][!//
    [!ENDLOOP!]
    [!ENDIF!][!//
  [!ENDLOOP!]
  [!LOOP "as:modconf('EthTSyn')[1]/EthTSynGlobalTimeDomain/*"!][!//
    [!IF "node:exists(./EthTSynPortConfig)"!][!//
    [!LOOP "./EthTSynPortConfig/*"!][!//
      [!IF "node:containsValue(../../EthTSynPortRole, 'EthTSynGlobalTimeMaster')"!][!//
      {
        [!CALL "DebounceFloatToMFC", "value"="../../EthTSynGlobalTimeDebounceTime"!]U, /* EthTSynGlobalTimeDebounceTime */
        [!IF "(node:value(../../EthTSynPortRole/EthTSynImmediateTimeSync)) = 'true'"!]
        [!CALL "TimeoutFloatToMFC", "value"="../../EthTSynPortRole/EthTSynCyclicMsgResumeTime"!]U, /* EthTSynCyclicMsgResumeTime (Master) */
        [!ELSE!][!//
        0U, /* EthTSynCyclicMsgResumeTime: Dummy value */
        [!ENDIF!][!//
        [!CALL "TimeoutFloatToMFC", "value"="../../EthTSynPortRole/EthTSynGlobalTimeTxPeriod"!]U, /* SyncTxInterval (Master) */
        [!IF "node:exists(./EthTSynPdelayConfig)"!][!//
        [!CALL "TimeoutFloatToMFC", "value"="./EthTSynPdelayConfig/EthTSynGlobalTimeTxPdelayReqPeriod"!]U, /* PdelayReqTxInterval (Master) */
        [!IF "node:exists(./EthTSynPdelayConfig/EthTSynInitialGlobalTimeTxPdelayReqPeriod)"!][!//
        [!CALL "TimeoutFloatToMFC", "value"="./EthTSynPdelayConfig/EthTSynInitialGlobalTimeTxPdelayReqPeriod"!]U, /* InitialPdelayReqTxInterval (Master) */
        [!ELSE!][!//
        0U,  /* InitialPdelayReqTxInterval (Master) */
        [!ENDIF!][!//
        0U, /* PdelayRespAndRespFollowUpTimeout (Master) */
        [!CALL "PdelayNanoseconds", "value"="./EthTSynPdelayConfig/EthTSynGlobalTimePropagationDelay"!]U, /* DefaultPdelayNs (Master) */
        [!ELSE!][!//
        [!IF "node:exists(./EthTSynDelayE2EConfig)"!][!//
        [!CALL "TimeoutFloatToMFC", "value"="./EthTSynDelayE2EConfig/EthTSynGlobalTimeTxDelayE2EReqPeriod"!]U, /* DelayReqTxInterval (Master) */
        0U, /* InitialPdelayReqTxInterval (Master) not used */
        0U, /* PdelayRespAndRespFollowUpTimeout (Master) */
        [!CALL "PdelayNanoseconds", "value"="./EthTSynDelayE2EConfig/EthTSynGlobalTimeDelayE2E"!]U, /* DefaultDelayNs (Master) */
        [!ELSE!][!//
        0xFFFFFFFFU, /* PdelayReqTxInterval (Master) */
        0U, /* InitialPdelayReqTxInterval (Master) */
        0U, /* PdelayRespAndRespFollowUpTimeout (Master) */
        0U, /* DefaultPdelayNs (Master) */
        [!ENDIF!][!//
        [!ENDIF!][!//
        0x0U,  /* EthTSynGlobalTimeFollowUpTimeout (Master) */
        0U,  /* EthTSynGlobalTimeRxDebounceTime (Master) */
        #if (ETHTSYN_PROD_ERR_HANDLING_SYNC_FAILED != TS_PROD_ERR_DISABLE)
        0xFFFFFFFFU,
        #endif
        #if (ETHTSYN_PROD_ERR_HANDLING_PDELAY_FAILED != TS_PROD_ERR_DISABLE)
        0xFFFFFFFFU,
        #endif
        0xFFFFFFFFU, /* EthTSynPdelayLatencyThreshold - Master not used*/
#if(ETHTSYN_ICV_USED == STD_ON)
        [!IF "node:exists(../../EthTSynPortRole/EthTSynGlobalTimeTxIcvGeneration)"!][!//
        [!CALL "TimeoutFloatToMFC", "value"="../../EthTSynPortRole/EthTSynGlobalTimeTxIcvGeneration/EthTSynIcvGenerationTimeout"!]U,  /* EthTSynIcvGenerationTimeout */
        0xFFFFFFFFU, /* EthTSynIcvVerificationTimeout used only for slave */
        [!"node:ref(../../EthTSynPortRole/EthTSynGlobalTimeTxIcvGeneration/EthTSynIcvGenerationJobRef)/CsmJobId"!]U, /* CsmJobId */
        [!ELSE!][!//
        0U, /* EthTSynIcvGenerationTimeout - not configured */
        0xFFFFFFFFU, /* EthTSynIcvVerificationTimeout used only for slave */
        0xFFFFFFFFU, /* CsmJobId - not configured */
        [!ENDIF!][!//

#endif
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
        0xFFFFFFFFU, /* EthTSynBridgeTxPeriod - Master not used*/
#endif
        0xFFFFU, /* EthTSynGlobalTimeSequenceCounterJumpWidth - Master not used*/
#if(ETHTSYN_ICV_USED == STD_ON)
        [!IF "node:exists(../../EthTSynPortRole/EthTSynGlobalTimeTxIcvGeneration)"!][!//
        [!"num:i(../../EthTSynPortRole/EthTSynGlobalTimeTxIcvGeneration/EthTSynIcvTxLength)"!]U, /* EthTSynIcvTxLength */
        [!"num:i($IcvTxStart)"!]U, /* EthTSynIcvOffset */
        [!VAR "IcvTxStart"="$IcvTxStart + num:i(../../EthTSynPortRole/EthTSynGlobalTimeTxIcvGeneration/EthTSynIcvTxLength)"!][!//
        0xFFFFU, /* EthTSynIcvRxLength - Master not used*/
        0xFFFFU, /* EthTSynIcvRxOffset - Master not used*/
        0xFFFFU, /* EthTSynIcvVerificationAttempts - Master not used*/
        [!IF "node:exists(../../EthTSynPortRole/EthTSynGlobalTimeTxIcvGeneration/EthTSynIcvGenerationFvIdRef)"!][!//
        [!"node:ref(../../EthTSynPortRole/EthTSynGlobalTimeTxIcvGeneration/EthTSynIcvGenerationFvIdRef)/StbMFreshnessValueId"!]U, /* FreshnessValueId */
        [!"node:ref(../../EthTSynPortRole/EthTSynGlobalTimeTxIcvGeneration/EthTSynIcvGenerationFvIdRef)/StbMFreshnessValueLength"!]U, /* FreshnessValueLength */
        [!"node:ref(../../EthTSynPortRole/EthTSynGlobalTimeTxIcvGeneration/EthTSynIcvGenerationFvIdRef)/StbMFreshnessValueTruncLength"!]U, /* FreshnessValueTruncLength */
        [!ELSE!][!//
        0xFFFFU, /* FreshnessValueId - not configured */
        0xFFU, /* FreshnessValueLength - not configured */
        0xFFU, /* FreshnessValueTruncLength - not configured */
        [!ENDIF!][!//
        [!ELSE!][!//
        0xFFFFU, /* EthTSynIcvTxLength - not configured */
        0xFFFFU, /* EthTSynIcvOffset - not configured */
        0xFFFFU, /* EthTSynIcvRxLength - not configured */
        0xFFFFU, /* EthTSynIcvRxOffset - not configured */
        0xFFFFU, /* EthTSynIcvVerificationAttempts - not configured */
        0xFFFFU, /* FreshnessValueId - not configured */
        0xFFU, /* FreshnessValueLength - not configured */
        0xFFU, /* FreshnessValueTruncLength - not configured */
        [!ENDIF!][!//
#endif
        [!VAR "CountOFSTimebase"="0"!]
        [!VAR "StbMRef"="(node:current()/../../EthTSynSynchronizedTimeBaseRef)"!]
        {
        [!LOOP "as:modconf('EthTSyn')[1]/EthTSynGlobalTimeDomain/*"!]
        [!IF "node:exists(node:ref(EthTSynSynchronizedTimeBaseRef)/StbMOffsetTimeBase)"!]
          [!IF "node:ref(EthTSynSynchronizedTimeBaseRef)/StbMOffsetTimeBase = string($StbMRef)"!]
            [!VAR "OfsGlobalTimeDomainId"="num:i(./EthTSynGlobalTimeDomainId)"!]
            [!VAR "OffsetTimeBaseId"="num:i(node:ref(EthTSynSynchronizedTimeBaseRef)/StbMSynchronizedTimeBaseIdentifier)"!]
          {[!"num:i($OfsGlobalTimeDomainId)"!]U, [!"num:i($OffsetTimeBaseId)"!]U},/* Configured OfsEthTSynTimeDomain -> [!"num:i($OfsGlobalTimeDomainId)"!] with the corresponding StbM OffsetTimeBaseId -> [!"num:i($OffsetTimeBaseId)"!]  */
             [!VAR "CountOFSTimebase"="$CountOFSTimebase + 1"!]
          [!ENDIF!]
        [!ENDIF!]
        [!ENDLOOP!]
        [!FOR "i"="$CountOFSTimebase" TO "15"!]
          {255U, 255U}, /* OFS timebase not configured */
        [!ENDFOR!]
        },
        0xFFU, /* EthTSynGlobalTimeSequenceCounterHysteresis - Master not used*/
        [!"node:ref(../../EthTSynGlobalTimeEthIfRef)/EthIfCtrlIdx"!]U, /* EthIfCtrlIdx */
        [!"num:i(./../../EthTSynGlobalTimeDomainId)"!]U, /* SyncGlobalTimeDomainId */
        [!"num:i($CountOFSTimebase)"!]U, /* Number of configured Ofs time bases */
        0U, /* Not used (Master) */
        [!"node:ref(./../../EthTSynSynchronizedTimeBaseRef)/StbMSynchronizedTimeBaseIdentifier"!]U, /* TimeBaseId */
        0xFFU, /* Not used (Master) */
        [!CALL "LogMsgInterval", "value"="../../EthTSynPortRole/EthTSynGlobalTimeTxPeriod"!]U, /* SyncTxMsgLogInterval (Master) */
        [!IF "node:exists(./EthTSynPdelayConfig)"!][!//
        [!CALL "LogMsgInterval", "value"="./EthTSynPdelayConfig/EthTSynGlobalTimeTxPdelayReqPeriod"!]U, /* PdelayTxMsgLogInterval (Master) */
        [!ELSE!][!//
        0U, /* PdelayTxMsgLogInterval (Master) */
        [!ENDIF!][!//
        0U, /* EthTSynPdelayFilter: Dummy value */
        [!IF "node:exists(../../EthTSynFramePrio)"!][!//
        [!"num:i(../../EthTSynFramePrio)"!]U, /* EthTSynFramePrio */
        [!ELSE!][!//
        0U, /* EthTSynFramePrio: Dummy value */
        [!ENDIF!][!//
        [!"concat("ETHTSYN_",node:value(../../EthTSynPortRole/EthTSynGlobalTimeTxCrcSecured))"!], /* TxCrcSecured */
        FALSE, /* RxCrcValidated: Dummy value */
#if(ETHTSYN_ICV_USED == STD_ON)
        FALSE, /* RxIcvValidated: Dummy value */
#endif
[!IF "node:exists(./../../EthTSynGlobalTimeFollowUpDataIDList)"!]
        {[!LOOP "util:distinct(node:order(./../../EthTSynGlobalTimeFollowUpDataIDList/EthTSynGlobalTimeFollowUpDataIDListElement/* ,'node:value(EthTSynGlobalTimeFollowUpDataIDListIndex)'))"!][!//
[!"node:value(./EthTSynGlobalTimeFollowUpDataIDListValue)"!]U, [!//
[!ENDLOOP!]}, /* EthTSyn_DataIdList */
[!ELSE!][!//
        {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U}, /* EthTSyn_DataIdList */
[!ENDIF!]
        [!IF "node:refvalid(./EthTSynSwitchManagementEthSwitchPortRef)"!][!//
        [!"num:i($PortStart)"!]U, /* PortStart */
          [!VAR "PortStart"="$SwitchCount + $PortStart + num:i(count(./../../EthTSynPortConfig/*))"!][!//
        [!"num:i(count(./../../EthTSynPortConfig/*) + 1)"!]U, /* PortCount */
        [!"num:i($HostPort)"!]U, /* Host Port */
        [!VAR "HostPort"="$SwitchCount + $HostPort + num:i(count(./../../EthTSynPortConfig/*))"!][!//
        [!ELSE!][!//
        0U, /* PortStart */
        0U, /* PortCount */
        0U, /* Host Port */
#if(ETHTSYN_BRIDGE_WITH_GTM_NOT_MGM_CPU == STD_ON)
        0U, /* PortSlave */
        FALSE, /* SimpleBridge (Master) */
        FALSE, /* SynchronizeSimpleBridge (Master) */
        FALSE, /* EthTSynSimpleBridgeValidateSync (Master) */
        FALSE, /* EthTSynSimpleBridgeTSynSendSync (Master) */
#endif
        [!ENDIF!][!//
#if(ETHTSYN_ICV_USED == STD_ON)
        [!IF "node:exists(../../EthTSynPortRole/EthTSynGlobalTimeTxIcvGeneration)"!][!//
        [!IF "../../EthTSynPortRole/EthTSynGlobalTimeTxIcvGeneration/EthTSynIcvGenerationBase = 'ICV_MAC'"!][!//
        TRUE, /* EthTSynIcvGenerationBase - Symmetric cryptography */
        [!ELSE!][!//
        FALSE, /* EthTSynIcvGenerationBase - Asymmetric cryptography */
        [!ENDIF!][!//
        [!ELSE!][!//
        FALSE, /* EthTSynIcvGenerationBase - Asymmetric cryptography */
        [!ENDIF!][!//
        FALSE, /* EthTSynIcvVerificationBase - only relevant for slave */
#endif
        [!IF "node:exists(node:ref(./../../EthTSynSynchronizedTimeBaseRef)/StbMLocalTimeClock)"!]
        [!IF "contains(node:ref(./../../EthTSynSynchronizedTimeBaseRef)/StbMLocalTimeClock/StbMLocalTimeHardware,'/EthTSyn/')"!]
        TRUE,/* VirtualLocalTimeSource of StbM == ETH freerunning counter */
        [!ELSE!][!//
        FALSE,/* VirtualLocalTimeSource of StbM == ETH freerunning counter */
        [!ENDIF!][!//
        [!ELSE!][!//
        FALSE,/* VirtualLocalTimeSource of StbM == ETH freerunning counter */
        [!ENDIF!][!//
        TRUE, /* TimeSyncMaster: Master */
        [!IF "node:exists(./EthTSynPdelayConfig)"!][!//
        [!IF "./EthTSynPdelayConfig/EthTSynGlobalTimePdelayRespEnable = 'true'"!][!//
        TRUE, /* PdelayRespEnable (Master)*/
        [!ELSE!][!//
        FALSE, /* PdelayRespEnable (Master)*/
        [!ENDIF!][!//
        [!ELSE!][!//
        [!IF "node:exists(./EthTSynDelayE2EConfig)"!][!//
        [!IF "./EthTSynDelayE2EConfig/EthTSynGlobalTimeDelayE2ERespEnable = 'true'"!][!//
        TRUE, /* DelayRespEnable (Master)*/
        [!ELSE!][!//
        FALSE, /* DelayRespEnable (Master)*/
        [!ENDIF!][!//
        [!ELSE!][!//
        FALSE, /* PdelayRespEnable/DelayRespEnable (Master)*/
        [!ENDIF!][!//
        [!ENDIF!][!//
        [!IF "../../EthTSynPortRole/EthTSynImmediateTimeSync = 'true'"!][!//
        TRUE, /* EthTSynImmediateTimeSync (Master)*/
        [!ELSE!][!//
        FALSE, /* EthTSynImmediateTimeSync (Master)*/
        [!ENDIF!][!//
        [!IF "../../EthTSynPortRole/EthTSynTLVFollowUpTimeSubTLV = 'true'"!][!//
        TRUE, /* TLVFollowUpTimeSubTLV (Master)*/
        [!ELSE!][!//
        FALSE, /* TLVFollowUpTimeSubTLV (Master)*/
        [!ENDIF!][!//
        [!IF "../../EthTSynPortRole/EthTSynTLVFollowUpStatusSubTLV = 'true'"!][!//
        TRUE, /* TLVFollowUpStatusSubTLV (Master)*/
        [!ELSE!][!//
        FALSE, /* TLVFollowUpStatusSubTLV (Master)*/
        [!ENDIF!][!//
        [!IF "../../EthTSynPortRole/EthTSynTLVFollowUpUserDataSubTLV = 'true'"!][!//
        TRUE, /* TLVFollowUpUserDataSubTLV (Master)*/
        [!ELSE!][!//
        FALSE, /* TLVFollowUpUserDataSubTLV (Master)*/
        [!ENDIF!][!//
        [!IF "../../EthTSynPortRole/EthTSynTLVFollowUpOFSSubTLV = 'true'"!][!//
        TRUE, /* TLVFollowUpOFSSubTLV (Master)*/
        [!ELSE!][!//
        FALSE, /* TLVFollowUpOFSSubTLV (Master)*/
        [!ENDIF!][!//
#if(ETHTSYN_ICV_USED == STD_ON)
        [!IF "../../EthTSynPortRole/EthTSynTLVFollowUpICVSubTLV = 'true'"!][!//
        TRUE, /* TLVFollowUpICVSubTLV (Master)*/
        [!ELSE!][!//
        FALSE, /* TLVFollowUpICVSubTLV (Master)*/
        [!ENDIF!][!//
#endif
      [!IF "node:exists(../../EthTSynPortRole/EthTSynCrcTimeFlagsTxSecured)"!][!//
        [!IF "(node:value(../../EthTSynPortRole/EthTSynCrcTimeFlagsTxSecured/EthTSynCrcMessageLength)) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!], /* CrcMessageLength */
        [!IF "(node:value(../../EthTSynPortRole/EthTSynCrcTimeFlagsTxSecured/EthTSynCrcDomainNumber)) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!], /* CrcDomainNumber */
        [!IF "(node:value(../../EthTSynPortRole/EthTSynCrcTimeFlagsTxSecured/EthTSynCrcCorrectionField)) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!], /* CrcCorrectionField */
        [!IF "(node:value(../../EthTSynPortRole/EthTSynCrcTimeFlagsTxSecured/EthTSynCrcSourcePortIdentity)) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!], /* CrcSourcePortIdentity */
        [!IF "(node:value(../../EthTSynPortRole/EthTSynCrcTimeFlagsTxSecured/EthTSynCrcSequenceId)) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!], /* CrcSequenceId */
        [!IF "(node:value(../../EthTSynPortRole/EthTSynCrcTimeFlagsTxSecured/EthTSynCrcPreciseOriginTimestamp)) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!], /* CrcPreciseOriginTimestamp */
      [!ELSE!][!//
        FALSE, /* CrcMessageLength */
        FALSE, /* CrcDomainNumber */
        FALSE, /* CrcCorrectionField */
        FALSE, /* CrcSourcePortIdentity */
        FALSE, /* CrcSequenceId */
        FALSE,  /* CrcPreciseOriginTimestamp */
      [!ENDIF!][!//
#if(ETHTSYN_SWITCH_USED == STD_ON)
      [!IF "../../EthTSynPortRole/EthTSynSwtPortIdxInCorrField = 'true'"!][!//
        TRUE, /* EthTSynSwtPortIdxInCorrField (Master)*/
      [!ELSE!][!//
        FALSE, /* EthTSynSwtPortIdxInCorrField (Master)*/
      [!ENDIF!][!//
      [!IF "node:exists(../../EthTSynEnableDebouncePerPort)"!][!//
      [!IF "(node:value(../../EthTSynEnableDebouncePerPort)) = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!], /* EnableDebouncePerPort */
      [!ELSE!][!//
      FALSE, /* EnableDebouncePerPort disabled */
      [!ENDIF!][!//
#endif /* ETHTSYN_SWITCH_USED == STD_ON */
#if(ETHTSYN_TIME_RECORDING == STD_ON)
       [!IF "node:refvalid(../../EthTSynSwitchManagementEthSwitchPortHostRef)"!][!//
        FALSE, /* If switch is used the validation shall be done per port (Master) */
       [!ELSE!][!//
       [!IF "node:value(./EthTSynEnableTimeValidation) = 'true'"!]
        TRUE, /* Timevalidation enabled (Master) */
       [!ELSE!][!//
        FALSE, /* Timevalidation disabled (Master) */
       [!ENDIF!][!//
       [!ENDIF!][!//
#endif /* ETHTSYN_TIME_RECORDING == STD_ON */
#if(ETHTSYN_IEEE1588_CONFIGURED == STD_ON)
        [!IF "../../EthTSynEnablePTPCalculation = 'true'"!][!//
        TRUE, /* PTP mechanism is used (Master)*/
        [!ELSE!][!//
        FALSE, /* gPTP mechanism is used (Master)*/
        [!ENDIF!][!//
        FALSE, /* EthTSynDelayReqAfterFup is not relevant for Master */
#endif
#if(ETHTSYN_DEM_REPORTING == STD_ON)
        0U, /* dummy value for EthTSynGlobalTimeMaster */
        0U, /* dummy value DEM Event ETHTSYN_E_PDELAY_FAILED */
      [!IF "node:exists(../../EthTSynPortRole/EthTSynDemEventParameterRefs/ETHTSYN_E_UNEXPECTED_SYNC)"!]
        [!"node:value(as:ref(../../EthTSynPortRole/EthTSynDemEventParameterRefs/ETHTSYN_E_UNEXPECTED_SYNC)/DemEventId)"!]U, /* DEM Event ETHTSYN_E_UNEXPECTED_SYNC */
      [!ELSE!]
        0U, /* Disabled DEM Event ETHTSYN_E_UNEXPECTED_SYNC */
      [!ENDIF!]
#endif
      },
      [!BREAK!][!//
      [!ENDIF!][!//
    [!ENDLOOP!]
    [!ENDIF!][!//
  [!ENDLOOP!]
  },
#if((ETHTSYN_SWITCH_USED == STD_ON))
  [!"concat($initPredefinedCfgName,'SwitchConfig_0')"!],
  [!"$SwtPortsConfigured"!]
#endif
};

#if(ETHTSYN_SWITCH_USED == STD_ON)
CONST(EthTSyn_SwitchConfigType, ETHTSYN_APPL_CONST) [!"concat($initPredefinedCfgName,'SwitchConfig_0')"!][[!"$SwtPortsConfigured"!]] =
{
[!LOOP "as:modconf('EthTSyn')[1]/EthTSynGlobalTimeDomain/*"!][!//
    [!IF "node:refvalid(./EthTSynSwitchManagementEthSwitchPortHostRef)"!][!//
  {
    [!IF "node:exists(./EthTSynSwitchPortHostDebounceTime)"!][!//
    [!CALL "DebounceFloatToMFC", "value"="./EthTSynSwitchPortHostDebounceTime"!]U, /* EthTSynSwitchPortHostDebounceTime */
    [!ELSE!][!//
    0xFFFFFFFFU,  /* EthTSynSwitchPortHostDebounceTime (Debouncing per port feature disabled) */
    [!ENDIF!][!//
    [!"node:ref(./EthTSynSwitchManagementEthSwitchPortHostRef)/../../EthSwtIdx"!]U, /* EthSwtIdx Host */
    [!"node:ref(./EthTSynSwitchManagementEthSwitchPortHostRef)/EthSwtPortIdx"!]U, /* EthSwtIdx Host */
#if(ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_OFF)
    0xFFFFU, /* PortId is not used for the host port */
#endif
    FALSE, /* EthTSynGlobalTimePdelayRespEnable (Host - Not needed)*/
#if(ETHTSYN_TIME_RECORDING == STD_ON)
    FALSE, /* EthTSynEnableTimeValidation (Host - Not needed)*/
#endif /* ETHTSYN_TIME_RECORDING == STD_ON */
  },
    [!ENDIF!][!//
  [!LOOP "./EthTSynPortConfig/*"!][!//
      [!IF "node:refvalid(./EthTSynSwitchManagementEthSwitchPortRef)"!][!//
  {
    [!IF "node:exists(./EthTSynSwitchPortDebounceTime)"!][!//
    [!CALL "DebounceFloatToMFC", "value"="./EthTSynSwitchPortDebounceTime"!]U, /* EthTSynSwitchPortDebounceTime */
    [!ELSE!][!//
    0xFFFFFFFFU,  /* EthTSynSwitchPortDebounceTime (Debouncing per port feature disabled) */
    [!ENDIF!][!//
    [!"node:ref(./EthTSynSwitchManagementEthSwitchPortRef)/../../EthSwtIdx"!]U, /* EthSwtIdx */
    [!"node:ref(./EthTSynSwitchManagementEthSwitchPortRef)/EthSwtPortIdx"!]U, /* EthSwtPortIdx */
#if(ETHTSYN_SEND_SYNC_ONLY_ON_HOST_PORT == STD_OFF)
    [!IF "node:exists(./EthTSynPortNumber)"!][!//
    [!"node:value(./EthTSynPortNumber)"!]U, /* Configured PortId  */
    [!ELSE!][!//
    0xFFFFU, /* PortId not used */
    [!ENDIF!][!//
#endif
    [!IF "./EthTSynPdelayConfig/EthTSynGlobalTimePdelayRespEnable = 'true'"!][!//
      TRUE, /* EthTSynGlobalTimePdelayRespEnable (Master)*/
    [!ELSE!][!//
      FALSE, /* EthTSynGlobalTimePdelayRespEnable (Master)*/
    [!ENDIF!][!//
#if(ETHTSYN_TIME_RECORDING == STD_ON)
    [!IF "./EthTSynEnableTimeValidation = 'true'"!][!//
      TRUE, /* EthTSynEnableTimeValidation */
    [!ELSE!][!//
      FALSE, /* EthTSynEnableTimeValidation */
    [!ENDIF!][!//
#endif /* ETHTSYN_TIME_RECORDING == STD_ON */
  },
    [!ENDIF!][!//
  [!ENDLOOP!][!//
[!ENDLOOP!][!//
};
#endif

#define ETHTSYN_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include <EthTSyn_MemMap.h>


/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
[!ENDCODE!]
