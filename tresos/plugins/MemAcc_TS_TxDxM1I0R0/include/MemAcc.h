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
#ifndef MEMACC_H
#define MEMACC_H

/*==================[inclusions]============================================*/

#include <TSAutosar.h>        /* EB specific standard types                 */
#include <MemAcc_Version.h>
#include <MemAcc_Cfg.h>
#include <MemAcc_Types.h>

/*==================[macros]================================================*/

#if (defined MEMACC_INIT_API_ID)
#error MEMACC_INIT_API_ID is already defined
#endif
/** \brief Defines API ID of function MemAcc_Init().
 **/
#define MEMACC_INIT_API_ID                             0x01U

#if (defined MEMACC_GET_VERSION_INFO_API_ID)
#error MEMACC_GET_VERSION_INFO_API_ID is already defined
#endif
/** \brief Defines API ID of function MemAcc_GetVersionInfo().
 **/
#define MEMACC_GET_VERSION_INFO_API_ID                 0x02U

#if (defined MEMACC_MAIN_FUNCTION_API_ID)
#error MEMACC_MAIN_FUNCTION_API_ID is already defined
#endif
/** \brief Defines API ID of function MemAcc_MainFunction().
 **/
#define MEMACC_MAIN_FUNCTION_API_ID                    0x03U

#if (defined MEMACC_CANCEL_API_ID)
#error MEMACC_CANCEL_API_ID is already defined
#endif
/** \brief Defines API ID of function MemAcc_Cancel().
 **/
#define MEMACC_CANCEL_API_ID                           0x04U

#if (defined MEMACC_GET_JOB_STATUS_API_ID)
#error MEMACC_GET_JOB_STATUS_API_ID is already defined
#endif
/** \brief Defines API ID of function MemAcc_GetJobStatus().
 **/
#define MEMACC_GET_JOB_STATUS_API_ID                   0x10U

#if (defined MEMACC_GET_MEMORY_INFO_API_ID)
#error MEMACC_GET_MEMORY_INFO_API_ID is already defined
#endif
/** \brief Defines API ID of function MemAcc_GetMemoryInfo().
 **/
#define MEMACC_GET_MEMORY_INFO_API_ID                  0x06U

#if (defined MEMACC_GET_PROCESSED_LENGTH_API_ID)
#error MEMACC_GET_PROCESSED_LENGTH_API_ID is already defined
#endif
/** \brief Defines API ID of function MemAcc_GetProcessedLength().
 **/
#define MEMACC_GET_PROCESSED_LENGTH_API_ID             0x07U

#if (defined MEMACC_GET_JOB_INFO_API_ID)
#error MEMACC_GET_JOB_INFO_API_ID is already defined
#endif
/** \brief Defines API ID of function MemAcc_GetJobInfo().
 **/
#define MEMACC_GET_JOB_INFO_API_ID                    0x08U

#if (defined MEMACC_READ_API_ID)
#error MEMACC_READ_API_ID is already defined
#endif
/** \brief Defines API ID of function MemAcc_Read().
 **/
#define MEMACC_READ_API_ID                             0x09U

#if (defined MEMACC_WRITE_API_ID)
#error MEMACC_WRITE_API_ID is already defined
#endif
/** \brief Defines API ID of function MemAcc_Write().
 **/
#define MEMACC_WRITE_API_ID                            0x0aU

#if (defined MEMACC_ERASE_API_ID)
#error MEMACC_ERASE_API_ID is already defined
#endif
/** \brief Defines API ID of function MemAcc_Erase().
 **/
#define MEMACC_ERASE_API_ID                            0x0bU

#if (defined MEMACC_COMPARE_API_ID)
#error MEMACC_COMPARE_API_ID is already defined
#endif
/** \brief Defines API ID of function MemAcc_Compare().
 **/
#define MEMACC_COMPARE_API_ID                         0x0cU

#if (defined MEMACC_BLANK_CHECK_API_ID)
#error MEMACC_BLANK_CHECK_API_ID is already defined
#endif
/** \brief Defines API ID of function MemAcc_BlankCheck().
 **/
#define MEMACC_BLANK_CHECK_API_ID                     0x0dU

#if (defined MEMACC_HW_SPECIFIC_SERVICE_API_ID)
#error MEMACC_HW_SPECIFIC_SERVICE_API_ID is already defined
#endif
/** \brief Defines API ID of function MemAcc_HwSpecificService().
 **/
#define MEMACC_HW_SPECIFIC_SERVICE_API_ID              0x0eU

#if (defined MEMACC_GET_JOB_RESULT_API_ID)
#error MEMACC_GET_JOB_RESULT_API_ID is already defined
#endif
/** \brief Defines API ID of function MemAcc_GetJobResult().
 **/
#define MEMACC_GET_JOB_RESULT_API_ID                   0x05U

#if (defined MEMACC_REQUEST_LOCK_ID)
#error MEMACC_REQUEST_LOCK_ID is already defined
#endif
/** \brief Defines API ID of function MemAcc_RequestLock().
 **/
#define MEMACC_REQUEST_LOCK_ID                         0x11U

#if (defined MEMACC_RELEASE_LOCK_ID)
#error MEMACC_RELEASE_LOCK_ID is already defined
#endif
/** \brief Defines API ID of function MemAcc_ReleaseLock().
 **/
#define MEMACC_RELEASE_LOCK_ID                         0x12U

/* !LINKSTO MemAcc.SWS_MemAcc_10038, 1 */
#if ( defined MEMACC_E_UNINIT )
#error MEMACC_E_UNINIT is already defined
#endif
/** \brief API service called without module initialization */
#define MEMACC_E_UNINIT                                0x01U

#if ( defined MEMACC_E_PARAM_POINTER )
#error MEMACC_E_PARAM_POINTER is already defined
#endif
/** \brief API service called with NULL pointer argument    */
#define MEMACC_E_PARAM_POINTER                         0x02U


#if ( defined MEMACC_E_PARAM_ADDRESS_AREA_ID )
#error MEMACC_E_PARAM_ADDRESS_AREA_ID is already defined
#endif
/** \brief API service called with wrong address area ID    */
#define MEMACC_E_PARAM_ADDRESS_AREA_ID                 0x03U

#if ( defined MEMACC_E_PARAM_ADDRESS_LENGTH )
#error MEMACC_E_PARAM_ADDRESS_LENGTH is already defined
#endif
/** \brief API service called with address and length not belonging to the passed address area ID */
#define MEMACC_E_PARAM_ADDRESS_LENGTH                  0x04U


#if ( defined MEMACC_E_PARAM_HW_ID )
#error MEMACC_E_PARAM_HW_ID is already defined
#endif
/** \brief API service called with a hardware ID not belonging to the passed address area ID */
#define MEMACC_E_PARAM_HW_ID                           0x05U


#if ( defined MEMACC_E_BUSY )
#error MEMACC_E_BUSY is already defined
#endif
/** \brief API service called for an address area ID with a pending job request */
#define MEMACC_E_BUSY                                  0x06U

#if ( defined MEMACC_E_MEM_INIT_FAILED )
#error MEMACC_E_MEM_INIT_FAILED is already defined
#endif
/** \brief Dynamic MEM driver activation failed due to inconsistent MEM driver binary */
#define MEMACC_E_MEM_INIT_FAILED                       0x07U


/*==================[external function declarations]========================*/

#define MEMACC_START_SEC_CODE
#include <MemAcc_MemMap.h>

/** \brief Service to initialize all variables and set the module state to initialized
 **
 ** This function initializes the MemAcc module.
 ** Normally, the ECU Manager invokes this API.
 **
 ** \param[in]  ConfigPtr Pointer to selected configuration structure
 **
 ** \ServiceID{0x01}
 ** \Reentrancy{Non Reentrant}
 ** \Synchronicity{Synchronous} */
extern FUNC(void, MEMACC_CODE) MemAcc_Init (const MemAcc_ConfigType* ConfigPtr);

/** \brief Service for reading the contents of a specific logical address
 **
 ** This API triggers a read job to copy data from the source address into the referenced destination data
 ** buffer. The result of this service can be retrieved using the MemAcc_GetJobResult API. If the
 ** read operation was successful, the result of the job is MEMACC_MEM_OK. If the read
 ** operation failed, the result of the job is either MEMACC_MEM_FAILED in case of a general
 ** error or MEMACC_MEM_ECC_CORRECTED/MEMACC_MEM_ECC_UNCORRECTED in
 ** case of a correctable/uncorrectable ECC error
 **
 ** \param[in]   AddressAreaId Numeric identifier of address area
 ** \param[in]   SourceAddress Read address in logical address space
 ** \param[out]  DestinationDataPtr Destination memory pointer to store the read data
 ** \param[in]   Length  Read length in bytes (aligned to read page size)
 **
 ** \return Std_ReturnType
 ** \retval E_OK     MemAcc accepted the read job
 ** \retval E_NOT_OK MemAcc rejected the read job
 **
 ** \ServiceID{0x09}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Asynchronous} */
extern FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_Read
(
  MemAcc_AddressAreaIdType AddressAreaId,
  MemAcc_AddressType SourceAddress,
  MemAcc_DataType* DestinationDataPtr,
  MemAcc_LengthType Length
);

/** \brief Service for writing a data in a specific logical address
 **
 ** This API triggers a write job to store the passed data to the provided address area with given address
 ** and length. The result of this service can be retrieved using the MemAcc_GetJobResult API. If
 ** the write operation was successful, the job result is MEMACC_MEM_OK. If there was an issue
 ** writing the data, the result is MEMACC_MEM_FAILED
 **
 ** \param[in]      AddressAreaId Numeric identifier of address area
 ** \param[in]      TargetAddress Write address in logical address space
 ** \param[in]      Length Write length in bytes (aligned to page size).
 ** \param[out]     SourceDataPtr Source data pointer (aligned to page size)
 **
 ** \return Std_ReturnType
 ** \retval E_OK     MemAcc accepted the write job
 ** \retval E_NOT_OK MemAcc rejected the write job
 **
 ** \ServiceID{0x0a}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Asynchronous} */
extern FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_Write
(
  MemAcc_AddressAreaIdType AddressAreaId,
  MemAcc_AddressType TargetAddress,
  const MemAcc_DataType* SourceDataPtr,
  MemAcc_LengthType Length
);

/** \brief Service for erasing sector or sectors
 **
 ** This API triggers an erase job of the given area defined by targetAddress and length. The result of this
 ** service can be retrieved using the Mem_GetJobResult API. If the erase operation was
 ** successful, the result of the job is MEM_JOB_OK. If the erase operation failed, e.g. due to a
 ** hardware issue, the result of the job is MEM_JOB_FAILED
 **
 ** \param[in]      AddressAreaId Numeric identifier of address area
 ** \param[in]      TargetAddress Erase address in logical address space (aligned to sector size
 ** \param[in]      Length Erase length in bytes (aligned to sector size)
 **
 ** \return Std_ReturnType
 ** \retval E_OK     MemAcc accepted the erase job
 ** \retval E_NOT_OK MemAcc rejected the erase job
 **
 ** \ServiceID{0x0b}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Asynchronous} */
extern FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_Erase
(
  MemAcc_AddressAreaIdType AddressAreaId,
  MemAcc_AddressType TargetAddress,
  MemAcc_LengthType Length
);

#if (MEMACC_COMPARE_API == STD_ON)
/** \brief Service comparing user buffer with data stored in the logical address
 **
 ** This operation compares the passed data to the memory content of the provided address area.
 ** The job terminates, if all bytes matched or a difference was detected. The result of this service
 ** can be retrieved using the MemAcc_GetJobResult() API. If the compare operation determined
 ** a mismatch, the result code is MEMACC_MEM_INCONSISTENT
 **
 ** \param[in]      AddressAreaId Numeric identifier of address area
 ** \param[in]      SourceAddress Compare address in logical address space
 ** \param[in]      DataPtr Pointer to user data which shall be compared to data in memory
 ** \param[in]      Length Compare length in bytes
 **
 ** \return Std_ReturnType
 ** \retval E_OK     MemAcc accepted the compare job
 ** \retval E_NOT_OK MemAcc rejected the compare job
 **
 ** \ServiceID{0x0c}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Asynchronous} */
extern FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_Compare
(
  MemAcc_AddressAreaIdType AddressAreaId,
  MemAcc_AddressType SourceAddress,
  const MemAcc_DataType* DataPtr,
  MemAcc_LengthType Length
);
#endif
/** \brief Service for checking if a specified logical address range is blank(erased)
 **
 ** This API starts a blank check operation starting from the address passed
 ** in the Address Area targeted, up to the specified length.
 ** MemAcc_GetJobResult API will return MEMACC_MEM_OK if range is blank, and
 ** MEMACC_MEM_INCONSISTENT if not blank
 **
 ** \param[in]      AddressAreaId Numeric identifier of address area.
 ** \param[in]      TargetAddress Address in logical address space.
 ** \param[in]      Length Blank check length in bytes.
 **
 ** \return Std_ReturnType
 ** \retval E_OK                    The requested job has been accepted
 ** \retval E_NOT_OK                The requested job has been rejected
 ** \retval E_MEM_SERVICE_NOT_AVAIL Driver service function is not available, no job was started
 **
 ** \ServiceID{0x0d}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Asynchronous} */
extern FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_BlankCheck
(
  MemAcc_AddressAreaIdType AddressAreaId,
  MemAcc_AddressType TargetAddress,
  MemAcc_LengthType Length
);

#if (                                                     \
      defined(MEMACC_DOXY_FLAG)                           \
      ||                                                  \
      (!defined(RTE_SCHM_SWCBSW_MEMACC_MAINFUNCTION))     \
    )                                                     \
/** \brief Service to handle the requested jobs and the internal management operations
 **
 ** This function asynchronously handles the requested read/write/erase jobs
 ** and performs all internal management operations.
 **
 ** \ServiceID{0x03}
 ** \Reentrancy{Non Reentrant}
 ** \Synchronicity{Synchronous} */
extern FUNC(void, MEMACC_CODE) MemAcc_MainFunction (void);

#endif

/** \brief Service for Canceling ongoing process
 **
 ** This API Triggers a cancel operation of the pending job for the address area referenced by the address AreaId. Cancelling affects only jobs in pending state
 **
 ** \param[in]      AddressAreaId Numeric identifier of address area
 **
 ** \ServiceID{0x04}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Asynchronous} */
extern FUNC(void, MEMACC_CODE) MemAcc_Cancel (MemAcc_AddressAreaIdType AddressAreaId);

/** \brief Service for getting the consolidated result of the last MemAcc job
 **
 ** This API returns the consolidated job result of the address area referenced by addressAreaId.
 ** If a MemAcc job is still pending, the API returns the result of the last MemAcc job
 **
 *  \param[in]      AddressAreaId Numeric identifier of address area
 **
 ** \return MemAcc_JobResultType
 ** \retval MEMACC_MEM_OK              Requested job finished successfully
 ** \retval MEMACC_MEM_FAILED          Requested job failed with error
 ** \retval MEMACC_MEM_INCONSISTENT    The results of the last MemAcc job didn’t meet the expected result
 ** \retval MEMACC_MEM_CANCELED        The last MemAcc job was canceled
 ** \retval MEMACC_MEM_ECC_CORRECTED   Requested job was corrected by the ECC
 ** \retval MEMACC_MEM_ECC_UNCORRECTED Requested ECC was unable to correct the last job
 **
 ** \ServiceID{0x05}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
extern FUNC(MemAcc_JobResultType, MEMACC_CODE) MemAcc_GetJobResult(MemAcc_AddressAreaIdType AddressAreaId);

/** \brief Service for getting the status of the last job
 ** This API returns the status of the MemAcc job referenced by addressAreaId
 **
 ** \param[in]      AddressAreaId Numeric identifier of address area
 **
 ** \return MemAcc_JobStatusType
 ** \retval MEMACC_JOB_IDLE           Job processing was completed or no job currently pending
 ** \retval MEMACC_JOB_PENDING        A job is currently being processed
 **
 ** \ServiceID{0x10}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
extern FUNC(MemAcc_JobStatusType, MEMACC_CODE) MemAcc_GetJobStatus(MemAcc_AddressAreaIdType AddressAreaId);
/** \brief This service function retrieves the physical memory device information of a specific address area
 **
 ** It can be used by an upper layer to get all necessary information to align the start address
 ** and trim the length for erase/write jobs
 **
 ** \param[in]      AddressAreaId Numeric identifier of address area.
 ** \param[in]      Address Address in logical address space from which corresponding memory device information shall be retrieved
 ** \param[out]     MemoryInfoPtr Destination memory pointer to store the memory device information
 **
 ** \return Std_ReturnType
 ** \retval E_OK     The requested addressAreaId and address are valid
 ** \retval E_NOT_OK The requested addressAreaId and address are invalid
 **
 ** \ServiceID{0x06}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
extern FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_GetMemoryInfo
(
  MemAcc_AddressAreaIdType AddressAreaId,
  MemAcc_AddressType Address,
  MemAcc_MemoryInfoType* MemoryInfoPtr
);

/** \brief Service for getting to processed length
 **
 ** Returns the accumulated number of bytes that have already been processed in the current job
 ** in the specified address area.
 **
 ** \param[in]      AddressAreaId Numeric identifier of address area.
 **
 ** \return MemAcc_LengthType Processed length of current job (in bytes)
 **
 ** \ServiceID{0x07}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
extern FUNC(MemAcc_LengthType, MEMACC_CODE) MemAcc_GetProcessedLength
(
  MemAcc_AddressAreaIdType AddressAreaId
);

/** \brief Service for getting to of the current memory job
 **
 ** It returns detailed information of the current memory job like memory device ID, job type, job
 ** processing state or job result, address area as well as address and length
 **
 ** \param[in]      AddressAreaId Numeric identifier of address area
 ** \param[out]     JobInfoPtr Structure pointer to return the detailed processing information of the current job
 **
 ** \ServiceID{0x08}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
extern FUNC(void, MEMACC_CODE) MemAcc_GetJobInfo
(
  MemAcc_AddressAreaIdType AddressAreaId,
  MemAcc_JobInfoType* JobInfoPtr
);

/** \brief This API returns version information of MemAcc module.
 **
 ** \param[out]     VersionInfoPtr Pointer to standard version information structure
 **
 ** \ServiceID{0x02}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
#if (MEMACC_VERSION_INFO_API == STD_ON)
extern FUNC(void, MEMACC_CODE) MemAcc_GetVersionInfo (Std_VersionInfoType *VersionInfoPtr);
#endif

/** \brief Service for locking an address area for exclusive access.
 **
 ** This API requests a lock of an address area for exclusive access.
 ** Once the lock is granted, lock notification function is called by MemAcc.
 **
 ** \param[in]      AddressAreaId Numeric identifier of address area
 ** \param[in]      Address Logical start address of the address area to identify the Mem driver to be locked
 ** \param[in]      Length Length of the address area to identify the Mem driver to be locked
 ** \param[in]      LockNotificationFctPtr Pointer to address area lock notification callback function
 **
 ** \return Std_ReturnType
 ** \retval E_OK     The requested job has been accepted by the module
 ** \retval E_NOT_OK The requested job has been rejected by the module
 **
 ** \ServiceID{0x11}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Asynchronous} */
extern FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_RequestLock
(
  MemAcc_AddressAreaIdType AddressAreaId,
  MemAcc_AddressType Address,
  MemAcc_LengthType Length,
  ApplicationLockNotification LockNotificationFctPtr
);

/** \brief Service for Releasing access lock of provided address area.
 **
 ** This API releases access lock of provided address area.
 **
 ** \param[in]      AddressAreaId Numeric identifier of address area
 ** \param[in]      Address Logical start address to identify lock area
 ** \param[in]      Length Length to identify lock area
 **
 ** \return Std_ReturnType
 ** \retval E_OK     The requested job has been accepted by the module
 ** \retval E_NOT_OK The requested job has been rejected by the module
 **
 ** \ServiceID{0x12}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
extern FUNC(Std_ReturnType, MEMACC_CODE) MemAcc_ReleaseLock
(
  MemAcc_AddressAreaIdType AddressAreaId,
  MemAcc_AddressType Address,
  MemAcc_LengthType Length
);
#define MEMACC_STOP_SEC_CODE
#include <MemAcc_MemMap.h>

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* ifndef MEMACC_H */

/*==================[end of file MemAcc.h]=====================================*/
