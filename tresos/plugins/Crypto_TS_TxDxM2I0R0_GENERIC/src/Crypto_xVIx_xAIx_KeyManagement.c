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

/* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_KeyManagement.c/0001,1 */

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

#include <CryIf_Cbk.h>                           /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_KeyManagement.c/0003,1 */

#include <Crypto_xVIx_xAIx.h>                    /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_KeyManagement.c/0002,1 */
#include <Crypto_xVIx_xAIx_KeyManagement.h>      /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_KeyManagement.c/0004,1 */
#include <Crypto_xVIx_xAIx_Int.h>                /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_KeyManagement.c/0005,1 */
#include <Crypto_xVIx_xAIx_Int_KeyManagement.h>  /* !LINKSTO Crypto.Dsn.Api/Files/Crypto_xVIx_xAIx_KeyManagement.c/0006,1 */

/* !LINKSTO Crypto.Dsn.Gen/KMn_GenerationPhase/0001,2 */
#if (CRYPTO_XVIX_XAIX_KEYMNGMT_ENABLED == STD_ON)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[internal function declarations]==============================================*/

/*==================[internal constants]==========================================================*/

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYPTO_xVIx_xAIx_START_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*--[Crypto_xVIx_xAIx_KeyElementSet]--------------------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/SWS_Crypto_91004/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeyElementSet
(
          uint32                                        cryptoKeyId,
          uint32                                        keyElementId,
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyPtr,
          uint32                                        keyLength
)
{
  Std_ReturnType retVal = E_NOT_OK;

  DBG_CRYPTO_XVIX_XAIX_KEYELEMENTSET_ENTRY(cryptoKeyId,keyElementId,keyPtr,keyLength);

#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (FALSE == Crypto_xVIx_xAIx_Initialized)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00075, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYELEMENTSET,
                           CRYPTO_XVIX_XAIX_E_UNINIT
                          );
    retVal = E_NOT_OK;
  }
  else
  if (CRYPTO_XVIX_XAIX_KEY_COUNT <= cryptoKeyId)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00076, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYELEMENTSET,
                           CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                          );
    retVal = E_NOT_OK;
  }
  else
  if (NULL_PTR == keyPtr)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00078, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYELEMENTSET,
                           CRYPTO_XVIX_XAIX_E_PARAM_POINTER
                          );
    retVal = E_NOT_OK;
  }
  else
  if (0U == keyLength)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00079, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYELEMENTSET,
                           CRYPTO_XVIX_XAIX_E_PARAM_VALUE
                          );
    retVal = E_NOT_OK;
  }
  else
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementSet/0001,1 */
    retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementSet(cryptoKeyId, keyElementId, keyPtr, keyLength);
  }

  DBG_CRYPTO_XVIX_XAIX_KEYELEMENTSET_EXIT(retVal,cryptoKeyId,keyElementId,keyPtr,keyLength);

  return retVal;
}

/*----[Crypto_xVIx_xAIx_KeyValidSet]--------------------------------------------------------------*/
/*----[Crypto_xVIx_xAIx_KeySetValid]--------------------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/SWS_Crypto_91005/0001,1 */

#if (   (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) \
     || (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_EB ) \
    )
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeyValidSet
#else /* #if (   (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) ... */
FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeySetValid
#endif /* #if (   (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) ... */
(
  uint32 cryptoKeyId
)
{
  Std_ReturnType retVal;

  DBG_CRYPTO_XVIX_XAIX_KEYSETVALID_ENTRY(cryptoKeyId);

#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (FALSE == Crypto_xVIx_xAIx_Initialized)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00082, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYVALIDSET,
                           CRYPTO_XVIX_XAIX_E_UNINIT
                          );
    retVal = E_NOT_OK;
  }
  else
  if (CRYPTO_XVIX_XAIX_KEY_COUNT <= cryptoKeyId)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00083, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYVALIDSET,
                           CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                          );
    retVal = E_NOT_OK;
  }
  else
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {

#if (   (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) \
     || (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_EB ) \
    )
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyValidSet/0001,1 */
    retVal = Crypto_xVIx_xAIx_Int_KMn_KeyValidSet(cryptoKeyId);
#else /* #if (   (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) ... */
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeySetValid/0001,1 */
    retVal = Crypto_xVIx_xAIx_Int_KMn_KeySetValid(cryptoKeyId);
#endif /* #if (   (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_430) ... */
  }

  DBG_CRYPTO_XVIX_XAIX_KEYSETVALID_EXIT(retVal,cryptoKeyId);

  return retVal;
}

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KEYSETINVALID == STD_ON)
/*----[Crypto_xVIx_xAIx_KeySetInvalid]------------------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/SWS_Crypto_91020/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeySetInvalid
(
  uint32 cryptoKeyId
)
{
  Std_ReturnType retVal = E_NOT_OK;

  DBG_CRYPTO_XVIX_XAIX_KEYSETINVALID_ENTRY(cryptoKeyId);

#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (FALSE == Crypto_xVIx_xAIx_Initialized)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00236, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYSETINVALID,
                           CRYPTO_XVIX_XAIX_E_UNINIT
                          );
    retVal = E_NOT_OK;
  }
  else
  if (CRYPTO_XVIX_XAIX_KEY_COUNT <= cryptoKeyId)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00237, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYSETINVALID,
                           CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                          );
    retVal = E_NOT_OK;
  }
  else
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00238,1 */
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeySetInvalid/0001,1 */
    retVal = Crypto_xVIx_xAIx_Int_KMn_KeySetInvalid(cryptoKeyId);
  }

  DBG_CRYPTO_XVIX_XAIX_KEYSETINVALID_EXIT(retVal,cryptoKeyId);

  return retVal;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KEYSETINVALID == STD_ON) */

#if (CRYPTO_XVIX_XAIX_API_ENABLED_KEYGETSTATUS == STD_ON)
/*----[Crypto_xVIx_xAIx_KeyGetStatus]-------------------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/SWS_Crypto_91019/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeyGetStatus
(
        uint32                                                       cryptoKeyId,
  P2VAR(Crypto_KeyStatusType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyStatusPtr
)
{
  Std_ReturnType retVal = E_NOT_OK;

  DBG_CRYPTO_XVIX_XAIX_KEYGETSTATUS_ENTRY(cryptoKeyId,keyStatusPtr);

#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (FALSE == Crypto_xVIx_xAIx_Initialized)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00232, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYGETSTATUS,
                           CRYPTO_XVIX_XAIX_E_UNINIT
                          );
    retVal = E_NOT_OK;
  }
  else
  if (CRYPTO_XVIX_XAIX_KEY_COUNT <= cryptoKeyId)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00233, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYGETSTATUS,
                           CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                          );
    retVal = E_NOT_OK;
  }
  else
  if (NULL_PTR == keyStatusPtr)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00234, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYGETSTATUS,
                           CRYPTO_XVIX_XAIX_E_PARAM_POINTER
                          );
    retVal = E_NOT_OK;
  }
  else
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyGetStatus/0001,1 */
    retVal = Crypto_xVIx_xAIx_Int_KMn_KeyGetStatus(cryptoKeyId,keyStatusPtr);
  }

  DBG_CRYPTO_XVIX_XAIX_KEYGETSTATUS_EXIT(retVal,cryptoKeyId,keyStatusPtr);

  return retVal;
}
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_KEYGETSTATUS == STD_ON) */

/*--[Crypto_xVIx_xAIx_KeyElementGet]--------------------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/SWS_Crypto_91006/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeyElementGet
(
        uint32                                         cryptoKeyId,
        uint32                                         keyElementId,
  P2VAR(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) resultPtr,
  P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) resultLengthPtr
)
{
  Std_ReturnType retVal = E_NOT_OK;

  DBG_CRYPTO_XVIX_XAIX_KEYELEMENTGET_ENTRY(cryptoKeyId,keyElementId,resultPtr,resultLengthPtr);

#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (FALSE == Crypto_xVIx_xAIx_Initialized)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00085, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYELEMENTGET,
                           CRYPTO_XVIX_XAIX_E_UNINIT
                          );
    retVal = E_NOT_OK;
  }
  else
  if (CRYPTO_XVIX_XAIX_KEY_COUNT <= cryptoKeyId)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00086, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYELEMENTGET,
                           CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                          );
    retVal = E_NOT_OK;
  }
  else
  if (NULL_PTR == resultPtr)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00088, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYELEMENTGET,
                           CRYPTO_XVIX_XAIX_E_PARAM_POINTER
                          );
    retVal = E_NOT_OK;
  }
  else
  if (NULL_PTR == resultLengthPtr)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00089, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYELEMENTGET,
                           CRYPTO_XVIX_XAIX_E_PARAM_POINTER
                          );
    retVal = E_NOT_OK;
  }
  else
  if (0U == *resultLengthPtr)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00090, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYELEMENTGET,
                           CRYPTO_XVIX_XAIX_E_PARAM_VALUE
                          );
    retVal = E_NOT_OK;
  }
  else
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementGet/0001,1 */
    retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementGet(cryptoKeyId,
                                                    keyElementId,
                                                    resultPtr,
                                                    resultLengthPtr
                                                   );
  }

  DBG_CRYPTO_XVIX_XAIX_KEYELEMENTGET_EXIT(retVal,cryptoKeyId,keyElementId,resultPtr,resultLengthPtr);

  return retVal;
}

/*--[Crypto_xVIx_xAIx_KeyElementCopy]-------------------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/SWS_Crypto_00148/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeyElementCopy
(
  uint32 cryptoKeyId,
  uint32 keyElementId,
  uint32 targetCryptoKeyId,
  uint32 targetKeyElementId
)
{
  Std_ReturnType retVal = E_NOT_OK;

#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
  uint32 SourceKeyElementIndex;
  uint32 TargetKeyElementIndex;
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */

  DBG_CRYPTO_XVIX_XAIX_KEYELEMENTCOPY_ENTRY(cryptoKeyId,keyElementId,targetCryptoKeyId,targetKeyElementId);

#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (FALSE == Crypto_xVIx_xAIx_Initialized)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00149, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYELEMENTCOPY,
                           CRYPTO_XVIX_XAIX_E_UNINIT
                          );
    retVal = E_NOT_OK;
  }
  else
  if (CRYPTO_XVIX_XAIX_KEY_COUNT <= cryptoKeyId)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00150, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYELEMENTCOPY,
                           CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                          );
    retVal = E_NOT_OK;
  }
  else
  if (CRYPTO_XVIX_XAIX_KEY_COUNT <= targetCryptoKeyId)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00151, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYELEMENTCOPY,
                           CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                          );
    retVal = E_NOT_OK;
  }
  else
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
    /* Find referenced source keyElement within the cryptoKey */
    for(SourceKeyElementIndex = 0U;
        SourceKeyElementIndex < Crypto_xVIx_xAIx_Keys[cryptoKeyId].cnfg->keyElementsCount;
        SourceKeyElementIndex++
       )
    {
      if (Crypto_xVIx_xAIx_Keys[cryptoKeyId].cnfg->keyElements[SourceKeyElementIndex].cnfg->description->id == keyElementId)
      {
        break;
      }
    }

    if (SourceKeyElementIndex == Crypto_xVIx_xAIx_Keys[cryptoKeyId].cnfg->keyElementsCount)
    {
      /* !LINKSTO Crypto.Asr.SWS_Crypto_00152, 1 */
      (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                             CRYPTO_XVIX_XAIX_INSTANCE_ID,
                             CRYPTO_XVIX_XAIX_SID_KEYELEMENTCOPY,
                             CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                            );
      retVal = E_NOT_OK;
    }
    else
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
    {
#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
      /* Find referenced target keyElement within the cryptoKey */
      for (TargetKeyElementIndex = 0U;
           TargetKeyElementIndex < Crypto_xVIx_xAIx_Keys[targetCryptoKeyId].cnfg->keyElementsCount;
           TargetKeyElementIndex++
          )
      {
        if (   Crypto_xVIx_xAIx_Keys[targetCryptoKeyId].cnfg->keyElements[TargetKeyElementIndex].cnfg->description->id
            == targetKeyElementId
           )
        {
          break;
        }
      }

      if (TargetKeyElementIndex == Crypto_xVIx_xAIx_Keys[targetCryptoKeyId].cnfg->keyElementsCount)
      {
        /* !LINKSTO Crypto.Asr.SWS_Crypto_00153, 1 */
        (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                               CRYPTO_XVIX_XAIX_INSTANCE_ID,
                               CRYPTO_XVIX_XAIX_SID_KEYELEMENTCOPY,
                               CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                              );
        retVal = E_NOT_OK;
      }
      else
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
      {
        /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementCopy/0001,1 */
        /* !LINKSTO Crypto.Asr.SWS_Crypto_00154,1 */
        retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementCopy(cryptoKeyId,
                                                         keyElementId,
                                                         targetCryptoKeyId,
                                                         targetKeyElementId
                                                        );
      }
    }
  }

  DBG_CRYPTO_XVIX_XAIX_KEYELEMENTCOPY_EXIT(retVal,cryptoKeyId,keyElementId,targetCryptoKeyId,targetKeyElementId);

  return retVal;
}

/*--[Crypto_xVIx_xAIx_KeyCopy]--------------------------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/SWS_Crypto_00155/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeyCopy
(
  uint32 cryptoKeyId,
  uint32 targetCryptoKeyId
)
{
  Std_ReturnType retVal = E_NOT_OK;

  DBG_CRYPTO_XVIX_XAIX_KEYCOPY_ENTRY(cryptoKeyId,targetCryptoKeyId);

#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (FALSE == Crypto_xVIx_xAIx_Initialized)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00156, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYCOPY,
                           CRYPTO_XVIX_XAIX_E_UNINIT
                          );
    retVal = E_NOT_OK;
  }
  else
  if (CRYPTO_XVIX_XAIX_KEY_COUNT <= cryptoKeyId)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00157, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYCOPY,
                           CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                          );
    retVal = E_NOT_OK;
  }
  else
  if (CRYPTO_XVIX_XAIX_KEY_COUNT <= targetCryptoKeyId)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00158, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYCOPY,
                           CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                          );
    retVal = E_NOT_OK;
  }
  else
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyCopy/0001,1 */
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00159,1 */
    retVal = Crypto_xVIx_xAIx_Int_KMn_KeyCopy(cryptoKeyId, targetCryptoKeyId);
  }

  DBG_CRYPTO_XVIX_XAIX_KEYCOPY_EXIT(retVal,cryptoKeyId,targetCryptoKeyId);

  return retVal;
}

/*--[Crypto_xVIx_xAIx_KeyElementIdsGet]-----------------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/SWS_Crypto_00160/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeyElementIdsGet
(
        uint32                                         cryptoKeyId,
  P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyElementIdsPtr,
  P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) keyElementIdsLengthPtr
)
{
  Std_ReturnType retVal = E_NOT_OK;

  DBG_CRYPTO_XVIX_XAIX_KEYELEMENTIDSGET_ENTRY(cryptoKeyId,keyElementIdsPtr,keyElementIdsLengthPtr);

#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (FALSE == Crypto_xVIx_xAIx_Initialized)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00161, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYELEMENTIDSGET,
                           CRYPTO_XVIX_XAIX_E_UNINIT
                          );
    retVal = E_NOT_OK;
  }
  else
  if (CRYPTO_XVIX_XAIX_KEY_COUNT <= cryptoKeyId)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00162, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYELEMENTIDSGET,
                           CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                          );
    retVal = E_NOT_OK;
  }
  else
  if (NULL_PTR == keyElementIdsPtr)
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementIdsGet/0002, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYELEMENTIDSGET,
                           CRYPTO_XVIX_XAIX_E_PARAM_POINTER
                          );
    retVal = E_NOT_OK;
  }
  else
  if (NULL_PTR == keyElementIdsLengthPtr)
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementIdsGet/0003, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYELEMENTIDSGET,
                           CRYPTO_XVIX_XAIX_E_PARAM_POINTER
                          );
    retVal = E_NOT_OK;
  }
  else

#if (!((CRYPTO_XVIX_XAIX_API_ENABLED_DETRUNTIMECHECKS == STD_ON) && (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_431)))
  if (*keyElementIdsLengthPtr < Crypto_xVIx_xAIx_Keys[cryptoKeyId].cnfg->keyElementsCount)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00164, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYELEMENTIDSGET,
                           CRYPTO_E_SMALL_BUFFER
                          );
    retVal = CRYPTO_E_SMALL_BUFFER;
  }
  else

#endif /* #if (!((CRYPTO_XVIX_XAIX_API_ENABLED_DETRUNTIMECHECKS == STD_ON) && (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_431)))  */
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */

#if ((CRYPTO_XVIX_XAIX_API_ENABLED_DETRUNTIMECHECKS == STD_ON) && (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_431))
  if (*keyElementIdsLengthPtr < Crypto_xVIx_xAIx_Keys[cryptoKeyId].cnfg->keyElementsCount)
  {

    /* !LINKSTO Crypto.Asr.SWS_Crypto_00110,1 */
    (void) Det_ReportRuntimeError(CRYPTO_XVIX_XAIX_MODULE_ID,
                                  CRYPTO_XVIX_XAIX_INSTANCE_ID,
                                  CRYPTO_XVIX_XAIX_SID_KEYELEMENTIDSGET,
                                  CRYPTO_XVIX_XAIX_E_RE_SMALL_BUFFER
                                 );
    retVal = CRYPTO_E_SMALL_BUFFER;
  }
  else
#endif /* #if ((CRYPTO_XVIX_XAIX_API_ENABLED_DETRUNTIMECHECKS == STD_ON) && (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_431)) */
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyElementIdsGet/0001,1 */
    retVal = Crypto_xVIx_xAIx_Int_KMn_KeyElementIdsGet(cryptoKeyId,
                                                       keyElementIdsPtr,
                                                       keyElementIdsLengthPtr
                                                      );
  }

  DBG_CRYPTO_XVIX_XAIX_KEYELEMENTIDSGET_EXIT(retVal,cryptoKeyId,keyElementIdsPtr,keyElementIdsLengthPtr);

  return retVal;
}

/*--[Crypto_xVIx_xAIx_RandomSeed]-----------------------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/SWS_Crypto_91013/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_RandomSeed
(
          uint32                                        cryptoKeyId,
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) seedPtr,
          uint32                                        seedLength
)
{
  Std_ReturnType retVal = E_NOT_OK;

  DBG_CRYPTO_XVIX_XAIX_RANDOMSEED_ENTRY(cryptoKeyId,seedPtr,seedLength);

#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (FALSE == Crypto_xVIx_xAIx_Initialized)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00128, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_RANDOMSEED,
                           CRYPTO_XVIX_XAIX_E_UNINIT
                          );
    retVal = E_NOT_OK;
  }
  else
  if (CRYPTO_XVIX_XAIX_KEY_COUNT <= cryptoKeyId)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00129, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_RANDOMSEED,
                           CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                          );
    retVal = E_NOT_OK;
  }
  else
  if (NULL_PTR == seedPtr)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00130,1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_RANDOMSEED,
                           CRYPTO_XVIX_XAIX_E_PARAM_POINTER
                          );
    retVal = E_NOT_OK;
  }
  else
  if (0U == seedLength)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00131,1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_RANDOMSEED,
                           CRYPTO_XVIX_XAIX_E_PARAM_VALUE
                          );
    retVal = E_NOT_OK;
  }
  else
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_RandomSeed/0001,1 */
    retVal = Crypto_xVIx_xAIx_Int_KMn_RandomSeed(cryptoKeyId, seedPtr, seedLength);
  }

  DBG_CRYPTO_XVIX_XAIX_RANDOMSEED_EXIT(retVal,cryptoKeyId,seedPtr,seedLength);

  return retVal;
}

/*--[Crypto_xVIx_xAIx_KeyGenerate]----------------------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/SWS_Crypto_91007/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeyGenerate
(
  uint32 cryptoKeyId
)
{
  Std_ReturnType retVal = E_NOT_OK;

  DBG_CRYPTO_XVIX_XAIX_KEYGENERATE_ENTRY(cryptoKeyId);

#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (FALSE == Crypto_xVIx_xAIx_Initialized)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00094, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYGENERATE,
                           CRYPTO_XVIX_XAIX_E_UNINIT
                          );
    retVal = E_NOT_OK;
  }
  else
  if (CRYPTO_XVIX_XAIX_KEY_COUNT <= cryptoKeyId)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00095, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYGENERATE,
                           CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                          );
    retVal = E_NOT_OK;
  }
  else
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00165,1 */
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyGenerate/0001,1 */
    retVal = Crypto_xVIx_xAIx_Int_KMn_KeyGenerate(cryptoKeyId);
  }

  DBG_CRYPTO_XVIX_XAIX_KEYGENERATE_EXIT(retVal,cryptoKeyId);

  return retVal;
}

/*--[Crypto_xVIx_xAIx_KeyDerive]------------------------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/SWS_Crypto_91008/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeyDerive
(
  uint32 cryptoKeyId,
  uint32 targetCryptoKeyId
)
{
  Std_ReturnType retVal = E_NOT_OK;

  DBG_CRYPTO_XVIX_XAIX_KEYDERIVE_ENTRY(cryptoKeyId,targetCryptoKeyId);

#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (FALSE == Crypto_xVIx_xAIx_Initialized)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00097, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYDERIVE,
                           CRYPTO_XVIX_XAIX_E_UNINIT
                          );
    retVal = E_NOT_OK;
  }
  else
  if (CRYPTO_XVIX_XAIX_KEY_COUNT <= cryptoKeyId)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00098, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYDERIVE,
                           CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                          );
    retVal = E_NOT_OK;
  }
  else
  if (CRYPTO_XVIX_XAIX_KEY_COUNT <= targetCryptoKeyId)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00180, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYDERIVE,
                           CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                          );
    retVal = E_NOT_OK;
  }
  else
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyDerive/0001, 1 */
    retVal = Crypto_xVIx_xAIx_Int_KMn_KeyDerive(cryptoKeyId, targetCryptoKeyId);
  }

  DBG_CRYPTO_XVIX_XAIX_KEYDERIVE_EXIT(retVal,cryptoKeyId,targetCryptoKeyId);

  return retVal;
}

/*--[Crypto_xVIx_xAIx_KeyExchangeCalcPubVal]------------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/SWS_Crypto_91009/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeyExchangeCalcPubVal
(
        uint32                                         cryptoKeyId,
  P2VAR(uint8,  AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) publicValuePtr,
  P2VAR(uint32, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) publicValueLengthPtr
)
{
  Std_ReturnType retVal = E_NOT_OK;

  DBG_CRYPTO_XVIX_XAIX_KEYEXCHANGECALCPUBVAL_ENTRY(cryptoKeyId,publicValuePtr,publicValueLengthPtr);

#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (FALSE == Crypto_xVIx_xAIx_Initialized)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00103, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYEXCHANGECALCPUBVAL,
                           CRYPTO_XVIX_XAIX_E_UNINIT
                          );
    retVal = E_NOT_OK;
  }
  else
  if (CRYPTO_XVIX_XAIX_KEY_COUNT <= cryptoKeyId)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00104, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYEXCHANGECALCPUBVAL,
                           CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                          );
    retVal = E_NOT_OK;
  }
  else
  if (NULL_PTR == publicValuePtr)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00105, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYEXCHANGECALCPUBVAL,
                           CRYPTO_XVIX_XAIX_E_PARAM_POINTER
                          );
    retVal = E_NOT_OK;
  }
  else
  if (NULL_PTR == publicValueLengthPtr)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00106,1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYEXCHANGECALCPUBVAL,
                           CRYPTO_XVIX_XAIX_E_PARAM_POINTER
                          );
    retVal = E_NOT_OK;
  }
  else
  if (0U == *publicValueLengthPtr)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00107,1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYEXCHANGECALCPUBVAL,
                           CRYPTO_XVIX_XAIX_E_PARAM_VALUE
                          );
    retVal = E_NOT_OK;
  }
  else
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyExchangeCalcPubVal/0001,1 */
    retVal = Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcPubVal(cryptoKeyId,
                                                            publicValuePtr,
                                                            publicValueLengthPtr
                                                           );
  }
#if ((CRYPTO_XVIX_XAIX_API_ENABLED_DETRUNTIMECHECKS == STD_ON) && (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_431))
  if (CRYPTO_E_SMALL_BUFFER == retVal)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00110, 1 */
    (void) Det_ReportRuntimeError(CRYPTO_XVIX_XAIX_MODULE_ID,
                                  CRYPTO_XVIX_XAIX_INSTANCE_ID,
                                  CRYPTO_XVIX_XAIX_SID_KEYEXCHANGECALCPUBVAL,
                                  CRYPTO_XVIX_XAIX_E_RE_SMALL_BUFFER
                                 );
  }
#else /* #if ((CRYPTO_XVIX_XAIX_API_ENABLED_DETRUNTIMECHECKS == STD_ON) && (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_431)) */
#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (CRYPTO_E_SMALL_BUFFER == retVal)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00110, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYEXCHANGECALCPUBVAL,
                           CRYPTO_E_SMALL_BUFFER
                          );
  }
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */

#endif /* #if ((CRYPTO_XVIX_XAIX_API_ENABLED_DETRUNTIMECHECKS == STD_ON) && (CRYPTO_XVIX_XAIX_API_VERSION == CRYPTO_API_VERSION_431)) */

  DBG_CRYPTO_XVIX_XAIX_KEYEXCHANGECALCPUBVAL_EXIT(retVal,cryptoKeyId,publicValuePtr,publicValueLengthPtr);

  return retVal;
}

/*--[Crypto_xVIx_xAIx_KeyExchangeCalcSecret]------------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/SWS_Crypto_91010/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_KeyExchangeCalcSecret
(
          uint32                                        cryptoKeyId,
  P2CONST(uint8, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) partnerPublicValuePtr,
          uint32                                        partnerPublicValueLength
)
{
  Std_ReturnType retVal = E_NOT_OK;

  DBG_CRYPTO_XVIX_XAIX_KEYEXCHANGECALCSECRET_ENTRY(cryptoKeyId,partnerPublicValuePtr,partnerPublicValueLength);

#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (FALSE == Crypto_xVIx_xAIx_Initialized)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00111, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYEXCHANGECALCSECRET,
                           CRYPTO_XVIX_XAIX_E_UNINIT
                          );
    retVal = E_NOT_OK;
  }
  else
  if (CRYPTO_XVIX_XAIX_KEY_COUNT <= cryptoKeyId)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00112, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYEXCHANGECALCSECRET,
                           CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                          );
    retVal = E_NOT_OK;
  }
  else
  if (NULL_PTR == partnerPublicValuePtr)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00113, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYEXCHANGECALCSECRET,
                           CRYPTO_XVIX_XAIX_E_PARAM_POINTER
                          );
    retVal = E_NOT_OK;
  }
  else
  if (0U == partnerPublicValueLength)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00115,1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_KEYEXCHANGECALCSECRET,
                           CRYPTO_XVIX_XAIX_E_PARAM_VALUE
                          );
    retVal = E_NOT_OK;
  }
  else
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_KeyExchangeCalcSecret/0001,1 */
    retVal = Crypto_xVIx_xAIx_Int_KMn_KeyExchangeCalcSecret(cryptoKeyId,
                                                            partnerPublicValuePtr,
                                                            partnerPublicValueLength
                                                           );
  }

  DBG_CRYPTO_XVIX_XAIX_KEYEXCHANGECALCSECRET_EXIT(retVal,cryptoKeyId,partnerPublicValuePtr,partnerPublicValueLength);

  return retVal;
}

/*--[Crypto_xVIx_xAIx_CertificateParse]-----------------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/SWS_Crypto_91011/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CertificateParse
(
  uint32 cryptoKeyId
)
{
  Std_ReturnType retVal = E_NOT_OK;

  DBG_CRYPTO_XVIX_XAIX_CERTIFICATEPARSE_ENTRY(cryptoKeyId);

#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (FALSE == Crypto_xVIx_xAIx_Initialized)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00168, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_CERTIFICATEPARSE,
                           CRYPTO_XVIX_XAIX_E_UNINIT
                          );
    retVal = E_NOT_OK;
  }
  else
  if (CRYPTO_XVIX_XAIX_KEY_COUNT <= cryptoKeyId)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00169, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_CERTIFICATEPARSE,
                           CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                          );
    retVal = E_NOT_OK;
  }
  else
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
  /* CHECK: NOPARSE
   * Certificate parsing is not implemented, thus the internal Crypto_xVIx_xAIx_Int_KMn_CertificateParse
   * always returns E_NOT_OK.
   */
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CertificateParse/0001,1 */
    retVal = Crypto_xVIx_xAIx_Int_KMn_CertificateParse(cryptoKeyId);
  }
  /* CHECK: PARSE */

  DBG_CRYPTO_XVIX_XAIX_CERTIFICATEPARSE_EXIT(retVal,cryptoKeyId);

  /* !LINKSTO Crypto.Asr.SWS_Crypto_00170,1 */
  return retVal;
}

/*--[Crypto_xVIx_xAIx_CertificateVerify]----------------------------------------------------------*/

/* !LINKSTO Crypto.Dsn.Api/Interfaces/SWS_Crypto_00171/0001,1 */

FUNC(Std_ReturnType, CRYPTO_xVIx_xAIx_CODE) Crypto_xVIx_xAIx_CertificateVerify
(
        uint32                                                          cryptoKeyId,
        uint32                                                          verifyCryptoKeyId,
  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CRYPTO_xVIx_xAIx_APPL_DATA) verifyPtr
)
{
  Std_ReturnType retVal = E_NOT_OK;

  DBG_CRYPTO_XVIX_XAIX_CERTIFICATEVERIFY_ENTRY(cryptoKeyId,verifyCryptoKeyId,verifyPtr);

#if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (FALSE == Crypto_xVIx_xAIx_Initialized)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00172, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_CERTIFICATEVERIFY,
                           CRYPTO_XVIX_XAIX_E_UNINIT
                          );
    retVal = E_NOT_OK;
  }
  else
  if (   (CRYPTO_XVIX_XAIX_KEY_COUNT <= cryptoKeyId      )
      || (CRYPTO_XVIX_XAIX_KEY_COUNT <= verifyCryptoKeyId)
     )
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00173, 1 */
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00174,1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_CERTIFICATEVERIFY,
                           CRYPTO_XVIX_XAIX_E_PARAM_HANDLE
                          );
    retVal = E_NOT_OK;
  }
  else
  if (NULL_PTR == verifyPtr)
  {
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00175, 1 */
    (void) Det_ReportError(CRYPTO_XVIX_XAIX_MODULE_ID,
                           CRYPTO_XVIX_XAIX_INSTANCE_ID,
                           CRYPTO_XVIX_XAIX_SID_CERTIFICATEVERIFY,
                           CRYPTO_XVIX_XAIX_E_PARAM_POINTER
                          );
    retVal = E_NOT_OK;
  }
  else
#endif /* #if (CRYPTO_XVIX_XAIX_API_ENABLED_DEVERRORDETECT == STD_ON) */
  /* CHECK: NOPARSE
   * Certificate validation is not implemented, thus the internal Crypto_xVIx_xAIx_Int_KMn_CertificateVerify
   * always returns E_NOT_OK.
   */
  {
    /* !LINKSTO Crypto.Dsn.Api/Crypto_xVIx_xAIx_CertificateVerify/0001,1 */
    /* !LINKSTO Crypto.Asr.SWS_Crypto_00177,1 */
    retVal = Crypto_xVIx_xAIx_Int_KMn_CertificateVerify(cryptoKeyId, verifyCryptoKeyId, verifyPtr);
  }
  /* CHECK: PARSE */

  DBG_CRYPTO_XVIX_XAIX_CERTIFICATEVERIFY_EXIT(retVal,cryptoKeyId,verifyCryptoKeyId,verifyPtr);

  return retVal;
}

#define CRYPTO_xVIx_xAIx_STOP_SEC_CODE
#include <Crypto_xVIx_xAIx_MemMap.h>

/*==================[internal function definitions]===============================================*/

#endif /*#if (CRYPTO_XVIX_XAIX_KEYMNGMT_ENABLED == STD_ON) */

/*================================================================================================*/

/*==================[end of file]=================================================================*/

