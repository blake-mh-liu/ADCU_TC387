[!/*****************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2022)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : CanTrcv_17_V9251_Cfg.h                                        **
**                                                                            **
**  VERSION   : 6.0.0                                                         **
**                                                                            **
**  DATE      : 2022-06-28                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : CanTrcv_17_V9251.bmd                              **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY :[cover parentID={C8E7F516-D1AB-4bec-A0DB-8B3F6EE476A0}]     **
**                [cover parentID={19E4B6BF-2CF1-4a8f-8E67-C62CF4550A32}]     **
**                                                                            **
**  DESCRIPTION  : Code template header file for CanTrcv_17_V9251 Driver      **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of CanTrcv Driver, AUTOSAR Release 4.2.2 **
**                                                  and AUTOSAR Release 4.4.0 **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
**                                                                            **
******************************************************************************/!][!//
[!//
/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2022)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : CanTrcv_17_V9251G_Cfg.h                                       **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]       !!!IGNORE-LINE!!!              **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]           !!!IGNORE-LINE!!!              **
**                                                                            **
**  MODULE DECRIPTION : CanTrcv_17_V9251.bmd                                  **
**                                                                            **
**  VARIANT   : VariantPC                                                     **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : CanTrcv_17_V9251 configuration generated out of            **
**                 ECU configuration file                                     **
**                                                                            **
**  SPECIFICATION(S) : Specification of CanTransceiver Driver                 **
**                     Release AUTOSAR 4.2.2                                  **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: No                                       **
*******************************************************************************/
[!AUTOSPACING!]
#ifndef CANTRCV_17_V9251_CFG_H
#define CANTRCV_17_V9251_CFG_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Include Icu header file */
#include "Icu_17_TimerIp.h"
/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
[!//
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "(as:stod( 'AURIX2G_V9251/EcucDefs/CanTrcv'))"!][!//
[!VAR "CanTrcvConfigSetName" = "'CanTrcvConfigSet'"!][!//
[!//

/* CANTRCV MODULE INSTANCE ID */
[!/* [cover parentID={C01E61FF-E988-4168-BF06-0A6200ECE1C1}] [/cover] */!][!//
#define CANTRCV_17_V9251_INSTANCE_ID                  ((uint8)[!"CanTrcvGeneral/CanTrcvIndex"!])

[!/*Section to Generate Autosar Specific Version Information */!][!//
[!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
[!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
[!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
[!VAR "NewString" = "text:replaceAll($moduleReleaseVer,"\.",'')"!]
/* Autosar specific version information */
[!IF "$MajorVersion = num:i(4)"!][!//
[!/* [cover parentID={76307BAF-70C6-4695-8DBF-77496F56A858}] [/cover] */!][!//
#define CANTRCV_17_V9251_AR_RELEASE_MAJOR_VERSION     ([!"$MajorVersion"!]U)
[!/* [cover parentID={53EB1C67-D388-4c21-A515-15D636A35AC6}] [/cover] */!][!//
#define CANTRCV_17_V9251_AR_RELEASE_MINOR_VERSION     ([!"$MinorVersion"!]U)
[!/* [cover parentID={FC67BD75-42D2-456d-BD18-D489CEC01E4D}] [/cover] */!][!//
#define CANTRCV_17_V9251_AR_RELEASE_REVISION_VERSION  ([!"$RevisionVersion"!]U)
[!ENDIF!][!//

[!/*Section to Generate Vendor Specific Version Information */!][!//
[!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
[!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
[!VAR "SwRevisionVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
/* Vendor specific implementation version information */
[!/* [cover parentID={F9FB32FA-11FC-4a78-9774-93DFED012DD4}] [/cover] */!][!//
#define CANTRCV_17_V9251_SW_MAJOR_VERSION             ([!"$SwMajorVersion"!]U)
[!/* [cover parentID={6896CC99-28D8-4fb1-94AF-EAAAF845BA2B}] [/cover] */!][!//
#define CANTRCV_17_V9251_SW_MINOR_VERSION             ([!"$SwMinorVersion"!]U)
[!/* [cover parentID={F2E0D948-6195-4f8b-B4F5-EC182EB617C8}] [/cover] */!][!//
#define CANTRCV_17_V9251_SW_PATCH_VERSION             ([!"$SwRevisionVersion"!]U)

/*
Configuration: CANTRCV_DEV_ERROR_DETECT
- if STD_ON, DET is Enabled
- if STD_OFF,DET is Disabled
*/
[!INDENT "0"!][!//
[!/* [cover parentID={C5860D9C-F770-43b6-B87B-EC15173D816B}] [/cover] */!][!//
#define CANTRCV_17_V9251_DEV_ERROR_DETECT             ([!//
[!IF "CanTrcvGeneral/CanTrcvDevErrorDetect = 'true'"!][!//
  STD_ON[!//
[!ELSE!][!//
  STD_OFF[!//
[!ENDIF!][!//
)
[!ENDINDENT!][!//
[!CR!][!//

/*
Configuration: CANTRCV_GENERAL_WAKE_UP_SUPPORT
- INTERRUPT: Only Interrupt mode is supported
*/
[!INDENT "0"!][!//
[!IF "CanTrcvGeneral/CanTrcvWakeUpSupport = 'CANTRCV_17_V9251_WAKEUP_BY_INTERRUPT'"!][!//
[!/* [cover parentID={1871FD41-4DEE-411d-BDF2-03B70942BB32}] [/cover] */!][!//
#define CANTRCV_17_V9251_GENERAL_WAKE_UP_SUPPORT  \
                                        (CANTRCV_17_V9251_WAKE_UP_BY_INTERRUPT)[!//

[!ENDIF!][!//
[!ENDINDENT!][!//
[!CR!][!//

/*
Configuration: CANTRCV_VERSION_INFO_API
- if STD_ON, Function CanTrcv_17_V9251_GetVersionInfo is available
- if STD_OFF,Function CanTrcv_17_V9251_GetVersionInfo is not available
*/
[!INDENT "0"!][!//
[!/* [cover parentID={0CDAF36C-ECAB-47cc-8D22-8724E3AC9B12}] [/cover] */!][!//
#define CANTRCV_17_V9251_GET_VERSION_INFO             ([!//
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
[!ENDINDENT!][!//
[!CR!][!//

/*
Configuration: CANTRCV_WAIT_COUNT expressed in nanoseconds.
- Range is 20us ... 255us
*/
[!INDENT "0"!][!//
[!VAR "CanTrcvWaitTime" = "CanTrcvGeneral/CanTrcvWaitTime/*[1]"!][!//
[!/* [cover parentID={E0819A65-DE78-4fe2-8F28-E41FE50E200F}] [/cover] */!][!//
#define CANTRCV_17_V9251_WAIT_COUNT                   ([!"num:i(($CanTrcvWaitTime) * num:i(1000000000))"!]U)
[!ENDINDENT!][!//
[!CR!][!//

/*
Configuration: Channel Identifier
*/
[!SELECT "node:ref($CanTrcvConfigSetName)"!][!//
  [!VAR "ChannelCount" = "0"!][!//
  [!LOOP "CanTrcvChannel/*"!][!//
    [!VAR "CanTrcvChUsed" = "./CanTrcvChannelUsed"!][!//
    [!IF "$CanTrcvChUsed = 'true'"!][!//
      [!VAR "CanTrcv_ChannelId" = "./CanTrcvChannelId"!]
      [!VAR "ChannelCount" = "$ChannelCount + 1"!][!//
      [!VAR "SymbolicName" = "node:name(.)"!][!//
      [!INDENT "0"!]
      /* Symbolic name for CanTrcvChannel_[!"$CanTrcv_ChannelId"!] */
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
      in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
      in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
      in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
      in generated code due to Autosar Naming constraints.*/
      [!/* [cover parentID={AD0876F4-37D8-44c3-8968-59114F5ADA78}] [/cover] */!][!//
      #ifndef CanTrcv_17_V9251Conf_CanTrcvChannel_[!"$SymbolicName"!]
      [!CR!][!//
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
      in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
      in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
      in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
      in generated code due to Autosar Naming constraints.*/
      #define CanTrcv_17_V9251Conf_CanTrcvChannel_[!"$SymbolicName"!]    ((uint8)[!"(num:i($CanTrcv_ChannelId))"!]U)
      #endif
      [!CR!][!//
        [!IF "./CanTrcvWakeupByBusUsed = 'true'"!][!//
        [!IF "node:refexists(./CanTrcvIcuChannelRef/*[1]) ='true'"!][!//
          /* Icu Channel reference to enable/disable the interrupts for wakeup */
          [!/* [cover parentID={ABF38E5E-2622-4b65-AA2F-B2EC93EB26A1}] [/cover] */!][!//
          #define CANTRCV_17_V9251_CH_[!"./CanTrcvChannelId"!]_ICU_REF        (IcuConf_IcuChannel_[!"node:name(node:ref(./CanTrcvIcuChannelRef/*[1]))"!])
        [!ELSE!][!//
          [!ERROR!][!//
            CanTrcv_17_V9251 Code Generator:In CanTransceiver Channel_[!"./CanTrcvChannelId "!],If CanTrcvWakeupByBusUsed parameter is enabled, then CanTrcvIcuChannelRef parameter must be configured.
          [!ENDERROR!][!//
        [!ENDIF!]
      [!ELSE!][!//
        /* Icu channel reference  not configured */
        #define CANTRCV_17_V9251_CH_[!"./CanTrcvChannelId"!]_ICU_REF        (ICU_REFERENCE_NOT_CONFIGURED)
      [!ENDIF!][!//
      [!CR!][!//
      /* CanTrcv Channel_[!"./CanTrcvChannelId"!] max baud rate supported */
      /* [cover parentID={B10A013A-6F8D-4c8f-BCC8-D9F079EDB143}] [/cover] */
      [!VAR "CanTrcvmaxChbaudrate" = "./CanTrcvMaxBaudrate"!][!//
      #define CANTRCV_17_V9251_CH_[!"./CanTrcvChannelId"!]_MAX_BAUDRATE_SUPPORT      ([!"($CanTrcvmaxChbaudrate)"!]U)
      [!CR!][!//
      [!ENDINDENT!]
    [!ENDIF!][!//
  [!ENDLOOP!][!//
  [!INDENT "0"!]
  /* Number of channels used */
  [!/* [cover parentID={3B3AFC1E-8190-41e8-9690-4E8175DD86AC}] [/cover] */!][!//
  #define CANTRCV_17_V9251_CHANNELS_USED              ((uint8)[!"num:i($ChannelCount)"!]U)
  [!VAR "ChannelCount1" = "0"!][!//
  [!LOOP "CanTrcvChannel/*"!][!//
    [!VAR "ChannelCount1" = "$ChannelCount1 + 1"!][!//
  [!ENDLOOP!][!//
  [!CR!][!//
  /* Number of channels configured in the CanTrcvChannel container */
  [!/* [cover parentID={CBEE7D56-A411-40e1-A61E-57A20B808EC9}] [/cover] */!][!//
  #define CANTRCV_17_V9251_CHANNELS_CFG               ((uint8)[!"num:i($ChannelCount1)"!]U)
  [!ENDINDENT!]
[!ENDSELECT!][!//

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/

/*******************************************************************************
**                               End of File                                  **
*******************************************************************************/
[!ENDSELECT!][!//
#endif /*END OF  CANTRCV_17_V9251_CFG_H */
