/**
 * \file
 *
 * \brief AUTOSAR PduR
 *
 * This file contains the implementation of the AUTOSAR
 * module PduR.
 *
 * \version 5.3.55
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*
 *  MISRA-C:2012 Deviation List
 *
 *  MISRAC2012-1) Deviated Rule: 11.5 (advisory)
 *  A conversion should not be performed from pointer to void into pointer to
 *  object.
 *
 *  Reason:
 *  The memory routines are optimized for dealing with aligned memory sections.
 *
 *  MISRAC2012-2) Deviated Rule: 5.8 (required)
 *  Identifiers that define objects or functions with external linkage shall be unique.
 *
 *  Reason:
 *  This violation is a false positive.
 *  The tool does not recognize the following situation:
 *  The function identifier depends if the merge compile use
 *  case is enabled or not. The behavior is realized through a
 *  instrumented macro which enables the use case dependent
 *  function identifier.
 *
 *  MISRAC2012-3) Deviated Rule: 13.5 (required)
 *  The right hand operand of a logical && or || operator shall not contain persistent side effects.
 *
 *  Reason:
 *  This violation is a false positive.
 *  The right hand operation does not contain persistent side effects. The usage of a macro is not
 *  interpreted correctly by the tool.
 *
 *  MISRAC2012-4) Deviated Rule: 17.2 (required)
 *  Functions shall not call themselves, either directly or indirectly.
 *
 *  Reason:
 *  This is a false positive.
 *  The tool cannot identify the correct call sequence for function calls via function pointers.
 *  The reported functions are not calling themselves, either directly or indirectly.
 *
 */

/*==================[inclusions]============================================*/

#include <PduR_Trace.h>
#include <TSAutosar.h>            /* EB specific standard types */
#include <TSAtomic_Assign.h>      /* Atomic assignments from Base PlugIn */
#include <ComStack_Types.h>       /* AUTOSAR Communication Stack types */
#include <PduR_Types.h>           /* type definitions of PduR module */
#include <PduR_Internal_Static.h> /* Internal API (static part) */
#include <PduR_Api_Depend.h>      /* Public API (depend part) */
#include <PduR_Lcfg.h>            /* Link-time configurable data */

#if ((PDUR_ZERO_COST_OPERATION_TP == STD_OFF) && (PDUR_TPGATEWAY_SUPPORT == STD_ON))
#include <SchM_PduR.h>            /* Schedule Manager for module PduR */

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/* AUTOSAR Memory Mapping - start section for code */
#if (TS_MERGED_COMPILE == STD_OFF)
#define PDUR_START_SEC_CODE
#include <PduR_MemMap.h>
#endif

/* Deviation MISRAC2012-2 */
TS_MOD_PRIV_DEFN FUNC(void, PDUR_CODE) PduR_ReleaseGateTpSession
(
   P2VAR(PduR_GateTpSessionInfoType, AUTOMATIC, PDUR_VAR_CLEARED) pSessionInfo
)
{
   DBG_PDUR_RELEASEGATETPSESSION_ENTRY(pSessionInfo);

   TS_AtomicAssign8(pSessionInfo->Status, (uint8)PDUR_GATETP_RST_STATUS_MSK);
   TS_AtomicAssign8(pSessionInfo->PendTxConfCount, (uint8)PDUR_GATETP_NO_PEND_TXCONF_MSK);
   pSessionInfo->RxWriteIndex = 0U;
   pSessionInfo->AvailableBufferSize = PDUR_TPBUFFER_LENGTH_ZERO;
   pSessionInfo->TpSduLength = PDUR_SDU_LENGTH_ZERO;

   DBG_PDUR_RELEASEGATETPSESSION_EXIT(pSessionInfo);
}


/* Deviation MISRAC2012-2 */
TS_MOD_PRIV_DEFN FUNC(Std_ReturnType, PDUR_CODE) PduR_GateTpTransmit
(
   PduR_PduIdType GMPduId,
   PduR_GateTpSessionIndexType SessionIndex,
   PduR_RefToModuleAPI TargetAPIRef,
   P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr,
   P2VAR(uint8, AUTOMATIC, PDUR_VAR_CLEARED) RemainingEntries
)
{
   /* return value */
   Std_ReturnType RetVal;

   /* pointer to routing table */
   CONSTP2CONST(PduR_GTabTpRxType, AUTOMATIC, PDUR_APPL_CONST) pGTabTpRx =
      PDUR_GET_CONFIG_ADDR(PduR_GTabTpRxType, PduR_GConfigPtr->PduR_GTabTpConfig.GTabRxRef);

   /* pointer to TP gateway sessions */
   /* Deviation MISRAC2012-1 */
   CONSTP2VAR(PduR_GateTpSessionInfoType, AUTOMATIC, PDUR_VAR_CLEARED) pSessionInfos =
      PDUR_GET_RAM_ADDR(PduR_GateTpSessionInfoType, PduR_GConfigPtr->PduR_GateTpSessionInfoRef);

   DBG_PDUR_GATETPTRANSMIT_ENTRY(GMPduId, SessionIndex, TargetAPIRef, PduInfoPtr, RemainingEntries);

#if (PDUR_ROUTINGPATHGROUPS_SUPPORT == STD_ON)
   /* destination is either enabled or not referenced by a routing path group,
       Note: Order of OR condition on purpose for faster evaluation and preventing call
       of PduR_IsRoutingPathGroupEnabled with PDUR_ROUTINGPATHGROUP_GO_THROUGH_ID */
   /* Deviation MISRAC2012-3 */
   if((pGTabTpRx[GMPduId].RPathGroupId == PDUR_ROUTINGPATHGROUP_GO_THROUGH_ID) ||
       (PduR_IsRoutingPathGroupEnabled(pGTabTpRx[GMPduId].RPathGroupId) != FALSE))
#endif /* (PDUR_ROUTINGPATHGROUPS_SUPPORT == STD_ON) */
   {
      /* get pointer to Transmit function */
      const PduR_TransmitFpType TransmitFp = PduR_TpModuleAPI[TargetAPIRef].TpTransmit;

      /* get target PDU ID to Transmit function from routing table */
      const PduR_PduIdType TargetPduId = pGTabTpRx[GMPduId].TargetPduId;

       /* initialize to check while condition */
      *RemainingEntries = pGTabTpRx[GMPduId].RemainingEntries;

      /* Deviation MISRAC2012-4 */
      /* call Transmit function */
      RetVal = TransmitFp(TargetPduId, PduInfoPtr);

      /* ENTER CRITICAL SECTION */
      SchM_Enter_PduR_SCHM_PDUR_EXCLUSIVE_AREA_0();

      /* handle rejected Transmit call (PduR_GateTpUpReception always returns E_OK) */
      if(RetVal != E_OK)
      {
         /* transmission failed, no TpTxConfirmation expected */
         pSessionInfos[SessionIndex].PendTxConfCount--;

#if (PDUR_MULTICAST_TP_HIGHEST_WINS_STRATEGY == STD_OFF)
         /* indicate abort of transmission to CopyTxData */
         TS_AtomicSetBit_8(&pSessionInfos[SessionIndex].Status, PDUR_GATETP_ABORT_POS);
#endif /* if (PDUR_MULTICAST_TP_HIGHEST_WINS_STRATEGY == STD_OFF) */

      }

#if(PDUR_MULTICAST_LOTPTOUP_SUPPORT == STD_ON)
      /* for upper layer only */
      if((*RemainingEntries == PDUR_LAST_MULTICAST_ENTRY_OF_PDUID) &&
         (PDUR_GATETP_CALL_UPPER_LAYER(TargetAPIRef)))
      {
         /* no TpTxConfirmation expected */
         pSessionInfos[SessionIndex].PendTxConfCount--;
      }
#endif

      /* EXIT CRITICAL SECTION */
      SchM_Exit_PduR_SCHM_PDUR_EXCLUSIVE_AREA_0();

   }
#if (PDUR_ROUTINGPATHGROUPS_SUPPORT == STD_ON)
   /* disabled destination PDU */
   else
   {

      /* ENTER CRITICAL SECTION */
      SchM_Enter_PduR_SCHM_PDUR_EXCLUSIVE_AREA_0();

      /* destination PDU disabled, no TxConfirmation expected */
      pSessionInfos[SessionIndex].PendTxConfCount--;

      /* EXIT CRITICAL SECTION */
      SchM_Exit_PduR_SCHM_PDUR_EXCLUSIVE_AREA_0();

      /* initialize to check while condition */
      *RemainingEntries = pGTabTpRx[GMPduId].RemainingEntries;

      RetVal = E_OK;
   }
#endif /* (PDUR_ROUTINGPATHGROUPS_SUPPORT == STD_ON) */

   DBG_PDUR_GATETPTRANSMIT_EXIT(RetVal, GMPduId, SessionIndex, TargetAPIRef, PduInfoPtr, RemainingEntries);

   return RetVal;
}


/* Deviation MISRAC2012-2 */
TS_MOD_PRIV_DEFN FUNC(void, PDUR_CODE) PduR_ReleaseGateTpSessionQueue
(
   PduR_PduIdType GMPduId
)
{
   /* pointer to routing table */
   CONSTP2CONST(PduR_GTabTpRxType, AUTOMATIC, PDUR_APPL_CONST) pGTabTpRx =
      PDUR_GET_CONFIG_ADDR(PduR_GTabTpRxType, PduR_GConfigPtr->PduR_GTabTpConfig.GTabRxRef);

   /* pointer to queue of TP gateway sessions */
   /* Deviation MISRAC2012-1 */
   CONSTP2VAR(PduR_GateTpSessionIndexType, AUTOMATIC, PDUR_VAR_CLEARED) pGateTpSessionIndex =
      PDUR_GET_RAM_ADDR(PduR_GateTpSessionIndexType, pGTabTpRx[GMPduId].SessionQueueMemRef);

   PduR_GateTpQueueIndexType QueueIndex;

   PduR_GateTpQueueIndexType QueueIndexMax;

   DBG_PDUR_RELEASEGATETPSESSIONQUEUE_ENTRY(GMPduId);

   {
#if (PDUR_TPGWQUEUE_ENABLE == STD_ON)
      QueueIndexMax = pGTabTpRx[GMPduId].SessionQueueDepth;
#else
      QueueIndexMax = PDUR_GATETPQUEUE_DEPTH_ONE;
#endif /* (PDUR_TPGWQUEUE_ENABLE == STD_ON)  */

      for(QueueIndex = 0U; QueueIndex < QueueIndexMax; QueueIndex++)
      {
         pGateTpSessionIndex[QueueIndex] =  PDUR_NO_GATETP_SESSION_ASSIGNED;
      }
   }

   DBG_PDUR_RELEASEGATETPSESSIONQUEUE_EXIT(GMPduId);
}


/* Deviation MISRAC2012-2 */
TS_MOD_PRIV_DEFN FUNC(void, PDUR_CODE) PduR_ReleaseGateTpQueueElement
(
   PduR_PduIdType GMPduId,
   boolean QueueElement
)
{
   /* pointer to routing table */
   CONSTP2CONST(PduR_GTabTpRxType, AUTOMATIC, PDUR_APPL_CONST) pGTabTpRx =
      PDUR_GET_CONFIG_ADDR(PduR_GTabTpRxType, PduR_GConfigPtr->PduR_GTabTpConfig.GTabRxRef);

   /* pointer to queue of TP gateway sessions */
   /* Deviation MISRAC2012-1 */
   CONSTP2VAR(PduR_GateTpSessionIndexType, AUTOMATIC, PDUR_VAR_CLEARED) pGateTpSessionIndex =
      PDUR_GET_RAM_ADDR(PduR_GateTpSessionIndexType, pGTabTpRx[GMPduId].SessionQueueMemRef);

   PduR_GateTpQueueIndexType CurQueueIndex = PDUR_GATETPQUEUE_FIRSTINDEX;

   DBG_PDUR_RELEASEGATETPQUEUEELEMENT_ENTRY(GMPduId, QueueElement);

#if (PDUR_TPGWQUEUE_ENABLE == STD_ON)
   /* Handle calls from TxConfirmation, PduR_ReleaseGateTpQueueElement shall not be called with queue depth one
      as session would be released */
   if (pGTabTpRx[GMPduId].SessionQueueDepth > PDUR_GATETPQUEUE_DEPTH_ONE)
   {
      PduR_GateTpQueueIndexType NextQueueIndex = PDUR_GATETPQUEUE_FIRSTINDEX;

      /* pointer to TP gateway session queue info */
      /* Deviation MISRAC2012-1 */
      CONSTP2VAR(PduR_GateTpQueueInfoType, AUTOMATIC, PDUR_VAR_CLEARED) pGateTpQueueInfo =
         PDUR_GET_RAM_ADDR(PduR_GateTpQueueInfoType, PduR_GConfigPtr->PduR_GateTpQueueInfoRef);

      if(QueueElement == PDUR_GATETP_QUEUE_ELEMENT_HEAD)
      {
         CurQueueIndex = pGateTpQueueInfo[GMPduId].HeadIdx;
         NextQueueIndex = (CurQueueIndex + 1U) % pGTabTpRx[GMPduId].SessionQueueDepth;

         /* update session queue info with next queue index to use for reception */
         if(NextQueueIndex != pGateTpQueueInfo[GMPduId].TailIdx)
         {
            pGateTpQueueInfo[GMPduId].HeadIdx = NextQueueIndex;
         }
         else
         {
            /* no free queue element available */
            pGateTpQueueInfo[GMPduId].HeadIdx = PDUR_NO_GATETP_QUEUEING_POSSIBLE;
         }
      }
      else
      {
         CurQueueIndex = pGateTpQueueInfo[GMPduId].TailIdx;
         NextQueueIndex = (CurQueueIndex + 1U) % pGTabTpRx[GMPduId].SessionQueueDepth;

         /* release TP gateway session */
         pGateTpSessionIndex[CurQueueIndex] =  PDUR_NO_GATETP_SESSION_ASSIGNED;

         /* update session queue info with next queue index to use for transmission */
         pGateTpQueueInfo[GMPduId].TailIdx = NextQueueIndex;

         /* update head of fully occupied queue with the new free position */
         if(pGateTpQueueInfo[GMPduId].HeadIdx == PDUR_NO_GATETP_QUEUEING_POSSIBLE)
         {
            pGateTpQueueInfo[GMPduId].HeadIdx = CurQueueIndex;
         }
      }
   }
   else
#endif /* (PDUR_TPGWQUEUE_ENABLE == STD_ON)  */
   {
     TS_PARAM_UNUSED(QueueElement);

     /* release TP gateway session */
     pGateTpSessionIndex[CurQueueIndex] =  PDUR_NO_GATETP_SESSION_ASSIGNED;
   }


   DBG_PDUR_RELEASEGATETPQUEUEELEMENT_EXIT(GMPduId, QueueElement);
}


/* Deviation MISRAC2012-2 */
TS_MOD_PRIV_DEFN FUNC(void, PDUR_CODE) PduR_ResetGateTpQueueHead
(
   PduR_PduIdType GMPduId
)
{
   /* pointer to routing table */
   CONSTP2CONST(PduR_GTabTpRxType, AUTOMATIC, PDUR_APPL_CONST) pGTabTpRx =
      PDUR_GET_CONFIG_ADDR(PduR_GTabTpRxType, PduR_GConfigPtr->PduR_GTabTpConfig.GTabRxRef);

   /* pointer to queue of TP gateway sessions */
   /* Deviation MISRAC2012-1 */
   CONSTP2VAR(PduR_GateTpSessionIndexType, AUTOMATIC, PDUR_VAR_CLEARED) pGateTpSessionIndex =
      PDUR_GET_RAM_ADDR(PduR_GateTpSessionIndexType, pGTabTpRx[GMPduId].SessionQueueMemRef);

   PduR_GateTpQueueIndexType QueueIndex = PDUR_GATETPQUEUE_FIRSTINDEX;

   DBG_PDUR_RESETGATETPQUEUEHEAD_ENTRY(GMPduId);

#if (PDUR_TPGWQUEUE_ENABLE == STD_ON)
   if (pGTabTpRx[GMPduId].SessionQueueDepth > PDUR_GATETPQUEUE_DEPTH_ONE)
   {
      /* pointer to TP gateway session queue info */
      /* Deviation MISRAC2012-1 */
      CONSTP2VAR(PduR_GateTpQueueInfoType, AUTOMATIC, PDUR_VAR_CLEARED) pGateTpQueueInfo =
         PDUR_GET_RAM_ADDR(PduR_GateTpQueueInfoType, PduR_GConfigPtr->PduR_GateTpQueueInfoRef);

      QueueIndex = pGateTpQueueInfo[GMPduId].HeadIdx;
   }
#endif /* (PDUR_TPGWQUEUE_ENABLE == STD_ON)  */

   /* release TP gateway session */
   pGateTpSessionIndex[QueueIndex] =  PDUR_NO_GATETP_SESSION_ASSIGNED;

   DBG_PDUR_RESETGATETPQUEUEHEAD_EXIT(GMPduId);
}


/* Deviation MISRAC2012-2 */
TS_MOD_PRIV_DEFN FUNC(PduR_GateTpSessionIndexType, PDUR_CODE) PduR_GetGateTpSessionInUse
(
   PduR_PduIdType GMPduId,
   boolean QueueElement
)
{
   /* pointer to routing table */
   CONSTP2CONST(PduR_GTabTpRxType, AUTOMATIC, PDUR_APPL_CONST) pGTabTpRx =
      PDUR_GET_CONFIG_ADDR(PduR_GTabTpRxType, PduR_GConfigPtr->PduR_GTabTpConfig.GTabRxRef);

   /* pointer to queue of TP gateway sessions */
   /* Deviation MISRAC2012-1 */
   CONSTP2VAR(PduR_GateTpSessionIndexType, AUTOMATIC, PDUR_VAR_CLEARED) pGateTpSessionIndex =
      PDUR_GET_RAM_ADDR(PduR_GateTpSessionIndexType, pGTabTpRx[GMPduId].SessionQueueMemRef);

   PduR_GateTpSessionIndexType SessionIndexRetVal;

   DBG_PDUR_GETGATETPSESSIONINUSE_ENTRY(GMPduId, QueueElement);

#if (PDUR_TPGWQUEUE_ENABLE == STD_ON)
   if (pGTabTpRx[GMPduId].SessionQueueDepth > PDUR_GATETPQUEUE_DEPTH_ONE)
   {
      /* pointer to TP gateway session queue info */
      /* Deviation MISRAC2012-1 */
      CONSTP2VAR(PduR_GateTpQueueInfoType, AUTOMATIC, PDUR_VAR_CLEARED) pGateTpQueueInfo =
         PDUR_GET_RAM_ADDR(PduR_GateTpQueueInfoType, PduR_GConfigPtr->PduR_GateTpQueueInfoRef);

      if(QueueElement == PDUR_GATETP_QUEUE_ELEMENT_HEAD)
      {
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
         /* PduR API called irregularly while queue is blocked completely */
         if( pGateTpQueueInfo[GMPduId].HeadIdx == PDUR_NO_GATETP_QUEUEING_POSSIBLE )
         {
            SessionIndexRetVal = PDUR_NO_GATETP_SESSION_ASSIGNED;
         }
         else
#endif /* if (PDUR_DEV_ERROR_DETECT == STD_ON) */
         {
           /* queued session on Rx side */
           SessionIndexRetVal = pGateTpSessionIndex[pGateTpQueueInfo[GMPduId].HeadIdx];
         }
      }
      else
      {
         /* since the TailIdx is not allowed to be set to an invalid value,
            some cases need to be considered separate to return the proper session index,
            especially, when TpTxConfirmation wants to call Transmit for the next PDU which is not completely received */

         /* conditions that allow no session assignment on Tx side by TailIdx, i.e. no (successful) Transmit call
            - no PDU in the queue AND
              - no incoming PDU OR
              - incoming PDU that fulfills not the Transmit criteria:
                rotf: TpThreshold not reached,
                      TpThreshold reached at time where a transmission was already ongoing, meanwhile completed
                dir:  no single Transmit called (PendTxConfCount = 0, holds until First call of Transmit in TpRxIndication,
                         better than set PDUR_GATETP_RECEPT_FIN_POS at the beginning of the TpRxIndication)
                         Note: PDUR_GATETP_TX_COMPLETE_POS set after all Transmits are called */

         /* no PDU in the queue (HeadIdx = TailIdx) */
         if(PduR_GateTpNoSessionQueued(GMPduId))
         {
            /* pointer to TP gateway sessions */
            CONSTP2VAR(PduR_GateTpSessionInfoType, AUTOMATIC, PDUR_VAR_CLEARED) pSessionInfos =
               PDUR_GET_RAM_ADDR(PduR_GateTpSessionInfoType, PduR_GConfigPtr->PduR_GateTpSessionInfoRef);

            /* API on Tx side called, but no reception of a new PDU has started */
            if(pGateTpSessionIndex[pGateTpQueueInfo[GMPduId].HeadIdx] == PDUR_NO_GATETP_SESSION_ASSIGNED)
            {
               /* no session is available at Tx side */
               SessionIndexRetVal = PDUR_NO_GATETP_SESSION_ASSIGNED;
            }
            /* API on Tx side called and reception of a new PDU has started already */
            else
            {

               /* reception of a new PDU has started, but no Transmit of considered PDU was sent:
                  - Rx sequence up to called TpRxIndication, but no Transmission was started
                  - Threshold not reached (for rotf only) */
               if(pSessionInfos[pGateTpSessionIndex[pGateTpQueueInfo[GMPduId].HeadIdx]].PendTxConfCount == 0U)
               {
                  /* no session is available at Tx side */
                  SessionIndexRetVal = PDUR_NO_GATETP_SESSION_ASSIGNED;
               }
               /* reception of a new PDU has started and Transmit of considered PDU was sent:
                  Threshold was reached during ongoing transmission (for routing on-the-fly only),
                  Transmit called by the CopyRxData itself in checking the Threshold each time,
                  TailIdx is released for getting the session index */
               else
               {
                  SessionIndexRetVal = pGateTpSessionIndex[pGateTpQueueInfo[GMPduId].TailIdx];
               }
            }
         }
         /* at least a single PDU is queued */
         else
         {
           /* unfinished session on Tx side */
           SessionIndexRetVal = pGateTpSessionIndex[pGateTpQueueInfo[GMPduId].TailIdx];
         }
      }
   }
   else
#endif /* (PDUR_TPGWQUEUE_ENABLE == STD_ON)  */
   {
     TS_PARAM_UNUSED(QueueElement);

     SessionIndexRetVal = pGateTpSessionIndex[PDUR_GATETPQUEUE_FIRSTINDEX];
   }

   DBG_PDUR_GETGATETPSESSIONINUSE_EXIT(SessionIndexRetVal, GMPduId, QueueElement);

   return SessionIndexRetVal;
}

/* Deviation MISRAC2012-2 */
TS_MOD_PRIV_DEFN FUNC(PduR_PduLengthType, PDUR_CODE) PduR_CalcAvailableDataSize
(
   PduR_GateTpSessionIndexType SessionIndex
)
{
   const PduR_BufTpIndexType BufTpIndex = (PduR_BufTpIndexType)SessionIndex;
   PduR_PduLengthType DataSize;

   /* pointer to TP gateway sessions */
   /* Deviation MISRAC2012-1 */
   CONSTP2VAR(PduR_GateTpSessionInfoType, AUTOMATIC, PDUR_VAR_CLEARED) pGateTpSessions =
      PDUR_GET_RAM_ADDR(PduR_GateTpSessionInfoType, PduR_GConfigPtr->PduR_GateTpSessionInfoRef);

   /* pointer to TP buffer configurations */
   CONSTP2CONST(PduR_BufTpConfigType, AUTOMATIC, PDUR_APPL_CONST) pBufTpConfig =
      PDUR_GET_CONFIG_ADDR(PduR_BufTpConfigType, PduR_GConfigPtr->PduR_BufTpConfigRef);

   DBG_PDUR_CALCAVAILABLEDATASIZE_ENTRY(SessionIndex);

   DataSize = pBufTpConfig[BufTpIndex].Length - pGateTpSessions[SessionIndex].AvailableBufferSize;

   DBG_PDUR_CALCAVAILABLEDATASIZE_EXIT(DataSize, SessionIndex);

   return DataSize;
}


/* Deviation MISRAC2012-2 */
TS_MOD_PRIV_DEFN FUNC(boolean, PDUR_CODE) PduR_GateTpNoSessionQueued
(
   PduR_PduIdType GMPduId
)
{
   boolean RetVal = FALSE;  /* return value if at least one PDU is queued */

   DBG_PDUR_GATETPNOSESSIONQUEUED_ENTRY(GMPduId);

#if (PDUR_TPGWQUEUE_ENABLE == STD_ON)
   {
     /* pointer to routing table */
     CONSTP2CONST(PduR_GTabTpRxType, AUTOMATIC, PDUR_APPL_CONST) pGTabTpRx =
        PDUR_GET_CONFIG_ADDR(PduR_GTabTpRxType, PduR_GConfigPtr->PduR_GTabTpConfig.GTabRxRef);

     if (pGTabTpRx[GMPduId].SessionQueueDepth > PDUR_GATETPQUEUE_DEPTH_ONE)
     {
        /* pointer to TP gateway session queue info */
        /* Deviation MISRAC2012-1 */
        CONSTP2VAR(PduR_GateTpQueueInfoType, AUTOMATIC, PDUR_VAR_CLEARED) pGateTpQueueInfo =
           PDUR_GET_RAM_ADDR(PduR_GateTpQueueInfoType, PduR_GConfigPtr->PduR_GateTpQueueInfoRef);

        /* the invalid value PDUR_NO_GATETP_QUEUEING_POSSIBLE can not be assigned to the TailIdx */
        if(pGateTpQueueInfo[GMPduId].HeadIdx == pGateTpQueueInfo[GMPduId].TailIdx)
        {
           RetVal = TRUE;
        }
     }
     else
     {
       RetVal = TRUE;
     }
   }
#else
   TS_PARAM_UNUSED(GMPduId);

   RetVal = TRUE;
#endif /* (PDUR_TPGWQUEUE_ENABLE == STD_ON)  */

   DBG_PDUR_GATETPNOSESSIONQUEUED_EXIT(RetVal, GMPduId);

   return RetVal;
}


/* Deviation MISRAC2012-2 */
TS_MOD_PRIV_DEFN FUNC(PduR_GateTpQueueIndexType, PDUR_CODE) PduR_GateTpGetSessionQueueHeadIndex
(
   PduR_PduIdType GMPduId
)
{
   PduR_GateTpQueueIndexType QueueHeadIndex = PDUR_GATETPQUEUE_FIRSTINDEX;

   DBG_PDUR_GATETPGETSESSIONQUEUEHEADINDEX_ENTRY(GMPduId);

#if (PDUR_TPGWQUEUE_ENABLE == STD_ON)
   {
      /* pointer to routing table */
      CONSTP2CONST(PduR_GTabTpRxType, AUTOMATIC, PDUR_APPL_CONST) pGTabTpRx =
         PDUR_GET_CONFIG_ADDR(PduR_GTabTpRxType, PduR_GConfigPtr->PduR_GTabTpConfig.GTabRxRef);

      if (pGTabTpRx[GMPduId].SessionQueueDepth > PDUR_GATETPQUEUE_DEPTH_ONE)
      {
         /* pointer to TP gateway session queue info */
         /* Deviation MISRAC2012-1 */
         CONSTP2VAR(PduR_GateTpQueueInfoType, AUTOMATIC, PDUR_VAR_CLEARED) pGateTpQueueInfo =
            PDUR_GET_RAM_ADDR(PduR_GateTpQueueInfoType, PduR_GConfigPtr->PduR_GateTpQueueInfoRef);

         QueueHeadIndex = pGateTpQueueInfo[GMPduId].HeadIdx;
      }
   }
#else
   TS_PARAM_UNUSED(GMPduId);
#endif /* (PDUR_TPGWQUEUE_ENABLE == STD_ON)  */

   DBG_PDUR_GATETPGETSESSIONQUEUEHEADINDEX_EXIT(QueueHeadIndex, GMPduId);

   return QueueHeadIndex;
}


/* Deviation MISRAC2012-2 */
TS_MOD_PRIV_DEFN FUNC(void, PDUR_CODE) PduR_GateTpSetSessionQueueHeadIndex
(
   PduR_PduIdType GMPduId,
   PduR_GateTpQueueIndexType QueueHeadIndex
)
{
   DBG_PDUR_GATETPSETSESSIONQUEUEHEADINDEX_ENTRY(GMPduId, QueueHeadIndex);

#if (PDUR_TPGWQUEUE_ENABLE == STD_ON)
   {
      /* pointer to routing table */
      CONSTP2CONST(PduR_GTabTpRxType, AUTOMATIC, PDUR_APPL_CONST) pGTabTpRx =
         PDUR_GET_CONFIG_ADDR(PduR_GTabTpRxType, PduR_GConfigPtr->PduR_GTabTpConfig.GTabRxRef);

      /* pointer to TP gateway session queue info */
      /* Deviation MISRAC2012-1 */
      CONSTP2VAR(PduR_GateTpQueueInfoType, AUTOMATIC, PDUR_VAR_CLEARED) pGateTpQueueInfo =
         PDUR_GET_RAM_ADDR(PduR_GateTpQueueInfoType, PduR_GConfigPtr->PduR_GateTpQueueInfoRef);

      if (pGTabTpRx[GMPduId].SessionQueueDepth > PDUR_GATETPQUEUE_DEPTH_ONE)
      {
         pGateTpQueueInfo[GMPduId].HeadIdx = QueueHeadIndex;
      }
      else
      {
         pGateTpQueueInfo[GMPduId].HeadIdx = PDUR_GATETPQUEUE_FIRSTINDEX;
      }
   }
#else
   TS_PARAM_UNUSED(GMPduId);
   TS_PARAM_UNUSED(QueueHeadIndex);
#endif /* (PDUR_TPGWQUEUE_ENABLE == STD_ON)  */

   DBG_PDUR_GATETPSETSESSIONQUEUEHEADINDEX_EXIT(GMPduId, QueueHeadIndex);
}


#if (PDUR_TPGWQUEUE_AND_NTO1ROUTING_ENABLED == STD_ON)
/* Deviation MISRAC2012-2 */
TS_MOD_PRIV_DEFN FUNC(boolean, PDUR_CODE) PduR_IsGateTpSessionInUse
(
    PduR_PduIdType GMPduId,
    PduR_GateTpQueueIndexType QueueIndex
)
{
  boolean isSessionInUse;

  /* pointer to routing table */
  CONSTP2CONST(PduR_GTabTpRxType, AUTOMATIC, PDUR_APPL_CONST) pGTabTpRx =
      PDUR_GET_CONFIG_ADDR(PduR_GTabTpRxType, PduR_GConfigPtr->PduR_GTabTpConfig.GTabRxRef);

  /* pointer to queue of TP gateway sessions */
  /* Deviation MISRAC2012-1 */
  CONSTP2VAR(PduR_GateTpSessionIndexType, AUTOMATIC, PDUR_VAR_CLEARED) pGateTpSessionIndex =
      PDUR_GET_RAM_ADDR(PduR_GateTpSessionIndexType, pGTabTpRx[GMPduId].SessionQueueMemRef);

  DBG_PDUR_ISGATETPSESSIONINUSE_ENTRY(GMPduId, QueueElement);

  /* PduR API called irregularly while queue is blocked completely */
  if( QueueIndex == PDUR_NO_GATETP_QUEUEING_POSSIBLE )
  {
    isSessionInUse = FALSE;
  }
  else
  {
    isSessionInUse = (PDUR_NO_GATETP_SESSION_ASSIGNED != pGateTpSessionIndex[QueueIndex]);
  }

  DBG_PDUR_ISGATETPSESSIONINUSE_EXIT(SessionIndex, GMPduId, QueueElement);

  return isSessionInUse;
}


#if (PDUR_MULTICORE_SUPPORT == STD_ON)
/* Deviation MISRAC2012-2 */
TS_MOD_PRIV_DEFN FUNC(PduR_PduIdType, PDUR_CODE) PduR_GetGMPduIdTxFromGMPduIdRx
(
    PduR_PduIdType GMPduIdRx
)
{
  PduR_PduIdType GMPduIdTx = 0U;

  /* pointer to routing table */
  CONSTP2CONST(PduR_GTabTpTxType, AUTOMATIC, PDUR_APPL_CONST) pGTabTpTx =
    PDUR_GET_CONFIG_ADDR(PduR_GTabTpTxType, PduR_GConfigPtr->PduR_GTabTpConfig.GTabTxRef);

  DBG_PDUR_GETGMPDUIDTXFROMGMPDUIDRX_ENTRY(GMPduIdRx);

  /* Since 1:1 gateway routing paths are considered only, each GMPduIdRx is part of the table */
  while(GMPduIdRx != pGTabTpTx[GMPduIdTx].GMPduIdRx)
  {
    GMPduIdTx++;
  };

  DBG_PDUR_GETGMPDUIDTXFROMGMPDUIDRX_EXIT(GMPduIdTx, GMPduIdRx);

  return GMPduIdTx;
}
#endif /* #if (PDUR_MULTICORE_SUPPORT == STD_ON) */
#endif /* (PDUR_TPGWQUEUE_AND_NTO1ROUTING_ENABLED == STD_ON) */

/* AUTOSAR Memory Mapping - end section for code */
#if (TS_MERGED_COMPILE == STD_OFF)
#define PDUR_STOP_SEC_CODE
#include <PduR_MemMap.h>
#endif

#else /* if (PDUR_ZERO_COST_OPERATION_TP == STD_OFF) && .. */

/* Avoid empty translation unit according to ISO C90 */
typedef void PduR_PreventEmptyTranslationUnit_GateTpType;


/*==================[internal function definitions]=========================*/

#endif /* if (PDUR_ZERO_COST_OPERATION_TP == STD_OFF) && .. */
/*==================[end of file]===========================================*/
