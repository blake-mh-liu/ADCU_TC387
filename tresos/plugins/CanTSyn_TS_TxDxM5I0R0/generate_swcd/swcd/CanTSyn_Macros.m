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
[!IF "not(var:defined('CANTSYN_MACROS_M'))"!]
[!VAR "CANTSYN_MACROS_M"="'true'"!]


[!IF "as:modconf('CanTSyn')[1]/CanTSynGeneral/CanTSynMultiCoreSupport = 'true'"!]

[!VAR "MulticoreVendorID"="num:i(1)"!]


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



[!ENDIF!]



[!ENDIF!][!// CANTSYN_MACROS_M

[!ENDNOCODE!][!//


