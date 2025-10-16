[!AUTOSPACING!]
[!INDENT "0"!]
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
**  FILENAME  : Port_Cfg.h                                                    **
**                                                                            **
**  VERSION   : 11.0.0                                                         **
**                                                                            **
**  DATE      : 2021-03-14                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Port.bmd                                          **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY :[cover parentID={E4D80828-0019-410c-9131-6649B5F90215}]     **
**                                                                            **
**  DESCRIPTION  : Code template header file for Port Driver                  **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Port Driver, AUTOSAR Release 4.2.2    **
**                     and AUTOSAR Release 4.4.0                              **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*****************************************************************************/!][!//
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
**  FILENAME  : Port_Cfg.h                                                    **
**                                                                            **
**  VERSION   : 11.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]              !!!IGNORE-LINE!!!           **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                !!!IGNORE-LINE!!!           ** 
**                                                                            **
**  BSW MODULE DECRIPTION : Port.bmd                                          **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Port configuration generated out of ECUC file              **
**                                                                            **
**  SPECIFICATION(S) : Specification of Port Driver, AUTOSAR Release 4.2.2    **
**                     and AUTOSAR Release 4.4.0                              **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef PORT_CFG_H
#define PORT_CFG_H
[!CR!]
[!//
[!//
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Port')[1]"!][!//. 
  [!//
  [!NOCODE!][!//
    [!INCLUDE "..\Port.m"!][!//
  [!ENDNOCODE!][!//
  [!//
  [!NOCODE!][!//
  [!VAR "AsMajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
  [!VAR "AsMinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
  [!VAR "AsRevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
  [!ENDNOCODE!][!//
  /* AUTOSAR specification version numbers */
  [!/*[cover parentID={CE649090-1A2D-408e-86D7-397A88FE3947}][/cover]*/!][!//
  #define PORT_AR_RELEASE_MAJOR_VERSION  ([!"$AsMajorVersion"!]U)
  [!/*[cover parentID={D7438673-7FDB-470b-ADA9-513FEE493F30}][/cover]*/!][!//
  #define PORT_AR_RELEASE_MINOR_VERSION  ([!"$AsMinorVersion"!]U)
  [!/*[cover parentID={8A5EB5FE-02EF-4d11-A2BE-66E293347829}][/cover]*/!][!//
  #define PORT_AR_RELEASE_REVISION_VERSION ([!"$AsRevisionVersion"!]U)
  [!NOCODE!][!//
  [!CR!]
  [!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
  [!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
  [!VAR "SwRevisionVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
  [!ENDNOCODE!] [!//
  /* Vendor specific implementation version information */
  [!/*[cover parentID={A13F25C0-DF24-4d91-B80A-5DBC600B3422}][/cover]*/!][!//
  #define PORT_SW_MAJOR_VERSION  ([!"$SwMajorVersion"!]U)
  [!/*[cover parentID={063CE33B-32FC-436f-9A5E-47226CC9DB70}][/cover]*/!][!//
  #define PORT_SW_MINOR_VERSION  ([!"$SwMinorVersion"!]U)
  [!/*[cover parentID={1E817267-DC5D-49b3-B5BD-614CF698808B}][/cover]*/!][!//
  #define PORT_SW_PATCH_VERSION  ([!"$SwRevisionVersion"!]U)
  /*******************************************************************************
  **                      Includes                                              **
  *******************************************************************************/
  /*******************************************************************************
  **                      Global Macro Definitions                              **
  *******************************************************************************/
  /*
  Container : PortGeneralConfiguration
  */
  [!/*[cover parentID={E71D3D86-E417-4ec2-8CE1-AB85423F22C8}][/cover]*/!][!//
  /*
    Configuration: PORT_DEV_ERROR_DETECT
    - if STD_ON, DET is Enabled 
    - if STD_OFF, DET is Disabled 
  */
  #define PORT_DEV_ERROR_DETECT       [!//
  [!CALL "Port_ConfigSwitch","node" = "PortGeneral/PortDevErrorDetect"!][!//
  /*
    Configuration: PORT_VERSION_INFO_API 
    - if STD_ON,  Function Port_GetVersionInfo is available  
    - if STD_OFF, Function Port_GetVersionInfo is not available 
  */
  #define PORT_VERSION_INFO_API       [!//
  [!CALL "Port_ConfigSwitch","node" = "PortGeneral/PortVersionInfoApi"!][!//
  /*
    Configuration: PORT_SET_PIN_MODE_API 
    - if STD_ON,  Function Port_SetPinMode is available  
    - if STD_OFF, Function Port_SetPinMode is not available 
  */
  [!/*[cover parentID={0552C05C-931B-4cb3-A833-7F8AA492DE1C}][/cover]*/!]
  #define PORT_SET_PIN_MODE_API       [!//
  [!CALL "Port_ConfigSwitch","node" = "PortGeneral/PortSetPinModeApi"!][!//
  /*
    Configuration: PORT_SET_PIN_DIRECTION_API
    - if STD_ON,  Function Port_SetPinDirection is available  
    - if STD_OFF, Function Port_SetPinDirection is not available 
  */
  [!/*[cover parentID={7BC3B15F-4AE7-4635-AF9C-600CF7D3AA5E}][/cover]*/!]
  #define PORT_SET_PIN_DIRECTION_API  [!//
  [!CALL "Port_ConfigSwitch","node" = "PortGeneral/PortSetPinDirectionApi"!][!//
  /*
    Configuration: PORT_INIT_API_MODE:
    -User Mode Macro for Init API
  */
  [!IF "PortGeneral/PortInitApiMode='PORT_MCAL_SUPERVISOR'"!][!//
    #define PORT_INIT_API_MODE                (PORT_MCAL_SUPERVISOR)
  [!ELSE!][!//
    #define PORT_INIT_API_MODE                (PORT_MCAL_USER1)
  [!ENDIF!][!//
  [!/*[cover parentID={9DC440F4-3312-470d-988B-5DD0560CF620}][/cover]*/!]
  /*
    Configuration: PortSafetyEnable  
    - if STD_ON, Safety is Enabled 
    - if STD_OFF, Safety  is Disabled 
  */
  #define PORT_SAFETY_ENABLE    [!//
  [!CALL "Port_ConfigSwitch","node" = "PortGeneral/PortSafetyEnable  "!][!//
  /*
    Configuration: PortInitCheckApi  
    - if STD_ON, PortInitCheckApi is available 
    - if STD_OFF, PortInitCheckApi is not available 
  */
  #define PORT_INIT_CHECK_API    [!//
  [!CALL "Port_ConfigSwitch","node" = "PortGeneral/PortInitCheckApi  "!][!//
  
   /*Macro for the constants*/
  [!NOCODE!][!//
  [!VAR "EmergencyDataOfs" = "num:i(7)"!][!//
  [!IF "PortGeneral/PortSetPinDirectionApi='true'"!][!//
  [!VAR "EmergencyDataOfs" = "num:i(12)"!][!//
  [!ENDIF!][!//
  
  [!IF "PortGeneral/PortSetPinModeApi='true'"!][!//
  [!VAR "EmergencyDataOfs" = "num:i($EmergencyDataOfs + num:i(1))"!][!//
  [!ENDIF!][!//
  [!ENDNOCODE!][!//
  
  #define PORT_DATA_OFS_EMER                ([!"$EmergencyDataOfs"!]U)
  
  [!/*[cover parentID={C717DEFF-8B39-4892-A41C-2B3E58B68CD9}][/cover]*/!]                                             
  /* Definition to specify the ports available on the microcontroller
   -Bit value = 0 implies the port is not available
   -Bit value = 1 implies the port is available
   -Bit 0 is for Port 0, Bit 1 is for Port 1, ... , Bit 31 is for Port 31 
  */
  [!CALL "Port_GetAvailablePorts00to31"!][!//
  /* Definition to specify the ports available on the microcontroller
   -Bit value = 0 implies the port is not available
   -Bit value = 1 implies the port is available
   -Bit 0 is for Port 32, Bit 1 is for Port 33, ... , Bit 8 is for Port 40 
  */
  [!/*[cover parentID={95D87135-CBED-4f1a-850F-F3AF95E5E80A}][/cover]*/!]
  [!CALL "Port_GetAvailablePorts32to63"!][!//
  /* Definition to specify the ports that are read only ports on the
    microcontroller
  -Bit value = 0 implies the port readable/writable
  -Bit value = 1 implies the port is read only port
  -Bit 0 is for Port 0, Bit 1 is for Port 1, ... , Bit 31 is for Port 31 
  */
  [!/*[cover parentID={AE9AA22C-77B1-4755-9215-1F383B144D81}][/cover]*/!][!//
  [!CALL "Port_ReadOnlyPorts00to31"!][!//
  /* Definition to specify the ports that are read only ports on the
    microcontroller
  -Bit value = 0 implies the port readable/writable
  -Bit value = 1 implies the port is read only port
  -Bit 0 is for Port 32, Bit 1 is for Port 33, ... , Bit 8 is for Port 40 
  */
  [!/*[cover parentID={E580C8DD-E32E-4bbd-8B6D-B108E2C40031}][/cover]*/!][!//
  [!CALL "Port_ReadOnlyPorts32to63"!][!//
  /* Maximum Port Number(Hex) */
  #define PORT_MAX_NUMBER             ([!"num:i(ecu:get('Port.MaxAvailablePort'))"!]U)
  /* Maximum PortPinID */
  
  #define PORT_MAX_PIN_ID             ([!"num:inttohex(bit:or(bit:shl(num:i(ecu:get('Port.MaxAvailablePort')),num:i(4)),num:i(15)))"!]U)
  /* Max Port Number available */
  
  #define PORT_TOTAL_AVAILABLE_PORTS   (16U)
  /* Max LPCR Register available */
  
  #define PORT_MAX_LPCR_REG           ([!"ecu:get('Port.MaxLPCRReg')"!]U)
  /*Macro that defines the derivate for errata PORTS_TC.H012 */
  [!/*[cover parentID={71A130D8-5180-48e0-8FE2-526CAE86BA9F}][/cover]*/!][!//
  [!NOCODE!][!//
  [!VAR "rel_derivate"= "(ecu:get('Rel.Derivate'))"!]
  [!VAR "Port14LvdsRxEnable" = "num:i(0)"!]
  [!IF "$rel_derivate = '_TRICORE_TC387' or $rel_derivate = '_TRICORE_TC397_ADAS' or $rel_derivate = '_TRICORE_TC397'"!][!//
  [!CALL "Port_Port14LVDSPinPair9_10Available"!][!//
  [!ENDIF!][!//  
  [!ENDNOCODE!][!//
  [!IF "$Port14LvdsRxEnable = num:i(1)"!][!//
   #define PORT14_PDISC_MASK            (0x0800U)
  [!ELSE!][!//
    #define PORT14_PDISC_MASK             (0U)
  [!ENDIF!][!//  
  
  /* Definition to specify the ports that are LVDS ports on the
    microcontroller
   -Bit value = 0 implies the port supports LVDS
   -Bit value = 1 implies the port does not support LVDS
   -Bit 0 is for Port 0, Bit 1 is for Port 1, ... , Bit 31 is for Port 31
  */
  [!/*[cover parentID={E42698F3-AC0B-481a-805B-49F8054F12B4}][/cover]*/!][!//
  [!CALL "Port_GetLVDSPorts00to31"!][!//
  /* Definition to specify the ports that are LVDS ports on the
    microcontroller
   -Bit value = 0 implies the port supports LVDS
   -Bit value = 1 implies the port does not support LVDS
   -Bit 0 is for Port 32, Bit 1 is for Port 33, ... , Bit 8 is for Port 40 
  */
  [!/*[cover parentID={1EECD8EB-70DD-40b8-89E4-AF2E14BE1042}][/cover]*/!][!//
  [!CALL "Port_GetLVDSPorts32to63"!][!//
  /* Definition to specify the ports that support PCSR on the
    microcontroller
   -Bit value = 0 implies the port supports PCSR
   -Bit value = 1 implies the port does not support PCSR
   -Bit 0 is for Port 0, Bit 1 is for Port 1, ... , Bit 31 is for Port 31
  */
  [!/*[cover parentID={58785DDD-C144-4201-B590-1011DEF50F08}][/cover]*/!][!//
  [!CALL "Port_GetPCSRPorts00to31"!][!//
  /* Definition to specify the ports that PCSR on the
  microcontroller
   -Bit value = 0 implies the port supports PCSR
   -Bit value = 1 implies the port does not support PCSR
   -Bit 0 is for Port 32, Bit 1 is for Port 33, ... , Bit 8 is for Port 40 
  */
  [!/*[cover parentID={CA94CBCD-D8DB-41af-B55B-03E43E4F2279}][/cover]*/!][!//
  [!CALL "Port_GetPCSRPorts32to63"!][!//
  /* Definitions to specify the pins available in the port 
   -Bit value = 0 implies the pin is not available
   -Bit value = 1 implies the pin is available
   -Bit 0 is for Pin 0, Bit 1 is for Pin 1, ... , Bit 15 is for Pin 15
  */
  [!/*[cover parentID={F7B62B30-0F8E-43b2-A1D7-6115470AD969}][/cover]*/!][!//
  [!CALL "Port_GetAvailablePortPins"!][!//
  /* Definition to specify the ports that support PDISC on the
    microcontroller
   -Bit value = 0 implies the port supports PDISC
   -Bit value = 1 implies the port does not support PDISC
   -Bit 0 is for Port 0, Bit 1 is for Port 1, ... , Bit 31 is for Port 31
  */
  [!CALL "Port_GetPDISCPorts00to31"!][!//
  /* Definition to specify the ports that PDISC on the
    microcontroller
   -Bit value = 0 implies the port supports PDISC
   -Bit value = 1 implies the port does not support PDISC
   -Bit 0 is for Port 32, Bit 1 is for Port 33, ... , Bit 8 is for Port 40 
  */
  [!CALL "Port_GetPDISCPorts32to63"!][!//
  /********************************************************************************
  **                      Global Symbols                                        **
  *******************************************************************************/
  /* 
  User Defined Symbolic names of all port pins Port_ConfigSet
  */
  [!FOR "PortNumber" = "num:i(0)" TO "num:i(ecu:get('Port.MaxAvailablePort'))"!][!//
    [!//
    [!IF "($PortNumber = text:split(ecu:get('Port.AvailablePorts'), ' ' ))"!][!//
      [!CALL "Port_GetPortPinSymbolicName","port" = "$PortNumber"!][!//
    [!ENDIF!]
  [!ENDFOR!]
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
  /*******************************************************************************
  **                      Global Inline Function Definitions                    **
  *******************************************************************************/
  #endif /* PORT_CFG_H */
[!ENDSELECT!]
[!ENDINDENT!] 
