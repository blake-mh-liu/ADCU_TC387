/**
 * \file
 *
 * \brief AUTOSAR Dcm
 *
 * This file contains the implementation of the AUTOSAR
 * module Dcm.
 *
 * \version 5.0.24
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef DCM_CBK_H
#define DCM_CBK_H

/*==================[inclusions]=================================================================*/

#include <ComStack_Types.h>                                       /* AUTOSAR Com Stack types */

#include <Dcm_Version.h>                                          /* Module version declarations */

#include <Dcm_Types.h>                                            /* DCM type definition */

#include <Dcm_Dsl_ComMChannelStateManager_External_Interface.h>   /* Dcm Dsl CComMChannelStateManager
                                                                     public header file */
/*==================[macros]=====================================================================*/

/*==================[type definitions]===========================================================*/

/** \brief Helper type definition to be used to prevent nested compiler abstraction macros which
 **        may lead to problems for some tool chains. */
typedef P2VAR(PduInfoType, TYPEDEF, DCM_APPL_DATA) Dcm_PduInfoPtrType;

/*==================[external function declarations]=============================================*/

#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/* !LINKSTO SWS_Dcm_01066,1 */

#if (DCM_PDUR_INTERFACE_VERSION == DCM_PDUR_INTERFACE_AUTOSAR_403)
/** \brief Called once to initialize the reception of a diagnostic request.
 **
 ** \param[in] DcmRxPduId Identifies the DCM data to be received. This information is used within
 ** the DCM to distinguish two or more receptions at the same time.
 **
 ** \param[in] TpSduLength This length identifies the overall number of bytes to be received.
 **
 ** \param[out] RxBufferSizePtr pointer to PduLengthType containing length of the available buffer.
 **
 ** \return Buffer request status
 ** \retval BUFREQ_OK Buffer request accomplished successful.
 ** \retval BUFREQ_E_NOT_OK Buffer request not successful. Buffer cannot be accessed by TP.
 ** \retval BUFREQ_E_OVFL DCM is not capable to receive the number of TpSduLength Bytes.
 **
 ** \ServiceID{::DCM_SVCID_STARTOFRECEPTION}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
/* !LINKSTO Dcm.LowerLayerInterfaces.DcmPdurInterfaceVersionAutosar403.Dcm_StartOfReception,1 */
extern FUNC(BufReq_ReturnType, DCM_CODE) Dcm_StartOfReception(
  PduIdType DcmRxPduId,
  PduLengthType TpSduLength,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr);

/** \brief Called once upon reception of each segment. Within this call, the received data
 **  is copied from the receive TP buffer to the DCM receive buffer.
 **
 ** \param[in] DcmRxPduId Identifies the DCM data to be received. This information is used within
 ** the DCM to distinguish two or more receptions at the same time.
 **
 ** \param[in] PduInfoPtr Pointer to a PduInfoType which indicates the number of bytes to be
 ** copied (SduLength) and the location of the source data (SduDataPtr).
 **
 ** \param[out] RxBufferSizePtr pointer to Remaining free place in receive buffer after
 ** completion of this call.
 **
 ** \return Request data copy status
 ** \retval BUFREQ_OK Data has been copied to the receive buffer completely as requested.
 ** \retval BUFREQ_E_NOT_OK Data has not been copied. Request failed.
 **
 ** \ServiceID{::DCM_SVCID_COPYRXDATA}
 ** \Reentrancy{Reentrant for different PduIds.Non reentrant for the same PduId.}
 ** \Synchronicity{Synchronous}
 */
/* !LINKSTO Dcm.LowerLayerInterfaces.DcmPdurInterfaceVersionAutosar403.Dcm_CopyRxData,1 */
extern FUNC(BufReq_ReturnType, DCM_CODE) Dcm_CopyRxData(
  PduIdType DcmRxPduId,
  P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr);

/** \brief Indicate that reception of data is finished
 **
 ** This function is called by the lower layer (in general the PDU Router):
 ** - with Result = ::NTFSRSLT_OK after the complete DCM I-PDU has successfully been received, i.e.
 **   at the very end of the segmented TP receive cycle or after receiving an unsegmented N-PDU.
 ** - with Result = ::NTFSRSLT_NOT_OK it is indicated that an error (e.g. timeout) has occurred
 **   during the reception of the DCM I-PDU. This passes the receive buffer back to DCM and allows
 **   error handling.  It is undefined which part of the buffer contains valid data in this case,
 **   so the DCM shall not evaluate that buffer.  By calling this service only the DCM is allowed
 **   to access the buffer.
 **
 ** \param[in] DcmRxPduId ID of DCM I-PDU that has been received.
 **
 ** \param[in] Result Result of the N-PDU reception
 **
 ** \ServiceID{::DCM_SVCID_TPRXINDICATION}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
/* !LINKSTO Dcm.LowerLayerInterfaces.DcmPdurInterfaceVersionAutosar403.Dcm_TpRxIndication,1 */
extern FUNC(void, DCM_CODE) Dcm_TpRxIndication(
  PduIdType DcmRxPduId,
  NotifResultType Result);

/** \brief Request transmission buffer
 **
 ** At invocation of Dcm_CopyTxData the DCM module copies the requested transmit data with ID PduId
 ** from its internal transmit buffer to the location specified by the PduInfoPtr. The function
 ** Dcm_CopyTxData also calculates and sets the TxDataCntPtr to the amount of remaining bytes for
 ** the transmission of this data.
 ** If RetryInfoPtr is NULL_PTR or if TpDataState is not equal TP_DATARETRY, the Dcm shall always
 ** copy the next fragment of data to the SduDataPtr.
 ** If TpDataState equals TP_DATARETRY, the Dcm shall copy previously copied data again, beginning
 ** from the offset position given in RetryInfoPtr->TxTpDataCnt from the current position.
 **
 ** \param[in] DcmTxPduId Identifies the DCM data to be sent. This information is used to derive
 ** the PCI information within the transport protocol. The value has to be same as in the according
 ** service call PduR_DcmTransmit().
 **
 ** \param[in] PduInfoPtr Pointer to a PduInfoType, which indicates the number of bytes to be copied
 ** (SduLength) and the location where the data have to be copied to (SduDataPtr).
 ** An SduLength of 0 is possible in order to poll the available transmit data count. In this case
 ** no data are to be copied and SduDataPtr might be invalid.
 **
 ** \param[in] RetryInfoPtr If the transmitted TP I-PDU does not support the retry feature a
 ** NULL_PTR can be provided. This indicates that the copied transmit data can be removed from the
 ** buffer after it has been copied.
 **
 ** \param[out] TxDataCntPtr Remaining Tx data after completion of this call
 ** \return Response data copy status
 ** \retval BUFREQ_OK Data has been copied to the transmit buffer completely as requested.
 ** \retval BUFREQ_E_NOT_OK Data has not been copied. Requestfailed,
 **         in case the corresponding I-PDU was stopped.
 ** \retval BUFREQ_E_BUSY Request could not be fulfilled, because
 **         the required amount of Tx data is not available. The lower
 **         layer module may retry this call later on. No data has been
 **         copied.
 **
 ** \ServiceID{::DCM_SVCID_COPYTXDATA}
 ** \Reentrancy{Reentrant for different PduIds.Non reentrant for the same PduId.}
 ** \Synchronicity{Synchronous}
 */
/* !LINKSTO Dcm.LowerLayerInterfaces.DcmPdurInterfaceVersionAutosar403.Dcm_CopyTxData,1 */
extern FUNC(BufReq_ReturnType, DCM_CODE) Dcm_CopyTxData(
  PduIdType DcmTxPduId,
  P2VAR(PduInfoType, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr,
  P2VAR(RetryInfoType, AUTOMATIC, DCM_APPL_DATA) RetryInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) TxDataCntPtr);

/** \brief Comfirm (un)successfull transmission
 **
 ** This function is called by the lower layer (in general the PDU Router):
 ** - with Result = ::NTFSRSLT_OK after the complete DCM I-PDU has successfully been transmitted,
 ** i.e. at the very end of the segmented TP transmit cycle. Within this function, the DCM shall
 ** unlock the transmit buffer.
 ** - with Result = ::NTFSRSLT_NOT_OK if an error (e.g. timeout) has occurred during the
 ** transmission of the DCM I-PDU. This enables unlocking
 ** of the transmit buffer and error handling.
 **
 ** \param[in] DcmTxPduId ID of DCM I-PDU that has been transmitted.
 **
 ** \param[in] Result Result of the N-PDU transmission.
 **
 ** \ServiceID{::DCM_SVCID_TPTXCONFIRMATION}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
/* !LINKSTO Dcm.LowerLayerInterfaces.DcmPdurInterfaceVersionAutosar403.Dcm_TpTxConfirmation,1 */
extern FUNC(void, DCM_CODE) Dcm_TpTxConfirmation(
  PduIdType DcmTxPduId,
  NotifResultType Result);

/** \brief This funtion is only a stub to provide the function symbol */
/* !LINKSTO Dcm.EB.LowerLayerInterfaces.DcmPdurInterfaceVersionAutosar403.Dcm_RxIndication,1 */
extern FUNC(void, DCM_CODE) Dcm_RxIndication(
  PduIdType DcmRxPduId,
  P2VAR(PduInfoType, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr);

/** \brief Comfirm (un)successfull transmission
 **
 ** This function is called by the lower layer (in general the PDU Router). This enables unlocking
 ** of the transmit buffer and error handling.
 **
 ** \param[in] DcmTxPduId ID of DCM I-PDU that has been transmitted.
 **
 ** \ServiceID{::DCM_SVCID_TXCONFIRMATION}
 ** \Reentrancy{Reentrant for different PduIds. Non reentrant for the same PduId.}
 ** \Synchronicity{Synchronous}
 */
/* !LINKSTO Dcm.LowerLayerInterfaces.DcmPdurInterfaceVersionAutosar403.PeriodicTransmission.Dcm_TxConfirmation,1 */
extern FUNC(void, DCM_CODE) Dcm_TxConfirmation(
  PduIdType DcmTxPduId);

#else /* #if (DCM_PDUR_INTERFACE_VERSION == DCM_PDUR_INTERFACE_AUTOSAR_R21_11) */

/** \brief This function is called at the start of receiving an N-SDU. The N-SDU might be fragmented into
 **        multiple N-PDUs (FF with one or more following CFs) or might consist of a single N-PDU (SF).
 **        The service shall provide the currently available maximum buffer size when invoked with TpSdu
 **        Length equal to 0. This function might be called in interrupt context.
 **
 ** \param[in] id Identification of the I-PDU.
 **
 ** \param[in] info Pointer to a PduInfoType structure containing the payload data (without protocol
 **            information) and payload length of the first frame or single frame of a transport
 **            protocol I-PDU reception, and the MetaData related to this PDU. If neither first/single
 **            frame data nor MetaData are available, this parameter is set to NULL_PTR.
 **
 ** \param[in] TpSduLength Total length of the N-SDU to be received.
 **
 ** \param[out] bufferSizePtr Available receive buffer in the receiving module. This parameter
 **             will be used to compute the Block Size (BS) in the transport protocol module.
 **
 ** \return Request data copy status
 ** \retval BUFREQ_OK Connection has been accepted. bufferSizePtr indicates the available receive
 **                   buffer; reception is continued. If no buffer of the requested size is available,
 **                   a receive buffer size of 0 shall be indicated by bufferSizePtr.
 **
 ** \retval BUFREQ_E_NOT_OK Connection has been rejected; reception is aborted. bufferSizePtr remains unchanged.
 **
 ** \retval BUFREQ_E_OVFL: No buffer of the required length can be provided; reception is aborted.
 **                        bufferSizePtr remains unchanged.
 **
 ** \ServiceID     {::DCM_SVCID_STARTOFRECEPTION}
 ** \Reentrancy    {Reentrant}
 ** \Synchronicity {Synchronous}
 */
/* !LINKSTO Dcm.LowerLayerInterfaces.DcmPdurInterfaceVersionAutosarR21-11.Dcm_StartOfReception,1 */
extern FUNC(BufReq_ReturnType, DCM_CODE) Dcm_StartOfReception(
  PduIdType id,
  P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) info,
  PduLengthType TpSduLength,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) bufferSizePtr);

/** \brief This function is called to provide the received data of an I-PDU segment (N-PDU) to the upper
 **        layer. Each call to this function provides the next part of the I-PDU data. The size of the
 **        remaining buffer is written to the position indicated by bufferSizePtr. This function might be
 **        called in interrupt context.
 **
 ** \param[in] id Identification of the received I-PDU.
 **
 ** \param[in] info Provides the source buffer (SduDataPtr) and the number of bytes to be copied
 **                 (SduLength). An SduLength of 0 can be used to query the current amount of available
 **                 buffer in the upper layer module. In this case, the SduDataPtr may be a NULL_PTR.
 **
 ** \param[out] bufferSizePtr Available receive buffer after data has been copied.
 **
 ** \return Request data copy status
 ** \retval BUFREQ_OK Data copied successfully.
 **
 ** \retval BUFREQ_E_NOT_OK Data was not copied because an error occurred.
 **
 ** \ServiceID     {::DCM_SVCID_COPYRXDATA}
 ** \Reentrancy    {Reentrant for different PduIds.Non reentrant for the same PduId.}
 ** \Synchronicity {Synchronous}
 */
/* !LINKSTO Dcm.LowerLayerInterfaces.DcmPdurInterfaceVersionAutosarR21-11.Dcm_CopyRxData,1 */
extern FUNC(BufReq_ReturnType, DCM_CODE) Dcm_CopyRxData(
  PduIdType id,
  P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) info,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) bufferSizePtr);

/** \brief Called after an I-PDU has been received via the TP API, the result indicates whether the
 **        transmission was successful or not. This function might be called in interrupt context.
 **
 ** \param[in] id     Identification of the received I-PDU.
 **
 ** \param[in] result Result of the reception.
 **
 ** \ServiceID     {::DCM_SVCID_TPRXINDICATION}
 ** \Reentrancy    {Reentrant}
 ** \Synchronicity {Synchronous}
 */
/* !LINKSTO Dcm.LowerLayerInterfaces.DcmPdurInterfaceVersionAutosarR21-11.Dcm_TpRxIndication,1 */
extern FUNC(void, DCM_CODE) Dcm_TpRxIndication(
  PduIdType id,
  Std_ReturnType result);

/** \brief This function is called to acquire the transmit data of an I-PDU segment (N-PDU).
 **        Each call to this function provides the next part of the I-PDU data unless retry->TpDataState
 **        is TP_DATARETRY. In this case the function restarts to copy the data beginning at the offset
 **        current position indicated by retry->TxTpDataCnt. The size of the remaining data is written to
 **        the position indicated by availableDataPtr. This function might be called in interrupt context.
 **
 ** \param[in] id Identification of the transmitted I-PDU.
 **
 ** \param[in] info Provides the destination buffer (SduDataPtr) and the number of bytes to be copied (SduLength).
 **                 If not enough transmit data is available, no data is copied by the upper layer module
 **                 and BUFREQ_E_BUSY is returned. The lower layer module may retry the call.
 **                 An SduLength of 0 can be used to indicate state changes in the retry parameter
 **                 or to query the current amount of available data in the upper layer module.
 **                 In this case, the Sdu DataPtr may be a NULL_PTR.
 **
 ** \param[in] retry This parameter is used to acknowledge transmitted data or to retransmit data
 **                  after transmission problems. If the retry parameter is a NULL_PTR, it indicates
 **                  that the transmit data can be removed from the buffer immediately after it has
 **                  been copied. Otherwise, the retry parameter must point to a valid RetryInfoType
 **                  element. If TpDataState indicates TP_CONFPENDING, the previously copied data
 **                  must remain in the TP buffer to be available for error recovery. TP_DATACONF
 **                  indicates that all data that has been copied before this call is confirmed and
 **                  can be removed from the TP buffer. Data copied by this API call is excluded and
 **                  will be confirmed later. TP_DATARETRY indicates that this API call shall copy
 **                  previously copied data in order to recover from an error. In this case
 **                  TxTpDataCnt specifies the offset in bytes from the current data copy position.
 **
 ** \param[out] availableDataPtr Indicates the remaining number of bytes that are available in the
 **                              upper layer module’s Tx buffer. availableDataPtr can be used by TP
 **                              modules that support dynamic payload lengths (e.g. FrIsoTp) to
 **                              determine the size of the following CFs.
 **
 ** \return Response data copy status
 ** \retval BUFREQ_OK Data has been copied to the transmit buffer completely as requested.
 **
 ** \retval BUFREQ_E_BUSY Request could not be fulfilled, because the required amount of Tx data is
 **                       not available. The lower layer module may retry this call later on.
 **                       No data has been copied.
 **
 ** \retval BUFREQ_E_NOT_OK Data has not been copied. Request failed.
 **
 ** \ServiceID     {::DCM_SVCID_COPYTXDATA}
 ** \Reentrancy    {Reentrant for different PduIds.Non reentrant for the same PduId.}
 ** \Synchronicity {Synchronous}
 */
/* !LINKSTO Dcm.LowerLayerInterfaces.DcmPdurInterfaceVersionAutosarR21-11.Dcm_CopyTxData,1 */
extern FUNC(BufReq_ReturnType, DCM_CODE) Dcm_CopyTxData(
  PduIdType id,
  P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) info,
  P2CONST(RetryInfoType, AUTOMATIC, DCM_APPL_DATA) retry,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) availableDataPtr);

/** \brief This function is called after the I-PDU has been transmitted on its network, the result
 **        indicates whether the transmission was successful or not. This function might be called context.
 **
 ** \param[in] id Identification of the transmitted I-PDU.
 **
 ** \param[in] result Result of the transmission of the I-PDU.
 **
 ** \ServiceID     {::DCM_SVCID_TPTXCONFIRMATION}
 ** \Reentrancy    {Reentrant}
 ** \Synchronicity {Synchronous}
 */
/* !LINKSTO Dcm.LowerLayerInterfaces.DcmPdurInterfaceVersionAutosarR21-11.Dcm_TpTxConfirmation,1 */
extern FUNC(void, DCM_CODE) Dcm_TpTxConfirmation(
  PduIdType id,
  Std_ReturnType result);

/** \brief This funtion is only a stub to provide the function symbol */
/* !LINKSTO Dcm.EB.LowerLayerInterfaces.DcmPdurInterfaceVersionAutosarR21-11.Dcm_RxIndication,1 */
extern FUNC(void, DCM_CODE) Dcm_RxIndication(
  PduIdType RxPduId,
  P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr);

/** \brief The lower layer communication interface module confirms the transmission of a PDU, or the
 **        failure to transmit a PDU. This function might be called in interrupt context.
 **
 ** \param[in] DcmTxPduId ID of the PDU that has been transmitted.
 **
 ** \param[in] result E_OK: The PDU was transmitted. E_NOT_OK: Transmission of the PDU failed.
 **
 ** \ServiceID{::DCM_SVCID_TXCONFIRMATION}
 ** \Reentrancy{Reentrant for different PduIds. Non reentrant for the same PduId.}
 ** \Synchronicity{Synchronous}
 */
/* !LINKSTO Dcm.LowerLayerInterfaces.DcmPdurInterfaceVersionAutosarR21-11.PeriodicTransmission.Dcm_TxConfirmation,1 */
extern FUNC(void, DCM_CODE) Dcm_TxConfirmation(
  PduIdType DcmTxPduId,
  Std_ReturnType result);
#endif /* #if (DCM_PDUR_INTERFACE_VERSION == DCM_PDUR_INTERFACE_AUTOSAR_403) */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*==================[internal function declarations]=============================================*/

/*==================[external constants]=========================================================*/

/*==================[internal constants]=========================================================*/

/*==================[external data]==============================================================*/

/*==================[internal data]==============================================================*/

/*==================[external function definitions]==============================================*/

/*==================[internal function definitions]==============================================*/

#endif /* ifndef DCM_CBK_H */
/*==================[end of file]================================================================*/
