[!/**
 * \file
 *
 * \brief AUTOSAR ComM
 *
 * This file contains the implementation of the AUTOSAR
 * module ComM.
 *
 * \version 5.19.7
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2021 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */!][!//
[!INCLUDE "ComM_Functions.m"!][!//
[!/* These checks were originally present as INVALID checks in ComM.xdm.m4
   * Since these inter-module checks involve parameters from different
   * configuration classes, it's no more possible to keep them in ComM.xdm.m4
   * Refer ASCPROJECT-660 for more details.
   */!]

[!/* *** multiple inclusion protection *** */!]
[!IF "not(var:defined('COMM_CHECKS_M'))"!]
[!VAR "COMM_CHECKS_M" = "'true'"!]

[!NOCODE!][!//

[!CALL "GetUsedUserPlusChannelPlusMasterPncPlusInhibitionOsApplications"!]
[!IF "(count(text:split($FoundUserPlusChannePlusMasterPncPlusInhibitionOsApplications,' ')) > 1) and (as:modconf('ComM')[1]/ComMGeneral/ComMMultiCoreSupport = 'false')"!]
  [!IF "as:modconf('ComM')[1]/ComMGeneral/ComMPncSupport = 'true'"!]
    [!LOOP "as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalDirection='RX']"!]
      [!VAR "varSignalRef" = "ComMPncComSignalRef"!]
      [!IF "num:i(count(as:modconf('Com')[1]/ComConfig/*[1]/ComIPdu/*/ComIPduSignalRef/*[string(.) = $varSignalRef])) != 1"!]
        [!/* !LINKSTO ComM.EB.RxSignalIsNotLinkedToASinglePdu,1 */!]
        [!ERROR!]"Com signal [!"$varSignalRef"!] is referenced by multiple Ipdu or not referenced at all"
        [!ENDERROR!]
      [!ENDIF!]
      [!IF "not(node:refvalid(as:modconf('Com')[1]/ComConfig/*/ComIPdu/*/ComIPduSignalRef/*[string(.) = $varSignalRef]/../../ComMainFunctionRef))"!]
        [!/* !LINKSTO ComM.EB.RxPduComMainfunctionRefNotValid,1 */!]
        [!ERROR!]"IPDU  which contains signal [!"$varSignalRef"!] does not have a valid ComMainFunctionRef"
        [!ENDERROR!]
      [!ENDIF!]
      [!VAR "MainFunctionRef" = "as:modconf('Com')[1]/ComConfig/*/ComIPdu/*/ComIPduSignalRef/*[string(.) = $varSignalRef]/../../ComMainFunctionRef"!]
      [!VAR "PartitionRef" = "node:ref($MainFunctionRef)/ComPartitionRef"!]
      [!IF "count(as:modconf('Os')[1]/OsApplication/*[node:exists(OsAppEcucPartitionRef) and (string(OsAppEcucPartitionRef) = $PartitionRef)]/OsAppEcucPartitionRef) != 1"!]
        [!/* !LINKSTO ComM.EB.RxPduNotLinkedToASingleOsApplication,1 */!]
        [!ERROR!]"One and only one OsApplication shall reference an EcuPartition configured in IPDU which contains Signal [!"$varSignalRef"!] and OsAppEcucPartitionRef shall be enabled"
        [!ENDERROR!]
      [!ENDIF!]
      [!CALL "GetSignalOsApplication","SignalHandle"="node:ref(ComMPncComSignalRef)/ComHandleId","Direction"="'RX'"!]
      [!IF "ComMPncComSignalKind = 'ERA'"!]
        [!CALL "GetChannelOsApplication","ChannelEcuCPartitionRef"="node:ref(ComMPncComSignalChannelRef)/ComMChannelPartitionRef"!]
        [!IF "$SignalOsApplication != $ChannelOsApplication"!]
          [!/* !LINKSTO ComM.EB.RxERASignalSamePartitionAsLinkedChannel,1 */!]
          [!ERROR!]"Signal [!"node:name(node:ref(ComMPncComSignalRef))"!] is not on the same partition as channel [!"node:name(node:ref(ComMPncComSignalChannelRef))"!]"
          [!ENDERROR!]    
        [!ENDIF!]
      [!ELSE!] [!/*[!/*[!IF "ComMPncComSignalKind = 'ERA'"!]*/!]
        [!CALL "GetMasterPncOsApplication"!]
        [!IF "$SignalOsApplication != $MasterPncOsApplication"!]
          [!/* !LINKSTO ComM.EB.RxEIRASignalSamePartitionAsMasterPnc,1 */!]
          [!ERROR!]"Signal [!"node:name(node:ref(ComMPncComSignalRef))"!] is not on the same partition as Master Pnc ComMMasterPNCEcuCPartitionRef!]"
          [!ENDERROR!]        
        [!ENDIF!]
      [!ENDIF!] [!/*[!IF "ComMPncComSignalKind = 'ERA'"!]*/!]
    [!ENDLOOP!]
 
    [!LOOP "as:modconf('ComM')[1]/ComMConfigSet/*[1]/ComMPnc/*/ComMPncComSignal/*[ComMPncComSignalDirection='TX']"!]
      [!VAR "varSignalRef" = "ComMPncComSignalRef"!]
      [!IF "num:i(count(as:modconf('Com')[1]/ComConfig/*[1]/ComIPdu/*/ComIPduSignalRef/*[string(.) = $varSignalRef])) != 1"!]
        [!/* !LINKSTO ComM.EB.TxSignalIsNotLinkedToASinglePdu,1 */!]
        [!ERROR!]"Com signal [!"$varSignalRef"!] is referenced by multiple Ipdu or not referenced at all"
        [!ENDERROR!]
      [!ENDIF!]
      [!IF "not(node:refvalid(as:modconf('Com')[1]/ComConfig/*/ComIPdu/*/ComIPduSignalRef/*[string(.) = $varSignalRef]/../../ComMainFunctionRef))"!]
        [!/* !LINKSTO ComM.EB.TxPduComMainfunctionRefNotValid,1 */!]
        [!ERROR!]"IPDU  which contains signal [!"$varSignalRef"!] does not have a valid ComMainFunctionRef"
        [!ENDERROR!]
      [!ENDIF!]
      [!VAR "MainFunctionRef" = "as:modconf('Com')[1]/ComConfig/*/ComIPdu/*/ComIPduSignalRef/*[string(.) = $varSignalRef]/../../ComMainFunctionRef"!]
      [!VAR "PartitionRef" = "node:ref($MainFunctionRef)/ComPartitionRef"!]
      [!IF "count(as:modconf('Os')[1]/OsApplication/*[node:exists(OsAppEcucPartitionRef) and (string(OsAppEcucPartitionRef) = $PartitionRef)]/OsAppEcucPartitionRef) != 1"!]
        [!/* !LINKSTO ComM.EB.TxPduNotLinkedToASingleOsApplication,1 */!]
        [!ERROR!]"One and only one OsApplication shall reference an EcuPartition configured in IPDU which contains Signal [!"$varSignalRef"!] and OsAppEcucPartitionRef shall be enabled"
        [!ENDERROR!]
      [!ENDIF!]
      [!CALL "GetSignalOsApplication","SignalHandle"="node:ref(ComMPncComSignalRef)/ComHandleId","Direction"="'TX'"!]
      [!IF "ComMPncComSignalKind = 'ERA'"!]
        [!CALL "GetChannelOsApplication","ChannelEcuCPartitionRef"="node:ref(ComMPncComSignalChannelRef)/ComMChannelPartitionRef"!]
        [!IF "$SignalOsApplication != $ChannelOsApplication"!]
          [!/* !LINKSTO ComM.EB.TxERASignalSamePartitionAsLinkedChannel,1 */!]
          [!ERROR!]"Signal [!"node:name(node:ref(ComMPncComSignalRef))"!] is not on the same partition as channel [!"node:name(node:ref(ComMPncComSignalChannelRef))"!]"
          [!ENDERROR!]    
        [!ENDIF!]
      [!ENDIF!] [!/*[!IF "ComMPncComSignalKind = 'ERA'"!]*/!]      
    [!ENDLOOP!]  
  [!ENDIF!]
[!ENDIF!]

[!ENDNOCODE!][!//

[!ENDIF!]

