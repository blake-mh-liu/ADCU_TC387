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
**  FILENAME  : Dio_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 8.0.0                                                         **
**                                                                            **
**  DATE      : 2020-05-05                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Dio.bmd                                           **
**                                                                            **
**  VARIANT   : Variant LT                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={E904F353-1698-4047-B0E7-3F3F73EB6811}]    **
**                                                                            **
**  DESCRIPTION  : Code template header file for Dio Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Dio Driver, AUTOSAR Release 4.2.2     **
**                     and AUTOSAR Release 4.4.0                              **
**                                                                            **
** MAY BE CHANGED BY USER : no                                                **
**                                                                            **
*****************************************************************************/!]
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
**  FILENAME  : Dio_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 8.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]         !!!IGNORE-LINE!!!                **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]             !!!IGNORE-LINE!!!              **
**                                                                            **
**  BSW MODULE DECRIPTION : Dio.bmd                                           **
**                                                                            **
**  VARIANT   : Variant LT                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Dio configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Dio Driver, AUTOSAR Release 4.2.2     **
**                     and AUTOSAR Release 4.4.0                              **
**                                                                            **
** MAY BE CHANGED BY USER : no                                                **
**                                                                            **
*******************************************************************************/
#ifndef DIO_CFG_H
#define DIO_CFG_H
[!//
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Dio')"!][!//
  [!//
  [!/* Include Code Generator Macros */!][!//
    [!NOCODE!][!//
      [!INCLUDE "..\Dio.m"!][!//
    [!ENDNOCODE!][!//
  [!//
  [!/* Verify the validity of DIO configuration */!][!//
  [!CALL "Dio_VerifyDioConfig"!][!//
  [!//
  /*
   Notes:
   - The runtime configuration is handled by the Port Driver Module.
   - The configuration and usage of the DIO Driver Module is adapted to
     the microcontroller and ECU.

  */

  /*Version check macros */
  [!/* [cover parentID={FA0C5412-3371-4daf-A193-E32AF8B92D6C}] [/cover]*/!][!//
  [!/* [cover parentID={79DA914F-1707-4990-931A-409F75720837}] [/cover]*/!][!//
  [!/* [cover parentID={6B1D8C3C-948D-460e-AD52-0B28873EEF47}] [/cover]*/!][!//
  [!NOCODE!][!//
    [!VAR "AsMajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
    [!VAR "AsMinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
    [!VAR "AsRevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
  [!ENDNOCODE!][!//
  #define DIO_AR_RELEASE_MAJOR_VERSION     ([!"$AsMajorVersion"!]U)
  #define DIO_AR_RELEASE_MINOR_VERSION     ([!"$AsMinorVersion"!]U)
  #define DIO_AR_RELEASE_REVISION_VERSION  ([!"$AsRevisionVersion"!]U)

  [!/* [cover parentID={45F074D2-9470-462b-8F87-5D6A6C368A73}] [/cover]*/!][!//
  [!/* [cover parentID={F8D3ECE9-C1DA-4810-9229-E0B0163069DE}] [/cover]*/!][!//
  [!/* [cover parentID={F428AA83-DA70-468b-894B-53DC215E266A}] [/cover]*/!][!//
  [!NOCODE!][!//
    [!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
    [!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
    [!VAR "SwRevisionVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
  [!ENDNOCODE!][!//

  #define DIO_SW_MAJOR_VERSION  ([!"$SwMajorVersion"!]U)
  #define DIO_SW_MINOR_VERSION  ([!"$SwMinorVersion"!]U)
  #define DIO_SW_PATCH_VERSION  ([!"$SwRevisionVersion"!]U)

  /*******************************************************************************
  **                      Includes                                              **
  *******************************************************************************/

  /*******************************************************************************
  **                      Global Macro Definitions                              **
  *******************************************************************************/

  /*                          Container: DioGeneral                            */
  /*

    Pre-processor switch to enable/disable detection of Development errors.
      - if defined ON, Development error detection is enabled
      - if defined OFF, Development error detection is disabled
  */
  [!/* [cover parentID={77FB036C-3267-4076-BF13-2B2A1E6213E3}] [/cover]*/!][!//
  #define DIO_DEV_ERROR_DETECT                [!//
  [!CALL "Dio_ConfigSwitch","nodeval" = "DioGeneral/DioDevErrorDetect"!][!//

  /*
    Pre-Compiler switch to include the API Dio_GetVersionInfo()
    - if defined ON, Dio_GetVersionInfo API available
    - if defined OFF, Dio_GetVersionInfo API not available
  */
  [!/* [cover parentID={220B3842-B43C-4a71-9B5E-B1759BF3CEFF}] [/cover]*/!][!//
  #define DIO_VERSION_INFO_API                [!//
  [!CALL "Dio_ConfigSwitch","nodeval" = "DioGeneral/DioVersionInfoApi"!][!//

  /*
    Pre-Compiler switch to include the API Dio_FlipChannel()
    - if defined ON, Dio_FlipChannel API available
    - if defined OFF, Dio_FlipChannel API not available
  */
  [!/* [cover parentID={DD330A94-E11A-4534-8B16-656FA7C87E75}] [/cover]*/!][!//
  #define DIO_FLIP_CHANNEL_API                [!//
  [!CALL "Dio_ConfigSwitch","nodeval" = "DioGeneral/DioFlipChannelApi"!][!//
  
  #define DIO_MASKED_WRITE_PORT_API           [!//
  [!CALL "Dio_ConfigSwitch","nodeval" = "DioGeneral/DioMaskedWritePortApi"!][!//
  /*
    Pre-Compiler switch to include the Safety Check
  */
  [!/* [cover parentID={5BDEC6C7-0D75-41c3-AB32-167C180F8FCE}] [/cover]*/!][!//  
  #define DIO_SAFETY_ENABLE                [!//
  [!CALL "Dio_ConfigSwitch","nodeval" = "DioGeneral/DioSafetyEnable"!][!//

  /* The following macros are available only if development error detection
    is enabled */
  [!IF "(DioGeneral/DioDevErrorDetect = 'true')or(DioGeneral/DioSafetyEnable = 'true')"!][!//
  /* Definition to specify the ports available on the microcontroller
    Bit value = 0 implies the port is not available
    Bit value = 1 implies the port is available
    Bit 0 is for Port 0, Bit 1 is for Port 1, ... , Bit 31 is for Port 31 */
    [!CALL "Dio_GetPortsAvailable00to31"!][!//

    /* Definition to specify the ports available on the microcontroller
    Bit value = 0 implies the port is not available
    Bit value = 1 implies the port is available
    Bit 0 is for Port 32, Bit 1 is for Port 33, ... , Bit 31 is for Port 63 */
    [!CALL "Dio_GetPortsAvailable32to63"!][!//

    /* Definition to specify the ports that are read only ports on the microcontroller
      Bit value = 0 implies the port readable/writable
      Bit value = 1 implies the port is read only port
      Bit 0 is for Port 0, Bit 1 is for Port 1, ... , Bit 31 is for Port 31 */
    [!CALL "Dio_GetReadOnlyPorts00to31"!][!//

    /* Definition to specify the ports that are read only ports on the microcontroller
      Bit value = 0 implies the port readable/writable
      Bit value = 1 implies the port is read only port
      Bit 0 is for Port 32, Bit 1 is for Port 33, ... , Bit 31 is for Port 63 */
    [!CALL "Dio_GetReadOnlyPorts32to63"!][!//

    /* Value of the most significant pin on the port
      Note: In case of no pins on a port, the value is kept 0 */
    [!CALL "Dio_GetPortMSPin"!][!//
  [!ENDIF!][!//  DioDecerrorDetect
  /* Macro to define the maximum port available */
  [!CALL "Dio_GetMaxAvailablePort"!][!//

  [!/* Macro to define the values to mask for the port pins */!][!//
  [!CALL "Dio_GetMaskForPortPins"!][!//

  [!/* Macro to define maximum valid port pin */!][!//
  [!CALL "Dio_GetMaxValidPortPin"!][!//

  /* Macro to define the No of channel groups configured */
  [!/* [cover parentID={90C0C6CD-C68E-4abb-BBF8-97D0100F4DA9}] [/cover]*/!][!//
  [!CALL "Dio_GetNumOfDioChannelGroupsConfigured"!][!//
  #define DIO_CHANNELGROUPCOUNT               ([!"$NumOfGroups"!]U)


  /*******************************************************************************
  **                           Global Symbols                                   **
  *******************************************************************************/

  /*
    Symbolic names for DIO Channels, Port & Channel groups
  */

  /*
                       Symbolic names for Channels
  */
  [!INDENT "0"!]
  [!FOR "PortNumber" = "num:i(0)" TO "ecu:get('Dio.MaxAvailablePort')"!][!//
    [!//
    [!IF "contains(ecu:get('Dio.AvailablePorts'),concat('_',$PortNumber,'_'))"!][!//
      [!CALL "Dio_GetDioChannelSymbolicNames","PortNum" = "$PortNumber"!][!//
    [!ENDIF!][!//
    [!//
  [!ENDFOR!]
  [!ENDINDENT!]
  /*
                      Symbolic names for DIO ports
  */
  [!CALL "Dio_GetDioPortSymbolicNames"!][!//

  /*
     User Defined Symbolic Names for the DIO Ports, Channels & Channel Groups
  */
  [!/* [cover parentID={44FD85BA-1493-46bf-A6A7-DA81CD2EF847}] [/cover]*/!][!//
  [!/* [cover parentID={E007630E-10E4-423b-9DB8-79DCA7C4478B}] [/cover]*/!][!//
  [!/* [cover parentID={BEFFD203-EE16-478d-9D2D-06EB3572B089}] [/cover]*/!][!//
  [!CALL "Dio_GetUserDefinedSymbolicNames"!][!//



  /*******************************************************************************
  **                      Global Constant Declarations                          **
  *******************************************************************************/
  [!VAR "configstruct" = "as:name(as:modconf('Dio')[1]/DioConfig)"!][!//
  #define DIO_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  #include "Dio_MemMap.h"

  extern const struct Dio_ConfigType Dio_Config; 
  #define DIO_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  /* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines 
  Dio_Memmap.h header is included without safegaurd.*/
  #include "Dio_MemMap.h"
  /*******************************************************************************
  **                      Global Data Type                                      **
  *******************************************************************************/
  [!ENDSELECT!]
  /* End of DIO_CFG_H */
  #endif
 [!ENDINDENT!]

