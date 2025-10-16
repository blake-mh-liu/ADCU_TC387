[!AUTOSPACING!]
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
**  FILENAME  : Dio_Lcfg.c                                                    **
**                                                                            **
**  VERSION   : 7.0.0                                                         **
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
**  TRACEABILITY : [cover parentID=]                                          **
**                                                                            **
**  DESCRIPTION  : Code template source file for Dio Driver                   **
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
**  FILENAME  : Dio_Lcfg.c                                                    **
**                                                                            **
**  VERSION   : 7.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]       !!!IGNORE-LINE!!!                  **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]           !!!IGNORE-LINE!!!                **
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
**                    and AUTOSAR Release 4.4.0                               **
**                                                                            **
** MAY BE CHANGED BY USER : no                                                **
**                                                                            **
*******************************************************************************/
[!//
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!/* [cover parentID={230C506C-DB5B-4759-95EF-D9E93D9BB391}] [/cover] */!][!//
[!/* [cover parentID={2E5CB007-76A6-4fa2-9FDD-70B526C70B83}] [/cover] */!][!//


[!SELECT "as:modconf('Dio')[1]"!][!//
  [!//
  [!/* Include Code Generator Macros */!][!//
  [!NOCODE!][!//
    [!INCLUDE "..\Dio.m"!][!//
  [!//
  [!ENDNOCODE!][!//

  /*******************************************************************************
  **                             Includes                                       **
  *******************************************************************************/

  /* Include Port Module File */
  #include "Dio.h"

  /*******************************************************************************
  **                      Private Macro Definitions                             **
  *******************************************************************************/

  /*******************************************************************************
  **                      Global Constant Definitions                           **
  *******************************************************************************/
  [!/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}] [/cover] */!][!// 
  /* Memory mapping of the DIO configuration */
  #define DIO_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  /* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines 
  Dio_Memmap.h header is included without safegaurd.*/
  #include "Dio_MemMap.h"
  /*
      Configuration of DIO Channel groups 
  */
  [!CODE!]
    [!CALL "Dio_GetDioChannelGroupDefinition"!][!//
  [!ENDCODE!]
  [!INDENT "2"!]
  static const Dio_PortChannelIdType Dio_kPortChannelConfig[] =
  { 
  [!ENDINDENT!]
      [!NOCODE!]
      [!INDENT "4"!][!//
      [!CALL "Dio_check_duplicate_DioPortId"!][!//
      [!FOR "PortNumber" = "num:i(0)" TO "ecu:get('Dio.MaxAvailablePort')"!][!//
        [!IF "contains(ecu:get('Dio.AvailablePorts'), concat('_', $PortNumber, '_'))"!][!//
          [!CODE!][!// 
          {
           /* Port[!"$PortNumber"!]*/[!//
          [!ENDCODE!][!//
          [!CALL "Dio_check_duplicate_DioPortChannelId", "PortNum" = "$PortNumber"!][!//
          [!CALL "Dio_GetDioConfiguredChannelInfo", "PortNum" = "$PortNumber"!][!// 
          [!CODE!][!// 
          }[!IF "$PortNumber != ecu:get('Dio.MaxAvailablePort')"!],[!ENDIF!][!CR!][!// 
          [!ENDCODE!][!//
       [!ENDIF!][!//
      [!ENDFOR!][!//
      [!ENDINDENT!][!//
      [!ENDNOCODE!]
    [!INDENT "2"!]
    };
   [!ENDINDENT!]
  [!/* [cover parentID={5393CD15-76E7-4b77-827F-B666E3B69509}] [/cover] */!][!//
  const Dio_ConfigType Dio_Config =
    {
      [!CODE!]
      [!CALL "Dio_GVerify_Unique_Channel_Name"!][!//
      [!CALL "Dio_GVerify_Unique_Channel_Grp_Name"!][!//
      [!CALL "Dio_GetNumOfDioChannelGroupsConfigured"!][!//

      /* Dio Port and Channelconfiguration */
      [!/* [cover parentID={11836F6F-13BA-4255-A9B5-AD42A5FFFF98}] [/cover] */!][!//
      &Dio_kPortChannelConfig[0],
      /* Dio Channelgroup configuration */
      [!/* [cover parentID={309BDA24-47D0-40fb-B831-53FBF32B9D3F}] [/cover] */!][!//    
      [!IF "$NumOfGroups != num:i(0)"!][!//
        &Dio_kChannelGroupConfig[0],
      [!ELSE!][!//
      NULL_PTR,
      [!ENDIF!][!//
      /* Configured number of Dio Channelgroups for configuration */
      DIO_CHANNELGROUPCOUNT
      [!ENDCODE!]
    };[!//

  #define DIO_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
    /* MISRA2012_RULE_4_10_JUSTIFICATION: To be compliant with autosar guidelines 
    Dio_Memmap.h header is included without safegaurd.*/
    /* MISRA2012_RULE_20_1_JUSTIFICATION: Dio_Memmap.h header included as per Autosar 
    guidelines. */
  #include "Dio_MemMap.h"

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
[!ENDSELECT!][!//
