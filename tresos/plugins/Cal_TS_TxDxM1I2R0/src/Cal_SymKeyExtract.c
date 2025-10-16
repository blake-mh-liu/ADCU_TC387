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
#include <Cal_SymKeyExtract.h>
#include <Cal_SymKeyExtract_Cfg.h>

#if (CAL_SYM_KEY_EXTRACT_ENABLED == TRUE)


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
/*----[Cal_SymKeyExtractStart]--------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_SymKeyExtractStart
(
  Cal_ConfigIdType            cfgId,
  Cal_SymKeyExtractCtxBufType contextBuffer
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_SYMKEYEXTRACTSTART_ENTRY(cfgId,contextBuffer);

  /* !LINKSTO CAL0063, 1
   */
  /* !LINKSTO CAL0046, 1
   */
  if(CAL_SYMKEYEX_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_SymKeyExtractConfigurations[cfgId].PrimitiveStartFct
    (
      Cal_SymKeyExtractConfigurations[cfgId].PrimitiveConfigPtr,
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


  DBG_CAL_SYMKEYEXTRACTSTART_EXIT(RetVal,cfgId,contextBuffer);
  return RetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cal_SymKeyExtractUpdate]-------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_SymKeyExtractUpdate
(
  Cal_ConfigIdType                         cfgId,
  Cal_SymKeyExtractCtxBufType              contextBuffer,
  P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) dataPtr,
  uint32                                   dataLength
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_SYMKEYEXTRACTUPDATE_ENTRY(cfgId,contextBuffer,dataPtr,dataLength);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_SYMKEYEX_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_SymKeyExtractConfigurations[cfgId].PrimitiveUpdateFct
    (
      Cal_SymKeyExtractConfigurations[cfgId].PrimitiveConfigPtr,
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


  DBG_CAL_SYMKEYEXTRACTUPDATE_EXIT(RetVal,cfgId,contextBuffer,dataPtr,dataLength);
  return RetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cal_SymKeyExtractFinish]-------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_SymKeyExtractFinish
(
  Cal_ConfigIdType                                cfgId,
  Cal_SymKeyExtractCtxBufType                     contextBuffer,
  P2VAR(Cal_SymKeyType, AUTOMATIC, CAL_APPL_DATA) keyPtr
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_SYMKEYEXTRACTFINISH_ENTRY(cfgId,contextBuffer,keyPtr);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_SYMKEYEX_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_SymKeyExtractConfigurations[cfgId].PrimitiveFinishFct
    (
      Cal_SymKeyExtractConfigurations[cfgId].PrimitiveConfigPtr,
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


  DBG_CAL_SYMKEYEXTRACTFINISH_EXIT(RetVal,cfgId,contextBuffer,keyPtr);
  return RetVal;
}


#define CAL_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function definitions]===============================================*/
#else /* #if (CAL_SYM_KEY_EXTRACT_ENABLED == TRUE) */


/** Dummy definition preventing this file from being empty, if there is no SymKeyExtract
 *  configuration.
 */
typedef void CalPrvntEmptyTranslationUnit_t;


#endif /* #if (CAL_SYM_KEY_EXTRACT_ENABLED == TRUE) #else */

/*==================[end of file]=================================================================*/

