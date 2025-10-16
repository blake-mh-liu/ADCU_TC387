/**
 * \file
 *
 * \brief AUTOSAR ReProgMemM
 *
 * This file contains the implementation of the AUTOSAR
 * module ReProgMemM.
 *
 * \version 1.13.0
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef REPROGMEMM_H
#define REPROGMEMM_H


/*==[Includes]================================================================*/

#include "Std_Types.h"               /* AUTOSAR standard types */
#include "ReProgMemM_Version.h"
#include "ReProgMemM_Types.h"
#include <ReProgMemM_Cfg.h>

#if(REPROGMEMM_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>
#endif

/*==[Macros]==================================================================*/


/* List of DET IDs */
#define REPROGMEMM_INSTANCE_ID                                  (0x00U)
#define REPROGMEMM_MAIN_ID                                      (0x01U)
#define REPROGMEMM_LIFECYCLE_ID                                 (0x02U)
#define REPROGMEMM_FOTAREQUEST_ID                               (0x03U)
#define REPROGMEMM_SETEVENTSTATUS_ID                            (0x04U)
#define REPROGMEMM_RESETEVENTSTATUS_ID                          (0x05U)

#define REPROGMEMM_ALREADY_INITIALIZED                          (0x00U)
#define REPROGMEMM_NOT_INITIALIZED                              (0x01U)
#define REPROGMEMM_MODESTATUS_ER                                (0x02U)
#define REPROGMEMM_REQUESTSTATUS_ER                             (0x03U)
#define REPROGMEMM_FOTASTATUS_ER                                (0x04U)
#define REPROGMEMM_BLOCKID_ER                                   (0x05U)
#define REPROGMEMM_SERVID_GETVERSIONINFO                        (0x06U)
#define REPROGMEMM_SERVID_WRITE                                 (0x07U)

#define REPROGMEMM_NULL_PTR_ID                                  (0x01U)

/* -- List of the ReprogMemM DET Module IDs -- */
#define REPROGMEMM_DET_MODULE_ID                                260U


#if (defined EB_STATIC_CHECK)
/** \brief This macro can be used to avoid compiler warnings
 *
 * It is left empty to not produce a false positive for MISRA 14.2
 */
#define REPROGMEMM_PARAM_UNUSED(x)
#else
/** \brief This macro can be used to avoid compiler warnings */
#define REPROGMEMM_PARAM_UNUSED(x) ((void) (x))
#endif


#if (REPROGMEMM_DEV_ERROR_DETECT == STD_ON)
#define REPROGMEMM_DET_REPORT_ERROR(InstanceId, ServiceId,ErrorCode)                       \
  ((void)Det_ReportError(REPROGMEMM_DET_MODULE_ID, InstanceId, (ServiceId), (ErrorCode)))
#endif /* REPROGMEMM_DEV_ERROR_DETECT == STD_ON */

/*==[Types]===================================================================*/

/*==[Constants with external linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/
#if (REPROGMEMM_TOPO_FLASH_ENABLED == STD_ON)
#if (REPROGMEMM_DUALBANK_ENABLED == STD_ON)

#define REPROGMEMM_START_SEC_VAR_CLEARED_8
#include <ReProgMemM_MemMap.h>
/* Current active memory bank */
extern VAR (uint8, ReProgMemM_VAR) ReProgMemM_UbActiveBank;

#define REPROGMEMM_STOP_SEC_VAR_CLEARED_8
#include <ReProgMemM_MemMap.h>

#define REPROGMEMM_START_SEC_VAR_CLEARED_32
#include <ReProgMemM_MemMap.h>

/* Offset between the active and inactive bank to be used to read/write the physical address */
extern VAR (uint32, ReProgMemM_VAR) ReProgMemM_UlInactiveBankOffset;

#define REPROGMEMM_STOP_SEC_VAR_CLEARED_32
#include <ReProgMemM_MemMap.h>

#endif
#endif

#define REPROGMEMM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <ReProgMemM_MemMap.h>

/* Memory Request structure */
extern VAR (REPROGMEMM_Request_t, ReProgMemM_VAR) ReProgMemM_StRequest;

/* Flash sectors table described in the order of their addresses */
extern VAR  (boolean, ReProgMemM_VAR) IsFlashSecTableOrdered;

#define REPROGMEMM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <ReProgMemM_MemMap.h>

/*==[Definition of functions with external linkage]===========================*/

#define REPROGMEMM_START_SEC_CODE
#include <ReProgMemM_MemMap.h>


/** \brief Getter to the active bank
 *
 ** Function that returns the active bank value in the given parameter.
 *
 * \param[in]  ActiveBank value of the current active bank.
 *
 ** \return Result of the operation
 ** \retval E_OK operation successfull
 ** \retval E_NOT_OK operation failed
 *
 */
extern FUNC(Std_ReturnType, ReProgMemM_CODE) ReProgMemM_GetActiveBank
(
    P2VAR(uint8, AUTOMATIC, ReProgMemM_APPL_DATA)  UbActiveBank
);

/** \brief Getter to the inactive active bank address offset
 *
 **
 ** \return Inactive bank address offset
 *
 */
extern FUNC(uint32, ReProgMemM_CODE) ReProgMemM_GetInactiveBankAddrOffset
(
    VAR (uint32, ReProgMemM_VAR) startAddress
);

/** \brief Init function
 *
 ** Function for ReProgMemM module initialization by initializing the lower layer flash drivers
 *
 */
/* !LINKSTO SwD.ReProgMemM.Init.If,1 */
extern FUNC(void, ReProgMemM_CODE) ReProgMemM_Init(void);

/** \brief Main function
 *
 ** Function called in the scheduler in order to perform the driver operations
 *
 */
/* !LINKSTO SwD.ReProgMemM.MainFunction.If,1 */
extern FUNC(void, ReProgMemM_CODE) ReProgMemM_MainFunction(void);

/** \brief Job status function
 *
 ** Function providing the status of the drivers job as well the ReProgMemM job
 *
 * \return Job status for the memory operations
 * \retval REPROGMEMM_JOB_STATUS_NO_ERROR
 * \retval REPROGMEMM_JOB_STATUS_ERROR
 * \retval REPROGMEMM_JOB_STATUS_BUSY
 * \retval REPROGMEMM_JOB_STATUS_INIT_FAILED
 * \retval REPROGMEMM_JOB_STATUS_ALIGNMENT_FAILED
 * \retval REPROGMEMM_JOB_STATUS_NOTPROTECTED_FAILED
 * \retval REPROGMEMM_JOB_STATUS_BLANKCHECK_FAILED
 * \retval REPROGMEMM_JOB_STATUS_MEMORY_NOT_INITIALIZED
 *
 */
/* !LINKSTO SwD.ReProgMemM.GetJobStatus.If,1 */
extern FUNC(Std_ReturnType, ReProgMemM_CODE) ReProgMemM_GetJobStatus(void);

/** \brief Erase status function
 *
 ** Function that prepares the erase operation by updating the erase address, verifying the erase range (allowed range and aligned on a programmable sector)
 **   and updating the request information
 *
 * \param[in] ulAddress Address to be used for the operation
 * \param[in] ulLength Length to be used for the operation
 *
 * \return Erase operation preparation status
 * \retval REPROGMEMM_STATUS_PENDING      Erase operation preparation is successful. Lower layer erase will be performed on next cycle
 * \retval E_NOT_OK                       Erase operation preparation failed. Lower layer erase will not be performed on next cycle
 *
 */
/* !LINKSTO SwD.ReProgMemM.Read.If,1 */
extern FUNC(Std_ReturnType, ReProgMemM_CODE) ReProgMemM_Erase
(
    VAR (uint32, ReProgMemM_VAR) ulAddress,
    VAR (uint32, ReProgMemM_VAR) ulLength
);


/** \brief Read status function
 *
 ** Function that prepares the read operation by updating the read address, verifying that the range is allowed and updating the request information
 *
 * \param[in]  ulAddress Address to be used for the operation
 * \param[in]  ulLength Length to be used for the operation
 * \param[out] pubDataPtr Pointer to the data to be read.
 * \param[in]  ubBankType Type of the bank: inactive or active to be used for the operation
 *
 * \return Read operation preparation status
 * \retval E_OK      Read operation preparation is successful. Lower layer read will be performed on next cycle
 * \retval E_NOT_OK  Read operation preparation failed. Lower layer read will not be performed on next cycle
 *
 */
/* !LINKSTO SwD.ReProgMemM.Erase.If,1 */
extern FUNC(Std_ReturnType, ReProgMemM_CODE) ReProgMemM_Read
(
    VAR   (uint32,             ReProgMemM_VAR) ulAddress,
    VAR   (uint32,             ReProgMemM_VAR) ulLength,
    P2VAR (uint8,  AUTOMATIC,  ReProgMemM_APPL_DATA) pubDataPtr,
    VAR   (uint8,              ReProgMemM_VAR) ubBankType
);

/** \brief Write status function
 *
 ** Function that prepares the write operation by updating the write address, verifying the write range (allowed range and aligned on a programmable sector)
 **   and updating the request information
 *
 * \param[in]  ulAddress  Address to be used for the operation
 * \param[in]  ulLength   Length to be used for the operation
 * \param[in]  pubDataPtr Pointer to the data to be written.
 *
 * \return Write operation preparation status
 * \retval REPROGMEMM_STATUS_PENDING  Write operation preparation is successful. Lower layer write will be performed on next cycle
 * \retval E_NOT_OK                   Write operation preparation failed. Lower layer write will not be performed on next cycle
 *
 */
/* !LINKSTO SwD.ReProgMemM.Write.If,1 */
extern FUNC(Std_ReturnType, ReProgMemM_CODE) ReProgMemM_Write
(
    VAR   (uint32,           ReProgMemM_VAR) ulAddress,
    VAR   (uint32,           ReProgMemM_VAR) ulLength,
    P2VAR (uint8, AUTOMATIC, ReProgMemM_APPL_DATA) pubDataPtr
);

/** \brief GetVersionInfo function
 *
 ** Function updating the version information of the ReProgMemM module
 *
 * \param[out] versioninfo module version information : vendor id, module id, software major, minor and patch versions
 *
 */
extern FUNC(void, ReProgMemM_CODE) ReProgMemM_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, ReProgMemM_APPL_DATA) versioninfo
);

/** \brief DEM SetEventStatus function for General Failure.
 **
 ** Function providing the status of the drivers job as well the ReProgMemM job
 **
 ** \param[in]     index index of Block requested
 ** \param[in]     EventStatus Status of the event
 **
 ** \return DEM conform return value
 ** \retval E_OK        - Set request finished successfully
 */
/*extern FUNC(Std_ReturnType, ReProgMemM_CODE) ReProgMemM_SetEventStatus_GeneralFailure(uint8 BlockIndex, Dem_EventStatusType EventStatus);*/

/** \brief DEM SetEventStatus function for ProgMemM Failure.
 **
 ** Function providing the status of the drivers job as well the ReProgMemM job
 **
 ** \param[in]     index index of Block requested
 ** \param[in]     EventStatus Status of the event
 **
 ** \return DEM conform return value
 ** \retval E_OK        - Set request finished successfully
 */
/*extern FUNC(Std_ReturnType, ReProgMemM_CODE) ReProgMemM_SetEventStatus_ProgMemMFailure(uint16 BlockIndex, Dem_EventStatusType EventStatus);*/

/** \brief DEM ResetEventStatus function for ProgMemM Failure.
 **
 ** Function providing the status of the drivers job as well the ReProgMemM job
 **
 ** \param[in]     index index of Block requested
 **
 ** \return DEM conform return value
 ** \retval E_OK        - Reset request finished successfully
 */
/*extern FUNC(Std_ReturnType, ReProgMemM_CODE) ReProgMemM_ResetEventStatus_ProgMemMFailure(uint8 BlockIndex);*/

#define REPROGMEMM_STOP_SEC_CODE
#include <ReProgMemM_MemMap.h>

#endif /* #ifndef REPROGMEMM_H */

/*==================[end of file]=============================================*/

