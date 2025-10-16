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
#ifndef J1939TP_TRACE_H
#define J1939TP_TRACE_H

/*==================[inclusions]============================================*/


#include <Std_Types.h>

/* Check if BASE_DBG_ENABLE is defined and set to STD_ON.
 * If so, include Base_Dbg.h which includes a custom header file */
#if (defined BASE_DBG_ENABLE)
#if (BASE_DBG_ENABLE == STD_ON)

#include <Base_Dbg.h>

#endif
#endif
#include <J1939Tp_Trace_Internal.h>
/*==================[macros]================================================*/

#ifndef DBG_J1939TP_MAINFUNCTION_ENTRY
/** \brief Entry point of function J1939Tp_MainFunction() */
#define DBG_J1939TP_MAINFUNCTION_ENTRY()
#endif

#ifndef DBG_J1939TP_MAINFUNCTION_EXIT
/** \brief Exit point of function J1939Tp_MainFunction() */
#define DBG_J1939TP_MAINFUNCTION_EXIT()
#endif

#ifndef DBG_J1939TP_GETVERSIONINFO_ENTRY
/** \brief Entry point of function J1939Tp_GetVersionInfo() */
#define DBG_J1939TP_GETVERSIONINFO_ENTRY(a)
#endif

#ifndef DBG_J1939TP_GETVERSIONINFO_EXIT
/** \brief Exit point of function J1939Tp_GetVersionInfo() */
#define DBG_J1939TP_GETVERSIONINFO_EXIT(a)
#endif

#ifndef DBG_J1939TP_INIT_ENTRY
/** \brief Entry point of function J1939Tp_Init() */
#define DBG_J1939TP_INIT_ENTRY(a)
#endif

#ifndef DBG_J1939TP_INIT_EXIT
/** \brief Exit point of function J1939Tp_Init() */
#define DBG_J1939TP_INIT_EXIT(a)
#endif

#ifndef DBG_J1939TP_SHUTDOWN_ENTRY
/** \brief Entry point of function J1939Tp_Shutdown() */
#define DBG_J1939TP_SHUTDOWN_ENTRY()
#endif

#ifndef DBG_J1939TP_SHUTDOWN_EXIT
/** \brief Exit point of function J1939Tp_Shutdown() */
#define DBG_J1939TP_SHUTDOWN_EXIT()
#endif

#ifndef DBG_J1939TP_TRANSMIT_ENTRY
/** \brief Entry point of function J1939Tp_Transmit() */
#define DBG_J1939TP_TRANSMIT_ENTRY(a,b)
#endif

#ifndef DBG_J1939TP_TRANSMIT_EXIT
/** \brief Exit point of function J1939Tp_Transmit() */
#define DBG_J1939TP_TRANSMIT_EXIT(a,b,c)
#endif

#ifndef DBG_J1939TP_CANCELTRANSMIT_ENTRY
/** \brief Entry point of function J1939Tp_CancelTransmit() */
#define DBG_J1939TP_CANCELTRANSMIT_ENTRY(a)
#endif

#ifndef DBG_J1939TP_CANCELTRANSMIT_EXIT
/** \brief Exit point of function J1939Tp_CancelTransmit() */
#define DBG_J1939TP_CANCELTRANSMIT_EXIT(a,b)
#endif

#ifndef DBG_J1939TP_CANCELRECEIVE_ENTRY
/** \brief Entry point of function J1939Tp_CancelReceive() */
#define DBG_J1939TP_CANCELRECEIVE_ENTRY(a)
#endif

#ifndef DBG_J1939TP_CANCELRECEIVE_EXIT
/** \brief Exit point of function J1939Tp_CancelReceive() */
#define DBG_J1939TP_CANCELRECEIVE_EXIT(a,b)
#endif

#ifndef DBG_J1939TP_CHANGEPARAMETER_ENTRY
/** \brief Entry point of function J1939Tp_ChangeParameter() */
#define DBG_J1939TP_CHANGEPARAMETER_ENTRY(a,b,c)
#endif

#ifndef DBG_J1939TP_CHANGEPARAMETER_EXIT
/** \brief Exit point of function J1939Tp_ChangeParameter() */
#define DBG_J1939TP_CHANGEPARAMETER_EXIT(a,b,c,d)
#endif

#ifndef DBG_J1939TP_TXCONFIRMATION_ENTRY
/** \brief Entry point of function J1939Tp_TxConfirmation() */
#define DBG_J1939TP_TXCONFIRMATION_ENTRY(a,b)
#endif

#ifndef DBG_J1939TP_TXCONFIRMATION_EXIT
/** \brief Exit point of function J1939Tp_TxConfirmation() */
#define DBG_J1939TP_TXCONFIRMATION_EXIT(a,b)
#endif

#ifndef DBG_J1939TP_RXINDICATION_ENTRY
/** \brief Entry point of function J1939Tp_RxIndication() */
#define DBG_J1939TP_RXINDICATION_ENTRY(a,b)
#endif

#ifndef DBG_J1939TP_RXINDICATION_EXIT
/** \brief Exit point of function J1939Tp_RxIndication() */
#define DBG_J1939TP_RXINDICATION_EXIT(a,b)
#endif

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[external data]=========================================*/

#endif /* ifndef J1939TP_TRACE_H */
/*==================[end of file]===========================================*/
