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
/*%%   _____________________________   %%  \file BlPduR_Conn_Treatment.c         */
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


/* CERT-C Deviation List
*
* CERTC-1) Deviated Rule: EXP.36
* Do not cast pointers into more strictly aligned pointer types
*
* Reason:
* This initialisation of pointer to NULL is needed at this place as otherwise it can result in no value assigned in certain conditions and this will have a junk value if not initialised.
*/

#include "BlPduR_Prj.h"
#include "BlPduR_Priv.h"
#include <BlPduR_Trace.h>
#include <TSMem.h>          /* EB specific memory functions */
/*===============================================================================*/

/*============================= PUBLIC DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */
/*                                                                               */
/*===============================================================================*/

/*============================ PRIVATE DEFINITIONS ==============================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Private Constants                                                           */

/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */
/* Message processing status */
static tBlPduRStatus m_uTreatmentStatus;
/* Current active connection */
u8 m_ubCurrentConnection;
u8 m_ubCurrentRxId;
static u8 m_ubSessionConnection;
static u8 m_ubStoredConnection;

#if (BLPDUR_SOURCE_ADDRESS_CHECK_ENABLE == STD_ON)
/* Current used tester address */
static u16 m_ubTesterAddress;
#endif
/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
/*                                                                               */
static void BlPduR_SendNRC21 (const tBufferConfigType* pstRxCurrentBufferConfig);
static void BlPduR_TreatReq (const tBufferConfigType* pstRxCurrentBufferConfig);
void BlPduR_IgnoreReq (const tBufferConfigType* pstRxCurrentBufferConfig);
/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */

tBlPduRStatus BlPduR_GetTreatmentStatus (void)
{
    tBlPduRStatus result;
    BLPDUR_ENTER_CRITICAL_SECTION();
    result = m_uTreatmentStatus;
    BLPDUR_EXIT_CRITICAL_SECTION();
    return result;
}

static void BlPduR_SendNRC21 (const tBufferConfigType* pstRxCurrentBufferConfig)
{       /* RQD_BLPDUR_CONN_TREATMENT_072 */
    tBufferInfoType *curRxBufferInfo ;
    u8*           paubUdsData        ;
    PduLengthType ulLen              ;

    BLPDUR_ENTER_CRITICAL_SECTION();
    if ( (pstRxCurrentBufferConfig            != NULL_PTR) &&
         (pstRxCurrentBufferConfig->ptrBuffer != NULL_PTR) )
    {
        curRxBufferInfo    = pstRxCurrentBufferConfig->bufferInfo;
        paubUdsData        = pstRxCurrentBufferConfig->ptrBuffer;
        ulLen = 3;
        curRxBufferInfo->filledLen = ulLen;
        curRxBufferInfo->dataMark  = 0;
        curRxBufferInfo->state = BLPDUR_BUFF_TXQUEUED;
        paubUdsData[1] = paubUdsData[0];
        paubUdsData[0] = 0x7FU;
        paubUdsData[2] = 0x21U;
        /* Update transmission buffer */
        curRxBufferInfo->filledLen = ulLen;
    }
    BLPDUR_EXIT_CRITICAL_SECTION();
}

#if (BLPDUR_QUEUED_MANAGEMENT_ENABLE == STD_OFF)
void BlPduR_IgnoreReq (const tBufferConfigType* pstRxCurrentBufferConfig)
{
    BlPduR_ReleaseBuffers(pstRxCurrentBufferConfig->bufferInfo); /* RQD_BLPDUR_CONN_TREATMENT_046 */
}
#endif

static void BlPduR_TreatReq (const tBufferConfigType* pstRxCurrentBufferConfig)
{
    tUdsAddrMode eUdsAddrMode;
    tUdsBoolean  eStatusRxReq;
    tBufferInfoType *curRxBufferInfo ;
    PduIdType     uRxPduId           ;
    u8*           paubUdsData        ;
    PduLengthType ulLen              ;
    PduLengthType BlPduRRxBufferSize ;
    PduIdType     uTxPduId           ;
    boolean       isBufLocked = FALSE;
    boolean       isBufIdle   = FALSE;

    BLPDUR_ENTER_CRITICAL_SECTION();
    curRxBufferInfo        = pstRxCurrentBufferConfig->bufferInfo;
    uRxPduId               = curRxBufferInfo->originatingRxPduId;
    paubUdsData            = pstRxCurrentBufferConfig->ptrBuffer;
    ulLen                  = curRxBufferInfo->filledLen;
    m_uTreatmentStatus     = BLPDUR_E_BUSY; /* RQD_BLPDUR_CONN_TREATMENT_076 */
    curRxBufferInfo->state = BLPDUR_BUFF_RXPROCESSING;
    m_ubCurrentRxId        = (u8) uRxPduId;
    m_ubCurrentConnection  = stRxPdu[uRxPduId].ConnectionNum;
    eUdsAddrMode           = stRxPdu[uRxPduId].AddressingType;
    BlPduRRxBufferSize     = pstRxCurrentBufferConfig->size;
    BLPDUR_EXIT_CRITICAL_SECTION();
    /* RQD_BLPDUR_CONN_TREATMENT_007 */
    eStatusRxReq = UDS_RxRequestWithAddrMode (&ulLen, paubUdsData, BlPduRRxBufferSize, eUdsAddrMode, UDS_TYPE_DIAG);
    BLPDUR_ENTER_CRITICAL_SECTION();
    if (curRxBufferInfo->state == BLPDUR_BUFF_IDLE)
    {
        isBufIdle = TRUE;
    }
    BLPDUR_EXIT_CRITICAL_SECTION();
    if (isBufIdle == TRUE)
    {  /* RQD_BLPDUR_CONN_TREATMENT_082 */
        pstRxCurrentBufferConfig = BlPduR_GetNxtProcBuf();
        curRxBufferInfo = pstRxCurrentBufferConfig->bufferInfo;
    }
    if ((eStatusRxReq == UDS_TRUE) && (pstRxCurrentBufferConfig != NULL_PTR))
    {
        /* Answer to the request only it is asked by DIAG layer */
        if (ulLen > 0U)
        {
            BLPDUR_ENTER_CRITICAL_SECTION();
            if (curRxBufferInfo->locked == TRUE)
            {
                isBufLocked = TRUE;
            }
            BLPDUR_EXIT_CRITICAL_SECTION();
            if (isBufLocked == TRUE)
            {   /* RQD_BLPDUR_CONN_TREATMENT_060  */
                tBufferConfigType* newBuf = BlPduR_GetFreeBufCfg(ulLen);
                if (newBuf != NULL_PTR)
                {
                    uint32 temp_cnt;
                    BlPduR_IncrementRxCnt();
                    temp_cnt = BlPduR_GetRxCnt();
                    BLPDUR_ENTER_CRITICAL_SECTION();
                    newBuf->bufferInfo->originatingRxPduId = m_ubCurrentRxId;
                    newBuf->bufferInfo->filledLen = ulLen;
                    TS_MemCpy(&(newBuf->ptrBuffer[0]),
                            paubUdsData, ulLen);
                    newBuf->bufferInfo->counter = temp_cnt;
                    newBuf->bufferInfo->filledLen = ulLen;
                    newBuf->bufferInfo->dataMark  = 0;
                    newBuf->bufferInfo->state = BLPDUR_BUFF_TXQUEUED;
                    BLPDUR_EXIT_CRITICAL_SECTION();
                }
                else
                {
                    /* RQD_BLPDUR_CONN_TREATMENT_073 */
                }
            }
            else
            {
                /* RQD_BLPDUR_CONN_TREATMENT_074 */
                /* Write the answer message data */
                BLPDUR_ENTER_CRITICAL_SECTION();
                curRxBufferInfo->filledLen = ulLen;
                curRxBufferInfo->dataMark  = 0;
                curRxBufferInfo->state = BLPDUR_BUFF_TXQUEUED;
                BLPDUR_EXIT_CRITICAL_SECTION();
            }
        }
        else
        {   /* RQD_BLPDUR_MANAGE_005 RQD_BLPDUR_MESSAGE_023 */
            /* Answer is empty (suppress bit set?), free the buffer */
            BlPduR_ReleaseBuffers(curRxBufferInfo); /* RQD_BLPDUR_CONN_TREATMENT_047 */
            BLPDUR_ENTER_CRITICAL_SECTION();
            m_uTreatmentStatus = BLPDUR_E_IDLE; /* RQD_BLPDUR_CONN_TREATMENT_077 */
            BLPDUR_EXIT_CRITICAL_SECTION();
        }

    }
    else if(eStatusRxReq == UDS_NRC_78)
    { /* RQD_BLPDUR_CONN_TREATMENT_079 RQD_BLPDUR_MANAGE_004 */
#if (BLPDUR_NETWORK_LIN_SUPPORTED == STD_ON)
        /* Disable LTP RX */
        (void)LTP_RxEnable(LTP_RX_ENABLE_OFF);
#endif
    }
    else
    {
        uTxPduId = BLPDUR_INVALID_PDU;
        /* RQD_BLPDUR_CONN_TREATMENT_078 RQD_BLPDUR_MANAGE_003 */
        BLPDUR_ENTER_CRITICAL_SECTION();
        if (m_ubCurrentConnection < BLPDUR_MAX_PDU_CONNECTION)
        {
            /* Set back treatment status to IDLE */
            m_uTreatmentStatus = BLPDUR_E_IDLE;

            /* Get the transmission Pdu Id */
            uTxPduId = stPduConnection[m_ubCurrentConnection].TxPdu;
        }
        BLPDUR_EXIT_CRITICAL_SECTION();
        if (uTxPduId != BLPDUR_INVALID_PDU)
        {
            /* Simulate Tx confirmation to free the buffer */
            BlPduR_TxConf(uTxPduId, BLPDUR_E_OK);
        }
    }
}

void BlPduR_InitConnection (void)
{   /* RQD_BLPDUR_INIT_010 */
    BLPDUR_ENTER_CRITICAL_SECTION();
    m_uTreatmentStatus = BLPDUR_E_IDLE; /* RQD_BLPDUR_CONN_TREATMENT_075 */
    m_ubSessionConnection = BLPDUR_NO_ACTIVE_CONNECTION;
    m_ubCurrentConnection = BLPDUR_NO_ACTIVE_CONNECTION;
    m_ubStoredConnection = BLPDUR_NO_ACTIVE_CONNECTION;
#if (BLPDUR_SOURCE_ADDRESS_CHECK_ENABLE == STD_ON)
    m_ubTesterAddress = BLPDUR_ALL_TESTER_ADDRESS; /* RQD_BLPDUR_INIT_011 */
#endif
    BLPDUR_EXIT_CRITICAL_SECTION();
}


void BlPduR_TpRxMsgManage (void)
{  /* RQD_BLPDUR_CONN_TREATMENT_041  */
    /* Data and length of the Diagnostic messages */
    tBufferConfigType* curRxBufCfg;
    tBufferConfigType* curTxBufCfg;
    PduIdType          uRxPduId;
    u8                 connectionNum;
    /* Deviation CERTC-1 */
    tBufferInfoType*   curTxBufferInfo = NULL_PTR;
    boolean            isTxInactive      = FALSE;
    boolean            isNoActiveConn  = FALSE;
    boolean            isTreatmentIdle = FALSE;
    boolean            isKnownConn     = FALSE;
    boolean            isActSession    = FALSE;
    DBG_BLPDUR_TPRXMSGMANAGE_ENTRY();
    curRxBufCfg = BlPduR_GetNxtQueuedRxBuf();
    if (curRxBufCfg != NULL_PTR) /* RQD_BLPDUR_MANAGE_001 */
    {
#if (BLPDUR_QUEUED_MANAGEMENT_ENABLE == STD_ON)
#if (BLPDUR_PROG_2_SUCCESSIVE_CHECKMEMORY_ALLOWED == STD_ON)
        /* RQD_BLPDUR_RECEPTION_072 */
        /* Do not queue the Checkmemory request if it comes a second time */
#endif
#endif
        /* RQD_BLPDUR_MANAGE_002 */
        BLPDUR_ENTER_CRITICAL_SECTION();
        uRxPduId            = curRxBufCfg->bufferInfo->originatingRxPduId;
        if (m_ubSessionConnection == BLPDUR_NO_ACTIVE_CONNECTION)
        {
            isNoActiveConn  = TRUE;
        }
        if (BLPDUR_E_IDLE == m_uTreatmentStatus)
        {
            isTreatmentIdle = TRUE;
        }
        if (stRxPdu[uRxPduId].ConnectionNum == m_ubCurrentConnection)
        {
            isKnownConn     = TRUE;
        }
        if (stRxPdu[uRxPduId].ConnectionNum == m_ubSessionConnection)
        {
            isActSession    = TRUE;
        }
        BLPDUR_EXIT_CRITICAL_SECTION();
        if (isNoActiveConn == TRUE)
        {
            if (isTreatmentIdle == TRUE)
            {/* RQD_BLPDUR_CONN_TREATMENT_040 */
                BlPduR_TreatReq(curRxBufCfg);
            }
            else
            {
                if (isKnownConn == TRUE)
                {
#if (BLPDUR_QUEUED_MANAGEMENT_ENABLE == STD_OFF)
                    BlPduR_IgnoreReq(curRxBufCfg);
#endif
                }
                else
                {
                    BlPduR_SendNRC21(curRxBufCfg);
                }
            }
        }
        else
        {
            if (isActSession == TRUE)
            {
                if (isTreatmentIdle == TRUE)
                {
                    BlPduR_TreatReq(curRxBufCfg);
                }
                else
                {
#if (BLPDUR_QUEUED_MANAGEMENT_ENABLE == STD_OFF)
                    BlPduR_IgnoreReq(curRxBufCfg);
#endif
                }
            }
            else
            {
                BlPduR_SendNRC21(curRxBufCfg);
            }
        }
    }
    curTxBufCfg = BlPduR_GetNxtQueuedTxBuf();
    if (curTxBufCfg != NULL_PTR)
    {
        tBlPduRStatus eStatus = BLPDUR_E_OK;
        BLPDUR_ENTER_CRITICAL_SECTION();
        curTxBufferInfo = curTxBufCfg->bufferInfo;
        uRxPduId        = curTxBufferInfo->originatingRxPduId;
        connectionNum   = stRxPdu[uRxPduId].ConnectionNum;
        if (stPduConnection[connectionNum].TxBufCfgPtr == NULL_PTR)
        {
            isTxInactive = TRUE;
        }
        BLPDUR_EXIT_CRITICAL_SECTION();
        if (isTxInactive == TRUE)
        {
            uint32 temp_cnt;

            PduIdType PduId;
            PduLengthType ulLen;
            u8 *paubData;
            BlPduR_IncrementRxCnt();
            temp_cnt = BlPduR_GetRxCnt();
            BLPDUR_ENTER_CRITICAL_SECTION();
            curTxBufCfg->bufferInfo->counter = temp_cnt;
            stPduConnection[connectionNum].TxBufCfgPtr = curTxBufCfg;
            PduId = stPduConnection[connectionNum].TxPdu;
            ulLen= curTxBufferInfo->filledLen;
            paubData = curTxBufCfg->ptrBuffer;
            BLPDUR_EXIT_CRITICAL_SECTION();
            eStatus = BlPduR_SendMsgData ( PduId,
                                           ulLen,
                                           paubData);
            BLPDUR_ENTER_CRITICAL_SECTION();
            if (eStatus == BLPDUR_E_OK)
            {
                curTxBufferInfo->state = BLPDUR_BUFF_TXPROCESSING;
            }
            else
            {
             /* Deviation CERTC-1 */
                stPduConnection[connectionNum].TxBufCfgPtr = NULL_PTR;
            }
            BLPDUR_EXIT_CRITICAL_SECTION();
        }
    }

    DBG_BLPDUR_TPRXMSGMANAGE_EXIT();

}

void BlPduR_TxConf(PduIdType uTxPduId, tBlPduRStatus eBlPduRStatus)
{
    u8 connectionNum;
    boolean isActiveConn = FALSE;
    u8* paubUdsData = NULL_PTR;
    /* Deviation CERTC-1 */
    tBufferConfigType* curBufCfg = NULL_PTR;
#if (BLPDUR_USE_PROG == STD_ON)
#ifdef PROG_RESPOND_TO_PROG_SESSION
#if (PROG_RESPOND_TO_PROG_SESSION == STD_ON)
    u8 ubIsReProgRequestFromAppli = FALSE;
#endif
#endif
#endif
    connectionNum = (u8)BlpduR_GetConnNumByTxPdu(uTxPduId);
    if (connectionNum != BLPDUR_NO_ACTIVE_CONNECTION)
    {
        BLPDUR_ENTER_CRITICAL_SECTION();
        if (stPduConnection[connectionNum].TxBufCfgPtr != NULL_PTR)
        {
            curBufCfg =  stPduConnection[connectionNum].TxBufCfgPtr;
            paubUdsData = curBufCfg->ptrBuffer;
        }
        BLPDUR_EXIT_CRITICAL_SECTION();
    }

    if ((curBufCfg != NULL_PTR) && (paubUdsData != NULL_PTR))
    {
        boolean isNRC78 = FALSE;
        BLPDUR_ENTER_CRITICAL_SECTION();

        if ((paubUdsData[0] == UDS_NRC) && (paubUdsData[2] == UDS_NRC_78))
        {
            isNRC78 = TRUE;
        }

        BLPDUR_EXIT_CRITICAL_SECTION();
        if(isNRC78 == TRUE)
        {   /* RQD_BLPDUR_TRANSMISSION_002  */
            UDS_LongRequestRespTxConf();
            BlPduR_ReleaseBuffers(curBufCfg->bufferInfo); /* RQD_BLPDUR_CONN_TREATMENT_008 */
            BLPDUR_ENTER_CRITICAL_SECTION();
            /* Deviation CERTC-1 */
            stPduConnection[connectionNum].TxBufCfgPtr = NULL_PTR;
            BLPDUR_EXIT_CRITICAL_SECTION();
        }
        else
        {
            BLPDUR_ENTER_CRITICAL_SECTION();
            if (connectionNum == m_ubCurrentConnection)
            {   /*  RQD_BLPDUR_TRANSMISSION_001 */
                m_ubCurrentConnection = BLPDUR_NO_ACTIVE_CONNECTION;
                m_uTreatmentStatus = BLPDUR_E_IDLE; /* RQD_BLPDUR_CONN_TREATMENT_080 */
            }
            /* Deviation CERTC-1 */
            stPduConnection[connectionNum].TxBufCfgPtr = NULL_PTR;
            BLPDUR_EXIT_CRITICAL_SECTION();
            BlPduR_ReleaseBuffers(curBufCfg->bufferInfo);

#if (BLPDUR_NETWORK_LIN_SUPPORTED == STD_ON)
            /* Enable LTP RX */ /* RQD_BLPDUR_TRANSMISSION_035 */
            (void)LTP_RxEnable(LTP_RX_ENABLE_ON);
#endif
        }
    }
    else
    {
        BLPDUR_ENTER_CRITICAL_SECTION();
        m_ubCurrentConnection = BLPDUR_NO_ACTIVE_CONNECTION;
        m_uTreatmentStatus = BLPDUR_E_IDLE; /* RQD_BLPDUR_TRANSMISSION_009*/
        BLPDUR_EXIT_CRITICAL_SECTION();
    }

    BLPDUR_ENTER_CRITICAL_SECTION();
    if (m_ubSessionConnection != BLPDUR_NO_ACTIVE_CONNECTION)
    {
        isActiveConn = TRUE;
    }
    BLPDUR_EXIT_CRITICAL_SECTION();
    /* RQD_BLPDUR_CONN_TREATMENT_006 */
    if (isActiveConn == TRUE)
    {
        uint32 conNum;
        boolean isActSession = FALSE;
        conNum = BlpduR_GetConnNumByTxPdu(uTxPduId);
        BLPDUR_ENTER_CRITICAL_SECTION();
        if (conNum == m_ubSessionConnection)
        {
            isActSession  = TRUE;
        }
        BLPDUR_EXIT_CRITICAL_SECTION();
        if (isActSession == TRUE)
        {   /* RQD_BLPDUR_TRANSMISSION_007 */
            UDS_ReloadTStopDiag();
        }
    }



#if (BLPDUR_USE_PROG == STD_ON)
#ifdef PROG_RESPOND_TO_PROG_SESSION
#if (PROG_RESPOND_TO_PROG_SESSION == STD_ON)
    ubIsReProgRequestFromAppli = PROG_ReturnsIsReProgRequestFromAppli();
    /* Simulate Rx request treatment is now done */
    if (ubIsReProgRequestFromAppli == TRUE)
    {
        if(m_eSimRxReqState == BLPDUR_SIM_RX_REQ_IN_PROGRESS)
        {
            m_eSimRxReqState = BLPDUR_SIM_RX_REQ_DONE;
        }
    }
#endif
#endif
#endif
    BLPDUR_ENTER_CRITICAL_SECTION();
    if(m_uTreatmentStatus == BLPDUR_E_IDLE)
    {   /* RQD_BLPDUR_TRANSMISSION_030 */
        /* Re-Initialize current Connection */
        m_ubCurrentConnection = BLPDUR_NO_ACTIVE_CONNECTION;
    } /*  RQD_BLPDUR_TRANSMISSION_031 */
    BLPDUR_EXIT_CRITICAL_SECTION();
    /* RQD_BLPDUR_TRANSMISSION_008 */
    /* PduId cast to be compatible with old prototype format */
    APP_TpTxConf((u8)(uTxPduId & 0x00FFU), eBlPduRStatus);
#if (BLPDUR_USE_PROG == STD_ON)
    /* PduId cast to be compatible with old prototype format */
    PROG_TpTxConf((u8)(uTxPduId & 0x00FFU), eBlPduRStatus);
#endif
}

void BlPduR_StoreConnectionInfo(void)
{
    u8 m_ubRxId;
    DBG_BLPDUR_STORECONNECTIONINFO_ENTRY();
    BLPDUR_ENTER_CRITICAL_SECTION();
    m_ubRxId = m_ubCurrentRxId;
    BLPDUR_EXIT_CRITICAL_SECTION();
    /* Callback to store the RxPduId */
    BlPduR_StoreRxPduId(m_ubRxId); /* RQD_BLPDUR_CONNECTION_012 */
    DBG_BLPDUR_STORECONNECTIONINFO_EXIT();
}

/* RQD_BLPDUR_CONN_TREATMENT_007 */
void BlPduR_Send_TPFrame(PduLengthType ulLen, const u8 *paubData)
{
    /* Deviation CERTC-1 */
    tBufferConfigType* curBufCfg = NULL_PTR;
    DBG_BLPDUR_SEND_TPFRAME_ENTRY(ulLen,paubData);
    if ((ulLen != 0U) && (paubData!=NULL_PTR))
    {
        if((paubData[0] == UDS_NRC) && (paubData[2] == UDS_NRC_78))
        { /* RQD_BLPDUR_CONN_TREATMENT_008 */
            curBufCfg = BlPduR_GetFreeBufCfg(ulLen);
            if (curBufCfg != NULL_PTR)
            {
                uint32 temp_cnt;
                BlPduR_IncrementRxCnt();
                temp_cnt = BlPduR_GetRxCnt();
                BLPDUR_ENTER_CRITICAL_SECTION();
                curBufCfg->bufferInfo->originatingRxPduId = m_ubCurrentRxId;
                curBufCfg->bufferInfo->filledLen = ulLen;
                TS_MemCpy(&(curBufCfg->ptrBuffer[0]),
                        paubData, ulLen);
                curBufCfg->bufferInfo->counter = temp_cnt;
                curBufCfg->bufferInfo->dataMark  = 0;
                curBufCfg->bufferInfo->state = BLPDUR_BUFF_TXQUEUED;
                BLPDUR_EXIT_CRITICAL_SECTION();
            }
        }
        else
        {
            curBufCfg = BlPduR_GetNxtProcBuf();
            if (curBufCfg != NULL_PTR)
            {
                uint32 temp_cnt;
                BlPduR_IncrementRxCnt();
                temp_cnt = BlPduR_GetRxCnt();
                BLPDUR_ENTER_CRITICAL_SECTION();
                /* RQD_BLPDUR_CONN_TREATMENT_009 */
                curBufCfg->bufferInfo->filledLen = ulLen;
                curBufCfg->bufferInfo->counter = temp_cnt;
                curBufCfg->bufferInfo->dataMark  = 0;
                curBufCfg->bufferInfo->state = BLPDUR_BUFF_TXQUEUED;
                BLPDUR_EXIT_CRITICAL_SECTION();
            }
            else
            {
                /*  RQD_BLPDUR_CONN_TREATMENT_011  */
                curBufCfg = BlPduR_GetFreeBufCfg(ulLen);
                if (curBufCfg != NULL_PTR)
                {
                    uint32 temp_cnt;
                    BlPduR_IncrementRxCnt();
                    temp_cnt = BlPduR_GetRxCnt();
                    BLPDUR_ENTER_CRITICAL_SECTION();
                    curBufCfg->bufferInfo->originatingRxPduId = m_ubCurrentRxId;
                    curBufCfg->bufferInfo->filledLen = ulLen;
                    TS_MemCpy(&(curBufCfg->ptrBuffer[0]),
                            paubData, ulLen);
                    curBufCfg->bufferInfo->counter = temp_cnt;
                    curBufCfg->bufferInfo->dataMark  = 0;
                    curBufCfg->bufferInfo->state = BLPDUR_BUFF_TXQUEUED;
                    BLPDUR_EXIT_CRITICAL_SECTION();
                }
            }
        }
    }
    else
    {
        curBufCfg = BlPduR_GetNxtProcBuf();
        if (curBufCfg != NULL_PTR)
        {
            /* RQD_BLPDUR_CONN_TREATMENT_047 */
            BlPduR_ReleaseBuffers(curBufCfg->bufferInfo);
            BLPDUR_ENTER_CRITICAL_SECTION();
            /* RQD_BLPDUR_CONN_TREATMENT_077 */
            m_uTreatmentStatus = BLPDUR_E_IDLE;
            BLPDUR_EXIT_CRITICAL_SECTION();
        }
    }


    DBG_BLPDUR_SEND_TPFRAME_EXIT();

}

void BlPduR_SimulateRxRequest(PduLengthType ulLen, u8 * paubUdsData, PduLengthType ulUdsDataSize, u8 ubWithResp)
{ /* RQD_BLPDUR_CONN_TREATMENT_013 */
    DBG_BLPDUR_SIMULATERXREQUEST_ENTRY(ulLen,paubUdsData,ulUdsDataSize,ubWithResp);
    if (ubWithResp == TRUE)
    {

#if (BLPDUR_USE_PROG == STD_ON)
#ifdef PROG_RESPOND_TO_PROG_SESSION
#if (PROG_RESPOND_TO_PROG_SESSION == STD_ON)
#ifdef PROG_DSC02_DENIED_IN_DEF_SESSION
#if (PROG_DSC02_DENIED_IN_DEF_SESSION == STD_ON)
        if (UDS_GetCurrentSession() == UDS_SESSION_EXTENDED_DIAG)
#endif /* PROG_DSC02_DENIED_IN_DEF_SESSION == STD_ON */
#endif /* PROG_DSC02_DENIED_IN_DEF_SESSION */
        {
#endif /* PROG_RESPOND_TO_PROG_SESSION == STD_ON */
#endif /* PROG_RESPOND_TO_PROG_SESSION */
#endif /* BLPDUR_USE_PROG == STD_ON */
            m_uTreatmentStatus = BLPDUR_E_BUSY; /* RQD_BLPDUR_CONN_TREATMENT_081 RQD_BLPDUR_RECEPTION_030 */
#if (BLPDUR_USE_PROG == STD_ON)
#ifdef PROG_RESPOND_TO_PROG_SESSION
#if (PROG_RESPOND_TO_PROG_SESSION == STD_ON)
            /* Simulate Rx Request treatment has started */
            m_eSimRxReqState = BLPDUR_SIM_RX_REQ_IN_PROGRESS;
        }
#ifdef PROG_DSC02_DENIED_IN_DEF_SESSION
#if (PROG_DSC02_DENIED_IN_DEF_SESSION == STD_ON)
        else
        {
            /* Response to Simulate Rx Request will not be sent - Reset should be performed */
            m_eSimRxReqState = BLPDUR_SIM_RX_REQ_DONE;
        }
#endif /* PROG_DSC02_DENIED_IN_DEF_SESSION == STD_ON */
#endif /* PROG_DSC02_DENIED_IN_DEF_SESSION */
#endif /* PROG_RESPOND_TO_PROG_SESSION == STD_ON */
#endif /* PROG_RESPOND_TO_PROG_SESSION */
#endif /* BLPDUR_USE_PROG == STD_ON */

    } /* RQD_BLPDUR_RECEPTION_031 */

    (void)UDS_RxRequest(&ulLen, paubUdsData, ulUdsDataSize); /* RQD_BLPDUR_RECEPTION_032 */

    DBG_BLPDUR_SIMULATERXREQUEST_EXIT();
}

void BlPduR_RxInd(PduIdType RxPduId, tBlPduRStatus eBlPduRStatus)
{
    /* Deviation CERTC-1 */
    tBufferConfigType* curBufCfg = NULL_PTR;
#if (BLPDUR_USE_UDS == STD_ON)
    tUdsStatus eUdsPendingStatus;
#endif
    /* RQD_BLPDUR_CONN_TREATMENT_014 */
    curBufCfg = BlPduR_GetRxInProgressBuf(RxPduId);
    if ((BLPDUR_E_OK != eBlPduRStatus) && (curBufCfg != NULL_PTR))
    {
        /* RQD_BLPDUR_CONN_TREATMENT_014 */
        BLPDUR_ENTER_CRITICAL_SECTION();
        curBufCfg->bufferInfo->state = BLPDUR_BUFF_IDLE;
        /* Deviation CERTC-1 */
        curBufCfg = NULL_PTR;
        BLPDUR_EXIT_CRITICAL_SECTION();
    }
    if ((curBufCfg != NULL_PTR) && (RxPduId < BLPDUR_MAX_RX_PDU_NUM))
    {
        boolean isTesterPresent    = FALSE;
        boolean isConnectionActive = FALSE;
        boolean isRxActTester      = FALSE;
        boolean isBigResponder = FALSE;
        BLPDUR_ENTER_CRITICAL_SECTION();
        if ((curBufCfg->ptrBuffer[0] == 0x3EU) &&
            (curBufCfg->ptrBuffer[1] == 0x80U) &&
            (curBufCfg->bufferInfo->filledLen == 2U))
        {
            isTesterPresent = TRUE;
        }
        else if ((curBufCfg->ptrBuffer[0] == 0x22U) || (curBufCfg->ptrBuffer[0] == 0x27U) )
        {   /* RQD_BLPDUR_CONN_TREATMENT_042 */
            isBigResponder = TRUE;
        }
    else
    {

    }
        if (m_ubSessionConnection != BLPDUR_NO_ACTIVE_CONNECTION)
        {
            isConnectionActive = TRUE;
        }
        if (stRxPdu[RxPduId].ConnectionNum == m_ubSessionConnection)
        {
            isRxActTester = TRUE;
        }
        BLPDUR_EXIT_CRITICAL_SECTION();
        if (isBigResponder == TRUE)
        {   /* RQD_BLPDUR_CONN_TREATMENT_042 */
            /* Deviation CERTC-1 */
            tBufferConfigType* newBuf = NULL_PTR;
            newBuf = BlPduR_GetFreeBufCfg(BLPDUR_RX_SMALL_BUFFERSIZE + 1U);
            if (newBuf != NULL_PTR)
            {
                BLPDUR_ENTER_CRITICAL_SECTION();
                TS_MemCpy(newBuf->ptrBuffer, curBufCfg->ptrBuffer, curBufCfg->size);
                newBuf->bufferInfo->filledLen = curBufCfg->bufferInfo->filledLen;
                newBuf->bufferInfo->dataMark  = curBufCfg->bufferInfo->dataMark;
                newBuf->bufferInfo->state     = curBufCfg->bufferInfo->state;
                newBuf->bufferInfo->originatingRxPduId = curBufCfg->bufferInfo->originatingRxPduId;
                newBuf->bufferInfo->counter   = curBufCfg->bufferInfo->counter;
                newBuf->bufferInfo->locked    = curBufCfg->bufferInfo->locked;
                BLPDUR_EXIT_CRITICAL_SECTION();
                BlPduR_ReleaseBuffers(curBufCfg->bufferInfo);
                curBufCfg = newBuf;
            }
        }
        /* RQD_BLPDUR_CONN_TREATMENT_015 */
        if (isTesterPresent == TRUE)
        { /* RQD_BLPDUR_RECEPTION_003 */
            BLPDUR_ENTER_CRITICAL_SECTION();
            curBufCfg->bufferInfo->state = BLPDUR_BUFF_IDLE;
            BLPDUR_EXIT_CRITICAL_SECTION();
#if (BLPDUR_USE_UDS == STD_ON)
            eUdsPendingStatus = UDS_IsPending();
            if (UDS_FALSE == eUdsPendingStatus)
#endif
            {
                /* RQD_BLPDUR_CONN_TREATMENT_016 */
                if (isConnectionActive == TRUE)
                {
                    if (isRxActTester == TRUE)
                    {
                        UDS_ReloadTStopDiag();
                    }
                }
            }
        }
        else
        {
            /* RQD_BLPDUR_CONN_TREATMENT_017 */
            BLPDUR_ENTER_CRITICAL_SECTION();
            curBufCfg->bufferInfo->state = BLPDUR_BUFF_RXQUEUED;
            BLPDUR_EXIT_CRITICAL_SECTION();
        }
    }
    /* RQD_BLPDUR_RECEPTION_002 */
    /* PduId cast to be compatible with old prototype format */
    APP_TpRxInd((u8)(RxPduId & 0x00FFU), eBlPduRStatus);  /* RQD_BLPDUR_CONN_TREATMENT_018 */
#if (BLPDUR_USE_PROG == STD_ON)
    /* PduValue cast to be compatible with old prototype format */
    PROG_TpRxInd((u8)(RxPduId & 0x00FFU), eBlPduRStatus); /* RQD_BLPDUR_CONN_TREATMENT_019 */
#endif

}

void UDS_SessionStatusInd (tUdsSessionType eUdsNewSessType,tUdsSessionType eUdsOldSessType,tUdsChangeReason eUdsChangingCause)
{  /*  RQD_BLPDUR_CONN_TREATMENT_020 */
    DBG_UDS_SESSIONSTATUSIND_ENTRY(eUdsNewSessType,eUdsOldSessType,eUdsChangingCause);
#if (BLPDUR_USE_PROG == STD_ON)
    BLPDUR_ENTER_CRITICAL_SECTION();
    if(eUdsNewSessType != UDS_SESSION_DEFAULT)
    {   /*  RQD_BLPDUR_CONN_TREATMENT_021 */
        /* If the current connection is set to no active connection, then the request have been received from application and we need to retrive the connection info */
        if(m_ubCurrentConnection == BLPDUR_NO_ACTIVE_CONNECTION)
        {
            BlPduR_RetrieveConnectionInfo();
        }
        m_ubSessionConnection = m_ubCurrentConnection;
    }
    else
    {   /*  RQD_BLPDUR_CONN_TREATMENT_022 */
        m_ubSessionConnection = BLPDUR_NO_ACTIVE_CONNECTION;
    }
    BLPDUR_EXIT_CRITICAL_SECTION();
    if(eUdsNewSessType == UDS_SESSION_PROGRAMMING)
    {   /* RQD_BLPDUR_SESSION_STATUS_IND_001 */
        /* action to perform on programming session opening */
        PROG_OpenProgrammingSession(); /*  RQD_BLPDUR_CONN_TREATMENT_023 */
    }
    else
    {
        /* if leaving programming session */
        if(eUdsOldSessType == UDS_SESSION_PROGRAMMING)
        {   /*  RQD_BLPDUR_CONN_TREATMENT_024 RQD_BLPDUR_SESSION_STATUS_IND_002 */
            PROG_CloseProgrammingSession(eUdsChangingCause);
        }
        else if(eUdsOldSessType == UDS_SESSION_EXTENDED_DIAG )
        {   /*  RQD_BLPDUR_CONN_TREATMENT_025 RQD_BLPDUR_SESSION_STATUS_IND_004 */
            PROG_CloseExtendedSession(eUdsChangingCause);
        }
        else
        {
            /* Nothing to do */
        }
    }
#endif /*(BLPDUR_USE_PROG == STD_ON)*/
    /* RQD_BLPDUR_SESSION_STATUS_IND_003 */
    /* Notify for diagnostic session transition */ /*  RQD_BLPDUR_CONN_TREATMENT_027 */
    APP_UdsSessionStatusInd (eUdsNewSessType, eUdsOldSessType, eUdsChangingCause);

    DBG_UDS_SESSIONSTATUSIND_EXIT();
}

#if (BLPDUR_SOURCE_ADDRESS_CHECK_ENABLE == STD_ON)
FUNC(void, PDUR_CODE) BlPduR_SaveTesterAddress(void)
{   /*  RQD_BLPDUR_CONN_TREATMENT_028 */
    DBG_BLPDUR_SAVETESTERADDRESS_ENTRY();
    /* RQD_BLPDUR_TESTER_001 */
    m_ubTesterAddress = stPduConnection[m_ubCurrentConnection].TestAddress;
    /* also store the connection number related to the tester address */
    m_ubStoredConnection = m_ubCurrentConnection;

    DBG_BLPDUR_SAVETESTERADDRESS_EXIT();
}
#endif


void BlPduR_RetrieveConnectionInfo(void)
{   /* RQD_BLPDUR_CONN_TREATMENT_029 */
    u8 ubRxPduId;
    DBG_BLPDUR_RETRIEVECONNECTIONINFO_ENTRY();
    BlPduR_GetRxPduId(&ubRxPduId); /* RQD_BLPDUR_CONNECTION_001 */
    BLPDUR_ENTER_CRITICAL_SECTION();
    /* If index is in the range of the table */
    if (BLPDUR_MAX_RX_PDU_NUM > ubRxPduId)
    {   /* RQD_BLPDUR_CONNECTION_002 */
        /* Store tester address and connection */
#if (BLPDUR_SOURCE_ADDRESS_CHECK_ENABLE == STD_ON)
        m_ubTesterAddress = stPduConnection[stRxPdu[ubRxPduId].ConnectionNum].TestAddress;
#endif
        m_ubCurrentConnection = stRxPdu[ubRxPduId].ConnectionNum;
        m_ubSessionConnection = stRxPdu[ubRxPduId].ConnectionNum;
        m_ubCurrentRxId = (u8)ubRxPduId;
#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON)
        m_ubGroupIdVal = stRxPdu[ubRxPduId].GroupId;
#endif
    }
    else
    {   /* RQD_BLPDUR_CONNECTION_003  */
        /* Set default connection and all tester allowed */
#if (BLPDUR_SOURCE_ADDRESS_CHECK_ENABLE == STD_ON)
        m_ubTesterAddress = BLPDUR_ALL_TESTER_ADDRESS;
#endif

        m_ubCurrentConnection = BLPDUR_NO_ACTIVE_CONNECTION;
#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON)
        m_ubGroupIdVal = BLPDUR_MULTIPLE_ID_NO_SEL;
#endif
    }
    BLPDUR_EXIT_CRITICAL_SECTION();

    DBG_BLPDUR_RETRIEVECONNECTIONINFO_EXIT();
}

#if (BLPDUR_SOURCE_ADDRESS_CHECK_ENABLE == STD_ON)
void BlPduR_SetTesterAddress(u16 ubTesterAddress)
{ /* RQD_BLPDUR_CONN_TREATMENT_030  */
    u8 ubIdx;
    u8 ubFound;
    ubFound = BLPDUR_FALSE;
    DBG_BLPDUR_SETTESTERADDRESS_ENTRY(ubTesterAddress);
    BLPDUR_ENTER_CRITICAL_SECTION();
    /* Check if tester address given is configured
     * If it exist store current connection */
    for(ubIdx = 0U; (ubIdx < BLPDUR_MAX_PDU_CONNECTION) && (ubFound != BLPDUR_TRUE); ubIdx++)
    {
        if (ubTesterAddress == stPduConnection[ubIdx].TestAddress)
        {   /* RQD_BLPDUR_TESTER_010 */
            /* Store tester address and connection */
            m_ubTesterAddress = ubTesterAddress;
            m_ubCurrentConnection = ubIdx;
            m_ubStoredConnection = ubIdx;
            ubFound = BLPDUR_TRUE;
        }
    }
    /* If the tester address given is not correct
     * set default connection and all tester allowed */
    if(ubFound == BLPDUR_FALSE)
    {   /* RQD_BLPDUR_TESTER_011 */
        m_ubTesterAddress = BLPDUR_ALL_TESTER_ADDRESS;
        m_ubCurrentConnection = BLPDUR_NO_ACTIVE_CONNECTION;
    } /* RQD_BLPDUR_TESTER_012 */
    BLPDUR_EXIT_CRITICAL_SECTION();

    DBG_BLPDUR_SETTESTERADDRESS_EXIT();
}
#endif

#if (BLPDUR_SOURCE_ADDRESS_CHECK_ENABLE == STD_ON)

StatusType BlPduR_VerifyTesterFilter(PduIdType RxPduId)
{  /* RQD_BLPDUR_CONN_TREATMENT_031 */
    u8 ubConnectionIndex;
    StatusType stdReturnValue;
    boolean impl20 = FALSE;
    boolean isTesterSet = FALSE;
#ifdef PROG_IMPL_VARIANT
#if (PROG_IMPL_VARIANT == PROG_IMPL_20)
    impl20 = TRUE;
#endif /* (PROG_IMPL_VARIANT == PROG_IMPL_20) */
#endif /* PROG_IMPL_VARIANT */
    BLPDUR_ENTER_CRITICAL_SECTION();
    /* tester address is not set yet, accept connection */
    if (BLPDUR_ALL_TESTER_ADDRESS == m_ubTesterAddress)
    {
        isTesterSet = TRUE;
    }
    BLPDUR_EXIT_CRITICAL_SECTION();
    if(isTesterSet == TRUE)
    {   /* RQD_BLPDUR_TESTER_020 */
        stdReturnValue = E_OK;
    }
    else
    {
        if (RxPduId < BLPDUR_MAX_RX_PDU_NUM)
        {
            boolean impl20isPDUIdOk = FALSE;
            BLPDUR_ENTER_CRITICAL_SECTION();
            if ( (stRxPdu[RxPduId].RxPduType == BLPDUR_STANDARD_CAN_ID) &&
                  impl20 )
            {
                impl20isPDUIdOk = TRUE;
            }
            BLPDUR_EXIT_CRITICAL_SECTION();
            if (impl20isPDUIdOk == TRUE)
            {   /* RQD_BLPDUR_TESTER_023 */
                /* no test filtering on standard CAN */
                stdReturnValue = E_OK;
            }
            else
            {
                BLPDUR_ENTER_CRITICAL_SECTION();
                /* get connection index */
                ubConnectionIndex = stRxPdu[RxPduId].ConnectionNum;
                /* get tester address associated to that connection */
                if (m_ubTesterAddress == stPduConnection[ubConnectionIndex].TestAddress)
                {   /* RQD_BLPDUR_TESTER_022 */
                    stdReturnValue = E_OK;
                }
                else
                {   /* RQD_BLPDUR_TESTER_021 */
                    stdReturnValue = E_NOT_OK;
                }
                BLPDUR_EXIT_CRITICAL_SECTION();
            }
        }
        else
        {
            stdReturnValue = E_NOT_OK;
        }
    }
    return stdReturnValue;
}
#endif
