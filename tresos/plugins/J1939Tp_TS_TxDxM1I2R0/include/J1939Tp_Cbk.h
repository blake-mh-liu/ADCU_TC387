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

#ifndef J1939TP_CBK_H                                /* To avoid double inclusion */
#define J1939TP_CBK_H

/*==============================================================================*/
/* Include Files Section                                                        */
/*==============================================================================*/
#include <J1939Tp_Typedefs.h>
#include <J1939Tp_Cfg.h>

/*=========== Exported functions prototypes=====================================*/
#define J1939TP_START_SEC_CODE
#include <J1939Tp_MemMap.h>

/* Indication of a received I-PDU from a lower layer communication interface module. */
extern FUNC(void, J1939TP_CODE) J1939Tp_RxIndication(PduIdType RxPduId, P2VAR(PduInfoType, AUTOMATIC, J1939TP_APPL_DATA) PduInfoPtr);

/* The lower layer communication interface module confirms the transmission of an I-PDU. */
#if (J1939TP_RELIABLE_TXCONFIRMATION == STD_ON)
extern FUNC(void, J1939TP_CODE) J1939Tp_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);
#else
extern FUNC(void, J1939TP_CODE) J1939Tp_TxConfirmation(PduIdType TxPduId);
#endif

#define J1939TP_STOP_SEC_CODE
#include <J1939Tp_MemMap.h>

#endif
/*==================[end of file]============================================*/
