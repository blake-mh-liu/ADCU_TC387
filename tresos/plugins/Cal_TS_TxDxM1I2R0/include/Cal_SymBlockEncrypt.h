/**
 * \file
 *
 * \brief AUTOSAR Cal
 *
 * This file contains the implementation of the AUTOSAR
 * module Cal.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef CAL_SYMBLOCKENCRYPT_H
#define CAL_SYMBLOCKENCRYPT_H


/*==================[includes]====================================================================*/


#include <Cal_Types.h>
#include <Cal_SymBlockEncrypt_Cfg.h>

#if (CAL_SYMBLOCKENCRYPT_ENABLED == TRUE)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/


/* !LINKSTO CAL0730, 1
 */
/* !LINKSTO CAL0742, 1
 */
/** \brief Context buffer for the symmetrical block encryption service.
 */
typedef Cal_AlignType Cal_SymBlockEncryptCtxBufType[CAL_SYMBLOCKENCRYPT_CTX_BUF_SIZE];



/* !LINKSTO CAL0025, 1
 */
/* !LINKSTO CAL0074, 1
 */
/**
 * \struct Cal_SymBlockEncryptConfigType
 * \brief Structure representing the configuration of the symmetrical block encryption
 *         algorithm.
 *//**
 * \var Cal_SymBlockEncryptConfigType::ConfigId
 * \brief Identifier for the current configuration.
 *//**
 * \var Cal_SymBlockEncryptConfigType::PrimitiveStartFct
 * \brief Pointer to the start function of the underlying Cpl primitive.
 *//**
 * \var Cal_SymBlockEncryptConfigType::PrimitiveUpdateFct
 * \brief Pointer to the update function of the underlying Cpl primitive.
 *//**
 * \var Cal_SymBlockEncryptConfigType::PrimitiveFinishFct
 * \brief Pointer to the finish function of the underlying Cpl primitive.
 *//**
 * \var Cal_SymBlockEncryptConfigType::PrimitiveConfigPtr
 * \brief Pointer to a Cpl configuration.
 */
typedef struct
{
  Cal_ConfigIdType ConfigId;

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveStartFct)
  (
    P2CONST(void,                      AUTOMATIC, CAL_APPL_DATA) cfgId,
    VAR(Cal_SymBlockEncryptCtxBufType, AUTOMATIC               ) contextBuffer,
    P2CONST(Cal_SymKeyType,            AUTOMATIC, CAL_APPL_DATA) keyPtr
  );

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveUpdateFct)
  (
    P2CONST(void,                      AUTOMATIC, CAL_APPL_DATA) cfgId,
    VAR(Cal_SymBlockEncryptCtxBufType, AUTOMATIC               ) contextBuffer,
    P2CONST(uint8,                     AUTOMATIC, CAL_APPL_DATA) iputTextPtr,
    VAR(uint32,                        AUTOMATIC               ) iputTextLength,
    P2VAR(uint8,                       AUTOMATIC, CAL_APPL_DATA) oputTextPtr,
    P2VAR(uint32,                      AUTOMATIC, CAL_APPL_DATA)  oputTextLengthPtr
  );

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveFinishFct)
  (
    P2CONST(void,                      AUTOMATIC, CAL_APPL_DATA) cfgId,
    VAR(Cal_SymBlockEncryptCtxBufType, AUTOMATIC               ) contextBuffer
  );

  P2CONST(void, TYPEDEF, CAL_CONST) PrimitiveConfigPtr;
}
Cal_SymBlockEncryptConfigType;


/*==================[external function declarations]==============================================*/

#define CAL_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO CAL0168, 1
 */
/** \brief  Start symmetrical block encryption computation.
 **
 ** This function requests the start of the symmetrical block encryption for
 ** the given configuration. The start function of the configured primitive
 ** is called and its return value is returned.
 **
 ** \param[in]   cfgId          An identification of the configuration for which
 **                             the start of the symmetrical block encryption
 **                             computation should be requested.
 ** \param[in]   keyPtr         A pointer to the key which should be used in the
 **                             symmetrical block encryption computation.
 ** \param[out]  contextBuffer  Holds the pointer to the buffer in which the context of this service
 **                             can be stored.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK      If the start was successfully requested.
 ** \retval   CAL_E_NOT_OK  Otherwise.
 **/
FUNC(Cal_ReturnType, CAL_CODE) Cal_SymBlockEncryptStart
(
  VAR(Cal_ConfigIdType,              AUTOMATIC               ) cfgId,
  VAR(Cal_SymBlockEncryptCtxBufType, AUTOMATIC               ) contextBuffer,
  P2CONST(Cal_SymKeyType,            AUTOMATIC, CAL_APPL_DATA) keyPtr
);

/* !LINKSTO CAL0173, 1
 */
/** \brief  Update symmetrical block encryption computation.
 **
 ** This function requests the update of the symmetrical block encryption
 ** computation for the given data. The update function of the configured
 ** primitive is called and its return value is returned.
 **
 ** \param[in]   cfgId                   An identification of the configuration for which
 **                                      the update of the symmetrical block encryption
 **                                      computation should be requested.
 ** \param[in]      plainTextPtr         A pointer to the start of an array
 **                                      which contains the constant plain
 **                                      text that shall be encrypted.
 ** \param[in]      plainTextLength      Length of the constant plain text
 **                                      in bytes.
 ** \param[out]     cipherTextPtr        A pointer to the start of an array
 **                                      where the encrypted text will be
 **                                      stored.
 ** \param[in,out]  contextBuffer        Holds the pointer to the buffer in which the context of
 **                                      this service is stored.
 ** \param[in,out]  cipherTextLengthPtr  Holds a pointer to a memory location
 **                                      in which the length information is stored.
 **                                      On calling this function this parameter
 **                                      shall contain the size of the buffer
 **                                      provided by cipherTextPtr. When the
 **                                      request has finished, the amount of
 **                                      data that has been encrypted shall be
 **                                      stored.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK      If the update was successfully requested.
 ** \retval   CAL_E_NOT_OK  If no symmetrical block encryption computation
 **                         has been started via Cal_SymBlockEncryptStart(),
 **                         yet.
 **/
FUNC(Cal_ReturnType, CAL_CODE) Cal_SymBlockEncryptUpdate
(
  VAR(Cal_ConfigIdType,              AUTOMATIC               ) cfgId,
  VAR(Cal_SymBlockEncryptCtxBufType, AUTOMATIC               ) contextBuffer,
  P2CONST(uint8,                     AUTOMATIC, CAL_APPL_DATA) plainTextPtr,
  VAR(uint32,                        AUTOMATIC               ) plainTextLength,
  P2VAR(uint8,                       AUTOMATIC, CAL_APPL_DATA) cipherTextPtr,
  P2VAR(uint32,                      AUTOMATIC, CAL_APPL_DATA) cipherTextLengthPtr
);

/* !LINKSTO CAL0180, 1
 */
/** \brief  Finish symmetrical block encryption computation.
 **
 ** This function requests the finishing of the symmetrical block encryption
 ** computation and the storing of the encrypted text in the given buffer.
 ** The finish function of the configured primitive is called and its return
 ** value is returned.
 **
 ** \param[in]   cfgId                   An identification of the configuration for which
 **                                      the finishing of the symmetrical block encryption
 **                                      computation should be requested.
 ** \param[in,out]  cipherTextLengthPtr  Holds a pointer to a memory location
 **                                      in which the length information is stored.
 **                                      On calling this function this parameter
 **                                      shall contain the size of the buffer
 **                                      provided by cipherTextPtr. When the
 **                                      request has finished, the amount of
 **                                      data that has been encrypted shall be
 **                                      stored.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK      If the finish was successfully requested.
 ** \retval   CAL_E_NOT_OK  If no symmetrical block encryption computation
 **                         has been started via Cal_SymBlockEncryptStart(),
 **                         yet.
 **/
FUNC(Cal_ReturnType, CAL_CODE) Cal_SymBlockEncryptFinish
(
  VAR(Cal_ConfigIdType,              AUTOMATIC               ) cfgId,
  VAR(Cal_SymBlockEncryptCtxBufType, AUTOMATIC               ) contextBuffer
);



#define CAL_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]==========================================================*/


#define CAL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief Array containg all existing configurations of the symmetrical block encryption service.
 */
extern CONST(Cal_SymBlockEncryptConfigType, CAL_CONST)
  Cal_SymBlockEncConfigurations[CAL_SYMBLOCKENCRYPT_CONFIG_COUNT];

#define CAL_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CAL_SYMBLOCKENCRYPT_ENABLED == TRUE) */

#endif /* #ifndef CAL_SYMBLOCKENCRYPT_H */

