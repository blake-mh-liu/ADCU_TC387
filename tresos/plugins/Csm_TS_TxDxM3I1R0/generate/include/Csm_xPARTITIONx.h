/**
 * \file
 *
 * \brief AUTOSAR Csm
 *
 * This file contains the implementation of the AUTOSAR
 * module Csm.
 *
 * \version 3.1.33
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef CSM_[!"text:toupper($partition.name)"!]_H
#define CSM_[!"text:toupper($partition.name)"!]_H

/*==================[deviations]==================================================================*/

/*==================[includes]====================================================================*/

#include <Rte_Csm_[!"$partition.name"!]_Type.h>

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

#define CSM_START_SEC_CODE
#include <Csm_MemMap.h>

[!IF "(node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) = 'CSM_API_VERSION_440') or (node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmJobBasedCallbacknotificationPorts) = 'true')"!][!//
  [!LOOP "node:order(./CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name],'node:value(./CsmJobId)')"!][!//
      [!VAR "vJob" = "node:name(.)"!][!//
      [!IF "node:exists(node:ref(./CsmJobPrimitiveRef)/*) = 'true' and node:value(node:ref(./CsmJobPrimitiveRef)/*/*/*[contains(node:name(.),'Processing')]) = 'CSM_ASYNCHRONOUS'"!][!//
extern FUNC(void, CSM_APPL_CODE) Csm_Call_[!"$vJob"!]_CallbackNotification_CallbackNotification
(
  Std_ReturnType result
);
    [!ENDIF!][!//
  [!ENDLOOP!]
[!ENDIF!][!//


[!LOOP "as:modconf('Csm')/CsmCallbacks/CsmCallback/*[node:empty(./CsmCallbackFunc)]"!][!//
[!VAR "cbkName" = "node:name(.)"!][!//
[!IF "count(as:modconf('Csm')/CsmJobs/CsmJob/*[node:exists(./CsmJobPrimitiveCallbackRef)][node:name(node:ref(./CsmJobPrimitiveCallbackRef)) = $cbkName][node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $partition.name]) > 0"!][!//
extern FUNC(void, CSM_APPL_CODE) Csm_Call_[!"$cbkName"!]_CallbackNotification_CallbackNotification
(
  P2CONST(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) job,
          Std_ReturnType                            result
);

[!ENDIF!][!//
[!ENDLOOP!][!//
#define CSM_STOP_SEC_CODE
#include <Csm_MemMap.h>

/*================================================================================================*/

#endif /* #ifndef CSM_[!"text:toupper($partition.name)"!]_H */

/*==================[end of file]=================================================================*/
