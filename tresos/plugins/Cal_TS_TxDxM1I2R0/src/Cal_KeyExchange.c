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
#include <Cal_KeyExchange.h>
#include <Cal_KeyExchange_Cfg.h>


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

#if (CAL_KEYEXCHANGE_PUBVAL_ENABLED == TRUE)

FUNC(Cal_ReturnType, CAL_CODE) Cal_KeyExchangeCalcPubVal
(
  Cal_ConfigIdType                                              cfgId,
  P2CONST(Cal_KeyExchangeBaseType,    AUTOMATIC, CAL_APPL_DATA) basePtr,
  P2CONST(Cal_KeyExchangePrivateType, AUTOMATIC, CAL_APPL_DATA) privateValuePtr,
  P2VAR(uint8,                        AUTOMATIC, CAL_APPL_DATA) publicValuePtr,
  P2VAR(uint32,                       AUTOMATIC, CAL_APPL_DATA) publicValueLengthPtr
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_KEYEXCHANGECALCPUBVAL_ENTRY(cfgId,basePtr,privateValuePtr,publicValuePtr,publicValueLengthPtr);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_KEYEXPUBVAL_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_KeyExPubValConfigurations[cfgId].PrimitiveCalcPubValFct
    (
      Cal_KeyExPubValConfigurations[cfgId].PrimitiveConfigPtr,
      basePtr,
      privateValuePtr,
      publicValuePtr,
      publicValueLengthPtr
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


  DBG_CAL_KEYEXCHANGECALCPUBVAL_EXIT(RetVal,cfgId,basePtr,privateValuePtr,publicValuePtr,publicValueLengthPtr);
  return RetVal;
}
#endif /* #if (CAL_KEYEXCHANGE_PUBVAL_ENABLED == TRUE) */

#if (CAL_KEYEXCHANGE_SECRET_ENABLED == TRUE)
FUNC(Cal_ReturnType, CAL_CODE) Cal_KeyExchangeCalcSecretStart
(
  Cal_ConfigIdType                                              cfgId,
  Cal_KeyExchangeCalcSecretCtxBufType                           contextBuffer,
  P2CONST(Cal_KeyExchangeBaseType,    AUTOMATIC, CAL_APPL_DATA) basePtr,
  P2CONST(Cal_KeyExchangePrivateType, AUTOMATIC, CAL_APPL_DATA) privateValuePtr
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_KEYEXCHANGECALCSECRETSTART_ENTRY(cfgId,contextBuffer,basePtr,privateValuePtr);

  /* !LINKSTO CAL0063, 1
   */
  /* !LINKSTO CAL0046, 1
   */
  if(CAL_KEYEXSECRET_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_KeyExSecretConfigurations[cfgId].PrimitiveCalcSecretStartFct
    (
      Cal_KeyExSecretConfigurations[cfgId].PrimitiveConfigPtr,
      contextBuffer,
      basePtr,
      privateValuePtr
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


  DBG_CAL_KEYEXCHANGECALCSECRETSTART_EXIT(RetVal,cfgId,contextBuffer,basePtr,privateValuePtr);
  return RetVal;
}



FUNC(Cal_ReturnType, CAL_CODE) Cal_KeyExchangeCalcSecretUpdate
(
  Cal_ConfigIdType                         cfgId,
  Cal_KeyExchangeCalcSecretCtxBufType      contextBuffer,
  P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) partnerPublicValuePtr,
  uint32                                   partnerPublicValueLength
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_KEYEXCHANGECALCSECRETUPDATE_ENTRY(cfgId,contextBuffer,partnerPublicValuePtr,partnerPublicValueLength);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_KEYEXSECRET_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_KeyExSecretConfigurations[cfgId].PrimitiveCalcSecretUpdateFct
    (
      Cal_KeyExSecretConfigurations[cfgId].PrimitiveConfigPtr,
      contextBuffer,
      partnerPublicValuePtr,
      partnerPublicValueLength
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


  DBG_CAL_KEYEXCHANGECALCSECRETUPDATE_EXIT(RetVal,cfgId,contextBuffer,partnerPublicValuePtr,partnerPublicValueLength);
  return RetVal;
}


FUNC(Cal_ReturnType, CAL_CODE) Cal_KeyExchangeCalcSecretFinish
(
  Cal_ConfigIdType                        cfgId,
  Cal_KeyExchangeCalcSecretCtxBufType     contextBuffer,
  P2VAR(uint8,  AUTOMATIC, CAL_APPL_DATA) sharedSecretPtr,
  P2VAR(uint32, AUTOMATIC, CAL_APPL_DATA) sharedSecretLengthPtr,
  boolean                                 TruncationIsAllowed
)
{
  Cal_ReturnType RetVal;

  DBG_CAL_KEYEXCHANGECALCSECRETFINISH_ENTRY(cfgId,contextBuffer,sharedSecretPtr,sharedSecretLengthPtr,TruncationIsAllowed);

  /* !LINKSTO CAL0063, 1
   */
  if(CAL_KEYEXSECRET_CONFIG_COUNT > cfgId)
  {
    /* !LINKSTO CAL0506, 1
     */
    RetVal = Cal_KeyExSecretConfigurations[cfgId].PrimitiveCalcSecretFinishFct
    (
      Cal_KeyExSecretConfigurations[cfgId].PrimitiveConfigPtr,
      contextBuffer,
      sharedSecretPtr,
      sharedSecretLengthPtr,
      TruncationIsAllowed
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


  DBG_CAL_KEYEXCHANGECALCSECRETFINISH_EXIT(RetVal,cfgId,contextBuffer,sharedSecretPtr,sharedSecretLengthPtr,TruncationIsAllowed);
  return RetVal;
}

#else /* #if (CAL_KEYEXCHANGE_SECRET_ENABLED == TRUE) */


/** Dummy definition preventing this file from being empty, if there is no KeyExchange
 *  configuration.
 */
typedef void CalPrvntEmptyTranslationUnit_t;



#endif /* #if (CAL_KEYEXCHANGE_SECRET_ENABLED == TRUE) #else */

#define CAL_STOP_SEC_CODE
#include <MemMap.h>



/*==[Definition of functions with internal linkage]===========================*/

