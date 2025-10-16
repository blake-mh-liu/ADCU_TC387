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
**  FILENAME  : Can_17_McmCan_Cfg.h                                           **
**                                                                            **
**  VERSION   : 12.0.0                                                         **
**                                                                            **
**  DATE      : 2021-08-19                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Can_17_McmCan.bmd                                 **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={A7B6579C-0625-4f54-9CC9-6C4981949D65}]    **
**                                                                            **
**  DESCRIPTION  : Code template header file for Can Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Can Driver, AUTOSAR Release 4.2.2 and **
**                     4.4.0                                                  **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*****************************************************************************/!]
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
**  FILENAME  : Can_17_McmCan_Cfg.h                                           **
**                                                                            **
**  VERSION   : 12.0.0                                                        **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]          !!!IGNORE-LINE!!!               **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]            !!!IGNORE-LINE!!!               **
**                                                                            **
**  BSW MODULE DECRIPTION : Can_17_McmCan.bmd                                 **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Can configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Can Driver, AUTOSAR Release 4.2.2 and **
**                     4.4.0                                                  **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

[!INDENT "0"!]
#ifndef CAN_17_MCMCAN_CFG_H
#define CAN_17_MCMCAN_CFG_H
[!/* Include Code Generator Macros */!][!//
[!INCLUDE "Can_17_McmCan.m"!][!//
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Can')[1]/CanConfigSet"!][!//
[!//
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/*******************************************************************************
**                      Common Published Information                          **
*******************************************************************************/
[!NOCODE!][!//
  /* Autosar specification version */
  [!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
  [!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
  [!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
[!ENDNOCODE!][!//
/* [cover parentID={BDE616FE-5D39-4b9d-9390-8351CC6C490C}]
[/cover] */
/* [cover parentID={7BE20AAE-30B8-46f5-ABBC-F2E65FBCEEE8}]
[/cover] */
#define CAN_17_MCMCAN_AR_RELEASE_MAJOR_VERSION          ([!"$MajorVersion"!]U)
/* [cover parentID={B0D7A378-F23B-4f83-86A7-50682CB089E5}]
[/cover] */
#define CAN_17_MCMCAN_AR_RELEASE_MINOR_VERSION          ([!"$MinorVersion"!]U)
/* [cover parentID={F34E3ADE-341D-4e08-9A3B-B454B00382E4}]
[/cover] */
#define CAN_17_MCMCAN_AR_RELEASE_REVISION_VERSION       ([!"$RevisionVersion"!]U)
[!NOCODE!][!//
  /* Vendor specific implementation version information */
  [!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
  [!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
  [!VAR "SwPatchVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
[!ENDNOCODE!]
/* [cover parentID={98E1F5ED-AA8E-49af-8DBB-E84CD1B0960B}]
[/cover] */
#define CAN_17_MCMCAN_SW_MAJOR_VERSION                  ([!"$SwMajorVersion"!]U)
/* [cover parentID={EAB7012E-044A-4fb7-84E1-245B81493A73}]
[/cover] */
#define CAN_17_MCMCAN_SW_MINOR_VERSION                  ([!"$SwMinorVersion"!]U)
/* [cover parentID={4763C7E9-3BE5-4b3b-96DA-1E92B11A9191}]
[/cover] */
#define CAN_17_MCMCAN_SW_PATCH_VERSION                  ([!"$SwPatchVersion"!]U)
[!VAR "MaxKernel" = "num:i(ecu:get('Can.MaxKernels'))"!][!//
[!VAR "MaxController" = "num:i(ecu:get('Can.MaxCtrlKer'))"!][!//
[!VAR "MaxCore" = "num:i(ecu:get('Mcu.NoOfCoreAvailable'))"!][!//
[!/* Can Activated controller identification and allocation */!][!//
[!CALL "CAN_CG_ControllerAllocation"!][!//
[!/* Bring in core specific configuration of the CAN controllers */!][!//
[!CALL "CAN_CG_GenerateModuleMap","Module" = "'CAN'"!][!//
[!VAR "BusOffInterruptStatus" = "num:i(0)"!][!//
[!VAR "RxInterruptStatus" = "num:i(0)"!][!//
[!VAR "TxInterruptStatus" = "num:i(0)"!][!//
[!VAR "BusOffPollingStatus" = "num:i(0)"!][!//
[!VAR "RxPollingStatus" = "num:i(0)"!][!//
[!VAR "RxMixedPollingStatus" = "num:i(0)"!][!//
[!VAR "RxMixedStatus" = "num:i(0)"!][!//
[!VAR "TxMixedStatus" = "num:i(0)"!][!//
[!VAR "TxPollingStatus" = "num:i(0)"!][!//
[!VAR "TxMixedPollingStatus" = "num:i(0)"!][!//
[!VAR "WUPollingStatus" = "num:i(0)"!][!//
[!VAR "RxDedInterruptStatus" = "num:i(0)"!][!//
[!VAR "RxFifoInterruptStatus" = "num:i(0)"!][!//


[!LOOP "./CanController/*"!][!//
  [!IF "CanControllerActivation = 'true'"!][!//
    [!IF "CanBusoffProcessing = 'INTERRUPT'"!][!//
      [!VAR "BusOffInterruptStatus" = "num:i(1)"!][!//
    [!ELSE!][!//
      [!VAR "BusOffPollingStatus" = "num:i(1)"!][!//
    [!ENDIF!][!//
    [!IF "CanRxProcessing = 'INTERRUPT'"!][!//
      [!VAR "RxInterruptStatus" = "num:i(1)"!][!//
    [!ELSEIF "CanRxProcessing = 'POLLING'"!][!//
      [!VAR "RxPollingStatus" = "num:i(1)"!][!//
    [!ELSE!][!//
      [!VAR "RxMixedStatus" = "num:i(1)"!][!//
    [!ENDIF!][!//
    [!IF "CanTxProcessing = 'INTERRUPT'"!][!//
      [!VAR "TxInterruptStatus" = "num:i(1)"!][!//
    [!ELSEIF "CanTxProcessing = 'POLLING'"!][!//
      [!VAR "TxPollingStatus" = "num:i(1)"!][!//
    [!ELSE!][!//
      [!VAR "TxMixedStatus" = "num:i(1)"!][!//
    [!ENDIF!][!//
    [!IF "CanWakeupProcessing   = 'POLLING'"!][!//
      [!VAR "WUPollingStatus" = "num:i(1)"!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//
/*******************************************************************************
**          Global Macro Definitions                                          **
*******************************************************************************/

[!/* [cover parentID={78A6E111-2A16-4706-9205-310977BE5798}]
[/cover] */!][!//
[!/* [cover parentID={6DA535BF-4C67-40ce-BA1F-61D6FFD4BD5E}]
[/cover] */!][!//
[!VAR "CanRxCalloutFnExists" = "num:i(0)"!][!//
    [!/* Extract Receive L-PDU Callout Function Pointer */!][!//
    [!IF "node:exists(../CanGeneral/CanLPduReceiveCalloutFunction/*[1]) = 'true'"!][!//
      [!VAR "RxLPduCallout" = "../CanGeneral/CanLPduReceiveCalloutFunction/*[1]"!][!//
      [!IF "$RxLPduCallout != '""' and $RxLPduCallout != '' and $RxLPduCallout != 'NULL_PTR' and $RxLPduCallout != 'NULL'"!][!//
        [!VAR "CanRxCalloutFnExists" = "num:i(1)"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
/* L-PDU receive callout support enabled or not */
[!/* [cover parentID={137D3C33-4017-40ab-918B-7CADC30D156C}]
[/cover] */!][!//
[!IF "$CanRxCalloutFnExists = num:i(1)"!][!//
#define CAN_17_MCMCAN_LPDU_RX_CALLOUT                    (STD_ON)
[!ELSE!][!//
#define CAN_17_MCMCAN_LPDU_RX_CALLOUT                    (STD_OFF)
[!ENDIF!][!//

[!/* [cover parentID={78A6E111-2A16-4706-9205-310977BE5798}]
[/cover] */!][!//
/* Master core is allocated with CAN controllers */
[!IF "$CGMasterAlloc = 1"!][!//
#define CAN_17_MCMCAN_MASTER_CORE_ALLOCATION                       (STD_ON)
[!ELSE!][!//
#define CAN_17_MCMCAN_MASTER_CORE_ALLOCATION                       (STD_OFF)
[!ENDIF!][!//

[!/* [cover parentID={211F892D-CBE4-4d08-A1AF-EA8D2E16463B}]
[/cover] */!][!//
/* Multicore Enabled or not */
#define CAN_17_MCMCAN_MULTICORE_ERROR_DETECT                       [!//
[!CALL "CAN_CG_ConfigSwitch","nodeval" = "../CanGeneral/CanMultiCoreErrorDetect"!]

[!/* [cover parentID={F68E4DC0-5C6F-4a64-8F5C-BC258FDEBF07}]
[/cover] */!][!//
#define CAN_17_MCMCAN_RUNTIME_ERROR_DETECT               [!//
[!CALL "CAN_CG_ConfigSwitch","nodeval" = "../CanGeneral/CanRunTimeErrorDetect"!]

[!/* [cover parentID={1D964BF4-8B27-46da-A999-9B5888FF124A}]
[/cover] */!][!//
/* Maximum number of CAN Controllers configured in a ConfigSet */
#define CAN_17_MCMCAN_NOOF_CONTROLLER                       (uint8)([!"num:i(count(./CanController/*))"!]U)
[!FOR "CoreIndx" = "0" TO "$MaxCore - '1'"!][!//
  [!VAR "CheckText" = "text:toupper(concat('CORE',$CoreIndx))"!][!//
  [!/* Bring in core specific CAN controller count */!][!//
  [!CALL "CAN_CG_GetContInCore","CoreName" = "$CheckText"!][!//
  [!IF "text:contains( text:split($CGAllocCore,','), $CheckText )"!][!//

  /* Maximum number of CAN Controllers configured in a ConfigSet for [!"$CheckText"!] */
  #define CAN_17_MCMCAN_[!"$CheckText"!]_NOOF_CONTROLLER      (uint8)([!"$NoOfCont"!]U)
  [!ENDIF!][!//
[!ENDFOR!][!//

[!VAR "TrigTransmit" = "num:i(0)"!][!//
[!VAR "CanHwObjectCount" = "num:i(count(./CanHardwareObject/*))"!][!//
[!FOR "HwObjIndx" = "1" TO "num:i($CanHwObjectCount)"!][!//
  [!IF "node:exists(./CanHardwareObject/*[position()=$HwObjIndx]/CanTriggerTransmitEnable/*[1]) = 'true'"!][!//
    [!IF "node:value(./CanHardwareObject/*[position()=$HwObjIndx]/CanTriggerTransmitEnable/*[1]) = 'true'"!][!//
      [!VAR "TrigTransmit" = "num:i(1)"!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDFOR!][!//
[!/* [cover parentID={F3CEB2B5-85EF-4d02-84D8-E2EEBFDA78C3}]
[/cover] */!][!//
/* Trigger transmit Enabled or not */
#define CAN_17_MCMCAN_TRIG_TRANSMIT                                 ([!IF "$TrigTransmit = num:i(1)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

[!VAR "MultiTxPeriod" = "num:i(0)"!][!//
[!VAR "MultiRxPeriod" = "num:i(0)"!][!//
[!/* [cover parentID={0D8BDC83-988C-490c-BD8E-DF31862D8F2D}]
[/cover] */!][!//
/* Maximum number of main function RW periods configured in a ConfigSet */
[!VAR "MultiperiodsVal" = "num:i(count(../CanGeneral/CanMainFunctionRWPeriods/*))"!][!//
[!IF "$MultiperiodsVal > 1"!][!//
  [!IF "$RxPollingStatus = num:i(1) or $RxMixedStatus = num:i(1)"!][!//
    [!VAR "MultiRxPeriod" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!VAR "MultiperiodsVal" = "num:i(count(../CanGeneral/CanMainFunctionRWPeriods/*))"!][!//
[!IF "$MultiperiodsVal > 1"!][!//
  [!IF "$TxPollingStatus = num:i(1) or $TxMixedStatus = num:i(1)"!][!//
    [!VAR "MultiTxPeriod" = "num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
#define CAN_17_MCMCAN_NOOF_RX_TX_PERIODS_CONFIG              ([!"$MultiperiodsVal"!]U)

[!/* [cover parentID={4DE6DCB0-21D2-483a-A1A1-6F2C7C856019}]
[/cover] */!][!//
/* Multiple cycle period for Recieve is configured in a ConfigSet */
#define CAN_17_MCMCAN_RX_MULTI_PERIODS_SUPPORT               ([!IF "$MultiRxPeriod = num:i(1)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

[!/* [cover parentID={636B07F0-AFFA-4e37-A3E1-0B8710D31670}]
[/cover] */!][!//
/* Multiple cycle period for Transmit is configured in a ConfigSet */
#define CAN_17_MCMCAN_TX_MULTI_PERIODS_SUPPORT               ([!IF "$MultiTxPeriod = num:i(1)"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

[!VAR "IcomRxMsgCount" = "num:i(0)"!][!//
[!VAR "IcomRxMsgSignalCount" = "num:i(0)"!][!//
[!VAR "IcomConfigCount" = "num:i(count(./CanIcom/./*[1]/CanIcomConfig/*))"!][!//
[!IF "../CanGeneral/CanPublicIcomSupport = 'true'"!][!//
  [!/* Loop for calculate Total number of Icom-Message and Icom-signal with in the configuration  */!][!//
  [!LOOP "./CanIcom/./*[1]/CanIcomConfig/*"!][!//
    [!VAR "IcomRxMsgCount" = "num:i(count(./CanIcomWakeupCauses/CanIcomRxMessage/*) + $IcomRxMsgCount )"!][!//
    [!FOR "Rxindx" = "1" TO "num:i($IcomRxMsgCount)"!][!//
      [!IF "node:exists(./CanIcomWakeupCauses/CanIcomRxMessage/*[position()=$Rxindx]/CanIcomRxMessageSignalConfig/*) = 'true'"!][!//
        [!VAR "IcomRxMsgSignalCount" = "num:i(count(./CanIcomWakeupCauses/CanIcomRxMessage/*[position()=$Rxindx]/CanIcomRxMessageSignalConfig/*) + $IcomRxMsgSignalCount)"!][!//
      [!ENDIF!][!//
    [!ENDFOR!][!//
  [!ENDLOOP!][!//
  [!/* [cover parentID={6B735756-7B1C-4ca3-85E4-B389A7F41960}]
  [/cover] */!][!//
  /* Maximum number of Icom configurations with in the ConfigSet */
  #define CAN_17_MCMCAN_NOOF_ICOM_CONFIGURATIONS        (IcomConfigIdType) ([!"$IcomConfigCount"!]U)

  [!/* [cover parentID={4395F5EB-4259-4798-9FA0-48F585BDB108}]
  [/cover] */!][!//
  /* Maximum number of Icom Message configurations with in the ConfigSet */
  #define CAN_17_MCMCAN_NOOF_ICOM_MSGCONFIGURATIONS     ([!"$IcomRxMsgCount"!]U)

  [!/* [cover parentID={CFF33692-9DAF-4876-B8A6-C210DDB76E72}]
  [/cover] */!][!//
  /* Maximum number of Icom Signal configurations with in the ConfigSet */
  #define CAN_17_MCMCAN_NOOF_ICOM_SIGNALCONFIGURATIONS  ([!"$IcomRxMsgSignalCount"!]U)
[!ENDIF!][!//

[!/* [cover parentID={A1298543-A455-4b70-9559-D607ABE2AE34}]
[/cover] */!][!//
/* Initialization and De-Initilaization user mode configuration */
#define CAN_17_MCMCAN_INIT_DEINIT_API_MODE   ([!"../CanGeneral/CanInitDeInitApiMode"!])

/*******************************************************************************
**                      CAN General Information                               **
*******************************************************************************/
/* Configuration: CAN_17_MCMCAN_INSTANCE_ID
 - Specifies the InstanceId of this module instance
*/
[!/* [cover parentID={E82F8AA2-1043-440c-85D6-2C804A008B52}]
[/cover] */!][!//
#define CAN_17_MCMCAN_INSTANCE_ID                     ([!"../CanGeneral/CanIndex"!]U)

/* Configuration: CAN_17_MCMCAN_DEV_ERROR_DETECT
 - STD_ON  - DET is enabled
 - STD_OFF - DET is disabled
*/
[!/* [cover parentID={A8611F59-B315-4dab-AE47-64C8D534CC84}]
[/cover] */!][!//
[!IF "$MinorVersion = num:i(2)"!][!//
#define CAN_17_MCMCAN_DEV_ERROR_DETECT                            [!//
[!CALL "CAN_CG_ConfigSwitch","nodeval" = "../CanGeneral/CanDevErrorDetection"!]
[!ELSE!][!//
#define CAN_17_MCMCAN_DEV_ERROR_DETECT                            [!//
[!CALL "CAN_CG_ConfigSwitch","nodeval" = "../CanGeneral/CanDevErrorDetect"!]
[!ENDIF!][!//


/* Configuration: CAN_17_MCMCAN_VERSION_INFO_API
 - STD_ON  - Can_17_McmCan_GetVersionInfo API is enabled
 - STD_OFF - Can_17_McmCan_GetVersionInfo API is disabled
*/
[!/* [cover parentID={BFA2B975-6875-4b44-9279-CE09AF0D31A1}]
[/cover] */!][!//
#define CAN_17_MCMCAN_VERSION_INFO_API                            [!//
[!CALL "CAN_CG_ConfigSwitch","nodeval" = "../CanGeneral/CanVersionInfoApi"!]

/* Configuration: CAN_17_MCMCAN_MULTIPLEXED_TRANSMISSION
 - STD_ON  - Multiplexed transmission feature is enabled
 - STD_OFF - Multiplexed transmission feature is disabled
*/
[!/* [cover parentID={50E6705F-C8BB-46fa-9C9F-A7908348E200}]
[/cover] */!][!//
#define CAN_17_MCMCAN_MULTIPLEXED_TRANSMISSION                    [!//
[!CALL "CAN_CG_ConfigSwitch","nodeval" = "../CanGeneral/CanMultiplexedTransmission"!]

/* Configuration: CAN_17_MCMCAN_TIMEOUT_DURATION
 - Specifies the maximum amount of time for a blocking function until
   a time-out is raised in short term wait loops
*/
[!/* [cover parentID={F045BC45-613C-42a0-9436-C72F69722508}]
[/cover] */!][!//
[!VAR "CanTimeoutDuration" = "../CanGeneral/CanTimeoutDuration"!][!//
#define CAN_17_MCMCAN_TIMEOUT_DURATION                            ([!"num:i($CanTimeoutDuration * 10000000)"!]U)
/*
  Note: Elektrobit Automotive GmbH modified the original code provided
        by the third party supplier. The modification is provided for
        convenience.
        Please use the modification on your discretion and account, or
        use the unmodified files provided with this distribution. 
  Please see for the reasons in the file ImportantNotes.txt for tag


ASCINFINEON-776 CanSetBaudrateApi should not be a list because it is not readable by CanIf
*/
/* Configuration: CAN_17_MCMCAN_SET_BAUDRATE_API
 - STD_ON  - Can_17_McmCan_SetBaudrate API is enabled
 - STD_OFF - Can_17_McmCan_SetBaudrate API is Disabled
*/
[!/* [cover parentID={B3714324-EEA9-44ee-8BC0-0695D8DE4EDC}]
[/cover] */!][!//
[!IF "node:exists(../CanGeneral/CanSetBaudrateApi) = 'true'"!][!//
    #define CAN_17_MCMCAN_SET_BAUDRATE_API                            [!//
    [!CALL "CAN_CG_ConfigSwitch","nodeval" = "../CanGeneral/CanSetBaudrateApi"!]
  [!ELSE!][!//
    #define CAN_17_MCMCAN_SET_BAUDRATE_API                           (STD_OFF)
[!ENDIF!][!//

/* Configuration: CanControllerFdBaudrateConfig
 - STD_ON  - FD Operation is Enabled
 - STD_OFF - FD Operation is Disabled
*/
[!/* [cover parentID={B5240496-84D2-4b7c-8F70-A9B7C12273B1}]
[/cover] */!][!//
[!/* Loop set for controller specific information read */!][!//
[!VAR "FDNodesPresentVal" = "num:i(0)"!][!//
[!LOOP "./CanController/*"!][!//
  [!VAR "BaudrateCfgCount" = "num:i(count(./CanControllerBaudrateConfig/*))"!][!//
  [!FOR "BaudrateIndx" = "1" TO "$BaudrateCfgCount"!][!//
    [!IF "(node:exists(CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig/*[1]))"!][!//
      [!/* Set Global switch for FD support */!][!//
      [!VAR "FDNodesPresentVal" = "num:i(1)"!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
[!ENDLOOP!][!//
[!IF "$FDNodesPresentVal = 0"!][!//
  #define CAN_17_MCMCAN_FD_ENABLE                                   (STD_OFF)
[!ELSE!][!//
  #define CAN_17_MCMCAN_FD_ENABLE                                   (STD_ON)
[!ENDIF!][!//
/* Configuration: CAN_17_MCMCAN_DEINIT_API
 - STD_ON  - CAN De-initialization API is enabled
 - STD_OFF - CAN De-initialization API is not enabled
*/
[!/* [cover parentID={D6062C72-4A90-433c-9B34-44D01B2A096E}]
[/cover] */!][!//
#define CAN_17_MCMCAN_DEINIT_API                                  [!//
[!CALL "CAN_CG_ConfigSwitch","nodeval" = "../CanGeneral/CanDeInitApi"!]

/* Configuration: CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT
 - STD_ON  - CAN Pretended networking is enabled
 - STD_OFF - CAN Pretended networking is not enabled
*/
[!/* [cover parentID={5C4ADE3F-9408-4970-821C-BF1F0402FBA9}]
[/cover] */!][!//
#define CAN_17_MCMCAN_PUBLIC_ICOM_SUPPORT                         [!//
[!CALL "CAN_CG_ConfigSwitch","nodeval" = "../CanGeneral/CanPublicIcomSupport"!]

/* Number of transmit hardware object buffers present */
#define CAN_17_MCMCAN_MAX_SWOBJECT_INDEX            ((uint8)([!"num:i((ecu:get('Can.MaxControllers')*num:i(32)))"!]U))

/* Number of nodes per kernel */
[!/* [cover parentID={687FEC40-1FFC-4921-AD2E-8866A19BBCE3}]
[/cover] */!][!//
#define CAN_17_MCMCAN_NOOF_NODES_PER_KERNEL     ((uint32)([!"(ecu:get('Can.MaxCtrlKer'))"!]U))



/******************************************************************************/
                    /* CAN Controller Configurations */
/******************************************************************************/
/* CAN Activation on CORE0
 - STD_ON  - A CAN Kernel is activated on Core 0
 - STD_OFF - No CAN Kernel is activated on Core 0
*/
[!/* [cover parentID={D2DB224C-5A77-4c64-AADF-2E73B11AB17B}]
[/cover] */!][!//
[!IF "not(text:contains( text:split($CGAllocCore,','), "CORE0" ))"!][!//
  #define CAN_17_MCMCAN_CORE0_ACTIVATION                     (STD_OFF)
[!ELSE!][!//
  #define CAN_17_MCMCAN_CORE0_ACTIVATION                     (STD_ON)
[!ENDIF!][!//
/* CAN Activation on CORE1
 - STD_ON  - A CAN Kernel is activated on Core 1
 - STD_OFF - No CAN Kernel is activated on Core 1
*/
[!/* [cover parentID={D2D0EFDA-83D1-4ec6-88BE-FE98F12BAC50}]
[/cover] */!][!//
[!IF "not(text:contains( text:split($CGAllocCore,','), "CORE1" ))"!][!//
  #define CAN_17_MCMCAN_CORE1_ACTIVATION                     (STD_OFF)
[!ELSE!][!//
  #define CAN_17_MCMCAN_CORE1_ACTIVATION                     (STD_ON)
[!ENDIF!][!//
/* CAN Activation on CORE2
 - STD_ON  - A CAN Kernel is activated on Core 2
 - STD_OFF - No CAN Kernel is activated on Core 2
*/
[!/* [cover parentID={28CD4DF3-493B-40cc-AA56-2D00D24EEF09}]
[/cover] */!][!//
[!IF "not(text:contains( text:split($CGAllocCore,','), "CORE2" ))"!][!//
  #define CAN_17_MCMCAN_CORE2_ACTIVATION                     (STD_OFF)
[!ELSE!][!//
  #define CAN_17_MCMCAN_CORE2_ACTIVATION                     (STD_ON)
[!ENDIF!][!//
/* CAN Activation on CORE3
 - STD_ON  - A CAN Kernel is activated on Core 3
 - STD_OFF - No CAN Kernel is activated on Core 3
*/
[!/* [cover parentID={C44BAB4A-7339-4b6a-9C46-2FE7EAFEE9FB}]
[/cover] */!][!//
[!IF "not(text:contains( text:split($CGAllocCore,','), "CORE3" ))"!][!//
  #define CAN_17_MCMCAN_CORE3_ACTIVATION                     (STD_OFF)
[!ELSE!][!//
  #define CAN_17_MCMCAN_CORE3_ACTIVATION                     (STD_ON)
[!ENDIF!][!//
/* CAN Activation on CORE4
 - STD_ON  - A CAN Kernel is activated on Core 4
 - STD_OFF - No CAN Kernel is activated on Core 4
*/
[!/* [cover parentID={5B5C1483-7C06-4478-81FC-C0AA19C9FCFB}]
[/cover] */!][!//
[!IF "not(text:contains( text:split($CGAllocCore,','), "CORE4" ))"!][!//
  #define CAN_17_MCMCAN_CORE4_ACTIVATION                     (STD_OFF)
[!ELSE!][!//
  #define CAN_17_MCMCAN_CORE4_ACTIVATION                     (STD_ON)
[!ENDIF!][!//
/* CAN Activation on CORE5
 - STD_ON  - A CAN Kernel is activated on Core 5
 - STD_OFF - No CAN Kernel is activated on Core 5
*/
[!/* [cover parentID={1BEB127A-3970-490d-B540-C35DDC8D27A4}]
[/cover] */!][!//
[!IF "not(text:contains( text:split($CGAllocCore,','), "CORE5" ))"!][!//
  #define CAN_17_MCMCAN_CORE5_ACTIVATION                     (STD_OFF)
[!ELSE!][!//
  #define CAN_17_MCMCAN_CORE5_ACTIVATION                     (STD_ON)
[!ENDIF!][!//



/*BusOff Processing Event used as Interrupt
 - STD_ON - BusOff event is notified through Interrupt mechanism by the
            configured controller
 - STD_OFF - BusOff event is notified through Interrupt mechanism by the
            configured controller
*/
[!/* [cover parentID={770D12EC-4677-4f63-9D68-818459709219}]
[/cover] */!][!//
[!IF "$BusOffInterruptStatus = 0"!][!//
  #define CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING                     (STD_OFF)
[!ELSE!][!//
  #define CAN_17_MCMCAN_BO_INTERRUPT_PROCESSING                     (STD_ON)
[!ENDIF!][!//

/* Transmission Processing Event used as Interrupt
 - STD_ON - Transmission event is notified through Interrupt mechanism by the
            configured controller
 - STD_OFF - Transmission event is notified through Interrupt mechanism by the
            configured controller
*/
[!/* [cover parentID={81AAE1E7-9BD4-4c1c-8CFF-FF767097AD58}]
[/cover] */!][!//
[!IF "$TxInterruptStatus = 0"!][!//
  #define CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING                     (STD_OFF)
[!ELSE!][!//
  #define CAN_17_MCMCAN_TX_INTERRUPT_PROCESSING                     (STD_ON)
[!ENDIF!][!//

/* Reception Processing Event used as Interrupt
 - STD_ON - Reception event is notified through Interrupt mechanism by the
            configured controller
 - STD_OFF - Reception event is not notified through Interrupt mechanism by the
            configured controller
*/
[!/* [cover parentID={51A4C1BD-C68D-4d15-AAAA-7F18A4D9D2C8}]
[/cover] */!][!//
[!IF "$RxInterruptStatus = 0"!][!//
  #define CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING                     (STD_OFF)
[!ELSE!][!//
  #define CAN_17_MCMCAN_RX_INTERRUPT_PROCESSING                     (STD_ON)
[!ENDIF!][!//

/*BusOff Processing Event used as POLLING
 - STD_ON - BusOff event is notified through Polling mechanism by the
            configured controller
 - STD_OFF - BusOff event is notified through Polling mechanism by the
            configured controller
*/
[!/* [cover parentID={8893D9B6-249D-44f6-8A18-C81B908D3230}]
[/cover] */!][!//
[!IF "$BusOffPollingStatus = 0"!][!//
  #define CAN_17_MCMCAN_BO_POLLING_PROCESSING                       (STD_OFF)
[!ELSE!][!//
  #define CAN_17_MCMCAN_BO_POLLING_PROCESSING                       (STD_ON)
[!ENDIF!][!//

/* Transmission Processing Event used as POLLING
 - STD_ON - Transmission event is notified through Polling mechanism by the
            configured controller
 - STD_OFF - Transmission event is notified through Polling mechanism by the
            configured controller
*/
[!/* [cover parentID={3887D8F4-930A-4211-B1BA-D6F52B6E6169}]
[/cover] */!][!//
[!IF "$TxPollingStatus = 0"!][!//
  #define CAN_17_MCMCAN_TX_POLLING_PROCESSING                       (STD_OFF)
[!ELSE!][!//
  #define CAN_17_MCMCAN_TX_POLLING_PROCESSING                       (STD_ON)
[!ENDIF!][!//

/* Reception Processing Event used as POLLING
 - STD_ON - Reception event is notified through Polling mechanism by the
            configured controller
 - STD_OFF - Reception event is notified through Polling mechanism by the
            configured controller
*/
[!/* [cover parentID={2D792F9D-44FA-4ceb-B70E-DE7158C44480}]
[/cover] */!][!//
[!IF "$RxPollingStatus = 0"!][!//
  #define CAN_17_MCMCAN_RX_POLLING_PROCESSING                       (STD_OFF)
[!ELSE!][!//
  #define CAN_17_MCMCAN_RX_POLLING_PROCESSING                       (STD_ON)
[!ENDIF!][!//

/* WakeUp Processing Event used as POLLING
 - STD_ON - WakeUp event is notified through Polling mechanism by the
            configured controller
 - STD_OFF - WakeUp event is notified through Polling mechanism by the
            configured controller
*/
[!/* [cover parentID={5D842C6F-4C56-44fe-A623-7C6FE0032C1A}]
[/cover] */!][!//
[!IF "$WUPollingStatus = 0"!][!//
  #define CAN_17_MCMCAN_WU_POLLING_PROCESSING                       (STD_OFF)
[!ELSE!][!//
  #define CAN_17_MCMCAN_WU_POLLING_PROCESSING                       (STD_ON)
[!ENDIF!][!//

/* Reception Processing Event used as Mixed
 - STD_ON - Reception event is notified through mixed mode by the
            configured controller
 - STD_OFF - Reception event is notified through mixed mode by the
            configured controller
*/
[!/* [cover parentID={855AF6D4-ED5C-4997-B4FC-E21418C12CA9}]
[/cover] */!][!//
[!IF "$RxMixedStatus = 1"!][!//
  #define CAN_17_MCMCAN_RX_MIXED_PROCESSING                     (STD_ON)
[!ELSE!][!//
  #define CAN_17_MCMCAN_RX_MIXED_PROCESSING                     (STD_OFF)
[!ENDIF!][!//

/* Transmission Processing Event used as Mixed
 - STD_ON - Transmission event is notified through mixed mode by the
            configured controller
 - STD_OFF - Transmission event is notified through mixed mode by the
            configured controller
*/
[!/* [cover parentID={1B25D80E-052F-427c-B4EF-8FE9DFDD73B2}]
[/cover] */!][!//
[!IF "$TxMixedStatus = 1"!][!//
  #define CAN_17_MCMCAN_TX_MIXED_PROCESSING                     (STD_ON)
[!ELSE!][!//
  #define CAN_17_MCMCAN_TX_MIXED_PROCESSING                     (STD_OFF)
[!ENDIF!][!//

/* Controller Handle Id */
[!NOCODE!][!//
  [!VAR "ActualCntrlIndex" = "'0'"!][!//
  [!VAR "ControllerConfigMaxTemp" = "num:i(count(./CanController/*))"!][!//
  [!FOR "Cntrlindx" = "0" TO "$ControllerConfigMaxTemp - 1"!][!//
    [!LOOP "./CanController/*"!][!//
      [!IF "CanControllerId = $Cntrlindx"!][!//
        [!IF "CanControllerActivation = 'true'"!][!//
          [!VAR "Text" = "node:name(.)"!][!//
          [!CODE!][!//

            [!/* [cover parentID={7BB086C8-4A6D-488b-9D5B-737BCF061C39}]
            [/cover] */!][!//
            /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
              in generated code due to Autosar Naming constraints.*/
            #define Can_17_McmCanConf_CanController_[!"$Text"!]             [!"$ActualCntrlIndex"!]
          [!ENDCODE!][!//
          [!VAR "ActualCntrlIndex" = "num:i($ActualCntrlIndex+1)"!][!//
        [!ENDIF!]
      [!ENDIF!]
    [!ENDLOOP!]
  [!ENDFOR!]
[!ENDNOCODE!][!//

/* Hardware object Handle Id */
[!NOCODE!][!//
[!VAR "ActualHwIndex" = "'0'"!][!//
[!VAR "HwObjConfigMaxTemp" = "num:i(count(./CanHardwareObject/*))"!][!//
[!FOR "HwObjindx" = "0" TO "$HwObjConfigMaxTemp - 1"!][!//
  [!LOOP "./CanHardwareObject/*"!][!//
    [!IF "CanObjectId  = $HwObjindx"!][!//
      [!IF "(node:ref(CanControllerRef)/CanControllerActivation = 'true')"!][!//
        [!VAR "Text" = "node:name(.)"!][!//
        [!CODE!][!//

          [!/* [cover parentID={872AF529-27F3-43ce-AC9F-7F80AAE00986}]
          [/cover] */!][!//
          /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
            in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
            in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
            in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
            in generated code due to Autosar Naming constraints.*/
          #define Can_17_McmCanConf_CanHardwareObject_[!"$Text"!]         [!"$ActualHwIndex"!]
        [!ENDCODE!][!//
        [!VAR "ActualHwIndex" = "num:i($ActualHwIndex+1)"!][!//
      [!ENDIF!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDFOR!]
[!ENDNOCODE!][!//

[!IF "../CanGeneral/CanPublicIcomSupport = 'true'"!][!//
  [!/* [cover parentID={BFFABD14-242B-462a-B5FF-34AEAB12AFDE}]
  [/cover] */!][!//
  /* ICOM Configuration Id */
  #define Can_17_McmCanConf_CanIcomConfigIndex_Deactivate            0
  [!VAR "IcomMax" = "num:i(count(./CanIcom/./*[1]/CanIcomConfig/*))"!][!//
  [!FOR "Icomindx" = "1" TO "$IcomMax"!][!//
    [!LOOP "./CanIcom/./*[1]/CanIcomConfig/*"!][!//
      [!IF "CanIcomConfigId  = $Icomindx"!][!//
        [!VAR "Text" = "node:name(.)"!][!//

        [!/* [cover parentID={59C8AF3D-8FD7-4779-A91E-372D9DFA41ED}]
        [/cover] */!][!//
        /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
          in generated code due to Autosar Naming constraints.*/
        /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
          in generated code due to Autosar Naming constraints.*/
        /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
          in generated code due to Autosar Naming constraints.*/
        /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
          in generated code due to Autosar Naming constraints.*/
        #define Can_17_McmCanConf_CanIcomConfigIndex_[!"$Text"!]         [!"$Icomindx"!]
      [!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ENDFOR!][!//
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
[!VAR "HwObjMaxIndx" = "num:i(count(../CanGeneral/CanMainFunctionRWPeriods/*))"!][!//
[!IF "$HwObjMaxIndx>1"!][!//
  [!IF "$MultiTxPeriod = num:i(1)"!]
    /*******************************************************************************
    **  Can_MainFunction_Write Function Declarations with multipleperiod support  **
    *******************************************************************************/
    [!FOR "HwObjindx" = "0" TO "$HwObjMaxIndx - 1"!][!//

      [!/* [cover parentID={6C243DDF-2B43-4af4-81C0-D104AE3634B6}]
      [/cover] */!][!//
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      extern void Can_17_McmCan_MainFunction_Write_[!"$HwObjindx"!](void);
    [!ENDFOR!][!//
  [!ENDIF!][!//
[!ENDIF!][!//

[!VAR "HwObjMaxIndx" = "num:i(count(../CanGeneral/CanMainFunctionRWPeriods/*))"!][!//
[!IF "$HwObjMaxIndx>1"!][!//
  [!IF "$MultiRxPeriod = num:i(1)"!]
    /*******************************************************************************
    **  Can_MainFunction_Read Function Declarations with multipleperiod support  **
    *******************************************************************************/
    [!FOR "HwObjindx" = "0" TO "$HwObjMaxIndx - 1"!][!//

      [!/* [cover parentID={D6383A7F-FBB5-4550-B179-C83DF72F254D}]
      [/cover] */!][!//
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
        in generated code due to Autosar Naming constraints.*/
      extern void Can_17_McmCan_MainFunction_Read_[!"$HwObjindx"!](void);
    [!ENDFOR!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/
[!ENDSELECT!]
[!ENDINDENT!]
#endif  /* CAN_17_MCMCAN_CFG_H */