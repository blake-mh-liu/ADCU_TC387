/*********************************************************************************/
/*                                                                               */
/*                                  CAN Stack                                    */
/*                                                                               */
/* ------------------------------------------------------------------------------*/
/*                                                                               */
/*                                 EB configuration                             */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file EB_Cbk.h                       */
/*%%  |                             |  %%  \brief EB layer include plugin file  */
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
[!CODE!]

#ifndef EB_CBK_H
#define EB_CBK_H

[!IF "node:exists(as:modconf('Com'))"!]
/** \brief Status change of monitoring frames
 **
 ** This callback is called by COM when the status of a monitored frame has changed.
 ** It is executed with the periodical task.
 **
 ** \param[in] uNodeIdx     Index of the supervised node in transmission or reception (0 .. COM_MON_NODE_MAX – 1)
 ** \param[in] eFrameStatus status of the transmitted frame ( COM_MON_NODE_STATUS_OK or COM_MON_NODE_STATUS_NOK)
 **
 **/
extern void APP_COM_MonNodeStatusInd(tComMonNodeIdx uNodeIdx, tComMonStatus eFrameStatus);

/** \brief Ending of a N_As timeout
 **
 ** This callback is called by the periodical ::COM_Manage task when a N_As timeout is elapsed.
 ** It is executed into regular scheduler tick.
 **
 ** \param[in] uFrameIdx    Index of the transmitted frame ( COM_TX_FRAME_BASE.. COM_TX_FRAME_MAX – 1)
 **
 **/
extern void APP_ComNAsInd (tComFrameIdx uFrameIdx);

/** \brief Transmission acknowledgement
 **
 ** This callback is called on successful frame acknowledgement.
 ** It is executed into CAN interrupt subroutine.
 **
 ** \param[in] uFrameIdx    Index of the transmitted frame ( COM_TX_FRAME_BASE.. COM_TX_FRAME_MAX – 1)
 **
 **/
extern void APP_ComTxConf (tComFrameIdx uFrameIdx);

/** \brief COM layer status change
 **
 ** This callback is called in order to signal the COM layer status change.
 ** It is called after having executed the ::COM_ModeModify function, when the requested mode was accepted.
 ** It is executed with the context of ::COM_ModeModify function call.
 **
 ** The eCurMode parameter holds the new COM layer status.
 **
 ** \param[in] eCurMode    COM mode (COM_MODE_OFF, COM_MODE_BUS_ON, COM_MODE_BUS_OFF)
 **
 **/
extern void APP_ComModeModifyExtension (tComMode eCurMode);

/** \brief Indication just before a frame transmission
 **
 ** This callback is called by COM just before requesting the frame transmission to the CAN controller.
 ** At this step, this is still possible to update the data buffer into the IL.
 ** It is executed with the periodical task.
 **
 ** \param[in] uFrameIdx    Index of the transmitted frame ( COM_TX_FRAME_BASE.. COM_TX_FRAME_MAX – 1)
 **
 **/
extern void APP_ComTxFrameInd (tComFrameIdx uFrameIdx);

/** \brief Communication recovery or transmission without error, after filtering
 **
 ** This callback is called by COM when recovering communication with a supervised node uNodeIdx.
 ** It is executed into regular scheduler tick.
 **
 ** In the case of the supervision in transmission, the called is done after an amount of ubFilterOk successive correct transmissions.
 ** In the case of the supervision in reception, the called is done after an amount of ubFilterOk successive received frames.
 **
 ** One frame can be supervised several times with different delay for communication back detection, for that multiple nodes must be defined for this frame in m_auComMonFrameIdx.
 **
 ** The filtering is configured in the m_aubComMonFilterOk [COM_MON_NODE_MAX] and m_aubComMonFilterNok[COM_MON_NODE_MAX] structures in the COM_Cfg.c file.
 **
 ** \param[in] uNodeIdx    Index of the supervised node in transmission or reception (0 .. COM_MON_NODE_MAX – 1)
 **
 **/
extern void APP_ComBackInd (tComMonNodeIdx uNodeIdx);

/** \brief Communication loss or N_As timeout, after filtering
 **
 ** This callback is called by COM when having lost communication with a supervised node uNodeIdx.
 ** It is executed into regular scheduler tick.
 **
 ** In the case of the supervision in transmission, the called is done after an amount of ubFilterNok  successive N_As timeout.
 ** In the case of the supervision in reception, the called is done after an amount of ubFilterNok non received frames.
 **
 ** One frame can be supervised several times with different delay for communication loss detection, for that multiple nodes must be defined for this frame in m_auComMonFrameIdx.
 ** But in this case, the default value for all the related frame signals will be applied on first node indication.
 **
 ** The filtering is configured in the m_aubComMonFilterOk [COM_MON_NODE_MAX] and m_aubComMonFilterNok[COM_MON_NODE_MAX] structures in the COM_Cfg.c file.
 **
 ** \param[in] uNodeIdx    Index of the supervised node in transmission or reception (0 .. COM_MON_NODE_MAX – 1)
 **
 **/
extern void APP_ComLossInd (tComMonNodeIdx uNodeIdx);

/** \brief TxTimeout Indication
 **
 ** This callback is called by COM when a transmission timeout (N_As) occurs.
 ** Depending on this callback returned value, the frame transmission will be aborted or not.
 ** It is executed into regular scheduler tick.
 **
 ** \param[in] uFrameIdx    Index of the transmitted frame ( COM_TX_FRAME_BASE.. COM_TX_FRAME_MAX – 1)
 **
 ** \return function status
 ** \retval COM_ERR_XXX            The frame will not be aborted.
 ** \retval COM_ERR_ABORT          The frame will be aborted.
 **
 **/
extern tComStatus APP_ComTxTimeoutInd (tComFrameIdx uFrameIdx);
[!ENDIF!]


[!IF "node:exists(as:modconf('Can')) and as:modconf('EB')/General/Osek_Autosar_Stack = 'OSEK'"!]
#if (CAN_WAKE_UP_DETECTION  == CAN_WAKE_UP_ACTIVATE)
/** \brief CAN Wake Up notification
 **
 ** This callback is called by CAN when a WAKE-UP is detected by the protocol handler (frame reception).
 **
 **/
extern void APP_CanWakeUpInd (void);
#endif
/** \brief CAN error notification
 **
 ** This callback is called by CAN when an error is detected in CAN controller
 ** during CAN_Activate or CAN_Desactivate.
 **\param[in] CAN_ERRORS uErrorID which indicates the corresponding error.
 **
 **/
extern void APP_CanCtrlModeErrorInd (tCanErrors uErrorID);
[!ENDIF!]

[!IF "node:exists(as:modconf('Tp'))"!]
/** \brief Transmission buffer empty indication
 **
 ** When all the bytes of the TP transmission buffer have been used and if all the databytes of the segmented
 ** message have not been transmitted, ::TP_DataBufferEmptyInd is called. This allows the customer to reload the
 ** TP transmission buffer via the API ::TP_SetMsgData.
 **
 ** In this case, only the address of the buffer is changed, so the customer must work with at least 2 buffers.
 **
 ** For information, ::TP_DataBufferEmptyInd shall be called only if the configuration TP_MSG_RELOAD_TRUE is set in the configuration parameter of the TP message.
 **
 ** \param[in] uMsgIdx TP message index
 **
 **/
extern void APP_TpDataBufferEmptyInd(tTpMsgIdx uMsgIdx);

/** \brief Message complete transmission
 **
 ** This callback is called when a message transmission is completed, successfully or not.
 **
 ** \param[in] uMsgIdx TP message index
 ** \param[in] ebStatus TP message status (TP_MSG_STATUS_*)
 **
 **/
extern void APP_TpTxConf(tTpMsgIdx uMsgIdx, u8 ebStatus);

/** \brief Message complete reception
 **
 ** This callback is called when a message reception is completed, successfully or not.
 **
 ** \param[in] uMsgIdx TP message index
 ** \param[in] ebStatus TP message status (TP_MSG_STATUS_*)
 **
 **/
extern void APP_TpRxInd(tTpMsgIdx uMsgIdx, u8 ebStatus);

/** \brief Automatic reception unlock
 **
 ** When the reception lock is requested for a channel, a counter is initialized to manage a timer (1000ms).
 ** The cyclic call ::TP_Manage decreases the counter. When the counter reaches 0, the reception is automatically unlocked. The aim is to prevent the system from an infinite lock.
 **
 ** \param[in] uMsgIdx TP message index
 ** \param[in] uRxEnable flag (TP_RX_ENABLE_ON/TP_RX_ENABLE_OFF)
 **
 **/
extern void APP_TpRxEnableInd (tTpMsgIdx uMsgIdx, tTpRxEnable uRxEnable);
[!ENDIF!]
[!IF "node:exists(as:modconf('Uds'))"!]
/** \brief Notification for diagnostic session transition
 **
 ** It provides old and new sessions, with the reason for the transition.
 **
 ** \param[in] eUdsNewSessType new session
 ** \param[in] eUdsOldSessType old session
 ** \param[in] eUdsChangingCause explicit request (UDS_SESSION_CHANGE_REQUESTED) or session timeout (UDS_SESSION_TIMEOUT)
 **
 **/
extern void APP_UdsSessionStatusInd (tUdsSessionType eUdsNewSessType,tUdsSessionType eUdsOldSessType,tUdsChangeReason eUdsChangingCause);
[!ENDIF!]

[!IF "node:exists(as:modconf('Tp')) and node:exists(as:modconf('Uds'))"!]
/** \brief UDS response notification just before transmission (buffer update if necessary)
 **
 ** This callback is called when UDS reponse is available but not yet transmitted.
 ** The buffer can be updated if necessary.
 **
 ** \param[in,out] uwLen pointer on data length
 ** \param[in,out] paubUdsData pointer on data
 ** \param[in] uMsgIdx TP message index
 ** \param[in] eStatusRxReq status of the UDS treatment (value UDS_TRUE, UDS_FALSE, UDS_NRC_78)
 **
 **/
extern void APP_GetUdsDataBufferInd(u16 *uwLen, u8 *paubUdsData, tTpMsgIdx uMsgIdx, tUdsStatus eStatusRxReq);
[!ENDIF!]

#endif      /* EB_CBK_H */
[!ENDCODE!]
