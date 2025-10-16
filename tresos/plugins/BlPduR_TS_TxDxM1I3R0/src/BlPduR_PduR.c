/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               BlPduR layer                                    */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BlPduR_PduR.c                   */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 1.3.0 BL3                */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*===============================================================================*/
/* Copyright 2016 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*===============================================================================*/

/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* CERT-C Deviation List
*
* CERTC-1) Deviated Rule: EXP.36
* Do not cast pointers into more strictly aligned pointer types
*
* Reason:
* This initialisation of pointer to NULL is needed at this place as otherwise it can result in no value assigned in certain conditions and this will have a junk value if not initialised.
*/

/* - Header Files: BlPduR                                                           */
#include "BlPduR_Prj.h"
#include "BlPduR_Priv.h"
#include <BlPduR_Trace.h>
#include <TSMem.h>          /* EB specific memory functions */



FUNC(BufReq_ReturnType, PDUR_CODE) BlPduR_StartOfReception
(
    PduIdType RxPduId,
    PduLengthType TpSduLength,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) BufferSizePtr
)
{
    BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
    PduIdType ubRxPduId = RxPduId;
    /* Deviation CERTC-1 */
    tBufferConfigType* curBufCfg = NULL_PTR;
#if (BLPDUR_SOURCE_ADDRESS_CHECK_ENABLE == STD_ON)
    StatusType stdTesterFilterStatus = E_OK;
#endif
    DBG_BLPDUR_STARTOFRECEPTION_ENTRY(RxPduId,TpSduLength,BufferSizePtr);

#if (BLPDUR_SOURCE_ADDRESS_CHECK_ENABLE == STD_ON)
    /* RQD_BLPDUR_PDUR_031 */
    stdTesterFilterStatus = BlPduR_VerifyTesterFilter(RxPduId);
    if (stdTesterFilterStatus != E_OK)
    {   /* RQD_BLPDUR_RECEPTION_041 */
        /* Tester is not allowed */
        retVal = BUFREQ_E_NOT_OK;
#if (BLPDUR_USE_PROG == STD_ON)
        PROG_TpStartOfReceptionInd(BLPDUR_E_NOT_OK);
#endif
    }
#endif
#if (BLPDUR_SOURCE_ADDRESS_CHECK_ENABLE == STD_ON)
    if ((BufferSizePtr != NULL_PTR) && (stdTesterFilterStatus == E_OK))
#else
    if (BufferSizePtr != NULL_PTR)
#endif
    {
        if (ubRxPduId < BLPDUR_MAX_RX_PDU_NUM)
        {
#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON)
            /* Convert PduId if necessary */ /* RQD_BLPDUR_RECEPTION_042 */
            BlPduR_ConvertRxFuncPduId(&RxPduId);
#endif
            /* RQD_BLPDUR_RECEPTION_044 */
            curBufCfg = BlPduR_GetRxInProgressBuf(RxPduId);
            if (curBufCfg == NULL_PTR) /* BlPDUR_002 */
            {     /* RQD_BLPDUR_RECEPTION_046 RQD_BLPDUR_RECEPTION_047 */
                /* occupy next free buffer */
                curBufCfg = BlPduR_GetFreeBufCfg(TpSduLength);
                /* check if buffer was found */
                if (curBufCfg != NULL_PTR)
                {   /* RQD_BLPDUR_RECEPTION_051 */
                    uint32 temp_cnt;
                    BlPduR_IncrementRxCnt();
                    temp_cnt = BlPduR_GetRxCnt();
                    BLPDUR_ENTER_CRITICAL_SECTION();
                    curBufCfg->bufferInfo->state              = BLPDUR_BUF_RX_IN_PROGRESS;
                    curBufCfg->bufferInfo->filledLen          = TpSduLength;
                    curBufCfg->bufferInfo->dataMark           = 0;
                    curBufCfg->bufferInfo->originatingRxPduId = RxPduId;
                    curBufCfg->bufferInfo->counter            = temp_cnt;
                    BLPDUR_EXIT_CRITICAL_SECTION();
                    *BufferSizePtr                            = curBufCfg->size;
                    /* Stop S3 timer on start of frame reception */
                    UDS_StopSessionTimer();
                    retVal = BUFREQ_OK;
                } /* RQD_BLPDUR_RECEPTION_050 */
            }
            else
            {   /* RQD_BLPDUR_RECEPTION_052 */
                PduLengthType tmp_dataMark;
                BLPDUR_ENTER_CRITICAL_SECTION();
                tmp_dataMark = curBufCfg->bufferInfo->dataMark;
                BLPDUR_EXIT_CRITICAL_SECTION();
                /* in case start of reception for the same is called again without calling copyrx*/
                if (tmp_dataMark == 0U)
                {   /* RQD_BLPDUR_RECEPTION_043 RQD_BLPDUR_RECEPTION_053 */
                    retVal = BUFREQ_OK;
                } /* RQD_BLPDUR_RECEPTION_045 */
            }
        } /* RQD_BLPDUR_RECEPTION_040 */
    }
    DBG_BLPDUR_STARTOFRECEPTION_EXIT(retVal);
    return retVal;
}

FUNC(BufReq_ReturnType, PDUR_CODE) BlPduR_CopyRxData
(
    PduIdType RxPduId,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_CONST) PduInfoPtr,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) BufferSizePtr
)
{
    /* Initialization */
    BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
    /* Deviation CERTC-1 */
    tBufferConfigType* curBufCfg = NULL_PTR;
    /* Deviation CERTC-1 */
    tBufferInfoType*  curRxBufferInfo = NULL_PTR;
    PduIdType ubRxPduId = RxPduId;
    DBG_BLPDUR_COPYRXDATA_ENTRY(RxPduId,PduInfoPtr,BufferSizePtr);
    curBufCfg = BlPduR_GetRxInProgressBuf(RxPduId); /* RQD_BLPDUR_MANAGE_010 */
    if ((PduInfoPtr != NULL_PTR) && (BufferSizePtr != NULL_PTR) && (curBufCfg != NULL_PTR))
    {
        curRxBufferInfo = curBufCfg->bufferInfo;
        if ((PduInfoPtr->SduLength == 0U) || (PduInfoPtr->SduDataPtr == NULL_PTR))
        {   /* RQD_BLPDUR_RECEPTION_011 */
            /* return available buffer size */
            BLPDUR_ENTER_CRITICAL_SECTION();
            *BufferSizePtr = (curBufCfg->size) - (curRxBufferInfo->dataMark);
            BLPDUR_EXIT_CRITICAL_SECTION();
            retVal = BUFREQ_OK;
        }
        else
        {
            boolean isBufFull = FALSE;
            BLPDUR_ENTER_CRITICAL_SECTION();
            if (((curRxBufferInfo->dataMark)+(PduInfoPtr->SduLength)) <= (curRxBufferInfo->filledLen))
            {
                isBufFull = TRUE;
            }
            BLPDUR_EXIT_CRITICAL_SECTION();
            if(isBufFull == TRUE)
            {  /* RQD_BLPDUR_RECEPTION_012 */
                /* copy payload into receive buffer */
                BLPDUR_ENTER_CRITICAL_SECTION();
                TS_MemCpy(&(curBufCfg->ptrBuffer[curRxBufferInfo->dataMark]),
                        PduInfoPtr->SduDataPtr, (uint16)PduInfoPtr->SduLength
                        );
                curRxBufferInfo->dataMark = (curRxBufferInfo->dataMark) + (PduInfoPtr->SduLength);
                /* Return remaining free space in receive buffer after completion of this call */
                *BufferSizePtr = (curBufCfg->size) - (curRxBufferInfo->dataMark);
                BLPDUR_EXIT_CRITICAL_SECTION();
                retVal = BUFREQ_OK;
            }
            else
            {   /* RQD_BLPDUR_RECEPTION_013 */
                retVal = BUFREQ_E_NOT_OK;
#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON)
                /* Convert PduId if necessary */
                BlPduR_ConvertRxFuncPduId(&ubRxPduId);
#endif
                BlPduR_RxInd(ubRxPduId, BLPDUR_E_NOT_OK );
            }
        }
    }
    else
    {
        /* RQD_BLPDUR_RECEPTION_014 */
        retVal = BUFREQ_E_NOT_OK;
#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON)
        /* Convert PduId if necessary */
        BlPduR_ConvertRxFuncPduId(&ubRxPduId);
#endif
        BlPduR_RxInd(ubRxPduId, BLPDUR_E_NOT_OK );
    }
    DBG_BLPDUR_COPYRXDATA_EXIT(retVal);
    return retVal;
}

FUNC(void, PDUR_CODE) BlPduR_TpRxIndication
(
    PduIdType    RxPduId,
    NotifResultType  Result
)
{
    PduIdType ubRxPduId = RxPduId;
    DBG_BLPDUR_TPRXINDICATION_ENTRY(RxPduId,Result);
#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON)
    /* Convert PduId if necessary */
    BlPduR_ConvertRxFuncPduId(&ubRxPduId);
#endif
    if(Result == NTFRSLT_OK)
    {   /* RQD_BLPDUR_RECEPTION_020 */
        BlPduR_RxInd(ubRxPduId, BLPDUR_E_OK );
    }
    else
    {   /* RQD_BLPDUR_RECEPTION_021 */
        BlPduR_RxInd(ubRxPduId, BLPDUR_E_NOT_OK );
    }
    DBG_BLPDUR_TPRXINDICATION_EXIT();
}

/* Function used to trigger transmission */
tBlPduRStatus BlPduR_SendMsgData (PduIdType PduId, PduLengthType ulLen, u8 *paubData)
{
    tBlPduRStatus retVal = BLPDUR_E_OK;

#if (BLPDUR_NETWORK_LIN_SUPPORTED == STD_ON)
        tBlPduRStatus eBlPduRStatus = BLPDUR_E_OK;
#else
      static PduInfoType TxInformation[BLPDUR_MAX_PDU_CONNECTION];
      Std_ReturnType RetCode;
#endif

    DBG_BLPDUR_SENDMSGDATA_ENTRY(PduId,ulLen,paubData);
#if (BLPDUR_NETWORK_LIN_SUPPORTED == STD_ON)
    {   /* RQD_BLPDUR_MANAGE_006 RQD_BLPDUR_MESSAGE_020*/
        if(BLPDUR_LIN_TX_PDU == PduId)
        { /* RQD_BLPDUR_MESSAGE_020 */
            eBlPduRStatus = BlPduR_LinTpTxMessage(ulLen, paubData);
            if (eBlPduRStatus != BLPDUR_E_OK)
            {
                /* Call tx Conf with error status */
                BlPduR_TxConf(PduId, BLPDUR_E_NOT_OK);
            }
        } /* RQD_BLPDUR_MESSAGE_021 */
    }
#else
    if ( (paubData != NULL_PTR) && (ulLen != 0U) && (PduId < BLPDUR_MAX_PDU_CONNECTION))
    {  /* RQD_BLPDUR_MANAGE_007 RQD_BLPDUR_MESSAGE_010 RQD_BLPDUR_MESSAGE_022 */
        /* Update transmission information given to PduR module*/
        TxInformation[PduId].SduDataPtr = NULL_PTR;
        TxInformation[PduId].SduLength = (PduLengthType)ulLen;
        RetCode = PduR_BlPduRTransmit(PduId, &TxInformation[PduId]);
        /* RQD_BLPDUR_MESSAGE_011 */
        if (RetCode != E_OK)
        {   /* RQD_BLPDUR_MANAGE_009 RQD_BLPDUR_MESSAGE_012 */
            BlPduR_TxConf(PduId, BLPDUR_E_NOT_OK);
            retVal = BLPDUR_E_NOT_OK;
        }
    }
    else
    {
        retVal = BLPDUR_E_NOT_OK;
    }
#endif
    DBG_BLPDUR_SENDMSGDATA_EXIT(retVal);
    return retVal;
}

FUNC(BufReq_ReturnType, PDUR_CODE) BlPduR_CopyTxData
(
    PduIdType TxPduId,
    P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr,
    P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) RetryInfoPtr,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) AvailableDataPtr
)
{
    BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
    u8 connectionNum = BLPDUR_NO_ACTIVE_CONNECTION;
    /* Deviation CERTC-1 */
    tBufferInfoType *curRxBufferInfo  = NULL_PTR;
    /* Deviation CERTC-1 */
    tBufferConfigType* curBufCfg = NULL_PTR;
    DBG_BLPDUR_COPYTXDATA_ENTRY(TxPduId,PduInfoPtr,RetryInfoPtr,AvailableDataPtr);
    OSC_PARAM_UNUSED(TxPduId);
    connectionNum = BlpduR_GetConnNumByTxPdu(TxPduId);
    BLPDUR_ENTER_CRITICAL_SECTION();
    if (connectionNum != BLPDUR_NO_ACTIVE_CONNECTION)
    {
        if (stPduConnection[connectionNum].TxBufCfgPtr != NULL_PTR)
        {
            curBufCfg       = stPduConnection[connectionNum].TxBufCfgPtr;
            curRxBufferInfo = curBufCfg->bufferInfo;
        }
    }
    BLPDUR_EXIT_CRITICAL_SECTION();
    if((PduInfoPtr != NULL_PTR) && (AvailableDataPtr != NULL_PTR) &&
        (curRxBufferInfo != NULL_PTR)) /* RQD_BLPDUR_ERROR_001 */
    {
        if(PduInfoPtr->SduLength == 0U)
        {   /* RQD_BLPDUR_TRANSMISSION_020 */
            /* TP layer polls length of transmission, supply length of data */
            BLPDUR_ENTER_CRITICAL_SECTION();
            *AvailableDataPtr = curRxBufferInfo->filledLen;
            retVal = BUFREQ_OK;
            BLPDUR_EXIT_CRITICAL_SECTION();
        }
        else if (RetryInfoPtr == NULL_PTR)
        {   /* RQD_BLPDUR_TRANSMISSION_021 */
            /* copy data */
            BLPDUR_ENTER_CRITICAL_SECTION();
            TS_MemCpy(PduInfoPtr->SduDataPtr, &curBufCfg->ptrBuffer[curRxBufferInfo->dataMark],
                    (uint16)PduInfoPtr->SduLength);
            /* Supply length of remaining data */
            curRxBufferInfo->dataMark += PduInfoPtr->SduLength;
            *AvailableDataPtr = curRxBufferInfo->filledLen - curRxBufferInfo->dataMark;
            retVal = BUFREQ_OK;
            BLPDUR_EXIT_CRITICAL_SECTION();
        }
        else
        {   /* RQD_BLPDUR_TRANSMISSION_022 */
            retVal = BUFREQ_E_NOT_OK;
        }
    }
    else
    {
        retVal = BUFREQ_E_NOT_OK;
    }
    DBG_BLPDUR_COPYTXDATA_EXIT(retVal);
    return retVal;
}

FUNC(void, PDUR_CODE) BlPduR_TpTxConfirmation
(
    PduIdType    TxPduId,
    NotifResultType  Result
)
{
    DBG_BLPDUR_TPTXCONFIRMATION_ENTRY(TxPduId,Result);
    if(Result == NTFRSLT_OK)
    {   /* RQD_BLPDUR_TRANSMISSION_010 */
        BlPduR_TxConf(TxPduId, BLPDUR_E_OK);
    }
    else
    {   /* RQD_BLPDUR_TRANSMISSION_011 */
        BlPduR_TxConf(TxPduId, BLPDUR_E_NOT_OK);
    }
    DBG_BLPDUR_TPTXCONFIRMATION_EXIT();
}


