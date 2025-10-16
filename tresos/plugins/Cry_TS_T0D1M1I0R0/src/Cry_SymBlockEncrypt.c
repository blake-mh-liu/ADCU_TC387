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

#include <Cry_SymBlockEncrypt.h>

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

CONST(uint32, CRYSTUB_40_CONST) Cry_SymBlockEncryptCfg = 0U;

#define CRYSTUB_40_STOP_SEC_CONST_32
#include <CryStub_40_MemMap.h>

/*==================[internal constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[internal data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CRYSTUB_40_START_SEC_CODE
#include <CryStub_40_MemMap.h>

/*------------------------------------------------------------------------------------------------*/
/*----[Cry_SymBlockEncryptStart]------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_SymBlockEncryptStart
(
  P2CONST(void,           AUTOMATIC, CRYSTUB_40_APPL_DATA) cfgPtr,
  P2CONST(Csm_SymKeyType, AUTOMATIC, CRYSTUB_40_APPL_DATA) keyPtr
)
{
  CRY_PARAM_UNUSED(cfgPtr);
  CRY_PARAM_UNUSED(keyPtr);

  return CSM_E_OK;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cry_SymBlockEncryptUpdate]-----------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_SymBlockEncryptUpdate
(
  P2CONST(uint8,  AUTOMATIC, CRYSTUB_40_APPL_DATA) plainTextPtr,
          uint32                                   plainTextLength,
    P2VAR(uint8,  AUTOMATIC, CRYSTUB_40_APPL_DATA) cipherTextPtr,
    P2VAR(uint32, AUTOMATIC, CRYSTUB_40_APPL_DATA) cipherTextLengthPtr
)
{
  CRY_PARAM_UNUSED(plainTextPtr);
  CRY_PARAM_UNUSED(plainTextLength);
  CRY_PARAM_UNUSED(cipherTextPtr);
  CRY_PARAM_UNUSED(cipherTextLengthPtr);

  return CSM_E_OK;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cry_SymBlockEncryptFinish]-----------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_SymBlockEncryptFinish
(
  void
)
{

  return CSM_E_OK;
}

/*------------------------------------------------------------------------------------------------*/
/*----[Cry_SymBlockEncryptMainFunction]-----------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

FUNC(void, CRYSTUB_40_CODE) Cry_SymBlockEncryptMainFunction
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

