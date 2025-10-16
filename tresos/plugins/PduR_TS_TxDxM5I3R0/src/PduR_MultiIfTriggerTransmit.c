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

#if((PDUR_ZERO_COST_OPERATION_IF == STD_OFF) && \
    (PDUR_MULTICAST_TOIF_SUPPORT == STD_ON) && \
    (PDUR_LOIF_TRIGGERTX_ENABLED == STD_ON))

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

FUNC(Std_ReturnType, PDUR_CODE) PduR_MultiIfTriggerTransmit
(
   PduIdType    MPduId,
   P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr
)
{
   Std_ReturnType RetVal;

   DBG_PDUR_MULTIIFTRIGGERTRANSMIT_ENTRY(MPduId, PduInfoPtr);

   {
      /* pointer to routing table */
      CONSTP2CONST(PduR_MTabUpIfTxType, AUTOMATIC, PDUR_APPL_CONST) pMTabUpIfTx =
         PDUR_GET_CONFIG_ADDR(PduR_MTabUpIfTxType, PduR_GConfigPtr->PduR_MTabUpIfConfig.MTabTxRef);

      /* reference to set of upper layer API-functions */
      const PduR_RefToModuleAPI SourceAPIRef = pMTabUpIfTx[MPduId].SourceModuleAPIRef;

      /* get upper layer PDU-ID */
      const PduR_PduIdType UprLyrTxPduId = pMTabUpIfTx[MPduId].UprLyrTxPduId;

      /* pointer to TriggerTransmit function */
      const PduR_IfTrTxFpType TriggerTransmitFp = PduR_IfModuleAPI[SourceAPIRef].IfTriggerTransmit;

      /* Deviation MISRAC2012-1 */
      /* call TriggerTransmit function */
      RetVal = TriggerTransmitFp(UprLyrTxPduId, PduInfoPtr);
   }

   DBG_PDUR_MULTIIFTRIGGERTRANSMIT_EXIT(RetVal, MPduId, PduInfoPtr);

   return RetVal;
}

/* AUTOSAR Memory Mapping - end section for code */
#if (TS_MERGED_COMPILE == STD_OFF)
#define PDUR_STOP_SEC_CODE
#include <PduR_MemMap.h>
#endif

#else /* if (PDUR_ZERO_COST_OPERATION_IF == STD_OFF) && .. */

/* Avoid empty translation unit according to ISO C90 */
typedef void PduR_PreventEmptyTranslationUnit_MultiIfTriggerTransmitType;


/*==================[internal function definitions]=========================*/

#endif /* if (PDUR_ZERO_COST_OPERATION_IF == STD_OFF) && .. */
/*==================[end of file]===========================================*/
