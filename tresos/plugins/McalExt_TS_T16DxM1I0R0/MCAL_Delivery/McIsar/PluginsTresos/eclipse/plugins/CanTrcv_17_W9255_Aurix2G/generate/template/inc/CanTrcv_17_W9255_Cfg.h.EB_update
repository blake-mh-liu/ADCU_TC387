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
**  FILENAME  : CanTrcv_17_W9255_Cfg.h                                        **
**                                                                            **
**  VERSION   : 4.0.0                                                         **
**                                                                            **
**  DATE      : 2020-08-10                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : CanTrcv_17_W9255.bmd                              **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={4E0D40FA-8B8F-4280-9CD2-58E883C93139}]    **
**                 [cover parentID={B22F34A4-4DDC-4a5c-8B4F-A4822EC9B363}]    **
**                                                                            **
**  DESCRIPTION  : Code template header file for CanTrcv Driver               **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of CanTrcv Driver, AUTOSAR Release 4.2.2 **
**                     and AUTOSAR Release 4.4.0                              **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*************************************************************************/!][!//
[!//
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
**  FILENAME  : CanTrcv_17_W9255_Cfg.h                                        **
**                                                                            **
**  VERSION   : 4.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]       !!!IGNORE-LINE!!!                  **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]           !!!IGNORE-LINE!!!                **
**                                                                            **
**  BSW MODULE DECRIPTION : CanTrcv_17_W9255.bmd                              **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : CanTrcv configuration generated out of ECUC file           **
**                                                                            **
**  SPECIFICATION(S) : Specification of CanTrcv Driver, AUTOSAR Release 4.2.2 **
**                       and AUTOSAR Release 4.4.0                            **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/******************************************************************************/
[!AUTOSPACING!]
#ifndef CANTRCV_17_W9255_CFG_H
#define CANTRCV_17_W9255_CFG_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Include Icu header file */
#include "Icu_17_TimerIp.h"
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "(as:stod( 'AURIX2G_W9255/EcucDefs/CanTrcv'))"!][!//
[!INDENT "0"!][!//
[!VAR "CanTrcvConfigSetName" = "'CanTrcvConfigSet'"!][!//
/* CAN transceiver module instance Id */
[!/* [cover parentID={79F3A41D-33B2-4fb6-B8C8-F30BA710B1FA}] [/cover] */!][!//
#define CANTRCV_17_W9255_INSTANCE_ID                     ((uint8)[!"CanTrcvGeneral/CanTrcvIndex"!])
[!CR!][!//
/*Autosar Specific Version Information*/
[!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
[!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
[!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
[!VAR "NewString" = "text:replaceAll($moduleReleaseVer,"\.",'')"!][!//
[!IF "$MajorVersion = num:i(4)"!][!//
  [!/* [cover parentID={8CEF61C5-49A1-4c8b-8377-2D2A638F19C1}] [/cover] */!][!//
  #define CANTRCV_17_W9255_AR_RELEASE_MAJOR_VERSION        ([!"$MajorVersion"!]U)
  [!/* [cover parentID={047A9B76-0010-41cb-9160-9E7EFD9ACBC8}] [/cover] */!][!//
  #define CANTRCV_17_W9255_AR_RELEASE_MINOR_VERSION        ([!"$MinorVersion"!]U)
  [!/* [cover parentID={538878B9-9933-4c7f-8B2F-2A28F3611BF4}] [/cover] */!][!//
  #define CANTRCV_17_W9255_AR_RELEASE_REVISION_VERSION     ([!"$RevisionVersion"!]U)
[!ENDIF!]
[!CR!][!//
[!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
[!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
[!VAR "SwRevisionVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
/* Software Version Information */
[!/* [cover parentID={6691D32C-1EB0-457e-A24D-19EF9B0ADD85}] [/cover] */!][!//
#define CANTRCV_17_W9255_SW_MAJOR_VERSION                ([!"$SwMajorVersion"!]U)
[!/* [cover parentID={B93E0008-6422-482a-9DC7-099DE035D1E1}] [/cover] */!][!//
#define CANTRCV_17_W9255_SW_MINOR_VERSION                ([!"$SwMinorVersion"!]U)
[!/* [cover parentID={082A6729-4E08-461b-B47D-C8150A8BE59C}] [/cover] */!][!//
#define CANTRCV_17_W9255_SW_PATCH_VERSION                ([!"$SwRevisionVersion"!]U)
[!CR!][!//
/*
Configuration: CANTRCV_17_W9255_DEV_ERROR_DETECT
Preprocessor switch for enabling the development error detection and
reporting.
- if STD_ON, DET is Enabled
- if STD_OFF, DET is Disabled
*/
[!/* [cover parentID={65AE7D98-33C4-412f-A774-BF1CF5165F38}] [/cover] */!][!//
#define CANTRCV_17_W9255_DEV_ERROR_DETECT                ([!//
[!IF "CanTrcvGeneral/CanTrcvDevErrorDetect = 'true'"!][!//
  STD_ON[!//
[!ELSE!][!//
  STD_OFF[!//
[!ENDIF!][!//
)
[!CR!][!//
/*
Configuration: CANTRCV_17_W9255_GENERAL_WAKE_UP_SUPPORT
Wake-up modes supported by the transceiver
- INTERRUPT: Wake-up by Interrupt mode
- POLLING: Wake-up by Polling mode
*/
[!/* [cover parentID={A3F2958B-2AE9-4020-896D-6B13F3EA8270}] [/cover] */!][!//
[!IF "CanTrcvGeneral/CanTrcvWakeUpSupport = 'CANTRCV_17_W9255_WAKE_UP_BY_INTERRUPT'"!][!//
  #define CANTRCV_17_W9255_GENERAL_WAKE_UP_SUPPORT      (CANTRCV_17_W9255_WAKE_UP_BY_INTERRUPT)
[!ELSEIF "CanTrcvGeneral/CanTrcvWakeUpSupport = 'CANTRCV_17_W9255_WAKE_UP_BY_POLLING'"!][!//
  #define CANTRCV_17_W9255_GENERAL_WAKE_UP_SUPPORT      (CANTRCV_17_W9255_WAKE_UP_BY_POLLING)
[!ENDIF!][!//
[!CR!][!//
/*
Configuration: CANTRCV_17_W9255_GET_VERSION_INFO
Version Information API configuration
- if STD_ON, Function CanTrcv_17_W9255_GetVersionInfo is available
- if STD_OFF, Function CanTrcv_17_W9255_GetVersionInfo is not available
*/
[!/* [cover parentID={EF818A46-BD17-46d7-AE9E-85CE67F7ADEE}] [/cover] */!][!//
#define CANTRCV_17_W9255_GET_VERSION_INFO                ([!//
[!IF "$MinorVersion = num:i(2)"!][!//
    [!IF "CanTrcvGeneral/CanTrcvGetVersionInfo = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
[!ELSE!][!//
    [!IF "CanTrcvGeneral/CanTrcvVersionInfoApi = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
[!ENDIF!][!//
)
[!CR!][!//
/*
Configuration: CANTRCV_17_W9255_WAIT_TIME (Unit is nanoseconds)
Wait time for transceiver mode changes
*/
[!/* [cover parentID={BCD20110-F83A-4e36-ACAA-3448D292B1B0}] [/cover] */!][!//
[!VAR "CanTrcvWaitTime" = "CanTrcvGeneral/CanTrcvWaitTime/*[1]"!][!//
#define CANTRCV_17_W9255_WAIT_TIME                       ([!"num:i(($CanTrcvWaitTime) * num:i(1000000000))"!]U)
[!CR!][!//
/*
Configuration: CANTRCV_17_W9255_SPI_COMM_RETRIES
Indicates the maximum number of communication retries in case of
failed SPI communication
*/
[!/*[cover parentID={5E1EE7D3-DC67-45ae-9556-CB1BFE00BB0E}] [/cover] */!][!//
[!IF "node:refexists(CanTrcvConfigSet/CanTrcvChannel/*/CanTrcvAccess/CanTrcvSpiSequence/*/CanTrcvSpiSequenceName/*) ='true'"!][!//
  [!VAR "CanTrcvSPICommRetries" = "CanTrcvConfigSet/CanTrcvSPICommRetries"!][!//
  #define CANTRCV_17_W9255_SPI_COMM_RETRIES                ([!"$CanTrcvSPICommRetries"!]U)
  [!CR!][!//
[!ENDIF!][!//
[!SELECT "node:ref($CanTrcvConfigSetName)"!][!//
  [!VAR "ChannelCount" = "0"!][!//
  [!VAR "Flag1" = "num:i(0)"!][!//
  [!LOOP "CanTrcvChannel/*"!][!//
    [!VAR "CanTrcvChUsed" = "./CanTrcvChannelUsed"!][!//
    [!VAR "Wakeupbybusused" = "./CanTrcvWakeupByBusUsed"!][!//
    [!IF "$CanTrcvChUsed = 'true'"!][!//
      [!VAR "CanTrcv_ChannelId" = "./CanTrcvChannelId"!]
      [!VAR "ChannelCount" = "$ChannelCount + 1"!][!//
      [!VAR "SymbolicName" = "node:name(.)"!][!//
      [!IF "node:exists(./CanTrcvPartialNetwork/*[1])"!][!//
        [!IF "./CanTrcvPartialNetwork/*[1]/CanTrcvPnEnabled = 'true' "!][!//
          [!VAR "Flag1" = "num:i($Flag1 + num:i(1))"!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
      /* Symbolic name of CanTrcv Channel_[!"./CanTrcvChannelId"!] */
      /*
      MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
      MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
      MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
      MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
      */
      #ifndef CanTrcv_17_W9255_CanTrcvConf_CanTrcvChannel_[!"$SymbolicName"!]
      /*
      MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
      MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
      MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
      MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
      */
      [!/*[cover parentID={06E6E031-0A84-418e-BA77-ADDD311B1128}] [/cover] */!][!//
      #define CanTrcv_17_W9255_CanTrcvConf_CanTrcvChannel_[!"$SymbolicName"!]    ([!"(num:i($CanTrcv_ChannelId))"!]U)
      #endif
      [!CR!][!//
      /* Max baud rate supported for CanTrcv Channel_[!"./CanTrcvChannelId"!] */
      [!/* [cover parentID={45E80747-0C91-4652-8D76-1A4E8A9A2143}] [/cover] */!][!//
      [!VAR "CanTrcvmaxChbaudrate" = "./CanTrcvMaxBaudrate"!][!//
      #define CANTRCV_17_W9255_CH_[!"./CanTrcvChannelId"!]_MAX_BAUDRATE_SUPPORT       ([!"($CanTrcvmaxChbaudrate)"!]U)
      [!CR!][!//
      [!IF "../../../CanTrcvGeneral/CanTrcvWakeUpSupport = 'CANTRCV_17_W9255_WAKE_UP_BY_INTERRUPT'"!][!//
        [!IF "./CanTrcvWakeupByBusUsed = 'true'"!][!//
          [!IF "node:refexists(./CanTrcvIcuChannelRef/*[1]) ='true'"!][!//
            /*
            MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
            MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
            MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
            MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars. in generated code due to Autosar naming constraints.
            */
            [!/* [cover parentID={4D50F30B-6F6C-481d-82FB-61B9F4429671}] [/cover] */!][!//
            [!//
            /* Icu Channel Reference for Cantrcv Channel[!"./CanTrcvChannelId "!] to enable/disable the interrupts for wakeups */
            #define CANTRCV_17_W9255_ICU_CHANNEL_CONFIGURED_[!"./CanTrcvChannelId "!]        (IcuConf_IcuChannel_[!"node:name(node:ref(./CanTrcvIcuChannelRef/*[1]))"!])
            [!CR!][!//
/*
	  Note: Elektrobit Automotive GmbH modified the original code provided
        by the third party supplier. The modification is provided for
        convenience.
        Please use the modification on your discretion and account, or
        use the unmodified files provided with this distribution. 
  Please see for the reasons in the file ImportantNotes.txt for tag

												 
	ASCINFINEON-849 CanTrcvWakeupSourceRef parameter should not be present as a list because it is not readable by CanIf	  
*/ 
            [!IF "(node:ref(node:ref(./CanTrcvIcuChannelRef/*[1])/IcuWakeup/*[1]/IcuChannelWakeupInfo/*[1])/EcuMWakeupSourceId) != (node:ref(./CanTrcvWakeupSourceRef)/EcuMWakeupSourceId)"!]
              [!ERROR!][!//
                CanTrcv_17_W9255 Code Generator: References of CanTrcvWakeupSourceRef and IcuChannelWakeupInfo should be same for CanTrcv Channel Id [!"./CanTrcvChannelId "!]
              [!ENDERROR!][!//
            [!ENDIF!][!//
          [!ELSE!][!//
            [!ERROR!][!//
              CanTrcv_17_W9255 Code Generator: ICU channel is not referenced for CanTrcv Channel Id [!"./CanTrcvChannelId "!]
            [!ENDERROR!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
  [!/* [cover parentID={4EF833A3-9C29-4e4b-B576-9D64BA3A5906}] [/cover] */!][!//
  /* Number of channels enabled */
  #define CANTRCV_17_W9255_CHANNELS_USED                   ([!"num:i($ChannelCount)"!]U)
  [!CR!][!//
  /* Number of channels Configured for PN */
  [!/* [cover parentID={CDD43427-3841-4be6-802C-FF94F5582CCA}] [/cover] */!][!//
  #define CANTRCV_17_W9255_PN_CONFIGURED_CHANNELS          ([!"num:i($Flag1)"!]U)
  [!CR!][!//
  [!VAR "ChannelCount1" = "num:i(0)"!][!//
  [!LOOP "CanTrcvChannel/*"!][!//
    [!VAR "ChannelCount1" = "$ChannelCount1 + 1"!][!//
  [!ENDLOOP!][!//
[!ENDSELECT!][!//
/* Number of channels configured */
[!/* [cover parentID={4D2D2DFE-1636-4085-A13F-68CCB32B6226}] [/cover] */!][!//
#define CANTRCV_17_W9255_CHANNELS_CONFIGURED             ([!"num:i($ChannelCount1)"!]U)
[!ENDINDENT!][!//
[!ENDSELECT!][!//
[!CR!][!//

[!IF "$MinorVersion = num:i(4)"!][!//
/*
Configuration: CANTRCV_17_W9255_RUNTIME_ERROR_DETECT
Preprocessor switch for enabling the runtime error detection and
reporting.
- if STD_ON, Reporting runntime error is Enabled
- if STD_OFF,Reporting runntime error is Disabled
*/
[!/* [cover parentID={5489C9FC-2F5D-4460-A4D6-CC2B735B8229}] [/cover] */!][!//
#define CANTRCV_17_W9255_RUNTIME_ERROR_DETECT                ([!//
[!IF "CanTrcvGeneral/CanTrcvRunTimeErrorDetect = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)
[!ENDIF!][!//
#endif
/*END OF  CANTRCV_17_W9255_CFG_H */
