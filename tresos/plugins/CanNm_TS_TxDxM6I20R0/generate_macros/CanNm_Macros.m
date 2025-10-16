[!/**
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
 */!][!//

[!/* *** multiple inclusion protection *** */!]
[!IF "not(var:defined('CANNM_MACROS_M'))"!]
[!VAR "CANNM_MACROS_M" = "'true'"!]

[!/*
*************************************************************************
* MACRO to get the string for the symbolic name value.
* "ShortNameRef" must reference the container holding the short name.
*************************************************************************
*/!][!//
[!NOCODE!][!//
[!MACRO "GetSymbolNameTx","ShortNameRef"!][!//
  [!VAR "SymbolName" = "asc:getShortName($ShortNameRef)"!][!//
  [!IF "$SymbolName = ''"!][!//
    [!VAR "SymbolName" = "concat('CanNmConf_',node:name(../..),'_',as:name(..),'_',as:name(.))"!][!//
  [!ELSE!][!//
    [!VAR "SymbolName" = "concat('CanNmConf_',node:name(.),'_',$SymbolName)"!][!//
  [!ENDIF!][!//
[!ENDMACRO!][!//
[!ENDNOCODE!][!//
[!/*
*************************************************************************
* MACRO to get the string for the symbolic name value.
* "ShortNameRef" must reference the container holding the short name.
*************************************************************************
*/!][!//
[!NOCODE!][!//
[!MACRO "GetSymbolNameRx","ShortNameRef"!][!//
  [!VAR "SymbolName" = "asc:getShortName($ShortNameRef)"!][!//
  [!IF "$SymbolName = ''"!][!//
    [!VAR "SymbolName" = "concat('CanNmConf_',node:name(../../..),'_',as:name(../..),'_',as:name(.))"!][!//
  [!ELSE!][!//
    [!VAR "SymbolName" = "concat('CanNmConf_',node:name(../../..),'_',as:name(../..),'_',$SymbolName)"!][!//
  [!ENDIF!][!//
[!ENDMACRO!][!//
[!ENDNOCODE!][!//
[!/*
*************************************************************************
* MACRO to indicate if multicore is enabled per channel.
*************************************************************************
*/!][!//
[!NOCODE!][!//
[!MACRO "GetMulticorePerChannelSupport"!][!//
  [!VAR "MulticorePerChannelSupport" = "false()"!][!//
  [!/* select one channel that has a partition reference set */!][!//
  [!/* !LINKSTO CanNm.EB.Dsn.Algorithm.ChannelPartition,1 */!]
  [!SELECT "as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmChannelConfig/eb-list::*
              [node:refvalid(node:ref(CanNmComMNetworkHandleRef)/ComMChannelPartitionRef)][1]"!][!//
    [!/* if there is any other channel with different partition set, then multicore is on */!][!//
    [!IF "count(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmChannelConfig/eb-list::*
                  [
                    node:refvalid(node:ref(CanNmComMNetworkHandleRef)/ComMChannelPartitionRef) and 
                    (node:value(node:ref(node:current()/CanNmComMNetworkHandleRef)/ComMChannelPartitionRef) != 
                     node:value(node:ref(CanNmComMNetworkHandleRef)/ComMChannelPartitionRef))
                  ]) > 0"!][!//
      [!VAR "MulticorePerChannelSupport" = "true()"!][!//
    [!ENDIF!][!//
  [!ENDSELECT!][!//
  [!/* !LINKSTO CanNm.EB.Dsn.Algorithm.AggregatePartition,1 */!]
  [!/* if there is a a master pnc partition and any channel has a different partition than that, then multicore is on */!][!//
  [!IF "node:refvalid(as:modconf('ComM')[1]/ComMGeneral/ComMMasterPNCEcuCPartitionRef)"!][!//
    [!IF "count(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmChannelConfig/eb-list::*
                  [
                    node:refvalid(node:ref(CanNmComMNetworkHandleRef)/ComMChannelPartitionRef) and 
                    (node:value(as:modconf('ComM')[1]/ComMGeneral/ComMMasterPNCEcuCPartitionRef) != 
                     node:value(node:ref(CanNmComMNetworkHandleRef)/ComMChannelPartitionRef))
                  ]) > 0"!][!//
      [!VAR "MulticorePerChannelSupport" = "true()"!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDMACRO!][!//
[!ENDNOCODE!][!//
[!/*
*************************************************************************
* MACRO to indicate if PN synchronized shutdown is enabled.
*************************************************************************
*/!][!//
[!NOCODE!][!//
[!MACRO "GetSynchronizedPncShutdownEnabled"!][!//
  [!IF "count(as:modconf('CanNm')[1]/CanNmGlobalConfig/eb-list::*[1]/CanNmChannelConfig/eb-list::*
          [(node:existsAndTrue(CanNmSynchronizedPncShutdownEnabled))]) > 0"!][!//
    [!VAR "SynchronizedPncShutdownEnabled" = "true()"!][!//
  [!ELSE!][!//
    [!VAR "SynchronizedPncShutdownEnabled" = "false()"!][!//
  [!ENDIF!][!//
[!ENDMACRO!][!//
[!ENDNOCODE!][!//
[!ENDIF!]
