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

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * The number of flash sectors depends on configuration settings. In case the flash sector table length is bigger that 1, the condition is always true
 *
 * TASKING-2) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * The number of flash sectors depends on configuration settings. In case the flash sector table length is 1, the condition is always true
 *
 * TASKING-3) Deviated Rule: W549
 * W549: condition is always false
 *
 * Reason:
 * The number of flash sectors depends on configuration settings. In case the flash sector table length is 1, the condition is always false
 */

/*==[Includes]================================================================*/
#include "Std_Types.h"               /* AUTOSAR standard types */

#include "ReProgMemM.h"
#include "ReProgMemM_Cfg.h"
#include "ReProgMemM_Interfaces.h"
#include <SchM_ReProgMemM.h>

#if(REPROGMEMM_USE_MEMACC_ENABLE == STD_ON)
#include "MemAcc.h"
#endif

#include "TSMem.h"
#include <ReProgMemM_Trace.h>             /* Dbg related macros for EB */
#include <ReProgMemM_UsrHdr.h>

/* ToDo: Abusive inclusion: No compliant Autosar:
 *  Functions in Appl layer => need RTE access 4
 */


/*==[Macros]==================================================================*/

#define REPROGMEMM_U32_MAX_VALUE  0xFFFFFFFFU

/*==[Declaration of functions with internal linkage]==========================*/
#define REPROGMEMM_START_SEC_CODE
#include <ReProgMemM_MemMap.h>

/** \brief ReProgMemM_GetDriverJobStatus function
 **
 ** Function to retrieve job status of memory driver
 **
 ** \return Job status
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
static FUNC(REPROGMEMM_JobStatus_t, ReProgMemM_CODE) ReProgMemM_GetDriverJobStatus(void);

/** \brief ReProgMemM_CopyFlashRoutinesToRam function
 **
 ** Function for copying the flash driver routines from ROM memory to RAM
 **
 ** \param[in] pRoutinesDataSource  Start address used for the write operation
 ** \param[in] pRoutinesDataDest    Length to be written
 ** \param[in] ulRoutinesDataLength Pointer to the data to be written
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
#if (REPROGMEMM_COPY_ROM_TO_RAM_ENABLE == STD_ON)
static FUNC(void, ReProgMemM_CODE) ReProgMemM_CopyFlashRoutinesToRam
(
    P2VAR (uint8,  AUTOMATIC, ReProgMemM_APPL_DATA) pRoutinesDataSource,
    P2VAR (uint8,  AUTOMATIC, ReProgMemM_APPL_DATA) pRoutinesDataDest,
    VAR   (uint32,            ReProgMemM_VAR) ulRoutinesDataLength
);
#endif
/** \brief ReProgMemM_SetRequestInfo function
 **
 ** Function for updating the driver operation request information
 **
 ** \param[in] ulAddr          Start address used for the write operation
 ** \param[in] ulLen           Length to be written
 ** \param[in] pubDataPtr      Pointer to the data to be written
 ** \param[in] ubRequestSelect Pointer to the data to be written
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
static FUNC(void, ReProgMemM_CODE) ReProgMemM_SetRequestInfo
(
    VAR   (uint32,                                ReProgMemM_VAR) ulAddr,
    VAR   (uint32,                                ReProgMemM_VAR) ulLen,
    P2VAR (uint8,                      AUTOMATIC, ReProgMemM_APPL_DATA) pubDataPtr,
    VAR   (REPROGMEMM_RequestSelect_t,            ReProgMemM_VAR) ubRequestSelect
);

/** \brief ReProgMemM_GetMemoryTypeByAddress function
 **
 ** Function that provides the memory type information associated to the given range
 **
 ** \param[in] ulAddr Address of the memory : to be used for the operation
 ** \param[in] ulLen  Length of the memory : to be used for the operation
 **
 ** \return Memory type corresponding to the given range
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
static FUNC(REPROGMEMM_MemoryType_t, ReProgMemM_CODE) ReProgMemM_GetMemoryTypeByAddress
(
    VAR (uint32, ReProgMemM_VAR) ulAddr,
    VAR (uint32, ReProgMemM_VAR) ulLen
);

/** \brief ReProgMemM_GetMemoryIdxByAddress function
 **
 ** Function that provides the memory id associated to the given range
 **
 ** \param[in] ulAddr Address of the memory : to be used for the operation
 ** \param[in] ulLen  Length of the memory : to be used for the operation
 **
 ** \return Memory id corresponding to the given range
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
static FUNC(REPROGMEMM_MemoryIdx_t, ReProgMemM_CODE) ReProgMemM_GetMemoryIdxByAddress
(
    VAR (uint32, ReProgMemM_VAR) ulAddr,
    VAR (uint32, ReProgMemM_VAR) ulLen
);

/** \brief ReProgMemM_IsRangeAddressAllowed function
 **
 ** Function that indicates if the range associated to the given address and length is allowed or not
 **
 ** \param[in] ulAddr Address to be used for the operation
 ** \param[in] ulLen  Length to be used for the operation
 ** \param[in] operationFlag Requested operation (FALSE = erase/write, TRUE = read)
 **
 ** \return Range status
 ** \retval REPROGMEMM_TRUE  Given range is allowed
 ** \retval REPROGMEMM_FALSE Given range is not allowed
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
static FUNC(REPROGMEMM_Boolean_t, ReProgMemM_CODE) ReProgMemM_IsRangeAddressAllowed
(
    VAR (uint32, ReProgMemM_VAR) ulAddr,
    VAR (uint32, ReProgMemM_VAR) ulLen,
    VAR  (REPROGMEMM_Boolean_t, ReProgMemM_VAR)  operationFlag
);

/** \brief ReProgMemM_IsAddressAlignedOnSector function
 **
 ** Function that indicates if the given address is aligned on a sector
 **
 ** \param[in] ulAddr Address to be used for the operation
 **
 ** \return Alignment status
 ** \retval REPROGMEMM_TRUE  Given address is aligned on a sector
 ** \retval REPROGMEMM_FALSE Given address is not aligned on a sector
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
static FUNC(REPROGMEMM_Boolean_t, ReProgMemM_CODE) ReProgMemM_IsAddressAlignedOnSector
(
    VAR (uint32, ReProgMemM_VAR) ulAddr
);

/** \brief ReProgMemM_GetSectorByAddress function
 **
 ** Function that provides the sector information associated to the given range
 **
 ** \param[in] ulAddr Address to be used for the operation
 ** \param[in] ulLen  Length to be used for the operation
 ** \param[in] ulStartAddrToBeTreat Address to be used for the operation
 ** \param[inout] ulEndAddrTobeTreat  End Address to be used for the operation
 **
 ** \return Sector associated to the given range
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
static FUNC(uint32, ReProgMemM_CODE) ReProgMemM_GetSectorByAddress
(
    VAR (uint32, ReProgMemM_VAR) ulAddr,
    VAR (uint32, ReProgMemM_VAR) ulLen,
    VAR (uint32, ReProgMemM_VAR) ulStartAddrToBeTreat,
    P2VAR (uint32,  AUTOMATIC, ReProgMemM_APPL_DATA) ulEndAddrTobeTreat
);

/** \brief ReProgMemM_IsAddressAlignedOnPage function
 **
 ** Function that indicates if the given address is aligned on a page
 **
 ** \param[in] ulAddr Address to be used for the operation
 **
 ** \return Address alignment on page
 ** \retval REPROGMEMM_TRUE  Given address is aligned on a page
 ** \retval REPROGMEMM_FALSE Given address is not aligned on a page
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
static FUNC(REPROGMEMM_Boolean_t, ReProgMemM_CODE) ReProgMemM_IsAddressAlignedOnPage
(
    VAR (uint32, ReProgMemM_VAR) ulAddr
);

/** \brief ReProgMemM_EraseMngt function
 **
 ** Function that perfoms an erase operation by calling the lower layer driver
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{ASynchronous}
 */
static FUNC(void, ReProgMemM_CODE) ReProgMemM_EraseMngt(void);

/** \brief ReProgMemM_WriteMngt function
 **
 ** Function that perfoms a write operation by calling the lower layer driver
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{ASynchronous}
 */
static FUNC(void, ReProgMemM_CODE) ReProgMemM_WriteMngt(void);

/** \brief ReProgMemM_ReadMngt function
 **
 ** Function that perfoms a read operation by calling the lower layer driver
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
static FUNC(void, ReProgMemM_CODE) ReProgMemM_ReadMngt(void);

/** \brief ReProgMemM_OrderFlashSecTableByAddr function
 **
 ** Function that order the flash sector table according to their start addresses
 **
 ** \param[in] Ordering Sector table
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
static FUNC(void, ReProgMemM_CODE) ReProgMemM_OrderFlashSecTableByAddr
(
  P2VAR(REPROGMEMM_CfgMemorySectorsProt_t, AUTOMATIC, ReProgMemM_APPL_DATA) secTable
);

#define REPROGMEMM_STOP_SEC_CODE
#include <ReProgMemM_MemMap.h>

/*==[Constants with external linkage]=========================================*/

/*==[Constants with internal linkage]=========================================*/

/*==[Variables with external linkage]=========================================*/

#if (REPROGMEMM_TOPO_FLASH_ENABLED == STD_ON)
#if (REPROGMEMM_DUALBANK_ENABLED == STD_ON)

#define REPROGMEMM_START_SEC_VAR_CLEARED_8
#include <ReProgMemM_MemMap.h>

/* Active bank global variable */
VAR (uint8,  ReProgMemM_VAR) ReProgMemM_UbActiveBank;

#define REPROGMEMM_STOP_SEC_VAR_CLEARED_8
#include <ReProgMemM_MemMap.h>

#define REPROGMEMM_START_SEC_VAR_CLEARED_32
#include <ReProgMemM_MemMap.h>

/* Offset between the active and inactive bank to be used to read/write the physical address */
VAR (uint32, ReProgMemM_VAR) ReProgMemM_UlInactiveBankOffset;

#define REPROGMEMM_STOP_SEC_VAR_CLEARED_32
#include <ReProgMemM_MemMap.h>
#endif
#endif

#define REPROGMEMM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <ReProgMemM_MemMap.h>

/* Memory Request structure */
VAR (REPROGMEMM_Request_t,  ReProgMemM_VAR) ReProgMemM_StRequest;

/* Flash sectors table described in the order of their addresses */
VAR  (boolean, ReProgMemM_VAR) IsFlashSecTableOrdered;

#define REPROGMEMM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <ReProgMemM_MemMap.h>

/*==[Variables with internal linkage]=========================================*/

#define REPROGMEMM_START_SEC_VAR_INIT_8
#include <ReProgMemM_MemMap.h>

static VAR   (REPROGMEMM_MemoryType_t,             ReProgMemM_VAR) ReProgMemM_UbMemoryType;
static VAR   (REPROGMEMM_MemoryIdx_t,              ReProgMemM_VAR) ReProgMemM_UbMemoryIdx;
static P2VAR (uint8,                   AUTOMATIC,  ReProgMemM_APPL_DATA) ReProgMemM_UbDataToWritePtr;

static   VAR (REPROGMEMM_CfgMemorySectorsProt_t, ReProgMemM_VAR)    SectorsTable[REPROGMEMM_FLASH_SECTORS_ELEMENTS];

#define REPROGMEMM_STOP_SEC_VAR_INIT_8
#include <ReProgMemM_MemMap.h>

/*==[Definition of functions with external linkage]===========================*/

#define REPROGMEMM_START_SEC_CODE
#include <ReProgMemM_MemMap.h>


#if (REPROGMEMM_DUALBANK_ENABLED == STD_ON)
/** \brief ReProgMemM_GetActiveBank function
 **
 ** Getter function for ActiveBank value.
 */
FUNC(Std_ReturnType, ReProgMemM_CODE) ReProgMemM_GetActiveBank
(
    P2VAR(uint8, AUTOMATIC, ReProgMemM_APPL_DATA)  UbActiveBank
)
{
    VAR (Std_ReturnType,       ReProgMemM_VAR) RetVal;

    DBG_REPROGMEMM_GETACTIVEBANK_ENTRY(UbActiveBank);

    if(NULL_PTR != UbActiveBank)
    {
        /* Get the current active bank */
        /* !LINKSTO SwD.ReProgMemM.GetActiveBank.1,1 */
        /* !LINKSTO SwD.ReProgMemM.GetActiveBank.If,1 */
        RetVal = ReProgMemM_CustomGetActiveBank(UbActiveBank);

        if(E_NOT_OK == RetVal)
        {
        /* !LINKSTO SwD.ReProgMemM.GetActiveBank.2,1 */
        /* Set active bank to an invalid value */

            *UbActiveBank = REPROGMEMM_DUALBANK_ACTIVE_BANK_NOK;
        }
    }
    else
    {
      RetVal = E_NOT_OK;
    }

    DBG_REPROGMEMM_GETACTIVEBANK_EXIT(RetVal);
    return RetVal;
}

/** \brief ReProgMemM_GetInactiveBankAddrOffset function
 **
 ** \param[in] startAddress used to determine the offset according to the address range
 **
 ** Getter to the inactive active bank address offset
 */
FUNC(uint32, ReProgMemM_CODE) ReProgMemM_GetInactiveBankAddrOffset
(
    VAR (uint32, ReProgMemM_VAR) startAddress
)
{
    VAR (uint32,       ReProgMemM_VAR) RetVal;

    DBG_REPROGMEMM_GETINACTIVEBANKADDROFFSET_ENTRY();

    /* Get Inactive bank address offset */
    /* !LINKSTO SwD.ReProgMemM.GetInactiveBankAddrOffset.1,2 */
    /* !LINKSTO SwD.ReProgMemM.GetInactiveBankAddrOffset.If,2 */
    RetVal = ReProgMemM_CustomGetInactiveBankAddrOffset(startAddress);

    DBG_REPROGMEMM_GETINACTIVEBANKADDROFFSET_EXIT(RetVal);
    return RetVal;
}
#endif

/** \brief ReProgMemM_Init function
 **
 ** full description can be found in ReProgMemM.h
 */
FUNC(void, ReProgMemM_CODE) ReProgMemM_Init(void)
{
#if (REPROGMEMM_COPY_ROM_TO_RAM_ENABLE == STD_ON)
    VAR (uint32, ReProgMemM_VAR) ulLength;
#endif
#if (REPROGMEMM_TOPO_FLASH_ENABLED == STD_ON)
    VAR (REPROGMEMM_JobStatus_t, ReProgMemM_VAR) ubInternalDriverStatus;
#endif

#if(REPROGMEMM_TOPO_FLASHEXT_ENABLED == STD_ON)
    VAR (REPROGMEMM_JobStatus_t, ReProgMemM_VAR) ubExternalDriverStatus;
#endif

    DBG_REPROGMEMM_INIT_ENTRY();

    /* Initialize all configured and enabled drivers */
#if (REPROGMEMM_TOPO_FLASH_ENABLED == STD_ON)
#if (REPROGMEMM_DUALBANK_ENABLED == STD_ON)
    /* Initialize the dual bank process */
    /* !LINKSTO SwD.ReProgMemM.Init.6,1 */
    /* !LINKSTO SwD.OTA.DualBankInit.If,1 */
    ReProgMemM_DualBank_Init();
    /* Get the current active bank */
    (void) ReProgMemM_GetActiveBank(&ReProgMemM_UbActiveBank);

#endif
#if (REPROGMEMM_COPY_ROM_TO_RAM_ENABLE == STD_ON)
    /* Copy the whole "Flash_API_ROM" ROM section to "Flash_API_RAM" RAM section */
    ulLength = REPROGMEMM_FLASH_ROUTINES_ROM_ADDR_END - REPROGMEMM_FLASH_ROUTINES_ROM_ADDR_START;
    ulLength = ulLength + (uint32)1U;

    /* !LINKSTO SwD.ReProgMemM.Init.5,2 */
    ReProgMemM_CopyFlashRoutinesToRam((uint8*)(REPROGMEMM_FLASH_ROUTINES_ROM_ADDR_START), (uint8*)(REPROGMEMM_FLASH_ROUTINES_RAM_ADDR_START), ulLength);
#endif

    /* !LINKSTO SwD.ReProgMemM.Init.3,1 */
    /* Initialization of the used Flash driver */
    ubInternalDriverStatus = ReProgMemM_FlashInit(REPROGMEMM_TRUE);
#endif

#if (REPROGMEMM_TOPO_FLASHEXT_ENABLED == STD_ON)
    /* !LINKSTO SwD.ReProgMemM.Init.4,1 */
    /* Initialization of the used external Flash driver */
    ubExternalDriverStatus = ReProgMemM_FlashInit(REPROGMEMM_FALSE);
#endif

#if (REPROGMEMM_TOPO_FLASH_ENABLED == STD_ON)
    if (E_OK == ubInternalDriverStatus)
    {
        ReProgMemM_StRequest.ubJobStatus = REPROGMEMM_JOB_STATUS_INTERNAL_INIT_OK;
    }
    else
    {
        ReProgMemM_StRequest.ubJobStatus = REPROGMEMM_JOB_STATUS_MEMORY_NOT_INITIALIZED;
    }
#endif
#if (REPROGMEMM_TOPO_FLASHEXT_ENABLED == STD_ON)
    if (E_OK == ubExternalDriverStatus)
    {
        ReProgMemM_StRequest.ubJobStatus = REPROGMEMM_JOB_STATUS_EXTERNAL_INIT_OK;
    }
    else
    {
        ReProgMemM_StRequest.ubJobStatus = REPROGMEMM_JOB_STATUS_MEMORY_NOT_INITIALIZED;
    }
#endif
#if ((REPROGMEMM_TOPO_FLASH_ENABLED == STD_OFF) && (REPROGMEMM_TOPO_FLASHEXT_ENABLED == STD_OFF))
    /* Unsupported memory initialization */
    ReProgMemM_StRequest.ubJobStatus = REPROGMEMM_JOB_STATUS_MEMORY_NOT_INITIALIZED;
#endif

    ReProgMemM_StRequest.ubRequestSelect = REPROGMEMM_REQUEST_NO_FLASH_RQT;

    SchM_Enter_ReProgMemM_SCHM_ReProgMemM_EXCLUSIVE_AREA_0();
    IsFlashSecTableOrdered = TRUE;
    SchM_Exit_ReProgMemM_SCHM_ReProgMemM_EXCLUSIVE_AREA_0();

    /* !LINKSTO SwD.ReProgMemM.Init.8,1 */
    TS_MemCpy(SectorsTable, m_astReProgMemMMemorySecProtCfg, sizeof(SectorsTable));
    ReProgMemM_OrderFlashSecTableByAddr(SectorsTable);

    DBG_REPROGMEMM_INIT_EXIT();
}

/** \brief ReProgMemM_MainFunction function
 **
 ** full description can be found in ReProgMemM.h
 */
FUNC(void, ReProgMemM_CODE) ReProgMemM_MainFunction(void)
{
    VAR (REPROGMEMM_RequestSelect_t, ReProgMemM_VAR) ubRequestSelect;

    DBG_REPROGMEMM_MAINFUNCTION_ENTRY();

    SchM_Enter_ReProgMemM_SCHM_ReProgMemM_EXCLUSIVE_AREA_0();

    ubRequestSelect = ReProgMemM_StRequest.ubRequestSelect;

   SchM_Exit_ReProgMemM_SCHM_ReProgMemM_EXCLUSIVE_AREA_0();

    switch (ubRequestSelect)
    {
        /* Erase request received : call Erase Manage function*/
        case REPROGMEMM_REQUEST_ERASE :
            /* !LINKSTO SwD.ReProgMemM.MainFunction.2,1 */
            ReProgMemM_EraseMngt();
            break;

        /* Write request received : call Write Manage function*/
        case REPROGMEMM_REQUEST_WRITE :
            /* !LINKSTO SwD.ReProgMemM.MainFunction.3,1 */
            ReProgMemM_WriteMngt();
            break;

        /* Read request received : call Read Manage function*/
        case REPROGMEMM_REQUEST_READ :
            /* !LINKSTO SwD.ReProgMemM.MainFunction.4,1 */
            ReProgMemM_ReadMngt();
            break;

        /* No Flash request received*/
        default :
            /* !LINKSTO SwD.ReProgMemM.MainFunction.1,1 */
            /* Nothing to do */
            break;
    }


    DBG_REPROGMEMM_MAINFUNCTION_EXIT();
}

/** \brief ReProgMemM_GetJobStatus function
 **
 ** full description can be found in ReProgMemM.h
 */
FUNC(Std_ReturnType, ReProgMemM_CODE) ReProgMemM_GetJobStatus(void)
{
    VAR (Std_ReturnType,         ReProgMemM_VAR) RetVal;
    VAR (REPROGMEMM_JobStatus_t, ReProgMemM_VAR) ubDriverStatus;

    DBG_REPROGMEMM_GETJOBSTATUS_ENTRY();


   SchM_Enter_ReProgMemM_SCHM_ReProgMemM_EXCLUSIVE_AREA_0();

    /* Get the memory type of the job */
    ReProgMemM_UbMemoryType = ReProgMemM_GetMemoryTypeByAddress ( ReProgMemM_StRequest.ulStartAddress, ReProgMemM_StRequest.ulLength);

#if ((REPROGMEMM_USE_MEMACC_ENABLE == STD_ON) || (REPROGMEMM_TOPO_FLASH_ENABLED == STD_ON) || (REPROGMEMM_TOPO_FLASHEXT_ENABLED == STD_ON))

#if(REPROGMEMM_USE_MEMACC_ENABLE == STD_ON)

    ubDriverStatus = ReProgMemM_GetDriverJobStatus();

#else
#if (REPROGMEMM_TOPO_FLASH_ENABLED == STD_ON)
    if (REPROGMEMM_MEM_TYPE_FLASH     == ReProgMemM_UbMemoryType)
    {
        /* !LINKSTO SwD.ReProgMemM.JobStatus.1,2 */
        ubDriverStatus = ReProgMemM_GetDriverJobStatus();
    }
    else
    {
        /* !LINKSTO SwD.ReProgMemM.JobStatus.6,2 */
        ubDriverStatus = REPROGMEMM_JOB_STATUS_ERROR;
    }
#else/* (REPROGMEMM_TOPO_FLASHEXT_ENABLED == STD_ON) */
    if (REPROGMEMM_MEM_TYPE_FLASH_EXT == ReProgMemM_UbMemoryType)
    {
        /* !LINKSTO SwD.ReProgMemM.JobStatus.2,2 */
        ubDriverStatus = ReProgMemM_GetDriverJobStatus();
    }
    else
    {
        /* !LINKSTO SwD.ReProgMemM.JobStatus.6,2 */
        ubDriverStatus = REPROGMEMM_JOB_STATUS_ERROR;
    }

#endif
#endif
#else
     ubDriverStatus = REPROGMEMM_JOB_STATUS_ERROR;
#endif

    /* Return the job status */
    if (((REPROGMEMM_JOB_STATUS_NO_ERROR == ReProgMemM_StRequest.ubJobStatus) && (ubDriverStatus == REPROGMEMM_JOB_STATUS_NO_ERROR)) ||
           (ReProgMemM_StRequest.ubJobStatus == REPROGMEMM_JOB_STATUS_INTERNAL_INIT_OK))
    {
        /* !LINKSTO SwD.ReProgMemM.JobStatus.3,2 */
        RetVal = E_OK;
    }
    else if ((REPROGMEMM_JOB_STATUS_BUSY == ReProgMemM_StRequest.ubJobStatus) || (ubDriverStatus == REPROGMEMM_JOB_STATUS_BUSY))
    {
        /* !LINKSTO SwD.ReProgMemM.JobStatus.5,1 */
        RetVal = REPROGMEMM_STATUS_PENDING;
    }
    else
    {
        /* !LINKSTO SwD.ReProgMemM.JobStatus.4,1 */
        RetVal = E_NOT_OK;
    }

    SchM_Exit_ReProgMemM_SCHM_ReProgMemM_EXCLUSIVE_AREA_0();

    DBG_REPROGMEMM_GETJOBSTATUS_EXIT(RetVal);
    return (RetVal);
}

/** \brief ReProgMemM_Erase function
 **
 ** full description can be found in ReProgMemM.h
 */
FUNC(Std_ReturnType, ReProgMemM_CODE) ReProgMemM_Erase
(
    VAR (uint32,  ReProgMemM_VAR) ulAddress,
    VAR (uint32,  ReProgMemM_VAR) ulLength
)
{
    VAR (Std_ReturnType, ReProgMemM_VAR) RetVal;
    VAR (REPROGMEMM_Address_t, ReProgMemM_VAR) ulCustomOffset;
    VAR (REPROGMEMM_Address_t, ReProgMemM_VAR) ulEraseAddr;

    DBG_REPROGMEMM_ERASE_ENTRY(ulAddress,ulLength);

    ulEraseAddr = 0x00000000U;
    RetVal      = E_OK;

    SchM_Enter_ReProgMemM_SCHM_ReProgMemM_EXCLUSIVE_AREA_0();

    /* Get the memory type of the job */
    ReProgMemM_UbMemoryType = ReProgMemM_GetMemoryTypeByAddress (ulAddress, ulLength);

    /* Get the memory index of the job */
    ReProgMemM_UbMemoryIdx = ReProgMemM_GetMemoryIdxByAddress (ulAddress, ulLength);

   if (ReProgMemM_UbMemoryIdx != REPROGMEMM_MEMORY_NB)
   {
#if (REPROGMEMM_CUSTOM_OFFSET_ENABLE == STD_ON)
        /* !LINKSTO SwD.ReProgMemM.Erase.9,1 */
        ulCustomOffset = ReProgMemM_CustomGetOffset(ulAddress);
#else
        /* !LINKSTO SwD.ReProgMemM.Erase.10,1 */
        ulCustomOffset = 0x00000000U;
#endif


        if (REPROGMEMM_MEM_TYPE_FLASH == ReProgMemM_UbMemoryType)
        {
#if (REPROGMEMM_DUALBANK_ENABLED == STD_ON)
            /* Set the aligned erase address */
            if (REPROGMEMM_DUALBANK_A_BANK_ACTIVE == ReProgMemM_UbActiveBank)
            {
                /* !LINKSTO SwD.ReProgMemM.Erase.3,2 */
                ReProgMemM_UlInactiveBankOffset = ReProgMemM_CustomGetInactiveBankAddrOffset(ulAddress);
                ulEraseAddr = (uint32)(ulAddress + ulCustomOffset + ReProgMemM_UlInactiveBankOffset + m_astReProgMemMMemoryCfg[ReProgMemM_UbMemoryIdx].ulAddressOffset);
            }
            else if(REPROGMEMM_DUALBANK_B_BANK_ACTIVE == ReProgMemM_UbActiveBank)
            {
                ulEraseAddr = (uint32)(ulAddress + ulCustomOffset + m_astReProgMemMMemoryCfg[ReProgMemM_UbMemoryIdx].ulAddressOffset);
            }
            else
            {
                /* !LINKSTO SwD.ReProgMemM.Erase.13,1 */
                RetVal = E_NOT_OK;
            }
#endif
#if ((REPROGMEMM_TOPO_FLASH_ENABLED == STD_ON) && (REPROGMEMM_DUALBANK_ENABLED == STD_OFF))
            /* !LINKSTO SwD.ReProgMemM.Erase.8,2 */
            /* Set the aligned erase address */
            ulEraseAddr = (uint32)(ulAddress + ulCustomOffset + m_astReProgMemMMemoryCfg[ReProgMemM_UbMemoryIdx].ulAddressOffset);
#endif
        }
        else if (REPROGMEMM_MEM_TYPE_FLASH_EXT == ReProgMemM_UbMemoryType)
        {
#if (REPROGMEMM_TOPO_FLASHEXT_ENABLED == STD_ON)
            /* !LINKSTO SwD.ReProgMemM.Erase.1,1 */
            /* Set the aligned erase address */
            ulEraseAddr = (uint32)(ulAddress + ulCustomOffset + m_astReProgMemMMemoryCfg[ReProgMemM_UbMemoryIdx].ulAddressOffset);
#endif
        }
        else
        {
            /* !LINKSTO SwD.ReProgMemM.Erase.11,1 */
            /* Unsupported memory - Can not happen */
        }
    }
    else
    {
        RetVal = E_NOT_OK;
    }

    if ((ReProgMemM_StRequest.ubJobStatus != REPROGMEMM_JOB_STATUS_MEMORY_NOT_INITIALIZED) && (E_NOT_OK != RetVal))
    /* Return the job status */
    {
        if (REPROGMEMM_TRUE == ReProgMemM_IsRangeAddressAllowed(ulEraseAddr, ulLength, REPROGMEMM_FALSE))
        {
            if (REPROGMEMM_TRUE == ReProgMemM_IsAddressAlignedOnSector(ulEraseAddr))
            {
                /* !LINKSTO SwD.ReProgMemM.Erase.7,1 */
                /* Update the request Info */
                ReProgMemM_SetRequestInfo (ulEraseAddr,ulLength, NULL_PTR,REPROGMEMM_REQUEST_ERASE);

                /* Return Memory access pending */
                RetVal = REPROGMEMM_STATUS_PENDING;
            }
            else
            {
                /* !LINKSTO SwD.ReProgMemM.Erase.6,2 */
                RetVal = E_NOT_OK;
            }
        }
        else
        {
            RetVal = E_NOT_OK;
        }
    }
    else
    {
        RetVal = E_NOT_OK;
    }
    SchM_Exit_ReProgMemM_SCHM_ReProgMemM_EXCLUSIVE_AREA_0();
    DBG_REPROGMEMM_ERASE_EXIT(RetVal);
    return (RetVal);
}

/** \brief ReProgMemM_Read function
 **
 ** full description can be found in ReProgMemM.h
 */
FUNC(Std_ReturnType, ReProgMemM_CODE) ReProgMemM_Read
(
    VAR  (uint32,            ReProgMemM_VAR) ulAddress,
    VAR  (uint32,            ReProgMemM_VAR) ulLength,
    P2VAR(uint8, AUTOMATIC,  ReProgMemM_APPL_DATA) pubDataPtr,
    VAR  (uint8,             ReProgMemM_VAR) ubBankType
)
{
    VAR (Std_ReturnType,       ReProgMemM_VAR) RetVal;
    VAR (REPROGMEMM_Address_t, ReProgMemM_VAR) ulCustomOffset;
    VAR (REPROGMEMM_Address_t, ReProgMemM_VAR) ulReadAddr;

#if (REPROGMEMM_DUALBANK_ENABLED == STD_ON)
    VAR (uint32, ReProgMemM_VAR) ulOffset;
#endif

    DBG_REPROGMEMM_READ_ENTRY(ulAddress,ulLength,pubDataPtr,ubBankType);

    ulReadAddr = 0x00000000U;
    RetVal     = E_OK;

     SchM_Enter_ReProgMemM_SCHM_ReProgMemM_EXCLUSIVE_AREA_0();

    /* Get the memory type of the job */
    ReProgMemM_UbMemoryType = ReProgMemM_GetMemoryTypeByAddress(ulAddress, ulLength);

    /* Get the memory index of the job */
    ReProgMemM_UbMemoryIdx = ReProgMemM_GetMemoryIdxByAddress(ulAddress, ulLength);
   if (ReProgMemM_UbMemoryIdx != REPROGMEMM_MEMORY_NB)
   {
#if (REPROGMEMM_CUSTOM_OFFSET_ENABLE == STD_ON)
        /* !LINKSTO SwD.ReProgMemM.Read.9,1 */
        ulCustomOffset = ReProgMemM_CustomGetOffset(ulAddress);
#else
        /* !LINKSTO SwD.ReProgMemM.Read.8,1 */
        ulCustomOffset = 0x00000000U;
#endif

        if (REPROGMEMM_MEM_TYPE_FLASH == ReProgMemM_UbMemoryType)
        {
#if (REPROGMEMM_DUALBANK_ENABLED == STD_ON)
            /* Set the aligned read address for active bank */
            if (REPROGMEMM_MEMACC_ACTIVE_BANK == ubBankType)
            {
                /* !LINKSTO SwD.ReProgMemM.Read.2,1 */
                ulOffset = (uint32)0U;
                ulReadAddr = (uint32)(ulAddress + ulCustomOffset + ulOffset + m_astReProgMemMMemoryCfg[ReProgMemM_UbMemoryIdx].ulAddressOffset);
            }
            /* Set the aligned read address for inactive bank */
            else if (REPROGMEMM_MEMACC_INACTIVE_BANK == ubBankType)
            {
                /* !LINKSTO SwD.ReProgMemM.Read.1,2 */
                ReProgMemM_UlInactiveBankOffset = ReProgMemM_CustomGetInactiveBankAddrOffset(ulAddress);
                ulOffset = ReProgMemM_UlInactiveBankOffset;
                ulReadAddr = (uint32)(ulAddress + ulCustomOffset + ulOffset + m_astReProgMemMMemoryCfg[ReProgMemM_UbMemoryIdx].ulAddressOffset);
            }
            else
            {
                /* !LINKSTO SwD.ReProgMemM.Read.13,1 */
                RetVal = E_NOT_OK;
            }
#endif
#if ((REPROGMEMM_TOPO_FLASH_ENABLED == STD_ON) && (REPROGMEMM_DUALBANK_ENABLED == STD_OFF))
            /* !LINKSTO SwD.ReProgMemM.Read.4,2 */
            /* Set the aligned read address */
            ulReadAddr = (uint32)(ulAddress + ulCustomOffset + m_astReProgMemMMemoryCfg[ReProgMemM_UbMemoryIdx].ulAddressOffset);
#endif
        }
        else if (REPROGMEMM_MEM_TYPE_FLASH_EXT == ReProgMemM_UbMemoryType)
        {
#if (REPROGMEMM_TOPO_FLASHEXT_ENABLED == STD_ON)
            /* !LINKSTO SwD.ReProgMemM.Read.7,1 */
            /* Set the aligned read address */
            ulReadAddr = (uint32)(ulAddress + ulCustomOffset + m_astReProgMemMMemoryCfg[ReProgMemM_UbMemoryIdx].ulAddressOffset);
#endif
        }
        else
        {
            /* !LINKSTO SwD.ReProgMemM.Read.10,1 */
            /* Unsupported memory - Can not happen */
        }
    }
    else
    {
        RetVal = E_NOT_OK;
    }

    if ((ReProgMemM_StRequest.ubJobStatus != REPROGMEMM_JOB_STATUS_MEMORY_NOT_INITIALIZED) && (E_NOT_OK != RetVal))
    /* Return the job status */
    {
        /* !LINKSTO SwD.ReProgMemM.Read.3,1 */
        if ((REPROGMEMM_TRUE == ReProgMemM_IsRangeAddressAllowed(ulReadAddr, ulLength, REPROGMEMM_TRUE))&&(pubDataPtr != NULL_PTR))
        {
            /* !LINKSTO SwD.ReProgMemM.Read.5,1 */
            /* Update the request Info */
            ReProgMemM_SetRequestInfo(ulReadAddr,ulLength, pubDataPtr, REPROGMEMM_REQUEST_READ);

            /* !LINKSTO SwD.ReProgMemM.Read.14,1 */
            /* Return Memory access pending */
            RetVal = REPROGMEMM_STATUS_PENDING;
        }
        else
        {
            /* !LINKSTO SwD.ReProgMemM.Read.6,1 */
            RetVal = E_NOT_OK;
        }
    }
    else
    {
        RetVal = E_NOT_OK;
    }
    SchM_Exit_ReProgMemM_SCHM_ReProgMemM_EXCLUSIVE_AREA_0();

    REPROGMEMM_PARAM_UNUSED(ubBankType);

    DBG_REPROGMEMM_READ_EXIT(RetVal);
    return (RetVal);
}

/** \brief ReProgMemM_Write function
 **
 ** full description can be found in ReProgMemM.h
 */
FUNC(Std_ReturnType, ReProgMemM_CODE) ReProgMemM_Write
(
    VAR  (uint32,            ReProgMemM_VAR) ulAddress,
    VAR  (uint32,            ReProgMemM_VAR) ulLength,
    P2VAR(uint8, AUTOMATIC,  ReProgMemM_APPL_DATA) pubDataPtr
)
{
    VAR (Std_ReturnType,       ReProgMemM_VAR) RetVal;
    VAR (REPROGMEMM_Address_t, ReProgMemM_VAR) ulCustomOffset;
    VAR (REPROGMEMM_Address_t, ReProgMemM_VAR) ulWriteAddr;

    DBG_REPROGMEMM_WRITE_ENTRY(ulAddress,ulLength,pubDataPtr);

    ulWriteAddr = 0x00000000U;
    RetVal      = E_OK;


#if (REPROGMEMM_CUSTOM_OFFSET_ENABLE == STD_ON)
    /* !LINKSTO SwD.ReProgMemM.Write.7,1 */
    ulCustomOffset = ReProgMemM_CustomGetOffset(ulAddress);
#else
    /* !LINKSTO SwD.ReProgMemM.Write.8,1 */
    ulCustomOffset = 0x00000000U;
#endif

    SchM_Enter_ReProgMemM_SCHM_ReProgMemM_EXCLUSIVE_AREA_0();
    /* Get the memory type of the job */
    ReProgMemM_UbMemoryType = ReProgMemM_GetMemoryTypeByAddress ( ulAddress, ulLength);

    /* Get the memory index of the job */
    ReProgMemM_UbMemoryIdx = ReProgMemM_GetMemoryIdxByAddress ( ulAddress, ulLength);
   if (ReProgMemM_UbMemoryIdx != REPROGMEMM_MEMORY_NB)
   {
        if (REPROGMEMM_MEM_TYPE_FLASH == ReProgMemM_UbMemoryType)
        {
#if (REPROGMEMM_DUALBANK_ENABLED == STD_ON)
            /* Set the aligned write address */
            if (REPROGMEMM_DUALBANK_A_BANK_ACTIVE == ReProgMemM_UbActiveBank)
            {
                /* !LINKSTO SwD.ReProgMemM.Write.1,2 */
                ReProgMemM_UlInactiveBankOffset = ReProgMemM_CustomGetInactiveBankAddrOffset(ulAddress);
                ulWriteAddr = (uint32)(ulAddress + ulCustomOffset + ReProgMemM_UlInactiveBankOffset + m_astReProgMemMMemoryCfg[ReProgMemM_UbMemoryIdx].ulAddressOffset);
            }
            else if (REPROGMEMM_DUALBANK_B_BANK_ACTIVE == ReProgMemM_UbActiveBank)
            {
                /* !LINKSTO SwD.ReProgMemM.Write.1,2 */
                ulWriteAddr = (uint32)(ulAddress + ulCustomOffset + m_astReProgMemMMemoryCfg[ReProgMemM_UbMemoryIdx].ulAddressOffset);
            }
            else
            {
                /* !LINKSTO SwD.ReProgMemM.Write.10,1 */
                RetVal = E_NOT_OK;
            }
#endif
#if ((REPROGMEMM_TOPO_FLASH_ENABLED == STD_ON) && (REPROGMEMM_DUALBANK_ENABLED == STD_OFF))
            /* !LINKSTO SwD.ReProgMemM.Write.4,2 */
            /* Set the aligned write address */
            ulWriteAddr = (uint32)(ulAddress + ulCustomOffset + m_astReProgMemMMemoryCfg[ReProgMemM_UbMemoryIdx].ulAddressOffset);
#endif
        }
        else if (REPROGMEMM_MEM_TYPE_FLASH_EXT == ReProgMemM_UbMemoryType)
        {
#if (REPROGMEMM_TOPO_FLASHEXT_ENABLED == STD_ON)
            /* !LINKSTO SwD.ReProgMemM.Write.2,1 */
            /* Set the aligned write address */
            ulWriteAddr = (uint32)(ulAddress + ulCustomOffset + m_astReProgMemMMemoryCfg[ReProgMemM_UbMemoryIdx].ulAddressOffset);
#endif
        }
        else
        {
            /* !LINKSTO SwD.ReProgMemM.Write.9,1 */
            /* Unsupported memory - can not happen */
        }
    }
    else
    {
        RetVal = E_NOT_OK;
    }

    if ((ReProgMemM_StRequest.ubJobStatus != REPROGMEMM_JOB_STATUS_MEMORY_NOT_INITIALIZED) && (E_NOT_OK != RetVal))
    /* Return the job status */
    {
        if (REPROGMEMM_TRUE == ReProgMemM_IsRangeAddressAllowed(ulWriteAddr, ulLength, REPROGMEMM_FALSE))
        {
            if (REPROGMEMM_TRUE == ReProgMemM_IsAddressAlignedOnPage(ulWriteAddr))
            {
                if (pubDataPtr != NULL_PTR)
                {
                    /* !LINKSTO SwD.ReProgMemM.Write.3,2 */
                    /* Update the request Info */
                    ReProgMemM_SetRequestInfo(ulWriteAddr, ulLength, pubDataPtr, REPROGMEMM_REQUEST_WRITE);

                    /* Return Memory access pending */
                    RetVal = REPROGMEMM_STATUS_PENDING;

                }
                else
                {
                    /* !LINKSTO SwD.ReProgMemM.Write.6,2 */
                    RetVal = E_NOT_OK;
                }
            }
            else
            {
                /* !LINKSTO SwD.ReProgMemM.Write.6,2 */
                RetVal = E_NOT_OK;
            }
        }
        else
        {
            /* !LINKSTO SwD.ReProgMemM.Write.6,2 */
            RetVal = E_NOT_OK;
        }
    }
    else
    {
        /* !LINKSTO SwD.ReProgMemM.Write.6,2 */
        RetVal = E_NOT_OK;
    }
    SchM_Exit_ReProgMemM_SCHM_ReProgMemM_EXCLUSIVE_AREA_0();

    DBG_REPROGMEMM_WRITE_EXIT(RetVal);
    return (RetVal);
}

#if (REPROGMEMM_VERSION_INFO_API == STD_ON)
/** \brief ReProgMemM_GetVersionInfo function
 **
 ** full description can be found in ReProgMemM.h
 */
FUNC(void, ReProgMemM_CODE) ReProgMemM_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, ReProgMemM_APPL_DATA) versioninfo
)
{
    DBG_REPROGMEMM_GETVERSIONINFO_ENTRY(versioninfo);

    if (versioninfo == NULL_PTR)
    {
#if (REPROGMEMM_DEV_ERROR_DETECT  == STD_ON)
        (void)REPROGMEMM_DET_REPORT_ERROR  (REPROGMEMM_INSTANCE_ID,
                                            REPROGMEMM_SERVID_GETVERSIONINFO,
                                            REPROGMEMM_NULL_PTR_ID
                                            );
#endif
    }
    else
    {
        /* !LINKSTO SwD.ReProgMemM.GetVersionInfo.1,1 */
        versioninfo->vendorID = REPROGMEMM_VENDOR_ID;
        versioninfo->moduleID = REPROGMEMM_MODULE_ID;
        versioninfo->sw_major_version = REPROGMEMM_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = REPROGMEMM_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = REPROGMEMM_SW_PATCH_VERSION;
    }
    DBG_REPROGMEMM_GETVERSIONINFO_EXIT();
}
#endif


#define REPROGMEMM_STOP_SEC_CODE
#include <ReProgMemM_MemMap.h>

/*==[Definition of functions with internal linkage]===========================*/
#define REPROGMEMM_START_SEC_CODE
#include <ReProgMemM_MemMap.h>

static FUNC(REPROGMEMM_JobStatus_t, ReProgMemM_CODE) ReProgMemM_GetDriverJobStatus(void)
{
    REPROGMEMM_JobStatus_t RetVal;

#if (REPROGMEMM_USE_MEMACC_ENABLE == STD_ON)
    /* !LINKSTO SwD.ReProgMemM.GetDriverJobStatus.1,1 */
    RetVal = ReProgMemM_MemAcc_JobStatus();
#else
    /* !LINKSTO SwD.ReProgMemM.GetDriverJobStatus.3,1 */
    RetVal = REPROGMEMM_JOB_STATUS_NO_ERROR;

    SchM_Enter_ReProgMemM_SCHM_ReProgMemM_EXCLUSIVE_AREA_0();

    if (REPROGMEMM_MEM_TYPE_FLASH == ReProgMemM_UbMemoryType)
    {
#if (REPROGMEMM_TOPO_FLASH_ENABLED == STD_ON)
        /* !LINKSTO SwD.ReProgMemM.GetDriverJobStatus.2,1 */
        /* !LINKSTO SwD.ReProgMemM.FlashGetJobStatus.If,1 */
        RetVal = ReProgMemM_FlsDriver_JobStatus();
#endif
    }
    else if (REPROGMEMM_MEM_TYPE_FLASH_EXT == ReProgMemM_UbMemoryType)
    {
#if (REPROGMEMM_TOPO_FLASHEXT_ENABLED == STD_ON)
        /* !LINKSTO SwD.ReProgMemM.GetDriverJobStatus.4,1 */
        /* Get the external Flash driver status */
        RetVal = ReProgMemM_FlsExtDriver_JobStatus();
#endif
    }
    else
    {
        /* Unsupported memory */
    }
#endif

    SchM_Exit_ReProgMemM_SCHM_ReProgMemM_EXCLUSIVE_AREA_0();

    return (RetVal);
}

#if (REPROGMEMM_COPY_ROM_TO_RAM_ENABLE == STD_ON)
static FUNC(void, ReProgMemM_CODE) ReProgMemM_CopyFlashRoutinesToRam
(
    P2VAR(uint8,  AUTOMATIC,  ReProgMemM_APPL_DATA) pRoutinesDataSource,
    P2VAR(uint8,  AUTOMATIC,  ReProgMemM_APPL_DATA) pRoutinesDataDest,
    VAR  (uint32,             ReProgMemM_VAR) ulRoutinesDataLength
)
{
#if (REPROGMEMM_COPY_FLASH_ROUTINES == STD_ON)
    /* Copy Flash routines into RAM */
    TS_MemCpy( (uint8*) (pRoutinesDataDest), (uint8*) (pRoutinesDataSource), ulRoutinesDataLength);
#endif
}
#endif

static FUNC(void, ReProgMemM_CODE) ReProgMemM_SetRequestInfo
(
    VAR  (uint32,                                 ReProgMemM_VAR) ulAddr,
    VAR  (uint32,                                 ReProgMemM_VAR) ulLen,
    P2VAR(uint8,                      AUTOMATIC,  ReProgMemM_APPL_DATA) pubDataPtr,
    VAR  (REPROGMEMM_RequestSelect_t,             ReProgMemM_VAR) ubRequestSelect
)
{
    SchM_Enter_ReProgMemM_SCHM_ReProgMemM_EXCLUSIVE_AREA_0();

    /* !LINKSTO SwD.ReProgMemM.SetRequestInfo.1,2 */
    /* Set Flash_MainFunction common information */
    ReProgMemM_StRequest.ubRequestSelect  = ubRequestSelect;
    ReProgMemM_StRequest.ubJobStatus      = REPROGMEMM_JOB_STATUS_BUSY;
    ReProgMemM_StRequest.ulStartAddress   = ulAddr;
    ReProgMemM_StRequest.ulLength         = ulLen;

    ReProgMemM_StRequest.pubDataPtr       = pubDataPtr;
    ReProgMemM_StRequest.ulEndAddress     = ulAddr + ulLen - (uint32) 1U;
    ReProgMemM_StRequest.ulAddressToTreat = ulAddr;
    ReProgMemM_StRequest.ulAddressTreated = (uint32) 0U;

    /* Initialize the pointer for the data to write */
    ReProgMemM_UbDataToWritePtr = pubDataPtr;

    if (REPROGMEMM_REQUEST_WRITE == ubRequestSelect)
    {
        /* Initialize the number of pages to write */
        if ((ulLen % (uint32) REPROGMEMM_FLASH_PAGE_SIZE) == (uint32) 0x00U)
        {
            /* !LINKSTO SwD.ReProgMemM.SetRequestInfo.2,1 */
            ReProgMemM_StRequest.ulNbOfPagesToWrite = ulLen / (uint32) REPROGMEMM_FLASH_PAGE_SIZE ;
        }
        else
        {
            /* !LINKSTO SwD.ReProgMemM.SetRequestInfo.3,1 */
            ReProgMemM_StRequest.ulNbOfPagesToWrite = (ulLen / (uint32) REPROGMEMM_FLASH_PAGE_SIZE) +(uint32) 1 ;
        }
    }
    else
    {
        /* !LINKSTO SwD.ReProgMemM.SetRequestInfo.4,1 */
        /* Nothing to do */
    }
    SchM_Exit_ReProgMemM_SCHM_ReProgMemM_EXCLUSIVE_AREA_0();
}

static FUNC(REPROGMEMM_MemoryType_t, ReProgMemM_CODE) ReProgMemM_GetMemoryTypeByAddress
(
    VAR  (uint32, ReProgMemM_VAR)  ulAddr,
    VAR  (uint32, ReProgMemM_VAR)  ulLen
)
{
    VAR (REPROGMEMM_MemoryType_t, ReProgMemM_VAR) ubMemoryType;
    VAR (REPROGMEMM_Boolean_t,    ReProgMemM_VAR) ubMemoryTypeFound;
    VAR (uint8,                   ReProgMemM_VAR) idx;

    ubMemoryType = REPROGMEMM_MEM_TYPE_INIT;
    ubMemoryTypeFound = REPROGMEMM_FALSE;

    for (idx = 0U; (idx < REPROGMEMM_MEMORY_NB) && (REPROGMEMM_FALSE == ubMemoryTypeFound); idx++)
    {
        if (ulAddr  >= m_astReProgMemMMemoryCfg[idx].ulMemoryStartAddress)
        {
            if ((ulAddr + ulLen) <= (m_astReProgMemMMemoryCfg[idx].ulMemoryStartAddress + m_astReProgMemMMemoryCfg[idx].ulMemoryLength))
            {
                ubMemoryType = m_astReProgMemMMemoryCfg[idx].ubMemoryType;
                ubMemoryTypeFound = REPROGMEMM_TRUE;
            }
        }

    }

    return ubMemoryType;
}

static FUNC(REPROGMEMM_MemoryIdx_t, ReProgMemM_CODE) ReProgMemM_GetMemoryIdxByAddress
(
    VAR  (uint32, ReProgMemM_VAR)  ulAddr,
    VAR  (uint32, ReProgMemM_VAR)  ulLen
)
{
    VAR (REPROGMEMM_MemoryIdx_t, ReProgMemM_VAR) ubMemoryIdx;
    VAR (REPROGMEMM_Boolean_t,   ReProgMemM_VAR) ubMemoryIdFound;
    VAR (uint8,                  ReProgMemM_VAR) idx;

    ubMemoryIdx = REPROGMEMM_MEMORY_NB;
    ubMemoryIdFound = REPROGMEMM_FALSE;

    for (idx = 0U; (idx < REPROGMEMM_MEMORY_NB) && (REPROGMEMM_FALSE == ubMemoryIdFound); idx++)
    {
        if (ulAddr >= m_astReProgMemMMemoryCfg[idx].ulMemoryStartAddress)
        {
            if ((ulAddr + ulLen) <= (m_astReProgMemMMemoryCfg[idx].ulMemoryStartAddress + m_astReProgMemMMemoryCfg[idx].ulMemoryLength))
            {
                ubMemoryIdx = idx;
                ubMemoryIdFound = REPROGMEMM_TRUE;
            }
        }
    }

    return ubMemoryIdx;
}

static FUNC(REPROGMEMM_Boolean_t, ReProgMemM_CODE) ReProgMemM_IsRangeAddressAllowed
(
    VAR  (uint32, ReProgMemM_VAR)  ulAddr,
    VAR  (uint32, ReProgMemM_VAR)  ulLen,
    VAR  (REPROGMEMM_Boolean_t, ReProgMemM_VAR)  operationFlag
)
{
    REPROGMEMM_Boolean_t RangeAddressAllowed;
    REPROGMEMM_Boolean_t StartAddrFound;
    REPROGMEMM_Boolean_t EndAddrFound;
    REPROGMEMM_Boolean_t OpFlag;

    VAR (uint32, ReProgMemM_VAR) ulSectorElsTableElementIdx;
    VAR (uint32, ReProgMemM_VAR) ulFlashSectorTable_StartAddress;
    VAR (uint32, ReProgMemM_VAR) ulFlashSectorTable_EndAddress;
    VAR (uint32, ReProgMemM_VAR) ulRequestedEndAddress;
    VAR (uint32, ReProgMemM_VAR) ulRequestedStartAddress;
    VAR (uint32, ReProgMemM_VAR) ulElementIdxStartAddr;
    VAR (uint32, ReProgMemM_VAR) ulElementIdxEndAddr;


    RangeAddressAllowed = REPROGMEMM_FALSE;
    StartAddrFound = REPROGMEMM_FALSE;
    EndAddrFound = REPROGMEMM_FALSE;
    ulElementIdxStartAddr = 0U;
    ulElementIdxEndAddr = 0U;
    OpFlag = operationFlag;

    /* Get the requested start and end addresses */
    if (  (((uint32)REPROGMEMM_U32_MAX_VALUE - ulAddr) > ulLen)
       && ((ulAddr + ulLen) != (uint32)0U))
    {
      ulRequestedEndAddress = ulAddr + (uint32)(ulLen) - (uint32)(1U);
      ulRequestedStartAddress = ulAddr;

      TS_MemCpy(SectorsTable, m_astReProgMemMMemorySecProtCfg, sizeof(SectorsTable));

      if(IsFlashSecTableOrdered == FALSE)
      {
          /* !LINKSTO SwD.ReProgMemM.IsRangeAddressAllowed.4,1 */
          ReProgMemM_OrderFlashSecTableByAddr(SectorsTable);
      }

      for (ulSectorElsTableElementIdx = (uint32)(0U); (ulSectorElsTableElementIdx < REPROGMEMM_FLASH_SECTORS_DESCRIPT_NB); ulSectorElsTableElementIdx++)
      {
          ulFlashSectorTable_StartAddress = SectorsTable[ulSectorElsTableElementIdx].ulStartAddress;

          ulFlashSectorTable_EndAddress = SectorsTable[ulSectorElsTableElementIdx].ulStartAddress +
                                                  SectorsTable[ulSectorElsTableElementIdx].ulLength - (uint32)(1U);


          if ((ulRequestedStartAddress >= ulFlashSectorTable_StartAddress ) && (ulRequestedStartAddress <= ulFlashSectorTable_EndAddress))
          {
              ulElementIdxStartAddr = ulSectorElsTableElementIdx;
              StartAddrFound = REPROGMEMM_TRUE;
          }

          if ((ulRequestedEndAddress >= ulFlashSectorTable_StartAddress ) && (ulRequestedEndAddress <= ulFlashSectorTable_EndAddress))
          {
              ulElementIdxEndAddr = ulSectorElsTableElementIdx;
              EndAddrFound = REPROGMEMM_TRUE;
          }
      }

      if((StartAddrFound == REPROGMEMM_TRUE) && (EndAddrFound == REPROGMEMM_TRUE))
      {
          /* Deviation TASKING-2 */
          if((ulElementIdxStartAddr == ulElementIdxEndAddr) && ((SectorsTable[ulElementIdxStartAddr].ubSectorProtection == REPROGMEMM_SECTOR_NOT_PROTECTED) || (OpFlag == REPROGMEMM_TRUE)))
          {
              /* !LINKSTO SwD.ReProgMemM.IsRangeAddressAllowed.2,1 */
              /* Address range is allowed (same sector table) */
              RangeAddressAllowed = REPROGMEMM_TRUE;
          }
          else
          {
              /* Requested range coverd by multiple sector */
              /* Deviation TASKING-3 */
              for(ulSectorElsTableElementIdx = ulElementIdxStartAddr; (ulSectorElsTableElementIdx < ulElementIdxEndAddr) && (StartAddrFound == REPROGMEMM_TRUE); ulSectorElsTableElementIdx++)
              {
                  ulFlashSectorTable_EndAddress = SectorsTable[ulSectorElsTableElementIdx].ulStartAddress +
                                                                  SectorsTable[ulSectorElsTableElementIdx].ulLength;

                  /* Check if the addresses of two consecutive tables are contiguous and programmable*/
                  if((SectorsTable[ulSectorElsTableElementIdx+(uint32)1].ulStartAddress != ulFlashSectorTable_EndAddress) ||
                     ( ((SectorsTable[ulSectorElsTableElementIdx].ubSectorProtection == REPROGMEMM_SECTOR_WRITE_PROTECTED) ||
                       (SectorsTable[ulSectorElsTableElementIdx+(uint32)1].ubSectorProtection == REPROGMEMM_SECTOR_WRITE_PROTECTED)) &&
                       (OpFlag == REPROGMEMM_FALSE))
                     )
                  {
                      StartAddrFound = REPROGMEMM_FALSE;
                  }
              }

              /* Deviation TASKING-2 */
              if(StartAddrFound == REPROGMEMM_TRUE)
              {
                  /* !LINKSTO SwD.ReProgMemM.IsRangeAddressAllowed.1,1 */
                  RangeAddressAllowed = REPROGMEMM_TRUE;
              }
              else
              {
                  /* !LINKSTO SwD.ReProgMemM.IsRangeAddressAllowed.3,1 */
                  /* Nothing to do */
              }
          }
      }
      else
      {
          /* !LINKSTO SwD.ReProgMemM.IsRangeAddressAllowed.3,1 */
          /* Nothing to do */
      }
    }
    else
    {
        /* Adress + Length is not in the range of a uint32. It is not allowed. */
        /* Nothing to do */
    }

    return RangeAddressAllowed;
}

static FUNC(REPROGMEMM_Boolean_t, ReProgMemM_CODE) ReProgMemM_IsAddressAlignedOnSector (VAR (uint32, ReProgMemM_VAR) ulAddr)
{
    VAR (REPROGMEMM_Boolean_t, ReProgMemM_VAR) ubBoolean;
    VAR (uint32,               ReProgMemM_VAR) ulSectorElsTableElementIdx;
    VAR (uint32,               ReProgMemM_VAR) ulFlashSectorTable_StartAddress;
    VAR (uint32,               ReProgMemM_VAR) ulFlashSectorTable_SectorSize;
    VAR (uint32,               ReProgMemM_VAR) ulFlashSectorTable_Length;
    VAR (uint32,               ReProgMemM_VAR) ulRequestedStartAddress;

    ubBoolean = REPROGMEMM_FALSE;
    ulRequestedStartAddress = ulAddr;

    /* For each FlashSectorsTable element */
    for (ulSectorElsTableElementIdx = (uint32)(0U); (ulSectorElsTableElementIdx < REPROGMEMM_FLASH_SECTORS_DESCRIPT_NB) && (REPROGMEMM_FALSE == ubBoolean); ulSectorElsTableElementIdx++)
    {
        ulFlashSectorTable_StartAddress = m_astReProgMemMMemorySecProtCfg[ulSectorElsTableElementIdx].ulStartAddress;

        ulFlashSectorTable_SectorSize = m_astReProgMemMMemorySecProtCfg[ulSectorElsTableElementIdx].ulSectorSize;

        ulFlashSectorTable_Length = m_astReProgMemMMemorySecProtCfg[ulSectorElsTableElementIdx].ulLength;

        if (  (ulRequestedStartAddress >= ulFlashSectorTable_StartAddress)
           && (ulRequestedStartAddress < (ulFlashSectorTable_StartAddress + ulFlashSectorTable_Length))
           && (((ulRequestedStartAddress - ulFlashSectorTable_StartAddress ) % ulFlashSectorTable_SectorSize) == (uint32)(0x00)))
        {
            /* Address range is aligned on sector */
            ubBoolean = REPROGMEMM_TRUE;
        }
    }

    return ubBoolean;
}

static FUNC(uint32, ReProgMemM_CODE) ReProgMemM_GetSectorByAddress
(
        VAR  (uint32, ReProgMemM_VAR)  ulAddr,
        VAR  (uint32, ReProgMemM_VAR)  ulLen,
        VAR  (uint32, ReProgMemM_VAR) ulStartAddrToBeTreat,
        P2VAR (uint32,  AUTOMATIC, ReProgMemM_APPL_DATA) ulEndAddrTobeTreat
)
{
    VAR (uint32,               ReProgMemM_VAR) ulSectorElsTableElementIdx;
    VAR (uint32,               ReProgMemM_VAR) ulFlashSectorTable_StartAddress;
    VAR (uint32,               ReProgMemM_VAR) ulFlashSectorTable_EndAddress;
    VAR (uint32,               ReProgMemM_VAR) ulRequestedStartAddress;
    VAR (uint32,               ReProgMemM_VAR) ulRequestedEndAddress;
    VAR (uint32,               ReProgMemM_VAR) ulRequestedSectorSize;
    VAR (uint32,               ReProgMemM_VAR) ulElementIdxStartAddr;
    VAR (uint32,               ReProgMemM_VAR) ulElementIdxEndAddr;

    ulElementIdxStartAddr = 0U;
    ulElementIdxEndAddr   = 0U;

    /* Get the requested start and end addresses */
    ulRequestedEndAddress = ulAddr + (uint32)(ulLen) - (uint32)(1U);
    ulRequestedStartAddress = ulStartAddrToBeTreat;

    TS_MemCpy(SectorsTable, m_astReProgMemMMemorySecProtCfg, sizeof(SectorsTable));

    if(IsFlashSecTableOrdered == FALSE)
    {
        /* !LINKSTO SwD.ReProgMemM.GetSectorByAddress.3,1 */
        ReProgMemM_OrderFlashSecTableByAddr(SectorsTable);
    }

    for (ulSectorElsTableElementIdx = (uint32)(0U); (ulSectorElsTableElementIdx < REPROGMEMM_FLASH_SECTORS_DESCRIPT_NB); ulSectorElsTableElementIdx++)
    {
        ulFlashSectorTable_StartAddress = SectorsTable[ulSectorElsTableElementIdx].ulStartAddress;

        ulFlashSectorTable_EndAddress = SectorsTable[ulSectorElsTableElementIdx].ulStartAddress +
                                                SectorsTable[ulSectorElsTableElementIdx].ulLength - (uint32)(1U);


        if ((ulRequestedStartAddress >= ulFlashSectorTable_StartAddress ) && (ulRequestedStartAddress <= ulFlashSectorTable_EndAddress))
        {
            ulElementIdxStartAddr = ulSectorElsTableElementIdx;
        }

        if ((ulRequestedEndAddress >= ulFlashSectorTable_StartAddress ) && (ulRequestedEndAddress <= ulFlashSectorTable_EndAddress))
        {
            ulElementIdxEndAddr = ulSectorElsTableElementIdx;
        }
    }

    /* Deviation TASKING-2 */
    if(ulElementIdxStartAddr == ulElementIdxEndAddr)
    {
        /* !LINKSTO SwD.ReProgMemM.GetSectorByAddress.1,1 */
        ulRequestedSectorSize = SectorsTable[ulElementIdxStartAddr].ulSectorSize;
        *ulEndAddrTobeTreat = ulRequestedEndAddress;
    }
    else
    {
        /* !LINKSTO SwD.ReProgMemM.GetSectorByAddress.2,1 */
        ulRequestedSectorSize = SectorsTable[ulElementIdxStartAddr].ulSectorSize;
        *ulEndAddrTobeTreat = SectorsTable[ulElementIdxStartAddr].ulStartAddress +
                SectorsTable[ulElementIdxStartAddr].ulLength - (uint32)(1U);
    }

    return ulRequestedSectorSize;
}

static FUNC(REPROGMEMM_Boolean_t, ReProgMemM_CODE) ReProgMemM_IsAddressAlignedOnPage
(
    VAR  (uint32, ReProgMemM_VAR)  ulAddr
)
{
    VAR (REPROGMEMM_Boolean_t, ReProgMemM_VAR) ubBoolean;
    VAR (uint32,               ReProgMemM_VAR) ulRequestedStartAddress;

    ubBoolean = REPROGMEMM_FALSE;
    ulRequestedStartAddress = ulAddr;

    if ((ulRequestedStartAddress % ((uint32) REPROGMEMM_FLASH_PAGE_SIZE)) == (uint32)(0x00))
    {
        /* Address range is aligned on page */
        ubBoolean = REPROGMEMM_TRUE;
    }

    return ubBoolean;
}


static FUNC(void, ReProgMemM_CODE) ReProgMemM_EraseMngt(void)
{
    VAR (Std_ReturnType, ReProgMemM_VAR) ubMemoryAccessStatus;
#if (REPROGMEMM_TOPO_FLASH_ENABLED == STD_ON)
    VAR (uint32, ReProgMemM_VAR) ulLogicalAddress;
#endif
    VAR (uint32, ReProgMemM_VAR) ulRequestedEndAddress;
    VAR (uint32, ReProgMemM_VAR) ulRequestedSectorSize;
    VAR (uint32, ReProgMemM_VAR) ulNumSectorsToErase;
    VAR (uint32, ReProgMemM_VAR) ulEraseEndAddress;

#if (REPROGMEMM_TOPO_FLASH_ENABLED == STD_ON)
    VAR (uint32, ReProgMemM_VAR) ulRemainingSectorsToErase;
    VAR (uint32, ReProgMemM_VAR) ulLogicalEndAddress;

    ulLogicalAddress = 0U;
    ulLogicalEndAddress = 0U;
#endif

    ubMemoryAccessStatus = E_NOT_OK;
    ulNumSectorsToErase = 0U;

    SchM_Enter_ReProgMemM_SCHM_ReProgMemM_EXCLUSIVE_AREA_0();


    /* Get the Requested end address */
    ulRequestedEndAddress = ReProgMemM_StRequest.ulStartAddress + ReProgMemM_StRequest.ulLength - (uint32)(1U);
    ulEraseEndAddress = 0U;

    /* Get the memory type of the job */
    ReProgMemM_UbMemoryType = ReProgMemM_GetMemoryTypeByAddress ( ReProgMemM_StRequest.ulStartAddress, ReProgMemM_StRequest.ulLength);

    /* Get the memory driver status */
    ReProgMemM_StRequest.ubJobStatus = ReProgMemM_GetDriverJobStatus();

    /* Get the sector size */
    ulRequestedSectorSize = ReProgMemM_GetSectorByAddress (ReProgMemM_StRequest.ulStartAddress, ReProgMemM_StRequest.ulLength, ReProgMemM_StRequest.ulAddressToTreat, &ulEraseEndAddress);

    if (ReProgMemM_StRequest.ubJobStatus == REPROGMEMM_JOB_STATUS_NO_ERROR)
    {

        if (REPROGMEMM_MEM_TYPE_FLASH == ReProgMemM_UbMemoryType)
        {
#if (REPROGMEMM_TOPO_FLASH_ENABLED == STD_ON)
            /* Get the logical address to treat */
            ReProgMemM_CustomGetPhysicalToLogicalAddress(ReProgMemM_StRequest.ulAddressToTreat, &ulLogicalAddress);

            /* Get the logical end address to treat */
            ReProgMemM_CustomGetPhysicalToLogicalAddress(ulEraseEndAddress, &ulLogicalEndAddress);

            /* Robustness on sector size */
            if (ulRequestedSectorSize > 0U)
            {
                /* Handle the case where the remaining memory range to erase is lower than a flash sector size. See ASCREPROGMEMM-204 */
                if ((ulLogicalEndAddress - ulLogicalAddress +1U) >= ulRequestedSectorSize)
                {
                    /* Compute remaining number of sectors to erase */
                    ulRemainingSectorsToErase = (uint32)( (ulLogicalEndAddress - ulLogicalAddress +1U) / ulRequestedSectorSize );
                }
                else
                {
                    ulRemainingSectorsToErase = 1U;
                }
            }
            else
            {
               ulRemainingSectorsToErase = 0U;
            }

            /* Check for overflow */
            if (ulRemainingSectorsToErase > REPROGMEMM_SIZE_PER_TURN)
            {
               ulNumSectorsToErase = REPROGMEMM_SIZE_PER_TURN;
            }
            else
            {
               ulNumSectorsToErase = ulRemainingSectorsToErase;
            }

            /* Get the Flash driver Erase status */
#if(REPROGMEMM_USE_MEMACC_ENABLE == STD_ON)
            /* !LINKSTO SwD.ReProgMemM.EraseMngt.8,2 */
            ubMemoryAccessStatus = MemAcc_Erase(MemAcc_FOTA_AreaId_AddressAreaId, (MemAcc_AddressType)ulLogicalAddress, (MemAcc_LengthType)(ulRequestedSectorSize*ulNumSectorsToErase));
#else
            /* !LINKSTO SwD.ReProgMemM.EraseMngt.1,3 */
            /* !LINKSTO SwD.ReProgMemM.FlashErase.If,1 */
            ubMemoryAccessStatus = ReProgMemM_FlsDriver_Erase(ulLogicalAddress,(uint32)(ulNumSectorsToErase));
#endif
#endif
        }
        else if (REPROGMEMM_MEM_TYPE_FLASH_EXT == ReProgMemM_UbMemoryType)
        {
#if (REPROGMEMM_TOPO_FLASHEXT_ENABLED == STD_ON)
            /* !LINKSTO SwD.ReProgMemM.EraseMngt.2,3 */
            /*Get the external Flash driver Erase status */
            ubMemoryAccessStatus = ReProgMemM_FlsExtDriver_Erase(ReProgMemM_StRequest.ulAddressToTreat,(uint32)(REPROGMEMM_SIZE_PER_TURN));
#endif
        }
        else
        {
            /* !LINKSTO SwD.ReProgMemM.EraseMngt.7,1 */
            /* Unsupported memory -- can not happen */
        }

        if (E_OK== ubMemoryAccessStatus)
        {
            /* !LINKSTO SwD.ReProgMemM.EraseMngt.3,1 */
            /* Update addresses treated and to treat */
            ReProgMemM_StRequest.ulAddressTreated = ReProgMemM_StRequest.ulAddressToTreat;
            ReProgMemM_StRequest.ulAddressToTreat += (ulNumSectorsToErase) * ulRequestedSectorSize;

            if (ulRequestedEndAddress <= ReProgMemM_StRequest.ulAddressToTreat)
            {
                /* !LINKSTO SwD.ReProgMemM.EraseMngt.6,1 */
                /* End address has been erased */
                ReProgMemM_StRequest.ubJobStatus = REPROGMEMM_JOB_STATUS_NO_ERROR;
                ReProgMemM_StRequest.ubRequestSelect = REPROGMEMM_REQUEST_NO_FLASH_RQT;
            }
            else
            {
                /* !LINKSTO SwD.ReProgMemM.EraseMngt.4,1 */
                /* End address has not been erased yet */
                ReProgMemM_StRequest.ubJobStatus = REPROGMEMM_JOB_STATUS_BUSY;
            }
        }
        else
        {
            ReProgMemM_StRequest.ubJobStatus = REPROGMEMM_JOB_STATUS_ERROR;
            ReProgMemM_StRequest.ubRequestSelect = REPROGMEMM_REQUEST_NO_FLASH_RQT;
        }
    }
    else
    {
        /* !LINKSTO SwD.ReProgMemM.EraseMngt.5,1 */
        /* Nothing to do until previous job is done and driver is available */
    }
    SchM_Exit_ReProgMemM_SCHM_ReProgMemM_EXCLUSIVE_AREA_0();
}

static FUNC(void, ReProgMemM_CODE) ReProgMemM_WriteMngt(void)
{
    VAR (Std_ReturnType, ReProgMemM_VAR) ubMemoryAccessStatus;
#if (REPROGMEMM_TOPO_FLASH_ENABLED == STD_ON)
    VAR (uint32,         ReProgMemM_VAR) ulLogicalAddress;
#endif
    VAR   (uint32,            ReProgMemM_VAR) ulNbBytesOnLastPage;
    P2VAR (uint8,  AUTOMATIC, ReProgMemM_APPL_DATA) pubRemaingDataToWrite;
    VAR   (uint32,            ReProgMemM_VAR) ulIdx;

    SchM_Enter_ReProgMemM_SCHM_ReProgMemM_EXCLUSIVE_AREA_0();

    /* Get the memory type of the job */
    ReProgMemM_UbMemoryType = ReProgMemM_GetMemoryTypeByAddress ( ReProgMemM_StRequest.ulStartAddress, ReProgMemM_StRequest.ulLength);

    /* Get the memory index of the job */
    ReProgMemM_UbMemoryIdx = ReProgMemM_GetMemoryIdxByAddress ( ReProgMemM_StRequest.ulStartAddress, ReProgMemM_StRequest.ulLength);

    ubMemoryAccessStatus = E_NOT_OK;

    /* Get the memory driver status */
    ReProgMemM_StRequest.ubJobStatus = ReProgMemM_GetDriverJobStatus();

    if (ReProgMemM_StRequest.ubJobStatus == REPROGMEMM_JOB_STATUS_NO_ERROR)
    {
       if (ReProgMemM_UbMemoryIdx != REPROGMEMM_MEMORY_NB)
       {
            if (REPROGMEMM_MEM_TYPE_FLASH == ReProgMemM_UbMemoryType)
            {
#if (REPROGMEMM_TOPO_FLASH_ENABLED == STD_ON)
                /* Get the logical address to treat */
                ReProgMemM_CustomGetPhysicalToLogicalAddress(ReProgMemM_StRequest.ulAddressToTreat, &ulLogicalAddress);

                /* Get the Flash driver write status */

#if(REPROGMEMM_USE_MEMACC_ENABLE == STD_ON)
                /* !LINKSTO SwD.ReProgMemM.WriteMngt.8,1 */
                ubMemoryAccessStatus = MemAcc_Write(MemAcc_FOTA_AreaId_AddressAreaId, (MemAcc_AddressType)ulLogicalAddress, (const MemAcc_DataType*)ReProgMemM_UbDataToWritePtr, (MemAcc_LengthType)m_astReProgMemMMemoryCfg[ReProgMemM_UbMemoryIdx].ulMinValueToWrite);
#else
                /* !LINKSTO SwD.ReProgMemM.WriteMngt.1,2 */
                ubMemoryAccessStatus = ReProgMemM_FlsDriver_Write(ulLogicalAddress, m_astReProgMemMMemoryCfg[ReProgMemM_UbMemoryIdx].ulMinValueToWrite, ReProgMemM_UbDataToWritePtr);

#endif
#endif
            }
            else if (REPROGMEMM_MEM_TYPE_FLASH_EXT == ReProgMemM_UbMemoryType)
            {
#if (REPROGMEMM_TOPO_FLASHEXT_ENABLED == STD_ON)
                /* Get the external Flash driver write status */
    /*#if(REPROGMEMM_USE_MEMACC_ENABLE == STD_ON)
                ubMemoryAccessStatus = MemAcc_Write(MemAcc_FOTA_AreaId_AddressAreaId, (MemAcc_AddressType)ulLogicalAddress, (const MemAcc_DataType*)ReProgMemM_UbDataToWritePtr, (MemAcc_LengthType)m_astReProgMemMMemoryCfg[ReProgMemM_UbMemoryIdx].ulMinValueToWrite);
    #else*/
                /* !LINKSTO SwD.ReProgMemM.WriteMngt.2,3 */
                ubMemoryAccessStatus = ReProgMemM_FlsExtDriver_Write(ReProgMemM_StRequest.ulAddressToTreat, m_astReProgMemMMemoryCfg[ReProgMemM_UbMemoryIdx].ulMinValueToWrite , ReProgMemM_UbDataToWritePtr);
    /*#endif*/
#endif
            }
            else
            {
                /* !LINKSTO SwD.ReProgMemM.WriteMngt.7,1 */
                /* Unsupported memory - can not happen */
            }
       }
        if (E_OK == ubMemoryAccessStatus)
        {
            /* !LINKSTO SwD.ReProgMemM.WriteMngt.3,1 */
            /* Update addresses treated and to treat */
            ReProgMemM_StRequest.ulAddressTreated = ReProgMemM_StRequest.ulAddressToTreat;
            ReProgMemM_StRequest.ulAddressToTreat += m_astReProgMemMMemoryCfg[ReProgMemM_UbMemoryIdx].ulMinValueToWrite;/*REPROGMEMM_FLASH_PAGE_SIZE;*/

            for (ulIdx = 0; ulIdx < m_astReProgMemMMemoryCfg[ReProgMemM_UbMemoryIdx].ulMinValueToWrite; ulIdx++)
            {
                ReProgMemM_StRequest.pubDataPtr++;
                ReProgMemM_UbDataToWritePtr++;
            }

            /* CHECK: NOPARSE */
            /* Defensive code: ulNbOfPagesToWrite value should never be 0 here.*/
            if (ReProgMemM_StRequest.ulNbOfPagesToWrite != (uint32)(0x0U))
            /* CHECK: PARSE */
            {
              /* Decrease the number of pages to write */
              ReProgMemM_StRequest.ulNbOfPagesToWrite--;
            }

            /* Check if there is remaining pages to write */
            if (ReProgMemM_StRequest.ulNbOfPagesToWrite != (uint32)(0x0U))
            {
                /* !LINKSTO SwD.ReProgMemM.WriteMngt.4,1 */
                /* Set the status as busy */
                ReProgMemM_StRequest.ubJobStatus = REPROGMEMM_JOB_STATUS_BUSY;

                if (ReProgMemM_StRequest.ulNbOfPagesToWrite == (uint32)(0x1U))
                {
                    /* Compute the number of useful bytes which will be write on the last page */
                    ulNbBytesOnLastPage = ReProgMemM_StRequest.ulLength % (uint32) REPROGMEMM_FLASH_PAGE_SIZE;

                    if (  (ulNbBytesOnLastPage != (uint32) 0x00U)
                       && (NULL_PTR != ReProgMemM_StRequest.pubDataPtr))
                    {
                        /* Retrieve the remaining data to write */
                        pubRemaingDataToWrite = ReProgMemM_StRequest.pubDataPtr;

                            /* Add the padding value in order to have a complete page */
                            for (ulIdx = ulNbBytesOnLastPage; ulIdx < REPROGMEMM_FLASH_PAGE_SIZE ; ulIdx++)
                            {
                                pubRemaingDataToWrite[ulIdx] = (uint8) REPROGMEMM_FLASH_PAGE_PADDING_VALUE;
                            }

                        /* Update the data to write */
                        ReProgMemM_UbDataToWritePtr = pubRemaingDataToWrite;
                    }
                }
            }
            /* All pages has been written, end of writing */
            else
            {
                /* !LINKSTO SwD.ReProgMemM.WriteMngt.5,1 */
                /* Set the status as no error */
                ReProgMemM_StRequest.ubJobStatus = REPROGMEMM_JOB_STATUS_NO_ERROR;
                ReProgMemM_StRequest.ubRequestSelect = REPROGMEMM_REQUEST_NO_FLASH_RQT;
            }

        }
        else
        {
            /* !LINKSTO SwD.ReProgMemM.WriteMngt.6,1 */
            ReProgMemM_StRequest.ubJobStatus = REPROGMEMM_JOB_STATUS_ERROR;
            ReProgMemM_StRequest.ubRequestSelect = REPROGMEMM_REQUEST_NO_FLASH_RQT;
        }
    }
    else
    {
        /* Nothing to do until previous job is done and driver is available */
    }
    SchM_Exit_ReProgMemM_SCHM_ReProgMemM_EXCLUSIVE_AREA_0();
}


static FUNC(void, ReProgMemM_CODE) ReProgMemM_ReadMngt(void)
{
    VAR (Std_ReturnType, ReProgMemM_VAR) ubMemoryAccessStatus;

#if (REPROGMEMM_TOPO_FLASH_ENABLED == STD_ON)
    VAR (uint32,         ReProgMemM_VAR) ulLogicalAddress;
#endif

    ubMemoryAccessStatus = E_NOT_OK;

    SchM_Enter_ReProgMemM_SCHM_ReProgMemM_EXCLUSIVE_AREA_0();

    /* Get the memory type of the job */
    ReProgMemM_UbMemoryType = ReProgMemM_GetMemoryTypeByAddress ( ReProgMemM_StRequest.ulStartAddress, ReProgMemM_StRequest.ulLength);

    /* Get the memory driver status */
    ReProgMemM_StRequest.ubJobStatus = ReProgMemM_GetDriverJobStatus();

    if (ReProgMemM_StRequest.ubJobStatus == REPROGMEMM_JOB_STATUS_NO_ERROR)
    {
        if (REPROGMEMM_MEM_TYPE_FLASH == ReProgMemM_UbMemoryType)
        {
#if (REPROGMEMM_TOPO_FLASH_ENABLED == STD_ON)
            /* Get the logical address to treat */
            ReProgMemM_CustomGetPhysicalToLogicalAddress(ReProgMemM_StRequest.ulAddressToTreat, &ulLogicalAddress);

            /* Get the Flash driver read status */
#if(REPROGMEMM_USE_MEMACC_ENABLE == STD_ON)
            /* !LINKSTO SwD.ReProgMemM.ReadMngt.6,1 */
            ubMemoryAccessStatus = MemAcc_Read (MemAcc_FOTA_AreaId_AddressAreaId, (MemAcc_AddressType) ulLogicalAddress, (MemAcc_DataType*) ReProgMemM_StRequest.pubDataPtr, (MemAcc_LengthType) ReProgMemM_StRequest.ulLength);
#else
            /* !LINKSTO SwD.ReProgMemM.FlashRead.If,1 */
            /* !LINKSTO SwD.ReProgMemM.ReadMngt.1,3 */
            ubMemoryAccessStatus = ReProgMemM_FlsDriver_Read(ulLogicalAddress, ReProgMemM_StRequest.ulLength, ReProgMemM_StRequest.pubDataPtr);
#endif
#endif
        }
        else if (REPROGMEMM_MEM_TYPE_FLASH_EXT == ReProgMemM_UbMemoryType)
        {
#if (REPROGMEMM_TOPO_FLASHEXT_ENABLED == STD_ON)
            /* Get the external Flash driver Read status */
/*#if (REPROGMEMM_USE_MEMACC_ENABLE == STD_ON)
            ubMemoryAccessStatus = MemAcc_Read (MemAcc_FOTA_AreaId_AddressAreaId, (MemAcc_AddressType) ulLogicalAddress, (MemAcc_DataType*) ReProgMemM_StRequest.pubDataPtr, (MemAcc_LengthType) ReProgMemM_StRequest.ulLength);
#else*/
            /* !LINKSTO SwD.ReProgMemM.ReadMngt.2,3 */
            ubMemoryAccessStatus = ReProgMemM_FlsExtDriver_Read(ReProgMemM_StRequest.ulAddressToTreat, ReProgMemM_StRequest.ulLength, ReProgMemM_StRequest.pubDataPtr);
/*#endif*/
#endif
        }
        else
        {
            /* !LINKSTO SwD.ReProgMemM.ReadMngt.5,1 */
            /* Unsupported memory - Can not happen */
        }

        if (E_OK == ubMemoryAccessStatus)
        {
            /* !LINKSTO SwD.ReProgMemM.ReadMngt.3,2 */
            ReProgMemM_StRequest.ubJobStatus = REPROGMEMM_JOB_STATUS_NO_ERROR;
        }
        else
        {
            /* !LINKSTO SwD.ReProgMemM.ReadMngt.4,2 */
            ReProgMemM_StRequest.ubJobStatus = REPROGMEMM_JOB_STATUS_ERROR;
        }

        ReProgMemM_StRequest.ubRequestSelect = REPROGMEMM_REQUEST_NO_FLASH_RQT;
    }
    else
    {
        /* Nothing to do until previous job is done and driver is available */
    }
    SchM_Exit_ReProgMemM_SCHM_ReProgMemM_EXCLUSIVE_AREA_0();
}

static FUNC(void, ReProgMemM_CODE) ReProgMemM_OrderFlashSecTableByAddr
(
  P2VAR(REPROGMEMM_CfgMemorySectorsProt_t, AUTOMATIC, ReProgMemM_APPL_DATA) secTable
)
{
    VAR   (uint32,                             ReProgMemM_VAR) secIndexI;
    VAR   (uint32,                             ReProgMemM_VAR) secIndexJ;
    VAR   (uint32,                             ReProgMemM_VAR) secNb;
    VAR   (REPROGMEMM_CfgMemorySectorsProt_t, ReProgMemM_VAR) secTemp;
    P2VAR (REPROGMEMM_CfgMemorySectorsProt_t, AUTOMATIC, ReProgMemM_APPL_DATA) secTabI;
    P2VAR (REPROGMEMM_CfgMemorySectorsProt_t, AUTOMATIC, ReProgMemM_APPL_DATA) secTabJ;

    secNb = REPROGMEMM_FLASH_SECTORS_ELEMENTS;

    /* Deviation TASKING-1 */
    /* Deviation TASKING-3 */
    if((secTable != NULL_PTR) && (secNb >= (uint32)(0x2U)))
    {
        /* !LINKSTO SwD.ReProgMemM.OrderFlashSecTableByAddr.2,1 */
        /* Deviation TASKING-3 */
        for(secIndexI=(uint32)(0U); secIndexI<(secNb-(uint32)(1U)); secIndexI++)
        {
            secTabI = (REPROGMEMM_CfgMemorySectorsProt_t *)(secTable+secIndexI);

            /* !LINKSTO SwD.ReProgMemM.OrderFlashSecTableByAddr.2,1 */
            for(secIndexJ=secIndexI+(uint32)(1U);secIndexJ<secNb; secIndexJ++)
            {
                secTabJ = (REPROGMEMM_CfgMemorySectorsProt_t *)(secTable+secIndexJ);

                if ( secTabI->ulStartAddress > secTabJ->ulStartAddress )
                {
                    /* !LINKSTO SwD.ReProgMemM.OrderFlashSecTableByAddr.1,1 */
                    SchM_Enter_ReProgMemM_SCHM_ReProgMemM_EXCLUSIVE_AREA_0();
                    IsFlashSecTableOrdered = FALSE;
                    SchM_Exit_ReProgMemM_SCHM_ReProgMemM_EXCLUSIVE_AREA_0();

                    TS_MemCpy(&secTemp, secTabI, sizeof(REPROGMEMM_CfgMemorySectorsProt_t));
                    TS_MemCpy(secTabI, secTabJ, sizeof(REPROGMEMM_CfgMemorySectorsProt_t));
                    TS_MemCpy(secTabJ, &secTemp, sizeof(REPROGMEMM_CfgMemorySectorsProt_t));
                }
            }
        }
    }
    else
    {
        /* !LINKSTO SwD.ReProgMemM.OrderFlashSecTableByAddr.3,1 */
        /* Nothing to do */
    }
}
#define REPROGMEMM_STOP_SEC_CODE
#include <ReProgMemM_MemMap.h>

/*==================[end of file]===========================================*/
