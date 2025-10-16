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

/* !LINKSTO Dcm.Dsn.File.DiagnosticPolicyHandler.PublicApi,1 */
/* This file contains the public API of the DiagnosticPolicyHandler SW unit. */

#if (!defined DCM_AUTHENTICATION_DIAGNOSTICPOLICYHANDLER_H)
#define DCM_AUTHENTICATION_DIAGNOSTICPOLICYHANDLER_H

/*==================[inclusions]==================================================================*/

#include <Std_Types.h>                                /* AUTOSAR standard types */
#include <Dcm_Types.h>
#include <Dcm_Authentication_Cfg.h>
#include <Dcm_Authentication_AuthenticationHandler.h> /* Includes type definition Dcm_AuthenticationConnectionIndexType */

#if (DCM_AUTHENTICATION_CONNECTION == STD_ON)

/*==================[macro definitions]==========================================================*/

/*==================[type declarations]===========================================================*/

/* !LINKSTO Dcm.Dsn.Type.Dcm_AccessControlDataType,1 */
/** \brief Data structure that contains the data for performing the authentication check. **/
typedef struct
{
  /** \brief Role to be used for authentication checks. **/
  uint8 AuthenticationRole[DCM_DSP_AUTHENTICATION_ROLE_SIZE];
  /* whitelist data not yet supported */
} Dcm_AccessControlDataType;

/*==================[external constant declarations]==============================================*/

/*==================[external data declarations]==================================================*/

/*==================[external function declarations]==============================================*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/** \brief Initializes the Dcm_DiagnosticPolicyHandler for UDS service 0x29
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, DCM_CODE) Dcm_DiagnosticPolicyHandler_Init(void);

/** \brief Reset the current authentication state for the connection to DEAUTHENTICATED.
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection to be reset.
 ** \param[in]    ChangeRole                     Identifies if the authentication role shall be changed.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, DCM_CODE) Dcm_DiagnosticPolicyHandler_ResetAuthentication(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  boolean ChangeRole
);

/** \brief Sets the current authentication state for the connection
 **
 ** This function sets the current authentication state for the connection to
 ** AUTHENTICATED and grants access to diagnostic services according to the role
 ** certificate element.
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 ** \param[in]    AccessControlData              Pointer to certificate data elements (role, whitelists).
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, DCM_CODE) Dcm_DiagnosticPolicyHandler_SetAuthentication(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  P2CONST(uint8, AUTOMATIC, DCM_VAR) AuthenticationRole
);

/** \brief Sets the deauthenticated role for the connection
 **
 ** This function sets a new role used in deauthenticated state for that connection.
 ** The set role is valid until the connection switches into authenticated state or the
 ** ECU is reset.
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 ** \param[in]    DeauthenticatedRole            The new deauthenticated role for the connection.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DiagnosticPolicyHandler_SetDeauthenticatedRole(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) DeauthenticatedRole
);

/** \brief Checks the permission for accessing data and/or diagnostic services
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 ** \param[in]    AuthenticationRole             Role to be checked for permission.
 **
 ** \return  Access permission
 ** \retval E_OK       Access permitted
 ** \retval E_NOT_OK   Access not permitted
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DiagnosticPolicyHandler_CheckAuthentication(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  P2CONST(uint8, AUTOMATIC, DCM_VAR) AuthenticationRole
);

#if (DCM_AUTHENTICATION_IDLECONNECTIONTIMER == STD_ON)
/** \brief Returns authentication state of an AuthenticationConnection
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 **
 ** \return  Authentication state
 ** \retval DCM_DEAUTHENTICATED    Connection is in the deauthenticated state
 ** \retval DCM_AUTHENTICATED      Connection is in the authenticated state
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
/* This function needs to be called inside critical section */
extern FUNC(Dcm_AuthenticationStateType, DCM_CODE) Dcm_DiagnosticPolicyHandler_GetAuthenticationState(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex
);
#endif /* #if (DCM_AUTHENTICATION_IDLECONNECTIONTIMER == STD_ON) */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif /* #if (DCM_AUTHENTICATION_CONNECTION == STD_ON) */

#endif /* if !defined(DCM_AUTHENTICATION_DIAGNOSTICPOLICYHANDLER_H) */
/*==================[end of file]=================================================================*/
