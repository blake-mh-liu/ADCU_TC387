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
**  FILENAME  : Stm_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 6.0.0                                                         **
**                                                                            **
**  DATE      : 2023-05-24                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Stm.bmd                                           **
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
**  DESCRIPTION  : Code template header file for Stm Driver                   **
**                                                                            **
**  SPECIFICATION(S) : Specification of Stm Driver                            **
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
**  FILENAME  : Stm_Cfg.h                                                     **
**                                                                            **
**  VERSION   : 6.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]                 !!!IGNORE-LINE!!!     **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                     !!!IGNORE-LINE!!!     **
**                                                                            **
**  BSW MODULE DECRIPTION : Stm.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Stm configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Requirements of Stm Driver                             **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef STM_CFG_H
#define STM_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
** Traceabilty      :                                                         **
*******************************************************************************/
[!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
[!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
[!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
#define STM_AR_RELEASE_MAJOR_VERSION     ([!"$MajorVersion"!]U)
#define STM_AR_RELEASE_MINOR_VERSION     ([!"$MinorVersion"!]U)
#define STM_AR_RELEASE_REVISION_VERSION  ([!"$RevisionVersion"!]U)

[!VAR "MajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
[!VAR "MinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
[!VAR "RevisionVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
[!VAR "NewString" = "text:replaceAll($moduleSoftwareVer,"\.",'')"!][!//
#define STM_SW_MAJOR_VERSION  ([!"$MajorVersion"!]U)
#define STM_SW_MINOR_VERSION  ([!"$MinorVersion"!]U)
#define STM_SW_PATCH_VERSION  ([!"$RevisionVersion"!]U)

#define    STM_CMP0_CMP1_UNUSED        (0xFFU)
#define    STM_CMP0_USED               (0x0U)
#define    STM_CMP1_USED               (0x1U)
#define    STM_CMP0_CMP1_USED          (0x2U)

#define    STM_TIMER_UNUSED            (0xFFU)

/*
  Configuration Options for the setting the privilege mode in ADC Driver
*/
#define STM_MCAL_SUPERVISOR  (0U)
#define STM_MCAL_USER1       (1U)


#define  STM_0  (0x0U)
#define  STM_1  (0x1U)
#define  STM_2  (0x2U)
#define  STM_3  (0x3U)
[!INDENT "0"!][!//
  [!IF "(ecu:get('Mcu.NoOfCoreAvailable') > num:i(4))"!]
    #define  STM_4  (0x4U)
    #define  STM_5  (0x5U)
  [!ENDIF!]
[!ENDINDENT!][!//
[!SELECT "as:modconf('Stm')[1]"!][!//
  [!INCLUDE "../Stm.m"!][!//
  [!VAR "TotalResourceMcalCore" = "num:i(0)"!][!//
  [!VAR "MasterCoreId" = "''"!][!//
  [!/* Include Code Generator Macros */!][!//
  [!NOCODE!][!//
    [!CALL "STM_GenerateModuleMap","Module" = "'STM'"!][!//
      [!VAR "Flag0" = "num:i(0)"!][!//
      [!VAR "Flag1" = "num:i(0)"!][!//
      [!VAR "Flag2" = "num:i(0)"!][!//
      [!VAR "Flag3" = "num:i(0)"!][!//
      [!VAR "Flag4" = "num:i(0)"!][!//
      [!VAR "Flag5" = "num:i(0)"!][!//
      [!VAR "TotalCoreMaps" = "num:i(count(text:split($CGCoreMap, ',')))"!][!//
      [!FOR "CoreIndex" = "num:i(1)" TO "$TotalCoreMaps"!][!//
        [!VAR "CoreMap1" = "text:split($CGCoreMap, ',')[num:i($CoreIndex)]"!][!//
        [!VAR "coreid" = "substring-before($CoreMap1, '_')"!][!//
        [!VAR "coreid" = "substring-after($coreid, 'CORE')"!][!//
        [!IF "$coreid = num:i(0)"!][!//
          [!VAR "Flag0" = "num:i($Flag0 + num:i(1))"!][!//
        [!ELSEIF "$coreid = num:i(1)"!][!//
          [!VAR "Flag1" = "num:i($Flag1 + num:i(1))"!][!//
        [!ELSEIF "$coreid = num:i(2)"!][!//
          [!VAR "Flag2" = "num:i($Flag2 + num:i(1))"!][!//
        [!ELSEIF "$coreid = num:i(3)"!][!//
          [!VAR "Flag3" = "num:i($Flag3 + num:i(1))"!][!//
        [!ELSEIF "$coreid = num:i(4)"!][!//
          [!VAR "Flag4" = "num:i($Flag4 + num:i(1))"!][!//
        [!ELSEIF "$coreid = num:i(5)"!][!//
          [!VAR "Flag5" = "num:i($Flag5 + num:i(1))"!][!//
        [!ENDIF!][!//
      [!ENDFOR!][!//
      [!IF "$TotalCoreMaps = num:i(0)"!][!//
        [!IF "$MasterCoreId = 'CORE0'"!][!//
          [!VAR "Flag0" = "num:i($Flag0 + num:i(1))"!][!//
        [!ELSEIF "$MasterCoreId = 'CORE1'"!][!//
          [!VAR "Flag1" = "num:i($Flag1 + num:i(1))"!][!//
        [!ELSEIF "$MasterCoreId = 'CORE2'"!][!//
          [!VAR "Flag2" = "num:i($Flag2 + num:i(1))"!][!//
        [!ELSEIF "$MasterCoreId = 'CORE3'"!][!//
          [!VAR "Flag3" = "num:i($Flag3 + num:i(1))"!][!//
        [!ELSEIF "$MasterCoreId = 'CORE4'"!][!//
          [!VAR "Flag4" = "num:i($Flag4 + num:i(1))"!][!//
        [!ELSEIF "$MasterCoreId = 'CORE5'"!][!//
          [!VAR "Flag5" = "num:i($Flag5 + num:i(1))"!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
  [!ENDNOCODE!]
/* Maximum number of timers configured in each core */
#define STM_CORE0_MAX_TIMERS       (0x[!"$Flag0"!]U)
#define STM_CORE1_MAX_TIMERS       (0x[!"$Flag1"!]U)
#define STM_CORE2_MAX_TIMERS       (0x[!"$Flag2"!]U)
#define STM_CORE3_MAX_TIMERS       (0x[!"$Flag3"!]U)
#define STM_CORE4_MAX_TIMERS       (0x[!"$Flag4"!]U)
#define STM_CORE5_MAX_TIMERS       (0x[!"$Flag5"!]U)

/*
                    Container:StmGeneral
*/
/*
  Configuration of Development Error Detection 
  API Parameter Checking is enabled if this compiler
  switch is STD_ON. 
  - if STD_ON, Development error detection is enabled
  - if STD_OFF, Development error detection is disabled
*/
#define STM_DEV_ERROR_DETECT                ([!//
[!IF "StmGeneral/StmDevErrorDetect = 'true'"!][!//
  STD_ON[!//
[!ELSE!][!//
  STD_OFF[!//
[!ENDIF!][!//
)

/*
  Configuration: STM_VERSION_INFO_API :
  Configuration of version information  
  Adds/removes the Stm_GetVersionInfo() API from the code 
  - if STD_ON, Stm_GetVersionInfo() is available in the code
  - if STD_OFF, Stm_GetVersionInfo() is not available in the code
*/
#define STM_VERSION_INFO_API                ([!//
[!IF "StmGeneral/StmVersionInfoApi = 'true'"!][!//
  STD_ON[!//
[!ELSE!][!//
  STD_OFF[!//
[!ENDIF!][!//
)

/* production error reporting enable/disabled macro */
#define STM_ENABLE_DEM_REPORT  (1U)
#define STM_DISABLE_DEM_REPORT (0U)


/* production error enable/disable for STM module clock enable failure */
[!INDENT "0"!][!//
  [!VAR "StmDemReportStatus" = "num:i(0)"!][!//
  [!IF "node:exists(StmDemEventParameterRefsConf/*[1])"!][!//
    [!IF "node:refexists(StmDemEventParameterRefsConf/*[1]/STM_E_CLC_ENABLE_ERR/*[1]) and (node:value(StmDemEventParameterRefsConf/*[1]/STM_E_CLC_ENABLE_ERR/*[1]) != ' ' )"!]
      #define STM_E_CLC_ENABLE_ERR_DEM_REPORT    (STM_ENABLE_DEM_REPORT)
      #define STM_E_CLC_ENABLE_ERR                \
      (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(StmDemEventParameterRefsConf/*[1]/STM_E_CLC_ENABLE_ERR/*[1])))"!])[!//
      [!VAR "StmDemReportStatus" = "num:i(1)"!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
  [!IF "$StmDemReportStatus = num:i(0)"!][!//
    #define STM_E_CLC_ENABLE_ERR_DEM_REPORT    (STM_DISABLE_DEM_REPORT)
  [!ENDIF!][!//
[!ENDINDENT!][!//

/*
Configuration: STM_RUNTIME_API_MODE 
  - if STM_MCAL_USER1 is selected   User1 Mode is enabled 
  - if STM_MCAL_SUPERVISOR is selected Runtime Mode is enabled 
*/
[!VAR "Stm_UserModeSelection" = "StmGeneral/StmRuntimeApiMode"!][!//
#define STM_RUN_TIME_API_MODE                ([!//
[!IF "$Stm_UserModeSelection = 'STM_MCAL_SUPERVISOR'"!][!//
  STM_MCAL_SUPERVISOR[!//
[!ELSE!][!//
  STM_MCAL_USER1[!//
[!ENDIF!][!//
)

[!VAR "StmMaxTim" = "ecu:get('Mcu.NoOfCoreAvailable')"!][!//  
/*
  Total number of STM timers availability
*/
#define STM_MAX_TIMERS      (0x[!"$StmMaxTim"!]U)

[!ENDSELECT!][!//

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/
#endif
