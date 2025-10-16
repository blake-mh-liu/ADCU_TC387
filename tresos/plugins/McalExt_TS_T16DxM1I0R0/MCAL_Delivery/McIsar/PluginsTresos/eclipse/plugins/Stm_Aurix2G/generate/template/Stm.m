[!/*
/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2019)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Stm.m                                                         **
**                                                                            **
**  VERSION   : 4.0.0                                                         **
**                                                                            **
**  DATE      : 2019-07-08                                                    **
**                                                                            **
**  BSW MODULE DESCRIPTION : Stm.bmd                                          **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Code template macro file for Stm Driver                    **
**                                                                            **
**  SPECIFICATION(S) : Specification of Stm Driver                            **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
*/!]

[!//
[!/* *** multiple inclusion protection*** */!][!//
[!IF "not(var:defined('STM_M'))"!][!//
[!VAR "STM_M"="'true'"!][!//

[!/*****************************************************************************
  Macro: STM_GenerateModuleMap

  Array values generated based on stm timer number allocation in cores

  Input Parameters:
  - Module: Module Name
*****************************************************************************/!]
[!MACRO "STM_GenerateModuleMap", "Module" = ""!][!//
  [!VAR "CGCoreUsed" = "''"!][!//
  [!VAR "CGModuleMap" = "''"!][!//
  [!SELECT "as:modconf('ResourceM')[1]"!][!//
    [!VAR "MasterCoreId" = "ResourceMMcalConfig/*[1]/ResourceMMasterCore"!][!//
    [!VAR "TotalResourceMcalCore" = "num:i(count(./ResourceMMcalConfig/*[1]/ResourceMMcalCore/*))"!][!//
    [!VAR "CGCoreMap" = "''"!][!//
    [!LOOP "ResourceMMcalConfig/*[1]/ResourceMMcalCore/*"!][!//
      [!VAR "CGCoreID" = "./ResourceMCoreID"!][!//
      [!LOOP "ResourceMAllocation/*"!][!//
        [!IF "$Module = ./ResourceMModuleName"!][!//
          [!VAR "index" = "num:i(count(text:split(./ResourceMResourceRef, '/')))"!][!//
          [!VAR "ResourceName" = "text:split(./ResourceMResourceRef, '/')[num:i($index)]"!][!//
          [!VAR "CGCoreMap" = "text:toupper(concat($CGCoreMap, $CGCoreID, '_', $ResourceName, ','))"!][!//
          [!VAR "CGModuleMap" = "concat($CGModuleMap, $CGCoreID, '_', $ResourceName, ',')"!][!//
          [!IF "not(contains(text:split($CGCoreUsed), $CGCoreID))"!][!//
            [!VAR "CGCoreUsed" = "concat($CGCoreUsed, $CGCoreID, ',')"!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDLOOP!][!//
    [!ENDLOOP!][!//
  [!ENDSELECT!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
** Name             : Stm_TimerValidation                                     **
**                                                                            **
** Description      : Macro to validate STM allocation in Resource Manager    **
**                                                                            **
*****************************************************************************/!]
[!MACRO "Stm_TimerValidation", "StmTimerUsed"="", "StmCmpRegUsed" = ""!][!//
  [!NOCODE!][!//
    [!VAR "Stm_Core0_TimerAlloc" = "'STM_TIMER_UNUSED'"!][!//
    [!VAR "Stm_Core0_CmpAlloc" = "'STM_CMP0_CMP1_UNUSED'"!][!//
    [!IF "(ecu:get('Mcu.NoOfCoreAvailable') > num:i(1))"!]
      [!VAR "Stm_Core1_TimerAlloc" = "'STM_TIMER_UNUSED'"!][!//
      [!VAR "Stm_Core1_CmpAlloc" = "'STM_CMP0_CMP1_UNUSED'"!][!//
      [!IF "(ecu:get('Mcu.NoOfCoreAvailable') > num:i(2))"!]
        [!VAR "Stm_Core2_TimerAlloc" = "'STM_TIMER_UNUSED'"!][!//
        [!VAR "Stm_Core2_CmpAlloc" = "'STM_CMP0_CMP1_UNUSED'"!][!//
        [!IF "(ecu:get('Mcu.NoOfCoreAvailable') > num:i(3))"!]
          [!VAR "Stm_Core3_TimerAlloc" = "'STM_TIMER_UNUSED'"!][!//
          [!VAR "Stm_Core3_CmpAlloc" = "'STM_CMP0_CMP1_UNUSED'"!][!//
          [!IF "(ecu:get('Mcu.NoOfCoreAvailable') > num:i(4))"!]
            [!VAR "Stm_Core4_TimerAlloc" = "'STM_TIMER_UNUSED'"!][!//
            [!VAR "Stm_Core4_CmpAlloc" = "'STM_CMP0_CMP1_UNUSED'"!][!//
            [!VAR "Stm_Core5_TimerAlloc" = "'STM_TIMER_UNUSED'"!][!//
            [!VAR "Stm_Core5_CmpAlloc" = "'STM_CMP0_CMP1_UNUSED'"!][!//
          [!ENDIF!]
        [!ENDIF!]
      [!ENDIF!]
    [!ENDIF!]    
    [!VAR "McuModPresence" = "num:i(0)"!][!//
    [!SELECT "as:modconf('Mcu')[1]"!][!//
      [!VAR "McuModPresence" = "num:i(1)"!][!//
    [!ENDSELECT!][!//
    [!IF "$McuModPresence = num:i(0)"!][!//
      [!ERROR!]
        MCU Module configuration is required for successful STM code generation, please add MCU module in the configuration.
      [!ENDERROR!]
    [!ENDIF!]
    [!SELECT "as:modconf('ResourceM')[1]"!][!//
      [!LOOP "ResourceMMcalConfig/*[1]/ResourceMMcalCore/*"!][!//
        [!VAR "CoreId" = "./ResourceMCoreID"!][!//
        [!VAR "Actual_CoreId" = "num:i(substring-after($CoreId,'E'))"!][!//  
        [!VAR "CGCoreID" = "./ResourceMCoreID"!][!//
        [!VAR "RMCoreArry" = "concat($RMCoreArry,$CGCoreID,'#')"!][!//
        [!VAR "StmConfigured" = "num:i(0)"!][!//
        [!IF "node:exists(./ResourceMAllocation/*[1])"!][!//
          [!LOOP "ResourceMAllocation/*"!][!//              
            [!VAR "StmCmp0Used" = "num:i(0)"!][!//
            [!VAR "StmCmp1Used" = "num:i(0)"!][!//
            [!IF "'STM' = ./ResourceMModuleName"!][!//
              [!VAR "StmConfigured" = "num:i(1)"!][!//
              [!VAR "StmTimerUsed" = "text:split(node:value(./ResourceMResourceRef),'_')[3]"!][!//
              [!VAR "StmTimerUsed" = "concat('STM_', $StmTimerUsed)"!][!//        
              [!IF "$Actual_CoreId = num:i(0)"!][!//              
                [!VAR "Stm_Core0_TimerAlloc" = "$StmTimerUsed"!][!//
              [!ELSEIF "$Actual_CoreId = num:i(1)"!][!//              
                [!VAR "Stm_Core1_TimerAlloc" = "$StmTimerUsed"!][!//
              [!ELSEIF "$Actual_CoreId = num:i(2)"!][!//              
                [!VAR "Stm_Core2_TimerAlloc" = "$StmTimerUsed"!][!//
              [!ELSEIF "$Actual_CoreId = num:i(3)"!][!//              
                [!VAR "Stm_Core3_TimerAlloc" = "$StmTimerUsed"!][!//
              [!ELSEIF "$Actual_CoreId = num:i(4)"!][!//              
                [!VAR "Stm_Core4_TimerAlloc" = "$StmTimerUsed"!][!//
              [!ELSEIF "$Actual_CoreId = num:i(5)"!][!//              
                [!VAR "Stm_Core5_TimerAlloc" = "$StmTimerUsed"!][!//
              [!ENDIF!]
              [!IF "(node:value(node:ref(./ResourceMResourceRef)/McuStmCmp0RegAllocationConf) = 'STM_CMP0_USED_BY_STM')"!][!//
                [!VAR "StmCmpRegUsed" = "'STM_CMP0_USED'"!][!//                     
                [!VAR "StmCmp0Used" = "num:i(1)"!][!//
              [!ENDIF!][!//
              [!IF "(node:value(node:ref(./ResourceMResourceRef)/McuStmCmp1RegAllocationConf) = 'STM_CMP1_USED_BY_STM')"!][!//
                [!VAR "StmCmpRegUsed" = "'STM_CMP1_USED'"!][!//       
                [!VAR "StmCmp1Used" = "num:i(1)"!][!//
              [!ENDIF!][!//
              [!IF "$StmCmp0Used = num:i(1) and $StmCmp1Used = num:i(1)"!][!//
                [!VAR "StmCmpRegUsed" = "'STM_CMP0_CMP1_USED'"!][!//        
              [!ENDIF!][!//
              [!IF "$StmCmp0Used = num:i(0) and $StmCmp1Used = num:i(0)"!][!//
                [!VAR "StmCmpRegUsed" = "'STM_CMP0_CMP1_UNUSED'"!][!//        
              [!ENDIF!][!//
              [!IF "$StmCmp0Used = num:i(0) and $StmCmp1Used = num:i(0) and $McuModPresence = num:i(0)"!][!//
                [!ERROR!]
                  Mcu STM CMP allocation is done in the Resource Manager module, however the MCU module is not present in the configuration.	
                [!ENDERROR!]
              [!ENDIF!][!//	
              [!IF "$Actual_CoreId = num:i(0)"!][!//              
                [!VAR "Stm_Core0_CmpAlloc" = "$StmCmpRegUsed"!][!//
              [!ELSEIF "$Actual_CoreId = num:i(1)"!][!//              
                [!VAR "Stm_Core1_CmpAlloc" = "$StmCmpRegUsed"!][!//
              [!ELSEIF "$Actual_CoreId = num:i(2)"!][!//              
                [!VAR "Stm_Core2_CmpAlloc" = "$StmCmpRegUsed"!][!//
              [!ELSEIF "$Actual_CoreId = num:i(3)"!][!//              
                [!VAR "Stm_Core3_CmpAlloc" = "$StmCmpRegUsed"!][!//
              [!ELSEIF "$Actual_CoreId = num:i(4)"!][!//              
                [!VAR "Stm_Core4_CmpAlloc" = "$StmCmpRegUsed"!][!//
              [!ELSEIF "$Actual_CoreId = num:i(5)"!][!//              
                [!VAR "Stm_Core5_CmpAlloc" = "$StmCmpRegUsed"!][!//
              [!ENDIF!]            
            [!ENDIF!][!//
          [!ENDLOOP!][!//  
        [!ENDIF!][!//    
      [!ENDLOOP!][!//

      [!CODE!]
        [!INDENT "2"!][!//
          {
            [!INDENT "4"!][!//
              [!"$Stm_Core0_TimerAlloc"!],
              [!"$Stm_Core0_CmpAlloc"!]
            [!ENDINDENT!][!//
          },
        [!ENDINDENT!][!//
        [!IF "(ecu:get('Mcu.NoOfCoreAvailable') > num:i(1))"!]
        [!INDENT "2"!][!//
          {
              [!INDENT "4"!][!//
                [!"$Stm_Core1_TimerAlloc"!],
                [!"$Stm_Core1_CmpAlloc"!]
              [!ENDINDENT!][!//
          },
        [!ENDINDENT!][!//
        [!ENDIF!][!//
        [!IF "(ecu:get('Mcu.NoOfCoreAvailable') > num:i(2))"!]
        [!INDENT "2"!][!//
          {
              [!INDENT "4"!][!//
                [!"$Stm_Core2_TimerAlloc"!],
                [!"$Stm_Core2_CmpAlloc"!]
              [!ENDINDENT!][!//
          },
        [!ENDINDENT!][!//
        [!ENDIF!][!//
        [!IF "(ecu:get('Mcu.NoOfCoreAvailable') > num:i(3))"!]
        [!ELSE!]
        [!ENDIF!]
        [!IF "(ecu:get('Mcu.NoOfCoreAvailable') > num:i(3))"!]
          [!INDENT "2"!][!//
            {
              [!INDENT "4"!][!//
                [!"$Stm_Core3_TimerAlloc"!],
                [!"$Stm_Core3_CmpAlloc"!]
              [!ENDINDENT!][!//
            },
          [!ENDINDENT!][!//
          [!IF "(ecu:get('Mcu.NoOfCoreAvailable') > num:i(4))"!]
          [!ELSE!]
          [!ENDIF!]
          [!IF "(ecu:get('Mcu.NoOfCoreAvailable') > num:i(4))"!]
            [!INDENT "2"!][!//
              {
                [!INDENT "4"!][!//
                  [!"$Stm_Core4_TimerAlloc"!],
                  [!"$Stm_Core4_CmpAlloc"!]
               [!ENDINDENT!][!//
              },
            [!ENDINDENT!][!//
            [!INDENT "2"!][!//
              {
                [!INDENT "4"!][!//
                 [!"$Stm_Core5_TimerAlloc"!],
                 [!"$Stm_Core5_CmpAlloc"!]  
               [!ENDINDENT!][!// 
              }
            [!ENDINDENT!][!// 
          [!ENDIF!]
        [!ENDIF!]
  
      [!ENDCODE!][!//
    
    [!ENDSELECT!][!//
  [!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!ENDIF!][!// IF "not(var:defined('STM_M'))
