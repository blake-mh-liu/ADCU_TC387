/**
 * \file
 *
 * \brief AUTOSAR Cpl
 *
 * This file contains the implementation of the AUTOSAR
 * module Cpl.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef CPL_MACVERIFY_H
#define CPL_MACVERIFY_H

/*==================[inclusions]=============================================*/

#include <Std_Types.h>

#include <Cal.h>
#include <Cal_Types.h>

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]====================================*/

#define EBSTUBS_START_SEC_CONST_32
#include <MemMap.h>

CONST(uint32, EBSTUBS_CONST) Cpl_MacVerifyCfg = 0U;

#define EBSTUBS_STOP_SEC_CONST_32
#include <MemMap.h>

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/
#define EBSTUBS_START_SEC_CODE
#include <MemMap.h>

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_MacVerifyStart
(
  P2CONST(void,           AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_MacVerifyCtxBufType                               contextBuffer,
  P2CONST(Cal_SymKeyType, AUTOMATIC, EBSTUBS_APPL_DATA) key
);

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_MacVerifyUpdate
(
  P2CONST(void,  AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_MacVerifyCtxBufType                      contextBuffer,
  P2CONST(uint8, AUTOMATIC, EBSTUBS_APPL_DATA) dataPtr,
  uint32                                       dataLength
);

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_MacVerifyFinish
(
  P2CONST(void,               AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_MacVerifyCtxBufType                                   contextBuffer,
  P2CONST(uint8,              AUTOMATIC, EBSTUBS_APPL_DATA) resultPtr,
  uint32                                                    resultLength,
  P2VAR(Cal_VerifyResultType, AUTOMATIC, EBSTUBS_APPL_DATA) verifyResult
);


#define EBSTUBS_STOP_SEC_CODE
#include <MemMap.h>


/*==================[internal function definitions]=========================*/

#endif /* if !defined( CPL_MACVERIFY_H ) */
/*==================[end of file]===========================================*/
