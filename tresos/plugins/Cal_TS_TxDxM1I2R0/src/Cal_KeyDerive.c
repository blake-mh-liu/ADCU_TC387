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
#include <Cal_KeyDerive.h>
#include <Cal_KeyDerive_Cfg.h>

#if (CAL_KEY_DERIVE_ENABLED == TRUE)


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
/*----[Cal_KeyDeriveStart]--------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_KeyDeriveStart
(
  Cal_ConfigIdType        cfgId,
  Cal_KeyDeriveCtxBufType contextBuffer,
  uint32                  keyLength,
  uint32                  iterations
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_KEYDERIVESTART_ENTRY(cfgId,contextBuffer,keyLength,iterations);

  /* !LINKSTO CAL0063, 1
   */
  /* !LINKSTO CAL0046, 1
   */
  if(CAL_KEYDERIVE_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_KeyDeriveConfigurations[cfgId].PrimitiveStartFct
    (
      Cal_KeyDeriveConfigurations[cfgId].PrimitiveConfigPtr,
      contextBuffer,
      keyLength,
      iterations
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


  DBG_CAL_KEYDERIVESTART_EXIT(RetVal,cfgId,contextBuffer,keyLength,iterations);
  return RetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cal_KeyDeriveUpdate]-------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_KeyDeriveUpdate
(
  Cal_ConfigIdType                         cfgId,
  Cal_KeyDeriveCtxBufType                  contextBuffer,
  P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) passwordPtr,
  uint32                                   passwordLength,
  P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) saltPtr,
  uint32                                   saltLength
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_KEYDERIVEUPDATE_ENTRY(cfgId,contextBuffer,passwordPtr,passwordLength,saltPtr,saltLength);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_KEYDERIVE_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_KeyDeriveConfigurations[cfgId].PrimitiveUpdateFct
    (
      Cal_KeyDeriveConfigurations[cfgId].PrimitiveConfigPtr,
      contextBuffer,
      passwordPtr,
      passwordLength,
      saltPtr,
      saltLength
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


  DBG_CAL_KEYDERIVEUPDATE_EXIT(RetVal,cfgId,contextBuffer,passwordPtr,passwordLength,saltPtr,saltLength);
  return RetVal;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cal_KeyDeriveFinish]-------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Cal_ReturnType, CAL_CODE) Cal_KeyDeriveFinish
(
  Cal_ConfigIdType                                cfgId,
  Cal_KeyDeriveCtxBufType                     contextBuffer,
  P2VAR(Cal_SymKeyType, AUTOMATIC, CAL_APPL_DATA) keyPtr
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_KEYDERIVEFINISH_ENTRY(cfgId,contextBuffer,keyPtr);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_KEYDERIVE_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_KeyDeriveConfigurations[cfgId].PrimitiveFinishFct
    (
      Cal_KeyDeriveConfigurations[cfgId].PrimitiveConfigPtr,
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


  DBG_CAL_KEYDERIVEFINISH_EXIT(RetVal,cfgId,contextBuffer,keyPtr);
  return RetVal;
}


#define CAL_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function definitions]===============================================*/
#else /* #if (CAL_KEY_DERIVE_ENABLED == TRUE) */


/** Dummy definition preventing this file from being empty, if there is no KeyDerive
 *  configuration.
 */
typedef void CalPrvntEmptyTranslationUnit_t;



#endif /* #if (CAL_KEY_DERIVE_ENABLED == TRUE) #else */

/*==================[end of file]=================================================================*/

