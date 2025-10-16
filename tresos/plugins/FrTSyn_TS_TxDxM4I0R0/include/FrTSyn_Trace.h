/**
 * \file
 *
 * \brief AUTOSAR FrTSyn
 *
 * This file contains the implementation of the AUTOSAR
 * module FrTSyn.
 *
 * \version 4.0.9
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef FRTSYN_TRACE_H
#define FRTSYN_TRACE_H


/*==================[macros]================================================*/
/* ====== FRTSYN public APIs ====== */

#ifndef DBG_FRTSYN_GETVERSIONINFO_ENTRY
/** \brief Entry point of function FrTSyn_GetVersionInfo() */
#define DBG_FRTSYN_GETVERSIONINFO_ENTRY(a)
#endif

#ifndef DBG_FRTSYN_GETVERSIONINFO_EXIT
/** \brief Exit point of function FrTSyn_GetVersionInfo() */
#define DBG_FRTSYN_GETVERSIONINFO_EXIT(a)
#endif

#ifndef DBG_FRTSYN_INIT_ENTRY
/** \brief Entry point of function FrTSyn_Init() */
#define DBG_FRTSYN_INIT_ENTRY(a)
#endif

#ifndef DBG_FRTSYN_INIT_EXIT
/** \brief Exit point of function FrTSyn_Init() */
#define DBG_FRTSYN_INIT_EXIT(a)
#endif

#ifndef DBG_FRTSYN_MAINFUNCTION_ENTRY
/** \brief Entry point of function FrTSyn_MainFunction() */
#define DBG_FRTSYN_MAINFUNCTION_ENTRY()
#endif

#ifndef DBG_FRTSYN_MAINFUNCTION_EXIT
/** \brief Exit point of function FrTSyn_MainFunction() */
#define DBG_FRTSYN_MAINFUNCTION_EXIT()
#endif

#ifndef DBG_FRTSYN_RXINDICATION_ENTRY
/** \brief Entry point of function FrTSyn_RxIndication() */
#define DBG_FRTSYN_RXINDICATION_ENTRY(a,b)
#endif

#ifndef DBG_FRTSYN_RXINDICATION_EXIT
/** \brief Exit point of function FrTSyn_RxIndication() */
#define DBG_FRTSYN_RXINDICATION_EXIT(a,b)
#endif

#ifndef DBG_FRTSYN_SETTRANSMISSIONMODE_ENTRY
/** \brief Entry point of function FrTSyn_SetTransmissionMode() */
#define DBG_FRTSYN_SETTRANSMISSIONMODE_ENTRY(a,b)
#endif

#ifndef DBG_FRTSYN_SETTRANSMISSIONMODE_EXIT
/** \brief Exit point of function FrTSyn_SetTransmissionMode() */
#define DBG_FRTSYN_SETTRANSMISSIONMODE_EXIT(a,b)
#endif

#ifndef DBG_FRTSYN_TRIGGERTRANSMIT_ENTRY
/** \brief Entry point of function FrTSyn_TriggerTransmit() */
#define DBG_FRTSYN_TRIGGERTRANSMIT_ENTRY(a,b)
#endif

#ifndef DBG_FRTSYN_TRIGGERTRANSMIT_EXIT
/** \brief Exit point of function FrTSyn_TriggerTransmit() */
#define DBG_FRTSYN_TRIGGERTRANSMIT_EXIT(a,b)
#endif


/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/


#endif /* ifndef FRTSYN_TRACE_H */
