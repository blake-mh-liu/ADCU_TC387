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
 *  MISRAC2012-2) Deviated Rule: 13.5 (required)
 *  The right hand operand of a logical && or || operator shall not contain persistent side effects.
 *
 *  Reason:
 *  This violation is a false positive.
 *  The right hand operation does not contain persistent side effects. The usage of a macro is not
 *  interpreted correctly by the tool.
 *
 *  MISRAC2012-3) Deviated Rule: 17.2 (required)
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
#include <ComStack_Types.h>       /* AUTOSAR Communication Stack types */
#include <PduR_Internal_Static.h> /* Internal API (static part) */
#include <PduR_Api_Depend.h>      /* Public API (depend part) */

#if ((PDUR_ZERO_COST_OPERATION_TP == STD_OFF) && (PDUR_TPGATEWAY_SUPPORT == STD_ON))
#include <SchM_PduR.h>            /* Schedule Manager for module PduR */
#include <PduR_Lcfg.h>            /* Link-time configurable data */
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

FUNC(void, PDUR_CODE) PduR_GateTpTxConfirmation
(
   PduIdType GMPduId,
   NotifResultType Result
)
{
   PduR_GateTpSessionIndexType SessionIndex;

#if (PDUR_TPGWQUEUE_ENABLE == STD_ON)
   PduR_GateTpSessionIndexType NextSessionIndex = PDUR_NO_GATETP_SESSION_ASSIGNED;

   boolean CallLoTpTransmit = FALSE;

   /* PduInfo for Transmit */
   PduInfoType PduR_PduInfo;

   /* for check on preemption by TpTxConf, basically, the invalid value PDUR_NO_GATETP_QUEUEING_POSSIBLE
      can not be assigned to the TailIdx */
   uint8 TailIndexInUse = PDUR_NO_GATETP_QUEUEING_POSSIBLE;

   /* pointer to TP gateway session queue info */
   /* Deviation MISRAC2012-1 */
   CONSTP2VAR(PduR_GateTpQueueInfoType, AUTOMATIC, PDUR_VAR_CLEARED) pGateTpQueueInfo =
      PDUR_GET_RAM_ADDR(PduR_GateTpQueueInfoType, PduR_GConfigPtr->PduR_GateTpQueueInfoRef);

#if (PDUR_MULTICORE_SUPPORT == STD_ON)
       /* pointer to routing table */
   CONSTP2CONST(PduR_GTabTpTxType, AUTOMATIC, PDUR_APPL_CONST) pGTabTpTx =
      PDUR_GET_CONFIG_ADDR(PduR_GTabTpTxType, PduR_GConfigPtr->PduR_GTabTpConfig.GTabTxRef);

       /* pointer to routing table */
   CONSTP2CONST(PduR_RefToModuleAPI, AUTOMATIC, PDUR_APPL_CONST) pGTabTpApi =
      PDUR_GET_CONFIG_ADDR(PduR_RefToModuleAPI, PduR_GConfigPtr->PduR_GTabTpConfig.GTabTpApiRef);

   const PduIdType GMPduIdApi = GMPduId;
#endif /* if (PDUR_MULTICORE_SUPPORT == STD_ON) */
#endif /* if (PDUR_TPGWQUEUE_ENABLE == STD_ON) */

#if ((PDUR_TPGWQUEUE_ENABLE == STD_ON) || (PDUR_MULTICAST_TP_HIGHEST_WINS_STRATEGY == STD_ON))
   /* pointer to routing table */
   CONSTP2CONST(PduR_GTabTpRxType, AUTOMATIC, PDUR_APPL_CONST) pGTabTpRx =
      PDUR_GET_CONFIG_ADDR(PduR_GTabTpRxType, PduR_GConfigPtr->PduR_GTabTpConfig.GTabRxRef);
#endif

#if (PDUR_DEV_ERROR_DETECT == STD_ON)
   boolean CallDetReportError = FALSE;
   uint8 DetErrorCode = PDUR_E_INVALID_REQUEST;
#endif /* if (PDUR_DEV_ERROR_DETECT == STD_ON) */

   DBG_PDUR_GATETPTXCONFIRMATION_ENTRY(GMPduId, Result);

#if (PDUR_TPGWQUEUE_ENABLE == STD_ON) && (PDUR_MULTICORE_SUPPORT == STD_ON)
   /* overload with corrected GMPduIdRx, otherwise, input parameter is used directly */
   GMPduId = pGTabTpTx[GMPduId].GMPduIdRx;
#endif /* (PDUR_TPGWQUEUE_ENABLE == STD_ON) && (PDUR_MULTICORE_SUPPORT == STD_ON) */

   /* ENTER CRITICAL SECTION */
   SchM_Enter_PduR_SCHM_PDUR_EXCLUSIVE_AREA_0();

   /* get TP gateway session in use, second parameter is unused for disabled queuing */
   SessionIndex = PduR_GetGateTpSessionInUse(GMPduId, PDUR_GATETP_QUEUE_ELEMENT_TAIL);

   /* TpTxConfirmation called without preceding StartOfReception */
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
   if(SessionIndex == PDUR_NO_GATETP_SESSION_ASSIGNED)
   {
      CallDetReportError = TRUE;
      DetErrorCode = PDUR_E_INVALID_REQUEST;
   }
   else
#endif /* if (PDUR_DEV_ERROR_DETECT == STD_ON) */
   {
      /* pointer to TP gateway sessions */
      /* Deviation MISRAC2012-1 */
      CONSTP2VAR(PduR_GateTpSessionInfoType, AUTOMATIC, PDUR_VAR_CLEARED) pSessionInfos =
         PDUR_GET_RAM_ADDR(PduR_GateTpSessionInfoType, PduR_GConfigPtr->PduR_GateTpSessionInfoRef);

      uint8 ResultGetBitReceptFin;

      pSessionInfos[SessionIndex].PendTxConfCount--;

      /* abort transmission for negative Result */
      if (Result != NTFRSLT_OK)
      {
#if (PDUR_MULTICAST_TP_HIGHEST_WINS_STRATEGY == STD_ON)
         /* setting the abort bit is independent on highest wins strategy for routing on-the-fly only, not the direct gateway */
         if (pGTabTpRx[GMPduId].TpThreshold != PDUR_GATETPTHRESHOLD_DIRECT)
#endif /* if (PDUR_MULTICAST_TP_HIGHEST_WINS_STRATEGY == STD_ON) */
         {
            /* abort transmission */
            TS_AtomicSetBit_8(&pSessionInfos[SessionIndex].Status, PDUR_GATETP_ABORT_POS);
         }
      }

      /* last TpTxConfirmation of GMPduId without pending reception */
      TS_GetBit(&pSessionInfos[SessionIndex].Status, PDUR_GATETP_RECEPT_FIN_POS, uint8,
                ResultGetBitReceptFin);
      if((pSessionInfos[SessionIndex].PendTxConfCount == 0U) &&
         (ResultGetBitReceptFin > 0U))
      {
         /* release the queue tail and update tail to next queue element */
         PduR_ReleaseGateTpQueueElement(GMPduId, PDUR_GATETP_QUEUE_ELEMENT_TAIL);

         /* release TP gateway session for final call of TpTxConfirmation */
         PduR_ReleaseGateTpSession(&pSessionInfos[SessionIndex]);

#if (PDUR_TPGWQUEUE_ENABLE == STD_ON)
         /* get TP gateway session in use; unqueued PDU is not provided if Transmit conditions are not fulfilled */
         NextSessionIndex = PduR_GetGateTpSessionInUse(GMPduId, PDUR_GATETP_QUEUE_ELEMENT_TAIL);

         /* Transmit conditions fulfilled (meanwhile), but no Transmit made:
            - Session queued (Rx completed)
            - Session not queued (Rotf with Threshold reached) */
         if(NextSessionIndex != PDUR_NO_GATETP_SESSION_ASSIGNED)
         {
            const PduR_BufTpIndexType BufTpIndex = (PduR_BufTpIndexType)NextSessionIndex;

            /* pointer to TP buffer configurations */
            CONSTP2CONST(PduR_BufTpConfigType, AUTOMATIC, PDUR_APPL_CONST) pBufTpConfig =
               PDUR_GET_CONFIG_ADDR(PduR_BufTpConfigType, PduR_GConfigPtr->PduR_BufTpConfigRef);

            /* pointer to the first element of the TP buffer */
            CONSTP2VAR(uint8, AUTOMATIC, PDUR_VAR_CLEARED) pStartTpBuf =
               PDUR_GET_RAM_ADDR(uint8, pBufTpConfig[BufTpIndex].MemRef);

            /* setup PduInfo for Transmit */
            /* No explicit cast is necessary since PduR_PduLengthType and PduLengthType
             * are both fixed with uint16 by the Java generator. */
            PduR_PduInfo.SduLength = pSessionInfos[NextSessionIndex].TpSduLength;
            PduR_PduInfo.SduDataPtr = pStartTpBuf;

            CallLoTpTransmit = TRUE;

            /* get TailIdx for later check on preemption if still the same queue element is considered */
            TailIndexInUse = pGateTpQueueInfo[GMPduId].TailIdx;
         }
#endif /* (PDUR_TPGWQUEUE_ENABLE == STD_ON) */
      }
   } /* (SessionIndex != PDUR_NO_GATETP_SESSION_ASSIGNED) */

   /* EXIT CRITICAL SECTION */
   SchM_Exit_PduR_SCHM_PDUR_EXCLUSIVE_AREA_0();

#if (PDUR_TPGWQUEUE_ENABLE == STD_ON)
   if(CallLoTpTransmit)
   {
      boolean IsTxConfPending;

      /* pointer to TP gateway sessions */
      CONSTP2VAR(PduR_GateTpSessionInfoType, AUTOMATIC, PDUR_VAR_CLEARED) pSessionInfos =
         PDUR_GET_RAM_ADDR(PduR_GateTpSessionInfoType, PduR_GConfigPtr->PduR_GateTpSessionInfoRef);

      /* loop through queue until LoTp_Transmit passes or end of queue is reached */
      do{
         /* initialize iterator for all entries providing the same GMPduId */
         PduR_PduIdType GTabPos = GMPduId;

#if (PDUR_MULTICORE_SUPPORT == STD_ON)
         /* initialize iterator for all entries providing the same GMPduIdApi */
         PduR_PduIdType GTabMCorePos = pGTabTpTx[GMPduIdApi].TargetApiId;
#endif /* (PDUR_MULTICORE_SUPPORT == STD_ON) */

         /* provided local variable to ease readability of while condition */
         uint8 RemainingEntries;

         /* reset for each PDU before any destination is handled */
         IsTxConfPending = TRUE;

         /* ENTER CRITICAL SECTION */
         SchM_Enter_PduR_SCHM_PDUR_EXCLUSIVE_AREA_0();

         /* initiate counter to number of destination PDUs possible */
         /* !LINKSTO PduR.EB.DesignDecision.TpGatewayPendTxConfCount,1 */
         pSessionInfos[NextSessionIndex].PendTxConfCount = pGTabTpRx[GMPduId].RemainingEntries + 1U;

         /* EXIT CRITICAL SECTION */
         SchM_Exit_PduR_SCHM_PDUR_EXCLUSIVE_AREA_0();

         /* loop through all routing table entries matching the current GMPduId */
         do{

#if (PDUR_MULTICORE_SUPPORT == STD_OFF)
            /* reference to set of target Tp-module API-functions with single core */
            const PduR_RefToModuleAPI TargetAPIRef = pGTabTpRx[GTabPos].TargetModuleAPIRef;
#else
            /* reference to set of target Tp-module API-functions with multi core */
            const PduR_RefToModuleAPI TargetAPIRef = pGTabTpApi[GTabMCorePos];
#endif
            /* Deviation MISRAC2012-3 */
            Std_ReturnType RetVal = PduR_GateTpTransmit(GTabPos, NextSessionIndex, TargetAPIRef, &PduR_PduInfo, &RemainingEntries);

            /* development error detection handling for rejected transmit call () */
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
            if(RetVal != E_OK)
            {
               /* only rejected LoTp_Transmit call considered within PduR_GateTpTransmit */
               CallDetReportError = TRUE;
               DetErrorCode = PDUR_E_TP_TX_REQ_REJECTED;
            }
#else
            TS_PARAM_UNUSED(RetVal);
#endif /* if (PDUR_DEV_ERROR_DETECT == STD_ON) */

            GTabPos++;

#if (PDUR_MULTICORE_SUPPORT == STD_ON)
            GTabMCorePos++;
#endif /* (PDUR_MULTICORE_SUPPORT == STD_ON) */

         }while(RemainingEntries != PDUR_LAST_MULTICAST_ENTRY_OF_PDUID);

         /* ENTER CRITICAL SECTION */
         SchM_Enter_PduR_SCHM_PDUR_EXCLUSIVE_AREA_0();

         /* check for preemption of TpTxConfirmation by TpTxConfirmation, where session is already released */
         if(TailIndexInUse == pGateTpQueueInfo[GMPduId].TailIdx)
         {

            /* release TP gateway session when no further TpTxConfirmation is pending what can be caused by:
               - Transmit call(s) rejected
               - destination PDU disabled (via routing path group)
               - destination PDU is upper layer */
            if(pSessionInfos[NextSessionIndex].PendTxConfCount == 0U)
            {
               /* release assigned TP gateway session */
               PduR_ReleaseGateTpSession(&pSessionInfos[NextSessionIndex]);

               /* release tail of Tp gateway queue */
               PduR_ReleaseGateTpQueueElement(GMPduId, PDUR_GATETP_QUEUE_ELEMENT_TAIL);

               /* no further TpTxConfirmation is expected */
               IsTxConfPending = FALSE;

               /* get next TP gateway session in the queue */
               NextSessionIndex = PduR_GetGateTpSessionInUse(GMPduId, PDUR_GATETP_QUEUE_ELEMENT_TAIL);

               /* Further session is queued */
               if(NextSessionIndex != PDUR_NO_GATETP_SESSION_ASSIGNED)
               {
                  const PduR_BufTpIndexType BufTpIndex = (PduR_BufTpIndexType)NextSessionIndex;

                  /* pointer to TP buffer configurations */
                  CONSTP2CONST(PduR_BufTpConfigType, AUTOMATIC, PDUR_APPL_CONST) pBufTpConfig =
                     PDUR_GET_CONFIG_ADDR(PduR_BufTpConfigType, PduR_GConfigPtr->PduR_BufTpConfigRef);

                  /* pointer to the first element of the TP buffer */
                  CONSTP2VAR(uint8, AUTOMATIC, PDUR_VAR_CLEARED) pStartTpBuf =
                     PDUR_GET_RAM_ADDR(uint8, pBufTpConfig[BufTpIndex].MemRef);

                  /* setup PduInfo for Transmit */
                  /* No explicit cast is necessary since PduR_PduLengthType and PduLengthType
                   * are both fixed with uint16 by the Java generator. */
                  PduR_PduInfo.SduLength = pSessionInfos[NextSessionIndex].TpSduLength;
                  PduR_PduInfo.SduDataPtr = pStartTpBuf;

                  /* get TailIdx for later check on preemption if still the same queue element is considered */
                  TailIndexInUse = pGateTpQueueInfo[GMPduId].TailIdx;
               }
            }
            else
            {
               /* provide information on all finished LoTp_Transmit calls to PduR_GateTpCopyTxData */
               TS_AtomicSetBit_8(&pSessionInfos[NextSessionIndex].Status, PDUR_GATETP_TX_COMPLETE_POS);
            }
         }

         /* EXIT CRITICAL SECTION */
         SchM_Exit_PduR_SCHM_PDUR_EXCLUSIVE_AREA_0();

      }while((IsTxConfPending == FALSE) &&
             (NextSessionIndex != PDUR_NO_GATETP_SESSION_ASSIGNED));
   }
#endif /* (PDUR_TPGWQUEUE_ENABLE == STD_ON) */

   /* Conglomerate DET handling */
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
   if(CallDetReportError)
   {
      PDUR_DET_REPORT_ERROR(PDUR_SID_LOTP_TX_CONF, DetErrorCode);
   }
#endif /* if (PDUR_DEV_ERROR_DETECT == STD_ON) */

   DBG_PDUR_GATETPTXCONFIRMATION_EXIT(GMPduId, Result);
}

/* AUTOSAR Memory Mapping - end section for code */
#if (TS_MERGED_COMPILE == STD_OFF)
#define PDUR_STOP_SEC_CODE
#include <PduR_MemMap.h>
#endif

#else /* if (PDUR_ZERO_COST_OPERATION_TP == STD_OFF) && .. */

/* Avoid empty translation unit according to ISO C90 */
typedef void PduR_PreventEmptyTranslationUnit_GateTpTxConfirmationType;


/*==================[internal function definitions]=========================*/

#endif /* if (PDUR_ZERO_COST_OPERATION_TP == STD_OFF) && .. */
/*==================[end of file]===========================================*/
