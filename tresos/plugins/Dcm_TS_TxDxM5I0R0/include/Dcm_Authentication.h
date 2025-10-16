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

/* !LINKSTO Dcm.Dsn.File.AuthenticationCore.PublicApi,1 */
/* This file contains the public API of the AuthenticationCore SW unit. */

#if (!defined DCM_AUTHENTICATION_H)
#define DCM_AUTHENTICATION_H

/*==================[inclusions]==================================================================*/

#include <Std_Types.h>                                   /* AUTOSAR standard types */
#include <Dcm_Types.h>
#include <Dcm_Authentication_Cfg.h>
#include <Dcm_Dsl_CommunicationServices_RxConnections.h> /* Typedef for Dcm_MainConnectionIndexType */
#include <Dcm_Authentication_AuthenticationHandler.h>    /* Includes type definition Dcm_AuthenticationConnectionIndexType */

#if (DCM_AUTHENTICATION_CONNECTION == STD_ON)

/*==================[macro definitions]===========================================================*/

/*==================[type declarations]===========================================================*/

/*==================[external constant declarations]==============================================*/

/*==================[external data declarations]==================================================*/

/*==================[external function declarations]==============================================*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/** \brief Initializes the SW-Units for UDS service 0x29
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, DCM_CODE) Dcm_Authentication_Init(void);

/** \brief Notify Authentication unit about S3Timeout
 **
 ** This function informes Authentication unit to reset authentication state and change the role
 ** if needed.
 **
 ** \param[in]    MainConnectionIndex  Identifies the MainConnection on which the S3Timeout occured.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, DCM_CODE) Dcm_Authentication_ResetOnTimeout(
  Dcm_MainConnectionIndexType MainConnectionIndex
);

#if (DCM_AUTHENTICATIONSTATE_MODESWITCH_SUPPORT == STD_ON)
/** \brief Notify authentication state change
 **
 ** This function invokes the switch of the corresponding ModeDeclarationGroup
 ** DcmAuthenticationState with the new authentication state of a connection.
 ** Schm_Switch and Rte_Switch are invoked.
 **
 ** \param[in]    AuthenticationConnectionIndex  Identifies the AuthenticationConnection.
 ** \param[in]    AuthenticationState  New authentication state.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, DCM_CODE) Dcm_Authentication_NotifyAuthenticationStateChange(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  Dcm_AuthenticationStateType AuthenticationState
);
#endif /* #if (DCM_AUTHENTICATIONSTATE_MODESWITCH_SUPPORT == STD_ON) */

#if (DCM_AUTHENTICATION_IDLECONNECTIONTIMER == STD_ON)
/** \brief Checks if MainConnection supports authentication
 **
 ** This function checks if the MainConnection is referenced in
 ** Authentication configuration table for connections.
 **
 ** \param[in]    MainConnectionIndex  Identifies the MainConnection.

 ** \return AuthenticationConnectionIndex Index of AuthenticationConnection if MainConnection
                                          supports authentication, otherwise DCM_NUM_MAIN_CONNECTIONS.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(Dcm_AuthenticationConnectionIndexType, DCM_CODE) Dcm_Authentication_GetAuthenticationConnectionIndex(
  Dcm_MainConnectionIndexType MainConnectionIndex
);
#endif /* #if (DCM_AUTHENTICATION_IDLECONNECTIONTIMER == STD_ON) */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif /* #if (DCM_AUTHENTICATION_CONNECTION == STD_ON) */

#endif /* if !defined(DCM_AUTHENTICATION_H) */
/*==================[end of file]=================================================================*/
