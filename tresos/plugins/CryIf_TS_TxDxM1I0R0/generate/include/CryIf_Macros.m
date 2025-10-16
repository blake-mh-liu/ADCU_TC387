[!/**
 * \file
 *
 * \brief AUTOSAR CryIf
 *
 * This file contains the implementation of the AUTOSAR
 * module CryIf.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2018 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */!][!//
[!/* -------------------------------------------------------------------------------------- */!][!//
[!//
[!/* *** multiple inclusion protection *** */!][!//
[!IF "not(var:defined('CRYIF_MACROS_M'))"!][!//
[!VAR "CRYIF_MACROS_M" = "'true'"!][!//
[!INDENT "0"!][!//
[!//
[!/* -------------------------------------------------------------------------------------- */!][!//
[!//
[!/*
****************************************************************************************************
* MACRO to get the module implementation prefix (MIP) of a Crypto module.
****************************************************************************************************
*/!][!//
[!//
[!MACRO "CryIf_CryptoMip", "ctr"!][!//
  [!VAR "vendorID" = "''"!][!//
  [!VAR "apiInfix" = "''"!][!//
  [!SELECT "node:ref($ctr)"!][!//
    [!IF "node:exists(as:modconf('CryIf')/CryIfEbGeneral/CryIfEbGeneralBswmdImplementation)"!][!//
      [!IF "node:exists(as:modconf('CryIf')/CryIfEbGeneral/CryIfEbGeneralBswmdImplementation/CryIfEbGeneralBswmdImplementationRefs/*/CryIfCryptoRef[node:path(node:ref(.)) = $ctr])"!][!//
        [!/* !LINKSTO CryIf.Dsn.Tbcg/Mip/00003,1 */!][!//
        [!SELECT "as:modconf('CryIf')/CryIfEbGeneral/CryIfEbGeneralBswmdImplementation/CryIfEbGeneralBswmdImplementationRefs/*/CryIfCryptoRef[node:path(node:ref(.)) = $ctr]/.."!][!//
          [!VAR "vendorID" = "asc:getVendorId(as:path(node:ref(./CryIfCryptoBswImplementationRef)))"!][!//
          [!VAR "apiInfix" = "asc:getVendorApiInfix(as:path(node:ref(./CryIfCryptoBswImplementationRef)))"!][!//
        [!ENDSELECT!][!//
      [!ELSE!][!//
        [!/* !LINKSTO CryIf.Dsn.Tbcg/Mip/00004,1 */!][!//
        [!IF "not(node:empty(./CommonPublishedInformation/VendorId))      "!][!VAR "vendorID" = "node:value(./CommonPublishedInformation/VendorId)      "!][!ENDIF!][!//
        [!IF "not(node:empty(./CommonPublishedInformation/VendorApiInfix))"!][!VAR "apiInfix" = "node:value(./CommonPublishedInformation/VendorApiInfix)"!][!ENDIF!][!//
      [!ENDIF!][!//
    [!ELSE!][!//
      [!/* !LINKSTO CryIf.Dsn.Tbcg/Mip/00002,1 */!][!//
      [!IF "not(node:empty(./CommonPublishedInformation/VendorId))      "!][!VAR "vendorID" = "node:value(./CommonPublishedInformation/VendorId)      "!][!ENDIF!][!//
      [!IF "not(node:empty(./CommonPublishedInformation/VendorApiInfix))"!][!VAR "apiInfix" = "node:value(./CommonPublishedInformation/VendorApiInfix)"!][!ENDIF!][!//
    [!ENDIF!][!//
    [!IF "(string-length($vendorID) > 0) and (string-length($apiInfix) > 0)"!][!//
[!/* generate '_<vi>_<ai>' pattern (multi instance) */!][!//
_[!"$vendorID"!]_[!"$apiInfix"!][!//
    [!ELSEIF "(string-length($vendorID) > 0) and (string-length($apiInfix) = 0)"!][!//
[!/* generate nothing (single instance) */!][!//
    [!ELSE!][!//
      [!ERROR "?concat('The vendorId and apiInfix for Crypto module &apos;', node:path(./../..), '&apos; are empty. Add/Complete the &apos;CommonPublishedInformation&apos; or add/complete/import the &apos;BSW-IMPLEMENTATION&apos; for this Crypto module.')"!][!//
    [!ENDIF!][!//
  [!ENDSELECT!][!//
[!ENDMACRO!][!//
[!//
[!/* -------------------------------------------------------------------------------------- */!][!//
[!//
[!ENDINDENT!][!//
[!ENDIF!][!/* *** multiple inclusion protection *** */!][!//
