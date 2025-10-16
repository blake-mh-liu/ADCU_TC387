[!/*****************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2019)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Fr_17_Eray_PBcfg.h                                            **
**                                                                            **
**  VERSION   : 7.0.0                                                         **
**                                                                            **
**  DATE      : 2019-06-28                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : Fr_17_Eray.bmd                                    **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  TRACEABILITY : [cover parentID={1B5F5E4D-B718-47c6-B433-B636751360E1}]    **
**                                                                            **
**  DESCRIPTION  : Code template header file for Fr Driver                    **
**                                                                            **
**  [/cover]                                                                  **
**                                                                            **
**  SPECIFICATION(S) : Specification of FlexRay Driver, AUTOSAR Release 4.2.2 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*************************************************************************/!][!//
[!//
/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2019)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Fr_17_Eray_PBcfg.h                                            **
**                                                                            **
**  VERSION   : 7.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]             !!!IGNORE-LINE!!!            **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]               !!!IGNORE-LINE!!!            **
**                                                                            **
**  BSW MODULE DECRIPTION : Fr_17_Eray.bmd                                    **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Fr configuration generated out of ECUC file                **
**                                                                            **
**  SPECIFICATION(S) : Specification of FlexRay Driver, AUTOSAR Release 4.2.2 **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef FR_17_ERAY_PBCFG_H
#define FR_17_ERAY_PBCFG_H
/*******************************************************************************
**                      Includes                                              **
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
/*******************************************************************************
**                      Global Const Declaration                              **
*******************************************************************************/
[!/*
[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
Memory mapping for configuration data [/cover]
*/!][!//
#define FR_17_ERAY_START_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so multiple inclusions are performed. This violation is an
approved exception without side effects by AUTOSAR. */
#include "Fr_17_Eray_MemMap.h"
[!AUTOSPACING!]
[!INDENT "0"!][!//
  [!IF "var:defined('postBuildVariant')"!][!//
    [!LOOP "variant:all()"!]
      [!WS"0"!]/* Extern declaration of Fr Config Root for [!"."!] */
      [!WS"0"!]extern const Fr_17_Eray_ConfigType Fr_17_Eray_Config_[!"."!];
    [!ENDLOOP!]
  [!ELSE!][!//
    [!WS"0"!]/* Extern declaration of Fr Config Root */
    [!WS"0"!]extern const Fr_17_Eray_ConfigType Fr_17_Eray_Config;
  [!ENDIF!][!//
[!ENDINDENT!][!//
[!/*
[cover parentID={E4047F9A-8865-4b2c-9D3C-385479854EAD}]
Memory mapping for configuration data [/cover]
*/!][!//
#define FR_17_ERAY_STOP_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: MemMap.h is used to define memory sections
of the data or code, so multiple inclusions are performed. This violation is an
approved exception without side effects by AUTOSAR. */
#include "Fr_17_Eray_MemMap.h"

#endif  /* FR_17_ERAY_PBCFG_H */

