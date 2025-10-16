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

/* MISRA-C:2012 Deviation List
 *
 *  MISRAC2012-1) Deviated Rule: 17.2 (required)
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

#if ((PDUR_MULTICAST_LOTPTOUP_SUPPORT == STD_ON) && (PDUR_ZERO_COST_OPERATION_TP == STD_OFF))
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

FUNC(Std_ReturnType, PDUR_CODE) PduR_GateTpUpReception
(
   PduIdType RxPduId,
   P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr,
   PduR_RefToModuleAPI TargetAPIRef
)
{
   /* initialize return value */
   BufReq_ReturnType RetVal;

   /* provided for the upper layer's output parameter, initialize to 0 for higher robustness */
   PduLengthType BufferSize = 0U;

   /* pointer to StartOfReception function of upper layer */
   const PduR_StrtOfRcptnFpType StrtOfRcptnFp = PduR_TpModuleAPI[TargetAPIRef].TpStartOfReception;

   /* pointer to CopyRxData function of upper layer  */
   const PduR_CopyRxDataFpType CopyRxDataFp = PduR_TpModuleAPI[TargetAPIRef].TpCopyRxData;

   /* pointer to RxIndication function of upper layer  */
   const PduR_TpRxIndFpType RxIndFp = PduR_TpModuleAPI[TargetAPIRef].TpRxIndication;

   /* TpSduLength corresponds to SduLength since the complete I-PDU is forwarded */
   const PduLengthType TpSduLength = PduInfoPtr->SduLength;

   DBG_PDUR_GATETPUPRECEPTION_ENTRY(RxPduId, PduInfoPtr, TargetAPIRef);

   /* Deviation MISRAC2012-1 */
   /* call StartOfReception function  */
   RetVal = StrtOfRcptnFp(RxPduId, TpSduLength, &BufferSize);

   /* stop interaction with Up module if not ok is returned */
   if(RetVal == BUFREQ_OK)
   {
      /* buffer of upper layer holds complete I-PDU */
      if(TpSduLength <= BufferSize)
      {
         /* Deviation MISRAC2012-1 */
         /* call CopyRxData function */
         RetVal = CopyRxDataFp(RxPduId, PduInfoPtr, &BufferSize);

         if(RetVal == BUFREQ_OK)
         {
            /* Deviation MISRAC2012-1 */
            /* call RxIndication function */
            RxIndFp(RxPduId, NTFRSLT_OK);
         }
         else
         {
            /* Deviation MISRAC2012-1 */
            /* call RxIndication function */
            RxIndFp(RxPduId, NTFRSLT_E_NOT_OK);
         }
      }
      /* TpSduLength exceeds buffer size of upper layer module */
      else
      {
         /* Deviation MISRAC2012-1 */
         /* call RxIndication function */
         RxIndFp(RxPduId, NTFRSLT_E_NO_BUFFER);
      }
   }

   DBG_PDUR_GATETPUPRECEPTION_EXIT(E_OK, RxPduId, PduInfoPtr, TargetAPIRef);

   /* the return value is not considered by the calling handler function */
   return E_OK;
}

/* AUTOSAR Memory Mapping - end section for code */
#if (TS_MERGED_COMPILE == STD_OFF)
#define PDUR_STOP_SEC_CODE
#include <PduR_MemMap.h>
#endif

#else /* if (PDUR_MULTICAST_LOTPTOUP_SUPPORT == STD_ON) && .. */

/* Avoid empty translation unit according to ISO C90 */
typedef void PduR_PreventEmptyTranslationUnit_GateTpUpReceptionType;


/*==================[internal function definitions]=========================*/

#endif /* if (PDUR_MULTICAST_LOTPTOUP_SUPPORT == STD_ON) && .. */
/*==================[end of file]===========================================*/
