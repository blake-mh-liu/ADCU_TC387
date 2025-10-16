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

#include <Cal_MacVerify.h>
#include <Cal_MacVerify_Cfg.h>

#if (CAL_MAC_VERIFY_ENABLED == TRUE)

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
/*----[Cal_MacVerifyStart]----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_MacVerifyStart
(
  Cal_ConfigIdType                                  cfgId,
  Cal_MacVerifyCtxBufType                           contextBuffer,
  P2CONST(Cal_SymKeyType, AUTOMATIC, CAL_APPL_DATA) keyPtr
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_MACVERIFYSTART_ENTRY(cfgId,contextBuffer,keyPtr);

  /* !LINKSTO CAL0063, 1
   */
  /* !LINKSTO CAL0046, 1
   */
  if(CAL_MACVRFY_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal =
      Cal_MacVerifyConfigurations[cfgId].PrimitiveStartFct
      (
        (P2CONST(void, AUTOMATIC, CAL_APPL_DATA))
          Cal_MacVerifyConfigurations[cfgId].PrimitiveConfigPtr,
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


  DBG_CAL_MACVERIFYSTART_EXIT(RetVal,cfgId,contextBuffer,keyPtr);
  return RetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cal_MacVerifyUpdate]---------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_MacVerifyUpdate
(
  Cal_ConfigIdType                                  cfgId,
  Cal_MacVerifyCtxBufType                           contextBuffer,
  P2CONST(uint8,  AUTOMATIC, CAL_APPL_DATA)         dataPtr,
  uint32                                            dataLength
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_MACVERIFYUPDATE_ENTRY(cfgId,contextBuffer,dataPtr,dataLength);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_MACVRFY_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal =
      Cal_MacVerifyConfigurations[cfgId].PrimitiveUpdateFct
      (
        (P2CONST(void, AUTOMATIC, CAL_APPL_DATA))
                Cal_MacVerifyConfigurations[cfgId].PrimitiveConfigPtr,
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


  DBG_CAL_MACVERIFYUPDATE_EXIT(RetVal,cfgId,contextBuffer,dataPtr,dataLength);
  return RetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cal_MacVerifyFinish]---------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_MacVerifyFinish
(
  Cal_ConfigIdType                                      cfgId,
  Cal_MacVerifyCtxBufType                               contextBuffer,
  P2CONST(uint8,              AUTOMATIC, CAL_APPL_DATA) MacPtr,
  uint32                                                MacLength,
  P2VAR(Cal_VerifyResultType, AUTOMATIC, CAL_APPL_DATA) resultPtr
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_MACVERIFYFINISH_ENTRY(cfgId,contextBuffer,MacPtr,MacLength,resultPtr);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_MACVRFY_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal =
      Cal_MacVerifyConfigurations[cfgId].PrimitiveFinishFct
      (
        (P2CONST(void, AUTOMATIC, CAL_APPL_DATA))
          Cal_MacVerifyConfigurations[cfgId].PrimitiveConfigPtr,
        contextBuffer,
        MacPtr,
        MacLength,
        resultPtr
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


  DBG_CAL_MACVERIFYFINISH_EXIT(RetVal,cfgId,contextBuffer,MacPtr,MacLength,resultPtr);
  return RetVal;
}



#define CAL_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function definitions]===============================================*/
#else /* #if (CAL_MAC_VERIFY_ENABLED == TRUE) */

/** Dummy definition preventing this file from being empty, if there is no MacVerify
 *  configuration.
 */
typedef void CalPrvntEmptyTranslationUnit_t;

#endif /* #if (CAL_MAC_VERIFY_ENABLED == TRUE) #else */

/*==================[end of file]=================================================================*/

