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
**  FILENAME  : Fr_17_Eray_Cfg.h                                              **
**                                                                            **
**  VERSION   : 13.0.0                                                        **
**                                                                            **
**  DATE      : 2023-05-19                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Fr_17_Eray.bmd                                    **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={F722E884-0C77-4526-8867-1BC8F5DE083D}]    **
**                                                                            **
**  DESCRIPTION  : Code template header file for Fr Driver                    **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of FlexRay Driver, AUTOSAR Release 4.2.2 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*****************************************************************************/!]
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
**  FILENAME  : Fr_17_Eray_Cfg.h                                              **
**                                                                            **
**  VERSION   : 13.0.0                                                        **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]             !!!IGNORE-LINE!!!        **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]               !!!IGNORE-LINE!!!          **
**                                                                            **
**  BSW MODULE DECRIPTION : Fr_17_Eray.bmd                                    **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Fr configuration generated out of ECUC file                **
**                                                                            **
**  SPECIFICATION(S) : Specification of FlexRay Driver, AUTOSAR Release 4.2.2 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/******************************************************************************/
#ifndef  FR_17_ERAY_CFG_H
#define  FR_17_ERAY_CFG_H

[!NOCODE!]
  [!INCLUDE "Fr_17_Eray.m"!][!//
[!ENDNOCODE!]
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
[!/************************Verification of fSCLK *************************/!][!//
[!INDENT "0"!][!//
  [!NOCODE!][!//
    [!/*
    [cover parentID={A6B4677A-D15D-4223-969B-8023F0D83472}] Code Generation dependency on other modules [/cover]
    */!][!//
    [!IF "not(node:exists(as:modconf('Mcu')[1]))"!]
      [!ERROR!][!//
        FR Code Generator: Mcu module is not added to the project.
      [!ENDERROR!][!//
    [!ENDIF!]

    [!IF "not(node:exists(as:modconf('FrIf')[1]))"!]
      [!ERROR!][!//
        FR Code Generator: FrIf module is not added to the project.
      [!ENDERROR!][!//
    [!ENDIF!]

    [!SELECT "as:modconf('Mcu')[1]"!][!//
      [!LOOP "McuModuleConfiguration/McuClockSettingConfig/*"!][!//
        [!IF "McuClockReferencePointConfig/McuPllDistributionSettingConfig/McuErayClkEnable = 'false'"!][!//
          [!ERROR!][!//
            Config Error : Enable Mcu_Eray Clock in McuModuleConfiguration_[!"@index"!]
          [!ENDERROR!][!//
        [!ENDIF!][!//
        [!VAR "ErayFrequency" = "num:i(McuClockReferencePointConfig/McuPllDistributionSettingConfig/McuErayFrequency)"!][!//
        [!IF "$ErayFrequency != 80000000"!][!//
          [!ERROR!][!//
            Config Error :Invalid Mcu_Eray frequency in McuModuleConfiguration_[!"@index"!].Supported frequency: 80MHz
          [!ENDERROR!][!//
        [!ENDIF!][!//
        [!VAR "SPBFrequency" = "num:i(McuClockReferencePointConfig/McuPllDistributionSettingConfig/McuSPBFrequency)"!][!//
      [!ENDLOOP!][!//
    [!ENDSELECT!][!//
  [!ENDNOCODE!][!//
  [!//
  [!/* Select MODULE-CONFIGURATION as context-node */!][!//
  [!VAR "ModuleName" = "'Fr'"!][!//
  [!SELECT "as:modconf($ModuleName)[1]"!][!//
    [!//
    /* Fr Instance ID */
    [!/*
    [cover parentID={3BC99ABE-B95D-426a-A50F-2CB3046C5F03}] FR_17_ERAY_INSTANCE_ID [/cover]
    */!][!//
    #define FR_17_ERAY_INSTANCE_ID                ((uint8)[!"num:i(FrGeneral/FrIndex)"!])

    [!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
    [!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
    [!VAR "PatchVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
    /* Autosar specification version */
    [!/*
    [cover parentID={222D2C9D-B00D-4b37-8241-1B77666A29E0}] FR_17_ERAY_AR_RELEASE_MAJOR_VERSION [/cover]
    */!][!//
    #define FR_17_ERAY_AR_RELEASE_MAJOR_VERSION           ([!"$MajorVersion"!]U)
    [!/*
    [cover parentID={F6B7109F-442C-405e-946B-14CF790F4B60}] FR_17_ERAY_AR_RELEASE_MINOR_VERSION [/cover]
    */!][!//
    #define FR_17_ERAY_AR_RELEASE_MINOR_VERSION           ([!"$MinorVersion"!]U)
    [!/*
    [cover parentID={7C99F736-7827-4d5b-9560-F0D1ED62AE32}] FR_17_ERAY_AR_RELEASE_REVISION_VERSION [/cover]
    */!][!//
    #define FR_17_ERAY_AR_RELEASE_REVISION_VERSION        ([!"$PatchVersion"!]U)
    [!//
    [!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
    [!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
    [!VAR "SwPatchVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//

    /* Vendor specific implementation version information */
    [!/*
    [cover parentID={C77EADC6-8134-4c2a-A75E-E2761A1B72DA}] FR_17_ERAY_SW_MAJOR_VERSION [/cover]
    */!][!//
    #define FR_17_ERAY_SW_MAJOR_VERSION           ([!"$SwMajorVersion"!]U)
    [!/*
    [cover parentID={12CA3F8D-EBEF-421d-B265-621C0B94FBBE}] FR_17_ERAY_SW_MINOR_VERSION [/cover]
    */!][!//
    #define FR_17_ERAY_SW_MINOR_VERSION           ([!"$SwMinorVersion"!]U)
    [!/*
    [cover parentID={A2BF8597-4BD7-4a74-ADAC-E5875F30EAB8}] FR_17_ERAY_SW_PATCH_VERSION [/cover]
    */!][!//
    #define FR_17_ERAY_SW_PATCH_VERSION           ([!"$SwPatchVersion"!]U)

    /* FR module Operation in Supervisory Mode  */
    #define FR_17_ERAY_MCAL_SUPERVISOR            (0U)

    /* FR module Operation in User 1 Mode  */
    #define FR_17_ERAY_MCAL_USER1                 (1U)

    #define FR_17_ERAY_LPDU_RECONFIGURABLE        (STD_ON)
    #define FR_17_ERAY_LPDU_NOT_RECONFIGURABLE    (STD_OFF)

    /*
    Container : FrDriverConfiguration - ECUC_Fr_00392:
    General configuration (parameters) of the FlexRay Driver module.
    */

    /*
    Configuration: FR_17_ERAY_PREPARE_LPDU
    Adds/removes the service Fr_17_Eray_PrepapreLPdu() from the code
    - if STD_ON, Fr_17_Eray_PrepapreLPdu() can be used
    - if STD_OFF, Fr_17_Eray_PrepapreLPdu() can not be used
    */
    [!/*
    [cover parentID={A2070D10-B988-4ea8-8FC0-BC9AFDD7317E}] FR_17_ERAY_PREPARE_LPDU [/cover]
    */!][!//
    #define FR_17_ERAY_PREPARE_LPDU                    [!CALL "Fr_17_Eray_CG_ConfigSwitch", "nodeval" = "FrGeneral/FrPrepareLPduSupport"!][!//

    /*
    Configuration: FR_17_ERAY_RECONFIG_LPDU
    Adds/removes the service Fr_17_Eray_ReconfigLPdu() from the code
    - if STD_ON, Fr_17_Eray_ReconfigLPdu() can be used
    - if STD_OFF, Fr_17_Eray_ReconfigLPdu() can not be used
    */
    [!/*
    [cover parentID={754B87F5-0063-4cc3-9091-8F2F9363FDCD}] FR_17_ERAY_RECONFIG_LPDU [/cover]
    */!][!//
    #define FR_17_ERAY_RECONFIG_LPDU                   [!CALL "Fr_17_Eray_CG_ConfigSwitch", "nodeval" = "FrGeneral/FrReconfigLPduSupport"!][!//

    /*
    Configuration: FR_17_ERAY_DISABLE_LPDU
    Adds/removes the service Fr_17_Eray_DisableLPdu() from the code
    - if STD_ON, Fr_17_Eray_DisableLPdu() can be used
    - if STD_OFF, Fr_17_Eray_DisableLPdu() can not be used
    */
    [!/*
    [cover parentID={E7C0CCDA-592C-4315-A146-50037DE564A5}] FR_17_ERAY_DISABLE_LPDU [/cover]
    */!][!//
    #define FR_17_ERAY_DISABLE_LPDU                    [!CALL "Fr_17_Eray_CG_ConfigSwitch", "nodeval" = "FrGeneral/FrDisableLPduSupport"!][!//

    /*
    Configuration: FR_17_ERAY_CTRL_TEST_COUNT
    Specifies the maximum number of iterations the FlexRay controller hardware test
    is performed during controller initialization.
    */
    [!/*
    [cover parentID={F6355EA0-784A-4869-8537-8E101E087C19}] FR_17_ERAY_CTRL_TEST_COUNT [/cover]
    */!][!//
    #define FR_17_ERAY_CTRL_TEST_COUNT                   ([!"FrGeneral/FrCtrlTestCount"!]U)

    /*
    Configuration: FR_17_ERAY_DEV_ERROR_DETECT
    Preprocessor switch to enable/disable the development error detection and
    reporting.
    - if STD_ON, Enable development error detection
    - if STD_OFF, Disable development error detection
    */
    [!/*
    [cover parentID={1920F68C-DD31-46d6-9F50-BB64C1A266C7}] FR_17_ERAY_DEV_ERROR_DETECT [/cover]
    */!][!//
    #define FR_17_ERAY_DEV_ERROR_DETECT                  [!CALL "Fr_17_Eray_CG_ConfigSwitch", "nodeval" = "FrGeneral/FrDevErrorDetect"!][!//

    /*Configuration: FR_17_ERAY_INDEX
    Specifies the InstanceId of this module instance.*/
    [!/*
    [cover parentID={F1937A96-C6C1-4d7e-AC79-83B9E98553C3}] FR_17_ERAY_INDEX [/cover]
    */!][!//
    #define FR_17_ERAY_INDEX             ([!"FrGeneral/FrIndex"!]U)

    /*
    Configuration: FR_17_ERAY_NUM_CTRL_SUPPORTED
    Determines the maximum number of communication controllers that the driver
    supports.
    */
    [!/*
    [cover parentID={166AF738-3733-4cd4-9020-BF6168E65CC4}] FR_17_ERAY_NUM_CTRL_SUPPORTED [/cover]
    */!][!//
    #define FR_17_ERAY_NUM_CTRL_SUPPORTED               ([!"FrGeneral/FrNumCtrlSupported"!]U)

    /*
    Configuration: FR_17_ERAY_RX_STRINGENT_CHECK
    If stringent check is enabled (true), received frames are only accepted if no
    slot status error occured.
    */
    [!/*
    [cover parentID={CF3F0BB0-D4DD-4c65-9D38-92826243E229}] FR_17_ERAY_RX_STRINGENT_CHECK [/cover]
    */!][!//
    #define FR_17_ERAY_RX_STRINGENT_CHECK                [!CALL "Fr_17_Eray_CG_ConfigSwitch", "nodeval" = "FrGeneral/FrRxStringentCheck"!]

    /*
    Configuration: FR_17_ERAY_RX_STRINGENT_LENGTH_CHECK
    If stringent check is enabled (true), received frames are only accepted the
    received payload length matches the configured payload length.
    */
    [!/*
    [cover parentID={D73FD46A-EF03-4f33-9CB0-A5794F538689}] FR_17_ERAY_RX_STRINGENT_LENGTH_CHECK [/cover]
    */!][!//
    #define FR_17_ERAY_RX_STRINGENT_LENGTH_CHECK         [!CALL "Fr_17_Eray_CG_ConfigSwitch", "nodeval" = "FrGeneral/FrRxStringentLengthCheck"!]

    /*
    Configuration: FR_17_ERAY_VERSION_INFO_API
    Adds/removes the service Fr_17_Eray_GetVersionInfo() from the code
    - if STD_ON, Fr_17_Eray_GetVersionInfo() can be used
    - if STD_OFF, Fr_17_Eray_GetVersionInfo() can not be used
    */
    [!/*
    [cover parentID={CE80629C-25E9-4da1-AEE5-9E46B2D72834}] FR_17_ERAY_VERSION_INFO_API [/cover]
    */!][!//
    #define FR_17_ERAY_VERSION_INFO_API                  [!CALL "Fr_17_Eray_CG_ConfigSwitch", "nodeval" = "FrGeneral/FrVersionInfoApi"!][!//

    /*
    Configuration: FR_17_ERAY_NMVECTOR_ENABLE
    Adds/removes the service Fr_17_Eray_GetNmVector() from the code
    - if STD_ON, Fr_17_Eray_GetNmVector() can be used
    - if STD_OFF, Fr_17_Eray_GetNmVector() can not be used
    */
    [!/*
    [cover parentID={46D29197-80FF-47bd-9D2A-EF2897B1C18C}] FR_17_ERAY_NMVECTOR_ENABLE [/cover]
    */!][!//
    #define FR_17_ERAY_NMVECTOR_ENABLE                   [!CALL "Fr_17_Eray_CG_ConfigSwitch", "nodeval" = "FrGeneral/FrNmVectorEnable"!][!//

    /*
    Configuration: FR_17_ERAY_TIMEOUT_DURATION
    Specifies the maximum time in nanoseconds for blocking function until
    a timeout is raised in short term wait loops.
    */
    [!/*
    [cover parentID={567DF5C3-2558-43a9-B1DF-E39B2DBC7EAE}] FR_17_ERAY_TIMEOUT_DURATION [/cover]
    */!][!//
    #define FR_17_ERAY_TIMEOUT_DURATION                  ([!"FrGeneral/FrTimeoutDurationFactor"!]U)

    /*
    Configuration: FR_INIT_API_MODE
    Specifies the operating modes for FlexRay initialization - SUPERVISOR/ USER1
    */
    [!/*
    [cover parentID={9B26E6CF-BEC1-4b99-818E-CD3CFE6A7AA5}] FR_17_ERAY_INIT_API_MODE [/cover]
    */!][!//
    [!IF "FrGeneral/FrInitApiMode = 'FR_MCAL_SUPERVISOR'"!][!//
      #define FR_17_ERAY_INIT_API_MODE                  (FR_17_ERAY_MCAL_SUPERVISOR)
    [!ELSE!][!//
      #define FR_17_ERAY_INIT_API_MODE                  (FR_17_ERAY_MCAL_USER1)
    [!ENDIF!][!//

    /*
    Configuration: FR_17_ERAY_TX_CONFLICT_DETECTION
    If transmit conflict detection is enabled (true), the Fr_CheckTxLPduStatus API
    detects the occurrence of a transmission conflict.
    */
    [!/* [cover parentID={1B4274FE-0B85-40ca-AFC0-52A7F845D8D1}] [/cover] */!][!//
    #define FR_17_ERAY_TX_CONFLICT_DETECTION             [!CALL "Fr_17_Eray_CG_ConfigSwitch","nodeval" = "FrGeneral/FrTxConflictDetection"!][!//

    /* Production Error reporting disabled macro */
    #define FR_17_ERAY_DEM_REPORT_DISABLED            (0U)

    /*****************************************************************************/
    /* Symbolic name definitions */
    /*****************************************************************************/
    /*
        Symbolic name definitions for FR controllers and timers.
        The symbolic names identify the controller/timers (within an ECU).
    */
    [!SELECT "as:modconf($ModuleName)[1]"!][!/* SELECT1 */!][!//
      [!SELECT "./FrMultipleConfiguration"!][!/* SELECT2 */!][!//
        [!VAR "OldControllerIdx" = "num:i(ecu:get('Eray.MaxControllers'))"!][!//
        [!LOOP "FrController/*"!][!/* LOOP4 */!][!//
          [!VAR "CurrControllerIdx" = "FrCtrlIdx"!][!//
          [!IF "$CurrControllerIdx = $OldControllerIdx"!][!//
            [!ERROR!][!//
              Config Error: The Controller Index [!"$CurrControllerIdx"!] has already been allocated, [!//
              configure a new controller for [!"node:path(.)"!][!//
            [!ENDERROR!][!//
          [!ENDIF!][!//
          /* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
          due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
          due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
          due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
          due to Autosar Naming constraints.*/
          #define Fr_17_ErayConf_FrController_[!"@name"!]       ([!"FrCtrlIdx"!]U)
          [!VAR "OldControllerIdx" = "$CurrControllerIdx"!][!//
          [!SELECT "FrAbsoluteTimer/*[1]"!][!/* SELECT3 */!][!//
            [!/* The FrAbsoluteTimer container have only one element FrAbsTimerIdx so its value will be printed */!]
            /* MISRA2012_RULE_5_1_JUSTIFICATION: Name of identifiers going beyond 32 chars.
            due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_2_JUSTIFICATION: Name of identifiers going beyond 32 chars.
            due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_4_JUSTIFICATION: Name of identifiers going beyond 32 chars.
            due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_5_JUSTIFICATION: Name of identifiers going beyond 32 chars.
            due to Autosar Naming constraints.*/
            #define Fr_17_ErayConf_FrAbsoluteTimer_[!"node:name(../../.)"!]    ([!"."!]U)
          [!ENDSELECT!][!/* SELECT3 */!]
        [!ENDLOOP!][!/* LOOP4 */!]
      [!ENDSELECT!][!/* SELECT1 */!][!//
    [!ENDSELECT!][!/* SELECT2 */!][!//
  [!ENDSELECT!][!//SELECT "as:modconf($ModuleName)[1]"!][!//
  /*****************************************************************************/

  /*******************************************************************************
  **                      Derived Configuration Parameters                      **
  *******************************************************************************/
  [!VAR "Controller0Available" = "num:i(0)"!][!//
  [!VAR "Controller1Available" = "num:i(0)"!][!//
  [!VAR "FR_MSG_BUFF_COUNT_MAX_0" = "num:i(0)"!][!//
  [!VAR "FR_MSG_BUFF_COUNT_MAX_1" = "num:i(0)"!][!//
  [!VAR "FrFifoConfiguredFlag" = "num:i(0)"!][!//
  [!SELECT "as:modconf($ModuleName)[1]"!][!//
    [!SELECT "./FrMultipleConfiguration"!][!//
      [!/* Calculate the fCLC_ERAY */!][!//
	  [!/*
		  Note: Elektrobit Automotive GmbH modified the original code provided
        by the third party supplier. The modification is provided for
        convenience.
        Please use the modification on your discretion and account, or
        use the unmodified files provided with this distribution. 
  Please see for the reasons in the file ImportantNotes.txt for tag

		ASCFRIF-1063 : Fr driver is implemented according with ASR 4.4.0 version and FrIf module is implemented according with ASR 4.0.3.
		Fr_17_Eray_Cfg.h original version is present in MCAL_Delivery\Original_Files\Fr

	  */!][!//
      [!VAR "FrClockDivider" = "node:ref('./*/FrClockConfiguration/FrClockDivider')"!][!//
      [!VAR "FrClockCLCERAY" = "num:i($SPBFrequency div $FrClockDivider)"!][!//
      [!VAR "Counter" = "num:i(count(./FrMultipleConfiguration/FrController/*))"!][!//
      [!FOR "Index" = "0" TO "(num:i($Counter)- 1)"!][!//
        [!SELECT "./FrMultipleConfiguration/FrController/*[@index = $Index]"!][!//
          [!VAR "ControllerIndex" = "./FrCtrlIdx"!][!//
          [!VAR "ControllerPath" = "node:path(.)"!][!//
          [!/* Example: ControllerPath = /AUTOSAR/TOP-LEVEL-PACKAGES/Fr/ELEMENTS/Fr/FrMultipleConfiguration/FrController/FrController_0 */!][!//
          [!VAR "ControllerShortNamePath" = "substring-after($ControllerPath, 'FrController')"!][!//
          [!/* Example: ControllerShortNamePath = /FrController_0 */!][!//
          [!/* Check if FIFO is configured */!][!//
          [!IF "(node:exists(concat($ControllerPath, '/FrFifo/*[1]')))"!][!/* FIFO_NODE_CHECK */!][!//
            [!VAR "FrFifoConfiguredFlag" = "num:i(1)"!][!//
          [!ENDIF!][!//
          [!/*
          [cover parentID={A6B4677A-D15D-4223-969B-8023F0D83472}] Code Generation dependency on other modules [/cover]
          */!][!//
	  [!/*
	      Note: Elektrobit Automotive GmbH modified the original code provided
        by the third party supplier. The modification is provided for
        convenience.
        Please use the modification on your discretion and account, or
        use the unmodified files provided with this distribution. 
  Please see for the reasons in the file ImportantNotes.txt for tag

ASCFRIF-1045 : Fr driver is implemented according with ASR 4.2.2 version and FrIf module is implemented according with ASR 4.0.3.
Fr_17_Eray_Cfg.h original version is present in MCAL_Delivery\Original_Files\Fr
	  */!][!//
          [!SELECT "as:modconf('FrIf')[1]/FrIfConfig/*"!][!/* SELECT1 */!][!//
            [!VAR "CtrlRefFound" = "num:i(0)"!][!//
            [!LOOP "FrIfCluster/*"!][!/* LOOP2 */!][!//
              [!LOOP "FrIfController/*"!][!/* LOOP3 */!][!//
                [!VAR "FrIfControllerPath" = "node:ref(node:path(./FrIfFrCtrlRef))"!][!//
                [!VAR "FrConfigPath" = "substring-after($FrIfControllerPath, '/Fr/Fr/')"!][!//
                [!VAR "FrConfigPath" = "substring-before($FrConfigPath, $ControllerShortNamePath)"!][!//
                [!VAR "FrIfControllerPath" = "substring-after($FrIfControllerPath, $FrConfigPath)"!][!//
                [!IF "$FrIfControllerPath = $ControllerShortNamePath"!][!/* IF1 */!][!//
                  [!VAR "CtrlRefFound" = "num:i(1)"!][!//
                  [!//
                  [!IF "$ControllerIndex = num:i(0)"!][!//
                    [!VAR "Controller0Available" = "num:i(1)"!][!//
                    [!/* Maximum message buffers limited to 128 */!][!//
                    [!IF "num:i(128) > num:i(count(FrIfLPdu/*))"!][!//
                      [!VAR "FR_MSG_BUFF_COUNT_MAX_0" = "num:i(count(FrIfLPdu/*))"!][!//
                    [!ELSE!][!//
                      [!VAR "FR_MSG_BUFF_COUNT_MAX_0" = "num:i(128)"!][!//
                    [!ENDIF!][!//
                    [!BREAK!][!//
                  [!ENDIF!][!//
                  [!IF "$ControllerIndex = num:i(1)"!][!//
                    [!VAR "Controller1Available" = "num:i(1)"!][!//
                    [!/* Maximum message buffers limited to 128 */!][!//
                    [!IF "num:i(128) > num:i(count(FrIfLPdu/*))"!][!//
                      [!VAR "FR_MSG_BUFF_COUNT_MAX_1" = "num:i(count(FrIfLPdu/*))"!][!//
                    [!ELSE!][!//
                      [!VAR "FR_MSG_BUFF_COUNT_MAX_1" = "num:i(128)"!][!//
                    [!ENDIF!][!//
                    [!BREAK!][!//
                  [!ENDIF!][!//
                [!ENDIF!][!/* IF1 */!][!//
              [!ENDLOOP!][!/* LOOP3 */!][!//
              [!IF "$CtrlRefFound = 1"!]
                [!BREAK!]
              [!ENDIF!][!//
            [!ENDLOOP!][!/* LOOP2 */!][!//
            [!IF "$CtrlRefFound != num:i(1)"!][!//
              [!ERROR!][!//
                Error: FlexRay controllers [!"$ControllerShortNamePath"!] in Fr module is not referred by any of the FrIf clusters.
              [!ENDERROR!][!//
            [!ENDIF!][!//
          [!ENDSELECT!][!/* SELECT1 */!][!//
        [!ENDSELECT!][!//
      [!ENDFOR!][!//
    [!ENDSELECT!][!//
  [!ENDSELECT!][!//
  [!//
  /*
  Configuration: FR_17_ERAY_CLEAR_RAMS_TIMEOUT
  Specifies the timeout duration in nanoseconds until a timeout
  is raised after initialization of the E-Ray internal RAM blocks.
  The initialization of the E-Ray internal RAM blocks requires minimum
  2048 fCLC_ERAY cycles. 5 percent margin(102 cycles) added to the value.
  */
  [!/*
  [cover parentID={841CF55D-063A-4372-AFE4-6A6F75248E0B}] FR_17_ERAY_CLEAR_RAMS_TIMEOUT [/cover]
  */!][!//
  #define FR_17_ERAY_CLEAR_RAMS_TIMEOUT                ([!"num:i(ceiling((num:i(2150) * num:i(1000000000))div($FrClockCLCERAY)))"!]U)

  /*
  Configuration: FR_17_ERAY_POC_BUSY_TIMEOUT
  Specifies the timeout duration in nanoseconds for the POC to exit the
  busy state during initialization until a timeout is raised.
  It takes a maximum of 1024 fCLC_ERAY cycles for the POC to exit busy state.
  5 percent margin(51 cycles) added to the value.
  */
  [!/*
  [cover parentID={79FC832D-93C5-45a7-8804-4409AD29A269}] Timeout for POC busy check during initialization [/cover]
  */!][!//
  [!/*
  [cover parentID={A827547F-F634-4f43-8BBB-D3AF2A06C976}] FR_17_ERAY_POC_BUSY_TIMEOUT [/cover]
  */!][!//
  #define FR_17_ERAY_POC_BUSY_TIMEOUT                  ([!"num:i(ceiling((num:i(1075) * num:i(1000000000))div($FrClockCLCERAY)))"!]U)

  /*
  Configuration: FR_17_ERAY_MBF_TO_OBF_TRNSF_TIMEOUT
  Specifies the worst case timeout duration in nanoseconds for
  the data transfer from Message Buffer RAM to Output Buffer.
  It takes a maximum of 435 fCLC_ERAY cycles for this data transfer.
  5 percent margin(22 cycles) is added to this value.
  */
  [!/*
  [cover parentID={95C2F636-D546-46bb-84FF-9E474303235A}] FR_17_ERAY_MBF_TO_OBF_TRNSF_TIMEOUT [/cover]
  */!][!//
  #define FR_17_ERAY_MBF_TO_OBF_TRNSF_TIMEOUT          ([!"num:i(ceiling((num:i(457) * num:i(1000000000))div($FrClockCLCERAY)))"!]U)

  [!/* ------------------------------------------*/!][!//
  /* Flag for FIFO configuration */
  [!/*
  [cover parentID={A243FB88-8E33-43e5-AEC0-312960520DCD}] FR_17_ERAY_FIFO_CONFIGURED [/cover]
  */!][!//
  [!IF "$FrFifoConfiguredFlag = num:i(1)"!][!//
    #define FR_17_ERAY_FIFO_CONFIGURED          (STD_ON)
  [!ELSE!][!//
    #define FR_17_ERAY_FIFO_CONFIGURED          (STD_OFF)
  [!ENDIF!][!//

  [!/* ------------------------------------------*/!][!//
  /*
     Estimated maximum number of message buffers used per controller.
    Min (128, max(LPDU count in all PB configurations))
  */
  [!/*
  [cover parentID={9880A71D-4E76-4e29-801F-6089F26689E4}] FR_17_ERAY_MSG_BUFF_COUNT_MAX_X [/cover]
  */!][!//
  #define FR_17_ERAY_MSG_BUFF_COUNT_MAX_0 ([!"$FR_MSG_BUFF_COUNT_MAX_0"!]U)
  #define FR_17_ERAY_MSG_BUFF_COUNT_MAX_1 ([!"$FR_MSG_BUFF_COUNT_MAX_1"!]U)

  /* Number of ERAY Controllers available in the device */
  [!/*
  [cover parentID={54714E66-0461-444b-8CAC-1C86954A88DF}] FR_17_ERAY_NUM_CONTROLLERS_IN_DEVICE [/cover]
  */!][!//
  #define FR_17_ERAY_NUM_CONTROLLERS_IN_DEVICE  ([!"ecu:get('Eray.MaxControllers')"!]U)

  [!/*
  [cover parentID={162402B8-DE7A-44d9-9ADC-83FCA6AE03B6}] FR_17_ERAY_CONTROLLER0_CONFIGURED [/cover]
  */!][!//
  [!IF "$Controller0Available = num:i(1)"!][!//
    #define FR_17_ERAY_CONTROLLER0_CONFIGURED   (STD_ON)
  [!ELSE!][!//
    #define FR_17_ERAY_CONTROLLER0_CONFIGURED   (STD_OFF)
  [!ENDIF!][!//

  [!/*
  [cover parentID={89352554-34E7-435a-847B-0215A7B891F0}] FR_17_ERAY_CONTROLLER1_CONFIGURED [/cover]
  */!][!//
  [!IF "$Controller1Available = num:i(1)"!][!//
    #define FR_17_ERAY_CONTROLLER1_CONFIGURED   (STD_ON)
  [!ELSE!][!//
    #define FR_17_ERAY_CONTROLLER1_CONFIGURED   (STD_OFF)
  [!ENDIF!][!//

  /*
  Configuration: FR_17_ERAY_RUNTIME_ERROR_DETECT
  Preprocessor switch for enabling the runtime error detection and
  reporting.
  - if STD_ON, Reporting runntime error is Enabled
  - if STD_OFF,Reporting runntime error is Disabled
  */
  [!/* [cover parentID={0C7C60C7-33B4-4514-9324-8FD111C3AD78}] [/cover] */!][!//
  #define FR_17_ERAY_RUNTIME_ERROR_DETECT  [!//
  [!IF "(node:exists(FrGeneral/FrRunTimeErrorDetect))"!][!//
    [!CALL "Fr_17_Eray_CG_ConfigSwitch","nodeval" = "FrGeneral/FrRunTimeErrorDetect"!][!//
  [!ELSE!][!//
    (STD_OFF)[!//
  [!ENDIF!][!//

  /*
  Configuration: FR_17_ERAY_EXTENDED_LPDU_REPORTING
  Adds/removes the FR EXTENDED LPDU REPORTING feature
  - if STD_ON, Enable LPDU reporting
  - if STD_OFF, Disable LPDU reporting
  */
  [!/* [cover parentID={D7D4B69A-E1C0-4e8c-8ABE-8C698CA76142}] [/cover] */!][!//
  #define FR_17_ERAY_EXTENDED_LPDU_REPORTING  [!//
  [!IF "(node:exists(FrGeneral/FrExtendedLPduReporting))"!][!//
    [!CALL "Fr_17_Eray_CG_ConfigSwitch","nodeval" = "FrGeneral/FrExtendedLPduReporting"!][!//
  [!ELSE!][!//
    (STD_OFF)[!//
  [!ENDIF!][!//

[!ENDINDENT!][!//

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/


#endif /* FR_17_ERAY_CFG_H */
