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
**  FILENAME  : Dsadc_PBcfg.h                                                 **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE      : 2021-02-24                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Dsadc.bmd                                         **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={6DA91FAF-84B3-4210-BF06-7F8E149AD442}]    **
**                                                                            **
**  DESCRIPTION  : Code template header file for Dsadc Driver                 **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of Dsadc Driver, AUTOSAR Release 4.2.2   **
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
**  FILENAME  : Dsadc_PBcfg.h                                                 **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]         !!!IGNORE-LINE!!!                **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]           !!!IGNORE-LINE!!!                **
**                                                                            **
**  BSW MODULE DECRIPTION : Dsadc.bmd                                         **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Dsadc configuration generated out of ECUC file             **
**                                                                            **
**  SPECIFICATION(S) : Specification of Dsadc Driver, AUTOSAR Release 4.2.2   **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef DSADC_PBCFG_H
#define DSADC_PBCFG_H

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

[!/*[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]Configuration Memory section as per AS [/cover] */!][!//
#define DSADC_START_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
   guideline.*/
#include "Dsadc_MemMap.h"
[!AUTOSPACING!]
[!VAR "EcucModuleExist" = "num:i(0)"!][!//
[!SELECT "as:modconf('EcuC')[1]"!][!//
  [!IF "node:exists(EcucPostBuildVariants/*[1]/EcucPostBuildVariantRef/*[1])"!][!//
    [!VAR "EcucModuleExist" = "num:i(1)"!][!//
    [!LOOP "EcucPostBuildVariants/*[1]/EcucPostBuildVariantRef/*"!][!//
      [!VAR "Variantname"="''"!][!//
      [!VAR "Variantname" = "text:split(.,'/')[4]"!]
      [!WS"0"!]/* Extern declaration of DSADC Config Root for [!"$Variantname"!] */
      [!WS"0"!]extern const Dsadc_ConfigType Dsadc_Config_[!"$Variantname"!];
    [!ENDLOOP!][!//
  [!ENDIF!][!//
[!ENDSELECT!][!//
[!IF "$EcucModuleExist = num:i(0)"!][!//
/* Extern declaration of DSADC Config Root */
extern const Dsadc_ConfigType Dsadc_Config;
[!ENDIF!][!//
#define DSADC_STOP_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
   guideline.*/
#include "Dsadc_MemMap.h"
#endif  /* DSADC_PBCFG_H */

