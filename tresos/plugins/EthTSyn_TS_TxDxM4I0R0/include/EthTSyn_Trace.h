/**
 * \file
 *
 * \brief AUTOSAR EthTSyn
 *
 * This file contains the implementation of the AUTOSAR
 * module EthTSyn.
 *
 * \version 4.0.10
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#ifndef ETHTSYN_TRACE_H
#define ETHTSYN_TRACE_H
/*==================[inclusions]============================================*/

#include <Std_Types.h> /* AUTOSAR standard types */

/*==================[macros]================================================*/

/* ====== EthTSyn public APIs ====== */
#ifndef DBG_ETHTSYN_INIT_ENTRY
/** \brief Entry point of function EthTSyn_Init() */
#define DBG_ETHTSYN_INIT_ENTRY(a)
#endif

#ifndef DBG_ETHTSYN_INIT_EXIT
/** \brief Exit point of function EthTSyn_Init() */
#define DBG_ETHTSYN_INIT_EXIT(a)
#endif

#ifndef DBG_ETHTSYN_MAINFUNCTION_ENTRY
/** \brief Entry point of function EthTSyn_MainFunction() */
#define DBG_ETHTSYN_MAINFUNCTION_ENTRY()
#endif

#ifndef DBG_ETHTSYN_MAINFUNCTION_EXIT
/** \brief Exit point of function EthTSyn_MainFunction() */
#define DBG_ETHTSYN_MAINFUNCTION_EXIT()
#endif

#ifndef DBG_ETHTSYN_GETVERSIONINFO_ENTRY
/** \brief Entry point of function EthTSyn_GetVersionInfo() */
#define DBG_ETHTSYN_GETVERSIONINFO_ENTRY(a)
#endif

#ifndef DBG_ETHTSYN_GETVERSIONINFO_EXIT
/** \brief Exit point of function EthTSyn_GetVersionInfo() */
#define DBG_ETHTSYN_GETVERSIONINFO_EXIT(a)
#endif

#ifndef DBG_ETHTSYN_RXINDICATION_ENTRY
/** \brief Entry point of function EthTSyn_RxIndication() */
#define DBG_ETHTSYN_RXINDICATION_ENTRY(a,b,c,d,e,f)
#endif

#ifndef DBG_ETHTSYN_RXINDICATION_EXIT
/** \brief Exit point of function EthTSyn_RxIndication() */
#define DBG_ETHTSYN_RXINDICATION_EXIT(a,b,c,d,e,f)
#endif

#if(ETHTSYN_RELIABLE_TXCONF == STD_OFF)

#ifndef DBG_ETHTSYN_TXCONFIRMATION_ENTRY
/** \brief Entry point of function EthTSyn_TxConfirmation() */
#define DBG_ETHTSYN_TXCONFIRMATION_ENTRY(a,b)
#endif

#ifndef DBG_ETHTSYN_TXCONFIRMATION_EXIT
/** \brief Exit point of function EthTSyn_TxConfirmation() */
#define DBG_ETHTSYN_TXCONFIRMATION_EXIT(a,b)
#endif

#else

#ifndef DBG_ETHTSYN_TXCONFIRMATION_ENTRY
/** \brief Entry point of function EthTSyn_TxConfirmation() */
#define DBG_ETHTSYN_TXCONFIRMATION_ENTRY(a,b,c)
#endif

#ifndef DBG_ETHTSYN_TXCONFIRMATION_EXIT
/** \brief Exit point of function EthTSyn_TxConfirmation() */
#define DBG_ETHTSYN_TXCONFIRMATION_EXIT(a,b,c)
#endif

#endif /* ETHTSYN_RELIABLE_TXCONF == STD_OFF */

#ifndef DBG_ETHTSYN_TRCVLINKSTATECHG_ENTRY
/** \brief Entry point of function EthTSyn_TrcvLinkStateChg() */
#define DBG_ETHTSYN_TRCVLINKSTATECHG_ENTRY(a,b)
#endif

#ifndef DBG_ETHTSYN_TRCVLINKSTATECHG_EXIT
/** \brief Exit point of function EthTSyn_TrcvLinkStateChg() */
#define DBG_ETHTSYN_TRCVLINKSTATECHG_EXIT(a,b)
#endif

#ifndef DBG_ETHTSYN_SETTRANSMISSIONMODE_ENTRY
/** \brief Entry point of function EthTSyn_SetTransmissionMode() */
#define DBG_ETHTSYN_SETTRANSMISSIONMODE_ENTRY(a,b)
#endif

#ifndef DBG_ETHTSYN_SETTRANSMISSIONMODE_EXIT
/** \brief Exit point of function EthTSyn_SetTransmissionMode() */
#define DBG_ETHTSYN_SETTRANSMISSIONMODE_EXIT(a,b)
#endif

#ifndef DBG_ETHTSYN_SETPROTOCOLPARAM_ENTRY
/** \brief Entry point of function EthTSyn_SetProtocolParam() */
#define DBG_ETHTSYN_SETPROTOCOLPARAM_ENTRY(a,b)
#endif

#ifndef DBG_ETHTSYN_SETPROTOCOLPARAM_EXIT
/** \brief Exit point of function EthTSyn_SetProtocolParam() */
#define DBG_ETHTSYN_SETPROTOCOLPARAM_EXIT(a,b,c)
#endif

#ifndef DBG_ETHTSYN_GETPROTOCOLPARAM_ENTRY
/** \brief Entry point of function EthTSyn_GetProtocolParam() */
#define DBG_ETHTSYN_GETPROTOCOLPARAM_ENTRY(a,b)
#endif

#ifndef DBG_ETHTSYN_GETPROTOCOLPARAM_EXIT
/** \brief Exit point of function EthTSyn_GetProtocolParam() */
#define DBG_ETHTSYN_GETPROTOCOLPARAM_EXIT(a,b,c)
#endif

#ifndef DBG_ETHTSYN_ICVGENERATIONINDICATION_ENTRY
/** \brief Entry point of function EthTSyn_IcvGenerationIndication() */
#define DBG_ETHTSYN_ICVGENERATIONINDICATION_ENTRY(a,b)
#endif

#ifndef DBG_ETHTSYN_ICVGENERATIONINDICATION_EXIT
/** \brief Exit point of function EthTSyn_IcvGenerationIndication() */
#define DBG_ETHTSYN_ICVGENERATIONINDICATION_EXIT(a,b)
#endif

#ifndef DBG_ETHTSYN_ICVVERIFICATIONINDICATION_ENTRY
/** \brief Entry point of function EthTSyn_IcvVerificationIndication() */
#define DBG_ETHTSYN_ICVVERIFICATIONINDICATION_ENTRY(a,b)
#endif

#ifndef DBG_ETHTSYN_ICVVERIFICATIONINDICATION_EXIT
/** \brief Exit point of function EthTSyn_IcvVerificationIndication() */
#define DBG_ETHTSYN_ICVVERIFICATIONINDICATION_EXIT(a,b)
#endif

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[external data]=========================================*/

#endif /* ifndef ETHTSYN_TRACE_H */
/*==================[end of file]===========================================*/
