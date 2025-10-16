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
#ifndef J1939NM_TRACE_H
#define J1939NM_TRACE_H

/*==================[inclusions]============================================*/


#include <Std_Types.h>

/* Check if BASE_DBG_ENABLE is defined and set to STD_ON.
 * If so, include Base_Dbg.h which includes a custom header file */
#if (defined BASE_DBG_ENABLE)
#if (BASE_DBG_ENABLE == STD_ON)

#include <Base_Dbg.h>

#endif
#endif

/*==================[macros]================================================*/

#ifndef DBG_J1939NM_NULL_POINTER_VALIDATION_ENTRY
/** \brief Entry point of function J1939Nm_NetworkHandleValidator() */
#define DBG_J1939NM_NULL_POINTER_VALIDATION_ENTRY(a)
#endif

#ifndef DBG_J1939NM_NULL_POINTER_VALIDATION_EXIT
/** \brief Exit point of function J1939Nm_NetworkHandleValidator() */
#define DBG_J1939NM_NULL_POINTER_VALIDATION_EXIT(a)
#endif

#ifndef DBG_J1939NM_SUBSTATE_VALIDATION_ENTRY
/** \brief Check for Invalid SubState other then J1939NM_OFFLINE_CLAIMING or J1939NM_OFFLINE_ACLOST*/
#define DBG_J1939NM_SUBSTATE_VALIDATION_ENTRY(a,b)
#endif

#ifndef DBG_J1939NM_SUBSTATE_VALIDATION_EXIT
/** \brief Check for Invalid SubState other then J1939NM_OFFLINE_CLAIMING or J1939NM_OFFLINE_ACLOST*/
#define DBG_J1939NM_SUBSTATE_VALIDATION_EXIT(a,b)
#endif

#ifndef DBG_J1939NM_HANDLE_PENDING_TRANSMISSION_ENTRY
/** \brief Entry point of function J1939Nm_HandlePendingTransmission() */
#define DBG_J1939NM_HANDLE_PENDING_TRANSMISSION_ENTRY(a,b)
#endif

#ifndef DBG_J1939NM_HANDLE_PENDING_TRANSMISSION_EXIT
/** \brief Exit point of function J1939Nm_HandlePendingTransmission() */
#define DBG_J1939NM_HANDLE_PENDING_TRANSMISSION_EXIT(a,b)
#endif

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[external data]=========================================*/

#endif /* ifndef J1939NM_TRACE_H */
/*==================[end of file]===========================================*/
