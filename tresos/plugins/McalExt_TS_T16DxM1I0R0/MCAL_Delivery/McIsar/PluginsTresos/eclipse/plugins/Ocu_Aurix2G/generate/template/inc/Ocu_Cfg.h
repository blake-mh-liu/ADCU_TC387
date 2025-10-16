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
**  FILENAME  : Ocu_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 8.0.0                                                         **
**                                                                            **
**  DATE      : 2021-03-02                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : NA                                                **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={6B32F4D1-FC77-43c7-8AE6-B644757CB762}]    **
**                                                                            **
**  DESCRIPTION  : Code template source file for Ocu Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) :Specification of Ocu Driver,AUTOSAR Release 4.2.2&4.4.0 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*****************************************************************************/!]
[!//
/*******************************************************************************
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
**  FILENAME  : Ocu_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 8.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]              !!!IGNORE-LINE!!!       **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                !!!IGNORE-LINE!!!         **
**                                                                            **
**                                                                            **
**  BSW MODULE DECRIPTION : NA                                                **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Ocu configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) :Specification of Ocu Driver,AUTOSAR Release 4.2.2&4.4.0 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef OCU_CFG_H
#define OCU_CFG_H

[!NOCODE!][!//
  [!INCLUDE "Ocu.m"!][!//
[!ENDNOCODE!][!//
[!INDENT "0"!]
  [!SELECT "as:modconf('Ocu')[1]"!][!// 
    
    /*******************************************************************************
    **                      Includes                                              **
    *******************************************************************************/
    /*******************************************************************************
    **                      Global Macro Definitions                              **
    *******************************************************************************/
    /*Section to Generate Autosar Specific Version Information*/
    [!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
    [!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
    [!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
    
    [!IF "$MajorVersion = num:i(4)"!][!//
      [!/*-- [cover parentID={40534EA4-A89D-4192-A878-8C5A99A56A2D}]  [/cover] --*/!][!//
      #define OCU_AR_RELEASE_MAJOR_VERSION  ([!"$MajorVersion"!]U)
      [!/*-- [cover parentID={66252555-C916-4576-B415-C506826A0483}]  [/cover] --*/!][!//
      #define OCU_AR_RELEASE_MINOR_VERSION  ([!"$MinorVersion"!]U)
      [!/*-- [cover parentID={A4782501-4265-40ae-B71A-CC145F2FBFB5}]  [/cover] --*/!][!//
      #define OCU_AR_RELEASE_REVISION_VERSION  ([!"$RevisionVersion"!]U)
    [!ENDIF!][!//
    
    /*Section to Generate Vendor Specific Version Information*/
    [!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
    [!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
    [!VAR "SwRevisionVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
    /* Vendor specific implementation version information */
    [!/*-- [cover parentID={6E2F396D-E475-436f-AEB3-B0C786C0D302}]  [/cover] --*/!][!//
    #define OCU_SW_MAJOR_VERSION   ([!"$SwMajorVersion"!]U)
    [!/*-- [cover parentID={B0B8D704-E5F5-4374-ACA1-D0E5FEC1C155}]  [/cover] --*/!][!//
    #define OCU_SW_MINOR_VERSION   ([!"$SwMinorVersion"!]U)
    [!/*-- [cover parentID={A4224078-135E-49e7-BFC7-5E09B47A0C03}]  [/cover] --*/!][!//
    #define OCU_SW_PATCH_VERSION   ([!"$SwRevisionVersion"!]U)
    
    /* General Configuration */
    /*
    Configuration: OCU_DEV_ERROR_DETECT
    Adds/removes the Development Error Detection 
    from the code 
    - if STD_ON, Development error detection is enabled
    - if STD_OFF, Development error detection is disabled
    */
    [!/*-- [cover parentID={1A32380B-8A4B-42da-A789-8AF1825BCFA8}]  [/cover] --*/!][!//
    #define OCU_DEV_ERROR_DETECT           [!CALL "OCU_CG_ConfigSwitch", "nodeval" = "OcuGeneral/OcuDevErrorDetect"!]
    /*
    Configuration: OCU_MULTICORE_ERROR_DETECT
    Adds/removes the Multicore Error Detection 
    from the code 
    - if STD_ON, Multicore error detection is enabled
    - if STD_OFF, Multicore error detection is disabled
    */
    [!/*-- [cover parentID={C97487BC-A1CE-4323-A30F-D5F55D4F5FF6}]  [/cover] --*/!][!//
    #define OCU_MULTICORE_ERROR_DETECT           [!CALL "OCU_CG_ConfigSwitch", "nodeval" = "OcuGeneral/OcuMultiCoreErrorDetect"!]
    
    /*
        Configuration : OCU_SAFETY_ENABLE
        Pre-processor switch to enable/disable the OCU driver safety features.
    */
    [!/*-- [cover parentID={02D08A58-0ECC-481e-81F8-5024BD61A29C}]  [/cover] --*/!][!//
    #define OCU_SAFETY_ENABLE [!CALL "OCU_CG_ConfigSwitch", "nodeval" = "OcuGeneral/OcuSafetyEnable"!]
    /*  [/cover] */
    
    /*
        Configuration : OCU_INITCHECK_API
        Pre-processor switch to enable/disable the OCU init check API.
    */
    [!/*-- [cover parentID={6B4E07B1-FFD8-4990-9988-DE4C29693F2A}]  [/cover] --*/!][!//
    #define OCU_INITCHECK_API [!CALL "OCU_CG_ConfigSwitch", "nodeval" = "OcuConfigurationOfOptionalApis/OcuInitCheckApi"!]
    /*  [/cover] */
    /*
    Configuration: OCU_DE_INIT_API
    Adds/removes Ocu_DeInit API 
    from the code 
    - if STD_ON, Ocu_DeInit is enabled
    - if STD_OFF, Ocu_DeInit is disabled
    */
    [!/*-- [cover parentID={2EA0DF86-C8D2-42b3-A8B7-252529B9D940}]  [/cover] --*/!][!//
    #define OCU_DE_INIT_API                [!CALL "OCU_CG_ConfigSwitch", "nodeval" = "OcuConfigurationOfOptionalApis/OcuDeInitApi"!]
    /*
    Configuration: OCU_SET_PIN_ACTION_API
    Adds/removes Set Pin Action API from the code 
    - if STD_ON, Ocu_SetPinAction is enabled
    - if STD_OFF, Ocu_SetPinAction is disabled
    */
    [!/*-- [cover parentID={13821C29-93B0-449b-9D30-CE789493C9B1}]  [/cover] --*/!][!//
    #define OCU_SET_PIN_ACTION_API             [!CALL "OCU_CG_ConfigSwitch", "nodeval" = "OcuConfigurationOfOptionalApis/OcuSetPinActionApi"!]
    /*
    Configuration: OCU_SET_PIN_STATE_API
    Adds/removes Set Pin State API from the code 
    - if STD_ON, Ocu_SetPinState is enabled
    - if STD_OFF, Ocu_SetPinState is disabled
    */
    [!/*-- [cover parentID={C60F03A9-0010-4561-AFDF-12B7DE14CDB3}]  [/cover] --*/!][!//
    #define OCU_SET_PIN_STATE_API  [!CALL "OCU_CG_ConfigSwitch", "nodeval" = "OcuConfigurationOfOptionalApis/OcuSetPinStateApi"!]
    /*
    Configuration: OCU_GET_COUNTER_API
    Adds/removes Get Counter API from the code 
    - if STD_ON, Ocu_GetCounter is enabled
    - if STD_OFF, Ocu_GetCounter is disabled
    */
    [!/*-- [cover parentID={DF89F340-9AE7-495e-82FE-EF9057C95F3B}]  [/cover] --*/!][!//
    #define OCU_GET_COUNTER_API        [!CALL "OCU_CG_ConfigSwitch", "nodeval" = "OcuConfigurationOfOptionalApis/OcuGetCounterApi"!]
    /*
    Configuration: OCU_SET_ABSOLUTE_THRESHOLD_API
    Adds/removes Set Absolute Threshold API from the code 
    - if STD_ON, Ocu_SetAbsoluteThreshold is enabled
    - if STD_OFF, Ocu_SetAbsoluteThreshold is disabled
    */
    [!/*-- [cover parentID={039E74E8-2078-4c9e-9005-0AE3579A4304}]  [/cover] --*/!][!//
    #define OCU_SET_ABSOLUTE_THRESHOLD_API       [!CALL "OCU_CG_ConfigSwitch", "nodeval" = "OcuConfigurationOfOptionalApis/OcuSetAbsoluteThresholdApi"!]
    /*
    Configuration: OCU_SET_RELATIVE_THRESHOLD_API
    Adds/removes Set Relative Threshold API from the code 
    - if STD_ON, Ocu_SetRelativeThreshold is enabled
    - if STD_OFF, Ocu_SetRelativeThreshold is disabled
    */
    [!/*-- [cover parentID={F2402AE6-B175-467e-968B-7D6586EB63AB}]  [/cover] --*/!][!//
    #define OCU_SET_RELATIVE_THRESHOLD_API       [!CALL "OCU_CG_ConfigSwitch", "nodeval" = "OcuConfigurationOfOptionalApis/OcuSetRelativeThresholdApi"!]
    /*
    Configuration: OCU_VERSION_INFO_API
    Adds/removes Get Version Info API from the code 
    - if STD_ON, Ocu_GetVersionInfo is enabled
    - if STD_OFF, Ocu_GetVersionInfo is disabled
    */
    [!/*-- [cover parentID={312D023F-5039-48a5-9A95-AC55ACF39F8D}]  [/cover] --*/!][!//
    #define OCU_VERSION_INFO_API       [!CALL "OCU_CG_ConfigSwitch", "nodeval" = "OcuConfigurationOfOptionalApis/OcuVersionInfoApi"!]
    /*
    Configuration: OCU_NOTIFICATION_SUPPORTED
    Adds/removes Enable Notification and Disable Notification APIs from the code 
    - if STD_ON, Ocu_EnableNotification and Ocu_DisableNotification are enabled
    - if STD_OFF, Ocu_EnableNotification and Ocu_DisableNotification are disabled
    */
    [!/*-- [cover parentID={33F06DEB-178E-4b94-8C92-879BA5C7358B}]  [/cover] --*/!][!//
    #define OCU_NOTIFICATION_SUPPORTED               [!CALL "OCU_CG_ConfigSwitch", "nodeval" = "OcuConfigurationOfOptionalApis/OcuNotificationSupported"!]
    [!VAR "SingelCore"= "num:i(0)"!][!//
    [!VAR "SingelCoreID"= "num:i(0)"!][!//
    [!SELECT "as:modconf('Ocu')[1]"!][!//
      [!NOCODE!]
        [!CALL "OCU_CG_GenerateModuleMap"!][!//
      [!ENDNOCODE!]
      [!VAR "MaxChannels"= "num:i(count(./OcuConfigSet/OcuChannel/*))"!][!//
      [!FOR "CoreId" = "num:i(1)" TO "num:i(6)"!][!//
        /*
          Core [!"num:i($CoreId - 1)"!] Configurations    
        */
        [!VAR "MaxChannelsCorex"= "num:i(0)"!][!//
        [!FOR "ChannelId" = "num:i(1)" TO "num:i($MaxChannels)"!][!//
          [!SELECT "./OcuConfigSet/OcuChannel/*[OcuChannelId = num:i($ChannelId) - num:i(1)]"!][!//
            [!NOCODE!][!//
              [!CALL "OCU_CG_GetCore", "Channel" = "node:name(node:current())"!][!//
            [!ENDNOCODE!][!//
            [!IF "(num:i($CGCoreId_Extract)) = (num:i($CoreId) - num:i(1))"!][!//
              [!VAR "MaxChannelsCorex"= "num:i($MaxChannelsCorex + 1)"!][!//
              [!/*-- [cover parentID={C701037E-3C15-4b54-AD7F-C4CB7D74463F}]  [/cover] --*/!][!//
              /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
                 in generated code due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
                 in generated code due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
                 in generated code due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_5_JUSTIFICATION: decomposition of name is not possible,
              Further distinct name can not be given*/
              #ifndef OcuConf_OcuChannel_[!"node:name(.)"!]
              /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
                 in generated code due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
                 in generated code due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
                 in generated code due to Autosar Naming constraints.*/
              /* MISRA2012_RULE_5_5_JUSTIFICATION: decomposition of name is not possible,
              Further distinct name can not be given*/
              #define OcuConf_OcuChannel_[!"node:name(.)"!]       ((Ocu_ChannelType)[!"./OcuChannelId"!]U)
              #endif
            [!ENDIF!][!//
          [!ENDSELECT!][!//
        [!ENDFOR!][!//channel
        /* Core [!"num:i($CoreId - 1)"!] Configurations summary */
        /* [cover parentID={C178A546-E7FB-4f7c-B406-585E5E43ECCC}] 
           [/cover] */
        #define OCU_MAX_CHANNELS_CORE[!"num:i($CoreId - 1)"!]                   ([!"num:i($MaxChannelsCorex)"!]U)
        /*  [/cover] */
        [!IF "$MaxChannelsCorex = $MaxChannels"!]
          [!VAR "SingelCore"= "num:i(1)"!][!//
          [!VAR "SingelCoreID"= "num:i($CoreId - 1)"!][!//
        [!ENDIF!]
      [!ENDFOR!][!//Core
    [!ENDSELECT!][!//
    
    /***************************************************************************
    TOTAL NUMBER OF CONFIGURED CHANNELS 
    ****************************************************************************/
    [!/*-- [cover parentID={C701037E-3C15-4b54-AD7F-C4CB7D74463F}]  [/cover] --*/!][!//
    #define OCU_MAX_CHANNELS         ([!"num:i($MaxChannels)"!]U)
    
    /* Macro to idntify single core execution */
    #define  OCU_SINGLE_CORE    [!CALL "OCU_CG_ConfigSwitchInt", "nodeval" = "num:i($SingelCore)"!]
    #define  OCU_SINGLE_CORE_ID [!"num:i($SingelCoreID)"!]

  [!ENDSELECT!][!//
[!ENDINDENT!]
#endif  /* OCU_CFG_H */


