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
#include <Cal_Random.h>
#include <Cal_Random_Cfg.h>



/*==[Macros]==================================================================*/



/*==[Types]===================================================================*/



/*==[Declaration of functions with internal linkage]==========================*/



/*==[Constants with internal linkage]=========================================*/



/*==[Variables with internal linkage]=========================================*/



/*==[Variables with external linkage]=========================================*/



/*==[Constants with external linkage]=========================================*/



/*==[Definition of functions with external linkage]===========================*/

#define CAL_START_SEC_CODE
#include <MemMap.h>

#if (CAL_RANDOMSEED_ENABLED == TRUE)

FUNC(Cal_ReturnType, CAL_CODE) Cal_RandomSeedStart
(
  Cal_ConfigIdType     cfgId,
  Cal_RandomCtxBufType contextBuffer
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_RANDOMSEEDSTART_ENTRY(cfgId,contextBuffer);

  /* !LINKSTO CAL0063, 1
   */
  /* !LINKSTO CAL0046, 1
   */
  if(CAL_RANDOMSEED_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_RandomSeedConfigurations[cfgId].PrimitiveSeedStartFct
    (
      Cal_RandomSeedConfigurations[cfgId].PrimitiveConfigPtr,
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


  DBG_CAL_RANDOMSEEDSTART_EXIT(RetVal,cfgId,contextBuffer);
  return RetVal;
}



FUNC(Cal_ReturnType, CAL_CODE) Cal_RandomSeedUpdate
(
  Cal_ConfigIdType                         cfgId,
  Cal_RandomCtxBufType                     contextBuffer,
  P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) seedPtr,
  uint32                                   seedLength
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_RANDOMSEEDUPDATE_ENTRY(cfgId,contextBuffer,seedPtr,seedLength);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_RANDOMSEED_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_RandomSeedConfigurations[cfgId].PrimitiveSeedUpdateFct
    (
      Cal_RandomSeedConfigurations[cfgId].PrimitiveConfigPtr,
      contextBuffer,
      seedPtr,
      seedLength
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


  DBG_CAL_RANDOMSEEDUPDATE_EXIT(RetVal,cfgId,contextBuffer,seedPtr,seedLength);
  return RetVal;
}


FUNC(Cal_ReturnType, CAL_CODE) Cal_RandomSeedFinish
(
  Cal_ConfigIdType                         cfgId,
  Cal_RandomCtxBufType                     contextBuffer
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_RANDOMSEEDFINISH_ENTRY(cfgId,contextBuffer);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_RANDOMSEED_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_RandomSeedConfigurations[cfgId].PrimitiveSeedFinishFct
    (
      Cal_RandomSeedConfigurations[cfgId].PrimitiveConfigPtr,
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


  DBG_CAL_RANDOMSEEDFINISH_EXIT(RetVal,cfgId,contextBuffer);
  return RetVal;
}

#endif /* #if (CAL_RANDOMSEED_ENABLED == TRUE) */

#if (CAL_RANDOMGEN_ENABLED == TRUE)

FUNC(Cal_ReturnType, CAL_CODE) Cal_RandomGenerate
(
   Cal_ConfigIdType                       cfgId,
   Cal_RandomCtxBufType                   contextBuffer,
   P2VAR(uint8, AUTOMATIC, CAL_APPL_DATA) resultPtr,
   uint32                                 resultLength
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_RANDOMGENERATE_ENTRY(cfgId,contextBuffer,resultPtr,resultLength);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_RANDOMGEN_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_RandomGenConfigurations[cfgId].PrimitiveGenerateFct
    (
      Cal_RandomGenConfigurations[cfgId].PrimitiveConfigPtr,
      contextBuffer,
      resultPtr,
      resultLength
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


  DBG_CAL_RANDOMGENERATE_EXIT(RetVal,cfgId,contextBuffer,resultPtr,resultLength);
  return RetVal;
}

#endif /* #if (CAL_RANDOMGEN_ENABLED == TRUE) */

#define CAL_STOP_SEC_CODE
#include <MemMap.h>


#if ((CAL_RANDOMGEN_ENABLED == FALSE) && (CAL_RANDOMSEED_ENABLED == FALSE))

/** Dummy definition preventing this file from being empty, if there is no Random
 *  configuration.
 */
typedef void CalPrvntEmptyTranslationUnit_t;


#endif /* #if ((CAL_RANDOMGEN_ENABLED == FALSE) && (CAL_RANDOMSEED_ENABLED == FALSE)) */
/*==[Definition of functions with internal linkage]===========================*/

