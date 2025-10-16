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

#ifndef CRY_CHECKSUM_H
#define CRY_CHECKSUM_H

/*==================[includes]====================================================================*/

#include <Csm.h>
#include <CryStub_40_CompilerCfg.h>

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

#define CRYSTUB_40_START_SEC_CODE
#include <CryStub_40_MemMap.h>

/** \brief  Start checksum computation.
 **
 ** This function requests the start of an checksum computation. This is a stub!
 **/
extern FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_ChecksumStart
(
  P2CONST(void, AUTOMATIC, CRYSTUB_40_APPL_DATA) cfgPtr
);

/** \brief  Update checksum computation.
 **
 ** This function requests the update of the checksum computation. This is a stub!
 **/
extern FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_ChecksumUpdate
(
  P2CONST(uint8,  AUTOMATIC, CRYSTUB_40_APPL_DATA) dataPtr,
          uint32                                   dataLength
);

/** \brief  Finish checksum computation.
 **
 ** This function requests the finishing of the checksum computation. This is a stub!
 **/
extern FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_ChecksumFinish
(
  P2VAR(uint8,   AUTOMATIC, CRYSTUB_40_APPL_DATA) resultPtr,
  P2VAR(uint32,  AUTOMATIC, CRYSTUB_40_APPL_DATA) resultLengthPtr,
        boolean                                   TruncationIsAllowed
);

/** \brief  Perform the checksum computation tasks.
 **
 ** This function performs the actual checksum computation tasks which have been requested by
 ** the Csm service main functions.
 **/
extern FUNC(void, CRYSTUB_40_CODE) Cry_ChecksumMainFunction
(
  void
);

#define CRYSTUB_40_STOP_SEC_CODE
#include <CryStub_40_MemMap.h>

/*==================[external constants]==========================================================*/

#define CRYSTUB_40_START_SEC_CONST_32
#include <CryStub_40_MemMap.h>

extern CONST(uint32, CRYSTUB_40_CONST) Cry_ChecksumCfg;

#define CRYSTUB_40_STOP_SEC_CONST_32
#include <CryStub_40_MemMap.h>

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #ifndef CRY_CHECKSUM_H */

/*==================[end of file]=================================================================*/

