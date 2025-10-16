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
**  FILENAME  : Crc_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 10.0.0                                                        **
**                                                                            **
**  DATE      : 2020-07-22                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Crc.bmd                                           **
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
**  DESCRIPTION  : Code template header file for CRC Library                  **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of CRC Driver, AUTOSAR Release 4.2.2     **
**                   : Specification of Crc Driver, AUTOSAR Release 4.4.0     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*************************************************************************/!][!//
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
**  FILENAME  : Crc_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 10.0.0                                                        **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]      !!!IGNORE-LINE!!!                   **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]          !!!IGNORE-LINE!!!                 **
**                                                                            **
**  BSW MODULE DECRIPTION : Crc.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : CRC configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of CRC Driver, AUTOSAR Release 4.2.2     **
**                   : Specification of Crc Driver, AUTOSAR Release 4.4.0     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
[!/* [cover parentID={084339EF-4E3B-40a4-A767-EF7DE0D43436}] */!][!//
[!/* [/cover] */!][!//
[!NOCODE!][!//
  [!INCLUDE "Crc.m"!][!//
[!ENDNOCODE!][!//
#ifndef CRC_CFG_H
#define CRC_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
#define CRC_HARDWARE_MODE       (0x01u)
#define CRC_RUNTIME_MODE        (0x02u)
#define CRC_TABLE_MODE          (0x03u)


/************************Macro for Initial Values of CRC***********************/
#define CRC_INITIAL_VALUE8      ((uint8)0xFFU)
#define CRC_INITIAL_VALUE8H2F   ((uint8)0xFFU)
#define CRC_INITIAL_VALUE16     ((uint16)0xFFFFU)
#define CRC_INITIAL_VALUE16ARC  ((uint16)0x0000U)
#define CRC_INITIAL_VALUE32     ((uint32)0xFFFFFFFFU)
#define CRC_INITIAL_VALUE32P4   ((uint32)0xFFFFFFFFU)
#define CRC_INITIAL_VALUE64     ((uint64)0xFFFFFFFFFFFFFFFFU)
/* ************************************************************************** */

[!AUTOSPACING!]
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Crc')[1]"!][!//
  [!INDENT "0"!]
    [!//
    [!NOCODE!][!//
    [!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
    [!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
    [!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
    [!VAR "NewString" = "text:replaceAll($moduleReleaseVer,"\.",'')"!][!//
    [!ENDNOCODE!][!//
    /*************************Autosar specific information*************************/
    [!/* [cover parentID={C8CF829D-BC18-49ae-9D5F-854A31BF05CB}] */!][!//
    [!/* [/cover] */!][!//
    #define CRC_AR_RELEASE_MAJOR_VERSION  ([!"$MajorVersion"!]U)
    [!/* [cover parentID={3DE22013-294C-4e0c-A14B-8497E12F165A}] */!][!//
    [!/* [/cover] */!][!//
    #define CRC_AR_RELEASE_MINOR_VERSION  ([!"$MinorVersion"!]U)
    [!/* [cover parentID={70B9BE0F-FAF9-488d-8CC5-A6AE13CFD821}] */!][!//
    [!/* [/cover] */!][!//
    #define CRC_AR_RELEASE_REVISION_VERSION  ([!"$RevisionVersion"!]U)
    /* ************************************************************************** */

    [!VAR "MajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
    [!VAR "MinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
    [!VAR "RevisionVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
    [!VAR "NewString" = "text:replaceAll($moduleSoftwareVer,"\.",'')"!][!//
    /*************************Release specific information*************************/
    [!/* [cover parentID={A18D550B-8069-42cc-8527-A3628ACF0671}] */!][!//
    [!/* [/cover] */!][!//
    #define CRC_SW_MAJOR_VERSION  ([!"$MajorVersion"!]U)
    [!/* [cover parentID={35FB64B1-4185-4a84-8B5E-4FB388EA4378}] */!][!//
    [!/* [/cover] */!][!//
    #define CRC_SW_MINOR_VERSION  ([!"$MinorVersion"!]U)
    [!/* [cover parentID={05A83C53-F0D3-422d-A45A-1EAC95B9E477}] */!][!//
    [!/* [/cover] */!][!//
    #define CRC_SW_PATCH_VERSION  ([!"$RevisionVersion"!]U)
    /* ************************************************************************** */

    /*************************Macro for versioninfoapi*****************************/
    [!/* [cover parentID={6A16D240-906B-4cd7-8CB5-FBFF690F8D6D}] */!][!//
    [!/* [/cover] */!][!//
    #define CRC_VERSION_INFO_API  ([!//
    [!IF "CrcGeneral/CrcVersionInfoApi  = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
    /* ************************************************************************** */

    /*************************Macro for Mode of CRC polynomials********************/
    /*Macro for selection of 16 bit CRC method */
    [!/* [cover parentID={8D50FC69-7BC3-4122-91DD-2E87169CBB82}] */!][!//
    [!/* [/cover] */!][!//
    [!IF "CrcGeneral/Crc16Mode/__1 = 'CRC_16_HARDWARE'"!][!//
      #define CRC_16_MODE (CRC_HARDWARE_MODE) [!//
    [!ELSEIF "CrcGeneral/Crc16Mode/__1 = 'CRC_16_RUNTIME'"!][!//
      #define CRC_16_MODE (CRC_RUNTIME_MODE) [!//
    [!ELSEIF "CrcGeneral/Crc16Mode/__1 = 'CRC_16_TABLE'"!][!//
      #define CRC_16_MODE (CRC_TABLE_MODE) [!//
    [!ELSE!][!//
      #define CRC_16_MODE (STD_OFF) [!//
    [!ENDIF!][!//

    /*Macro for selection of 16 bit CRC16ARC method*/
    [!/* [cover parentID={849C9D71-146F-4e6e-8046-266541BD80C5}] */!][!//
    [!/* [/cover] */!][!//
    [!IF "CrcGeneral/Crc16ARCMode/__1 = 'CRC_16_ARC_HARDWARE'"!][!//
      #define CRC_16ARC_MODE (CRC_HARDWARE_MODE) [!//
    [!ELSEIF "CrcGeneral/Crc16ARCMode/__1 = 'CRC_16_ARC_RUNTIME'"!][!//
      #define CRC_16ARC_MODE (CRC_RUNTIME_MODE) [!//
    [!ELSEIF "CrcGeneral/Crc16ARCMode/__1 = 'CRC_16_ARC_TABLE'"!][!//
      #define CRC_16ARC_MODE (CRC_TABLE_MODE) [!//
    [!ELSE!][!//
      #define CRC_16ARC_MODE (STD_OFF) [!//
    [!ENDIF!][!//

    /*Macro for selection of 32 bit CRC32 method */
    [!/* [cover parentID={098DB2FF-8290-4c2d-8619-317E04E2EE0A}] */!][!//
    [!/* [/cover] */!][!//
    [!IF "CrcGeneral/Crc32Mode/__1 = 'CRC_32_HARDWARE'"!][!//
      #define CRC_32_MODE (CRC_HARDWARE_MODE) [!//
    [!ELSEIF "CrcGeneral/Crc32Mode/__1 = 'CRC_32_RUNTIME'"!][!//
      #define CRC_32_MODE (CRC_RUNTIME_MODE) [!//
    [!ELSEIF "CrcGeneral/Crc32Mode/__1 = 'CRC_32_TABLE'"!][!//
      #define CRC_32_MODE (CRC_TABLE_MODE) [!//
    [!ELSE!][!//
      #define CRC_32_MODE (STD_OFF) [!//
    [!ENDIF!][!//

    /*Macro for selection of 32 bit CRCP4 method */
    [!/* [cover parentID={F9704DEB-1CA1-41a1-BC0D-A5FF70408FBB}] */!][!//
    [!/* [/cover] */!][!//
    [!IF "CrcGeneral/Crc32P4Mode/__1 = 'CRC_32P4_HARDWARE'"!][!//
      #define CRC_32P4_MODE (CRC_HARDWARE_MODE) [!//
    [!ELSEIF "CrcGeneral/Crc32P4Mode/__1 = 'CRC_32P4_RUNTIME'"!][!//
      #define CRC_32P4_MODE (CRC_RUNTIME_MODE) [!//
    [!ELSEIF "CrcGeneral/Crc32P4Mode/__1 = 'CRC_32P4_TABLE'"!][!//
      #define CRC_32P4_MODE (CRC_TABLE_MODE) [!//
    [!ELSE!][!//
      #define CRC_32P4_MODE (STD_OFF) [!//
    [!ENDIF!][!//

    /*Macro for selection of 8 bit CRC method*/
    [!/* [cover parentID={8C3F4ADF-2550-4c70-B539-0AB11F17451E}] */!][!//
    [!/* [/cover] */!][!//
    [!IF "CrcGeneral/Crc8Mode/__1 = 'CRC_8_HARDWARE'"!][!//
      #define CRC_8_MODE (CRC_HARDWARE_MODE)[!//
    [!ELSEIF "CrcGeneral/Crc8Mode/__1 = 'CRC_8_RUNTIME'"!][!//
      #define CRC_8_MODE (CRC_RUNTIME_MODE)[!//
    [!ELSEIF "CrcGeneral/Crc8Mode/__1 = 'CRC_8_TABLE'"!][!//
      #define CRC_8_MODE (CRC_TABLE_MODE)[!//
    [!ELSE!][!//
      #define CRC_8_MODE (STD_OFF) [!//
    [!ENDIF!][!//

    /*Macro for selection of 8 bit CRC8H2F method*/
    [!/* [cover parentID={8278D7D6-0C00-431b-9CA0-2A2E4A619F7E}] */!][!//
    [!/* [/cover] */!][!//
    [!IF "CrcGeneral/Crc8H2FMode/__1 = 'CRC_8H2F_HARDWARE'"!][!//
      #define CRC_8H2F_MODE (CRC_HARDWARE_MODE)[!//
    [!ELSEIF "CrcGeneral/Crc8H2FMode/__1 = 'CRC_8H2F_RUNTIME'"!][!//
      #define CRC_8H2F_MODE (CRC_RUNTIME_MODE)[!//
    [!ELSEIF "CrcGeneral/Crc8H2FMode/__1 = 'CRC_8H2F_TABLE'"!][!//
      #define CRC_8H2F_MODE (CRC_TABLE_MODE)[!//
    [!ELSE!][!//
      #define CRC_8H2F_MODE (STD_OFF) [!//
    [!ENDIF!][!//

     /*Macro for selection of 64 bit CRC64 method*/
    [!/* [cover parentID={CD506828-CEE2-4bad-BA3F-C0D214D281F2}] */!][!//
    [!/* [/cover] */!][!//
    [!IF "CrcGeneral/Crc64Mode/__1 = 'CRC_64_RUNTIME'"!][!//
      #define CRC_64_MODE (CRC_RUNTIME_MODE)[!//
    [!ELSEIF "CrcGeneral/Crc64Mode/__1 = 'CRC_64_TABLE'"!][!//
      #define CRC_64_MODE (CRC_TABLE_MODE)[!//
    [!ELSE!][!//
      #define CRC_64_MODE (STD_OFF) [!//
    [!ENDIF!][!//

    /* ************************************************************************** */

    /*************************Macro for DMA mode***********************************/
    /*Macro for selection of CRC_8_DMA mode*/
    [!/* [cover parentID={8847CEFA-FC33-409a-9C6F-09E89A8F542F}] */!][!//
    [!/* [/cover] */!][!//
      #define CRC_8_DMAMODE ([!//
    [!IF "CrcGeneral/CrcDma8bitApi  = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
    /*Macro for selection of CRC_16_DMA mode*/
    [!/* [cover parentID={0A45AC47-54B2-4651-B8B4-335DBD793656}] */!][!//
    [!/* [/cover] */!][!//
      #define CRC_16_DMAMODE ([!//
    [!IF "CrcGeneral/CrcDma16bitApi  = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
    /*Macro for selection of CRC_32_DMA mode*/
    [!/* [cover parentID={E980F231-466D-4632-923C-BDE5BB7D1DE4}] */!][!//
    [!/* [/cover] */!][!//
      #define CRC_32_DMAMODE ([!//
    [!IF "CrcGeneral/CrcDma32bitApi  = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
    /*Macro for selection of CRC_32P4_DMA mode*/
    [!/* [cover parentID={8EB7E4F2-9EEC-4a99-A944-36F2BC6FE202}] */!][!//
    [!/* [/cover] */!][!//
     #define CRC_32P4_DMAMODE ([!//
    [!IF "CrcGeneral/CrcDma32P4bitApi  = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )

    /* ************************************************************************** */
    [!/* [cover parentID={87869FC4-1164-45e8-8548-E39AA9D48E90}] */!][!//
    [!/* [/cover] */!][!//
    [!IF "CrcGeneral/CrcSafetyEnable = 'true'"!][!//
    #define CRC_SAFETYENABLE              (STD_ON)[!//

      /*************************Macro for Error value********************************/
      [!/* [cover parentID={A60567C6-251A-4660-9460-9766D4EC0276}] */!][!//
      [!/* [/cover] */!][!//
      [!IF "((CrcGeneral/Crc8Mode/__1 = 'CRC_8_HARDWARE') or (CrcGeneral/Crc8Mode/__1 = 'CRC_8_RUNTIME') or (CrcGeneral/Crc8Mode/__1 = 'CRC_8_TABLE'))"!][!//
      #define CRC_8_CONFIGERROR_VAL          ([!"CrcGeneral/Crc8ReturnErrorValue"!])
      [!ENDIF!][!//
      [!/* [cover parentID={4FEFB7F2-F95F-4c8b-A057-17E7E157EFBA}] */!][!//
      [!/* [/cover] */!][!//
      [!IF "((CrcGeneral/Crc8H2FMode/__1 = 'CRC_8H2F_HARDWARE') or (CrcGeneral/Crc8H2FMode/__1 = 'CRC_8H2F_RUNTIME') or (CrcGeneral/Crc8H2FMode/__1 = 'CRC_8H2F_TABLE'))"!][!//
      #define CRC_8H2F_CONFIGERROR_VAL    ([!"CrcGeneral/Crc8H2FReturnErrorValue"!])
      [!ENDIF!][!//
      [!/* [cover parentID={8E7569BB-4D55-4be2-81E3-3D6B54CD5374}] */!][!//
      [!/* [/cover] */!][!//
      [!IF "((CrcGeneral/Crc16Mode/__1 = 'CRC_16_HARDWARE') or (CrcGeneral/Crc16Mode/__1 = 'CRC_16_RUNTIME') or (CrcGeneral/Crc16Mode/__1 = 'CRC_16_TABLE'))"!][!//
      #define CRC_16_CONFIGERROR_VAL      ([!"CrcGeneral/Crc16ReturnErrorValue"!])
      [!ENDIF!][!//
      [!/* [cover parentID={22A1CF66-8320-4605-A060-D812133F6700}] */!][!//
      [!/* [/cover] */!][!//
      [!IF "((CrcGeneral/Crc16ARCMode/__1 = 'CRC_16_ARC_HARDWARE') or (CrcGeneral/Crc16ARCMode/__1 = 'CRC_16_ARC_RUNTIME') or (CrcGeneral/Crc16ARCMode/__1 = 'CRC_16_ARC_TABLE'))"!][!//
      #define CRC_16ARC_CONFIGERROR_VAL      ([!"CrcGeneral/Crc16ARCReturnErrorValue"!])
      [!ENDIF!][!//
      [!/* [cover parentID={D25344CE-D478-4a48-B2B6-84FF7804BC6B}] */!][!//
      [!/* [/cover] */!][!//
      [!IF "((CrcGeneral/Crc32Mode/__1 = 'CRC_32_HARDWARE') or (CrcGeneral/Crc32Mode/__1 = 'CRC_32_RUNTIME') or (CrcGeneral/Crc32Mode/__1 = 'CRC_32_TABLE'))"!][!//
      #define CRC_32_CONFIGERROR_VAL      ([!"CrcGeneral/Crc32ReturnErrorValue"!])
      [!ENDIF!][!//
      [!/* [cover parentID={58609002-A43B-4ebc-841B-FA5E65C9AEC9}] */!][!//
      [!/* [/cover] */!][!//
      [!IF "((CrcGeneral/Crc32P4Mode/__1 = 'CRC_32P4_RUNTIME') or (CrcGeneral/Crc32P4Mode/__1 = 'CRC_32P4_TABLE'))"!][!//
      #define CRC_32P4_CONFIGERROR_VAL      ([!"CrcGeneral/Crc32P4ReturnErrorValue"!])
      [!ENDIF!][!//
      [!/* [cover parentID={E86B6934-BAA5-4448-B38E-2B9DF5801EAF}] */!][!//
      [!/* [/cover] */!][!//
      [!IF "((CrcGeneral/Crc64Mode/__1 = 'CRC_64_RUNTIME') or (CrcGeneral/Crc64Mode/__1 = 'CRC_64_TABLE'))"!][!//
      #define CRC_64_CONFIGERROR_VAL      ([!"CrcGeneral/Crc64ReturnErrorValue"!])
      [!ENDIF!][!//
    [!ELSE!][!//
      /*Safety is disabled*/
      #define CRC_SAFETYENABLE  (STD_OFF)[!//

      /* ************************************************************************** */
    [!ENDIF!][!//
    [!IF "CrcGeneral/CrcDma8bitApi = 'true' or CrcGeneral/CrcDma16bitApi  = 'true' or
    CrcGeneral/CrcDma32bitApi  = 'true' or CrcGeneral/CrcDma32P4bitApi  = 'true'"!][!//"!][!//
      /*********************Macro for user/supervisory mode**************************/
      [!/* [cover parentID={33109129-E4F3-42a3-80B6-30DD41F04CAC}] */!][!//
      [!/* [/cover] */!][!//
      #define CRC_RUNTIME_API_MODE    ([!"CrcGeneral/CrcRuntimeApiMode"!])
      /* ************************************************************************** */
    [!ENDIF!][!//
  [!ENDINDENT!]
[!ENDSELECT!][!//

/****************************FCE-DMA allocation to Cores***********************/
[!NOCODE!][!//
[!INDENT "0"!][!//
  [!VAR "MasterCoreNumber" = "num:i(0)"!][!//
  [!/* Get the number of the core configured as the master core */!][!//
  [!CALL "Crc_CG_GetMasterCoreNumber", "MasterCoreNumber" = "num:i(0)"!][!//
  [!VAR "CGCoreAllocation" = "''"!][!//
  [!VAR "Totalnumber_of_FCEResource" = "num:i(0)"!][!//
  [!IF "node:exists(./CrcChannelConfig)"!][!//
    [!VAR "Totalnumber_of_FCEResource" = "num:i(count(CrcChannelConfig/*))"!][!//
    [!CODE!][!//
    [!/* [cover parentID={9F17926B-5BD2-4f4c-AA5F-FCECAF9AEC23}] */!][!//
    [!/* [/cover] */!][!//
    #define CRC_DMA_MAX_CHANNELS ([!"$Totalnumber_of_FCEResource"!]U)
    [!ENDCODE!][!//
    /*looping through each FCE resource to get the values*/
    [!FOR "FCE_ResourceIndex" = "num:i(0)" TO "num:i($Totalnumber_of_FCEResource) -1"!][!//
      [!SELECT "CrcChannelConfig/*[@index=$FCE_ResourceIndex]"!][!//
      [!VAR "FCEChannelID" = "(./CrcChannelId)"!][!//
      /*FCE channel*/
      [!VAR "Result_Handler" = "(./CrcResultNotification)"!][!//
      /*Result handler for FCE channel*/
      [!VAR "Error_Handler" = "(./CrcErrorNotification)"!][!//
      /*Error handler for FCE channel*/
      [!VAR "index" = "num:i(count(text:split(./CrcDmaChannel, '/')))"!][!//
      [!VAR "CrcDma_reseource" = "text:split(./CrcDmaChannel, '/')[num:i($index)]"!][!//
      /*find if the DMA resource belongs to CRC*/
      [!VAR "Check_Var" = "'false'"!][!//
      /*Macro to check if the Resource belongs to CRC,Check_Var is either true or false
      true: if the channel is allocated to CRC in DMA module
      false: if the channel is not allocated to CRC in DMA module*/
      [!CALL "Crc_CG_CheckDmaResource", "AllocationName" = "$CrcDma_reseource", "Module_Name" = "'CRC'", "Check_Var" = "'false'"!][!//
      [!IF "$Check_Var = 'false'"!][!//
        [!ERROR!][!//
           CRC Code Generator: Only configure the DMA channel allocated to the CRC module.
        [!ENDERROR!][!//
      [!ELSE!][!//
        [!VAR "CGCoreID" = "$MasterCoreNumber"!][!//
        [!CALL "Crc_CG_GenerateModuleMap", "AllocationName" = "$CrcDma_reseource", "Module"="'DMA'", "CGCoreID" = "$CGCoreID"!][!//
        /*add the core to the configured core list*/
        [!IF "not(contains(text:split($CGCoreAllocation), $CGCoreID))"!][!//
          [!VAR "CGCoreAllocation" = "concat($CGCoreAllocation, $CGCoreID, ',')"!][!//
        [!ELSE!][!//
          [!ERROR!][!//
            CRC Code Generator: CORE_[!"($CGCoreID)"!] has more than one DMA channel allocated (allowed is only one).
            Either remove the DMA channel allocation from Resource Manager or unallocate the DMA channel in CRC configuration.
          [!ENDERROR!][!//
        [!ENDIF!][!//
        /*we have DMA channel and core, lets check for the NULL_PTR error*/
      [!ENDIF!]
      [!ENDSELECT!][!//
    [!ENDFOR!][!//
  [!ELSE!][!//
    [!CODE!][!//
    #define CRC_DMA_MAX_CHANNELS ([!"$Totalnumber_of_FCEResource"!]U)
    [!ENDCODE!][!//
  [!ENDIF!][!//
  [!FOR "ChannelCoreIndex" = "0" TO "num:i(5)"!][!//
    [!VAR "ChannelCoreName" = "$ChannelCoreIndex"!][!//
    [!/* Check if the core is in the list */!][!//
    [!IF "not(contains(text:split($CGCoreAllocation), $ChannelCoreName))"!][!//
      [!CODE!][!//
      [!/* [cover parentID={8A0BAEE0-E7E2-4ab5-B072-F5E2037D6040}] */!][!//
      [!/* [/cover] */!][!//
      #define CRC_CONFIGURED_CORE[!"$ChannelCoreIndex"!] (STD_OFF)
      [!ENDCODE!][!//
    [!ELSE!][!//
      [!CODE!][!//
      #define CRC_CONFIGURED_CORE[!"$ChannelCoreIndex"!] (STD_ON)
      [!ENDCODE!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
[!ENDINDENT!][!//
[!ENDNOCODE!][!//
/* ************************************************************************** */
#endif  /* CRC_CFG_H */
