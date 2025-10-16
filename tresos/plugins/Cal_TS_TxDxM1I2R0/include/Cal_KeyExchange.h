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

#ifndef CAL_KEYEXCHANGE_H
#define CAL_KEYEXCHANGE_H


/*==[Includes]================================================================*/

#include <Cal_Types.h>

#include <Cal_KeyExchange_Cfg.h>


/*==[Macros]==================================================================*/



/*==[Types]===================================================================*/


#if (CAL_KEYEXCHANGE_PUBVAL_ENABLED == TRUE)

/* !LINKSTO CAL0025, 1
 */
/* !LINKSTO CAL0074, 1
 */
/** \brief Structure which contains the configuration for a public value calculation of a key
 *         exchange protocol.
 */
/**
 * \struct Cal_KeyExchangePubValConfigType
 * \brief Structure representing the configuration of a public value calculation of a key
 *         exchange protocol.
 *//**
 * \var Cal_KeyExchangePubValConfigType::ConfigId
 * \brief Identifier for the current configuration.
 *//**
 * \var Cal_KeyExchangePubValConfigType::PrimitiveCalcPubValFct
 * \brief Pointer to the function of the underlying Cpl primitive which calculates the public value.
 *//**
 * \var Cal_KeyExchangePubValConfigType::PrimitiveConfigPtr
 * \brief Pointer to a Cpl configuration.
 */
typedef struct
{
  Cal_ConfigIdType ConfigId;

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveCalcPubValFct)
  (
    P2CONST(void,                       AUTOMATIC, CAL_APPL_DATA) cfgPtr,
    P2CONST(Cal_KeyExchangeBaseType,    AUTOMATIC, CAL_APPL_DATA) basePtr,
    P2CONST(Cal_KeyExchangePrivateType, AUTOMATIC, CAL_APPL_DATA) privateValuePtr,
    P2VAR(uint8,                        AUTOMATIC, CAL_APPL_DATA) publicValuePtr,
    P2VAR(uint32,                       AUTOMATIC, CAL_APPL_DATA) publicValueLengthPtr
  );

  P2CONST(void, TYPEDEF, CAL_CONST) PrimitiveConfigPtr;
}
Cal_KeyExchangePubValConfigType;

#endif /* #if (CAL_KEYEXCHANGE_PUBVAL_ENABLED == TRUE) */

#if (CAL_KEYEXCHANGE_SECRET_ENABLED == TRUE)


/* !LINKSTO CAL0730, 1
 */
/* !LINKSTO CAL0742, 1
 */
/** \brief type which specifies the array size of the context buffer required for key exchange
 *         protocol.
 */
typedef Cal_AlignType Cal_KeyExchangeCalcSecretCtxBufType[CAL_KEYEXCHANGE_CONTEXT_BUFFER_SIZE];


/** \brief Structure which contains the configuration for a secret calculation in a Key ExchangeSeed
 *         protocol.
 */
/**
 * \struct Cal_KeyExchangeSecretConfigType
 * \brief Structure representing the configuration of a secret calculation in a Key ExchangeSeed
 *         protocol.
 *//**
 * \var Cal_KeyExchangeSecretConfigType::ConfigId
 * \brief Identifier for the current configuration.
 *//**
 * \var Cal_KeyExchangeSecretConfigType::PrimitiveStartFct
 * \brief Pointer to the start function of the underlying Cpl primitive.
 *//**
 * \var Cal_KeyExchangeSecretConfigType::PrimitiveUpdateFct
 * \brief Pointer to the update function of the underlying Cpl primitive.
 *//**
 * \var Cal_KeyExchangeSecretConfigType::PrimitiveFinishFct
 * \brief Pointer to the finish function of the underlying Cpl primitive.
 *//**
 * \var Cal_KeyExchangeSecretConfigType::PrimitiveConfigPtr
 * \brief Pointer to a Cpl configuration.
 */
typedef struct
{
  Cal_ConfigIdType ConfigId;

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveCalcSecretStartFct)
  (
    P2CONST(void,                       AUTOMATIC, CAL_APPL_DATA) cfgPtr,
    Cal_KeyExchangeCalcSecretCtxBufType                           contextBuffer,
    P2CONST(Cal_KeyExchangeBaseType,    AUTOMATIC, CAL_APPL_DATA) basePtr,
    P2CONST(Cal_KeyExchangePrivateType, AUTOMATIC, CAL_APPL_DATA) privateValuePtr
  );

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveCalcSecretUpdateFct)
  (
    P2CONST(void, AUTOMATIC, CAL_APPL_DATA)  cfgPtr,
    Cal_KeyExchangeCalcSecretCtxBufType      contextBuffer,
    P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) partnerPublicValuePtr,
    uint32                                   partnerPublicValueLength
  );

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveCalcSecretFinishFct)
  (
    P2CONST(void, AUTOMATIC, CAL_APPL_DATA) cfgPtr,
    Cal_KeyExchangeCalcSecretCtxBufType     contextBuffer,
    P2VAR(uint8,  AUTOMATIC, CAL_APPL_DATA) sharedSecretPtr,
    P2VAR(uint32, AUTOMATIC, CAL_APPL_DATA) sharedSecretLengthPtr,
    boolean                                 TruncationIsAllowed
  );

  P2CONST(void, AUTOMATIC, CAL_CONST) PrimitiveConfigPtr;
}
Cal_KeyExchangeSecretConfigType;

#endif /* #if (CAL_KEYEXCHANGE_SECRET_ENABLED == TRUE) */

/*==[Constants with external linkage]=========================================*/


#define CAL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

#if (CAL_KEYEXCHANGE_PUBVAL_ENABLED == TRUE)
/** \brief Array containing all configurations for the public value calculation of a key exchange
 *         protocol.
 */
extern CONST(Cal_KeyExchangePubValConfigType, CAL_CONST)
  Cal_KeyExPubValConfigurations[CAL_KEYEXPUBVAL_CONFIG_COUNT];
#endif /* (CAL_KEYEXCHANGE_PUBVAL_ENABLED == TRUE) */

#if (CAL_KEYEXCHANGE_SECRET_ENABLED == TRUE)
/** \brief Array containing all configurations for the secret calculation of a key exchange
 *         protocol.
 */
extern CONST(Cal_KeyExchangeSecretConfigType, CAL_CONST)
  Cal_KeyExSecretConfigurations[CAL_KEYEXSECRET_CONFIG_COUNT];
#endif /* #if (CAL_KEYEXCHANGE_SECRET_ENABLED == TRUE) */

#define CAL_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>


/*==[Variables with external linkage]=========================================*/



/*==[Declaration of functions with external linkage]==========================*/

#define CAL_START_SEC_CODE
#include <MemMap.h>

#if (CAL_KEYEXCHANGE_PUBVAL_ENABLED == TRUE)

/* !LINKSTO CAL0377, 1
 */
/**
 *
 * \brief Calculate public value for the key exchange protocol.
 *
 * This function performs the calculation of a public value. The
 * public value calculation function of the configured primitive is called and its
 * return value is returned.
 *
 * \param[in]     cfgId                 An identification of the configuration for which the public
 *                                      value calculation shall be requested.
 *
 * \param[in]     basePtr               A Pointer to the base information known to both users of the
 *                                      key exchange protocol.
 *
 * \param[in]     privateValuePtr       A pointer to the private information known only to the
 *                                      current user of the key exchange protocol.
 *
 * \param[out]    publicValuePtr        A pointer to the buffer where the public value shall be
 *                                      stored.
 *
 * \param[in,out] publicValueLengthPtr  A pointer which holds the length information.
 *                                      On calling it holds the length f the buffer provided by
 *                                      publicValuePtr.
 *                                      On returning it holds the length of the calculated public
 *                                      value.
 *
 * \returns error value
 *
 * \retval CAL_E_OK                 If the public value calculation was successfully requested.
 * \retval CAL_E_NOT_OK             If the request failed.
 * \retval CAL_E_SMALL_BUFFER       If the provided buffer is too small to store the result.
 *
 */
extern FUNC(Cal_ReturnType, CAL_CODE) Cal_KeyExchangeCalcPubVal
(
  Cal_ConfigIdType                                              cfgId,
  P2CONST(Cal_KeyExchangeBaseType,    AUTOMATIC, CAL_APPL_DATA) basePtr,
  P2CONST(Cal_KeyExchangePrivateType, AUTOMATIC, CAL_APPL_DATA) privateValuePtr,
  P2VAR(uint8,                        AUTOMATIC, CAL_APPL_DATA) publicValuePtr,
  P2VAR(uint32,                       AUTOMATIC, CAL_APPL_DATA) publicValueLengthPtr
);

#endif /* #if (CAL_KEYEXCHANGE_PUBVAL_ENABLED == TRUE) */


#if (CAL_KEYEXCHANGE_SECRET_ENABLED == TRUE)
/* !LINKSTO CAL0396, 1
 */
/**
 *
 * \brief Start calculation of the secret of a key exchange protocol.
 *
 * This function performs the start of the secret calculation of a key exchange. The secret
 * calculation start function of the
 * configured primitive is called and its return value is returned.
 *
 * \param[in]  cfgId            An identification of the secret calculation configuration for which
 *                              the initialization shall be requested.
 * \param[out] contextBuffer    A Pointer to a buffer where the context of the current configuration
 *                              will be stored.
 * \param[in]  basePtr          A Pointer to the base information known to both users of the
 *                              key exchange protocol.
 * \param[in]  privateValuePtr  A pointer to the private information known only to the
 *                              current user of the key exchange protocol.

 * \returns error value
 *
 * \retval CAL_E_OK     If the secret calculation start was successfully requested.
 * \retval CAL_E_NOT_OK If the request failed.
 *
 */
extern FUNC(Cal_ReturnType, CAL_CODE) Cal_KeyExchangeCalcSecretStart
(
  Cal_ConfigIdType                                              cfgId,
  Cal_KeyExchangeCalcSecretCtxBufType                           contextBuffer,
  P2CONST(Cal_KeyExchangeBaseType,    AUTOMATIC, CAL_APPL_DATA) basePtr,
  P2CONST(Cal_KeyExchangePrivateType, AUTOMATIC, CAL_APPL_DATA) privateValuePtr
);

/* !LINKSTO CAL0404, 1
 */
/**
 *
 * \brief Update secret calculation.
 *
 * This function performs the update of the KeyExchange secret calculation. The secret calculation
 * update function of the configured primitive is called and its return value is returned.
 *
 * \param[in]     cfgId                     An identification of the configuration for which the
 *                                          secret calculation update shall be requested.
 * \param[in,out] contextBuffer             A Pointer to a buffer which holds the context of the
 *                                          current configuration.
 * \param[in]     partnerPublicValuePtr     A pointer to the public value data from the key exchange
 *                                          partner.
 * \param[in]     partnerPublicValueLength  Holds the length of the public value data.
 *
 * \returns error value
 *
 * \retval CAL_E_OK     If the secret calculation update was successfully requested.
 * \retval CAL_E_NOT_OK Otherwise.
 */
extern FUNC(Cal_ReturnType, CAL_CODE) Cal_KeyExchangeCalcSecretUpdate
(
  Cal_ConfigIdType                         cfgId,
  Cal_KeyExchangeCalcSecretCtxBufType      contextBuffer,
  P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) partnerPublicValuePtr,
  uint32                                   partnerPublicValueLength
);

/* !LINKSTO CAL0411, 1
 */
/**
 *
 * \brief Finish secret calculation.
 *
 * This function performs the finishing of the secret calculation of a key exchange protocol.
 *
 * \param[in]     cfgId                 An identification of the configuration for which the
 *                                      secret calculation finish shall be requested.
 * \param[in,out] contextBuffer         A Pointer to a buffer which holds the context of the current
 *                                      configuration.
 * \param[out]    sharedSecretPtr       A Pointer to a buffer which hold the calculated secret of
 *                                      the key exchange.
 * \param[in,out] sharedSecretLengthPtr Holds the Length information.
 *                                      On Calling the Pointer holds the length of the buffer
 *                                      provided by sharedSecretPtr.
 *                                      On returning the pointer holds the length of the shared
 *                                      secret.
 * \param[in]     TruncationIsAllowed   This parameter states whether the truncation of the
 *                                      calculated secret is allowed.
 *                                      TRUE: Truncation is allowed.
 *                                      FALSE: Truncation is not allowed.
 *
 * \returns error value
 *
 * \retval CAL_E_OK           If the secret of the key exchange was successfully calculated.
 * \retval CAL_E_NOT_OK       The request failed.
 * \retval CAL_E_SMALL_BUFFER The provided buffer is too small to store the result and truncation
 *                            is not allowed.
 */
extern FUNC(Cal_ReturnType, CAL_CODE) Cal_KeyExchangeCalcSecretFinish
(
  Cal_ConfigIdType                        cfgId,
  Cal_KeyExchangeCalcSecretCtxBufType     contextBuffer,
  P2VAR(uint8,  AUTOMATIC, CAL_APPL_DATA) sharedSecretPtr,
  P2VAR(uint32, AUTOMATIC, CAL_APPL_DATA) sharedSecretLengthPtr,
  boolean                                 TruncationIsAllowed
);

#endif /* #if (CAL_KEYEXCHANGE_SECRET_ENABLED == TRUE) */

#define CAL_STOP_SEC_CODE
#include <MemMap.h>


#endif /* #ifndef CAL_KEYEXCHANGE_H */

