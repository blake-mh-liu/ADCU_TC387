[!NOCODE!]
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
**  FILENAME  : McalLib_Cfg.h                                                 **
**                                                                            **
**  VERSION   : 11.0.0                                                        **
**                                                                            **
**  DATE      : 2023-05-16                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : McalLib.bmd                                       **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID]                                           **
**                                                                            **
**  DESCRIPTION  : Code template header file for Mcal Library                 **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Mcal Library                          **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*****************************************************************************/!]
[!ENDNOCODE!][!//
[!AUTOSPACING!][!//
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
**  FILENAME  : McalLib_Cfg.h                                                 **
**                                                                            **
**  VERSION   : 11.0.0                                                        **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]             !!!IGNORE-LINE!!!            **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]               !!!IGNORE-LINE!!!            **
**                                                                            **
**  BSW MODULE DECRIPTION : McalLib.bmd                                       **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : McalLib configuration generated out of ECUC file           **
**                                                                            **
**  SPECIFICATION(S) : Specification of McalLib Driver                        **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
[!/*[cover parentID={F6A194AF-8C7D-4aad-9FB1-E591B813604E}][/cover]*/!][!//
#ifndef MCALLIB_CFG_H
#define MCALLIB_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
[!NOCODE!][!//
  [!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
  [!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
  [!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
[!ENDNOCODE!][!//
[!/*[cover parentID={9AE124B7-37AC-4a67-857D-D35F06761F59}][/cover]*/!][!//
#define MCALLIB_AR_RELEASE_MAJOR_VERSION      ([!"$MajorVersion"!]U)
[!/*[cover parentID={20CA2AB7-21D4-4dcd-B61D-57AE97F1ADCA}][/cover]*/!][!//
#define MCALLIB_AR_RELEASE_MINOR_VERSION      ([!"$MinorVersion"!]U)
[!/*[cover parentID={87A9CA3A-7E7B-4e19-9EE0-8142E70784B3}][/cover]*/!][!//
#define MCALLIB_AR_RELEASE_REVISION_VERSION   ([!"$RevisionVersion"!]U)
[!NOCODE!][!//
  [!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
  [!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
  [!VAR "SwPatchVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
[!ENDNOCODE!][!//
[!/*[cover parentID={68B5D94B-EAAB-45b8-942A-DFE7235FC973}][/cover]*/!][!//
#define MCALLIB_SW_MAJOR_VERSION              ([!"$SwMajorVersion"!]U)
[!/*[cover parentID={2F720BF2-F889-4c6d-88E8-A429DFF2F9A2}][/cover]*/!][!//
#define MCALLIB_SW_MINOR_VERSION              ([!"$SwMinorVersion"!]U)
[!/*[cover parentID={30B056FE-4EED-4a16-8AC4-21FDDBA9275B}][/cover]*/!][!//
#define MCALLIB_SW_PATCH_VERSION              ([!"$SwPatchVersion"!]U)

/*Number of cores available*/
[!/*[cover parentID={E6A3B6D0-1D03-43d0-A080-91CC4B3FA5FB}][/cover]*/!][!//
#define MCAL_NO_OF_CORES              ([!"num:inttohex(ecu:get('Mcu.NoOfCoreAvailable'))"!]U)
/* Number of active cores available */
[!/*[cover parentID={C99428A8-76A8-43d8-8889-F11AA3D60CD7}][/cover]*/!][!//
#define MCAL_NO_OF_ACTIVE_CORES       ([!"num:inttohex(as:modconf('ResourceM')[1]/ResourceMMcalConfig/*[1]/ResourceMNumberOfActiveCores)"!]U)

/* Backup clock frequency in MHz */
[!/*[cover parentID={96A719FE-796E-4832-9318-7C363CF66A1D}][/cover]*/!][!//
#define MCAL_BACKUP_FREQUENCY         ([!"num:inttohex(ecu:get('McalLib.BackupClockFreq'))"!]U)

/* Global PSPR base address */
[!/*[cover parentID={3D07BBDD-A861-49c0-A6EA-A918D645D0A6}][/cover]*/!][!//
#define MCAL_PSPR0_GLOBAL_BASE_ADDR   ([!"num:inttohex(ecu:get('McalLib.PsprCore0StartAddr'))"!]U)
[!NOCODE!][!//
  [!/*[cover parentID={8C7162AA-6630-4ae6-95D4-B09D4DB05A04}][/cover]*/!][!//
  [!/*[cover parentID={C46F068A-442E-4637-B90F-12710417A4CD}][/cover]*/!][!//
  [!/*[cover parentID={ED499666-E048-4ced-BDB3-2E157C2AC0FA}][/cover]*/!][!//
  [!/*[cover parentID={C1EE2273-CE94-41e2-A3BF-162C4D9A833E}][/cover]*/!][!//
  [!/*[cover parentID={D4993593-6B34-4aad-B920-1C6FA5DC9F3F}][/cover]*/!][!//
  [!FOR "CpuID" = "num:i(1)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable') - num:i(1))"!][!//
    [!VAR "CurrCoreExists" = "concat('Mcu.fCPU', $CpuID, 'Exists')"!][!//
    [!VAR "PsprMacro" = "concat('MCAL_PSPR', $CpuID, '_GLOBAL_BASE_ADDR')"!][!//
    [!VAR "PsprCurrCoreStartAddr" = "concat('McalLib.PsprCore', $CpuID, 'StartAddr')"!][!//
    [!IF "ecu:get($CurrCoreExists) = 'true'"!][!//
      [!CODE!][!//
        [!INDENT "0"!][!//
          #define [!"$PsprMacro"!]   ([!"num:inttohex(ecu:get($PsprCurrCoreStartAddr))"!]U)
        [!ENDINDENT!][!//
      [!ENDCODE!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
[!ENDNOCODE!][!//

/* Global PSPR End address */
[!/*[cover parentID={97C40932-51AF-414f-BC0A-7382AB0BA160}][/cover]*/!][!//
#define MCAL_PSPR0_GLOBAL_END_ADDR    ([!"num:inttohex(ecu:get('McalLib.PsprCore0EndAddr'))"!]U)
[!NOCODE!][!//
[!/*[cover parentID={7095B3C7-87F9-4f1a-84D5-64BA41CB6506}][/cover]*/!][!//
[!/*[cover parentID={305886FD-6739-483b-A520-3BC2BAEA1B64}][/cover]*/!][!//
[!/*[cover parentID={10B583FB-6854-4d07-AB29-1EFA5F0450F3}][/cover]*/!][!//
[!/*[cover parentID={64081E3D-4A32-43cc-A812-C9D7257C9213}][/cover]*/!][!//
[!/*[cover parentID={CF8EDF34-2A10-4325-A191-00ADCFA8034F}][/cover]*/!][!//
[!FOR "CpuID" = "num:i(1)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable') - num:i(1))"!][!//
  [!VAR "CurrCoreExists" = "concat('Mcu.fCPU', $CpuID, 'Exists')"!][!//
  [!VAR "PsprMacro" = "concat('MCAL_PSPR', $CpuID, '_GLOBAL_END_ADDR')"!][!//
  [!VAR "PsprCurrCoreEndAddr" = "concat('McalLib.PsprCore', $CpuID, 'EndAddr')"!][!//
  [!IF "ecu:get($CurrCoreExists) = 'true'"!][!//
    [!CODE!][!//
      [!INDENT "0"!][!//
        #define [!"$PsprMacro"!]    ([!"num:inttohex(ecu:get($PsprCurrCoreEndAddr))"!]U)
      [!ENDINDENT!][!//
    [!ENDCODE!][!//
  [!ENDIF!][!//
[!ENDFOR!][!//
[!ENDNOCODE!][!//

/* Global DSPR base address */
[!/*[cover parentID={283014DF-B436-4233-B9FB-D311BADBD9B0}][/cover]*/!][!//
#define MCAL_DSPR0_GLOBAL_BASE_ADDR   ([!"num:inttohex(ecu:get('McalLib.DsprCore0StartAddr'))"!]U)
[!NOCODE!][!//
[!/*[cover parentID={77C7166A-C4D8-4916-9FD7-0CD3BEFC9116}][/cover]*/!][!//
[!/*[cover parentID={4ED8C5C8-673F-498b-AD91-43036E0A1830}][/cover]*/!][!//
[!/*[cover parentID={91898296-49FB-4b38-927A-4D8559FA5622}][/cover]*/!][!//
[!/*[cover parentID={5BD191A4-4678-4704-AC08-5BC60D6F0CC0}][/cover]*/!][!//
[!/*[cover parentID={14742C4A-0A4C-4305-A3D6-0A91F4EDCE03}][/cover]*/!][!//
[!FOR "CpuID" = "num:i(1)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable') - num:i(1))"!][!//
  [!VAR "CurrCoreExists" = "concat('Mcu.fCPU', $CpuID, 'Exists')"!][!//
  [!VAR "DsprMacro" = "concat('MCAL_DSPR', $CpuID, '_GLOBAL_BASE_ADDR')"!][!//
  [!VAR "DsprCurrCoreStartAddr" = "concat('McalLib.DsprCore', $CpuID, 'StartAddr')"!][!//
  [!IF "ecu:get($CurrCoreExists) = 'true'"!][!//
    [!CODE!][!//
      [!INDENT "0"!][!//
        #define [!"$DsprMacro"!]   ([!"num:inttohex(ecu:get($DsprCurrCoreStartAddr))"!]U)
      [!ENDINDENT!][!//
    [!ENDCODE!][!//
  [!ENDIF!][!//
[!ENDFOR!][!//
[!ENDNOCODE!][!//

/* Global DSPR End address */
[!/*[cover parentID={AFF6AEC3-1B9A-4d62-ACBC-01B54E78A91B}][/cover]*/!][!//
#define MCAL_DSPR0_GLOBAL_END_ADDR    ([!"num:inttohex(ecu:get('McalLib.DsprCore0EndAddr'))"!]U)
[!NOCODE!][!//
[!/*[cover parentID={053B0237-4617-4dc6-845C-116B25AF40E1}][/cover]*/!][!//
[!/*[cover parentID={DA542DF0-E3CA-4e71-8ECB-3E10E58C8A15}][/cover]*/!][!//
[!/*[cover parentID={44AB1F62-BA7D-4192-9545-C8C845280C61}][/cover]*/!][!//
[!/*[cover parentID={C2303E4F-BBA4-47ac-8DB5-497AB1096C59}][/cover]*/!][!//
[!/*[cover parentID={E02DE55D-9BAA-48ff-A546-D23C34D77C88}][/cover]*/!][!//
[!FOR "CpuID" = "num:i(1)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable') - num:i(1))"!][!//
  [!VAR "CurrCoreExists" = "concat('Mcu.fCPU', $CpuID, 'Exists')"!][!//
  [!VAR "DsprMacro" = "concat('MCAL_DSPR', $CpuID, '_GLOBAL_END_ADDR')"!][!//
  [!VAR "DsprCurrCoreEndAddr" = "concat('McalLib.DsprCore', $CpuID, 'EndAddr')"!][!//
  [!IF "ecu:get($CurrCoreExists) = 'true'"!][!//
    [!CODE!][!//
      [!INDENT "0"!][!//
        #define [!"$DsprMacro"!]    ([!"num:inttohex(ecu:get($DsprCurrCoreEndAddr))"!]U)
      [!ENDINDENT!][!//
    [!ENDCODE!][!//
  [!ENDIF!][!//
[!ENDFOR!][!//
[!ENDNOCODE!][!//

/*
Configuration: MCALLIB_SAFETY_ENABLE:
Compile switch to enable/disable the Safety Enable API
- ON if McalLibSafetyEnable   is true
- OFF if McalLibSafetyEnable   is false
*/
[!NOCODE!][!//
[!/*[cover parentID={C5587013-0247-4b94-8AAD-9472AD0A5A68}][/cover]*/!][!//
[!IF "McalLibGeneral/McalLibSafetyEnable = 'true'"!][!//
  [!CODE!][!//
    [!INDENT "0"!][!//
      #define MCALLIB_SAFETY_ENABLE         (STD_ON)
    [!ENDINDENT!][!//                     
  [!ENDCODE!][!//                       
[!ELSE!][!//                            
  [!CODE!][!//                          
    [!INDENT "0"!][!//                    
      #define  MCALLIB_SAFETY_ENABLE        (STD_OFF)
    [!ENDINDENT!][!//
  [!ENDCODE!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//

/*For retriving the Master Core ID */
[!NOCODE!][!//
[!SELECT "as:modconf('ResourceM')[1]"!][!//
  [!/*[cover parentID={D9877FD3-20A0-48a3-9A79-7AFE5287A000}][/cover]*/!][!//
  [!CODE!][!//
    [!INDENT "0"!][!//
      #define MCAL_MASTER_COREID            ([!"substring(node:value(ResourceMMcalConfig/*[1]/ResourceMMasterCore),5,1)"!]U)
    [!ENDINDENT!][!//
  [!ENDCODE!][!//
[!ENDSELECT!][!//
[!ENDNOCODE!][!//

#endif  /* MCALLIB_CFG_H */

