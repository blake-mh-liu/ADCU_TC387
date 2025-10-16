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

/** \brief  Macro that specifies Csm source code.
 **/
#define CSM_SRC

/*==================[deviations]==================================================================*/

/*==================[misra deviations]============================================================*/

/*==================[includes]====================================================================*/

#include <Csm.h>
#include <Csm_Int.h>
#include <CryIf.h>
#include <SchM_Csm.h>

/* !LINKSTO CSM.Req.Gen/Det/00001,1 */
#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
/* !LINKSTO SWS_Csm_00485,1 */
#include <Det.h>
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */

/*==================[macros]======================================================================*/

/*==================[type definitions]============================================================*/

/*==================[internal function declarations]==============================================*/

/*==================[internal constants]==========================================================*/

/*==================[internal data]===============================================================*/

/*==================[external constants]==========================================================*/

/*==================[external data]===============================================================*/

/*==================[external function definitions]===============================================*/

#define CSM_START_SEC_CODE
#include <Csm_MemMap.h>

/* --- Csm_QueuePushJob ------------------------------------------------------------------------- */

FUNC(Std_ReturnType, CSM_CODE) Csm_QueuePushJob
(
  P2VAR(Csm_QueueType, AUTOMATIC, CSM_APPL_DATA) csmQueuePtr,
  P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) csmJobPtr
)
{
  Std_ReturnType retVal            = E_NOT_OK;
  uint32         queueElementIndex = 0U;
  P2VAR(Csm_QueueElementType, AUTOMATIC, CSM_APPL_DATA) current    = NULL_PTR;
  P2VAR(Csm_QueueElementType, AUTOMATIC, CSM_APPL_DATA) previous   = NULL_PTR;
  P2VAR(Csm_QueueElementType, AUTOMATIC, CSM_APPL_DATA) newElement = NULL_PTR;

  if (csmQueuePtr == NULL_PTR)
  {
    /* !LINKSTO CSM.Req.Gen/Queueing/00003,1 */
    retVal = E_NOT_OK;
  }
  else
  if (csmJobPtr == NULL_PTR)
  {
    /* !LINKSTO CSM.Req.Gen/Queueing/00003,1 */
    retVal = E_NOT_OK;
  }
  else
  if (csmQueuePtr->currentSize >= csmQueuePtr->maxSize)
  {
    /* !LINKSTO CSM.Req.Gen/Queueing/00005,1 */
    retVal = CRYPTO_E_QUEUE_FULL;
  }
  else
  {
    current = csmQueuePtr->head;
    if (current == NULL_PTR)
    {
      csmQueuePtr->data[0].job  = csmJobPtr;
      csmQueuePtr->data[0].next = NULL_PTR;
      csmQueuePtr->head         = &(csmQueuePtr->data[0]);
      csmQueuePtr->currentSize++;
      retVal = E_OK;
    }
    else
    {
      /* check for empty element */
      /* CHECK: NOPARSE */
      /* Defensive programming - unreachable code.
       * This loop has at least one cycle, because maxSize is at least 1
       * according to specification
       */
      for (queueElementIndex = 0; queueElementIndex < csmQueuePtr->maxSize; queueElementIndex++)
      /* CHECK: PARSE */
      {
        if (csmQueuePtr->data[queueElementIndex].job == NULL_PTR)
        {
          csmQueuePtr->data[queueElementIndex].job = csmJobPtr;
          newElement = &csmQueuePtr->data[queueElementIndex];
          break;
        }
      }

      /* !LINKSTO SWS_Csm_00944,1 */
      while ( (current != NULL_PTR                                                  ) &&
              (current->job->jobInfo->jobPriority >= csmJobPtr->jobInfo->jobPriority)
            )
      {
        previous = current;
        current = current->next;
      }

      if (previous == NULL_PTR)
      {
        csmQueuePtr->head = newElement;
      }
      else
      {
        previous->next = newElement;
      }

      newElement->next = current;
      csmQueuePtr->currentSize++;
      retVal = E_OK;
    }
  }
  return retVal;
}

/* --- Csm_QueueDelJob -------------------------------------------------------------------------- */

FUNC(Std_ReturnType, CSM_CODE) Csm_QueueDelJob
(
  P2VAR(Csm_QueueType, AUTOMATIC, CSM_APPL_DATA) csmQueuePtr,
  P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) csmJobPtr
)
{
  Std_ReturnType retVal = E_NOT_OK;
  P2VAR(Csm_QueueElementType, AUTOMATIC, CSM_APPL_DATA) current = NULL_PTR;
  P2VAR(Csm_QueueElementType, AUTOMATIC, CSM_APPL_DATA) previous = NULL_PTR;

  if (csmQueuePtr == NULL_PTR)
  {
    /* !LINKSTO CSM.Req.Gen/Queueing/00003,1 */
    retVal = E_NOT_OK;
  }
  else
  if (csmJobPtr == NULL_PTR)
  {
    /* !LINKSTO CSM.Req.Gen/Queueing/00003,1 */
    retVal = E_NOT_OK;
  }
  else
  {
    current = csmQueuePtr->head;
    /* !LINKSTO CSM.Req.Gen/Queueing/00006,1 */
    while ( (current != NULL_PTR                                                  ) &&
            (current->job->jobInfo->jobPriority >= csmJobPtr->jobInfo->jobPriority)
          )
    {
      if (current->job == csmJobPtr)
      {
        if (current == csmQueuePtr->head)
        {
          csmQueuePtr->head = current->next;
        }
        else
        {
          previous->next = current->next;
        }
        current->job = NULL_PTR;
        current->next = NULL_PTR;
        csmQueuePtr->currentSize--;
        retVal = E_OK;
        break;
      }
      else
      {
        previous = current;
        current = current->next;
      }
    }
  }
  return retVal;
}

/* --- Csm_Main --------------------------------------------------------------------------------- */

/* !LINKSTO CSM.Req.Api/CsmMultiCore/MainFunction/00001,1 */
/* !LINKSTO CSM.Dsn.SWS_Csm_00479,1 */
/* !LINKSTO SWS_Csm_00019,1 */

#if (CSM_API_ENABLED_SERVICE_ASYNCHRONOUS == STD_ON)
FUNC(void, CSM_CODE) Csm_Main
(
  uint32 queueIndex
)
{
  Std_ReturnType  result = E_NOT_OK;
  Crypto_JobType *job    = NULL_PTR;
  boolean         run    = FALSE;

#if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON)
  if (!Csm_Initialized)
  {
    /* !LINKSTO SWS_Csm_00485,1, SWS_Csm_00489,1, SWS_Csm_00539,1 */
    (void)Det_ReportError(CSM_MODULE_ID,
                          CSM_INSTANCE_ID,
                          CSM_SID_MAINFUNCTION,
                          CSM_E_UNINIT
                         );
  }
  else
#endif /* #if (CSM_API_ENABLED_DEVERRORDETECT == STD_ON) */
  {
    job = NULL_PTR;

    if (Csm_Queues[queueIndex] != NULL_PTR)
    {
      /* !LINKSTO SWS_Csm_00037,1 */
      if (Csm_Queues[queueIndex]->lockMainQueueDelJob == FALSE)
      {
        /* !LINKSTO CSM.Dsn.Api/ExAreas/00001,1, CSM.Dsn.Api/ExAreas/00002,1 */
        SchM_Enter_Csm_SCHM_CSM_EXCLUSIVE_AREA_0();
        if (Csm_Queues[queueIndex]->head != NULL_PTR)
        {
          job = Csm_Queues[queueIndex]->head->job;
        }
        if ((Csm_Queues[queueIndex]->lockMainProcessJob == FALSE) &&
            (job != NULL_PTR) &&
            (Csm_JobExtraData[job->jobId].csmLockFlag == FALSE)
           )
        {
          Csm_Queues[queueIndex]->lockMainProcessJob   = TRUE;
          /* !LINKSTO CSM.Req.Api/Csm_MainFunction/00001,1 */
          Csm_JobExtraData[job->jobId].csmLockFlag  = TRUE;
          run                                             = TRUE;
        }
        SchM_Exit_Csm_SCHM_CSM_EXCLUSIVE_AREA_0();

        if (run == TRUE)
        {
          /* !LINKSTO SWS_Csm_00506,1 */
          result = CryIf_ProcessJob(Csm_Queues[queueIndex]->cryIfChannelId, job);
          /* !LINKSTO CSM.Dsn.Api/ExAreas/00001,1, CSM.Dsn.Api/ExAreas/00002,1 */
          SchM_Enter_Csm_SCHM_CSM_EXCLUSIVE_AREA_0();
          if (!((result == CRYPTO_E_BUSY) || (result == CRYPTO_E_QUEUE_FULL)))
          {
            (void) Csm_QueueDelJob(Csm_Queues[queueIndex], job);
            Csm_JobExtraData[job->jobId].csmQueueLevel = CSM_QL_CRYPTO;
          }
          Csm_Queues[queueIndex]->lockMainProcessJob   = FALSE;
          /* !LINKSTO CSM.Req.Api/Csm_MainFunction/00002,1 */
          Csm_JobExtraData[job->jobId].csmLockFlag  = FALSE;
          SchM_Exit_Csm_SCHM_CSM_EXCLUSIVE_AREA_0();
        }
      }

      /* !LINKSTO SWS_Csm_00037,1 */
      Csm_Queues[queueIndex]->lockMainQueueDelJob = FALSE;
    }
  }
}
#endif /* #if (CSM_API_ENABLED_SERVICE_ASYNCHRONOUS == STD_ON) */

FUNC(void, CSM_CODE) Csm_Int_CallbackNotification
(
  P2CONST(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) job,
          Std_ReturnType                            result
)
{
  if (result != E_OK)
  {
    if(Csm_JobExtraCnfg[job->jobId].csmSWCCallback != NULL_PTR)
    {
      Csm_JobExtraCnfg[job->jobId].csmSWCCallback(result);
    }
    else
    {
#if (CSM_CBK_COUNT != 0)
      if ( job->jobPrimitiveInfo->callbackId != CSM_CBK_EMPTY)
      {
        Csm_Callbacks[job->jobPrimitiveInfo->callbackId].callback(job, result);
      }
#endif /* #if (CSM_CBK_COUNT != 0) */
    }
    Csm_JobExtraData[job->jobId].csmQueueLevel = CSM_QL_NONE;
  }
  else
  {
    /* !LINKSTO CSM.Req.Correction.SWS_Csm_01053,3 */
    if (((job->CSM_API_JOBPRIMITIVEINPUTOUTPUT.mode & CRYPTO_OPERATIONMODE_UPDATE    )
           != 0U
        ) &&
        ((job->CSM_API_JOBPRIMITIVEINPUTOUTPUT.mode & CRYPTO_OPERATIONMODE_SINGLECALL)
           != CRYPTO_OPERATIONMODE_SINGLECALL
        ) &&
        ( job->jobPrimitiveInfo->callbackId                 != CSM_CBK_EMPTY) &&
        ( job->jobPrimitiveInfo->callbackUpdateNotification == TRUE         )
       )
    {
#if (CSM_CBK_COUNT != 0U)
      /* !LINKSTO SWS_Csm_00039,1 */
      Csm_Callbacks[job->jobPrimitiveInfo->callbackId].callback(job, result);
#endif /* #if (CSM_CBK_COUNT != 0U) */
    }
    /* !LINKSTO CSM.Req.Correction.SWS_Csm_01044,1 */
    if (((job->CSM_API_JOBPRIMITIVEINPUTOUTPUT.mode & CRYPTO_OPERATIONMODE_FINISH) != 0U           )
       )
    {
      if(Csm_JobExtraCnfg[job->jobId].csmSWCCallback != NULL_PTR)
      {
        Csm_JobExtraCnfg[job->jobId].csmSWCCallback(result);
      }
      else
      {
#if (CSM_CBK_COUNT != 0U)
        if( job->jobPrimitiveInfo->callbackId != CSM_CBK_EMPTY)
        {
          Csm_Callbacks[job->jobPrimitiveInfo->callbackId].callback(job, result);
        }
#endif /* #if (CSM_CBK_COUNT != 0U) */
      }
      if( Csm_JobExtraData[job->jobId].csmQueueLevel == CSM_QL_CRYPTO)
      {
        Csm_JobExtraData[job->jobId].csmQueueLevel = CSM_QL_NONE;
      }
    }
  }
}

#define CSM_STOP_SEC_CODE
#include <Csm_MemMap.h>

/*==================[internal function definitions]===============================================*/

/*==================[end of file]=================================================================*/

