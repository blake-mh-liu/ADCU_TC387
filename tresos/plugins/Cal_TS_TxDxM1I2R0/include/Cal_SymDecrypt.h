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

#ifndef CAL_SYMDECRYPT_H
#define CAL_SYMDECRYPT_H


/*==================[includes]====================================================================*/


#include <Cal_Types.h>
#include <Cal_SymDecrypt_Cfg.h>

#if (CAL_SYM_DECRYPT_ENABLED == TRUE)

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/


/* !LINKSTO CAL0730, 1
 */
/* !LINKSTO CAL0742, 1
 */
/** \brief type representing the required context buffer for symmetrical decryption.
 */
typedef Cal_AlignType Cal_SymDecryptCtxBufType[CAL_SYMDECRYPT_CTX_BUF_SIZE];



/* !LINKSTO CAL0025, 1
 */
/* !LINKSTO CAL0074, 1
 */
/**
 * \struct Cal_SymDecryptConfigType
 * \brief Structure representing the configuration of the symmetrical decryption
 *         algorithm.
 *//**
 * \var Cal_SymDecryptConfigType::ConfigId
 * \brief Identifier for the current configuration.
 *//**
 * \var Cal_SymDecryptConfigType::PrimitiveStartFct
 * \brief Pointer to the start function of the underlying Cpl primitive.
 *//**
 * \var Cal_SymDecryptConfigType::PrimitiveUpdateFct
 * \brief Pointer to the update function of the underlying Cpl primitive.
 *//**
 * \var Cal_SymDecryptConfigType::PrimitiveFinishFct
 * \brief Pointer to the finish function of the underlying Cpl primitive.
 *//**
 * \var Cal_SymDecryptConfigType::PrimitiveConfigPtr
 * \brief Pointer to a Cpl configuration.
 */
typedef struct
{
  Cal_ConfigIdType ConfigId;

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveStartFct)
  (
    P2CONST(void,                     AUTOMATIC, CAL_APPL_DATA) cfgPtr,
    Cal_SymDecryptCtxBufType                                    contextBuffer,
    P2CONST(Cal_SymKeyType,           AUTOMATIC, CAL_APPL_DATA) keyPtr,
    P2CONST(uint8,                    AUTOMATIC, CAL_APPL_DATA) initVectorPtr,
        VAR(uint32,                   AUTOMATIC               ) initVectorLength
  );

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveUpdateFct)
  (
    P2CONST(void,   AUTOMATIC, CAL_APPL_DATA) cfgPtr,
    Cal_SymDecryptCtxBufType                  contextBuffer,
    P2CONST(uint8,  AUTOMATIC, CAL_APPL_DATA) iputTextPtr,
        VAR(uint32, AUTOMATIC               ) iputTextLength,
      P2VAR(uint8,  AUTOMATIC, CAL_APPL_DATA) oputTextPtr,
      P2VAR(uint32, AUTOMATIC, CAL_APPL_DATA) oputTextLengthPtr
  );

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveFinishFct)
  (
    P2CONST(void, AUTOMATIC, CAL_APPL_DATA) cfgPtr,
    Cal_SymDecryptCtxBufType                contextBuffer,
    P2VAR(uint8,  AUTOMATIC, CAL_APPL_DATA) oputTextPtr,
    P2VAR(uint32, AUTOMATIC, CAL_APPL_DATA) oputTextLengthPtr
  );
  P2CONST(void, TYPEDEF, CAL_CONST) PrimitiveConfigPtr;

}
Cal_SymDecryptConfigType;

/*==================[external function declarations]==============================================*/

#define CAL_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO CAL0228, 1
 */
/** \brief  Start symmetrical decryption computation.
 **
 ** This function performs the start of the symmetrical decryption for
 ** the given configuration. The start function of the configured primitive
 ** is called and its return value is returned.
 **
 ** \param[in]      cfgId             An identification of the configuration for which
 **                                   the start of the symmetrical decryption
 **                                   computation should be requested.
 ** \param[out]     contextBuffer     A buffer which will hold the context for this SymDecrypt
 **                                   configuration.
 ** \param[in]      keyPtr            A pointer to the key which should be used in the
 **                                   symmetrical decryption computation.
 ** \param[in]      InitVectorPtr     Holds a pointer to the initialization vector which has to be
 **                                   used during the symmetrical decryption computation.
 ** \param[in]      InitVectorLength  Holds the length of the initialisation vector
 **                                   which has to be used during the symmetrical
 **                                   decryption computation.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK      If the start was successfully requested.
 ** \retval   CAL_E_NOT_OK  Otherwise.
 **/
FUNC(Cal_ReturnType, CAL_CODE) Cal_SymDecryptStart
(
  VAR(Cal_ConfigIdType,         AUTOMATIC               ) cfgId,
  VAR(Cal_SymDecryptCtxBufType, AUTOMATIC               ) contextBuffer,
  P2CONST(Cal_SymKeyType,       AUTOMATIC, CAL_APPL_DATA) keyPtr,
  P2CONST(uint8,                AUTOMATIC, CAL_APPL_DATA) InitVectorPtr,
  VAR(uint32,                   AUTOMATIC               ) InitVectorLength
);

/* !LINKSTO CAL0234, 1
 */
/** \brief  Update symmetrical decryption computation.
 **
 ** This function performs the update of the symmetrical decryption
 ** computation for the given data. The update function of the configured
 ** primitive is called and its return value is returned.
 **
 ** \param[in]      cfgId               An identification of the configuration for which
 **                                     the update of the symmetrical decryption
 **                                     computation should be requested.
 ** \param[in,out]  contextBuffer       A buffer which holds the context for this SymDecrypt
 **                                     configuration.
 ** \param[in]      cipherTextPtr       A pointer to the start of an array
 **                                     which contains the constant cipher
 **                                     text that shall be decrypted.
 ** \param[in]      cipherTextLength    Length of the constant cipher text
 **                                     in bytes.
 ** \param[out]     plainTextPtr        A pointer to the start of an array
 **                                     where the decrypted text will be
 **                                     stored.
 ** \param[in,out]  plainTextLengthPtr  Holds a pointer to a memory location
 **                                     in which the length information is stored.
 **                                     On calling this function this parameter
 **                                     shall contain the size of the buffer
 **                                     provided by plainTextPtr.
 **                                     When the
 **                                     request has finished, the amount of
 **                                     data that has been decrypted shall be
 **                                     stored.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK            If the update was successfully requested.
 ** \retval   CAL_E_NOT_OK        If no symmetrical decryption computation
 **                               has been started via Cal_SymDecryptStart(),
 **                               yet.
 ** \retval   CAL_E_SMALL_BUFFER  If the provided buffer is to small to store
 **                               the result.
 **/
FUNC(Cal_ReturnType, CAL_CODE) Cal_SymDecryptUpdate
(
  VAR(Cal_ConfigIdType,         AUTOMATIC               ) cfgId,
  VAR(Cal_SymDecryptCtxBufType, AUTOMATIC               ) contextBuffer,
  P2CONST(uint8,                AUTOMATIC, CAL_APPL_DATA) cipherTextPtr,
  VAR(uint32,                   AUTOMATIC               ) cipherTextLength,
  P2VAR(uint8,                  AUTOMATIC, CAL_APPL_DATA) plainTextPtr,
  P2VAR(uint32,                 AUTOMATIC, CAL_APPL_DATA) plainTextLengthPtr
);

/* !LINKSTO CAL0243, 1
 */
/** \brief  Finish symmetrical decryption computation.
 **
 ** This function finishes the symmetrical decryption
 ** computation and the stores of the decrypted text in the given buffer.
 ** The finish function of the configured primitive is called and its return
 ** value is returned.
 **
 ** \param[in]      cfgId               An identification of the configuration for which
 **                                     the finish of the symmetrical decryption
 **                                     computation should be requested.
 ** \param[in,out]  contextBuffer       A buffer which holds the context for this SymDecrypt
 **                                     configuration.
 ** \param[out]     plainTextPtr        A pointer to the start of an array
 **                                     where the decrypted text will be
 **                                     stored.
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
 ** \retval   CAL_E_OK            If the finish was successfully requested.
 ** \retval   CAL_E_NOT_OK        If no symmetrical decryption computation
 **                               has been started via Cal_SymDecryptStart(),
 **                               yet.
 ** \retval   CAL_E_SMALL_BUFFER  If the provided buffer is to small to store
 **                               the result.
 **/
FUNC(Cal_ReturnType, CAL_CODE) Cal_SymDecryptFinish
(
  VAR(Cal_ConfigIdType,         AUTOMATIC               ) cfgId,
  VAR(Cal_SymDecryptCtxBufType, AUTOMATIC               ) contextBuffer,
  P2VAR(uint8,                  AUTOMATIC, CAL_APPL_DATA) plainTextPtr,
  P2VAR(uint32,                 AUTOMATIC, CAL_APPL_DATA) plainTextLengthPtr
);



#define CAL_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]==========================================================*/


#define CAL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief Array containing all existing symmetrical decryption service configurations.
 */
extern CONST(Cal_SymDecryptConfigType, CAL_CONST)
  Cal_SymDecryptConfigurations[CAL_SYMDECRYPT_CONFIG_COUNT];

#define CAL_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CAL_SYM_DECRYPT_ENABLED == TRUE) */

#endif /* #ifndef CAL_SYMDECRYPT_H */

