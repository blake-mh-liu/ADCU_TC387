/**
 * \file
 *
 * \brief AUTOSAR NvM
 *
 * This file contains the implementation of the AUTOSAR
 * module NvM.
 *
 * \version 6.17.36
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
/*==================[inclusions]============================================*/

#include <Std_Types.h>                                               /* AUTOSAR standard types */
#include <TSAutosar.h>                                               /* EB specific standard types */

#include <NvM.h>                                                     /* configuration header*/
#include <NvM_Wrapper.h>                                             /* own header */
#include <NvM_FunctionIntern.h>                                      /* own header */
#include <NvM_Queue.h>                                               /* own header */
#include <NvM_DataIntern.h>                                          /* User Header Needed for Callout declaration*/
#if (defined NVM_INTERNAL_USE)
#error NVM_INTERNAL_USE is already defined
#endif
#define NVM_INTERNAL_USE
#if (NVM_BSW_DISTRIBUTION_ENABLED == STD_ON)
#include <Os.h>                                                      /* Os Application related                 */
#endif
#if ( NVM_DEV_ERROR_DETECT == STD_ON )
#include <Det.h>               /* API of module Det. */
#endif
/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

#if ( defined(NVM_MC_CALLOUTS_ENABLED) )
#define NVM_START_SEC_CODE_MC_SHARED
#include <NvM_MemMap.h>
#endif /*MC CALLOUTS ENABLED*/

#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)

#if (defined (NVM_READBLOCK_CALLOUT))
/*======================NvM_Wrapper_ReadBlock==========================*/
FUNC(Std_ReturnType, NVM_CODE) NvM_Wrapper_ReadBlock
(
  NvM_BlockIdType BlockId,
  P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvM_DstPtr
)
{
  /* !LINKSTO NvM.MultiCore.ReadCallout_PreVerification,1 */
  uint16 BlockIndex = NvM_CheckCondReadBlock(BlockId, NvM_DstPtr);
  Std_ReturnType ret = E_NOT_OK;

  /* Check block is not already pending for the case when DET is disabled */
  if(BlockIndex != NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS)
  {
    ret = NVM_READBLOCK_CALLOUT(BlockIndex, NvM_DstPtr);
    if (ret == E_NOT_OK)
    {
      NvM_AdminBlockTable[BlockIndex].NvMExtendedStatus &= (uint8)(~(NVM_ES_MULTICORE_LOCK_MASK));
    }
  }
  return ret;
}
#endif /* defined NVM_READBLOCK_CALLOUT */

#if (defined(NVM_WRITEBLOCK_CALLOUT))
/*======================NvM_Wrapper_WriteBlock==========================*/
FUNC(Std_ReturnType, NVM_CODE) NvM_Wrapper_WriteBlock
(
  NvM_BlockIdType BlockId,
  P2CONST(void, AUTOMATIC, NVM_APPL_DATA) NvM_SrcPtr
)
{
  /* !LINKSTO NvM.MultiCore.WriteCallout_PreVerification,1 */
  uint16 BlockIndex = NvM_CheckCondWriteBlock(BlockId, NvM_SrcPtr);
  Std_ReturnType ret = E_NOT_OK;
  if(BlockIndex != NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS)
  {
    ret = NVM_WRITEBLOCK_CALLOUT(BlockIndex, NvM_SrcPtr);
    if (ret == E_NOT_OK)
    {
      NvM_AdminBlockTable[BlockIndex].NvMExtendedStatus &= (uint8)(~(NVM_ES_MULTICORE_LOCK_MASK));
    }
  }
  return ret;
}
#endif /* defined NVM_WRITEBLOCK_CALLOUT */

#if (defined(NVM_RESTOREBLOCKDEFAULTS_CALLOUT))
/*======================NvM_Wrapper_RestoreBlockDefaults==========================*/
FUNC(Std_ReturnType,NVM_CODE) NvM_Wrapper_RestoreBlockDefaults
(
  NvM_BlockIdType BlockId,
  P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvM_DstPtr
)
{
  /* !LINKSTO NvM.MultiCore.RestoreBlockDefaultsCallout_PreVerification,1 */
  uint16 BlockIndex = NvM_CheckCondRestoreBlockDefaults(BlockId, NvM_DstPtr);
  Std_ReturnType ret = E_NOT_OK;
  if(BlockIndex != NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS)
  {
    ret = NVM_RESTOREBLOCKDEFAULTS_CALLOUT(BlockIndex, NvM_DstPtr);
    if (ret == E_NOT_OK)
    {
      NvM_AdminBlockTable[BlockIndex].NvMExtendedStatus &= (uint8)(~(NVM_ES_MULTICORE_LOCK_MASK));
    }
  }
  return ret;
}
#endif /* defined NVM_RESTOREBLOCKDEFAULTS_CALLOUT */

#if (defined(NVM_READPRAMBLOCK_CALLOUT))
/*======================NvM_Wrapper_ReadPRAMBlock==========================*/
FUNC(Std_ReturnType, NVM_CODE) NvM_Wrapper_ReadPRAMBlock
(
  NvM_BlockIdType BlockId
)
{
  /* !LINKSTO NvM.MultiCore.ReadPRAMBlockCallout_PreVerification,1 */
  uint16 BlockIndex = NvM_CheckCondReadPRAMBlock(BlockId);
  Std_ReturnType ret = E_NOT_OK;

  if(BlockIndex != NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS)
  {
    ret = NVM_READPRAMBLOCK_CALLOUT(BlockIndex);
    if (ret == E_NOT_OK)
    {
      NvM_AdminBlockTable[BlockIndex].NvMExtendedStatus &= (uint8)(~(NVM_ES_MULTICORE_LOCK_MASK));
    }
  }
  return ret;
}
#endif /* defined NVM_READPRAMBLOCK_CALLOUT */

#if (defined(NVM_WRITEPRAMBLOCK_CALLOUT))
/*======================NvM_Wrapper_WritePRAMBlock==========================*/
FUNC(Std_ReturnType, NVM_CODE) NvM_Wrapper_WritePRAMBlock
(
  NvM_BlockIdType BlockId
)
{
  /* !LINKSTO NvM.MultiCore.WritePRAMBlockCallout_PreVerification,1 */
  uint16 BlockIndex = NvM_CheckCondWritePRAMBlock(BlockId);
  Std_ReturnType ret = E_NOT_OK;

  if(BlockIndex != NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS)
  {
    ret = NVM_WRITEPRAMBLOCK_CALLOUT(BlockIndex);
    if (ret == E_NOT_OK)
    {
      NvM_AdminBlockTable[BlockIndex].NvMExtendedStatus &= (uint8)(~(NVM_ES_MULTICORE_LOCK_MASK));
    }
  }
  return ret;
}
#endif /* defined NVM_WRITEPRAMBLOCK_CALLOUT */

#if (defined(NVM_RESTOREPRAMBLOCKDEFAULTS_CALLOUT))
/*======================NvM_Wrapper_RestorePRAMBlockDefaults==========================*/
FUNC(Std_ReturnType,NVM_CODE) NvM_Wrapper_RestorePRAMBlockDefaults
(
  NvM_BlockIdType BlockId
)
{
  /* !LINKSTO NvM.MultiCore.RestorePRAMBlockDefaultsCallout_PreVerification,1 */
  uint16 BlockIndex = NvM_CheckCondRestorePRAMBlockDefaults(BlockId);
  Std_ReturnType ret = E_NOT_OK;

  if(BlockIndex != NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS)
  {
    ret = NVM_RESTOREPRAMBLOCKDEFAULTS_CALLOUT(BlockIndex);
    if (ret == E_NOT_OK)
    {
      NvM_AdminBlockTable[BlockIndex].NvMExtendedStatus &= (uint8)(~(NVM_ES_MULTICORE_LOCK_MASK));
    }
  }
  return ret;
}
#endif /* defined NVM_RESTOREPRAMBLOCKDEFAULTS_CALLOUT */

#if (defined(NVM_CANCELJOBS_CALLOUT))
/*======================NvM_Wrapper_CancelJobs==========================*/
FUNC(Std_ReturnType, NVM_CODE) NvM_Wrapper_CancelJobs
(
  NvM_BlockIdType BlockId
)
{
  /* !LINKSTO NvM.MultiCore.CancelJobsCallout_PreVerification,1 */
  uint16 BlockIndex = NvM_CheckCondCancelJobs(BlockId);
  Std_ReturnType ret = E_NOT_OK;

  if(BlockIndex != NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS)
  {
    if( NvM_AdminBlockTable[BlockIndex].NvMResult == NVM_REQ_PENDING )
    {
      ret = NVM_CANCELJOBS_CALLOUT(BlockIndex);
      if (ret == E_NOT_OK)
      {
        NvM_AdminBlockTable[BlockIndex].NvMExtendedStatus &= (uint8)(~(NVM_ES_MULTICORE_LOCK_MASK));
      }
    }
    else
    {
      NvM_AdminBlockTable[BlockIndex].NvMExtendedStatus &= (uint8)(~(NVM_ES_MULTICORE_LOCK_MASK));
    }
  }
  return ret;
}
#endif /* defined NVM_CANCELJOBS_CALLOUT */

#endif /* #if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) */

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)

#if (defined(NVM_ERASENVBLOCK_CALLOUT))
/*======================NvM_Wrapper_EraseNvBlock==========================*/
FUNC(Std_ReturnType, NVM_CODE) NvM_Wrapper_EraseNvBlock
(
  NvM_BlockIdType BlockId
)
{
  /* !LINKSTO NvM.MultiCore.EraseNvBlockCallout_PreVerification,1 */
  uint16 BlockIndex = NvM_CheckCondEraseNvBlock(BlockId);
  Std_ReturnType ret = E_NOT_OK;

  if(BlockIndex != NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS)
  {
    ret = NVM_ERASENVBLOCK_CALLOUT(BlockIndex);
    if (ret == E_NOT_OK)
    {
      NvM_AdminBlockTable[BlockIndex].NvMExtendedStatus &= (uint8)(~(NVM_ES_MULTICORE_LOCK_MASK));
    }
  }

  return ret;
}
#endif /* defined NVM_ERASENVBLOCK_CALLOUT */

#if (defined(NVM_INVALIDATENVBLOCK_CALLOUT))
/*======================NvM_Wrapper_InvalidateNvBlock==========================*/
FUNC( Std_ReturnType,NVM_CODE ) NvM_Wrapper_InvalidateNvBlock
(
  NvM_BlockIdType BlockId
)
{
  /* !LINKSTO NvM.MultiCore.InvalidateNvBlockCallout_PreVerification,1 */
  uint16 BlockIndex = NvM_CheckCondInvalidateNvBlock(BlockId);
  Std_ReturnType ret = E_NOT_OK;

  if(BlockIndex != NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS)
  {
    ret = NVM_INVALIDATENVBLOCK_CALLOUT(BlockIndex);
    if (ret == E_NOT_OK)
    {
      NvM_AdminBlockTable[BlockIndex].NvMExtendedStatus &= (uint8)(~(NVM_ES_MULTICORE_LOCK_MASK));
    }
  }

  return ret;
}
#endif /* defined NVM_INVALIDATENVBLOCK_CALLOUT */

#endif /* #if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3) */

#if ( defined(NVM_MC_CALLOUTS_ENABLED) )
#define NVM_STOP_SEC_CODE_MC_SHARED
#include <NvM_MemMap.h>
#endif /*MC CALLOUTS ENABLED*/


#if (NVM_BSW_DISTRIBUTION_ENABLED == STD_ON)
#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)

/*======================NvM_Wrapper_ReadBlock==========================*/
FUNC(Std_ReturnType, NVM_CODE) NvM_Wrapper_ReadBlock
(
  NvM_BlockIdType BlockId,
  P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvM_DstPtr
)
{
  /* !LINKSTO NvM.MultiCore.ReadCallout_PreVerification,1 */
  uint16 BlockIndex = NvM_CheckCondReadBlock(BlockId, NvM_DstPtr);
  uint8 PartitionIdx;
  Std_ReturnType ret = E_NOT_OK;

  /* Check block is not already pending for the case when DET is disabled */
  if(BlockIndex != NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS)
  {
    os_applicationid_t OsApplicationId = NVM_GET_OS_APPLICATION_ID();
    if(OsApplicationId != NVM_OS_APPLICATION_ID_MASTER)
    {
      if(OsApplicationId == NvM_BlockDescriptorTable[BlockIndex].OsAppId)
      {
        NVM_QUEUE_WAIT_TO_LOCK();
        if(E_OK == NvM_Queue_CheckFullStandard(BlockIndex))
        {
          /* Increment the satellite job counter */
          NvM_Std_Initiated_On_Satellite++;
          /* Clearing the flag as fast as possible. */
          NVM_QUEUE_LOCK_RELEASE();

          PartitionIdx = NvM_GetPartitionIndex(OsApplicationId);
          ret = NvM_SchMInterPartitionCalls[PartitionIdx].schMJobCallsToMaster->readBlock(BlockIndex, NvM_DstPtr);

          HANDLE_SATELLITE_TO_MASTER_REQUEST_RESULT(ret, BlockIndex);
        }
        else
        {
          /* Clearing the flag as fast as possible. */
          NVM_QUEUE_LOCK_RELEASE();

          /* The job is not accepted. */
          NVM_ASYNC_ASYNC_LOCK_RELEASE(BlockIndex);
          NVM_ASYNC_SYNC_LOCK_RELEASE(BlockIndex);

#if (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW != TS_PROD_ERR_DISABLE)
          /* The queue is full and the job could not be accepted. */
          NvM_Report_Queue_Overflow(BlockIndex, NVM_READ_BLOCK_API_ID);
#endif
        }
      }
      else
      {
        /* This block is not mapped to this partition */
        /* !LINKSTO NvM.BswDistribution.DetWrongPartition,1 */
        NVM_DET_REPORT_ERROR( NVM_READ_BLOCK_API_ID, NVM_E_WRONG_PARTITION );

        /* The job is not accepted. */
        NVM_ASYNC_ASYNC_LOCK_RELEASE(BlockIndex);
        NVM_ASYNC_SYNC_LOCK_RELEASE(BlockIndex);
      }
    }
    else
    {
      /* We are in the master context */
      /* !LINKSTO NvM.BswDistribution.MasterAcceptAll,1 */
      ret = NvM_ASR40_ReadBlock(BlockIndex, NvM_DstPtr);
    }
  }
  return ret;
}

/*======================NvM_Wrapper_WriteBlock==========================*/
FUNC(Std_ReturnType, NVM_CODE) NvM_Wrapper_WriteBlock
(
  NvM_BlockIdType BlockId,
  P2CONST(void, AUTOMATIC, NVM_APPL_DATA) NvM_SrcPtr
)
{
  /* !LINKSTO NvM.MultiCore.WriteCallout_PreVerification,1 */
  uint16 BlockIndex = NvM_CheckCondWriteBlock(BlockId, NvM_SrcPtr);
  uint8 PartitionIdx;
  Std_ReturnType ret = E_NOT_OK;
  boolean ConditionValid = FALSE;
  if(BlockIndex != NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS)
  {
    os_applicationid_t OsApplicationId = NVM_GET_OS_APPLICATION_ID();
    if(OsApplicationId != NVM_OS_APPLICATION_ID_MASTER)
    {
      if(OsApplicationId == NvM_BlockDescriptorTable[BlockIndex].OsAppId)
      {
        NVM_QUEUE_WAIT_TO_LOCK();
#if (( NVM_JOB_PRIORITIZATION == STD_ON ) && ( NVM_NUMBER_OF_IMMEDIATE_PRIORITY_BLOCKS > 0U ) && ( NVM_SIZE_IMMEDIATE_JOB_QUEUE > 0U))
        if ( NvM_BlockDescriptorTable[BlockIndex].blockJobPriority == NVM_BLOCK_IMMEDIATE_PRIORITY )
        {
          if(NVM_IMMEDIATE_QUEUE_NOT_FULL())
          {
            ConditionValid = TRUE;
            /* Increment the satellite job counter */
            NvM_Imm_Initiated_On_Satellite++;
          }
        }
        else
#endif /* #if (( NVM_JOB_PRIORITIZATION == STD_ON ) && ( NVM_NUMBER_OF_IMMEDIATE_PRIORITY_BLOCKS > 0U ) && ( NVM_SIZE_IMMEDIATE_JOB_QUEUE > 0 )) */
        {
          if(E_OK == NvM_Queue_CheckFullStandard(BlockIndex))
          {
            ConditionValid = TRUE;
            /* Increment the satellite job counter */
            NvM_Std_Initiated_On_Satellite++;
          }
        }
        /* Clearing the flag as fast as possible. */
        NVM_QUEUE_LOCK_RELEASE();

        if(ConditionValid)
        {
          PartitionIdx = NvM_GetPartitionIndex(OsApplicationId);
          ret = NvM_SchMInterPartitionCalls[PartitionIdx].schMJobCallsToMaster->writeBlock(BlockIndex, NvM_SrcPtr);

          HANDLE_SATELLITE_TO_MASTER_REQUEST_RESULT(ret, BlockIndex);
        }
        else
        {
          /* The job is not accepted. */
          NVM_ASYNC_ASYNC_LOCK_RELEASE(BlockIndex);
          NVM_ASYNC_SYNC_LOCK_RELEASE(BlockIndex);

#if (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW != TS_PROD_ERR_DISABLE)
          /* The queue is full and the job could not be accepted. */
          NvM_Report_Queue_Overflow(BlockIndex, NVM_WRITE_BLOCK_API_ID);
#endif
        }
      }
      else
      {
        /* This block is not mapped to this partition */
        /* !LINKSTO NvM.BswDistribution.DetWrongPartition,1 */
        NVM_DET_REPORT_ERROR( NVM_WRITE_BLOCK_API_ID, NVM_E_WRONG_PARTITION );

        /* The job is not accepted. */
        NVM_ASYNC_ASYNC_LOCK_RELEASE(BlockIndex);
        NVM_ASYNC_SYNC_LOCK_RELEASE(BlockIndex);
      }
    }
    else
    {
      /* We are in the master context */
      /* !LINKSTO NvM.BswDistribution.MasterAcceptAll,1 */
      ret = NvM_ASR40_WriteBlock(BlockIndex, NvM_SrcPtr);
    }
  }
  return ret;
}

/*======================NvM_Wrapper_RestoreBlockDefaults==========================*/
FUNC(Std_ReturnType,NVM_CODE) NvM_Wrapper_RestoreBlockDefaults
(
  NvM_BlockIdType BlockId,
  P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvM_DstPtr
)
{
  /* !LINKSTO NvM.MultiCore.RestoreBlockDefaultsCallout_PreVerification,1 */
  uint16 BlockIndex = NvM_CheckCondRestoreBlockDefaults(BlockId, NvM_DstPtr);
  uint8 PartitionIdx;
  Std_ReturnType ret = E_NOT_OK;
  if(BlockIndex != NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS)
  {
    os_applicationid_t OsApplicationId = NVM_GET_OS_APPLICATION_ID();
    if(OsApplicationId != NVM_OS_APPLICATION_ID_MASTER)
    {
      if(OsApplicationId == NvM_BlockDescriptorTable[BlockIndex].OsAppId)
      {
        NVM_QUEUE_WAIT_TO_LOCK();
        if(E_OK == NvM_Queue_CheckFullStandard(BlockIndex))
        {
          /* Increment the satellite job counter */
          NvM_Std_Initiated_On_Satellite++;
          /* Clearing the flag as fast as possible. */
          NVM_QUEUE_LOCK_RELEASE();

          PartitionIdx = NvM_GetPartitionIndex(OsApplicationId);
          ret = NvM_SchMInterPartitionCalls[PartitionIdx].schMJobCallsToMaster->restoreBlockDefaults(BlockIndex, NvM_DstPtr);

          HANDLE_SATELLITE_TO_MASTER_REQUEST_RESULT(ret, BlockIndex);
        }
        else
        {
          /* Clearing the flag as fast as possible. */
          NVM_QUEUE_LOCK_RELEASE();

          /* The job is not accepted. */
          NVM_ASYNC_ASYNC_LOCK_RELEASE(BlockIndex);
          NVM_ASYNC_SYNC_LOCK_RELEASE(BlockIndex);

#if (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW != TS_PROD_ERR_DISABLE)
          /* The queue is full and the job could not be accepted. */
          NvM_Report_Queue_Overflow(BlockIndex, NVM_RESTORE_BLOCK_DEFAULTS_API_ID);
#endif
        }
      }
      else
      {
        /* This block is not mapped to this partition */
        /* !LINKSTO NvM.BswDistribution.DetWrongPartition,1 */
        NVM_DET_REPORT_ERROR( NVM_RESTORE_BLOCK_DEFAULTS_API_ID, NVM_E_WRONG_PARTITION );

        /* The job is not accepted. */
        NVM_ASYNC_ASYNC_LOCK_RELEASE(BlockIndex);
        NVM_ASYNC_SYNC_LOCK_RELEASE(BlockIndex);
      }
    }
    else
    {
      /* We are in the master context */
      /* !LINKSTO NvM.BswDistribution.MasterAcceptAll,1 */
      ret = NvM_ASR40_RestoreBlockDefaults(BlockIndex, NvM_DstPtr);
    }
  }
  return ret;
}

/*======================NvM_Wrapper_ReadPRAMBlock==========================*/
FUNC(Std_ReturnType, NVM_CODE) NvM_Wrapper_ReadPRAMBlock
(
  NvM_BlockIdType BlockId
)
{
  /* !LINKSTO NvM.MultiCore.ReadPRAMBlockCallout_PreVerification,1 */
  uint16 BlockIndex = NvM_CheckCondReadPRAMBlock(BlockId);
  uint8 PartitionIdx;
  Std_ReturnType ret = E_NOT_OK;

  if(BlockIndex != NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS)
  {
    os_applicationid_t OsApplicationId = NVM_GET_OS_APPLICATION_ID();
    if(OsApplicationId != NVM_OS_APPLICATION_ID_MASTER)
    {
      if(OsApplicationId == NvM_BlockDescriptorTable[BlockIndex].OsAppId)
      {
        NVM_QUEUE_WAIT_TO_LOCK();
        if(E_OK == NvM_Queue_CheckFullStandard(BlockIndex))
        {
          /* Increment the satellite job counter */
          NvM_Std_Initiated_On_Satellite++;
          /* Clearing the flag as fast as possible. */
          NVM_QUEUE_LOCK_RELEASE();

          PartitionIdx = NvM_GetPartitionIndex(OsApplicationId);
          ret = NvM_SchMInterPartitionCalls[PartitionIdx].schMJobCallsToMaster->readPRAMBlock(BlockIndex);

          HANDLE_SATELLITE_TO_MASTER_REQUEST_RESULT(ret, BlockIndex);
        }
        else
        {
          /* Clearing the flag as fast as possible. */
          NVM_QUEUE_LOCK_RELEASE();

          /* The job is not accepted. */
          NVM_ASYNC_ASYNC_LOCK_RELEASE(BlockIndex);
          NVM_ASYNC_SYNC_LOCK_RELEASE(BlockIndex);

#if (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW != TS_PROD_ERR_DISABLE)
          /* The queue is full and the job could not be accepted. */
          NvM_Report_Queue_Overflow(BlockIndex, NVM_READ_PRAM_BLOCK_API_ID);
#endif
        }
      }
      else
      {
        /* This block is not mapped to this partition */
        /* !LINKSTO NvM.BswDistribution.DetWrongPartition,1 */
        NVM_DET_REPORT_ERROR( NVM_READ_PRAM_BLOCK_API_ID, NVM_E_WRONG_PARTITION );

        /* The job is not accepted. */
        NVM_ASYNC_ASYNC_LOCK_RELEASE(BlockIndex);
        NVM_ASYNC_SYNC_LOCK_RELEASE(BlockIndex);
      }
    }
    else
    {
      /* We are in the master context */
      /* !LINKSTO NvM.BswDistribution.MasterAcceptAll,1 */
      ret = NvM_ASR42_ReadPRAMBlock(BlockIndex);
    }
  }
  return ret;
}

/*======================NvM_Wrapper_WritePRAMBlock==========================*/
FUNC(Std_ReturnType, NVM_CODE) NvM_Wrapper_WritePRAMBlock
(
  NvM_BlockIdType BlockId
)
{
  /* !LINKSTO NvM.MultiCore.WritePRAMBlockCallout_PreVerification,1 */
  uint16 BlockIndex = NvM_CheckCondWritePRAMBlock(BlockId);
  uint8 PartitionIdx;
  Std_ReturnType ret = E_NOT_OK;
  boolean ConditionValid = FALSE;

  if(BlockIndex != NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS)
  {
    os_applicationid_t OsApplicationId = NVM_GET_OS_APPLICATION_ID();
    if(OsApplicationId != NVM_OS_APPLICATION_ID_MASTER)
    {
      if(OsApplicationId == NvM_BlockDescriptorTable[BlockIndex].OsAppId)
      {
        NVM_QUEUE_WAIT_TO_LOCK();
#if (( NVM_JOB_PRIORITIZATION == STD_ON ) && ( NVM_NUMBER_OF_IMMEDIATE_PRIORITY_BLOCKS > 0U ) && ( NVM_SIZE_IMMEDIATE_JOB_QUEUE > 0U))
        if ( NvM_BlockDescriptorTable[BlockIndex].blockJobPriority == NVM_BLOCK_IMMEDIATE_PRIORITY )
        {
          if(NVM_IMMEDIATE_QUEUE_NOT_FULL())
          {
            ConditionValid = TRUE;
            /* Increment the satellite job counter */
            NvM_Imm_Initiated_On_Satellite++;
          }
        }
        else
#endif /* #if (( NVM_JOB_PRIORITIZATION == STD_ON ) && ( NVM_NUMBER_OF_IMMEDIATE_PRIORITY_BLOCKS > 0U ) && ( NVM_SIZE_IMMEDIATE_JOB_QUEUE > 0 )) */
        {
          if(E_OK == NvM_Queue_CheckFullStandard(BlockIndex))
          {
            ConditionValid = TRUE;
            /* Increment the satellite job counter */
            NvM_Std_Initiated_On_Satellite++;
          }
        }
        /* Clearing the flag as fast as possible. */
        NVM_QUEUE_LOCK_RELEASE();

        if(ConditionValid)
        {
          PartitionIdx = NvM_GetPartitionIndex(OsApplicationId);
          ret = NvM_SchMInterPartitionCalls[PartitionIdx].schMJobCallsToMaster->writePRAMBlock(BlockIndex);

          HANDLE_SATELLITE_TO_MASTER_REQUEST_RESULT(ret, BlockIndex);
        }
        else
        {
          /* The job is not accepted. */
          NVM_ASYNC_ASYNC_LOCK_RELEASE(BlockIndex);
          NVM_ASYNC_SYNC_LOCK_RELEASE(BlockIndex);

#if (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW != TS_PROD_ERR_DISABLE)
          /* The queue is full and the job could not be accepted. */
          NvM_Report_Queue_Overflow(BlockIndex, NVM_WRITE_PRAM_BLOCK_API_ID);
#endif
        }
      }
      else
      {
        /* This block is not mapped to this partition */
        /* !LINKSTO NvM.BswDistribution.DetWrongPartition,1 */
        NVM_DET_REPORT_ERROR( NVM_WRITE_PRAM_BLOCK_API_ID, NVM_E_WRONG_PARTITION );

        /* The job is not accepted. */
        NVM_ASYNC_ASYNC_LOCK_RELEASE(BlockIndex);
        NVM_ASYNC_SYNC_LOCK_RELEASE(BlockIndex);
      }
    }
    else
    {
      /* We are in the master context */
      /* !LINKSTO NvM.BswDistribution.MasterAcceptAll,1 */
      ret = NvM_ASR42_WritePRAMBlock(BlockIndex);
    }
  }
  return ret;
}

/*======================NvM_Wrapper_RestorePRAMBlockDefaults==========================*/
FUNC(Std_ReturnType,NVM_CODE) NvM_Wrapper_RestorePRAMBlockDefaults
(
  NvM_BlockIdType BlockId
)
{
  /* !LINKSTO NvM.MultiCore.RestorePRAMBlockDefaultsCallout_PreVerification,1 */
  uint16 BlockIndex = NvM_CheckCondRestorePRAMBlockDefaults(BlockId);
  uint8 PartitionIdx;
  Std_ReturnType ret = E_NOT_OK;

  if(BlockIndex != NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS)
  {
    os_applicationid_t OsApplicationId = NVM_GET_OS_APPLICATION_ID();
    if(OsApplicationId != NVM_OS_APPLICATION_ID_MASTER)
    {
      if(OsApplicationId == NvM_BlockDescriptorTable[BlockIndex].OsAppId)
      {
        NVM_QUEUE_WAIT_TO_LOCK();
        if(E_OK == NvM_Queue_CheckFullStandard(BlockIndex))
        {
          /* Increment the satellite job counter */
          NvM_Std_Initiated_On_Satellite++;
          /* Clearing the flag as fast as possible. */
          NVM_QUEUE_LOCK_RELEASE();

          PartitionIdx = NvM_GetPartitionIndex(OsApplicationId);
          ret = NvM_SchMInterPartitionCalls[PartitionIdx].schMJobCallsToMaster->restorePRAMBlockDefaults(BlockIndex);

          HANDLE_SATELLITE_TO_MASTER_REQUEST_RESULT(ret, BlockIndex);
        }
        else
        {
          /* Clearing the flag as fast as possible. */
          NVM_QUEUE_LOCK_RELEASE();

          /* The job is not accepted. */
          NVM_ASYNC_ASYNC_LOCK_RELEASE(BlockIndex);
          NVM_ASYNC_SYNC_LOCK_RELEASE(BlockIndex);

#if (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW != TS_PROD_ERR_DISABLE)
          /* The queue is full and the job could not be accepted. */
          NvM_Report_Queue_Overflow(BlockIndex, NVM_RESTORE_PRAM_BLOCK_DEFAULTS_API_ID);
#endif
        }
      }
      else
      {
        /* This block is not mapped to this partition */
        /* !LINKSTO NvM.BswDistribution.DetWrongPartition,1 */
        NVM_DET_REPORT_ERROR( NVM_RESTORE_PRAM_BLOCK_DEFAULTS_API_ID, NVM_E_WRONG_PARTITION );

        /* The job is not accepted. */
        NVM_ASYNC_ASYNC_LOCK_RELEASE(BlockIndex);
        NVM_ASYNC_SYNC_LOCK_RELEASE(BlockIndex);
      }
    }
    else
    {
      /* We are in the master context */
      /* !LINKSTO NvM.BswDistribution.MasterAcceptAll,1 */
      ret = NvM_ASR42_RestorePRAMBlockDefaults(BlockIndex);
    }
  }
  return ret;
}

/*======================NvM_Wrapper_CancelJobs==========================*/
FUNC(Std_ReturnType, NVM_CODE) NvM_Wrapper_CancelJobs
(
  NvM_BlockIdType BlockId
)
{
  /* !LINKSTO NvM.MultiCore.CancelJobsCallout_PreVerification,1 */
  uint16 BlockIndex = NvM_CheckCondCancelJobs(BlockId);
  uint8 PartitionIdx;
  Std_ReturnType ret = E_NOT_OK;

  if(BlockIndex != NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS)
  {
    os_applicationid_t OsApplicationId = NVM_GET_OS_APPLICATION_ID();
    if(OsApplicationId != NVM_OS_APPLICATION_ID_MASTER)
    {
      if(OsApplicationId == NvM_BlockDescriptorTable[BlockIndex].OsAppId)
      {
        if(NVM_CANCEL_OPERATION_LOCK(BlockIndex))
        {
          if(NVM_GET_SATELLITE_JOB_ACCEPTED_FLAG(BlockIndex) == TRUE)
          {
            if(NVM_GET_SATELLITE_JOB_ONGOING_FLAG(BlockIndex) == FALSE)
            {
              PartitionIdx = NvM_GetPartitionIndex(OsApplicationId);
              NVM_SET_SATELLITE_JOB_TO_BE_CANCELLED_FLAG(BlockIndex);
              ret = NvM_SchMInterPartitionCalls[PartitionIdx].schMJobCallsToMaster->cancelJobs(BlockIndex);
            }
          }
          else
          {
            /* The job cannot be cancelled */
            /* !LINKSTO NvM.BswDistribution.SatelliteCancel,1 */
          }
          NVM_CANCEL_OPERATION_LOCK_RELEASE(BlockIndex);
        }
        else
        {
          /* The job is either ongoing or we have just interrupted the job request or
           * the job could not be queued because the queue is full. Nothing to be done. */
        }
      }
      else
      {
        /* This block is not mapped to this partition */
        /* !LINKSTO NvM.BswDistribution.DetWrongPartition,1 */
        NVM_DET_REPORT_ERROR( NVM_CANCEL_JOBS_API_ID, NVM_E_WRONG_PARTITION );
      }
    }
    else
    {
      /* We are in the master context */
      ret = NvM_ASR40_CancelJobs(BlockIndex);
    }
  }
  return ret;
}

#endif /* #if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) */

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)

/*======================NvM_Wrapper_EraseNvBlock==========================*/
FUNC(Std_ReturnType, NVM_CODE) NvM_Wrapper_EraseNvBlock
(
  NvM_BlockIdType BlockId
)
{
  uint16 BlockIndex = NvM_CheckCondEraseNvBlock(BlockId);
  uint8 PartitionIdx;
  Std_ReturnType ret = E_NOT_OK;

  if(BlockIndex != NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS)
  {
    os_applicationid_t OsApplicationId = NVM_GET_OS_APPLICATION_ID();
    if(OsApplicationId != NVM_OS_APPLICATION_ID_MASTER)
    {
      if(OsApplicationId == NvM_BlockDescriptorTable[BlockIndex].OsAppId)
      {
        NVM_QUEUE_WAIT_TO_LOCK();
        if(E_OK == NvM_Queue_CheckFullStandard(BlockIndex))
        {
          /* Increment the satellite job counter */
          NvM_Std_Initiated_On_Satellite++;
          /* Clearing the flag as fast as possible. */
          NVM_QUEUE_LOCK_RELEASE();

          PartitionIdx = NvM_GetPartitionIndex(OsApplicationId);
          ret = NvM_SchMInterPartitionCalls[PartitionIdx].schMJobCallsToMaster->eraseNvBlock(BlockIndex);

          HANDLE_SATELLITE_TO_MASTER_REQUEST_RESULT(ret, BlockIndex);
        }
        else
        {
          /* Clearing the flag as fast as possible. */
          NVM_QUEUE_LOCK_RELEASE();

          /* The job is not accepted. */
          NVM_ASYNC_ASYNC_LOCK_RELEASE(BlockIndex);
          NVM_ASYNC_SYNC_LOCK_RELEASE(BlockIndex);

#if (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW != TS_PROD_ERR_DISABLE)
          /* The queue is full and the job could not be accepted. */
          NvM_Report_Queue_Overflow(BlockIndex, NVM_ERASE_NV_BLOCK_API_ID);
#endif
        }
      }
      else
      {
        /* This block is not mapped to this partition */
        /* !LINKSTO NvM.BswDistribution.DetWrongPartition,1 */
        NVM_DET_REPORT_ERROR( NVM_ERASE_NV_BLOCK_API_ID, NVM_E_WRONG_PARTITION );

        /* The job is not accepted. */
        NVM_ASYNC_ASYNC_LOCK_RELEASE(BlockIndex);
        NVM_ASYNC_SYNC_LOCK_RELEASE(BlockIndex);
      }
    }
    else
    {
      /* We are in the master context */
      /* !LINKSTO NvM.BswDistribution.MasterAcceptAll,1 */
      ret = NvM_ASR40_EraseNvBlock(BlockIndex);
    }
  }

  return ret;
}

/*======================NvM_Wrapper_InvalidateNvBlock==========================*/
FUNC( Std_ReturnType,NVM_CODE ) NvM_Wrapper_InvalidateNvBlock
(
  NvM_BlockIdType BlockId
)
{
  uint16 BlockIndex = NvM_CheckCondInvalidateNvBlock(BlockId);
  uint8 PartitionIdx;
  Std_ReturnType ret = E_NOT_OK;

  if(BlockIndex != NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS)
  {
    os_applicationid_t OsApplicationId = NVM_GET_OS_APPLICATION_ID();
    if(OsApplicationId != NVM_OS_APPLICATION_ID_MASTER)
    {
      if(OsApplicationId == NvM_BlockDescriptorTable[BlockIndex].OsAppId)
      {
        NVM_QUEUE_WAIT_TO_LOCK();
        if(E_OK == NvM_Queue_CheckFullStandard(BlockIndex))
        {
          /* Increment the satellite job counter */
          NvM_Std_Initiated_On_Satellite++;
          /* Clearing the flag as fast as possible. */
          NVM_QUEUE_LOCK_RELEASE();

          PartitionIdx = NvM_GetPartitionIndex(OsApplicationId);
          ret = NvM_SchMInterPartitionCalls[PartitionIdx].schMJobCallsToMaster->invalidateNvBlock(BlockIndex);

          HANDLE_SATELLITE_TO_MASTER_REQUEST_RESULT(ret, BlockIndex);
        }
        else
        {
          /* Clearing the flag as fast as possible. */
          NVM_QUEUE_LOCK_RELEASE();

          /* The job is not accepted. */
          NVM_ASYNC_ASYNC_LOCK_RELEASE(BlockIndex);
          NVM_ASYNC_SYNC_LOCK_RELEASE(BlockIndex);

#if (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW != TS_PROD_ERR_DISABLE)
          /* The queue is full and the job could not be accepted. */
          NvM_Report_Queue_Overflow(BlockIndex, NVM_INVALIDATE_NV_BLOCK_API_ID);
#endif
        }
      }
      else
      {
        /* This block is not mapped to this partition */
        /* !LINKSTO NvM.BswDistribution.DetWrongPartition,1 */
        NVM_DET_REPORT_ERROR( NVM_INVALIDATE_NV_BLOCK_API_ID, NVM_E_WRONG_PARTITION );

        /* The job is not accepted. */
        NVM_ASYNC_ASYNC_LOCK_RELEASE(BlockIndex);
        NVM_ASYNC_SYNC_LOCK_RELEASE(BlockIndex);
      }
    }
    else
    {
      /* We are in the master context */
      /* !LINKSTO NvM.BswDistribution.MasterAcceptAll,1 */
      ret = NvM_ASR40_InvalidateNvBlock(BlockIndex);
    }
  }

  return ret;
}

#endif /* #if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3) */

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>
#endif

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
