[!/*****************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2022)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : CanTrcv_17_V9251_Cfg.c                                        **
**                                                                            **
**  VERSION   : 6.0.0                                                         **
**                                                                            **
**  DATE      : 2022-06-28                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : CanTrcv_17_V9251.bmd                              **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={26FCEFB6-8740-47a7-86B0-DBA0870B2008}]    **
**                 [cover parentID={19E4B6BF-2CF1-4a8f-8E67-C62CF4550A32}]    **
**                                                                            **
**  DESCRIPTION  : Code template source file for CanTrcv_17_V9251 Driver      **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of CanTrcv Driver, AUTOSAR Release 4.2.2 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*************************************************************************/!][!//
[!//
/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2022)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : CanTrcv_17_V9251_Cfg.c                                        **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]       !!!IGNORE-LINE!!!                  **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]           !!!IGNORE-LINE!!!                **
**                                                                            **
**  BSW MODULE DECRIPTION : CanTrcv_17_V9251.bmd                              **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION :  CanTrcv_17_V9251 configuration generated out of ECUC file  **
**                                                                            **
**  SPECIFICATION(S) : Specification of CanTrcv Driver, AUTOSAR Release 4.2.2 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/[!//
[!AUTOSPACING!]
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "(as:stod( 'AURIX2G_V9251/EcucDefs/CanTrcv'))"!][!//
[!VAR "CanTrcvConfigSetName" = "'CanTrcvConfigSet'"!][!//

/*******************************************************************************
**                             Includes                                       **
*******************************************************************************/
/* Include CanTrcv header file */
#include "CanTrcv_17_V9251.h"
[!//
[!NOCODE!]
[!IF "not(node:exists(as:modconf('Dio')[1]))"!][!//
  [!ERROR!][!//
    CanTrcv_17_V9251 Code Generator: Dio module is not added to the project.
  [!ENDERROR!][!//
[!ENDIF!][!//

[!IF "not(node:exists(as:modconf('Icu')[1]))"!][!//
  [!ERROR!][!//
    CanTrcv_17_V9251 Code Generator: Icu module is not added to the project.
  [!ENDERROR!][!//
[!ENDIF!][!//

[!IF "not(node:exists(as:modconf('EcuM')[1]))"!][!//
  [!ERROR!][!//
    CanTrcv_17_V9251 Code Generator: EcuM module is not added to the project.
  [!ENDERROR!][!//
[!ENDIF!][!//
[!//
[!ENDNOCODE!][!//
/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Imported Global Constant Declaration                  **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/*******************************************************************************
**Information provided by elements of CanTrcv_17_V9251_ChannelConfig structure**
********************************************************************************
1.CanTrcv_17_V9251_NetworkMode : CAN Transceiver State after Initialization.
                                  - CanTrcvOpModeNormal
                                  - CanTrcvOpModeStandby

2.CanTrcv_17_V9251_WakeupSourceRef : EcuMWakeupSource Id, if configured.
                                WAKEUP_SOURCE_NOT_CONFIGURED, if not configured.

3.CanTrcv_17_V9251_DioChannel  : Choice Reference to a DIO Channel.

4.CanTrcv_17_V9251_DioPinLevel : Internal value for Initialization based on
                                  configured operating mode.
                                  CANTRCV_17_V9251_NORMAL_MODE,if NORMAL_MODE
                                  CANTRCV_17_V9251_STANDBY_MODE,if STANDBY_MODE

5.CanTrcv_17_V9251_ChannelId   : Channel Id of CanTrcv Channel.

6.CanTrcv_17_V9251_WakeupbyBus : Specifies wake up by bus is used or not.
                                  - if TRUE, is used
                                  - if FALSE, is not used
********************************************************************************
**                                                                            **
*******************************************************************************/
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_V9251_START_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
/* [cover parentID={DC0F3BD1-1815-492a-8B3D-D19A2DBC37C6}]
    MemMap file  [/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
    MemMap for variables  [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
    MemMap file  [/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
    MemMap for const  [/cover] */
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_V9251_MemMap.h"

[!SELECT "node:ref($CanTrcvConfigSetName)"!][!//
  [!VAR "TotalCanTrcvChannels" = "num:i(0)"!][!//
  [!LOOP "CanTrcvChannel/*"!][!//
    [!VAR "CanTrcvChUsed" = "./CanTrcvChannelUsed"!][!//
      [!IF "$CanTrcvChUsed = 'true'"!][!//
        [!VAR "TotalCanTrcvChannels" = "num:i($TotalCanTrcvChannels + num:i(1))"!][!//
      [!ENDIF!][!//
  [!ENDLOOP!][!//
  [!INDENT "0"!][!//
  /*[cover parentID={152B4BF1-9AF6-4cf8-B4D8-184F7B3C2E77}][/cover]*/
  [!CR!][!//
  const CanTrcv_17_V9251_ChannelInfoType
            CanTrcv_17_V9251_ChannelConfig[CANTRCV_17_V9251_CHANNELS_USED] =
  {
    [!INDENT "2"!][!//
    [!VAR "ChannelCount1" = "num:i(0)"!][!//
    [!LOOP "node:order(CanTrcvChannel/*, './CanTrcvChannelId')"!][!//
      [!VAR "CanTrcv_ChannelId" = "./CanTrcvChannelId"!]
      [!VAR "CanTrcvChUsed" = "./CanTrcvChannelUsed"!][!//
      [!IF "$CanTrcvChUsed = 'true'"!][!//
        [!VAR "ChannelCount1" = "num:i($ChannelCount1 + num:i(1))"!][!//
        /* CanTransceiver Channel [!"./CanTrcvChannelId "!] Specific Information */
        {
          [!INDENT "4"!][!//
          [!IF "./CanTrcvInitState = 'CANTRCV_17_V9251_OP_MODE_NORMAL'"!][!//
            CANTRCV_TRCVMODE_NORMAL,
          [!ELSEIF "./CanTrcvInitState = 'CANTRCV_17_V9251_OP_MODE_STANDBY'"!][!//
            CANTRCV_TRCVMODE_STANDBY,
          [!ENDIF!][!//
            [!IF "./CanTrcvWakeupByBusUsed = 'true'"!][!//
            [!IF "node:refexists(./CanTrcvWakeupSourceRef/*[1]) ='true'"!][!//
              [!"node:ref(./CanTrcvWakeupSourceRef/*[1])/EcuMWakeupSourceId"!]U,
            [!ELSE!][!//
              [!ERROR!][!//
                CanTrcv_17_V9251 Code Generator: In CanTransceiver Channel_[!"./CanTrcvChannelId "!],If CanTrcvWakeupByBusUsed parameter is enabled, then CanTrcvWakeupSourceRef parameter must be configured.
              [!ENDERROR!][!//
            [!ENDIF!]
          [!ELSE!][!//
            WAKEUP_SOURCE_NOT_CONFIGURED,
          [!ENDIF!][!//
          [!LOOP "./CanTrcvAccess/CanTrcvDioChannelAccess/*"!][!//
            [!IF "CanTrcvHardwareInterfaceName = 'STB'"!][!//
              [!VAR "DioChannelName" = "node:name(node:ref(CanTrcvDioSymNameRef))"!][!//
                DioConf_DioChannel_[!"$DioChannelName"!],
            [!ENDIF!][!//
          [!ENDLOOP!][!//
          [!IF "./CanTrcvInitState = 'CANTRCV_17_V9251_OP_MODE_NORMAL' "!][!//
            CANTRCV_17_V9251_NORMAL_MODE,
          [!ELSEIF "./CanTrcvInitState = 'CANTRCV_17_V9251_OP_MODE_STANDBY'"!][!//
            CANTRCV_17_V9251_STANDBY_MODE,
          [!ENDIF!][!//
          [!"num:i($CanTrcv_ChannelId)"!]U,
            [!IF "./CanTrcvWakeupByBusUsed = 'true'"!][!//
            TRUE
          [!ELSE!][!//
            FALSE
          [!ENDIF!][!//
          [!ENDINDENT!][!//
        }[!IF "$ChannelCount1 < num:i($TotalCanTrcvChannels)"!],[!CR!][!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
    [!CR!][!//
  };

  /*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
  naming convention, hence it goes beyond 32 characters.*/
  /*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
  naming convention, hence it goes beyond 32 characters.*/
  /*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
  naming convention, hence it goes beyond 32 characters.*/
  /*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
  naming convention, hence it goes beyond 32 characters.*/
  #define CANTRCV_17_V9251_STOP_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
  /* [cover parentID={DC0F3BD1-1815-492a-8B3D-D19A2DBC37C6}]
      MemMap file  [/cover] */
  /* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
      MemMap for variables  [/cover] */
  /* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
      MemMap file  [/cover] */
  /* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
      MemMap for const  [/cover] */
  /*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline. */
  /*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
  without safegaurd. It complies to Autosar guidelines. */
  #include "CanTrcv_17_V9251_MemMap.h"

  /*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
  naming convention, hence it goes beyond 32 characters.*/
  /*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
  naming convention, hence it goes beyond 32 characters.*/
  /*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
  naming convention, hence it goes beyond 32 characters.*/
  /*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
  naming convention, hence it goes beyond 32 characters.*/
  #define CANTRCV_17_V9251_START_SEC_CONFIG_DATA_QM_LOCAL_8
  /* [cover parentID={DC0F3BD1-1815-492a-8B3D-D19A2DBC37C6}]
      MemMap file  [/cover] */
  /* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
      MemMap for variables  [/cover] */
  /* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
      MemMap file  [/cover] */
  /* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
      MemMap for const  [/cover] */
  /* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline. */
  /* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
  without safegaurd. It complies to Autosar guidelines. */
  #include "CanTrcv_17_V9251_MemMap.h"

  /* CanTrcv_17_V9251_ChannelUsed array contains Channel Index of configured Channel
  - if ChannelIndex, is used
  - if 0XFF, is not used
  */
  /*[cover parentID={8CF0195E-4D53-4341-BD4A-BEBC304F1D80}][/cover]*/

  [!VAR "ChnnelMaxIndx" = "num:i(count(./CanTrcvChannel/*))"!][!//
  const uint8 CanTrcv_17_V9251_ChannelUsed[CANTRCV_17_V9251_CHANNELS_CFG] =
  {
    [!INDENT "2"!][!//
    [!VAR "Count1" = "num:i(0)"!][!//
    [!VAR "ChannelCount2" = "0"!][!//
    [!FOR "ChannelIndex" = "0" TO "$ChnnelMaxIndx - '1'"!][!//
      [!LOOP "CanTrcvChannel/*"!][!//
        [!VAR "CanTrcv_ChannelId" = "./CanTrcvChannelId"!][!//
        [!IF "$CanTrcv_ChannelId = $ChannelIndex"!][!//
          [!VAR "CanTrcvChUsed" = "./CanTrcvChannelUsed"!][!//
          [!IF "$Count1 > '0'"!],[!CR!][!ENDIF!][!//
          [!VAR "Count1" = "num:i($Count1+'1')"!][!//
          [!IF "$CanTrcvChUsed = 'true'"!][!//
            /* Index of CAN Transceiver Channel_[!"./CanTrcvChannelId "!] is used */
            [!"num:i($ChannelCount2)"!]U[!//
            [!VAR "ChannelCount2" = "$ChannelCount2 + 1"!][!//
          [!ELSE!][!//
            /* CAN Transceiver Channel_[!"./CanTrcvChannelId "!] is not used */
            0xFFU[!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDLOOP!][!//
    [!ENDFOR!][!//
    [!ENDINDENT!][!//
    [!CR!][!//
  };
  [!ENDINDENT!][!//
[!ENDSELECT!][!//
[!//

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_V9251_STOP_SEC_CONFIG_DATA_QM_LOCAL_8
/* [cover parentID={DC0F3BD1-1815-492a-8B3D-D19A2DBC37C6}]
    MemMap file  [/cover] */
/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
    MemMap for variables  [/cover] */
/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
    MemMap file  [/cover] */
/* [cover parentID={5713A17A-3FA1-427f-A0B6-89125A17689A}]
    MemMap for const  [/cover] */
 /*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
 guideline. */
 /*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
 without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_V9251_MemMap.h"
/*******************************************************************************
**                               End of File                                  **
*******************************************************************************/
[!ENDSELECT!]
