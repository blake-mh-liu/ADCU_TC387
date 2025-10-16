/**
 * \file
 *
 * \brief AUTOSAR CanTSyn
 *
 * This file contains the implementation of the AUTOSAR
 * module CanTSyn.
 *
 * \version 5.0.5
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

#include <CanTSyn_Cfg.h> /* Generated pre-compile configuration. */
[!INCLUDE "../include/CanTSyn_PrecompileMacros.m"!][!//
[!INCLUDE "../include/CanTSyn_Checks.m"!][!//

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/* !LINKSTO CanTSyn.dsn.PrecompileTimeConfig,1 */

[!CALL "isIcvGenerationSupported"!]
[!CALL "isIcvVerificationSupported"!]
[!CALL "isFvUsedInIcvGeneration"!]
[!CALL "isFvUsedInIcvVerification"!]
[!IF "$CanTSyn_SyncDomains != 0"!]
[!CALL "GetCanTSynCRCSyncDomains"!]

[!FOR "i" = "0" TO "$CanTSyn_SyncDomains - 1"!][!//
[!VAR "currentTimeDomain" = "text:split($sortedDomainsList, ',')[position()-1 = $i]"!]
[!SELECT "node:ref($currentTimeDomain)"!][!//

  [!IF "node:exists(./CanTSynGlobalTimeSyncDataIDList/CanTSynGlobalTimeSyncDataIDListElement)"!]
#define CANTSYN_START_SEC_CONST_8
#include <CanTSyn_MemMap.h>

static CONST(CanTSyn_DataIDListType, CANTSYN_APPL_CONST) CanTSyn_DataIdListSyncValues_[!"as:name(.)"!][16] =
{
    [!FOR "j" = "0" TO "15"!]
      [!INDENT "1"!]
  [!"num:i(node:value(concat(node:paths(util:distinct(node:order(./CanTSynGlobalTimeSyncDataIDList/CanTSynGlobalTimeSyncDataIDListElement/*, 'CanTSynGlobalTimeSyncDataIDListIndex')))[position()-1 = $j],'/CanTSynGlobalTimeSyncDataIDListValue')))"!]U,
      [!ENDINDENT!]
    [!ENDFOR!]
};

#define CANTSYN_STOP_SEC_CONST_8
#include <CanTSyn_MemMap.h>
  [!ENDIF!]

  [!IF "node:exists(./CanTSynGlobalTimeFupDataIDList/CanTSynGlobalTimeFupDataIDListElement)"!]
#define CANTSYN_START_SEC_CONST_8
#include <CanTSyn_MemMap.h>

static CONST(CanTSyn_DataIDListType, CANTSYN_APPL_CONST) CanTSyn_DataIdListFupValues_[!"as:name(.)"!][16] =
{
    [!FOR "j" = "0" TO "15"!]
      [!INDENT "1"!]
  [!"num:i(node:value(concat(node:paths(util:distinct(node:order(./CanTSynGlobalTimeFupDataIDList/CanTSynGlobalTimeFupDataIDListElement/*, 'CanTSynGlobalTimeFupDataIDListIndex')))[position()-1 = $j],'/CanTSynGlobalTimeFupDataIDListValue')))"!]U,
      [!ENDINDENT!]
    [!ENDFOR!]
};

#define CANTSYN_STOP_SEC_CONST_8
#include <CanTSyn_MemMap.h>
  [!ENDIF!]

[!ENDSELECT!]
[!ENDFOR!]
[!ENDIF!]


[!IF "$CanTSyn_OffsetDomains != 0"!]
[!CALL "GetCanTSynCRCOffsetDomains"!]
[!FOR "i" = "0" TO "$CanTSyn_OffsetDomains - 1"!][!//
[!VAR "currentTimeDomain" = "text:split($sortedDomainsList, ',')[position()-1 = $i]"!]
[!SELECT "node:ref($currentTimeDomain)"!][!//

  [!IF "node:exists(./CanTSynGlobalTimeOfsDataIDList/CanTSynGlobalTimeOfsDataIDListElement)"!]
#define CANTSYN_START_SEC_CONST_8
#include <CanTSyn_MemMap.h>

static CONST(CanTSyn_DataIDListType, CANTSYN_APPL_CONST) CanTSyn_DataIdListOfsValues_[!"as:name(.)"!][16] =
{
    [!FOR "j" = "0" TO "15"!]
      [!INDENT "1"!]
  [!"num:i(node:value(concat(node:paths(util:distinct(node:order(./CanTSynGlobalTimeOfsDataIDList/CanTSynGlobalTimeOfsDataIDListElement/*, 'CanTSynGlobalTimeOfsDataIDListIndex')))[position()-1 = $j],'/CanTSynGlobalTimeOfsDataIDListValue')))"!]U,
      [!ENDINDENT!]
    [!ENDFOR!]
};
#define CANTSYN_STOP_SEC_CONST_8
#include <CanTSyn_MemMap.h>
  [!ENDIF!]

  [!IF "node:exists(./CanTSynGlobalTimeOfnsDataIDList/CanTSynGlobalTimeOfnsDataIDListElement)"!]
    [!IF "node:value(./CanTSynUseExtendedMsgFormat) = 'false'"!]
#define CANTSYN_START_SEC_CONST_8
#include <CanTSyn_MemMap.h>

static CONST(CanTSyn_DataIDListType, CANTSYN_APPL_CONST) CanTSyn_DataIdListOfnsValues_[!"as:name(.)"!][16] =
{
    [!FOR "j" = "0" TO "15"!]
      [!INDENT "1"!]
  [!"num:i(node:value(concat(node:paths(util:distinct(node:order(./CanTSynGlobalTimeOfnsDataIDList/CanTSynGlobalTimeOfnsDataIDListElement/*, 'CanTSynGlobalTimeOfnsDataIDListIndex')))[position()-1 = $j],'/CanTSynGlobalTimeOfnsDataIDListValue')))"!]U,
      [!ENDINDENT!]
    [!ENDFOR!]
};

#define CANTSYN_STOP_SEC_CONST_8
#include <CanTSyn_MemMap.h>
    [!ENDIF!]
  [!ENDIF!]

[!ENDSELECT!]
[!ENDFOR!]
[!ENDIF!]

#define CANTSYN_START_SEC_CONFIG_DATA_UNSPECIFIED
#include <CanTSyn_MemMap.h>


[!VAR "IcvDataIndex" = "0"!]
[!VAR "ComputedIcvIndex" = "0"!]
[!IF "$CanTSyn_TMSize != 0"!]
[!CALL "GetCanTSynMasterDomainsList"!]
[!CALL "IsMasterTimeValidationSupported"!]
CONST(CanTSyn_TimeMasterDomainConfigType, CANTSYN_APPL_CONST) CanTSyn_TimeMasterConfig[[!"num:i($CanTSyn_TMSize)"!]] =
{
[!FOR "i" = "0" TO "$CanTSyn_TMSize - 1"!][!//
  [!VAR "currentTimeDomainCfg"="text:split($sortedMasterDomainsList,',')[position()-1 = $i]"!]
  [!SELECT "node:ref($currentTimeDomainCfg)"!][!//

  /* [!"as:name(.)"!] */
  {
  [!IF "$CanTSyn_CRCMasterDomains != 0"!]
    [!IF "node:value(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxCrcSecured) = 'CRC_SUPPORTED'"!]
      [!IF "(node:value(./CanTSynGlobalTimeDomainId) < 16)"!]
    &CanTSyn_DataIdListSyncValues_[!"as:name(.)"!][0], /* DataID List for the SYNC messages */
    &CanTSyn_DataIdListFupValues_[!"as:name(.)"!][0], /* DataID List for the FUP messages */
      [!ELSE!]
    &CanTSyn_DataIdListOfsValues_[!"as:name(.)"!][0], /* DataID List for the OFS messages */
        [!IF "node:value(./CanTSynUseExtendedMsgFormat) = 'false'"!]
    &CanTSyn_DataIdListOfnsValues_[!"as:name(.)"!][0], /* DataID List for the OFNS messages */
        [!ELSE!]
    NULL_PTR,
        [!ENDIF!]
      [!ENDIF!]
    [!ELSE!]
    NULL_PTR,
    NULL_PTR,
    [!ENDIF!]
  [!ENDIF!]
  [!IF "$isIcvGenerationSupported = 'true'"!]
    [!IF "node:exists(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvGeneration)"!]
      [!VAR "dataLength"="18"!] /* SYNC + FUP payload */
    [!"num:i($IcvDataIndex)"!]U, /* IcvDataStartIndex */
    [!"num:i(as:ref(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvGeneration/CanTSynIcvGenerationJobRef)/CsmJobId)"!]U, /* IcvGenerationJobId */
      [!IF "$isFvUsedInIcvGeneration = 'true'"!]
        [!IF "node:exists(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvGeneration/CanTSynIcvGenerationFvIdRef)"!]
          [!VAR "StbMFreshnessValue"="./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvGeneration/CanTSynIcvGenerationFvIdRef"!]
          [!VAR "FvLength" = "num:i(as:ref($StbMFreshnessValue)/StbMFreshnessValueLength)"!]
    [!"num:i($FvLength)"!]U, /* IcvGenerationFvLength */
          [!VAR "dataLength" = "$dataLength + num:i(((num:i($FvLength)+7) div 8))"!]
    [!"num:i(as:ref($StbMFreshnessValue)/StbMFreshnessValueTruncLength)"!]U, /* IcvGenerationFvTruncLength */
        [!ELSE!]
    CANTSYN_ICV_PARAMETER_NOT_USED_32_BITS, /* IcvGenerationFvLength */
    CANTSYN_ICV_PARAMETER_NOT_USED_32_BITS, /* IcvGenerationFvTruncLength */
        [!ENDIF!]
      [!ENDIF!]
    [!"num:i($dataLength)"!]U, /* IcvDataLength */
      [!VAR "IcvDataIndex"="$IcvDataIndex + $dataLength"!]  
    [!ELSE!]
    CANTSYN_ICV_PARAMETER_NOT_USED_32_BITS, /* IcvDataStartIndex */
    CANTSYN_ICV_PARAMETER_NOT_USED_32_BITS, /* IcvGenerationJobId */
      [!IF "$isFvUsedInIcvGeneration = 'true'"!]
    CANTSYN_ICV_PARAMETER_NOT_USED_32_BITS, /* IcvGenerationFvLength */
    CANTSYN_ICV_PARAMETER_NOT_USED_32_BITS, /* IcvGenerationFvTruncLength */    
      [!ENDIF!]
    CANTSYN_ICV_PARAMETER_NOT_USED_32_BITS, /* IcvDataLength */
    [!ENDIF!]
  [!ENDIF!]
  [!CALL "TimeoutFloatToMFC", "value"="./CanTSynGlobalTimeMaster/CanTSynGlobalTimeDebounceTime"!]
    [!"num:i($mValue + 1)"!]U, /* Debounce Time (Master) */
  [!CALL "IsTxImmediateTransmissionUsed"!]
  [!IF "$IsTxImmediateTransmissionUsed = 'true'"!]
    [!IF "node:exists(./CanTSynGlobalTimeMaster/CanTSynCyclicMsgResumeTime)"!]
    [!CALL "TimeoutFloatToMFC", "value"="./CanTSynGlobalTimeMaster/CanTSynCyclicMsgResumeTime"!]
    [!"$mValue"!]U, /* CyclicMsgResumeTime (Master) */
    [!ELSE!]
    0U, /* CyclicMsgResumeTime (Master) */
    [!ENDIF!]
  [!ENDIF!]
  [!CALL "TimeoutFloatToMFC", "value"="./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxPeriod"!]
    [!"$mValue"!]U, /* SyncTxInterval (Master) */
  [!IF "node:exists(./CanTSynGlobalTimeMaster/CanTSynMasterConfirmationTimeout)"!]
  [!CALL "TimeoutFloatToMFC", "value"="./CanTSynGlobalTimeMaster/CanTSynMasterConfirmationTimeout"!]
  [!ELSE!]
  [!CALL "TimeoutFloatToMFC", "value"="3"!]
  [!ENDIF!]
    [!"$mValue"!]U, /* Confirmation Timeout */
    [!"num:i(node:value(node:ref(./CanTSynSynchronizedTimeBaseRef)/StbMSynchronizedTimeBaseIdentifier))"!]U, /* StbMSynchronizedTimeBaseIdentifier */
  [!CALL "GetCanIfHandleId", "CanTSynGlobalTimePduRef" = "./CanTSynGlobalTimeMaster/CanTSynGlobalTimeMasterPdu/CanTSynGlobalTimePduRef"!][!//
    [!"$PduId"!]U, /* CanIfTxPduId */
[!IF "$isIcvGenerationSupported = 'true'"!]
  [!IF "node:exists(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvGeneration)"!]
    [!"num:i($ComputedIcvIndex)"!]U, /* ComputedIcvStartIndex */
[!CALL "TimeoutFloatToMFC", "value"="./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvGeneration/CanTSynIcvGenerationTimeout"!]
    [!"$mValue"!]U, /* IcvGenerationTimeout */
    [!IF "$isFvUsedInIcvGeneration = 'true'"!]
      [!IF "node:exists(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvGeneration/CanTSynIcvGenerationFvIdRef)"!]
    [!VAR "StbMFreshnessValue"="./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvGeneration/CanTSynIcvGenerationFvIdRef"!]
    [!"num:i(as:ref($StbMFreshnessValue)/StbMFreshnessValueId)"!]U, /* IcvGenerationFvId */
    TRUE, /* IsFvUsed */
      [!ELSE!]
    CANTSYN_ICV_PARAMETER_NOT_USED_16_BITS, /* IcvGenerationFvId */
    FALSE, /* IsFvUsed */
      [!ENDIF!]
    [!ENDIF!]
    [!"concat("CANTSYN_",string(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvGeneration/CanTSynIcvGenerationBase))"!], /* IcvGenerationBase */
    [!VAR "IcvTxLength"="num:i(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvGeneration/CanTSynIcvTxLength)"!]
    [!"$IcvTxLength"!]U, /* IcvTxLength */
    [!VAR "ComputedIcvIndex"="$ComputedIcvIndex + $IcvTxLength"!]
  [!ELSE!]
    CANTSYN_ICV_PARAMETER_NOT_USED_16_BITS, /* ComputedIcvStartIndex */
    CANTSYN_ICV_PARAMETER_NOT_USED_16_BITS, /* IcvGenerationTimeout */
    [!IF "$isFvUsedInIcvGeneration = 'true'"!]
    CANTSYN_ICV_PARAMETER_NOT_USED_16_BITS, /* IcvGenerationFvId */
    FALSE, /* IsFvUsed */
    [!ENDIF!]
    CANTSYN_ICV_PARAMETER_NOT_USED_8_BITS, /* IcvGenerationBase */
    CANTSYN_ICV_PARAMETER_NOT_USED_8_BITS, /* IcvTxLength */
  [!ENDIF!]
[!ENDIF!]
    [!"num:i(node:value(./CanTSynGlobalTimeDomainId))"!]U, /* TimeDomainId */
  [!CALL "GetCanIfCtrlId", "CanTSynGlobalTimePduRef" = "./CanTSynGlobalTimeMaster/CanTSynGlobalTimeMasterPdu/CanTSynGlobalTimePduRef"!][!//
    [!"$CtrlId"!]U, /* CanIfCtrlId */
  [!CALL "GetCanIfCtrlIndex", "ControllerID" = "$CtrlId"!][!//
    [!"$CtrlIndex"!]U, /* CtrlIdx */
    [!"concat("CANTSYN_",node:value(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxCrcSecured))"!], /* TxCrcSecured */
  [!CALL "isImmediateTimeSync", "value"="./CanTSynGlobalTimeMaster/CanTSynImmediateTimeSync"!]
    [!"$isImmediateTimeSync"!]U, /* ImmediateTimeSync */
[!IF "$CanTSyn_NumTxExtendedMsgFormat > 0"!]
  [!CALL "isExtendedMessage", "value"="./CanTSynUseExtendedMsgFormat"!]
    [!"$isExtendedMessage"!]U, /* ExtendedMessage */
[!ENDIF!]
[!IF "$isMasterTimeValidationSupported = 'true'"!]
  [!IF "node:value(./CanTSynEnableTimeValidation) = 'true'"!]    
    TRUE,/* IsTimeValidationUsed */
    [!"node:value(./CanTSynGlobalTimeNetworkSegmentId)"!]U, /* NetworkSegmentId */
  [!ELSE!]    
    FALSE,/* IsTimeValidationUsed */
    CANTSYN_SEGMENTID_UNUSED, /* NetworkSegmentId */
  [!ENDIF!] 
[!ENDIF!]
    [!"concat("CANTSYN_",string(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvSecured))"!], /* IcvGenerationSupport */
[!IF "$isIcvGenerationSupported = 'true'"!]
  [!IF "node:exists(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvGeneration)"!]
    [!VAR "CsmPrimitiveRef" = "as:ref(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvGeneration/CanTSynIcvGenerationJobRef)/CsmJobPrimitiveRef"!]
    [!IF "string(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvGeneration/CanTSynIcvGenerationBase) = 'ICV_MAC'"!]
    [!"concat("CANTSYN_ICV_",string(as:ref($CsmPrimitiveRef)/CsmMacGenerate/CsmMacGenerateConfig/CsmMacGenerateProcessing))"!]  /* IcvGenerationCsmProcessing */    
    [!ELSE!]
    [!"concat("CANTSYN_ICV_",string(as:ref($CsmPrimitiveRef)/CsmSignatureGenerate/CsmSignatureGenerateConfig/CsmSignatureGenerateProcessing))"!]  /* IcvGenerationCsmProcessing */
    [!ENDIF!]
  [!ELSE!]
    CANTSYN_ICV_PARAMETER_NOT_USED_8_BITS /* IcvGenerationCsmProcessing */
  [!ENDIF!]
[!ENDIF!]    
  },[!//
  [!ENDSELECT!]
[!ENDFOR!]
};
[!ENDIF!]


[!CALL "IsSlaveTimeValidationSupported"!]
[!IF "$CanTSyn_TSSize != 0"!]
[!CALL "GetCanTSynSlaveDomainsList"!]
[!VAR "ExpectedSecurityPayloadLength"="0"!]
CONST(CanTSyn_TimeSlaveDomainConfigType, CANTSYN_APPL_CONST) CanTSyn_TimeSlaveConfig[[!"num:i($CanTSyn_TSSize)"!]] =
{
[!FOR "i" = "0" TO "$CanTSyn_TSSize - 1"!][!//
  [!VAR "currentTimeDomainCfg"="text:split($sortedSlaveDomainsList,',')[position()-1 = $i]"!]
  [!SELECT "node:ref($currentTimeDomainCfg)"!][!//

  /* [!"as:name(.)"!] */
  {
  [!IF "$CanTSyn_CRCSlaveDomains != 0"!]
    [!IF "(node:value(./CanTSynGlobalTimeSlave/CanTSynRxCrcValidated) = 'CRC_VALIDATED') or (node:value(./CanTSynGlobalTimeSlave/CanTSynRxCrcValidated) = 'CRC_OPTIONAL')"!]
      [!IF "(node:value(./CanTSynGlobalTimeDomainId) < 16)"!]
    &CanTSyn_DataIdListSyncValues_[!"as:name(.)"!][0],
    &CanTSyn_DataIdListFupValues_[!"as:name(.)"!][0],
      [!ELSE!]
    &CanTSyn_DataIdListOfsValues_[!"as:name(.)"!][0],
        [!IF "node:value(./CanTSynUseExtendedMsgFormat) = 'false'"!]
    &CanTSyn_DataIdListOfnsValues_[!"as:name(.)"!][0],
        [!ELSE!]
    NULL_PTR,
        [!ENDIF!]
      [!ENDIF!]
    [!ELSE!]
    NULL_PTR,
    NULL_PTR,
    [!ENDIF!]
  [!ENDIF!]
  [!IF "$isIcvVerificationSupported = 'true'"!]
    [!IF "node:exists(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeRxIcvVerification)"!]
      [!VAR "dataLength"="18"!] /* SYNC + FUP payload */
    [!"num:i($IcvDataIndex)"!]U, /* IcvDataStartIndex */
    [!"num:i(as:ref(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeRxIcvVerification/CanTSynIcvVerificationJobRef)/CsmJobId)"!]U, /* IcvVerificationJobId */
      [!IF "$isFvUsedInIcvVerification = 'true'"!]
        [!IF "node:exists(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeRxIcvVerification/CanTSynIcvVerificationFvIdRef)"!]
          [!VAR "StbMFreshnessValue"="./CanTSynGlobalTimeSlave/CanTSynGlobalTimeRxIcvVerification/CanTSynIcvVerificationFvIdRef"!]
          [!VAR "FvLength" = "num:i(as:ref($StbMFreshnessValue)/StbMFreshnessValueLength)"!]
    [!"$FvLength"!]U, /* IcvVerificationFvLength */
          [!VAR "dataLength" = "$dataLength + num:i(((num:i($FvLength)+7) div 8))"!]
          [!VAR "TruncFvLength"="num:i(as:ref($StbMFreshnessValue)/StbMFreshnessValueTruncLength)"!]
    [!"$TruncFvLength"!]U, /* IcvVerificationFvTruncLength */
          [!IF "$TruncFvLength < $FvLength"!]
            [!VAR "ExpectedSecurityPayloadLength"="$ExpectedSecurityPayloadLength + num:i(((num:i($TruncFvLength)+7) div 8))"!]
          [!ELSE!]
            [!VAR "ExpectedSecurityPayloadLength"="$ExpectedSecurityPayloadLength + num:i(((num:i($FvLength)+7) div 8))"!]
          [!ENDIF!]
        [!ELSE!]
    CANTSYN_ICV_PARAMETER_NOT_USED_32_BITS, /* IcvVerificationFvLength */
    CANTSYN_ICV_PARAMETER_NOT_USED_32_BITS, /* IcvVerificationFvTruncLength */
        [!ENDIF!]
      [!ENDIF!]
    [!"num:i($dataLength)"!]U, /* IcvDataLength */
      [!VAR "IcvDataIndex"="$IcvDataIndex + $dataLength"!]      
    [!ELSE!]
    CANTSYN_ICV_PARAMETER_NOT_USED_32_BITS, /* IcvDataStartIndex */
    CANTSYN_ICV_PARAMETER_NOT_USED_32_BITS, /* IcvVerificationJobId */
      [!IF "$isFvUsedInIcvVerification = 'true'"!]
    CANTSYN_ICV_PARAMETER_NOT_USED_32_BITS, /* IcvVerificationFvLength */
    CANTSYN_ICV_PARAMETER_NOT_USED_32_BITS, /* IcvVerificationFvTruncLength */  
      [!ENDIF!]
    CANTSYN_ICV_PARAMETER_NOT_USED_32_BITS, /* IcvDataLength */  
    [!ENDIF!]
  [!ENDIF!]
  [!IF "../../CanTSynReportError/CanTSynSyncFailedReportError = 'DEM'"!]
    [!IF "node:exists(CanTSynGlobalTimeSlave/CanTSynDemEventParameterRefs/CANTSYN_E_SYNC_FAILED)"!]
    [!"node:value(as:ref(CanTSynGlobalTimeSlave/CanTSynDemEventParameterRefs/CANTSYN_E_SYNC_FAILED)/DemEventId)"!]U, /* DEM Event CANTSYN_E_SYNC_FAILED */
    [!ELSE!]
    65535U, /* Disabled DEM Event CANTSYN_E_SYNC_FAILED */
    [!ENDIF!]
  [!ENDIF!]
  [!IF "not(../../CanTSynReportError/CanTSynSyncFailedReportError = 'DISABLE')"!]
  [!CALL "TimeoutFloatToMFC", "value"="./CanTSynGlobalTimeSlave/CanTSynReceiveSyncPairsPeriod"!]
    [!"$mValue"!]U, /* Sync Pairs timeout for Dem/Det reporting (Slave) */
  [!ENDIF!]
  [!CALL "TimeoutFloatToMFC", "value"="./CanTSynGlobalTimeSlave/CanTSynGlobalTimeRxDebounceTime"!]
    [!"$mValue"!]U, /* RxDebounceTime (Slave) */
  [!CALL "TimeoutFloatToMFC", "value"="./CanTSynGlobalTimeSlave/CanTSynGlobalTimeFollowUpTimeout"!]
    [!"$mValue"!]U, /* RxFollowUpOffsetInterval (Slave) */
    [!"num:i(node:value(node:ref(./CanTSynSynchronizedTimeBaseRef)/StbMSynchronizedTimeBaseIdentifier))"!]U, /* StbMSynchronizedTimeBaseIdentifier */
[!IF "$isIcvVerificationSupported = 'true'"!]
  [!IF "node:exists(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeRxIcvVerification)"!]
    [!"num:i($ComputedIcvIndex)"!]U, /* ComputedIcvStartIndex */
    [!CALL "TimeoutFloatToMFC", "value"="./CanTSynGlobalTimeSlave/CanTSynGlobalTimeRxIcvVerification/CanTSynIcvVerificationTimeout"!]
    [!"$mValue"!]U, /* IcvVerificationTimeout */
    [!"num:i(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeRxIcvVerification/CanTSynIcvVerificationAttempts)"!]U, /* IcvVerificationAttempts */
    [!IF "$isFvUsedInIcvVerification = 'true'"!]
      [!IF "node:exists(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeRxIcvVerification/CanTSynIcvVerificationFvIdRef)"!]
       [!VAR "StbMFreshnessValue"="./CanTSynGlobalTimeSlave/CanTSynGlobalTimeRxIcvVerification/CanTSynIcvVerificationFvIdRef"!]
    [!"num:i(as:ref($StbMFreshnessValue)/StbMFreshnessValueId)"!]U, /* IcvVerificationFvId */
    TRUE, /* IsFvUsed */
      [!ELSE!]
    CANTSYN_ICV_PARAMETER_NOT_USED_16_BITS, /* IcvVerificationFvId */
    FALSE, /* IsFvUsed */
      [!ENDIF!]
    [!ENDIF!]
    [!VAR "RxLength"="num:i(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeRxIcvVerification/CanTSynIcvRxLength)"!]
    [!"$RxLength"!]U, /* IcvRxLength */
    [!VAR "ExpectedSecurityPayloadLength"="$ExpectedSecurityPayloadLength + $RxLength"!]
    [!"concat("CANTSYN_",string(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeRxIcvVerification/CanTSynIcvVerificationBase))"!], /* IcvVerificationBase */
  [!ELSE!]
    CANTSYN_ICV_PARAMETER_NOT_USED_16_BITS, /* ComputedIcvStartIndex */
    CANTSYN_ICV_PARAMETER_NOT_USED_16_BITS, /* IcvVerificationTimeout */
    CANTSYN_ICV_PARAMETER_NOT_USED_16_BITS, /* IcvVerificationAttempts */
    [!IF "$isFvUsedInIcvVerification = 'true'"!]
    CANTSYN_ICV_PARAMETER_NOT_USED_16_BITS, /* IcvVerificationFvId */  
    FALSE, /* IsFvUsed */
    [!ENDIF!]
    CANTSYN_ICV_PARAMETER_NOT_USED_8_BITS, /* IcvRxLength */
    CANTSYN_ICV_PARAMETER_NOT_USED_8_BITS, /* IcvVerificationBase */
  [!ENDIF!]
[!ENDIF!]
  [!CALL "CheckCanIfRxPdu", "CanTSynGlobalTimePduRef" = "./CanTSynGlobalTimeSlave/CanTSynGlobalTimeSlavePdu/CanTSynGlobalTimePduRef"!][!//
  [!CALL "SlaveTimeDomainId", "value" = "./CanTSynGlobalTimeDomainId"!]
    [!"$mValue"!]U, /* TimeDomainId */
    [!"concat("CANTSYN_",node:value(./CanTSynGlobalTimeSlave/CanTSynRxCrcValidated))"!], /* RxCrcValidated */
    [!"num:i(node:value(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeSequenceCounterHysteresis))"!]U, /* SequenceCounterHysteresis */
    [!"num:i(node:value(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeSequenceCounterJumpWidth))"!]U, /* SequenceCounterJumpWidth */
    [!"num:i($i)"!]U, /* HysteresisArrayIndex */
[!IF "$CanTSyn_NumRxExtendedMsgFormat > 0"!]
  [!CALL "isExtendedMessage", "value"="./CanTSynUseExtendedMsgFormat"!]
    [!"$isExtendedMessage"!]U, /* ExtendedMessage */
[!ENDIF!]
[!IF "$isSlaveTimeValidationSupported = 'true'"!]
  [!IF "node:value(./CanTSynEnableTimeValidation) = 'true'"!]    
    TRUE,/* IsTimeValidationUsed */
    [!"node:value(./CanTSynGlobalTimeNetworkSegmentId)"!]U, /* NetworkSegmentId */
  [!ELSE!]    
    FALSE,/* IsTimeValidationUsed */
    CANTSYN_SEGMENTID_UNUSED, /* NetworkSegmentId */
  [!ENDIF!] 
[!ENDIF!]
    [!"concat("CANTSYN_",string(./CanTSynGlobalTimeSlave/CanTSynRxIcvVerificationType))"!], /* IcvVerificationSupport */ 
[!IF "$isIcvVerificationSupported = 'true'"!]
  [!IF "node:exists(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeRxIcvVerification)"!]
    [!"num:i($ExpectedSecurityPayloadLength)"!]U, /* ExpectedSecurityPayloadLength */
    [!VAR "ExpectedSecurityPayloadLength"="0"!]
    [!VAR "CsmPrimitiveRef" = "as:ref(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeRxIcvVerification/CanTSynIcvVerificationJobRef)/CsmJobPrimitiveRef"!]
    [!IF "string(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeRxIcvVerification/CanTSynIcvVerificationBase) = 'ICV_MAC'"!]
    [!"concat("CANTSYN_ICV_",string(as:ref($CsmPrimitiveRef)/CsmMacVerify/CsmMacVerifyConfig/CsmMacVerifyProcessing))"!] /* IcvVerificationCsmProcessing */
    [!ELSE!]
    [!"concat("CANTSYN_ICV_",string(as:ref($CsmPrimitiveRef)/CsmSignatureVerify/CsmSignatureVerifyConfig/CsmSignatureVerifyProcessing))"!] /* IcvVerificationCsmProcessing */
    [!ENDIF!]
  [!ELSE!]
    CANTSYN_ICV_PARAMETER_NOT_USED_8_BITS, /* ExpectedSecurityPayloadLength */
    CANTSYN_ICV_PARAMETER_NOT_USED_8_BITS /* IcvVerificationCsmProcessing */
  [!ENDIF!]
[!ENDIF!]
  },[!//
  [!ENDSELECT!]
[!ENDFOR!]

};
[!ENDIF!]

#define CANTSYN_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include <CanTSyn_MemMap.h>

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
[!ENDCODE!]


