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

#ifndef CPL_KEYEXCHANGE_H
#define CPL_KEYEXCHANGE_H

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

CONST(uint32, EBSTUBS_CONST) Cpl_KeyExchangeCfg = 0U;

#define EBSTUBS_STOP_SEC_CONST_32
#include <MemMap.h>

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/
#define EBSTUBS_START_SEC_CODE
#include <MemMap.h>


FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_KeyExchange
(
  P2CONST(void,                       AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  P2CONST(Cal_KeyExchangeBaseType,    AUTOMATIC, EBSTUBS_APPL_DATA) basePtr,
  P2CONST(Cal_KeyExchangePrivateType, AUTOMATIC, EBSTUBS_APPL_DATA) privateValuePtr,
  P2VAR(uint8,                        AUTOMATIC, EBSTUBS_APPL_DATA) publicValuePtr,
  P2VAR(uint32,                       AUTOMATIC, EBSTUBS_APPL_DATA) publicValueLengthPtr
);

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_KeyExchangeStart
(
  P2CONST(void,                       AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_KeyExchangeCalcSecretCtxBufType                               contextBuffer,
  P2CONST(Cal_KeyExchangeBaseType,    AUTOMATIC, EBSTUBS_APPL_DATA) basePtr,
  P2CONST(Cal_KeyExchangePrivateType, AUTOMATIC, EBSTUBS_APPL_DATA) privateValuePtr
);

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_KeyExchangeUpdate
(
  P2CONST(void,  AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_KeyExchangeCalcSecretCtxBufType          contextBuffer,
  P2CONST(uint8, AUTOMATIC, EBSTUBS_APPL_DATA) partnerPublicValuePtr,
  uint32                                       partnerPublicValueLength
);

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_KeyExchangeFinish
(
  P2CONST(void, AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_KeyExchangeCalcSecretCtxBufType         contextBuffer,
  P2VAR(uint8,  AUTOMATIC, EBSTUBS_APPL_DATA) sharedSecretPtr,
  P2VAR(uint32, AUTOMATIC, EBSTUBS_APPL_DATA) sharedSecretLengthPtr,
  boolean                                     TruncationIsAllowed
);



#define EBSTUBS_STOP_SEC_CODE
#include <MemMap.h>


/*==================[internal function definitions]=========================*/

#endif /* if !defined( CPL_KEYEXCHANGE_H ) */
/*==================[end of file]===========================================*/
