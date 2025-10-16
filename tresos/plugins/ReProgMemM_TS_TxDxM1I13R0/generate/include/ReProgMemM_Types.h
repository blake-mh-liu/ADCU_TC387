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

#ifndef REPROGMEMM_TYPES_H
#define REPROGMEMM_TYPES_H

/*==================[includes]================================================*/
#include "Std_Types.h"                              /* AUTOSAR standard types */

/*==================[macros]==================================================*/

#define REPROGMEMM_INVALID_LENGTH 0U


/*==================[type definitions]========================================*/
/** \brief ReProgMemM layer FALSE define used for boolean actions in the layer*/
typedef uint8  REPROGMEMM_Boolean_t;
#define REPROGMEMM_FALSE   0U
/** \brief ReProgMemM layer TRUE define used for boolean actions in the layer*/
#define REPROGMEMM_TRUE    1U

typedef uint8  REPROGMEMM_MemoryType_t;
#define REPROGMEMM_MEM_TYPE_INIT                      0xFFU
#define REPROGMEMM_MEM_TYPE_FLASH                     0x00U
#define REPROGMEMM_MEM_TYPE_EEPROM                    0x01U
#define REPROGMEMM_MEM_TYPE_RAM                       0x02U
#define REPROGMEMM_MEM_TYPE_SCRATCHPAD                0x03U
#define REPROGMEMM_MEM_TYPE_FLASH_EXT                 0x04U
#define REPROGMEMM_MEM_TYPE_CUSTOM                    0x05U

typedef uint8  REPROGMEMM_JobStatus_t;
#define REPROGMEMM_JOB_STATUS_NO_ERROR                0x00U
#define REPROGMEMM_JOB_STATUS_ERROR                   0x01U
#define REPROGMEMM_JOB_STATUS_BUSY                    0x02U
#define REPROGMEMM_JOB_STATUS_INTERNAL_INIT_OK        0x03U
#define REPROGMEMM_JOB_STATUS_EXTERNAL_INIT_OK        0x04U
#define REPROGMEMM_JOB_STATUS_ALIGNMENT_FAILED        0x05U
#define REPROGMEMM_JOB_STATUS_NOTPROTECTED_FAILED     0x06U
#define REPROGMEMM_JOB_STATUS_BLANKCHECK_FAILED       0x07U
#define REPROGMEMM_JOB_STATUS_MEMORY_NOT_INITIALIZED  0x08U

typedef uint8  REPROGMEMM_MemoryIdx_t;

typedef uint32 REPROGMEMM_Address_t;

typedef uint8 REPROGMEMM_AccessType_t;
#define REPROGMEMM_MEM_ACCESS_TYPE_NONE             0x00U
#define REPROGMEMM_MEM_ACCESS_TYPE_READ             0x01U
#define REPROGMEMM_MEM_ACCESS_TYPE_WRITE            0x02U
#define REPROGMEMM_MEM_ACCESS_TYPE_READ_WRITE       0x03U

typedef uint8  REPROGMEMM_SectorProtectionType_t;
#define REPROGMEMM_SECTOR_NOT_PROTECTED             0x00U
#define REPROGMEMM_SECTOR_WRITE_PROTECTED           0x01U

#define REPROGMEMM_DUALBANK_A_BANK_ACTIVE           0x01U
#define REPROGMEMM_DUALBANK_B_BANK_ACTIVE           0x02U
#define REPROGMEMM_DUALBANK_ACTIVE_BANK_NOK         0xFFU

#define REPROGMEMM_MEMACC_ACCESSINACTIVEBANK_ON     2U
#define REPROGMEMM_MEMACC_ACCESSINACTIVEBANK_OFF    1U

typedef uint32 REPROGMEMM_Protection_Password_t;

/* memory sectors Protection Configuration type */
#define REPROGMEMM_PROT_PASSWORD_SIZE               8U
typedef struct
{
    REPROGMEMM_Protection_Password_t      aulProtectionPassword[REPROGMEMM_PROT_PASSWORD_SIZE]; /* PFLASH config Protection Password */
    uint32                                ulStartAddress;                                       /* Start Address of the sector */
    uint32                                ulLength;                                             /* Length of the sector */
    uint32                                ulSectorSize;                                         /* Sector size */
    REPROGMEMM_SectorProtectionType_t     ubSectorProtection;                                   /* Sector protection activation */
}REPROGMEMM_CfgMemorySectorsProt_t;

/* memory configuration structure type */
typedef struct
{
    REPROGMEMM_MemoryType_t       ubMemoryType;
    uint32                        ulMinValueToWrite;
    uint16                        ulBlockLength;
    REPROGMEMM_Address_t          ulAddressOffset;
    uint8                         ubEraseValue;
    REPROGMEMM_Address_t          ulMemoryStartAddress;
    uint32                        ulMemoryLength;
}REPROGMEMM_CfgMemory_t;

typedef uint8 REPROGMEMM_RequestSelect_t;
/*#define REPROGMEMM_REQUEST_INIT           0x00U*/
#define REPROGMEMM_REQUEST_ERASE          0x01U
#define REPROGMEMM_REQUEST_WRITE          0x02U
#define REPROGMEMM_REQUEST_READ           0x03U
#define REPROGMEMM_REQUEST_NO_FLASH_RQT   0x04U

/* Constant indicating where the operation (Read..) should be performed */
#define REPROGMEMM_MEMACC_ACTIVE_BANK               0x01U
#define REPROGMEMM_MEMACC_INACTIVE_BANK             0x02U

/* Process/Operation return type */
#define REPROGMEMM_STATUS_PENDING         0x20U        /* Process On Going */

/* memory configuration structure type */
typedef struct
{
    REPROGMEMM_RequestSelect_t      ubRequestSelect;
    REPROGMEMM_JobStatus_t          ubJobStatus;
    uint32                          ulStartAddress;
    uint32                          ulLength;
    uint32                          ulEndAddress;
    uint32                          ulAddressToTreat;
    uint32                          ulAddressTreated;
    uint32                          ulNbOfPagesToWrite;
    uint8*                          pubDataPtr;
}REPROGMEMM_Request_t;

/*==================[external function declarations]==========================*/

/*==================[internal function declarations]==========================*/

/*==================[external constants]======================================*/

/*==================[internal constants]======================================*/

/*==================[external data]===========================================*/

/*==================[internal data]===========================================*/

/*==================[external function definitions]===========================*/

/*==================[internal function definitions]===========================*/

#endif /* ifndef REPROGMEMM_TYPES_H */

/*==================[end of file]=============================================*/
