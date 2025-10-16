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

#ifndef CRY_SYMBLOCKENCRYPT_H
#define CRY_SYMBLOCKENCRYPT_H

/*==================[includes]====================================================================*/

#include <Csm.h>
#include <CryStub_40_CompilerCfg.h>

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

#define CRYSTUB_40_START_SEC_CODE
#include <CryStub_40_MemMap.h>

/** \brief  Start symmetrical block encryption computation.
 **
 ** This function requests the start of an symmetrical block encryption computation. This is a
 ** stub!
 **/
extern FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_SymBlockEncryptStart
(
  P2CONST(void,           AUTOMATIC, CRYSTUB_40_APPL_DATA) cfgPtr,
  P2CONST(Csm_SymKeyType, AUTOMATIC, CRYSTUB_40_APPL_DATA) keyPtr
);

/** \brief  Update symmetrical block encryption computation.
 **
 ** This function requests the update of the symmetrical block encryption computation. This is
 ** a stub!
 **/
extern FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_SymBlockEncryptUpdate
(
  P2CONST(uint8,  AUTOMATIC, CRYSTUB_40_APPL_DATA) plainTextPtr,
          uint32                                   plainTextLength,
    P2VAR(uint8,  AUTOMATIC, CRYSTUB_40_APPL_DATA) cipherTextPtr,
    P2VAR(uint32, AUTOMATIC, CRYSTUB_40_APPL_DATA) cipherTextLengthPtr
);

/** \brief  Finish symmetrical block encryption computation.
 **
 ** This function requests the finishing of the symmetrical block encryption computation. This
 ** is a stub!
 **/
extern FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_SymBlockEncryptFinish
(
  void
);

/** \brief  Perform the symmetrical block encryption computation tasks.
 **
 ** This function performs the actual symmetrical block encryption computation tasks which have
 ** been requested by the Csm service main functions.
 **/
extern FUNC(void, CRYSTUB_40_CODE) Cry_SymBlockEncryptMainFunction
(
  void
);

#define CRYSTUB_40_STOP_SEC_CODE
#include <CryStub_40_MemMap.h>

/*==================[external constants]==========================================================*/

#define CRYSTUB_40_START_SEC_CONST_32
#include <CryStub_40_MemMap.h>

extern CONST(uint32, CRYSTUB_40_CONST) Cry_SymBlockEncryptCfg;

#define CRYSTUB_40_STOP_SEC_CONST_32
#include <CryStub_40_MemMap.h>

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #ifndef CRY_SYMBLOCKENCRYPT_H */

/*==================[end of file]=================================================================*/

