[!AUTOSPACING!]
[!INDENT "0"!]
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
**  FILENAME  : Port_PBcfg.h                                                  **
**                                                                            **
**  VERSION   : 9.0.0                                                         **
**                                                                            **
**  DATE      : 2020-11-11                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Port.bmd                                          **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY :[cover parentID={05ED3531-8A13-4e8f-B1A9-E14A6CBEA2D1}]     **                             
**                                                                            **                                                                            
**  DESCRIPTION  : Code template header file for Port Driver                  **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of PORT Driver, AUTOSAR Release 4.2.2    **
**                     and AUTOSAR Release 4.4.0                              **
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
**  FILENAME  : Port_PBcfg.h                                                  **
**                                                                            **
**  VERSION   : 9.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]           !!!IGNORE-LINE!!!              **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]              !!!IGNORE-LINE!!!             **
**                                                                            **
**  BSW MODULE DECRIPTION : Port.bmd                                          **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Port configuration generated out of ECUC file              **
**                                                                            **
**  SPECIFICATION(S) : Specification of Port Driver, AUTOSAR Release 4.2.2    **
**                    and AUTOSAR Release 4.4.0                               **
**                                                                            **
** MAY BE CHANGED BY USER : no                                                **
**                                                                            **
*******************************************************************************/
#ifndef PORT_PBCFG_H
#define PORT_PBCFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/*******************************************************************************
**                      Global Const Declaration                              **
*******************************************************************************/
/*
  Note: Elektrobit Automotive GmbH modified the original code provided
        by the third party supplier. The modification is provided for
        convenience.
        Please use the modification on your discretion and account, or
        use the unmodified files provided with this distribution. 
  Please see for the reasons in the file ImportantNotes.txt for tag

ASCINFINEON-1043 Update PostBuild generation 
*/
#define PORT_START_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
guideline.*/
#include "Port_MemMap.h"
[!AUTOSPACING!][!//
  [!IF "var:defined('postBuildVariant')"!]
    [!LOOP "variant:all()"!]
      [!WS"0"!]extern const Port_ConfigType Port_Config_[!"."!];
    [!ENDLOOP!]
  [!ELSE!]
    [!WS"0"!]/* Extern declaration of Port Config Root */
    [!WS"0"!]extern const Port_ConfigType Port_Config;
  [!ENDIF!][!//
[!CR!]
#define PORT_STOP_SEC_CONFIG_DATA_ASIL_B_GLOBAL_UNSPECIFIED
/*MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header usage as per Autosar
guideline.*/
#include "Port_MemMap.h"
#endif  /* PORT_PBCFG_H */
[!ENDINDENT!]