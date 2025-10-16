[!/**
 * \file
 *
 * \brief AUTOSAR FrNm
 *
 * This file contains the implementation of the AUTOSAR
 * module FrNm.
 *
 * \version 5.16.16
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */!][!//
[!/* These checks were originally present as INVALID checks in FrNm.xdm.
   * Since these inter-module checks involve parameters from different
   * configuration classes, it's no more possible to keep them in FrNm.xdm.
   * Refer ASCFRNM-588 for more details.
   */!]

[!/* *** multiple inclusion protection *** */!]
[!IF "not(var:defined('FRNM_MACROS_M'))"!]
[!VAR "FRNM_MACROS_M" = "'true'"!]

[!/*
*************************************************************************
* MACRO to get the string for the symbolic name value.
* "ShortNameRef" must reference the container holding the short name.
*************************************************************************
*/!]
[!NOCODE!][!//
[!MACRO "GetSymbolName","ShortNameRef"!][!//
  [!VAR "SymbolName" = "asc:getShortName($ShortNameRef)"!][!//
  [!IF "$SymbolName = ''"!][!//
    [!VAR "SymbolName" = "concat('FrNmConf_',node:name(../..),'_',as:name(.))"!][!//
  [!ELSE!][!//
    [!VAR "SymbolName" = "concat('FrNmConf_',node:name(.),'_',$SymbolName)"!][!//
  [!ENDIF!][!//
[!ENDMACRO!][!//
[!ENDNOCODE!]

[!/*
*************************************************************************
* MACRO to indicate if PN synchronized shutdown is enabled.
*************************************************************************
*/!][!//
[!NOCODE!][!//
[!MACRO "GetSynchronizedPncShutdownEnabled"!][!//
  [!IF "num:i(count(as:modconf('FrNm')[1]/FrNmChannelConfig/eb-list::*[1]/FrNmChannel/eb-list::*[node:exists(FrNmChannelIdentifiers/FrNmSynchronizedPncShutdownEnabled) and (node:existsAndTrue(FrNmChannelIdentifiers/FrNmSynchronizedPncShutdownEnabled))])) > 0"!]
    [!VAR "SynchronizedPncShutdownEnabled" = "'true'"!][!//
  [!ELSE!][!//
    [!VAR "SynchronizedPncShutdownEnabled" = "'false'"!][!//
  [!ENDIF!][!//
[!ENDMACRO!][!//
[!ENDNOCODE!][!//

[!ENDIF!]