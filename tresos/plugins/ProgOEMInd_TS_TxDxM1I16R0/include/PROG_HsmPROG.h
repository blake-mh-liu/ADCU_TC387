
#ifndef PROG_HSMPROG_H
#define PROG_HSMPROG_H

/* --------{ EB Automotive C Source File }-------- */

/* Public interface for the PROG
 * state machine.
 *
 * This file defines the public symbols and functions to use the
 * PROG state machine.
 */

/* NOCOV List
 *
 * NOCOV-TEMPLATE:
 *
 * Reason:
 * The file is a generated from a generic template that does not
 * respect all the OsekCore rules.
 */

/*==================[inclusions]============================================*/

#include <Std_Types.h>                            /* AUTOSAR standard types */

/* include state machine driver interface */
#include <PROG_Hsm.h>

/*==================[macros]================================================*/
/* CHECK: NOPARSE */
/* NOCOV-TEMPLATE */

/* Events/signal defined in the PROG state machine. */
#define PROG_HSM_PROG_EV_PROG_EVENT_OPEN_PROG_SESSION 0U
#define PROG_HSM_PROG_EV_PROG_EVENT_REQ_DSC01 1U
#define PROG_HSM_PROG_EV_PROG_EVENT_REQ_DSC03 2U
#define PROG_HSM_PROG_EV_PROG_EVENT_REQ_ER 3U
#define PROG_HSM_PROG_EV_PROG_EVENT_REQ_PRECOND_CHECK 4U
#define PROG_HSM_PROG_EV_PROG_EVENT_RESET 5U
#define PROG_HSM_PROG_EV_PROG_EVENT_S3_TIMEOUT 6U
#define PROG_HSM_PROG_EV_PROG_EVENT_CHECKSUM_UPDATE 7U
#define PROG_HSM_PROG_EV_PROG_EVENT_CRC_FINISH 8U
#define PROG_HSM_PROG_EV_PROG_EVENT_WAIT_NRC78 9U
#define PROG_HSM_PROG_EV_PROG_EVENT_TX_CONF 10U
#define PROG_HSM_PROG_EV_PROG_EVENT_UNLOCK_FAILED 11U
#define PROG_HSM_PROG_EV_PROG_EVENT_SLEEP 12U
#define PROG_HSM_PROG_EV_PROG_EVENT_BLU_PROGRESS 13U
#define PROG_HSM_PROG_EV_PROG_EVENT_FAILED 14U
#define PROG_HSM_PROG_EV_PROG_EVENT_STREAMING 15U
#define PROG_HSM_PROG_EV_PROG_EVENT_WRITE_CHECK 16U
#define PROG_HSM_PROG_EV_PROG_EVENT_CRYPTO_FINISH 17U
#define PROG_HSM_PROG_EV_PROG_EVENT_TD_END 18U
#define PROG_HSM_PROG_EV_PROG_EVENT_WRITE 19U
#define PROG_HSM_PROG_EV_PROG_EVENT_REQ_CHECKMEMORY 20U
#define PROG_HSM_PROG_EV_PROG_EVENT_REQ_COHERENCY_CHECK 21U
#define PROG_HSM_PROG_EV_PROG_EVENT_REQ_COMPARE_KEY 22U
#define PROG_HSM_PROG_EV_PROG_EVENT_REQ_GET_SEED 23U
#define PROG_HSM_PROG_EV_PROG_EVENT_REQ_RD 24U
#define PROG_HSM_PROG_EV_PROG_EVENT_REQ_RTE 25U
#define PROG_HSM_PROG_EV_PROG_EVENT_REQ_TD 26U
#define PROG_HSM_PROG_EV_PROG_EVENT_REQ_ERASE 27U
#define PROG_HSM_PROG_EV_PROG_EVENT_REQ_WRITE_FP 28U
#define PROG_HSM_PROG_EV_PROG_EVENT_FINISHED 29U
#define PROG_HSM_PROG_EV_PROG_EVENT_INIT 30U

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

#define PROG_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief Initialization data for the statechart statechart PROG */
extern CONST(PROG_HsmStatechartType, PROG_CONST)
 PROG_HsmScPROG;

#define PROG_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/
/* CHECK: PARSE */
#endif /* defined PROG_HSMPROG_H */
/*==================[end of file]===========================================*/
