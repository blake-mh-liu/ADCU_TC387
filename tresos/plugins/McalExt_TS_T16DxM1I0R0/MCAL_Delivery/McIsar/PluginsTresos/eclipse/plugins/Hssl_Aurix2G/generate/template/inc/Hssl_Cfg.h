[!AUTOSPACING!]
[!INDENT "0"!]
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
**  FILENAME  : Hssl_Cfg.h                                                    **
**                                                                            **
**  VERSION   : 7.0.0                                                         **
**                                                                            **
**  DATE      : 2020-09-09                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : NA                                                **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID= ]                                         **
**                                                                            **
**  DESCRIPTION  : Code template header file for Hssl Driver                  **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*****************************************************************************/!][!//
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
**  FILENAME  : Hssl_Cfg.h                                                    **
**                                                                            **
**  VERSION   : 7.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]      !!!IGNORE-LINE!!!               **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]         !!!IGNORE-LINE!!!                **
**                                                                            **
**  BSW MODULE DECRIPTION : NA                                                **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Hssl configuration generated out of ECUC file              **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef HSSL_CFG_H
#define HSSL_CFG_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
[!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
[!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
[!VAR "SwRevisionVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
/* Vendor specific implementation version information */
#define HSSL_SW_MAJOR_VERSION   ([!"$SwMajorVersion"!]U)
#define HSSL_SW_MINOR_VERSION   ([!"$SwMinorVersion"!]U)
#define HSSL_SW_PATCH_VERSION   ([!"$SwRevisionVersion"!]U)
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Hssl')[1]"!][!//
  [!//
  [!VAR "HsslModuleConfigPath" = "'HsslConfig/*'"!][!//
  [!LOOP "HsslConfig/*"!][!//
    [!VAR "HsslNotify" = "./HsslEXICallbackFunction"!][!//
    [!IF "num:isnumber($HsslNotify) !=  'true' and $HsslNotify != 'NULL_PTR'"!]
      /* Global Error EXI Callback function for HSSL */
      extern void [!"$HsslNotify"!](uint32 Event);
    [!ENDIF!][!//
    [!VAR "HsslNotify" = "./*/HsslCh0COKCallbackFunction"!][!//
    [!IF "num:isnumber($HsslNotify) !=  'true' and $HsslNotify != 'NULL_PTR'"!]
      /* Write Callback function for HSSL Channel-0 */
      extern void [!"$HsslNotify"!](uint32 Event);
    [!ENDIF!][!//
    [!VAR "HsslNotify" = "./*/HsslCh1COKCallbackFunction"!][!//
    [!IF "num:isnumber($HsslNotify) !=  'true' and $HsslNotify != 'NULL_PTR'"!]
      /* Write Callback function for HSSL Channel-1 */
      extern void [!"$HsslNotify"!](uint32 Event);
    [!ENDIF!][!//
    [!VAR "HsslNotify" = "./*/HsslCh2COKCallbackFunction"!][!//
    [!IF "num:isnumber($HsslNotify) !=  'true' and $HsslNotify != 'NULL_PTR'"!]
      /* Write Callback function for HSSL Channel-2 */
      extern void [!"$HsslNotify"!](uint32 Event);
    [!ENDIF!][!//
    [!VAR "HsslNotify" = "./*/HsslCh3COKCallbackFunction"!][!//
    [!IF "num:isnumber($HsslNotify) !=  'true' and $HsslNotify != 'NULL_PTR'"!]
      /* Write Callback function for HSSL Channel-3 */
      extern void [!"$HsslNotify"!](uint32 Event);
    [!ENDIF!][!//
    [!VAR "HsslNotify" = "./*/HsslCh0RDICallbackFunction"!][!//
    [!IF "num:isnumber($HsslNotify) !=  'true' and $HsslNotify != 'NULL_PTR'"!]
      /* Read Callback function for HSSL Channel-0 */
      extern void [!"$HsslNotify"!](uint32 Event);
    [!ENDIF!][!//
    [!VAR "HsslNotify" = "./*/HsslCh1RDICallbackFunction"!][!//
    [!IF "num:isnumber($HsslNotify) !=  'true' and $HsslNotify != 'NULL_PTR'"!]
      /* Read Callback function for HSSL Channel-1 */
      extern void [!"$HsslNotify"!](uint32 Event);
    [!ENDIF!][!//
    [!VAR "HsslNotify" = "./*/HsslCh2RDICallbackFunction"!][!//
    [!IF "num:isnumber($HsslNotify) !=  'true' and $HsslNotify != 'NULL_PTR'"!]
      /* Read Callback function for HSSL Channel-2 */
      extern void [!"$HsslNotify"!](uint32 Event);
    [!ENDIF!][!//
    [!VAR "HsslNotify" = "./*/HsslCh3RDICallbackFunction"!][!//
    [!IF "num:isnumber($HsslNotify) !=  'true' and $HsslNotify != 'NULL_PTR'"!]
      /* Read Callback function for HSSL Channel-3 */
      extern void [!"$HsslNotify"!](uint32 Event);
    [!ENDIF!][!//
    [!VAR "HsslNotify" = "./*/HsslCh0TRGCallbackFunction"!][!//
    [!IF "num:isnumber($HsslNotify) !=  'true' and $HsslNotify != 'NULL_PTR'"!]
      /* Trigger Callback function for HSSL Channel-0 */
      extern void [!"$HsslNotify"!](uint32 Event);
    [!ENDIF!][!//
    [!VAR "HsslNotify" = "./*/HsslCh1TRGCallbackFunction"!][!//
    [!IF "num:isnumber($HsslNotify) !=  'true' and $HsslNotify != 'NULL_PTR'"!]
      /* Trigger Callback function for HSSL Channel-1 */
      extern void [!"$HsslNotify"!](uint32 Event);
    [!ENDIF!][!//
    [!VAR "HsslNotify" = "./*/HsslCh2TRGCallbackFunction"!][!//
    [!IF "num:isnumber($HsslNotify) !=  'true' and $HsslNotify != 'NULL_PTR'"!]
      /* Trigger Callback function for HSSL Channel-2 */
      extern void [!"$HsslNotify"!](uint32 Event);
    [!ENDIF!][!//
    [!VAR "HsslNotify" = "./*/HsslCh3TRGCallbackFunction"!][!//
    [!IF "num:isnumber($HsslNotify) !=  'true' and $HsslNotify != 'NULL_PTR'"!]
      /* Trigger Callback function for HSSL Channel-3 */
      extern void [!"$HsslNotify"!](uint32 Event);
    [!ENDIF!][!//
    [!VAR "HsslNotify" = "./*/HsslCh0ERRCallbackFunction"!][!//
    [!IF "num:isnumber($HsslNotify) !=  'true' and $HsslNotify != 'NULL_PTR'"!]
      /* Error Callback function for HSSL Channel-0 */
      extern void [!"$HsslNotify"!](uint32 Event);
    [!ENDIF!][!//
    [!VAR "HsslNotify" = "./*/HsslCh1ERRCallbackFunction"!][!//
    [!IF "num:isnumber($HsslNotify) !=  'true' and $HsslNotify != 'NULL_PTR'"!]
      /* Error Callback function for HSSL Channel-1 */
      extern void [!"$HsslNotify"!](uint32 Event);
    [!ENDIF!][!//
    [!VAR "HsslNotify" = "./*/HsslCh2ERRCallbackFunction"!][!//
    [!IF "num:isnumber($HsslNotify) !=  'true' and $HsslNotify != 'NULL_PTR'"!]
      /* Error Callback function for HSSL Channel-2 */
      extern void [!"$HsslNotify"!](uint32 Event);
    [!ENDIF!][!//
    [!VAR "HsslNotify" = "./*/HsslCh3ERRCallbackFunction"!][!//
    [!IF "num:isnumber($HsslNotify) !=  'true' and $HsslNotify != 'NULL_PTR'"!]
      /* Error Callback function for HSSL Channel-3 */
      extern void [!"$HsslNotify"!](uint32 Event);
    [!ENDIF!][!//
  [!ENDLOOP!][!//
  [!LOOP "HsslConfig/*"!][!//
    [!VAR "HsslNotify" = "./HsslDmaMultiReadCallback"!][!//
    [!IF "num:isnumber($HsslNotify) !=  'true' and $HsslNotify != 'NULL_PTR'"!]
      /* DMA multi read callback */
      extern void [!"$HsslNotify"!](uint32 Event);
    [!ENDIF!][!//
    [!VAR "HsslNotify" = "./HsslDmaMultiWriteCallback"!][!//
    [!IF "num:isnumber($HsslNotify) !=  'true' and $HsslNotify != 'NULL_PTR'"!]
      /* DMA multi write Callback function for HSSL Channel-3 */
      extern void [!"$HsslNotify"!](uint32 Event);
    [!ENDIF!][!//
  [!ENDLOOP!][!//

  #define HSSL_MASTER               (0U)
  #define HSSL_SLAVE                (1U)
  #define HSSL_NO_ACCESS            (0U)
  #define HSSL_READ_ACCESS          (1U)
  #define HSSL_WRITE_ACCESS         (2U)
  #define HSSL_READ_WRITE_ACCESS    (3U)
  #define HSSL_REFCLK_10MHZ (0U)
  #define HSSL_REFCLK_20MHZ (1U)
  #define HSSL_REFCLK_40MHZ (2U)
  #define HSSL_SYSCLK_DIV_1 (0U)
  #define HSSL_SYSCLK_DIV_2 (1U)
  #define HSSL_SYSCLK_DIV_4 (2U)
  #define HSSL_TX_LOW_SPEED (0U)
  #define HSSL_TX_HIGH_SPEED (2U)
  #define HSSL_RX_LOW_SPEED (0U)
  #define HSSL_RX_MEDIUM_SPEED (1U)
  #define HSSL_RX_HIGH_SPEED (2U)
  #define HSSL_POLLING_MODE (0U)
  #define HSSL_INTERUPT_MODE (1U)

  /*
  Configuration: HSSL_DEV_ERROR_DETECT
  - if STD_ON, DET is Enabled
  - if STD_OFF,DET is Disabled
  If the switch HSSL_DEV_ERROR_DETECT is enabled API parameter checking
  is also enabled.
  */
  #define HSSL_DEV_ERROR_DETECT  ([!//
  [!IF "HsslGeneral/HsslDevErrorDetect = 'true'"!][!//
    STD_ON[!//
  [!ELSE!][!//
    STD_OFF[!//
  [!ENDIF!][!//
  )
  [!CODE!][!//
  [!IF "HsslGeneral/HsslInterfaceMode = 'HSSL_MASTER'"!][!//
    [!VAR "Interface" = "'HSSL_MASTER'"!][!//
    [!VAR "SystemClock" = "'STD_ON'"!][!//
  [!ELSEIF "HsslGeneral/HsslInterfaceMode = 'HSSL_SLAVE'"!][!//
    [!VAR "Interface" = "'HSSL_SLAVE'"!][!//
    [!VAR "SystemClock" = "'STD_OFF'"!][!//
  [!ENDIF!][!/* ./Interfacemode */!][!//
  [!/* ------ Determine the Interface Modes for Memory ----- */!]
  #define HSSL_INTERFACE_MODE   ([!"$Interface"!])[!CR!][!//
  #define HSSL_SYSTEM_CLOCK   ([!"$SystemClock"!])[!CR!][!//
  [!ENDCODE!][!//
  [!CODE!][!//
  [!IF "HsslGeneral/HsslOperatingMode = 'HSSL_POLLING_MODE'"!][!//
    [!VAR "Interface" = "'HSSL_POLLING_MODE'"!][!//
  [!ELSEIF "HsslGeneral/HsslOperatingMode = 'HSSL_INTERUPT_MODE'"!][!//
    [!VAR "Interface" = "'HSSL_INTERUPT_MODE'"!][!//
  [!ENDIF!][!/* ./Interfacemode */!][!//
  [!/* ------ Determine the Interface Modes for Memory ----- */!]
  #define HSSL_OPERATING_MODE   ([!"$Interface"!])[!CR!][!//
  [!ENDCODE!][!//

  /* clok pre divider value for HSSL */
  #define HSSL_CLOCK_PREDIVIDER  ([!//
  [!"num:inttohex(HsslGeneral/Hsslclockpredivider)"!]U)

  /* Configurred HSSL Instances */
  [!CODE!][!//
  [!VAR "NoOfHsslInstances" = "num:i(count(HsslConfig/*))"!][!//
  #define HSSL_NUM_INSTANCES_CONFIGURRED  ([!"$NoOfHsslInstances"!]U)
  [!VAR "Hssl0InstanceAvail" = "'STD_OFF'"!][!//
  [!VAR "Hssl1InstanceAvail" = "'STD_OFF'"!][!//
  [!IF "$NoOfHsslInstances = 2"!][!//
    #define HSSL0_CONFIGURRED STD_ON
    #define HSSL1_CONFIGURRED STD_ON
  [!ELSE!][!//
    [!IF "(HsslConfig/*/HsslInstanceID) = 0"!][!//
      #define HSSL0_CONFIGURRED STD_ON
      #define HSSL1_CONFIGURRED STD_OFF
    [!ELSE!][!//
      #define HSSL0_CONFIGURRED STD_OFF
      #define HSSL1_CONFIGURRED STD_ON
    [!ENDIF!][!//
  [!ENDIF!][!//
  [!ENDCODE!][!//
  #define HSSL_CH2_STREAMING       (1U)
  #define HSSL_CH2_COMMAND         (0U)

  /* Configurring the Channel-2 as Stream Mode/Command Mode */
  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      #define HSSL0_STREAMING_CH_MODE  ([!//
      [!IF "HsslConfig/*[@index=$ChannelIndex]/HsslCh2Mode = 'HSSL_CH2_STREAMING'"!][!//
        HSSL_CH2_STREAMING[!//
      [!ELSE!][!//
        HSSL_CH2_COMMAND[!//
      [!ENDIF!][!//
      )
    [!ELSE!][!//
      #define HSSL1_STREAMING_CH_MODE  ([!//
      [!IF "HsslConfig/*[@index=$ChannelIndex]/HsslCh2Mode = 'HSSL_CH2_STREAMING'"!][!//
        HSSL_CH2_STREAMING[!//
      [!ELSE!][!//
        HSSL_CH2_COMMAND[!//
      [!ENDIF!][!//
      )
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//

  /* Configurring the Channel-2 Transmitter as Single/Continuous Block mode */
  #define  HSSL_STREAMING_MODE_CONTINOUS     (0U)
  #define  HSSL_STREAMING_MODE_SINGLE        (1U)
  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      #define HSSL0_STREAMING_MODE_TX  ([!//
      [!IF "HsslConfig/*[@index=$ChannelIndex]/HsslCh2Mode = 'HSSL_CH2_STREAMING'"!][!//
        [!IF "HsslConfig/*[@index=$ChannelIndex]/HsslStreamingModeTx = 'HSSL_STREAMING_MODE_SINGLE'"!][!//
          HSSL_STREAMING_MODE_SINGLE[!//
        [!ELSE!][!//
          HSSL_STREAMING_MODE_CONTINOUS[!//
        [!ENDIF!][!//
      [!ELSE!][!//
        HSSL_STREAMING_MODE_CONTINOUS[!//
      [!ENDIF!][!//
      )
    [!ELSE!][!//
      #define HSSL1_STREAMING_MODE_TX  ([!//
      [!IF "HsslConfig/*[@index=$ChannelIndex]/HsslCh2Mode = 'HSSL_CH2_STREAMING'"!][!//
        [!IF "HsslConfig/*[@index=$ChannelIndex]/HsslStreamingModeTx = 'HSSL_STREAMING_MODE_SINGLE'"!][!//
          HSSL_STREAMING_MODE_SINGLE[!//
        [!ELSE!][!//
          HSSL_STREAMING_MODE_CONTINOUS[!//
        [!ENDIF!][!//
      [!ELSE!][!//
        HSSL_STREAMING_MODE_CONTINOUS[!//
      [!ENDIF!][!//
      )
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//

  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/HsslEXICallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/HsslEXICallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/HsslEXICallbackFunction)"!][!//
        /* HSSL0 EXI - User callback functions */
        #define HSSL0_EXI_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/HsslEXICallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/HsslEXICallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL0_EXI_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function address */
      [!ELSE!]
        #define HSSL0_EXI_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
      [!//
    [!ELSE!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/HsslEXICallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/HsslEXICallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/HsslEXICallbackFunction)"!][!//
        /* HSSL1 EXI - User callback functions */
        #define HSSL1_EXI_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/HsslEXICallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/HsslEXICallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL1_EXI_HANDLE_CALLBACK          ([!"$callback"!])
      [!ELSE!]
        #define HSSL1_EXI_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!//

  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0COKCallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0COKCallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0COKCallbackFunction)"!][!//
        /* Hssl0 Channel-0 Write- User callback functions */
        #define HSSL0_CH0_WRITE_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0COKCallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0COKCallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL0_CH0_WRITE_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL0_CH0_WRITE_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
      [!//
    [!ELSE!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0COKCallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0COKCallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0COKCallbackFunction)"!][!//
        /* Hssl1 Channel-0 Write- User callback functions */
        #define HSSL1_CH0_WRITE_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0COKCallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0COKCallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL1_CH0_WRITE_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL1_CH0_WRITE_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!//

 [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1COKCallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1COKCallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1COKCallbackFunction)"!][!//
        /* Hssl0 Channel-1 Write- User callback functions */
        #define HSSL0_CH1_WRITE_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1COKCallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1COKCallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL0_CH1_WRITE_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL0_CH1_WRITE_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
      [!//
    [!ELSE!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1COKCallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1COKCallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1COKCallbackFunction)"!][!//
        /* Hssl1 Channel-0 Write- User callback functions */
        #define HSSL1_CH1_WRITE_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1COKCallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1COKCallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL1_CH1_WRITE_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL1_CH1_WRITE_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!//

  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2COKCallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2COKCallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2COKCallbackFunction)"!][!//
        /* Hssl0 Channel Write- User callback functions */
        #define HSSL0_CH2_WRITE_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2COKCallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2COKCallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL0_CH2_WRITE_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL0_CH2_WRITE_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
      [!//
    [!ELSE!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2COKCallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2COKCallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2COKCallbackFunction)"!][!//
        /* Hssl1 Channel Write- User callback functions */
        #define HSSL1_CH2_WRITE_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2COKCallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2COKCallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL1_CH2_WRITE_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL1_CH2_WRITE_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!//

  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3COKCallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3COKCallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3COKCallbackFunction)"!][!//
        /* Hssl0 Channel Write- User callback functions */
        #define HSSL0_CH3_WRITE_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3COKCallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3COKCallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL0_CH3_WRITE_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL0_CH3_WRITE_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
      [!//
    [!ELSE!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3COKCallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3COKCallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3COKCallbackFunction)"!][!//
        /* Hssl1 Channel Write- User callback functions */
        #define HSSL1_CH3_WRITE_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3COKCallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3COKCallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL1_CH3_WRITE_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL1_CH3_WRITE_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!//

  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0RDICallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0RDICallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0RDICallbackFunction)"!][!//
        /* Hssl0 Channel Read- User callback functions */
        #define HSSL0_CH0_READ_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0RDICallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0RDICallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL0_CH0_READ_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL0_CH0_READ_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
      [!//
    [!ELSE!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0RDICallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0RDICallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0RDICallbackFunction)"!][!//
        /* Hssl1 Channel read- User callback functions */
        #define HSSL1_CH0_READ_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0RDICallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0RDICallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL1_CH0_READ_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL1_CH0_READ_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!//

  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1RDICallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1RDICallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1RDICallbackFunction)"!][!//
        /* Hssl0 Channel Read- User callback functions */
        #define HSSL0_CH1_READ_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1RDICallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1RDICallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL0_CH1_READ_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL0_CH1_READ_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
      [!//
    [!ELSE!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1RDICallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1RDICallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1RDICallbackFunction)"!][!//
        /* Hssl1 Channel read- User callback functions */
        #define HSSL1_CH1_READ_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1RDICallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1RDICallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL1_CH1_READ_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL1_CH1_READ_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!//

  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2RDICallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2RDICallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2RDICallbackFunction)"!][!//
        /* Hssl0 Channel Read- User callback functions */
        #define HSSL0_CH2_READ_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2RDICallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2RDICallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL0_CH2_READ_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL0_CH2_READ_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
      [!//
    [!ELSE!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2RDICallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2RDICallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2RDICallbackFunction)"!][!//
        /* Hssl1 Channel read- User callback functions */
        #define HSSL1_CH2_READ_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2RDICallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2RDICallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL1_CH2_READ_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL1_CH2_READ_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!//

  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3RDICallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3RDICallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3RDICallbackFunction)"!][!//
        /* Hssl0 Channel Read- User callback functions */
        #define HSSL0_CH3_READ_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3RDICallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3RDICallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL0_CH3_READ_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL0_CH3_READ_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
      [!//
    [!ELSE!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3RDICallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3RDICallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3RDICallbackFunction)"!][!//
        /* Hssl1 Channel read- User callback functions */
        #define HSSL1_CH3_READ_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3RDICallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3RDICallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL1_CH3_READ_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL1_CH3_READ_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!//

  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0TRGCallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0TRGCallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0TRGCallbackFunction)"!][!//
        /* Hssl0 Channel Trigger- User callback functions */
        #define HSSL0_CH0_TRIGGER_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0TRGCallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0TRGCallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL0_CH0_TRIGGER_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL0_CH0_TRIGGER_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
      [!//
    [!ELSE!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0TRGCallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0TRGCallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0TRGCallbackFunction)"!][!//
        /* Hssl1 Channel Trigger- User callback functions */
        #define HSSL1_CH0_TRIGGER_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0TRGCallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0TRGCallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL1_CH0_TRIGGER_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL1_CH0_TRIGGER_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!//

  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1TRGCallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1TRGCallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1TRGCallbackFunction)"!][!//
        /* Hssl0 Channel Trigger- User callback functions */
        #define HSSL0_CH1_TRIGGER_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1TRGCallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1TRGCallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL0_CH1_TRIGGER_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL0_CH1_TRIGGER_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
      [!//
    [!ELSE!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1TRGCallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1TRGCallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1TRGCallbackFunction)"!][!//
        /* Hssl1 Channel Trigger- User callback functions */
        #define HSSL1_CH1_TRIGGER_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1TRGCallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1TRGCallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL1_CH1_TRIGGER_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL1_CH1_TRIGGER_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!//

  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2TRGCallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2TRGCallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2TRGCallbackFunction)"!][!//
        /* Hssl0 Channel Trigger- User callback functions */
        #define HSSL0_CH2_TRIGGER_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2TRGCallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2TRGCallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL0_CH2_TRIGGER_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL0_CH2_TRIGGER_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
      [!//
    [!ELSE!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2TRGCallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2TRGCallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2TRGCallbackFunction)"!][!//
        /* Hssl1 Channel Trigger- User callback functions */
        #define HSSL1_CH2_TRIGGER_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2TRGCallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2TRGCallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL1_CH2_TRIGGER_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL1_CH2_TRIGGER_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!//

  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3TRGCallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3TRGCallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3TRGCallbackFunction)"!][!//
        /* Hssl0 Channel Trigger- User callback functions */
        #define HSSL0_CH3_TRIGGER_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3TRGCallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3TRGCallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL0_CH3_TRIGGER_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL0_CH3_TRIGGER_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
      [!//
    [!ELSE!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3TRGCallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3TRGCallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3TRGCallbackFunction)"!][!//
        /* Hssl1 Channel Trigger- User callback functions */
        #define HSSL1_CH3_TRIGGER_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3TRGCallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3TRGCallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL1_CH3_TRIGGER_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL1_CH3_TRIGGER_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!//

  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0ERRCallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0ERRCallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0ERRCallbackFunction)"!][!//
        /* Hssl0 Channel Error- User callback functions */
        #define HSSL0_CH0_ERROR_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0ERRCallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0ERRCallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL0_CH0_ERROR_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL0_CH0_ERROR_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
      [!//
    [!ELSE!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0ERRCallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0ERRCallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0ERRCallbackFunction)"!][!//
        /* Hssl1 Channel Error- User callback functions */
        #define HSSL1_CH0_ERROR_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0ERRCallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh0ERRCallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL1_CH0_ERROR_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL1_CH0_ERROR_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!//

  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1ERRCallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1ERRCallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1ERRCallbackFunction)"!][!//
        /* Hssl0 Channel Error- User callback functions */
        #define HSSL0_CH1_ERROR_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1ERRCallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1ERRCallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL0_CH1_ERROR_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL0_CH1_ERROR_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
      [!//
    [!ELSE!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1ERRCallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1ERRCallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1ERRCallbackFunction)"!][!//
        /* Hssl1 Channel Error- User callback functions */
        #define HSSL1_CH1_ERROR_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1ERRCallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh1ERRCallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL1_CH1_ERROR_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL1_CH1_ERROR_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!//

  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2ERRCallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2ERRCallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2ERRCallbackFunction)"!][!//
        /* Hssl0 Channel Error- User callback functions */
        #define HSSL0_CH2_ERROR_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2ERRCallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2ERRCallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL0_CH2_ERROR_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL0_CH2_ERROR_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
      [!//
    [!ELSE!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2ERRCallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2ERRCallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2ERRCallbackFunction)"!][!//
        /* Hssl1 Channel Error- User callback functions */
        #define HSSL1_CH2_ERROR_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2ERRCallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh2ERRCallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL1_CH2_ERROR_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL1_CH2_ERROR_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!//

  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3ERRCallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3ERRCallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3ERRCallbackFunction)"!][!//
        /* Hssl0 Channel Error- User callback functions */
        #define HSSL0_CH3_ERROR_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3ERRCallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3ERRCallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL0_CH3_ERROR_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL0_CH3_ERROR_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
      [!//
    [!ELSE!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3ERRCallbackFunction)) and ((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3ERRCallbackFunction != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3ERRCallbackFunction)"!][!//
        /* Hssl1 Channel Error- User callback functions */
        #define HSSL1_CH3_ERROR_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3ERRCallbackFunction)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/*/HsslCh3ERRCallbackFunction),8)"!], /*Notfication Function address*/
        #define HSSL1_CH3_ERROR_HANDLE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL1_CH3_ERROR_HANDLE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!//

  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/HsslDmaMultiReadCallback)) and ((HsslConfig/*[@index=$ChannelIndex])/HsslDmaMultiReadCallback != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/HsslDmaMultiReadCallback)"!][!//
        /* Hssl0 Channel Error- User callback functions */
        #define HSSL0_DMA_MULTIREAD_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/HsslDmaMultiReadCallback)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/HsslDmaMultiReadCallback),8)"!], /*Notfication Function address*/
        #define HSSL0_DMA_MULTIREAD_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL0_DMA_MULTIREAD_CALLBACK          NULL_PTR
      [!ENDIF!][!//
      [!//
    [!ELSE!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/HsslDmaMultiReadCallback)) and ((HsslConfig/*[@index=$ChannelIndex])/HsslDmaMultiReadCallback != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/HsslDmaMultiReadCallback)"!][!//
        /* Hssl1 Channel Error- User callback functions */
        #define HSSL1_DMA_MULTIREAD_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/HsslDmaMultiReadCallback)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/HsslDmaMultiReadCallback),8)"!], /*Notfication Function address*/
        #define HSSL1_DMA_MULTIREAD_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL1_DMA_MULTIREAD_CALLBACK          NULL_PTR
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!//

  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/HsslDmaMultiWriteCallback)) and ((HsslConfig/*[@index=$ChannelIndex])/HsslDmaMultiWriteCallback != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/HsslDmaMultiWriteCallback)"!][!//
        /* Hssl0 Channel Error- User callback functions */
        #define HSSL0_DMA_MULTIWRITE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/HsslDmaMultiWriteCallback)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/HsslDmaMultiWriteCallback),8)"!], /*Notfication Function address*/
        #define HSSL0_DMA_MULTIWRITE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL0_DMA_MULTIWRITE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
      [!//
    [!ELSE!][!//
      [!IF "not(num:isnumber((HsslConfig/*[@index=$ChannelIndex])/HsslDmaMultiWriteCallback)) and ((HsslConfig/*[@index=$ChannelIndex])/HsslDmaMultiWriteCallback != 'NULL_PTR')"!]
        [!VAR "callback" = "((HsslConfig/*[@index=$ChannelIndex])/HsslDmaMultiWriteCallback)"!][!//
        /* Hssl1 Channel Error- User callback functions */
        #define HSSL1_DMA_MULTIWRITE_CALLBACK          ([!"$callback"!]) /* Notification Function */
      [!ELSEIF "num:isnumber((HsslConfig/*[@index=$ChannelIndex])/HsslDmaMultiWriteCallback)"!]
        [!VAR "callback" = "num:inttohex(num:radixtoint((HsslConfig/*[@index=$ChannelIndex])/HsslDmaMultiWriteCallback),8)"!], /*Notfication Function address*/
        #define HSSL1_DMA_MULTIWRITE_CALLBACK          ([!"$callback"!]) /* Notification function address */
      [!ELSE!]
        #define HSSL1_DMA_MULTIWRITE_CALLBACK          NULL_PTR
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!//

  /* Configurring the Channel-2 Receiver as Single/Continuous Block mode */
  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      #define HSSL0_STREAMING_MODE_RX  ([!//
      [!IF "HsslConfig/*[@index=$ChannelIndex]/HsslCh2Mode = 'HSSL_CH2_STREAMING'"!][!//
        [!IF "HsslConfig/*[@index=$ChannelIndex]/HsslStreamingModeRx = 'HSSL_STREAMING_MODE_SINGLE'"!][!//
          HSSL_STREAMING_MODE_SINGLE[!//
        [!ELSE!][!//
          HSSL_STREAMING_MODE_CONTINOUS[!//
        [!ENDIF!][!//
      [!ELSE!][!//
        HSSL_STREAMING_MODE_CONTINOUS[!//
      [!ENDIF!][!//
      )
    [!ELSE!][!//
      #define HSSL1_STREAMING_MODE_RX  ([!//
      [!IF "HsslConfig/*[@index=$ChannelIndex]/HsslCh2Mode = 'HSSL_CH2_STREAMING'"!][!//
        [!IF "HsslConfig/*[@index=$ChannelIndex]/HsslStreamingModeRx = 'HSSL_STREAMING_MODE_SINGLE'"!][!//
          HSSL_STREAMING_MODE_SINGLE[!//
        [!ELSE!][!//
          HSSL_STREAMING_MODE_CONTINOUS[!//
        [!ENDIF!][!//
      [!ELSE!][!//
        HSSL_STREAMING_MODE_CONTINOUS[!//
      [!ENDIF!][!//
      )
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//

  /* Configuration: HSSL_HW_MAX_MODULES
  *  Maximum number of HSSL modules supported
  */
  #define HSSL_HW_MAX_MODULES  ([!"ecu:get('Hssl.MaxControllers')"!]U)

  /* Configuration: HSSL_VERSION_INFO_API
  HSSL Enable/Disable version information API
  - if STD_ON, Enables Version Info API
  - if STD_OFF, Disables Version Info API
  */
  #define HSSL_VERSION_INFO_API  ([!//
  [!IF "HsslGeneral/HsslVersionInfoApi = 'true'"!][!//
    STD_ON[!//
  [!ELSE!][!//
    STD_OFF[!//
  [!ENDIF!][!//
  )

  /*
  Configuration: HSSL_RUNNING_IN_USER_0_MODE_ENABLE
  - if STD_ON, enable User0 mode
  - if STD_OFF, enable User1 mode
  */
  #define HSSL_SUPERVISOR_MODE                   (STD_ON)
  #define HSSL_USER_MODE                         (STD_OFF)
  [!IF "HsslGeneral/HsslInitApiMode = 'HSSL_MCAL_SUPERVISOR'"!][!//
    #define HSSL_INIT_API_MODE              HSSL_SUPERVISOR_MODE
  [!ELSE!][!//
    #define HSSL_INIT_API_MODE              HSSL_USER_MODE
  [!ENDIF!][!//
  [!IF "HsslGeneral/HsslRuntimeApiMode = 'HSSL_MCAL_SUPERVISOR'"!][!//
    #define HSSL_RUN_TIME_API_MODE                 HSSL_SUPERVISOR_MODE
  [!ELSE!][!//
    #define HSSL_RUN_TIME_API_MODE                 HSSL_USER_MODE
  [!ENDIF!][!//
  #define HSSL_MULTI_SLAVE_MODE  ([!//
  [!IF "HsslGeneral/HsslMultiSlaveMode = 'true'"!][!//
    STD_ON[!//
  [!ELSE!][!//
    STD_OFF[!//
  [!ENDIF!][!//
  )

  /* Address pointer containing the address of the memory
  location containing the unique ID data */
  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      #define HSSL0_TIDADD_ADDR  ([!//
      [!"num:inttohex(HsslConfig/*[@index=$ChannelIndex]/HsslTargetIDAddr)"!]U)
    [!ELSE!][!//
      #define HSSL1_TIDADD_ADDR  ([!//
      [!"num:inttohex(HsslConfig/*[@index=$ChannelIndex]/HsslTargetIDAddr)"!]U)
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//

  /* DMA Transmit Channel Used for Multi Write */
  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!VAR "DmaChNum" = "(node:ref(HsslConfig/*[@index=$ChannelIndex]/HsslDmaMultiWriteChannelRef)/DmaChannelId)"!][!//
      #define HSSL0_DMA_MULTI_WRITE_CHANNEL_USED          ([!"$DmaChNum"!]U)
      [!IF "$NoOfHsslInstances != 2"!][!//
        #define HSSL_DMA_MULTI_WRITE_CHANNEL HSSL0_DMA_MULTI_WRITE_CHANNEL_USED
      [!ENDIF!][!//
      [!//
    [!ELSE!][!//
      [!VAR "DmaChNum" = "(node:ref(HsslConfig/*[@index=$ChannelIndex]/HsslDmaMultiWriteChannelRef)/DmaChannelId)"!][!//
      #define HSSL1_DMA_MULTI_WRITE_CHANNEL_USED          ([!"$DmaChNum"!]U)
      [!IF "$NoOfHsslInstances != 2"!][!//
        #define HSSL_DMA_MULTI_WRITE_CHANNEL HSSL1_DMA_MULTI_WRITE_CHANNEL_USED
      [!ENDIF!][!//
      [!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!//

  /* DMA Transmit Channel Used for Multi Write/multi read */
  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!VAR "DmaChNum" = "(node:ref(HsslConfig/*[@index=$ChannelIndex]/HsslDmaMultiReadTxChannelRef)/DmaChannelId)"!][!//
      #define HSSL0_DMA_MULTI_READ_TX_CHANNEL_USED          ([!"$DmaChNum"!]U)
      [!IF "$NoOfHsslInstances != 2"!][!//
        #define HSSL_DMA_MULTI_READ_TX_CHANNEL HSSL0_DMA_MULTI_READ_TX_CHANNEL_USED
      [!ENDIF!][!//
      [!//
    [!ELSE!][!//
      [!VAR "DmaChNum" = "(node:ref(HsslConfig/*[@index=$ChannelIndex]/HsslDmaMultiReadTxChannelRef)/DmaChannelId)"!][!//
      #define HSSL1_DMA_MULTI_READ_TX_CHANNEL_USED          ([!"$DmaChNum"!]U)
      [!IF "$NoOfHsslInstances != 2"!][!//
        #define HSSL_DMA_MULTI_READ_TX_CHANNEL HSSL1_DMA_MULTI_READ_TX_CHANNEL_USED
      [!ENDIF!][!//
      [!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!//

  /* DMA receive Channel Used for Multi Write/multi read */
  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!VAR "DmaChNum" = "(node:ref(HsslConfig/*[@index=$ChannelIndex]/HsslDmaMultiReadRxChannelRef)/DmaChannelId)"!][!//
      #define HSSL0_DMA_MULTI_READ_RX_CHANNEL_USED          ([!"$DmaChNum"!]U)
      [!IF "$NoOfHsslInstances != 2"!][!//
        #define HSSL_DMA_MULTI_READ_RX_CHANNEL HSSL0_DMA_MULTI_READ_RX_CHANNEL_USED
      [!ENDIF!][!//
      [!//
    [!ELSE!][!//
      [!VAR "DmaChNum" = "(node:ref(HsslConfig/*[@index=$ChannelIndex]/HsslDmaMultiReadRxChannelRef)/DmaChannelId)"!][!//
      #define HSSL1_DMA_MULTI_READ_RX_CHANNEL_USED          ([!"$DmaChNum"!]U)
      [!IF "$NoOfHsslInstances != 2"!][!//
        #define HSSL_DMA_MULTI_READ_RX_CHANNEL HSSL1_DMA_MULTI_READ_RX_CHANNEL_USED
      [!ENDIF!][!//
      [!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!//

  /* Memory Access Window and Protection Window definitions for HSSL */
  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!//
      #define HSSL0_ACCESS_WINDOW_START_ADDR0 ([!//
      [!"num:inttohex(HsslConfig/*[@index=$ChannelIndex]/HsslAcessWindowStartAddr0)"!]U)
      [!//
      #define HSSL0_ACCESS_WINDOW_START_ADDR1 ([!//
      [!"num:inttohex(HsslConfig/*[@index=$ChannelIndex]/HsslAcessWindowStartAddr1)"!]U)
      [!//
      #define HSSL0_ACCESS_WINDOW_START_ADDR2 ([!//
      [!"num:inttohex(HsslConfig/*[@index=$ChannelIndex]/HsslAcessWindowStartAddr2)"!]U)
      [!//
      #define HSSL0_ACCESS_WINDOW_START_ADDR3 ([!//
      [!"num:inttohex(HsslConfig/*[@index=$ChannelIndex]/HsslAcessWindowStartAddr3)"!]U)
      [!//
      #define HSSL0_ACCESS_WINDOW_END_ADDR0 ([!//
      [!"num:inttohex(HsslConfig/*[@index=$ChannelIndex]/HsslAcessWindowEndAddr0)"!]U)
      [!//
      #define HSSL0_ACCESS_WINDOW_END_ADDR1 ([!//
      [!"num:inttohex(HsslConfig/*[@index=$ChannelIndex]/HsslAcessWindowEndAddr1)"!]U)
      [!//
      #define HSSL0_ACCESS_WINDOW_END_ADDR2 ([!//
      [!"num:inttohex(HsslConfig/*[@index=$ChannelIndex]/HsslAcessWindowEndAddr2)"!]U)
      [!//
      #define HSSL0_ACCESS_WINDOW_END_ADDR3 ([!//
      [!"num:inttohex(HsslConfig/*[@index=$ChannelIndex]/HsslAcessWindowEndAddr3)"!]U)
      [!//
    [!ELSE!][!//
      #define HSSL1_ACCESS_WINDOW_START_ADDR0 ([!//
      [!"num:inttohex(HsslConfig/*[@index=$ChannelIndex]/HsslAcessWindowStartAddr0)"!]U)
      [!//
      #define HSSL1_ACCESS_WINDOW_START_ADDR1 ([!//
      [!"num:inttohex(HsslConfig/*[@index=$ChannelIndex]/HsslAcessWindowStartAddr1)"!]U)
      [!//
      #define HSSL1_ACCESS_WINDOW_START_ADDR2 ([!//
      [!"num:inttohex(HsslConfig/*[@index=$ChannelIndex]/HsslAcessWindowStartAddr2)"!]U)
      [!//
      #define HSSL1_ACCESS_WINDOW_START_ADDR3 ([!//
      [!"num:inttohex(HsslConfig/*[@index=$ChannelIndex]/HsslAcessWindowStartAddr3)"!]U)
      [!//
      #define HSSL1_ACCESS_WINDOW_END_ADDR0 ([!//
      [!"num:inttohex(HsslConfig/*[@index=$ChannelIndex]/HsslAcessWindowEndAddr0)"!]U)
      [!//
      #define HSSL1_ACCESS_WINDOW_END_ADDR1 ([!//
      [!"num:inttohex(HsslConfig/*[@index=$ChannelIndex]/HsslAcessWindowEndAddr1)"!]U)
      [!//
      #define HSSL1_ACCESS_WINDOW_END_ADDR2 ([!//
      [!"num:inttohex(HsslConfig/*[@index=$ChannelIndex]/HsslAcessWindowEndAddr2)"!]U)
      [!//
      #define HSSL1_ACCESS_WINDOW_END_ADDR3 ([!//
      [!"num:inttohex(HsslConfig/*[@index=$ChannelIndex]/HsslAcessWindowEndAddr3)"!]U)
      [!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//

  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!/* Determine the operating mode configured by the user */!][!//
    [!IF "HsslConfig/*[@index=$ChannelIndex]/HsslAcessRuleWindow0 = 'NO_ACCESS'"!][!//
      [!VAR "AccessMode" = "'HSSL_NO_ACCESS'"!][!//
    [!ELSEIF "HsslConfig/*[@index=$ChannelIndex]/HsslAcessRuleWindow0 = 'READ'"!][!//
      [!VAR "AccessMode" = "'HSSL_READ_ACCESS'"!][!//
    [!ELSEIF "HsslConfig/*[@index=$ChannelIndex]/HsslAcessRuleWindow0 = 'WRITE'"!][!//
      [!VAR "AccessMode" = "'HSSL_WRITE_ACCESS'"!][!//
    [!ELSEIF "HsslConfig/*[@index=$ChannelIndex]/HsslAcessRuleWindow0 = 'READ_WRITE'"!][!//
      [!VAR "AccessMode" = "'HSSL_READ_WRITE_ACCESS'"!][!//
    [!ENDIF!][!/* ./HsslAcessRuleWindow0 */!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!/* ------ Determine the Access Modes for Memory ----- */!]
      #define HSSL0_ACCESS_MODE_0   ([!"$AccessMode"!])
    [!ELSE!]
      #define HSSL1_ACCESS_MODE_0   ([!"$AccessMode"!])
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!/* Determine the operating mode configured by the user */!][!//
    [!IF "HsslConfig/*[@index=$ChannelIndex]/HsslAcessRuleWindow1 = 'NO_ACCESS'"!][!//
      [!VAR "AccessMode" = "'HSSL_NO_ACCESS'"!][!//
    [!ELSEIF "HsslConfig/*[@index=$ChannelIndex]/HsslAcessRuleWindow1 = 'READ'"!][!//
      [!VAR "AccessMode" = "'HSSL_READ_ACCESS'"!][!//
    [!ELSEIF "HsslConfig/*[@index=$ChannelIndex]/HsslAcessRuleWindow1 = 'WRITE'"!][!//
      [!VAR "AccessMode" = "'HSSL_WRITE_ACCESS'"!][!//
    [!ELSEIF "HsslConfig/*[@index=$ChannelIndex]/HsslAcessRuleWindow1 = 'READ_WRITE'"!][!//
      [!VAR "AccessMode" = "'HSSL_READ_WRITE_ACCESS'"!][!//
    [!ENDIF!][!/* ./HsslAcessRuleWindow1 */!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!/* ------ Determine the Access Modes for Memory ----- */!]
      #define HSSL0_ACCESS_MODE_1   ([!"$AccessMode"!])
    [!ELSE!]
      #define HSSL1_ACCESS_MODE_1   ([!"$AccessMode"!])
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!/* Determine the operating mode configured by the user */!][!//
    [!IF "HsslConfig/*[@index=$ChannelIndex]/HsslAcessRuleWindow2 = 'NO_ACCESS'"!][!//
      [!VAR "AccessMode" = "'HSSL_NO_ACCESS'"!][!//
    [!ELSEIF "HsslConfig/*[@index=$ChannelIndex]/HsslAcessRuleWindow2 = 'READ'"!][!//
      [!VAR "AccessMode" = "'HSSL_READ_ACCESS'"!][!//
    [!ELSEIF "HsslConfig/*[@index=$ChannelIndex]/HsslAcessRuleWindow2 = 'WRITE'"!][!//
      [!VAR "AccessMode" = "'HSSL_WRITE_ACCESS'"!][!//
    [!ELSEIF "HsslConfig/*[@index=$ChannelIndex]/HsslAcessRuleWindow2 = 'READ_WRITE'"!][!//
      [!VAR "AccessMode" = "'HSSL_READ_WRITE_ACCESS'"!][!//
    [!ENDIF!][!/* ./HsslAcessRuleWindow2 */!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!/* ------ Determine the Access Modes for Memory ----- */!]
      #define HSSL0_ACCESS_MODE_2   ([!"$AccessMode"!])
    [!ELSE!]
      #define HSSL1_ACCESS_MODE_2   ([!"$AccessMode"!])
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!/* Determine the operating mode configured by the user */!][!//
    [!IF "HsslConfig/*[@index=$ChannelIndex]/HsslAcessRuleWindow3 = 'NO_ACCESS'"!][!//
      [!VAR "AccessMode" = "'HSSL_NO_ACCESS'"!][!//
    [!ELSEIF "HsslConfig/*[@index=$ChannelIndex]/HsslAcessRuleWindow3 = 'READ'"!][!//
      [!VAR "AccessMode" = "'HSSL_READ_ACCESS'"!][!//
    [!ELSEIF "HsslConfig/*[@index=$ChannelIndex]/HsslAcessRuleWindow3 = 'WRITE'"!][!//
      [!VAR "AccessMode" = "'HSSL_WRITE_ACCESS'"!][!//
    [!ELSEIF "HsslConfig/*[@index=$ChannelIndex]/HsslAcessRuleWindow3 = 'READ_WRITE'"!][!//
      [!VAR "AccessMode" = "'HSSL_READ_WRITE_ACCESS'"!][!//
    [!ENDIF!][!/* ./HsslAcessRuleWindow3 */!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!/* ------ Determine the Access Modes for Memory ----- */!]
      #define HSSL0_ACCESS_MODE_3   ([!"$AccessMode"!])
    [!ELSE!]
      #define HSSL1_ACCESS_MODE_3   ([!"$AccessMode"!])
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!/* Determine the Refrence clock configured by the user */!][!//
    [!IF "HsslConfig/*[@index=$ChannelIndex]/HsslReferenceClock = 'HSSL_10MHZ'"!][!//
      [!VAR "RefClk" = "'HSSL_REFCLK_10MHZ'"!][!//
    [!ELSEIF "HsslConfig/*[@index=$ChannelIndex]/HsslReferenceClock = 'HSSL_20MHZ'"!][!//
      [!VAR "RefClk" = "'HSSL_REFCLK_20MHZ'"!][!//
    [!ELSEIF "HsslConfig/*[@index=$ChannelIndex]/HsslReferenceClock = 'HSSL_40MHZ'"!][!//
      [!VAR "RefClk" = "'HSSL_REFCLK_40MHZ'"!][!//
    [!ENDIF!][!/* ./Refrenceclock */!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!/* ------ Determine the Refrence clock ----- */!]
      #define HSSL0_REFRENCE_CLK   ([!"$RefClk"!])
    [!ELSE!]
      #define HSSL1_REFRENCE_CLK   ([!"$RefClk"!])
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!/* Determine the System clock frequency divider configured by the user */!][!//
    [!IF "HsslConfig/*[@index=$ChannelIndex]/HsslSystemClockDivider = 'SYSCLK_DIV_1'"!][!//
      [!VAR "SystemClk" = "'HSSL_SYSCLK_DIV_1'"!][!//
    [!ELSEIF "HsslConfig/*[@index=$ChannelIndex]/HsslSystemClockDivider = 'SYSCLK_DIV_2'"!][!//
      [!VAR "SystemClk" = "'HSSL_SYSCLK_DIV_2'"!][!//
    [!ELSEIF "HsslConfig/*[@index=$ChannelIndex]/HsslSystemClockDivider = 'SYSCLK_DIV_4'"!][!//
      [!VAR "SystemClk" = "'HSSL_SYSCLK_DIV_4'"!][!//
    [!ENDIF!][!/* ./SystemClockDivider */!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!/* ------ Determine the System clock ----- */!]
      #define HSSL0_SYSCLK_DIV   ([!"$SystemClk"!])
    [!ELSE!]
      #define HSSL1_SYSCLK_DIV   ([!"$SystemClk"!])
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!/* Determine the Master mode TX speed configured by the user */!][!//
    [!IF "HsslConfig/*[@index=$ChannelIndex]/HsslMasterTxSpeed = 'LOW_SPEED'"!][!//
      [!VAR "MTxSpeed" = "'HSSL_TX_LOW_SPEED'"!][!//
    [!ELSEIF "HsslConfig/*[@index=$ChannelIndex]/HsslMasterTxSpeed = 'HIGH_SPEED'"!][!//
      [!VAR "MTxSpeed" = "'HSSL_TX_HIGH_SPEED'"!][!//
    [!ENDIF!][!/* ./MasterTxSpeed */!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!/* ------ Determine the System clock ----- */!]
      #define HSSL0_MASTER_TX_SPEED   ([!"$MTxSpeed"!])
    [!ELSE!]
      #define HSSL1_MASTER_TX_SPEED   ([!"$MTxSpeed"!])
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
  [!CODE!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "0" TO "num:i($NoOfHsslInstances) -1"!][!//
    [!/* Determine the Master mode RX speed configured by the user */!][!//
    [!IF "HsslConfig/*[@index=$ChannelIndex]/HsslMasterRxSpeed = 'LOW_SPEED'"!][!//
      [!VAR "MRxSpeed" = "'HSSL_RX_LOW_SPEED'"!][!//
    [!ELSEIF "HsslConfig/*[@index=$ChannelIndex]/HsslMasterRxSpeed = 'MEDIUM_SPEED'"!][!//
      [!VAR "MRxSpeed" = "'HSSL_RX_MEDIUM_SPEED'"!][!//
    [!ELSEIF "HsslConfig/*[@index=$ChannelIndex]/HsslMasterRxSpeed = 'HIGH_SPEED'"!][!//
      [!VAR "MRxSpeed" = "'HSSL_RX_HIGH_SPEED'"!][!//
    [!ENDIF!][!/* ./MasterRxSpeed */!][!//
    [!IF "(HsslConfig/*[@index=$ChannelIndex]/HsslInstanceID) = 0"!][!//
      [!/* ------ Determine the System clock ----- */!]
      #define HSSL0_MASTER_RX_SPEED   ([!"$MRxSpeed"!])
    [!ELSE!]
      #define HSSL1_MASTER_RX_SPEED   ([!"$MRxSpeed"!])
    [!ENDIF!][!//
  [!ENDFOR!][!//
  [!ENDCODE!][!//
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
#endif /* end of HSSL_CFG_H */
[!ENDINDENT!]
