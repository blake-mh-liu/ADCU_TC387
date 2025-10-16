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
[!IF "not(var:defined('CANTSYN_CHECKS_M'))"!]
[!VAR "CANTSYN_CHECKS_M"="'true'"!][!/*

[!INCLUDE "CanTSyn_PrecompileMacros.m"!][!//

[!/*
****************************************************************************************************
* MACRO to get the CanIfTxPduHandleId with which CanIf_Transmit() has to be called. The macro parameter
* "CanTSynGlobalTimePduRef" must reference this PDU. The PDU-ID is stored in the global variable "PduID".
*
* GetCanIfHandleId is called to check whether the PDU referenced by CanTSynGlobalTimePdu is
* also referenced by any of the CanIfTxPdu.
****************************************************************************************************
*/!]
[!MACRO "GetCanIfHandleId","CanTSynGlobalTimePduRef"!][!NOCODE!]
    [!VAR "PduRefPath" = "node:path(node:ref($CanTSynGlobalTimePduRef))"!]
      [!VAR "FoundIds" = "false()"!]
      [!LOOP "text:split($CanIfTxRefToHandleIdList,';')"!]
          [!IF "string(text:split(.,':')[1]) = $PduRefPath"!]
              [!VAR "PduId" = "text:split(.,':')[2]"!]
              [!VAR "FoundIds" = "true()"!]
              [!BREAK!]
          [!ENDIF!]
      [!ENDLOOP!]
      [!IF "$FoundIds = 'false'"!]
        <!-- !LINKSTO CanTSyn.ECUC_CanTSyn_00027,1 -->
        [!ERROR!] The CanIf module does not reference the PDU '[!"$PduRefPath"!]' [!ENDERROR!]
      [!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!]


[!/*
****************************************************************************************************
* MACRO to check if a CanIfRxPdu is referencing the same Pdu as "CanTSynGlobalTimePduRef" must
* reference this PDU.
*
* CheckCanIfRxPdu is called to check whether the PDU referenced by CanTSynGlobalTimePdu is
* also referenced by any of the CanIfRxPdu.
****************************************************************************************************
*/!]
[!MACRO "CheckCanIfRxPdu","CanTSynGlobalTimePduRef"!][!NOCODE!]
    [!VAR "RxPduRefPath" = "node:path(node:ref($CanTSynGlobalTimePduRef))"!]
      [!VAR "FoundRxId" = "false()"!]
      [!LOOP "text:split($CanIfRxRefToHandleIdList,';')"!]
        [!IF "string(text:split(.,':')[1]) = $RxPduRefPath"!]
          [!VAR "FoundRxId" = "true()"!]
          [!BREAK!]
        [!ENDIF!]
      [!ENDLOOP!]
      [!IF "$FoundRxId = 'false'"!]
        <!-- !LINKSTO CanTSyn.ECUC_CanTSyn_00040,1 -->
        [!ERROR!] The CanIf module does not reference the PDU '[!"$RxPduRefPath"!]' [!ENDERROR!]
      [!ENDIF!]
[!ENDNOCODE!][!ENDMACRO!]





[!/*
***********************************************************************************************************************************************
* ERROR CHECKS for CanTSynMultiCoreSupport activation - CanTSynMultiCoreSupport must be activated in case
*                                                       TimeMasterDomainPartitionRef or TimeSlaveDomainPartitionRef are intended to be used
***********************************************************************************************************************************************
*/!]
[!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*"!]
  [!IF "((node:value(as:modconf('CanTSyn')[1]/CanTSynGeneral/CanTSynMultiCoreSupport) = 'false') and (((node:exists(./CanTSynGlobalTimeMaster)) and (node:exists(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeMasterDomainPartitionRef))) or ((node:exists(./CanTSynGlobalTimeSlave)) and (node:exists(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeSlaveDomainPartitionRef)))))"!]
    [!/* !LINKSTO CanTSyn.EB.Check.CanTSynMultiCoreSupport.Disabled.TimeDomainPartitionRef.Used,1 */!]
    [!ERROR!] CanTSynMultiCoreSupport shall be enabled, if there is at least one CanTSynGlobalTimeMasterDomainPartitionRef or CanTSynGlobalTimeSlaveDomainPartitionRef configured![!ENDERROR!]
    [!BREAK!]
  [!ENDIF!]
[!ENDLOOP!]



[!IF "as:modconf('CanTSyn')[1]/CanTSynGeneral/CanTSynMultiCoreSupport = 'true'"!]

[!CALL "CreatePartitionRefList"!]

[!/*
******************************************************************************************************************
* ERROR CHECKS for EcuCPartition - CanTSynGlobalTimePdu must be linked to the same partition as refered EcuCPdu
******************************************************************************************************************
*/!]

[!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*"!]
  [!IF "((node:exists(./CanTSynGlobalTimeMaster)) and (node:exists(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeMasterDomainPartitionRef)))"!]
    [!VAR "canTSynTxEcucPduRefName" = "as:name(as:ref(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeMasterPdu/CanTSynGlobalTimePduRef))"!]
    [!VAR "canTSynMasterTDPartitionName" = "as:name(as:ref(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeMasterDomainPartitionRef))"!]
    
    [!VAR "countPartitionsRefsEntries" = "count(text:order(text:split($PartitionsRefList, ';')))"!][!//
    [!FOR "PartitionsRefsEntriesIndex" = "1" TO "$countPartitionsRefsEntries"!][!//
       [!VAR "partRefName" = "text:order(text:split($PartitionsRefList, ';'))[position() = number($PartitionsRefsEntriesIndex)]"!][!//
       [!VAR "ecucPartitionRefName" = "text:split($partRefName, ':')[1]"!][!//
       [!VAR "ecucTxPduName" = "text:split($partRefName, ':')[3]"!][!//
       
       [!// refered TxPdu found in the list of EcuCPdus
       [!IF "($canTSynTxEcucPduRefName = $ecucTxPduName)"!]
       
         [!SELECT "as:ref(concat('/EcuC/EcuC/EcucPduCollection/', $ecucTxPduName))"!]
       
           [!IF "((count(./EcucPduDedicatedPartition/*) != 0) and (count(./EcucPduDedicatedPartition/*[(node:value(./EcucPduDedicatedPartitionBswModuleRef) = 'ASPath:/CanIf/CanIf')]) != 0))"!]
             [!LOOP "./EcucPduDedicatedPartition/*[(node:value(./EcucPduDedicatedPartitionBswModuleRef) = 'ASPath:/CanIf/CanIf')]"!]
                 [!VAR "EcuCPduPartitionName" = "as:name(as:ref(./EcucPduDedicatedPartitionRef))"!]
                 [!// throw an error if an EcuCPdu is mapped to a different partition than the linked CanTSynGlobalTimeMasterDomain
                 [!IF "($canTSynMasterTDPartitionName != $EcuCPduPartitionName)"!]
                   [!/* !LINKSTO CanTSyn.EB.Check.EcuCTxPdu.And.CanTSynGlobalTimeMaster.MappedTo.DifferentPartitions.DedicatedPartition,1 */!]
                   [!ERROR!] The EcuCTxPdu named [!"$ecucTxPduName"!] has EcucPduDedicatedPartitionRef configured to a diferent partition than CanTSynGlobalTimeMaster![!ENDERROR!]
                   [!BREAK!]
                 [!ENDIF!]
             [!ENDLOOP!]
           [!ELSEIF "(node:exists(./EcucPduDefaultPartitionRef) = 'true')"!]
             [!VAR "EcuCPduPartitionName" = "as:name(as:ref(./EcucPduDefaultPartitionRef))"!]
             [!// throw an error if an EcuCPdu is mapped to a different partition than the linked CanTSynGlobalTimeMasterDomain
             [!IF "($canTSynMasterTDPartitionName != $EcuCPduPartitionName)"!]
               [!/* !LINKSTO CanTSyn.EB.Check.EcuCTxPdu.And.CanTSynGlobalTimeMaster.MappedTo.DifferentPartitions.DefaultPartition,1 */!]
               [!ERROR!] The EcuCTxPdu named [!"$ecucTxPduName"!] has EcucPduDefaultPartitionRef configured to a diferent partition than CanTSynGlobalTimeMaster![!ENDERROR!]
               [!BREAK!]
             [!ENDIF!]
           [!ELSE!]
             [!// throw an error if an EcuCPdu is mapped to a different partition than the linked CanTSynGlobalTimeMasterDomain
             [!/* !LINKSTO CanTSyn.EB.Check.EcuCTxPdu.MappedTo.NoPartition,1 */!]
             [!ERROR!] The EcuCTxPdu named [!"$ecucTxPduName"!] has no EcucPduDedicatedPartitionRef or EcucPduDefaultPartitionRef configured![!ENDERROR!]
             [!BREAK!]
           [!ENDIF!]
         
         [!ENDSELECT!]
       [!ENDIF!]
    [!ENDFOR!]
  [!ENDIF!]
  

  [!IF "((node:exists(./CanTSynGlobalTimeSlave)) and (node:exists(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeSlaveDomainPartitionRef)))"!]
    [!VAR "canTSynRxEcucPduRefName" = "as:name(as:ref(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeSlavePdu/CanTSynGlobalTimePduRef))"!]
    [!VAR "canTSynSlaveTDPartitionName" = "as:name(as:ref(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeSlaveDomainPartitionRef))"!]

    [!VAR "countPartitionsRefsEntries" = "count(text:order(text:split($PartitionsRefList, ';')))"!][!//
    [!FOR "PartitionsRefsEntriesIndex" = "1" TO "$countPartitionsRefsEntries"!][!//
       [!VAR "partRefName" = "text:order(text:split($PartitionsRefList, ';'))[position() = number($PartitionsRefsEntriesIndex)]"!][!//
       [!VAR "ecucPartitionRefName" = "text:split($partRefName, ':')[1]"!][!//
       [!VAR "ecucRxPduName" = "text:split($partRefName, ':')[3]"!][!//
       
       [!// refered RxPdu found in the list of EcuCPdus
       [!IF "($canTSynRxEcucPduRefName = $ecucRxPduName)"!]
       
         [!SELECT "as:ref(concat('/EcuC/EcuC/EcucPduCollection/', $ecucRxPduName))"!]
       
           [!IF "((count(./EcucPduDedicatedPartition/*) != 0) and (count(./EcucPduDedicatedPartition/*[(node:value(./EcucPduDedicatedPartitionBswModuleRef) = 'ASPath:/CanIf/CanIf')]) != 0))"!]
             [!LOOP "./EcucPduDedicatedPartition/*[(node:value(./EcucPduDedicatedPartitionBswModuleRef) = 'ASPath:/CanIf/CanIf')]"!]
                 [!VAR "EcuCPduPartitionName" = "as:name(as:ref(./EcucPduDedicatedPartitionRef))"!]
                 [!// throw an error if an EcuCPdu is mapped to a different partition than the linked CanTSynGlobalTimeSlaveDomain
                 [!IF "($canTSynSlaveTDPartitionName != $EcuCPduPartitionName)"!]
                   [!/* !LINKSTO CanTSyn.EB.Check.EcuCRxPdu.And.CanTSynGlobalTimeSlave.MappedTo.DifferentPartitions.DedicatedPartition,1 */!]
                   [!ERROR!] The EcuCRxPdu named [!"$ecucRxPduName"!] has EcucPduDedicatedPartitionRef configured to a diferent partition than CanTSynGlobalTimeSlave![!ENDERROR!]
                   [!BREAK!]
                 [!ENDIF!]
             [!ENDLOOP!]
           [!ELSEIF "(node:exists(./EcucPduDefaultPartitionRef) = 'true')"!]
             [!VAR "EcuCPduPartitionName" = "as:name(as:ref(./EcucPduDefaultPartitionRef))"!]
             [!// throw an error if an EcuCPdu is mapped to a different partition than the linked CanTSynGlobalTimeSlaveDomain
             [!IF "($canTSynSlaveTDPartitionName != $EcuCPduPartitionName)"!]
               [!/* !LINKSTO CanTSyn.EB.Check.EcuCRxPdu.And.CanTSynGlobalTimeSlave.MappedTo.DifferentPartitions.DefaultPartition,1 */!]
               [!ERROR!] The EcuCRxPdu named [!"$ecucRxPduName"!] has EcucPduDefaultPartitionRef configured to a diferent partition than CanTSynGlobalTimeSlave![!ENDERROR!]
               [!BREAK!]
             [!ENDIF!]
           [!ELSE!]
             [!// throw an error if an EcuCPdu is mapped to a different partition than the linked CanTSynGlobalTimeSlaveDomain
             [!/* !LINKSTO CanTSyn.EB.Check.EcuCRxPdu.MappedTo.NoPartition,1 */!]
             [!ERROR!] The EcuCRxPdu named [!"$ecucRxPduName"!] has no EcucPduDedicatedPartitionRef or EcucPduDefaultPartitionRef configured![!ENDERROR!]
             [!BREAK!]
           [!ENDIF!]
         
         [!ENDSELECT!]
       [!ENDIF!]
    [!ENDFOR!]
  [!ENDIF!]

[!ENDLOOP!]


[!ENDIF!]



*/!][!ENDIF!][!// CANTSYN_CHECKS_M

[!ENDNOCODE!][!//


