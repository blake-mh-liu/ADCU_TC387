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

#ifndef J1939RM_H
#define J1939RM_H

/* !LINKSTO J1939Rm.ASR41.SWS_J1939Rm_00001,1 */
#include <J1939Rm_Cfg.h>
#include <J1939Rm_Version.h>

#ifndef J1939RM_NO_PBCFG_REQUIRED
#if (J1939RM_PBCFGM_SUPPORT_ENABLED == STD_OFF)
#include <J1939Rm_PBcfg.h>     /* post build configuration of J1939Rm */
#endif /* J1939RM_PBCFGM_SUPPORT_ENABLED == STD_OFF */
#endif /* J1939RM_NO_PBCFG_REQUIRED */
#include <J1939Rm_Api.h>
#if (J1939RM_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>
#endif

/*  NULL Source address **/
#define J1939RM_NULL_ADDRESS       (0xFEu)

#define J1939RM_E_INIT_FAILED 0x03u
#define RX_SA_BYTE        (3u)
#define RX_DA_BYTE        (4u)
#define RX_PRIO_BYTE      (6u)
#define TX_SA_BYTE        (0u)
#define TX_DA_BYTE        (1u)
#define TX_PRIO_BYTE      (3u)


/* Service ID's */
#if (defined J1939RM_INIT)
#error J1939RM_INIT already defined
#endif
#define J1939RM_INIT                  0x01u

#if (defined J1939RM_DEINIT)
#error J1939RM_DEINIT already defined
#endif
#define J1939RM_DEINIT                0x02u

#if (defined J1939RM_GETVERSIONINFO)
#error J1939RM_GETVERSIONINFO already defined
#endif
#define J1939RM_GETVERSIONINFO        0x03u

#if (defined J1939RM_SETSTATE)
#error J1939RM_SETSTATE already defined
#endif
#define J1939RM_SETSTATE              0x05u

#if (defined J1939RM_TRANSMIT)
#error J1939RM_TRANSMIT already defined
#endif
#define J1939RM_TRANSMIT              0x06u

#if (defined J1939RM_SENDREQUEST)
#error J1939RM_SENDREQUEST already defined
#endif
#define J1939RM_SENDREQUEST           0x07u

#if (defined J1939RM_CANCELREQUESTTIMEOUT)
#error J1939RM_CANCELREQUESTTIMEOUT already defined
#endif
#define J1939RM_CANCELREQUESTTIMEOUT  0x08u

#if (defined J1939RM_SENDACK)
#error J1939RM_SENDACK already defined
#endif
#define J1939RM_SENDACK               0x09u

#if (defined J1939RM_RXINDICATION)
#error J1939RM_RXINDICATION already defined
#endif
#define J1939RM_RXINDICATION          0x42u

#if (defined J1939RM_TXCONFIRMATION)
#error J1939RM_TXCONFIRMATION already defined
#endif
#define J1939RM_TXCONFIRMATION        0x40u

#if (defined J1939RM_COPYTXDATA)
#error J1939RM_COPYTXDATA already defined
#endif
#define J1939RM_COPYTXDATA            0x43u

#if (defined J1939RM_TPTXCONFIRMATION)
#error J1939RM_TPTXCONFIRMATION already defined
#endif
#define J1939RM_TPTXCONFIRMATION      0x37u

#if (defined J1939RM_COMRXIPDUCALLOUT)
#error J1939RM_COMRXIPDUCALLOUT already defined
#endif
#define J1939RM_COMRXIPDUCALLOUT      0x28u

#if (defined J1939RM_MAINFUNCTION)
#error J1939RM_MAINFUNCTION already defined
#endif
#define J1939RM_MAINFUNCTION          0x04u

#if (defined J1939RM_PGN_MAX)
#error J1939RM_PGN_MAX already defined
#endif
#define J1939RM_PGN_MAX          262143u



/** \brief Definition of DET error code J1939RM_E_INVALID_CALL */
#if (defined J1939RM_E_INVALID_CALL)
#error J1939RM_E_INVALID_CALL already defined!
#endif /* #if (defined J1939RM_E_INVALID_CALL)*/
#define J1939RM_E_INVALID_CALL 0xFF /** Invalid call for this dummy function */

/* Public Operations */

#define J1939RM_START_SEC_CODE
#include <J1939Rm_MemMap.h>

extern FUNC(void, J1939RM_CODE) J1939Rm_Init(P2CONST(J1939Rm_ConfigType, AUTOMATIC, J1939RM_APPL_CONST) ConfigPtr);

extern FUNC(void, J1939RM_CODE) J1939Rm_DeInit(void);

extern FUNC(void, J1939RM_CODE) J1939Rm_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, J1939RM_APPL_DATA) versionInfo);

extern FUNC(Std_ReturnType, J1939RM_CODE) J1939Rm_SetState(NetworkHandleType channel, uint8 node, J1939Rm_StateType newState);

extern FUNC(Std_ReturnType, J1939RM_CODE) J1939Rm_Transmit(PduIdType id, P2CONST(PduInfoType, AUTOMATIC, J1939RM_APPL_CONST) info);

#ifndef J1939RM_RTE_SEND_REQUEST
#if (J1939RM_SENDREQUEST_SUPPORT == STD_ON)
extern FUNC(Std_ReturnType, J1939RM_CODE) J1939Rm_SendRequest(uint8 userId, NetworkHandleType channel, uint32 requestedPgn, uint8 destAddress, uint8 priority, boolean checkTimeout);
#endif
#endif

extern FUNC(void, J1939RM_CODE) J1939Rm_CancelRequestTimeout(uint8 userId, NetworkHandleType channel, uint32 requestedPgn, uint8 destAddress);

#ifndef J1939RM_RTE_SEND_ACK
extern FUNC(Std_ReturnType, J1939RM_CODE) J1939Rm_SendAck(uint8 userId, NetworkHandleType channel, uint32 ackPgn, J1939Rm_AckCode ackCode, uint8 ackAddress, uint8 priority);
#endif

extern FUNC(void, J1939RM_CODE) J1939Rm_MainFunction(void);

#ifndef J1939RM_RTE_CANCEL_REQUEST_TIMEOUT
extern FUNC(Std_ReturnType, J1939RM_CODE) J1939Rm_CancelRequestTimeout_Operation (uint8 UserId, NetworkHandleType channel, uint32 requestedPgn, uint8 destAddress);
#endif


/*These functions were added due to EB PduR limitation*/

/**
 * \brief Dummy funtion for PduR.
 *
 * This function shall not be called, and if so it shall report developement error.
 *
 * \ServiceID{0xFB}
 */
extern FUNC(BufReq_ReturnType, J1939RM_CODE) J1939Rm_PduRTpCopyRxData (PduIdType PduId,P2CONST(PduInfoType, AUTOMATIC, J1939RM_APPL_CONST) PduInfoPointer, P2VAR(PduLengthType, AUTOMATIC, J1939RM_APPL_DATA) RxBufferSizePtr);

/**
 * \brief Dummy funtion for PduR.
 *
 * This function shall not be called, and if so it shall report developement error.
 *
 * \ServiceID{0xFA}
 */
extern FUNC(void, J1939RM_CODE) J1939Rm_PduRTpRxIndication (PduIdType RxPduId, NotifResultType Result);

/**
 * \brief Dummy funtion for PduR.
 *
 * This function shall not be called, and if so it shall report developement error.
 *
 * \ServiceID{0xFC}
 */
extern FUNC(BufReq_ReturnType, J1939RM_CODE) J1939Rm_PduRTpStartOfReception ( PduIdType PduId, PduLengthType PduLength, P2VAR(PduLengthType, AUTOMATIC, J1939RM_APPL_DATA) RxBufferSizePtr);


#define J1939RM_STOP_SEC_CODE
#include <J1939Rm_MemMap.h>

#endif /* J1939RM_H */
/*==================[end of file]============================================*/
