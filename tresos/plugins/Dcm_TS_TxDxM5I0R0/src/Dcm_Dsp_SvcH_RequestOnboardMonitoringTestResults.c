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

/*This file contains the implementation of the Diagnostic Service
  * Processing module in Dcm; all parts that relate to OBD Mode 6 */

/*===============================[includes]======================================================*/

#include <Dcm_Trace.h>
#include <Std_Types.h>                                                 /* AUTOSAR standard types */
#include <TSAutosar.h>

#include <Dcm_Dsp_SvcH_RequestOnboardMonitoringTestResults.h>

/* The functions provided and implemented by this unit are exclusively used for
 * OBD service 0x06 handling. */
#if(DCM_DSP_USE_SERVICE_0X06 == STD_ON)

#include <Dcm_Dsp_MidServices.h>                              /* Declaration of MidServices APIs */

#include <TSMem.h>                                               /* EB specific memory functions */

/*===========================[macro definitions]=================================================*/

/* !LINKSTO Dcm.ISO-15031-5_8.1.1_1,1 */
#if (defined DCM_OBD_AVAILABILITY_REQ_SIZE)
  #error "DCM_OBD_AVAILABILITY_REQ_SIZE is already defined"
#endif
#define DCM_OBD_AVAILABILITY_REQ_SIZE        6U

/* !LINKSTO SWS_Dcm_00956,1 */
#if (defined DCM_OBD_NONAVAILABILITY_REQ_SIZE)
  #error "DCM_OBD_NONAVAILABILITY_REQ_SIZE is already defined"
#endif
#define DCM_OBD_NONAVAILABILITY_REQ_SIZE     1U

#if (defined DCM_OBD_MID_AVAILDATALEN)
#error DCM_OBD_MID_AVAILDATALEN already defined
#endif
/** \brief Length of a single supported MID response */
#define DCM_OBD_MID_AVAILDATALEN 4U /* DATA_A, ... DATA_D */


/*=====================[external constants declarations]=========================================*/

/*=====================[internal constants declarations]=========================================*/

/*==================[internal function declarations]=============================================*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/** \brief Processes service requests for OBD service 0x06
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 */
STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RequestOnBoardMonitoringTestResults_Process(
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*==================[internal function definitions]=============================================*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/* !LINKSTO Dcm.dsn.OBDMID.ProcessObdMids,1 */
STATIC FUNC(void, DCM_CODE) Dcm_Dsp_RequestOnBoardMonitoringTestResults_Process(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext)
{
  Dcm_NegativeResponseCodeType Nrc = DCM_E_POSITIVERESPONSE;
  Std_ReturnType retVal = E_NOT_OK;
  Dcm_MsgLenType resDataLen = 0U;
  /* Get the number of requested MIDs. Allowed are max. 6 for availability
   * requests or max. 1 for non-availability requests */
  Dcm_MsgLenType nrReqMids = pMsgContext->reqDataLen;

  /* Pointer to the array of MIDs. Can be either the requestMessage
   * or, in case a common buffer is used, a separate buffer to which the
   * content of the request message is saved before it is overwritten by
   * the reponse message */
  P2VAR(uint8, AUTOMATIC, DCM_VAR) pReqMidList;

#if (DCM_COMMON_BUFF_CONFIGURED == STD_ON)
  /* reqBackup is used to store the requested Mids,
   * if a single buffer is configured as Rx and Tx buffer.
   * Size of buffer is the max number of MIDs that can be
   * requested in service 06 i.e. 6 MIDs meaning 6 bytes */
  uint8 reqBackup[DCM_OBD_AVAILABILITY_REQ_SIZE];

  /* If RX and TX buffer is common */
  if (pMsgContext->resData == pMsgContext->reqData)
  {
    /* Save the MIDs to the local buffer*/
    TS_MemCpy(reqBackup, pMsgContext->reqData, nrReqMids);

    /* Use the backup buffer for the request message */
    pReqMidList = reqBackup;
  }
  else
#endif
  {
    /* Use the original request message buffer */
    pReqMidList = pMsgContext->reqData;
  }

  /* Nothing to be sent as of yet */
  pMsgContext->resDataLen = 0U;

  /* Get availability or non-availability data? */
  if (DCM_IS_AVAILABILITY_OBDSUBID(pReqMidList[0U]) == TRUE)
  {
    uint8_least idxMidList;

    /* Iterate over all (at most 6) availability MIDs */
    for (idxMidList = 0U; idxMidList < nrReqMids; idxMidList++)
    {
      retVal = E_NOT_OK;

      /* Check if there are non-vailability MIDs among the availability ones */
      if (DCM_IS_AVAILABILITY_OBDSUBID(pReqMidList[idxMidList]) == TRUE)
      {
        /* write OBDMID into response */
        pMsgContext->resData[pMsgContext->resDataLen] = pReqMidList[idxMidList];

        if (pMsgContext->resMaxDataLen - pMsgContext->resDataLen >= DCM_OBD_MID_AVAILDATALEN)
        {
          /* Get availability MID response data */
          retVal = Dcm_Dsp_MidServices_GetAvailabilityMid(pReqMidList[idxMidList],
                                            &(pMsgContext->resData[(pMsgContext->resDataLen) + 1U]));
          if (retVal == E_NOT_OK)
          {
            /* !LINKSTO Dcm.ISO-15031-5_8.6.2_2,1 */
            Nrc = DCM_E_REQUESTOUTOFRANGE;
          }
        }
        else
        {
          /* Buffer is too small for the response data; Set the Negative Response Code. */
          /* !LINKSTO Dcm.EB.ReadDataById.NRC0x14,1 */
          Nrc = DCM_E_RESPONSETOOLONG;
        }
      }
      else
      {
        /* !LINKSTO Dcm.ISO-15031-5_8.6.1_10,1 */
        /* !LINKSTO SWS_Dcm_00945,1 */
        /* Mix of availability and non-availability MIDs is not allowed.
         * Ignore whole request and do not respond to it in any way. */
        Nrc = DCM_E_GENERALREJECT;
      }

      /* Increase the length of the response message if availability data was added */
      if (retVal == E_OK)
      {
        pMsgContext->resDataLen += DCM_OBD_MID_AVAILDATALEN + 1U;
      }
      else
      {
        /* Insufficient buffer space or invalid request (avail. and non-avail in same req.)? */
        if (Nrc != DCM_E_REQUESTOUTOFRANGE)
        {
          /* Ignore whole request message. */
          pMsgContext->resDataLen = 0U;
          break;
        }
      }
    }
  }
  else
  {
    /* !LINKSTO Dcm.ISO-15031-5_8.6.1_9,1 */
    /* !LINKSTO SWS_Dcm_00956,1 */
    /* Only 1 non-availability MID may be requested at once. Requesting more than one
     * is an error and will lead to the request message being ignored */
    if(nrReqMids == DCM_OBD_NONAVAILABILITY_REQ_SIZE)
    {
      /* write OBDMID into response */
      pMsgContext->resData[0U] = pReqMidList[0U];

      /* Get the non-availability MID response data */
      retVal = Dcm_Dsp_MidServices_GetNonAvailabilityMid(pReqMidList[0U],
                                                        &(pMsgContext->resData[1U]),
                                                        pMsgContext->resMaxDataLen,
                                                        &resDataLen,
                                                        &Nrc,
                                                        TRUE);

      /* Only set the length of the response message if the reading of the MID succeeded */
      if (retVal == E_OK)
      {
        /* !LINKSTO Dcm.EB.OBD_0x06.DTRDataObtained.PosResponse,1 */
        pMsgContext->resDataLen = resDataLen + 1U;
      }
    }
  }

  /* Suppress response if there is nothing to be send */
  if (pMsgContext->resDataLen == 0U)
  {
    /* !LINKSTO Dcm.ISO-15031-5_6.2.4.3.7_Table11_q,1 */
    /* !LINKSTO Dcm.ISO-15031-5_6.2.4.3.7_Table11_s,1 */
    /* !LINKSTO Dcm.EB.OBD_0x06.DcmGetNumTIDsOfOBDMID.E_NOT_OK.NoResponse,1 */
    /* !LINKSTO Dcm.EB.OBD_0x06.DcmGetNumTIDsOfOBDMID.E_OK.NoTIDs.NoResponse,1 */
    /* !LINKSTO Dcm.EB.OBD_0x06.NoDTRDataObtained.NoResponse,1 */
    pMsgContext->msgAddInfo.suppressPosResponse = TRUE;
  }
}

/*==================[external function definitions]=============================================*/

/* !LINKSTO Dcm414,1, Dcm.dsn.OBDMID.ScvH0x06,1 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_RequestOnBoardMonitoringTestResults_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
#if (DCM_DSP_MIDSERVICES_USE_LOCKING == STD_ON)
  boolean HasMidServicesLock = TRUE;
#endif

  DBG_DCM_DSP_REQUESTONBOARDMONITORINGTESTRESULTS_SVCH_ENTRY(OpStatus, pMsgContext);

  if (DCM_INITIAL == OpStatus)
  {
    /* If access to the MidServices needs to be protected */
#if (DCM_DSP_MIDSERVICES_USE_LOCKING == STD_ON)
    Std_ReturnType LockStatus = Dcm_Dsp_MidServices_LockServices();

    if (DCM_E_RESOURCE_LOCKED == LockStatus)
    {
      HasMidServicesLock = FALSE;

#if (DCM_RESPOND_WITH_BUSYREPEATREQUEST == STD_ON)
      /* !LINKSTO Dcm.EB.RequestOnBoardMonitoringTestResults.AcceptedForDispatching.ReadDataByIdentifierAlreadyRunningOnDifferentStack.Async.BRREnabled.TransmitNRC0x21,1 */
      /* !LINKSTO Dcm.EB.RequestOnBoardMonitoringTestResults.AcceptedForDispatching.RequestOnBoardMonitoringTestResultsAlreadyRunningOnDifferentStack.Async.BRREnabled.TransmitNRC0x21,1 */
      /* set negative response code */
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_BUSYREPEATREQUEST);
#else
      /* !LINKSTO Dcm.EB.RequestOnBoardMonitoringTestResults.AcceptedForDispatching.RequestOnBoardMonitoringTestResultsAlreadyRunningOnDifferentStack.Async.BRRDisabled.Discard,1 */
      /* !LINKSTO Dcm.EB.RequestOnBoardMonitoringTestResults.AcceptedForDispatching.ReadDataByIdentifierAlreadyRunningOnDifferentStack.Async.BRRDisabled.Discard,1 */
      /* no response */
      pMsgContext->msgAddInfo.suppressPosResponse = TRUE;
#endif /* #if (DCM_RESPOND_WITH_BUSYREPEATREQUEST == STD_ON) */
    }
    else
#endif /* #if (DCM_DSP_MIDSERVICES_USE_LOCKING == STD_ON) */
    {
      /* Validate the request length against min and max */
      /* !LINKSTO Dcm.ISO-15031-5_8.6.1_8,1 */
      if((pMsgContext->reqDataLen > 0U)
          && (pMsgContext->reqDataLen <= DCM_OBD_AVAILABILITY_REQ_SIZE))
      {
        /* Call the service handler. It is synchronous and will terminate during this call. */
        Dcm_Dsp_RequestOnBoardMonitoringTestResults_Process(pMsgContext);
      }
      else
      {
        /* Ignore invalid request. */
        pMsgContext->msgAddInfo.suppressPosResponse = TRUE;
      }
    }
  }

  serviceProcessStatus = DCM_E_DONE;

#if (DCM_DSP_MIDSERVICES_USE_LOCKING == STD_ON)
  /* Unlock MidServices */
  if (HasMidServicesLock == TRUE)
  {
    Dcm_Dsp_MidServices_UnlockServices();
  }
#endif /* #if(DCM_DSP_MIDSERVICES_USE_LOCKING == STD_ON) */

  DBG_DCM_DSP_REQUESTONBOARDMONITORINGTESTRESULTS_SVCH_EXIT(serviceProcessStatus
                                                           ,OpStatus, pMsgContext);

  return serviceProcessStatus;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif /* #if(DCM_DSP_USE_SERVICE_0X06 == STD_ON) */

/*==================[end of file]================================================================*/

