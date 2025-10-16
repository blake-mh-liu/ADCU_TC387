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
[!INCLUDE "../include/CanTSyn_PrecompileMacros.m"!][!//
#include <CanTSyn_Int_Cfg.h>

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[internal constants]====================================*/

/*==================[internal data]=========================================*/

/*==================[external constants]====================================*/

#define CANTSYN_START_SEC_CONFIG_DATA_UNSPECIFIED
#include <CanTSyn_MemMap.h>

[!IF "$isMulticoreEnabled = 'true'"!][!//

[!CALL "numberOfEcuCPartitionsUsedByCanTSyn"!]
[!CALL "isOnlyTimeDomainMFAllocUsed"!][!//
[!IF "$isOnlyTimeDomainMFAllocUsed = 'false'"!][!//
  [!VAR "partitionRefName" = "concat('EcucPartition_',num:i($numberOfEcuCPartitionsUsedByCanTSyn - 1))"!][!//
  [!CALL "GetNumberOfTimeDomainsNotConnectedToAnyPartition"!][!//
CONST(uint16, CANTSYN_APPL_CONST) CanTSyn_[!"$partitionRefName"!]_TimeDomainsList[[!"num:i($notConnectedTimeDomainCounter)"!]] =
{
  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*"!][!//
    [!VAR "pduIndex" = "0"!][!//
    [!VAR "directionType" = "0"!][!//
    [!VAR "indexDirectionType" = "0"!][!//
    [!IF "((node:exists(./CanTSynGlobalTimeMaster)) and (not(node:exists(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeMasterDomainPartitionRef))))"!][!//
      [!VAR "pduIndex" = "bit:shl(node:value(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeMasterPdu/CanTSynGlobalTimeMasterConfirmationHandleId),8)"!][!//
      [!IF "(node:value(./CanTSynGlobalTimeDomainId) < 16)"!][!//
        [!VAR "indexDirectionType" = "bit:or($pduIndex,$directionType)"!][!//
  [!"$indexDirectionType"!]U, /* [!"bit:shr($pduIndex,8)"!] | 0x00000000 (pduIndex | SyncTx) */
      [!ELSE!][!//
        [!VAR "directionType" = "bit:bitset($directionType, 1)"!][!//
        [!VAR "indexDirectionType" = "bit:or($pduIndex,$directionType)"!][!//
  [!"$indexDirectionType"!]U, /* [!"bit:shr($pduIndex,8)"!] | 0x00000010 (pduIndex | OfsTx) */
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!IF "((node:exists(./CanTSynGlobalTimeSlave)) and (not(node:exists(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeSlaveDomainPartitionRef))))"!]
        [!VAR "pduIndex" = "bit:shl(node:value(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeSlavePdu/CanTSynGlobalTimeSlaveHandleId),8)"!]
        [!IF "(node:value(./CanTSynGlobalTimeDomainId) < 16)"!][!//
          [!VAR "directionType" = "bit:bitset($directionType, 0)"!][!//
          [!VAR "indexDirectionType" = "bit:or($pduIndex,$directionType)"!][!//
  [!"$indexDirectionType"!]U, /* [!"bit:shr($pduIndex,8)"!] | 0x00000001 (pduIndex | SyncRx) */
        [!ELSE!][!//
          [!VAR "directionType" = "bit:bitset($directionType, 0)"!][!//
          [!VAR "directionType" = "bit:bitset($directionType, 1)"!][!//
          [!VAR "indexDirectionType" = "bit:or($pduIndex,$directionType)"!][!//
  [!"$indexDirectionType"!]U, /* [!"bit:shr($pduIndex,8)"!] | 0x00000011 (pduIndex | OfsRx) */
        [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
};
[!ENDIF!][!//


[!CALL "CreatePartitionRefList"!]

[!VAR "lastPartitionRef"!][!ENDVAR!][!//
[!VAR "countPartitionsRefsEntries" = "count(text:order(text:split($PartitionsRefList, ';')))"!][!//
[!FOR "PartitionsRefsEntriesIndex" = "1" TO "$countPartitionsRefsEntries"!][!//
  [!VAR "partRefName" = "text:order(text:split($PartitionsRefList, ';'))[position() = number($PartitionsRefsEntriesIndex)]"!][!//
  [!VAR "ecucPartitionRefName" = "text:split($partRefName, ':')[1]"!][!//
  [!IF "not($lastPartitionRef = $ecucPartitionRefName)"!][!//
  [!CALL "GetNumberOfConnectedTimeDomains", "ecuCPartitionName" = "$ecucPartitionRefName"!][!//
CONST(uint16, CANTSYN_APPL_CONST) CanTSyn_[!"$ecucPartitionRefName"!]_TimeDomainsList[[!"num:i($connectedTimeDomainCounter)"!]] =
{
  [!LOOP "as:modconf('CanTSyn')[1]/CanTSynGlobalTimeDomain/*"!][!//
    [!VAR "pduIndex" = "0"!][!//
    [!VAR "directionType" = "0"!][!//
    [!VAR "indexDirectionType" = "0"!][!//
    [!IF "((node:exists(./CanTSynGlobalTimeMaster)) and (node:exists(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeMasterDomainPartitionRef)))"!][!//
      [!VAR "partitionRefName" = "as:name(node:ref(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeMasterDomainPartitionRef))"!][!//
      [!IF "$partitionRefName = $ecucPartitionRefName"!][!//
        [!VAR "pduIndex" = "bit:shl(node:value(./CanTSynGlobalTimeMaster/CanTSynGlobalTimeMasterPdu/CanTSynGlobalTimeMasterConfirmationHandleId),8)"!][!//
        [!IF "(node:value(./CanTSynGlobalTimeDomainId) < 16)"!][!//
          [!VAR "indexDirectionType" = "bit:or($pduIndex,$directionType)"!][!//
  [!"$indexDirectionType"!]U, /* [!"bit:shr($pduIndex,8)"!] | 0x00000000 (pduIndex | SyncTx) */
        [!ELSE!][!//
          [!VAR "directionType" = "bit:bitset($directionType, 1)"!][!//
          [!VAR "indexDirectionType" = "bit:or($pduIndex,$directionType)"!][!//
  [!"$indexDirectionType"!]U, /* [!"bit:shr($pduIndex,8)"!] | 0x00000010 (pduIndex | OfsTx) */
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!IF "((node:exists(./CanTSynGlobalTimeSlave)) and (node:exists(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeSlaveDomainPartitionRef)))"!][!//
      [!VAR "partitionRefName" = "as:name(node:ref(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeSlaveDomainPartitionRef))"!][!//
      [!IF "$partitionRefName = $ecucPartitionRefName"!][!//
        [!VAR "pduIndex" = "bit:shl(node:value(./CanTSynGlobalTimeSlave/CanTSynGlobalTimeSlavePdu/CanTSynGlobalTimeSlaveHandleId),8)"!][!//
        [!IF "(node:value(./CanTSynGlobalTimeDomainId) < 16)"!][!//
          [!VAR "directionType" = "bit:bitset($directionType, 0)"!][!//
          [!VAR "indexDirectionType" = "bit:or($pduIndex,$directionType)"!][!//
  [!"$indexDirectionType"!]U, /* [!"bit:shr($pduIndex,8)"!] | 0x00000001 (pduIndex | SyncRx) */
        [!ELSE!][!//
          [!VAR "directionType" = "bit:bitset($directionType, 0)"!][!//
          [!VAR "directionType" = "bit:bitset($directionType, 1)"!][!//
          [!VAR "indexDirectionType" = "bit:or($pduIndex,$directionType)"!][!//
  [!"$indexDirectionType"!]U, /* [!"bit:shr($pduIndex,8)"!] | 0x00000011 (pduIndex | OfsRx) */
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
};
  [!ENDIF!][!//
  [!VAR "lastPartitionRef" = "$ecucPartitionRefName"!][!//
[!ENDFOR!][!//


[!CALL "numberOfEcuCPartitionsUsedByCanTSyn"!][!//
CONST(CanTSyn_PartitionCfgType, CANTSYN_APPL_CONST) CanTSyn_PartitionTimeDomainsList[[!"num:i($numberOfEcuCPartitionsUsedByCanTSyn)"!]] =
{
[!VAR "lastPartitionRef"!][!ENDVAR!][!//
[!VAR "pos" = "0"!][!//
[!VAR "countPartitionsRefsEntries" = "count(text:order(text:split($PartitionsRefList, ';')))"!][!//
[!FOR "PartitionsRefsEntriesIndex" = "1" TO "$countPartitionsRefsEntries"!][!//
  [!VAR "partRefName" = "text:order(text:split($PartitionsRefList, ';'))[position() = number($PartitionsRefsEntriesIndex)]"!][!//
  [!VAR "ecucPartitionRefName" = "text:split($partRefName, ':')[1]"!][!//
  [!IF "not($lastPartitionRef = $ecucPartitionRefName)"!][!//
  {
    [!"num:i($pos)"!]U,  /* partition index */
    [!CALL "GetNumberOfConnectedTimeDomains", "ecuCPartitionName" = "$ecucPartitionRefName"!]
    [!"num:i($connectedTimeDomainCounter)"!]U, /* number of time domains connected to [!"$ecuCPartitionName"!] */
    &CanTSyn_[!"$ecuCPartitionName"!]_TimeDomainsList[0U],  /* pointer to the list of time domains connected to the [!"$ecuCPartitionName"!] partition */
  },
  [!VAR "pos" = "$pos + 1"!]
  [!ENDIF!][!//
  [!VAR "lastPartitionRef" = "$ecucPartitionRefName"!][!//
[!ENDFOR!]
[!IF "$isOnlyTimeDomainMFAllocUsed = 'false'"!][!//
  {
    [!"num:i($pos)"!]U,  /* partition index */
    [!CALL "GetNumberOfTimeDomainsNotConnectedToAnyPartition"!][!//
    [!"num:i($notConnectedTimeDomainCounter)"!]U, /* number of time domains which are not connected to any EcuCPartition */
    &CanTSyn_[!"concat('EcucPartition_',num:i($numberOfEcuCPartitionsUsedByCanTSyn - 1))"!]_TimeDomainsList[0U],  /* pointer to the list of time domains not connected to any EcuCPartition */
  },
[!ENDIF!][!//
};

[!ENDIF!]

#define CANTSYN_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include <CanTSyn_MemMap.h>

/*==================[external data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/


[!IF "$isMulticoreEnabled = 'true'"!][!//

[!CALL "createSlaveTimeDomainMFAlloc"!][!//
[!LOOP "text:split($createSlaveTimeDomainMFAlloc,';')"!][!//
  [!VAR "qRxName" = "text:split(.,':')[1]"!][!//
  [!VAR "partitionName" = "text:split(.,':')[2]"!][!//
  [!VAR "qRxName" = "concat('CanTSyn_', $MulticoreVendorID, '_', $partitionName, $qRxName)"!][!//

#define CANTSYN_[!"$MulticoreVendorID"!]_[!"$partitionName"!]_START_SEC_CODE
#include <CanTSyn_[!"$MulticoreVendorID"!]_[!"$partitionName"!]_MemMap.h>

/** \brief CanTSyn Rx main function
 **
 ** Processes decoupled TimeSlavePdus
 **
 ** This function has to be called by a task controlled by the
 ** BSW scheduler.
 **
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
FUNC(void, CANTSYN_[!"$MulticoreVendorID"!]_[!"$partitionName"!]_CODE) [!"$qRxName"!](void)
{
  CanTSyn_MainFunction_Rx([!"text:split(.,':')[3]"!]U);
}

#define CANTSYN_[!"$MulticoreVendorID"!]_[!"$partitionName"!]_STOP_SEC_CODE
#include <CanTSyn_[!"$MulticoreVendorID"!]_[!"$partitionName"!]_MemMap.h>
[!ENDLOOP!][!//Rx



[!CALL "createMasterTimeDomainMFAlloc"!][!//
[!LOOP "text:split($createMasterTimeDomainMFAlloc,';')"!][!//
  [!VAR "qTxName" = "text:split(.,':')[1]"!][!//
  [!VAR "partitionName" = "text:split(.,':')[2]"!][!//
  [!VAR "qTxName" = "concat('CanTSyn_', $MulticoreVendorID, '_', $partitionName, $qTxName)"!][!//

#define CANTSYN_[!"$MulticoreVendorID"!]_[!"$partitionName"!]_START_SEC_CODE
#include <CanTSyn_[!"$MulticoreVendorID"!]_[!"$partitionName"!]_MemMap.h>

/** \brief CanTSyn Tx main function
 **
 ** Performs the processes of the activities that are not directly initiated by
 ** the calls from CAN driver.
 **
 ** This function has to be called by a task controlled by the
 ** BSW scheduler.
 **
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
FUNC(void, CANTSYN_[!"$MulticoreVendorID"!]_[!"$partitionName"!]_CODE) [!"$qTxName"!](void)
{
  CanTSyn_MainFunction_Tx([!"text:split(.,':')[3]"!]U);
}
#define CANTSYN_[!"$MulticoreVendorID"!]_[!"$partitionName"!]_STOP_SEC_CODE
#include <CanTSyn_[!"$MulticoreVendorID"!]_[!"$partitionName"!]_MemMap.h>
[!ENDLOOP!][!//Tx
[!ENDIF!][!//

/*==================[end of file]===========================================*/
[!ENDCODE!][!//
