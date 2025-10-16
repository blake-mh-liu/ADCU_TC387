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

#ifndef CRY_SYMKEYEXTRACT_H
#define CRY_SYMKEYEXTRACT_H

/*==================[includes]====================================================================*/

#include <Csm.h>
#include <CryStub_40_CompilerCfg.h>

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

#define CRYSTUB_40_START_SEC_CODE
#include <CryStub_40_MemMap.h>

/** \brief  Start symmetrical key extraction computation.
 **
 ** This function requests the start of an symmetrical key extraction computation. This is a
 ** stub!
 **/
extern FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_SymKeyExtractStart
(
  P2CONST(void, AUTOMATIC, CRYSTUB_40_APPL_DATA) cfgPtr
);

/** \brief  Update symmetrical key extraction computation.
 **
 ** This function requests the update of the symmetrical key extraction computation. This is a
 ** stub!
 **/
extern FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_SymKeyExtractUpdate
(
  P2CONST(uint8,  AUTOMATIC, CRYSTUB_40_APPL_DATA) dataPtr,
          uint32                                   dataLength
);

/** \brief  Finish symmetrical key extraction computation.
 **
 ** This function requests the finishing of the symmetrical key extraction computation. This is
 ** a stub!
 **/
extern FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_SymKeyExtractFinish
(
  P2VAR(Csm_SymKeyType, AUTOMATIC, CRYSTUB_40_APPL_DATA) keyPtr
);

/** \brief  Perform the symmetrical key extraction computation tasks.
 **
 ** This function performs the actual symmetrical key extraction computation tasks which have
 ** been requested by the Csm service main functions.
 **/
extern FUNC(void, CRYSTUB_40_CODE) Cry_SymKeyExtractMainFunction
(
  void
);

#define CRYSTUB_40_STOP_SEC_CODE
#include <CryStub_40_MemMap.h>

/*==================[external constants]==========================================================*/

#define CRYSTUB_40_START_SEC_CONST_32
#include <CryStub_40_MemMap.h>

extern CONST(uint32, CRYSTUB_40_CONST) Cry_SymKeyExtractCfg;

#define CRYSTUB_40_STOP_SEC_CONST_32
#include <CryStub_40_MemMap.h>

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #ifndef CRY_SYMKEYEXTRACT_H */

/*==================[end of file]=================================================================*/

