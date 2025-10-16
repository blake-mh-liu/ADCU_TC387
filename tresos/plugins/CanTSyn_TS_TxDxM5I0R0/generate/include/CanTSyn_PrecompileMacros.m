[!/**
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
 */!][!//
[!NOCODE!]
[!// multiple inclusion protection
[!IF "not(var:defined('CANTSYN_PRECOMPILEMACROS_M'))"!]
[!VAR "CANTSYN_PRECOMPILEMACROS_M"="'true'"!][!/*

=== Size of the CanTSyn Time Domains ===
*/!][!VAR "CanTSyn_TDSize" = "num:i(count(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*))"!][!/*

=== Size of The total CanTSyn Master Time Domains ===
*/!][!VAR "CanTSyn_TMSize" = "num:i(count(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*/CanTSynGlobalTimeMaster))"!][!/*

=== Size of The total CanTSyn Slave Time Domains ===
*/!][!VAR "CanTSyn_TSSize" = "num:i(count(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*/CanTSynGlobalTimeSlave))"!][!/*

=== Size of The CanTSyn SYNC Time Domains with Domain Id value less than 16 and with CRC support on Master or CRC support on Slave ===
*/!][!VAR "CanTSyn_SyncDomains" = "num:i(count(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[(CanTSynGlobalTimeDomainId < 16) and (((node:exists(CanTSynGlobalTimeMaster)) and (node:value(CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxCrcSecured) = 'CRC_SUPPORTED')) or ((node:exists(CanTSynGlobalTimeSlave)) and ((node:value(CanTSynGlobalTimeSlave/CanTSynRxCrcValidated) = 'CRC_VALIDATED') or (node:value(CanTSynGlobalTimeSlave/CanTSynRxCrcValidated) = 'CRC_OPTIONAL'))))]))"!][!/*

=== Size of The CanTSyn OFFSET Time Domains with Domain Id value greather or equal than 16 with CRC support on Master or CRC support on Slave ===
*/!][!VAR "CanTSyn_OffsetDomains" = "num:i(count(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[(CanTSynGlobalTimeDomainId > 15) and (((node:exists(CanTSynGlobalTimeMaster)) and (node:value(CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxCrcSecured) = 'CRC_SUPPORTED')) or ((node:exists(CanTSynGlobalTimeSlave)) and ((node:value(CanTSynGlobalTimeSlave/CanTSynRxCrcValidated) = 'CRC_VALIDATED') or (node:value(CanTSynGlobalTimeSlave/CanTSynRxCrcValidated) = 'CRC_OPTIONAL'))))]))"!][!/*

=== Size of The CanTSyn Master Time Domains with CRC support ===
*/!][!VAR "CanTSyn_CRCMasterDomains" = "num:i(count(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[(node:exists(CanTSynGlobalTimeMaster)) and (node:value(CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxCrcSecured) = 'CRC_SUPPORTED')]))"!][!/*

=== Size of The CanTSyn Slave Time Domains with CRC support ===
*/!][!VAR "CanTSyn_CRCSlaveDomains" = "num:i(count(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[(node:exists(CanTSynGlobalTimeSlave)) and ((node:value(CanTSynGlobalTimeSlave/CanTSynRxCrcValidated) = 'CRC_VALIDATED') or (node:value(CanTSynGlobalTimeSlave/CanTSynRxCrcValidated) = 'CRC_OPTIONAL'))]))"!][!/*

=== Size of The CanTSyn Master Time Domains with Domain less than 16 ===
*/!][!VAR "CanTSyn_SyncTMSize" = "num:i(count(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[node:exists(./CanTSynGlobalTimeMaster) and (CanTSynGlobalTimeDomainId<16)]))"!][!/*

=== Size of The CanTSyn Slave Time Domains with Domain less than 16 ===
*/!][!VAR "CanTSyn_SyncTSSize" = "num:i(count(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[(node:exists(./CanTSynGlobalTimeSlave)) and (CanTSynGlobalTimeDomainId<16)]))"!][!/*

=== Size of The CanTSyn Master Time Domains with Domain greater than 15 ===
*/!][!VAR "CanTSyn_OffsetTMSize" = "num:i(count(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[(node:exists(./CanTSynGlobalTimeMaster)) and (CanTSynGlobalTimeDomainId>15)]))"!][!/*

=== Size of The CanTSyn Slave Time Domains with Domain greater than 15 ===
*/!][!VAR "CanTSyn_OffsetTSSize" = "num:i(count(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[(node:exists(./CanTSynGlobalTimeSlave)) and (CanTSynGlobalTimeDomainId>15)]))"!][!/*

=== Size of The CanTSyn Master Time Domains with support for ICV authentication ===
*/!][!VAR "CanTSyn_IcvTMSize" = "num:i(count(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[(node:exists(./CanTSynGlobalTimeMaster)) and (string(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvSecured) = 'ICV_SUPPORTED')]))"!][!/*

=== Size of The CanTSyn Slave Time Domains with support for ICV authentication ===
*/!][!VAR "CanTSyn_IcvTSSize" = "num:i(count(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[(node:exists(./CanTSynGlobalTimeSlave)) and (node:exists(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeRxIcvVerification))]))"!][!/*

=== Number of Tx time domains which have CanTSynUseExtendedMsgFormat enabled ===
*/!][!VAR "CanTSyn_NumTxExtendedMsgFormat" = "num:i(count(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*/CanTSynGlobalTimeMaster/*[../../CanTSynUseExtendedMsgFormat = 'true']))"!][!/*

=== Number of Rx time domains which have CanTSynUseExtendedMsgFormat enabled ===
*/!][!VAR "CanTSyn_NumRxExtendedMsgFormat" = "num:i(count(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*/CanTSynGlobalTimeSlave/*[../../CanTSynUseExtendedMsgFormat = 'true']))"!][!/*

=== Check if dem is used ===
*/!][!VAR "useDEM"="(as:modconf('CanTSyn')[1]/CanTSynReportError/CanTSynSyncFailedReportError = 'DEM')"!][!/*

=== Multicore support ===
*/!][!VAR "isMulticoreEnabled" = "as:modconf('CanTSyn')[1]/CanTSynGeneral/CanTSynMultiCoreSupport = 'true'"!][!/*

=== Check if Security Event Reporting is enabled ===
*/!][!VAR "isSecurityEventReportingEnabled" = "as:modconf('CanTSyn')[1]/CanTSynGeneral/CanTSynEnableSecurityEventReporting = 'true'"!][!/*

=== Macro to translate the configured timeout float into number of main function cycles. ===
Note: If value is not a multiple of the main function period, it is round down.
      Rounding down has the advantage for wait for send timeouts because a frame is then sent
      earlier and the receiver will not run into a timeout while waiting for the next frame.

*/!][!MACRO "TimeoutFloatToMFC", "value"!][!NOCODE!]
[!VAR "mValue" = "num:i($value div as:modconf('CanTSyn')[1]/CanTSynGeneral/CanTSynMainFunctionPeriod)"!]
[!ENDNOCODE!][!ENDMACRO!][!/*

=== Macro to translate the configured Slave Time Domain ID. ===
*/!][!MACRO "SlaveTimeDomainId", "value"!][!NOCODE!]
[!VAR "mValue" = "num:i($value)"!]
[!IF "$mValue>15"!]
  [!VAR "mValue" = "num:i($value - 16)"!]
[!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!][!/*

===Macro to sort the Time Domain List based on the DomainId
*/!][!MACRO "GetCanTSynCRCSyncDomains", ""!]
    [!VAR "sortedDomainsList"="text:join(node:paths(util:distinct(node:order(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[(CanTSynGlobalTimeDomainId < 16) and (((node:exists(CanTSynGlobalTimeMaster)) and (node:value(CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxCrcSecured) = 'CRC_SUPPORTED')) or ((node:exists(CanTSynGlobalTimeSlave)) and ((node:value(CanTSynGlobalTimeSlave/CanTSynRxCrcValidated) = 'CRC_VALIDATED') or (node:value(CanTSynGlobalTimeSlave/CanTSynRxCrcValidated) = 'CRC_OPTIONAL'))))],'CanTSynGlobalTimeDomainId '))),',')"!]
[!ENDMACRO!][!/*

===Macro to sort the Time Domain List based on the DomainId
*/!][!MACRO "GetCanTSynCRCOffsetDomains", ""!]
    [!VAR "sortedDomainsList"="text:join(node:paths(util:distinct(node:order(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[(CanTSynGlobalTimeDomainId > 15) and (((node:exists(CanTSynGlobalTimeMaster)) and (node:value(CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxCrcSecured) = 'CRC_SUPPORTED')) or ((node:exists(CanTSynGlobalTimeSlave)) and ((node:value(CanTSynGlobalTimeSlave/CanTSynRxCrcValidated) = 'CRC_VALIDATED') or (node:value(CanTSynGlobalTimeSlave/CanTSynRxCrcValidated) = 'CRC_OPTIONAL'))))],'CanTSynGlobalTimeDomainId '))),',')"!]
[!ENDMACRO!][!/*

=== Macro to sort the Master Time Domain List based on the CanTSynGlobalTimeMasterConfirmationHandleId. ===
*/!][!MACRO "GetCanTSynMasterDomainsList", ""!]
    [!VAR "sortedMasterDomainsList"="text:join(node:paths(util:distinct(node:order(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[node:exists(./CanTSynGlobalTimeMaster)],'CanTSynGlobalTimeMaster/CanTSynGlobalTimeMasterPdu/CanTSynGlobalTimeMasterConfirmationHandleId'))),',')"!]
[!ENDMACRO!][!/*

=== Macro to sort the Slave Time Domain List based on the CanTSynGlobalTimeSlaveHandleId. ===
*/!][!MACRO "GetCanTSynSlaveDomainsList", ""!]
    [!VAR "sortedSlaveDomainsList"="text:join(node:paths(util:distinct(node:order(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[node:exists(./CanTSynGlobalTimeSlave)],'CanTSynGlobalTimeSlave/CanTSynGlobalTimeSlavePdu/CanTSynGlobalTimeSlaveHandleId'))),',')"!]
[!ENDMACRO!][!/*

****************************************************************************************************
* Create a list of PDU names and the corresponding handle IDs.
* - CanIfTxRefToHandleIdList will hold all source PDU IDs of all CanIf TxPdus.
* Each list is realized as continuous string. The string contains tuples separated by ";". Each
* tuple contains two elements separated by ":". First element of tuple is the PDU reference. The
* Second element of the tuple is the corresponding handle ID.
* A list, for example, looks like this: Pdu_0:321;Pdu_1:322;Pdu_3:323;
* The location of the PDU AUTOSAR/TOP-LEVEL-PACKAGES/EcuC/ELEMENTS/EcuC/EcucPduCollection/Pdu/ is
* not shown in the example.
****************************************************************************************************
*/!]
[!VAR "CanIfTxRefToHandleIdList"="''"!]
[!// Iterate over all Tx PDUs to collect the PDU-IDs
[!LOOP "as:modconf('CanIf')[1]/CanIfInitCfg/*/CanIfTxPduCfg/*"!]
  [!// Get the source PDU-ID of a Tx PDU
  [!VAR "HandleId" = "./CanIfTxPduId"!]
  [!VAR "PduRef" = "node:path(node:ref(./CanIfTxPduRef))"!]
  [!VAR "CanIfTxRefToHandleIdList"!][!"$CanIfTxRefToHandleIdList"!];[!"$PduRef"!]:[!"$HandleId"!][!ENDVAR!]
  [!// Get the PDU-IDs of a Tx PDU

[!ENDLOOP!]


****************************************************************************************************
* Create a list of PDU names and the corresponding handle IDs.
* - CanIfRxRefToHandleIdList will hold all source PDU IDs of all CanIf RxPdus.
* Each list is realized as continuous string. The string contains tuples separated by ";". Each
* tuple contains two elements separated by ":". First element of tuple is the PDU reference. The
* Second element of the tuple is the corresponding handle ID.
* A list, for example, looks like this: Pdu_0:321;Pdu_1:322;Pdu_3:323;
* The location of the PDU AUTOSAR/TOP-LEVEL-PACKAGES/EcuC/ELEMENTS/EcuC/EcucPduCollection/Pdu/ is
* not shown in the example.
****************************************************************************************************
*/!]
[!VAR "CanIfRxRefToHandleIdList"="''"!]
[!// Iterate over all Rx PDUs to collect the PDU-IDs
[!LOOP "as:modconf('CanIf')[1]/CanIfInitCfg/*/CanIfRxPduCfg/*"!]
  [!// Get the source PDU-ID of a Rx PDU
  [!VAR "HandleId" = "./CanIfRxPduId"!]
  [!VAR "PduRef" = "node:path(node:ref(./CanIfRxPduRef))"!]
  [!VAR "CanIfRxRefToHandleIdList"!][!"$CanIfRxRefToHandleIdList"!];[!"$PduRef"!]:[!"$HandleId"!][!ENDVAR!]
  [!// Get the PDU-IDs of a Rx PDU

[!ENDLOOP!]


****************************************************************************************************
* Create a list of PDU names and the corresponding controller handle IDs.
* - CanIfTxRefToCtrlIdList will hold all source Controller IDs of all CanIf TxPdus.
* Each list is realized as continuous string. The string contains tuples separated by ";". Each
* tuple contains two elements separated by ":". First element of tuple is the PDU path. The
* second element of the tuple is the corresponding handle ID.
* A list, for example, looks like this: Pdu_0:321;Pdu_1:322;Pdu_3:323;
* The location of the PDU AUTOSAR/TOP-LEVEL-PACKAGES/EcuC/ELEMENTS/EcuC/EcucPduCollection/Pdu/ is
* not shown in the example.
****************************************************************************************************
*/!]
[!VAR "CanTSyn_CtrlSize" = "num:i(0)"!]
[!VAR "CanIfTxRefToCtrlIdList"="''"!]
[!// Iterate over all Tx PDUs to collect the Ctrl IDs
[!LOOP "as:modconf('CanIf')[1]/CanIfInitCfg/*/CanIfTxPduCfg/*"!]
  [!VAR "PduRef" = "node:path(node:ref(./CanIfTxPduRef))"!]
  [!VAR "CtrlIdx" = "as:ref(as:ref(as:ref(./CanIfTxPduBufferRef)/CanIfBufferHthRef/*[1])/CanIfHthCanCtrlIdRef)/CanIfCtrlId"!]
  [!VAR "CtrlIdFound" = "false()"!]

  [!LOOP "text:split($CanIfTxRefToCtrlIdList,';')"!]
    [!IF "text:split(.,':')[2] = string($CtrlIdx)"!]
      [!VAR "CtrlIdFound" = "true()"!]
      [!BREAK!]
    [!ENDIF!]
  [!ENDLOOP!]


  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*"!]
    [!IF "node:exists(./CanTSynGlobalTimeMaster)"!]
      [!IF "string($PduRef) = node:path(node:ref(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeMasterPdu/CanTSynGlobalTimePduRef))"!]
        [!IF "$CtrlIdFound = 'false'"!]
          [!VAR "CanTSyn_CtrlSize" = "$CanTSyn_CtrlSize + 1"!]
        [!ENDIF!]

        [!VAR "CanIfTxRefToCtrlIdList"!][!"$CanIfTxRefToCtrlIdList"!];[!"$PduRef"!]:[!"$CtrlIdx"!][!ENDVAR!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDLOOP!]


****************************************************************************************************
* Create a list of controller handle IDs and indexes the corresponding controllers.
* - CanIfIndexToCtrlIdList will hold all indexes of all Controller IDs.
* Each list is realized as continuous string. The string contains tuples separated by ";". Each
* tuple contains two elements separated by ":". First element of tuple is the Controller ID. The
* second element of the tuple is the corresponding index.
* A list, for example, looks like this: Pdu_0:321;Pdu_1:322;Pdu_3:323;
* The location of the PDU AUTOSAR/TOP-LEVEL-PACKAGES/EcuC/ELEMENTS/EcuC/EcucPduCollection/Pdu/ is
* not shown in the example.
****************************************************************************************************
*/!]
[!VAR "CanTSyn_CtrlIndex" = "num:i(0)"!]
[!VAR "CanIfIndexToCtrlIdList"="''"!]
[!// Iterate over all Tx PDUs to collect the Ctrl IDs
[!LOOP "as:modconf('CanIf')[1]/CanIfCtrlDrvCfg/*[1]/CanIfCtrlCfg/*"!]
  [!VAR "CtrlID" = "./CanIfCtrlId"!]

  [!LOOP "text:split($CanIfTxRefToCtrlIdList,';')"!]
    [!IF "text:split(.,':')[2] = string($CtrlID)"!]
      [!VAR "CanIfIndexToCtrlIdList"!][!"$CanIfIndexToCtrlIdList"!];[!"$CtrlID"!]:[!"$CanTSyn_CtrlIndex"!][!ENDVAR!]
      [!VAR "CanTSyn_CtrlIndex" = "$CanTSyn_CtrlIndex + 1"!]
      [!BREAK!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDLOOP!]




[!/*
****************************************************************************************************
* MACRO to get the CanIfCtrlId with which CanTSyn_SetTransmissionMode() will be called. The macro parameter
* "CanTSynGlobalTimePduRef" must reference this PDU. The controller ID is stored in the global variable "CtrlId".
****************************************************************************************************
*/!]
[!MACRO "GetCanIfCtrlId","CanTSynGlobalTimePduRef"!][!NOCODE!]
  [!VAR "PduRefPath" = "node:path(node:ref($CanTSynGlobalTimePduRef))"!]
  [!LOOP "text:split($CanIfTxRefToCtrlIdList,';')"!]
    [!IF "string(text:split(.,':')[1]) = $PduRefPath"!]
      [!VAR "CtrlId" = "text:split(.,':')[2]"!]
      [!BREAK!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!]


[!/*
****************************************************************************************************
* MACRO to get the GetCanIfCtrlIndex with which CanTSyn_SetTransmissionMode() will be called. The macro
* parameter "CtrlId" represents the handle ID of this controller. The controller index is stored in the
* global variable "CtrlIndex".
****************************************************************************************************
*/!]
[!MACRO "GetCanIfCtrlIndex","ControllerID"!][!NOCODE!]
  [!LOOP "text:split($CanIfIndexToCtrlIdList,';')"!]
    [!IF "string(text:split(.,':')[1]) = $ControllerID"!]
      [!VAR "CtrlIndex" = "num:i(text:split(.,':')[2])"!]
      [!BREAK!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO to get the value of CanTSynImmediateTimeSync parameter
*
* isImmediateTimeSync is called to check whether CanTSynImmediateTimeSync is TRUE or FALSE
****************************************************************************************************
*/!]
[!MACRO "isImmediateTimeSync","value"!][!NOCODE!]
  [!VAR "isImmediateTimeSync" = "num:i(0)"!]
  [!IF "$value = 'true'"!]
    [!VAR "isImmediateTimeSync" = "num:i(1)"!]
  [!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO to get the value of CanTSynUseExtendedMsgFormat parameter
*
* isExtendedMessage is called to check whether CanTSynUseExtendedMsgFormat is TRUE or FALSE
****************************************************************************************************
*/!]
[!MACRO "isExtendedMessage","value"!][!NOCODE!]
  [!VAR "isExtendedMessage" = "num:i(0)"!]
  [!IF "$value = 'true'"!]
    [!VAR "isExtendedMessage" = "num:i(1)"!]
  [!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO to check whether the ICV generation is supported or not for the Master feature.
****************************************************************************************************
*/!]

[!MACRO "isIcvGenerationSupported",""!][!NOCODE!]
  [!VAR "isIcvGenerationSupported" = "false()"!]
  [!// Iterate over all Master TimeDomains to check if the ICV generation is supported
  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*"!]
    [!IF "node:exists(./CanTSynGlobalTimeMaster)"!]
      [!IF "node:value(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvSecured) = 'ICV_SUPPORTED'"!]
        [!VAR "isIcvGenerationSupported" = "true()"!]
        [!BREAK!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO to check if freshness value is used in ICV generation for any time master.
****************************************************************************************************
*/!]

[!MACRO "isFvUsedInIcvGeneration",""!][!NOCODE!]
  [!VAR "isFvUsedInIcvGeneration" = "false()"!]
  [!// Iterate over all Master TimeDomains to check if the Freshness Value is used in ICV generation
  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*"!]
    [!IF "node:exists(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvGeneration/CanTSynIcvGenerationFvIdRef)"!]
      [!VAR "isFvUsedInIcvGeneration" = "true()"!]
      [!BREAK!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO to check if there is any master time domain that uses truncated freshness values for ICV
* generation.
****************************************************************************************************
*/!]

[!MACRO "isTruncatedFvUsed",""!][!NOCODE!]
  [!VAR "isTruncatedFvUsed" = "false()"!]
  [!// Iterate over all Master TimeDomains to check if the Freshness Value with truncated length is used
  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*"!]
    [!IF "node:exists(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvGeneration/CanTSynIcvGenerationFvIdRef)"!]
      [!VAR "StbMFreshnessValue"="./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvGeneration/CanTSynIcvGenerationFvIdRef"!]
        [!IF "num:i(as:ref($StbMFreshnessValue)/StbMFreshnessValueLength) > num:i(as:ref($StbMFreshnessValue)/StbMFreshnessValueTruncLength)"!]
          [!VAR "isTruncatedFvUsed" = "true()"!]
          [!BREAK!]
        [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO to check if freshness value is used in ICV verification.
****************************************************************************************************
*/!]

[!MACRO "isFvUsedInIcvVerification",""!][!NOCODE!]
  [!VAR "isFvUsedInIcvVerification" = "false()"!]
  [!// Iterate over all Slave TimeDomains to check if the Freshness Value is used in ICV verification
  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*"!]
    [!IF "node:exists(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeRxIcvVerification/CanTSynIcvVerificationFvIdRef)"!]
      [!VAR "isFvUsedInIcvVerification" = "true()"!]
      [!BREAK!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO to check whether the ICV verification is supported or not for the Slave feature.
****************************************************************************************************
*/!]

[!MACRO "isIcvVerificationSupported",""!][!NOCODE!]
  [!VAR "isIcvVerificationSupported" = "false()"!]
  [!// Iterate over all Slave TimeDomains to check if the ICV verification is supported
  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*"!]
    [!IF "node:exists(./CanTSynGlobalTimeSlave)"!]
      [!VAR "IcvVerificationType" = "string(./CanTSynGlobalTimeSlave/CanTSynRxIcvVerificationType)"!]
      [!IF "($IcvVerificationType = 'ICV_OPTIONAL') or ($IcvVerificationType = 'ICV_VERIFIED')"!]
        [!VAR "isIcvVerificationSupported" = "true()"!]
        [!BREAK!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO to compute the total length of the IcvData array. The freshness value is configured in bits
* and has to be converted to byte value.
****************************************************************************************************
*/!]

[!MACRO "getIcvTotalDataLength",""!][!NOCODE!]
  [!VAR "IcvTotalDataLength" = "0"!]
  [!VAR "SyncFupCombinedSize" = "18"!]
  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*"!]
    [!IF "node:exists(./CanTSynGlobalTimeMaster) and (string(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvSecured) = 'ICV_SUPPORTED')"!]
      [!IF "node:exists(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvGeneration/CanTSynIcvGenerationFvIdRef)"!]
        [!VAR "StbMFreshnessValue"="./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvGeneration/CanTSynIcvGenerationFvIdRef"!]
        [!VAR "FvLength" = "(((num:i(as:ref($StbMFreshnessValue)/StbMFreshnessValueLength)) + 7) div 8)"!]
        [!VAR "IcvTotalDataLength" = "$IcvTotalDataLength + $SyncFupCombinedSize + $FvLength"!]
      [!ELSE!]
        [!VAR "IcvTotalDataLength" = "$IcvTotalDataLength + $SyncFupCombinedSize"!]
      [!ENDIF!]
    [!ENDIF!]
    [!IF "node:exists(./CanTSynGlobalTimeSlave) and ((string(./CanTSynGlobalTimeSlave/CanTSynRxIcvVerificationType) = 'ICV_VERIFIED') or (string(./CanTSynGlobalTimeSlave/CanTSynRxIcvVerificationType) = 'ICV_OPTIONAL') )"!]
      [!IF "node:exists(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeRxIcvVerification/CanTSynIcvVerificationFvIdRef)"!]
        [!VAR "StbMFreshnessValue"="./CanTSynGlobalTimeSlave/CanTSynGlobalTimeRxIcvVerification/CanTSynIcvVerificationFvIdRef"!]
        [!VAR "FvLength" = "(((num:i(as:ref($StbMFreshnessValue)/StbMFreshnessValueLength)) + 7) div 8)"!]
        [!VAR "IcvTotalDataLength" = "$IcvTotalDataLength + $SyncFupCombinedSize + $FvLength"!]
      [!ELSE!]
        [!VAR "IcvTotalDataLength" = "$IcvTotalDataLength + $SyncFupCombinedSize"!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO to get the information if the CRC is used for the Master feature.
****************************************************************************************************
*/!]

[!MACRO "getComputedIcvTotalLength",""!][!NOCODE!]
  [!VAR "IcvComputedTotalLength" = "0"!]
  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*"!]
    [!IF "node:exists(./CanTSynGlobalTimeMaster) and (string(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvSecured) = 'ICV_SUPPORTED')"!]
        [!VAR "IcvLength" = "num:i(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvGeneration/CanTSynIcvTxLength)"!]
        [!VAR "IcvComputedTotalLength" = "num:i($IcvComputedTotalLength) + num:i($IcvLength)"!]
    [!ENDIF!]
    [!IF "node:exists(./CanTSynGlobalTimeSlave) and ((string(./CanTSynGlobalTimeSlave/CanTSynRxIcvVerificationType) = 'ICV_VERIFIED') or (string(./CanTSynGlobalTimeSlave/CanTSynRxIcvVerificationType) = 'ICV_OPTIONAL') )"!]
        [!VAR "IcvLength" = "num:i(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeRxIcvVerification/CanTSynIcvRxLength)"!]
        [!VAR "IcvComputedTotalLength" = "num:i($IcvComputedTotalLength) + num:i($IcvLength)"!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO to compute the maximum value of the freshness value length. Value is configured in bits
* and has to be converted to byte value.
****************************************************************************************************
*/!]

[!MACRO "getMaxFreshnessValueLength",""!][!NOCODE!]
  [!VAR "FvMaxLength" = "1"!]
  [!VAR "TruncFvMaxLength" = "1"!]
  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*"!]
    [!IF "node:exists(./CanTSynGlobalTimeMaster) and (string(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvSecured) = 'ICV_SUPPORTED')"!]
      [!IF "node:exists(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvGeneration/CanTSynIcvGenerationFvIdRef)"!]
        [!VAR "StbMFreshnessValue"="./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvGeneration/CanTSynIcvGenerationFvIdRef"!]
        [!VAR "FvLength" = "(((num:i(as:ref($StbMFreshnessValue)/StbMFreshnessValueLength)) + 7) div 8)"!]
        [!VAR "TruncFvLength" = "(((num:i(as:ref($StbMFreshnessValue)/StbMFreshnessValueTruncLength)) + 7) div 8)"!]
        [!IF "$FvLength > $FvMaxLength"!]
          [!VAR "FvMaxLength" = "num:i($FvLength)"!]
        [!ENDIF!]
        [!IF "$TruncFvLength > $TruncFvMaxLength"!]
          [!VAR "TruncFvMaxLength" = "num:i($TruncFvLength)"!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]

    [!IF "node:exists(./CanTSynGlobalTimeSlave) and ((string(./CanTSynGlobalTimeSlave/CanTSynRxIcvVerificationType) = 'ICV_VERIFIED') or (string(./CanTSynGlobalTimeSlave/CanTSynRxIcvVerificationType) = 'ICV_OPTIONAL') )"!]
      [!IF "node:exists(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeRxIcvVerification/CanTSynIcvVerificationFvIdRef)"!]
        [!VAR "StbMFreshnessValue"="./CanTSynGlobalTimeSlave/CanTSynGlobalTimeRxIcvVerification/CanTSynIcvVerificationFvIdRef"!]
        [!VAR "FvLength" = "num:i(((num:i(as:ref($StbMFreshnessValue)/StbMFreshnessValueLength)) + 7) div 8)"!]
        [!VAR "TruncFvLength" = "num:i(((num:i(as:ref($StbMFreshnessValue)/StbMFreshnessValueTruncLength)) + 7) div 8)"!]
        [!IF "$FvLength > $FvMaxLength"!]
          [!VAR "FvMaxLength" = "num:i($FvLength)"!]
        [!ENDIF!]
        [!IF "$TruncFvLength > $TruncFvMaxLength"!]
          [!VAR "TruncFvMaxLength" = "num:i($TruncFvLength)"!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO to check for the usage of Csm_MacGenerate
****************************************************************************************************
*/!]

[!MACRO "isCsmMacGenerateUsed",""!][!NOCODE!]
  [!VAR "CsmMacGenerateUsage" = "'false'"!]
  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*"!]
    [!IF "node:exists(./CanTSynGlobalTimeMaster) and (string(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvSecured) = 'ICV_SUPPORTED')"!]
      [!IF "string(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvGeneration/CanTSynIcvGenerationBase) = 'ICV_MAC'"!]
        [!VAR "CsmMacGenerateUsage" = "'true'"!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO to check for the usage of Csm_SignatureGenerate
****************************************************************************************************
*/!]

[!MACRO "isCsmSignatureGenerateUsed",""!][!NOCODE!]
  [!VAR "CsmSignatureGenerateUsage" = "'false'"!]
  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*"!]
    [!IF "node:exists(./CanTSynGlobalTimeMaster) and (string(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvSecured) = 'ICV_SUPPORTED')"!]
      [!IF "string(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxIcvGeneration/CanTSynIcvGenerationBase) = 'ICV_SIGNATURE'"!]
        [!VAR "CsmSignatureGenerateUsage" = "'true'"!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO to check for the usage of Csm_MacVerify
****************************************************************************************************
*/!]

[!MACRO "isCsmMacVerifyUsed",""!][!NOCODE!]
  [!VAR "CsmMacVerifyUsage" = "'false'"!]
  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*"!]
    [!IF "node:exists(./CanTSynGlobalTimeSlave) and ((string(./CanTSynGlobalTimeSlave/CanTSynRxIcvVerificationType) = 'ICV_VERIFIED') or (string(./CanTSynGlobalTimeSlave/CanTSynRxIcvVerificationType) = 'ICV_OPTIONAL') )"!]
      [!IF "string(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeRxIcvVerification/CanTSynIcvVerificationBase) = 'ICV_MAC'"!]
        [!VAR "CsmMacVerifyUsage" = "'true'"!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO to check for the usage of Csm_SignatureVerify
****************************************************************************************************
*/!]

[!MACRO "isCsmSignatureVerifyUsed",""!][!NOCODE!]
  [!VAR "CsmSignatureVerifyUsage" = "'false'"!]
  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*"!]
    [!IF "node:exists(./CanTSynGlobalTimeSlave) and ((string(./CanTSynGlobalTimeSlave/CanTSynRxIcvVerificationType) = 'ICV_VERIFIED') or (string(./CanTSynGlobalTimeSlave/CanTSynRxIcvVerificationType) = 'ICV_OPTIONAL') )"!]
      [!IF "string(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeRxIcvVerification/CanTSynIcvVerificationBase) = 'ICV_SIGNATURE'"!]
        [!VAR "CsmSignatureVerifyUsage" = "'true'"!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO to get the information if the CRC is used for the Master feature.
****************************************************************************************************
*/!]

[!MACRO "IsTxCRCUsed",""!][!NOCODE!]
  [!VAR "isTxCRCUsed" = "false()"!]
  [!// Iterate over all TimeDomain to check if the CRC is used
  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*"!]
    [!IF "node:exists(./CanTSynGlobalTimeMaster)"!]
      [!IF "node:value(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeTxCrcSecured) = 'CRC_SUPPORTED'"!]
        [!VAR "isTxCRCUsed" = "true()"!]
        [!BREAK!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!]


[!/*
****************************************************************************************************
* MACRO to get the information if immediate transmission is used for the Master feature.
****************************************************************************************************
*/!]
[!MACRO "IsTxImmediateTransmissionUsed",""!][!NOCODE!]
  [!VAR "IsTxImmediateTransmissionUsed" = "false()"!]
  [!// Iterate over all TimeDomain to check if the Immediate Transmission is used
  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*"!]
    [!IF "node:exists(./CanTSynGlobalTimeMaster)"!]
      [!IF "node:value(./CanTSynGlobalTimeMaster/CanTSynImmediateTimeSync) = 'true'"!]
        [!VAR "IsTxImmediateTransmissionUsed" = "true()"!]
        [!BREAK!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!]


[!/*
****************************************************************************************************
* MACRO to get the information if the CRC is used for the Slave feature.
****************************************************************************************************
*/!]
[!MACRO "IsRxCRCUsed",""!][!NOCODE!]
  [!VAR "isRxCRCUsed" = "false()"!]
  [!// Iterate over all TimeDomain to check if the CRC is used
  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*"!]
    [!IF "node:exists(./CanTSynGlobalTimeSlave)"!]
      [!IF "(node:value(./CanTSynGlobalTimeSlave/CanTSynRxCrcValidated) = 'CRC_VALIDATED') or (node:value(./CanTSynGlobalTimeSlave/CanTSynRxCrcValidated) = 'CRC_OPTIONAL')"!]
        [!VAR "isRxCRCUsed" = "true()"!]
        [!BREAK!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!]


[!/*
****************************************************************************************************
* MACRO to get the information if the sequence counter Hysteresis is used for the Slave feature.
****************************************************************************************************
*/!]
[!MACRO "IsScHysteresisUsed",""!][!NOCODE!]
  [!VAR "IsScHysteresisUsed" = "false()"!]
  [!// Iterate over all TimeDomain to check if the SC Hysteresis is configured > 0
  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*"!]
    [!IF "node:exists(./CanTSynGlobalTimeSlave)"!]
      [!IF "(node:value(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeSequenceCounterHysteresis) > 0)"!]
        [!VAR "IsScHysteresisUsed" = "true()"!]
        [!BREAK!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!]


[!/*
****************************************************************************************************
* MACRO to get the information if the Tx Offset is used.
****************************************************************************************************
*/!]
[!MACRO "IsTxOffsetUsed",""!][!NOCODE!]
  [!VAR "isTxOffsetUsed" = "false()"!]
  [!IF "$CanTSyn_OffsetTMSize != 0"!]
    [!VAR "isTxOffsetUsed" = "true()"!]
  [!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!]


[!/*
****************************************************************************************************
* MACRO to get the information if the Rx Offset is used.
****************************************************************************************************
*/!]
[!MACRO "IsRxOffsetUsed",""!][!NOCODE!]
  [!VAR "isRxOffsetUsed" = "false()"!]
  [!IF "$CanTSyn_OffsetTSSize != 0"!]
    [!VAR "isRxOffsetUsed" = "true()"!]
  [!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!]


[!/*
****************************************************************************************************
* MACRO to get the information if OFNS frames are used.
****************************************************************************************************
*/!]
[!MACRO "IsOFNSFrameUsed",""!][!NOCODE!]
  [!VAR "isOFNSFrameUsed" = "false()"!]
  [!// Iterate over all TimeDomain to check if there is an offset domain not using extended message type
  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*"!]
    [!IF "(CanTSynGlobalTimeDomainId > 15) and (CanTSynUseExtendedMsgFormat = 'false')"!]
      [!VAR "isOFNSFrameUsed" = "true()"!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!]


[!/*
****************************************************************************************************
* MACRO to get the information if the Tx Offset is used.
****************************************************************************************************
*/!]
[!MACRO "IsTxSyncUsed",""!][!NOCODE!]
  [!VAR "isTxSyncUsed" = "false()"!]
  [!IF "$CanTSyn_SyncTMSize != 0"!]
    [!VAR "isTxSyncUsed" = "true()"!]
  [!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!]


[!/*
****************************************************************************************************
* MACRO to get the information if the Rx Offset is used.
****************************************************************************************************
*/!]
[!MACRO "IsRxSyncUsed",""!][!NOCODE!]
  [!VAR "isRxSyncUsed" = "false()"!]
  [!IF "$CanTSyn_SyncTSSize != 0"!]
    [!VAR "isRxSyncUsed" = "true()"!]
  [!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO to get the information if the Time validation is enabled for any Master time domain.
****************************************************************************************************
*/!]
[!MACRO "IsMasterTimeValidationSupported",""!][!NOCODE!]
  [!VAR "isMasterTimeValidationSupported" = "false()"!]
  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*"!]
    [!IF "(as:modconf('CanTSyn')[1]/CanTSynGeneral/CanTSynTimeValidationSupport = 'true') and (node:exists(./CanTSynGlobalTimeMaster)) and (./CanTSynEnableTimeValidation = 'true')"!]
      [!VAR "isMasterTimeValidationSupported" = "true()"!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO to get the information if the Time validation is enabled for any Slave time domain.
****************************************************************************************************
*/!]
[!MACRO "IsSlaveTimeValidationSupported",""!][!NOCODE!]
  [!VAR "isSlaveTimeValidationSupported" = "false()"!]
  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*"!]
    [!IF "(as:modconf('CanTSyn')[1]/CanTSynGeneral/CanTSynTimeValidationSupport = 'true') and (node:exists(./CanTSynGlobalTimeSlave)) and (./CanTSynEnableTimeValidation = 'true')"!]
      [!VAR "isSlaveTimeValidationSupported" = "true()"!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!]



[!IF "as:modconf('CanTSyn')[1]/CanTSynGeneral/CanTSynMultiCoreSupport = 'true'"!]

[!/*
****************************************************************************************************
* Multicore VENDOR ID
****************************************************************************************************
*/!]
[!VAR "MulticoreVendorID"="num:i(1)"!]


[!/*
****************************************************************************************************
* MACRO to get the information if all Master and Slave time domains use EcuCPartitionRef
****************************************************************************************************
*/!]
[!VAR "isOnlyTimeDomainMFAllocUsed" = "true()"!]
[!MACRO "isOnlyTimeDomainMFAllocUsed",""!][!NOCODE!]
  [!IF "((count(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[((node:exists(./CanTSynGlobalTimeMaster)) and (not(node:exists(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeMasterDomainPartitionRef))))]) > 0) or (count(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[((node:exists(./CanTSynGlobalTimeSlave)) and (not(node:exists(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeSlaveDomainPartitionRef))))]) > 0))"!]
    [!VAR "isOnlyTimeDomainMFAllocUsed" = "false()"!]
  [!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!]


[!/*
****************************************************************************************************
* Macro creates a string-map of EcuCPartitionName-Direction-EcuCPduName allocation and
* adds to the list only the EcucPartitions which are connected to CanTSyn time domains.
* Attribute list elements by colon (:) and entries by semicolon (;).
****************************************************************************************************
*/!]
[!VAR "PartitionsRefList"!][!ENDVAR!][!//
[!VAR "lastPartitionRefNameTx"!][!ENDVAR!][!//
[!VAR "lastPartitionRefNameRx"!][!ENDVAR!][!//
[!MACRO "CreatePartitionRefList"!][!NOCODE!]
[!LOOP "util:distinct(node:order(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[((node:exists(./CanTSynGlobalTimeMaster)) and (node:exists(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeMasterDomainPartitionRef)))], 'node:CanTSynGlobalTimeMaster/CanTSynGlobalTimeMasterDomainPartitionRef'))"!][!//
  [!VAR "partitionNameTx" = "as:name(as:ref(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeMasterDomainPartitionRef))"!][!//
  [!IF "not($lastPartitionRefNameTx = $partitionNameTx)"!][!//
    [!VAR "PartitionsRefList"!][!"$PartitionsRefList"!];[!"as:name(as:ref(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeMasterDomainPartitionRef))"!]:[!"'Tx'"!]:[!"as:name(as:ref(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeMasterPdu/CanTSynGlobalTimePduRef))"!][!ENDVAR!][!//
  [!ENDIF!][!//
  [!VAR "lastPartitionRefNameTx" = "$partitionNameTx"!][!//
[!ENDLOOP!][!//
[!LOOP "util:distinct(node:order(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[((node:exists(./CanTSynGlobalTimeSlave)) and (node:exists(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeSlaveDomainPartitionRef)))], 'node:CanTSynGlobalTimeSlave/CanTSynGlobalTimeSlaveDomainPartitionRef'))"!][!//
  [!VAR "partitionNameRx" = "as:name(as:ref(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeSlaveDomainPartitionRef))"!][!//
  [!IF "not($lastPartitionRefNameRx = $partitionNameRx)"!][!//
    [!VAR "PartitionsRefList"!][!"$PartitionsRefList"!];[!"as:name(as:ref(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeSlaveDomainPartitionRef))"!]:[!"'Rx'"!]:[!"as:name(as:ref(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeSlavePdu/CanTSynGlobalTimePduRef))"!][!ENDVAR!][!//
  [!ENDIF!][!//
  [!VAR "lastPartitionRefNameRx" = "$partitionNameRx"!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!][!ENDMACRO!]



[!CALL "CreatePartitionRefList"!]
[!CALL "isOnlyTimeDomainMFAllocUsed"!]
[!/*
****************************************************************************************************
* Macro creates a string-map of EcuCPartitionName-TimDomainName allocation and
* counts the number of EcuCPartitions which are linked to CanTSyn time domains.
* Attribute list elements by colon (:) and entries by semicolon (;).
****************************************************************************************************
*/!]
[!MACRO "numberOfEcuCPartitionsUsedByCanTSyn",""!][!NOCODE!]
  [!VAR "numberOfEcuCPartitionsUsedByCanTSyn" = "num:i(0)"!]

  [!VAR "lastPartitionRefName"!][!ENDVAR!][!//
  [!LOOP "text:order(text:split($PartitionsRefList, ';'))"!][!//
    [!VAR "partitionRefName" = "text:split(., ':')[1]"!][!//
    [!IF "not($lastPartitionRefName = $partitionRefName)"!][!//
      [!VAR "numberOfEcuCPartitionsUsedByCanTSyn" = "$numberOfEcuCPartitionsUsedByCanTSyn + 1"!]
    [!ENDIF!][!//
    [!VAR "lastPartitionRefName" = "$partitionRefName"!][!//
  [!ENDLOOP!]

  [!IF "($isOnlyTimeDomainMFAllocUsed = 'false')"!]
    [!VAR "numberOfEcuCPartitionsUsedByCanTSyn" = "$numberOfEcuCPartitionsUsedByCanTSyn + 1"!]
  [!ENDIF!]

[!ENDNOCODE!][!ENDMACRO!]


[!/*
****************************************************************************************************
* Macro creates a string-map of SlaveTimeDomain-MainFunctionRx allocation.
* Attribute list elements by colon (:) and entries by semicolon (;).
****************************************************************************************************
*/!]
[!MACRO "createSlaveTimeDomainMFAlloc",""!][!NOCODE!]
  [!VAR "createSlaveTimeDomainMFAlloc"="''"!]
  [!VAR "lastPartitionRef"!][!ENDVAR!][!//
  [!VAR "pos" = "0"!][!//
  [!VAR "countPartitionsRefsEntries" = "count(text:order(text:split($PartitionsRefList, ';')))"!][!//
  [!FOR "PartitionsRefsEntriesIndex" = "1" TO "$countPartitionsRefsEntries"!][!//
    [!VAR "partRefName" = "text:order(text:split($PartitionsRefList, ';'))[position() = number($PartitionsRefsEntriesIndex)]"!][!//
    [!VAR "ecucPartitionRefName" = "text:split($partRefName, ':')[1]"!][!//
    [!IF "not($lastPartitionRef = $ecucPartitionRefName)"!][!//
      [!VAR "direction" = "text:split($partRefName, ':')[2]"!][!//
      [!IF "($direction = 'Rx')"!][!//
        [!VAR "MFname" = "concat('_MainFunction_', $direction)"!]
        [!VAR "createSlaveTimeDomainMFAlloc"!][!"$createSlaveTimeDomainMFAlloc"!];[!"$MFname"!]:[!"$ecucPartitionRefName"!]:[!"num:i($pos)"!][!ENDVAR!]
      [!ENDIF!][!//
      [!VAR "pos" = "$pos + 1"!]
    [!ENDIF!][!//
    [!VAR "lastPartitionRef" = "$ecucPartitionRefName"!][!//
  [!ENDFOR!]
[!ENDNOCODE!][!ENDMACRO!]


[!CALL "createSlaveTimeDomainMFAlloc"!]
[!/*
****************************************************************************************************
* Macro creates a string-map of MasterTimeDomain-MainFunctionTx allocation.
* Attribute list elements by colon (:) and entries by semicolon (;).
****************************************************************************************************
*/!]
[!VAR "createMasterTimeDomainMFAlloc"="''"!]
[!MACRO "createMasterTimeDomainMFAlloc",""!][!NOCODE!]
  [!VAR "lastPartitionRefTx"!][!ENDVAR!][!//
  [!VAR "posTx" = "0"!][!//
  [!VAR "countPartitionsRefsEntries" = "count(text:order(text:split($PartitionsRefList, ';')))"!][!//
  [!FOR "PartitionsRefsEntriesIndex" = "1" TO "$countPartitionsRefsEntries"!][!//
    [!VAR "partRefName" = "text:order(text:split($PartitionsRefList, ';'))[position() = number($PartitionsRefsEntriesIndex)]"!][!//
    [!VAR "ecucPartitionRefName" = "text:split($partRefName, ':')[1]"!][!//
    [!VAR "direction" = "text:split($partRefName, ':')[2]"!][!//
        [!IF "($lastPartitionRefTx = $ecucPartitionRefName)"!]
          [!LOOP "text:split($createSlaveTimeDomainMFAlloc,';')"!]
            [!VAR "partitionName" = "text:split(.,':')[2]"!]
            [!IF "$ecucPartitionRefName = $partitionName"!]
              [!VAR "posTx" = "$posTx - 1"!]
              [!BREAK!]
            [!ENDIF!]
          [!ENDLOOP!]
          [!VAR "MFname" = "concat('_MainFunction_', $direction)"!]
          [!VAR "createMasterTimeDomainMFAlloc"!][!"$createMasterTimeDomainMFAlloc"!];[!"$MFname"!]:[!"$ecucPartitionRefName"!]:[!"num:i($posTx)"!][!ENDVAR!]
        [!ELSE!]
          [!IF "($direction = 'Tx')"!][!//
            [!VAR "MFname" = "concat('_MainFunction_', $direction)"!]
            [!VAR "createMasterTimeDomainMFAlloc"!][!"$createMasterTimeDomainMFAlloc"!];[!"$MFname"!]:[!"$ecucPartitionRefName"!]:[!"num:i($posTx)"!][!ENDVAR!]
          [!ENDIF!]
          [!VAR "posTx" = "$posTx + 1"!]
        [!ENDIF!]
        [!VAR "lastPartitionRefTx" = "$ecucPartitionRefName"!][!//
  [!ENDFOR!]
[!ENDNOCODE!][!ENDMACRO!]



[!/*
**********************************************************************************************************************
* This macro gets the number of connected master/slave time domains for ecuCPartitionName
**********************************************************************************************************************
*/!]
[!MACRO "GetNumberOfConnectedTimeDomains", "ecuCPartitionName"!][!NOCODE!]
  [!VAR "connectedTimeDomainCounter" = "0"!]
  [!// loop through MASTERs and count each master time domain which is linked to ecuCPartitionName
  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[((node:exists(./CanTSynGlobalTimeMaster)) and (node:exists(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeMasterDomainPartitionRef)))]"!]
    [!VAR "masterPartitionRefName" = "as:name(node:ref(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeMasterDomainPartitionRef))"!]
    [!IF "$masterPartitionRefName = $ecuCPartitionName"!]
      [!VAR "connectedTimeDomainCounter" = "num:i($connectedTimeDomainCounter + 1)"!]
    [!ENDIF!]
  [!ENDLOOP!]
  [!// loop through SLAVEs and count each slave time domain which is linked to ecuCPartitionName
  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[((node:exists(./CanTSynGlobalTimeSlave)) and (node:exists(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeSlaveDomainPartitionRef)))]"!]
    [!VAR "slavePartitionRefName" = "as:name(node:ref(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeSlaveDomainPartitionRef))"!]
    [!IF "$slavePartitionRefName = $ecuCPartitionName"!]
      [!VAR "connectedTimeDomainCounter" = "num:i($connectedTimeDomainCounter + 1)"!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!]



[!IF "((count(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[((node:exists(./CanTSynGlobalTimeMaster)) and (not(node:exists(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeMasterDomainPartitionRef))))]) > 0) or (count(as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[((node:exists(./CanTSynGlobalTimeSlave)) and (not(node:exists(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeSlaveDomainPartitionRef))))]) > 0))"!]
[!/*
**********************************************************************************************************************
* This macro gets the number of connected master/slave time domains for ecuCPartitionName
**********************************************************************************************************************
*/!]
[!MACRO "GetNumberOfTimeDomainsNotConnectedToAnyPartition",""!][!NOCODE!]
  [!VAR "notConnectedTimeDomainCounter" = "0"!]
  [!// loop through MASTERs and count each master time domain which is linked to ecuCPartitionName
  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[((node:exists(./CanTSynGlobalTimeMaster)) and (not(node:exists(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeMasterDomainPartitionRef))))]"!]
    [!VAR "notConnectedTimeDomainCounter" = "num:i($notConnectedTimeDomainCounter + 1)"!]
  [!ENDLOOP!]
  [!// loop through SLAVEs and count each slave time domain which is linked to ecuCPartitionName
  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*[((node:exists(./CanTSynGlobalTimeSlave)) and (not(node:exists(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeSlaveDomainPartitionRef))))]"!]
    [!VAR "notConnectedTimeDomainCounter" = "num:i($notConnectedTimeDomainCounter + 1)"!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!]

[!ENDIF!]

[!ENDIF!]



*/!][!ENDIF!][!// CANTSYN_PRECOMPILEMACROS_M

[!ENDNOCODE!][!//


