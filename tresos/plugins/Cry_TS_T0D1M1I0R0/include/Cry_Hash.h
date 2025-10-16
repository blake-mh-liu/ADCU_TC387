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

#ifndef CRY_HASH_H
#define CRY_HASH_H

/*==================[includes]====================================================================*/

#include <Csm.h>
#include <CryStub_40_CompilerCfg.h>

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

#define CRYSTUB_40_START_SEC_CODE
#include <CryStub_40_MemMap.h>

/** \brief  Start hash computation.
 **
 ** This function requests the start of an hash computation. This is a stub!
 **/
extern FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_HashStart
(
  P2CONST(void, AUTOMATIC, CRYSTUB_40_APPL_DATA) cfgPtr
);

/** \brief  Update hash computation.
 **
 ** This function requests the update of the hash computation. This is a stub!
 **/
extern FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_HashUpdate
(
  P2CONST(uint8,  AUTOMATIC, CRYSTUB_40_APPL_DATA) dataPtr,
          uint32                                   dataLength
);

/** \brief  Finish hash computation.
 **
 ** This function requests the finishing of the hash computation. This is a stub!
 **/
extern FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_HashFinish
(
  P2VAR(uint8,   AUTOMATIC, CRYSTUB_40_APPL_DATA) resultPtr,
  P2VAR(uint32,  AUTOMATIC, CRYSTUB_40_APPL_DATA) resultLengthPtr,
        boolean                                   TruncationIsAllowed
);

/** \brief  Process hash AlgorithmId computation.
 **
 ** This function process the hash AlgorithmId computation. This is a stub!
 **/
extern FUNC(P2CONST(uint8, AUTOMATIC, CRYSTUB_40_APPL_DATA), CRYSTUB_40_CODE) Cry_HashAlgorithmId
(
  P2CONST(void,   AUTOMATIC, CRYSTUB_40_APPL_DATA) cfgPtr,
    P2VAR(uint32, AUTOMATIC, CRYSTUB_40_APPL_DATA) AlgorithmIdLengthPtr
);

/** \brief  Perform the hash computation tasks.
 **
 ** This function performs the actual hash computation tasks which have been requested by the
 ** Csm service main functions.
 **/
extern FUNC(void, CRYSTUB_40_CODE) Cry_HashMainFunction
(
  void
);

#define CRYSTUB_40_STOP_SEC_CODE
#include <CryStub_40_MemMap.h>

/*==================[external constants]==========================================================*/

#define CRYSTUB_40_START_SEC_CONST_32
#include <CryStub_40_MemMap.h>

extern CONST(uint32, CRYSTUB_40_CONST) Cry_HashCfg;

#define CRYSTUB_40_STOP_SEC_CONST_32
#include <CryStub_40_MemMap.h>

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #ifndef CRY_HASH_H */

/*==================[end of file]=================================================================*/

