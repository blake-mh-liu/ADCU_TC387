/**
 * \file
 *
 * \brief AUTOSAR J1939Rm
 *
 * This file contains the implementation of the AUTOSAR
 * module J1939Rm.
 *
 * \version 1.1.15
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef J1939RM_CBK_H
#define J1939RM_CBK_H

/* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00001,1 */
#include <J1939Rm_Cfg.h>
#include <TSAutosar.h>

/** \brief Defines Dummy API id of function J1939Rm_PduRTpStartOfReception(). */
#if (defined J1939RM_SID_PDURTPSTARTOFRECEPTION)
#error J1939RM_SID_PDURTPSTARTOFRECEPTION already defined!
#endif /* #if (defined J1939RM_SID_PDURTPSTARTOFRECEPTION)*/
#define J1939RM_SID_PDURTPSTARTOFRECEPTION 0xFC

/** \brief Defines Dummy API id of function J1939Rm_PduRTpCopyRxData(). */
#if (defined J1939RM_SID_PDURTPCOPYRXDATA)
#error J1939RM_SID_PDURTPCOPYRXDATA already defined!
#endif /* #if (defined J1939RM_SID_PDURTPCOPYRXDATA)*/
#define J1939RM_SID_PDURTPCOPYRXDATA 0xFB

/** \brief Defines Dummy API id of function J1939Rm_PduRTpRxIndication(). */
#if (defined J1939RM_SID_PDURTPRXINDICATION)
#error J1939RM_SID_PDURTPRXINDICATION already defined!
#endif /* #if (defined J1939RM_SID_PDURTPRXINDICATION)*/
#define J1939RM_SID_PDURTPRXINDICATION 0xFA

/* Callback Operations */

#define J1939RM_START_SEC_CODE
#include <J1939Rm_MemMap.h>

#if ((defined J1939RM_SUPPORT_REQUESTINDICATION) || (defined J1939RM_ACKINDICATION_SUPPORT))
extern FUNC(void, J1939RM_CODE) J1939Rm_RxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, J1939RM_APPL_CONST) PduInfoPtr);
#endif

extern FUNC(void, J1939RM_CODE) J1939Rm_TxConfirmation(PduIdType TxPduId);

extern FUNC(BufReq_ReturnType, J1939RM_CODE) J1939Rm_CopyTxData(PduIdType id, P2CONST(PduInfoType, AUTOMATIC, J1939RM_APPL_CONST) info, P2VAR(RetryInfoType, AUTOMATIC, J1939RM_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, J1939RM_APPL_DATA) availableDataPtr);

extern FUNC(void, J1939RM_CODE) J1939Rm_TpTxConfirmation(PduIdType id, Std_ReturnType result);

extern FUNC(boolean, J1939RM_CODE) J1939Rm_ComRxIpduCallout(PduIdType PduId, P2CONST(PduInfoType, AUTOMATIC, J1939RM_APPL_CONST) PduInfoPtr);





#define J1939RM_STOP_SEC_CODE
#include <J1939Rm_MemMap.h>

#endif /* J1939RM_CBK_H */

/*==================[end of file]============================================*/
