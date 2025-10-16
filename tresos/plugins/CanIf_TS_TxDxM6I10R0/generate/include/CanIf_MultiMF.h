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

#ifndef CANIF_MULTIMF_H
#define CANIF_MULTIMF_H

/*==================[inclusions]============================================*/
[!IF "CanIfPublicCfg/CanIfDecoupledProcessingSupport = 'true'"!]

[!INCLUDE "../../generate_macros/CanIf_DecoupledProcessing.m"!]
#include <ComStack_Types.h>     /* AUTOSAR COM types */

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

#define CANIF_START_SEC_CODE
#include <CanIf_MemMap.h>

/** \brief CanIf Rx main function
 **
 ** Processes RxPdus decoupled from the reception events
 **
 ** This function has to be called periodically by the BSW scheduler.
 **
 ** \ServiceID{0x40}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, CANIF_CODE) CanIf_MainFunctionRx_Generic(uint8 Idx);


/** \brief CanIf Tx main function
 **
 ** Processes TxPdus decoupled from the transmit confirmation events
 **
 ** This function has to be called by the BSW scheduler.
 **
 ** \ServiceID{0x41}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, CANIF_CODE) CanIf_MainFunctionTx_Generic(uint8 Idx);

[!VAR "multicoreEnabled" = "CanIfPublicCfg/CanIfMultiCoreSupport = 'true'"!]
[!IF "$multicoreEnabled = 'true'"!]
#define CANIF_STOP_SEC_CODE
#include <CanIf_MemMap.h>
[!ENDIF!]

[!CALL "createRxMFAlloc"!]
[!LOOP "text:split($mfRxAlloc,';')"!]
[!VAR "qName" = "text:split(.,'#')[3]"!]
[!IF "$multicoreEnabled = 'true'"!]
  [!VAR "qName" = "concat('CanIf_1_', $qName)"!]
  [!VAR "partitionName" = "text:split(text:split(.,'#')[3], '_MainFunction')[1]"!]
[!ENDIF!]

#ifndef RTE_SCHM_SWCBSW_[!"text:toupper($qName)"!]
#define RTE_SCHM_SWCBSW_[!"text:toupper($qName)"!]

[!IF "$multicoreEnabled = 'true'"!]
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
extern FUNC(void, CANIF_1_[!"$partitionName"!]_CODE) [!"$qName"!](void);
[!ELSE!]
extern FUNC(void, CANIF_CODE) [!"$qName"!](void);
[!ENDIF!]

[!IF "$multicoreEnabled = 'true'"!]
#define CANIF_1_[!"$partitionName"!]_STOP_SEC_CODE
#include <CanIf_1_[!"$partitionName"!]_MemMap.h>
[!ENDIF!]

#endif /* RTE_SCHM_SWCBSW_[!"text:toupper($qName)"!] */

[!ENDLOOP!][!//Rx

[!CALL "createTxMFAlloc"!]
[!LOOP "text:split($mfTxAlloc,';')"!]
[!VAR "qName" = "text:split(.,'#')[3]"!]
[!IF "$multicoreEnabled = 'true'"!]
  [!VAR "qName" = "concat('CanIf_1_', $qName)"!]
  [!VAR "partitionName" = "text:split(text:split(.,'#')[3], '_MainFunction')[1]"!]
[!ENDIF!]

#ifndef RTE_SCHM_SWCBSW_[!"text:toupper($qName)"!]
#define RTE_SCHM_SWCBSW_[!"text:toupper($qName)"!]

[!IF "$multicoreEnabled = 'true'"!]
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
extern FUNC(void, CANIF_1_[!"$partitionName"!]_CODE) [!"$qName"!](void);
[!ELSE!]
extern FUNC(void, CANIF_CODE) [!"$qName"!](void);
[!ENDIF!]

[!IF "$multicoreEnabled = 'true'"!]
#define CANIF_1_[!"$partitionName"!]_STOP_SEC_CODE
#include <CanIf_1_[!"$partitionName"!]_MemMap.h>

[!ENDIF!]
#endif /* RTE_SCHM_SWCBSW_[!"text:toupper($qName)"!] */

[!ENDLOOP!][!//Tx

[!IF "$multicoreEnabled = 'false'"!]
#define CANIF_STOP_SEC_CODE
#include <CanIf_MemMap.h>
[!ENDIF!]
[!ELSE!]

#include <TSCompiler.h>

TS_PREVENTEMPTYTRANSLATIONUNIT

[!ENDIF!][!//CanIfDecoupledProcessingSupport

/*==================[internal function definitions]=========================*/
#endif /* ifndef CANIF_MULTIMF_H */
/*==================[end of file]============================================*/
[!ENDCODE!][!//

