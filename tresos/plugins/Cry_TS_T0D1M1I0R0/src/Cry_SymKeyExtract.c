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

#include <Cry_SymKeyExtract.h>

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

CONST(uint32, CRYSTUB_40_CONST) Cry_SymKeyExtractCfg = 0U;

#define CRYSTUB_40_STOP_SEC_CONST_32
#include <CryStub_40_MemMap.h>

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYSTUB_40_START_SEC_CODE
#include <CryStub_40_MemMap.h>

/*------------------------------------------------------------------------------------------------*/
/*----[Cry_SymKeyExtractStart]--------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_SymKeyExtractStart
(
  P2CONST(void, AUTOMATIC, CRYSTUB_40_APPL_DATA) cfgPtr
)
{
  CRY_PARAM_UNUSED(cfgPtr);

  return CSM_E_OK;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cry_SymKeyExtractUpdate]-------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_SymKeyExtractUpdate
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
/*----[Cry_SymKeyExtractFinish]-------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_SymKeyExtractFinish
(
  P2VAR(Csm_SymKeyType, AUTOMATIC, CRYSTUB_40_APPL_DATA) keyPtr
)
{
  CRY_PARAM_UNUSED(keyPtr);

  return CSM_E_OK;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cry_SymKeyExtractMainFunction]-------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(void, CRYSTUB_40_CODE) Cry_SymKeyExtractMainFunction
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

