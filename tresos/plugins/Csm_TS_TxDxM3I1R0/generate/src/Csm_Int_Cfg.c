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
[!AUTOSPACING!]
[!/* ====================================================================================== */!][!//
[!INCLUDE "include/Csm_Macros.m"!]
[!/* ====================================================================================== */!][!//
[!//

/** \brief  Macro that specifies Csm source code.
 **/
#define CSM_SRC

/*==================[deviations]==================================================================*/

/*==================[misra deviations]============================================================*/

/* MISRA-C:2012 Deviations
 *
 * MISRAC2012-1) Deviated Rule: 11.1 (required)
 *   Conversions shall not be performed between a pointer to a function and any other type.
 *
 *   Reason:
 *   The calls to callbacks accessible via Rte must be inserted in the array of API callbacks
 *   returning void. That's why the return value of Rte callbacks has to be casted.
 */

/*==================[includes]====================================================================*/

#include <Csm_Types.h>
#include <Csm_Int_Types.h>
#include <Csm_Int_Cfg.h>
#include <Csm_Cfg.h>

#include <CryIf.h>
[!IF "(node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmJobBasedCallbacknotificationPorts) = 'false' and $Csm_Rte_Enabled_Callback = 'true') or (node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmJobBasedCallbacknotificationPorts) = 'true' and $Csm_Rte_Enabled_CallbackR2011 = 'true')"!][!//
#include <SchM_Csm.h>
[!IF "num:i(count(as:modconf('Csm')/CsmMainFunction/*)) = 0"!][!//
#include <Rte_Csm.h>
[!ELSE!][!//
[!LOOP "node:refs(as:modconf('Csm')/CsmMainFunction/*/CsmMainFunctionPartitionRef)"!][!//
[!VAR "ecucPartition" = "node:name(.)"!][!//
[!IF "num:i(0) != num:i(count(as:modconf('Csm')/CsmJobs/CsmJob/*[CsmJobUsePort = 'true' and node:name(node:ref(node:ref(node:ref(./CsmJobQueueRef)/CsmQueueMainFunctionRef)/CsmMainFunctionPartitionRef)) = $ecucPartition]))"!][!//
#include <Csm_[!"string($ecucPartition)"!].h>
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
[!ENDIF!][!//

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[internal function declarations]==============================================*/

/*==================[internal constants]==========================================================*/

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

#define CSM_START_SEC_CONST_32
#include <Csm_MemMap.h>

[!//
[!/* -------------------------------------------------------------------------------------- */!][!//
[!//
/* --- Keys --- */
/* !LINKSTO CSM.Dsn.Api/Consts/00005,1 */

/* !LINKSTO CSM.Req.Gen/CsmKeys/00001,1 */
#if (CSM_API_ENABLED_KEYMNGMNT == STD_ON)
CONST(uint32, CSM_CONST) Csm_Keys[CSM_KEY_COUNT] =
{
[!LOOP "node:order(./CsmKeys/CsmKey/*,'node:value(./CsmKeyId)')"!][!//
  [!WS "2"!][!"node:value(node:ref(./CsmKeyRef)/CryIfKeyId)"!]U, /* [!"node:name(node:ref(./CsmKeyRef))"!]" */
[!ENDLOOP!]
};
#endif /* #if (CSM_API_ENABLED_KEYMNGMNT == STD_ON) */

#define CSM_STOP_SEC_CONST_32
#include <Csm_MemMap.h>

#define CSM_START_SEC_CONST_UNSPECIFIED
#include <Csm_MemMap.h>

[!/* -------------------------------------------------------------------------------------- */!][!//
[!//
/* --- Callbacks --- */
/* !LINKSTO CSM.Dsn.Api/Consts/00004,2 */

[!IF "num:i(0) != num:i(count(./CsmCallbacks/CsmCallback/*))"!]
/* Deviation MISRAC2012-1 <START> */
CONST(Csm_CallbackNotificationCtxType, CSM_CONST) Csm_Callbacks[CSM_CBK_COUNT] =
{
  [!LOOP "node:order(./CsmCallbacks/CsmCallback/*, 'node:value(./CsmCallbackId)')"!]
    [!WS "2"!]{
      [!IF "node:empty(./CsmCallbackFunc)"!]
        [!IF "(node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) != 'CSM_API_VERSION_440') and (node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmJobBasedCallbacknotificationPorts) = 'false')"!][!//
          [!IF "num:i(count(as:modconf('Csm')/CsmMainFunction/*)) = 0"!]
            [!WS "4"!][!/* callback        */!](Csm_CallbackNotificationType) Rte_Call_[!"node:name(.)"!]_CallbackNotification_CallbackNotification,
          [!ELSE!]
            [!WS "4"!][!/* callback        */!](Csm_CallbackNotificationType) Csm_Call_[!"node:name(.)"!]_CallbackNotification_CallbackNotification,
          [!ENDIF!]
          [!WS "4"!][!/* internalTrigger */!]SchM_ActMainFunction_Csm_[!"node:name(.)"!]_InternalTriggerForCallback,
        [!ELSE!]
          [!WS "4"!]NULL_PTR,
          [!WS "4"!]NULL_PTR,
        [!ENDIF!]
      [!ELSE!]
        [!WS "4"!][!/* callback        */!][!"node:value(./CsmCallbackFunc)"!],
        [!IF "$Csm_Rte_Enabled_Callback = 'true'"!]
          [!WS "4"!][!/* internalTrigger */!]NULL_PTR,
        [!ENDIF!]
      [!ENDIF!]
    [!WS "2"!]},
  [!ENDLOOP!]
};
/* Deviation MISRAC2012-1 <STOP> */
[!ENDIF!]
[!//
[!/* -------------------------------------------------------------------------------------- */!][!//
[!//
/* --- Queues --- */
/* !LINKSTO CSM.Dsn.Api/Consts/00006,1 */

CONSTP2VAR(Csm_QueueType, AUTOMATIC, CSM_APPL_DATA) Csm_Queues[CSM_QUE_COUNT] =
{
[!LOOP "./CsmQueues/CsmQueue/*"!]
  [!IF "true() = node:contains(node:refs(./../../../CsmJobs/CsmJob/*/CsmJobQueueRef), .)"!]
    [!WS "2"!]&(Csm_Queue_[!"node:name(.)"!]),
  [!ELSE!]
    [!WS "2"!]NULL_PTR,
  [!ENDIF!]
[!ENDLOOP!]
};

[!//
[!/* -------------------------------------------------------------------------------------- */!][!//
[!//
/* --- Job additional configurations --- */
/* !LINKSTO CSM.Dsn.Api/Consts/00007,1 */

/* Deviation MISRAC2012-1 <START> */
CONST(Crypto_JobExtraCnfgType, CSM_CONST) Csm_JobExtraCnfg[CSM_JOB_COUNT] =
{
[!LOOP "node:order(./CsmJobs/CsmJob/*,'node:value(./CsmJobId)')"!]
  {
    [!IF "node:refvalid(./CsmJobQueueRef)"!]
      [!WS "4"!][!/* csmQueue     */!]&Csm_Queue_[!"node:name(node:ref(./CsmJobQueueRef))"!],
    [!ELSE!]
      [!WS "4"!]NULL_PTR,
      [!ERROR "Job/CsmJobQueueRef not valid."!]
    [!ENDIF!]

    [!IF "((node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbAutosarApiVersion) = 'CSM_API_VERSION_440') or (node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmJobBasedCallbacknotificationPorts) = 'true')) and ((CsmJobUsePort = 'true') and (node:exists(node:ref(./CsmJobPrimitiveRef)/*) = 'true') and (node:value(node:ref(./CsmJobPrimitiveRef)/*/*/*[contains(node:name(.),'Processing')]) = 'CSM_ASYNCHRONOUS'))"!][!//
      [!VAR "vJob" = "node:name(.)"!][!//
      [!IF "num:i(count(as:modconf('Csm')/CsmMainFunction/*)) = 0"!]
        [!IF "node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmJobBasedCallbacknotificationPorts) = 'true'"!][!//
          [!WS "4"!][!/* csmSWCCallback  */!](Csm_CallbackNotificationSWCType) Rte_Call_CallbackNotification_[!"node:name(.)"!]_CallbackNotification,
        [!ELSE!][!//
          [!WS "4"!][!/* csmSWCCallback  */!](Csm_CallbackNotificationSWCType) Rte_Call_[!"node:name(.)"!]_CallbackNotification_CallbackNotification,
        [!ENDIF!]
      [!ELSE!]
        [!WS "4"!][!/* csmSWCCallback  */!](Csm_CallbackNotificationSWCType) Csm_Call_[!"node:name(.)"!]_CallbackNotification_CallbackNotification,
      [!ENDIF!]
      [!WS "4"!][!/* internalTrigger */!]SchM_ActMainFunction_Csm_InternalTriggerForCallback_[!"node:name(.)"!]
    [!ELSE!][!//
      [!WS "4"!]NULL_PTR,
      [!WS "4"!]NULL_PTR
    [!ENDIF!][!//
  },
[!ENDLOOP!]
};
/* Deviation MISRAC2012-1 <STOP> */

[!//
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include <Csm_MemMap.h>

/*==================[external data]===============================================================*/

#define CSM_START_SEC_VAR_INIT_UNSPECIFIED
#include <Csm_MemMap.h>

[!/* -------------------------------------------------------------------------------------- */!][!//
[!//
/* ---- Queue element buffers --- */
/* !LINKSTO CSM.Dsn.Api/Datas/00003,1 */

[!LOOP "node:refs(./CsmJobs/CsmJob/*/CsmJobQueueRef)"!]
VAR(Csm_QueueElementType, CSM_APPL_DATA) Csm_QueueElementsBuffer_[!"node:name(.)"!][CSM_QUE_SIZE_[!"text:toupper(node:name(.))"!]] =
{
  [!FOR "i" = "num:i(1)" TO "num:i(node:value(./CsmQueueSize))"!]
    [!WS "2"!]{ NULL_PTR, NULL_PTR },
  [!ENDFOR!]
};

[!ENDLOOP!]
[!//
[!/* -------------------------------------------------------------------------------------- */!][!//
[!//
/* --- Queues --- */
/* !LINKSTO CSM.Dsn.Api/Datas/00005,1 */

[!VAR "queueID" = "num:i(0)"!]
[!LOOP "node:refs(./CsmJobs/CsmJob/*/CsmJobQueueRef)"!]
VAR(Csm_QueueType, CSM_APPL_DATA) Csm_Queue_[!"node:name(.)"!] =
{
  [!WS "2"!][!/* queueId             */!][!"$queueID"!]U,
  [!WS "2"!][!/* lockMainQueueDelJob */!]FALSE,
  [!WS "2"!][!/* lockMainProcessJob  */!]FALSE,
  [!IF "node:refvalid(./CsmChannelRef)"!]
#if defined(CryIfConf_CryIfChannel_[!"node:name(node:ref(./CsmChannelRef))"!])
    [!WS "2"!][!/* cryIfChannelId      */!]CryIfConf_CryIfChannel_[!"node:name(node:ref(./CsmChannelRef))"!],
#else
    [!WS "2"!][!/* cryIfChannelId      */!][!"node:value(node:ref(./CsmChannelRef)/CryIfChannelId)"!]U,
#endif
  [!ELSE!]
    [!WS "2"!][!/* cryIfChannelId      */!]CSM_CHN_EMPTY,
    [!ERROR "Job/CsmJobQueueRef/CsmChannelRef not valid."!]
  [!ENDIF!]
  [!WS "2"!][!/* currentSize         */!]0U,
  [!WS "2"!][!/* maxSize             */!]CSM_QUE_SIZE_[!"text:toupper(node:name(.))"!],
  [!WS "2"!][!/* head                */!]NULL_PTR,
  [!WS "2"!][!/* data                */!]&(Csm_QueueElementsBuffer_[!"node:name(.)"!][0U])
  [!VAR "queueID" = "num:i($queueID + num:i(1))"!]
};

[!ENDLOOP!]
[!//
[!/* -------------------------------------------------------------------------------------- */!][!//
[!//
/* --- Job additional datas --- */
/* !LINKSTO CSM.Dsn.Api/Datas/00004,1 */

VAR(Crypto_JobExtraDataType, CSM_APPL_DATA) Csm_JobExtraData[CSM_JOB_COUNT] =
{
[!LOOP "node:order(./CsmJobs/CsmJob/*,'node:value(./CsmJobId)')"!]
  [!WS "2"!]{ CSM_QL_NONE, FALSE, E_NOT_OK },
[!ENDLOOP!]
};
[!//
[!/* -------------------------------------------------------------------------------------- */!][!//
[!//
[!IF "node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmJobBasedCallbacknotificationPorts) = 'false' and $Csm_Rte_Enabled_Callback = 'true'"!]
/* --- Callback additional datas --- */
/* !LINKSTO CSM.Dsn.Api/Datas/00006,1 */

VAR(Csm_CallbacksExtraDataType, CSM_APPL_DATA) Csm_CallbacksExtraData[CSM_CBK_COUNT] =
{
  [!LOOP "node:order(./CsmCallbacks/CsmCallback/*, 'node:value(./CsmCallbackId)')"!]
    [!WS "2"!]{
      [!WS "4"!]NULL_PTR,
      [!WS "4"!]E_NOT_OK
    [!WS "2"!]},
  [!ENDLOOP!]
};
[!ENDIF!]

[!//
[!/* -------------------------------------------------------------------------------------- */!][!//
[!//
#define CSM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <Csm_MemMap.h>

/*==================[external function definitions]===============================================*/

/*==================[internal function definitions]===============================================*/

/*==================[end of file]=================================================================*/

