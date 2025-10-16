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

/*==================[inclusions]=============================================*/

#include <Std_Types.h>

#include <Cal_Types.h>

#include <Cpl_SignatureVerify.h>
#include <Cpl_AsymPublicKeyExtract.h>
#include <Cpl_KeyExchange.h>
#include <Cpl_KeyDerive.h>
#include <Cpl_Hash.h>
#include <Cpl_MacVerify.h>
#include <Cpl_MacGenerate.h>
#include <Cpl_Random.h>
#include <Cpl_SymDecrypt.h>
#include <Cpl_SymBlockDecrypt.h>
#include <Cpl_SymBlockEncrypt.h>
#include <Cpl_SymKeyExtract.h>

#include <TsAutosar.h>
/*==================[macros]=================================================*/

#if !defined(CPLSTUB_PARAM_UNUSED)
#define CPLSTUB_PARAM_UNUSED(x) ((void) (x))
#endif

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/
#define EBSTUBS_START_SEC_CODE
#include <MemMap.h>

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_SymKeyExtractStart
(
  P2CONST(void,           AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_SymKeyExtractCtxBufType                           contextBuffer
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_SymKeyExtractUpdate
(
  P2CONST(void,  AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_SymKeyExtractCtxBufType                  contextBuffer,
  P2CONST(uint8, AUTOMATIC, EBSTUBS_APPL_DATA) dataPtr,
  uint32                                       dataLength
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(dataPtr);
  CPLSTUB_PARAM_UNUSED(dataLength);
  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_SymKeyExtractFinish
(
  P2CONST(void,         AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_SymKeyExtractCtxBufType                         contextBuffer,
  P2VAR(Cal_SymKeyType, AUTOMATIC, EBSTUBS_APPL_DATA) resultPtr
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(resultPtr);
  return CAL_E_OK;
}


FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_SymBlockEncryptStart
(
  P2CONST(void,           AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_SymBlockEncryptCtxBufType                         contextBuffer,
  P2CONST(Cal_SymKeyType, AUTOMATIC, EBSTUBS_APPL_DATA) key
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(key);
  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_SymBlockEncryptUpdate
(
  P2CONST(void,  AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_SymBlockEncryptCtxBufType                contextBuffer,
  P2CONST(uint8, AUTOMATIC, EBSTUBS_APPL_DATA) dataPtr,
  uint32                                       dataLength,
  P2VAR(uint8,   AUTOMATIC, EBSTUBS_APPL_DATA) resultPtr,
  P2VAR(uint32,  AUTOMATIC, EBSTUBS_APPL_DATA) resultLengthPtr
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(dataPtr);
  CPLSTUB_PARAM_UNUSED(dataLength);
  CPLSTUB_PARAM_UNUSED(resultPtr);
  CPLSTUB_PARAM_UNUSED(resultLengthPtr);
  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_SymBlockEncryptFinish
(
  P2CONST(void, AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_SymBlockEncryptCtxBufType               contextBuffer
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_SymBlockDecryptStart
(
  P2CONST(void,           AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_SymBlockDecryptCtxBufType                         contextBuffer,
  P2CONST(Cal_SymKeyType, AUTOMATIC, EBSTUBS_APPL_DATA) key
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(key);
  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_SymBlockDecryptUpdate
(
  P2CONST(void,  AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_SymBlockDecryptCtxBufType                contextBuffer,
  P2CONST(uint8, AUTOMATIC, EBSTUBS_APPL_DATA) dataPtr,
  uint32                                       dataLength,
  P2VAR(uint8,   AUTOMATIC, EBSTUBS_APPL_DATA) resultPtr,
  P2VAR(uint32,  AUTOMATIC, EBSTUBS_APPL_DATA) resultLengthPtr
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(dataPtr);
  CPLSTUB_PARAM_UNUSED(dataLength);
  CPLSTUB_PARAM_UNUSED(resultPtr);
  CPLSTUB_PARAM_UNUSED(resultLengthPtr);
  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_SymBlockDecryptFinish
(
  P2CONST(void, AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_SymBlockDecryptCtxBufType               contextBuffer
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_SymDecryptStart
(
  P2CONST(void,           AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_SymDecryptCtxBufType                              contextBuffer,
  P2CONST(Cal_SymKeyType, AUTOMATIC, EBSTUBS_APPL_DATA) key,
  P2CONST(uint8,          AUTOMATIC, EBSTUBS_APPL_DATA) data,
  uint32                                                length
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(key);
  CPLSTUB_PARAM_UNUSED(data);
  CPLSTUB_PARAM_UNUSED(length);
  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_SymDecryptUpdate
(
  P2CONST(void,  AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_SymDecryptCtxBufType                     contextBuffer,
  P2CONST(uint8, AUTOMATIC, EBSTUBS_APPL_DATA) dataPtr,
  uint32                                       dataLength,
  P2VAR(uint8,   AUTOMATIC, EBSTUBS_APPL_DATA) resultPtr,
  P2VAR(uint32,  AUTOMATIC, EBSTUBS_APPL_DATA) resultLengthPtr
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(dataPtr);
  CPLSTUB_PARAM_UNUSED(dataLength);
  CPLSTUB_PARAM_UNUSED(resultPtr);
  CPLSTUB_PARAM_UNUSED(resultLengthPtr);
  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_SymDecryptFinish
(
  P2CONST(void, AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_SymDecryptCtxBufType                    contextBuffer,
  P2VAR(uint8,  AUTOMATIC, EBSTUBS_APPL_DATA) resultPtr,
  P2VAR(uint32, AUTOMATIC, EBSTUBS_APPL_DATA) resultLengthPtr
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(resultPtr);
  CPLSTUB_PARAM_UNUSED(resultLengthPtr);
  return CAL_E_OK;
}


FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_RandomStart
(
  P2CONST(void, AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_RandomCtxBufType                        contextBuffer
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_RandomUpdate
(
  P2CONST(void,  AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_RandomCtxBufType                         contextBuffer,
  P2CONST(uint8, AUTOMATIC, EBSTUBS_APPL_DATA) dataPtr,
  uint32                                       dataLength
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(dataPtr);
  CPLSTUB_PARAM_UNUSED(dataLength);
  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_RandomFinish
(
  P2CONST(void, AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_RandomCtxBufType                        contextBuffer
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);

  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_Random
(
  P2CONST(void, AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_RandomCtxBufType                        contextBuffer,
  P2VAR(uint8,  AUTOMATIC, EBSTUBS_APPL_DATA) resultPtr,
  uint32                                      resultLength
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);

  CPLSTUB_PARAM_UNUSED(resultPtr);
  CPLSTUB_PARAM_UNUSED(resultLength);
  return CAL_E_OK;
}


FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_MacVerifyStart
(
  P2CONST(void,           AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_MacVerifyCtxBufType                               contextBuffer,
  P2CONST(Cal_SymKeyType, AUTOMATIC, EBSTUBS_APPL_DATA) key
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(key);
  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_MacVerifyUpdate
(
  P2CONST(void, AUTOMATIC, EBSTUBS_APPL_DATA)  cfgPtr,
  Cal_MacVerifyCtxBufType                      contextBuffer,
  P2CONST(uint8, AUTOMATIC, EBSTUBS_APPL_DATA) dataPtr,
  uint32                                       dataLength
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(dataPtr);
  CPLSTUB_PARAM_UNUSED(dataLength);
  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_MacVerifyFinish
(
  P2CONST(void,               AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_MacVerifyCtxBufType                                   contextBuffer,
  P2CONST(uint8,              AUTOMATIC, EBSTUBS_APPL_DATA) resultPtr,
  uint32                                                    resultLength,
  P2VAR(Cal_VerifyResultType, AUTOMATIC, EBSTUBS_APPL_DATA) verifyResult
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(resultPtr);
  CPLSTUB_PARAM_UNUSED(resultLength);
  CPLSTUB_PARAM_UNUSED(verifyResult);
  return CAL_E_OK;
}


FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_MacGenerateStart
(
  P2CONST(void,           AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_MacGenerateCtxBufType                             contextBuffer,
  P2CONST(Cal_SymKeyType, AUTOMATIC, EBSTUBS_APPL_DATA) key
)
{
  CPLSTUB_PARAM_UNUSED(key);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_MacGenerateUpdate
(
  P2CONST(void, AUTOMATIC, EBSTUBS_APPL_DATA)  cfgPtr,
  Cal_MacGenerateCtxBufType                    contextBuffer,
  P2CONST(uint8, AUTOMATIC, EBSTUBS_APPL_DATA) dataPtr,
  uint32                                       dataLength
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(dataPtr);
  CPLSTUB_PARAM_UNUSED(dataLength);
  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_MacGenerateFinish
(
  P2CONST(void, AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_MacGenerateCtxBufType                   contextBuffer,
  P2VAR(uint8,  AUTOMATIC, EBSTUBS_APPL_DATA) resultPtr,
  P2VAR(uint32, AUTOMATIC, EBSTUBS_APPL_DATA) resultLengthPtr,
  boolean                                     TruncationAllowed
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(resultPtr);
  CPLSTUB_PARAM_UNUSED(resultLengthPtr);
  CPLSTUB_PARAM_UNUSED(TruncationAllowed);
  return CAL_E_OK;
}


FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_HashStart
(
  P2CONST(void, AUTOMATIC, EBSTUBS_APPL_DATA)  cfgPtr,
  Cal_HashCtxBufType                           contextBuffer
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  return CAL_E_OK;
}


FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_HashUpdate
(
  P2CONST(void, AUTOMATIC, EBSTUBS_APPL_DATA)  cfgPtr,
  Cal_HashCtxBufType                           contextBuffer,
  P2CONST(uint8, AUTOMATIC, EBSTUBS_APPL_DATA) dataPtr,
  uint32                                       dataLength
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(dataPtr);
  CPLSTUB_PARAM_UNUSED(dataLength);
  return CAL_E_OK;
}


FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_HashFinish
(
  P2CONST(void, AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_HashCtxBufType                          contextBuffer,
  P2VAR(uint8,  AUTOMATIC, EBSTUBS_APPL_DATA) resultPtr,
  P2VAR(uint32, AUTOMATIC, EBSTUBS_APPL_DATA) resultLengthPtr,
  boolean                                     TruncationAllowed
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(resultPtr);
  CPLSTUB_PARAM_UNUSED(resultLengthPtr);
  CPLSTUB_PARAM_UNUSED(TruncationAllowed);
  return CAL_E_OK;
}



FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_SignatureVerifyStart
(
  P2CONST(void, AUTOMATIC, EBSTUBS_APPL_DATA)                  cfgPtr,
  Cal_SignatureVerifyCtxBufType                                contextBuffer,
  P2CONST(Cal_AsymPublicKeyType, AUTOMATIC, EBSTUBS_APPL_DATA) keyPtr
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(keyPtr);
  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_SignatureVerifyUpdate
(
  P2CONST(void, AUTOMATIC, EBSTUBS_APPL_DATA)  cfgPtr,
  Cal_SignatureVerifyCtxBufType                contextBuffer,
  P2CONST(uint8, AUTOMATIC, EBSTUBS_APPL_DATA) dataPtr,
  uint32                                       dataLength
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(dataPtr);
  CPLSTUB_PARAM_UNUSED(dataLength);
  return CAL_E_OK;
}


FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_SignatureVerifyFinish
(
  P2CONST(void,               AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_SignatureVerifyCtxBufType                             contextBuffer,
  P2CONST(uint8,              AUTOMATIC, EBSTUBS_APPL_DATA) resultPtr,
  uint32                                                    resultLength,
  P2VAR(Cal_VerifyResultType, AUTOMATIC, EBSTUBS_APPL_DATA) verifyResultPtr
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(resultPtr);
  CPLSTUB_PARAM_UNUSED(resultLength);
  CPLSTUB_PARAM_UNUSED(verifyResultPtr);
  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_AsymPublicKeyExtractStart
(
  P2CONST(void, AUTOMATIC, EBSTUBS_APPL_DATA)              cfgPtr,
  Cal_AsymPublicKeyExtractCtxBufType                       contextBuffer
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_AsymPublicKeyExtractUpdate
(
  P2CONST(void, AUTOMATIC, EBSTUBS_APPL_DATA)  cfgPtr,
  Cal_AsymPublicKeyExtractCtxBufType           contextBuffer,
  P2CONST(uint8, AUTOMATIC, EBSTUBS_APPL_DATA) dataPtr,
  uint32                                       dataLength
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(dataPtr);
  CPLSTUB_PARAM_UNUSED(dataLength);
  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_AsymPublicKeyExtractFinish
(
  P2CONST(void,               AUTOMATIC, EBSTUBS_APPL_DATA)  cfgPtr,
  Cal_AsymPublicKeyExtractCtxBufType                         contextBuffer,
  P2VAR(Cal_AsymPublicKeyType, AUTOMATIC, EBSTUBS_APPL_DATA) resultPtr
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(resultPtr);
  return CAL_E_OK;
}


FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_KeyExchange
(
  P2CONST(void,                       AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  P2CONST(Cal_KeyExchangeBaseType,    AUTOMATIC, EBSTUBS_APPL_DATA) basePtr,
  P2CONST(Cal_KeyExchangePrivateType, AUTOMATIC, EBSTUBS_APPL_DATA) privateValuePtr,
  P2VAR(uint8,                        AUTOMATIC, EBSTUBS_APPL_DATA) publicValuePtr,
  P2VAR(uint32,                       AUTOMATIC, EBSTUBS_APPL_DATA) publicValueLengthPtr
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(basePtr);
  CPLSTUB_PARAM_UNUSED(privateValuePtr);
  CPLSTUB_PARAM_UNUSED(publicValuePtr);
  CPLSTUB_PARAM_UNUSED(publicValueLengthPtr);
  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_KeyExchangeStart
(
  P2CONST(void,                       AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_KeyExchangeCalcSecretCtxBufType                               contextBuffer,
  P2CONST(Cal_KeyExchangeBaseType,    AUTOMATIC, EBSTUBS_APPL_DATA) basePtr,
  P2CONST(Cal_KeyExchangePrivateType, AUTOMATIC, EBSTUBS_APPL_DATA) privateValuePtr
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(basePtr);
  CPLSTUB_PARAM_UNUSED(privateValuePtr);
  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_KeyExchangeUpdate
(
  P2CONST(void, AUTOMATIC, EBSTUBS_APPL_DATA)  cfgPtr,
  Cal_KeyExchangeCalcSecretCtxBufType          contextBuffer,
  P2CONST(uint8, AUTOMATIC, EBSTUBS_APPL_DATA) partnerPublicValuePtr,
  uint32                                       partnerPublicValueLength
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(partnerPublicValuePtr);
  CPLSTUB_PARAM_UNUSED(partnerPublicValueLength);
  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_KeyExchangeFinish
(
  P2CONST(void, AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_KeyExchangeCalcSecretCtxBufType         contextBuffer,
  P2VAR(uint8,  AUTOMATIC, EBSTUBS_APPL_DATA) sharedSecretPtr,
  P2VAR(uint32, AUTOMATIC, EBSTUBS_APPL_DATA) sharedSecretLengthPtr,
  boolean                                     TruncationIsAllowed
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(sharedSecretPtr);
  CPLSTUB_PARAM_UNUSED(sharedSecretLengthPtr);
  CPLSTUB_PARAM_UNUSED(TruncationIsAllowed);
  return CAL_E_OK;
}


FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_KeyDeriveStart
(
  P2CONST(void, AUTOMATIC, EBSTUBS_APPL_DATA) cfgPtr,
  Cal_KeyDeriveCtxBufType                     contextBuffer,
  uint32                                      keyLength,
  uint32                                      interations
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(keyLength);
  CPLSTUB_PARAM_UNUSED(interations);
  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_KeyDeriveUpdate
(
  P2CONST(void, AUTOMATIC, EBSTUBS_APPL_DATA)  cfgPtr,
  Cal_KeyDeriveCtxBufType                      contextBuffer,
  P2CONST(uint8, AUTOMATIC, EBSTUBS_APPL_DATA) passwordPtr,
  uint32                                       passwordLength,
  P2CONST(uint8, AUTOMATIC, EBSTUBS_APPL_DATA) saltPtr,
  uint32                                       saltLength
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(passwordPtr);
  CPLSTUB_PARAM_UNUSED(passwordLength);
  CPLSTUB_PARAM_UNUSED(saltPtr);
  CPLSTUB_PARAM_UNUSED(saltLength);
  return CAL_E_OK;
}

FUNC(Cal_ReturnType, EBSTUBS_CODE) Cpl_KeyDeriveFinish
(
  P2CONST(void, AUTOMATIC, EBSTUBS_APPL_DATA)         cfgPtr,
  Cal_KeyDeriveCtxBufType                             contextBuffer,
  P2VAR(Cal_SymKeyType, AUTOMATIC, EBSTUBS_APPL_DATA) keyPtr
)
{
  CPLSTUB_PARAM_UNUSED(cfgPtr);
  CPLSTUB_PARAM_UNUSED(contextBuffer);
  CPLSTUB_PARAM_UNUSED(keyPtr);

  return CAL_E_OK;
}

#define EBSTUBS_STOP_SEC_CODE
#include <MemMap.h>


/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
