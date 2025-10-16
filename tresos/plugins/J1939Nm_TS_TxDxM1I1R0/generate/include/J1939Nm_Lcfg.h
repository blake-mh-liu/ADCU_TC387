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
#ifndef J1939NM_LCFG_H
#define J1939NM_LCFG_H

/*==================[includes]==============================================*/

#include <TSAutosar.h>              /* global configuration */

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/* start data section declaration */
#define J1939NM_START_SEC_CONST_32
#include <J1939Nm_MemMap.h>

/* value used to validate post build configuration against link time configuration */
extern CONST(uint32, J1939NM_CONST) J1939Nm_LcfgSignature;

/* stop data section declaration */
#define J1939NM_STOP_SEC_CONST_32
#include <J1939Nm_MemMap.h>

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* ifndef J1939NM_LCFG_H */
/*==================[end of file]===========================================*/
