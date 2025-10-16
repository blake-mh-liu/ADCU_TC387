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
 *  MISRAC2012-2) Deviated Rule: 17.2 (required)
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
#include <TSMem.h>                /* TS_MemCpy */

#if ((PDUR_MULTICORE_SUPPORT == STD_ON) &&\
     (PDUR_ZERO_COST_OPERATION_IF == STD_OFF) &&\
     (PDUR_MULTICAST_FROMIF_SUPPORT == STD_ON) &&\
     (PDUR_SB_TX_BUFFER_SUPPORT == STD_ON))

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

FUNC(void, PDUR_CODE) PduR_GateIfSbNoInitMCoreUpRxIndication
(
    PduIdType GPduId,
    P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr
)
{
   DBG_PDUR_GATEIFSBNOINITMCOREUPRXINDICATION_ENTRY(GPduId, PduInfoPtr);

#if (PDUR_DEV_ERROR_DETECT == STD_ON)
   /* check if input parameter is NULL */
   if (NULL_PTR == PduInfoPtr->SduDataPtr)
   {
       PDUR_DET_REPORT_ERROR(PDUR_SID_GATEIF_SBNOINIT_MCORE_UP_RXIND, PDUR_E_NULL_POINTER);
   }
   else
#endif /* #if (PDUR_DEV_ERROR_DETECT == STD_ON) */
   {
      /* pointer to routing table */
      CONSTP2CONST(PduR_GTabIfRxType, AUTOMATIC, PDUR_APPL_CONST) pGTabIfRx =
         PDUR_GET_CONFIG_ADDR(PduR_GTabIfRxType, PduR_GConfigPtr->PduR_GTabIfConfig.GTabRxRef);

      /* pointer to configuration of single buffer for dynamic payload */
      CONSTP2CONST(PduR_BufSbConfigType, AUTOMATIC, PDUR_APPL_CONST) pBufSbConfig =
         PDUR_GET_CONFIG_ADDR(PduR_BufSbConfigType, PduR_GConfigPtr->PduR_BufSbDynPyldConfigRef);

      /* local representation of the BufferId */
      const uint16 BufferId = pGTabIfRx[GPduId].BufferId;

      /* pointer to memory location of single buffer in RAM */
      /* Deviation MISRAC2012-1 */
      CONSTP2VAR(uint8, AUTOMATIC, PDUR_VAR_CLEARED) pBufMem =
         PDUR_GET_RAM_ADDR(uint8, pBufSbConfig[BufferId].MemRef);

      /* length of incoming dynamic PDU */
      uint8 UsedSduLength;

      /* length of single buffer */
      const uint8 lenSbBuffer = pBufSbConfig[BufferId].Length;

      PduInfoType PduR_PduInfo;

      /* ENTER CRITICAL SECTION */
      SchM_Enter_PduR_SCHM_PDUR_EXCLUSIVE_AREA_1();

      /* allocate length value */
      if(PduInfoPtr->SduLength > lenSbBuffer)
      {
         /* use buffer length */
         UsedSduLength = lenSbBuffer;
      }
      else
      {
         /* use SDU length value from PduInfoPtr: the SduLength data type (fix PduLengthTypeEnum
          * uint16) is casted to uint8 since the maximum value that can be reached by SduLength
          * does not exceed the maximum value that can be represented by uint8 */
         UsedSduLength = (uint8)PduInfoPtr->SduLength;
      }

      /* Copy data to single buffer of PDU Router */
      TS_MemCpy(pBufMem, PduInfoPtr->SduDataPtr, UsedSduLength);

      /* set up PduInfo for Up_IfRxIndication call */
      PduR_PduInfo.SduDataPtr = pBufMem;
      PduR_PduInfo.SduLength = UsedSduLength;

      /* EXIT CRITICAL SECTION */
      SchM_Exit_PduR_SCHM_PDUR_EXCLUSIVE_AREA_1();

      {
         /* reference to set of target If-module API-functions */
         const PduR_RefToModuleAPI TargetAPIRef = pGTabIfRx[GPduId].TargetModuleAPIRef;

         /* get pointer to Up_RxIndication function from routing table */
         const PduR_IfRxIndFpType RxIndFp = PduR_IfModuleAPI[TargetAPIRef].IfRxIndication;

         /* get target PDU ID to RxIndication function from routing table */
         const PduR_PduIdType TargetPduId = pGTabIfRx[GPduId].TargetPduId;

         /* Deviation MISRAC2012-2 */
         /* Call Up_IfRxIndication function with incoming buffered PDU */
         RxIndFp(TargetPduId, &PduR_PduInfo);
      }
   }

   DBG_PDUR_GATEIFSBNOINITMCOREUPRXINDICATION_EXIT(GPduId, PduInfoPtr);
}

/* AUTOSAR Memory Mapping - end section for code */
#if (TS_MERGED_COMPILE == STD_OFF)
#define PDUR_STOP_SEC_CODE
#include <PduR_MemMap.h>
#endif

#else /* if (PDUR_ZERO_COST_OPERATION_IF == STD_OFF) && .. */

/* Avoid empty translation unit according to ISO C90 */
typedef void PduR_PreventEmptyTranslationUnit_GateIfSbNoInitMCoreUpRxIndicationType;


/*==================[internal function definitions]=========================*/

#endif /* if (PDUR_ZERO_COST_OPERATION_IF == STD_OFF) && .. */
/*==================[end of file]===========================================*/
