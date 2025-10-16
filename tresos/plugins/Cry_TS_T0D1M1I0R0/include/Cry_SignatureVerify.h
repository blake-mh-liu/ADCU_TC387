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

#ifndef CRY_SIGNATUREVERIFY_H
#define CRY_SIGNATUREVERIFY_H

/*==================[includes]====================================================================*/

#include <Csm.h>
#include <CryStub_40_CompilerCfg.h>

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external function declarations]==============================================*/

#define CRYSTUB_40_START_SEC_CODE
#include <CryStub_40_MemMap.h>

/** \brief  Start signature verification computation.
 **
 ** This function requests the start of an signature verification computation. This is a stub!
 **/
extern FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_SignatureVerifyStart
(
  P2CONST(void,                  AUTOMATIC, CRYSTUB_40_APPL_DATA) cfgPtr,
  P2CONST(Csm_AsymPublicKeyType, AUTOMATIC, CRYSTUB_40_APPL_DATA) keyPtr
);

/** \brief  Update signature verification computation.
 **
 ** This function requests the update of the signature verification computation. This is a
 ** stub!
 **/
extern FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_SignatureVerifyUpdate
(
  P2CONST(uint8,  AUTOMATIC, CRYSTUB_40_APPL_DATA) dataPtr,
          uint32                                   dataLength
);

/** \brief  Finish signature verification computation.
 **
 ** This function requests the finishing of the signature verification computation. This is a
 ** stub!
 **/
extern FUNC(Csm_ReturnType, CRYSTUB_40_CODE) Cry_SignatureVerifyFinish
(
  P2CONST(uint8,                AUTOMATIC, CRYSTUB_40_APPL_DATA) signaturePtr,
          uint32                                                 signatureLength,
    P2VAR(Csm_VerifyResultType, AUTOMATIC, CRYSTUB_40_APPL_DATA) resultPtr
);

/** \brief  Perform the signature verification computation tasks.
 **
 ** This function performs the actual signature verification computation tasks which have been
 ** requested by the Csm service main functions.
 **/
extern FUNC(void, CRYSTUB_40_CODE) Cry_SignatureVerifyMainFunction
(
  void
);

#define CRYSTUB_40_STOP_SEC_CODE
#include <CryStub_40_MemMap.h>

/*==================[external constants]==========================================================*/

#define CRYSTUB_40_START_SEC_CONST_32
#include <CryStub_40_MemMap.h>

extern CONST(uint32, CRYSTUB_40_CONST) Cry_SignatureVerifyCfg;

#define CRYSTUB_40_STOP_SEC_CONST_32
#include <CryStub_40_MemMap.h>

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #ifndef CRY_SIGNATUREVERIFY_H */

/*==================[end of file]=================================================================*/

