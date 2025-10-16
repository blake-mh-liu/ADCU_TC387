/**
 * \file
 *
 * \brief AUTOSAR Dcm
 *
 * This file contains the implementation of the AUTOSAR
 * module Dcm.
 *
 * \version 5.0.24
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* !LINKSTO Dcm.Dsn.File.CryptoStackFacade.PublicApi,1 */
/* This file contains the public API of the CryptoStackFacade SW unit. */

#if (!defined DCM_AUTHENTICATION_CRYPTOSTACKFACADE_H)
#define DCM_AUTHENTICATION_CRYPTOSTACKFACADE_H

/*==================[inclusions]==================================================================*/

#include <Std_Types.h>                                /* AUTOSAR standard types */
#include <Dcm_Types.h>
#include <Dcm_Authentication_Cfg.h>
#include <Dcm_Authentication_AuthenticationHandler.h> /* Includes type definition Dcm_AuthenticationConnectionIndexType */

#if (DCM_AUTHENTICATION_CONNECTION == STD_ON)

/*==================[macro definitions]===========================================================*/

/** @defgroup Macro_Dcm_CryptoOperationType macros for Dcm_CryptoOperationType
 ** \brief    These macros are used as values for Dcm_CryptoOperationType
 **  @{
 */
#if (defined DCM_CRYPTOOPERATION_VERIFYCERTIFICATE)
  #error "DCM_CRYPTOOPERATION_VERIFYCERTIFICATE is already defined"
#endif
#define DCM_CRYPTOOPERATION_VERIFYCERTIFICATE    0U

#if (defined DCM_CRYPTOOPERATION_CREATECHALLENGE)
  #error "DCM_CRYPTOOPERATION_CREATECHALLENGE is already defined"
#endif
#define DCM_CRYPTOOPERATION_CREATECHALLENGE      1U

#if (defined DCM_CRYPTOOPERATION_SIGNCHALLENGE)
  #error "DCM_CRYPTOOPERATION_SIGNCHALLENGE is already defined"
#endif
#define DCM_CRYPTOOPERATION_SIGNCHALLENGE        2U

#if (defined DCM_CRYPTOOPERATION_VERIFYSIGNATURE)
  #error "DCM_CRYPTOOPERATION_VERIFYSIGNATURE is already defined"
#endif
#define DCM_CRYPTOOPERATION_VERIFYSIGNATURE      3U
/* @} */
/* End of macro definitions for Dcm_CryptoOperationType */

/*==================[type declarations]===========================================================*/
/* !LINKSTO Dcm.Dsn.Type.Dcm_CryptoOperationType,1 */
typedef uint8 Dcm_CryptoOperationType;

typedef struct
{
  uint16 GeneratedLength;
  Dcm_NegativeResponseCodeType AuthenticationResult;
  boolean KeyMCallbackPending;
  boolean CsmCallbackPending;
} Dcm_CryptoStackFacadeType;

/*==================[external constant declarations]==============================================*/

/*==================[external data declarations]==================================================*/
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dcm_MemMap.h>

extern VAR(Dcm_CryptoStackFacadeType, DCM_VAR) Dcm_CryptoStackFacade[DCM_NUM_AUTHENTICATION_CONNECTIONS];

#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dcm_MemMap.h>
/*==================[external function declarations]==============================================*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/** \brief Initializes the Dcm_CryptoStackFacade for UDS service 0x29
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, DCM_CODE) Dcm_CryptoStackFacade_Init(void);

/** \brief Cancels an ongoing cryptographic operation for a connection
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 ** \param[in]    Operation                      ID of the operation to be canceled.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, DCM_CODE) Dcm_CryptoStackFacade_CancelOperation(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  Dcm_CryptoOperationType Operation
);

/** \brief Generates a server challenge of the configured ChallengeLength for
 ** the selected connection
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 ** \param[in]    LengthOfChallenge              Required size of the generated server challenge.
 ** \param[out]   ChallengeServer                Pointer to the memory location where the generated
 **                                              server challenge shall be stored.
 ** \param[out]   ErrorCode                      Pointer to the memory location where the NRC value shall
 **                                              be stored, if the result is E_NOT_OK.
 ** \return  Result of the create challenge request
 ** \retval E_OK      Request accepted
 ** \retval E_NOT_OK  Request failed, ErrorCode is written
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Asynchronous}
 */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_CryptoStackFacade_CreateChallenge(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  uint16 LengthOfChallenge,
  P2VAR(uint8, AUTOMATIC, DCM_VAR) ChallengeServer,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode
);

/** \brief Reads the role extension octet string from the available certificate of the
 ** selected connection
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 ** \param[out]   AuthenticationRole             Pointer to a output buffer that holds the authentication
 **                                              role of the configured size.
 ** \param[out]   ErrorCode                      Pointer to the memory location where the NRC value shall
 **                                              be stored, if the result is E_NOT_OK.
 ** \return  Result of the read authentication role request
 ** \retval E_OK      Request completed
 ** \retval E_NOT_OK  Request failed, ErrorCode is written
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_CryptoStackFacade_GetAuthenticationRole(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  P2VAR(uint8, AUTOMATIC, DCM_VAR) AuthenticationRole,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode
);

/** \brief Stores the client certificate for a subsequent certificate verification
 **
 ** This function temporarily stores the client certificate for a subsequent certificate
 ** verification for a connection.  A stored certificate can be deleted by calling this
 ** function with LengthOfCertificate equal to zero.
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 ** \param[in]    Certificate                    Pointer to the certificate data.
 ** \param[in]    LengthOfCertificate            Length of the certificate data.
 ** \param[out]   ErrorCode                      Pointer to the memory location where the NRC value shall
 **                                              be stored, if the result is E_NOT_OK.
 ** \return  Result of the set certificate request
 ** \retval E_OK      Request completed
 ** \retval E_NOT_OK  Request failed, ErrorCode is written
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_CryptoStackFacade_SetCertificate(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  P2VAR(uint8, AUTOMATIC, DCM_VAR) Certificate,
  uint32 LengthOfCertificate,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode
);

#if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON)
/** \brief Signs the client challenge
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 ** \param[in]    ChallengeClient                Pointer to the challenge client data.
 ** \param[in]    LengthOfChallenge              Length of the challenge client data.
 ** \param[out]   SignedChallenge                Pointer to the memory location where the signed
 **                                              client challenge shall be stored.
 ** \param[in]    LengthOfSignedChallenge        Required size of the signed client challenge.
 ** \param[out]   ErrorCode                      Pointer to the memory location where the NRC value shall
 **                                              be stored, if the result is E_NOT_OK.
 ** \return  Result of the sign client challenge request
 ** \retval E_OK      Request accepted
 ** \retval E_NOT_OK  Request failed, ErrorCode is written
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Asynchronous}
 */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_CryptoStackFacade_SignChallenge(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  P2CONST(uint8, AUTOMATIC, DCM_VAR) ChallengeClient,
  uint32 LengthOfChallenge,
  P2VAR(uint8, AUTOMATIC, DCM_VAR) SignedChallenge,
  uint32 LengthOfSignedChallenge,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode
);

/** \brief Gets the server certificate
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 ** \param[in,out]CertificateServer              Provides a pointer to a certificate data structure.
 **                                              The buffer located by the pointer in the structure shall
 **                                              be provided by the caller of this function. The length
 **                                              information indicates the maximum length of the buffer
 **                                              when the function is called. If E_OK is returned, the
 **                                              length information indicates the actual length of the
 **                                              certificate data in the buffer.
 ** \param[out]   ErrorCode                      Pointer to the memory location where the NRC value shall
 **                                              be stored, if the result is E_NOT_OK.
 ** \return  Result of the server certificate get request
 ** \retval E_OK      Request accepted
 ** \retval E_NOT_OK  Request failed, ErrorCode is written
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_CryptoStackFacade_GetCertificate(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  P2VAR(Dcm_AuthenticationCertificateType, AUTOMATIC, DCM_VAR) CertificateServer,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode
);
#endif /* #if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON) */

/** \brief Verifies the client certificate
 **
 ** This function verifies the client certificate, previously stored with SetCertificate().
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 ** \param[out]   ErrorCode                      Pointer to the memory location where the NRC value shall
 **                                              be stored, if the result is E_NOT_OK.
 ** \return  Result of the certificate verification request
 ** \retval E_OK      Request accepted
 ** \retval E_NOT_OK  Request not accepted, ErrorCode is written
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Asynchronous}
 */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_CryptoStackFacade_VerifyCertificate(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode
);

/** \brief Verifies the signature of the proof of ownership client
 **
 ** This function verifies the signature of the proof of ownership client with the
 ** public key from the previously received certificate client.
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 ** \param[in]    Data                           Pointer to the data to be verified.
 ** \param[in]    LengthOfData                   Length of the data to be verified.
 ** \param[in]    Signature                      Pointer to the signature to be verified.
 ** \param[in]    LengthOfSignature              Length of the signature.
 ** \param[out]   ErrorCode                      Pointer to the memory location where the NRC value shall
 **                                              be stored, if the result is E_NOT_OK.
 ** \return  Result of the signature verification request
 ** \retval E_OK      Request accepted
 ** \retval E_NOT_OK  Request not accepted, ErrorCode is written
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Asynchronous}
 */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_CryptoStackFacade_VerifySignature(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  P2CONST(uint8, AUTOMATIC, DCM_VAR) Data,
  uint16 LengthOfData,
  P2CONST(uint8, AUTOMATIC, DCM_VAR) Signature,
  uint16 LengthOfSignature,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode
);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif /* #if (DCM_AUTHENTICATION_CONNECTION == STD_ON) */

#endif /* if !defined(DCM_AUTHENTICATION_CRYPTOSTACKFACADE_H) */
/*==================[end of file]=================================================================*/
