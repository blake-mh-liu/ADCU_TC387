/***************************************************************************
 *
 * \file Dccm_MainFunction.c
 *
 * \brief Diagnostic Client Communication Manager implementation of MainFunction
 *
 * Copyright 2020 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* MISRA-C:2012 Deviation List
 *
  * MISRAC2012-1) Deviated Rule: 2.1 (required)
 * A project shall not contain unreachable code.
 *
 * Reason:
 * False positive. The C1 coverage report shows TRUE and FALSE coverage for
 * the reported lines. This proves that the code is reachable.
 */
/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * False positive, because in the indicated TestSequence, DCCM_MAX_DIAGNOSTIC_PROTOCOLS is 1U.
 * This means that the condition is not always true. If the condition were always true then an infinite loop would occur.
 */

/*==================[inclusions]=============================================*/

#include <Dccm_Internal.h>
#include <PduR_Dccm.h>
#include <Dccm_Cfg.h>                      /* Dccm configuration            */

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[internal function declarations]=========================*/

#define DCCM_START_SEC_CODE
#include <Dccm_MemMap.h>

STATIC FUNC(void, DCCM_CODE) Dccm_CheckTimeout(Dccm_ProtocolIdType ProtocolId);
STATIC FUNC(void, DCCM_CODE) Dccm_CheckTimeoutForFunctionalRequest(void);
STATIC FUNC(void, DCCM_CODE) Dccm_SendTesterPresent(Dccm_ProtocolIdType ProtocolId);
STATIC FUNC(void, DCCM_CODE) Dccm_ManageTesterPresent(void);
STATIC FUNC(void, DCCM_CODE) Dccm_ManageSendNotify(Dccm_ProtocolIdType ProtocolId);

#define DCCM_STOP_SEC_CODE
#include <Dccm_MemMap.h>

/*==================[external constants]=====================================*/

#define DCCM_START_SEC_CONST_UNSPECIFIED
#include <Dccm_MemMap.h>

CONST(PduIdType, DCCM_CONST) MaxServers = DCCM_MAX_SERVERS_PHYSICAL_ADDRESSING + DCCM_MAX_SERVERS_FUNCTIONAL_ADDRESSING;

CONST(Dccm_DiagnosticProtocolType, DCCM_CONST) Dccm_DiagnosticProtocolDefault =
{
  0U,/* TxPduId */
  0U, /* RxPduId */
  0U, /* PduRTxPduId */
  DCCM_DIAGNOSTIC_PROTOCOL_STATUS_UNUSED, /* Status */
  NULL_PTR, /* DataLengthPtr */
  NULL_PTR, /* Callback */
  /* Dccm_PduInfoRxTxType Dccm_PduInfo:*/
  {
    /* PduInfoType PduInfo; */
    {
      NULL_PTR, /* SduDataPtr */
      0U, /* SduLength */
    },
    NULL_PTR, /* Buffer */
    0U, /* Length */
    0U, /* TpTotalLength */
    0U /* TxConfirmedLength */
  },
  DCCM_RSP_OK, /* ResponseCode */
  {/* Dccm_TimeoutsType Timeouts*/
    DCCM_TIMEOUT_OFF, /* Timeout */
    DCCM_TIMEOUT_OFF,/* InternalTimeout */
    DCCM_TIMEOUT_INTERNAL, /* InternalTimeoutConfigurationValue */
#if (DCCM_P2CLIENT_ENABLED == STD_ON)
    DCCM_TIMEOUT_P2CLIENT, /* P2ClientConfigurationValue */
    DCCM_TIMEOUT_P2STARCLIENT /* P2StarClientConfigurationValue */
#elif (DCCM_P6CLIENT_ENABLED == STD_ON)
    DCCM_TIMEOUT_P6CLIENT, /* P6ClientConfigurationValue */
    DCCM_TIMEOUT_P6STARCLIENT /* P6StarClientConfigurationValue */
#endif
  },
#if (DCCM_BUFFER_STREAMING == STD_ON)
  NULL_PTR, /*  BufferStreamingCallback */
  0U, /* StartLocation */
  0U, /* AvailableData */
  DCCM_RETRY_INFO_NULL, /* RetryInformation */
#endif
  /* Dccm_TesterPresentType TesterPresent */
  {
    FALSE, /* isTesterPresentEnabled */
    FALSE, /* isMarkedForDisable */
    NULL_PTR,/* DataLengthPtr */
    NULL_PTR,/* Buffer */
    0U, /* Length */
    FALSE, /* mustSendTesterPresentMessage */
    DCCM_TIMEOUT_OFF, /* TesterPresentInterval */
    DCCM_TIMEOUT_OFF, /* TesterPresentIntervalCounter */
  },
  PHYSICAL_ADDRESSING, /* AddressingType */
  /* RequestInfo */
  {
    DCCM_NO_SERVICE, /* ServiceID */
    FALSE, /* SuppressPosRsp */
    FALSE, /* isServiceIDsaved */
    FALSE, /* isSuppressPosRspSaved */
  },
  FALSE, /* TesterPresentInitiatedByDccm */
  FALSE, /* PreparedToReceiveFunctionalResponse */
  FALSE, /* ResponsePendingWasReceived */
};

#define DCCM_STOP_SEC_CONST_UNSPECIFIED
#include <Dccm_MemMap.h>

/*==================[internal constants]=====================================*/

#define DCCM_START_SEC_CONST_UNSPECIFIED
#include <Dccm_MemMap.h>

STATIC CONST(Dccm_FunctionalRequestHelperType, DCCM_CONST) Dccm_FunctionalRequestHelperDefault =
{
  DCCM_INVALID_PROTOCOL_ID, /*FunctionalRequestOngoingOnProtocolId*/
  FALSE, /* SuppressPosRsp */
  FALSE, /* isSuppressPosRspSaved */
  DCCM_TIMEOUT_OFF, /* Timeout */
#if (DCCM_P2CLIENT_ENABLED == STD_ON)
  DCCM_TIMEOUT_OFF, /* P2ClientConfigurationValue*/
  DCCM_TIMEOUT_OFF, /* P2StarClientConfigurationValue */
#elif (DCCM_P6CLIENT_ENABLED == STD_ON)
  DCCM_TIMEOUT_OFF, /* P6ClientConfigurationValue */
  DCCM_TIMEOUT_OFF, /* P6StarClientConfigurationValue */
#endif
};

#define DCCM_STOP_SEC_CONST_UNSPECIFIED
#include <Dccm_MemMap.h>

/*==================[external data]==========================================*/

#define DCCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dccm_MemMap.h>

/**
 * \brief Diagnostic protocol: A diagnostic protocol represent the whole communication between
 * one Diagnostic Client an one Diagnostic Server
 */
VAR(Dccm_DiagnosticProtocolType, DCCM_VAR) Dccm_DiagnosticProtocols[DCCM_MAX_DIAGNOSTIC_PROTOCOLS];
/**
 * \brief The ProtocolId's on which to send the TesterPresent message
 */
VAR(Dccm_ProtocolIdType, DCCM_VAR) ProtocolIdsForTesterPresentMessages[DCCM_MAX_DIAGNOSTIC_PROTOCOLS];
/**
 * \brief Contains data related to the current functional request.
 */
VAR(Dccm_FunctionalRequestHelperType, DCCM_VAR) Dccm_FunctionalRequestHelper;

#define DCCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dccm_MemMap.h>


#define DCCM_START_SEC_VAR_INIT_8
#include <Dccm_MemMap.h>

/**
 * \brief The number of ProtocolId's on which to send the TesterPresent message
 */
VAR(uint8, DCCM_VAR) NumberOfProtocolIdsForTesterPresentMessages = 0U;

/**
 * \brief Did the client initialized Dccm with a call to the function Dccm_Init()?
 * If not, some functions will return error
 */
VAR(boolean, DCCM_VAR) DccmWasInitialized = FALSE;

#define DCCM_STOP_SEC_VAR_INIT_8
#include <Dccm_MemMap.h>

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

#define DCCM_START_SEC_CODE
#include <Dccm_MemMap.h>

FUNC(void, DCCM_CODE) Dccm_Init(void)
{
  Dccm_ProtocolIdType ProtocolId;

  NumberOfProtocolIdsForTesterPresentMessages = 0U;
  NrOfProtocolsAlreadyUsedForPhysicalCommunication = 0U;
  Dccm_FunctionalRequestHelper = Dccm_FunctionalRequestHelperDefault;

  /* Deviation TASKING-1 */
  for(ProtocolId = 0; ProtocolId < DCCM_MAX_DIAGNOSTIC_PROTOCOLS; ProtocolId++)
  {
    Dccm_DiagnosticProtocols[ProtocolId] = Dccm_DiagnosticProtocolDefault;
    ProtocolIdsForTesterPresentMessages [ProtocolId] = DCCM_INVALID_PROTOCOL_ID;
  }

  DccmWasInitialized = TRUE;
}

FUNC(void, DCCM_CODE) Dccm_MainFunction(void)
{
  Std_ReturnType RetVal;
  Dccm_ProtocolIdType ProtocolId = 0U;
  sint8 CurrentAddressingType;

#if (DCCM_BUFFER_STREAMING == STD_ON)
  PduLengthType HowManyBytesToAsk = 0U;
#endif

  if (DccmWasInitialized == TRUE)
  {
    Dccm_ManageTesterPresent();
    Dccm_CheckTimeoutForFunctionalRequest();

    /* send functional addressing requests first */
    /* for (CurrentAddressingType = FUNCTIONAL_ADDRESSING; CurrentAddressingType >= PHYSICAL_ADDRESSING ; CurrentAddressingType --)*/
    for (CurrentAddressingType = 1; CurrentAddressingType >= 0 ; CurrentAddressingType --)
    {
      /* Deviation TASKING-1 */
      for (ProtocolId = 0; ProtocolId < DCCM_MAX_DIAGNOSTIC_PROTOCOLS; ProtocolId++)
      {
        /* CurrentAddressingType has the type sint8, but in the logic from this context, it will have only the values 1 and 0.
         * Because of this, it is safe to cast to uint8.
        */
        if (Dccm_DiagnosticProtocols[ProtocolId].AddressingType == ((uint8) CurrentAddressingType))
        {
          if (Dccm_DiagnosticProtocols[ProtocolId].Status != DCCM_DIAGNOSTIC_PROTOCOL_STATUS_UNUSED)
          {
            /* check for communication timeouts */
            Dccm_CheckTimeout(ProtocolId);

            switch (Dccm_DiagnosticProtocols[ProtocolId].Status)
            {
              case DCCM_DIAGNOSTIC_PROTOCOL_STATUS_READY_TO_TRANSMIT:
                /* trigger PduR transmit */
                RetVal = PduR_DccmTransmit(Dccm_DiagnosticProtocols[ProtocolId].PduRTxPduId, &(Dccm_DiagnosticProtocols[ProtocolId].Dccm_PduInfo.PduInfo));

                /* ENTER critical section */
                SchM_Enter_Dccm_SCHM_DCCM_EXCLUSIVE_AREA_0();
                /* set internal timeout, to avoid endless loop if PduR does not
                * call Dccm_TxConfirmation */
                if (Dccm_DiagnosticProtocols[ProtocolId].Timeouts.InternalTimeoutConfigurationValue != DCCM_TIMEOUT_OFF)
                {
                  Dccm_DiagnosticProtocols[ProtocolId].Timeouts.InternalTimeout = Dccm_DiagnosticProtocols[ProtocolId].Timeouts.InternalTimeoutConfigurationValue + DCCM_EXE_INTERVAL;
                }
                /* LEAVE critical section */
                SchM_Exit_Dccm_SCHM_DCCM_EXCLUSIVE_AREA_0();

                /* communication timeout will be set after successful
                 * transmission (in Dccm_TxConfirmation)*/
                if (RetVal == E_OK)
                {
                  Dccm_DiagnosticProtocols[ProtocolId].Status = DCCM_DIAGNOSTIC_PROTOCOL_STATUS_TRANSMIT;
                }
                else
                {
                  Dccm_DiagnosticProtocols[ProtocolId].ResponseCode = DCCM_RSP_TX_TRIG_FAILED;
                  Dccm_DiagnosticProtocols[ProtocolId].Status = DCCM_DIAGNOSTIC_PROTOCOL_STATUS_SEND_NOTIFY;
                }
                break;

#if (DCCM_BUFFER_STREAMING == STD_ON)
              case DCCM_DIAGNOSTIC_PROTOCOL_STATUS_TRANSMIT_REQUEST_NEXT_BUFFER:
                if ( *(Dccm_DiagnosticProtocols[ProtocolId].DataLengthPtr)
                      < (Dccm_DiagnosticProtocols[ProtocolId].StartLocation + Dccm_DiagnosticProtocols[ProtocolId].Dccm_PduInfo.Length)
                )
                {
                  HowManyBytesToAsk = *(Dccm_DiagnosticProtocols[ProtocolId].DataLengthPtr) - Dccm_DiagnosticProtocols[ProtocolId].StartLocation;
                }
                else
                {
                  HowManyBytesToAsk  = Dccm_DiagnosticProtocols[ProtocolId].Dccm_PduInfo.Length;
                }
                RetVal = Dccm_DiagnosticProtocols[ProtocolId].BufferStreamingCallback
                (
                    ProtocolId,
                    Dccm_DiagnosticProtocols[ProtocolId].Dccm_PduInfo.Buffer,
                    Dccm_DiagnosticProtocols[ProtocolId].StartLocation,
                    & HowManyBytesToAsk,
                    Dccm_DiagnosticProtocols[ProtocolId].RetryInformation
                );
                if (RetVal == E_OK)
                {
                  Dccm_DiagnosticProtocols[ProtocolId].AvailableData = HowManyBytesToAsk;
                  Dccm_DiagnosticProtocols[ProtocolId].Status = DCCM_DIAGNOSTIC_PROTOCOL_STATUS_TRANSMIT;
                }
                else
                {
                  /* let the protocol status unchanged */
                }
                break;
#endif

              case DCCM_DIAGNOSTIC_PROTOCOL_STATUS_SEND_NOTIFY:
                Dccm_ManageSendNotify(ProtocolId);

                break;

              default:
                /* for all the other states we have nothing to do in the main function */
                break;
            }
          }
        }
      }
    }
  }
}

#define DCCM_STOP_SEC_CODE
#include <Dccm_MemMap.h>

/*==================[internal function definitions]==========================*/

#define DCCM_START_SEC_CODE
#include <Dccm_MemMap.h>

/**
 * \brief Check if timeout occurred
 */
STATIC FUNC(void, DCCM_CODE) Dccm_CheckTimeout
(
  Dccm_ProtocolIdType ProtocolId
)
{
  /* Note: when the code of this function is updated, the code from the function Dccm_CheckTimeoutForFunctionalRequest()
   * should also be updated, with the observation that InternalTimeout is not relevant for Dccm_CheckTimeoutForFunctionalRequest().*/
  /* ENTER critical section */
  SchM_Enter_Dccm_SCHM_DCCM_EXCLUSIVE_AREA_0();

  /* P2Client and P2*Client */
  if (Dccm_DiagnosticProtocols[ProtocolId].Timeouts.Timeout != DCCM_TIMEOUT_OFF)
  {
    if (Dccm_DiagnosticProtocols[ProtocolId].Timeouts.Timeout >= DCCM_EXE_INTERVAL)
    {
      Dccm_DiagnosticProtocols[ProtocolId].Timeouts.Timeout = Dccm_DiagnosticProtocols[ProtocolId].Timeouts.Timeout - DCCM_EXE_INTERVAL;
    }
    else
    {
#if (DCCM_P2CLIENT_ENABLED == STD_ON)
      if ((Dccm_DiagnosticProtocols[ProtocolId].RequestInfo.isSuppressPosRspSaved == TRUE)
          && (Dccm_DiagnosticProtocols[ProtocolId].RequestInfo.SuppressPosRsp == TRUE)
      )
      {
        Dccm_DiagnosticProtocols[ProtocolId].ResponseCode = DCCM_RSP_TIMEOUT_P2CLIENT_SPRMIB_TRUE;
      }
      else
      {
        Dccm_DiagnosticProtocols[ProtocolId].ResponseCode = DCCM_RSP_TIMEOUT_P2CLIENT;
      }
#elif (DCCM_P6CLIENT_ENABLED == STD_ON)
      if ((Dccm_DiagnosticProtocols[ProtocolId].RequestInfo.isSuppressPosRspSaved == TRUE)
          && (Dccm_DiagnosticProtocols[ProtocolId].RequestInfo.SuppressPosRsp == TRUE)
      )
      {
        Dccm_DiagnosticProtocols[ProtocolId].ResponseCode = DCCM_RSP_TIMEOUT_P6CLIENT_SPRMIB_TRUE;
      }
      else
      {
        Dccm_DiagnosticProtocols[ProtocolId].ResponseCode = DCCM_RSP_TIMEOUT_P6CLIENT;
      }
#endif
      Dccm_DiagnosticProtocols[ProtocolId].Status = DCCM_DIAGNOSTIC_PROTOCOL_STATUS_SEND_NOTIFY;
    }
  }

  /* internal timeout*/
  if (Dccm_DiagnosticProtocols[ProtocolId].Timeouts.InternalTimeout != DCCM_TIMEOUT_OFF)
  {
    if (Dccm_DiagnosticProtocols[ProtocolId].Timeouts.InternalTimeout >= DCCM_EXE_INTERVAL)
    {
      Dccm_DiagnosticProtocols[ProtocolId].Timeouts.InternalTimeout = Dccm_DiagnosticProtocols[ProtocolId].Timeouts.InternalTimeout - DCCM_EXE_INTERVAL;
    }
    else
    {
      Dccm_DiagnosticProtocols[ProtocolId].ResponseCode = DCCM_RSP_TIMEOUT_INTERNAL;
      Dccm_DiagnosticProtocols[ProtocolId].Status = DCCM_DIAGNOSTIC_PROTOCOL_STATUS_SEND_NOTIFY;
    }
  }

  /* LEAVE critical section */
  SchM_Exit_Dccm_SCHM_DCCM_EXCLUSIVE_AREA_0();
}

/**
 * \brief Check if timeout occurred for the functional request
 */
STATIC FUNC(void, DCCM_CODE) Dccm_CheckTimeoutForFunctionalRequest
(
  void
)
{
  /* Note: the code of this function should have more or less the same code with the function Dccm_CheckTimeout(),
   * with the observation that InternalTimeout is not relevant for this function.*/
  /* ENTER critical section */
  SchM_Enter_Dccm_SCHM_DCCM_EXCLUSIVE_AREA_0();

  /* P2Client and P2*Client */
  if (Dccm_FunctionalRequestHelper.Timeout != DCCM_TIMEOUT_OFF)
  {
    if (Dccm_FunctionalRequestHelper.Timeout >= DCCM_EXE_INTERVAL)
    {
      Dccm_FunctionalRequestHelper.Timeout = Dccm_FunctionalRequestHelper.Timeout - DCCM_EXE_INTERVAL;
    }
    else if (Dccm_DiagnosticProtocols[Dccm_FunctionalRequestHelper.FunctionalRequestOngoingOnProtocolId].Status == DCCM_DIAGNOSTIC_PROTOCOL_STATUS_RECEIVE)
    {
      /* This part must be delayed until no TesterPresent is sent on the functional protocol.*/
      /* The sending of functional TesterPresent happened before this moment.
       * If the status of the functional protocol is RECEIVE, then the response can be notified to the SWC.
       * If the status of the functional protocol is not RECEIVE, then this is also the "retry mechanism".
       * The "retry" will stop only after Dccm_FunctionalRequestHelper is reset to it's default value, at the end of "SEND_NOTIFY" from the Dccm_MainFunction().*/
#if (DCCM_P2CLIENT_ENABLED == STD_ON)
      if ( (Dccm_FunctionalRequestHelper.isSuppressPosRspSaved == TRUE)
          && (Dccm_FunctionalRequestHelper.SuppressPosRsp == TRUE)
      )
      {
        Dccm_DiagnosticProtocols[Dccm_FunctionalRequestHelper.FunctionalRequestOngoingOnProtocolId].ResponseCode = DCCM_RSP_TIMEOUT_P2CLIENT_SPRMIB_TRUE;
      }
      else
      {
        Dccm_DiagnosticProtocols[Dccm_FunctionalRequestHelper.FunctionalRequestOngoingOnProtocolId].ResponseCode = DCCM_RSP_TIMEOUT_P2CLIENT;
      }
#elif (DCCM_P6CLIENT_ENABLED == STD_ON)
      /* Currently, P6Client is out of scope for functional request processing. */
      /* To be updated at the implementation for P6_Client/P6*_Client. */
      /*if ((Dccm_FunctionalRequestHelper.isSuppressPosRspSaved == TRUE)
          && (Dccm_FunctionalRequestHelper.SuppressPosRsp == TRUE)
      )
      {
        Dccm_DiagnosticProtocols[Dccm_FunctionalRequestHelper.FunctionalRequestOngoingOnProtocolId].ResponseCode = DCCM_RSP_TIMEOUT_P6CLIENT_SPRMIB_TRUE;
      }
      else
      {
        Dccm_DiagnosticProtocols[Dccm_FunctionalRequestHelper.FunctionalRequestOngoingOnProtocolId].ResponseCode = DCCM_RSP_TIMEOUT_P6CLIENT;
      }*/
#endif
      Dccm_DiagnosticProtocols[Dccm_FunctionalRequestHelper.FunctionalRequestOngoingOnProtocolId].Status = DCCM_DIAGNOSTIC_PROTOCOL_STATUS_SEND_NOTIFY;
    }
    else
    { /* Nothing to do here.*/ }
  }
  /* LEAVE critical section */
  SchM_Exit_Dccm_SCHM_DCCM_EXCLUSIVE_AREA_0();
}

/**
 * \brief Send the TesterPresent message
 */
STATIC FUNC(void, DCCM_CODE) Dccm_SendTesterPresent
(
  Dccm_ProtocolIdType ProtocolId
)
{
  /* Use an exclusive area to prevent the following use-case:
   * Dccm starts in an execution thread the function Dccm_SendTesterPresent() (this function)
   * (this means to copy the TesterPresent messages in the array with protocols)
   * but the client of Dccm, form a different thread of execution,
   * asks to add or delete a tester present destination
   * (using the functions Dccm_EnableTesterPresent() or Dccm_DisableTesterPresent()):
   * this would disrupt the array ProtocolIdsForTesterPresentMessages
   * and the variable NumberOfProtocolIdsForTesterPresentMessages during the execution of this function.
   *
   * The function Dccm_SendRequest() do not call code from outside of UsdC,
   * and always have a finite execution time - it is just putting data in a buffer.
   * */
  /* ENTER critical section */
  SchM_Enter_Dccm_SCHM_DCCM_EXCLUSIVE_AREA_0();

  if (Dccm_DiagnosticProtocols[ProtocolId].TesterPresent.DataLengthPtr != NULL_PTR)
  {
    /* Keep-Alive-Logic is defined as the functionally addressed valid TesterPresent message with
       suppressPosRspMsgIndicationBit set to TRUE and shall be processed by bypass logic. */
    /* initialize values */
    Dccm_DiagnosticProtocols[ProtocolId].TesterPresent.Buffer[0] = DCCM_SID_TESTER_PRESENT;
    Dccm_DiagnosticProtocols[ProtocolId].TesterPresent.Buffer[1] = DCCM_SUPP_MSG_BIT;
    *(Dccm_DiagnosticProtocols[ProtocolId].TesterPresent.DataLengthPtr) = 2U;

     /* if the code execution reached this point, the call to Dccm_SendRequest() will return without errors,
      * because all conditions were already verified, or the parameters are good for sure,
      * as they are provided internally by the Dccm module. */
    Dccm_DiagnosticProtocols[ProtocolId].TesterPresentInitiatedByDccm = TRUE;

    (void) Dccm_SendRequest ( ProtocolId,
        Dccm_DiagnosticProtocols[ProtocolId].TesterPresent.Buffer,
        Dccm_DiagnosticProtocols[ProtocolId].TesterPresent.Length,
        Dccm_DiagnosticProtocols[ProtocolId].TesterPresent.DataLengthPtr );
  }
  Dccm_DiagnosticProtocols[ProtocolId].TesterPresent.mustSendTesterPresentMessage = FALSE;

  /* LEAVE critical section */
  SchM_Exit_Dccm_SCHM_DCCM_EXCLUSIVE_AREA_0();
}

STATIC FUNC(void, DCCM_CODE) Dccm_ManageTesterPresent
(
  void
)
{
  Dccm_ProtocolIdType ProtocolId = 0;

  /* Should send Tester Present message for functional addressing?
   * Only if the sending of TesterPresent was enabled for at least one server/address. */
  if (NumberOfProtocolIdsForTesterPresentMessages > 0U)
  {
    for (ProtocolId = 0; ProtocolId < NumberOfProtocolIdsForTesterPresentMessages; ProtocolId++)
    {
      if (Dccm_DiagnosticProtocols[ProtocolIdsForTesterPresentMessages[ProtocolId]].TesterPresent.isMarkedForDisable == TRUE)
      {
        /* do nothing: if the TesterPresent was "marked for disable" for the current protocol,
         * no tracking is needed related with "when to send the next TesterPresent message". */
      }
      else if (Dccm_DiagnosticProtocols[ProtocolIdsForTesterPresentMessages[ProtocolId]].TesterPresent.TesterPresentIntervalCounter > DCCM_EXE_INTERVAL)
      {
        /* continue to decrement the counter */
        Dccm_DiagnosticProtocols[ProtocolIdsForTesterPresentMessages[ProtocolId]].TesterPresent.TesterPresentIntervalCounter =
                   Dccm_DiagnosticProtocols[ProtocolIdsForTesterPresentMessages[ProtocolId]].TesterPresent.TesterPresentIntervalCounter - DCCM_EXE_INTERVAL;

        /* retry implementation */
        /* Dccm should retry to send TesterPresent but only if the protocol is ready to be used (i.e., there is no other sendRequest in progress) */
        if (Dccm_DiagnosticProtocols[ProtocolIdsForTesterPresentMessages[ProtocolId]].TesterPresent.mustSendTesterPresentMessage == TRUE)
        {
          if ( (Dccm_DiagnosticProtocols[ProtocolIdsForTesterPresentMessages[ProtocolId]].AddressingType == FUNCTIONAL_ADDRESSING)
              && (Dccm_DiagnosticProtocols[ProtocolIdsForTesterPresentMessages[ProtocolId]].Status == DCCM_DIAGNOSTIC_PROTOCOL_STATUS_RECEIVE)
          )
          {
            Dccm_DiagnosticProtocols[ProtocolIdsForTesterPresentMessages[ProtocolId]].Status = DCCM_DIAGNOSTIC_PROTOCOL_STATUS_READY;
          }

          if (Dccm_DiagnosticProtocols[ProtocolIdsForTesterPresentMessages[ProtocolId]].Status == DCCM_DIAGNOSTIC_PROTOCOL_STATUS_READY)
          {
            /* send the message */
            Dccm_SendTesterPresent(ProtocolIdsForTesterPresentMessages[ProtocolId]);
          }
        }
      }
      else
      {
        /* record that the TesterPresent message must be sent */
        Dccm_DiagnosticProtocols[ProtocolIdsForTesterPresentMessages[ProtocolId]].TesterPresent.mustSendTesterPresentMessage = TRUE;

        if ( (Dccm_DiagnosticProtocols[ProtocolIdsForTesterPresentMessages[ProtocolId]].AddressingType == FUNCTIONAL_ADDRESSING)
            && (Dccm_DiagnosticProtocols[ProtocolIdsForTesterPresentMessages[ProtocolId]].Status == DCCM_DIAGNOSTIC_PROTOCOL_STATUS_RECEIVE)
        )
        {
          Dccm_DiagnosticProtocols[ProtocolIdsForTesterPresentMessages[ProtocolId]].Status = DCCM_DIAGNOSTIC_PROTOCOL_STATUS_READY;
        }

        /* send the message but only if the protocol is ready to be used - there is no other sendRequest in progress */
        if (Dccm_DiagnosticProtocols[ProtocolIdsForTesterPresentMessages[ProtocolId]].Status == DCCM_DIAGNOSTIC_PROTOCOL_STATUS_READY)
        {
          Dccm_SendTesterPresent(ProtocolIdsForTesterPresentMessages[ProtocolId]);
        }
        /* reinitialize the counter */
        Dccm_DiagnosticProtocols[ProtocolIdsForTesterPresentMessages[ProtocolId]].TesterPresent.TesterPresentIntervalCounter =
            Dccm_DiagnosticProtocols[ProtocolIdsForTesterPresentMessages[ProtocolId]].TesterPresent.TesterPresentInterval;
      }
    }
  }
}

STATIC FUNC(void, DCCM_CODE) Dccm_ManageSendNotify
(
  Dccm_ProtocolIdType ProtocolId
)
{
  Dccm_ProtocolIdType PhysicalProtocolId = 0U;
  boolean itWasTesterPresentInitiatedByDccm = Dccm_DiagnosticProtocols[ProtocolId].TesterPresentInitiatedByDccm;

  /* Deviation MISRAC2012-1 <START> */
  /* notify SW-Manager */
  if ( /* In principle, do not send any notification to SWC if it was a TesterPresent initiated by Dccm. */
       (Dccm_DiagnosticProtocols[ProtocolId].TesterPresentInitiatedByDccm == FALSE)
       /* Exception: if Dccm was configured explicitly in this way, still send the notification after sending
        * a TesterPresent initiated by Dccm. */
       || (DCCM_TO_NOTIFY_KEEP_ALIVE_LOGIC == STD_ON)
  )
  {
    Dccm_DiagnosticProtocols[ProtocolId].Callback(ProtocolId, Dccm_DiagnosticProtocols[ProtocolId].ResponseCode);
  }
  /* Deviation MISRAC2012-1 <STOP> */

  /* clean-up: at the end of the request handling, TesterPresentInitiatedByDccm must be FALSE in any use-case. */
  Dccm_DiagnosticProtocols[ProtocolId].TesterPresentInitiatedByDccm = FALSE;

  if (Dccm_DiagnosticProtocols[ProtocolId].TesterPresent.isMarkedForDisable == TRUE)
  {
     (void)Dccm_DisableTesterPresent(ProtocolId);
  }

  /* stop timeout counter */
  /* ENTER critical section */
  SchM_Enter_Dccm_SCHM_DCCM_EXCLUSIVE_AREA_0();
  Dccm_DiagnosticProtocols[ProtocolId].Timeouts.Timeout = DCCM_TIMEOUT_OFF;
  Dccm_DiagnosticProtocols[ProtocolId].Timeouts.InternalTimeout = DCCM_TIMEOUT_OFF;
  /* LEAVE critical section */
  SchM_Exit_Dccm_SCHM_DCCM_EXCLUSIVE_AREA_0();

  /* clean the state of the protocol */
  Dccm_DiagnosticProtocols[ProtocolId].PreparedToReceiveFunctionalResponse = FALSE;
  Dccm_DiagnosticProtocols[ProtocolId].ResponsePendingWasReceived = FALSE;
  if ( (Dccm_FunctionalRequestHelper.FunctionalRequestOngoingOnProtocolId == ProtocolId) /* The current communication protocol is in use for the single functional request allowed for SWC. */
      && (itWasTesterPresentInitiatedByDccm == TRUE) /* The current SendNotify is for a TesterPresent initiated by Dccm. */
      /*&& (Dccm_DiagnosticProtocols[ProtocolId].AddressingType == FUNCTIONAL_ADDRESSING)*/ /* XXX: really needed?: The protocol is for functional addressing. */
  )
  {
    /* Continue to wait for possible functional responses. */
    Dccm_DiagnosticProtocols[ProtocolId].Status = DCCM_DIAGNOSTIC_PROTOCOL_STATUS_RECEIVE;
  }
  else
  {
    Dccm_DiagnosticProtocols[ProtocolId].Status = DCCM_DIAGNOSTIC_PROTOCOL_STATUS_READY;
  }

  /* Special handling if the current protocol is the functional protocol where a functional request was sent by SWC. */
  if ( (Dccm_FunctionalRequestHelper.FunctionalRequestOngoingOnProtocolId == ProtocolId)
      && (itWasTesterPresentInitiatedByDccm == FALSE)
  )
  {
    /* clean-up all the physical protocols that are still waiting the "functional response" that will never come */
    /* Deviation MISRAC2012-1 <START> */
    if (
        (DCCM_FUNCREQ_SPRMIBTRUE_NOTIFY_PHYSPROTO == STD_ON)
        ||
        ( (DCCM_FUNCREQ_SPRMIBTRUE_NOTIFY_PHYSPROTO == STD_OFF)
          &&
          (
            ( (Dccm_FunctionalRequestHelper.isSuppressPosRspSaved == TRUE)
               && (Dccm_FunctionalRequestHelper.SuppressPosRsp == FALSE)
            )
            ||
            /* SPRMIB not saved, e.g.: functional request too short (maybe erroneous) that will trigger responses with NegativeResponseCodes. */
            (Dccm_FunctionalRequestHelper.isSuppressPosRspSaved == FALSE)
          )
        )
    )
    {
    /* Deviation TASKING-1 */
      for (PhysicalProtocolId = 0U; PhysicalProtocolId < DCCM_MAX_DIAGNOSTIC_PROTOCOLS; PhysicalProtocolId++)
      {
        if ( /* XXX is this really needed? check also the status of the protocol?: to be RECEIVING? */
            (Dccm_DiagnosticProtocols[PhysicalProtocolId].Status == DCCM_DIAGNOSTIC_PROTOCOL_STATUS_RECEIVE)
            /* PreparedToReceiveFunctionalResponse can be TRUE only on PHYSICAL_ADDRESSING (this is
             * because of the checks from Dccm_PrepareRxBufferForFuncReq()); */
            && (Dccm_DiagnosticProtocols[PhysicalProtocolId].PreparedToReceiveFunctionalResponse == TRUE)
        )
        {
#if (DCCM_P2CLIENT_ENABLED == STD_ON)
          if ((Dccm_FunctionalRequestHelper.isSuppressPosRspSaved == TRUE)
              && (Dccm_FunctionalRequestHelper.SuppressPosRsp == TRUE)
              /* the next condition is for the physical protocol */
              && (Dccm_DiagnosticProtocols[PhysicalProtocolId].ResponsePendingWasReceived == FALSE)
          )
          {
            Dccm_DiagnosticProtocols[PhysicalProtocolId].ResponseCode = DCCM_RSP_TIMEOUT_P2CLIENT_SPRMIB_TRUE;
          }
          else
          {
            Dccm_DiagnosticProtocols[PhysicalProtocolId].ResponseCode = DCCM_RSP_TIMEOUT_P2CLIENT;
          }
#elif (DCCM_P6CLIENT_ENABLED == STD_ON)
          /* Currently, P6Client is out of scope for functional request processing. */
          /* To be updated at the implementation for P6_Client/P6*_Client. */
          /*
          if ((Dccm_FunctionalRequestHelper.isSuppressPosRspSaved == TRUE)
              && (Dccm_FunctionalRequestHelper.SuppressPosRsp == TRUE)*/
              /* the next condition is for the physical protocol */
          /*    && (Dccm_DiagnosticProtocols[PhysicalProtocolId].ResponsePendingWasReceived == FALSE)
          )
          {
            Dccm_DiagnosticProtocols[PhysicalProtocolId].ResponseCode = DCCM_RSP_TIMEOUT_P6CLIENT_SPRMIB_TRUE;
          }
          else
          {
            Dccm_DiagnosticProtocols[PhysicalProtocolId].ResponseCode = DCCM_RSP_TIMEOUT_P6CLIENT;
          } */
#endif
          Dccm_DiagnosticProtocols[PhysicalProtocolId].Status = DCCM_DIAGNOSTIC_PROTOCOL_STATUS_SEND_NOTIFY;
          /* the functional protocols are all processed with higher priority: at this time,
           * the "for" above sets the timeout response for the physical protocols that are still waiting
           * the "functional response" that will never come.
           * the physical protocols are all processed with lower priority: at that time,
           * the timeout response codes that are set in the "for" above will be sent with the notification call-back.
           *  */
        }
      } /* for */
    }
    /* Deviation MISRAC2012-1 <STOP> */
    /* no functional request is on-going (ignoring the "keep-alive" functional valid TesterPresent) */
    Dccm_FunctionalRequestHelper = Dccm_FunctionalRequestHelperDefault;
  } /* if ( (Dccm_FunctionalRequestHelper.FunctionalRequestOngoingOnProtocolId==ProtocolId) && (itWasTesterPresentInitiatedByDccm==FALSE) */
}

#define DCCM_STOP_SEC_CODE
#include <Dccm_MemMap.h>

/*==================[end of file]============================================*/
