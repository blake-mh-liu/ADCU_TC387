/**
 * \file
 *
 * \brief AUTOSAR ComM
 *
 * This file contains the implementation of the AUTOSAR
 * module ComM.
 *
 * \version 5.21.4
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 8.3 (required)
 * All declarations of an object or function shall use the same names and type qualifiers.
 *
 * Reason:
 * typedef of generated file .arxml don't use the same name.
 *
 */

/* !LINKSTO ComM.EB_Ref.ASR403.SWS_ComM_00463.ComM_EcuMBswM,1 */
#ifndef COMM_ECUMBSWM_H
#define COMM_ECUMBSWM_H

/*==================[inclusions]============================================*/

#include <ComStack_Types.h>   /* AUTOSAR COM stack standard types */
#include <ComM_Version.h>     /* ComM module version information */

/*==================[macros]================================================*/

#if (defined COMM_SID_ECUM_WAKE_UP_INDICATION)
#error COMM_SID_ECUM_WAKE_UP_INDICATION already defined
#endif
/** \brief AUTOSAR API service ID.
 **
 ** Definition of service ID for ComM_EcuM_WakeupIndiciation(). */
#define COMM_SID_ECUM_WAKE_UP_INDICATION  42U

#if (defined COMM_SID_ECUM_PNC_WAKE_UP_INDICATION)
#error COMM_SID_ECUM_PNC_WAKE_UP_INDICATION already defined
#endif
/** \brief AUTOSAR API service ID.
 **
 ** Definition of service ID for ComM_EcuM_WakeupIndiciation(). */
#define COMM_SID_ECUM_PNC_WAKE_UP_INDICATION  55U

#if (defined COMM_SID_COMMUNICATIONALLOWED)
#error COMM_SID_COMMUNICATIONALLOWED already defined
#endif
/** \brief AUTOSAR API service ID.
 **
 ** Definition of service ID for ComM_CommunicationAllowed(). */
#define COMM_SID_COMMUNICATIONALLOWED 53U

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/
#define COMM_START_SEC_CODE
#include <ComM_MemMap.h>

#ifndef RTE_SCHM_SWCBSW_COMM_ECUM_WAKEUPINDICATION
#define RTE_SCHM_SWCBSW_COMM_ECUM_WAKEUPINDICATION
/** \brief Indicate that the ECU State Manager has received a wakeup.
 **
 ** This function provides an indication that the ECU State Manager
 ** has received a wakeup event for the given channel.
 **
 ** \param[in] Channel Network channel on which the mode transition
 **                    has occurred.
 **
 ** \ServiceID{::COMM_SID_ECUM_WAKE_UP_INDICATION}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
/* Deviation MISRAC2012-1 */
extern FUNC(void, COMM_CODE) ComM_EcuM_WakeUpIndication
(
  NetworkHandleType Channel
);
#endif

#ifndef RTE_SCHM_SWCBSW_COMM_ECUM_PNCWAKEUPINDICATION
#define RTE_SCHM_SWCBSW_COMM_ECUM_PNCWAKEUPINDICATION
/** \brief Notification of a wake up on the corresponding partial network cluster.
 **
 ** This function provides an indication that the ECU State Manager
 ** has received a wakeup event for the given PNC.
 **
 ** \param[in] PNCid Partial network index
 **
 ** \ServiceID{::COMM_SID_ECUM_PNC_WAKE_UP_INDICATION}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
extern FUNC(void, COMM_CODE) ComM_EcuM_PNCWakeUpIndication
(
  PNCHandleType PNCid
);
#endif
/** \brief Indication to ComM when communication is allowed .
 **
 ** EcuM or BswM shall indicate to ComM when communication is allowed.
 **
 ** \param[in] Channel Network channel on which communication is allowed.
 ** \param[in] Allowed communication is allowed (true) or not (false)
 ** \ServiceID{::COMM_SID_COMMUNICATIONALLOWED}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Asynchronous} */
extern FUNC(void, COMM_CODE) ComM_CommunicationAllowed
(
  NetworkHandleType Channel,
  boolean           Allowed
);
#define COMM_STOP_SEC_CODE
#include <ComM_MemMap.h>

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* ifndef COMM_ECUMBSWM_H */
/*==================[end of file]===========================================*/
