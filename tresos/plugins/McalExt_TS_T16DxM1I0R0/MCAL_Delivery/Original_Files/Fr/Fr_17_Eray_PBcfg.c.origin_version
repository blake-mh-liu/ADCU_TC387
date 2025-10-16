[!/*****************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2022)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Fr_17_Eray_PBcfg.c                                            **
**                                                                            **
**  VERSION   : 19.0.0                                                        **
**                                                                            **
**  DATE      : 2022-07-11                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Fr_17_Eray.bmd                                    **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={6287D8F3-9B4F-401c-AE6D-7AC1A8622359}]    **
**                                                                            **
**  DESCRIPTION  : Code template source file for Fr Driver                    **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of FlexRay Driver, AUTOSAR Release 4.2.2 **
**                     and 4.4.0                                              **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*****************************************************************************/!]
/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2022)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Fr_17_Eray_PBcfg.c                                            **
**                                                                            **
**  VERSION   : 19.0.0                                                        **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]             !!!IGNORE-LINE!!!        **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]               !!!IGNORE-LINE!!!          **
**                                                                            **
**  BSW MODULE DECRIPTION : Fr_17_Eray.bmd                                    **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Fr configuration generated out of ECUC file                **
**                                                                            **
**  SPECIFICATION(S) : Specification of FlexRay Driver, AUTOSAR Release 4.2.2 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

[!NOCODE!]
  [!INCLUDE "Fr_17_Eray.m"!][!//
[!ENDNOCODE!]

/*******************************************************************************
**  Include Section   **
*******************************************************************************/
/* Include module header File */
#include "Fr_17_Eray.h"
[!//
[!VAR "VariantsConfigured" = "num:i(0)"!][!//
[!SELECT "as:modconf('EcuC')[1]"!][!//
  [!IF "node:exists(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!][!//
    [!VAR "PredefinedVarName1" = "(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!][!//
    [!VAR "PredefinedVarName2" = "substring-after($PredefinedVarName1, "/")"!][!//
    [!VAR "PredefinedVarName3" = "substring-after($PredefinedVarName2, "/")"!][!//
    [!VAR "PredefinedVarName" = "substring-after($PredefinedVarName3, "/")"!][!//
    [!VAR "VariantsConfigured" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDSELECT!][!//

/*******************************************************************************
**  Inclusion File Check  **
*******************************************************************************/


/*******************************************************************************
**  Private Macro Definitions **
*******************************************************************************/

/*******************************************************************************
**  Private Type Definitions  **
*******************************************************************************/


/*******************************************************************************
**  Private Function Declarations **
*******************************************************************************/


/*******************************************************************************
**  Global Function Declarations   **
*******************************************************************************/

/*******************************************************************************
  Global Constant Definitions
*******************************************************************************/
[!NOCODE!]
  /* macro values for  FrIfGdSampleClockPeriod */
  #define T12_5NS ((uint8)0)
  #define T25NS   ((uint8)1)
  #define T50NS   ((uint8)2)
  #define T100NS  ((uint8)3)
  #define T200NS  ((uint8)4)
[!ENDNOCODE!]
[!INDENT "0"!][!//
  [!/***************************MACRO - LPDU ID EXIST IN THE ARRAY**************************/!][!//
  [!NOCODE!][!//
    [!MACRO "LpduIdExist","TempArray" = "","Lpduid" = "","Count" = ""!][!//
      [!VAR "VTempstr" = "''"!][!//
      [!VAR "LpduExist" = "num:i(0)"!][!//
      [!FOR "TmpCount" = "num:i(1)" TO "num:i($Count)"!][!//
        [!VAR "VTempstr" = "text:split($TempArray,'@')[num:i($TmpCount)]"!][!//
        [!/******************Parse the second element which is LPDU idx ********/!][!//
        [!VAR "VTempstr" = "text:split($VTempstr,'#')[num:i(2)]"!][!//
        [!IF "num:i($Lpduid) = num:i($VTempstr)"!][!//
          [!VAR "LpduExist" = "num:i(1)"!][!//
          [!BREAK!][!//
        [!ENDIF!][!//
      [!ENDFOR!][!//
    [!ENDMACRO!][!//
  [!ENDNOCODE!][!//
  [!VAR "ModuleName" = "'Fr'"!][!//
  [!SELECT "as:modconf($ModuleName)[1]"!][!//
  [!//
  [!//
  [!//
  [!//
  [!/* Start of dump for Buffer Reconfiguration */!][!//
  [!VAR "MSG_RAM_SIZE_TOTAL" = "num:i(8192)"!][!//
  [!VAR "MSG_RAM_SIZE_WORDS_TOTAL" = "num:i(2048)"!][!//
  [!VAR "MSG_BUFFER_COUNT_MAX" = "num:i(128)"!][!//
  /*
  @@@@@@START_OF_BUFFER_RECONFIG_DUMP@@@@@@
  MSG_RAM_SIZE_TOTAL [!"$MSG_RAM_SIZE_TOTAL"!]
  MSG_BUFFER_COUNT_MAX [!"$MSG_BUFFER_COUNT_MAX"!]
  [!/* Dummy comment - introduced to get rid of syntax highlight issue with next line */!][!//
  [!/*************VARIABLES FOR RECONFIG ALGORITHM************/!][!//
  [!VAR "ArrKeySlotCtrl0" = "''"!][!//
  [!VAR "ArrKeySlotCtrl1" = "''"!][!//
  [!VAR "KeySlotCountCtrl0" = "num:i(0)"!][!//
  [!VAR "KeySlotCountCtrl1" = "num:i(0)"!][!//
  [!VAR "ArrFifoLpduCtrl0" = "''"!][!//
  [!VAR "ArrFifoLpduCtrl1" = "''"!][!//
  [!VAR "ArrDynamicLpduCtrl0" = "''"!][!//
  [!VAR "ArrDynamicLpduCtrl1" = "''"!][!//
  [!VAR "ArrStaticReconEnLpduCtrl0" = "''"!][!//
  [!VAR "ArrStaticReconEnLpduCtrl1" = "''"!][!//
  [!VAR "ArrStaticReconDisLpduCtrl0" = "''"!][!//
  [!VAR "ArrStaticReconDisLpduCtrl1" = "''"!][!//
  [!VAR "ArrStaticReconDisPrepLpduCtrl0" = "''"!][!//
  [!VAR "ArrStaticReconDisPrepLpduCtrl1" = "''"!][!//
  [!VAR "FifoCountCtrl0" = "num:i(0)"!][!//
  [!VAR "FifoCountCtrl1" = "num:i(0)"!][!//
  [!VAR "DynamicLpduCountCtrl0" = "num:i(0)"!][!//
  [!VAR "DynamicLpduCountCtrl1" = "num:i(0)"!][!//
  [!VAR "StaticReconEnCountCtrl0" = "num:i(0)"!][!//
  [!VAR "StaticReconEnCountCtrl1" = "num:i(0)"!][!//
  [!VAR "StaticReconDisCountCtrl0" = "num:i(0)"!][!//
  [!VAR "StaticReconDisCountCtrl1" = "num:i(0)"!][!//
  [!VAR "StaticReconDisPrepCountCtrl0" = "num:i(0)"!][!//
  [!VAR "StaticReconDisPrepCountCtrl1" = "num:i(0)"!][!//
  [!VAR "BuffReconfigReqCtrl0" = "'NO'"!][!//
  [!VAR "BuffReconfigReqCtrl1" = "'NO'"!][!//
  [!VAR "LpduExist" = "num:i(0)"!][!//
  [!VAR "FifoDepthCtrl0" = "num:i(0)"!][!//
  [!VAR "FifoDepthCtrl1" = "num:i(0)"!][!//
  [!VAR "KeyslotDlc" =  "num:i(0)"!][!//
  [!VAR "DynslotDlc" =  "num:i(0)"!][!//
  [!VAR "StaticEnRecoDlc" = "num:i(0)"!][!//
  [!VAR "StaticDisRecoDlc" = "num:i(0)"!][!//
  [!VAR "StaticDisRecoPrepDlc" = "num:i(0)"!][!//
  [!VAR "FifoDlcCtrl0" = "num:i(0)"!][!//
  [!VAR "FifoDlcCtrl1" = "num:i(0)"!][!//
  [!VAR "TmpDlc" = "num:i(0)"!][!//
  [!VAR "FifoExistCtrl0" = "num:i(0)"!][!//
  [!VAR "FifoExistCtrl1" = "num:i(0)"!][!//
  [!/***********************************************************/!][!//
  [!VAR "ConfigShortNamePath" = "as:name(FrMultipleConfiguration)"!][!//
  [!SELECT "FrMultipleConfiguration"!][!//
    [!VAR "ConfigPath" = "node:path(.)"!][!//
    [!VAR "Counter" = "num:i(count(FrController/*))"!][!//
    [!FOR "Index" = "0" TO "(num:i($Counter)- 1)"!][!//
      [!SELECT "./FrController/*[@index = $Index]"!][!//
        [!VAR "ControllerPath" = "node:path(.)"!][!//
        [!VAR "ControllerIdx" = "./FrCtrlIdx"!][!//
        [!/* Example: ControllerPath = /AUTOSAR/TOP-LEVEL-PACKAGES/Fr/ELEMENTS/Fr/FrMultipleConfiguration/FrController/FrController_0 */!][!//
        [!VAR "ControllerPath2" = "substring-after($ControllerPath, 'ELEMENTS/Fr/FrMultipleConfiguration')"!][!//
        [!/* Example: ControllerPath2 = /FrController/FrController_0 */!][!//
        [!VAR "ControllerPath1" = "substring-after($ControllerPath2, '/FrController')"!][!//
        [!/* Example: ControllerPath1 = /FrController_0 */!][!//
        [!VAR "ControllerPath2" = "concat('/', $ConfigShortNamePath)"!][!//
        [!/* Example: ControllerPath2 = /Default_0 */!][!//
        [!VAR "ControllerPath2" = "concat($ControllerPath2, $ControllerPath1)"!][!//
        [!/* Example: ControllerPath2 = /Default_0/FrController_0 */!][!//
        [!VAR "CtrlRefFound" = "num:i(0)"!][!//
        [!LOOP "as:modconf('FrIf')[1]/FrIfConfig/FrIfCluster/*"!][!/* DUMP_LOOP1 */!][!//
          [!VAR "CurrentCluster" = "node:path(.)"!][!//
          [!VAR "MacroPerCycle" = "FrIfGMacroPerCycle"!][!//
          [!VAR "NumberOfStaticSlots" = "FrIfGNumberOfStaticSlots"!][!//
          [!VAR "MSG_RAM_DYNAMIC" = "num:i(0)"!][!//
          [!/*
          [cover parentID={AC43C14F-2641-4783-B95A-DD08716D0113}] Usage of FrIf configuration containers [/cover]
          */!][!//
          [!LOOP "FrIfController/*"!][!/* DUMP_LOOP3 */!][!//
            [!VAR "FrIfControllerPath" = "node:ref(node:path(./FrIfFrCtrlRef))"!][!//
            [!VAR "FrIfControllerPath" = "substring-after($FrIfControllerPath, '/Fr/Fr')"!][!//
            [!IF "$FrIfControllerPath = $ControllerPath2"!][!/* IF1 */!][!//
            [!/************ Added for job list reference missing validation if buffer reconfiguration is needed *********/!][!//
            [!IF "num:i($ControllerIdx) = num:i(0)"!][!//
              [!VAR "Ctrl0LpduPath" = "node:path(.)"!][!//
            [!ELSEIF "num:i($ControllerIdx) = num:i(1)"!][!//
              [!VAR "Ctrl1LpduPath" = "node:path(.)"!][!//
            [!ENDIF!][!//
            [!/* ---------  Config Rule FR_CR_202 ---------*/!][!//
            [!IF "not(node:isconsecutive(FrIfLPdu/*/FrIfLPduIdx, 0))"!][!//
              [!ERROR!][!//
                Error: FrIfLPduIdx is not consecutive for [!"$ControllerPath"!].
              [!ENDERROR!][!//
            [!ENDIF!][!//
            [!/* ------------------------------------------*/!][!//
            [!VAR "SumOfLPduLengths" = "num:i(0)"!][!//
            [!/*
            [cover parentID={AC43C14F-2641-4783-B95A-DD08716D0113}] Usage of FrIf configuration containers [/cover]
            */!][!//
            [!LOOP "FrIfLPdu/*"!][!/* DUMP_LOOP9 */!][!//
              [!VAR "TmpDlc" = "num:i(node:ref(FrIfVBTriggeringRef)/FrIfLSduLength)"!][!//
              [!VAR "TmpDlc" = "num:i(ceiling($TmpDlc div num:i(4)))"!][!//
              [!VAR "SumOfLPduLengths" = "$SumOfLPduLengths + $TmpDlc"!][!//
            [!ENDLOOP!][!/* DUMP_LOOP9 */!][!//
            [!VAR "LPduCount" = "num:i(count(FrIfLPdu/*))"!][!//
            [!IF "num:i($SumOfLPduLengths + ($LPduCount * 4)) > $MSG_RAM_SIZE_WORDS_TOTAL"!][!//
              HW_BUFFER_RECONFIGURATION_USED YES, Controller Index:[!"$ControllerIdx"!] [!"num:i($SumOfLPduLengths + ($LPduCount * 4))"!] 32-bit words
            [!ELSE!][!//
              HW_BUFFER_RECONFIGURATION_USED NO, Controller Index:[!"$ControllerIdx"!] [!"num:i($SumOfLPduLengths + ($LPduCount * 4))"!] 32-bit words
            [!ENDIF!][!//
            [!//
            [!VAR "KeySlotId" = "num:i(2048)"!][!/* 2047 is maximum slot ID possible */!][!//
            [!IF "not(node:empty(concat($ControllerPath, '/FrPKeySlotId')))"!][!//
              [!VAR "KeySlotId" = "node:ref(concat($ControllerPath, '/FrPKeySlotId'))"!][!//
            [!ENDIF!][!//
            [!VAR "KeySlotLPduExists" = "num:i(0)"!][!//
            [!VAR "KeySlotLPduIdx" = "'NO_LPDU_IDX'"!][!//
            [!IF "($KeySlotId != num:i(2048)) and ($KeySlotId != num:i(0))"!][!/* Key slot Id exists */!][!//
              [!LOOP "FrIfLPdu/*"!][!/* DUMP_LOOP8 */!][!//
                [!IF "(node:ref(FrIfVBTriggeringRef)/FrIfSlotId) = $KeySlotId"!][!//
                  KEY_SLOT_LPDU,1,[!"FrIfLPduIdx"!],[!"num:i(node:ref(FrIfVBTriggeringRef)/FrIfLSduLength)"!]
                  [!VAR "KeySlotLPduIdx" = "FrIfLPduIdx"!][!//
                  [!VAR "KeySlotLPduExists" = "num:i(1)"!][!//
                  [!/*******************************************************************/!][!//
                  [!IF "num:i($ControllerIdx) = num:i(0)"!][!//
                    [!VAR "ArrKeySlotCtrl0" = "concat($ArrKeySlotCtrl0,'0#',string(FrIfLPduIdx),'#')"!][!//
                    [!VAR "TmpDlc" = "num:i(node:ref(FrIfVBTriggeringRef)/FrIfLSduLength)"!][!//
                    [!VAR "TmpDlc" = "num:i(ceiling($TmpDlc div num:i(4)))"!][!//
                    [!VAR "ArrKeySlotCtrl0" = "concat($ArrKeySlotCtrl0,string(num:i($TmpDlc)),'@')"!][!//
                    [!VAR "KeySlotCountCtrl0" = "num:i($KeySlotCountCtrl0 + num:i(1))"!][!//
                    [!IF "$KeySlotCountCtrl0 = num:i(1)"!][!//
                      [!VAR "KeySlotToLpdu" = "num:i($KeySlotLPduIdx)"!][!//
                    [!ENDIF!][!//
                    [!IF "$KeySlotCountCtrl0 > num:i(1)"!][!//
                    [!/* ---------  Config Rule FR_CR_215 ---------*/!][!//
                      [!ERROR!][!//
                        Error: LPdu index = [!"num:i($KeySlotToLpdu)"!] for controller 0 is already assigned to keyslot = [!"$KeySlotId"!], so LPdu index = [!"FrIfLPduIdx"!] to keyslot assignment is not possible.
                      [!ENDERROR!][!//
                    [!ENDIF!][!//
                  [!ENDIF!][!//
                  [!IF "num:i($ControllerIdx) = num:i(1)"!][!/************ADDED*********/!][!//
                    [!VAR "ArrKeySlotCtrl1" = "concat($ArrKeySlotCtrl1,'0#',string(FrIfLPduIdx),'#')"!][!//
                    [!VAR "TmpDlc" = "num:i(node:ref(FrIfVBTriggeringRef)/FrIfLSduLength)"!][!//
                    [!VAR "TmpDlc" = "num:i(ceiling($TmpDlc div num:i(4)))"!][!//
                    [!VAR "ArrKeySlotCtrl1" = "concat($ArrKeySlotCtrl1,string(num:i($TmpDlc)),'@')"!][!//
                    [!VAR "KeySlotCountCtrl1" = "num:i($KeySlotCountCtrl1 + num:i(1))"!][!//
                    [!IF "$KeySlotCountCtrl1 = num:i(1)"!][!//
                      [!VAR "KeySlotToLpdu" = "num:i($KeySlotLPduIdx)"!][!//
                    [!ENDIF!][!//
                    [!IF "$KeySlotCountCtrl1 > num:i(1)"!][!//
                      [!ERROR!][!//
                        Error: LPdu index = [!"num:i($KeySlotToLpdu)"!] for controller 1 is already assigned to keyslot = [!"$KeySlotId"!], so LPdu index = [!"FrIfLPduIdx"!] to keyslot assignment is not possible.
                      [!ENDERROR!][!//
                    [!ENDIF!][!//
                  [!ENDIF!][!//
                  [!/****************************************************************************/!][!//
                [!ENDIF!][!//
              [!ENDLOOP!][!/* DUMP_LOOP8 */!][!//
              [!/* ---------  Config Rule FR_CR_209 ---------*/!][!//
              [!IF "$KeySlotLPduExists != num:i(1)"!][!//
                [!ERROR!][!//
                  Error: There is no LPdu that corresponds to Key Slot ID: [!"$KeySlotId"!] for [!"$ControllerPath"!].
                [!ENDERROR!][!//
              [!ENDIF!][!//
              [!/* ------------------------------------------*/!][!//
            [!ELSE!][!//
              KEY_SLOT_LPDU,0
            [!ENDIF!][!//
            [!//
            [!IF "node:exists(concat($ControllerPath, '/FrFifo/*[1]'))"!][!//
              [!VAR "IsLpduAvailableForFifo" = "num:i(0)"!][!//
              [!/*******************************************************************************/!][!//
              [!IF "num:i($ControllerIdx) = num:i(0)"!][!/************ADDED*********/!][!//
                [!VAR "FifoDepthCtrl0" = "node:ref($ControllerPath)/FrFifo/*[1]/FrFifoDepth"!][!//
              [!ENDIF!][!//
              [!/************ADDED*********/!][!//
              [!IF "num:i($ControllerIdx) = num:i(1)"!][!//
                [!VAR "FifoDepthCtrl1" = "node:ref($ControllerPath)/FrFifo/*[1]/FrFifoDepth"!][!//
              [!ENDIF!][!//
              [!/*******************************************************************************/!][!//
              FIFO_LPDU[!//
              [!VAR "FrFifoPath" = "node:path(node:ref($ControllerPath)/FrFifo/*[1])"!][!//
              [!VAR "FifoLpduLength" = "num:i(0)"!][!//
              [!VAR "RejectStaticSegment" = "num:i(0)"!][!//
              [!IF "node:value(concat($FrFifoPath, '/FrRejectStaticSegment')) = 'true'"!][!//
                [!VAR "RejectStaticSegment" = "num:i(1)"!][!//
              [!ENDIF!][!//
              [!LOOP "FrIfLPdu/*"!][!/* DUMP_LOOP7 */!][!//
                [!VAR "RejectLpdu" = "num:i(0)"!][!//
                [!VAR "LpduChannel" = "substring-after(node:ref(FrIfVBTriggeringRef)/FrIfChannel, '_')"!][!//
                [!VAR "LpduCycleCode" = "node:ref(FrIfVBTriggeringRef)/FrIfBaseCycle + node:ref(FrIfVBTriggeringRef)/FrIfCycleRepetition"!][!//
                [!VAR "LpduFid" = "node:ref(FrIfVBTriggeringRef)/FrIfSlotId"!][!//
                [!IF "$RejectStaticSegment = num:i(1)"!][!//
                  [!IF "$LpduFid <= $NumberOfStaticSlots"!][!//
                    [!VAR "RejectLpdu" = "num:i(1)"!][!//
                  [!ENDIF!][!//
                [!ENDIF!][!//
                [!IF "$RejectLpdu = num:i(0)"!][!//
                  [!VAR "FifoChannel" = "substring-after(node:ref(concat($FrFifoPath, '/FrChannels')), '_')"!][!//
                  [!IF "$LpduChannel = $FifoChannel"!][!//
                    [!VAR "FifoCycleCode" = "node:value(node:ref(concat($FrFifoPath, '/FrBaseCycle'))) + node:value(node:ref(concat($FrFifoPath, '/FrCycleRepetition')))"!][!//
                    [!IF "$LpduCycleCode = $FifoCycleCode"!][!//
                      [!/*
                      [cover parentID={092409E7-4EC4-4722-9B23-D704B0A751EB}] Receive FIFO Functionality [/cover]
                      */!][!//
                      [!VAR "RejectionFilterID" = "num:i(node:value(node:ref(concat($FrFifoPath, '/FrFrameIdRejectionFilter'))))"!][!//
                      [!VAR "RejectionFilterMask" = "num:i(node:value(node:ref(concat($FrFifoPath, '/FrFrameIdRejectionFilterMask'))))"!][!//
                      [!VAR "RejectionFilter" = "bit:or(num:i($RejectionFilterID),num:i($RejectionFilterMask))"!][!//
                      [!VAR "RejectLpdu" = "num:i(1)"!][!//
                      [!FOR "BitPosition" = "0" TO "10"!][!/* for 11 bit FID */!][!//
                        [!VAR "getBit" = "bit:getbit(num:i($RejectionFilterMask),num:i($BitPosition))"!][!//
                        [!IF "$getBit = 'false'"!][!//
                          [!IF "$RejectLpdu = num:i(1)"!][!//
                            [!IF "bit:getbit(num:i($RejectionFilter),num:i($BitPosition)) = bit:getbit(num:i($LpduFid),num:i($BitPosition))"!][!//
                              [!VAR "RejectLpdu" = "num:i(1)"!][!//
                            [!ELSE!][!//
                              [!VAR "RejectLpdu" = "num:i(0)"!][!//
                              [!BREAK!][!//
                            [!ENDIF!][!//
                          [!ENDIF!][!//
                        [!ENDIF!][!//
                      [!ENDFOR!][!//
                      [!IF "$RejectLpdu = num:i(0)"!][!//
                        [!/***************FIFO LPDU present ***********/!][!//
                        [!VAR "IsLpduAvailableForFifo" = "num:i(1)"!][!//
                        [!IF "$FifoLpduLength = num:i(0)"!][!//
                          [!VAR "FifoLpduLength" = "num:i(node:ref(FrIfVBTriggeringRef)/FrIfLSduLength)"!][!//
                        [!ELSE!][!//
                          [!IF "$FifoLpduLength != num:i(node:ref(FrIfVBTriggeringRef)/FrIfLSduLength)"!][!//
                            [!ERROR!][!//
                              Error: FIFO data length must be same for all the FIFO LPdus, the LPdu([!"FrIfLPduIdx"!]) is configured with wrong length for [!"$ControllerPath"!].
                            [!ENDERROR!][!//
                          [!ENDIF!][!//
                        [!ENDIF!][!//
                        [!IF "FrIfLPduIdx = $KeySlotLPduIdx"!][!//
                          [!ERROR!][!//
                            Error: Keyslot LPdu can not be part of FIFO for [!"$ControllerPath"!].
                          [!ENDERROR!][!//
                        [!ENDIF!][!//
                        [!IF "node:ref(FrIfVBTriggeringRef)/FrIfAlwaysTransmit = 'true'"!][!//
                          [!VAR "LPduTxStatus" = "num:i(1)"!][!//
                        [!ELSE!][!//
                          [!VAR "LPduIdxPath" = "node:path(.)"!][!//
                          [!NOCODE!][!//
                            [!CALL "Fr_17_Eray_CG_GetLPduIdxPath", "LPduIdxPath" = "$LPduIdxPath"!][!//
                            [!CALL "Fr_17_Eray_CG_MsBufDir", "CurrentCluster" = "$CurrentCluster", "LPduIdxPath" = "$LPduIdxPath"!][!//
                          [!ENDNOCODE!][!//
                        [!ENDIF!][!//
                        [!//
                        [!IF "$LPduTxStatus = num:i(1)"!][!//
                          [!ERROR!][!//
                            Error: Only receive LPdu can be configured for FIFO, LPdu [!"FrIfLPduIdx"!] is a transmit LPdu for [!"$ControllerPath"!]
                          [!ENDERROR!][!//
                        [!ENDIF!][!//
                        ,[!"FrIfLPduIdx"!][!//
                        ,[!"num:i(node:ref(FrIfVBTriggeringRef)/FrIfLSduLength)"!][!//
                        [!IF "$LpduFid <= $NumberOfStaticSlots"!][!//
                          ,S[!//
                        [!ELSE!][!//
                          ,D[!//
                        [!ENDIF!][!//
                        [!/*
                        [cover parentID={7FA10B35-9A96-4943-9A5C-018C25CB932C}]
                        LPdus matching the FIFO filter criteria are assigned to receive FIFO [/cover]
                        */!][!//
                        [!/******************************ADDED************************/!][!//
                        [!IF "num:i($ControllerIdx) = num:i(0)"!][!//
                          [!VAR "FifoExistCtrl0" = "num:i(1)"!][!//
                          [!VAR "FifoDlcCtrl0" = "num:i(node:ref(FrIfVBTriggeringRef)/FrIfLSduLength)"!][!//
                          [!VAR "FifoDlcCtrl0" = "num:i(ceiling($FifoDlcCtrl0 div num:i(4)))"!][!//
                          [!VAR "ArrFifoLpduCtrl0" = "concat($ArrFifoLpduCtrl0,'0#',string(FrIfLPduIdx),'#')"!][!//
                          [!VAR "ArrFifoLpduCtrl0" = "concat($ArrFifoLpduCtrl0,string(num:i($FifoDlcCtrl0)),'@')"!][!//
                          [!VAR "FifoCountCtrl0" = "num:i($FifoCountCtrl0 + num:i(1))"!][!//
                        [!ENDIF!][!//
                        [!/***********************************************************/!][!//
                        [!/******************************ADDED************************/!][!//
                        [!IF "num:i($ControllerIdx) = num:i(1)"!][!//
                          [!VAR "FifoExistCtrl1" = "num:i(1)"!][!//
                          [!VAR "FifoDlcCtrl1" = "num:i(node:ref(FrIfVBTriggeringRef)/FrIfLSduLength)"!][!//
                          [!VAR "FifoDlcCtrl1" = "num:i(ceiling($FifoDlcCtrl1 div num:i(4)))"!][!//
                          [!VAR "ArrFifoLpduCtrl1" = "concat($ArrFifoLpduCtrl1,'0#',string(FrIfLPduIdx),'#')"!][!//
                          [!VAR "ArrFifoLpduCtrl1" = "concat($ArrFifoLpduCtrl1,string(num:i($FifoDlcCtrl1)),'@')"!][!//
                          [!VAR "FifoCountCtrl1" = "num:i($FifoCountCtrl1 + num:i(1))"!][!//
                        [!ENDIF!][!//
                        [!/***********************************************************/!][!//
                      [!ENDIF!][!//
                    [!ENDIF!][!//
                  [!ENDIF!][!//
                [!ENDIF!][!//
              [!ENDLOOP!][!/* DUMP_LOOP7 */!][!//
              [!IF "$IsLpduAvailableForFifo = num:i(0)"!][!//
                [!/***************If there is no FIFO LPDU present ***********/!][!//
                ,0
              [!ENDIF!][!//
              [!ENDIF!][!//
              [!//
              [!/* -----------No Dynamic LPDU configured------*/!][!//
              [!/*
              [cover parentID={AC43C14F-2641-4783-B95A-DD08716D0113}] Usage of FrIf configuration containers [/cover]
              */!][!//
              [!IF "num:i(count(FrIfFrameTriggering/*[FrIfSlotId > $NumberOfStaticSlots])) = num:i(0)"!][!//
                DYNAMIC_LPDU,0
              [!ELSE!][!//
                DYNAMIC_LPDU,[!"num:i(count(FrIfFrameTriggering/*[FrIfSlotId > $NumberOfStaticSlots]))"!]
                [!LOOP "FrIfLPdu/*"!][!/* DUMP_LOOP7 */!][!//
                  [!IF "(node:ref(FrIfVBTriggeringRef)/FrIfSlotId) > $NumberOfStaticSlots"!][!//
                    [!/* ---------  Config Rule FR_CR_211 ---------*/!][!//
                    [!IF "(node:ref(FrIfVBTriggeringRef)/FrIfChannel) = 'FRIF_CHANNEL_AB'"!][!//
                      [!ERROR!][!//
                        Error: Dynamic segment LPdu ([!"FrIfVBTriggeringRef"!]) is configured for both the channels (A and B) for [!"$ControllerPath"!].
                      [!ENDERROR!][!//
                    [!ENDIF!][!//
                    [!/* ------------------------------------------*/!][!//
                    [!"FrIfLPduIdx"!][!//
                    ,[!"num:i(node:ref(FrIfVBTriggeringRef)/FrIfLSduLength)"!]
                    [!/******************************ADDED************************/!][!//
                    [!IF "num:i($ControllerIdx) = num:i(0)"!][!//
                      [!VAR "TempLpduid" = "FrIfLPduIdx"!][!//
                      [!NOCODE!][!//
                        [!CALL "LpduIdExist","TempArray" = "$ArrFifoLpduCtrl0","Lpduid" = "$TempLpduid","Count" = "$FifoCountCtrl0"!][!//
                      [!ENDNOCODE!][!//
                      [!IF "num:i($LpduExist) = num:i(0)"!][!//
                        [!VAR "ArrDynamicLpduCtrl0" = "concat($ArrDynamicLpduCtrl0,'0#',string(FrIfLPduIdx),'#')"!][!//
                        [!VAR "TmpDlc" = "num:i(node:ref(FrIfVBTriggeringRef)/FrIfLSduLength)"!][!//
                        [!VAR "TmpDlc" = "num:i(ceiling($TmpDlc div num:i(4)))"!][!//
                        [!VAR "ArrDynamicLpduCtrl0" = "concat($ArrDynamicLpduCtrl0,string($TmpDlc),'@')"!][!//
                        [!VAR "DynamicLpduCountCtrl0" = "$DynamicLpduCountCtrl0 + num:i(1)"!][!//
                      [!ENDIF!][!//
                    [!ENDIF!][!//
                    [!//
                    [!IF "num:i($ControllerIdx) = num:i(1)"!][!//
                      [!VAR "TempLpduid" = "FrIfLPduIdx"!][!//
                      [!NOCODE!][!//
                        [!CALL "LpduIdExist","TempArray" = "$ArrFifoLpduCtrl1","Lpduid" = "$TempLpduid","Count" = "$FifoCountCtrl1"!][!//
                      [!ENDNOCODE!][!//
                      [!IF "num:i($LpduExist) = num:i(0)"!][!//
                        [!VAR "ArrDynamicLpduCtrl1" = "concat($ArrDynamicLpduCtrl1,'0#',string(FrIfLPduIdx),'#')"!][!//
                        [!VAR "TmpDlc" = "num:i(node:ref(FrIfVBTriggeringRef)/FrIfLSduLength)"!][!//
                        [!VAR "TmpDlc" = "num:i(ceiling($TmpDlc div num:i(4)))"!][!//
                        [!VAR "ArrDynamicLpduCtrl1" = "concat($ArrDynamicLpduCtrl1,string($TmpDlc),'@')"!][!//
                        [!VAR "DynamicLpduCountCtrl1" = "$DynamicLpduCountCtrl1 + num:i(1)"!][!//
                      [!ENDIF!][!//
                    [!ENDIF!][!//
                    [!/***********************************************************/!][!//
                  [!ENDIF!][!//
                [!ENDLOOP!][!/* DUMP_LOOP7 */!][!//
              [!ENDIF!][!//
              Static LPDUs for which FrIf reconfig available, length
              RECONFIG_LPDU,[!//
              [!VAR "FrIfCtrlName" = "substring-after(node:path(.), 'FrIfController/')"!][!//
              [!VAR "CommOpCount" = "num:i(0)"!][!//
              [!VAR "ReconfigLpduCount" = "num:i(0)"!][!//
              [!VAR "ReconfigLpduArr" = "''"!][!//
              [!VAR "NonReconfigLpduArr" = "''"!][!//
              [!/*
              [cover parentID={AC43C14F-2641-4783-B95A-DD08716D0113}] Usage of FrIf configuration containers [/cover]
              */!][!//
              [!LOOP "../../FrIfJobList/FrIfJob/*"!][!/* DUMP_LOOP4 */!][!//
                [!LOOP "FrIfCommunicationOperation/*"!][!/* DUMP_LOOP5 */!][!//
                  [!IF "node:empty(FrIfLPduIdxRef)"!][!//
                    [!ERROR!][!//
                      Missing reference to LPdu index for the communication operation [!"node:name(.)"!] within the FrIf Job [!"node:name(../..)"!]
                    [!ENDERROR!][!//
                  [!ENDIF!][!//
                  [!IF "contains(FrIfLPduIdxRef, $FrIfCtrlName)"!][!//
                    [!IF "num:i(node:ref(node:ref(./FrIfLPduIdxRef)/FrIfVBTriggeringRef)/FrIfSlotId) <= $NumberOfStaticSlots"!][!//
                      [!IF "node:ref(./FrIfLPduIdxRef)/FrIfLPduIdx != $KeySlotLPduIdx"!][!//
                        [!IF "node:ref(./FrIfLPduIdxRef)/FrIfReconfigurable = 'true'"!][!//
                          [!VAR "LpduFound" = "num:i(0)"!][!//
                          [!FOR "Index" = "0" TO "(num:i($ReconfigLpduCount))"!][!//
                            [!IF "node:ref(./FrIfLPduIdxRef)/FrIfLPduIdx = text:split($ReconfigLpduArr,',')[num:i($Index)]"!][!//
                              [!VAR "LpduFound" = "num:i(1)"!][!//
                              [!BREAK!][!//
                            [!ENDIF!][!//
                          [!ENDFOR!][!//
                          [!IF "$LpduFound = num:i(0)"!][!//
                            [!VAR "ReconfigLpduArr" = "concat($ReconfigLpduArr,node:ref(./FrIfLPduIdxRef)/FrIfLPduIdx,',')"!][!//
                            [!VAR "ReconfigLpduCount" = "$ReconfigLpduCount + num:i(1)"!][!//
                            [!"node:ref(./FrIfLPduIdxRef)/FrIfLPduIdx"!],[!"num:i(node:ref(node:ref(./FrIfLPduIdxRef)/FrIfVBTriggeringRef)/FrIfLSduLength)"!],
                          [!ENDIF!][!//
                          [!VAR "TempLpduid" = "node:ref(./FrIfLPduIdxRef)/FrIfLPduIdx"!][!//
                          [!IF "num:i($ControllerIdx) = num:i(0)"!][!//
                            [!NOCODE!][!//
                              [!CALL "LpduIdExist","TempArray" = "$ArrFifoLpduCtrl0","Lpduid" = "$TempLpduid","Count" = "$FifoCountCtrl0"!][!//
                            [!ENDNOCODE!][!//
                            [!IF "num:i($LpduExist) = num:i(0)"!][!//
                              [!VAR "TmpDlc" = "num:i(node:ref(node:ref(./FrIfLPduIdxRef)/FrIfVBTriggeringRef)/FrIfLSduLength)"!][!//
                              [!VAR "TmpDlc" = "num:i(ceiling($TmpDlc div num:i(4)))"!][!//
                              [!VAR "ArrStaticReconEnLpduCtrl0" = "concat($ArrStaticReconEnLpduCtrl0,'0#',string(node:ref(./FrIfLPduIdxRef)/FrIfLPduIdx),'#')"!][!//
                              [!VAR "ArrStaticReconEnLpduCtrl0" = "concat($ArrStaticReconEnLpduCtrl0,string(num:i($TmpDlc)),'@')"!][!//
                              [!VAR "StaticReconEnCountCtrl0" = "$StaticReconEnCountCtrl0 + num:i(1)"!][!//
                            [!ENDIF!][!//
                          [!ENDIF!][!//
                          [!IF "num:i($ControllerIdx) = num:i(1)"!][!//
                            [!NOCODE!][!//
                              [!CALL "LpduIdExist","TempArray" = "$ArrFifoLpduCtrl1","Lpduid" = "$TempLpduid","Count" = "$FifoCountCtrl1"!][!//
                            [!ENDNOCODE!][!//
                            [!IF "num:i($LpduExist) = num:i(0)"!][!//
                              [!VAR "TmpDlc" = "num:i(node:ref(node:ref(./FrIfLPduIdxRef)/FrIfVBTriggeringRef)/FrIfLSduLength)"!][!//
                              [!VAR "TmpDlc" = "num:i(ceiling($TmpDlc div num:i(4)))"!][!//
                              [!VAR "ArrStaticReconEnLpduCtrl1" = "concat($ArrStaticReconEnLpduCtrl1,'0#',string(node:ref(./FrIfLPduIdxRef)/FrIfLPduIdx),'#')"!][!//
                              [!VAR "ArrStaticReconEnLpduCtrl1" = "concat($ArrStaticReconEnLpduCtrl1,string(num:i($TmpDlc)),'@')"!][!//
                              [!VAR "StaticReconEnCountCtrl1" = "$StaticReconEnCountCtrl1 + num:i(1)"!][!//
                            [!ENDIF!][!//
                          [!ENDIF!][!//
                        [!ELSE!][!//
                          [!NOCODE!][!//
                            [!/* Find out if there are any LPDUs that need share message objects i.e. the
                            LPdus that are not dynamic and LPdu that corresponds to key slot id.
                            Note that IF conditions are same as used inside the forthcoming loop
                            LOOP "FrIfCommunicationOperation/*"
                            */!][!//
                          [!ENDNOCODE!][!//
                          [!VAR "LpduFound" = "num:i(0)"!][!//
                          [!FOR "Index" = "0" TO "(num:i($CommOpCount))"!][!//
                            [!IF "node:ref(./FrIfLPduIdxRef)/FrIfLPduIdx = text:split($NonReconfigLpduArr,',')[num:i($Index)]"!][!//
                              [!VAR "LpduFound" = "num:i(1)"!][!//
                              [!BREAK!][!//
                            [!ENDIF!][!//
                          [!ENDFOR!][!//
                          [!IF "$LpduFound = num:i(0)"!][!//
                            [!VAR "TempLpduid" = "node:ref(./FrIfLPduIdxRef)/FrIfLPduIdx"!][!//
                            [!IF "num:i($ControllerIdx) = num:i(0)"!][!//
                              [!NOCODE!][!//
                                [!CALL "LpduIdExist","TempArray" = "$ArrFifoLpduCtrl0","Lpduid" = "$TempLpduid","Count" = "$FifoCountCtrl0"!][!//
                              [!ENDNOCODE!][!//
                              [!IF "num:i($LpduExist) = num:i(0)"!][!//
                                [!VAR "NonReconfigLpduArr" = "concat($NonReconfigLpduArr,node:ref(./FrIfLPduIdxRef)/FrIfLPduIdx,',')"!][!//
                                [!VAR "CommOpCount" = "$CommOpCount + num:i(1)"!][!//
                                [!VAR "TmpDlc" = "num:i(node:ref(node:ref(./FrIfLPduIdxRef)/FrIfVBTriggeringRef)/FrIfLSduLength)"!][!//
                                [!VAR "TmpDlc" = "num:i(ceiling($TmpDlc div num:i(4)))"!][!//
                                [!VAR "ArrStaticReconDisLpduCtrl0" = "concat($ArrStaticReconDisLpduCtrl0,'0#',string(node:ref(./FrIfLPduIdxRef)/FrIfLPduIdx),'#')"!][!//
                                [!VAR "ArrStaticReconDisLpduCtrl0" = "concat($ArrStaticReconDisLpduCtrl0,string(num:i($TmpDlc)),'@')"!][!//
                                [!VAR "StaticReconDisCountCtrl0" = "$StaticReconDisCountCtrl0 + num:i(1)"!][!//
                              [!ENDIF!][!//
                            [!ENDIF!][!//
                            [!IF "num:i($ControllerIdx) = num:i(1)"!][!//
                              [!NOCODE!][!//
                                [!CALL "LpduIdExist","TempArray" = "$ArrFifoLpduCtrl1","Lpduid" = "$TempLpduid","Count" = "$FifoCountCtrl1"!][!//
                              [!ENDNOCODE!][!//
                              [!IF "num:i($LpduExist) = num:i(0)"!][!//
                                [!VAR "NonReconfigLpduArr" = "concat($NonReconfigLpduArr,node:ref(./FrIfLPduIdxRef)/FrIfLPduIdx,',')"!][!//
                                [!VAR "CommOpCount" = "$CommOpCount + num:i(1)"!][!//
                                [!VAR "TmpDlc" = "num:i(node:ref(node:ref(./FrIfLPduIdxRef)/FrIfVBTriggeringRef)/FrIfLSduLength)"!][!//
                                [!VAR "TmpDlc" = "num:i(ceiling($TmpDlc div num:i(4)))"!][!//
                                [!VAR "ArrStaticReconDisLpduCtrl1" = "concat($ArrStaticReconDisLpduCtrl1,'0#',string(node:ref(./FrIfLPduIdxRef)/FrIfLPduIdx),'#')"!][!//
                                [!VAR "ArrStaticReconDisLpduCtrl1" = "concat($ArrStaticReconDisLpduCtrl1,string(num:i($TmpDlc)),'@')"!][!//
                                [!VAR "StaticReconDisCountCtrl1" = "$StaticReconDisCountCtrl1 + num:i(1)"!][!//
                              [!ENDIF!][!//
                            [!ENDIF!][!//
                          [!ENDIF!][!//
                        [!ENDIF!][!//
                      [!ENDIF!][!//
                    [!ENDIF!][!//
                  [!ENDIF!][!//
                [!ENDLOOP!][!/* DUMP_LOOP5 */!][!//
              [!ENDLOOP!][!/* DUMP_LOOP4 */!][!//
              Total:[!"num:i($ReconfigLpduCount)"!]
              Number of LPDU which may share HW buffer
              STATIC_LPDU,[!//
              [!/****************LPDU for which HW reconfig available, count printed here *************/!][!//
              [!"num:i($CommOpCount)"!]
              COM_OP,macrotick,LpduIdx,Length
              [!LOOP "../../FrIfJobList/FrIfJob/*"!][!/* DUMP_LOOP4 */!][!//
                [!IF "num:i($CommOpCount) != num:i(0)"!][!//
                  [!/*
                  [cover parentID={7FA10B35-9A96-4943-9A5C-018C25CB932C}]
                  FrIf Job list cycle time and macrotick parameters are referenced for buffer reconfiguration algorithm [/cover]
                  */!][!//
                  [!VAR "TempCycle" = "num:i((FrIfCycle * $MacroPerCycle) + FrIfMacrotick)"!][!//
                  [!LOOP "FrIfCommunicationOperation/*"!][!/* DUMP_LOOP6 */!][!//
                    [!IF "FrIfCommunicationAction = 'PREPARE_LPDU'"!][!/* SWS_Fr_00003 */!][!//
                      [!IF "contains(FrIfLPduIdxRef, $FrIfCtrlName)"!][!//
                        [!/* Message buffers shared only by LPDUs meant for static segment */!][!//
                        [!IF "num:i(node:ref(node:ref(./FrIfLPduIdxRef)/FrIfVBTriggeringRef)/FrIfSlotId) <= $NumberOfStaticSlots"!][!//
                          [!IF "node:ref(./FrIfLPduIdxRef)/FrIfLPduIdx != $KeySlotLPduIdx"!][!/* LPDU corresponding to key slot */!][!//
                            [!IF "node:ref(./FrIfLPduIdxRef)/FrIfReconfigurable != 'true'"!][!//
                              [!"FrIfCommunicationAction"!][!//
                              [!/****************COM_OP macrotick printed here *********************/!][!//
                              ,[!"$TempCycle"!][!//
                              [!/****************LPDU id and Length printed here *********************/!][!//
                              ,[!"node:ref(./FrIfLPduIdxRef)/FrIfLPduIdx"!][!//
                              ,[!"num:i(node:ref(node:ref(./FrIfLPduIdxRef)/FrIfVBTriggeringRef)/FrIfLSduLength)"!]
                              [!/*******************************************ADDED*******************************/!][!//
                              [!VAR "TempLpduid" = "node:ref(./FrIfLPduIdxRef)/FrIfLPduIdx"!][!//
                              [!IF "num:i($ControllerIdx) = num:i(0)"!][!//
                                [!NOCODE!][!//
                                  [!CALL "LpduIdExist","TempArray" = "$ArrFifoLpduCtrl0","Lpduid" = "$TempLpduid","Count" = "$FifoCountCtrl0"!][!//
                                [!ENDNOCODE!][!//
                                [!IF "num:i($LpduExist) = num:i(0)"!][!//
                                [!NOCODE!][!//
                                  [!CALL "LpduIdExist","TempArray" = "$ArrStaticReconDisPrepLpduCtrl0","Lpduid" = "$TempLpduid","Count" = "$StaticReconDisPrepCountCtrl0"!][!//
                                [!ENDNOCODE!][!//
                                  [!IF "num:i($LpduExist) = num:i(0)"!][!//
                                    [!VAR "TmpDlc" = "num:i(node:ref(node:ref(./FrIfLPduIdxRef)/FrIfVBTriggeringRef)/FrIfLSduLength)"!][!//
                                    [!VAR "TmpDlc" = "num:i(ceiling($TmpDlc div num:i(4)))"!][!//
                                    [!VAR "ArrStaticReconDisPrepLpduCtrl0" = "concat($ArrStaticReconDisPrepLpduCtrl0,string($TempCycle),'#')"!][!//
                                    [!VAR "ArrStaticReconDisPrepLpduCtrl0" = "concat($ArrStaticReconDisPrepLpduCtrl0,string(node:ref(./FrIfLPduIdxRef)/FrIfLPduIdx),'#')"!][!//
                                    [!VAR "ArrStaticReconDisPrepLpduCtrl0" = "concat($ArrStaticReconDisPrepLpduCtrl0,string(num:i($TmpDlc)),'@')"!][!//
                                    [!VAR "StaticReconDisPrepCountCtrl0" = "$StaticReconDisPrepCountCtrl0 + num:i(1)"!][!//
                                    [!FOR "TmpCount" = "num:i(1)" TO "num:i($StaticReconDisCountCtrl0)"!][!//
                                      [!VAR "VTempstr" = "text:split($ArrStaticReconDisLpduCtrl0,'@')[num:i($TmpCount)]"!][!//
                                      [!/******************Parse the second element which is LPDU idx ********/!][!//
                                      [!VAR "VTempLpduIdx" = "text:split($VTempstr,'#')[num:i(2)]"!][!//
                                      [!IF "num:i($TempLpduid) = num:i($VTempLpduIdx)"!][!//
                                        [!VAR "VTempstr" = "concat($VTempstr,'@')"!][!//
                                        [!VAR "ArrStaticReconDisLpduCtrl0" = "text:replace($ArrStaticReconDisLpduCtrl0,$VTempstr,'')"!][!//
                                        [!VAR "StaticReconDisCountCtrl0" = "$StaticReconDisCountCtrl0 - num:i(1)"!][!//
                                        [!BREAK!][!//
                                      [!ENDIF!][!//
                                    [!ENDFOR!][!//
                                  [!ENDIF!][!//
                                [!ENDIF!][!//
                              [!ENDIF!][!//
                              [!IF "num:i($ControllerIdx) = num:i(1)"!][!//
                                [!NOCODE!][!//
                                  [!CALL "LpduIdExist","TempArray" = "$ArrFifoLpduCtrl1","Lpduid" = "$TempLpduid","Count" = "$FifoCountCtrl1"!][!//
                                [!ENDNOCODE!][!//
                                [!IF "num:i($LpduExist) = num:i(0)"!][!//
                                  [!NOCODE!][!//
                                    [!CALL "LpduIdExist","TempArray" = "$ArrStaticReconDisPrepLpduCtrl1","Lpduid" = "$TempLpduid","Count" = "$StaticReconDisPrepCountCtrl1"!][!//
                                  [!ENDNOCODE!][!//
                                  [!IF "num:i($LpduExist) = num:i(0)"!][!//
                                    [!VAR "TmpDlc" = "num:i(node:ref(node:ref(./FrIfLPduIdxRef)/FrIfVBTriggeringRef)/FrIfLSduLength)"!][!//
                                    [!VAR "TmpDlc" = "num:i(ceiling($TmpDlc div num:i(4)))"!][!//
                                    [!VAR "ArrStaticReconDisPrepLpduCtrl1" = "concat($ArrStaticReconDisPrepLpduCtrl1,string($TempCycle),'#')"!][!//
                                    [!VAR "ArrStaticReconDisPrepLpduCtrl1" = "concat($ArrStaticReconDisPrepLpduCtrl1,string(node:ref(./FrIfLPduIdxRef)/FrIfLPduIdx),'#')"!][!//
                                    [!VAR "ArrStaticReconDisPrepLpduCtrl1" = "concat($ArrStaticReconDisPrepLpduCtrl1,string(num:i($TmpDlc)),'@')"!][!//
                                    [!VAR "StaticReconDisPrepCountCtrl1" = "$StaticReconDisPrepCountCtrl1 + num:i(1)"!][!//
                                    [!FOR "TmpCount" = "num:i(1)" TO "num:i($StaticReconDisCountCtrl1)"!][!//
                                      [!VAR "VTempstr" = "text:split($ArrStaticReconDisLpduCtrl1,'@')[num:i($TmpCount)]"!][!//
                                      [!/******************Parse the second element which is LPDU idx ********/!][!//
                                      [!VAR "VTempLpduIdx" = "text:split($VTempstr,'#')[num:i(2)]"!][!//
                                      [!IF "num:i($TempLpduid) = num:i($VTempLpduIdx)"!][!//
                                        [!VAR "VTempstr" = "concat($VTempstr,'@')"!][!//
                                        [!VAR "ArrStaticReconDisLpduCtrl1" = "text:replace($ArrStaticReconDisLpduCtrl1,$VTempstr,'')"!][!//
                                        [!VAR "StaticReconDisCountCtrl1" = "$StaticReconDisCountCtrl1 - num:i(1)"!][!//
                                        [!BREAK!][!//
                                      [!ENDIF!][!//
                                    [!ENDFOR!][!//
                                  [!ENDIF!][!//
                                [!ENDIF!][!//
                              [!ENDIF!][!//
                            [!/*******************************************************************************/!][!//
                            [!ENDIF!][!//
                          [!ENDIF!][!//
                        [!ENDIF!][!//
                      [!ENDIF!][!//
                    [!ENDIF!][!/* SWS_Fr_00003 */!][!//
                  [!ENDLOOP!][!/* DUMP_LOOP6 */!][!//
                [!ENDIF!][!//
              [!ENDLOOP!][!/* DUMP_LOOP4 */!][!//
              [!VAR "CtrlRefFound" = "num:i(1)"!][!//
              [!BREAK!][!//
            [!ENDIF!][!/* IF1 */!][!//
          [!ENDLOOP!][!/* DUMP_LOOP3 */!][!//
          [!IF "$CtrlRefFound = 1"!]
            [!BREAK!]
          [!ENDIF!][!//
          [!IF "$CtrlRefFound = 1"!]
            [!BREAK!]
          [!ENDIF!][!//
        [!ENDLOOP!][!/* DUMP_LOOP1 */!][!//
      [!ENDSELECT!][!//
    [!ENDFOR!][!//
  [!ENDSELECT!][!//

  PB_CFG_END

  @@@@@@END_OF_BUFFER_RECONFIG_DUMP@@@@@@
  */
  [!//End of dump for BUFFER RECONFIG
  [!//
  [!//
  [!//
  [!/*
  [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
  Memory mapping for configuration data [/cover]
  */!][!//
  #define FR_17_ERAY_START_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
  /* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
  of the data or code, so included multiple times from code. This violation is an
  approved exception without side effects by AUTOSAR. */
  #include "Fr_17_Eray_MemMap.h"
  [!//
  [!SELECT "FrMultipleConfiguration"!][!//
    [!VAR "Counter" = "num:i(count(./FrController/*))"!][!//
    [!FOR "Index" = "0" TO "(num:i($Counter)- 1)"!][!//
      [!SELECT "./FrController/*[@index = $Index]"!][!//
        [!VAR "ControllerPath" = "node:path(.)"!][!//
        [!VAR "ControllerIndex" = "./FrCtrlIdx"!][!//
        [!/* Example: ControllerPath = /AUTOSAR/TOP-LEVEL-PACKAGES/Fr/ELEMENTS/Fr/FrMultipleConfiguration/FrController/FrController_0 */!][!//
        [!VAR "ControllerShortNamePath" = "substring-after($ControllerPath, 'FrController')"!][!//
        [!/* Example: ControllerShortNamePath = /FrController_0 */!][!//
        [!/* Following variable is used to terminate the loop */!][!//
        [!VAR "CtrlRefFound" = "num:i(0)"!][!//
        [!LOOP "as:modconf('FrIf')[1]/FrIfConfig/FrIfCluster/*"!][!/* RECONFIG_LOOP1 */!][!//
          [!//
          [!VAR "NumberOfStaticSlots" = "FrIfGNumberOfStaticSlots"!][!//
          [!VAR "CurrentCluster" = "node:path(.)"!][!//
          [!LOOP "FrIfController/*"!][!/* RECONFIG_LOOP2 */!][!//
            [!VAR "FrIfControllerPath" = "node:ref(node:path(./FrIfFrCtrlRef))"!][!//
            [!VAR "FrConfigPath" = "substring-after($FrIfControllerPath, '/Fr/Fr/')"!][!//
            [!VAR "FrConfigPath" = "substring-before($FrConfigPath, $ControllerShortNamePath)"!][!//
            [!VAR "FrIfControllerPath" = "substring-after($FrIfControllerPath, $FrConfigPath)"!][!//
            [!IF "$FrIfControllerPath = $ControllerShortNamePath"!][!/* RECONFIG_IF1 */!][!//
            [!VAR "SumOfLPduLengths" = "num:i(0)"!][!//
            [!LOOP "FrIfLPdu/*"!][!/* RECONFIG_LOOP3 */!][!//
              [!VAR "TmpDlc" = "num:i(node:ref(FrIfVBTriggeringRef)/FrIfLSduLength)"!][!//
              [!VAR "TmpDlc" = "num:i(ceiling($TmpDlc div num:i(4)))"!][!//
              [!VAR "SumOfLPduLengths" = "$SumOfLPduLengths + $TmpDlc"!][!//
            [!ENDLOOP!][!/* RECONFIG_LOOP3 */!][!//
            [!//
            [!//
            [!//
            [!VAR "LPduCount" = "num:i(count(FrIfLPdu/*))"!][!//
            [!VAR "MsgRAMSizeRequired" = "num:i($SumOfLPduLengths + ($LPduCount * 4))"!][!//
            [!IF "($MsgRAMSizeRequired > $MSG_RAM_SIZE_WORDS_TOTAL) or ($LPduCount > $MSG_BUFFER_COUNT_MAX)"!][!/* RECONFIG_IF2 */!][!//
              [!IF "num:i($ControllerIndex) = num:i(0)"!][!//
                [!VAR "BuffReconfigReqCtrl0" = "'YES'"!][!//
              [!ENDIF!][!//
              [!IF "num:i($ControllerIndex) = num:i(1)"!][!//
                [!VAR "BuffReconfigReqCtrl1" = "'YES'"!][!//
              [!ENDIF!][!//
              [!/*********************************************************************/!][!//
              [!/*
              Buffer Reconfiguration is required to find LPDU to message buffer mapping.
              Buffer Reconfiguration output follows.
              */!][!//
              [!/* ---------  Config Rule FR_CR_098 ---------*/!][!//
              [!IF "as:modconf($ModuleName)[1]/FrGeneral/FrPrepareLPduSupport != 'true'"!][!//
                [!ERROR!][!//
                  Error: Buffer reconfiguration is required but FrPrepareLPduSupport is OFF (false)
                [!ENDERROR!][!//
              [!ENDIF!][!//
              [!/* ------------------------------------------*/!][!//

              [!/***********************************BUFFER RECONFIG ALGORITHM START*********************************/!][!//
              [!/****************************Buffer Item positions**************************/!][!//
              [!/******[@2130#5#4#&0@3125#4#4#&1@4120#3#4#&2@5115#2#4#&3@10110#1#4#&4]******/!][!//
              [!VAR "VItemCycleTime" = "num:i(1)"!][!//
              [!VAR "VItemLpduIdx" = "num:i(2)"!][!//
              [!VAR "VItemPayloadL" = "num:i(3)"!][!//
              [!VAR "VItemBuffPos" = "num:i(4)"!][!//
              [!VAR "VItemSymbol" = "num:i(5)"!][!//
              [!/**************************************************************************************************************/!][!//
              [!/***************************************************************************/!][!//
              [!/***********************************SORTING MACRO******************************/!][!//
              [!MACRO "Sorting","SortArray" = "","VItem" = "","VTotalNum" = ""!][!//
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
                    [!VAR "VTempStr1_1" = "text:split($VTempStr1,'#')[num:i($VItem)]"!][!//
                    [!VAR "VTempStr2_2" = "text:split($VTempStr2,'#')[num:i($VItem)]"!][!//
                    [!VAR "VTempInt1" = "num:i(number($VTempStr1_1))"!][!//
                    [!VAR "VTempInt2" = "num:i(number($VTempStr2_2))"!][!//
                    [!IF "$VTempInt1 > $VTempInt2"!][!//
                      [!VAR "SortArray" = "text:replace($SortArray,$VTempStr1,$VTempReplceStr1)"!][!//
                      [!VAR "SortArray" = "text:replace($SortArray,$VTempStr2,$VTempReplceStr2)"!][!//
                      [!VAR "SortArray" = "text:replace($SortArray,$VTempReplceStr2,$VTempStr1)"!][!//
                      [!VAR "SortArray" = "text:replace($SortArray,$VTempReplceStr1,$VTempStr2)"!][!//
                    [!ENDIF!][!//
                  [!ENDFOR!][!//
                [!ENDFOR!][!//
              [!ENDMACRO!][!//
              [!/******/!][!//
              [!/*************************MACRO TO ADD BUFFER POSITIONS****************/!][!//
              [!MACRO "AddBufferPos","SortArray" = "","VTotalNum" = ""!][!//
                [!VAR "VStrStore_1" = "''"!][!//
                [!VAR "VStrStore_2" = "''"!][!//
                [!VAR "Vcount1" = "num:i(0)"!][!//
                [!FOR "Vcount1" = "num:i(0)" TO "num:i($VTotalNum - 1)"!][!//
                [!VAR "VStrStore_1" = "text:split($SortArray,'@')[num:i($Vcount1+1)]"!][!//
                [!VAR "VStrStore_2" = "$VStrStore_1"!][!//
                [!VAR "VStrStore_1" = "concat($VStrStore_1,'#&',string($Vcount1))"!][!//
                [!VAR "SortArray" = "text:replace($SortArray,$VStrStore_2,$VStrStore_1)"!][!//
                [!ENDFOR!][!//
              [!ENDMACRO!][!//
              [!/******/!][!//
              [!/*************************MACRO TO ADD BUFFER INDEX********************************/!][!//
              [!MACRO "AddBufferIndex","SortArray" = "","VStartNum" = "","VTotalNum" = "","LpduType" = ""!][!//
                [!VAR "VStrStore_1" = "''"!][!//
                [!VAR "VStrStore_2" = "''"!][!//
                [!VAR "Vcount1" = "num:i(0)"!][!//
                [!FOR "Vcount1" = "num:i(0)" TO "num:i($VTotalNum - 1)"!][!//
                [!VAR "VStartNum" = "num:i($VStartNum + num:i(1))"!][!//
                [!VAR "VStrStore_1" = "text:split($SortArray,'@')[num:i($Vcount1+1)]"!][!//
                [!VAR "VStrStore_2" = "$VStrStore_1"!][!//
                [!IF "$LpduType = 'fifo'"!][!//
                [!VAR "VStrStore_1" = "concat($VStrStore_1,'#','255')"!][!//
                [!ELSEIF "$LpduType = 'keyslot'"!][!//
                [!VAR "VStrStore_1" = "concat($VStrStore_1,'#',string($Vcount1))"!][!//
                [!ELSE!][!//
                [!VAR "VStrStore_1" = "concat($VStrStore_1,'#',string($VStartNum))"!][!//
                [!ENDIF!][!//
                [!VAR "SortArray" = "text:replace($SortArray,$VStrStore_2,$VStrStore_1)"!][!//
                [!ENDFOR!][!//
              [!ENDMACRO!][!//
              [!/******/!][!//
              [!/**********************************BUFFER RECONFIG MACRO***************************/!][!//
              [!MACRO "BuffReconfig","SortArray" = "","VTotalReconLpdu" = "","VMaxAvaBuffCount" = "","VKeySlotCount" = ""!][!//
                [!VAR "VTempStrParse1" = "''"!][!//
                [!VAR "VTempStrParse2" = "''"!][!//
                [!VAR "VTempStrParse3" = "''"!][!//
                [!VAR "VRunCountr" = "num:i(1)"!][!//
                [!VAR "VRemainBuff" = "num:i(0)"!][!//
                [!VAR "BuffRecIterFlag" = "num:i(0)"!][!//
                [!VAR "VNoOfReconfigLpdu" = "num:i($VTotalReconLpdu)"!][!//
                [!VAR "VReconfigNo" = "$VNoOfReconfigLpdu div $VMaxAvaBuffCount"!][!//
                [!VAR "VReconfigNo" = "floor($VReconfigNo)"!][!//
                [!VAR "VRemainBuff" = "$VNoOfReconfigLpdu mod $VMaxAvaBuffCount"!][!//
                [!IF "$VRemainBuff > num:i(0)"!][!//
                  [!VAR "VReconfigNo" = "num:i($VReconfigNo + 1)"!][!//
                [!ENDIF!][!//
                [!IF "($VReconfigNo > num:i(4))"!][!//
                  [!VAR "ReconfigStatus" = "'fail'"!][!//
                [!ELSE!][!//
                  [!IF "$BuffReconfigInitTst = num:i(1)"!][!//
                    [!VAR "BuffRecNewArrTemp" = "''"!][!//
                    [!VAR "VReconfigNo_1" = "$VReconfigNo"!][!//
                    [!VAR "BuffRecIterTrig" = "num:i(floor($VNoOfReconfigLpdu div $VReconfigNo) * $VReconfigNo)"!][!//
                    [!VAR "VReconfigRemainNo" = "$VNoOfReconfigLpdu - $BuffRecIterTrig"!][!//
                    [!/***LOOP through the array and find base cycle and Cycle repetition***/!][!//
                    [!FOR "BuffRecCount1" = "num:i(1)" TO "num:i($VNoOfReconfigLpdu)"!][!//
                      [!VAR "BuffRecSplit1" = "text:split($SortArray,'@')[num:i($BuffRecCount1)]"!][!//
                      [!VAR "BuffRecSplit2" = "$BuffRecSplit1"!][!//
                      [!VAR "BuffRecSplit3" = "$BuffRecSplit1"!][!//
                      [!VAR "BuffRecSplit3" = "substring-before($BuffRecSplit3,'&')"!][!//
                      [!VAR "BuffRecSplit2" = "substring-after($BuffRecSplit2,'#')"!][!//
                      [!VAR "BuffRecSplit2" = "substring-before($BuffRecSplit2,'#')"!][!//
                      [!VAR "BuffRecBaseCyc" = "num:i(node:ref(FrIfLPdu/*[FrIfLPduIdx=$BuffRecSplit2]/FrIfVBTriggeringRef)/FrIfBaseCycle)"!][!//
                      [!VAR "BuffRecCycRep" = "num:i(node:ref(FrIfLPdu/*[FrIfLPduIdx=$BuffRecSplit2]/FrIfVBTriggeringRef)/FrIfCycleRepetition)"!][!//
                      [!VAR "BuffRecCy_L"="num:i(0)"!][!//
                      [!VAR "BuffRecCy_H"="num:i(0)"!][!//
                      [!VAR "BuffRecBitPos" = "$BuffRecBaseCyc"!][!//
                      [!FOR "BuffRecCount2" = "num:i(0)" TO "num:i(63)"!][!//
                        [!IF "$BuffRecBitPos < num:i(32)"!][!//
                          [!VAR "BuffRecCy_L"="bit:bitset($BuffRecCy_L,$BuffRecBitPos)"!][!//
                        [!ELSE!][!//
                          [!VAR "BitPosMSB" = "num:i($BuffRecBitPos) - num:i(32)"!][!//
                          [!VAR "BuffRecCy_H"="bit:bitset($BuffRecCy_H, $BitPosMSB)"!][!//
                        [!ENDIF!][!//
                        [!VAR "BuffRecBitPos" = "num:i($BuffRecBitPos) + num:i($BuffRecCycRep)"!][!//
                        [!IF "$BuffRecBitPos > num:i(63)"!][!//
                          [!BREAK!][!//
                        [!ENDIF!][!//
                      [!ENDFOR!][!//
                      [!VAR "BuffRecNewArrTemp" = "concat($BuffRecNewArrTemp, $BuffRecSplit3)"!][!//
                      [!VAR "BuffRecNewArrTemp" = "concat($BuffRecNewArrTemp,$BuffRecCy_L)"!][!//
                      [!VAR "BuffRecNewArrTemp" = "concat($BuffRecNewArrTemp,'#')"!][!//
                      [!VAR "BuffRecNewArrTemp" = "concat($BuffRecNewArrTemp,$BuffRecCy_H)"!][!//
                      [!VAR "BuffRecNewArrTemp" = "concat($BuffRecNewArrTemp,'&')"!][!//
                      [!VAR "BuffRecNewArrTemp" = "concat($BuffRecNewArrTemp,num:i($BuffRecCount1)-1)"!][!//
                      [!VAR "BuffRecNewArrTemp" = "concat($BuffRecNewArrTemp,'@')"!][!//
                      [!VAR "BuffRecCount1" = "$BuffRecCount1 + num:i(1)"!][!//
                    [!ENDFOR!][!//
                    [!VAR "BuffRecSkipList" = "''"!][!//
                    [!VAR "BuffRecCyRp" = "''"!][!//
                    [!VAR "BuffRecFillCount" = "num:i(0)"!][!//
                    [!VAR "BuffRecIter" = "num:i(0)"!][!//
                    [!VAR "BuffRecCyRpTotDLC" = "num:i(0)"!][!//
                    [!FOR "BuffRecCount2" = "num:i(1)" TO "num:i($VNoOfReconfigLpdu)"!][!//
                      [!IF "$VRemainBuff > num:i(0)"!][!//
                        [!IF "$BuffRecIter = num:i($BuffRecIterTrig) and ($BuffRecIterFlag = num:i(0))"!][!//
                          [!VAR "VReconfigNo_1" = "num:i($VReconfigRemainNo)"!][!//
                          [!VAR "BuffRecIterFlag" = "num:i(1)"!][!//
                        [!ENDIF!][!//
                      [!ENDIF!][!//
                      [!/***Skip If already filled***/!][!//
                      [!IF "not(text:contains(text:split($BuffRecSkipList,'@'),$BuffRecCount2))"!][!//
                        [!VAR "BuffRecFillCount" = "num:i(1)"!][!//
                        [!VAR "BuffRecNewArrP1_Old" = "text:split($BuffRecNewArrTemp,'@')[num:i($BuffRecCount2)]"!][!//
                        [!VAR "BuffRecCy_L1" = "substring-before($BuffRecNewArrP1_Old,'&')"!][!//
                        [!VAR "BuffRecCy_L1" = "substring-after($BuffRecCy_L1,'#')"!][!//
                        [!VAR "BuffRecCy_Lpdu" = "substring-before($BuffRecCy_L1,'#')"!][!//
                        [!VAR "BuffRecCy_Temp" = "substring-after($BuffRecCy_L1,'#')"!][!//
                        [!VAR "BuffRecCyRpMaxDLC" = "substring-before($BuffRecCy_Temp,'#')"!][!//
                        [!VAR "BuffRecCy_Temp" = "substring-after($BuffRecCy_Temp,'#')"!][!//
                        [!VAR "BuffRecCy_L1" = "substring-before($BuffRecCy_Temp,'#')"!][!//
                        [!VAR "BuffRecCy_H1" = "substring-after($BuffRecCy_Temp,'#')"!][!//
                        [!VAR "BuffRecCy_L_Temp2"= "$BuffRecCy_L1"!][!//
                        [!VAR "BuffRecCy_H_Temp2"= "$BuffRecCy_H1"!][!//
                        [!VAR "BuffRecSkipList" = "concat($BuffRecSkipList,$BuffRecCount2)"!][!//
                        [!VAR "BuffRecSkipList" = "concat($BuffRecSkipList,'@')"!][!//
                        [!VAR "BuffRecCyRp" = "concat($BuffRecCyRp,'@')"!][!//
                        [!VAR "BuffRecCyRp" = "concat($BuffRecCyRp,$BuffRecNewArrP1_Old)"!][!//
                        [!VAR "BuffRecIter" = "num:i($BuffRecIter + 1)"!][!//
                        [!FOR "BuffRecCount3" = "num:i(1)" TO "num:i($VNoOfReconfigLpdu)"!][!//
                          [!/***Skip If already filled***/!][!//
                          [!IF "not(text:contains(text:split($BuffRecSkipList,'@'),$BuffRecCount3))"!][!//
                            [!VAR "BuffRecNewArrP1_i2" = "text:split($BuffRecNewArrTemp,'@')[num:i($BuffRecCount3)]"!][!//
                            [!VAR "BuffRecNewArrP2_i2" = "$BuffRecNewArrP1_i2"!][!//
                            [!VAR "BuffRecCy_L1_i2" = "substring-before($BuffRecNewArrP2_i2,'&')"!][!//
                            [!VAR "BuffRecCy_L1_i2" = "substring-after($BuffRecCy_L1_i2,'#')"!][!//
                            [!VAR "BuffRecCy_Lpdu_i2" = "substring-before($BuffRecCy_L1_i2,'#')"!][!//
                            [!VAR "BuffRecCy_Temp" = "substring-after($BuffRecCy_L1_i2,'#')"!][!//
                            [!VAR "BuffRecCy_DLC_i2" = "substring-before($BuffRecCy_Temp,'#')"!][!//
                            [!VAR "BuffRecCy_Temp" = "substring-after($BuffRecCy_Temp,'#')"!][!//
                            [!VAR "BuffRecCy_L1_i2" = "substring-before($BuffRecCy_Temp,'#')"!][!//
                            [!VAR "BuffRecCy_H1_i2" = "substring-after($BuffRecCy_Temp,'#')"!][!//
                            [!IF "not(bit:or((bit:and($BuffRecCy_L_Temp2, $BuffRecCy_L1_i2)),(bit:and($BuffRecCy_H_Temp2, $BuffRecCy_H1_i2))))"!][!//
                              [!VAR "BuffRecCy_L_Temp2"="bit:or($BuffRecCy_L_Temp2,$BuffRecCy_L1_i2)"!][!//
                              [!VAR "BuffRecCy_H_Temp2"="bit:or($BuffRecCy_H_Temp2,$BuffRecCy_H1_i2)"!][!//
                              [!VAR "BuffRecSkipList" = "concat($BuffRecSkipList,$BuffRecCount3)"!][!//
                              [!VAR "BuffRecSkipList" = "concat($BuffRecSkipList,'@')"!][!//
                              [!IF "$BuffRecCyRpMaxDLC < $BuffRecCy_DLC_i2"!][!//
                                [!VAR "BuffRecCyRpMaxDLC" = "$BuffRecCy_DLC_i2"!][!//
                              [!ENDIF!][!//
                              [!VAR "BuffRecCyRp" = "concat($BuffRecCyRp,'@')"!][!//
                              [!VAR "BuffRecCyRp" = "concat($BuffRecCyRp,$BuffRecNewArrP1_i2)"!][!//
                              [!VAR "BuffRecFillCount" = "num:i($BuffRecFillCount + 1)"!][!//
                              [!VAR "BuffRecIter" = "num:i($BuffRecIter + 1)"!][!//
                              [!IF "$BuffRecFillCount = $VReconfigNo_1"!][!//
                                [!VAR "BuffRecCyRpTotDLC" = "num:i($BuffRecCyRpTotDLC + $BuffRecCyRpMaxDLC)"!][!//
                                [!BREAK!][!//
                              [!ENDIF!][!//
                            [!ENDIF!][!//
                          [!ENDIF!][!//
                        [!ENDFOR!][!//
                        [!IF "($BuffRecCount3 = $VNoOfReconfigLpdu) and ($BuffRecFillCount < $VReconfigNo_1)"!][!//
                          [!ERROR!][!//
                            Error: Not enough hardware buffer available for sharing the LpduId:[!"$BuffRecCy_Lpdu"!] in FrCtrlIdx:[!"$ControllerIndex"!]
                            Hint: Reconfigure Lpdu communication cycle/s(ref.FrIfFrameTriggering)
                          [!ENDERROR!][!//
                          [!BREAK!][!//
                        [!ENDIF!][!//
                      [!ENDIF!][!//
                    [!ENDFOR!][!//
                    [!IF "($BuffRecCount2 = $VNoOfReconfigLpdu) and ($BuffRecFillCount < $VReconfigNo_1)"!][!//
                      [!ERROR!][!//
                        Error: Not enough hardware buffer available for sharing the LpduId:[!"$BuffRecCy_Lpdu"!] in FrCtrlIdx:[!"$ControllerIndex"!]
                        Hint: Reconfigure Lpdu communication cycle/s(ref.FrIfFrameTriggering)
                      [!ENDERROR!][!//
                    [!ENDIF!][!//
                    [!VAR "BuffRecCyRp" = "concat($BuffRecCyRp,'@')"!][!//
                    [!VAR "New_BuffRecCyRp" = "substring-after($BuffRecCyRp,'@')"!][!//
                    [!/***Remove the ComCycle data***/!][!//
                    [!VAR "BuffRecCyRp_Final" = "''"!][!//
                    [!FOR "New_BuffRecCount2" = "num:i(1)" TO "num:i($VNoOfReconfigLpdu)"!][!//
                      [!VAR "Buff_Temp" = "text:split($New_BuffRecCyRp,'@')[num:i($New_BuffRecCount2)]"!][!//
                      [!VAR "Buff_Temp2" = "substring-before($Buff_Temp,'&')"!][!//
                      [!VAR "Buff_Val1" = "substring-before($Buff_Temp,'#')"!][!//
                      [!VAR "Buff_Temp3" = "substring-after($Buff_Temp2,'#')"!][!//
                      [!VAR "Buff_Val2" = "substring-before($Buff_Temp3,'#')"!][!//
                      [!VAR "Buff_Temp4" = "substring-after($Buff_Temp3,'#')"!][!//
                      [!VAR "Buff_Val3" = "substring-before($Buff_Temp4,'#')"!][!//
                      [!VAR "BuffRecCyRp_Final" = "concat($BuffRecCyRp_Final,$Buff_Val1)"!][!//
                      [!VAR "BuffRecCyRp_Final" = "concat($BuffRecCyRp_Final,'#')"!][!//
                      [!VAR "BuffRecCyRp_Final" = "concat($BuffRecCyRp_Final,$Buff_Val2)"!][!//
                      [!VAR "BuffRecCyRp_Final" = "concat($BuffRecCyRp_Final,'#')"!][!//
                      [!VAR "BuffRecCyRp_Final" = "concat($BuffRecCyRp_Final,$Buff_Val3)"!][!//
                      [!VAR "BuffRecCyRp_Final" = "concat($BuffRecCyRp_Final,'#')"!][!//
                      [!VAR "BuffRecCyRp_Final" = "concat($BuffRecCyRp_Final,'&')"!][!//
                      [!VAR "BuffRecCyRp_Final" = "concat($BuffRecCyRp_Final,num:i($New_BuffRecCount2)-1)"!][!//
                      [!VAR "BuffRecCyRp_Final" = "concat($BuffRecCyRp_Final,'@')"!][!//
                    [!ENDFOR!][!//
                    [!VAR "SortArray" ="$BuffRecCyRp_Final"!][!//
                    [!VAR "ReconfigStatus" = "'pass'"!][!//
                    [!FOR "Vcounter1" = "num:i(0)" TO "num:i($VMaxAvaBuffCount - 1)"!][!//
                      [!FOR "Vcounter2" = "num:i(1)" TO "num:i($VReconfigNo)"!][!//
                        [!VAR "VBuffIndex" = "num:i($Vcounter1)"!][!//
                        [!IF "$VRunCountr > $VNoOfReconfigLpdu"!][!//
                          [!BREAK!][!//
                        [!ENDIF!][!//
                        [!VAR "VTempStrParse1" = "text:split($SortArray,'@')[num:i($VRunCountr)]"!][!//
                        [!VAR "VTempStrParse2" = "$VTempStrParse1"!][!//
                        [!VAR "VTempStrParse2" = "substring-before($VTempStrParse2,'&')"!][!//
                        [!VAR "VTempStrParse2" = "concat($VTempStrParse2,string(num:i($VBuffIndex + $VKeySlotCount)))"!][!//
                        [!VAR "SortArray" = "text:replace($SortArray,$VTempStrParse1,$VTempStrParse2)"!][!//
                        [!VAR "VRunCountr" = "$VRunCountr + num:i(1)"!][!//
                      [!ENDFOR!][!//
                    [!ENDFOR!][!//
                  [!ELSE!][!//
                    [!VAR "ReconfigStatus" = "'pass'"!][!//
                    [!FOR "Vcounter1" = "num:i(1)" TO "num:i($VReconfigNo)"!][!//
                      [!FOR "Vcounter2" = "num:i(0)" TO "num:i($VMaxAvaBuffCount - 1)"!][!//
                        [!VAR "VBuffIndex" = "num:i($Vcounter2)"!][!//
                        [!IF "$VRunCountr > $VNoOfReconfigLpdu"!][!//
                          [!BREAK!][!//
                        [!ENDIF!][!//
                        [!VAR "VTempStrParse1" = "text:split($SortArray,'@')[num:i($VRunCountr)]"!][!//
                        [!VAR "VTempStrParse2" = "$VTempStrParse1"!][!//
                        [!VAR "VTempStrParse2" = "substring-before($VTempStrParse2,'&')"!][!//
                        [!VAR "VTempStrParse2" = "concat($VTempStrParse2,string(num:i($VBuffIndex + $VKeySlotCount)))"!][!//
                        [!VAR "SortArray" = "text:replace($SortArray,$VTempStrParse1,$VTempStrParse2)"!][!//
                        [!VAR "VRunCountr" = "$VRunCountr + num:i(1)"!][!//
                      [!ENDFOR!][!//
                    [!ENDFOR!][!//
                  [!ENDIF!][!//
                [!ENDIF!][!//
              [!ENDMACRO!][!//
              [!/******/!][!//
              [!/****************PAYLOAD LENGTH CALCULATION MACRO*********************/!][!//
              [!MACRO "PayLoadCalc","SortArray" = "","VTotalNum" = ""!][!//
                [!VAR "VPayloadArr" = "''"!][!//
                [!VAR "TtlSizeCalc" = "num:i(0)"!][!//
                [!VAR "VstrTempReplace1" = "''"!][!//
                [!VAR "VDlcGrtr" = "num:i(0)"!][!//
                [!VAR "VDlcTemp" = "num:i(0)"!][!//
                [!VAR "VStrSplit1" = "''"!][!//
                [!VAR "VStrSplit2" = "''"!][!//
                [!VAR "VStrSplit1_1" = "''"!][!//
                [!VAR "VStrSplit2_2" = "''"!][!//
                [!VAR "VCountrLoop1" = "num:i(0)"!][!//
                [!VAR "VCountrLoop2" = "num:i(0)"!][!//
                [!FOR "VCountrLoop1" = "num:i(1)" TO "num:i($VTotalNum)"!][!//
                  [!VAR "VStrSplit1" = "text:split($SortArray,'@')[num:i($VCountrLoop1)]"!][!//
                  [!VAR "VStrSplit1_1" = "text:split($VStrSplit1,'#')[num:i($VItemSymbol)]"!][!//
                  [!IF "$VStrSplit1_1 != 'USED'"!][!//
                    [!VAR "VDlcGrtr" = "number(text:split($VStrSplit1,'#')[num:i($VItemPayloadL)])"!][!//
                    [!FOR "VCountrLoop2" = "num:i($VCountrLoop1 + 1)" TO "num:i($VTotalNum)"!][!//
                      [!VAR "VStrSplit2" = "text:split($SortArray,'@')[num:i($VCountrLoop2)]"!][!//
                      [!VAR "VStrSplit2_2" = "text:split($VStrSplit2,'#')[num:i($VItemSymbol)]"!][!//
                      [!IF "($VStrSplit2_2 != 'USED') and (text:split($VStrSplit1,'#')[num:i($VItemBuffPos)] = text:split($VStrSplit2,'#')[num:i($VItemBuffPos)])"!][!//
                        [!VAR "VDlcTemp" = "number(text:split($VStrSplit2,'#')[num:i($VItemPayloadL)])"!][!//
                        [!IF "$VDlcGrtr < $VDlcTemp"!][!//
                          [!VAR "VDlcGrtr" = "$VDlcTemp"!][!//
                        [!ENDIF!][!//
                        [!VAR "VstrTempReplace1" = "$VStrSplit2"!][!//
                        [!VAR "VstrTempReplace1" = "concat($VstrTempReplace1,'#USED')"!][!//
                        [!VAR "SortArray" = "text:replace($SortArray,$VStrSplit2,$VstrTempReplace1)"!][!//
                      [!ENDIF!][!//
                    [!ENDFOR!][!//
                    [!VAR "TtlSizeCalc" = "$TtlSizeCalc + num:i($VDlcGrtr)"!][!//
                    [!VAR "VPayloadArr" = "concat($VPayloadArr,string(num:i($VDlcGrtr)),'@')"!][!//
                  [!ENDIF!][!//
                [!ENDFOR!][!//
              [!ENDMACRO!][!//
              [!/******/!][!//
              [!/****************************************************************************************/!][!//
              [!/*******************************MACRO FOR GET VALUE**************************************/!][!//
              [!MACRO "GetVal","TmpString" = "","Item" = ""!][!//
                [!VAR "Val" = "num:i(0)"!][!//
                [!VAR "TmpString" = "text:split($TmpString,'#')[num:i($Item)]"!][!//
                [!VAR "Val" = "num:i(number($TmpString))"!][!//
              [!ENDMACRO!][!//
              [!/****************************************************************************************/!][!//
              [!/***************** MACRO FOR OFFSET ARRAY GENERATION*************************************/!][!//
              [!MACRO "OffsetArrCal", "Getarr" = "", "TtlNo" = ""!][!//
                [!VAR "OffsetCount" = "num:i(0)"!][!//
                [!VAR "OffsetArr" = "'0@'"!][!//
                [!VAR "TmpOffsetVal" = "num:i(0)"!][!//
                [!VAR "Flag" = "num:i(0)"!][!//
                [!VAR "TmpVal" = "num:i(0)"!][!//
                [!FOR "VCountrLoop1" = "num:i(0)" TO "num:i($TtlNo - num:i(1))"!][!//
                  [!VAR "GtrDlc" = "num:i(0)"!][!//
                  [!FOR "VCountrLoop2" = "num:i(1)" TO "num:i($TtlNo)"!][!//
                    [!VAR "VStrSplit1" = "text:split($Getarr,'@')[num:i($VCountrLoop2)]"!][!//
                    [!VAR "VBuffIndex" = "number(text:split($VStrSplit1,'#')[num:i($VItemBuffPos)])"!][!//
                    [!IF "$VCountrLoop1 = num:i($VBuffIndex)"!][!//
                      [!VAR "Flag" = "num:i(1)"!][!//
                      [!VAR "TmpVal" = "number(text:split($VStrSplit1,'#')[num:i($VItemPayloadL)])"!][!//
                        [!IF "$TmpVal > $GtrDlc"!][!//
                          [!VAR "GtrDlc" = "$TmpVal"!][!//
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                  [!ENDFOR!][!//
                  [!IF "$Flag = num:i(1)"!][!//
                    [!VAR "TmpOffsetVal" = "num:i($TmpOffsetVal + $GtrDlc)"!][!//
                    [!VAR "OffsetArr" = "concat($OffsetArr,$TmpOffsetVal,'@')"!][!//
                    [!VAR "Flag" = "num:i(0)"!][!//
                    [!VAR "OffsetCount" = "$OffsetCount + num:i(1)"!][!//
                  [!ENDIF!][!//
                [!ENDFOR!][!//
              [!ENDMACRO!][!//
              [!/****************************************************************************************/!][!//
              [!/*******************************MACRO FOR ARRAY GENERATION*******************************/!][!//
              [!MACRO "ArrGenerate","CtrlNo" = "","ReUsedBuffCount" = ""!][!//
                [!VAR "ArrLpdu" = "''"!][!//
                [!IF "$CtrlNo = num:i(0)"!][!//
                  [!VAR "BuffRecBuffUtlzd" = "num:i(floor($VNoOfReconfigLpdu div $VReconfigNo))"!][!//
                  [!IF "num:i(floor($VNoOfReconfigLpdu mod $VReconfigNo)) > num:i(0)"!][!//
                    [!VAR "BuffRecBuffUtlzd" = "num:i($BuffRecBuffUtlzd + 1)"!][!//
                  [!ENDIF!][!//
                  [!VAR "StartPos" = "num:i(0)"!][!//
                  [!CALL "AddBufferIndex","SortArray" = "$ArrKeySlotCtrl0","VStartNum" = "$StartPos","VTotalNum" = "$KeySlotCountCtrl0","LpduType" = "'keyslot'"!][!//
                  [!VAR "ArrKeySlotCtrl0" = "$SortArray"!][!//
                  [!IF "$KeySlotCountCtrl0 = num:i(0)"!][!//
                    [!VAR "StartPos" = "$StartPos + num:i($BuffRecBuffUtlzd - num:i(1))"!][!//
                  [!ELSE!][!//
                    [!VAR "StartPos" = "$StartPos + num:i($BuffRecBuffUtlzd)"!][!//
                  [!ENDIF!][!//
                  [!CALL "AddBufferIndex","SortArray" = "$ArrStaticReconDisLpduCtrl0","VStartNum" = "$StartPos","VTotalNum" = "$StaticReconDisCountCtrl0","LpduType" = "'static'"!][!//
                  [!VAR "ArrStaticReconDisLpduCtrl0" = "$SortArray"!][!//
                  [!VAR "StartPos" = "$StartPos + num:i($StaticReconDisCountCtrl0)"!][!//
                  [!/*
                  [cover parentID={7FA10B35-9A96-4943-9A5C-018C25CB932C}]
                  LPdu with ('FrIfReconfigurable' set to true) is allocated a separate hardware buffer [/cover]
                  */!][!//
                  [!CALL "AddBufferIndex","SortArray" = "$ArrStaticReconEnLpduCtrl0","VStartNum" = "$StartPos","VTotalNum" = "$StaticReconEnCountCtrl0","LpduType" = "'static'"!][!//
                  [!VAR "ArrStaticReconEnLpduCtrl0" = "$SortArray"!][!//
                  [!VAR "StartPos" = "$StartPos + num:i($StaticReconEnCountCtrl0)"!][!//
                  [!/*
                  [cover parentID={7FA10B35-9A96-4943-9A5C-018C25CB932C}]
                  Each LPdu within the dynamic segment is allocated a separate hardware buffer [/cover]
                  */!][!//
                  [!CALL "AddBufferIndex","SortArray" = "$ArrDynamicLpduCtrl0","VStartNum" = "$StartPos","VTotalNum" = "$DynamicLpduCountCtrl0","LpduType" = "'dynamic'"!][!//
                  [!VAR "ArrDynamicLpduCtrl0" = "$SortArray"!][!//
                  [!VAR "StartPos" = "$StartPos + num:i($DynamicLpduCountCtrl0)"!][!//
                  [!CALL "AddBufferIndex","SortArray" = "$ArrFifoLpduCtrl0","VStartNum" = "$StartPos","VTotalNum" = "$FifoCountCtrl0","LpduType" = "'fifo'"!][!//
                  [!VAR "ArrFifoLpduCtrl0" = "$SortArray"!][!//
                  [!VAR "ArrLpdu" = "concat($ArrLpdu,$ArrKeySlotCtrl0)"!][!//
                  [!VAR "ArrLpdu" = "concat($ArrLpdu,$ArrStaticReconDisPrepLpduCtrl0)"!][!//
                  [!VAR "ArrLpdu" = "concat($ArrLpdu,$ArrStaticReconDisLpduCtrl0)"!][!//
                  [!VAR "ArrLpdu" = "concat($ArrLpdu,$ArrStaticReconEnLpduCtrl0)"!][!//
                  [!VAR "ArrLpdu" = "concat($ArrLpdu,$ArrDynamicLpduCtrl0)"!][!//
                  [!VAR "ArrLpdu" = "concat($ArrLpdu,$ArrFifoLpduCtrl0)"!][!//
                  [!CALL "Sorting","SortArray" = "$ArrLpdu","VItem" = "$VItemLpduIdx","VTotalNum" = "$TtlMsgBufReq"!][!//
                  [!VAR "ArrLpdu" = "$SortArray"!][!//
                  /* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
                  due to Autosar Naming constraints.*/
                  /* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
                  due to Autosar Naming constraints.*/
                  /* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
                  due to Autosar Naming constraints.*/
                  /* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
                  due to Autosar Naming constraints.*/
                  [!/*
                  [cover parentID={EC0BEF88-63F4-4649-ACFF-D3D2F08769A4}] Fr_17_Eray_<ConfigShortName>_LPduIdx2MsgBuff_<CtrlIdx> [/cover]
                  */!][!//
                  static const uint8 Fr_17_Eray_[!"$ConfigShortNamePath"!]_LPduIdx2MsgBuff_[!"$CtrlNo"!][[!"num:i($TtlMsgBufReq)"!]] =
                  {
                  [!VAR "Cnt" = "num:i(0)"!][!//
                  [!FOR "k" = "num:i(1)" TO "$TtlMsgBufReq - num:i(1)"!][!//
                    [!VAR "GtempArr" = "text:split($ArrLpdu,'@')[num:i($k)]"!][!//
                    [!CALL "GetVal","TmpString" = "$GtempArr","Item" = "$VItemBuffPos"!][!//
                    [!VAR "Cnt" = "$Cnt + num:i(1)"!][!//
                    [!IF "$Cnt > num:i(10)"!][!//
                      [!VAR "Cnt" = "num:i(0)"!]
                      [!//
                    [!ENDIF!][!//
                    [!INDENT "2"!][!//
                      [!"num:i($Val)"!]U, [!//
                    [!ENDINDENT!][!//
                  [!ENDFOR!][!//
                  [!VAR "GtempArr" = "text:split($ArrLpdu,'@')[num:i($TtlMsgBufReq)]"!][!//
                  [!CALL "GetVal","TmpString" = "$GtempArr","Item" = "$VItemBuffPos"!][!//
                  [!INDENT "2"!][!//
                    [!"num:i($Val)"!]U
                  [!ENDINDENT!][!//
                  };
                  [!//
                  [!VAR "DataPtrOffset" = "num:i($KeySlotCountCtrl0 + $StaticReconDisCountCtrl0 + $StaticReconEnCountCtrl0 + $DynamicLpduCountCtrl0 + $ReUsedBuffCount)"!][!//
                  [!VAR "TtlMsgBuffUsed" = "num:i($DataPtrOffset)"!][!//
                  [!VAR "FifoCalcDepthCtrl0" = "num:i(0)"!][!//
                  [!IF "$FifoCountCtrl0 > num:i(0)"!][!//
                    [!IF "$FifoDepthCtrl0 < $FifoCountCtrl0"!][!//
                      [!VAR "TtlMsgBuffUsed" = "num:i($DataPtrOffset + $FifoDepthCtrl0)"!][!//
                      [!VAR "FifoCalcDepthCtrl0" = "$FifoDepthCtrl0"!][!//
                    [!ELSE!][!//
                      [!VAR "TtlMsgBuffUsed" = "num:i($DataPtrOffset + $FifoCountCtrl0)"!][!//
                      [!VAR "FifoCalcDepthCtrl0" = "$FifoCountCtrl0"!][!//
                    [!ENDIF!][!//
                    [!VAR "DataPtrOffset" = "num:i($DataPtrOffset + $FifoCalcDepthCtrl0)"!][!//
                  [!ENDIF!][!//
                  [!VAR "HardwareMsgBuffer0" = "num:i($TtlMsgBuffUsed)"!][!//
                  [!VAR "HdrOffset" = "num:i($TtlMsgBuffUsed * num:i(4))"!][!//
                  [!CALL "OffsetArrCal", "Getarr" = "$ArrLpdu", "TtlNo" = "$TtlMsgBufReq"!][!//
                  /* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
                  due to Autosar Naming constraints.*/
                  /* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
                  due to Autosar Naming constraints.*/
                  /* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
                  due to Autosar Naming constraints.*/
                  /* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
                  due to Autosar Naming constraints.*/
                  static const uint16 Fr_17_Eray_[!"$ConfigShortNamePath"!]_DataPointerOffset_[!"$CtrlNo"!][[!"num:i($DataPtrOffset)"!]] =
                  {
                  [!//
                  [!VAR "Cnt" = "num:i(0)"!][!//
                  [!FOR "k" = "num:i(1)" TO "num:i($OffsetCount - num:i(1))"!][!//
                    [!VAR "OutOffset" = "number(text:split($OffsetArr,'@')[num:i($k)])"!][!//
                    [!VAR "Cnt" = "$Cnt + num:i(1)"!][!//
                    [!IF "$Cnt > num:i(10)"!][!//
                      [!VAR "Cnt" = "num:i(0)"!]
                      [!//
                    [!ENDIF!][!//
                    [!INDENT "2"!][!//
                      [!"num:i($OutOffset + $HdrOffset)"!]U, [!//
                    [!ENDINDENT!][!//
                  [!ENDFOR!][!//
                  [!IF "$FifoCountCtrl0 = num:i(0)"!][!//
                    [!VAR "OutOffset" = "number(text:split($OffsetArr,'@')[num:i($OffsetCount)])"!][!//
                    [!INDENT "2"!][!//
                      [!"num:i($OutOffset + $HdrOffset)"!]U
                    [!ENDINDENT!][!//
                    };
                  [!ELSE!][!//
                    [!VAR "FifoDataPtrOffset" = "num:i(0)"!][!//
                    [!VAR "OutOffset" = "number(text:split($OffsetArr,'@')[num:i($OffsetCount)])"!][!//
                    [!"num:i($OutOffset + $HdrOffset)"!]U[!//
                    [!VAR "OutOffset" = "number(text:split($OffsetArr,'@')[num:i($OffsetCount)+num:i(1)])"!][!//
                    [!VAR "FifoDataPtrOffset" = "num:i($OutOffset + $HdrOffset)"!][!//
                    [!FOR "i" = "0" TO "$FifoCalcDepthCtrl0 - 1"!][!//
                      [!VAR "Cnt" = "$Cnt + num:i(1)"!][!//
                      [!IF "$Cnt > num:i(10)"!][!//
                        [!VAR "Cnt" = "num:i(0)"!]
                        [!//
                      [!ENDIF!][!//
                      , [!"$FifoDataPtrOffset"!]U[!//
                      [!VAR "FifoDataPtrOffset" = "num:i($FifoDataPtrOffset + $FifoDlcCtrl0)"!][!//
                    [!ENDFOR!][!//
                    };
                  [!ENDIF!][!//
                [!ENDIF!][!//
                [!/************** for controller 1 **************************/!][!//
                [!IF "$CtrlNo = num:i(1)"!][!//
                  [!VAR "StartPos" = "num:i(0)"!][!//
                  [!VAR "BuffRecBuffUtlzd" = "num:i(floor($VNoOfReconfigLpdu div $VReconfigNo))"!][!//
                  [!IF "num:i(floor($VNoOfReconfigLpdu mod $VReconfigNo)) > num:i(0)"!][!//
                    [!VAR "BuffRecBuffUtlzd" = "num:i($BuffRecBuffUtlzd + 1)"!][!//
                  [!ENDIF!][!//
                  [!CALL "AddBufferIndex","SortArray" = "$ArrKeySlotCtrl1","VStartNum" = "$StartPos","VTotalNum" = "$KeySlotCountCtrl1","LpduType" = "'keyslot'"!][!//
                  [!VAR "ArrKeySlotCtrl1" = "$SortArray"!][!//
                  [!IF "$KeySlotCountCtrl1 = num:i(0)"!][!//
                    [!VAR "StartPos" = "$StartPos + num:i($BuffRecBuffUtlzd - num:i(1))"!][!//
                  [!ELSE!][!//
                    [!VAR "StartPos" = "$StartPos + num:i($BuffRecBuffUtlzd)"!][!//
                  [!ENDIF!][!//
                  [!CALL "AddBufferIndex","SortArray" = "$ArrStaticReconDisLpduCtrl1","VStartNum" = "$StartPos","VTotalNum" = "$StaticReconDisCountCtrl1","LpduType" = "'static'"!][!//
                  [!VAR "ArrStaticReconDisLpduCtrl1" = "$SortArray"!][!//
                  [!VAR "StartPos" = "$StartPos + num:i($StaticReconDisCountCtrl1)"!][!//
                  [!CALL "AddBufferIndex","SortArray" = "$ArrStaticReconEnLpduCtrl1","VStartNum" = "$StartPos","VTotalNum" = "$StaticReconEnCountCtrl1","LpduType" = "'static'"!][!//
                  [!VAR "ArrStaticReconEnLpduCtrl1" = "$SortArray"!][!//
                  [!VAR "StartPos" = "$StartPos + num:i($StaticReconEnCountCtrl1)"!][!//
                  [!CALL "AddBufferIndex","SortArray" = "$ArrDynamicLpduCtrl1","VStartNum" = "$StartPos","VTotalNum" = "$DynamicLpduCountCtrl1","LpduType" = "'dynamic'"!][!//
                  [!VAR "ArrDynamicLpduCtrl1" = "$SortArray"!][!//
                  [!VAR "StartPos" = "$StartPos + num:i($DynamicLpduCountCtrl1)"!][!//
                  [!CALL "AddBufferIndex","SortArray" = "$ArrFifoLpduCtrl1","VStartNum" = "$StartPos","VTotalNum" = "$FifoCountCtrl1","LpduType" = "'fifo'"!][!//
                  [!VAR "ArrFifoLpduCtrl1" = "$SortArray"!][!//
                  [!VAR "ArrLpdu" = "concat($ArrLpdu,$ArrKeySlotCtrl1)"!][!//
                  [!VAR "ArrLpdu" = "concat($ArrLpdu,$ArrStaticReconDisPrepLpduCtrl1)"!][!//
                  [!VAR "ArrLpdu" = "concat($ArrLpdu,$ArrStaticReconDisLpduCtrl1)"!][!//
                  [!VAR "ArrLpdu" = "concat($ArrLpdu,$ArrStaticReconEnLpduCtrl1)"!][!//
                  [!VAR "ArrLpdu" = "concat($ArrLpdu,$ArrDynamicLpduCtrl1)"!][!//
                  [!VAR "ArrLpdu" = "concat($ArrLpdu,$ArrFifoLpduCtrl1)"!][!//
                  [!CALL "Sorting","SortArray" = "$ArrLpdu","VItem" = "$VItemLpduIdx","VTotalNum" = "$TtlMsgBufReq"!][!//
                  [!VAR "ArrLpdu" = "$SortArray"!][!//
                  /* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
                  due to Autosar Naming constraints.*/
                  /* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
                  due to Autosar Naming constraints.*/
                  /* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
                  due to Autosar Naming constraints.*/
                  /* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
                  due to Autosar Naming constraints.*/
                  [!/*
                  [cover parentID={EC0BEF88-63F4-4649-ACFF-D3D2F08769A4}] Fr_17_Eray_<ConfigShortName>_LPduIdx2MsgBuff_<CtrlIdx> [/cover]
                  */!][!//
                  static const uint8 Fr_17_Eray_[!"$ConfigShortNamePath"!]_LPduIdx2MsgBuff_[!"$CtrlNo"!][[!"num:i($TtlMsgBufReq)"!]] =
                  {
                  [!INDENT "2"!][!//[!//[!//
                    [!VAR "Cnt" = "num:i(0)"!][!//
                    [!FOR "k" = "num:i(1)" TO "$TtlMsgBufReq - num:i(1)"!][!//
                      [!VAR "GtempArr" = "text:split($ArrLpdu,'@')[num:i($k)]"!][!//
                      [!CALL "GetVal","TmpString" = "$GtempArr","Item" = "$VItemBuffPos"!][!//
                      [!VAR "Cnt" = "$Cnt + num:i(1)"!][!//
                      [!IF "$Cnt > num:i(10)"!][!//
                        [!VAR "Cnt" = "num:i(0)"!]
                        [!//
                      [!ENDIF!][!//
                      [!"num:i($Val)"!]U, [!//
                    [!ENDFOR!][!//
                    [!VAR "GtempArr" = "text:split($ArrLpdu,'@')[num:i($TtlMsgBufReq)]"!][!//
                    [!CALL "GetVal","TmpString" = "$GtempArr","Item" = "$VItemBuffPos"!][!//
                    [!"num:i($Val)"!]U
                  [!ENDINDENT!][!//
                  };
                  [!//
                  [!VAR "DataPtrOffset" = "num:i($KeySlotCountCtrl1 + $StaticReconDisCountCtrl1 + $StaticReconEnCountCtrl1 + $DynamicLpduCountCtrl1 + $ReUsedBuffCount)"!][!//
                  [!VAR "TtlMsgBuffUsed" = "num:i($DataPtrOffset)"!][!//
                  [!VAR "FifoCalcDepthCtrl1" = "num:i(0)"!][!//
                  [!IF "$FifoCountCtrl1 > num:i(0)"!][!//
                    [!IF "$FifoDepthCtrl1 < $FifoCountCtrl1"!][!//
                    [!VAR "TtlMsgBuffUsed" = "num:i($DataPtrOffset + $FifoDepthCtrl1)"!][!//
                    [!VAR "FifoCalcDepthCtrl1" = "$FifoDepthCtrl1"!][!//
                  [!ELSE!][!//
                    [!VAR "TtlMsgBuffUsed" = "num:i($DataPtrOffset + $FifoCountCtrl1)"!][!//
                    [!VAR "FifoCalcDepthCtrl1" = "$FifoCountCtrl1"!][!//
                  [!ENDIF!][!//
                  [!VAR "DataPtrOffset" = "num:i($DataPtrOffset + $FifoCalcDepthCtrl1)"!][!//
                [!ENDIF!][!//
                [!VAR "HardwareMsgBuffer1" = "num:i($TtlMsgBuffUsed)"!][!//
                [!VAR "HdrOffset" = "num:i($TtlMsgBuffUsed * num:i(4))"!][!//
                [!CALL "OffsetArrCal", "Getarr" = "$ArrLpdu", "TtlNo" = "$TtlMsgBufReq"!][!//
                /* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
                due to Autosar Naming constraints.*/
                /* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
                due to Autosar Naming constraints.*/
                /* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
                due to Autosar Naming constraints.*/
                /* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
                due to Autosar Naming constraints.*/
                static const uint16 Fr_17_Eray_[!"$ConfigShortNamePath"!]_DataPointerOffset_[!"$CtrlNo"!][[!"num:i($DataPtrOffset)"!]] =
                {
                  [!//
                  [!VAR "Cnt" = "num:i(0)"!][!//
                  [!FOR "k" = "num:i(1)" TO "num:i($OffsetCount - num:i(1))"!][!//
                    [!VAR "OutOffset" = "number(text:split($OffsetArr,'@')[num:i($k)])"!][!//
                    [!VAR "Cnt" = "$Cnt + num:i(1)"!][!//
                    [!IF "$Cnt > num:i(10)"!][!//
                      [!VAR "Cnt" = "num:i(0)"!]
                      [!//
                    [!ENDIF!][!//
                    [!INDENT "2"!][!//
                      [!"num:i($OutOffset + $HdrOffset)"!]U, [!//
                    [!ENDINDENT!][!//
                  [!ENDFOR!][!//
                  [!IF "$FifoCountCtrl1 = num:i(0)"!][!//
                    [!VAR "OutOffset" = "number(text:split($OffsetArr,'@')[num:i($OffsetCount)])"!][!//
                    [!INDENT "2"!][!//
                      [!"num:i($OutOffset + $HdrOffset)"!]U
                    [!ENDINDENT!][!//
                    };
                  [!ELSE!][!//
                    [!VAR "FifoDataPtrOffset" = "num:i(0)"!][!//
                    [!VAR "OutOffset" = "number(text:split($OffsetArr,'@')[num:i($OffsetCount)])"!][!//
                    [!INDENT "2"!][!//
                      [!"num:i($OutOffset + $HdrOffset)"!]U[!//
                    [!ENDINDENT!][!//
                    [!VAR "OutOffset" = "number(text:split($OffsetArr,'@')[num:i($OffsetCount)+num:i(1)])"!][!//
                    [!VAR "FifoDataPtrOffset" = "num:i($OutOffset + $HdrOffset)"!][!//
                    [!FOR "i" = "0" TO "$FifoCalcDepthCtrl1 - 1"!][!//
                      [!VAR "Cnt" = "$Cnt + num:i(1)"!][!//
                      [!IF "$Cnt > num:i(10)"!][!//
                        [!VAR "Cnt" = "num:i(0)"!]
                        [!//
                      [!ENDIF!][!//
                      , [!"$FifoDataPtrOffset"!]U[!//
                      [!VAR "FifoDataPtrOffset" = "num:i($FifoDataPtrOffset + $FifoDlcCtrl1)"!][!//
                    [!ENDFOR!][!//
                    };
                  [!ENDIF!][!//

              [!ENDIF!][!//

              [!ENDMACRO!][!//
              [!/****************************************************************************************/!][!//
              [!/****************REMOVE DUPLICATE LPDU ID MACRO******************************************/!][!//
              [!/*Removing lpdu with minimum length if more than one lpdu exist with same lpdu id*/!][!//
              [!MACRO "RmvDuPlicateLpduId","TempArray" = "","TotalCount" = ""!][!//
                [!VAR "RmvTmpCount" = "num:i(0)"!][!//
                [!VAR "DestArray" = "''"!][!//
                [!VAR "VDtempArray1" = "''"!][!//
                [!VAR "VDtempArray2" = "''"!][!//
                [!VAR "VDtempArray1_1" = "''"!][!//
                [!VAR "VDtempArray2_2" = "''"!][!//
                [!VAR "VDcount1" = "num:i(0)"!][!//
                [!VAR "VDcount2" = "num:i(0)"!][!//
                [!VAR "VDtempArray_11" = "''"!][!//
                [!VAR "VDtempArray_22" = "''"!][!//
                [!FOR "VDcount1" = "num:i(1)" TO "num:i($TotalCount)"!][!//
                  [!VAR "VDtempArray1" = "text:split($TempArray,'@')[num:i($VDcount1)]"!][!//
                  [!IF "$VDtempArray1 != 'USED'"!][!//
                    [!VAR "TempArray" = "text:replace($TempArray,$VDtempArray1,'USED')"!][!//
                    [!VAR "VDtempArray1_1" = "text:split($VDtempArray1,'#')[num:i($VItemLpduIdx)]"!][!//
                    [!FOR "VDcount2" = "num:i($VDcount1 + 1)" TO "num:i($TotalCount)"!][!//
                      [!VAR "VDtempArray2" = "text:split($TempArray,'@')[num:i($VDcount2)]"!][!//
                      [!IF "$VDtempArray2 != 'USED'"!][!//
                        [!VAR "VDtempArray2_2" = "text:split($VDtempArray2,'#')[num:i($VItemLpduIdx)]"!][!//
                        [!IF "$VDtempArray1_1 = $VDtempArray2_2"!][!//
                          [!VAR "TempArray" = "text:replace($TempArray,$VDtempArray2,'USED')"!][!//
                          [!VAR "VDtempArray_11" = "text:split($VDtempArray1,'#')[num:i($VItemPayloadL)]"!][!//
                          [!VAR "VDtempArray_22" = "text:split($VDtempArray2,'#')[num:i($VItemPayloadL)]"!][!//
                          [!IF "number($VDtempArray_11) < number($VDtempArray_22)"!][!//
                            [!VAR "VDtempArray1" = "$VDtempArray2"!][!//
                          [!ENDIF!][!//
                        [!ENDIF!][!//
                      [!ENDIF!][!//
                    [!ENDFOR!][!//
                    [!VAR "RmvTmpCount" = "$RmvTmpCount + num:i(1)"!][!//
                    [!VAR "DestArray" = "concat($DestArray,$VDtempArray1,'@')"!][!//
                  [!ENDIF!][!//
                [!ENDFOR!][!//
              [!ENDMACRO!][!//
              [!/**************************************************************************************/!][!//
              [!/***************************MACRO - PAYLOAD LENGTH CALCULATION ************************/!][!//
              [!MACRO "TotalPayLdLen","TempArray" = "","Count" = ""!][!//
                [!VAR "TtlLength" = "num:i(0)"!][!//
                [!FOR "TmpCount" = "num:i(1)" TO "num:i($Count)"!][!//
                  [!VAR "VTempstr" = "text:split($TempArray,'@')[num:i($TmpCount)]"!][!//
                  [!VAR "VTempstr" = "text:split($VTempstr,'#')[num:i($VItemPayloadL)]"!][!//
                  [!VAR "TtlLength" = "$TtlLength + num:i($VTempstr)"!][!//
                [!ENDFOR!][!//
              [!ENDMACRO!][!//
              [!/**************************************************************************************/!][!//
              [!/***************************MACRO - JOBLIST TO LPDU REFERENCE CHECK *******************/!][!//
              [!MACRO "CheckJobRef","CtrlPath" = "","KeySlotIdCtrl" = ""!][!//
                [!VAR "IsRefExist" = "'NO'"!][!//
                [!SELECT "node:ref($CtrlPath)"!][!//
                  [!VAR "ControlllerName" = "substring-after($CtrlPath, 'FrIfController/')"!][!//
                  [!LOOP "FrIfLPdu/*"!][!//
                    [!VAR "SlotID" = "(node:ref(FrIfVBTriggeringRef))/FrIfSlotId"!][!//
                    [!VAR "LpduID" = "num:i(FrIfLPduIdx)"!][!//
                    [!IF "(num:i($SlotID) != num:i($KeySlotIdCtrl)) and (num:i($SlotID) <= num:i($NumberOfStaticSlots))"!][!//
                      [!VAR "IsRefExist" = "'NO'"!][!//
                      [!LOOP "(node:ref($CtrlPath))/../../FrIfJobList/FrIfJob/*"!][!//
                        [!LOOP "FrIfCommunicationOperation/*"!][!//
                          [!IF "contains(FrIfLPduIdxRef, $ControlllerName)"!][!//
                            [!IF "num:i((node:ref(FrIfLPduIdxRef))/FrIfLPduIdx) = num:i($LpduID)"!][!//
                              [!VAR "IsRefExist" = "'YES'"!][!//
                              [!BREAK!][!//
                            [!ENDIF!][!//
                          [!ENDIF!][!//
                        [!ENDLOOP!][!//
                        [!IF "$IsRefExist = 'YES'"!][!//
                          [!BREAK!][!//
                        [!ENDIF!][!//
                      [!ENDLOOP!][!//
                      [!/* ---------  Config Rule FR_CR_216 ---------*/!][!//
                      [!IF "($IsRefExist = 'NO')"!][!//
                        [!ERROR!][!//
                          Reconfig Error: Missing Joblist reference to LPdu index = [!"FrIfLPduIdx"!]  for [!"$CtrlPath"!] since buffer reconfiguration is needed.
                        [!ENDERROR!][!//
                      [!ENDIF!][!//
                    [!ENDIF!][!//
                  [!ENDLOOP!][!//
                  [!/* ---------  Config Rule FR_CR_216 ---------*/!][!//
                  [!/* ---------  if no joblist is configured ---------*/!][!//
                  [!IF "($IsRefExist = 'NO')"!][!//
                    [!ERROR!][!//
                      Reconfig Error: Missing Joblist for [!"$CtrlPath"!] since buffer reconfiguration is needed.
                    [!ENDERROR!][!//
                  [!ENDIF!][!//
                [!ENDSELECT!][!//
              [!ENDMACRO!][!//
              [!/**************************************************************************************/!][!//
              [!VAR "HdrSize" = "num:i(4)"!][!//
              [!VAR "TtlMsgBuff" = "num:i(128)"!][!//
              [!VAR "TtlMsgRamSize" = "num:i(2048)"!][!//
              [!/************************ for controller 0 ************************************************/!][!//
              [!IF "((num:i($ControllerIndex) = num:i(0)) and ($BuffReconfigReqCtrl0 = 'YES'))"!][!//
                [!VAR "KeySlotIdCtrl0" = "num:i(2048)"!][!/* 2047 is maximum slot ID possible */!][!//
                [!IF "$KeySlotCountCtrl0 != num:i(0)"!][!//
                  [!VAR "KeySlotIdCtrl0" = "node:ref(concat($ControllerPath, '/FrPKeySlotId'))"!][!//
                [!ENDIF!][!//
                [!CALL "CheckJobRef","CtrlPath" = "$Ctrl0LpduPath","KeySlotIdCtrl" = "$KeySlotIdCtrl0"!][!//
                [!CALL "RmvDuPlicateLpduId","TempArray" = "$ArrFifoLpduCtrl0","TotalCount" = "$FifoCountCtrl0"!][!//
                [!VAR "ArrFifoLpduCtrl0" = "$DestArray"!][!//
                [!VAR "FifoCountCtrl0" = "$RmvTmpCount"!][!//
                [!CALL "RmvDuPlicateLpduId","TempArray" = "$ArrDynamicLpduCtrl0","TotalCount" = "$DynamicLpduCountCtrl0"!][!//
                [!VAR "ArrDynamicLpduCtrl0" = "$DestArray"!][!//
                [!VAR "DynamicLpduCountCtrl0" = "$RmvTmpCount"!][!//
                [!CALL "RmvDuPlicateLpduId","TempArray" = "$ArrStaticReconEnLpduCtrl0","TotalCount" = "$StaticReconEnCountCtrl0"!][!//
                [!VAR "ArrStaticReconEnLpduCtrl0" = "$DestArray"!][!//
                [!VAR "StaticReconEnCountCtrl0" = "$RmvTmpCount"!][!//
                [!CALL "RmvDuPlicateLpduId","TempArray" = "$ArrStaticReconDisLpduCtrl0","TotalCount" = "$StaticReconDisCountCtrl0"!][!//
                [!VAR "ArrStaticReconDisLpduCtrl0" = "$DestArray"!][!//
                [!VAR "StaticReconDisCountCtrl0" = "$RmvTmpCount"!][!//
                [!CALL "RmvDuPlicateLpduId","TempArray" = "$ArrStaticReconDisPrepLpduCtrl0","TotalCount" = "$StaticReconDisPrepCountCtrl0"!][!//
                [!VAR "ArrStaticReconDisPrepLpduCtrl0" = "$DestArray"!][!//
                [!VAR "StaticReconDisPrepCountCtrl0" = "$RmvTmpCount"!][!//
                [!//
                [!CALL "TotalPayLdLen","TempArray" = "$ArrKeySlotCtrl0","Count" = "$KeySlotCountCtrl0"!][!//
                [!VAR "KeyslotDlc" = "num:i($TtlLength)"!][!//
                [!VAR "ReqRamKeySlt" = "num:i($KeyslotDlc + ($KeySlotCountCtrl0 * $HdrSize ))"!][!//
                [!CALL "TotalPayLdLen","TempArray" = "$ArrDynamicLpduCtrl0","Count" = "$DynamicLpduCountCtrl0"!][!//
                [!VAR "DynslotDlc" = "num:i($TtlLength)"!][!//
                [!VAR "ReqRamDynSlt" = "num:i($DynslotDlc + ($DynamicLpduCountCtrl0 * $HdrSize ))"!][!//
                [!CALL "TotalPayLdLen","TempArray" = "$ArrStaticReconEnLpduCtrl0","Count" = "$StaticReconEnCountCtrl0"!][!//
                [!VAR "StaticEnRecoDlc" = "num:i($TtlLength)"!][!//
                [!VAR "ReqRamStcSltEn" = "num:i($StaticEnRecoDlc + ($StaticReconEnCountCtrl0 * $HdrSize ))"!][!//
                [!CALL "TotalPayLdLen","TempArray" = "$ArrStaticReconDisLpduCtrl0","Count" = "$StaticReconDisCountCtrl0"!][!//
                [!VAR "StaticDisRecoDlc" = "num:i($TtlLength)"!][!//
                [!VAR "ReqRamStcSltDis" = "num:i($StaticDisRecoDlc + ($StaticReconDisCountCtrl0 * $HdrSize ))"!][!//
                [!CALL "TotalPayLdLen","TempArray" = "$ArrStaticReconDisPrepLpduCtrl0","Count" = "$StaticReconDisPrepCountCtrl0"!][!//
                [!VAR "StaticDisRecoPrepDlc" = "num:i($TtlLength)"!][!//
                [!VAR "ReqRamStcSltDisPrep" = "num:i($StaticDisRecoPrepDlc + ($StaticReconDisPrepCountCtrl0 * $HdrSize))"!][!//
                [!IF "$FifoDepthCtrl0 < $FifoCountCtrl0"!][!//
                  [!VAR "FifoConfigCountCtrl0" = "num:i($FifoDepthCtrl0)"!][!//
                [!ELSE!][!//
                  [!VAR "FifoConfigCountCtrl0" = "num:i($FifoCountCtrl0)"!][!//
                [!ENDIF!][!//
                [!VAR "ReqRamFifo" = "num:i($FifoConfigCountCtrl0 *($FifoDlcCtrl0 + $HdrSize ))"!][!//
                [!//
                [!VAR "TtlMsgBufCount" = "num:i($KeySlotCountCtrl0 + $FifoConfigCountCtrl0 + $DynamicLpduCountCtrl0 + $StaticReconEnCountCtrl0 + $StaticReconDisCountCtrl0 + $StaticReconDisPrepCountCtrl0)"!][!//
                [!VAR "TtlMsgBufReq" = "num:i($KeySlotCountCtrl0 + $FifoCountCtrl0 + $DynamicLpduCountCtrl0 + $StaticReconEnCountCtrl0 + $StaticReconDisCountCtrl0 + $StaticReconDisPrepCountCtrl0)"!][!//
                [!VAR "TtlMsgRamReq" = "num:i($ReqRamKeySlt + $ReqRamDynSlt + $ReqRamStcSltEn + $ReqRamStcSltDis + $ReqRamFifo + $ReqRamStcSltDisPrep)"!][!//
                [!VAR "FixedRam" = "$TtlMsgRamReq - $ReqRamStcSltDisPrep"!][!//
                [!IF "$FixedRam > $TtlMsgRamSize"!][!//
                  [!ERROR!][!//
                    Reconfig Error: No Available RAM to configure all LPdus for Controller Idx = 0.
                    Reduce the size of FIFO depth or reduce the dynamic LPdu count/ static LPdu count with FrIfReconfigurable set to 'true' or
                    Configure 'PREPARE_LPDU' operation for additional static LPdus (with FrIfReconfigurable set to 'false')
                  [!ENDERROR!][!//
                [!ENDIF!][!//
                [!VAR "ReconfigRamSize" = "num:i($TtlMsgRamSize - $FixedRam)"!][!//
                [!VAR "FixedMsgBuffCount" = "num:i($KeySlotCountCtrl0 + $FifoConfigCountCtrl0 + $DynamicLpduCountCtrl0 + $StaticReconEnCountCtrl0 + $StaticReconDisCountCtrl0)"!][!//
                [!IF "$FixedMsgBuffCount >= $TtlMsgBuff"!][!//
                  [!ERROR!][!//
                    Reconfig Error: No Available hardware buffers to configure all LPdus for Controller Idx = 0.
                    Reduce the size of FIFO depth or reduce the dynamic LPdu count/ static LPdu count with FrIfReconfigurable set to 'true' or
                    Configure 'PREPARE_LPDU' operation for additional static LPdus (with FrIfReconfigurable set to 'false')
                  [!ENDERROR!][!//
                [!ENDIF!][!//
                [!VAR "ReconfigBuffNo" = "num:i(0)"!][!//
                [!IF "$TtlMsgBufCount >= $TtlMsgBuff"!][!//
                  [!VAR "ReconfigBuffNo" = "num:i($TtlMsgBuff - $FixedMsgBuffCount)"!][!//
                [!ELSE!][!//
                  [!FOR "ForCount" = "num:i(1)" TO "$StaticReconDisPrepCountCtrl0"!][!//
                    [!CALL "TotalPayLdLen","TempArray" = "$ArrStaticReconDisPrepLpduCtrl0","Count" = "$ForCount"!][!//
                    [!VAR "TmpRamCalc" = "num:i($TtlLength + ($ForCount * $HdrSize))"!][!//
                    [!IF "$TmpRamCalc > $ReconfigRamSize"!][!//
                      [!VAR "ReconfigBuffNo" = "num:i($ForCount - num:i(1))"!][!//
                      [!BREAK!][!//
                    [!ENDIF!][!//
                  [!ENDFOR!][!//
                [!ENDIF!][!//
                [!//
                [!IF "$ReconfigBuffNo <= num:i(0)"!][!//
                  [!ERROR!][!//
                    Reconfig Error: No Available RAM to configure all LPdus for Controller Idx = 0.
                    Reduce the size of FIFO depth or reduce the dynamic LPdu count/ static LPdu count with FrIfReconfigurable set to 'true' or
                    Configure 'PREPARE_LPDU' operation for additional static LPdus (with FrIfReconfigurable set to 'false')
                  [!ENDERROR!][!//
                [!ENDIF!][!//
                [!VAR "GenerateArr" = "'false'"!][!//
                [!CALL "Sorting","SortArray" = "$ArrStaticReconDisPrepLpduCtrl0","VItem" = "$VItemCycleTime","VTotalNum" = "$StaticReconDisPrepCountCtrl0"!][!//
                [!VAR "ArrStaticReconDisPrepLpduCtrl0" = "$SortArray"!][!//
                [!CALL "AddBufferPos","SortArray" = "$ArrStaticReconDisPrepLpduCtrl0","VTotalNum" = "$StaticReconDisPrepCountCtrl0"!][!//
                [!VAR "ArrStaticReconDisPrepLpduCtrl0" = "$SortArray"!][!//
                [!FOR "ForCount" = "num:i(1)" TO "$StaticReconDisPrepCountCtrl0"!][!//
                [!VAR "BuffReconfigInitTst" = "num:i(0)"!][!//
                  [!CALL "BuffReconfig","SortArray" = "$ArrStaticReconDisPrepLpduCtrl0","VTotalReconLpdu" = "$StaticReconDisPrepCountCtrl0","VMaxAvaBuffCount" = "$ReconfigBuffNo","VKeySlotCount" = "$KeySlotCountCtrl0"!][!//
                  [!VAR "TempReconfigArr" = "$SortArray"!][!//
                  [!IF "$ReconfigStatus = 'pass'"!][!//
                    [!CALL "PayLoadCalc","SortArray" = "$TempReconfigArr","VTotalNum" = "$StaticReconDisPrepCountCtrl0"!][!//
                    [!VAR "TmpRamCalc" = "num:i($TtlSizeCalc + ($ReconfigBuffNo * $HdrSize))"!][!//
                    [!IF "$TmpRamCalc > $ReconfigRamSize"!][!//
                      [!VAR "ReconfigBuffNo" = "num:i($ReconfigBuffNo - num:i(1))"!][!//
                    [!ELSE!][!//
                      [!VAR "BuffReconfigInitTst" = "num:i(1)"!][!//
                      [!CALL "BuffReconfig","SortArray" = "$ArrStaticReconDisPrepLpduCtrl0","VTotalReconLpdu" = "$StaticReconDisPrepCountCtrl0","VMaxAvaBuffCount" = "$ReconfigBuffNo","VKeySlotCount" = "$KeySlotCountCtrl0"!][!//
                      [!VAR "TempReconfigArr" = "$SortArray"!][!//
                      [!VAR "TmpRamCalc" = "num:i($BuffRecCyRpTotDLC + ($ReconfigBuffNo * $HdrSize))"!][!//
                      [!VAR "ArrStaticReconDisPrepLpduCtrl0" = "$TempReconfigArr"!][!//
                      [!VAR "GenerateArr" = "'true'"!][!//
                      [!BREAK!][!//
                    [!ENDIF!][!//
                  [!ELSE!][!//
                    [!VAR "GenerateArr" = "'false'"!][!//
                    [!BREAK!][!//
                  [!ENDIF!][!//
                [!ENDFOR!][!//
                [!//
                [!IF "$GenerateArr = 'true'"!][!//
                  [!VAR "BuffRecBuffUtlzd" = "num:i(floor($VNoOfReconfigLpdu div $VReconfigNo))"!][!//
                  [!IF "num:i(floor($VNoOfReconfigLpdu mod $VReconfigNo)) > num:i(0)"!][!//
                    [!VAR "BuffRecBuffUtlzd" = "num:i($BuffRecBuffUtlzd + 1)"!][!//
                  [!ENDIF!][!//
                  [!CALL "ArrGenerate","CtrlNo" = "num:i(0)","ReUsedBuffCount" = "$BuffRecBuffUtlzd"!][!//
                [!ELSE!][!//
                  [!/*
                  [cover parentID={7FA10B35-9A96-4943-9A5C-018C25CB932C}]
                  Unable to map all the required communication operations to available resources [/cover]
                  */!][!//
                  [!ERROR!][!//
                    Reconfig Error: No Available RAM to configure all LPdus for Controller Idx = 0.
                    Reduce the size of FIFO depth or reduce the dynamic LPdu count/ static LPdu count with FrIfReconfigurable set to 'true' or
                    Configure 'PREPARE_LPDU' operation for additional static LPdus (with FrIfReconfigurable set to 'false')
                  [!ENDERROR!][!//
                [!ENDIF!][!//
              [!ENDIF!][!//
              [!/************************ for controller 1 ************************************************/!][!//
              [!IF "((num:i($ControllerIndex) = num:i(1)) and ($BuffReconfigReqCtrl1 = 'YES'))"!][!//
                [!VAR "KeySlotIdCtrl1" = "num:i(2048)"!][!/* 2047 is maximum slot ID possible */!][!//
                [!IF "$KeySlotCountCtrl1 != num:i(0)"!][!//
                  [!VAR "KeySlotIdCtrl1" = "node:ref(concat($ControllerPath, '/FrPKeySlotId'))"!][!//
                [!ENDIF!][!//
                [!CALL "CheckJobRef","CtrlPath" = "$Ctrl1LpduPath","KeySlotIdCtrl" = "$KeySlotIdCtrl1"!][!//
                [!CALL "RmvDuPlicateLpduId","TempArray" = "$ArrFifoLpduCtrl1","TotalCount" = "$FifoCountCtrl1"!][!//
                [!VAR "ArrFifoLpduCtrl1" = "$DestArray"!][!//
                [!VAR "FifoCountCtrl1" = "$RmvTmpCount"!][!//
                [!CALL "RmvDuPlicateLpduId","TempArray" = "$ArrDynamicLpduCtrl1","TotalCount" = "$DynamicLpduCountCtrl1"!][!//
                [!VAR "ArrDynamicLpduCtrl1" = "$DestArray"!][!//
                [!VAR "DynamicLpduCountCtrl1" = "$RmvTmpCount"!][!//
                [!CALL "RmvDuPlicateLpduId","TempArray" = "$ArrStaticReconEnLpduCtrl1","TotalCount" = "$StaticReconEnCountCtrl1"!][!//
                [!VAR "ArrStaticReconEnLpduCtrl1" = "$DestArray"!][!//
                [!VAR "StaticReconEnCountCtrl1" = "$RmvTmpCount"!][!//
                [!CALL "RmvDuPlicateLpduId","TempArray" = "$ArrStaticReconDisLpduCtrl1","TotalCount" = "$StaticReconDisCountCtrl1"!][!//
                [!VAR "ArrStaticReconDisLpduCtrl1" = "$DestArray"!][!//
                [!VAR "StaticReconDisCountCtrl1" = "$RmvTmpCount"!][!//
                [!CALL "RmvDuPlicateLpduId","TempArray" = "$ArrStaticReconDisPrepLpduCtrl1","TotalCount" = "$StaticReconDisPrepCountCtrl1"!][!//
                [!VAR "ArrStaticReconDisPrepLpduCtrl1" = "$DestArray"!][!//
                [!VAR "StaticReconDisPrepCountCtrl1" = "$RmvTmpCount"!][!//
                [!//
                [!CALL "TotalPayLdLen","TempArray" = "$ArrKeySlotCtrl1","Count" = "$KeySlotCountCtrl1"!][!//
                [!VAR "KeyslotDlc" = "num:i($TtlLength)"!][!//
                [!VAR "ReqRamKeySlt" = "num:i($KeyslotDlc + ($KeySlotCountCtrl1 * $HdrSize ))"!][!//
                [!CALL "TotalPayLdLen","TempArray" = "$ArrDynamicLpduCtrl1","Count" = "$DynamicLpduCountCtrl1"!][!//
                [!VAR "DynslotDlc" = "num:i($TtlLength)"!][!//
                [!VAR "ReqRamDynSlt" = "num:i($DynslotDlc + ($DynamicLpduCountCtrl1 * $HdrSize ))"!][!//
                [!CALL "TotalPayLdLen","TempArray" = "$ArrStaticReconEnLpduCtrl1","Count" = "$StaticReconEnCountCtrl1"!][!//
                [!VAR "StaticEnRecoDlc" = "num:i($TtlLength)"!][!//
                [!VAR "ReqRamStcSltEn" = "num:i($StaticEnRecoDlc + ($StaticReconEnCountCtrl1 * $HdrSize ))"!][!//
                [!CALL "TotalPayLdLen","TempArray" = "$ArrStaticReconDisLpduCtrl1","Count" = "$StaticReconDisCountCtrl1"!][!//
                [!VAR "StaticDisRecoDlc" = "num:i($TtlLength)"!][!//
                [!VAR "ReqRamStcSltDis" = "num:i($StaticDisRecoDlc + ($StaticReconDisCountCtrl1 * $HdrSize ))"!][!//
                [!CALL "TotalPayLdLen","TempArray" = "$ArrStaticReconDisPrepLpduCtrl1","Count" = "$StaticReconDisPrepCountCtrl1"!][!//
                [!VAR "StaticDisRecoPrepDlc" = "num:i($TtlLength)"!][!//
                [!VAR "ReqRamStcSltDisPrep" = "num:i($StaticDisRecoPrepDlc + ($StaticReconDisPrepCountCtrl1 * $HdrSize))"!][!//
                [!IF "$FifoDepthCtrl1 < $FifoCountCtrl1"!][!//
                  [!VAR "FifoConfigCountCtrl1" = "num:i($FifoDepthCtrl1)"!][!//
                [!ELSE!][!//
                  [!VAR "FifoConfigCountCtrl1" = "num:i($FifoCountCtrl1)"!][!//
                [!ENDIF!][!//
                [!VAR "ReqRamFifo" = "num:i($FifoConfigCountCtrl1 *($FifoDlcCtrl1 + $HdrSize ))"!][!//
                [!//
                [!VAR "TtlMsgBufCount" = "num:i($KeySlotCountCtrl1 + $FifoConfigCountCtrl1 + $DynamicLpduCountCtrl1 + $StaticReconEnCountCtrl1 + $StaticReconDisCountCtrl1 + $StaticReconDisPrepCountCtrl1)"!][!//
                [!VAR "TtlMsgBufReq" = "num:i($KeySlotCountCtrl1 + $FifoCountCtrl1 + $DynamicLpduCountCtrl1 + $StaticReconEnCountCtrl1 + $StaticReconDisCountCtrl1 + $StaticReconDisPrepCountCtrl1)"!][!//
                [!VAR "TtlMsgRamReq" = "num:i($ReqRamKeySlt + $ReqRamDynSlt + $ReqRamStcSltEn + $ReqRamStcSltDis + $ReqRamFifo + $ReqRamStcSltDisPrep)"!][!//
                [!VAR "FixedRam" = "$TtlMsgRamReq - $ReqRamStcSltDisPrep"!][!//
                [!IF "$FixedRam > $TtlMsgRamSize"!][!//
                  [!ERROR!][!//
                    Reconfig Error: No Available RAM to configure all LPdus for Controller Idx = 1.
                    Reduce the size of FIFO depth or reduce the Dynamic LPdu count/ Static LPdu count with FrIfReconfigurable set to 'true' or
                    Configure 'PREPARE_LPDU' operation for additional static LPdus (with FrIfReconfigurable set to 'false')
                  [!ENDERROR!][!//
                [!ENDIF!][!//
                [!VAR "ReconfigRamSize" = "num:i($TtlMsgRamSize - $FixedRam)"!][!//
                [!VAR "FixedMsgBuffCount" = "num:i($KeySlotCountCtrl1 + $FifoConfigCountCtrl1 + $DynamicLpduCountCtrl1 + $StaticReconEnCountCtrl1 + $StaticReconDisCountCtrl1)"!][!//
                [!IF "$FixedMsgBuffCount >= $TtlMsgBuff"!][!//
                  [!ERROR!][!//
                    Reconfig Error: No Available hardware buffers to configure all LPdus for Controller Idx = 1.
                    Reduce the size of FIFO depth or reduce the dynamic LPdu count/ static LPdu count with FrIfReconfigurable set to 'true' or
                    Configure 'PREPARE_LPDU' operation for additional static LPdus (with FrIfReconfigurable set to 'false')
                  [!ENDERROR!][!//
                [!ENDIF!][!//
                [!VAR "ReconfigBuffNo" = "num:i(0)"!][!//
                [!IF "$TtlMsgBufCount >= $TtlMsgBuff"!][!//
                  [!VAR "ReconfigBuffNo" = "num:i($TtlMsgBuff - $FixedMsgBuffCount)"!][!//
                [!ELSE!][!//
                  [!FOR "ForCount" = "num:i(1)" TO "$StaticReconDisPrepCountCtrl1"!][!//
                    [!CALL "TotalPayLdLen","TempArray" = "$ArrStaticReconDisPrepLpduCtrl1","Count" = "$ForCount"!][!//
                    [!VAR "TmpRamCalc" = "num:i($TtlLength + ($ForCount * $HdrSize))"!][!//
                    [!IF "$TmpRamCalc > $ReconfigRamSize"!][!//
                      [!VAR "ReconfigBuffNo" = "num:i($ForCount - num:i(1))"!][!//
                      [!BREAK!][!//
                    [!ENDIF!][!//
                  [!ENDFOR!][!//
                [!ENDIF!][!//
                [!IF "$ReconfigBuffNo <= num:i(0)"!][!//
                  [!ERROR!][!//
                    Reconfig Error: No Available RAM to configure all LPdus for Controller Idx = 1.
                    Reduce the size of FIFO depth or reduce the Dynamic LPdu count/ Static LPdu count with FrIfReconfigurable set to 'true' or
                    Configure 'PREPARE_LPDU' operation for additional static LPdus (with FrIfReconfigurable set to 'false')
                  [!ENDERROR!][!//
                [!ENDIF!][!//
                [!//
                [!VAR "GenerateArr" = "'false'"!][!//
                [!CALL "Sorting","SortArray" = "$ArrStaticReconDisPrepLpduCtrl1","VItem" = "$VItemCycleTime","VTotalNum" = "$StaticReconDisPrepCountCtrl1"!][!//
                [!VAR "ArrStaticReconDisPrepLpduCtrl1" = "$SortArray"!][!//
                [!CALL "AddBufferPos","SortArray" = "$ArrStaticReconDisPrepLpduCtrl1","VTotalNum" = "$StaticReconDisPrepCountCtrl1"!][!//
                [!VAR "ArrStaticReconDisPrepLpduCtrl1" = "$SortArray"!][!//
                [!FOR "ForCount" = "num:i(1)" TO "$StaticReconDisPrepCountCtrl1"!][!//
                  [!VAR "BuffReconfigInitTst" = "num:i(0)"!][!//
                  [!CALL "BuffReconfig","SortArray" = "$ArrStaticReconDisPrepLpduCtrl1","VTotalReconLpdu" = "$StaticReconDisPrepCountCtrl1","VMaxAvaBuffCount" = "$ReconfigBuffNo","VKeySlotCount" = "$KeySlotCountCtrl1"!][!//
                  [!VAR "TempReconfigArr" = "$SortArray"!][!//
                  [!IF "$ReconfigStatus = 'pass'"!][!//
                    [!CALL "PayLoadCalc","SortArray" = "$TempReconfigArr","VTotalNum" = "$StaticReconDisPrepCountCtrl1"!][!//
                    [!VAR "TmpRamCalc" = "num:i($TtlSizeCalc + ($ReconfigBuffNo * $HdrSize))"!][!//
                    [!IF "$TmpRamCalc > $ReconfigRamSize"!][!//
                      [!VAR "ReconfigBuffNo" = "num:i($ReconfigBuffNo - num:i(1))"!][!//
                    [!ELSE!][!//
                      [!VAR "BuffReconfigInitTst" = "num:i(1)"!][!//
                      [!CALL "BuffReconfig","SortArray" = "$ArrStaticReconDisPrepLpduCtrl1","VTotalReconLpdu" = "$StaticReconDisPrepCountCtrl1","VMaxAvaBuffCount" = "$ReconfigBuffNo","VKeySlotCount" = "$KeySlotCountCtrl1"!][!//
                      [!VAR "TempReconfigArr" = "$SortArray"!][!//
                      [!VAR "TmpRamCalc" = "num:i($BuffRecCyRpTotDLC + ($ReconfigBuffNo * $HdrSize))"!][!//
                      [!VAR "ArrStaticReconDisPrepLpduCtrl1" = "$TempReconfigArr"!][!//
                      [!VAR "GenerateArr" = "'true'"!][!//
                      [!BREAK!][!//
                    [!ENDIF!][!//
                  [!ELSE!][!//
                    [!VAR "GenerateArr" = "'false'"!][!//
                    [!BREAK!][!//
                  [!ENDIF!][!//
                [!ENDFOR!][!//
                [!//
                [!IF "$GenerateArr = 'true'"!][!//
                  [!VAR "BuffRecBuffUtlzd" = "num:i(floor($VNoOfReconfigLpdu div $VReconfigNo))"!][!//
                    [!IF "num:i(floor($VNoOfReconfigLpdu mod $VReconfigNo)) > num:i(0)"!][!//
                      [!VAR "BuffRecBuffUtlzd" = "num:i($BuffRecBuffUtlzd + 1)"!][!//
                    [!ENDIF!][!//
                  [!CALL "ArrGenerate","CtrlNo" = "num:i(1)","ReUsedBuffCount" = "$BuffRecBuffUtlzd"!][!//
                [!ELSE!][!//
                  [!ERROR!][!//
                    Reconfig Error: No Available RAM to configure all LPdus for Controller Idx = 1.
                    Reduce the size of FIFO depth or reduce the dynamic LPdu count/ static LPdu count with FrIfReconfigurable set to 'true' or
                    Configure 'PREPARE_LPDU' operation for additional static LPdus (with FrIfReconfigurable set to 'false')
                  [!ENDERROR!][!//
                [!ENDIF!][!//
                [!ENDIF!][!//
              [!ELSE!][!/* RECONFIG_IF2 */!][!//
              /*
              LPduIdx to message buffer mapping for Controller [!"$ControllerIndex"!]
              */
              [!VAR "LPduCount" = "num:i(count(FrIfLPdu/*))"!][!//
              [!//
              /* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
              due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
              due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
              due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
              due to Autosar Naming constraints.*/
              [!/*
              [cover parentID={EC0BEF88-63F4-4649-ACFF-D3D2F08769A4}] Fr_17_Eray_<ConfigShortName>_LPduIdx2MsgBuff_<CtrlIdx> [/cover]
              */!][!//
              static const uint8 Fr_17_Eray_[!"$ConfigShortNamePath"!]_LPduIdx2MsgBuff_[!"$ControllerIndex"!][[!"num:i($LPduCount)"!]] =
              {
              [!INDENT "2"!][!//
                [!//
                [!VAR "Cnt" = "num:i(0)"!][!//
                [!VAR "KeySlotFrIfLPduIdx" = "num:i(4096)"!][!/* 4096 is maximum LPdu Idx possible + 1 */!][!//
                [!VAR "KeySlotIdxStr" = "''"!][!//
                [!VAR "BufferIndexVar" = "num:i(0)"!][!//
                [!IF "($ControllerIndex = num:i(0)) and ($KeySlotCountCtrl0 != num:i(0))"!][!//
                  [!VAR "KeySlotIdxStr" = "text:split($ArrKeySlotCtrl0,'@')[1]"!][!//
                  [!VAR "KeySlotFrIfLPduIdx" = "text:split($KeySlotIdxStr,'#')[2]"!][!//
                  [!VAR "BufferIndexVar" = "num:i(1)"!][!//
                [!ENDIF!][!//
                [!IF "($ControllerIndex = num:i(1)) and ($KeySlotCountCtrl1 != num:i(0))"!][!//
                  [!VAR "KeySlotIdxStr" = "text:split($ArrKeySlotCtrl1,'@')[1]"!][!//
                  [!VAR "KeySlotFrIfLPduIdx" = "text:split($KeySlotIdxStr,'#')[2]"!][!//
                  [!VAR "BufferIndexVar" = "num:i(1)"!][!//
                [!ENDIF!][!//
                [!FOR "k" = "num:i(0)" TO "num:i($LPduCount - 2)"!][!/* RECONFIG_FOR2 */!][!//
                  [!IF "($ControllerIndex = num:i(0)) and ($FifoExistCtrl0 = num:i(1))"!][!//
                    [!CALL "LpduIdExist","TempArray" = "$ArrFifoLpduCtrl0","Lpduid" = "$k","Count" = "$FifoCountCtrl0"!][!//
                  [!ENDIF!][!//
                  [!IF "($ControllerIndex = num:i(1)) and ($FifoExistCtrl1 = num:i(1))"!][!//
                    [!CALL "LpduIdExist","TempArray" = "$ArrFifoLpduCtrl1","Lpduid" = "$k","Count" = "$FifoCountCtrl1"!][!//
                  [!ENDIF!][!//
                  [!IF "$LpduExist = num:i(1)"!][!//
                    [!VAR "Cnt" = "$Cnt + num:i(1)"!][!//
                    [!IF "$Cnt > num:i(10)"!][!//
                      [!VAR "Cnt" = "num:i(0)"!]
                      [!//
                    [!ENDIF!][!//
                    255U, [!//
                  [!ELSE!][!//
                    [!IF "($KeySlotFrIfLPduIdx != num:i(4096)) and ($k = $KeySlotFrIfLPduIdx)"!][!//
                      [!VAR "Cnt" = "$Cnt + num:i(1)"!][!//
                      [!IF "$Cnt > num:i(10)"!][!//
                        [!VAR "Cnt" = "num:i(0)"!]
                        [!//
                      [!ENDIF!][!//
                      0U, [!//
                    [!ELSE!][!//
                      [!VAR "Cnt" = "$Cnt + num:i(1)"!][!//
                      [!IF "$Cnt > num:i(10)"!][!//
                        [!VAR "Cnt" = "num:i(0)"!]
                        [!//
                      [!ENDIF!][!//
                      [!"num:i($BufferIndexVar)"!]U, [!//
                      [!VAR "BufferIndexVar" = "$BufferIndexVar + num:i(1)"!][!//
                    [!ENDIF!][!//
                  [!ENDIF!][!//
                [!ENDFOR!][!/* RECONFIG_FOR2 */!][!//
              [!ENDINDENT!][!//
              [!IF "($ControllerIndex = num:i(0)) and ($FifoExistCtrl0 = num:i(1))"!][!//
                [!CALL "LpduIdExist","TempArray" = "$ArrFifoLpduCtrl0","Lpduid" = "($LPduCount - 1)","Count" = "$FifoCountCtrl0"!][!//
              [!ENDIF!][!//
              [!IF "($ControllerIndex = num:i(1)) and ($FifoExistCtrl1 = num:i(1))"!][!//
                [!CALL "LpduIdExist","TempArray" = "$ArrFifoLpduCtrl1","Lpduid" = "($LPduCount - 1)","Count" = "$FifoCountCtrl1"!][!//
              [!ENDIF!][!//
              [!IF "$LpduExist = num:i(1)"!][!//
                [!VAR "Cnt" = "$Cnt + num:i(1)"!][!//
                [!IF "$Cnt > num:i(10)"!][!//
                  [!VAR "Cnt" = "num:i(0)"!]
                  [!//
                [!ENDIF!][!//
                [!INDENT "2"!][!//
                  255U, [!//
                [!ENDINDENT!][!//
              };
              [!ELSE!][!//
                [!IF "($KeySlotFrIfLPduIdx != num:i(4096)) and (($LPduCount - 1) = $KeySlotFrIfLPduIdx)"!][!//
                  [!INDENT "2"!][!//
                    0U
                  [!ENDINDENT!][!//
                  };
                [!ELSE!][!//
                  [!"num:i($BufferIndexVar)"!]U
                  };
                  [!VAR "BufferIndexVar" = "$BufferIndexVar + num:i(1)"!][!//
                [!ENDIF!][!//
              [!ENDIF!][!//
              [!IF "$LPduCount > $BufferIndexVar"!][!//
                [!VAR "BufferIndexVar" = "$BufferIndexVar + num:i(1)"!][!//
              [!ENDIF!][!//
              [!VAR "FifoCalcDepthCtrl0" = "num:i(0)"!][!//
              [!IF "($ControllerIndex = num:i(0)) and ($FifoExistCtrl0 = num:i(1))"!][!//
                [!IF "$FifoDepthCtrl0 < $FifoCountCtrl0"!][!//
                  [!VAR "FifoCalcDepthCtrl0" = "$FifoDepthCtrl0"!][!//
                [!ELSE!][!//
                  [!VAR "FifoCalcDepthCtrl0" = "$FifoCountCtrl0"!][!//
                [!ENDIF!][!//
                [!VAR "BufferIndexVar" = "$BufferIndexVar + $FifoCalcDepthCtrl0 - num:i(1)"!][!//
              [!ENDIF!][!//
              [!VAR "FifoCalcDepthCtrl1" = "num:i(0)"!][!//
              [!IF "($ControllerIndex = num:i(1)) and ($FifoExistCtrl1 = num:i(1))"!][!//
                [!IF "$FifoDepthCtrl1 < $FifoCountCtrl1"!][!//
                  [!VAR "FifoCalcDepthCtrl1" = "$FifoDepthCtrl1"!][!//
                [!ELSE!][!//
                  [!VAR "FifoCalcDepthCtrl1" = "$FifoCountCtrl1"!][!//
                [!ENDIF!][!//
                [!VAR "BufferIndexVar" = "$BufferIndexVar + $FifoCalcDepthCtrl1 - num:i(1)"!][!//
              [!ENDIF!][!//
              /* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
              due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
              due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
              due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
              due to Autosar Naming constraints.*/
              [!/*
              [cover parentID={62808142-29D8-4845-8878-DFB01DAB6C52}] Fr_17_Eray_<ConfigShortName>_DataPointerOffset_<CtrlIdx> [/cover]
              */!][!//
              static const uint16 Fr_17_Eray_[!"$ConfigShortNamePath"!]_DataPointerOffset_[!"$ControllerIndex"!][[!"num:i($BufferIndexVar)"!]] =
              {
              [!INDENT "2"!][!//
                [!//
                [!VAR "Cnt" = "num:i(0)"!][!//
                [!/* Note: Data pointer is pointer to the first 32-bit word of the
                Data Section of the addressed Message Buffer in the Message RAM. */!][!//
                [!VAR "AdditionalElement" = "num:i(0)"!][!//
                [!VAR "TmpTotalCount" = "$LPduCount"!][!//
                [!IF "$ControllerIndex = num:i(0)"!][!//
                  [!IF "$FifoDepthCtrl0 < $FifoCountCtrl0"!][!//
                    [!VAR "TmpTotalCount" = "$LPduCount - $FifoCountCtrl0"!][!//
                    [!VAR "TmpTotalCount" = "$TmpTotalCount + $FifoDepthCtrl0"!][!//
                  [!ENDIF!][!//
                [!ENDIF!][!//
                [!IF "$ControllerIndex = num:i(1)"!][!//
                  [!IF "$FifoDepthCtrl1 < $FifoCountCtrl1"!][!//
                    [!VAR "TmpTotalCount" = "$LPduCount - $FifoCountCtrl1"!][!//
                    [!VAR "TmpTotalCount" = "$TmpTotalCount + $FifoDepthCtrl1"!][!//
                  [!ENDIF!][!//
                [!ENDIF!][!//
                [!VAR "DataPointerOffset" = "num:i($TmpTotalCount * 4)"!][!//
                [!VAR "FirstWrite" = "num:i(0)"!][!//
                [!IF "$KeySlotFrIfLPduIdx != num:i(4096)"!][!//
                  [!VAR "FirstWrite" = "num:i(1)"!][!//
                  [!SELECT "node:ref(FrIfLPdu/*[FrIfLPduIdx = $KeySlotFrIfLPduIdx]/FrIfVBTriggeringRef)"!][!//
                    [!"$DataPointerOffset"!]U[!//
                    [!IF "(FrIfLSduLength mod 4) = 0"!][!/* RECONFIG_IF3 */!][!//
                      [!VAR "DataPointerOffset" = "num:i($DataPointerOffset + (FrIfLSduLength div 4))"!][!//
                    [!ELSE!][!//
                      [!VAR "DataPointerOffset" = "num:i($DataPointerOffset + (FrIfLSduLength div 4) + 1)"!][!//
                    [!ENDIF!][!//
                  [!ENDSELECT!][!//
                [!ENDIF!][!//
                [!FOR "i" = "0" TO "$LPduCount - 1"!][!/* RECONFIG_FOR3 */!][!//
                  [!VAR "vCrcReg" = "0"!][!//
                  [!IF "$i != $KeySlotFrIfLPduIdx"!][!//
                    [!VAR "LPduIdxPath" = "node:path(FrIfLPdu/*[FrIfLPduIdx = $i])"!][!//
                    [!IF "($ControllerIndex = num:i(0)) and ($FifoExistCtrl0 = num:i(1))"!][!//
                      [!CALL "LpduIdExist","TempArray" = "$ArrFifoLpduCtrl0","Lpduid" = "$i","Count" = "$FifoCountCtrl0"!][!//
                    [!ENDIF!][!//
                    [!IF "($ControllerIndex = num:i(1)) and ($FifoExistCtrl1 = num:i(1))"!][!//
                      [!CALL "LpduIdExist","TempArray" = "$ArrFifoLpduCtrl1","Lpduid" = "$i","Count" = "$FifoCountCtrl1"!][!//
                    [!ENDIF!][!//
                    [!IF "$LpduExist = num:i(0)"!][!//
                      [!NOCODE!]
                        [!CALL "Fr_17_Eray_CG_GetLPduIdxPath", "LPduIdxPath" = "$LPduIdxPath"!][!//
                      [!ENDNOCODE!][!//
                      [!IF "$FirstWrite = num:i(1)"!][!//
                        , [!//
                      [!ENDIF!][!//
                      [!VAR "FirstWrite" = "num:i(1)"!][!//
                      [!SELECT "node:ref(FrIfLPdu/*[FrIfLPduIdx = $i]/FrIfVBTriggeringRef)"!][!/* RECONFIG_SELECT1 */!][!//
                        [!VAR "Cnt" = "$Cnt + num:i(1)"!][!//
                        [!IF "$Cnt > num:i(10)"!][!//
                          [!VAR "Cnt" = "num:i(0)"!]
                          [!//
                        [!ENDIF!][!//
                        [!"$DataPointerOffset"!]U[!//
                        [!IF "(FrIfLSduLength mod 4) = 0"!][!/* RECONFIG_IF3 */!][!//
                          [!VAR "DataPointerOffset" = "num:i($DataPointerOffset + (FrIfLSduLength div 4))"!][!//
                          [!ELSE!][!//
                          [!VAR "DataPointerOffset" = "num:i($DataPointerOffset + (FrIfLSduLength div 4) + 1)"!][!//
                        [!ENDIF!][!/* RECONFIG_IF3 */!][!//
                      [!ENDSELECT!][!/* RECONFIG_SELECT1 */!][!//
                    [!ELSE!][!//
                    [!VAR "AdditionalElement" = "num:i(1)"!][!//
                    [!ENDIF!][!//
                  [!ENDIF!][!//
                [!ENDFOR!][!/* RECONFIG_FOR3 */!][!//
                [!IF "$AdditionalElement = num:i(1)"!][!//
                  [!IF "($ControllerIndex = num:i(0))"!][!//
                    [!FOR "i" = "0" TO "$FifoCalcDepthCtrl0 - 1"!][!//
                      [!VAR "Cnt" = "$Cnt + num:i(1)"!][!//
                      [!IF "$Cnt > num:i(10)"!][!//
                        [!VAR "Cnt" = "num:i(0)"!]
                        [!//
                      [!ENDIF!][!//
                      , [!"$DataPointerOffset"!]U[!//
                      [!VAR "DataPointerOffset" = "num:i($DataPointerOffset + $FifoDlcCtrl0)"!][!//
                    [!ENDFOR!][!//
                  [!ENDIF!][!//
                  [!IF "($ControllerIndex = num:i(1))"!][!//
                    [!FOR "i" = "0" TO "$FifoCalcDepthCtrl1 - 1"!][!//
                      [!VAR "Cnt" = "$Cnt + num:i(1)"!][!//
                      [!IF "$Cnt > num:i(10)"!][!//
                        [!VAR "Cnt" = "num:i(0)"!]
                        [!//
                      [!ENDIF!][!//
                      , [!"$DataPointerOffset"!]U[!//
                      [!VAR "DataPointerOffset" = "num:i($DataPointerOffset + $FifoDlcCtrl1)"!][!//
                    [!ENDFOR!][!//
                  [!ENDIF!][!//
                [!ENDIF!]
              [!ENDINDENT!][!//
              };
              [!//
            [!ENDIF!][!/* RECONFIG_IF2 */!][!//
            [!VAR "CtrlRefFound" = "num:i(1)"!][!//
            [!BREAK!][!//
            [!ENDIF!][!/* RECONFIG_IF1 */!][!//
          [!ENDLOOP!][!/* RECONFIG_LOOP2 */!][!//
          [!IF "$CtrlRefFound = 1"!]
            [!BREAK!]
          [!ENDIF!][!//
        [!ENDLOOP!][!/* RECONFIG_LOOP1 */!][!//
      [!ENDSELECT!][!//
    [!ENDFOR!][!//
  [!ENDSELECT!][!//
  [!//
  [!//
  [!//
  [!/*
  Case 1: An FrController is not referred in any cluster in any of the FrIf (post-build) configurations
  ==> This is an error.
  Case 2: An FrController is referred in multiple clusters in any of the FrIf (post-build) configurations
  ==> In this case, first cluster (found by the XPath search) that refers to FrController is considered
  Case 3: An FrController is referred in multiple clusters in multiple FrIf (post-build) configurations
  ==> In this case, first cluster of first FrIf module confguration (found by the XPath search),
  that refers to FrController is considered
  */!][!//
  [!//
  [!SELECT "FrMultipleConfiguration"!][!//
    [!VAR "Counter" = "num:i(count(./FrController/*))"!][!//
    [!FOR "Index" = "0" TO "(num:i($Counter)- 1)"!][!//
    [!SELECT "./FrController/*[@index = $Index]"!][!//
      [!VAR "ControllerPath" = "node:path(.)"!][!//
      [!VAR "ControllerIndex" = "./FrCtrlIdx"!][!//
      [!/* ControllerPath path = [!"$ControllerPath"!]*/!][!//
      [!/* Example: ControllerPath = /AUTOSAR/TOP-LEVEL-PACKAGES/Fr/ELEMENTS/Fr/FrMultipleConfiguration/FrController/FrController_0 */!][!//
      [!VAR "ControllerShortNamePath" = "substring-after($ControllerPath, 'FrController')"!][!//
      [!/* Example: ControllerShortNamePath = /FrController_0 */!][!//
      [!/* Following variable is used to terminate the loop */!][!//
      [!VAR "CtrlRefFound" = "num:i(0)"!][!//
        [!LOOP "as:modconf('FrIf')[1]/FrIfConfig/FrIfCluster/*"!][!/* LPDU_CONFIG_LOOP2 */!][!//
          [!//
          [!VAR "ClusterChannels" = "FrIfGChannels"!][!//
          [!VAR "NumberOfStaticSlots" = "FrIfGNumberOfStaticSlots"!][!//
          [!VAR "PayloadLengthStatic" = "FrIfGPayloadLengthStatic"!][!//
          [!VAR "CurrentCluster" = "node:path(.)"!][!//
          [!LOOP "FrIfController/*"!][!/* LPDU_CONFIG_LOOP3 */!][!//
            [!VAR "FrIfControllerPath" = "node:ref(node:path(./FrIfFrCtrlRef))"!][!//
            [!VAR "FrConfigPath" = "substring-after($FrIfControllerPath, '/Fr/Fr/')"!][!//
            [!VAR "FrConfigPath" = "substring-before($FrConfigPath, $ControllerShortNamePath)"!][!//
            [!VAR "FrIfControllerPath" = "substring-after($FrIfControllerPath, $FrConfigPath)"!][!//
            [!IF "$FrIfControllerPath = $ControllerShortNamePath"!][!/* LPDU_CONFIG_IF1 */!][!//
              [!VAR "LPduCount" = "num:i(count(FrIfLPdu/*))"!][!//
              [!/* ---------  Config Rule FR_CR_204 ---------*/!][!//
              [!IF "$LPduCount >= num:i(255)"!][!//
                [!ERROR!][!//
                  Error: Number of LPdus configured ([!"$LPduCount"!] is more than supported (255, Id = 0 to 254).
                [!ENDERROR!][!//
              [!ENDIF!][!//
              [!/* ------------------------------------------*/!][!//
              [!VAR "PayloadLengthDynMax" = "node:value(node:ref(concat($ControllerPath, '/FrPPayloadLengthDynMax')))"!][!//
              [!VAR "KeySlotUsedForStartup" = "num:i(0)"!][!//
              [!VAR "KeySlotUsedForSync" = "num:i(0)"!][!//
              [!VAR "KeySlotId" = "num:i(2048)"!][!/* 2047 is maximum slot ID possible */!][!//
              [!IF "node:exists(concat($ControllerPath, '/FrPKeySlotId'))"!][!//
                [!VAR "KeySlotId" = "node:ref(concat($ControllerPath, '/FrPKeySlotId'))"!][!//
                [!/* ---------  Config Rule FR_CR_097 ---------*/!][!//
                [!IF "$KeySlotId > $NumberOfStaticSlots"!][!//
                  [!ERROR!][!//
                    Error: Key Slot ID of controller [!"$ControllerPath"!] corresponds to a dynamic slot.
                  [!ENDERROR!][!//
                [!ENDIF!][!//
                [!/* ------------------------------------------*/!][!//
                [!IF "node:value(node:ref(concat($ControllerPath, '/FrPKeySlotUsedForStartup'))) = 'true'"!][!//
                  [!VAR "KeySlotUsedForStartup" = "num:i(1)"!][!//
                [!ENDIF!][!//
                [!VAR "StaticLPduCount" = "num:i(0)"!][!//
                [!LOOP "FrIfLPdu/*"!][!/* LPDU_CONFIG_LOOP4 */!][!//
                  [!IF "(node:ref(FrIfVBTriggeringRef)/FrIfSlotId) <= $NumberOfStaticSlots"!][!//
                    [!VAR "StaticLPduCount" = "num:i($StaticLPduCount + 1)"!][!//
                  [!ENDIF!][!//
                [!ENDLOOP!][!/* LPDU_CONFIG_LOOP4 */!][!//
                [!IF "node:value(node:ref(concat($ControllerPath, '/FrPKeySlotUsedForSync'))) = 'true'"!][!//
                  [!VAR "KeySlotUsedForSync" = "num:i(1)"!][!//
                [!ENDIF!][!//
              [!ENDIF!][!//
              [!//
              [!VAR "LatestTx" = "node:ref(concat($ControllerPath, '/FrPLatestTx'))"!][!//
              [!VAR "NumberOfStaticSlots" = "num:i(node:value(concat($CurrentCluster,'/FrIfGNumberOfStaticSlots')))"!][!//
              [!VAR "NumberOfMinislots" = "num:i(node:value(concat($CurrentCluster,'/FrIfGNumberOfMinislots')))"!][!//
              [!/* ---------  Config Rule FR_CR_092 ---------*/!][!//
              [!IF "($LatestTx > $NumberOfMinislots)"!][!//
                [!ERROR!][!//
                Error: PLatestTx [!"$LatestTx"!] is greater than number of configured Minislots - [!"$NumberOfMinislots"!]
                [!ENDERROR!][!//
              [!ENDIF!][!//
              [!/* ------------------------------------------*/!][!//
              [!//
              [!VAR "WakeupChannel" = "node:ref(concat($ControllerPath, '/FrPWakeupChannel'))"!][!//
              [!VAR "WakeupChannel2" = "substring-after($WakeupChannel, 'FR_CHANNEL_')"!][!//
              [!VAR "Channels" = "node:ref(concat($ControllerPath, '/FrPChannels'))"!][!//
              [!VAR "PChannels2" = "substring-after($Channels, 'FR_CHANNEL_')"!][!//
              [!VAR "GChannels2" = "substring-after($ClusterChannels, 'FR_CHANNEL_')"!][!//
              [!/* ---------  Config Rule FR_CR_213 ---------*/!][!//
              [!IF "not(contains($PChannels2, $WakeupChannel2))"!][!//
                [!ERROR!][!//
                Error: Wakeup channel can not be [!"$WakeupChannel"!] when CC channel configuration FrPChannels is [!"$Channels"!]
                [!ENDERROR!][!//
              [!ENDIF!][!//
              [!/* ------------------------------------------*/!][!//
              [!/* ---------  Config Rule FR_CR_099 ---------*/!][!//
              [!IF "not(contains($GChannels2, $PChannels2))"!][!//
                [!ERROR!][!//
                  Error: Node channel configuration (FrPChannels) can not be [!"$Channels"!] when cluster channel configuration (GChannels) is [!"$ClusterChannels"!]
                [!ENDERROR!][!//
              [!ENDIF!][!//
              [!/* ------------------------------------------*/!][!//
              [!//
              /*************** LPDU configuration Controller [!"$ControllerIndex"!] ***************/
              /* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
              due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
              due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
              due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
              due to Autosar Naming constraints.*/
              [!/*
              [cover parentID={FF5BF668-CAB5-4379-ACED-AC031AD2926D}] Fr_17_Eray_<ConfigShortName>_kLPduConfig_<CtrlIdx> [/cover]
              */!][!//
              static const Fr_17_Eray_LPduConfigType Fr_17_Eray_[!"$ConfigShortNamePath"!]_kLPduConfig_[!"$ControllerIndex"!] [[!"$LPduCount"!]] =
              {
              [!INDENT "2"!][!//
                [!/*
                [cover parentID={886E3513-28DA-4af5-A070-12A555297BF9}] Start with the lowest LPdu [/cover]
                */!][!//
                [!/*
                [cover parentID={F4FD738E-CBCF-4955-9D70-8DD4F0A9C5E2}] Loop till the last configured LPdu [/cover]
                */!][!//
                [!FOR "i" = "0" TO "$LPduCount - 1"!][!/* LPDU_CONFIG_FOR2 */!][!//
                  [!VAR "vWRHS2" = "num:i(0)"!][!//
                  [!VAR "vCrcReg" = "0"!][!//
                  [!VAR "LPduIdxPath" = "node:path(FrIfLPdu/*[FrIfLPduIdx = $i])"!][!//
                  [!NOCODE!]
                    [!CALL "Fr_17_Eray_CG_GetLPduIdxPath", "LPduIdxPath" = "$LPduIdxPath"!][!//
                  [!ENDNOCODE!][!//
                  [!SELECT "node:ref(FrIfLPdu/*[FrIfLPduIdx = $i]/FrIfVBTriggeringRef)"!][!/* LPDU_CONFIG_SELECT1 */!][!//
                    [!NOCODE!]
                      [!//
                      [!/*
                      [cover parentID={FF778F2E-B343-42c4-A6E3-FFB6FFD409B9}] Find out the LPdu direction [/cover]
                      */!][!//
                      [!/* Find out the LPDU direction */!][!//
                      [!IF "FrIfAlwaysTransmit = 'true'"!][!//
                        [!VAR "LPduTxStatus" = "num:i(1)"!][!//
                      [!ELSE!][!//
                        [!CALL "Fr_17_Eray_CG_MsBufDir", "CurrentCluster" = "$CurrentCluster", "LPduIdxPath" = "$LPduIdxPath"!][!//
                      [!ENDIF!][!//
                      [!//
                      [!/****************** Start of Header CRC calculation *******************/!][!//
                      [!VAR "CurrentSlotId" = "FrIfSlotId"!][//
                      [!IF "FrIfSlotId > $NumberOfStaticSlots"!][!/* Dynamic frame */!][!//
                        [!VAR "LSduLength16BitWords" = "FrIfLSduLength div 2"!][//
                        [!CALL "Fr_17_Eray_CG_HeaderCRC", "Sync" = "num:i(0)", "Sfi" = "num:i(0)", "Fid" = "FrIfSlotId", "Plc" = "$LSduLength16BitWords"!][!//
                      [!ELSE!][!/* Static frame */!][!//
                        [!IF "FrIfSlotId = $KeySlotId"!][!/* Key slot frame (one of the static frames)*/!][!//
                          [!/* ---------  Config Rule FR_CR_210 ---------*/!][!//
                          [!IF "$LPduTxStatus = num:i(0)"!][!//
                            [!ERROR!][!//
                              Error: Key slot ([!"$KeySlotId"!]) is not configured to be used as a transmit frame/ LPdu for [!"$ControllerPath"!]
                            [!ENDERROR!][!//
                          [!ENDIF!][!//
                          [!/* ------------------------------------------*/!][!//
                          [!/*
                          Note: $PayloadLengthStatic is already in terms of 16 bit words since
                          GPayloadLengthStatic is mentioned in terms of 16 bit words
                          */!][!//
                          [!CALL "Fr_17_Eray_CG_HeaderCRC", "Sync" = "$KeySlotUsedForSync", "Sfi" = "$KeySlotUsedForStartup", "Fid" = "FrIfSlotId", "Plc" = "$PayloadLengthStatic"!][!//
                        [!ELSE!][!//
                          [!/* Not a keyslot id frame : Sync = 0, Sfi = 0 */!][!//
                          [!CALL "Fr_17_Eray_CG_HeaderCRC", "Sync" = "num:i(0)", "Sfi" = "num:i(0)", "Fid" = "FrIfSlotId", "Plc" = "$PayloadLengthStatic"!][!//
                        [!ENDIF!][!/* KeySlot or not ? */!][!//
                      [!ENDIF!][!/* Static or dynamic ? */!][!//
                      [!/****************** End of Header CRC calculation *********************/!][!//
                      [!//
                      [!VAR "CtrlChCfg" = "substring-after(node:value(concat($ControllerPath, '/FrPChannels')), '_')"!]
                      [!VAR "LpduChCfg" = "substring-after(FrIfChannel, '_')"!]
                      [!IF "$CtrlChCfg != 'CHANNEL_AB'"!]
                        [!/* ---------  Config Rule FR_CR_212 ---------*/!][!//
                        [!IF "$CtrlChCfg != $LpduChCfg"!]
                          [!ERROR!][!//
                            Error: Channel configuration for LPdu [!"$i"!] ([!"$LpduChCfg"!]) is not consistent with channel configuration on CC ([!"$CtrlChCfg"!]).
                          [!ENDERROR!][!//
                        [!ENDIF!][!//
                        [!/* ------------------------------------------*/!][!//
                      [!ENDIF!][!//
                    [!ENDNOCODE!][!//
                    /* -------------------------  LPDU [!"$i"!] ------------------------------- */
                    {
                    [!INDENT "4"!][!//
                      [!VAR "vWRHS1" = "num:i(0)"!][!//
                      [!VAR "TempWrhs1Val" = "num:i(0)"!][!//
                      /*
                      [!"FrIfSlotId"!]U - Slot ID
                      [!VAR "vWRHS1" = "bit:or($vWRHS1,bit:shl(FrIfSlotId,0))"!][!//
                      [!/* ---------  Config Rule FR_CR_206 ---------*/!][!//
                      [!IF "FrIfBaseCycle >= FrIfCycleRepetition"!][!//
                        [!ERROR!][!//
                          Error: FrIfBaseCycle ([!"FrIfBaseCycle"!]) is not less than FrIfCycleRepetition ([!"FrIfCycleRepetition"!]) for frame [!"node:path(.)"!]
                        [!ENDERROR!][!//
                      [!ENDIF!][!//
                      [!/* ------------------------------------------*/!][!//
                      [!"num:i(FrIfCycleRepetition + FrIfBaseCycle)"!]U - Cycle code
                      [!VAR "TempWrhs1Val" = "num:i(FrIfCycleRepetition + FrIfBaseCycle)"!][!//
                      [!VAR "vWRHS1" = "bit:or($vWRHS1,bit:shl($TempWrhs1Val,16))"!][!//
                      [!IF "substring-after(FrIfChannel,'_') = 'CHANNEL_AB'"!][!//
                        3U,[!//
                        [!VAR "vWRHS1" = "bit:or($vWRHS1,bit:shl(3,24))"!][!//
                      [!ELSEIF "substring-after(FrIfChannel,'_') = 'CHANNEL_B'"!][!//
                        2U,[!//
                        [!VAR "vWRHS1" = "bit:or($vWRHS1,bit:shl(2,24))"!][!//
                      [!ELSE!][!//
                        1U,[!//
                        [!VAR "vWRHS1" = "bit:or($vWRHS1,bit:shl(1,24))"!][!//
                      [!ENDIF!][!//
                       - FrPChannels , add 0x1 as the hw regs take ChannelA = 1, ChannelB = 2
                       and ChannelAB = 3
                      [!"$LPduTxStatus"!]U - Message Buffer Direction: 0 - Receive, 1 - Transmit
                      [!VAR "vWRHS1" = "bit:or($vWRHS1,bit:shl($LPduTxStatus,26))"!][!//
                      [!IF "FrIfPayloadPreamble = 'true'"!][!//
                        1U[!//
                        [!VAR "vWRHS1" = "bit:or($vWRHS1,bit:shl(1,27))"!][!//
                      [!ELSE!][!//
                        0U[!//
                      [!ENDIF!], - PPIT: 0 - Disable, 1 - Enable
                      1U, - Transmission Mode : 1 - Single shot - always single shot
                      [!VAR "vWRHS1" = "bit:or($vWRHS1,bit:shl(1,28))"!][!//
                      0U  - Message Buffer Service Request - always set to 0
                      */
                      [!"num:inttohex($vWRHS1,8)"!]U,
                      /*
                      [!IF "$LPduTxStatus = num:i(1)"!][!//
                        [!"$vCrcReg"!]U - Header CRC
                      [!VAR "TempVal" = "num:hextoint($vCrcReg)"!][!//
                      [!VAR "vWRHS2" = "bit:or($vWRHS2,bit:shl($TempVal,0))"!][!//
                      [!ELSE!][!//
                        0x0U - Header CRC
                      [!ENDIF!][!//
                      [!/* ---------  Config Rule FR_CR_203 ---------*/!][!//
                      [!IF "num:i(FrIfLSduLength mod 2) != num:i(0)"!][!//
                        [!ERROR!][!//
                          Error: LSDU length for frame [!"node:path(.)"!] is not even number ([!"FrIfLSduLength"!])
                        [!ENDERROR!][!//
                      [!ENDIF!][!//
                      [!/* ------------------------------------------*/!][!//
                      [!//
                      [!IF "FrIfSlotId <= $NumberOfStaticSlots"!][!//
                        [!/* ---------  Config Rule FR_CR_216 ---------*/!][!//
                        [!IF "num:i(FrIfLSduLength div 2) > $PayloadLengthStatic"!][!//
                          [!ERROR!][!//
                            Error: LSDU length for frame [!"node:path(.)"!] ([!"num:i(FrIfLSduLength div 2)"!] 16-bit words) is more than gPayloadLengthStatic ([!"$PayloadLengthStatic"!] 16-bit words)
                          [!ENDERROR!][!//
                        [!ENDIF!][!//
                        [!/* ------------------------------------------*/!][!//
                      [!ELSE!][!//
                        [!/* ---------  Config Rule FR_CR_217 ---------*/!][!//
                        [!IF "num:i(FrIfLSduLength div 2) > $PayloadLengthDynMax"!][!//
                          [!ERROR!][!//
                            Error: LSDU length for frame [!"node:path(.)"!] ([!"num:i(FrIfLSduLength div 2)"!] 16-bit words) is more than PPayloadLengthDynMax ([!"$PayloadLengthDynMax"!] 16-bit words)
                          [!ENDERROR!][!//
                        [!ENDIF!][!//
                        [!/* ------------------------------------------*/!][!//
                      [!ENDIF!][!//
                      [!IF "((./FrIfSlotId <= $NumberOfStaticSlots) and (./FrIfAllowDynamicLSduLength = 'true')) "!][!//
                        [!ERROR!][!//
                          Error: LPdu [!"node:path(.)"!] is configured as static frame and  FrIfAllowDynamicLSduLength is configured.
                          FrIfAllowDynamicLSduLength should not enabled for static frames.
                        [!ENDERROR!][!//
                      [!ENDIF!][!//
                      [!/* Note: WRHS2.B.PLC is length of Data Section (number of 2-byte words)
                      as configured by the Host. */!][!//
                      [!"num:i(FrIfLSduLength div 2)"!]U - Payload Length Configured
                      [!CALL "Fr_17_Eray_CG_ConfigSwitch2", "nodeval" = "FrIfAllowDynamicLSduLength"!]U - FrIfAllowDynamicLSduLength
                      */
                      [!VAR "TempVal" = "num:i(FrIfLSduLength div 2)"!][!//
                      [!VAR "vWRHS2" = "bit:or($vWRHS2,bit:shl($TempVal,16))"!][!//
                      [!IF "(./FrIfAllowDynamicLSduLength = 'true')"!][!//
                        [!VAR "vWRHS2" = "bit:or($vWRHS2,bit:shl(1,23))"!][!//
                      [!ENDIF!][!//
                      [!"num:inttohex($vWRHS2,8)"!]U,
                      [!/* Generate LPDU Reconfigurable Flag */!][!//
                    [!ENDINDENT!][!//
                  [!ENDSELECT!][!/* LPDU_CONFIG_SELECT1 */!][!//
                  [!SELECT "FrIfLPdu/*[FrIfLPduIdx = $i]"!][!//
                    [!INDENT "4"!][!//
                      [!IF "FrIfReconfigurable = 'true'"!][!//
                        [!IF "($KeySlotUsedForSync = num:i(1)) and ($KeySlotUsedForStartup = num:i(1))"!][!//
                          [!IF "$CurrentSlotId = $KeySlotId"!][!//
                            [!ERROR!][!//
                              Error: Key slot ([!"$KeySlotId"!]) frame/ LPdu can not be reconfigured as it is used for sync frame transmission.
                            [!ENDERROR!][!//
                          [!ENDIF!][!//
                        [!ENDIF!][!//
                        FR_17_ERAY_LPDU_RECONFIGURABLE,
                      [!ELSE!][!//
                        FR_17_ERAY_LPDU_NOT_RECONFIGURABLE,
                      [!ENDIF!][!//
                      /*DEM Id for FlexRay Slot Status Error. */
                      [!SELECT "node:ref(FrIfVBTriggeringRef)"!][!//
                        [!/*
                        [cover parentID={EDDF8786-B782-49b4-A99A-FD3C27F52D7B}] FRIF_E_LPDU_SLOTSTATUS - production error [/cover]
                        */!][!//
                        [!IF "(node:exists(./FrIfFrameTriggeringDemEventParameterRefs/*[1]/FRIF_E_LPDU_SLOTSTATUS/*[1]) = 'true') and (node:value(./FrIfFrameTriggeringDemEventParameterRefs/*[1]/FRIF_E_LPDU_SLOTSTATUS/*[1]) != ' ')"!][!//
                          DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./FrIfFrameTriggeringDemEventParameterRefs/*[1]/FRIF_E_LPDU_SLOTSTATUS/*[1])))"!]
                        [!ELSE!][!//
                          FR_17_ERAY_DEM_REPORT_DISABLED
                        [!ENDIF!][!//
                      [!ENDSELECT!][!//
                    [!ENDINDENT!][!//
                  [!ENDSELECT!][!//
                  [!SELECT "node:ref(FrIfLPdu/*[FrIfLPduIdx = $i]/FrIfVBTriggeringRef)"!][!/* LPDU_CONFIG_SELECT1 */!][!//
                    }[!//
                    [!IF "$i < ($LPduCount - 1)"!][!//
                      ,
                    [!ENDIF!][!//
                  [!ENDSELECT!][!/* LPDU_CONFIG_SELECT1 */!][!//
                [!ENDFOR!][!/* LPDU_CONFIG_FOR2 */!][!//
              [!ENDINDENT!]
              };

              [!VAR "FrIfNodePath" = "$CurrentCluster"!][!//
              [!//
              [!/* ---------  Config Rule FR_CR_200 ---------*/!][!//
              [!IF "node:value(concat($FrIfNodePath,'/FrIfGdSampleClockPeriod')) != 'T12_5NS'"!][!//
                [!ERROR!][!//
                  Error: FlexRay driver supports only 80Mbps. Hence GdSampleClockPeriod should be T12_5NS.
                [!ENDERROR!][!//
              [!ENDIF!][!//
              [!/* ------------------------------------------*/!][!//
              [!/* ---------  Config Rule FR_CR_219 ---------*/!][!//
              [!IF "node:value(concat($FrIfNodePath,'/FrIfGdBit')) != 'T100NS'"!][!//
                [!ERROR!][!//
                  Error: FrIfGdBit shall be 4 times Microtick duration. FrPdMicrotick is fixed at T25NS.Also
                  gdBit[micro second] = cSamplesPerBit * gdSampleClockPeriod[micro second] and cSamplesPerBit = 8 and gdSampleClockPeriod T12_5NS.
                [!ENDERROR!][!//
              [!ENDIF!][!//
              [!/* ------------------------------------------*/!][!//
              [!//
              [!/* ---------  Config Rule FR_CR_201 ---------*/!][!//
              [!IF "num:i(node:value(concat($FrIfNodePath,'/FrIfGdWakeupRxLow'))) < num:i(11)"!][!//
                [!ERROR!][!//
                  Error: Minimum value gdWakeupSymbolRxLow should be 11. This is required to take care of FlexRay Protocol 2.1 Rev. A compliance.
                [!ENDERROR!][!//
              [!ENDIF!][!//
              [!/* ------------------------------------------*/!][!//
              [!//
              /***** Communication controller configuration Controller [!"$ControllerIndex"!]  *****/
              /* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
              due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
              due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
              due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
              due to Autosar Naming constraints.*/
              [!/*
              [cover parentID={A85E5128-012E-4932-B7F8-B5B2F689DBC2}] Fr_17_Eray_<ConfigShortName>_kCCCfg_<CtrlIdx> [/cover]
              */!][!//
              static const Fr_17_Eray_CCConfigType Fr_17_Eray_[!"$ConfigShortNamePath"!]_kCCCfg_[!"$ControllerIndex"!] =
              {
              [!INDENT "2"!][!//
                /* SUCC1 register configuration */
                [!NOCODE!][!//
                [!ENDNOCODE!][!//
                [!NOCODE!][!//
                  [!VAR "vSUCC1" = "num:i(0)"!][!//
                  [!IF "(node:value(concat($ControllerPath, '/FrPKeySlotUsedForStartup')) = 'true')"!][!//
                    [!VAR "vSUCC1" = "bit:or($vSUCC1,bit:shl(1,8))"!][!//
                  [!ENDIF!][!//
                  [!IF "(node:value(concat($ControllerPath, '/FrPKeySlotUsedForSync')) = 'true')"!][!//
                    [!VAR "vSUCC1" = "bit:or($vSUCC1,bit:shl(1,9))"!][!//
                  [!ENDIF!][!//
                  [!VAR "TempSucc1Val" = "num:i(node:value(concat($FrIfNodePath,'/FrIfGColdStartAttempts')))"!][!//
                  [!VAR "vSUCC1" = "bit:or($vSUCC1,bit:shl($TempSucc1Val,11))"!][!//
                  [!VAR "TempSucc1Val" = "num:i(node:value(concat($ControllerPath, '/FrPAllowPassiveToActive')))"!][!//
                  [!VAR "vSUCC1" = "bit:or($vSUCC1,bit:shl($TempSucc1Val,16))"!][!//
                  [!IF "node:value(concat($ControllerPath, '/FrPWakeupChannel')) = 'FR_CHANNEL_A'"!][!//
                    [!VAR "vSUCC1" = "bit:or($vSUCC1,bit:shl(0,21))"!][!// /* FrPWakeupChannel */
                  [!ELSE!][!//
                    [!VAR "vSUCC1" = "bit:or($vSUCC1,bit:shl(1,21))"!][!// /* FrPWakeupChannel */
                  [!ENDIF!][!//
                  [!IF "(node:value(concat($ControllerPath, '/FrPKeySlotOnlyEnabled')) = 'true')"!][!//
                    [!VAR "vSUCC1" = "bit:or($vSUCC1,bit:shl(1,22))"!][!//
                  [!ENDIF!][!//
                  [!IF "(node:value(concat($ControllerPath, '/FrPAllowHaltDueToClock')) = 'true')"!][!//
                    [!VAR "vSUCC1" = "bit:or($vSUCC1,bit:shl(1,23))"!][!//
                  [!ENDIF!][!//
                  [!IF "node:value(concat($ControllerPath, '/FrPChannels')) = 'FR_CHANNEL_AB'"!][!//
                    [!VAR "vSUCC1" = "bit:or($vSUCC1,bit:shl(3,26))"!][!//
                  [!ELSEIF "node:value(concat($ControllerPath, '/FrPChannels')) = 'FR_CHANNEL_B'"!][!//
                    [!VAR "vSUCC1" = "bit:or($vSUCC1,bit:shl(2,26))"!][!//
                  [!ELSE!][!//
                    [!VAR "vSUCC1" = "bit:or($vSUCC1,bit:shl(1,26))"!][!//
                  [!ENDIF!][!//
                [!ENDNOCODE!][!//
                /*
                0U - CmdPOCBusy (Unused member)
                [!CALL "Fr_17_Eray_CG_ConfigSwitch2", "nodeval" = "node:value(concat($ControllerPath, '/FrPKeySlotUsedForStartup'))"!]U - pKeySlotUsedForStartup
                [!CALL "Fr_17_Eray_CG_ConfigSwitch2", "nodeval" = "node:value(concat($ControllerPath, '/FrPKeySlotUsedForSync'))"!]U - pKeySlotUsedForSync
                0U - Reserved bit
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGColdStartAttempts')))"!]U - FrIfGColdStartAttempts
                [!"node:value(concat($ControllerPath, '/FrPAllowPassiveToActive'))"!]U - FrPAllowPassiveToActive
                [!IF "node:value(concat($ControllerPath, '/FrPWakeupChannel')) = 'FR_CHANNEL_A'"!][!//
                  0U - FrPWakeupChannel
                [!ELSE!][!//
                  1U - FrPWakeupChannel
                [!ENDIF!][!//
                [!CALL "Fr_17_Eray_CG_ConfigSwitch2", "nodeval" = "node:value(concat($ControllerPath, '/FrPKeySlotOnlyEnabled'))"!]U - FrPKeySlotOnlyEnabled in FlexRay Protocol 2.1 Rev. A
                [!CALL "Fr_17_Eray_CG_ConfigSwitch2", "nodeval" = "node:value(concat($ControllerPath, '/FrPAllowHaltDueToClock'))"!]U - FrPAllowHaltDueToClock
                0U - pChannelsMTS (Unused), 0 means no channels selected
                [!IF "node:value(concat($ControllerPath, '/FrPChannels')) = 'FR_CHANNEL_AB'"!][!//
                  3U[!//
                [!ELSEIF "node:value(concat($ControllerPath, '/FrPChannels')) = 'FR_CHANNEL_B'"!][!//
                  2U[!//
                [!ELSE!][!//
                  1U[!//
                [!ENDIF!][!//
                - FrPChannels, add 0x1 as the hw regs take ChannelA = 1, ChannelB = 2 and ChannelAB = 3
                */
                [!"num:inttohex($vSUCC1,8)"!]U,
                /* SUCC2 register settings */
                [!NOCODE!][!//
                  [!VAR "vSUCC2" = "num:i(0)"!][!//
                  [!VAR "TempSucc2Val" = "num:i(node:value(concat($ControllerPath, '/FrPdListenTimeout')))"!][!//
                  [!VAR "vSUCC2" = "bit:or($vSUCC2,bit:shl($TempSucc2Val,0))"!][!//
                  [!VAR "TempSucc2Val" = "num:i((node:value(concat($FrIfNodePath,'/FrIfGListenNoise')))-1)"!][!//
                  [!VAR "vSUCC2" = "bit:or($vSUCC2,bit:shl($TempSucc2Val,24))"!][!//
                [!ENDNOCODE!][!//
                /*
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPdListenTimeout')))"!]U - FrPdListenTimeout
                [!"num:inttohex(num:i((node:value(concat($FrIfNodePath,'/FrIfGListenNoise')))-1))"!]U - (FrIfGListenNoise - 1)
                */
                [!"num:inttohex($vSUCC2,8)"!]U,
                /* SUCC3 register settings */
                [!NOCODE!][!//
                  [!VAR "vSUCC3" = "num:i(0)"!][!//
                  [!VAR "TempSucc3Val" = "num:i(node:value(concat($FrIfNodePath,'/FrIfGMaxWithoutClockCorrectPassive')))"!][!//
                  [!VAR "vSUCC3" = "bit:or($vSUCC3,bit:shl($TempSucc3Val,0))"!][!//
                  [!VAR "TempSucc3Val" = "num:i(node:value(concat($FrIfNodePath,'/FrIfGMaxWithoutClockCorrectFatal')))"!][!//
                  [!VAR "vSUCC3" = "bit:or($vSUCC3,bit:shl($TempSucc3Val,4))"!][!//
                [!ENDNOCODE!][!//
                /*
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGMaxWithoutClockCorrectPassive')))"!]U - FrIfGMaxWithoutClockCorrectPassive
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGMaxWithoutClockCorrectFatal')))"!]U - FrIfGMaxWithoutClockCorrectFatal
                */
                [!"num:inttohex($vSUCC3,8)"!]U,
                /* NEMC register settings */
                /*
                [!"num:inttohex(num:i(node:value(concat($FrIfNodePath,'/FrIfGNetworkManagementVectorLength'))))"!]U - FrIfGNetworkManagementVectorLength
                */
                [!"num:inttohex(num:i(node:value(concat($FrIfNodePath,'/FrIfGNetworkManagementVectorLength'))), 8)"!]U,
                /* PRTC1 register settings */
                [!NOCODE!][!//
                  [!VAR "vPRTC1" = "num:i(0)"!][!//
                  [!VAR "FrTSSTransmitter" = "num:i(node:value(concat($FrIfNodePath,'/FrIfGdTSSTransmitter')))"!][!//
                  [!/* ---------  Config Rule FR_CR_205 ---------*/!][!//
                  [!IF "(($FrTSSTransmitter < 3) or ($FrTSSTransmitter > 15))"!][!//
                    [!ERROR!][!//
                      Error: Duration of the Transmission Start Sequence (TSS) of cluster [!"$FrIfNodePath"!] (FrIfGdTSSTransmitter) not in valid range. Valid range:3 to 15 as per hardware user manual.See the PRTC1 register description.
                    [!ENDERROR!][!//
                  [!ENDIF!][!//
                  [!/* ------------------------------------------*/!][!//
                  [!VAR "vPRTC1" = "bit:or($vPRTC1,bit:shl($FrTSSTransmitter,0))"!][!//
                  [!VAR "FrCASRxLowMax" = "num:i(node:value(concat($FrIfNodePath,'/FrIfGdCasRxLowMax')))"!][!//
                  [!/* ---------  Config Rule FR_CR_207 ---------*/!][!//
                  [!IF "($FrCASRxLowMax < 67) or ($FrCASRxLowMax > 99)"!][!//
                    [!ERROR!][!//
                      Error: Upper limit of the acceptance window for a collision avoidance symbol (CAS) of cluster [!"$FrIfNodePath"!] (FrIfGdCasRxLowMax) not in valid range. Valid range:67(43H) to 99(63H) as per hardware user manual.See the PRTC1 register description.
                    [!ENDERROR!][!//
                  [!ENDIF!][!//
                  [!/* ------------------------------------------*/!][!//
                  [!VAR "vPRTC1" = "bit:or($vPRTC1,bit:shl($FrCASRxLowMax,4))"!][!//
                  [!VAR "TempPRTC1Val" = "num:i(node:value(concat($FrIfNodePath,'/FrIfGdWakeupRxWindow')))"!][!//
                  [!VAR "vPRTC1" = "bit:or($vPRTC1,bit:shl($TempPRTC1Val,16))"!][!//
                  [!VAR "TempPRTC1Val" = "num:i(node:value(concat($ControllerPath, '/FrPWakeupPattern')))"!][!//
                  [!VAR "vPRTC1" = "bit:or($vPRTC1,bit:shl($TempPRTC1Val,26))"!][!//
                [!ENDNOCODE!][!//
                /*
                [!"num:inttohex($FrTSSTransmitter)"!]U - FrIfGdTSSTransmitter
                [!"num:inttohex($FrCASRxLowMax)"!]U - FrIfGdCasRxLowMax
                0U - Strobe Point Position. Always zero (default)
                0U - BRP. Always zero as driver supports only 10Mbps rate
                [!"num:inttohex(num:i(node:value(concat($FrIfNodePath,'/FrIfGdWakeupRxWindow'))))"!]U - FrIfgdWakeupRxWindow
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPWakeupPattern')))"!]U - FrPWakeupPattern
                */
                [!"num:inttohex($vPRTC1,8)"!]U,
                /* PRTC2 register settings */
                [!NOCODE!][!//
                  [!VAR "vPRTC2" = "num:i(0)"!][!//
                  [!VAR "TempPRTC2Val" = "num:i(node:value(concat($FrIfNodePath,'/FrIfGdWakeupRxIdle')))"!][!//
                  [!VAR "vPRTC2" = "bit:or($vPRTC2,bit:shl($TempPRTC2Val,0))"!][!//
                  [!VAR "TempPRTC2Val" = "num:i(node:value(concat($FrIfNodePath,'/FrIfGdWakeupRxLow')))"!][!//
                  [!VAR "vPRTC2" = "bit:or($vPRTC2,bit:shl($TempPRTC2Val,8))"!][!//
                  [!VAR "TempPRTC2Val" = "num:i(node:value(concat($FrIfNodePath,'/FrIfGdWakeupTxIdle')))"!][!//
                  [!VAR "vPRTC2" = "bit:or($vPRTC2,bit:shl($TempPRTC2Val,16))"!][!//
                  [!VAR "TempPRTC2Val" = "num:i(node:value(concat($FrIfNodePath,'/FrIfGdWakeupTxActive')))"!][!//
                  [!VAR "vPRTC2" = "bit:or($vPRTC2,bit:shl($TempPRTC2Val,24))"!][!//
                [!ENDNOCODE!][!//
                /*
                [!"num:inttohex(num:i(node:value(concat($FrIfNodePath,'/FrIfGdWakeupRxIdle'))))"!]U - FrIfgdWakeupRxIdle
                [!"num:inttohex(num:i(node:value(concat($FrIfNodePath,'/FrIfGdWakeupRxLow'))))"!]U - FrIfgdWakeupRxLow
                [!"num:inttohex(num:i(node:value(concat($FrIfNodePath,'/FrIfGdWakeupTxIdle'))))"!]U - FrIfGdWakeupTxIdle
                [!"num:inttohex(num:i(node:value(concat($FrIfNodePath,'/FrIfGdWakeupTxActive'))))"!]U - FrIfGdWakeupTxActive
                */
                [!"num:inttohex($vPRTC2,8)"!]U,
                /* MHDC register settings */
                [!NOCODE!][!//
                  [!VAR "vMHDC" = "num:i(0)"!][!//
                  [!VAR "TempMHDCVal" = "num:i(node:value(concat($FrIfNodePath,'/FrIfGPayloadLengthStatic')))"!][!//
                  [!VAR "vMHDC" = "bit:or($vMHDC,bit:shl($TempMHDCVal,0))"!][!//
                  [!VAR "TempMHDCVal" = "num:i(node:value(concat($ControllerPath, '/FrPLatestTx')))"!][!//
                  [!VAR "vMHDC" = "bit:or($vMHDC,bit:shl($TempMHDCVal,16))"!][!//
                [!ENDNOCODE!][!//
                /*
                [!"num:inttohex(num:i(node:value(concat($FrIfNodePath,'/FrIfGPayloadLengthStatic'))))"!]U - FrIfGPayloadLengthStatic
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPLatestTx')))"!]U - FrPLatestTx
                */
                [!"num:inttohex($vMHDC,8)"!]U,
                /* GTUC01 register settings */
                /*
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPMicroPerCycle')))"!]U - UT: FrPMicroPerCycle
                */
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPMicroPerCycle')), 8)"!]U,
                /* GTUC02 register settings */
                [!NOCODE!][!//
                  [!VAR "vGTUC02" = "num:i(0)"!][!//
                  [!VAR "TempGTUC02Val" = "num:i(node:value(concat($FrIfNodePath,'/FrIfGMacroPerCycle')))"!][!//
                  [!VAR "vGTUC02" = "bit:or($vGTUC02,bit:shl($TempGTUC02Val,0))"!][!//
                  [!VAR "TempGTUC02Val" = "num:i(node:value(concat($FrIfNodePath,'/FrIfGSyncFrameIDCountMax')))"!][!//
                  [!VAR "vGTUC02" = "bit:or($vGTUC02,bit:shl($TempGTUC02Val,16))"!][!//
                    /* FrIfGSyncFrameIDCountMax maps to FrIfGSyncNodeMax FR Pr 2.1, */
                [!ENDNOCODE!][!//
                /*
                [!"num:inttohex(num:i(node:value(concat($FrIfNodePath,'/FrIfGMacroPerCycle'))))"!]U - FrIfGMacroPerCycle
                [!"num:inttohex(num:i(node:value(concat($FrIfNodePath,'/FrIfGSyncFrameIDCountMax'))))"!]U - FrIfGSyncFrameIDCountMax maps to FrIfGSyncNodeMax FR Pr 2.1
                */
                [!"num:inttohex($vGTUC02,8)"!]U,
                /* GTUC03 register settings */
                [!NOCODE!][!//
                  [!VAR "vGTUC03" = "num:i(0)"!][!//
                  [!VAR "TempGTUC03Val" = "num:i(node:value(concat($ControllerPath, '/FrPMicroInitialOffsetA')))"!][!//
                  [!VAR "vGTUC03" = "bit:or($vGTUC03,bit:shl($TempGTUC03Val,0))"!][!//
                  [!VAR "TempGTUC03Val" = "num:i(node:value(concat($ControllerPath, '/FrPMicroInitialOffsetB')))"!][!//
                  [!VAR "vGTUC03" = "bit:or($vGTUC03,bit:shl($TempGTUC03Val,8))"!][!//
                  [!VAR "TempGTUC03Val" = "num:i(node:value(concat($ControllerPath, '/FrPMacroInitialOffsetA')))"!][!//
                  [!VAR "vGTUC03" = "bit:or($vGTUC03,bit:shl($TempGTUC03Val,16))"!][!//
                  [!VAR "TempGTUC03Val" = "num:i(node:value(concat($ControllerPath, '/FrPMacroInitialOffsetB')))"!][!//
                  [!VAR "vGTUC03" = "bit:or($vGTUC03,bit:shl($TempGTUC03Val,24))"!][!//
                [!ENDNOCODE!][!//
                /*
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPMicroInitialOffsetA')))"!]U - FrPMicroInitialOffsetA [A]
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPMicroInitialOffsetB')))"!]U - FrPMicroInitialOffsetB [B]
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPMacroInitialOffsetA')))"!]U - FrPMacroInitialOffsetA [A]
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPMacroInitialOffsetB')))"!]U - FrPMacroInitialOffsetB [B]
                */
                [!"num:inttohex($vGTUC03,8)"!]U,
                /* GTUC04 register settings */
                [!NOCODE!][!//
                  [!VAR "vGTUC04" = "num:i(0)"!][!//
                  [!VAR "TempGTUC04Val" = "(num:i(node:value(concat($FrIfNodePath,'/FrIfGMacroPerCycle'))) - num:i(node:value(concat($FrIfNodePath,'/FrIfGdNit'))) - 1)"!][!//
                  [!VAR "vGTUC04" = "bit:or($vGTUC04,bit:shl($TempGTUC04Val,0))"!][!//
                  [!VAR "TempGTUC04Val" = "(num:i(node:value(concat($ControllerPath, '/FrPOffsetCorrectionStart'))) - 1)"!][!//
                  [!VAR "vGTUC04" = "bit:or($vGTUC04,bit:shl($TempGTUC04Val,16))"!][!//
                [!ENDNOCODE!][!//
                /*
                [!"num:inttohex(num:i(node:value(concat($FrIfNodePath,'/FrIfGMacroPerCycle'))) - num:i(node:value(concat($FrIfNodePath,'/FrIfGdNit'))) - 1)"!]U[!//
               - NetworkIdleTimeStart = (FrIfGMacroPerCycle - FrIfGdNit - 1)
                [!"num:inttohex(num:i(node:value(concat($ControllerPath, '/FrPOffsetCorrectionStart'))) - 1)"!]U[!//
               - Range: 8 -15998, maps to (FrPOffsetCorrectionStart - 1)
                */
                [!"num:inttohex($vGTUC04,8)"!]U,
                /* GTUC05 register settings */
                [!NOCODE!][!//
                  [!VAR "vGTUC05" = "num:i(0)"!][!//
                  [!VAR "TempGTUC05Val" = "num:i(node:value(concat($ControllerPath, '/FrPDelayCompensationA')))"!][!//
                  [!VAR "vGTUC05" = "bit:or($vGTUC05,bit:shl($TempGTUC05Val,0))"!][!//
                  [!VAR "TempGTUC05Val" = "num:i(node:value(concat($ControllerPath, '/FrPDelayCompensationB')))"!][!//
                  [!VAR "vGTUC05" = "bit:or($vGTUC05,bit:shl($TempGTUC05Val,8))"!][!//
                  [!VAR "TempGTUC05Val" = "num:i(node:value(concat($ControllerPath, '/FrPClusterDriftDamping')))"!][!//
                  [!VAR "vGTUC05" = "bit:or($vGTUC05,bit:shl($TempGTUC05Val,16))"!][!//
                  [!VAR "TempGTUC05Val" = "num:i(node:value(concat($ControllerPath, '/FrPDecodingCorrection')))"!][!//
                  [!VAR "vGTUC05" = "bit:or($vGTUC05,bit:shl($TempGTUC05Val,24))"!][!//
                [!ENDNOCODE!][!//
                /*
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPDelayCompensationA')))"!]U - FrPDelayCompensationA
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPDelayCompensationB')))"!]U - FrPDelayCompensationB
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPClusterDriftDamping')))"!]U - FrPClusterDriftDamping
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPDecodingCorrection')))"!]U - FrPDecodingCorrection
                */
                [!"num:inttohex($vGTUC05,8)"!]U,
                /* GTUC06 register settings */
                [!NOCODE!][!//
                  [!VAR "vGTUC06" = "num:i(0)"!][!//
                  [!VAR "TempGTUC06Val" = "num:i(node:value(concat($ControllerPath, '/FrPdAcceptedStartupRange')))"!][!//
                  [!VAR "vGTUC06" = "bit:or($vGTUC06,bit:shl($TempGTUC06Val,0))"!][!//
                  [!VAR "TempGTUC06Val" = "num:i(node:value(concat($ControllerPath, '/FrPRateCorrectionOut')))"!][!//
                  [!VAR "vGTUC06" = "bit:or($vGTUC06,bit:shl($TempGTUC06Val,16))"!][!//
                [!ENDNOCODE!][!//
                /*
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPdAcceptedStartupRange')))"!]U - FrPdAcceptedStartupRange
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPRateCorrectionOut')))"!]U - is same as FrPdMaxDrift
                */
                [!"num:inttohex($vGTUC06,8)"!]U,
                /* GTUC07 register settings */
                [!NOCODE!][!//
                  [!VAR "vGTUC07" = "num:i(0)"!][!//
                  [!VAR "TempGTUC07Val" = "num:i(node:value(concat($FrIfNodePath,'/FrIfGdStaticSlot')))"!][!//
                  [!VAR "vGTUC07" = "bit:or($vGTUC07,bit:shl($TempGTUC07Val,0))"!][!//
                  [!VAR "TempGTUC07Val" = "num:i(node:value(concat($FrIfNodePath,'/FrIfGNumberOfStaticSlots')))"!][!//
                  [!VAR "vGTUC07" = "bit:or($vGTUC07,bit:shl($TempGTUC07Val,16))"!][!//
                [!ENDNOCODE!][!//
                /*
                [!"num:inttohex(num:i(node:value(concat($FrIfNodePath,'/FrIfGdStaticSlot'))))"!]U - FrIfGdStaticSlot
                [!"num:inttohex(num:i(node:value(concat($FrIfNodePath,'/FrIfGNumberOfStaticSlots'))))"!] - FrIfGNumberOfStaticSlots
                */
                [!"num:inttohex($vGTUC07,8)"!]U,
                /* GTUC08 register settings */
                [!NOCODE!][!//
                  [!VAR "vGTUC08" = "num:i(0)"!][!//
                  [!VAR "TempGTUC08Val" = "num:i(node:value(concat($FrIfNodePath,'/FrIfGdMinislot')))"!][!//
                  [!VAR "vGTUC08" = "bit:or($vGTUC08,bit:shl($TempGTUC08Val,0))"!][!//
                  [!VAR "TempGTUC08Val" = "num:i(node:value(concat($FrIfNodePath,'/FrIfGNumberOfMinislots')))"!][!//
                  [!VAR "vGTUC08" = "bit:or($vGTUC08,bit:shl($TempGTUC08Val,16))"!][!//
                [!ENDNOCODE!][!//
                /*
                [!"num:inttohex(num:i(node:value(concat($FrIfNodePath,'/FrIfGdMinislot'))))"!]U - FrIfGdMinislot
                [!"num:inttohex(num:i(node:value(concat($FrIfNodePath,'/FrIfGNumberOfMinislots'))))"!]U - FrIfGNumberOfMinislots
                */
                [!"num:inttohex($vGTUC08,8)"!]U,
                /* GTUC09 register settings */
                [!NOCODE!][!//
                  [!VAR "vGTUC09" = "num:i(0)"!][!//
                  [!VAR "TempGTUC09Val" = "num:i(node:value(concat($FrIfNodePath,'/FrIfGdActionPointOffset')))"!][!//
                  [!VAR "vGTUC09" = "bit:or($vGTUC09,bit:shl($TempGTUC09Val,0))"!][!//
                  [!VAR "TempGTUC09Val" = "num:i(node:value(concat($FrIfNodePath,'/FrIfGdMiniSlotActionPointOffset')))"!][!//
                  [!VAR "vGTUC09" = "bit:or($vGTUC09,bit:shl($TempGTUC09Val,8))"!][!//
                  [!VAR "TempGTUC09Val" = "num:i(node:value(concat($FrIfNodePath,'/FrIfGdDynamicSlotIdlePhase')))"!][!//
                  [!VAR "vGTUC09" = "bit:or($vGTUC09,bit:shl($TempGTUC09Val,16))"!][!//
                [!ENDNOCODE!][!//
                /*
                [!"num:inttohex(num:i(node:value(concat($FrIfNodePath,'/FrIfGdActionPointOffset'))))"!]U - FrIfgdActionPointOffset
                [!"num:inttohex(num:i(node:value(concat($FrIfNodePath,'/FrIfGdMiniSlotActionPointOffset'))))"!]U - FrIfgdMinislotActionPointOffset
                [!"num:inttohex(num:i(node:value(concat($FrIfNodePath,'/FrIfGdDynamicSlotIdlePhase'))))"!]U - FrIfgdDynamicSlotIdlePhase
                */
                [!"num:inttohex($vGTUC09,8)"!]U,
                /* GTUC10 register settings */
                [!NOCODE!][!//
                  [!VAR "vGTUC10" = "num:i(0)"!][!//
                  [!VAR "TempGTUC10Val" = "num:i(node:value(concat($ControllerPath, '/FrPOffsetCorrectionOut')))"!][!//
                  [!VAR "vGTUC10" = "bit:or($vGTUC10,bit:shl($TempGTUC10Val,0))"!][!//
                  [!VAR "TempGTUC10Val" = "num:i(node:value(concat($ControllerPath, '/FrPRateCorrectionOut')))"!][!//
                  [!VAR "vGTUC10" = "bit:or($vGTUC10,bit:shl($TempGTUC10Val,16))"!][!//
                [!ENDNOCODE!][!//
                /*
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPOffsetCorrectionOut')))"!]U - FrPOffsetCorrectionOut
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPRateCorrectionOut')))"!]U - FrPRateCorrectionOut
                */
                [!"num:inttohex($vGTUC10,8)"!]U,
                /* GTUC11 register settings */
                [!NOCODE!][!//
                  [!VAR "vGTUC11" = "num:i(0)"!][!//
                [!ENDNOCODE!][!//
                /*
                0x0000U - Unused (FrPExternOffsetControl, FrPExternRateControl
                0U - FrPExternOffsetCorrection is not present in AS40
                0U - FrPExternRateCorrection is not present in AS40
                */
                [!"num:inttohex($vGTUC11,8)"!]U,
                /* CUST1 register settings */
                [!NOCODE!][!//
                  [!VAR "vCUST1" = "num:i(0)"!][!//
                  [!VAR "RxlineA" = "node:value(concat($ControllerPath, '/FrRxInputSelectionA'))"!][!//
                  [!VAR "RxlineB" = "node:value(concat($ControllerPath, '/FrRxInputSelectionB'))"!][!//
                  [!IF "substring-before($RxlineA,'_PORT') = 'FR_RXSEL0'"!][!//
                    [!VAR "vCUST1" = "bit:or($vCUST1,bit:shl(0,10))"!][!//
                  [!ELSEIF "substring-before($RxlineA,'_PORT') = 'FR_RXSEL1'"!][!//
                    [!VAR "vCUST1" = "bit:or($vCUST1,bit:shl(1,10))"!][!//
                  [!ELSEIF "substring-before($RxlineA,'_PORT') = 'FR_RXSEL2'"!][!//
                    [!VAR "vCUST1" = "bit:or($vCUST1,bit:shl(2,10))"!][!//
                  [!ELSEIF "substring-before($RxlineA,'_PORT') = 'FR_RXSEL3'"!][!//
                    [!VAR "vCUST1" = "bit:or($vCUST1,bit:shl(3,10))"!][!//
                  [!ENDIF!][!//
                  [!IF "substring-before($RxlineB,'_PORT') = 'FR_RXSEL0'"!][!//
                    [!VAR "vCUST1" = "bit:or($vCUST1,bit:shl(0,12))"!][!//
                  [!ELSEIF "substring-before($RxlineB,'_PORT') = 'FR_RXSEL1'"!][!//
                    [!VAR "vCUST1" = "bit:or($vCUST1,bit:shl(1,12))"!][!//
                  [!ELSEIF "substring-before($RxlineB,'_PORT') = 'FR_RXSEL2'"!][!//
                    [!VAR "vCUST1" = "bit:or($vCUST1,bit:shl(2,12))"!][!//
                  [!ELSEIF "substring-before($RxlineB,'_PORT') = 'FR_RXSEL3'"!][!//
                    [!VAR "vCUST1" = "bit:or($vCUST1,bit:shl(3,12))"!][!//
                  [!ENDIF!][!//
                [!ENDNOCODE!][!//
                /*
                0x00U - Unused
                0x00U - Reserved
                [!"node:value(concat($ControllerPath, '/FrRxInputSelectionA'))"!] - FrRxInputSelection Channel A
                [!"node:value(concat($ControllerPath, '/FrRxInputSelectionB'))"!] - FrRxInputSelection Channel B
                0x00U - Unused
                */
                [!"num:inttohex($vCUST1,8)"!]U
              [!ENDINDENT!][!//
              };

              [!IF "(node:exists(concat($ControllerPath, '/FrFifo/*[1]')))"!][!/* FIFO_NODE_CHECK */!][!//
                #if (FR_17_ERAY_FIFO_CONFIGURED == STD_ON)
                /***** FR Receive receive FIFO configuration Controller [!"$ControllerIndex"!]  *****/
                /* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
                due to Autosar Naming constraints.*/
                /* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
                due to Autosar Naming constraints.*/
                /* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
                due to Autosar Naming constraints.*/
                /* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
                due to Autosar Naming constraints.*/
                [!/*
                [cover parentID={E2BAB0DE-61FB-42c1-9DE9-CA7922951E27}] Fr_17_Eray_<ConfigShortName>_RxFifoConfig_<CtrlIdx> [/cover]
                */!][!//
                static const Fr_17_Eray_RxFifoConfigType Fr_17_Eray_[!"$ConfigShortNamePath"!]_RxFifoConfig_[!"$ControllerIndex"!] =
                {
                [!NOCODE!][!//
                  [!VAR "vFrChannels" = "node:value(concat($ControllerPath, '/FrFifo/*[1]/FrChannels'))"!][!//
                  [!VAR "vFrChannels2" = "substring-after($vFrChannels, 'FR_CHANNEL_')"!][!//
                  [!VAR "Channels" = "node:ref(concat($ControllerPath, '/FrPChannels'))"!][!//
                  [!VAR "Channels2" = "substring-after($Channels, 'FR_CHANNEL_')"!][!//
                  [!/* ---------  Config Rule FR_CR_218 ---------*/!][!//
                  [!IF "not(contains($Channels2, $vFrChannels2))"!][!//
                    [!ERROR!][!//
                      Error: FIFO channel can not be [!"$vFrChannels"!] when CC channel configuration FrPChannels is [!"$Channels"!]
                    [!ENDERROR!][!//
                  [!ENDIF!][!//
                  [!IF "$vFrChannels = 'FR_CHANNEL_AB'"!][!//
                    [!VAR "vFrChannelVal" = "num:i(0)"!][!//
                  [!ELSEIF "$vFrChannels = 'FR_CHANNEL_B'"!][!//
                    [!VAR "vFrChannelVal" = "num:i(1)"!][!//
                  [!ELSE!][!//
                    [!VAR "vFrChannelVal" = "num:i(2)"!][!//
                  [!ENDIF!][!//
                  [!VAR "vFrCycleRepetition" = "node:value(concat($ControllerPath, '/FrFifo/*[1]/FrCycleRepetition'))"!][!//
                  [!VAR "vFrBaseCycle" = "node:value(concat($ControllerPath, '/FrFifo/*[1]/FrBaseCycle'))"!][!//
                  [!IF "$vFrBaseCycle >= $vFrCycleRepetition"!][!//
                    [!ERROR!][!//
                      Error: FrIfBaseCycle ([!"$vFrBaseCycle"!]) is not less than FrIfCycleRepetition ([!"$vFrCycleRepetition"!]) in FIFO configuration
                    [!ENDERROR!][!//
                  [!ENDIF!][!//
                  [!VAR "CycleCode" = "bit:or($vFrCycleRepetition,$vFrBaseCycle)"!][!//
                  [!VAR "CycleCode" = "bit:shl($CycleCode,16)"!][!//
                  [!/*
                  [cover parentID={092409E7-4EC4-4722-9B23-D704B0A751EB}] Receive FIFO Functionality [/cover]
                  */!][!//
                  [!VAR "FrameIdRejectionFilterMask" = "node:value(concat($ControllerPath, '/FrFifo/*[1]/FrFrameIdRejectionFilterMask'))"!][!//
                  [!VAR "FrameIdRejectionFilter" = "node:value(concat($ControllerPath, '/FrFifo/*[1]/FrFrameIdRejectionFilter'))"!][!//
                  [!VAR "FrameIdRejectionFilter" = "bit:shl($FrameIdRejectionFilter,2)"!][!//
                  [!VAR "RejectStaticSegment" = "num:i(0)"!][!//
                  [!VAR "RejectNullFrames" = "num:i(0)"!][!//
                  [!IF "node:value(concat($ControllerPath, '/FrFifo/*[1]/FrRejectStaticSegment')) = 'true'"!][!//
                    [!VAR "RejectStaticSegment" = "num:i(1)"!][!//
                  [!ENDIF!][!//
                  [!IF "node:value(concat($ControllerPath, '/FrFifo/*[1]/FrRejectNullFrames')) = 'true'"!][!//
                    [!VAR "RejectNullFrames" = "num:i(1)"!][!//
                  [!ENDIF!][!//
                  [!VAR "RejectStaticSegment" = "bit:shl($RejectStaticSegment,23)"!][!//
                  [!VAR "RejectNullFrames" = "bit:shl($RejectNullFrames,24)"!][!//
                  [!VAR "FrfCfg" = "bit:or($vFrChannelVal,$FrameIdRejectionFilter)"!][!//
                  [!VAR "FrfCfg" = "bit:or($FrfCfg,$CycleCode)"!][!//
                  [!VAR "FrfCfg" = "bit:or($FrfCfg,$RejectStaticSegment)"!][!//
                  [!VAR "FrfCfg" = "bit:or($FrfCfg,$RejectNullFrames)"!][!//
                [!ENDNOCODE!][!//
                [!INDENT "2"!][!//
                  /* Fifo Rejection Filter criteria
                  FrChannels|(FrFid<<2)|((FrCycleRepetition|FrBaseCycle)<<16U)|(RSS<23)|(RNF<24)
                  */
                  [!"$FrfCfg"!]U,[!//

                  /* FIFO Rejection Filter Mask */
                  [!"num:i($FrameIdRejectionFilterMask)"!]U,[!//

                  /* Fifo Depth. It is the number of FIFO Lpdus/FrFifoDepth which is lower */
                  [!IF "num:i($ControllerIndex) = num:i(0)"!][!//
                    [!IF "$FifoCountCtrl0 = num:i(0)"!][!//
                      [!WARNING!][!//
                        FR Code Generator: FrFifo container of Controller0 configured
                        and the number of receive Lpdus configured for FIFO is 0, Check the FIFO filter
                        setting.
                      [!ENDWARNING!][!//
                    [!ENDIF!][!//
                    [!IF "$FifoDepthCtrl0 < $FifoCountCtrl0"!][!//
                      [!WARNING!][!//
                        FR Code Generator: The number of FIFO Lpdus is greater than FrFifoDepth,
                        so FIFO overrun may occur if not read on time for Controller0.
                      [!ENDWARNING!][!//
                      [!"num:i($FifoDepthCtrl0)"!]U[!//
                    [!ELSE!][!//
                      [!"num:i($FifoCountCtrl0)"!]U[!//
                    [!ENDIF!][!//
                  [!ENDIF!][!//
                  [!IF "num:i($ControllerIndex) = num:i(1)"!][!//
                    [!IF "$FifoCountCtrl1 = num:i(0)"!][!//
                      [!WARNING!][!//
                        FR Code Generator: FrFifo container of Controller1 configured
                        and the number of receive Lpdus configured for FIFO is 0, Check the FIFO filter
                        setting.
                      [!ENDWARNING!][!//
                    [!ENDIF!][!//
                    [!IF "$FifoDepthCtrl1 < $FifoCountCtrl1"!][!//
                      [!WARNING!][!//
                        FR Code Generator: The number of FIFO Lpdus is greater than FrFifoDepth,
                        so FIFO overrun may occur if not read on time for Controller1.
                      [!ENDWARNING!][!//
                      [!"num:i($FifoDepthCtrl1)"!]U[!//
                    [!ELSE!][!//
                      [!"num:i($FifoCountCtrl1)"!]U[!//
                    [!ENDIF!][!//
                  [!ENDIF!][!//
                [!ENDINDENT!]
                };
                #endif
              [!ENDIF!][!/* FIFO_NODE_CHECK */!][!//
              [!//

              /* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
              due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
              due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
              due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
              due to Autosar Naming constraints.*/
              [!/*
              [cover parentID={227AEBDD-A1AA-406f-A34F-14E801B3110F}] Fr_17_Eray_<ConfigShortName>_CCConfigArray_<CtrlIdx> [/cover]
              */!][!//
              static const uint32 Fr_17_Eray_[!"$ConfigShortNamePath"!]_CCConfigArray_[!"$ControllerIndex"!][63] =
              {
              [!INDENT "2"!][!//
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGdCycle'))* 1000000000,8)"!]U,  /* FrIfGdCycle */
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPMicroPerCycle')),8)"!]U, /* UT: FrPMicroPerCycle */
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPdListenTimeout')),8)"!]U, /* FrPdListenTimeout */
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGMacroPerCycle')),8)"!]U, /* FrIfGMacroPerCycle */
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGdMacrotick'))* 1000000000,8)"!]U,  /* FrIfGdMacrotick */
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGNumberOfMinislots')),8)"!]U, /* FrIfGNumberOfMinislots */
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGNumberOfStaticSlots')),8)"!]U, /* FrIfGNumberOfStaticSlots */
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGdNit')),8)"!]U,  /* FrIfGdNit */
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGdStaticSlot')),8)"!]U, /* FrIfGdStaticSlot */
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGdWakeupRxWindow')),8)"!]U, /* FrIfgdWakeupRxWindow */
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPKeySlotId')),8)"!]U, /* FrPKeySlotId */
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPLatestTx')),8)"!]U, /* FrPLatestTx */
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPOffsetCorrectionOut')),8)"!]U, /* FrPOffsetCorrectionOut */
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPOffsetCorrectionStart')),8)"!]U, /* FrPOffsetCorrectionStart */
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPRateCorrectionOut')),8)"!]U, /* FrPRateCorrectionOut */
                [!"num:inttohex(num:i(0),8)"!]U,  /* Second Keyslot ID */
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPdAcceptedStartupRange')),8)"!]U, /* FrPdAcceptedStartupRange */
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGColdStartAttempts')),8)"!]U, /* FrIfGColdStartAttempts */
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGCycleCountMax')),8)"!]U,  /* FrIfGCycleCountMax */
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGListenNoise')),8)"!]U, /*FrIfGListenNoise */
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGMaxWithoutClockCorrectFatal')),8)"!]U, /* FrIfGMaxWithoutClockCorrectFatal */
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGMaxWithoutClockCorrectPassive')),8)"!]U, /* FrIfGMaxWithoutClockCorrectPassive */
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGNetworkManagementVectorLength')),8)"!]U, /* FrIfGNetworkManagementVectorLength */
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGPayloadLengthStatic')),8)"!]U, /* FrIfGPayloadLengthStatic */
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGSyncFrameIDCountMax')),8)"!]U, /* FrIfGSyncFrameIDCountMax maps to FrIfGSyncNodeMax FR Pr 2.1 */
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGdActionPointOffset')),8)"!]U, /* FrIfgdActionPointOffset */
                [!"num:inttohex(num:i(0),8)"!]U, /* FrIfGdBit */
                [!"num:inttohex($FrCASRxLowMax,8)"!]U, /* FrIfGdCasRxLowMax */
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGdDynamicSlotIdlePhase')),8)"!]U, /* FrIfgdDynamicSlotIdlePhase */
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGdMiniSlotActionPointOffset')),8)"!]U, /* FrIfgdMinislotActionPointOffset */
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGdMinislot')),8)"!]U, /* FrIfGdMinislot */
                [!"num:inttohex(num:i(0),8)"!]U, /*  0 - T12_5NS -> 10 Mbps */
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGdSymbolWindow')),8)"!]U,  /* FrIfGdSymbolWindow */
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGdActionPointOffset')),8)"!]U, /* FrIfgdActionPointOffset */
                [!"num:inttohex($FrTSSTransmitter,8)"!]U, /* FrIfGdTSSTransmitter */
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGdWakeupRxIdle')),8)"!]U, /* FrIfgdWakeupRxIdle */
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGdWakeupRxLow')),8)"!]U, /* FrIfgdWakeupRxLow */
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGdWakeupTxActive')),8)"!]U, /* FrIfGdWakeupTxActive */
                [!"num:inttohex(node:value(concat($FrIfNodePath,'/FrIfGdWakeupTxIdle')),8)"!]U, /* FrIfGdWakeupTxIdle */
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPAllowPassiveToActive')),8)"!]U, /* FrPAllowPassiveToActive */
                [!IF "node:value(concat($ControllerPath, '/FrPChannels')) = 'FR_CHANNEL_AB'"!][!//
                  [!"num:inttohex(num:i(2),8)"!]U,[!//
                [!ELSEIF "node:value(concat($ControllerPath, '/FrPChannels')) = 'FR_CHANNEL_B'"!][!//
                  [!"num:inttohex(num:i(1),8)"!]U,[!//
                [!ELSE!][!//
                  [!"num:inttohex(num:i(0),8)"!]U,[!//
                [!ENDIF!][!//
                /* FrPChannels */
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPClusterDriftDamping')),8)"!]U, /* FrPClusterDriftDamping */
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPDecodingCorrection')),8)"!]U, /* FrPDecodingCorrection */
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPDelayCompensationA')),8)"!]U, /* FrPDelayCompensationA */
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPDelayCompensationB')),8)"!]U, /* FrPDelayCompensationB */
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPMacroInitialOffsetA')),8)"!]U, /* FrPMacroInitialOffsetA */
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPMacroInitialOffsetB')),8)"!]U, /* FrPMacroInitialOffsetB */
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPMicroInitialOffsetA')),8)"!]U, /* FrPMicroInitialOffsetA */
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPMicroInitialOffsetB')),8)"!]U, /* FrPMicroInitialOffsetB */
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPPayloadLengthDynMax')),8)"!]U, /* FrPPayloadLengthDynMax */
                [!"num:inttohex(num:i(1),8)"!]U, /* 1 - N2SAMPLES - Fixed at N2 samples as the baudrate supported is 10Mbit/s */
                [!IF "node:value(concat($ControllerPath, '/FrPWakeupChannel')) = 'FR_CHANNEL_A'"!][!//
                  [!"num:inttohex(num:i(0),8)"!]U, /* FrPWakeupChannel ->  0 - FR_CHANNEL_A */
                [!ELSE!][!//
                  [!"num:inttohex(num:i(1),8)"!]U, /* FrPWakeupChannel -> 1 - FR_CHANNEL_B */
                [!ENDIF!][!//
                [!"num:inttohex(node:value(concat($ControllerPath, '/FrPWakeupPattern')),8)"!]U, /* FrPWakeupPattern */
                [!"num:inttohex(num:i(1),8)"!]U, /* FrPdMicrotick -> 1 - T25NS */
                [!"num:inttohex(num:i(0),8)"!]U, /* FrIfGdIgnoreAfterTx - Set to 0 for FR Pr 2.1 */
                [!IF "(node:value(concat($ControllerPath, '/FrPAllowHaltDueToClock')) = 'true')"!][!//
                  [!"num:inttohex(num:i(1),8)"!]U, /* FrPAllowHaltDueToClock */
                [!ELSE!][!//
                  [!"num:inttohex(num:i(0),8)"!]U, /* FrPAllowHaltDueToClock */
                [!ENDIF!][!//
                  [!"num:inttohex(num:i(0),8)"!]U, /* FrPExternalSync - Set to 0 for FR Pr 2.1 */
                  [!"num:inttohex(num:i(0),8)"!]U, /* FrPFallBackInternal - Set to 0 for FR Pr 2.1 */
                [!IF "(node:value(concat($ControllerPath, '/FrPKeySlotOnlyEnabled')) = 'true')"!][!//
                  [!"num:inttohex(num:i(1),8)"!]U, /* FrPKeySlotOnlyEnabled */
                [!ELSE!][!//
                  [!"num:inttohex(num:i(0),8)"!]U, /* FrPKeySlotOnlyEnabled */
                [!ENDIF!][!//
                [!IF "(node:value(concat($ControllerPath, '/FrPKeySlotUsedForStartup')) = 'true')"!][!//
                  [!"num:inttohex(num:i(1),8)"!]U, /* FrPKeySlotUsedForStartup */
                [!ELSE!][!//
                  [!"num:inttohex(num:i(0),8)"!]U, /* FrPKeySlotUsedForStartup */
                [!ENDIF!][!//
                [!IF "(node:value(concat($ControllerPath, '/FrPKeySlotUsedForSync')) = 'true')"!][!//
                  [!"num:inttohex(num:i(1),8)"!]U, /* FrPKeySlotUsedForSync */
                [!ELSE!][!//
                  [!"num:inttohex(num:i(0),8)"!]U, /* FrPKeySlotUsedForSync */
                [!ENDIF!][!//
                [!"num:inttohex(num:i(0),8)"!]U, /* FrPNmVectorEarlyUpdate - Set to 0 for FR Pr 2.1 */
                [!"num:inttohex(num:i(0),8)"!]U  /* FrPTwoKeySlotMode - Set to 0 for FR Pr 2.1 */
              [!ENDINDENT!][!//
              };

              [!VAR "CtrlRefFound" = "num:i(1)"!][!//
              [!BREAK!][!//
            [!ENDIF!][!/* LPDU_CONFIG_IF1 */!][!//
          [!ENDLOOP!][!/* LPDU_CONFIG_LOOP3 */!][!//
          [!IF "$CtrlRefFound = 1"!]
            [!BREAK!]
          [!ENDIF!]
        [!ENDLOOP!][!/* LPDU_CONFIG_LOOP2 */!][!//
        [!IF "$CtrlRefFound = 1"!]
          [!BREAK!]
        [!ENDIF!]
      [!ENDSELECT!][!//
    [!ENDFOR!][!//

    [!VAR "ControllerPath" = "node:path(.)"!][!//
    [!VAR "FrClockDivider" = "num:i(0)"!][!//
    [!VAR "LPDU_COUNT_TOTAL" = "num:i(0)"!][!//
    /* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
    due to Autosar Naming constraints.*/
    /* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
    due to Autosar Naming constraints.*/
    /* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
    due to Autosar Naming constraints.*/
    /* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
    due to Autosar Naming constraints.*/
    [!/*
    [cover parentID={1FCFD574-11B3-4507-AD41-D7A1E3CEB3E7}] Fr_17_Eray_<ConfigShortName>_CC [/cover]
    */!][!//
    static const Fr_17_Eray_CCType Fr_17_Eray_[!"$ConfigShortNamePath"!]_CC[] =
    {
    [!INDENT "2"!][!//
      [!VAR "Counter" = "num:i(count(./FrController/*))"!][!//
      [!FOR "Index" = "0" TO "(num:i($Counter)- 1)"!][!//
        [!SELECT "./FrController/*[@index = $Index]"!][!//
          [!VAR "ControllerPathTemp" = "node:path(.)"!][!//
          [!/* Example: ControllerPathTemp = /AUTOSAR/TOP-LEVEL-PACKAGES/Fr/ELEMENTS/Fr/FrMultipleConfiguration/FrController/FrController_0 */!][!//
          [!VAR "ControllerShortNamePath" = "substring-after($ControllerPathTemp, 'FrController')"!][!//
          [!/* Example: ControllerShortNamePath = /FrController_0 */!][!//
          [!VAR "ControllerIndex" = "./FrCtrlIdx"!][!//
          [!VAR "CtrlRefFound" = "num:i(0)"!][!//
          [!LOOP "as:modconf('FrIf')[1]/FrIfConfig/FrIfCluster/*"!][!/*LOOP1*/!][!/* CONFIG_ROOT_LOOP2 */!][!//
            [!VAR "NumberOfStaticSlots" = "FrIfGNumberOfStaticSlots"!][!//
            [!LOOP "FrIfController/*"!][!/* CONFIG_ROOT_LOOP3 */!][!//
              [!VAR "FrIfControllerPath" = "node:ref(node:path(./FrIfFrCtrlRef))"!][!//
              [!VAR "FrConfigPath" = "substring-after($FrIfControllerPath, '/Fr/Fr/')"!][!//
              [!VAR "FrConfigPath" = "substring-before($FrConfigPath, $ControllerShortNamePath)"!][!//
              [!VAR "FrIfControllerPath" = "substring-after($FrIfControllerPath, $FrConfigPath)"!][!//
              [!IF "$FrIfControllerPath = $ControllerShortNamePath"!][!/* CONFIG_ROOT_IF1 */!][!//
                [!VAR "LPDU_COUNT_TOTAL" = "num:i(count(FrIfLPdu/*))"!][!//
                [!VAR "FrClockDivider" = "node:value(concat($ControllerPath, '/FrClockConfiguration/FrClockDivider'))"!][!//
                [!VAR "CtrlRefFound" = "num:i(1)"!][!//
              [!ENDIF!][!/* CONFIG_ROOT_IF1 */!][!//
              [!IF "$CtrlRefFound = 1"!][!//
                [!BREAK!][!//
              [!ENDIF!][!//
            [!ENDLOOP!][!/* CONFIG_ROOT_LOOP3 */!][!//
            [!IF "$CtrlRefFound = 1"!][!//
              [!BREAK!][!//
            [!ENDIF!][!//
          [!ENDLOOP!][!/* CONFIG_ROOT_LOOP2  */!][!//
          [!/* ---------  Config Rule FR_CR_214 --------- */!][!//
          [!IF "$CtrlRefFound != num:i(1)"!][!//
            [!ERROR!][!//
              Error: FlexRay Communication Controller [!"$ControllerShortNamePath"!] is not referrred by FrIf in any cluster.
            [!ENDERROR!][!//
          [!ENDIF!][!//
          [!/* ------------------------------------------*/!][!//
          {
          [!INDENT "4"!][!//
            /* Pointer to configuration of Communication Controller */
            &Fr_17_Eray_[!"$ConfigShortNamePath"!]_kCCCfg_[!"$ControllerIndex"!],

            /* Pointer to array of LPDU configurations */
            Fr_17_Eray_[!"$ConfigShortNamePath"!]_kLPduConfig_[!"$ControllerIndex"!],

            #if (FR_17_ERAY_FIFO_CONFIGURED == STD_ON)
            [!IF "(node:exists(concat($ControllerPathTemp, '/FrFifo/*[1]')))"!][!/* FIFO_NODE_CHECK */!][!//
                &Fr_17_Eray_[!"$ConfigShortNamePath"!]_RxFifoConfig_[!"$ControllerIndex"!],
            [!ELSE!][!//
                NULL_PTR,
            [!ENDIF!][!//
            #endif

            /* Pointer to array of FR parameters accessed by Fr_ReadCCConfig */
            Fr_17_Eray_[!"$ConfigShortNamePath"!]_CCConfigArray_[!"$ControllerIndex"!],

            /* Pointer to LPDU to message buffer mapping array */
            Fr_17_Eray_[!"$ConfigShortNamePath"!]_LPduIdx2MsgBuff_[!"$ControllerIndex"!],

            /* Pointer to Data pointer offsets */
            Fr_17_Eray_[!"$ConfigShortNamePath"!]_DataPointerOffset_[!"$ControllerIndex"!],

            /* Number of LPDUs configured */
            [!"$LPDU_COUNT_TOTAL"!]U,

            /* ERAY Module clock configuration : Runtime Mode Control setting */
            [!"$FrClockDivider"!]U,

            /* Buffer Reconfiguration Status */
            [!IF "((num:i($ControllerIndex) = num:i(0)) and ($BuffReconfigReqCtrl0 = 'YES')) or ((num:i($ControllerIndex) = num:i(1)) and ($BuffReconfigReqCtrl1 = 'YES'))"!][!//
              1U,
            [!ELSE!][!//
              0U,
            [!ENDIF!]
              /*DEM Id for FlexRay controller hardware test failure.*/
            [!IF "(node:exists(./FrControllerDemEventParameterRefs/*[1]/FR_E_CTRL_TESTRESULT/*[1]) = 'true') and (node:value(./FrControllerDemEventParameterRefs/*[1]/FR_E_CTRL_TESTRESULT/*[1]) != ' ' )"!][!//
              DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./FrControllerDemEventParameterRefs/*[1]/FR_E_CTRL_TESTRESULT/*[1])))"!],
            [!ELSE!][!//
              FR_17_ERAY_DEM_REPORT_DISABLED,
            [!ENDIF!][!//

            /* Number of HW message buffers required */
            [!IF "$ControllerIndex = num:i(0)"!][!//
              [!IF "$BuffReconfigReqCtrl0 = 'YES'"!][!//
                [!"num:i($HardwareMsgBuffer0)"!]U[!//
              [!ELSE!][!//
                [!"$LPDU_COUNT_TOTAL"!]U
              [!ENDIF!][!//
            [!ENDIF!][!//
            [!IF "$ControllerIndex = num:i(1)"!][!//
              [!IF "$BuffReconfigReqCtrl1 = 'YES'"!][!//
                  [!"num:i($HardwareMsgBuffer1)"!]U[!//
              [!ELSE!][!//
                [!"$LPDU_COUNT_TOTAL"!]U
              [!ENDIF!][!//
            [!ENDIF!][!//
          [!ENDINDENT!][!//
          }[!//
          [!IF "$Index != ($Counter - 1)"!][!//
            ,
          [!ENDIF!][!//
        [!ENDSELECT!][!//
      [!ENDFOR!][!//
    [!ENDINDENT!][!//

    };

    /* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
    due to Autosar Naming constraints.*/
    /* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
    due to Autosar Naming constraints.*/
    /* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
    due to Autosar Naming constraints.*/
    /* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
    due to Autosar Naming constraints.*/
    [!/*
    [cover parentID={D237BE2D-DE0A-431a-9DFF-CE2C8C904C82}] Fr_17_Eray_<ConfigShortName>_CCMap [/cover]
    */!][!//
    static const uint8 Fr_17_Eray_[!"$ConfigShortNamePath"!]_CCMap[FR_17_ERAY_NUM_CONTROLLERS_IN_DEVICE] =
    {
    [!INDENT "2"!][!//
      [!FOR "ControllerNum" = "0" TO "(num:i(ecu:get('Eray.MaxControllers'))- 1)"!][!//
        [!VAR "Found" = "num:i(0)"!][!//
        [!VAR "Counter" = "num:i(count(./FrController/*))"!][!//
        [!FOR "Index" = "0" TO "(num:i($Counter)- 1)"!][!//
          [!SELECT "./FrController/*[@index = $Index]"!][!//
            [!IF "./FrCtrlIdx = $ControllerNum"!][!//
              [!VAR "Found" = "num:i(1)"!][!//
              [!"@index"!]U[!//
              [!IF "$ControllerNum != (num:i(ecu:get('Eray.MaxControllers')) - 1)"!][!//
                ,
              [!ENDIF!][!//
            [!ENDIF!][!//
          [!ENDSELECT!][!//
        [!ENDFOR!][!//
        [!IF "$Found = num:i(0)"!][!//
          255U[!//
          [!IF "$ControllerNum != (num:i(ecu:get('Eray.MaxControllers')) - 1)"!][!//
            ,
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDFOR!][!//
    [!ENDINDENT!]
    };

    [!ENDSELECT!][!//

    /* Implementation-specific post build configuration for FlexRay driver */
    [!/*
    [cover parentID={C64677EA-28BF-4fdf-976F-1DED9A292083}] Fr_17_Eray_Config [/cover]
    */!][!//
    [!IF "$VariantsConfigured = num:i(1)"!][!//
      const Fr_17_Eray_ConfigType Fr_17_Eray_Config_[!"$PredefinedVarName"!] =
    [!ELSE!][!//
      const Fr_17_Eray_ConfigType Fr_17_Eray_Config =
    [!ENDIF!][!//
    {
    [!INDENT "2"!][!//
      &Fr_17_Eray_[!"$ConfigShortNamePath"!]_CC[0],
      &Fr_17_Eray_[!"$ConfigShortNamePath"!]_CCMap[0]
    [!ENDINDENT!]
    };

  [!ENDSELECT!][!//
[!ENDINDENT!][!//
[!/*
[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
Memory mapping for configuration data [/cover]
*/!][!//
#define FR_17_ERAY_STOP_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so included multiple times from code. This violation is an
approved exception without side effects by AUTOSAR. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: MemMap.h is used to define memory
sections of the data or code, so included multiple times from code.
Variable declared before MemMap header file */
#include "Fr_17_Eray_MemMap.h"
