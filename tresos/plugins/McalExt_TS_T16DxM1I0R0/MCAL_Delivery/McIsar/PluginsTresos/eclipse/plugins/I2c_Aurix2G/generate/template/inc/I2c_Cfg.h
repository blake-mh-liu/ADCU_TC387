[!/*****************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2019)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : I2c_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 4.0.0                                                         **
**                                                                            **
**  DATE      : 2019-07-08                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : I2c.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR      : Infineon Technologies                                       **
**                                                                            **
**  DESCRIPTION : This file contains                                          **
**                Code template for I2c_Cfg.h file                            **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: No                                       **
**                                                                            **
*******************************************************************************/!][!//
[!//
/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2018)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : I2c_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 4.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]    !!!IGNORE-LINE!!!                     **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]    !!!IGNORE-LINE!!!                       **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : I2C configuration generated out of ECU configuration       **
**                 file (I2c.bmd/.xdm)                                        **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: No                                       **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                                                                            **
**  TRACEBILITY :                                                             **
**                                                                            **
*******************************************************************************/
[!AUTOSPACING!]
#ifndef I2C_CFG_H
#define I2C_CFG_H

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
[!INDENT "0"!][!//
  [!//
  [!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!]
  [!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!]
  [!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!]
  [!VAR "NewString" = "text:replaceAll($moduleReleaseVer,"\.",'')"!]
  [!//
  [!IF "$MajorVersion = num:i(4)"!]
    #define I2C_AR_RELEASE_MAJOR_VERSION  ([!"$MajorVersion"!]U)
    #define I2C_AR_RELEASE_MINOR_VERSION  ([!"$MinorVersion"!]U)
    #define I2C_AR_RELEASE_REVISION_VERSION  ([!"$RevisionVersion"!]U)
  [!ENDIF!]

  [!//
  [!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!]
  [!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!]
  [!VAR "SwRevisionVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!]
  #define I2C_SW_MAJOR_VERSION   ([!"$SwMajorVersion"!]U)
  #define I2C_SW_MINOR_VERSION   ([!"$SwMinorVersion"!]U)
  #define I2C_SW_PATCH_VERSION   ([!"$SwRevisionVersion"!]U)

  [!//
  [!/* Find the Autosar version number */!][!//
  [!IF "$NewString = num:i(402)"!]
    [!VAR "AS_Version" = "num:i(402)"!]
  [!ELSEIF "$NewString = num:i(321)"!]
    [!VAR "AS_Version" = "num:i(321)"!]
  [!ELSE!][!//
    [!VAR "AS_Version" = "num:i(0)"!]
  [!ENDIF!]
  [!//
  [!/*
  MACRO: CG_ConfigSwitch
  Macro to generate configuration switch values STD_ON/STD_OFF based on configuration
  true/false
  */!][!//
  [!MACRO "CG_ConfigSwitch", "node" = ""!]
    [!IF "$node = 'true'"!]
      (STD_ON)
    [!ELSE!]
      (STD_OFF)
    [!ENDIF!]
  [!ENDMACRO!]
  [!MACRO "CG_ConfigSwitch_Number", "node" = ""!]
    [!IF "$node = '1'"!]
      (STD_ON)
    [!ELSE!]
      (STD_OFF)
    [!ENDIF!]
  [!ENDMACRO!]
  [!//
  #define I2C_DEV_ERROR_DETECT  [!//
  [!CALL "CG_ConfigSwitch","node" = "I2cGeneral/I2cDevErrorDetect"!]

  #define I2C_VERSION_INFO_API  [!//
  [!CALL "CG_ConfigSwitch","node" = "I2cGeneral/I2cVersionInfoApi"!]

  [!IF "I2cGeneral/I2cInitDeInitApiMode = 'I2C_MCAL_USER1'"!][!//
    #define I2C_INIT_DEINIT_API_MODE  (I2C_MCAL_USER1)

  [!ELSE!][!//
    #define I2C_INIT_DEINIT_API_MODE  (I2C_MCAL_SUPERVISOR)

  [!ENDIF!][!//


  [!VAR "MaxChannels" = "num:i(count(I2cConfigSet/I2cChannelConfiguration/*))"!]
  [!//
  #define I2C_MAX_CHANNELS ([!"num:i($MaxChannels)"!]U)

  #define I2C_REG_ADDR\
  [!//
  [!FOR "Hwnumber" = "0" TO "num:i(ecu:get('I2c.NoOfAvailableI2c')) - 1"!][!//
    [!INDENT "24"!][!//
                          &MODULE_I2C[!"$Hwnumber"!][!//
    [!ENDINDENT!][!//
   [!IF "$Hwnumber != num:i(ecu:get('I2c.NoOfAvailableI2c')) - 1"!],\
   [!ENDIF!][!//
  [!ENDFOR!][!//

  #define I2C_MAX_HW_UNIT ([!"num:i(ecu:get('I2c.NoOfAvailableI2c'))"!])
[!ENDINDENT!][!//

#endif  /* I2C_CFG_H */

