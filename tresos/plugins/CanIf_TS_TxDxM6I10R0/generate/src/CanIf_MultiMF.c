/**
 * \file
 *
 * \brief AUTOSAR CanIf
 *
 * This file contains the implementation of the AUTOSAR
 * module CanIf.
 *
 * \version 6.10.40
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
[!CODE!]
[!AUTOSPACING!]

/*==================[inclusions]============================================*/
[!IF "CanIfPublicCfg/CanIfDecoupledProcessingSupport = 'true'"!]

[!INCLUDE "../../generate_macros/CanIf_DecoupledProcessing.m"!]
#include <CanIf_MultiMF.h>

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[internal constants]====================================*/

/*==================[internal data]=========================================*/

/*==================[external constants]====================================*/

/*==================[external data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

[!VAR "multicoreEnabled" = "CanIfPublicCfg/CanIfMultiCoreSupport = 'true'"!]

[!IF "$multicoreEnabled = 'false'"!]
#define CANIF_START_SEC_CODE
#include <CanIf_MemMap.h>
[!ENDIF!]

[!CALL "createRxMFAlloc"!]
[!LOOP "text:split($mfRxAlloc,';')"!]
[!VAR "qRxName" = "text:split(.,'#')[3]"!]
[!IF "$multicoreEnabled = 'true'"!]
  [!VAR "qRxName" = "concat('CanIf_1_', $qRxName)"!]
  [!VAR "partitionName" = "text:split(text:split(.,'#')[3], '_MainFunction')[1]"!]

#define CANIF_1_[!"$partitionName"!]_START_SEC_CODE
#include <CanIf_1_[!"$partitionName"!]_MemMap.h>
[!ENDIF!]

/** \brief CanIf Rx main function
 **
 ** Processes decoupled RxPdus
 **
 ** This function has to be called by a task controlled by the
 ** BSW scheduler.
 **
 ** \ServiceID{0x40}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
[!IF "$multicoreEnabled = 'true'"!]
FUNC(void, CANIF_1_[!"$partitionName"!]_CODE) [!"$qRxName"!](void)
[!ELSE!]
FUNC(void, CANIF_CODE) [!"$qRxName"!](void)
[!ENDIF!]
{
  CanIf_MainFunctionRx_Generic([!"num:i(text:split(.,'#')[1])"!]U);
}

[!IF "$multicoreEnabled = 'true'"!]
#define CANIF_1_[!"$partitionName"!]_STOP_SEC_CODE
#include <CanIf_1_[!"$partitionName"!]_MemMap.h>
[!ENDIF!]
[!ENDLOOP!][!//Rx

[!CALL "createTxMFAlloc"!]
[!LOOP "text:split($mfTxAlloc,';')"!]
[!VAR "qTxName" = "text:split(.,'#')[3]"!]
[!IF "$multicoreEnabled = 'true'"!]
  [!VAR "qTxName" = "concat('CanIf_1_', $qTxName)"!]
  [!VAR "partitionName" = "text:split(text:split(.,'#')[3], '_MainFunction')[1]"!]

#define CANIF_1_[!"$partitionName"!]_START_SEC_CODE
#include <CanIf_1_[!"$partitionName"!]_MemMap.h>
[!ENDIF!]

/** \brief CanIf Tx main function
 **
 ** Performs the processes of the activities that are not directly initiated by
 ** the calls from CAN driver.
 **
 ** This function has to be called by a task controlled by the
 ** BSW scheduler.
 **
 ** \ServiceID{0x41}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
[!IF "$multicoreEnabled = 'true'"!]
FUNC(void, CANIF_1_[!"$partitionName"!]_CODE) [!"$qTxName"!](void)
[!ELSE!]
FUNC(void, CANIF_CODE) [!"$qTxName"!](void)
[!ENDIF!]
{
  CanIf_MainFunctionTx_Generic([!"num:i(text:split(.,'#')[1])"!]U);
}

[!IF "$multicoreEnabled = 'true'"!]
#define CANIF_1_[!"$partitionName"!]_STOP_SEC_CODE
#include <CanIf_1_[!"$partitionName"!]_MemMap.h>
[!ENDIF!]
[!ENDLOOP!][!//Tx

  [!IF "CanIfPublicCfg/CanIfMultiCoreSupport = 'false'"!]
#define CANIF_STOP_SEC_CODE
#include <CanIf_MemMap.h>
  [!ENDIF!]
[!ELSE!]
#include <TSCompiler.h>

/* Avoid empty translation unit according to ISO C90 */
TS_PREVENTEMPTYTRANSLATIONUNIT

[!ENDIF!][!//CanIfDecoupledProcessingSupport
/*==================[end of file]===========================================*/
[!ENDCODE!][!//
