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
**  FILENAME  : Dsadc_Cfg.h                                                   **
**                                                                            **
**  VERSION   : 11.0.0                                                        **
**                                                                            **
**  DATE      : 2023-05-19                                                    **
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
**  TRACEABILITY : [cover parentID={1818A65E-1F63-413d-998A-DB78E1B995B7}]    **
**                                                                            **
**  DESCRIPTION  : Code template header file for Dsadc Driver                 **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of DSADC Driver                          **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*************************************************************************/!][!//
[!//
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
**  FILENAME  : Dsadc_Cfg.h                                                   **
**                                                                            **
**  VERSION   : 11.0.0                                                        **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]        !!!IGNORE-LINE!!!                 **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]          !!!IGNORE-LINE!!!                 **
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
**  DESCRIPTION  : Dsadc configuration generated out of ECUC file             **
**                                                                            **
**  SPECIFICATION(S) : Specification of DSADC Driver                          **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef DSADC_CFG_H
#define DSADC_CFG_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
[!NOCODE!]
  [!INCLUDE "Dsadc.m"!][!//
[!ENDNOCODE!]
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
[!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
[!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
[!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
[!/* [cover parentID={7E0A0621-195B-4251-A9EF-BDFF8DE883C0}]DSADC_AR_RELEASE_MAJOR_VERSION[/cover] */!][!//
#define DSADC_AR_RELEASE_MAJOR_VERSION      ([!"$MajorVersion"!]U)
[!/* [cover parentID={6BF82E32-23D6-4fc6-91D6-58DFBA8A2360}]DSADC_AR_RELEASE_MINOR_VERSION[/cover] */!][!//
#define DSADC_AR_RELEASE_MINOR_VERSION      ([!"$MinorVersion"!]U)
[!/* [cover parentID={786B4EBB-99CD-471a-B904-F00164269C3C}]DSADC_AR_RELEASE_REVISION_VERSION[/cover] */!][!//
#define DSADC_AR_RELEASE_REVISION_VERSION   ([!"$RevisionVersion"!]U)

[!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
[!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
[!VAR "SwPatchVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
[!/* [cover parentID={521C6C30-7C38-41fe-B78E-37AAB476BE90}]DSADC_SW_MAJOR_VERSION[/cover] */!][!//
#define DSADC_SW_MAJOR_VERSION  ([!"$SwMajorVersion"!]U)
[!/* [cover parentID={82188C61-315F-46d8-90D2-661F8C0D8FFA}]DSADC_SW_MINOR_VERSION[/cover] */!][!//
#define DSADC_SW_MINOR_VERSION  ([!"$SwMinorVersion"!]U)
[!/* [cover parentID={08803BCC-A8D2-405b-80B8-CB1D6549BF89}]DSADC_SW_PATCH_VERSION[/cover] */!][!//
#define DSADC_SW_PATCH_VERSION  ([!"$SwPatchVersion"!]U)

[!/* [cover parentID={3AC02878-50EA-40cc-B4E1-45354B737B5C}] Number of DSADC channels available[/cover] */!][!//
#define DSADC_NUM_OF_CHANNELS              ([!"num:inttohex(ecu:get('Dsadc.NoOfChannels'))"!]U)

/* Configuration Options for DEM Options for the enabling/disabling of
   DEM in DSADC Driver */
#define DSADC_DISABLE_DEM_REPORT    (0x0U)
#define DSADC_ENABLE_DEM_REPORT     (0x1U)

/*Configuration option for DSADC Channel Access Mode*/
#define DSADC_SINGLE_READ           (0x0U)
#define DSADC_CIRCULAR_BUFFER       (0x1U)
#define DSADC_STREAM_LINEAR_BUFFER  (0x2U)
#define DSADC_DMA_ACCESS            (0x3U)

/*Configuration option for DSADc Channel Timestamp function availability*/
#define DSADC_TIMESTAMP_DISABLED    (0x0U)
#define DSADC_TIMESTAMP_ENABLED     (0x1U)

/*Configuration option for DSADC Channel Timestamp Trigger function availability*/
#define DSADC_NO_TIMESTAMP_TRIGGER  (0x0U)
#define DSADC_TIMESTAMP_WINDOWOPEN  (0x1U)
#define DSADC_TIMESTAMP_WINDOWCLOSE (0x2U)

/*Configuration option for DSADC Channel Trigger Mode*/
#define DSADC_TRIGGER_MODE_NORMAL   (0x0U)
#define DSADC_TRIGGER_MODE_WINDOW   (0x1U)

/*Configuration option for DSADC Channel Gate signla Active level*/
#define DSADC_GATE_HIGH_LEVEL       (0x0U)
#define DSADC_GATE_LOW_LEVEL        (0x1U)

/*Configuration option for Carrier Signal Type */
#define DSADC_CARR_SIG_STOPPED      (0x0U)
#define DSADC_CARR_SIG_SQUAREWAVE   (0x1U)
#define DSADC_CARR_SIG_TRIANGLE     (0x2U)
#define DSADC_CARR_SIG_SINEWAVE     (0x3U)

/* Type of Trigger Source when the Trigger mode is Window  */
#define DSADC_TRIGGER_NONE          (0x0U)
#define DSADC_TRIGGER_GTM           (0x1U)
#define DSADC_TRIGGER_ERU           (0x2U)

/* Configuration Options for the setting the privilege mode in DSADC Driver */
#define DSADC_SUPERVISOR_MODE  (0U)
#define DSADC_USER1_MODE  (1U)

[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Dsadc')[1]"!][!//
/* Derived Configuration for DsadcDevErrorDetect */
[!/* [cover parentID={B6480DA6-96BC-434b-91A3-52272AE7C26C}] DSADC_DEV_ERROR_DETECT [/cover] */!][!//
#define DSADC_DEV_ERROR_DETECT            [!//
[!CALL "Dsadc_ConfigPreCompileSwitch","NodeVal" = "DsadcGeneral/DsadcDevErrorDetect"!][!//

/* Derived Configuration for DsadcDeInitApi */
[!/* [cover parentID={60B10D25-4FDE-4d59-90CF-B4DF44325AFF}]DSADC_DEINIT_API[/cover] */!][!//
#define DSADC_DEINIT_API                  [!//
[!CALL "Dsadc_ConfigPreCompileSwitch","NodeVal" = "DsadcGeneral/DsadcDeInitApi"!][!//

[!/* [cover parentID={90C3DF65-8DB5-4765-8100-F582F7FF3198}] DSADC_SAFETY_ENABLE [/cover] */!][!//
/* Derived Configuration for DsadcSafetyEnable */
#define DSADC_SAFETY_ENABLE               [!//
[!CALL "Dsadc_ConfigPreCompileSwitch","NodeVal" = "DsadcGeneral/DsadcSafetyEnable"!][!//

/* Derived Configuration for DsadcInitCheckApi */
[!/* [cover parentID={33CD96D2-8DED-45ac-BAC0-2D51BB308F22}] DSADC_INITCHECK_API [/cover] */!][!//
#define DSADC_INITCHECK_API               [!CALL "Dsadc_ConfigPreCompileSwitch", "NodeVal" = "./DsadcGeneral/DsadcInitCheckApi"!]

/* Derived Configuration for DsadcVersionInfoApi */
[!/* [cover parentID={6247BAD5-D47D-4f6f-825D-96947B6E8EEB}] DSADC_VERSION_INFO_API [/cover] */!][!//
#define DSADC_VERSION_INFO_API            [!CALL "Dsadc_ConfigPreCompileSwitch", "NodeVal" = "./DsadcGeneral/DsadcVersionInfoApi"!]

/* Derived Configuration for DsadcRestartIntegratorApi */
[!/* [cover parentID={F4C94749-B88B-4345-9608-52FA7144B654}]DSADC_RESTART_INTEGRATOR_API[/cover] */!][!//
#define DSADC_RESTART_INTEGRATOR_API                  [!//
[!CALL "Dsadc_ConfigPreCompileSwitch","NodeVal" = "DsadcGeneral/DsadcRestartIntegratorApi"!][!//

/* Configuration: DSADC_INIT_DEINIT_API_MODE
Determines the privilege mode in which the Initialization and De-initialization APIs would operate*/
[!/* [cover parentID={65EC2A71-EE97-4bab-AC5C-9713212BF5AD}] DSADC_INIT_DEINIT_API_MODE [/cover] */!][!//
[!VAR "DsadcMode"="'DSADC_SUPERVISOR_MODE'"!][!//
[!IF "DsadcGeneral/DsadcInitDeInitApiMode = 'DSADC_MCAL_USER1'"!][!//
  [!VAR "DsadcMode"="'DSADC_USER1_MODE'"!][!//
[!ENDIF!][!//
#define DSADC_INIT_DEINIT_API_MODE          ([!"$DsadcMode"!])

/* Configuration: DSADC_RUN_TIME_API_MODE
Determines the privilege mode in which the runtime APIs would operate*/
[!/* [cover parentID={8BB0CB09-F581-45fe-81B1-79BEA080CC23}]Precompile Time support for User Mode[/cover] */!][!//
[!/* [cover parentID={C76C4B31-E676-476a-A709-3DC9E608A405}] DSADC_RUN_TIME_API_MODE [/cover] */!][!//
[!VAR "DsadcMode"="'DSADC_SUPERVISOR_MODE'"!][!//
[!IF "DsadcGeneral/DsadcRuntimeApiMode = 'DSADC_MCAL_USER1'"!][!//
[!VAR "DsadcMode"="'DSADC_USER1_MODE'"!][!//
[!ENDIF!][!//
#define DSADC_RUN_TIME_API_MODE             ([!"$DsadcMode"!])

[!VAR "Dsadc_Gtm_Used" = "'STD_OFF'"!][!//
[!VAR "Dsadc_Eru_Used" = "'STD_OFF'"!][!//
[!VAR "Dsadc_AllCh_ResultHandling_DMA" = "'STD_ON'"!][!//
[!VAR "SettingsIndex" = "num:i(0)"!][!//
[!VAR "ChannelId" = "num:i(0)"!][!//
[!VAR "DsadcMaxChannels"= "num:i(count(DsadcConfigSet/*[1]/DsadcChannelConfiguration/*))"!][!//
[!FOR "ChannelId" = "num:i(0)" TO "num:i($DsadcMaxChannels) - num:i(1)"!][!//
[!IF "contains(DsadcConfigSet/*[@index = $SettingsIndex]/DsadcChannelConfiguration/*[DsadcChannelId = num:i($ChannelId)]/DsadcDemodulatorConfiguration/*[1]/DsadcTriggerSelect,'GTM')"!][!//
[!VAR "Dsadc_Gtm_Used" = "'STD_ON'"!][!//
[!ELSEIF "contains(DsadcConfigSet/*[@index = $SettingsIndex]/DsadcChannelConfiguration/*[DsadcChannelId = num:i($ChannelId)]/DsadcDemodulatorConfiguration/*[1]/DsadcTriggerSelect,'ERU')"!][!//
[!VAR "Dsadc_Eru_Used" = "'STD_ON'"!][!//
[!ENDIF!][!//
[!VAR "Dsadc_AllCh_ResultHandling" = "DsadcConfigSet/*[@index = $SettingsIndex]/DsadcChannelConfiguration/*[DsadcChannelId = num:i($ChannelId)]/DsadcAccessMode"!][!//
[!IF "$Dsadc_AllCh_ResultHandling != 'DSADC_DMA_ACCESS'"!][!//
[!VAR "Dsadc_AllCh_ResultHandling_DMA" = "'STD_OFF'"!][!//
[!ENDIF!][!//
[!ENDFOR!][!//

/* Configuration: DSADC_GTMTRIGGER_USED
Pre Compile switch to determine any channel is using GTM or not.*/
[!/* [cover parentID={159C1966-6253-4215-B679-959EA132E028}]DSADC_GTMTRIGGER_USED[/cover] */!][!//
#define DSADC_GTMTRIGGER_USED               ([!"$Dsadc_Gtm_Used"!])

/* Configuration: DSADC_ERUTRIGGER_USED
Pre Compile switch to determine any channel is using ERU or not.*/
[!/* [cover parentID={CD0EDD04-6583-4779-B6DB-93BEB8C5EE31}]DSADC_ERUTRIGGER_USED[/cover] */!][!//
#define DSADC_ERUTRIGGER_USED               ([!"$Dsadc_Eru_Used"!])

/* Configuration: DSADC_ALL_CH_RESULT_HANDLING_DMA
Pre Compile switch to determine whether all channels are using the DMA or not.*/
[!/* [cover parentID={3A37B5DC-777A-4736-BF30-46C7EEFEB4A5}]DSADC_ALL_CH_RESULT_HANDLING_DMA[/cover] */!][!//
#define DSADC_ALL_CH_RESULT_HANDLING_DMA    ([!"$Dsadc_AllCh_ResultHandling_DMA"!])
/* Configured DSADC Channels Symbolic Names */
[!LOOP "DsadcConfigSet/*[1]/DsadcChannelConfiguration/*"!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code to be in sync with  Autosar Naming constraints.
No side effects foreseen by violating this MISRA rule.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code to be in sync with  Autosar Naming constraints.
No side effects foreseen by violating this MISRA rule.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code to be in sync with  Autosar Naming constraints.
No side effects foreseen by violating this MISRA rule.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code to be in sync with  Autosar Naming constraints.
No side effects foreseen by violating this MISRA rule.*/
#ifndef DsadcChannel_[!"node:name(.)"!]
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code to be in sync with  Autosar Naming constraints.
No side effects foreseen by violating this MISRA rule.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code to be in sync with  Autosar Naming constraints.
No side effects foreseen by violating this MISRA rule.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code to be in sync with  Autosar Naming constraints.
No side effects foreseen by violating this MISRA rule.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
in generated code to be in sync with  Autosar Naming constraints.
No side effects foreseen by violating this MISRA rule.*/
[!/* [cover parentID={7C0A440E-6B6A-48b4-B64F-DC0B07941869}]DsadcChannel_<DsadcChannelName>[/cover] */!][!//  
#define DsadcChannel_[!"node:name(.)"!]     ((Dsadc_ChannelType)[!"num:inttohex(DsadcChannelId)"!]U)
#endif
[!ENDLOOP!][!//

/* Number of DSADC channels configured */
[!/* [cover parentID={F06FBB8B-F138-47b3-922F-4C94C203F559}] DSADC_MAX_CHANNELS_CONFIGURED [/cover] */!][!//
#define DSADC_MAX_CHANNELS_CONFIGURED                ((Dsadc_ChannelType)[!"$DsadcMaxChannels"!]U)

[!/* [cover parentID={5B8F1A07-91C5-4cbb-A51B-39404E99B4D5}] DSADC_MAX_ERS_CHANNELS_CONFIGURED [/cover] */!][!//
/* Number of ERS channels configured for DSADC driver for pattern detection*/
[!VAR "ErsMaxChannels"= "num:i(count(DsadcConfigSet/*[1]/DsadcErsEtlConfig/*))"!][!//
#define DSADC_MAX_ERS_CHANNELS_CONFIGURED            ([!"$ErsMaxChannels"!]U)

/* Configuration: DSADC_CLC_FAILURE_DEM_NOTIF Determines whether Production Error for CLC failure is enabled or disabled */
[!IF "(node:exists(DsadcDemEventParameterRefs/*[1]))"!][!//
[!SELECT "DsadcDemEventParameterRefs/*[1]"!][!//
[!IF "(node:exists(./DsadcClcFailureNotification/*[1]))"!][!//
[!/* [cover parentID={BCE2EF7C-BAA7-489d-AC8A-053A714384CA}]DSADC_CLC_FAILURE_DEM_NOTIF[/cover] */!][!//
#define DSADC_CLC_FAILURE_DEM_NOTIF   (DSADC_ENABLE_DEM_REPORT)
[!/* [cover parentID={E77C7462-990D-4166-B82A-C2434978D866}]DSADC_E_CLC_FAILURE[/cover] */!][!//
[!/* [cover parentID={F7815DD7-C448-4277-AAAA-82B0824A0C88}]DSADC_E_CLC_FAILURE[/cover] */!][!//
#define DSADC_E_CLC_FAILURE           (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./DsadcClcFailureNotification/*[1])))"!])
[!ELSE!][!//
[!/* [cover parentID={BCE2EF7C-BAA7-489d-AC8A-053A714384CA}]DSADC_CLC_FAILURE_DEM_NOTIF[/cover] */!][!//
#define DSADC_CLC_FAILURE_DEM_NOTIF   (DSADC_DISABLE_DEM_REPORT)
[!ENDIF!][!//
[!IF "(node:exists(./DsadcFifoFailureNotification/*[1]))"!][!//
[!/* [cover parentID={EA808181-B0CA-4757-B9E6-50D295F162A5}]DSADC_FIFO_FAILURE_DEM_NOTIF[/cover] */!][!//
#define DSADC_FIFO_FAILURE_DEM_NOTIF  (DSADC_ENABLE_DEM_REPORT)
[!/* [cover parentID={755F2D21-4A27-4261-AF61-173274EE0934}]DSADC_E_FIFO_FAILURE[/cover] */!][!//
[!/* [cover parentID={5A0C1F84-2089-4415-9277-82386CE5DF91}]DSADC_E_FIFO_FAILURE[/cover] */!][!//
#define DSADC_E_FIFO_FAILURE          (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./DsadcFifoFailureNotification/*[1])))"!])
[!ELSE!][!//
[!/* [cover parentID={EA808181-B0CA-4757-B9E6-50D295F162A5}]DSADC_FIFO_FAILURE_DEM_NOTIF[/cover] */!][!//
#define DSADC_FIFO_FAILURE_DEM_NOTIF  (DSADC_DISABLE_DEM_REPORT)
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ELSE!][!//
[!/* [cover parentID={BCE2EF7C-BAA7-489d-AC8A-053A714384CA}]DSADC_CLC_FAILURE_DEM_NOTIF[/cover] */!][!//
#define DSADC_CLC_FAILURE_DEM_NOTIF   (DSADC_DISABLE_DEM_REPORT)
[!/* [cover parentID={EA808181-B0CA-4757-B9E6-50D295F162A5}]DSADC_FIFO_FAILURE_DEM_NOTIF[/cover] */!][!//
#define DSADC_FIFO_FAILURE_DEM_NOTIF  (DSADC_DISABLE_DEM_REPORT)
[!ENDIF!][!//

[!ENDSELECT!][!//

#endif  /* DSADC_CFG_H */

