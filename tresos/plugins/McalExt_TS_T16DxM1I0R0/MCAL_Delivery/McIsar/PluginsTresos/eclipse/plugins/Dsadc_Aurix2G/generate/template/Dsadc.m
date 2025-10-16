[!/*
/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2023)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Dsadc.m                                                       **
**                                                                            **
**  VERSION   : 9.0.0                                                         **
**                                                                            **
**  DATE      : 2023-06-15                                                    **
**                                                                            **
**  BSW MODULE DESCRIPTION : Dsadc.bmd                                        **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={F6B4C1D2-FDDC-45de-A126-238743A842B6}]    **
**                                                                            **
**  DESCRIPTION  : Code template macro file for DSADC Driver                  **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Dsadc Driver                          **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
*/!]

[!/* *** multiple inclusion protection*** */!][!//
[!IF "not(var:defined('DSADC_M'))"!][!//
[!VAR "DSADC_M"="'true'"!][!//
[!AUTOSPACING!]

/*******************************************************************************
** Name             : Dsadc_ConfigPreCompileSwitch                            **
**                                                                            **
** Description      : Macro to generate configuration switch Values ON/OFF    **
**                    based on configuration true/false                       **
**                                                                            **
*******************************************************************************/

[!MACRO "Dsadc_ConfigPreCompileSwitch", "NodeVal" = ""!][!//
[!//
[!IF "$NodeVal = 'true'"!][!//
  (STD_ON)[!//
[!ELSE!][!//
  (STD_OFF)[!//
[!ENDIF!]
[!ENDMACRO!]

/*******************************************************************************
** Name             : Dsadc_ConfigureClcReg                                   **
**                                                                            **
** Description      : Macro to generate the value to be configured in the     **
**                    CLC register                                            **
*******************************************************************************/
[!MACRO "Dsadc_ConfigureClcReg","SleepModeConfig"= "","DsadcClcConfig"=""!][!//
[!NOCODE!][!//
[!VAR "DsadcClcConfig" = "num:i(0)"!]

[!VAR "SleepMode" = "num:i(0)"!]

[!IF "$SleepModeConfig = 'SLEEP_DISABLE'"!]
  [!VAR "SleepMode" = "num:i('1')"!]
[!ENDIF!]

[!VAR "DsadcClcConfig" = "bit:shl($SleepMode,3)"!]

[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Dsadc_ConfigureGlobalCfgReg                             **
**                                                                            **
** Description      : Macro to generate the value to be configured in the     **
**                    DSADC global configuration register                     **
*******************************************************************************/
[!MACRO "Dsadc_ConfigureGlobalCfgReg","DitherTrimValueConfig"= "","SyncClockGenConfig"= "","SupVoltValueConfig"= "","DsadcGlobalConfig"=""!][!//
[!NOCODE!][!//

[!VAR "DitherTrimValue" = "num:i(0)"!]

[!IF "$DitherTrimValueConfig = 'DSADC_DITHERING_LOW_100_MILVLT'"!]
  [!VAR "DitherTrimValue" = "num:i('1')"!]
[!ELSEIF "$DitherTrimValueConfig = 'DSADC_DITHERING_MED_200_MILVLT'"!]
  [!VAR "DitherTrimValue" = "num:i('3')"!]
[!ELSEIF "$DitherTrimValueConfig = 'DSADC_DITHERING_HIGH_400_MILVLT'"!]
  [!VAR "DitherTrimValue" = "num:i('7')"!]
[!ENDIF!]

[!VAR "DsadcGlobalConfig" = "bit:shl($DitherTrimValue,8)"!]

[!VAR "SyncClockGen" = "num:i(0)"!]

[!IF "$SyncClockGenConfig = 'UNSYNCHRONIZED_MODE'"!]
  [!VAR "SyncClockGen" = "num:i('1')"!]
[!ENDIF!]

[!VAR "DsadcGlobalConfig" = "bit:or($DsadcGlobalConfig,bit:shl($SyncClockGen,12))"!]

[!VAR "SupVoltValue" = "num:i(0)"!]
[!IF "$SupVoltValueConfig = 'VOLTAGESUPPLY_5V'"!]
  [!VAR "SupVoltValue" = "num:i('1')"!]
[!ELSEIF "$SupVoltValueConfig = 'VOLTAGESUPPLY_3_3V'"!]
  [!VAR "SupVoltValue" = "num:i('2')"!]
[!ENDIF!]

[!VAR "DsadcGlobalConfig" = "bit:or($DsadcGlobalConfig,bit:shl($SupVoltValue,13))"!]

[!VAR "DsadcGlobalConfig" = "bit:or($DsadcGlobalConfig,32768)"!]
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Dsadc_ConfigureCGReg                                    **
**                                                                            **
** Description      : Macro to generate the value to be configured in the     **
**                    Carrier generator configuration register                **
*******************************************************************************/

[!MACRO "Dsadc_ConfigureCGReg","BitReverseConfig"= "","CarrierSignalPolConfig"= "","CGFreqDivConfig"= "","CarrierGenConfig"=""!][!//
[!NOCODE!][!//

[!VAR "BitReverseMode" = "num:i(0)"!]
[!IF "$BitReverseConfig = 'DSADC_BIT_REVERSE_MODE'"!]
  [!VAR "BitReverseMode" = "num:i('1')"!]
[!ENDIF!]
[!VAR "CarrierGenConfig" = "bit:shl($BitReverseMode,2)"!]

[!VAR "CarrierSignalPol" = "num:i(0)"!]
  [!IF "$CarrierSignalPolConfig = 'DSADC_CARR_SIG_INVERTED'"!]
[!VAR "CarrierSignalPol" = "num:i('1')"!]
[!ENDIF!]
[!VAR "CarrierGenConfig" = "bit:or($CarrierGenConfig,bit:shl($CarrierSignalPol,3))"!]

[!VAR "CGFreqDiv" = "num:i(0)"!]
[!IF "$CGFreqDivConfig = 'DSADC_CG_CLOCKDIVIDER_DIV4'"!]
  [!VAR "CGFreqDiv" = "num:i(1)"!]
[!ELSEIF "$CGFreqDivConfig = 'DSADC_CG_CLOCKDIVIDER_DIV6'"!]
  [!VAR "CGFreqDiv" = "num:i(2)"!]
[!ELSEIF "$CGFreqDivConfig = 'DSADC_CG_CLOCKDIVIDER_DIV8'"!]
  [!VAR "CGFreqDiv" = "num:i(3)"!]
[!ELSEIF "$CGFreqDivConfig = 'DSADC_CG_CLOCKDIVIDER_DIV10'"!]
  [!VAR "CGFreqDiv" = "num:i(4)"!]
[!ELSEIF "$CGFreqDivConfig = 'DSADC_CG_CLOCKDIVIDER_DIV12'"!]
  [!VAR "CGFreqDiv" = "num:i(5)"!]
[!ELSEIF "$CGFreqDivConfig = 'DSADC_CG_CLOCKDIVIDER_DIV14'"!]
  [!VAR "CGFreqDiv" = "num:i(6)"!]
[!ELSEIF "$CGFreqDivConfig = 'DSADC_CG_CLOCKDIVIDER_DIV16'"!]
  [!VAR "CGFreqDiv" = "num:i(7)"!]
[!ELSEIF "$CGFreqDivConfig = 'DSADC_CG_CLOCKDIVIDER_DIV18'"!]
  [!VAR "CGFreqDiv" = "num:i(8)"!]
[!ELSEIF "$CGFreqDivConfig = 'DSADC_CG_CLOCKDIVIDER_DIV20'"!]
  [!VAR "CGFreqDiv" = "num:i(9)"!]
[!ELSEIF "$CGFreqDivConfig = 'DSADC_CG_CLOCKDIVIDER_DIV22'"!]
  [!VAR "CGFreqDiv" = "num:i(10)"!]
[!ELSEIF "$CGFreqDivConfig = 'DSADC_CG_CLOCKDIVIDER_DIV24'"!]
  [!VAR "CGFreqDiv" = "num:i(11)"!]
[!ELSEIF "$CGFreqDivConfig = 'DSADC_CG_CLOCKDIVIDER_DIV26'"!]
  [!VAR "CGFreqDiv" = "num:i(12)"!]
[!ELSEIF "$CGFreqDivConfig = 'DSADC_CG_CLOCKDIVIDER_DIV28'"!]
  [!VAR "CGFreqDiv" = "num:i(13)"!]
[!ELSEIF "$CGFreqDivConfig = 'DSADC_CG_CLOCKDIVIDER_DIV30'"!]
  [!VAR "CGFreqDiv" = "num:i(14)"!]
[!ELSEIF "$CGFreqDivConfig = 'DSADC_CG_CLOCKDIVIDER_DIV32'"!]
  [!VAR "CGFreqDiv" = "num:i(15)"!]
[!ENDIF!]
[!VAR "CarrierGenConfig" = "bit:or($CarrierGenConfig,bit:shl($CGFreqDiv,4))"!]

[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Dsadc_ConfigureCMVReg                                   **
**                                                                            **
** Description      : Macro to generate the value to be configured in the     **
**                    common mode voltage configuration register              **
*******************************************************************************/
[!MACRO "Dsadc_ConfigureCMVReg","CMVEnableConfig"= "","CMVSelectConfig"= "",
"MuxAPositivEnableConfig"= "","MuxBPositivEnableConfig"= "","MuxCPositivEnableConfig"= "","MuxDPositivEnableConfig"= "",
"MuxANegativEnableConfig"= "","MuxBNegativEnableConfig"= "","MuxCNegativEnableConfig"= "","MuxDNegativEnableConfig"= "",
"CMVRegConfig"=""!][!//
[!NOCODE!][!//

[!VAR "CMVSelect" = "num:i(0)"!][!//
[!IF "$CMVSelectConfig = 'DSADC_VCM_VREFX_4'"!][!//
  [!VAR "CMVSelect" = "num:i(1)"!][!//
[!ELSEIF "$CMVSelectConfig = 'DSADC_VCM_VREFX_8'"!][!//
  [!VAR "CMVSelect" = "num:i(2)"!][!//
[!ELSEIF "$CMVSelectConfig = 'DSADC_VCM_VREFX_16'"!][!//
  [!VAR "CMVSelect" = "num:i(3)"!][!//
[!ENDIF!]
[!VAR "CMVRegConfig" = "$CMVSelect"!][!//

[!VAR "CMVEnable" = "num:i(0)"!][!//
[!IF "$CMVEnableConfig = 'true'"!][!//
  [!VAR "CMVEnable" = "num:i(1)"!][!//
[!ENDIF!]
[!VAR "CMVRegConfig" = "bit:or($CMVRegConfig,bit:shl($CMVEnable,2))"!][!//

[!VAR "MuxAPositivEnable" = "num:i(0)"!][!//
[!IF "$MuxAPositivEnableConfig = 'true'"!][!//
  [!VAR "MuxAPositivEnable" = "num:i(1)"!][!//
[!ENDIF!]
[!VAR "CMVRegConfig" = "bit:or($CMVRegConfig,bit:shl($MuxAPositivEnable,16))"!][!//

[!VAR "MuxBPositivEnable" = "num:i(0)"!][!//
[!IF "$MuxBPositivEnableConfig = 'true'"!][!//
  [!VAR "MuxBPositivEnable" = "num:i(1)"!][!//
[!ENDIF!]
[!VAR "CMVRegConfig" = "bit:or($CMVRegConfig,bit:shl($MuxBPositivEnable,17))"!][!//

[!VAR "MuxCPositivEnable" = "num:i(0)"!][!//
[!IF "$MuxCPositivEnableConfig = 'true'"!][!//
  [!VAR "MuxCPositivEnable" = "num:i(1)"!][!//
[!ENDIF!]
[!VAR "CMVRegConfig" = "bit:or($CMVRegConfig,bit:shl($MuxCPositivEnable,18))"!][!//

[!VAR "MuxDPositivEnable" = "num:i(0)"!][!//
[!IF "$MuxDPositivEnableConfig = 'true'"!][!//
  [!VAR "MuxDPositivEnable" = "num:i(1)"!][!//
[!ENDIF!]
[!VAR "CMVRegConfig" = "bit:or($CMVRegConfig,bit:shl($MuxDPositivEnable,19))"!][!//

[!VAR "MuxANegativEnable" = "num:i(0)"!][!//
[!IF "$MuxANegativEnableConfig = 'true'"!][!//
  [!VAR "MuxANegativEnable" = "num:i(1)"!][!//
[!ENDIF!]
[!VAR "CMVRegConfig" = "bit:or($CMVRegConfig,bit:shl($MuxANegativEnable,20))"!][!//

[!VAR "MuxBNegativEnable" = "num:i(0)"!][!//
[!IF "$MuxBNegativEnableConfig = 'true'"!][!//
  [!VAR "MuxBNegativEnable" = "num:i(1)"!][!//
[!ENDIF!]
[!VAR "CMVRegConfig" = "bit:or($CMVRegConfig,bit:shl($MuxBNegativEnable,21))"!][!//

[!VAR "MuxCNegativEnable" = "num:i(0)"!][!//
[!IF "$MuxCNegativEnableConfig = 'true'"!][!//
  [!VAR "MuxCNegativEnable" = "num:i(1)"!][!//
[!ENDIF!]
[!VAR "CMVRegConfig" = "bit:or($CMVRegConfig,bit:shl($MuxCNegativEnable,22))"!][!//

[!VAR "MuxDNegativEnable" = "num:i(0)"!][!//
[!IF "$MuxDNegativEnableConfig = 'true'"!][!//
  [!VAR "MuxDNegativEnable" = "num:i(1)"!][!//
[!ENDIF!]
[!VAR "CMVRegConfig" = "bit:or($CMVRegConfig,bit:shl($MuxDNegativEnable,23))"!][!//

[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Dsadc_ConfigureChModulator                              **
**                                                                            **
** Description      : Macro to generate the value to be configured for the    **
**                    modulator channel configuration register.               **
*******************************************************************************/

[!MACRO "Dsadc_ConfigureChModulator","AnalogClockSyncDelayConfig"= "","ClockDividerConfig"= "","DitherEnableConfig"= "",
"IntRstEnableConfig"= "",
"InputGainConfig"= "",
"InputMuxActionModeConfig"= "",
"InputMuxControlModeConfig"= "",
"NegInputLineConfig"= "",
"PosInputLineConfig"= "",
"InputPinSelectionConfig"= "",
"DsadcTriggerModeConfig"= "",
"ModulatorRegConfig"=""!][!//
[!NOCODE!][!//

[!VAR "PosInputLine" = "num:i(0)"!][!//
[!IF "$PosInputLineConfig = 'DSADC_POS_IN_SUPPLY_VOLT'"!][!//
  [!VAR "PosInputLine" = "num:i(1)"!][!//
[!ELSEIF "$PosInputLineConfig = 'DSADC_POS_IN_COMMON_MODE_VOLT'"!][!//
  [!VAR "PosInputLine" = "num:i(2)"!][!//
[!ELSEIF "$PosInputLineConfig = 'DSADC_POS_IN_REFERENCE_GROUND'"!][!//
  [!VAR "PosInputLine" = "num:i(3)"!][!//
[!ENDIF!]
[!VAR "ModulatorRegConfig" = "$PosInputLine"!][!//

[!VAR "NegInputLine" = "num:i(0)"!][!//
[!IF "$NegInputLineConfig = 'DSADC_NEG_IN_SUPPLY_VOLT'"!][!//
  [!VAR "NegInputLine" = "num:i(1)"!][!//
[!ELSEIF "$NegInputLineConfig = 'DSADC_NEG_IN_COMMON_MODE_VOLT'"!][!//
  [!VAR "NegInputLine" = "num:i(2)"!][!//
[!ELSEIF "$NegInputLineConfig = 'DSADC_NEG_IN_REFERENCE_GROUND'"!][!//
  [!VAR "NegInputLine" = "num:i(3)"!][!//
[!ENDIF!]
[!VAR "ModulatorRegConfig" = "bit:or($ModulatorRegConfig,bit:shl($NegInputLine,2))"!][!//

[!VAR "InputGain" = "num:i(0)"!][!//
[!IF "$InputGainConfig = 'DSADC_INPUT_GAIN_FACTOR_2'"!][!//
  [!VAR "InputGain" = "num:i(1)"!][!//
[!ELSEIF "$InputGainConfig = 'DSADC_INPUT_GAIN_FACTOR_4'"!][!//
  [!VAR "InputGain" = "num:i(2)"!][!//
[!ENDIF!]
[!VAR "ModulatorRegConfig" = "bit:or($ModulatorRegConfig,bit:shl($InputGain,4))"!][!//

[!VAR "InputPinSelection" = "num:i(text:split($InputPinSelectionConfig,'_')[3])"!]
[!VAR "ModulatorRegConfig" = "bit:or($ModulatorRegConfig,bit:shl($InputPinSelection,8))"!][!//

[!VAR "InputMuxControlMode" = "num:i(0)"!][!//
[!IF "$InputMuxControlModeConfig = 'DSADC_INMUX_TRIG_EVENT_FALLING_EDGE'"!][!//
  [!VAR "InputMuxControlMode" = "num:i(1)"!][!//
[!ELSEIF "$InputMuxControlModeConfig = 'DSADC_INMUX_TRIG_EVENT_RISING_EDGE'"!][!//
  [!VAR "InputMuxControlMode" = "num:i(2)"!][!//
[!ELSEIF "$InputMuxControlModeConfig = 'DSADC_INMUX_TRIG_EVENT_BOTH_EDGES'"!][!//
  [!VAR "InputMuxControlMode" = "num:i(3)"!][!//
[!ENDIF!]
[!VAR "ModulatorRegConfig" = "bit:or($ModulatorRegConfig,bit:shl($InputMuxControlMode,12))"!][!//

[!VAR "InputMuxActionMode" = "num:i(0)"!][!//
[!IF "$DsadcTriggerModeConfig = 'DSADC_TRIGGER_MODE_WINDOW'"!][!//
  [!IF "$InputMuxActionModeConfig = 'DSADC_INPUTMUX_SINGLE_STEP_MODE'"!][!//
    [!VAR "InputMuxActionMode" = "num:i(1)"!][!//
  [!ENDIF!]
[!ENDIF!]
[!VAR "ModulatorRegConfig" = "bit:or($ModulatorRegConfig,bit:shl($InputMuxActionMode,14))"!][!//

[!VAR "ClockDivider" = "num:i(0)"!][!//
[!IF "$ClockDividerConfig = 'DSADC_CLOCKDIVIDER_DIV6'"!][!//
  [!VAR "ClockDivider" = "num:i(1)"!][!//
[!ELSEIF "$ClockDividerConfig = 'DSADC_CLOCKDIVIDER_DIV8'"!][!//
  [!VAR "ClockDivider" = "num:i(2)"!][!//
[!ELSEIF "$ClockDividerConfig = 'DSADC_CLOCKDIVIDER_DIV10'"!][!//
  [!VAR "ClockDivider" = "num:i(3)"!][!//
[!ELSEIF "$ClockDividerConfig = 'DSADC_CLOCKDIVIDER_DIV12'"!][!//
  [!VAR "ClockDivider" = "num:i(4)"!][!//
[!ELSEIF "$ClockDividerConfig = 'DSADC_CLOCKDIVIDER_DIV14'"!][!//
  [!VAR "ClockDivider" = "num:i(5)"!][!//
[!ELSEIF "$ClockDividerConfig = 'DSADC_CLOCKDIVIDER_DIV16'"!][!//
  [!VAR "ClockDivider" = "num:i(6)"!][!//
[!ELSEIF "$ClockDividerConfig = 'DSADC_CLOCKDIVIDER_DIV18'"!][!//
  [!VAR "ClockDivider" = "num:i(7)"!][!//
[!ENDIF!]
[!VAR "ModulatorRegConfig" = "bit:or($ModulatorRegConfig,bit:shl($ClockDivider,16))"!][!//

[!VAR "ModulatorRegConfig" = "bit:or($ModulatorRegConfig,bit:shl($AnalogClockSyncDelayConfig,20))"!]

[!VAR "DitherEnable" = "num:i(0)"!][!//
[!IF "$DitherEnableConfig = 'true'"!][!//
  [!VAR "DitherEnable" = "num:i(1)"!][!//
[!ENDIF!]
[!VAR "ModulatorRegConfig" = "bit:or($ModulatorRegConfig,bit:shl($DitherEnable,26))"!][!//

[!VAR "IntRstEnable" = "num:i(0)"!][!//
[!IF "$IntRstEnableConfig = 'true'"!][!//
  [!VAR "IntRstEnable" = "num:i(1)"!][!//
[!ENDIF!]
[!VAR "ModulatorRegConfig" = "bit:or($ModulatorRegConfig,bit:shl($IntRstEnable,27))"!][!//

[!VAR "ModulatorRegConfig" = "bit:or($ModulatorRegConfig,2147516416)"!]

[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Dsadc_ConfigureFilterChain                              **
**                                                                            **
** Description      : Macro to generate the value to be configured for the    **
**                    EDSADC channel filter chain configuration register.     **
*******************************************************************************/

[!MACRO "Dsadc_ConfigureFilterChain","FIR0EnableConfig"= "",
"FIR1EnableConfig"= "",
"OvershootCompensationEnConfig"= "",
"FIR1DecimationEnableConfig"= "",
"PreFilterEnableConfig"= "",
"AltServiceReqGenConfig"= "",
"OffsetCompFilterEnableConfig"= "",
"OffsetCompValueProtectConfig"= "",
"ComparatorEventSelectConfig"= "",
"FilterChainConfig"=""!][!//
[!NOCODE!][!//

[!VAR "FIR0Enable" = "num:i(0)"!][!//
[!IF "$FIR0EnableConfig = 'true'"!][!//
  [!VAR "FIR0Enable" = "num:i(1)"!][!//
[!ENDIF!]
[!VAR "FilterChainConfig" = "$FIR0Enable"!][!//

[!VAR "FIR1Enable" = "num:i(0)"!][!//
[!IF "$FIR1EnableConfig = 'true'"!][!//
  [!VAR "FIR1Enable" = "num:i(1)"!][!//
[!ENDIF!]
[!VAR "FilterChainConfig" = "bit:or($FilterChainConfig,bit:shl($FIR1Enable,1))"!][!//

[!VAR "OvershootCompenEnable" = "num:i(0)"!][!//
[!IF "$OvershootCompensationEnConfig = 'true'"!][!//
  [!VAR "OvershootCompenEnable" = "num:i(1)"!][!//
[!ENDIF!]
[!VAR "FilterChainConfig" = "bit:or($FilterChainConfig,bit:shl($OvershootCompenEnable,2))"!][!//

[!VAR "FIR1DecimationEnable" = "num:i(1)"!][!//
[!IF "$FIR1DecimationEnableConfig = 'true'"!][!//
  [!VAR "FIR1DecimationEnable" = "num:i(0)"!][!//
[!ENDIF!]
[!VAR "FilterChainConfig" = "bit:or($FilterChainConfig,bit:shl($FIR1DecimationEnable,3))"!][!//

[!VAR "PreFilterEnable" = "num:i(0)"!][!//
[!IF "$PreFilterEnableConfig = 'true'"!][!//
  [!VAR "PreFilterEnable" = "num:i(1)"!][!//
[!ENDIF!]
[!VAR "FilterChainConfig" = "bit:or($FilterChainConfig,bit:shl($PreFilterEnable,5))"!][!//

[!VAR "OffsetCompFilterEnable" = "num:i(0)"!][!//
[!IF "$OffsetCompFilterEnableConfig = 'DSADC_OFFCOMP_FILTER_RATE_1'"!][!//
  [!VAR "OffsetCompFilterEnable" = "num:i(1)"!][!//
[!ELSEIF "$OffsetCompFilterEnableConfig = 'DSADC_OFFCOMP_FILTER_RATE_2'"!][!//
  [!VAR "OffsetCompFilterEnable" = "num:i(2)"!][!//
[!ELSEIF "$OffsetCompFilterEnableConfig = 'DSADC_OFFCOMP_FILTER_RATE_3'"!][!//
  [!VAR "OffsetCompFilterEnable" = "num:i(3)"!][!//
[!ELSEIF "$OffsetCompFilterEnableConfig = 'DSADC_OFFCOMP_FILTER_RATE_4'"!][!//
  [!VAR "OffsetCompFilterEnable" = "num:i(4)"!][!//
[!ELSEIF "$OffsetCompFilterEnableConfig = 'DSADC_OFFCOMP_FILTER_RATE_5'"!][!//
  [!VAR "OffsetCompFilterEnable" = "num:i(5)"!][!//
[!ELSEIF "$OffsetCompFilterEnableConfig = 'DSADC_OFFCOMP_FILTER_RATE_6'"!][!//
  [!VAR "OffsetCompFilterEnable" = "num:i(6)"!][!//
[!ELSEIF "$OffsetCompFilterEnableConfig = 'DSADC_OFFCOMP_FILTER_RATE_7'"!][!//
  [!VAR "OffsetCompFilterEnable" = "num:i(7)"!][!//
[!ENDIF!]

[!VAR "FilterChainConfig" = "bit:or($FilterChainConfig,bit:shl($OffsetCompFilterEnable,8))"!][!//

[!VAR "OffsetCompValueProtect" = "num:i(0)"!][!//
[!IF "$OffsetCompValueProtectConfig = 'true'"!][!//
  [!VAR "OffsetCompValueProtect" = "num:i(1)"!][!//
[!ENDIF!]
[!VAR "FilterChainConfig" = "bit:or($FilterChainConfig,bit:shl($OffsetCompValueProtect,11))"!][!//

[!VAR "AuxServiceReqGen" = "num:i(0)"!][!//
[!IF "$AltServiceReqGenConfig = 'DSADC_COMPARATOR_EVENT'"!][!//
  [!VAR "AuxServiceReqGen" = "num:i(1)"!][!//
[!ELSEIF "$AltServiceReqGenConfig = 'DSADC_TIMESTAMP_EVENT'"!][!//
  [!VAR "AuxServiceReqGen" = "num:i(2)"!][!//
[!ELSEIF "$AltServiceReqGenConfig = 'DSADC_RESOLVER_EVENT'"!][!//
  [!VAR "AuxServiceReqGen" = "num:i(3)"!][!//
[!ENDIF!]
[!VAR "FilterChainConfig" = "bit:or($FilterChainConfig,bit:shl($AuxServiceReqGen,20))"!][!//

[!VAR "ComparatorEventSelect" = "num:i(0)"!][!//
[!IF "$ComparatorEventSelectConfig = 'DSADC_RESULT_INSIDE_RANGE'"!][!//
  [!VAR "ComparatorEventSelect" = "num:i(1)"!][!//
[!ELSEIF "$ComparatorEventSelectConfig = 'DSADC_RESULT_OUTSIDE_RANGE'"!][!//
  [!VAR "ComparatorEventSelect" = "num:i(2)"!][!//
[!ENDIF!]
[!VAR "FilterChainConfig" = "bit:or($FilterChainConfig,bit:shl($ComparatorEventSelect,22))"!][!//

[!VAR "FilterChainConfig" = "bit:or($FilterChainConfig,2147516416)"!]

[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Dsadc_ConfigureCICFilter                                **
**                                                                            **
** Description      : Macro to generate the value to be configured for the    **
**                    EDSADC channel filter chain configuration register.     **
*******************************************************************************/

[!MACRO "Dsadc_ConfigureCICFilter","CICFilterDecimationFactorConfig"= "",
"CICFilterStartValueConfig"= "",
"CICFilterConfig"=""!][!//
[!NOCODE!][!//

[!VAR "CICFilterConfig" = "num:i($CICFilterDecimationFactorConfig - 1)"!]
[!VAR "CICFilterConfig" = "bit:or($CICFilterConfig,bit:shl(num:i($CICFilterStartValueConfig - 1),16))"!][!//

[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Dsadc_ConfigureAuxCICFilter                             **
**                                                                            **
** Description      : Macro to generate the value to be configured for the    **
**                    EDSADC channel Auxiliary CIC filter register.           **
*******************************************************************************/

[!MACRO "Dsadc_ConfigureAuxCICFilter","AuxCICFilterEnableConfig"= "",
"AuxCICFilterDecimationFactorConfig"= "",
"AuxCICFilterConfig"=""!][!//
[!NOCODE!][!//

[!VAR "AuxCICFilterDecimation" = "num:i(0)"!][!//
[!VAR "AuxCICFilterEnable" = "num:i(0)"!][!//
[!IF "$AuxCICFilterEnableConfig = 'true'"!][!//
  [!VAR "AuxCICFilterEnable" = "num:i(1)"!][!//
  [!IF "$AuxCICFilterDecimationFactorConfig = 'DSADC_AUXCIC_OSR_32'"!][!//
    [!VAR "AuxCICFilterDecimation" = "num:i(1)"!][!//
  [!ENDIF!]
[!ENDIF!]

[!VAR "AuxCICFilterConfig" = "bit:or($AuxCICFilterEnable,bit:shl($AuxCICFilterDecimation,1))"!][!//

[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Dsadc_ConfigureOffsetCompensationReg                    **
**                                                                            **
** Description      : Macro to generate the value to be configured in the     **
**                    Offset compensation register                            **
*******************************************************************************/

[!MACRO "Dsadc_ConfigureOffsetCompensationReg","OffsetCompensationValueConfig"= "",
"OffsetCompensationRegConfig"=""!][!//
[!NOCODE!][!//

[!VAR "OffsetCompensationRegConfig" = "bit:and(num:hextoint('0x0000ffff'),num:i($OffsetCompensationValueConfig))"!][!//

[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Dsadc_ConfigureGainCorrection                           **
**                                                                            **
** Description      : Macro to generate the value to be configured in         **
**                    the Gain correction register                            **
*******************************************************************************/

[!MACRO "Dsadc_ConfigureGainCorrection","CICFilterOutputShiftPosConfig"= "","GainCorrMulFactorConfig"= "",
"GainCorrConfig"=""!][!//
[!NOCODE!][!//

[!VAR "GainCorrConfig" = "num:i(round($GainCorrMulFactorConfig * 4096))"!][!//

[!VAR "CICFilterOutputShiftPos" = "num:i(text:split($CICFilterOutputShiftPosConfig,'_')[2])"!]
[!VAR "GainCorrConfig" = "bit:or($GainCorrConfig,bit:shl($CICFilterOutputShiftPos,16))"!][!//

[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Dsadc_ConfigureGainCalibration                          **
**                                                                            **
** Description      : Macro to generate the value to be configured in         **
**                    the Gain calibration and gain correction registers      **
*******************************************************************************/

[!MACRO "Dsadc_ConfigureGainCalibration",
"CICFilterOutputShiftPosConfig"= "",
"GainCorrMulFactorConfig"= "",
"CICDecimationRateConfig"= "",
"GainCalibMulFactorConfig"= "",
"CalibAlgoTargetValueConfig"= "",
"GainCalibConfig"="","GainCtrlConfig"=""!][!//
[!NOCODE!][!//

[!VAR "GainCalibConfig" = "bit:or(num:i(round($GainCalibMulFactorConfig * 4096)),bit:shl($CalibAlgoTargetValueConfig,16))"!][!//

[!VAR "GainCtrlConfig" = "num:i(round($GainCorrMulFactorConfig * 4096))"!][!//

[!VAR "CICFilterOutputShiftPos" = "num:i(text:split($CICFilterOutputShiftPosConfig,'_')[2])"!]
[!VAR "GainCtrlConfig" = "bit:or($GainCtrlConfig,bit:shl($CICFilterOutputShiftPos,16))"!][!//

[!VAR "CICDecimationRate" = "num:i(0)"!][!//
[!IF "$CICDecimationRateConfig = 'DSADC_CIC_DECIMATION_RATE_16'"!][!//
  [!VAR "CICDecimationRate" = "num:i(1)"!][!//
[!ELSEIF "$CICDecimationRateConfig = 'DSADC_CIC_DECIMATION_RATE_32'"!][!//
  [!VAR "CICDecimationRate" = "num:i(2)"!][!//
[!ELSEIF "$CICDecimationRateConfig = 'DSADC_CIC_DECIMATION_RATE_64'"!][!//
  [!VAR "CICDecimationRate" = "num:i(3)"!][!//
[!ELSEIF "$CICDecimationRateConfig = 'DSADC_CIC_DECIMATION_RATE_128'"!][!//
  [!VAR "CICDecimationRate" = "num:i(4)"!][!//
[!ELSEIF "$CICDecimationRateConfig = 'DSADC_CIC_DECIMATION_RATE_256'"!][!//
  [!VAR "CICDecimationRate" = "num:i(5)"!][!//
[!ELSEIF "$CICDecimationRateConfig = 'DSADC_CIC_DECIMATION_RATE_512'"!][!//
  [!VAR "CICDecimationRate" = "num:i(6)"!][!//
[!ENDIF!]
[!VAR "GainCtrlConfig" = "bit:or($GainCtrlConfig,bit:shl($CICDecimationRate,24))"!][!//

[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Dsadc_LimitCheck                                        **
**                                                                            **
** Description      : Macro to generate the value to be configured in the     **
**                    range checking boundary selection register              **
*******************************************************************************/

[!MACRO "Dsadc_LimitCheck","LowerBoundaryValueConfig"= "","UpperBoundaryValueConfig"= "","LimitCheckConfig"=""!][!//
[!NOCODE!][!//

[!VAR "LowerBoundaryValue" = "bit:and(num:hextoint('0x0000ffff'),num:i($LowerBoundaryValueConfig))"!][!//
[!VAR "UpperBoundaryValue" = "bit:and(num:hextoint('0x0000ffff'),num:i($UpperBoundaryValueConfig))"!][!//
[!VAR "LimitCheckConfig" = "bit:or($LowerBoundaryValue,bit:shl($UpperBoundaryValueConfig,16))"!][!//

[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Dsadc_OvershootConfig                                   **
**                                                                            **
** Description      : Macro to generate the value to be configured in the     **
**                    range checking boundary selection register              **
*******************************************************************************/

[!MACRO "Dsadc_OvershootConfig","SlewRateFilterStrength"="","SlewRateFilterRunTime"="","StepDetectionMode"= "","StepDetectionThreshold"="",
"OverShootConfig"=""!][!//

[!NOCODE!][!//
[!VAR "SlewRateFilterStrengthConfig" = "num:i(0)"!][!//
[!IF "$SlewRateFilterStrength = 'DSADC_WEAK_FILTER_EFFECT'"!][!//
  [!VAR "SlewRateFilterStrengthConfig" = "num:i(1)"!][!//
[!ELSEIF "$SlewRateFilterStrength = 'DSADC_MEDIUM_FILTER_EFFECT'"!][!//
  [!VAR "SlewRateFilterStrengthConfig" = "num:i(2)"!][!//
[!ELSEIF "$SlewRateFilterStrength = 'DSADC_MAXIMUM_FILTER_EFFECT'"!][!//
  [!VAR "SlewRateFilterStrengthConfig" = "num:i(3)"!][!//
[!ENDIF!]
[!VAR "SlewRateFltrStr" = "bit:shl($SlewRateFilterStrengthConfig,0)"!][!//

[!VAR "SlewRateFilterRunTimeConfig" = "num:i(0)"!][!//
[!IF "$SlewRateFilterRunTime = 'DSADC_SLEWRATE_FILTR_RUNTIME_2'"!][!//
  [!VAR "SlewRateFilterRunTimeConfig" = "num:i(0)"!][!//
[!ELSEIF "$SlewRateFilterRunTime = 'DSADC_SLEWRATE_FILTR_RUNTIME_4'"!][!//
  [!VAR "SlewRateFilterRunTimeConfig" = "num:i(1)"!][!//
[!ELSEIF "$SlewRateFilterRunTime = 'DSADC_SLEWRATE_FILTR_RUNTIME_8'"!][!//
  [!VAR "SlewRateFilterRunTimeConfig" = "num:i(2)"!][!//
[!ELSEIF "$SlewRateFilterRunTime = 'DSADC_SLEWRATE_FILTR_RUNTIME_16'"!][!//
  [!VAR "SlewRateFilterRunTimeConfig" = "num:i(3)"!][!//
[!ENDIF!]
[!VAR "SlewRateFltrRT" = "bit:or($SlewRateFltrStr,bit:shl($SlewRateFilterRunTimeConfig,2))"!][!//

[!VAR "StepDetectionModeConfig" = "num:i(0)"!][!//
[!IF "$StepDetectionMode = 'DSADC_STEP_DETECT_CMP_LAST'"!][!//
  [!VAR "StepDetectionModeConfig" = "num:i(0)"!][!//
[!ELSEIF "$StepDetectionMode = 'DSADC_STEP_DETECT_CMP_SEC_LAST'"!][!//
  [!VAR "StepDetectionModeConfig" = "num:i(1)"!][!//
[!ENDIF!]
[!VAR "StepDetectMode" = "bit:or($SlewRateFltrRT,bit:shl($StepDetectionModeConfig,4))"!][!//

[!VAR "StepDetectionThresholdConfig" = "$StepDetectionThreshold"!][!//
[!VAR "OverShootConfig" = "bit:or($StepDetectMode,bit:shl($StepDetectionThresholdConfig,16))"!][!//
[!ENDNOCODE!][!//

[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Dsadc_DemodulatorConfig                                 **
**                                                                            **
** Description      : Macro to generate the value to be configured in the     **
**                    EDSADC channel demodulator configuration register.      **
*******************************************************************************/

[!MACRO "Dsadc_DemodulatorConfig","IntegratorTriggerModeConfig"= "",
"TriggerSelectConfig"= "",
"ResultDisplayModeConfig"= "",
"TimestampModeEnableConfig"= "",
"TimestampTriggerModeConfig"= "",
"TriggerModeConfig"= "",
"GateActiveLevelConfig"= "",
"DemodulatorRegConfig"= ""!][!//
[!NOCODE!][!//

[!VAR "TriggerSelect" = "num:i(text:split($TriggerSelectConfig,'_')[2])"!][!//
[!VAR "DemodulatorRegConfig" = "bit:shl($TriggerSelect,16)"!][!//

[!VAR "IntegratorTriggerMode" = "num:i(0)"!][!//
[!IF "$IntegratorTriggerModeConfig = 'DSADC_INTR_FALLING_EDGE'"!][!//
  [!VAR "IntegratorTriggerMode" = "num:i(1)"!][!//
[!ELSEIF "$IntegratorTriggerModeConfig = 'DSADC_INTR_RISING_EDGE'"!][!//
  [!VAR "IntegratorTriggerMode" = "num:i(2)"!][!//
[!ELSEIF "$IntegratorTriggerModeConfig = 'DSADC_INTR_ALWAYS_ACTIVE'"!][!//
  [!VAR "IntegratorTriggerMode" = "num:i(3)"!][!//
[!ENDIF!]

[!VAR "DemodulatorRegConfig" = "bit:or($DemodulatorRegConfig,bit:shl($IntegratorTriggerMode,20))"!][!//

[!VAR "TimestampTrigger" = "num:i(0)"!][!//
[!IF "($TriggerModeConfig = 'DSADC_TRIGGER_MODE_WINDOW') and ($TimestampModeEnableConfig = 'DSADC_TIMESTAMP_ENABLED') and ($GateActiveLevelConfig = 'DSADC_GATE_LOW_LEVEL')"!][!//
  [!IF "($TimestampTriggerModeConfig = 'DSADC_TIMESTAMP_WINDOWOPEN')"!][!//
    [!VAR "TimestampTrigger" = "num:i(1)"!][!//
  [!ELSEIF "($TimestampTriggerModeConfig = 'DSADC_TIMESTAMP_WINDOWCLOSE')"!][!//
    [!VAR "TimestampTrigger" = "num:i(2)"!][!//
  [!ENDIF!]
[!ELSEIF "($TriggerModeConfig = 'DSADC_TRIGGER_MODE_WINDOW') and ($TimestampModeEnableConfig = 'DSADC_TIMESTAMP_ENABLED') and ($GateActiveLevelConfig = 'DSADC_GATE_HIGH_LEVEL')"!][!//
  [!IF "($TimestampTriggerModeConfig = 'DSADC_TIMESTAMP_WINDOWOPEN')"!][!//
    [!VAR "TimestampTrigger" = "num:i(2)"!][!//
  [!ELSEIF "($TimestampTriggerModeConfig = 'DSADC_TIMESTAMP_WINDOWCLOSE')"!][!//
    [!VAR "TimestampTrigger" = "num:i(1)"!][!//
  [!ENDIF!]
[!ENDIF!]

[!VAR "DemodulatorRegConfig" = "bit:or($DemodulatorRegConfig,bit:shl($TimestampTrigger,22))"!][!//

[!/* [cover parentID={98C17187-95B5-4b67-BAE2-16726ACD9B95}]DataReadMode[/cover] */!][!//
[!VAR "DataReadMode" = "num:i(1)"!][!//
[!IF "($TriggerModeConfig = 'DSADC_TRIGGER_MODE_WINDOW') and ($TimestampModeEnableConfig = 'DSADC_TIMESTAMP_ENABLED') and ($TimestampTriggerModeConfig = 'DSADC_TIMESTAMP_WINDOWOPEN')"!][!//
  [!VAR "DataReadMode" = "num:i(0)"!][!//
[!ENDIF!]
[!VAR "DemodulatorRegConfig" = "bit:or($DemodulatorRegConfig,bit:shl($DataReadMode,26))"!][!//

[!VAR "TimestampEnable" = "num:i(0)"!][!//
[!IF "($TimestampModeEnableConfig = 'DSADC_TIMESTAMP_ENABLED') and ($TimestampTriggerModeConfig = 'DSADC_TIMESTAMP_WINDOWOPEN')"!][!//
  [!VAR "TimestampEnable" = "num:i(1)"!][!//
[!ENDIF!]

[!VAR "DemodulatorRegConfig" = "bit:or($DemodulatorRegConfig,bit:shl($TimestampEnable,28))"!][!//

[!VAR "ResultDisplayMode" = "num:i(0)"!][!//
[!IF "$ResultDisplayModeConfig = 'DSADC_RES_UNSIGNED_MODE'"!][!//
  [!VAR "ResultDisplayMode" = "num:i(1)"!][!//
[!ENDIF!]

[!VAR "DemodulatorRegConfig" = "bit:or($DemodulatorRegConfig,bit:shl($ResultDisplayMode,29))"!][!//

[!VAR "DemodulatorRegConfig" = "bit:or($DemodulatorRegConfig,2147516416)"!]

[!ENDNOCODE!][!//
[!ENDMACRO!][!//


/*******************************************************************************
** Name             : Dsadc_FifoConfig                                        **
**                                                                            **
** Description      : Macro to generate the value to be configured in the     **
**                    EDSADC channel Result FIFO configuration register.      **
*******************************************************************************/

[!MACRO "Dsadc_FifoConfig","TimestampModeEnableConfig"= "",
"TriggerModeConfig"= "",
"TimestampTriggerModeConfig"= "",
"DsadcFifoCtrlRegConfig"= ""!][!//
[!NOCODE!][!//

[!VAR "FifoFillLevel" = "num:i(0)"!][!//
[!IF "($TriggerModeConfig = 'DSADC_TRIGGER_MODE_WINDOW') and ($TimestampModeEnableConfig = 'DSADC_TIMESTAMP_ENABLED') and ($TimestampTriggerModeConfig = 'DSADC_TIMESTAMP_WINDOWOPEN')"!][!//
  [!VAR "FifoFillLevel" = "num:i(2)"!][!//
[!ENDIF!]
[!VAR "DsadcFifoCtrlRegConfig" = "bit:or($DsadcFifoCtrlRegConfig,bit:shl($FifoFillLevel,0))"!][!//

[!ENDNOCODE!][!//
[!ENDMACRO!][!//


/*******************************************************************************
** Name             : Dsadc_TimestampCntConfig                                **
**                                                                            **
** Description      : Macro to generate the value to be configured in the     **
**                    time stamp register                                     **
*******************************************************************************/

[!MACRO "Dsadc_TimestampCntConfig","TimestampCounterClockSelConfig"= "",
"InputMuxSetCopyEnableConfig"= "",
"TimestampFeatureConfig"= "",
"TimestampCntRegConfig"=""!][!//
[!NOCODE!][!//

[!VAR "TimestampCounterClockSel" = "num:i(0)"!][!//
[!IF "$TimestampCounterClockSelConfig = 'CLOCKDIVIDER_DIV2'"!][!//
  [!VAR "TimestampCounterClockSel" = "num:i(1)"!][!//
[!ELSEIF "$TimestampCounterClockSelConfig = 'CLOCKDIVIDER_DIV4'"!][!//
  [!VAR "TimestampCounterClockSel" = "num:i(2)"!][!//
[!ELSEIF "$TimestampCounterClockSelConfig = 'CLOCKDIVIDER_DIV8'"!][!//
  [!VAR "TimestampCounterClockSel" = "num:i(3)"!][!//
[!ENDIF!]

[!VAR "TimestampCntRegConfig" = "bit:shl($TimestampCounterClockSel,16)"!][!//

[!VAR "TimestampFeature" = "num:i(0)"!][!//
[!/* [cover parentID={3AAD76EE-507F-4b5c-9559-B957652E7D89}]extract the timestamp run control bit[/cover] */!][!//
[!IF "$TimestampFeatureConfig = 'DSADC_TIMESTAMP_ENABLED'"!][!//
  [!VAR "TimestampFeature" = "num:i(1)"!][!//
[!ENDIF!]

[!VAR "TimestampCntRegConfig" = "bit:or($TimestampCntRegConfig,bit:shl($TimestampFeature,19))"!][!//

[!VAR "InputMuxSetCopyEnable" = "num:i(0)"!][!//
[!IF "$InputMuxSetCopyEnableConfig = 'true'"!][!//
  [!VAR "InputMuxSetCopyEnable" = "num:i(1)"!][!//
[!ENDIF!]

[!VAR "TimestampCntRegConfig" = "bit:or($TimestampCntRegConfig,bit:shl($InputMuxSetCopyEnable,20))"!][!//

[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Dsadc_IntegratorConfig                                  **
**                                                                            **
** Description      : Macro to generate the value to be configured in the     **
**                    integration window control register                     **
*******************************************************************************/

[!MACRO "Dsadc_IntegratorConfig","DiscardCountConfig"= "",
"IntegrationCountConfig"= "",
"IntegrationTriggerConfig"= "",
"IntegratorRegConfig"=""!][!//
[!NOCODE!][!//

[!VAR "IntegratorShiftControl" = "num:i(0)"!][!//
[!IF "$IntegrationCountConfig = '2'"!][!//
  [!VAR "IntegratorShiftControl" = "num:i(0)"!][!//
[!ELSEIF "($IntegrationCountConfig >= '3') and ($IntegrationCountConfig <= '4')"!][!//
  [!VAR "IntegratorShiftControl" = "num:i(1)"!][!//
[!ELSEIF "($IntegrationCountConfig >= '5') and ($IntegrationCountConfig <= '8')"!][!//
  [!VAR "IntegratorShiftControl" = "num:i(2)"!][!//
[!ELSEIF "($IntegrationCountConfig >= '9') and ($IntegrationCountConfig <= '16')"!][!//
  [!VAR "IntegratorShiftControl" = "num:i(3)"!][!//
[!ELSEIF "($IntegrationCountConfig >= '17') and ($IntegrationCountConfig <= '32')"!][!//
  [!VAR "IntegratorShiftControl" = "num:i(4)"!][!//
[!ELSEIF "($IntegrationCountConfig >= '33') and ($IntegrationCountConfig <= '64')"!][!//
  [!VAR "IntegratorShiftControl" = "num:i(5)"!][!//
[!ENDIF!][!//
[!VAR "IntegratorRegConfig" = "$IntegratorShiftControl"!][!//

[!/* [cover parentID={8EE8E4F8-A3C2-4eb8-814E-3321B9B1FFEC}]For Trigger mode window IWC is 1[/cover] */!][!//
[!VAR "IntegrationWindowCtrl" = "num:i(0)"!][!//
[!IF "$IntegrationTriggerConfig = 'DSADC_TRIGGER_MODE_WINDOW'"!][!//
  [!VAR "IntegrationWindowCtrl" = "num:i(1)"!][!//
[!ENDIF!]
[!VAR "IntegratorRegConfig" = "bit:or($IntegratorRegConfig,bit:shl($IntegrationWindowCtrl,4))"!][!//

[!/* [cover parentID={8EE8E4F8-A3C2-4eb8-814E-3321B9B1FFEC}]IWS set to 1 always[/cover] */!][!//
[!VAR "IntegratorRegConfig" = "bit:or($IntegratorRegConfig,bit:shl(num:i(1),5))"!][!//

[!VAR "IntegratorRegConfig" = "bit:or($IntegratorRegConfig,bit:shl($DiscardCountConfig,16))"!][!//

[!VAR "IntegratorRegConfig" = "bit:or($IntegratorRegConfig,bit:shl(num:i($IntegrationCountConfig - 1),24))"!][!//

[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Dsadc_ChannelIntModeConfig                              **
**                                                                            **
** Description      : Macro to generate the value to be configured in the     **
**                    Interrupt mode field in SRGM field of Filter Register   **
*******************************************************************************/
[!/* [cover parentID={54E52716-1D02-45e7-B0BE-AA886DE024AD},{8EE8E4F8-A3C2-4eb8-814E-3321B9B1FFEC}]Dsadc_ChannelIntModeConfig[/cover] */!][!//
[!MACRO "Dsadc_ChannelIntModeConfig","TriggerModeConfig"= "",
"TimestampTriggerModeConfig"= "",
"GateActiveLevelConfig"= "",
"TimestampFeatureConfig"= "",
"DsadcChannelIntMode"=""!][!//
[!NOCODE!][!//

[!/* [cover parentID={41FC6101-9BD4-4db9-9082-D0BE68CAB19D}]Initilaize the Channel Intrerrupt Mode as 3[/cover] */!][!//
[!VAR "DsadcChannelIntMode" = "num:i(3)"!][!//
[!/* [cover parentID={37F903C9-5A7C-4e76-856B-2620786C645F}]Check Window Active phase is High[/cover] */!][!//
[!IF "($TriggerModeConfig = 'DSADC_TRIGGER_MODE_WINDOW') and ($GateActiveLevelConfig = 'DSADC_GATE_HIGH_LEVEL')"!][!//
  [!IF " ($TimestampFeatureConfig = 'DSADC_TIMESTAMP_DISABLED') or (($TimestampFeatureConfig = 'DSADC_TIMESTAMP_ENABLED') and ($TimestampTriggerModeConfig = 'DSADC_TIMESTAMP_WINDOWCLOSE'))"!][!//
    [!VAR "DsadcChannelIntMode" = "num:i(1)"!][!//
  [!ENDIF!]
[!/* [cover parentID={5050E686-823C-45e7-928D-BA1F468020F8}]Check Window Active phase is Low[/cover] */!][!//  
[!ELSEIF "($TriggerModeConfig = 'DSADC_TRIGGER_MODE_WINDOW') and ($GateActiveLevelConfig = 'DSADC_GATE_LOW_LEVEL') and ($TimestampFeatureConfig = 'DSADC_TIMESTAMP_DISABLED')"!][!//
  [!IF " ($TimestampFeatureConfig = 'DSADC_TIMESTAMP_DISABLED') or (($TimestampFeatureConfig = 'DSADC_TIMESTAMP_ENABLED') and ($TimestampTriggerModeConfig = 'DSADC_TIMESTAMP_WINDOWCLOSE'))"!][!//
    [!VAR "DsadcChannelIntMode" = "num:i(2)"!][!//
  [!ENDIF!]
[!ENDIF!]

[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Dsadc_ResolverConfig                                    **
**                                                                            **
** Description      : Macro to generate the value to be configured in the     **
**                    carrier generator synchronization and rectification     **
**                    configuration registers                                 **
*******************************************************************************/

[!MACRO "Dsadc_ResolverConfig","RectificationEnableConfig"= "",
"SignSignalSourceConfig"= "",
"SignSignalChannelConfig"= "",
"PosSignDelayValueConfig"= "",
"NegSignDelayValueConfig"= "",
"CGSyncRegConfig"="","RectifierRegConfig"=""!][!//
[!NOCODE!][!//

[!VAR "CGSyncRegConfig" = "bit:or(bit:shl($PosSignDelayValueConfig,16),bit:shl($NegSignDelayValueConfig,24))"!][!//

[!VAR "RectificationEnable" = "num:i(0)"!][!//
[!IF "$RectificationEnableConfig = 'true'"!][!//
  [!VAR "RectificationEnable" = "num:i(1)"!][!//
[!ENDIF!]
[!VAR "RectifierRegConfig" = "$RectificationEnable"!][!//

[!VAR "SignSignalSource" = "num:i(text:split($SignSignalSourceConfig,'_')[2])"!][!//
[!VAR "RectifierRegConfig" = "bit:or($RectifierRegConfig,bit:shl($SignSignalSource,4))"!][!//

[!VAR "SignSignalChannel" = "num:i(text:split($SignSignalChannelConfig,'DSADC_CHANNEL_')[1])"!][!//
[!VAR "RectifierRegConfig" = "bit:or($RectifierRegConfig,bit:shl($SignSignalChannel,8))"!][!//

[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Dsadc_PatternDetectionConfiguration                     **
**                                                                            **
** Description      : Macro to generate the value to be configured for the    **
**                    the OGU output channel, in accordance with element      **
**                    of structure type Dsadc_EruOguConfigType                **
*******************************************************************************/

[!MACRO "Dsadc_PatternDetectionConfiguration","OguChannelRef"= "",
"EruErsCh0PatternFlagEnableConfig"= "",
"EruErsCh1PatternFlagEnableConfig"= "",
"EruErsCh2PatternFlagEnableConfig"= "",
"EruErsCh3PatternFlagEnableConfig"= "",
"EruErsCh4PatternFlagEnableConfig"= "",
"EruErsCh5PatternFlagEnableConfig"= "",
"EruErsCh6PatternFlagEnableConfig"= "",
"EruErsCh7PatternFlagEnableConfig"= "",
"OguChNo"="",
"EruIgcrCfg"="",
"EruChSelInOguConfig"=""!][!//
[!NOCODE!][!//

[!VAR "OguChNo" = "num:i(substring-after($OguChannelRef,'McuEruChannelOutputUnitConf_'))"!][!//

[!VAR "EruErsCh0PatternFlagEnable" = "num:i(0)"!][!//
[!IF "$EruErsCh0PatternFlagEnableConfig = 'true'"!][!//
  [!VAR "EruErsCh0PatternFlagEnable" = "num:i(1)"!][!//
  [!VAR "EruChSelInOguConfig" = "bit:or($EruChSelInOguConfig,bit:shl(1,0))"!][!//
[!ENDIF!]
[!VAR "EruIgcrCfg" = "$EruErsCh0PatternFlagEnable"!][!//

[!VAR "EruErsCh1PatternFlagEnable" = "num:i(0)"!][!//
[!IF "$EruErsCh1PatternFlagEnableConfig = 'true'"!][!//
  [!VAR "EruErsCh1PatternFlagEnable" = "num:i(1)"!][!//
  [!VAR "EruChSelInOguConfig" = "bit:or($EruChSelInOguConfig,bit:shl(1,1))"!][!//
[!ENDIF!]
[!VAR "EruIgcrCfg" = "bit:or($EruIgcrCfg,bit:shl($EruErsCh1PatternFlagEnable,1))"!][!//

[!VAR "EruErsCh2PatternFlagEnable" = "num:i(0)"!][!//
[!IF "$EruErsCh2PatternFlagEnableConfig = 'true'"!][!//
  [!VAR "EruErsCh2PatternFlagEnable" = "num:i(1)"!][!//
  [!VAR "EruChSelInOguConfig" = "bit:or($EruChSelInOguConfig,bit:shl(1,2))"!][!//
[!ENDIF!]
[!VAR "EruIgcrCfg" = "bit:or($EruIgcrCfg,bit:shl($EruErsCh2PatternFlagEnable,2))"!][!//

[!VAR "EruErsCh3PatternFlagEnable" = "num:i(0)"!][!//
[!IF "$EruErsCh3PatternFlagEnableConfig = 'true'"!][!//
  [!VAR "EruErsCh3PatternFlagEnable" = "num:i(1)"!][!//
  [!VAR "EruChSelInOguConfig" = "bit:or($EruChSelInOguConfig,bit:shl(1,3))"!][!//
[!ENDIF!]
[!VAR "EruIgcrCfg" = "bit:or($EruIgcrCfg,bit:shl($EruErsCh3PatternFlagEnable,3))"!][!//

[!VAR "EruErsCh4PatternFlagEnable" = "num:i(0)"!][!//
[!IF "$EruErsCh4PatternFlagEnableConfig = 'true'"!][!//
  [!VAR "EruErsCh4PatternFlagEnable" = "num:i(1)"!][!//
  [!VAR "EruChSelInOguConfig" = "bit:or($EruChSelInOguConfig,bit:shl(1,4))"!][!//
[!ENDIF!]
[!VAR "EruIgcrCfg" = "bit:or($EruIgcrCfg,bit:shl($EruErsCh4PatternFlagEnable,4))"!][!//

[!VAR "EruErsCh5PatternFlagEnable" = "num:i(0)"!][!//
[!IF "$EruErsCh5PatternFlagEnableConfig = 'true'"!][!//
  [!VAR "EruErsCh5PatternFlagEnable" = "num:i(1)"!][!//
  [!VAR "EruChSelInOguConfig" = "bit:or($EruChSelInOguConfig,bit:shl(1,5))"!][!//
[!ENDIF!]
[!VAR "EruIgcrCfg" = "bit:or($EruIgcrCfg,bit:shl($EruErsCh5PatternFlagEnable,5))"!][!//

[!VAR "EruErsCh6PatternFlagEnable" = "num:i(0)"!][!//
[!IF "$EruErsCh6PatternFlagEnableConfig = 'true'"!][!//
  [!VAR "EruErsCh6PatternFlagEnable" = "num:i(1)"!][!//
  [!VAR "EruChSelInOguConfig" = "bit:or($EruChSelInOguConfig,bit:shl(1,6))"!][!//
[!ENDIF!]
[!VAR "EruIgcrCfg" = "bit:or($EruIgcrCfg,bit:shl($EruErsCh6PatternFlagEnable,6))"!][!//

[!VAR "EruErsCh7PatternFlagEnable" = "num:i(0)"!][!//
[!IF "$EruErsCh7PatternFlagEnableConfig = 'true'"!][!//
  [!VAR "EruErsCh7PatternFlagEnable" = "num:i(1)"!][!//
  [!VAR "EruChSelInOguConfig" = "bit:or($EruChSelInOguConfig,bit:shl(1,7))"!][!//
[!ENDIF!]
[!VAR "EruIgcrCfg" = "bit:or($EruIgcrCfg,bit:shl($EruErsCh7PatternFlagEnable,7))"!][!//

[!VAR "EruIgcrCfg" = "bit:or($EruIgcrCfg,bit:shl(1,13))"!][!//
[!VAR "EruIgcrCfg" = "bit:or($EruIgcrCfg,bit:shl(1,14))"!][!//

[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Dsadc_ErsChannelConfiguration                           **
**                                                                            **
** Description      : Macro to generate the value to be configured for the    **
**                    an ERU ERS input channel in the EICR register           **
**                    corresponding to the input channel. It also generates   **
                      a 8 bit variable ,EruChConfigured, which contains       **
                      information on the ERS channels configured.(Bit 0 for   **
                      ERS Ch0, Bit 7 for ERS Ch7)                             **
*******************************************************************************/

[!MACRO "Dsadc_ErsChannelConfiguration","ErsChannelRef"= "",
"EruStatusFlagConfig"= "","EruErsInputPinConfig"= "","ErsChNo"="","ErsEicrCfg"="","EruChConfigured"=""!][!//
[!NOCODE!][!//

[!VAR "ErsChNo" = "num:i(substring-after($ErsChannelRef,'McuEruChannelInputLineConf_'))"!][!//
[!VAR "EruErsInputPinSelect" = "num:i(text:split($EruErsInputPinConfig,'_')[2])"!][!//
[!VAR "ErsEicrCfg" = "bit:shl($EruErsInputPinSelect,4)"!][!//
[!VAR "ErsEicrCfg" = "bit:or($ErsEicrCfg,bit:shl(1,10))"!][!//

[!VAR "EruStatusFlag" = "num:i(1)"!][!//
[!IF "$EruStatusFlagConfig = 'DSADC_ETL_RISING_EDGE'"!][!//
  [!VAR "EruStatusFlag" = "num:i(2)"!][!//
[!ENDIF!]
[!VAR "ErsEicrCfg" = "bit:or($ErsEicrCfg,bit:shl($EruStatusFlag,8))"!][!//

[!VAR "EruChConfigured" = "bit:or($EruChConfigured,bit:shl(1,$ErsChNo))"!][!//

[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!ENDIF!][!// IF "not(var:defined('DSADC_M'))
