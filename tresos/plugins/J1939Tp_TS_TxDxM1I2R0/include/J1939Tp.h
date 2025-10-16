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

#ifndef J1939TP_H                                /* To avoid double inclusion */
#define J1939TP_H

/*==============================================================================*/
/* Include Files Section                                                        */
/*==============================================================================*/
#include <J1939Tp_Typedefs.h>
#include <J1939Tp_Cfg.h>
#include <EcuC.h>
#ifndef J1939TP_NO_PBCFG_REQUIRED
#if (J1939TP_PBCFGM_SUPPORT_ENABLED == STD_OFF)
#include <J1939Tp_PBcfg.h>     /* post build configuration of J1939Tp */
#endif /* J1939TP_PBCFGM_SUPPORT_ENABLED == STD_OFF */
#endif /* J1939TP_NO_PBCFG_REQUIRED */

#include <J1939Tp_Api.h>
/*====================== Det Error definition ==================================*/
#define J1939TP_E_UNINIT                  0x01U
#define J1939TP_E_REINIT                  0x02U
#define J1939TP_E_INIT_FAILED             0x03U
#define J1939TP_E_PARAM_POINTER           0x10U
#define J1939TP_E_INVALID_PDU_SDU_ID      0x11U
#define J1939TP_E_TIMEOUT_T1              0x30U
#define J1939TP_E_TIMEOUT_T2              0x31U
#define J1939TP_E_TIMEOUT_T3              0x32U
#define J1939TP_E_TIMEOUT_T4              0x33U
#define J1939TP_E_TIMEOUT_T5              0x51U
#define J1939TP_E_TIMEOUT_TR              0x34U
#define J1939TP_E_TIMEOUT_TH              0x35U
#define J1939TP_E_INVALID_TMS             0x40U
#define J1939TP_E_INVALID_TNOP            0x41U
#define J1939TP_E_INVALID_MNOP            0x42U
#define J1939TP_E_INVALID_PGN             0x43U
#define J1939TP_E_INVALID_NOP             0x44U
#define J1939TP_E_INVALID_NPN             0x45U
#define J1939TP_E_INVALID_CAR             0x46U
#define J1939TP_E_INVALID_SN              0x47U
#define J1939TP_E_INVALID_SDU_LENGTH      0x48U
#define J1939TP_E_INVALID_SESSION_NUMBER  0x49U
/*====================== API Service ID definition =============================*/
#define J1939TP_INIT_SERVICEID            0x01U
#define J1939TP_SHUTDOWN_SERVICEID        0x02U
#define J1939TP_GETVERSIONINFO_SERVICEID  0x03U
#define J1939TP_TRANSMIT_SERVICEID        0x49U
#define J1939TP_CANCELTRANSMIT_SERVICEID  0x4aU
#define J1939TP_CANCELRECEIVE_SERVICEID   0x4cU
#define J1939TP_CHANGEPARAMETER_SERVICEID 0x4bU
#define J1939TP_RXINDICATION_SERVICEID    0x42U
#define J1939TP_TXCONFIRMATION_SERVICEID  0x40U
#define J1939TP_MAINFUNCTION_SERVICEID    0x04U
/*======================Macro Section===========================================*/
#define METADATA_SA_BYTE_EIGHT 8u
#define METADATA_DA_BYTE_NINE 9u
#define METADATA_PGN_BYTE_TEN 10u
#define METADATA_PRIORITY_BYTE_ELEVEN 11u
#define METADATA_SA_INDEX_0 0U
#define METADATA_DA_INDEX_1 1U
#define METADATA_PGN_INDEX_2 2U
#define METADATA_PRIORITY_INDEX_3 3U
#define J1939TP_BUFFER_MAX_PERCENT (PduLengthType)100U
#define J1939TP_CANFD_DT_SESSION_NUMBER(FirstByte, Session_num) ((Session_num) = ((FirstByte) & 0x0FU))
#define J1939TP_VALID_DT_CANFD_FRAME(CtrlByte, ValidFrame) ((ValidFrame) = ((((CtrlByte) & 0xF0U) == 0U) ? TRUE : FALSE))
#define J1939TP_GET_FRAME_TYPE(CtrlByte, FrameType) ((FrameType) = ((CtrlByte) & (0x0FU)))
#define J1939TP_SET_SESSION_NUMBER(Session_num, Frame) ((Frame) = ((Session_num) & (0x0FU)))
#define J1939TP_GET_SESSION_NUMBER(CtrlByte, Session_num) ((Session_num) = (((CtrlByte) & 0xF0U) >> 4U))
#define J1939TP_CANID_EXTENDED(CanId) ((((CanId) & 0x80000000U) > 0U) ? TRUE : FALSE)
#define J1939TP_GET_PGN(PgnConfig, Pgn) ((Pgn) = (uint8)(((PgnConfig) & 0x00FF00U) >> 8U))
#define J1939TP_GET_GE(PgnConfig, GroupExtention) ((GroupExtention) = (uint8)((PgnConfig) & 0x0000FFU))
#define J1939TP_PGN_PDU_2(Pgn) ((Pgn >= 0xF0U) ? TRUE : FALSE)
#define J1939TP_GLOBAL_ADDRESS                                 0xFFU

/*=====================Functions Prototypes=====================================*/
#define J1939TP_START_SEC_CODE
#include <J1939Tp_MemMap.h>

/* Main function of the J1939Tp. Used for scheduling purposes and timeout
     supervision. */
extern FUNC(void, J1939TP_CODE) J1939Tp_MainFunction(void);

#if (J1939TP_VERSION_INFO_API == STD_ON)
/* Returns the version information of J1939Tp.*/
extern FUNC(void, J1939TP_CODE) J1939Tp_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, J1939TP_APPL_DATA) VersionInfo);
#endif /* J1939TP_VERSION_INFO_API == STD_ON */

/* This function initializes the J1939Tp module.*/
extern FUNC(void, J1939TP_CODE) J1939Tp_Init(P2CONST(J1939Tp_ConfigType,AUTOMATIC,J1939TP_APPL_CONST) ConfigPtr);


/* This function is used to shutdown the J1939Tp module. */
extern FUNC(void, J1939TP_CODE) J1939Tp_Shutdown(void);


/* This service function is used to request the transmission of a PDU.*/
extern FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_Transmit(PduIdType TxPduId, P2CONST(PduInfoType,AUTOMATIC,J1939TP_APPL_CONST) PduInfoPtr);


#if (J1939TP_CANCELLATION_SUPPORT == STD_ON)
/* This service function is used to cancel the ongoing transmission of a PDU in a
 * lower layer communication module.*/
extern FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_CancelTransmit(PduIdType TxPduId);


/* This service function is used to request cancellation of an ongoing reception of
 * a PDU in a lower layer transport protocol module. */
extern FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_CancelReceive(PduIdType RxPduId);
#endif /* J1939TP_CANCELLATION_SUPPORT == STD_ON */

/* This service function is used to change a specific transport protocol parameter. */
extern FUNC(Std_ReturnType, J1939TP_CODE) J1939Tp_ChangeParameter(PduIdType id, TPParameterType parameter, uint16 value);

#define J1939TP_STOP_SEC_CODE
#include <J1939Tp_MemMap.h>

#endif
/*==================[end of file]============================================*/
