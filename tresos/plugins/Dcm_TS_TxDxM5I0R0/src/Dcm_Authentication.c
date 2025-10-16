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

/* !LINKSTO Dcm.Dsn.File.AuthenticationCore.Impl,1 */
/* This file contains the implementation of the AuthenticationCore SW unit. */

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

#include <Dcm_Authentication.h>
#include <Dcm_Authentication_DiagnosticPolicyHandler.h>
#include <Dcm_Authentication_AuthenticationHandler.h>
#include <Dcm_Authentication_CryptoStackFacade.h>

#include <Std_Types.h>                                   /* AUTOSAR standard types */
#include <TSAutosar.h>
#include <TSMem.h>
#if (DCM_AUTHENTICATION_CONNECTION == STD_ON)
#include <Dcm.h>
#endif
#include <Dcm_Int.h>                                     /* Module intenal definitions */
#include <Dcm_Trace.h>
#include <Dcm_Dsl_CommunicationServices_RxConnections.h> /* Typedef for Dcm_MainConnectionIndexType*/

#if (DCM_INCLUDE_RTE == STD_ON)
#include <Rte_Dcm.h>                                     /* Dcm_SetDeauthenticateRole() and Dcm_ResetAuthentication() prototype */
#endif

#if (DCM_AUTHENTICATION_CONNECTION == STD_ON)

/*==================[macro definitions]==========================================================*/

/*==================[type declarations]==========================================================*/

/*==================[internal function declarations]=============================================*/

/*==================[internal constants]=========================================================*/

/*==================[internal data]==============================================================*/

/*==================[external constants]=========================================================*/

/*==================[external data]==============================================================*/

/*==================[external function definitions]==============================================*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/* !LINKSTO Dcm.Dsn.IB.Authentication.Init,1 */
FUNC(void, DCM_CODE) Dcm_Authentication_Init(void)
{
  DBG_DCM_AUTHENTICATION_INIT_ENTRY();

  Dcm_DiagnosticPolicyHandler_Init();
  Dcm_AuthenticationHandler_Init();
  Dcm_CryptoStackFacade_Init();

  DBG_DCM_AUTHENTICATION_INIT_EXIT();
}

/* !LINKSTO Dcm.EB.AuthenticationStateHandling.SetDeauthenticatedRole.API,1 */
/* !LINKSTO Dcm.Dsn.IB.Authentication.SetDeauthenticatedRole,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_SetDeauthenticatedRole(
  uint16 connectionId,
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) deauthenticatedRole
)
{
  Std_ReturnType Result = E_OK;
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex = DCM_NUM_MAIN_CONNECTIONS;
  boolean MainConnectionWithConnectionIdFound = FALSE;
  Dcm_MainConnectionIndexType Index = 0U;

  DBG_DCM_SETDEAUTHENTICATEDROLE_ENTRY(connectionId, deauthenticatedRole);

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized != TRUE)
  {
    /* !LINKSTO Dcm.EB.AuthenticationStateHandling.SetDeauthenticatedRoleAPI.DcmNotInitialized.DcmDevErrorDetectTrue.ReportDETError,1 */
    DCM_DET_REPORT_ERROR(DCM_SVCID_SETDEAUTHENTICATEDROLE, DCM_E_UNINIT);
  }
  else
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Check if there is any DcmDslMainConnection with required connectionId */
    /* Deviation TASKING-1 */
    for (Index = 0U; Index < DCM_NUM_MAIN_CONNECTIONS; Index++)
    {
      if (Dcm_MainConnectionConfig[Index].ConnectionId == connectionId)
      {
        AuthenticationConnectionIndex = Dcm_MainConnectionConfig[Index].AuthenticatedIndex;
        MainConnectionWithConnectionIdFound = TRUE;
        break;
      }
    }

    if (MainConnectionWithConnectionIdFound == TRUE)
    {
      /* Check if MainConnection has reference in AuthenticationConnectionContainer */
      if (AuthenticationConnectionIndex != DCM_NUM_AUTHENTICATION_CONNECTIONS)
      {
        /* Check parameter deauthenticatedRole */
        if (deauthenticatedRole != NULL_PTR)
        {
          /* !LINKSTO Dcm.EB.AuthenticationStateHandling.Authenticated.SetDeauthenticatedRoleAPI.ReturnsOK,1 */
          /* !LINKSTO Dcm.EB.AuthenticationStateHandling.Deauthenticated.ConfiguredDeauthenticatedRole.SetDeauthenticatedRoleAPI.ReturnsOK.NewCurrentRole.ProvidedDeauthenticatedRole,1 */
          (void)Dcm_DiagnosticPolicyHandler_SetDeauthenticatedRole(AuthenticationConnectionIndex, deauthenticatedRole);
        }
#if (DCM_DEV_ERROR_DETECT == STD_ON)
        else
        {
          /* !LINKSTO Dcm.EB.AuthenticationStateHandling.SetDeauthenticatedRoleAPI.NoDeauthenticatedRole.DcmDevErrorDetectTrue.ReportDETError,1 */
          DCM_DET_REPORT_ERROR(DCM_SVCID_SETDEAUTHENTICATEDROLE, DCM_E_PARAM_POINTER);
        }
      }
      else
      {
        /* !LINKSTO Dcm.EB.AuthenticationStateHandling.SetDeauthenticatedRoleAPI.ConnectionIdNotReferenced.DcmDevErrorDetectTrue.ReportDETError,1 */
        DCM_DET_REPORT_ERROR(DCM_SVCID_SETDEAUTHENTICATEDROLE, DCM_E_PARAM);
      }
    }
    else
    {
      /* !LINKSTO Dcm.EB.AuthenticationStateHandling.SetDeauthenticatedRoleAPI.ConnectionIdNotConfigured.DcmDevErrorDetectTrue.ReportDETError,1 */
      DCM_DET_REPORT_ERROR(DCM_SVCID_SETDEAUTHENTICATEDROLE, DCM_E_PARAM);
    }
#else /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
      }
    }
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
  }

  DBG_DCM_SETDEAUTHENTICATEDROLE_EXIT(Result, connectionId, deauthenticatedRole);
  return Result;
}

/* !LINKSTO Dcm.EB.AuthenticationStateHandling.ResetAuthentication.API,1 */
/* !LINKSTO Dcm.Dsn.IB.Authentication.ResetAuthentication,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_ResetAuthentication(
  uint16 connectionId
)
{
  Std_ReturnType Result = E_OK;
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex = DCM_NUM_MAIN_CONNECTIONS;
  boolean MainConnectionWithConnectionIdFound = FALSE;
  Dcm_MainConnectionIndexType MainConnectionIndex;

  DBG_DCM_RESETAUTHENTICATION_ENTRY(connectionId);

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized != TRUE)
  {
    /* !LINKSTO Dcm.EB.AuthenticationStateHandling.ResetAuthenticationAPI.DcmNotInitialized.DcmDevErrorDetectTrue.ReportDETError,1 */
    DCM_DET_REPORT_ERROR(DCM_SVCID_RESETAUTHENTICATION, DCM_E_UNINIT);
  }
  else
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Check if there is any DcmDslMainConnection with required connectionId */
    /* Deviation TASKING-1 */
    for (MainConnectionIndex = 0U; MainConnectionIndex < DCM_NUM_MAIN_CONNECTIONS; MainConnectionIndex++)
    {
      if (Dcm_MainConnectionConfig[MainConnectionIndex].ConnectionId == connectionId)
      {
        AuthenticationConnectionIndex = Dcm_MainConnectionConfig[MainConnectionIndex].AuthenticatedIndex;
        MainConnectionWithConnectionIdFound = TRUE;
        break;
      }
    }

    if (MainConnectionWithConnectionIdFound == TRUE)
    {
      /* Check if MainConnection has reference in AuthenticationConnection container */
      if (AuthenticationConnectionIndex != DCM_NUM_AUTHENTICATION_CONNECTIONS)
      {
        /* !LINKSTO Dcm.EB.AuthenticationStateHandling.Authenticated.ResetAuthenticationAPI.ReturnsOK.TransitionToDeauthenticated,1 */
        /* !LINKSTO Dcm.EB.AuthenticationStateHandling.Authenticated.ResetAuthenticationAPI.ReturnsOK.NewCurrentRole.ConfiguredDeauthenticatedRole,1 */
        /* !LINKSTO Dcm.EB.AuthenticationStateHandling.Deauthenticated.ResetAuthenticationAPI.ReturnsOK.TransitionToDeauthenticated,1 */
        /* !LINKSTO Dcm.EB.AuthenticationStateHandling.Deauthenticated.ProvidedDeauthenticatedRole.ResetAuthenticationAPI.ReturnsOK.NewCurrentRole.ConfiguredDeauthenticatedRole,1 */
        /* There is no errors, set the flag. Execution is delayed to the next MF cycle. */
        (void)Dcm_AuthenticationHandler_ResetAuthenticationCalledSetFlag(AuthenticationConnectionIndex);
      }
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      else
      {
        /* !LINKSTO Dcm.EB.AuthenticationStateHandling.ResetAuthenticationAPI.ConnectionIdNotReferenced.DcmDevErrorDetectTrue.ReportDETError,1 */
        DCM_DET_REPORT_ERROR(DCM_SVCID_RESETAUTHENTICATION, DCM_E_PARAM);
      }
    }
    else
    {
      /* !LINKSTO Dcm.EB.AuthenticationStateHandling.ResetAuthenticationAPI.ConnectionIdNotConfigured.DcmDevErrorDetectTrue.ReportDETError,1 */
      DCM_DET_REPORT_ERROR(DCM_SVCID_RESETAUTHENTICATION, DCM_E_PARAM);
    }
#else  /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
    }
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
  }

  DBG_DCM_RESETAUTHENTICATION_EXIT(Result, connectionId);
  return Result;
}

/* !LINKSTO Dcm.Dsn.IB.Authentication.ResetOnTimeout,1 */
FUNC(void, DCM_CODE) Dcm_Authentication_ResetOnTimeout(
  Dcm_MainConnectionIndexType MainConnectionIndex
)
{
  DBG_DCM_AUTHENTICATION_RESETONTIMEOUT_ENTRY(MainConnectionIndex);

  DCM_PRECONDITION_ASSERT((MainConnectionIndex < DCM_NUM_MAIN_CONNECTIONS),
                           DCM_INTERNAL_API_ID);

  if(DCM_NUM_AUTHENTICATION_CONNECTIONS > Dcm_MainConnectionConfig[MainConnectionIndex].AuthenticatedIndex)
  {
    Dcm_DiagnosticPolicyHandler_ResetAuthentication(Dcm_MainConnectionConfig[MainConnectionIndex].AuthenticatedIndex,
                                                    FALSE);
  }

  DBG_DCM_AUTHENTICATION_RESETONTIMEOUT_EXIT(MainConnectionIndex);
}

#if (DCM_AUTHENTICATIONSTATE_MODESWITCH_SUPPORT == STD_ON)
/* !LINKSTO Dcm.Dsn.IB.Authentication.NotifyAuthenticationStateChange,1 */
FUNC(void, DCM_CODE) Dcm_Authentication_NotifyAuthenticationStateChange(
  Dcm_AuthenticationConnectionIndexType AuthenticationConnectionIndex,
  Dcm_AuthenticationStateType AuthenticationState
)
{
  DBG_DCM_AUTHENTICATION_NOTIFYAUTHENTICATIONSTATECHANGE_ENTRY(ConnectionId, AuthenticationState);

  DCM_PRECONDITION_ASSERT((AuthenticationConnectionIndex < DCM_NUM_AUTHENTICATION_CONNECTIONS),
                           DCM_INTERNAL_API_ID);

  (void)Dcm_AuthenticationConfigPtr->AuthenticationConnection[AuthenticationConnectionIndex].AuthenticationSchMSwitch(AuthenticationState);
#if (DCM_INCLUDE_RTE == STD_ON)
  /* !LINKSTO Dcm.EB.AuthenticationStateHandling.Authenticated.ResetAuthenticationAPI.ReturnsOK.TransitionToDeauthenticated.RteModeSwitch,1
     !LINKSTO Dcm.EB.AuthenticationStateHandling.Deauthenticated.ResetAuthenticationAPI.ReturnsOK.TransitionToDeauthenticated.RteModeSwitch,1
     !LINKSTO Dcm.EB.AuthenticationStateHandling.Authenticated.S3ServerTimeout.TransitionToDeauthenticated.RteModeSwitch,1
     !LINKSTO Dcm.EB.AuthenticationStateHandling.AuthenticationServiceRequest.DeAuthenticate.Authenticated.TransitionToDeauthenticated.RteModeSwitch,1
     !LINKSTO Dcm.EB.AuthenticationStateHandling.AuthenticationServiceRequest.DeAuthenticate.Deauthenticated.TransitionToDeauthenticated.RteModeSwitch,1
     !LINKSTO Dcm.EB.AuthenticationStateHandling.AuthenticationServiceRequest.ProofOfOwnership.Deauthenticated.TransitionToAuthenticated.RteModeSwitch,1
     !LINKSTO Dcm.EB.AuthenticationStateHandling.AuthenticationServiceRequest.ProofOfOwnership.Authenticated.TransitionToAuthenticated.RteModeSwitch,1 */
  (void)Dcm_AuthenticationConfigPtr->AuthenticationConnection[AuthenticationConnectionIndex].AuthenticationRteSwitch(AuthenticationState);
#endif /* (DCM_INCLUDE_RTE == STD_ON) */

  DBG_DCM_AUTHENTICATION_NOTIFYAUTHENTICATIONSTATECHANGE_EXIT(ConnectionId, AuthenticationState);
}
#endif /*#if (DCM_AUTHENTICATIONSTATE_MODESWITCH_SUPPORT == STD_ON) */

#if (DCM_AUTHENTICATION_IDLECONNECTIONTIMER == STD_ON)
/* !LINKSTO Dcm.Dsn.IB.Authentication.GetAuthenticationConnectionIndex,1 */
FUNC(Dcm_AuthenticationConnectionIndexType, DCM_CODE) Dcm_Authentication_GetAuthenticationConnectionIndex(
  Dcm_MainConnectionIndexType MainConnectionIndex
)
{
  Dcm_AuthenticationConnectionIndexType ReturnAuthenticationConnectionIndex = DCM_NUM_MAIN_CONNECTIONS;

  DBG_DCM_AUTHENTICATION_GETAUTHENTICATIONCONNECTIONINDEX_ENTRY(MainConnectionIndex);

  /* Check if MainConnection index is different than DCM_INVALID_MAINCONNECTION_INDEX.
     Check if connection is an authentication connection, i.e. connection is referenced
     in Authentication configuration table for connections. */
  if((MainConnectionIndex != DCM_INVALID_MAINCONNECTION_INDEX) &&
     (DCM_NUM_AUTHENTICATION_CONNECTIONS > Dcm_MainConnectionConfig[MainConnectionIndex].AuthenticatedIndex))
  {
    ReturnAuthenticationConnectionIndex = Dcm_MainConnectionConfig[MainConnectionIndex].AuthenticatedIndex;
  }

  DBG_DCM_AUTHENTICATION_GETAUTHENTICATIONCONNECTIONINDEX_EXIT(ReturnAuthenticationConnectionIndex);

  return ReturnAuthenticationConnectionIndex;
}
#endif /* #if (DCM_AUTHENTICATION_IDLECONNECTIONTIMER == STD_ON) */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*==================[internal function definitions]==============================================*/

#endif /* #if (DCM_AUTHENTICATION_CONNECTION == STD_ON) */

/*==================[end of file]================================================================*/
