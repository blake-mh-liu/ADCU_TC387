/**
 * \file
 *
 * \brief AUTOSAR Cal
 *
 * This file contains the implementation of the AUTOSAR
 * module Cal.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[includes]====================================================================*/
#include <Cal_Trace.h>
#include <Cal_Types.h>
#include <Cal_SymDecrypt.h>
#include <Cal_SymDecrypt_Cfg.h>

#if (CAL_SYM_DECRYPT_ENABLED == TRUE)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CAL_START_SEC_CODE
#include <MemMap.h>

/*------------------------------------------------------------------------------------------------*/
/*----[Cal_SymDecryptStart]-----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_SymDecryptStart
(
  VAR(Cal_ConfigIdType,         AUTOMATIC               ) cfgId,
  VAR(Cal_SymDecryptCtxBufType, AUTOMATIC               ) contextBuffer,
  P2CONST(Cal_SymKeyType,       AUTOMATIC, CAL_APPL_DATA) keyPtr,
  P2CONST(uint8,                AUTOMATIC, CAL_APPL_DATA) InitVectorPtr,
  VAR(uint32,                   AUTOMATIC               ) InitVectorLength
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_SYMDECRYPTSTART_ENTRY(cfgId,contextBuffer,keyPtr,InitVectorPtr,InitVectorLength);

  /* !LINKSTO CAL0063, 1
   */
  /* !LINKSTO CAL0046, 1
   */
  if(CAL_SYMDECRYPT_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_SymDecryptConfigurations[cfgId].PrimitiveStartFct
    (
      Cal_SymDecryptConfigurations[cfgId].PrimitiveConfigPtr,
      contextBuffer,
      keyPtr,
      InitVectorPtr,
      InitVectorLength
    );
  }
  else
  {
    /* !LINKSTO CAL0488, 1
     */
    /* !LINKSTO CAL0539, 1
     */
    RetVal = CAL_E_NOT_OK;
  }


  DBG_CAL_SYMDECRYPTSTART_EXIT(RetVal,cfgId,contextBuffer,keyPtr,InitVectorPtr,InitVectorLength);
  return RetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cal_SymDecryptUpdate]----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_SymDecryptUpdate
(
  VAR(Cal_ConfigIdType,         AUTOMATIC               ) cfgId,
  VAR(Cal_SymDecryptCtxBufType, AUTOMATIC               ) contextBuffer,
  P2CONST(uint8,                AUTOMATIC, CAL_APPL_DATA) cipherTextPtr,
  VAR(uint32,                   AUTOMATIC               ) cipherTextLength,
  P2VAR(uint8,                  AUTOMATIC, CAL_APPL_DATA) plainTextPtr,
  P2VAR(uint32,                 AUTOMATIC, CAL_APPL_DATA) plainTextLengthPtr
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_SYMDECRYPTUPDATE_ENTRY(cfgId,contextBuffer,cipherTextPtr,cipherTextLength,plainTextPtr,plainTextLengthPtr);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_SYMDECRYPT_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_SymDecryptConfigurations[cfgId].PrimitiveUpdateFct
    (
      Cal_SymDecryptConfigurations[cfgId].PrimitiveConfigPtr,
      contextBuffer,
      cipherTextPtr,
      cipherTextLength,
      plainTextPtr,
      plainTextLengthPtr
    );
  }
  else
  {
    /* !LINKSTO CAL0488, 1
     */
    /* !LINKSTO CAL0539, 1
     */
    RetVal = CAL_E_NOT_OK;
  }


  DBG_CAL_SYMDECRYPTUPDATE_EXIT(RetVal,cfgId,contextBuffer,cipherTextPtr,cipherTextLength,plainTextPtr,plainTextLengthPtr);
  return RetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cal_SymDecryptFinish]----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_SymDecryptFinish
(
  VAR(Cal_ConfigIdType,         AUTOMATIC               ) cfgId,
  VAR(Cal_SymDecryptCtxBufType, AUTOMATIC               ) contextBuffer,
  P2VAR(uint8,                  AUTOMATIC, CAL_APPL_DATA) plainTextPtr,
  P2VAR(uint32,                 AUTOMATIC, CAL_APPL_DATA) plainTextLengthPtr
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_SYMDECRYPTFINISH_ENTRY(cfgId,contextBuffer,plainTextPtr,plainTextLengthPtr);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_SYMDECRYPT_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_SymDecryptConfigurations[cfgId].PrimitiveFinishFct
    (
      Cal_SymDecryptConfigurations[cfgId].PrimitiveConfigPtr,
      contextBuffer,
      plainTextPtr,
      plainTextLengthPtr
    );
  }
  else
  {
    /* !LINKSTO CAL0488, 1
     */
    /* !LINKSTO CAL0539, 1
     */
    RetVal = CAL_E_NOT_OK;
  }


  DBG_CAL_SYMDECRYPTFINISH_EXIT(RetVal,cfgId,contextBuffer,plainTextPtr,plainTextLengthPtr);
  return RetVal;
}



#define CAL_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function definitions]===============================================*/
#else /* #if (CAL_SYM_DECRYPT_ENABLED == TRUE) */



/** Dummy definition preventing this file from being empty, if there is no SymDecrypt
 *  configuration.
 */
typedef void CalPrvntEmptyTranslationUnit_t;

#endif /* #if (CAL_SYM_DECRYPT_ENABLED == TRUE) #else */

/*==================[end of file]=================================================================*/

