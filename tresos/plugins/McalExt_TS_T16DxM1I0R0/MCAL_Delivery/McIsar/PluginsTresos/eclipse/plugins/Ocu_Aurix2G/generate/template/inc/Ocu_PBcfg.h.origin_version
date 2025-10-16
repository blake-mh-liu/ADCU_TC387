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
**  FILENAME  : Ocu_PBcfg.h                                                   **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE      : 2020-04-23                                                    **
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
**  TRACEABILITY : [cover parentID={EE8433BB-9C52-47cc-A45A-959483047D32}]    **
**                                                                            **
**  DESCRIPTION  : OCU configuration generated out of ECUC file               **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) :Specification of OCU Driver,AUTOSAR Release 4.2.2&4.4.0 **
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
**  FILENAME  : Ocu_PBcfg.h                                                   **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]                !!!IGNORE-LINE!!!     **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]                  !!!IGNORE-LINE!!!       **
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
**  DESCRIPTION  : OCU configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) :Specification of OCU Driver,AUTOSAR Release 4.2.2&4.4.0 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef OCU_PBCFG_H
#define OCU_PBCFG_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**               Exported Configuration data structures                       **
*******************************************************************************/
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
#define OCU_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
   guideline.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Ocu_MemMap.h"
[!AUTOSPACING!] 
[!VAR "EcucModuleExist" = "num:i(0)"!][!//
[!SELECT "as:modconf('EcuC')[1]"!][!//
  [!IF "node:exists(EcucPostBuildVariants/*[1]/EcucPostBuildVariantRef/*[1])"!][!//
    [!VAR "EcucModuleExist" = "num:i(1)"!][!//
    [!LOOP "EcucPostBuildVariants/*[1]/EcucPostBuildVariantRef/*"!][!//
      [!VAR "Variantname"="''"!][!//
      [!VAR "Variantname" = "text:split(.,'/')[4]"!]
      [!WS"0"!]/* Extern declaration of O Config Root for [!"$Variantname"!] */
      [!WS"0"!]extern const Ocu_ConfigType Ocu_Config_[!"$Variantname"!];
    [!ENDLOOP!][!//
  [!ENDIF!][!//
[!ENDSELECT!][!//
[!IF "$EcucModuleExist = num:i(0)"!][!//
  /* Extern declaration of Ocu Config Root */
  extern const Ocu_ConfigType Ocu_Config;
[!ENDIF!][!//
/* MISRA2012_RULE_5_1_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_2_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_4_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION: External identifiers going beyond 32 chars.
   in generated code due to Autosar Naming constraints.*/
#define OCU_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
   guideline.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline. */
#include "Ocu_MemMap.h"
#endif  /* OCU_PBCFG_H */

