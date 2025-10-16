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

/*==================[inclusions]=============================================*/
#include <TSAutosar.h>         /* EB specific standard types */
#include <ComStack_Types.h>    /* typedefs for AUTOSAR com stack */
#include <J1939Rm_Lcfg.h>      /* Generated configuration */

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/* start data section declaration */
#define J1939RM_START_SEC_CONST_32
#include <J1939Rm_MemMap.h>

/* value used to validate post build configuration against link time configuration */
CONST(uint32, J1939RM_CONST) J1939Rm_LcfgSignature = [!"asc:getConfigSignature(as:modconf('J1939RM')[1]//eb-list::*[not(child::*) and (node:configclass() = 'Link')])"!]U;

/* stop data section declaration */
#define J1939RM_STOP_SEC_CONST_32
#include <J1939Rm_MemMap.h>

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/

