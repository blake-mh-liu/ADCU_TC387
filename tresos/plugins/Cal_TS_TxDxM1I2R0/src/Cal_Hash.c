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

/*==[Includes]================================================================*/

#include <Cal_Trace.h>
#include <Cal_Types.h>

#include <Cal_Hash.h>
#include <Cal_Hash_Cfg.h>

/*==[Macros]==================================================================*/

/*==[Types]===================================================================*/

/*==[Declaration of functions with internal linkage]==========================*/

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with internal linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

/*==[Constants with external linkage]=========================================*/

/*==[Definition of functions with external linkage]===========================*/

#if (CAL_HASH_ENABLED == TRUE)

#define CAL_START_SEC_CODE
#include <MemMap.h>


FUNC(Cal_ReturnType, CAL_CODE) Cal_HashStart
(
  Cal_ConfigIdType   cfgId,
  Cal_HashCtxBufType contextBuffer
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_HASHSTART_ENTRY(cfgId,contextBuffer);

  /* !LINKSTO CAL0063, 1
   */
  /* !LINKSTO CAL0046, 1
   */
  if(CAL_HASH_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_HashConfigurations[cfgId].PrimitiveStartFct
    (
       Cal_HashConfigurations[cfgId].PrimitiveConfigPtr,
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


  DBG_CAL_HASHSTART_EXIT(RetVal,cfgId,contextBuffer);
  return RetVal;
}




FUNC(Cal_ReturnType, CAL_CODE) Cal_HashUpdate
(
  Cal_ConfigIdType                         cfgId,
  Cal_HashCtxBufType                       contextBuffer,
  P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) dataPtr,
  uint32                                   dataLength
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_HASHUPDATE_ENTRY(cfgId,contextBuffer,dataPtr,dataLength);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_HASH_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal =
       Cal_HashConfigurations[cfgId].PrimitiveUpdateFct
       (
         Cal_HashConfigurations[cfgId].PrimitiveConfigPtr,
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

  DBG_CAL_HASHUPDATE_EXIT(RetVal,cfgId,contextBuffer,dataPtr,dataLength);
  return RetVal;
}


FUNC(Cal_ReturnType, CAL_CODE) Cal_HashFinish
(
  Cal_ConfigIdType                         cfgId,
  Cal_HashCtxBufType                       contextBuffer,
  P2VAR(uint8,  AUTOMATIC, CAL_APPL_DATA)  resultPtr,
  P2VAR(uint32, AUTOMATIC, CAL_APPL_DATA)  resultLengthPtr,
  boolean                                  truncationAllowed
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_HASHFINISH_ENTRY(cfgId,contextBuffer,resultPtr,resultLengthPtr,truncationAllowed);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_HASH_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal =
       Cal_HashConfigurations[cfgId].PrimitiveFinishFct
       (
          Cal_HashConfigurations[cfgId].PrimitiveConfigPtr,
          contextBuffer,
          resultPtr,
          resultLengthPtr,
          truncationAllowed
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


  DBG_CAL_HASHFINISH_EXIT(RetVal,cfgId,contextBuffer,resultPtr,resultLengthPtr,truncationAllowed);
  return RetVal;
}


#define CAL_STOP_SEC_CODE
#include <MemMap.h>

#else /* #if (CAL_HASH_ENABLED == TRUE) */

/** Dummy definition preventing this file from being empty, if there is no Hash
 *  configuration.
 */
typedef void CalPrvntEmptyTranslationUnit_t;



#endif /* #if (CAL_HASH_ENABLED == TRUE) #else */

/*==[Definition of functions with internal linkage]===========================*/

