/**
 * \file
 *
 * \brief AUTOSAR MemAcc
 *
 * This file contains the implementation of the AUTOSAR
 * module MemAcc.
 *
 * \version 1.0.10
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.8 (Required):
 * A cast shall not remove any const or volatile qualification from the type pointed to by a pointer.
 *
 * Reason:
 * For of memory optimization, the same pointer type const MemAcc_DataType* is used for jobs
 * that write user data and jobs that only read user data
 * As a consequence, a cast that discards 'const' qualifier is needed.
 *
 * MISRAC2012-2) Deviated Rule: 13.5 (Required):
 * The right hand operand of a logical && or || operator shall not contain persistent side effects.
 *
 * Reason:
 * TS_MemCmp function doesn't have side effects and it just compare the contents of two buffers
 * without modifying them
 */

/* mgcc62 Deviation List
 *
 * MGCC62-1) Deviated Rule: cast-qual
 * warning: cast discards 'const' qualifier from pointer target type [-Wcast-qual]
 *
 * Reason:
 * For of memory optimization, the same pointer type uint8* is used for jobs
 * that write user data and jobs that only read user data
 * As a consequence, a cast that discards 'const' qualifier is needed.
 */

/* CERT-C Deviation List
 *
 * CERTC-1) Deviated Rule: EXP.40
 * Do not modify constant objects
 *
 * Reason:
 * For of memory optimization, the same pointer type uint8* is used for jobs
 * that write user data and jobs that only read user data
 * As a consequence, a cast that discards 'const' qualifier is needed.
 */

 /*==================[inclusions]=============================================*/

#include <TSAutosar.h>            /* EB specific standard types              */
#include <TSMem.h>                /* Autosar Base module header              */
#include <SchM_MemAcc.h>

#include <MemAcc_Lcfg.h>
#include <MemAcc.h>               /* General MemAcc header file              */

#include <MemAcc_Int_Types.h>
#include <MemAcc_Queue.h>
#include <MemAcc_Int.h>
#include <MemAcc_Trace.h>

#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
#include <Det.h>                  /* API of module Det.                      */
#endif
#if (MEMACC_LEGACY_DRIVER_SUPPORT == STD_ON)
#include <MemIf.h>          /* memory interface types */
#endif
/*==================[macros]=================================================*/

#if (defined MEMACC_REQUEST_PARAM_OFFSET_INVALID)
#error MEMACC_REQUEST_PARAM_OFFSET_INVALID is already defined
#endif
/** \brief Checks for offset of a job start given a valid Area Index
 **
 ** \param[in]   AreaIdx Index of the area
 ** \param[in]   Offset  Logical address to be checked if belongs to the area
 **
 ** \pre   AreaIdx must be valid
 **
 ** \return True if Offset is INVALID
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
#define MEMACC_REQUEST_PARAM_OFFSET_INVALID(AreaIdx, Offset)                \
(                                                                           \
  ((Offset) < MemAcc_AddressAreas[(AreaIdx)].LogicalStartAddress)           \
  ||                                                                        \
  (                                                                         \
    (Offset) >                                                              \
    (                                                                       \
      MemAcc_AddressAreas[(AreaIdx)].LogicalStartAddress                    \
      +                                                                     \
      (MemAcc_AddressAreas[(AreaIdx)].Length - 1U)                          \
    )                                                                       \
  )                                                                         \
)

#if (defined MEMACC_REQUEST_PARAM_LENGTH_INVALID)
#error MEMACC_REQUEST_PARAM_LENGTH_INVALID is already defined
#endif
/** \brief Checks for invalid length of a job given a valid Area Index and Offset
 **
 ** \param[in]   AreaIdx Index of the area
 ** \param[in]   Offset  Logical address for which length is checked
 ** \param[in]   Length  Number of bytes to check if inside area, starting at given offset
 **
 ** \pre   Offset and AreaIdx must be valid
 **
 ** \return True if Length is INVALID
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
#define MEMACC_REQUEST_PARAM_LENGTH_INVALID(AreaIdx, Offset, Length)        \
(                                                                           \
  ((Length) > MemAcc_AddressAreas[(AreaIdx)].Length)                        \
  ||                                                                        \
  (Length == 0U)                                                            \
  ||                                                                        \
  (                                                                         \
    (Length - 1U)                                                           \
    >                                                                       \
    (                                                                       \
      MemAcc_AddressAreas[(AreaIdx)].LogicalStartAddress                    \
      +                                                                     \
      (MemAcc_AddressAreas[(AreaIdx)].Length - 1U)                          \
      -                                                                     \
      (Offset)                                                              \
    )                                                                       \
  )                                                                         \
)

#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
#if (defined MEMACC_DET_REPORT_ERROR)
#error MEMACC_DET_REPORT_ERROR is already defined
#endif
/** \brief Defines the Det reporting.
 **/
#define MEMACC_DET_REPORT_ERROR( ApiId, ErrorId )                           \
  (void)Det_ReportError( MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, ( ApiId ), ( ErrorId ) )
#endif

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

#define MEMACC_START_SEC_CODE
#include <MemAcc_MemMap.h>

/** \brief Handles the Locking state machine for the area whose index is specified as parameter
 **
 ** \param[in]   AddressAreaCfgIdx Index in the configuration of areas
 ** \param[in]   LockRequest Lock request for the area
 ** \pre   Parameters must be validated before function call
 **
 ** \return void
 **
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous} */
STATIC FUNC(void, MEMACC_CODE) MemAcc_AreaLockStateMachine (MemAcc_AddressAreaIdType AddressAreaCfgIdx, MemAcc_AddressAreaLockType * LockRequest);


#if ((MEMACC_ERASE_RETRY_SUPPORT == STD_ON) || (MEMACC_WRITE_RETRY_SUPPORT == STD_ON))
/** \brief Check if retry is applicable on the the related job, and update JobRetryCounter and JobState
 **
 ** \param[in]   AddressAreaCfgIdx Index in the configuration of areas
 **
 ** \pre   Parameters must be validated before function call
 **
 ** \return boolean
 ** \retval TRUE, FALSE
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
STATIC FUNC(boolean, MEMACC_CODE) MemAcc_HandleRetryOperations (MemAcc_AddressAreaIdType AddressAreaCfgIdx);
#endif


/** \brief Validates the input of a Job receiving a Job address, a Job content address and a length.
 **
 ** Reports DET errors depending on validation of parameters and DET enable switch
 **
 ** \param[in]   ApiId              Numeric Id of the API for which validation is performed
 ** \param[in]   AddressAreaCfgIdx  Index in the configuration of areas
 ** \param[in]   JobAddress         Logical address in memory for the job
 ** \param[in]   JobDataPtr         Data pointer for Job content: returned or input data
 ** \param[in]   Length             Length of the job
 **
 ** \return Std_ReturnType
 ** \retval E_OK, E_NOT_OK
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
STATIC FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_ValidateMemDataJobParams
(
    uint8                     ApiId,
    MemAcc_AddressAreaIdType  AddressAreaCfgIdx,
    MemAcc_AddressType        JobAddress,
    const MemAcc_DataType     *JobDataPtr,
    MemAcc_LengthType         Length
);


/** \brief Validates the input of a Job receiving a Job address and a length.
 **
 ** Reports DET errors depending on validation of parameters and DET enable switch
 **
 ** \param[in]   ApiId              Numeric Id of the API for which validation is performed
 ** \param[in]   AddressAreaCfgIdx  Index in the configuration of areas
 ** \param[in]   JobAddress         Logical address in memory for the job
 ** \param[in]   Length             Length of the job
 **
 ** \return Std_ReturnType
 ** \retval E_OK, E_NOT_OK
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
STATIC FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_ValidateMemOperationJobParams
(
    uint8                     ApiId,
    MemAcc_AddressAreaIdType  AddressAreaCfgIdx,
    MemAcc_AddressType        JobAddress,
    MemAcc_LengthType         Length
);


/** \brief Finds and returns the sub-area for a logical memory address
 **
 ** \param[in]   AddressAreaCfgIdx Index of the area
 ** \param[in]   LogicalAddress Logical address for which sub-area is returned
 **
 ** \pre   Parameters must be validated before function call
 **
 ** \return MemAcc_AddressAreaIdType
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
STATIC FUNC(MemAcc_AddressAreaIdType, MEMACC_CODE) MemAcc_FindLogicalAddressSubarea (MemAcc_AddressAreaIdType AddressAreaCfgIdx, MemAcc_AddressType LogicalAddress);


/** \brief Validates the input of the GetJobInfo function.
 **
 ** Validates the input of the GetJobInfo function.
 **
 ** \param[in]   AddressAreaCfgIdx Index in the areas configuration
 ** \param[in]   JobInfoPtr Structure pointer to return the detailed processing information of the current job
 **
 ** \return Std_ReturnType
 ** \retval E_OK, E_NOT_OK
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
STATIC FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_ValidateGetJobInfoParams (MemAcc_AddressAreaIdType AddressAreaCfgIdx, MemAcc_JobInfoType* JobInfoPtr);


/** \brief Validates the input of the GetMemoryInfo function.
 **
 ** Validates the input of the GetMemoryInfo function.
 **
 ** \param[in]   AddressAreaCfgIdx Index in the areas configuration
 ** \param[in]   Address Address in logical address space from which corresponding memory device information shall be retrieved
 ** \param[in]   MemoryInfoPtr Destination memory pointer to store the memory device information
 **
 ** \return Std_ReturnType
 ** \retval E_OK, E_NOT_OK
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
STATIC FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_ValidateGetMemoryInfoParams (MemAcc_AddressAreaIdType AddressAreaCfgIdx, MemAcc_AddressType Address,MemAcc_MemoryInfoType* MemoryInfoPtr);


/** \brief Gets the job result for all ongoing subareas
 **
 ** Gets the job result for all ongoing subareas
 ** \return void
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
STATIC FUNC(void, MEMACC_CODE) MemAcc_GetOngoingJobResults (void);


/** \brief Gets the job result and merges it into a common return(abstract of the type of lower layer)
 **
 ** Converts return values of legacy drivers to values of memory driver
 **
 ** \param[in]   AddressAreaCfgIdx Index in the configuration of areas
 **
 ** \return MemAcc_Mem_JobResultType
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
STATIC FUNC(MemAcc_Mem_JobResultType, MEMACC_CODE) MemAcc_GetDriverJobResult (MemAcc_AddressAreaIdType AddressAreaCfgIdx);


/** \brief Triggers the lower layer jobs for a SubArea.
 **
 ** Triggers the lower layer jobs for a SubArea.
 **
 ** \param[in]   AddressAreaCfgIdx Index in the areas configuration
 **
 ** \return Std_ReturnType
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
STATIC FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_TriggerJob (MemAcc_AddressAreaIdType AddressAreaCfgIdx);


/** \brief Returns the Index in the configuration for a specific Address Area
 **
 ** Returns the index in the configuration of the Address Area structures for an Area Id
 ** or invalid value for an invalid Area Id
 **
 ** \param[in]   AddressAreaId Address Area Id
 **
 ** \return MemAcc_AddressAreaIdType
 ** \retval Index of the Address Area
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
STATIC FUNC(MemAcc_AddressAreaIdType, MEMACC_CODE) MemAcc_GetAddressAreaConfigIndex (MemAcc_AddressAreaIdType AddressAreaId);


/** \brief Add a job that goes page by page to the driver queues
 **
 ** Add the needed jobs to the drivers queues
 **
 ** \param[in]   AddressAreaCfgIdx Address Area Index
 ** \param[in]   DriverAddress the logical address targeted by the request
 ** \param[in]   UserDataPtr Pointer to the user buffer
 ** \param[in]   Length Length targeted
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
STATIC FUNC(void, MEMACC_CODE) MemAcc_AddDeviceRequest
(
  MemAcc_AddressAreaIdType AddressAreaCfgIdx,
  MemAcc_AddressType JobLogicalAddress,
  const MemAcc_DataType *UserDataPtr,
  MemAcc_LengthType JobLength
);


/** \brief Handles the area job state machine by triggering the
 **        corresponding driver for each sub-area pertaining to the job
 **
 ** \param[in]   AddressAreaCfgIdx Address Area Index in the administrative array
 **
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous} */
STATIC FUNC(void, MEMACC_CODE) MemAcc_AreaJobStateMachine (MemAcc_AddressAreaIdType AddressAreaCfgIdx);


/** \brief Handles the area in progress job state.
 **
 **
 **
 ** \param[in]   AddressAreaCfgIdx Address Area Index in the administrative array
 **
 ** \return boolean
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous} */
STATIC FUNC(boolean, MEMACC_CODE) MemAcc_AreaInProgressJobState (MemAcc_AddressAreaIdType AddressAreaCfgIdx);


#if (MEMACC_LEGACY_DRIVER_SUPPORT == STD_ON)
/** \brief Checks whether blank check api is available for all drivers
 **        that would be used for a blank check job
 **
 **
 ** \param[in]  AddressAreaCfgIdx Address Area Index in the administrative array
 ** \param[in]  TargetAddress  Address starting the blank check job
 ** \param[in]  JobLength  Length of the blank check job
 **
 ** \pre   Parameters must be validated before function call,
 **        as contiguity of sub-areas is ensured by the generator
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
STATIC FUNC(boolean, MEMACC_CODE) MemAcc_BlankCheckApisAvailable(
    MemAcc_AddressAreaIdType AddressAreaCfgIdx,
    MemAcc_AddressType JobLogicalAddress,
    MemAcc_LengthType JobLength);
#endif /* MEMACC_LEGACY_DRIVER_SUPPORT */


/** \brief Get the read chunk size to be used during Read and BlankCheck driver call
 **
 ** \param[in]   AddressAreaCfgIdx Index in the areas configuration
  **
 ** \return Std_ReturnType
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
STATIC FUNC(MemAcc_LengthType, MEMACC_CODE) MemAcc_GetReadChunkSize(MemAcc_AddressAreaIdType AddressAreaCfgIdx);
#define MEMACC_STOP_SEC_CODE
#include <MemAcc_MemMap.h>

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/
#define MEMACC_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <MemAcc_MemMap.h>

/** \brief Holds job administrative data for the configured address areas */
STATIC VAR(MemAcc_AdminAddressAreaType, MEMACC_VAR_CLEARED) MemAcc_AdminAddressArea[MEMACC_NB_OF_CONFIGURED_ADDRESSAREAS];

/** \brief Holds lock requests data for the configured address areas */
STATIC VAR(MemAcc_AddressAreaLockType, MEMACC_VAR_CLEARED) MemAcc_LockRequests[MEMACC_NB_OF_CONFIGURED_ADDRESSAREAS];

#define MEMACC_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <MemAcc_MemMap.h>

#define MEMACC_START_SEC_VAR_INIT_8
#include <MemAcc_MemMap.h>

/** \brief It holds the initialization status of MemAcc. */
STATIC VAR(boolean, MEMACC_VAR) MemAcc_InitStatus = FALSE;

#define MEMACC_STOP_SEC_VAR_INIT_8
#include <MemAcc_MemMap.h>

#define MEMACC_START_SEC_VAR_CLEARED_8
#include <MemAcc_MemMap.h>

/** \brief Holds the requests for canceling area jobs */
STATIC VAR( boolean, MEMACC_VAR_CLEARED ) MemAcc_CancelRequests[MEMACC_NB_OF_CONFIGURED_ADDRESSAREAS];

#define MEMACC_STOP_SEC_VAR_CLEARED_8
#include <MemAcc_MemMap.h>

#define MEMACC_START_SEC_VAR_CLEARED_16
#include <MemAcc_MemMap.h>

/** \brief Holds number of job requests buffered since last main cycle */
STATIC VAR(MemAcc_AddressAreaIdType, MEMACC_VAR_CLEARED) MemAcc_JobRequestsBufferElementsNo;

#define MEMACC_STOP_SEC_VAR_CLEARED_16
#include <MemAcc_MemMap.h>

#define MEMACC_START_SEC_VAR_CLEARED_32
#include <MemAcc_MemMap.h>

/** \brief Holds a queue with the indexes of the memory areas
 *  corresponding to the received jobs since last main cycle
 * */
STATIC VAR( MemAcc_AddressAreaIdType, MEMACC_VAR_CLEARED ) MemAcc_JobRequestsBuffer[MEMACC_NB_OF_CONFIGURED_ADDRESSAREAS];

#define MEMACC_STOP_SEC_VAR_CLEARED_32
#include <MemAcc_MemMap.h>


#define MEMACC_START_SEC_CONST_UNSPECIFIED
#include <MemAcc_MemMap.h>

/** \brief Initialization values for a lock request */
STATIC CONST(MemAcc_AddressAreaLockType, MEMACC_CONST) LockRequestInit = {NULL_PTR, FALSE, FALSE};

#define MEMACC_STOP_SEC_CONST_UNSPECIFIED
#include <MemAcc_MemMap.h>
/*==================[internal function definitions]==========================*/

#define MEMACC_START_SEC_CODE
#include <MemAcc_MemMap.h>

STATIC FUNC(MemAcc_LengthType, MEMACC_CODE) MemAcc_GetReadChunkSize(
    MemAcc_AddressAreaIdType AddressAreaCfgIdx)
{
  MemAcc_AddressAreaIdType SubAreaIdx = MemAcc_AdminAddressArea[AddressAreaCfgIdx].SubAreaIdx;
  const MemAcc_SectorBatchType * const SectorBatchCfgPtr = MemAcc_AddressAreas[AddressAreaCfgIdx].SubAreaCfg[SubAreaIdx].SectorBatch;
#if ( MEMACC_READ_BURST_SUPPORT == STD_ON )
  MemAcc_AddressSubAreaAdminType * const SubAreaAdminPtr = &MemAcc_AdminAddressArea[AddressAreaCfgIdx].SubAreaAdmin;
  const MemAcc_AddressSubAreaType * const SubAreaCfgPtr  = &MemAcc_AddressAreas[AddressAreaCfgIdx].SubAreaCfg[SubAreaIdx];
#endif /* MEMACC_READ_BURST_SUPPORT */
  MemAcc_LengthType ReadChunkSize = 0;
#if (MEMACC_READ_BURST_SUPPORT == STD_ON)
  /* !LINKSTO MemAcc.SWS_MemAcc_00101,1 */
  /* !LINKSTO MemAcc.EB.MemoryAccess.Compare.Burst,1 */
  /* !LINKSTO MemAcc.EB.MemoryAccess.BlankCheck.Burst,1 */
  if((SubAreaCfgPtr->UseReadBurst)
      &&
      (SubAreaAdminPtr->RemainingLength >= SectorBatchCfgPtr->ReadPageBurstSize))
  {
    ReadChunkSize = SectorBatchCfgPtr->ReadPageBurstSize;
  }
  else if((SubAreaCfgPtr->UseReadBurst)
          &&
         ((SubAreaAdminPtr->RemainingLength < SectorBatchCfgPtr->ReadPageBurstSize)
         &&
         (SubAreaAdminPtr->RemainingLength >= SectorBatchCfgPtr->ReadPageSize)))
  {
    ReadChunkSize = SubAreaAdminPtr->RemainingLength;
  }
  /* !LINKSTO MemAcc.MemoryAccess.Read.Page, 1 */
  /* !LINKSTO MemAcc.EB.MemoryAccess.Compare.Page, 1 */
  /* !LINKSTO MemAcc.EB.MemoryAccess.BlankCheck.Page, 1 */
  else
#endif /* MEMACC_READ_BURST_SUPPORT */
  {
    ReadChunkSize = SectorBatchCfgPtr->ReadPageSize;
  }

  return ReadChunkSize;
}
#if ((MEMACC_ERASE_RETRY_SUPPORT == STD_ON) || (MEMACC_WRITE_RETRY_SUPPORT == STD_ON))
STATIC FUNC(boolean, MEMACC_CODE) MemAcc_HandleRetryOperations (MemAcc_AddressAreaIdType AddressAreaCfgIdx)
{
  boolean Retry = FALSE;
  MemAcc_AdminAddressAreaType *AdminAddressArea = &MemAcc_AdminAddressArea[AddressAreaCfgIdx];
  const MemAcc_AddressSubAreaType * const SubAreaCfgPtr = &MemAcc_AddressAreas[AddressAreaCfgIdx].SubAreaCfg[AdminAddressArea->SubAreaIdx];
  const MemAcc_JobType JobType = MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobType;

  /* !LINKSTO MemAcc.SWS_MemAcc_00100, 1 */
#if (MEMACC_WRITE_RETRY_SUPPORT == STD_ON)
  if( ( JobType == MEMACC_WRITE_JOB ) && ( AdminAddressArea->JobRetryCounter < SubAreaCfgPtr->NumberOfWriteRetries ) )
  {
    Retry = TRUE;
  }
  else
  {
    /* No write retry */
  }
#endif

  /* !LINKSTO MemAcc.SWS_MemAcc_00005, 1 */
#if (MEMACC_ERASE_RETRY_SUPPORT == STD_ON)
  if( ( JobType == MEMACC_ERASE_JOB ) && ( AdminAddressArea->JobRetryCounter < SubAreaCfgPtr->NumberOfEraseRetries ) )
  {
    Retry = TRUE;
  }
  else
  {
    /* No erase retry */
  }
#endif

  if(Retry)
  {
    AdminAddressArea->JobRetryCounter++;
  }
  else
  {
    /* Retry is not applicable due to
      - Job type is not Erase or Write,
      - The configured number of retries is zero, or
      - The number of retries is exceeded
    */
  }
  return Retry;
}
#endif


STATIC FUNC(MemAcc_AddressAreaIdType, MEMACC_CODE) MemAcc_FindLogicalAddressSubarea(MemAcc_AddressAreaIdType AddressAreaCfgIdx, MemAcc_AddressType LogicalAddress)
{
  MemAcc_AddressAreaIdType SubAreaIdx;
  MemAcc_AddressSubAreaType const *SubAreaCfgPtr;
  boolean SubAreaFound = FALSE;
  for (SubAreaIdx = 0; (SubAreaIdx < MemAcc_AddressAreas[AddressAreaCfgIdx].NumberOfSubAreas) && (SubAreaFound == FALSE); SubAreaIdx++)
  {
    SubAreaCfgPtr = &MemAcc_AddressAreas[AddressAreaCfgIdx].SubAreaCfg[SubAreaIdx];
    if(LogicalAddress <= ((SubAreaCfgPtr->LogicalStartAddress) + (SubAreaCfgPtr->Length -1U)))
    {
      SubAreaFound = TRUE;
    }
  }
  SubAreaIdx--;
  return SubAreaIdx;
}


STATIC FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_ValidateMemDataJobParams
(
    uint8                     ApiId,
    MemAcc_AddressAreaIdType  AddressAreaCfgIdx,
    MemAcc_AddressType        JobAddress,
    const MemAcc_DataType     *JobDataPtr,
    MemAcc_LengthType         Length
)
{
  /* !LINKSTO MemAcc.Request.InvalidParameter, 1 */
  /* !LINKSTO MemAcc.Request.MultipleRequestsForSameAreaReturnCode, 1 */
  Std_ReturnType Result = E_NOT_OK;

  if(AddressAreaCfgIdx == MEMACC_INVALID_ADDRESSAREA)
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00044, 1 */
    /* !LINKSTO MemAcc.SWS_MemAcc_00049, 1*/
    /* !LINKSTO MemAcc.SWS_MemAcc_00058, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
    MEMACC_DET_REPORT_ERROR(ApiId, MEMACC_E_PARAM_ADDRESS_AREA_ID);
#endif
  }
  else if(JobDataPtr == NULL_PTR)
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00045, 1 */
    /* !LINKSTO MemAcc.SWS_MemAcc_00050, 1*/
    /* !LINKSTO MemAcc.SWS_MemAcc_00059, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
    MEMACC_DET_REPORT_ERROR(ApiId,MEMACC_E_PARAM_POINTER);
#endif
  }
  else if(MEMACC_REQUEST_PARAM_OFFSET_INVALID(AddressAreaCfgIdx, JobAddress))
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00046, 1*/
    /* !LINKSTO MemAcc.SWS_MemAcc_00051, 1*/
    /* !LINKSTO MemAcc.SWS_MemAcc_00060, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
    MEMACC_DET_REPORT_ERROR(ApiId, MEMACC_E_PARAM_ADDRESS_LENGTH);
#endif
  }
  else if(MEMACC_REQUEST_PARAM_LENGTH_INVALID(AddressAreaCfgIdx, JobAddress, Length))
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00046, 1*/
    /* !LINKSTO MemAcc.SWS_MemAcc_00051, 1*/
    /* !LINKSTO MemAcc.SWS_MemAcc_00060, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
    MEMACC_DET_REPORT_ERROR(ApiId, MEMACC_E_PARAM_ADDRESS_LENGTH);
#endif
  }
  else
  {
    Result = E_OK;
  }

#if ( MEMACC_DEV_ERROR_DETECT != STD_ON )
  TS_PARAM_UNUSED(ApiId);
#endif

  return Result;
}


STATIC FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_ValidateMemOperationJobParams
(
    uint8                     ApiId,
    MemAcc_AddressAreaIdType  AddressAreaCfgIdx,
    MemAcc_AddressType        JobAddress,
    MemAcc_LengthType         Length
)
{
  /* !LINKSTO MemAcc.Request.InvalidParameter, 1 */
  /* !LINKSTO MemAcc.Request.MultipleRequestsForSameAreaReturnCode, 1 */
  Std_ReturnType Result = E_NOT_OK;

  if(AddressAreaCfgIdx == MEMACC_INVALID_ADDRESSAREA)
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00039, 1*/
    /* !LINKSTO MemAcc.SWS_MemAcc_00054, 1*/
    /* !LINKSTO MemAcc.SWS_MemAcc_00063, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
    MEMACC_DET_REPORT_ERROR(ApiId, MEMACC_E_PARAM_ADDRESS_AREA_ID);
#endif
  }
  else if(MEMACC_REQUEST_PARAM_OFFSET_INVALID(AddressAreaCfgIdx, JobAddress))
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00055, 1*/
    /* !LINKSTO MemAcc.SWS_MemAcc_00064, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
    MEMACC_DET_REPORT_ERROR(ApiId, MEMACC_E_PARAM_ADDRESS_LENGTH);
#endif
  }
  else if(MEMACC_REQUEST_PARAM_LENGTH_INVALID(AddressAreaCfgIdx, JobAddress, Length))
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00055, 1*/
    /* !LINKSTO MemAcc.SWS_MemAcc_00064, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
    MEMACC_DET_REPORT_ERROR(ApiId, MEMACC_E_PARAM_ADDRESS_LENGTH);
#endif
  }
  else
  {
    Result = E_OK;
  }

#if ( MEMACC_DEV_ERROR_DETECT != STD_ON )
  TS_PARAM_UNUSED(ApiId);
#endif

  return Result;
}


#if (MEMACC_LEGACY_DRIVER_SUPPORT == STD_ON)
STATIC FUNC(boolean, MEMACC_CODE) MemAcc_BlankCheckApisAvailable
(
  MemAcc_AddressAreaIdType AddressAreaCfgIdx,
  MemAcc_AddressType JobLogicalAddress,
  MemAcc_LengthType JobLength
)
{
  MemAcc_AddressSubAreaType const *SubAreaCfgPtr;
  MemAcc_HwIdType                 HwIdx;
  MemAcc_LengthType               RemainingLength;
  MemAcc_LengthType               SubAreaPossibleJobLength;
  MemAcc_AddressAreaIdType        SubAreaIdx;
  boolean                         DrvApisAvailable = TRUE;

  SubAreaIdx = MemAcc_FindLogicalAddressSubarea(AddressAreaCfgIdx, JobLogicalAddress);
  SubAreaCfgPtr = &MemAcc_AddressAreas[AddressAreaCfgIdx].SubAreaCfg[SubAreaIdx];

  HwIdx = SubAreaCfgPtr->DrvHwId;
  if(((MemAcc_MemApi_LegacyType const *)MemAcc_MemoryDevicesInfo[HwIdx].DrvApiTable)->BlankCheck != NULL_PTR)
  {
    /*avoid possible ovf for an end of memory sub-area*/
    SubAreaPossibleJobLength = ((SubAreaCfgPtr->LogicalStartAddress + (SubAreaCfgPtr->Length -1U))
                               - JobLogicalAddress + 1U);

    if(JobLength > SubAreaPossibleJobLength)
    {
      RemainingLength = JobLength - SubAreaPossibleJobLength;

      for(++SubAreaIdx; SubAreaIdx < MemAcc_AddressAreas[AddressAreaCfgIdx].NumberOfSubAreas; SubAreaIdx++)
      {
        SubAreaCfgPtr = &MemAcc_AddressAreas[AddressAreaCfgIdx].SubAreaCfg[SubAreaIdx];
        HwIdx = SubAreaCfgPtr->DrvHwId;
        if( ((MemAcc_MemApi_LegacyType const *)MemAcc_MemoryDevicesInfo[HwIdx].DrvApiTable)->BlankCheck != NULL_PTR)
        {
          if(RemainingLength <= SubAreaCfgPtr->Length)
          {
            break;
          }
          else/*Job Spans Other SubArea*/
          {
            RemainingLength -= SubAreaCfgPtr->Length;
          }
        }
        else
        {
          DrvApisAvailable = FALSE;
          break;
        }
      }
    }
    else
    { /*availability already set, nothing to do*/
    }
  }
  else
  {
    DrvApisAvailable = FALSE;
  }
  return DrvApisAvailable;
}
#endif /* MEMACC_LEGACY_DRIVER_SUPPORT */
/*--------------------------[MemAcc_GetAddressAreaConfigIndex]---------------------------------------*/
STATIC FUNC(MemAcc_AddressAreaIdType, MEMACC_CODE) MemAcc_GetAddressAreaConfigIndex (MemAcc_AddressAreaIdType AddressAreaId)
{
  MemAcc_AddressAreaIdType AddressAreaCfgStartIdx  = 0U;
  MemAcc_AddressAreaIdType AddressAreaCfgMiddleIdx = 0U;
  MemAcc_AddressAreaIdType AddressAreaCfgEndIdx    = MEMACC_NB_OF_CONFIGURED_ADDRESSAREAS - 1U;
  MemAcc_AddressAreaIdType AddressAreaCfgIdx       = MEMACC_INVALID_ADDRESSAREA;
  MemAcc_AddressAreaIdType CurrAddressAreaId       = 0U;

  /* MemAcc_AddressAreas array is sorted during the generation based on AddressAreaId */
  while(AddressAreaCfgStartIdx <= AddressAreaCfgEndIdx)
  {
    AddressAreaCfgMiddleIdx = (AddressAreaCfgStartIdx + AddressAreaCfgEndIdx)/2U;
    CurrAddressAreaId = MemAcc_AddressAreas[AddressAreaCfgMiddleIdx].AddressAreaId;
    if(AddressAreaId == CurrAddressAreaId)
    {
      AddressAreaCfgIdx = AddressAreaCfgMiddleIdx;
      break;
    }
    else if(AddressAreaId < CurrAddressAreaId)
    {
      AddressAreaCfgEndIdx = AddressAreaCfgMiddleIdx - 1U;
    }
    else
    {
      AddressAreaCfgStartIdx = AddressAreaCfgMiddleIdx + 1U;
    }
  }
  return AddressAreaCfgIdx;
}

/*--------------------------[MemAcc_AddDeviceRequest]---------------------------------------*/
STATIC FUNC(void, MEMACC_CODE) MemAcc_AddDeviceRequest
(
  MemAcc_AddressAreaIdType AddressAreaCfgIdx,
  MemAcc_AddressType JobLogicalAddress,
  const MemAcc_DataType *UserDataPtr,
  MemAcc_LengthType JobLength
)
{
  MemAcc_AddressAreaIdType SubAreaIdx;
  MemAcc_AddressSubAreaAdminType * SubAreaAdminPtr;
  const MemAcc_AddressSubAreaType * SubAreaCfgPtr;
  MemAcc_AddressType SubAreaEndAddress;

  MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobLogicalAddress = JobLogicalAddress;
  MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobLength = JobLength;
  MemAcc_AdminAddressArea[AddressAreaCfgIdx].ProcessedLength = 0;
  MemAcc_AdminAddressArea[AddressAreaCfgIdx].MemLength = 0;
#if ((MEMACC_ERASE_RETRY_SUPPORT == STD_ON) || (MEMACC_WRITE_RETRY_SUPPORT == STD_ON))
  MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobRetryCounter = 0;
#endif
  /* !LINKSTO MemAcc.SWS_MemAcc_00020, 1*/
  MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobStatus = MEMACC_JOB_PENDING;
  /* !LINKSTO MemAcc.EB.GetJobResult.Init.NewRequest, 1*/
  MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobResult = MEMACC_MEM_OK;

  /*Handle first sub-area, job might start anywhere inside*/
  SubAreaIdx = MemAcc_FindLogicalAddressSubarea(AddressAreaCfgIdx, JobLogicalAddress);
  MemAcc_AdminAddressArea[AddressAreaCfgIdx].SubAreaIdx = SubAreaIdx;


  SubAreaCfgPtr = &MemAcc_AddressAreas[AddressAreaCfgIdx].SubAreaCfg[SubAreaIdx];

  SubAreaAdminPtr = &MemAcc_AdminAddressArea[AddressAreaCfgIdx].SubAreaAdmin;
  /* !LINKSTO MemAcc.Dsn.SubAreaJobState.NewJob, 1*/
  SubAreaAdminPtr->JobState = MEMACC_WAITING;
  SubAreaAdminPtr->JobPhysicalStartAddress = SubAreaCfgPtr->PhysicalStartAddress
                                            +(JobLogicalAddress - SubAreaCfgPtr->LogicalStartAddress);
  SubAreaAdminPtr->UserDataPtr =  UserDataPtr;

  SubAreaEndAddress = SubAreaCfgPtr->LogicalStartAddress + (SubAreaCfgPtr->Length - 1U);

  if((JobLogicalAddress + (JobLength - 1U)) <= SubAreaEndAddress)
  {/*Job ends in this first subArea*/
    SubAreaAdminPtr->RemainingLength = JobLength;
  }
  else
  {
    /*Job Spans Other SubArea*/
    SubAreaAdminPtr->RemainingLength = (SubAreaEndAddress - JobLogicalAddress) + 1U;
  }

  SchM_Enter_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_1();
  MemAcc_JobRequestsBuffer[MemAcc_JobRequestsBufferElementsNo] = AddressAreaCfgIdx;
  MemAcc_JobRequestsBufferElementsNo++;
  SchM_Exit_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_1();
}
/*--------------------------[MemAcc_AreaInProgressJobState]---------------------------------------*/
STATIC FUNC(boolean, MEMACC_CODE) MemAcc_AreaInProgressJobState (MemAcc_AddressAreaIdType AddressAreaCfgIdx)
{
  MemAcc_AdminAddressAreaType *AdminAddressArea = &MemAcc_AdminAddressArea[AddressAreaCfgIdx];
  boolean TriggerJob = FALSE;
  MemAcc_AddressSubAreaAdminType *SubAreaAdminPtr = &(AdminAddressArea->SubAreaAdmin);
  const MemAcc_AddressSubAreaType * SubAreaCfgPtr;
  MemAcc_LengthType RemainingLength;

  switch (SubAreaAdminPtr->MemDrvJobResult)
  {
  /* !LINKSTO MemAcc.SWS_MemAcc_00028, 1*/
  case MEM_JOB_OK:
#if ((MEMACC_ERASE_RETRY_SUPPORT == STD_ON) || (MEMACC_WRITE_RETRY_SUPPORT == STD_ON))
    AdminAddressArea->JobRetryCounter = 0;
#endif
#if (MEMACC_COMPARE_API == STD_ON)
    /* Deviation MISRAC2012-2 */
    if((AdminAddressArea->JobType == MEMACC_COMPARE_JOB)
        &&
        (
            TS_MemCmp(MemAcc_AddressAreas[AddressAreaCfgIdx].AddressAreaCmpBuffer,
            (SubAreaAdminPtr->UserDataPtr - AdminAddressArea->MemLength),
            AdminAddressArea->MemLength) != E_OK)
        )
    {
      /* !LINKSTO MemAcc.Request.Inconsistent.Compare , 1 */
      /* !LINKSTO MemAcc.Compare.JobResult.Mismatch, 1 */
      AdminAddressArea->JobResult = MEMACC_MEM_INCONSISTENT;
    }
    else
#endif
    {
      if((SubAreaAdminPtr->RemainingLength) > 0U )
      {
        TriggerJob = TRUE;
      }
      else
      {
        /* !LINKSTO MemAcc.Dsn.SubAreaJobState.JobDone, 1*/
        /*sub area completed*/
        SubAreaAdminPtr->JobState = MEMACC_IDLE;
        /*After one area is completed check if any more is needed, if not, complete Area Job*/
        if(AdminAddressArea->ProcessedLength == AdminAddressArea->JobLength)
        {
          /* !LINKSTO MemAcc.SWS_MemAcc_00105, 1*/
          /* !LINKSTO MemAcc.Compare.JobResult.Match, 1*/
          /* !LINKSTO MemAcc.Dsn.Interaction.Polling.JobResult, 1*/
          /* !LINKSTO MemAcc.Dsn.Interaction.Cbk.CancelFinishedJob, 1*/
          AdminAddressArea->JobResult = MEMACC_MEM_OK;
          /* !LINKSTO MemAcc.SWS_MemAcc_00104, 1*/
          AdminAddressArea->JobStatus = MEMACC_JOB_IDLE;
        }
        else
        {
          AdminAddressArea->SubAreaIdx++;
          SubAreaCfgPtr = &MemAcc_AddressAreas[AddressAreaCfgIdx].SubAreaCfg[AdminAddressArea->SubAreaIdx];

          SubAreaAdminPtr->JobPhysicalStartAddress = SubAreaCfgPtr->PhysicalStartAddress;

          RemainingLength = AdminAddressArea->JobLength - AdminAddressArea->ProcessedLength;

          if(RemainingLength <= SubAreaCfgPtr->Length)
          {
            SubAreaAdminPtr->RemainingLength = RemainingLength;
          }
          else
          {
            SubAreaAdminPtr->RemainingLength = SubAreaCfgPtr->Length;
          }
          TriggerJob = TRUE;
        }
      }
    }
    break;
  case MEM_JOB_PENDING:
    /* do nothing this cycle, job still ongoing
     * and cancel request is handled only at driver operation end
     */
    break;
  default:
    /*ongoing sub-area job failed, job for AreaId is terminated*/
    if(SubAreaAdminPtr->MemDrvJobResult == MEM_INCONSISTENT)
    {
      /* !LINKSTO MemAcc.Dsn.Interaction.Polling.JobResult, 1*/
      /* !LINKSTO MemAcc.Dsn.Interaction.Cbk.CancelFinishedJob, 1*/
      /* !LINKSTO MemAcc.Request.Inconsistent.BlankCheck, 1 */
      AdminAddressArea->JobResult = MEMACC_MEM_INCONSISTENT;
    }
    else
    {
#if ((MEMACC_ERASE_RETRY_SUPPORT == STD_ON) || (MEMACC_WRITE_RETRY_SUPPORT==STD_ON))
      if(MemAcc_HandleRetryOperations(AddressAreaCfgIdx))
      {
        SubAreaAdminPtr->RemainingLength += AdminAddressArea->MemLength;
        AdminAddressArea->ProcessedLength -= AdminAddressArea->MemLength;
        SubAreaAdminPtr->JobPhysicalStartAddress -= AdminAddressArea->MemLength;
        if(SubAreaAdminPtr->UserDataPtr != NULL_PTR)
        {
          SubAreaAdminPtr->UserDataPtr -= AdminAddressArea->MemLength;
        }
        else
        {
          /*Job type without user data*/
        }

        TriggerJob = TRUE;
      }
      else
#endif
      {
        /* !LINKSTO MemAcc.Dsn.Interaction.Polling.JobResult, 1*/
        /* !LINKSTO MemAcc.Dsn.Interaction.Cbk.CancelFinishedJob, 1*/
        /* !LINKSTO MemAcc.SWS_MemAcc_00109, 1*/
        AdminAddressArea->JobResult = MEMACC_MEM_FAILED;
      }
    }
    break;
  }

  return TriggerJob;
}

/*--------------------------[MemAcc_AreaJobStateMachine]---------------------------------------*/
STATIC FUNC(void, MEMACC_CODE) MemAcc_AreaLockStateMachine (MemAcc_AddressAreaIdType AddressAreaCfgIdx, MemAcc_AddressAreaLockType * LockRequest)
{
  boolean LockStateRequest = FALSE;
  boolean LockStateChangeRequest = FALSE;
  ApplicationLockNotification LockNotificationFcn = NULL_PTR;
  MemAcc_AddressSubAreaAdminType *SubAreaAdminPtr;
  MemAcc_AdminAddressAreaType *AdminAddressArea = &MemAcc_AdminAddressArea[AddressAreaCfgIdx];

  SubAreaAdminPtr = &(AdminAddressArea->SubAreaAdmin);

  /* !LINKSTO MemAcc.SWS_MemAcc_00116, 1*/

  LockStateRequest = LockRequest->Lock;
  LockNotificationFcn = LockRequest->AddressAreaLockNotification;
  LockStateChangeRequest = LockRequest->LockStateChangeRequest;

  switch (AdminAddressArea->AddressAreaLockState)
  {
  case MEMACC_ADDRESSAREA_UNLOCKED:
    if(LockStateRequest == TRUE)
    {
      if(AdminAddressArea->JobType != MEMACC_NO_JOB)
      {
        if(SubAreaAdminPtr->JobState == MEMACC_INPROGRESS)
        {
          if(SubAreaAdminPtr->MemDrvJobResult != MEM_JOB_PENDING)
          {
            AdminAddressArea->AddressAreaLockState = MEMACC_ADDRESSAREA_LOCKED;
            LockNotificationFcn();
          }
          else
          {
            /*we'll wait for current memory driver operation end,
             * triggering new driver requests will be disabled*/
            AdminAddressArea->AddressAreaLockState = MEMACC_ADDRESSAREA_LOCK_REQUESTED;
          }
        }
        else
        {
          AdminAddressArea->AddressAreaLockState = MEMACC_ADDRESSAREA_LOCKED;
          LockNotificationFcn();
        }
      }
      else
      {
        AdminAddressArea->AddressAreaLockState = MEMACC_ADDRESSAREA_LOCKED;
        LockNotificationFcn();
      }
    }
    else
    {
    }
    break;
  case MEMACC_ADDRESSAREA_LOCKED:
    if(LockStateRequest == FALSE)
    {
      AdminAddressArea->AddressAreaLockState = MEMACC_ADDRESSAREA_UNLOCKED;
    }
    else
    {
      if(LockStateChangeRequest == TRUE)
      {
        LockNotificationFcn();
      }
    }
    break;
  case MEMACC_ADDRESSAREA_LOCK_REQUESTED:
    if((LockStateChangeRequest == TRUE) && (LockStateRequest == FALSE))
    {
      AdminAddressArea->AddressAreaLockState = MEMACC_ADDRESSAREA_UNLOCKED;
    }
    else
    {
      if(SubAreaAdminPtr->MemDrvJobResult != MEM_JOB_PENDING)
      {
        AdminAddressArea->AddressAreaLockState = MEMACC_ADDRESSAREA_LOCKED;
        LockNotificationFcn();
      }
    }
    break;
  /* CHECK: NOPARSE */
  default:
    /* Unknown state, should not be reached*/
    break;
  /* CHECK: PARSE */
  }
}

/*--------------------------[MemAcc_AreaJobStateMachine]---------------------------------------*/
STATIC FUNC(void, MEMACC_CODE) MemAcc_AreaJobStateMachine (MemAcc_AddressAreaIdType AddressAreaCfgIdx)
{
  MemAcc_Mem_JobResultType DriverJobResult;

  Std_ReturnType TriggerJobResult = E_NOT_OK;
  boolean TriggerJob = FALSE;
  boolean CheckCancelRequest = FALSE;
  MemAcc_AddressSubAreaAdminType *SubAreaAdminPtr;
  MemAcc_AdminAddressAreaType *AdminAddressArea = &MemAcc_AdminAddressArea[AddressAreaCfgIdx];

  SubAreaAdminPtr = &(AdminAddressArea->SubAreaAdmin);
  switch(SubAreaAdminPtr->JobState)
  {
  case MEMACC_WAITING:
    CheckCancelRequest = TRUE;
    if(AdminAddressArea->AddressAreaLockState == MEMACC_ADDRESSAREA_UNLOCKED)
    {
      TriggerJob = TRUE;
    }
    break;
  case MEMACC_INPROGRESS:
    TriggerJob = MemAcc_AreaInProgressJobState(AddressAreaCfgIdx);
    CheckCancelRequest = TriggerJob;
    if((TriggerJob == TRUE) && (AdminAddressArea->AddressAreaLockState != MEMACC_ADDRESSAREA_UNLOCKED))
    {
      SubAreaAdminPtr->JobState = MEMACC_WAITING;
      TriggerJob = FALSE;
    }
    break;
  /* CHECK: NOPARSE */
  case MEMACC_IDLE:
    break;
  default:
    /* Unknown state, should not be reached*/
    break;
  /* CHECK: PARSE */
  }

  if(CheckCancelRequest == TRUE)
  {
    if(MemAcc_CancelRequests[AddressAreaCfgIdx] == TRUE)
    {
      /* !LINKSTO MemAcc.Dsn.Interaction.Polling.Canceled, 1*/
      /* !LINKSTO MemAcc.Dsn.Interaction.Cbk.Canceled, 1*/
      /* !LINKSTO MemAcc.SWS_MemAcc_00028, 1*/
      AdminAddressArea->JobResult = MEMACC_MEM_CANCELED;
      TriggerJob = FALSE;
    }
    else
    {/*continue processing*/
    }
  }

  if(TriggerJob)
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00006, 1 */
    DriverJobResult = MemAcc_GetDriverJobResult(AddressAreaCfgIdx);
    if(DriverJobResult != MEM_JOB_PENDING)
    {
      TriggerJobResult = MemAcc_TriggerJob(AddressAreaCfgIdx);
      if (TriggerJobResult == E_NOT_OK)
      {
        /* !LINKSTO MemAcc.SWS_MemAcc_00109, 1*/
        AdminAddressArea->JobResult = MEMACC_MEM_FAILED;
      }
      else
      {
        /* !LINKSTO MemAcc.Dsn.SubAreaJobState.JobRequested, 1*/
        SubAreaAdminPtr->JobState = MEMACC_INPROGRESS;
      }
    }
    else
    {
      /* !LINKSTO MemAcc.Dsn.SubAreaJobState.BusyDriver, 1*/
      SubAreaAdminPtr->JobState = MEMACC_WAITING;
    }
  }
  else
  {/*idle, locked or canceled*/
  }

  /*Job result is set to MEMACC_MEM_OK when job is started;
   * and changed only at job end
   * tdo: according to published SWS, JobResult shall not be set to OK at new request...
   */
  if(AdminAddressArea->JobResult != MEMACC_MEM_OK)
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00104, 1*/
    AdminAddressArea->JobStatus = MEMACC_JOB_IDLE;
  }
  else
  {
    /* The current job is sill in progress */
  }

  if(AdminAddressArea->JobStatus != MEMACC_JOB_PENDING)
  {
    AdminAddressArea->SubAreaAdmin.JobState = MEMACC_IDLE;
  }
  else
  {
    /*continue processing this area next main cycle*/
  }
}
#define MEMACC_STOP_SEC_CODE
#include <MemAcc_MemMap.h>


/*==================[external function definitions]==========================*/

#define MEMACC_START_SEC_CODE
#include <MemAcc_MemMap.h>


/*--------------------------[MemAcc_Init]---------------------------------------*/
/* !LINKSTO MemAcc.Dsn.Interfaces.Init, 1*/
FUNC(void, MEMACC_CODE) MemAcc_Init (const MemAcc_ConfigType* ConfigPtr)
{
  MemAcc_AddressAreaIdType AddressAreaCfgIdx = 0;

#if (MEMACC_HANDLING_SUPPORT == STD_ON)
  MemAcc_HwIdType HwIdx;
  Mem_ConfigType DriverConfigPtr;
  MemAcc_MemInstanceIdType InstanceIdx = 0;
#endif /* #if (MEMACC_HANDLING_SUPPORT == STD_ON) */

  TS_PARAM_UNUSED(ConfigPtr); /*post build configuration is not supported yet*/

  DBG_MEMACC_INIT_ENTRY();

  MemAcc_JobRequestsBufferElementsNo = 0;

  MemAcc_Queue_Init();

  for(AddressAreaCfgIdx = 0; AddressAreaCfgIdx < MEMACC_NB_OF_CONFIGURED_ADDRESSAREAS; AddressAreaCfgIdx++)
  {
    MemAcc_CancelRequests[AddressAreaCfgIdx] = FALSE;
    MemAcc_LockRequests[AddressAreaCfgIdx] = LockRequestInit;
    MemAcc_JobRequestsBuffer[AddressAreaCfgIdx] = MEMACC_QUEUE_INVALID_AREA_INDEX;


    /* !LINKSTO MemAcc.SWS_MemAcc_00112, 1*/
    MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobResult = MEMACC_MEM_OK;
    /* !LINKSTO MemAcc.SWS_MemAcc_00113, 1*/
    MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobStatus = MEMACC_JOB_IDLE;
    MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobType   = MEMACC_NO_JOB;
    MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobLength = 0;
    MemAcc_AdminAddressArea[AddressAreaCfgIdx].MemLength = 0;
    MemAcc_AdminAddressArea[AddressAreaCfgIdx].LastActiveSubAreaIdx = 0;
    MemAcc_AdminAddressArea[AddressAreaCfgIdx].AddressAreaLockState = MEMACC_ADDRESSAREA_UNLOCKED;
#if ((MEMACC_ERASE_RETRY_SUPPORT == STD_ON) || (MEMACC_WRITE_RETRY_SUPPORT == STD_ON))
    MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobRetryCounter = 0;
#endif
      /* !LINKSTO MemAcc.Dsn.SubAreaJobState.Init, 1*/
    MemAcc_AdminAddressArea[AddressAreaCfgIdx].SubAreaAdmin.JobState = MEMACC_IDLE;
  }

  MemAcc_InitStatus = TRUE;

  DBG_MEMACC_INIT_EXIT();
}


/*--------------------------[MemAcc_Read]---------------------------------------*/
/* !LINKSTO MemAcc.Dsn.Interfaces.Read, 1*/
FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_Read
(
  MemAcc_AddressAreaIdType AddressAreaId,
  MemAcc_AddressType SourceAddress,
  MemAcc_DataType *DestinationDataPtr,
  MemAcc_LengthType Length
)
{
  Std_ReturnType Result = E_NOT_OK;
  MemAcc_AddressAreaIdType AddressAreaCfgIdx;

  DBG_MEMACC_READ_ENTRY(AddressAreaId, SourceAddress, DestinationDataPtr, Length);

  if(MemAcc_InitStatus)
  {
    AddressAreaCfgIdx = MemAcc_GetAddressAreaConfigIndex(AddressAreaId);
    Result = MemAcc_ValidateMemDataJobParams(MEMACC_READ_API_ID, AddressAreaCfgIdx, SourceAddress, DestinationDataPtr, Length);
    if( Result == E_OK)
    {
      SchM_Enter_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_0();
      /* !LINKSTO MemAcc.SWS_MemAcc_00018, 1 */
      if(MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobType != MEMACC_NO_JOB)
      {
        SchM_Exit_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_0();

        Result = E_NOT_OK;
        /* !LINKSTO MemAcc.SWS_MemAcc_00047, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
        MEMACC_DET_REPORT_ERROR(MEMACC_READ_API_ID, MEMACC_E_BUSY);
#endif
      }
      else
      {
        /* !LINKSTO MemAcc.SWS_MemAcc_00008, 1*/
        MemAcc_CancelRequests[AddressAreaCfgIdx] = FALSE;
        MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobType = MEMACC_READ_JOB;
        SchM_Exit_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_0();

        MemAcc_AddDeviceRequest(AddressAreaCfgIdx, SourceAddress, DestinationDataPtr, Length);
      }
    }
  }
  else
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00043, 1*/
    #if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
        MEMACC_DET_REPORT_ERROR(MEMACC_READ_API_ID, MEMACC_E_UNINIT);
    #endif
  }

  DBG_MEMACC_READ_EXIT(Result, AddressAreaId, SourceAddress, DestinationDataPtr, Length);
  return Result;
}


/*--------------------------[MemAcc_Write]---------------------------------------*/
/* !LINKSTO MemAcc.Dsn.Interfaces.Write, 1 */
FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_Write
(
  MemAcc_AddressAreaIdType AddressAreaId,
  MemAcc_AddressType TargetAddress,
  const MemAcc_DataType* SourceDataPtr,
  MemAcc_LengthType Length
)
{
  Std_ReturnType Result = E_NOT_OK;
  MemAcc_AddressAreaIdType AddressAreaCfgIdx;

  DBG_MEMACC_WRITE_ENTRY(AddressAreaId, TargetAddress, SourceDataPtr, Length);
  if(MemAcc_InitStatus)
  {
    AddressAreaCfgIdx = MemAcc_GetAddressAreaConfigIndex(AddressAreaId);
    Result = MemAcc_ValidateMemDataJobParams(MEMACC_WRITE_API_ID,AddressAreaCfgIdx, TargetAddress, SourceDataPtr, Length);
    if( Result == E_OK)
    {
      SchM_Enter_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_0();
      /* !LINKSTO MemAcc.SWS_MemAcc_00018, 1 */
      if(MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobType != MEMACC_NO_JOB)
      {
        SchM_Exit_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_0();

        Result = E_NOT_OK;
        /* !LINKSTO MemAcc.SWS_MemAcc_00052, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
        MEMACC_DET_REPORT_ERROR(MEMACC_WRITE_API_ID, MEMACC_E_BUSY);
#endif
      }
      else
      {
        /* !LINKSTO MemAcc.SWS_MemAcc_00008, 1*/
        MemAcc_CancelRequests[AddressAreaCfgIdx] = FALSE;
        MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobType = MEMACC_WRITE_JOB;
        SchM_Exit_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_0();

        MemAcc_AddDeviceRequest(AddressAreaCfgIdx, TargetAddress, SourceDataPtr, Length);
      }
    }
  }
  else
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00048, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
    MEMACC_DET_REPORT_ERROR(MEMACC_WRITE_API_ID, MEMACC_E_UNINIT);
#endif
  }
  DBG_MEMACC_WRITE_EXIT(Result, AddressAreaId, TargetAddress, SourceDataPtr, Length);
  return Result;
}


/*--------------------------[MemAcc_Erase]---------------------------------------*/
/* !LINKSTO MemAcc.Dsn.Interfaces.Erase, 1*/
FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_Erase
(
  MemAcc_AddressAreaIdType AddressAreaId,
  MemAcc_AddressType TargetAddress,
  MemAcc_LengthType Length
)
{
  Std_ReturnType Result = E_NOT_OK;
  MemAcc_AddressAreaIdType AddressAreaCfgIdx;

  DBG_MEMACC_ERASE_ENTRY(AddressAreaId, TargetAddress, Length);
  if(MemAcc_InitStatus)
  {
    AddressAreaCfgIdx = MemAcc_GetAddressAreaConfigIndex(AddressAreaId);
    Result = MemAcc_ValidateMemOperationJobParams(MEMACC_ERASE_API_ID, AddressAreaCfgIdx, TargetAddress, Length);
    if( Result == E_OK)
    {
      SchM_Enter_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_0();
      /* !LINKSTO MemAcc.SWS_MemAcc_00018, 1 */
      if(MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobType != MEMACC_NO_JOB)
      {
        SchM_Exit_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_0();

        Result = E_NOT_OK;
        /* !LINKSTO MemAcc.SWS_MemAcc_00056, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
        MEMACC_DET_REPORT_ERROR(MEMACC_ERASE_API_ID, MEMACC_E_BUSY);
#endif
      }
      else
      {
        /* !LINKSTO MemAcc.SWS_MemAcc_00008, 1*/
        MemAcc_CancelRequests[AddressAreaCfgIdx] = FALSE;
        MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobType = MEMACC_ERASE_JOB;
        SchM_Exit_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_0();

        MemAcc_AddDeviceRequest(AddressAreaCfgIdx, TargetAddress, NULL_PTR, Length);
      }
    }
  }
  else
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00053, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
    MEMACC_DET_REPORT_ERROR(MEMACC_ERASE_API_ID, MEMACC_E_UNINIT);
#endif
  }

  DBG_MEMACC_ERASE_EXIT(Result, AddressAreaId, TargetAddress, Length);
  return Result;
}


#if (MEMACC_COMPARE_API == STD_ON)
/*--------------------------[MemAcc_Compare]---------------------------------------*/
/* !LINKSTO MemAcc.Dsn.Interfaces.Compare, 1*/
FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_Compare
(
  MemAcc_AddressAreaIdType AddressAreaId,
  MemAcc_AddressType SourceAddress,
  const MemAcc_DataType *DataPtr,
  MemAcc_LengthType Length
)
{
  Std_ReturnType Result = E_NOT_OK;
  MemAcc_AddressAreaIdType AddressAreaCfgIdx;

  DBG_MEMACC_COMPARE_ENTRY(AddressAreaId, SourceAddress, DataPtr, Length);

  if(MemAcc_InitStatus)
  {
    AddressAreaCfgIdx = MemAcc_GetAddressAreaConfigIndex(AddressAreaId);
    Result = MemAcc_ValidateMemDataJobParams(MEMACC_COMPARE_API_ID,AddressAreaCfgIdx, SourceAddress, DataPtr, Length);
    if( Result == E_OK)
    {
      SchM_Enter_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_0();
      /* !LINKSTO MemAcc.SWS_MemAcc_00018, 1 */
      if(MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobType != MEMACC_NO_JOB)
      {
        SchM_Exit_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_0();

        Result = E_NOT_OK;
        /* !LINKSTO MemAcc.SWS_MemAcc_00061, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
        MEMACC_DET_REPORT_ERROR(MEMACC_COMPARE_API_ID, MEMACC_E_BUSY);
#endif
      }
      else
      {
        /* !LINKSTO MemAcc.SWS_MemAcc_00008, 1*/
        MemAcc_CancelRequests[AddressAreaCfgIdx] = FALSE;
        MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobType = MEMACC_COMPARE_JOB;
        SchM_Exit_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_0();

        MemAcc_AddDeviceRequest(AddressAreaCfgIdx, SourceAddress, DataPtr, Length);
      }
    }
  }
  else
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00057, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
    MEMACC_DET_REPORT_ERROR(MEMACC_COMPARE_API_ID, MEMACC_E_UNINIT);
#endif
  }

  DBG_MEMACC_COMPARE_EXIT(Result, AddressAreaId, SourceAddress, DataPtr, Length);
  return Result;
}
#endif


/*--------------------------[MemAcc_BlankCheck]---------------------------------------*/
/* !LINKSTO MemAcc.Dsn.Interfaces.BlankCheck, 1*/
FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_BlankCheck
(
  MemAcc_AddressAreaIdType AddressAreaId,
  MemAcc_AddressType TargetAddress,
  MemAcc_LengthType Length
)
{
  MemAcc_AddressAreaIdType AddressAreaCfgIdx;
  Std_ReturnType Result = E_NOT_OK;


  DBG_MEMACC_BLANKCHECK_ENTRY(AddressAreaId, TargetAddress, Length);

  if(MemAcc_InitStatus)
  {
    AddressAreaCfgIdx = MemAcc_GetAddressAreaConfigIndex(AddressAreaId);
    Result = MemAcc_ValidateMemOperationJobParams(MEMACC_BLANK_CHECK_API_ID, AddressAreaCfgIdx, TargetAddress, Length);
    if( Result == E_OK)
    {
      /*check all sub-areas to which driver they belong*/
#if (MEMACC_LEGACY_DRIVER_SUPPORT == STD_ON)
      if(MemAcc_BlankCheckApisAvailable(AddressAreaCfgIdx, TargetAddress, Length))
#endif /* MEMACC_LEGACY_DRIVER_SUPPORT */
      {
        SchM_Enter_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_0();
        /* !LINKSTO MemAcc.SWS_MemAcc_00018, 1 */
        if(MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobType != MEMACC_NO_JOB)
        {
          SchM_Exit_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_0();

          Result = E_NOT_OK;
          /* !LINKSTO MemAcc.SWS_MemAcc_00065, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
          MEMACC_DET_REPORT_ERROR(MEMACC_BLANK_CHECK_API_ID, MEMACC_E_BUSY);
#endif
        }
        else
        {
          /* !LINKSTO MemAcc.SWS_MemAcc_00008, 1*/
          MemAcc_CancelRequests[AddressAreaCfgIdx] = FALSE;
          MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobType = MEMACC_BLANKCHECK_JOB;
          SchM_Exit_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_0();

          MemAcc_AddDeviceRequest(AddressAreaCfgIdx, TargetAddress, NULL_PTR, Length);
        }
      }
#if (MEMACC_LEGACY_DRIVER_SUPPORT == STD_ON)
      else
      {
        Result = MEMACC_MEM_SERVICE_NOT_AVAIL;
      }
#endif /* MEMACC_LEGACY_DRIVER_SUPPORT */
    }
    else
    {
      /* Invalid parameters, return NOK to caller*/
    }
  }
  else
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00062, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
    MEMACC_DET_REPORT_ERROR(MEMACC_BLANK_CHECK_API_ID, MEMACC_E_UNINIT);
#endif
  }

  DBG_MEMACC_BLANKCHECK_EXIT(Result, AddressAreaId, TargetAddress, Length);
  return Result;
}

/*--------------------------[MemAcc_GetDriverJobResult]---------------------------------------*/
STATIC FUNC(MemAcc_Mem_JobResultType, MEMACC_CODE) MemAcc_GetDriverJobResult(
    MemAcc_AddressAreaIdType AddressAreaCfgIdx
  )
{
  MemAcc_Mem_JobResultType  MemJobResult = MEM_JOB_FAILED;
  MemAcc_HwIdType HwIdx = MemAcc_AddressAreas[AddressAreaCfgIdx].SubAreaCfg[MemAcc_AdminAddressArea[AddressAreaCfgIdx].SubAreaIdx].DrvHwId;
#if (MEMACC_LEGACY_DRIVER_SUPPORT == STD_ON)
  MemAcc_MemInvocationType DrvInvocationType = MemAcc_MemoryDevicesInfo[HwIdx].DrvInvocationType;
  MemIf_JobResultType MemIfJobResult;
  if(DrvInvocationType == DIRECT_LEGACY)
  {
    MemIfJobResult = ((const MemAcc_MemApi_LegacyType*)MemAcc_MemoryDevicesInfo[HwIdx].DrvApiTable)->GetJobResult();
    switch (MemIfJobResult)
    {
    case MEMIF_JOB_OK:
      MemJobResult = MEM_JOB_OK;
      break;
    case MEMIF_JOB_PENDING:
      MemJobResult = MEM_JOB_PENDING;
      break;
    case MEMIF_BLOCK_INCONSISTENT:
      MemJobResult = MEM_INCONSISTENT;
      break;
    case MEMIF_JOB_FAILED:
      MemJobResult = MEM_JOB_FAILED;
      break;
    default:
      MemJobResult = MEM_JOB_FAILED;
      break;
    }
  }
  else
#endif /* MEMACC_LEGACY_DRIVER_SUPPORT */
  {

#if (MEMACC_MEM_DRIVER_SUPPORT == STD_ON)
    MemJobResult = ((const MemAcc_MemApi_Type*)MemAcc_MemoryDevicesInfo[HwIdx].DrvApiTable)->GetJobResult(MemAcc_MemoryDevicesInfo[HwIdx].MemInstanceId);
#endif /* MEMACC_MEM_DRIVER_SUPPORT */
  }
  return MemJobResult;
}
/*--------------------------[MemAcc_GetOngoingJobResults]---------------------------------------*/
STATIC FUNC(void, MEMACC_CODE) MemAcc_GetOngoingJobResults(void)
{
  MemAcc_AddressAreaIdType SearchQueueIdx;
  MemAcc_AddressAreaIdType AddressAreaCfgIdx;
  MemAcc_Mem_JobResultType JobResult;


  for(SearchQueueIdx = 0; SearchQueueIdx < MemAcc_QueueElementsNo; SearchQueueIdx++)
  {
    AddressAreaCfgIdx = MemAcc_AreaIdQueue[SearchQueueIdx];
    /*no need to protect admin data here
     * since SubAreaAdmin for a started job is not overwritten by any API*/
    if(MemAcc_AdminAddressArea[AddressAreaCfgIdx].SubAreaAdmin.JobState == MEMACC_INPROGRESS)
    {
      JobResult = MemAcc_GetDriverJobResult(AddressAreaCfgIdx);

      MemAcc_AdminAddressArea[AddressAreaCfgIdx].SubAreaAdmin.MemDrvJobResult = JobResult;
    }
  }
}


/*--------------------------[MemAcc_TriggerJob]---------------------------------------*/
STATIC FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_TriggerJob
(
  MemAcc_AddressAreaIdType AddressAreaCfgIdx
)
{
  MemAcc_AdminAddressAreaType *AdminAddressArea = &MemAcc_AdminAddressArea[AddressAreaCfgIdx];
  Std_ReturnType Result = E_NOT_OK;
  MemAcc_AddressAreaIdType SubAreaIdx = AdminAddressArea->SubAreaIdx;
  MemAcc_HwIdType HwIdx = MemAcc_AddressAreas[AddressAreaCfgIdx].SubAreaCfg[SubAreaIdx].DrvHwId;
  MemAcc_AddressSubAreaAdminType * const SubAreaAdminPtr = &(AdminAddressArea->SubAreaAdmin);
#if ( (MEMACC_WRITE_BURST_SUPPORT == STD_ON) \
    ||(MEMACC_ERASE_BURST_SUPPORT == STD_ON) \
    )
  const MemAcc_AddressSubAreaType * const SubAreaCfgPtr = &MemAcc_AddressAreas[AddressAreaCfgIdx].SubAreaCfg[SubAreaIdx];
#endif
  const MemAcc_SectorBatchType * const SectorBatchCfgPtr = MemAcc_AddressAreas[AddressAreaCfgIdx].SubAreaCfg[SubAreaIdx].SectorBatch;
  MemAcc_LengthType ProcessingLength = 0;
  MemAcc_DataType *ReadDataPtr;
  /* Trigger the lower layer based on the Job, Burst and Legacy support */
  switch(AdminAddressArea->JobType)
  {
    case MEMACC_READ_JOB:
#if (MEMACC_COMPARE_API == STD_ON)
    case MEMACC_COMPARE_JOB: /* An intended fall through as the behavior of compare and read is the same  interaction with drivers */
      if(AdminAddressArea->JobType == MEMACC_COMPARE_JOB)
      {
        ReadDataPtr = MemAcc_AddressAreas[AddressAreaCfgIdx].AddressAreaCmpBuffer;
      }
      else
#endif
      {
        /* Deviation MISRAC2012-1, MGCC62-1, CERTC-1 */
        /* Deviation CERTC-1 */
        ReadDataPtr = (MemAcc_DataType *)SubAreaAdminPtr->UserDataPtr;
      }

      ProcessingLength = MemAcc_GetReadChunkSize(AddressAreaCfgIdx);

#if (MEMACC_LEGACY_DRIVER_SUPPORT == STD_ON)
      if(MemAcc_MemoryDevicesInfo[HwIdx].DrvInvocationType == DIRECT_LEGACY)
      {
        Result = ((const MemAcc_MemApi_LegacyType*)MemAcc_MemoryDevicesInfo[HwIdx].DrvApiTable)->Read(
                                  SubAreaAdminPtr->JobPhysicalStartAddress,
                                  ReadDataPtr,
                                  ProcessingLength);
      }
      else
#endif /* MEMACC_LEGACY_DRIVER_SUPPORT */
      {
#if (MEMACC_MEM_DRIVER_SUPPORT == STD_ON)
        Result = ((const MemAcc_MemApi_Type*)MemAcc_MemoryDevicesInfo[HwIdx].DrvApiTable)->Read(
                                  MemAcc_MemoryDevicesInfo[HwIdx].MemInstanceId,
                                  SubAreaAdminPtr->JobPhysicalStartAddress,
                                  ReadDataPtr,
                                  ProcessingLength);
#endif /* MEMACC_MEM_DRIVER_SUPPORT */
      }
      break;
    case MEMACC_WRITE_JOB:
#if (MEMACC_WRITE_BURST_SUPPORT == STD_ON)
      /* !LINKSTO MemAcc.SWS_MemAcc_00102,1 */
      if(
          (SubAreaCfgPtr->UseWriteBurst)
          &&
          (
            AdminAddressArea->SubAreaAdmin.RemainingLength
            >=
            SectorBatchCfgPtr->WritePageBurstSize
          )
        )
      {
        ProcessingLength = SectorBatchCfgPtr->WritePageBurstSize;
      }
#if (MEMACC_VARIABLE_WRITE_SUPPORT == STD_ON)
      /* !LINKSTO MemAcc.EB.VariableWrite.Functionality,1 */
      else if(SubAreaCfgPtr->UseVariableWrite)
      {
        ProcessingLength = AdminAddressArea->SubAreaAdmin.RemainingLength;
      }
#endif
      /* !LINKSTO MemAcc.MemoryAccess.Write.Page, 1 */
      else
#endif /* MEMACC_WRITE_BURST_SUPPORT */
      {
        ProcessingLength = SectorBatchCfgPtr->WritePageSize;
      }
#if (MEMACC_LEGACY_DRIVER_SUPPORT == STD_ON)
        if(MemAcc_MemoryDevicesInfo[HwIdx].DrvInvocationType == DIRECT_LEGACY)
        {
          Result = ((const MemAcc_MemApi_LegacyType*)MemAcc_MemoryDevicesInfo[HwIdx].DrvApiTable)->Write(
                                    SubAreaAdminPtr->JobPhysicalStartAddress,
                                    SubAreaAdminPtr->UserDataPtr,
                                    ProcessingLength);
        }
        else
#endif /* MEMACC_LEGACY_DRIVER_SUPPORT */
        {
#if (MEMACC_MEM_DRIVER_SUPPORT == STD_ON)
          Result = ((const MemAcc_MemApi_Type*)MemAcc_MemoryDevicesInfo[HwIdx].DrvApiTable)->Write(
                                    MemAcc_MemoryDevicesInfo[HwIdx].MemInstanceId,
                                    SubAreaAdminPtr->JobPhysicalStartAddress,
                                    SubAreaAdminPtr->UserDataPtr,
                                    ProcessingLength);
#endif /* MEMACC_MEM_DRIVER_SUPPORT */
        }
      break;
    case MEMACC_ERASE_JOB:
#if (MEMACC_ERASE_BURST_SUPPORT == STD_ON)
      /* !LINKSTO MemAcc.SWS_MemAcc_00087,1*/
      if(
          (SubAreaCfgPtr->UseEraseBurst)
          &&
          (
            AdminAddressArea->SubAreaAdmin.RemainingLength
            >=
            SectorBatchCfgPtr->SectorBurstSize
          )
        )
      {
        ProcessingLength = SectorBatchCfgPtr->SectorBurstSize;
      }
      /* !LINKSTO MemAcc.MemoryAccess.Erase.Sector, 1 */
      else
#endif /* MEMACC_ERASE_BURST_SUPPORT */
      {
        ProcessingLength = SectorBatchCfgPtr->SectorSize;
      }
#if (MEMACC_LEGACY_DRIVER_SUPPORT == STD_ON)
        if(MemAcc_MemoryDevicesInfo[HwIdx].DrvInvocationType == DIRECT_LEGACY)
        {
          Result = ((const MemAcc_MemApi_LegacyType*)MemAcc_MemoryDevicesInfo[HwIdx].DrvApiTable)->Erase(
                                    SubAreaAdminPtr->JobPhysicalStartAddress,
                                    ProcessingLength);
        }
        else
#endif /* MEMACC_LEGACY_DRIVER_SUPPORT */
        {
#if (MEMACC_MEM_DRIVER_SUPPORT == STD_ON)
          Result = ((const MemAcc_MemApi_Type*)MemAcc_MemoryDevicesInfo[HwIdx].DrvApiTable)->Erase(
                                    MemAcc_MemoryDevicesInfo[HwIdx].MemInstanceId,
                                    SubAreaAdminPtr->JobPhysicalStartAddress,
                                    ProcessingLength);
#endif /* MEMACC_MEM_DRIVER_SUPPORT */
        }
    break;
    case MEMACC_BLANKCHECK_JOB:

      ProcessingLength = MemAcc_GetReadChunkSize(AddressAreaCfgIdx);

#if (MEMACC_LEGACY_DRIVER_SUPPORT == STD_ON)
      if(MemAcc_MemoryDevicesInfo[HwIdx].DrvInvocationType == DIRECT_LEGACY)
      {
        Result = ((const MemAcc_MemApi_LegacyType*)MemAcc_MemoryDevicesInfo[HwIdx].DrvApiTable)->BlankCheck(
            SubAreaAdminPtr->JobPhysicalStartAddress,
            ProcessingLength);
      }
      else
#endif /* MEMACC_LEGACY_DRIVER_SUPPORT */
      {
#if (MEMACC_MEM_DRIVER_SUPPORT == STD_ON)
        Result = ((const MemAcc_MemApi_Type*)MemAcc_MemoryDevicesInfo[HwIdx].DrvApiTable)->BlankCheck(
            MemAcc_MemoryDevicesInfo[HwIdx].MemInstanceId,
            SubAreaAdminPtr->JobPhysicalStartAddress,
            ProcessingLength);
#endif /* MEMACC_MEM_DRIVER_SUPPORT */
      }
      break;
/* CHECK: NOPARSE */
/* switching is done between fixed known job types, so default is not needed */
    default:
      /*Unknown job, result already set*/
      break;
/* CHECK: PARSE */
  }
  if(Result != E_NOT_OK)
  {
    AdminAddressArea->LastActiveSubAreaIdx = SubAreaIdx;

    AdminAddressArea->MemLength = ProcessingLength;
    AdminAddressArea->ProcessedLength += ProcessingLength;

    SubAreaAdminPtr->RemainingLength -= ProcessingLength;
    SubAreaAdminPtr->JobPhysicalStartAddress += ProcessingLength;
    if(SubAreaAdminPtr->UserDataPtr != NULL_PTR)
    {
      SubAreaAdminPtr->UserDataPtr += ProcessingLength;
    }
    else
    {
      /*Job type without user data*/
    }
  }
  else
  {/*job not successfully triggered, no update of last active sub area index*/
  }
  return Result;
}


/*--------------------------[MemAcc_MainFunction]---------------------------------------*/
/* !LINKSTO MemAcc.Dsn.Interfaces.MainFunction, 1*/
FUNC(void, MEMACC_CODE) MemAcc_MainFunction (void)
{
  MemAcc_AddressAreaIdType SearchIdx;
  MemAcc_AddressAreaIdType AddressAreaCfgIdx;

  #if(MEMACC_HANDLING_SUPPORT == STD_ON)
  MemAcc_HwIdType HwIdx;
  MemAcc_MemInstanceIdType InstanceIdx;
  #endif

  MemAcc_AddressAreaIdType RequestsBufferElementsNoCopy;
  MemAcc_AddressAreaIdType RequestsBufferCopy[MEMACC_JOB_QUEUE_SIZE];
  MemAcc_AddressAreaLockType LockRequests[MEMACC_NB_OF_CONFIGURED_ADDRESSAREAS];

  DBG_MEMACC_MAINFUNCTION_ENTRY();

  /*Step1: Get Job Results for jobs triggered in the previous cycle*/
  /* Optimization potential: if driver would also have some storage to handle owner change,
   * no double checking of status;
   * we could process the prev results while processing the new queue state tbd
   */
  MemAcc_GetOngoingJobResults();

  /*Step 2: Order requests according to priority*/
  SchM_Enter_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_1();
  RequestsBufferElementsNoCopy = MemAcc_JobRequestsBufferElementsNo;
  TS_MemCpy(RequestsBufferCopy, (MemAcc_AddressAreaIdType*)MemAcc_JobRequestsBuffer, sizeof(MemAcc_JobRequestsBuffer[0]) * MemAcc_JobRequestsBufferElementsNo);

  /*Clear requests buffer*/
  MemAcc_JobRequestsBufferElementsNo = 0;
  SchM_Exit_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_1();

  for(SearchIdx = 0; SearchIdx < RequestsBufferElementsNoCopy; SearchIdx++)
  {
    MemAcc_InsertInQueue(RequestsBufferCopy[SearchIdx]);
  }

  /*Step3: Go through all areas and handle locking state*/
  SchM_Enter_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_2();
  for(AddressAreaCfgIdx = 0; AddressAreaCfgIdx < MEMACC_NB_OF_CONFIGURED_ADDRESSAREAS; AddressAreaCfgIdx++)
  {
    LockRequests[AddressAreaCfgIdx] = MemAcc_LockRequests[AddressAreaCfgIdx];
    /*safe to clear requests also for queued areas since they were already processed*/
    MemAcc_LockRequests[AddressAreaCfgIdx].LockStateChangeRequest = FALSE;
  }
  SchM_Exit_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_2();

  for(AddressAreaCfgIdx = 0; AddressAreaCfgIdx < MEMACC_NB_OF_CONFIGURED_ADDRESSAREAS; AddressAreaCfgIdx++)
  {
    MemAcc_AreaLockStateMachine(AddressAreaCfgIdx, &LockRequests[AddressAreaCfgIdx]);
  }

  /*Step4: Go through all pending AreaId jobs and trigger sub-area jobs*/
  for(SearchIdx = 0; SearchIdx < MemAcc_QueueElementsNo; SearchIdx++)
  {
    AddressAreaCfgIdx = MemAcc_AreaIdQueue[SearchIdx];

    MemAcc_AreaJobStateMachine(AddressAreaCfgIdx);
  }

  /*Step5: Remove from queue all completed jobs*/
  for(SearchIdx = MemAcc_QueueElementsNo; SearchIdx > 0U; SearchIdx--)
  {

    MemAcc_AddressAreaIdType QueueIdx = SearchIdx - 1U;
    AddressAreaCfgIdx = MemAcc_AreaIdQueue[QueueIdx];
    if(MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobStatus != MEMACC_JOB_PENDING)
    {
      MemAcc_JobResultType JobResult;

      MemAcc_DequeueFromIndex(QueueIdx);

      JobResult = MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobResult;
      MemAcc_CancelRequests[AddressAreaCfgIdx] = FALSE;
      /*After setting JobType to MEMACC_NO_JOB, new requests for the area will be accepted*/
      MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobType = MEMACC_NO_JOB;

      if(MemAcc_AddressAreas[AddressAreaCfgIdx].AddressAreaCallback != NULL_PTR)
      {
        /* !LINKSTO MemAcc.SWS_MemAcc_00015, 1*/
        /* !LINKSTO MemAcc.Dsn.Interaction.Cbk.CancelFinishedJob, 1*/
        (void)MemAcc_AddressAreas[AddressAreaCfgIdx].AddressAreaCallback(AddressAreaCfgIdx, JobResult);
      }
    }
  }
  DBG_MEMACC_MAINFUNCTION_EXIT();
}

/*--------------------------[MemAcc_Cancel]---------------------------------------*/
/* !LINKSTO MemAcc.Dsn.Interfaces.Cancel, 1*/
FUNC(void, MEMACC_CODE) MemAcc_Cancel (MemAcc_AddressAreaIdType AddressAreaId)
{
  MemAcc_AddressAreaIdType AddressAreaCfgIdx;

  DBG_MEMACC_CANCEL_ENTRY(AddressAreaId);

  if(MemAcc_InitStatus)
  {
    AddressAreaCfgIdx = MemAcc_GetAddressAreaConfigIndex(AddressAreaId);

    if(AddressAreaCfgIdx == MEMACC_INVALID_ADDRESSAREA)
    {
      /* !LINKSTO MemAcc.SWS_MemAcc_00031, 1*/
  #if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
      MEMACC_DET_REPORT_ERROR(MEMACC_CANCEL_API_ID,MEMACC_E_PARAM_ADDRESS_AREA_ID);
  #endif
    }
    else
    {
      if(MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobType == MEMACC_NO_JOB)
      {
        /* !LINKSTO MemAcc.SWS_MemAcc_00029, 1*/
        /*Nothing to do if job ended*/
      }
      else
      {
        /* !LINKSTO MemAcc.SWS_MemAcc_00028, 1*/
        MemAcc_CancelRequests[AddressAreaCfgIdx] = TRUE;
      }
    }
  }
  else
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00030, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
    MEMACC_DET_REPORT_ERROR(MEMACC_CANCEL_API_ID, MEMACC_E_UNINIT);
#endif
  }

  DBG_MEMACC_CANCEL_EXIT(AddressAreaId);
}


/*--------------------------[MemAcc_GetJobResult]---------------------------------------*/
/* !LINKSTO MemAcc.Dsn.Interfaces.GetJobResult, 1*/
FUNC(MemAcc_JobResultType, MEMACC_CODE) MemAcc_GetJobResult(MemAcc_AddressAreaIdType AddressAreaId)
{
  MemAcc_JobResultType Result = MEMACC_MEM_FAILED;
  MemAcc_AddressAreaIdType AddressAreaCfgIdx;

  DBG_MEMACC_GETJOBRESULT_ENTRY(AddressAreaId);
  if(MemAcc_InitStatus)
  {
    AddressAreaCfgIdx = MemAcc_GetAddressAreaConfigIndex(AddressAreaId);

    if(AddressAreaCfgIdx == MEMACC_INVALID_ADDRESSAREA)
    {
      /* !LINKSTO MemAcc.SWS_MemAcc_00034, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
      MEMACC_DET_REPORT_ERROR(MEMACC_GET_JOB_RESULT_API_ID,MEMACC_E_PARAM_ADDRESS_AREA_ID);
#endif
    }
    else
    {
      /* !LINKSTO MemAcc.Dsn.Interaction.Polling.JobResult, 1*/
      Result = MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobResult;
    }
  }
  else
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00033, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
    MEMACC_DET_REPORT_ERROR(MEMACC_GET_JOB_RESULT_API_ID,MEMACC_E_UNINIT);
#endif
  }

  DBG_MEMACC_GETJOBRESULT_EXIT(Result, AddressAreaId);
  return Result;
}
/*--------------------------[MemAcc_GetJobStatus]---------------------------------------*/
/* !LINKSTO MemAcc.Dsn.Interfaces.GetJobStatus, 1*/
FUNC(MemAcc_JobStatusType, MEMACC_CODE) MemAcc_GetJobStatus(MemAcc_AddressAreaIdType AddressAreaId)
{
  MemAcc_JobStatusType Result = MEMACC_JOB_IDLE;
  MemAcc_AddressAreaIdType AddressAreaCfgIdx;

  DBG_MEMACC_GETJOBSTATUS_ENTRY(AddressAreaId);
  if(MemAcc_InitStatus)

  {
    AddressAreaCfgIdx = MemAcc_GetAddressAreaConfigIndex(AddressAreaId);

    if(AddressAreaCfgIdx == MEMACC_INVALID_ADDRESSAREA)
    {
      /* !LINKSTO MemAcc.EB.GetJobStatus.InvalidAddressAreaId, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
      MEMACC_DET_REPORT_ERROR(MEMACC_GET_JOB_STATUS_API_ID,MEMACC_E_PARAM_ADDRESS_AREA_ID);
#endif
    }
    else
    {
      /* !LINKSTO MemAcc.SWS_MemAcc_00118, 1*/
      /* !LINKSTO MemAcc.SWS_MemAcc_00119, 1*/
      Result = MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobStatus;
    }
  }
  else
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00117, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
    MEMACC_DET_REPORT_ERROR(MEMACC_GET_JOB_STATUS_API_ID,MEMACC_E_UNINIT);
#endif
  }

  DBG_MEMACC_GETJOBSTATUS_EXIT(Result,AddressAreaId);
  return Result;
}
/*--------------------------[MemAcc_ValidateGetMemoryInfoParams]---------------------------------------*/
STATIC FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_ValidateGetMemoryInfoParams
(
  MemAcc_AddressAreaIdType AddressAreaCfgIdx,
  MemAcc_AddressType Address,
  MemAcc_MemoryInfoType* MemoryInfoPtr)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_MEMACC_VALIDATEGETMEMORYINFOPARAMS_ENTRY(AddressAreaCfgIdx, Address, MemoryInfoPtr);

  if(AddressAreaCfgIdx == MEMACC_INVALID_ADDRESSAREA)
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00036, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
    MEMACC_DET_REPORT_ERROR(MEMACC_GET_MEMORY_INFO_API_ID, MEMACC_E_PARAM_ADDRESS_AREA_ID);
#endif
  }
  else if(MemoryInfoPtr == NULL_PTR)
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00037, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
    MEMACC_DET_REPORT_ERROR(MEMACC_GET_MEMORY_INFO_API_ID, MEMACC_E_PARAM_POINTER);
#endif
  }
  else if(MEMACC_REQUEST_PARAM_OFFSET_INVALID(AddressAreaCfgIdx, Address))
  {
    /* !LINKSTO MemAcc.EB.GetMemoryInfo.InvalidAddress, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
    MEMACC_DET_REPORT_ERROR(MEMACC_GET_MEMORY_INFO_API_ID, MEMACC_E_PARAM_ADDRESS_LENGTH);
#endif
  }
  else
  {
    Result = E_OK;
  }

  DBG_MEMACC_VALIDATEGETMEMORYINFOPARAMS_EXIT(Result, AddressAreaCfgIdx, Address, MemoryInfoPtr);
  return Result;
}

/*--------------------------[MemAcc_GetMemoryInfo]---------------------------------------*/
/* !LINKSTO MemAcc.Dsn.Interfaces.GetMemoryInfo, 1*/
FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_GetMemoryInfo
(
  MemAcc_AddressAreaIdType AddressAreaId,
  MemAcc_AddressType Address,
  MemAcc_MemoryInfoType* MemoryInfoPtr
)
{
  Std_ReturnType Result = E_NOT_OK;
  MemAcc_AddressAreaIdType AddressAreaCfgIdx;
  MemAcc_AddressAreaIdType SubAreaIdx;

  const MemAcc_SectorBatchType* SectorBatchCfgPtr;
  const MemAcc_AddressSubAreaType* SubAreaCfgPtr;

  DBG_MEMACC_GETMEMORYINFO_ENTRY(AddressAreaId, Address, MemoryInfoPtr);

  if(MemAcc_InitStatus)
  {
      AddressAreaCfgIdx = MemAcc_GetAddressAreaConfigIndex(AddressAreaId);
      Result = MemAcc_ValidateGetMemoryInfoParams(AddressAreaCfgIdx, Address, MemoryInfoPtr);

      if(Result == E_OK)
      {
        SubAreaIdx = MemAcc_FindLogicalAddressSubarea(AddressAreaCfgIdx, Address);

        SubAreaCfgPtr = &MemAcc_AddressAreas[AddressAreaCfgIdx].SubAreaCfg[SubAreaIdx];
        SectorBatchCfgPtr = MemAcc_AddressAreas[AddressAreaCfgIdx].SubAreaCfg[SubAreaIdx].SectorBatch;
        MemoryInfoPtr->LogicalStartAddress=SubAreaCfgPtr->LogicalStartAddress;
        MemoryInfoPtr->PhysicalStartAddress=SubAreaCfgPtr->PhysicalStartAddress;
        MemoryInfoPtr->MaxOffset= (SubAreaCfgPtr->Length - 1U);
        MemoryInfoPtr->EraseSectorSize=SectorBatchCfgPtr->SectorSize;
        MemoryInfoPtr->ReadPageSize=SectorBatchCfgPtr->ReadPageSize;
        MemoryInfoPtr->WritePageSize=SectorBatchCfgPtr->WritePageSize;
        MemoryInfoPtr->HwId=SubAreaCfgPtr->DrvHwId;

    #if (MEMACC_ERASE_BURST_SUPPORT == STD_ON)
        MemoryInfoPtr->EraseSectorBurstSize=SectorBatchCfgPtr->SectorBurstSize;
    #else
        MemoryInfoPtr->EraseSectorBurstSize=SectorBatchCfgPtr->SectorSize;
    #endif

    #if (MEMACC_READ_BURST_SUPPORT == STD_ON)
        MemoryInfoPtr->ReadPageBurstSize=SectorBatchCfgPtr->ReadPageBurstSize;
    #else
        MemoryInfoPtr->ReadPageBurstSize=SectorBatchCfgPtr->ReadPageSize;
    #endif

    #if (MEMACC_WRITE_BURST_SUPPORT == STD_ON)
        MemoryInfoPtr->WritePageBurstSize=SectorBatchCfgPtr->WritePageBurstSize;
    #else
        MemoryInfoPtr->WritePageBurstSize=SectorBatchCfgPtr->WritePageSize;
    #endif
      }
  }
  else
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00035, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
    MEMACC_DET_REPORT_ERROR(MEMACC_GET_MEMORY_INFO_API_ID,MEMACC_E_UNINIT);
#endif
  }

  DBG_MEMACC_GETMEMORYINFO_EXIT(Result, AddressAreaId, Address, MemoryInfoPtr);

  return Result;
}


/*--------------------------[MemAcc_GetProcessedLength]---------------------------------------*/
/* !LINKSTO MemAcc.Dsn.Interfaces.GetProcessedLength , 1*/
FUNC(MemAcc_LengthType, MEMACC_CODE) MemAcc_GetProcessedLength
(
  MemAcc_AddressAreaIdType AddressAreaId
)
{
  MemAcc_LengthType ProcessedLength = 0;
  MemAcc_AddressAreaIdType AddressAreaCfgIdx;

  DBG_MEMACC_GETPROCESSEDLENGTH_ENTRY(AddressAreaId);

  if(MemAcc_InitStatus)
  {
    AddressAreaCfgIdx = MemAcc_GetAddressAreaConfigIndex(AddressAreaId);
    if(AddressAreaCfgIdx == MEMACC_INVALID_ADDRESSAREA)
    {
      /* !LINKSTO MemAcc.SWS_MemAcc_00039, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
      MEMACC_DET_REPORT_ERROR(MEMACC_GET_PROCESSED_LENGTH_API_ID, MEMACC_E_PARAM_ADDRESS_AREA_ID);
#endif
    }
    else
    {
      /* !LINKSTO MemAcc.SWS_MemAcc_00120, 1*/
      ProcessedLength = MemAcc_AdminAddressArea[AddressAreaCfgIdx].ProcessedLength;
    }
  }
  else
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00038, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
    MEMACC_DET_REPORT_ERROR(MEMACC_GET_PROCESSED_LENGTH_API_ID, MEMACC_E_UNINIT);
#endif
  }

  DBG_MEMACC_GETPROCESSEDLENGTH_EXIT(ProcessedLength, AddressAreaId);
  return ProcessedLength;
}


/*--------------------------------------[MemAcc_ValidateGetJobInfoParams]---------------------------------------*/
STATIC FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_ValidateGetJobInfoParams
(
  MemAcc_AddressAreaIdType AddressAreaCfgIdx,
  MemAcc_JobInfoType* JobInfoPtr
)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_MEMACC_VALIDATEGETJOBINFOPARAMS_ENTRY(AddressAreaCfgIdx, JobInfoPtr);

  if(AddressAreaCfgIdx == MEMACC_INVALID_ADDRESSAREA)
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00041, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
    MEMACC_DET_REPORT_ERROR(MEMACC_GET_JOB_INFO_API_ID, MEMACC_E_PARAM_ADDRESS_AREA_ID);
#endif
  }
  else if(JobInfoPtr == NULL_PTR)
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00042, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
    MEMACC_DET_REPORT_ERROR(MEMACC_GET_JOB_INFO_API_ID, MEMACC_E_PARAM_POINTER);
#endif
  }
  else
  {
    Result = E_OK;
  }

  DBG_MEMACC_VALIDATEGETJOBINFOPARAMS_EXIT(Result, AddressAreaCfgIdx, JobInfoPtr);
  return Result;
}
/*--------------------------[MemAcc_GetJobInfo]---------------------------------------*/
/* !LINKSTO MemAcc.Dsn.Interfaces.GetJobInfo, 1*/
FUNC(void, MEMACC_CODE) MemAcc_GetJobInfo
(
  MemAcc_AddressAreaIdType AddressAreaId,
  MemAcc_JobInfoType* JobInfoPtr
)
{
  MemAcc_AddressAreaIdType AddressAreaCfgIdx;
  MemAcc_AddressAreaIdType SubAreaIdx;
  MemAcc_AddressSubAreaAdminType *SubAreaAdminPtr;
  const MemAcc_AddressSubAreaType * SubAreaCfgPtr;

  DBG_MEMACC_GETJOBINFO_ENTRY(AddressAreaId,JobInfoPtr);

  if(MemAcc_InitStatus == FALSE)
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00040, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
    MEMACC_DET_REPORT_ERROR(MEMACC_GET_JOB_INFO_API_ID, MEMACC_E_UNINIT);
#endif
  }
  else
  {
    AddressAreaCfgIdx = MemAcc_GetAddressAreaConfigIndex(AddressAreaId);

    if(MemAcc_ValidateGetJobInfoParams(AddressAreaCfgIdx, JobInfoPtr) == E_OK)
    {
      JobInfoPtr->LogicalAddress = MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobLogicalAddress;
      JobInfoPtr->Length = MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobLength;
      JobInfoPtr->CurrentJob = MemAcc_AdminAddressArea[AddressAreaCfgIdx].JobType;
      if( MemAcc_AdminAddressArea[AddressAreaCfgIdx].MemLength > 0U )
      {
        SubAreaIdx = MemAcc_AdminAddressArea[AddressAreaCfgIdx].LastActiveSubAreaIdx;
        SubAreaAdminPtr = &MemAcc_AdminAddressArea[AddressAreaCfgIdx].SubAreaAdmin;
        SubAreaCfgPtr = &MemAcc_AddressAreas[AddressAreaCfgIdx].SubAreaCfg[SubAreaIdx];
        JobInfoPtr->MemAddress = (SubAreaAdminPtr->JobPhysicalStartAddress - MemAcc_AdminAddressArea[AddressAreaCfgIdx].MemLength);
        JobInfoPtr->MemLength = MemAcc_AdminAddressArea[AddressAreaCfgIdx].MemLength;
        JobInfoPtr->HwId = SubAreaCfgPtr->DrvHwId;
        JobInfoPtr->MemInstanceId = MemAcc_MemoryDevicesInfo[SubAreaCfgPtr->DrvHwId].MemInstanceId;

        if(SubAreaAdminPtr->JobState==MEMACC_INPROGRESS)
        {
          /* !LINKSTO MemAcc.EB.MemoryAccess.GetJobInfo.ActiveJob, 1*/
          JobInfoPtr->MemResult = MemAcc_GetDriverJobResult(AddressAreaCfgIdx);
        }
        else
        {
          /* !LINKSTO MemAcc.EB.MemoryAccess.GetJobInfo.InactiveJob, 1*/
          JobInfoPtr->MemResult = SubAreaAdminPtr->MemDrvJobResult;
        }
      }
      else
      {
        JobInfoPtr->MemAddress = 0;
        JobInfoPtr->MemLength = 0;
        JobInfoPtr->MemResult = MEM_JOB_OK;
        JobInfoPtr->HwId = 0;
        JobInfoPtr->MemInstanceId = 0;
      }
    }
  }

  DBG_MEMACC_GETJOBINFO_EXIT(AddressAreaId,JobInfoPtr);

}

#if (MEMACC_VERSION_INFO_API == STD_ON)
/*--------------------------[MemAcc_GetVersionInfo]---------------------------------------*/
/* !LINKSTO MemAcc.Dsn.Interfaces.GetVersionInfo, 1*/
FUNC(void, MEMACC_CODE) MemAcc_GetVersionInfo (Std_VersionInfoType *VersionInfoPtr)
{
  DBG_MEMACC_GETVERSIONINFO_ENTRY(VersionInfoPtr);

  if(VersionInfoPtr == NULL_PTR)
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00027, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
    MEMACC_DET_REPORT_ERROR(MEMACC_GET_VERSION_INFO_API_ID, MEMACC_E_PARAM_POINTER);
#endif
  }
  else
  {
    VersionInfoPtr->vendorID = MEMACC_VENDOR_ID;
    VersionInfoPtr->moduleID = MEMACC_MODULE_ID;
    VersionInfoPtr->sw_major_version = MEMACC_SW_MAJOR_VERSION;
    VersionInfoPtr->sw_minor_version = MEMACC_SW_MINOR_VERSION;
    VersionInfoPtr->sw_patch_version = MEMACC_SW_PATCH_VERSION;
  }
  DBG_MEMACC_GETVERSIONINFO_ENTRY(VersionInfoPtr);
}
#endif
/* !LINKSTO MemAcc.Dsn.Interfaces.RequestLock, 1*/
/*--------------------------[MemAcc_RequestLock]---------------------------------------*/
FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_RequestLock
(
  MemAcc_AddressAreaIdType AddressAreaId,
  MemAcc_AddressType Address,
  MemAcc_LengthType Length,
  ApplicationLockNotification LockNotificationFctPtr
)
{
  Std_ReturnType Result = E_NOT_OK;
  MemAcc_AddressAreaIdType AddressAreaCfgIdx;

  DBG_MEMACC_REQUESTLOCK_ENTRY(AddressAreaId, Address, Length, LockNotificationFctPtr);
  if(MemAcc_InitStatus)
  {
    AddressAreaCfgIdx = MemAcc_GetAddressAreaConfigIndex(AddressAreaId);

    if(AddressAreaCfgIdx == MEMACC_INVALID_ADDRESSAREA)
    {
      /* !LINKSTO MemAcc.SWS_MemAcc_00071, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
      MEMACC_DET_REPORT_ERROR(MEMACC_REQUEST_LOCK_ID,MEMACC_E_PARAM_ADDRESS_AREA_ID);
#endif
    }
    else if(LockNotificationFctPtr == NULL_PTR)
    {
    /* !LINKSTO MemAcc.SWS_MemAcc_00072, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
      MEMACC_DET_REPORT_ERROR(MEMACC_REQUEST_LOCK_ID, MEMACC_E_PARAM_POINTER);
#endif
    }
    else
    {
      SchM_Enter_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_2();
      if(MemAcc_LockRequests[AddressAreaCfgIdx].Lock == FALSE)
      {
        MemAcc_LockRequests[AddressAreaCfgIdx].Lock = TRUE;
        MemAcc_LockRequests[AddressAreaCfgIdx].AddressAreaLockNotification = LockNotificationFctPtr;
        MemAcc_LockRequests[AddressAreaCfgIdx].LockStateChangeRequest = TRUE;
        SchM_Exit_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_2();
        Result = E_OK;
      }
      else
      {
        /* Nothing to do if lock was previously requested, return NOK */
        SchM_Exit_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_2();
      }
    }
  }
  else
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00099, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
    MEMACC_DET_REPORT_ERROR(MEMACC_REQUEST_LOCK_ID,MEMACC_E_UNINIT);
#endif
  }
  TS_PARAM_UNUSED(Address);
  TS_PARAM_UNUSED(Length);
  DBG_MEMACC_REQUESTLOCK_EXIT(Result, AddressAreaId, Address, Length, LockNotificationFctPtr);
  return Result;
}

/* !LINKSTO MemAcc.Dsn.Interfaces.ReleaseLock, 1*/
/*--------------------------[MemAcc_ReleaseLock]---------------------------------------*/
FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_ReleaseLock
(
  MemAcc_AddressAreaIdType AddressAreaId,
  MemAcc_AddressType Address,
  MemAcc_LengthType Length
)
{
  Std_ReturnType Result = E_NOT_OK;
  MemAcc_AddressAreaIdType AddressAreaCfgIdx;

  DBG_MEMACC_RELEASELOCK_ENTRY(AddressAreaId, Address, Length);
  if(MemAcc_InitStatus)
  {
    AddressAreaCfgIdx = MemAcc_GetAddressAreaConfigIndex(AddressAreaId);

    if(AddressAreaCfgIdx == MEMACC_INVALID_ADDRESSAREA)
    {
      /* !LINKSTO MemAcc.SWS_MemAcc_00093, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
      MEMACC_DET_REPORT_ERROR(MEMACC_RELEASE_LOCK_ID,MEMACC_E_PARAM_ADDRESS_AREA_ID);
#endif
    }
    else
    {
      SchM_Enter_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_2();
      if(MemAcc_LockRequests[AddressAreaCfgIdx].Lock == TRUE)
      {
        MemAcc_LockRequests[AddressAreaCfgIdx].Lock = FALSE;
        MemAcc_LockRequests[AddressAreaCfgIdx].AddressAreaLockNotification = NULL_PTR;
        MemAcc_LockRequests[AddressAreaCfgIdx].LockStateChangeRequest = TRUE;
        SchM_Exit_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_2();
        Result = E_OK;
      }
      else
      {
        /* Nothing to do if address area is unlocked */
        SchM_Exit_MemAcc_SCHM_MEMACC_EXCLUSIVE_AREA_2();
      }
    }
  }
  else
  {
    /* !LINKSTO MemAcc.SWS_MemAcc_00076, 1*/
#if ( MEMACC_DEV_ERROR_DETECT == STD_ON )
    MEMACC_DET_REPORT_ERROR(MEMACC_RELEASE_LOCK_ID,MEMACC_E_UNINIT);
#endif
  }
  TS_PARAM_UNUSED(Address);
  TS_PARAM_UNUSED(Length);
  DBG_MEMACC_RELEASELOCK_EXIT(Result, AddressAreaId, Address, Length);
  return Result;
}
#define MEMACC_STOP_SEC_CODE
#include <MemAcc_MemMap.h>
/*==================[end of file]===========================================*/
