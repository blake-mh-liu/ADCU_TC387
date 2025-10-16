[!/*****************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2020)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME    : Eth_17_GEthMacV2_PBcfg.c                                    **
**                                                                            **
**  VERSION     : 6.0.0                                                       **
**                                                                            **
**  DATE        : 2020-10-19                                                  **
**                                                                            **
**  BSW MODULE DECRIPTION : NA                                                **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR      : DL-AUTOSAR-Engineering                                      **
**                                                                            **
**  VENDOR      : Infineon Technologies                                       **
**                                                                            **
**                                                                            **
**  TRACEABILITY : [cover parentID]                                           **
**                                                                            **
**  DESCRIPTION  : Code template source file for Eth Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Eth Driver, AUTOSAR Release 4.4.0     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
******************************************************************************/!]
/******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2020)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Eth_17_GEthMacV2_PBCfg.c                                      **
**                                                                            **
**  VERSION   : 6.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]     !!!IGNORE-LINE!!!                    **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]       !!!IGNORE-LINE!!!                    **
**                                                                            **
**  BSW MODULE DECRIPTION : NA                                                **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Eth configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Eth Driver, AUTOSAR Release 4.4.0     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
[!/*[cover parentID={8904D64D-924F-4eef-B2FA-E9084BFC69E3}][/cover]*/!][!//
[!/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}][/cover]*/!][!//
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
[!INDENT "0"!][!//
/* Include ETH Module File */
#include "Eth_17_GEthMacV2.h"
[!NOCODE!]
[!INCLUDE "Eth_17_GEthMacV2.m"!][!//
[!ENDNOCODE!]
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
[!/*[cover parentID={FF30A463-CDA3-4b49-A745-A6CD2F3F9B63}][/cover]*/!][!//
[!/*[cover parentID={6EE6E933-ABA0-4c6e-9AF0-4A1BB260FF63}][/cover] */!][!//
[!/*[cover parentID={4579FE20-92DA-4848-93DB-7AD4FD35DD50}][/cover]*/!][!//
/*
  Note: Elektrobit Automotive GmbH modified the original code provided
        by the third party supplier. The modification is provided for
        convenience.
        Please use the modification on your discretion and account, or
        use the unmodified files provided with this distribution. 
  Please see for the reasons in the file ImportantNotes.txt for tag

ASCINFINEON-1043 Update PostBuild generation 
ASCINFINEON-983 - Autosar specification deviation in ETH driver. Removed v:lst from Eth.xdm.
*/
[!NOCODE!][!//
[!IF "not(node:exists(as:modconf('Mcu')[1]))"!][!//
  [!ERROR!][!//
    Ethernet needs Mcu module
  [!ENDERROR!][!//
[!ENDIF!][!//
[!IF "not(node:exists(as:modconf('ResourceM')[1]))"!][!//
  [!ERROR!][!//
    Ethernet needs ResourceM module
  [!ENDERROR!][!//
[!ENDIF!][!//
[!//
[!ENDNOCODE!][!//
[!//
[!AUTOSPACING!][!//
[!SELECT "as:modconf('Eth')[1]"!][!//
  [!NOCODE!][!//
  [!CALL "ETH_GenerateModuleMap", "Module" = "'ETH'"!][!//
  [!CALL "ETH_GetMasterCoreID"!][!//
  [!VAR "MaxControllers"= "ecu:get('Eth.EthAvaliableNodes')"!][!//
  [!/*************Error check for same MACAddress************/!][!//
  [!VAR "MaxControllersConfigured"= "num:i(count(EthConfigSet/EthCtrlConfig/*))"!][!//
  [!IF "$MaxControllersConfigured > num:i(1)"!][!//
    [!FOR "ControllerId" = "num:i(0)" TO "num:i($MaxControllers)-num:i(1)"!][!//
      [!SELECT "EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]"!][!//
        [!IF "num:i($ControllerId) = num:i(0)"!][!//
          [!VAR "MacAddress0" = "node:value(./EthCtrlPhyAddress/*[1])"!][!//
        [!ENDIF!][!//
        [!IF "num:i($ControllerId) = num:i(1)"!][!//
          [!VAR "MacAddress1" = "node:value(./EthCtrlPhyAddress/*[1])"!][!//
        [!ENDIF!][!//
      [!ENDSELECT!][!//
    [!ENDFOR!][!//
    [!IF "$MacAddress0 = $MacAddress1"!][!//
      [!ERROR!][!//
        Error : MACAddress configured in parameter EthCtrlPhyAddress must be unique for each ETH controller.
      [!ENDERROR!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//

  [!/*************Macro for Config Shaper detection************/!][!//
  [!NOCODE!][!//
  [!MACRO "Eth_ShaperDet", "PredecessorRef" = "", "RetVal" = ""!][!//
    [!VAR "PredString" = "$PredecessorRef"!][!//
    [!VAR "LoopCount" = "count(EthCtrlConfigEgress/EthCtrlConfigShaper/*)"!][!//
    [!FOR "Count1" = "num:i(1)" TO "num:i($LoopCount)"!][!//
      [!VAR "StringSearch" = "node:name(EthCtrlConfigEgress/EthCtrlConfigShaper/*[num:i($Count1)])"!][!//
      [!IF "$StringSearch = $PredString"!][!//
        [!VAR "RetVal" = "num:i(1)"!][!//
        [!BREAK!][!//
      [!ENDIF!][!//
    [!ENDFOR!][!//
  [!ENDMACRO!][!//
  [!ENDNOCODE!][!//

  [!/***********************************SORTING MACRO******************************/!][!//
  [!NOCODE!][!//
  [!MACRO "Sorting","SortArray" = "","VItem" = "","VTotalNum" = "",,"VDrctn" = ""!][!//
    [!VAR "VTempStr1" = "''"!][!//
    [!VAR "VTempStr2" = "''"!][!//
    [!VAR "VTempStr1_1" = "''"!][!//
    [!VAR "VTempStr2_2" = "''"!][!//
    [!VAR "Vcount1" = "num:i(0)"!][!//
    [!VAR "Vcount2" = "num:i(0)"!][!//
    [!VAR "VTempInt1" = "num:i(0)"!][!//
    [!VAR "VTempInt2" = "num:i(0)"!][!//
    [!VAR "VTempReplceStr1" = "'String1'"!][!//
    [!VAR "VTempReplceStr2" = "'String2'"!][!//
    [!FOR "Vcount1" = "num:i(1)" TO "num:i($VTotalNum - 1)"!][!//
      [!FOR "Vcount2" = "num:i($Vcount1 + 1)" TO "num:i($VTotalNum)"!][!//
        [!VAR "VTempStr1" = "text:split($SortArray,'@')[num:i($Vcount1)]"!][!//
        [!VAR "VTempStr2" = "text:split($SortArray,'@')[num:i($Vcount2)]"!][!//
        [!VAR "VTempStr1_1" = "text:split($VTempStr1,',')[num:i($VItem)]"!][!//
        [!VAR "VTempStr2_2" = "text:split($VTempStr2,',')[num:i($VItem)]"!][!//
        [!VAR "VTempInt1" = "num:i(number($VTempStr1_1))"!][!//
        [!VAR "VTempInt2" = "num:i(number($VTempStr2_2))"!][!//
        [!IF "$VDrctn > num:i(0)"!][!//
          [!IF "$VTempInt1 > $VTempInt2"!][!//
            [!VAR "SortArray" = "text:replace($SortArray,$VTempStr1,$VTempReplceStr1)"!][!//
            [!VAR "SortArray" = "text:replace($SortArray,$VTempStr2,$VTempReplceStr2)"!][!//
            [!VAR "SortArray" = "text:replace($SortArray,$VTempReplceStr2,$VTempStr1)"!][!//
            [!VAR "SortArray" = "text:replace($SortArray,$VTempReplceStr1,$VTempStr2)"!][!//
          [!ENDIF!][!//
        [!ELSE!][!//
          [!IF "$VTempInt1 < $VTempInt2"!][!//
            [!VAR "SortArray" = "text:replace($SortArray,$VTempStr1,$VTempReplceStr1)"!][!//
            [!VAR "SortArray" = "text:replace($SortArray,$VTempStr2,$VTempReplceStr2)"!][!//
            [!VAR "SortArray" = "text:replace($SortArray,$VTempReplceStr2,$VTempStr1)"!][!//
            [!VAR "SortArray" = "text:replace($SortArray,$VTempReplceStr1,$VTempStr2)"!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDFOR!][!//
    [!ENDFOR!][!//
  [!ENDMACRO!][!//
  [!ENDNOCODE!][!//
  [!/******/!][!//

  [!/***********************************REPLACE MACRO******************************/!][!//
  [!NOCODE!][!//
  [!MACRO "ReplaceValue","ReplaceArray" = "","VPosition" = "","VReplaceVal" = ""!][!//
    [!VAR "VRplc1" = "''"!][!//
    [!VAR "VRplc2" = "''"!][!//
    [!VAR "VRplc1" = "substring($ReplaceArray,1,(num:i($VPosition)-1))"!][!//
    [!VAR "VRplc2" = "substring($ReplaceArray,(num:i($VPosition)+1))"!][!//
    [!VAR "ReplaceArray" = "concat($VRplc1,$VReplaceVal,$VRplc2)"!][!//
  [!ENDMACRO!][!//
  [!ENDNOCODE!][!//
  [!/******/!][!//

  [!/***********************************SUM MACRO******************************/!][!//
  [!NOCODE!][!//
  [!MACRO "SumElem","SumArray" = "","VNumElem" = "","SumVal" = ""!][!//
    [!VAR "VTempSum" = "num:i(0)"!][!//
    [!FOR "Vcount" = "num:i(1)" TO "num:i($VNumElem)"!][!//
      [!VAR "VElemVal" = "text:split($SumArray,' ')[num:i($Vcount)]"!][!//
      [!VAR "VTempSum" = "num:i($VTempSum) + num:i($VElemVal)"!][!//
    [!ENDFOR!][!//
    [!VAR "SumVal" = "num:i($VTempSum)"!][!//
  [!ENDMACRO!][!//
  [!ENDNOCODE!][!//
  [!/******/!][!//

  [!/*** Error check if Predecessor Order is continuous in Strict Priority ******/!][!//
  [!/*** Error check if Weight with value 0 is configured for WRR ***********/!][!//
  [!/*** Error check if DMA Weights are not configured for WSP and WRR  ******/!][!//
  [!FOR "ControllerId" = "num:i(0)" TO "num:i($MaxControllers)-num:i(1)"!][!//
    [!VAR "Count" = "''"!][!//
    [!SELECT "EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]/EthCtrlConfigEgress"!][!//
      [!LOOP "(EthCtrlConfigScheduler/*)"!][!//
        [!IF "node:value(./EthCtrlConfigSchedulerAlgorithm) = 'ETH_SCHEDULER_STRICT_PRIORITY'"!][!//
          [!VAR "PredecessorRange" = "num:i(count(EthCtrlConfigSchedulerPredecessor/*)) - num:i(1)"!][!//
          [!LOOP "(EthCtrlConfigSchedulerPredecessor/*)"!][!//
            [!VAR "Order" = "num:i(./EthCtrlConfigSchedulerPredecessorOrder)"!][!//
            [!IF "$Order > num:i($PredecessorRange)"!][!//
              [!ERROR!][!//
                Error : EthCtrlConfigSchedulerPredecessorOrder is not within the range [0,[!"num:i($PredecessorRange)"!]] for Strict Priority scheduling algorithm.
              [!ENDERROR!][!//
            [!ENDIF!][!//
            [!IF "contains($Count, $Order)"!][!//
              [!ERROR!][!//
                Error : EthCtrlConfigSchedulerPredecessorOrder is not unique for Strict Priority scheduling algorithm.
              [!ENDERROR!][!//
            [!ELSE!][!//
              [!VAR "Count" = "concat($Count,string($Order))"!][!//
            [!ENDIF!][!//
          [!ENDLOOP!][!//
        [!ELSE!][!//
          [!LOOP "(EthCtrlConfigSchedulerPredecessor/*)"!][!//
            [!VAR "Order" = "num:i(./EthCtrlConfigSchedulerPredecessorOrder)"!][!//
            [!IF "$Order = num:i(0)"!][!//
              [!ERROR!][!//
                Error : EthCtrlConfigSchedulerPredecessorOrder which corresponds to the weight cannot be 0 for Weighted Round Robin scheduling.
              [!ENDERROR!][!//
            [!ENDIF!][!//
          [!ENDLOOP!][!//
        [!ENDIF!][!//
      [!ENDLOOP!][!//
    [!ENDSELECT!][!//
    [!SELECT "EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]/EthCtrlConfigEgress/EthCtrlConfigDMAArbitration/*[1]"!][!//
        [!IF "node:value(./EthCtrlConfigDMAArbitrationAlgorithm) != 'ETH_DMA_ARBITRATION_FIXED_PRIORITY'"!][!//
          [!IF "not(node:exists(EthCtrlConfigDMAWeightAssignment/*))"!][!//
            [!ERROR!][!//
              Error : Weights for the DMA scheduler needs to be configured for the egress FIFOs in Weighted Round Robin or Weighted Strict Priority scheduling.
            [!ENDERROR!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDSELECT!][!//
  [!ENDFOR!][!//

  [!/*************Error check if FIFO order is continuous and Priority is assigned to IngressFifo************/!][!//
  [!FOR "ControllerId" = "num:i(0)" TO "num:i($MaxControllers)-num:i(1)"!][!//
    [!VAR "Count" = "num:i(0)"!][!//
    [!VAR "IngressFifoConfigured" = "num:i(0)"!][!//
    [!VAR "FifoIdx" = "num:i(0)"!][!//
    [!SELECT "EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]"!][!//
      [!VAR "EgressVal" = "node:isconsecutive(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*/EthCtrlConfigEgressFifoIdx,0)"!][!//
      [!IF "($EgressVal) = 'false'"!][!//
        [!ERROR!][!//
          Error : EthCtrlConfigEgressFifoIdx order is not continuous. EthCtrlConfigEgressFifoIdx order should be continuous and start from 0.
        [!ENDERROR!][!//
      [!ENDIF!][!//
      [!VAR "IngressVal" = "node:isconsecutive(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*/EthCtrlConfigIngressFifoIdx,0)"!][!//
      [!IF "($IngressVal) = 'false'"!][!//
        [!ERROR!][!//
          Error : EthCtrlConfigIngressFifoIdx order is not continuous. EthCtrlConfigIngressFifoIdx order should be continuous and start from 0.
        [!ENDERROR!][!//
      [!ENDIF!][!//
      [!VAR "IngressFifoConfigured" = "num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*))"!][!//
      [!IF "$IngressFifoConfigured > num:i(1)"!][!//
        [!FOR "IngressFifo" = "num:i(0)" TO "num:i($IngressFifoConfigured) - num:i(1)"!][!//
          [!VAR "FifoIdx" = "EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoIdx"!][!//
          [!IF "not(node:exists(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoPriorityAssignment/*))"!][!//
            [!ERROR!][!//
              Error : Priority not assigned to Ingress Fifo index [!"$FifoIdx"!]. If more than one FIFO is configured, priority assignment for all the FIFOs is mandatory.
            [!ENDERROR!][!//
          [!ENDIF!][!//
        [!ENDFOR!][!//
      [!ENDIF!][!//
    [!ENDSELECT!][!//
  [!ENDFOR!][!//

  [!/******* Error check for missing priority and valid reference************/!][!//
  [!FOR "ControllerId" = "num:i(0)" TO "num:i($MaxControllers)-num:i(1)"!][!//
  [!VAR "EFifoPriorityOrderString" ="''"!][!//
  [!VAR "EFifoPriorityCountString" ="''"!][!//
  [!VAR "IFifoPriorityOrderString" ="''"!][!//
  [!IF "node:exists(EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = $ControllerId])"!][!//
    [!SELECT "EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]"!][!//
      [!/****************Egress valid reference error**************/!][!//
      [!VAR "EgressFifoConfigured" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*))"!][!//
      [!IF "$EgressFifoConfigured > num:i(0)"!][!//
        [!VAR "SchedString" = "node:name(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1])"!][!//
        [!VAR "PredecessorMax" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*))"!][!//
        [!FOR "Predecessor" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
          [!VAR "RefVal" = "node:refvalid(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)"!][!//
          [!IF "$RefVal = 'false'"!][!//
            [!ERROR!][!//
              Select valid reference for EthCtrlConfigSchedulerPredecessorRef parameter for scheduling the Egress FIFO.
            [!ENDERROR!][!//
          [!ENDIF!][!//
          [!VAR "PredRefString" = "text:split(node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef),'/')[last()]"!][!//
          [!IF "$SchedString = $PredRefString"!][!//
            [!ERROR!][!//
              The parameter EthCtrlConfigSchedulerPredecessorRef cannot have a reference to scheduler, as only one scheduler is supported by the Ethernet driver. Remove the scheduler reference.
            [!ENDERROR!][!//
          [!ENDIF!][!//
        [!ENDFOR!][!//
      [!ENDIF!][!//
      [!/*************Missing priority and valid reference error************/!][!//
      [!VAR "IngressFifoConfigured" = "num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*))"!][!//
      [!IF "$IngressFifoConfigured > num:i(0)"!][!//
        [!FOR "IngressFifo" = "num:i(0)" TO "num:i($IngressFifoConfigured) - num:i(1)"!][!//
          [!VAR "IFifoPriorityCount" = "num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoPriorityAssignment/*))"!][!//
          [!IF "$IFifoPriorityCount != num:i(0)"!][!//
            [!FOR "Count" = "num:i(1)" TO "num:i($IFifoPriorityCount)"!][!//
              [!VAR "IngressPriority" = "EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoPriorityAssignment/*[num:i($Count)]"!][!//
              [!VAR "IFifoPriorityOrderString" = "string(concat($IFifoPriorityOrderString,$IngressPriority))"!][!//
            [!ENDFOR!][!//
          [!ELSE!][!//
            [!VAR "IFifoPriorityOrderString" = "string("01234567")"!][!//
          [!ENDIF!][!//
        [!ENDFOR!][!//
        [!FOR "Count" = "num:i(0)" TO "num:i(7)"!][!//
          [!VAR "BolVal" = "text:contains(string($IFifoPriorityOrderString),string($Count))"!][!//
          [!IF "$BolVal = 'false'"!][!//
            [!ERROR!][!//
              All the ingress priorities within the range [0,7] should be configured within the Ingress FIFOs. This is required by the GETHMAC IP hardware for routing of packets.
            [!ENDERROR!][!//
          [!ENDIF!][!//
        [!ENDFOR!][!//
        [!VAR "RefVal" = "node:refvalid(EthCtrlConfigIngress/EthCtrlConfigIngressUntaggedPktsFifoRef)"!][!//
        [!IF "$RefVal = 'false'"!][!//
          [!ERROR!][!//
            Select a valid reference for EthCtrlConfigIngressUntaggedPktsFifoRef parameter to route the untagged packets to the Ingress FIFO.
          [!ENDERROR!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDSELECT!][!//
  [!ENDIF!][!//
  [!ENDFOR!][!//

  [!/*************Error check if Config shaper is scheduled before normal scheduler************/!][!//
  [!FOR "ControllerId" = "num:i(0)" TO "num:i($MaxControllers) - num:i(1)"!][!//
    [!VAR "TempVal" = "num:i(0)"!][!//
    [!VAR "ShaperCnt" = "num:i(0)"!][!//
    [!SELECT "EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]"!][!//
    [!VAR "EgressFifoConfigured" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*))"!][!//
    [!IF "$EgressFifoConfigured > num:i(0)"!][!//
      [!VAR "ShaperMax" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigShaper/*))"!][!//
      [!IF "node:exists(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]) = 'true'"!][!//
        [!VAR "PredecessorMax" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*))"!][!//
        [!FOR "Predecessor" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
          [!VAR "PredecessorString" = "text:split(node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef),'/')[last()]"!][!//
          [!CALL "Eth_ShaperDet", "PredecessorRef" = "$PredecessorString", "RetVal" = "num:i(255)"!][!//
          [!IF "$RetVal = num:i(255)"!][!//
            [!VAR "EFifoId" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoIdx))"!][!//
          [!ELSE!][!//
            [!VAR "EFifoId" = "num:i(255)"!][!//
            [!VAR "ShaperCnt" = "num:i($ShaperCnt+num:i(1))"!][!//
          [!ENDIF!][!//
          [!FOR "Shaper" = "num:i(1)" TO "num:i($ShaperMax)"!][!//
            [!VAR "SFifoId" = "node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigShaper/*[num:i($Shaper)]/EthCtrlConfigShaperPredecessorFifoRef)/EthCtrlConfigEgressFifoIdx)"!][!//
            [!IF "$EFifoId = $SFifoId"!][!//
              [!ERROR!][!//
                Fifo index [!"$EFifoId"!] is configured in EthCtrlConfigShaper as well as in Config scheduler. EthCtrlConfigShaper needs to be configured in Config scheduler.
              [!ENDERROR!][!//
            [!ENDIF!][!//
          [!ENDFOR!][!//
        [!ENDFOR!][!//
        [!IF "$ShaperCnt = $PredecessorMax"!][!//
          [!ERROR!][!//
            EthCtrlConfigScheduler cannot have only EthCtrlConfigShaper scheduled. There should be atleast one egress FIFO without shaper configured for scheduling.
          [!ENDERROR!][!//
        [!ENDIF!][!//
        [!IF "node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerAlgorithm) = 'ETH_SCHEDULER_STRICT_PRIORITY'"!][!//
          [!VAR "TempVal" = "num:i(0)"!][!//
          [!FOR "Predecessor" = "num:i(0)" TO "num:i($PredecessorMax) - num:i(1)"!][!//
            [!VAR "PredecessorString" = "text:split(node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef),'/')[last()]"!][!//
            [!CALL "Eth_ShaperDet", "PredecessorRef" = "$PredecessorString", "RetVal" = "num:i(255)"!][!//
            [!IF "$RetVal = num:i(1)"!][!//
              [!VAR "TempVal" = "num:i(1)"!][!//
            [!ENDIF!][!//
            [!IF "$TempVal = num:i(1)"!][!//
              [!IF "$RetVal = num:i(255)"!][!//
                [!ERROR!][!//
                   EthCtrlConfigFifo [!"$PredecessorString"!] should be scheduled in EthCtrlConfigScheduler before EthCtrlConfigShaper.
                [!ENDERROR!][!//
              [!ENDIF!][!//
            [!ENDIF!][!//
          [!ENDFOR!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!ENDSELECT!][!//
  [!ENDFOR!][!//

  [!/*************Error check if configured MAC type and speed is not supported by the device************/!][!//
  [!FOR "ControllerId" = "num:i(0)" TO "num:i($MaxControllers)-num:i(1)"!][!//
    [!SELECT "EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]"!][!//
      [!IF "./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XGMII' and ./EthCtrlMacLayerSubType/*[1] = 'REDUCED'"!][!//
        [!VAR "PhyIntfFlag" = "(node:containsValue((ecu:list('Eth.EthPhyIntf')), 'RGMII'))"!][!//
        [!IF "$PhyIntfFlag = 'false'"!][!//
          [!ERROR!]
            Error : The configured MAC layer type/ subtype- RGMII for controller [!"./EthCtrlIdx"!] is not supported by the device.
          [!ENDERROR!]
        [!ENDIF!][!//
      [!ELSEIF "./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XMII' and ./EthCtrlMacLayerSubType/*[1] = 'REDUCED'"!][!//
        [!VAR "PhyIntfFlag" = "(node:containsValue((ecu:list('Eth.EthPhyIntf')), 'RMII'))"!][!//
        [!IF "$PhyIntfFlag = 'false'"!][!//
          [!ERROR!]
            Error : The configured MAC layer type/ subtype- RMII for controller [!"./EthCtrlIdx"!] is not supported by the device.
          [!ENDERROR!]
        [!ENDIF!][!//
      [!ELSEIF "./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XMII' and ./EthCtrlMacLayerSubType/*[1] = 'STANDARD'"!][!//
        [!VAR "PhyIntfFlag" = "(node:containsValue((ecu:list('Eth.EthPhyIntf')), 'MII'))"!][!//
        [!IF "$PhyIntfFlag = 'false'"!][!//
          [!ERROR!]
            Error : The configured MAC layer type/ subtype- MII for controller [!"./EthCtrlIdx"!] is not supported by the device.
          [!ENDERROR!]
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!IF "(./EthCtrlMacLayerSpeed/*[1] = 'ETH_MAC_LAYER_SPEED_1G')"!][!//
        [!VAR "MacSpeedFlag" = "(node:containsValue((ecu:list('Eth.EthSpeed')), 'ETH_1000MBPS'))"!][!//
        [!IF "$MacSpeedFlag = 'false'"!][!//
          [!ERROR!]
            Error : The configured MAC layer speed of 1 Gbps for controller [!"./EthCtrlIdx"!] is not supported by the device.
          [!ENDERROR!]
        [!ENDIF!][!//
      [!ELSEIF "(./EthCtrlMacLayerSpeed/*[1] = 'ETH_MAC_LAYER_SPEED_100M')"!][!//
        [!VAR "MacSpeedFlag" = "(node:containsValue((ecu:list('Eth.EthSpeed')), 'ETH_100MBPS'))"!][!//
        [!IF "$MacSpeedFlag = 'false'"!][!//
          [!ERROR!]
            Error : The configured MAC layer speed of 100 Mbps for controller [!"./EthCtrlIdx"!] is not supported by the device.
          [!ENDERROR!]
        [!ENDIF!][!//
      [!ELSEIF "(./EthCtrlMacLayerSpeed/*[1] = 'ETH_MAC_LAYER_SPEED_10M')"!][!//
        [!VAR "MacSpeedFlag" = "(node:containsValue((ecu:list('Eth.EthSpeed')), 'ETH_10MBPS'))"!][!//
        [!IF "$MacSpeedFlag = 'false'"!][!//
          [!ERROR!]
            Error : The configured MAC layer speed of 10 Mbps for controller [!"./EthCtrlIdx"!] is not supported by the device.
          [!ENDERROR!]
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDSELECT!][!//
  [!ENDFOR!][!//
  [!ENDNOCODE!][!//
  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  #define ETH_17_GETHMACV2_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
     without safeguard. It complies to Autosar guidelines. */
  /* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function
    before MemMap inclusion It complies to Autosar guidelines. */
  #include "Eth_17_GEthMacV2_MemMap.h"
  /*Array to store index of the controller in the allocated core.*/
  [!VAR "CurrentIdx" = "num:i(255)"!][!//
  [!VAR "EthCore0Idx" = "num:i(0)"!][!//
  [!VAR "EthCore1Idx" = "num:i(0)"!][!//
  [!VAR "EthCore2Idx" = "num:i(0)"!][!//
  [!VAR "EthCore3Idx" = "num:i(0)"!][!//
  [!VAR "EthCore4Idx" = "num:i(0)"!][!//
  [!VAR "EthCore5Idx" = "num:i(0)"!][!//
  [!IF "var:defined('postBuildVariant')"!][!//
    [!/*[cover parentID={C586A240-8E5C-4076-9B28-A1AFE51FCBEE}][/cover]*/!][!//
      static const uint8 Eth_17_GEthMacV2_ControllerIndexMap_[!"$postBuildVariant"!] [[!"num:i($MaxControllers)"!]] =
  [!ELSE!][!//
      static const uint8 Eth_17_GEthMacV2_ControllerIndexMap [[!"num:i($MaxControllers)"!]] =
  [!ENDIF!][!//
  {
  [!INDENT "2"!][!//
  [!FOR "ControllerID" = "num:i(0)" TO "num:i($MaxControllers) - num:i(1)"!][!//
    [!IF "node:exists(EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]) = 'true'"!][!//
      [!SELECT "EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]"!][!//
        [!VAR "NodeName" = "node:name(.)"!][!//
        [!FOR "CoreId" = "num:i(0)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
          [!CALL "ETH_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
          [!IF "$CGAllocationResult = 'TRUE'"!][!//
            [!IF "$CoreId = num:i(0)"!][!//
              [!VAR "CurrentIdx" = "$EthCore0Idx"!][!//
              [!VAR "EthCore0Idx" = "$EthCore0Idx+num:i(1)"!][!//
            [!ELSEIF "$CoreId = num:i(1)"!][!//
              [!VAR "CurrentIdx" = "$EthCore1Idx"!][!//
              [!VAR "EthCore1Idx" = "$EthCore1Idx+num:i(1)"!][!//
            [!ELSEIF "$CoreId = num:i(2)"!][!//
              [!VAR "CurrentIdx" = "$EthCore2Idx"!][!//
              [!VAR "EthCore2Idx" = "$EthCore2Idx+num:i(1)"!][!//
            [!ELSEIF "$CoreId = num:i(3)"!][!//
              [!VAR "CurrentIdx" = "$EthCore3Idx"!][!//
              [!VAR "EthCore3Idx" = "$EthCore3Idx+num:i(1)"!][!//
            [!ELSEIF "$CoreId = num:i(4)"!][!//
              [!VAR "CurrentIdx" = "$EthCore4Idx"!][!//
              [!VAR "EthCore4Idx" = "$EthCore4Idx+num:i(1)"!][!//
            [!ELSEIF "$CoreId = num:i(5)"!][!//
              [!VAR "CurrentIdx" = "$EthCore5Idx"!][!//
              [!VAR "EthCore5Idx" = "$EthCore5Idx+num:i(1)"!][!//
            [!ENDIF!][!//
          [!ENDIF!][!//
        [!ENDFOR!][!//
      [!ENDSELECT!][!//
      [!"num:inttohex(number($CurrentIdx))"!]U,
    [!ELSE!][!//
      [!"num:inttohex(number($CurrentIdx))"!]U,
    [!ENDIF!][!//
    [!VAR "CurrentIdx" = "num:i(255)"!][!//
  [!ENDFOR!][!//
  [!ENDINDENT!][!//
  };

  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  #define ETH_17_GETHMACV2_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
     without safeguard. It complies to Autosar guidelines. */
  /* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function
    before MemMap inclusion It complies to Autosar guidelines. */
  #include "Eth_17_GEthMacV2_MemMap.h"

  [!FOR "CoreId" = "num:i(0)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
    [!VAR "MaxControllersCore" = "num:i(0)"!][!//
    [!VAR "TempCoreId" = "concat('CORE',$CoreId)"!][!//
    [!CALL "ETH_GetMasterCoreID"!][!//
    [!FOR "ControllerID" = "num:i(0)" TO "num:i($MaxControllers) - num:i(1)"!][!//
      [!IF "node:exists(EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]) = 'true'"!][!//
        [!SELECT "EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]"!][!//
          [!VAR "NodeName" = "node:name(.)"!][!//
          [!CALL "ETH_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
          [!IF "$CGAllocationResult = 'TRUE'"!][!//
            [!NOCODE!][!//
              [!VAR "MaxControllersCore" = "$MaxControllersCore + num:i(1)"!][!//
            [!ENDNOCODE!][!//
          [!ENDIF!][!//
        [!ENDSELECT!][!//
      [!ENDIF!][!//
    [!ENDFOR!][!//
    [!IF "$MaxControllersCore != num:i(0)"!][!//
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      #define ETH_17_GETHMACV2_START_SEC_CONFIG_DATA_QM_CORE[!"$CoreId"!]_UNSPECIFIED
      /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
         without safeguard. It complies to Autosar guidelines. */
      /* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function
        before MemMap inclusion It complies to Autosar guidelines. */
      #include "Eth_17_GEthMacV2_MemMap.h"

      [!FOR "ControllerID" = "num:i(0)" TO "num:i($MaxControllers) - num:i(1)"!][!//
        [!VAR "MaxPriority" = "num:i(8)"!][!//
        [!VAR "PriorityIdx" = "num:i(255)"!][!//
        [!VAR "FifoIdx" = "num:i(0)"!][!//
        [!VAR "FifoIdxPrint" = "num:i(0)"!][!//
        [!VAR "FifoIdxNotSched" ="''"!][!//
        [!VAR "SchedulerString" ="''"!][!//
        [!IF "node:exists(EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]) = 'true'"!][!//
        [!SELECT "EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]"!][!//
          [!VAR "NodeName" = "node:name(.)"!][!//
          [!CALL "ETH_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
          [!IF "$CGAllocationResult = 'TRUE'"!][!//
            [!VAR "EgressFifoConfigured" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*))"!][!//
            [!IF "$EgressFifoConfigured > num:i(0)"!][!//
            /* Priority to FIFO index mapping */
            [!VAR "PredecessorMax" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*))"!][!//
            [!/*[cover parentID={37A06C11-EF3F-42b6-87C6-947F276D6642}][/cover]*/!][!//
            /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            [!IF "var:defined('postBuildVariant')"!]
              static const uint8 Eth_17_GEthMacV2_TxPrioFifoMapCtrl[!"$ControllerID"!]_[!"$postBuildVariant"!][[!"num:i($MaxPriority)"!]] =
            [!ELSE!][!//
              static const uint8 Eth_17_GEthMacV2_TxPrioFifoMapCtrl[!"$ControllerID"!][[!"num:i($MaxPriority)"!]] =
            [!ENDIF!][!//
            {
              [!INDENT "2"!][!//
              [!FOR "EgressFifo" = "num:i(0)" TO "num:i($EgressFifoConfigured) - num:i(1)"!][!//
                [!VAR "FifoIdx" = "num:i($EgressFifo)"!][!//
                [!VAR "TempVal" = "num:i(1)"!][!//
                [!IF "node:exists(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]) = 'true'"!][!//
                  [!FOR "Predecessor" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
                    [!VAR "SchedulerString" = "text:split(node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef),'/')[last()]"!][!//
                    [!CALL "Eth_ShaperDet", "PredecessorRef" = "$SchedulerString", "RetVal" = "num:i(255)"!][!//
                    [!IF "$RetVal = num:i(1)"!][!//
                      [!VAR "SchedFifoIdx" = "node:value(node:ref(node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigShaperPredecessorFifoRef))/EthCtrlConfigEgressFifoIdx)"!][!//
                    [!ELSE!][!//
                      [!VAR "SchedFifoIdx" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoIdx))"!][!//
                    [!ENDIF!][!//
                    [!IF "$FifoIdx = $SchedFifoIdx"!][!//
                      [!VAR "TempVal" = "num:i(0)"!][!//
                      [!BREAK!][!//
                    [!ENDIF!][!//
                  [!ENDFOR!][!//
                [!ENDIF!][!//
                [!IF "$TempVal = num:i(1)"!][!//
                    [!VAR "FifoIdxNotSched" = "concat($FifoIdxNotSched,$FifoIdx,',')"!][!//
                [!ENDIF!][!//
              [!ENDFOR!][!//
              [!VAR "MaxVal" = "count(text:split($FifoIdxNotSched,','))"!][!//
              [!FOR "Priority" = "num:i(0)" TO "num:i($MaxPriority) - num:i(1)"!][!//
                [!VAR "IdxFlag" = "num:i(0)"!][!//
                [!FOR "EgressFifo" = "num:i(1)" TO "num:i($EgressFifoConfigured)"!][!//
                  [!VAR "FifoIdx" = "num:i(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[num:i($EgressFifo)]/EthCtrlConfigEgressFifoIdx)"!][!//
                  [!IF "$EgressFifoConfigured > num:i(1)"!][!//
                    [!IF "node:exists(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[num:i($EgressFifo)]/EthCtrlConfigEgressFifoPriorityAssignment/*[1]) = 'true'"!][!//
                      [!VAR "FifoPriorityCount" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[num:i($EgressFifo)]/EthCtrlConfigEgressFifoPriorityAssignment/*))"!][!//
                      [!FOR "FifoPriority" = "num:i(1)" TO "num:i($FifoPriorityCount)"!][!//
                        [!VAR "EgressPriority" = "EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[num:i($EgressFifo)]/EthCtrlConfigEgressFifoPriorityAssignment/*[num:i($FifoPriority)]"!][!//
                        [!IF "$Priority = $EgressPriority"!][!//
                          [!VAR "IdxTest" = "text:contains(text:split($FifoIdxNotSched,','),string($FifoIdx))"!][!//
                          [!IF "$IdxTest = 'false'"!][!//
                            [!VAR "FifoIdxPrint" = "num:i($FifoIdx)"!][!//
                            [!FOR "FifoValue" = "num:i(1)" TO "num:i($MaxVal)"!][!//
                              [!IF "$FifoIdx > text:split($FifoIdxNotSched,',')[num:i($FifoValue)]"!][!//
                                [!VAR "FifoIdxPrint" = "num:i($FifoIdxPrint) - num:i(1)"!][!//
                              [!ENDIF!][!//
                            [!ENDFOR!][!//
                            [!"num:inttohex(($FifoIdxPrint))"!]U[!IF "$Priority < num:i($MaxPriority) - num:i(1)"!],[!ENDIF!][!CR!]
                            [!VAR "IdxFlag" = "num:i(1)"!][!//
                          [!ELSE!][!//
                            [!VAR "IdxFlag" = "num:i(0)"!][!//
                          [!ENDIF!][!//
                        [!ENDIF!][!//
                      [!ENDFOR!][!//
                    [!ELSE!][!//
                      [!ERROR!][!//
                        Priority not assigned to Egress FIFO index [!"$FifoIdx"!]. If more than one FIFO is configured priority assignment for all the fifo is mandatory.
                      [!ENDERROR!][!//
                    [!ENDIF!][!//
                  [!ELSE!][!//
                    [!VAR "FifoPriorityCount" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[num:i($EgressFifo)]/EthCtrlConfigEgressFifoPriorityAssignment/*))"!][!//
                    [!IF "$FifoPriorityCount = num:i(0)"!][!//
                      [!"num:inttohex(($FifoIdx))"!]U[!IF "$Priority < num:i($MaxPriority) - num:i(1)"!],[!ENDIF!][!CR!]
                      [!VAR "IdxFlag" = "num:i(1)"!][!//
                    [!ELSE!][!//
                      [!FOR "FifoPriority" = "num:i(1)" TO "num:i($FifoPriorityCount)"!][!//
                        [!VAR "EgressPriority" = "EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[num:i($EgressFifo)]/EthCtrlConfigEgressFifoPriorityAssignment/*[num:i($FifoPriority)]"!][!//
                        [!IF "$Priority = $EgressPriority"!][!//
                          [!VAR "IdxTest" = "text:contains(text:split($FifoIdxNotSched,','),string($FifoIdx))"!][!//
                          [!IF "$IdxTest = 'false'"!][!//
                            [!VAR "FifoIdxPrint" = "num:i($FifoIdx)"!][!//
                            [!"num:inttohex(($FifoIdxPrint))"!]U[!IF "$Priority < num:i($MaxPriority) - num:i(1)"!],[!ENDIF!][!CR!]
                            [!VAR "IdxFlag" = "num:i(1)"!][!//
                          [!ELSE!][!//
                            [!VAR "IdxFlag" = "num:i(0)"!][!//
                          [!ENDIF!][!//
                        [!ENDIF!][!//
                      [!ENDFOR!][!//
                    [!ENDIF!][!//
                  [!ENDIF!][!//
                [!ENDFOR!][!//
                [!IF "$IdxFlag = num:i(0)"!][!//
                  [!"num:inttohex($PriorityIdx)"!]U[!IF "$Priority < num:i($MaxPriority) - num:i(1)"!],[!ENDIF!][!CR!]
                [!ENDIF!][!//
              [!ENDFOR!][!//
              [!ENDINDENT!][!//
            };

             /* Fifo to Egress Queue Mapping */
            [!VAR "NewPriority" ="num:i(0)"!][!//
            [!VAR "Flag" ="num:i(0)"!][!//
            [!VAR "FifoOrderString" ="''"!][!//
            [!VAR "NonCBSOrderString" ="''"!][!//
            [!VAR "CBSOrderString" ="''"!][!//
            [!VAR "CBSCount" = "num:i(0)"!][!//
            [!VAR "PredecessorString" ="''"!][!//
            [!VAR "BufTotal" = "num:i(0)"!][!//
            [!VAR "BufLength" = "num:i(0)"!][!//
            [!IF "node:exists(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]) = 'true'"!][!//
              [!VAR "PredecessorMax" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*))"!][!//
            [!ENDIF!][!//
            [!VAR "PredecessorString" = "text:split(node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[1]/EthCtrlConfigSchedulerPredecessorRef),'/')[last()]"!][!//
            [!/*[cover parentID={08D01086-EAC3-4225-A16F-BD6C3D48B5C7}][/cover]*/!][!//
            /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            [!IF "var:defined('postBuildVariant')"!][!//
                static const uint8 Eth_17_GEthMacV2_TxFifoChnlMapCtrl[!"$ControllerID"!]_[!"$postBuildVariant"!][[!"num:i($PredecessorMax)"!]] =
            [!ELSE!][!//
                static const uint8 Eth_17_GEthMacV2_TxFifoChnlMapCtrl[!"$ControllerID"!][[!"num:i($PredecessorMax)"!]] =
            [!ENDIF!][!//
            {
              [!INDENT "2"!][!//
                [!IF "node:exists(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]) = 'true'"!][!//
                  [!IF "node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerAlgorithm) = 'ETH_SCHEDULER_STRICT_PRIORITY'"!][!//
                    [!FOR "Predecessor" = "num:i(0)" TO "num:i($PredecessorMax)-num:i(1)"!][!//
                      [!VAR "PredecessorOrder" = "num:i(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorOrder)"!][!//
                      [!VAR "OldPriority" = "$NewPriority"!][!//
                      [!VAR "PredecessorString" = "text:split(node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef),'/')[last()]"!][!//
                      [!CALL "Eth_ShaperDet", "PredecessorRef" = "$PredecessorString", "RetVal" = "num:i(255)"!][!//
                      [!IF "$RetVal = num:i(1)"!][!//
                        [!VAR "FifoIdx" = "node:value(node:ref(node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigShaperPredecessorFifoRef))/EthCtrlConfigEgressFifoIdx)"!][!//
                        [!VAR "BufTotal" = "node:value(node:ref(node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigShaperPredecessorFifoRef))/EthCtrlConfigEgressFifoBufTotal)"!][!//
                        [!VAR "BufLength" = "node:value(node:ref(node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigShaperPredecessorFifoRef))/EthCtrlConfigEgressFifoBufLenByte)"!][!//
                      [!ELSE!][!//
                        [!VAR "FifoIdx" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoIdx))"!][!//
                        [!VAR "BufTotal" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoBufTotal))"!][!//
                        [!VAR "BufLength" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[EthCtrlConfigSchedulerPredecessorOrder = ($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoBufLenByte))"!][!//
                      [!ENDIF!][!//
                      [!VAR "FifoOrderString" = "concat($FifoOrderString,$FifoIdx,',',$PredecessorOrder,',',$BufTotal,',',$BufLength,'@')"!][!// form the string FifoIdx,PredecessorOrder,BufTotal,BufLength@.....
                    [!ENDFOR!][!//
                  [!ELSE!][!//
                    [!FOR "Predecessor" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
                      [!VAR "PredecessorOrder" = "num:i(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorOrder)"!][!//
                      [!VAR "PredecessorString" = "text:split(node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef),'/')[last()]"!][!//
                      [!CALL "Eth_ShaperDet", "PredecessorRef" = "$PredecessorString", "RetVal" = "num:i(255)"!][!//
                      [!IF "$RetVal = num:i(1)"!][!//
                        [!VAR "FifoIdx" = "node:value(node:ref(node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigShaperPredecessorFifoRef))/EthCtrlConfigEgressFifoIdx)"!][!//
                        [!VAR "BufTotal" = "node:value(node:ref(node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigShaperPredecessorFifoRef))/EthCtrlConfigEgressFifoBufTotal)"!][!//
                        [!VAR "BufLength" = "node:value(node:ref(node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigShaperPredecessorFifoRef))/EthCtrlConfigEgressFifoBufLenByte)"!][!//
                      [!ELSE!][!//
                        [!VAR "FifoIdx" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoIdx))"!][!//
                        [!VAR "BufTotal" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoBufTotal))"!][!//
                        [!VAR "BufLength" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoBufLenByte))"!][!//
                      [!ENDIF!][!//
                      [!IF "node:exists(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[EthCtrlConfigEgressFifoIdx = ($FifoIdx)]/EthCtrlConfigEgressFifoPriorityAssignment/*) = 'true'"!][!//
                        [!VAR "NewPriority" = "num:max(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[EthCtrlConfigEgressFifoIdx = ($FifoIdx)]/EthCtrlConfigEgressFifoPriorityAssignment/*)"!][!//
                      [!ELSE!][!//
                        [!VAR "NewPriority" ="num:i(0)"!][!//
                      [!ENDIF!][!//
                      [!IF "$RetVal = num:i(1)"!][!//
                        [!VAR "CBSCount" = "num:i($CBSCount) + num:i(1)"!][!//
                        [!VAR "CBSOrderString" = "concat($CBSOrderString,$FifoIdx,',',$NewPriority,',',$PredecessorOrder,',',$BufTotal,',',$BufLength,'@')"!][!// form the string FifoIdx,MaxPriority,PredecessorOrder,BufTotal,BufLength@.....
                      [!ELSE!][!//
                        [!VAR "NonCBSOrderString" = "concat($NonCBSOrderString,$FifoIdx,',',$NewPriority,',',$PredecessorOrder,',',$BufTotal,',',$BufLength,'@')"!][!// form the string FifoIdx,MaxPriority,PredecessorOrder,BufTotal,BufLength@.....
                      [!ENDIF!][!//
                    [!ENDFOR!][!//
                    [!CALL "Sorting","SortArray" = "$CBSOrderString","VItem" = "num:i(2)","VTotalNum" = "$CBSCount","VDrctn" = "num:i(1)"!][!//
                    [!VAR "CBSOrderString" = "$SortArray"!][!//
                    [!CALL "Sorting","SortArray" = "$NonCBSOrderString","VItem" = "num:i(2)","VTotalNum" = "$PredecessorMax - $CBSCount","VDrctn" = "num:i(1)"!][!//
                    [!VAR "NonCBSOrderString" = "$SortArray"!][!//
                    [!VAR "FifoOrderString" = "concat($NonCBSOrderString,$CBSOrderString)"!][!//
                    [!FOR "Predecessor" = "num:i(0)" TO "num:i($PredecessorMax) - num:i(1)"!][!//
                      [!VAR "StringElem" = "text:split($FifoOrderString,'@')[num:i($Predecessor+1)]"!][!//
                      [!CALL "ReplaceValue","ReplaceArray" = "$StringElem","VPosition" = "num:i(3)","VReplaceVal" = "$Predecessor"!][!//
                      [!VAR "FifoOrderString" = "text:replace($FifoOrderString,$StringElem,$ReplaceArray)"!][!//
                    [!ENDFOR!][!//
                  [!ENDIF!][!//
                [!ENDIF!][!//
                [!VAR "MapIdx" = "num:i(0)"!][!//
                [!VAR "ChnlMapStr" = "''"!][!//
                [!FOR "Count" = "num:i(1)" TO "num:i(4)"!][!//
                  [!FOR "Count1" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
                    [!VAR "Split" = "text:split($FifoOrderString,'@')[num:i($Count1)]"!][!//
                    [!VAR "Index" = "text:split($Split,',')[num:i(1)]"!][!//
                    [!VAR "PredOrder" = "text:split($Split,',')[num:i(2)]"!][!//
                    [!IF "num:i($Index) = num:i($Count)-num:i(1)"!][!//
                      [!VAR "ChnlMapStr" = "concat($ChnlMapStr,$PredOrder,',',$MapIdx,'@')"!][!//
                      [!VAR "MapIdx" ="num:i($MapIdx + num:i(1))"!][!//
                      [!VAR "Flag" ="$Flag + num:i(1)"!][!//
                      [!"num:i($PredOrder)"!]U[!IF "$Flag < num:i($PredecessorMax)"!],[!ENDIF!][!CR!]
                      [!BREAK!][!//
                    [!ENDIF!][!//
                  [!ENDFOR!][!//
                [!ENDFOR!][!//
              [!ENDINDENT!][!//
            };

            /* Channel to Egress FIFO Mapping */
            /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            [!IF "var:defined('postBuildVariant')"!][!//
                static const uint8 Eth_17_GEthMacV2_TxChnlFifoMapCtrl[!"$ControllerID"!]_[!"$postBuildVariant"!][4] =
            [!ELSE!][!//
                static const uint8 Eth_17_GEthMacV2_TxChnlFifoMapCtrl[!"$ControllerID"!][4] =
            [!ENDIF!][!//
            {
              [!CALL "Sorting","SortArray" = "$ChnlMapStr","VItem" = "num:i(1)","VTotalNum" = "$PredecessorMax","VDrctn" = "num:i(1)"!][!//
              [!VAR "ChnlMapStr" = "$SortArray"!][!//
              [!INDENT "2"!][!//
                [!FOR "Count1" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
                  [!VAR "Split" = "text:split($ChnlMapStr,'@')[num:i($Count1)]"!][!//
                  [!VAR "ChnlIdx" = "text:split($Split,',')[num:i(1)]"!][!//
                  [!VAR "MapFifoIdx" = "text:split($Split,',')[num:i(2)]"!][!//
                  [!IF "num:i($ChnlIdx) = num:i($Count1)-num:i(1)"!][!//
                    [!"num:i($MapFifoIdx)"!]U[!IF "$Count1 < num:i(4)"!],[!ENDIF!][!CR!]
                  [!ENDIF!][!//
                [!ENDFOR!][!//
                [!IF "$PredecessorMax < num:i(4)"!][!//
                  [!FOR "Count1" = "num:i($Count1+num:i(1))" TO "num:i(4)"!][!//
                    [!"num:i(255)"!]U[!IF "$Count1 < num:i(4)"!],[!ENDIF!][!CR!]
                  [!ENDFOR!][!//
                [!ENDIF!][!//
              [!ENDINDENT!][!//
            };

            /* Egress FIFO configuration */
            [!VAR "EgressFifoConfigured" = "num:i(0)"!][!//
            [!VAR "Flag" = "num:i(0)"!][!//
            [!VAR "EgressFifoOrderString" ="''"!][!//
            [!VAR "CreditValue" ="num:i(0)"!][!//
            [!VAR "PortTxRate" ="num:i(0)"!][!//
            [!VAR "TxQueueMode" ="num:i(0)"!][!//
            [!VAR "RemQueueSize" ="num:i(0)"!][!//
            [!VAR "IdleBandwidth" ="num:i(0)"!][!//
            [!VAR "MaxValue" ="num:i(536870912)"!][!//
            [!VAR "TotalQueueSize" ="num:i(0)"!][!//
            [!VAR "EgressFifoConfigured" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*))"!][!//
            [!VAR "PredecessorString" = "text:split(node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[1]/EthCtrlConfigSchedulerPredecessorRef),'/')[last()]"!][!//
            [!CALL "Eth_ShaperDet", "PredecessorRef" = "$PredecessorString", "RetVal" = "num:i(255)"!][!//
              [!IF "$EgressFifoConfigured > num:i(0)"!][!//
                [!VAR "ShaperMax" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigShaper/*))"!][!//
                [!IF "node:exists(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]) = 'true'"!][!//
                  [!VAR "PredecessorMax" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*))"!][!//
                  [!FOR "Predecessor" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
                    [!VAR "PredecessorString" = "text:split(node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef),'/')[last()]"!][!//
                    [!CALL "Eth_ShaperDet", "PredecessorRef" = "$PredecessorString", "RetVal" = "num:i(255)"!][!//
                    [!IF "$RetVal = num:i(1)"!][!//
                      [!VAR "BufLength" = "node:value(node:ref(node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigShaperPredecessorFifoRef))/EthCtrlConfigEgressFifoBufLenByte)"!][!//
                      [!IF "num:i($BufLength) mod 256 != 0"!][!//
                        [!VAR "EgressQueueQuotient" = "num:i($BufLength) div 256"!][!//
                        [!VAR "BufLength" = "(num:i($EgressQueueQuotient) + 1) * 256"!][!//
                      [!ENDIF!][!//
                      [!VAR "TotalQueueSize" = "num:i($TotalQueueSize) + num:i($BufLength)"!][!//
                    [!ELSE!][!//
                      [!VAR "BufLength" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoBufLenByte))"!][!//
                      [!IF "num:i($BufLength) mod 256 != 0"!][!//
                        [!VAR "EgressQueueQuotient" = "num:i($BufLength) div 256"!][!//
                        [!VAR "BufLength" = "(num:i($EgressQueueQuotient) + 1) * 256"!][!//
                      [!ENDIF!][!//
                      [!VAR "TotalQueueSize" = "num:i($TotalQueueSize) + num:i($BufLength)"!][!//
                    [!ENDIF!][!//
                  [!ENDFOR!][!//
                  [!IF "num:i($TotalQueueSize) > num:i(4096)"!][!//
                    [!ERROR!][!//
                        The sum of the individual buffer lengths (rounded off to 256 byte length) of Egress FIFOs is greater than 4KB. Reduce to size of buffer lengths to fit within 4KB size.
                    [!ENDERROR!][!//
                  [!ENDIF!][!//
                [!ENDIF!][!//
                [!VAR "RemQueueSize" = " num:i(4096) - num:i($TotalQueueSize)"!][!//
                [!VAR "RemQueueQuotient" = " num:i($RemQueueSize) div num:i(256)"!][!//
                [!VAR "RemQueueQuotient_1" = " num:i($RemQueueQuotient) div num:i($EgressFifoConfigured)"!][!//
                [!VAR "RemQueueMod" = " num:i($RemQueueQuotient) mod num:i($EgressFifoConfigured)"!][!//
                [!/* algorithm to calculate Egress Queue Size */!][!//
                [!VAR "BufTotArr" = "''"!][!//
                [!VAR "BufLenArr" = "''"!][!//
                [!VAR "InitArr" = "'1 1 1 1'"!][!//
                [!CALL "Sorting","SortArray" = "$FifoOrderString","VItem" = "num:i(2)","VTotalNum" = "$PredecessorMax","VDrctn" = "num:i(-1)"!][!//
                [!VAR "FifoOrderString" = "$SortArray"!][!//
                [!FOR "Predecessor" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
                  [!VAR "Split" = "text:split($FifoOrderString,'@')[num:i($Predecessor)]"!][!//
                  [!IF "node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerAlgorithm) = 'ETH_SCHEDULER_STRICT_PRIORITY'"!][!//
                    [!VAR "BufTotArr" = "concat($BufTotArr,text:split($Split,',')[num:i(3)],' ')"!][!//
                    [!VAR "BufLen" = "text:split($Split,',')[num:i(4)]"!][!//
                  [!ELSE!][!//
                    [!VAR "BufTotArr" = "concat($BufTotArr,text:split($Split,',')[num:i(4)],' ')"!][!//
                    [!VAR "BufLen" = "text:split($Split,',')[num:i(5)]"!][!//
                  [!ENDIF!][!//
                  [!IF "num:i($BufLen) mod 256 != 0"!][!//
                    [!VAR "VQuotient" = "num:i($BufLen) div 256"!][!//
                    [!VAR "BufLen" = "(num:i($VQuotient) + 1) * 256"!][!//
                  [!ENDIF!][!//
                  [!VAR "BufLen" = "num:i(num:i($BufLen) div 256)"!][!//
                  [!VAR "BufLenArr" = "concat($BufLenArr,$BufLen,' ')"!][!//
                [!ENDFOR!][!//
                [!VAR "EgQueueSize" = "num:i(16)"!][!//
                [!VAR "NewInitArr" = "$InitArr"!][!//
                [!FOR "$VLoop" = "num:i(0)" TO "num:i($EgQueueSize)"!][!//
                  [!VAR "NewInitArr" = "''"!][!//
                  [!FOR "VLoop2" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
                    [!VAR "VBufTotArElem" = "text:split($BufTotArr,' ')[num:i($VLoop2)]"!][!//
                    [!VAR "VInitArrElem" = "text:split($InitArr,' ')[num:i($VLoop2)]"!][!//
                    [!IF "num:i($VBufTotArElem)-num:i($VInitArrElem) > num:i(0)"!][!//
                      [!VAR "VNewInitArrElem" =  "num:i($VInitArrElem) + num:i(1)"!][!//
                      [!VAR "NewInitArr" = "concat($NewInitArr,num:i($VNewInitArrElem),' ')"!][!//
                    [!ELSE!][!//
                      [!VAR "NewInitArr" = "concat($NewInitArr,num:i($VInitArrElem),' ')"!][!//
                    [!ENDIF!][!//
                  [!ENDFOR!][!//
                  [!VAR "MulRes" = "num:mul(text:split($BufLenArr),text:split($NewInitArr))"!][!//
                  [!VAR "MulRes" = "text:join(text:split($MulRes, ','), ' ')"!][!//
                  [!VAR "MulRes" = "substring-before(substring-after($MulRes, '['),']')"!][!//
                  [!CALL "SumElem","SumArray"="$MulRes","VNumElem"="num:i($PredecessorMax)","SumVal"="num:i(0)"!][!//
                  [!VAR "SumMulElem" = "$SumVal"!][!//
                  [!IF "(num:i($SumMulElem) = num:i($EgQueueSize))"!][!//
                    [!VAR "InitArr" = "$NewInitArr"!][!//
                    [!VAR "FinalAlloc" = "$MulRes"!][!//
                    [!BREAK!][!//
                  [!ELSEIF "(num:i($SumMulElem) > num:i($EgQueueSize))"!][!//
                    [!VAR "MulRes" = "num:mul(text:split($BufLenArr),text:split($InitArr))"!][!//
                    [!VAR "MulRes" = "text:join(text:split($MulRes, ','), ' ')"!][!//
                    [!VAR "MulRes" = "substring-before(substring-after($MulRes, '['),']')"!][!//
                    [!VAR "FinalAlloc" = "$MulRes"!][!//
                    [!FOR "VLoop3" = "num:i(1)" TO "num:i(2)"!][!//
                      [!FOR "Predecessor" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
                        [!VAR "VInitArrGetElem" = "num:i(text:split($FinalAlloc,' ')[num:i($Predecessor)])"!][!//
                        [!VAR "VInitArrGetElem" = "num:i($VInitArrGetElem + (num:i(1)))"!][!//
                        [!VAR "FinalAlloc" = "concat(substring-before($FinalAlloc, text:split($FinalAlloc,' ')[num:i($Predecessor)]),$VInitArrGetElem,substring-after($FinalAlloc, text:split($FinalAlloc,' ')[num:i($Predecessor)]))"!][!//
                        [!CALL "SumElem","SumArray"="$FinalAlloc","VNumElem"="num:i($PredecessorMax)","SumVal"="num:i(0)"!][!//
                        [!IF "$SumVal = num:i(16)"!][!//
                          [!BREAK!][!//
                        [!ENDIF!][!//
                      [!ENDFOR!][!//
                      [!IF "$SumVal = num:i(16)"!][!//
                        [!BREAK!][!//
                      [!ENDIF!][!//
                    [!ENDFOR!][!//
                    [!BREAK!][!//
                  [!ELSEIF "(contains($InitArr, $BufTotArr))"!][!//
                    [!VAR "MulRes" = "num:mul(text:split($BufLenArr),text:split($InitArr))"!][!//
                    [!VAR "MulRes" = "text:join(text:split($MulRes, ','), ' ')"!][!//
                    [!VAR "MulRes" = "substring-before(substring-after($MulRes, '['),']')"!][!//
                    [!CALL "SumElem","SumArray"="$MulRes","VNumElem"="num:i($PredecessorMax)","SumVal"="num:i(0)"!][!//
                    [!VAR "VInitArrFirstElem" = "num:i(text:split($MulRes,' ')[num:i(1)])"!][!//
                    [!VAR "VInitArrFirstElem" = "num:i($VInitArrFirstElem + (num:i($EgQueueSize)-num:i($SumVal)))"!][!//
                    [!VAR "FinalAlloc" = "concat($VInitArrFirstElem,substring-after($MulRes, text:split($MulRes,' ')[num:i(1)]))"!][!//
                    [!BREAK!][!//
                  [!ELSE!][!//
                    [!VAR "InitArr" = "$NewInitArr"!]
                  [!ENDIF!][!//
                [!ENDFOR!][!//
                [!/*[cover parentID={16E4A9B2-F0D0-47e0-B942-E8C2BAEE1E81}][/cover]*/!][!//
                [!IF "var:defined('postBuildVariant')"!]
                    static const Eth_17_GEthMacV2_TxFifoCfgType Eth_17_GEthMacV2_TxFifoCfgCtrl[!"$ControllerID"!]_[!"$postBuildVariant"!][[!"num:i($PredecessorMax)"!]] =
                [!ELSE!][!//
                    static const Eth_17_GEthMacV2_TxFifoCfgType Eth_17_GEthMacV2_TxFifoCfgCtrl[!"$ControllerID"!][[!"num:i($PredecessorMax)"!]] =
                [!ENDIF!][!//
                {
                  [!FOR "EgressFifo" = "num:i(0)" TO "num:i($EgressFifoConfigured) - num:i(1)"!][!//
                    [!VAR "EgressFifoIdx" = "num:i(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[EthCtrlConfigEgressFifoIdx = ($EgressFifo)]/EthCtrlConfigEgressFifoIdx)"!][!//
                    [!IF "node:exists(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[EthCtrlConfigEgressFifoIdx = ($EgressFifoIdx)]/EthCtrlConfigEgressFifoPriorityAssignment/*) = 'true'"!][!//
                      [!VAR "Priority" = "num:max(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[EthCtrlConfigEgressFifoIdx = ($EgressFifo)]/EthCtrlConfigEgressFifoPriorityAssignment/*)"!][!//
                    [!ELSE!][!//
                      [!VAR "Priority" = "num:i(0)"!][!//
                    [!ENDIF!][!//
                    [!VAR "EgressFifoOrderString" = "concat($EgressFifoOrderString,$EgressFifoIdx,',',$Priority,'@')"!][!//
                  [!ENDFOR!][!//
                  [!VAR "Split1" = "$EgressFifoOrderString"!][!//
                  [!VAR "VTempReplceStr1" = "'String1'"!][!//
                  [!VAR "VTempReplceStr2" = "'String2'"!][!//
                  [!FOR "Count" = "num:i(1)" TO "num:i($EgressFifoConfigured)"!][!//
                    [!FOR "Count1" = "num:i(1)" TO "num:i($EgressFifoConfigured)- num:i($Count)"!][!//
                      [!VAR "Split" = "text:split($Split1,'@')[num:i($Count1)]"!][!//
                      [!VAR "Temp2" = "text:split($Split1,'@')[num:i($Count1) + num:i(1)]"!][!//
                      [!VAR "Index" = "text:split($Split,',')[num:i(1)]"!][!//
                      [!VAR "Priority1" = "text:split($Split,',')[num:i(2)]"!][!//
                      [!VAR "Priority2" = "text:split($Temp2,',')[num:i(2)]"!][!//
                      [!IF "$Priority1 < $Priority2"!][!//
                        [!VAR "Split1" = "text:replace($Split1,$Split,$VTempReplceStr1)"!][!//
                        [!VAR "Split1" = "text:replace($Split1,$Temp2,$VTempReplceStr2)"!][!//
                        [!VAR "Split1" = "text:replace($Split1,$VTempReplceStr2,$Split)"!][!//
                        [!VAR "Split1" = "text:replace($Split1,$VTempReplceStr1,$Temp2)"!][!//
                      [!ENDIF!][!//
                    [!ENDFOR!][!//
                  [!ENDFOR!][!//
                  [!FOR "EgressFifo" = "num:i(0)" TO "num:i($EgressFifoConfigured) - num:i(1)"!][!//
                    [!NOCODE!][!//
                      [!VAR "EgressFifoIdx" = "num:i(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[EthCtrlConfigEgressFifoIdx = ($EgressFifo)]/EthCtrlConfigEgressFifoIdx)"!][!// check if EgressFifoIdx can be removed as this should be same as EgressFifo
                      [!IF "node:exists(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]) = 'true'"!][!//
                        [!VAR "PredecessorMax" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*))"!][!//
                        [!FOR "Predecessor" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
                          [!VAR "PredecessorString" = "text:split(node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef),'/')[last()]"!][!//
                          [!CALL "Eth_ShaperDet", "PredecessorRef" = "$PredecessorString", "RetVal" = "num:i(255)"!][!//
                            [!IF "$RetVal = num:i(1)"!][!//
                              [!VAR "SchedFifoIdx" = "node:value(node:ref(node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigShaperPredecessorFifoRef))/EthCtrlConfigEgressFifoIdx)"!][!//
                            [!ELSE!][!//
                              [!VAR "SchedFifoIdx" = "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*[num:i($Predecessor)]/EthCtrlConfigSchedulerPredecessorRef)/EthCtrlConfigEgressFifoIdx))"!][!//
                            [!ENDIF!][!//
                            [!IF "$EgressFifoIdx = $SchedFifoIdx"!][!//
                              [!VAR "TempVal" = "num:i(0)"!][!//
                              [!BREAK!][!//
                            [!ELSE!][!//
                              [!VAR "TempVal" = "num:i(1)"!][!//
                            [!ENDIF!][!//
                        [!ENDFOR!][!//
                      [!ENDIF!][!//
                      [!/*************Warning for Fifo configured but not scheduled************/!][!//
                      [!IF "$TempVal = num:i(1)"!][!//
                        [!WARNING!][!//
                          Egress FIFO index [!"$EgressFifo"!] is configured but not scheduled for transmission. The transmission requests from FIFO index [!"$EgressFifo"!] will not be accepted.
                        [!ENDWARNING!][!//
                      [!ELSE!][!//
                        [!/*****Check if the scheduled FIFO is configured with DMA weight in WSP/ WRR*****/!][!//
                        [!VAR "DmaChnlWeight" = "num:i(0)"!][!//
                        [!IF "node:value(EthCtrlConfigEgress/EthCtrlConfigDMAArbitration/*[1]/EthCtrlConfigDMAArbitrationAlgorithm) != 'ETH_DMA_ARBITRATION_FIXED_PRIORITY'"!][!//
                          [!FOR "Count1" = "num:i(1)" TO "num:i(count(EthCtrlConfigEgress/EthCtrlConfigDMAArbitration/*[1]/EthCtrlConfigDMAWeightAssignment/*))"!][!//
                            [!VAR "DMASchedFifoIdx" =  "node:value((node:ref(EthCtrlConfigEgress/EthCtrlConfigDMAArbitration/*[1]/EthCtrlConfigDMAWeightAssignment/*[num:i($Count1)]/EthCtrlConfigDMAEgressFifoRef)/EthCtrlConfigEgressFifoIdx))"!][!//
                            [!IF "$EgressFifo = $DMASchedFifoIdx"!][!//
                              [!VAR "DmaChnlWeight" = "node:value(EthCtrlConfigEgress/EthCtrlConfigDMAArbitration/*[1]/EthCtrlConfigDMAWeightAssignment/*[num:i($Count1)]/EthCtrlConfigDMAArbitrationWeight)"!][!//
                              [!BREAK!][!//
                            [!ENDIF!][!//
                          [!ENDFOR!][!//
                          [!IF "$DmaChnlWeight = num:i(0)"!][!//
                            [!ERROR!][!//
                              Error: The Weight for Egress FIFO index [!"$EgressFifo"!] is not configured in the EthCtrlConfigDMAWeightAssignment container. Configuration of weight is mandatory in Weighted Strict Priority/ Weight Round Robin scheduling mechanism.
                            [!ENDERROR!][!//
                          [!ELSE!][!//
                            [!VAR "DmaChnlWeight" = "num:i(num:i($DmaChnlWeight) - num:i(1))"!][!//
                          [!ENDIF!][!//
                        [!ENDIF!][!//

                        [!/*************Slope Calculation(IdleSlope, SendSlope, HiCredit, LoCredit)************/!][!//
                        [!IF "$RetVal = num:i(1)"!][!//
                          [!IF "(./EthCtrlMacLayerSpeed/*[1] = 'ETH_MAC_LAYER_SPEED_10M')"!][!//
                            [!VAR "PortTxRate" ="num:i(10000000)"!][!//
                          [!ELSEIF "(./EthCtrlMacLayerSpeed/*[1] = 'ETH_MAC_LAYER_SPEED_100M')"!][!//
                            [!VAR "PortTxRate" ="num:i(100000000)"!][!//
                          [!ELSE!][!//
                            [!VAR "PortTxRate" ="num:i(1000000000)"!][!//
                          [!ENDIF!][!//
                          [!IF "./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XGMII' and ./EthCtrlMacLayerSubType/*[1] = 'REDUCED'"!][!//
                            [!IF "(./EthCtrlMacLayerSpeed/*[1] = 'ETH_MAC_LAYER_SPEED_10M') or (./EthCtrlMacLayerSpeed/*[1] = 'ETH_MAC_LAYER_SPEED_100M')"!][!//
                              [!VAR "CreditValue" ="num:i(4)"!][!//
                            [!ELSE!][!//
                              [!VAR "CreditValue" ="num:i(8)"!][!//
                            [!ENDIF!][!//
                          [!ELSEIF "./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XMII' and ./EthCtrlMacLayerSubType/*[1] = 'REDUCED'"!][!//
                            [!IF "(./EthCtrlMacLayerSpeed/*[1] = 'ETH_MAC_LAYER_SPEED_10M') or (./EthCtrlMacLayerSpeed/*[1] = 'ETH_MAC_LAYER_SPEED_100M')"!][!//
                              [!VAR "CreditValue" ="num:i(4)"!][!//
                            [!ENDIF!][!//
                          [!ELSE!][!//
                            [!VAR "CreditValue" ="num:i(4)"!][!//
                          [!ENDIF!][!//
                          [!FOR "Shaper" = "num:i(1)" TO "num:i($ShaperMax)"!][!//
                            [!VAR "ShaperFifoIdx" = "node:value(node:ref(EthCtrlConfigEgress/EthCtrlConfigShaper/*[num:i($Shaper)]/EthCtrlConfigShaperPredecessorFifoRef)/EthCtrlConfigEgressFifoIdx)"!][!//
                            [!IF "$ShaperFifoIdx = $SchedFifoIdx"!][!//
                              [!VAR "IdleSlopeValue" ="EthCtrlConfigEgress/EthCtrlConfigShaper/*[num:i($Shaper)]/EthCtrlConfigShaperIdleSlope/*[1]"!][!//
                              [!IF "(./EthCtrlMacLayerSpeed/*[1] = 'ETH_MAC_LAYER_SPEED_10M')"!][!//
                                [!IF "$IdleSlopeValue > num:i(10000000)"!][!//
                                  [!ERROR!][!//
                                    Error: Value of EthCtrlConfigShaperIdleSlope parameter is beyond the maximum range for the configured MAC layer type and speed.
                                  [!ENDERROR!][!//
                                [!ENDIF!][!//
                              [!ELSEIF "(./EthCtrlMacLayerSpeed/*[1] = 'ETH_MAC_LAYER_SPEED_100M')"!][!//
                                [!IF "$IdleSlopeValue > num:i(100000000)"!][!//
                                  [!ERROR!][!//
                                    Error: Value of EthCtrlConfigShaperIdleSlope parameter is beyond the maximum range for the configured MAC layer type and speed.
                                  [!ENDERROR!][!//
                                [!ENDIF!][!//
                              [!ENDIF!][!//
                              [!VAR "HiCreditValue" ="EthCtrlConfigEgress/EthCtrlConfigShaper/*[num:i($Shaper)]/EthCtrlConfigShaperHiCredit"!][!//
                              [!VAR "LoCreditValue" ="EthCtrlConfigEgress/EthCtrlConfigShaper/*[num:i($Shaper)]/EthCtrlConfigShaperLoCredit"!][!//
                              [!VAR "IdleBandwidth" ="num:i($IdleSlopeValue) div num:i($PortTxRate)"!][!//
                              [!VAR "IdleSlopeCredit" ="$IdleBandwidth * $CreditValue"!][!//
                              [!VAR "SendSlopeCredit" ="$CreditValue - $IdleSlopeCredit"!][!//
                              [!VAR "IdleSlopeCredit" ="num:i(round($IdleSlopeCredit * num:i(1024)))"!][!//
                              [!VAR "SendSlopeCredit" ="num:i(round($SendSlopeCredit * num:i(1024)))"!][!//
                              [!VAR "HiCreditValue" ="$HiCreditValue * num:i(1024)"!][!//
                              [!IF "$LoCreditValue > num:i(0)"!][!//
                                [!VAR "LoCreditValue" ="($MaxValue - ($LoCreditValue * num:i(1024)))"!][!//
                              [!ENDIF!][!//
                              [!VAR "TxQueueMode" ="num:inttohex(1)"!][!//
                            [!ENDIF!][!//
                          [!ENDFOR!][!//
                        [!ELSE!][!//
                          [!IF "node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerAlgorithm) = 'ETH_SCHEDULER_STRICT_PRIORITY'"!][!//
                            [!VAR "IdleSlopeCredit" ="num:i(0)"!][!//
                          [!ELSE!][!//
                            [!FOR "Count1" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
                              [!VAR "SplitStr" = "text:split($FifoOrderString,'@')[num:i($Count1)]"!][!//
                              [!VAR "Index" = "text:split($SplitStr,',')[num:i(1)]"!][!//
                              [!IF "num:i($Index) = num:i($EgressFifo)"!][!//
                                [!VAR "IdleSlopeCredit" = "num:i(text:split($SplitStr,',')[num:i(3)])"!][!//
                                [!VAR "EgressQueueSize" = "text:split($FinalAlloc,' ')[num:i($PredecessorMax) - num:i($PredOrder)]"!][!//
                                [!BREAK!][!//
                              [!ENDIF!][!//
                            [!ENDFOR!][!//
                          [!ENDIF!][!//
                          [!VAR "SendSlopeCredit" ="num:i(0)"!][!//
                          [!VAR "HiCreditValue" ="num:i(0)"!][!//
                          [!VAR "LoCreditValue" ="num:i(0)"!][!//
                          [!VAR "TxQueueMode" ="num:inttohex(2)"!][!//
                        [!ENDIF!][!//
                        [!VAR "EgressFifoBufLenByte" = "num:i(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[EthCtrlConfigEgressFifoIdx = num:i($EgressFifo)]/EthCtrlConfigEgressFifoBufLenByte)"!][!//
                        [!VAR "EgressFifoBufLenByteAligned" = "num:i(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[EthCtrlConfigEgressFifoIdx = num:i($EgressFifo)]/EthCtrlConfigEgressFifoBufLenByte)"!][!//
                        [!VAR "RxBufQuotient" = "num:i($EgressFifoBufLenByteAligned) div 8"!][!//
                        /*Checking if configured RxLengthByte is a multiple of 8 or not*/
                        [!IF "num:i($EgressFifoBufLenByteAligned) mod 8 != 0"!][!//
                          /*if configured value for RxLengthByte is not a multiple of 8 assign the next
                          multiple of 8 to variable EthCtrlRxBufLenBytevalue*/
                          [!VAR "EgressFifoBufLenByteAligned" = "num:i((num:i($RxBufQuotient) + 1) * 8)"!][!//
                        [!ENDIF!][!//
                        [!VAR "EgressFifoBufTotal" = "num:i(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[EthCtrlConfigEgressFifoIdx = num:i($EgressFifo)]/EthCtrlConfigEgressFifoBufTotal)"!][!//
                        [!FOR "Count1" = "num:i(1)" TO "num:i($PredecessorMax)"!][!//
                          [!VAR "SplitStr" = "text:split($FifoOrderString,'@')[num:i($Count1)]"!][!//
                          [!VAR "Index" = "text:split($SplitStr,',')[num:i(1)]"!][!//
                          [!IF "num:i($Index) = num:i($EgressFifo)"!][!//
                            [!VAR "PredOrder" = "text:split($SplitStr,',')[num:i(2)]"!][!//
                            [!VAR "EgressQueueSize" = "text:split($FinalAlloc,' ')[num:i($PredecessorMax) - num:i($PredOrder)]"!][!//
                            [!VAR "EgressQueueSize" = "num:i(num:i($EgressQueueSize) - num:i(1))"!][!//
                            [!BREAK!][!//
                          [!ENDIF!][!//
                        [!ENDFOR!][!//
                      [!ENDIF!][!//
                    [!ENDNOCODE!][!//
                    [!IF "$TempVal = num:i(0)"!][!//
                      [!INDENT "2"!][!//
                      {
                        [!INDENT "4"!][!//
                        /* HiCredit Value */
                        (uint32)[!"num:inttohex($HiCreditValue)"!]U,
                        /* LoCredit Value */
                        (uint32)[!"num:inttohex($LoCreditValue)"!]U,
                        /* Egress Fifo buffer total */
                        (uint16)[!"$EgressFifoBufTotal"!]U,
                        /* Egress Fifo length byte */
                        (uint16)[!"$EgressFifoBufLenByte"!]U,
                        /* Egress Fifo length byte aligned */
                        (uint16)[!"$EgressFifoBufLenByteAligned"!]U,
                        /* Idle Slope Credit Value or
                           Configured weight for WRR algorithm */
                        (uint16)[!"num:inttohex($IdleSlopeCredit)"!]U,
                        /* Send Slope Credit Value */
                        (uint16)[!"num:inttohex($SendSlopeCredit)"!]U,
                        /* Egress Fifo Index*/
                        (uint8)[!"$EgressFifoIdx"!]U,
                        /* DMA Channel Weight */
                        (uint8)[!"$DmaChnlWeight"!]U,
                        /* Egress Queue Mode */
                        (uint8)[!"$TxQueueMode"!]U,
                        /* Egress Queue Size */
                        (uint8)[!"num:inttohex($EgressQueueSize)"!]U
                        [!ENDINDENT!][!//
                      }[!IF "$EgressFifo < num:i($PredecessorMax) - num:i(1)"!],[!ENDIF!][!CR!]
                      [!ENDINDENT!][!//
                    [!ENDIF!][!//
                  [!ENDFOR!][!//
                };
              [!ENDIF!][!//
            [!ELSE!][!//
              /* Priority to FIFO index mapping */
              /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
              [!IF "var:defined('postBuildVariant')"!][!//
                static const uint8 Eth_17_GEthMacV2_TxPrioFifoMapCtrl[!"$ControllerID"!]_[!"$postBuildVariant"!][[!"num:i($MaxPriority)"!]] =
              [!ELSE!][!//
                static const uint8 Eth_17_GEthMacV2_TxPrioFifoMapCtrl[!"$ControllerID"!][[!"num:i($MaxPriority)"!]] =
              [!ENDIF!][!//
              {
                [!INDENT "2"!][!//
                [!FOR "Priority" = "num:i(0)" TO "num:i($MaxPriority) - num:i(1)"!][!//
                  [!"num:inttohex(num:i(255))"!]U[!IF "$Priority < num:i($MaxPriority) - num:i(1)"!],[!ENDIF!][!CR!]
                [!ENDFOR!][!//
                [!ENDINDENT!][!//
              };

              [!/*[cover parentID={56D3B569-6949-4430-B304-15AA2E0FA00F}][/cover]*/!][!//
              /* Channel to Egress FIFO Mapping */
              /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
              [!IF "var:defined('postBuildVariant')"!][!//
                  static const uint8 Eth_17_GEthMacV2_TxChnlFifoMapCtrl[!"$ControllerID"!]_[!"$postBuildVariant"!][4] =
              [!ELSE!][!//
                  static const uint8 Eth_17_GEthMacV2_TxChnlFifoMapCtrl[!"$ControllerID"!][4] =
              [!ENDIF!][!//
              {
              [!INDENT "2"!][!//
                [!FOR "Count1" = "num:i(1)" TO "num:i(4)"!][!//
                  [!"num:i(255)"!]U[!IF "$Count1 < num:i(4)"!],[!ENDIF!][!CR!]
                [!ENDFOR!][!//
              [!ENDINDENT!][!//
              };
            [!ENDIF!][!//

            /* Channel to Ingress FIFO Mapping */
            [!VAR "ConfiguredFifoIngress" = "num:i(0)"!][!//
            [!VAR "InFifoOrderString" ="''"!][!//
            [!VAR "PriorityString" ="''"!][!//
            [!VAR "IngressFifoIdx" ="num:i(0)"!][!//
            [!VAR "PriorityCnt" = "num:i(0)"!][!//
            [!VAR "Flag" ="num:i(0)"!][!//
            [!VAR "ConfiguredFifoIngress" = "num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*))"!][!//
            /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            [!IF "var:defined('postBuildVariant')"!][!//
                static const uint8 Eth_17_GEthMacV2_RxChnlFifoMapCtrl[!"$ControllerID"!]_[!"$postBuildVariant"!][4] =
            [!ELSE!][!//
                static const uint8 Eth_17_GEthMacV2_RxChnlFifoMapCtrl[!"$ControllerID"!][4] =
            [!ENDIF!][!//
            {
            [!INDENT "2"!][!//
            [!IF "$ConfiguredFifoIngress > num:i(0)"!][!//
              [!FOR "IngressFifo" = "num:i(0)" TO "num:i($ConfiguredFifoIngress) - num:i(1)"!][!//
                [!IF "node:exists(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]) = 'true'"!][!//
                  [!VAR "IngressFifoIdx" = "node:value(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoIdx)"!][!//
                  [!VAR "PriorityCnt" = "num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoPriorityAssignment/*))"!][!//
                  [!IF "$PriorityCnt > num:i(0)"!][!//
                    [!VAR "Priority" = "num:max(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifoIdx)]/EthCtrlConfigIngressFifoPriorityAssignment/*)"!][!//
                  [!ELSE!][!//
                    [!VAR "Priority" = "num:i(7)"!][!//
                  [!ENDIF!][!//
                  [!VAR "InBufTotal" = "node:value(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifoIdx)]/EthCtrlConfigIngressFifoBufTotal)"!][!//
                  [!VAR "InBufLength" = "node:value(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifoIdx)]/EthCtrlConfigIngressFifoBufLenByte)"!][!//
                  [!IF "(num:i($InBufTotal) = num:i(0)) or (num:i($InBufLength) = num:i(0))"!][!//
                    [!ERROR!][!//
                      The ingress FIFO buffer length and buffer size should not be zero for successful reception of packets. If the ingress FIFO is not required for reception, delete the ingress container having FIFO index [!"num:i($IngressFifoIdx)"!] for controller [!"./EthCtrlIdx"!].
                    [!ENDERROR!][!//
                  [!ENDIF!][!//
                  [!IF "num:i($InBufLength) <= num:i(18)"!][!//
                    [!ERROR!][!//
                      The ingress FIFO buffer length configured should be greater than 18 bytes as the length of 18 bytes are consumed by Header and FCFS fields of Ethernet packets. Modify accordingly the FIFO buffer length of ingress FIFO having FIFO index [!"num:i($IngressFifoIdx)"!] for controller [!"./EthCtrlIdx"!].
                    [!ENDERROR!][!//
                  [!ENDIF!][!//
                  [!VAR "InFifoOrderString" = "concat($InFifoOrderString,$IngressFifoIdx,',',$Priority,',',$InBufTotal,',',$InBufLength,'@')"!][!//
                [!ENDIF!][!//
              [!ENDFOR!][!//
              [!VAR "Split1" = "$InFifoOrderString"!][!//
              [!VAR "VTempReplceStr1" = "'String1'"!][!//
              [!VAR "VTempReplceStr2" = "'String2'"!][!//
              [!FOR "Count" = "num:i(1)" TO "num:i($ConfiguredFifoIngress)"!][!//
                [!FOR "Count1" = "num:i(1)" TO "num:i($ConfiguredFifoIngress)- num:i($Count)"!][!//
                  [!VAR "Split" = "text:split($Split1,'@')[num:i($Count1)]"!][!//
                  [!VAR "Temp2" = "text:split($Split1,'@')[num:i($Count1) + num:i(1)]"!][!//
                  [!VAR "Index" = "text:split($Split,',')[num:i(1)]"!][!//
                  [!VAR "Priority1" = "text:split($Split,',')[num:i(2)]"!][!//
                  [!VAR "Priority2" = "text:split($Temp2,',')[num:i(2)]"!][!//
                  [!IF "$Priority1 > $Priority2"!][!//
                    [!VAR "Split1" = "text:replace($Split1,$Split,$VTempReplceStr1)"!][!//
                    [!VAR "Split1" = "text:replace($Split1,$Temp2,$VTempReplceStr2)"!][!//
                    [!VAR "Split1" = "text:replace($Split1,$VTempReplceStr2,$Split)"!][!//
                    [!VAR "Split1" = "text:replace($Split1,$VTempReplceStr1,$Temp2)"!][!//
                  [!ENDIF!][!//
                [!ENDFOR!][!//
              [!ENDFOR!][!//
              [!FOR "Count" = "num:i(1)" TO "num:i($ConfiguredFifoIngress)"!][!//
                [!VAR "Split_2" = "text:split($Split1,'@')[num:i($Count)]"!][!//
                [!VAR "Index" = "text:split($Split_2,',')[num:i(1)]"!][!//
                [!VAR "Flag" ="$Flag + num:i(1)"!][!//
                [!"$Index"!]U[!IF "$Flag < num:i(4)"!],[!ENDIF!][!CR!]
              [!ENDFOR!][!//
              [!IF "$ConfiguredFifoIngress < num:i(4)"!][!//
                [!FOR "Count" = "num:i($Count+num:i(1))" TO "num:i(4)"!][!//
                  [!"num:i(255)"!]U[!IF "$Count < num:i(4)"!],[!ENDIF!][!CR!]
                [!ENDFOR!][!//
              [!ENDIF!][!//
            [!ELSE!][!//
              [!FOR "Count" = "num:i(1)" TO "num:i(4)"!][!//
                [!"num:i(255)"!]U[!IF "$Count < num:i(4)"!],[!ENDIF!][!CR!]
              [!ENDFOR!][!//
            [!ENDIF!][!//
            [!ENDINDENT!][!//
            };

            [!VAR "Flag" ="num:i(0)"!][!//
            [!IF "$ConfiguredFifoIngress > num:i(0)"!][!//
            [!/*[cover parentID={DE09BE73-93A5-4aa5-BF37-C1DCEC077823}][/cover]*/!][!//
            /* Fifo Ingress to Queue Mapping */
            /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            [!IF "var:defined('postBuildVariant')"!][!//
              static const uint8 Eth_17_GEthMacV2_RxFifoChnlMapCtrl[!"$ControllerID"!]_[!"$postBuildVariant"!] [[!"num:i($ConfiguredFifoIngress)"!]] =
            [!ELSE!][!//
              static const uint8 Eth_17_GEthMacV2_RxFifoChnlMapCtrl[!"$ControllerID"!] [[!"num:i($ConfiguredFifoIngress)"!]] =
            [!ENDIF!][!//
            {
              [!INDENT "2"!][!//
              [!FOR "Count1" = "num:i(0)" TO "num:i($ConfiguredFifoIngress) - num:i(1)"!][!//
                [!FOR "Count" = "num:i(0)" TO "num:i($ConfiguredFifoIngress) - num:i(1)"!][!//
                  [!VAR "Split" = "text:split($Split1,'@')[num:i($Count) + num:i(1)]"!][!//
                  [!VAR "Index" = "text:split($Split,',')[num:i(1)]"!][!//
                  [!IF "$Index = $Count1"!][!//
                    [!VAR "Flag" ="$Flag + num:i(1)"!][!//
                    [!"$Count"!]U[!IF "$Flag < num:i($ConfiguredFifoIngress)"!],[!ENDIF!][!CR!]
                    [!BREAK!][!//
                  [!ENDIF!][!//
                [!ENDFOR!][!//
              [!ENDFOR!][!//
              [!ENDINDENT!][!//
            };
            [!ENDIF!][!//

          [!VAR "IngressFifoConfigured" = "num:i(0)"!][!//
          [!VAR "PriorityConfigured" = "num:i(0)"!][!//
          [!VAR "PriorityValue" = "num:i(0)"!][!//
          [!VAR "PriorityCount" = "num:i(0)"!][!//
          [!VAR "IngressFifoConfigured" = "num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*))"!][!//
          [!IF "$IngressFifoConfigured > num:i(0)"!][!//
            [!/*[cover parentID={C3A0ACC0-58A6-4a39-8660-4C8939022FF5}][/cover]*/!][!//
            /* Ingress FIFO configuration */
             [!IF "var:defined('postBuildVariant')"!][!//
              static const Eth_17_GEthMacV2_RxFifoCfgType Eth_17_GEthMacV2_RxFifoCfgCtrl[!"$ControllerID"!]_[!"$postBuildVariant"!][[!"num:i($IngressFifoConfigured)"!]] =
            [!ELSE!][!//
              static const Eth_17_GEthMacV2_RxFifoCfgType Eth_17_GEthMacV2_RxFifoCfgCtrl[!"$ControllerID"!][[!"num:i($IngressFifoConfigured)"!]] =
            [!ENDIF!][!//
            {
              [!FOR "IngressFifo" = "num:i(0)" TO "num:i($IngressFifoConfigured) - num:i(1)"!][!//
              [!NOCODE!][!//
                [!VAR "PriorityConfigured" = "num:i(0)"!][!//
                [!VAR "IngressFifoIdx" = "num:i(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoIdx)"!][!//
                [!VAR "IngressFifoBufLenByte" = "num:i(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoBufLenByte)"!][!//
                [!VAR "IngressFifoBufLenByteAligned" = "num:i(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoBufLenByte)"!][!//
                [!VAR "RxBufQuotient" = "num:i($IngressFifoBufLenByteAligned) div 8"!][!//
                  /*Checking if configured RxLengthByte is a muliple of 8 0r not*/
                  [!IF "num:i($IngressFifoBufLenByteAligned) mod 8 != 0"!][!//
                    /*if configured value for RxLengthByte is not a multiple of 8 assign the next
                    multiple of 8 to variable EthCtrlRxBufLenBytevalue*/
                    [!VAR "IngressFifoBufLenByteAligned" = "num:i((num:i($RxBufQuotient) + 1) * 8)"!][!//
                  [!ENDIF!][!//
                [!VAR "IngressFifoBufTotal" = "num:i(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoBufTotal)"!][!//
                [!VAR "PriorityCount" = "num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoPriorityAssignment/*))"!][!//
                [!IF "$PriorityCount != num:i(0)"!][!//
                  [!FOR "Priority" = "num:i(1)" TO "num:i($PriorityCount)"!][!//
                    [!VAR "PriorityValue" = "EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoPriorityAssignment/*[num:i($Priority)]"!][!//
                    [!VAR "PriorityConfigured" = "bit:or($PriorityConfigured,bit:shl(num:i(1),$PriorityValue))"!][!//
                  [!ENDFOR!][!//
                [!ELSE!][!//
                  [!VAR "PriorityConfigured" = "num:i(255)"!][!//
                [!ENDIF!][!//
                [!/* Algorithm to calculate Egress Queue Size */!][!//
                [!VAR "InBufTotArr" = "''"!][!//
                [!VAR "InBufLenArr" = "''"!][!//
                [!VAR "InInitArr" = "'1 1 1 1'"!][!//
                [!CALL "Sorting","SortArray" = "$Split1","VItem" = "num:i(2)","VTotalNum" = "$IngressFifoConfigured","VDrctn" = "num:i(-1)"!][!//
                [!VAR "InFifoOrdSortedStr" = "$SortArray"!][!//
                [!FOR "vCount" = "num:i(1)" TO "num:i($IngressFifoConfigured)"!][!//
                  [!VAR "InSplit" = "text:split($InFifoOrdSortedStr,'@')[num:i($vCount)]"!][!//
                  [!VAR "InBufTotArr" = "concat($InBufTotArr,text:split($InSplit,',')[num:i(3)],' ')"!][!//
                  [!VAR "InBufLen" = "text:split($InSplit,',')[num:i(4)]"!][!//
                  [!IF "num:i($InBufLen) mod 256 != 0"!][!//
                    [!VAR "VQuotient" = "num:i($InBufLen) div 256"!][!//
                    [!VAR "InBufLen" = "(num:i($VQuotient) + 1) * 256"!][!//
                  [!ENDIF!][!//
                  [!VAR "InBufLen" = "num:i(num:i($InBufLen) div 256)"!][!//
                  [!VAR "InBufLenArr" = "concat($InBufLenArr,$InBufLen,' ')"!][!//
                [!ENDFOR!][!//
                [!VAR "InQueueSize" = "num:i(32)"!][!//
                [!VAR "NewInInitArr" = "$InInitArr"!][!//
                [!FOR "$VLoop" = "num:i(0)" TO "num:i($InQueueSize)"!][!//
                  [!VAR "NewInInitArr" = "''"!][!//
                  [!FOR "VLoop2" = "num:i(1)" TO "num:i($IngressFifoConfigured)"!][!//
                    [!VAR "VBufTotArElem" = "text:split($InBufTotArr,' ')[num:i($VLoop2)]"!][!//
                    [!VAR "VInitArrElem" = "text:split($InInitArr,' ')[num:i($VLoop2)]"!][!//
                    [!IF "num:i($VBufTotArElem)-num:i($VInitArrElem) > num:i(0)"!][!//
                      [!VAR "VNewInitArrElem" =  "num:i($VInitArrElem) + num:i(1)"!][!//
                      [!VAR "NewInInitArr" = "concat($NewInInitArr,num:i($VNewInitArrElem),' ')"!][!//
                    [!ELSE!][!//
                      [!VAR "NewInInitArr" = "concat($NewInInitArr,num:i($VInitArrElem),' ')"!][!//
                    [!ENDIF!][!//
                  [!ENDFOR!][!//
                  [!VAR "MulRes" = "num:mul(text:split($InBufLenArr),text:split($NewInInitArr))"!][!//
                  [!VAR "MulRes" = "text:join(text:split($MulRes, ','), ' ')"!][!//
                  [!VAR "MulRes" = "substring-before(substring-after($MulRes, '['),']')"!][!//
                  [!CALL "SumElem","SumArray"="$MulRes","VNumElem"="num:i($IngressFifoConfigured)","SumVal"="num:i(0)"!][!//
                  [!VAR "SumMulElem" = "$SumVal"!][!//
                  [!IF "(num:i($SumMulElem) = num:i($InQueueSize))"!][!//
                    [!VAR "InInitArr" = "$NewInInitArr"!][!//
                    [!VAR "InFinalAlloc" = "$MulRes"!][!//
                    [!BREAK!][!//
                  [!ELSEIF "(num:i($SumMulElem) > num:i($InQueueSize))"!][!//
                    [!VAR "MulRes" = "num:mul(text:split($InBufLenArr),text:split($InInitArr))"!][!//
                    [!VAR "MulRes" = "text:join(text:split($MulRes, ','), ' ')"!][!//
                    [!VAR "MulRes" = "substring-before(substring-after($MulRes, '['),']')"!][!//
                    [!VAR "InFinalAlloc" = "$MulRes"!][!//
                    [!FOR "VLoop3" = "num:i(1)" TO "num:i(2)"!][!//
                      [!FOR "VLoop4" = "num:i(1)" TO "num:i($IngressFifoConfigured)"!][!//
                        [!VAR "VInitArrGetElem" = "num:i(text:split($InFinalAlloc,' ')[num:i($VLoop4)])"!][!//
                        [!VAR "VInitArrGetElem" = "num:i($VInitArrGetElem + (num:i(1)))"!][!//
                        [!VAR "InFinalAlloc" = "concat(substring-before($InFinalAlloc, text:split($InFinalAlloc,' ')[num:i($VLoop4)]),$VInitArrGetElem,substring-after($InFinalAlloc, text:split($InFinalAlloc,' ')[num:i($VLoop4)]))"!][!//
                        [!CALL "SumElem","SumArray"="$InFinalAlloc","VNumElem"="num:i($IngressFifoConfigured)","SumVal"="num:i(0)"!][!//
                        [!IF "$SumVal = num:i($InQueueSize)"!][!//
                          [!BREAK!][!//
                        [!ENDIF!][!//
                      [!ENDFOR!][!//
                      [!IF "$SumVal = num:i($InQueueSize)"!][!//
                        [!BREAK!][!//
                      [!ENDIF!][!//
                    [!ENDFOR!][!//
                    [!BREAK!][!//
                  [!ELSEIF "(contains($InInitArr, $InBufTotArr))"!][!//
                    [!VAR "MulRes" = "num:mul(text:split($InBufLenArr),text:split($InInitArr))"!][!//
                    [!VAR "MulRes" = "text:join(text:split($MulRes, ','), ' ')"!][!//
                    [!VAR "MulRes" = "substring-before(substring-after($MulRes, '['),']')"!][!//
                    [!CALL "SumElem","SumArray"="$MulRes","VNumElem"="num:i($IngressFifoConfigured)","SumVal"="num:i(0)"!][!//
                    [!VAR "VInitArrFirstElem" = "num:i(text:split($MulRes,' ')[num:i(1)])"!][!//
                    [!VAR "VInitArrFirstElem" = "num:i($VInitArrFirstElem + (num:i($InQueueSize)-num:i($SumVal)))"!][!//
                    [!VAR "InFinalAlloc" = "concat($VInitArrFirstElem,substring-after($MulRes, text:split($MulRes,' ')[num:i(1)]))"!][!//
                    [!BREAK!][!//
                  [!ELSE!][!//
                    [!VAR "InInitArr" = "$NewInInitArr"!]
                  [!ENDIF!][!//
                [!ENDFOR!][!//
                [!FOR "Count1" = "num:i(1)" TO "num:i($IngressFifoConfigured)"!][!//
                  [!VAR "SplitStr" = "text:split($InFifoOrdSortedStr,'@')[num:i($Count1)]"!][!//
                  [!VAR "Index" = "text:split($SplitStr,',')[num:i(1)]"!][!//
                  [!IF "num:i($Index) = num:i($IngressFifo)"!][!//
                    [!VAR "IngressQueueSize" = "text:split($InFinalAlloc,' ')[num:i($Count1)]"!][!//
                    [!VAR "IngressQueueSize" = "num:i(num:i($IngressQueueSize) - num:i(1))"!][!//
                    [!BREAK!][!//
                  [!ENDIF!][!//
                [!ENDFOR!][!//
                [!ENDNOCODE!][!//
                [!INDENT "2"!][!//
                {
                  [!INDENT "4"!][!//
                  /*Ingress Fifo buffer total */
                  (uint16)[!"$IngressFifoBufTotal"!]U,
                  /* Ingress Fifo length byte */
                  (uint16)[!"$IngressFifoBufLenByte"!]U,
                  /* Ingress Fifo length byte aligned */
                  (uint16)[!"$IngressFifoBufLenByteAligned"!]U,
                  /* Ingress Fifo Index*/
                  (uint8)[!"$IngressFifoIdx"!]U,
                  /* Priority Configured for FIFO
                    (the set bits are the configured priorities) */
                  (uint8)[!"num:inttohex($PriorityConfigured, 2)"!]U,
                  /* Ingress queue size */
                  (uint8)[!"$IngressQueueSize"!]U
                  [!ENDINDENT!][!//
                }[!IF "$IngressFifo < num:i($IngressFifoConfigured) - num:i(1)"!],[!ENDIF!][!CR!]
                [!ENDINDENT!][!//
              [!ENDFOR!][!//
            };
            [!ENDIF!][!//
          [!ENDIF!][!//
        [!ENDSELECT!][!//
        [!ENDIF!][!//
      [!ENDFOR!][!//

      /*  Structure to store controller configuration data for Core[!"$CoreId"!] */
      [!/*[cover parentID={ACD39F1D-20F4-477c-8639-49326FB8D321}][/cover]*/!][!//
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      [!IF "var:defined('postBuildVariant')"!][!//
        static const Eth_17_GEthMacV2_CoreCtrlConfigType Eth_17_GEthMacV2_CoreCtrlCfgCore[!"$CoreId"!]_[!"$postBuildVariant"!][[!"num:i($MaxControllersCore)"!]]=
      [!ELSE!]
        static const Eth_17_GEthMacV2_CoreCtrlConfigType Eth_17_GEthMacV2_CoreCtrlCfgCore[!"$CoreId"!][[!"num:i($MaxControllersCore)"!]]=
      [!ENDIF!]
      {
      [!FOR "ControllerID" = "num:i(0)" TO "num:i($MaxControllers) - num:i(1)"!][!//
        [!IF "node:exists(EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]) = 'true'"!][!//
          [!SELECT "EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]"!][!//
            [!VAR "NodeName" = "node:name(.)"!][!//
            [!VAR "EthCtrlIdxTemp" = "./EthCtrlIdx"!][!//
            [!CALL "ETH_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
            [!IF "$CGAllocationResult = 'TRUE'"!][!//
              [!NOCODE!][!//
                [!VAR "EthMACAddress" = "text:replaceAll(node:value(./EthCtrlPhyAddress/*[1]),'-',':')"!][!//
                [!IF "./EthCtrlMacLayerSpeed/*[1] = 'ETH_MAC_LAYER_SPEED_10M'"!][!//
                  [!VAR "EthCntrlPortSpeedSelect" = "num:i(1)"!][!//
                [!ELSEIF "./EthCtrlMacLayerSpeed/*[1] = 'ETH_MAC_LAYER_SPEED_100M'"!][!//
                  [!VAR "EthCntrlPortSpeedSelect" = "num:i(3)"!][!//
                [!ELSE!][!//
                  [!VAR "EthCntrlPortSpeedSelect" = "num:i(0)"!][!//
                [!ENDIF!][!//

                [!IF "./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XMII' and ./EthCtrlMacLayerSubType/*[1] = 'STANDARD'"!][!//
                  [!VAR "EthCntrlMode" = "num:i(0)"!][!// /* MII MODE */[!//
                [!ELSEIF "./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XMII' and ./EthCtrlMacLayerSubType/*[1] = 'REDUCED'"!][!//
                  [!VAR "EthCntrlMode" = "num:i(4)"!][!// /* RMII MODE */[!//
                [!ELSE!][!//
                  [!VAR "EthCntrlMode" = "num:i(1)"!][!// /* RGMII MODE */ [!//
                [!ENDIF!][!//
                [!VAR "EthCntrlMode" = "bit:shl($EthCntrlMode,2)"!][!//
                [!VAR "EthCtrlProperty" = "bit:or($EthCntrlPortSpeedSelect,$EthCntrlMode)"!][!//

                [!IF "./EthOpMode = 'FULLDUPLEX'"!][!//
                  [!VAR "EthCntrlOpMode" = "num:i(1)"!][!// /* FULLDUPLEX */[!//
                [!ELSE!][!//
                  [!VAR "EthCntrlOpMode" = "num:i(0)"!][!// /* HALFDUPLEX */[!//
                [!ENDIF!][!//
                [!VAR "EthCntrlOpMode" = "bit:shl($EthCntrlOpMode,5)"!][!//
                [!VAR "EthCtrlProperty" = "bit:or($EthCtrlProperty,$EthCntrlOpMode)"!][!//

                /* Enabled/Disable Tx Interrupt*/
                [!VAR "EthInterruptEnable" = "num:i(0)"!][!//
                [!IF "./EthCtrlEnableTxInterrupt = 'true'"!][!//
                  [!VAR "EthInterruptEnable" = "bit:shl(num:i(1),6)"!][!//
                [!ENDIF!][!//
                /* Enabled/Disable Rx Interrupt*/
                [!IF "./EthCtrlEnableRxInterrupt = 'true'"!][!//
                  [!VAR "EthInterruptEnable" = "bit:or($EthInterruptEnable,bit:shl(num:i(1),7))"!][!//
                [!ENDIF!][!//
                [!VAR "EthCtrlProperty" = "bit:or($EthCtrlProperty,$EthInterruptEnable)"!][!//

                [!VAR "EthCrcStrip" = "num:i(0)"!][!//
                [!IF "./EthCtrlEnableCrcStripping = 'true'"!][!//
                  [!VAR "EthCrcStrip" = "bit:shl(num:i(1),8)"!][!//
                [!ENDIF!][!//
                [!VAR "EthCtrlProperty" = "bit:or($EthCtrlProperty,$EthCrcStrip)"!][!//

                [!VAR "EthRegWriteWaitTime" = "num:i(0)"!][!//
                [!IF "./EthCtrlMacLayerSpeed/*[1] = 'ETH_MAC_LAYER_SPEED_10M'"!][!//
                  [!VAR "EthRegWriteWaitTime" = "num:i(2400)"!][!//
                [!ELSEIF "./EthCtrlMacLayerSpeed/*[1] = 'ETH_MAC_LAYER_SPEED_100M'"!][!//
                  [!VAR "EthRegWriteWaitTime" = "num:i(240)"!][!//
                [!ELSE!][!//
                  [!VAR "EthPeripheralBusFreq" = "num:i(node:ref(../../../EthGeneral/EthPeripheralBusClock)/McuPllDistributionSettingConfig/McuSPBFrequency)"!][!//
                  [!VAR "EthRegWriteWaitTime" = "num:i(((1000000000) div num:i($EthPeripheralBusFreq)) * 6)"!][!//
                [!ENDIF!][!//

                /* Total Egress FIFO configured */
                [!VAR "EFifoConfigured" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*))"!][!//
                /* Egress FIFO Scheduled */
                [!VAR "EFifoScheduled" = "num:i(count(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerPredecessor/*))"!][!//
                /* Total Ingress FIFO configured */
                [!VAR "IFifoConfigured" = "num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*))"!][!//

                /* DMA transmit arbitration algorithm */
                [!IF "node:value(EthCtrlConfigEgress/EthCtrlConfigDMAArbitration/*[1]/EthCtrlConfigDMAArbitrationAlgorithm) = 'ETH_DMA_ARBITRATION_FIXED_PRIORITY'"!][!//
                  [!VAR "PDMATxArbitAlgo" = "num:i(0)"!][!//
                [!ELSEIF "node:value(EthCtrlConfigEgress/EthCtrlConfigDMAArbitration/*[1]/EthCtrlConfigDMAArbitrationAlgorithm) = 'ETH_DMA_ARBITRATION_WEIGHTED_STRICT_PRIORITY'"!][!//
                  [!VAR "PDMATxArbitAlgo" = "num:i(1)"!][!//
                [!ELSE!][!// Weighted Round Robin
                   [!VAR "PDMATxArbitAlgo" = "num:i(2)"!][!//
                [!ENDIF!][!//

                /* MTL Scheduling algorithm */
                [!IF "node:value(EthCtrlConfigEgress/EthCtrlConfigScheduler/*[1]/EthCtrlConfigSchedulerAlgorithm) = 'ETH_SCHEDULER_STRICT_PRIORITY'"!][!//
                  [!VAR "PSchedAlgo" = "num:i(3)"!][!//
                [!ELSE!][!//
                  [!VAR "PSchedAlgo" = "num:i(0)"!][!//
                [!ENDIF!][!//

                /* Untagged RX packets to queue routing */
                [!VAR "RefVal" = "node:refvalid(EthCtrlConfigIngress/EthCtrlConfigIngressUntaggedPktsFifoRef)"!][!//
                [!IF "$RefVal = 'false'"!][!//
                  [!VAR "UntaggedQueueNum" = "num:i(255)"!][!//
                [!ELSE!][!//
                  [!VAR "UntaggedFifoIdx" =  "node:value(node:ref(EthCtrlConfigIngress/EthCtrlConfigIngressUntaggedPktsFifoRef)/EthCtrlConfigIngressFifoIdx)"!][!//
                  [!VAR "IngressFifoConfigured" = "num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*))"!][!//
                  [!VAR "UntaggedQueueNum" = "num:i(0)"!][!//
                  [!FOR "Count" = "num:i(0)" TO "num:i($IngressFifoConfigured) - num:i(1)"!][!//
                    [!VAR "Split" = "text:split($Split1,'@')[num:i($Count) + num:i(1)]"!][!//
                    [!VAR "Index" = "text:split($Split,',')[num:i(1)]"!][!//
                    [!IF "$Index = $UntaggedFifoIdx"!][!//
                      [!VAR "UntaggedQueueNum" = "num:i($Count)"!][!//
                      [!BREAK!][!//
                    [!ENDIF!][!//
                  [!ENDFOR!][!//
                [!ENDIF!][!//

                /*Specifies the Tx/Rx clock delay in RGMII mode for skew timing*/
                [!VAR "EthTxRxSkewDelay" = "num:i(0)"!][!//
                [!IF "./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XGMII' and ./EthCtrlMacLayerSubType/*[1] = 'REDUCED'"!][!//
                  [!VAR "EthTxRxSkewDelay" = "./EthSkewTxClockDelay"!][!//
                  [!VAR "EthTxRxSkewDelay" = "bit:or($EthTxRxSkewDelay,bit:shl(num:i(./EthSkewRxClockDelay),4))"!][!//
                [!ENDIF!][!//

                /*Selects alternate input for MDIO Input Signal */
                [!VAR "EthAltInSelx" = "substring(./EthMdioAlternateInput,1,4)"!][!//
                [!IF "$EthAltInSelx = 'ALT0'"!][!//
                  [!VAR "EthMdioAltInputVal" = "num:i(0)"!][!//
                [!ELSEIF "$EthAltInSelx = 'ALT1'"!][!//
                  [!VAR "EthMdioAltInputVal" = "num:i(1)"!][!//
                [!ELSEIF "$EthAltInSelx = 'ALT2'"!][!//
                  [!VAR "EthMdioAltInputVal" = "num:i(2)"!][!//
                [!ELSEIF "$EthAltInSelx = 'ALT3'"!][!//
                  [!VAR "EthMdioAltInputVal" = "num:i(3)"!][!//
                [!ELSE!][!//
                  [!VAR "EthMdioAltInputVal" = "num:i(0)"!][!//
                [!ENDIF!][!//

                /*Selects alternate input for Receive Clock for MII/RGMII-only ALT0 for RGMII*/
                [!IF "(./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XMII' and ./EthCtrlMacLayerSubType/*[1] = 'STANDARD') or (./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XGMII' and ./EthCtrlMacLayerSubType/*[1] = 'REDUCED')"!][!//
                  [!VAR "EthRxClkInx" = "substring(./EthRxClkInput,1,4)"!][!//
                  [!IF "$EthRxClkInx = 'ALT0'"!][!//
                    [!VAR "EthRxClkInVal" = "num:i(0)"!][!//
                  [!ELSEIF "$EthRxClkInx = 'ALT1'"!][!//
                    [!VAR "EthRxClkInVal" = "num:i(4)"!][!//
                  [!ELSEIF "$EthRxClkInx = 'ALT2'"!][!//
                    [!VAR "EthRxClkInVal" = "num:i(8)"!][!//
                  [!ELSEIF "$EthRxClkInx = 'ALT3'"!][!//
                    [!VAR "EthRxClkInVal" = "num:i(12)"!][!//
                  [!ELSE!]
                    [!VAR "EthRxErrMIIInVal" = "num:i(0)"!][!//
                  [!ENDIF!][!//
                [!ELSE!]
                  [!VAR "EthRxClkInVal" = "num:i(0)"!][!//
                [!ENDIF!][!//
                [!VAR "EthGpctlRegVal" = "bit:or($EthMdioAltInputVal,$EthRxClkInVal)"!][!//

                /*Selects alternate input for Receive Error for MII. */
                [!IF "./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XMII' and ./EthCtrlMacLayerSubType/*[1] = 'STANDARD'"!][!//
                  [!VAR "EthRxErrMIIInx" = "substring(./EthRxErrMIIInput,1,4)"!][!//
                  [!IF "$EthRxErrMIIInx = 'ALT0'"!][!//
                    [!VAR "EthRxErrMIIInVal" = "num:i(0)"!][!//
                  [!ELSEIF "$EthRxErrMIIInx = 'ALT1'"!][!//
                    [!VAR "EthRxErrMIIInVal" = "num:i(1024)"!][!//
                  [!ELSEIF "$EthRxErrMIIInx = 'ALT2'"!][!//
                    [!VAR "EthRxErrMIIInVal" = "num:i(2048)"!][!//
                  [!ELSEIF "$EthRxErrMIIInx = 'ALT3'"!][!//
                    [!VAR "EthRxErrMIIInVal" = "num:i(3072)"!][!//
                  [!ELSE!]
                    [!VAR "EthRxErrMIIInVal" = "num:i(0)"!][!//
                  [!ENDIF!][!//
                [!ELSE!]
                  [!VAR "EthRxErrMIIInVal" = "num:i(0)"!][!//
                [!ENDIF!][!//
                [!VAR "EthGpctlRegVal" = "bit:or($EthGpctlRegVal,$EthRxErrMIIInVal)"!][!//

                /*Selects alternate input for Carrier Sense for MII. */
                [!IF "./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XMII' and ./EthCtrlMacLayerSubType/*[1] = 'STANDARD'"!][!//
                  [!VAR "EthCarrierSenseMIIInx" = "substring(./EthCarrierSenseMIIInput,1,4)"!][!//
                  [!IF "$EthCarrierSenseMIIInx = 'ALT0'"!][!//
                    [!VAR "EthCarrierSenseMIIInVal" = "num:i(0)"!][!//
                  [!ELSEIF "$EthCarrierSenseMIIInx = 'ALT1'"!][!//
                    [!VAR "EthCarrierSenseMIIInVal" = "num:i(16)"!][!//
                  [!ELSEIF "$EthCarrierSenseMIIInx = 'ALT2'"!][!//
                    [!VAR "EthCarrierSenseMIIInVal" = "num:i(32)"!][!//
                  [!ELSEIF "$EthCarrierSenseMIIInx = 'ALT3'"!][!//
                    [!VAR "EthCarrierSenseMIIInVal" = "num:i(48)"!][!//
                  [!ELSE!]
                    [!VAR "EthCarrierSenseMIIInVal" = "num:i(0)"!][!//
                  [!ENDIF!][!//
                [!ELSE!][!//
                  [!VAR "EthCarrierSenseMIIInVal" = "num:i(0)"!][!//
                [!ENDIF!][!//
                [!VAR "EthGpctlRegVal" = "bit:or($EthGpctlRegVal,$EthCarrierSenseMIIInVal)"!][!//

                /*Selects alternate input for Carrier Sense for MII. */
                [!IF "./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XMII' and ./EthCtrlMacLayerSubType/*[1] = 'STANDARD'"!][!//
                  [!VAR "EthRecDataValidMIIInx" = "substring(./EthRecDataValidMIIInput,1,4)"!][!//
                  [!IF "$EthRecDataValidMIIInx = 'ALT0'"!][!//
                    [!VAR "EthRecDataValidMIIInVal" = "num:i(0)"!][!//
                  [!ELSEIF "$EthRecDataValidMIIInx = 'ALT1'"!][!//
                    [!VAR "EthRecDataValidMIIInVal" = "num:i(256)"!][!//
                  [!ELSEIF "$EthRecDataValidMIIInx = 'ALT2'"!][!//
                    [!VAR "EthRecDataValidMIIInVal" = "num:i(512)"!][!//
                  [!ELSEIF "$EthRecDataValidMIIInx = 'ALT3'"!][!//
                    [!VAR "EthRecDataValidMIIInVal" = "num:i(768)"!][!//
                  [!ELSE!]
                    [!VAR "EthRecDataValidMIIInVal" = "num:i(0)"!][!//
                  [!ENDIF!][!//
                [!ELSE!][!//
                  [!VAR "EthRecDataValidMIIInVal" = "num:i(0)"!][!//
                [!ENDIF!][!//
                [!VAR "EthGpctlRegVal" = "bit:or($EthGpctlRegVal,$EthRecDataValidMIIInVal)"!][!//

                /*Selects alternate input for Transmit clock input for MII. */
                [!IF "./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XMII' and ./EthCtrlMacLayerSubType/*[1] = 'STANDARD'"!][!//
                  [!VAR "EthTxClockMIIInputCntrlx" = "substring(./EthTxClockMIIInput,1,4)"!][!//
                  [!IF "$EthTxClockMIIInputCntrlx = 'ALT0'"!][!//
                    [!VAR "EthTxClockMIIInputCntrlVal" = "num:i(0)"!][!//
                  [!ELSEIF "$EthTxClockMIIInputCntrlx = 'ALT1'"!][!//
                    [!VAR "EthTxClockMIIInputCntrlVal" = "num:i(1048576)"!][!//
                  [!ELSEIF "$EthTxClockMIIInputCntrlx = 'ALT2'"!][!//
                    [!VAR "EthTxClockMIIInputCntrlVal" = "num:i(2097152)"!][!//
                  [!ELSEIF "$EthTxClockMIIInputCntrlx = 'ALT3'"!][!//
                    [!VAR "EthTxClockMIIInputCntrlVal" = "num:i(3145728)"!][!//
                  [!ELSE!]
                    [!VAR "EthTxClockMIIInputCntrlVal" = "num:i(0)"!][!//
                  [!ENDIF!][!//
                [!ELSE!][!//
                  [!VAR "EthTxClockMIIInputCntrlVal" = "num:i(0)"!][!//
                [!ENDIF!][!//
                [!VAR "EthGpctlRegVal" = "bit:or($EthGpctlRegVal,$EthTxClockMIIInputCntrlVal)"!][!//

                /*Selects alternate input for Collision input for MII. */
                [!IF "./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XMII' and ./EthCtrlMacLayerSubType/*[1] = 'STANDARD'"!][!//
                  [!VAR "EthCollisionMIICntrlx" = "substring(./EthCollisionMII,1,4)"!][!//
                  [!IF "$EthCollisionMIICntrlx = 'ALT0'"!][!//
                    [!VAR "EthCollisionMIICntrlVal" = "num:i(0)"!][!//
                  [!ELSEIF "$EthCollisionMIICntrlx = 'ALT1'"!][!//
                    [!VAR "EthCollisionMIICntrlVal" = "num:i(64)"!][!//
                  [!ELSEIF "$EthCollisionMIICntrlx = 'ALT2'"!][!//
                    [!VAR "EthCollisionMIICntrlVal" = "num:i(128)"!][!//
                  [!ELSEIF "$EthCollisionMIICntrlx = 'ALT3'"!][!//
                    [!VAR "EthCollisionMIICntrlVal" = "num:i(192)"!][!//
                  [!ELSE!]
                    [!VAR "EthCollisionMIICntrlVal" = "num:i(0)"!][!//
                  [!ENDIF!][!//
                [!ELSE!][!//
                  [!VAR "EthCollisionMIICntrlVal" = "num:i(0)"!][!//
                [!ENDIF!][!//
                [!VAR "EthGpctlRegVal" = "bit:or($EthGpctlRegVal,$EthCollisionMIICntrlVal)"!][!//

                /*Selects alternate input for Reference clock input for RMII(50MHz). */
                [!IF "./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XMII' and ./EthCtrlMacLayerSubType/*[1] = 'REDUCED'"!][!//
                  [!VAR "EthRefClkRMIIInx" = "substring(./EthRefClkRMIIInput,1,4)"!][!//
                  [!IF "$EthRefClkRMIIInx = 'ALT0'"!][!//
                    [!VAR "EthRefClkRMIIInVal" = "num:i(0)"!][!//
                  [!ELSEIF "$EthRefClkRMIIInx = 'ALT1'"!][!//
                    [!VAR "EthRefClkRMIIInVal" = "num:i(4)"!][!//
                  [!ELSEIF "$EthRefClkRMIIInx = 'ALT2'"!][!//
                    [!VAR "EthRefClkRMIIInVal" = "num:i(8)"!][!//
                  [!ELSEIF "$EthRefClkRMIIInx = 'ALT3'"!][!//
                    [!VAR "EthRefClkRMIIInVal" = "num:i(12)"!][!//
                  [!ELSE!]
                    [!VAR "EthRefClkRMIIInVal" = "num:i(0)"!][!//
                  [!ENDIF!][!//
                [!ELSE!][!//
                  [!VAR "EthRefClkRMIIInVal" = "num:i(0)"!][!//
                [!ENDIF!][!//
                [!VAR "EthGpctlRegVal" = "bit:or($EthGpctlRegVal,$EthRefClkRMIIInVal)"!][!//

                /*Selects alternate input for Carrier Sense/Data Valid combi-signal for RMII */
                [!IF "./EthCtrlMacLayerType = 'ETH_MAC_LAYER_TYPE_XMII' and ./EthCtrlMacLayerSubType/*[1] = 'REDUCED'"!][!//
                  [!VAR "EthCRSDVRMIIInx" = "substring(./EthCRSDVRMIIInput,1,4)"!][!//
                  [!IF "$EthCRSDVRMIIInx = 'ALT0'"!][!//
                    [!VAR "EthCRSDVRMIIInVal" = "num:i(0)"!][!//
                  [!ELSEIF "$EthCRSDVRMIIInx = 'ALT1'"!][!//
                    [!VAR "EthCRSDVRMIIInVal" = "num:i(256)"!][!//
                  [!ELSEIF "$EthCRSDVRMIIInx = 'ALT2'"!][!//
                  [!VAR "EthCRSDVRMIIInVal" = "num:i(512)"!][!//
                  [!ELSEIF "EthCRSDVRMIIInx = 'ALT3'"!][!//
                  [!VAR "EthCRSDVRMIIInVal" = "num:i(768)"!][!//
                  [!ELSE!]
                  [!VAR "EthCRSDVRMIIInVal" = "num:i(0)"!][!//
                  [!ENDIF!][!//
                [!ELSE!][!//
                  [!VAR "EthCRSDVRMIIInVal" = "num:i(0)"!][!//
                [!ENDIF!][!//
                [!VAR "EthGpctlRegVal" = "bit:or($EthGpctlRegVal,$EthCRSDVRMIIInVal)"!][!//

                /*Selects alternate input for RX-Data 0 for MII and RMII-only ALT0 for RGMII*/
                [!VAR "EthReceiveData0Inx" = "substring(./EthReceiveData0Input,1,4)"!][!//
                [!IF "$EthReceiveData0Inx = 'ALT0'"!][!//
                  [!VAR "EthReceiveData0InVal" = "num:i(0)"!][!//
                [!ELSEIF "$EthReceiveData0Inx = 'ALT1'"!][!//
                  [!VAR "EthReceiveData0InVal" = "num:i(4096)"!][!//
                [!ELSEIF "$EthReceiveData0Inx = 'ALT2'"!][!//
                  [!VAR "EthReceiveData0InVal" = "num:i(8192)"!][!//
                [!ELSEIF "EthReceiveData0Inx = 'ALT3'"!][!//
                  [!VAR "EthReceiveData0InVal" = "num:i(12288)"!][!//
                [!ELSE!]
                  [!VAR "EthReceiveData0InVal" = "num:i(0)"!][!//
                [!ENDIF!][!//
                [!VAR "EthGpctlRegVal" = "bit:or($EthGpctlRegVal,$EthReceiveData0InVal)"!][!//

                /*Selects alternate input for RX-Data 1 for MII and RMII-only ALT0 for RGMII*/
                [!VAR "EthReceiveData1Inx" = "substring(./EthReceiveData1Input,1,4)"!][!//
                [!IF "$EthReceiveData1Inx = 'ALT0'"!][!//
                  [!VAR "EthReceiveData1InVal" = "num:i(0)"!][!//
                [!ELSEIF "$EthReceiveData1Inx = 'ALT1'"!][!//
                  [!VAR "EthReceiveData1InVal" = "num:i(16384)"!][!//
                [!ELSEIF "$EthReceiveData1Inx = 'ALT2'"!][!//
                  [!VAR "EthReceiveData1InVal" = "num:i(32768)"!][!//
                [!ELSEIF "EthReceiveData1Inx = 'ALT3'"!][!//
                  [!VAR "EthReceiveData1InVal" = "num:i(49152)"!][!//
                [!ELSE!]
                  [!VAR "EthReceiveData1InVal" = "num:i(0)"!][!//
                [!ENDIF!][!//
                [!VAR "EthGpctlRegVal" = "bit:or($EthGpctlRegVal,$EthReceiveData1InVal)"!][!//

                /*Selects alternate input for RX-Data 2 for MII and RMII-only ALT0 for RGMII*/
                [!VAR "EthReceiveData2Inx" = "substring(./EthReceiveData2Input,1,4)"!][!//
                [!IF "$EthReceiveData2Inx = 'ALT0'"!][!//
                  [!VAR "EthReceiveData2InVal" = "num:i(0)"!][!//
                [!ELSEIF "$EthReceiveData2Inx = 'ALT1'"!][!//
                  [!VAR "EthReceiveData2InVal" = "num:i(65536)"!][!//
                [!ELSEIF "$EthReceiveData2Inx = 'ALT2'"!][!//
                  [!VAR "EthReceiveData2InVal" = "num:i(131072)"!][!//
                [!ELSEIF "EthReceiveData2Inx = 'ALT3'"!][!//
                  [!VAR "EthReceiveData2InVal" = "num:i(196608)"!][!//
                [!ELSE!]
                  [!VAR "EthReceiveData2InVal" = "num:i(0)"!][!//
                [!ENDIF!][!//
                [!VAR "EthGpctlRegVal" = "bit:or($EthGpctlRegVal,$EthReceiveData2InVal)"!][!//

                /*Selects alternate input for RX-Data 3 for MII and RMII-only ALT0 for RGMII*/
                [!VAR "EthReceiveData3Inx" = "substring(./EthReceiveData3Input,1,4)"!][!//
                [!IF "$EthReceiveData3Inx = 'ALT0'"!][!//
                  [!VAR "EthReceiveData3InVal" = "num:i(0)"!][!//
                [!ELSEIF "$EthReceiveData3Inx = 'ALT1'"!][!//
                  [!VAR "EthReceiveData3InVal" = "num:i(262144)"!][!//
                [!ELSEIF "$EthReceiveData3Inx = 'ALT2'"!][!//
                  [!VAR "EthReceiveData3InVal" = "num:i(524288)"!][!//
                [!ELSEIF "EthReceiveData3Inx = 'ALT3'"!][!//
                  [!VAR "EthReceiveData3InVal" = "num:i(786432)"!][!//
                [!ELSE!]
                  [!VAR "EthReceiveData3InVal" = "num:i(0)"!][!//
                [!ENDIF!][!//
                [!VAR "EthGpctlRegVal" = "bit:or($EthGpctlRegVal,$EthReceiveData3InVal)"!][!//

                /* Clock configuration for MDC */
                [!VAR "EthMDCFreq" = "num:i(node:value(./EthMDCClockFrequency))"!][!//
                [!VAR "EthCSRBusFreq" = "num:i(node:ref(../../../EthGeneral/EthPeripheralBusClock)/McuPllDistributionSettingConfig/McuSPBFrequency)"!][!//
                [!VAR "EthDividerRaw" = "($EthCSRBusFreq div $EthMDCFreq)"!][!//
                [!VAR "EthDivider" = "ceiling($EthCSRBusFreq div $EthMDCFreq)"!][!//
                [!VAR "EthDividerUpdated" = "num:i(0)"!][!//
                [!IF "(($EthDivider >= num:i(4)) and ($EthDivider <= num:i(6)))"!][!//
                  [!IF "$EthDivider = num:i(4)"!][!//
                    [!VAR "EthDividerUpdated" = "num:i(4)"!][!//
                    [!VAR "EthCSRRegVal" = "num:inttohex(8)"!][!//
                  [!ELSE!][!//
                    [!VAR "EthDividerUpdated" = "num:i(6)"!][!//
                    [!VAR "EthCSRRegVal" = "num:inttohex(9)"!][!//
                  [!ENDIF!][!//
                [!ELSEIF "(($EthDivider > num:i(6)) and ($EthDivider <= num:i(8)))"!][!//
                  [!VAR "EthDividerUpdated" = "num:i(8)"!][!//
                  [!VAR "EthCSRRegVal" = "num:inttohex(10)"!][!//
                [!ELSEIF "(($EthDivider > num:i(8)) and ($EthDivider <= num:i(10)))"!][!//
                  [!VAR "EthDividerUpdated" = "num:i(10)"!][!//
                  [!VAR "EthCSRRegVal" = "num:inttohex(11)"!][!//
                [!ELSEIF "(($EthDivider > num:i(10)) and ($EthDivider <= num:i(12)))"!][!//
                  [!VAR "EthDividerUpdated" = "num:i(12)"!][!//
                  [!VAR "EthCSRRegVal" = "num:inttohex(12)"!][!//
                [!ELSEIF "(($EthDivider > num:i(12)) and ($EthDivider <= num:i(14)))"!][!//
                  [!VAR "EthDividerUpdated" = "num:i(14)"!][!//
                  [!VAR "EthCSRRegVal" = "num:inttohex(13)"!][!//
                [!ELSEIF "(($EthDivider > num:i(14)) and ($EthDivider <= num:i(16)))"!][!//
                  [!VAR "EthDividerUpdated" = "num:i(16)"!][!//
                  [!VAR "EthCSRRegVal" = "num:inttohex(14)"!][!//
                [!ELSEIF "(($EthDivider > num:i(16)) and ($EthDivider <= num:i(18)))"!][!//
                  [!VAR "EthDividerUpdated" = "num:i(18)"!][!//
                  [!VAR "EthCSRRegVal" = "num:inttohex(15)"!][!//
                [!ELSEIF "(($EthDivider > num:i(18)) and ($EthDivider <= num:i(26)))"!][!//
                  [!VAR "EthDividerUpdated" = "num:i(26)"!][!//
                  [!VAR "EthCSRRegVal" = "num:inttohex(3)"!][!//
                [!ELSEIF "(($EthDivider > num:i(26)) and ($EthDivider <= num:i(42)))"!][!//
                  [!VAR "EthDividerUpdated" = "num:i(42)"!][!//
                  [!VAR "EthCSRRegVal" = "num:inttohex(0)"!][!//
                [!ELSE!][!//
                  [!ERROR!]
                    MDCClockFrequency configured for the controller [!"$EthCtrlIdxTemp"!] is not supported by the hardware.
                  [!ENDERROR!]
                [!ENDIF!][!//
                [!VAR "EthWarningFlag" = "num:i(1)"!][!//
                [!LOOP "text:split('4 6 8 10 12 14 16 18 26 42')"!][!//
                  [!IF "$EthDividerRaw = num:i(.)"!][!//
                    [!VAR "EthWarningFlag" = "num:i(0)"!][!//
                    [!BREAK!]
                  [!ENDIF!][!//
                [!ENDLOOP!][!//
                [!IF "$EthWarningFlag = num:i(1)"!][!//
                  [!WARNING!]
                    MDC clock frequency configured is [!"$EthMDCFreq div num:i(1000000)"!] MHz for controller [!"$EthCtrlIdxTemp"!]. Nearest MDC frequency supported by hardware and generated is [!"num:i(num:i($EthCSRBusFreq) div ($EthDividerUpdated)) div num:i(1000000)"!] MHz.
                  [!ENDWARNING!]
                [!ENDIF!][!//
              [!ENDNOCODE!][!//
              [!INDENT "2"!][!//
              {
                [!INDENT "4"!][!//
                 /*Specifies the Tx[0:3]/Rx[4:7] clock delay in RGMII mode for transmit
                skew timing*/
                (uint32)[!"$EthTxRxSkewDelay"!],
                /* Element to store GETH_GPCTL register value for current controller */
                (uint32)[!"$EthGpctlRegVal"!],
                /* Recommended time(in ns) to wait for back to back register write */
                (uint32)[!"$EthRegWriteWaitTime"!],
                /* Address of Egress fifo Configuration */
                [!IF "$EFifoConfigured > num:i(0)"!][!//
                  [!IF "var:defined('postBuildVariant')"!][!//
                    Eth_17_GEthMacV2_TxFifoCfgCtrl[!"$EthCtrlIdxTemp"!]_[!"$postBuildVariant"!],
                  [!ELSE!][!//
                    Eth_17_GEthMacV2_TxFifoCfgCtrl[!"$EthCtrlIdxTemp"!],
                  [!ENDIF!][!//
                [!ELSE!][!//
                  NULL_PTR,
                [!ENDIF!][!//
                 /* Address of Egress Queue Mapping */
                [!IF "$EFifoConfigured > num:i(0)"!][!//
                  [!IF "var:defined('postBuildVariant')"!][!//
                    Eth_17_GEthMacV2_TxFifoChnlMapCtrl[!"$EthCtrlIdxTemp"!]_[!"$postBuildVariant"!],
                  [!ELSE!][!//
                    Eth_17_GEthMacV2_TxFifoChnlMapCtrl[!"$EthCtrlIdxTemp"!],
                  [!ENDIF!][!//
                [!ELSE!][!//
                  NULL_PTR,
                [!ENDIF!][!//
                /* Channel to Egress FIFO Map */
                [!IF "var:defined('postBuildVariant')"!][!//
                  Eth_17_GEthMacV2_TxChnlFifoMapCtrl[!"$EthCtrlIdxTemp"!]_[!"$postBuildVariant"!],
                [!ELSE!][!//
                  Eth_17_GEthMacV2_TxChnlFifoMapCtrl[!"$EthCtrlIdxTemp"!],
                [!ENDIF!][!//
                /* Address of fifo Priority Mapping */
                [!IF "var:defined('postBuildVariant')"!][!//
                  Eth_17_GEthMacV2_TxPrioFifoMapCtrl[!"$EthCtrlIdxTemp"!]_[!"$postBuildVariant"!],
                [!ELSE!][!//
                  Eth_17_GEthMacV2_TxPrioFifoMapCtrl[!"$EthCtrlIdxTemp"!],
                [!ENDIF!][!//
                /* Address of Ingress fifo Configuration */
                [!IF "$IFifoConfigured > num:i(0)"!][!//
                  [!IF "var:defined('postBuildVariant')"!][!//
                    Eth_17_GEthMacV2_RxFifoCfgCtrl[!"$EthCtrlIdxTemp"!]_[!"$postBuildVariant"!],
                  [!ELSE!][!//
                    Eth_17_GEthMacV2_RxFifoCfgCtrl[!"$EthCtrlIdxTemp"!],
                  [!ENDIF!][!//
                [!ELSE!][!//
                  NULL_PTR,
                [!ENDIF!][!//
                /* Address of Ingress Queue Mapping */
                [!IF "$IFifoConfigured > num:i(0)"!][!//
                  [!IF "var:defined('postBuildVariant')"!][!//
                    Eth_17_GEthMacV2_RxFifoChnlMapCtrl[!"$EthCtrlIdxTemp"!]_[!"$postBuildVariant"!],
                  [!ELSE!][!//
                    Eth_17_GEthMacV2_RxFifoChnlMapCtrl[!"$EthCtrlIdxTemp"!],
                  [!ENDIF!][!//
                [!ELSE!][!//
                  NULL_PTR,
                [!ENDIF!][!//
                [!/*[cover parentID={1B780BCE-3342-406c-A225-3AE9D941425B}][/cover]*/!][!//
                /* Channel to Ingress FIFO Map */
                [!IF "var:defined('postBuildVariant')"!][!//
                  Eth_17_GEthMacV2_RxChnlFifoMapCtrl[!"$EthCtrlIdxTemp"!]_[!"$postBuildVariant"!],
                [!ELSE!][!//
                  Eth_17_GEthMacV2_RxChnlFifoMapCtrl[!"$EthCtrlIdxTemp"!],
                [!ENDIF!][!//
                 /* Properties of Ethernet Controller
                 Bit[0] - Port Select(PS)
                   0 for 1000Mbps
                   1 for 10 or 100 Mbps
                 Bit[1] - Speed(FES)
                   0 for 10 Mbps when PS bit is 1 and 1 Gbps when PS bit is 0
                   1 for 100 Mbps when PS bit is 1
                 Bit[2:4] - PhyInterface (000-MII, 100-RMII,001-RGMII)
                 Bit[5] - Mode of the Controller [0 - HALFDUPLEX, 1- FULLDUPLEX]
                 Bit[6] - Tx Interrupt Enable/Disable [0 - Disabled, 1- Enabled]
                 Bit[7] - Rx Interrupt Enable/Disable [0 - Disabled, 1- Enabled]
                 Bit[8] - CRC Stripping Enable/Disable [0 - Disabled, 1- Enabled]
                */
                (uint16)[!"$EthCtrlProperty"!],
                /*DEM Id for Ethernet controller hardware test failure*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_ACCESS/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_ACCESS/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_ACCESS/*[1])))"!],
                [!ELSE!][!//
                  ETH_17_GETHMACV2_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                /*DEM Id for Ethernet controller Frames Lost Error*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_RX_FRAMES_LOST/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_RX_FRAMES_LOST/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_RX_FRAMES_LOST/*[1])))"!],
                [!ELSE!][!//
                  ETH_17_GETHMACV2_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                /*DEM Id for Ethernet controller Frames Alignment Error*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_ALIGNMENT/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_ALIGNMENT/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_ALIGNMENT/*[1])))"!],
                [!ELSE!][!//
                  ETH_17_GETHMACV2_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                /*DEM Id for Ethernet controller Frames CRC Error*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_CRC/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_CRC/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_CRC/*[1])))"!],
                [!ELSE!][!//
                  ETH_17_GETHMACV2_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                /*DEM Id for Ethernet controller  Undersize frame Error*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_UNDERSIZEFRAME/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_UNDERSIZEFRAME/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_UNDERSIZEFRAME/*[1])))"!],
                [!ELSE!][!//
                  ETH_17_GETHMACV2_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                /*DEM Id for Ethernet controller  Oversize frame Error*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_OVERSIZEFRAME/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_OVERSIZEFRAME/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_OVERSIZEFRAME/*[1])))"!],
                [!ELSE!][!//
                  ETH_17_GETHMACV2_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                /*DEM Id for Ethernet controller Single collision Error*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_SINGLECOLLISION/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_SINGLECOLLISION/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_SINGLECOLLISION/*[1])))"!],
                [!ELSE!][!//
                  ETH_17_GETHMACV2_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                /*DEM Id for Ethernet controller Multiple collision Error*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_MULTIPLECOLLISION/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_MULTIPLECOLLISION/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_MULTIPLECOLLISION/*[1])))"!],
                [!ELSE!][!//
                  ETH_17_GETHMACV2_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                /*DEM Id for Ethernet controller Late collision Error*/
                [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_LATECOLLISION/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_LATECOLLISION/*[1]) != ' ' )"!][!//
                  DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./EthDemEventParameterRefs/*[1]/ETH_E_LATECOLLISION/*[1])))"!],
                [!ELSE!][!//
                  ETH_17_GETHMACV2_DISABLE_DEM_REPORT,
                [!ENDIF!][!//
                /* MAC address of the controller in network byte order */
                {
                  [!INDENT "6"!][!//
                  (uint8)0x[!"text:split($EthMACAddress, ':')[position() = 1]"!]U,
                  (uint8)0x[!"text:split($EthMACAddress, ':')[position() = 2]"!]U,
                  (uint8)0x[!"text:split($EthMACAddress, ':')[position() = 3]"!]U,
                  (uint8)0x[!"text:split($EthMACAddress, ':')[position() = 4]"!]U,
                  (uint8)0x[!"text:split($EthMACAddress, ':')[position() = 5]"!]U,
                  (uint8)0x[!"text:split($EthMACAddress, ':')[position() = 6]"!]U
                  [!ENDINDENT!][!//
                },
                /* Eth Controller Index */
                (uint8)[!"$EthCtrlIdxTemp"!]U,
                /* Total Egress Queue */
                [!IF "$EFifoConfigured > num:i(0)"!][!//
                  (uint8)[!"$EFifoScheduled"!]U,
                [!ELSE!][!//
                  (uint8)[!"num:i(0)"!]U,
                [!ENDIF!][!//
                /* DMA transmit arbitration algorithm */
                (uint8)[!"$PDMATxArbitAlgo"!]U,
                /* MTL transmit scheduling algorithm */
                (uint8)[!"$PSchedAlgo"!]U,
                /* Total Ingress Queue */
                (uint8)[!"$IFifoConfigured"!]U,
                /* Queue where the untagged Rx frames are routed */
                (uint8)[!"$UntaggedQueueNum"!]U,
                /* Clock configuration for MDC */
                (uint8)[!"$EthCSRRegVal"!]U
                [!ENDINDENT!][!//
              },
              [!ENDINDENT!][!//
            [!ENDIF!][!//
          [!ENDSELECT!][!//
        [!ENDIF!][!//
      [!ENDFOR!][!//
      };

      /* Structure to store core[!"$CoreId"!] configuration data */
      [!/*[cover parentID={9A6A0128-3062-4a3f-88D9-35092CA4E7F0}][/cover]*/!][!//
      [!IF "var:defined('postBuildVariant')"!][!//
        static const Eth_17_GEthMacV2_CoreConfigType Eth_17_GEthMacV2_ConfigCore[!"$CoreId"!]_[!"$postBuildVariant"!] =
      [!ELSE!][!//
        static const Eth_17_GEthMacV2_CoreConfigType Eth_17_GEthMacV2_ConfigCore[!"$CoreId"!] =
      [!ENDIF!][!//
      {
      [!INDENT "2"!][!//
      /* Starting address of the controller configuration for core[!"$CoreId"!] */
      /* MISRA2012_RULE_11_8_JUSTIFICATION: No side effects foreseen
      * by violating this MISRA rule */
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      [!IF "var:defined('postBuildVariant')"!][!//
        (Eth_17_GEthMacV2_CoreCtrlConfigType*)Eth_17_GEthMacV2_CoreCtrlCfgCore[!"$CoreId"!]_[!"$postBuildVariant"!],
      [!ELSE!][!//
        (Eth_17_GEthMacV2_CoreCtrlConfigType*)Eth_17_GEthMacV2_CoreCtrlCfgCore[!"$CoreId"!],
      [!ENDIF!][!//
      [!"num:i($MaxControllersCore)"!]U /* Maximum controllers allocated to core[!"$CoreId"!] */
      [!ENDINDENT!][!//
      };

      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      #define ETH_17_GETHMACV2_STOP_SEC_CONFIG_DATA_QM_CORE[!"$CoreId"!]_UNSPECIFIED
      /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
         without safeguard. It complies to Autosar guidelines. */
      /* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function
        before MemMap inclusion It complies to Autosar guidelines. */
      #include "Eth_17_GEthMacV2_MemMap.h"

    [!ENDIF!][!//
  [!ENDFOR!][!//

    /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
      in generated code due to Autosar Naming constraints.*/
    /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
      in generated code due to Autosar Naming constraints.*/
    /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
      in generated code due to Autosar Naming constraints.*/
    /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
      in generated code due to Autosar Naming constraints.*/
    #define ETH_17_GETHMACV2_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
     without safeguard. It complies to Autosar guidelines. */
     /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
    guideline. */
  #include "Eth_17_GEthMacV2_MemMap.h"
  [!/*[cover parentID={72DD941C-F13B-464d-89ED-7F505C6BD96C}][/cover]*/!][!//
  [!VAR "Module" = "'ETH'"!][!//
  [!CALL "ETH_GenerateModuleMap", "Module" = "'ETH'"!][!//
  [!CALL "ETH_GetMasterCoreID"!][!//
  [!IF "var:defined('postBuildVariant')"!][!//
    const Eth_17_GEthMacV2_ConfigType Eth_17_GEthMacV2_Config_[!"$postBuildVariant"!] =
  [!ELSE!]
    const Eth_17_GEthMacV2_ConfigType Eth_17_GEthMacV2_Config =
  [!ENDIF!]
  {
  [!INDENT "2"!][!//
  /* starting address of Core<x> Configuration data */
  {
  [!INDENT "4"!][!//
  [!FOR "CoreId" = "num:i(0)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
    [!VAR "TempCoreId" = "concat('CORE',$CoreId)"!][!//
    [!VAR "MaxControllersCore" = "num:i(0)"!][!//
    [!FOR "ControllerID" = "num:i(0)" TO "num:i($MaxControllers) - num:i(1)"!][!//
      [!IF "node:exists(EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]) = 'true'"!][!//
        [!SELECT "EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]"!][!//
          [!VAR "NodeName" = "node:name(.)"!][!//
          [!VAR "EthCtrlIdx" = "./EthCtrlIdx"!][!//
          [!CALL "ETH_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
          [!IF "$CGAllocationResult = 'TRUE'"!][!//
            [!NOCODE!][!//
              [!VAR "MaxControllersCore" = "$MaxControllersCore + num:i(1)"!][!//
            [!ENDNOCODE!][!//
          [!ENDIF!][!//
        [!ENDSELECT!][!//
      [!ENDIF!][!//
    [!ENDFOR!][!//
    [!IF "$MaxControllersCore != num:i(0)"!][!//
      /* MISRA2012_RULE_11_8_JUSTIFICATION: No side effects foreseen
       * by violating this MISRA rule */
      [!IF "var:defined('postBuildVariant')"!][!//
        (Eth_17_GEthMacV2_CoreConfigType*)&Eth_17_GEthMacV2_ConfigCore[!"$CoreId"!]_[!"$postBuildVariant"!][!IF "$CoreId < num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!],[!ENDIF!][!CR!]
      [!ELSE!][!//
        (Eth_17_GEthMacV2_CoreConfigType*)&Eth_17_GEthMacV2_ConfigCore[!"$CoreId"!][!IF "$CoreId < num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!],[!ENDIF!][!CR!]
      [!ENDIF!]
       /* MISRA2012_RULE_11_8_JUSTIFICATION: No side effects foreseen
       * by violating this MISRA rule */
    [!ELSE!]
      NULL_PTR[!IF "$CoreId < num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!],[!ENDIF!][!CR!]
    [!ENDIF!]
  [!ENDFOR!]
  [!ENDINDENT!][!//
  },
  /* Address of index mapping array */
  [!IF "var:defined('postBuildVariant')"!][!//
    (uint8*)Eth_17_GEthMacV2_ControllerIndexMap_[!"$postBuildVariant"!]
  [!ELSE!][!//
    (uint8*)Eth_17_GEthMacV2_ControllerIndexMap
  [!ENDIF!][!//
    /* MISRA2012_RULE_11_8_JUSTIFICATION: No side effects foreseen
   * by violating this MISRA rule */
   [!ENDINDENT!][!//
  };

  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
  #define ETH_17_GETHMACV2_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
     without safeguard. It complies to Autosar guidelines. */
  /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
    guideline. */
  #include "Eth_17_GEthMacV2_MemMap.h"
[!ENDSELECT!][!//
[!ENDINDENT!][!//
