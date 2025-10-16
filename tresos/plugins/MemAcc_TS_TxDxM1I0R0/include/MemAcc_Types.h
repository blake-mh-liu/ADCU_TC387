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
#ifndef MEMACC_TYPES_H
#define MEMACC_TYPES_H

/*==================[inclusions]============================================*/

#include <TSAutosar.h>            /* EB specific standard types      */

#include <Std_Types.h>            /* AUTOSAR standard types.*/
#include <MemAcc_CfgTypes.h>

/*==================[type definitions]======================================*/
/** \brief Returned by APIs if the underlying Mem driver service function is not available*/
#ifndef E_MEM_SERVICE_NOT_AVAIL
#define  MEMACC_MEM_SERVICE_NOT_AVAIL 2U
#else
#define  MEMACC_MEM_SERVICE_NOT_AVAIL E_MEM_SERVICE_NOT_AVAIL
#endif
/* !LINKSTO MemAcc.Dsn.Types.MemAcc_MemInstanceIdType, 1*/
/** \brief Memory driver instance identifier type. */
typedef uint32 MemAcc_MemInstanceIdType;

/* !LINKSTO MemAcc.Dsn.Types.MemAcc_HwIdType, 1 */
/** \brief Type for the unique numeric identifiers of all Mem hardware instances used for hardware specific requests. */
typedef uint32 MemAcc_HwIdType;

/* !LINKSTO MemAcc.Dsn.Types.MemAcc_AddressAreaIdType, 1 */
/** \brief Unique address area ID type. */
typedef uint16 MemAcc_AddressAreaIdType;

/* !LINKSTO MemAcc.Dsn.Types.MemAcc_DataType, 1 */
/** \brief General data type */
typedef uint8 MemAcc_DataType;

/* !LINKSTO MemAcc.Dsn.Types.MemAcc_MemHwServiceIdType, 1 */
/** \brief Index type for Mem driver hardware specific service table */
typedef uint32 MemAcc_MemHwServiceIdType;

/*---------- [MemAcc Job result macros]------------*/

/* !LINKSTO MemAcc.Dsn.Types.MemAcc_JobResultType, 1 */
 /** \brief This type denotes the result of the last job. */
typedef uint8 MemAcc_JobResultType;

#if (defined MEMACC_MEM_OK)
#error MEMACC_MEM_OK is already defined
#endif /* if (defined MEMACC_MEM_OK) */
  /** \brief The job has been finished successfully. */
#define  MEMACC_MEM_OK ((MemAcc_JobResultType)0U)

#if (defined MEMACC_MEM_FAILED)
#error MEMACC_MEM_FAILED is already defined
#endif /* if (defined MEMACC_MEM_FAILED) */
  /** \brief The last MemAcc job resulted in an unspecific failure and the job was not completed. */
#define  MEMACC_MEM_FAILED ((MemAcc_JobResultType)1U)

#if (defined MEMACC_MEM_INCONSISTENT)
#error MEMACC_MEM_INCONSISTENT is already defined
#endif /* if (defined MEMACC_MEM_INCONSISTENT) */
  /** \brief The results of the last MemAcc job didn’t meet the expected result. */
  /* * e.g. a blank check operation was applied on a non-blank memory area*/
#define  MEMACC_MEM_INCONSISTENT ((MemAcc_JobResultType)2U)

#if (defined MEMACC_MEM_CANCELED)
#error MEMACC_MEM_CANCELED is already defined
#endif /* if (defined MEMACC_MEM_CANCELED) */
  /** \brief The last MemAcc job was canceled. */
#define  MEMACC_MEM_CANCELED ((MemAcc_JobResultType)3U)

#if (defined MEMACC_MEM_ECC_UNCORRECTED)
#error MEMACC_MEM_ECC_UNCORRECTED is already defined
#endif /* if (defined MEMACC_MEM_ECC_UNCORRECTED) */
  /** \brief The last memory operation returned an uncorrectable ECC error. */
#define  MEMACC_MEM_ECC_UNCORRECTED ((MemAcc_JobResultType)4U)

#if (defined MEMACC_MEM_ECC_CORRECTED)
#error MEMACC_MEM_ECC_CORRECTED is already defined
#endif /* if (defined MEMACC_MEM_ECC_CORRECTED) */
  /** \brief The last memory operation returned a correctable ECC error. */
#define  MEMACC_MEM_ECC_CORRECTED ((MemAcc_JobResultType)5U)


/*---------- [MemAcc Job status type macros]------------*/

/* !LINKSTO MemAcc.Dsn.Types.MemAcc_JobStatusType,1 */
 /** \brief Asynchronous job status type. */
typedef uint8 MemAcc_JobStatusType;

#if (defined MEMACC_JOB_IDLE)
#error MEMACC_JOB_IDLE is already defined
#endif /* if (defined MEMACC_JOB_IDLE) */
  /** \brief Job processing was completed or no job currently pending. */
#define  MEMACC_JOB_IDLE ((MemAcc_JobStatusType)0U)

#if (defined MEMACC_JOB_PENDING)
#error MEMACC_JOB_PENDING is already defined
#endif /* if (defined MEMACC_JOB_PENDING) */
  /** \brief A job is currently being processed. */
#define  MEMACC_JOB_PENDING ((MemAcc_JobStatusType)1U)

/*---------- [MemAcc Job type macros]------------*/

/* !LINKSTO MemAcc.Dsn.Types.MemAcc_JobType, 1 */
 /** \brief This type represents the current job of the MemAcc module. */
typedef uint8 MemAcc_JobType;

#if (defined MEMACC_NO_JOB)
#error MEMACC_NO_JOB is already defined
#endif /* if (defined MEMACC_NO_JOB) */
  /** \brief No job currently pending. */
#define  MEMACC_NO_JOB ((MemAcc_JobType)0U)

#if (defined MEMACC_WRITE_JOB)
#error MEMACC_WRITE_JOB is already defined
#endif /* if (defined MEMACC_WRITE_JOB) */
  /** \brief Write job is pending . */
#define  MEMACC_WRITE_JOB ((MemAcc_JobType)1U)

#if (defined MEMACC_READ_JOB)
#error MEMACC_READ_JOB is already defined
#endif /* if (defined MEMACC_READ_JOB) */
  /** \brief Read job is pending . */
#define  MEMACC_READ_JOB ((MemAcc_JobType)2U)

#if (defined MEMACC_COMPARE_JOB)
#error MEMACC_COMPARE_JOB is already defined
#endif /* if (defined MEMACC_COMPARE_JOB) */
  /** \brief Compare job is pending . */
#define  MEMACC_COMPARE_JOB ((MemAcc_JobType)3U)

#if (defined MEMACC_ERASE_JOB)
#error MEMACC_ERASE_JOB is already defined
#endif /* if (defined MEMACC_ERASE_JOB) */
  /** \brief Erase job is pending . */
#define  MEMACC_ERASE_JOB ((MemAcc_JobType)4U)

#if (defined MEMACC_MEMHWSPECIFIC_JOB)
#error MEMACC_MEMHWSPECIFIC_JOB is already defined
#endif /* if (defined MEMACC_MEMHWSPECIFIC_JOB) */
  /** \brief Hardware specific service job is pending . */
#define  MEMACC_MEMHWSPECIFIC_JOB ((MemAcc_JobType)5U)

#if (defined MEMACC_BLANKCHECK_JOB)
#error MEMACC_BLANKCHECK_JOB is already defined
#endif /* if (defined MEMACC_BLANKCHECK_JOB) */
  /** \brief Blank check job is pending . */
#define  MEMACC_BLANKCHECK_JOB ((MemAcc_JobType)6U)

#if (defined MEMACC_REQUESTLOCK_JOB)
#error MEMACC_REQUESTLOCK_JOB is already defined
#endif /* if (defined MEMACC_REQUESTLOCK_JOB) */
  /** \brief Request lock job is pending . */
#define  MEMACC_REQUESTLOCK_JOB ((MemAcc_JobType)7U)

/* !LINKSTO MemAcc.Dsn.Types.AddressAreaJobEndNotification, 1*/
/** \brief MemAcc application job end notification callback
 **
 ** It is called if a asynchronous MemAcc API request has finished.
 ** The function name is configurable
 **
 ** \param[in]      AddressAreaId Numeric identifier of address area
 ** \param[in]      JobResult Result of the last MemAcc operation
 **
 ** \ServiceID{0x0F}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{synchronous} */
typedef P2FUNC(void, MEMACC_CODE, AddressAreaJobEndNotification ) ( MemAcc_AddressAreaIdType MemAccAddressAreaId, MemAcc_JobResultType JobResult );

/* !LINKSTO MemAcc.Dsn.Types.ApplicationLockNotification, 1*/
/** \brief Address area lock application callback
 **
 ** \ServiceID{0x14}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{synchronous} */
typedef P2FUNC( void, MEMACC_CODE, ApplicationLockNotification )(void);

/* !LINKSTO MemAcc.Dsn.Types.MemAcc_ConfigType, 1*/
/** \brief Postbuild configuration structure type */
typedef struct
{
  uint8 Dummy; /* A Place Holder */
}MemAcc_ConfigType;

/* !LINKSTO MemAcc.Dsn.Types.MemAcc_JobInfoType, 1 */
/** \brief Layout information of the current processing state of the MemAcc module */
typedef struct
{
  /** \brief Address of currently active address area request. */
  MemAcc_AddressType LogicalAddress;
  /** \brief Length of the currently active address area request. */
  MemAcc_LengthType Length;
  /** \brief Referenced memory driver hardware identifier. */
  MemAcc_HwIdType HwId;
  /** \brief Instance ID of the current memory request. */
  uint32 MemInstanceId;
  /** \brief Physical address of the current memory driver request. */
  MemAcc_AddressType MemAddress;
  /** \brief Length of memory driver request. */
  MemAcc_LengthType MemLength;
  /** \brief Currently active MemAcc job. */
  MemAcc_JobType CurrentJob;
  /** \brief Current or last Mem driver result. */
  MemAcc_Mem_JobResultType MemResult;
} MemAcc_JobInfoType;

/* !LINKSTO MemAcc.Dsn.Types.MemAcc_MemoryInfoType, 1 */
/** \brief This structure contains information of Mem device characteristics.
 ** It can be accessed via the MemAcc_GetMemoryInfo() service.
*/
typedef struct
{
  /** \brief Logical start address of sub address area. */
  MemAcc_AddressType LogicalStartAddress;
  /** \brief Physical start address of sub address area. */
  MemAcc_AddressType PhysicalStartAddress;
  /** \brief Size of sub address area in bytes -1. */
  MemAcc_LengthType MaxOffset;
  /** \brief Size of a sector in bytes. */
  uint32 EraseSectorSize;
  /** \brief Size of a sector burst in bytes. Equals SectorSize in case burst is disabled. */
  uint32 EraseSectorBurstSize;
  /** \brief Read size of a page in bytes. */
  uint32 ReadPageSize;
  /** \brief Write size of a page in bytes. */
  uint32 WritePageSize;
  /** \brief Size of a read page burst in bytes. Equals ReadPageSize in case burst is disabled. */
  uint32 ReadPageBurstSize;
  /** \brief Size of a write page burst in bytes. Equals WritePageSize in case burst is disabled. */
  uint32 WritePageBurstSize;
  /** \brief Referenced memory driver hardware identifier. */
  MemAcc_HwIdType HwId;
} MemAcc_MemoryInfoType;

/** \brief Pointer to State */
typedef MemAcc_JobInfoType* MemAcc_JobInfoPtrType;

/** \brief Pointer to the configuration structure */
typedef MemAcc_ConfigType* MemAcc_ConfigPtrType;

/** \brief Pointer to Memory Info */
typedef MemAcc_MemoryInfoType* MemAcc_MemoryInfoPtrType;

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* MEMACC_TYPES_H */

/*=========================[end of file MemAcc_Types.h]========================*/
