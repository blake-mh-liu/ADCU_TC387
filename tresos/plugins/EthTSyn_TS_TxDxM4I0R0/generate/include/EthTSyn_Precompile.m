[!/**
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
 */!][!//
[!// multiple inclusion protection
[!IF "not(var:defined('ETHTSYN_PRECOMPILE_M'))"!]
[!VAR "ETHTSYN_PRECOMPILE_M"="'true'"!][!/*

=== Maximum number of EthTSyn controller(number of time domains) ===
*/!][!VAR "EthTSyn_MaxCtrl" = "num:i(count(as:modconf('EthTSyn')[1]/EthTSynGlobalTimeDomain/*[node:exists(./EthTSynPortConfig)]))"!][!/*

=== Maximum number of EthTSyn slaves ===
*/!][!VAR "EthTSyn_MaxSlave" = "num:i(count(as:modconf('EthTSyn')[1]/EthTSynGlobalTimeDomain/*[(node:exists(./EthTSynPortConfig)) and (node:containsValue(./EthTSynPortRole, 'EthTSynGlobalTimeSlave'))]))"!][!/*

=== Number of TimeDomains that have switch configured ===
*/!][!VAR "EthTSyn_TimeDomainsSwt" = "num:i(count(as:modconf('EthTSyn')[1]/EthTSynGlobalTimeDomain/*[(node:exists(./EthTSynPortConfig)) and (node:refvalid(EthTSynSwitchManagementEthSwitchPortHostRef))]))"!][!/*

=== Check if dem is used ===
*/!][!VAR "useDEM"="((as:modconf('EthTSyn')[1]/EthTSynReportError/EthTSynSyncFailedReportError = 'DEM') or (as:modconf('EthTSyn')[1]/EthTSynReportError/EthTSynPdelayFailedReportError = 'DEM') or (as:modconf('EthTSyn')[1]/EthTSynReportError/EthTSynUnexpectedSyncReportError = 'DEM')) "!][!/*
[!/*
****************************************************************************************************
* MACRO to get the information if the CRC is used for the Master feature.
****************************************************************************************************
*/!]
[!MACRO "EthTSyn_MaxSwtPorts",""!][!NOCODE!][!/*
  */!][!VAR "MaxSwtPorts" = "$EthTSyn_TimeDomainsSwt"!][!/*
  */!][!LOOP "as:modconf('EthTSyn')[1]/EthTSynGlobalTimeDomain/*"!][!/*
    */!][!IF "(node:exists(./EthTSynPortConfig))"!][!/*
      */!][!LOOP "./EthTSynPortConfig/*"!][!/*
          */!][!IF "node:refvalid(./EthTSynSwitchManagementEthSwitchPortRef)"!][!/*
             */!][!VAR "MaxSwtPorts" = "$MaxSwtPorts + 1"!][!/*
        */!][!ENDIF!][!/*
      */!][!ENDLOOP!][!/*
    */!][!ENDIF!][!/*
  */!][!ENDLOOP!][!/*
*/!][!ENDNOCODE!][!"num:i($MaxSwtPorts)"!][!ENDMACRO!][!/*

[!/*
****************************************************************************************************
* MACRO to get the information if the CRC is used for the Master feature.
****************************************************************************************************
*/!]
[!MACRO "IsTxCRCUsed",""!][!NOCODE!]
  [!VAR "isTxCRCUsed" = "'false'"!]
  [!// Iterate over all TimeDomain to check if the CRC is used
  [!LOOP "as:modconf('EthTSyn')[1]/EthTSynGlobalTimeDomain/*"!]
    [!IF "node:containsValue(./EthTSynPortRole, 'EthTSynGlobalTimeMaster')"!]
      [!IF "node:value(./EthTSynPortRole/EthTSynGlobalTimeTxCrcSecured) = 'CRC_SUPPORTED'"!]
        [!VAR "isTxCRCUsed" = "'true'"!]
        [!BREAK!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!]

[!/*
****************************************************************************************************
* MACRO to get the information if the ICV is used
****************************************************************************************************
*/!]
[!MACRO "IsICVTxUsed",""!][!NOCODE!]
  [!VAR "IsICVTxUsed" = "'false'"!]
  [!// Iterate over all TimeDomain to check if the CRC is used
  [!LOOP "as:modconf('EthTSyn')[1]/EthTSynGlobalTimeDomain/*"!]
    [!IF "node:containsValue(./EthTSynPortRole, 'EthTSynGlobalTimeMaster')"!]
      [!IF "node:exists(./EthTSynPortRole/EthTSynGlobalTimeTxIcvGeneration)"!]
      [!IF "node:value(./EthTSynPortRole/EthTSynTLVFollowUpICVSubTLV) = 'true'"!]
        [!VAR "IsICVTxUsed" = "'true'"!]
        [!BREAK!]
      [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!][!/*

[!/*
****************************************************************************************************
* MACRO to get the information if the ICVrx is used
****************************************************************************************************
*/!]
[!MACRO "IsICVRxUsed",""!][!NOCODE!]
  [!VAR "IsICVRxUsed" = "'false'"!]
  [!// Iterate over all TimeDomain to check if the CRC is used
  [!LOOP "as:modconf('EthTSyn')[1]/EthTSynGlobalTimeDomain/*"!]
    [!IF "node:containsValue(./EthTSynPortRole, 'EthTSynGlobalTimeSlave')"!]
      [!IF "node:exists(./EthTSynPortRole/EthTSynRxIcvVerificationType)"!]
      [!IF "node:value(./EthTSynPortRole/EthTSynRxIcvVerificationType) = 'ICV_OPTIONAL' or node:value(./EthTSynPortRole/EthTSynRxIcvVerificationType) = 'ICV_VERIFIED'"!]
        [!VAR "IsICVRxUsed" = "'true'"!]
        [!BREAK!]
      [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!][!/*

****************************************************************************************************
* MACRO to get the information if the ICV is used
****************************************************************************************************
*/!]
[!MACRO "IsICVUsed",""!][!NOCODE!]
  [!VAR "IsICVUsed" = "'false'"!]
    [!CALL "IsICVTxUsed"!]
    [!CALL "IsICVRxUsed"!]
    [!IF "($IsICVTxUsed = 'true') or  ($IsICVRxUsed = 'true')"!]
      [!VAR "IsICVUsed" = "'true'"!]
   [!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!][!/*
[!/*
****************************************************************************************************
* MACRO to get the total IcvTxLength
****************************************************************************************************
*/!]
[!MACRO "IcvTxLength",""!][!NOCODE!]
  [!VAR "IcvTxLength" = "0"!]
  [!// Iterate over all Master TimeDomains and add EthTSynIcvTxLength if Synchronous behaviour is used.
  [!LOOP "as:modconf('EthTSyn')[1]/EthTSynGlobalTimeDomain/*"!]
    [!IF "node:containsValue(./EthTSynPortRole, 'EthTSynGlobalTimeMaster')"!]
      [!IF "node:exists(./EthTSynPortRole/EthTSynGlobalTimeTxIcvGeneration)"!]
        [!VAR "IcvTxLength" = "$IcvTxLength + num:i(node:value(./EthTSynPortRole/EthTSynGlobalTimeTxIcvGeneration/EthTSynIcvTxLength))"!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!"num:i($IcvTxLength)"!][!ENDMACRO!][!/*


[!/*
****************************************************************************************************
* MACRO Used to see if IcvGenerationBase or IcvVerificationBase are either ICV_MAC
****************************************************************************************************
*/!]
[!MACRO "IcvBaseMAC",""!][!NOCODE!]
  [!VAR "IcvBaseMAC" = "'false'"!]
  [!// Iterate over all Master TimeDomains to see if IcvGenerationBase or IcvVerificationBase are MAC
  [!LOOP "as:modconf('EthTSyn')[1]/EthTSynGlobalTimeDomain/*"!]
    [!IF "node:containsValue(./EthTSynPortRole, 'EthTSynGlobalTimeMaster')"!]
      [!IF "node:exists(./EthTSynPortRole/EthTSynGlobalTimeTxIcvGeneration)"!]
        [!IF "node:value(./EthTSynPortRole/EthTSynGlobalTimeTxIcvGeneration/EthTSynIcvGenerationBase) = 'ICV_MAC'"!]
          [!VAR "IcvBaseMAC" = "'true'"!]
          [!BREAK!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
    [!IF "node:containsValue(./EthTSynPortRole, 'EthTSynGlobalTimeSlave')"!]
      [!IF "node:exists(./EthTSynPortRole/EthTSynGlobalTimeRxIcvVerification)"!]
        [!IF "node:value(./EthTSynPortRole/EthTSynGlobalTimeRxIcvVerification/EthTSynIcvVerificationBase) = 'ICV_MAC'"!]
          [!VAR "IcvBaseMAC" = "'true'"!]
          [!BREAK!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!][!/*


[!/*
****************************************************************************************************
* MACRO Used to see if IcvGenerationBase or IcvVerificationBase are ICV_SIGNATURE
****************************************************************************************************
*/!]
[!MACRO "IcvBaseSIGNATURE",""!][!NOCODE!]
  [!VAR "IcvBaseSIGNATURE" = "'false'"!]
  [!// Iterate over all Master TimeDomains to see if IcvGenerationBase or IcvVerificationBase are MAC
  [!LOOP "as:modconf('EthTSyn')[1]/EthTSynGlobalTimeDomain/*"!]
    [!IF "node:containsValue(./EthTSynPortRole, 'EthTSynGlobalTimeMaster')"!]
      [!IF "node:exists(./EthTSynPortRole/EthTSynGlobalTimeTxIcvGeneration)"!]
        [!IF "node:value(./EthTSynPortRole/EthTSynGlobalTimeTxIcvGeneration/EthTSynIcvGenerationBase) = 'ICV_SIGNATURE'"!]
          [!VAR "IcvBaseSIGNATURE" = "'true'"!]
          [!BREAK!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
    [!IF "node:containsValue(./EthTSynPortRole, 'EthTSynGlobalTimeSlave')"!]
      [!IF "node:exists(./EthTSynPortRole/EthTSynGlobalTimeRxIcvVerification)"!]
        [!IF "node:value(./EthTSynPortRole/EthTSynGlobalTimeRxIcvVerification/EthTSynIcvVerificationBase) = 'ICV_SIGNATURE'"!]
          [!VAR "IcvBaseSIGNATURE" = "'true'"!]
          [!BREAK!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!][!/*

[!/*
****************************************************************************************************
* MACRO to get the information if the CRC is used for the Slave feature.
****************************************************************************************************
*/!]
[!MACRO "IsRxCRCUsed",""!][!NOCODE!]
  [!VAR "isRxCRCUsed" = "'false'"!]
  [!// Iterate over all TimeDomain to check if the CRC is used
  [!LOOP "as:modconf('EthTSyn')[1]/EthTSynGlobalTimeDomain/*"!]
    [!IF "node:containsValue(./EthTSynPortRole, 'EthTSynGlobalTimeSlave')"!]
      [!IF "(node:exists(./EthTSynPortRole/EthTSynRxCrcValidated))"!]
        [!IF "(node:value(./EthTSynPortRole/EthTSynRxCrcValidated) = 'CRC_VALIDATED') or (node:value(./EthTSynPortRole/EthTSynRxCrcValidated) = 'CRC_OPTIONAL')"!]
          [!VAR "isRxCRCUsed" = "'true'"!]
          [!BREAK!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!][!/*

[!/*
****************************************************************************************************
* MACRO to get the information if the Freshness is used for Slave
****************************************************************************************************
*/!]
[!MACRO "IsRxFVUsed",""!][!NOCODE!]
  [!VAR "IsRxFVUsed" = "'false'"!]
  [!// Iterate over all TimeDomain to check if the CRC is used
  [!LOOP "as:modconf('EthTSyn')[1]/EthTSynGlobalTimeDomain/*"!]
    [!IF "node:containsValue(./EthTSynPortRole, 'EthTSynGlobalTimeSlave')"!]
      [!IF "(node:exists(./EthTSynPortRole/EthTSynGlobalTimeRxIcvVerification))"!]
        [!IF "(node:exists(./EthTSynPortRole/EthTSynGlobalTimeRxIcvVerification/EthTSynIcvVerificationFvIdRef))"!]
          [!VAR "IsRxFVUsed" = "'true'"!]
          [!BREAK!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!][!/*

[!/*
****************************************************************************************************
* MACRO to get the information if the Freshness is used for Slave
****************************************************************************************************
*/!]
[!MACRO "MaxRxIcvSize",""!][!NOCODE!]
  [!VAR "MaxRxIcvSize" = "0"!]
  [!// Iterate over all TimeDomain to check if the ICV is used
  [!LOOP "as:modconf('EthTSyn')[1]/EthTSynGlobalTimeDomain/*"!]
    [!IF "node:containsValue(./EthTSynPortRole, 'EthTSynGlobalTimeSlave')"!]
      [!IF "(node:exists(./EthTSynPortRole/EthTSynGlobalTimeRxIcvVerification))"!]
        [!IF "(node:value(./EthTSynPortRole/EthTSynGlobalTimeRxIcvVerification/EthTSynIcvRxLength) > $MaxRxIcvSize)"!]
          [!VAR "MaxRxIcvSize" = "node:value(./EthTSynPortRole/EthTSynGlobalTimeRxIcvVerification/EthTSynIcvRxLength )"!]
          [!BREAK!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!"num:i($MaxRxIcvSize)"!][!ENDMACRO!][!/*

[!/*
****************************************************************************************************
* MACRO to get the information if the Freshness is used for Master
****************************************************************************************************
*/!]
[!MACRO "IsTxFVUsed",""!][!NOCODE!]
  [!VAR "IsTxFVUsed" = "'false'"!]
  [!// Iterate over all TimeDomain to check if the CRC is used
  [!LOOP "as:modconf('EthTSyn')[1]/EthTSynGlobalTimeDomain/*"!]
    [!IF "node:containsValue(./EthTSynPortRole, 'EthTSynGlobalTimeMaster')"!]
      [!IF "(node:exists(./EthTSynPortRole/EthTSynGlobalTimeTxIcvGeneration))"!]
        [!IF "(node:exists(./EthTSynPortRole/EthTSynGlobalTimeTxIcvGeneration/EthTSynIcvGenerationFvIdRef))"!]
          [!VAR "IsTxFVUsed" = "'true'"!]
          [!BREAK!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!][!/*

[!/*
****************************************************************************************************
* MACRO to get the information if the Freshness with truncated length is used for Master
****************************************************************************************************
*/!]
[!MACRO "IsTruncFVUsed",""!][!NOCODE!]
  [!VAR "IsTruncFVUsed" = "'false'"!]
  [!// Iterate over all TimeDomain to check if the CRC is used
  [!LOOP "as:modconf('EthTSyn')[1]/EthTSynGlobalTimeDomain/*"!]
    [!IF "node:containsValue(./EthTSynPortRole, 'EthTSynGlobalTimeMaster')"!]
      [!IF "(node:exists(./EthTSynPortRole/EthTSynGlobalTimeTxIcvGeneration))"!]
        [!IF "(node:exists(./EthTSynPortRole/EthTSynGlobalTimeTxIcvGeneration/EthTSynIcvGenerationFvIdRef))"!]
          [!VAR "StbMFreshnessValue"="./EthTSynPortRole/EthTSynGlobalTimeTxIcvGeneration/EthTSynIcvGenerationFvIdRef"!]
          [!IF "num:i(as:ref($StbMFreshnessValue)/StbMFreshnessValueLength) > num:i(as:ref($StbMFreshnessValue)/StbMFreshnessValueTruncLength)"!]
            [!VAR "IsTruncFVUsed" = "'true'"!]
            [!BREAK!]
          [!ENDIF!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!][!/*

[!/*
****************************************************************************************************
* MACRO to get the information if the Switch is needed
****************************************************************************************************
*/!]
[!MACRO "IsSwtUsed",""!][!NOCODE!]
  [!VAR "IsSwtUsed" = "'false'"!]
  [!// Iterate over all TimeDomain to check if the Swt is used
  [!LOOP "as:modconf('EthTSyn')[1]/EthTSynGlobalTimeDomain/*"!]
    [!IF "node:refvalid(EthTSynSwitchManagementEthSwitchPortHostRef)"!]
      [!IF "(EthTSynPortRole = 'EthTSynGlobalTimeMaster')"!]
        [!IF "node:refvalid(./EthTSynPortConfig/*/EthTSynSwitchManagementEthSwitchPortRef)"!]
          [!VAR "IsSwtUsed" = "'true'"!]
          [!BREAK!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!][!/*

[!/*
****************************************************************************************************
* MACRO to get the information if the Switch Bridge is used
****************************************************************************************************
*/!]
[!MACRO "IsSwtBridgeUsed",""!][!NOCODE!]
  [!VAR "IsSwtBridgeUsed" = "'false'"!]
  [!// Iterate over all TimeDomain to check if the Swt bridge is used
  [!LOOP "as:modconf('EthTSyn')[1]/EthTSynGlobalTimeDomain/*"!]
    [!IF "((./EthTSynPortRole = 'EthTSynGlobalTimeSlave') and (count(./EthTSynPortConfig/*) > 1))"!]
      [!IF "node:refvalid(./EthTSynPortConfig/*/EthTSynSwitchManagementEthSwitchPortRef)"!]
        [!VAR "IsSwtBridgeUsed" = "'true'"!]
        [!BREAK!]
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!][!/*

[!/*
****************************************************************************************************
* MACRO to get the information if the a different value than EthTSynGlobalTimeTxPdelayReqPeriod will be used.
****************************************************************************************************
*/!]
[!MACRO "IsInitialPdelay",""!][!NOCODE!]
  [!VAR "IsInitialPdelay" = "'false'"!]
  [!// Iterate over all TimeDomain to check if the Swt bridge is used
  [!LOOP "as:modconf('EthTSyn')[1]/EthTSynGlobalTimeDomain/*"!]
  [!LOOP "./EthTSynPortConfig/*"!]
    [!IF "(node:exists(./EthTSynPdelayConfig/EthTSynInitialGlobalTimeTxPdelayReqPeriod) and (node:value(./EthTSynPdelayConfig/EthTSynInitialGlobalTimeTxPdelayReqPeriod) > 0))"!]
      [!VAR "IsInitialPdelay" = "'true'"!]
      [!BREAK!]
    [!ENDIF!]
  [!ENDLOOP!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!][!/*

[!/*
****************************************************************************************************
* MACRO to get the information if the CRC is used for the Master feature.
****************************************************************************************************
*/!]
[!MACRO "EthTSyn_SlaveOfsTimeDomains",""!][!NOCODE!][!/*
  */!][!VAR "OfsTd" = "0"!][!/*
  */!][!LOOP "as:modconf('EthTSyn')[1]/EthTSynGlobalTimeDomain/*"!][!/*
    */!][!IF "(node:value(./EthTSynGlobalTimeDomainId) > 15)"!][!/*
      */!][!VAR "OfsTd" = "$OfsTd + 1"!][!/*
    */!][!ENDIF!][!/*
  */!][!ENDLOOP!][!/*
*/!][!ENDNOCODE!][!"num:i($OfsTd)"!][!ENDMACRO!][!/*


[!/*
****************************************************************************************************
* MACRO to get the information if the Switch is needed
****************************************************************************************************
*/!]
[!MACRO "IsPTPUsed",""!][!NOCODE!]
  [!VAR "IsPTPUsed" = "'false'"!]
  [!// Iterate over all TimeDomain to check if PTP with E2E mechanism is used
  [!LOOP "as:modconf('EthTSyn')[1]/EthTSynGlobalTimeDomain/*"!]
    [!IF "(node:value(./EthTSynEnablePTPCalculation) = 'true')"!]
      [!VAR "IsPTPUsed" = "'true'"!]
      [!BREAK!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDNOCODE!][!ENDMACRO!][!/*


*/!][!ENDIF!][!// ETHTSYN_PRECOMPILE_M
