/**
 * \file
 *
 * \brief AUTOSAR Cry
 *
 * This file contains the implementation of the AUTOSAR
 * module Cry.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2019 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*================================================================================================*/

/*==================[includes]====================================================================*/

#include <Cry_SignatureGenerate.h>

/*==================[macros]======================================================================*/

#if !defined(CRY_PARAM_UNUSED)
#define CRY_PARAM_UNUSED(x) ((void) (x))
#endif

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

/*==================[internal function declarations]==============================================*/

/*==================[external constants]==========================================================*/

#define CRYSTUB_40_START_SEC_CONST_32
#include <CryStub_40_MemMap.h>

CONST(uint32, CRYSTUB_40_CONST) Cry_SignatureGenerateCfg = 0U;

#define CRYSTUB_40_STOP_SEC_CONST_32
#include <CryStub_40_MemMap.h>

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYSTUB_40_START_SEC_CODE
#include <CryStub_40_MemMap.h>

/*------------------------------------------------------------------------------------------------*/
/*----[Cry_SignatureGenerateStart]----------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_SignatureGenerateStart
(
  P2CONST(void,                   AUTOMATIC, CRYSTUB_40_APPL_DATA) cfgPtr,
  P2CONST(Csm_AsymPrivateKeyType, AUTOMATIC, CRYSTUB_40_APPL_DATA) keyPtr
)
{
  CRY_PARAM_UNUSED(cfgPtr);
  CRY_PARAM_UNUSED(keyPtr);

  return CSM_E_OK;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cry_SignatureGenerateUpdate]---------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_SignatureGenerateUpdate
(
  P2CONST(uint8,  AUTOMATIC, CRYSTUB_40_APPL_DATA) dataPtr,
          uint32                                   dataLength
)
{
  CRY_PARAM_UNUSED(dataPtr);
  CRY_PARAM_UNUSED(dataLength);

  return CSM_E_OK;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cry_SignatureGenerateFinish]---------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_SignatureGenerateFinish
(
  P2VAR(uint8,  AUTOMATIC, CRYSTUB_40_APPL_DATA) resultPtr,
  P2VAR(uint32, AUTOMATIC, CRYSTUB_40_APPL_DATA) resultLengthPtr
)
{
  CRY_PARAM_UNUSED(resultPtr);
  CRY_PARAM_UNUSED(resultLengthPtr);

  return CSM_E_OK;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cry_SignatureGenerateMainFunction]---------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(void, CRYSTUB_40_CODE) Cry_SignatureGenerateMainFunction
(
  void
)
{
}

#define CRYSTUB_40_STOP_SEC_CODE
#include <CryStub_40_MemMap.h>

/*==================[internal function definitions]===============================================*/

/*================================================================================================*/

/*==================[end of file]=================================================================*/

