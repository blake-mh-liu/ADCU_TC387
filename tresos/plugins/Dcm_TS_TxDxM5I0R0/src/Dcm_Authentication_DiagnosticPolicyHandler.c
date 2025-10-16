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

/* !LINKSTO Dcm.Dsn.File.DiagnosticPolicyHandler.Impl,1 */
/* This file contains the implementation of the DiagnosticPolicyHandler SW unit. */

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * This warnings is a false positive.
 * The compiler optimizes the 'for' loop (which has only 1 iteration) in the following way
 * - it prepares in advance the index for the next iteration
 * - if the index is equal to '0' it goes back to check the 'for' loop conditions, otherwise it just moves on
 * - since the index is already equal to '1', it never jumps back to check the exit condition
 */

/*==================[includes]===================================================================*/

#include <Dcm_Authentication_DiagnosticPolicyHandler.h>
#include <Dcm_Authentication.h>

#include <Std_Types.h> /* AUTOSAR standard types */
#include <TSAutosar.h>
#include <TSMem.h>
#include <SchM_Dcm.h>  /* SchM interface for Dcm */
#include <Dcm_Trace.h>
#include <Dcm_Int.h>   /* Includes definition of DCM_INTERNAL_API_ID */

#if (DCM_AUTHENTICATION_CONNECTION == STD_ON)

/*==================[macro definitions]==========================================================*/

/*==================[type declarations]==========================================================*/

/*==================[internal function declarations]=============================================*/

/*==================[internal constants]=========================================================*/

/*==================[internal data]==============================================================*/

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dcm_MemMap.h>
/* !LINKSTO Dcm.EB.AuthenticationStateHandling.AuthenticationState.PerDcmDslMainConnection,1 */
/* !LINKSTO Dcm.Dsn.SM.AuthenticationState,1 */
STATIC VAR(Dcm_AuthenticationStateType, DCM_VAR) Dcm_AuthenticationState[DCM_NUM_AUTHENTICATION_CONNECTIONS];
STATIC VAR(Dcm_AccessControlDataType, DCM_VAR) Dcm_AccessControlData[DCM_NUM_AUTHENTICATION_CONNECTIONS];

#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dcm_MemMap.h>

/*==================[external constants]=========================================================*/

/*==================[external data]==============================================================*/

/*==================[external function definitions]==============================================*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/* !LINKSTO Dcm.Dsn.IB.DiagnosticPolicyHandler.Init,1 */
FUNC(void, DCM_CODE) Dcm_DiagnosticPolicyHandler_Init(void)
{
  uint16_least AuthenticationConnectionIndex;

  DBG_DCM_DIAGNOSTICPOLICYHANDLER_INIT_ENTRY();

  /* Deviation TASKING-1 <+2> */
  for (AuthenticationConnectionIndex = 0U;
       AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS;
       AuthenticationConnectionIndex++)
  {
    /* !LINKSTO Dcm.EB.AuthenticationStateHandling.Init.Deauthenticated,1 */
    Dcm_AuthenticationState[AuthenticationConnectionIndex] = DCM_DEAUTHENTICATED;

    /* !LINKSTO Dcm.EB.AuthenticationStateHandling.Init.CurrentRole.ConfiguredDeauthenticatedRole,1 */
    TS_MemCpy(Dcm_AccessControlData[AuthenticationConnectionIndex].AuthenticationRole,
              Dcm_AuthenticationConfigPtr->DeauthenticatedRole,
              DCM_DSP_AUTHENTICATION_ROLE_SIZE);
  }
  DBG_DCM_DIAGNOSTICPOLICYHANDLER_INIT_EXIT();
}

/* !LINKSTO Dcm.Dsn.IB.DiagnosticPolicyHandler.ResetAuthentication,1 */
FUNC(void, DCM_CODE) Dcm_DiagnosticPolicyHandler_ResetAuthentication(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  boolean ChangeRole
)
{
  Dcm_AuthenticationStateType OldAuthenticationState;

  DBG_DCM_DIAGNOSTICPOLICYHANDLER_RESETAUTHENTICATION_ENTRY(AuthenticationConnectionIndex);

  DCM_PRECONDITION_ASSERT((AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS),
                           DCM_INTERNAL_API_ID);

  /* ENTER critical section */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  OldAuthenticationState = Dcm_AuthenticationState[AuthenticationConnectionIndex];

  if ( (ChangeRole == TRUE) ||
       (OldAuthenticationState == DCM_AUTHENTICATED) )
  {

    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.DeAuthenticate.Authenticated.TransitionToDeauthenticated,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.DeAuthenticate.Deauthenticated.TransitionToDeauthenticated,1
       !LINKSTO Dcm.EB.AuthenticationStateHandling.Authenticated.ResetAuthenticationAPI.ReturnsOK.TransitionToDeauthenticated,1
       !LINKSTO Dcm.EB.AuthenticationStateHandling.Deauthenticated.ResetAuthenticationAPI.ReturnsOK.TransitionToDeauthenticated,1
       !LINKSTO Dcm.EB.AuthenticationStateHandling.Authenticated.S3ServerTimeout.TransitionToDeauthenticated,1 */
    Dcm_AuthenticationState[AuthenticationConnectionIndex] = DCM_DEAUTHENTICATED;

#if (DCM_AUTHENTICATION_IDLECONNECTIONTIMER == STD_ON)
    /* !LINKSTO Dcm.EB.AuthenticationStateHandling.Authenticated.DefaultSession.ResetAuthenticationAPI.ReturnsOK.StopIdleConnectionTimer,1 */
    /* !LINKSTO Dcm.EB.AuthenticationStateHandling.Authenticated.NonDefaultSession.ResetAuthenticationAPI.ReturnsOK.StopIdleConnectionTimer,1 */
    (void)Dcm_AuthenticationHandler_IdleConnectionTimerStop(AuthenticationConnectionIndex);
#endif /* #if (DCM_AUTHENTICATION_IDLECONNECTIONTIMER == STD_ON) */

    /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.DeAuthenticate.Authenticated.TransitionToDeauthenticated.NewCurrentRole.ConfiguredDeauthenticatedRole,1
       !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.DeAuthenticate.DeAuthenticated.ProvidedDeauthenticatedRole.TransitionToDeauthenticated.NewCurrentRole.ConfiguredDeauthenticatedRole,1
       !LINKSTO Dcm.EB.AuthenticationStateHandling.Authenticated.ResetAuthenticationAPI.ReturnsOK.NewCurrentRole.ConfiguredDeauthenticatedRole,1
       !LINKSTO Dcm.EB.AuthenticationStateHandling.Deauthenticated.ProvidedDeauthenticatedRole.ResetAuthenticationAPI.ReturnsOK.NewCurrentRole.ConfiguredDeauthenticatedRole,1
       !LINKSTO Dcm.EB.AuthenticationStateHandling.Authenticated.S3ServerTimeout.NewCurrentRole.ConfiguredDeauthenticatedRole,1 */
    TS_MemCpy(Dcm_AccessControlData[AuthenticationConnectionIndex].AuthenticationRole,
              Dcm_AuthenticationConfigPtr->DeauthenticatedRole,
              DCM_DSP_AUTHENTICATION_ROLE_SIZE);
  }

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

#if (DCM_AUTHENTICATIONSTATE_MODESWITCH_SUPPORT == STD_ON)
  if ( (ChangeRole == TRUE) ||
       (OldAuthenticationState == DCM_AUTHENTICATED) )
  {
    /* Invoke mode switch on every transition */
    /* !LINKSTO Dcm.EB.AuthenticationStateHandling.Authenticated.ResetAuthenticationAPI.ReturnsOK.TransitionToDeauthenticated.RteModeSwitch,1
       !LINKSTO Dcm.EB.AuthenticationStateHandling.Deauthenticated.ResetAuthenticationAPI.ReturnsOK.TransitionToDeauthenticated.RteModeSwitch,1
       !LINKSTO Dcm.EB.AuthenticationStateHandling.Authenticated.S3ServerTimeout.TransitionToDeauthenticated.RteModeSwitch,1
       !LINKSTO Dcm.EB.AuthenticationStateHandling.AuthenticationServiceRequest.DeAuthenticate.Authenticated.TransitionToDeauthenticated.RteModeSwitch,1
       !LINKSTO Dcm.EB.AuthenticationStateHandling.AuthenticationServiceRequest.DeAuthenticate.Deauthenticated.TransitionToDeauthenticated.RteModeSwitch,1 */
    Dcm_Authentication_NotifyAuthenticationStateChange(AuthenticationConnectionIndex, DCM_DEAUTHENTICATED);
  }
#endif /* (DCM_AUTHENTICATIONSTATE_MODESWITCH_SUPPORT == STD_ON) */

  DBG_DCM_DIAGNOSTICPOLICYHANDLER_RESETAUTHENTICATION_EXIT(AuthenticationConnectionIndex);
}

/* !LINKSTO Dcm.Dsn.IB.DiagnosticPolicyHandler.SetAuthentication,1 */
FUNC(void, DCM_CODE) Dcm_DiagnosticPolicyHandler_SetAuthentication(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  P2CONST(uint8, AUTOMATIC, DCM_VAR) AuthenticationRole
)
{
  DBG_DCM_DIAGNOSTICPOLICYHANDLER_SETAUTHENTICATION_ENTRY(AuthenticationConnectionIndex, AuthenticationRole);

  DCM_PRECONDITION_ASSERT((AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS),
                           DCM_INTERNAL_API_ID);

  /* ENTER critical section */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.KeyMCertElementGet.ReturnsOK.ValidRoleSize.Deauthenticated.ConfiguredDeauthenticatedRole.SetNewRole,1
     !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.KeyMCertElementGet.ReturnsOK.ValidRoleSize.Deauthenticated.ProvidedDeauthenticatedRole.SetNewRole,1
     !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.KeyMCertElementGet.ReturnsOK.ValidRoleSize.Authenticated.SetNewRole,1 */
  TS_MemCpy(Dcm_AccessControlData[AuthenticationConnectionIndex].AuthenticationRole,
            AuthenticationRole,
            DCM_DSP_AUTHENTICATION_ROLE_SIZE);

  /* !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.Deauthenticated.TransitionToAuthenticated,1
     !LINKSTO Dcm.EB.UDSServices.AuthenticationServiceRequest.ProofOfOwnership.Authenticated.TransitionToAuthenticated,1 */
  Dcm_AuthenticationState[AuthenticationConnectionIndex] = DCM_AUTHENTICATED;

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

#if (DCM_AUTHENTICATIONSTATE_MODESWITCH_SUPPORT == STD_ON)
   /* !LINKSTO Dcm.EB.AuthenticationStateHandling.AuthenticationServiceRequest.ProofOfOwnership.Deauthenticated.TransitionToAuthenticated.RteModeSwitch,1
      !LINKSTO Dcm.EB.AuthenticationStateHandling.AuthenticationServiceRequest.ProofOfOwnership.Authenticated.TransitionToAuthenticated.RteModeSwitch,1 */
  Dcm_Authentication_NotifyAuthenticationStateChange(AuthenticationConnectionIndex, DCM_AUTHENTICATED);
#endif /* (DCM_AUTHENTICATIONSTATE_MODESWITCH_SUPPORT == STD_ON) */

  DBG_DCM_DIAGNOSTICPOLICYHANDLER_SETAUTHENTICATION_EXIT(AuthenticationConnectionIndex, AuthenticationRole);
}

/* !LINKSTO Dcm.Dsn.IB.DiagnosticPolicyHandler.SetDeauthenticatedRole,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DiagnosticPolicyHandler_SetDeauthenticatedRole(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) DeauthenticatedRole
)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DCM_DIAGNOSTICPOLICYHANDLER_SETDEAUTHENTICATEDROLE_ENTRY(AuthenticationConnectionIndex, DeauthenticatedRole);

  DCM_PRECONDITION_ASSERT((AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS),
                           DCM_INTERNAL_API_ID);

  /* ENTER critical section */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  if (Dcm_AuthenticationState[AuthenticationConnectionIndex] == DCM_DEAUTHENTICATED)
  {
    /* !LINKSTO Dcm.EB.AuthenticationStateHandling.Deauthenticated.ProvidedDeauthenticatedRole.SetDeauthenticatedRoleAPI.ReturnsOK.NewCurrentRole.ProvidedDeauthenticatedRole,1 */
    /* !LINKSTO Dcm.EB.AuthenticationStateHandling.Deauthenticated.ConfiguredDeauthenticatedRole.SetDeauthenticatedRoleAPI.ReturnsOK.NewCurrentRole.ProvidedDeauthenticatedRole,1 */
    TS_MemCpy(Dcm_AccessControlData[AuthenticationConnectionIndex].AuthenticationRole,
              DeauthenticatedRole,
              DCM_DSP_AUTHENTICATION_ROLE_SIZE);
    Result = E_OK;
  }
  else
  {
    /* !LINKSTO Dcm.EB.AuthenticationStateHandling.Authenticated.SetDeauthenticatedRoleAPI.ReturnsOK,1 */
    /* Do nothing */
  }

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  DBG_DCM_DIAGNOSTICPOLICYHANDLER_SETDEAUTHENTICATEDROLE_EXIT(Result, AuthenticationConnectionIndex, DeauthenticatedRole);
  return Result;
}

/* !LINKSTO Dcm.Dsn.IB.DiagnosticPolicyHandler.CheckAuthentication,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DiagnosticPolicyHandler_CheckAuthentication(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  P2CONST(uint8, AUTOMATIC, DCM_VAR) AuthenticationRole
)
{
  Std_ReturnType Result = E_NOT_OK;
  uint8 RoleIndex = 0U;

  DBG_DCM_DIAGNOSTICPOLICYHANDLER_CHECKAUTHENTICATION_ENTRY(AuthenticationConnectionIndex, AuthenticationRole);

  DCM_PRECONDITION_ASSERT((AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS),
                           DCM_INTERNAL_API_ID);

  /* Deviation TASKING-1 */
  for (RoleIndex = 0U; RoleIndex < DCM_DSP_AUTHENTICATION_ROLE_SIZE; ++RoleIndex)
  {
    if ((Dcm_AccessControlData[AuthenticationConnectionIndex].AuthenticationRole[RoleIndex] & AuthenticationRole[RoleIndex]) != 0U)
    {
      Result = E_OK;
      break;
    }
  }

  DBG_DCM_DIAGNOSTICPOLICYHANDLER_CHECKAUTHENTICATION_EXIT(Result, AuthenticationConnectionIndex, AuthenticationRole);
  return Result;
}

#if (DCM_AUTHENTICATION_IDLECONNECTIONTIMER == STD_ON)
/* This function needs to be called inside critical section */
/* !LINKSTO Dcm.Dsn.IB.DiagnosticPolicyHandler.GetAuthenticationState,1 */
FUNC(Dcm_AuthenticationStateType, DCM_CODE) Dcm_DiagnosticPolicyHandler_GetAuthenticationState(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex
)
{
  Dcm_AuthenticationStateType ReturnAuthenticationState = DCM_DEAUTHENTICATED;

  DBG_DCM_DIAGNOSTICPOLICYHANDLER_GETAUTHENTICATIONSTATE_ENTRY(AuthenticationConnectionIndex);

  DCM_PRECONDITION_ASSERT((AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS),
                           DCM_INTERNAL_API_ID);

  /* There is no need to protect Dcm_AuthenticationState, since this function is called inside critical session. */
  if (Dcm_AuthenticationState[AuthenticationConnectionIndex] == DCM_AUTHENTICATED)
  {
    ReturnAuthenticationState = DCM_AUTHENTICATED;
  }

  DBG_DCM_DIAGNOSTICPOLICYHANDLER_GETAUTHENTICATIONSTATE_EXIT(AuthenticationConnectionIndex, ReturnAuthenticationState);

  return ReturnAuthenticationState;
}
#endif /* #if (DCM_AUTHENTICATION_IDLECONNECTIONTIMER == STD_ON) */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*==================[internal function definitions]==============================================*/

#endif /* #if (DCM_AUTHENTICATION_CONNECTION == STD_ON) */

/*==================[end of file]================================================================*/
