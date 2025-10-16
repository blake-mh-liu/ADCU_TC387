/**
 * \file
 *
 * \brief AUTOSAR FrNm
 *
 * This file contains the implementation of the AUTOSAR
 * module FrNm.
 *
 * \version 5.16.16
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef FRNM_HSMFRNM_H
#define FRNM_HSMFRNM_H

/* Public interface for the FrNm
 * state machine.
 *
 * This file defines the public symbols and functions to use the
 * FrNm state machine.
 */

/*==================[inclusions]============================================*/

/* include state machine driver interface */
#include <FrNm_Hsm.h>

/*==================[macros]================================================*/

/* Events/signal defined in the FrNm state machine. */
#if (defined FRNM_HSM_FRNM_EV_RX_INDICATION)
#error FRNM_HSM_FRNM_EV_RX_INDICATION already defined
#endif
#define FRNM_HSM_FRNM_EV_RX_INDICATION 0U

#if (defined FRNM_HSM_FRNM_EV_NETWORK_START)
#error FRNM_HSM_FRNM_EV_NETWORK_START already defined
#endif
#define FRNM_HSM_FRNM_EV_NETWORK_START 1U

#if (defined FRNM_HSM_FRNM_EV_TX_CONFIRMATION_NETWORK_MODE)
#error FRNM_HSM_FRNM_EV_TX_CONFIRMATION_NETWORK_MODE already defined
#endif
#define FRNM_HSM_FRNM_EV_TX_CONFIRMATION_NETWORK_MODE 2U

#if (defined FRNM_HSM_FRNM_EV_TX_TIMEOUT_NETWORK_MODE)
#error FRNM_HSM_FRNM_EV_TX_TIMEOUT_NETWORK_MODE already defined
#endif
#define FRNM_HSM_FRNM_EV_TX_TIMEOUT_NETWORK_MODE 3U

#if (defined FRNM_HSM_FRNM_EV_FAILSAFE_SYNCH_MODE)
#error FRNM_HSM_FRNM_EV_FAILSAFE_SYNCH_MODE already defined
#endif
#define FRNM_HSM_FRNM_EV_FAILSAFE_SYNCH_MODE 4U

#if (defined FRNM_HSM_FRNM_EV_VOTE_CYCLE_TIMESLOT_SEND_IN_RS)
#error FRNM_HSM_FRNM_EV_VOTE_CYCLE_TIMESLOT_SEND_IN_RS already defined
#endif
#define FRNM_HSM_FRNM_EV_VOTE_CYCLE_TIMESLOT_SEND_IN_RS 5U

#if (defined FRNM_HSM_FRNM_EV_DATA_CYCLE_TIMESLOT_SEND_IN_RS)
#error FRNM_HSM_FRNM_EV_DATA_CYCLE_TIMESLOT_SEND_IN_RS already defined
#endif
#define FRNM_HSM_FRNM_EV_DATA_CYCLE_TIMESLOT_SEND_IN_RS 6U

#if (defined FRNM_HSM_FRNM_EV_DATA_CYCLE_TIMESLOT)
#error FRNM_HSM_FRNM_EV_DATA_CYCLE_TIMESLOT already defined
#endif
#define FRNM_HSM_FRNM_EV_DATA_CYCLE_TIMESLOT 7U

#if (defined FRNM_HSM_FRNM_EV_VOTE_CYCLE_TIMESLOT)
#error FRNM_HSM_FRNM_EV_VOTE_CYCLE_TIMESLOT already defined
#endif
#define FRNM_HSM_FRNM_EV_VOTE_CYCLE_TIMESLOT 8U

#if (defined FRNM_HSM_FRNM_EV_TX_CONFIRMATION)
#error FRNM_HSM_FRNM_EV_TX_CONFIRMATION already defined
#endif
#define FRNM_HSM_FRNM_EV_TX_CONFIRMATION 9U

#if (defined FRNM_HSM_FRNM_EV_TX_TIMEOUT)
#error FRNM_HSM_FRNM_EV_TX_TIMEOUT already defined
#endif
#define FRNM_HSM_FRNM_EV_TX_TIMEOUT 10U

#if (defined FRNM_HSM_FRNM_EV_VOTE_RECEIVED)
#error FRNM_HSM_FRNM_EV_VOTE_RECEIVED already defined
#endif
#define FRNM_HSM_FRNM_EV_VOTE_RECEIVED 11U

#if (defined FRNM_HSM_FRNM_EV_UNI_TIMEOUT)
#error FRNM_HSM_FRNM_EV_UNI_TIMEOUT already defined
#endif
#define FRNM_HSM_FRNM_EV_UNI_TIMEOUT 12U

#if (defined FRNM_HSM_FRNM_EV_FAILSAFE_SLEEP_MODE)
#error FRNM_HSM_FRNM_EV_FAILSAFE_SLEEP_MODE already defined
#endif
#define FRNM_HSM_FRNM_EV_FAILSAFE_SLEEP_MODE 13U

#if (defined FRNM_HSM_FRNM_EV_REP_CYCLE_COMPLETED)
#error FRNM_HSM_FRNM_EV_REP_CYCLE_COMPLETED already defined
#endif
#define FRNM_HSM_FRNM_EV_REP_CYCLE_COMPLETED 14U

#if (defined FRNM_HSM_FRNM_EV_STARTUP_ERROR)
#error FRNM_HSM_FRNM_EV_STARTUP_ERROR already defined
#endif
#define FRNM_HSM_FRNM_EV_STARTUP_ERROR 15U

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

#define FRNM_START_SEC_CONST_UNSPECIFIED
#include <FrNm_MemMap.h>

/** \brief Initialization data for the statechart statechart FrNm */
extern CONST(FrNm_HsmStatechartType, FRNM_CONST)
 FrNm_HsmScFrNm;

#define FRNM_STOP_SEC_CONST_UNSPECIFIED
#include <FrNm_MemMap.h>

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* defined FRNM_HSMFRNM_H */
/*==================[end of file]===========================================*/
