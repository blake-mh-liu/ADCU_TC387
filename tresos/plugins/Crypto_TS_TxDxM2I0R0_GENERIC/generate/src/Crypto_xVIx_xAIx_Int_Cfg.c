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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Cfg.c/0001,1 */
[!AUTOSPACING!]
[!/*========================================================================================*/!][!//
[!INCLUDE "../include/Crypto_xVIx_xAIx_Macros.m"!]
[!IF "ecu:has('Cpu.Type')"!]
  [!VAR "WordWidthInBytes" = "bit:shr(ecu:get('Cpu.Type'), 3)"!]
[!ELSE!]
  [!ERROR "It is not possible to determine the 'Cpu.Type'."!]
[!ENDIF!]
[!//
[!VAR "CreateSecondaryJobTemplates" = "'false'"!]
[!VAR "CreateDefaultRandomJobTemplates" = "'false'"!]
[!CALL "GetPrimitivesPoolList", "ctr" = "node:path(CryptoDriverObjects)"!]
[!/*========================================================================================*/!][!//

/*==================[deviations]==================================================================*/

/* MISRA-C:2012 Deviation List
*
* MISRAC2012-1) Deviated Rule: 2.1 (required)
* A project shall not contain unreachable code.
*
* Reason:
* Problems could arise on little and big endian platform. But tests are successful on little and
* big endian platform.
*/

/*==================[includes]====================================================================*/

#include <Crypto_xVIx_xAIx_Int.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_Int_Cfg.c/0002,1 */

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[internal function declarations]==============================================*/

/*==================[internal constants]==========================================================*/
[!VAR "CreateKeyDeriveConfigData" = "'false'"!]
[!LOOP "util:distinct(node:order(CryptoEbGeneral/CryptoEbMisc/CryptoEbKeyManagementAlgorithm/eb-list::*))"!]
  [!IF "node:value(.) = 'CRYPTO_KMN_KEYDERIVE_SINGLESTEPKDF_NOTSET'"!]
    [!VAR "CreateKeyDeriveConfigData" = "'true'"!]
  [!ENDIF!]
[!ENDLOOP!]
[!IF "$CreateKeyDeriveConfigData = 'true'"!]
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * constants related to key derived primitives
 */

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_PTR
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief List of all configured support key derived primitives
 **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_Int_KDF_SupportedPrimitives/0001,1 */
CONST(Crypto_PrimitiveInfoType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_Int_KDF_SupportedPrimitives[CRYPTO_XVIX_XAIX_KDF_ALGORITHMLIST_MAXLEN] =
{
  {20U, CRYPTO_HASH, {CRYPTO_ALGOFAM_SHA1    , CRYPTO_ALGOFAM_NOT_SET, 0U, CRYPTO_ALGOFAM_NOT_SET}},
  {28U, CRYPTO_HASH, {CRYPTO_ALGOFAM_SHA2_224, CRYPTO_ALGOFAM_NOT_SET, 0U, CRYPTO_ALGOFAM_NOT_SET}},
  {32U, CRYPTO_HASH, {CRYPTO_ALGOFAM_SHA2_256, CRYPTO_ALGOFAM_NOT_SET, 0U, CRYPTO_ALGOFAM_NOT_SET}},
  {48U, CRYPTO_HASH, {CRYPTO_ALGOFAM_SHA2_384, CRYPTO_ALGOFAM_NOT_SET, 0U, CRYPTO_ALGOFAM_NOT_SET}},
  {64U, CRYPTO_HASH, {CRYPTO_ALGOFAM_SHA2_512, CRYPTO_ALGOFAM_NOT_SET, 0U, CRYPTO_ALGOFAM_NOT_SET}},
  {28U, CRYPTO_HASH, {CRYPTO_ALGOFAM_SHA3_224, CRYPTO_ALGOFAM_NOT_SET, 0U, CRYPTO_ALGOFAM_NOT_SET}},
  {32U, CRYPTO_HASH, {CRYPTO_ALGOFAM_SHA3_256, CRYPTO_ALGOFAM_NOT_SET, 0U, CRYPTO_ALGOFAM_NOT_SET}},
  {48U, CRYPTO_HASH, {CRYPTO_ALGOFAM_SHA3_384, CRYPTO_ALGOFAM_NOT_SET, 0U, CRYPTO_ALGOFAM_NOT_SET}},
  {64U, CRYPTO_HASH, {CRYPTO_ALGOFAM_SHA3_512, CRYPTO_ALGOFAM_NOT_SET, 0U, CRYPTO_ALGOFAM_NOT_SET}}
};

/** \brief List of all configured support key derived process
 **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_Int_KDF_Primitives/0001,1 */
CONST(Crypto_xVIx_xAIx_KDFPrimitivesFcnPtrType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_Int_KDF_Primitives[CRYPTO_XVIX_XAIX_KDF_PRIMITIVELIST_MAXLEN] =
{
  Crypto_xVIx_xAIx_Int_KMn_KEYDERIVE_SINGLESTEPKDF_NOTSET_Process
};

/** \brief List of all configured support key derived interface
 **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_Int_KDF_ConfigKmnInterface/0001,1 */
CONST(Crypto_xVIx_xAIx_KDFPrimitivesConfig_Type, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_Int_KDF_ConfigKmnInterface[CRYPTO_XVIX_XAIX_KDF_CONFIGIFCLIST_MAXLEN] =
{
  /*1st Job Primitive, 2nd Job Primitive, KeyDerive Jobs length, KeyDerive Process Function Index*/
  {{{0u, 20U},{255U,0U}}, 1U, 0U},/*SingleStep KDF Hash(x) CRYPTO_ALGOFAM_SHA1*/
  {{{1u, 28U},{255U,0U}}, 1U, 0U},/*SingleStep KDF Hash(x) CRYPTO_ALGOFAM_SHA2_224*/
  {{{2u, 32U},{255U,0U}}, 1U, 0U},/*SingleStep KDF Hash(x) CRYPTO_ALGOFAM_SHA2_256*/
  {{{3u, 48U},{255U,0U}}, 1U, 0U},/*SingleStep KDF Hash(x) CRYPTO_ALGOFAM_SHA2_384*/
  {{{4u, 64U},{255U,0U}}, 1U, 0U},/*SingleStep KDF Hash(x) CRYPTO_ALGOFAM_SHA2_512*/
  {{{5u, 28U},{255U,0U}}, 1U, 0U},/*SingleStep KDF Hash(x) CRYPTO_ALGOFAM_SHA3_224*/
  {{{6u, 32U},{255U,0U}}, 1U, 0U},/*SingleStep KDF Hash(x) CRYPTO_ALGOFAM_SHA3_256*/
  {{{7u, 48U},{255U,0U}}, 1U, 0U},/*SingleStep KDF Hash(x) CRYPTO_ALGOFAM_SHA3_384*/
  {{{8u, 64U},{255U,0U}}, 1U, 0U} /*SingleStep KDF Hash(x) CRYPTO_ALGOFAM_SHA3_512*/
};

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_PTR
#include <Crypto_xVIx_xAIx_MemMap.h>

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
 * constants related to cryptographic primitives of the specific
 * Crypto Driver Object '[!"node:pos(.)"!] - [!"node:name(.)"!]'
 */

/* ~ ~ ~ primitive link-time configurations ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_PTR
#include <Crypto_xVIx_xAIx_MemMap.h>

  [!IF "node:exists(./CryptoDefaultRandomPrimitiveRef)"!]
    [!VAR "r1s" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR1Shrt, '_')[position() = 1]"!]
    [!VAR "r1f" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR1Shrt, '_')[position() = 2]"!]
    [!VAR "r1m" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR1Shrt, '_')[position() = 3]"!]
/** \brief  Global constant that represents the link-time configuration of the primary primitive
 **         of the default random primitive '[!"$r1s"!]_[!"$r1f"!]_[!"$r1m"!]'
 **         of the specific crypto driver object '[!"node:name(.)"!]'.
 **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CDO_CDO_R1Cnfg_SRV_FAM_MOD/0001,1 */
static CONST(Crypto_xVIx_xAIx_CDOPrimitiveCnfgType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_R1Cnfg_[!"$r1s"!]_[!"$r1f"!]_[!"$r1m"!] =
{
  [!/* description   */!]&Crypto_xVIx_xAIx_CPr_[!"$r1s"!]_[!"$r1f"!]_[!"$r1m"!],
  [!/* workspace     */!]&Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_R1Wksp,
  [!/* workspaceSize */!] CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_R1WKSP_SIZE_BYTES,
  [!/* heap          */!] NULL_PTR,
  [!/* heapSize      */!] 0U
};

    [!IF "num:i(0) < $CryptoDriverObjectPrimitivesListRealTrimR2Size"!]
      [!VAR "r2s" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR2Shrt, '_')[position() = 1]"!]
      [!VAR "r2f" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR2Shrt, '_')[position() = 2]"!]
      [!VAR "r2m" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR2Shrt, '_')[position() = 3]"!]
/** \brief  Global constant that represents the link-time configuration of the secondary primitive
 **         of the default random primitive '[!"$r2s"!]_[!"$r2f"!]_[!"$r2m"!]'
 **         of the specific crypto driver object '[!"node:name(.)"!]'.
 **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CDO_CDO_R2Cnfg_SRV_FAM_MOD/0001,1 */
static CONST(Crypto_xVIx_xAIx_CDOPrimitiveCnfgType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_R2Cnfg_[!"$r2s"!]_[!"$r2f"!]_[!"$r2m"!] =
{
  [!/* description   */!]&Crypto_xVIx_xAIx_CPr_[!"$r2s"!]_[!"$r2f"!]_[!"$r2m"!],
  [!/* workspace     */!]&Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_R2Wksp,
  [!/* workspaceSize */!] CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_R2WKSP_SIZE_BYTES,
  [!/* heap          */!] NULL_PTR,
  [!/* heapSize      */!] 0U
};

    [!ENDIF!]
  [!ENDIF!]
  [!FOR "i" = "1" TO "$CryptoDriverObjectPrimitivesListRealTrimP1Size"!]
    [!VAR "p1s" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealTrimP1Shrt)[position() = $i]), '_')[position() = 1]"!]
    [!VAR "p1f" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealTrimP1Shrt)[position() = $i]), '_')[position() = 2]"!]
    [!VAR "p1m" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealTrimP1Shrt)[position() = $i]), '_')[position() = 3]"!]
/** \brief  Global constant that represents the link-time configuration of the specific primary
 **         primitive '[!"$p1s"!]_[!"$p1f"!]_[!"$p1m"!]'
 **         of the specific crypto driver object '[!"node:name(.)"!]'.
 **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CDO_CDO_P1Cnfg_SRV_FAM_MOD/0001,1 */
static CONST(Crypto_xVIx_xAIx_CDOPrimitiveCnfgType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P1Cnfg_[!"$p1s"!]_[!"$p1f"!]_[!"$p1m"!] =
{
  /* Deviation MISRAC2012-1 <START> */
  [!/* description   */!]&Crypto_xVIx_xAIx_CPr_[!"$p1s"!]_[!"$p1f"!]_[!"$p1m"!],
  [!/* workspace     */!]&Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P1Wksp,
  [!/* workspaceSize */!] CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P1WKSP_SIZE_BYTES,
  [!IF "node:exists(./CryptoEbPrimaryHeapSize)"!]
  [!/* heap          */!]&Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P1Heap,
  [!ELSE!]
  [!/* heap          */!] NULL_PTR,
  [!ENDIF!]
  [!/* heapSize      */!] CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P1HEAP_SIZE_BYTES
  /* Deviation MISRAC2012-1 <STOP> */
};

  [!ENDFOR!]
  [!FOR "i" = "1" TO "$CryptoDriverObjectPrimitivesListRealTrimP2Size"!]
    [!VAR "p2s" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealTrimP2Shrt)[position() = $i]), '_')[position() = 1]"!]
    [!VAR "p2f" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealTrimP2Shrt)[position() = $i]), '_')[position() = 2]"!]
    [!VAR "p2m" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealTrimP2Shrt)[position() = $i]), '_')[position() = 3]"!]
/** \brief  Global constant that represents the link-time configuration of the specific secondary
 **         primitive '[!"$p2s"!]_[!"$p2f"!]_[!"$p2m"!]'
 **         of the specific crypto driver object '[!"node:name(.)"!]'.
 **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CDO_CDO_P2Cnfg_SRV_FAM_MOD/0001,1 */
static CONST(Crypto_xVIx_xAIx_CDOPrimitiveCnfgType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P2Cnfg_[!"$p2s"!]_[!"$p2f"!]_[!"$p2m"!] =
{
  /* Deviation MISRAC2012-1 <START> */
  [!/* description   */!]&Crypto_xVIx_xAIx_CPr_[!"$p2s"!]_[!"$p2f"!]_[!"$p2m"!],
  [!/* workspace     */!]&Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P2Wksp,
  [!/* workspaceSize */!] CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P2WKSP_SIZE_BYTES,
  [!IF "node:exists(./CryptoEbSecondaryHeapSize)"!]
  [!/* heap          */!]&Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P2Heap,
  [!ELSE!]
  [!/* heap          */!] NULL_PTR,
  [!ENDIF!]
  [!/* heapSize      */!] CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P2HEAP_SIZE_BYTES
  /* Deviation MISRAC2012-1 <STOP> */
};

  [!ENDFOR!]
/* ~ ~ ~ compositions of secondary and default random primitive configurations  ~ ~ ~ ~ ~ ~ ~ ~ ~ */

  [!IF "node:exists(./CryptoDefaultRandomPrimitiveRef)"!]
    [!IF "num:i(0) < $CryptoDriverObjectPrimitivesListRealTrimR2Size"!]
/* Crypto Driver Object secondary primitives of default random */

      [!VAR "r2s" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR2Shrt, '_')[position() = 1]"!]
      [!VAR "r2f" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR2Shrt, '_')[position() = 2]"!]
      [!VAR "r2m" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR2Shrt, '_')[position() = 3]"!]
/** \brief  Global constant that represents the specific secondary primitive
 **         '[!"$r2s"!]_[!"$r2f"!]_[!"$r2m"!]' of the default random primitive
 **         of the specific crypto driver object '[!"node:name(.)"!]'.
 **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CDO_CDO_R2/0001,1 */
static CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_R2_[!"$r2s"!]_[!"$r2f"!]_[!"$r2m"!] =
{
  &Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_R2Cnfg_[!"$r2s"!]_[!"$r2f"!]_[!"$r2m"!],
  &Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_R2Data_[!"$r2s"!]_[!"$r2f"!]_[!"$r2m"!],
   NULL_PTR,
   NULL_PTR
};

    [!ENDIF!]
/* Crypto Driver Object primary primitives of default random */

    [!VAR "r1s" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR1Shrt, '_')[position() = 1]"!]
    [!VAR "r1f" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR1Shrt, '_')[position() = 2]"!]
    [!VAR "r1m" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR1Shrt, '_')[position() = 3]"!]
/** \brief  Global constant that represents the specific primary primitive
 **         '[!"$r1s"!]_[!"$r1f"!]_[!"$r1m"!]' of the default random primitive
 **         of the specific crypto driver object '[!"node:name(.)"!]'.
 **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CDO_CDO_R1/0001,1 */
static CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_R1_[!"$r1s"!]_[!"$r1f"!]_[!"$r1m"!] =
{
  &Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_R1Cnfg_[!"$r1s"!]_[!"$r1f"!]_[!"$r1m"!],
  &Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_R1Data_[!"$r1s"!]_[!"$r1f"!]_[!"$r1m"!],
  [!IF "num:i(0) < $CryptoDriverObjectPrimitivesListRealTrimR2Size"!]
    [!VAR "r2s" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR2Shrt, '_')[position() = 1]"!]
    [!VAR "r2f" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR2Shrt, '_')[position() = 2]"!]
    [!VAR "r2m" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR2Shrt, '_')[position() = 3]"!]
  &Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_R2_[!"$r2s"!]_[!"$r2f"!]_[!"$r2m"!],
  [!ELSE!]
   NULL_PTR,
  [!ENDIF!]
   NULL_PTR
};

  [!ENDIF!]
/* Crypto Driver Object secondary primitives */

  [!FOR "i" = "1" TO "$CryptoDriverObjectPrimitivesListRealTrimP2Size"!]
    [!VAR "p2s" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealTrimP2Shrt)[position() = $i]), '_')[position() = 1]"!]
    [!VAR "p2f" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealTrimP2Shrt)[position() = $i]), '_')[position() = 2]"!]
    [!VAR "p2m" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealTrimP2Shrt)[position() = $i]), '_')[position() = 3]"!]
/** \brief  Global constant that represents the specific secondary primitive
 **         '[!"$p2s"!]_[!"$p2f"!]_[!"$p2m"!]' of the specific
 **         crypto driver object '[!"node:name(.)"!]'.
 **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CDO_CDO_P2/0001,1 */
static CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P2_[!"$p2s"!]_[!"$p2f"!]_[!"$p2m"!] =
{
  &Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P2Cnfg_[!"$p2s"!]_[!"$p2f"!]_[!"$p2m"!],
  &Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P2Data_[!"$p2s"!]_[!"$p2f"!]_[!"$p2m"!],
   NULL_PTR,
    [!IF "node:exists(./CryptoDefaultRandomPrimitiveRef)"!]
      [!VAR "r1s" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR1Shrt, '_')[position() = 1]"!]
      [!VAR "r1f" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR1Shrt, '_')[position() = 2]"!]
      [!VAR "r1m" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR1Shrt, '_')[position() = 3]"!]
  &Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_R1_[!"$r1s"!]_[!"$r1f"!]_[!"$r1m"!]
    [!ELSE!]
   NULL_PTR
    [!ENDIF!]
};

  [!ENDFOR!]
#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_PTR
#include <Crypto_xVIx_xAIx_MemMap.h>

/* ~ ~ ~ cryptographic primitive compositions of primary and secondary primitive configurations ~ */

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_PTR
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  Global constant that represents the list of specific primary primitives
 **         of the specific crypto driver object '[!"node:name(.)"!]'.
 **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CDO_CDO_P1/0001,1 */
static CONST(Crypto_xVIx_xAIx_CDOPrimitiveType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P1[CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_CPR_COUNT] =
{
  [!FOR "i" = "1" TO "$CryptoDriverObjectPrimitivesListRealFullP1Size"!]
    [!VAR "p1s" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealFullP1Shrt)[position() = $i]), '_')[position() = 1]"!]
    [!VAR "p1f" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealFullP1Shrt)[position() = $i]), '_')[position() = 2]"!]
    [!VAR "p1m" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealFullP1Shrt)[position() = $i]), '_')[position() = 3]"!]
    [!VAR "p2s" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealFullP1Shrt)[position() = $i]), '_')[position() = 4]"!]
    [!VAR "p2f" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealFullP1Shrt)[position() = $i]), '_')[position() = 5]"!]
    [!VAR "p2m" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealFullP1Shrt)[position() = $i]), '_')[position() = 6]"!]
  {
    [!/* cnfg */!]&Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P1Cnfg_[!"$p1s"!]_[!"$p1f"!]_[!"$p1m"!],
    [!/* data */!]&Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P1Data_[!"$p1s"!]_[!"$p1f"!]_[!"$p1m"!],
    [!IF "$p2s != '' and $p2f != 'NOTSET' and $p2m != ''"!]
    &Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P2_[!"$p2s"!]_[!"$p2f"!]_[!"$p2m"!],
    [!ELSE!]
     NULL_PTR,
    [!ENDIF!]
    [!IF "node:exists(./CryptoDefaultRandomPrimitiveRef)"!]
    &Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_R1_[!"$r1s"!]_[!"$r1f"!]_[!"$r1m"!]
    [!ELSE!]
     NULL_PTR
    [!ENDIF!]
  }[!//
    [!IF "$i < $CryptoDriverObjectPrimitivesListCnfgFullP1Size"!]
,
    [!ENDIF!]
  [!ENDFOR!]

};

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_PTR
#include <Crypto_xVIx_xAIx_MemMap.h>

[!ENDLOOP!]
[!//
[!LOOP "util:distinct(node:order(CryptoDriverObjects/CryptoDriverObject/eb-list::*, 'node:value(CryptoDriverObjectId)'))"!]
  [!CALL "GetCryptoDriverObjectPrimitivesList", "cdo" = "node:path(node:current())"!]
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * constants related to the specific Crypto Driver Object '[!"node:pos(.)"!] - [!"node:name(.)"!]'
 */

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  Global constant that represents the link-time configuration of the specific
 **         crypto driver object [!"node:name(.)"!].
 **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CDOCnfg_CDO/0001,1 */
static CONST(Crypto_xVIx_xAIx_CDOCnfgType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CDOCnfg_[!"node:name(.)"!] =
{
  [!/* primitiveList       */!]Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P1,
  [!/* primitiveListLength */!]CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_CPR_COUNT,
  [!/* useForKMn           */!][!"text:toupper(node:value(CryptoEbUseForKeyManagement))"!],
[!IF "node:exists(./CryptoDefaultRandomKeyRef)"!]
  [!/* defaultRandomKeyId  */!][!"node:value(node:ref(./CryptoDefaultRandomKeyRef)/CryptoKeyId)"!]U
[!ELSE!]
  [!/* defaultRandomKeyId  */!]CRYPTO_XVIX_XAIX_KEY_EMPTY
[!ENDIF!]
};

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

[!ENDLOOP!]
#define CRYPTO_xVIx_xAIx_START_SEC_CONST_8
#include <Crypto_xVIx_xAIx_MemMap.h>

[!IF "node:exists(CryptoKeys)"!]
/* !LINKSTO Crypto.Dsn.Gen/KMn_GenerationPhase/0002,2 */

/* constants related to KeyElements for all configured Keys. */

[!VAR "KeyElements" = "''"!]
[!LOOP "util:distinct(node:order(CryptoKeys/CryptoKey/eb-list::*, 'node:value(CryptoKeyId)'))"!]
  [!SELECT "./CryptoKeyTypeRef"!]
    [!LOOP "as:ref(.)/CryptoKeyElementRef/eb-list::*"!]
      [!SELECT "node:current()"!]
        [!IF "not(text:match($KeyElements, concat('\b', node:name(as:ref(.)), '\b')))"!]
          [!VAR "KeyElements" = "concat($KeyElements, ' ', node:name(as:ref(.)))"!]
/* !LINKSTO Crypto.Dsn.Gen/KMn_GenerationPhase/0003,1 */
/* !LINKSTO Crypto.Dsn.Gen/KMn_GenerationPhase/0004,1 */
/* !LINKSTO Crypto.Dsn.Gen/KMn_GenerationPhase/0005,1 */
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_KMn_KeyElementInit_KeyElement/0001,1 */
static CONST(uint8, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_KMn_KeyElementInit_[!"node:name(as:ref(.))"!][[!"node:value(as:ref(.)/CryptoKeyElementSize)"!]U] =
{
          [!IF "node:empty(as:ref(.)/CryptoKeyElementInitValue)"!]
  0U
          [!ELSE!]
            [!VAR "SplitLine" = "0"!]
            [!VAR "Counter" = "1"!]
            [!LOOP "text:split(text:replaceAll(node:value(as:ref(.)/CryptoKeyElementInitValue), '\s+', ''), ',')"!]
              [!IF "num:i($SplitLine) = 0"!]
  [!//
              [!ENDIF!]
              [!VAR "SplitLine" = "$SplitLine + 1"!]
              [!VAR "Counter" = "$Counter + 1"!]
[!"."!]U,[!//
              [!IF "num:i($SplitLine) = 8"!]

                [!VAR "SplitLine" = "0"!]
              [!ELSE!]
 [!//
              [!ENDIF!]
            [!ENDLOOP!]
            [!FOR "i" = "$Counter" TO "node:value(as:ref(.)/CryptoKeyElementSize )"!]
              [!IF "num:i($SplitLine) = 0"!]
  [!//
              [!ENDIF!]
              [!VAR "SplitLine" = "$SplitLine + 1"!]
0x00U,[!//
              [!IF "num:i($SplitLine) = 8"!]

                [!VAR "SplitLine" = "0"!]
              [!ELSE!]
 [!//
              [!ENDIF!]
            [!ENDFOR!]
          [!ENDIF!]
};
        [!ENDIF!]
      [!ENDSELECT!]
    [!ENDLOOP!]
  [!ENDSELECT!]
[!ENDLOOP!]
[!ENDIF!]
#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_8
#include <Crypto_xVIx_xAIx_MemMap.h>

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

[!IF "node:exists(CryptoKeys)"!]
/* !LINKSTO Crypto.Dsn.Gen/KMn_GenerationPhase/0002,2 */
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_KMn_KeyElementDescription_KeyElement/0001,1 */
[!VAR "KeyElements" = "''"!]
[!LOOP "util:distinct(node:order(CryptoKeys/CryptoKey/eb-list::*, 'node:value(CryptoKeyId)'))"!]
  [!SELECT "./CryptoKeyTypeRef"!]
    [!LOOP "as:ref(.)/CryptoKeyElementRef/eb-list::*"!]
      [!SELECT "node:current()"!]
        [!IF "not(text:match($KeyElements, concat('\b', node:name(as:ref(.)), '\b')))"!]
          [!VAR "KeyElements" = "concat($KeyElements, ' ', node:name(as:ref(.)))"!]
static CONST(Crypto_xVIx_xAIx_KeyElementDescriptionType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_KMn_KeyElementDescription_[!"node:name(as:ref(.))"!] =
{
  [!"node:value(as:ref(.)/CryptoKeyElementId)"!]U, /* id */
  [!"node:value(as:ref(.)/CryptoKeyElementSize )"!]U, /* maxSize */
  Crypto_xVIx_xAIx_KMn_KeyElementInit_[!"node:name(as:ref(.))"!], /* initValue */
  [!"text:replace(node:value(as:ref(.)/CryptoKeyElementReadAccess), 'CRYPTO_', 'CRYPTO_XVIX_XAIX_')"!], /* readAccess */
  [!"text:replace(node:value(as:ref(.)/CryptoKeyElementWriteAccess), 'CRYPTO_', 'CRYPTO_XVIX_XAIX_')"!], /* writeAccess */
  [!"text:toupper(node:value(as:ref(.)/CryptoKeyElementAllowPartialAccess))"!], /* allowPartialAccess */
  [!"text:toupper(node:value(as:ref(.)/CryptoKeyElementPersist))"!], /* persistent */
  [!"text:replace(node:value(as:ref(.)/CryptoKeyElementFormat), 'CRYPTO_', 'CRYPTO_XVIX_XAIX_')"!] /* format */
};

        [!ENDIF!]
      [!ENDSELECT!]
    [!ENDLOOP!]
  [!ENDSELECT!]
[!ENDLOOP!]
[!ENDIF!]
[!IF "node:exists(CryptoKeys)"!]
/* constants related to KeyElements for every Key. */

/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_KMn_KeyElementCnfg_KeyElement_Key/0001,1 */
[!LOOP "util:distinct(node:order(CryptoKeys/CryptoKey/eb-list::*, 'node:value(CryptoKeyId)'))"!]
  [!VAR "keyName" = "node:name(.)"!]
/* constants related to KeyElements for [!"$keyName"!]. */
  [!SELECT "./CryptoKeyTypeRef"!]
    [!LOOP "util:distinct(node:order(as:ref(.)/CryptoKeyElementRef/eb-list::*, 'node:value(as:ref(.)/CryptoKeyElementId)'))"!]
static CONST(Crypto_xVIx_xAIx_KeyElementCnfgType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_KMn_KeyElementCnfg_[!"node:name(as:ref(.))"!]_[!"$keyName"!] =
{
  &Crypto_xVIx_xAIx_KMn_KeyElementDescription_[!"node:name(as:ref(.))"!] /* commonCnfg */
};
    [!ENDLOOP!]

/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_KMn_KeyElements_Key/0001,1 */
    [!VAR "size" = "num:i(count(as:ref(.)/CryptoKeyElementRef/eb-list::*))"!]
static CONST(Crypto_xVIx_xAIx_KeyElementType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_KMn_KeyElements_[!"$keyName"!][[!"$size"!]U] =
{
    [!VAR "i" = "0"!]
    [!LOOP "util:distinct(node:order(as:ref(.)/CryptoKeyElementRef/eb-list::*, 'node:value(as:ref(.)/CryptoKeyElementId)'))"!]
  {
    &Crypto_xVIx_xAIx_KMn_KeyElementCnfg_[!"node:name(as:ref(.))"!]_[!"$keyName"!], /* cnfg */
    &Crypto_xVIx_xAIx_KMn_KeyElementData_[!"node:name(as:ref(.))"!]_[!"$keyName"!]  /* data */
  }[!//
      [!VAR "i" = "$i + 1"!]
      [!IF "$i < $size"!]
,
      [!ENDIF!]
    [!ENDLOOP!]

};
  [!ENDSELECT!]

/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_KMn_KeyCnfg_Key/0001,1 */
static CONST(Crypto_xVIx_xAIx_KeyCnfgType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_KMn_KeyCnfg_[!"$keyName"!] =
{
  [!"node:value(CryptoKeyDeriveIterations)"!]U, /* keyDeriveIterations */
  [!"num:i(count(node:ref(./CryptoKeyTypeRef)/CryptoKeyElementRef/eb-list::*))"!]U, /* keyElementsCount */
  [!"num:i(count(node:ref(./CryptoKeyTypeRef)/CryptoKeyElementRef/eb-list::*[node:existsAndTrue(as:ref(.)/CryptoKeyElementPersist)]))"!]U, /* persistentKeyElementsCount */
  Crypto_xVIx_xAIx_KMn_KeyElements_[!"$keyName"!] /* keyElements */
};
[!ENDLOOP!]

[!ENDIF!]
#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * constants related to general and non-recurring descriptions of crypto primitives assigned to
 * crypto driver objects
 */

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_PTR
#include <Crypto_xVIx_xAIx_MemMap.h>

[!FOR "i" = "1" TO "$PrimitivesPoolListSize"!]
  [!VAR "pss" = "text:split(string(text:split($PrimitivesPoolListShrt)[position() = $i]), '_')[position() = 1]"!]
  [!VAR "pfs" = "text:split(string(text:split($PrimitivesPoolListShrt)[position() = $i]), '_')[position() = 2]"!]
  [!VAR "pms" = "text:split(string(text:split($PrimitivesPoolListShrt)[position() = $i]), '_')[position() = 3]"!]
  [!VAR "psl" = "concat('CRYPTO_',$pss)"!]
  [!VAR "pfl" = "text:split(string(text:split($PrimitivesPoolListLong)[position() = $i]), '|')[position() = 2]"!]
  [!VAR "pml" = "text:split(string(text:split($PrimitivesPoolListLong)[position() = $i]), '|')[position() = 3]"!]
  [!IF "$pss = 'RANDOM'"!]
    [!VAR "psl" = "concat($psl,'GENERATE')"!]
  [!ENDIF!]
/** \brief  Structure that contains the constant internal configuration of a primitive **/
CONST(Crypto_xVIx_xAIx_PrimitiveDescriptionType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CPr_[!"$pss"!]_[!"$pfs"!]_[!"$pms"!] =
{
  [!/* fcnMain          */!]Crypto_xVIx_xAIx_CPr_[!"$pss"!]_[!"$pfs"!]_[!"$pms"!]_Main,
  [!/* fcnProcess       */!]Crypto_xVIx_xAIx_CPr_[!"$pss"!]_[!"$pfs"!]_[!"$pms"!]_Process,
  [!/* fcnCancel        */!]Crypto_xVIx_xAIx_CPr_[!"$pss"!]_[!"$pfs"!]_[!"$pms"!]_Cancel,
  [!/* fcnReset         */!]Crypto_xVIx_xAIx_CPr_[!"$pss"!]_[!"$pfs"!]_[!"$pms"!]_Reset,
  [!/* fcnRestart       */!]Crypto_xVIx_xAIx_CPr_[!"$pss"!]_[!"$pfs"!]_[!"$pms"!]_Restart,
  [!/* fcnCallback      */!]Crypto_xVIx_xAIx_CPr_[!"$pss"!]_[!"$pfs"!]_[!"$pms"!]_Callback,

  [!/* service          */!][!"$psl"!],
  [!/* family           */!][!"$pfl"!],
  [!/* mode             */!][!"$pml"!]
};

[!ENDFOR!]
[!//
#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_PTR
#include <Crypto_xVIx_xAIx_MemMap.h>

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * macros generally related to Crypto Driver Object
 */

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_PTR
#include <Crypto_xVIx_xAIx_MemMap.h>

/* constant of all Crypto Driver Objects */
/** \brief  Structure which contains the list of all Crypto Driver Objects **/
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_CDOs/0001,1 */
CONST(Crypto_xVIx_xAIx_CDOType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CDOs[CRYPTO_XVIX_XAIX_CDO_COUNT] =
{
[!VAR "i" = "0"!]
[!VAR "size" = "num:i(count(CryptoDriverObjects/CryptoDriverObject/eb-list::*))"!]
[!LOOP "util:distinct(node:order(CryptoDriverObjects/CryptoDriverObject/eb-list::*, 'node:value(CryptoDriverObjectId)'))"!]
  {
    [!/* cnfg */!]&Crypto_xVIx_xAIx_CDOCnfg_[!"node:name(.)"!],
    [!/* data */!]&Crypto_xVIx_xAIx_CDOData_[!"node:name(.)"!]
  }[!//
  [!VAR "i" = "$i + 1"!]
  [!IF "$i < $size"!]
,[!//
  [!ENDIF!]

[!ENDLOOP!]
};

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_PTR
#include <Crypto_xVIx_xAIx_MemMap.h>

[!IF "node:exists(CryptoKeys)"!]
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * macros generally related to crypto keys
 */

#define CRYPTO_xVIx_xAIx_START_SEC_CONST_PTR
#include <Crypto_xVIx_xAIx_MemMap.h>

/* !LINKSTO Crypto.Dsn.Gen/KMn_GenerationPhase/0002,2 */
/* !LINKSTO Crypto.Dsn.Api/Consts/Crypto_xVIx_xAIx_Keys/0001,1 */
CONST(Crypto_xVIx_xAIx_KeyType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_Keys[CRYPTO_XVIX_XAIX_KEY_COUNT] =
{
[!VAR "i" = "0"!]
[!VAR "size" = "num:i(count(CryptoKeys/CryptoKey/eb-list::*))"!]
[!LOOP "util:distinct(node:order(CryptoKeys/CryptoKey/eb-list::*, 'node:value(CryptoKeyId)'))"!]
  {
    &Crypto_xVIx_xAIx_KMn_KeyCnfg_[!"node:name(.)"!], /* cnfg */
    &Crypto_xVIx_xAIx_KMn_KeyData_[!"node:name(.)"!] /* data*/
  }[!//
  [!VAR "i" = "$i + 1"!]
  [!IF "$i < $size"!]
,
  [!ENDIF!]
[!ENDLOOP!]

};

#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_PTR
#include <Crypto_xVIx_xAIx_MemMap.h>

[!ENDIF!]
[!//
#define CRYPTO_xVIx_xAIx_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

[!IF "($CreateSecondaryJobTemplates = 'true') or ($CreateDefaultRandomJobTemplates = 'true')"!]
CONST(Crypto_PrimitiveInfoType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_SecondaryJob_PrimitiveInfo =
{
  0U,                       /* resultLength    */
  CRYPTO_ENCRYPT,           /* service         */
  {                         /* algorithm       */
    CRYPTO_ALGOFAM_AES,     /* family          */
    CRYPTO_ALGOFAM_NOT_SET, /* secondaryFamily */
    0U,                     /* keyLength       */
    CRYPTO_ALGOMODE_ECB     /* mode            */
  }
};

CONST(Crypto_JobPrimitiveInfoType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_SecondaryJob_JobPrimitiveInfo =
{
  CRYPTO_XVIX_XAIX_CBK_EMPTY, /* callbackId                 */
  NULL_PTR,                   /* primitiveInfo              */
  0U,                         /* secureCounterId            */
  0U,                         /* cryIfKeyId                 */
  CRYPTO_PROCESSING_SYNC,     /* processingType             */
  TRUE                        /* callbackUpdateNotification */
};

CONST(Crypto_JobInfoType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_SecondaryJob_JobInfo =
{
  1U, /* jobId       */
  1U  /* jobPriority */
};
CONST(Crypto_JobType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_SecondaryJob =
{
  1U,                               /* jobId                     */
  CRYPTO_JOBSTATE_IDLE,             /* jobState                  */
  {                                 /* jobPrimitiveInputOutput   */
    NULL_PTR,                       /* inputPtr                  */
    0U,                             /* inputLength               */
    NULL_PTR,                       /* secondaryInputPtr         */
    0U,                             /* secondaryInputLength      */
    NULL_PTR,                       /* tertiaryInputPtr          */
    0U,                             /* tertiaryInputLength       */
    NULL_PTR,                       /* outputPtr                 */
    NULL_PTR,                       /* outputLengthPtr           */
    NULL_PTR,                       /* secondaryOutputPtr        */
    NULL_PTR,                       /* secondaryOutputLengthPtr  */
#if (CRYPTO_API_VERSION_431 == CRYPTO_XVIX_XAIX_API_VERSION)
    0U,                             /* input64 */
#endif /* #if (CRYPTO_API_VERSION_431 == CRYPTO_XVIX_XAIX_API_VERSION) */
    NULL_PTR,                       /* verifyPtr                 */
#if (CRYPTO_API_VERSION_EB != CRYPTO_XVIX_XAIX_API_VERSION)
    NULL_PTR,                       /* output64Ptr */
#endif /* #if (CRYPTO_API_VERSION_EB != CRYPTO_XVIX_XAIX_API_VERSION) */
    CRYPTO_OPERATIONMODE_START      /* mode                      */
  },
  NULL_PTR,                         /* jobPrimitiveInfo          */
  NULL_PTR,                         /* jobInfo                   */
  0U                                /* cryptoKeyId               */
};

[!ENDIF!]
#define CRYPTO_xVIx_xAIx_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

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

  [!FOR "i" = "1" TO "$CryptoDriverObjectPrimitivesListRealTrimP1Size"!]
    [!VAR "p1s" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealTrimP1Shrt)[position() = $i]), '_')[position() = 1]"!]
    [!VAR "p1f" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealTrimP1Shrt)[position() = $i]), '_')[position() = 2]"!]
    [!VAR "p1m" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealTrimP1Shrt)[position() = $i]), '_')[position() = 3]"!]
/** \brief  Buffer containing the dynamic data of the primitive **/
/* !LINKSTO Crypto.Dsn.Api/Data/Crypto_xVIx_xAIx_CDO_CDO_P1Data_SRV_FAM_MOD/0001,1 */
VAR(Crypto_xVIx_xAIx_CDOPrimitiveDataType, CRYPTO_xVIx_xAIx_APPL_DATA) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P1Data_[!"$p1s"!]_[!"$p1f"!]_[!"$p1m"!] =
{
  [!/* primitivePrimary */!]NULL_PTR
};

  [!ENDFOR!]
  [!FOR "i" = "1" TO "$CryptoDriverObjectPrimitivesListRealTrimP2Size"!]
    [!VAR "p2s" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealTrimP2Shrt)[position() = $i]), '_')[position() = 1]"!]
    [!VAR "p2f" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealTrimP2Shrt)[position() = $i]), '_')[position() = 2]"!]
    [!VAR "p2m" = "text:split(string(text:split($CryptoDriverObjectPrimitivesListRealTrimP2Shrt)[position() = $i]), '_')[position() = 3]"!]
/** \brief  Buffer containing the dynamic data of the secondary primitive **/
/* !LINKSTO Crypto.Dsn.Api/Data/Crypto_xVIx_xAIx_CDO_CDO_P2Data_SRV_FAM_MOD/0001,1 */
VAR(Crypto_xVIx_xAIx_CDOPrimitiveDataType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P2Data_[!"$p2s"!]_[!"$p2f"!]_[!"$p2m"!] =
{
  [!/* primitiveSecondary */!]NULL_PTR
};

  [!ENDFOR!]
  [!IF "node:exists(./CryptoDefaultRandomPrimitiveRef)"!]
    [!VAR "r1s" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR1Shrt, '_')[position() = 1]"!]
    [!VAR "r1f" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR1Shrt, '_')[position() = 2]"!]
    [!VAR "r1m" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR1Shrt, '_')[position() = 3]"!]
/** \brief  Buffer containing the dynamic data of the random primitive **/
/* !LINKSTO Crypto.Dsn.Api/Data/Crypto_xVIx_xAIx_CDO_CDO_R1Data_SRV_FAM_MOD/0001,1 */
VAR(Crypto_xVIx_xAIx_CDOPrimitiveDataType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_R1Data_[!"$r1s"!]_[!"$r1f"!]_[!"$r1m"!] =
{
  [!/* primitivePrimaryDefaultRandom */!]NULL_PTR
};

    [!IF "num:i(0) < $CryptoDriverObjectPrimitivesListRealTrimR2Size"!]
      [!VAR "r2s" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR2Shrt, '_')[position() = 1]"!]
      [!VAR "r2f" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR2Shrt, '_')[position() = 2]"!]
      [!VAR "r2m" = "text:split($CryptoDriverObjectPrimitivesListRealTrimR2Shrt, '_')[position() = 3]"!]
/** \brief  Buffer containing the dynamic data of the secondary random primitive **/
/* !LINKSTO Crypto.Dsn.Api/Data/Crypto_xVIx_xAIx_CDO_CDO_R2Data_SRV_FAM_MOD/0001,1 */
VAR(Crypto_xVIx_xAIx_CDOPrimitiveDataType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_R2Data_[!"$r2s"!]_[!"$r2f"!]_[!"$r2m"!] =
{
  [!/* primitiveSecondaryDefaultRandom */!]NULL_PTR
};
    [!ENDIF!]
  [!ENDIF!]
#define CRYPTO_xVIx_xAIx_STOP_SEC_VAR_INIT_PTR
#include <Crypto_xVIx_xAIx_MemMap.h>

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * constants related to the specific Crypto Driver Object '[!"node:pos(.)"!] - [!"node:name(.)"!]'
 */

/* ~ ~ ~ crypto driver object run-time datas  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

#define CRYPTO_xVIx_xAIx_START_SEC_VAR_INIT_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

VAR(Crypto_xVIx_xAIx_CDODataType, CRYPTO_xVIx_xAIx_APPL_DATA) Crypto_xVIx_xAIx_CDOData_[!"node:name(.)"!] =
{
  [!/* primitiveCurrent                   */!]NULL_PTR,
  [!/* jobCurrent                         */!]NULL_PTR,
  [!/* state                              */!]CRYPTO_XVIX_XAIX_CDOSTATE_IDLE,
  [!/* jobCurrentIsProcessed              */!]FALSE,
  [!/* jobCurrentSecondaryIsProcessed     */!]FALSE,
  [!/* jobCurrentDefaultRandomIsProcessed */!]FALSE
};

#define CRYPTO_xVIx_xAIx_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/* ~ ~ ~ crypto driver object workspaces  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

#define CRYPTO_xVIx_xAIx_START_SEC_VAR_CLEARED_[!CALL "GetWorkspacesMemMapAlignment"!]
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  Variable which specifies the context of the primary primitive **/
/* !LINKSTO Crypto.Dsn.Api/Data/Crypto_xVIx_xAIx_CDO_CDO_P1Wksp/0001,1 */
VAR(uint[!"ecu:get('Cpu.Type')"!], CRYPTO_xVIx_xAIx_APPL_DATA) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P1Wksp[CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P1WKSP_SIZE_WORDS] = {0U};

  [!IF "num:i(0) < $CryptoDriverObjectPrimitivesListRealTrimP2Size"!]
/** \brief  Variable which specifies the context of the secondary primitive **/
/* !LINKSTO Crypto.Dsn.Api/Data/Crypto_xVIx_xAIx_CDO_CDO_P2Wksp/0001,1 */
VAR(uint[!"ecu:get('Cpu.Type')"!], CRYPTO_xVIx_xAIx_APPL_DATA) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P2Wksp[CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P2WKSP_SIZE_WORDS] = {0U};

  [!ENDIF!]
  [!IF "node:exists(./CryptoEbPrimaryHeapSize)"!]
/** \brief  Variable which specifies the heap buffer of the primary primitive **/
/* !LINKSTO Crypto.Dsn.Api/Data/Crypto_xVIx_xAIx_CDO_CDO_P1Heap/0001,1 */
VAR(uint[!"ecu:get('Cpu.Type')"!], CRYPTO_xVIx_xAIx_APPL_DATA) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P1Heap[CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P1HEAP_SIZE_WORDS] = {0U};

  [!ENDIF!]
  [!IF "num:i(0) < $CryptoDriverObjectPrimitivesListRealTrimP2Size"!]
    [!IF "node:exists(./CryptoEbSecondaryHeapSize)"!]
/** \brief  Variable which specifies the heap buffer of the secondary primitive **/
/* !LINKSTO Crypto.Dsn.Api/Data/Crypto_xVIx_xAIx_CDO_CDO_P2Heap/0001,1 */
VAR(uint[!"ecu:get('Cpu.Type')"!], CRYPTO_xVIx_xAIx_APPL_DATA) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_P2Heap[CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_P2HEAP_SIZE_WORDS] = {0U};

    [!ENDIF!]
  [!ENDIF!]
  [!IF "node:exists(./CryptoDefaultRandomPrimitiveRef)"!]
/** \brief  Variable which specifies the context of the secondary random primitive **/
/* !LINKSTO Crypto.Dsn.Api/Data/Crypto_xVIx_xAIx_CDO_CDO_R1Wksp/0001,1 */
VAR(uint[!"ecu:get('Cpu.Type')"!], CRYPTO_xVIx_xAIx_APPL_DATA) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_R1Wksp[CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_R1WKSP_SIZE_WORDS] = {0U};

    [!IF "num:i(0) < $CryptoDriverObjectPrimitivesListRealTrimR2Size"!]
/** \brief  Variable which specifies the context of the secondary random primitive **/
/* !LINKSTO Crypto.Dsn.Api/Data/Crypto_xVIx_xAIx_CDO_CDO_R2Wksp/0001,1 */
VAR(uint[!"ecu:get('Cpu.Type')"!], CRYPTO_xVIx_xAIx_APPL_DATA) Crypto_xVIx_xAIx_CDO_[!"node:name(.)"!]_R2Wksp[CRYPTO_XVIX_XAIX_CDO_[!"text:toupper(node:name(.))"!]_R2WKSP_SIZE_WORDS] = {0U};

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

/* !LINKSTO Crypto.Dsn.Api/Data/Crypto_xVIx_xAIx_KMn_KeyElementDataArray_KeyElement_Key/0001,1 */
  [!SELECT "./CryptoKeyTypeRef"!]
    [!LOOP "util:distinct(node:order(as:ref(.)/CryptoKeyElementRef/eb-list::*, 'node:value(as:ref(.)/CryptoKeyElementId)'))"!]
VAR(uint[!"ecu:get('Cpu.Type')"!], CRYPTO_xVIx_xAIx_VAR) Crypto_xVIx_xAIx_KMn_KeyElementDataArray_[!"node:name(as:ref(.))"!]_[!"$keyName"!][([!"node:value(as:ref(.)/CryptoKeyElementSize)"!] + [!"$WordWidthInBytes"!] - 1)/[!"$WordWidthInBytes"!]] =
{
  0U
};

    [!ENDLOOP!]
#define CRYPTO_xVIx_xAIx_STOP_SEC_VAR_INIT_[!CALL "GetWorkspacesMemMapAlignment"!]
#include <Crypto_xVIx_xAIx_MemMap.h>

#define CRYPTO_xVIx_xAIx_START_SEC_VAR_INIT_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>
    [!LOOP "util:distinct(node:order(as:ref(.)/CryptoKeyElementRef/eb-list::*, 'node:value(as:ref(.)/CryptoKeyElementId)'))"!]

/* !LINKSTO Crypto.Dsn.Api/Data/Crypto_xVIx_xAIx_KMn_KeyElementData_KeyElement_Key/0001,1 */
VAR(Crypto_xVIx_xAIx_KeyElementDataType, CRYPTO_xVIx_xAIx_VAR) Crypto_xVIx_xAIx_KMn_KeyElementData_[!"node:name(as:ref(.))"!]_[!"$keyName"!] =
{
  [!"node:value(as:ref(.)/CryptoKeyElementSize )"!]U, /* size */
  0U, /* readLock */
  (P2VAR(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA)) Crypto_xVIx_xAIx_KMn_KeyElementDataArray_[!"node:name(as:ref(.))"!]_[!"$keyName"!], /* data */
  FALSE /* writeLock */
};
    [!ENDLOOP!]
  [!ENDSELECT!]

/* !LINKSTO Crypto.Dsn.Api/Data/Crypto_xVIx_xAIx_KMn_KeyData_KeyElement/0001,1 */
VAR(Crypto_xVIx_xAIx_KeyDataType, CRYPTO_xVIx_xAIx_VAR) Crypto_xVIx_xAIx_KMn_KeyData_[!"node:name(.)"!] =
{
  CRYPTO_XVIX_XAIX_KEYSTATE_INVALID /* keyState */
};

#define CRYPTO_xVIx_xAIx_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

[!ENDLOOP!]
/*==================[external function definitions]===============================================*/

/*==================[internal function definitions]===============================================*/

/*==================[end of file]=================================================================*/

