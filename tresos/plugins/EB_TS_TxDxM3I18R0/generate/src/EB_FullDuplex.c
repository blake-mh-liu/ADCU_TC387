/*********************************************************************************/
/*                                                                               */
/*                                  CAN Stack                                    */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                                EB configuration                               */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file EB_FullDuplex.c                 */
/*%%  |                             |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%  Module version: 3.18.0 BL3                */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&    &&&&&             |  %%                                        */
/*%%  |   &       &    &            |  %%                                        */
/*%%  |   &&&&&   &&&&&             |  %%                                        */
/*%%  |_____________________________|  %%                                        */
/*%%                                   %%                                        */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*********************************************************************************/
/* Copyright 2010 by Elektrobit Automotive GmbH                                  */
/* All rights exclusively reserved for Elektrobit Automotive GmbH,               */
/* unless expressly agreed to otherwise.                                         */
/*********************************************************************************/
[!AUTOSPACING!]
[!NOCODE!]
[!VAR "FullDuplexUses" = "0"!]
[!VAR "FunctionalMsgExist" = "0"!]
[!IF "node:exists(as:modconf('Tp'))"!]
    [!FOR "MsgNB" = "1" TO "num:i(count(as:modconf('Tp')/Message/*))" STEP "1"!]
         [!IF "as:modconf('Tp')/Message/*[position()=$MsgNB]/Mode = 'Full_Duplex'"!]
            [!VAR "FullDuplexUses" = "1"!]
        [!ENDIF!]
        [!IF "(as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Obd' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag_Obd')  and as:modconf('Tp')/Message/*[position()=$MsgNB]/Adressing_Mode = 'Functional'"!]
            [!VAR "FunctionalMsgExist" = "1"!]
        [!ENDIF!]
    [!ENDFOR!]
    [!/* Activate generation of EB_Prg_Queued.c file*/!]
    [!IF "$FullDuplexUses = 0"!]
        [!SKIPFILE!]
    [!ENDIF!]
[!ELSE!]
    [!SKIPFILE!]
[!ENDIF!]
[!ENDNOCODE!]
[!CODE!]
/******************************** FILE INCLUSION *********************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Header Files: EB                                                            */
#include "EB_Prj.h"
[!IF "as:modconf('EB')/General/Osek_Autosar_Stack = 'AUTOSAR'"!]
#include "EB_Boot_PduR.h"
[!ENDIF!]
#include <EB_Trace.h>                        /* Dbg related macros for EB */
/*                                                                               */
/*********************************************************************************/

/****************************** PUBLIC DEFINITIONS *******************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */

/*-------------------------------------------------------------------------------*/
/* - Public Callback Prototypes                                                  */
/*                                                                               */
/*********************************************************************************/

/***************************** PRIVATE DEFINITIONS *******************************/
/*                                                                               */
/*-------------------------------------------------------------------------------*/
/* - Private Constants                                                           */

/*-------------------------------------------------------------------------------*/
/* - Private Types                                                               */

/*-------------------------------------------------------------------------------*/
/* - Private Variables                                                           */

[!IF "node:exists(as:modconf('Tp')) and node:exists(as:modconf('Uds'))"!]
/* Flag to notice TpRx indication */
[!LOOP "as:modconf('Tp')/Message/*"!]
    [!IF "(Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd')"!]
        [!IF "Mode = 'Full_Duplex'"!]
NCS_PRI_VAR u8 m_uEbTpMsgFlagIdx[!"name(.)"!];
        [!ENDIF!]
    [!ENDIF!]
[!ENDLOOP!]
[!ENDIF!]

NCS_PRI_VAR u8 m_aubMessageRxCnt[TP_MSG_MAX];
NCS_PRI_VAR tEbQueuedStatus m_ubReqTreatmentState[TP_MSG_MAX];
NCS_PRI_VAR u8 *m_paubUdsData;
NCS_PRI_VAR u16 m_uwLen;
/*-------------------------------------------------------------------------------*/
/* - Private Macros                                                              */

/*-------------------------------------------------------------------------------*/
/* - Private Function Prototypes                                                 */
NCS_PRI_FCT tEbQueuedStatus EB_SwapCheck(tTpMsgIdx uMsgIdx);

/*                                                                               */
/*********************************************************************************/


/******************************** IMPLEMENTATION *********************************/
/*                                                                               */

/*-------------------------------------------------------------------------------*/
/* - Public Functions                                                            */


/*----------------------------------{EB_InitFullDuplex}--------------------------------*/
void EB_InitFullDuplex(void)
{
    u8 ubIdx;

    DBG_EB_INITFULLDUPLEX_ENTRY();

    for(ubIdx = 0U; ubIdx < TP_MSG_MAX;ubIdx++)
    {
        m_aubMessageRxCnt[ubIdx] = 0U;
        m_ubReqTreatmentState[ubIdx] = EB_STATUS_NOT_STARTED;
    }

[!LOOP "as:modconf('Tp')/Message/*"!]
    [!IF "(Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd')"!]
        [!IF "Mode = 'Full_Duplex'"!]
    m_uEbTpMsgFlagIdx[!"name(.)"!] = EB_FALSE;
        [!ENDIF!]
    [!ENDIF!]
[!ENDLOOP!]
    DBG_EB_INITFULLDUPLEX_EXIT();
}
/*----------------------------------{End EB_InitFullDuplex}--------------------------------*/


[!IF "node:exists(as:modconf('Tp')) and node:exists(as:modconf('Uds'))"!]
    [!IF "count(as:modconf('Tp')/Message/*[(Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd')]) > 0"!]
/*----------------------------------{EB_TpRxMsgManageFullDuplex}--------------------------------*/
void EB_TpRxMsgManageFullDuplex (void)
{
    [!LOOP "as:modconf('Tp')/Message/*"!]
    [!IF "(Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd')"!]
        [!IF "Mode = 'Full_Duplex'"!]
    /* Check if a complete TP frame has been received */
    if ( EB_TRUE == m_uEbTpMsgFlagIdx[!"name(.)"!])
    {
        tTpMsgIdx uMsgIdx;
        /* Transport Protocol functions return status */
        tTpStatus eStatus ;
        tUdsBoolean eStatusRxReq;
        tEbQueuedStatus eEbQueuedStatus;
        u8 ubItStatus;
        [!IF "$FunctionalMsgExist = 1"!]
        u8 ubError;

        /* No error detected */
        ubError = EB_FALSE;
        [!ENDIF!]

        DBG_EB_TPRXMSGMANAGEFULLDUPLEX_ENTRY();

        uMsgIdx = TP_MSG_IDX_[!"name(.)"!];

        /* Disable interrupt while treating share flag */
        ubItStatus = APP_InterruptDisable();

        eEbQueuedStatus = EB_SwapCheck(uMsgIdx);
        
        if(EB_STATUS_OK == eEbQueuedStatus)
        {
            /* Reset indication flag */
            m_uEbTpMsgFlagIdx[!"name(.)"!] = EB_FALSE;
        }

        APP_InterruptEnable(ubItStatus);

        if((EB_STATUS_OK == eEbQueuedStatus) || (EB_STATUS_QUEUED == eEbQueuedStatus))
        {
            PduLengthType ulRxBufferSize;
            [!IF "as:modconf('EB')/General/Osek_Autosar_Stack = 'AUTOSAR'"!]
            /* The UDS buffer size is read from the configuration parameter TP_Buffer_Size_Functional and TP_Buffer_Size_Physical*/
            ulRxBufferSize = TP_UDS_GetBufferSize(uMsgIdx);
            [!ELSE!]
            /* For CAN, the buffer size is set to the 4096 Bytes*/
            ulRxBufferSize = EB_CAN_BUFFERSIZE;
            [!ENDIF!]
            /* Diagnostic request treatment */
            eStatusRxReq = UDS_RxRequestWithAddrMode (&m_uwLen, m_paubUdsData, ulRxBufferSize, [!IF "Adressing_Mode = 'Physical'"!]UDS_ADDR_PHYSICAL[!ELSE!]UDS_ADDR_FUNCTIONAL[!ENDIF!], [!IF "Type = 'Diag'"!]UDS_TYPE_DIAG[!ELSEIF "Type = 'Obd'"!]UDS_TYPE_OBD[!ELSEIF "Type = 'Diag_Obd'"!]UDS_TYPE_DIAG_OBD[!ENDIF!]);

            /* Callout to APP to indicate/update if necessary the data buffer*/
            APP_GetUdsDataBufferInd(&m_uwLen, m_paubUdsData, uMsgIdx, eStatusRxReq);

            if (eStatusRxReq == UDS_TRUE)
            {
                /* Answer to the request only it is asked by DIAG layer */
                if (m_uwLen > 0U)
                {
                    /* Write the answer message data */
                    eStatus = TP_SetMsgData (uMsgIdx, m_uwLen, m_paubUdsData);

                    /* The message data update is complete without any error */
                    if (eStatus == TP_ERR_OK)
                    {
                        [!IF "$FunctionalMsgExist = 1"!]
                        /* Send the Diagnostic answer message */
                        eStatus = TP_SendMsg (uMsgIdx);

                        if (eStatus != TP_ERR_OK)
                        {
                            ubError = EB_TRUE;
                        }
                        [!ELSE!]
                        (void)TP_SendMsg (uMsgIdx);
                        [!ENDIF!]
                    }
                    else
                    {
                        [!IF "$FunctionalMsgExist = 1"!]
                        ubError = EB_TRUE;
                        [!ELSE!]
                        /* Nothing to do */
                        [!ENDIF!]
                    }
                }
                else
                {
                    [!IF "$FunctionalMsgExist = 1"!]
                    ubError = EB_TRUE;
                    [!ELSE!]
                    /* Nothing to do */
                    [!ENDIF!]
                }
            }
            [!IF "as:modconf('Uds')/General/RESPONSE_PENDING = 'true'"!]
            /* In the case of a NRC 78 */
            else if (eStatusRxReq == UDS_NRC_78)
            {
                /* Memorize the TpMsgIdx in order to manage the next possible NRC78 */
                /* coming later with UDS_LongRequestResponseInd callback */
                m_ubTpMsgIdxNrc78 = uMsgIdx;
                [!IF "$FunctionalMsgExist = 1"!]
                /* Lock all functional channel during response pending to avoid any buffer problem */
                    [!FOR "MsgNB" = "1" TO "num:i(count(as:modconf('Tp')/Message/*))" STEP "1"!]
                        [!IF "(as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Obd' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag_Obd') and as:modconf('Tp')/Message/*[position()=$MsgNB]/Adressing_Mode = 'Functional'"!]
                        [!WS "16"!](void)TP_RxEnable(TP_MSG_IDX_[!"name(as:modconf('Tp')/Message/*[position()=$MsgNB])"!], TP_RX_ENABLE_OFF);
                        [!ENDIF!]
                    [!ENDFOR!]
                [!ENDIF!]
            }
            [!ENDIF!]
            else
            {
                [!IF "$FunctionalMsgExist = 1"!]
                /* Invalid parameter for function UDS_RxRequest */
                ubError = EB_TRUE;
                [!ELSE!]
                /* Nothing to do */
                [!ENDIF!]
            }
        }
        else if (EB_STATUS_ERROR == eEbQueuedStatus)
        {
            /* Reset indication flag */
            m_uEbTpMsgFlagIdx[!"name(.)"!] = EB_FALSE;
            [!IF "$FunctionalMsgExist = 1"!]
            /* Invalid parameter for function UDS_RxRequest */
            ubError = EB_TRUE;
            [!ENDIF!]
        }
        else
        {
            /* Nothing to do */
        }

        [!IF "$FunctionalMsgExist = 1"!]
        /* If an error happend un lock all TP channel */
        if (EB_TRUE == ubError)
        {
            [!FOR "MsgNB" = "1" TO "num:i(count(as:modconf('Tp')/Message/*))" STEP "1"!]
                [!IF "(as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Obd' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag_Obd') and as:modconf('Tp')/Message/*[position()=$MsgNB]/Adressing_Mode = 'Functional'"!]
                [!WS "12"!](void)TP_RxEnable(TP_MSG_IDX_[!"name(as:modconf('Tp')/Message/*[position()=$MsgNB])"!], TP_RX_ENABLE_ON);
                [!ENDIF!]
            [!ENDFOR!]
        }
        [!ENDIF!]
    }/* End of Uds message */
    else
    {
        DBG_EB_TPRXMSGMANAGEFULLDUPLEX_ENTRY();
    }
        [!ENDIF!]
    [!ELSE!]
        DBG_EB_TPRXMSGMANAGEFULLDUPLEX_ENTRY();
    [!ENDIF!]
    DBG_EB_TPRXMSGMANAGEFULLDUPLEX_EXIT();
    [!ENDLOOP!]

}
/*----------------------------------{End EB_TpRxMsgManageFullDuplex}--------------------------------*/
    [!ENDIF!]
[!ENDIF!]

/*----------------------------------{TP_TxConfFullDuplex}--------------------------------------*/
void TP_TxConfFullDuplex  (tTpMsgIdx uMsgIdx, u8 ebStatus)
{
    tTpStatus eStatus;

    DBG_TP_TXCONFFULLDUPLEX_ENTRY(uMsgIdx,ebStatus);

[!IF "node:exists(as:modconf('Uds')) and (count(as:modconf('Tp')/Message/*[(Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd')]) >= 1)"!]
  [!IF "as:modconf('Uds')/General/RESPONSE_PENDING = 'true'"!]

    /* NRC_78 TxConf is received */
    if ( uMsgIdx == m_ubTpMsgIdxNrc78 )
    {
        /* Transmission to UDS */
        UDS_LongRequestRespTxConf();
    }
    /* If not in response pending state unlock all TP channel */
    else
    {
        /* decrement  Message Rx Count */
        m_aubMessageRxCnt[uMsgIdx]--;

        /* Set treatment as not started since response has been sent */
        m_ubReqTreatmentState[uMsgIdx] = EB_STATUS_NOT_STARTED;

        if (1U == m_aubMessageRxCnt[uMsgIdx])
        {
            eStatus = TP_GetMsgData (uMsgIdx, &m_uwLen, &m_paubUdsData);

            if (eStatus == TP_ERR_OK)
            {
                (void)TP_SwapBuffer(uMsgIdx);
            }
        }
        /* Rx Count is 0 or >= 2 */
        else
        {
            [!IF "as:modconf('Tp')/TpGeneral/TpDataStreaming = 'true'"!]
            /* Allow streaming only if there is no other request in the queue (count = 0) */
            EB_SetStreamingStatus(EB_STREAMING_ALLOWED);
            [!ENDIF!]

            /* reset RxCount to 0 to go back on nominal behaviour if it is >= 2 (error case) */
             m_aubMessageRxCnt[uMsgIdx] = 0U;
        }
    [!IF "$FunctionalMsgExist = 1"!]
        /* Enable all TP functional channel after physical transmission are done*/
      [!FOR "MsgNB" = "1" TO "num:i(count(as:modconf('Tp')/Message/*))" STEP "1"!]
        [!IF "(as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Obd' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag_Obd') and as:modconf('Tp')/Message/*[position()=$MsgNB]/Adressing_Mode = 'Functional'"!]
            [!WS "8"!](void)TP_RxEnable(TP_MSG_IDX_[!"name(as:modconf('Tp')/Message/*[position()=$MsgNB])"!], TP_RX_ENABLE_ON);
        [!ENDIF!]
      [!ENDFOR!]
    [!ENDIF!]
  [!ELSE!]
    OSC_PARAM_UNUSED(eStatus);
  [!ENDIF!]

  [!IF "as:modconf('Uds')/General/RELOAD_TSTOPDIAG = 'true'"!]
        {
            switch(uMsgIdx)
            {
    [!FOR "MsgNB" = "1" TO "num:i(count(as:modconf('Tp')/Message/*))" STEP "1"!]
      [!IF "(as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Obd' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag_Obd')"!]
                case TP_MSG_IDX_[!"name(as:modconf('Tp')/Message/*[position()=$MsgNB])"!]:
      [!ENDIF!]
    [!ENDFOR!]
                    UDS_ReloadTStopDiag();
                    break;
                default:
                    /* Nothing to do */
                    break;
            }
        }
  [!ENDIF!]
  [!IF "as:modconf('Uds')/General/RESPONSE_PENDING = 'true'"!]
    }
  [!ENDIF!]
[!ENDIF!]

[!IF "as:modconf('EB')/General/Osek_Autosar_Stack = 'AUTOSAR'"!]
    EB_TxConf(uMsgIdx);
[!ENDIF!]
    APP_TpTxConf(uMsgIdx, ebStatus);
[!IF "node:exists(as:modconf('Prog'))"!]
    PROG_TpTxConf(uMsgIdx, ebStatus);
[!ENDIF!]
    DBG_TP_TXCONFFULLDUPLEX_EXIT();
}
/*----------------------------------{End TP_TxConfFullDuplex}--------------------------------------*/


/*----------------------------------{TP_RxIndFullDuplex}-------------------------------------------*/
void TP_RxIndFullDuplex (tTpMsgIdx uMsgIdx, u8 ebStatus)
{
    tTpStatus eStatus;

    DBG_TP_RXINDFULLDUPLEX_ENTRY(uMsgIdx,ebStatus);

[!IF "node:exists(as:modconf('Uds'))"!]
    [!VAR "DIAG_MESS_NB" = "count(as:modconf('Tp')/Message/*[(Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd')])"!]
    [!IF "$DIAG_MESS_NB > 0"!]
    if (ebStatus == TP_MSG_STATUS_OK)
    {
        switch(uMsgIdx)
        {
        [!LOOP "as:modconf('Tp')/Message/*"!]
            [!IF "(Type = 'Diag' or Type = 'Obd' or Type = 'Diag_Obd')"!]
                [!IF "Mode = 'Full_Duplex'"!]
            case TP_MSG_IDX_[!"name(.)"!]:
                if (0U == m_aubMessageRxCnt[uMsgIdx])
                {
                    eStatus = TP_GetMsgData (uMsgIdx, &m_uwLen, &m_paubUdsData);

                    if (eStatus == TP_ERR_OK)
                    {
                        eStatus = TP_SwapBuffer(uMsgIdx);

                         if (eStatus == TP_ERR_OK)
                        {
                            m_aubMessageRxCnt[uMsgIdx]++;
                            /* Notification for scheduling */
                            m_uEbTpMsgFlagIdx[!"name(.)"!] = EB_TRUE;
                            [!IF "as:modconf('Tp')/TpGeneral/TpDataStreaming = 'true'"!]
                            EB_SetStreamingStatus(EB_STREAMING_FORBIDDEN);
                            [!ENDIF!]

                            [!IF "$FunctionalMsgExist = 1"!]
                            /* Lock all functional channel to avoid any buffer problem */
                                [!FOR "MsgNB" = "1" TO "num:i(count(as:modconf('Tp')/Message/*))" STEP "1"!]
                                    [!IF "(as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Obd' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag_Obd') and as:modconf('Tp')/Message/*[position()=$MsgNB]/Adressing_Mode = 'Functional'"!]
                                    [!WS "28"!](void)TP_RxEnable(TP_MSG_IDX_[!"name(as:modconf('Tp')/Message/*[position()=$MsgNB])"!], TP_RX_ENABLE_OFF);
                                    [!ENDIF!]
                                [!ENDFOR!]
                            [!ENDIF!]
                        }
                    }
                }
                else if (1U == m_aubMessageRxCnt[uMsgIdx])
                {
                    m_aubMessageRxCnt[uMsgIdx]++;
                    /* Notification for scheduling */
                    m_uEbTpMsgFlagIdx[!"name(.)"!] = EB_TRUE;
                    [!IF "as:modconf('Tp')/TpGeneral/TpDataStreaming = 'true'"!]
                    EB_SetStreamingStatus(EB_STREAMING_FORBIDDEN);
                    [!ENDIF!]

                    [!IF "$FunctionalMsgExist = 1"!]
                    /* Lock all functional channel to avoid any buffer problem */
                        [!FOR "MsgNB" = "1" TO "num:i(count(as:modconf('Tp')/Message/*))" STEP "1"!]
                            [!IF "(as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Obd' or as:modconf('Tp')/Message/*[position()=$MsgNB]/Type = 'Diag_Obd') and as:modconf('Tp')/Message/*[position()=$MsgNB]/Adressing_Mode = 'Functional'"!]
                            [!WS "20"!](void)TP_RxEnable(TP_MSG_IDX_[!"name(as:modconf('Tp')/Message/*[position()=$MsgNB])"!], TP_RX_ENABLE_OFF);
                            [!ENDIF!]
                        [!ENDFOR!]
                    [!ENDIF!]
                }
                else
                {
                    m_aubMessageRxCnt[uMsgIdx] = 0U;
                }
                break;
                [!ENDIF!]
            [!ENDIF!]
        [!ENDLOOP!]
            default:
                /* Nothing to do */
                break;
        }
    }
    else
    {
        [!IF "as:modconf('Tp')/TpGeneral/TpDataStreaming = 'true'"!]
        EB_SetStreamingStatus(EB_STREAMING_ALLOWED);
        [!ENDIF!]
    }
    [!ENDIF!]
[!ENDIF!]

    APP_TpRxInd (uMsgIdx, ebStatus);
[!IF "node:exists(as:modconf('Prog'))"!]
    PROG_TpRxInd (uMsgIdx, ebStatus);
[!ENDIF!]

    DBG_TP_RXINDFULLDUPLEX_EXIT();
}
/*----------------------------------{End TP_RxIndFullDuplex}-------------------------------------------*/

/*----------------------------------{EB_SwapCheck}-----------------------------------------------------*/
NCS_PRI_FCT tEbQueuedStatus EB_SwapCheck(tTpMsgIdx uMsgIdx)
{
    tEbQueuedStatus eEbQueuedStatus;

    if(uMsgIdx < TP_MSG_MAX)
    {
        if (m_aubMessageRxCnt[uMsgIdx] == 1U)
        {
            /* Set treatment to IN PROGRESS */
            m_ubReqTreatmentState[uMsgIdx] = EB_STATUS_IN_PROGRESS;
            /* Return Status OK */
            eEbQueuedStatus = EB_STATUS_OK;
        }
        else if (m_aubMessageRxCnt[uMsgIdx] == 2U)
        {
            /* If an operation is already in progress */
            if(m_ubReqTreatmentState[uMsgIdx] == EB_STATUS_IN_PROGRESS)
            {
                /* Return Status wait the previous treatment is not over */
                eEbQueuedStatus = EB_STATUS_WAIT;
            }
            else
            {
                 /* Set treatment to IN PROGRESS */
                m_ubReqTreatmentState[uMsgIdx] = EB_STATUS_IN_PROGRESS;
                /* Return Status OK */
                eEbQueuedStatus = EB_STATUS_QUEUED;
            }
        }
        else
        {
            /* Reset counter on error to restart from nominal value */
            m_aubMessageRxCnt[uMsgIdx] = 0U;
            eEbQueuedStatus = EB_STATUS_ERROR;
        }
    }
    else
    {
        eEbQueuedStatus = EB_STATUS_ERROR;
    }
    return eEbQueuedStatus;
}
/*----------------------------------{End EB_SwapCheck}-------------------------------------------------*/
[!ENDCODE!]

