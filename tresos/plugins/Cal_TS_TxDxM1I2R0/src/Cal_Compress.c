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

/* !LINKSTO EB_CAL_0801_001, 1
 */

/*==================[includes]====================================================================*/

#include <Cal_Trace.h>
#include <Cal_Types.h>
#include <Cal_Compress.h>
#include <Cal_Compress_Cfg.h>



#if (CAL_COMPRESS_ENABLED == STD_ON)

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
/*----[Cal_CompressStart]-------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_CompressStart
(
  VAR(Cal_ConfigIdType,       AUTOMATIC) cfgId,
  VAR(Cal_CompressCtxBufType, AUTOMATIC) contextBuffer
)
{
  VAR(Cal_ReturnType, AUTOMATIC) RetVal;

  DBG_CAL_COMPRESSSTART_ENTRY(cfgId,contextBuffer);

  /* !LINKSTO CAL0063, 1
   */
  /* !LINKSTO CAL0046, 1
   */
  if(CAL_COMPRESS_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_CompressConfigurations[cfgId].PrimitiveStartFct
    (
      (P2CONST(void, AUTOMATIC, CAL_APPL_DATA))
        Cal_CompressConfigurations[cfgId].PrimitiveConfigPtr,
      contextBuffer
    );
  }
  else
  {
    /* !LINKSTO CAL0488, 1
     */
    /* !LINKSTO CAL0539, 1
     */
    /* !LINKSTO EB_CAL_0804_001, 1
     */
    RetVal = CAL_E_NOT_OK;
  }


  DBG_CAL_COMPRESSSTART_EXIT(RetVal,cfgId,contextBuffer);
  return RetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cal_CompressUpdate]------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_CompressUpdate
(
      VAR(Cal_ConfigIdType,       AUTOMATIC               ) cfgId,
      VAR(Cal_CompressCtxBufType, AUTOMATIC               ) contextBuffer,
  P2CONST(uint8,                  AUTOMATIC, CAL_APPL_DATA) iputBuf,
    P2VAR(uint32,                 AUTOMATIC, CAL_APPL_DATA) iputBufLen,
    P2VAR(uint8,                  AUTOMATIC, CAL_APPL_DATA) oputBuf,
    P2VAR(uint32,                 AUTOMATIC, CAL_APPL_DATA) oputBufLen
)
{
  VAR(Cal_ReturnType, AUTOMATIC) RetVal;

  DBG_CAL_COMPRESSUPDATE_ENTRY(cfgId,contextBuffer,iputBuf,iputBufLen,oputBuf,oputBufLen);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_COMPRESS_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_CompressConfigurations[cfgId].PrimitiveUpdateFct
    (
      (P2CONST(void, AUTOMATIC, CAL_APPL_DATA))
        Cal_CompressConfigurations[cfgId].PrimitiveConfigPtr,
      contextBuffer,
      iputBuf,
      iputBufLen,
      oputBuf,
      oputBufLen
    );
  }
  else
  {
    /* !LINKSTO CAL0488, 1
     */
    /* !LINKSTO CAL0539, 1
     */
    /* !LINKSTO EB_CAL_0804_006, 1
     */
    RetVal = CAL_E_NOT_OK;
  }


  DBG_CAL_COMPRESSUPDATE_EXIT(RetVal,cfgId,contextBuffer,iputBuf,iputBufLen,oputBuf,oputBufLen);
  return RetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cal_CompressFinish]------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_CompressFinish
(
    VAR(Cal_ConfigIdType,       AUTOMATIC               ) cfgId,
    VAR(Cal_CompressCtxBufType, AUTOMATIC               ) contextBuffer,
  P2VAR(uint8,                  AUTOMATIC, CAL_APPL_DATA) oputBuf,
  P2VAR(uint32,                 AUTOMATIC, CAL_APPL_DATA) oputBufLen
)
{
  VAR(Cal_ReturnType, AUTOMATIC) RetVal;

  DBG_CAL_COMPRESSFINISH_ENTRY(cfgId,contextBuffer,oputBuf,oputBufLen);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_COMPRESS_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_CompressConfigurations[cfgId].PrimitiveFinishFct
    (
      (P2CONST(void, AUTOMATIC, CAL_APPL_DATA))
        Cal_CompressConfigurations[cfgId].PrimitiveConfigPtr,
      contextBuffer,
      oputBuf,
      oputBufLen
    );
  }
  else
  {
    /* !LINKSTO CAL0488, 1
     */
    /* !LINKSTO CAL0539, 1
     */
    /* !LINKSTO EB_CAL_0804_011, 1
     */
    RetVal = CAL_E_NOT_OK;
  }


  DBG_CAL_COMPRESSFINISH_EXIT(RetVal,cfgId,contextBuffer,oputBuf,oputBufLen);
  return RetVal;
}

#define CAL_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function definitions]===============================================*/

/*================================================================================================*/

#else /* #if (CAL_COMPRESS_ENABLED == STD_ON) */

/** \brief  Dummy definition preventing this file from being empty, if there is no compression
 **         configuration.
 **/
typedef void CalPrvntEmptyTranslationUnit_t;

#endif /* #if (CAL_COMPRESS_ENABLED == STD_ON) #else */

/*==================[end of file]=================================================================*/

