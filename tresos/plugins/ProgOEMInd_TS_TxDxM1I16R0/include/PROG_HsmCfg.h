#ifndef PROG_HSMCFG_H
#define PROG_HSMCFG_H

/* --------{ EB Automotive C Source File }-------- */

/* this file must be provided by the user
 *
 * It sets configuration options for the hsm */

/* NOCOV List
 *
 * NOCOV-TEMPLATE:
 *
 * Reason:
 * The file is a generated from a generic template that does not
 * respect all the OsekCore rules.
 */

/*==================[inclusions]============================================*/
#include "EB_Prj.h"

/*==================[macros]================================================*/
/* CHECK: NOPARSE */
/* NOCOV-TEMPLATE */

/** \brief Enable multiple instances of the same statemachine */
#define PROG_HSM_INST_MULTI_ENABLED      STD_OFF


/* *** Individual settings for each Hsm model *** */

/** \brief Number of instances of hsm NMIND
 *
 * Definition is only needed if PROG_HSM_INST_MULTI_ENABLED==STD_ON */
#define PROG_HSM_PROG_NUM_INST         1U

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

/* CHECK: PARSE */
#endif
/*==================[end of file]===========================================*/
