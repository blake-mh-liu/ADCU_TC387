/* *--------{ EB Automotive C Source File }-------- */
#ifndef  J1939DCM_CBK_H
#define  J1939DCM_CBK_H

/*==================[includes]===============================================*/
#include <ComM_Dcm.h>

#include <J1939Dcm_Cfg.h>

#include <J1939Dcm_Types.h>
/*==================[external function declarations]========================*/
#define  J1939DCM_START_SEC_CODE_CORE
#include <J1939Dcm_MemMap.h>

/* Indicates reception of a Request PG. */
extern FUNC(void, J1939DCM_CODE) J1939Dcm_RequestIndication(    VAR(uint8, AUTOMATIC) node,
                                                                VAR(NetworkHandleType, AUTOMATIC) channel,
                                                                VAR(uint32, AUTOMATIC) requestedPgn,
                                                                VAR(uint8, AUTOMATIC) sourceAddress,
                                                                VAR(uint8, AUTOMATIC) destAddress,
                                                                VAR(uint8, AUTOMATIC) priority );

/* Indication of a received I-PDU from a lower layer communication interface module. */
extern FUNC(void, J1939DCM_CODE) J1939Dcm_RxIndication( PduIdType RxPduId,
                                                        P2CONST(PduInfoType, AUTOMATIC, AUTOMATIC) PduInfoPtr );

extern FUNC(void, J1939DCM_CODE) J1939Dcm_TxConfirmation(   VAR(PduIdType, AUTOMATIC) TxPduId);

/* This function is called at the start of receiving an N-SDU. */
extern FUNC(BufReq_ReturnType, J1939DCM_CODE) J1939Dcm_StartOfReception(    VAR(PduIdType, AUTOMATIC) id,
                                                                            VAR(PduLengthType, AUTOMATIC) TpSduLength,
                                                                            P2VAR(PduLengthType, AUTOMATIC, AUTOMATIC) bufferSizePtr );

/* This function is called to provide the received data of an I-PDU segment (N-PDU) to the upper layer. */
extern FUNC(BufReq_ReturnType, J1939DCM_CODE) J1939Dcm_CopyRxData(  VAR(PduIdType, AUTOMATIC) id,
                                                                    P2CONST(PduInfoType, AUTOMATIC, AUTOMATIC) info,
                                                                    P2VAR(PduLengthType, AUTOMATIC, AUTOMATIC) bufferSizePtr );

/* Called after an I-PDU has been received, the result indicates whether the transmission was successful or not. */
extern FUNC(void, J1939DCM_CODE) J1939Dcm_TpRxIndication(   VAR(PduIdType, AUTOMATIC) id,
                                                            VAR(NotifResultType, AUTOMATIC) result );

#if (J1939DCM_TP_TX_AVAILABLE == STD_ON)
/* This function is called to acquire the transmit data of an I-PDU segment (N-PDU). */
extern FUNC(BufReq_ReturnType, J1939DCM_CODE) J1939Dcm_CopyTxData(  VAR(PduIdType, AUTOMATIC) id,
                                                                    P2CONST(PduInfoType, AUTOMATIC, AUTOMATIC) info,
                                                                    P2VAR(RetryInfoType, AUTOMATIC, AUTOMATIC) retry,
                                                                    P2VAR(PduLengthType, AUTOMATIC, AUTOMATIC) availableDataPtr );

/* This function is called after the I-PDU has been transmitted, the result indicates whether the transmission was successful or not. */
extern FUNC(void, J1939DCM_CODE) J1939Dcm_TpTxConfirmation(     VAR(PduIdType, AUTOMATIC) id,
                                                                VAR(Std_ReturnType, AUTOMATIC) result);

#endif /* (J1939DCM_TP_TX_AVAILABLE == STD_ON) */

extern FUNC(void, J1939DCM_CODE) J1939Dcm_DemTriggerOnDTCStatus(VAR(uint32, AUTOMATIC) DTC);

extern FUNC(Std_ReturnType, J1939DCM_CODE) J1939Dcm_SetState(   VAR(NetworkHandleType, AUTOMATIC) channel,
                                                                VAR(uint8, AUTOMATIC) node,
                                                                VAR(J1939Dcm_StateType, AUTOMATIC) newState);

#if(J1939DCM_DM13_AVAILABLE == STD_ON)
/* This function allows the application software to control the transmission of broadcast message for DM13 feature*/
extern FUNC(Std_ReturnType, J1939DCM_CODE)J1939Dcm_Broadcast_Transmission_Mode(boolean tTransmissionMode);
#endif/* (J1939DCM_DM13_AVAILABLE == STD_ON)*/

#define  J1939DCM_STOP_SEC_CODE_CORE
#include <J1939Dcm_MemMap.h>

#endif

