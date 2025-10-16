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

#include <Cry_Hash.h>

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

CONST(uint32, CRYSTUB_40_CONST) Cry_HashCfg = 0U;

#define CRYSTUB_40_STOP_SEC_CONST_32
#include <CryStub_40_MemMap.h>

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYSTUB_40_START_SEC_CODE
#include <CryStub_40_MemMap.h>

/*------------------------------------------------------------------------------------------------*/
/*----[Cry_HashStart]-----------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_HashStart
(
  P2CONST(void, AUTOMATIC, CRYSTUB_40_APPL_DATA) cfgPtr
)
{
  CRY_PARAM_UNUSED(cfgPtr);

  return CSM_E_OK;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cry_HashUpdate]----------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_HashUpdate
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
/*----[Cry_HashFinish]----------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_HashFinish
(
  P2VAR(uint8,   AUTOMATIC, CRYSTUB_40_APPL_DATA) resultPtr,
  P2VAR(uint32,  AUTOMATIC, CRYSTUB_40_APPL_DATA) resultLengthPtr,
        boolean                                   TruncationIsAllowed
)
{
  CRY_PARAM_UNUSED(resultPtr);
  CRY_PARAM_UNUSED(resultLengthPtr);
  CRY_PARAM_UNUSED(TruncationIsAllowed);

  return CSM_E_OK;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cry_HashAlgorithmId]-----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(P2CONST(uint8, AUTOMATIC, CRYSTUB_40_APPL_DATA), CRYSTUB_40_CODE) Cry_HashAlgorithmId
(
  P2CONST(void,   AUTOMATIC, CRYSTUB_40_APPL_DATA) cfgPtr,
    P2VAR(uint32, AUTOMATIC, CRYSTUB_40_APPL_DATA) AlgorithmIdLengthPtr
)
{
  static P2CONST(uint8, AUTOMATIC, CRYSTUB_40_APPL_DATA) ret = NULL_PTR;

  CRY_PARAM_UNUSED(cfgPtr);
  CRY_PARAM_UNUSED(AlgorithmIdLengthPtr);

  return ret;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cry_HashMainFunction]----------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(void, CRYSTUB_40_CODE) Cry_HashMainFunction
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

