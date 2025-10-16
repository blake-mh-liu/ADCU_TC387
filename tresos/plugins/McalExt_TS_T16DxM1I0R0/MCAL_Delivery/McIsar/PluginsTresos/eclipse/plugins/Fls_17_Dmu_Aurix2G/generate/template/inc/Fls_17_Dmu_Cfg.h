[!/****************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2021)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Fls_17_Dmu_Cfg.h                                            **
**                                                                           **
**  VERSION    :  12.0.0                                                     **
**                                                                           **
**  DATE       :  2021-09-12                                                 **
**                                                                           **
**  VARIANT    : Variant PB                                                  **
**                                                                           **
**  PLATFORM   : Infineon AURIX2G                                            **
**                                                                           **
**  AUTHOR     : DL-AUTOSAR-Engineering                                      **
**                                                                           **
**  VENDOR     : Infineon Technologies                                       **
**                                                                           **
**  DESCRIPTION: Code template for Fls_17_Dmu_Cfg.h file                     **
**                                                                           **
**  SPECIFICATION(S) : Specification of FLS Driver,                          **
**                           AUTOSAR Release 4.2.2 and 4.4.0                 **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: No                                      **
**                                                                           **
******************************************************************************/

************************************************************************/!][!//
[!//
/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2021)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Fls_17_Dmu_Cfg.h                                            **
**                                                                           **
**  VERSION :  12.0.0                                                        **
**                                                                           **
**  DATE, TIME: [!"$date"!], [!"$time"!]              !!!IGNORE-LINE!!!      **
**                                                                           **
**  GENERATOR : Build [!"$buildnr"!]                !!!IGNORE-LINE!!!        **
**                                                                           **
**  BSW MODULE DECRIPTION : NA                                               **
**                                                                           **
**  VARIANT   : Variant PB                                                   **
**                                                                           **
**  PLATFORM  : Infineon AURIX2G                                             **
**                                                                           **
**  AUTHOR    : DL-AUTOSAR-Engineering                                       **
**                                                                           **
**  VENDOR    : Infineon Technologies                                        **
**                                                                           **
**  DESCRIPTION  : FLS configuration generated out of ECU configuration      **
**                   file                                                    **
**                                                                           **
**  SPECIFICATION(S) : Specification of FLS Driver,                          **
**                           AUTOSAR Release 4.2.2 and 4.4.0                 **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: No                                      **
**                                                                           **
******************************************************************************/
[!/* [cover parentID={E28116AB-67A4-45c7-9E55-89F2E3382919}][/cover] */!]
[!/* [cover parentID={1E72E6C2-4107-4551-BFE4-BC613F96086B}][/cover] */!]
#ifndef FLS_17_DMU_CFG_H
#define FLS_17_DMU_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
[!NOCODE!][!//
  [!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
[!ENDNOCODE!][!//
[!/* [cover parentID={D0DC9620-096E-49ad-B133-83B17D89DABC}][/cover] */!]
[!IF "$MinorVersion = num:i(2)"!][!//
/* MemIf Type Defnitions Imported from Memory Abstract Interface */
#include "MemIf_Types.h"
[!ELSE!][!//
/* Typedefs Imported from Memory Abstract Interface */ 
#include "MemIf.h"
[!ENDIF!]

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
[!AUTOSPACING!]
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!VAR "IfxFeeUsed" = "'OFF'"!][!//
[!VAR "IfxFeeNVMUsed" = "'OFF'"!][!//
[!SELECT "as:modconf('Fls')[1]"!][!//
  [!IF "FlsGeneral/FlsIfxFeeUse = 'true'"!][!//
    [!VAR "IfxFeeUsed" = "'ON'"!][!//
  [!ENDIF!][!//
[!//
/*
  Published parameters
*/

[!/* [cover parentID={72361E09-F5A3-4bce-B7FD-91E62DA26868}][/cover] */!]
/* FLS Instance ID */
#define FLS_17_DMU_INSTANCE_ID                ((uint8)[!"num:i(FlsGeneral/FlsDriverIndex)"!])

[!/* [cover parentID={52D5C648-C1BB-4cf9-8A73-C6FB379A6B35}][/cover] */!]
#define Fls_17_DmuConf_FlsGeneral_FlsDriverIndex  (FLS_17_DMU_INSTANCE_ID)
[!NOCODE!]
  [!//
  [!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
  [!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
  [!VAR "PatchVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
  [!/* [cover parentID={3C713A78-F913-4e44-BBB9-C4C08E13E286}][/cover] */!]
  [!/* [cover parentID={06DCA606-0506-4613-BBEF-CE0533760FB8}][/cover] */!]
  [!/* [cover parentID={4460533D-3C5B-4be4-A982-0766EA07F413}][/cover] */!]
[!ENDNOCODE!]
/* Autosar specification version */
#define FLS_17_DMU_AR_RELEASE_MAJOR_VERSION           ([!"$MajorVersion"!]U)
#define FLS_17_DMU_AR_RELEASE_MINOR_VERSION           ([!"$MinorVersion"!]U)
#define FLS_17_DMU_AR_RELEASE_REVISION_VERSION        ([!"$PatchVersion"!]U)

[!NOCODE!]
  [!//
  [!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
  [!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
  [!VAR "SwPatchVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
  [!/* [cover parentID={21E2E6A5-9DB2-4bb9-A165-1B6EDA81C534}][/cover] */!]
  [!/* [cover parentID={34293E32-5DB5-452f-B4E8-6B324BFDBE7C}][/cover] */!]
  [!/* [cover parentID={A85C7241-164D-42a9-AA80-9ED474424FC0}][/cover] */!]
[!ENDNOCODE!]
/* Vendor specific implementation version information */
#define FLS_17_DMU_SW_MAJOR_VERSION           ([!"$SwMajorVersion"!]U)
#define FLS_17_DMU_SW_MINOR_VERSION           ([!"$SwMinorVersion"!]U)
#define FLS_17_DMU_SW_PATCH_VERSION           ([!"$SwPatchVersion"!]U)

/*
  The following macros will enable or disable a particular feature in FLS
  module.Set the macro to STD_ON to enable the feature and STD_OFF to
  disable the same.
*/
/* Enable/Disable Development error detection(DET)  */
#define FLS_17_DMU_DEV_ERROR_DETECT         [!//
[!IF "FlsGeneral/FlsDevErrorDetect = 'true'"!][!//
  (STD_ON[!//
[!ELSE!][!//
  (STD_OFF[!//
[!ENDIF!][!//
)
[!/* [cover parentID={63262F83-0F72-4676-8894-C4C00D13204E}][/cover] */!]
[!/* [cover parentID={A3823A5A-6FC6-410c-9254-508235A487AC}][/cover] */!]
/* Enable/Disable RunTime error detection */
#define FLS_17_DMU_RUNTIME_ERROR_DETECT         [!//
[!IF "FlsGeneral/FlsRunTimeErrorDetect = 'true'"!][!//
  (STD_ON[!//
[!ELSE!][!//
  (STD_OFF[!//
[!ENDIF!][!//
)

[!/* [cover parentID={9F1DDCD5-635A-4826-B961-6EC75D5ACDD2}][/cover] */!]
/* Enable/Disable Safety error detection */
#define FLS_17_DMU_SAFETY_ENABLE         [!//
[!IF "FlsGeneral/FlsSafetyEnable = 'true'"!][!//
  (STD_ON[!//
[!ELSE!][!//
  (STD_OFF[!//
[!ENDIF!][!//
)

[!/* [cover parentID={BA634840-20BB-4b2a-BA15-D51EEAC54AA9}][/cover] */!]
/*Enable/Disable FLS Init Check API*/
#define FLS_17_DMU_INITCHECK_API         [!//
[!IF "FlsGeneral/FlsInitCheckApi = 'true'"!][!//
  (STD_ON[!//
[!ELSE!][!//
  (STD_OFF[!//
[!ENDIF!][!//
)


[!/* [cover parentID={88F8A5C9-CCDB-40bd-A8A2-5DB65E9BA807}][/cover] */!]
[!IF "$IfxFeeUsed = 'OFF'"!][!//
  [!INDENT "0"!][!//
  /* Flash job interrupt mode or polling mode*/
  #define FLS_17_DMU_USE_INTERRUPTS          [!//
  [!ENDINDENT!][!//
  [!IF "FlsGeneral/FlsUseInterrupts = 'true'"!][!//
    (STD_ON[!//
  [!ELSE!][!//
    (STD_OFF[!//
  [!ENDIF!][!//
[!ELSE!][!//
  [!INDENT "0"!][!//
  #define FLS_17_DMU_USE_INTERRUPTS          [!//
  [!ENDINDENT!][!//
(STD_OFF[!//
[!ENDIF!][!//
)

[!/* [cover parentID={168B75FF-1AF1-458e-98E1-FE805D566DF8}][/cover] */!]
/*Erase verification during write feature*/
[!IF "$MinorVersion = '4'"!][!//
  [!INDENT "0"!][!//
  #define FLS_17_DMU_ERASE_VERIFICATION       [!//
  [!ENDINDENT!][!//
  [!IF "FlsGeneral/FlsEraseVerificationEnabled = 'true' and $IfxFeeUsed = 'OFF'"!][!//
    (STD_ON[!//
  [!ELSE!][!//
    (STD_OFF[!//
  [!ENDIF!][!//
[!ELSE!][!//
  [!INDENT "0"!][!//
  #define FLS_17_DMU_ERASE_VERIFICATION       [!//
  [!ENDINDENT!][!//
  [!IF "(FlsGeneral/FlsDevErrorDetect = 'true' or FlsGeneral/FlsSafetyEnable = 'true') and $IfxFeeUsed = 'OFF'"!][!//
    (STD_ON[!//
  [!ELSE!][!//
    (STD_OFF[!//
  [!ENDIF!][!//
[!ENDIF!][!//
)

[!/* [cover parentID={FEBCFFB2-6288-4266-88A6-01050C8A3BCA}][/cover] */!]
/*Erase verification reporting feature*/
[!IF "$MinorVersion = '4'"!][!//
  [!INDENT "0"!][!//
  #define FLS_17_DMU_ERASE_VERIFY_REPORT       [!//
  [!ENDINDENT!][!//
  [!IF "FlsGeneral/FlsEraseVerificationEnabled = 'true' and FlsGeneral/FlsRunTimeErrorDetect = 'true'"!][!//
    (STD_ON[!//
  [!ELSE!][!//
    (STD_OFF[!//
  [!ENDIF!][!//
[!ELSE!][!//
  [!INDENT "0"!][!//
  #define FLS_17_DMU_ERASE_VERIFY_REPORT          [!//
  [!ENDINDENT!][!//
(STD_OFF[!//
[!ENDIF!][!//
)

[!/* [cover parentID={03B793C6-EEBA-4ad9-A9D7-334FFCCBF48A}][/cover] */!]
/*Write verification feature*/
[!IF "$MinorVersion = '4'"!][!//
  [!INDENT "0"!][!//
  #define FLS_17_DMU_WRITE_VERIFICATION       [!//
  [!ENDINDENT!][!//
  [!IF "FlsGeneral/FlsWriteVerificationEnabled = 'true' and FlsGeneral/FlsRunTimeErrorDetect = 'true'"!][!//
    (STD_ON[!//
  [!ELSE!][!//
    (STD_OFF[!//
  [!ENDIF!][!//
[!ELSE!][!//
  [!INDENT "0"!][!//
  #define FLS_17_DMU_WRITE_VERIFICATION          [!//
  [!ENDINDENT!][!//
(STD_OFF[!//
[!ENDIF!][!//
)

[!/* [cover parentID={8540A463-4580-4878-8F8A-E3CA7527538B}][/cover] */!]
/*Timeout Supervision feature*/
[!IF "$MinorVersion = '4'"!][!//
  [!INDENT "0"!][!//
  #define FLS_17_DMU_TIMEOUT_SUPERVISION       [!//
  [!ENDINDENT!][!//
  [!IF "FlsGeneral/FlsTimeoutSupervisionEnabled = 'true'"!][!//
    (STD_ON[!//
  [!ELSE!][!//
    (STD_OFF[!//
  [!ENDIF!][!//
[!ELSE!][!//
  [!INDENT "0"!][!//
  #define FLS_17_DMU_TIMEOUT_SUPERVISION       [!//
  [!ENDINDENT!][!//
  [!IF "FlsGeneral/FlsDevErrorDetect = 'true' or FlsGeneral/FlsSafetyEnable = 'true'"!][!//
    (STD_ON[!//
  [!ELSE!][!//
    (STD_OFF[!//
  [!ENDIF!][!//
[!ENDIF!][!//
)

/*Fls_cancel api selection*/
[!/* [cover parentID={93874644-E3F1-49ec-8F47-C181466B0C72}][/cover] */!]
#define FLS_17_DMU_CANCEL_API             [!//
[!IF "FlsGeneral/FlsCancelApi = 'true'"!][!//
  (STD_ON[!//
[!ELSE!][!//
  (STD_OFF[!//
[!ENDIF!][!//
)

[!/* [cover parentID={0E4D6F9C-9247-479e-80BF-8E0312E7A38C}][/cover] */!]
/*Fls_17_Dmu_GetEccErrorPageAddress api selection*/
#define FLS_17_DMU_ECC_ERROR_INFO_API       [!//
[!IF "FlsGeneral/FlsEccErrorInfoApi = 'true' and $IfxFeeUsed = 'ON'"!][!//
  (STD_ON[!//
[!ELSE!][!//
  (STD_OFF[!//
[!ENDIF!][!//
)

[!/* [cover parentID={4F0037BB-C54B-4b02-B6C6-7EA385885260}][/cover] */!]
/*Fls_SetMode api selection*/
#define FLS_17_DMU_SET_MODE_API             [!//
[!IF "FlsGeneral/FlsSetModeApi = 'true'"!][!//
  (STD_ON[!//
[!ELSE!][!//
  (STD_OFF[!//
[!ENDIF!][!//
)

/*Fls_compare api selection*/
#define FLS_17_DMU_COMPARE_API            [!//
[!IF "FlsGeneral/FlsCompareApi = 'true'"!][!//
  (STD_ON[!//
[!ELSE!][!//
  (STD_OFF[!//
[!ENDIF!][!//
)

[!/* [cover parentID={5C9703DD-3DEB-47d3-B1F2-AA6C8748DCCA}][/cover] */!]
/*Fls_BlankCheck api selection*/
#define FLS_17_DMU_BLANK_CHECK_API            [!//
[!IF "FlsGeneral/FlsBlankCheckApi = 'true'"!][!//
  (STD_ON[!//
[!ELSE!][!//
  (STD_OFF[!//
[!ENDIF!][!//
)

/*Fls_GetJobResult api selection*/
#define FLS_17_DMU_GET_JOB_RESULT_API     [!//
[!IF "FlsGeneral/FlsGetJobResultApi = 'true'"!][!//
  (STD_ON[!//
[!ELSE!][!//
  (STD_OFF[!//
[!ENDIF!][!//
)

[!/* [cover parentID={DD61519C-ED4F-480f-8B38-C21246D4E0C8}][/cover] */!]
/*Fls_GetStatus api selection*/
#define FLS_17_DMU_GET_STATUS_API         [!//
[!IF "FlsGeneral/FlsGetStatusApi = 'true'"!][!//
  (STD_ON[!//
[!ELSE!][!//
  (STD_OFF[!//
[!ENDIF!][!//
)

/*Fls_GetVersionInfo api selection*/
#define FLS_17_DMU_VERSION_INFO_API   [!//
[!IF "FlsGeneral/FlsVersionInfoApi = 'true'"!][!//
  (STD_ON[!//
[!ELSE!][!//
  (STD_OFF[!//
[!ENDIF!][!//
)

/*Erase suspend/resume feature selection*/
#define FLS_17_DMU_USE_ERASESUSPEND   [!//
[!IF "FlsIfxSpecificConfig/FlsUseEraseSuspend = 'true'"!][!//
  (STD_ON[!//
[!ELSE!][!//
  (STD_OFF[!//
[!ENDIF!][!//
)


[!/* [cover parentID={D0A747BC-456D-4353-91D9-A0376EB61DE3}][/cover] */!]
[!IF "$IfxFeeUsed = 'ON'"!][!//
/* IFX FEE is being used in configuration */
#define FLS_17_DMU_IFX_FEE_USED        (STD_ON)
[!ELSE!][!//
/* IFX FEE is not in use */
#define FLS_17_DMU_IFX_FEE_USED        (STD_OFF)
[!ENDIF!][!//

[!/* [cover parentID={BB7A3FFE-FC26-4525-81F3-5EE695EA8D62}][/cover] */!]
/*DFLASH base/start address*/
[!VAR "DF0BaseAddress" = "FlsGeneral/FlsBaseAddress"!][!//
#define FLS_17_DMU_BASE_ADDRESS           ([!"num:inttohex($DF0BaseAddress)"!]U)

/*DFLASH total size*/
[!/*[cover parentID={D078C6D6-5C16-4680-97CD-DD673F41DAA1}][/cover]*/!]
[!VAR "DF0Size" = "FlsGeneral/FlsTotalSize"!][!//
#define FLS_17_DMU_TOTAL_SIZE             ([!"num:inttohex($DF0Size)"!]U)

[!VAR "SectorPageSize" = "FlsConfigSet/FlsSectorList/*/*/*/FlsPageSize"!][!//
[!IF "$IfxFeeUsed = 'ON'"!][!//
  [!SELECT "FlsConfigSet/FlsSectorList/*[1]"!][!//
    [!VAR "TotalSectorSize" = "num:i(0)"!][!//
    [!LOOP "FlsSector/*"!][!//
      [!VAR "NumberofSector" = "FlsNumberOfSectors"!][!//
      [!VAR "SectorAddress" = "FlsSectorStartaddress"!][!//
      [!VAR "SectorSize" = "FlsSectorSize"!][!//
      [!IF "$NumberofSector = 2"!][!//
        [!VAR "IfxFeeNVMUsed" = "'ON'"!][!//
    [!INDENT "0"!][!//
        /* Start address of the NVM Sector0 */
        #define FLS_17_DMU_NVMSECTOR0_STARTADDRESS ([!"num:inttohex($SectorAddress + $DF0BaseAddress)"!]U)

        /* Start address of the NVM Sector1 */
        [!/*[cover parentID={0EF026E3-7E78-4210-BA00-21FDED676D2F}][/cover]*/!]
        #define FLS_17_DMU_NVMSECTOR1_STARTADDRESS ([!"num:inttohex($SectorAddress + $SectorSize + $DF0BaseAddress)"!]U)

        /* Size of the 1 NVM sector of the the double sector in bytes*/
        [!/*[cover parentID={3C2F5740-7DBD-49dc-8E69-1FFDBEB93300}][/cover]*/!]
        #define FLS_17_DMU_NVMSECTOR_SIZE        ([!"num:inttohex($SectorSize)"!]U)
    [!ENDINDENT!][!//
        [!VAR "TotalSectorSize" = "num:i($TotalSectorSize + $SectorSize * 2 + $SectorAddress)"!][!//
      [!ELSE!][!//
      [!INDENT "0"!][!//
        /* Start address of the Quasi Static Data */
        #define FLS_17_DMU_QSDATA_STARTADDRESS   ([!"num:inttohex($SectorAddress + $DF0BaseAddress)"!]U)

        /* Size of the Quasi static data in bytes*/
        #define FLS_17_DMU_QSDATA_SIZE           ([!"num:inttohex($SectorSize)"!]U)
    [!ENDINDENT!][!//
        [!VAR "TotalSectorSize" = "num:i($TotalSectorSize + $SectorSize)"!][!//
        [!VAR "AvailableSize" = "num:i($DF0Size - $SectorAddress)"!][!//
        [!IF "$AvailableSize < $SectorSize"!][!//
          [!ERROR!][!//
      Error: Total sizes of the sectors configured is greater than the Total Flash size!
          [!ENDERROR!][!//
      [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "($TotalSectorSize + $DF0BaseAddress) > ($DF0Size + $DF0BaseAddress)"!][!//
      [!ERROR!][!//
 Error: Total sizes of the sectors configured is greater than the Total Flash size!
      [!ENDERROR!][!//
    [!ENDIF!][!//
  [!ENDSELECT!][!//
[!ELSE!][!//
  [!SELECT "FlsConfigSet/FlsSectorList/*[1]"!][!//
    [!VAR "TotalSectorSize" = "num:i(0)"!][!//
    [!LOOP "FlsSector/*"!][!//
      [!VAR "NumberofSector" = "FlsNumberOfSectors"!][!//
      [!VAR "SectorAddress" = "FlsSectorStartaddress"!][!//
      [!VAR "SectorSize" = "FlsSectorSize"!][!//
      [!VAR "NumberofSector" = "FlsNumberOfSectors"!][!//
    [!/*[cover parentID={D8B16691-EDC9-409f-83E5-483568B4DC4C}][/cover]*/!]
      [!WS"0"!]#define FlsConf_[!"node:name(.)"!]_STARTADDRESS ([!"num:inttohex($SectorAddress + $DF0BaseAddress)"!]U)
      [!VAR "EachSectorSize" = "num:i($SectorSize * $NumberofSector)"!][!//
      [!VAR "TotalSectorSize" = "num:i($TotalSectorSize + $EachSectorSize)"!][!//
      [!VAR "AvailableSize" = "num:i($DF0Size - $SectorAddress)"!][!//
      [!IF "$AvailableSize < $EachSectorSize"!][!//
        [!ERROR!][!//
          Error: Total sizes of the sectors configured is greater than the Total Flash size!
        [!ENDERROR!][!//
      [!ENDIF!][!//
    [!ENDLOOP!]
    [!IF "($TotalSectorSize + $DF0BaseAddress) > ($DF0Size + $DF0BaseAddress)"!][!//
      [!ERROR!][!//
        Error: Total sizes of the sectors configured is greater than the Total Flash size!
      [!ENDERROR!][!//
    [!ENDIF!][!//
  [!ENDSELECT!][!//
[!ENDIF!][!//

[!IF "$IfxFeeNVMUsed = 'ON'"!][!//
  [!IF "node:exists(FlsConfigSet/FlsSectorList/*/FlsSector/*[2])"!][!//
    [!IF "num:i(FlsConfigSet/FlsSectorList/*/FlsSector/*[2]/FlsNumberOfSectors) > num:i(1)"!][!//
      [!ERROR!][!//
        Error: Ifx Fee is present and has double data sector mode. Max value of FlsNumberOfsectors is '1' for the second sector.
        Suggestion: Please correct the value of FlsNumberOfSectors.
      [!ENDERROR!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
  [!IF "node:exists(FlsConfigSet/FlsSectorList/*/FlsSector/*[3])"!][!//
    [!ERROR!][!//
      Error: Ifx Fee has double data sector mode. Third sector configuration is not allowed.
      Suggestion: Please remove one sector.
    [!ENDERROR!][!//
  [!ENDIF!][!//
  [!/*[cover parentID={5474766C-EC75-41eb-B120-605597916B7A}][/cover]*/!]
  [!INDENT "0"!][!//
  /* IFX FEE NVM is present in the configuration */
  #define FLS_17_DMU_IFX_NVM_PRESENT        (STD_ON)
  [!ENDINDENT!][!//
[!ELSE!][!//
  [!INDENT "0"!][!//
  /* IFX FEE NVM is not present in the configuration */
  #define FLS_17_DMU_IFX_NVM_PRESENT        (STD_OFF)
  [!ENDINDENT!][!//
[!ENDIF!][!//

[!/*[cover parentID={50362CBD-C81E-4d82-A6AA-12CB8DB53240}][/cover]*/!]
/*
Configuration: FLS_INIT_API_MODE
Specifies the operating modes for Fls initialization - SUPERVISOR/ USER1
*/
[!IF "FlsGeneral/FlsInitApiMode = 'FLS_17_DMU_MCAL_SUPERVISOR'"!][!//
  [!WS"0"!]#define FLS_17_DMU_INIT_API_MODE             (FLS_17_DMU_MCAL_SUPERVISOR)
[!ELSE!][!//
  [!IF "FlsGeneral/FlsRuntimeApiMode = 'FLS_17_DMU_MCAL_SUPERVISOR'"!][!//
    [!ERROR!][!//
      Error: If RuntimeApiMode is supervisor mode then InitApiMode should be Supervisor.
      Suggestion: Please change the InitApiMode to supervisor.
    [!ENDERROR!][!//
  [!ELSE!][!//
    [!WS"0"!]#define FLS_17_DMU_INIT_API_MODE           (FLS_17_DMU_MCAL_USER1)
  [!ENDIF!][!//
[!ENDIF!][!//

[!NOCODE!]
[!/*[cover parentID={EED71106-D819-4c17-924D-84E4123A13CD}][/cover]*/!]
[!/*[cover parentID={EC71D959-1018-4c1c-BCD5-CA936ED0E967}][/cover]*/!]
[!ENDNOCODE!]
/*
Configuration: FLS_RUNTIME_API_MODE
Specifies the operating modes for Fls runtime - SUPERVISOR/ USER1
*/
[!IF "FlsGeneral/FlsRuntimeApiMode = 'FLS_17_DMU_MCAL_SUPERVISOR'"!][!//
#define FLS_17_DMU_RUNTIME_API_MODE           (FLS_17_DMU_MCAL_SUPERVISOR)
[!ELSE!][!//
#define FLS_17_DMU_RUNTIME_API_MODE           (FLS_17_DMU_MCAL_USER1)
[!ENDIF!][!//

[!/*[cover parentID={C0680422-86D1-4b25-87C3-B82645699CDA}][/cover]*/!]
/* Page size of the Data flash is 8 bytes */
#define FLS_17_DMU_PAGE_SIZE            ([!"$SectorPageSize"!]U)

[!/*[cover parentID={ECD879CA-6973-43a0-A5F6-2C364FD69904}][/cover]*/!]
/* erase and write times are published in us (micro seconds) */
[!VAR "EraseTime" = "FlsPublishedInformation/FlsEraseTime"!][!//
#define FLS_17_DMU_ERASE_TIME            ([!"num:i(($EraseTime) * num:i(1000))"!]U)

[!/*[cover parentID={23409171-4C67-4942-B5E5-9497AEF9D45A}][/cover]*/!]
[!VAR "WriteTime" = "FlsPublishedInformation/FlsWriteTime"!][!//
#define FLS_17_DMU_WRITE_TIME            ([!"num:i(($WriteTime) * num:i(1000))"!]U)

[!/*[cover parentID={303CB202-46B0-468f-9E72-66086BF46051}][/cover]*/!]
[!VAR "ErasedValue" = "FlsPublishedInformation/FlsErasedValue"!][!//
#define FLS_17_DMU_DEFAULT_ERASEVALUE            ([!"num:i($ErasedValue)"!]U)

/*Timeout for Erase suspend/resume feature*/
[!/*[cover parentID={03DA6395-E09B-4114-AC16-C8D3FBF3278B}][/cover]*/!]
#if (FLS_17_DMU_USE_ERASESUSPEND == STD_ON)
#define FLS_17_DMU_ERASESUSPEND_TIMEOUT        ([!"num:inttohex(FlsIfxSpecificConfig/FlsEraseSuspendTimeout)"!]U)
#endif

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
#endif  /* FLS_17_DMU_CFG_H */
[!ENDSELECT!]
