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
**  FILENAME  : Dma_PBcfg.h                                                   **
**                                                                            **
**  VERSION   : 6.0.0                                                         **
**                                                                            **
**  DATE      : 2019-11-11                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Dma.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={A74D6386-06E7-4a3a-AF51-DCD116B7AC8C}]    **
**                                                                            **
**  DESCRIPTION  : Code template header file for Dma Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of DMA Driver, AUTOSAR Release 4.2.2     **
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
**  FILENAME  : Dma_PBcfg.h                                                   **
**                                                                            **
**  VERSION   : 6.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]             !!!IGNORE-LINE!!!            **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]               !!!IGNORE-LINE!!!            **
**                                                                            **
**  BSW MODULE DECRIPTION : Dma.bmd                                           **
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
**  SPECIFICATION(S) : Specification of DMA Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef DMA_PBCFG_H
#define DMA_PBCFG_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Dma.h"

/*
  Note: Elektrobit Automotive GmbH modified the original code provided
        by the third party supplier. The modification is provided for
        convenience.
        Please use the modification on your discretion and account, or
        use the unmodified files provided with this distribution. 
  Please see for the reasons in the file ImportantNotes.txt for tag

ASCINFINEON-1043 Update PostBuild generation 
*/
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
#define DMA_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
   guideline.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Dma_MemMap.h"
[!AUTOSPACING!]
[!INDENT "0"!][!//
  [!IF "var:defined('postBuildVariant')"!][!//
    [!LOOP "variant:all()"!]
      [!WS"0"!]/* Extern declaration of Dma Config Root for [!"."!] */
      [!WS"0"!]extern const Dma_ConfigType Dma_Config_[!"."!];
    [!ENDLOOP!]
  [!ELSE!][!//
    [!WS"0"!]/* Extern declaration of Dma Config Root */
    [!WS"0"!]extern const Dma_ConfigType Dma_Config;
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
#define DMA_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
   guideline.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Dma_MemMap.h"
#endif  /* DMA_PBCFG_H */


