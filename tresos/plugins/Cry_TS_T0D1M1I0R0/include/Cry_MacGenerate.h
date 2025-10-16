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

#ifndef CRY_MACGENERATE_H
#define CRY_MACGENERATE_H

/*==================[includes]====================================================================*/

#include <Csm.h>
#include <CryStub_40_CompilerCfg.h>

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

#define CRYSTUB_40_START_SEC_CODE
#include <CryStub_40_MemMap.h>

/** \brief  Start MAC generate computation.
 **
 ** This function requests the start of an MAC generate computation. This is a stub!
 **/
extern FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_MacGenerateStart
(
  P2CONST(void,           AUTOMATIC, CRYSTUB_40_APPL_DATA) cfgPtr,
  P2CONST(Csm_SymKeyType, AUTOMATIC, CRYSTUB_40_APPL_DATA) keyPtr
);

/** \brief  Update MAC generate computation.
 **
 ** This function requests the update of the MAC generate computation. This is a stub!
 **/
extern FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_MacGenerateUpdate
(
  P2CONST(uint8,  AUTOMATIC, CRYSTUB_40_APPL_DATA) dataPtr,
          uint32                                   dataLength
);

/** \brief  Finish MAC generate computation.
 **
 ** This function requests the finishing of the MAC generate computation. This is a stub!
 **/
extern FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_MacGenerateFinish
(
  P2VAR(uint8,   AUTOMATIC, CRYSTUB_40_APPL_DATA) resultPtr,
  P2VAR(uint32,  AUTOMATIC, CRYSTUB_40_APPL_DATA) resultLengthPtr,
        boolean                                   TruncationIsAllowed
);

/** \brief  Perform the mac generate computation tasks.
 **
 ** This function performs the actual mac generate computation tasks which have been requested
 ** by the Csm service main functions.
 **/
extern FUNC(void, CRYSTUB_40_CODE) Cry_MacGenerateMainFunction
(
  void
);

#define CRYSTUB_40_STOP_SEC_CODE
#include <CryStub_40_MemMap.h>

/*==================[external constants]==========================================================*/

#define CRYSTUB_40_START_SEC_CONST_32
#include <CryStub_40_MemMap.h>

extern CONST(uint32, CRYSTUB_40_CONST) Cry_MacGenerateCfg;

#define CRYSTUB_40_STOP_SEC_CONST_32
#include <CryStub_40_MemMap.h>

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #ifndef CRY_MACGENERATE_H */

/*==================[end of file]=================================================================*/

