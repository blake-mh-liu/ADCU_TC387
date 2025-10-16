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

/* !LINKSTO Crypto.Req.Api/Crypto_xVIx_xAIx_Externals.template.c/0001,1 */

/*==================[deviations]==================================================================*/
[!VAR "numberOfCombinationsOfKeysAndPersistentKeyElements" = "num:i(0)"!]
[!VAR "numberOfKeysWithAtLeastOnePersistentKeyElement"     = "num:i(0)"!]
[!LOOP "util:distinct(node:order(CryptoKeys/CryptoKey/eb-list::*, 'node:value(CryptoKeyId)'))"!]
  [!VAR "numberOfPersistentKeyElementsInKey"                 = "num:i(count(util:distinct(node:refs(node:ref(./CryptoKeyTypeRef)/CryptoKeyElementRef/eb-list::*))/CryptoKeyElementPersist[node:existsAndTrue(.)]))"!]
  [!VAR "numberOfCombinationsOfKeysAndPersistentKeyElements" = "num:i($numberOfCombinationsOfKeysAndPersistentKeyElements + $numberOfPersistentKeyElementsInKey)"!]
  [!IF "num:i(0) < $numberOfPersistentKeyElementsInKey"!][!VAR "numberOfKeysWithAtLeastOnePersistentKeyElement" = "num:i($numberOfKeysWithAtLeastOnePersistentKeyElement + 1)"!][!ENDIF!]
[!ENDLOOP!]

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

#include <Std_Types.h>
#include <NvM.h>
#include <Crypto_xVIx_xAIx_Externals.h>
#include <Crypto_xVIx_xAIx_Int.h>

/*==================[macros]======================================================================*/

#define CRYPTO_XVIX_XAIX_COUT_PARAM_UNUSED(x)                    ((void) (x))
#define CRYPTO_XVIX_XAIX_NONE                                    0xFFFFFFFFU

/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/CRYPTO_XVIX_XAIX_VLD_CFG_KY/0002,1 */
#define CRYPTO_XVIX_XAIX_VLD_CFG_GET_BYTE(x)                     ((uint32) (((x) >> 8U) & 0x00FFFFFFU))
#define CRYPTO_XVIX_XAIX_VLD_CFG_GET_MASK(x)                     ((uint32) (((x) >> 0U) & 0x000000FFU))

#define CRYPTO_XVIX_XAIX_NVM_WRITEALL                            0U
#define CRYPTO_XVIX_XAIX_NVM_WRITEBLOCK                          1U
#define CRYPTO_XVIX_XAIX_NVM_READALL                             0U
#define CRYPTO_XVIX_XAIX_NVM_READBLOCK                           1U

/** \brief  Macro that identifies whether the callout function implementation for
 **        'Crypto_XVIx_xAIx_KeyElement_SetData' is enabled (STD_ON) or not (STD_OFF).
 **/
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/CRYPTO_XVIX_XAIX_COUT_ENABLED_KEYELEMENT_SETDATA/0001,1 */
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/CRYPTO_XVIX_XAIX_COUT_ENABLED_KEYELEMENT_SETDATA/0002,1 */
#define CRYPTO_XVIX_XAIX_COUT_ENABLED_KEYELEMENT_SETDATA         [!WS "9"!][!IF "num:i(0) < $numberOfCombinationsOfKeysAndPersistentKeyElements"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Macro that identifies whether the callout function implementation for
 **        'Crypto_XVIx_xAIx_KeyElement_GetData' is enabled (STD_ON) or not (STD_OFF).
 **/
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/CRYPTO_XVIX_XAIX_COUT_ENABLED_KEYELEMENT_GETDATA/0001,1 */
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/CRYPTO_XVIX_XAIX_COUT_ENABLED_KEYELEMENT_GETDATA/0002,1 */
#define CRYPTO_XVIX_XAIX_COUT_ENABLED_KEYELEMENT_GETDATA         [!WS "9"!][!IF "num:i(0) < $numberOfCombinationsOfKeysAndPersistentKeyElements"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Macro that identifies whether the callout function implementation for
 **        'Crypto_XVIx_xAIx_Key_SetValid' is enabled (STD_ON) or not (STD_OFF).
 **/
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/CRYPTO_XVIX_XAIX_COUT_ENABLED_KEY_SETVALID/0001,1 */
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/CRYPTO_XVIX_XAIX_COUT_ENABLED_KEY_SETVALID/0002,1 */
#define CRYPTO_XVIX_XAIX_COUT_ENABLED_KEY_SETVALID               [!WS "15"!][!IF "num:i(0) < $numberOfCombinationsOfKeysAndPersistentKeyElements"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  Macro that identifies whether the callout function implementation for
 **        'Crypto_XVIx_xAIx_Key_GetValid' is enabled (STD_ON) or not (STD_OFF).
 **/
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/CRYPTO_XVIX_XAIX_COUT_ENABLED_KEY_GETVALID/0001,1 */
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/CRYPTO_XVIX_XAIX_COUT_ENABLED_KEY_GETVALID/0002,1 */
#define CRYPTO_XVIX_XAIX_COUT_ENABLED_KEY_GETVALID               [!WS "15"!][!IF "num:i(0) < $numberOfCombinationsOfKeysAndPersistentKeyElements"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/** \brief  The number of all configured combinations of Crypto keys and persistent key elements.
 **/
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/CRYPTO_XVIX_XAIX_KE_COUNT/0001,1 */
#define CRYPTO_XVIX_XAIX_KE_COUNT                                [!WS "33"!][!"$numberOfCombinationsOfKeysAndPersistentKeyElements"!]U

/** \brief  The number of Crypto keys that contain at least one persistently configured key element.
 **/
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/CRYPTO_XVIX_XAIX_VLD_COUNT/0001,1 */
#define CRYPTO_XVIX_XAIX_VLD_COUNT                               [!WS "32"!][!"$numberOfKeysWithAtLeastOnePersistentKeyElement"!]U

/*==================[type definitions]============================================================*/

/** \brief  Structure which summarizes the instances of configuration dependent, constant data
 **         and run-time data per Crypto key.
 **/
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_KeyInfoType/0001,1 */
typedef struct
{
  CONSTP2CONST(Crypto_xVIx_xAIx_KeyInfoCnfgType, AUTOMATIC, CRYPTO_xVIx_xAIx_CONST) cnfg;
    CONSTP2VAR(Crypto_xVIx_xAIx_KeyInfoDataType, AUTOMATIC, CRYPTO_xVIx_xAIx_CONST) data;
}
Crypto_xVIx_xAIx_KeyInfoType;

/** \brief  Structure which summarizes the instances of configuration dependent, constant data
 **         and run-time data per key element.
 **/
/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_KeyElementInfoType/0001,1 */
typedef struct
{
  CONSTP2CONST(Crypto_xVIx_xAIx_KeyElementInfoCnfgType, AUTOMATIC, CRYPTO_xVIx_xAIx_CONST) cnfg;
    CONSTP2VAR(Crypto_xVIx_xAIx_KeyElementInfoDataType, AUTOMATIC, CRYPTO_xVIx_xAIx_CONST) data;
}
Crypto_xVIx_xAIx_KeyElementInfoType;

/*==================[internal function declarations]==============================================*/

/*==================[internal constants]==========================================================*/

#define CRYPTO_XVIX_XAIX_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_KeyInfo/0001,1 */
[!IF "num:i(0) < $numberOfCombinationsOfKeysAndPersistentKeyElements"!]
static CONST(Crypto_xVIx_xAIx_KeyInfoType, CRYPTO_xVIx_xAIx_CONST)
  Crypto_xVIx_xAIx_KeyInfo[CRYPTO_XVIX_XAIX_VLD_COUNT] =
{
[!LOOP "util:distinct(node:order(CryptoKeys/CryptoKey/eb-list::*, 'node:value(CryptoKeyId)'))"!]
  [!IF "0 < num:i(count(util:distinct(node:refs(node:ref(./CryptoKeyTypeRef)/CryptoKeyElementRef/eb-list::*))/CryptoKeyElementPersist[node:existsAndTrue(.)]))"!]
  {
    &Crypto_xVIx_xAIx_KeyInfoCnfg_[!"node:name(.)"!],
    &Crypto_xVIx_xAIx_KeyInfoData_[!"node:name(.)"!]
  },
  [!ENDIF!]
[!ENDLOOP!]
};
[!ENDIF!]

/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_KeyElementInfo/0001,1 */
[!IF "num:i(0) < $numberOfCombinationsOfKeysAndPersistentKeyElements"!]
static CONST(Crypto_xVIx_xAIx_KeyElementInfoType, CRYPTO_xVIx_xAIx_CONST)
  Crypto_xVIx_xAIx_KeyElementInfo[CRYPTO_XVIX_XAIX_KE_COUNT] =
{
[!LOOP "util:distinct(node:order(CryptoKeys/CryptoKey/eb-list::*, 'node:value(CryptoKeyId)'))"!]
  [!VAR "keyName" = "node:name(.)"!]
  [!LOOP "util:distinct(node:order(util:distinct(node:refs(node:ref(./CryptoKeyTypeRef)/CryptoKeyElementRef/eb-list::*)), 'node:value(./CryptoKeyElementId)'))"!]
    [!IF "node:existsAndTrue(./CryptoKeyElementPersist)"!]
  {
    &Crypto_xVIx_xAIx_KeyElementInfoCnfg_[!"$keyName"!]_[!"node:name(.)"!],
    &Crypto_xVIx_xAIx_KeyElementInfoData_[!"$keyName"!]_[!"node:name(.)"!]
  },
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDLOOP!]
};
[!ENDIF!]

#define CRYPTO_XVIX_XAIX_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

#define CRYPTO_XVIX_XAIX_START_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

[!LOOP "util:distinct(node:order(CryptoKeys/CryptoKey/eb-list::*, 'node:value(CryptoKeyId)'))"!]
  [!IF "0 < num:i(count(util:distinct(node:refs(node:ref(./CryptoKeyTypeRef)/CryptoKeyElementRef/eb-list::*))/CryptoKeyElementPersist[node:existsAndTrue(.)]))"!]
CONST(Crypto_xVIx_xAIx_KeyInfoCnfgType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_KeyInfoCnfg_[!"node:name(.)"!] =
{
  [!"node:value(./CryptoKeyId)"!],
  CRYPTO_XVIX_XAIX_VLD_CFG_[!"node:name(.)"!]
};
  [!ENDIF!]
[!ENDLOOP!]

[!LOOP "util:distinct(node:order(CryptoKeys/CryptoKey/eb-list::*, 'node:value(CryptoKeyId)'))"!]
  [!VAR "keyName" = "node:name(.)"!]
  [!VAR "keyId"   = "node:value(CryptoKeyId)"!]
  [!LOOP "util:distinct(node:order(util:distinct(node:refs(node:ref(./CryptoKeyTypeRef)/CryptoKeyElementRef/eb-list::*)), 'node:value(./CryptoKeyElementId)'))"!]
    [!IF "node:existsAndTrue(./CryptoKeyElementPersist)"!]
CONST(Crypto_xVIx_xAIx_KeyElementInfoCnfgType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_KeyElementInfoCnfg_[!"$keyName"!]_[!"node:name(.)"!] =
{
  [!"$keyId"!],
  [!"node:value(./CryptoKeyElementId)"!],
  CRYPTO_XVIX_XAIX_KE_NVMBLK_[!"$keyName"!]_[!"node:name(.)"!],
  CRYPTO_XVIX_XAIX_KE_NVMWTY_[!"$keyName"!]_[!"node:name(.)"!],
  CRYPTO_XVIX_XAIX_KE_NVMRTY_[!"$keyName"!]_[!"node:name(.)"!]
};
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDLOOP!]

#define CRYPTO_XVIX_XAIX_STOP_SEC_CONST_UNSPECIFIED
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[external data]===============================================================*/

#define CRYPTO_XVIX_XAIX_START_SEC_VAR_CLEARED_[!CALL "GetWorkspacesMemMapAlignment"!]
#include <Crypto_xVIx_xAIx_MemMap.h>

[!LOOP "util:distinct(node:order(CryptoKeys/CryptoKey/eb-list::*, 'node:value(CryptoKeyId)'))"!]
  [!IF "0 < num:i(count(util:distinct(node:refs(node:ref(./CryptoKeyTypeRef)/CryptoKeyElementRef/eb-list::*))/CryptoKeyElementPersist[node:existsAndTrue(.)]))"!]
VAR(Crypto_xVIx_xAIx_KeyInfoDataType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_KeyInfoData_[!"node:name(.)"!] = {0U};
  [!ENDIF!]
[!ENDLOOP!]

[!LOOP "util:distinct(node:order(CryptoKeys/CryptoKey/eb-list::*, 'node:value(CryptoKeyId)'))"!]
  [!VAR "keyName" = "node:name(.)"!]
  [!LOOP "util:distinct(node:order(util:distinct(node:refs(node:ref(./CryptoKeyTypeRef)/CryptoKeyElementRef/eb-list::*)), 'node:value(./CryptoKeyElementId)'))"!]
    [!IF "node:existsAndTrue(./CryptoKeyElementPersist)"!]
VAR(Crypto_xVIx_xAIx_KeyElementInfoDataType, CRYPTO_xVIx_xAIx_CONST) Crypto_xVIx_xAIx_KeyElementInfoData_[!"$keyName"!]_[!"node:name(.)"!] = {0U};
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDLOOP!]

#define CRYPTO_XVIX_XAIX_STOP_SEC_VAR_CLEARED_[!CALL "GetWorkspacesMemMapAlignment"!]
#include <Crypto_xVIx_xAIx_MemMap.h>

#define CRYPTO_XVIX_XAIX_START_SEC_VAR_CLEARED_8
#include <Crypto_xVIx_xAIx_MemMap.h>

VAR(uint8, CRYPTO_xVIx_xAIx_VAR)
  Crypto_xVIx_xAIx_Vld_Buffer[CRYPTO_XVIX_XAIX_VLD_NVMSIZE] =
{
  0U
};

#define CRYPTO_XVIX_XAIX_STOP_SEC_VAR_CLEARED_8
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[external function definitions]===============================================*/

/*--- Crypto_xVIx_xAIx_KeyElement_SetData --------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_COUT_ENABLED_KEYELEMENT_SETDATA == STD_ON)

#define CRYPTO_xVIx_xAIx_START_SEC_CODE_KEYELEMENT_SETDATA
#include <Crypto_xVIx_xAIx_MemMap.h>

/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_KeyElement_SetData/General/0002,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEYELEMENT_SETDATA_CODE)
  Crypto_xVIx_xAIx_KeyElement_SetData
(
          uint32                                                                             keyId,
          uint32                                                                             keyElementId,
  P2CONST(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEYELEMENT_SETDATA_APPL_DATA) dataPtr,
          uint32                                                                             dataLength
)
{
  /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_KeyElement_SetData/General/0003,1 */
  Std_ReturnType stdResult = E_NOT_OK;

  uint32         i         = 0U;

  CRYPTO_XVIX_XAIX_COUT_PARAM_UNUSED(dataPtr);
  CRYPTO_XVIX_XAIX_COUT_PARAM_UNUSED(dataLength);

  for (i=0; i<CRYPTO_XVIX_XAIX_KE_COUNT; i++)
  {
    if (   (Crypto_xVIx_xAIx_KeyElementInfo[i].cnfg->keyId        == keyId       )
        && (Crypto_xVIx_xAIx_KeyElementInfo[i].cnfg->keyElementId == keyElementId)
       )
    {
      /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_KeyElement_SetData/SetKeyElementChangedTrue/0001,1 */
      Crypto_xVIx_xAIx_KeyElementInfo[i].data->keyElementChanged = TRUE;
      stdResult                                                  = E_OK;
      break;
    }
  }

  return stdResult;
}

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE_KEYELEMENT_SETDATA
#include <Crypto_xVIx_xAIx_MemMap.h>

#endif /* #if (CRYPTO_XVIX_XAIX_COUT_ENABLED_KEYELEMENT_SETDATA == STD_ON) */

/*--- Crypto_xVIx_xAIx_KeyElement_GetData --------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_COUT_ENABLED_KEYELEMENT_GETDATA == STD_ON)

#define CRYPTO_xVIx_xAIx_START_SEC_CODE_KEYELEMENT_GETDATA
#include <Crypto_xVIx_xAIx_MemMap.h>

/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_KeyElement_GetData/General/0002,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEYELEMENT_GETDATA_CODE)
  Crypto_xVIx_xAIx_KeyElement_GetData
(
        uint32                                                                             keyId,
        uint32                                                                             keyElementId,
  P2VAR(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEYELEMENT_SETDATA_APPL_DATA) dataPtr,
  P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEYELEMENT_SETDATA_APPL_DATA) dataLengthPtr
)
{
  /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_KeyElement_GetData/General/0003,1 */
  /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_KeyElement_GetData/General/0004,1 */
  /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_KeyElement_GetData/ReadBlock/0002,1 */
  Std_ReturnType        stdResult   = E_NOT_OK;

  NvM_RequestResultType nvmResult   = NVM_REQ_NOT_OK;
  uint16                nvmBlockId  = (uint16) CRYPTO_XVIX_XAIX_NONE;
  uint8                 nvmReadType = (uint8 ) CRYPTO_XVIX_XAIX_NONE;
  uint32                i           = 0U;

  CRYPTO_XVIX_XAIX_COUT_PARAM_UNUSED(dataPtr);
  CRYPTO_XVIX_XAIX_COUT_PARAM_UNUSED(dataLengthPtr);

  for (i=0; i<CRYPTO_XVIX_XAIX_KE_COUNT; i++)
  {
    if (   (Crypto_xVIx_xAIx_KeyElementInfo[i].cnfg->keyId        == keyId       )
        && (Crypto_xVIx_xAIx_KeyElementInfo[i].cnfg->keyElementId == keyElementId)
       )
    {
      nvmBlockId  = Crypto_xVIx_xAIx_KeyElementInfo[i].cnfg->nvmBlockId;
      nvmReadType = Crypto_xVIx_xAIx_KeyElementInfo[i].cnfg->nvmReadType;
      break;
    }
  }

  if (   ((uint16) CRYPTO_XVIX_XAIX_NONE != nvmBlockId )
      && (CRYPTO_XVIX_XAIX_NVM_READBLOCK >= nvmReadType)
     )
  {
    if (CRYPTO_XVIX_XAIX_NVM_READBLOCK == nvmReadType)
    {
      /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_KeyElement_GetData/ReadBlock/0001,1 */
      stdResult = NvM_ReadPRAMBlock(nvmBlockId);
      if (E_OK == stdResult)
      {
        do
        {
          /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_KeyElement_GetData/ReadBlock/0003,1 */
          stdResult = NvM_GetErrorStatus(nvmBlockId, &nvmResult);
        }
        while (   (E_OK            == stdResult)
               && (NVM_REQ_PENDING == nvmResult)
              );
        if (   (E_OK       != stdResult)
            || (NVM_REQ_OK != nvmResult)
          )
        {
          /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_KeyElement_GetData/ReadBlock/0004,1 */
          stdResult = E_NOT_OK;
        }
      }
    }
    else
    if (CRYPTO_XVIX_XAIX_NVM_READALL == nvmReadType)
    {
      /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_KeyElement_GetData/ReadAll/0001,1 */
      stdResult = NvM_GetErrorStatus(nvmBlockId, &nvmResult);
      if (   (E_OK       != stdResult)
          || (NVM_REQ_OK != nvmResult)
         )
      {
        /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_KeyElement_GetData/ReadAll/0002,1 */
        stdResult = E_NOT_OK;
      }
    }
    else
    {
      /* empty py intent */
    }
  }

  return stdResult;
}

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE_KEYELEMENT_GETDATA
#include <Crypto_xVIx_xAIx_MemMap.h>

#endif /* #if (CRYPTO_XVIX_XAIX_COUT_ENABLED_KEYELEMENT_GETDATA == STD_ON) */

/*--- Crypto_xVIx_xAIx_Key_SetValid --------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_COUT_ENABLED_KEY_SETVALID == STD_ON)

#define CRYPTO_xVIx_xAIx_START_SEC_CODE_KEY_SETVALID
#include <Crypto_xVIx_xAIx_MemMap.h>

/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/General/0002,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEY_SETVALID_CODE)
  Crypto_xVIx_xAIx_Key_SetValid
(
  uint32  keyId,
  boolean validState
)
{
  /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/General/0003,1 */
  Std_ReturnType        stdResult               = E_NOT_OK;

  NvM_RequestResultType nvmResult               = NVM_REQ_NOT_OK;
  uint16                nvmBlockId              = (uint16) CRYPTO_XVIX_XAIX_NONE;
  uint8                 nvmWriteType            = 0xFFU;
  uint32                validityPositionInfo    = (uint32) CRYPTO_XVIX_XAIX_NONE;
  boolean               flgWriteValidStateToNvM = TRUE;
  uint32                i                       = 0U;

  for (i=0; i<CRYPTO_XVIX_XAIX_VLD_COUNT; i++)
  {
    if (Crypto_xVIx_xAIx_KeyInfo[i].cnfg->keyId == keyId)
    {
      validityPositionInfo = Crypto_xVIx_xAIx_KeyInfo[i].cnfg->validityPositionInfo;
      break;
    }
  }

  if ((uint32) CRYPTO_XVIX_XAIX_NONE != validityPositionInfo)
  {

    if (TRUE == validState)
    {
      /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/ValidSetToTrue/General/0001,1 */
      for (i=0; i<CRYPTO_XVIX_XAIX_KE_COUNT; i++)
      {
        if (   (Crypto_xVIx_xAIx_KeyElementInfo[i].cnfg->keyId             == keyId)
            && (Crypto_xVIx_xAIx_KeyElementInfo[i].data->keyElementChanged == TRUE )
           )
        {
          nvmBlockId   = Crypto_xVIx_xAIx_KeyElementInfo[i].cnfg->nvmBlockId;
          nvmWriteType = Crypto_xVIx_xAIx_KeyElementInfo[i].cnfg->nvmWriteType;

          if (CRYPTO_XVIX_XAIX_NVM_WRITEBLOCK == nvmWriteType)
          {
            /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/ValidSetToTrue/WriteBlock/0001,1 */
            stdResult  = NvM_WritePRAMBlock(nvmBlockId);
            if (E_OK == stdResult)
            {
              do
              {
                /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/ValidSetToTrue/WriteBlock/0006,1 */
                stdResult = NvM_GetErrorStatus(nvmBlockId, &nvmResult);
              }
              while (   (E_OK            == stdResult)
                     && (NVM_REQ_PENDING == nvmResult)
                    );
              if (   (E_OK       != stdResult)
                  || (NVM_REQ_OK != nvmResult)
                 )
              {
                /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/ValidSetToTrue/WriteBlock/0007,1 */
                /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/ValidSetToTrue/WriteBlock/0008,1 */
                /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/ValidSetToTrue/WriteBlock/0009,1 */
                flgWriteValidStateToNvM = FALSE;
              }
            }
            else
            {
              /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/ValidSetToTrue/WriteBlock/0002,1 */
              /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/ValidSetToTrue/WriteBlock/0003,1 */
              /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/ValidSetToTrue/WriteBlock/0004,1 */
              flgWriteValidStateToNvM = FALSE;
            }
          }
          else
          if (CRYPTO_XVIX_XAIX_NVM_WRITEALL == nvmWriteType)
          {
            /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/ValidSetToTrue/WriteAll/0001,1 */
            stdResult = NvM_SetRamBlockStatus(nvmBlockId, TRUE);
            if (E_OK != stdResult)
            {
              /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/ValidSetToTrue/WriteAll/0002,1 */
              /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/ValidSetToTrue/WriteAll/0003,1 */
              /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/ValidSetToTrue/WriteAll/0004,1 */
              flgWriteValidStateToNvM = FALSE;
            }
          }
          else
          {
            /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/ValidSetToTrue/General/0002,1 */
            flgWriteValidStateToNvM = FALSE;
          }
          Crypto_xVIx_xAIx_KeyElementInfo[i].data->keyElementChanged = FALSE;
        }
      }

      if (TRUE == flgWriteValidStateToNvM)
      {
        /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/ValidSetToTrue/WriteBlock/0011,1 */
        /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/ValidSetToTrue/WriteAll/0005,1 */
        Crypto_xVIx_xAIx_Vld_Buffer[CRYPTO_XVIX_XAIX_VLD_CFG_GET_BYTE(validityPositionInfo)]
          |= CRYPTO_XVIX_XAIX_VLD_CFG_GET_MASK(validityPositionInfo);
      }
      else
      {
        /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/ValidSetToTrue/WriteBlock/0005,1 */
        /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/ValidSetToTrue/WriteBlock/0010,1 */
        stdResult = E_NOT_OK;
      }
    }
    else
    {
      /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/ValidSetToFalse/0001,1 */
      Crypto_xVIx_xAIx_Vld_Buffer[CRYPTO_XVIX_XAIX_VLD_CFG_GET_BYTE(validityPositionInfo)]
        &= ~CRYPTO_XVIX_XAIX_VLD_CFG_GET_MASK(validityPositionInfo);
    }

    if (TRUE == flgWriteValidStateToNvM)
    {

#if (CRYPTO_XVIX_XAIX_NVM_WRITEBLOCK == CRYPTO_XVIX_XAIX_VLD_NVMWTY)

      /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/WriteValidStateToNvm/WriteBlock/0001,1 */
      stdResult = NvM_WritePRAMBlock(CRYPTO_XVIX_XAIX_VLD_NVMBLK);
      if (E_OK == stdResult)
      {
        do
        {
          /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/WriteValidStateToNvm/WriteBlock/0003,1 */
          stdResult = NvM_GetErrorStatus(CRYPTO_XVIX_XAIX_VLD_NVMBLK, &nvmResult);
        }
        while (   (E_OK            == stdResult)
               && (NVM_REQ_PENDING == nvmResult)
              );
        if (   (E_OK       != stdResult)
            || (NVM_REQ_OK != nvmResult)
           )
        {
          /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/WriteValidStateToNvm/WriteBlock/0004,1 */
          stdResult = E_NOT_OK;
        }
        /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/WriteValidStateToNvm/WriteBlock/0005,1 */
      }
      else
      {
        stdResult = E_NOT_OK;
      }
      /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/WriteValidStateToNvm/WriteBlock/0002,1 */

#elif (CRYPTO_XVIX_XAIX_NVM_WRITEALL == CRYPTO_XVIX_XAIX_VLD_NVMWTY) /* #if (CRYPTO_XVIX_XAIX_NVM_WRITEBLOCK == CRYPTO_XVIX_XAIX_VLD_NVMWTY) */

      /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/WriteValidStateToNvm/WriteAll/0001,1 */
      stdResult = NvM_SetRamBlockStatus(CRYPTO_XVIX_XAIX_VLD_NVMBLK, TRUE);
      if (E_OK != stdResult)
      {
        /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/WriteValidStateToNvm/WriteAll/0002,1 */
        stdResult = E_NOT_OK;
      }
      /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/WriteValidStateToNvm/WriteAll/0003,1 */

#else /* #if (CRYPTO_XVIX_XAIX_NVM_WRITEBLOCK == CRYPTO_XVIX_XAIX_VLD_NVMWTY) */

      /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_SetValid/WriteValidStateToNvm/General/0001,1 */
      stdResult = E_NOT_OK;

#endif /* #if (CRYPTO_XVIX_XAIX_NVM_WRITEBLOCK == CRYPTO_XVIX_XAIX_VLD_NVMWTY) */

    }

  }

  return stdResult;
}

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE_KEY_SETVALID
#include <Crypto_xVIx_xAIx_MemMap.h>

#endif /* #if (CRYPTO_XVIX_XAIX_COUT_ENABLED_KEY_SETVALID == STD_ON) */

/*--- Crypto_xVIx_xAIx_Key_GetValid --------------------------------------------------------------*/

#if (CRYPTO_XVIX_XAIX_COUT_ENABLED_KEY_GETVALID == STD_ON)

#define CRYPTO_xVIx_xAIx_START_SEC_CODE_KEY_GETVALID
#include <Crypto_xVIx_xAIx_MemMap.h>

/* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_GetValid/General/0002,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEY_GETVALID_CODE)
  Crypto_xVIx_xAIx_Key_GetValid
(
        uint32                                                                        keyId,
  P2VAR(boolean, AUTOMATIC, CRYPTO_xVIx_xAIx_CRYPTO_XVIX_XAIX_KEY_GETVALID_APPL_DATA) validStatePtr
)
{
  /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_GetValid/General/0003,1 */
  /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_GetValid/General/0004,1 */
  /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_GetValid/ReadBlock/0002,1 */
  Std_ReturnType        stdResult            = E_NOT_OK;

#if (CRYPTO_XVIX_XAIX_NVM_READBLOCK == CRYPTO_XVIX_XAIX_VLD_NVMRTY)

  NvM_RequestResultType nvmResult            = NVM_REQ_NOT_OK;

#endif /* #if (CRYPTO_XVIX_XAIX_NVM_READBLOCK == CRYPTO_XVIX_XAIX_VLD_NVMRTY) */

  uint32                validityPositionInfo = (uint32) CRYPTO_XVIX_XAIX_NONE;
  uint32                i                    = 0U;

  for (i=0; i<CRYPTO_XVIX_XAIX_VLD_COUNT; i++)
  {
    if (Crypto_xVIx_xAIx_KeyInfo[i].cnfg->keyId == keyId)
    {
      validityPositionInfo = Crypto_xVIx_xAIx_KeyInfo[i].cnfg->validityPositionInfo;
      break;
    }
  }

  if ((uint32) CRYPTO_XVIX_XAIX_NONE != validityPositionInfo)
  {

#if (CRYPTO_XVIX_XAIX_NVM_READBLOCK == CRYPTO_XVIX_XAIX_VLD_NVMRTY)

    /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_GetValid/ReadBlock/0001,1 */
    stdResult = NvM_ReadPRAMBlock(CRYPTO_XVIX_XAIX_VLD_NVMBLK);
    if (E_OK == stdResult)
    {
      do
      {
        /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_GetValid/ReadBlock/0003,1 */
        stdResult = NvM_GetErrorStatus(CRYPTO_XVIX_XAIX_VLD_NVMBLK, &nvmResult);
      }
      while (    (E_OK            == stdResult)
              && (NVM_REQ_PENDING == nvmResult)
            );
      if (   (E_OK       != stdResult)
          || (NVM_REQ_OK != nvmResult)
          )
      {
        /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_GetValid/ReadBlock/0004,1 */
        stdResult = E_NOT_OK;
      }
    }

#elif (CRYPTO_XVIX_XAIX_NVM_READALL == CRYPTO_XVIX_XAIX_VLD_NVMRTY) /* #if (CRYPTO_XVIX_XAIX_NVM_READBLOCK == CRYPTO_XVIX_XAIX_VLD_NVMRTY) */

    /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_GetValid/ReadAll/0001,1 */
    stdResult = E_OK;

#endif /* #if (CRYPTO_XVIX_XAIX_NVM_READBLOCK == CRYPTO_XVIX_XAIX_VLD_NVMRTY) */

    if (E_OK == stdResult)
    {
      /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_GetValid/ReadBlock/0005,1 */
      /* !LINKSTO Crypto.Req.Api/NvMCalloutTemplate/Crypto_xVIx_xAIx_Key_GetValid/ReadAll/0001,1 */
      *validStatePtr =
        (boolean)
        (
          Crypto_xVIx_xAIx_Vld_Buffer[CRYPTO_XVIX_XAIX_VLD_CFG_GET_BYTE(validityPositionInfo)]
            & CRYPTO_XVIX_XAIX_VLD_CFG_GET_MASK(validityPositionInfo)
        );
    }

  }

  return stdResult;
}

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE_KEY_GETVALID
#include <Crypto_xVIx_xAIx_MemMap.h>

#endif /* #if (CRYPTO_XVIX_XAIX_COUT_ENABLED_KEY_GETVALID == STD_ON) */

/*==================[internal function definitions]===============================================*/

/*==================[end of file]=================================================================*/

