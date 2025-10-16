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

#include <Cry_AsymPrivateKeyWrapSym.h>

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

CONST(uint32, CRYSTUB_40_CONST) Cry_AsymPrivateKeyWrapSymCfg = 0U;

#define CRYSTUB_40_STOP_SEC_CONST_32
#include <CryStub_40_MemMap.h>

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYSTUB_40_START_SEC_CODE
#include <CryStub_40_MemMap.h>

/*------------------------------------------------------------------------------------------------*/
/*----[Cry_AsymPrivateKeyWrapSymStart]------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_AsymPrivateKeyWrapSymStart
(
  P2CONST(void,                   AUTOMATIC, CRYSTUB_40_APPL_DATA) cfgPtr,
  P2CONST(Csm_AsymPrivateKeyType, AUTOMATIC, CRYSTUB_40_APPL_DATA) keyPtr,
  P2CONST(Csm_SymKeyType,         AUTOMATIC, CRYSTUB_40_APPL_DATA) wrappingKeyPtr
)
{
  CRY_PARAM_UNUSED(cfgPtr);
  CRY_PARAM_UNUSED(keyPtr);
  CRY_PARAM_UNUSED(wrappingKeyPtr);

  return CSM_E_OK;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cry_AsymPrivateKeyWrapSymUpdate]-----------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_AsymPrivateKeyWrapSymUpdate
(
  P2VAR(uint8,  AUTOMATIC, CRYSTUB_40_APPL_DATA) dataPtr,
  P2VAR(uint32, AUTOMATIC, CRYSTUB_40_APPL_DATA) dataLengthPtr
)
{
  CRY_PARAM_UNUSED(dataPtr);
  CRY_PARAM_UNUSED(dataLengthPtr);

  return CSM_E_OK;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cry_AsymPrivateKeyWrapSymFinish]-----------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_AsymPrivateKeyWrapSymFinish
(
  void
)
{

  return CSM_E_OK;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cry_AsymPrivateKeyWrapSymMainFunction]-----------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(void, CRYSTUB_40_CODE) Cry_AsymPrivateKeyWrapSymMainFunction
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

