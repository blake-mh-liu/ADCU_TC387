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
**  FILENAME    : Iom_PBcfg.c                                                 **
**                                                                            **
**  VERSION     : 7.0.0                                                       **
**                                                                            **
**  DATE        : 2021-02-23                                                  **
**                                                                            **
**  BSW MODULE DECRIPTION : NA                                                **
**                                                                            **
**  VARIANT     : Variant PB                                                  **
**                                                                            **
**  PLATFORM    : Infineon AURIX2G                                            **
**  AUTHOR      : DL-AUTOSAR-Engineering                                      **
**                                                                            **
**  VENDOR      : Infineon Technologies                                       **
**                                                                            **
**  DESCRIPTION : This file contains                                          **
**                Code template for Iom_PBCfg.c file                          **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: No                                       **
**                                                                            **
*******************************************************************************/!][!//
[!//
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
***************************************************************************** **
**                                                                            **
**  FILENAME    : Iom_PBcfg.c                                                 **
**                                                                            **
**  VERSION     : 7.0.0                                                     **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]                !!!IGNORE-LINE!!!      **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                    !!!IGNORE-LINE!!!       **
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
**  DESCRIPTION  : IOM configuration generated out of ECU configuration       **
**                 file (Iom.bmd/.xdm)                                        **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: No                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                       Includes                                             **
*******************************************************************************/

[!NOCODE!][!//
  [!IF "not(node:exists(as:modconf('ResourceM')[1]))"!]
    [!ERROR!][!//
      IOM needs ResourceM module.
    [!ENDERROR!][!//
  [!ENDIF!]

  [!IF "not(node:exists(as:modconf('Mcu')[1]))"!]
    [!ERROR!][!//
      IOM needs MCU module.
    [!ENDERROR!][!//
  [!ENDIF!]
[!ENDNOCODE!][!//

/* Include module header file */
#include "Iom.h"

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

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/


/* Memory Mapping the configuration constant */
#define IOM_START_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
  guideline.*/

#include "Iom_MemMap.h"

/*******************************************************************************
**                     Utility Macros                                         **
*******************************************************************************/


/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/


[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Iom')[1]"!][!//
  [!//
  [!VAR "ModuleIndex" = "num:i(1)"!][!//
  [!VAR "TotalConfig" = "num:i(1)"!][!//
  [!VAR "ModulePath" = "'IomConfigSet/*[1]'"!][!//
  [!VAR "FpcCount" = "num:i(count(IomConfigSet/IomFpcConfiguration/*))"!][!//

  [!INDENT "0"!][!//
    /* FPC configuration */
    [!IF "$VariantsConfigured = num:i(1)"!][!//
      static const Iom_FpcConfigType Iom_kFpcConfiguration[]_[!"$PredefinedVarName"!] =
    [!ELSE!]
      static const Iom_FpcConfigType Iom_kFpcConfiguration[] =
    [!ENDIF!][!//
    {
      [!FOR "FpcIndex" = "0" TO "(num:i($FpcCount)- 1)"!][!//
        [!INDENT "2"!][!//
          {
            [!SELECT "IomConfigSet/IomFpcConfiguration/*[($FpcIndex) + num:i(1)]"!][!//
              [!NOCODE!][!//
                [!VAR "FpcCompVal" = "./IomFpcCompareVal"!][!//
                [!VAR "FpcResetTimer" = "./IomFpcResetTimer"!][!//
                [!VAR "FpcResetTimerVal" = "num:i(0)"!][!//
                [!IF "$FpcResetTimer = 'IOM_TIMER_CLEAR'"!][!//
                  [!VAR "FpcResetTimerVal" = "num:i(1)"!][!//
                [!ENDIF!][!//
                [!VAR "FpcConfVal" = "bit:or(num:i(substring(./IomFpcMode,9,1)),num:i(bit:shl(num:i(substring(./IomFpcMonInputSel,10,1)),num:i(3))))"!][!//
                [!VAR "FpcConfVal1" = "bit:or(num:i($FpcConfVal),num:i(bit:shl(num:i($FpcResetTimerVal),num:i(6))))"!][!//
                [!VAR "FpcConfVal2" = "bit:or(num:i($FpcConfVal1),num:i(bit:shl(num:i(substring(./IomFpcReferInputSel,10,1)),num:i(8))))"!][!//
                [!VAR "FpcConfVal3" = "bit:or(num:i($FpcCompVal),num:i(bit:shl(num:i($FpcConfVal2),num:i(16))))"!][!//
              [!ENDNOCODE!][!//
              [!INDENT "4"!][!//
                /* FPC control register value */
                ([!"num:inttohex($FpcConfVal3,8)"!]U),
                /* FPC unit number */
                ((uint8) [!"(./IomFpcHwUnit)"!]U)
              [!ENDINDENT!][!//
            [!ENDSELECT!][!//
          }
        [!ENDINDENT!][!//
        [!IF "($FpcIndex)!=(num:i($FpcCount)- 1)"!],
        [!ENDIF!]

      [!ENDFOR!][!//

    };
  [!ENDINDENT!][!//
  [!INDENT "0"!][!//
    [!VAR "LamCount" = "num:i(count(IomConfigSet/IomLamConfiguration/*))"!][!//
    /* LAM Configuration */
    [!IF "$VariantsConfigured = num:i(1)"!][!//
      static const Iom_LamConfigType Iom_kLamConfiguration[]_[!"$PredefinedVarName"!] =
    [!ELSE!]
      static const Iom_LamConfigType Iom_kLamConfiguration[] =
    [!ENDIF!][!//
    {
      [!INDENT "2"!][!//
        [!FOR "LamIndex" = "0" TO "(num:i($LamCount)- 1)"!][!//
          {
            [!SELECT "IomConfigSet/IomLamConfiguration/*[($LamIndex) + num:i(1)]"!][!//
              [!NOCODE!][!//
                [!VAR "LamInvReferSignal" = "./IomLamInvReferSignal"!][!//
                [!VAR "LamInvReferSignalVal" = "num:i(0)"!][!//
                [!IF "$LamInvReferSignal = 'true'"!][!//
                  [!VAR "LamInvReferSignalVal" = "num:i(1)"!][!//
                [!ENDIF!][!//
                [!VAR "LamInvMonSignal" = "./IomLamInvMonSignal"!][!//
                [!VAR "LamInvMonSignalVal" = "num:i(0)"!][!//
                [!IF "$LamInvMonSignal = 'true'"!][!//
                  [!VAR "LamInvMonSignalVal" = "num:i(1)"!][!//
                [!ENDIF!][!//
                [!VAR "LamMonSrcSelect" = "./IomLamMonSrcSelect"!][!//
                [!VAR "LamMonSrcSelectVal" = "num:i(0)"!][!//
                [!IF "$LamMonSrcSelect = 'IOM_MON_SIGNAL_EXOR_FPCR'"!][!//
                  [!VAR "LamMonSrcSelectVal" = "num:i(1)"!][!//
                [!ENDIF!][!//
                [!VAR "LamRunMode" = "./IomLamRunMode"!][!//
                [!VAR "LamRunModeVal" = "num:i(0)"!][!//
                [!IF "$LamRunMode = 'IOM_EVENT_WINDOW_GATED'"!][!//
                  [!VAR "LamRunModeVal" = "num:i(1)"!][!//
                [!ENDIF!][!//
                [!VAR "LamEventWinSelect" = "./IomLamEventWinSelect"!][!//
                [!VAR "LamEventWinSelectVal" = "num:i(0)"!][!//
                [!IF "$LamEventWinSelect = 'IOM_EVENT_WIN_GEN_MON'"!][!//
                  [!VAR "LamEventWinSelectVal" = "num:i(1)"!][!//
                [!ENDIF!][!//
                [!VAR "LamDisableEvents" = "./IomLamDisableEvents"!][!//
                [!VAR "LamDisableEventsVal" = "num:i(0)"!][!//
                [!IF "$LamDisableEvents = 'true'"!][!//
                  [!VAR "LamDisableEventsVal" = "num:i(1)"!][!//
                [!ENDIF!][!//
                [!VAR "LamEveWinActEdgeSel" = "./IomLamEveWinActiveEdgeSelect"!][!//
                [!VAR "LamEveWinActEdgeSelVal" = "num:i(0)"!][!//
                [!IF "$LamEveWinActEdgeSel = 'IOM_NEITHER_GATE_POS_CLR'"!][!//
                  [!VAR "LamEveWinActEdgeSelVal" = "num:i(1)"!][!//
                [!ELSEIF "$LamEveWinActEdgeSel = 'IOM_NEITHER_GATE_NEG_CLR'"!][!//
                  [!VAR "LamEveWinActEdgeSelVal" = "num:i(2)"!][!//
                [!ELSEIF "$LamEveWinActEdgeSel = 'IOM_NEITHER_GATE_EITHER_CLR'"!][!//
                  [!VAR "LamEveWinActEdgeSelVal" = "num:i(3)"!][!//
                [!ELSEIF "$LamEveWinActEdgeSel = 'IOM_POS_GATE_NEITHER_CLR'"!][!//
                  [!VAR "LamEveWinActEdgeSelVal" = "num:i(4)"!][!//
                [!ELSEIF "$LamEveWinActEdgeSel = 'IOM_POS_GATE_POS_CLR'"!][!//
                  [!VAR "LamEveWinActEdgeSelVal" = "num:i(5)"!][!//
                [!ELSEIF "$LamEveWinActEdgeSel = 'IOM_POS_GATE_NEG_CLR'"!][!//
                  [!VAR "LamEveWinActEdgeSelVal" = "num:i(6)"!][!//
                [!ELSEIF "$LamEveWinActEdgeSel = 'IOM_POS_GATE_EITHER_CLR'"!][!//
                  [!VAR "LamEveWinActEdgeSelVal" = "num:i(7)"!][!//
                [!ELSEIF "$LamEveWinActEdgeSel = 'IOM_NEG_GATE_NEITHER_CLR'"!][!//
                  [!VAR "LamEveWinActEdgeSelVal" = "num:i(8)"!][!//
                [!ELSEIF "$LamEveWinActEdgeSel = 'IOM_NEG_GATE_POS_CLR'"!][!//
                  [!VAR "LamEveWinActEdgeSelVal" = "num:i(9)"!][!//
                [!ELSEIF "$LamEveWinActEdgeSel = 'IOM_NEG_GATE_NEG_CLR'"!][!//
                  [!VAR "LamEveWinActEdgeSelVal" = "num:i(10)"!][!//
                [!ELSEIF "$LamEveWinActEdgeSel = 'IOM_NEG_GATE_EITHER_CLR'"!][!//
                  [!VAR "LamEveWinActEdgeSelVal" = "num:i(11)"!][!//
                [!ELSEIF "$LamEveWinActEdgeSel = 'IOM_EITHER_GATE_NEITHER_CLR'"!][!//
                  [!VAR "LamEveWinActEdgeSelVal" = "num:i(12)"!][!//
                [!ELSEIF "$LamEveWinActEdgeSel = 'IOM_EITHER_GATE_POS_CLR'"!][!//
                  [!VAR "LamEveWinActEdgeSelVal" = "num:i(13)"!][!//
                [!ELSEIF "$LamEveWinActEdgeSel = 'IOM_EITHER_GATE_NEG_CLR'"!][!//
                  [!VAR "LamEveWinActEdgeSelVal" = "num:i(14)"!][!//
                [!ELSEIF "$LamEveWinActEdgeSel = 'IOM_EITHER_GATE_EITHER_CLR'"!][!//
                  [!VAR "LamEveWinActEdgeSelVal" = "num:i(15)"!][!//
                [!ENDIF!][!//
                [!VAR "LamInvEventWin" = "./IomLamInvEventWin"!][!//
                [!VAR "LamInvEventWinVal" = "num:i(0)"!][!//
                [!IF "$LamInvEventWin = 'true'"!][!//
                  [!VAR "LamInvEventWinVal" = "num:i(1)"!][!//
                [!ENDIF!][!//
              [!ENDNOCODE!][!//
              [!INDENT "4"!][!//
                /* LAM threshold value */
                ((uint32)[!"(./IomLamThreshold )"!]U),
                /* LAM configuration value */
                [!NOCODE!][!//
                  [!VAR "LamConfVal" = "bit:or(num:i($LamInvReferSignalVal),num:i(bit:shl(num:i($LamInvMonSignalVal),num:i(1))))"!][!//
                  [!VAR "LamConfVal1" = "bit:or(num:i($LamConfVal),num:i(bit:shl(num:i($LamMonSrcSelectVal),num:i(2))))"!][!//
                  [!VAR "LamConfVal2" = "bit:or(num:i($LamConfVal1),num:i(bit:shl(num:i($LamRunModeVal),num:i(3))))"!][!//
                  [!VAR "LamConfVal3" = "bit:or(num:i($LamConfVal2),num:i(bit:shl(num:i($LamEventWinSelectVal),num:i(4))))"!][!//
                  [!VAR "LamConfVal4" = "bit:or(num:i($LamConfVal3),num:i(bit:shl(num:i($LamDisableEventsVal),num:i(5))))"!][!//
                  [!VAR "LamConfVal5" = "bit:or(num:i($LamConfVal4),num:i(bit:shl(num:i($LamEveWinActEdgeSelVal),num:i(8))))"!][!//
                  [!VAR "LamConfVal6" = "bit:or(num:i($LamConfVal5),num:i(bit:shl(num:i($LamInvEventWinVal),num:i(12))))"!][!//
                  [!VAR "LamConfVal7" = "bit:or(num:i($LamConfVal6),num:i(bit:shl(num:i(substring(./IomLamMonInputSel,23,2)),num:i(16))))"!][!//
                  [!VAR "LamConfVal8" = "bit:or(num:i($LamConfVal7),num:i(bit:shl(num:i(substring(./IomLamRefInputSel,21,2)),num:i(20))))"!][!//
                [!ENDNOCODE!][!//
                ([!"num:inttohex($LamConfVal8,9)"!]U),
                /* LAM unit number */
                ((uint8) [!"(./IomLamHwUnit)"!]U)
              [!ENDINDENT!][!//
            [!ENDSELECT!][!//
          }
          [!IF "($LamIndex)!=(num:i($LamCount)- 1)"!],
          [!ENDIF!]

        [!ENDFOR!][!//
      [!ENDINDENT!][!//
    };
  [!ENDINDENT!][!//

  [!INDENT "0"!][!//
    /* ECM configuration */
    [!IF "$VariantsConfigured = num:i(1)"!][!//
      static const Iom_EcmConfigType Iom_kEcmConfiguration_[!"$PredefinedVarName"!] =
    [!ELSE!]
      static const Iom_EcmConfigType Iom_kEcmConfiguration =
    [!ENDIF!][!//
    {
      [!INDENT "2"!][!//
        [!SELECT "IomConfigSet/IomEcmConfiguration/IomEventCombModCount"!][!//
          /* ECM counter configuration */
          [!NOCODE!][!//
            [!VAR "EcmCntVal" = "bit:or(num:i(./IomEcmEventSel0),num:i(bit:shl(num:i(./IomEcmThreshold0),num:i(4))))"!][!//
            [!VAR "EcmCntVal1" = "bit:or(num:i($EcmCntVal),num:i(bit:shl(num:i(./IomEcmEventSel1),num:i(8))))"!][!//
            [!VAR "EcmCntVal2" = "bit:or(num:i($EcmCntVal1),num:i(bit:shl(num:i(./IomEcmThreshold1),num:i(12))))"!][!//
            [!VAR "EcmCntVal3" = "bit:or(num:i($EcmCntVal2),num:i(bit:shl(num:i(./IomEcmEventSel2),num:i(16))))"!][!//
            [!VAR "EcmCntVal4" = "bit:or(num:i($EcmCntVal3),num:i(bit:shl(num:i(./IomEcmThreshold2),num:i(20))))"!][!//
            [!VAR "EcmCntVal5" = "bit:or(num:i($EcmCntVal4),num:i(bit:shl(num:i(./IomEcmEventSel3),num:i(24))))"!][!//
            [!VAR "EcmCntVal6" = "bit:or(num:i($EcmCntVal5),num:i(bit:shl(num:i(./IomEcmThreshold3),num:i(28))))"!][!//
          [!ENDNOCODE!][!//
          [!"num:inttohex($EcmCntVal6,8)"!]U,[!//
        [!ENDSELECT!][!//

        [!SELECT "IomConfigSet/IomEcmConfiguration/IomEventCombModGlobalSel"!][!//
          [!NOCODE!][!//
            [!VAR "EcmEventSel" = "'IomEcmEventCombSel'"!][!//
            [!VAR "EcmCountHex" = "num:i(0)"!]
            [!FOR "EcmCount" = "0" TO "15"!][!//
              [!VAR "EcmValue" = "node:value(node:ref(concat($EcmEventSel,$EcmCount)))"!][!//
              [!IF "$EcmValue = 'IOM_DISABLE_CHANNEL_EVENT'"!][!//
                [!VAR "EcmCountHex" = "bit:or(num:i($EcmCountHex),bit:shl(num:i(0),num:i($EcmCount)))"!][!//
              [!ELSE!][!//
                [!VAR "EcmCountHex" = "bit:or(num:i($EcmCountHex),bit:shl(num:i(1),num:i($EcmCount)))"!][!//
              [!ENDIF!][!//
            [!ENDFOR!][!//
            [!VAR "EcmAccEventSel" = "'IomEcmAccEventCombSel'"!][!//
            [!FOR "EcmAccCount" = "0" TO "3"!][!//
              [!VAR "EcmAccValue" = "node:value(node:ref(concat($EcmAccEventSel,$EcmAccCount)))"!][!//
              [!IF "$EcmAccValue = 'IOM_DISABLE_COUNT_EVENT'"!][!//
                [!VAR "EcmCountHex" = "bit:or(num:i($EcmCountHex),bit:shl(num:i(0),num:i(16 + num:i($EcmAccCount))))"!][!//
              [!ELSE!][!//
                [!VAR "EcmCountHex" = "bit:or(num:i($EcmCountHex),bit:shl(num:i(1),num:i(16 + num:i($EcmAccCount))))"!][!//
              [!ENDIF!][!//
            [!ENDFOR!][!//
          [!ENDNOCODE!][!//
        [!ENDSELECT!][!//
        ([!"num:inttohex($EcmCountHex,8)"!]U)[!//
      [!ENDINDENT!][!//

    };
  [!ENDINDENT!][!//

  [!INDENT "0"!][!//
    [!IF "$VariantsConfigured = num:i(1)"!][!//
      const Iom_ConfigType Iom_Config_[!"$PredefinedVarName"!] =
    [!ELSE!]
      const Iom_ConfigType Iom_Config =
    [!ENDIF!][!//
    {
      [!INDENT "2"!][!//
        &Iom_kFpcConfiguration[0],
        &Iom_kLamConfiguration[0],
        &Iom_kEcmConfiguration,
         /* GTM configuration */
        [!IF "ecu:get('Gtm.Available')='true'"!][!//
          [!SELECT "IomConfigSet/IomGtmConfiguration"!][!//
            [!NOCODE!][!//
              [!VAR "GtmString" = "'IomGtmInput'"!][!//
              [!VAR "GtmAccessHex" = "num:i(0)"!][!//
              [!FOR "GtmCount" = "0" TO "7"!][!//
                [!VAR "GtmAccessValue" = "node:value(node:ref(concat($GtmString,$GtmCount)))"!][!//
                [!IF "$GtmAccessValue = 'IOM_ENABLE_GTM_INPUT'"!][!//
                  [!VAR "GtmAccessHex" = "bit:or(num:i($GtmAccessHex),bit:shl(num:i(1),num:i($GtmCount)))"!][!//
                [!ELSE!][!//
                  [!VAR "GtmAccessHex" = "bit:or(num:i($GtmAccessHex),bit:shl(num:i(0),num:i($GtmCount)))"!][!//
                [!ENDIF!][!//
              [!ENDFOR!][!//
            [!ENDNOCODE!][!//
          [!ENDSELECT!][!//
          ([!"num:inttohex($GtmAccessHex,8)"!]U),[!//
        [!ELSE!][!//
          (0x0U),
        [!ENDIF!][!//


        /* Clc configuration */
        [!SELECT "IomConfigSet/IomSysConfiguration/IomClcConfiguration"!][!//
          [!NOCODE!][!//
            [!VAR "ClcSleepMode" = "./IomClcSleepModeEn"!][!//
            [!"$ClcSleepMode"!][!//
            [!VAR "ClcRmcval" = "./IomClcRmcVal"!][!//
            [!"num:i($ClcRmcval)"!]
            [!VAR "ClcSleepModeVal" = "num:i(0)"!][!//
            [!IF "$ClcSleepMode = 'true'"!][!//
              [!VAR "ClcSleepModeVal" = "num:i(1)"!][!//
            [!ENDIF!][!//
            [!VAR "ClkConfVal" = "bit:or(num:i(0),num:i(bit:shl(num:i($ClcSleepModeVal),num:i(3))))"!][!//
            [!VAR "ClkConfVal1" = "bit:or(num:i($ClkConfVal),num:i(bit:shl(num:i($ClcRmcval),num:i(8))))"!][!//
          [!ENDNOCODE!][!//
          [!"num:inttohex($ClkConfVal1,8)"!]U,
        [!ENDSELECT!][!//
        /* Max Channels configured */
        [!IF "$FpcCount = $LamCount"!]
          [!"num:i($FpcCount)"!]U
        [!ELSE!]
          [!ERROR!][!//
            Error: Wrong Configuration. Number of Fpc and Lam channels configured should be same.
          [!ENDERROR!][!//
        [!ENDIF!][!//
      [!ENDINDENT!][!//
    };
  [!ENDINDENT!][!//
  [!INDENT "0"!][!//
    #define IOM_STOP_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
    /*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
    guideline.*/
    /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
    guideline. */

    #include "Iom_MemMap.h"
  [!ENDINDENT!][!//
[!ENDSELECT!][!//

[!AUTOSPACING!][!//

