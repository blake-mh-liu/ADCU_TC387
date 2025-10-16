[!/*
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
**  FILENAME  : Crc.m                                                         **
**                                                                            **
**  VERSION   : 2.0.0                                                         **
**                                                                            **
**  DATE      : 2020-07-16                                                    **
**                                                                            **
**  BSW MODULE DESCRIPTION : NA                                               **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={E2889330-0E18-47f5-A8B6-51C775E5B296}]    **
**                                                                            **
**  DESCRIPTION  : Code template macro file for Crc Driver                    **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
*/!]
/******************************************************************************/
[!/* *** multiple inclusion protection*** */!][!//
[!IF "not(var:defined('CRC_M'))"!][!//
  [!VAR "CRC_M"="'true'"!][!//
[!AUTOSPACING!]

[!/*****************************************************************************
** Name             : Crc_CG_GetDmaChannelNumber                              **
**                                                                            **
** Description      : Macro to get the DMA channel assocuated with FCE        **
**                    Channel                                                 **
**                                                                            **
*****************************************************************************/!]
[!MACRO "Crc_CG_GetDmaChannelNumber", "AllocationName" = "", "DmaChannelNum" = ""!][!//
[!NOCODE!][!//
  [!VAR "AllocationName" = "concat($AllocationName, '#')"!]
  [!VAR "NodeName" = "''"!][!//
  [!SELECT "as:modconf('Dma')[1]"!][!//
    [!IF "node:exists(./DmaChannelConfig)"!][!//
      [!VAR "NoOfDmaCh" = "num:i(count(DmaChannelConfig/*))"!][!//
      [!FOR "ChannelIndex" = "num:i(0)" TO "num:i($NoOfDmaCh) -1"!][!//
        [!SELECT "DmaChannelConfig/*[@index=$ChannelIndex]"!][!//
          [!VAR "NodeName" = "node:name(.)"!][!//
          [!VAR "NodeName" = "concat($NodeName, '#')"!][!//
          [!IF "text:match($NodeName, $AllocationName) = 'true'"!][!//
             [!VAR "DmaChannelNum" = "num:i(DmaChannelId)"!][!//
             [!VAR "Dma_Result_Handler" = "(./DmaChannelNotification)"!][!//
             [!IF "$Dma_Result_Handler = 'NULL_PTR'"!][!//
                [!ERROR!][!//
                   CRC Code Generator: Configure the DmaChannelNotification pointer to the CRC notification callback function in the DMA resource assigned to the CRC module.
                [!ENDERROR!][!//
             [!ENDIF!][!//
             [!VAR "Dma_Error_Handler" = "(./DmaErrorNotification)"!][!//
             [!IF "$Dma_Error_Handler = 'NULL_PTR'"!][!//
                [!ERROR!][!//
                   CRC Code Generator: Configure the DmaErrorNotification pointer to the CRC error callback function in the DMA rersource assigned to the CRC module.
                [!ENDERROR!][!//
             [!ENDIF!][!//
          [!ENDIF!][!//
        [!ENDSELECT!][!//
      [!ENDFOR!][!//
    [!ENDIF!][!//
  [!ENDSELECT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
** Name             : Crc_CG_CheckDmaResource                                 **
**                                                                            **
** Description      : Macro to Validate the DMA channel available for CRC     **
**                    Channel                                                 **
**                                                                            **
*****************************************************************************/!]
[!MACRO "Crc_CG_CheckDmaResource", "AllocationName" = "", "Module_Name" = "", "Check_Var" = ""!][!//
[!NOCODE!][!//
  [!VAR "AllocationName" = "concat($AllocationName, '#')"!]
  [!VAR "NodeName" = "''"!][!//
  [!SELECT "as:modconf('Dma')[1]"!][!//
    [!IF "node:exists(./DmaChannelConfig)"!][!//
      [!VAR "NoOfDmaCh" = "num:i(count(DmaChannelConfig/*))"!][!//
      [!FOR "ChannelIndex" = "num:i(0)" TO "num:i($NoOfDmaCh) -1"!][!//
        [!SELECT "DmaChannelConfig/*[@index=$ChannelIndex]"!][!//
            [!VAR "NodeName" = "node:name(.)"!][!//
            [!VAR "NodeName" = "concat($NodeName, '#')"!][!//
            [!IF "text:match($NodeName, $AllocationName) = 'true'"!][!//
              [!VAR "Channel_Module" = "(./DmaChannelUser)"!][!//
              [!IF "text:match($Channel_Module, "CRC") = 'True'"!][!//
                [!VAR "Module_Name" = "$Channel_Module"!][!//
                [!VAR "Check_Var" = "'true'"!][!//
              [!ENDIF!][!//
            [!ENDIF!][!//
        [!ENDSELECT!][!//
      [!ENDFOR!][!//
    [!ENDIF!][!//
  [!ENDSELECT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//


[!/*****************************************************************************
** Name             : Crc_CG_GenerateModuleMap                                **
**                                                                            **
** Description      : Macro to get the core of the cofigured DMA channel      **
**                                                                            **
*****************************************************************************/!]
[!MACRO "Crc_CG_GenerateModuleMap", "AllocationName" = "",  "Module" = "", "CGCoreID"=""!][!//
[!NOCODE!][!//
  [!/* Select the resource manager */!]
  [!VAR "Check_" = "'false'"!][!//
  [!SELECT "as:modconf('ResourceM')[1]"!][!//
    [!/* Find the master core ID which is configured. Only get the core number, not the entire string. */!]
    [!VAR "CGMasterCoreId" = "substring(node:value(ResourceMMcalConfig/*[1]/ResourceMMasterCore),5,1)"!][!//
    [!/* Now, enter into the list of all the cores  */!]
    [!LOOP "ResourceMMcalConfig/*[1]/ResourceMMcalCore/*"!][!// /**/
      [!VAR "Check_" = "'false'"!][!//
      [!/* Lets get into the core specific configurations */!]
      [!VAR "CoreID" = "./ResourceMCoreID"!][!//
      [!/* Lets loop through the allocated resources */!]
      [!LOOP "ResourceMAllocation/*"!][!//
        [!/* Is this resource for the module under consideration? */!]
        [!IF "$Module = ./ResourceMModuleName"!][!//
          [!/* Is that a valid node or not? */!]
          [!IF "node:refvalid(./ResourceMResourceRef)"!][!//
            [!/* Split the resource string based on '/' */!][!//
            [!VAR "index" = "num:i(count(text:split(./ResourceMResourceRef, '/')))"!][!//
            [!/* Get the resource name */!][!//
            [!VAR "ResourceName" = "text:split(./ResourceMResourceRef, '/')[num:i($index)]"!][!//
              [!IF "$ResourceName = $AllocationName"!][!//
                [!VAR "CGCoreID" = "$CoreID"!][!//
                [!VAR "CGCoreID" = "num:i(substring($CGCoreID, 5, 1))"!][!//
                [!VAR "Check_" = "'true'"!][!//
                [!BREAK!]
              [!ENDIF!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDLOOP!][!//
        [!IF "$Check_ = 'true'"!][!//
         [!BREAK!]
        [!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ENDSELECT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
** Name             : Crc_CG_GetMasterCoreNumber                              **
**                                                                            **
** Description      : Macro to Get MasterCore                                 **
**                    Channel                                                 **
**                                                                            **
*****************************************************************************/!]
[!MACRO "Crc_CG_GetMasterCoreNumber", "MasterCoreNumber" = ""!][!//
[!NOCODE!][!//
  [!SELECT "as:modconf('ResourceM')[1]"!][!//
    [!VAR "MasterCoreName" = "as:modconf('ResourceM')[1]/ResourceMMcalConfig/*[1]/ResourceMMasterCore"!][!//
    [!VAR "MasterCoreNumber" = "num:i(substring($MasterCoreName, 5, 1))"!][!//
  [!ENDSELECT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!ENDIF!][!// IF "not(var:defined('CRC_M'))
