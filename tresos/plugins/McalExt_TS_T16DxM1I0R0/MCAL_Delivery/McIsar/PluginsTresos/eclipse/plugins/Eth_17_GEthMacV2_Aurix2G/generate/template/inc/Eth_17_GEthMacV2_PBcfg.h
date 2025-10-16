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
**  FILENAME  : Eth_17_GEthMacV2_PBcfg.h                                      **
**                                                                            **
**  VERSION   : 2.0.0                                                         **
**                                                                            **
**  DATE      : 2020-08-27                                                    **
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
**  TRACEABILITY : [cover parentID]                                           **
**                                                                            **
**  DESCRIPTION  : Code template header file for Eth Driver                   **
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
**  FILENAME  : Eth_17_GEthMacV2_PBcfg.h                                      **
**                                                                            **
**  VERSION   : 2.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]     !!!IGNORE-LINE!!!                    **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]        !!!IGNORE-LINE!!!                    **
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
[!/*
[cover parentID={E148FCEA-1429-405d-8F40-AFD6FDA05D64}][/cover]
*/!][!//

#ifndef ETH_17_GETHMACV2_PBCFG_H
#define ETH_17_GETHMACV2_PBCFG_H

/*******************************************************************************
**                      Global Const Declaration                              **
*******************************************************************************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
   guideline.*/
#include "Eth_17_GEthMacV2_MemMap.h"
/*
  Note: Elektrobit Automotive GmbH modified the original code provided
        by the third party supplier. The modification is provided for
        convenience.
        Please use the modification on your discretion and account, or
        use the unmodified files provided with this distribution. 
  Please see for the reasons in the file ImportantNotes.txt for tag

ASCINFINEON-1043 Update PostBuild generation 
*/
[!AUTOSPACING!]
[!INDENT "0"!][!//
  [!IF "var:defined('postBuildVariant')"!][!//
    [!LOOP "variant:all()"!]
      [!WS"0"!]/* Extern declaration of Eth Config Root for [!"."!] */
      [!WS"0"!]extern const Eth_17_GEthMacV2_ConfigType Eth_17_GEthMacV2_Config_[!"."!];
    [!ENDLOOP!][!//
  [!ELSE!][!//
    [!WS"0"!]/* Extern declaration of Eth Config Root */
    [!WS"0"!]extern const Eth_17_GEthMacV2_ConfigType Eth_17_GEthMacV2_Config;
  [!ENDIF!][!//
[!ENDINDENT!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
  in generated code due to Autosar Naming constraints.*/
#define ETH_17_GETHMACV2_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
   guideline.*/
#include "Eth_17_GEthMacV2_MemMap.h"
#endif  /* ETH_17_GETHMACV2_PBCFG_H */
