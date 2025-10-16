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
/*%%   _____________________________   %%  \file BlPduR_Buf_Mng.c                */
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
* This initialisation of pointer to NULL is needed at this place as otherwise it can result in
* no value assigned in certain conditions and this will have a junk value if not initialised.
*/

#include "BlPduR_Prj.h"
#include "BlPduR_Priv.h"
#include <BlPduR_Trace.h>
#include <TSMem.h>          /* EB specific memory functions */
#include <Base_Modules.h>   /* Module enable defines and standard config pointer names */
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
NCS_PRI_VAR u32 m_pubRxCounter;
static tBufferConfigType* m_apstMultipleReceptionBuffer[BLPDUR_RX_PHY_BUFFER_NUM];
static u8 m_ubBuffLockCount;
/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
/*                                                                               */

/*===============================================================================*/

/*=============================== IMPLEMENTATION ================================*/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */
void BlPduR_Buf_Init(void)
{
    u8 ubIdx;
    BLPDUR_ENTER_CRITICAL_SECTION();
    for(ubIdx = 0U;ubIdx <BLPDUR_RX_PHY_BUFFER_NUM; ubIdx++)
    {
        /* RQD_BLPDUR_BUF_MNG_001 */
        /* Deviation CERTC-1 */
        m_apstMultipleReceptionBuffer[ubIdx] = NULL_PTR;
    }
    m_ubBuffLockCount = 0U;
    BLPDUR_EXIT_CRITICAL_SECTION();
    for(ubIdx = 0U; ubIdx < (BLPDUR_MAX_RX_PDU_NUM); ubIdx++)
    {
        tBufferInfoType* bufInfo = stRxSmallBufferConfig[ubIdx].bufferInfo;
        BlPduR_ReleaseBuffers(bufInfo);
    }

    for(ubIdx = 0U; ubIdx < (BLPDUR_RX_PHY_BUFFER_NUM); ubIdx++)
    {
        tBufferInfoType* bufInfo = stRxPhysBufferConfig[ubIdx].bufferInfo;
        BlPduR_ReleaseBuffers(bufInfo);
    }
}

tBufferConfigType* BlPduR_GetFreeBufCfg(PduLengthType TpSduLength)
{ /* RQD_BLPDUR_BUF_MNG_032 */


    u8 ubIdx;
    /* Deviation CERTC-1 */
    tBufferConfigType* curBufCfg = NULL_PTR;

    BLPDUR_ENTER_CRITICAL_SECTION();
    if (TpSduLength <= BLPDUR_RX_SMALL_BUFFERSIZE) /* RQD_BLPDUR_BUF_MNG_001 */
    {
        /* search a free buffer from the small buffer list */
        for(ubIdx = 0U; ubIdx < (BLPDUR_MAX_RX_PDU_NUM); ubIdx++)
        {
            tBufferInfoType* bufInfo = stRxSmallBufferConfig[ubIdx].bufferInfo;
            if (bufInfo->state == BLPDUR_BUFF_IDLE)
            {
                curBufCfg = &stRxSmallBufferConfig[ubIdx];
                break;
            }
        }
    }

    if (curBufCfg == NULL_PTR)
    {
        /* search a free buffer from the big buffer list */
        for(ubIdx = 0U; ubIdx < (BLPDUR_RX_PHY_BUFFER_NUM); ubIdx++)
        {
            tBufferConfigType* curRxBufCfg = &stRxPhysBufferConfig[ubIdx];
            tBufferInfoType* bufInfo = stRxPhysBufferConfig[ubIdx].bufferInfo;
            if ( (bufInfo->state == BLPDUR_BUFF_IDLE) &&
                 (TpSduLength <= curRxBufCfg->size) )
            {
                curBufCfg = &stRxPhysBufferConfig[ubIdx];
                break;
            }
        }
    }

    BLPDUR_EXIT_CRITICAL_SECTION();

    return curBufCfg;
}

/* get the next buffer which as been received in order */
static tBufferConfigType* GetNxtQueuedBuf(tBufferStateType refState)
{  /* RQD_BLPDUR_BUF_MNG_034  */
    u8 ubIdx;
    uint32 compare_cnt = 0xFFFFFFFFU;
    /* Deviation CERTC-1 */
    tBufferConfigType* result = NULL_PTR;

    BLPDUR_ENTER_CRITICAL_SECTION();
    for(ubIdx = 0U; ubIdx < (BLPDUR_MAX_RX_PDU_NUM); ubIdx++)
    {
        tBufferInfoType* bufInfo = stRxSmallBufferConfig[ubIdx].bufferInfo;
        if (bufInfo->state == refState)
        {
            if (bufInfo->counter <= compare_cnt)
            {
                result = &stRxSmallBufferConfig[ubIdx];
                compare_cnt = bufInfo->counter;
            }
        }
    }

    for(ubIdx = 0U; ubIdx < (BLPDUR_RX_PHY_BUFFER_NUM); ubIdx++)
    {
        tBufferInfoType* bufInfo = stRxPhysBufferConfig[ubIdx].bufferInfo;
        if (bufInfo->state == refState)
        {
            if (bufInfo->counter <= compare_cnt)
            {
                result = &stRxPhysBufferConfig[ubIdx];
                compare_cnt = bufInfo->counter;
            }
        }
    }
    BLPDUR_EXIT_CRITICAL_SECTION();
    return result;
}

#if (BLPDUR_MULTIPLE_BUFFERS_ENABLE ==  STD_ON)
static u8 GetNumFreeBuf(void)
{ /* RQD_BLPDUR_BUF_MNG_038 */
    u8 ubIdx;
    u8 retval = 0U;

    BLPDUR_ENTER_CRITICAL_SECTION();
    for(ubIdx = 0U; ubIdx < (BLPDUR_RX_PHY_BUFFER_NUM); ubIdx++)
    {
        tBufferInfoType* bufInfo = stRxPhysBufferConfig[ubIdx].bufferInfo;
        if (bufInfo->state == BLPDUR_BUFF_IDLE)
        {
            retval++;
        }
    }
    BLPDUR_EXIT_CRITICAL_SECTION();
    return retval;
}
#endif


tBufferConfigType* BlPduR_GetRxInProgressBuf(PduIdType RxPduId)
{ /* RQD_BLPDUR_BUF_MNG_039 */
    u8 ubIdx;
    /* Deviation CERTC-1 */
    tBufferConfigType* result = NULL_PTR;

    BLPDUR_ENTER_CRITICAL_SECTION();
    for(ubIdx = 0U; ubIdx < (BLPDUR_MAX_RX_PDU_NUM); ubIdx++)
    {
        tBufferInfoType* bufInfo = stRxSmallBufferConfig[ubIdx].bufferInfo;
        if (bufInfo->state == BLPDUR_BUF_RX_IN_PROGRESS)
        {
            if (bufInfo->originatingRxPduId == RxPduId)
            {
                result = &stRxSmallBufferConfig[ubIdx];
                break;
            }
        }
    }
    if (result == NULL_PTR)
    {
        for(ubIdx = 0U; ubIdx < (BLPDUR_RX_PHY_BUFFER_NUM); ubIdx++)
        {
            tBufferInfoType* bufInfo = stRxPhysBufferConfig[ubIdx].bufferInfo;
            if (bufInfo->state == BLPDUR_BUF_RX_IN_PROGRESS)
            {
                if (bufInfo->originatingRxPduId == RxPduId)
                {
                    result = &stRxPhysBufferConfig[ubIdx];
                    break;
                }
            }
        }
    }
    BLPDUR_EXIT_CRITICAL_SECTION();
    return result;
}


tBufferConfigType* BlPduR_GetNxtProcBuf(void)
{   /* RQD_BLPDUR_BUF_MNG_042  */
    u8 ubIdx;
    /* Deviation CERTC-1 */
    tBufferConfigType* result = NULL_PTR;

    BLPDUR_ENTER_CRITICAL_SECTION();
    for(ubIdx = 0U; ubIdx < (BLPDUR_MAX_RX_PDU_NUM - 1U); ubIdx++)
    {
        tBufferInfoType* bufInfo = stRxSmallBufferConfig[ubIdx].bufferInfo;
        if ((bufInfo->state == BLPDUR_BUFF_RXPROCESSING) && (bufInfo->locked == FALSE))
        {
            result = &stRxSmallBufferConfig[ubIdx];
            break;
        }
    }
    if (result == NULL_PTR)
    {
        for(ubIdx = 0U; ubIdx < (BLPDUR_RX_PHY_BUFFER_NUM); ubIdx++)
        {
            tBufferInfoType* bufInfo = stRxPhysBufferConfig[ubIdx].bufferInfo;
            if ((bufInfo->state == BLPDUR_BUFF_RXPROCESSING) && (bufInfo->locked == FALSE))
            {
                result = &stRxPhysBufferConfig[ubIdx];
                break;
            }
        }
    }
    BLPDUR_EXIT_CRITICAL_SECTION();
    return result;
}


tBufferConfigType* BlPduR_GetNxtQueuedRxBuf(void)
{ /* RQD_BLPDUR_BUF_MNG_035 */
    return GetNxtQueuedBuf(BLPDUR_BUFF_RXQUEUED);
}

tBufferConfigType* BlPduR_GetNxtQueuedTxBuf(void)
{ /* RQD_BLPDUR_BUF_MNG_036 */
    return GetNxtQueuedBuf(BLPDUR_BUFF_TXQUEUED);
}

uint32 BlPduR_GetRxCnt(void)
{ /* RQD_BLPDUR_BUF_MNG_034  */
    uint32 result = 0U;
    BLPDUR_ENTER_CRITICAL_SECTION();
    result = m_pubRxCounter;
    BLPDUR_EXIT_CRITICAL_SECTION();
    return result;
}

void BlPduR_IncrementRxCnt(void)
{ /* RQD_BLPDUR_BUF_MNG_034  */
    BLPDUR_ENTER_CRITICAL_SECTION();
    if (m_pubRxCounter<0xFFFFFFFFU)
    {
        m_pubRxCounter++;
    }
    else
    {
        m_pubRxCounter = 0U;
    }

    BLPDUR_EXIT_CRITICAL_SECTION();
}

/*----------------------------------{BlPduR_ReleaseBuffers}------------------------*/
void BlPduR_ReleaseBuffers(tBufferInfoType* pBufferInfo)
{ /* RQD_BLPDUR_BUF_MNG_043  */
    if (pBufferInfo != NULL_PTR)
    {
        BLPDUR_ENTER_CRITICAL_SECTION();
        /* set buffer state to idle */
        pBufferInfo->state = BLPDUR_BUFF_IDLE;
        /* reset filled buffer length */
        pBufferInfo->filledLen = 0U;
        /* reset buffer data marking variables */
        pBufferInfo->dataMark = 0U;
        pBufferInfo->counter = 0U;
        pBufferInfo->originatingRxPduId = 0U;
        pBufferInfo->locked = FALSE;
        BLPDUR_EXIT_CRITICAL_SECTION();
    }
}

/*-------------------------------{BlPduR_LockBuffer}------------------------------*/
#if (BLPDUR_MULTIPLE_BUFFERS_ENABLE ==  STD_ON)
void BlPduR_LockBuffer(u8* pubIsLastBuffer)
{
    tBufferConfigType* curRxBufferCfg;
    u8 freeBufCnt = 0U;
    DBG_BLPDUR_LOCKBUFFER_ENTRY(pubIsLastBuffer);
    curRxBufferCfg = BlPduR_GetNxtProcBuf();
    freeBufCnt = GetNumFreeBuf(); /* RQD_BLPDUR_BUF_MNG_038 */
    if (freeBufCnt <= 1U)
    {
        *pubIsLastBuffer = TRUE; /* RQD_BLPDUR_BUFFERS_002 */
    }
    else
    {
        *pubIsLastBuffer = FALSE;
    }

    BLPDUR_ENTER_CRITICAL_SECTION();
    if ((curRxBufferCfg != NULL_PTR) && (m_ubBuffLockCount<BLPDUR_RX_PHY_BUFFER_NUM))
    { /* RQD_BLPDUR_BUFFERS_001 */
        /* The buffer reception order shall stored for the multiplebuffer treatment */
        m_apstMultipleReceptionBuffer[m_ubBuffLockCount] = curRxBufferCfg;

        /* Set the buffer in lock state */
        curRxBufferCfg->bufferInfo->locked = TRUE;

        /* Increment the number of lock buffer */
        m_ubBuffLockCount++;
    }
    BLPDUR_EXIT_CRITICAL_SECTION();
    DBG_BLPDUR_LOCKBUFFER_EXIT();
}
#endif
/*----------------------------{end BlPduR_LockBuffer}-----------------------------*/

/*-----------------------------{BlPduR_UnlockBuffer}------------------------------*/
#if (BLPDUR_MULTIPLE_BUFFERS_ENABLE ==  STD_ON)
void BlPduR_UnlockBuffer(u8 ubBufferType)
{
    u8 ubIdx;
    DBG_BLPDUR_UNLOCKBUFFER_ENTRY(ubBufferType);
    /* If buffer is the first buffer locked */
    if (BLPDUR_OLD_BUFFER == ubBufferType)
    {
        /* RQD_BLPDUR_BUF_MNG_061 RQD_BLPDUR_BUFFERS_020*/
        /* Deviation CERTC-1 */
        tBufferInfoType* pBufferInfo = NULL_PTR;
        BLPDUR_ENTER_CRITICAL_SECTION();
        if  ( (m_apstMultipleReceptionBuffer[0U] != NULL_PTR) &&
             (m_apstMultipleReceptionBuffer[0]->bufferInfo != NULL_PTR) &&
             (m_ubBuffLockCount > 0U) )
        {
            pBufferInfo = m_apstMultipleReceptionBuffer[0U]->bufferInfo;
            m_apstMultipleReceptionBuffer[0U]->bufferInfo->locked = FALSE;
            /* shift reception flag */
            for(ubIdx = 0U; ubIdx < (BLPDUR_RX_PHY_BUFFER_NUM-1U); ubIdx++)
            {
                m_apstMultipleReceptionBuffer[ubIdx] = m_apstMultipleReceptionBuffer[ubIdx + 1U];
            }
            /* reset last reception flag to ensure the invalid value */
            /* Deviation CERTC-1 */
            m_apstMultipleReceptionBuffer[BLPDUR_RX_PHY_BUFFER_NUM-1U] = NULL_PTR;
            /* Decrement count of buffer locked */
            m_ubBuffLockCount--;
        }
        BLPDUR_EXIT_CRITICAL_SECTION();
        if (pBufferInfo != NULL_PTR)
        {
            BlPduR_ReleaseBuffers(pBufferInfo);
        }
    }
    else /* otherwise reset all buffers */
    { /* RQD_BLPDUR_BUF_MNG_071 RQD_BLPDUR_BUFFERS_021 */
        BLPDUR_ENTER_CRITICAL_SECTION();
        for(ubIdx = 0U;ubIdx <BLPDUR_RX_PHY_BUFFER_NUM; ubIdx++)
        {
            /* Release all buffer */
            stRxPhysBufferConfig[ubIdx].bufferInfo->locked = FALSE;
            /* release all queued element */
            /* Deviation CERTC-1 */
            m_apstMultipleReceptionBuffer[ubIdx] = NULL_PTR;
        }
        /* Reinit the counter */
        m_ubBuffLockCount = 0U;
        BLPDUR_EXIT_CRITICAL_SECTION();
    }

    DBG_BLPDUR_UNLOCKBUFFER_EXIT();
}
#endif
/*--------------------------{end BlPduR_UnlockBuffer}-----------------------------*/

/*----------------------------{BlPduR_GetNextBuffer}------------------------------*/
#if (BLPDUR_MULTIPLE_BUFFERS_ENABLE ==  STD_ON)
void BlPduR_GetNextBuffer(PduLengthType *pulLen, u8 ** paubData)
{ /* RQD_BLPDUR_BUF_MNG_070  */
    DBG_BLPDUR_GETNEXTBUFFER_ENTRY(pulLen,paubData);
    BLPDUR_ENTER_CRITICAL_SECTION();
    if(m_apstMultipleReceptionBuffer[0U] == NULL_PTR)
    {   /* RQD_BLPDUR_BUFFERS_030 */
        /* First buffer is not locked. No buffer is taken*/
        *paubData = NULL_PTR;
        *pulLen = 0U;
    }
    else
    {   /* RQD_BLPDUR_BUFFERS_031 */
        /* First buffer is taken*/
        *paubData = m_apstMultipleReceptionBuffer[0U]->ptrBuffer;
        *pulLen = m_apstMultipleReceptionBuffer[0U]->bufferInfo->filledLen;
    }
    BLPDUR_EXIT_CRITICAL_SECTION();
    DBG_BLPDUR_GETNEXTBUFFER_EXIT();
}
#endif
/*-------------------------{end BlPduR_GetNextBuffer}-----------------------------*/

uint32 BlPduR_GetBufferSize(void)
{
    uint32             result=0U;
    /* Deviation CERTC-1 */
    tBufferConfigType* curBufCfg = NULL_PTR;
    if (BLPDUR_E_BUSY == BlPduR_GetTreatmentStatus())
    {
        curBufCfg = BlPduR_GetNxtProcBuf(); /* RQD_BLPDUR_BUF_MNG_042 */
        if (curBufCfg != NULL_PTR)
        {
            result = curBufCfg->size;
        }
    }
    return result;
}

boolean BlPduR_GetBiggerBuffer(PduLengthType *pulLen, u8 ** paubData)
{   /* RQD_BLPDUR_BUF_MNG_046 */
    /* Deviation CERTC-1 */
    tBufferConfigType* curBufCfg = NULL_PTR;
    /* Deviation CERTC-1 */
    tBufferConfigType* newBuf    = NULL_PTR;
    boolean            result    = BLPDUR_FALSE;

    if (BLPDUR_E_BUSY == BlPduR_GetTreatmentStatus())
    {   /* RQD_BLPDUR_BUF_MNG_047 */
        curBufCfg = BlPduR_GetNxtProcBuf();
        newBuf = BlPduR_GetFreeBufCfg(BLPDUR_RX_SMALL_BUFFERSIZE+1U);
        if (newBuf != NULL_PTR)
        {   /* RQD_BLPDUR_BUF_MNG_047 */
            BLPDUR_ENTER_CRITICAL_SECTION();
            TS_MemCpy(newBuf->ptrBuffer, curBufCfg->ptrBuffer, curBufCfg->size);
            newBuf->bufferInfo->filledLen = curBufCfg->bufferInfo->filledLen;
            newBuf->bufferInfo->dataMark = curBufCfg->bufferInfo->dataMark;
            newBuf->bufferInfo->state = curBufCfg->bufferInfo->state;
            newBuf->bufferInfo->originatingRxPduId = curBufCfg->bufferInfo->originatingRxPduId;
            newBuf->bufferInfo->counter = curBufCfg->bufferInfo->counter;
            newBuf->bufferInfo->locked = curBufCfg->bufferInfo->locked;
            *paubData = newBuf->ptrBuffer;
            *pulLen = newBuf->size;
            BLPDUR_EXIT_CRITICAL_SECTION();
            BlPduR_ReleaseBuffers(curBufCfg->bufferInfo); /* RQD_BLPDUR_BUF_MNG_045 */
            result = BLPDUR_TRUE;
        }
    }
    return result;
}
