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
**  FILENAME  : I2c_PBcfg.h                                                   **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE      : 2019-09-06                                                    **
**                                                                            **
**  BSW MODULE DECRIPTION : I2c.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Code template header file for I2c Driver                   **
**                                                                            **
**  SPECIFICATION(S) : Specification of I2c Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*************************************************************************/!][!//
[!//
/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2018)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : I2c_PBcfg.h                                                   **
**                                                                            **
**  VERSION   : 5.0.0                                                         **
**                                                                            **
**  DATE, TIME: [!"$date"!], [!"$time"!]    !!!IGNORE-LINE!!!                 **
**                                                                            **
**  GENERATOR : Build [!"$buildnr"!]    !!!IGNORE-LINE!!!                     **
**                                                                            **
**  BSW MODULE DECRIPTION : I2c.bmd                                           **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : Infineon AURIX2G                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : I2c configuration generated out of ECUC file               **
**                                                                            **
**  SPECIFICATION(S) : Specification of I2c Driver, AUTOSAR Release 4.2.2     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
#ifndef I2C_PBCFG_H
#define I2C_PBCFG_H
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
**                      Includes                                              **
*******************************************************************************/
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
#define I2C_START_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
 /* MISRA2012_RULE_8_4_JUSTIFICATION: Module configuration data structure
   declaration is as per Autosar guidelines. This data structure is needed
   by SW units using I2c Driver APIs hence it should be declared as extern in
   the SW unit from where it is used */
#include "I2c_MemMap.h"
[!AUTOSPACING!]
  [!IF "var:defined('postBuildVariant')"!][!//
    [!LOOP "variant:all()"!]
      [!WS"0"!]/* Extern declaration of I2c Config Root for [!"."!] */
      [!WS"0"!]extern const I2c_ConfigType I2c_Config_[!"."!];
    [!ENDLOOP!]
  [!ELSE!][!//
    [!WS"0"!]/* Extern declaration of I2c Config Root */
    [!WS"0"!]extern const I2c_ConfigType I2c_Config;
  [!ENDIF!][!//
#define I2C_STOP_SEC_CONFIG_DATA_QM_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
/* MISRA2012_RULE_20_1_JUSTIFICATION: Declaration before #include,
 * this is due to inclusion of memmap.h to specify the location to which
 * the variable has to be placed. */
#include "I2c_MemMap.h"
#endif

