[!/*****************************************************************************
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
**  FILENAME  : Mcu_PBcfg.c                                                   **
**                                                                            **
**  VERSION   : 33.0.0                                                        **
**                                                                            **
**  DATE      : 2023-05-22                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Mcu.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID=]                                          **
**                                                                            **
**  DESCRIPTION  : Code template source file for Mcu Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Mcu Driver, AUTOSAR Release 4.2.2 and **
**                     4.4.0                                                  **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*****************************************************************************/!][!//
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
**  FILENAME  : Mcu_PBcfg.c                                                   **
**                                                                            **
**  VERSION   : 33.0.0                                                        **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]       !!!IGNORE-LINE!!!                  **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]           !!!IGNORE-LINE!!!                **
**                                                                            **
**  BSW MODULE DECRIPTION : Mcu.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Mcu configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Mcu Driver, AUTOSAR Release 4.2.2     **
**                     and 4.4.0                                              **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                       Includes                                             **
*******************************************************************************/
/*
  Note: Elektrobit Automotive GmbH modified the original code provided
        by the third party supplier. The modification is provided for
        convenience.
        Please use the modification on your discretion and account, or
        use the unmodified files provided with this distribution. 
  Please see for the reasons in the file ImportantNotes.txt for tag

ASCINFINEON-1043 Update PostBuild generation 
*/
[!/*[cover parentID={C4B1331B-77FF-436e-8395-546A7D51431E}][/cover]*/!][!//
/* Include module header file */
#include "Mcu.h"
[!NOCODE!]
  [!INCLUDE "Mcu.m"!][!// Include macro definitions.
[!ENDNOCODE!]
[!//
[!IF "var:defined('postBuildVariant')"!][!//
[!VAR "McuConfigShortName" = "concat('_Config_',$postBuildVariant)"!][!//
[!ELSE!][!//
[!VAR "McuConfigShortName"="'_Config'"!][!//
[!ENDIF!]
[!SELECT " as:modconf('ResourceM')[1]"!][!//
    [!VAR "CoresAvailable" = "num:i(as:modconf('ResourceM')[1]/ResourceMMcalConfig/*[1]/ResourceMNumberOfActiveCores)"!][!//
[!ENDSELECT!][!//
[!IF "not(node:exists(as:modconf('McalLib')[1]))"!]
  [!ERROR!][!//
    MCU Code Generator: McalLib module is not added to the project.
  [!ENDERROR!][!//
[!ENDIF!]
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Mcu')[1]"!][!//
/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
[!/*[cover parentID={72DABBEB-F27B-4677-B6B4-B53F634341BA}][/cover]*/!][!//
[!/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}][/cover]*/!][!//
#define MCU_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
[!/*[cover parentID={4E3D9856-2420-4bc0-8E39-B0F93F3DC39E}][/cover]*/!][!//
#include "Mcu_MemMap.h"

[!NOCODE!][!//
  [!VAR "ModulePath" = "'McuModuleConfiguration'"!][!//
[!ENDNOCODE!][!//
[!NOCODE!][!//
  [!VAR "OSCFREQ" = "num:i(McuGeneralConfiguration/McuMainOscillatorFrequency)"!][!//
  [!VAR "SYSCLKFREQ" = "num:i(McuGeneralConfiguration/McuSysClkFrequency)"!][!//
  [!IF "McuGeneralConfiguration/McuOscillatorMode = 'EXT_CRYSTAL_CERAMIC_RES_MODE_SEL0'"!][!//
    [!IF "($OSCFREQ < num:i(16)) or ($OSCFREQ > num:i(40))"!][!//
      [!ERROR!][!//
        Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: Configured oscillator clock frequency is out of range in EXT_CRYSTAL_CERAMIC_RES_MODE_SEL0 mode. (16Mhz - 40Mhz)
      [!ENDERROR!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
  [!VAR "FBACK" = "num:i(ecu:get('Mcu.BackUpFrequency') div num:i(1000000))"!][!//
  [!VAR "OscFrequency" = "num:i($OSCFREQ * num:i(1000000))"!][!//
  [!VAR "BackupFrequency" = "num:i(ecu:get('Mcu.BackUpFrequency'))"!][!//
  [!VAR "SysClkFrequency" = "num:i($SYSCLKFREQ * num:i(1000000))"!][!//
[!ENDNOCODE!][!//
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
/*
  PLL Distribution configuration structure(s)
  for each clock setting configurations
*/
[!VAR "ClkCfgCount" = "num:i(count(node:ref($ModulePath)/McuClockSettingConfig/*))"!][!//
[!FOR "ClkIndex" = "num:i(0)" TO "(num:i($ClkCfgCount)- num:i(1))"!][!//
[!SELECT "node:ref($ModulePath)/McuClockSettingConfig/*[McuClockSettingId = num:i($ClkIndex)]/McuClockReferencePointConfig"!][!//
[!/*[cover parentID={EBAAB1BB-D3A3-4eeb-A5F5-92225ED3B370}]*/!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
static const Mcu_PllDistributionConfigType Mcu_kPllDistributionConfiguration[!"$McuConfigShortName"!]_[!"string($ClkIndex)"!] =
{
  [!NOCODE!][!//
    [!VAR "Ccucon0" = "num:i(0)"!]
    [!VAR "Ccucon1" = "num:i(0)"!]
    [!VAR "Ccucon2" = "num:i(0)"!]
    [!VAR "Ccucon5" = "num:i(0)"!]
    [!VAR "Ccucon6" = "num:i(0)"!]
    [!IF "$CoresAvailable >= num:i(2)"!][!//
      [!VAR "Ccucon7" = "num:i(0)"!]
    [!ENDIF!][!//
    [!IF "$CoresAvailable >= num:i(3)"!][!//
      [!VAR "Ccucon8" = "num:i(0)"!]
    [!ENDIF!][!//
    [!IF "$CoresAvailable >= num:i(4)"!][!//
      [!VAR "Ccucon9" = "num:i(0)"!]
    [!ENDIF!][!//
    [!IF "$CoresAvailable >= num:i(5)"!][!//
      [!VAR "Ccucon10" = "num:i(0)"!]
    [!ENDIF!][!//
    [!IF "$CoresAvailable >= num:i(6)"!][!//
      [!VAR "Ccucon11" = "num:i(0)"!]
    [!ENDIF!][!//

    [!/******************************************************/!][!//
    [!/*STM divider value calc and dependency check - start */!][!//
    [!/******************************************************/!][!//
    [!CALL "Mcu_CG_ValFreq","Freq" = "'STM'"!][!//
    [!IF "./McuPllDistributionSettingConfig/McuSTMFrequency = num:i(0)"!][!//
      [!ERROR!][!//
        Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: McuSTMFrequency should not be ZERO, because Mcu driver APIs use McalLib timer tick APIs to implement required time-delay.
      [!ENDERROR!][!//
    [!ENDIF!][!//
    [!VAR "Ccucon0" = "bit:or($Ccucon0,bit:shl($CalculatedVal,num:i(0)))"!][!//
    [!/******************************************************/!][!//
    [!/*STM divider value calc and dependency check -   end */!][!//
    [!/******************************************************/!][!//
    [!/* In case Low power divider mode is selected then this value is set by parameter - McuLowPowerDivValue*/!][!//
    [!IF "(text:split(./McuPllDistributionSettingConfig/McuLowPowerDivValue,'SEL')[2] != num:i(0))"!][!//
      [!/*McuLowPowerDivValue*/!][!//
      [!VAR "CalculatedVal" = "./McuPllDistributionSettingConfig/McuLowPowerDivValue"!][!//
      [!VAR "CalculatedVal" = "num:i(text:split($CalculatedVal,'SEL')[2])"!][!//
      [!VAR "Ccucon0" = "bit:or($Ccucon0,bit:shl($CalculatedVal,num:i(12)))"!][!//
    [!ELSE!][!//
      [!/******************************************************/!][!//
      [!/*SRI/SPB/BBB divider value calc and dependency check - start */!][!//
      [!/******************************************************/!][!//
      [!CALL "Mcu_CG_ValFreq","Freq" = "'SRI'"!][!//
      [!VAR "Ccucon0" = "bit:or($Ccucon0,bit:shl($CalculatedVal,num:i(8)))"!][!//

      [!/* SPB divider value calculation and validation */!][!//
      [!CALL "Mcu_CG_ValFreq","Freq" = "'SPB'"!][!//
      [!VAR "Ccucon0" = "bit:or($Ccucon0,bit:shl($CalculatedVal,num:i(16)))"!][!//

      [!/******************************************************/!][!//
      [!/*GTM divider value calc and dependency check - start */!][!//
      [!/******************************************************/!][!//
      [!IF "ecu:get('Gtm.Available')='true'"!][!//
        [!CALL "Mcu_CG_GtmValFreq"!][!//
        [!VAR "Ccucon0" = "bit:or($Ccucon0,bit:shl($CalculatedVal,num:i(4)))"!][!//
      [!ELSE!]
        [!VAR "Ccucon0" = "bit:or($Ccucon0,bit:shl(num:i(1),num:i(4)))"!][!//
      [!ENDIF!]
      [!/******************************************************/!][!//
      [!/*GTM divider value calc and dependency check - end */!][!//
      [!/******************************************************/!][!//

      [!/*BBB divider value calc and dependency check */!][!//
      [!CALL "Mcu_CG_ValFreq","Freq" = "'BBB'"!][!//
      [!VAR "Ccucon0" = "bit:or($Ccucon0,bit:shl($CalculatedVal,num:i(20)))"!][!//

      [!/*FSI divider value calculation and check*/!][!//
      [!/* Verify McuFSIFrequency */!][!//
      [!CALL "Mcu_CG_ValFreq","Freq" = "'FSI'"!][!//
      [!IF "./McuPllDistributionSettingConfig/McuSRIFrequency < ./McuPllDistributionSettingConfig/McuFSIFrequency"!][!//
        [!ERROR!][!//
          Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: McuFSIFrequency must be equal or less than  McuSRIFrequency.
        [!ENDERROR!][!//
      [!ENDIF!][!//
      [!VAR "Ccucon0" = "bit:or($Ccucon0,bit:shl($CalculatedVal,num:i(24)))"!][!//

      [!/*ADAS clock source and frequency selection*/!][!//
      [!IF "./McuPllDistributionSettingConfig/McuAdasFrequency > num:i(0)"!][!//
        [!CALL "Mcu_CG_ValFreq","Freq" = "'Adas'"!][!//
        [!IF "./McuPllDistributionSettingConfig/McuSRIFrequency > ./McuPllDistributionSettingConfig/McuAdasFrequency"!][!//
          [!ERROR!][!//
            Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]:  McuSRIFrequency cannot be greater than  McuAdasFrequency.
          [!ENDERROR!][!//
        [!ENDIF!][!//
        [!VAR "Ccucon5" = "bit:or($Ccucon5,bit:shl($CalculatedVal,num:i(8)))"!][!//
      [!ELSE!][!//
        [!IF "ecu:get('Mcu.fAdasExists')='false'"!][!//
          [!INFO!][!//
            MCU: To update SRAM support hardware registers, McuAdasFrequncy should be configured > 0
          [!ENDINFO!][!//
        [!ENDIF!][!//
        [!VAR "CalculatedVal" = "num:i(0)"!][!//
        [!VAR "Ccucon5" = "bit:or($Ccucon5,bit:shl($CalculatedVal,num:i(8)))"!][!//
      [!ENDIF!][!//
      
      [!/*Gigabit Ethernet clock source and frequency selection*/!][!//
      [!CALL "Mcu_CG_ValFreq","Freq" = "'GEth'"!][!//
      [!IF "(./McuPllDistributionSettingConfig/McuSRIFrequency < ./McuPllDistributionSettingConfig/McuGEthFrequency)"!][!//
         [!ERROR!][!//
           Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: McuGEthFrequency should not be greater than McuSRIFrequency.
         [!ENDERROR!][!//
      [!ENDIF!][!//
      [!VAR "Ccucon5" = "bit:or($Ccucon5,bit:shl($CalculatedVal,num:i(0)))"!][!//
    [!ENDIF!][!//[!IF "(text:split(./McuPllDistributionSettingConfig/McuLowPowerDivValue,'SEL')[2] != 0)"!][!//
    [!/******************************************************/!][!//
    [!/*SRI/SPB/BBB divider value calc and dependency check - end */!][!//
    [!/******************************************************/!][!//
    [!/* Verify McuFSI2Frequency */!][!//
    [!CALL "Mcu_CG_ValFreq","Freq" = "'FSI2'"!][!//
    [!IF "./McuPllDistributionSettingConfig/McuSRIFrequency < ./McuPllDistributionSettingConfig/McuFSI2Frequency"!][!//
      [!ERROR!][!//
        Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: McuFSI2Frequency must be equal or less than  McuSRIFrequency.
      [!ENDERROR!][!//
    [!ENDIF!][!//
    [!VAR "Ccucon0" = "bit:or($Ccucon0,bit:shl($CalculatedVal,num:i(26)))"!][!//

    [!/*McuClockDistributionInpClockSel*/!][!//
    [!VAR "CalculatedVal" = "./McuPllDistributionSettingConfig/McuClockDistributionInpClockSel"!][!//
    [!VAR "CalculatedVal" = "text:split($CalculatedVal,'SEL')[3]"!][!//
    [!VAR "Ccucon0" = "bit:or($Ccucon0,bit:shl($CalculatedVal,num:i(28)))"!][!//

    [!/*CCUCON5 preparation */!][!//
    [!/* McanH clock source and frequency selection*/!][!//
    [!CALL "Mcu_CG_ValFreq","Freq" = "'McanH'"!][!//
    [!IF "(./McuPllDistributionSettingConfig/McuSPBFrequency < ./McuPllDistributionSettingConfig/McuMcanHFrequency)"!][!//
       [!ERROR!][!//
         Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: McuMcanHFrequency should not be greater than McuSPBFrequency.
       [!ENDERROR!][!//
    [!ENDIF!][!//
    [!VAR "Ccucon5" = "bit:or($Ccucon5,bit:shl($CalculatedVal,num:i(4)))"!][!//

    [!/*CCUCON1 prepration */!][!//
    [!/*MCAN clock source and frequency selection*/!][!//
    [!CALL "Mcu_CG_MCNASCLNFreq","Freq" = "'MCan'", "ClkSrcSel" = "num:i(0)"!][!//
    [!VAR "Ccucon1" = "bit:or($Ccucon1,bit:shl($CalculatedVal, num:i(0)))"!][!//
    [!VAR "Ccucon1" = "bit:or($Ccucon1,bit:shl($ClkSrcSel    , num:i(4)))"!][!//

    [!/*McuFreqSource1ClockDivSelect*/!][!//
    [!VAR "CalculatedVal" = "./McuPeripheralPllSettingConfig/McuFreqSource1ClockDivSelect"!][!//
    [!VAR "CalculatedVal" = "text:split($CalculatedVal,'SEL')[2]"!][!//
    [!VAR "Ccucon1" = "bit:or($Ccucon1,bit:shl($CalculatedVal,num:i(7)))"!][!//

    [!/*MSC clock source and frequency selection*/!][!//
    [!IF "ecu:get('Mcu.fMscExists')='true'"!][!//
      [!CALL "Mcu_CG_MSCQSPIFreq","Freq" = "'Msc'","ClkSrcSel" = "num:i(0)"!][!//
      [!VAR "Ccucon1" = "bit:or($Ccucon1,bit:shl($CalculatedVal, num:i(16)))"!][!//
      [!VAR "Ccucon1" = "bit:or($Ccucon1,bit:shl($ClkSrcSel    , num:i(20)))"!][!//
    [!ELSE!]
      [!/*Following step is taken in order to confirm to default value of CCUCON1. Writing 1 will have no effect if MSC is not present in the device*/!][!//
      [!VAR "Ccucon1" = "bit:or($Ccucon1,bit:shl(num:i(1),num:i(20)))"!][!//
    [!ENDIF!][!//

    [!/*QSPI clock source and frequency selection*/!][!//
    [!CALL "Mcu_CG_MSCQSPIFreq","Freq" = "'Qspi'","ClkSrcSel" = "num:i(0)"!][!//
    [!VAR "Ccucon1" = "bit:or($Ccucon1,bit:shl($CalculatedVal, num:i(24)))"!][!//
    [!VAR "Ccucon1" = "bit:or($Ccucon1,bit:shl($ClkSrcSel    , num:i(28)))"!][!//

    [!/*I2C divider value calc and check*/!][!//
    [!IF "ecu:get('Mcu.fI2CExists')='true'"!][!//
      [!CALL "Mcu_CG_I2CASCLINFFreq","Freq" = "'I2C'"!][!//
      [!VAR "Ccucon1" = "bit:or($Ccucon1,bit:shl($CalculatedVal,num:i(8)))"!][!//
    [!ELSE!]
      [!/*A value of 3 is written to conform to the system reset value of I2C when IP is not available in the hardware*/!][!//
      [!VAR "Ccucon1" = "bit:or($Ccucon1,bit:shl(num:i(3),num:i(8)))"!][!//
    [!ENDIF!][!//

    [!/*CCUCON2 preparation */!][!//
    [!/*ASCLIN-Fast clock source and frequency selection*/!][!//
    [!CALL "Mcu_CG_I2CASCLINFFreq","Freq" = "'AscLinFast'"!][!//
    [!VAR "Ccucon2" = "bit:or($Ccucon2,bit:shl($CalculatedVal,num:i(0)))"!][!//

    [!/*ASCLIN-Slow clock source and frequency selection*/!][!//
    [!CALL "Mcu_CG_MCNASCLNFreq","Freq" = "'AscLinSlow'", "ClkSrcSel" = "num:i(0)"!][!//
    [!VAR "Ccucon2" = "bit:or($Ccucon2,bit:shl($CalculatedVal, num:i(8)))"!][!//
    [!VAR "Ccucon2" = "bit:or($Ccucon2,bit:shl($ClkSrcSel    , num:i(12)))"!][!//

    [!IF "ecu:get('Mcu.fEBUExists')='true'"!][!//
      [!IF "(./McuPllDistributionSettingConfig/McuEbuClkEnable = 'true')"!][!//
        [!VAR "Ccucon2" = "bit:xor($Ccucon2,bit:shl(num:i(1),num:i(24)))"!][!//
      [!ENDIF!][!//
    [!ELSE!]
      [!VAR "Ccucon2" = "bit:xor($Ccucon2,bit:shl(num:i(1),num:i(24)))"!][!//
    [!ENDIF!][!//
    [!IF "ecu:get('Mcu.fERAYExists')='true'"!][!//
      [!IF "(./McuPllDistributionSettingConfig/McuErayClkEnable = 'true')"!][!//
        [!VAR "Ccucon2" = "bit:xor($Ccucon2,bit:shl(num:i(1),num:i(25)))"!][!//
      [!ENDIF!][!//
    [!ELSE!]
      [!VAR "Ccucon2" = "bit:xor($Ccucon2,bit:shl(num:i(1),num:i(25)))"!][!//
    [!ENDIF!][!//
    [!IF "ecu:get('Mcu.fHSPDMExists')='true'"!][!//
      [!IF "(./McuPllDistributionSettingConfig/McuHspdmClkEnable = 'true')"!][!//
        [!VAR "Ccucon2" = "bit:xor($Ccucon2,bit:shl(num:i(1),num:i(26)))"!][!//
      [!ENDIF!][!//
    [!ELSE!]
      [!VAR "Ccucon2" = "bit:xor($Ccucon2,bit:shl(num:i(1),num:i(26)))"!][!//
    [!ENDIF!][!//

    [!/*Clock Monitoring feature*/!][!//
    [!IF "../../../../McuGeneralConfiguration/McuSafetyEnable = 'true'"!][!//
      [!VAR "Ccucon3" = "num:i(0)"!][!//
      [!VAR "Ccucon4" = "num:i(0)"!][!//
      [!IF "./McuClockMonitorConfig/McuPll0ClockMonEnable = 'true'"!][!//
        [!VAR "Ccucon3" = "bit:or($Ccucon3,bit:shl(num:i(1),num:i(0)))"!][!//
      [!ENDIF!][!//
      [!IF "./McuClockMonitorConfig/McuPll1ClockMonEnable = 'true'"!][!//
        [!VAR "Ccucon3" = "bit:or($Ccucon3,bit:shl(num:i(1),num:i(1)))"!][!//
      [!ENDIF!][!//
      [!IF "./McuClockMonitorConfig/McuPll2ClockMonEnable = 'true'"!][!//
        [!VAR "Ccucon3" = "bit:or($Ccucon3,bit:shl(num:i(1),num:i(2)))"!][!//
      [!ENDIF!][!//
      [!IF "./McuClockMonitorConfig/McuSpbClockMonEnable = 'true'"!][!//
        [!VAR "Ccucon3" = "bit:or($Ccucon3,bit:shl(num:i(1),num:i(3)))"!][!//
      [!ENDIF!][!//
      [!IF "./McuClockMonitorConfig/McuBackupClockMonEnable = 'true'"!][!//
        [!VAR "Ccucon3" = "bit:or($Ccucon3,bit:shl(num:i(1),num:i(4)))"!][!//
      [!ENDIF!][!//
      [!IF "./McuClockMonitorConfig/McuBackupClockRangeMonEnable = 'true'"!][!//
        [!VAR "Ccucon4" = "bit:or($Ccucon4,bit:shl(num:i(1),num:i(24)))"!][!//
        [!VAR "BackupLowTh" = "num:i(0)"!][!//
        [!VAR "BackupUpTh" = "num:i(0)"!][!//
        [!VAR "Pll0Freq" = "num:i(./McuSystemPllSettingConfig/McuClockReferencePointFrequency0)"!][!//
        [!VAR "BackupLowTh" = "num:i(num:f((num:i(512)) div $Pll0Freq) * num:f(0.9) * num:i(100000000))"!][!//
      [!IF "BackupLowTh > num:i(4095)"!][!//
        [!ERROR!]
          Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]:Backup lower threshold is out of bound. Please select proper value.
        [!ENDERROR!]
      [!ENDIF!][!//
        [!VAR "BackupLowTh" = "bit:and($BackupLowTh,num:i(4095))"!]
        [!VAR "BackupUpTh" = "num:i(num:f((num:i(512)) div $Pll0Freq) * num:f(1.1) * num:i(100000000))"!][!//
      [!IF "BackupUpTh > num:i(4095)"!][!//
      [!ERROR!]
        Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]:Backup upper threshold is out of bound. Please select proper value.
      [!ENDERROR!]
      [!ENDIF!][!//
        [!VAR "BackupUpTh" = "bit:and($BackupUpTh,num:i(4095))"!]
        [!VAR "Ccucon4" = "bit:or($Ccucon4,bit:shl($BackupLowTh,num:i(0)))"!][!//
        [!VAR "Ccucon4" = "bit:or($Ccucon4,bit:shl($BackupUpTh,num:i(12)))"!][!//
      [!ENDIF!][!//
      [!VAR "Ccucon4" = "bit:or($Ccucon4,bit:shl(num:i(1),num:i(30)))"!][!//
    [!ENDIF!][!//
    [!/*CPUx clock source and frequency selection*/!][!//
    [!VAR "freq" = "'CPU0'"!]
    [!FOR "index" = "num:i(1)" TO "num:i(count(text:split($freq, ',')))"!]
    [!CALL "Mcu_CG_CPUFreq","Freq" = "text:split($freq, ',')[num:i($index)]"!][!//
    [!ENDFOR!]
    [!VAR "Ccucon6" = "bit:or($Ccucon6,bit:shl($CalculatedVal,num:i(0)))"!][!//
    [!IF "$CoresAvailable >= num:i(2)"!][!//
      [!VAR "freq" = "'CPU1'"!]
    [!FOR "index" = "num:i(1)" TO "num:i(count(text:split($freq, ',')))"!]
    [!CALL "Mcu_CG_CPUFreq","Freq" = "text:split($freq, ',')[num:i($index)]"!][!//
    [!ENDFOR!]
      [!VAR "Ccucon7" = "bit:or($Ccucon7,bit:shl($CalculatedVal,num:i(0)))"!][!//
    [!ENDIF!][!//
    [!IF "$CoresAvailable >= num:i(3)"!][!//
      [!VAR "freq" = "'CPU2'"!]
    [!FOR "index" = "num:i(1)" TO "num:i(count(text:split($freq, ',')))"!]
    [!CALL "Mcu_CG_CPUFreq","Freq" = "text:split($freq, ',')[num:i($index)]"!][!//
    [!ENDFOR!]
      [!VAR "Ccucon8" = "bit:or($Ccucon8,bit:shl($CalculatedVal,num:i(0)))"!][!//
    [!ENDIF!][!//
    [!IF "$CoresAvailable >= num:i(4)"!][!//
      [!VAR "freq" = "'CPU3'"!]
    [!FOR "index" = "num:i(1)" TO "num:i(count(text:split($freq, ',')))"!]
    [!CALL "Mcu_CG_CPUFreq","Freq" = "text:split($freq, ',')[num:i($index)]"!][!//
    [!ENDFOR!]
      [!VAR "Ccucon9" = "bit:or($Ccucon9,bit:shl($CalculatedVal,num:i(0)))"!][!//
    [!ENDIF!][!//
    [!IF "$CoresAvailable >= num:i(5)"!][!//
      [!VAR "freq" = "'CPU4'"!]
    [!FOR "index" = "num:i(1)" TO "num:i(count(text:split($freq, ',')))"!]
    [!CALL "Mcu_CG_CPUFreq","Freq" = "text:split($freq, ',')[num:i($index)]"!][!//
    [!ENDFOR!]
      [!VAR "Ccucon10" = "bit:or($Ccucon10,bit:shl($CalculatedVal,0))"!][!//
    [!ENDIF!][!//
    [!IF "$CoresAvailable >= num:i(6)"!][!//
      [!VAR "freq" = "'CPU5'"!]
    [!FOR "index" = "num:i(1)" TO "num:i(count(text:split($freq, ',')))"!]
    [!CALL "Mcu_CG_CPUFreq","Freq" = "text:split($freq, ',')[num:i($index)]"!][!//
    [!ENDFOR!]
      [!VAR "Ccucon11" = "bit:or($Ccucon11,bit:shl($CalculatedVal,num:i(0)))"!][!//
    [!ENDIF!][!//
  [!ENDNOCODE!][!//
  /* CCUCON0 value */
  [!"num:inttohex($Ccucon0,num:i(8))"!]U,
  /* CCUCON1 value */
  [!"num:inttohex($Ccucon1,num:i(8))"!]U,
  /* CCUCON2 value */
  [!"num:inttohex($Ccucon2,num:i(8))"!]U,
  [!IF "../../../../McuGeneralConfiguration/McuSafetyEnable = 'true'"!][!//
  /* CCUCON3 value */
  [!"num:inttohex($Ccucon3,num:i(8))"!]U,
  /* CCUCON4 value */
  [!"num:inttohex($Ccucon4,num:i(8))"!]U,
  [!ENDIF!][!//
  /* CCUCON5 value */
  [!"num:inttohex($Ccucon5,num:i(8))"!]U,
  /* CCUCON6...CCUCON[!"string(5 + $CoresAvailable)"!] value */
  {
    [!"num:inttohex($Ccucon6,num:i(8))"!]U[!IF "$CoresAvailable >= num:i(2)"!],
    [!"num:inttohex($Ccucon7,num:i(8))"!]U[!ENDIF!][!IF "$CoresAvailable >= num:i(3)"!],
    [!"num:inttohex($Ccucon8,num:i(8))"!]U[!ENDIF!][!IF "$CoresAvailable >= num:i(4)"!],
    [!"num:inttohex($Ccucon9,num:i(8))"!]U[!ENDIF!][!IF "$CoresAvailable >= num:i(5)"!],
    [!"num:inttohex($Ccucon10,num:i(8))"!]U[!ENDIF!][!IF "$CoresAvailable >= num:i(6)"!],
    [!"num:inttohex($Ccucon11,num:i(8))"!]U[!ENDIF!][!//

  }
};
[!ENDSELECT!][!//
[!ENDFOR!][!//
[!/*[/cover]*/!][!//
/*
   Configuration : Mcu_ConfigType
   For Mcu_ConfigType: MCU specific configuration ID
   This id corresponds to the container name of the McuConfiguration.
   Use this as the parameter for API: Mcu_Init
   Container: McuClockSettingConfig
   Multilplicity : 1 - *
*/
[!VAR "ClkCount" = "num:i(count(node:ref($ModulePath)/McuClockSettingConfig/*))"!][!//
[!/*[cover parentID={12EC64DD-D9D1-44a9-A86E-075E2D10FBF4}]*/!][!//
static const Mcu_ClockConfigType Mcu_kClockConfiguration[!"$McuConfigShortName"!][[!"num:i($ClkCount)"!]] =
{
[!FOR "ClkIdx" = "num:i(0)" TO "num:i($ClkCount - 1)"!][!//
  [!SELECT "node:ref($ModulePath)/McuClockSettingConfig/*[McuClockSettingId = num:i($ClkIdx)]/McuClockReferencePointConfig"!][!//
  [!VAR "BackupFreqKDiv" = "num:i(0)"!][!//
  [!VAR "KDivVal" = "num:i(0)"!][!//
  /*[!"node:name(./..)"!]*/
    [!NOCODE!][!//
      [!VAR "InselFrequency" = "num:i(0)"!][!//
      [!VAR "INSELFREQ" = "num:i(0)"!][!//
      [!VAR "TempVar" = "num:i(0)"!][!//
      [!VAR "TempVal" = "./McuSystemPllSettingConfig/McuPllInputSrcSelection"!][!//
      [!VAR "TempVal" = "text:split($TempVal,'SEL')[3]"!][!//
      [!IF "$TempVal = num:i(0)"!][!//
        [!VAR "InselFrequency" = "$BackupFrequency"!][!//
        [!VAR "INSELFREQ" = "$FBACK"!][!//
      [!ELSEIF "$TempVal = num:i(1)"!][!//
        [!VAR "InselFrequency" = "$OscFrequency"!][!//
        [!VAR "INSELFREQ" = "$OSCFREQ"!][!//
      [!ELSEIF "$TempVal = num:i(2)"!][!//
        [!VAR "InselFrequency" = "$SysClkFrequency"!][!//
        [!VAR "INSELFREQ" = "$SYSCLKFREQ"!][!//
      [!ENDIF!][!//
      [!/* Pll input source clk selection */!][!//
      [!IF "./McuSystemPllSettingConfig/McuPllInputSrcSelection = 'OSC_CLOCK_SRC_SELECT_SEL1'"!][!//
        [!IF "../../../../McuGeneralConfiguration/McuOscillatorMode = 'OSC_DISABLED_MODE_SEL3'"!][!//
          [!ERROR!][!//
            Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: Mcu PLL input clock source is selected as Oscillator clock, whereas Oscillator is disabled.
          [!ENDERROR!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!IF "./McuPllDistributionSettingConfig/McuClockDistributionInpClockSel = 'PLL_INPUT_CLOCK_SRC_SELECT_SEL1'"!][!//
        [!/*Verify Clock parameters for proper range and plausibility check*/!][!//
        [!/* Verify SYSPLL DCO frequencies */!][!//
        [!VAR "TempVar" = "round(num:i($InselFrequency div (./McuSystemPllSettingConfig/McuSystemPllPDivider+1)))"!][!//
        [!IF "($TempVar < ecu:get('Mcu.SysFoscByPMinFrequency')) or ($TempVar > ecu:get('Mcu.SysFoscByPMaxFrequency'))"!][!//
          [!ERROR!][!//
            Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: The system PLL DCO input frequency shall be in valid range of 10Mhz to 40Mhz. Check the P divider value/input source value.
          [!ENDERROR!][!//
        [!ENDIF!][!//
        [!VAR "TempVar" = "round(num:i(($InselFrequency * (./McuSystemPllSettingConfig/McuSystemPllNDivider+1)) div (./McuSystemPllSettingConfig/McuSystemPllPDivider+1)))"!][!//
        [!IF "($TempVar < ecu:get('Mcu.SysPllDcoBaseMinFrequency')) or ($TempVar > ecu:get('Mcu.SysPllDcoBaseMaxFrequency'))"!][!//
          [!ERROR!][!//
            Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: The system PLL DCO frequency shall be in valid range 400Mhz to 800Mhz. check the combination chosen for P and N divider values
          [!ENDERROR!][!//
        [!ENDIF!][!//
          [!/* Calculate SYSPLL Backup K2 Divider value */!][!//
          [!VAR "KDivVal" = "round(num:i(($INSELFREQ * (./McuSystemPllSettingConfig/McuSystemPllNDivider+1)) div ((./McuSystemPllSettingConfig/McuSystemPllPDivider+1)*($FBACK))))"!][!//
          [!VAR "TempVar" = "round(num:i(($InselFrequency * (./McuSystemPllSettingConfig/McuSystemPllNDivider+1)) div ((./McuSystemPllSettingConfig/McuSystemPllPDivider+1)*$KDivVal)))"!][!//
          [!IF "($TempVar > (($FBACK + num:i(20)) * num:i(1000000))) or ($TempVar < (($FBACK - num:i(20)) * num:i(1000000)))"!][!//
            [!ERROR!][!//
              Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: The system Backup frequency can't be reached with configured.
            [!ENDERROR!][!//
          [!ENDIF!][!//
          [!IF "$KDivVal > num:i(8)"!][!//
            [!ERROR!][!//
              Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: No backup clock (100Mhz) frequency can be reached by selected PDIV and NDIV combination.
            [!ENDERROR!][!//
          [!ENDIF!][!//
          [!VAR "BackupFreqKDiv" = "bit:or($BackupFreqKDiv,bit:shl(($KDivVal - num:i(1)),num:i(0)))"!][!//
          [!/* Verify McuClockReferencePointFrequency0 */!][!//
          [!IF "(./McuSystemPllSettingConfig/McuClockReferencePointFrequency0 < ecu:get('Mcu.FSysPllMinFrequency')) or (./McuSystemPllSettingConfig/McuClockReferencePointFrequency0 > ecu:get('Mcu.FSysPllMaxFrequency'))"!][!//
            [!ERROR!][!//
              Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!][!"$McuVariantName"!]: The parameter McuClockReferencePointFrequency0 should be in the proper valid range. 20Mhz to 300Mhz.
            [!ENDERROR!][!//
          [!ENDIF!][!//
          [!VAR "TempVar" = "round(num:i(($InselFrequency * (./McuSystemPllSettingConfig/McuSystemPllNDivider+1)) div ((./McuSystemPllSettingConfig/McuSystemPllPDivider+1)*(./McuSystemPllSettingConfig/McuSystemPllK2Divider+1))))"!][!//
          [!IF "($TempVar != ./McuSystemPllSettingConfig/McuClockReferencePointFrequency0)"!][!//
            [!ERROR!][!//
              Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: The system PLL frequency, McuClockReferencePointFrequency0 does not match with the divider values configured in the parameters McuPllPDivider, McuPllNDivider, McuPllK2Divider and McuMainOscillatorFrequency (which is under McuGeneralConfiguration). The formula for calculation is McuClockReferencePointFrequency0 = (((McuPllNDivider+1)*(McuMainOscillatorFrequency)) / ((McuPllPDivider+1)*(McuPllK2Divider+1))).
            [!ENDERROR!][!//
          [!ENDIF!][!//
          [!/* Verify PERPLL DCO frequencies */!][!//
          [!VAR "TempVar" = "round(num:i($InselFrequency div (./McuPeripheralPllSettingConfig/McuPeripheralPllPDivider+1)))"!][!//
          [!IF "($TempVar < ecu:get('Mcu.PerPllFoscByPMinFrequency')) or ($TempVar > ecu:get('Mcu.PerPllFoscByPMaxFrequency'))"!][!//
            [!ERROR!][!//
              Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: The peripheral PLL oscillator frquency shall be in valid range 10Mhz to 40Mhz. Check the P divider value.
            [!ENDERROR!][!//
          [!ENDIF!][!//
          [!VAR "TempVar" = "round(num:i(($InselFrequency * (./McuPeripheralPllSettingConfig/McuPeripheralPllNDivider+1)) div (./McuPeripheralPllSettingConfig/McuPeripheralPllPDivider+1)))"!][!//
          [!IF "($TempVar < ecu:get('Mcu.PerPllDcoBaseMinFrequency')) or ($TempVar > ecu:get('Mcu.PerPllDcoBaseMaxFrequency'))"!][!//
            [!ERROR!][!//
              Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: The peripheral PLL DCO frequency shall be in valid range 400Mhz to 800Mhz. check the combination chosen for P and N divider values
            [!ENDERROR!][!//
          [!ENDIF!][!//
          [!/* Verify McuClockReferencePointFrequency1 */!][!//
          [!IF "(./McuPeripheralPllSettingConfig/McuClockReferencePointFrequency1 < ecu:get('Mcu.FPerPll1MinFrequency')) or (./McuPeripheralPllSettingConfig/McuClockReferencePointFrequency1 > ecu:get('Mcu.FPerPll1MaxFrequency'))"!][!//
            [!ERROR!][!//
              Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: The parameter McuClockReferencePointFrequency1 should be in the proper valid range. 20Mhz to 320Mhz.
            [!ENDERROR!][!//
          [!ENDIF!][!//
          [!VAR "TempVar" = "num:i(text:split(./McuPeripheralPllSettingConfig/McuFreqSource1ClockDivSelect,'SEL')[2])"!][!//
          [!IF "$TempVar = num:i(0)"!][!//
            [!VAR "TempVar" = "round(num:i(($InselFrequency * (./McuPeripheralPllSettingConfig/McuPeripheralPllNDivider+1)) div (num:i(2) * (./McuPeripheralPllSettingConfig/McuPeripheralPllPDivider+1)*(./McuPeripheralPllSettingConfig/McuPeripheralPllK2Divider+1))))"!][!//
            [!IF "$TempVar != ./McuPeripheralPllSettingConfig/McuClockReferencePointFrequency1"!][!//
              [!ERROR!][!//
                Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: The peripheral PLL1 frequency, McuClockReferencePointFrequency1 does not match with the divider values configured in the parameters McuPllPDivider, McuPllNDivider, McuPllK2Divider and McuMainOscillatorFrequency (which is under McuGeneralConfiguration). The formula for calculation is McuClockReferencePointFrequency1 = (((McuPllNDivider+1)*(McuMainOscillatorFrequency)) / ((McuPllPDivider+1)*(McuPllK2Divider+1))).
              [!ENDERROR!][!//
            [!ENDIF!][!//
            [!/* Calculate PERPLL Backup K2 Divider value */!][!//
            [!VAR "KDivVal" = "round(num:i(($INSELFREQ * (./McuPeripheralPllSettingConfig/McuPeripheralPllNDivider+1)) div (num:i(2) * (./McuPeripheralPllSettingConfig/McuPeripheralPllPDivider+1)*($FBACK))))"!][!//
            [!VAR "TempVar" = "round(num:i(($InselFrequency * (./McuPeripheralPllSettingConfig/McuPeripheralPllNDivider+1)) div (num:i(2) * (./McuPeripheralPllSettingConfig/McuPeripheralPllPDivider+1)*$KDivVal)))"!][!//
            [!IF "($TempVar > (($FBACK + num:i(20)) * num:i(1000000)))or($TempVar < (($FBACK - num:i(20)) * num:i(1000000)))"!][!//
              [!ERROR!][!//
                Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: The PLL Backup frequency can't be reached with configured PERPLL P and N value.
              [!ENDERROR!][!//
            [!ENDIF!][!//
            [!IF "$KDivVal > num:i(8)"!][!//
              [!ERROR!][!//
                Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: No backup clock (100Mhz) frequency can be reached by selected PDIV and NDIV combination.
              [!ENDERROR!][!//
            [!ENDIF!][!//
            [!VAR "BackupFreqKDiv" = "bit:or($BackupFreqKDiv,bit:shl(($KDivVal - num:i(1)),num:i(4)))"!][!//!][!//
          [!ELSE!][!//
            [!VAR "TempVar" = "round(num:i(($InselFrequency * (./McuPeripheralPllSettingConfig/McuPeripheralPllNDivider+1)) div ((./McuPeripheralPllSettingConfig/McuPeripheralPllPDivider+1)*(./McuPeripheralPllSettingConfig/McuPeripheralPllK2Divider+1))))"!][!//
            [!IF "($TempVar != ./McuPeripheralPllSettingConfig/McuClockReferencePointFrequency1)"!][!//
              [!ERROR!][!//
                Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: The peripheral PLL1 frequency, McuClockReferencePointFrequency1 does not match with the divider values configured in the parameters McuPllPDivider, McuPllNDivider, McuPllK2Divider and McuMainOscillatorFrequency (which is under McuGeneralConfiguration). The formula for calculation is McuClockReferencePointFrequency1 = (((McuPllNDivider+1)*(McuMainOscillatorFrequency)) / ((McuPllPDivider+1)*(McuPllK2Divider+1))).
              [!ENDERROR!][!//
            [!ENDIF!][!//
            [!/* Calculate PERPLL Backup K2 Divider value */!][!//
            [!VAR "KDivVal" = "round(num:i(($INSELFREQ * (./McuPeripheralPllSettingConfig/McuPeripheralPllNDivider+1)) div ((./McuPeripheralPllSettingConfig/McuPeripheralPllPDivider+1)*($FBACK))))"!][!//
            [!VAR "TempVar" = "round(num:i(($InselFrequency * (./McuPeripheralPllSettingConfig/McuPeripheralPllNDivider+1)) div ((./McuPeripheralPllSettingConfig/McuPeripheralPllPDivider+1)*$KDivVal)))"!][!//
            [!IF "($TempVar > (($FBACK + num:i(20)) * num:i(1000000)))or($TempVar < (($FBACK - num:i(20)) * num:i(1000000)))"!][!//
              [!ERROR!][!//
                Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: The PLL Backup frequency can't be reached with configured PERPLL P and N value.
              [!ENDERROR!][!//
            [!ENDIF!][!//
            [!IF "$KDivVal > num:i(8)"!][!//
              [!ERROR!][!//
                Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: No backup clock (100Mhz) frequency can be reached by selected PDIV and NDIV combination.
              [!ENDERROR!][!//
            [!ENDIF!][!//
            [!VAR "BackupFreqKDiv" = "bit:or($BackupFreqKDiv,bit:shl(($KDivVal - num:i(1)),num:i(4)))"!][!//!][!//
          [!ENDIF!][!//
          [!/* Verify McuClockReferencePointFrequency2 */!][!//
          [!IF "(./McuPeripheralPllSettingConfig/McuClockReferencePointFrequency2 < ecu:get('Mcu.FPerPll2MinFrequency')) or (./McuPeripheralPllSettingConfig/McuClockReferencePointFrequency2 > ecu:get('Mcu.FPerPll2MaxFrequency'))"!][!//
            [!ERROR!][!//
              Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: The parameter McuClockReferencePointFrequency2 should be in the proper valid range. 20Mhz to 200Mhz.
            [!ENDERROR!][!//
          [!ENDIF!][!//
          [!VAR "TempVar" = "num:i(text:split(./McuPeripheralPllSettingConfig/McuPll2DivSelect,'SEL')[2])"!][!//
          [!IF "ecu:get('Mcu.PerPllErrataApplicable') = 'true'"!][!//
            [!IF "$TempVar = num:i(1)"!][!//
              [!WARNING!][!//
                The option "MCU_K3_DIV_FACTOR_BYPASSED_SEL1" shall not be used for McuPll2DivSelect in devices with Peripheral PLL HW design weakness. This option may lead to physical damage over lifetime for the parts driven by this PLL. For more details and list of affected devices, please refer to PER_PLL_TC.001. Ignore warning if not applicable to the derivative step. 
              [!ENDWARNING!][!//
            [!ENDIF!][!//
          [!ENDIF!][!//
          [!IF "$TempVar = num:i(0)"!][!//
            [!VAR "TempVar" = "round(num:i(($InselFrequency * (./McuPeripheralPllSettingConfig/McuPeripheralPllNDivider+1)) div ((1.6)*(./McuPeripheralPllSettingConfig/McuPeripheralPllPDivider+1)*(./McuPeripheralPllSettingConfig/McuPeripheralPllK3Divider+1))))"!][!//
            [!IF "($TempVar != ./McuPeripheralPllSettingConfig/McuClockReferencePointFrequency2)"!][!//
              [!ERROR!][!//
                Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: The peripheral PLL2 frequency, McuClockReferencePointFrequency2 does not match with the divider values configured in the parameters McuPllPDivider, McuPllNDivider, McuPllK3Divider and McuMainOscillatorFrequency (which is under McuGeneralConfiguration). The formula for calculation is McuClockReferencePointFrequency2 = (((McuPllNDivider+1)*(McuMainOscillatorFrequency)) / ((McuPllPDivider+1)*(McuPllK3Divider+1)) * DIVBY) where DIVBY = numeric value in McuPll2DivSelect.
              [!ENDERROR!][!//
            [!ENDIF!][!//
            [!/* Calculate PERPLL Backup K3 Divider value */!][!//
            [!VAR "KDivVal" = "round(num:i(($INSELFREQ * (./McuPeripheralPllSettingConfig/McuPeripheralPllNDivider+1)) div ((1.6)*(./McuPeripheralPllSettingConfig/McuPeripheralPllPDivider+1)*($FBACK))))"!][!//
            [!VAR "TempVar" = "round(num:i(($InselFrequency * (./McuPeripheralPllSettingConfig/McuPeripheralPllNDivider+1)) div (1.6*(./McuPeripheralPllSettingConfig/McuPeripheralPllPDivider+1)*$KDivVal)))"!][!//
            [!IF "($TempVar > (($FBACK + num:i(20)) * num:i(1000000))) and ($TempVar < (($FBACK - num:i(20)) * num:i(1000000)))"!][!//
              [!ERROR!][!//
                Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: The PLL Backup frequency can't be reached with configured PERPLL P and N value.
              [!ENDERROR!][!//
            [!ENDIF!][!//
            [!IF "$KDivVal > num:i(8)"!][!//
            [!ERROR!][!//
              Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: No backup clock (100Mhz) frequency can be reached by selected PDIV and NDIV combination.
            [!ENDERROR!][!//
          [!ENDIF!][!//
            [!VAR "BackupFreqKDiv" = "bit:or($BackupFreqKDiv,bit:shl(($KDivVal - num:i(1)),num:i(8)))"!][!//!][!//
          [!ELSE!][!//
            [!VAR "TempVar" = "round(num:i(($InselFrequency * (./McuPeripheralPllSettingConfig/McuPeripheralPllNDivider+1)) div ((num:i(2))*(./McuPeripheralPllSettingConfig/McuPeripheralPllPDivider+1)*(./McuPeripheralPllSettingConfig/McuPeripheralPllK3Divider+1))))"!][!//
            [!IF "($TempVar != ./McuPeripheralPllSettingConfig/McuClockReferencePointFrequency2)"!][!//
              [!ERROR!][!//
                Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: The peripheral PLL2 frequency, McuClockReferencePointFrequency2 does not match with the divider values configured in the parameters McuPllPDivider, McuPllNDivider, McuPllK3Divider and McuMainOscillatorFrequency (which is under McuGeneralConfiguration). The formula for calculation is McuClockReferencePointFrequency2 = (((McuPllNDivider+1)*(McuMainOscillatorFrequency)) / ((McuPllPDivider+1)*(McuPllK3Divider+1)) * DIVBY) where DIVBY = numeric value in McuPll2DivSelect.
              [!ENDERROR!][!//
            [!ENDIF!][!//
            [!/* Calculate PERPLL Backup K3 Divider value */!][!//
            [!VAR "KDivVal" = "round(num:i(($INSELFREQ * (./McuPeripheralPllSettingConfig/McuPeripheralPllNDivider+1)) div (num:i(2) * (./McuPeripheralPllSettingConfig/McuPeripheralPllPDivider+1)*($FBACK))))"!][!//
            [!VAR "TempVar" = "round(num:i(($InselFrequency * (./McuPeripheralPllSettingConfig/McuPeripheralPllNDivider+1)) div (num:i(2) * (./McuPeripheralPllSettingConfig/McuPeripheralPllPDivider+1)*$KDivVal)))"!][!//
            [!IF "($TempVar > (($FBACK + num:i(20)) * num:i(1000000)))and($TempVar < (($FBACK - num:i(20)) * num:i(1000000)))"!][!//
              [!ERROR!][!//
                Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: The PLL Backup frequency can't be reached with configured PERPLL P and N value.
              [!ENDERROR!][!//
            [!ENDIF!][!//
            [!IF "$KDivVal > num:i(8)"!][!//
              [!ERROR!][!//
                Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: No backup clock (100Mhz) frequency can be reached by selected PDIV and NDIV combination.
              [!ENDERROR!][!//
            [!ENDIF!][!//
            [!VAR "BackupFreqKDiv" = "bit:or($BackupFreqKDiv,bit:shl(($KDivVal - num:i(1)),num:i(8)))"!][!//!][!//
          [!ENDIF!][!//
        [!/* Verify McuHsctFrequency */!][!//
        [!IF "./McuPllDistributionSettingConfig/McuHsctFrequency != round(num:i(($InselFrequency * (./McuPeripheralPllSettingConfig/McuPeripheralPllNDivider+1)) div ((./McuPeripheralPllSettingConfig/McuPeripheralPllPDivider+1)*(num:i(2)))))"!][!//
          [!ERROR!][!//
            Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: McuHsctFrequency shall be equal peripheral DCO frequency / 2.
          [!ENDERROR!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!/* Verify McuClockEBUFrequency */!][!//
      [!IF "ecu:get('Mcu.fEBUExists')='true'"!][!//
        [!IF "(./McuPllDistributionSettingConfig/McuEbuClkEnable = 'true')"!][!//
          [!/* Verify McuEBUFrequency if EBU exists in device */!][!//
          [!IF "(./McuPllDistributionSettingConfig/McuEbuFrequency != ./McuPeripheralPllSettingConfig/McuClockReferencePointFrequency1)"!][!//
            [!ERROR!][!//
              Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: McuEbuFrequency must be same as McuClockReferencePointFrequency1.
            [!ENDERROR!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!/* Verify McuADCFrequency */!][!//
      [!IF "(./McuPllDistributionSettingConfig/McuClockDistributionInpClockSel != 'BACKUP_INPUT_CLOCK_SRC_SELECT_SEL0')"!][!//
      [!IF "(./McuPllDistributionSettingConfig/McuAdcFrequency != ./McuPeripheralPllSettingConfig/McuClockReferencePointFrequency1)"!][!//
        [!ERROR!][!//
          Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: McuAdcFrequency must be same as McuClockReferencePointFrequency1.
        [!ENDERROR!][!//
      [!ENDIF!][!//
      [!ENDIF!][//
      [!/* Verify McuERayFrequency */!][!//
      [!IF "ecu:get('Mcu.fERAYExists')='true'"!][!//
        [!IF "(./McuPllDistributionSettingConfig/McuErayClkEnable = 'true')"!][!//
          [!IF "./McuPllDistributionSettingConfig/McuClockDistributionInpClockSel = 'PLL_INPUT_CLOCK_SRC_SELECT_SEL1'"!][!//
            [!IF "(./McuPllDistributionSettingConfig/McuErayFrequency != round((./McuPeripheralPllSettingConfig/McuClockReferencePointFrequency1) div num:i(2)))"!][!//
              [!ERROR!][!//
                Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: McuErayFrequency must be same as McuClockReferencePointFrequency1 /2 .  Else Disable the Eray clock by setting McuErayClkEnable to false.
              [!ENDERROR!][!//
            [!ENDIF!][!//
          [!ENDIF!][!//
          [!IF "./McuPllDistributionSettingConfig/McuErayFrequency != num:i(ecu:get('Mcu.fErayFrequency'))"!][!//
            [!ERROR!][!//
              Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: McuErayFrequency must be fixed at 80 Mhz. Else Disable the Eray clock by setting McuErayClkEnable to false.
            [!ENDERROR!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!/* Check if HSPDM frequencies are enabled or not */!][!//
      [!IF "ecu:get('Mcu.fHSPDMExists')='true'"!][!//
        [!IF "(./McuPllDistributionSettingConfig/McuHspdmClkEnable = 'true')"!][!//
          [!/* Verify McuHspdm160Frequency */!][!//
          [!IF "(./McuPllDistributionSettingConfig/McuHspdm160Frequency != ./McuPeripheralPllSettingConfig/McuClockReferencePointFrequency1)"!][!//
            [!ERROR!][!//
              Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: McuHspdm160Frequency must be same as McuClockReferencePointFrequency1.
            [!ENDERROR!][!//
          [!ENDIF!][!//
          [!/* Verify McuHspdm320Frequency */!][!//
          [!IF "(./McuPllDistributionSettingConfig/McuHspdm320Frequency) != (num:i(./McuPeripheralPllSettingConfig/McuClockReferencePointFrequency1) * (num:i(num:i(text:split(node:fallback(./McuPeripheralPllSettingConfig/McuFreqSource1ClockDivSelect,'_SEL0'),'SEL')[2]) = num:i(0)) + num:i(1)))"!][!//
            [!ERROR!][!//
              Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: McuHspdm320Frequency must be same as fPLL1 or fBACKUP(based on McuClockDistributionInpClockSel) .
            [!ENDERROR!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!/* Verify McuReferenceFrequency1 */!][!//
      [!IF "(./McuPllDistributionSettingConfig/McuReferenceFrequency1 != round((./McuSystemPllSettingConfig/McuClockReferencePointFrequency0) div num:i(24)))"!][!//
        [!ERROR!][!//
          Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: McuReferenceFrequency1 must be same as McuClockReferencePointFrequency0 / 24
        [!ENDERROR!][!//
      [!ENDIF!][!//
      [!/* Verify McuReferenceFrequency2 */!][!//
      [!IF "(./McuPllDistributionSettingConfig/McuReferenceFrequency2 != round((./McuPeripheralPllSettingConfig/McuClockReferencePointFrequency1) div 24))"!][!//
        [!ERROR!][!//
          Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: McuReferenceFrequency2 must be same as McuClockReferencePointFrequency1 / 24
        [!ENDERROR!][!//
      [!ENDIF!][!//
      [!/* External Clock configuration - Ouput 1 */!][!//
      [!VAR "ExternalClockCfg" = "num:i(0)"!]
      [!IF "./McuExternalClockOutputConfig/McuExtClock0Enable = 'true'"!][!//
        [!VAR "ExternalClockCfg" = "bit:or($ExternalClockCfg,bit:shl(num:i(1),num:i(0)))"!][!//
        [!VAR "TempVal" = "./McuExternalClockOutputConfig/McuExtClockOutSel0"!][!//
        [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
        [!VAR "ExternalClockCfg" = "bit:or($ExternalClockCfg,bit:shl($TempVal,num:i(2)))"!][!//
      [!ENDIF!][!//
      [!/* External Clock configuration - Ouput 2 */!][!//
      [!IF "./McuExternalClockOutputConfig/McuExtClock1Enable = 'true'"!][!//
        [!VAR "ExternalClockCfg" = "bit:or($ExternalClockCfg,bit:shl(num:i(1),num:i(16)))"!][!//
        [!IF "./McuExternalClockOutputConfig/McuExtClock1Inverted = 'false'"!][!//
          [!VAR "ExternalClockCfg" = "bit:or($ExternalClockCfg,bit:shl(num:i(1),num:i(17)))"!][!//
        [!ENDIF!][!//
        [!VAR "TempVal" = "./McuExternalClockOutputConfig/McuExtClockOutSel1"!][!//
        [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
        [!VAR "ExternalClockCfg" = "bit:or($ExternalClockCfg,bit:shl($TempVal,num:i(18)))"!][!//
        [!IF "$TempVal = num:i(0)"!][!// fSPB clock is selected as output
          [!VAR "TempVal" = "./McuExternalClockOutputConfig/McuFoutClockDiv"!][!//
          [!VAR "ExternalClockCfg" = "bit:or($ExternalClockCfg,bit:shl((($TempVal) - num:i(1)),num:i(24)))"!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDNOCODE!][!//
  {
    /* System PLL configuration value */
    {
      [!"num:i(text:split(./McuSystemPllSettingConfig/McuPllInputSrcSelection,'SEL')[3])"!]U,
      [!"num:i(./McuSystemPllSettingConfig/McuSystemPllPDivider)"!]U,
      [!"num:i(./McuSystemPllSettingConfig/McuSystemPllNDivider)"!]U,
      [!"num:i(./McuSystemPllSettingConfig/McuSystemPllK2Divider)"!]U,
    [!IF "./McuSystemPllSettingConfig/McuFmPllEnable = 'true'"!][!//
      1U,
      [!VAR "TempVal" = "./McuSystemPllSettingConfig/McuFMPllModAmp"!][!//
      [!VAR "TempVal" = "num:i($INSELFREQ) * num:i(64) * num:i(./McuSystemPllSettingConfig/McuSystemPllNDivider + 1)"!][!//
      [!VAR "TempVal" = "num:f($TempVal) div (num:f(100) * num:f(3.6) * num:f(./McuSystemPllSettingConfig/McuSystemPllPDivider + 1))"!][!//
      [!VAR "McuModulationAmplitude" = "num:f(./McuSystemPllSettingConfig/McuFMPllModAmp) * num:f($TempVal)"!][!//
      [!IF "$McuModulationAmplitude > num:i(1023)"!]
        [!ERROR!][!//
          Config Error [!"$McuVariantName"!]: FMPLL modulation amplitude exceed maximum value of 1023. It is calculated based on McuFMPllModAmp and PLLFREQ
        [!ENDERROR!][!//
      [!ENDIF!][!//
      [!VAR "McuMODCFG_15_10" = "ecu:get('Mcu.SysPllModulationConfiguration')"!][!//
      [!"num:i(bit:or((bit:shl($McuMODCFG_15_10,10)),num:i($McuModulationAmplitude)))"!]U
    [!ELSE!][!//
      0U,
      0U
    [!ENDIF!][!//
    },
    /* Peripheral PLL configuration value */
    {
      [!"num:i(./McuPeripheralPllSettingConfig/McuPeripheralPllNDivider)"!]U,
      [!"num:i(./McuPeripheralPllSettingConfig/McuPeripheralPllPDivider)"!]U,
      [!"num:i(./McuPeripheralPllSettingConfig/McuPeripheralPllK2Divider)"!]U,
      [!"num:i(./McuPeripheralPllSettingConfig/McuPeripheralPllK3Divider)"!]U,
      [!"num:i(text:split(./McuPeripheralPllSettingConfig/McuPll2DivSelect,'SEL')[2])"!]U,
      0U
    },
    /* System PLL K2 divider increment step change delay */
    [!"num:i(./McuSystemPllSettingConfig/McuSysPllK2DivStepUpChangeDelay)"!]U,
    /* System PLL K2 divider decrement step change delay */
    [!"num:i(./McuSystemPllSettingConfig/McuSysPllK2DivStepDownChangeDelay)"!]U,
    /* Peripheral PLL K2 divider step change increment */
    [!"num:i(./McuPeripheralPllSettingConfig/McuPerPllK2DivStepUpChangeDelay)"!]U,
    /* Peripheral PLL K2 divider step change decrement */
    [!"num:i(./McuPeripheralPllSettingConfig/McuPerPllK2DivStepDownChangeDelay)"!]U,
    /* Peripheral PLL K3 divider step change increment */
    [!"num:i(./McuPeripheralPllSettingConfig/McuPerPllK3DivStepUpChangeDelay)"!]U,
    /* Peripheral PLL K3 divider step change decrement */
    [!"num:i(./McuPeripheralPllSettingConfig/McuPerPllK3DivStepDownChangeDelay)"!]U,
    /* PLL clock divider configuration pointer */
    &Mcu_kPllDistributionConfiguration[!"$McuConfigShortName"!]_[!"string($ClkIdx)"!],
    /* External Clock configuration */
    [!"num:inttohex($ExternalClockCfg,8)"!]U,
    /* Backup frequency K Divider value for both PLLs */
    [!"num:inttohex($BackupFreqKDiv,4)"!]U,
    /* Converter Control Phase Synchronization configuration */
    [!"num:inttohex(num:i(text:split(./McuPllDistributionSettingConfig/McuConvCtrlPhaseSynchConf,'SEL')[2]),2)"!]U,
  },[!IF "$ClkIndex != (num:i($ClkCfgCount)- 1)"!],[!ENDIF!]/*[!"node:name(.)"!]*/
  [!ENDSELECT!]
[!ENDFOR!][!//
};
[!/*[/cover]*/!][!//
/*
  Ptr to RAM Section in config structure
  Container: McuRamSectorSettingConf
  Multiplicity: 1 - *
  Configuration: RAM Section Id
  This id corresponds to the container name of the McuRAMSettingConfiguration.
  Use this as the parameter for API: Mcu_InitRamSection
*/

[!IF "num:i(count(node:ref($ModulePath)/McuRamSectorSettingConf/*)) > num:i(0)"!][!//
[!VAR "RamSecCount" = "num:i(count(node:ref($ModulePath)/McuRamSectorSettingConf/*))"!][!//
[!/*[cover parentID={6BB1E94E-3B5A-484e-B433-20FEE2646B7F}]*/!][!//
static const Mcu_RamConfigType Mcu_kRamConfiguration[!"$McuConfigShortName"!][[!"num:i($RamSecCount)"!]] =
{
  [!FOR "RamSecIdx" = "num:i(0)" TO "num:i($RamSecCount - num:i(1))"!][!//
  [!SELECT "node:ref($ModulePath)/McuRamSectorSettingConf/*[McuRamSectorSettingId = num:i($RamSecIdx)]"!][!//
  /*[!"node:name(.)"!]*/
  {
    [!NOCODE!][!//
      [!/*Check for ram section base address and size within any possible ram address range*/!][!//
      [!VAR "BaseAdr" = "./McuRamSectionBaseAddress"!][!//
      [!/*To Check non-cached LMU region*/!][!//
    [!IF "bit:shr($BaseAdr,num:i(28)) = num:i(11)"!][!//
    [!VAR "BaseAdr" = "bit:bitclear($BaseAdr,num:i(29))"!][!//
      [!ENDIF!][!//
      [!VAR "Size" = "./McuRamSectionSize"!][!//
      [!VAR "ArMinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
      [!VAR "RamDataVal" = "./McuRamDefaultValue"!][!//
      [!IF "$ArMinorVersion = num:i(4)"!][!//
        [!VAR "WriteSize" = "./McuRamSectionWriteSize"!][!//
        [!VAR "RamData" = "num:i(0)"!][!//
        [!FOR "RamVal" = "num:i(0)" TO "num:i($WriteSize - num:i(1))"!][!//
          [!VAR "RamData" = "bit:or($RamData,bit:shl(num:i($RamDataVal),num:i(num:i(8)*num:i($RamVal))))"!][//
        [!ENDFOR!][!//
      [!ENDIF!][!//
      [!IF "not((($BaseAdr >= ecu:get('Mcu.CPU0LMUAddStart')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.CPU0LMUAddEnd'))) or
                (($BaseAdr >= ecu:get('Mcu.CPU0DSPRAddStart')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.CPU0DSPRAddEnd'))) or
                (($BaseAdr >= ecu:get('Mcu.CPU0PSPRAddStart')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.CPU0PSPRAddEnd'))) or
                (($CoresAvailable >= num:i(2)) and ($BaseAdr >= ecu:get('Mcu.CPU1LMUAddStart')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.CPU1LMUAddEnd'))) or
                (($CoresAvailable >= num:i(2)) and ($BaseAdr >= ecu:get('Mcu.CPU1DSPRAddStart')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.CPU1DSPRAddEnd'))) or
                (($CoresAvailable >= num:i(2)) and ($BaseAdr >= ecu:get('Mcu.CPU1PSPRAddStart')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.CPU1PSPRAddEnd'))) or
                (($CoresAvailable >= num:i(3)) and ($BaseAdr >= ecu:get('Mcu.CPU2LMUAddStart')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.CPU2LMUAddEnd'))) or
                (($CoresAvailable >= num:i(3)) and ($BaseAdr >= ecu:get('Mcu.CPU2DSPRAddStart')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.CPU2DSPRAddEnd'))) or
                (($CoresAvailable >= num:i(3)) and ($BaseAdr >= ecu:get('Mcu.CPU2PSPRAddStart')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.CPU2PSPRAddEnd'))) or
                (($CoresAvailable >= num:i(4)) and ($BaseAdr >= ecu:get('Mcu.CPU3LMUAddStart')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.CPU3LMUAddEnd'))) or
                (($CoresAvailable >= num:i(4)) and ($BaseAdr >= ecu:get('Mcu.CPU3DSPRAddStart')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.CPU3DSPRAddEnd'))) or
                (($CoresAvailable >= num:i(4)) and ($BaseAdr >= ecu:get('Mcu.CPU3PSPRAddStart')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.CPU3PSPRAddEnd'))) or
                (($CoresAvailable >= num:i(5)) and ($BaseAdr >= ecu:get('Mcu.CPU4LMUAddStart')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.CPU4LMUAddEnd'))) or
                (($CoresAvailable >= num:i(5)) and ($BaseAdr >= ecu:get('Mcu.CPU4DSPRAddStart')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.CPU4DSPRAddEnd'))) or
                (($CoresAvailable >= num:i(5)) and ($BaseAdr >= ecu:get('Mcu.CPU4PSPRAddStart')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.CPU4PSPRAddEnd'))) or
                (($CoresAvailable >= num:i(6)) and ($BaseAdr >= ecu:get('Mcu.CPU5LMUAddStart')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.CPU5LMUAddEnd'))) or
                (($CoresAvailable >= num:i(6)) and ($BaseAdr >= ecu:get('Mcu.CPU5DSPRAddStart')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.CPU5DSPRAddEnd'))) or
                (($CoresAvailable >= num:i(6)) and ($BaseAdr >= ecu:get('Mcu.CPU5PSPRAddStart')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.CPU5PSPRAddEnd'))) or
                ((ecu:get('Mcu.fLMU0Exists') = 'true') and ($BaseAdr >= ecu:get('Mcu.LMU0AddStart')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.LMU0AddEnd'))) or
                ((ecu:get('Mcu.fLMU1Exists') = 'true') and ($BaseAdr >= ecu:get('Mcu.LMU1AddStart')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.LMU1AddEnd'))) or
                ((ecu:get('Mcu.fLMU2Exists') = 'true') and ($BaseAdr >= ecu:get('Mcu.LMU2AddStart')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.LMU2AddEnd'))) or
                ((ecu:get('Mcu.fLMU3Exists') = 'true') and ($BaseAdr >= ecu:get('Mcu.LMU3AddStart')) and (($BaseAdr+$Size - num:i(1)) <= ecu:get('Mcu.LMU3AddEnd'))))"!][!//
        [!ERROR!][!//
          Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: Ram Base address or size is out of possible ram ranges.
        [!ENDERROR!][!//
      [!ENDIF!][!//
      [!IF "$ArMinorVersion = num:i(4)"!][!//
        [!VAR "Mulp" = "num:i(num:i($Size) mod num:i($WriteSize))"!][!//
        [!IF "($WriteSize > $Size) or ($Mulp != num:i(0))"!][!//
          [!/*[cover parentID={D37DC2F3-D905-4ba7-8B1E-1588263E6F4C}]*/!][!//
          [!ERROR!][!//
            Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: RAM section size cannot be smaller than the write size or a non-multiple of RAM write size. Please configure a value that is multiple of RAM write size.
          [!ENDERROR!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDNOCODE!][!//
    /* RAM Section Configuration: [!"node:name(.)"!] */
    /* RAM section base address */
    /* MISRA2012_RULE_11_6_JUSTIFICATION: Memory address is generated as a numerical 
       value from property file and in code, it is accessed as a pointer to the
       RAM address. Hence an explicit typecast from integer to uint32 based pointer.
       */
    (Mcu_RamBaseAdrType)[!"num:inttohex(./McuRamSectionBaseAddress,num:i(8))"!]U,
    /* RAM section size */
    (Mcu_RamSizeType)[!"num:inttohex(./McuRamSectionSize,num:i(8))"!]U,
    /* Default initialization value */
    (Mcu_RamPrstDatType)[!"num:inttohex($RamDataVal,num:i(2))"!]U,
    [!IF "$ArMinorVersion = num:i(4)"!][!//
    /*Prepared Ram Data to be written at once*/
    (uint64)[!"num:inttohex($RamData,num:i(16))"!]U,
    /* RAM section write size */
    (Mcu_RamWriteSizeType)[!"num:inttohex(./McuRamSectionWriteSize,num:i(8))"!]U
    [!ENDIF!][!//
  }[!IF "$RamSecIdx < num:i($RamSecCount - 1)"!],[!ENDIF!]
  [!ENDSELECT!][!//
  [!ENDFOR!][!//

};
[!ENDIF!][!//
[!/*[/cover]*/!][!//
[!VAR "McuModeIndex" = "num:i(0)"!][!//
[!VAR "McuStandbyModeEnable" = "num:i(0)"!][!//
[!NOCODE!][!//
  [!VAR "McuMode" = "num:i(0)"!]
  [!VAR "EvrcLowPowerMode" = "num:i(0)"!]
  [!VAR "ModeSettingConfig" = "num:i(count(node:ref($ModulePath)/McuModeSettingConf/*))"!]
  [!FOR "ModeIndex" = "num:i(0)" TO "($ModeSettingConfig - num:i(1))"!][!//
    [!VAR "McuModeConfig" = "num:i(node:ref($ModulePath)/McuModeSettingConf/*[$ModeIndex+1]/McuMode)"!][!//
    [!VAR "McuMode" = "bit:or($McuMode,bit:shl(num:i(1),$McuModeConfig))"!][!//
    [!IF "$McuModeConfig = num:i(1)"!][!//
      [!VAR "TempVal" = "node:ref($ModulePath)/McuModeSettingConf/*[$ModeIndex+1]/McuEvrcLPMOnSleepReqEnable"!][!//
      [!IF "$TempVal = 'true'"!][!//
        [!VAR "EvrcLowPowerMode" = "num:i(1)"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!IF "$McuModeConfig = num:i(2)"!][!//
      [!VAR "McuStandbyModeEnable" = "num:i(1)"!][!//
      [!VAR "McuModeIndex" = "num:i($ModeIndex)"!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
[!ENDNOCODE!][!//
/*
  Standby Mode config structure for Low Power (Standby) Mode Configuration:
  [!"substring-before((substring-after(node:path(.),concat($ModulePath,'/'))),'/McuStandbySettingConf')"!]
*/
[!/*[cover parentID={18F5A6DB-D93A-4bd9-B159-660992C96E31}]*/!][!//
static const Mcu_LowPowerModeType  Mcu_kLowPowerModeConfiguration[!"$McuConfigShortName"!] =
{
[!NOCODE!][!//
  [!VAR "PMSWCR0Value" = "num:i(0)"!][!//
  [!VAR "PMSWCR3Value" = "num:i(0)"!][!//
  [!VAR "PMSWCR4Value" = "num:i(0)"!][!//
  [!VAR "PMSWCR5Value" = "num:i(0)"!][!//
  [!VAR "EVRUVMONValue" = "num:i(0)"!][!//
  [!VAR "EVRMONCTRLValue" = "num:i(0)"!][!//
  [!VAR "StdbyRamEnable" = "num:i(0)"!][!//
  [!IF "$McuStandbyModeEnable = num:i(1)"!][!//
    [!SELECT "node:ref($ModulePath)/McuModeSettingConf/*[$McuModeIndex+1]/McuStdbyModeSettingConf"!][!//
      [!/* Calculate  PMSWCR0 register value */!][!//
      [!VAR "OutVal" = "num:i(0)"!][!//
      [!/*McuStdbyModeESR0WakeupEnable*/!][!//
      [!IF "./McuStdbyModeESR0Conf/McuStdbyModeESR0WakeupEnable = 'true'"!][!//
        [!VAR "PMSWCR0Value" = "bit:or($PMSWCR0Value,bit:shl(num:i(1),num:i(24)))"!][!//
        [!CALL "Mcu_CG_GetBooleanVal","InpVal" = "./McuStdbyModeESR0Conf/McuStdbyModeESR0FltEnable"!][!//
        [!VAR "PMSWCR0Value" = "bit:or($PMSWCR0Value,bit:shl($OutVal,num:i(4)))"!][!//
        [!VAR "TempVal" = "./McuStdbyModeESR0Conf/McuStdbyModeESR0EdgeDetection"!][!//
        [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
        [!VAR "PMSWCR0Value" = "bit:or($PMSWCR0Value,bit:shl($TempVal,num:i(5)))"!][!//
      [!ENDIF!][!//
      [!/*McuStdbyModeESR1WakeupEnable*/!][!//
      [!IF "./McuStdbyModeESR1Conf/McuStdbyModeESR1WakeupEnable = 'true'"!][!//
        [!VAR "PMSWCR0Value" = "bit:or($PMSWCR0Value,bit:shl(num:i(1),num:i(25)))"!][!//
        [!CALL "Mcu_CG_GetBooleanVal","InpVal" = "./McuStdbyModeESR1Conf/McuStdbyModeESR1FltEnable"!][!//
        [!VAR "PMSWCR0Value" = "bit:or($PMSWCR0Value,bit:shl($OutVal,num:i(7)))"!][!//
        [!VAR "TempVal" = "./McuStdbyModeESR1Conf/McuStdbyModeESR1EdgeDetection"!][!//
        [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
        [!VAR "PMSWCR0Value" = "bit:or($PMSWCR0Value,bit:shl($TempVal,num:i(8)))"!][!//
      [!ENDIF!][!//
      [!/*McuStdbyModePinAWakeupEnable*/!][!//
      [!IF "./McuStdbyModePinAConf/McuStdbyModePinAWakeupEnable = 'true'"!][!//
        [!VAR "PMSWCR0Value" = "bit:or($PMSWCR0Value,bit:shl(num:i(1),num:i(26)))"!][!//
        [!CALL "Mcu_CG_GetBooleanVal","InpVal" = "./McuStdbyModePinAConf/McuStdbyModePinAFltEnable"!][!//
        [!VAR "PMSWCR0Value" = "bit:or($PMSWCR0Value,bit:shl($OutVal,num:i(10)))"!][!//
        [!VAR "TempVal" = "./McuStdbyModePinAConf/McuStdbyModePinAEdgeDetection"!][!//
        [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
        [!VAR "PMSWCR0Value" = "bit:or($PMSWCR0Value,bit:shl($TempVal,num:i(11)))"!][!//!][!//
      [!ENDIF!][!//
      [!/*McuStdbyModePinBWakeupEnable*/!][!//
      [!IF "./McuStdbyModePinBConf/McuStdbyModePinBWakeupEnable = 'true'"!][!//
        [!VAR "PMSWCR0Value" = "bit:or($PMSWCR0Value,bit:shl(num:i(1),num:i(27)))"!][!//
        [!CALL "Mcu_CG_GetBooleanVal","InpVal" = "./McuStdbyModePinBConf/McuStdbyModePinBFltEnable"!][!//
        [!VAR "PMSWCR0Value" = "bit:or($PMSWCR0Value,bit:shl($OutVal,num:i(13)))"!][!//
        [!VAR "TempVal" = "./McuStdbyModePinBConf/McuStdbyModePinBEdgeDetection"!][!//
        [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
        [!VAR "PMSWCR0Value" = "bit:or($PMSWCR0Value,bit:shl($TempVal,num:i(14)))"!][!//!][!//
      [!ENDIF!][!//
      [!/*McuStdbyModeRamEnable*/!][!//
      [!VAR "StdbyRamEnable" = "num:i(text:split(./McuStdbyModeRamEnable,'SEL')[2])"!][!//
      [!IF "($StdbyRamEnable > num:i(2))"!][!//
        [!IF "not($CoresAvailable > num:i(1))"!][!//
          [!ERROR!][!//
            Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: standby ram is selected as dLMU, but CPU1 is not available in device.
          [!ENDERROR!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!VAR "PMSWCR0Value" = "bit:or($PMSWCR0Value,bit:shl($StdbyRamEnable,num:i(16)))"!][!//
      [!/*McuStdbyModeBlankingFilterDelay*/!][!//
      [!VAR "TempVal" = "./McuStdbyModeBlankingFilterDelay"!][!//
      [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
      [!VAR "PMSWCR0Value" = "bit:or($PMSWCR0Value,bit:shl($TempVal,num:i(20)))"!][!//!][!//
      [!/*McuStdbyModeEntryOnVEXTRampDown*/!][!//
      [!CALL "Mcu_CG_GetBooleanVal","InpVal" = "./McuStdbyModeVddVextConf/McuStdbyModeEntryOnVEXTRampDown"!][!//
      [!VAR "PMSWCR0Value" = "bit:or($PMSWCR0Value,bit:shl($OutVal,num:i(2)))"!][!//
      [!/*McuStdbyModeEntryOnVDDRampDown*/!][!//
      [!CALL "Mcu_CG_GetBooleanVal","InpVal" = "./McuStdbyModeVddVextConf/McuStdbyModeEntryOnVDDRampDown"!][!//
      [!VAR "PMSWCR0Value" = "bit:or($PMSWCR0Value,bit:shl($OutVal,num:i(3)))"!][!//!][!//
      [!/*McuStdbyModeWakeupFromEVR*/!][!//
      [!CALL "Mcu_CG_GetBooleanVal","InpVal" = "./McuStdbyModeWakeupFromEVR"!][!//
      [!VAR "PMSWCR0Value" = "bit:or($PMSWCR0Value,bit:shl($OutVal,num:i(28)))"!][!//
      [!/*McuStdbyModeWakeupFromSCR*/!][!//
      [!CALL "Mcu_CG_GetBooleanVal","InpVal" = "./McuStdbyModeWakeupFromSCR"!][!//
      [!VAR "PMSWCR0Value" = "bit:or($PMSWCR0Value,bit:shl($OutVal,num:i(29)))"!][!//!][!//
      [!/*McuStdbyModeWakeupFromPORST*/!][!//
      [!CALL "Mcu_CG_GetBooleanVal","InpVal" = "./McuStdbyModeWakeupFromPORST"!][!//
      [!VAR "PMSWCR0Value" = "bit:or($PMSWCR0Value,bit:shl($OutVal,num:i(30)))"!][!//!][!//
      [!/*McuStdbyModeClkSelection*/!][!//
      [!VAR "TempVal" = "./McuStdbyModeClkSelection"!][!//
      [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
      [!VAR "PMSWCR4Value" = "bit:or($PMSWCR4Value,bit:shl($TempVal,num:i(6)))"!][!//!][!//
      [!/*McuStdbyModePortTriStateEnable*/!][!//
      [!CALL "Mcu_CG_GetBooleanVal","InpVal" = "./McuStdbyModePortTriStateEnable"!][!//
      [!VAR "PMSWCR5Value" = "bit:or($PMSWCR5Value,bit:shl($OutVal,num:i(1)))"!][!//!][!//
      [!/*Enable bit protection for TRISTEQ bit*/!][!//
      [!VAR "PMSWCR5Value" = "bit:or($PMSWCR5Value,bit:shl(num:i(1),num:i(0)))"!][!//!][!//
      [!/*McuStdbyModeESR0TriStateEnable*/!][!//
      [!CALL "Mcu_CG_GetBooleanVal","InpVal" = "./McuStdbyModeESR0TriStateEnable"!][!//
      [!VAR "PMSWCR5Value" = "bit:or($PMSWCR5Value,bit:shl($OutVal,num:i(2)))"!][!//
      [!/*McuStdbyModePORSTFilterEnable*/!][!//
      [!CALL "Mcu_CG_GetBooleanVal","InpVal" = "./McuStdbyModePORSTFilterEnable"!][!//
      [!VAR "PMSWCR5Value" = "bit:or($PMSWCR5Value,bit:shl($OutVal,num:i(4)))"!][!//
      [!/*McuStdbyModeWakeupTimerEnable*/!][!//
      [!IF "./McuStdbyModeWakeupTimerConf/McuStdbyModeWakeupTimerEnable = 'true'"!][!//
        [!/*McuStdbyModeWakeupTimerValue*/!][!//
        [!VAR "TempVal" = "./McuStdbyModeWakeupTimerConf/McuStdbyModeWakeupTimerValue"!][!//
        [!VAR "PMSWCR3Value" = "bit:or($PMSWCR3Value,bit:shl($TempVal,num:i(0)))"!][!//!][!/
        [!/*McuStdbyModeWakeupTimerEnable*/!][!//
        [!CALL "Mcu_CG_GetBooleanVal","InpVal" = "./McuStdbyModeWakeupTimerConf/McuStdbyModeWakeupTimerEnable"!][!//
        [!VAR "PMSWCR3Value" = "bit:or($PMSWCR3Value,bit:shl($OutVal,num:i(27)))"!][!//
        [!VAR "PMSWCR0Value" = "bit:or($PMSWCR0Value,bit:shl($OutVal,num:i(31)))"!][!//
        [!/*McuStdbyModeWakeupTimerClkDiv*/!][!//
        [!VAR "TempVal" = "./McuStdbyModeWakeupTimerConf/McuStdbyModeWakeupTimerClkDiv"!][!//
        [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
        [!VAR "PMSWCR3Value" = "bit:or($PMSWCR3Value,bit:shl($TempVal,num:i(29)))"!][!//!][!//
        [!/*McuStdbyModeWakeupTimerMode*/!][!//
        [!VAR "TempVal" = "./McuStdbyModeWakeupTimerConf/McuStdbyModeWakeupTimerMode"!][!//
        [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
        [!VAR "PMSWCR3Value" = "bit:or($PMSWCR3Value,bit:shl($TempVal,num:i(30)))"!][!//!][!//
      [!ENDIF!][!//
      [!/* Calculate  EVRUVMON and EVRMONCTRL registers value */!][!//
      [!/*McuStdbyModeVextUVThres*/!][!//
      [!IF "./McuStdbyModeVddVextConf/McuStdbyModeEntryOnVEXTRampDown = 'true'"!][!//
        [!VAR "TempVal" = "./McuStdbyModeVddVextConf/McuStdbyModeVextUVThres"!][!//
        [!VAR "EVRUVMONValue" = "bit:and($EVRUVMONValue,num:i(4278255615))"!][!//!][!/
        [!VAR "EVRUVMONValue" = "bit:or($EVRUVMONValue,bit:shl($TempVal,num:i(16)))"!][!//!][!/
        [!/*McuStdbyModeVextUMMonMode*/!][!//
        [!VAR "TempVal" = "./McuStdbyModeVddVextConf/McuStdbyModeVextUMMonMode"!][!//
        [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
        [!VAR "EVRMONCTRLValue" = "bit:and($EVRMONCTRLValue,num:i(4291821567))"!][!//!][!/
        [!VAR "EVRMONCTRLValue" = "bit:or($EVRMONCTRLValue,bit:shl($TempVal,num:i(20)))"!][!//
      [!ENDIF!][!//
      [!/*McuStdbyModeVddUVThres*/!][!//
      [!IF "./McuStdbyModeVddVextConf/McuStdbyModeEntryOnVDDRampDown = 'true'"!][!//
        [!VAR "TempVal" = "./McuStdbyModeVddVextConf/McuStdbyModeVddUVThres"!][!//
        [!VAR "EVRUVMONValue" = "bit:and($EVRUVMONValue,num:i(4294967040))"!][!//!][!/
        [!VAR "EVRUVMONValue" = "bit:or($EVRUVMONValue,bit:shl($TempVal,num:i(0)))"!][!//!][!/
        [!/*McuStdbyModeVddUMMonMode*/!][!//
        [!VAR "TempVal" = "./McuStdbyModeVddVextConf/McuStdbyModeVddUMMonMode"!][!//
        [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
        [!VAR "EVRMONCTRLValue" = "bit:and($EVRMONCTRLValue,num:i(4294967247))"!][!//!][!/
        [!VAR "EVRMONCTRLValue" = "bit:or($EVRMONCTRLValue,bit:shl($TempVal,num:i(4)))"!][!//
      [!ENDIF!][!//
    [!/*To Allow cached and non-cached LMU region for McuStdbyModeRamEnable*/!][!//
    [!VAR "StdbyRamType" = "num:i(0)"!][!//
      [!IF "contains(./McuStdbyModeRamEnable,'NONCACHED')"!][!//
      [!VAR "StdbyRamType" = "bit:shl(num:i(1),num:i(29))"!][!//
      [!ENDIF!][!//
    [!ENDSELECT!][!//
  [!ENDIF!][!//
[!ENDNOCODE!][!//
[!AUTOSPACING!][!//
  /*MaxModeEvrcCtrl value*/
  {
    [!"num:inttohex($McuMode,num:i(1))"!]U,
    [!"num:inttohex($EvrcLowPowerMode,num:i(1))"!]U,
    0U
  },
  /* PMSWCR0 Register value */
  [!"num:inttohex($PMSWCR0Value,num:i(8))"!]U,
  /* PMSWCR3Value  */
  [!"num:inttohex($PMSWCR3Value,num:i(8))"!]U,
  /* PMSWCR4Value  */
  [!"num:inttohex($PMSWCR4Value,num:i(8))"!]U,
  /* PMSWCR5Value  */
  [!"num:inttohex($PMSWCR5Value,num:i(8))"!]U,
  /* EVRUVMONValue  */
  [!"num:inttohex($EVRUVMONValue,num:i(8))"!]U,
  /* EVRMONCTRLValue  */
  [!"num:inttohex($EVRMONCTRLValue,num:i(8))"!]U[!IF "($StdbyRamEnable > num:i(0))"!],
  /* Standby RAM start address(es) */
  [!IF "($StdbyRamEnable = num:i(1))"!]
  {
    /* MISRA2012_RULE_11_6_JUSTIFICATION: Memory address is generated as a numerical 
       value from property file and in code, it is accessed as a pointer to the
       RAM address. Hence an explicit typecast from integer to uint32 based pointer.
       */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: Memory address is generated as a numerical 
       value from property file and in code, it is accessed as a pointer to the
       RAM address. Hence an explicit typecast from integer to uint32 based pointer.
       */
    (uint32*)[!"num:inttohex((bit:or(ecu:get('Mcu.CPU0LMUAddStart'),$StdbyRamType)),num:i(8))"!]U,
  }
  [!ENDIF!][!//
  [!IF "($StdbyRamEnable = num:i(2))"!]
  {
    /* MISRA2012_RULE_11_6_JUSTIFICATION: Memory address is generated as a numerical 
       value from property file and in code, it is accessed as a pointer to the
       RAM address. Hence an explicit typecast from integer to uint32 based pointer.
       */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: Memory address is generated as a numerical 
       value from property file and in code, it is accessed as a pointer to the
       RAM address. Hence an explicit typecast from integer to uint32 based pointer.
       */
    (uint32*)[!"num:inttohex((bit:or(ecu:get('Mcu.CPU0LMUAddStart'),$StdbyRamType)),num:i(8))"!]U,
    (uint32*)[!"num:inttohex((bit:or(ecu:get('Mcu.CPU0LMUAddBlk1Start'),$StdbyRamType)),num:i(8))"!]U
    /* MISRA2012_RULE_11_6_JUSTIFICATION: Memory address is generated as a numerical 
       value from property file and in code, it is accessed as a pointer to the
       RAM address. Hence an explicit typecast from integer to uint32 based pointer.
       */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: Memory address is generated as a numerical 
       value from property file and in code, it is accessed as a pointer to the
       RAM address. Hence an explicit typecast from integer to uint32 based pointer.
       */
  }
  [!ENDIF!][!//
  [!IF "($StdbyRamEnable = num:i(4))"!]
  {
    /* MISRA2012_RULE_11_6_JUSTIFICATION: Memory address is generated as a numerical 
       value from property file and in code, it is accessed as a pointer to the
       RAM address. Hence an explicit typecast from integer to uint32 based pointer.
       */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: Memory address is generated as a numerical 
       value from property file and in code, it is accessed as a pointer to the
       RAM address. Hence an explicit typecast from integer to uint32 based pointer.
       */
    (uint32*)[!"num:inttohex((bit:or(ecu:get('Mcu.CPU1LMUAddStart'),$StdbyRamType)),num:i(8))"!]U,
    (uint32*)[!"num:inttohex((bit:or(ecu:get('Mcu.CPU1LMUAddBlk1Start'),$StdbyRamType)),num:i(8))"!]U
    /* MISRA2012_RULE_11_6_JUSTIFICATION: Memory address is generated as a numerical 
       value from property file and in code, it is accessed as a pointer to the
       RAM address. Hence an explicit typecast from integer to uint32 based pointer.
       */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: Memory address is generated as a numerical 
       value from property file and in code, it is accessed as a pointer to the
       RAM address. Hence an explicit typecast from integer to uint32 based pointer.
       */
  }
  [!ENDIF!][!//
  [!IF "($StdbyRamEnable = num:i(7))"!]
  {
    /* MISRA2012_RULE_11_6_JUSTIFICATION: Memory address is generated as a numerical 
       value from property file and in code, it is accessed as a pointer to the
       RAM address. Hence an explicit typecast from integer to uint32 based pointer.
       */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: Memory address is generated as a numerical 
       value from property file and in code, it is accessed as a pointer to the
       RAM address. Hence an explicit typecast from integer to uint32 based pointer.
       */
    (uint32*)[!"num:inttohex((bit:or(ecu:get('Mcu.CPU0LMUAddStart'),$StdbyRamType)),num:i(8))"!]U,
    /* MISRA2012_RULE_11_6_JUSTIFICATION: Memory address is generated as a numerical 
       value from property file and in code, it is accessed as a pointer to the
       RAM address. Hence an explicit typecast from integer to uint32 based pointer.
       */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: Memory address is generated as a numerical 
       value from property file and in code, it is accessed as a pointer to the
       RAM address. Hence an explicit typecast from integer to uint32 based pointer.
       */
    (uint32*)[!"num:inttohex((bit:or(ecu:get('Mcu.CPU0LMUAddBlk1Start'),$StdbyRamType)),num:i(8))"!]U,
    /* MISRA2012_RULE_11_6_JUSTIFICATION: Memory address is generated as a numerical 
       value from property file and in code, it is accessed as a pointer to the
       RAM address. Hence an explicit typecast from integer to uint32 based pointer.
       */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: Memory address is generated as a numerical 
       value from property file and in code, it is accessed as a pointer to the
       RAM address. Hence an explicit typecast from integer to uint32 based pointer.
       */
    (uint32*)[!"num:inttohex((bit:or(ecu:get('Mcu.CPU1LMUAddStart'),$StdbyRamType)),num:i(8))"!]U,
    (uint32*)[!"num:inttohex((bit:or(ecu:get('Mcu.CPU1LMUAddBlk1Start'),$StdbyRamType)),num:i(8))"!]U
    /* MISRA2012_RULE_11_6_JUSTIFICATION: Memory address is generated as a numerical 
       value from property file and in code, it is accessed as a pointer to the
       RAM address. Hence an explicit typecast from integer to uint32 based pointer.
       */
    /* MISRA2012_RULE_11_4_JUSTIFICATION: Memory address is generated as a numerical 
       value from property file and in code, it is accessed as a pointer to the
       RAM address. Hence an explicit typecast from integer to uint32 based pointer.
       */
  }
  [!ENDIF!][!//
  [!ELSE!][!//
  [!CR!]
  [!ENDIF!][!//
};
[!/*[/cover]*/!][!//
[!IF "(ecu:get('Gtm.Available') = 'true')"!][!//
/*Generate configuration structure for GTM Clock config*/
[!VAR "ClusterCount" = "num:i(ecu:get('Gtm.NumberOfClusters'))"!][!//
[!VAR "ClusterClkCfg" = "num:i(0)"!][!//
[!VAR "TempVal" = "num:i(0)"!][!//
[!VAR "ClkCnt" = "num:i(count(node:ref($ModulePath)/McuClockSettingConfig/*))"!][!//
[!VAR "Clk_Idx" = "num:i(0)"!][!//
[!VAR "GTM_FreqCheck" = "num:i(0)"!][!//
[!FOR "Clk_Idx" = "num:i(0)" TO "num:i($ClkCnt - 1)"!][!//
  [!SELECT "node:ref($ModulePath)/McuClockSettingConfig/*[McuClockSettingId = num:i($Clk_Idx)]/McuClockReferencePointConfig"!][!//
    [!IF "./McuPllDistributionSettingConfig/McuGTMFrequency > num:i(100000000)"!][!//
      [!VAR "GTM_FreqCheck" = "num:i(1)"!][!//
    [!ELSE!][!//
      [!VAR "GTM_FreqCheck" = "num:i(0)"!][!//
    [!ENDIF!][!//
  [!ENDSELECT!][!//
[!ENDFOR!][!//
[!FOR "ClusterIndex" = "num:i(0)" TO "(num:i($ClusterCount)- num:i(1))"!][!//
  [!SELECT "node:ref($ModulePath)/GtmGlobalConfiguration/*[1]/GtmClusterConf/*[@name = concat('GtmClusterConf','_',num:i($ClusterIndex))]"!][!//
    [!/* Cluster Divider Configuration */!][!//
    [!VAR "TempVal" = "num:i(text:split(./GtmCmuClusterInputClockDividerEnable,'SEL')[2])"!][!//
    [!IF "($ClusterIndex = num:i(0)) and ($TempVal = num:i(0))"!][!//
      [!ERROR!][!//
        Config Error: Cluster 0 clock can't be disabled because it is needed by CMU and other sub-modules for Clock.
      [!ENDERROR!][!//
    [!ENDIF!][!//
       [!IF "($ClusterIndex > num:i(4)) and ($TempVal = num:i(1)) and ($GTM_FreqCheck = num:i(1))"!][!//
      [!ERROR!][!//
        Config Error: The parameters in container GtmClusterConf[!"$McuVariantName"!]: For the Clusters greater than 4, (only 100MHz capable), the allowed settings for the CLS_CLK_DIV are 0 and 2 (clock divider 2).
      [!ENDERROR!][!//
    [!ELSE!][!//
        [!VAR "ClusterClkCfg" = "bit:or($ClusterClkCfg,bit:shl($TempVal,(num:i(2) * $ClusterIndex)))"!][!//
    [!ENDIF!][!//
  [!ENDSELECT!][!//
[!ENDFOR!][!//
[!/*[cover parentID={99CE9B7A-6BF2-42fe-B8DD-FE0A53FB4704}]*/!][!//
static const Mcu_GtmClockSettingType Mcu_kGtmClockConfigPtr[!"$McuConfigShortName"!] =
{
[!SELECT "node:ref($ModulePath)/GtmGlobalConfiguration/*[1]/McuGtmClockManagementConf"!][!//
  [!IF "./GtmCmuGlobalClockNumerator < ./GtmCmuGlobalClockDenominator"!][!//
    [!ERROR!][!//
      Config Error: The parameters in container McuGtmClockManagementConf[!"$McuVariantName"!]:  GtmCmuGlobalClockNumerator should be always greater than or equal to  GtmCmuGlobalClockDenominator.
    [!ENDERROR!][!//
  [!ENDIF!][!//
  [!VAR "GtmCmuClockEnable" = "num:i(0)"!][!//
  [!IF "./GtmConfigClockSetting/GtmCmuConfigClock0Enable = 'true'"!][!//
    [!VAR "GtmCmuClockEnable" = "bit:or($GtmCmuClockEnable,bit:shl(num:i(2),num:i(0)))"!][!//
  [!ENDIF!][!//
  [!IF "./GtmConfigClockSetting/GtmCmuConfigClock1Enable = 'true'"!][!//
    [!VAR "GtmCmuClockEnable" = "bit:or($GtmCmuClockEnable,bit:shl(num:i(2),num:i(2)))"!][!//
  [!ENDIF!][!//
  [!IF "./GtmConfigClockSetting/GtmCmuConfigClock2Enable = 'true'"!][!//
    [!VAR "GtmCmuClockEnable" = "bit:or($GtmCmuClockEnable,bit:shl(num:i(2),num:i(4)))"!][!//
  [!ENDIF!][!//
  [!IF "./GtmConfigClockSetting/GtmCmuConfigClock3Enable = 'true'"!][!//
    [!VAR "GtmCmuClockEnable" = "bit:or($GtmCmuClockEnable,bit:shl(num:i(2),num:i(6)))"!][!//
  [!ENDIF!][!//
  [!IF "./GtmConfigClockSetting/GtmCmuConfigClock4Enable = 'true'"!][!//
    [!VAR "GtmCmuClockEnable" = "bit:or($GtmCmuClockEnable,bit:shl(num:i(2),num:i(8)))"!][!//
  [!ENDIF!][!//
  [!IF "./GtmConfigClockSetting/GtmCmuConfigClock5Enable = 'true'"!][!//
    [!VAR "GtmCmuClockEnable" = "bit:or($GtmCmuClockEnable,bit:shl(num:i(2),num:i(10)))"!][!//
  [!ENDIF!][!//
  [!IF "./GtmConfigClockSetting/GtmCmuConfigClock6Enable = 'true'"!][!//
    [!VAR "GtmCmuClockEnable" = "bit:or($GtmCmuClockEnable,bit:shl(num:i(2),num:i(12)))"!][!//
  [!ENDIF!][!//
  [!IF "./GtmConfigClockSetting/GtmCmuConfigClock7Enable = 'true'"!][!//
    [!VAR "GtmCmuClockEnable" = "bit:or($GtmCmuClockEnable,bit:shl(num:i(2),num:i(14)))"!][!//
  [!ENDIF!][!//
  [!IF "./GtmExtClockSetting/GtmCmuExtClock0Enable = 'true'"!][!//
    [!VAR "GtmCmuClockEnable" = "bit:or($GtmCmuClockEnable,bit:shl(num:i(2),num:i(16)))"!][!//
  [!ENDIF!][!//
  [!IF "./GtmExtClockSetting/GtmCmuExtClock1Enable = 'true'"!][!//
    [!VAR "GtmCmuClockEnable" = "bit:or($GtmCmuClockEnable,bit:shl(num:i(2),num:i(18)))"!][!//
  [!ENDIF!][!//
  [!IF "./GtmExtClockSetting/GtmCmuExtClock2Enable = 'true'"!][!//
    [!VAR "GtmCmuClockEnable" = "bit:or($GtmCmuClockEnable,bit:shl(num:i(2),num:i(20)))"!][!//
  [!ENDIF!][!//
  [!IF "./GtmFixedClockSetting/GtmCmuFixedClockEnable = 'true'"!][!//
    [!VAR "GtmCmuClockEnable" = "bit:or($GtmCmuClockEnable,bit:shl(num:i(2),num:i(22)))"!][!//
  [!ENDIF!][!//
  /*CMU config clock, external and fixed clock enable - GtmCmuClockEnable*/
  [!"num:inttohex($GtmCmuClockEnable,num:i(8))"!]U,
  /*CMU global clock numerator - GtmCmuGlobalNumerator*/
  [!"num:inttohex(./GtmCmuGlobalClockNumerator,num:i(8))"!]U,
  /*CMU global clock denominator - GtmCmuGlobalDenominator*/
  [!"num:inttohex(./GtmCmuGlobalClockDenominator,num:i(8))"!]U,

  /*CMU config clock_0...7 Numerator and Denominator - GtmCmuConfClkCtrl*/
  {
  [!IF "./GtmConfigClockSetting/GtmCmuConfigClock0Enable = 'true'"!][!//
    [!"num:inttohex(./GtmConfigClockSetting/GtmCmuConfigClock0Div,num:i(8))"!]U,
  [!ELSE!][!//
    0U,
  [!ENDIF!][!//
  [!IF "./GtmConfigClockSetting/GtmCmuConfigClock1Enable = 'true'"!][!//
    [!"num:inttohex(./GtmConfigClockSetting/GtmCmuConfigClock1Div,num:i(8))"!]U,
  [!ELSE!][!//
    0U,
  [!ENDIF!][!//
  [!IF "./GtmConfigClockSetting/GtmCmuConfigClock2Enable = 'true'"!][!//
    [!"num:inttohex(./GtmConfigClockSetting/GtmCmuConfigClock2Div,num:i(8))"!]U,
  [!ELSE!][!//
    0U,
  [!ENDIF!][!//
  [!IF "./GtmConfigClockSetting/GtmCmuConfigClock3Enable = 'true'"!][!//
    [!"num:inttohex(./GtmConfigClockSetting/GtmCmuConfigClock3Div,num:i(8))"!]U,
  [!ELSE!][!//
    0U,
  [!ENDIF!][!//
  [!IF "./GtmConfigClockSetting/GtmCmuConfigClock4Enable = 'true'"!][!//
    [!"num:inttohex(./GtmConfigClockSetting/GtmCmuConfigClock4Div,num:i(8))"!]U,
  [!ELSE!][!//
    0U,
  [!ENDIF!][!//
  [!IF "./GtmConfigClockSetting/GtmCmuConfigClock5Enable = 'true'"!][!//
    [!"num:inttohex(./GtmConfigClockSetting/GtmCmuConfigClock5Div,num:i(8))"!]U,
  [!ELSE!][!//
    0U,
  [!ENDIF!][!//
  [!IF "./GtmConfigClockSetting/GtmCmuConfigClock6Enable = 'true'"!][!//
    [!"num:inttohex(./GtmConfigClockSetting/GtmCmuConfigClock6Div,num:i(8))"!]U,
  [!ELSE!][!//
    0U,
  [!ENDIF!][!//
  [!IF "./GtmConfigClockSetting/GtmCmuConfigClock7Enable = 'true'"!][!//
    [!"num:inttohex(./GtmConfigClockSetting/GtmCmuConfigClock7Div,num:i(8))"!]U
  [!ELSE!][!//
    0U
  [!ENDIF!][!//
  },

  /*CMU fixed clock Divider selection - GtmCmuFixedClkCtrl*/
  [!IF "./GtmFixedClockSetting/GtmCmuFixedClockEnable = 'true'"!][!//
    [!"num:inttohex(text:split(./GtmFixedClockSetting/GtmCmuFixedClockSel,'SEL')[2],num:i(8))"!]U,
  [!ELSE!][!//
    /*Fixed Clock disabled - reset value*/
    0U,
  [!ENDIF!][!//

  /*GTM cluster input clock divider configuration - GtmCmuClusterInputClockDividerEnable */
  [!"num:inttohex($ClusterClkCfg,num:i(8))"!]U,

  /* External clock settings - GtmEclkCtrl*/
  {
  [!IF "./GtmExtClockSetting/GtmCmuExtClock0Enable = 'true'"!][!//
    [!IF "./GtmExtClockSetting/GtmCmuExtClock0Numerator < ./GtmExtClockSetting/GtmCmuExtClock0Denominator"!][!//
      [!ERROR!][!//
        Config Error: The parameters in container GtmExtClockSetting[!"$McuVariantName"!]:  GtmCmuExtClock0Numerator should be always greater than or equal to GtmCmuExtClock0Denominator.
      [!ENDERROR!][!//
    [!ENDIF!][!//
    /*External clock_0 Numerator and Denominator*/
    {[!"num:i(./GtmExtClockSetting/GtmCmuExtClock0Numerator)"!]U, [!"num:i(./GtmExtClockSetting/GtmCmuExtClock0Denominator )"!]U},
  [!ELSE!][!//
    /*External Clock_0 disabled - reset value of numerator and denominator*/
    {1U, 1U},
  [!ENDIF!][!//
  [!IF "./GtmExtClockSetting/GtmCmuExtClock1Enable = 'true'"!][!//
    [!IF "./GtmExtClockSetting/GtmCmuExtClock1Numerator < ./GtmExtClockSetting/GtmCmuExtClock1Denominator"!][!//
      [!ERROR!][!//
        Config Error: The parameters in container GtmExtClockSetting[!"$McuVariantName"!]:  GtmCmuExtClock1Numerator should be always greater than or equal to GtmCmuExtClock1Denominator.
      [!ENDERROR!][!//
    [!ENDIF!][!//
    /*External clock_1 Numerator and Denominator*/
    {[!"num:i(./GtmExtClockSetting/GtmCmuExtClock1Numerator)"!]U, [!"num:i(./GtmExtClockSetting/GtmCmuExtClock1Denominator )"!]U},
  [!ELSE!][!//
    /*External Clock_1 disabled - reset value of numerator and denominator*/
    {1U, 1U},
  [!ENDIF!][!//
  [!IF "./GtmExtClockSetting/GtmCmuExtClock2Enable = 'true'"!][!//
    [!IF "./GtmExtClockSetting/GtmCmuExtClock2Numerator < ./GtmExtClockSetting/GtmCmuExtClock2Denominator"!][!//
      [!ERROR!][!//
        Config Error: The parameters in container GtmExtClockSetting[!"$McuVariantName"!]:  GtmCmuExtClock2Numerator should be always greater than or equal to GtmCmuExtClock2Denominator.
      [!ENDERROR!][!//
    [!ENDIF!][!//
    /*External clock_2 Numerator and Denominator*/
    {[!"num:i(./GtmExtClockSetting/GtmCmuExtClock2Numerator)"!]U, [!"num:i(./GtmExtClockSetting/GtmCmuExtClock2Denominator )"!]U}
  [!ELSE!][!//
    /*External Clock_2 disabled - reset value of numerator and denominator*/
    {1U, 1U}
  [!ENDIF!][!//
  }
[!ENDSELECT!][!//[!SELECT "node:ref($ModulePath)/GtmGlobalConfiguration/*[1]/McuGtmClockManagementConf"!][!//
};
[!/*[/cover]*/!][!//
/*Generate configuration structure for GTM cluster config*/
[!VAR "TimChCount" = "num:i(ecu:get('Gtm.NumberOfTimChannels'))"!][!//
[!VAR "TomChCount" = "num:i(ecu:get('Gtm.NumberOfTomChannels'))"!][!//
[!VAR "AtomChCount" = "num:i(ecu:get('Gtm.NumberOfAtomChannels'))"!][!//
[!/*[cover parentID={359B7260-F11B-42d9-B4EE-D77C0568F34E}]*/!][!//
static const Mcu_GtmClusterConfigType Mcu_kGtmClusterConfigPtr[!"$McuConfigShortName"!][[!"$ClusterCount"!]] =
{
[!FOR "ClusterIndex" = "num:i(0)" TO "(num:i($ClusterCount)- num:i(1))"!][!//
  [!VAR "GtmCcmCfg" = "num:i(0)"!][!//
  [!VAR "GtmCcmConfClockCfg" = "num:i(0)"!][!//
  [!SELECT "./McuHardwareResourceAllocationConf/*[1]/McuGtmAllocationConf/*[1]"!][!//
    [!/*Calculate cluster configuration as TIM enable*/!][!//
    [!IF " ClusterIndex < num:i(ecu:get('Gtm.NumberOfTimModules'))"!][!//
      [!VAR "TempVal" = "num:i(0)"!][!//
      [!SELECT "./McuGtmTimAllocationConf/*[@name = concat('McuGtmTimAllocationConf','_',num:i($ClusterIndex))]"!][!//
        [!LOOP "./McuGtmTimChannelAllocationConf/*"!][!//
          [!IF "./McuGtmTimChannelAllocationConf != 'GTM_TIM_CHANNEL_NOT_USED'"!][!//
            [!VAR "TempVal" = "num:i($TempVal+1)"!][!//
            [!BREAK!]
          [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "$TempVal > 0"!][!//
          [!VAR "GtmCcmCfg" = "bit:or($GtmCcmCfg,bit:shl(num:i(1),num:i(0)))"!][!//
        [!ENDIF!][!//
      [!ENDSELECT!]
    [!ENDIF!][!//
    [!/*Calculate cluster configuration as TOM enable*/!][!//
    [!IF " ClusterIndex < num:i(ecu:get('Gtm.NumberOfTomModules'))"!][!//
      [!VAR "TempVal" = "num:i(0)"!][!//
      [!SELECT "./McuGtmTomAllocationConf/*[@name = concat('McuGtmTomAllocationConf','_',num:i($ClusterIndex))]"!][!//
        [!LOOP "./McuGtmTomChannelAllocationConf/*"!][!//
          [!IF "(./McuGtmTomChannelAllocationConf != 'GTM_TOM_CHANNEL_NOT_USED')"!][!//
            [!VAR "TempVal" = "num:i($TempVal+1)"!][!//
            [!BREAK!]
          [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "$TempVal > num:i(0)"!][!//
          [!VAR "GtmCcmCfg" = "bit:or($GtmCcmCfg,bit:shl(num:i(1),num:i(1)))"!][!//
        [!ENDIF!][!//
      [!ENDSELECT!]
    [!ENDIF!][!//
    [!/*Calculate cluster configuration as ATOM enable*/!][!//
    [!IF " ClusterIndex < num:i(ecu:get('Gtm.NumberOfAtomModules'))"!][!//
      [!VAR "TempVal" = "num:i(0)"!][!//
      [!SELECT "./McuGtmAtomAllocationConf/*[@name = concat('McuGtmAtomAllocationConf','_',num:i($ClusterIndex))]"!][!//
        [!LOOP "./McuGtmAtomChannelAllocationConf/*"!][!//
          [!IF "(./McuGtmAtomChannelAllocationConf != 'GTM_ATOM_CHANNEL_NOT_USED') "!][!//
            [!VAR "TempVal" = "num:i($TempVal+num:i(1))"!][!//
            [!BREAK!]
          [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "$TempVal > num:i(0)"!][!//
          [!VAR "GtmCcmCfg" = "bit:or($GtmCcmCfg,bit:shl(num:i(1),num:i(2)))"!][!//
        [!ENDIF!][!//
      [!ENDSELECT!]
    [!ENDIF!][!//
  [!ENDSELECT!][!//[!SELECT "./McuHardwareResourceAllocationConf/*[1]/McuGtmAllocationConf/*[1]"!][!//

  [!SELECT "node:ref($ModulePath)/GtmGlobalConfiguration/*[1]/GtmClusterConf/*[@name = concat('GtmClusterConf','_',num:i($ClusterIndex))]"!][!//
      [!VAR "GtmCcmClkEnable" = "(text:split(./GtmCmuClusterInputClockDividerEnable,'SEL')[2])"!][!//
      [!IF "$GtmCcmCfg != num:i(0) and $GtmCcmClkEnable = num:i(0)"!][!//
        [!ERROR!][!//
           Config Error: The clock to cluster [!"$ClusterIndex"!] is disabled while TIM/TOM/ATOM for that cluster is being used. Please enable the cluster clock.
        [!ENDERROR!][!//
      [!ENDIF!]
      [!VAR "GtmCcmConfClockCfg" = "bit:or($GtmCcmConfClockCfg,bit:shl(text:split(./GtmClusterConfClockSetting/GtmClusterConfClock0Src,'SEL')[2],num:i(0)))"!][!//
      [!VAR "GtmCcmConfClockCfg" = "bit:or($GtmCcmConfClockCfg,bit:shl(text:split(./GtmClusterConfClockSetting/GtmClusterConfClock1Src,'SEL')[2],num:i(4)))"!][!//
      [!VAR "GtmCcmConfClockCfg" = "bit:or($GtmCcmConfClockCfg,bit:shl(text:split(./GtmClusterConfClockSetting/GtmClusterConfClock2Src,'SEL')[2],num:i(8)))"!][!//
      [!VAR "GtmCcmConfClockCfg" = "bit:or($GtmCcmConfClockCfg,bit:shl(text:split(./GtmClusterConfClockSetting/GtmClusterConfClock3Src,'SEL')[2],num:i(12)))"!][!//
      [!VAR "GtmCcmConfClockCfg" = "bit:or($GtmCcmConfClockCfg,bit:shl(text:split(./GtmClusterConfClockSetting/GtmClusterConfClock4Src,'SEL')[2],num:i(16)))"!][!//
      [!VAR "GtmCcmConfClockCfg" = "bit:or($GtmCcmConfClockCfg,bit:shl(text:split(./GtmClusterConfClockSetting/GtmClusterConfClock5Src,'SEL')[2],num:i(20)))"!][!//
      [!VAR "GtmCcmConfClockCfg" = "bit:or($GtmCcmConfClockCfg,bit:shl(text:split(./GtmClusterConfClockSetting/GtmClusterConfClock6Src,'SEL')[2],num:i(24)))"!][!//
      [!VAR "GtmCcmConfClockCfg" = "bit:or($GtmCcmConfClockCfg,bit:shl(text:split(./GtmClusterConfClockSetting/GtmClusterConfClock7Src,'SEL')[2],num:i(28)))"!][!//
  /*GTM Cluster_[!"$ClusterIndex"!] configuration*/
  {
    /*GTM cluster TIM/TOM/ATOM enable settings*/
    [!"num:inttohex($GtmCcmCfg,num:i(8))"!]U,
    /*GTM cluster config clock settings*/
    [!"num:inttohex($GtmCcmConfClockCfg,num:i(8))"!]U,
    /*GTM cluster fixed clock settings*/
    [!"num:inttohex((text:split(./GtmClusterFixedClockSetting/GtmClusterFixedClockSrc,'SEL')[2]),num:i(8))"!]U
  [!ENDSELECT!]
  }[!IF "$ClusterIndex < (($ClusterCount) - num:i(1))"!],[!ENDIF!]
[!ENDFOR!][!//[!FOR "ClusterIndex" = "0" TO "(num:i($Count)- 1)"!][!//

};
[!/*[/Cover]*/!][!//

/*
 Gtm Configuration structure for module
  Container: Mcu_kGtmConfiguration
  Multiplicity: 1 - *
*/
[!/*[cover parentID={C15710A2-1C79-420e-9AD0-2F46C82A4888}]*/!][!//
static const Mcu_GtmConfigType Mcu_kGtmConfiguration[!"$McuConfigShortName"!] =
{
  /* Ptr to GTM clock configuration -  GtmClockCfgPtr */
  &Mcu_kGtmClockConfigPtr[!"$McuConfigShortName"!],
  /* Ptr to GTM cluster configuration -  GtmClusterCfgPtr */
  Mcu_kGtmClusterConfigPtr[!"$McuConfigShortName"!],
  [!SELECT "node:ref($ModulePath)/GtmGlobalConfiguration/*[1]"!][!//
  /*Configuration for TOM global settings*/
  {
    /*Configuration for Tom global settings -  GtmTomCfg*/
    [!VAR "TomCount" = "num:i(count(./GtmTomGlobalConf/*))"!][!//
    [!FOR "TomIdx" ="num:i(0)" TO "num:i($TomCount - 1)"!][!//
      [!SELECT "GtmTomGlobalConf/*[@name = concat('GtmTomGlobalConf_',num:i($TomIdx))]"!][!//
        /*[!"node:name(.)"!]*/
        [!NOCODE!][!//
          [!VAR "TomTgcActTb_g0" = "num:i(0)"!][!//
          [!VAR "TomTgcActTb_g1" = "num:i(0)"!][!//
          [!VAR "TomTgcActTb_g0" = "(./GtmTomGroupConf/*[1]/GtmTomActionTimeBaseUnitConf/GtmTomActionTimeBaseValue)"!][!//
          [!VAR "TomTgcActTb_g0" = "bit:or($TomTgcActTb_g0,bit:shl(text:split(./GtmTomGroupConf/*[1]/GtmTomActionTimeBaseUnitConf/GtmTomActionTimeBaseSelection,'TS')[2],25))"!][!//
          [!VAR "TomTgcActTb_g1" = "bit:or($TomTgcActTb_g1,bit:shl((./GtmTomGroupConf/*[2]/GtmTomActionTimeBaseUnitConf/GtmTomActionTimeBaseValue),0))"!][!//
          [!VAR "TomTgcActTb_g1" = "bit:or($TomTgcActTb_g1,bit:shl(text:split(./GtmTomGroupConf/*[2]/GtmTomActionTimeBaseUnitConf/GtmTomActionTimeBaseSelection,'TS')[2],25))"!][!//
          [!VAR "TomTgcIntTrigRstCn0_g0" = "num:i(0)"!][!//
          [!VAR "TomTgcIntTrigRstCn0_g1" = "num:i(0)"!][!//
          [!VAR "TomChCount" = "num:i(count(./GtmTomChannelConf/*))"!][!//
          [!FOR "TomChIdx" ="num:i(0)" TO "num:i($TomChCount - 1)"!][!//
            [!SELECT "GtmTomChannelConf/*[@name = concat('GtmTomChannelConf_',num:i($TomChIdx))]"!][!//
              [!IF "./GtmTomChInternalTriggerEnable = 'true'"!][!//
                [!IF "$TomChIdx < 8 "!][!//
                  [!VAR "TomTgcIntTrigRstCn0_g0" = "bit:or($TomTgcIntTrigRstCn0_g0,bit:shl(num:i(2),($TomChIdx * num:i(2))))"!][!//
                [!ELSE!]
                  [!VAR "TomTgcIntTrigRstCn0_g1" = "bit:or($TomTgcIntTrigRstCn0_g1,bit:shl(num:i(2),(($TomChIdx - num:i(8)) * num:i(2))))"!][!//
                [!ENDIF!][!//
              [!ELSE!]
                [!IF "$TomChIdx < 8 "!][!//
                  [!VAR "TomTgcIntTrigRstCn0_g0" = "bit:or($TomTgcIntTrigRstCn0_g0,bit:shl(num:i(1),($TomChIdx * num:i(2))))"!][!//
                [!ELSE!]
                  [!VAR "TomTgcIntTrigRstCn0_g1" = "bit:or($TomTgcIntTrigRstCn0_g1,bit:shl(num:i(1),(($TomChIdx - num:i(8)) * num:i(2))))"!][!//
                [!ENDIF!][!//
              [!ENDIF!][!//
              [!IF "./GtmTomChResetCn0OnTriggerEnable = 'true'"!][!//
                [!IF "$TomChIdx < num:i(8)"!][!//
                  [!VAR "TomTgcIntTrigRstCn0_g0" = "bit:or($TomTgcIntTrigRstCn0_g0,bit:shl(num:i(2),(($TomChIdx * num:i(2)) + num:i(16))))"!][!//
                [!ELSE!]
                  [!VAR "TomTgcIntTrigRstCn0_g1" = "bit:or($TomTgcIntTrigRstCn0_g1,bit:shl(num:i(2),($TomChIdx * num:i(2))))"!][!//
                [!ENDIF!][!//
              [!ELSE!]
                [!IF "$TomChIdx < num:i(8)"!][!//
                  [!VAR "TomTgcIntTrigRstCn0_g0" = "bit:or($TomTgcIntTrigRstCn0_g0,bit:shl(num:i(1),(($TomChIdx * num:i(2)) + num:i(16))))"!][!//
                [!ELSE!]
                  [!VAR "TomTgcIntTrigRstCn0_g1" = "bit:or($TomTgcIntTrigRstCn0_g1,bit:shl(num:i(1),($TomChIdx * num:i(2))))"!][!//
                [!ENDIF!][!//
              [!ENDIF!][!//
            [!ENDSELECT!]
          [!ENDFOR!][!//
        [!ENDNOCODE!][!//
        {
          /*TomTgcIntTrigRstCn0 value for group0*/
          [!"num:inttohex($TomTgcIntTrigRstCn0_g0,num:i(8))"!]U,
          /*TomTgcActTb value for group0*/
          [!"num:inttohex($TomTgcActTb_g0,num:i(8))"!]U
        },
        {
          /*TomTgcIntTrigRstCn1 value for group1*/
          [!"num:inttohex($TomTgcIntTrigRstCn0_g1,num:i(8))"!]U,
          /*TomTgcActTb value for group1*/
          [!"num:inttohex($TomTgcActTb_g1,num:i(8))"!]U
        }[!IF "$TomIdx < num:i($TomCount - 1)"!],[!ENDIF!]
      [!ENDSELECT!]
    [!ENDFOR!][!//

  },
  /*Configuration for ATOM global settings*/
  {
    /*Configuration for Atom global settings -  GtmAtomCfg*/
    [!VAR "AtomCount" = "num:i(count(./GtmAtomGlobalConf/*))"!][!//
    [!FOR "AtomIdx" ="num:i(0)" TO "num:i($AtomCount - 1)"!][!//
      [!SELECT "GtmAtomGlobalConf/*[@name = concat('GtmAtomGlobalConf_',num:i($AtomIdx))]"!][!//

        /*[!"node:name(.)"!]*/
        [!NOCODE!][!//
          [!VAR "AtomTgcActTb" = "num:i(0)"!][!//
          [!VAR "AtomTgcActTb" = "bit:or($AtomTgcActTb,bit:shl(num:i(./GtmAtomGroupConf/GtmAtomActionTimeBaseUnitConf/GtmAtomActionTimeBaseValue),num:i(0)))"!][!//
          [!VAR "AtomTgcActTb" = "bit:or($AtomTgcActTb,bit:shl(text:split(GtmAtomGroupConf/GtmAtomActionTimeBaseUnitConf/GtmAtomActionTimeBaseSelection,'TS')[2],num:i(25)))"!][!//
          [!VAR "AtomTgcIntTrigRstCn0" = "num:i(0)"!][!//
          [!VAR "AtomChCount" = "num:i(count(./GtmAtomChannelConf/*))"!][!//
          [!FOR "AtomChIdx" ="num:i(0)" TO "num:i($AtomChCount - 1)"!][!//
            [!SELECT "GtmAtomChannelConf/*[@name = concat('GtmAtomChannelConf_',num:i($AtomChIdx))]"!][!//
                [!IF "./GtmAtomChInternalTriggerEnable"!][!//
                  [!VAR "AtomTgcIntTrigRstCn0" = "bit:or($AtomTgcIntTrigRstCn0,bit:shl(num:i(2),($AtomChIdx * num:i(2))))"!][!//
                [!ELSE!]
                  [!VAR "AtomTgcIntTrigRstCn0" = "bit:or($AtomTgcIntTrigRstCn0,bit:shl(num:i(1),($AtomChIdx * num:i(2))))"!][!//
                [!ENDIF!][!//
                [!IF "./GtmAtomChResetCn0OnTriggerEnable"!][!//
                  [!VAR "AtomTgcIntTrigRstCn0" = "bit:or($AtomTgcIntTrigRstCn0,bit:shl(num:i(2),(($AtomChIdx * num:i(2)) + num:i(16))))"!][!//
                [!ELSE!]
                  [!VAR "AtomTgcIntTrigRstCn0" = "bit:or($AtomTgcIntTrigRstCn0,bit:shl(num:i(1),(($AtomChIdx * num:i(2)) + num:i(16))))"!][!//
                [!ENDIF!][!//
            [!ENDSELECT!]
          [!ENDFOR!][!//
        [!ENDNOCODE!][!//
        {
          /*AtomTgcIntTrigRstCn0 value*/
          [!"num:inttohex($AtomTgcIntTrigRstCn0,num:i(8))"!]U,
          /*AtomTgcActTb value */
          [!"num:inttohex($AtomTgcActTb,num:i(8))"!]U
        }[!IF "$AtomIdx < num:i($AtomCount - 1)"!],[!ENDIF!]
      [!ENDSELECT!]
    [!ENDFOR!][!//

  },

  /*Configuration for Gtm to Adc trigger settings*/
  {
  [!FOR "TrigIndex" = "num:i(0)" TO "num:i(4)"!][!//
    [!NOCODE!][!//
      [!VAR "GtmAdcTrig0" = "num:i(0)"!][!//
      [!VAR "GtmAdcTrig1" = "num:i(0)"!][!//
      [!VAR "AdcNo" = "num:i(0)"!][!//
      [!LOOP "./GtmTriggerForAdc/*"!][!//
        [!VAR "AdcNo" = "num:i(text:split(node:name(.),'_')[2])"!]
        [!VAR "TempVal" = "num:i(text:split(node:value(concat('GtmAdcTrigger',num:i($TrigIndex),'Select')),'_')[2])"!][!//
        [!IF "$TempVal > num:i(0)"!][!//
          [!IF "not(text:contains(ecu:list('Adc.HwUnitId'),string(concat('HWUNIT_ADC',num:i($AdcNo)))))"!][!//
            [!ERROR!][!//
              Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: ADC[!"num:i($AdcNo)"!] is not available in this device. Trigger is configured for unavailable ADC unit.
            [!ENDERROR!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
        [!IF "$AdcNo < num:i(8)"!][!//
          [!VAR "GtmAdcTrig0" = "bit:or($GtmAdcTrig0,bit:shl($TempVal,(num:i(4) * $AdcNo)))"!][!//
        [!ELSE!]
          [!VAR "GtmAdcTrig1" = "bit:or($GtmAdcTrig1,bit:shl($TempVal,((num:i(4) * $AdcNo) - num:i(32))))"!][!//
        [!ENDIF!][!//
      [!ENDLOOP!][!//
    [!ENDNOCODE!][!//
    /*Configuration of Gtm Adc trigger [!"$TrigIndex"!]*/
    {
      /*GtmAdcOut0 value*/
      [!"num:inttohex($GtmAdcTrig0,num:i(8))"!]U,
      /*GtmAdcOut1 value */
      [!"num:inttohex($GtmAdcTrig1,num:i(8))"!]U
    }[!IF "$TrigIndex < num:i(4)"!],[!ENDIF!]
  [!ENDFOR!][!//
  },
  /*Configuration for Gtm to Dsadc trigger settings*/
  {
  [!FOR "TrigIndex" = "num:i(0)" TO "num:i(3)"!][!//
    [!NOCODE!][!//
      [!VAR "GtmDsadcTrig0" = "num:i(0)"!][!//
      [!VAR "GtmDsadcTrig1" = "num:i(0)"!][!//
      [!VAR "DsadcNo" = "num:i(0)"!][!//
      [!LOOP "./GtmTriggerForDsadc/*"!][!//
        [!VAR "DsadcNo" = "num:i(text:split(node:name(.),'_')[2])"!]
        [!VAR "TempVal" = "node:value(concat('GtmDsadcTrigger',num:i($TrigIndex),'Select'))"!][!//
        [!VAR "TempVal" = "substring-after($TempVal, 'TRIG_')"!][!//
        [!IF "contains($TempVal, '_TOM')"!]
          [!VAR "ErrChk" = "substring-after($TempVal, 'TOM_')"!][!//
          [!VAR "TempVal" = "substring-before($TempVal, '_TOM')"!][!//
          [!VAR "ModNo" = "substring-before($ErrChk, '_')"!][!//
          [!VAR "ChNo" = "substring-after($ErrChk, '_')"!][!//
          [!SELECT "../../../../../McuHardwareResourceAllocationConf/*/McuGtmAllocationConf/*/McuGtmTomAllocationConf/*[@name = concat('McuGtmTomAllocationConf_',num:i($ModNo))]/McuGtmTomChannelAllocationConf/*[@name = concat('McuGtmTomChannelAllocationConf_',num:i($ChNo))]"!][!//
            [!IF "McuTomChannelEventHandledByDsadc = 'false'"!][!//
               [!ERROR!][!//
                 Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: TRIG_[!"$TempVal"!]_TOM_[!"$ModNo"!]_[!"$ChNo"!] is configured in GtmTriggerForDsadc but not configured in McuHardwareResourceAllocationConf. Please select proper trigger source.
               [!ENDERROR!][!//
            [!ENDIF!]
          [!ENDSELECT!][!//
        [!ELSEIF "contains($TempVal, '_ATOM')"!]
          [!VAR "ErrChk" = "substring-after($TempVal, 'ATOM_')"!][!//
          [!VAR "TempVal" = "substring-before($TempVal, '_ATOM')"!][!//
          [!VAR "ModNo" = "substring-before($ErrChk, '_')"!][!//
          [!VAR "ChNo" = "substring-after($ErrChk, '_')"!][!//
          [!SELECT "../../../../../McuHardwareResourceAllocationConf/*/McuGtmAllocationConf/*/McuGtmAtomAllocationConf/*[@name = concat('McuGtmAtomAllocationConf_',num:i($ModNo))]/McuGtmAtomChannelAllocationConf/*[@name = concat('McuGtmAtomChannelAllocationConf_',num:i($ChNo))]"!][!//
            [!IF "McuAtomChannelEventHandledByDsadc = 'false'"!][!//
               [!ERROR!][!//
                 Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: TRIG_[!"$TempVal"!]_ATOM_[!"$ModNo"!]_[!"$ChNo"!] is configured in GtmTriggerForDsadc but not configured in McuHardwareResourceAllocationConf. Please select proper trigger source.
               [!ENDERROR!][!//
            [!ENDIF!]
          [!ENDSELECT!][!//
        [!ELSE!]
          [!VAR "TempVal" = "substring-before($TempVal, '_NO')"!][!//
        [!ENDIF!][!//
        [!IF "$TempVal > num:i(0)"!][!//
          [!IF "not(text:contains(ecu:list('Dsadc.ChannelsAvailable'),string(concat('DSADC_CHANNEL_',num:i($DsadcNo)))))"!][!//
            [!ERROR!][!//
              Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: DSADC[!"num:i($DsadcNo)"!] is not available in this device. Trigger is configured for unavailable DSADC unit.
            [!ENDERROR!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
        [!IF "$DsadcNo < num:i(8)"!][!//
          [!VAR "GtmDsadcTrig0" = "bit:or($GtmDsadcTrig0,bit:shl($TempVal,(num:i(4) * $DsadcNo)))"!][!//
        [!ELSE!]
          [!VAR "GtmDsadcTrig1" = "bit:or($GtmDsadcTrig1,bit:shl($TempVal,((num:i(4) * $DsadcNo) - num:i(32))))"!][!//
        [!ENDIF!][!//
      [!ENDLOOP!][!//
    [!ENDNOCODE!][!//
    /*Configuration of Gtm Dsadc trigger [!"$TrigIndex"!]*/
    {
      /*GtmDsadcOut0 value*/
      [!"num:inttohex($GtmDsadcTrig0,num:i(8))"!]U,
      /*GtmDsadcOut1 value */
      [!"num:inttohex($GtmDsadcTrig1,num:i(8))"!]U
    }[!IF "$TrigIndex < num:i(3)"!],[!ENDIF!]
  [!ENDFOR!][!//

  },
  /*Configuration for Timer to Port connections*/
  {
    [!NOCODE!][!// 
      [!VAR "Portsels" = "text:grep(text:split(text:join(./*/*/*/*/GtmTimerPortPinSelect)),concat('^','TOUT','.*$'))"!]
      [!VAR "PortList" = "translate($Portsels,'[]','')"!]
      [!VAR "ToutSelValArr" = "''"!]
      [!VAR "ToutSelMskArr" = "''"!]
      [!FOR "Cnt" = "num:i(0)" TO "num:i(num:i(ecu:get('Gtm.NumberofToutSel'))-num:i(1))"!]
        [!VAR "ToutSelVal" = "num:i(0)"!]
        [!VAR "ToutSelMsk" = "num:i(0)"!]
        [!FOR "index" = "1" TO "count(text:split($PortList,','))"!]
          [!VAR "TempVal" = "text:split($PortList,',')[position() = $index]"!]
          [!VAR "ToutIndex" = "substring-before($TempVal, '_PORT')"!]
          [!VAR "SelVal" = "substring-after(substring-after($ToutIndex,'_SEL'),'_')"!]
          [!VAR "ToutNo" = "substring-after(substring-before($ToutIndex, '_SEL'),'TOUT')"!]
          [!VAR "ToutIndexNo" = "num:i(num:i($ToutNo) div num:i(8))"!]
          [!VAR "ToutSelNo" = "num:i(num:i($ToutNo) mod num:i(8))"!]
          [!IF "$ToutIndexNo = num:i($Cnt)"!]
            [!VAR "SelIndex" = "num:i(num:i($ToutSelNo) * num:i(4))"!]
            [!VAR "ToutSelVal" = "bit:or($ToutSelVal, bit:shl(num:i($SelVal),$SelIndex))"!]
            [!VAR "ToutSelMsk" = "bit:or($ToutSelMsk, bit:shl(num:i(15),$SelIndex))"!]
          [!ENDIF!]
        [!ENDFOR!]
        [!VAR "ToutSelValArr" = "concat($ToutSelValArr,',', $ToutSelVal)"!][!//
        [!VAR "ToutSelMskArr" = "concat($ToutSelMskArr,',', $ToutSelMsk)"!][!//
      [!ENDFOR!]
      [!VAR "ToutSelValArr" = "text:split($ToutSelValArr,',')"!]
      [!VAR "ToutSelMskArr" = "text:split($ToutSelMskArr,',')"!]
      [!VAR "ToutSelList" = "translate($ToutSelValArr,'[]','')"!]
      [!VAR "ToutSelMskList" = "translate($ToutSelMskArr,'[]','')"!]
    [!ENDNOCODE!][!//
    /*Configuration of ToutSel*/
    [!FOR "index" = "1" TO "count(text:split($ToutSelList,','))"!]
      [!VAR "ToutSelRegVal" = "text:split($ToutSelList,',')[position() = $index]"!]
      [!INDENT "4"!]
      /*Toutsel [!"num:i(num:i($index)-num:i(1))"!] value*/
      [!"num:inttohex($ToutSelRegVal,num:i(8))"!]U[!IF "num:i(num:i($index)-num:i(1)) < num:i(num:i(ecu:get('Gtm.NumberofToutSel'))-num:i(1))"!],
      [!ENDIF!][!//
      [!ENDINDENT!]
    [!ENDFOR!][!//

  },
  /*Mask for TOUTSEL configuration. SELx used will be generated as 0xF*/
  {
    [!FOR "index" = "1" TO "count(text:split($ToutSelMskList,','))"!]
      [!VAR "ToutSelRegMskVal" = "text:split($ToutSelMskList,',')[position() = $index]"!]
      [!INDENT "4"!]
      /*Toutsel [!"num:i(num:i($index)-num:i(1))"!] mask value*/
      [!"num:inttohex($ToutSelRegMskVal,num:i(8))"!]U[!IF "num:i(num:i($index)-num:i(1)) < num:i(num:i(ecu:get('Gtm.NumberofToutSel'))-num:i(1))"!],
      [!ENDIF!][!//
      [!ENDINDENT!]
    [!ENDFOR!][!//
    
  },
  /*Configuration for Port to Timer Connections*/
  {
   [!NOCODE!][!//
    [!VAR "TIMINSELValue" = "num:i(0)"!][!//
    [!VAR "TimInSelValArr" = "''"!]
    [!VAR "TimCount" = "num:i(count(./GtmTimGlobalConf/*))"!][!//
    [!FOR "TimIdx" ="num:i(0)" TO "num:i($TimCount - 1)"!][!//
      [!SELECT "GtmTimGlobalConf/*[@name = concat('GtmTimGlobalConf_',num:i($TimIdx))]"!][!//
        [!VAR "TimChCount" = "num:i(count(./GtmTimChannelConf/*))"!][!//
         [!FOR "TimChIdx" ="num:i(0)" TO "num:i($TimChCount - 1)"!][!//
           [!SELECT "GtmTimChannelConf/*[@name = concat('GtmTimChannelConf_',num:i($TimChIdx))]"!][!//
            [!VAR "TempVal" = "./GtmTimInpPortPinSel"!][!//
            [!VAR "TimChValue" = "substring-after($TempVal,'SEL')"!]
            [!VAR "TIMINSELValue" = "bit:or($TIMINSELValue,bit:shl($TimChValue,(num:i($TimChIdx)*num:i(4))))"!][!//
           [!ENDSELECT!]
         [!ENDFOR!]
        [!VAR "TimInSelValArr" = "concat($TimInSelValArr,',', $TIMINSELValue)"!][!//
        [!VAR "TIMINSELValue" = "num:i(0)"!][!//
      [!ENDSELECT!]
    [!ENDFOR!]  
    [!VAR "TimInSelValArr" = "text:split($TimInSelValArr,',')"!]
    [!VAR "TimInSelList" = "translate($TimInSelValArr,'[]','')"!]
   [!ENDNOCODE!][!//   
    /*Configuration of TimInSel*/   
    [!FOR "index" = "1" TO "count(text:split($TimInSelList,','))"!]
      [!VAR "TimInSelRegVal" = "text:split($TimInSelList,',')[position() = $index]"!]
      [!INDENT "4"!]
      /*TimInsel [!"num:i(num:i($index)-num:i(1))"!] value*/
      [!"num:inttohex($TimInSelRegVal,num:i(8))"!]U[!IF "num:i(num:i($index)-num:i(1)) < num:i(num:i(ecu:get('Gtm.NumberOfTimModules'))-num:i(1))"!],
      [!ENDIF!][!//
      [!ENDINDENT!]
    [!ENDFOR!][!//
    
  },
  /*Configuration for TBU channel - GtmTbuCfg (GtmTbuChannelConf)*/
  [!NOCODE!][!//
    [!VAR "GtmTbuCfg" = "num:i(0)"!][!//
    [!VAR "LoopCntr" = "num:i(0)"!][!//
    [!LOOP "./GtmTbuChannelConf/*"!][!//
      [!IF "./GtmTbuChannelEnable = 'true'"!][!//
        [!VAR "GtmTbuCfg" = "bit:or($GtmTbuCfg,bit:shl(num:i(2),(num:i(2) * $LoopCntr)))"!][!//
        [!IF "$LoopCntr = num:i(0)"!][!//
          [!VAR "GtmTbuCfg" = "bit:or($GtmTbuCfg,bit:shl(text:split(./GtmTbuChResolutionSel,'SEL')[2],(num:i(8) + (num:i(4) * $LoopCntr))))"!][!//
        [!ELSEIF "$LoopCntr = num:i(3)"!][!//
          [!VAR "GtmTbuCfg" = "bit:or($GtmTbuCfg,bit:shl(num:i(1),(num:i(8) + (num:i(4) * $LoopCntr))))"!][!//
        [!ELSEIF "($LoopCntr = num:i(1)) or ($LoopCntr = num:i(2))"!][!//
          [!VAR "GtmTbuCfg" = "bit:or($GtmTbuCfg,bit:shl(text:split(./GtmTbuChMode,'SEL')[2],(num:i(8) + (num:i(4) * $LoopCntr))))"!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
      [!IF "$LoopCntr < num:i(3)"!][!//
        [!VAR "GtmTbuCfg" = "bit:or($GtmTbuCfg,bit:shl(text:split(./GtmTbuChClockSourceSelection,'SEL')[2],(9 + (num:i(4) * $LoopCntr))))"!][!//
      [!ENDIF!][!//
      [!IF "$LoopCntr = num:i(3)"!][!//
        [!VAR "GtmTbuCfg" = "bit:or($GtmTbuCfg,bit:shl(text:split(./GtmTbuChModuloCntrSel,'SEL')[2],(num:i(12) + (num:i(4) * $LoopCntr))))"!][!//
      [!ENDIF!][!//
      [!VAR "LoopCntr" = "$LoopCntr + num:i(1)"!][!//
    [!ENDLOOP!][!//
  [!ENDNOCODE!][!//
  [!"num:inttohex($GtmTbuCfg,num:i(8))"!]U,
  [!NOCODE!][!//
    [!VAR "TomCount" = "num:i(ecu:get('Gtm.NumberOfTomModules'))"!][!//
    [!VAR "TomChCount" = "num:i(ecu:get('Gtm.NumberOfTomChannels'))"!][!//
    [!VAR "TomModuleUsed" = "num:i(0)"!][!//
    [!FOR "TomIndex" = "num:i(0)" TO "(num:i($TomCount)- num:i(1))"!][!//
      [!VAR "TempVal" = "num:i(0)"!][!//
      [!FOR "TomChIndex" = "num:i(0)" TO "(num:i($TomChCount) - num:i(1))"!][!//
        [!IF "(../../../McuHardwareResourceAllocationConf/*[1]/McuGtmAllocationConf/*[1]/McuGtmTomAllocationConf/*[@name = concat('McuGtmTomAllocationConf','_',num:i($TomIndex))]/McuGtmTomChannelAllocationConf/*[@index = $TomChIndex]/McuGtmTomChannelAllocationConf != 'GTM_TOM_CHANNEL_NOT_USED')"!][!//
          [!VAR "TempVal" = "num:i(1)"!][!//
          [!BREAK!][!//
        [!ENDIF!][!//
      [!ENDFOR!][!//
      [!VAR "TomModuleUsed" = "bit:or($TomModuleUsed,bit:shl($TempVal,$TomIndex))"!][!//
    [!ENDFOR!][!//
    [!VAR "AtomCount" = "num:i(ecu:get('Gtm.NumberOfAtomModules'))"!][!//
    [!VAR "AtomChCount" = "num:i(ecu:get('Gtm.NumberOfAtomChannels'))"!][!//
    [!VAR "AtomModuleUsed" = "num:i(0)"!][!//
    [!FOR "AtomIndex" = "num:i(0)" TO "(num:i($AtomCount)- num:i(1))"!][!//
      [!VAR "TempVal" = "num:i(0)"!][!//
      [!FOR "AtomChIndex" = "num:i(0)" TO "(num:i($AtomChCount) - num:i(1))"!][!//
        [!IF "(../../../McuHardwareResourceAllocationConf/*[1]/McuGtmAllocationConf/*[1]/McuGtmAtomAllocationConf/*[@name = concat('McuGtmAtomAllocationConf','_',num:i($AtomIndex))]/McuGtmAtomChannelAllocationConf/*[@index = $AtomChIndex]/McuGtmAtomChannelAllocationConf != 'GTM_ATOM_CHANNEL_NOT_USED')"!][!//
          [!VAR "TempVal" = "num:i(1)"!][!//
          [!BREAK!][!//
        [!ENDIF!][!//
      [!ENDFOR!][!//
      [!VAR "AtomModuleUsed" = "bit:or($AtomModuleUsed,bit:shl($TempVal,$AtomIndex))"!][!//
    [!ENDFOR!][!//
  [!ENDNOCODE!][!//
  /* TOM modules used configuration */
  [!"num:inttohex($TomModuleUsed,num:i(4))"!]U,
  /* ATOM modules used configuration */
  [!"num:inttohex($AtomModuleUsed,num:i(4))"!]U,
  /* Gtm sleep mode configuration */
  [!IF "../../../McuGeneralConfiguration/McuGtmSleepModeEnabled = 'true'"!][!//
  (boolean)TRUE
  [!ELSE!]
  (boolean)FALSE
  [!ENDIF!][!//
[!ENDSELECT!][!//[!SELECT "node:ref($ModulePath)/GtmGlobalConfiguration"!]
};
[!ENDIF!][!//
[!/*[/cover]*/!][!//

#if (MCU_GPT1_USED == STD_ON) || (MCU_GPT2_USED == STD_ON)
/* GPT12 Prescalar configuration structure */
static const Mcu_Gpt12ConfigType Mcu_kGpt12PrescalerConfiguration[!"$McuConfigShortName"!] =
{
[!NOCODE!]
[!VAR "Gpt1BlockUsed" = "num:i(0)"!][!//
[!VAR "Gpt2BlockUsed" = "num:i(0)"!][!//
[!SELECT "./McuHardwareResourceAllocationConf/*[1]/McuGpt12ModuleAllocationConf"!][!//
  [!FOR "TimerIndex" = "num:i(0)" TO "num:i(ecu:get('Gpt12.MaxTimers')) - num:i(1)"!][!//
    [!VAR "CurrNodeName" = "concat('McuGpt12ModuleAllocationConf','_',num:i($TimerIndex))"!][!//
    [!/* Fetch the timer (T2/T3/T4/T5/T6) information*/!]
    [!VAR "CurrGPT12Timer" = "text:split(./*[@name = $CurrNodeName]/McuGpt12TimerAllocation, 'GPT_TIMER_')[num:i(1)]"!][!//
    [!IF "(./*[@name = $CurrNodeName]/McuGpt12ModuleAllocationConf != 'GPT_TIMER_NOT_USED')"!][!//
      [!IF "num:i($CurrGPT12Timer) < num:i(5)"!][!//
        [!VAR "Gpt1BlockUsed" = "num:i(1)"!][!//
      [!ELSE!]
        [!VAR "Gpt2BlockUsed" = "num:i(1)"!][!//
      [!ENDIF!]
    [!ENDIF!]
  [!ENDFOR!]
[!ENDSELECT!][!//
[!ENDNOCODE!][!//
[!SELECT "./McuModuleConfiguration/McuGpt12PrescalerConf"!][!//
  [!NOCODE!][!//
    [!VAR "Gpt1PreScalar" = "num:i(0)"!]
    [!VAR "Gpt2PreScalar" = "num:i(0)"!]
    [!VAR "Gpt1ClockDiv" = "num:i(0)"!][!//
    [!VAR "Gpt2ClockDiv" = "num:i(0)"!][!//
    [!IF "./Gpt1BlockPrescalerSel != 'GPT1_BLOCK_NOT_USED'"!]
      [!IF "$Gpt1BlockUsed = num:i(0)"!]
        [!ERROR!][!//
          Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: GPT Block 1 pre-scaler is configured while GPT Block1 is not used. Select GPT1_BLOCK_NOT_USED.
        [!ENDERROR!][!//
      [!ENDIF!][!//
      [!VAR "Gpt1PreScalar" = "num:i(text:split(./Gpt1BlockPrescalerSel,'FACTOR_')[2])"!][!//
    [!ELSE!]
      [!IF "$Gpt1BlockUsed != num:i(0)"!]
        [!ERROR!][!//
          Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: GPT Block 1 pre-scaler is configured to GPT1_BLOCK_NOT_USED while GPT Block1 is used. Select proper divider configuration.
        [!ENDERROR!][!//
      [!ENDIF!]
    [!ENDIF!][!//
    [!IF "./Gpt2BlockPrescalerSel != 'GPT2_BLOCK_NOT_USED'"!]
      [!IF "$Gpt2BlockUsed = num:i(0)"!]
        [!ERROR!][!//
          Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: GPT Block 2 pre-scaler is configured while GPT Block2 is not used. Select GPT2_BLOCK_NOT_USED.
        [!ENDERROR!][!//
      [!ENDIF!][!//
      [!VAR "Gpt2PreScalar" = "num:i(text:split(./Gpt2BlockPrescalerSel,'FACTOR_')[2])"!][!//
    [!ELSE!]
      [!IF "$Gpt2BlockUsed != num:i(0)"!]
        [!ERROR!][!//
          Config Error in [!"concat($ModulePath,substring-after(node:path(.),$ModulePath))"!][!"$McuVariantName"!]: GPT Block 2 pre-scaler is configured to GPT2_BLOCK_NOT_USED while GPT Block2 is used. Select proper divider configuration.
       [!ENDERROR!][!//
      [!ENDIF!]
    [!ENDIF!][!//
    [!IF "num:i($Gpt1PreScalar) = num:i(8)"!][!//
      [!VAR "Gpt1ClockDiv" = "num:i(0)"!][!//
    [!ELSEIF "num:i($Gpt1PreScalar) = num:i(4)"!][!//
      [!VAR "Gpt1ClockDiv" = "num:i(1)"!][!//
    [!ELSEIF "num:i($Gpt1PreScalar) = num:i(32)"!][!//
      [!VAR "Gpt1ClockDiv" = "num:i(2)"!][!//
    [!ELSEIF "num:i($Gpt1PreScalar) = num:i(16)"!][!//
      [!VAR "Gpt1ClockDiv" = "num:i(3)"!][!//
    [!ENDIF!][!//
    [!IF "num:i($Gpt2PreScalar) = num:i(4)"!][!//
      [!VAR "Gpt2ClockDiv" = "num:i(0)"!][!//
    [!ELSEIF "num:i($Gpt2PreScalar) = num:i(2)"!][!//
      [!VAR "Gpt2ClockDiv" = "num:i(1)"!][!//
    [!ELSEIF "num:i($Gpt2PreScalar) = num:i(16)"!][!//
      [!VAR "Gpt2ClockDiv" = "num:i(2)"!][!//
    [!ELSEIF "num:i($Gpt2PreScalar) = num:i(8)"!][!//
      [!VAR "Gpt2ClockDiv" = "num:i(3)"!][!//
    [!ENDIF!][!//
  [!ENDNOCODE!][!//
  /*GPT Block 1 Prescalar */
  [!"num:inttohex(num:i($Gpt1ClockDiv),num:i(2))"!]U,
  /*GPT Block 2 Prescalar */
  [!"num:inttohex(num:i($Gpt2ClockDiv),num:i(2))"!]U,
  /*Reserved field initialized to 0*/
  0x0U
[!ENDSELECT!][!//
};
#endif
/* Main MCU Configuration Structure */
[!/*[cover parentID={9824B5C5-5CD7-4027-BD2B-9FF0B9E2DFD8}]*/!][!//
const Mcu_ConfigType Mcu[!"$McuConfigShortName"!] =
{
  /*[!"node:name(node:ref($ModulePath))"!]*/
[!NOCODE!][!//
  [!/*Prepare for ARSTDIS register value*/!][!//
  [!VAR "McuArstdisVal" = "num:i(0)"!][!//
  [!IF "node:ref($ModulePath)/McuResetSettingConf/McuSTM0ResetOnApplResetEnable = 'false'"!][!//
    [!VAR "McuArstdisVal" = "bit:or($McuArstdisVal,bit:shl(num:i(1),num:i(0)))"!][!//
  [!ENDIF!][!//
  [!IF "(ecu:get('Mcu.fSTM1Exists') = 'true') and (node:ref($ModulePath)/McuResetSettingConf/McuSTM1ResetOnApplResetEnable = 'false')"!][!//
    [!VAR "McuArstdisVal" = "bit:or($McuArstdisVal,bit:shl(num:i(1),num:i(1)))"!][!//
  [!ENDIF!][!//
  [!IF "(ecu:get('Mcu.fSTM2Exists') = 'true') and (node:ref($ModulePath)/McuResetSettingConf/McuSTM2ResetOnApplResetEnable = 'false')"!][!//
    [!VAR "McuArstdisVal" = "bit:or($McuArstdisVal,bit:shl(num:i(1),num:i(2)))"!][!//
  [!ENDIF!][!//
  [!IF "(ecu:get('Mcu.fSTM3Exists') = 'true') and (node:ref($ModulePath)/McuResetSettingConf/McuSTM3ResetOnApplResetEnable = 'false')"!][!//
    [!VAR "McuArstdisVal" = "bit:or($McuArstdisVal,bit:shl(num:i(1),num:i(3)))"!][!//
  [!ENDIF!][!//
  [!IF "(ecu:get('Mcu.fSTM4Exists') = 'true') and (node:ref($ModulePath)/McuResetSettingConf/McuSTM4ResetOnApplResetEnable = 'false')"!][!//
    [!VAR "McuArstdisVal" = "bit:or($McuArstdisVal,bit:shl(num:i(1),num:i(4)))"!][!//
  [!ENDIF!][!//
  [!IF "(ecu:get('Mcu.fSTM5Exists') = 'true') and (node:ref($ModulePath)/McuResetSettingConf/McuSTM5ResetOnApplResetEnable = 'false')"!][!//
    [!VAR "McuArstdisVal" = "bit:or($McuArstdisVal,bit:shl(num:i(1),num:i(5)))"!][!//
  [!ENDIF!][!//
  [!/*Prepare for RSTCON register value*/!][!//
  [!VAR "McuRstconVal" = "num:i(0)"!][!//
  [!VAR "TempVal" = "node:ref($ModulePath)/McuResetSettingConf/McuESR0ResetConf"!][!//
  [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
  [!VAR "McuRstconVal" = "bit:or($McuRstconVal,bit:shl($TempVal,num:i(0)))"!][!//
  [!VAR "TempVal" = "node:ref($ModulePath)/McuResetSettingConf/McuESR1ResetConf"!][!//
  [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
  [!VAR "McuRstconVal" = "bit:or($McuRstconVal,bit:shl($TempVal,num:i(2)))"!][!//
  [!VAR "TempVal" = "node:ref($ModulePath)/McuResetSettingConf/McuSMUResetConf"!][!//
  [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
  [!VAR "McuRstconVal" = "bit:or($McuRstconVal,bit:shl($TempVal,num:i(6)))"!][!//
  [!VAR "TempVal" = "node:ref($ModulePath)/McuResetSettingConf/McuSWResetConf"!][!//
  [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
  [!VAR "McuRstconVal" = "bit:or($McuRstconVal,bit:shl($TempVal,num:i(8)))"!][!//
  [!VAR "TempVal" = "node:ref($ModulePath)/McuResetSettingConf/McuSTM0ResetConf"!][!//
  [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
  [!VAR "McuRstconVal" = "bit:or($McuRstconVal,bit:shl($TempVal,num:i(10)))"!][!//
  [!IF "ecu:get('Mcu.fSTM1Exists') = 'true'"!][!//
    [!VAR "TempVal" = "node:ref($ModulePath)/McuResetSettingConf/McuSTM1ResetConf"!][!//
    [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
    [!VAR "McuRstconVal" = "bit:or($McuRstconVal,bit:shl($TempVal,num:i(12)))"!][!//
  [!ENDIF!][!//
  [!IF "ecu:get('Mcu.fSTM2Exists') = 'true'"!][!//
    [!VAR "TempVal" = "node:ref($ModulePath)/McuResetSettingConf/McuSTM2ResetConf"!][!//
    [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
    [!VAR "McuRstconVal" = "bit:or($McuRstconVal,bit:shl($TempVal,14))"!][!//
  [!ENDIF!][!//
  [!IF "ecu:get('Mcu.fSTM3Exists') = 'true'"!][!//
    [!VAR "TempVal" = "node:ref($ModulePath)/McuResetSettingConf/McuSTM3ResetConf"!][!//
    [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
    [!VAR "McuRstconVal" = "bit:or($McuRstconVal,bit:shl($TempVal,num:i(16)))"!][!//
  [!ENDIF!][!//
  [!IF "ecu:get('Mcu.fSTM4Exists') = 'true'"!][!//
    [!VAR "TempVal" = "node:ref($ModulePath)/McuResetSettingConf/McuSTM4ResetConf"!][!//
    [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
    [!VAR "McuRstconVal" = "bit:or($McuRstconVal,bit:shl($TempVal,num:i(18)))"!][!//
  [!ENDIF!][!//
  [!IF "ecu:get('Mcu.fSTM5Exists') = 'true'"!][!//
    [!VAR "TempVal" = "node:ref($ModulePath)/McuResetSettingConf/McuSTM5ResetConf"!][!//
    [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
    [!VAR "McuRstconVal" = "bit:or($McuRstconVal,bit:shl($TempVal,num:i(20)))"!][!//
  [!ENDIF!][!//
  [!/*Check and calculate trap settings for each core*/!][!//
  [!/*Calculate McuTrapSettingConf0 value*/!][!//
  [!VAR "McuTrapSettingConf0" = "num:i(0)"!][!//
  [!VAR "McuTrapSettingConf1" = "num:i(0)"!][!//
  [!SELECT "node:ref($ModulePath)/McuTrapSettingConf"!][!//
    [!IF "./McuCPU0ESR0TrapEnable = 'false'"!][!//
      [!VAR "McuTrapSettingConf0" = "bit:or($McuTrapSettingConf0,bit:shl(num:i(1),num:i(0)))"!][!//
    [!ENDIF!][!//
    [!IF "./McuCPU0ESR1TrapEnable = 'false'"!][!//
      [!VAR "McuTrapSettingConf0" = "bit:or($McuTrapSettingConf0,bit:shl(num:i(1),num:i(1)))"!][!//
    [!ENDIF!][!//
    [!IF "./McuCPU0Trap2Enable = 'false'"!][!//
      [!VAR "McuTrapSettingConf0" = "bit:or($McuTrapSettingConf0,bit:shl(num:i(1),num:i(2)))"!][!//
    [!ENDIF!][!//
    [!IF "./McuCPU0SMUTrapEnable = 'false'"!][!//
      [!VAR "McuTrapSettingConf0" = "bit:or($McuTrapSettingConf0,bit:shl(num:i(1),num:i(3)))"!][!//
    [!ENDIF!][!//
    [!VAR "McuTrapSettingConf0" = "bit:or($McuTrapSettingConf0,bit:shl(num:i(15),num:i(4)))"!][!//
    [!IF "$CoresAvailable >= num:i(2)"!][!//
      [!IF "./McuCPU1ESR0TrapEnable = 'false'"!][!//
        [!VAR "McuTrapSettingConf0" = "bit:or($McuTrapSettingConf0,bit:shl(num:i(1),num:i(8)))"!][!//
      [!ENDIF!][!//
      [!IF "./McuCPU1ESR1TrapEnable = 'false'"!][!//
        [!VAR "McuTrapSettingConf0" = "bit:or($McuTrapSettingConf0,bit:shl(num:i(1),num:i(9)))"!][!//
      [!ENDIF!][!//
      [!IF "./McuCPU1Trap2Enable = 'false'"!][!//
        [!VAR "McuTrapSettingConf0" = "bit:or($McuTrapSettingConf0,bit:shl(num:i(1),num:i(10)))"!][!//
      [!ENDIF!][!//
      [!IF "./McuCPU1SMUTrapEnable = 'false'"!][!//
        [!VAR "McuTrapSettingConf0" = "bit:or($McuTrapSettingConf0,bit:shl(num:i(1),num:i(11)))"!][!//
      [!ENDIF!][!//
    [!ELSE!][!//
      [!VAR "McuTrapSettingConf0" = "bit:or($McuTrapSettingConf0,bit:shl(num:i(15),num:i(8)))"!][!//
    [!ENDIF!][!//
    [!VAR "McuTrapSettingConf0" = "bit:or($McuTrapSettingConf0,bit:shl(num:i(15),num:i(12)))"!][!//
    [!IF "$CoresAvailable >= num:i(3)"!][!//
      [!IF "./McuCPU2ESR0TrapEnable = 'false'"!][!//
        [!VAR "McuTrapSettingConf0" = "bit:or($McuTrapSettingConf0,bit:shl(num:i(1),num:i(16)))"!][!//
      [!ENDIF!][!//
      [!IF "./McuCPU2ESR1TrapEnable = 'false'"!][!//
        [!VAR "McuTrapSettingConf0" = "bit:or($McuTrapSettingConf0,bit:shl(num:i(1),num:i(17)))"!][!//
      [!ENDIF!][!//
      [!IF "./McuCPU2Trap2Enable = 'false'"!][!//
        [!VAR "McuTrapSettingConf0" = "bit:or($McuTrapSettingConf0,bit:shl(num:i(1),num:i(18)))"!][!//
      [!ENDIF!][!//
      [!IF "./McuCPU2SMUTrapEnable = 'false'"!][!//
        [!VAR "McuTrapSettingConf0" = "bit:or($McuTrapSettingConf0,bit:shl(num:i(1),num:i(19)))"!][!//
      [!ENDIF!][!//
    [!ELSE!][!//
      [!VAR "McuTrapSettingConf0" = "bit:or($McuTrapSettingConf0,bit:shl(num:i(15),num:i(16)))"!][!//
    [!ENDIF!][!//
    [!VAR "McuTrapSettingConf0" = "bit:or($McuTrapSettingConf0,bit:shl(num:i(15),num:i(20)))"!][!//
    [!IF "$CoresAvailable >= num:i(4)"!][!//
      [!IF "./McuCPU3ESR0TrapEnable = 'false'"!][!//
        [!VAR "McuTrapSettingConf0" = "bit:or($McuTrapSettingConf0,bit:shl(num:i(1),num:i(24)))"!][!//
      [!ENDIF!][!//
      [!IF "./McuCPU3ESR1TrapEnable = 'false'"!][!//
        [!VAR "McuTrapSettingConf0" = "bit:or($McuTrapSettingConf0,bit:shl(num:i(1),num:i(25)))"!][!//
      [!ENDIF!][!//
      [!IF "./McuCPU3Trap2Enable = 'false'"!][!//
        [!VAR "McuTrapSettingConf0" = "bit:or($McuTrapSettingConf0,bit:shl(num:i(1),num:i(26)))"!][!//
      [!ENDIF!][!//
      [!IF "./McuCPU3SMUTrapEnable = 'false'"!][!//
        [!VAR "McuTrapSettingConf0" = "bit:or($McuTrapSettingConf0,bit:shl(num:i(1),num:i(27)))"!][!//
      [!ENDIF!][!//
    [!ELSE!][!//
      [!VAR "McuTrapSettingConf0" = "bit:or($McuTrapSettingConf0,bit:shl(num:i(15),num:i(24)))"!][!//
    [!ENDIF!][!//
    [!VAR "McuTrapSettingConf0" = "bit:or($McuTrapSettingConf0,bit:shl(num:i(15),num:i(28)))"!][!//
    [!/*Calculate McuTrapSettingConf1 value */!][!//
    [!IF "$CoresAvailable >= num:i(5)"!][!//
      [!IF "./McuCPU4ESR0TrapEnable = 'false'"!][!//
        [!VAR "McuTrapSettingConf1" = "bit:or($McuTrapSettingConf1,bit:shl(num:i(1),num:i(0)))"!][!//
      [!ENDIF!][!//
      [!IF "./McuCPU4ESR1TrapEnable = 'false'"!][!//
        [!VAR "McuTrapSettingConf1" = "bit:or($McuTrapSettingConf1,bit:shl(num:i(1),num:i(1)))"!][!//
      [!ENDIF!][!//
      [!IF "./McuCPU4Trap2Enable = 'false'"!][!//
        [!VAR "McuTrapSettingConf1" = "bit:or($McuTrapSettingConf1,bit:shl(num:i(1),num:i(2)))"!][!//
      [!ENDIF!][!//
      [!IF "./McuCPU4SMUTrapEnable = 'false'"!][!//
        [!VAR "McuTrapSettingConf1" = "bit:or($McuTrapSettingConf1,bit:shl(num:i(1),num:i(3)))"!][!//
      [!ENDIF!][!//
    [!ELSE!][!//
      [!VAR "McuTrapSettingConf1" = "bit:or($McuTrapSettingConf1,bit:shl(num:i(15),num:i(0)))"!][!//
    [!ENDIF!][!//
    [!VAR "McuTrapSettingConf1" = "bit:or($McuTrapSettingConf1,bit:shl(num:i(15),num:i(4)))"!][!//
    [!IF "$CoresAvailable >= num:i(6)"!][!//
      [!IF "./McuCPU5ESR0TrapEnable = 'false'"!][!//
        [!VAR "McuTrapSettingConf1" = "bit:or($McuTrapSettingConf1,bit:shl(num:i(1),num:i(8)))"!][!//
      [!ENDIF!][!//
      [!IF "./McuCPU5ESR1TrapEnable = 'false'"!][!//
        [!VAR "McuTrapSettingConf1" = "bit:or($McuTrapSettingConf1,bit:shl(num:i(1),num:i(9)))"!][!//
      [!ENDIF!][!//
      [!IF "./McuCPU5Trap2Enable = 'false'"!][!//
        [!VAR "McuTrapSettingConf1" = "bit:or($McuTrapSettingConf1,bit:shl(num:i(1),num:i(10)))"!][!//
      [!ENDIF!][!//
      [!IF "./McuCPU5SMUTrapEnable = 'false'"!][!//
        [!VAR "McuTrapSettingConf1" = "bit:or($McuTrapSettingConf1,bit:shl(num:i(1),num:i(11)))"!][!//
      [!ENDIF!][!//
    [!ELSE!][!//
      [!VAR "McuTrapSettingConf1" = "bit:or($McuTrapSettingConf1,bit:shl(num:i(15),num:i(8)))"!][!//
    [!ENDIF!][!//
    [!VAR "McuTrapSettingConf1" = "bit:or($McuTrapSettingConf1,bit:shl(num:i(15),num:i(12)))"!][!//
  [!ENDSELECT!][!//
[!ENDNOCODE!][!//
  /* MCU clock Configuration Pointer*/
  Mcu_kClockConfiguration[!"$McuConfigShortName"!],
  /* Ram Section configuration Pointer*/
  [!IF "num:i(count(node:ref($ModulePath)/McuRamSectorSettingConf/*)) = num:i(0)"!][!//
  NULL_PTR,
  [!ELSE!][!//
  Mcu_kRamConfiguration[!"$McuConfigShortName"!],
  [!ENDIF!][!//
  #if (MCU_GTM_USED == STD_ON)
  /* GTM Global Configuration Pointer*/
  &Mcu_kGtmConfiguration[!"$McuConfigShortName"!],
  #endif
  /*Ptr to GPT12 Prescaler config structure */
  #if ((MCU_GPT1_USED == STD_ON) || (MCU_GPT2_USED == STD_ON))
  &Mcu_kGpt12PrescalerConfiguration[!"$McuConfigShortName"!],
  #endif
  /* Ptr to Standby Mode in config structure */
  &Mcu_kLowPowerModeConfiguration[!"$McuConfigShortName"!],
  /* Reset configuration */
  [!"num:inttohex($McuRstconVal,num:i(8))"!]U,
  /* Application Reset Disable configuration */
  [!"num:inttohex($McuArstdisVal,num:i(8))"!]U,
  /* Trap configuration */
  [!"num:inttohex($McuTrapSettingConf0,num:i(8))"!]U,
  [!IF "($CoresAvailable >= num:i(5)) or ($CoresAvailable >= num:i(6))"!][!//
  [!"num:inttohex($McuTrapSettingConf1,num:i(8))"!]U,
  [!ENDIF!][!//
  /*Eru global input filter configuration */
  [!VAR "EruInputFilterReg" = "num:i(node:ref($ModulePath)/McuEruGlobalConf/McuEruInputFilterRegVal)"!][!//
  [!VAR "EruInputFilterReg" = "bit:and($EruInputFilterReg,num:hextoint('0xff01ffff'))"!][!//
  [!"num:inttohex($EruInputFilterReg,num:i(8))"!]U,
  /* Total number of Clock settings */
  ((Mcu_ClockType)[!"num:i(count(node:ref($ModulePath)/McuClockSettingConfig/*))"!]U),
  /* Total number of RAM Sectors */
  ((Mcu_RamSectionType)[!"num:i(count(node:ref($ModulePath)/McuRamSectorSettingConf/*))"!]U),
  [!SELECT "./McuGeneralConfiguration"!]
  /*GPT12 sleep mode setting */
  #if ((MCU_GPT1_USED == STD_ON) || (MCU_GPT2_USED == STD_ON))
  [!IF "./McuGpt12SleepModeEnabled = 'true'"!][!//
  (boolean)TRUE,
  [!ELSE!]
  (boolean)FALSE,
  [!ENDIF!][!//
  #endif
  #if (MCU_CCU60_USED == STD_ON)
  [!IF "./McuCcu60SleepModeEnabled = 'true'"!][!//
  (boolean)TRUE,
  [!ELSE!]
  (boolean)FALSE,
  [!ENDIF!][!//
  #endif
  #if (MCU_CCU61_USED == STD_ON)
  [!IF "./McuCcu61SleepModeEnabled = 'true'"!][!//
  (boolean)TRUE
  [!ELSE!]
  (boolean)FALSE
  [!ENDIF!][!//
  #endif
  [!ENDSELECT!]
};
[!/*[/cover]*/!][!//
/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/

[!ENDSELECT!][!//
#define MCU_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header included as per Autosar
   guidelines. */
#include "Mcu_MemMap.h"
