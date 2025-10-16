[!/*
/*******************************************************************************
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
**  FILENAME  : Ocu.m                                                         **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE      : 2020-04-23                                                    **
**                                                                            **
**  BSW MODULE DESCRIPTION : NA                                               **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={26D7AE23-67B0-4289-9638-671A095FDA2A}]    **
**                                                                            **
**  DESCRIPTION  : Code template macro file for Ocu Driver                    **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) :Specification of OCU Driver,AUTOSAR Release 4.2.2&4.4.0 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
********************************************************************************
**                       Includes                                             **
****************************************************************************/!]
[!//
[!/* *** multiple inclusion protection*** */!][!//
[!IF "not(var:defined('OCU_M'))"!][!//
  [!VAR "OCU_M"="'true'"!][!//
  [!/*
  MACRO: OCU_CG_ConfigSwitch 
  Macro to generate configuration switch Values STD_ON/STD_OFF based on configuration
  true/false
  */!]
  [!MACRO "OCU_CG_ConfigSwitch", "nodeval" = ""!][!//
    [!//
    [!IF "$nodeval = 'true'"!][!//
      (STD_ON)[!//
    [!ELSE!][!//
      (STD_OFF)[!//
    [!ENDIF!][!//
  [!ENDMACRO!][!//
  
  [!/*
  MACRO: OCU_CG_ConfigSwitchInt 
  Macro to generate configuration switch Values STD_ON/STD_OFF based on configuration
  zero/non-zero
  */!]
  [!MACRO "OCU_CG_ConfigSwitchInt", "nodeval" = ""!][!//
    [!//
    [!IF "$nodeval != num:i(0)"!][!//
      (STD_ON)[!//
    [!ELSE!][!//
      (STD_OFF)[!//
    [!ENDIF!][!//
  [!ENDMACRO!][!//
  
  /*******************************************************************************
  ** Name             : OCU_CG_GenerateModuleMap                                **
  **                                                                            **
  ** Description      : Macro to generate core channel mappings for a module    **
  **                                                                            **
  *******************************************************************************/
  [!MACRO "OCU_CG_GenerateModuleMap"!][!//
    [!SELECT "as:modconf('ResourceM')[1]"!][!//
      [!VAR "CGMasterCoreId_Extract" = "substring(node:value(ResourceMMcalConfig/*[1]/ResourceMMasterCore),5,1)"!]
      [!VAR "CGCoreID" = "num:i(0)"!]
      [!VAR "CGAllocatedChannelMap" = "''"!]
      [!VAR "CGCoreMap" = "''"!]
      [!LOOP "ResourceMMcalConfig/*[1]/ResourceMMcalCore/*"!][!// 
        [!VAR "CGCoreID" = "./ResourceMCoreID"!]
        [!LOOP "ResourceMAllocation/*"!][!//
          [!VAR "TempMod" = "./ResourceMModuleName"!]
          [!IF "'OCU' = $TempMod"!][!//
            [!VAR "index" = "num:i(count(text:split(./ResourceMResourceRef, '/')))"!]
            [!VAR "ResourceName" = "text:split(./ResourceMResourceRef, '/')[num:i($index)]"!]
            [!VAR "CGCoreMap" = "text:toupper(concat($CGCoreMap, $CGCoreID, '_', $ResourceName, ','))"!][!//
            [!VAR "CGAllocatedChannelMap" = "text:toupper(concat($CGAllocatedChannelMap, $ResourceName, ','))"!][!//
          [!ENDIF!][!// 
        [!ENDLOOP!][!//
      [!ENDLOOP!][!//
    [!ENDSELECT!][!//
  [!ENDMACRO!]
  
  /*******************************************************************************
  ** Name             : OCU_CG_ValidateChAllocation                             **
  **                                                                            **
  ** Description      : Macro to validate if a channel is allocated to the core **
  **                                                                            **
  ** Pre-requisite    : CG_GenerateModuleMap macro should be called before      **
  **                    calling this macro                                      **
  *******************************************************************************/
  [!MACRO "OCU_CG_ValidateChAllocation", "CoreNumber" = "", "Channel" = ""!][!//
    [!VAR "CGAllocationResult" = "'FALSE'"!]
    [!VAR "CGChannelPattern" = "text:toupper(concat('CORE', num:i($CoreNumber), '_', $Channel))"!]
    [!IF "text:contains( text:split($CGCoreMap,','), $CGChannelPattern )"!][!// 
      [!VAR "CGAllocationResult" = "'TRUE'"!]
    [!ELSEIF "not(text:contains( text:split($CGAllocatedChannelMap,','), text:toupper($Channel)))"!][!//
      [!IF "num:i($CGMasterCoreId_Extract) = (num:i($CoreNumber))"!]
        [!VAR "CGAllocationResult" = "'TRUE'"!]
      [!ENDIF!][!// 
    [!ENDIF!][!//
  [!ENDMACRO!]
  
  
  /*******************************************************************************
  ** Name             : OCU_CG_GetCore                                          **
  **                                                                            **
  ** Description      : Macro to get the core to which the channel is assigned  **
  **                                                                            **
  ** Pre-requisite    : CG_GenerateModuleMap macro should be called before      **
  **                    calling this macro                                      **
  *******************************************************************************/
  [!MACRO "OCU_CG_GetCore", "Channel" = ""!][!//
    [!IF "(text:contains( text:split($CGAllocatedChannelMap,','), text:toupper($Channel)))"!]
      [!VAR "CGCoreIndexPos" = "num:i(text:indexOf(text:split($CGCoreMap), concat(text:toupper($Channel),',')) - 2)"!]
      [!VAR "CGCoreId_Extract" = "num:i(substring( $CGCoreMap, $CGCoreIndexPos, num:i(1)))"!]
    [!ELSE!]
      [!VAR "CGCoreId_Extract" = "num:i($CGMasterCoreId_Extract)"!]
    [!ENDIF!]
  [!ENDMACRO!]
[!ENDIF!]
