[!AUTOSPACING!]
[!INDENT "0"!]
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
**  FILENAME  : Spi_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 17.0.0                                                        **
**                                                                            **
**  DATE      : 2023-05-20                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Spi.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={289F3F4C-42DB-49dc-928A-815998D1FCF8}]    **
**                                                                            **
**  DESCRIPTION  : Code template header file for Spi Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Spi Driver, AUTOSAR Release 4.2.2     **
**                     Specification of Spi Driver, AUTOSAR Release 4.4.0     **
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
**  FILENAME  : Spi_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 17.0.0                                                        **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]  !!!IGNORE-LINE!!!                   **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]       !!!IGNORE-LINE!!!                  **
**                                                                            **
**  BSW MODULE DECRIPTION : Spi.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Spi configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Spi Driver, AUTOSAR Release 4.2.2     **
**                     Specification of Spi Driver, AUTOSAR Release 4.4.0     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
[!AUTOSPACING!]
[!NOCODE!]
[!INCLUDE "..\Spi_checks.m"!]
[!ENDNOCODE!]
/* To avoid multiple inclusion of the header file more than once */
#ifndef SPI_CFG_H
#define SPI_CFG_H
[!NOCODE!]
[!VAR "Spi_MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
[!VAR "Spi_MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
[!VAR "Spi_RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
[!VAR "Spi_NewString" = "text:replaceAll($moduleReleaseVer,"\.",'')"!]

[!VAR "SpiAS422Enable" = "num:i(0)"!]

[!IF "$Spi_MinorVersion = num:i(2)"!][!//
  [!IF "$Spi_RevisionVersion = num:i(2)"!][!//
    [!VAR "SpiAS422Enable" = "num:i(1)"!]
  [!ENDIF!]
[!ENDIF!]
[!ENDNOCODE!]
[!IF "$SpiAS422Enable = num:i(1)"!]
[!// [cover parentID={93E71B93-4895-46af-A75B-1A49D52040F1}][/cover][!//
[!IF "node:exists(./SpiGeneral/SpiUserCallbackHeaderFile/*[1])"!]
  #include "[!"./SpiGeneral/SpiUserCallbackHeaderFile/*[1]"!]"
/**/
[!ENDIF!]
[!ENDIF!]

/* Section to Generate Autosar Specific Version Information */
[!/* [cover parentID={BD18627D-3BF7-4713-8C4B-4A108D050A16}]SPI_AR_RELEASE_MAJOR_VERSION[/cover] */!][!//
#define SPI_AR_RELEASE_MAJOR_VERSION          ([!"$Spi_MajorVersion"!]U)
[!/* [cover parentID={452C3548-A225-4a82-A296-454894FCEFA6}]SPI_AR_RELEASE_MINOR_VERSION[/cover] */!][!//
#define SPI_AR_RELEASE_MINOR_VERSION          ([!"$Spi_MinorVersion"!]U)
[!/* [cover parentID={ED2AB037-6027-42e5-BCD0-E18BABD46AE7}]SPI_AR_RELEASE_REVISION_VERSION[/cover] */!][!//
#define SPI_AR_RELEASE_REVISION_VERSION       ([!"$Spi_RevisionVersion"!]U)
[!VAR "Spi_MaxCore" = "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!]
[!//getting core ID
[!CALL "Spi_CGGenerateModuleMap", "Module" = "'SPI'"!]
[!CALL "Spi_CGGetCore"!]
/* Section to Generate Vendor Specific Version Information */
/* Vendor specific implementation version information      */
[!VAR "Spi_SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
[!VAR "Spi_SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
[!VAR "Spi_SwRevisionVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
[!/* [cover parentID={A5E86010-0892-424b-81BF-75DBF5B06F4B}]SPI_SW_MAJOR_VERSION[/cover] */!][!//
#define SPI_SW_MAJOR_VERSION                  ([!"$Spi_SwMajorVersion"!]U)
[!/* [cover parentID={26C53F12-EEA9-43F2-9421-064718E56597}]SPI_SW_MINOR_VERSION[/cover] */!][!//
#define SPI_SW_MINOR_VERSION                  ([!"$Spi_SwMinorVersion"!]U)
[!/* [cover parentID={868F31FF-E62F-4015-B686-19F1F6D886CA}]SPI_SW_PATCH_VERSION[/cover] */!][!//
#define SPI_SW_PATCH_VERSION                  ([!"$Spi_SwRevisionVersion"!]U)
[!CALL "Spi_CGGenerateModuleMap", "Module" = "'SPI'"!][!//
[!CALL "Spi_CGGetCore"!][!//
[!CALL "Spi_CGStoreCoreConfig"!][!//
[!CALL "Spi_CGStoreKernelCoreConfig"!][!//
[!//
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Spi')[1]"!]
  [!//
  [!/* Macro call to verify Channel configuration */!][!//
  [!CALL "Spi_CGVerifyChannelConfig"!][!//
  [!//
  [!/* Macro call to verify Job configuration */!][!//
  [!CALL "Spi_CGVerifyJobConfig"!][!//
  [!//
  [!/* Macro call to verify ExternalDevices configuration */!][!//
  [!CALL "Spi_CGVerifyExternalDeviceConfig"!][!//
  [!//
  [!/* Macro call to verify Spi Hw configuration */!][!//
  [!CALL "Spi_CGVerifySpiHwConfig"!][!//
  [!//
  [!/* Macro call to verify Spi Sequence configuration */!][!//
  [!CALL "Spi_CGVerifySequenceConfig"!][!//
  [!//
  [!/* Macro call to verify channel sharing configuration */!][!//
  [!CALL "Spi_CGVerifyChannelSharingConfig"!][!//
  [!//
  [!VAR "SpiMaxUnit" ="node:value(SpiPublishedInformation/SpiMaxHwUnit)"!]
  [!VAR "QspiLastId" = "num:i(text:split(ecu:get('Spi.AvailableQSPIModule'),'QSPI')[num:i($SpiMaxUnit)])"!]
  /* Pre-Compile parameters */
  /* (Development Error)/(Default Error) Trace */
  [!// [cover parentID={DE13BB9B-DBE3-4184-91A8-9FB83723FB76}][/cover][!//
  #define SPI_DEV_ERROR_DETECT                  [!//
  [!IF "SpiGeneral/SpiDevErrorDetect = 'true'"!][!//
    (STD_ON)
  [!ELSE!][!//
    (STD_OFF)
  [!ENDIF!][!//
  /* Runtime Error*/
  [!// [cover parentID={4C2D9237-C686-4DC9-961D-437464EF283F}][/cover][!//
  [!IF "$SpiAS422Enable = num:i(1)"!]
  #define SPI_RUNTIME_ERROR_DETECT (STD_OFF)
  [!ELSE!]
  #define SPI_RUNTIME_ERROR_DETECT                  [!//
  [!IF "SpiGeneral/SpiRunTimeErrorDetect = 'true'"!][!//
    (STD_ON)
  [!ELSE!][!//
    (STD_OFF)
  [!ENDIF!][!//
  [!ENDIF!][!//
  [!// [cover parentID={59A724A7-B2F2-412b-B6EC-302F4B6A0EFC}] Safety ON / OFF [/cover][!//
  [!// [cover parentID={3D2FF4DE-A42C-4ba6-BA6F-7E533C040AE1}][/cover][!//
  /* Safety error check */
  #define SPI_SAFETY_ENABLE                  [!//
  [!IF "SpiGeneral/SpiSafetyEnable = 'true'"!][!//
    (STD_ON)
  [!ELSE!][!//
    (STD_OFF)
  [!ENDIF!][!//
  /* Production Error reporting  macros */
  #define SPI_DEM_REPORT_DISABLED               (0U)
  #define SPI_DEM_REPORT_ENABLED                (1U)
  /* Production Error Related Macros */
  [!IF "node:exists(SpiDemEventParameterRefs/*[1])"!][!//
    [!IF "node:refexists(SpiDemEventParameterRefs/*[1]/SPI_E_HARDWARE_ERROR/*[1])"!][!//
      [!// [cover parentID={DEC591FF-01EA-4c05-951B-BBCA0984B506}][/cover][!//
      #define SPI_HW_ERROR_DEM_REPORT               (SPI_DEM_REPORT_ENABLED)
      [!/* [cover parentID={586FE60E-4FBE-4190-9069-089AA4B428E4}]SPI_E_HARDWARE_ERROR[/cover] */!][!//
      #define SPI_E_HARDWARE_ERROR                  ((Dem_EventIdType)DemConf_DemEventParameter_[!"node:name(node:ref(node:value(SpiDemEventParameterRefs/*[1]/SPI_E_HARDWARE_ERROR/*[1])))"!])
    [!ELSE!][!//
      #define SPI_HW_ERROR_DEM_REPORT               (SPI_DEM_REPORT_DISABLED)
    [!ENDIF!][!//
  [!ELSE!][!//
    #define SPI_HW_ERROR_DEM_REPORT               (SPI_DEM_REPORT_DISABLED)
  [!ENDIF!][!//
  /* Kind of transmission available,
  0 - Only Synchronous Transmission
  1 - Only Asynchronous Transmission(Interrupt mode only)
  2 - Both Sync and Async(Both Interrupt and Polling Mode) Transmission */
  [!// [cover parentID={09FB0A4C-CF01-484d-ABBD-918214D89A8C}][/cover][!//
  #define SPI_LEVEL_DELIVERED                   [!//
  ([!"node:value(SpiGeneral/SpiLevelDelivered)"!]U)
  [!IF "num:i(SpiGeneral/SpiLevelDelivered) = num:i(2)"!]
    /* Main function period - Used by application to poll the SPI Hw module */
    [!//[cover parentID={6679837F-5435-47b7-A19B-AE681A3122B1}][/cover][!//
    #define SPI_MAIN_FUNCTION_PERIOD              [!//
    [!IF "node:exists(SpiGeneral/SpiMainFunctionPeriod/*[1])"!]
      ([!"node:value(SpiGeneral/SpiMainFunctionPeriod/*[1])"!]U)
    [!ELSE!][!//
      (0U)
    [!ENDIF!]
  [!ENDIF!]
  /* Kind of Channele buffers allowed
  0 - Only Internal buffers allowed
  1 - Only External buffers allowed
  2 - Both Internal and External buffers allowed */
  [!// [cover parentID={1E38081C-1BE1-4429-A615-345BBC6AB5C1}][/cover][!//
  #define SPI_CHANNEL_BUFFERS_ALLOWED           [!//
  ([!"node:value(SpiGeneral/SpiChannelBuffersAllowed)"!]U)
  /* Specifies if the API Spi_Cancel() is available */
  [!// [cover parentID={0B3037DE-22C1-4c08-93D5-872E9B2805B6}][/cover][!//
  #define SPI_CANCEL_API                        [!//
  [!IF "SpiGeneral/SpiCancelApi = 'true'"!][!//
    (STD_ON)
  [!ELSE!][!//
    (STD_OFF)
  [!ENDIF!][!//
  /* Specifies if the API Spi_GetHWUnitStatus() is available */
  [!//[cover parentID={485EFE77-DC74-41f7-9B08-94DAE697961A}][/cover][!//
  #define SPI_HW_STATUS_API                     [!//
  [!IF "SpiGeneral/SpiHwStatusApi = 'true'"!][!//
    (STD_ON)
  [!ELSE!][!//
    (STD_OFF)
  [!ENDIF!][!//
  /* Specifies if the API Spi_ControlLoopBack() is available */
  [!/* [cover parentID={1B0E99D7-B92C-4796-837D-992FD5051C32}][/cover] */!][!//
  #define SPI_CONTROL_LOOPBACK_API                     [!//
  [!IF "SpiGeneral/SpiEnableLoopBackApi = 'true'"!][!//
    (STD_ON)
  [!ELSE!][!//
    (STD_OFF)
  [!ENDIF!][!//
  /* Specifies if the API Spi_GetVersionInfo() is available */
  [!//[cover parentID={F4D10739-7F23-41b1-BAD3-AF408C406440}][/cover][!//
  #define SPI_VERSION_INFO_API                  [!//
  [!IF "SpiGeneral/SpiVersionInfoApi = 'true'"!][!//
    (STD_ON)
  [!ELSE!][!//
    (STD_OFF)
  [!ENDIF!][!//
  /* Specifies if Sequences can be interrupted during
  transmission. For Level = 0, its value is STD_OFF by default */
  [!// [cover parentID={02F3FD03-15BF-4312-8F88-BFAD03F19D14}][/cover][!//
  #define SPI_INTERRUPTIBLE_SEQ_ALLOWED         [!//
  [!IF "(SpiGeneral/SpiLevelDelivered != num:i(0)) and (SpiGeneral/SpiInterruptibleSeqAllowed = 'true')"!][!//
    (STD_ON)
  [!ELSE!][!//
    (STD_OFF)
  [!ENDIF!][!//
  /* Configuration Options:
  SPI Sequence Interruptible Options */
  #define SPI_SEQ_INT_FALSE                     ((uint8)0U)
  #define SPI_SEQ_INT_TRUE                      ((uint8)1U)
  /* Specifies if concurrent transmission of synchronous
  sequences are allowed. For Level = 1, its value is STD_OFF by default */
  [!// [cover parentID={F3A871BC-8156-404f-BF25-485D30047CDA}][/cover][!//
  #define SPI_SUPPORT_CONCURRENT_SYNC_TRANSMIT  [!//
  [!IF "(SpiGeneral/SpiLevelDelivered != num:i(1)) and (SpiGeneral/SpiSupportConcurrentSyncTransmit = 'true')"!][!//
    (STD_ON)
  [!ELSE!][!//
    (STD_OFF)
  [!ENDIF!][!//
  /* Maximum QSPI Hw units available */
  [!//[cover parentID={6920B79A-63B8-47ee-B6DC-70657ABC2213}][/cover][!//
  #define SPI_MAX_HW_UNIT                       [!//
  ([!"(num:i(($QspiLastId) + 1))"!]U)
  #define SPI_SYNC_BUS                          (0U)
  #define SPI_ASYNC_BUS                         (1U)
  [!CALL "Spi_CGVerifySpiHwConfig"!][!//
  [!/* [cover parentID={842B884F-0FD1-4619-BDEC-F74D01B6A338}]SPI_HW_QSPIx_USED[/cover] */!][!//
  [!/* [cover parentID={6DF5084B-B2D4-488c-9267-C110CFCA2C78}]SPI_QSPIx_HWTYPE[/cover] */!][!//
  [!CALL "Spi_CGIsQSPIzUsed"!][!//
  /* Is QSPI0 Used */
  #define SPI_HW_QSPI0_USED                     [!//
  [!IF "$Spi_MacQspi0Used = num:i(1)"!][!//
    (STD_ON)
  [!ELSE!][!//
    (STD_OFF)
  [!ENDIF!][!//
  [!IF "$Spi_MacQspi0Used = num:i(1)"!]
    /* Index for QSPI0 module */
    #define SPI_QSPI0_INDEX                       (0U)
    /* Sync/Async */
    #define SPI_QSPI0_HWTYPE                      [!//
    [!IF "$SpiAS422Enable = num:i(1)"!]
      [!IF "$Spi_MacQspi0HwType = num:i(1)"!][!//
        (SPI_ASYNC_BUS)
      [!ELSE!][!//
        (SPI_SYNC_BUS)
      [!ENDIF!][!//
    [!ELSE!]
      [!IF "$Spi_MacQspi0HwType440 = num:i(1)"!][!//
        (SPI_ASYNC_BUS)
      [!ELSE!][!//
        (SPI_SYNC_BUS)
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDIF!]
  [!IF "$QspiLastId > num:i(0)"!]
    /* Is QSPI1 Used */
    #define SPI_HW_QSPI1_USED                     [!//
    [!IF "$Spi_MacQspi1Used = num:i(1)"!][!//
      (STD_ON)
    [!ELSE!][!//
      (STD_OFF)
    [!ENDIF!][!//
    [!IF "$Spi_MacQspi1Used = num:i(1)"!]
      /* Index for QSPI1module */
      #define SPI_QSPI1_INDEX                       (1U)
      /* Sync/Async */
      #define SPI_QSPI1_HWTYPE                      [!//
      [!IF "$SpiAS422Enable = num:i(1)"!]
          [!IF "$Spi_MacQspi1HwType = num:i(1)"!][!//
          (SPI_ASYNC_BUS)
        [!ELSE!][!//
          (SPI_SYNC_BUS)
        [!ENDIF!][!//
      [!ELSE!]
        [!IF "$Spi_MacQspi1HwType440 = num:i(1)"!][!//
          (SPI_ASYNC_BUS)
        [!ELSE!][!//
          (SPI_SYNC_BUS)
       [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDIF!]
  [!ENDIF!]
  [!IF "$QspiLastId > num:i(1)"!]
    /* Is QSPI2 Used */
    #define SPI_HW_QSPI2_USED                     [!//
    [!IF "$Spi_MacQspi2Used = num:i(1)"!][!//
      (STD_ON)
    [!ELSE!][!//
      (STD_OFF)
    [!ENDIF!][!//
    [!IF "$Spi_MacQspi2Used = num:i(1)"!]
      /* Index for QSPI2 module */
      #define SPI_QSPI2_INDEX                       (2U)
      /* Sync/Async */
      #define SPI_QSPI2_HWTYPE                      [!//
      [!IF "$SpiAS422Enable = num:i(1)"!]
        [!IF "$Spi_MacQspi2HwType = num:i(1)"!][!//
          (SPI_ASYNC_BUS)
        [!ELSE!][!//
          (SPI_SYNC_BUS)
        [!ENDIF!][!//
      [!ELSE!]
      [!IF "$Spi_MacQspi2HwType440 = num:i(1)"!][!//
          (SPI_ASYNC_BUS)
        [!ELSE!][!//
          (SPI_SYNC_BUS)
       [!ENDIF!][!//
    [!ENDIF!][!//
    [!ENDIF!]
  [!ENDIF!][!//
  [!IF "$QspiLastId > num:i(2)"!]
    /* Is QSPI3 Used */
    #define SPI_HW_QSPI3_USED                     [!//
    [!IF "$Spi_MacQspi3Used = num:i(1)"!][!//
      (STD_ON)
    [!ELSE!][!//
      (STD_OFF)
    [!ENDIF!][!//
    [!IF "$Spi_MacQspi3Used = num:i(1)"!]
      /* Index for QSPI3 module */
      #define SPI_QSPI3_INDEX                       (3U)
      /* Sync/Async */
      #define SPI_QSPI3_HWTYPE                      [!//
      [!IF "$SpiAS422Enable = num:i(1)"!]
        [!IF "$Spi_MacQspi3HwType = num:i(1)"!][!//
          (SPI_ASYNC_BUS)
        [!ELSE!][!//
          (SPI_SYNC_BUS)
        [!ENDIF!][!//
      [!ELSE!]
      [!IF "$Spi_MacQspi3HwType440 = num:i(1)"!][!//
          (SPI_ASYNC_BUS)
        [!ELSE!][!//
          (SPI_SYNC_BUS)
       [!ENDIF!][!//
    [!ENDIF!][!//
    [!ENDIF!]
  [!ENDIF!][!//
  [!IF "$QspiLastId > num:i(3)"!]
    /* Is QSPI4 Used */
    #define SPI_HW_QSPI4_USED                     [!//
    [!IF "$Spi_MacQspi4Used = num:i(1)"!][!//
      (STD_ON)
    [!ELSE!][!//
      (STD_OFF)
    [!ENDIF!][!//
    [!IF "$Spi_MacQspi4Used = num:i(1)"!]
      /* Index for QSPI4 module */
      #define SPI_QSPI4_INDEX                       (4U)
      /* Sync/Async */
      #define SPI_QSPI4_HWTYPE                      [!//
      [!IF "$SpiAS422Enable = num:i(1)"!]
        [!IF "$Spi_MacQspi4HwType = num:i(1)"!][!//
          (SPI_ASYNC_BUS)
        [!ELSE!][!//
          (SPI_SYNC_BUS)
        [!ENDIF!][!//
      [!ELSE!]
      [!IF "$Spi_MacQspi4HwType440 = num:i(1)"!][!//
          (SPI_ASYNC_BUS)
        [!ELSE!][!//
          (SPI_SYNC_BUS)
       [!ENDIF!][!//
    [!ENDIF!][!//
    [!ENDIF!]
  [!ENDIF!][!//
  [!IF "$QspiLastId > num:i(4)"!]
    /* Is QSPI5 Used */
    #define SPI_HW_QSPI5_USED                     [!//
    [!IF "$Spi_MacQspi5Used = num:i(1)"!][!//
      (STD_ON)
    [!ELSE!][!//
      (STD_OFF)
    [!ENDIF!][!//
    [!IF "$Spi_MacQspi5Used = num:i(1)"!]
      /* Index for QSPI5 module */
      #define SPI_QSPI5_INDEX                       (5U)
      /* Sync/Async */
      #define SPI_QSPI5_HWTYPE                      [!//
      [!IF "$SpiAS422Enable = num:i(1)"!]
        [!IF "$Spi_MacQspi5HwType = num:i(1)"!][!//
          (SPI_ASYNC_BUS)
        [!ELSE!][!//
          (SPI_SYNC_BUS)
        [!ENDIF!][!//
      [!ELSE!]
      [!IF "$Spi_MacQspi5HwType440 = num:i(1)"!][!//
          (SPI_ASYNC_BUS)
        [!ELSE!][!//
          (SPI_SYNC_BUS)
       [!ENDIF!][!//
    [!ENDIF!][!//
    [!ENDIF!]
  [!ENDIF!][!//
  /* Timeout value to wait for trail delay to be completed.
  Should be atleast greater than the Trail delay
  (also to avoid possible infinite loops) */
  #define SPI_DELAY_TIMEOUT                     (0xFFFFFFFEU)
  /* SPI Module is enabled,
  Module does not enter sleep mode upon sleep request */
  #define SPI_CLK_SLEEP_DISABLE                 (0x00000008U)
  /* SPI Module is enabled,
  Module enters sleep mode upon sleep request         */
  #define SPI_CLK_SLEEP_ENABLE                  (0x00000000U)
  /* Job Delimiter, marks end of Job */
  #define SPI_JOB_DELIMITER                     ((uint16)0xFFFFU)
  /* Sequence Delimiter, marks end of Sequence */
  #define SPI_SEQUENCE_DELIMITER                ((uint8)0xFFU)
  /* Channel Delimiter, marks the end of channel */
  #define SPI_CHANNEL_DELIMITER                 ((uint8)0xFFU)
  /* QSPI HW Delimiter, marks the end of QSPI module */
  #define SPI_QSPI_HW_DELIMITER                 ((uint8)0xFFU)

  [!VAR "Spi_MacMaxIBASize0" = "num:i(0)"!]
  [!VAR "Spi_MacMaxIBASize1" = "num:i(0)"!]
  [!VAR "Spi_MacMaxIBASize2" = "num:i(0)"!]
  [!VAR "Spi_MacMaxIBASize3" = "num:i(0)"!]
  [!VAR "Spi_MacMaxIBASize4" = "num:i(0)"!]
  [!VAR "Spi_MacMaxIBASize5" = "num:i(0)"!]
  [!VAR "Spi_MasterChnllstNum" = "''"!]
  [!IF "$Spi_MacQspi0Used = num:i(1)"!]
      [!CALL "Spi_CGCalculateIBSizeQSPIz","Spi_OutQspiIndex" = "'QSPI0'"!][!//
      [!VAR "Spi_MacMaxIBASize0" = "$Spi_MacMaxIBSize"!][!//
  [!ENDIF!]
  [!IF "$Spi_MacQspi1Used = num:i(1)"!]
      [!CALL "Spi_CGCalculateIBSizeQSPIz","Spi_OutQspiIndex" = "'QSPI1'"!][!//
      [!VAR "Spi_MacMaxIBASize1" = "$Spi_MacMaxIBSize"!]
  [!ENDIF!]
  [!IF "$Spi_MacQspi2Used = num:i(1)"!]
      [!CALL "Spi_CGCalculateIBSizeQSPIz","Spi_OutQspiIndex" = "'QSPI2'"!][!//
      [!VAR "Spi_MacMaxIBASize2" = "$Spi_MacMaxIBSize"!][!//
  [!ENDIF!]
  [!IF "$Spi_MacQspi3Used = num:i(1)"!]
      [!CALL "Spi_CGCalculateIBSizeQSPIz","Spi_OutQspiIndex" = "'QSPI3'"!][!//
      [!VAR "Spi_MacMaxIBASize3" = "$Spi_MacMaxIBSize"!][!//
  [!ENDIF!]
  [!IF "$Spi_MacQspi4Used = num:i(1)"!]
      [!CALL "Spi_CGCalculateIBSizeQSPIz","Spi_OutQspiIndex" = "'QSPI4'"!][!//
      [!VAR "Spi_MacMaxIBASize4" = "$Spi_MacMaxIBSize"!][!//
  [!ENDIF!]
  [!IF "$Spi_MacQspi5Used = num:i(1)"!]
      [!CALL "Spi_CGCalculateIBSizeQSPIz","Spi_OutQspiIndex" = "'QSPI5'"!][!//
      [!VAR "Spi_MacMaxIBASize5" = "$Spi_MacMaxIBSize"!][!//
  [!ENDIF!]
  [!/* [cover parentID={ECCAD1EB-7342-4261-86A5-E6AB7A347A6F}][/cover] */!][!//
  [!CALL "Spi_CGStoreCoreConfig"!][!//
  [!CALL "Spi_CGStoreKernelCoreConfig"!]
  [!FOR "CPU_ID" = "0" TO "num:i($Spi_MaxCore)"!][!//
    [!IF "text:split($Core_config,',')[position() = $CPU_ID + num:i(1)] = num:i(1)"!]
      [!NOCODE!]
      [!VAR "TotalIBSize"="num:i(0)"!]
      [!IF "text:split($QSPICore_config,',')[position() = num:i(1)] = $CPU_ID"!]
        [!VAR "TotalIBSize"="$TotalIBSize + $Spi_MacMaxIBASize0"!]
      [!ENDIF!]
      [!IF "text:split($QSPICore_config,',')[position() = num:i(2)] = $CPU_ID"!]
        [!VAR "TotalIBSize"="$TotalIBSize + $Spi_MacMaxIBASize1"!]
      [!ENDIF!]
      [!IF "text:split($QSPICore_config,',')[position() = num:i(3)] = $CPU_ID"!]
        [!VAR "TotalIBSize"="$TotalIBSize + $Spi_MacMaxIBASize2"!]
      [!ENDIF!]
      [!IF "text:split($QSPICore_config,',')[position() = num:i(4)] = $CPU_ID"!]
        [!VAR "TotalIBSize"="$TotalIBSize + $Spi_MacMaxIBASize3"!]
      [!ENDIF!]
      [!IF "text:split($QSPICore_config,',')[position() = num:i(5)] = $CPU_ID"!]
        [!VAR "TotalIBSize"="$TotalIBSize + $Spi_MacMaxIBASize4"!]
      [!ENDIF!]
      [!IF "text:split($QSPICore_config,',')[position() = num:i(6)] = $CPU_ID"!]
        [!VAR "TotalIBSize"="$TotalIBSize + $Spi_MacMaxIBASize5"!]
      [!ENDIF!]
      [!ENDNOCODE!]
      [!IF "$TotalIBSize > num:i(65536)"!]
      [!ERROR!]
         Total IB channels Size per Core should not be greater than 65535.
      [!ENDERROR!]
      [!ENDIF!]
      [!/* [cover parentID={269C414A-2DB0-4339-8398-C9BCDC7986C1}]SPI_ASYNC_IB_BUFFER_SIZE_COREx[/cover] */!][!//
      [!/* [cover parentID={2EDE429C-0FD6-45db-9EFD-B251CB98BE3A}]SPI_IB_BUFFER_SIZE_COREx[/cover] */!][!//
      #define SPI_IB_BUFFER_SIZE_CORE[!"num:i($CPU_ID)"!]           ([!"num:i($TotalIBSize)"!]U)
    [!ENDIF!]
  [!ENDFOR!][!//

    /* Job Queue Length for QSPI1 */
    [!//[cover parentID={A83C287C-C9D4-48c7-9B5B-DC48543827CC}][/cover][!//
    [!//[cover parentID={5B543EE4-F18C-4951-A27F-C33E93AD4EBD}][/cover][!//
    #define SPI_JOB_QUEUE_LENGTH_QSPI0            [!//
    [!IF "node:exists(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = 'QSPI0']/SpiJobQueueLengthQspix)"!]
      ([!"num:i((num:i(node:value(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel =      'QSPI0']/SpiJobQueueLengthQspix))) + num:i(1))"!]U)
    [!ELSE!][!//
      (0U)
    [!ENDIF!]
  [!IF "$QspiLastId > num:i(0)"!]
    /* Job Queue Length for QSPI1 */
    #define SPI_JOB_QUEUE_LENGTH_QSPI1            [!//
    [!IF "node:exists(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = 'QSPI1']/SpiJobQueueLengthQspix)"!]
      ([!"num:i((num:i(node:value(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = 'QSPI1']/SpiJobQueueLengthQspix))) + num:i(1))"!]U)
    [!ELSE!][!//
      (0U)
    [!ENDIF!]
  [!ENDIF!][!//
  [!IF "$QspiLastId > num:i(1)"!]
    /* Job Queue Length for QSPI2 */
    #define SPI_JOB_QUEUE_LENGTH_QSPI2            [!//
    [!IF "node:exists(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = 'QSPI2']/SpiJobQueueLengthQspix)"!]
      ([!"num:i((num:i(node:value(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = 'QSPI2']/SpiJobQueueLengthQspix))) + num:i(1))"!]U)
    [!ELSE!][!//
      (0U)
    [!ENDIF!]
  [!ENDIF!][!//
  [!IF "$QspiLastId > num:i(2)"!]
    /* Job Queue Length for QSPI3 */
    #define SPI_JOB_QUEUE_LENGTH_QSPI3            [!//
    [!IF "node:exists(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = 'QSPI3']/SpiJobQueueLengthQspix)"!]
      ([!"num:i((num:i(node:value(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = 'QSPI3']/SpiJobQueueLengthQspix))) + num:i(1))"!]U)
    [!ELSE!][!//
      (0U)
    [!ENDIF!]
  [!ENDIF!][!//
  [!IF "$QspiLastId > num:i(3)"!]
    /* Job Queue Length for QSPI4 */
    #define SPI_JOB_QUEUE_LENGTH_QSPI4            [!//
    [!IF "node:exists(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = 'QSPI4']/SpiJobQueueLengthQspix)"!]
      ([!"num:i((num:i(node:value(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = 'QSPI4']/SpiJobQueueLengthQspix))) + num:i(1))"!]U)
    [!ELSE!][!//
      (0U)
    [!ENDIF!]
  [!ENDIF!][!//
  [!IF "$QspiLastId > num:i(4)"!]
    /* Job Queue Length for QSPI5 */
    #define SPI_JOB_QUEUE_LENGTH_QSPI5            [!//
    [!IF "node:exists(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = 'QSPI5']/SpiJobQueueLengthQspix)"!]
      ([!"num:i((num:i(node:value(SpiHwConfiguration/*[1]/SpiHwConfigurationQspi/*[SpiHwConfigKernel = 'QSPI5']/SpiJobQueueLengthQspix))) + num:i(1))"!]U)
    [!ELSE!][!//
      (0U)
    [!ENDIF!]
  [!ENDIF!][!//
  /* QSPI Channel Index */
  #define SPI_QSPI_CHANNEL0                     ((uint8)0U)
  #define SPI_QSPI_CHANNEL1                     ((uint8)1U)
  #define SPI_QSPI_CHANNEL2                     ((uint8)2U)
  #define SPI_QSPI_CHANNEL3                     ((uint8)3U)
  #define SPI_QSPI_CHANNEL4                     ((uint8)4U)
  #define SPI_QSPI_CHANNEL5                     ((uint8)5U)
  #define SPI_QSPI_CHANNEL6                     ((uint8)6U)
  #define SPI_QSPI_CHANNEL7                     ((uint8)7U)
  #define SPI_QSPI_CHANNEL8                     ((uint8)8U)
  #define SPI_QSPI_CHANNEL9                     ((uint8)9U)
  #define SPI_QSPI_CHANNEL10                    ((uint8)10U)
  #define SPI_QSPI_CHANNEL11                    ((uint8)11U)
  #define SPI_QSPI_CHANNEL12                    ((uint8)12U)
  #define SPI_QSPI_CHANNEL13                    ((uint8)13U)
  #define SPI_QSPI_CHANNEL14                    ((uint8)14U)
  #define SPI_QSPI_CHANNEL15                    ((uint8)15U)
  [!VAR "Num_IB0"="num:i(0)"!]
  [!VAR "Num_IB1"="num:i(0)"!]
  [!VAR "Num_IB2"="num:i(0)"!]
  [!VAR "Num_IB3"="num:i(0)"!]
  [!VAR "Num_IB4"="num:i(0)"!]
  [!VAR "Num_IB5"="num:i(0)"!]
  /* Number of IB channels on Async Hw */
  [!VAR "Spi_MasterChnlIstNum" = "''"!]
  [!IF "$Spi_MacQspi0Used = num:i(1)"!]
    /*Kernel 0*/
    [!NOCODE!]
    [!VAR "Num_IB0"="num:i(0)"!]
    [!IF "num:i(SpiGeneral/SpiChannelBuffersAllowed) != num:i(1)"!]
        [!LOOP "SpiDriver/SpiChannel/*[SpiChannelType = 'IB']"!]
          [!VAR "temp"="node:name(.)"!]
          [!LOOP "../../SpiJob/*/SpiChannelList/*[node:name(node:ref(./SpiChannelAssignment)) = $temp]"!]
            [!IF "(node:ref(../../SpiDeviceAssignment)/SpiHwUnit = 'QSPI0') and (not(text:contains(text:split($Spi_MasterChnlIstNum,','), $temp)))"!]
              [!VAR "Num_IB0"="$Num_IB0 + num:i(1)"!]
              [!VAR "Spi_MasterChnlIstNum" = "concat($Spi_MasterChnlIstNum,$temp,',')"!]
              [!BREAK!]
            [!ENDIF!]
          [!ENDLOOP!]
        [!ENDLOOP!]
    [!ELSE!]
      [!VAR "Num_IB0"="num:i(0)"!]
    [!ENDIF!]
    [!ENDNOCODE!]
  [!ENDIF!]
  [!IF "$Spi_MacQspi1Used = num:i(1)"!]
    /*Kernel 1*/
    [!NOCODE!]
    [!VAR "Num_IB1"="num:i(0)"!]
    [!IF "num:i(SpiGeneral/SpiChannelBuffersAllowed) != num:i(1)"!]
        [!LOOP "SpiDriver/SpiChannel/*[SpiChannelType = 'IB']"!]
          [!VAR "temp"="node:name(.)"!]
          [!LOOP "../../SpiJob/*/SpiChannelList/*[node:name(node:ref(./SpiChannelAssignment)) = $temp]"!]
            [!IF "(node:ref(../../SpiDeviceAssignment)/SpiHwUnit = 'QSPI1') and (not(text:contains(text:split($Spi_MasterChnlIstNum,','), $temp)))"!]
              [!VAR "Num_IB1"="$Num_IB1 + num:i(1)"!]
              [!VAR "Spi_MasterChnlIstNum" = "concat($Spi_MasterChnlIstNum,$temp,',')"!]
              [!BREAK!]
            [!ENDIF!]
          [!ENDLOOP!]
        [!ENDLOOP!]
    [!ELSE!]
      [!VAR "Num_IB1"="num:i(0)"!]
    [!ENDIF!]
    [!ENDNOCODE!]
  [!ENDIF!]
  [!IF "$Spi_MacQspi2Used = num:i(1)"!]
    /*Kernel 2*/
    [!NOCODE!]
    [!VAR "Num_IB2"="num:i(0)"!]
    [!IF "num:i(SpiGeneral/SpiChannelBuffersAllowed) != num:i(1)"!]
        [!LOOP "SpiDriver/SpiChannel/*[SpiChannelType = 'IB']"!]
          [!VAR "temp"="node:name(.)"!]
          [!LOOP "../../SpiJob/*/SpiChannelList/*[node:name(node:ref(./SpiChannelAssignment)) = $temp]"!]
            [!IF "(node:ref(../../SpiDeviceAssignment)/SpiHwUnit = 'QSPI2') and (not(text:contains(text:split($Spi_MasterChnlIstNum,','), $temp)))"!]
              [!VAR "Num_IB2"="$Num_IB2 + num:i(1)"!]
              [!VAR "Spi_MasterChnlIstNum" = "concat($Spi_MasterChnlIstNum,$temp,',')"!]
              [!BREAK!]
            [!ENDIF!]
          [!ENDLOOP!]
        [!ENDLOOP!]
    [!ELSE!]
      [!VAR "Num_IB2"="num:i(0)"!]
    [!ENDIF!]
    [!ENDNOCODE!]
  [!ENDIF!]
  [!IF "$Spi_MacQspi3Used = num:i(1)"!]
    /*Kernel 3*/
    [!NOCODE!]
    [!VAR "Num_IB3"="num:i(0)"!]
    [!IF "num:i(SpiGeneral/SpiChannelBuffersAllowed) != num:i(1)"!]
        [!LOOP "SpiDriver/SpiChannel/*[SpiChannelType = 'IB']"!]
          [!VAR "temp"="node:name(.)"!]
          [!LOOP "../../SpiJob/*/SpiChannelList/*[node:name(node:ref(./SpiChannelAssignment)) = $temp]"!]
            [!IF "(node:ref(../../SpiDeviceAssignment)/SpiHwUnit = 'QSPI3') and (not(text:contains(text:split($Spi_MasterChnlIstNum,','), $temp)))"!]
              [!VAR "Num_IB3"="$Num_IB3 + num:i(1)"!]
              [!VAR "Spi_MasterChnlIstNum" = "concat($Spi_MasterChnlIstNum,$temp,',')"!]
              [!BREAK!]
            [!ENDIF!]
          [!ENDLOOP!]
        [!ENDLOOP!]
    [!ELSE!]
      [!VAR "Num_IB3"="num:i(0)"!]
    [!ENDIF!]
    [!ENDNOCODE!]
  [!ENDIF!]
  [!IF "$Spi_MacQspi4Used = num:i(1)"!]
    /*Kernel 4*/
    [!NOCODE!]
    [!VAR "Num_IB4"="num:i(0)"!]
    [!IF "num:i(SpiGeneral/SpiChannelBuffersAllowed) != num:i(1)"!]
        [!LOOP "SpiDriver/SpiChannel/*[SpiChannelType = 'IB']"!]
          [!VAR "temp"="node:name(.)"!]
          [!LOOP "../../SpiJob/*/SpiChannelList/*[node:name(node:ref(./SpiChannelAssignment)) = $temp]"!]
            [!IF "(node:ref(../../SpiDeviceAssignment)/SpiHwUnit = 'QSPI4') and (not(text:contains(text:split($Spi_MasterChnlIstNum,','), $temp)))"!]
              [!VAR "Num_IB4"="$Num_IB4 + num:i(1)"!]
              [!VAR "Spi_MasterChnlIstNum" = "concat($Spi_MasterChnlIstNum,$temp,',')"!]
              [!BREAK!]
            [!ENDIF!]
          [!ENDLOOP!]
        [!ENDLOOP!]
    [!ELSE!]
      [!VAR "Num_IB4"="num:i(0)"!]
    [!ENDIF!]
    [!ENDNOCODE!]
  [!ENDIF!]
  [!IF "$Spi_MacQspi5Used = num:i(1)"!]
    /*Kernel 5*/
    [!NOCODE!]
    [!VAR "Num_IB5"="num:i(0)"!]
    [!IF "num:i(SpiGeneral/SpiChannelBuffersAllowed) != num:i(1)"!]
        [!LOOP "SpiDriver/SpiChannel/*[SpiChannelType = 'IB']"!]
          [!VAR "temp"="node:name(.)"!]
          [!LOOP "../../SpiJob/*/SpiChannelList/*[node:name(node:ref(./SpiChannelAssignment)) = $temp]"!]
            [!IF "(node:ref(../../SpiDeviceAssignment)/SpiHwUnit = 'QSPI5') and (not(text:contains(text:split($Spi_MasterChnlIstNum,','), $temp)))"!]
              [!VAR "Num_IB5"="$Num_IB5 + num:i(1)"!]
              [!VAR "Spi_MasterChnlIstNum" = "concat($Spi_MasterChnlIstNum,$temp,',')"!]
              [!BREAK!]
            [!ENDIF!]
          [!ENDLOOP!]
        [!ENDLOOP!]
    [!ELSE!]
      [!VAR "Num_IB5"="num:i(0)"!]
    [!ENDIF!]
    [!ENDNOCODE!]
  [!ENDIF!]

  [!CALL "Spi_CGStoreCoreConfig"!][!//
  [!CALL "Spi_CGStoreKernelCoreConfig"!]
  [!FOR "CPU_ID" = "0" TO "num:i($Spi_MaxCore)"!][!//
    [!IF "text:split($Core_config,',')[position() = $CPU_ID + num:i(1)] = num:i(1)"!]
      [!NOCODE!]
      [!VAR "TotalIBPerCore"="num:i(0)"!]
      [!IF "text:split($QSPICore_config,',')[position() = num:i(1)] = $CPU_ID"!]
        [!VAR "TotalIBPerCore"="$TotalIBPerCore + $Num_IB0"!]
      [!ENDIF!]
      [!IF "text:split($QSPICore_config,',')[position() = num:i(2)] = $CPU_ID"!]
        [!VAR "TotalIBPerCore"="$TotalIBPerCore + $Num_IB1"!]
      [!ENDIF!]
      [!IF "text:split($QSPICore_config,',')[position() = num:i(3)] = $CPU_ID"!]
        [!VAR "TotalIBPerCore"="$TotalIBPerCore + $Num_IB2"!]
      [!ENDIF!]
      [!IF "text:split($QSPICore_config,',')[position() = num:i(4)] = $CPU_ID"!]
        [!VAR "TotalIBPerCore"="$TotalIBPerCore + $Num_IB3"!]
      [!ENDIF!]
      [!IF "text:split($QSPICore_config,',')[position() = num:i(5)] = $CPU_ID"!]
        [!VAR "TotalIBPerCore"="$TotalIBPerCore + $Num_IB4"!]
      [!ENDIF!]
      [!IF "text:split($QSPICore_config,',')[position() = num:i(6)] = $CPU_ID"!]
        [!VAR "TotalIBPerCore"="$TotalIBPerCore + $Num_IB5"!]
      [!ENDIF!]
      [!ENDNOCODE!]
      [!//[cover parentID={89D0EB06-9CEF-4feb-A741-C7F4038E9558}][/cover][!//
      #define SPI_NUM_IB_CHANNELS_CORE[!"num:i($CPU_ID)"!]            ([!"num:i($TotalIBPerCore)"!]U)
    [!ENDIF!]
  [!ENDFOR!][!//

  [!//[cover parentID={77F90031-7F7E-4F64-B69D-21B0DFCD6B56}][/cover][!//
  [!CALL "Spi_CGStoreCoreConfig"!][!//
  [!FOR "CPU_ID" = "0" TO "num:i($Spi_MaxCore)"!][!//
    [!IF "text:split($Core_config,',')[position() = $CPU_ID + num:i(1)] = num:i(1)"!][!//
      #define SPI_CORE[!"num:i($CPU_ID)"!]_ENABLE     STD_ON
    [!ELSE!][!//
      #define SPI_CORE[!"num:i($CPU_ID)"!]_ENABLE     STD_OFF
    [!ENDIF!][!//
  [!ENDFOR!][!//

  [!VAR "Total_ch0"="num:i(0)"!]
  [!VAR "Total_ch1"="num:i(0)"!]
  [!VAR "Total_ch2"="num:i(0)"!]
  [!VAR "Total_ch3"="num:i(0)"!]
  [!VAR "Total_ch4"="num:i(0)"!]
  [!VAR "Total_ch5"="num:i(0)"!]
  /* Number of EB channels */
  [!IF "$Spi_MacQspi0Used = num:i(1)"!]
    /*kernel 0*/
    [!NOCODE!]
    [!VAR "Total_ch0"="num:i(0)"!]
    [!LOOP "SpiDriver/SpiChannel/*[SpiChannelType = 'EB']"!]
      [!VAR "temp"="node:name(.)"!]
      [!LOOP "../../SpiJob/*/SpiChannelList/*[node:name(node:ref(./SpiChannelAssignment)) = $temp]"!]
        [!IF "(node:ref(../../SpiDeviceAssignment)/SpiHwUnit = 'QSPI0') and (not(text:contains(text:split($Spi_MasterChnlIstNum,','), $temp)))"!]
          [!VAR "Total_ch0"="$Total_ch0 + num:i(1)"!]
          [!VAR "Spi_MasterChnlIstNum" = "concat($Spi_MasterChnlIstNum,$temp,',')"!]
          [!BREAK!]
        [!ENDIF!]
      [!ENDLOOP!]
    [!ENDLOOP!]
    [!ENDNOCODE!]
  [!ENDIF!]
  [!IF "$Spi_MacQspi1Used = num:i(1)"!]
    /*kernel 1*/
    [!NOCODE!]
    [!VAR "Total_ch1"="num:i(0)"!]
    [!LOOP "SpiDriver/SpiChannel/*[SpiChannelType = 'EB']"!]
      [!VAR "temp"="node:name(.)"!]
      [!LOOP "../../SpiJob/*/SpiChannelList/*[node:name(node:ref(./SpiChannelAssignment)) = $temp]"!]
        [!IF "(node:ref(../../SpiDeviceAssignment)/SpiHwUnit = 'QSPI1') and (not(text:contains(text:split($Spi_MasterChnlIstNum,','), $temp)))"!]
          [!VAR "Spi_MasterChnlIstNum" = "concat($Spi_MasterChnlIstNum,$temp,',')"!]
          [!VAR "Total_ch1"="$Total_ch1 + num:i(1)"!]
          [!BREAK!]
        [!ENDIF!]
      [!ENDLOOP!]
    [!ENDLOOP!]
    [!ENDNOCODE!]
  [!ENDIF!]
  [!IF "$Spi_MacQspi2Used = num:i(1)"!]
    /*Kernel 2*/
    [!NOCODE!]
    [!VAR "Total_ch2"="num:i(0)"!]
    [!LOOP "SpiDriver/SpiChannel/*[SpiChannelType = 'EB']"!]
      [!VAR "temp"="node:name(.)"!]
      [!LOOP "../../SpiJob/*/SpiChannelList/*[node:name(node:ref(./SpiChannelAssignment)) = $temp]"!]
        [!IF "(node:ref(../../SpiDeviceAssignment)/SpiHwUnit = 'QSPI2') and (not(text:contains(text:split($Spi_MasterChnlIstNum,','), $temp)))"!]
          [!VAR "Total_ch2"="$Total_ch2 + num:i(1)"!]
          [!VAR "Spi_MasterChnlIstNum" = "concat($Spi_MasterChnlIstNum,$temp,',')"!]
          [!BREAK!]
        [!ENDIF!]
      [!ENDLOOP!]
    [!ENDLOOP!]
    [!ENDNOCODE!]
  [!ENDIF!]
  [!IF "$Spi_MacQspi3Used = num:i(1)"!]
    /*Kernel 3*/
    [!NOCODE!]
    [!VAR "Total_ch3"="num:i(0)"!]
    [!LOOP "SpiDriver/SpiChannel/*[SpiChannelType = 'EB']"!]
      [!VAR "temp"="node:name(.)"!]
      [!LOOP "../../SpiJob/*/SpiChannelList/*[node:name(node:ref(./SpiChannelAssignment)) = $temp]"!]
        [!IF "(node:ref(../../SpiDeviceAssignment)/SpiHwUnit = 'QSPI3') and (not(text:contains(text:split($Spi_MasterChnlIstNum,','), $temp)))"!]
          [!VAR "Total_ch3"="$Total_ch3 + num:i(1)"!]
          [!VAR "Spi_MasterChnlIstNum" = "concat($Spi_MasterChnlIstNum,$temp,',')"!]
          [!BREAK!]
        [!ENDIF!]
      [!ENDLOOP!]
    [!ENDLOOP!]
    [!ENDNOCODE!]
  [!ENDIF!]
  [!IF "$Spi_MacQspi4Used = num:i(1)"!]
    /*Kernel 4*/
    [!NOCODE!]
    [!VAR "Total_ch4"="num:i(0)"!]
    [!LOOP "SpiDriver/SpiChannel/*[SpiChannelType = 'EB']"!]
      [!VAR "temp"="node:name(.)"!]
      [!LOOP "../../SpiJob/*/SpiChannelList/*[node:name(node:ref(./SpiChannelAssignment)) = $temp]"!]
        [!IF "(node:ref(../../SpiDeviceAssignment)/SpiHwUnit = 'QSPI4') and (not(text:contains(text:split($Spi_MasterChnlIstNum,','), $temp)))"!]
          [!VAR "Total_ch4"="$Total_ch4 + num:i(1)"!]
          [!VAR "Spi_MasterChnlIstNum" = "concat($Spi_MasterChnlIstNum,$temp,',')"!]
          [!BREAK!]
        [!ENDIF!]
      [!ENDLOOP!]
    [!ENDLOOP!]
    [!ENDNOCODE!]
  [!ENDIF!]
  [!IF "$Spi_MacQspi5Used = num:i(1)"!]
    /*Kernel 5*/
    [!NOCODE!]
    [!VAR "Total_ch5"="num:i(0)"!]
    [!LOOP "SpiDriver/SpiChannel/*[SpiChannelType = 'EB']"!]
      [!VAR "temp"="node:name(.)"!]
      [!LOOP "../../SpiJob/*/SpiChannelList/*[node:name(node:ref(./SpiChannelAssignment)) = $temp]"!]
        [!IF "(node:ref(../../SpiDeviceAssignment)/SpiHwUnit = 'QSPI5') and (not(text:contains(text:split($Spi_MasterChnlIstNum,','), $temp)))"!]
          [!VAR "Total_ch5"="$Total_ch5 + num:i(1)"!]
          [!VAR "Spi_MasterChnlIstNum" = "concat($Spi_MasterChnlIstNum,$temp,',')"!]
          [!BREAK!]
        [!ENDIF!]
      [!ENDLOOP!]
    [!ENDLOOP!]
    [!ENDNOCODE!]
  [!ENDIF!]
  [!FOR "CPU_ID" = "0" TO "num:i($Spi_MaxCore)"!][!//
    [!IF "text:split($Core_config,',')[position() = $CPU_ID + num:i(1)] = num:i(1)"!]
      [!NOCODE!]
      [!VAR "TotalEBPerCore"="num:i(0)"!]
      [!IF "text:split($QSPICore_config,',')[position() = num:i(1)] = $CPU_ID"!]
        [!VAR "TotalEBPerCore"="$TotalEBPerCore + $Total_ch0"!]
      [!ENDIF!]
      [!IF "text:split($QSPICore_config,',')[position() = num:i(2)] = $CPU_ID"!]
        [!VAR "TotalEBPerCore"="$TotalEBPerCore + $Total_ch1"!]
      [!ENDIF!]
      [!IF "text:split($QSPICore_config,',')[position() = num:i(3)] = $CPU_ID"!]
        [!VAR "TotalEBPerCore"="$TotalEBPerCore + $Total_ch2"!]
      [!ENDIF!]
      [!IF "text:split($QSPICore_config,',')[position() = num:i(4)] = $CPU_ID"!]
        [!VAR "TotalEBPerCore"="$TotalEBPerCore + $Total_ch3"!]
      [!ENDIF!]
      [!IF "text:split($QSPICore_config,',')[position() = num:i(5)] = $CPU_ID"!]
        [!VAR "TotalEBPerCore"="$TotalEBPerCore + $Total_ch4"!]
      [!ENDIF!]
      [!IF "text:split($QSPICore_config,',')[position() = num:i(6)] = $CPU_ID"!]
        [!VAR "TotalEBPerCore"="$TotalEBPerCore + $Total_ch5"!]
      [!ENDIF!]
      [!ENDNOCODE!]
      [!//[cover parentID={189C1840-42D5-4f07-BAF2-78323B4BE2FE}][/cover][!//
      #define SPI_NUM_EB_CHANNELS_CORE[!"num:i($CPU_ID)"!]            ([!"num:i($TotalEBPerCore)"!]U)
    [!ENDIF!]
  [!ENDFOR!][!//

  [!/* [cover parentID={A418BA5B-0941-4bd3-A1B3-F0E434DAF198}]SPI_DMA_MAX_TCS_NUM_QSPIx[/cover] */!][!//
  [!CALL "Spi_CGDmaTcsCount"!][!//
  [!CALL "Spi_CGVerifySpiHwConfig"!][!//
  [!IF "$Spi_MacQspi0Used = num:i(1)"!]
    [!IF "$SpiAS422Enable = num:i(1)"!]
      [!IF "$Spi_MacQspi0HwType = num:i(1)"!]
        /* DMA Transaction control set per channel for QSPI0 */
        #define SPI_DMA_MAX_TCS_NUM_QSPI0             [!//
        ([!"num:i($Spi_DmaMaxTcsNumQspi0)"!]U)
      [!ELSE!]
        #define SPI_DMA_MAX_TCS_NUM_QSPI0 (0U)
      [!ENDIF!]
      [!ELSE!]
        [!IF "$Spi_MacQspi0HwType440 = num:i(1)"!]
        /* DMA Transaction control set per channel for QSPI0 */
      #define SPI_DMA_MAX_TCS_NUM_QSPI0             [!//
      ([!"num:i($Spi_DmaMaxTcsNumQspi0)"!]U)
        [!ELSE!]
        #define SPI_DMA_MAX_TCS_NUM_QSPI0 (0U)
      [!ENDIF!]
    [!ENDIF!]
  [!ENDIF!]
  [!IF "$Spi_MacQspi1Used = num:i(1)"!]
    [!IF "$SpiAS422Enable = num:i(1)"!]
      [!IF "$Spi_MacQspi1HwType = num:i(1)"!]
        /* DMA Transaction control set per channel for QSPI1 */
        #define SPI_DMA_MAX_TCS_NUM_QSPI1             [!//
        ([!"num:i($Spi_DmaMaxTcsNumQspi1)"!]U)
      [!ELSE!]
        #define SPI_DMA_MAX_TCS_NUM_QSPI1 (0U)
      [!ENDIF!]
      [!ELSE!]
        [!IF "$Spi_MacQspi1HwType440 = num:i(1)"!]
        /* DMA Transaction control set per channel for QSPI1 */
      #define SPI_DMA_MAX_TCS_NUM_QSPI1             [!//
      ([!"num:i($Spi_DmaMaxTcsNumQspi1)"!]U)
        [!ELSE!]
        #define SPI_DMA_MAX_TCS_NUM_QSPI1 (0U)
      [!ENDIF!]
    [!ENDIF!]
  [!ENDIF!]
  [!IF "$Spi_MacQspi2Used = num:i(1)"!]
    [!IF "$SpiAS422Enable = num:i(1)"!]
      [!IF "$Spi_MacQspi2HwType = num:i(1)"!]
        /* DMA Transaction control set per channel for QSPI2 */
        #define SPI_DMA_MAX_TCS_NUM_QSPI2             [!//
        ([!"num:i($Spi_DmaMaxTcsNumQspi2)"!]U)
      [!ELSE!]
        #define SPI_DMA_MAX_TCS_NUM_QSPI2 (0U)
      [!ENDIF!]
      [!ELSE!]
        [!IF "$Spi_MacQspi2HwType440 = num:i(1)"!]
        /* DMA Transaction control set per channel for QSPI2 */
      #define SPI_DMA_MAX_TCS_NUM_QSPI2             [!//
      ([!"num:i($Spi_DmaMaxTcsNumQspi2)"!]U)
        [!ELSE!]
        #define SPI_DMA_MAX_TCS_NUM_QSPI2 (0U)
      [!ENDIF!]
    [!ENDIF!]
  [!ENDIF!]
 [!IF "$Spi_MacQspi3Used = num:i(1)"!]
    [!IF "$SpiAS422Enable = num:i(1)"!]
      [!IF "$Spi_MacQspi3HwType = num:i(1)"!]
        /* DMA Transaction control set per channel for QSPI3 */
        #define SPI_DMA_MAX_TCS_NUM_QSPI3             [!//
        ([!"num:i($Spi_DmaMaxTcsNumQspi3)"!]U)
      [!ELSE!]
        #define SPI_DMA_MAX_TCS_NUM_QSPI3 (0U)
      [!ENDIF!]
      [!ELSE!]
        [!IF "$Spi_MacQspi3HwType440 = num:i(1)"!]
        /* DMA Transaction control set per channel for QSPI3 */
      #define SPI_DMA_MAX_TCS_NUM_QSPI3             [!//
      ([!"num:i($Spi_DmaMaxTcsNumQspi3)"!]U)
        [!ELSE!]
        #define SPI_DMA_MAX_TCS_NUM_QSPI3 (0U)
      [!ENDIF!]
    [!ENDIF!]
  [!ENDIF!]
  [!IF "$Spi_MacQspi4Used = num:i(1)"!]
    [!IF "$SpiAS422Enable = num:i(1)"!]
      [!IF "$Spi_MacQspi4HwType = num:i(1)"!]
        /* DMA Transaction control set per channel for QSPI4 */
        #define SPI_DMA_MAX_TCS_NUM_QSPI4             [!//
        ([!"num:i($Spi_DmaMaxTcsNumQspi4)"!]U)
      [!ELSE!]
        #define SPI_DMA_MAX_TCS_NUM_QSPI4 (0U)
      [!ENDIF!]
      [!ELSE!]
        [!IF "$Spi_MacQspi4HwType440 = num:i(1)"!]
        /* DMA Transaction control set per channel for QSPI4 */
      #define SPI_DMA_MAX_TCS_NUM_QSPI4             [!//
      ([!"num:i($Spi_DmaMaxTcsNumQspi4)"!]U)
        [!ELSE!]
        #define SPI_DMA_MAX_TCS_NUM_QSPI4 (0U)
      [!ENDIF!]
    [!ENDIF!]
  [!ENDIF!]
  [!IF "$Spi_MacQspi5Used = num:i(1)"!]
    [!IF "$SpiAS422Enable = num:i(1)"!]
      [!IF "$Spi_MacQspi5HwType = num:i(1)"!]
        /* DMA Transaction control set per channel for QSPI5 */
        #define SPI_DMA_MAX_TCS_NUM_QSPI5             [!//
        ([!"num:i($Spi_DmaMaxTcsNumQspi5)"!]U)
      [!ELSE!]
        #define SPI_DMA_MAX_TCS_NUM_QSPI5 (0U)
      [!ENDIF!]
      [!ELSE!]
        [!IF "$Spi_MacQspi5HwType440 = num:i(1)"!]
        /* DMA Transaction control set per channel for QSPI5 */
      #define SPI_DMA_MAX_TCS_NUM_QSPI5             [!//
      ([!"num:i($Spi_DmaMaxTcsNumQspi5)"!]U)
        [!ELSE!]
        #define SPI_DMA_MAX_TCS_NUM_QSPI5 (0U)
      [!ENDIF!]
    [!ENDIF!]
  [!ENDIF!]
  /* Indicates no CS to be done */
  #define SPI_CS_VIA_HW_OR_NONE                 (0xFFFFU)
  #define SPI_PARITY_EVEN                       (0U)
  #define SPI_PARITY_ODD                        (1U)
  #define SPI_PARITY_UNUSED                     (2U)
  /* Configuration Options:
  Selection of Channel Buffer Type */
  /* EB Buffer Channel Type */
  #define SPI_EB_CHANNEL                        (0U)
  /* IB Buffer Channel Type */
  #define SPI_IB_CHANNEL                        (1U)
  /* Invalid DMA channel */
  #define SPI_DMA_CHNL_INVALID                  (0xFFU)
  [!//
  [!/* Store Symbolic names for Sequences in variables */!][!//
  [!CALL "Spi_CGStoreSequence_ID"!][!//
  [!//
  /* Sequence ID */[!//
  [!/* Print Symbolic names for Sequences which are stored in variables */!][!//
  [!LOOP "SpiDriver/SpiSequence/*"!][!//
    /* MISRA2012_RULE_5_1_JUSTIFICATION: The macro is generated as per the naming
    convention followed for symbolic names, defined as per AUTOSAR  */
    /* MISRA2012_RULE_5_2_JUSTIFICATION: The macro is generated as per the naming
    convention followed for symbolic names, defined as per AUTOSAR  */
    /* MISRA2012_RULE_5_4_JUSTIFICATION: The macro is generated as per the naming
    convention followed for symbolic names, defined as per AUTOSAR  */
    /* MISRA2012_RULE_5_5_JUSTIFICATION: The macro is generated as per the naming
    convention followed for symbolic names, defined as per AUTOSAR  */
    [!//[cover parentID={9977A32B-7EE5-47cb-99E1-48C775FAF78F}][/cover][!//
    #define SpiConf_SpiSequence_[!"node:name(node:current())"!]      ([!"node:current()/SpiSequenceId"!]U)
  [!ENDLOOP!][!//
  [!/* Store Symbolic names for Jobs in variables */!][!//
  [!CALL "Spi_CGStoreJob_ID"!][!//
  /* Job ID */[!//
  [!/* Print Symbolic names for Jobs which are stored in variables */!][!//
  [!LOOP "SpiDriver/SpiJob/*"!][!//
    [!//[cover parentID={A1EB7D14-ECCF-4401-8406-F89D2FCC01C5}][/cover][!//
    #define SpiConf_SpiJob_[!"node:name(node:current())"!]      ([!"node:current()/SpiJobId"!]U)
  [!ENDLOOP!][!//
  [!/* Store Symbolic names for Channels in variables */!][!//
  [!CALL "Spi_CGStoreChannel_ID"!][!//
  /* Channel ID */[!//
  [!/* Print Symbolic names for Channels which are stored in variables */!][!//
  [!LOOP "SpiDriver/SpiChannel/*"!][!//
    /* MISRA2012_RULE_5_1_JUSTIFICATION: The macro is generated as per the naming
    convention followed for symbolic names, defined as per AUTOSAR  */
    /* MISRA2012_RULE_5_2_JUSTIFICATION: The macro is generated as per the naming
    convention followed for symbolic names, defined as per AUTOSAR  */
    /* MISRA2012_RULE_5_4_JUSTIFICATION: The macro is generated as per the naming
    convention followed for symbolic names, defined as per AUTOSAR  */
    /* MISRA2012_RULE_5_5_JUSTIFICATION: The macro is generated as per the naming
    convention followed for symbolic names, defined as per AUTOSAR  */
    [!//[cover parentID={929398FD-A615-4634-A141-F2433ABFEB10}][/cover][!//
    #define SpiConf_SpiChannel_[!"node:name(node:current())"!]      ([!"node:current()/SpiChannelId"!]U)
  [!ENDLOOP!]
  [!//
  [!//
  [!//
[!ENDSELECT!][!/* as:modconf('Spi')[1] */!][!//
/*Physical sequence ID*/
[!CALL "Spi_CGGenerateSequence_IDPhysical"!][!//
/* Physical Job ID */[!//
[!/* Print Symbolic names for Jobs which are stored in variables */!][!//
[!CALL "Spi_CGGenerateJob_IDPhysical"!]
/* Channel ID */[!//
[!/* Print Symbolic names for Channels which are stored in variables */!][!//
[!CALL "Spi_CGGenerateChannel_IDPhysical"!][!//
/*end Physical*/
[!CALL "Spi_CGCalculateTotalSequencePerCore"!]
[!CALL "Spi_CGCalculateTotalJobPerCore"!]
[!FOR "CPU_ID" = "0" TO "num:i($Spi_MaxCore)"!][!//
  [!FOR "QSPIID" = "0" TO "(num:i($QspiLastId))"!][!//
    [!IF "text:split($QSPICore_config,',')[position() = num:i($QSPIID) + 1] = $CPU_ID"!]
      [!/* [cover parentID={18E4CC58-2E38-43e3-AC7B-93F5DE642F55}]SPI_QSPIx_CORE[/cover] */!][!//
      #define SPI_QSPI[!"num:i($QSPIID)"!]_CORE          [!"$CPU_ID"!]
    [!ENDIF!]
  [!ENDFOR!]
[!ENDFOR!]
[!// [cover parentID={ADDC372B-1A3A-414c-9AC7-AC7487111E7A}][/cover][!//
#define SPI_INIT_DEINIT_API_MODE              [!"node:value(SpiGeneral/SpiInitDeInitApiMode)"!]

[!// [cover parentID={D0C7BE6C-C63F-4315-B38C-1FF806BDEB43}][/cover][!//
#define SPI_RUN_TIME_API_MODE                 [!"node:value(SpiGeneral/SpiRuntimeApiMode)"!]
#define SPI_MCAL_SUPERVISOR                   (0U)
#define SPI_MCAL_USER1                        (1U)
[!// [cover parentID={BB6EC852-F9E4-4349-B056-E8D2A1FB578B}][/cover][!//
#define SPI_INIT_CHECK_API                        [!//
[!IF "SpiGeneral/SpiInitCheckApi = 'true'"!][!//
  (STD_ON)
[!ELSE!][!//
  (STD_OFF)
[!ENDIF!][!//
[!/* [cover parentID={70E36561-78F6-4CED-AE0A-8C917724A468}]SPI_MULTICORE_ERROR_DETECT[/cover] */!][!//
#define SPI_MULTICORE_ERROR_DETECT                        [!//
[!IF "SpiGeneral/SpiMultiCoreErrorDetect = 'true'"!][!//
  (STD_ON)
[!ELSE!][!//
  (STD_OFF)
[!ENDIF!][!//
#endif  /* SPI_CFG_H */
/* End Of File */
[!ENDINDENT!]
