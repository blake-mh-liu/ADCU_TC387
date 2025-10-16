/*===============================================================================*/
/*                                                                               */
/*                               BOOT Layers                                     */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                               BlPduR layer                                      */
/*                                                                               */
/*===============================================================================*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file BlPduR_Lin.c                    */
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
/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.3 (required)
 * A cast shall not be performed between a pointer to object type and a pointer to a different
 * object type.
 *
 *   Reason:
 * The memory routines are optimized for dealing with aligned memory
 * and the correct alignment has been checked before converting
 * to different object types
 */
/*=============================== FILE INCLUSION ================================*/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files: BlPduR                                                        */
#include "BlPduR_Prj.h"

#if (BLPDUR_NETWORK_LIN_SUPPORTED == STD_ON)
#include "BlPduR_Priv.h"
#include <BlPduR_Trace.h>
#include <TSMem.h>          /* EB specific memory functions */
#include <Base_Modules.h>   /* Module enable defines and standard config pointer names */
/*                                                                               */
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

u8 aubBlPduRRxLinBuffer[BLPDUR_RX_PHYS_BUFFERSIZE];

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
/*--------------------------------{BLPDUR_LIN_Init}--------------------------------*/
void BlPduR_Lin_Init(void)
{
    u16 ubIdx;
    for(ubIdx=0U; ubIdx<BLPDUR_RX_PHYS_BUFFERSIZE; ubIdx++)
    {
        aubBlPduRRxLinBuffer[ubIdx]=0U;
    }/* RQD_BLPDUR_LIN_INIT_001 */
}
/*--------------------------------{end BLPDUR_LIN_Init}----------------------------*/
/*--------------------------------{LIN_StatusInd}--------------------------------*/
#if (LIN_CTRL_MAX > 1)
void LIN_StatusInd (u8 ubCtrlIdx, tLinFrameIdx uFrameIdx, tLinFrameStatus eStatus)
#else
void LIN_StatusInd (tLinFrameIdx uFrameIdx, tLinFrameStatus eStatus)
#endif
{
    /* Successfull transmission */
    if (eStatus == LIN_STATUS_TX_OK)
    {
#if BLPDUR_LIN_BIT_RESPONSE_ENABLE == STD_ON
        /* The error_response bit is clear */
        if (uFrameIdx == BLPDUR_LIN_FRAME_IDX_BIT_RESP_ERROR)
        {
            LIN_WR_BIT_RESPONSE_ERROR(LIN_FALSE);
        }
#endif

        /* For the Transport Protocol, N_As indication
           Associate the COM frame to the TP message */
        if (uFrameIdx == BLPDUR_LIN_FRAME_IDX_TX)
        {
            /* Call LTP Tx Confirmation */
            LTP_LinTxConf(); /* RQD_BLPDUR_LIN_STATUSIND_005 */
        }
    }
}
/*---------------------------------{end LIN_StatusInd}----------------------------*/

/*----------------------------------{LIN_ComLossInd}--------------------------------*/
void LIN_ComLossInd(void)
{   /* RQD_BLPDUR_LIN_COMLOSSIND_001 */
    /* Switch the LIN layer to Anormal mode */
    (void)l_ifc_disconnect ();
}
/*----------------------------------{end LIN_ComLossInd}----------------------------*/

/*----------------------------------{LIN_WakeUpInd}--------------------------------*/
void LIN_WakeUpInd(void)
{   /* RQD_BLPDUR_LIN_WAKEUPIND_001 */
    /* Switch the LIN layer to Normal mode */
    (void)l_ifc_connect ();
}
/*----------------------------------{end LIN_WakeUpInd}----------------------------*/

/*-----------------------------{LTP_RxInd}------------------------------------------*/
void LTP_RxInd (u8 ebStatus)
{
    /* Transport Protocol functions return status */
    tLtpStatus eStatus = LTP_MSG_STATUS_NAS;
    uint8* ptr_Buffer;
    ptr_Buffer = &aubBlPduRRxLinBuffer[0];

    if(ebStatus == LTP_MSG_STATUS_OK)
    {
        if((m_ubCurrentConnection == BLPDUR_NO_ACTIVE_CONNECTION) || (m_ubCurrentConnection == stRxPdu[BLPDUR_RX_LIN].ConnectionNum))
        {
            u16 TpSduLength;

            eStatus = LTP_GetMsgData (&TpSduLength, &ptr_Buffer);

            if(eStatus == LTP_MSG_STATUS_OK)
            {   /* RQD_BLPDUR_LIN_RECEPTION_002 */ /* RQD_BLPDUR_LIN_RECEPTION_003 */
                tBufferConfigType* curBufCfg = BlPduR_GetFreeBufCfg(TpSduLength);
                if (curBufCfg != NULL_PTR)
                {
                    TS_MemCpy(curBufCfg->ptrBuffer, aubBlPduRRxLinBuffer, TpSduLength);
                    BlPduR_IncrementRxCnt();
                    curBufCfg->bufferInfo->state              = BLPDUR_BUF_RX_IN_PROGRESS;
                    curBufCfg->bufferInfo->filledLen          = TpSduLength;
                    curBufCfg->bufferInfo->dataMark           = TpSduLength;
                    curBufCfg->bufferInfo->originatingRxPduId = BLPDUR_RX_LIN;
                    curBufCfg->bufferInfo->counter            = BlPduR_GetRxCnt();
                    BlPduR_RxInd(BLPDUR_RX_LIN, BLPDUR_E_OK );
                }
                /* RQD_BLPDUR_LIN_RECEPTION_005 */
                /* Stop S3 timer on start of frame reception */
                UDS_StopSessionTimer();

                APP_TpRxInd(BLPDUR_RX_LIN, ebStatus);
            }
            else
            {   /* RQD_BLPDUR_LIN_RECEPTION_004 */
                BlPduR_RxInd(BLPDUR_RX_LIN, BLPDUR_E_NOT_OK );
            }
        }
    }
    else
    {   /* RQD_BLPDUR_LIN_RECEPTION_001 */
        BlPduR_RxInd(BLPDUR_RX_LIN, BLPDUR_E_NOT_OK );
    }

}
/*----------------------------------{end LTP_RxInd}--------------------------------*/

/*-----------------------------------{BlPduR_LinTpTxMessage}----------------------------------*/
tBlPduRStatus BlPduR_LinTpTxMessage (u16 uwlen, u8* pubData)
{
    tBlPduRStatus eBlPduRStatus = BLPDUR_E_OK;
    tLtpStatus eLtpStatus;
    /* RQD_BLPDUR_LIN_TRANSMISSION_001 */
    /* Store transmit buffer to manage TxConf correctly */
    m_pubTxBuffer = pubData;

    /* Write the answer message datas */
    eLtpStatus = LTP_SetMsgData (uwlen, pubData);

    /* The message datas update is complete without any error */
    if (eLtpStatus == LTP_ERR_OK)
    {   /* RQD_BLPDUR_LIN_TRANSMISSION_003  */
        /* Send the Diagnostic answer message */
        eLtpStatus = LTP_SendMsg();

        if (eLtpStatus != LTP_ERR_OK)
        {  /* RQD_BLPDUR_LIN_TRANSMISSION_005*/
            eBlPduRStatus = BLPDUR_E_NOT_OK;
        }
    }
    else
    {
        eBlPduRStatus = BLPDUR_E_NOT_OK;
    }

    return eBlPduRStatus;
}
/*----------------------------------{end BlPduR_LinTpTxMessage}-------------------------------*/

/*-----------------------------------{LTP_TxConf}----------------------------------*/
void LTP_TxConf (u8 ebStatus)
{
    if(ebStatus == LTP_MSG_STATUS_OK)
    {
        /* Call BlPduR TxConfirmation */
        BlPduR_TxConf(BLPDUR_LIN_TX_PDU,BLPDUR_E_OK);
    }
    else
    {
        /* Call BlPduR TxConfirmation */
        BlPduR_TxConf(BLPDUR_LIN_TX_PDU,BLPDUR_E_NOT_OK);
    }
}
/*----------------------------------{end LTP_TxConf}-------------------------------*/
#endif /* #if (BLPDUR_LIN_USED == STD_ON)*/
