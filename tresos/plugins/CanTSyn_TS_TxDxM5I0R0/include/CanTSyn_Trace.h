/**
 * \file
 *
 * \brief AUTOSAR CanTSyn
 *
 * This file contains the implementation of the AUTOSAR
 * module CanTSyn.
 *
 * \version 5.0.5
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef CANTSYN_TRACE_H
#define CANTSYN_TRACE_H


/*==================[macros]================================================*/
/* ====== CanTSyn public APIs ====== */

#ifndef DBG_CANTSYN_GETVERSIONINFO_ENTRY
/** \brief Entry point of function CanTSyn_GetVersionInfo() */
#define DBG_CANTSYN_GETVERSIONINFO_ENTRY(a)
#endif

#ifndef DBG_CANTSYN_GETVERSIONINFO_EXIT
/** \brief Exit point of function CanTSyn_GetVersionInfo() */
#define DBG_CANTSYN_GETVERSIONINFO_EXIT(a)
#endif

#ifndef DBG_CANTSYN_INIT_ENTRY
/** \brief Entry point of function CanTSyn_Init() */
#define DBG_CANTSYN_INIT_ENTRY(a)
#endif

#ifndef DBG_CANTSYN_INIT_EXIT
/** \brief Exit point of function CanTSyn_Init() */
#define DBG_CANTSYN_INIT_EXIT(a)
#endif


#ifndef DBG_CANTSYN_MAINFUNCTION_ENTRY
/** \brief Entry point of function CanTSyn_MainFunction() */
#define DBG_CANTSYN_MAINFUNCTION_ENTRY()
#endif

#ifndef DBG_CANTSYN_MAINFUNCTION_EXIT
/** \brief Exit point of function CanTSyn_MainFunction() */
#define DBG_CANTSYN_MAINFUNCTION_EXIT()
#endif


#ifndef DBG_CANTSYN_MAINFUNCTION_TX_ENTRY
/** \brief Entry point of function CanTSyn_MainFunction_Tx() */
#define DBG_CANTSYN_MAINFUNCTION_TX_ENTRY(a)
#endif

#ifndef DBG_CANTSYN_MAINFUNCTION_TX_EXIT
/** \brief Exit point of function CanTSyn_MainFunction_Tx() */
#define DBG_CANTSYN_MAINFUNCTION_TX_EXIT(a)
#endif


#ifndef DBG_CANTSYN_MAINFUNCTION_RX_ENTRY
/** \brief Entry point of function CanTSyn_MainFunction_Rx() */
#define DBG_CANTSYN_MAINFUNCTION_RX_ENTRY(a)
#endif

#ifndef DBG_CANTSYN_MAINFUNCTION_RX_EXIT
/** \brief Exit point of function CanTSyn_MainFunction_Rx() */
#define DBG_CANTSYN_MAINFUNCTION_RX_EXIT(a)
#endif


#ifndef DBG_CANTSYN_SETTRANSMISSIONMODE_ENTRY
/** \brief Entry point of function CanTSyn_SetTransmissionMode() */
#define DBG_CANTSYN_SETTRANSMISSIONMODE_ENTRY(a,b)
#endif

#ifndef DBG_CANTSYN_SETTRANSMISSIONMODE_EXIT
/** \brief Exit point of function CanTSyn_SetTransmissionMode() */
#define DBG_CANTSYN_SETTRANSMISSIONMODE_EXIT(a,b)
#endif

#ifndef DBG_CANTSYN_RXINDICATION_ENTRY
/** \brief Entry point of function CanTSyn_RxIndication() */
#define DBG_CANTSYN_RXINDICATION_ENTRY(a,b)
#endif

#ifndef DBG_CANTSYN_RXINDICATION_EXIT
/** \brief Exit point of function CanTSyn_RxIndication() */
#define DBG_CANTSYN_RXINDICATION_EXIT(a,b)
#endif

#if(CANTSYN_RELIABLE_TXCONF == STD_OFF)

#ifndef DBG_CANTSYN_TXCONFIRMATION_ENTRY
/** \brief Entry point of function CanTSyn_TxConfirmation() */
#define DBG_CANTSYN_TXCONFIRMATION_ENTRY(a)
#endif

#ifndef DBG_CANTSYN_TXCONFIRMATION_EXIT
/** \brief Exit point of function CanTSyn_TxConfirmation() */
#define DBG_CANTSYN_TXCONFIRMATION_EXIT(a)
#endif

#else

#ifndef DBG_CANTSYN_TXCONFIRMATION_ENTRY
/** \brief Entry point of function CanTSyn_TxConfirmation() */
#define DBG_CANTSYN_TXCONFIRMATION_ENTRY(a,b)
#endif

#ifndef DBG_CANTSYN_TXCONFIRMATION_EXIT
/** \brief Exit point of function CanTSyn_TxConfirmation() */
#define DBG_CANTSYN_TXCONFIRMATION_EXIT(a,b)
#endif

#endif /* CANTSYN_RELIABLE_TXCONF == STD_OFF */

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/


#endif /* ifndef CANTSYN_TRACE_H */


