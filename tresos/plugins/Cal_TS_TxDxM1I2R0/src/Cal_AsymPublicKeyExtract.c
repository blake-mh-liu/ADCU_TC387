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

#include <Cal_AsymPublicKeyExtract.h>
#include <Cal_AsymPublicKeyExtract_Cfg.h>

#if (CAL_ASYM_PUB_KEY_EXTRACT_ENABLED == TRUE)


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
/*----[Cal_AsymPublicKeyExtractStart]-------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_AsymPublicKeyExtractStart
(
  Cal_ConfigIdType                   cfgId,
  Cal_AsymPublicKeyExtractCtxBufType contextBuffer
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_ASYMPUBLICKEYEXTRACTSTART_ENTRY(cfgId,contextBuffer);

  /* !LINKSTO CAL0063, 1
   */
  /* !LINKSTO CAL0046, 1
   */
  if(cfgId < CAL_ASYMPUBKEYEXTRACT_CFG_COUNT)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_AsymPublicKeyExtractConfigs[cfgId].PrimitiveStartFct
    (
      Cal_AsymPublicKeyExtractConfigs[cfgId].PrimitiveConfigPtr,
      contextBuffer
    );
  }else
  {
    /* !LINKSTO CAL0488, 1
     */
    /* !LINKSTO CAL0539, 1
     */
    RetVal = CAL_E_NOT_OK;
  }


  DBG_CAL_ASYMPUBLICKEYEXTRACTSTART_EXIT(RetVal,cfgId,contextBuffer);
  return RetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cal_AsymPublicKeyExtractUpdate]------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_AsymPublicKeyExtractUpdate
(
  Cal_ConfigIdType                         cfgId,
  Cal_AsymPublicKeyExtractCtxBufType       contextBuffer,
  P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) dataPtr,
  uint32                                   dataLength
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_ASYMPUBLICKEYEXTRACTUPDATE_ENTRY(cfgId,contextBuffer,dataPtr,dataLength);

  /* !LINKSTO CAL0063, 1
   */
  if(cfgId < CAL_ASYMPUBKEYEXTRACT_CFG_COUNT)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_AsymPublicKeyExtractConfigs[cfgId].PrimitiveUpdateFct
    (
      Cal_AsymPublicKeyExtractConfigs[cfgId].PrimitiveConfigPtr,
      contextBuffer,
      dataPtr,
      dataLength
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


  DBG_CAL_ASYMPUBLICKEYEXTRACTUPDATE_EXIT(RetVal,cfgId,contextBuffer,dataPtr,dataLength);
  return RetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cal_AsymPublicKeyExtractFinish]------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_AsymPublicKeyExtractFinish
(
  Cal_ConfigIdType                                       cfgId,
  Cal_AsymPublicKeyExtractCtxBufType                     contextBuffer,
  P2VAR(Cal_AsymPublicKeyType, AUTOMATIC, CAL_APPL_DATA) keyPtr
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_ASYMPUBLICKEYEXTRACTFINISH_ENTRY(cfgId,contextBuffer,keyPtr);

  /* !LINKSTO CAL0063, 1
   */
  if(cfgId < CAL_ASYMPUBKEYEXTRACT_CFG_COUNT)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_AsymPublicKeyExtractConfigs[cfgId].PrimitiveFinishFct
    (
      Cal_AsymPublicKeyExtractConfigs[cfgId].PrimitiveConfigPtr,
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


  DBG_CAL_ASYMPUBLICKEYEXTRACTFINISH_EXIT(RetVal,cfgId,contextBuffer,keyPtr);
  return RetVal;
}


#define CAL_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function definitions]===============================================*/
#else /* #if (CAL_ASYM_PUB_KEY_EXTRACT_ENABLED == TRUE) */

/** Dummy definition preventing this file from being empty, if there is no AsymPublicKeyExtract
 *  configuration.
 */
typedef void CalPrvntEmptyTranslationUnit_t;


#endif /* #if (CAL_ASYM_PUB_KEY_EXTRACT_ENABLED == TRUE) #else */

/*==================[end of file]=================================================================*/

