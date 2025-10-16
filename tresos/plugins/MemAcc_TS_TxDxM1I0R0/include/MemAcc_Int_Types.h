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
#ifndef MEMACC_INT_TYPES_H
#define MEMACC_INT_TYPES_H

/*==================[inclusions]============================================*/

#include <TSAutosar.h>            /* EB specific standard types     */
#include <MemAcc_Cfg.h>
                                  /* standard types                 */
#include <Std_Types.h>            /* AUTOSAR standard types. */
#include <MemAcc_Types.h>

#if (MEMACC_LEGACY_DRIVER_SUPPORT == STD_ON)
#include <MemIf.h>          /* memory interface types */
#endif

/*==================[type definitions]============================================*/

typedef uint8 MemAcc_IntJobStateType;

/** \brief This type represents state of an address area lock. */
typedef uint8 MemAcc_AddressAreaLockStateType;

/** \brief Priority of address area job type. */
typedef uint16 MemAcc_JobPriorityType;

 /** \brief This type represents the Mem API invocation type . */
typedef uint8 MemAcc_MemInvocationType;

#if (MEMACC_LEGACY_DRIVER_SUPPORT == STD_ON)
/* !LINKSTO MemAcc.EB.Legacy.DataTypes, 1*/
/** \brief Address type for legacy drivers Fls/Eep. */
typedef uint32 MemAcc_LegacyDriverAddressType;

/** \brief Length type for legacy drivers Fls/Eep. */
typedef uint32 MemAcc_LegacyDriverLengthType;

#endif
/*---------- [MemAcc Internal Job State]------------*/
#if (defined MEMACC_IDLE)
#error MEMACC_IDLE is already defined
#endif /* if (defined MEMACC_IDLE) */
  /** \brief No Job for this address area. */
#define  MEMACC_IDLE ((MemAcc_IntJobStateType)0U)

#if (defined MEMACC_INPROGRESS)
#error MEMACC_INPROGRESS is already defined
#endif /* if (defined MEMACC_INPROGRESS) */
  /** \brief Job is currently being processed. */
#define  MEMACC_INPROGRESS ((MemAcc_IntJobStateType)1U)

#if (defined MEMACC_WAITING)
#error MEMACC_WAITING is already defined
#endif /* if (defined MEMACC_WAITING) */
  /** \brief Job is waiting. */
#define  MEMACC_WAITING ((MemAcc_IntJobStateType)2U)

/*---------- [MemAcc Address Area Lock State]------------*/
#if (defined MEMACC_ADDRESSAREA_UNLOCKED)
#error MEMACC_ADDRESSAREA_UNLOCKED is already defined
#endif /* if (defined MEMACC_ADDRESSAREA_UNLOCKED) */
  /** \brief Address area is unlocked. */
#define  MEMACC_ADDRESSAREA_UNLOCKED ((MemAcc_AddressAreaLockStateType)0U)

#if (defined MEMACC_ADDRESSAREA_LOCKED)
#error MEMACC_ADDRESSAREA_LOCKED is already defined
#endif /* if (defined MEMACC_ADDRESSAREA_LOCKED) */
  /** \brief Address area is currently locked. */
#define  MEMACC_ADDRESSAREA_LOCKED ((MemAcc_AddressAreaLockStateType)1U)

#if (defined MEMACC_ADDRESSAREA_LOCK_REQUESTED)
#error MEMACC_ADDRESSAREA_LOCK_REQUESTED is already defined
#endif /* if (defined MEMACC_ADDRESSAREA_LOCK_REQUESTED) */
  /** \brief Address area is requested to be locked. */
#define  MEMACC_ADDRESSAREA_LOCK_REQUESTED ((MemAcc_AddressAreaLockStateType)2U)

/*---------- [MemAcc Invocation Types]------------*/
#if (defined DIRECT_STATIC)
#error DIRECT_STATIC is already defined
#endif /* if (defined DIRECT_STATIC) */
  /** \brief Mem driver is linked with application.
   ** Mem service functions are directly called by MemAcc. Mem_Init is called
   ** by EcuM and Mem_MainFunction is triggered by SchM.
  */
#define  DIRECT_STATIC ((MemAcc_MemInvocationType)0U)

#if (defined INDIRECT_DYNAMIC)
#error INDIRECT_DYNAMIC is already defined
#endif /* if (defined INDIRECT_DYNAMIC) */
  /** \brief Mem driver is linked as a separate binary and is dynamically activated.
   ** MemAcc will use Mem driver header table to invoke Mem service functions
   ** Call of Mem_Init and Mem_MainFunction is handled by MemAcc.
  */
#define  INDIRECT_DYNAMIC ((MemAcc_MemInvocationType)1U)

#if (defined INDIRECT_STATIC)
#error INDIRECT_STATIC is already defined
#endif /* if (defined INDIRECT_STATIC) */
  /** \brief Mem driver is linked with application.
   ** MemAcc will use Mem driver header table to invoke Mem service functions
   ** Call of Mem_Init and Mem_MainFunction is handled by MemAcc.
  */
#define  INDIRECT_STATIC ((MemAcc_MemInvocationType)2U)

#if (defined DIRECT_LEGACY)
#error DIRECT_LEGACY is already defined
#endif /* if (defined DIRECT_LEGACY) */
  /** \brief Fls/Eep driver is linked with application.
   ** Fls/Eep service functions are directly called by MemAcc. Fls_Init is called
   ** by EcuM and Fls_MainFunction is triggered by SchM.
  */
#define  DIRECT_LEGACY ((MemAcc_MemInvocationType)3U)

/*=========[ flash memory driver Function pointers definitions]=============*/
#if ( MEMACC_MEM_DRIVER_SUPPORT == STD_ON )

/**  \brief Defines the type for flash memory MainFunction function . */
typedef FUNC( void,MEMACC_CODE)MemAcc_MemMainFuncType(MemAcc_MemInstanceIdType InstanceId);

/**  \brief Defines the type for flash memory init function . */
typedef FUNC( void,MEMACC_CODE )MemAcc_MemInitFuncType(MemAcc_MemInstanceIdType InstanceId, const MemAcc_ConfigType* ConfigPtr);

/**  \brief Defines the type for flash memory Erase function . */
typedef FUNC( Std_ReturnType,MEMACC_CODE)MemAcc_MemEraseFuncType(MemAcc_MemInstanceIdType InstanceId, MemAcc_AddressType TargetAddress, MemAcc_LengthType Length );

/**  \brief Defines the type for flash memory BlankCheck function . */
typedef FUNC( Std_ReturnType,MEMACC_CODE)MemAcc_MemBlankCheckFuncType(MemAcc_MemInstanceIdType InstanceId, MemAcc_AddressType TargetAddress, MemAcc_LengthType Length );

/**  \brief Defines the type for flash memory Write function . */
typedef FUNC( Std_ReturnType,MEMACC_CODE)MemAcc_MemWriteFuncType(MemAcc_MemInstanceIdType InstanceId, MemAcc_AddressType TargetAddress, const uint8* SourceDataPtr, MemAcc_LengthType Length );

/**  \brief Defines the type for flash memory Read function . */
typedef FUNC( Std_ReturnType,MEMACC_CODE)MemAcc_MemReadFuncType(MemAcc_MemInstanceIdType InstanceId, MemAcc_AddressType SourceAddress, uint8* DestinationDataPtr, MemAcc_LengthType Length);

/**  \brief Defines the type for flash memory GetJobResult function . */
typedef FUNC( MemAcc_Mem_JobResultType,MEMACC_CODE)MemAcc_MemGetJobResultFuncType(MemAcc_MemInstanceIdType InstanceId);

/**  \brief Defines the type for flash memory hardware specific function . */
typedef FUNC( Std_ReturnType,MEMACC_CODE)MemAcc_MemHwSpecificServiceType(MemAcc_MemInstanceIdType InstanceId ,
                                                       MemAcc_DataType* Data,MemAcc_LengthType Length);
#endif /* MEMACC_MEM_DRIVER_SUPPORT */
/* -----------------------------[ Type definitions for legacy API driver ]--------------------------------------- */

#if (MEMACC_LEGACY_DRIVER_SUPPORT == STD_ON)
/**  \brief Defines the type for legacy flash memory Erase function . */
typedef FUNC( Std_ReturnType,MEMACC_CODE)MemAcc_MemEraseFuncLegacyType( MemAcc_LegacyDriverAddressType TargetAddress, MemAcc_LegacyDriverLengthType Length );

/**  \brief Defines the type for legacy flash memory BlankCheck function . */
typedef FUNC( Std_ReturnType,MEMACC_CODE )MemAcc_MemBlankCheckFuncLegacyType( MemAcc_LegacyDriverAddressType TargetAddress, MemAcc_LegacyDriverLengthType Length );

/**  \brief Defines the type for legacy flash memory Write function . */
typedef FUNC( Std_ReturnType,MEMACC_CODE )MemAcc_MemWriteFuncLegacyType( MemAcc_LegacyDriverAddressType TargetAddress, const uint8* SourceDataPtr, MemAcc_LegacyDriverLengthType Length );

/**  \brief Defines the type for legacy flash memory Read function . */
typedef FUNC( Std_ReturnType,MEMACC_CODE)MemAcc_MemReadFuncLegacyType(MemAcc_LegacyDriverAddressType SourceAddress, uint8* DestinationDataPtr, MemAcc_LegacyDriverLengthType Length);

/**  \brief Defines the type for legacy flash memory GetJobResult function. */
typedef FUNC( MemIf_JobResultType,MEMACC_CODE )MemAcc_MemGetJobResultFuncLegacyType( void );
#endif

/** \brief Layout of a sector batch */
typedef struct
{
  /** \brief Size of a sector in bytes. */
  uint32 SectorSize;
  /** \brief Size of a page read in bytes. */
  uint32 ReadPageSize;
  /** \brief Size of a page write in bytes. */
  uint32 WritePageSize;
  /** \brief It define Max erase cycles. */
  uint32 MaxEraseCycles;
#if (MEMACC_ERASE_BURST_SUPPORT == STD_ON)
  /** \brief Size of a sector burst in bytes. Equals SectorSize in case burst is disabled. */
  uint32 SectorBurstSize;
#endif
#if (MEMACC_READ_BURST_SUPPORT == STD_ON)
  /** \brief Size of a read Page burst in bytes. Equals PageSize in case burst is disabled. */
  uint32 ReadPageBurstSize;
#endif
#if (MEMACC_WRITE_BURST_SUPPORT == STD_ON)
  /** \brief Size of a write Page burst in bytes. Equals PageSize in case burst is disabled. */
  uint32 WritePageBurstSize;
#endif
} MemAcc_SectorBatchType;

/** \brief Layout information of an address sub area  */
typedef struct
{
  /** \brief Physical start Address of a sub area. */
  MemAcc_AddressType PhysicalStartAddress;
  /** \brief Logical start Address of a sub area. */
  MemAcc_AddressType LogicalStartAddress;
  /** \brief sub area length. */
  MemAcc_LengthType Length;
  /** \brief Memory driver Hardware identifier. */
  MemAcc_HwIdType DrvHwId;
  /** \brief Referenced sector batch pointer. */
  const MemAcc_SectorBatchType* SectorBatch;
#if (MEMACC_ERASE_RETRY_SUPPORT == STD_ON)
  /** \brief This value specifies the number of retries of a failed erase job. */
  uint8 NumberOfEraseRetries;
#endif
#if (MEMACC_WRITE_RETRY_SUPPORT == STD_ON)
  /** \brief This value specifies the number of retries of a failed write job. */
  uint8 NumberOfWriteRetries;
#endif
#if (MEMACC_ERASE_BURST_SUPPORT == STD_ON)
  /** \brief This flag is set to TRUE when erase burst is enabled for sub-area*/
  boolean UseEraseBurst;
#endif
#if (MEMACC_READ_BURST_SUPPORT == STD_ON)
  /** \brief This flag is set to TRUE when read burst is enabled for sub-area*/
  boolean UseReadBurst;
#endif
#if (MEMACC_WRITE_BURST_SUPPORT == STD_ON)
  /** \brief This flag is set to TRUE when write burst is enabled for sub-area*/
  boolean UseWriteBurst;
#endif
#if (MEMACC_VARIABLE_WRITE_SUPPORT == STD_ON)
    /** \brief This flag is set to TRUE when variable write is enabled for sub-area*/
  boolean UseVariableWrite;
#endif
} MemAcc_AddressSubAreaType;

/** \brief Admin runtime data of an address sub area  */
typedef struct
{
  /** \brief Pointer to user data for the next memory driver operation. */
  P2CONST(MemAcc_DataType, AUTOMATIC, MEMACC_APPL_DATA) UserDataPtr;
  /** \brief Physical start address of a sub area job. */
  MemAcc_AddressType JobPhysicalStartAddress;
  /** \brief Remaining length. */
  MemAcc_LengthType RemainingLength;
  /** \brief Current Job status. */
  MemAcc_IntJobStateType JobState;
  /** \brief MemDrv Job result from previous cycle. */
  MemAcc_Mem_JobResultType MemDrvJobResult;
} MemAcc_AddressSubAreaAdminType;

/** \brief Layout information of an address area  */
typedef struct
{
  /** \brief Pointer to address sub areas array. */
  CONSTP2CONST(MemAcc_AddressSubAreaType, AUTOMATIC, MEMACC_APPL_CONST) SubAreaCfg;
#if (MEMACC_COMPARE_API == STD_ON)
  /** \brief Pointer to the address area buffer used for reading data from Mem/Fls/Eep during compare API processing. */
  CONSTP2VAR(MemAcc_DataType, AUTOMATIC, MEMACC_APPL_CONST) AddressAreaCmpBuffer;
#endif
  /** \brief Address area error status callback function. */
  AddressAreaJobEndNotification AddressAreaCallback;
  /** \brief logical start Address of an address area. */
  MemAcc_AddressType LogicalStartAddress;
  /** \brief Address area length. */
  MemAcc_LengthType Length;
  /** \brief Address area id. */
  MemAcc_AddressAreaIdType AddressAreaId;
  /** \brief Priority of address area job. */
  MemAcc_JobPriorityType JobPriority;
  /** \brief Buffer alignment value. */
  uint8 BufferAlignmentValue;
  /** \brief Number of sub areas. */
  uint8 NumberOfSubAreas;
} MemAcc_AddressAreaCfgType;

/** \brief Admin runtime data of the Address Area */
typedef struct
{
  /** \brief Current address area job logical address.  */
  MemAcc_AddressType JobLogicalAddress;
  /** \brief Current address area job length.  */
  MemAcc_LengthType JobLength;
  /** \brief Processed job length.  */
  MemAcc_LengthType ProcessedLength;
  /** \brief Current Mem request length.  */
  MemAcc_LengthType MemLength;
  /** \brief Index of the current sub area to be executed (might be waiting due to a higher prio job)*/
  MemAcc_AddressAreaIdType LastActiveSubAreaIdx;
  /** \brief Index of pending sub-area job */
  MemAcc_AddressAreaIdType SubAreaIdx;
  /** \brief Structure holding the data for the current sub-area job*/
  MemAcc_AddressSubAreaAdminType SubAreaAdmin;
  /** \brief Current address area job result.  */
  MemAcc_JobResultType JobResult;
  /** \brief Current address area job status.  */
  MemAcc_JobStatusType JobStatus;
  /** \brief Current address area job type. */
  MemAcc_JobType JobType;
#if ((MEMACC_ERASE_RETRY_SUPPORT == STD_ON) || (MEMACC_WRITE_RETRY_SUPPORT == STD_ON))
  /** \brief Number of retries performed for an ongoing erase/write job */
  uint8 JobRetryCounter;
#endif
  /** \brief Current address area lock state.  */
  MemAcc_AddressAreaLockStateType AddressAreaLockState;
}MemAcc_AdminAddressAreaType;

/** \brief Lock request data of the Address Area */
typedef struct
{
  /** \brief Pointer to address area lock notification callback function. */
  ApplicationLockNotification AddressAreaLockNotification;

  /** \brief Lock request for the area */
  boolean Lock;

  /** \brief New lock state requested for the area since last main cycle.*/
  boolean LockStateChangeRequest;
}MemAcc_AddressAreaLockType;

#if ( MEMACC_MEM_DRIVER_SUPPORT == STD_ON )
/** \brief Layout information of a memory driver APIs pointers  */
typedef struct
{
  #if (MEMACC_HANDLING_SUPPORT == STD_ON)
  /** \brief Init API function pointer. */
  MemAcc_MemInitFuncType* Init;
  /** \brief MainFunction API function pointer. */
  MemAcc_MemMainFuncType* MainFunction;
  #endif
  /** \brief GetJobResult API function pointer. */
  MemAcc_MemGetJobResultFuncType* GetJobResult;
  /** \brief Read API function pointer. */
  MemAcc_MemReadFuncType* Read;
  /** \brief Write API function pointer. */
  MemAcc_MemWriteFuncType* Write;
  /** \brief Erase API function pointer. */
  MemAcc_MemEraseFuncType* Erase;
  /** \brief BlankCheck API function pointer. */
  MemAcc_MemBlankCheckFuncType* BlankCheck;
} MemAcc_MemApi_Type;
#endif /* MEMACC_MEM_DRIVER_SUPPORT */

#if (MEMACC_LEGACY_DRIVER_SUPPORT == STD_ON)
/** \brief Layout information of a legacy memory driver APIs pointers  */
typedef struct
{
  /** \brief GetJobResult API function pointer. */
  MemAcc_MemGetJobResultFuncLegacyType* GetJobResult;
  /** \brief Read API function pointer. */
  MemAcc_MemReadFuncLegacyType* Read;
  /** \brief Write API function pointer. */
  MemAcc_MemWriteFuncLegacyType* Write;
  /** \brief Erase API function pointer. */
  MemAcc_MemEraseFuncLegacyType* Erase;
  /** \brief BlankCheck API function pointer. */
  MemAcc_MemBlankCheckFuncLegacyType* BlankCheck;
} MemAcc_MemApi_LegacyType;
#endif

/** \brief Layout of the configured memory drivers information that are necessary to
 * interact with memory drivers  */
typedef struct
{
  /** \brief Pointer to driver APIs table. */
  const void* DrvApiTable ;
  /** \brief Referenced memory driver instance identifier. */
  MemAcc_MemInstanceIdType MemInstanceId;
  /** \brief Driver API invocation type. */
  MemAcc_MemInvocationType DrvInvocationType ;
} MemAcc_MemoryDrvInfoType;

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* MEMACC_INT_TYPES_H */

/*=========================[end of file MemAcc_Int_Types.h]========================*/
