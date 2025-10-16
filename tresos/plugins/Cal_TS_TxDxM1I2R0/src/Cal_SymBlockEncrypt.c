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
#include <Cal_SymBlockEncrypt.h>
#include <Cal_SymBlockEncrypt_Cfg.h>

#if (CAL_SYMBLOCKENCRYPT_ENABLED == TRUE)


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
/*----[Cal_SymBlockEncryptStart]------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_SymBlockEncryptStart
(
  VAR(Cal_ConfigIdType,              AUTOMATIC               ) cfgId,
  VAR(Cal_SymBlockEncryptCtxBufType, AUTOMATIC               ) contextBuffer,
  P2CONST(Cal_SymKeyType,            AUTOMATIC, CAL_APPL_DATA) keyPtr
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_SYMBLOCKENCRYPTSTART_ENTRY(cfgId,contextBuffer,keyPtr);

  /* !LINKSTO CAL0063, 1
   */
  /* !LINKSTO CAL0046, 1
   */
  if(CAL_SYMBLOCKENCRYPT_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_SymBlockEncConfigurations[cfgId].PrimitiveStartFct
    (
      (P2CONST(void, AUTOMATIC, CAL_APPL_DATA))
        Cal_SymBlockEncConfigurations[cfgId].PrimitiveConfigPtr,
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


  DBG_CAL_SYMBLOCKENCRYPTSTART_EXIT(RetVal,cfgId,contextBuffer,keyPtr);
  return RetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cal_SymBlockEncryptUpdate]-----------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_SymBlockEncryptUpdate
(
  VAR(Cal_ConfigIdType,              AUTOMATIC               ) cfgId,
  VAR(Cal_SymBlockEncryptCtxBufType, AUTOMATIC               ) contextBuffer,
  P2CONST(uint8,                     AUTOMATIC, CAL_APPL_DATA) plainTextPtr,
  VAR(uint32,                        AUTOMATIC               ) plainTextLength,
  P2VAR(uint8,                       AUTOMATIC, CAL_APPL_DATA) cipherTextPtr,
  P2VAR(uint32,                      AUTOMATIC, CAL_APPL_DATA) cipherTextLengthPtr
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_SYMBLOCKENCRYPTUPDATE_ENTRY(cfgId,contextBuffer,plainTextPtr,plainTextLength,cipherTextPtr,cipherTextLengthPtr);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_SYMBLOCKENCRYPT_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_SymBlockEncConfigurations[cfgId].PrimitiveUpdateFct
    (
      (P2CONST(void, AUTOMATIC, CAL_APPL_DATA)) Cal_SymBlockEncConfigurations[cfgId].PrimitiveConfigPtr,
      contextBuffer,
      plainTextPtr,
      plainTextLength,
      cipherTextPtr,
      cipherTextLengthPtr
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


  DBG_CAL_SYMBLOCKENCRYPTUPDATE_EXIT(RetVal,cfgId,contextBuffer,plainTextPtr,plainTextLength,cipherTextPtr,cipherTextLengthPtr);
  return RetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cal_SymBlockEncryptFinish]-----------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_SymBlockEncryptFinish
(
  VAR(Cal_ConfigIdType,              AUTOMATIC               ) cfgId,
  VAR(Cal_SymBlockEncryptCtxBufType, AUTOMATIC               ) contextBuffer
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_SYMBLOCKENCRYPTFINISH_ENTRY(cfgId,contextBuffer);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_SYMBLOCKENCRYPT_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_SymBlockEncConfigurations[cfgId].PrimitiveFinishFct
    (
      (P2CONST(void, AUTOMATIC, CAL_APPL_DATA)) Cal_SymBlockEncConfigurations[cfgId].PrimitiveConfigPtr,
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


  DBG_CAL_SYMBLOCKENCRYPTFINISH_EXIT(RetVal,cfgId,contextBuffer);
  return RetVal;
}


#define CAL_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function definitions]===============================================*/
#else /* #if (CAL_SYMBLOCKENCRYPT_ENABLED == TRUE) */


/** Dummy definition preventing this file from being empty, if there is no SymBlockEncrypt
 *  configuration.
 */
typedef void CalPrvntEmptyTranslationUnit_t;


#endif /* #if (CAL_SYMBLOCKENCRYPT_ENABLED == TRUE) #else */

/*==================[end of file]=================================================================*/

