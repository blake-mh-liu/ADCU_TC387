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

/* !LINKSTO Dcm.Dsn.File.AuthenticationHandler.PublicApi,1 */
/* This file contains the public API of the AuthenticationHandler SW unit. */

#if (!defined DCM_AUTHENTICATION_AUTHENTICATIONHANDLER_H)
#define DCM_AUTHENTICATION_AUTHENTICATIONHANDLER_H

/*==================[inclusions]==================================================================*/

#include <Std_Types.h>         /* AUTOSAR standard types */
#include <Dcm_Types.h>
#include <Dcm_Authentication_Cfg.h>

#if (DCM_AUTHENTICATION_CONNECTION == STD_ON)

/*==================[macro definitions]===========================================================*/

/*==================[type declarations]===========================================================*/

/* !LINKSTO Dcm.Dsn.Type.Dcm_AuthenticationDirectionType,1 */
typedef uint8 Dcm_AuthenticationDirectionType;
#if (defined DCM_AUTHENTICATIONDIRECTION_UNIDIRECTIONAL)
  #error DCM_AUTHENTICATIONDIRECTION_UNIDIRECTIONAL already defined
#endif /* if (defined DCM_AUTHENTICATIONDIRECTION_UNIDIRECTIONAL) */
#define DCM_AUTHENTICATIONDIRECTION_UNIDIRECTIONAL 0U

#if (defined DCM_AUTHENTICATIONDIRECTION_BIDIRECTIONAL)
  #error DCM_AUTHENTICATIONDIRECTION_BIDIRECTIONAL already defined
#endif /* if (defined DCM_AUTHENTICATIONDIRECTION_BIDIRECTIONAL) */
#define DCM_AUTHENTICATIONDIRECTION_BIDIRECTIONAL 1U

/* !LINKSTO Dcm.Dsn.Type.Dcm_AuthenticationCertificateType,1 */
typedef struct
{
  /** \brief Pointer to certificate data. **/
  P2VAR(uint8, TYPEDEF, DCM_VAR) Certificate;
  /** \brief Length of the certificate data. **/
  uint32 LengthOfCertificate;
} Dcm_AuthenticationCertificateType;

/* !LINKSTO Dcm.Dsn.Type.Dcm_AuthenticationChallengeType,1 */
typedef struct
{
  /** \brief Pointer to challenge data. **/
  P2VAR(uint8, TYPEDEF, DCM_VAR) Challenge;
  /** \brief Length of challenge data. **/
  uint32 LengthOfChallenge;
} Dcm_AuthenticationChallengeType;

/* !LINKSTO Dcm.Dsn.Type.Dcm_AuthenticationProofOfOwnershipType,1 */
typedef struct
{
  /** \brief Pointer to the proof of ownership data. **/
  P2VAR(uint8, TYPEDEF, DCM_VAR) ProofOfOwnership;
  /** \brief Length of the proof of ownership data. **/
  uint16 LengthOfProofOfOwnership;
} Dcm_AuthenticationProofOfOwnershipType;

/* !LINKSTO Dcm.Dsn.Type.Dcm_AuthenticationContextType,1 */
typedef struct
{
  /** \brief IN: Descriptor of the client certificate data. **/
  Dcm_AuthenticationCertificateType CertificateClient;
  /** \brief OUT: Descriptor of the server challenge data. **/
  Dcm_AuthenticationChallengeType ChallengeServer;
#if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON)
  /** \brief IN: Descriptor of the client challenge data. **/
  Dcm_AuthenticationChallengeType ChallengeClient;
  /** \brief IN-OUT: Descriptor of the client certificate data. **/
  Dcm_AuthenticationCertificateType CertificateServer;
  /** \brief OUT: */
  Dcm_AuthenticationProofOfOwnershipType ProofOfOwnershipServer;
#endif /* #if (DCM_0X29_0X02_SSVC_ENABLED == STD_ON) */
  /** \brief IN: Selects the authentication direction (unidirectional: client
   *  authentication, bidirectional: client and server authentication). **/
  Dcm_AuthenticationDirectionType AuthenticationDirection;
  /** \brief OUT: Result (NRC) of the authentication processing. **/
  Dcm_NegativeResponseCodeType ErrorCode;
} Dcm_AuthenticationContextType;

/* !LINKSTO Dcm.Dsn.Type.Dcm_AuthenticationConnectionIndexType,1 */
/** \brief The index of a AuthenticationConnection in the Dcm_AuthenticationConfig[] array.*/
typedef uint16 Dcm_AuthenticationConnectionIndexType;

/*==================[external constant declarations]==============================================*/

/*==================[external data declarations]==================================================*/

/*==================[external function declarations]==============================================*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/** \brief Initializes the Dcm_AuthenticationHandler for UDS service 0x29
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, DCM_CODE) Dcm_AuthenticationHandler_Init(void);

/** \brief Performs clean-up tasks in MainFunction context after cancellation is completed.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, DCM_CODE) Dcm_AuthenticationHandler_MainFunction(void);

/** \brief Cancels an ongoing authentication procedure for a connection
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, DCM_CODE) Dcm_AuthenticationHandler_CancelAuthentication(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex
);

/** \brief Processes an authentication request acording to unidirectional APCE
 ** (Authentication with PKI Certificate Exchange) concept
 **
 ** This function processes an authentication request and generates/writes the
 ** server response data into the output buffer, passed via AuthenticationContext
 ** parameter. This includes verification of the client certificate
 ** and generation of the server challenge.
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 ** \param[in]    AuthenticationContext          Pointer to the context that holds all input
 **                                              and output data.
 **
 ** \return  Result of the authentication procedure
 ** \retval E_OK           Request completed
 ** \retval E_NOT_OK       Request failed, NRC is updated in AuthenticationContext
 ** \retval DCM_E_BUSY     Request failed, crypto stack is still busy
 ** \retval DCM_E_PENDING  Request is in progress, function needs to be called again
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Asynchronous}
 */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_AuthenticationHandler_AuthenticationProcess(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  P2VAR(Dcm_AuthenticationContextType, AUTOMATIC, DCM_VAR) AuthenticationContext
);

/** \brief Performs the proof of ownership client verification
 **
 ** This function verifies the signature of the proof of ownership token with the
 ** public key from the received certificate. If the ownership is proven, the
 ** authentication state of the connection is set to AUTHENTICATED and access to
 ** diagnostic objects is granted according to the roles provided with the certificate.
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 ** \param[in]    ProofOfOwnershipClient         Structure that holds all input data
 ** \param[out]   ErrorCode                      Pointer to the memory location where the
 **                                              NRC value shall be stored, if the result
 **                                              is E_NOT_OK.
 **
 ** \return  Result of the proof of ownership request
 ** \retval E_OK           Request completed
 ** \retval E_NOT_OK       Request failed, NRC is updated in ProofOfOwnershipContext
 ** \retval DCM_E_BUSY     Request failed, crypto stack is still busy
 ** \retval DCM_E_PENDING  Request is in progress, function needs to be called again
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Asynchronous}
 */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_AuthenticationHandler_ProofOfOwnership(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  Dcm_AuthenticationProofOfOwnershipType ProofOfOwnershipClient,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode
);

/** \brief Callback function to provide the result of the asynchronous operation
 **
 ** This function is called by Dcm_CryptoStackFacade to provide the result of a
 ** Crypto Stack operation as Dcm NRC value. The NRC DCM_E_POSITIVERESPONSE
 ** indicates a successful completion of the Crypto Stack operation.
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 ** \param[in]    ErrorCode                      Result (NRC) of the asynchronous operation.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, DCM_CODE) Dcm_AuthenticationHandler_CryptoOperationDone(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  uint16 GeneratedLength,
  Dcm_NegativeResponseCodeType ErrorCode
);

/** \brief Function to set flag Dcm_AuthenticationHandler_ResetAuthentication
 **
 ** This function is called from context of ResetAuthentication() api,i.e. from any context.
 ** It sets the flag of AuthenticationConnection in order to delay execution of required action
 ** to the next MF cycle.
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
FUNC(void, DCM_CODE) Dcm_AuthenticationHandler_ResetAuthenticationCalledSetFlag(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex
);

#if (DCM_AUTHENTICATION_IDLECONNECTIONTIMER == STD_ON)
/** \brief Function to start IdleConnectionTimer
 **
 ** This function starts the IdleConnectionTimer of a connection if it is in DCM_AUTHENTICATED state.
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection
 **                                              on which IdleConnectionTimer shall be started.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, DCM_CODE) Dcm_AuthenticationHandler_IdleConnectionTimerStart(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex
);

/** \brief Function to stop IdleConnectionTimer
 **
 ** This function stops IdleConnectionTimer of a connection.
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection
 **                                              on which IdleConnectionTimer shall be stopped.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, DCM_CODE) Dcm_AuthenticationHandler_IdleConnectionTimerStop(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex
);

/** \brief Function to start IdleConnectionTimer
 **
 ** This function have to be called within a critical section.
 ** It starts IdleConnectionTimer if the connection is in DCM_AUTHENTICATED state.
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection
 **                                              on which IdleConnectionTimer shall be started.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, DCM_CODE) Dcm_AuthenticationHandler_ChangeToIdleConnectionTimer(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex
);

/** \brief Function to stop IdleConnectionTimer
 **
 ** This function have to be called within a critical section.
 ** It stops IdleConnectionTimer.
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection
 **                                              on which IdleConnectionTimer shall be stopped.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, DCM_CODE) Dcm_AuthenticationHandler_IdleConnectionTimerStopOnFallback(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex
);
#endif /* #if (DCM_AUTHENTICATION_IDLECONNECTIONTIMER == STD_ON) */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif /* #if (DCM_AUTHENTICATION_CONNECTION == STD_ON) */


#endif /* if !defined(DCM_AUTHENTICATION_AUTHENTICATIONHANDLER_H) */
/*==================[end of file]=================================================================*/
