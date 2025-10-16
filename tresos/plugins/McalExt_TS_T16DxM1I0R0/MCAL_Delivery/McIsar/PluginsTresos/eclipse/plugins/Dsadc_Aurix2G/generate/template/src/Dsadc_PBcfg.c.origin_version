[!/*****************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2021)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Dsadc_PBcfg.c                                                 **
**                                                                            **
**  VERSION   : 8.0.0                                                         **
**                                                                            **
**  DATE      : 2021-02-24                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Dsadc.bmd                                         **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={87CFE788-74EA-4b8a-BF8A-269CE700CB7A}]    **
**                                                                            **
**  DESCRIPTION  : Code template source file for Dsadc Driver                 **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Dsadc Driver                          **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*************************************************************************/!][!//
[!//
/*****************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2021)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Dsadc_PBcfg.c                                                 **
**                                                                            **
**  VERSION   : 8.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]            !!!IGNORE-LINE!!!             **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]              !!!IGNORE-LINE!!!             **
**                                                                            **
**  BSW MODULE DECRIPTION : Dsadc.bmd                                         **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION :  Dsadc configuration generated out of ECUC file             **
**                                                                            **
**  SPECIFICATION(S) : Specification of DSADC Driver                          **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                            Includes                                        **
*******************************************************************************/
/* Include module header file */
/* [cover parentID={C7D5952A-E79A-496d-A6D8-22C1661986B6}] */
#include "Dsadc.h"
[!NOCODE!]
  [!INCLUDE "Dsadc.m"!][!//
[!ENDNOCODE!][!//
[!//

[!NOCODE!][!//
  [!/*[cover parentID={B2DF571F-554E-4bb4-861B-C0EE7F89E062}]Dependent Module Checks[/cover] */!]
  [!IF "not(node:exists(as:modconf('Mcu')[1]))"!]
    [!ERROR!][!//
      [!WS"0"!]DSADC Code Generator: Mcu module is not added to the project.
    [!ENDERROR!][!//
  [!ENDIF!]

  [!VAR "VariantsConfigured" = "num:i(0)"!]
  [!SELECT "as:modconf('EcuC')[1]"!][!//
    [!IF "node:exists(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!][!//
      [!VAR "PredefinedVarName1" = "(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!]
      [!VAR "PredefinedVarName2" = "substring-after($PredefinedVarName1, "/")"!][!//
      [!VAR "PredefinedVarName3" = "substring-after($PredefinedVarName2, "/")"!][!//
      [!VAR "PredefinedVarName" = "substring-after($PredefinedVarName3, "/")"!][!//
      [!VAR "VariantsConfigured" = "num:i(1)"!]
    [!ENDIF!][!//
  [!ENDSELECT!]
[!ENDNOCODE!]


#define DSADC_START_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Dsadc_MemMap.h"
[!SELECT "as:modconf('Dsadc')[1]"!][!//
  [!VAR "SettingsIndex" = "num:i(0)"!][!//
  [!VAR "ChannelId" = "num:i(0)"!][!//
  [!VAR "DsadcChannelIdVar" = "num:i(0)"!][!//
  [!VAR "MaxChannels"= "num:i(count(DsadcConfigSet/*[1]/DsadcChannelConfiguration/*))"!][!//
  [!FOR "ChannelId" = "num:i(0)" TO "num:i($MaxChannels) - num:i(1)"!][!//
    [!SELECT "DsadcConfigSet/*[@index = $SettingsIndex]/DsadcChannelConfiguration/*[DsadcChannelId = num:i($ChannelId)]"!][!//
      [!VAR "DsadcChannelIdVar" = "num:i(DsadcChannelId)"!][!//
      [!VAR "BufferFullNotify" = "./DsadcBufferFullNotification"!][!//
      [!IF "($BufferFullNotify) != 'NULL_PTR'"!][!//
        [!IF "not(num:isnumber(./DsadcBufferFullNotification))"!][!//
          [!WS"0"!]/*Function declaration for Buffer full Notification for DSADC Channel Id [!"$DsadcChannelIdVar"!]*/
          [!WS"0"!]extern void [!"$BufferFullNotify"!](void);
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!VAR "NewResultNotify" = "./DsadcNewResultNotification"!][!//
      [!IF "($NewResultNotify) != 'NULL_PTR'"!][!//
        [!IF "not(num:isnumber(./DsadcNewResultNotification))"!][!//
          [!WS"0"!]/*Function declaration for New Result Notification for DSADC Channel Id [!"$DsadcChannelIdVar"!]*/
          [!WS"0"!]extern void [!"$NewResultNotify"!](void);
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!VAR "WindowCloseNotify" = "./DsadcWindowCloseNotification "!][!//
      [!IF "($WindowCloseNotify) != 'NULL_PTR'"!][!//
        [!IF "not(num:isnumber(./DsadcWindowCloseNotification))"!][!//
          [!WS"0"!]/*Function declaration for Window Close Notification for DSADC Channel Id [!"$DsadcChannelIdVar"!]*/
          [!WS"0"!]extern void [!"$WindowCloseNotify"!](void);
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDSELECT!][!//
  [!ENDFOR!][!//
[!ENDSELECT!][!//

[!SELECT "as:modconf('Dsadc')[1]"!][!//
  [!VAR "SettingsIndex" = "num:i(0)"!][!//
  [!VAR "ChannelId" = "num:i(0)"!][!//
  [!VAR "EruOguNodeSelect" = "num:i(0)"!][!//
  [!VAR "DsadcChannelIdVar" = "num:i(0)"!][!//
  [!VAR "EruChSelInOguConfig" = "num:i(0)"!][!//
  [!VAR "MaxChannels"= "num:i(count(DsadcConfigSet/*[1]/DsadcChannelConfiguration/*))"!][!//
  [!FOR "ChannelId" = "num:i(0)" TO "num:i($MaxChannels) - num:i(1)"!][!//
    [!SELECT "DsadcConfigSet/*[@index = $SettingsIndex]/DsadcChannelConfiguration/*[DsadcChannelId = num:i($ChannelId)]"!][!//
      [!VAR "DsadcChannelIdVar" = "num:i(DsadcChannelId)"!][!//
      [!SELECT "DsadcDemodulatorConfiguration/*[1]"!][!//
        [!IF "node:exists(./DsadcOguConfig/*[1])"!][!//
          [!WS"0"!]/*OGU Trigger Configuration for DSADC Channel Id [!"$DsadcChannelIdVar"!]*/
          [!VAR "OguChNo" = "num:i(0)"!][!//
          [!VAR "EruIgcrCfg" = "num:i(0)"!][!//
          [!WS"0"!][!CALL "Dsadc_PatternDetectionConfiguration","OguChannelRef"= "DsadcOguConfig/*[1]/DsadcEruOguRef",
                          "EruErsCh0PatternFlagEnableConfig"= "DsadcOguConfig/*[1]/DsadcEruErsCh0PatternFlagEnable",
                          "EruErsCh1PatternFlagEnableConfig"= "DsadcOguConfig/*[1]/DsadcEruErsCh1PatternFlagEnable",
                          "EruErsCh2PatternFlagEnableConfig"= "DsadcOguConfig/*[1]/DsadcEruErsCh2PatternFlagEnable",
                          "EruErsCh3PatternFlagEnableConfig"= "DsadcOguConfig/*[1]/DsadcEruErsCh3PatternFlagEnable",
                          "EruErsCh4PatternFlagEnableConfig"= "DsadcOguConfig/*[1]/DsadcEruErsCh4PatternFlagEnable",
                          "EruErsCh5PatternFlagEnableConfig"= "DsadcOguConfig/*[1]/DsadcEruErsCh5PatternFlagEnable",
                          "EruErsCh6PatternFlagEnableConfig"= "DsadcOguConfig/*[1]/DsadcEruErsCh6PatternFlagEnable",
                          "EruErsCh7PatternFlagEnableConfig"= "DsadcOguConfig/*[1]/DsadcEruErsCh7PatternFlagEnable",
                          "OguChNo"="$OguChNo",
                          "EruIgcrCfg"="$EruIgcrCfg",
                          "EruChSelInOguConfig"="$EruChSelInOguConfig"!][!//
          [!IF "$EruChSelInOguConfig = num:i(0)"!][!//
            [!ERROR!][!//
              [!WS"0"!]ERROR - DSADC Code Generator: None of the ERS input channels are configured for OGU output channel [!"$OguChNo"!]  as inputs to it for pattern detection.
            [!ENDERROR!][!//
          [!ENDIF!][!//
          [!WS"0"!][!/* [cover parentID={FC495E8B-7B85-4501-8D98-B149E791B841}]Error Check for ERU OGU selection for same node[/cover] */!][!//
          [!VAR "EruOguCurrentNode" = "bit:and(bit:and(num:i($OguChNo+4), num:i(7)), num:i($OguChNo))"!][!//
          [!VAR "EruNodeUsed" = "bit:shr(bit:and(bit:shl(1,$EruOguCurrentNode),$EruOguNodeSelect),$EruOguCurrentNode)"!][!//
          [!IF "$EruNodeUsed = num:i(0)"!][!//
            [!VAR "EruOguNodeSelect" = "bit:or(bit:shl(1,$EruOguCurrentNode),$EruOguNodeSelect)"!][!//
          [!WS"0"!][!ELSE!][!//
            [!ERROR!][!//
              [!WS"0"!]ERROR - DSADC Code Generator: OGU Channel of the same node is already used. Please select the different channel.
            [!ENDERROR!][!//
          [!WS"0"!][!ENDIF!][!//
          [!IF "$VariantsConfigured = num:i(1)"!][!//
            [!WS"0"!][!/* [cover parentID={B1B94293-CDD5-4d19-A622-5AF5A53D901E}]Dsadc_kOguTriggerConfig[_variant] [x][/cover] */!][!//
            [!WS"0"!]static const Dsadc_EruOguConfigType Dsadc_kOguTriggerConfig_[!"$PredefinedVarName"!] [!"$DsadcChannelIdVar"!] =
          [!ELSE!][!//
            [!WS"0"!][!/* [cover parentID={B1B94293-CDD5-4d19-A622-5AF5A53D901E}]Dsadc_kOguTriggerConfig[_variant] [x][/cover] */!][!//
            [!WS"0"!]static const Dsadc_EruOguConfigType Dsadc_kOguTriggerConfig[!"$DsadcChannelIdVar"!] =
          [!ENDIF!][!//
          [!WS"0"!]{
          [!WS"2"!]/*IGCR configuration for the given OGU channel*/
          [!WS"2"!][!"num:inttohex($EruIgcrCfg,4)"!]U,
          [!WS"2"!]/*OGU channel number */
          [!WS"2"!][!"num:inttohex($OguChNo,2)"!]U
          [!WS"0"!]};
        [!ENDIF!][!//
      [!ENDSELECT!][!//
    [!ENDSELECT!][!//
  [!ENDFOR!][!//
[!ENDSELECT!][!//

[!VAR "EruChConfigured" = "num:i(0)"!][!//
[!SELECT "as:modconf('Dsadc')[1]"!][!//
  [!IF "node:exists(./DsadcConfigSet/*[1]/DsadcErsEtlConfig/*[1])"!][!//
    [!WS"0"!]/*ERU input channels configuration for pattern detection of OGU channels*/
    [!IF "$VariantsConfigured = num:i(1)"!][!//
      [!WS"0"!][!/* [cover parentID={79BFF436-5AAF-4038-ABB3-8E79A9AD6042}]Dsadc_kErsInputConfiguration[_variant] [x][/cover] */!][!//
      [!WS"0"!]static const Dsadc_EruErsConfigType Dsadc_kErsInputConfiguration_[!"$PredefinedVarName"!] [DSADC_MAX_ERS_CHANNELS_CONFIGURED] =
    [!ELSE!][!//
      [!WS"0"!][!/* [cover parentID={79BFF436-5AAF-4038-ABB3-8E79A9AD6042}]Dsadc_kErsInputConfiguration[_variant] [x][/cover] */!][!//
      [!WS"0"!]static const Dsadc_EruErsConfigType Dsadc_kErsInputConfiguration  [DSADC_MAX_ERS_CHANNELS_CONFIGURED] =
    [!ENDIF!][!//
    [!WS"0"!]{
    [!VAR "SettingsIndex" = "num:i(0)"!][!//
    [!VAR "ErsEtlIndex" = "num:i(0)"!][!//
    [!VAR "MaxErsEtlInputChannels"= "num:i(count(DsadcConfigSet/*[1]/DsadcErsEtlConfig/*))"!][!//
    [!FOR "ErsEtlIndex" = "num:i(0)" TO "num:i($MaxErsEtlInputChannels) - num:i(1)"!][!//
      [!SELECT "DsadcConfigSet/*[@index = $SettingsIndex]/DsadcErsEtlConfig/*[@index = $ErsEtlIndex]"!][!//
        [!VAR "ErsChNo" = "num:i(0)"!][!//
        [!VAR "ErsEicrCfg" = "num:i(0)"!][!//
        [!WS"0"!][!CALL "Dsadc_ErsChannelConfiguration","ErsChannelRef"= "DsadcEruErsRef",
                        "EruStatusFlagConfig"= "DsadcEruStatusFlagConfig",
                        "EruErsInputPinConfig"= "DsadcEruErsInputPin",
                        "ErsChNo"="$ErsChNo",
                        "ErsEicrCfg"="$ErsEicrCfg",
                        "EruChConfigured"="$EruChConfigured"!][!//
        [!WS"2"!]/*Configuration of ERS Input channel [!"$ErsChNo"!]*/
        [!WS"2"!]{
        [!WS"4"!]/*EICR configuration for the given ERS input channel*/
        [!WS"4"!][!"num:inttohex($ErsEicrCfg,4)"!]U,
        [!WS"4"!]/*ERS channel number*/
        [!WS"4"!][!"num:inttohex($ErsChNo,2)"!]U
        [!WS"2"!]}[!IF "$ErsEtlIndex < (num:i($MaxErsEtlInputChannels) - num:i(1))"!],[!ENDIF!]

        [!AUTOSPACING!]
      [!ENDSELECT!][!//
    [!ENDFOR!][!//
    [!WS"0"!]};
  [!ENDIF!][!//
[!ENDSELECT!][!//

[!IF "$EruChConfigured != $EruChSelInOguConfig"!][!//
  [!VAR "ErsEtlInputIndex" = "num:i(0)"!][!//
  [!FOR "ErsEtlInputIndex" = "num:i(0)" TO "num:i(8) - num:i(1)"!][!//
    [!VAR "LocalEruChConfigured" = "bit:and($EruChConfigured,bit:shl(1,$ErsEtlInputIndex))"!][!//
    [!VAR "LocalEruChSelInOguConfig" = "bit:and($EruChSelInOguConfig,bit:shl(1,$ErsEtlInputIndex))"!][!//
    [!IF "$LocalEruChConfigured != $LocalEruChSelInOguConfig"!][!//
      [!IF "$LocalEruChConfigured != num:i(0)"!][!//
        [!ERROR!][!//
          [!WS"0"!]ERROR - DSADC Code Generator: ERU ERS input channel [!"$ErsEtlInputIndex"!] which is configured in DsadcErsEtlConfig is not used for pattern detection in any of the OGU channels configured.
        [!ENDERROR!][!//
      [!ELSE!]
        [!ERROR!][!//
          [!WS"0"!]ERROR - DSADC Code Generator: ERU ERS input channel [!"$ErsEtlInputIndex"!] is selected to be used in pattern detection in one of the OGU channels, but it not configured in the DsadcErsEtlConfig container
        [!ENDERROR!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
[!ENDIF!][!//

/*DSADC channels configurations*/
[!IF "$VariantsConfigured = num:i(1)"!][!//
  [!WS"0"!][!/* [cover parentID={118378FE-C2F8-47e7-961E-D7325BA73575}]Dsadc_kChannelConfiguration[_variant] [x][/cover] */!][!//
  [!WS"0"!]static const Dsadc_ChannelConfigType Dsadc_kChannelConfiguration_[!"$PredefinedVarName"!] [DSADC_MAX_CHANNELS_CONFIGURED] =
[!ELSE!][!//
  [!WS"0"!][!/* [cover parentID={118378FE-C2F8-47e7-961E-D7325BA73575}]Dsadc_kChannelConfiguration[_variant] [x][/cover] */!][!//
  [!WS"0"!]static const Dsadc_ChannelConfigType Dsadc_kChannelConfiguration  [DSADC_MAX_CHANNELS_CONFIGURED] =
[!ENDIF!][!//
{
[!SELECT "as:modconf('Dsadc')[1]"!][!//
  [!VAR "SettingsIndex" = "num:i(0)"!][!//
  [!VAR "ChannelId" = "num:i(0)"!][!//
  [!VAR "MaxChannels"= "num:i(count(DsadcConfigSet/*[1]/DsadcChannelConfiguration/*))"!][!//
  [!FOR "ChannelId" = "num:i(0)" TO "num:i($MaxChannels) - num:i(1)"!][!//
    [!SELECT "DsadcConfigSet/*[@index = $SettingsIndex]/DsadcChannelConfiguration/*[DsadcChannelId = num:i($ChannelId)]"!][!//
      [!NOCODE!][!//
        [!// DSADC HW channel associated with channel ID
        [!VAR "DSADCHwCh"= "DsadcHwChannelNum"!][!//
        [!VAR "EdsadcHwCh" = "num:i(text:split($DSADCHwCh,'_')[3])"!][!//
        [!// DSADC SW Access Mode
        [!VAR "DsadcSwAccessMode"= "DsadcAccessMode"!][!//
        [!// DSADC Timestamp
        [!VAR "Dsadctimestamp"= "DsadcTimestampFeature"!][!//
        [!// DSADC Timestamp Trigger mode
        [!IF "($Dsadctimestamp = 'DSADC_TIMESTAMP_ENABLED')"!][!//
          [!VAR "DsadcTimestampTriggerMod"= "DsadcDemodulatorConfiguration/*[1]/DsadcTimestampConfiguration/*[1]/DsadcTimestampTriggerMode"!][!//
        [!ELSE!][!//
          [!VAR "DsadcTimestampTriggerMod"= "'DSADC_NO_TIMESTAMP_TRIGGER'"!][!//
        [!ENDIF!]
        [!// DSADC Trigger Mode
        [!VAR "DsadcTrigMode"= "DsadcTriggerMode"!][!//
        [!// DSADC Gate Active Level
        [!VAR "DsadcGateActLevel"= "DsadcGateActiveLevel"!][!//
        [!// DSADC Buffer Full Notification
        [!VAR "DsadcBuffFullNotif"= "DsadcBufferFullNotification"!][!//
        [!// DSADC New Result Notification
        [!VAR "DsadcNewResNotif"= "DsadcNewResultNotification"!][!//
        [!// DSADC Window Close Notification
        [!VAR "DsadcWindowCloseNotif"= "DsadcWindowCloseNotification"!][!//
        [!// DSADC Multiplexer Common Mode voltage configuration
        [!VAR "CMVRegConfig" = "num:i(0)"!][!//
        [!CALL "Dsadc_ConfigureCMVReg","CMVEnableConfig"= "DsadcCommonModeVoltConfig/DsadcCommonModeVoltageEnable",
               "CMVSelectConfig"= "DsadcCommonModeVoltConfig/DsadcCommonModeVoltageSelect",
               "MuxAPositivEnableConfig"= "DsadcCommonModeVoltConfig/DsadcComModeVoltPosAEnable","MuxBPositivEnableConfig"= "DsadcCommonModeVoltConfig/DsadcComModeVoltPosBEnable",
               "MuxCPositivEnableConfig"= "DsadcCommonModeVoltConfig/DsadcComModeVoltPosCEnable","MuxDPositivEnableConfig"= "DsadcCommonModeVoltConfig/DsadcComModeVoltPosDEnable",
               "MuxANegativEnableConfig"= "DsadcCommonModeVoltConfig/DsadcComModeVoltNegAEnable","MuxBNegativEnableConfig"= "DsadcCommonModeVoltConfig/DsadcComModeVoltNegBEnable",
               "MuxCNegativEnableConfig"= "DsadcCommonModeVoltConfig/DsadcComModeVoltNegCEnable","MuxDNegativEnableConfig"= "DsadcCommonModeVoltConfig/DsadcComModeVoltNegDEnable",
               "CMVRegConfig"="$CMVRegConfig"!][!//
        [!// DSADC channel Modulator configuration
        [!VAR "ModulatorRegConfig" = "num:i(0)"!][!//
        [!CALL "Dsadc_ConfigureChModulator","AnalogClockSyncDelayConfig"= "DsadcModulatorConfiguration/DsadcAnalogClockSyncDelay",
               "ClockDividerConfig"= "DsadcModulatorConfiguration/DsadcClockDivider",
               "DitherEnableConfig"= "DsadcModulatorConfiguration/DsadcDitheringEnable",
               "IntRstEnableConfig"= "DsadcModulatorConfiguration/DsadcIntegratorResetEnable",
               "InputGainConfig"= "DsadcModulatorConfiguration/DsadcInputGain",
               "InputMuxActionModeConfig"= "DsadcModulatorConfiguration/DsadcInputMuxActionMode",
               "InputMuxControlModeConfig"= "DsadcModulatorConfiguration/DsadcInputMuxControlMode",
               "NegInputLineConfig"= "DsadcModulatorConfiguration/DsadcNegativeInputLine",
               "PosInputLineConfig"= "DsadcModulatorConfiguration/DsadcPositiveInputLine",
               "InputPinSelectionConfig"= "DsadcModulatorConfiguration/DsadcInputPinSelection",
               "DsadcTriggerModeConfig"= "$DsadcTrigMode",
               "ModulatorRegConfig"="$ModulatorRegConfig"!][!//
        [!// DSADC Filter configuration
        [!VAR "FilterChainConfig" = "num:i(0)"!][!//
        [!CALL "Dsadc_ConfigureFilterChain","FIR0EnableConfig"= "DsadcFilterConfiguration/DsadcFIR0FilterEnable",
               "FIR1EnableConfig"= "DsadcFilterConfiguration/DsadcFIR1FilterEnable",
               "OvershootCompensationEnConfig"= "DsadcFilterConfiguration/DsadcOvershootCompensationEn",
               "FIR1DecimationEnableConfig"= "DsadcFilterConfiguration/DsadcFIR1FilterDecimationEnable",
               "PreFilterEnableConfig"= "DsadcFilterConfiguration/DsadcPreFilterEnable",
               "AltServiceReqGenConfig"= "DsadcFilterConfiguration/DsadcAlternateServiceReq",
               "OffsetCompFilterEnableConfig"= "DsadcFilterConfiguration/DsadcOffsetCompFilterEnable",
               "OffsetCompValueProtectConfig"= "DsadcFilterConfiguration/DsadcOffsetCompValueProtect",
               "ComparatorEventSelectConfig"= "DsadcFilterConfiguration/DsadcComparatorConfiguration/DsadcComparatorEventSelect",
               "FilterChainConfig"="$FilterChainConfig"!][!//
        [!// DSADC CIC Filter configuration
        [!VAR "CICFilterConfig" = "num:i(0)"!][!//
        [!CALL "Dsadc_ConfigureCICFilter","CICFilterDecimationFactorConfig"= "DsadcFilterConfiguration/DsadcCICFilterDecimationFactor",
               "CICFilterStartValueConfig"= "DsadcFilterConfiguration/DsadcCICFilterStartValue",
               "CICFilterConfig"="$CICFilterConfig"!][!//
        [!// DSADC Aux CIC Filter configuration
        [!VAR "AuxCICFilterConfig" = "num:i(0)"!][!//
        [!CALL "Dsadc_ConfigureAuxCICFilter","AuxCICFilterEnableConfig"= "DsadcFilterConfiguration/DsadcAuxFilterConfig/DsadcAuxCicFilterEnable",
               "AuxCICFilterDecimationFactorConfig"= "DsadcFilterConfiguration/DsadcAuxFilterConfig/DsadcAuxFilterCicDecimationFactor",
               "AuxCICFilterConfig"="$AuxCICFilterConfig"!][!//
        [!// DSADC Offset Compensation value
        [!VAR "OffsetCompensationRegConfig" = "num:i(0)"!][!//
        [!CALL "Dsadc_ConfigureOffsetCompensationReg","OffsetCompensationValueConfig"= "DsadcFilterConfiguration/DsadcOffsetCompValue",
               "OffsetCompensationRegConfig"="$OffsetCompensationRegConfig"!][!//
        [!// DSADC Gain Correction register configuration
        [!VAR "GainCorrConfig" = "num:i(0)"!][!//
        [!CALL "Dsadc_ConfigureGainCorrection","CICFilterOutputShiftPosConfig"= "DsadcFilterConfiguration/DsadcGainCalibConfig/DsadcGainCorrConfig/DsadcCICFilterOutputShiftPos",
               "GainCorrMulFactorConfig"= "DsadcFilterConfiguration/DsadcGainCalibConfig/DsadcGainCorrConfig/DsadcGainCorrMulFactor",
               "GainCorrConfig"="$GainCorrConfig"!][!//
        [!// DSADC Gain Calibration and control register configuration
        [!VAR "GainCalibConfig" = "num:i(0)"!][!//
        [!VAR "GainCtrlConfig" = "num:i(0)"!][!//
        [!CALL "Dsadc_ConfigureGainCalibration",
               "CICFilterOutputShiftPosConfig"= "DsadcFilterConfiguration/DsadcGainCalibConfig/DsadcCalibAlgoConfig/DsadcCalibCICFilterOutputShiftPos",
               "GainCorrMulFactorConfig"= "DsadcFilterConfiguration/DsadcGainCalibConfig/DsadcCalibAlgoConfig/DsadcCalibGainCorrMulFactor",
               "CICDecimationRateConfig"= "DsadcFilterConfiguration/DsadcGainCalibConfig/DsadcCalibAlgoConfig/DsadcCICDecimationRate",
               "GainCalibMulFactorConfig"= "DsadcFilterConfiguration/DsadcGainCalibConfig/DsadcCalibAlgoConfig/DsadcGainCalibMulFactor",
               "CalibAlgoTargetValueConfig"= "DsadcFilterConfiguration/DsadcGainCalibConfig/DsadcCalibAlgoConfig/DsadcCalibAlgoTargetValue",
               "GainCalibConfig"="$GainCalibConfig","GainCtrlConfig"="$GainCtrlConfig"!][!//
        [!// DSADC Limit Checking boundary register configuration
        [!VAR "LimitCheckConfig" = "num:i(0)"!][!//
        [!CALL "Dsadc_LimitCheck","LowerBoundaryValueConfig"= "DsadcFilterConfiguration/DsadcComparatorConfiguration/DsadcLowerBoundaryValue",
               "UpperBoundaryValueConfig"= "DsadcFilterConfiguration/DsadcComparatorConfiguration/DsadcUpperBoundaryValue",
               "LimitCheckConfig"="$LimitCheckConfig"!][!//
        [!// DSADC OverShoot Configuration register configuration
        [!VAR "OverShootConfig" = "num:i(0)"!][!//
        [!VAR "MaxOvershootConfig" = "num:i(count(DsadcFilterConfiguration/DsadcOvershootCompenConfig/*))"!]
        [!IF "$MaxOvershootConfig > num:i(0)"!]
          [!CALL "Dsadc_OvershootConfig","SlewRateFilterStrength"= "DsadcFilterConfiguration/DsadcOvershootCompenConfig/*[1]/DsadcSlewRateFilterStrength",
                 "SlewRateFilterRunTime"= "DsadcFilterConfiguration/DsadcOvershootCompenConfig/*[1]/DsadcSlewRateFilterRunTime",
                 "StepDetectionMode"= "DsadcFilterConfiguration/DsadcOvershootCompenConfig/*[1]/DsadcStepDetectionMode",
                 "StepDetectionThreshold"= "DsadcFilterConfiguration/DsadcOvershootCompenConfig/*[1]/DsadcStepDetectionThreshold",
                 "OverShootConfig" = "$OverShootConfig"!][!//
        [!ENDIF!]
        [!// DSADC Demodulator register configuration
        [!VAR "DemodulatorRegConfig" = "num:i(0)"!][!//
        [!CALL "Dsadc_DemodulatorConfig","IntegratorTriggerModeConfig"= "DsadcDemodulatorConfiguration/*[1]/DsadcIntegratorTriggerMode",
               "TriggerSelectConfig"= "DsadcDemodulatorConfiguration/*[1]/DsadcTriggerSelect",
               "ResultDisplayModeConfig"= "DsadcDemodulatorConfiguration/*[1]/DsadcResultDisplayMode",
               "TimestampModeEnableConfig"= "$Dsadctimestamp",
               "TimestampTriggerModeConfig" = "$DsadcTimestampTriggerMod",
               "TriggerModeConfig"= "$DsadcTrigMode",
               "GateActiveLevelConfig"= "$DsadcGateActLevel",
               "DemodulatorRegConfig"="$DemodulatorRegConfig"!][!//
        [!// DSADC Result FIFO Control register configuration
        [!VAR "DsadcFifoCtrlRegConfig" = "num:i(0)"!][!//
        [!CALL "Dsadc_FifoConfig","TimestampModeEnableConfig"= "$Dsadctimestamp",
               "TriggerModeConfig"= "$DsadcTrigMode",
               "TimestampTriggerModeConfig" = "$DsadcTimestampTriggerMod",
               "DsadcFifoCtrlRegConfig"="$DsadcFifoCtrlRegConfig"!][!//
        [!// DSADC CG synchronization and rectifier registers configuration
        [!VAR "CGSyncRegConfig" = "num:i(0)"!][!//
        [!VAR "RectifierRegConfig" = "num:i(0)"!][!//
        [!IF "node:exists(./DsadcRectificationConfiguration/*[1])"!][!//
          [!CALL "Dsadc_ResolverConfig","RectificationEnableConfig"= "DsadcRectificationConfiguration/*[1]/DsadcRectificationEnable",
                 "SignSignalSourceConfig"= "DsadcRectificationConfiguration/*[1]/DsadcSignSignalSource",
                 "SignSignalChannelConfig"= "DsadcRectificationConfiguration/*[1]/DsadcSignSignalChannel",
                 "PosSignDelayValueConfig"= "DsadcRectificationConfiguration/*[1]/DsadcPosSignDelayValue",
                 "NegSignDelayValueConfig"= "DsadcRectificationConfiguration/*[1]/DsadcNegSignDelayValue",
                 "CGSyncRegConfig"="$CGSyncRegConfig","RectifierRegConfig"="$RectifierRegConfig"!][!//
        [!ENDIF!]
        [!SELECT "DsadcDemodulatorConfiguration/*[1]"!][!//
          [!// DSADC Timestamp counter register configuration
          [!VAR "TimestampCntRegConfig" = "num:i(0)"!][!//
          [!IF "node:exists(./DsadcTimestampConfiguration/*[1])"!][!//
          [!CALL "Dsadc_TimestampCntConfig","TimestampCounterClockSelConfig"= "DsadcTimestampConfiguration/*[1]/DsadcTimestampCounterClockSel",
                 "InputMuxSetCopyEnableConfig"= "DsadcTimestampConfiguration/*[1]/DsadcInputMuxSetCopyEnable",
                 "TimestampFeatureConfig"= "$Dsadctimestamp",
                 "TimestampCntRegConfig"="$TimestampCntRegConfig"!][!//
          [!ENDIF!]
          [!// DSADC Integrator register Configuration
          [!VAR "IntegratorRegConfig" = "num:i(0)"!][!//
          [!IF "node:exists(./DsadcIntegratorConfiguration/*[1])"!][!//
          [!CALL "Dsadc_IntegratorConfig","DiscardCountConfig"= "DsadcIntegratorConfiguration/*[1]/DsadcDiscardCount",
                 "IntegrationCountConfig"= "DsadcIntegratorConfiguration/*[1]/DsadcIntegrationCount",
                 "IntegrationTriggerConfig"= "$DsadcTrigMode",
                 "IntegratorRegConfig"="$IntegratorRegConfig"!][!//
          [!ENDIF!]
          [!// DSADC Trigger source 
          [!VAR "DsadcTriggerSource" = "'DSADC_TRIGGER_NONE'"!][!//]
          [!IF "contains(DsadcTriggerSelect,'ERU')"!][!//
            [!VAR "DsadcTriggerSource" = "'DSADC_TRIGGER_ERU'"!][!//
          [!ELSEIF "contains(DsadcTriggerSelect,'GTM')"!][!//!][!//
            [!VAR "DsadcTriggerSource" = "'DSADC_TRIGGER_GTM'"!][!//
          [!ENDIF!]
          [!// DSADC Channel Interrupt Mode Configuration
          [!VAR "DsadcChannelIntMode" = "num:i(0)"!][!//
          [!CALL "Dsadc_ChannelIntModeConfig","TriggerModeConfig"= "$DsadcTrigMode",
                 "TimestampTriggerModeConfig" = "$DsadcTimestampTriggerMod",
                 "GateActiveLevelConfig"= "$DsadcGateActLevel",
                 "TimestampFeatureConfig"= "$Dsadctimestamp",
                 "DsadcChannelIntMode"="$DsadcChannelIntMode"!][!//
        [!ENDSELECT!][!//
      [!ENDNOCODE!][!//
      [!WS"2"!]/*Configuration of DSADC Channel Id [!"DsadcChannelId"!]*/
      [!WS"2"!]{
      [!WS"4"!]/*Address for the OGU trigger configuration structure*/
      [!IF "node:exists(./DsadcDemodulatorConfiguration/*[1]/DsadcOguConfig/*[1])"!][!//
        [!IF "$VariantsConfigured = num:i(1)"!][!//
          [!WS"4"!]&Dsadc_kOguTriggerConfig_[!"$PredefinedVarName"!][!"DsadcChannelId"!],
        [!ELSE!]
        [!WS"4"!]&Dsadc_kOguTriggerConfig[!"DsadcChannelId"!],
      [!ENDIF!]
      [!ELSE!]
      [!WS"4"!]NULL_PTR,
      [!ENDIF!]
      [!WS"4"!]/* Modulator Configuration Register */
      [!WS"4"!][!"num:inttohex($ModulatorRegConfig,8)"!]U,
      [!WS"4"!]/* Common Mode Voltage Configuration Register */
      [!WS"4"!][!"num:inttohex($CMVRegConfig,8)"!]U,
      [!WS"4"!]/* Demodulator Configuration Register */
      [!WS"4"!][!"num:inttohex($DemodulatorRegConfig,8)"!]U,
      [!WS"4"!]/* Filter Configuration Register */
      [!WS"4"!][!"num:inttohex($FilterChainConfig,8)"!]U,
      [!WS"4"!]/* CIC Filter Configuration Register */
      [!WS"4"!][!"num:inttohex($CICFilterConfig,8)"!]U,
      [!WS"4"!]/* AUX CIC Filter Configuration Register */
      [!WS"4"!][!"num:inttohex($AuxCICFilterConfig,8)"!]U,
      [!WS"4"!]/* Timestamp counter Register */
      [!WS"4"!][!"num:inttohex($TimestampCntRegConfig,8)"!]U,
      [!WS"4"!]/* Integrator Window Control Register */
      [!WS"4"!][!"num:inttohex($IntegratorRegConfig,8)"!]U,
      [!WS"4"!]/* Result FIFO Control Register */
      [!WS"4"!][!"num:inttohex($DsadcFifoCtrlRegConfig,8)"!]U,
      [!WS"4"!]/* Offset Compensation Register */
      [!WS"4"!][!"num:inttohex($OffsetCompensationRegConfig,8)"!]U,
      [!WS"4"!]/* Gain Calibration Register */
      [!WS"4"!][!"num:inttohex($GainCalibConfig,8)"!]U,
      [!WS"4"!]/* Gain Control Register */
      [!WS"4"!][!"num:inttohex($GainCtrlConfig,8)"!]U,
      [!WS"4"!]/* Gain Correction Register */
      [!WS"4"!][!"num:inttohex($GainCorrConfig,8)"!]U,
      [!WS"4"!]/* Limit Checking boundary configuration Register */
      [!WS"4"!][!"num:inttohex($LimitCheckConfig,8)"!]U,
      [!WS"4"!]/* Overshoot compensation configuration Register */
      [!WS"4"!][!"num:inttohex($OverShootConfig,8)"!]U,
      [!WS"4"!]/* Carrier Generator Synchronization Register */
      [!WS"4"!][!"num:inttohex($CGSyncRegConfig,8)"!]U,
      [!WS"4"!]/* Rectification Configuration Register */
      [!WS"4"!][!"num:inttohex($RectifierRegConfig,8)"!]U,
      [!WS"4"!]/* DSADC Channel number */
      [!WS"4"!][!"num:inttohex($EdsadcHwCh,2)"!]U,
      [!WS"4"!]/* DSADC Channel Access Mode */
      [!WS"4"!][!"$DsadcSwAccessMode"!],
      [!WS"4"!]/* DSADC Timestamp*/
      [!WS"4"!][!"$Dsadctimestamp"!],
      [!WS"4"!]/* DSADC TimestampTriggerMode*/
      [!WS"4"!][!"$DsadcTimestampTriggerMod"!],
      [!WS"4"!]/* DSADC Channel Trigger Mode */
      [!WS"4"!][!"$DsadcTrigMode"!],
      [!WS"4"!]/* DSADC Channel Trigger Source */
      [!WS"4"!][!"$DsadcTriggerSource"!],
      [!WS"4"!]/* DSADC Channel DsadcGateActiveLevel */
      [!WS"4"!][!"$DsadcGateActLevel"!],
      [!WS"4"!]/* DSADC Channel Interrupt Mode*/
      [!WS"4"!][!"num:inttohex($DsadcChannelIntMode,2)"!]U,
      [!WS"4"!]/* DSADC Buffer Full Notification */
      [!WS"4"!][!"$DsadcBuffFullNotif"!],
      [!WS"4"!]/* DSADC New Result Notification */
      [!WS"4"!][!"$DsadcNewResNotif"!],
      [!WS"4"!]/* DSADC Window Close Notification  */
      [!WS"4"!][!"$DsadcWindowCloseNotif"!]
      [!WS"2"!]}[!IF "$ChannelId != $MaxChannels -1"!],[!ENDIF!]

      [!AUTOSPACING!]
    [!ENDSELECT!][!//
  [!ENDFOR!][!//
[!ENDSELECT!][!//
};

/* Configuration Root for DsadcConfigSet*/


[!IF "$VariantsConfigured = num:i(1)"!][!//
  [!WS"0"!][!/* [cover parentID={B38FA37E-BB5B-4f03-BF99-A465D5D41ECB}]Dsadc_Config[_variant][/cover] */!][!//
  [!WS"0"!]const Dsadc_ConfigType Dsadc_Config_[!"$PredefinedVarName"!] =
[!ELSE!][!//
  [!WS"0"!][!/* [cover parentID={B38FA37E-BB5B-4f03-BF99-A465D5D41ECB}]Dsadc_Config[_variant][/cover] */!][!//
  [!WS"0"!]const Dsadc_ConfigType Dsadc_Config =
[!ENDIF!][!//
{
[!SELECT "as:modconf('Dsadc')[1]"!][!//
  [!VAR "SettingsIndex" = "num:i(0)"!][!//
  [!SELECT "DsadcConfigSet/*[@index = $SettingsIndex]"!][!//
    [!NOCODE!][!//
      [!// DSADC CLC register calculation
      [!VAR "DsadcClcConfig" = "num:i(0)"!][!//
      [!CALL "Dsadc_ConfigureClcReg","SleepModeConfig"= "DsadcGlobalConfiguration/DsadcSleepMode",
             "DsadcClcConfig"="$DsadcClcConfig"!][!//
      [!// DSADc Carrier Generator waveform Selection
      [!VAR "DsadcCgWaveform" = "DsadcCarrierGeneratorConfiguration/DsadcCarrierSignalType"!]
      [!// DSADC Global Configuration register calculation
      [!VAR "DsadcGlobalConfig" = "num:i(0)"!][!//
      [!CALL "Dsadc_ConfigureGlobalCfgReg","DitherTrimValueConfig"= "DsadcGlobalConfiguration/DsadcDitheringTrimValue",
             "SyncClockGenConfig"= "DsadcGlobalConfiguration/DsadcSyncClockGen","SupVoltValueConfig"= "DsadcGlobalConfiguration/DsadcSupplyVoltageLevel",
             "DsadcGlobalConfig"="$DsadcGlobalConfig"!][!//
      [!// DSADC Carrier Generator Configuration register calculation
      [!VAR "CarrierGenConfig" = "num:i(0)"!][!//
      [!CALL "Dsadc_ConfigureCGReg","BitReverseConfig"= "DsadcCarrierGeneratorConfiguration/DsadcPwmGenerationMode",
             "CarrierSignalPolConfig"= "DsadcCarrierGeneratorConfiguration/DsadcCarrierSignalPolarity",
             "CGFreqDivConfig"= "DsadcCarrierGeneratorConfiguration/DsadcCarrierFrequencyClockDiv",
             "CarrierGenConfig"="$CarrierGenConfig"!][!//
    [!ENDNOCODE!][!//
    [!WS"2"!]/* pointer to DSDAC channel configuration */
    [!IF "$VariantsConfigured = num:i(1)"!][!//
      [!WS"2"!]&Dsadc_kChannelConfiguration_[!"$PredefinedVarName"!][0],
    [!ELSE!][!//
      [!WS"2"!]&Dsadc_kChannelConfiguration[0],
    [!ENDIF!][!//
    [!WS"2"!]/* pointer to ERU input channel configuration */
    [!IF "node:exists(./DsadcErsEtlConfig/*[1])"!][!//
      [!IF "$VariantsConfigured = num:i(1)"!][!//
        [!WS"2"!]&Dsadc_kErsInputConfiguration_[!"$PredefinedVarName"!][0],
      [!ELSE!][!//
        [!WS"2"!]&Dsadc_kErsInputConfiguration[0],
      [!ENDIF!][!//
    [!ELSE!][!//
      NULL_PTR,
    [!ENDIF!][!//
    [!WS"2"!]/* Contents of DSADC Clock control register, CLC */
    [!WS"2"!][!"num:inttohex($DsadcClcConfig,8)"!]U,
    [!WS"2"!]/* Contents DSADC Global configuration register GLOBCFG */
    [!WS"2"!][!"num:inttohex($DsadcGlobalConfig,8)"!]U,
    [!WS"2"!]/* Contents DSADC Carrier generator configuration register CGCFG */
    [!WS"2"!][!"num:inttohex($CarrierGenConfig,8)"!]U,
    [!WS"2"!]/*Carrier Generator Waveform*/
    [!WS"2"!][!"$DsadcCgWaveform"!]
    [!AUTOSPACING!][!//
  [!ENDSELECT!][!//
[!ENDSELECT!][!//
};

#define DSADC_STOP_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration of notification function
  before MemMap inclusion It complies to Autosar guidelines. */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Dsadc_MemMap.h"

