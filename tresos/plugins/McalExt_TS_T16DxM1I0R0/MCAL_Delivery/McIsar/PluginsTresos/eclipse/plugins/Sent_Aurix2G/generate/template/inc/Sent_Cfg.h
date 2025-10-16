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
**  FILENAME  : Sent_Cfg.h                                                    **
**                                                                            **
**  VERSION   : 7.0.0                                                         **
**                                                                            **
**  DATE      : 2020-06-17                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Sent.bmd                                          **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID= ]                                         **
**                                                                            **
**  DESCRIPTION  : Code template header file for Sent Driver                  **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Sent Driver, AUTOSAR Release 4.2.2    **
**                                               and AUTOSAR Release 4.4.0    **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*****************************************************************************/!]
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
**  FILENAME  : Sent_Cfg.h                                                    **
**                                                                            **
**  VERSION   : 7.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]   !!!IGNORE-LINE!!!                  **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]       !!!IGNORE-LINE!!!                  **
**                                                                            **
**  BSW MODULE DECRIPTION : Sent.bmd                                          **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Sent configuration generated out of ECUC file              **
**                                                                            **
**  SPECIFICATION(S) : Specification of Sent Driver, AUTOSAR Release 4.2.2    **
**                                               and AUTOSAR Release 4.4.0    **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef SENT_CFG_H
#define SENT_CFG_H

#include "Sent_Types.h"

[!//
[!//
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!AUTOSPACING!][!//
[!INDENT "0"!][!//
  [!SELECT "as:modconf('Sent')[1]"!][!//
    [!//
    [!NOCODE!][!//
      [!INCLUDE "..\Sent.m"!][!//
    [!ENDNOCODE!][!//
    [!//
    [!NOCODE!][!//
      [!VAR "AsMajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
      [!VAR "AsMinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
      [!VAR "AsRevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
    [!ENDNOCODE!][!//
      /* AUTOSAR specification version numbers */
      #define SENT_AR_RELEASE_MAJOR_VERSION     ([!"$AsMajorVersion"!]U)
      #define SENT_AR_RELEASE_MINOR_VERSION     ([!"$AsMinorVersion"!]U)
      #define SENT_AR_RELEASE_REVISION_VERSION  ([!"$AsRevisionVersion"!]U)
    [!NOCODE!][!//
      [!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
      [!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
      [!VAR "SwPatchVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
    [!ENDNOCODE!]
    /* Vendor specific implementation version information */
    #define SENT_SW_MAJOR_VERSION              ([!"$SwMajorVersion"!]U)
    #define SENT_SW_MINOR_VERSION              ([!"$SwMinorVersion"!]U)
    #define SENT_SW_PATCH_VERSION              ([!"$SwPatchVersion"!]U)
    /* SENT_MCAL_SUPERVISOR  */
    /* Sent Operation in Supervisory Mode  */
    #define SENT_MCAL_SUPERVISOR             (0U)

    /* SENT_MCAL_USER1  */
    /* Sent Operation in User 1 Mode  */
    #define SENT_MCAL_USER1                  (1U)
    /*******************************************************************************
    **                      Includes                                              **
    *******************************************************************************/
    /*******************************************************************************
    **                      Global Macro Definitions                              **
    *******************************************************************************/
    /*
                         Container : SentGeneralConfiguration
    */
    /*
      The following macros will enable or disable a particular feature
      in SENT module.
      Set the macro to ON to enable the feature and OFF to disable the same.
    */
    /*
    Configuration: SENT_DEV_ERROR_DETECT
    Preprocessor switch for enabling the development error detection and
    reporting.
    - if STD_ON, DET is Enabled
    - if STD_OFF,DET is Disabled
    */
    #define SENT_DEV_ERROR_DETECT  [!//
    [!CALL "CG_ConfigSwitch","MacInputVal" = "SentGeneral/SentDevErrorDetect"!][!//

    /* Configuration: SENT_DEINIT_API
    Sent_DeInit API configuration
    - if STD_ON, DeInit API is Enabled
    - if STD_OFF, DeInit API is Disabled
    */
    #define SENT_DEINIT_API        [!//
    [!CALL "CG_ConfigSwitch","MacInputVal" = "SentGeneral/SentDeInitApi"!][!//

    /* Configuration: SENT_VERSION_INFO_API
    Version Information API configuration
    - if STD_ON, VersionInfo API is Enabled
    - if STD_OFF, VersionInfo API is Disabled
    */
    #define SENT_VERSION_INFO_API  [!//
    [!CALL "CG_ConfigSwitch","MacInputVal" = "SentGeneral/SentVersionInfoApi"!][!//

    /* Configuration: SENT_SPC_USED
    SENT SPC Feature configuration
    - if STD_ON, SPC feature is Enabled
    - if STD_OFF, SPC feature is Disabled
    */
    #define SENT_SPC_USED         [!//
    [!CALL "CG_ConfigSwitch","MacInputVal" = "SentGeneral/SentSpcFeatureSupport"!][!//

    /* Configuration: SENT_RESET_SFR_AT_INIT
    SENT Enable/Disable Reset of SFR's during Init
    - if STD_ON, Enables Reset of SFR's during Init
    - if STD_OFF, Disables Reset of SFR's during Init
    */
    #define SENT_RESET_SFR_AT_INIT [!//
    [!CALL "CG_ConfigSwitch","MacInputVal" = "SentGeneral/SentResetSfrAtInit"!]

    /* Multicore Enabled or not */
    #define SENT_MULTICORE_ERROR_DETECT [!//
    [!CALL "CG_ConfigSwitch","MacInputVal" = "SentGeneral/SentMultiCoreErrorDetect"!]

    /* Configuration: SENT_HW_MAX_CHANNELS
    Maximum number of SENT physical channels supported
    */
    #define SENT_HW_MAX_CHANNELS   ([!"ecu:get('Sent.MaxChannelsSupported')"!]U)

    /* Configuration: SENT MODULE INSTANCE ID */
    #define SENT_INSTANCE_ID       ((uint8)[!"SentGeneral/SentIndex"!])

    /* Total no. of config sets */
    #define SENT_CONFIG_COUNT    ([!"num:i(count(SentConfigSet/*))"!]U)
    /*
    Configuration: SENT_INIT_DEINIT_API_MODE:
    -User Mode Macro for init deinit APIs
    */
    [!IF "SentGeneral/SentInitDeInitApiMode = 'SENT_MCAL_SUPERVISOR'"!][!//
      #define SENT_INIT_DEINIT_API_MODE      (SENT_MCAL_SUPERVISOR)
    [!ELSE!][!//
      #define SENT_INIT_DEINIT_API_MODE      (SENT_MCAL_USER1)
    [!ENDIF!][!//
    [!CR!][!//
    /* Configured SENT Channels Symbolic Names */
    [!LOOP "SentConfigSet/SentChannelConfigSet/*"!][!//
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      #ifndef Sent_Conf_Channel_[!"node:name(.)"!]
        /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
          in generated code due to Autosar Naming constraints.*/
        /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
          in generated code due to Autosar Naming constraints.*/
        /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
          in generated code due to Autosar Naming constraints.*/
        /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
          in generated code due to Autosar Naming constraints.*/
      [!INDENT "2"!][!//
        #define Sent_Conf_Channel_[!"node:name(.)"!]     ((Sent_ChannelCfgType)[!"SentChLogiIndex"!])
      [!ENDINDENT!][!//
      #endif
    [!ENDLOOP!][!//
    /*******************************************************************************
    **                      Global Macro Definitions                              **
    *******************************************************************************/
    [!LOOP "SentChannelConfigSet/SentChannel/*"!][!//
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      #ifndef SentChannelConfigSet_[!"node:name(.)"!]
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      [!INDENT "2"!][!//
        #define SentChannelConfigSet_[!"node:name(.)"!]     ((Sent_ChannelType)[!"SentChLogiIndex"!])
      [!ENDINDENT!][!//
       #endif
    [!ENDLOOP!][!//
    /*******************************************************************************
    **                                Sent Driver Usage                           **
    *******************************************************************************/
    [!NOCODE!][!//
      [!/* Collect core-channel mappings from Resource Manager. */!]
      [!CALL "Sent_GenerateModuleMap", "Module"="'SENT'"!][!//
      [!CALL "Sent_GetMasterCoreID"!][!//
      [!SELECT "as:modconf('Sent')[1]/SentConfigSet/SentChannelConfigSet/*"!]
        [!/* Append the missing resources to master core */!]
        [!CALL "Sent_ValidateChAllocation", "Item" = "node:name(node:current())"!][!//
        [!IF "$CGResult = 'FALSE'"!]
          [!VAR "CGModuleMap" = "concat($CGModuleMap, 'CORE', $CGMasterCoreId, '_', node:name(node:current()), '#,')"!][!//
          [!VAR "pattern" = "concat('CORE', $CGMasterCoreId)"!]
          [!IF "not(contains(text:split($CGCoreUsed),$pattern))"!]
            [!VAR "CGCoreUsed" = "concat($CGCoreUsed, $pattern, ',')"!][!//
          [!ENDIF!]
        [!ENDIF!]
      [!ENDSELECT!]
      [!/* If no resource is allocated to master core, add master core to CGCoreUsed as dummy core */!]
      [!VAR "pattern" = "concat('CORE', $CGMasterCoreId)"!]
      [!IF "not(contains(text:split($CGCoreUsed),$pattern))"!]
        [!VAR "CGCoreUsed" = "concat($CGCoreUsed, $pattern, ',')"!][!//
      [!ENDIF!]
      [!VAR "MaxCoreConfigured" = "num:i(count(text:split($CGCoreUsed, ',')))"!]
    [!ENDNOCODE!][!//
    [!CR!]
    /* Configuration: ResourceM
    The configuration contains allocation of Sent channels across cores.
    - if STD_ON, atleast one sent channel is configured in the core.
    - if STD_OFF, no sent channels are configured in the core. */
    [!NOCODE!][!//
      [!FOR "CoreIndex" = "num:i(1)" TO "num:i(6)"!][!//
        [!VAR "corePattern" = "concat( 'CORE', num:i($CoreIndex - 1) )"!]
        [!VAR "matchCore" = "concat( '^.*(', $corePattern, ').*$' )"!]
        [!IF "text:match($CGCoreUsed, $matchCore)"!] [!// Fetch all strings matching the core.
          [!CODE!]
            #define SENT_CONFIGURED_CORE[!"num:i($CoreIndex - 1)"!]                              (STD_ON)
          [!ENDCODE!]
        [!ELSE!]
          [!CODE!]
            #define SENT_CONFIGURED_CORE[!"num:i($CoreIndex - 1)"!]                              (STD_OFF)
          [!ENDCODE!]
        [!ENDIF!]
      [!ENDFOR!]
    [!ENDNOCODE!]
    [!CR!]
    /*
       Configuration:Max channels configured for Sent, max channels are same across
       variants.
    */
    [!NOCODE!][!//
      [!SELECT "SentConfigSet/*"!][!//
        [!VAR "MaxChannels"= "num:i(count(SentChannelConfigSet/*))"!][!//
      [!ENDSELECT!][!//
    [!ENDNOCODE!][!//

    /* [cover parentID={995E2C8C-C822-4607-A21E-DFBF8C0BF9EC}]
    Sent Max Channels macro
    [/cover] */
    #define SENT_MAX_CHANNELS_CONFIGURED         ((Sent_ChannelType)[!"$MaxChannels"!])
    /* Number of Cores confgiured for Sent */
    [!VAR "MaxChannelsCore" = "num:i(255)"!][!//
    [!FOR "CoreId" = "num:i(0)" TO "$MaxCoreConfigured - num:i(1)"!][!//
      [!VAR "TempCoreId" = "concat('CORE',$CoreId)"!][!//
      [!IF "(text:contains( text:split($CGAllocatedCores,','), $TempCoreId)) or ($CGMasterCoreId = $TempCoreId) or ($CoreId < ecu:get('Mcu.NoOfCoreAvailable'))"!][!//
        [!VAR "MaxChannelsCore" = "num:i(0)"!][!//
        [!VAR "Module" = "'SENT'"!][!//
        [!SELECT "SentChannelConfigSet/*[SentChLogiIndex= num:i($ChannelId)]"!][!//
          [!VAR "NodeName" = "node:name(.)"!][!//
          [!CALL "Sent_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
            [!IF "$CGAllocationResult = 'TRUE'"!][!//
          [!VAR "MaxChannelsCore" = "$MaxChannelsCore + num:i(1)"!][!//
          [!ENDIF!]
        [!ENDSELECT!]
      [!ENDIF!]
    [!ENDFOR!]
    [!CALL "Sent_PrintMasterCoreID"!][!//
    [!CALL "Sent_CGCalculateTotalChannelPerCore"!][!//
    [!CALL "Sent_CGCalculateChannelMasterCore"!][!//
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
    [!VAR "TotalConfig" = "num:i(count(SentConfigSet/*))"!][!//
    [!FOR "SentId" ="num:i(1)" TO "(num:i($TotalConfig))"!][!//
      [!SELECT "SentConfigSet/*[num:i($SentId)]"!][!//
        [!NOCODE!][!//
          [!VAR "MaxSentChannels" = "num:i(0)"!][!//
          [!VAR "MaxSentChannels" = "num:i(count(SentChannelConfigSet/*))"!][!//
        [!ENDNOCODE!][!//
        extern const Sent_NotifFnPtrType SentNotifFnPtrArray[[!"num:i($MaxSentChannels)"!]];
        /* ConfigSet [!"num:i($SentId - 1)"!] */
        [!FOR "Channel" = "0" TO "num:i($MaxSentChannels)"!][!//
          [!SELECT "SentChannelConfigSet/*[num:i($Channel)]"!][!//
            [!VAR "SentCallOutFn" = "./SentChanCalloutFn"!][!//
            [!IF "string-length($SentCallOutFn) = 0"!][!//
              [!VAR "SentCallOutFn" = "'NULL_PTR'"!][!//
            [!ENDIF!][!//
            [!IF "num:isnumber($SentCallOutFn) = 'true'"!][!//
            [!ELSEIF "$SentCallOutFn != 'NULL_PTR' "!][!//
              /* Application Callback function for SENT Channel[!"SentChLogiIndex"!] */
              extern void [!"$SentCallOutFn"!] (Sent_ChannelIdxType ChannelId,
                                                        Sent_NotifType Stat);
            [!ENDIF!]
          [!ENDSELECT!][!//
        [!ENDFOR!][!//
      [!ENDSELECT!][!//
    [!ENDFOR!][!//

    /*******************************************************************************
    **                      Global Inline Function Definitions                    **
    *******************************************************************************/
  [!ENDSELECT!][!//
[!ENDINDENT!][!//
#endif  /* SENT_CFG_H */

