[!/**
 * \file
 *
 * \brief AUTOSAR CanIf
 *
 * This file contains the implementation of the AUTOSAR
 * module CanIf.
 *
 * \version 6.10.40
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */!][!//
[!/*
*** multiple inclusion protection ***
*/!][!IF "not(var:defined('CANIF_CHECKS_M'))"!][!/*
*/!][!VAR "CANIF_CHECKS_M"="'true'"!][!/*

*/[!INCLUDE "CanIf_PreCompileMacros.m"!][!/*
*/!][!INCLUDE "CanIf_Macros.m"!][!/*

=============================================================================
Configuration Checks as defined in the DOORS Design Document
=============================================================================


*** Check that all transceivers have different infixes ***
*/!][!LOOP "text:split($trcvInfixList,';')"!][!/*
   */!][!ASSERT "text:uniq(text:split($trcvInfixList,';'), .)"!]Two transceiver drivers used have identical VendorId ('[!"substring-before(., '_')"!]') and VendorApiInfix ('[!"substring-after(., '_')"!]')[!ENDASSERT!][!/*
*/!][!ENDLOOP!][!/*
*/!][!/*


*/!][!VAR "controllerRefs"="''"!][!/*
*/!][!LOOP "CanIfCtrlDrvCfg/*"!][!/*
   */!][!LOOP "CanIfCtrlCfg/*"!][!/*
      */!][!ASSERT "as:ref(CanIfCtrlCanCtrlRef)/CanControllerActivation = 'true'"!]CAN Controller [!"as:name(as:ref(CanIfCtrlCanCtrlRef))"!] (referenced by [!"as:name(.)"!]) needs to be activated for use with the CAN Interface.[!ENDASSERT!][!/*
   
      */!][!ASSERT "count(text:grep(text:split($controllerRefs), CanIfCtrlCanCtrlRef)) = 0"!]CAN Controller [!"as:name(as:ref(CanIfCtrlCanCtrlRef))"!] is referenced multiple times. Needs to be unique.[!ENDASSERT!][!/*
      */!][!VAR "controllerRefs" = "concat($controllerRefs, ' ', CanIfCtrlCanCtrlRef)"!][!/*
   */!][!ENDLOOP!][!/*
*/!][!ENDLOOP!][!/*


<!-- !LINKSTO CanIf.SWS_CanIf_00663,1 -->
*/!][!LOOP "CanIfInitCfg/*[1]/CanIfInitHohCfg/*"!][!/*
   */!][!LOOP "CanIfHrhCfg/*"!][!/*
      */!][!IF "(CanIfHrhSoftwareFilter = 'false') and
                (count(../../../../CanIfRxPduCfg/*[num:i(count(CanIfRxPduHrhIdRef/*[as:path(as:ref(.)) = as:path(node:current())])) > 0]) > 1)"!][!/*
         */!][!WARNING!]HrH [!"as:name(.)"!] is used by multiple Rx-PDUs but software filtering is disabled.[!ENDWARNING!][!/*
      */!][!ENDIF!][!/*
   */!][!ENDLOOP!][!/*
*/!][!ENDLOOP!][!/*


*/!][!LOOP "CanIfInitCfg/*[1]/CanIfInitHohCfg/*"!][!/*
   */!][!LOOP "CanIfHrhCfg/*"!][!/*
      */!][!ASSERT "as:path(as:ref(as:ref(CanIfHrhIdSymRef)/CanControllerRef)) = as:path(as:ref(as:ref(CanIfHrhCanCtrlIdRef)/CanIfCtrlCanCtrlRef))"!]HrH [!"as:name(.)"!] is assigned to a different CAN controller than its associated CAN Driver HrH.[!ENDASSERT!][!/*
      */!][!ASSERT "count(../*[CanIfHrhIdSymRef = node:current()/CanIfHrhIdSymRef]) = 1"!]HrH [!"as:name(.)"!] references a CAN Driver HrH that is referenced by another HrH.[!ENDASSERT!][!/*
   */!][!ENDLOOP!][!/*
*/!][!ENDLOOP!][!/*


*/!][!LOOP "CanIfInitCfg/*[1]/CanIfInitHohCfg/*"!][!/*
   */!][!LOOP "CanIfHthCfg/*"!][!/*
      */!][!ASSERT "as:path(as:ref(as:ref(CanIfHthIdSymRef)/CanControllerRef)) = as:path(as:ref(as:ref(CanIfHthCanCtrlIdRef)/CanIfCtrlCanCtrlRef))"!]HtH [!"as:name(.)"!] is assigned to a different CAN controller than its associated CAN Driver HtH.[!ENDASSERT!][!/*
      */!][!ASSERT "count(../*[CanIfHthIdSymRef = node:current()/CanIfHthIdSymRef]) = 1"!]HtH [!"as:name(.)"!] references a CAN Driver HtH that is referenced by another HtH.[!ENDASSERT!][!/*
   */!][!ENDLOOP!][!/*
*/!][!ENDLOOP!][!/*



*/!][!VAR "ecucRefList"="concat(text:join(CanIfInitCfg/*[1]/CanIfRxPduCfg/*/CanIfRxPduRef), ' ', text:join(CanIfInitCfg/*[1]/CanIfTxPduCfg/*/CanIfTxPduRef))"!][!/*
*/!][!LOOP "text:split($ecucRefList)"!][!/*
   */!][!ASSERT "text:uniq(text:split($ecucRefList), .)"!]Global PDU [!"."!] is referenced more than once[!ENDASSERT!][!/*
*/!][!ENDLOOP!][!/*


*/!][!IF "as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfMultiCoreSupport = 'true'"!][!/*
   */!][!VAR "TxPduPartition" = "''"!][!/*
*/!][!ENDIF!][!/*

*/!][!LOOP "CanIfInitCfg/*[1]/CanIfTxPduCfg/*"!][!/*
   */!][!IF "CanIfTxPduCanIdType = 'STANDARD_CAN'"!][!/*
      */!][!ASSERT "node:value(as:ref(as:ref(as:ref(CanIfTxPduBufferRef)/CanIfBufferHthRef/*[1])/CanIfHthIdSymRef)/CanIdType) != 'EXTENDED'"!]
      Tx-PDU [!"as:name(.)"!] uses standard identifiers but is associated to an HtH that is configured for extended identifiers.[!ENDASSERT!][!/*
   */!][!ENDIF!][!/*
   */!][!IF "CanIfTxPduCanIdType = 'STANDARD_FD_CAN'"!][!/*
      */!][!ASSERT "node:value(as:ref(as:ref(as:ref(CanIfTxPduBufferRef)/CanIfBufferHthRef/*[1])/CanIfHthIdSymRef)/CanIdType) != 'EXTENDED'"!]
      Tx-PDU [!"as:name(.)"!] uses standard identifiers but is associated to an HtH that is configured for extended identifiers.[!ENDASSERT!][!/*
   */!][!ENDIF!][!/*
   */!][!IF "CanIfTxPduCanIdType = 'EXTENDED_CAN'"!][!/*
      */!][!ASSERT "node:value(as:ref(as:ref(as:ref(CanIfTxPduBufferRef)/CanIfBufferHthRef/*[1])/CanIfHthIdSymRef)/CanIdType) != 'STANDARD'"!]
      Tx-PDU [!"as:name(.)"!] uses extended identifiers but is associated to an HtH that is configured for standard identifiers.[!ENDASSERT!][!/*
   */!][!ENDIF!][!/*
   */!][!IF "CanIfTxPduCanIdType = 'EXTENDED_FD_CAN'"!][!/*
      */!][!ASSERT "node:value(as:ref(as:ref(as:ref(CanIfTxPduBufferRef)/CanIfBufferHthRef/*[1])/CanIfHthIdSymRef)/CanIdType) != 'STANDARD'"!]
      Tx-PDU [!"as:name(.)"!] uses extended identifiers but is associated to an HtH that is configured for standard identifiers.[!ENDASSERT!][!/*
   */!][!ENDIF!][!/*

   */!][!IF "as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfMultiCoreSupport = 'true'"!][!/*
     */!][!IF "node:exists(as:ref(as:ref(as:ref(as:ref(CanIfTxPduBufferRef)/CanIfBufferHthRef/*[1])/CanIfHthCanCtrlIdRef)/CanIfCtrlCanCtrlRef)/CanControllerEcucPartitionRef)"!][!/*
       */!][!VAR "PduPartition" = "''"!][!/*

       */!][!ASSERT "node:exists(as:ref(CanIfTxPduRef)/EcucPduDedicatedPartition/*[as:name(as:ref(./EcucPduDedicatedPartitionBswModuleRef)) = 'CanIf']) or
                     node:exists(as:ref(CanIfTxPduRef)/EcucPduDefaultPartitionRef)"!]
       Controller [!"as:name(as:ref(as:ref(as:ref(as:ref(CanIfTxPduBufferRef)/CanIfBufferHthRef/*[1])/CanIfHthCanCtrlIdRef)/CanIfCtrlCanCtrlRef))"!] refers an EcucPartition (via CanControllerEcucPartitionRef), Tx-PDU [!"as:name(.)"!] must refer the same EcucPartition using EcucPduDedicatedPartition or EcucPduDefaultPartitionRef.[!ENDASSERT!][!/*

       */!][!IF "node:exists(as:ref(CanIfTxPduRef)/EcucPduDedicatedPartition/*[as:name(as:ref(./EcucPduDedicatedPartitionBswModuleRef)) = 'CanIf'])"!][!/*
         <!-- !LINKSTO CanIf.EB.Multicore.CtrlDedicatedPartitionRef,1 -->
         */!][!ASSERT "as:path(as:ref(as:ref(CanIfTxPduRef)/EcucPduDedicatedPartition/*[as:name(as:ref(./EcucPduDedicatedPartitionBswModuleRef)) = 'CanIf']/EcucPduDedicatedPartitionRef)) = 
                   as:path(as:ref(as:ref(as:ref(as:ref(as:ref(CanIfTxPduBufferRef)/CanIfBufferHthRef/*[1])/CanIfHthCanCtrlIdRef)/CanIfCtrlCanCtrlRef)/CanControllerEcucPartitionRef))"!]
         Tx-PDU [!"as:name(.)"!] must refer the same EcucPartition (via EcucPduDedicatedPartitionRef) as its corresponding controller [!"as:name(as:ref(as:ref(as:ref(as:ref(CanIfTxPduBufferRef)/CanIfBufferHthRef/*[1])/CanIfHthCanCtrlIdRef)/CanIfCtrlCanCtrlRef))"!].[!ENDASSERT!][!/*
       */!][!ELSE!][!/*
        <!-- !LINKSTO CanIf.EB.Multicore.CtrlDefaultPartitionRef,1 -->
        */!][!ASSERT "as:path(as:ref(as:ref(CanIfTxPduRef)/EcucPduDefaultPartitionRef)) = 
                      as:path(as:ref(as:ref(as:ref(as:ref(as:ref(CanIfTxPduBufferRef)/CanIfBufferHthRef/*[1])/CanIfHthCanCtrlIdRef)/CanIfCtrlCanCtrlRef)/CanControllerEcucPartitionRef))"!]
        Tx-PDU [!"as:name(.)"!] must refer the same EcucPartition (via EcucPduDefaultPartitionRef or EcucPduDedicatedPartitionRef) as its corresponding controller [!"as:name(as:ref(as:ref(as:ref(as:ref(CanIfTxPduBufferRef)/CanIfBufferHthRef/*[1])/CanIfHthCanCtrlIdRef)/CanIfCtrlCanCtrlRef))"!].[!ENDASSERT!][!/*
       */!][!ENDIF!][!/*

       */!][!IF "node:exists(as:modconf('J1939Nm')[1]/J1939NmConfigSet/*[1]/J1939NmChannel/*[J1939NmTxPdu/J1939NmTxPduRef = node:current()/CanIfTxPduRef])"!][!/*

         */!][!ASSERT "node:exists(as:ref(CanIfTxPduRef)/EcucPduDedicatedPartition/*[as:name(node:ref(./EcucPduDedicatedPartitionBswModuleRef)) = 'J1939Nm']) or
                       node:exists(as:ref(CanIfTxPduRef)/EcucPduDefaultPartitionRef)"!]
         If CanIfMultiCoreSupport is enabled, Tx J1939Nm PDU [!"as:name(as:modconf('J1939Nm')[1]/J1939NmConfigSet/*[1]/J1939NmChannel/*[J1939NmTxPdu/J1939NmTxPduRef = node:current()/CanIfTxPduRef]/J1939NmTxPdu)"!] must refer an EcucPartition (via EcucPduDedicatedPartition or EcucPduDefaultPartitionRef).[!ENDASSERT!][!/*

         */!][!IF "node:exists(as:ref(CanIfTxPduRef)/EcucPduDedicatedPartition/*[as:name(node:ref(./EcucPduDedicatedPartitionBswModuleRef)) = 'J1939Nm'])"!][!/*
           */!][!IF "$TxPduPartition = ''"!][!/*
             */!][!VAR "TxPduPartition" = "as:path(as:ref(as:ref(CanIfTxPduRef)/EcucPduDedicatedPartition/*[as:name(node:ref(./EcucPduDedicatedPartitionBswModuleRef)) = 'J1939Nm']/EcucPduDedicatedPartitionRef))"!][!/*
           */!][!ELSE!][!/*
             <!-- !LINKSTO CanIf.EB.Multicore.J1939DedicatedPartitionRef,1 -->
             */!][!ASSERT "$TxPduPartition = as:path(as:ref(as:ref(CanIfTxPduRef)/EcucPduDedicatedPartition/*[as:name(node:ref(./EcucPduDedicatedPartitionBswModuleRef)) = 'J1939Nm']/EcucPduDedicatedPartitionRef))"!]
             All J1939Nm PDUs must refer the same partition as the entire J1939 stack.[!ENDASSERT!][!/*
           */!][!ENDIF!][!/*
         */!][!ELSE!][!/*
           */!][!IF "$TxPduPartition = ''"!][!/*
             */!][!VAR "TxPduPartition" = "as:path(as:ref(as:ref(CanIfTxPduRef)/EcucPduDefaultPartitionRef))"!][!/*
           */!][!ELSE!][!/*
             <!-- !LINKSTO CanIf.EB.Multicore.J1939DefaultPartitionRef,1 -->
             */!][!ASSERT "string($TxPduPartition) = as:ref(as:ref(CanIfTxPduRef)/EcucPduDefaultPartitionRef)"!]
             All J1939Nm PDUs must refer the same partition as the entire J1939 stack.[!ENDASSERT!][!/*
           */!][!ENDIF!][!/*
         */!][!ENDIF!][!/*

       */!][!ENDIF!][!/*

       */!][!IF "node:exists(as:modconf('J1939Tp')[1]/J1939TpConfiguration/*[1]/J1939TpTxChannel/*[J1939TpTxCmNPdu/J1939TpTxCmNPduRef = node:current()/CanIfTxPduRef]) or
                 node:exists(as:modconf('J1939Tp')[1]/J1939TpConfiguration/*[1]/J1939TpTxChannel/*[J1939TpTxDtNPdu/J1939TpTxDtNPduRef = node:current()/CanIfTxPduRef]) or
                 node:exists(as:modconf('J1939Tp')[1]/J1939TpConfiguration/*[1]/J1939TpTxChannel/*/J1939TpTxPg/*[J1939TpTxDirectNPdu/J1939TpTxDirectNPduRef = node:current()/CanIfTxPduRef]) or 
                 node:exists(as:modconf('J1939Tp')[1]/J1939TpConfiguration/*[1]/J1939TpRxChannel/*[J1939TpTxFcNPdu/J1939TpTxFcNPduRef = node:current()/CanIfTxPduRef])"!][!/*

         */!][!ASSERT "node:exists(as:ref(CanIfTxPduRef)/EcucPduDedicatedPartition/*[as:name(node:ref(./EcucPduDedicatedPartitionBswModuleRef)) = 'J1939Tp']) or
                       node:exists(as:ref(CanIfTxPduRef)/EcucPduDefaultPartitionRef)"!]
         If CanIfMultiCoreSupport is enabled, Tx J1939Tp PDU must refer an EcucPartition (via EcucPduDedicatedPartition or EcucPduDefaultPartitionRef).[!ENDASSERT!][!/*

         */!][!IF "node:exists(as:ref(CanIfTxPduRef)/EcucPduDedicatedPartition/*[as:name(node:ref(./EcucPduDedicatedPartitionBswModuleRef)) = 'J1939Tp'])"!][!/*
           */!][!IF "$TxPduPartition = ''"!][!/*
             */!][!VAR "TxPduPartition" = "as:path(as:ref(as:ref(CanIfTxPduRef)/EcucPduDedicatedPartition/*[as:name(node:ref(./EcucPduDedicatedPartitionBswModuleRef)) = 'J1939Tp']/EcucPduDedicatedPartitionRef))"!][!/*
           */!][!ELSE!][!/*
             <!-- !LINKSTO CanIf.EB.Multicore.J1939DedicatedPartitionRef,1 -->
             */!][!ASSERT "$TxPduPartition = as:path(as:ref(as:ref(CanIfTxPduRef)/EcucPduDedicatedPartition/*[as:name(node:ref(./EcucPduDedicatedPartitionBswModuleRef)) = 'J1939Tp']/EcucPduDedicatedPartitionRef))"!]
             All J1939Tp PDUs must refer the same partition as the entire J1939 stack.[!ENDASSERT!][!/*
           */!][!ENDIF!][!/*

         */!][!ELSE!][!/*
           */!][!IF "$TxPduPartition = ''"!][!/*
             */!][!VAR "TxPduPartition" = "as:path(as:ref(as:ref(CanIfTxPduRef)/EcucPduDefaultPartitionRef))"!][!/*
           */!][!ELSE!][!/*
             <!-- !LINKSTO CanIf.EB.Multicore.J1939DefaultPartitionRef,1 -->
             */!][!ASSERT "$TxPduPartition = as:path(as:ref(as:ref(CanIfTxPduRef)/EcucPduDefaultPartitionRef))"!]
             All J1939Tp PDUs must refer the same partition as the entire J1939 stack.[!ENDASSERT!][!/*
           */!][!ENDIF!][!/*
         */!][!ENDIF!][!/*
       */!][!ENDIF!][!/*

     */!][!ENDIF!][!/*
   */!][!ENDIF!][!/*
*/!][!ENDLOOP!][!/*

*/!][!IF "as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfMultiCoreSupport = 'true'"!][!/*
   */!][!VAR "j1939PduPartition" = "''"!][!/*
   */!][!LOOP "CanIfInitCfg/*[1]/CanIfRxPduCfg/*"!][!/*
      */!][!VAR "currentRxPduName" = "as:name(.)"!][!/*
      */!][!VAR "pduPartition" = "''"!][!/*

       */!][!IF "node:exists(as:ref(CanIfRxPduRef)/EcucPduDedicatedPartition/*[as:name(node:ref(./EcucPduDedicatedPartitionBswModuleRef)) = 'CanIf'])"!][!/*
         */!][!VAR "pduPartition" = "as:path(as:ref(as:ref(CanIfRxPduRef)/EcucPduDedicatedPartition/*[as:name(node:ref(./EcucPduDedicatedPartitionBswModuleRef)) = 'CanIf']/EcucPduDedicatedPartitionRef))"!][!/*
       */!][!ELSEIF "node:exists(as:ref(CanIfRxPduRef)/EcucPduDefaultPartitionRef)"!][!/*
         */!][!VAR "pduPartition"="as:path(as:ref(as:ref(CanIfRxPduRef)/EcucPduDefaultPartitionRef))"!][!/*
       */!][!ENDIF!][!/*

         */!][!LOOP "CanIfRxPduHrhIdRef/*"!][!/*
           */!][!IF "node:exists(as:ref(as:ref(as:ref(.)/CanIfHrhCanCtrlIdRef)/CanIfCtrlCanCtrlRef)/CanControllerEcucPartitionRef)"!][!/*
             <!-- !LINKSTO CanIf.EB.Multicore.CtrlDedicatedPartitionRef,1 -->
             <!-- !LINKSTO CanIf.EB.Multicore.CtrlDefaultPartitionRef,1 -->
             */!][!ASSERT "$pduPartition != ''"!]
             Controller [!"as:name(as:ref(as:ref(as:ref(.)/CanIfHrhCanCtrlIdRef)/CanIfCtrlCanCtrlRef))"!] refers an EcucPartition (via CanControllerEcucPartitionRef), Rx-PDU [!"$currentRxPduName"!] must refer the same EcucPartition using EcucPduDedicatedPartition or EcucPduDefaultPartitionRef.[!ENDASSERT!][!/*

             */!][!ASSERT "$pduPartition = as:path(as:ref(as:ref(as:ref(as:ref(.)/CanIfHrhCanCtrlIdRef)/CanIfCtrlCanCtrlRef)/CanControllerEcucPartitionRef))"!]
             Rx-PDU [!"$currentRxPduName"!] must refer the same EcucPartition (via EcucPduDefaultPartitionRef or EcucPduDedicatedPartitionRef) as its corresponding controller [!"as:name(as:ref(as:ref(as:ref(.)/CanIfHrhCanCtrlIdRef)/CanIfCtrlCanCtrlRef))"!].[!ENDASSERT!][!/*
           */!][!ENDIF!][!/*
         */!][!ENDLOOP!][!/*

     */!][!IF "node:exists(as:modconf('J1939Nm')[1]/J1939NmConfigSet/*[1]/J1939NmChannel/*[J1939NmRxPdu/J1939NmRxPduRef = node:current()/CanIfRxPduRef])"!][!/*

       */!][!ASSERT "node:exists(as:ref(CanIfRxPduRef)/EcucPduDedicatedPartition/*[as:name(node:ref(./EcucPduDedicatedPartitionBswModuleRef)) = 'J1939Nm']) or
                     node:exists(as:ref(CanIfRxPduRef)/EcucPduDefaultPartitionRef)"!]
        If CanIfMultiCoreSupport is enabled, Rx J1939Nm PDU must refer an EcucPartition (via EcucPduDedicatedPartition or EcucPduDefaultPartitionRef).[!ENDASSERT!][!/*

       */!][!IF "node:exists(as:ref(CanIfRxPduRef)/EcucPduDedicatedPartition/*[as:name(node:ref(./EcucPduDedicatedPartitionBswModuleRef)) = 'J1939Nm'])"!][!/*
         */!][!IF "$j1939PduPartition = ''"!][!/*
           */!][!VAR "j1939PduPartition" = "as:path(as:ref(as:ref(CanIfRxPduRef)/EcucPduDedicatedPartition/*[as:name(node:ref(./EcucPduDedicatedPartitionBswModuleRef)) = 'J1939Nm']/EcucPduDedicatedPartitionRef))"!][!/*
         */!][!ELSE!][!/*
           <!-- !LINKSTO CanIf.EB.Multicore.J1939DedicatedPartitionRef,1 -->
           */!][!ASSERT "$j1939PduPartition = as:path(as:ref(as:ref(CanIfRxPduRef)/EcucPduDedicatedPartition/*[as:name(node:ref(./EcucPduDedicatedPartitionBswModuleRef)) = 'J1939Nm']/EcucPduDedicatedPartitionRef))"!]
           All J1939Nm PDUs must refer the same partition as the entire J1939 stack.[!ENDASSERT!][!/*
         */!][!ENDIF!][!/*
       */!][!ELSE!][!/*
         */!][!IF "$j1939PduPartition = ''"!][!/*
           */!][!VAR "j1939PduPartition" = "as:path(as:ref(as:ref(CanIfRxPduRef)/EcucPduDefaultPartitionRef))"!][!/*
         */!][!ELSE!][!/*
           <!-- !LINKSTO CanIf.EB.Multicore.J1939DefaultPartitionRef,1 -->
           */!][!ASSERT "$j1939PduPartition = as:path(as:ref(as:ref(CanIfRxPduRef)/EcucPduDefaultPartitionRef))"!]
           All J1939Nm PDUs must refer the same partition as the entire J1939 stack.[!ENDASSERT!][!/*
         */!][!ENDIF!][!/*
       */!][!ENDIF!][!/*
     */!][!ENDIF!][!/*

   */!][!IF "node:exists(as:modconf('J1939Tp')[1]/J1939TpConfiguration/*[1]/J1939TpRxChannel/*[J1939TpRxCmNPdu/J1939TpRxCmNPduRef = node:current()/CanIfRxPduRef]) or
             node:exists(as:modconf('J1939Tp')[1]/J1939TpConfiguration/*[1]/J1939TpRxChannel/*[J1939TpRxDtNPdu/J1939TpRxDtNPduRef = node:current()/CanIfRxPduRef]) or
             node:exists(as:modconf('J1939Tp')[1]/J1939TpConfiguration/*[1]/J1939TpRxChannel/*/J1939TpRxPg/*[J1939TpRxDirectNPdu/J1939TpRxDirectNPduRef = node:current()/CanIfRxPduRef]) or 
             node:exists(as:modconf('J1939Tp')[1]/J1939TpConfiguration/*[1]/J1939TpTxChannel/*[J1939TpRxFcNPdu/J1939TpRxFcNPduRef = node:current()/CanIfRxPduRef])"!][!/*

     */!][!ASSERT "node:exists(as:ref(CanIfRxPduRef)/EcucPduDedicatedPartition/*[as:name(node:ref(./EcucPduDedicatedPartitionBswModuleRef)) = 'J1939Tp']) or
                   node:exists(as:ref(CanIfRxPduRef)/EcucPduDefaultPartitionRef)"!]
         If CanIfMultiCoreSupport is enabled, Rx J1939Tp PDU must refer an EcucPartition (via EcucPduDedicatedPartition or EcucPduDefaultPartitionRef).[!ENDASSERT!][!/*

     */!][!IF "node:exists(as:ref(CanIfRxPduRef)/EcucPduDedicatedPartition/*[as:name(node:ref(./EcucPduDedicatedPartitionBswModuleRef)) = 'J1939Tp'])"!][!/*
       */!][!IF "$j1939PduPartition = ''"!][!/*
         */!][!VAR "j1939PduPartition" = "as:path(as:ref(as:ref(CanIfRxPduRef)/EcucPduDedicatedPartition/*[as:name(node:ref(./EcucPduDedicatedPartitionBswModuleRef)) = 'J1939Tp']/EcucPduDedicatedPartitionRef))"!][!/*
       */!][!ELSE!][!/*
         <!-- !LINKSTO CanIf.EB.Multicore.J1939DedicatedPartitionRef,1 -->
         */!][!ASSERT "$j1939PduPartition = as:path(as:ref(as:ref(CanIfRxPduRef)/EcucPduDedicatedPartition/*[as:name(node:ref(./EcucPduDedicatedPartitionBswModuleRef)) = 'J1939Tp']/EcucPduDedicatedPartitionRef))"!]
         All J1939Tp PDUs must refer the same partition as the entire J1939 stack.[!ENDASSERT!][!/*
       */!][!ENDIF!][!/*

     */!][!ELSE!][!/*
       */!][!IF "$j1939PduPartition = ''"!][!/*
         */!][!VAR "j1939PduPartition" = "as:path(as:ref(as:ref(CanIfRxPduRef)/EcucPduDefaultPartitionRef))"!][!/*
       */!][!ELSE!][!/*
         <!-- !LINKSTO CanIf.EB.Multicore.J1939DefaultPartitionRef,1 -->
         */!][!ASSERT "$j1939PduPartition = as:path(as:ref(as:ref(CanIfRxPduRef)/EcucPduDefaultPartitionRef))"!]
         All J1939Tp PDUs must refer the same partition as the entire J1939 stack.[!ENDASSERT!][!/*
       */!][!ENDIF!][!/*
     */!][!ENDIF!][!/*
   */!][!ENDIF!][!/*

   */!][!ENDLOOP!][!/*

   */!][!IF "as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfDecoupledProcessingSupport = 'true'"!][!/*

     */!][!LOOP "as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfRxProcessing/*"!][!/*
       */!][!LOOP "CanIfRxPduProcessingRef/*"!][!/*
         */!][!VAR "PduPartition" = "''"!][!/*
         */!][!IF "node:exists(as:ref(as:ref(.)/CanIfRxPduRef)/EcucPduDedicatedPartition/*[as:name(as:ref(./EcucPduDedicatedPartitionBswModuleRef)) = 'CanIf'])"!][!/*
           */!][!VAR "PduPartition" = "as:path(as:ref(as:ref(as:ref(.)/CanIfRxPduRef)/EcucPduDedicatedPartition/*[as:name(as:ref(./EcucPduDedicatedPartitionBswModuleRef)) = 'CanIf']/EcucPduDedicatedPartitionRef))"!][!/*
         */!][!ELSE!][!/*
           */!][!VAR "PduPartition" = "as:path(as:ref(as:ref(as:ref(.)/CanIfRxPduRef)/EcucPduDefaultPartitionRef))"!][!/*
         */!][!ENDIF!][!/*
         <!-- !LINKSTO CanIf.EB.Multicore.CanIfRxProcessing.SamePartitionOnMainFunction,1 -->
         */!][!ASSERT "$PduPartition = as:path(as:ref(../../CanIfPartitionRef))"!]
         Rx PDU [!"as:name(as:ref(.))"!] must refer the same partition as the CanIfPartitionRef of [!"as:name(../..)"!].[!ENDASSERT!][!/*
       */!][!ENDLOOP!][!/*
     */!][!ENDLOOP!][!/*

     */!][!LOOP "as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfTxProcessing/*"!][!/*
       */!][!LOOP "CanIfTxPduProcessingRef/*"!][!/*
         */!][!VAR "PduPartition" = "''"!][!/*
         */!][!IF "node:exists(as:ref(as:ref(.)/CanIfTxPduRef)/EcucPduDedicatedPartition/*[as:name(as:ref(./EcucPduDedicatedPartitionBswModuleRef)) = 'CanIf'])"!][!/*
           */!][!VAR "PduPartition" = "as:path(as:ref(as:ref(as:ref(.)/CanIfTxPduRef)/EcucPduDedicatedPartition/*[as:name(as:ref(./EcucPduDedicatedPartitionBswModuleRef)) = 'CanIf']/EcucPduDedicatedPartitionRef))"!][!/*
         */!][!ELSE!][!/*
           */!][!VAR "PduPartition" = "as:path(as:ref(as:ref(as:ref(.)/CanIfTxPduRef)/EcucPduDefaultPartitionRef))"!][!/*
         */!][!ENDIF!][!/*
         <!-- !LINKSTO CanIf.EB.Multicore.CanIfTxProcessing.SamePartitionOnMainFunction,1 -->
         */!][!ASSERT "$PduPartition = as:path(as:ref(../../CanIfPartitionRef))"!]
         Tx PDU [!"as:name(as:ref(.))"!] must refer the same partition as the CanIfPartitionRef of [!"as:name(../..)"!].[!ENDASSERT!][!/*
       */!][!ENDLOOP!][!/*
     */!][!ENDLOOP!][!/*

   */!][!ENDIF!][!/*

*/!][!ENDIF!][!/*

*/!][!IF "node:exists(as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfPublicMaxRxBuffer) and (number($currRxBufferPos) > as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfPublicMaxRxBuffer)"!][!/*
  */!][!ERROR!]The actually required message buffer required for Pdus which support CanIf_ReadRxPduData() ([!"num:i($currRxBufferPos)"!]) must not exceed CanIfPublicMaxRxBuffer ([!"as:modconf('CanIf')[1]/CanIfPublicCfg/CanIfPublicMaxRxBuffer"!]).[!ENDERROR!][!/*
*/!][!ENDIF!][!/*

*** End of file ***
*/!][!ENDIF!][!/*
*/!][!//
