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
**  FILENAME  : Mcu_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 21.0.0                                                        **
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
**  TRACEABILITY : [cover parentID={92B82DA9-A966-4be2-A5C1-2130696BCB7D}]    **
**                                                                            **
**  DESCRIPTION  : Code template header file for Mcu Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Mcu Driver, AUTOSAR Release 4.2.2     **
**                     and 4.4.0                                              **
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
**  FILENAME  : Mcu_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 21.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]         !!!IGNORE-LINE!!!                **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]             !!!IGNORE-LINE!!!              **
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
[!/*[cover parentID={92B82DA9-A966-4be2-A5C1-2130696BCB7D}]*/!][!//
#ifndef MCU_CFG_H
#define MCU_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
[!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
[!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
[!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
[!VAR "NewString" = "text:replaceAll($moduleReleaseVer,"\.",'')"!]
/* Autosar version of the module */
[!/*[cover parentID={478547C9-C0A7-46ab-AFDA-781FA253EDCD}][/cover]*/!][!//
#define MCU_AS_VERSION ([!"$NewString"!])

/* AUTOSAR specification version numbers */
[!/*[cover parentID={52E05C2E-2854-4f29-B3A5-DB36BA472837}][/cover]*/!][!//
[!/*[cover parentID={63C74B1D-48EF-4e77-AD52-067AAA4B8B9C}][/cover]*/!][!//
[!/*[cover parentID={0079783A-976C-4940-B2EE-5DEF3658A0F0}][/cover]*/!][!//
[!/*[cover parentID={D4D58E41-7DEC-4482-9797-D577E463D2BB}][/cover]*/!][!//
[!/*[cover parentID={FF0462EF-EEE0-44a1-A192-372E1BE9E391}][/cover]*/!][!//
[!IF "$MajorVersion = num:i(4)"!][!//
#define MCU_AR_RELEASE_MAJOR_VERSION      ([!"$MajorVersion"!]U)
#define MCU_AR_RELEASE_MINOR_VERSION      ([!"$MinorVersion"!]U)
#define MCU_AR_RELEASE_REVISION_VERSION   ([!"$RevisionVersion"!]U)
[!ENDIF!][!//

[!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
[!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
[!VAR "SwRevisionVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
/* Vendor specific implementation version information */
[!/*[cover parentID={70FF89CE-7F99-4051-9D02-6F733CD282B6}][/cover]*/!][!//
#define MCU_SW_MAJOR_VERSION   ([!"$SwMajorVersion"!]U)
#define MCU_SW_MINOR_VERSION   ([!"$SwMinorVersion"!]U)
#define MCU_SW_PATCH_VERSION   ([!"$SwRevisionVersion"!]U)

/* MCU_MCAL_SUPERVISOR  */
/* Mcu Operation in Supervisory Mode  */
#define MCU_MCAL_SUPERVISOR             (0U)

/* MCU_MCAL_USER1  */
/* Mcu Operation in User 1 Mode  */
#define MCU_MCAL_USER1                  (1U)

[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Mcu')[1]"!][!//
[!//

/*
  Configuration: MCU_DEV_ERROR_DETECT
  Preprocessor switch for enabling the development error detection and
  reporting.
  ON  : DET is Enabled
  OFF : DET is Disabled
*/
[!/* [cover parentID={CF478994-5338-4c02-B94C-B1C5B2FC7999}] [/cover]*/!][!//
[!IF "McuGeneralConfiguration/McuDevErrorDetect = 'true'"!][!//
#define  MCU_DEV_ERROR_DETECT (STD_ON)
[!ELSE!][!//
#define  MCU_DEV_ERROR_DETECT (STD_OFF)
[!ENDIF!][!//

/*
  Configuration: MCU_MULTICORE_ERROR_DETECT
  Preprocessor switch for enabling the multicore error detection and
  reporting.
  ON  : Multicore error detection and reporting is Enabled
  OFF : Multicore error detection and reporting is Disabled
*/
[!/* [cover parentID={1372F678-85D5-4861-ACC1-A9C5069533DC}] [/cover]*/!][!//
[!IF "McuGeneralConfiguration/McuMultiCoreErrorDetect = 'true'"!][!//
#define  MCU_MULTICORE_ERROR_DETECT (STD_ON)
[!ELSE!][!//
#define  MCU_MULTICORE_ERROR_DETECT (STD_OFF)
[!ENDIF!][!//

/*
  Configuration: MCU_VERSION_INFO_API
  Preprocessor switch to enable / disable the API to read out the modules
  version information.
  ON  : version info API is enabled
  OFF : version info API is disabled
*/
[!IF "McuGeneralConfiguration/McuVersionInfoApi = 'true'"!][!//
[!/*[cover parentID= {0567762F-3A8D-44de-98D9-F79E8F485355}]*/!][!//
#define MCU_VERSION_INFO_API (STD_ON)
[!ELSE!][!//
#define MCU_VERSION_INFO_API (STD_OFF)
[!ENDIF!][!//
[!/*[/cover]*/!][!//
/*
  Configuration : MCU_DISTRIBUTE_PLL_CLOCK_API
  Preprocessor switch to enable / disable the use of the
  API Mcu_DistributePllClock()
  ENABLED  : Mcu_DistributePllClock API is available
  DISABLED : Mcu_DistributePllClock API is not available
*/
[!/*[cover parentID={3A74C11E-5BE1-4633-A902-84C35B01228D}] [/cover]*/!][!//
[!IF "McuGeneralConfiguration/McuNoPll = 'false'"!][!//
#define  MCU_DISTRIBUTE_PLL_CLOCK_API (STD_ON)
[!ELSE!][!//
#define  MCU_DISTRIBUTE_PLL_CLOCK_API (STD_OFF)
[!ENDIF!][!//

/*
  Configuration : MCU_INIT_CLOCK_API
  Preprocessor switch to enable / disable the use of the
  API Mcu_InitClock()
  ENABLED  : Mcu_InitClock API is available
  DISABLED : Mcu_InitClock API is not available
*/
[!/*[cover parentID= {7A725F43-C518-463d-8E82-E99869AAF876}][/cover]*/!][!//
[!IF "McuGeneralConfiguration/McuInitClock = 'true'"!][!//
#define  MCU_INIT_CLOCK_API (STD_ON)
[!ELSE!][!//
#define  MCU_INIT_CLOCK_API (STD_OFF)
[!ENDIF!][!//

/*
  Configuration : MCU_PERFORM_RESET_API
  Preprocessor switch to enable / disable the use of the
  API Mcu_PerformReset()
  ENABLED  : Mcu_PerformReset API is available
  DISABLED : Mcu_PerformReset API is not available
*/
[!/*[cover parentID= {7A832DBF-A8A0-459f-A31B-032FC09BE4D6}]*/!][!//
[!IF "McuGeneralConfiguration/McuPerformResetApi = 'true'"!][!//
#define  MCU_PERFORM_RESET_API (STD_ON)
[!ELSE!][!//
#define  MCU_PERFORM_RESET_API (STD_OFF)
[!ENDIF!][!//
[!/*[/cover]*/!][!//
/*
  Configuration : MCU_GET_RAM_STATE_API (McuGetRamStateApi)
  Pre-processor switch to enable/disable the API Mcu_GetRamState.
  (If the H/W does not support the functionality, this parameter
  can be used to disable the API).
*/
[!IF "McuGeneralConfiguration/McuGetRamStateApi = 'true'"!][!//
[!/*[cover parentID= {0C740769-2EE6-4743-87C5-7B4367284426}]*/!][!//
#define MCU_GET_RAM_STATE_API (STD_ON)
[!ELSE!][!//
#define MCU_GET_RAM_STATE_API (STD_OFF)
[!ENDIF!][!//
[!/*[/cover]*/!][!//
/*
  Configuration : MCU_CLR_COLD_RESET_STAT_API (McuClearColdResetStatusApi)
  Pre-processor switch to enable/disable the API Mcu_ClearColdResetStatus.
*/
[!/*[cover parentID={5754D674-67AD-422c-8724-C4D3124BF3F6}] [/cover]*/!][!//
[!IF "McuGeneralConfiguration/McuClearColdResetStatusApi = 'true'"!][!//
#define MCU_CLR_COLD_RESET_STAT_API (STD_ON)
[!ELSE!][!//
#define MCU_CLR_COLD_RESET_STAT_API (STD_OFF)
[!ENDIF!][!//

/*
  Configuration : MCU_TRAP_API (McuIfxTrapApi)
  Pre-processor switch to Enables/Disables availability of trap related APIs
  defined by IFX namely Mcu_GetTrapCause, Mcu_SetTrapRequest and
  Mcu_ClearTrapRequest.
*/
[!IF "McuGeneralConfiguration/McuIfxTrapApi = 'true'"!][!//
[!/*[cover parentID= {C04157DA-7234-4e26-96FC-B488480EDF75}]*/!][!//
#define MCU_TRAP_API (STD_ON)
[!ELSE!][!//
#define MCU_TRAP_API (STD_OFF)
[!ENDIF!][!//
[!/*[/cover]*/!][!//
/*
  Configuration : MCU_CPU_CCUCON_UPDATE_API (McuIfxCpuCcuconApi)
  This parameter Enables/Disables availability of Cpu Ccucon register
  update API defined by IFX namely Mcu_UpdateCpuCcuconReg
*/
[!/*[cover parentID={C0CB5BFF-E992-48f3-BDAF-F8679AC3699D} ] [/cover]*/!][!//
[!IF "McuGeneralConfiguration/McuIfxCpuCcuconApi = 'true'"!][!//
#define MCU_CPU_CCUCON_UPDATE_API (STD_ON)
[!ELSE!][!//
#define MCU_CPU_CCUCON_UPDATE_API (STD_OFF)
[!ENDIF!][!//

/*
  Configuration : MCU_LOW_POWER_MODE_API (McuIfxLpmApi)
  Pre-processor switch to Enables/Disables availability of low power mode APIs
  defined by IFX namely Mcu_GetCpuIdleModeInitiator, Mcu_GetCpuState,
  Mcu_GetWakeupCause and Mcu_ClearWakeupCause.
*/
[!/*[cover parentID={33EE6E43-986F-4820-AFFD-B6BFC9AD068A}][/cover]*/!][!//
[!IF "McuGeneralConfiguration/McuIfxLpmApi = 'true'"!][!//
#define MCU_LOW_POWER_MODE_API (STD_ON)
[!ELSE!][!//
#define MCU_LOW_POWER_MODE_API (STD_OFF)
[!ENDIF!][!//

[!/*[cover parentID={8A887FB0-81C0-4949-91AB-07D90DF5E396}]*/!][!//
/*
  Configuration : MCU_DEINIT_API (McuIfxDeInitApi)
  Pre-processor switch to Enables/Disables availability of
  Mcu Deinitialization API - Mcu_DeInit.
*/
[!/*[/cover]*/!][!//
[!IF "McuGeneralConfiguration/McuIfxDeInitApi = 'true'"!][!//
#define MCU_DEINIT_API (STD_ON)
[!ELSE!][!//
#define MCU_DEINIT_API (STD_OFF)
[!ENDIF!][!//

/*
  Configuration : MCU_CLK_SRC_FAILURE_NOTIF_API
                                   (McuClockSourceFailureNotification)
  Pre-processor switch for availibility of Clock failure related Production Errors
  notification function. ENABLED Clock failure related Production Errors are reported
  DISABLED Clock failure related Production Errors are not reported.
*/
[!/*[cover parentID= {32933C1E-5084-4199-A8A4-31C241ABFEB8}] [/cover]*/!][!//

[!IF "McuGeneralConfiguration/McuClockSourceFailureNotification = 'true'"!][!//
#define MCU_CLK_SRC_FAILURE_NOTIF_API (STD_ON)
[!ELSE!][!//
#define MCU_CLK_SRC_FAILURE_NOTIF_API (STD_OFF)
[!ENDIF!][!//

/*
    Configuration : MCU_SAFETY_ENABLE
    Pre-processor switch to enable/disable the MCU driver safety features.
*/
[!/*[cover parentID= {97510B77-476C-4499-AB17-C87EC87C263B}] [/cover]*/!][!//
[!IF "McuGeneralConfiguration/McuSafetyEnable = 'true'"!][!//
#define MCU_SAFETY_ENABLE (STD_ON)
[!ELSE!][!//
#define MCU_SAFETY_ENABLE (STD_OFF)
[!ENDIF!][!//
[!/*[/cover]*/!][!//

[!/*[cover parentID= {6CA8839F-9353-4b73-8865-06A296FE7298}] */!][!//
[!IF "McuGeneralConfiguration/McuInitCheckApi = 'true'"!][!//
#define MCU_INITCHECK_API (STD_ON)
[!ELSE!][!//
#define MCU_INITCHECK_API (STD_OFF)
[!ENDIF!][!//
[!/*[/cover]*/!][!//

[!/*[cover parentID= {EF597D8B-BBC1-4ae0-814A-1ECC0FC7F65E}] */!][!//
[!IF "McuGeneralConfiguration/McuInitDeInitApiMode = 'MCU_MCAL_SUPERVISOR'"!][!//
#define MCU_INIT_DEINIT_API_MODE (MCU_MCAL_SUPERVISOR)
[!ELSE!][!//
#define MCU_INIT_DEINIT_API_MODE (MCU_MCAL_USER1)
[!ENDIF!][!//
[!/*[/cover]*/!][!//

[!/*[cover parentID= {F0DF105B-34E6-4b06-811E-E8ADD52D3E60}] */!][!//
[!IF "McuGeneralConfiguration/McuRuntimeApiMode = 'MCU_MCAL_SUPERVISOR'"!][!//
#define MCU_RUNTIME_API_MODE (MCU_MCAL_SUPERVISOR)
[!ELSE!][!//
#define MCU_RUNTIME_API_MODE (MCU_MCAL_USER1)
[!ENDIF!][!//
[!/*[/cover]*/!][!//
/*
    Configuration: MCU_GTM_USED
    This parameter defines if GTM module is used by modules.
*/
[!IF "ecu:get('Gtm.Available')='true'"!][!//
  #define MCU_GTM_USED (STD_ON)

  /*
  Configuration: MCU_GTM_NO_OF_TOM_AVAILABLE
  This parameter defines no of TOM units available [0...6]
*/
[!/*[cover parentID={CCC3A2AA-10D4-48f4-8F88-6201D356A769}][/cover]*/!][!//
#define MCU_GTM_NO_OF_TOM_AVAILABLE  ([!"num:i(ecu:get('Gtm.NumberOfTomModules'))"!]U)

/*
    Configuration: MCU_GTM_NO_OF_ATOM_AVAILABLE
    This parameter defines no of Atom units available [0...12]
*/
[!/*[cover parentID={E7FDB86A-81C0-40fc-97C9-04C244DC7917}][/cover]*/!][!//
#define MCU_GTM_NO_OF_ATOM_AVAILABLE  ([!"num:i(ecu:get('Gtm.NumberOfAtomModules'))"!]U)

/*
    Configuration: MCU_GTM_NO_OF_TIM_AVAILABLE
    This parameter defines no of Tim units available [0...12]
*/
[!/*[cover parentID={E00BF6B7-51D2-4e89-BF56-1E37BE6518D5}][/cover]*/!][!//
#define MCU_GTM_NO_OF_TIM_AVAILABLE  ([!"num:i(ecu:get('Gtm.NumberOfTimModules'))"!]U)

/*
    Configuration: MCU_GTM_NO_OF_TBU_CH_AVAILABLE
    This parameter defines no of TOM units available [0...3]
*/
[!/*[cover parentID={820B11DE-32C6-4059-94FE-06F5819F902E}][/cover]*/!][!//
#define MCU_GTM_NO_OF_TBU_CH_AVAILABLE  ([!"num:i(ecu:get('Gtm.NumberOfTbuChannels'))"!]U)

/*
    Configuration: MCU_GTM_NO_OF_CCM_AVAILABLE
    This parameter defines no of CCM clusters available [0...12]
*/
[!/*[cover parentID={4471D276-0E1E-49ed-9245-AE5EA39B2E1C}][/cover]*/!][!//
#define MCU_GTM_NO_OF_CCM_AVAILABLE  ([!"num:i(ecu:get('Gtm.NumberOfClusters'))"!]U)

/*
    Configuration: MCU_NO_OF_TOUTSEL_AVAILABLE
    This parameter defines no of TOUTSEL registers available [0...33]
*/
[!/*[cover parentID={7A576ABC-B3A9-40c5-A050-890A8DB30BE3}][/cover]*/!][!//
#define MCU_GTM_NO_OF_TOUTSEL_AVAILABLE  ([!"num:i(ecu:get('Gtm.NumberofToutSel'))"!]U)

/*
    Configuration: MCU_GTM_TO_DSADC_TRIG_AVAILABLE
    This parameter specifies whether GTM to DSADC trigger is available or not.
*/
[!IF "num:i(ecu:get('Dsadc.NoOfChannels')) > num:i(0)"!]
[!/*[cover parentID={894EADBE-DE68-42a3-84BF-2BB5EE353D2A}][/cover]*/!][!//
#define MCU_GTM_TO_DSADC_TRIG_AVAILABLE  (STD_ON)
[!ELSE!]
#define MCU_GTM_TO_DSADC_TRIG_AVAILABLE  (STD_OFF)
[!ENDIF!]

[!IF "num:i(ecu:get('Dsadc.NoOfChannels')) > num:i(8)"!]
[!/*[cover parentID={EABA86D8-D622-4184-90B5-38296BE76F21}][/cover]*/!][!//
#define MCU_GTM_TO_DSADC_TRIG1  (STD_ON)
[!ELSE!]
#define MCU_GTM_TO_DSADC_TRIG1  (STD_OFF)
[!ENDIF!]

[!VAR "TbuCnt" = "num:i(ecu:get('Gtm.NumberOfTbuChannels'))"!][!//
[!VAR "TbuChenMsk" = "num:i(0)"!][!//
[!FOR "TbuIndex" = "num:i(0)" TO "(num:i($TbuCnt)- num:i(1))"!][!//
  [!VAR "TbuChenMsk" = "bit:or(bit:shl(num:i(3),(num:i(2) * $TbuIndex)),$TbuChenMsk)"!][!//
[!ENDFOR!][!//
[!/*[cover parentID={F443BF96-37A9-491b-B86C-793C06A6C734}][/cover]*/!][!//
#define MCU_TBU_CH_EN_MSK        ([!"num:inttohex($TbuChenMsk,num:i(8))"!]U)

[!VAR "ClusterCount" = "num:i(ecu:get('Gtm.NumberOfClusters'))"!][!//
[!VAR "GtmClsClkCfgRstVal" = "num:i(0)"!][!//
[!VAR "GtmClusterRstVal" = "num:i(2)"!][!//
[!FOR "ClusterIndex" = "num:i(0)" TO "(num:i($ClusterCount)- num:i(1))"!][!//
  [!VAR "GtmClsClkCfgRstVal" = "bit:or(bit:shl($GtmClsClkCfgRstVal,$GtmClusterRstVal),$GtmClusterRstVal)"!][!//
[!ENDFOR!][!//
[!/*[cover parentID={A5CD1591-13A1-48ac-ADA7-A9B9435556AB}][/cover]*/!][!//
#define MCU_GTM_CLS_CLK_CFG_RESET_VAL        ([!"num:inttohex($GtmClsClkCfgRstVal,num:i(8))"!]U)
[!ELSE!][!//
[!/*[cover parentID= {C5D1E04D-C99D-42d9-9BC2-35F20D3A98B1}][/cover]*/!][!//
#define MCU_GTM_USED (STD_OFF)
[!ENDIF!][!//


/*
    Configuration: MCU_MAIN_OSC_FREQ  (MHz)
    This parameter defines main oscillator frequency in MHz
*/
[!/*[cover parentID= {8DC1636C-16F2-4314-B749-9B4FFBCA8715}][/cover]*/!][!//
#define MCU_MAIN_OSC_FREQ  ([!"McuGeneralConfiguration/McuMainOscillatorFrequency"!]U)

/*
    Configuration: MCU_SYSCLK_FREQ  (MHz)
    This parameter defines SYSCLK frequency in MHz
*/
[!/*[cover parentID={91B7BA49-DA8C-4ce7-A721-655C391D54C8}][/cover]*/!][!//
#define MCU_SYSCLK_FREQ  ([!"McuGeneralConfiguration/McuSysClkFrequency"!]U)

/*
    Configuration: MCU_BACKUP_FREQ  (MHz)
    This parameter defines back up frequency in MHz
*/
[!/*[cover parentID={3CDAE1AF-CB9F-469c-B63E-6E94440A77D3}][/cover]*/!][!//
#define MCU_BACKUP_FREQ    ([!"num:i(ecu:get('Mcu.BackUpFrequency') div num:i(1000000))"!]U)

/* This parameter defines whether CCU6 kernel 0 is used or not*/
[!SELECT "./McuHardwareResourceAllocationConf/*[1]/McuCcu6ModuleAllocationConf"!][!//
[!IF "(./*[@name = concat('McuCcu6ModuleAllocationConf','_',num:i(0))]/McuCcu6ModuleAllocationConf = 'CCU6_MODULE_NOT_USED')"!][!//
[!/*[cover parentID={15C97F1A-2716-41fe-A150-CA252DFAC7AC}][/cover]*/!][!//
#define MCU_CCU60_USED     (STD_OFF)
[!ELSE!]
#define MCU_CCU60_USED     (STD_ON)
[!ENDIF!][!//

/* This parameter defines whether CCU6 kernel 1 is used or not*/
[!IF "(./*[@name = concat('McuCcu6ModuleAllocationConf','_',num:i(1))]/McuCcu6ModuleAllocationConf = 'CCU6_MODULE_NOT_USED')"!][!//
[!/*[cover parentID={CF23D9A7-22C6-457d-B810-FD80A89E4A90}][/cover]*/!][!//
#define MCU_CCU61_USED     (STD_OFF)
[!ELSE!]
#define MCU_CCU61_USED     (STD_ON)
[!ENDIF!][!//
[!ENDSELECT!][!//

[!NOCODE!][!//
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
/* This parameter defines whether GPT1 Block is used or not*/
[!IF "$Gpt1BlockUsed = num:i(0)"!][!//
[!/*[cover parentID={6435268E-2CAE-46b8-8ACD-FB3F01E3D9DC}][/cover]*/!][!//
#define MCU_GPT1_USED     (STD_OFF)
[!ELSEIF "$Gpt1BlockUsed = num:i(1)"!][!//
#define MCU_GPT1_USED     (STD_ON)
[!ENDIF!][!//

/* This parameter defines whether GPT1 Block is used or not*/
[!IF "$Gpt2BlockUsed = num:i(0)"!][!//
[!/*[cover parentID={2E5100F6-6144-41f8-A963-FD4108D01600}][/cover]*/!][!//
#define MCU_GPT2_USED     (STD_OFF)
[!ELSEIF "$Gpt2BlockUsed = num:i(1)"!][!//
#define MCU_GPT2_USED     (STD_ON)
[!ENDIF!][!//

/* OSC Frequency Value
    This bit field defines the divider value that generates
    the reference clock that is supervised by the
    oscillator watchdog.
    fOSCREF = OSCCON.OSCVAL - 1 + 16 MHz.
    Equation is OSCVAL = (fOSCREF - 15). */
[!/*[cover parentID={03884108-8132-470c-A65D-9BF76EEFBBC2}]*/!][!//
[!NOCODE!][!//
  [!VAR "McuOscValReg" = "num:inttohex(num:i(0))"!][!//
  [!IF "(McuGeneralConfiguration/McuOscillatorMode != 'OSC_DISABLED_MODE_SEL3')"!][!//
    [!VAR "McuOscValReg" = "num:i(McuGeneralConfiguration/McuMainOscillatorFrequency) - num:i(15)"!][!//
    [!VAR "McuOscValReg" = "num:inttohex(num:i($McuOscValReg))"!][!//
  [!ENDIF!][!//
[!ENDNOCODE!][!//
#define MCU_OSCVAL_REG_VALUE  ([!"$McuOscValReg"!]U)

[!/*[cover parentID={9CF0A748-F7FD-491d-BE0D-9B5DABC1A8DF}]*/!][!//
[!NOCODE!][!//
  [!VAR "McuOscValSysclkReg" = "num:i(McuGeneralConfiguration/McuSysClkFrequency) - num:i(15)"!][!//
  [!VAR "McuOscValSysclkReg" = "num:inttohex(num:i($McuOscValSysclkReg))"!][!//
[!ENDNOCODE!][!//
#define MCU_SYSCLK_OSCVAL     ([!"$McuOscValSysclkReg"!]U)

[!/*[/cover]*/!][!//
/*
    MACRO : MCU_OSC_MODE
    configured Oscillator mode
    EXT_CRYSTAL_CERAMIC_RES_MODE - 0
    EXT_INPUT_CLOCK_MODE         - 2
    OSC_DISABLED_MODE            - 3
*/
[!/*[cover parentID={A565F475-3EA7-4fa3-BFD4-C65CB9C9859E}][/cover]*/!][!//
#define MCU_OSC_MODE    ([!"num:i(text:split(./McuGeneralConfiguration/McuOscillatorMode,'SEL')[2])"!]U)

/*
    MACRO : MCU_OSC_CAPACITANCE_EN
    configured Oscillator capacitance information
*/
[!NOCODE!][!//
  [!VAR "Osccon" = "num:i(0)"!][!//
  [!IF "McuGeneralConfiguration/McuOscCapacitance0Enable = 'true'"!]
    [!VAR "Osccon" = "bit:or($Osccon,bit:shl(num:i(1),num:i(24)))"!][!//
  [!ENDIF!][!//
  [!IF "McuGeneralConfiguration/McuOscCapacitance1Enable = 'true'"!]
    [!VAR "Osccon" = "bit:or($Osccon,bit:shl(num:i(1),num:i(25)))"!][!//
  [!ENDIF!][!//
  [!IF "McuGeneralConfiguration/McuOscCapacitance2Enable = 'true'"!]
    [!VAR "Osccon" = "bit:or($Osccon,bit:shl(num:i(1),num:i(26)))"!][!//
  [!ENDIF!][!//
  [!IF "McuGeneralConfiguration/McuOscCapacitance3Enable = 'true'"!]
    [!VAR "Osccon" = "bit:or($Osccon,bit:shl(num:i(1),num:i(27)))"!][!//
  [!ENDIF!][!//
  [!IF "McuGeneralConfiguration/McuOscAmpRegulationEnable = 'true'"!][!//
    [!VAR "Osccon" = "bit:or($Osccon,bit:shl(num:i(1),num:i(23)))"!][!//
  [!ENDIF!][!//
[!ENDNOCODE!][!//
[!/*[cover parentID={E73852FA-4560-4ef8-B070-5DBAA0095ACA}][/cover]*/!][!//
#define MCU_OSC_CAPACITANCE_EN     ([!"num:inttohex($Osccon,8)"!]U)

[!NOCODE!][!//
  [!VAR "ModulePath" = "'McuModuleConfiguration'"!][!//
  [!VAR "ModuleIndex" = "num:i(0)"!][!//
  [!VAR "McuStdbyRamEn" = "num:i(0)"!][!//
  [!VAR "Count" = "num:i(count(node:ref($ModulePath)/*))"!][!//
  [!VAR "McuSystemModeEnable" = "num:i(0)"!][!//
  [!VAR "McuIdleModeEnable" = "num:i(0)"!][!//
  [!FOR "ModuleIndex" = "num:i(0)" TO "(num:i($Count)- num:i(1))"!][!//
    [!VAR "MaxModeEvrcCtrl" = "num:i(0)"!]
    [!VAR "ModeSettingConfig" = "num:i(count(node:ref($ModulePath)/McuModeSettingConf/*))"!]
    [!FOR "ModeIndex" = "num:i(0)" TO "($ModeSettingConfig - num:i(1))"!][!//
      [!VAR "McuModeConfig" = "num:i(node:ref($ModulePath)/McuModeSettingConf/*[$ModeIndex+1]/McuMode)"!][!//
    [!IF "$McuModeConfig = num:i(0)"!][!//
        [!VAR "McuIdleModeEnable" = "num:i(1)"!][!//
      [!ENDIF!][!//
      [!IF "$McuModeConfig = num:i(1)"!][!//
        [!VAR "McuSystemModeEnable" = "num:i(1)"!][!//
      [!ENDIF!][!//
      [!IF "$McuModeConfig = num:i(2)"!][!//
        [!VAR "McuSystemModeEnable" = "num:i(1)"!][!//
      [!VAR "McuStdbyRamEn" = "num:i(text:split(node:ref($ModulePath)/McuModeSettingConf/*[$ModeIndex+1]/McuStdbyModeSettingConf/McuStdbyModeRamEnable,'SEL')[2])"!][!//
      [!ENDIF!][!//
    [!ENDFOR!][!//
  [!ENDFOR!][!//
[!ENDNOCODE!][!//
[!/* System and Idle mode Core Calculation */!][!//
[!NOCODE!][!//
  [!VAR "McuSysModeCore" = "num:i(0)"!]
  [!VAR "TempVal" = "./McuGeneralConfiguration/McuSystemModeCpuCore"!][!//
  [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
  [!VAR "McuSysModeCore" = "num:i($TempVal+num:i(1))"!][!//
  [!VAR "McuIdleModeCore" = "num:i(0)"!][!//
  [!VAR "TempVal" = "./McuGeneralConfiguration/McuIdleModeCpuCore"!][!//
  [!VAR "TempVal" = "text:split($TempVal,'SEL')[2]"!][!//
  [!VAR "McuIdleModeCore" = "num:i($TempVal)"!][!//
[!ENDNOCODE!][!//
/* Master Core for triggering System Modes for controller
 1 - Core 0
 2 - Core 1
 3 - Core 2
 4 - Core 3
 5 - Core 4
 6 - Core 5
 7 - All Cores Unanimously
*/
#define MCU_SYSTEM_CORE_NOT_DEFINED     (0U)
[!IF "($McuSystemModeEnable > num:i(0))"!][!//
[!/*[cover parentID= {08AA96D1-C854-4cad-B958-A789E6CFB198}][/cover]*/!][!//
#define MCU_SYSTEM_MODE_CORE            ([!"num:i($McuSysModeCore)"!]U)
[!/*McuStandbyEntryMode*/!][!//
[!/*[cover parentID= {E03F632C-ABD0-4bba-A868-4C5C438740BF}][/cover]*/!][!//
#define MCU_STANDBY_MODE_ENTRY          ([!"num:i(text:split(./McuGeneralConfiguration/McuStandbyEntryMode,'SEL')[2])"!]U)
[!ELSE!]
#define MCU_SYSTEM_MODE_CORE            (MCU_SYSTEM_CORE_NOT_DEFINED)
[!ENDIF!][!//

/* Master Core for triggering Idle Mode for controller
 1 - Core 0
 2 - Core 1
 3 - Core 2
 4 - Core 3
 5 - Core 4
 6 - Core 5
 0 - All Cores Individually
*/
[!/*[cover parentID= {94BA7757-989B-4c80-81AD-4D842CE9C577}][/cover]*/!][!//
#define MCU_IDLE_CORE_NOT_DEFINED         (7U)
[!IF "$McuIdleModeEnable > num:i(0)"!][!//
#define MCU_IDLE_MODE_CORE                ([!"num:i($McuIdleModeCore)"!]U)
[!ELSE!]
#define MCU_IDLE_MODE_CORE                (MCU_IDLE_CORE_NOT_DEFINED)
[!ENDIF!][!//

/* Standby Mode Ram enable configuration */
[!NOCODE!][!//
[!/* [cover parentID= {4AE1BF08-D704-4652-A7BF-90DD63B4797E}]*/!][!//
  [!IF "($McuStdbyRamEn > num:i(0))"!][!//
    [!IF "($McuStdbyRamEn = num:i(1))"!][!// dLMU0 lower block is selected
      [!CODE!]
      [!AUTOSPACING!]
      [!INDENT "0"!]
      #define MCU_NO_OF_STDBY_RAM_BLK       (1U)
      [!ENDINDENT!]
      [!ENDCODE!]
    [!ENDIF!][!//
    [!IF "($McuStdbyRamEn = num:i(2))"!][!// dLMU0 is selected
      [!CODE!]
      [!AUTOSPACING!]
      [!INDENT "0"!]
      #define MCU_NO_OF_STDBY_RAM_BLK       (2U)
      [!ENDINDENT!]
      [!ENDCODE!]
    [!ENDIF!][!//
    [!IF "($McuStdbyRamEn = num:i(4))"!][!// dLMU1 are selected
      [!CODE!]
      [!AUTOSPACING!]
      [!INDENT "0"!]
      #define MCU_NO_OF_STDBY_RAM_BLK       (2U)
      [!ENDINDENT!]
      [!ENDCODE!]
    [!ENDIF!][!//
    [!IF "($McuStdbyRamEn = num:i(7))"!][!// Both dLMU0 and dLMU1 are selected
      [!CODE!]
      [!AUTOSPACING!]
      [!INDENT "0"!]
      #define MCU_NO_OF_STDBY_RAM_BLK       (4U)
      [!ENDINDENT!]
      [!ENDCODE!]
    [!ENDIF!][!//
  [!ELSE!][!//
    [!CODE!]
    [!AUTOSPACING!]
    [!INDENT "0"!]
    #define MCU_NO_OF_STDBY_RAM_BLK       (0U)
    [!ENDINDENT!]
    [!ENDCODE!]
  [!ENDIF!][!//
[!ENDNOCODE!]

/*
  Macro to write into Trap disable register
*/
[!VAR "CoreCount" = "num:i(as:modconf('ResourceM')[1]/ResourceMMcalConfig/*[1]/ResourceMNumberOfActiveCores)"!][!//
[!IF "($CoreCount = num:i(1))"!][!//
#define MCU_TRAPDIS0_RESET_VAL     (0xF0F0F0FFU)
[!ELSEIF "($CoreCount = num:i(2))"!][!//
#define MCU_TRAPDIS0_RESET_VAL     (0xF0F0FFFFU)
[!ELSEIF "($CoreCount = num:i(3))"!][!//
#define MCU_TRAPDIS0_RESET_VAL     (0xF0FFFFFFU)
[!ELSEIF "($CoreCount = num:i(4))"!][!//
#define MCU_TRAPDIS0_RESET_VAL     (0xFFFFFFFFU)
[!ELSE!][!//
#define MCU_TRAPDIS0_RESET_VAL     (0xFFFFFFFFU)
#define MCU_TRAPDIS1_RESET_VAL     (0x0000FFFFU)
[!ENDIF!][!//

/*
    Container: McuModeSettingConf
    Multiplicity: 1 - *
    Configuration Options:
    For MCU power down modes Mcu_ModeType :
    IDLE Mode: CPU clock is disabled and peripheral clock is running
    as configured
*/
#define MCU_IDLE             (0U)

/*
    Configuration Options:
    For MCU power down modes Mcu_ModeType :
    SLEEP Mode: CPU clock is disabled and Peripherals go to sleep if
    configured for sleep mode
*/
#define MCU_SLEEP            (1U)

/*
    Configuration Options:
    For MCU power down modes Mcu_ModeType :
*/
#define MCU_STANDBY          (2U)

/*
    Maximum number of modes which are configurable is 3
*/
#define MCU_MAX_NO_MODES     (3U)

[!VAR "ModeSettingConfig" = "num:i(count(node:ref($ModulePath)/McuModeSettingConf/*))"!]
[!FOR "ModeIndex" = "num:i(0)" TO "($ModeSettingConfig - num:i(1))"!][!//
  [!VAR "SymbolicName" = "concat('McuConf_McuModeSettingConf_',node:name(node:ref($ModulePath)/McuModeSettingConf/*[$ModeIndex+1]))"!]
[!/*[cover parentID= {E4ED0085-EB4B-4580-A78E-8A6BDF7666E3}]*/!][!//
/*
  Configuration: Mode Id
  This id corresponds to the container name of the McuModeSettingConfiguration
  Use this as the parameter for API: Mcu_SetMode
*/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef [!"$SymbolicName"!]
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define [!"$SymbolicName"!]  ([!"num:i(node:ref($ModulePath)/McuModeSettingConf/*[$ModeIndex+1]/McuMode)"!]U)
#endif
[!ENDFOR!][!//
[!/*[/cover]*/!][!//

/*
  Container: McuClockSettingConfig
  Multiplicity: 1 -*
*/
[!/*[cover parentID= {8DFB209E-AA9F-4c4e-B68C-791ED7856555}]*/!][!//
[!VAR "ClockSettingConfig" = "num:i(count(node:ref($ModulePath)/McuClockSettingConfig/*))"!][!//
[!FOR "ClockIndex" = "num:i(0)" TO "($ClockSettingConfig - num:i(1))"!][!//
  [!VAR "SymbolicName" = "concat('McuConf_McuClockSettingConfig_',node:name(node:ref($ModulePath)/McuClockSettingConfig/*[McuClockSettingId = num:i($ClockIndex)]))"!]
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef [!"$SymbolicName"!]
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define [!"$SymbolicName"!]  ([!"num:i(node:ref($ModulePath)/McuClockSettingConfig/*[McuClockSettingId = num:i($ClockIndex)]/McuClockSettingId)"!]U)
#endif
[!ENDFOR!][!//
[!/*[/cover]*/!][!//
/*
  Container: McuRamSectorSettingConf
  Multiplicity: 0 -*
*/

[!VAR "RamSectorSettingConfig" = "num:i(count(node:ref($ModulePath)/McuRamSectorSettingConf/*))"!][!//
[!/*[cover parentID= {B7661B96-79C4-45f4-8F3B-637646F7DAA3}]*/!][!//
[!IF "$RamSectorSettingConfig > num:i(0)"!][!//
  [!FOR "RAMSectionIndex" = "num:i(0)" TO "($RamSectorSettingConfig - num:i(1))"!][!//
  [!VAR "SymbolicName" = "concat('McuConf_McuRamSectorSettingConf_',node:name(node:ref($ModulePath)/McuRamSectorSettingConf/*[McuRamSectorSettingId = num:i($RAMSectionIndex)]))"!]
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef [!"$SymbolicName"!]
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define [!"$SymbolicName"!]  ([!"num:i(node:ref($ModulePath)/McuRamSectorSettingConf/*[McuRamSectorSettingId = num:i($RAMSectionIndex)]/McuRamSectorSettingId)"!]U)
#endif
  [!ENDFOR!][!//
[!ENDIF!][!//
[!/*[/cover]*/!][!//
/*
  Container: McuResetReasonConf
  Multiplicity: 1-1
*/
[!/*[cover parentID= {C727B85A-0C06-4be6-A7B3-5E0A7AEA5D18}]*/!][!//
[!VAR "LoopCounter" = "'McuPublishedInformation/McuResetReasonConf'"!][!//
[!LOOP "node:ref($LoopCounter)/*"!][!//
  [!NOCODE!][!//
    [!VAR "SymbolicName" = "concat('McuConf_McuResetReasonConf_',node:name(.))"!]
  [!ENDNOCODE!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#ifndef [!"$SymbolicName"!]
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define [!"$SymbolicName"!]  ([!"num:i(./McuResetReason)"!]U)
#endif
[!ENDLOOP!][!//
[!/*[/cover]*/!][!//
/* Production Error reporting enable/disabled macro */
#define MCU_ENABLE_DEM_REPORT  (1U)
#define MCU_DISABLE_DEM_REPORT (0U)

/* Production Error enable/disable for Oscillator Failure */
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!VAR "McuOscFail" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1]/MCU_E_OSC_FAILURE/*[1])"!][!//
[!/*[cover parentID= {4E04A93B-FCFC-4b02-8569-1E506F1D83E2}][/cover]*/!][!//
#define MCU_E_OSC_FAILURE_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
[!/*[cover parentID={0D31720A-AEC5-4439-80B0-8DFFA733F18E}][/cover]*/!][!//
#define MCU_E_OSC_FAILURE               \
           (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_OSC_FAILURE/*[1])))"!])[!//
  [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
  [!VAR "McuOscFail" = "num:i(1)"!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
[!/*[cover parentID={450D47EE-C613-467c-812B-C030C3DDC2F2}][/cover]*/!][!//
#define MCU_E_OSC_FAILURE_DEM_REPORT     (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* Production Error enable/disable for system PLL Timeout */
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!VAR "McuSysPllTimeOut" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1]/MCU_E_SYSTEM_PLL_TIMEOUT_ERR/*[1])"!][!//
  [!IF "node:refexists(McuDemEventParameterRefsConf/*[1]/MCU_E_SYSTEM_PLL_TIMEOUT_ERR/*[1]) and (node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_SYSTEM_PLL_TIMEOUT_ERR/*[1]) != ' ' )"!][!//
[!/*[cover parentID= {1D2A5A0F-8C11-4ffa-8BBC-078C773082EF}][/cover]*/!][!//
#define MCU_E_SYSTEM_PLL_TIMEOUT_ERR_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
[!/*[cover parentID= {D9327BAC-0644-44a4-8678-C4AA11010126}][/cover]*/!][!//
#define MCU_E_SYSTEM_PLL_TIMEOUT_ERR                \
           (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_SYSTEM_PLL_TIMEOUT_ERR/*[1])))"!])[!//
    [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
    [!VAR "McuSysPllTimeOut" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
[!/*[cover parentID= {EE8DA45D-147C-4ec9-A845-0335DC6A14A1}][/cover]*/!][!//
#define MCU_E_SYSTEM_PLL_TIMEOUT_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//


/* Production Error enable/disable for Peripheral PLL Timeout */
[!/*[cover parentID={4166BC28-387E-4748-AF1A-63D722C1BA2C}] [/cover]*/!][!//
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!VAR "McuPerPllTimeOut" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1]/MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR/*[1])"!][!//
  [!IF "node:refexists(McuDemEventParameterRefsConf/*[1]/MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR/*[1]) and (node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR/*[1]) != ' ' )"!][!//

/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
[!/*[cover parentID= {8B624B40-6685-4403-9175-EDF34838BFE9}][/cover]*/!][!//
#define MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR                \
           (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR/*[1])))"!])[!//
    [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
    [!VAR "McuPerPllTimeOut" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define MCU_E_PERIPHERAL_PLL_TIMEOUT_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* Production Error enable/disable for system PLL lock loss */
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!VAR "McuSysPllLockLoss" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1]/MCU_E_SYSTEM_PLL_LOCK_LOSS/*[1])"!][!//
[!/*[cover parentID={8DB3DDCF-216F-4cc5-8FA1-F0C85C6A38E1}][/cover]*/!][!//
#define MCU_E_SYSTEM_PLL_LOCK_LOSS_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
[!/*[cover parentID={C777FE59-0045-4282-9D8A-721F9B834EDB}][/cover]*/!][!//
[!/*[cover parentID={E9C7373C-09C0-4dc8-8A13-E042F77A4290}][/cover]*/!][!//
#define MCU_E_SYSTEM_PLL_LOCK_LOSS                \
           (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_SYSTEM_PLL_LOCK_LOSS/*[1])))"!])[!//
  [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
  [!VAR "McuSysPllLockLoss" = "num:i(1)"!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
[!/*[cover parentID={4E04A93B-FCFC-4b02-8569-1E506F1D83E2}][/cover]*/!][!//
#define MCU_E_SYSTEM_PLL_LOCK_LOSS_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* Production Error enable/disable for peripheral PLL lock loss */
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!VAR "McuPerPllLockLoss" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1]/MCU_E_PERIPHERAL_PLL_LOCK_LOSS/*[1])"!][!//
[!/*[cover parentID={69218AE2-F7A6-43f3-A834-E5637E6C7C71}][/cover]*/!][!//
#define MCU_E_PERIPHERAL_PLL_LOCK_LOSS_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
[!/*[cover parentID={02307940-EC02-42de-995C-BE563206D792}][/cover]*/!][!//
[!/*[cover parentID={37A2CD56-596F-4018-A7B7-58AFB7DA19E3}][/cover]*/!][!//
#define MCU_E_PERIPHERAL_PLL_LOCK_LOSS                \
           (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_PERIPHERAL_PLL_LOCK_LOSS/*[1])))"!])[!//
  [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
  [!VAR "McuPerPllLockLoss" = "num:i(1)"!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
#define MCU_E_PERIPHERAL_PLL_LOCK_LOSS_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* Production Error enable/disable for GTM module enable failure */
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!VAR "McuGtmClcEnable" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1])"!][!//
  [!IF "node:refexists(McuDemEventParameterRefsConf/*[1]/MCU_E_GTM_CLC_ENABLE_ERR/*[1]) and (node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_GTM_CLC_ENABLE_ERR/*[1]) != ' ' )"!][!//
[!/* [cover parentID={758F684A-4746-419c-9458-F6BE184F397C}][/cover]*/!][!//
#define MCU_E_GTM_CLC_ENABLE_ERR_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
#define MCU_E_GTM_CLC_ENABLE_ERR                \
           (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_GTM_CLC_ENABLE_ERR/*[1])))"!])[!//
    [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
    [!VAR "McuGtmClcEnable" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
[!/* [cover parentID= {4E04A93B-FCFC-4b02-8569-1E506F1D83E2}][/cover]*/!][!//
#define MCU_E_GTM_CLC_ENABLE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* Production Error enable/disable for GTM module disable failure */
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!VAR "McuGtmClcDisable" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1])"!][!//
  [!IF "node:refexists(McuDemEventParameterRefsConf/*[1]/MCU_E_GTM_CLC_DISABLE_ERR/*[1]) and (node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_GTM_CLC_DISABLE_ERR/*[1]) != ' ' )"!][!//
[!/* [cover parentID={4DC5407F-C44E-466c-A7A5-530B51244577}][/cover]*/!][!//
#define MCU_E_GTM_CLC_DISABLE_ERR_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
#define MCU_E_GTM_CLC_DISABLE_ERR                \
            (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_GTM_CLC_DISABLE_ERR/*[1])))"!])[!//
    [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
    [!VAR "McuGtmClcDisable" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
[!/* [cover parentID= {4E04A93B-FCFC-4b02-8569-1E506F1D83E2}][/cover]*/!][!//
#define MCU_E_GTM_CLC_DISABLE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* Production Error enable/disable for CONVCTRL module enable failure */
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!VAR "McuConvCtrlClcEnable" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1])"!][!//
  [!IF "node:refexists(McuDemEventParameterRefsConf/*[1]/MCU_E_CONVCTRL_CLC_ENABLE_ERR/*[1]) and (node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_CONVCTRL_CLC_ENABLE_ERR/*[1]) != ' ' )"!][!//
[!/*[cover parentID={C3DE451C-E699-4b24-90E0-391EB02E2457}][/cover]*/!][!//
#define MCU_E_CONVCTRL_CLC_ENABLE_ERR_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
#define MCU_E_CONVCTRL_CLC_ENABLE_ERR                \
            (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_CONVCTRL_CLC_ENABLE_ERR/*[1])))"!])[!//
    [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
    [!VAR "McuConvCtrlClcEnable" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
#define MCU_E_CONVCTRL_CLC_ENABLE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* Production Error enable/disable for CONVCTRL module disable failure */
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!VAR "McuConvCtrlClcDisable" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1])"!][!//
  [!IF "node:refexists(McuDemEventParameterRefsConf/*[1]/MCU_E_CONVCTRL_CLC_DISABLE_ERR/*[1]) and (node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_CONVCTRL_CLC_DISABLE_ERR/*[1]) != ' ' )"!][!//
[!/*[cover parentID={BE0114BC-1647-4cfc-BF17-E7E0176FCF5F}][/cover]*/!][!//
#define MCU_E_CONVCTRL_CLC_DISABLE_ERR_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
[!/*[cover parentID={5179398F-3F99-418b-BF58-5F5DF68D643D}][/cover]*/!][!//
#define MCU_E_CONVCTRL_CLC_DISABLE_ERR                \
            (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_CONVCTRL_CLC_DISABLE_ERR/*[1])))"!])[!//
    [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
    [!VAR "McuConvCtrlClcDisable" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
#define MCU_E_CONVCTRL_CLC_DISABLE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* Production Error enable/disable for CCUCON0 update inability (LCK bit set) */
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!VAR "McuCcuconUpErr" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1])"!][!//
  [!IF "node:refexists(McuDemEventParameterRefsConf/*[1]/MCU_E_CCUCON_UPDATE_ERR/*[1]) and (node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_CCUCON_UPDATE_ERR/*[1]) != ' ' )"!][!//
[!/*[cover parentID={91BDF9B4-8388-4d6f-836B-6C0BBBE0FD12}] [/cover]*/!][!//
#define MCU_E_CCUCON_UPDATE_ERR_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
[!/*[cover parentID={93B276EF-67CD-49e9-9170-166C01FC0C67}] [/cover]*/!][!//
#define MCU_E_CCUCON_UPDATE_ERR                \
            (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_CCUCON_UPDATE_ERR/*[1])))"!])[!//
    [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
    [!VAR "McuCcuconUpErr" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
#define MCU_E_CCUCON_UPDATE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* Production Error enable/disable for CCU6 kernel enable */
[!/*[cover parentID={5271EEF5-C873-4b67-9535-FD1DA452E35E}] [/cover]*/!][!//
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!VAR "McuCcu6ClcEnable" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1])"!][!//
  [!IF "node:refexists(McuDemEventParameterRefsConf/*[1]/MCU_E_CCU6_CLC_ENABLE_ERR/*[1]) and (node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_CCU6_CLC_ENABLE_ERR/*[1]) != ' ' )"!][!//

#define MCU_E_CCU6_CLC_ENABLE_ERR_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
#define MCU_E_CCU6_CLC_ENABLE_ERR                \
            (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_CCU6_CLC_ENABLE_ERR/*[1])))"!])[!//
    [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
    [!VAR "McuCcu6ClcEnable" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
[!/*[cover parentID= {4E04A93B-FCFC-4b02-8569-1E506F1D83E2}] [/cover]*/!][!//
#define MCU_E_CCU6_CLC_ENABLE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* Production Error enable/disable for CCU6 kernel disable */
[!/*[cover parentID={2B7C0E50-0F19-4259-87E9-F0E86D386464}] [/cover]*/!][!//
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!VAR "McuCcu6ClcDisable" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1])"!][!//
  [!IF "node:refexists(McuDemEventParameterRefsConf/*[1]/MCU_E_CCU6_CLC_DISABLE_ERR/*[1]) and (node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_CCU6_CLC_DISABLE_ERR/*[1]) != ' ' )"!][!//

#define MCU_E_CCU6_CLC_DISABLE_ERR_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
#define MCU_E_CCU6_CLC_DISABLE_ERR                \
            (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_CCU6_CLC_DISABLE_ERR/*[1])))"!])[!//
    [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
    [!VAR "McuCcu6ClcDisable" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
#define MCU_E_CCU6_CLC_DISABLE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* Production Error enable/disable for GPT12 module enable */
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!VAR "McuGpt12ClcEnable" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1])"!][!//
  [!IF "node:refexists(McuDemEventParameterRefsConf/*[1]/MCU_E_GPT12_CLC_ENABLE_ERR/*[1]) and (node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_GPT12_CLC_ENABLE_ERR/*[1]) != ' ' )"!][!//
[!/*[cover parentID={597E48C0-FC34-461f-B5A5-ACB49A2E3155}][/cover]*/!][!//
#define MCU_E_GPT12_CLC_ENABLE_ERR_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
#define MCU_E_GPT12_CLC_ENABLE_ERR                \
            (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_GPT12_CLC_ENABLE_ERR/*[1])))"!])[!//
    [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
    [!VAR "McuGpt12ClcEnable" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
#define MCU_E_GPT12_CLC_ENABLE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

/* Production Error enable/disable for GPT12 module disable */
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!VAR "McuGpt12ClcDisable" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1])"!][!//
  [!IF "node:refexists(McuDemEventParameterRefsConf/*[1]/MCU_E_GPT12_CLC_DISABLE_ERR/*[1]) and (node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_GPT12_CLC_DISABLE_ERR/*[1]) != ' ' )"!][!//
[!/*[cover parentID={A6E9068E-7136-45c3-9E0B-043D0C5A7CCD}][/cover]*/!][!//
#define MCU_E_GPT12_CLC_DISABLE_ERR_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
#define MCU_E_GPT12_CLC_DISABLE_ERR                \
            (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_GPT12_CLC_DISABLE_ERR/*[1])))"!])[!//
    [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
    [!VAR "McuGpt12ClcDisable" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
#define MCU_E_GPT12_CLC_DISABLE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//


/* Production Error enable/disable for PMSWCRx update inability (BUSY bit) */
[!/*[cover parentID={E84B44DE-95A1-4500-881B-F7FD9C929EEB}][/cover]*/!][!//
[!VAR "McuDemReportStatus" = "num:i(0)"!][!//
[!VAR "McuPmswcrUpErr" = "num:i(0)"!][!//
[!IF "node:exists(McuDemEventParameterRefsConf/*[1])"!][!//
  [!IF "node:refexists(McuDemEventParameterRefsConf/*[1]/MCU_E_PMSWCR_UPDATE_ERR/*[1]) and (node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_PMSWCR_UPDATE_ERR/*[1]) != ' ' )"!][!//

#define MCU_E_PMSWCR_UPDATE_ERR_DEM_REPORT    (MCU_ENABLE_DEM_REPORT)
#define MCU_E_PMSWCR_UPDATE_ERR                \
            (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(McuDemEventParameterRefsConf/*[1]/MCU_E_PMSWCR_UPDATE_ERR/*[1])))"!])[!//
    [!VAR "McuDemReportStatus" = "num:i(1)"!][!//
    [!VAR "McuPmswcrUpErr" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!IF "$McuDemReportStatus = num:i(0)"!][!//
#define MCU_E_PMSWCR_UPDATE_ERR_DEM_REPORT    (MCU_DISABLE_DEM_REPORT)
[!ENDIF!][!//

[!IF "($McuOscFail = num:i(1)) or ($McuSysPllTimeOut = num:i(1)) or ($McuPerPllTimeOut = num:i(1)) or ($McuSysPllLockLoss = num:i(1)) or ($McuPerPllLockLoss = num:i(1)) or ($McuGtmClcEnable = num:i(1)) or ($McuGtmClcDisable = num:i(1)) or ($McuConvCtrlClcEnable = num:i(1)) or ($McuConvCtrlClcDisable = num:i(1)) or ($McuCcuconUpErr = num:i(1)) or ($McuCcu6ClcEnable = num:i(1)) or ($McuCcu6ClcDisable = num:i(1)) or ($McuGpt12ClcEnable = num:i(1)) or ($McuGpt12ClcDisable = num:i(1)) or ($McuPmswcrUpErr = num:i(1))"!][!//
#define MCU_E_ERR_DEM_REPORTING      (STD_ON)
[!ELSE!]    
#define MCU_E_ERR_DEM_REPORTING      (STD_OFF)
[!ENDIF!][!//
/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
[!ENDSELECT!][!//

#endif /* end of MCU_CFG_H */

