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

#ifndef CAL_SIGNATUREVERIFY_H
#define CAL_SIGNATUREVERIFY_H


/*==[Includes]================================================================*/


#include <Cal_Types.h>

#include <Cal_SignatureVerify_Cfg.h>

#if (CAL_SIG_VRFY_ENABLED == TRUE)

/*==[Macros]==================================================================*/



/*==[Types]===================================================================*/


/* !LINKSTO CAL0730, 1
 */
/* !LINKSTO CAL0742, 1
 */
/** \brief type which specifies the array size of the context buffer required for signature
 *         verification.
 */
typedef Cal_AlignType Cal_SignatureVerifyCtxBufType[CAL_SIGNATUREVERIFY_CONTEXT_BUFFER_SIZE];



/* !LINKSTO CAL0025, 1
 */
/* !LINKSTO CAL0074, 1
 */
/**
 * \struct Cal_SignatureVerifyConfigType
 * \brief Structure representing the configuration of the signature verification
 *         algorithm.
 *//**
 * \var Cal_SignatureVerifyConfigType::ConfigId
 * \brief Identifier for the current configuration.
 *//**
 * \var Cal_SignatureVerifyConfigType::PrimitiveStartFct
 * \brief Pointer to the start function of the underlying Cpl primitive.
 *//**
 * \var Cal_SignatureVerifyConfigType::PrimitiveUpdateFct
 * \brief Pointer to the update function of the underlying Cpl primitive.
 *//**
 * \var Cal_SignatureVerifyConfigType::PrimitiveFinishFct
 * \brief Pointer to the finish function of the underlying Cpl primitive.
 *//**
 * \var Cal_SignatureVerifyConfigType::PrimitiveConfigPtr
 * \brief Pointer to a Cpl configuration.
 */
typedef struct
{
  Cal_ConfigIdType ConfigId;

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveStartFct)
  (
    P2CONST(void, AUTOMATIC, CAL_APPL_DATA)                  cfgPtr,
    Cal_SignatureVerifyCtxBufType                            contextBuffer,
    P2CONST(Cal_AsymPublicKeyType, AUTOMATIC, CAL_APPL_DATA) keyPtr
  );

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveUpdateFct)
  (
    P2CONST(void, AUTOMATIC, CAL_APPL_DATA)  cfgPtr,
    Cal_SignatureVerifyCtxBufType            contextBuffer,
    P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) dataPtr,
    uint32                                   dataLength
  );

  P2FUNC(Cal_ReturnType, CAL_APPL_CODE, PrimitiveFinishFct)
  (
    P2CONST(void, AUTOMATIC, CAL_APPL_DATA)               cfgPtr,
    Cal_SignatureVerifyCtxBufType                         contextBuffer,
    P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA)              signaturePtr,
    uint32                                                signatureLength,
    P2VAR(Cal_VerifyResultType, AUTOMATIC, CAL_APPL_DATA) resultPtr
  );

  P2CONST(void, TYPEDEF, CAL_CONST) PrimitiveConfigPtr;
}
Cal_SignatureVerifyConfigType;


/*==[Constants with external linkage]=========================================*/


#define CAL_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>


/** \brief Signature verification configuration.
 * An array containing the configurations of the signature verification service.
 */
extern CONST(Cal_SignatureVerifyConfigType, CAL_CONST)
  Cal_SigVerifyConfigurations[CAL_SIGVRFY_CONFIG_COUNT];

#define CAL_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>


/*==[Variables with external linkage]=========================================*/



/*==[Declaration of functions with external linkage]==========================*/

#define CAL_START_SEC_CODE
#include <MemMap.h>

/* !LINKSTO CAL0314, 1
 */
/**
 *
 * \brief Start signature verification.
 *
 * This function requests the start of the signature verification for the
 * given configuration and key. The start function of the configured primitive
 * is called and its return value is returned.
 *
 * \param[in]  cfgId         An identification of the configuration for which the start of the
 *                           signature verification shall be requested.
 *
 * \param[out] contextBuffer A pointer to a buffer where the context of the current SignatureVerify
 *                           configuration will be stored.
 *
 * \param[in]  keyPtr        A pointer to the key which should be used in the signature
 *                           verification.
 *
 * \returns error value
 *
 * \retval CAL_E_OK     If the start was successfully requested.
 * \retval CAL_E_NOT_OK If the request failed.
 *
 */
extern FUNC(Cal_ReturnType, CAL_CODE) Cal_SignatureVerifyStart
(
  Cal_ConfigIdType                                         cfgId,
  Cal_SignatureVerifyCtxBufType                            contextBuffer,
  P2CONST(Cal_AsymPublicKeyType, AUTOMATIC, CAL_APPL_DATA) keyPtr
);

/* !LINKSTO CAL0320, 1
 */
/**
 *
 * \brief Update signature verification.
 *
 * This function performs the update of a signature verification for
 * the given data. The update function of the configured primitive
 * is called and its return value is returned.
 *
 * \param[in]     cfgId         An identification of the configuration for which the update of the
 *                              signature verification shall be requested.
 *
 * \param[in,out] contextBuffer A pointer to a buffer which holds the context of the current
 *                              SignatureVerify configuration.
 *
 * \param[in]     dataPtr       A pointer to the start of an array which contains a part of the
 *                              data for which the signature should be verified.
 *
 * \param[in]     dataLength    The amount of bytes of data.
 *
 * \returns error value
 *
 * \retval CAL_E_OK     If the update was successfully requested.
 *
 * \retval CAL_E_NOT_OK If no signature verification has been started via
 *         Cal_SignatureVerifyStart()yet.
 */
extern FUNC(Cal_ReturnType, CAL_CODE) Cal_SignatureVerifyUpdate
(
  Cal_ConfigIdType                         cfgId,
  Cal_SignatureVerifyCtxBufType            contextBuffer,
  P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA) dataPtr,
  uint32                                   dataLength
);

/* !LINKSTO CAL0327, 1
 */
/**
 *
 * \brief Finish signature verification.
 *
 * This function performs the finishing of a signature verification. The finish
 * function of the configured primitive is called and its return value is
 * returned.
 *
 * \param[in]     cfgId           An identification of the configuration for which the finish of the
 *                                signature verification shall be requested.
 *
 * \param[in,out] contextBuffer   A pointer to a buffer which holds the context of the current
 *                                SignatureVerify configuration.
 *
 * \param[in]     signaturePtr    A pointer to the start of an array where the signature to
 *                                be verified is stored.
 *
 * \param[in]     signatureLength The length of the signature in bytes.
 *
 * \param[out]    resultPtr       A pointer to a variable where the result of the signature
 *                                verification should be stored.
 *
 * \returns error value
 *
 * \retval CAL_E_OK If the finish was successfully requested.
 *
 * \retval CAL_E_NOT_OK If no signature verification has been started via
 *         Cal_SignatureVerifyStart() yet.
 */
extern FUNC(Cal_ReturnType, CAL_CODE) Cal_SignatureVerifyFinish
(
  Cal_ConfigIdType                                      cfgId,
  Cal_SignatureVerifyCtxBufType                         contextBuffer,
  P2CONST(uint8, AUTOMATIC, CAL_APPL_DATA)              signaturePtr,
  uint32                                                signatureLength,
  P2VAR(Cal_VerifyResultType, AUTOMATIC, CAL_APPL_DATA) resultPtr
);


#define CAL_STOP_SEC_CODE
#include <MemMap.h>

#endif /* #if (CAL_SIG_VRFY_ENABLED == TRUE) */

#endif /* #ifndef CAL_SIGNATUREVERIFY_H */

