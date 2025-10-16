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

/* !LINKSTO Dcm.Dsn.File.DataTransferServices.Impl,1 */
/* This file contains the implementation of data transfer service functions. */

/*===============================[includes]======================================================*/
#include <Dcm_Trace.h>
#include <Dcm_Dsp_DataTransferServices.h>
#include <TSAutosar.h>
#include <TSMem.h>

#if (DCM_DSP_USE_DATATRANSFERSERVICES == STD_ON)

/*==================[macro definitions]==========================================================*/

/*==================[type definitions]===========================================================*/

/*==================[internal function declarations]=============================================*/

/*==================[external constants declarations]============================================*/

/*===================[internal constants declarations]===========================================*/

/*==================[external data declarations]=================================================*/

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dcm_MemMap.h>

VAR(Dcm_DataTransferType, DCM_VAR) Dcm_DataTransferContext[DCM_NUM_PROTOCOL];

#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dcm_MemMap.h>

/*==================[internal data declarations]=================================================*/

/*==================[external function definitions]==============================================*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/* Initializes the control structures used by the RequestDownload (0x34), RequestUpload (0x35),
   TransferData (0x36) and RequestTransferExit (0x37) service handlers */
FUNC(void, DCM_CODE) Dcm_UploadDownloadInit(void)
{
  DBG_DCM_UPLOADDOWNLOADINIT_ENTRY();

  TS_MemSet(Dcm_DataTransferContext,0U,sizeof(Dcm_DataTransferContext));

  DBG_DCM_UPLOADDOWNLOADINIT_EXIT();
}

/* This function performs required actions upon session change. */
FUNC(void, DCM_CODE) Dcm_Dsl_DataTransferServices_SessionChange(
  Dcm_SesCtrlType NewSession
)
{
  DBG_DCM_DATATRANSFERSERVICES_SESSIONCHANGE_ENTRY(NewSession);

  if(DCM_DEFAULT_SESSION == NewSession)
  {
    /* !LINKSTO Dcm.EB.DiagnosticSessionControl.S3Timeout.SessionTransitionToDefault.ResetDataTransferServicesState,1 */
    /* !LINKSTO Dcm.EB.DiagnosticSessionControl.ProtocolPreemption.SessionTransitionToDefault.ResetDataTransferServicesState,1 */
    /* !LINKSTO Dcm.EB.DiagnosticSessionControl.IncomingOBDRequest.SessionTransitionToDefault.ResetDataTransferServicesState,1 */
    /* !LINKSTO Dcm.EB.DiagnosticSessionControl.ResetToDefaultSessionAPI.SessionTransitionToDefault.ResetDataTransferServicesState,1 */
    /* !LINKSTO Dcm.EB.DiagnosticSessionControl.ResetToDefaultSessionOperation.SessionTransitionToDefault.ResetDataTransferServicesState,1 */
    /* !LINKSTO Dcm.EB.DiagnosticSessionControl.DiagnosticSessionControlRequest.SessionTransitionToDefault.ResetDataTransferServicesState,1 */
    Dcm_UploadDownloadInit();
  }

  DBG_DCM_DATATRANSFERSERVICES_SESSIONCHANGE_EXIT();
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*==================[internal function definitions]==============================================*/

#endif /* #if(DCM_DSP_USE_DATATRANSFERSERVICES) */

/*==================[end of file]================================================================*/
