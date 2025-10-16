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
**  FILENAME  : Mcu_PBcfg.h                                                   **
**                                                                            **
**  VERSION   : 8.0.0                                                         **
**                                                                            **
**  DATE      : 2021-02-22                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Mcu.bmd                                           **
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
**  DESCRIPTION  : Code template header file for Mcu Driver                   **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of MCU Driver, AUTOSAR Release 4.2.2     **
**                     and 4.4.0                                              **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*************************************************************************/!][!//
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
********************************************************************************
**                                                                            **
**  FILENAME  : Mcu_PBcfg.h                                                   **
**                                                                            **
**  VERSION   : 8.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]           !!!IGNORE-LINE!!!              **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]               !!!IGNORE-LINE!!!            **
**                                                                            **
**  BSW MODULE DECRIPTION : Mcu.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Mcu configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of MCU Driver, AUTOSAR Release 4.2.2     **
**                     and 4.4.0                                              **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef MCU_PBCFG_H
#define MCU_PBCFG_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
[!/*[cover parentID={71734164-4DD8-4041-9D63-74BE20AD502A}][/cover]*/!][!//
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
#define MCU_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
   guideline.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
/*
  Note: Elektrobit Automotive GmbH modified the original code provided
        by the third party supplier. The modification is provided for
        convenience.
        Please use the modification on your discretion and account, or
        use the unmodified files provided with this distribution. 
  Please see for the reasons in the file ImportantNotes.txt for tag

ASCINFINEON-1043 Update PostBuild generation 
*/
#include "Mcu_MemMap.h"
[!AUTOSPACING!]
  [!IF "var:defined('postBuildVariant')"!][!//
    [!LOOP "variant:all()"!]
      [!WS"0"!]/* Extern declaration of Mcu Config Root for [!"."!] */
      [!WS"0"!]extern const Mcu_ConfigType Mcu_Config_[!"."!];
    [!ENDLOOP!]
  [!ELSE!][!//
    [!WS"0"!]/* Extern declaration of Mcu Config Root */
    [!WS"0"!]extern const Mcu_ConfigType Mcu_Config;
  [!ENDIF!][!//
#define MCU_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
   guideline.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Mcu_MemMap.h"

#endif  /* MCU_PBCFG_H */

