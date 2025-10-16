[!AUTOSPACING!]
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
**  FILENAME  : Pwm_17_GtmCcu6.m                                              **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE      : 2020-04-27                                                    **
**                                                                            **
**  BSW MODULE DESCRIPTION : Pwm.bmd                                          **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={B751D2B4-9144-4381-B41F-E3C3524D4351}]    **
**                 [/cover]                                                   **
**                                                                            **
**  DESCRIPTION  : Code template macro file for Pwm Driver                    **
**                                                                            **
**                                                                            **
**                                                                            **
**  SPECIFICATION(S) : AUTOSAR Specification of Pwm Driver                    **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
*/!]

[!/* *** multiple inclusion protection*** */!][!//
[!IF "not(var:defined('PWM_17_GTMCCU6_M'))"!][!//
  [!INDENT "0"!][!//
    [!VAR "PWM_17_GTMCCU6_M"="'true'"!][!//
    [!/*
    MACRO: PWM_ConfigSwitch 
    Macro to generate configuration switch Values STD_ON/STD_OFF based on configuration
    true/false
    */!]
    [!MACRO "PWM_ConfigSwitch", "nodeval" = ""!][!//
      [!//
      [!IF "$nodeval = 'true'"!][!//
        [!WS"1"!](STD_ON)[!//
      [!ELSE!][!//
        [!WS"1"!](STD_OFF)[!//
      [!ENDIF!]
    [!ENDMACRO!]

    [!/*
    MACRO: PWM_PrintPeriodUpdateEndPeriodComments
    Macro to print a set of comments;
    parameter dummy ; may be for future use
    */!]
    [!MACRO "PWM_PrintPeriodUpdateEndPeriodComments"!][!//
      /*
      Configuration: PWM_DUTY_PERIOD_UPDATED_ENDPERIOD
       Applicable for Variable Period Channel Class.
       Feature to have the duty cycle / period change, whether to update
       the duty / period at the end period or not.
      */
    [!ENDMACRO!]

    /*******************************************************************************
    ** Name             : PWM_GenerateModuleMap                                    **
    **                                                                            **
    ** Description      : Macro to generate core-channel mappings for a module    **
    **                                                                            **
    *******************************************************************************/
    /* [cover parentID={0AC3A5F0-7970-40fc-894E-68581183EE66}]
    Macro to generate module map. consist of core to channel mapping 
    [/cover] */
    [!VAR "CGAllocatedChannelCount" = "num:i(0)"!][!//
    [!MACRO "PWM_GenerateModuleMap", "Module" = ""!][!//
      [!NOCODE!][!//
        [!SELECT "as:modconf('ResourceM')[1]"!][!//
          [!VAR "CGMasterCoreId_Extract" = "substring(node:value(ResourceMMcalConfig/*[1]/ResourceMMasterCore),5,1)"!][!//
          [!VAR "CGCoreID" = "num:i(0)"!][!//
          [!VAR "CGAllocatedChannelMap" = "''"!][!//
          [!VAR "CGCoreMap" = "''"!][!//
          [!VAR "CGAllocatedCores" = "''"!][!//
          [!LOOP "ResourceMMcalConfig/*[1]/ResourceMMcalCore/*"!][!//
            [!VAR "CGCoreID" = "./ResourceMCoreID"!][!//
            [!LOOP "ResourceMAllocation/*"!][!//
              [!IF "$Module = ./ResourceMModuleName"!][!//
                [!IF "node:refvalid(./ResourceMResourceRef) = 'true'"!][!//
                [!ELSE!][!//
                  [!ERROR!]
                    ERROR: Invalid resource allocation done in [!"$CGCoreID"!] for [!"$Module"!] module:[!"node:path(.)"!] [!//
                  [!ENDERROR!]
                [!ENDIF!][!//
                [!VAR "index" = "num:i(count(text:split(./ResourceMResourceRef, '/')))"!][!//
                [!VAR "CGAllocatedChannelCount" = "$CGAllocatedChannelCount+num:i(1)"!][!//
                [!VAR "ResourceName" = "text:split(./ResourceMResourceRef, '/')[num:i($index)]"!][!//
                [!VAR "CGCoreMap" = "text:toupper(concat($CGCoreMap, $CGCoreID, '_', $ResourceName, ','))"!][!//
                [!VAR "CGAllocatedCores" = "concat($CGAllocatedCores,$CGCoreID,',')"!][!//
                [!VAR "CGAllocatedChannelMap" = "text:toupper(concat($CGAllocatedChannelMap, $ResourceName, ','))"!][!//
              [!ENDIF!][!//
            [!ENDLOOP!][!//
          [!ENDLOOP!][!//
        [!ENDSELECT!][!//
      [!ENDNOCODE!][!//
    [!ENDMACRO!][!//

    /*******************************************************************************
    ** Name             : PWM_ValidateChAllocation                                **
    **                                                                            **
    ** Description      : Macro to validate if a channel is allocated to the core **
    **                                                                            **
    ** Pre-requisite    : PWM_GenerateModuleMap macro should be called before     **
    **                    calling this macro                                      **
    *******************************************************************************/
    [!MACRO "PWM_ValidateChAllocation", "CoreNumber" = "", "Channel" = ""!][!//
      [!NOCODE!][!//
        [!VAR "CGAllocationResult" = "'FALSE'"!][!//
        [!VAR "CGChannelPattern" = "text:toupper(concat('CORE', num:i($CoreNumber), '_', $Channel))"!][!//
        [!IF "text:contains( text:split($CGCoreMap,','), $CGChannelPattern )"!][!//
          [!VAR "CGAllocationResult" = "'TRUE'"!][!//
        [!ELSEIF "not(text:contains( text:split($CGAllocatedChannelMap,','), text:toupper($Channel)))"!][!//
          [!IF "num:i($CGMasterCoreId_Extract) = (num:i($CoreNumber))"!][!//
            [!VAR "CGAllocationResult" = "'TRUE'"!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDNOCODE!][!//
    [!ENDMACRO!][!//
    /*******************************************************************************
    ** Name             : PWM_GetMasterCoreID                                     **
    **                                                                            **
    ** Description      : Macro to get master core ID                             **
    **                                                                            **
    ** Pre-requisite    : NA                                                      **
    *******************************************************************************/
    /* [cover parentID={CDCB31FF-E981-48a3-A0EA-D1F6CA034C78}]
      Macro to get master core ID
    [/cover] */
    [!MACRO "PWM_GetMasterCoreID"!][!//
      [!SELECT "as:modconf('ResourceM')[1]"!][!//
        [!VAR "CGMasterCoreId" = "node:value(ResourceMMcalConfig/*[1]/ResourceMMasterCore)"!][!//
      [!ENDSELECT!][!//
    [!ENDMACRO!][!//

  [!ENDINDENT!][!//
[!ENDIF!][!// IF "not(var:defined('PWM_17_GTMCCU6_M'))
