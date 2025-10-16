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
**  FILENAME  : Sent_PBCfg.c                                                  **
**                                                                            **
**  VERSION   : 9.0.0                                                         **
**                                                                            **
**  DATE      : 2020-06-14                                                    **
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
**  TRACEABILITY : [cover parentID= ]                                         **
**                                                                            **
**  DESCRIPTION  : Code template source file for Sent Driver                  **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
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
**  FILENAME  : Sent_PBCfg.c                                                  **
**                                                                            **
**  VERSION   : 9.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]   !!!IGNORE-LINE!!!                  **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]       !!!IGNORE-LINE!!!                  **
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
**  DESCRIPTION  : Sent configuration generated out of ECUC file              **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
[!AUTOSPACING!]
[!INDENT "0"!][!//
  [!NOCODE!][!//
    [!//
    [!VAR "VariantsConfigured" = "num:i(0)"!]
    [!SELECT "as:modconf('EcuC')"!][!//
      [!IF "node:exists(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!][!//
        [!VAR "PredefinedVarName1" = "(EcucPostBuildVariants/*[1]/EcucSelectedPostBuildVariantRef)"!]
        [!VAR "PredefinedVarName2" = "substring-after($PredefinedVarName1, "/")"!][!//
        [!VAR "PredefinedVarName3" = "substring-after($PredefinedVarName2, "/")"!][!//
        [!VAR "PredefinedVarName" = "substring-after($PredefinedVarName3, "/")"!][!//
        [!VAR "VariantsConfigured" = "num:i(1)"!]
      [!ENDIF!][!//
    [!ENDSELECT!]
    [!INCLUDE "Sent.m"!][!//
  [!ENDNOCODE!][!//

  /*******************************************************************************
  **                       Includes                                             **
  *******************************************************************************/
  #include "Sent_Cfg.h"
  /* Module header file */
  #include "Sent.h"
  /*******************************************************************************
  **                      Private Macro definition                              **
  *******************************************************************************/

  /*******************************************************************************
  **                      Configuration Options                                 **
  *******************************************************************************/

  /*******************************************************************************
  **                      Private Type Definitions                              **
  *******************************************************************************/

  /*******************************************************************************
  **                      Private Function Declarations                         **
  *******************************************************************************/

  /*******************************************************************************
  **                      Global Variable Definitions                           **
  *******************************************************************************/

  /*******************************************************************************
  **                      Global Funtion Declarations                           **
  *******************************************************************************/

  /*******************************************************************************
  **                      Global Constant Definitions                           **
  *******************************************************************************/
  [!/* Select MODULE-CONFIGURATION as context-node */!][!//
  [!SELECT "as:modconf('Sent')[1]"!][!//
    [!CALL "Sent_GenerateModuleMap", "Module" = "'SENT'"!][!//
    [!VAR "AccenInit" = "num:i(0)"!][!//
    [!NOCODE!]
      [!IF "SentGeneral/SentAccessEnable = 'SENT_ACCEN_INIT'"!][!//
        [!VAR "AccenInit" = "num:i(1)"!][!//
      [!ENDIF!][!//
      [!VAR "TotalConfig" = "num:i(count(SentConfigSet/*))"!][!//
      [!FOR "SentId" ="num:i(1)" TO "(num:i($TotalConfig))"!][!//
        [!SELECT "SentConfigSet/*[num:i($SentId)]"!][!//
          /*Channel Structure for selected Core*/
          [!VAR "MaxCoreConfigured" = "num:i(count(text:split($CGCoreUsed, ',')))"!]
          [!FOR "CoreId" = "num:i(0)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
            [!VAR "TempCoreId" = "concat('CORE',$CoreId)"!][!//
            [!CALL "Sent_GetMasterCoreID"!][!//
            [!IF "(text:contains( text:split($CGAllocatedCores,','), $TempCoreId)) or ($CGMasterCoreId = $TempCoreId)"!][!//
              [!CODE!]
                /******************* CORE[!"num:i($CoreId)"!] CHANNEL CONFIGURATION MEMMAP SECTION *************/
                /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
                /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
                /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
                /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
                #define SENT_START_SEC_CONFIG_DATA_QM_CORE[!"$CoreId"!]_UNSPECIFIED
                /*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
                guideline.*/
                /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
                guideline. */
                #include "Sent_MemMap.h"
                /*Channel Structure for selected Core*/
                [!IF "$VariantsConfigured = num:i(1)"!][!//
                  static const Sent_ChannelCfgType Sent_ChanConfig_Core[!"$CoreId"!]_[!"$PredefinedVarName"!][SENT_CHANNEL_COUNT_CORE[!"$CoreId"!]] =
                [!ELSE!][!//
                  static const Sent_ChannelCfgType Sent_ChanConfig_Core[!"$CoreId"!][SENT_CHANNEL_COUNT_CORE[!"$CoreId"!]] =
                [!ENDIF!][!//
                {
              [!ENDCODE!]
              [!VAR "SPBClock" = "(node:ref(./SentSystemClock)/*/McuClockSPBFrequency)"!] [!//
              [!VAR "SentClock" = "$SPBClock div SentModuleClkDiv"!] [!//
              [!VAR "SentFracClock" = "$SentClock div (num:i(1024) - SentBaudFracStep)"!] [!//
              [!VAR "SuspendEn" = "num:i(0)"!][!//
              [!IF "SentSleepModeEnable = 'true'"!][!//
                [!/* SUSEN bit is bit 19 in RCR register */!][!//
                [!VAR "SuspendEn" = "num:i(524288)"!][!//
              [!ENDIF!][!//
              [!CALL "Sent_GenerateModuleMap", "Module" = "'SENT'"!][!//
              [!CALL "Sent_GetMasterCoreID"!][!//
              [!VAR "TotalChannels" = "num:i(0)"!][!//
              [!VAR "TotalChannels" = "num:i(count(SentChannelConfigSet/*))"!][!//
              [!VAR "IntNode" = "$CoreId"!]
              [!FOR "ChannelNo" = "num:i(0)" TO "num:i($TotalChannels)"!][!//
                [!SELECT "node:SentChannelConfigSet/*[num:i($ChannelNo)]"!][!//
                  [!VAR "NodeName" = "node:name(.)"!][!//
                  [!CALL "Sent_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
                  [!IF "$CGAllocationResult = 'TRUE'"!][!//
                    [!VAR "RCRVal" = "num:i(0)"!][!//
                    [!IF "SentChanIgnoreEndPulse = 'true'"!][!//
                      [!/* IEP bit is bit 1 */!][!//
                      [!VAR "RCRVal" = "bit:shl(2,0) + $RCRVal"!][!//
                    [!ENDIF!][!//
                    [!IF "SentChanCRCMode = 'SENT_IFX_ALTERNATE'"!][!//
                      [!/* ACE bit is bit 2 */!][!//
                      [!VAR "RCRVal" = "bit:shl(2,1) + $RCRVal"!][!//
                    [!ENDIF!][!//
                    [!IF "SentChanStatusNibbleCRCInc = 'true'"!][!//
                      [!/* SNI bit is bit 3 */!][!//
                      [!VAR "RCRVal" = "bit:shl(2,2) + $RCRVal"!][!//
                    [!ENDIF!][!//
                    [!IF "SentChanSerialProcEn = 'true'"!][!//
                      [!/* SDP bit is bit 4 */!][!//
                      [!VAR "RCRVal" = "bit:shl(2,3) + $RCRVal"!][!//
                    [!ENDIF!][!//
                    [!IF "SentChanSerialCrcDisable = 'true'"!][!//
                      [!/* SCDIS bit is bit 5 */!][!//
                      [!VAR "RCRVal" = "bit:shl(2,4) + $RCRVal"!][!//
                    [!ENDIF!][!//
                    [!IF "SentChanFrameCrcDisable = 'true'"!][!//
                      [!/* CDIS bit is bit 6 */!][!//
                      [!VAR "RCRVal" = "bit:shl(2,5) + $RCRVal"!][!//
                    [!ENDIF!][!//
                    [!IF "SentChanFrameChk = 'SENT_PAST_VALID_SYNC_PULSE'"!][!//
                      [!/* CFC bit is bit 7 */!][!//
                      [!VAR "RCRVal" = "bit:shl(2,6) + $RCRVal"!][!//
                    [!ENDIF!][!//
                    [!/* FRL bits are bit 8-15 */!][!//
                    [!VAR "RCRVal" = "num:i(SentChanFrameDataLen * 256) + $RCRVal"!][!//
                    [!IF "SentChanCRZEn = 'false'"!][!//
                      [!/* CFZ bit is bit 16 */!][!//
                      [!VAR "RCRVal" = "bit:shl(2,15) + $RCRVal"!][!//
                    [!ENDIF!][!//
                    [!IF "SentChanEnESF = 'true'"!][!//
                      [!/* ESF bit is bit 17 */!][!//
                      [!VAR "RCRVal" = "bit:shl(2,16) + $RCRVal"!][!//
                    [!ENDIF!][!//
                    [!IF "SentChanDriftErrEn = 'false'"!][!//
                      [!/* IDE bit is bit 18 */!][!//
                      [!VAR "RCRVal" = "bit:shl(2,17) + $RCRVal"!][!//
                    [!ENDIF!][!//
                    [!/* Add SUSEN if enabled */!][!//
                    [!VAR "RCRVal" = "$SuspendEn + $RCRVal"!][!//
                    [!/* Add FDFL if enabled */!][!//
                    [!IF "SentChanFreqDriftCheckLen = 'true'"!][!//
                      [!/* FDFL is bit 20 and 18bit and 1bit should be 1 for FDFL*/!][!//
                      [!VAR "RCRVal" = "num:i(1310722) + $RCRVal"!][!//
                    [!ENDIF!][!//
                    [!VAR "OutMac_ALTI" = "num:i(0)"!][!//
                    [!VAR "PortSelect" = "SentRxInput"!][!//
                    [!VAR "PortPinID" = "text:split($PortSelect, '_')[position()-1 = 2]"!][!//
                    [!IF "$PortPinID = 'A'"!][!//
                      [!VAR "PISEL_Value" = "num:i(0)"!][!//
                    [!ELSEIF "$PortPinID = 'B'"!][!//
                      [!VAR "PISEL_Value" = "num:i(1)"!][!//
                    [!ELSEIF "$PortPinID = 'C'"!][!//
                      [!VAR "PISEL_Value" = "num:i(2)"!][!//
                    [!ELSEIF "$PortPinID = 'D'"!][!//
                      [!VAR "PISEL_Value" = "num:i(3)"!][!//
                    [!ENDIF!][!//
                    [!//
                    [!VAR "IOCRVal" = "num:i(0)"!][!//
                    [!VAR "IOCRVal" = "$PISEL_Value + $IOCRVal"!][!//
                    [!/* DEPTH bits are bit 4-7 */!][!//
                    [!VAR "IOCRVal" = "num:i(SentChanGlitchFilterDepth * 16) + $IOCRVal"!][!//
                    [!IF "SentChanOutPulse = 'SENT_ACTIVE_HIGH'"!][!//
                      [!/* OIE bit is bit 8 */!][!//
                      [!VAR "IOCRVal" = "bit:shl(2,7) + $IOCRVal"!][!//
                    [!ENDIF!][!//
                    [!IF "SentChanInPulse = 'SENT_ACTIVE_HIGH'"!][!//
                      [!/* IIE bit is bit 9 */!][!//
                      [!VAR "IOCRVal" = "bit:shl(2,8) + $IOCRVal"!][!//
                    [!ENDIF!][!//
                    [!//
                    [!//
                    [!VAR "SentChanPreDivClock" = "$SentFracClock div (num:i(1) + SentChanPreDiv)"!][!//
                    [!VAR "SentChanBaudFreq" = "($SentChanPreDivClock * num:i(56)) div SentChanBaudDiv"!][!//
                    [!VAR "SentChanBaudRate" = "(num:i(1) div $SentChanBaudFreq) * num:i(1000000)"!][!//

                    [!/* Following code snippet is to ensure that nibble position configured in **
                    **   view is not repeated.                                                  **
                    **   Algorithm:                                                             **
                    **       Step1: Extract each position value from configured view            **
                    **       Step2: set the corresponding bit posion in UniqueView using XOR    **
                    **       Step3: varify the final value of UniqueView is 0xFF                **
                    **       Step4: If value is not correct report error                      */!]

                    [!VAR "DataView" = "num:i(SentChanDataView)"!]
                    [!VAR "UniqueView" = "num:i(0)"!]
                    [!FOR "Iterator" ="num:i(1)" TO "(num:i(8))"!]
                      [!VAR "Position" = "num:i(num:mod($DataView,num:i(16)))"!]
                      [!VAR "DataView" = "bit:shr($DataView,4)"!]
                      [!VAR "UniqueView" = "bit:xor( $UniqueView, bit:shl(1,$Position))"!]
                    [!ENDFOR!]
                    [!IF "$UniqueView != num:i(255)"!]
                      [!ERROR!]
                        Positions configured in [!"as:name(.)"!]/SentChanDataView is not valid. SentChanDataView is allowed to have only unique numbers ranging from 0 to 7.
                      [!ENDERROR!]
                    [!ENDIF!]
                    [!CODE!]
                      [!INDENT "2"!][!//
                        {
                        [!INDENT "4"!][!//
                          [!VAR "Sentchannel"="node:name(.)"!]
                          /* Channel:[!"$Sentchannel"!] */
                          /* SENT_RCRx register value */
                          ([!"num:inttohex($RCRVal, 8)"!]U),
                          /* SENT_IOCRx register value */
                          ([!"num:inttohex($IOCRVal, 8)"!]U),
                          /* SENT_VIEWx register value */
                          ([!"num:inttohex(SentChanDataView, 8)   "!]U),
                          /* SENT_CPDRx register value */
                          ([!"num:inttohex(SentChanPreDiv, 8)"!]U),
                          /* SENT_CFDRx reg value (Baudrate tick time derived is [!"$SentChanBaudRate"!](us)) */
                          ([!"num:inttohex(SentChanBaudDiv, 8)"!]U),
                          /* Frame length */
                          ([!"SentChanFrameDataLen"!]U),
                          /* SENT Physical Channel Id arranged corewise */
                          ([!"substring-after(SentChPhyIndex,"SENT")"!]U),
                          /*Callback function ptr */
                          [!"SentChanCalloutFn "!],
                          /*Channel interrupt node */
                          [!"num:inttohex($IntNode)"!]
                        [!ENDINDENT!][!//
                        }
                      [!ENDINDENT!][!//
                      [!IF "ChannelNo != TotalChannels - 1"!]
                        ,
                      [!ENDIF!]
                    [!ENDCODE!]
                  [!ENDIF!][!//
                [!ENDSELECT!][!//
              [!ENDFOR!]
              [!CODE!][!//
                };
                /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
                /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
                /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
                /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
                #define SENT_STOP_SEC_CONFIG_DATA_QM_CORE[!"$CoreId"!]_UNSPECIFIED
                /*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
                guideline.*/
                /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
                guideline. */
                #include "Sent_MemMap.h"
                /******************* CORE[!"num:i($CoreId)"!] CHANNEL CONFIGURATION MEMMAP SECTION END*************/
              [!ENDCODE!]
            [!ENDIF!][!//
          [!ENDFOR!][!//
        [!ENDSELECT!][!//
      [!ENDFOR!][!//
      [!VAR "TotalConfig" = "num:i(count(SentConfigSet/*))"!][!//
      [!FOR "SentId" ="num:i(1)" TO "(num:i($TotalConfig))"!][!//
        [!SELECT "SentConfigSet/*[num:i($SentId)]"!][!//
          [!VAR "MaxCoreConfigured" = "num:i(count(text:split($CGCoreUsed, ',')))"!]
          [!FOR "CoreId" = "num:i(0)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
            [!VAR "TempCoreId" = "concat('CORE',$CoreId)"!][!//
            [!CALL "Sent_GetMasterCoreID"!][!//
            [!IF "(text:contains( text:split($CGAllocatedCores,','), $TempCoreId)) or ($CGMasterCoreId = $TempCoreId)"!][!//
              [!CALL "Sent_GenerateModuleMap", "Module" = "'SENT'"!][!//
              [!CALL "Sent_GetMasterCoreID"!][!//
              [!VAR "TotalChannels" = "num:i(0)"!][!//
              [!VAR "TotalChannels" = "num:i(count(SentChannelConfigSet/*))"!][!//
              [!VAR "MaxChannelsCore" = "num:i(0)"!][!//
              [!FOR "Channel" = "num:i(0)" TO "num:i($TotalChannels)"!]
                [!SELECT "node:SentChannelConfigSet/*[num:i($Channel)]"!][!//
                  [!VAR "NodeName" = "node:name(.)"!][!//
                  [!CALL "Sent_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
                  [!IF "$CGAllocationResult = 'TRUE'"!][!//
                    [!VAR "MaxChannelsCore" = "$MaxChannelsCore + num:i(1)"!][!//
                  [!ENDIF!][!//
                [!ENDSELECT!]
              [!ENDFOR!]
              [!CODE!]
                /******************* CORE[!"num:i($CoreId)"!] CHANNEL CONFIGURATION MEMMAP SECTION *************/
                /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
                /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
                /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
                /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
                /* Code data Structure for selected Core*/
                #define SENT_START_SEC_CONFIG_DATA_QM_CORE[!"$CoreId"!]_UNSPECIFIED
                /*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
                guideline.*/
                /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
                guideline. */
                #include "Sent_MemMap.h"
                [!IF "$VariantsConfigured = num:i(1)"!][!//
                  static const Sent_CoreConfigType Sent_CoreConfigCore[!"$CoreId"!]_[!"$PredefinedVarName"!] =
                [!ELSE!][!//
                  static const Sent_CoreConfigType Sent_CoreConfigCore[!"$CoreId"!] =
                [!ENDIF!][!//
                {
                [!INDENT "2"!][!//
                  (Sent_ChannelIdxType)[!"num:i($MaxChannelsCore)"!]U,
                  [!IF "$MaxChannelsCore = num:i(0)"!][!//
                    NULL_PTR
                  [!ELSE!][!//
                    [!IF "$VariantsConfigured = num:i(1)"!][!//
                      Sent_ChanConfig_Core[!"$CoreId"!]_[!"$PredefinedVarName"!]
                    [!ELSE!][!//
                      Sent_ChanConfig_Core[!"$CoreId"!]
                    [!ENDIF!][!//
                  [!ENDIF!][!//
                [!ENDINDENT!][!//
                };
                /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
                /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
                /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
                /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
                in generated code due to Autosar Naming constraints.*/
                #define SENT_STOP_SEC_CONFIG_DATA_QM_CORE[!"$CoreId"!]_UNSPECIFIED
                /*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
                guideline.*/
                /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
                guideline. */
                #include "Sent_MemMap.h"
                /******************* CORE[!"num:i($CoreId)"!] CHANNEL CONFIGURATION MEMMAP SECTION END*************/
              [!ENDCODE!][!//
            [!ENDIF!][!//
          [!ENDFOR!][!//
        [!ENDSELECT!][!//
      [!ENDFOR!][!//
    [!ENDNOCODE!]
    /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
    /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
    /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
    /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
    in generated code due to Autosar Naming constraints.*/
    #define SENT_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
    /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
    without safegaurd. It complies to Autosar guidelines. */
    /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
    guideline. */
    #include "Sent_MemMap.h"
    /* Data structure to hold core channel index map */
    /* Allocation of the channels to different cores */
    [!SELECT "SentConfigSet/*[num:i(1)]"!][!//
      [!VAR "TotalChannels" = "num:i(count(SentChannelConfigSet/*))"!][!//
      [!NOCODE!]
        [!VAR "Module" = "'SENT'"!][!//
        [!CALL "Sent_GenerateModuleMap", "Module" = "'SENT'"!][!//
        [!VAR "CurrentIdx" = "num:i(0)"!][!//
        [!VAR "SentCore0Idx" = "num:i(0)"!][!//
        [!VAR "SentCore1Idx" = "num:i(0)"!][!//
        [!VAR "SentCore2Idx" = "num:i(0)"!][!//
        [!VAR "SentCore3Idx" = "num:i(0)"!][!//
        [!VAR "SentCore4Idx" = "num:i(0)"!][!//
        [!VAR "SentCore5Idx" = "num:i(0)"!][!//
        [!//
        [!CODE!]
          [!IF "$VariantsConfigured = num:i(1)"!][!//
            static const Sent_ChannelMapType Sent_ChannelLookUp_[!"$PredefinedVarName"!][[!"num:i($TotalChannels)"!]] =
          [!ELSE!][!//
            static const Sent_ChannelMapType Sent_ChannelLookUp[[!"num:i($TotalChannels)"!]] =
          [!ENDIF!][!//
          {
        [!ENDCODE!][!//
        [!//
        [!INDENT "2"!][!//
          [!CODE!]
            /*CoreID, ChannelIndex*/
          [!ENDCODE!]
          [!FOR "ChannelId" = "num:i(0)" TO "num:i($TotalChannels) - num:i(1)"!][!//
            [!SELECT "SentChannelConfigSet/*[SentChLogiIndex = num:i($ChannelId)]"!][!//
              [!VAR "NodeName" = "node:name(.)"!][!//
              [!FOR "CoreId" = "num:i(0)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
                [!CALL "Sent_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
                [!IF "$CGAllocationResult = 'TRUE'"!][!//
                  [!IF "$CoreId = num:i(0)"!][!//
                    [!VAR "CurrentIdx" = "$SentCore0Idx"!][!//
                    [!VAR "SentCore0Idx" = "$SentCore0Idx+num:i(1)"!][!//
                  [!ELSEIF "$CoreId = num:i(1)"!][!//
                    [!VAR "CurrentIdx" = "$SentCore1Idx"!][!//
                    [!VAR "SentCore1Idx" = "$SentCore1Idx+num:i(1)"!][!//
                  [!ELSEIF "$CoreId = num:i(2)"!][!//
                    [!VAR "CurrentIdx" = "$SentCore2Idx"!][!//
                    [!VAR "SentCore2Idx" = "$SentCore2Idx+num:i(1)"!][!//
                  [!ELSEIF "$CoreId = num:i(3)"!][!//
                    [!VAR "CurrentIdx" = "$SentCore3Idx"!][!//
                    [!VAR "SentCore3Idx" = "$SentCore3Idx+num:i(1)"!][!//
                  [!ELSEIF "$CoreId = num:i(4)"!][!//
                    [!VAR "CurrentIdx" = "$SentCore4Idx"!][!//
                    [!VAR "SentCore4Idx" = "$SentCore4Idx+num:i(1)"!][!//
                  [!ELSEIF "$CoreId = num:i(5)"!][!//
                    [!VAR "CurrentIdx" = "$SentCore5Idx"!][!//
                    [!VAR "SentCore5Idx" = "$SentCore5Idx+num:i(1)"!][!//
                  [!ELSE!][!//
                  [!ENDIF!][!//
                  [!CODE!][!//
                    {[!"num:inttohex(number($CoreId))"!]U,[!"num:inttohex(number($CurrentIdx))"!]U}[!//
                    [!IF "num:i($ChannelId) != num:i($TotalChannels - 1)"!][!//
                      ,
                    [!ENDIF!][!//
                    [!VAR "CurrentIdx" = "num:i(0)"!]
                  [!ENDCODE!]
                [!ENDIF!][!//
              [!ENDFOR!][!//
            [!ENDSELECT!][!//
          [!ENDFOR!][!//
        [!ENDINDENT!][!//
      [!ENDNOCODE!]
      [!CR!][!//
      };
    [!ENDSELECT!][!//
    [!CALL "Sent_GenerateModuleMap", "Module" = "'SENT'"!][!//
    [!CALL "Sent_GetMasterCoreID"!][!//
    [!//
    /* Physical to Logical channel mapping */
    /* physical channel id is the index value of Sent_ChannelId and corresponding
    logical channel id in the channel configuration is stored */
    [!VAR "SentMaxChannel" = "num:i(ecu:get('Sent.MaxChannelsSupported'))"!][!//
    [!IF "$VariantsConfigured = num:i(1)"!][!//
      static const Sent_ChannelIdxType Sent_LogicalChannelId_[!"$PredefinedVarName"!][SENT_HW_MAX_CHANNELS] =
    [!ELSE!][!//
      static const Sent_ChannelIdxType Sent_LogicalChannelId[SENT_HW_MAX_CHANNELS] =
    [!ENDIF!][!//
    {
    [!INDENT "2"!][!//
      [!FOR "SentCounter" = "0" TO "num:i($SentMaxChannel - 1)"!][!//
        [!SELECT "SentConfigSet/*[num:i(1)]"!][!//
          [!IF "num:i(count(SentChannelConfigSet/*[SentChPhyIndex = concat('SENT',$SentCounter)])) = num:i(0)"!][!//
            0xFFU[!//
          [!ELSE!][!//
            [!LOOP "SentChannelConfigSet/*[SentChPhyIndex = concat('SENT',$SentCounter)]"!][!//
              [!"node:value(./SentChLogiIndex)"!]U[!//
            [!ENDLOOP!]
          [!ENDIF!][!//
          [!IF "num:i($SentCounter) != num:i($SentMaxChannel - 1)"!][!//
            ,
          [!ELSE!]
          [!ENDIF!][!//
        [!ENDSELECT!][!//
      [!ENDFOR!][!//
    [!ENDINDENT!]
    [!CR!][!//
    };
    /* Logical to physical channel mapping */
    /* Logical id is the index value hardware channel id and
    physical id is the mapping to the configured channel in sequence */
    [!VAR "SentMaxChannel" = "num:i(count(SentConfigSet/*[1]/SentChannelConfigSet/*))"!][!//
    [!IF "$VariantsConfigured = num:i(1)"!][!//
      static const Sent_ChannelIdxType Sent_PhyChannelId_[!"$PredefinedVarName"!][SENT_MAX_CHANNELS_CONFIGURED] =
    [!ELSE!][!//
      static const Sent_ChannelIdxType Sent_PhyChannelId[SENT_MAX_CHANNELS_CONFIGURED] =
    [!ENDIF!][!//
    {
    [!INDENT "2"!][!//
      [!VAR "SentCounter" = "num:i(0)"!]
      [!LOOP "SentConfigSet/*[1]/SentChannelConfigSet/*"!][!//
        [!VAR "SentCounter" = "num:i($SentCounter + 1)"!]
        [!"substring-after(node:value(./SentChPhyIndex),"SENT")"!]U[!//
        [!IF "num:i($SentCounter) != num:i($SentMaxChannel)"!][!//
          ,
        [!ENDIF!][!//
      [!ENDLOOP!]
    [!ENDINDENT!]
    [!CR!][!//
    };
  [!ENDSELECT!][!//
  /* SENT Module Configuration */
  [!/*const Sent_ConfigType Sent_Config = */!][!//
  [!IF "$VariantsConfigured = num:i(1)"!][!//
    const Sent_ConfigType Sent_Config_[!"$PredefinedVarName"!] =
  [!ELSE!]
    const Sent_ConfigType Sent_Config =
  [!ENDIF!]
  {
  [!INDENT "2"!][!//
    [!SELECT "SentConfigSet/*[num:i($SentId)]"!][!//
      [!CALL "Sent_GenerateModuleMap", "Module"="'SENT'"!][!//
      {
      [!INDENT "4"!][!//
        [!FOR "CoreId" = "num:i(0)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
          [!VAR "TempCoreId" = "concat('CORE',$CoreId)"!][!//
          [!IF "(text:contains( text:split($CGAllocatedCores,','), $TempCoreId)) or ($CGMasterCoreId = $TempCoreId)"!][!//
            [!IF "$VariantsConfigured = num:i(1)"!][!//
              &Sent_CoreConfigCore[!"$CoreId"!]_[!"$PredefinedVarName"!][!IF "$CoreId < num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!],[!ENDIF!][!//
            [!ELSE!][!//
              &Sent_CoreConfigCore[!"$CoreId"!][!//
              [!IF "$CoreId < num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!]
                ,
              [!ENDIF!][!//
            [!ENDIF!][!//
          [!ELSE!][!//
            NULL_PTR[!//
            [!IF "$CoreId < num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
              ,
            [!ENDIF!][!//
          [!ENDIF!][!//
        [!ENDFOR!][!//
      [!ENDINDENT!][!//
      [!CR!][!//
      },
      [!NOCODE!][!//
        [!VAR "SleepModeEn" = "num:i(0)"!][!//
        [!IF "SentSleepModeEnable = 'true'"!][!//
          [!/* Set the desired bit of CLC register i.e. 3rd bit */!][!//
          [!VAR "SleepModeEn" = "num:i(8)"!][!//
        [!ENDIF!][!//
        [!/* Get the RMC value and left shift by 8 */!][!//
        [!VAR "SentCLCRegVal" = "num:i(SentModuleClkDiv * 256)"!][!//
        [!/* Add the EDIS bit if set */!][!//
        [!VAR "SentCLCRegVal" = "$SentCLCRegVal + $SleepModeEn"!][!//
      [!ENDNOCODE!][!//
      /* Module clock divider */
      ([!"num:inttohex($SentCLCRegVal)"!]U),
      /* Module Fractional step divider */
      ([!"num:i(SentBaudFracStep)"!]U),
      /* SENT channels configured */
      [!NOCODE!][!//
        //[!VAR "MaxSentChannels" = "num:i(0)"!][!//
        [!VAR "MaxSentChannels" = "num:i(count(SentChannelConfigSet/*))"!][!//
      [!ENDNOCODE!][!//
      ([!"$MaxSentChannels"!]U),
      /* Channel Id to the core sequence mapping */
      [!IF "$VariantsConfigured = num:i(1)"!][!//
        Sent_ChannelLookUp_[!"$PredefinedVarName"!],
      [!ELSE!][!//
        Sent_ChannelLookUp,
      [!ENDIF!][!//
      /* Physical to Logical Id mapping */
      [!IF "$VariantsConfigured = num:i(1)"!][!//
        Sent_LogicalChannelId_[!"$PredefinedVarName"!],
      [!ELSE!][!//
        Sent_LogicalChannelId,
      [!ENDIF!][!//
      /* Logical to Physical ID mapping */
      [!IF "$VariantsConfigured = num:i(1)"!][!//
        Sent_PhyChannelId_[!"$PredefinedVarName"!]
      [!ELSE!][!//
        Sent_PhyChannelId
      [!ENDIF!][!//
    [!ENDSELECT!][!//
  [!ENDINDENT!][!//
  };
  /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
  #define SENT_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
  without safegaurd. It complies to Autosar guidelines. */
  /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline. */
  #include "Sent_MemMap.h"
[!ENDINDENT!][!//
