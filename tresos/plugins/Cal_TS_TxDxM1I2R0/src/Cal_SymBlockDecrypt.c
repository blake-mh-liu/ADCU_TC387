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
#include <Cal_SymBlockDecrypt.h>
#include <Cal_SymBlockDecrypt_Cfg.h>

#if (CAL_SYMBLOCKDECRYPT_ENABLED == TRUE)


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
/*----[Cal_SymBlockDecryptStart]------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_SymBlockDecryptStart
(
  Cal_ConfigIdType                                             cfgId,
  Cal_SymBlockDecryptCtxBufType                                contextBuffer,
  P2CONST(Cal_SymKeyType,            AUTOMATIC, CAL_APPL_DATA) keyPtr
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_SYMBLOCKDECRYPTSTART_ENTRY(cfgId,contextBuffer,keyPtr);

  /* !LINKSTO CAL0063, 1
   */
  /* !LINKSTO CAL0046, 1
   */
  if(CAL_SYMBLOCKDECRYPT_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_SymBlockDecConfigurations[cfgId].PrimitiveStartFct
    (
      (P2CONST(void, AUTOMATIC, CAL_APPL_DATA)) Cal_SymBlockDecConfigurations[cfgId].PrimitiveConfigPtr,
      contextBuffer,
      keyPtr
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


  DBG_CAL_SYMBLOCKDECRYPTSTART_EXIT(RetVal,cfgId,contextBuffer,keyPtr);
  return RetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cal_SymBlockDecryptUpdate]-----------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_SymBlockDecryptUpdate
(
  Cal_ConfigIdType                                             cfgId,
  Cal_SymBlockDecryptCtxBufType                                contextBuffer,
  P2CONST(uint8,                     AUTOMATIC, CAL_APPL_DATA) cipherTextPtr,
  uint32                                                       cipherTextLength,
  P2VAR(uint8,                       AUTOMATIC, CAL_APPL_DATA) plainTextPtr,
  P2VAR(uint32,                      AUTOMATIC, CAL_APPL_DATA) plainTextLengthPtr
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_SYMBLOCKDECRYPTUPDATE_ENTRY(cfgId,contextBuffer,cipherTextPtr,cipherTextLength,plainTextPtr,plainTextLengthPtr);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_SYMBLOCKDECRYPT_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_SymBlockDecConfigurations[cfgId].PrimitiveUpdateFct
    (
      (P2CONST(void, AUTOMATIC, CAL_APPL_DATA)) Cal_SymBlockDecConfigurations[cfgId].PrimitiveConfigPtr,
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


  DBG_CAL_SYMBLOCKDECRYPTUPDATE_EXIT(RetVal,cfgId,contextBuffer,cipherTextPtr,cipherTextLength,plainTextPtr,plainTextLengthPtr);
  return RetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cal_SymBlockDecryptFinish]-----------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_SymBlockDecryptFinish
(
  Cal_ConfigIdType              cfgId,
  Cal_SymBlockDecryptCtxBufType contextBuffer
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_SYMBLOCKDECRYPTFINISH_ENTRY(cfgId,contextBuffer);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_SYMBLOCKDECRYPT_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_SymBlockDecConfigurations[cfgId].PrimitiveFinishFct
    (
      (P2CONST(void, AUTOMATIC, CAL_APPL_DATA)) Cal_SymBlockDecConfigurations[cfgId].PrimitiveConfigPtr,
      contextBuffer
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


  DBG_CAL_SYMBLOCKDECRYPTFINISH_EXIT(RetVal,cfgId,contextBuffer);
  return RetVal;
}

#define CAL_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function definitions]===============================================*/
#else /* #if (CAL_SYMBLOCKDECRYPT_ENABLED == TRUE) */

/** Dummy definition preventing this file from being empty, if there is no SymBlockDecrypt
 *  configuration.
 */
typedef void CalPrvntEmptyTranslationUnit_t;


#endif /* #if (CAL_SYMBLOCKDECRYPT_ENABLED == TRUE) #else */

/*==================[end of file]=================================================================*/

