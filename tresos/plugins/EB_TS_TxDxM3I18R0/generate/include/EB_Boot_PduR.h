/*********************************************************************************/
/*                                                                               */
/*                                  BOOT Stack                                   */
/*                                                                               */
/* ----------------------------------------------------------------------------- */
/*                                                                               */
/*                                EB BOOT PDUR                                   */
/*                                                                               */
/*********************************************************************************/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                                        */
/*%%   _____________________________   %%  \file EB_Boot_PduR.h                  */
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
[!/* Activate generation of EB_Boot_PduR.h file*/!]
[!IF "as:modconf('EB')/General/Osek_Autosar_Stack != 'AUTOSAR'"!]
    [!SKIPFILE!]
[!ENDIF!]
[!ENDNOCODE!]
#ifndef EB_BOOT_PDUR_H_
#define EB_BOOT_PDUR_H_

#include <TSAutosar.h>      /* EB specific standard types */
#include <ComStack_Types.h> /* AUTOSAR Communication Stack types */
#include <EB_prj.h>         /* Osekcore includes */

/*==================[macros]================================================*/
/* skip this code from DoxyGen only API documentation is provided */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
[!IF "as:modconf('EB')/General/Osek_Autosar_Stack = 'AUTOSAR'"!]
#define TP_RX_FUNC_BUFFERSIZE           [!"num:i(Communication/TP_Buffer_Size_Functional)"!]U
#define TP_RX_PHYS_BUFFERSIZE           [!"num:i(Communication/TP_Buffer_Size_Physical)"!]U


/* values taken from PduR.xdm */
#define PDUR_PHYRESP_TPSDU 2U
#define PDUR_BL_DIAGREQ_TPSDU [!"num:dectoint(Communication/RxSdu_Physical_Id)"!]U
#define PDUR_FUNCTIONALREQ_TPSDU [!"num:dectoint(Communication/RxSdu_Functional_Id)"!]U
#define NUMBER_OF_RXBUFFERS 2U
#define PDUR_TX_TPSDU [!"num:dectoint(Communication/TxSdu_Id)"!]U
#define PDUR_TX_TPSDU_CONF [!"num:dectoint(Communication/TxSduConf_Id)"!]U
[!ENDIF!]
/* The maximum RX allowed physical request at the same time is 2 and shall not be changed */
#define PDUR_MAX_PHY_RX_ALLOWED   2U
/* The maximum RX allowed functional request at the same time is 1 and shall not be changed */
#define PDUR_MAX_FUNC_RX_ALLOWED  1U
/* The number of transmission is currently limited to 2 One physical one functional */
#define PDUR_MAX_TX_ALLOWED  2U

#define PDUR_ALL_PDU 0xFFU

/* PduIdx in FrIf config of the PDU containing the NetworkStatus */
#define PDUR_APP_NETWORKSTATUS_PDUIDX 0U

#endif /* endif DOXYGEN_SHOULD_SKIP_THIS */

/*==================[external function declarations]========================*/

/**
 ** \brief This service is called by the receiving FrTp module requesting a TP-buffer.
 **
 ** \param[in]  RxPduId             Identification of the received I-PDU.
 ** \param[in]  TpSduLength         Total length of the PDU to be received.
 ** \param[out] BufferSizePtr       Available receive buffer in the receiving module.
 **                                 This parameter will be used to compute the Block Size (BS) in
 **                                 the transport protocol module.
 **
 ** \return Result of buffer request
 ** \retval BUFREQ_OK        Connection has been accepted.
 **                          BufferSizePtr indicates the available receive buffer.
 ** \retval BUFREQ_E_BUSY    Currently no buffer of the requested size is available.
 **                          BufferSizePtr remains unchanged. Connection has been rejected.
 ** \retval BUFREQ_E_OVFL    No Buffer of the required length can be provided.
 ** \retval BUFREQ_E_NOT_OK  Connection has been rejected. BufferSizePtr remains unchanged.
 **/
extern FUNC(BufReq_ReturnType, PDUR_CODE) EB_StartOfReception
(
    PduIdType RxPduId,
    PduLengthType TpSduLength,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) BufferSizePtr
);

/**
 ** \brief This service is called by the receiving FrTp module requesting a TP-buffer.
 **
 ** \param[in]  RxPduId             Identification of the received I-PDU.
 ** \param[in]  PduInfoPtr          Pointer to the buffer (SduDataPtr) and its length (SduLength)
 **                                 containing the data to be copied by PDU Router module in
 **                                 case of gateway or upper layer module in case of reception.
 ** \param[out] BufferSizePtr       Available receive buffer after data has been copied.
 **
 ** \return Result of buffer request
 ** \retval BUFREQ_OK        Buffer request accomplished successfully.
 ** \retval BUFREQ_E_BUSY    Temporarily no buffer available.
 **                          It's up the requestor to retry request for a certain time.
 ** \retval BUFREQ_E_NOT_OK  Buffer request not successful. Buffer cannot be accessed.
 **/
extern FUNC(BufReq_ReturnType, PDUR_CODE) EB_CopyRxData
(
    PduIdType RxPduId,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_CONST) PduInfoPtr,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) BufferSizePtr
);

/**
 ** \brief This service is called by the sending FrTp module requesting a TP-buffer.
 **
 ** \param[in]  TxPduId             Identification of the transmitted I-PDU.
 ** \param[out] PduInfoPtr          Provides destination buffer and the number of bytes to copy.
 **                                 In case of gateway the PDU Router module will copy,
 **                                 otherwise the source upper layer module will copy the data.
 **                                 If not enough transmit data is available, no data is copied.
 **                                 The transport protocol module will retry.
 **                                 A copy size of 0 can be used to indicate state changes in the
 **                                 retry parameter.
 ** \param[in]  RetryInfoPtr        This parameter is used to retransmit data because problems
 **                                 during the last service call.
 **                                 If the I-PDU is transmitted from a local module (e.g. DCM) the
 **                                 PDU router module will just forward the parameter value
 **                                 without check. If the I-PDU is gatewayed from another bus,
 **                                 the PDU Router module will make the following interpretation:
 **                                 If the transmitted TP I-PDU does not support the retry feature
 **                                 a NULL_PTR is provided. It indicates that the copied transmit
 **                                 data can be removed from the buffer after it has been copied.
 **                                 If the retry feature is used by the Tx I-PDU, RetryInfoPtr must
 **                                 point to a valid RetryInfoType element.
 **                                 If TpDataState indicates TP_CONFPENDING, the previously
 **                                 copied data must remain in the TP buffer to be available for
 **                                 error recovery.
 **                                 TP_DATACONF indicates that all data that have been copied
 **                                 so far are confirmed and can be removed from the TP buffer.
 **                                 Data copied by this API call are excluded and will be
 **                                 confirmed later.
 **                                 TP_DATARETRY indicates that this API call shall copy
 **                                 already copied data in order to recover from an error. In this
 **                                 case AvailableDataPtr specifies the offset of the first byte to be
 **                                 copied by the API call.
 ** \param[out] AvailableDataPtr    Indicates the remaining number of bytes that are available in
 **                                 the PduR Tx buffer. AvailableDataPtr can be used by
 **                                 TP modules that support dynamic payload lengths (e.g. Iso
 **                                 FrTp) to determine the size of the following CFs.
 ** \param[in]  RTabLoTpConfigIdx   Index referring to the configuration of the LoTp-Module.
 **
 ** \return Result of buffer request
 ** \retval BUFREQ_OK        Data has been copied to the transmit buffer completely as requested.
 ** \retval BUFREQ_E_BUSY    Request could not be fulfilled, because the required amount of
 **                          Tx data is not available. TP layer might retry later on.
 **                          No data has been copied.
 ** \retval BUFREQ_E_NOT_OK  Data has not been copied. Request failed.
 **/
extern FUNC(BufReq_ReturnType, PDUR_CODE) EB_CopyTxData
(
    PduIdType TxPduId,
    P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr,
    P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) RetryInfoPtr,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) AvailableDataPtr
);

/**
 ** \brief This service is called by the FrTp module after an I-PDU has been received
 ** successfully or when an error occurred. It is also used to confirm cancellation of an I-PDU.
 **
 ** \param[in]  RxPduId   Identification of the received I-PDU.
 ** \param[in]  Result    Result of the reception.
 **/
extern FUNC(void, PDUR_CODE) EB_TpRxIndication
(
    PduIdType    RxPduId,
    NotifResultType  Result
);

/**
 ** \brief This service is called by the FrTp module after the I-PDU has been
 ** transmitted on its network, the result will reveal if the transmission was successful or not.
 **
 ** \param[in]  TxPduId  Identification of the transmitted I-PDU.
 ** \param[in]  Result   Result of the transmission of the I-PDU.
 **/
extern FUNC(void, PDUR_CODE) EB_TpTxConfirmation
(
    PduIdType    TxPduId,
    NotifResultType  Result
);

/**
 ** \brief This service is called by EB and APP modules to release buffers.
 **
 ** \param[in]  uMsgIdx         Message index.
 **/
extern void TP_UDS_ReleaseBuffers(tTpMsgIdx uMsgIdx);

/**
 ** \brief This function is used to get the Network status signal from the coordinator.
 **
 ** \param[in]  RxPduId         Identification of the received I-PDU.
 ** \param[in]  PduInfoPtr      Pointer to the buffer (SduDataPtr) and its length (SduLength).
 **/
extern void PDUR_APP_Wrapper_RxIndication
(
  PduIdType RxPduId,
  P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr
);

/* skip this code from DoxyGen (already defined in TP module API)  */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
/**
 ** \brief This service is used to lock/unlock a receiving channel.
 **
 ** \param[in]  uMsgIdx         Message index.
 ** \param[in]  uRxEnable       Required channel state.
 **
 ** \return Result of locking/unlocking request
 ** \retval TP_ERR_OK           Locking/unlocking successful.
 ** \retval TP_ERR_IDX          The message index input parameter is out of range.
 **/
extern tTpStatus TP_RxEnable (tTpMsgIdx uMsgIdx, tTpRxEnable uRxEnable);

/**
 ** \brief This service is used to prepare and send the diagnostic answer message via FrTp_Transmit.
 **
 ** \param[in]  uMsgIdx         Message index (unused).
 ** \param[in]  uwLen           Answer message data length.
 ** \param[in]  paubData        Answer message data buffer.
 **
 ** \return Result of the transmission triggering
 ** \retval TP_ERR_OK           Transmission triggering successful.
 ** \retval TP_ERR_LEN          Transmission triggering NOT OK.
 **/
extern tTpStatus TP_SetMsgData (tTpMsgIdx uMsgIdx, u16 uwLen, u8 *paubData);


/**
 ** \brief This service is a wrapper to TP_SetMsgData it is mandatory to be compliant with the OsekCore Can stack
 **
 ** \param[in]  uMsgIdx         Message index (unused).
 ** \param[in]  uwLen           Answer message data length.
 ** \param[in]  paubData        Answer message data buffer.
 **
 ** \return Result of the transmission triggering
 ** \retval TP_ERR_OK           Transmission triggering successful.
 ** \retval TP_ERR_LEN          Transmission triggering NOT OK.
 **/
extern tTpStatus TP_SetMsgDataCopy (tTpMsgIdx uMsgIdx, u16 uwLen, u8 *paubData);

/**
 ** \brief This service is used to get pointer/length of received message data.
 **
 ** \param[in]  uMsgIdx         Message index.
 ** \param[out] puwLen          Received message data length.
 ** \param[out] paubData        Received message data buffer.
 **
 ** \return Result of buffer request
 ** \retval TP_ERR_OK           Operation successful.
 ** \retval TP_ERR_IDX          The message index input parameter is out of range.
 **/
extern tTpStatus TP_GetMsgData (tTpMsgIdx uMsgIdx, u16 *puwLen, u8 **paubData);

/** \brief Allow to swap both buffer for full duplex management
 **
 ** This function shall be called after a full reception has been correctly
 ** done to allow the next one to be received without overlap the previous one
 **
 ** \param[in] uMsgIdx Message index of the TP channel where the buffer shall be swap
 **
 ** \return tTpStatus
 ** \retval TP_ERR_OK the swap have been successfully done
 ** \retval TP_ERR_IDX the index pass in out of range
 ** \retval TP_ERR_COM_FRAME_MODE the full duplex is not activated for this channel
 **/
extern tTpStatus TP_SwapBuffer(tTpMsgIdx uMsgIdx);

/** \brief Message complete transmission
 **
 ** This callback is called when a message transmission is completed, successfully or not.
 **
 ** \param[in] uMsgIdx TP message index
 ** \param[in] ebStatus TP message status (TP_MSG_STATUS_*)
 **
 **/
extern void TP_TxConf (tTpMsgIdx uMsgIdx, u8 ebStatus);
/** \brief Message complete reception
 **
 ** This callback is called when a message reception is completed, successfully or not.
 **
 ** \param[in] uMsgIdx TP message index
 ** \param[in] ebStatus TP message status (TP_MSG_STATUS_*)
 **
 **/
extern void TP_RxInd (tTpMsgIdx uMsgIdx, u8 ebStatus);
/** \brief Message complete transmission for a channel configured in Full Duplex
 **
 ** This callback is called when a message transmission is completed, successfully or not and the message is configured in Full Duplex mode.
 **
 ** \param[in] uMsgIdx TP message index
 ** \param[in] ebStatus TP message status (TP_MSG_STATUS_*)
 **
 **/
extern void TP_TxConfFullDuplex(tTpMsgIdx uMsgIdx, u8 ebStatus);
/** \brief Message complete reception  for a channel configured in Full Duplex
 **
 ** This callback is called when a message reception is completed, successfully or not and the message is configured in Full Duplex mode.
 **
 ** \param[in] uMsgIdx TP message index
 ** \param[in] ebStatus TP message status (TP_MSG_STATUS_*)
 **
 **/
extern void TP_RxIndFullDuplex(tTpMsgIdx uMsgIdx, u8 ebStatus);
#endif

/** \brief Provide Current RxPduId
 **
 ** This callback is called before jumpoing to SBL to get the current RxPduId. SBL will use it to determine wich TxPduId shall be used for response.
 **
 ** \param[out] ubCurrentRxPduId RxPduId
 **
 **/
extern void EB_GetCurrentRxPdu(u8 * ubCurrentRxPduId);

/** \brief Set Current RxPduId
 **
 ** This callback is called in SBL to set the RxPduId used in PBL to jump to SBL.
 **
 ** \param[in] ubCurrentRxPduId RxPduId
 **
 **/
extern void EB_SetCurrentRxPdu(u8 ubCurrentRxPduId);


/** \brief manage the TxConf for multi Fr TP channel
 **
 ** This callback is called on TP TxConf it allow to manage the txconf management in Fr wrapper.
 ** This API is only available on FlexRay network
 **
 **/
extern void EB_TxConf(tTpMsgIdx uMsgIdx);

/** \brief Function to get the allocated UDS Rx Buffer buffer size from PduId
 **
 ** \param[in] PduId
 **
 **/
extern PduLengthType TP_UDS_GetBufferSize(PduIdType PduId);

/* skip this code from DoxyGen (stubbed functions)  */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
extern void TP_Manage(void);
extern void TP_Init(void);
extern void TP_ComNAsInd (tTpMsgIdx uMsgIdx);
extern void TP_ComTxConf (tTpMsgIdx uMsgIdx);
extern void TP_ComTxConfFC (tTpMsgIdx uMsgIdx);
extern tTpStatus TP_SendMsg (tTpMsgIdx uMsgIdx);
extern tTpStatus TP_ReceiveFrame (tTpMsgIdx uMsgIdx);
[!IF "as:modconf('Tp')/TpGeneral/TpDataStreaming = 'true'"!]
extern void TP_StreamingFrameReceived(u16 ulReceivedDataLength, u8* aubData);
[!ENDIF!]
extern void PDUR_APP_Wrapper_TxConfirmation(PduIdType TxPduId);
extern Std_ReturnType PDUR_APP_Wrapper_TriggerTransmit
(
  PduIdType TxPduId,
  P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr
);
#endif

#endif /* EB_BOOT_PDUR_H_ */

/*==================[end of file]===========================================*/
