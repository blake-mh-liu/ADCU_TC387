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

/* !LINKSTO Dcm.Dsn.File.ClearDiagInfo.Impl,1 */
/* This file contains the implementation of the Diagnostic Service ClearDiagnosticInformation. */

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 15.2 (required)
 *     "An unconditional break statement shall terminate every non-empty switch clause."
 *
 *     Reason:
 *     The following actions have to be executed in the same state so the break
 *     statement. The fallthrough allows shorter and non-duplicated code.
 *
 */

/* MISRA-C:2012 Deviation List
 *
 *  MISRAC2012-1) Deviated Rule: 16.3 (required)
 *     "An unconditional break statement shall terminate every switch-clause."
 *
 *     Reason:
 *     The following actions have to be executed in the same state so the break
 *     statement is removed in order to have shorter code and avoid duplicated code.
 *
 *  MISRAC2012-2) Deviated Rule: 8.9 (advisory)
 *     "An object should be defined at block scope if its identifier only
 *     appears in a single function."
 *
 *     Reason:
 *     The object is defined in this way because the values that are stored
 *     in them are required for the next call of this function and should be
 *     hold in the data segment memory.
 *
 *  MISRAC2012-3) Deviated Rule: 16.1 (required)
 *     "All switch statements shall be well-formed"
 *
 *     Reason:
 *     This violation is present because rule 16.3 is violated and justified inside the affected
 *     switch statement, as noted under rule 16.1:
 *     some of the restrictions imposed on switch statements by this rule are expounded in the
 *     15.3, 16.2, 16.3, 16.4, 16.5, 16.6 rules, which are violated inside the current switch statement.
 */

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
 *
 */

/* gcc Deviation List
 *
 * GCC-1) Deviated Rule: implicit-fallthrough
 * warning: this statement may fall through [-Wimplicit-fallthrough=]
 *
 * Reason:
 * The following actions have to be executed in the same state so the break
 * statement is removed in order to have shorter code and avoid duplicated code.
 */

/*==================[includes]===================================================================*/

#include <Dcm_Trace.h>
#include <Std_Types.h>                                                 /* AUTOSAR standard types */
#include <TSAutosar.h>
#include <Dcm_Dsp_SvcH_ClearDiagnosticInformation.h>
#include <Dcm_Dsl_Supervisor.h>

/* The functions provided and implemented by this unit are exclusively used for
 * UDS service 0x14 handling. */
#if (DCM_DSP_USE_SERVICE_0X14 == STD_ON)

/*==================[macro definitions]==========================================================*/

#if (DCM_DSP_CLEARDIAGNOSTICINFORMATION_PARALLEL_PROCESSING_ENABLED == STD_ON)

#if (DCM_NUM_PROTOCOL > 1U)
#if (defined DCM_CLEAR_DIAGNOSTIC_INFO_CONTEXT)
  #error "DCM_CLEAR_DIAGNOSTIC_INFO_CONTEXT is already defined"
#endif
#define DCM_CLEAR_DIAGNOSTIC_INFO_CONTEXT(ProtocolIndex) Dcm_ClearDiagnosticInfoContext[(ProtocolIndex)]
#else
#if (defined DCM_CLEAR_DIAGNOSTIC_INFO_CONTEXT)
  #error "DCM_CLEAR_DIAGNOSTIC_INFO_CONTEXT is already defined"
#endif
#define DCM_CLEAR_DIAGNOSTIC_INFO_CONTEXT(ProtocolIndex) Dcm_ClearDiagnosticInfoContext[0U]
#endif /* #if (DCM_NUM_PROTOCOL > 1U) */

#endif /* #if ((DCM_DSP_CLEARDIAGNOSTICINFORMATION_PARALLEL_PROCESSING_ENABLED == STD_ON) */

/*==================[type declarations]==========================================================*/

/*==================[internal function declarations]=============================================*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

#if (DCM_DSP_CLEARDIAGNOSTICINFORMATION_PARALLEL_PROCESSING_ENABLED == STD_ON)

/** \brief Shared resource handling before service processing
 **
 ** \param[in]    ProtocolIdx  Index of the protocol that is processing the service
 ** \param[inout] OpStatus     Status of the service processing before execution
 **
 ** \retval DCM_E_DONE         end processing
 ** \retval DCM_E_PENDING      postpone processing
 ** \retval DCM_E_OK           do processing
 */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ClearDiagnosticInformation_ParallelExecutionPreProcessing(
  Dcm_ProtocolIndexType ProtocolIndex,
  P2VAR(Dcm_OpStatusType, AUTOMATIC, DCM_VAR) OpStatus);

/** \brief Shared resource handling after service processing
 **
 ** \param[in]    ProtocolIdx           Index of the protocol that is processing the service
 ** \param[in]    serviceProcessStatus  Status of the service processing after execution
 */
STATIC FUNC(void, DCM_CODE) Dcm_DspInternal_ClearDiagnosticInformation_ParallelExecutionPostProcessing(
  Dcm_ProtocolIndexType ProtocolIndex,
  Std_ReturnType serviceProcessStatus);

#endif /* #if ((DCM_DSP_CLEARDIAGNOSTICINFORMATION_PARALLEL_PROCESSING_ENABLED == STD_ON) */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*==================[internal constant definitions]==============================================*/

/*==================[internal data definitions]==================================================*/

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dcm_MemMap.h>

#if (DCM_DSP_CLEARDIAGNOSTICINFORMATION_PARALLEL_PROCESSING_ENABLED == STD_ON)

/* Dcm_ClearDiagnosticInfoContext is used to hold information regarding the processing of
 * the service ClearDiagnosticInformation(0x14).
 */
/* Rationale for mapping Dcm_ClearDiagnosticInfoContext to NOINIT section.
 *
 * Members of Dcm_ClearDiagnosticInfoContext are initialized and accessed as described below:
 * DemClientOwner: Initialized in Dcm_DspInternal_ClearDiagnosticInformation_SvcH() before
 *                 being accessed from the same function.
 */
/* Deviation MISRAC2012-2 */
STATIC VAR(Dcm_ClearDiagnosticInfoContextType, DCM_VAR) Dcm_ClearDiagnosticInfoContext[DCM_NUM_PROTOCOL];

#endif /* #if ((DCM_DSP_CLEARDIAGNOSTICINFORMATION_PARALLEL_PROCESSING_ENABLED == STD_ON) */

#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dcm_MemMap.h>

/*==================[external constant definitions]==============================================*/

/*==================[external data definitions]==================================================*/

/*==================[external function definitions]==============================================*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

FUNC(void, DCM_CODE) Dcm_DspInternal_ClearDiagnosticInformation_Init(void)
{
  Dcm_ProtocolIndexType ProtocolIndex;

  DBG_DCM_DSPINTERNAL_CLEARDIAGNOSTICINFORMATION_INIT_ENTRY();

  /* Deviation TASKING-1 */
  for (ProtocolIndex=0U; ProtocolIndex<DCM_NUM_PROTOCOL; ProtocolIndex++)
  {
#if (DCM_DSP_CLEARDIAGNOSTICINFORMATION_PARALLEL_PROCESSING_ENABLED == STD_ON)
    DCM_CLEAR_DIAGNOSTIC_INFO_CONTEXT(ProtocolIndex).DemClientOwner = FALSE;
#endif
  }

  DBG_DCM_DSPINTERNAL_CLEARDIAGNOSTICINFORMATION_INIT_EXIT();
}

/* This is the generic service handler for UDS service 0x14 */
/* !LINKSTO SWS_Dcm_00247,1 */
/* !LINKSTO Dcm.Dsn.IB.ClearDiagnosticInformation.SvcH,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ClearDiagnosticInformation_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext)
{
  uint32 reqDTC;
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
  Dcm_OpStatusType LocalOpStatus = OpStatus;
  Dcm_NegativeResponseCodeType Nrc = E_OK;

  Dcm_ProtocolIndexType ProtocolIndex = Dcm_Dsl_Supervisor_GetProcessingProtocolIndex(
      DCM_RX_CONNECTION_ID_FROM_RXPDUID(pMsgContext->dcmRxPduId),
      (Dcm_RequestOriginType)(pMsgContext->msgAddInfo.requestOrigin));

  Dcm_DemClientIdType DemClientId = Dcm_Dsl_GetDemClientId(ProtocolIndex);

  DBG_DCM_DSPINTERNAL_CLEARDIAGNOSTICINFORMATION_SVCH_ENTRY(OpStatus,pMsgContext);


#if (DCM_DSP_CLEARDIAGNOSTICINFORMATION_PARALLEL_PROCESSING_ENABLED == STD_ON)
  serviceProcessStatus =
    Dcm_DspInternal_ClearDiagnosticInformation_ParallelExecutionPreProcessing(ProtocolIndex, &LocalOpStatus);

  if (DCM_E_OK == serviceProcessStatus)
  {
    /* reset service process status */
    serviceProcessStatus = DCM_E_ABORT;
#endif /* #if (DCM_DSP_CLEARDIAGNOSTICINFORMATION_PARALLEL_PROCESSING_ENABLED == STD_ON) */

    switch (LocalOpStatus)
    {
      case DCM_INITIAL:
        /* Check if length of request data is correct */
#if (DCM_CLEAR_DTC_MEMORY_SELECTION == STD_ON)
        if ((pMsgContext->reqDataLen < 3U) ||
            (pMsgContext->reqDataLen > 4U ))
#else
        if (pMsgContext->reqDataLen != 3U)
#endif /* #if (DCM_CLEAR_DTC_MEMORY_SELECTION == STD_ON) */
        {
          /* !LINKSTO Dcm.EB.ClearDiagnosticInformation.DcmDspClearDTCMemorySelectionDisabled.InvalidRequestSize.TransmitNrc0x13,1 */
          /* !LINKSTO Dcm.EB.ClearDiagnosticInformation.DcmDspClearDTCMemorySelectionEnabled.InvalidRequestSizeMinimum.TransmitNrc0x13,1 */
          /* !LINKSTO Dcm.EB.ClearDiagnosticInformation.DcmDspClearDTCMemorySelectionEnabled.InvalidRequestSizeMaximum.TransmitNrc0x13,1 */
          /* Invalid request length */
          Nrc = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
          serviceProcessStatus = DCM_E_DONE;
        }
        else
        {
          reqDTC = ((uint32)pMsgContext->reqData[0U] << 16U) |
                   ((uint32)pMsgContext->reqData[1U] << 8U)  |
                   ((uint32)pMsgContext->reqData[2U]);

          {
            uint8 DTCFormat = DEM_DTC_FORMAT_UDS;
#if (DCM_DSP_READDTCINFORMATION_SUPPORTEDOBDUDSDTCSEPARATION == STD_ON)
            if (reqDTC == DCM_GROUP_OF_DTCS_EMISSIONS_SYSTEM_GROUP)
            {
              /* !LINKSTO Dcm.ClearDiagnosticInformation.DcmDspClearDTCMemorySelectionDisabled.4ByteRequest.DTCSeparationEnabled.DTCGroup0xFFFF33.SetDTCOriginPrimaryMemory.SetDTCFormatOBD3Byte,1 */
              /* !LINKSTO Dcm.ClearDiagnosticInformation.DcmDspClearDTCMemorySelectionEnabled.4ByteRequest.DTCSeparationEnabled.DTCGroup0xFFFF33.SetDTCOriginPrimaryMemory.SetDTCFormatOBD3Byte,1 */
              /* !LINKSTO Dcm.ClearDiagnosticInformation.DcmDspClearDTCMemorySelectionEnabled.5ByteRequest.DTCSeparationEnabled.DTCGroup0xFFFF33.SetDTCOriginUserMemory.SetDTCFormatOBD3Byte,1 */
              DTCFormat = DEM_DTC_FORMAT_OBD_3BYTE;
            }
#endif

#if (DCM_CLEAR_DTC_MEMORY_SELECTION == STD_ON)
            if(pMsgContext->reqDataLen == 4U)
            {
              /* !LINKSTO Dcm.ClearDiagnosticInformation.DcmDspClearDTCMemorySelectionEnabled.5ByteRequest.DTCSeparationNotConfigured.SetDTCOriginUserMemory.SetDTCFormatUDS,1 */
              /* !LINKSTO Dcm.ClearDiagnosticInformation.DcmDspClearDTCMemorySelectionEnabled.5ByteRequest.DTCSeparationDisabled.SetDTCOriginUserMemory.SetDTCFormatUDS,1 */
              /* !LINKSTO Dcm.ClearDiagnosticInformation.DcmDspClearDTCMemorySelectionEnabled.5ByteRequest.DTCSeparationEnabled.DTCGroupNot0xFFFF33.SetDTCOriginUserMemory.SetDTCFormatUDS,1 */
              serviceProcessStatus = Dcm_Dsp_DemFacade_ClearDTCInfo_Setup(DemClientId, reqDTC,
                                           DTCFormat, (uint16)(pMsgContext->reqData[3U] + DCM_DTC_ORIGIN_USER_MEMORY_BASE), &Nrc);
            }
            else
#endif /* #if (DCM_CLEAR_DTC_MEMORY_SELECTION == STD_ON) */

            {
              /* !LINKSTO Dcm.ClearDiagnosticInformation.DcmDspClearDTCMemorySelectionDisabled.4ByteRequest.DTCSeparationNotConfigured.SetDTCOriginPrimaryMemory.SetDTCFormatUDS,1 */
              /* !LINKSTO Dcm.ClearDiagnosticInformation.DcmDspClearDTCMemorySelectionDisabled.4ByteRequest.DTCSeparationDisabled.SetDTCOriginPrimaryMemory.SetDTCFormatUDS,1 */
              /* !LINKSTO Dcm.ClearDiagnosticInformation.DcmDspClearDTCMemorySelectionDisabled.4ByteRequest.DTCSeparationEnabled.DTCGroupNot0xFFFF33.SetDTCOriginPrimaryMemory.SetDTCFormatUDS,1 */
              /* !LINKSTO Dcm.ClearDiagnosticInformation.DcmDspClearDTCMemorySelectionEnabled.4ByteRequest.DTCSeparationNotConfigured.SetDTCOriginPrimaryMemory.SetDTCFormatUDS,1 */
              /* !LINKSTO Dcm.ClearDiagnosticInformation.DcmDspClearDTCMemorySelectionEnabled.4ByteRequest.DTCSeparationDisabled.SetDTCOriginPrimaryMemory.SetDTCFormatUDS,1 */
              /* !LINKSTO Dcm.ClearDiagnosticInformation.DcmDspClearDTCMemorySelectionEnabled.4ByteRequest.DTCSeparationEnabled.DTCGroupNot0xFFFF33.SetDTCOriginPrimaryMemory.SetDTCFormatUDS,1 */
              serviceProcessStatus = Dcm_Dsp_DemFacade_ClearDTCInfo_Setup(DemClientId, reqDTC,
                                           DTCFormat, DEM_DTC_ORIGIN_PRIMARY_MEMORY, &Nrc);

            }
          }

          if (E_OK == Nrc)
          {
            serviceProcessStatus = Dcm_Dsp_DemFacade_ClearDTCInfo_Process(DemClientId, &Nrc);
          }
        }
        break;

      /* Status PENDING was returned before */
      case DCM_PENDING:
        serviceProcessStatus = Dcm_Dsp_DemFacade_ClearDTCInfo_Process(DemClientId, &Nrc);
        break;

      case DCM_CANCEL:
        /* !LINKSTO Dcm.EB.ClearDiagnosticInformation.Canceling,1 */
        serviceProcessStatus = Dcm_Dsp_DemFacade_ClearDTCInfo_Cancel(DemClientId);
        break;

      case DCM_FORCE_RCRRP_OK:
      case DCM_UPDATE_PAGE:
      case DCM_CONFIRMED_OK:
      case DCM_CONFIRMED_NOK:
        serviceProcessStatus = DCM_E_DONE;
        break;

      /* CHECK: NOPARSE */
      default:
        /* Defensive branch. Default case at the end of the switch statement */
        DCM_UNREACHABLE_CODE_ASSERT(DCM_SID_CLR_DIAG_INFORMATION);
        break;
      /* CHECK: PARSE */
    }

    if ((E_OK != Nrc) && (serviceProcessStatus == DCM_E_DONE))
    {
      /* Set negative response code */
      Dcm_ExternalSetNegResponse(pMsgContext, Nrc);
    }

#if (DCM_DSP_CLEARDIAGNOSTICINFORMATION_PARALLEL_PROCESSING_ENABLED == STD_ON)
  }

  Dcm_DspInternal_ClearDiagnosticInformation_ParallelExecutionPostProcessing(ProtocolIndex, serviceProcessStatus);
#endif /* #if (DCM_DSP_CLEARDIAGNOSTICINFORMATION_PARALLEL_PROCESSING_ENABLED == STD_ON) */

  DBG_DCM_DSPINTERNAL_CLEARDIAGNOSTICINFORMATION_SVCH_EXIT(serviceProcessStatus,
                                                           OpStatus,pMsgContext);
  return serviceProcessStatus;
}

/*==================[internal function definitions]==============================================*/

#if (DCM_DSP_CLEARDIAGNOSTICINFORMATION_PARALLEL_PROCESSING_ENABLED == STD_ON)

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ClearDiagnosticInformation_ParallelExecutionPreProcessing(
  Dcm_ProtocolIndexType ProtocolIndex,
  P2VAR(Dcm_OpStatusType, AUTOMATIC, DCM_VAR) OpStatus)
{
  Std_ReturnType serviceProcessStatus = DCM_E_OK;
  Dcm_OpStatusType LocalOpStatus = *OpStatus;

  /* Deviation MISRAC2012-3 */
  switch (LocalOpStatus)
  {
    /* Deviation MISRA-1, MISRAC2012-1, MISRAC2012-3 */
    /* Deviation GCC-1 <START> */
    case DCM_INITIAL:
    {
      /* Dummy assignment to avoid "implicit-fallthrough" GCC compiler warning in coverage build */
      LocalOpStatus = *OpStatus;
      DCM_PRECONDITION_ASSERT((DCM_CLEAR_DIAGNOSTIC_INFO_CONTEXT(ProtocolIndex).DemClientOwner == FALSE),
                              DCM_SID_CLR_DIAG_INFORMATION);
      /* no break */
    }
    /* Deviation GCC-1 <STOP> */

    case DCM_PENDING:
      if (FALSE == DCM_CLEAR_DIAGNOSTIC_INFO_CONTEXT(ProtocolIndex).DemClientOwner)
      {
        Dcm_DemClientIdType DemClientId = Dcm_Dsl_GetDemClientId(ProtocolIndex);

        /* client is not locked by that protocol; try to lock */
        Std_ReturnType LockStatus = Dcm_Dsp_DemFacade_LockClient(DemClientId);
        if (DCM_E_RESOURCE_LOCKED == LockStatus)
        {
          /* !LINKSTO Dcm.EB.UDSServices.ClearDiagnosticInformation.AcceptedForDispatching.ReadGenericInformationAlreadyRunningOnDifferentStack.SameDemClient.Postpone,1 */
          /* !LINKSTO Dcm.EB.UDSServices.ClearDiagnosticInformation.AcceptedForDispatching.ReadDTCInformationAlreadyRunningOnDifferentStack.SameDemClient.Postpone,1 */
          /* !LINKSTO Dcm.EB.UDSServices.ClearDiagnosticInformation.AcceptedForDispatching.ClearDiagnosticInformationAlreadyRunningOnDifferentStack.SameDemClient.Postpone,1 */

          /* client cannot be locked by that protocol; postpone processing */
          serviceProcessStatus = DCM_E_PENDING;
        }
        else
        {

          /* !LINKSTO Dcm.EB.UDSServices.ClearDiagnosticInformation.AcceptedForDispatching.ReadGenericInformationAlreadyRunningOnDifferentStack.NotSameDemClient.ProcessInParallel,1 */
          /* !LINKSTO Dcm.EB.UDSServices.ClearDiagnosticInformation.AcceptedForDispatching.ReadDTCInformationAlreadyRunningOnDifferentStack.NotSameDemClient.ProcessInParallel,1 */
          /* !LINKSTO Dcm.EB.UDSServices.ClearDiagnosticInformation.AcceptedForDispatching.ClearDiagnosticInformationAlreadyRunningOnDifferentStack.NotSameDemClient.ProcessInParallel,1 */

          /* client can be locked by that protocol; start processing */
          DCM_CLEAR_DIAGNOSTIC_INFO_CONTEXT(ProtocolIndex).DemClientOwner = TRUE;
          LocalOpStatus = DCM_INITIAL;
        }
      }
      break;

    case DCM_CANCEL:
      if (FALSE == DCM_CLEAR_DIAGNOSTIC_INFO_CONTEXT(ProtocolIndex).DemClientOwner)
      {
        /* client is not locked by that protocol; no further actions needed */
        serviceProcessStatus = DCM_E_DONE;
      }
      break;

    case DCM_FORCE_RCRRP_OK:
    case DCM_UPDATE_PAGE:
    case DCM_CONFIRMED_OK:
    case DCM_CONFIRMED_NOK:
      break;

    /* CHECK: NOPARSE */
    default:
      /* Defensive branch. Default case at the end of the switch statement */
      DCM_UNREACHABLE_CODE_ASSERT(DCM_SID_CLR_DIAG_INFORMATION);
      break;
    /* CHECK: PARSE */
  }

  *OpStatus = LocalOpStatus;
  return serviceProcessStatus;
}

STATIC FUNC(void, DCM_CODE) Dcm_DspInternal_ClearDiagnosticInformation_ParallelExecutionPostProcessing(
  Dcm_ProtocolIndexType ProtocolIndex,
  Std_ReturnType serviceProcessStatus)
{
  if ((DCM_CLEAR_DIAGNOSTIC_INFO_CONTEXT(ProtocolIndex).DemClientOwner == TRUE) &&
      (serviceProcessStatus != DCM_E_PENDING) &&
      (serviceProcessStatus != DCM_E_FORCE_RCRRP) &&
      (serviceProcessStatus != DCM_E_PROCESS_PAGE)
     )
  {
    Dcm_DemClientIdType DemClientId = Dcm_Dsl_GetDemClientId(ProtocolIndex);

    /* If client is locked by that protocol, unlock client when:
     *   - all amount of data was sent by page buffering mechanism or
     *   - the service handler is in a final state
     */
    Dcm_Dsp_DemFacade_UnlockClient(DemClientId);
    DCM_CLEAR_DIAGNOSTIC_INFO_CONTEXT(ProtocolIndex).DemClientOwner = FALSE;
  }
}

#endif /* #if ((DCM_DSP_CLEARDIAGNOSTICINFORMATION_PARALLEL_PROCESSING_ENABLED == STD_ON) */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif /* #if (DCM_DSP_USE_SERVICE_0X14 == STD_ON) ) */

/*==================[end of file]================================================================*/
