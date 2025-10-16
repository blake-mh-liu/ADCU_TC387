[!/****************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2023)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME    : Iom_Cfg.h                                                  **
**                                                                           **
**  VERSION     : 4.0.0                                                      **
**                                                                           **
**  DATE        : 2023-05-23                                                 **
**                                                                           **
**  BSW MODULE DECRIPTION : NA                                               **
**                                                                           **
**  VARIANT   : Variant PB                                                   **
**                                                                           **
**  PLATFORM  : Infineon AURIX2G                                             **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : This file contains                                         **
**                Code template for Iom_Cfg.h file                           **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: No                                      **
**                                                                           **
******************************************************************************/!][!//
[!//
/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2023)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Iom_Cfg.h                                                   **
**                                                                           **
**  VERSION    : 4.0.0                                                       **
**                                                                           **
**  DATE, TIME: [!"$date"!], [!"$time"!]            !!!IGNORE-LINE!!!        **
**                                                                           **
**  GENERATOR : Build [!"$buildnr"!]                 !!!IGNORE-LINE!!!       **
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
**  DESCRIPTION  : IOM configuration generated out of ECU configuration      **
**                 file (Iom.bmd/.xdm)                                       **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: No                                      **
**                                                                           **
******************************************************************************/


#ifndef IOM_CFG_H
#define IOM_CFG_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/


[!SELECT "as:modconf('Iom')[1]"!][!//
  [!INDENT "0"!][!//
    [!//
    [!AUTOSPACING!][!// 

    [!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
    [!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
    [!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//

    #define IOM_AR_RELEASE_MAJOR_VERSION      ([!"$MajorVersion"!]U)
    #define IOM_AR_RELEASE_MINOR_VERSION      ([!"$MinorVersion"!]U)
    #define IOM_AR_RELEASE_REVISION_VERSION   ([!"$RevisionVersion"!]U)

    [!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
    [!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
    [!VAR "SwPatchVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//

    #define IOM_SW_MAJOR_VERSION              ([!"$SwMajorVersion"!]U)
    #define IOM_SW_MINOR_VERSION              ([!"$SwMinorVersion"!]U)
    #define IOM_SW_PATCH_VERSION              ([!"$SwPatchVersion"!]U)  



    /* Configuration: IOM_VERSION_INFO_API
    Preprocessor switch for enabling version information Iom_GetVersionInfo() API  
    - if STD_ON, VersionInfo API is Enabled 
    - if STD_OFF, VersionInfo API is Disabled 
    */
    #define IOM_VERSION_INFO_API  ([!//
    [!IF "IomGeneral/IomVersionInfoApi = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )

    /* Configuration: IOM_DEINIT_API
    Preprocessor switch for enabling Iom_Deinit API 
    - if STD_ON, Deinit API is Enabled 
    - if STD_OFF, Deinit API is Disabled 
    */
    #define IOM_DEINIT_API  ([!//
    [!IF "IomGeneral/IomDeInitApi = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )

    /*
    Configuration: IOM_DEV_ERROR_DETECT
    Preprocessor switch for enabling the development error detection and 
    reporting. 
    - if STD_ON, DET is Enabled 
    - if STD_OFF,DET is Disabled 
    */
    #define IOM_DEV_ERROR_DETECT  ([!//
    [!IF "IomGeneral/IomDevErrorDetect = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )

    /*
    Configuration: IOM_GTM_AVAILABLE
    Preprocessor switch for checcking wheteher GTM is available */
    #define IOM_GTM_AVAILABLE ([!//
    [!IF "ecu:get('Gtm.Available')='true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
   
    /* Instance id for the IOM module */
    #define IOM_INSTANCE_ID ([!"(IomGeneral/IomIndex )"!]U)

    /*
      Configuration Options for Production error
      Options for the enabling/disabling of Production error in IOM Driver
    */
    #define IOM_DISABLE_DEM_REPORT  (0U)
    #define IOM_ENABLE_DEM_REPORT   (1U)

    /* Production error enable/disable for IOM module clock enable failure */
    [!VAR "IomDemReportStatus" = "num:i(0)"!][!//
    [!IF "node:exists(IomDemEventParameterRefsConf/*[1])"!][!//
      [!IF "node:refexists(IomDemEventParameterRefsConf/*[1]/IomClcFailureNotification/*[1]) and (node:value(IomDemEventParameterRefsConf/*[1]/IomClcFailureNotification/*[1]) != ' ' )"!]
        #define IOM_E_CLC_ENABLE_ERR_DEM_REPORT    (IOM_ENABLE_DEM_REPORT)
        #define IOM_E_CLC_ENABLE_ERR                \
        (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(IomDemEventParameterRefsConf/*[1]/IomClcFailureNotification/*[1])))"!])[!//
        [!VAR "IomDemReportStatus" = "num:i(1)"!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!IF "$IomDemReportStatus = num:i(0)"!][!//
      #define IOM_E_CLC_ENABLE_ERR_DEM_REPORT    (IOM_DISABLE_DEM_REPORT)
    [!ENDIF!][!//

    /*
      Configuration Options for the setting the privilege mode in IOM Driver
    */
    #define IOM_MCAL_SUPERVISOR  (0U)
    #define IOM_MCAL_USER1       (1U)
    /*
    Configuration: IOM_INIT_DEINIT_API_MODE
    - if STD_ON, Enable Protected Mode(user mode) in Init API 
    - if STD_OFF, Enable Supervisor mode in Init API  
    */
    [!IF "IomGeneral/IomInitDeInitApiMode = 'IOM_MCAL_SUPERVISOR'"!][!//
      #define IOM_INIT_DEINIT_API_MODE                     (IOM_MCAL_SUPERVISOR)
    [!ELSE!][!//
      #define IOM_INIT_DEINIT_API_MODE                     (IOM_MCAL_USER1)
    [!ENDIF!][!//

    /*Configuration: IOM_RUN_TIME_API_MODE
    - if STD_ON, Enable Protected mode in APIs other than Init/Deinit APIs
    - if STD_OFF, Disable Protected mode in APIs other than Init/Deinit APIs
    */
    [!IF "IomGeneral/IomRuntimeApiMode = 'IOM_MCAL_SUPERVISOR'"!][!//
      #define IOM_RUN_TIME_API_MODE (IOM_MCAL_SUPERVISOR)
    [!ELSE!][!//
      #define  IOM_RUN_TIME_API_MODE (IOM_MCAL_USER1)
    [!ENDIF!][!//

    /*******************************************************************************
    **                      Global Symbols                                        **
    *******************************************************************************/




     /******************************************************************************
    **                      Global Macro Definitions                              **
    *******************************************************************************/


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
  [!ENDINDENT!][!//
[!ENDSELECT!][!//
#endif  /* IOM_CFG_H */
