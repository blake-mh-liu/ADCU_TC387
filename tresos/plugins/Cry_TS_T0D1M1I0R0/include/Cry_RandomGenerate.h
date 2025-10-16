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

#ifndef CRY_RANDOMGENERATE_H
#define CRY_RANDOMGENERATE_H

/*==================[includes]====================================================================*/

#include <Csm.h>
#include <CryStub_40_CompilerCfg.h>

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

#define CRYSTUB_40_START_SEC_CODE
#include <CryStub_40_MemMap.h>

/** \brief  Process random generate computation.
 **
 ** This function process the random generate computation. This is a stub!
 **/
extern FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_RandomGenerate
(
  P2CONST(void,   AUTOMATIC, CRYSTUB_40_APPL_DATA) cfgPtr,
    P2VAR(uint8,  AUTOMATIC, CRYSTUB_40_APPL_DATA) resultPtr,
          uint32                                   resultLength
);

/** \brief  Perform the random generate computation tasks.
 **
 ** This function performs the actual random generate computation tasks which have been
 ** requested by the Csm service main functions.
 **/
extern FUNC(void, CRYSTUB_40_CODE) Cry_RandomGenerateMainFunction
(
  void
);

#define CRYSTUB_40_STOP_SEC_CODE
#include <CryStub_40_MemMap.h>

/*==================[external constants]==========================================================*/

#define CRYSTUB_40_START_SEC_CONST_32
#include <CryStub_40_MemMap.h>

extern CONST(uint32, CRYSTUB_40_CONST) Cry_RandomGenerateCfg;

#define CRYSTUB_40_STOP_SEC_CONST_32
#include <CryStub_40_MemMap.h>

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #ifndef CRY_RANDOMGENERATE_H */

/*==================[end of file]=================================================================*/

