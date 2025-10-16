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

#ifndef CAL_KEYDERIVE_H
#define CAL_KEYDERIVE_H

/*==================[includes]====================================================================*/

#include <Cal_Types.h>
#include <Cal_KeyDerive_Cfg.h>

#if (CAL_KEY_DERIVE_ENABLED == TRUE)


/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/


/* !LINKSTO CAL0730, 1
 */
/* !LINKSTO CAL0742, 1
 */
/** \brief type representing the required context buffer for key derivation.
 */
typedef Cal_AlignType Cal_KeyDeriveCtxBufType[CAL_KEYDERIVE_CONTEXT_BUFFER_SIZE];




/* !LINKSTO CAL0025, 1
 */
/* !LINKSTO CAL0074, 1
 */
/**
 * \struct Cal_KeyDeriveConfigType
 * \brief Structure representing the configuration of the key derivation
 *         algorithm.
 *//**
 * \var Cal_KeyDeriveConfigType::ConfigId
 * \brief Identifier for the current configuration.
 *//**
 * \var Cal_KeyDeriveConfigType::PrimitiveStartFct
 * \brief Pointer to the start function of the underlying Cpl primitive.
 *//**
 * \var Cal_KeyDeriveConfigType::PrimitiveUpdateFct
 * \brief Pointer to the update function of the underlying Cpl primitive.
 *//**
 * \var Cal_KeyDeriveConfigType::PrimitiveFinishFct
 * \brief Pointer to the finish function of the underlying Cpl primitive.
 *//**
 * \var Cal_KeyDeriveConfigType::PrimitiveConfigPtr
 * \brief Pointer to a Cpl configuration.
 */
typedef struct
{
  Cal_ConfigIdType ConfigId;

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveStartFct)
  (
    P2CONST(void, AUTOMATIC, CAL_APPL_DATA) cfgPtr,
    Cal_KeyDeriveCtxBufType                 contextBuffer,
    uint32                                  keyLength,
    uint32                                  interations
  );

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveUpdateFct)
  (
    P2CONST(void, AUTOMATIC, CAL_APPL_DATA)  cfgPtr,
    Cal_KeyDeriveCtxBufType              contextBuffer,
    P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) passwordPtr,
    uint32                                   passwordLength,
    P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) saltPtr,
    uint32                                   saltLength
  );

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveFinishFct)
  (
    P2CONST(void, AUTOMATIC, CAL_APPL_DATA)         cfgPtr,
    Cal_KeyDeriveCtxBufType                         contextBuffer,
    P2VAR(Cal_SymKeyType, AUTOMATIC, CAL_APPL_DATA) keyPtr
  );

  P2CONST(void, TYPEDEF, CAL_CONST) PrimitiveConfigPtr;
}
Cal_KeyDeriveConfigType;

/*==================[external function declarations]==============================================*/

#define CAL_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO CAL0355, 1
 */
/** \brief  Start key derivation.
 **
 ** This function performs the start of a key derivation for the
 ** given configuration. The start function of the configured primitive
 ** is called and its return value is returned.
 **
 ** \param[in]      cfgId          An identification of the configuration for which the
 **                                the start of the key derivation shall be
 **                                requested.
 ** \param[out]     contextBuffer  A Pointer to a buffer where the context of the current
 **                                configuration of the KeyDerive service will be stored.
 ** \param[in]      keyLength      The length of the key to be derived.
 ** \param[in]      iterations     The number of iterations to be performed by the underlying key
 **                                derivation primitive.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK      If the start was successfully requested.
 ** \retval   CAL_E_NOT_OK  Otherwise.
 **/
extern FUNC(Cal_ReturnType, CAL_CODE) Cal_KeyDeriveStart
(
  Cal_ConfigIdType        cfgId,
  Cal_KeyDeriveCtxBufType contextBuffer,
  uint32                  keyLength,
  uint32                  iterations
);

/* !LINKSTO CAL0362, 1
 */
/** \brief  Update key derivation.
 **
 ** This function performs the update of the key derivation for the
 ** given data. The update function of the configured primitive is called and
 ** its return value is returned.
 **
 ** \param[in]      cfgId          An identification of the configuration for which the
 **                                the update of the key derivation shall be
 **                                requested.
 ** \param[in,out]  contextBuffer  A Pointer to a buffer which holds the context of the current
 **                                configuration of the KeyDerive service.
 ** \param[in]      passwordPtr    A pointer to the the password i.e. the original key from which
 **                                to derive a new key.
 ** \param[in]      passwordLength The length of the password in bytes.
 ** \param[in]      saltPtr        A pointer to the cryptographic salt i.e. a random number.
 ** \param[in]      saltLength     The length of the salt in bytes.
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK     If the update was successfully requested.
 ** \retval   CAL_E_NOT_OK If the request failed.
 **/
extern FUNC(Cal_ReturnType, CAL_CODE) Cal_KeyDeriveUpdate
(
  Cal_ConfigIdType                         cfgId,
  Cal_KeyDeriveCtxBufType                  contextBuffer,
  P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) passwordPtr,
  uint32                                   passwordLength,
  P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) saltPtr,
  uint32                                   saltLength
);

/* !LINKSTO CAL0371, 1
 */
/** \brief  Finish key derivation.
 **
 ** This function performs the finishing of the key derivation. The finish function of the
 ** configured primitive is called and its return value is returned.
 **
 ** \param[in]      cfgId          An identification of the configuration for which the
 **                                the finishing of the key derivation shall be
 **                                requested.
 ** \param[in,out]  contextBuffer  A Pointer to a buffer which holds the context of the current
 **                                configuration of the KeyDerive service.
 ** \param[out]     keyPtr         A pointer to the buffer where the derived key
 **                                should be stored
 **
 ** \returns  Error value.
 **
 ** \retval   CAL_E_OK      If the finish was successfully requested.
 ** \retval   CAL_E_NOT_OK  If the request failed.
 **/
extern FUNC(Cal_ReturnType, CAL_CODE) Cal_KeyDeriveFinish
(
  Cal_ConfigIdType                                cfgId,
  Cal_KeyDeriveCtxBufType                         contextBuffer,
  P2VAR(Cal_SymKeyType, AUTOMATIC, CAL_APPL_DATA) keyPtr
);


#define CAL_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]==========================================================*/


#define CAL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief Array containing all KeyDerive service configurations.
 */
extern CONST(Cal_KeyDeriveConfigType, CAL_CONST)
  Cal_KeyDeriveConfigurations[CAL_KEYDERIVE_CONFIG_COUNT];

#define CAL_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[external data]===============================================================*/

/*================================================================================================*/

#endif /* #if (CAL_KEY_DERIVE_ENABLED == TRUE) */

#endif /* #ifndef CAL_KEYDERIVE_H */

