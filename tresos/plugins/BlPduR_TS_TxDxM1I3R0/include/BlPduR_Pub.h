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
/*%%   _____________________________   %%  \file BlPduR_Pub.h                    */
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
#ifndef BLPDUR_PUB_H
#define BLPDUR_PUB_H

#include "BlPduR_Cfg.h"
/* skip this code from DoxyGen only API documentation is provided */
#ifndef DOXYGEN_SHOULD_SKIP_THIS

typedef u8 tBlPduRBoolean;
#define BLPDUR_TRUE         1U
#define BLPDUR_FALSE        0U

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

/*-------------------------------------------------------------------------------*/
/* - Public Variables                                                            */

/*-------------------------------------------------------------------------------*/
/* - Public Function Prototypes                                                  */
/** \brief Initialize all layers
 **
 ** This function call all the subInit function BlPduR_InitX
 ** It shall be called only once at ECU start-up.
 **
 **/
extern void BlPduR_Init (void);


/** \brief Initialize  the communication stack
 **
 ** This function initializes the communication stack
 ** (CAN or FR or Ethernet) by calling there *_Init function.
 **
 **/
extern void BlPduR_Init1(void);

/** \brief Initialize all specific bootloader layers
 **
 ** This function initializes the Bootloader specific layer
 ** (PROG, SA and ReProgMemM or Flash) by calling there *_Init function.
 **
 **/
extern void BlPduR_Init2(void);

/** \brief Periodical task of all layers
 **
 ** Modules periodic functions are called in this function (ex: COM_Manage)
 ** BLPDUR_MANAGE_PERIOD is configured in Tresos BlPduR plugin.
 ** The reception of segmented frames are handled in this function.
 **
 **/
extern void BlPduR_Manage (void);

/** \brief Check if FlexRay network is synchronized
 **
 ** If FlexRay is used, this Api check if the Flexray
 ** network is synchronized and return the status and
 ** the FlexRay cycle.
 **
 ** \return synchronization status
 ** \retval BLPDUR_TRUE            Network is synchronized
 ** \retval BLPDUR_FALSE           Network is not synchronized
 **/
extern u8 BlPduR_IsNetworkSynchronized(u8 * frCycle);

/** \brief Activate the FlexRay mode AllSlots
 **
 ** If FlexRay is used, this Api call FlexRay state manager
 ** to request him the AllSlots mode
 **
 **/
extern void BlPduR_AllSlots(void);



#if(BLPDUR_SOURCE_ADDRESS_CHECK_ENABLE == STD_ON)
/** \brief Store the tester address in global variable
 **
 ** Provide to BlPduR the tester address that shall be accepted
 ** in reception.
 **
 **/
extern void BlPduR_SetTesterAddress(u16 ubTesterAddress);
#endif /*(BLPDUR_SOURCE_ADDRESS_CHECK_ENABLE == STD_ON)*/

/** \brief RQD_BLPDUR_PUB_029 Retrieve the active connection information
 **
 **
 **/
extern void BlPduR_RetrieveConnectionInfo(void);

/** \brief Store the active connection information
 **
 **
 **/
extern void BlPduR_StoreConnectionInfo(void);

/** \brief Send A TP frame using the current Tester Address
 **
 ** Send A TP frame using the current Tester Address
 **
 ** \param[in]  ulLen Message length
 ** \param[in]  paubUdsData message data pointer
 **
 **/
extern void BlPduR_Send_TPFrame(PduLengthType ulLen, const u8 *paubData);

/** \brief Simulate the reception of a frame
 **
 ** Simulate the reception of a frame
 **
 ** \param[in]  ulLen Message length
 ** \param[in]  paubUdsData message data pointer
 ** \param[in]  ubWithResp indicate if a response will be performed (TRUE/FALSE)
 **
 **/
extern void BlPduR_SimulateRxRequest(PduLengthType ulLen, u8 * paubUdsData, PduLengthType ulUdsDataSize, u8 ubWithResp);

/** \brief This service is called by the PROG module to save tester address to be used later in tester filtering **/
extern FUNC(void, PDUR_CODE) BlPduR_SaveTesterAddress(void);


/** \brief This service is called by the receiving Tp module, through PduR, requesting a TP-buffer.
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
extern FUNC(BufReq_ReturnType, PDUR_CODE) BlPduR_StartOfReception
(
    PduIdType RxPduId,
    PduLengthType TpSduLength,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) BufferSizePtr
);


/** \brief This service is called by the receiving Tp module, through PduR, requesting a TP-buffer.
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
extern FUNC(BufReq_ReturnType, PDUR_CODE) BlPduR_CopyRxData
(
    PduIdType RxPduId,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_CONST) PduInfoPtr,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) BufferSizePtr
);

/** \brief This service is called by the sending Tp module, through PduR, requesting a TP-buffer.
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
extern FUNC(BufReq_ReturnType, PDUR_CODE) BlPduR_CopyTxData
(
    PduIdType TxPduId,
    P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr,
    P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) RetryInfoPtr,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) AvailableDataPtr
);

/** \brief This service is called by the Tp module, through PduR, after an I-PDU has been received
 ** successfully or when an error occurred. It is also used to confirm cancellation of an I-PDU.
 **
 ** \param[in]  RxPduId   Identification of the received I-PDU.
 ** \param[in]  Result    Result of the reception.
 **/
extern FUNC(void, PDUR_CODE) BlPduR_TpRxIndication
(
    PduIdType    RxPduId,
    NotifResultType  Result
);

/** \brief This service is called by the Tp module, through PduR, after the I-PDU has been
 ** transmitted on its network, the result will reveal if the transmission was successful or not.
 **
 ** \param[in]  TxPduId  Identification of the transmitted I-PDU.
 ** \param[in]  Result   Result of the transmission of the I-PDU.
 **/
extern FUNC(void, PDUR_CODE) BlPduR_TpTxConfirmation
(
    PduIdType    TxPduId,
    NotifResultType  Result
);

/** \brief This service is used to trigger transmission .
 **
 ** \param[in]  PduId Identification of the PDU
 ** \param[in]  ulLen Message length
 ** \param[in]  paubData Address of the buffer to treat
 **/
extern tBlPduRStatus BlPduR_SendMsgData (PduIdType PduId, PduLengthType ulLen, u8 *paubData);

#if (BLPDUR_MULTIPLE_BUFFERS_ENABLE ==  STD_ON)
/** \brief This service is called by the Prog module, to unlock one or all buffer used.
 **
 ** \param[in]  ubBufferType Buffer to be unlock (one or all)
 **/
extern void BlPduR_UnlockBuffer(u8 ubBufferType);
/** \brief This service is called by the Prog module, to lock the buffer receive for treatment
 **
 ** \param[out] pubIsLastBuffer Information if there is still some buffer available to lock
 **/
extern void BlPduR_LockBuffer(u8* pubIsLastBuffer);
/** \brief This service is called by the Prog module, to get the next buffer information to treat.
 **
 ** \param[out] pulLen Length of the data store in the provided buffer
 ** \param[out] paubData Address of the buffer to treat (Null pointer if no more buffer)
 **/
extern void BlPduR_GetNextBuffer(PduLengthType *pulLen, u8 ** paubData);
#endif

#if (BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON)
/** \brief This service is Called by Can module to filter receive frames
 **
 ** This service is used to know if the given CanId shall be accepted or rejected depending on the active group ID
 **
 ** \param[in] Hrh Hardward object number
 ** \param[in] CanId Can ID of the received frame
 ** \param[in] CanDlc Length of the received frame
 ** \param[in] CanSduPtr Pointer to the data of the received frame
 **/
extern FUNC(boolean, COM_APPL_CODE) BlPduR_GroupIdFrameFilter(Can_HwHandleType Hrh,Can_IdType CanId,uint8 CanDlc,const uint8 *CanSduPtr);
#endif

#if (((BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON) && (BLPDUR_MULTIPLE_ID_TYPE == BLPDUR_MULTIPLE_ID_CAN_NOTIFICATION)) || (BLPDUR_NM_MESSAGE_ENABLE == STD_ON))
/** \brief This service is Called by CanIf through PduR to notify a Pdu reception
 **
 ** \param[in] RxPduId Pdu Number received
 ** \param[in] PduInfoPtr Pointer to the Pdu Information
 **/
extern FUNC(void, PDUR_CODE) BlPduR_RxIndication
(
   PduIdType RxPduId,
   P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr
);
#endif /* #if (((BLPDUR_MULTIPLE_ID_ENABLE ==  STD_ON) && (BLPDUR_MULTIPLE_ID_TYPE == BLPDUR_MULTIPLE_ID_CAN_NOTIFICATION)) || (BLPDUR_NM_MESSAGE_ENABLE == STD_ON)) */

#if (BLPDUR_UPDATE_TP_PARAM_ENABLE == STD_ON)
/** \brief This API changes the value of a TP paremeter (STmin or BS)
 **
 ** \param[in] ubParameterId parameter ID to change (BLPDUR_TP_STMIN or BLPDUR_TP_BS)
 ** \param[in] uwParameterValue new value to set
 **
 ** \return BlPduRStatus variable change status
 ** \retval BLPDUR_E_OK            Parameter is changed
 ** \retval BLPDUR_E_NOT_OK        Parameter isn't changed
 **/
extern tBlPduRStatus BlPduR_TpChangeParameter (tTpParameterId ubParameterId, u16 uwParameterValue);

/** \brief This API gets the value of a TP paremeter (STmin or BS)
 **
 ** \param[in] ubParameterId parameter ID to get (BLPDUR_TP_STMIN or BLPDUR_TP_BS)
 **
 ** \return u16 value of the requested TP parameter
 **/
extern u16 BlPduR_GetTpParameter (tTpParameterId ubParameterId);
#endif /*(BLPDUR_UPDATE_TP_PARAM_ENABLE == STD_ON)*/

#if (BLPDUR_NETWORK_ETH_SUPPORTED == STD_ON)
/** \brief Calls SoAd API that indicates an incoming TCP connection on a server socket
 **
 ** This service is used to know if the given CanId shall be accepted or rejected depending on the active group ID
 **
 ** \return connection status
 ** \retval BLPDUR_TRUE     SoAd accepts the established connection
 ** \retval BLPDUR_FALSE    SoAd refuses the established connection, TcpIp stack shall close the connection.
 **/
extern tBlPduRBoolean BlPduR_IsTcpConnectionReestablished(void);
#endif /*(BLPDUR_NETWORK_ETH_SUPPORTED == STD_ON)*/
#if (BLPDUR_NETWORK_LIN_SUPPORTED == STD_ON)
/** \brief This API gives transmission indication depending on the LTP module message status
 **
 ** \param[in] ebStatus LTP message status
 **
 **/
extern void LTP_TxConf (u8 ebStatus);

/** \brief This API
 **
 ** \param[in] ebStatus LTP message status
 **
 **/
extern void LTP_RxInd (u8 ebStatus);

/** \brief This API
 **/
extern void LIN_WakeUpInd(void);

/** \brief This API
 **/
extern void LIN_ComLossInd(void);

/** \brief This API
 **
 ** \param[in] uFrameIdx transmitted or received frame
  ** \param[in] eStatus LIN message status
 **
 **/
extern void LIN_StatusInd(tLinFrameIdx uFrameIdx, tLinFrameStatus eStatus);

#endif

extern uint32 BlPduR_GetBufferSize(void); /* RQD_BLPDUR_PUB_039  */
extern boolean BlPduR_GetBiggerBuffer(PduLengthType *pulLen, u8 ** paubData); /* RQD_BLPDUR_PUB_039  */

extern u8 BlPduR_TxBusy(void);
extern void SchM_Enter_BLPDUR_SCHM_BLPDUR_EXCLUSIVE_AREA_0(void);
extern void SchM_Exit_BLPDUR_SCHM_BLPDUR_EXCLUSIVE_AREA_0(void);

#endif      /* BLPDUR_PUB_H */
