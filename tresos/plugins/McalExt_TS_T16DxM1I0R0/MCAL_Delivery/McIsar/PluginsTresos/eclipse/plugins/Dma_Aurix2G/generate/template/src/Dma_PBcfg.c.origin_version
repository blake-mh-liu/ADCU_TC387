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
**  FILENAME  : Dma_PBCfg.c                                                   **
**                                                                            **
**  VERSION   : 16.0.0                                                        **
**                                                                            **
**  DATE      : 2021-02-22                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : NA                                                **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID= {367B973F-B7B8-45dc-B522-D9277605761E}]   **
**                                                                            **
**  DESCRIPTION  : Code template source file for Dma Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
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
**  FILENAME  : Dma_PBCfg.c                                                   **
**                                                                            **
**  VERSION   : 16.0.0                                                        **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]               !!!IGNORE-LINE!!!          **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                 !!!IGNORE-LINE!!!          **
**                                                                            **
**  BSW MODULE DECRIPTION : NA                                                **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Dma configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
[!//
[!VAR "VariantsConfigured" = "num:i(0)"!]
[!SELECT "as:modconf('EcuC')[1]"!][!//
  [!IF "node:exists(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!][!//
    [!VAR "PredefinedVarName1" = "(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!]
    [!VAR "PredefinedVarName2" = "substring-after($PredefinedVarName1, "/")"!][!//
    [!VAR "PredefinedVarName3" = "substring-after($PredefinedVarName2, "/")"!][!//
    [!VAR "PredefinedVarName" = "substring-after($PredefinedVarName3, "/")"!][!//
    [!VAR "VariantsConfigured" = "num:i(1)"!]
  [!ENDIF!][!//
[!ENDSELECT!][!//
[!IF "not(node:exists(as:modconf('ResourceM')[1]))"!]
  [!ERROR!][!//
    DMA Code Generator: ResourceM module is not added to the project.
  [!ENDERROR!][!//
[!ENDIF!]
[!IF "not(node:exists(as:modconf('Mcu')[1]))"!]
  [!ERROR!][!//
    DMA Code Generator: Mcu module is not added to the project.
  [!ENDERROR!][!//
[!ENDIF!]
[!IF "not(node:exists(as:modconf('McalLib')[1]))"!]
  [!ERROR!][!//
    DMA Code Generator: McalLib module is not added to the project.
  [!ENDERROR!][!//
[!ENDIF!]
[!NOCODE!][!//
  [!INCLUDE "Dma.m"!][!//
[!ENDNOCODE!][!//
[!/* [cover parentID={EA4BB141-5DA0-4503-8923-417FB7BE153B}]Dependent Module Checks[/cover] */!][!//

/*******************************************************************************
**                            Includes                                        **
*******************************************************************************/
/* Include module header file */
#include "Dma.h"
[!SELECT "as:modconf('Dma')[1]"!][!//
[!AUTOSPACING!][!//

/*******************************************************************************
**                    Customer specific includes                              **
*******************************************************************************/
[!NOCODE!][!//
  [!INDENT "0"!][!//
    [!VAR "HeaderList" = "''"!]
    [!VAR "NoOfDmaChannels" = "num:i(count(DmaChannelConfig/*))"!][!//
    [!VAR "ChannelIndex" = "num:i(0)"!][!//
    [!FOR "ChannelIndex" = "num:i(0)" TO "num:i($NoOfDmaChannels) -1"!][!//
      [!IF "node:exists(./DmaChannelConfig/*[@index=$ChannelIndex])"!][!//
        [!SELECT "DmaChannelConfig/*[@index=$ChannelIndex]"!][!//
          [!VAR "ChannelTcsIndex" = "num:i(0)"!][!//
          [!VAR "NoOfTCS" = "num:i(count(DmaChannelTransactionSet/*))"!][!//
          [!FOR "ChannelTcsIndex" = "num:i(0)" TO "num:i($NoOfTCS) - num:i(1)"!][!//
            [!SELECT "DmaChannelTransactionSet/*[@index=$ChannelTcsIndex]"!][!//
              [!CODE!][!//
                [!IF "node:exists(./DmaUserHeaderFileWithExternDeclarations)"!][!//
                    [!VAR "HeaderFile" = "DmaUserHeaderFileWithExternDeclarations"!][!//
                    [!IF "$HeaderFile != 'NULL'"!][!//
                      [!VAR "HeaderSearchPattern" = "concat('<', $HeaderFile, '>')"!][!//
                      [!IF "not(contains($HeaderList, $HeaderSearchPattern))"!][!//
                        #include "[!"$HeaderFile"!]"
                        [!VAR "HeaderList" = "concat($HeaderList, '<', $HeaderFile, '>,')"!][!//
                      [!ENDIF!][!//
                    [!ENDIF!][!//
                [!ELSE!][!//
                  [!WARNING "Warning: The specified resource does not exist!!"!][!//
                [!ENDIF!][!//
              [!ENDCODE!][!//
            [!ENDSELECT!][!//
          [!ENDFOR!][!//
        [!ENDSELECT!][!//
      [!ELSE!][!//
        [!WARNING "Warning: The specified resource does not exist!!"!][!//
      [!ENDIF!][!//  
    [!ENDFOR!][!//
  [!ENDINDENT!][!//
[!ENDNOCODE!][!//

[!VAR "DmaMaxChannels" = "ecu:get('Dma.MaxDmaChannel')"!][!//
/*******************************************************************************
**          Channel specific move engine error notification functions         **
*******************************************************************************/

/* User defined move engine error notification functions to be called by DMA driver in case
 * of error  */[!CR!]
[!IF "node:exists(./DmaChannelConfig)"!][!//
  [!VAR "NoOfDmaChannels" = "num:i(count(DmaChannelConfig/*))"!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!FOR "ChannelIndex" = "num:i(0)" TO "num:i($NoOfDmaChannels) - num:i(1)"!][!//
    [!IF "node:exists(./DmaChannelConfig/*[@index=$ChannelIndex])"!][!//
      [!SELECT "DmaChannelConfig/*[@index=$ChannelIndex]"!][!//
        [!IF "node:exists(DmaChannelNotification)"!][!//
          [!VAR "RPNotification" = "DmaErrorNotification"!][!//
          [!INDENT "0"!][!//
            /* Channel specific Error notification function for Channel [!"num:i(DmaChannelId)"!]  */ 
            [!IF "$RPNotification != 'NULL_PTR'"!][!//
              extern void [!"$RPNotification"!](uint8 Channel, uint32 Event);
            [!ELSE!][!//
              /* <**No notification function is configured for this Channel**> */
            [!ENDIF!][!//
          [!ENDINDENT!][!//
        [!ELSE!]
          [!WARNING "Warning: The specified resource does not exist!!"!][!//
        [!ENDIF!][!//
      [!ENDSELECT!][!//
    [!ELSE!]
      [!WARNING "Warning: The specified resource does not exist!!"!][!//
    [!ENDIF!][!//
  [!ENDFOR!][!//
[!ELSE!]
  [!WARNING "Warning: The specified resource does not exist!!"!][!//
[!ENDIF!][!//
  
/* ************************************************************************** */

/*******************************************************************************
**              Channel specific notification functions                       **
*******************************************************************************/

/* User defined notification functions for channels to be called by
 * the DMA driver in case of channel interrupts */
[!IF "node:exists(./DmaChannelConfig)"!][!//
  [!INDENT "0"!][!//
    [!VAR "ChNotificationExists" = "'False'"!]
    [!VAR "NoOfDmaChannels" = "num:i(count(DmaChannelConfig/*))"!][!//
    [!VAR "ChannelIndex" = "num:i(0)"!][!//
    [!FOR "ChannelIndex" = "num:i(0)" TO "num:i($NoOfDmaChannels) -1"!][!//
      [!IF "node:exists(./DmaChannelConfig/*[@index=$ChannelIndex])"!][!//
        [!SELECT "DmaChannelConfig/*[@index=$ChannelIndex]"!][!//
          [!IF "node:exists(DmaChannelNotification)"!][!//
            [!IF "DmaChannelNotification != 'NULL_PTR'"!][!//
              /* Channel specific notification function for Channel [!"num:i(DmaChannelId)"!]  */
              extern void [!"DmaChannelNotification"!](uint8 Channel, uint32 Event);
              [!VAR "ChNotificationExists" = "'True'"!]
            [!ENDIF!]
          [!ELSE!]
            [!WARNING "Warning: The specified resource does not exist!!"!][!//
          [!ENDIF!][!//
        [!ENDSELECT!]
      [!ELSE!]
        [!WARNING "Warning: The specified resource does not exist!!"!][!//
      [!ENDIF!][!//
    [!ENDFOR!]
    [!IF "$ChNotificationExists = 'False'"!][!//
      /* <***** No Channel specific notifications are configured *****> */
    [!ENDIF!]
  [!ENDINDENT!][!//
[!ELSE!]
  [!WARNING "Warning: The specified resource does not exist!!"!][!//
[!ENDIF!][!//
/* ******************************************************************* */

[!SELECT "as:modconf('ResourceM')[1]"!][!//
  [!VAR "MasterCoreName" = "as:modconf('ResourceM')[1]/ResourceMMcalConfig/*[1]/ResourceMMasterCore"!]
  [!VAR "MasterCoreNumber" = "substring($MasterCoreName, 5, 1)"!][!//
[!ENDSELECT!][!//
[!/* Get all the core and channel mappings from the Resource Manager */!]
[!CALL "Dma_CG_GenerateModuleMap", "Module"="'DMA'"!][!//
[!NOCODE!][!//
  [!// Variable to hold linklistenable and doublebuffer status !][!//
  [!VAR "Dma_DoubleBufferControl" = "'STD_OFF'"!]
  [!VAR "LinkListEnable" = "'STD_OFF'"!][!//
  [!VAR "NoOfDmaChannels" = "num:i(count(DmaChannelConfig/*))"!][!//
  [!VAR "ChannelIndex" = "num:i(0)"!][!//
  [!/* Lets iterate through each of the available channels */!][!//
  [!FOR "ChannelIndex" = "num:i(0)" TO "num:i($NoOfDmaChannels) - num:i(1)"!][!//
    [!SELECT "DmaChannelConfig/*[@index=$ChannelIndex]"!][!//
      [!VAR "NoOfTCS" = "num:i(count(DmaChannelTransactionSet/*))"!][!//
      [!VAR "ChannelTcsIndex" = "num:i(0)"!][!//
      [!FOR "ChannelTcsIndex" = "num:i(0)" TO "num:i($NoOfTCS) - num:i(1)"!][!//
        [!SELECT "DmaChannelTransactionSet/*[@index=$ChannelTcsIndex]"!][!//
          [!CALL "Dma_DoubleBufferConfig", "ShadowMode"="DmaTcsShadowRegisterConfiguration","Dma_DoubleBufferControl" ="$Dma_DoubleBufferControl"!][!//
          [!IF "text:contains(node:value(DmaTcsShadowRegisterConfiguration),'LINK') = 'true'"!][!//
            [!VAR "LinkListEnable" = "'STD_ON'"!][!//
          [!ENDIF!]
        [!ENDSELECT!][!//
      [!ENDFOR!][!//
    [!ENDSELECT!][!//
  [!ENDFOR!][!//
[!ENDNOCODE!][!//
[!//
[!/* [cover parentID={64855B2E-FB75-4b7d-B34C-E5AA5CBAC0CE}]
Dma_kChConfigRoot_Core
[/cover] */!][!//
/* ***************** Configuration of the TCSes ***************** */
[!VAR "DmaChannelCoreNo" = "num:i(0)"!][!//
[!/* Lets cycle through all the DMA channels which are allocated in the configuration of DMA */!][!//
[!FOR "ChannelIndex" = "num:i(0)" TO "num:i($NoOfDmaChannels) - num:i(1)"!][!//
  [!/* Select the configuration of a particular channel */!][!//
  [!SELECT "DmaChannelConfig/*[@index=$ChannelIndex]"!][!//
    [!/* Get the ID of the channel under consideration */!][!//
    [!VAR "ChannelID" ="num:i(DmaChannelId)"!][!//
    [!VAR "DmaChannelcfg" ="substring-after(node:path(.),'DmaChannelConfig/')"!][!//
    [!VAR "User" ="DmaChannelUser"!][!//
    [!/* [cover parentID={CC0B022F-0454-4834-863D-064AE9EEF22A}]
    Dma_ConfigchannelUserData
    [/cover] */!][!//
    [!CALL "Dma_ConfigchannelUserData","DmaChUser"= "$User","Dmach"= "$DmaChannelcfg"!][!// 
    [!/* Lets synthesize the channel name which we need to consider */!][!//
    [!VAR "DmaChannelRefName" = "node:name(.)"!][!//
    [!VAR "DmaChannelRefNamePattern" = "concat('<', '__ALCH#', $ChannelID, '__', $DmaChannelRefName, '>')"!][!//
    [!//VAR "DmaChannelRefName" = "concat('DmaChannelConfig_', ',')"!][!//
    [!/* Has that channel found its way into the resoruce manager? */!][!//
    [!IF "contains($CGAllocatedResources, $DmaChannelRefNamePattern)"!][!//
      [!/* The channel is allocated in the RM. Lets synthesize the full name of the channel, by which its known in the resource manager club! */!][!//
      [!VAR "DmaModuleMapRegEx" = "concat('<CORE[0-9]', '__ALCH#', $ChannelID, '__', $DmaChannelRefName, '>')"!][!//
      [!/* Check for our channel in the list */!][!//
      [!VAR "DmaPatternSearchResult" = "text:grep(text:split($CGModuleMap,','), $DmaModuleMapRegEx )"!][!//
      [!/* Get the core number */!][!//
      [!VAR "DmaChannelCoreNo" = "substring($DmaPatternSearchResult, 7, 1)"!][!//
    [!ELSE!][!//
      [!/* Well, apparently, that channel appears to be an orphan, lets give it a parent! */!][!//
      [!VAR "DmaChannelCoreNo" = "$MasterCoreNumber"!][!//
    [!ENDIF!][!//
    [!VAR "ChannelTcsIndex" = "num:i(0)"!][!//
    [!VAR "NoOfTCS" = "num:i(count(DmaChannelTransactionSet/*))"!][!//
    [!INDENT "0"!][!//

      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going
       * beyond 32 chars because of naming convention*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going
       * beyond 32 chars because of naming convention*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going
       * beyond 32 chars because of naming convention*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going
       * beyond 32 chars because of naming convention*/
      #define DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"$DmaChannelCoreNo"!]_256
      /* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is
       * repeatedly included without include guard. This is
       * as per AUTOSAR */
      /* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of
       * MoveEngine Notification before #include memap.h
       * - Accepted deviation in AUTOSAR */
     [!/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
      * Const Section
      * [/cover]*/!]
     [!/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
      * Const Section
      * [/cover]*/!]
      #include "Dma_MemMap.h"

      /* DMA channel [!"$ChannelID"!] Transaction set control Configuration */
      static const Dma_TransactionCtrlSetType Dma_kChannel_[!"$ChannelID"!]_TcsConfigRoot[]=
      {
      [!INDENT "2"!][!//
        [!FOR "ChannelTcsIndex" = "num:i(0)" TO "num:i($NoOfTCS) - num:i(1)"!][!//
          [!SELECT "DmaChannelTransactionSet/*[@index=$ChannelTcsIndex]"!][!//
            /* Dma Channel [!"$ChannelID"!] TCS [!"$ChannelTcsIndex"!] */
            {
            [!INDENT "4"!][!//
              [!NOCODE!][!//
                [!VAR "DmaAddrIntControl" = "num:i(0)"!][!//
                [!VAR "DmaChcfgrControl" = "num:i(0)"!][!//
                [!VAR "DmaReadDataCrc" = "num:i(DmaTcsReferenceDataCrc)"!][!//
                [!VAR "DmaSourceDestAddressCrc" = "num:i(DmaTcsReferenceAddressCrc)"!][!//
                [!VAR "DmaSourceAddr" = "DmaTcsSourceAddress"!][!//
                [!VAR "DmaDestAddr" = "DmaTcsDestinationAddress"!][!//
                [!VAR "DmaDoubleBufAddr" = "DmaTcsDoubleBuffer"!][!//
                [!VAR "DmaControlAndStatus" = "num:i(0)"!][!//
                [!VAR "DmaPatternModeVar" = "num:i(0)"!][!//               
                [!IF "(./DmaPatternMode != 'Pattern_Detection_Disabled') or (./DmaTcsShadowRegisterConfiguration != 'DMA_CONDITIONAL_LINKED_LIST')"!][!//
                  [!VAR "DmaPatternModeVar" = "DmaPatternMode"!][!//
                [!ENDIF!][!//
                
                [!CALL "Dma_AdicrConfig", "SrcModFactor"="DmaTcsSourceAddressModificationFactor", "SrcCirclBufferLen"="DmaTcsCircularBufferSourceLength", "IncrementSrcAddr"="DmaTcsSourceAddressMovement", "DestModFactor"="DmaTcsDestinationAddressModificationFactor", "DestCirclBufferLen"="DmaTcsCircularBufferDestinationLength", "IncrementDestAddr"="DmaTcsDestinationAddressMovement", "IntEnable"="DmaTcsDataTransferInterrupt" ,"IntCtrl"="DmaTcsInterruptDataTransfer", "TcountThreshold"="DmaTcsInterruptDataTransferThreshold", "WrpSrc"="DmaTcsInterruptSourceAddressWrap", "WrpDest"="DmaTcsInterruptDestinationAddressWrap","ShadowCtrl"="DmaTcsShadowRegisterConfiguration", "SrcCirclBuffEn"="DmaTcsCircularBufferSourceEnable", "DestCirclBuffEn"="DmaTcsCircularBufferDestinationEnable", "TimeStampEn"="DmaTcsAppendTimeStamp", "DmaAddrIntControl"="$DmaAddrIntControl"!][!//
                               
                [!CALL "Dma_ChcfgrConfig", "DataWidth"="DmaTcsMoveLength","PatternMode"="$DmaPatternModeVar","BlockMode"="DmaTcsTransferLength","TransactionLenght"="DmaTcsTransactionLength", "DmaTransferReqState"="DmaTcsTriggerFrequency","HwMode"="DmaTcsHardwareTrigger", "PeripheralSelect"="DmaTcsDaisyChaining","Priority"="0","CrcSwapOrder"="DmaTcsSwapDataCRCByteOrder","DmaChcfgrControl"="$DmaChcfgrControl"!][!//
                [!VAR "DmaShadowAddress" = "'NULL_PTR'"!]
                [!IF "text:contains(node:value(DmaTcsShadowRegisterConfiguration),'LINK') = 'true'"!][!//
                    [!CALL "Dma_CG_GetTcsConfIndex", "LocalTcsId" = "num:i(DmaNextTcsIndex)", "TcsConfIndexLocation" = "num:i(0)"!][!//
                    [!VAR "DmaShadowAddress" = "concat('&Dma_kChannel_',$ChannelID,'_TcsConfigRoot[',$TcsConfIndexLocation,']')"!][!//
                [!ELSEIF "text:contains(node:value(DmaTcsShadowRegisterConfiguration),'DOUBLE') = 'true'"!][!//
                    [!VAR "DmaShadowAddress" = "$DmaDoubleBufAddr"!][!//
                [!ENDIF!][!//   
                [!IF "text:contains(node:value(DmaTcsShadowRegisterConfiguration),'CONDITIONAL') = 'true'"!][!// 
                  [!VAR "ConditionalLlNextNode" = "DmaCLLNextIndex"!]
                  [!VAR "DmaShadowAddress1" = "concat('&Dma_kChannel_',$ChannelID,'_TcsConfigRoot[',$ConditionalLlNextNode,']')"!][!// 
                  // 
                [!ENDIF!][!//
              [!ENDNOCODE!][!//
              [!IF "$LinkListEnable = 'STD_ON'"!][!//
                /* Configuration for DMA register DMA_RDCRCRz */
                [!"(num:inttohex($DmaReadDataCrc,8))"!]U,
                /* Configuration for DMA register DMA_SDCRCRz */
                [!IF "text:contains(node:value(DmaTcsShadowRegisterConfiguration),'CONDITIONAL') = 'true'"!][!//
              /* MISRA2012_RULE_11_6_JUSTIFICATION: Memory address is generated as a numerical value 
                 configuration and in code, it is accessed as a pointer to the RAM address. Hence an 
                 explicit typecast from integer to uint32 based pointer. */
              /* MISRA2012_RULE_11_4_JUSTIFICATION: Memory address is generated as a numerical value 
                 configuration and in code, it is accessed as a pointer to the RAM address. Hence an 
                 explicit typecast from integer to uint32 based pointer. */
                  (uint32)[!"$DmaShadowAddress1"!],
                [!ELSE!][!//
                  [!"(num:inttohex($DmaSourceDestAddressCrc,8))"!]U,
                [!ENDIF!][!//  
              [!ENDIF!][!//
              /* Configuration for DMA source address register DMA_SADRz */
              /* MISRA2012_RULE_11_6_JUSTIFICATION: Memory address is generated as a numerical value 
                 configuration and in code, it is accessed as a pointer to the RAM address. Hence an 
                 explicit typecast from integer to uint32 based pointer. */
              /* MISRA2012_RULE_11_4_JUSTIFICATION: Memory address is generated as a numerical value 
                 configuration and in code, it is accessed as a pointer to the RAM address. Hence an 
                 explicit typecast from integer to uint32 based pointer. */
              /* MISRA2012_RULE_11_3_JUSTIFICATION: Memory address is generated as a numerical value 
                 configuration and in code, it is accessed as a pointer to the RAM address. Hence an 
                 explicit typecast from integer to uint32 based pointer. */                  
              (uint32 *)[!"$DmaSourceAddr"!],
              /* Configuration for DMA destination address register DMA_DADRz */
              /* MISRA2012_RULE_11_6_JUSTIFICATION: Memory address is generated as a numerical value 
                 configuration and in code, it is accessed as a pointer to the RAM address. Hence an 
                 explicit typecast from integer to uint32 based pointer. */
              /* MISRA2012_RULE_11_4_JUSTIFICATION: Memory address is generated as a numerical value 
                 configuration and in code, it is accessed as a pointer to the RAM address. Hence an 
                 explicit typecast from integer to uint32 based pointer. */
              /* MISRA2012_RULE_11_3_JUSTIFICATION: Memory address is generated as a numerical value 
                 configuration and in code, it is accessed as a pointer to the RAM address. Hence an 
                 explicit typecast from integer to uint32 based pointer. */ 
              (uint32 *)[!"$DmaDestAddr"!],
              /* Configuration for DMA Channel Address and Interrupt Control
               * Register DMA_ADICRz */
              [!"(num:inttohex($DmaAddrIntControl,8))"!]U,
              /* Configuration for DMA Channel Configuration Register DMA_CHCFGRz */
              [!VAR "PRR1chcfg" = "num:i(0)"!][!//              
              [!SELECT "../../../../DmaPatternConfig"!][!// 
                [!IF "node:exists(./DmaChannelForPattern1)"!][!//           
                  [!VAR "PRR1Path" = "./DmaChannelForPattern1"!][!//
                  [!IF "$PRR1Path != ''"!][!//
                    [!VAR "PRR1ChannelID" = "node:ref($PRR1Path)/DmaChannelId"!][!//             
                    [!VAR "PRR1TcsPatternMode" = "node:ref($PRR1Path)/DmaChannelTransactionSet/*[@index=$ChannelTcsIndex]/DmaPatternMode"!][!//  
                    [!VAR "PRR1TcsShadowRegCfg" = "node:ref($PRR1Path)/DmaChannelTransactionSet/*[@index=$ChannelTcsIndex]/DmaTcsShadowRegisterConfiguration"!][!//                    
                    [!IF "($ChannelID = $PRR1ChannelID) and (($PRR1TcsPatternMode = 'Pattern_Detection_Disabled') or ($PRR1TcsShadowRegCfg = 'DMA_CONDITIONAL_LINKED_LIST'))"!][!//         
                      [!VAR "PRR1chcfg" = "bit:or(num:i($DmaChcfgrControl), num:i(67108864))"!][!//
                      [!"(num:inttohex($PRR1chcfg,8))"!]U,
                    [!ELSE!][!//
                      [!"(num:inttohex($DmaChcfgrControl,8))"!]U,
                    [!ENDIF!][!//
                  [!ELSE!][!//
                      [!"(num:inttohex($DmaChcfgrControl,8))"!]U,
                  [!ENDIF!][!//
                [!ELSE!][!//
                  [!/* if DmaChannelForPattern0 exists or does not exist */!][!//
                  [!"(num:inttohex($DmaChcfgrControl,8))"!]U,
                [!ENDIF!][!//               
              [!ENDSELECT!][!//             
              /* Configuration for DMA Channel Shadow Address Register DMA_SHADRz */
              /* MISRA2012_RULE_11_6_JUSTIFICATION: Memory address is generated as a numerical value 
                 configuration and in code, it is accessed as a pointer to the RAM address. Hence an 
                 explicit typecast from integer to uint32 based pointer. */
              /* MISRA2012_RULE_11_4_JUSTIFICATION: Memory address is generated as a numerical value 
                 configuration and in code, it is accessed as a pointer to the RAM address. Hence an 
                 explicit typecast from integer to uint32 based pointer. */
              /* MISRA2012_RULE_11_3_JUSTIFICATION: Memory address is generated as a numerical value 
                 configuration and in code, it is accessed as a pointer to the RAM address. Hence an 
                 explicit typecast from integer to uint32 based pointer. */ 
              [!IF "text:contains(node:value(DmaTcsShadowRegisterConfiguration),'LINK') = 'true'"!][!//
                (const struct Dma_TransactionCtrlSetType*)[!"$DmaShadowAddress"!],
              [!ELSEIF "text:contains(node:value(DmaTcsShadowRegisterConfiguration),'DOUBLE') = 'true'"!][!//
                (const struct Dma_TransactionCtrlSetType*)[!"$DmaDoubleBufAddr"!],
              [!ELSEIF "$LinkListEnable = 'STD_ON'"!][!//
                (const struct Dma_TransactionCtrlSetType*) 0x00000000U,
              [!ELSEIF "$Dma_DoubleBufferControl = 'STD_ON'"!][!//
                (const struct Dma_TransactionCtrlSetType*) 0x00000000U,
              [!ENDIF!][!//
              [!IF "$LinkListEnable = 'STD_ON'"!][!//
                [!IF "DmaTcsAutoStartEnable = 'true'"!]
                    [!VAR "DmaControlAndStatus" = "bit:or($DmaControlAndStatus, bit:shl(1,31))"!][!//
                [!ENDIF!]
                /* Configuration for DMA Channel Control and Status Register DMA_CHCSRz */
                [!"(num:inttohex($DmaControlAndStatus,8))"!]U
              [!ENDIF!][!//
            [!ENDINDENT!][!//
            }[!IF "$ChannelTcsIndex != $NoOfTCS - num:i(1)"!],
            [!ENDIF!][!//
            [!IF "num:i(DmaNextTcsIndex)  >= $NoOfTCS"!][!//
              [!IF "text:contains(node:value(DmaTcsShadowRegisterConfiguration),'LINK') = 'true'"!][!//
                [!ERROR!][!//
                  Config Error: Channel [!"$ChannelIndex"!], TCS [!"$ChannelTcsIndex"!], DmaNextTcsIndex([!"DmaNextTcsIndex"!] is pointing to non-existing node [!//
                [!ENDERROR!][!//
              [!ENDIF!][!//
            [!ENDIF!][!//
          [!ENDSELECT!][!//
        [!ENDFOR!][!//
      [!ENDINDENT!][!//
      [!CR!]};
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
       * because of naming convention*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
       * because of naming convention*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
       * because of naming convention*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
       * because of naming convention*/
      #define DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"$DmaChannelCoreNo"!]_256
      /* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is repeatedly included
       * without include guard. This is as per AUTOSAR */
       /* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of MoveEngine Notification
       * before #include memap.h - Accepted deviation in AUTOSAR */
      #include "Dma_MemMap.h"

    [!ENDINDENT!][!//
  [!ENDSELECT!][!//
[!ENDFOR!][!//
/* ************************************************************** */

[!NOCODE!]
  [!/* Get the count of the unassigned channels */!][!//
  [!VAR "NoOfUnassignedChannels" = "num:i(0)"!][!//
  [!CALL "Dma_CG_GetNoOfUnallocatedChannels", "NoOfUnassignedChannels" = "num:i(0)"!][!//
[!ENDNOCODE!]
[!/* [cover parentID={416F272A-A694-48be-ABDE-72991E89C5B4}]
Dma_kChConfigRoot_Core
[/cover] */!][!//
[!INDENT "0"!][!//
  /* *************** Channel root configuration list ************** */
  [!/* The channel position index for each core specific structure */!]
  [!VAR "ChannelIndexPositionPerCore" = "''"!][!//
  [!FOR "ChannelCoreIndex" = "0" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
    [!/* The index position counter during the generation */!]
    [!VAR "ChannelIndexPositionCounter" = "num:i(0)"!][!//
    [!VAR "ChannelRootStructureNeeded" = "'NO'"!][!//
    [!VAR "ChannelCoreName" = "concat('CORE',$ChannelCoreIndex)"!][!//
    [!/* Check if the core is in the used list */!][!//
    [!IF "contains(text:split($CGCoreUsed), $ChannelCoreName)"!][!//
      [!VAR "ChannelRootStructureNeeded" = "'YES'"!][!//
    [!ELSEIF "$ChannelCoreIndex = $MasterCoreNumber and num:i($NoOfUnassignedChannels) > num:i(0)"!][!//
      [!VAR "ChannelRootStructureNeeded" = "'YES'"!][!//
    [!ENDIF!][!//
    [!IF "$ChannelRootStructureNeeded = 'YES'"!][!//
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
       * because of naming convention*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
       * because of naming convention*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
       * because of naming convention*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
       * because of naming convention*/
      #define DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"$ChannelCoreIndex"!]_UNSPECIFIED
      /* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is repeatedly included
       * without include guard. This is as per AUTOSAR */
      /* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of MoveEngine Notification
       * before #include memap.h - Accepted deviation in AUTOSAR */
      #include "Dma_MemMap.h"
      /* Configuration of all the DMA channels */
      static const Dma_ChConfigType Dma_kChConfigRoot_Core[!"$ChannelCoreIndex"!][]=
      {
      [!INDENT "2"!][!//
        [!VAR "ChannelIndex" = "num:i(0)"!][!//
        [!FOR "ChannelIndex" = "0" TO "num:i($NoOfDmaChannels) - num:i(1)"!][!//
          [!SELECT "DmaChannelConfig/*[@index=$ChannelIndex]"!][!//
            [!CALL "Dma_CG_GetTheCoreAssignmentOfChannel", "LocalChannelID" = "num:i(DmaChannelId)", "CoreOfChannel" = "num:i(0)"!][!//
            [!/* Is the channel under consideration belong to the core, for which we are 'iterating'? */!][!//
            [!IF "$CoreOfChannel = $ChannelCoreIndex"!][!//
              [!VAR "GenerationNeeded" = "'YES'"!][!//
            [!ELSEIF "$CoreOfChannel = 'NOCORE' and $ChannelCoreIndex = $MasterCoreNumber"!][!//
              [!VAR "GenerationNeeded" = "'YES'"!][!//
            [!ELSE!][!//
              [!VAR "GenerationNeeded" = "'NO'"!][!//
            [!ENDIF!][!//
            [!IF "$GenerationNeeded = 'YES'"!][!//
              {
              [!VAR "ChannelIndexPositionPerCore" = "concat($ChannelIndexPositionPerCore, 'Ch', num:i(DmaChannelId) + num:i(1000), '_Pos', $ChannelIndexPositionCounter + num:i(1000), '_Core', $ChannelCoreIndex, ',')"!][!//
              [!VAR "ChannelIndexPositionCounter" = "$ChannelIndexPositionCounter + num:i(1)"!][!//
              [!INDENT "4"!][!//
                [!VAR "DmaTsrReg" = "num:i(0)"!][!//
                [!VAR "DmaChannelNotification" = "DmaChannelNotification"!][!//
                [!VAR "RPNotification" = "DmaErrorNotification"!][!//
                &Dma_kChannel_[!"DmaChannelId"!]_TcsConfigRoot[0U], /* TCS config Root */
                [!"$DmaChannelNotification"!], /* Channel Notification */
                [!CALL "Dma_TsrConfig", "DmaTRLConf" = "DmaTcsInterruptTransactionLoss", "DmaTsrReg"="$DmaTsrReg""!][!//
                [!"(num:inttohex($DmaTsrReg,8))"!]U, /* TSR configuration */
                (uint8)[!"DmaChannelId"!]U, /* Dma Channel ID */
                (uint8)[!"num:inttohex(DmaChannelAssignedPartition)"!]U, /* Channel Assigned partition */
                [!VAR "CurrentPartition" = "num:i(DmaChannelAssignedPartition)"!][!//               
                [!"$RPNotification"!] /* Error Notification */
              [!ENDINDENT!][!//
              }[!IF "$ChannelIndex != $NoOfDmaChannels -1"!],
                [!ENDIF!][!//CR!]
            [!ENDIF!][!//
          [!ENDSELECT!][!//
        [!ENDFOR!][!//
      [!ENDINDENT!][!//
      };
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
       * because of naming convention*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
       * because of naming convention*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
       * because of naming convention*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
       * because of naming convention*/
      #define DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"$ChannelCoreIndex"!]_UNSPECIFIED
      /* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is repeatedly included
       * without include guard. This is as per AUTOSAR */
      /* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of MoveEngine Notification
       * before #include memap.h - Accepted deviation in AUTOSAR */
      #include "Dma_MemMap.h"
    [!ENDIF!][!//
  [!ENDFOR!][!//
  /* *************************************************************** */
[!ENDINDENT!][!//
[!/* [cover parentID={CE1183AE-EDA0-404c-B75F-70B07380424E}]
Dma_ChConfigRootCoreX
[/cover] */!][!//
[!INDENT "0"!][!//
  /* ************* Configuration structure of each core ************* */
  [!FOR "ChannelCoreIndex" = "0" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
    [!VAR "CoreRootStructureNeeded" = "'NO'"!][!//
    [!VAR "ChannelCoreName" = "concat('CORE',$ChannelCoreIndex)"!][!//
    [!/* Check if the core is in the used list */!][!//
    [!IF "contains(text:split($CGCoreUsed), $ChannelCoreName)"!][!//
      [!VAR "CoreRootStructureNeeded" = "'YES'"!][!//
    [!ELSEIF "$ChannelCoreIndex = $MasterCoreNumber and num:i($NoOfUnassignedChannels) > num:i(0)"!][!//
      [!VAR "CoreRootStructureNeeded" = "'YES'"!][!//
    [!ENDIF!][!//
    [!IF "$CoreRootStructureNeeded = 'YES'"!][!//
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
       * because of naming convention*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
       * because of naming convention*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
       * because of naming convention*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
       * because of naming convention*/
      #define DMA_START_SEC_CONFIG_DATA_ASIL_B_CORE[!"$ChannelCoreIndex"!]_UNSPECIFIED
      /* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is repeatedly included
       * without include guard. This is as per AUTOSAR */
      /* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of MoveEngine Notification
       * before #include memap.h - Accepted deviation in AUTOSAR */
      #include "Dma_MemMap.h"
      static const Dma_CoreSpecificChConfigType Dma_ChConfigRootCore[!"$ChannelCoreIndex"!]=
      {
      [!INDENT "2"!][!//
        /* Core specific config pointer */
        &Dma_kChConfigRoot_Core[!"$ChannelCoreIndex"!][0],
        [!CALL "Dma_CG_GetResourceNumbers", "LocalCoreId"="$ChannelCoreIndex", "AllocationTotalCount" = "''"!][!//
        /* Total number of DMA channels in core [!"$ChannelCoreIndex"!] */
        [!/* Assigned channels = [!"num:i($AllocationTotalCount)"!], Unassigned channels = [!"num:i($NoOfUnassignedChannels)"!] */!][!//
        [!IF "$ChannelCoreIndex = $MasterCoreNumber"!]
            [!"num:i(num:i($AllocationTotalCount) + num:i($NoOfUnassignedChannels))"!]
        [!ELSE!]
            [!"num:i($AllocationTotalCount)"!]
        [!ENDIF!]
      [!ENDINDENT!][!//
      };
      /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
       * because of naming convention*/
      /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
       * because of naming convention*/
      /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
       * because of naming convention*/
      /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
       * because of naming convention*/
      #define DMA_STOP_SEC_CONFIG_DATA_ASIL_B_CORE[!"$ChannelCoreIndex"!]_UNSPECIFIED
      /* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is repeatedly included
       * without include guard. This is as per AUTOSAR */
      /* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of MoveEngine Notification
       * before #include memap.h - Accepted deviation in AUTOSAR */
      #include "Dma_MemMap.h"
    [!ENDIF!][!//
  [!ENDFOR!][!//
/* **************************************************************** */
[!ENDINDENT!][!//

[!/* [cover parentID={5D84DC08-6409-4201-903B-A8C9F4EEC524}]
Dma_Config
[/cover] */!][!//
[!INDENT "0"!][!//
  /* ************* Base Configuration Structure of DMA ************* */
  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   * because of naming convention*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   * because of naming convention*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   * because of naming convention*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   * because of naming convention*/  
  #define DMA_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  /* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of MoveEngine Notification
   * before #include memap.h - Accepted deviation in AUTOSAR */
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is repeatedly included
   * without include guard. This is as per AUTOSAR */
  #include "Dma_MemMap.h"
  [!IF "$VariantsConfigured = num:i(1)"!][!//
  const Dma_ConfigType Dma_Config_[!"$PredefinedVarName"!] =
  [!ELSE!][!//
  const Dma_ConfigType Dma_Config=
  [!ENDIF!][!//
  {
  [!INDENT "2"!][!//
  [!NOCODE!][!//
    [!SELECT "DmaMoveEngineConfig"!][!//
      [!VAR "MENotification" = "as:modconf('Dma')[1]/DmaResourcePartition/*[1]/DmaErrorNotification"!][!//
      [!VAR "Dma_ErrEnControl"="num:i(0)"!][!//
      [!CALL "Dma_ErrEnConfig", "SrcErr"="DmaMESourceErrorInterrupt","DstErr"="DmaMEDestinationErrorInterrupt", "LLErr"="DmaMELinkedListErrorInterrupt", "Dma_ErrEnControl" ="$Dma_ErrEnControl"!][!//     
    [!ENDSELECT!][!// 
    [!IF "(num:i(count(./DmaChannelConfig/*[DmaChannelTransactionSet/*[DmaPatternMode != 'Pattern_Detection_Disabled']]))>0)or(num:i(count(./DmaChannelConfig/*[DmaChannelTransactionSet/*[DmaTcsShadowRegisterConfiguration = 'DMA_CONDITIONAL_LINKED_LIST']]))>0)"!][!//
      [!SELECT "DmaPatternConfig"!][!//
        [!VAR "Pattern0Ch" = "num:i(255)"!][!//
        [!VAR "Pattern1Ch" = "num:i(255)"!][!// 
        
        [!IF "node:exists(./DmaChannelForPattern0)"!][!//       
          [!IF "./DmaChannelForPattern0 != ''"!]
            [!VAR "Pattern0ChPath" = "./DmaChannelForPattern0"!][!//      
            [!SELECT "node:ref($Pattern0ChPath)/DmaChannelTransactionSet/*"!][!//        
              [!IF "./DmaTcsShadowRegisterConfiguration != 'DMA_CONDITIONAL_LINKED_LIST'"!][!//          
                [!VAR "Pattern0Mode" = "./DmaPatternMode"!][!//         
                [!IF "($Pattern0Mode = 'Pattern_Mode_5') or ($Pattern0Mode ='Pattern_Mode_6') or ($Pattern0Mode='Pattern_Mode_7')"!][!//
                  [!ERROR!][!//
                    ERROR: DmaChannelForPattern0 should be configured for PRR0 only.
                  [!ENDERROR!][!//  
                [!ENDIF!][!//              
              [!ENDIF!][!//           
            [!ENDSELECT!][!// 
            [!VAR "Pattern0Ch" = "num:i(node:ref($Pattern0ChPath)/DmaChannelId)"!][!//             
          [!ENDIF!][!// 
        [!ENDIF!][!// 

        [!IF "node:exists(./DmaChannelForPattern1)"!][!//       
          [!IF "./DmaChannelForPattern1 != ''"!][!//    
            [!VAR "Pattern1ChPath" = "./DmaChannelForPattern1"!][!//
            [!SELECT "node:ref($Pattern1ChPath)/DmaChannelTransactionSet/*"!][!//       
              [!IF "./DmaTcsShadowRegisterConfiguration != 'DMA_CONDITIONAL_LINKED_LIST'"!][!//           
                [!VAR "Pattern1Mode" = "./DmaPatternMode"!][!//     
                [!IF "($Pattern1Mode = 'Pattern_Mode_1') or ($Pattern1Mode ='Pattern_Mode_2') or ($Pattern1Mode='Pattern_Mode_3')"!][!//
                  [!ERROR!][!//
                    ERROR: DmaChannelForPattern1 should be configured for PRR1 only.
                  [!ENDERROR!][!//                    
                [!ENDIF!][!//            
              [!ENDIF!][!//          
            [!ENDSELECT!][!//
            [!VAR "Pattern1Ch" = "num:i(node:ref($Pattern1ChPath)/DmaChannelId)"!][!//             
          [!ENDIF!][!//       
        [!ENDIF!][!//
        
        [!VAR "Pattern0" = "./DmaPattern0"!][!//
        [!VAR "Pattern1" = "./DmaPattern1"!][!//
      [!ENDSELECT!][!//  

    [!//[!Resource allocation check for pattern mode!][!//
    [!IF "((not(node:exists(./DmaPatternConfig/DmaChannelForPattern0))) or (./DmaPatternConfig/DmaChannelForPattern0 = '') )and((not(node:exists(./DmaPatternConfig/DmaChannelForPattern1))) or (./DmaPatternConfig/DmaChannelForPattern1 = ''))"!][!//  
      [!VAR "vaildModecfg"= "num:i(0)"!][!//        
      [!SELECT "DmaChannelConfig/*/DmaChannelTransactionSet/*"!][!//            
        [!IF "(./DmaPatternMode != 'Pattern_Detection_Disabled')or(./DmaTcsShadowRegisterConfiguration = 'DMA_CONDITIONAL_LINKED_LIST')"!][!//
          [!VAR "vaildModecfg"= "num:i($vaildModecfg + 1)"!][!//         
        [!ENDIF!][!//                  
      [!ENDSELECT!][!//
      [!IF "$vaildModecfg > num:i(0)"!][!//
        [!ERROR!][!//
          ERROR: No channel is reserved for 'Pattern Mode' or 'CLL'. Please release the unused resourse.
        [!ENDERROR!][!//    
      [!ENDIF!][!//
      
    [!ELSEIF "((node:exists(./DmaPatternConfig/DmaChannelForPattern0)) or (./DmaPatternConfig/DmaChannelForPattern0 != '') )and((not(node:exists(./DmaPatternConfig/DmaChannelForPattern1))) or (./DmaPatternConfig/DmaChannelForPattern1 = ''))"!][!//  
      [!VAR "vaildModecfg"= "num:i(0)"!][!//
      [!SELECT "DmaChannelConfig/*"!][!//
        [!IF "(substring-after($Pattern0ChPath,'/Dma/Dma/') != node:name(.))"!][!//      
          [!IF "(./DmaChannelTransactionSet/*/DmaPatternMode != 'Pattern_Detection_Disabled')or(./DmaChannelTransactionSet/*/DmaTcsShadowRegisterConfiguration = 'DMA_CONDITIONAL_LINKED_LIST')"!][!//"!][!//
            [!VAR "vaildModecfg"= "num:i($vaildModecfg + 1)"!][!//         
          [!ENDIF!][!//
        [!ENDIF!][!//          
      [!ENDSELECT!][!//
      [!IF "$vaildModecfg > num:i(0)"!][!//
        [!ERROR!][!//
          ERROR: Only one channel is used PRR0, but more than one configuration is done for 'Pattern Mode' or 'CLL'. Please release the unused resourse.
        [!ENDERROR!][!//    
      [!ENDIF!][!//
      
      [!ELSEIF "((node:exists(./DmaPatternConfig/DmaChannelForPattern1)) or (./DmaPatternConfig/DmaChannelForPattern1 != '') )and((not(node:exists(./DmaPatternConfig/DmaChannelForPattern0))) or (./DmaPatternConfig/DmaChannelForPattern0 = ''))"!][!//  
      [!VAR "vaildModecfg"= "num:i(0)"!][!//
      [!SELECT "DmaChannelConfig/*"!][!//
        [!IF "(substring-after($Pattern1ChPath,'/Dma/Dma/') != node:name(.))"!][!//      
          [!IF "(./DmaChannelTransactionSet/*/DmaPatternMode != 'Pattern_Detection_Disabled')or(./DmaChannelTransactionSet/*/DmaTcsShadowRegisterConfiguration = 'DMA_CONDITIONAL_LINKED_LIST')"!][!//"!][!//
            [!VAR "vaildModecfg"= "num:i($vaildModecfg + 1)"!][!//         
          [!ENDIF!][!//
        [!ENDIF!][!//          
      [!ENDSELECT!][!//
      [!IF "$vaildModecfg > num:i(0)"!][!//
        [!ERROR!][!//
          ERROR: Only one channel is used PRR1, but more than one configuration is done for 'Pattern Mode' or 'CLL'. Please release the unused resourse.
        [!ENDERROR!][!//    
      [!ENDIF!][!//
    
      [!ELSEIF "((node:exists(./DmaPatternConfig/DmaChannelForPattern0)) and (node:exists(./DmaPatternConfig/DmaChannelForPattern1))) and ((./DmaPatternConfig/DmaChannelForPattern0 != '') and (./DmaPatternConfig/DmaChannelForPattern1 != ''))"!][!//  
        [!VAR "vaildModecfg"= "num:i(0)"!][!//         
        [!SELECT "DmaChannelConfig/*"!][!//  
          [!IF "(substring-after($Pattern0ChPath,'/Dma/Dma/') != node:name(.))and(substring-after($Pattern1ChPath,'/Dma/Dma/') != node:name(.))"!][!//         
            [!IF "(./DmaChannelTransactionSet/*/DmaPatternMode != 'Pattern_Detection_Disabled')or(./DmaChannelTransactionSet/*/DmaTcsShadowRegisterConfiguration = 'DMA_CONDITIONAL_LINKED_LIST')"!][!//"!][!//
              [!VAR "vaildModecfg"= "num:i($vaildModecfg + 1)"!][!//         
            [!ENDIF!][!// 
          [!ENDIF!][!//           
        [!ENDSELECT!][!//      
        [!IF "$vaildModecfg > num:i(0)"!][!//
          [!ERROR!][!//
            ERROR: Two channels are used, but more than two configuration is done for 'Pattern Mode' or 'CLL' . Please release the unused resourse.
          [!ENDERROR!][!//    
        [!ENDIF!][!//      
      [!ENDIF!][!//    
    [!ENDIF!][!//
      
    [!ENDNOCODE!][!//
    {
    [!INDENT "4"!][!//
      [!FOR "ChannelCoreIndex" = "0" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable')) -1"!][!//
         /* Channel Configuration root for Core [!"$ChannelCoreIndex"!]*/
         [!CALL "Dma_CG_GetResourceNumbers", "LocalCoreId"="$ChannelCoreIndex", "AllocationTotalCount" = "''"!][!//
         /* This is the number of resources:[!"$AllocationTotalCount"!] */
         [!IF "$AllocationTotalCount > 0"!][!//
            &Dma_ChConfigRootCore[!"$ChannelCoreIndex"!],
         [!ELSE!][!//
          [!IF "$ChannelCoreIndex = $MasterCoreNumber and $NoOfUnassignedChannels > 0"!][!//
            &Dma_ChConfigRootCore[!"$ChannelCoreIndex"!],
          [!ELSE!][!//
            NULL_PTR,
          [!ENDIF!][!//
         [!ENDIF!][!//
      [!ENDFOR!][!//
    [!ENDINDENT!][!//
    },
    /* MoveEngine Error config for ME0 and ME1 */
    {[!//
    [!WS"0"!][!"text:toupper(num:inttohex($Dma_ErrEnControl,8))"!]U,[!//
    [!WS"0"!][!"text:toupper(num:inttohex($Dma_ErrEnControl,8))"!]U[!//
    [!WS"0"!]}, 
    
    [!IF "(num:i(count(./DmaChannelConfig/*[DmaChannelTransactionSet/*[DmaPatternMode != 'Pattern_Detection_Disabled']]))>0)or(num:i(count(./DmaChannelConfig/*[DmaChannelTransactionSet/*[DmaTcsShadowRegisterConfiguration = 'DMA_CONDITIONAL_LINKED_LIST']]))>0)"!][!//    
      /* pattern matching register value PRR0 and PRR1 */
      { [!"$Pattern0"!] , [!"$Pattern1"!] } ,
      
      /* Dma ChannelId for pattern0 and pattern1 */
      {[!"$Pattern0Ch"!] , [!"$Pattern1Ch"!]},[!//
    [!ENDIF!][!//
    
    /* Access partition configuration */
    {[!CR!]
    [!INDENT "4"!][!//
      [!VAR "NoOfDmaResourcePartitions" = "num:i(count(DmaResourcePartition/*))"!]
      [!VAR "PartitionIndex" = "num:i(0)"!][!//
      /* Bus master configuration */
      {[!//
      [!FOR "PartitionIndex" = "0" TO "num:i($NoOfDmaResourcePartitions) -1"!][!//
        [!SELECT "DmaResourcePartition/*[@index=$PartitionIndex]"!][!//
          [!VAR "BusMaster"="DmaPermittedBusMaster"!][!//
          [!WS"0"!][!"text:toupper(num:inttohex($BusMaster,8))"!]U[!//
          [!WS"0"!][!IF "$PartitionIndex != $NoOfDmaResourcePartitions -1"!],[!//
          [!ENDIF!][!//
        [!ENDSELECT!][!//
      [!ENDFOR!][!//
      [!WS"0"!]},
      /* Resource partition configuration */
      {[!//
      [!FOR "PartitionIndex" = "0" TO "num:i($NoOfDmaResourcePartitions) -1"!][!//
        [!SELECT "DmaResourcePartition/*[@index=$PartitionIndex]"!][!//
          [!VAR "Dma_ResourcePartitionControl"="num:i(0)"!][!//
          [!CALL "Dma_ResourcePartitionConfig", "BusMode"="DmaResourcePartitionBusMode","Dma_ResourcePartitionControl" ="$Dma_ResourcePartitionControl"!][!//
          [!WS"0"!][!"text:toupper(num:inttohex($Dma_ResourcePartitionControl,2))"!]U[!//
          [!WS"0"!][!IF "$PartitionIndex != $NoOfDmaResourcePartitions -1"!],[!//
          [!ENDIF!][!//
        [!ENDSELECT!][!//
      [!ENDFOR!][!//
      [!WS"0"!]}
    [!ENDINDENT!][!//
    },
    /* { Channel Position Index, Channel Core Map } - The mapping data of channels */
    [!VAR "ChannelIndex" = "num:i(0)"!][!//
    {
    [!INDENT "4"!][!//
      [!FOR "ChannelIndex" = "num:i(0)" TO "$DmaMaxChannels -1"!][!//
        {[!//
        [!VAR "ChannelMapRefName" = "concat('Ch', num:i($ChannelIndex) + 1000)"!][!//
        [!IF "contains($ChannelIndexPositionPerCore, $ChannelMapRefName)"!][!//
          [!VAR "ChannelMapRegEx" = "concat('Ch', num:i($ChannelIndex) + 1000, '_Pos1[0-9][0-9][0-9]', '_Core[0-6]')"!][!//
          [!VAR "ChannelMapSearchResult" = "text:grep(text:split($ChannelIndexPositionPerCore,','), $ChannelMapRegEx )"!][!//
          [!VAR "ChannelMapPos" = "substring($ChannelMapSearchResult, 13, 3)"!][!//
          [!VAR "ChannelMapCore" = "substring($ChannelMapSearchResult, 21, 1)"!][!//
          [!"num:i($ChannelMapPos)"!], [!"num:i($ChannelMapCore)"!] [!//
        [!ELSE!][!//
        255, 255 [!//
        [!ENDIF!][!//
        }, /* Channel [!"$ChannelIndex"!] */
      [!ENDFOR!][!//
    [!ENDINDENT!][!//
    },
    [!INDENT "2"!][!//
      [!VAR "NoOfDmaChannelConfigs" = "num:i(count(DmaChannelConfig/*))"!][!//
      [!VAR "ChannelIndex" = "num:i(0)"!][!//
      [!VAR "ChannelNumber" = "num:i(0)"!][!//
      [!VAR "TrlStatusWord1" = "num:i(0)"!][!//
      [!VAR "TrlStatusWord2" = "num:i(0)"!][!//
      [!VAR "TrlStatusWord3" = "num:i(0)"!][!//
      [!VAR "TrlStatusWord4" = "num:i(0)"!][!//
      [!FOR "ChannelIndex" = "num:i(0)" TO "num:i($NoOfDmaChannelConfigs) -1"!][!//
        [!IF "node:exists(./DmaChannelConfig/*[@index=$ChannelIndex])"!][!//
          [!SELECT "DmaChannelConfig/*[@index=$ChannelIndex]"!][!//
            [!IF "node:exists(DmaTcsInterruptTransactionLoss)"!][!//
              [!IF "DmaTcsInterruptTransactionLoss = 'true'"!][!//
                [!IF "num:i(DmaChannelId) < num:i(32)"!][!//
                  [!VAR "TrlStatusWord1" = "bit:or($TrlStatusWord1,bit:shl(1,num:i(DmaChannelId)))"!][!//
                [!ELSEIF "num:i(DmaChannelId) >= num:i(32) and num:i(DmaChannelId) < num:i(64)"!][!//
                  [!VAR "ChannelNumber" = "num:i(DmaChannelId) - 32"!][!//
                  [!VAR "TrlStatusWord2" = "bit:or($TrlStatusWord2,bit:shl(1,num:i($ChannelNumber)))"!][!//
                [!ELSEIF "num:i(DmaChannelId) >= num:i(64) and num:i(DmaChannelId) < num:i(96)"!][!//
                  [!VAR "ChannelNumber" = "num:i(DmaChannelId) - num:i(64)"!][!//
                  [!VAR "TrlStatusWord3" = "bit:or($TrlStatusWord3,bit:shl(1,$ChannelNumber))"!][!//
                [!ELSEIF "num:i(DmaChannelId) >= num:i(96) and num:i(DmaChannelId) < num:i(128)"!][!//
                  [!VAR "ChannelNumber" = "num:i(DmaChannelId) - num:i(96)"!][!//
                  [!VAR "TrlStatusWord4" = "bit:or($TrlStatusWord4,bit:shl(1,$ChannelNumber))"!][!//
                [!ENDIF!][!//
              [!ENDIF!][!//
            [!ELSE!][!//
              [!WARNING "Warning: The specified resource does not exist!!"!][!//
            [!ENDIF!][!//
          [!ENDSELECT!][!//
        [!ENDIF!][!//
      [!ENDFOR!][!//
      {
      [!INDENT "4"!][!//
        /* Bit map of the channels with TRL enabled */
        [!"num:inttohex($TrlStatusWord1)"!]U,
        [!IF "$DmaMaxChannels > 32 "!][!//
          [!"num:inttohex($TrlStatusWord2)"!]U,
        [!ENDIF!][!//
        [!IF "$DmaMaxChannels > 64 "!][!//
          [!"num:inttohex($TrlStatusWord3)"!]U,
        [!ENDIF!][!//
        [!IF "$DmaMaxChannels > 96 "!][!//
          [!"num:inttohex($TrlStatusWord4)"!]U,
        [!ENDIF!][!//
      [!ENDINDENT!][!//
      },
    [!ENDINDENT!][!//
    /* Total number of DMA channels */
    [!"text:toupper(num:inttohex($NoOfDmaChannels,8))"!]U,
  [!ENDINDENT!][!//
  };
  /* ************************************************************** */
[!ENDINDENT!][!//

[!ENDSELECT!][!//

[!INDENT "0"!][!//
  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars
   * because of naming convention*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars
   * because of naming convention*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars
   * because of naming convention*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars
   * because of naming convention*/
  #define DMA_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Dma_Memmap.h is repeatedly included
   * without include guard. This is as per AUTOSAR */
  /* MISRA2012_RULE_20_1_JUSTIFICATION: declaration of MoveEngine Notification
   * before #include memap.h - Accepted deviation in AUTOSAR */
  #include "Dma_MemMap.h"
[!ENDINDENT!][!//
