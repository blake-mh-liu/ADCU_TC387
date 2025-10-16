/**
 * \file
 *
 * \brief AUTOSAR J1939Nm
 *
 * This file contains the implementation of the AUTOSAR
 * module J1939Nm.
 *
 * \version 1.1.13
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef J1939NM_CBK_H
#define J1939NM_CBK_H

#include <J1939Nm_Cfg.h>
/* !LINKSTO EB_Ref.SWS_J1939Nm_00001.2,1*/
#include <J1939Nm_Types.h>
/* A J1939Nm implementation shall provide a header file J1939Nm_Cbk.h that contains function
 * declarations for the callback functions in the J1939Nm
 */

/*-----------------------------------------------------------------------------
 * Callback notification
 *-----------------------------------------------------------------------------*/

#define J1939NM_START_SEC_CODE
#include <J1939Nm_MemMap.h>

/* ************************************************************
 *  Name                 : J1939Nm_RxIndication
 *  Description          : Indication of a received I-PDU from a lower
 *               layer communication interface module.
 *  Parameters           : Input: PduIdType RxPduId
 *             : Input: PduInfoType* PduInfoPtr
 *  Return               : none
 *  Critical/explanation : [No]
 **************************************************************/
extern FUNC(void,J1939NM_CODE) J1939Nm_RxIndication(
    VAR(PduIdType, AUTOMATIC)  RxPduId,
    P2VAR(PduInfoType, AUTOMATIC, J1939NM_APPL_DATA) PduInfoPtr
);

/* ************************************************************
 *  Name                 : J1939Nm_TxConfirmation
 *  Description          : The lower layer communication interface module
 *               confirms the transmission of an I-PDU.
 *  Parameters           : Input: PduIdType TxPduId
 *  Return               : none
 *  Critical/explanation : [No]
 **************************************************************/
extern FUNC(void,J1939NM_CODE) J1939Nm_TxConfirmation(
    VAR(PduIdType, AUTOMATIC) TxPduId, VAR(Std_ReturnType, AUTOMATIC) result
);

/* ************************************************************
 *  Name                 : J1939Nm_RequestIndication
 *  Description          : Indicates reception of a Request PG.
 *
 *  Parameters           : Input: uint8 node
 *             : Input: NetworkHandleType channel
 *             : Input: uint32 requestPgn
 *             : Input: uint8 sourceAddress
 *             : Input: uint8 destAddress
 *             : Input: uint8 priority
 *  Return               : none
 *  Critical/explanation : [No]
 **************************************************************/
extern FUNC(void,J1939NM_CODE) J1939Nm_RequestIndication(
  VAR(uint8, AUTOMATIC) node,
  VAR(NetworkHandleType, AUTOMATIC) channel,
  VAR(uint32, AUTOMATIC) requestedPgn,
  VAR(uint8, AUTOMATIC) sourceAddress,
  VAR(uint8, AUTOMATIC) destAddress,
  VAR(uint8, AUTOMATIC) priority
);

#define J1939NM_STOP_SEC_CODE
#include <J1939Nm_MemMap.h>

#endif /* J1939NM_CBK_H */


