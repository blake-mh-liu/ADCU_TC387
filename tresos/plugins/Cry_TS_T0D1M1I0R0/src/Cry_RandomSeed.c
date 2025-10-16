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

#include <Cry_RandomSeed.h>

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

CONST(uint32, CRYSTUB_40_CONST) Cry_RandomSeedCfg = 0U;

#define CRYSTUB_40_STOP_SEC_CONST_32
#include <CryStub_40_MemMap.h>

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYSTUB_40_START_SEC_CODE
#include <CryStub_40_MemMap.h>

/*------------------------------------------------------------------------------------------------*/
/*----[Cry_RandomSeedStart]-----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_RandomSeedStart
(
  P2CONST(void, AUTOMATIC, CRYSTUB_40_APPL_DATA) cfgPtr
)
{
  CRY_PARAM_UNUSED(cfgPtr);

  return CSM_E_OK;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cry_RandomSeedUpdate]----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_RandomSeedUpdate
(
  P2CONST(uint8,  AUTOMATIC, CRYSTUB_40_APPL_DATA) seedPtr,
          uint32                                   seedLength
)
{
  CRY_PARAM_UNUSED(seedPtr);
  CRY_PARAM_UNUSED(seedLength);

  return CSM_E_OK;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cry_RandomSeedFinish]----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_RandomSeedFinish
(
  void
)
{

  return CSM_E_OK;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cry_RandomSeedMainFunction]----------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(void, CRYSTUB_40_CODE) Cry_RandomSeedMainFunction
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

