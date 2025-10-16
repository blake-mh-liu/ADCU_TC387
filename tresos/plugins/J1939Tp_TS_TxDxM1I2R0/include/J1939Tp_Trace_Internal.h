/**
 * \file
 *
 * \brief AUTOSAR J1939Tp
 *
 * This file contains the implementation of the AUTOSAR
 * module J1939Tp.
 *
 * \version 1.2.14
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#ifndef J1939TP_TRACE_INTERNAL_H
#define J1939TP_TRACE_INTERNAL_H

/*==================[inclusions]============================================*/

/*==================[macros]================================================*/
/* Place internal debug instrumentation macros in this file, i.e. all
   macros that are not generated for the public api instrumentation.
*/
/*==================[macros]================================================*/

#ifndef DBG_J1939TP_BAM_TRANSMIT_ENTRY
/** \brief Entry point of function J1939Tp_BAM_Transmit() */
#define DBG_J1939TP_BAM_TRANSMIT_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_BAM_TRANSMIT_EXIT
/** \brief Exit point of function J1939Tp_BAM_Transmit() */
#define DBG_J1939TP_BAM_TRANSMIT_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_CMDT_TRANSMIT_ENTRY
/** \brief Entry point of function J1939Tp_CMDT_Transmit() */
#define DBG_J1939TP_CMDT_TRANSMIT_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_CMDT_TRANSMIT_EXIT
/** \brief Exit point of function J1939Tp_CMDT_Transmit() */
#define DBG_J1939TP_CMDT_TRANSMIT_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_BAM_RECEPTION_ENTRY
/** \brief Entry point of function J1939Tp_BAM_Reception() */
#define DBG_J1939TP_BAM_RECEPTION_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_BAM_RECEPTION_EXIT
/** \brief Exit point of function J1939Tp_BAM_Reception() */
#define DBG_J1939TP_BAM_RECEPTION_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_CMDT_RECEPTION_ENTRY
/** \brief Entry point of function J1939Tp_CMDT_Reception() */
#define DBG_J1939TP_CMDT_RECEPTION_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_CMDT_RECEPTION_EXIT
/** \brief Exit point of function J1939Tp_CMDT_Reception() */
#define DBG_J1939TP_CMDT_RECEPTION_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_RX_CMDT_WAIT_TXCONFIRMATION_ENTRY
/** \brief Entry point of function J1939Tp_Rx_CMDT_Wait_TxConfirmation() */
#define DBG_J1939TP_RX_CMDT_WAIT_TXCONFIRMATION_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_RX_CMDT_WAIT_TXCONFIRMATION_EXIT
/** \brief Exit point of function J1939Tp_Rx_CMDT_Wait_TxConfirmation() */
#define DBG_J1939TP_RX_CMDT_WAIT_TXCONFIRMATION_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_DIRECTPG_TRANSMIT_ENTRY
/** \brief Entry point of function J1939Tp_DirectPg_Transmit() */
#define DBG_J1939TP_DIRECTPG_TRANSMIT_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_DIRECTPG_TRANSMIT_EXIT
/** \brief Exit point of function J1939Tp_DirectPg_Transmit() */
#define DBG_J1939TP_DIRECTPG_TRANSMIT_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_DIRECTPG_DATA_TRANSMIT_ENTRY
/** \brief Entry point of function J1939Tp_DirectPg_Data_Transmit() */
#define DBG_J1939TP_DIRECTPG_DATA_TRANSMIT_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_DIRECTPG_DATA_TRANSMIT_EXIT
/** \brief Exit point of function J1939Tp_DirectPg_Data_Transmit() */
#define DBG_J1939TP_DIRECTPG_DATA_TRANSMIT_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_UNLOCKTXPDU_ENTRY
/** \brief Entry point of function J1939Tp_UnlockTxPdu() */
#define DBG_J1939TP_UNLOCKTXPDU_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_UNLOCKTXPDU_EXIT
/** \brief Exit point of function J1939Tp_UnlockTxPdu() */
#define DBG_J1939TP_UNLOCKTXPDU_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_TXTIMERJOB_ENTRY
/** \brief Entry point of function J1939Tp_TxTimerJob() */
#define DBG_J1939TP_TXTIMERJOB_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_TXTIMERJOB_EXIT
/** \brief Exit point of function J1939Tp_TxTimerJob() */
#define DBG_J1939TP_TXTIMERJOB_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_RXTIMERJOB_ENTRY
/** \brief Entry point of function J1939Tp_RxTimerJob() */
#define DBG_J1939TP_RXTIMERJOB_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_RXTIMERJOB_EXIT
/** \brief Exit point of function J1939Tp_RxTimerJob() */
#define DBG_J1939TP_RXTIMERJOB_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_TXCONFIRMATIONTIMERJOB_ENTRY
/** \brief Entry point of function J1939Tp_TxConfirmationTimerJob() */
#define DBG_J1939TP_TXCONFIRMATIONTIMERJOB_ENTRY(a)
#endif

#ifndef DBG_J1939TP_TXCONFIRMATIONTIMERJOB_EXIT
/** \brief Exit point of function J1939Tp_TxConfirmationTimerJob() */
#define DBG_J1939TP_TXCONFIRMATIONTIMERJOB_EXIT(a)
#endif

#ifndef DBG_J1939TP_FCNPDUMETADATA_HANDLE_ENTRY
/** \brief Entry point of function J1939Tp_FCNPduMetaData_Handle() */
#define DBG_J1939TP_FCNPDUMETADATA_HANDLE_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_J1939TP_FCNPDUMETADATA_HANDLE_EXIT
/** \brief Exit point of function J1939Tp_FCNPduMetaData_Handle() */
#define DBG_J1939TP_FCNPDUMETADATA_HANDLE_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_J1939TP_RXINDICATION_DIRECTPG_ENTRY
/** \brief Entry point of function RxIndication_DirectPg() */
#define DBG_J1939TP_RXINDICATION_DIRECTPG_ENTRY(a,b,c,d)
#endif

#ifndef DBG_J1939TP_RXINDICATION_DIRECTPG_EXIT
/** \brief Exit point of function RxIndication_DirectPg() */
#define DBG_J1939TP_RXINDICATION_DIRECTPG_EXIT(a,b,c,d)
#endif

#ifndef DBG_J1939TP_NSDU_CHANGESTATE_ENTRY
/** \brief Entry point of function J1939Tp_NSDU_ChangeState() */
#define DBG_J1939TP_NSDU_CHANGESTATE_ENTRY(a,b)
#endif

#ifndef DBG_J1939TP_NSDU_CHANGESTATE_EXIT
/** \brief Exit point of function J1939Tp_NSDU_ChangeState() */
#define DBG_J1939TP_NSDU_CHANGESTATE_EXIT(a,b)
#endif

#ifndef DBG_J1939TP_RXINDICATION_TXFCN_CTS_ENTRY
/** \brief Entry point of function J1939Tp_RxIndication_TxFcN_CTS() */
#define DBG_J1939TP_RXINDICATION_TXFCN_CTS_ENTRY(a,b,c,d)
#endif

#ifndef DBG_J1939TP_RXINDICATION_TXFCN_CTS_EXIT
/** \brief Exit point of function J1939Tp_RxIndication_TxFcN_CTS() */
#define DBG_J1939TP_RXINDICATION_TXFCN_CTS_EXIT(a,b,c,d)
#endif

#ifndef DBG_J1939TP_CMDT_TRANSMIT_DATA_ENTRY
/** \brief Entry point of function J1939Tp_CMDT_Transmit_Data() */
#define DBG_J1939TP_CMDT_TRANSMIT_DATA_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_CMDT_TRANSMIT_DATA_EXIT
/** \brief Exit point of function J1939Tp_CMDT_Transmit_Data() */
#define DBG_J1939TP_CMDT_TRANSMIT_DATA_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_CMDT_WAIT_CTS_ENTRY
/** \brief Entry point of function J1939Tp_CMDT_Wait_CTS() */
#define DBG_J1939TP_CMDT_WAIT_CTS_ENTRY(a)
#endif

#ifndef DBG_J1939TP_CMDT_WAIT_CTS_EXIT
/** \brief Exit point of function J1939Tp_CMDT_Wait_CTS() */
#define DBG_J1939TP_CMDT_WAIT_CTS_EXIT(a)
#endif

#ifndef DBG_J1939TP_CMDT_WAIT_EOM_ENTRY
/** \brief Entry point of function J1939Tp_CMDT_Wait_EOM() */
#define DBG_J1939TP_CMDT_WAIT_EOM_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_CMDT_WAIT_EOM_EXIT
/** \brief Exit point of function J1939Tp_CMDT_Wait_EOM() */
#define DBG_J1939TP_CMDT_WAIT_EOM_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_CMDT_FD_TRANSMIT_DATA_ENTRY
/** \brief Entry point of function J1939Tp_CMDT_FD_Transmit_Data() */
#define DBG_J1939TP_CMDT_FD_TRANSMIT_DATA_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_CMDT_FD_TRANSMIT_DATA_EXIT
/** \brief Exit point of function J1939Tp_CMDT_FD_Transmit_Data() */
#define DBG_J1939TP_CMDT_FD_TRANSMIT_DATA_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_TXCONFIRMATION_VALIDATE_TXPDUID_ENTRY
/** \brief Entry point of function J1939Tp_TxConfirmation_Validate_TxPduId() */
#define DBG_J1939TP_TXCONFIRMATION_VALIDATE_TXPDUID_ENTRY(a,b)
#endif

#ifndef DBG_J1939TP_TXCONFIRMATION_VALIDATE_TXPDUID_EXIT
/** \brief Exit point of function J1939Tp_TxConfirmation_Validate_TxPduId() */
#define DBG_J1939TP_TXCONFIRMATION_VALIDATE_TXPDUID_EXIT(a,b)
#endif

#ifndef DBG_J1939TP_TXCONFIRMATION_CM_ENTRY
/** \brief Entry point of function J1939Tp_TxConfirmation_CM() */
#define DBG_J1939TP_TXCONFIRMATION_CM_ENTRY(a,b)
#endif

#ifndef DBG_J1939TP_TXCONFIRMATION_CM_EXIT
/** \brief Exit point of function J1939Tp_TxConfirmation_CM() */
#define DBG_J1939TP_TXCONFIRMATION_CM_EXIT(a,b)
#endif

#ifndef DBG_J1939TP_TXCONFIRMATION_DT_ENTRY
/** \brief Entry point of function J1939Tp_TxConfirmation_DT() */
#define DBG_J1939TP_TXCONFIRMATION_DT_ENTRY(a,b)
#endif

#ifndef DBG_J1939TP_TXCONFIRMATION_DT_EXIT
/** \brief Exit point of function J1939Tp_TxConfirmation_DT() */
#define DBG_J1939TP_TXCONFIRMATION_DT_EXIT(a,b)
#endif

#ifndef DBG_J1939TP_TXCONFIRMATION_CMDT_DATA_ENTRY
/** \brief Entry point of function J1939Tp_TxConfirmation_CMDT_Data() */
#define DBG_J1939TP_TXCONFIRMATION_CMDT_DATA_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_TXCONFIRMATION_CMDT_DATA_EXIT
/** \brief Exit point of function J1939Tp_TxConfirmation_CMDT_Data() */
#define DBG_J1939TP_TXCONFIRMATION_CMDT_DATA_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_TXCONFIRMATION_CMDT_EOMS_ENTRY
/** \brief Entry point of function J1939Tp_TxConfirmation_CMDT_EOMS() */
#define DBG_J1939TP_TXCONFIRMATION_CMDT_EOMS_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_TXCONFIRMATION_CMDT_EOMS_EXIT
/** \brief Exit point of function J1939Tp_TxConfirmation_CMDT_EOMS() */
#define DBG_J1939TP_TXCONFIRMATION_CMDT_EOMS_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_RXINDICATION_VALIDATE_RXPDUID_ENTRY
/** \brief Entry point of function J1939Tp_RxIndication_Validate_RxPduId() */
#define DBG_J1939TP_RXINDICATION_VALIDATE_RXPDUID_ENTRY(a,b)
#endif

#ifndef DBG_J1939TP_RXINDICATION_VALIDATE_RXPDUID_EXIT
/** \brief Exit point of function J1939Tp_RxIndication_Validate_RxPduId() */
#define DBG_J1939TP_RXINDICATION_VALIDATE_RXPDUID_EXIT(a,b)
#endif

#ifndef DBG_J1939TP_RXINDICATION_DT_ENTRY
/** \brief Entry point of function J1939Tp_RxIndication_DT() */
#define DBG_J1939TP_RXINDICATION_DT_ENTRY(a,b,c,d)
#endif

#ifndef DBG_J1939TP_RXINDICATION_DT_EXIT
/** \brief Exit point of function J1939Tp_RxIndication_DT() */
#define DBG_J1939TP_RXINDICATION_DT_EXIT(a,b,c,d)
#endif

#ifndef DBG_J1939TP_SETECUCMETADATARX_ENTRY
/** \brief Entry point of function J1939Tp_SetEcuCMetaDataRx() */
#define DBG_J1939TP_SETECUCMETADATARX_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_SETECUCMETADATARX_EXIT
/** \brief Exit point of function J1939Tp_SetEcuCMetaDataRx() */
#define DBG_J1939TP_SETECUCMETADATARX_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_NPDUMETADATA_HANDLE_ENTRY
/** \brief Entry point of function J1939Tp_NPduMetaData_Handle() */
#define DBG_J1939TP_NPDUMETADATA_HANDLE_ENTRY(a,b,c,d,e,f)
#endif

#ifndef DBG_J1939TP_NPDUMETADATA_HANDLE_EXIT
/** \brief Exit point of function J1939Tp_NPduMetaData_Handle() */
#define DBG_J1939TP_NPDUMETADATA_HANDLE_EXIT(a,b,c,d,e,f)
#endif

#ifndef DBG_J1939TP_RXINDICATION_TXFCN_CM_ENTRY
/** \brief Entry point of function J1939Tp_RxIndication_TxFcN_CM() */
#define DBG_J1939TP_RXINDICATION_TXFCN_CM_ENTRY(a,b)
#endif

#ifndef DBG_J1939TP_RXINDICATION_TXFCN_CM_EXIT
/** \brief Exit point of function J1939Tp_RxIndication_TxFcN_CM() */
#define DBG_J1939TP_RXINDICATION_TXFCN_CM_EXIT(a,b)
#endif

#ifndef DBG_J1939TP_VALIDATE_TXFCN_CM_LENGTH_ENTRY
/** \brief Entry point of function J1939Tp_Validate_TxFcN_CM_Length() */
#define DBG_J1939TP_VALIDATE_TXFCN_CM_LENGTH_ENTRY(a,b,c,d,e,f)
#endif

#ifndef DBG_J1939TP_VALIDATE_TXFCN_CM_LENGTH_EXIT
/** \brief Exit point of function J1939Tp_Validate_TxFcN_CM_Length() */
#define DBG_J1939TP_VALIDATE_TXFCN_CM_LENGTH_EXIT(a,b,c,d,e,f)
#endif

#ifndef DBG_J1939TP_RXINDICATION_CM_ENTRY
/** \brief Entry point of function J1939Tp_RxIndication_CM() */
#define DBG_J1939TP_RXINDICATION_CM_ENTRY(a,b)
#endif

#ifndef DBG_J1939TP_RXINDICATION_CM_EXIT
/** \brief Exit point of function J1939Tp_RxIndication_CM() */
#define DBG_J1939TP_RXINDICATION_CM_EXIT(a,b)
#endif

#ifndef DBG_J1939TP_CM_VALIDATION_ENTRY
/** \brief Entry point of function J1939Tp_CM_Validation() */
#define DBG_J1939TP_CM_VALIDATION_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_CM_VALIDATION_EXIT
/** \brief Exit point of function J1939Tp_CM_Validation() */
#define DBG_J1939TP_CM_VALIDATION_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_CM_TYPE_CHECK_ENTRY
/** \brief Entry point of function J1939Tp_CM_Type_check() */
#define DBG_J1939TP_CM_TYPE_CHECK_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_J1939TP_CM_TYPE_CHECK_EXIT
/** \brief Exit point of function J1939Tp_CM_Type_check() */
#define DBG_J1939TP_CM_TYPE_CHECK_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_J1939TP_RXINDICATION_CM_EOMS_ENTRY
/** \brief Entry point of function J1939Tp_RxIndication_CM_EOMS() */
#define DBG_J1939TP_RXINDICATION_CM_EOMS_ENTRY(a,b,c,d)
#endif

#ifndef DBG_J1939TP_RXINDICATION_CM_EOMS_EXIT
/** \brief Exit point of function J1939Tp_RxIndication_CM_EOMS() */
#define DBG_J1939TP_RXINDICATION_CM_EOMS_EXIT(a,b,c,d)
#endif

#ifndef DBG_J1939TP_RXGET_METADATAINFO_ENTRY
/** \brief Entry point of function J1939Tp_RxGet_MetaDataInfo() */
#define DBG_J1939TP_RXGET_METADATAINFO_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_RXGET_METADATAINFO_EXIT
/** \brief Exit point of function J1939Tp_RxGet_MetaDataInfo() */
#define DBG_J1939TP_RXGET_METADATAINFO_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_RXGET_PG_ID_ENTRY
/** \brief Entry point of function J1939Tp_RxGet_pg_id() */
#define DBG_J1939TP_RXGET_PG_ID_ENTRY(a)
#endif

#ifndef DBG_J1939TP_RXGET_PG_ID_EXIT
/** \brief Exit point of function J1939Tp_RxGet_pg_id() */
#define DBG_J1939TP_RXGET_PG_ID_EXIT(a,b)
#endif

#ifndef DBG_J1939TP_RXGET_NSDU_ID_ENTRY
/** \brief Entry point of function J1939Tp_RxGet_nsdu_id() */
#define DBG_J1939TP_RXGET_NSDU_ID_ENTRY(a)
#endif

#ifndef DBG_J1939TP_RXGET_NSDU_ID_EXIT
/** \brief Exit point of function J1939Tp_RxGet_nsdu_id() */
#define DBG_J1939TP_RXGET_NSDU_ID_EXIT(a,b)
#endif

#ifndef DBG_J1939TP_RXINDICATION_CM_DT_ENTRY
/** \brief Entry point of function J1939Tp_RxIndication_CM_DT() */
#define DBG_J1939TP_RXINDICATION_CM_DT_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_RXINDICATION_CM_DT_EXIT
/** \brief Exit point of function J1939Tp_RxIndication_CM_DT() */
#define DBG_J1939TP_RXINDICATION_CM_DT_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_RXINDICATION_CM_RTS_ENTRY
/** \brief Entry point of function J1939Tp_RxIndication_CM_RTS() */
#define DBG_J1939TP_RXINDICATION_CM_RTS_ENTRY(a,b)
#endif

#ifndef DBG_J1939TP_RXINDICATION_CM_RTS_EXIT
/** \brief Exit point of function J1939Tp_RxIndication_CM_RTS() */
#define DBG_J1939TP_RXINDICATION_CM_RTS_EXIT(a,b)
#endif

#ifndef DBG_J1939TP_RXINDICATION_CM_RTS_IDLE_ENTRY
/** \brief Entry point of function J1939Tp_RxIndication_CM_RTS_IDLE() */
#define DBG_J1939TP_RXINDICATION_CM_RTS_IDLE_ENTRY(a)
#endif

#ifndef DBG_J1939TP_RXINDICATION_CM_RTS_IDLE_EXIT
/** \brief Exit point of function J1939Tp_RxIndication_CM_RTS_IDLE() */
#define DBG_J1939TP_RXINDICATION_CM_RTS_IDLE_EXIT(a)
#endif

#ifndef DBG_J1939Tp_RxIndication_CM_BAM_ENTRY
/** \brief Entry point of function J1939Tp_RxIndication_CM_BAM() */
#define DBG_J1939Tp_RxIndication_CM_BAM_ENTRY(a,b)
#endif

#ifndef DBG_J1939Tp_RxIndication_CM_BAM_EXIT
/** \brief Exit point of function J1939Tp_RxIndication_CM_BAM() */
#define DBG_J1939Tp_RxIndication_CM_BAM_EXIT(a,b)
#endif

#ifndef DBG_J1939TP_RXINDICATION_CM_ABORT_ENTRY
/** \brief Entry point of function J1939Tp_RxIndication_CM_Abort() */
#define DBG_J1939TP_RXINDICATION_CM_ABORT_ENTRY(a,b,c,d)
#endif

#ifndef DBG_J1939TP_RXINDICATION_CM_ABORT_EXIT
/** \brief Exit point of function J1939Tp_RxIndication_CM_Abort() */
#define DBG_J1939TP_RXINDICATION_CM_ABORT_EXIT(a,b,c,d)
#endif

#ifndef DBG_J1939Tp_RxIndication_CM_BAM_IDLE_ENTRY
/** \brief Entry point of function J1939Tp_RxIndication_CM_BAM_IDLE() */
#define DBG_J1939Tp_RxIndication_CM_BAM_IDLE_ENTRY(a)
#endif

#ifndef DBG_J1939Tp_RxIndication_CM_BAM_IDLE_EXIT
/** \brief Exit point of function J1939Tp_RxIndication_CM_BAM_IDLE() */
#define DBG_J1939Tp_RxIndication_CM_BAM_IDLE_EXIT(a)
#endif

#ifndef DBG_J1939TP_NROFRXPACKETSINCTS_ENTRY
/** \brief Entry point of function J1939Tp_NrOfRxPacketsInCts() */
#define DBG_J1939TP_NROFRXPACKETSINCTS_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_NROFRXPACKETSINCTS_EXIT
/** \brief Exit point of function J1939Tp_NrOfRxPacketsInCts() */
#define DBG_J1939TP_NROFRXPACKETSINCTS_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_CHECKAVAILABLEBUFFER_ENTRY
/** \brief Entry point of function J1939Tp_CheckAvailableBuffer() */
#define DBG_J1939TP_CHECKAVAILABLEBUFFER_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_CHECKAVAILABLEBUFFER_EXIT
/** \brief Exit point of function J1939Tp_CheckAvailableBuffer() */
#define DBG_J1939TP_CHECKAVAILABLEBUFFER_EXIT(a,b,c,d)
#endif

#ifndef DBG_J1939TP_SENDFCWAIT_CTS_ENTRY
/** \brief Entry point of function J1939Tp_SendFCWait_CTS() */
#define DBG_J1939TP_SENDFCWAIT_CTS_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_SENDFCWAIT_CTS_EXIT
/** \brief Exit point of function J1939Tp_SendFCWait_CTS() */
#define DBG_J1939TP_SENDFCWAIT_CTS_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_ENDOFMSGACK_ENTRY
/** \brief Entry point of function J1939Tp_EndOfMsgAck() */
#define DBG_J1939TP_ENDOFMSGACK_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_ENDOFMSGACK_EXIT
/** \brief Exit point of function J1939Tp_EndOfMsgAck() */
#define DBG_J1939TP_ENDOFMSGACK_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_ABORT_CONN_ENTRY
/** \brief Entry point of function J1939Tp_Abort_Conn_RX() */
#define DBG_J1939TP_ABORT_CONN_ENTRY(a,b,c,d,e,f,g,h)
#endif

#ifndef DBG_J1939TP_ABORT_CONN_EXIT
/** \brief Exit point of function J1939Tp_Abort_Conn_RX() */
#define DBG_J1939TP_ABORT_CONN_EXIT(a,b,c,d,e,f,g,h)
#endif

#ifndef DBG_J1939TP_RXCHANNELABORTHANDLER_ENTRY
/** \brief Entry point of function J1939Tp_RxChannelAbortHandler() */
#define DBG_J1939TP_RXCHANNELABORTHANDLER_ENTRY(a)
#endif

#ifndef DBG_J1939TP_RXCHANNELABORTHANDLER_EXIT
/** \brief Exit point of function J1939Tp_RxChannelAbortHandler() */
#define DBG_J1939TP_RXCHANNELABORTHANDLER_EXIT(a)
#endif

#ifndef DBG_J1939TP_REINIT_RX_ENTRY
/** \brief Entry point of function J1939Tp_Reinit_Rx() */
#define DBG_J1939TP_REINIT_RX_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_REINIT_RX_EXIT
/** \brief Exit point of function J1939Tp_Reinit_Rx() */
#define DBG_J1939TP_REINIT_RX_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_REINIT_TX_ENTRY
/** \brief Entry point of function J1939Tp_Reinit_Tx() */
#define DBG_J1939TP_REINIT_TX_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_REINIT_TX_EXIT
/** \brief Exit point of function J1939Tp_Reinit_Tx() */
#define DBG_J1939TP_REINIT_TX_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_CMDT_RECEPTION_CTS0_ENTRY
/** \brief Entry point of function J1939Tp_CMDT_Reception_CTS0() */
#define DBG_J1939TP_CMDT_RECEPTION_CTS0_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_CMDT_RECEPTION_CTS0_EXIT
/** \brief Exit point of function J1939Tp_CMDT_Reception_CTS0() */
#define DBG_J1939TP_CMDT_RECEPTION_CTS0_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_CMDT_RECEPTION_DATA_COMPLETE_ENTRY
/** \brief Entry point of function J1939Tp_CMDT_Reception_Data_Complete() */
#define DBG_J1939TP_CMDT_RECEPTION_DATA_COMPLETE_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_CMDT_RECEPTION_DATA_COMPLETE_EXIT
/** \brief Exit point of function J1939Tp_CMDT_Reception_Data_Complete() */
#define DBG_J1939TP_CMDT_RECEPTION_DATA_COMPLETE_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_CMDT_RECEPTION_COPYRXDATA_ENTRY
/** \brief Entry point of function J1939Tp_CMDT_Reception_CopyRxData() */
#define DBG_J1939TP_CMDT_RECEPTION_COPYRXDATA_ENTRY(a,b,c,d)
#endif

#ifndef DBG_J1939TP_CMDT_RECEPTION_COPYRXDATA_EXIT
/** \brief Exit point of function J1939Tp_CMDT_Reception_CopyRxData() */
#define DBG_J1939TP_CMDT_RECEPTION_COPYRXDATA_EXIT(a,b,c,d)
#endif

#ifndef DBG_J1939TP_BAM_RECEPTION_COPYRXDATA_ENTRY
/** \brief Entry point of function J1939Tp_BAM_Reception_CopyRxData() */
#define DBG_J1939TP_BAM_RECEPTION_COPYRXDATA_ENTRY(a,b,c,d)
#endif

#ifndef DBG_J1939TP_BAM_RECEPTION_COPYRXDATA_EXIT
/** \brief Exit point of function J1939Tp_BAM_Reception_CopyRxData() */
#define DBG_J1939TP_BAM_RECEPTION_COPYRXDATA_EXIT(a,b,c,d)
#endif

#ifndef DBG_J1939TP_CMDT_TRANSMIT_RTS_ENTRY
/** \brief Entry point of function J1939Tp_CMDT_Transmit_RTS() */
#define DBG_J1939TP_CMDT_TRANSMIT_RTS_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_CMDT_TRANSMIT_RTS_EXIT
/** \brief Exit point of function J1939Tp_CMDT_Transmit_RTS() */
#define DBG_J1939TP_CMDT_TRANSMIT_RTS_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_CMDT_BUILD_RTS_ENTRY
/** \brief Entry point of function J1939Tp_CMDT_Build_RTS() */
#define DBG_J1939TP_CMDT_BUILD_RTS_ENTRY(a,b,c,d)
#endif

#ifndef DBG_J1939TP_CMDT_BUILD_RTS_EXIT
/** \brief Exit point of function J1939Tp_CMDT_Build_RTS() */
#define DBG_J1939TP_CMDT_BUILD_RTS_EXIT(a,b,c,d)
#endif

#ifndef DBG_J1939TP_CMDT_WAIT_EOMS_ENTRY
/** \brief Entry point of function J1939Tp_CMDT_Wait_EOMS() */
#define DBG_J1939TP_CMDT_WAIT_EOMS_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_CMDT_WAIT_EOMS_EXIT
/** \brief Exit point of function J1939Tp_CMDT_Wait_EOMS() */
#define DBG_J1939TP_CMDT_WAIT_EOMS_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_CMDT_RECEPTION_CTS_ENTRY
/** \brief Entry point of function J1939Tp_CMDT_Reception_CTS() */
#define DBG_J1939TP_CMDT_RECEPTION_CTS_ENTRY(a,b,c,d)
#endif

#ifndef DBG_J1939TP_CMDT_RECEPTION_CTS_EXIT
/** \brief Exit point of function J1939Tp_CMDT_Reception_CTS() */
#define DBG_J1939TP_CMDT_RECEPTION_CTS_EXIT(a,b,c,d)
#endif

#ifndef DBG_J1939TP_CMDT_RECEPTION_CTS_DATA_ENTRY
/** \brief Entry point of function J1939Tp_CMDT_Reception_CTS_Data() */
#define DBG_J1939TP_CMDT_RECEPTION_CTS_DATA_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_J1939TP_CMDT_RECEPTION_CTS_DATA_EXIT
/** \brief Exit point of function J1939Tp_CMDT_Reception_CTS_Data() */
#define DBG_J1939TP_CMDT_RECEPTION_CTS_DATA_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_J1939TP_CMDT_WAIT_DATA_ENTRY
/** \brief Entry point of function J1939Tp_CMDT_Wait_Data() */
#define DBG_J1939TP_CMDT_WAIT_DATA_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_CMDT_WAIT_DATA_EXIT
/** \brief Exit point of function J1939Tp_CMDT_Wait_Data() */
#define DBG_J1939TP_CMDT_WAIT_DATA_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_CMDT_TRANSMIT_SEND_ABORT_ENTRY
/** \brief Entry point of function J1939Tp_CMDT_Transmit_Send_Abort() */
#define DBG_J1939TP_CMDT_TRANSMIT_SEND_ABORT_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_CMDT_TRANSMIT_SEND_ABORT_EXIT
/** \brief Exit point of function J1939Tp_CMDT_Transmit_Send_Abort() */
#define DBG_J1939TP_CMDT_TRANSMIT_SEND_ABORT_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_BAM_TRANSMIT_SEND_ABORT_ENTRY
/** \brief Entry point of function J1939Tp_BAM_Transmit_Send_Abort() */
#define DBG_J1939TP_BAM_TRANSMIT_SEND_ABORT_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_BAM_TRANSMIT_SEND_ABORT_EXIT
/** \brief Exit point of function J1939Tp_BAM_Transmit_Send_Abort() */
#define DBG_J1939TP_BAM_TRANSMIT_SEND_ABORT_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_CMDT_RECEPTION_SEND_ABORT_ENTRY
/** \brief Entry point of function J1939Tp_CMDT_Reception_Send_Abort() */
#define DBG_J1939TP_CMDT_RECEPTION_SEND_ABORT_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_CMDT_RECEPTION_SEND_ABORT_EXIT
/** \brief Exit point of function J1939Tp_CMDT_Reception_Send_Abort() */
#define DBG_J1939TP_CMDT_RECEPTION_SEND_ABORT_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_CALCULATE_MAXPACKETSPERBLOCK_ENTRY
/** \brief Entry point of function J1939Tp_Calculate_MaxPacketsPerBlock() */
#define DBG_J1939TP_CALCULATE_MAXPACKETSPERBLOCK_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_J1939TP_CALCULATE_MAXPACKETSPERBLOCK_EXIT
/** \brief Exit point of function J1939Tp_Calculate_MaxPacketsPerBlock() */
#define DBG_J1939TP_CALCULATE_MAXPACKETSPERBLOCK_EXIT(a,b,c,d,e,f)
#endif

#ifndef DBG_J1939Tp_CMDT_Reception_RTS_ENTRY
/** \brief Entry point of function J1939Tp_CMDT_Reception_RTS() */
#define DBG_J1939Tp_CMDT_Reception_RTS_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939Tp_CMDT_Reception_RTS_EXIT
/** \brief Exit point of function J1939Tp_CMDT_Reception_RTS() */
#define DBG_J1939Tp_CMDT_Reception_RTS_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_BAM_TRANSMIT_DATA_ENTRY
/** \brief Entry point of function J1939Tp_BAM_Transmit_Data() */
#define DBG_J1939TP_BAM_TRANSMIT_DATA_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_BAM_TRANSMIT_DATA_EXIT
/** \brief Exit point of function J1939Tp_BAM_Transmit_Data() */
#define DBG_J1939TP_BAM_TRANSMIT_DATA_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_BAM_TRANSMIT_FD_DATA_ENTRY
/** \brief Entry point of function J1939Tp_BAM_Transmit_FD_Data() */
#define DBG_J1939TP_BAM_TRANSMIT_FD_DATA_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_BAM_TRANSMIT_FD_DATA_EXIT
/** \brief Exit point of function J1939Tp_BAM_Transmit_FD_Data() */
#define DBG_J1939TP_BAM_TRANSMIT_FD_DATA_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_CMDT_TRANSMIT_DATA_TIMEOUT_ENTRY
/** \brief Entry point of function J1939Tp_CMDT_Transmit_Data_Timeout() */
#define DBG_J1939TP_CMDT_TRANSMIT_DATA_TIMEOUT_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_CMDT_TRANSMIT_DATA_TIMEOUT_EXIT
/** \brief Exit point of function J1939Tp_CMDT_Transmit_Data_Timeout() */
#define DBG_J1939TP_CMDT_TRANSMIT_DATA_TIMEOUT_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_BAM_TRANSMIT_DATA_TIMEOUT_ENTRY
/** \brief Entry point of function J1939Tp_BAM_Transmit_Data_Timeout() */
#define DBG_J1939TP_BAM_TRANSMIT_DATA_TIMEOUT_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_BAM_TRANSMIT_DATA_TIMEOUT_EXIT
/** \brief Exit point of function J1939Tp_BAM_Transmit_Data_Timeout() */
#define DBG_J1939TP_BAM_TRANSMIT_DATA_TIMEOUT_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_TX_STORE_METADATA_ENTRY
/** \brief Entry point of function J1939Tp_Tx_Store_MetaData() */
#define DBG_J1939TP_TX_STORE_METADATA_ENTRY(a,b,c,d)
#endif

#ifndef DBG_J1939TP_TX_STORE_METADATA_EXIT
/** \brief Exit point of function J1939Tp_Tx_Store_MetaData() */
#define DBG_J1939TP_TX_STORE_METADATA_EXIT(a,b,c,d)
#endif

#ifndef DBG_J1939TP_TRANSMIT_INTERNAL_ENTRY
/** \brief Entry point of function J1939Tp_Transmit_Internal() */
#define DBG_J1939TP_TRANSMIT_INTERNAL_ENTRY(a,b,c,d,e,f,g)
#endif

#ifndef DBG_J1939TP_TRANSMIT_INTERNAL_EXIT
/** \brief Exit point of function J1939Tp_Transmit_Internal() */
#define DBG_J1939TP_TRANSMIT_INTERNAL_EXIT(a,b,c,d,e,f,g)
#endif

#ifndef DBG_J1939TP_ABORT_FRAME_BUILD_ENTRY
/** \brief Entry point of function J1939_AbortFrame_Build() */
#define DBG_J1939TP_ABORT_FRAME_BUILD_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_J1939TP_ABORT_FRAME_BUILD_EXIT
/** \brief Exit point of function J1939_AbortFrame_Build() */
#define DBG_J1939TP_ABORT_FRAME_BUILD_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_J1939TP_RX_CHANNEL_PG_SERAILIZATION_ENTRY
/** \brief ENTRY point of function J1939Tp_RxChannelPgSerialization() */
#define DBG_J1939TP_RX_CHANNEL_PG_SERAILIZATION_ENTRY(a)
#endif

#ifndef DBG_J1939TP_RX_CHANNEL_PG_SERAILIZATION_EXIT
/** \brief Exit point of function J1939Tp_RxChannelPgSerialization() */
#define DBG_J1939TP_RX_CHANNEL_PG_SERAILIZATION_EXIT(a)
#endif

#ifndef DBG_J1939TP_TX_CHANNEL_PG_SERAILIZATION_ENTRY
/** \brief ENTRY point of function J1939Tp_TxChannelPgSerialization() */
#define DBG_J1939TP_TX_CHANNEL_PG_SERAILIZATION_ENTRY(a)
#endif

#ifndef DBG_J1939TP_TX_CHANNEL_PG_SERAILIZATION_EXIT
/** \brief Exit point of function J1939Tp_TxChannelPgSerialization() */
#define DBG_J1939TP_TX_CHANNEL_PG_SERAILIZATION_EXIT(a)
#endif

#ifndef DBG_J1939TP_TX_PG_NSDU_SERAILIZATION_ENTRY
/** \brief ENTRY point of function J1939Tp_TxPgNsduSerialization() */
#define DBG_J1939TP_TX_PG_NSDU_SERAILIZATION_ENTRY(a,b)
#endif

#ifndef DBG_J1939TP_TX_PG_NSDU_SERAILIZATION_EXIT
/** \brief Exit point of function J1939Tp_TxPgNsduSerialization() */
#define DBG_J1939TP_TX_PG_NSDU_SERAILIZATION_EXIT(a,b)
#endif

#ifndef DBG_J1939TP_RX_PG_NSDU_SERAILIZATION_ENTRY
/** \brief ENTRY point of function J1939Tp_RxPgNsduSerialization() */
#define DBG_J1939TP_RX_PG_NSDU_SERAILIZATION_ENTRY(a,b)
#endif

#ifndef DBG_J1939TP_RX_PG_NSDU_SERAILIZATION_EXIT
/** \brief Exit point of function J1939Tp_RxPgNsduSerialization() */
#define DBG_J1939TP_RX_PG_NSDU_SERAILIZATION_EXIT(a,b)
#endif

#ifndef DBG_J1939TP_BAM_NSDU_WAIT_CONFIRMATION_HANDLING_ENTRY
/** \brief ENTRY point of function J1939Tp_BAM_NsduTxWaitConfirmationHandling() */
#define DBG_J1939TP_BAM_NSDU_WAIT_CONFIRMATION_HANDLING_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_BAM_NSDU_WAIT_CONFIRMATION_HANDLING_EXIT
/** \brief Exit point of function J1939Tp_BAM_NsduTxWaitConfirmationHandling() */
#define DBG_J1939TP_BAM_NSDU_WAIT_CONFIRMATION_HANDLING_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_BAM_CANCELATION_HANDLE_ENTRY
/** \brief ENTRY point of function J1939Tp_BAM_CancelationHandle() */
#define DBG_J1939TP_BAM_CANCELATION_HANDLE_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_BAM_CANCELATION_HANDLE_EXIT
/** \brief Exit point of function J1939Tp_BAM_CancelationHandle() */
#define DBG_J1939TP_BAM_CANCELATION_HANDLE_EXIT(a,b,c)
#endif

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[external data]=========================================*/

#endif /* ifndef J1939TP_TRACE_INTERNAL_H */
/*==================[end of file]===========================================*/
