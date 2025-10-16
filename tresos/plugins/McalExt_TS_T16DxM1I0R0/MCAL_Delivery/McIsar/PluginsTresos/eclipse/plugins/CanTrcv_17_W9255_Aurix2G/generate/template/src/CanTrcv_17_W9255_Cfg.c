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
**  FILENAME  : CanTrcv_17_W9255_Cfg.c                                        **
**                                                                            **
**  VERSION   : 6.0.0                                                         **
**                                                                            **
**  DATE      : 2020-08-10                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : CanTrcv_17_W9255.bmd                              **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={BDD474F6-F430-4146-ADE0-D54A95B83B25}]    **
**                 [cover parentID={B22F34A4-4DDC-4a5c-8B4F-A4822EC9B363}]    **
**                                                                            **
**  DESCRIPTION  : Code template source file for CanTrcv_17_W9255 Driver      **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of CanTrcv Driver, AUTOSAR Release 4.2.2 **
**                                                  and AUTOSAR Release 4.4.0 **
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
**  FILENAME  : CanTrcv_17_W9255_Cfg.c                                        **
**                                                                            **
**  VERSION   : 6.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]       !!!IGNORE-LINE!!!                  **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]           !!!IGNORE-LINE!!!                **
**                                                                            **
**  BSW MODULE DECRIPTION : CanTrcv_17_W9255.bmd                              **
**                                                                            **
**  VARIANT   : Variant PC                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : CanTrcv_17_W9255 configuration generated out of ECUC file  **
**                                                                            **
**  SPECIFICATION(S) : Specification of CanTrcv Driver, AUTOSAR Release 4.2.2 **
**                                                  and AUTOSAR Release 4.4.0 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Includes                                       **
*******************************************************************************/
[!AUTOSPACING!]
[!/*[cover parentID={E2878637-D6D2-412e-A4CA-141FDE5BCC00}] File Structure
[/cover]*/!][!//
/* Include CanTrcv header file */
#include "CanTrcv_17_W9255.h"
[!NOCODE!][!//
  [!/*[cover parentID={3BE34470-088E-49cd-933E-15FB7B40AC81}]
  Imported Interfaces [/cover]*/!][!//
  [!IF "not(node:exists(as:modconf('Spi')[1]))"!]
    [!ERROR!][!//
      CanTrcv_17_W9255 Code Generator: Spi module is not added to the project.
    [!ENDERROR!][!//
  [!ENDIF!]
  [!IF "not(node:exists(as:modconf('EcuM')[1]))"!]
    [!ERROR!][!//
      CanTrcv_17_W9255 Code Generator: EcuM module is not added to the project.
    [!ENDERROR!][!//
  [!ENDIF!]
  [!IF "not(node:exists(as:modconf('Icu')[1]))"!]
    [!ERROR!][!//
      CanTrcv_17_W9255 Code Generator: Icu module is not added to the project.
    [!ENDERROR!][!//
  [!ENDIF!]
[!ENDNOCODE!][!//
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "(as:stod( 'AURIX2G_W9255/EcucDefs/CanTrcv'))"!][!//
[!VAR "MaxChannels" = "num:i(255)"!][!//
[!VAR "CanTrcvConfigSetName" = "'CanTrcvConfigSet'"!][!//
/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define CANTRCV_17_W9255_START_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
[!/* [cover parentID={03C90BFA-850A-4b3e-9D6E-51E503B46FE9}]
    MemMap file  [/cover] */!][!//
[!/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
    MemMap for variables  [/cover] */!][!//
[!/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
    MemMap file  [/cover] */!][!//
[!CR!][!//
/*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
guideline. */
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
without safegaurd. It complies to Autosar guidelines. */
#include "CanTrcv_17_W9255_MemMap.h"
[!SELECT "node:ref($CanTrcvConfigSetName)"!][!//
  [!INDENT "0"!][!//
  [!VAR "NumChannel" = "num:i($MaxChannels)"!][!//
  [!VAR "TotalCanTrcvChannels" = "num:i(0)"!][!//
  [!LOOP "node:order(CanTrcvChannel/*, './CanTrcvChannelId')"!][!//
    [!VAR "CanTrcvChUsed" = "./CanTrcvChannelUsed"!][!//
    [!IF "$CanTrcvChUsed = 'true'"!][!//
      [!VAR "TotalCanTrcvChannels" = "num:i($TotalCanTrcvChannels + num:i(1))"!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
  [!CR!][!//
  [!/* [cover parentID={F26A356C-6BD2-4838-AD5C-45FBCED3AEF5}] [/cover] */!][!//
  const CanTrcv_17_W9255_ChannelConfigType CanTrcv_17_W9255_ChannelConfig[CANTRCV_17_W9255_CHANNELS_USED] =
  {
    [!INDENT "2"!][!//
    [!VAR "ChannelCount1" = "num:i(0)"!][!//
    [!LOOP "node:order(CanTrcvChannel/*, './CanTrcvChannelId')"!][!//
      [!VAR "CanTrcv_ChannelId" = "./CanTrcvChannelId"!][!//
      [!VAR "CanTrcvChUsed" = "./CanTrcvChannelUsed"!][!//
        [!IF "$CanTrcvChUsed = 'true'"!][!//
          [!VAR "ChannelCount1" = "num:i($ChannelCount1 + num:i(1))"!][!//
          /* CanTransceiver Channel [!"./CanTrcvChannelId "!] Specific Information */
          {
            [!INDENT "4"!][!//
            /* CAN Transceiver state after driver initialization */
            [!IF "./CanTrcvInitState = 'CANTRCV_17_W9255_OP_MODE_NORMAL'"!][!//
              /* Command to write to MODE_CTRL register when the requested mode is NORMAL */
              0x8108U,
            [!ELSEIF "./CanTrcvInitState = 'CANTRCV_17_W9255_OP_MODE_SLEEP'"!][!//
              /* Command to write to MODE_CTRL register when the requested mode is SLEEP */
              0x8101U,
            [!ELSEIF "./CanTrcvInitState = 'CANTRCV_17_W9255_OP_MODE_STANDBY'"!][!//
              /* Command to write to MODE_CTRL register when the requested mode is STANDBY */
              0x8102U,
            [!ENDIF!][!//
            [!CR!][!//
            /* CanTrcvWakeupSource reference */
            [!IF "./CanTrcvWakeupByBusUsed = 'true'"!][!//
/*
              Note: Elektrobit Automotive GmbH modified the original code provided
        by the third party supplier. The modification is provided for
        convenience.
        Please use the modification on your discretion and account, or
        use the unmodified files provided with this distribution. 
  Please see for the reasons in the file ImportantNotes.txt for tag

												 
	ASCINFINEON-849 CanTrcvWakeupSourceRef parameter should not be present as a list because it is not readable by CanIf	  
*/ 
              [!IF "node:refexists(./CanTrcvWakeupSourceRef) ='true'"!][!//
                [!"node:ref(./CanTrcvWakeupSourceRef)/EcuMWakeupSourceId"!]U,
              [!ELSE!][!//
                [!ERROR!][!//
                  CanTrcv_17_W9255 Code Generator: Configure wakeup source reference for the channel [!"./CanTrcvChannelId "!]
                [!ENDERROR!][!//
              [!ENDIF!][!//
            [!ELSE!][!//
              CANTRCV_17_W9255_WAKEUP_SOURCE_NOT_CONFIGURED,
            [!ENDIF!][!//
            [!CR!][!//
            /* CanTrcvPorWakeupSource reference */
            [!IF "node:refexists(./CanTrcvPorWakeupSourceRef/*[1]) ='true'"!][!//
              [!"node:ref(./CanTrcvPorWakeupSourceRef/*[1])/EcuMWakeupSourceId"!]U,
            [!ELSE!][!//
              CANTRCV_17_W9255_WAKEUP_SOURCE_NOT_CONFIGURED,
            [!ENDIF!][!//
            [!CR!][!//
            /* CanTrcvSyserrWakeupSource reference */
            [!IF "node:refexists(./CanTrcvSyserrWakeupSourceRef/*[1]) ='true'"!][!//
              [!"node:ref(./CanTrcvSyserrWakeupSourceRef/*[1])/EcuMWakeupSourceId"!]U,
            [!ELSE!][!//
              CANTRCV_17_W9255_WAKEUP_SOURCE_NOT_CONFIGURED,
            [!ENDIF!][!//
            [!CR!][!//
            /* CAN Transceiver Channel Id */
            [!"num:i($CanTrcv_ChannelId)"!]U,
            [!CR!][!//
            /* Sequence Id used */
            [!"node:ref(./CanTrcvAccess/CanTrcvSpiSequence/*/CanTrcvSpiSequenceName/*[1])/SpiSequenceId"!]U,
            [!CR!][!//
            /* Spi Channel Id used */
            [!IF "(node:refexists(./CanTrcvAccess/CanTrcvSpiSequence/*/CanTrcvSpiSequenceName/*[1]))"!][!//
              [!"node:ref(node:ref(node:ref(./CanTrcvAccess/CanTrcvSpiSequence/*/CanTrcvSpiSequenceName/*[1])/SpiJobAssignment/*[1])/SpiChannelList/*[1]/SpiChannelAssignment)/SpiChannelId"!]U,
            [!ENDIF!][!//
            [!CR!][!//
            /*
            Wake up by bus status
            - if STD_ON, Bus is used
            - if STD_OFF, Bus is not used
            */
            [!IF "./CanTrcvWakeupByBusUsed = 'true'"!][!//
              STD_ON
            [!ELSE!][!//
              STD_OFF
            [!ENDIF!][!//
          [!ENDINDENT!][!//
        }[!IF "$ChannelCount1 < num:i($TotalCanTrcvChannels)"!],[!ENDIF!][!CR!]
      [!ENDIF!][!//
    [!ENDLOOP!]
    [!ENDINDENT!][!//
  };
  [!CR!][!//
  /*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
  naming convention, hence it goes beyond 32 characters.*/
  /*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
  naming convention, hence it goes beyond 32 characters.*/
  /*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
  naming convention, hence it goes beyond 32 characters.*/
  /*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
  naming convention, hence it goes beyond 32 characters.*/
  #define CANTRCV_17_W9255_STOP_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
  [!/* [cover parentID={03C90BFA-850A-4b3e-9D6E-51E503B46FE9}]
      MemMap file  [/cover] */!][!//
  [!/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
      MemMap for variables  [/cover] */!][!//
  [!/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
      MemMap file  [/cover] */!][!//
  [!CR!][!//
  /*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline. */
  /*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
  without safegaurd. It complies to Autosar guidelines. */
  #include "CanTrcv_17_W9255_MemMap.h"
  [!CR!][!//
  /*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
  naming convention, hence it goes beyond 32 characters.*/
  /*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
  naming convention, hence it goes beyond 32 characters.*/
  /*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
  naming convention, hence it goes beyond 32 characters.*/
  /*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
  naming convention, hence it goes beyond 32 characters.*/
  #define CANTRCV_17_W9255_START_SEC_CONFIG_DATA_QM_LOCAL_8
  [!/* [cover parentID={03C90BFA-850A-4b3e-9D6E-51E503B46FE9}]
      MemMap file  [/cover] */!][!//
  [!/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
      MemMap for variables  [/cover] */!][!//
  [!CR!][!//
  [!/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
      MemMap file  [/cover] */!][!//
  /*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline. */
  /*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
  without safegaurd. It complies to Autosar guidelines. */
  #include "CanTrcv_17_W9255_MemMap.h"
  [!CR!][!//
  /* The following array gives information about the Channel state.
  - if the Channel is enabled, the array member holds the Channel inex
  - if the Channel is disabled, the array member holds value 0XFF
  */
  [!VAR "ChnnelMaxIndx" = "num:i(count(./CanTrcvChannel/*))"!][!//
  [!/* [cover parentID={56BD7232-F5CA-4816-8101-97A2428D393D}] [/cover] */!][!//
  const uint8 CanTrcv_17_W9255_ChannelUsed[CANTRCV_17_W9255_CHANNELS_CONFIGURED] =
  {
    [!INDENT "2"!][!//
    [!VAR "Count1" = "num:i(0)"!][!//
    [!VAR "ChannelCount2" = "0"!][!//
    [!FOR "ChannelIndex" = "0" TO "$ChnnelMaxIndx - '1'"!][!//
      [!LOOP "CanTrcvChannel/*"!][!//
        [!VAR "CanTrcv_ChannelId" = "./CanTrcvChannelId"!][!//
        [!IF "$CanTrcv_ChannelId = $ChannelIndex"!][!//
          [!VAR "CanTrcvChUsed" = "./CanTrcvChannelUsed"!][!//
          [!IF "$Count1 > '0'"!][!//
          ,
          [!ENDIF!][!//
          [!VAR "Count1" = "num:i($Count1+'1')"!][!//
          [!IF "$CanTrcvChUsed = 'true'"!][!//
            /* CAN Transceiver Channel Id [!"./CanTrcvChannelId "!] is used */
            [!"num:i($ChannelCount2)"!]U[!//
            [!VAR "ChannelCount2" = "$ChannelCount2 + 1"!][!//
          [!ELSE!][!//
            /* CAN Transceiver Channel Id [!"./CanTrcvChannelId "!] is not used */
            0xFFU[!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDLOOP!][!//
    [!ENDFOR!][!//
    [!ENDINDENT!][!//
    [!CR!]
  };
  [!CR!]
  /* The following array gives information about the PN state.
  - if PN is enabled for the Channel, the array member holds the Channel index
  - if PN is disabled for the Channel, the array member holds value 0XFF
  */
  [!VAR "ChnnelMaxIndx" = "num:i(count(./CanTrcvChannel/*))"!][!//
  [!/* [cover parentID={96ACCBBD-6F6E-4319-AD58-FA8C278B8BC7}] [/cover] */!][!//
  const uint8 CanTrcv_17_W9255_PnConfigured[CANTRCV_17_W9255_CHANNELS_CONFIGURED] =
  {
    [!INDENT "2"!][!//
    [!VAR "Count1" = "num:i(0)"!][!//
    [!VAR "ChannelCount2" = "0"!][!//
    [!FOR "ChannelIndex" = "0" TO "$ChnnelMaxIndx - '1'"!][!//
      [!LOOP "CanTrcvChannel/*"!][!//
        [!VAR "CanTrcv_ChannelId" = "./CanTrcvChannelId"!][!//
        [!IF "$CanTrcv_ChannelId = $ChannelIndex"!][!//
          [!VAR "CanTrcvChUsed" = "./CanTrcvChannelUsed"!][!//
          [!IF "$Count1 > '0'"!][!//
            ,
          [!ENDIF!][!//
          [!VAR "Count1" = "num:i($Count1+'1')"!][!//
          [!IF "$CanTrcvChUsed = 'true'"!][!//
            [!IF "node:exists(./CanTrcvPartialNetwork/*[1])"!][!//
              [!VAR "CanTrcvPnEnabled" = "./CanTrcvPartialNetwork/*[1]/CanTrcvPnEnabled"!][!//
              [!IF "$CanTrcvPnEnabled = 'true'"!][!//
                /* PN for CAN Transceiver Channel Id [!"./CanTrcvChannelId "!] is configured */
                [!"num:i($ChannelCount2)"!]U[!//
                [!VAR "ChannelCount2" = "$ChannelCount2 + 1"!][!//
              [!ELSE!][!//
                /* PN for CAN Transceiver Channel Id [!"./CanTrcvChannelId "!] is not configured */
                0xFFU[!//
              [!ENDIF!][!//
            [!ELSE!][!//
              /* PN for CAN Transceiver Channel Id [!"./CanTrcvChannelId "!] is not configured */
              0xFFU[!//
            [!ENDIF!][!//
          [!ELSE!][!//
            /* PN for CAN Transceiver Channel Id [!"./CanTrcvChannelId "!] is not configured */
            0xFFU[!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDLOOP!][!//
    [!ENDFOR!][!//
    [!ENDINDENT!][!//
    [!CR!]
  };
  [!CR!][!//
  /*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
  naming convention, hence it goes beyond 32 characters.*/
  /*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
  naming convention, hence it goes beyond 32 characters.*/
  /*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
  naming convention, hence it goes beyond 32 characters.*/
  /*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
  naming convention, hence it goes beyond 32 characters.*/
  #define CANTRCV_17_W9255_STOP_SEC_CONFIG_DATA_QM_LOCAL_8
  [!/* [cover parentID={03C90BFA-850A-4b3e-9D6E-51E503B46FE9}]
      MemMap file  [/cover] */!][!//
  [!/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
      MemMap for variables  [/cover] */!][!//
  [!CR!][!//
  [!/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
      MemMap file  [/cover] */!][!//
  /*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
  guideline. */
  /*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
  without safegaurd. It complies to Autosar guidelines. */
  #include "CanTrcv_17_W9255_MemMap.h"
  [!CR!][!//
  [!IF "$ChannelCount2 >= num:i(1)"!][!//
    /*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
    naming convention, hence it goes beyond 32 characters.*/
    /*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
    naming convention, hence it goes beyond 32 characters.*/
    /*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
    naming convention, hence it goes beyond 32 characters.*/
    /*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
    naming convention, hence it goes beyond 32 characters.*/
    #define CANTRCV_17_W9255_START_SEC_CONFIG_DATA_QM_LOCAL_16
    [!/* [cover parentID={03C90BFA-850A-4b3e-9D6E-51E503B46FE9}]
        MemMap file  [/cover] */!][!//
    [!/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
        MemMap for variables  [/cover] */!][!//
    [!CR!][!//
    [!/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
        MemMap file  [/cover] */!][!//
    /*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
    guideline. */
    /*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
    without safegaurd. It complies to Autosar guidelines. */
    #include "CanTrcv_17_W9255_MemMap.h"
    [!CR!]
    /* Each command consists of 2 bytes out of which the Bits 0-7 represent data
    and bits 8-15 represent address of the respective register */
    [!CR!][!//
    [!VAR "ChannelCount1" = "num:i(0)"!][!//
    [!LOOP "node:order(CanTrcvChannel/*, './CanTrcvChannelId')"!][!//
      [!VAR "CanTrcvChUsed" = "./CanTrcvChannelUsed"!][!//
      [!IF "$CanTrcvChUsed = 'true'"!][!//
        [!VAR "ChannelCount1" = "num:i($ChannelCount1 + num:i(1))"!][!//
        [!IF "node:exists(./CanTrcvPartialNetwork/*[1])"!]
          [!IF "./CanTrcvPartialNetwork/*[1]/CanTrcvPnEnabled = 'true' "!][!//
            /* PN configuration commands(Baudrate, CAN Id, CAN Id mask and DLC) of CAN Transceiver Channel Id [!"./CanTrcvChannelId "!] */
            [!/* [cover parentID={C13851CB-A8FE-4766-AE71-92907FD7A134}] [/cover] */!][!//
            static const uint16 CanTrcv_17_W9255_Ch[!"./CanTrcvChannelId "!]PnIdInfo[] =
            {
              [!INDENT "2"!][!//
              /* Baud rate of the WUF */
              [!VAR "CanTrcv_Baudrate" ="node:value(./CanTrcvPartialNetwork/*[1]/CanTrcvBaudRate)"!][!//
              [!IF "$CanTrcv_Baudrate = num:i(125)"!][!//
                /* Command to write to SWK_CTRL_2 register with PN enabled, BR ratio 10 and Baud of 125kbps */
                0x8692U,
              [!ELSEIF "$CanTrcv_Baudrate = num:i(250)"!][!//
                /* Command to write to SWK_CTRL_2 register with PN enabled, BR ratio 10 and Baud of 250kbps */
                0x8693U,
              [!ELSEIF "$CanTrcv_Baudrate = num:i(500)"!][!//
                /* Command to write to SWK_CTRL_2 register with PN enabled, BR ratio 10 and Baud of 500kbps */
                0x8694U,
              [!ELSE!][!//
                /* Command to write to SWK_CTRL_2 register with PN enabled, BR ratio 10 and Baud of 1Mbps */
                0x8695U,
              [!ENDIF!][!//
              [!CR!][!//
              /* CAN ID of the WUF */
              [!VAR "CanTrcv_Pn_Frame_Can_Id" ="node:value(./CanTrcvPartialNetwork/*[1]/CanTrcvPnFrameCanId)"!][!//
              [!IF "./CanTrcvPartialNetwork/*[1]/CanTrcvPnCanIdIsExtended = 'true' "!][!//
                [!VAR "CanId" = "num:i(0)"!][!//
                [!FOR "j" = "0" TO "3"!][!//
                  [!VAR "Element" = "bit:and($CanTrcv_Pn_Frame_Can_Id,num:i(255))"!][!//
                  [!IF "$j=3"!][!//
                    [!VAR "Element" = "bit:or($Element, num:i(32))"!][!//
                  [!ENDIF!][!//
                  [!IF "$j!=0"!][!//
                    [!VAR "CanId" = "concat($CanId,',',$Element)"!][!//
                  [!ELSE!][!//
                    [!VAR "CanId" = "$Element"!][!//
                  [!ENDIF!][!//
                  [!VAR "CanTrcv_Pn_Frame_Can_Id" = "bit:shr($CanTrcv_Pn_Frame_Can_Id, num:i(8))"!][!//
                [!ENDFOR!][!//
                [!VAR "RegAddr" = "num:i(35328)"!][!//
                [!VAR "OffsetAddr" = "num:i(256)"!][!//
                [!FOR "j" = "1" TO "4"!][!//
                  [!VAR "IndVal" = "text:split($CanId,',')[position() = $j]"!][!//
                  [!VAR "Intval" = "num:i($IndVal)"!][!//
                  [!VAR "Intval" = "bit:or($Intval, $RegAddr)"!][!//
                  [!VAR "Intval" = "num:inttohex($Intval)"!][!//
                  /* Command to write CAN ID to SWK_ID[!"num:i($j - num:i(1))"!]_CTRL register */
                  [!"$Intval"!]U,
                  [!VAR "RegAddr" = "num:i($RegAddr - $OffsetAddr)"!][!//
                [!ENDFOR!][!//
              [!ELSE!][!//
                [!VAR "ID0" = "bit:shl(bit:and($CanTrcv_Pn_Frame_Can_Id, num:i(63)), num:i(2))"!][!//
                [!VAR "ID1" = "bit:and(bit:shr($CanTrcv_Pn_Frame_Can_Id, num:i(6)), num:i(31))"!][!//
                [!VAR "CanId" = "concat(num:i(0),',',num:i(0),',',$ID0,',',$ID1)"!][!//
                [!VAR "RegAddr" = "num:i(35328)"!][!//
                [!VAR "OffsetAddr" = "num:i(256)"!][!//
                [!FOR "j" = "1" TO "4"!][!//
                  [!VAR "IndVal" = "text:split($CanId,',')[position() = $j]"!][!//
                  [!VAR "Intval" = "num:i($IndVal)"!][!//
                  [!VAR "Intval" = "bit:or($Intval, $RegAddr)"!][!//
                  [!VAR "Intval" = "num:inttohex($Intval)"!][!//
                  /* Command to write CAN ID to SWK_ID[!"num:i($j - num:i(1))"!]_CTRL register */
                  [!"$Intval"!]U,
                  [!VAR "RegAddr" = "num:i($RegAddr - $OffsetAddr)"!][!//
                [!ENDFOR!][!//
              [!ENDIF!][!//
              [!CR!][!//
              /* CAN ID Mask of the WUF */
              [!VAR "CanTrcv_Pn_Frame_Can_Id_Mask" ="node:value(./CanTrcvPartialNetwork/*[1]/CanTrcvPnFrameCanIdMask)"!][!//
              [!IF "./CanTrcvPartialNetwork/*[1]/CanTrcvPnCanIdIsExtended = 'true' "!][!//
                [!VAR "IdMask" = "num:i(0)"!][!//
                [!FOR "j" = "0" TO "3"!][!//
                  [!VAR "Element" = "bit:and($CanTrcv_Pn_Frame_Can_Id_Mask,num:i(255))"!][!//
                  [!IF "$j!=0"!][!//
                    [!VAR "IdMask" = "concat($IdMask,',',$Element)"!][!//
                  [!ELSE!][!//
                    [!VAR "IdMask" = "$Element"!][!//
                  [!ENDIF!][!//
                  [!VAR "CanTrcv_Pn_Frame_Can_Id_Mask" = "bit:shr($CanTrcv_Pn_Frame_Can_Id_Mask, num:i(8))"!][!//
                [!ENDFOR!][!//
                [!VAR "RegAddr" = "num:i(36352)"!][!//
                [!VAR "OffsetAddr" = "num:i(256)"!][!//
                [!FOR "j" = "1" TO "4"!][!//
                  [!VAR "IndVal" = "text:split($IdMask,',')[position() = $j]"!][!//
                  [!VAR "Intval" = "num:i($IndVal)"!][!//
                  [!VAR "Intval" = "bit:or($Intval, $RegAddr)"!][!//
                  [!VAR "Intval" = "num:inttohex($Intval)"!][!//
                  /* Command to write CAN Id mask to SWK_MASK_ID[!"num:i($j - num:i(1))"!]_CTRL register */
                  [!"$Intval"!]U,
                  [!VAR "RegAddr" = "num:i($RegAddr - $OffsetAddr)"!][!//
                [!ENDFOR!][!//
              [!ELSE!][!//
                [!VAR "IDMaks0" = "bit:shl(bit:and($CanTrcv_Pn_Frame_Can_Id_Mask, num:i(63)), num:i(2))"!][!//
                [!VAR "IDMask1" = "bit:and(bit:shr($CanTrcv_Pn_Frame_Can_Id_Mask, num:i(6)), num:i(31))"!][!//
                [!VAR "IdMask" = "concat(num:i(0),',',num:i(0),',',$IDMaks0,',',$IDMask1)"!][!//
                [!VAR "RegAddr" = "num:i(36352)"!][!//
                [!VAR "OffsetAddr" = "num:i(256)"!][!//
                [!FOR "j" = "1" TO "4"!][!//
                  [!VAR "IndVal" = "text:split($IdMask,',')[position() = $j]"!][!//
                  [!VAR "Intval" = "num:i($IndVal)"!][!//
                  [!VAR "Intval" = "bit:or($Intval, $RegAddr)"!][!//
                  [!VAR "Intval" = "num:inttohex($Intval)"!][!//
                  /* Command to write CAN Id mask to SWK_MASK_ID[!"num:i($j - num:i(1))"!]_CTRL register */
                  [!"$Intval"!]U,
                  [!VAR "RegAddr" = "num:i($RegAddr - $OffsetAddr)"!][!//
                [!ENDFOR!][!//
              [!ENDIF!][!//
              [!CR!][!//
              /* Data Length Code of the WUF */
              [!VAR "CanTrcv_Pn_Frame_Dlc" ="node:value(./CanTrcvPartialNetwork/*[1]/CanTrcvPnFrameDlc)"!][!//
              [!VAR "DlcAddr" = "num:i(36608)"!][!//
              [!VAR "CanTrcv_Pn_Frame_Dlc" = "bit:or($CanTrcv_Pn_Frame_Dlc,$DlcAddr)"!][!//
              [!VAR "CanTrcv_Pn_Frame_Dlc" = "num:inttohex($CanTrcv_Pn_Frame_Dlc)"!][!//
              [!"$CanTrcv_Pn_Frame_Dlc"!]U
              [!ENDINDENT!][!//
            };
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!CR!][!//
    [!VAR "ChannelCount1" = "num:i(0)"!][!//
    [!LOOP "node:order(CanTrcvChannel/*, './CanTrcvChannelId')"!][!//
      [!VAR "CanTrcvChUsed" = "./CanTrcvChannelUsed"!][!//
      [!IF "$CanTrcvChUsed = 'true'"!][!//
        [!VAR "ChannelCount1" = "num:i($ChannelCount1 + num:i(1))"!][!//
        [!IF "node:exists(./CanTrcvPartialNetwork/*[1])"!][!//
          [!IF "./CanTrcvPartialNetwork/*[1]/CanTrcvPnEnabled = 'true' "!][!//
            /* PN data mask configuration of CAN Transceiver Channel Id [!"./CanTrcvChannelId "!] */
            [!/* [cover parentID={9B0D784B-0ACC-43ba-BD39-5C8722A018AA}] [/cover] */!][!//
            static const uint16 CanTrcv_17_W9255_Ch[!"./CanTrcvChannelId "!]PnDataInfo[] =
            {
              [!INDENT "2"!][!//
              [!VAR "PnIndexCount" = "num:i(count(./CanTrcvPartialNetwork/*[1]/CanTrcvPnFrameDataMaskSpec/*))"!][!//
              [!VAR "CanTrcv_Pn_Frame_Dlc" ="node:value(./CanTrcvPartialNetwork/*[1]/CanTrcvPnFrameDlc)"!][!//
              [!IF "$PnIndexCount != $CanTrcv_Pn_Frame_Dlc"!][!//
                [!ERROR!][!//
                  CanTrcv_17_W9255 Code Generator: Configure data mask for the remaining valid indices of channel [!"./CanTrcvChannelId "!] in CanTrcvPnFrameDataMaskSpec container
                [!ENDERROR!][!//
              [!ENDIF!][!//
              [!VAR "loopcount" = "num:i(0)"!][!//
              [!VAR "DataAddr" = "num:i(0)"!][!//
              [!LOOP "./CanTrcvPartialNetwork/*[1]/CanTrcvPnFrameDataMaskSpec/*"!][!//
                [!VAR "loopcount" = "num:i($loopcount + num:i(1))"!][!//
                [!VAR "CanTrcv_Pn_Frame_Data_Mask" ="node:value(./CanTrcvPnFrameDataMask)"!][!//
                [!VAR "Can_Trcv_Pn_Frame_Data_Mask_Index" ="node:value(./CanTrcvPnFrameDataMaskIndex)"!][!//
                [!VAR "Data0CtrlAddr" = "num:i(38656)"!][!//
                [!VAR "OffsetAddr" = "num:i(256)"!][!//
                [!VAR "DataMaskAddr" = "num:i($Data0CtrlAddr - num:i($Can_Trcv_Pn_Frame_Data_Mask_Index * $OffsetAddr))"!][!//
                [!VAR "Data" = "bit:or($DataMaskAddr,$CanTrcv_Pn_Frame_Data_Mask)"!][!//
                [!VAR "Data" = "num:inttohex($Data)"!][!//
                /* Command to write Data mask to SWK_DATA[!"num:i($Can_Trcv_Pn_Frame_Data_Mask_Index)"!]_CTRL register */
                [!"$Data"!]U[!IF "$loopcount < num:i($CanTrcv_Pn_Frame_Dlc)"!],[!ENDIF!][!CR!]
                [!IF "$loopcount!=1"!][!//
                  [!VAR "DataAddr" = "concat($DataAddr,',',$Data)"!][!//
                [!ELSE!][!//
                  [!VAR "DataAddr" = "$Data"!][!//
                [!ENDIF!][!//
              [!ENDLOOP!][!//
              [!ENDINDENT!][!//
            };
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!CR!]
    /*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
    naming convention, hence it goes beyond 32 characters.*/
    /*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
    naming convention, hence it goes beyond 32 characters.*/
    /*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
    naming convention, hence it goes beyond 32 characters.*/
    /*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
    naming convention, hence it goes beyond 32 characters.*/
    #define CANTRCV_17_W9255_STOP_SEC_CONFIG_DATA_QM_LOCAL_16
    [!/* [cover parentID={03C90BFA-850A-4b3e-9D6E-51E503B46FE9}]
        MemMap file  [/cover] */!][!//
    [!/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
        MemMap for variables  [/cover] */!][!//
    [!/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
        MemMap file  [/cover] */!][!//
    [!CR!][!//
    /*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
    guideline. */
    /*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
    without safegaurd. It complies to Autosar guidelines. */
    #include "CanTrcv_17_W9255_MemMap.h"
    /*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
    naming convention, hence it goes beyond 32 characters.*/
    /*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
    naming convention, hence it goes beyond 32 characters.*/
    /*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
    naming convention, hence it goes beyond 32 characters.*/
    /*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
    naming convention, hence it goes beyond 32 characters.*/
    #define CANTRCV_17_W9255_START_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
    [!/* [cover parentID={03C90BFA-850A-4b3e-9D6E-51E503B46FE9}]
        MemMap file  [/cover] */!][!//
    [!/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
        MemMap for variables  [/cover] */!][!//
    [!/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
        MemMap file  [/cover] */!][!//
    [!CR!][!//
    /*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
    guideline. */
    /*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
    without safegaurd. It complies to Autosar guidelines. */
    #include "CanTrcv_17_W9255_MemMap.h"
    [!CR!][!//
    /*MISRA2012_RULE_8_9_JUSTIFICATION: The variable CanTrcv_17_W9255_PNConfig cannot
    be declared at block scope as it is generated from the configuration in the
    configuration files and is used by the Init API of the driver. */
    [!/* [cover parentID={9EB3F1BD-AAFF-4e4d-A63C-1532D44F2668}] [/cover] */!][!//
    const CanTrcv_17_W9255_PNConfigType CanTrcv_17_W9255_PNConfig[CANTRCV_17_W9255_PN_CONFIGURED_CHANNELS] =
    {
      [!INDENT "2"!][!//
      [!VAR "ChannelCount1" = "num:i(0)"!][!//
      [!VAR "PnCount" = "num:i(0)"!][!//
      [!LOOP "node:order(CanTrcvChannel/*, './CanTrcvChannelId')"!][!//
        [!VAR "CanTrcvChUsed" = "./CanTrcvChannelUsed"!][!//
        [!IF "$CanTrcvChUsed = 'true'"!][!//
          [!VAR "ChannelCount1" = "num:i($ChannelCount1 + num:i(1))"!][!//
          [!IF "node:exists(./CanTrcvPartialNetwork/*[1])"!]
            [!IF "./CanTrcvPartialNetwork/*[1]/CanTrcvPnEnabled = 'true' "!][!//
              [!VAR "PnCount" = "num:i($PnCount + num:i(1))"!][!//
              /* PN configuration of CAN Transceiver Channel Id [!"./CanTrcvChannelId "!] */
              {
                [!INDENT "4"!][!//
                /* Pointer to baudrate, Id, Id mask of the PN frame */
                CanTrcv_17_W9255_Ch[!"./CanTrcvChannelId "!]PnIdInfo,
                [!CR!][!//
                /* Pointer to data masks of the PN frame */
                CanTrcv_17_W9255_Ch[!"./CanTrcvChannelId "!]PnDataInfo,
                [!CR!][!//
                /* Data Length Code of the WUF */
                [!VAR "CanTrcv_Pn_Frame_Dlc" ="node:value(./CanTrcvPartialNetwork/*[1]/CanTrcvPnFrameDlc)"!][!//
                [!"$CanTrcv_Pn_Frame_Dlc"!]U
                [!ENDINDENT!][!//
              }[!IF "$PnCount < num:i($ChannelCount2)"!],[!ENDIF!][!CR!]
            [!ENDIF!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDLOOP!]
      [!ENDINDENT!][!//
    };
    [!CR!]
    /*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
    naming convention, hence it goes beyond 32 characters.*/
    /*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
    naming convention, hence it goes beyond 32 characters.*/
    /*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
    naming convention, hence it goes beyond 32 characters.*/
    /*MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
    naming convention, hence it goes beyond 32 characters.*/
    #define CANTRCV_17_W9255_STOP_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
    [!CR!]
    [!/* [cover parentID={03C90BFA-850A-4b3e-9D6E-51E503B46FE9}]
        MemMap file  [/cover] */!][!//
    [!/* [cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
        MemMap for variables  [/cover] */!][!//
    [!/* [cover parentID={EA0715EE-3E3C-4aac-A42E-4B5CFC96CEED}]
        MemMap file  [/cover] */!][!//
    /*MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
    guideline. */
    /*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
    without safegaurd. It complies to Autosar guidelines. */
    #include "CanTrcv_17_W9255_MemMap.h"
  [!ENDIF!][!//
  [!ENDINDENT!][!//
[!ENDSELECT!][!//
[!ENDSELECT!][!//