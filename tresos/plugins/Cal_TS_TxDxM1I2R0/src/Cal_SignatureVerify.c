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
#include <Cal_SignatureVerify.h>
#include <Cal_SignatureVerify_Cfg.h>

#if (CAL_SIG_VRFY_ENABLED == TRUE)

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

FUNC(Cal_ReturnType, CAL_CODE) Cal_SignatureVerifyStart
(
  Cal_ConfigIdType                                         cfgId,
  Cal_SignatureVerifyCtxBufType                            contextBuffer,
  P2CONST(Cal_AsymPublicKeyType, AUTOMATIC, CAL_APPL_DATA) keyPtr
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_SIGNATUREVERIFYSTART_ENTRY(cfgId,contextBuffer,keyPtr);

  /* !LINKSTO CAL0046, 1
   */
  /* !LINKSTO CAL0063, 1
   */
  if(CAL_SIGVRFY_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_SigVerifyConfigurations[cfgId].PrimitiveStartFct
    (
      Cal_SigVerifyConfigurations[cfgId].PrimitiveConfigPtr,
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


  DBG_CAL_SIGNATUREVERIFYSTART_EXIT(RetVal,cfgId,contextBuffer,keyPtr);
  return RetVal;
}


FUNC(Cal_ReturnType, CAL_CODE) Cal_SignatureVerifyUpdate
(
  Cal_ConfigIdType                         cfgId,
  Cal_SignatureVerifyCtxBufType            contextBuffer,
  P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) dataPtr,
  uint32                                   dataLength
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_SIGNATUREVERIFYUPDATE_ENTRY(cfgId,contextBuffer,dataPtr,dataLength);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_SIGVRFY_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_SigVerifyConfigurations[cfgId].PrimitiveUpdateFct
    (
      Cal_SigVerifyConfigurations[cfgId].PrimitiveConfigPtr,
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


  DBG_CAL_SIGNATUREVERIFYUPDATE_EXIT(RetVal,cfgId,contextBuffer,dataPtr,dataLength);
  return RetVal;
}


FUNC(Cal_ReturnType, CAL_CODE) Cal_SignatureVerifyFinish
(
  Cal_ConfigIdType                                      cfgId,
  Cal_SignatureVerifyCtxBufType                         contextBuffer,
  P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA)              signaturePtr,
  uint32                                                signatureLength,
  P2VAR(Cal_VerifyResultType, AUTOMATIC, CAL_APPL_DATA) resultPtr
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_SIGNATUREVERIFYFINISH_ENTRY(cfgId,contextBuffer,signaturePtr,signatureLength,resultPtr);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_SIGVRFY_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_SigVerifyConfigurations[cfgId].PrimitiveFinishFct
    (
      Cal_SigVerifyConfigurations[cfgId].PrimitiveConfigPtr,
      contextBuffer,
      signaturePtr,
      signatureLength,
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


  DBG_CAL_SIGNATUREVERIFYFINISH_EXIT(RetVal,cfgId,contextBuffer,signaturePtr,signatureLength,resultPtr);
  return RetVal;
}


#define CAL_STOP_SEC_CODE
#include <MemMap.h>



/*==[Definition of functions with internal linkage]===========================*/
#else /* #if (CAL_SIG_VRFY_ENABLED == TRUE) */

/** Dummy definition preventing this file from being empty, if there is no SignatureVerify
 *  configuration.
 */
typedef void CalPrvntEmptyTranslationUnit_t;

#endif /* #if (CAL_SIG_VRFY_ENABLED == TRUE) #else */

