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
[!AUTOSPACING!][!//
[!/*========================================================================================*/!][!//
[!INCLUDE "../include/Crypto_xVIx_xAIx_Macros.m"!]
[!/*========================================================================================*/!][!//

/* !LINKSTO Crypto.Req.Api/Crypto_xVIx_xAIx_Externals.template.h/0001,1 */

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

#include <Std_Types.h>

/*==================[macros]======================================================================*/

/* --- generated, do not edit ------------------------------------------------------------------- */

/* macros to be used in nvm configuration for 'RAM Block Data Address'
 */
[!LOOP "util:distinct(node:order(CryptoKeys/CryptoKey/eb-list::*, 'node:value(CryptoKeyId)'))"!]
  [!VAR "keyName" = "node:name(.)"!]
  [!LOOP "util:distinct(node:order(util:distinct(node:refs(node:ref(./CryptoKeyTypeRef)/CryptoKeyElementRef/eb-list::*)), 'node:value(./CryptoKeyElementId)'))"!]
#define  CRYPTO_XVIX_XAIX_KE_[!"$keyName"!]_[!"node:name(.)"!]  \
  Crypto_xVIx_xAIx_KMn_KeyElementDataArray_[!"node:name(.)"!]_[!"$keyName"!]
  [!ENDLOOP!]
[!ENDLOOP!]

#define  CRYPTO_XVIX_XAIX_VLD  Crypto_xVIx_xAIx_Vld_Buffer

/* --- to be configured ------------------------------------------------------------------------- */

/** \brief  The IDs of the NvM blocks the persistently configured key elements <KE> of the keys
 **         <KY> shall be stored in.
 **         The value of these macros shall be configured by the user!
 **/
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/CRYPTO_XVIX_XAIX_KE_NVMBLK_KY_KE/0001,1 */
/**@{*/
[!LOOP "util:distinct(node:order(CryptoKeys/CryptoKey/eb-list::*, 'node:value(CryptoKeyId)'))"!]
  [!VAR "keyName" = "node:name(.)"!]
  [!LOOP "util:distinct(node:order(util:distinct(node:refs(node:ref(./CryptoKeyTypeRef)/CryptoKeyElementRef/eb-list::*)), 'node:value(./CryptoKeyElementId)'))"!]
    [!IF "node:existsAndTrue(./CryptoKeyElementPersist)"!]
#define  CRYPTO_XVIX_XAIX_KE_NVMBLK_[!"$keyName"!]_[!"node:name(.)"!]  <to be configured>U
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDLOOP!]
/**@}*/

/** \brief  The types of process how the data of the persistently configured key elements <KE>
 **         of the keys <KY> shall be written to the corresponding NvM block
 **         'CRYPTO_XVIX_XAIX_KE_NVMBLK_<KY>_<KE>'.
 **         The value of this macro shall be configured by the user!
 **
 ** [==0U] ... write via NvM_WriteAll
 ** [==1U] ... write immediately via NvM_Write(PRAM)Block
 **/
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/CRYPTO_XVIX_XAIX_KE_NVMWTY_KY_KE/0001,1 */
/**@{*/
[!LOOP "util:distinct(node:order(CryptoKeys/CryptoKey/eb-list::*, 'node:value(CryptoKeyId)'))"!]
  [!VAR "keyName" = "node:name(.)"!]
  [!LOOP "util:distinct(node:order(util:distinct(node:refs(node:ref(./CryptoKeyTypeRef)/CryptoKeyElementRef/eb-list::*)), 'node:value(./CryptoKeyElementId)'))"!]
    [!IF "node:existsAndTrue(./CryptoKeyElementPersist)"!]
#define  CRYPTO_XVIX_XAIX_KE_NVMWTY_[!"$keyName"!]_[!"node:name(.)"!]  <to be configured>U
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDLOOP!]
/**@}*/

/** \brief  The types of process how the data of the persistently configured key elements <KE>
 **         of the keys <KY> shall be read from the corresponding NvM block
 **         'CRYPTO_XVIX_XAIX_KE_NVMBLK_<KY>_<KE>'.
 **         The value of this macro shall be configured by the user!
 **
 ** [==0U] ... read via NvM_ReadAll
 ** [==1U] ... read immediately via NvM_Read(PRAM)Block
 **/
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/CRYPTO_XVIX_XAIX_KE_NVMRTY_KY_KE/0001,1 */
/**@{*/
[!LOOP "util:distinct(node:order(CryptoKeys/CryptoKey/eb-list::*, 'node:value(CryptoKeyId)'))"!]
  [!VAR "keyName" = "node:name(.)"!]
  [!LOOP "util:distinct(node:order(util:distinct(node:refs(node:ref(./CryptoKeyTypeRef)/CryptoKeyElementRef/eb-list::*)), 'node:value(./CryptoKeyElementId)'))"!]
    [!IF "node:existsAndTrue(./CryptoKeyElementPersist)"!]
#define  CRYPTO_XVIX_XAIX_KE_NVMRTY_[!"$keyName"!]_[!"node:name(.)"!]  <to be configured>U
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDLOOP!]
/**@}*/

/** \brief  The ID of the single NvM block that shall store the valid state information for all
 **         Crypto keys that contain at least one persistently configured key element.
 **         The value of this macro shall be configured by the user!
 **/
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/CRYPTO_XVIX_XAIX_VLD_NVMBLK/0001,1 */
#define CRYPTO_XVIX_XAIX_VLD_NVMBLK                                    <to be configured>U

/** \brief  The size of the NvM block 'CRYPTO_XVIX_XAIX_VLD_NVMBLK'.
 **         (This size shall be equal or greater than '1 + biggest byte index' used in
 **          the following *_VLD_CFG_* macros.)
 **         The value of this macro shall be configured by the user!
 **/
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/CRYPTO_XVIX_XAIX_VLD_NVMSIZE/0001,1 */
#define CRYPTO_XVIX_XAIX_VLD_NVMSIZE                                   <to be configured>U

/** \brief  The type of process how the data of valid state information for keys with at least one
 **         persistently configured key element shall be written to the corresponding NvM block
 **         'CRYPTO_XVIX_XAIX_VLD_NVMBLK'.
 **         The value of this macro shall be configured by the user!
 **
 ** [==0U] ... write via NvM_WriteAll
 ** [==1U] ... write immediately via NvM_Write(PRAM)Block
 **/
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/CRYPTO_XVIX_XAIX_VLD_NVMWTY/0001,1 */
#define CRYPTO_XVIX_XAIX_VLD_NVMWTY                                    <to be configured>U

/** \brief  The type of process how the data of valid state information for keys with at least one
 **         persistently configured key element shall be read from the corresponding NvM block
 **         'CRYPTO_XVIX_XAIX_VLD_NVMBLK'.
 **         The value of this macro shall be configured by the user!
 **
 ** [==0U] ... read via NvM_ReadAll
 ** [==1U] ... read immediately via NvM_Read(PRAM)Block
 **/
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/CRYPTO_XVIX_XAIX_VLD_NVMRTY/0001,1 */
#define CRYPTO_XVIX_XAIX_VLD_NVMRTY                                    <to be configured>U

/** \brief  Configuration macros that specify in which bit(s) of which byte of NvMBlock
 **         'CRYPTO_XVIX_XAIX_VLD_NVMBLK' the valid information of a key that contain at least one
 **         persistently configured key element shall be stored.
 **         The value of this macro shall be configured by the user!
 **
 ** The index of the byte and the mask for the bit(s) to be used shall be encoded as a combined
 ** uint32 value. The upper 24 bits of this uint32 shall represent the byte index, the lower 8 bits
 ** the mask of the bit(s) that shall store the valid state information.
 **/
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/CRYPTO_XVIX_XAIX_VLD_CFG_KY/0001,1 */
/**@{*/
[!LOOP "util:distinct(node:order(CryptoKeys/CryptoKey/eb-list::*, 'node:value(CryptoKeyId)'))"!]
  [!IF "0 < num:i(count(util:distinct(node:refs(node:ref(./CryptoKeyTypeRef)/CryptoKeyElementRef/eb-list::*))/CryptoKeyElementPersist[node:existsAndTrue(.)]))"!]
#define  CRYPTO_XVIX_XAIX_VLD_CFG_[!"node:name(.)"!]                   <to be configured>U
  [!ENDIF!]
[!ENDLOOP!]
/**@}*/

/*==================[type definitions]============================================================*/

/** \brief  Structure which summarizes configuration dependent, constant during run-time data per
 **         key.
 **/
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_KeyInfoCnfgType/0001,1 */
typedef struct
{
  CONST(uint32, CRYPTO_xVIx_xAIx_CONST) keyId;
  CONST(uint32, CRYPTO_xVIx_xAIx_CONST) validityPositionInfo;
}
Crypto_xVIx_xAIx_KeyInfoCnfgType;

/** \brief  Structure which summarizes run-time data per key.
 **/
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_KeyInfoDataType/0001,1 */
typedef struct
{
  uint8 dummy;
}
Crypto_xVIx_xAIx_KeyInfoDataType;

/** \brief  Structure which summarizes configuration dependent, constant during run-time data per
 **         key element.
 **/
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_KeyElementInfoCnfgType/0001,1 */
typedef struct
{
  CONST(uint32, CRYPTO_xVIx_xAIx_CONST) keyId;
  CONST(uint32, CRYPTO_xVIx_xAIx_CONST) keyElementId;
  CONST(uint16, CRYPTO_xVIx_xAIx_CONST) nvmBlockId;
  CONST(uint8,  CRYPTO_xVIx_xAIx_CONST) nvmWriteType;
  CONST(uint8,  CRYPTO_xVIx_xAIx_CONST) nvmReadType;
}
Crypto_xVIx_xAIx_KeyElementInfoCnfgType;

/** \brief  Structure which summarizes run-time data per key element.
 **/
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_KeyElementInfoDataType/0001,1 */
typedef struct
{
  boolean keyElementChanged;
}
Crypto_xVIx_xAIx_KeyElementInfoDataType;

/*==================[external constants]==========================================================*/

#define CRYPTO_XVIX_XAIX_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  Instances of Crypto_xVIx_xAIx_KeyInfoCnfgType per Crypto key <Ky> that contain at least
 **         one persistently configured key element.
 **/
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_KeyInfoCnfg_Ky/0001,1 */
/**@{*/
[!LOOP "util:distinct(node:order(CryptoKeys/CryptoKey/eb-list::*, 'node:value(CryptoKeyId)'))"!]
  [!IF "0 < num:i(count(util:distinct(node:refs(node:ref(./CryptoKeyTypeRef)/CryptoKeyElementRef/eb-list::*))/CryptoKeyElementPersist[node:existsAndTrue(.)]))"!]
extern CONST(Crypto_xVIx_xAIx_KeyInfoCnfgType, CRYPTO_xVIx_xAIx_CONST)
  Crypto_xVIx_xAIx_KeyInfoCnfg_[!"node:name(.)"!];
  [!ENDIF!]
[!ENDLOOP!]
/**@}*/

/** \brief  Instances of Crypto_xVIx_xAIx_KeyElementInfoCnfgType per Crypto key <Ky> and its
 **         persistently configured key elements <Ke>.
 **/
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_KeyElementInfoCnfg_Ky_Ke/0001,1 */
/**@{*/
[!LOOP "util:distinct(node:order(CryptoKeys/CryptoKey/eb-list::*, 'node:value(CryptoKeyId)'))"!]
  [!VAR "keyName" = "node:name(.)"!]
  [!LOOP "util:distinct(node:order(util:distinct(node:refs(node:ref(./CryptoKeyTypeRef)/CryptoKeyElementRef/eb-list::*)), 'node:value(./CryptoKeyElementId)'))"!]
    [!IF "node:existsAndTrue(./CryptoKeyElementPersist)"!]
extern CONST(Crypto_xVIx_xAIx_KeyElementInfoCnfgType, CRYPTO_xVIx_xAIx_CONST)
  Crypto_xVIx_xAIx_KeyElementInfoCnfg_[!"$keyName"!]_[!"node:name(.)"!];
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDLOOP!]
/**@}*/

#define CRYPTO_XVIX_XAIX_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[external data]===============================================================*/

#define CRYPTO_XVIX_XAIX_START_SEC_VAR_CLEARED_[!CALL "GetWorkspacesMemMapAlignment"!]
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  Instances of Crypto_xVIx_xAIx_KeyInfoDataType per Crypto key <Ky> that contain at least
 **         one persistently configured key element.
 **/
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_KeyInfoData_Ky/0001,1 */
/**@{*/
[!LOOP "util:distinct(node:order(CryptoKeys/CryptoKey/eb-list::*, 'node:value(CryptoKeyId)'))"!]
  [!IF "0 < num:i(count(util:distinct(node:refs(node:ref(./CryptoKeyTypeRef)/CryptoKeyElementRef/eb-list::*))/CryptoKeyElementPersist[node:existsAndTrue(.)]))"!]
extern VAR(Crypto_xVIx_xAIx_KeyInfoDataType, CRYPTO_xVIx_xAIx_VAR)
  Crypto_xVIx_xAIx_KeyInfoData_[!"node:name(.)"!];
  [!ENDIF!]
[!ENDLOOP!]
/**@}*/

/** \brief  Instance of Crypto_xVIx_xAIx_KeyElementInfoDataType per Crypto key <Ky> and its
 **         persistently configured key elements <Ke>.
 **/
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_KeyElementInfoData_Ky_Ke/0001,1 */
/**@{*/
[!LOOP "util:distinct(node:order(CryptoKeys/CryptoKey/eb-list::*, 'node:value(CryptoKeyId)'))"!]
  [!VAR "keyName" = "node:name(.)"!]
  [!LOOP "util:distinct(node:order(util:distinct(node:refs(node:ref(./CryptoKeyTypeRef)/CryptoKeyElementRef/eb-list::*)), 'node:value(./CryptoKeyElementId)'))"!]
    [!IF "node:existsAndTrue(./CryptoKeyElementPersist)"!]
extern VAR(Crypto_xVIx_xAIx_KeyElementInfoDataType, CRYPTO_xVIx_xAIx_VAR)
  Crypto_xVIx_xAIx_KeyElementInfoData_[!"$keyName"!]_[!"node:name(.)"!];
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDLOOP!]
/**@}*/

#define CRYPTO_XVIX_XAIX_STOP_SEC_VAR_CLEARED_[!CALL "GetWorkspacesMemMapAlignment"!]
#include <Crypto_xVIx_xAIx_MemMap.h>

#define CRYPTO_XVIX_XAIX_START_SEC_VAR_CLEARED_8
#include <Crypto_xVIx_xAIx_MemMap.h>

/** \brief  Internal buffer to handle the layout of the single NvM block (see
 **         CRYPTO_XVIX_XAIX_VLD_NVMBLK) that shall store the valid state information for all
 **         Crypto keys that contain at least one persistently configured key element.
 **/
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Vld_Buffer/0001,1 */
extern VAR(uint8, CRYPTO_xVIx_xAIx_VAR)
  Crypto_xVIx_xAIx_Vld_Buffer[CRYPTO_XVIX_XAIX_VLD_NVMSIZE];

#define CRYPTO_XVIX_XAIX_STOP_SEC_VAR_CLEARED_8
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[external function declarations]==============================================*/

/*================================================================================================*/

/*==================[end of file]=================================================================*/

