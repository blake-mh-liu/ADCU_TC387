/**
 * \file
 *
 * \brief AUTOSAR Crypto
 *
 * This file contains the implementation of the AUTOSAR
 * module Crypto.
 *
 * \version 2.0.39
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Cfg.h/0001,1 */

#ifndef CRYPTO_XVIX_XAIX_INT_CFG_H
#define CRYPTO_XVIX_XAIX_INT_CFG_H
[!AUTOSPACING!][!//
[!/*========================================================================================*/!][!//
[!INCLUDE "Crypto_xVIx_xAIx_Macros.m"!]
[!//
[!IF "ecu:has('Cpu.Type')"!]
  [!VAR "WordWidthInBytes" = "bit:shr(ecu:get('Cpu.Type'), 3)"!]
[!ELSE!]
  [!ERROR "It is not possible to determine the 'Cpu.Type'."!]
[!ENDIF!]
[!//
[!VAR "CreateSecondaryJobTemplates" = "'false'"!]
[!VAR "CreateDefaultRandomJobTemplates" = "'false'"!]
[!/*========================================================================================*/!][!//

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

[!CALL "GetPrimitivesPoolList", "ctr" = "node:path(CryptoDriverObjects)"!]
[!VAR "maxlen" = "num:max(node:foreach(text:split($PrimitivesPoolListShrt), 'cpr', 'string-length($cpr)') | node:foreach(CryptoEbGeneral/CryptoEbMisc/CryptoEbKeyManagementAlgorithm/eb-list::*, 'kmn', 'string-length(text:replace($kmn, "CRYPTO_KMN_", ""))'))"!]
#include <Crypto_xVIx_xAIx_Int_Types.h>  [!"substring($WS, 1, $maxlen - num:i(1))"!]/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Cfg.h/0002,1 */
[!FOR "i" = "1" TO "$PrimitivesPoolListSize"!]
  [!VAR "primitive" = "string(text:split($PrimitivesPoolListShrt)[position() = $i])"!]
#include <Crypto_xVIx_xAIx_Int_CPr_[!"$primitive"!].h>  [!"substring($WS, 1, $maxlen - string-length($primitive))"!]/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Cfg.h/0003,1 */
[!ENDFOR!]
[!LOOP "util:distinct(node:order(CryptoEbGeneral/CryptoEbMisc/CryptoEbKeyManagementAlgorithm/eb-list::*))"!]
  [!VAR "primitive" = "text:replace(node:value(.), 'CRYPTO_KMN_','')"!]
#include <Crypto_xVIx_xAIx_Int_KMn_[!"$primitive"!].h>  [!"substring($WS, 1, $maxlen - string-length($primitive))"!]/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Cfg.h/0004,1 */
[!ENDLOOP!]

/*==================[macros]======================================================================*/

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * miscellaneous macros (a)
 */

#if (defined CRYPTO_XVIX_XAIX_MAX)
#error CRYPTO_XVIX_XAIX_MAX is already defined
#endif
/** \brief  Macro indicating the maximum of two values. **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_MAX,1 */
#define CRYPTO_XVIX_XAIX_MAX(a, b) (((a) > (b)) ? (a) : (b))

#if (defined CRYPTO_XVIX_XAIX_MIN)
#error CRYPTO_XVIX_XAIX_MIN is already defined
#endif
/** \brief  Macro indicating the minimum of two values. **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_MIN,1 */
#define CRYPTO_XVIX_XAIX_MIN(a, b) (((a) < (b)) ? (a) : (b))

#if (defined CRYPTO_XVIX_XAIX_JOBSTATE)
#error CRYPTO_XVIX_XAIX_JOBSTATE is already defined
#endif
/** \brief  Macro which selects the name 'state' or 'jobState' of the member in CSM Crypto_JobType
 **         structure that represents the current job state depending on the selected API version
 **/
/* !LINKSTO Crypto.Req.Api/CRYPTO_API_VERSION_XX/CRYPTO_XVIX_XAIX_JOBSTATE,2 */
[!IF "node:value(CryptoEbGeneral/CryptoEbMisc/CryptoEbAutosarApiVersion) = 'CRYPTO_API_VERSION_430'"!]
#define CRYPTO_XVIX_XAIX_JOBSTATE state
[!ELSE!]
#define CRYPTO_XVIX_XAIX_JOBSTATE jobState
[!ENDIF!]

#if (defined CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT)
#error CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT is already defined
#endif
/** \brief  Macro which selects the name 'PrimitiveInputOutput' or 'jobPrimitiveInputOutput' of the member
 **         in CSM Crypto_JobType structure that represents the current job state depending on the selected
 **         API version.
 **/
/* !LINKSTO Crypto.Req.Api/CRYPTO_API_VERSION_XX/CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT,2 */
[!IF "node:value(CryptoEbGeneral/CryptoEbMisc/CryptoEbAutosarApiVersion) = 'CRYPTO_API_VERSION_430'"!]
#define CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT PrimitiveInputOutput
[!ELSE!]
#define CRYPTO_XVIX_XAIX_JOBPRIMITIVEINPUTOUTPUT jobPrimitiveInputOutput
[!ENDIF!]

#if (defined CRYPTO_XVIX_XAIX_INTERNAL_E_KEY_NOT_AVAILABLE)
#error CRYPTO_XVIX_XAIX_INTERNAL_E_KEY_NOT_AVAILABLE is already defined
#endif
/** \brief  Internally error value for CRYPTO_E_KEY_NOT_AVAILABLE used to distinguish between API version definitions **/
/* !LINKSTO Crypto.Req.Api/CRYPTO_API_VERSION_XX/CRYPTO_XVIX_XAIX_INTERNALKEYNOTAVAILABLE/0001,1 */
[!IF "(node:value(CryptoEbGeneral/CryptoEbMisc/CryptoEbAutosarApiVersion) = 'CRYPTO_API_VERSION_430') or (node:value(CryptoEbGeneral/CryptoEbMisc/CryptoEbAutosarApiVersion) = 'CRYPTO_API_VERSION_431') or (node:value(CryptoEbGeneral/CryptoEbMisc/CryptoEbAutosarApiVersion) = 'CRYPTO_API_VERSION_EB')"!]
#define CRYPTO_XVIX_XAIX_INTERNAL_E_KEY_NOT_AVAILABLE E_NOT_OK
[!ELSE!]
#define CRYPTO_XVIX_XAIX_INTERNAL_E_KEY_NOT_AVAILABLE CRYPTO_XVIX_XAIX_E_NOT_AVAILABLE
[!ENDIF!]

[!LOOP "util:distinct(node:order(CryptoDriverObjects/CryptoDriverObject/eb-list::*, 'node:value(CryptoDriverObjectId)'))"!]
  [!CALL "GetCryptoDriverObjectPrimitivesList", "cdo" = "node:path(node:current())"!]
  [!IF "($CryptoDriverObjectPrimitivesListRealFullP2Size != 0) or ($CryptoDriverObjectPrimitivesListRealFullR2Size != 0)"!]
    [!VAR "CreateSecondaryJobTemplates" = "'true'"!]
  [!ENDIF!]
  [!IF "$CryptoDriverObjectPrimitivesListRealFullR1Size != 0"!]
    [!VAR "CreateDefaultRandomJobTemplates" = "'true'"!]
  [!ENDIF!]
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * macros related to the specific Crypto Driver Object '[!"node:pos(.)"!] - [!"node:name(.)"!]'
 */

#if (defined CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_CPR_COUNT)
#error CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_CPR_COUNT is already defined
#endif
/** \brief  Number of primitives directly assigned to crypto driver object '[!"node:pos(.)"!] - [!"node:name(.)"!]' **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_CDO_CDO_CPR_COUNT/0001,1 */
#define CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_CPR_COUNT [!"$CryptoDriverObjectPrimitivesListRealFullP1Size"!]U

[!/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */!][!//
  [!IF "node:exists(./CryptoEbPrimaryWorkspaceSize)"!]
    [!VAR "P1WkspSizeBytes" = "concat(num:i(node:value(./CryptoEbPrimaryWorkspaceSize)), 'U')"!]
    [!VAR "P1WkspSizeWords" = "concat(num:i(((node:value(./CryptoEbPrimaryWorkspaceSize) - 1) div $WordWidthInBytes) + 1), 'U')"!]
  [!ELSE!]
    [!CALL "GetMaxWorkspaceSize", "lst" = "$CryptoDriverObjectPrimitivesListRealTrimP1Shrt"!]
    [!VAR "P1WkspSizeBytes" = "concat('(', $CryptoDriverObjectWorkspaceSize, ')')"!]
    [!VAR "P1WkspSizeWords" = "concat('((((CRYPTO_XVIX_XAIX_CDO_', text:toupper(node:name(.)), '_P1WKSP_SIZE_BYTES) - 1) / ', $WordWidthInBytes,') + 1)')"!]
  [!ENDIF!]
#if (defined CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P1WKSP_SIZE_BYTES)
#error CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P1WKSP_SIZE_BYTES is already defined
#endif
/** \brief  Macro that defines the size in bytes of the workspace of the specific crypto driver
 **         object '[!"node:name(.)"!]' that is intended to hold
 **         the context (the run-time data) of a currently executed primary primitive.
 **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_CDO_CDO_P1WKSP_SIZE_BYTES/0001,1 */
#define CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P1WKSP_SIZE_BYTES [!"$P1WkspSizeBytes"!]

#if (defined CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P1WKSP_SIZE_WORDS)
#error CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P1WKSP_SIZE_WORDS is already defined
#endif
/** \brief  Macro that defines the size in words of the workspace of the specific crypto driver
 **         object '[!"node:name(.)"!]' that is intended to hold
 **         the context (the run-time data) of a currently executed primary primitive.
 **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_CDO_CDO_P1WKSP_SIZE_WORDS/0001,1 */
#define CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P1WKSP_SIZE_WORDS [!"$P1WkspSizeWords"!]

[!/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */!][!//
  [!IF "num:i(0) < $CryptoDriverObjectPrimitivesListRealTrimP2Size"!]
    [!IF "node:exists(./CryptoEbSecondaryWorkspaceSize)"!]
      [!VAR "P2WkspSizeBytes" = "concat(num:i(node:value(./CryptoEbSecondaryWorkspaceSize)), 'U')"!]
      [!VAR "P2WkspSizeWords" = "concat(num:i(((node:value(./CryptoEbSecondaryWorkspaceSize) - 1) div $WordWidthInBytes) + 1), 'U')"!]
    [!ELSE!]
      [!CALL "GetMaxWorkspaceSize", "lst" = "$CryptoDriverObjectPrimitivesListRealTrimP2Shrt"!]
      [!VAR "P2WkspSizeBytes" = "concat('(', $CryptoDriverObjectWorkspaceSize, ')')"!]
      [!VAR "P2WkspSizeWords" = "concat('((((CRYPTO_XVIX_XAIX_CDO_', text:toupper(node:name(.)), '_P2WKSP_SIZE_BYTES) - 1) / ', $WordWidthInBytes,') + 1)')"!]
    [!ENDIF!]
#if (defined CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P2WKSP_SIZE_BYTES)
#error CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P2WKSP_SIZE_BYTES is already defined
#endif
/** \brief  Macro that defines the size in bytes of the workspace of the specific crypto driver
 **         object '[!"node:name(.)"!]' that is intended to hold
 **         the context (the run-time data) of a currently executed secondary primitive.
 **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_CDO_CDO_P2WKSP_SIZE_BYTES/0001,1 */
#define CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P2WKSP_SIZE_BYTES [!"$P2WkspSizeBytes"!]

#if (defined CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P2WKSP_SIZE_WORDS)
#error CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P2WKSP_SIZE_WORDS is already defined
#endif
/** \brief  Macro that defines the size in words of the workspace of the specific crypto driver
 **         object '[!"node:name(.)"!]' that is intended to hold
 **         the context (the run-time data) of a currently executed secondary primitive.
 **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_CDO_CDO_P2WKSP_SIZE_WORDS/0001,1 */
#define CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P2WKSP_SIZE_WORDS [!"$P2WkspSizeWords"!]

  [!ENDIF!]
[!/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */!][!//
  [!IF "node:exists(./CryptoEbPrimaryHeapSize)"!]
    [!VAR "P1HeapSizeBytes" = "concat(num:i(node:value(./CryptoEbPrimaryHeapSize)), 'U')"!]
    [!VAR "P1HeapSizeWords" = "concat(num:i(((node:value(./CryptoEbPrimaryHeapSize) - 1) div $WordWidthInBytes) + 1), 'U')"!]
  [!ELSE!]
    [!VAR "P1HeapSizeBytes" = "concat(0, 'U')"!]
    [!VAR "P1HeapSizeWords" = "concat(0, 'U')"!]
  [!ENDIF!]
#if (defined CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P1HEAP_SIZE_BYTES)
#error CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P1HEAP_SIZE_BYTES is already defined
#endif
/** \brief  Macro that defines the size in bytes of the heap buffer of the specific crypto driver
 **         object '[!"node:name(.)"!]' that is intended to hold
 **         the context (the run-time data) of a currently executed primary primitive.
 **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_CDO_CDO_P1HEAP_SIZE_BYTES/0001,1 */
#define CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P1HEAP_SIZE_BYTES [!"$P1HeapSizeBytes"!]

#if (defined CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P1HEAP_SIZE_WORDS)
#error CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P1HEAP_SIZE_WORDS is already defined
#endif
/** \brief  Macro that defines the size in words of the heap buffer of the specific crypto driver
 **         object '[!"node:name(.)"!]' that is intended to hold
 **         the context (the run-time data) of a currently executed primary primitive.
 **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_CDO_CDO_P1HEAP_SIZE_WORDS/0001,1 */
#define CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P1HEAP_SIZE_WORDS [!"$P1HeapSizeWords"!]

[!/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */!][!//
  [!IF "num:i(0) < $CryptoDriverObjectPrimitivesListRealTrimP2Size"!]
    [!IF "node:exists(./CryptoEbSecondaryHeapSize)"!]
      [!VAR "P2HeapSizeBytes" = "concat(num:i(node:value(./CryptoEbSecondaryHeapSize)), 'U')"!]
      [!VAR "P2HeapSizeWords" = "concat(num:i(((node:value(./CryptoEbSecondaryHeapSize) - 1) div $WordWidthInBytes) + 1), 'U')"!]
    [!ELSE!]
      [!VAR "P2HeapSizeBytes" = "concat(0, 'U')"!]
      [!VAR "P2HeapSizeWords" = "concat(0, 'U')"!]
    [!ENDIF!]
#if (defined CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P2HEAP_SIZE_BYTES)
#error CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P2HEAP_SIZE_BYTES is already defined
#endif
/** \brief  Macro that defines the size in bytes of the heap buffer of the specific crypto driver
 **         object '[!"node:name(.)"!]' that is intended to hold
 **         the context (the run-time data) of a currently executed secondary primitive.
 **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_CDO_CDO_P2HEAP_SIZE_BYTES/0001,1 */
#define CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P2HEAP_SIZE_BYTES [!"$P2HeapSizeBytes"!]

#if (defined CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P2HEAP_SIZE_WORDS)
#error CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P2HEAP_SIZE_WORDS is already defined
#endif
/** \brief  Macro that defines the size in words of the heap buffer of the specific crypto driver
 **         object '[!"node:name(.)"!]' that is intended to hold
 **         the context (the run-time data) of a currently executed secondary primitive.
 **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_CDO_CDO_P2HEAP_SIZE_WORDS/0001,1 */
#define CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P2HEAP_SIZE_WORDS [!"$P2HeapSizeWords"!]

  [!ENDIF!]
[!/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */!][!//
  [!IF "node:exists(./CryptoDefaultRandomPrimitiveRef)"!]
    [!IF "node:exists(./CryptoDefaultRandomPrimaryWorkspaceSize)"!]
      [!VAR "R1WkspSizeBytes" = "concat(num:i(node:value(./CryptoDefaultRandomPrimaryWorkspaceSize)), 'U')"!]
      [!VAR "R1WkspSizeWords" = "concat(num:i(((node:value(./CryptoDefaultRandomPrimaryWorkspaceSize) - 1) div $WordWidthInBytes) + 1), 'U')"!]
    [!ELSE!]
      [!CALL "GetMaxWorkspaceSize", "lst" = "$CryptoDriverObjectPrimitivesListRealTrimR1Shrt"!]
      [!VAR "R1WkspSizeBytes" = "concat('(', $CryptoDriverObjectWorkspaceSize, ')')"!]
      [!VAR "R1WkspSizeWords" = "concat('((((CRYPTO_XVIX_XAIX_CDO_', text:toupper(node:name(.)), '_R1WKSP_SIZE_BYTES) - 1) / ', $WordWidthInBytes,') + 1)')"!]
    [!ENDIF!]
#if (defined CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_R1WKSP_SIZE_BYTES)
#error CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_R1WKSP_SIZE_BYTES is already defined
#endif
/** \brief  Macro that defines the size in bytes of the workspace of the specific crypto driver
 **         object '[!"node:name(.)"!]' that is intended to hold
 **         the context (the run-time data) of the primary primitive of the default random
 **         primitive.
 **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_CDO_CDO_R1WKSP_SIZE_BYTES/0001,1 */
#define CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_R1WKSP_SIZE_BYTES [!"$R1WkspSizeBytes"!]

#if (defined CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_R1WKSP_SIZE_WORDS)
#error CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_R1WKSP_SIZE_WORDS is already defined
#endif
/** \brief  Macro that defines the size in bytes of the workspace of the specific crypto driver
 **         object '[!"node:name(.)"!]' that is intended to hold
 **         the context (the run-time data) of the primary primitive of the default random
 **         primitive.
 **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_CDO_CDO_R1WKSP_SIZE_WORDS/0001,1 */
#define CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_R1WKSP_SIZE_WORDS [!"$R1WkspSizeWords"!]

  [!ENDIF!]
[!/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */!][!//
  [!IF "node:exists(./CryptoDefaultRandomPrimitiveRef)"!]
    [!IF "node:exists(./CryptoDefaultRandomSecondaryWorkspaceSize)"!]
      [!VAR "R2WkspSizeBytes" = "concat(num:i(node:value(./CryptoDefaultRandomSecondaryWorkspaceSize)), 'U')"!]
      [!VAR "R2WkspSizeWords" = "concat(num:i(((node:value(./CryptoDefaultRandomSecondaryWorkspaceSize) - 1) div $WordWidthInBytes) + 1), 'U')"!]
    [!ELSE!]
      [!CALL "GetMaxWorkspaceSize", "lst" = "$CryptoDriverObjectPrimitivesListRealTrimR2Shrt"!]
      [!VAR "R2WkspSizeBytes" = "concat('(', $CryptoDriverObjectWorkspaceSize, ')')"!]
      [!VAR "R2WkspSizeWords" = "concat('((((CRYPTO_XVIX_XAIX_CDO_', text:toupper(node:name(.)), '_R2WKSP_SIZE_BYTES) - 1) / ', $WordWidthInBytes,') + 1)')"!]
    [!ENDIF!]
#if (defined CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_R2WKSP_SIZE_BYTES)
#error CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_R2WKSP_SIZE_BYTES is already defined
#endif
/** \brief  Macro that defines the size in bytes of the workspace of the specific crypto driver
 **         object '[!"node:name(.)"!]' that is intended to hold
 **         the context (the run-time data) of the secondary primitive of the default random
 **         primitive.
 **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_CDO_CDO_R2WKSP_SIZE_BYTES/0001,1 */
#define CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_R2WKSP_SIZE_BYTES [!"$R2WkspSizeBytes"!]

#if (defined CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_R2WKSP_SIZE_WORDS)
#error CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_R2WKSP_SIZE_WORDS is already defined
#endif
/** \brief  Macro that defines the size in bytes of the workspace of the specific crypto driver
 **         object '[!"node:name(.)"!]' that is intended to hold
 **         the context (the run-time data) of the secondary primitive of the default random
 **         primitive.
 **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_CDO_CDO_R2WKSP_SIZE_WORDS/0001,1 */
#define CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_R2WKSP_SIZE_WORDS [!"$R2WkspSizeWords"!]

  [!ENDIF!]
[!ENDLOOP!]
[!//
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * macros generally related to Crypto Driver Object
 */

#if (defined CRYPTO_XVIX_XAIX_CDO_COUNT)
#error CRYPTO_XVIX_XAIX_CDO_COUNT is already defined
#endif
/** \brief  Number of configured crypto driver objects **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_CDO_COUNT,1 */
#define CRYPTO_XVIX_XAIX_CDO_COUNT [!"num:i(count(CryptoDriverObjects/CryptoDriverObject/eb-list::*))"!]U

#if (defined CRYPTO_XVIX_XAIX_DEFAULTRANDOM_ENABLED)
#error CRYPTO_XVIX_XAIX_DEFAULTRANDOM_ENABLED is already defined
#endif
/** \brief  Macro that defines whether a default random primitive is configured or not **/
[!IF "$CreateDefaultRandomJobTemplates = 'true'"!]
#define CRYPTO_XVIX_XAIX_DEFAULTRANDOM_ENABLED STD_ON
[!ELSE!]
#define CRYPTO_XVIX_XAIX_DEFAULTRANDOM_ENABLED STD_OFF
[!ENDIF!]

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * macros related to crypto keys
 */

[!LOOP "util:distinct(node:order(CryptoKeys/CryptoKey/eb-list::*, 'node:value(CryptoKeyId)'))"!]
#if (defined CRYPTO_XVIX_XAIX_KEY_[!"text:toupper(node:name(.))"!]_ID)
#error CRYPTO_XVIX_XAIX_KEY_[!"text:toupper(node:name(.))"!]_ID is already defined
#endif
/** \brief  Identifier of crypto key [!"text:toupper(node:name(.))"!] **/
#define CRYPTO_XVIX_XAIX_KEY_[!"text:toupper(node:name(.))"!]_ID [!"node:pos(.)"!]U

[!ENDLOOP!]
[!//
#if (defined CRYPTO_XVIX_XAIX_KEY_COUNT)
#error CRYPTO_XVIX_XAIX_KEY_COUNT is already defined
#endif
/** \brief  Number of configured crypto keys **/
#define CRYPTO_XVIX_XAIX_KEY_COUNT [!"num:i(count(CryptoKeys/CryptoKey/eb-list::*))"!]U

/* macros related to Key Elements */

#if (defined CRYPTO_XVIX_XAIX_KEY_ELEMENT_COUNT)
#error CRYPTO_XVIX_XAIX_KEY_ELEMENT_COUNT is already defined
#endif
/** \brief  Number of configured crypto key elements **/
#define CRYPTO_XVIX_XAIX_KEY_ELEMENT_COUNT [!"num:i(count(CryptoKeyElements/CryptoKeyElement/eb-list::*))"!]U

/* macros related to persistent KeyElements */
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_SETDATA/0001,1 */
#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_SETDATA)
#error CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_SETDATA is already defined
#endif
/** \brief  macro for activating the storing of persisten KeyElements **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_SETDATA/0002,1 */
[!IF "num:i(0) < count(util:distinct(node:refs(util:distinct(node:refs(./CryptoKeys/CryptoKey/eb-list::*/CryptoKeyTypeRef))/CryptoKeyElementRef/eb-list::*))/CryptoKeyElementPersist[node:existsAndTrue(.)])"!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_SETDATA STD_ON
[!ELSE!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_SETDATA STD_OFF
[!ENDIF!][!//

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_GETDATA/0001,1 */
#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_GETDATA)
#error CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_GETDATA is already defined
#endif
/** \brief  macro for activating the reading of persistent KeyElements **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_GETDATA/0002,1 */
[!IF "num:i(0) < count(util:distinct(node:refs(util:distinct(node:refs(./CryptoKeys/CryptoKey/eb-list::*/CryptoKeyTypeRef))/CryptoKeyElementRef/eb-list::*))/CryptoKeyElementPersist[node:existsAndTrue(.)])"!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_GETDATA STD_ON
[!ELSE!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEYELEMENT_GETDATA STD_OFF
[!ENDIF!][!//

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_SETVALID/0001,1 */
#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_SETVALID)
#error CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_SETVALID is already defined
#endif
/** \brief  macro for activating the setting the valid state of persistent KeyElements **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_SETVALID/0002,1 */
[!IF "num:i(0) < count(util:distinct(node:refs(util:distinct(node:refs(./CryptoKeys/CryptoKey/eb-list::*/CryptoKeyTypeRef))/CryptoKeyElementRef/eb-list::*))/CryptoKeyElementPersist[node:existsAndTrue(.)])"!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_SETVALID STD_ON
[!ELSE!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_SETVALID STD_OFF
[!ENDIF!][!//

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_GETVALID/0001,1 */
#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_GETVALID)
#error CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_GETVALID is already defined
#endif
/** \brief  macro for activating the storing of persistent KeyElements **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_GETVALID/0002,1 */
[!IF "num:i(0) < count(util:distinct(node:refs(util:distinct(node:refs(./CryptoKeys/CryptoKey/eb-list::*/CryptoKeyTypeRef))/CryptoKeyElementRef/eb-list::*))/CryptoKeyElementPersist[node:existsAndTrue(.)])"!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_GETVALID STD_ON
[!ELSE!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_COUT_KEY_GETVALID STD_OFF
[!ENDIF!][!//

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * macros related to padding
 */

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_API_ENABLED_INT_PADDING_PKCS7/0001,1 */
#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_INT_PADDING_PKCS7)
#error CRYPTO_XVIX_XAIX_API_ENABLED_INT_PADDING_PKCS7 is already defined
#endif
/** \brief  Macro representing whether the PKCS #7 padding is configured via at least one
 **         primitive assigned to a Crypto Driver Object.
 **/
[!IF "contains(string(node:foreach(util:distinct(node:refs(CryptoDriverObjects/CryptoDriverObject/eb-list::*/CryptoPrimitiveRef/eb-list::*))/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*, 'x', '$x')), 'CRYPTO_ALGOFAM_PADDING_PKCS7')"!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_INT_PADDING_PKCS7 STD_ON
[!ELSE!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_INT_PADDING_PKCS7 STD_OFF
[!ENDIF!][!//

/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_API_ENABLED_INT_PADDING_TLS12/0001,1 */
#if (defined CRYPTO_XVIX_XAIX_API_ENABLED_INT_PADDING_TLS12)
#error CRYPTO_XVIX_XAIX_API_ENABLED_INT_PADDING_TLS12 is already defined
#endif
/** \brief  Macro representing whether the TLS 1.2 padding is configured via at least one
 **         primitive assigned to a Crypto Driver Object.
 **/
[!IF "contains(string(node:foreach(util:distinct(node:refs(CryptoDriverObjects/CryptoDriverObject/eb-list::*/CryptoPrimitiveRef/eb-list::*))/CryptoPrimitiveAlgorithmSecondaryFamiliy/eb-list::*, 'x', '$x')), 'CRYPTO_ALGOFAM_PADDING_TLS12')"!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_INT_PADDING_TLS12 STD_ON
[!ELSE!][!//
#define CRYPTO_XVIX_XAIX_API_ENABLED_INT_PADDING_TLS12 STD_OFF
[!ENDIF!][!//

[!IF "$CreateSecondaryJobTemplates = 'true'"!]
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * miscellaneous macros (b)
 */

#if (defined CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB)
#error CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB is already defined
#endif
/** \brief  This macro sets the secondary job used for processing. **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB,1 */
#define CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB()                                                                                                  \
do                                                                                                                                            \
{                                                                                                                                             \
  TS_MemCpy(&workspace->secondaryJob_primitiveInfo,    &Crypto_xVIx_xAIx_SecondaryJob_PrimitiveInfo,    sizeof(Crypto_PrimitiveInfoType)   ); \
  TS_MemCpy(&workspace->secondaryJob_jobPrimitiveInfo, &Crypto_xVIx_xAIx_SecondaryJob_JobPrimitiveInfo, sizeof(Crypto_JobPrimitiveInfoType)); \
  TS_MemCpy(&workspace->secondaryJob_jobInfo,          &Crypto_xVIx_xAIx_SecondaryJob_JobInfo,          sizeof(Crypto_JobInfoType)         ); \
  TS_MemCpy(&workspace->secondaryJob,                  &Crypto_xVIx_xAIx_SecondaryJob,                  sizeof(Crypto_JobType)             ); \
  workspace->secondaryJob_jobPrimitiveInfo.primitiveInfo = (Crypto_PrimitiveInfoType *)&workspace->secondaryJob_primitiveInfo;                \
  workspace->secondaryJob.jobPrimitiveInfo               = &workspace->secondaryJob_jobPrimitiveInfo;                                         \
  workspace->secondaryJob.jobInfo                        = &workspace->secondaryJob_jobInfo;                                                  \
}                                                                                                                                             \
while (0U)

#if (defined CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_KEY)
#error CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_KEY is already defined
#endif
/** \brief  This macro sets the secondary job key used for processing. **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_KEY,1 */
#define CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_KEY()                                                \
do                                                                                              \
{                                                                                               \
  TS_MemCpy(&workspace->secondaryJob_primitiveInfo.algorithm.keyLength,                         \
            &job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength,                         \
            sizeof(job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength));                 \
  TS_MemCpy(&workspace->secondaryJob.cryptoKeyId, &job->cryptoKeyId, sizeof(job->cryptoKeyId)); \
}                                                                                               \
while (0U)

#if (defined CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_SRV)
#error CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_SRV is already defined
#endif
/** \brief  This macro sets the secondary job service used for processing. **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_SRV,1 */
#define CRYPTO_XVIX_XAIX_SET_SECONDARY_JOB_SRV()                    \
do                                                                  \
{                                                                   \
  TS_MemCpy(&workspace->secondaryJob_primitiveInfo.service,         \
            &job->jobPrimitiveInfo->primitiveInfo->service,         \
            sizeof(job->jobPrimitiveInfo->primitiveInfo->service)); \
}                                                                   \
while (0U)

[!ENDIF!]
[!IF "$CreateDefaultRandomJobTemplates = 'true'"!]
#if (defined CRYPTO_XVIX_XAIX_SET_DEFAULTRANDOM_JOB)
#error CRYPTO_XVIX_XAIX_SET_DEFAULTRANDOM_JOB is already defined
#endif
/** \brief  This macro sets the default random job used for processing. **/
/* !LINKSTO Crypto.Dsn.Api/Macros/CRYPTO_XVIX_XAIX_SET_DEFAULTRANDOM_JOB,1 */
#define CRYPTO_XVIX_XAIX_SET_DEFAULTRANDOM_JOB()                                                                                                  \
do                                                                                                                                                \
{                                                                                                                                                 \
  TS_MemCpy(&workspace->defaultRandomJob_primitiveInfo,    &Crypto_xVIx_xAIx_SecondaryJob_PrimitiveInfo,    sizeof(Crypto_PrimitiveInfoType)   ); \
  TS_MemCpy(&workspace->defaultRandomJob_jobPrimitiveInfo, &Crypto_xVIx_xAIx_SecondaryJob_JobPrimitiveInfo, sizeof(Crypto_JobPrimitiveInfoType)); \
  TS_MemCpy(&workspace->defaultRandomJob_jobInfo,          &Crypto_xVIx_xAIx_SecondaryJob_JobInfo,          sizeof(Crypto_JobInfoType)         ); \
  TS_MemCpy(&workspace->defaultRandomJob,                  &Crypto_xVIx_xAIx_SecondaryJob,                  sizeof(Crypto_JobType)             ); \
  workspace->defaultRandomJob_jobPrimitiveInfo.primitiveInfo = (Crypto_PrimitiveInfoType *)&workspace->defaultRandomJob_primitiveInfo;                                        \
  workspace->defaultRandomJob.jobPrimitiveInfo               = &workspace->defaultRandomJob_jobPrimitiveInfo;                                     \
  workspace->defaultRandomJob.jobInfo                        = &workspace->defaultRandomJob_jobInfo;                                              \
}                                                                                                                                                 \
while (0U)

[!ENDIF!]
[!//
#if (defined CRYPTO_XVIX_XAIX_KDF_ALGORITHMLIST_MAXLEN)
#error CRYPTO_XVIX_XAIX_KDF_ALGORITHMLIST_MAXLEN is already defined
#endif
/** \brief Macro representing the maximum len of the supporting key derived algorithm list
 **/
#define CRYPTO_XVIX_XAIX_KDF_ALGORITHMLIST_MAXLEN 9U

#if (defined CRYPTO_XVIX_XAIX_KDF_PRIMITIVELIST_MAXLEN)
#error CRYPTO_XVIX_XAIX_KDF_PRIMITIVELIST_MAXLEN is already defined
#endif
/** \brief Macro representing the maximum len of the supporting key derived primitive list
 **/
#define CRYPTO_XVIX_XAIX_KDF_PRIMITIVELIST_MAXLEN 1U

#if (defined CRYPTO_XVIX_XAIX_KDF_CONFIGIFCLIST_MAXLEN)
#error CRYPTO_XVIX_XAIX_KDF_CONFIGIFCLIST_MAXLEN is already defined
#endif
/** \brief Macro representing the maximum len of the configured key derived interface list
 **/
#define CRYPTO_XVIX_XAIX_KDF_CONFIGIFCLIST_MAXLEN 9U

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * constants related to general and nonrecurring descriptions of crypto primitives assigned to
 * crypto driver objects
 */

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_PTR
#include <Crypto_xVIx_xAIx_MemMap.h>

[!FOR "i" = "1" TO "$PrimitivesPoolListSize"!]
  [!VAR "pss" = "text:split(string(text:split($PrimitivesPoolListShrt)[position() = $i]), '_')[position() = 1]"!]
  [!VAR "pfs" = "text:split(string(text:split($PrimitivesPoolListShrt)[position() = $i]), '_')[position() = 2]"!]
  [!VAR "pms" = "text:split(string(text:split($PrimitivesPoolListShrt)[position() = $i]), '_')[position() = 3]"!]
/** \brief  Structure containing the constant internal description of a crypto primitive [!"$pss"!]_[!"$pfs"!]_[!"$pms"!]
 **/
  [!CALL "GetReqs_Crypto_xVIx_xAIx_CPr_SRV_FAM_MOD", "pri" = "concat($pss,'_',$pfs,'_',$pms)"!]
extern CONST(Crypto_xVIx_xAIx_PrimitiveDescriptionType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CPr_[!"$pss"!]_[!"$pfs"!]_[!"$pms"!];

[!ENDFOR!]
[!//
#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_PTR
#include <Crypto_xVIx_xAIx_MemMap.h>

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * macros generally related to Crypto Driver Object
 */

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_PTR
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  List of all configured Crypto Driver Objects
 **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CDOs/0001,1 */
extern CONST(Crypto_xVIx_xAIx_CDOType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CDOs[CRYPTO_XVIX_XAIX_CDO_COUNT];

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_PTR
#include <Crypto_xVIx_xAIx_MemMap.h>

[!IF "node:exists(CryptoKeys)"!]
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * macros generally related to crypto keys
 */

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_PTR
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief List of all configured Keys **/
/* !LINKSTO Crypto.Dsn.Gen/KMn_GenerationPhase/0002,2 */
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_Keys/0001,1 */
extern CONST(Crypto_xVIx_xAIx_KeyType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_Keys[CRYPTO_XVIX_XAIX_KEY_COUNT];

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_PTR
#include <Crypto_xVIx_xAIx_MemMap.h>
[!ENDIF!]

[!VAR "CreateKeyDeriveConfigData" = "'false'"!]
[!LOOP "util:distinct(node:order(CryptoEbGeneral/CryptoEbMisc/CryptoEbKeyManagementAlgorithm/eb-list::*))"!]
  [!IF "node:value(.) = 'CRYPTO_KMN_KEYDERIVE_SINGLESTEPKDF_NOTSET'"!]
    [!VAR "CreateKeyDeriveConfigData" = "'true'"!]
  [!ENDIF!]
[!ENDLOOP!]
[!IF "$CreateKeyDeriveConfigData = 'true'"!]
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * constants related to key derive primitives
 */

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_PTR
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief List of all configured support key derived primitives
 **/
extern CONST(Crypto_PrimitiveInfoType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_Int_KDF_SupportedPrimitives[CRYPTO_XVIX_XAIX_KDF_ALGORITHMLIST_MAXLEN];

/** \brief List of all configured support key derived process
 **/
extern CONST(Crypto_xVIx_xAIx_KDFPrimitivesFcnPtrType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_Int_KDF_Primitives[CRYPTO_XVIX_XAIX_KDF_PRIMITIVELIST_MAXLEN];

/** \brief List of all configured support key derived interface
 **/
extern CONST(Crypto_xVIx_xAIx_KDFPrimitivesConfig_Type, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_Int_KDF_ConfigKmnInterface[CRYPTO_XVIX_XAIX_KDF_ALGORITHMLIST_MAXLEN];

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_PTR
#include <Crypto_xVIx_xAIx_MemMap.h>

[!ENDIF!]
/*==================[external data]===============================================================*/
[!//
[!LOOP "util:distinct(node:order(CryptoDriverObjects/CryptoDriverObject/eb-list::*, 'node:value(CryptoDriverObjectId)'))"!]
  [!CALL "GetCryptoDriverObjectPrimitivesList", "cdo" = "node:path(node:current())"!]

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * variables related to cryptographic primitives of the specific
 * Crypto Driver Object '[!"node:pos(.)"!] - [!"node:name(.)"!]'
 */

/* ~ ~ ~ primitive run-time datas ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

#define CRYPTO_xVIx_xAIx_START_SEC_VAR_INIT_PTR
#include <Crypto_xVIx_xAIx_MemMap.h>

  [!IF "node:exists(./CryptoDefaultRandomPrimitiveRef)"!]
    [!VAR "r1s" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR1Shrt, '_')[position() = 1]"!]
    [!VAR "r1f" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR1Shrt, '_')[position() = 2]"!]
    [!VAR "r1m" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR1Shrt, '_')[position() = 3]"!]
/** \brief  Global variable that represents the run-time data of the primary primitive
 **         of the default random primitive '[!"$r1s"!]_[!"$r1f"!]_[!"$r1m"!]'
 **         of the specific crypto driver object '[!"node:name(.)"!]'.
 **/
/* !LINKSTO Crypto.Dsn.Api/Data/Crypto_xVIx_xAIx_CDO_CDO_R1Data_SRV_FAM_MOD/0001,1 */
extern VAR(Crypto_xVIx_xAIx_CDOPrimitiveDataType, CRYPTO_xVIx_xAIx_APPL_DATA) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_R1Data_[!"$r1s"!]_[!"$r1f"!]_[!"$r1m"!];

    [!IF "num:i(0) < $CryptoDriverObjectPrimitivesListRealTrimR2Size"!]
      [!VAR "r2s" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR2Shrt, '_')[position() = 1]"!]
      [!VAR "r2f" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR2Shrt, '_')[position() = 2]"!]
      [!VAR "r2m" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR2Shrt, '_')[position() = 3]"!]
/** \brief  Global variable that represents the run-time data of the secondary primitive
 **         of the default random primitive '[!"$r2s"!]_[!"$r2f"!]_[!"$r2m"!]'
 **         of the specific crypto driver object '[!"node:name(.)"!]'.
 **/
/* !LINKSTO Crypto.Dsn.Api/Data/Crypto_xVIx_xAIx_CDO_CDO_R2Data_SRV_FAM_MOD/0001,1 */
extern VAR(Crypto_xVIx_xAIx_CDOPrimitiveDataType, CRYPTO_xVIx_xAIx_APPL_DATA) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_R2Data_[!"$r2s"!]_[!"$r2f"!]_[!"$r2m"!];

    [!ENDIF!]
  [!ENDIF!]
  [!FOR "i" = "1" TO "$CryptoDriverObjectPrimitivesListRealTrimP1Size"!]
    [!VAR "p1s" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealTrimP1Shrt)[position() = $i]), '_')[position() = 1]"!]
    [!VAR "p1f" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealTrimP1Shrt)[position() = $i]), '_')[position() = 2]"!]
    [!VAR "p1m" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealTrimP1Shrt)[position() = $i]), '_')[position() = 3]"!]
/** \brief  Global constant that represents the run-time data of the specific primary
 **         primitive '[!"$p1s"!]_[!"$p1f"!]_[!"$p1m"!]'
 **         of the specific crypto driver object '[!"node:name(.)"!]'.
 **/
/* !LINKSTO Crypto.Dsn.Api/Data/Crypto_xVIx_xAIx_CDO_CDO_P1Data_SRV_FAM_MOD/0001,1 */
extern VAR(Crypto_xVIx_xAIx_CDOPrimitiveDataType, CRYPTO_xVIx_xAIx_APPL_DATA) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P1Data_[!"$p1s"!]_[!"$p1f"!]_[!"$p1m"!];

  [!ENDFOR!]
  [!FOR "i" = "1" TO "$CryptoDriverObjectPrimitivesListRealTrimP2Size"!]
    [!VAR "p2s" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealTrimP2Shrt)[position() = $i]), '_')[position() = 1]"!]
    [!VAR "p2f" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealTrimP2Shrt)[position() = $i]), '_')[position() = 2]"!]
    [!VAR "p2m" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealTrimP2Shrt)[position() = $i]), '_')[position() = 3]"!]
/** \brief  Global constant that represents the run-time data of the specific secondary
 **         primitive '[!"$p2s"!]_[!"$p2f"!]_[!"$p2m"!]'
 **         of the specific crypto driver object '[!"node:name(.)"!]'.
 **/
/* !LINKSTO Crypto.Dsn.Api/Data/Crypto_xVIx_xAIx_CDO_CDO_P2Data_SRV_FAM_MOD/0001,1 */
extern VAR(Crypto_xVIx_xAIx_CDOPrimitiveDataType, CRYPTO_xVIx_xAIx_APPL_DATA) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P2Data_[!"$p2s"!]_[!"$p2f"!]_[!"$p2m"!];

  [!ENDFOR!]
#define CRYPTO_xVIx_xAIx_STOP_SEC_VAR_INIT_PTR
#include <Crypto_xVIx_xAIx_MemMap.h>

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * variables related to the specific Crypto Driver Object '[!"node:pos(.)"!] - [!"node:name(.)"!]'
 */

/* ~ ~ ~ crypto driver object run-time datas  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

#define CRYPTO_xVIx_xAIx_START_SEC_VAR_INIT_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  Global variable that represents the run-time data of the specific
 **         crypto driver object '[!"node:name(.)"!]'.
 **/
/* !LINKSTO Crypto.Dsn.Api/Data/Crypto_xVIx_xAIx_CDOData_CDO/0001,1 */
extern VAR(Crypto_xVIx_xAIx_CDODataType, CRYPTO_xVIx_xAIx_APPL_DATA) Crypto_xVIx_xAIx_CDOData_[!"node:name(.)"!];

#define CRYPTO_xVIx_xAIx_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/* ~ ~ ~ crypto driver object workspaces  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

#define CRYPTO_xVIx_xAIx_START_SEC_VAR_CLEARED_[!CALL "GetWorkspacesMemMapAlignment"!]
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  Global array that represents the workspace of the specific crypto driver object
 **         '[!"node:name(.)"!]' that is intended to hold the context
 **         of a currently executed primary primitive.
 **/
/* !LINKSTO Crypto.Dsn.Api/Data/Crypto_xVIx_xAIx_CDO_CDO_P1Wksp/0001,1 */
extern VAR(uint[!"ecu:get('Cpu.Type')"!], CRYPTO_xVIx_xAIx_APPL_DATA) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P1Wksp[CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P1WKSP_SIZE_WORDS];

  [!IF "num:i(0) < $CryptoDriverObjectPrimitivesListRealFullP2Size"!]
/** \brief  Global array that represents the workspace of the specific crypto driver object
 **         '[!"node:name(.)"!]' that is intended to hold the context
 **         of a currently executed secondary primitive.
 **/
/* !LINKSTO Crypto.Dsn.Api/Data/Crypto_xVIx_xAIx_CDO_CDO_P2Wksp/0001,1 */
extern VAR(uint[!"ecu:get('Cpu.Type')"!], CRYPTO_xVIx_xAIx_APPL_DATA) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P2Wksp[CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P2WKSP_SIZE_WORDS];

  [!ENDIF!]
  [!IF "node:exists(./CryptoEbPrimaryHeapSize)"!]
/** \brief  Global array that represents the heap buffer of the specific crypto driver object
 **         '[!"node:name(.)"!]' that is intended to hold the context
 **         of a currently executed primary primitive.
 **/
/* !LINKSTO Crypto.Dsn.Api/Data/Crypto_xVIx_xAIx_CDO_CDO_P1Heap/0001,1 */
extern VAR(uint[!"ecu:get('Cpu.Type')"!], CRYPTO_xVIx_xAIx_APPL_DATA) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P1Heap[CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P1HEAP_SIZE_WORDS];

  [!ENDIF!]
  [!IF "num:i(0) < $CryptoDriverObjectPrimitivesListRealFullP2Size"!]
    [!IF "node:exists(./CryptoEbSecondaryHeapSize)"!]
/** \brief  Global array that represents the heap buffer of the specific crypto driver object
 **         '[!"node:name(.)"!]' that is intended to hold the context
 **         of a currently executed secondary primitive.
 **/
/* !LINKSTO Crypto.Dsn.Api/Data/Crypto_xVIx_xAIx_CDO_CDO_P2Heap/0001,1 */
extern VAR(uint[!"ecu:get('Cpu.Type')"!], CRYPTO_xVIx_xAIx_APPL_DATA) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P2Heap[CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P2HEAP_SIZE_WORDS];

    [!ENDIF!]
  [!ENDIF!]
  [!IF "node:exists(./CryptoDefaultRandomPrimitiveRef)"!]
/** \brief  Global array that represents the workspace of the specific crypto driver object
 **         '[!"node:name(.)"!]' that is intended to hold the context
 **         of the primary primitive of the default random primitive of this crypto driver object.
 **/
/* !LINKSTO Crypto.Dsn.Api/Data/Crypto_xVIx_xAIx_CDO_CDO_R1Wksp/0001,1 */
extern VAR(uint[!"ecu:get('Cpu.Type')"!], CRYPTO_xVIx_xAIx_APPL_DATA) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_R1Wksp[CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_R1WKSP_SIZE_WORDS];

    [!IF "num:i(0) < $CryptoDriverObjectPrimitivesListRealTrimR2Size"!]
/** \brief  Global array that represents the workspace of the specific crypto driver object
 **         '[!"node:name(.)"!]' that is intended to hold the context
 **         of the secondary primitive of the default random primitive of this crypto driver object.
 **/
/* !LINKSTO Crypto.Dsn.Api/Data/Crypto_xVIx_xAIx_CDO_CDO_R2Wksp/0001,1 */
extern VAR(uint[!"ecu:get('Cpu.Type')"!], CRYPTO_xVIx_xAIx_APPL_DATA) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_R2Wksp[CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_R2WKSP_SIZE_WORDS];

    [!ENDIF!]
  [!ENDIF!]
#define CRYPTO_xVIx_xAIx_STOP_SEC_VAR_CLEARED_[!CALL "GetWorkspacesMemMapAlignment"!]
#include <Crypto_xVIx_xAIx_MemMap.h>
[!ENDLOOP!]

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * variables related to crypto keys
 */

[!LOOP "util:distinct(node:order(CryptoKeys/CryptoKey/eb-list::*, 'node:value(CryptoKeyId)'))"!]
/* variables related specific to Crypto Key '[!"node:name(.)"!]' */
  [!VAR "keyName" = "node:name(.)"!]

#define CRYPTO_xVIx_xAIx_START_SEC_VAR_INIT_[!CALL "GetWorkspacesMemMapAlignment"!]

#include <Crypto_xVIx_xAIx_MemMap.h>
  [!SELECT "./CryptoKeyTypeRef"!]
    [!LOOP "util:distinct(node:order(as:ref(.)/CryptoKeyElementRef/eb-list::*, 'node:value(as:ref(.)/CryptoKeyElementId)'))"!]

/** \brief Buffer for storing the dynamic data of the Crypto key **/
extern VAR(uint[!"ecu:get('Cpu.Type')"!], CRYPTO_xVIx_xAIx_VAR) Crypto_xVIx_xAIx_KMn_KeyElementDataArray_[!"node:name(as:ref(.))"!]_[!"$keyName"!][([!"node:value(as:ref(.)/CryptoKeyElementSize)"!] + [!"$WordWidthInBytes"!] - 1) / [!"$WordWidthInBytes"!]];
    [!ENDLOOP!]

#define CRYPTO_xVIx_xAIx_STOP_SEC_VAR_INIT_[!CALL "GetWorkspacesMemMapAlignment"!]
#include <Crypto_xVIx_xAIx_MemMap.h>

#define CRYPTO_xVIx_xAIx_START_SEC_VAR_INIT_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>
    [!LOOP "util:distinct(node:order(as:ref(.)/CryptoKeyElementRef/eb-list::*, 'node:value(as:ref(.)/CryptoKeyElementId)'))"!]

extern VAR(Crypto_xVIx_xAIx_KeyElementDataType, CRYPTO_xVIx_xAIx_VAR) Crypto_xVIx_xAIx_KMn_KeyElementData_[!"node:name(as:ref(.))"!]_[!"$keyName"!];
    [!ENDLOOP!]
  [!ENDSELECT!]

extern VAR(Crypto_xVIx_xAIx_KeyDataType, CRYPTO_xVIx_xAIx_VAR) Crypto_xVIx_xAIx_KMn_KeyData_[!"node:name(.)"!];

#define CRYPTO_xVIx_xAIx_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

[!ENDLOOP!]
/*==================[external function declarations]==============================================*/

/*================================================================================================*/

#endif /* #ifndef CRYPTO_XVIX_XAIX_INT_CFG_H */

/*==================[end of file]=================================================================*/

