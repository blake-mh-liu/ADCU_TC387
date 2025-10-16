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
**  FILENAME  : Lin_17_AscLin.m                                               **
**                                                                            **
**  VERSION   : 7.0.0                                                         **
**                                                                            **
**  DATE      : 2020-06-30                                                    **
**                                                                            **
**  BSW MODULE DESCRIPTION : Lin.bmd                                          **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY :                                                            **
**                                                                            **
**  DESCRIPTION  : Code template macro file for Lin Driver                    **
**                                                                            **
**                                                                            **
**                                                                            **
**  SPECIFICATION(S) : Specification of Lin Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
********************************************************************************
*/!]
[!/* [cover parentID={A6441ED2-CF72-40f9-B26D-BD0C8B9BBA95}][/cover] */!][!//
[!/* [cover parentID={85D5F19A-EC0D-4dc7-A085-F9688CC1833A}][/cover] */!][!//

/*******************************************************************************
**MACRO: Lin_17_AscLin_CalcBaudParams                                         **
**Macro to calculate Baudrate parameters                                      **
*******************************************************************************/
/* [cover parentID={376367B3-351F-425c-B89D-2D4EB9B2D938}]
Macro to calculate Baudrate parameters.
[/cover] */
[!MACRO "Lin_17_AscLin_CalcBaudParams", "BaudRate" = "", "input_freq1" = ""!][!//
  [!NOCODE!][!//
    [!VAR "BaudConfig_found" = "num:i(0)"!][!//
    [!VAR "N_D" = "num:f(0.001)"!][!//
    [!VAR "O" = "num:i(16)"!][!//  /* BITCON.OVERSAMPLING + 1*/
    [!FOR "inc" = "num:i(0)" TO "num:i(1000)"!][!//  /* ForLoop1 */
      [!VAR "temp_pre" = "(num:i($input_freq1) * num:f($N_D) ) div ( ($BaudRate) * ($O))"!][!//
      [!IF "num:i($temp_pre) < num:i(4096) and num:i($temp_pre) >= num:i(1) and num:f($N_D) <=num:f(1)"!][!//   /* If Condition1 */
        [!VAR "temp_baud" = "(num:i($input_freq1) * num:f($N_D) ) div ( num:i($temp_pre) * ($O))"!][!//
        [!IF "num:i($temp_baud) = num:i($BaudRate)"!][!//   /* If Condition2 */
          [!VAR "Numerator" = "num:i(num:f($N_D) * 1000)"!][!//
          [!VAR "Denominator" = "num:i(1000)"!][!//
          [!VAR "Prescalar" = "num:i(($temp_pre)-1)"!][!//
          [!VAR "BaudConfig_found" = "num:i(1)"!][!//
          [!BREAK!][!//
        [!ENDIF!][!//      /* End Of If Condition2 */
      [!ENDIF!][!//         /* End Of If Condition1 */
      [!VAR "N_D" = "($N_D)+ num:f(0.001)"!][!//
    [!ENDFOR!][!// /* End of ForLoop1 */
    [!IF "$BaudConfig_found != num:i(1)"!][!//
      [!ERROR!][!//
        BaudRate Configuration couldnot be found for the input frequency LinSysClockRef: [!"$input_freq1"!] and LinChannelBaudRate: [!"$BaudRate"!]
      [!ENDERROR!][!//
    [!ENDIF!]
  [!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
**MACRO: Lin_17_AscLin_CalcWakeupParams                                       **
**Macro to calculate Prescalar and Depth parameters for Wakeup detection.     **
*******************************************************************************/
/*
Macro to calculate Prescalar and Depth parameters for Wakeup detection.
[/cover] */
[!MACRO "Lin_17_AscLin_CalcWakeupParams",  "input_freq2" = ""!][!//
  [!NOCODE!][!//
    [!VAR "wakeupval_found" = "num:i(0)"!][!//
    [!VAR "expectedval" = "(num:i($input_freq2) div num:i(1000000)) * num:i(150)"!][!//

    [!FOR "WakeupPrescalar" = "num:i(1)" TO "num:i(4096)"!][!//
      [!FOR "WakeupIocrDepth" = "num:i(1)" TO "num:i(63)"!][!//

        [!VAR "CalcVal1" = "num:i($WakeupPrescalar) * num:i($WakeupIocrDepth)"!][!//
        [!VAR "CalcVal2" = "num:i($WakeupPrescalar) * num:i($WakeupIocrDepth + 1)"!][!//

        [!IF "num:i($expectedval) = num:i($CalcVal1)"!][!//
          [!VAR "wakeupval_found" = "num:i(1)"!][!//
          [!BREAK!][!//
        [!ELSEIF "(num:i($expectedval) > num:i($CalcVal1)) and  (num:i($expectedval) <= num:i($CalcVal2))"!][!//
          [!VAR "wakeupval_found" = "num:i(1)"!][!//
          [!BREAK!][!//
        [!ENDIF!]
      [!ENDFOR!][!//
      [!IF "$wakeupval_found = num:i(1)"!][!//
        [!VAR "WakeupPrescalar" = "num:i($WakeupPrescalar) -  1"!][!//
      [!BREAK!][!//
      [!ENDIF!]
    [!ENDFOR!][!//
  [!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*********************************************************************************
**MACRO: Lin_17_AscLin_ConfigurationCheck                                       **
**Macro to verify if the configuration for Lin module is valid or not.          **
*********************************************************************************/
/* [cover parentID={C4824B8D-FB58-46ad-9923-478B9DCD4994}]
Macro to verify if the configuration for Lin module is valid or not.
[/cover] */
[!MACRO "Lin_17_AscLin_ConfigurationCheck",  "input_freq3" = ""!][!//
  [!NOCODE!][!//
    [!SELECT "as:modconf('Lin')[1]"!][!//.
      [!FOR "ASCLIN" = "0" TO "num:i(ecu:get('AscLin.MaxNoOfAscLinModules'))- 1"!][!//
        [!LOOP "LinGlobalConfig/LinChannel/*"!][!//
          [!VAR "tmp" = "num:i(count(./../*[LinChanAssignedHw = text:concat('ASCLIN',$ASCLIN)]))"!][!//
          [!IF "num:i($tmp) > num:i(1)"!][!//
            [!ERROR!][!//
              ASCLIN[!"$ASCLIN"!] module shouldn't be configured for more than 1 Lin Channel
            [!ENDERROR!][!//
          [!ELSEIF "num:i($tmp) = num:i(1)"!][!//
            [!VAR "flag" = "num:i(0)"!][!//
            [!VAR "Count" = "num:i(0)"!][!//
            [!VAR "AscLinHW" = "LinChanAssignedHw"!]
             [!SELECT "as:modconf('Mcu')[1]/McuHardwareResourceAllocationConf/*[1]"!][!//
               [!LOOP "./McuAscLinAllocationConf/*"!][!//
                 [!VAR "McuAscLinKernel" = "McuAscLinChannelAllocationConf/McuAscLinKernelId"!]
                 [!VAR "McuAscLinChannelAllocationConf" = "McuAscLinChannelAllocationConf/McuAscLinChannelAllocationConf"!]
                 [!IF "$AscLinHW = $McuAscLinKernel"!]
                   [!VAR "Count" = "$Count + num:i(1)"!][!//
                   [!VAR "flag" = "num:i(1)"!][!//]
                   [!IF "$McuAscLinChannelAllocationConf = 'ASCLIN_CH_USED_BY_LIN_DRIVER' and $Count > num:i(1)"!]
                     [!ERROR!]
                        More than one instance of [!"$AscLinHW"!] exists in Mcu Configuration container.
                     [!ENDERROR!][!//
                   [!ELSEIF "$AscLinHW = $McuAscLinKernel and $McuAscLinChannelAllocationConf != 'ASCLIN_CH_USED_BY_LIN_DRIVER'and $Count = num:i(1)"!]
                     [!ERROR!]
                        Select McuAscLinChannelAllocationConf and Configure the [!"$AscLinHW"!] hardware unit for LIN in Mcu Configuration container.
                     [!ENDERROR!][!//
                   [!ENDIF!][!//
                 [!ENDIF!][!//
                 [!SELECT "as:modconf('Lin')[1]"!][!//
                   [!IF "$McuAscLinChannelAllocationConf = 'ASCLIN_CH_USED_BY_LIN_DRIVER' and num:i(count(./LinGlobalConfig/LinChannel/*[LinChanAssignedHw = $McuAscLinKernel])) = num:i(0)"!][!//
                     [!ERROR!]
                       [!"$McuAscLinKernel"!] is not configured in Lin channel container.
                     [!ENDERROR!]
                   [!ENDIF!][!//
                 [!ENDSELECT!][!//
               [!ENDLOOP!][!//
               [!IF "$flag = num:i(0)"!][!//
                 [!ERROR!]
                  Allocate only configured ASCLIN hardware to McuAscLinKernel
                 [!ENDERROR!][!//
              [!ENDIF!][!//
             [!ENDSELECT!][!//
          [!ENDIF!] [!//
          [!IF "LinAutoCalcBaudParams = 'false'"!][!//
            [!VAR "Numerator" = "num:i(LinChannelBaudNumerator)"!][!//
            [!VAR "Denominator" = "num:i(LinChannelBaudDenominator)"!][!//
            [!VAR "Prescalar" = "num:i(LinChannelBaudPreScalar)"!][!//
            [!VAR "fPD" = "num:i($input_freq3) div (num:i($Prescalar) + 1)"!][!//
            [!VAR "fOVS" = "num:i($fPD) * num:i($Numerator) div num:i($Denominator)"!][!//
            [!VAR "BaudRate" = "num:i($fOVS) div (num:i(15) + 1)"!][!//

            [!IF "$BaudRate > num:i(20000)"!][!//
              [!ERROR!][!//
                BaudRate  > 20000 is not allowed for Lin. Reconfigure the LinChanBaudNumerator, LinChanBaudDenominator, LinChanBaudPrescalar parameters.
              [!ENDERROR!][!//
            [!ELSEIF "$BaudRate < num:i(1000)"!]
              [!ERROR!][!//
                BaudRate  < 1000 is not allowed for Lin. Reconfigure the LinChanBaudNumerator, LinChanBaudDenominator, LinChanBaudPrescalar parameters.
              [!ENDERROR!][!//
            [!ENDIF!][!//
          [!ENDIF!][!//
        [!ENDLOOP!][!//
      [!ENDFOR!][!//
    [!ENDSELECT!][!//
  [!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : LIN_GenerateModuleMap                                   **
**                                                                            **
** Description      : Macro to generate core-channel mappings for a module    **
**                                                                            **
*******************************************************************************/
/* [cover parentID={837DE294-F056-47fa-8278-97956D007396}]
Macro to generate module map. consist of core to channel mapping
[/cover] */
[!MACRO "Lin_17_AscLin_GenerateModuleMap", "Module" = ""!][!//
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
** Name             : LIN_ValidateChAllocation                                **
**                                                                            **
** Description      : Macro to validate if a channel is allocated to the core **
**                                                                            **
** Pre-requisite    : LIN_GenerateModuleMap macro should be called before     **
**                    calling this macro                                      **
*******************************************************************************/
/*
Macro checks the validity of the channel to the core
[/cover] */
[!MACRO "Lin_17_AscLin_ValidateChAllocation", "CoreNumber" = "", "Channel" = ""!][!//
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

