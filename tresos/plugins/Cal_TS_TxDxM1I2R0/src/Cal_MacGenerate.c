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
#include <Cal_MacGenerate.h>
#include <Cal_MacGenerate_Cfg.h>

#if (CAL_MAC_GENERATE_ENABLED == TRUE)

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
/*----[Cal_MacGenerateStart]----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_MacGenerateStart
(
  Cal_ConfigIdType                                  cfgId,
  Cal_MacGenerateCtxBufType                         contextBuffer,
  P2CONST(Cal_SymKeyType, AUTOMATIC, CAL_APPL_DATA) keyPtr
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_MACGENERATESTART_ENTRY(cfgId,contextBuffer,keyPtr);

  /* !LINKSTO CAL0063, 1
   */
  /* !LINKSTO CAL0046, 1
   */
  if(CAL_MACGEN_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal =
      Cal_MacGenerateConfigurations[cfgId].PrimitiveStartFct
      (
        (P2CONST(void, AUTOMATIC, CAL_APPL_DATA))
          Cal_MacGenerateConfigurations[cfgId].PrimitiveConfigPtr,
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


  DBG_CAL_MACGENERATESTART_EXIT(RetVal,cfgId,contextBuffer,keyPtr);
  return RetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cal_MacGenerateUpdate]---------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_MacGenerateUpdate
(
  Cal_ConfigIdType                                  cfgId,
  Cal_MacGenerateCtxBufType                         contextBuffer,
  P2CONST(uint8,  AUTOMATIC, CAL_APPL_DATA)         dataPtr,
  uint32                                            dataLength
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_MACGENERATEUPDATE_ENTRY(cfgId,contextBuffer,dataPtr,dataLength);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_MACGEN_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal =
      Cal_MacGenerateConfigurations[cfgId].PrimitiveUpdateFct
      (
        (P2CONST(void, AUTOMATIC, CAL_APPL_DATA))
                Cal_MacGenerateConfigurations[cfgId].PrimitiveConfigPtr,
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


  DBG_CAL_MACGENERATEUPDATE_EXIT(RetVal,cfgId,contextBuffer,dataPtr,dataLength);
  return RetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cal_MacGenerateFinish]---------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_MacGenerateFinish
(
  Cal_ConfigIdType                        cfgId,
  Cal_MacGenerateCtxBufType               contextBuffer,
  P2VAR(uint8,  AUTOMATIC, CAL_APPL_DATA) resultPtr,
  P2VAR(uint32, AUTOMATIC, CAL_APPL_DATA) resultLengthPtr,
  boolean                                 truncationIsAllowed
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_MACGENERATEFINISH_ENTRY(cfgId,contextBuffer,resultPtr,resultLengthPtr,truncationIsAllowed);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_MACGEN_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal =
      Cal_MacGenerateConfigurations[cfgId].PrimitiveFinishFct
      (
        (P2CONST(void, AUTOMATIC, CAL_APPL_DATA))
          Cal_MacGenerateConfigurations[cfgId].PrimitiveConfigPtr,
        contextBuffer,
        resultPtr,
        resultLengthPtr,
        truncationIsAllowed
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


  DBG_CAL_MACGENERATEFINISH_EXIT(RetVal,cfgId,contextBuffer,resultPtr,resultLengthPtr,truncationIsAllowed);
  return RetVal;
}



#define CAL_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function definitions]===============================================*/
#else /* #if (CAL_MAC_GENERATE_ENABLED == TRUE) */

/** Dummy definition preventing this file from being empty, if there is no MacGenerate
 *  configuration.
 */
typedef void CalPrvntEmptyTranslationUnit_t;

#endif /* #if (CAL_MAC_GENERATE_ENABLED == TRUE) #else */

/*==================[end of file]=================================================================*/

