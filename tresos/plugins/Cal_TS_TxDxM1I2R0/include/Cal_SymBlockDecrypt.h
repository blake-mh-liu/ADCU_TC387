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

#ifndef CAL_SYMBLOCKDECRYPT_H
#define CAL_SYMBLOCKDECRYPT_H


/*==================[includes]====================================================================*/


#include <Cal_Types.h>
#include <Cal_SymBlockDecrypt_Cfg.h>

#if (CAL_SYMBLOCKDECRYPT_ENABLED == TRUE)


/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/


/* !LINKSTO CAL0730, 1
 */
/* !LINKSTO CAL0742, 1
 */
/** \brief Context buffer for the symmetrical block decryption service.
 */
typedef Cal_AlignType Cal_SymBlockDecryptCtxBufType[CAL_SYMBLOCKDECRYPT_CTX_BUF_SIZE];



/* !LINKSTO CAL0025, 1
 */
/* !LINKSTO CAL0074, 1
 */
/**
 * \struct Cal_SymBlockDecryptConfigType
 * \brief Structure representing the configuration of the symmetrical block decryption
 *         algorithm.
 *//**
 * \var Cal_SymBlockDecryptConfigType::ConfigId
 * \brief Identifier for the current configuration.
 *//**
 * \var Cal_SymBlockDecryptConfigType::PrimitiveStartFct
 * \brief Pointer to the start function of the underlying Cpl primitive.
 *//**
 * \var Cal_SymBlockDecryptConfigType::PrimitiveUpdateFct
 * \brief Pointer to the update function of the underlying Cpl primitive.
 *//**
 * \var Cal_SymBlockDecryptConfigType::PrimitiveFinishFct
 * \brief Pointer to the finish function of the underlying Cpl primitive.
 *//**
 * \var Cal_SymBlockDecryptConfigType::PrimitiveConfigPtr
 * \brief Pointer to a Cpl configuration.
 */
typedef struct
{
  Cal_ConfigIdType ConfigId;

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveStartFct)
  (
    P2CONST(void,                      AUTOMATIC, CAL_APPL_DATA) cfgId,
    Cal_SymBlockDecryptCtxBufType                                contextBuffer,
    P2CONST(Cal_SymKeyType,            AUTOMATIC, CAL_APPL_DATA) keyPtr
  );

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveUpdateFct)
  (
    P2CONST(void,                      AUTOMATIC, CAL_APPL_DATA) cfgId,
    Cal_SymBlockDecryptCtxBufType                                contextBuffer,
    P2CONST(uint8,                     AUTOMATIC, CAL_APPL_DATA) cipherTextPtr,
    uint32                                                       cipherTextLength,
    P2VAR(uint8,                       AUTOMATIC, CAL_APPL_DATA) plainTextPtr,
    P2VAR(uint32,                      AUTOMATIC, CAL_APPL_DATA) plainTextLengthPtr
  );

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveFinishFct)
  (
    P2CONST(void,                      AUTOMATIC, CAL_APPL_DATA) cfgId,
    Cal_SymBlockDecryptCtxBufType                                contextBuffer
  );

  P2CONST(void, TYPEDEF, CAL_CONST) PrimitiveConfigPtr;
}
Cal_SymBlockDecryptConfigType;

/*==================[external function declarations]==============================================*/

#define CAL_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO CAL0187, 1
 */
/** \brief  Start symmetrical block decryption computation.
 **
 ** This function requests the start of the symmetrical block decryption for
 ** the given configuration. The start function of the configured primitive
 ** is called and its return value is returned.
 **
 ** \param[in]  cfgId          An identification of the configuration for which
 **                            the start of the symmetrical block decryption
 **                            computation should be requested.
 ** \param[in]  keyPtr         A pointer to the key which should be used in the
 **                            symmetrical block decryption computation.
 ** \param[out] contextBuffer  Holds the pointer to the buffer in which the context of this service
 **                            can be stored.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK      If the start was successfully requested.
 ** \retval   CAL_E_NOT_OK  Otherwise.
 **/
FUNC(Cal_ReturnType, CAL_CODE) Cal_SymBlockDecryptStart
(
  Cal_ConfigIdType                                  cfgId,
  Cal_SymBlockDecryptCtxBufType                     contextBuffer,
  P2CONST(Cal_SymKeyType, AUTOMATIC, CAL_APPL_DATA) keyPtr
);

/* !LINKSTO CAL0192, 1
 */
/** \brief  Update symmetrical block decryption computation.
 **
 ** This function requests the update of the symmetrical block decryption
 ** computation for the given data. The update function of the configured
 ** primitive is called and its return value is returned.
 **
 ** \param[in]      cfgId               An identification of the configuration for which
 **                                     the update of the symmetrical block decryption
 **                                     computation should be requested.
 ** \param[in]      cipherTextPtr       A pointer to the start of an array
 **                                     which contains the constant cipher
 **                                     text that shall be decrypted.
 ** \param[in]      cipherTextLength    Length of the constant cipher text
 **                                     in bytes.
 ** \param[out]     plainTextPtr        A pointer to the start of an array
 **                                     where the decrypted text will be
 **                                     stored.
 ** \param[in,out]  contextBuffer       Holds the pointer to the buffer in which the context of this
 **                                     service is stored.
 ** \param[in,out]  plainTextLengthPtr  Holds a pointer to a memory location
 **                                     in which the length information is stored.
 **                                     On calling this function this parameter
 **                                     shall contain the size of the buffer
 **                                     provided by plainTextPtr. When the
 **                                     request has finished, the amount of
 **                                     data that has been decrypted shall be
 **                                     stored.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK      If the update was successfully requested.
 ** \retval   CAL_E_NOT_OK  If no symmetrical block decryption computation
 **                         has been started via Cal_SymBlockDecryptStart(),
 **                         yet.
 **/
FUNC(Cal_ReturnType, CAL_CODE) Cal_SymBlockDecryptUpdate
(
  Cal_ConfigIdType                                             cfgId,
  Cal_SymBlockDecryptCtxBufType                                contextBuffer,
  P2CONST(uint8,                     AUTOMATIC, CAL_APPL_DATA) cipherTextPtr,
  uint32                                                       cipherTextLength,
  P2VAR(uint8,                       AUTOMATIC, CAL_APPL_DATA) plainTextPtr,
  P2VAR(uint32,                      AUTOMATIC, CAL_APPL_DATA) plainTextLengthPtr
);

/* !LINKSTO CAL0199, 1
 */
/** \brief  Finish symmetrical block decryption computation.
 **
 ** This function requests the finishing of the symmetrical block decryption
 ** computation and the storing of the decrypted text in the given buffer.
 ** The finish function of the configured primitive is called and its return
 ** value is returned.
 **
 ** \param[in]      cfgId               An identification of the configuration for which
 **                                     the finishing of the symmetrical block decryption
 **                                     computation should be requested.
 ** \param[in,out]  contextBuffer       Holds the pointer to the buffer in which the context of this
 **                                     service is stored.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK      If the finish was successfully requested.
 ** \retval   CAL_E_NOT_OK  If no symmetrical block decryption computation
 **                         has been started via Cal_SymBlockDecryptStart(),
 **                         yet.
 **/
FUNC(Cal_ReturnType, CAL_CODE) Cal_SymBlockDecryptFinish
(
  Cal_ConfigIdType              cfgId,
  Cal_SymBlockDecryptCtxBufType contextBuffer
);


#define CAL_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]==========================================================*/


#define CAL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief Array containing all existing SymBlockDecrypt service configurations
 */
extern CONST(Cal_SymBlockDecryptConfigType, CAL_CONST)
  Cal_SymBlockDecConfigurations[CAL_SYMBLOCKDECRYPT_CONFIG_COUNT];

#define CAL_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CAL_SYMBLOCKDECRYPT_ENABLED == TRUE) */

#endif /* #ifndef CAL_SYMBLOCKDECRYPT_H */

