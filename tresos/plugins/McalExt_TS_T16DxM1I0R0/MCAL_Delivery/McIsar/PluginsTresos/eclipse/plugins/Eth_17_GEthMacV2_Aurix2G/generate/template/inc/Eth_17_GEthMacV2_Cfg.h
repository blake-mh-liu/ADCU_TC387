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
*******************************************************************************
**                                                                            **
**  FILENAME    : Eth_17_GEthMacV2_Cfg.h                                      **
**                                                                            **
**  VERSION     : 3.0.0                                                       **
**                                                                            **
**  DATE        : 2020-09-08                                                  **
**                                                                            **
**  BSW MODULE DECRIPTION : NA                                                **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR      : DL-AUTOSAR-Engineering                                      **
**                                                                            **
**  VENDOR      : Infineon Technologies                                       **
**                                                                            **
**  TRACEABILITY : [cover parentID={D714F172-661E-4f56-880A-F2FCEE3C8DEE}]    **
**                                                                            **
**  DESCRIPTION : This file contains                                          **
**                Code template for Eth_17_GEthMacV2_Cfg.h file               **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Eth Driver, AUTOSAR Release 4.4.0     **
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
**  FILENAME  : Eth_17_GEthMacV2_Cfg.h                                        **
**                                                                            **
**  VERSION   : 3.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]      !!!IGNORE-LINE!!!                   **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]          !!!IGNORE-LINE!!!                 **
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
**  DESCRIPTION  : Eth configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of Eth Driver, AUTOSAR Release 4.4.0     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/

#ifndef ETH_17_GETHMACV2_CFG_H
#define ETH_17_GETHMACV2_CFG_H
[!INDENT "0"!][!//
  [!NOCODE!]
    [!INCLUDE "Eth_17_GEthMacV2.m"!][!//
  [!ENDNOCODE!]
  /*******************************************************************************
  **                      Includes                                              **
  *******************************************************************************/

  /*******************************************************************************
  **                      Global Macro Definitions                              **
  *******************************************************************************/
  /*
    Note: Elektrobit Automotive GmbH modified the original code provided
        by the third party supplier. The modification is provided for
        convenience.
        Please use the modification on your discretion and account, or
        use the unmodified files provided with this distribution. 
  Please see for the reasons in the file ImportantNotes.txt for tag

  ASCINFINEON-983 : Autosar specification deviation in ETH driver. Removed v:lst from Eth.xdm.
  */
  
  [!NOCODE!][!//
  [!IF "not(node:exists(as:modconf('EthSwt')[1]))"!][!//
    [!WARNING!][!//
      EthSwt module is not added to the project.
    [!ENDWARNING!][!//
  [!ENDIF!][!//
  [!//
  [!ENDNOCODE!][!//

  [!/*
  [cover parentID={2EBBBDC5-44EF-430b-94AF-5D345F120E98}][/cover]
  */!][!//
  [!/*
  [cover parentID={A4FBFDA3-A996-4aa6-9038-8712621DB638}][/cover]
  */!][!//
  [!/*
  [cover parentID={EDD82081-F958-4dc5-8E6B-1678F0C19FF5}][/cover]
  */!][!//
  [!/*
  [cover parentID={7C00871A-B089-4df5-AB4D-6806043C7BD5}][/cover]
  */!][!//
  [!/*
  [cover parentID={A71D2417-14FE-4767-883C-5187B13CCEEE}][/cover]
  */!][!//
  [!/*
  [cover parentID={0C3A8F94-31D2-45aa-AF41-D863ED12B37E}][/cover]
  */!][!//
  [!AUTOSPACING!]
  [!VAR "MajorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 0]"!][!//
  [!VAR "MinorVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 1]"!][!//
  [!VAR "RevisionVersion" = "text:split($moduleReleaseVer, '.')[position()-1 = 2]"!][!//
  #define ETH_17_GETHMACV2_AR_RELEASE_MAJOR_VERSION      ([!"$MajorVersion"!]U)
  #define ETH_17_GETHMACV2_AR_RELEASE_MINOR_VERSION      ([!"$MinorVersion"!]U)
  #define ETH_17_GETHMACV2_AR_RELEASE_REVISION_VERSION   ([!"$RevisionVersion"!]U)

  [!VAR "SwMajorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 0]"!][!//
  [!VAR "SwMinorVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 1]"!][!//
  [!VAR "SwPatchVersion" = "text:split($moduleSoftwareVer, '.')[position()-1 = 2]"!][!//
  #define ETH_17_GETHMACV2_SW_MAJOR_VERSION              ([!"$SwMajorVersion"!]U)
  #define ETH_17_GETHMACV2_SW_MINOR_VERSION              ([!"$SwMinorVersion"!]U)
  #define ETH_17_GETHMACV2_SW_PATCH_VERSION              ([!"$SwPatchVersion"!]U)
  [!/* Select MODULE-CONFIGURATION as context-node */!][!//
  [!SELECT "as:modconf('Eth')[1]"!][!//
    [!//

    [!/*
    [cover parentID={8F1A8E0D-3C47-4a62-B746-697393C15A3D}][/cover]
    */!][!//
    /*
    Configuration: ETH_17_GETHMACV2_DEV_ERROR_DETECT
    - if STD_ON, Development error is Enabled
    - if STD_OFF,Development error is Disabled
       This parameter shall activate or deactivate the detection of all
       development errors.
    */
    #define ETH_17_GETHMACV2_DEV_ERROR_DETECT  ([!//
    [!IF "EthGeneral/EthDevErrorDetect = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )

    [!/*
    [cover parentID={F4F16757-E2B6-4d97-9C66-859B65590C60}][/cover]
    */!][!//
    /*
    Configuration: ETH_17_GETHMACV2_VERSION_INFO_API
    - if STD_ON, Function Eth_17_GEthMacV2_GetVersionInfo is available
    - if STD_OFF,Function Eth_17_GEthMacV2_GetVersionInfo is not available
    */
    #define ETH_17_GETHMACV2_VERSION_INFO_API  ([!//
    [!IF "EthGeneral/EthVersionInfoApi = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )

    [!/*
    [cover parentID={DB1C1CDB-64FE-4d53-AD0C-DEFD7565C39F}][/cover]
    */!][!//
    [!VAR "MaxControllers"= "ecu:get('Eth.EthAvaliableNodes')"!][!//
    [!FOR "ConfigId" = "num:i(0)" TO "num:i($MaxControllers) - num:i(1)"!][!//
      [!IF "node:exists(EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ConfigId)]) = 'true'"!][!//
        [!SELECT "EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ConfigId)]"!][!//
          /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
            in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
            in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
            in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
            in generated code due to Autosar Naming constraints.*/
          #ifndef Eth_17_GEthMacV2Conf_EthCtrlConfig_[!"node:name(.)"!]
          /* Macro to hold index of the configured controller */
          /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
            in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
            in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
            in generated code due to Autosar Naming constraints.*/
          /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
            in generated code due to Autosar Naming constraints.*/
          #define Eth_17_GEthMacV2Conf_EthCtrlConfig_[!"node:name(.)"!] ([!//
          [!"num:i(node:value(./EthCtrlIdx))"!]U)
          #endif
        [!ENDSELECT!][!//
      [!ENDIF!][!//
    [!ENDFOR!][!//

    [!/*
    [cover parentID={2FED7601-FA8C-4a72-9F03-311E65438017}][/cover]
    */!][!//
    /*
    Configuration: ETH_17_GETHMACV2_INDEX
    - Ethernet Driver Instance ID, used in DET  Interface.
    */
    #define ETH_17_GETHMACV2_INDEX ([!//
    [!"num:i(node:value(EthGeneral/EthIndex))"!]U)
    [!NOCODE!]
      [!VAR "TotalConfig" = "num:i(count(EthConfigSet))"!][!//
      [!VAR "EthCtrlEnableMiiApi" = "num:i(0)"!][!//
      [!VAR "EthCtrlEnableRxInterruptApi" = "num:i(0)"!][!//
      [!VAR "EthCtrlEnableTxInterruptApi" = "num:i(0)"!][!//
      [!FOR "ConfigId" = "num:i(1)" TO "num:i($TotalConfig)"!][!//
        [!SELECT "EthConfigSet"!][!//
          [!FOR "ControllerId" = "num:i(0)" TO "num:i($MaxControllers) - num:i(1)"!][!//
            [!IF "node:exists(EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]) = 'true'"!]
              [!SELECT "EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]"!][!//
                [!VAR "EthCtrlEnableMiiApiTemp1" = "./EthCtrlEnableMii"!][!//
                [!VAR "EthCtrlIndexTemp1" = "./EthCtrlIdx"!][!//
                [!IF "./EthCtrlEnableMii = 'true'"!][!//
                  [!VAR "EthCtrlEnableMiiApi" = "num:i(1)"!][!//
                [!ENDIF!][!//
                [!IF "./EthCtrlEnableRxInterrupt = 'true'"!][!//
                  [!VAR "EthCtrlEnableRxInterruptApi" = "num:i(1)"!][!//
                [!ENDIF!][!//
                [!IF "./EthCtrlEnableTxInterrupt = 'true'"!][!//
                  [!VAR "EthCtrlEnableTxInterruptApi" = "num:i(1)"!][!//
                [!ENDIF!][!//
                [!FOR "ControllerId1" = "num:i(0)" TO "num:i($MaxControllers)-num:i(1)"!][!//
                  [!IF "node:exists(../*[EthCtrlIdx = num:i($ControllerId1)]) = 'true'"!]
                    [!SELECT "../*[EthCtrlIdx = num:i($ControllerId1)]"!][!//
                      [!VAR "EthCtrlEnableMiiApiTemp2" = "./EthCtrlEnableMii"!][!//
                      [!VAR "EthCtrlIndexTemp2" = "./EthCtrlIdx"!][!//
                      [!IF "$EthCtrlIndexTemp2 != $EthCtrlIndexTemp1"!][!//
                        [!IF "$EthCtrlEnableMiiApiTemp2 != $EthCtrlEnableMiiApiTemp1"!][!//
                          [!ERROR!]
                            ERROR: Select or Unselect EthCtrlEnableMii parameter for all the controllers [!"@name"!].
                          [!ENDERROR!]
                        [!ENDIF!][!//
                      [!ENDIF!][!//
                    [!ENDSELECT!][!//
                  [!ENDIF!][!//
                [!ENDFOR!][!//
              [!ENDSELECT!][!//
            [!ENDIF!][!//
          [!ENDFOR!][!//
        [!ENDSELECT!][!//
      [!ENDFOR!][!//
    [!ENDNOCODE!]

    [!/*
    [cover parentID={E33744EC-EE25-433b-BF55-D6FCC05F7E9B}][/cover]
    */!][!//
    /*
    Configuration: ETH_17_GETHMACV2_ENA_MII_API
    - if STD_ON, Functions Eth_17_WriteMii,Eth_17_ReadMii are available
    - if STD_OFF,Functions Eth_17_WriteMii,Eth_17_ReadMii are not available
    */
    #define ETH_17_GETHMACV2_ENA_MII_API  ([!//
    [!IF "$EthCtrlEnableMiiApi = num:i(1)"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )

    [!/*
    [cover parentID={0DFC366F-DE96-4150-BCF8-FCD35B69E925}][/cover]
    */!][!//
    /*
    Configuration: ETH_17_GETHMACV2_RX_IRQHDLR
    - if STD_ON, the receive interrupt handler is available
    - if STD_OFF, the receive interrupt handler is not available
    */
    #define ETH_17_GETHMACV2_RX_IRQHDLR  ([!//
    [!IF "$EthCtrlEnableRxInterruptApi = num:i(1)"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )

    [!/*
    [cover parentID={23260AAC-4633-4f7e-80F0-D299B4DEAEF8}][/cover]
    */!][!//
    /*
    Configuration: ETH_17_GETHMACV2_TX_IRQHDLR
    - if STD_ON, the transmit interrupt handler is available
    - if STD_OFF, the transmit interrupt handler is not available
    */
    #define ETH_17_GETHMACV2_TX_IRQHDLR  ([!//
    [!IF "$EthCtrlEnableTxInterruptApi = num:i(1)"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )

    [!/*
    [cover parentID={7D09BF5A-4347-4dc5-B5CB-9F611EB8D33B}][/cover]
    */!][!//
    /* Maximum time in nanoseconds to wait for hardware timeout errors*/
    #define ETH_17_GETHMACV2_MAXTIMEOUT_COUNT  ([!//
    [!"num:i(node:value(EthGeneral/EthTimeoutCount))"!][!//
    U)

    [!/*
    [cover parentID={162DD36B-161F-4010-AF99-DF21BB567FB4}][/cover]
    */!][!//
    /*
      Configuration: ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT
    - if STD_ON, Ethernet switch management support is enabled
    - if STD_OFF, Ethernet switch management support is disabled
    */
    [!VAR "SwtMgmtSupport"= "num:i(0)"!][!//
    [!IF "not(node:exists(as:modconf('EthSwt')[1]))"!][!//
      #define ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT        (STD_OFF)
    [!ELSE!][!//
      [!SELECT "as:modconf('EthSwt')[1]"!][!//
        [!IF "EthSwtGeneral/EthSwtManagementSupportApi = 'false'"!][!//
          #define ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT        (STD_OFF)
        [!ELSE!][!//
          #define ETH_17_GETHMACV2_SWT_MANAGEMENT_SUPPORT        (STD_ON)
          [!VAR "SwtMgmtSupport"= "num:i(1)"!][!//
        [!ENDIF!][!//
      [!ENDSELECT!][!//
    [!ENDIF!][!//

    [!/*
    [cover parentID={549C220B-ABE3-4a67-BEF2-C49B3A7C75AE}][/cover]
    */!][!//
    [!/*
    [cover parentID={3EF492E8-E06E-4354-924E-6DF560544757}][/cover]
    */!][!//
    [!/*
    [cover parentID={C9756D6E-32C5-495b-9380-60B63982AA1E}][/cover]
    */!][!//
    [!VAR "TxBuffer"= "num:i(0)"!][!//
    [!VAR "RxBuffer"= "num:i(0)"!][!//
    [!VAR "TotalRxBufferSize"= "num:i(0)"!][!//
    [!SELECT "EthConfigSet"!][!//
      [!FOR "ControllerId" = "num:i(0)" TO "num:i($MaxControllers) - num:i(1)"!][!//
        [!IF "node:exists(EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]) = 'true'"!][!//
          [!SELECT "EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]"!][!//
            [!NOCODE!][!//
              /* Rx buffer memory is allocated as 8 byte aligned for optimal performance.
                 Total Rx memory allocated = Size of one buffer (8 byte aligned) * Number of buffers */
              [!FOR "IngressFifo" = "num:i(0)" TO "num:i(3)"!][!//
                [!IF "node:exists(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]) = 'true'"!][!//
                  [!VAR "EthCtrlConfigIngressFifoBufLenByteValue" = "EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoBufLenByte"!][!//
                  [!VAR "EthCtrlConfigIngressFifoBufTotalValue" = "EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoBufTotal"!][!//
                  [!VAR "RxBufQuotient" = "num:i($EthCtrlConfigIngressFifoBufLenByteValue) div 8"!][!//
                  [!IF "num:i($EthCtrlConfigIngressFifoBufLenByteValue) mod 8 != 0"!][!//
                    [!VAR "EthCtrlConfigIngressFifoBufLenByteValue" = "(num:i($RxBufQuotient) + 1) * 8"!][!//
                  [!ENDIF!]!][!//
                  [!VAR "RxBuffer" = "(string(num:i($EthCtrlConfigIngressFifoBufLenByteValue) * num:i($EthCtrlConfigIngressFifoBufTotalValue)))"!][!//
                  [!VAR "IngressFifoIdx" = "EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*[EthCtrlConfigIngressFifoIdx = ($IngressFifo)]/EthCtrlConfigIngressFifoIdx"!][!//
                  [!CODE!]
                    /* Rx buffer count and size for controller[!"./EthCtrlIdx"!] FIFO Index[!"num:i($IngressFifoIdx)"!] */
                    /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    #define ETH_17_GETHMACV2_FIFO[!"num:i($IngressFifoIdx)"!]_CTRL[!"./EthCtrlIdx"!]_RXBUF_COUNT      ([!"num:i($EthCtrlConfigIngressFifoBufTotalValue)"!]U)

                    /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    #define ETH_17_GETHMACV2_FIFO[!"num:i($IngressFifoIdx)"!]_CTRL[!"./EthCtrlIdx"!]_RXBUF_SIZE       ([!"string($RxBuffer)"!]U)
                  [!ENDCODE!][!CR!]
                [!ELSE!][!//
                  [!CODE!]
                    /* Rx buffer count and size for controller[!"./EthCtrlIdx"!] FIFO Index[!"num:i($IngressFifo)"!] */
                    /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    #define ETH_17_GETHMACV2_FIFO[!"num:i($IngressFifo)"!]_CTRL[!"./EthCtrlIdx"!]_RXBUF_COUNT      (0U)

                    /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    #define ETH_17_GETHMACV2_FIFO[!"num:i($IngressFifo)"!]_CTRL[!"./EthCtrlIdx"!]_RXBUF_SIZE       (0U)
                  [!ENDCODE!][!CR!]
                [!ENDIF!][!//
              [!ENDFOR!][!//
              [!CODE!][!//
              /* Number of Receive FIFOs configured */
              #define ETH_17_GETHMACV2_CTRL[!"./EthCtrlIdx"!]_RXFIFO_CFGD       ([!"num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*))"!]U)
              [!ENDCODE!][!CR!]
              /* If switch management support is enabled */
              [!IF "$SwtMgmtSupport = num:i(1)"!][!//
                [!IF "num:i(count(EthCtrlConfigIngress/EthCtrlConfigIngressFifo/*)) > num:i(1)"!][!//
                  [!ERROR!][!//
                    When switch management support functionality is enabled, only one ingress FIFO is supported. Configure only one ingress FIFO for controller [!"./EthCtrlIdx"!]
                  [!ENDERROR!][!//
                [!ENDIF!]!][!//
              [!ENDIF!]!][!//
              [!/*
              [cover parentID={DB957B57-6625-400d-94AC-A1024D3E7594}][/cover]
              */!][!//
              [!/*
              [cover parentID={DC211EC6-9475-411e-A9AB-1FB1CE4648BC}][/cover]
              */!][!//
              [!/*
              [cover parentID={5597D4B0-2EBF-43d5-B0C2-AE4AD8F767FE}][/cover]
              */!][!//
              [!/*
              [cover parentID={0176B556-D35A-4cc2-A3B7-95F77AF9C8E6}][/cover]
              */!][!//
              /* Tx buffer memory is allocated as 8 byte aligned for optimal performance.
               Total Tx memory allocated = Size of one 8 byte aligned buffer * Number of Buffers. */
              [!FOR "EgressFifo" = "num:i(0)" TO "num:i(3)"!][!//
                [!IF "node:exists(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[EthCtrlConfigEgressFifoIdx = ($EgressFifo)]) = 'true'"!][!//
                  [!VAR "EthCtrlConfigEgressFifoBufLenByteValue" = "EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[EthCtrlConfigEgressFifoIdx = ($EgressFifo)]/EthCtrlConfigEgressFifoBufLenByte"!][!//
                  [!VAR "EthCtrlConfigEgressFifoBufTotalValue" = "EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[EthCtrlConfigEgressFifoIdx = ($EgressFifo)]/EthCtrlConfigEgressFifoBufTotal"!][!//
                  [!IF "(num:i($EthCtrlConfigEgressFifoBufTotalValue) = num:i(0)) or (num:i($EthCtrlConfigEgressFifoBufLenByteValue) = num:i(0))"!][!//
                    [!ERROR!][!//
                      The egress FIFO buffer length and buffer size should not be zero for packets to be transmitted. If the egress FIFO is not required for transmission in any of the variant, delete the egress container having FIFO index [!"num:i($EgressFifo)"!] for controller [!"./EthCtrlIdx"!].
                    [!ENDERROR!][!//
                  [!ENDIF!]!][!//
                  [!IF "num:i($EthCtrlConfigEgressFifoBufLenByteValue) <= num:i(18)"!][!//
                    [!ERROR!][!//
                      The egress FIFO buffer length configured should be greater than 18 bytes as the length of 18 bytes are consumed by Header and FCFS fields of Ethernet packets. Modify accordingly the FIFO buffer length of egress FIFO having FIFO index [!"num:i($EgressFifo)"!] for controller [!"./EthCtrlIdx"!].
                    [!ENDERROR!][!//
                  [!ENDIF!]!][!//
                  [!VAR "TxBufQuotient" = "num:i($EthCtrlConfigEgressFifoBufLenByteValue) div 8"!][!//
                  [!IF "num:i($EthCtrlConfigEgressFifoBufLenByteValue) mod 8 != 0"!][!//
                    [!VAR "EthCtrlConfigEgressFifoBufLenByteValue" = "(num:i($TxBufQuotient) + 1) * 8"!][!//
                  [!ENDIF!]!][!//
                  [!VAR "TxBuffer" = "(string(num:i($EthCtrlConfigEgressFifoBufLenByteValue) * num:i($EthCtrlConfigEgressFifoBufTotalValue)))"!][!//
                  [!VAR "EgressFifoIdx" = "EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*[EthCtrlConfigEgressFifoIdx = ($EgressFifo)]/EthCtrlConfigEgressFifoIdx"!][!//
                  [!CODE!][!//
                    /* Tx buffer count and size for controller[!"./EthCtrlIdx"!] FIFO Index[!"num:i($EgressFifoIdx)"!] */
                    /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    #define ETH_17_GETHMACV2_FIFO[!"num:i($EgressFifoIdx)"!]_CTRL[!"./EthCtrlIdx"!]_TXBUF_COUNT      ([!"num:i($EthCtrlConfigEgressFifoBufTotalValue)"!]U)

                    /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    #define ETH_17_GETHMACV2_FIFO[!"num:i($EgressFifoIdx)"!]_CTRL[!"./EthCtrlIdx"!]_TXBUF_SIZE       ([!"string($TxBuffer)"!]U)
                  [!ENDCODE!][!CR!]
                [!ELSE!][!//
                  [!CODE!]
                    /* Tx buffer count and size for controller[!"./EthCtrlIdx"!] FIFO Index[!"num:i($EgressFifo)"!] */
                    /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    #define ETH_17_GETHMACV2_FIFO[!"num:i($EgressFifo)"!]_CTRL[!"./EthCtrlIdx"!]_TXBUF_COUNT      (0U)

                    /* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    /* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    /* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    /* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32
                    characters due to MIP added as per AUTOSAR requirement. Since compiler
                    supports more than 32 characters, no side effects seen. */
                    #define ETH_17_GETHMACV2_FIFO[!"num:i($EgressFifo)"!]_CTRL[!"./EthCtrlIdx"!]_TXBUF_SIZE       (0U)
                  [!ENDCODE!][!CR!]
                [!ENDIF!][!//
              [!ENDFOR!][!//
              [!CODE!][!//
              /* Number of Transmit FIFOs configured */
              #define ETH_17_GETHMACV2_CTRL[!"./EthCtrlIdx"!]_TXFIFO_CFGD       ([!"num:i(count(EthCtrlConfigEgress/EthCtrlConfigEgressFifo/*))"!]U)
              [!ENDCODE!][!//
            [!ENDNOCODE!][!//
            [!VAR "TxBuffer"= "num:i(0)"!][!//
            [!VAR "RxBuffer"= "num:i(0)"!][!//
            [!VAR "EthCtrlRxBufLenBytevalue"= "num:i(0)"!][!//
            [!VAR "EthCtrlTxBufLenBytevalue"= "num:i(0)"!][!//
            [!VAR "RxBufQuotient"= "num:i(0)"!][!//
            [!VAR "TxBufQuotient"= "num:i(0)"!][!//
            [!VAR "TotalRxBufferSize"= "num:i(0)"!][!//
          [!ENDSELECT!][!//
        [!ENDIF!][!//
      [!ENDFOR!][!//
    [!ENDSELECT!][!//

    [!VAR "EthPeripheralBusFrequency" = "num:i(node:ref(./EthGeneral/EthPeripheralBusClock)/McuPllDistributionSettingConfig/McuSPBFrequency)"!][!//
    [!/*
    [cover parentID={74DA9848-C58D-4885-9183-1DF22209B56F}][/cover]
    */!][!//
    /* fSPB (SPB frequency) period in nanoseconds */
    [!VAR "EthSpbPeriodInNanoSeconds" = "num:i((1000000000) div num:i($EthPeripheralBusFrequency))"!][!//
    #define ETH_17_GETHMACV2_FSPB_PERIOD_IN_NANOSEC   ([!"$EthSpbPeriodInNanoSeconds"!]U)

    [!/*
    [cover parentID={6BEF2F1C-494D-47cd-9C0B-E09DD325DB59}][/cover]
    */!][!//
    /* fGETH frequency in Hz - basic frequency for the Gigabit Ethernet Kernel */
    [!VAR "EthOperateFrequency" = "num:i(node:ref(./EthGeneral/EthOperationFrequency)/McuPllDistributionSettingConfig/McuGEthFrequency)"!][!//
    /* Timestamp Addend register value for fine update to get 20 ns
       resolution */
    [!VAR "EthAddendValue" = "num:i(num:f((4294967295) div num:f(num:i($EthOperateFrequency) div (50000000))))"!][!//
    #define ETH_17_GETHMACV2_TIMESTAMP_ADDEND_VAL     ([!"$EthAddendValue"!]U)

    [!/*
    [cover parentID={9ACA9304-33E3-4075-8B67-E8CD4838BD18}][/cover]
    */!][!//
    /* Wait time in nanoseconds after a kernel reset in RGMII mode */
    #define ETH_17_GETHMACV2_KRNLRST_RGMII_WAITCNT    ([!"num:i(ceiling(num:i(35) * ($EthSpbPeriodInNanoSeconds)))"!]U)

    [!/*
    [cover parentID={D46E826C-0B3F-4664-8282-803A4B129F7B}][/cover]
    */!][!//
    /* Wait time in nanoseconds after a kernel reset in MII/ RMII mode */
    #define ETH_17_GETHMACV2_KRNLRST_MII_WAITCNT      ([!"num:i(ceiling(num:i(70) * ($EthSpbPeriodInNanoSeconds)))"!]U)

    [!/*
    [cover parentID={24F25B5E-2E2E-4e2a-8C05-C4708DD49FAE}][/cover]
    */!][!//
    /* Number of fSPB cycles to wait after a DMA software reset */
    #define ETH_17_GETHMACV2_DMA_RESET_WAITCYCLE      ([!"EthGeneral/EthDmaSwResetWaitCycle"!]U)

    [!/*
    [cover parentID={591CF9C1-285A-495e-892B-35580C83C13B}][/cover]
    */!][!//
    /*
    Configuration: ETH_17_GETHMACV2_GETCNTRVALUES_API
    - if STD_ON, Function Eth_17_GEthMacV2_GetCounterValues is available
    - if STD_OFF,Function Eth_17_GEthMacV2_GetCounterValues is not available
    */
    [!IF "EthGeneral/EthGetDropCountApi = 'true'"!][!//
      #define  ETH_17_GETHMACV2_GETCNTRVALUES_API    (STD_ON)
    [!ELSE!][!//
      #define  ETH_17_GETHMACV2_GETCNTRVALUES_API    (STD_OFF)
    [!ENDIF!][!//

    [!/*
    [cover parentID={B198ADE2-BD1A-44f3-B90D-AD7F5985DAAD}][/cover]
    */!][!//
    /*
    Configuration: ETH_17_GETHMACV2_GETRXSTATS_API
    - if STD_ON, Function Eth_17_GEthMacV2_GetRxStats is available
    - if STD_OFF,Function Eth_17_GEthMacV2_GetRxStats is not available
    */
    [!IF "EthGeneral/EthGetEtherStatsApi   = 'true'"!][!//
      #define  ETH_17_GETHMACV2_GETRXSTATS_API   (STD_ON)
    [!ELSE!][!//
      #define  ETH_17_GETHMACV2_GETRXSTATS_API   (STD_OFF)
    [!ENDIF!][!//

    [!/*
    [cover parentID={5B4CD9DB-BC7C-45c4-AF5D-F5CAF1670799}][/cover]
    */!][!//
    /*
    Configuration: ETH_17_GETHMACV2_GETTXSTATS_API
    - if STD_ON, Eth_17_GEthMacV2_GetTxStats() API is available
    - if STD_OFF, Eth_17_GEthMacV2_GetTxStats() API is unavailable
    */
    [!IF "EthGeneral/EthGetTxStatsApi = 'true'"!][!//
      #define  ETH_17_GETHMACV2_GETTXSTATS_API   (STD_ON)
    [!ELSE!][!//
      #define  ETH_17_GETHMACV2_GETTXSTATS_API   (STD_OFF)
    [!ENDIF!][!//

    [!/*
    [cover parentID={65D0C112-02DD-474a-8E6F-BF7888D2E770}][/cover]
    */!][!//
    /*
    Configuration: ETH_17_GETHMACV2_GETTXERRCNTRVAL_API
    - if STD_ON, Eth_17_GEthMacV2_GetTxErrorCounterValues() API is available
    - if STD_OFF, Eth_17_GEthMacV2_GetTxErrorCounterValues() API is unavailable
    */
    [!IF "EthGeneral/EthGetTxErrorCounterValuesApi = 'true'"!][!//
      #define  ETH_17_GETHMACV2_GETTXERRCNTRVAL_API   (STD_ON)
    [!ELSE!][!//
      #define  ETH_17_GETHMACV2_GETTXERRCNTRVAL_API   (STD_OFF)
    [!ENDIF!][!//

    [!/*
    [cover parentID={BCAE163A-10CE-4f2f-B1D5-734765577EB5}][/cover]
    */!][!//
    /*
    Configuration: ETH_17_GETHMACV2_GLOBALTIMESUPPORT
    - if STD_ON, TimeStamp feature is enabled.
    - if STD_OFF,TimeStamp feature is disabled.
    */
    [!IF "EthGeneral/EthGlobalTimeSupport   = 'true'"!][!//
      #define  ETH_17_GETHMACV2_GLOBALTIMESUPPORT   (STD_ON)
    [!ELSE!][!//
      #define  ETH_17_GETHMACV2_GLOBALTIMESUPPORT   (STD_OFF)
    [!ENDIF!][!//

    [!/*
    [cover parentID={DC16EDD7-C347-4327-AB00-C3F2F4E6CCEF}][/cover]
    */!][!//
    /*
      Configuration: ETH_17_GETHMACV2_MULTICORE_ERROR_DETECT :
      Adds/removes the Multi-core error detection and reporting
      from the code
      - if STD_ON, Multi-core error detection and reporting is enabled
      - if STD_OFF, Multi-core error detection and reporting is disabled
    */
    [!IF "EthGeneral/EthMultiCoreErrorDetect   = 'true'"!][!//
      #define ETH_17_GETHMACV2_MULTICORE_ERROR_DETECT           (STD_ON)
    [!ELSE!][!//
      #define ETH_17_GETHMACV2_MULTICORE_ERROR_DETECT           (STD_OFF)
    [!ENDIF!][!//

    [!/*
    [cover parentID={B08F60B3-BAF3-42b4-9581-82C576763C9F}][/cover]
    */!][!//
    /*
      Configuration: ETH_17_GETHMACV2_ICMP_CHECKSUMOFFLOAD_ENABLE
      - if STD_ON, Hardware offloading for ICMP checksums is enabled.
      - if STD_OFF,Hardware offloading for ICMP checksums is disabled.
    */
    [!IF "EthGeneral/EthCtrlOffloading/EthCtrlEnableOffloadChecksumICMP   = 'true'"!][!//
      #define ETH_17_GETHMACV2_ICMP_CHECKSUMOFFLOAD_ENABLE  (STD_ON)
    [!ELSE!][!//
      #define ETH_17_GETHMACV2_ICMP_CHECKSUMOFFLOAD_ENABLE  (STD_OFF)
    [!ENDIF!][!//

    [!/*
    [cover parentID={6E445804-E669-449e-A472-36D714658B95}][/cover]
    */!][!//
    /*
      Configuration: ETH_17_GETHMACV2_IPV4_CHECKSUMOFFLOAD_ENABLE
      - if STD_ON, Hardware offloading for IPV4 checksums is enabled.
      - if STD_OFF,Hardware offloading for IPV4 checksums is disabled.
    */
    [!IF "EthGeneral/EthCtrlOffloading/EthCtrlEnableOffloadChecksumIPv4     = 'true'"!][!//
      #define ETH_17_GETHMACV2_IPV4_CHECKSUMOFFLOAD_ENABLE  (STD_ON)
    [!ELSE!][!//
      #define ETH_17_GETHMACV2_IPV4_CHECKSUMOFFLOAD_ENABLE  (STD_OFF)
    [!ENDIF!][!//

    [!/*
    [cover parentID={4EFF89FB-242E-4393-A55D-3B1116E1C571}][/cover]
    */!][!//
    /*
      Configuration: ETH_17_GETHMACV2_TCP_CHECKSUMOFFLOAD_ENABLE
      - if STD_ON, Hardware offloading for TCP checksums is enabled.
      - if STD_OFF,Hardware offloading for TCP checksums is disabled.
    */
    [!IF "EthGeneral/EthCtrlOffloading/EthCtrlEnableOffloadChecksumTCP     = 'true'"!][!//
      #define ETH_17_GETHMACV2_TCP_CHECKSUMOFFLOAD_ENABLE   (STD_ON)
    [!ELSE!][!//
      #define ETH_17_GETHMACV2_TCP_CHECKSUMOFFLOAD_ENABLE   (STD_OFF)
    [!ENDIF!][!//

    [!/*
    [cover parentID={1842E374-E2AB-4843-B1CD-A0E7D5424E7B}][/cover]
    */!][!//
    /*
      Configuration: ETH_17_GETHMACV2_UDP_CHECKSUMOFFLOAD_ENABLE
      - if STD_ON, Hardware offloading for UDP checksums is enabled.
      - if STD_OFF,Hardware offloading for UDP checksums is disabled.
    */
    [!IF "EthGeneral/EthCtrlOffloading/EthCtrlEnableOffloadChecksumUDP   = 'true'"!][!//
      #define ETH_17_GETHMACV2_UDP_CHECKSUMOFFLOAD_ENABLE   (STD_ON)
    [!ELSE!][!//
      #define ETH_17_GETHMACV2_UDP_CHECKSUMOFFLOAD_ENABLE   (STD_OFF)
    [!ENDIF!][!//

    [!/*
    [cover parentID={C69E45F0-5927-47d3-A114-3494F21585D1}] ETH_17_INIT_API_MODE
    [/cover]
    */!][!//
    /*
      Configuration: ETH_17_GETHMACV2_INIT_API_MODE
      - if ETH_17_GETHMACV2_MCAL_SUPERVISOR - Init API is executed in supervisor mode.
      - if ETH_17_GETHMACV2_MCAL_USER1 - Init API is executed in user1 mode.
    */
    [!IF "EthGeneral/EthInitApiMode = 'ETH_MCAL_SUPERVISOR'"!][!//
      #define ETH_17_GETHMACV2_INIT_API_MODE         (ETH_17_GETHMACV2_MCAL_SUPERVISOR)
    [!ELSE!][!//
      #define ETH_17_GETHMACV2_INIT_API_MODE         (ETH_17_GETHMACV2_MCAL_USER1)
    [!ENDIF!][!//

    [!/*
    [cover parentID={31D49AB3-67D6-4efa-81F1-447E516EDD1B}] ETH_17_RUNTIME_API_MODE
    [/cover]
    */!][!//
    /*
    Configuration: ETH_17_GETHMACV2_RUNTIME_API_MODE
    - if ETH_17_GETHMACV2_MCAL_SUPERVISOR - Runtime APIs are executed in supervisor mode.
    - if ETH_17_GETHMACV2_MCAL_USER1 - Runtime APIs are executed in user1 mode.
    */
    [!IF "EthGeneral/EthRuntimeApiMode = 'ETH_MCAL_SUPERVISOR'"!][!//
      #define ETH_17_GETHMACV2_RUNTIME_API_MODE      (ETH_17_GETHMACV2_MCAL_SUPERVISOR)
    [!ELSE!][!//
      #define ETH_17_GETHMACV2_RUNTIME_API_MODE      (ETH_17_GETHMACV2_MCAL_USER1)
    [!ENDIF!][!//

    [!CALL "ETH_GenerateModuleMap", "Module" = "'ETH'"!][!//
    [!FOR "CoreId" = "num:i(0)" TO "num:i(6) - num:i(1)"!][!//
      [!VAR "MaxControllersCore" = "num:i(255)"!][!//
      [!VAR "TempCoreId" = "concat('CORE',$CoreId)"!][!//
      [!CALL "ETH_GetMasterCoreID"!][!//
      [!IF "(text:contains( text:split($CGAllocatedCores,','), $TempCoreId)) or ($CGMasterCoreId = $TempCoreId) or ($CoreId < ecu:get('Mcu.NoOfCoreAvailable'))"!][!//
        [!VAR "MaxControllersCore" = "num:i(0)"!][!//
        [!FOR "ControllerID" = "num:i(0)" TO "num:i($MaxControllers) - num:i(1)"!][!//
          [!IF "node:exists(EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]) = 'true'"!][!//
            [!SELECT "EthConfigSet/EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerID)]"!][!//
              [!VAR "NodeName" = "node:name(.)"!][!//
              [!VAR "EthCtrlIdx" = "./EthCtrlIdx"!][!//
              [!CALL "ETH_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
              [!IF "$CGAllocationResult = 'TRUE'"!][!//
                [!VAR "MaxControllersCore" = "$MaxControllersCore + num:i(1)"!][!//
                /* Controller[!"$EthCtrlIdx"!] is configured to [!"$TempCoreId"!] */
                [!/*
                [cover parentID={A01F2CC7-136C-4c80-8D65-B43AF91EBF48}][/cover]
                */!][!//
                #define ETH_17_GETHMACV2_CTRL[!"$EthCtrlIdx"!]_[!"$TempCoreId"!]  (STD_ON)

                /* Controller[!"$EthCtrlIdx"!] is configured in this project */
                [!/*
                [cover parentID={29CB1246-DC71-4e38-8780-9E422CF93B82}][/cover]
                */!][!//
                #define ETH_17_GETHMACV2_CTRL[!"$EthCtrlIdx"!]_CONFIGURED         (STD_ON)

              [!ENDIF!][!//
            [!ENDSELECT!][!//
          [!ENDIF!][!//
        [!ENDFOR!][!//
      [!ENDIF!][!//
      /* Maximum Controllers allocated to [!"$TempCoreId"!]
      Value = 255- represents core is not available in current device */
      [!/*
      [cover parentID={1486D73E-46AB-4e8c-9EB5-8449A49F7337}][/cover]
      */!][!//
      #define ETH_17_GETHMACV2_MAX_CTRL_[!"$TempCoreId"!]               ([!"num:i($MaxControllersCore)"!]U)

    [!ENDFOR!][!//
    /* Maximum available cores in this device */
    [!/*
    [cover parentID={3C0B10DE-0284-4232-ADDF-556DFC03CC04}][/cover]
    */!][!//
    #define ETH_17_GETHMACV2_MAX_CORES                     ([!"ecu:get('Mcu.NoOfCoreAvailable')"!]U)

    /* Maximum controllers available in this device */
    [!/*
    [cover parentID={84F947A2-2182-4d72-82CF-63A8F065A5FF}][/cover]
    */!][!//
    #define ETH_17_GETHMACV2_MAX_CONTROLLERS               ([!"ecu:get('Eth.EthAvaliableNodes')"!]U)

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
    **                      Global Inline Function Definitions                    **
    *******************************************************************************/

    #endif  /* ETH_17_GETHMACV2_CFG_H */

  [!ENDSELECT!][!//
[!ENDINDENT!][!//

