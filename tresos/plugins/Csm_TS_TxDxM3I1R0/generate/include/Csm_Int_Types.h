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
[!INCLUDE "Csm_Macros.m"!]
[!/* ====================================================================================== */!][!//
[!//
#ifndef CSM_INT_TYPES_H
#define CSM_INT_TYPES_H

/*==================[deviations]==================================================================*/

/*==================[misra deviations]============================================================*/

/*  MISRA-C:2012 Deviation List
 *
 *  MISRAC2012-1) Deviated Rule: 20.7 (required)
 *   "Expressions resulting from the expansion of macro parameters shall be enclosed in
 *    parentheses."
 *
 *   Reason:
 *   Enclosing parameter 'ptrtype' of compiler abstraction macro P2VAR for previous/next pointers
 *   of linked lists tends to faulty c code after preprocessing.
 */

/*==================[includes]====================================================================*/

/* !LINKSTO SWS_Csm_00068,1 */
#include <Std_Types.h>

#include <Csm_Types.h>

/*==================[macros]======================================================================*/

/** \brief  Csm job queue level 'CSM_QL_NONE'. The job is not queued.
 **/
#if (defined CSM_QL_NONE)
  #error CSM_QL_NONE is already defined
#endif /* #if (defined CSM_QL_NONE) */
#define  CSM_QL_NONE    0x0000U

/** \brief  Csm job queue level 'CSM_QL_CSM'. The job is queued in the Csm module.
 **/
#if (defined CSM_QL_CSM)
  #error CSM_QL_CSM is already defined
#endif /* #if (defined CSM_QL_CSM) */
#define  CSM_QL_CSM     0x0001U

/** \brief  Csm job queue level 'CSM_QL_CRYPTO'. The job is queued in the Crypto module.
 **/
#if (defined CSM_QL_CRYPTO)
  #error CSM_QL_CRYPTO is already defined
#endif /* #if (defined CSM_QL_CRYPTO) */
#define  CSM_QL_CRYPTO  0x0002U

/*==================[type definitions]============================================================*/

/**! \brief  Enumeration of the queue level (None, Csm, Crypto) a job is enqueued in.
 **/
/* !LINKSTO CSM.Dsn.Api/Types/00005,1 */
typedef uint8 Csm_JobQueueLevelType;

/**! \brief  Csm callback notification function pointer
 **/
/* !LINKSTO CSM.Dsn.Api/Types/00006,1 */
typedef P2FUNC(void, CSM_APPL_CODE, Csm_CallbackNotificationType)
(
  P2CONST(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) job,
          Std_ReturnType                            result
);

/**! \brief  SchM callout notification function pointer
 **/
/* !LINKSTO CSM.Dsn.Api/Types/00007,1 */
typedef P2FUNC(void, CSM_APPL_CODE, Csm_InternalTriggerType)
(
  void
);

/**! \brief  Structure for call back notification context
 **/
/* !LINKSTO CSM.Dsn.Api/Types/00008,1 */
typedef struct
{
  Csm_CallbackNotificationType callback;
[!IF "$Csm_Rte_Enabled_Callback = 'true'"!]
  Csm_InternalTriggerType internalTrigger;
[!ENDIF!]
}
Csm_CallbackNotificationCtxType;

/**! \brief  Csm callback notifications function pointer if the R20-11 callback logic has been configured
 **/
/* !LINKSTO CSM.Dsn.Api/Types/00010,1 */
typedef P2FUNC(void, CSM_APPL_CODE, Csm_CallbackNotificationSWCType)
(
  Crypto_ResultType result
);

[!IF "(node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmJobBasedCallbacknotificationPorts) = 'false' and $Csm_Rte_Enabled_Callback = 'true') or (node:value(as:modconf('Csm')/CsmEbGeneral/CsmEbMisc/CsmEbCorrectionCsmJobBasedCallbacknotificationPorts) = 'true' and $Csm_Rte_Enabled_CallbackR2011 = 'true')"!]
/**! \brief  Structure for call back notification result
 **/
/* !LINKSTO CSM.Dsn.Api/Types/00009,1 */
typedef struct
{
  P2CONST(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) job;
          Std_ReturnType                            result;
}
Csm_CallbacksExtraDataType;
[!ENDIF!]
/** \brief  Structure of a Csm queue element
 **/
/* !LINKSTO CSM.Dsn.Api/Types/00001,1 */
typedef struct Csm_QueueElement
{
  P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) job;               /*!< Job that is referenced by the queue element */
  /* Deviation MISRAC2012-1 <+1> */
  P2VAR(struct Csm_QueueElement, AUTOMATIC, CSM_APPL_DATA) next;  /*!< Reference to the next element in the queue */
}
Csm_QueueElementType;

/** \brief  Meta data structure of a Csm queue
 **/
/* !LINKSTO CSM.Dsn.Api/Types/00003,1 */
typedef struct
{
  uint32  queueId;                                                        /*!< Numeric queue identifier. */
  boolean lockMainQueueDelJob;                                            /*!< Flag whether the processing of asyncronous jobs regarding this queue shall be stopped until next main function call, due to locking dequeuing jobs in Csm_MainFunction. */
  boolean lockMainProcessJob;                                             /*!< Flag whether the processing of job with highest priority (== head) shall be prevented in Csm_MainFunction, e.g. to prevent multiple processing due to preemption.       */
  uint32 cryIfChannelId;
  uint32 currentSize;                                                     /*!< Current size of the queue */
  CONST(uint32, CSM_CONST) maxSize;                                    /*!< Maximum number of elements that can be stored in the queue */
  P2VAR(Csm_QueueElementType, AUTOMATIC, CSM_APPL_DATA) head;       /*!< Pointer to the first element of the queue (highest priority) */
  CONSTP2VAR(Csm_QueueElementType, AUTOMATIC, CSM_APPL_DATA) data;  /*!< Pointer to the data array that stores the queue elements */
}
Csm_QueueType;

/**! \brief  Structure which contains additional job configurations.
 **/
/* !LINKSTO CSM.Dsn.Api/Types/00002,2 */
typedef struct
{
  P2VAR(Csm_QueueType, AUTOMATIC, CSM_APPL_DATA) csmQueue;
  Csm_CallbackNotificationSWCType csmSWCCallback;
  Csm_InternalTriggerType         internalTrigger;
}
Crypto_JobExtraCnfgType;

/**! \brief  Structure which contains additional job datas.
 **/
/* !LINKSTO CSM.Dsn.Api/Types/00004,2 */
typedef struct
{
  Csm_JobQueueLevelType csmQueueLevel;
  boolean        csmLockFlag;
  Std_ReturnType callbackSWCResult;
}
Crypto_JobExtraDataType;

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function declarations]==============================================*/

/*================================================================================================*/

#endif /* #ifndef CSM_INT_TYPES_H */

/*==================[end of file]=================================================================*/

