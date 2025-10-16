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
**  FILENAME  : I2c_PBcfg.c                                                   **
**                                                                            **
**  VERSION   : 9.0.0                                                         **
**                                                                            **
**  DATE      : 2020-05-11                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : I2c.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Code template source file for I2c Driver                   **
**                                                                            **
**  SPECIFICATION(S) : Specification of I2c Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*************************************************************************/!]
[!//
/*****************************************************************************
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
**  FILENAME  : I2c_PBcfg.c                                                   **
**                                                                            **
**  VERSION   : 9.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]    !!!IGNORE-LINE!!!                 **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]    !!!IGNORE-LINE!!!                     **
**                                                                            **
**  BSW MODULE DECRIPTION : i2c.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION : This file contains                                          **
**                Code template for I2c_PBcfg.c file                          **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: No                                       **
**                                                                            **
*******************************************************************************/
[!//
/*******************************************************************************
**                                                                            **
**  TRACEBILITY :                                                             **
**                                                                            **
*******************************************************************************/
[!NOCODE!][!//
  [!IF "not(node:exists(as:modconf('ResourceM')[1]))"!]
    [!ERROR!][!//
      I2C needs ResourceM module.
    [!ENDERROR!][!//
  [!ENDIF!]

  [!IF "not(node:exists(as:modconf('Mcu')[1]))"!]
    [!ERROR!][!//
      I2C needs MCU module.
    [!ENDERROR!][!//
  [!ENDIF!]
[!ENDNOCODE!][!//

[!//
[!VAR "VariantsConfigured" = "num:i(0)"!]
[!SELECT "as:modconf('EcuC')"!][!//
  [!IF "node:exists(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!][!//
    [!VAR "PredefinedVarName1" = "(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!]
    [!VAR "PredefinedVarName2" = "substring-after($PredefinedVarName1, "/")"!][!//
    [!VAR "PredefinedVarName3" = "substring-after($PredefinedVarName2, "/")"!][!//
    [!VAR "PredefinedVarName" = "substring-after($PredefinedVarName3, "/")"!][!//
    [!VAR "VariantsConfigured" = "num:i(1)"!]
  [!ENDIF!][!//
[!ENDSELECT!]


[!AUTOSPACING!]
[!//
[!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!]
[!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!]
[!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!]
[!//
[!VAR "I2cChannelConfigurationName" = "'I2cConfigSet/I2cChannelConfiguration'"!]
[!//
[!SELECT "as:modconf('I2c')[1]"!]
  [!VAR "TotalConfig" = "num:i(count(node:ref($I2cChannelConfigurationName)/*))"!]
[!ENDSELECT!]
[!//
[!//
[!IF "node:refexists(I2cGeneral/I2cSystemClock) = 'true'"!][!//
  [!VAR "FI2C_Clk" = "num:i(node:ref(I2cGeneral/I2cSystemClock)/McuClockReferencePointFrequency)"!]
[!ELSE!]
  [!ERROR!][!//
    Clock configuration is incomplete.
  [!ENDERROR!][!//
[!ENDIF!]

[!//
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Include I2C Module File */
#include "I2c.h"

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
[!INDENT "0"!][!//
[!LOOP "I2cConfigSet/I2cChannelConfiguration/*"!][!//
  [!IF "I2cAsyncNotification = 'true'"!][!//
    [!IF "node:exists(I2cPacketEndNotification)"!][!//
      [!VAR "Notify" = "I2cPacketEndNotification"!][!//
        [!IF "$Notify = 'NULL_PTR' or num:isnumber($Notify) = 'true'"!][!//
        [!ELSE!][!//
          /* Notification Function */
          extern void [!"$Notify"!](I2c_ErrorType ErrorId); 
        [!ENDIF!][!//
    [!ELSE!][!//
      [!VAR "Notify" = "'NULL_PTR'"!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDINDENT!]

#define I2C_START_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.
*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "I2c_MemMap.h"
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('I2c')[1]"!][!//
[!INDENT "0"!][!//
  [!IF "$VariantsConfigured = num:i(1)"!][!//
    static const I2c_ChannelConfigType  I2c_ChannelConfig_[!"$PredefinedVarName"!][I2C_MAX_CHANNELS] =
  [!ELSE!][!//
    static const I2c_ChannelConfigType I2c_ChannelConfig[I2C_MAX_CHANNELS] =
  [!ENDIF!][!//
  {
  [!INDENT "2"!][!//
    [!LOOP "I2cConfigSet/I2cChannelConfiguration/*"!][!//
      [!NOCODE!][!//
        [!VAR "HwUnit" = "I2cHwUnit"!][!//
        [!VAR "HwUnitNumber" = "text:split($HwUnit, '_')[position() = 2]"!][!//
      [!ENDNOCODE!][!//
      {
      [!INDENT "4"!][!//
        /* Hw Unit */
        [!"num:inttohex(num:i($HwUnitNumber ))"!]U,
        [!//
        [!//
        [!VAR "AdrValue" = "num:i(0)"!][!//
        [!VAR "AdddressCfgValue_Adr" = "$AdrValue"!][!//
        [!//
        [!VAR "TBAM_Cfg" = "node:value(I2cAddressingMode)"!][!//
        [!IF "$TBAM_Cfg = 'I2C_10_BIT_ADDRESSING'"!][!//
          [!VAR "TBAM_Value" = "num:i(1)"!][!//
        [!ELSE!][!//
          [!VAR "TBAM_Value" = "num:i(0)"!][!//
        [!ENDIF!][!//
        [!VAR "AdddressCfgValue_TBAM" = "bit:shl( $TBAM_Value, 16)"!][!//
        [!//
        [!VAR "GCE_Value" = "num:i(0)"!][!//
        [!VAR "AdddressCfgValue_GCE" = "bit:shl( $GCE_Value, 17)"!][!//
        [!//
        [!VAR "MCE_Cfg" = "node:value(I2cSpeed)"!][!//
        [!IF "$MCE_Cfg = 'HIGH_SPEED_MODE'"!][!//
          [!VAR "MCE_Value" = "num:i(1)"!][!//
        [!ELSE!][!//
          [!VAR "MCE_Value" = "num:i(0)"!][!//
        [!ENDIF!][!//
        [!VAR "AdddressCfgValue_MCE" = "bit:shl( $MCE_Value, 18)"!][!//
        [!//
        [!VAR "MnS_Value" = "num:i(1)"!][!//
        [!VAR "AdddressCfgValue_MnS" = "bit:shl( $MnS_Value, 19)"!][!//
        [!//
        [!VAR "SONA_Value" = "num:i(1)"!][!//
        [!VAR "AdddressCfgValue_SONA" = "bit:shl( $SONA_Value, 20)"!][!//
        [!//
        [!VAR "SOPE_Value" = "num:i(1)"!][!//
        [!VAR "AdddressCfgValue_SOPE" = "bit:shl( $SOPE_Value, 21)"!][!//
        [!//
        [!VAR "AdddressCfgValue" = "num:inttohex(num:i(0))"!][!//
        [!VAR "AdddressCfgValue" = "bit:or($AdddressCfgValue, $AdddressCfgValue_Adr)"!][!//
        [!VAR "AdddressCfgValue" = "bit:or($AdddressCfgValue, $AdddressCfgValue_TBAM)"!][!//
        [!VAR "AdddressCfgValue" = "bit:or($AdddressCfgValue, $AdddressCfgValue_GCE)"!][!//
        [!VAR "AdddressCfgValue" = "bit:or($AdddressCfgValue, $AdddressCfgValue_MCE)"!][!//
        [!VAR "AdddressCfgValue" = "bit:or($AdddressCfgValue, $AdddressCfgValue_MnS)"!][!//
        [!VAR "AdddressCfgValue" = "bit:or($AdddressCfgValue, $AdddressCfgValue_SONA)"!][!//
        [!VAR "AdddressCfgValue" = "bit:or($AdddressCfgValue, $AdddressCfgValue_SOPE)"!][!//
        [!//
        [!//

        /* AdddressCfgValue */
        [!"num:inttohex(num:i($AdddressCfgValue ))"!]U,
        [!//
        [!//
        [!VAR "DEC_Cfg" = "node:value(I2cFractionalDividerDec)"!][!//
        [!VAR "DEC_Value" = "$DEC_Cfg"!][!//
        [!VAR "FracDividerCfgValue_DEC" = "$DEC_Value"!][!//
        [!//
        [!VAR "INC_Cfg" = "node:value(I2cFractionalDividerInc)"!][!//
        [!VAR "INC_Value" = "$INC_Cfg"!][!//
        [!VAR "FracDividerCfgValue_INC" = "bit:shl($INC_Value, 16)"!][!//
        [!//
        [!VAR "FracDividerCfgValue" = "num:inttohex(num:i(0))"!][!//
        [!VAR "FracDividerCfgValue" = "bit:or($FracDividerCfgValue, $FracDividerCfgValue_DEC)"!][!//
        [!VAR "FracDividerCfgValue" = "bit:or($FracDividerCfgValue, $FracDividerCfgValue_INC)"!][!//
        [!//
        [!//

        [!IF "I2cSpeed = 'HIGH_SPEED_MODE'"!][!//
          [!VAR "Temp_INC" = "num:i(2)"!][!//
          [!VAR "Temp_FracDividerCfgValue_INC" = "bit:shl($Temp_INC, 16)"!][!//
          [!VAR "Temp_FracDividerCfgValue_DEC" = "num:i(0)"!][!//
          [!VAR "Temp_FracDividerCfgValue_DEC" = "(((($Temp_INC * $FI2C_Clk) div 400000) - (3 * $Temp_INC)) div 2)"!][!//
          [!VAR "Temp_FracDividerCfgValue" = "num:inttohex(num:i(0))"!][!//
          [!VAR "Temp_FracDividerCfgValue" = "bit:or($Temp_FracDividerCfgValue, $Temp_FracDividerCfgValue_DEC)"!][!//
          [!VAR "Temp_FracDividerCfgValue" = "bit:or($Temp_FracDividerCfgValue, $Temp_FracDividerCfgValue_INC)"!][!//
          /* FracDividerCfgValue */
          [!"num:inttohex(num:i($Temp_FracDividerCfgValue))"!]U,

          /* FracDividerHighCfgValue */
          [!"num:inttohex(num:i($FracDividerCfgValue))"!]U,
        [!ELSE!][!//
          /* FracDividerCfgValue */
          [!"num:inttohex(num:i($FracDividerCfgValue))"!]U,

          /* FracDividerHighCfgValue */
          [!"num:inttohex(num:i(0))"!]U,
        [!ENDIF!][!//
        [!//
        [!//
        [!VAR "SDA_DEL_HD_DAT_Cfg" = "node:value(I2cSdaDelayStageDataHoldTime)"!][!//
        [!VAR "SDA_DEL_HD_DAT_Value" = "$SDA_DEL_HD_DAT_Cfg"!][!//
        [!VAR "TimingCfgvalue_SDA_DEL_HD_DAT" = "$SDA_DEL_HD_DAT_Value"!][!//
        [!//
        [!VAR "HS_SDA_DEL_HD_DAT_Value" = "num:i(0)"!][!//
        [!VAR "TimingCfgvalue_HS_SDA_DEL_HD_DAT" = "bit:shl( $HS_SDA_DEL_HD_DAT_Value, 6)"!][!//
        [!//
        [!VAR "SCL_DEL_HD_STA_Cfg" = "node:value(I2cSclDelayStageHoldTimeStartBit)"!][!//
        [!VAR "SCL_DEL_HD_STA_Value" = "$SCL_DEL_HD_STA_Cfg"!][!//
        [!VAR "TimingCfgvalue_SCL_DEL_HD_STA" = "bit:shl( $SCL_DEL_HD_STA_Value, 9)"!][!//
        [!//
        [!VAR "EN_SCL_LOW_LEN_Cfg" = "node:value(I2cEnCfgFastModeSclLowLength)"!][!//
        [!VAR "EN_SCL_LOW_LEN_Value" = "num:i(0)"!][!//
        [!IF "$EN_SCL_LOW_LEN_Cfg = 'true' "!][!//
          [!VAR "EN_SCL_LOW_LEN_Value" = "num:i(1)"!][!//
        [!ELSE!][!//
          [!VAR "EN_SCL_LOW_LEN_Value" = "num:i(0)"!][!//
        [!ENDIF!][!//
        [!VAR "TimingCfgvalue_EN_SCL_LOW_LEN" = "bit:shl($EN_SCL_LOW_LEN_Value, 14)"!][!//
        [!//
        [!VAR "FS_SCL_LOW_Cfg" = "node:value(I2cSetFastModeSclLowPerTime)"!][!//
        [!VAR "FS_SCL_LOW_Value" = "num:i(0)"!][!//
        [!IF "$FS_SCL_LOW_Cfg = 'true' "!][!//
          [!VAR "FS_SCL_LOW_Value" = "num:i(1)"!][!//
        [!ELSE!][!//
          [!VAR "FS_SCL_LOW_Value" = "num:i(0)"!][!//
        [!ENDIF!][!//
        [!VAR "TimingCfgvalue_FS_SCL_LOW" = "bit:shl( $FS_SCL_LOW_Value, 15)"!][!//
        [!//
        [!VAR "HS_SDA_DEL_Value" = "num:i(0)"!][!//
        [!VAR "TimingCfgvalue_HS_SDA_DEL" = "bit:shl( $HS_SDA_DEL_Value, 16)"!][!//
        [!//
        [!VAR "SCL_LOW_LEN_Cfg" = "node:value(I2cFastModeSclLowLength)"!][!//
        [!VAR "SCL_LOW_LEN_Value" = "$SCL_LOW_LEN_Cfg"!][!//
        [!VAR "TimingCfgvalue_SCL_LOW_LEN" = "bit:shl( $SCL_LOW_LEN_Value, 24)"!][!//
        [!//
        [!VAR "TimingCfgvalue" = "num:inttohex(num:i(0))"!][!//
        [!VAR "TimingCfgvalue" = "bit:or($TimingCfgvalue, $TimingCfgvalue_SDA_DEL_HD_DAT)"!][!//
        [!VAR "TimingCfgvalue" = "bit:or($TimingCfgvalue, $TimingCfgvalue_HS_SDA_DEL_HD_DAT)"!][!//
        [!VAR "TimingCfgvalue" = "bit:or($TimingCfgvalue, $TimingCfgvalue_SCL_DEL_HD_STA)"!][!//
        [!VAR "TimingCfgvalue" = "bit:or($TimingCfgvalue, $TimingCfgvalue_EN_SCL_LOW_LEN)"!][!//
        [!VAR "TimingCfgvalue" = "bit:or($TimingCfgvalue, $TimingCfgvalue_FS_SCL_LOW)"!][!//
        [!VAR "TimingCfgvalue" = "bit:or($TimingCfgvalue, $TimingCfgvalue_HS_SDA_DEL)"!][!//
        [!VAR "TimingCfgvalue" = "bit:or($TimingCfgvalue, $TimingCfgvalue_SCL_LOW_LEN)"!][!//
        [!//
        [!//

        /* TimingCfgvalue */
        [!"num:inttohex(num:i($TimingCfgvalue ))"!]U,
        [!//
        [!//
        [!VAR "RXBS_Value" = "num:i(2)"!][!//
        [!VAR "FIFOCfgValue_RXBS" = "$RXBS_Value"!][!//
        [!//
        [!VAR "TXBS_Value" = "num:i(2)"!][!//
        [!VAR "FIFOCfgValue_TXBS" = "bit:shl($TXBS_Value, 4)"!][!//
        [!//
        [!VAR "RXFA_Value" = "num:i(0)"!][!//
        [!VAR "FIFOCfgValue_RXFA" = "bit:shl($RXFA_Value, 8)"!][!//
        [!//
        [!VAR "TXFA_Value" = "num:i(0)"!][!//
        [!VAR "FIFOCfgValue_TXFA" = "bit:shl($TXFA_Value, 12)"!][!//
        [!//
        [!VAR "RXFC_Value" = "num:i(1)"!][!//
        [!VAR "FIFOCfgValue_RXFC" = "bit:shl($RXFC_Value, 16)"!][!//
        [!//
        [!VAR "TXFC_Value" = "num:i(1)"!][!//
        [!VAR "FIFOCfgValue_TXFC" = "bit:shl($TXFC_Value, 17)"!][!//
        [!//
        [!VAR "CRBC_Value" = "num:i(0)"!][!//
        [!VAR "FIFOCfgValue_CRBC" = "bit:shl($CRBC_Value, 18)"!][!//
        [!//
        [!VAR "FIFOCfgValue" = "num:inttohex(num:i(0))"!][!//
        [!VAR "FIFOCfgValue" = "bit:or($FIFOCfgValue, $FIFOCfgValue_RXBS)"!][!//
        [!VAR "FIFOCfgValue" = "bit:or($FIFOCfgValue, $FIFOCfgValue_TXBS)"!][!//
        [!VAR "FIFOCfgValue" = "bit:or($FIFOCfgValue, $FIFOCfgValue_RXFA)"!][!//
        [!VAR "FIFOCfgValue" = "bit:or($FIFOCfgValue, $FIFOCfgValue_TXFA)"!][!//
        [!VAR "FIFOCfgValue" = "bit:or($FIFOCfgValue, $FIFOCfgValue_RXFC)"!][!//
        [!VAR "FIFOCfgValue" = "bit:or($FIFOCfgValue, $FIFOCfgValue_TXFC)"!][!//
        [!VAR "FIFOCfgValue" = "bit:or($FIFOCfgValue, $FIFOCfgValue_CRBC)"!][!//
        [!//
        [!//

        /* FIFOCfgValue */
        [!"num:inttohex(num:i($FIFOCfgValue))"!]U,
        [!//
        [!//
        [!VAR "PortSelect" = "I2cSDASelect"!][!//
        [!VAR "PortPinID" = "text:split($PortSelect, '_')[1]"!][!//
        [!IF "$PortPinID = 'SDA0A' or $PortPinID ='SDA1A'"!][!//
          [!VAR "PISEL_Value" = "num:i(0)"!][!//
        [!ELSEIF "$PortPinID = 'SDA0B' or $PortPinID ='SDA1B'"!][!//
          [!VAR "PISEL_Value" = "num:i(1)"!][!//
        [!ELSEIF "$PortPinID = 'SDA0C' or $PortPinID ='SDA1C'"!][!//
          [!VAR "PISEL_Value" = "num:i(2)"!][!//
        [!ENDIF!][!//
        [!VAR "PortPinCfgvalue_PISEL" = "$PISEL_Value"!][!//
        [!//
        [!VAR "PortPinCfgvalue" = "num:inttohex(num:i(0))"!][!//
        [!VAR "PortPinCfgvalue" = "bit:or($PortPinCfgvalue, $PortPinCfgvalue_PISEL)"!][!//
        [!//
        [!//

        /* PortPinCfgvalue */
        [!"num:inttohex(num:i($PortPinCfgvalue))"!]U,
        [!//
        [!//
        [!VAR "EDIS_Cfg" = "0"!][!//
        [!VAR "EDIS_Value" = "$EDIS_Cfg"!][!//
        [!VAR "HWClkSetting_EDIS" = "bit:shl($EDIS_Value,3)"!][!//
        [!VAR "RMC_Cfg" = "node:value(I2cRmc)"!][!//
        [!VAR "RMC_Value" = "$RMC_Cfg"!][!//
        [!VAR "HWClkSetting_RMC" = "bit:shl($RMC_Value, 8)"!][!//
        [!VAR "HWClkSetting" = "num:inttohex(num:i(0))"!][!//
        [!VAR "HWClkSetting" = "bit:or($HWClkSetting, $HWClkSetting_EDIS)"!][!//
        [!VAR "HWClkSetting" = "bit:or($HWClkSetting, $HWClkSetting_RMC)"!][!//

        /* HwClkSettings */
        [!"num:inttohex(num:i($HWClkSetting))"!]U,

        /* AddressingMode */
        [!IF "I2cAddressingMode = 'I2C_7_BIT_ADDRESSING'"!][!//
          I2C_7_BIT_ADDRESSING,
        [!ELSE!][!//
          I2C_10_BIT_ADDRESSING,
        [!ENDIF!][!//

        /* Notification function */
        {
        [!INDENT "6"!][!//
          [!IF "I2cAsyncNotification = 'true'"!]
            [!IF "node:exists(I2cPacketEndNotification) = 'true' and I2cPacketEndNotification != 'NULL_PTR'"!][!//
              [!VAR "Notify" = "I2cPacketEndNotification"!][!//
              [!IF "num:isnumber($Notify) = 'true'"!][!//
                [!"concat('(I2c_NotifType)',num:inttohex(num:radixtoint($Notify),8),'U')"!],
              [!ELSE!][!//
                &[!"$Notify"!]
              [!ENDIF!][!//
            [!ELSE!][!//
              NULL_PTR
            [!ENDIF!][!//
          [!ELSE!][!//
              NULL_PTR
         [!ENDIF!][!//
        [!ENDINDENT!][!//
        },

        /* Tx Timeout value */
        [!"num:i(I2cTxTimeOut)"!]U,

        /* Rx Timeout value */
        [!"num:i(I2cRxTimeOut)"!]U
      [!ENDINDENT!][!//
      },
    [!ENDLOOP!]
  [!ENDINDENT!][!//
  };
  /* I2c configuration set */
  /* MISRA2012_RULE_8_7_JUSTIFICATION: Module configuration data structure
     declaration is as per Autosar guidelines. This data structure is needed
     by SW units using I2c Driver APIs hence it should be declared as extern in
     the SW unit from where it is used */
   /* MISRA2012_RULE_8_4_JUSTIFICATION: Module configuration data structure
     declaration is as per Autosar guidelines. This data structure is needed
     by SW units using I2c Driver APIs hence it should be declared as extern in
     the SW unit from where it is used */
    [!SELECT "I2cConfigSet/*[1]"!][!//
      [!IF "$VariantsConfigured = num:i(1)"!]
        const I2c_ConfigType I2c_Config_[!"$PredefinedVarName"!] =
      [!ELSE!]
        const I2c_ConfigType I2c_Config  =
      [!ENDIF!][!//
    [!ENDSELECT!][!//
    {
    [!INDENT "6"!][!//
      [!IF "$VariantsConfigured = num:i(1)"!][!//
        &I2c_ChannelConfig_[!"$PredefinedVarName"!][0],
      [!ELSE!][!//
        &I2c_ChannelConfig[0],
      [!ENDIF!][!//
      I2C_MAX_CHANNELS
    [!ENDINDENT!][!//
    };
  [!ENDINDENT!][!//
[!ENDSELECT!][!//

#define I2C_STOP_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "I2c_MemMap.h"
