/**
 * \file
 *
 * \brief AUTOSAR FrIf
 *
 * This file contains the implementation of the AUTOSAR
 * module FrIf.
 *
 * \version 5.3.33
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
[!CODE!]
[!AUTOSPACING!]

#ifndef FRIF_SYMBOLICNAMES_PBCFG_H
#define FRIF_SYMBOLICNAMES_PBCFG_H

/*
* Include Section
*/

[!INCLUDE "CommonMacros.m"!][!//
[!IF "node:value(as:modconf('FrIf')/FrIfGeneral/VendorSpecific/SymbolicNamesULPduHandleId)='true'"!][!//
[!LOOP "as:modconf('FrIf')[1]/FrIfUserUpperLayerConfig/*[node:value(FrIfUpperLayerUseSymbolicNamesPduHandleId)='true']"!][!//
#include <[!"node:value(./FrIfUpperLayerIncludeFile)"!]>
[!ENDLOOP!][!//
[!ENDIF!][!//

/*==================[macros]=================================================*/
[!/* Array for holding Shortnames */!]
[!VAR "ShortNameList"="''"!]

[!/*  MACRO to get the string for the symbolic name value.
   * "ShortNameRef" must reference the container holding the short name. (AUTOSAR short name)
   * "OldName" must hold an unique string for the case that the specification
   * conform short name does not exist. This is supplied to be backward compatible.
*/!][!/*

*/!]
[!MACRO "GetSymbolName","ShortNameRef","OldName"!]
[!VAR "SymbolName" = "asc:getShortName($ShortNameRef)"!]
[!IF "$SymbolName = ''"!]
[!VAR "SymbolName" = "concat(name(../../.),'_',name(.),'_',$OldName)"!]
[!ELSE!]
[!VAR "ShortNameList" = "concat($ShortNameList,' ',$SymbolName)"!]
[!IF "not(text:uniq(text:split($ShortNameList), $SymbolName))"!]
[!ERROR!] The short name [!"$SymbolName"!] of the schema node [!"$OldName"!] is not unique.[!ENDERROR!]
[!ENDIF!]
[!VAR "SymbolName" = "concat($OldName,'_',$SymbolName)"!]
[!ENDIF!]
[!ENDMACRO!]

[!MACRO "GetFrIfPduSymbolName","ObjectRef"!]
[!VAR "SymbolName" = "asc:getShortName($ObjectRef)"!]
[!IF "($SymbolName = 'FrIfPduDirection')"!]
[!VAR "SymbolName" = "name(../.)"!]
[!ELSE!]
[!VAR "ShortNameList" = "concat($ShortNameList,' ',$SymbolName)"!]
[!IF "not(text:uniq(text:split($ShortNameList), $SymbolName))"!]
[!ERROR!] The short name [!"$SymbolName"!] of the schema node [!"$ObjectRef"!] is not unique.[!ENDERROR!]
[!ENDIF!]
[!VAR "SymbolName" = "concat('FrIfTxPdu_',$SymbolName)"!]
[!ENDIF!]
[!ENDMACRO!]
[!/*

*/!][!LOOP "as:modconf('FrIf')[1]/FrIfConfig/*[1]/FrIfCluster/*"!]
[!CALL "GetSymbolName", "ShortNameRef"="'.'", "OldName"="name(../.)"!]
[!CALL "GuardedDefine", "Comment"="'Export symbolic name values for FrIfClstIds'",
  "Name"="concat('FrIfConf_', $SymbolName)"!] [!"FrIfClstIdx"!]U
#if (defined FRIF_PROVIDE_LEGACY_SYMBOLIC_NAMES)
[!CALL "GuardedDefine", "Comment"="'Export symbolic name value with module abbreviation as prefix only (AUTOSAR 4.0 rev2 <= AUTOSAR version)'",
  "Name"="concat('FrIf_', @name)"!] [!"FrIfClstIdx"!]U
#endif /* defined FRIF_PROVIDE_LEGACY_SYMBOLIC_NAMES */
[!ENDLOOP!]

[!LOOP "as:modconf('FrIf')[1]/FrIfConfig/*[1]/FrIfPdu/*/*[@name='FrIfTxPdu']"!]
[!CALL "GetFrIfPduSymbolName", "ObjectRef"="'.'"!]
[!CALL "GuardedDefine", "Comment"="'Export symbolic name values for FrIfTxPduIds'",
  "Name"="concat('FrIfConf_', $SymbolName)"!] [!"FrIfTxPduId"!]U
#if (defined FRIF_PROVIDE_LEGACY_SYMBOLIC_NAMES)
[!CALL "GuardedDefine", "Comment"="'Export symbolic name value with module abbreviation as prefix only (AUTOSAR 4.0 rev2 <= AUTOSAR version)'",
  "Name"="concat('FrIf_', ../@name)"!] [!"FrIfTxPduId"!]U
#endif /* defined FRIF_PROVIDE_LEGACY_SYMBOLIC_NAMES */
[!ENDLOOP!][!/*

*/!][!LOOP "as:modconf('FrIf')[1]/FrIfConfig/*[1]/FrIfCluster/*/FrIfController/*"!]
[!CALL "GetSymbolName", "ShortNameRef"="'.'", "OldName"="name(../.)"!]
[!CALL "GuardedDefine", "Comment"="'Export symbolic name values for FrIfCtrlIdxs'",
  "Name"="concat('FrIfConf_', $SymbolName)"!] [!"FrIfCtrlIdx"!]U
#if (defined FRIF_PROVIDE_LEGACY_SYMBOLIC_NAMES)
[!CALL "GuardedDefine", "Comment"="'Export symbolic name value with module abbreviation as prefix only (AUTOSAR 4.0 rev2 <= AUTOSAR version)'",
  "Name"="concat('FrIf_', ../../@name, '_', @name)"!] [!"FrIfCtrlIdx"!]U
#endif /* defined FRIF_PROVIDE_LEGACY_SYMBOLIC_NAMES */
[!ENDLOOP!][!/*

*/!][!LOOP "as:modconf('FrIf')[1]/FrIfConfig/*[1]/FrIfCluster/*/FrIfController/*/FrIfLPdu/*"!]
[!CALL "GetSymbolName", "ShortNameRef"="'.'", "OldName"="name(../.)"!]
[!CALL "GuardedDefine", "Comment"="'Export symbolic name values for FrIfLPduIdxs'",
  "Name"="concat('FrIfConf_', $SymbolName)"!] [!"FrIfLPduIdx"!]U
#if (defined FRIF_PROVIDE_LEGACY_SYMBOLIC_NAMES)
[!CALL "GuardedDefine", "Comment"="'Export symbolic name value with module abbreviation as prefix only (AUTOSAR 4.0 rev2 <= AUTOSAR version)'",
  "Name"="concat('FrIf_', ../../../../@name, '_', ../../@name, '_', @name)"!] [!"FrIfLPduIdx"!]U
#endif /* defined FRIF_PROVIDE_LEGACY_SYMBOLIC_NAMES */
[!ENDLOOP!][!//

[!IF "node:value(as:modconf('FrIf')/FrIfGeneral/VendorSpecific/SymbolicNamesULPduHandleId)='true'"!][!//
[!LOOP "as:modconf('FrIf')/FrIfConfig/*[1]/FrIfPdu/*[(FrIfPduDirection = 'FrIfRxPdu') and (node:exists(VendorSpecific/FrIfUseULSymbolicNames)) and (node:value(VendorSpecific/FrIfUseULSymbolicNames) = 'true')]"!][!//
[!IF "node:exists(as:modconf(as:name(as:ref(./VendorSpecific/FrIfUpperLayerRef)))) = 'true'"!][!//
[!IF "count(as:modconf(as:name(as:ref(./VendorSpecific/FrIfUpperLayerRef)))/CddComStackContribution/CddComIfUpperLayerContribution/CddComIfUpperLayerRxPdu/*[(node:refvalid(CddComIfPduRef) and (node:path(as:ref(CddComIfPduRef)) = node:path(as:ref(node:current()/FrIfPduDirection/FrIfRxPduRef))))]) = 1"!][!//
#define FrIf_IntSym_[!"as:name(node:current())"!] [!//
[!"text:split(node:path(as:modconf(as:name(as:ref(./VendorSpecific/FrIfUpperLayerRef)))/CddComStackContribution/CddComIfUpperLayerContribution/CddComIfUpperLayerRxPdu/*[(node:refvalid(CddComIfPduRef) and (node:path(as:ref(CddComIfPduRef)) = node:path(as:ref(node:current()/FrIfPduDirection/FrIfRxPduRef))))]),'/')[5]"!]Conf_CddComIfUpperLayerRxPdu_[!"as:name(as:modconf(as:name(as:ref(./VendorSpecific/FrIfUpperLayerRef)))/CddComStackContribution/CddComIfUpperLayerContribution/CddComIfUpperLayerRxPdu/*[(node:refvalid(CddComIfPduRef) and (node:path(as:ref(CddComIfPduRef)) = node:path(as:ref(node:current()/FrIfPduDirection/FrIfRxPduRef))))])"!]
[!ELSE!]
[!ERROR!]PDU "[!"as:name(node:current())"!]" has to be referenced exactly once.[!ENDERROR!]
[!ENDIF!]
[!ELSE!]
[!ERROR!]Could not find a module named "[!"as:name(as:ref(./VendorSpecific/FrIfUpperLayerRef))"!]".[!ENDERROR!]
[!ENDIF!][!//
[!ENDLOOP!]

[!LOOP "as:modconf('FrIf')/FrIfConfig/*[1]/FrIfPdu/*[(FrIfPduDirection = 'FrIfTxPdu') and (node:exists(VendorSpecific/FrIfUseULSymbolicNames)) and (node:value(VendorSpecific/FrIfUseULSymbolicNames) = 'true')]"!][!//
/* Map internal UL symbolic names with CDD symbolic names */
[!IF "node:exists(as:modconf(as:name(as:ref(./VendorSpecific/FrIfUpperLayerRef)))) = 'true'"!][!//
[!IF "count(as:modconf(as:name(as:ref(./VendorSpecific/FrIfUpperLayerRef)))/CddComStackContribution/CddComIfUpperLayerContribution/CddComIfUpperLayerTxPdu/*[(node:refvalid(CddComIfPduRef) and (node:path(as:ref(CddComIfPduRef)) = node:path(as:ref(node:current()/FrIfPduDirection/FrIfTxPduRef))))]) = 1"!][!//
#define FrIf_IntSym_[!"as:name(node:current())"!] [!//
[!"text:split(node:path(as:modconf(as:name(as:ref(./VendorSpecific/FrIfUpperLayerRef)))/CddComStackContribution/CddComIfUpperLayerContribution/CddComIfUpperLayerTxPdu/*[(node:refvalid(CddComIfPduRef) and (node:path(as:ref(CddComIfPduRef)) = node:path(as:ref(node:current()/FrIfPduDirection/FrIfTxPduRef))))]),'/')[5]"!]Conf_CddComIfUpperLayerTxPdu_[!"as:name(as:modconf(as:name(as:ref(./VendorSpecific/FrIfUpperLayerRef)))/CddComStackContribution/CddComIfUpperLayerContribution/CddComIfUpperLayerTxPdu/*[(node:refvalid(CddComIfPduRef) and (node:path(as:ref(CddComIfPduRef)) = node:path(as:ref(node:current()/FrIfPduDirection/FrIfTxPduRef))))])"!]
[!ELSE!]
[!ERROR!]PDU "[!"as:name(node:current())"!]" has to be referenced exactly once.[!ENDERROR!]
[!ENDIF!]
[!ELSE!]
[!ERROR!]Could not find a module named "[!"as:name(as:ref(./VendorSpecific/FrIfUpperLayerRef))"!]".[!ENDERROR!]
[!ENDIF!][!//
[!ENDLOOP!]
[!ENDIF!]

#endif /* FRIF_SYMBOLICNAMES_PBCFG_H */

/*==================[end of file]============================================*/
[!ENDCODE!][!//

