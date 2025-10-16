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
**  FILENAME  : Uart_PBcfg.h                                                  **
**                                                                            **
**  VERSION   : 7.0.0                                                         **
**                                                                            **
**  DATE      : 2020-04-30                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Uart.bmd                                          **
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
**  DESCRIPTION  : Code template header file for Uart Driver                  **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) :Specification of Uart Driver, AUTOSAR Release 4.2.2 and **
**                                                   AUTOSAR Release 4.4.0    **
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
**  FILENAME  : Uart_PBcfg.h                                                  **
**                                                                            **
**  VERSION   : 7.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]  !!!IGNORE-LINE!!!                   **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]      !!!IGNORE-LINE!!!                   **
**                                                                            **
**  BSW MODULE DECRIPTION : Uart.bmd                                          **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Uart configuration generated out of ECUC file              **
**                                                                            **
**  SPECIFICATION(S) :Specification of Uart Driver, AUTOSAR Release 4.2.2 and **
**                                                  AUTOSAR Release 4.4.0     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
/* [cover parentID={040BB356-FE7A-4301-ADD6-EB5BE12C0AE7}]
[/cover] */
#ifndef UART_PBCFG_H
#define UART_PBCFG_H
/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
#define UART_START_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
/* [cover parentID={84FCEDA9-01F7-4f48-AC8B-47FFAF8417E4}] */
/*  [/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Uart_MemMap.h"
[!AUTOSPACING!]
[!INDENT "0"!]
  [!VAR "EcucModuleExist" = "num:i(0)"!][!//
  [!SELECT "as:modconf('EcuC')[1]"!][!//
    [!IF "node:exists(EcucPostBuildVariants/*[1]/EcucPostBuildVariantRef/*[1])"!][!//
      [!VAR "EcucModuleExist" = "num:i(1)"!][!//
      [!LOOP "EcucPostBuildVariants/*[1]/EcucPostBuildVariantRef/*"!][!//
        [!VAR "Variantname"="''"!][!//
        [!VAR "Variantname" = "text:split(.,'/')[4]"!]
        [!WS"0"!]/* Extern declaration of Uart Config Root for [!"$Variantname"!] */
        [!WS"0"!]extern const Uart_ConfigType Uart_Config_[!"$Variantname"!];
      [!ENDLOOP!][!//
    [!ENDIF!][!//
  [!ENDSELECT!][!//
  [!IF "$EcucModuleExist = num:i(0)"!][!//
  /* Extern declaration of Uart Config Root */
  extern const Uart_ConfigType Uart_Config;
  [!ENDIF!][!//
[!ENDINDENT!]
#define UART_STOP_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED
/* [cover parentID={84FCEDA9-01F7-4f48-AC8B-47FFAF8417E4}] */
/*  [/cover] */
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "Uart_MemMap.h"
#endif

