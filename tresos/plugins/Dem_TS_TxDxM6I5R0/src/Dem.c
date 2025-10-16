/**
 * \file
 *
 * \brief AUTOSAR Dem
 *
 * This file contains the implementation of the AUTOSAR
 * module Dem.
 *
 * \version 6.5.8
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2024 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/* This file contains definitions for interface functions provided by Dem to
 * the Ecu State Manager and SW-Components. */

/* MISRA-C:2012 Deviation List
 *
 *  MISRAC2012-1) Deviated Rule: 8.3 (required)
 *    "All declarations of an object or function shall use the same names
 *    and type qualifiers"
 *
 *    Reason:
 *    Different data types names are generated for the Rte ASR42 and ASR40
 *    interfaces, having compatible types.
 *
 *  MISRAC2012-2) Deviated Rule: 2.1 (required)
 *    "A project shall not contain unreachable code."
 *
 *    Reason:
 *    Run time check for the active OBD variant is always DEM_OBD_VARIANT_OBDONUDS
 *    when switching/selection of the OBD variant is not supported.
 *
 *  MISRAC2012-3) Deviated Rule 11.3 (required)
 *    "A cast shall not be performed between a pointer to object type and
 *     a pointer to a different object type."
 *
 *    Reason:
 *    Cast is needed as Float32 to uint32 conversion is needed to store in
 *    uint8 buffer.
 */

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * The compiler optimizes the 'for' loop (which has only 1 iteration) in the
 * following way:
 * - it prepares in advance the index for the next iteration;
 * - if the index is equal to '0' it goes back to check the 'for' loop
 *   conditions, otherwise it just moves on;
 * - since the index is already equal to '1', it never jumps back to check the
 *   exit condition.
 *
 * TASKING-2) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * The compiler optimizes the 'while' loop when it has a single iteration.
 * The warning is a false positive, as the 'false' condition which terminates
 * the loop is reached. This is proven by the coverage metrics and by the fact
 * that the loop is not infinite.
 *
 * TASKING-3) Deviated Rule: W541
 * W541: array subscript is above array bounds
 *
 * Reason:
 * False positive, index is accessing array inside bounds.
 *
 * TASKING-4) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * "Result" remains E_NOT_OK only if ASR40_GetEventFreezeFrameData returns E_NOT_OK.
 * In other configurations, the code coverage reaches sections where the result is
 * equal with the value E_OK.
 *
 * TASKING-5) Deviated Rule: W549
 * W549: condition is always false
 *
 * Reason:
 * values for "HandlePassedEvents" and "HandleFailedEvents" updates based on event
 * queue length. In other configurations, the code coverage reaches sections
 * where "HandlePassedEvents" and "HandleFailedEvents" value is zero.
 *
 * TASKING-6) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * "ResetImmediateNvData" is FALSE if the Dem_RestoreImmediateData function is called
 * with a FALSE argument. In other configurations, the code coverage reaches sections
 * where ResetImmediateNvData is different from the value FALSE.
 *
 * TASKING-7) Deviated Rule: W549
 * W549: condition is always false
 *
 * Reason:
 * "ProcessEntryResult" is DEM_E_NODATAAVAILABLE only if the function Dem_ProcessEventEntry
 * returns DEM_E_NODATAAVAILABLE. In other configurations, the code coverage reaches
 * sections where ProcessEntryResult is equal to the value DEM_E_NODATAAVAILABLE.
 *
 * TASKING-8) Deviated Rule: W549
 * W549: condition is always false
 *
 * Reason:
 * The values for "OtherEventStatusChanged" or "CurrentEventStatusChanged" are TRUE only if
 * at least one status had changed. In other configurations, the code coverage reaches sections
 * where either "OtherEventStatusChanged" or "CurrentEventStatusChanged" value is TRUE.
 *
 * TASKING-9) Deviated Rule: W507
 * W507: variable "IndicatorIdx" is possibly uninitialized
 *
 * Reason:
 * The variable "IndicatorIdx" is read only if Dem_IsMILEvent(EventId, &IndicatorIdx) returns TRUE
 * case in which the initialization of the variable is ensured by the function algorithm.
 *
 * TASKING-10) Deviated Rule: W549
 * W549: condition is always false
 *
 * Reason:
 * The function Dem_InternalGetEventFreezeFrameData() can have return values DEM_E_WRONG_DIDNUMBER,
 * DEM_E_WRONG_RECORDNUMBER, DEM_E_NODATAAVAILABLE when an invalid DID or invalid record number
 * or not stored event ID in its entry are passed as an arguments. In other configurations,
 * the code coverage reaches sections where Dem_InternalGetEventFreezeFrameData return value
 * is equal to DEM_E_WRONG_DIDNUMBER or DEM_E_WRONG_RECORDNUMBER or DEM_E_NODATAAVAILABLE.
 *
 * TASKING-11) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * The function Dem_InternalGetEventExtendedDataRecord() can have return value
 * E_OK when extended data is updated properly in destination buffer. In other configurations,
 * the code coverage reaches section where Dem_InternalGetEventExtendedDataRecord return
 * value is equal to E_OK.
 *
 * TASKING-12) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * The values of "EDSegSize" is zero when the event is not available in its
 * memory entry and "Result" is updated to DEM_BUFFER_TOO_SMALL when the input
 * parameter Bufsize is less than the extended data record size. In other
 * configurations, the code coverage reaches section where "EDSegSize" value
 * is zero or "Result" value is DEM_BUFFER_TOO_SMALL.
 *
 * TASKING-13) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * If (DEM_TRIGGER_ON_DEQUALIFICATION_SUPPORT == STD_ON) freeze frame data
 * must also be captured for passed reports to update the dequalification
 * data elements, when an entry already exists.
 * If the feature is not used, check might always be true.
 */

/*==================[inclusions]============================================*/
/* !LINKSTO dsn.Dem.IncludeStr,1 */

#include <Std_Types.h>                            /* AUTOSAR standard types */
#include <TSAutosar.h>                        /* EB specific standard types */
#include <TSMem.h>                          /* EB specific memory functions */

#include <Dem_Int.h>             /* module public and internal declarations */
#include <Dem_Trace.h>                        /* Dbg related macros for Dem */

#if (DEM_USE_PERMANENT_STORAGE == STD_ON)
#include <NvM.h>                                      /* memory access APIs */
#endif
#if ( (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) && \
      (DEM_SUPPORT_FIM_ON_FDC_TRESHOLD == STD_ON) )
#include <FiM.h>                                        /* FiM trigger APIs */
#endif

/*==================[macros]================================================*/
/* !LINKSTO Dem.Version.Check,2 */

/*------------------[AUTOSAR vendor identification check]-------------------*/

#ifndef DEM_VENDOR_ID /* configuration check */
#error DEM_VENDOR_ID must be defined
#endif

#if (DEM_VENDOR_ID != 1U) /* vendor check */
#error DEM_VENDOR_ID has wrong vendor id
#endif

/*------------------[AUTOSAR release version identification check]----------*/

#ifndef DEM_AR_RELEASE_MAJOR_VERSION /* configuration check */
#error DEM_AR_RELEASE_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (DEM_AR_RELEASE_MAJOR_VERSION != 4U)
#error DEM_AR_RELEASE_MAJOR_VERSION wrong (!= 4U)
#endif

#ifndef DEM_AR_RELEASE_MINOR_VERSION /* configuration check */
#error DEM_AR_RELEASE_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (DEM_AR_RELEASE_MINOR_VERSION != 0U )
#error DEM_AR_RELEASE_MINOR_VERSION wrong (!= 0U)
#endif

#ifndef DEM_AR_RELEASE_REVISION_VERSION /* configuration check */
#error DEM_AR_RELEASE_REVISION_VERSION must be defined
#endif

/* revision version check */
#if (DEM_AR_RELEASE_REVISION_VERSION != 3U )
#error DEM_AR_RELEASE_REVISION_VERSION wrong (!= 3U)
#endif

/*------------------[AUTOSAR module version identification check]-----------*/

#ifndef DEM_SW_MAJOR_VERSION /* configuration check */
#error DEM_SW_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (DEM_SW_MAJOR_VERSION != 6U)
#error DEM_SW_MAJOR_VERSION wrong (!= 6U)
#endif

#ifndef DEM_SW_MINOR_VERSION /* configuration check */
#error DEM_SW_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (DEM_SW_MINOR_VERSION < 5U)
#error DEM_SW_MINOR_VERSION wrong (< 5U)
#endif

#ifndef DEM_SW_PATCH_VERSION /* configuration check */
#error DEM_SW_PATCH_VERSION must be defined
#endif

/* patch version check */
#if (DEM_SW_PATCH_VERSION < 8U)
#error DEM_SW_PATCH_VERSION wrong (< 8U)
#endif

#if (DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON)
#if (defined DEM_SET_STORAGE_ORDER_ID_ARRAY)
#error DEM_SET_STORAGE_ORDER_ID_ARRAY already defined
#endif
/** \brief Macro to set StorageOrderId in an array */
#define DEM_SET_STORAGE_ORDER_ID_ARRAY(dest, src) \
(dest)[0] = (uint8) ((uint32)(src) >> (16U)); \
(dest)[1] = (uint8) ((uint32)(src) >> (8U)); \
(dest)[2] = (uint8) (src);

#if (defined DEM_GET_STORAGEORDERID_UINT32)
#error DEM_GET_STORAGEORDERID_UINT32 already defined
#endif
/** \brief Macro to get StorageOrderId in uint32 format
 **
 ** Macro converts three elements of StorageOrderId array to a uint32 in
 ** Big-endian representation.
 */
#define DEM_GET_STORAGEORDERID_UINT32(Array) \
  (((uint32)((Array)[2])) | ((uint32)((Array)[1]) << 8U) | ((uint32)((Array)[0]) << 16U))
#endif /* DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON */

#if (defined DEM_IS_ERROR_QUEUE_EMPTY)
#error DEM_IS_ERROR_QUEUE_EMPTY already defined
#endif
/** \brief Macro to check, if the internal error queue is empty */
#define DEM_IS_ERROR_QUEUE_EMPTY() \
  ( Dem_ErrorQueue[Dem_ErrorQueueReadIdx] == \
    (Dem_ErrorQueueEntryType)DEM_EVENT_ID_INVALID )

/*==================[type definitions]======================================*/

/** \brief Type of event memory entry allocation result */
typedef enum
{
  DEM_EVENTENTRYALLOC_INVALID   = 0,           /**< entry allocation failed */
  DEM_EVENTENTRYALLOC_ALLOCATED = 1,               /**< new entry allocated */
  DEM_EVENTENTRYALLOC_REPLACED  = 2,           /**< existing entry replaced */
  DEM_EVENTENTRYALLOC_EXISTS    = 3            /**< existing entry selected */
} Dem_EventEntryAllocResultType;

/** \brief Function pointer type for generic "Sw-Unit Initializer" function */
typedef P2FUNC(void, DEM_CODE, Dem_InitSwUnitFncPtrType) (void);

#if ( (DEM_J1939_SUPPORT == STD_ON) && \
      ( (DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON) || \
        (DEM_J1939_READING_DTC_SUPPORT == STD_ON) ) )
/** \brief Function pointer type for generic J1939 Initialize */
typedef P2FUNC(void, DEM_CODE, Dem_InitJ1939FncPtrType) (void);
#endif

#if (DEM_USE_EVENT_DISPLACEMENT == STD_ON)
/*------------------[definitions for event displacement]--------------------*/
/** \brief Event displacement criterion match type
 **
 ** The range is ordered in descending significance.
 */
 typedef enum
{
  DEM_CRITERION_MATCH_AGED,
  DEM_CRITERION_MATCH_PRIO,
  DEM_CRITERION_MATCH_PASSIVE_STATUS,
  DEM_CRITERION_MATCH_TNCTOC_STATUS,
  DEM_CRITERION_MATCH_NONE
} Dem_EventDisplacementCriterionMatchType;
#endif /* DEM_USE_EVENT_DISPLACEMENT == STD_ON */

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( (DEM_USE_PERMANENT_STORAGE == STD_ON) || \
      (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U) )
/** \brief Function to get the status of a NvM block
 **
 ** This is an interface function to the NvM, to get the status of a NvM block.
 **
 ** \param[in] NvDataBlockId Id of the NvM block
 **
 ** \return Std_ReturnType value indication success
 ** \retval E_OK     the block was restored successfully from NVRAM
 ** \retval E_NOT_OK the block was NOT restored successfully from NVRAM
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_NvMGetNvRAMBlockStatus(
  NvM_BlockIdType NvDataBlockId);
#endif

/** \brief Function to reset the non-volatile Dem data
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 **
 ** \note Implementation is OEM specific.
 */
STATIC FUNC(void, DEM_CODE) Dem_ResetNvData(void);

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
/** \brief Function to restore the non-volatile Dem data immediately
 ** via NvM single block read functionality
 **
 ** If data restore fails then entry status is set such that either the reset
 ** data or new event data shall be written persistently during shutdown
 **
 ** \param[in] ResetImmediateNvData contains true/false condition to reset NvM data memory
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_RestoreImmediateData(boolean ResetImmediateNvData);

/** \brief Function derives the bits TNCSLC, TFSLC and CDTC
 **
 ** This function derives the bits TNCSLC, TFSLC and CDTC based on the
 ** event memory entry.
 **
 ** \param[in]   GateEntryBase  Pointer to the common gate-entry data
 ** \param[in]   EvMemEntry     Pointer to the destination memory of the event
 ** \param[in]   EventId        Identifies the Dem event
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_RestoreDerivedEventStatus(
  P2VAR(Dem_GateEntryBaseType, AUTOMATIC, DEM_VAR_CLEARED) GateEntryBase,
  Dem_EventMemoryEntryPtrType                              EvMemEntry,
  Dem_EventIdType                                          EventId);
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */

#if (DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON)
/** \brief Function to initialize the 'StorageOrderId generator' state
 **
 ** This function initializes the 'StorageOrderId generator' state based on
 ** the largest values corresponding to the StorageOrderIds stored in the
 ** non-volatile blocks.
 ** It needs to be called during Dem_Init() first for the event status block
 ** and afterwards for a non-volatile data block with the largest
 ** StorageOrderId.
 **
 ** \param[in]  LargestStorageOrderId  The value corresponding to the largest
 **                                    StorageOrderId for the non-volatile
 **                                    blocks of respective BlockType.
 ** \param[in]  BlockType              The type of the non-volatile block for
 **                                    which the LargestStorageOrderId is
 **                                    reported.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_NotifyUsedStorageOrderId(
  uint32                      LargestStorageOrderId,
  Dem_StorageOrderIdBlockType BlockType);

/** \brief Function to restore the DTC status of the events
 **
 ** It is used for restoring the DTC status of the events with immediate
 ** storage enabled.
 **
 ** \param[in]  DataValue   Pointer to the memory location from where the
 **                         DTC/event status is restored.
 ** \param[in]  EventId     Id of the event for which the DTC status is
 **                         restored.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_RestoreDTCStatus(
  P2CONST(uint8, AUTOMATIC, DEM_APPL_DATA) DataValue,
  Dem_EventIdType                          EventId);

/** \brief Function to restore DTC status and largest StorageOrderId
 **
 ** This function restores the DTC status of the events with intermediate
 ** storage enabled and retrieves the largest StorageOrderId among all the
 ** event data blocks.
 **
 ** \param[in]    EventId             Identifies the Dem event
 ** \param[in]    GateEntryStorageOrderId  Pointer to
 **                                   StorageOrderIdAndDTCStatus[] arrays from
 **                                   nonvolatile gate-entries of the event
 **                                   memory blocks
 ** \param[out]   LargestDataBlockId  The value corresponding to the largest
 **                                   StorageOrderId between the event status
 **                                   block and a given event data block
 **
 ** \return       boolean             Status of Intermediate DTC status
 **                                   restoration
 ** \retval       TRUE                Intermediate DTC status restored
 ** \retval       FALSE               Intermediate DTC status not restored
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_RestoreIntermediateDTCstatus(
  uint32                                    StorageOrderStatusBlockId,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC)       LargestDataBlockId,
  P2CONST(uint8, AUTOMATIC, DEM_APPL_DATA)  GateEntryStorageOrderId,
  Dem_EventIdType                           EventId);
#endif /* DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON */

#if ( (DEM_USE_PERMANENT_STORAGE == STD_ON) && \
      ((DEM_STATUS_BIT_STORAGE_TF == STD_OFF) || \
      (DEM_STATUS_BIT_STORAGE_TF_PER_EVENT_SUPPORT == STD_ON)) )
/** \brief Function to clear TestFailed(TF) status bit
 **
 ** This function clears TestFailed(TF) status bit when non-volatile storage
 ** of TF bit is disabled to ensure a volatile storage behavior.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ClearStatusBitStorageTestFailed(void);
#endif /* (DEM_USE_PERMANENT_STORAGE == STD_ON) && \
          ((DEM_STATUS_BIT_STORAGE_TF == STD_OFF) || \
          (DEM_STATUS_BIT_STORAGE_TF_PER_EVENT_SUPPORT == STD_ON)) */

#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)
/** \brief Function to initialize the permanent memory
 **
 ** \param[in] ResetPermanentNvData contains true/false condition to reset NvM data memory
 **
 ** \Reentrancy{Non Reentrant}
 ** \Synchronicity{Synchronous}
 */
/* !LINKSTO Dem_OBD_0020,1 */
STATIC FUNC(void, DEM_CODE) Dem_PermanentMemoryInit(boolean ResetPermanentNvData);
#endif

#if (DEM_NUM_FFSEGS > 0U)
/** \brief Function to get the index of a freeze frame data segment by the
 ** given DID
 **
 ** \param[in] FFKind  Kind of freeze frame
 ** \param[in] IndividPartFFClass  Class of individual freeze frame part
 ** \param[in] DataId
 ** \param[out] Offset
 **
 ** \return Index of matched element in Dem_FFSegment[] array
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Dem_FFSegIdxType, DEM_CODE) Dem_FindFFSegIdx(
  Dem_FFKindType                                 FFKind,
  P2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) IndividPartFFClass,
  uint16                                         DataId,
  P2VAR(Dem_SizeFFType, AUTOMATIC, AUTOMATIC)    Offset);
#endif /* DEM_NUM_FFSEGS > 0U */

#if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
/** \brief Function to get the entry data pointer of a prestored freeze frame
 **
 ** This is done by searching in the event description array and adding all
 ** several freeze frame class sizes.
 **
 ** ATTENTION: If an event ID where prestorage of freeze frames is disabled
 ** is given, the entry data pointer of the last event where prestorage is
 ** enabled is returned.
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 **
 ** \return Pointer to the prestored freeze frame entry data
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC_P2VAR(Dem_EntryDataType, DEM_VAR_CLEARED, DEM_CODE)
  Dem_GetPFFEntryDataPtr(Dem_EventIdType EventId);
#endif

#if ( (DEM_USE_AGING == STD_ON) && \
      (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD) )
/** \brief Function to update the Aging counter of the given event Id, if an
 ** entry exists
 **
 ** The entry will be deleted, if the aging counter reaches 0(zero).
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 **
 ** \return Result of the Combined DTC status update
 ** \retval TRUE  Combined DTC status was updated
 ** \retval FALSE Combined DTC status was not updated
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 ** \pre This function shall be called from within a critical section
 */
STATIC FUNC(boolean, DEM_CODE) Dem_UpdateAgingCounter(Dem_EventIdType EventId);
#endif

/** \brief This function adds a new or updates an existing event entry
 **        and processes the extended data and the freeze frame,
 **        except of OBD freeze frame.
 **
 ** \param[in] CapturedDataBuf  Source buffer to copy data into
 **                             event memory destination
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in] EventStatus  Status of event. Normally, either
 **              ::DEM_EVENT_STATUS_FAILED or ::DEM_EVENT_STATUS_PASSED, but
 **              if ::DEM_EXTENDED_DATA_CAPTURE is set to
 **              ::DEM_TRIGGER_ON_FDC_THRESHOLD, a status of
 **              ::DEM_EVENT_STATUS_UNCONFIRMED is also possible.
 ** \param[in] Notification collecting information for delayed status notifications
 ** \param[in] TransitionType  conditions triggering this event.
 ** \param[in] EventRelatedDataSize Structure for data start position and size.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ProcessEventEntry(
  Dem_EntryDataPtrType             CapturedDataBuf,
  Dem_EventInfoType                EventInfo,
  Dem_EventStatusType              EventStatus,
  Dem_EventNotificationDataPtrType Notification,
  Dem_StatusTransitionType         TransitionType,
  Dem_ExternalEntryDataBufferManagementType EventRelatedDataSize);

#if ( (DEM_USE_PERMANENT_STORAGE == STD_ON) && \
      (DEM_NUM_DEBOUNCE_COUNTER_PERM > 0U) )
#if (DEM_OPCYC_NVSTORAGE == STD_ON)
/** \brief This Function updates the Debounce Counter Status.
 **
 ** \param[in] DebounceStatusIdx
 ** \param[in] EvId
 ** \param[in] NvDebIdx
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_DebounceProcess(
  Dem_EventIdType                                   DebounceStatusIdx,
  Dem_EventIdType                                   EvId,
  P2VAR(Dem_EvIdLeastType,AUTOMATIC, AUTOMATIC)     NvDebIdx);
#endif /* (DEM_OPCYC_NVSTORAGE == STD_ON) */

/** \brief This Function stores the internal Debounce Counter Status in NvData.
 **
 ** \return none
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_StoreDebounceCounterStatus(void);
#endif /* ( (DEM_USE_PERMANENT_STORAGE == STD_ON) && \
            (DEM_NUM_DEBOUNCE_COUNTER_PERM > 0U) ) */

/** \brief Function to process transient states STARTED/FINISHED "around" the RAM_PROCESSING
 **        state, in order to handle any configured ClearDTCNotifications and checks the
 **        correct conditions to call Dem_ProcessClearDTC()
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ProcessClearDTCNotification(void);

/** \brief This function processes the status and WIR bit update in context
 **        of Dem_ProcessEvent
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in] EventStatus  Status of event. Normally, either
 **              ::DEM_EVENT_STATUS_FAILED or ::DEM_EVENT_STATUS_PASSED, but
 **              if ::DEM_EXTENDED_DATA_CAPTURE is set to
 **              ::DEM_TRIGGER_ON_FDC_THRESHOLD, a status of
 **              ::DEM_EVENT_STATUS_UNCONFIRMED is also possible.
 ** \param[in] FirstFailed if this is the first entry in the queue
 **                        with event failed/confirmed
 ** \param[in] Jobs Jobs mask to be processed by the function
 ** \param[in] Notification Information for delayed status notifications
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ProcessEventStatusUpdate(
  Dem_EventIdType                   EventId,
  Dem_EventStatusType               EventStatus,
  boolean                           FirstFailed,
  Dem_ProcessEventJobMaskType       Jobs,
  Dem_EventNotificationDataPtrType  Notification);

#if (DEM_OPCYCLE_CTRS_SUPPORT == STD_ON)
/** \brief Function to handle the increment of CSLF, CSFF and FAILEDCYCLES counter values for
 **  all events in event memory belonging to the current operation cycle
 **
 ** This function is called by Dem_OpCycleProcessCycleEnd()
 **
 ** \param[in] OperationCycleId  Identification of operation cycle
 **                             (0 <= OpCycleId < DEM_NUM_OPCYCLES)
 **
 ** \Reentrancy{Non reentrant - function shall be called from within a critical section}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_CheckForIncrementOpCycleCounters(
  Dem_OperationCycleIdType OperationCycleId);
#endif /* DEM_OPCYCLE_CTRS_SUPPORT == STD_ON */

#if (DEM_OPCYCLE_CTR_CSLF_SUPPORT == STD_ON)
/** \brief Function to reset the CSLF counter of the given event,
 ** if the UDS status bit TF is transitioning from 0 to 1
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 **
 ** \Reentrancy{Non reentrant - function shall be called from within a critical section}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ResetCycleSinceLastFailed(Dem_EventIdType EventId);
#endif /* DEM_OPCYCLE_CTR_CSLF_SUPPORT == STD_ON */

/** \brief This function provides an event memory entry for the current
 ** entry update. Depending on the type of the current update and the
 ** occupation of the memory, an existing entry, a new entry might or no
 ** entry might be returned.
 ** It is used by Dem_ProcessEventEntry() to retrieve an event memory data
 ** element to store or update an event.
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in] EventStatus  Status of event
 **            (optional for ::DEM_TRIGGER_ON_FDC_THRESHOLD)
 ** \param[out] EvMemEntryPtr  Pointer to the event memory entry to be used
 ** \param[out] EvMemIdxPtr  Entry index of found event memory entry
 ** \param[out] ReplacedEventIdPtr  EventId of the replaced event
 ** \param[out] Notification  Information for delayed status notifications
 ** \param[in] TransitionType  Bit mask holding the applicable status
 **                            bit transitions.
 **
 ** \return Allocation result
 ** \retval DEM_EVENTENTRYALLOC_EXISTS
 ** \retval DEM_EVENTENTRYALLOC_REPLACED
 ** \retval DEM_EVENTENTRYALLOC_ALLOCATED
 ** \retval DEM_EVENTENTRYALLOC_INVALID
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Dem_EventEntryAllocResultType, DEM_CODE)
  Dem_GetEventEntryForUpdate(
    Dem_EventIdType                                          EventId,
    Dem_EventStatusType                                      EventStatus,
    P2VAR(Dem_EventMemoryEntryPtrType, AUTOMATIC, AUTOMATIC) EvMemEntryPtr,
    P2VAR(Dem_SizeEvMemEntryType, AUTOMATIC, AUTOMATIC)      EvMemIdxPtr,
    P2VAR(Dem_EventIdType, AUTOMATIC, AUTOMATIC)             ReplacedEventIdPtr,
    Dem_EventNotificationDataPtrType                         Notification,
    Dem_StatusTransitionType                                 TransitionType);

/** \brief This function tries to find an existing entry in the event memory
 ** or tries to allocate or replace an entry
 **
 ** It is used by Dem_ProcessEventEntry() to retrieve an event memory data
 ** element to store or update an event.
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in] EventStatus  Status of event
 **            (optional for ::DEM_TRIGGER_ON_FDC_THRESHOLD)
 ** \param[out] EvMemEntryPtr  Pointer to the event memory entry to be used
 ** \param[out] EvMemIdxPtr  Entry index of found event memory entry
 ** \param[out] ReplacedEventIdPtr  EventId of the replaced event
 ** \param[out] EventStatusChangedMsgPtr  The message for the status changed
 **                                       callback
 ** \return Allocation result
 ** \retval DEM_EVENTENTRYALLOC_EXISTS
 ** \retval DEM_EVENTENTRYALLOC_REPLACED
 ** \retval DEM_EVENTENTRYALLOC_ALLOCATED
 ** \retval DEM_EVENTENTRYALLOC_INVALID
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Dem_EventEntryAllocResultType, DEM_CODE)
  Dem_FindOrAllocateEventEntry(
    Dem_EventIdType                                          EventId,
    Dem_EventStatusType                                      EventStatus,
    P2VAR(Dem_EventMemoryEntryPtrType, AUTOMATIC, AUTOMATIC) EvMemEntryPtr,
    P2VAR(Dem_SizeEvMemEntryType, AUTOMATIC, AUTOMATIC)      EvMemIdxPtr,
    P2VAR(Dem_EventIdType, AUTOMATIC, AUTOMATIC)             ReplacedEventIdPtr,
    Dem_EventStatusChangedMsgPtrType                         EventStatusChangedMsgPtr);

#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
/** \brief This function tries to notify the satellites
 **
 ** \param[in] SendPreInitReportsToMaster Boolean specifying if Satellites are to be informed
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_InformSatellites(boolean SendPreInitReportsToMaster);
#endif /* (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON) */

/** \brief This function tries to replace an existing event entry with a
 ** new event
 **
 ** It is used by Dem_FindOrAllocateEventEntry() in case it could not find
 ** an empty entry to be allocated.
 **
 ** \param[in]  EventId                   0 < EventId <= DEM_MAX_EVENTID
 ** \param[in]  OriginIdx                 Index specifying the event memory type
 ** \param[out] EvMemEntryPtr             Pointer to the event memory entry to
 **                                       be used
 ** \param[out] EvMemIdxPtr               Pointer to the index of the event
 **                                       memory
 ** \param[out] ReplacedEventIdPtr        EventId of the replaced event
 ** \param[out] EventStatusChangedMsgPtr  The message for the status changed
 **                                       callback
 **
 ** \return Allocation result
 ** \retval DEM_EVENTENTRYALLOC_REPLACED  Event entry successfully replaced
 ** \retval DEM_EVENTENTRYALLOC_INVALID  Unable to replace an event entry
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Dem_EventEntryAllocResultType, DEM_CODE) Dem_ReplaceEventEntry(
  Dem_EventIdType                                          EventId,
  uint8                                                    OriginIdx,
  P2VAR(Dem_EventMemoryEntryPtrType, AUTOMATIC, AUTOMATIC) EvMemEntryPtr,
  P2VAR(Dem_SizeEvMemEntryType, AUTOMATIC, AUTOMATIC)      EvMemIdxPtr,
  P2VAR(Dem_EventIdType, AUTOMATIC, AUTOMATIC)             ReplacedEventIdPtr,
  Dem_EventStatusChangedMsgPtrType                         EventStatusChangedMsgPtr);

#if ((DEM_NUM_CMB_DTCS > 0U) && (DEM_NUM_FAILURECYCLES > 0U) && \
     (DEM_OBDONUDS_COMBINATION_ENABLED == STD_OFF))
/** \brief Initialize all failure counters for the events involved in a combination
 ** with the event that allocated the memory entry.
 **
 ** It is used by Dem_FindOrAllocateEventEntry() in case an entry for the
 ** combined DTC already exists.
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 **
 ** \return void
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_InitFailureCounterOfCmbEvents(
  Dem_EventIdType EventId);

/** \brief Find the index in the CmbEvFailureCycleCounter table for
 ** a combined event based on the EventId.
 */
STATIC FUNC(Dem_CmbDTCEvLnkType, DEM_CODE) Dem_GetFailureCounterIdxOfCmbEvent(
  Dem_EventIdType EventId);
#endif

#if (DEM_NUM_CMB_DTCS > 0U)
/** \brief Recalculates the cmb statuses for the events involved in a combination.
 ** Used in Dem_Init and for start/end of operation cycle.
 ** \param[in]  TriggeredByCycleEnd      If triggered by a cycle end, evaluate
 **                                      a PASSED cycle to reset the combined PDTC bit
 */
STATIC FUNC(void, DEM_CODE) Dem_InitAllCmbDTCStatus(boolean TriggeredByCycleEnd);
#endif

#if (DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON)
/** \brief Restores combined PDTC status from NvRAM.
 */
STATIC FUNC(void, DEM_CODE) Dem_RestoreCmbPDTC(void);
#endif

#if (DEM_NUM_FFSEGS > 0U)
/** \brief Function which processes the freeze frame data of a reported event
 **
 ** It is used by Dem_ProcessEventEntry().
 **
 ** \param[in] CapturedDataBuf  Source buffer to copy data into
 **                             event memory destination
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in] EventStatus  Status of event
 ** \param[in] EvMemEntryPtr  Pointer to event memory entry where to store
 **                           data
 ** \param[in] EventRelatedDataSize Structure for ED and FF start position
 **                                 and size.
 ** \param[out] Notification  Information for delayed status notifications
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ProcessEventEntryFFData(
  Dem_EntryDataPtrType                        CapturedDataBuf,
  Dem_EventIdType                             EventId,
  Dem_EventStatusType                         EventStatus,
  Dem_EventMemoryEntryPtrType                 EvMemEntryPtr,
  Dem_EventNotificationDataPtrType            Notification,
  Dem_ExternalEntryDataBufferManagementType   EventRelatedDataSize);

/** \brief Function to copy a complete freeze frame from
 ** the pre-capture buffer into the event entry.
 **
 ** It shall not be called with invalid reference to a freeze frame class
 **
 ** \param[in] CapturedDataBuf  Source buffer to copy data into
 **                             event memory destination
 ** \param[in] FFKind  Kind of freeze frame
 ** \param[in] IndividPartFFClass  Class of individual freeze frame part
 ** \param[in] FFEntryData  Freeze frame entry data destination
 ** \param[in] EventStatus  Status of event
 **
 ** \return Result of FF storage/update
 ** \retval DEM_EVENTENTRY_UPDATED             FF update was done
 ** \retval DEM_EVENTENTRY_NO_UPDATE_REQUIRED  FF update was not required
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_StoreFF(
  P2VAR(Dem_EntryDataType, AUTOMATIC, AUTOMATIC)      CapturedDataBuf,
  Dem_FFKindType                                      FFKind,
  CONSTP2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) IndividPartFFClass,
  const Dem_EntryDataPtrType                          FFEntryData,
  Dem_EventStatusType                                 EventStatus);

#if ( (DEM_NUM_FFCLS > 0U) && \
      (DEM_NUM_FFSEGS > 0U) )
/** \brief Function to capture a complete freeze frame
 ** into the provided buffer.
 **
 ** It shall not be called within the critical section
 **
 ** \param[in] FFKind  Kind of freeze frame
 ** \param[in] IndividPartFFClass  Class of individual freeze frame part
 ** \param[in] EventId  The Id of the event which triggered the capture of the FreezeFrame
 ** \param[in] EventStatus  Status of event
 ** \param[in] FFDataDestination  Freeze frame entry data destination
 ** \param[in] FFSize  Freeze frame size to be captured
 **
 ** \return Result of FF capture
 ** \retval E_OK                   All data successfully captured or
 **                                no capturing required
 ** \retval DEM_E_NODATAAVAILABLE  At least one external data element
 **                                could not be read
 **
 ** \Reentrancy{Reentrant - if different exclusive destination buffers are provided}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_CaptureFF(
  Dem_FFKindType                                      FFKind,
  CONSTP2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) IndividPartFFClass,
  Dem_EventIdType                                     EventId,
  Dem_EventStatusType                                 EventStatus,
  P2VAR(Dem_EntryDataType, AUTOMATIC, AUTOMATIC)      FFDataDestination,
  P2VAR(Dem_SizeEntryDataType, AUTOMATIC, AUTOMATIC)  FFSize);

/** \brief Function to capture a complete development freeze frame
 **  into the provided buffer.
 **
 ** It shall not be called within the critical section
 **
 ** \param[in] EventId  The Id of the event which triggered the capture of the FreezeFrame
 ** \param[in] FFDataDestination  Freeze frame entry data destination
 ** \param[in] EventRelatedDataSize Size of DevFFA and DevFFB
 **
 ** \return Result of DevFF capture
 ** \retval E_OK                   All data successfully captured or
 **                                no capturing required
 ** \retval DEM_E_NODATAAVAILABLE  At least one external data element
 **                                could not be read
 **
 ** \Reentrancy{Reentrant - if different exclusive destination buffers are provided}
 ** \Synchronicity{Synchronous}
 */
#if (DEM_DEV_FREEZE_FRAME_USED == STD_ON)
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_CaptureDevFFs(
  Dem_EventIdType                                                        EventId,
  P2VAR(Dem_EntryDataType, AUTOMATIC, AUTOMATIC)                         FFDataDestination,
  P2VAR(Dem_ExternalEntryDataBufferManagementType, AUTOMATIC, AUTOMATIC) EventRelatedDataSize);
#endif
#endif

#if (DEM_DEV_FREEZE_FRAME_USED == STD_ON)
/** \brief Function to store a development freeze frames at the specified
 ** position in memory
 **
 ** \param[in] CapturedDataBuf  Source buffer to copy data into
 **                             event memory destination
 ** \param[in] EventId  EventId of DevFFs to be stored
 ** \param[in] EvMemEntryPtr  Pointer to the event memory entry
 **                           to store the DevFFs
 ** \param[in] EventRelatedDataSize Structure for ED and FF
 **                                 start position and size.
 **
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
/* !LINKSTO dsn.Dem.DevFF.IF.StoreDevFFs,1 */
STATIC FUNC(void, DEM_CODE) Dem_StoreDevFFs(
  P2VAR(Dem_EntryDataType, AUTOMATIC, AUTOMATIC)      CapturedDataBuf,
  Dem_EventIdType                                     EventId,
  Dem_EventMemoryEntryPtrType                         EvMemEntryPtr,
  Dem_ExternalEntryDataBufferManagementType EventRelatedDataSize);
#endif
#endif /* (DEM_NUM_FFSEGS > 0U) */

#if ( (DEM_NUM_EDSEGS > 0U) && \
      (DEM_NUM_EXT_DATAELEMENTS > 0U) )
/** \brief Function which processes the extended data of a reported event
 **
 ** It is used by Dem_ProcessEventEntry().
 **
 ** \param[in] CapturedDataBuf  Source buffer to copy data into
 **                             event memory destination
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in] EvMemEntryPtr  Pointer to event memory entry where to store
 **                           data
 ** \param[in] EventEntryAllocResult  Information if event is new or replaced
 ** \param[in] EventRelatedDataSize Structure for data start position and size
 ** \param[out] Notification  Information for delayed status notifications
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ProcessEventEntryEData(
  Dem_EntryDataPtrType                        CapturedDataBuf,
  Dem_EventIdType                             EventId,
  Dem_EventMemoryEntryPtrConstType            EvMemEntryPtr,
  Dem_EventEntryAllocResultType               EventEntryAllocResult,
  Dem_EventNotificationDataPtrType            Notification,
  Dem_ExternalEntryDataBufferManagementType   EventRelatedDataSize);

/** \brief Function to copy he complete extended data from
 ** the pre-capture buffer into the event entry
 **
 ** \param[in] CapturedDataBuf  Source buffer to copy data into
 **                             event memory destination
 ** \param[in] EDEntryData  ED entry data destination
 ** \param[in] EDClass  The class of the ED
 ** \param[in] EntryExists  Information if an entry for the ED exists
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_StoreED(
  P2VAR(Dem_EntryDataType, AUTOMATIC, AUTOMATIC) CapturedDataBuf,
  Dem_EntryDataPtrType                           EDEntryData,
  P2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass,
  boolean                                        EntryExists);

/** \brief Function to capture the complete extended data into the
 ** provided buffer
 **
 ** \param[in] EDataDestination  Source buffer to copy data from heap buffer
 ** \param[in] EntryExists  Information if an entry for the ED exists
 ** \param[in] EventId  Id of the event for which extended data is copied
 **
 ** \param[out] EDSize  Size of extended data copied from heap buffer
 ** \param[out] ReportEDUpdate  Reports extended data update
 **
 ** \return Result of ED capture

 ** \retval E_OK                   All data successfully captured or
 **                                no capturing required
 ** \retval DEM_E_NODATAAVAILABLE  At least one external data element
 **                                could not be read
 **
 ** \Reentrancy{reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_CaptureED(
  Dem_EntryDataPtrType                                   EDataDestination,
  boolean                                                EntryExists,
  Dem_EventIdType                                        EventId,
  P2VAR(Dem_SizeEntryDataType, AUTOMATIC, AUTOMATIC)     EDSize,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC)                   ReportEDUpdate);
#endif /* (DEM_NUM_EDSEGS > 0U) && (DEM_NUM_EXT_DATAELEMENTS > 0U) */

#if (DEM_NUM_OF_PIDS_IN_OBDFF > 0U)
/** \brief Function to capture the OBD freeze frame data
 ** into the provided buffer
 **
 ** \param[in] EventId   Event Id for which data is captured.
 ** \param[out] ObdDataDestination   Destination buffer for captured data.
 ** \param[out] ObdFFSize   OBD FF size to be copied.
 **
 ** \return Result of OBD FF capture
 **
 ** \retval E_OK                   All data successfully captured or
 **                                no capturing required
 ** \retval DEM_E_NODATAAVAILABLE  At least one external data element
 **                                could not be read
 ** \Reentrancy{Reentrant - if different exclusive destination buffers are provided}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_CaptureOBDFreezeFrame(
  Dem_EventIdType                                          EventId,
  P2VAR(Dem_EntryDataType, AUTOMATIC, AUTOMATIC)           ObdDataDestination,
  P2VAR(Dem_SizeEntryDataType, AUTOMATIC, AUTOMATIC)       ObdFFSize);
#endif

/** \brief Internal function to allocate heap buffer for data capturing.
 **
 ** \param[in] ServiceId  Service Id for async call (MainFunction)
 **                       or sync call (SetEventStatus)
 ** \param[out] BufferIdx  Index of the buffer that was allocated
 ** \param[out] BufferStart  Adress of the allocated data buffer
 **
 ** \return Result of heap buffer allocation
 ** \retval TRUE  Buffer allocated
 ** \retval FALSE  Buffer not allocated
 **
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_AllocateCaptureBuffer(
  uint8 ServiceId,
  P2VAR(Dem_CaptureBufferCountType, AUTOMATIC, AUTOMATIC) BufferIdx,
  P2VAR(Dem_EntryDataPtrType, AUTOMATIC, AUTOMATIC) BufferStart);

#if (DEM_MAX_NUM_EVENT_ENTRY_CAPTURE_BUFFER > 0U)
/** \brief Internal function to release heap buffer
 **
 ** \param[in] BufferIdx Index of the buffer that shall be released
 **
 ** \Reentrancy{Non Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_EventMemoryCaptureBufferRelease(
  Dem_CaptureBufferCountType BufferIdx);
#endif

/** \brief Function to search for an empty entry in the given event memory
 **
 ** \param[in] OriginIdx  0 <= OriginIdx < DEM_MAXNUM_ORIGINS
 ** \param[out] FoundEntry Event memory entry of event with given event Id
 ** \param[out] FoundEntryIdx Entry index of founded event memory entry
 **
 ** \return Result of the searching
 ** \retval TRUE  entry was found
 ** \retval FALSE no entry exists
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_SearchForEmptyEntry(
  uint8                                                  OriginIdx,
  P2VAR(Dem_EventMemoryEntryPtrType, AUTOMATIC, DEM_VAR) FoundEntry,
  P2VAR(Dem_SizeEvMemEntryType, AUTOMATIC, AUTOMATIC)    FoundEntryIdx);

#if (DEM_USE_EVENT_DISPLACEMENT == STD_ON)
/** \brief Function to search for a replaceable entry in the event memory by
 ** the given event Id using specific displacement-search-algorithm
 **
 ** \param[in] OriginIdx  0 <= OriginIdx < DEM_MAXNUM_ORIGINS
 ** \param[in] NewEventId  0 < NewEventId <= Dem_MaxEventId
 ** \param[out] FFKind Kind of freeze frame
 ** \param[out] FoundEntry Event memory entry of event with given event Id
 ** \param[out] FoundEntryIdx Entry index of founded event memory entry
 **
 ** \return Result of the searching
 ** \retval TRUE  entry was found
 ** \retval FALSE no entry exists
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_SearchForEntryToReplace(
  uint8                                                    OriginIdx,
  Dem_EventIdType                                          NewEventId,
  Dem_FFKindType                                           FFKind,
  P2VAR(Dem_EventMemoryEntryPtrType, AUTOMATIC, AUTOMATIC) FoundEntry,
  P2VAR(Dem_SizeEvMemEntryType, AUTOMATIC, AUTOMATIC)      FoundEntryIdx);
#endif

/** \brief Function to update the value of the occurrence order of the event,
 ** which is used for processing event displacement
 **
 ** \param[in] UpdatedEvMemEntry
 **
 ** \return Result of the occurrence order update
 ** \retval TRUE  occurrence order was updated
 ** \retval FALSE occurrence order was not updated
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_UpdateOccurrenceOrder(
  Dem_EventMemoryEntryPtrType UpdatedEvMemEntry);

/** \brief Function to re-arrange the occurrence order of events, which is used
 ** while processing event displacement, when the occurrence order threshold is
 ** reached for a memory
 **
 ** \param[in] Origin  0 < Origin < DEM_MAXNUM_ORIGINS
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_RearrangeOccurrenceOrder(uint8 OriginIdx);

/** \brief Function to initialize array used to store the current largest value
 ** of the occurrence order of events, which is used for processing event
 ** displacement
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_InitMaxOccOrder(void);

#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE)
/** \brief This function handles the storage and update of multiple OBD freeze frame
 **
 ** \param[in] CapturedDataBuf  Source buffer to copy data into
 **                             event memory destination
 ** \param[in] EventId  Id of the event which triggered the capture of OBD Freeze Frame
 ** \param[in] EventMemoryEntryIdx  The index of the event memory entry which triggered the
 **                                 capture of OBD Freeze Frame.
 ** \param[in] EventEntryAllocResult  Information if event entry is new, replaced or already
 **                                   existing
 ** \param[in] TransitionType  Conditions triggering the current event entry processing
 ** \param[in] EventRelatedDataSize Structure for data start position and size
 ** \param[out] Notification  Information for delayed status notifications
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ProcessMultipleOBDFreezeFrameEntry(
  Dem_EntryDataPtrType                        CapturedDataBuf,
  Dem_EventIdType                             EventId,
  Dem_SizeEvMemEntryType                      EventMemoryEntryIdx,
  Dem_EventEntryAllocResultType               EventEntryAllocResult,
  Dem_StatusTransitionType                    TransitionType,
  Dem_EventNotificationDataPtrType            Notification,
  Dem_ExternalEntryDataBufferManagementType   EventRelatedDataSize);
#endif

#if ( (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE) && \
      (DEM_NUM_OF_PIDS_IN_OBDFF > 0U) )
/** \brief Function to set the occurrence order of an OBD event entry
 ** \param[in] EventMemoryEntryIdx    Index of the event memory entry
 **                                   for which OBD occurrence order is set
 **
 ** \return Result of the OBD occurrence order update
 ** \retval TRUE  OBD occurrence order was updated
 ** \retval FALSE OBD occurrence order was not updated
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_SetOBDFFOccurrenceOrder(
  Dem_SizeEvMemEntryType EventMemoryEntryIdx);

/** \brief Function to re-arrange the occurrence order of OBD FF
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_RearrangeOBDOccurrenceOrder(void);

#if (DEM_USE_PERMANENT_STORAGE == STD_ON)
/** \brief Init Dem_MaxOBDOccOrder parameter with the highest value saved
 ** for an OBD event entry.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_InitMaxOBDOccOrder(void);
#endif
#endif /* ( (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE)  &&
            (DEM_NUM_OF_PIDS_IN_OBDFF > 0U) ) */

#if ( ((DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF) || \
        (DEM_NUM_FAILURECYCLES == 0U)) && \
      (DEM_OPCYC_OBD_DCY_USED == STD_ON) )
/** \brief This function checks that the confirmed status of an event
 ** assigned to the not qualified Driving Cycle has been reached.
 **
 ** \param[in] EventId     1 < EventId <= DEM_MAX_EVENTID
 **
 ** \return Boolean indicating the failure counter has reached
 **         the failure threshold or not
 ** \retval TRUE  the failure counter reached the threshold
 ** \retval FALSE the failure counter didn't reach the threshold
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_CheckConfirmedDrivingCycle(
  Dem_EventIdType EventId);
#endif

#if (DEM_NUM_FAILURECYCLES > 0U)
#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON)
/** \brief This function sets the ConfirmedDTC bit for all events in event
 ** memory, whose event failure counter has reached its threshold value
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_SetCDTCOnConfirmation(void);
#endif

/** \brief This function resets the event failure counter if the event
 ** is tested and never failed in the operation cycle
 **
 ** \param[in] EventId          1 < EventId <= DEM_MAX_EVENTID
 ** \param[in] OperationCycleId Identification of operation cycle
 **                             (0 <= OpCycleId < DEM_NUM_OPCYCLES)
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ProcessFailureCounterReset(
  Dem_EventIdType          EventId,
  Dem_OperationCycleIdType OperationCycleId);

/** \brief Updates failure counter at the start of failure cycle
 **
 ** \param[in] EventId          1 < EventId <= DEM_MAX_EVENTID
 ** \param[in] OperationCycleId Identification of operation cycle
 **                             (0 <= OpCycleId < DEM_NUM_OPCYCLES)
 **
 ** \pre This function shall be called from within a critical section
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_UpdateFailureCounterCycleStart(
  Dem_EventIdType          EventId,
  Dem_OperationCycleIdType OperationCycleId);
#endif /* (DEM_NUM_FAILURECYCLES > 0U) */

#if (DEM_OBD_CENTRALIZED_PID_REL_DISTANCE_HANDLING == STD_OFF)

#if (DEM_OBD_CENTRALIZED_PID21_HANDLING == STD_OFF)
/** \brief Reset the PID$21 related informations: NrWUCsWhileMILInactive and.
 ** TicksTraveledWhileMILIsActivated
 **
 ** \return none
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ResetDistanceTraveledWhileMILIsActivated(void);
#endif

/** \brief Calculates distance traveled in the last past second.
 **
 ** \return Distance traveled in the last past second expressed.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(uint32, DEM_CODE) Dem_CalculateDeltaDistanceTravel(void);

/** \brief Updates the distance traveled within a second.
 ** It is used for calculating PID$21 and PID$31.
 **
 ** \param[in] DeltaDistanceTraveled
 **
 ** \return none
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_UpdateDistanceRelatedPIDs(
  uint32 DeltaDistanceTraveled);

/** \brief Process distance related PIDs information.
 ** Check if MILPrevStatusOnlyOnOffRelevance must be updated and update the PID21
 ** and PID31 related distances, once every second.
 **
 ** \param[in] none
 ** \param[out] none
 **
 ** \return none
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ProcessDistanceRelatedPIDs(void);
#endif  /* DEM_OBD_CENTRALIZED_PID_REL_DISTANCE_HANDLING == STD_OFF */

#if (DEM_CB_TRIG_ON_EVDAT_ASR403 == STD_ON)
#if ( (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON) && \
      (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON) )
/** \brief Function to check whether one of the given Internal Data Elements is mapped
 ** for the EventId. Second data element was added for obtaining faster processing times
 ** for the case when two data elements are checked. Implementing it for checking only one
 ** data element, and separate call for both of them, is leading to misra warning
 ** for rule 13.5.
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in] FirstDataElementIdx
 ** \param[in] SecondDataElementIdx
 **
 ** \return Result of the check
 ** \retval TRUE  given Internal Data Element is mapped for the EventId
 ** \retval FALSE given Internal Data Element is not mapped for the EventId
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_CheckIntDataElementUsage(
  Dem_EventIdType        EventId,
  Dem_DataElementIdxType FirstDataElementIdx,
  Dem_DataElementIdxType SecondDataElementIdx);

/** \brief Function to call Event data changed callback for all the events in
 ** the event memory for which the event memory overflow indication internal
 ** data element exists
 **
 ** \param[in] OriginIdx  0 <= OriginIdx < DEM_MAXNUM_ORIGINS
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_CbTriggerOnOvfIndSet(uint8 OriginIdx);

#endif /* (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON) && (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON) */
#endif /* (DEM_CB_TRIG_ON_EVDAT_ASR403 == STD_ON) */

#if (DEM_NUM_INDICATOR_LINKS > 0U)
/** \brief Function which processes the indicator cycle counter
 **
 ** \param[in] OperationCycleId  Identification of operation cycle, like power
 **                     cycle, driving cycle,  ... (0 <= OpCycleId < DEM_NUM_OPCYCLES)
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ProcessIndicator(
  Dem_OperationCycleIdType OperationCycleId);

/** \brief Function which processes the healing cycle counter
 **
 ** It is used by Dem_ProcessIndicator().
 **
 ** For the case DEM_TRIGGER_ON_FDC_THRESHOLD, it will only process the
 ** counter role.
 **
 ** \param[in] IndicatorIdx
 ** \param[in] EventId
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ProcessIndicatorOffCriteria(
  Dem_IndicatorIdxType IndicatorIdx,
  Dem_EventIdType      EventId);

/** \brief Function to check the Warning indicator Off-Criteria of the event
 **
 ** It is used by Dem_ProcessIndicatorOffCriteria().
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 **
 ** \return Boolean value indicating whether Warning indicator Off-Criteria is
 **         fulfilled or not.
 ** \retval TRUE   Warning indicator Off-Criteria is fulfilled
 ** \retval FALSE  Warning indicator Off-Criteria is not fulfilled
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 **/
STATIC FUNC(boolean, DEM_CODE) Dem_CheckWIROffCriteriaFulfilled(
  Dem_EventIdType EventId);

#if (DEM_MILGROUP_SUPPORT == STD_ON)
/** \brief Internal function to get the current MIL group counter of the
 ** given MIL group
 **
 ** \param[in] MILGroupIndex  Index of the MIL group
 **
 ** \return Dem_IndicatorCycleCounterType value indicating the highest MIL
 ** indicator counter of the events from the given MIL group which are not
 ** requesting the MIL on
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 **/
STATIC FUNC(Dem_IndicatorCycleCounterType, DEM_CODE)
  Dem_MILGroupGetGroupCounter(Dem_MILGroupIndexType MILGroupIndex);

/** \brief Internal function to identify the event of the given MIL group
 ** that was first reported as failed in the current operation cycle and store
 ** this info in Dem_MILGroupFirstFailedEventId[] array. If no event from the
 ** MIL group was reported as failed, DEM_MILGROUP_EVENT_NONE value is stored.
 **
 ** \param[in] MILGroupIndex  Index of the MIL group
 **
 ** \return none
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 **/
STATIC FUNC(void, DEM_CODE) Dem_MILGroupCalcFirstFailedEventId(
  Dem_MILGroupIndexType MILGroupIndex);

/** \brief Internal function to calculate the first failed event for all MIL
 ** groups during Dem initialization.
 **
 ** \return none
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 **/
STATIC FUNC(void, DEM_CODE) Dem_MILGroupCalcAllFirstFailedEventId(void);

/** \brief Internal function to check if all events of the given MIL group
 ** are tested and only qualified as PASSED in the current operation cycle
 **
 ** \param[in] EventId        The Id of the event tested and qualified as
 **                           passed in the current operation cycle that
 **                           triggers the call of this function
 ** \param[in] MILGroupIndex  Index of the MIL group
 **
 ** \return Boolean value indicating if all enabled events in the group that
 ** still have a MIL indicator were tested in this operation cycle and only
 ** qualified as passed
 ** \retval TRUE   Check criteria is fulfilled
 ** \retval FALSE  Check criteria is not fulfilled
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 **/
STATIC FUNC(boolean, DEM_CODE) Dem_MILGroupCheckPassedCycleAll(
  Dem_EventIdType       EventId,
  Dem_MILGroupIndexType MILGroupIndex);

/** \brief Internal function to identify the event of the given MIL group that
 ** was first qualified as FAILED in the current operation cycle
 **
 ** \param[in] MILGroupIndex    Index of the MIL group
 ** \param[in] EventId          Id of the event tested and qualified as
 **                             failed in the current operation cycle that
 **                             triggers the call of this function
 ** \param[in] ProcessingState  Current processing state of the event
 **
 ** \return The EventId of the first failed event in the MIL group. If
 ** DEM_MILGROUP_EVENT_NONE is returned, no event from the MIL group has been
 ** reported as failed in this operation cycle.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 **/
STATIC FUNC(Dem_EventIdType, DEM_CODE) Dem_MILGroupGetFirstFailedEventId(
  Dem_MILGroupIndexType                 MILGroupIndex,
  Dem_EventIdType                       EventId,
  Dem_MILGroup_EventProcessingStateType ProcessingState);

/** \brief Internal function to process the MIL group counter and the
 ** MIL indicator/event failure counters for MIL group events
 **
 ** \param[in]  EventId                 Id of the event
 ** \param[in]  IndicatorIdx            Index of the indicator. If the function
 **                                     is called with IndicatorIdx set to
 **                                     DEM_NUM_INDICATOR_LINKS, the event
 **                                     failure counter is processed, otherwise
 **                                     the indicator failure cycle counter is
 **                                     processed.
 ** \param[in]  ProcessingState         Current processing state of the event
 ** \param[out] FailureCycleCounterPtr  Pointer to the event/MIL indicator
 **                                     failure counter
 **
 ** \return Boolean value indicating whether the event/indicator failure
 ** counters are handled within MIL group processing
 ** \retval TRUE   The event is assigned to a MIL group and has a MIL indicator
 ** that doesn't request MIL on
 ** \retval FALSE  The event is not assigned to a MIL group or has the MIL
 ** indicator removed from event through calibration or MIL on is requested
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 **/
STATIC FUNC(boolean, DEM_CODE) Dem_MILGroupProcessCounter(
  P2VAR(Dem_IndicatorCycleCounterType, AUTOMATIC, DEM_APPL_DATA)
                                        FailureCycleCounterPtr,
  Dem_EventIdType                       EventId,
  Dem_IndicatorIdxType                  IndicatorIdx,
  Dem_MILGroup_EventProcessingStateType ProcessingState);
#endif /* (DEM_MILGROUP_SUPPORT == STD_ON) */

#if (DEM_OPCYC_OBD_DCY_USED == STD_ON) && ((defined DEM_MIL_ID) && (DEM_NUM_INDICATOR_LINKS > 0U))
/** \brief Function to check if MIL is linked to the given event
 **
 ** \param[in]   EventId       0 < EventId <= DEM_MAX_EVENTID
 ** \param[out]  IndicatorIdx  Index of indicator (only valid, if retval
 **                            is TRUE)
 **
 ** \return Boolean value indicating whether MIL is linked to the event
 ** \retval TRUE   MIL linked to the given event
 ** \retval FALSE  MIL not linked to the given event
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 **/
STATIC FUNC(boolean, DEM_CODE) Dem_IsMILEvent(
  Dem_EventIdType                                   EventId,
  P2VAR(Dem_IndicatorIdxType, AUTOMATIC, AUTOMATIC) IndicatorIdx);
#endif

#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) && \
    (DEM_OPERATION_CYCLE_PROCESSING == DEM_PROCESS_OPCYC_STATE)
/** \brief Function which handles event healing based on OCC2
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **
 ** \pre This function shall be called from within a critical section only.
 */
STATIC FUNC(void, DEM_CODE) Dem_ProcessOCC2BasedHealing(
  Dem_EventIdType EventId);
#endif /* (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) */
#endif /* (DEM_NUM_INDICATOR_LINKS > 0U) */

#if (DEM_NUM_INDICATOR_LINKS > 0U)
#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
/** \brief Updates the WarningIndicatorRequestedSinceLastClear SI30.bit5 bit
 **        for a found entry
 **
 ** \param[in]    EventId        Identification of the Event for which
                                 the WIRSLC status shall be set.
 ** \param[inout] FoundEntry     Event memory entry of event with given
                                 event Id
 ** \param[inout] FoundEntryIdx  Entry index of found event memory entry
 ** \param[inout] EntryFound     An event memory entry has been found
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_SetWIRSLCForFoundEntry(
  P2VAR(Dem_EventMemoryEntryPtrType, AUTOMATIC, AUTOMATIC)   FoundEntry,
  P2VAR(Dem_SizeEvMemEntryType, AUTOMATIC, AUTOMATIC)        FoundEntryIdx,
  P2VAR(Dem_SizeEvMemEntryType, AUTOMATIC, AUTOMATIC)        EntryFound,
  Dem_EventIdType                                            EventId);
#endif /* (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) */
#endif /* (DEM_NUM_INDICATOR_LINKS > 0U) */

#if ((DEM_OPERATION_CYCLE_PROCESSING == DEM_PROCESS_OPCYC_STATE) || \
     (DEM_OPERATION_CYCLE_PROCESSING == DEM_PROCESS_OPCYC_RESTART))
/** \brief Processes actions required at the start of an operation cycle
 **
 ** \param[in] OperationCycleId
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_OpCycleProcessCycleStart(
  Dem_OperationCycleIdType OperationCycleId);

/** \brief Processes actions for an event at the start of an operation cycle
 **
 ** \param[in]    EventId
 **
 ** \pre This function shall be called from within a critical section only.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_OpCycleProcessEventCycleStart(
  Dem_EventIdType EventId);

/** \brief Processes actions required at the end of an operation cycle
 **
 ** \param[in] OperationCycleId
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_OpCycleProcessCycleEnd(
  Dem_OperationCycleIdType OperationCycleId);

/** \brief Processes actions for an event at the end of an operation cycle
 **
 ** \param[in]    EventId
 **
 ** \pre This function shall be called from within a critical section only.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_OpCycleProcessEventCycleEnd(
  Dem_EventIdType EventId);
#endif /* ((DEM_OPERATION_CYCLE_PROCESSING == DEM_PROCESS_OPCYC_STATE) ||
     (DEM_OPERATION_CYCLE_PROCESSING == DEM_PROCESS_OPCYC_RESTART)) */

#if (DEM_MAR_SUPPORT == STD_ON)
/** \brief Internal function to process the Monitor Activity Ratio data
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_MarUpdateMARData(void);
#endif

#if ((DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) && \
     (DEM_VCC_OCC5_USED == STD_ON))
/** \brief Increments the OCC5 counter value for all emission related events currently
 ** residing in the event memory
 **
 ** This function is called by Dem_OpCycleProcessCycleStart() when warm-up cycle (WUC)
 ** is started
 **
 */
STATIC FUNC(void, DEM_CODE) Dem_IncrementAllOcc5(void);
#endif

#if (defined DEM_OPCYC_WARMUP_ID)
/** \brief Increments the counter value for number of OBD warm-up cycles
 **  since all DTCs were cleared.
 **
 ** This function is called by Dem_OpCycleProcessCycleStart() when warm-up cycle (WUC)
 ** is started
 **
 ** \return none
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC (void, DEM_CODE) Dem_IncrementWarmupCtr(void);

#if (DEM_OBD_CENTRALIZED_PID21_HANDLING == STD_OFF)
/** \brief Increments the counter value for number of OBD warm-up cycles
 **  since the MIL was deactivated.
 **
 ** This function is called by Dem_OpCycleProcessCycleStart() when warm-up cycle (WUC)
 ** is started
 **
 ** \return none
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC (void, DEM_CODE) Dem_ProcessWUCWhileMILIsDeactivated(void);
#endif
#endif /* #if (defined DEM_OPCYC_WARMUP_ID) */


#if (DEM_USE_ADVANCED_EVENT_DISPLACEMENT == STD_ON)
/** \brief checks whether an given event is passive according to the advanced
 ** displacement algorithm
 */
STATIC FUNC(boolean, DEM_CODE) Dem_IsEventAdvancedPassive(
  Dem_EventMemoryEntryPtrType EvMemEntry,
  Dem_EventIdType             ReportedEventId);
#endif

#if ((DEM_OBD_EVENT_DISPLACEMENT == STD_ON) && (DEM_USE_EVENT_DISPLACEMENT == STD_ON))
/** \brief Function to check whether a given event matches the condition for
 ** OBD displacement behavior.
 **
 ** It is used by Dem_SearchForEntryToReplace().
 ** This function must be called only for existing event entries with the same
 ** priority as the new reported event.
 **
 ** \param[in] EventId          1 < EventId <= DEM_MAX_EVENTID
 **
 ** \return Result of the check
 ** \retval TRUE  displacing is allowed (OBD condition does not match)
 ** \retval FALSE displacing is not allowed (OBD condition matches)
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_IsDisplaceOBDEventEntryAllowed(
  Dem_EventIdType EventId);
#endif

#if (DEM_DEV_FREEZE_FRAME_USED == STD_ON)
/** \brief This function reads the event Ids of the Development Freeze
 ** Frame A and B Classes stored and restore it to the primary memory.
 **
 ** If a stored Dev Freeze Frame Id exists in the primary memory
 ** the link to the correct Dev Freeze Frame A or/and B is restored
 ** in the primary memory.
 **
 */
STATIC FUNC(void, DEM_CODE) Dem_InitDevFreezeFrameEntryIdx(void);
#endif

#if ((DEM_DEV_ERROR_DETECT == STD_ON) && (DEM_NUM_DEBOUNCE_COUNTER_PERM > 0U))
/** \brief This function shall check if the state of the DEM is PREINITIALIZE
 ** and if the event uses counter-based debouncing with permanent debounce counter storage
 ** enabled.
 **
 ** If the DEM is in PREINITIALIZED state and the event uses counter-based debouncing with
 ** permanent debounce counter storage enabled, return TRUE and report a
 ** DET error.
 **
 ** This function is called by Dem_ResetEventDebounceStatus() and Dem_ReportErrorStatus().
 **
 */
STATIC FUNC(boolean, DEM_CODE) Dem_DebounceCounterWithNvStorageDuringPreInit(Dem_EventIdType EventId);
#endif

#if (DEM_NUM_BSW_EVENTS > 0U)
/** \brief Function to process the status of diagnostic events of BSW
 **
 ** \param[in] EventId  Identification of an Event by assigned Event ID.
 **                     The Event ID is configured in the Dem.
 ** \param[in] EventStatus  Monitor test result
 ** \param[in] QueuedInPreinitPhase  Information from which phase the request is
 **
 ** \ServiceID{::DEM_SID_ReportErrorStatus}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Asynchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ReportErrorStatusCore(
  Dem_EventIdType     EventId,
  Dem_EventStatusType EventStatus,
  boolean             QueuedInPreinitPhase);
#endif

/** \brief Function to translate event's TFTOC value in the error queue
 **        to the value for Dem_StatusTransitionType
 **
 ** \param[in] QueueEntry current queue element
 ** \return Init value for event TFTOC transition
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Dem_StatusTransitionType, DEM_CODE) Dem_ErrorQueueGetEventTFTOCTransitionBit(
  Dem_ErrorQueueElementType QueueEntry);

#if ((DEM_OPCYC_OBD_DCY_USED == STD_ON) && \
    ( (!((DEM_NUM_FAILURECYCLES > 0U) && (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON))) || \
      ((DEM_NUM_INDICATOR_LINKS > 0U) && (defined DEM_MIL_ID)) ) )
/** \brief Function to check/set the CDTC and/or MIL for events of the driving cycle.
 **
 ** \param[in] EventId  Identification of an Event by assigned Event ID.
 **                     The Event ID is configured in the Dem.
 ** \param[out] StatusChanged  Indicates if the event status was changed.
 ** \return boolean  Indicator if event entry was changed
 ** \retval TRUE   Event entry was updated
 ** \retval FALSE  Event entry was not updated
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
STATIC FUNC(boolean, DEM_CODE)Dem_ProcessDCYQualificationPerEvent(
  Dem_EventIdType EventId,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC) StatusChanged);
#endif

/** \brief Internal function to get Extended record for an event
 **
 ** This function shall be used to read all or specific Extended Data record
 ** for an Event and store the data and the size in its given output buffer
 **
 ** \param[in] EventId      Identification of an event by assigned EventId
    \param[in] RecordNumber  Identification of requested Extended data record
                            Valid values are between 0x01 and 0xEF as defined
                            in ISO14229-1
    \param[in] ResultInit   Parameter contains the initial result value of the API
 ** \param[out] DestBuffer  Pointer that points to the buffer, to
                            which the extended data shall be written to
 ** \param[in,out] BufSize  Parameter contains the maximum number of data bytes
                            that can be written to the buffer. The function
                            returns the actual number of written data bytes
                            in this parameter
 **
 ** \return Function execution success status
 ** \retval E_OK                 Operation successful
 ** \retval E_NOT_OK             Operation could not be performed
 ** \retval DEM_NO_SUCH_ELEMENT: The requested event data is not currently stored
                                (but the request was valid) OR the requested
                                record number is not supported by the event
 ** \retval DEM_BUFFER_TOO_SMALL: The provided buffer size is too small
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_InternalGetEventExtendedDataRecord(
  Dem_EventIdType                         EventId,
  uint8                                   RecordNumber,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) BufSize,
  Std_ReturnType                          ResultInit);

/** \brief Internal function to get Freeze Frame record for an event
 **
 ** This function shall be used to read all or specific Freeze frame record
 ** for an Event and store the data and the size in its given output buffer.
 **
 ** \param[in]  EventId     Identification of an event by assigned EventId
    \param[in]  RecordNumber  Identification of a freeze frame record as
                            defined in ISO14229-1. 0xFF means most recent
                            freeze frame record is returned. 0x00 is only
                            supported if the Dem module supports WWH-OBD
                            (refer to DemOBDSupport)
    \param[in]  DataId      Parameter specifies the DID (ISO14229-1) that shall
                            be copied to the destination buffer
    \param[in]  ResultInit  Parameter contains the initial result value of the API
 ** \param[out] DestBuffer  Pointer that points to the buffer, to which the
                            freeze frame data record shall be written to
 ** \param[in,out] BufSize  Parameter contains the maximum number of data bytes
                            that can be written to the buffer. The function
                            returns the actual number of written data bytes
                            in this parameter
 **
 ** \return Function execution success status
 ** \retval E_OK                 Operation successful
 ** \retval E_NOT_OK             Operation could not be performed
 ** \retval DEM_NO_SUCH_ELEMENT: The requested event data is not currently
                                 stored(but the request was valid)
                                 OR The requested record number is not
                                 supported by the event OR The requested DID
                                 is not supported by the freeze frame
 ** \retval DEM_BUFFER_TOO_SMALL: The provided buffer size is too small
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_InternalGetEventFreezeFrameData(
  Dem_EventIdType                         EventId,
  uint8                                   RecordNumber,
  boolean                                 ReportTotalRecord,
  uint16                                  DataId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) BufSize,
  Std_ReturnType                          ResultInit);

#if (DEM_NUM_EXT_DATAELEMENTS > 0U)
  /** \brief Internal function to read external data elements of data type uint8
 **
 ** This function shall be used to read external data elements of data type uint8
 ** via the Client server or sender reciever interfaces and store the value in
 ** the destination buffer.
 **
 ** \param[in]     DataElementIndex Index of the external data element in the
 **                                 internal structure
 ** \param[in]     EventId          The Id of the event which triggered the capture
 **                                 of the Event Related Data
 ** \param[out]    DestBuffer       Buffer where the data read from the DataElement
 **                                 shall be written
 **
 ** \return Result of reading the data element
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_ReadExtDataElementUint8(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC)                 DestBuffer,
  Dem_DataElementIdxType                             DataElementIndex,
  Dem_EventIdType                                    EventId);

#if (DEM_INCLUDE_RTE == STD_ON)
/** \brief Internal function to read external data elements of data type uint16
 **
 ** This function shall be used to read external data elements of data type uint16
 ** via the Client server or sender reciever interfaces and store the value in
 ** the destination buffer.
 **
 ** \param[in]     DataElementIndex Index of the external data element in the
 **                                 internal structure
 ** \param[in]     EventId          The Id of the event which triggered the capture
 **                                 of the Event Related Data
 ** \param[out]    DestBuffer       Buffer where the data read from the DataElement
 **                                 shall be written
 **
 ** \return Result of reading the data element
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_ReadExtDataElementUint16(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC)                 DestBuffer,
  Dem_DataElementIdxType                             DataElementIndex,
  Dem_EventIdType                                    EventId);

  /** \brief Internal function to read external data elements of data type uint32
 **
 ** This function shall be used to read external data elements of data type uint32
 ** via the Client server or sender reciever interfaces and store the value in
 ** the destination buffer.
 **
 ** \param[in]     DataElementIndex Index of the external data element in the
 **                                 internal structure
 ** \param[in]     EventId          The Id of the event which triggered the capture
 **                                 of the Event Related Data
 ** \param[out]    DestBuffer       Buffer where the data read from the DataElement
 **                                 shall be written
 **
 ** \return Result of reading the data element
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_ReadExtDataElementUint32(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC)                 DestBuffer,
  Dem_DataElementIdxType                             DataElementIndex,
  Dem_EventIdType                                    EventId);
#endif /* #if (DEM_INCLUDE_RTE == STD_ON) */

#if (DEM_DEFAULT_ASR_SERVICE_API == DEM_SERVICE_API_ASR2011)
/** \brief Internal function to read external data elements of data type sint8
 **
 ** This function shall be used to read external data elements of data type sint8
 ** via the Client server or sender reciever interfaces and store the value in
 ** the destination buffer.
 **
 ** \param[in]     DataElementIndex Index of the external data element in the
 **                                 internal structure
 ** \param[in]     EventId          The Id of the event which triggered the capture
 **                                 of the Event Related Data
 ** \param[out]    DestBuffer       Buffer where the data read from the DataElement
 **                                 shall be written
 **
 ** \return Result of reading the data element
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_ReadExtDataElementSint8(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC)                 DestBuffer,
  Dem_DataElementIdxType                             DataElementIndex,
  Dem_EventIdType                                    EventId);

/** \brief Internal function to read external data elements of data type sint16
 **
 ** This function shall be used to read external data elements of data type sint16
 ** via the Client server or sender reciever interfaces and store the value in
 ** the destination buffer.
 **
 ** \param[in]     DataElementIndex Index of the external data element in the
 **                                 internal structure
 ** \param[in]     EventId          The Id of the event which triggered the capture
 **                                 of the Event Related Data
 ** \param[out]    DestBuffer       Buffer where the data read from the DataElement
 **                                 shall be written
 **
 ** \return Result of reading the data element
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_ReadExtDataElementSint16(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC)                 DestBuffer,
  Dem_DataElementIdxType                             DataElementIndex,
  Dem_EventIdType                                    EventId);

/** \brief Internal function to read external data elements of data type sint32
 **
 ** This function shall be used to read external data elements of data type sint32
 ** via the Client server or sender reciever interfaces and store the value in
 ** the destination buffer.
 **
 ** \param[in]     DataElementIndex Index of the external data element in the
 **                                 internal structure
 ** \param[in]     EventId          The Id of the event which triggered the capture
 **                                 of the Event Related Data
 ** \param[out]    DestBuffer       Buffer where the data read from the DataElement
 **                                 shall be written
 **
 ** \return Result of reading the data element
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_ReadExtDataElementSint32(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC)                 DestBuffer,
  Dem_DataElementIdxType                             DataElementIndex,
  Dem_EventIdType                                    EventId);

/** \brief Internal function to read external data elements of data type float32
 **
 ** This function shall be used to read external data elements of data type float32
 ** via the Client server or sender reciever interfaces and store the value in
 ** the destination buffer.
 **
 ** \param[in]     DataElementIndex Index of the external data element in the
 **                                 internal structure
 ** \param[in]     EventId          The Id of the event which triggered the capture
 **                                 of the Event Related Data
 ** \param[out]    DestBuffer       Buffer where the data read from the DataElement
 **                                 shall be written
 **
 ** \return Result of reading the data element
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_ReadExtDataElementFloat32(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC)                 DestBuffer,
  Dem_DataElementIdxType                             DataElementIndex,
  Dem_EventIdType                                    EventId);
#endif /* #if (DEM_DEFAULT_ASR_SERVICE_API == DEM_SERVICE_API_ASR2011) */
#endif /* #if (DEM_NUM_EXT_DATAELEMENTS > 0U) */

#if ( (DEM_INCLUDE_RTE == STD_OFF) || (DEM_NUM_SWC_EVENTS > 0) )
#if (DEM_INTERNAL_DEBOUNCE_SUPPORT == STD_ON)
/** \brief Internal function for applying the debounce status to the given event
 **
 ** \param[in] EventId
 ** \param[in] DebounceStatus
 **
 ** \return none
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ApplyDebounceStatus(
  Dem_EventIdType             EventId,
  Dem_DebounceResetStatusType DebounceStatus);
#endif
#endif

/** \brief Internal function to capture event related data
 **  (freeze frames, extended data) from external sources into a heap buffer.
 ** This extra capturing step is needed because external data must not be
 ** read within critical sections, but the update of the event related data
 ** must be protected by a critical section.
 **
 ** \param[in] ServiceId  Service Id for async call (MainFunction)
 **                       or sync call (SetEventStatus)
 ** \param[in] EventId  The Id of the event which triggered the
 **                     capture of external data
 ** \param[in] EventStatus  Status of event
 ** \param[in] BufferStart Adress of provided data buffer
 ** \param[in] EventRelatedDataSize Structure for data
                                    start position and size
 **
 ** \param[out] ReportEDUpdate  Reports extended data update
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ProcessEventPreCapture(
  uint8 ServiceId,
  Dem_EventIdType EventId,
  Dem_EventStatusType EventStatus,
  Dem_EntryDataPtrType BufferStart,
  Dem_ExternalEntryDataBufferManagementType *EventRelatedDataSize,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC) ReportEDUpdate);

#if (DEM_MAX_NUM_EVENT_ENTRY_CAPTURE_BUFFER > 0U)
/** \brief Internal function to allocate heap buffer for data capturing.
 ** This function must be called from a critical section.
 **
 ** \param[out] BufferIdx  Index of the buffer that was allocated
 ** \param[out] BufferStart  Adress of the allocated data buffer
 **
 ** \return Result of heap buffer allocation
 ** \retval TRUE  Buffer allocated
 ** \retval FALSE  Buffer not allocated
 **
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_EventMemoryCaptureBufferGet(
  P2VAR(Dem_CaptureBufferCountType, AUTOMATIC, AUTOMATIC) BufferIdx,
  P2VAR(Dem_EntryDataPtrType, AUTOMATIC, AUTOMATIC) BufferStart);
#endif

#if (DEM_EVENT_CONFIRMATION_THRESHOLD_COUNTER_ADAPTABLE == STD_ON)
/** \brief Function to initialize the adaptable confirmation threshold for each event
 **
 ** This function initializes the RAM array Dem_ConfirmationThresholdRuntime[]
 ** with the configured values from DemEventFailureCycleCounterThreshold.
 ** It needs to be called during Dem_PreInit().
 ** The data in Dem_ConfirmationThresholdRuntime[] can be adapted during
 ** runtime via the API Dem_SetEventConfirmationThresholdCounter().
 **
 ** Note: An initialization of this data by compile-time is not possible,
 **       because the underlying DemEventFailureCycleCounterThreshold
 **       is calibtratable and can be changed after compilation.
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_InitEventConfirmationThresholdCounter(void);
#endif

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*==================[internal data]=========================================*/

#define DEM_START_SEC_VAR_INIT_8
#include <Dem_MemMap.h>

/*------------------[variables for fault confirmation]----------------------*/
#if ( (DEM_NUM_FAILURECYCLES > 0U) && \
      (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON) )
/** \brief Triggers the asynchronous processing of fault confirmation */
VAR(boolean, DEM_VAR) Dem_DoProcessFaultConfirmation = FALSE;
#endif

/*------------------[variables for OBD variant selection]-------------------*/
#if (DEM_OBD_VARIANT_SELECTABLE == STD_ON)
/** \brief Holds the active OBD variant */
VAR(uint8, DEM_VAR) Dem_ActiveOBDVariant = DEM_OBD_VARIANT_NONE;
#endif

#define DEM_STOP_SEC_VAR_INIT_8
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_CLEARED_8
#include <Dem_MemMap.h>

#if (DEM_NUM_CMB_DTCS > 0U)
/** \brief holds the combined DTCStatus of all combined events per DTC */
VAR(Dem_EventStatusExtendedType, DEM_VAR_CLEARED)
  Dem_CmbDTCStatus[DEM_NUM_CMB_DTCS];

/** \brief holds the changed status flag for every Combined DTC */
STATIC VAR(uint8, DEM_VAR_CLEARED) Dem_CmbDTCFlags[DEM_NUM_CMB_DTCS_BYTES];
#endif

/*------------------[variables for user controlled WIR bit]-----------------*/
#if (DEM_USER_CTRL_WIR_SUPPORT == STD_ON)
/* !LINKSTO Dem.UserCtrlWIR_Implicit1,1 */
/** \brief Bit array which holds the requested user controlled WIR bit status for all events
 ** (with one bit per event and EventId as index) */
VAR(uint8, DEM_VAR) Dem_UserCtrlWIRStatus[DEM_USER_CTRL_WIR_STATUS_SIZE];
#endif

/*--------------------------------------------------------------------------*/

/** \brief Index of first entry in queue to read */
STATIC VAR(Dem_ErrorQueueIdxType, DEM_VAR_CLEARED) Dem_ErrorQueueReadIdx;

/** \brief Index of next entry in queue to write */
STATIC VAR(Dem_ErrorQueueIdxType, DEM_VAR_CLEARED) Dem_ErrorQueueWriteIdx;

#if (DEM_SIZE_PFF_ENTRY_DATA != 0U)
/** \brief Entry area for possible prestored freeze frames */
STATIC VAR(Dem_EntryDataType, DEM_VAR_CLEARED)
  Dem_PFFEntryDataArea[DEM_SIZE_PFF_ENTRY_DATA];
#endif

#if (DEM_MILGROUP_SUPPORT == STD_ON)
/*------------------[variables for MIL groups]------------------------------*/

/** \brief Array used to store the MIL groups failure counters */
STATIC VAR(Dem_FailureCycleCounterType, DEM_VAR_CLEARED)
  Dem_MILGroupLastCalculatedCounter[DEM_MILGROUP_NUM_GROUP];
#endif

#define DEM_STOP_SEC_VAR_CLEARED_8
#include <Dem_MemMap.h>

#define DEM_START_SEC_VAR_CLEARED_16
#include <Dem_MemMap.h>

#if (DEM_MILGROUP_SUPPORT == STD_ON)
/** \brief Array used to store the first failed event of the MIL group
 ** in the current operation cycle */
STATIC VAR(Dem_EventIdType, DEM_VAR_CLEARED)
  Dem_MILGroupFirstFailedEventId[DEM_MILGROUP_NUM_GROUP];

/*--------------------------------------------------------------------------*/
#endif

#if ( (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE) && \
      (DEM_NUM_OF_PIDS_IN_OBDFF > 0U) )
/** \brief Variable used to store the highest occurrence order of primary events
 ** providing an indication of first entry creation time.
 ** The oldest event is represented by the lower value. */
STATIC VAR(Dem_OccOrderType, DEM_VAR_CLEARED) Dem_MaxOBDOccOrder;
#endif

/** \brief Array which stores the value of current largest occurrence order
 ** of the events for each event memory
 */
STATIC VAR(Dem_OccOrderType, DEM_VAR_CLEARED)
  Dem_MaxOccOrder[DEM_MAXNUM_ORIGINS];

#if (DEM_OBD_CENTRALIZED_PID_REL_DISTANCE_HANDLING == STD_OFF)
/** \brief Variable which stores the old value for the distance traveled
 ** since engine start. Needed for calculation of PID31 and PID21
 */
STATIC VAR(uint16, DEM_VAR_CLEARED) Dem_LastTimeSinceEngineStart;

/** \brief Prescaler for PID$31 calculation. The algorithm for calculating the distance
 ** is executed once per second to reduce the load for Rte calls in Dem_MainFunction()
 */
STATIC VAR(uint16, DEM_VAR_CLEARED) Dem_MainFunctionOneSecondCounter;
#endif

#define DEM_STOP_SEC_VAR_CLEARED_16
#include <Dem_MemMap.h>

#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U)
#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 255U)
#define DEM_START_SEC_VAR_CLEARED_16
#include <Dem_MemMap.h>
#else
#define DEM_START_SEC_VAR_CLEARED_8
#include <Dem_MemMap.h>
#endif

/** \brief Queue holding the errors appeared before Dem_Init(), or to be
 ** entered or updated in event memory after Dem_Init()
 */
STATIC VAR(Dem_RootErrorQueueEntryType, DEM_VAR_CLEARED) Dem_RootErrorQueue[DEM_ROOT_ERROR_BUFFER_SIZE];

#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 255U)
#define DEM_STOP_SEC_VAR_CLEARED_16
#include <Dem_MemMap.h>
#else
#define DEM_STOP_SEC_VAR_CLEARED_8
#include <Dem_MemMap.h>
#endif
#endif

/*------[variables for event memory when Immediate storage is enabled]------*/

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
#define DEM_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
#include <Dem_MemMap.h>

/** \brief Primary event memory */
STATIC VAR(Dem_EventMemoryEntryType, DEM_VAR_CLEARED)
  Dem_EventMemoryPrimary[DEM_MAX_NUMBER_EVENT_ENTRY_PRI];

#if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR != 0U)
/* !LINKSTO Dem.ASR40.SWS_Dem_00162_Implicit1,1 */
/** \brief Mirror event memory */
STATIC VAR(Dem_EventMemoryEntryType, DEM_VAR_CLEARED)
  Dem_EventMemoryMirror[DEM_MAX_NUMBER_EVENT_ENTRY_MIR];
#endif

#if (DEM_MAX_NUMBER_EVENT_ENTRY_SEC != 0U)
/* !LINKSTO Dem.ASR40.SWS_Dem_00162_Implicit1,1 */
/** \brief Secondary event memory */
STATIC VAR(Dem_EventMemoryEntryType, DEM_VAR_CLEARED)
  Dem_EventMemorySecondary[DEM_MAX_NUMBER_EVENT_ENTRY_SEC];
#endif

#define DEM_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
#include <Dem_MemMap.h>

#define DEM_START_SEC_VAR_SAVED_ZONE_8
#include <Dem_MemMap.h>

#if (DEM_SIZE_ENTRY_DATA_PRIMARY != 0U)
/** \brief Primary entry data area */
STATIC VAR(Dem_EntryDataType, DEM_VAR_CLEARED) Dem_EntryDataPrimary[
  DEM_SIZE_ENTRY_DATA_PRIMARY];
#endif

#if (DEM_SIZE_ENTRY_DATA_MIRROR != 0U)
/** \brief Mirror entry data area */
STATIC VAR(Dem_EntryDataType, DEM_VAR_CLEARED) Dem_EntryDataMirror[
  DEM_SIZE_ENTRY_DATA_MIRROR];
#endif

#if (DEM_SIZE_ENTRY_DATA_SECONDARY != 0U)
/** \brief Secondary entry data area */
STATIC VAR(Dem_EntryDataType, DEM_VAR_CLEARED) Dem_EntryDataSecondary[
  DEM_SIZE_ENTRY_DATA_SECONDARY];
#endif

#define DEM_STOP_SEC_VAR_SAVED_ZONE_8
#include <Dem_MemMap.h>

#define DEM_START_SEC_VAR_SAVED_ZONE_16
#include <Dem_MemMap.h>

#if (DEM_SIZE_ENTRY_DATA_PRIMARY != 0U)
/** \brief Primary entry data free position */
STATIC VAR(Dem_SizeEntryDataType, DEM_VAR_CLEARED) Dem_EntryDataFreePosPrimary;
#endif

#if (DEM_SIZE_ENTRY_DATA_MIRROR != 0U)
/** \brief Mirror entry data free position */
STATIC VAR(Dem_SizeEntryDataType, DEM_VAR_CLEARED) Dem_EntryDataFreePosMirror;
#endif

#if (DEM_SIZE_ENTRY_DATA_SECONDARY != 0U)
/** \brief Secondary entry data free position */
STATIC VAR(Dem_SizeEntryDataType, DEM_VAR_CLEARED) Dem_EntryDataFreePosSecondary;
#endif

#define DEM_STOP_SEC_VAR_SAVED_ZONE_16
#include <Dem_MemMap.h>
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */

/*----------------[variables of Storage Order Id Generator
 *                when Intermediate storage is enabled]---------------------*/

#if (DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON)
#define DEM_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
#include <Dem_MemMap.h>

/** \brief state of the StorageOrderId generator. */
STATIC VAR(Dem_StorageOrderIdGeneratorStateType, DEM_VAR_CLEARED)
  Dem_StorageOrderIdGeneratorState;

#define DEM_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
#include <Dem_MemMap.h>
#endif /* DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON */

/*--------------[capture buffers for external data elements]----------------*/
#define DEM_START_SEC_VAR_CLEARED_8
#include <Dem_MemMap.h>

#if (DEM_SIZE_EXTERNAL_ENTRY_DATA > 0U)
/** \brief Buffer to capture external event entry data in Dem_MainFunction() */
STATIC VAR(Dem_EntryDataType, DEM_VAR_CLEARED)
  Dem_ExternalEntryDataBuffer[DEM_SIZE_EXTERNAL_ENTRY_DATA];
#endif

#define DEM_STOP_SEC_VAR_CLEARED_8
#include <Dem_MemMap.h>

#define DEM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dem_MemMap.h>

#if (DEM_MAX_NUM_EVENT_ENTRY_CAPTURE_BUFFER > 0U)
/** \brief Pool of buffers to capture external event entry data during
 ** synchronous event processing */
STATIC VAR(Dem_ExternalEntryDataBufferPoolType, DEM_VAR_CLEARED)
  Dem_ExternalEntryDataBufferPool[DEM_MAX_NUM_EVENT_ENTRY_CAPTURE_BUFFER];
#endif

#define DEM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dem_MemMap.h>

/*==================[external data]=========================================*/

#define DEM_START_SEC_VAR_CLEARED_16
#include <Dem_MemMap.h>

/** \brief Queue holding the errors appeared before Dem_Init(), or to be
 ** entered or updated in event memory after Dem_Init()
 */
VAR(Dem_ErrorQueueEntryType, DEM_VAR_CLEARED) Dem_ErrorQueue[
  DEM_BSW_ERROR_BUFFER_SIZE];

#define DEM_STOP_SEC_VAR_CLEARED_16
#include <Dem_MemMap.h>

#define DEM_START_SEC_VAR_CLEARED_8
#include <Dem_MemMap.h>

/** \brief NvM write operation (and related gate entry) status per event
 ** memory */
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
VAR(Dem_NvMGateEntryInfoType, DEM_VAR_CLEARED) Dem_NvMGateEntryInfo[DEM_MAXNUM_ORIGINS];
#endif

/** \brief Queue to store the extended part of the error queue entry
 */
#if (DEM_ERROR_QUEUE_EXTENDED == STD_ON)
VAR(Dem_ErrorQueueEntryExtType, DEM_VAR_CLEARED) Dem_ErrorQueueExt[DEM_BSW_ERROR_BUFFER_SIZE];
#endif

/** \brief Array to store ClearDTC process results per requesting client */
VAR(Std_ReturnType, DEM_VAR_CLEARED) Dem_ClearDTCResult
  [DEM_NUMBER_OF_CLIENTS + DEM_NUMBER_OF_VIRTUAL_CLIENTS];

#if ( (DEM_OBDONUDS_SUPPORT) && \
      (DEM_READINESS_CALIBRATION_SUPPORT == STD_ON) )
/** \brief Bit-field array that holds the flags indicating whether an EventId is
 ** assigned or not to a Readiness Group other than DEM_OBD_RDY_NONE, when
 ** calibration is enabled */
VAR(uint8, DEM_VAR_CLEARED) Dem_RGEvents[DEM_RG_EVENTS_ARRAY_SIZE];
#endif

#if (DEM_CALIBRATION_SUPPORT == STD_ON)
/** \brief DTC severity availability mask derived from DTC severity and
 ** WWH-OBD DTC class, when calibration is enabled */
VAR(uint8, DEM_VAR_CLEARED) Dem_SeverityAvailabilityMask;

/** \brief Indicates whether Dem_SeverityAvailabilityMask was updated
 ** after Dem restart */
VAR(boolean, DEM_VAR_CLEARED) Dem_IsSeverityMaskUpdated;
#endif

#define DEM_STOP_SEC_VAR_CLEARED_8
#include <Dem_MemMap.h>

#define DEM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dem_MemMap.h>

/** \brief Status of an asynchronous ClearDTC operation */
VAR(Dem_ClearDtcAsyncStatusType, DEM_VAR_CLEARED) Dem_ClearDtcAsyncStatus;

/*------------------[variables for gate-entry]------------------------------*/

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)

/* non-volatile primary data of the Dem */
VAR(Dem_NvGateEntryPrimaryDataType, DEM_VAR_CLEARED)
  Dem_NvGateEntryPrimaryData;

#if (DEM_MAX_NUMBER_EVENT_ENTRY_SEC != 0U)
/* non-volatile secondary data of the Dem */
VAR(Dem_NvGateEntrySecondaryDataType, DEM_VAR_CLEARED)
  Dem_NvGateEntrySecondaryData;
#endif

#if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR != 0U)
/* non-volatile mirror data of the Dem */
VAR(Dem_NvGateEntryMirrorDataType, DEM_VAR_CLEARED)
  Dem_NvGateEntryMirrorData;
#endif

#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */

#define DEM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dem_MemMap.h>

#define DEM_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
#include <Dem_MemMap.h>

/** \brief Non-volatile data of the Dem - Native */
VAR(Dem_NvDataType, DEM_VAR_CLEARED) Dem_NvData;

#define DEM_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
#include <Dem_MemMap.h>

/*==================[external constants]====================================*/

/*------------------[Dem_EventMem array]------------------------------------*/

#define DEM_START_SEC_CONST_UNSPECIFIED
#include <Dem_MemMap.h>

/** \brief Pointers to the event memories */
CONSTP2VAR(Dem_EventMemoryEntryType, DEM_CONST, DEM_VAR_CLEARED)
  Dem_EventMem[DEM_MAXNUM_ORIGINS] =
{
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
  Dem_EventMemoryPrimary,
#if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR != 0U)
  Dem_EventMemoryMirror,
#else
  NULL_PTR,
#endif
  NULL_PTR,
#if (DEM_MAX_NUMBER_EVENT_ENTRY_SEC != 0U)
  Dem_EventMemorySecondary
#else
  NULL_PTR
#endif
#else /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_OFF */
  Dem_NvData.EventMemoryPrimary,
#if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR != 0U)
  Dem_NvData.EventMemoryMirror,
#else
  NULL_PTR,
#endif
  NULL_PTR,
#if (DEM_MAX_NUMBER_EVENT_ENTRY_SEC != 0U)
  Dem_NvData.EventMemorySecondary
#else
  NULL_PTR
#endif
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */
};

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include <Dem_MemMap.h>

/*---------------------------[Dem_EntryData array]--------------------------*/

#define DEM_START_SEC_CONST_UNSPECIFIED
#include <Dem_MemMap.h>

/** \brief Pointers to the event memory entry data */
CONSTP2VAR(Dem_EntryDataType, DEM_CONST, DEM_VAR_CLEARED)
  Dem_EntryData[DEM_MAXNUM_ORIGINS] =
{
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
#if (DEM_SIZE_ENTRY_DATA_PRIMARY != 0U)
  Dem_EntryDataPrimary,
#else
  NULL_PTR,
#endif
#if (DEM_SIZE_ENTRY_DATA_MIRROR != 0U)
  Dem_EntryDataMirror,
#else
  NULL_PTR,
#endif
  NULL_PTR,
#if (DEM_SIZE_ENTRY_DATA_SECONDARY != 0U)
  Dem_EntryDataSecondary
#else
  NULL_PTR
#endif
#else /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_OFF */
#if (DEM_SIZE_ENTRY_DATA_PRIMARY != 0U)
  Dem_NvData.EntryDataPrimary,
#else
  NULL_PTR,
#endif
#if (DEM_SIZE_ENTRY_DATA_MIRROR != 0U)
  Dem_NvData.EntryDataMirror,
#else
  NULL_PTR,
#endif
  NULL_PTR,
#if (DEM_SIZE_ENTRY_DATA_SECONDARY != 0U)
  Dem_NvData.EntryDataSecondary
#else
  NULL_PTR
#endif
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */
};

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include <Dem_MemMap.h>

/*------------------[Dem_EntryDataFreePos array]----------------------------*/

#define DEM_START_SEC_CONST_UNSPECIFIED
#include <Dem_MemMap.h>

/** \brief Pointers to the event memory entry free position data */
CONSTP2VAR(Dem_SizeEntryDataType, DEM_CONST, DEM_VAR_CLEARED)
  Dem_EntryDataFreePos[DEM_MAXNUM_ORIGINS] =
{
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
#if (DEM_SIZE_ENTRY_DATA_PRIMARY != 0U)
  &Dem_EntryDataFreePosPrimary,
#else
  NULL_PTR,
#endif
#if (DEM_SIZE_ENTRY_DATA_MIRROR != 0U)
  &Dem_EntryDataFreePosMirror,
#else
  NULL_PTR,
#endif
  NULL_PTR,
#if (DEM_SIZE_ENTRY_DATA_SECONDARY != 0U)
  &Dem_EntryDataFreePosSecondary
#else
  NULL_PTR
#endif
#else /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_OFF */
#if (DEM_SIZE_ENTRY_DATA_PRIMARY != 0U)
  &Dem_NvData.EntryDataFreePosPrimary,
#else
  NULL_PTR,
#endif
#if (DEM_SIZE_ENTRY_DATA_MIRROR != 0U)
  &Dem_NvData.EntryDataFreePosMirror,
#else
  NULL_PTR,
#endif
  NULL_PTR,
#if (DEM_SIZE_ENTRY_DATA_SECONDARY != 0U)
  &Dem_NvData.EntryDataFreePosSecondary
#else
  NULL_PTR
#endif
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */
};

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include <Dem_MemMap.h>

/*------------------[Dem_NvGateEntryData array]-----------------------------*/

#define DEM_START_SEC_CONST_UNSPECIFIED
#include <Dem_MemMap.h>

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
Dem_NvGateEntryDataPtrVoidType Dem_NvGateEntryData[DEM_MAXNUM_ORIGINS] =
{
  (Dem_NvGateEntryDataPtrVoidType) &Dem_NvGateEntryPrimaryData,
#if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR != 0U)
  (Dem_NvGateEntryDataPtrVoidType) &Dem_NvGateEntryMirrorData,
#else
  (Dem_NvGateEntryDataPtrVoidType) NULL_PTR,
#endif
  (Dem_NvGateEntryDataPtrVoidType) NULL_PTR,
#if (DEM_MAX_NUMBER_EVENT_ENTRY_SEC != 0U)
  (Dem_NvGateEntryDataPtrVoidType) &Dem_NvGateEntrySecondaryData
#else
  (Dem_NvGateEntryDataPtrVoidType) NULL_PTR
#endif
};

/*------------------[Dem_GateEntryData array]-------------------------------*/

Dem_GateEntryDataPtrVoidType Dem_GateEntryData[DEM_MAXNUM_ORIGINS] =
{
  (Dem_GateEntryDataPtrVoidType)
    &Dem_NvGateEntryPrimaryData.EntryPrimary.EntryData,
#if (DEM_SIZE_ENTRY_DATA_MIRROR != 0U)
  (Dem_GateEntryDataPtrVoidType)
    &Dem_NvGateEntryMirrorData.EntryMirror.EntryData,
#else
  (Dem_GateEntryDataPtrVoidType) NULL_PTR,
#endif
  (Dem_GateEntryDataPtrVoidType) NULL_PTR,
#if (DEM_SIZE_ENTRY_DATA_SECONDARY != 0U)
  (Dem_GateEntryDataPtrVoidType)
    &Dem_NvGateEntrySecondaryData.EntrySecondary.EntryData
#else
  (Dem_GateEntryDataPtrVoidType) NULL_PTR
#endif
};

/*------------------[Dem_NvDataBlockId array]-------------------------------*/

/** \brief Array of NvM block Id's on event memories */
CONST(NvM_BlockIdType, DEM_CONST) Dem_NvDataBlockId[DEM_MAXNUM_ORIGINS] =
{
  DEM_NVM_BLOCK_ID_PRIMARY,
  DEM_NVM_BLOCK_ID_MIRROR,
  DEM_NVM_BLOCK_ID_PERMANENT,
  DEM_NVM_BLOCK_ID_SECONDARY
};

#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include <Dem_MemMap.h>

/*------------------[Dem_SizeEventMem array]--------------------------------*/

#define DEM_START_SEC_CONST_8
#include <Dem_MemMap.h>

/** \brief Sizes of the event memories */
CONST(Dem_SizeEvMemEntryType, DEM_CONST)
  Dem_SizeEventMem[DEM_MAXNUM_ORIGINS] =
{
  DEM_MAX_NUMBER_EVENT_ENTRY_PRI,
  DEM_MAX_NUMBER_EVENT_ENTRY_MIR,
  0U,
  DEM_MAX_NUMBER_EVENT_ENTRY_SEC
};

#define DEM_STOP_SEC_CONST_8
#include <Dem_MemMap.h>

#if (DEM_DEV_FREEZE_FRAME_USED == STD_ON)
/*------------------[Dem_SizeDevFFMem array]--------------------------------*/

#define DEM_START_SEC_CONST_8
#include <Dem_MemMap.h>

/** \brief Array holding the number of available slots for development
 **   freeze frames A and B */
CONST(uint8, DEM_CONST)
  Dem_SizeDevFFMem[DEM_NUM_OF_DEVFF_KIND] =
{
  DEM_MAX_NUMBER_DEVFFA_ENTRY,
  DEM_MAX_NUMBER_DEVFFB_ENTRY
};

#define DEM_STOP_SEC_CONST_8
#include <Dem_MemMap.h>

#define DEM_START_SEC_CONST_UNSPECIFIED
#include <Dem_MemMap.h>

/** \brief Array holding the pointers to the array of data of stored
 **   freeze frame A and B
 */
CONSTP2VAR(uint8, DEM_CONST, DEM_VAR_CLEARED)
  Dem_DevFFData[DEM_NUM_OF_DEVFF_KIND] =
{
#if (DEM_MAX_NUMBER_DEVFFA_ENTRY > 0U)
    Dem_NvData.DevFFAData,
#else
    NULL_PTR,
#endif
#if (DEM_MAX_NUMBER_DEVFFB_ENTRY > 0U)
    Dem_NvData.DevFFBData
#else
    NULL_PTR
#endif
};

/** \brief Array holding the pointers to the array of eventIds of stored
 **   freeze frame A and B
 */
CONSTP2VAR(Dem_EventIdType, DEM_CONST, DEM_VAR_CLEARED)
  Dem_DevFFEventId[DEM_NUM_OF_DEVFF_KIND] =
{
#if (DEM_MAX_NUMBER_DEVFFA_ENTRY > 0U)
    Dem_NvData.DevFFAEventId,
#else
    NULL_PTR,
#endif
#if (DEM_MAX_NUMBER_DEVFFB_ENTRY > 0U)
    Dem_NvData.DevFFBEventId
#else
    NULL_PTR
#endif
};

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include <Dem_MemMap.h>
#endif /* (DEM_DEV_FREEZE_FRAME_USED == STD_ON) */

/*==================[internal constants]====================================*/
#define DEM_START_SEC_CONST_UNSPECIFIED
#include <Dem_MemMap.h>

#if (DEM_SIZE_PFF_ENTRY_DATA != 0U)
/** \brief Pointer to the prestored freeze frame data area */
STATIC CONSTP2VAR(Dem_EntryDataType, DEM_CONST, DEM_VAR_CLEARED) Dem_PFFEntryData =
  Dem_PFFEntryDataArea;
#endif

/** \brief Function pointer array for sw-unit initializers */
STATIC CONST(Dem_InitSwUnitFncPtrType, DEM_CONST)
  Dem_InitSwUnitFncPtr[] =
{
  &Dem_InitEventReportVerifier,
  &Dem_InitDTCFilter,
  &Dem_InitDTCSelector,
  &Dem_InitEventMemoryProcessor,
  &Dem_InitRecordFilter,
  &Dem_InitDataRecordSelector,
  &Dem_InitDTCMemoryFilter
};

#if ( (DEM_J1939_SUPPORT == STD_ON) && \
      ( (DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON) || \
        (DEM_J1939_READING_DTC_SUPPORT == STD_ON) ) )
/** \brief Function pointer array for J1939 feature initializers */
STATIC CONST(Dem_InitJ1939FncPtrType, DEM_CONST)
  Dem_InitJ1939FncPtr[DEM_NUMBER_OF_J1939_FEATURES] =
{
#if (DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON)
  &Dem_InitJ1939FreezeFrameFilter,
#endif
#if (DEM_J1939_READING_DTC_SUPPORT == STD_ON)
  &Dem_InitJ1939DtcFilter
#endif
};
#endif

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include <Dem_MemMap.h>

/*==================[external function definitions]=========================*/

#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*------------------[Dem_GetVersionInfo]------------------------------------*/

#if (DEM_VERSION_INFO_API == STD_ON)
FUNC(void, DEM_CODE) Dem_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, DEM_APPL_DATA) versioninfo)
{
  DBG_DEM_GETVERSIONINFO_ENTRY(versioninfo);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (NULL_PTR == versioninfo)
  {
    DEM_REPORT_ERROR(DEM_SID_GetVersionInfo, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    versioninfo->vendorID         = DEM_VENDOR_ID;
    versioninfo->moduleID         = DEM_MODULE_ID;
    versioninfo->sw_major_version = DEM_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = DEM_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = DEM_SW_PATCH_VERSION;
  }

  DBG_DEM_GETVERSIONINFO_EXIT(versioninfo);
}
#endif /* DEM_VERSION_INFO_API == STD_ON */

/*------------------[Dem_PreInit]-------------------------------------------*/

FUNC(void, DEM_CODE) Dem_PreInit(
  P2CONST(Dem_ConfigType, AUTOMATIC, DEM_APPL_CONST) ConfigPtr)
{
  DBG_DEM_PREINIT_ENTRY(ConfigPtr);

  TS_PARAM_UNUSED(ConfigPtr);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO Dem.DetReport.WrongConditionPreInit,1 */
  if (Dem_InitializationState != DEM_UNINITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_PreInit, DEM_E_WRONG_CONDITION);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    Dem_ErrorQueueIdxType QueueIdx;
    Dem_EventIdType EvId;

#if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
    uint16_least EvtAvailIdx;
#endif

    /* initialize (relative) error-queue pointers */
    Dem_ErrorQueueReadIdx =  0U;
    Dem_ErrorQueueWriteIdx = 0U;

    /* initialize error-queue ring buffer indexes */
    /* Deviation TASKING-1 */
    for (QueueIdx = 0U; QueueIdx < DEM_BSW_ERROR_BUFFER_SIZE; ++QueueIdx)
    {
      Dem_ErrorQueue[QueueIdx] = (Dem_ErrorQueueEntryType)DEM_EVENT_ID_INVALID;
#if (DEM_ERROR_QUEUE_EXTENDED == STD_ON)
      Dem_ErrorQueueExt[QueueIdx] = (Dem_ErrorQueueEntryExtType)0;
#endif
    }

    /* reset debouncing counters for event (Dem.ASR40.SWS_Dem_00438) */
    /* !LINKSTO Dem.SWS_Dem_01213,1 */
    /* Deviation TASKING-1 */
    for (EvId = 1U; EvId <= DEM_MAX_EVENTID; ++EvId)
    {
      Dem_DebounceFctPtrTable[Dem_GbiDebounceAlgo(EvId)].ResetFct(EvId);
    }

#if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
      /* !LINKSTO dsn.Dem.EventAvailability.DemEventAvailableStatus.PreInit,1 */
      /* initialize event available status array with pre-configured values */
      /* Deviation TASKING-1 */
      for (EvtAvailIdx = 0U; EvtAvailIdx < DEM_EVENT_ENABLED_ARRAY_SIZE; ++EvtAvailIdx)
      {
        Dem_EventAvailableStatus[EvtAvailIdx] = Dem_EventEnabled[EvtAvailIdx];
      }
#endif /* (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY) */

#if (DEM_EVENT_CONFIRMATION_THRESHOLD_COUNTER_ADAPTABLE == STD_ON)
    Dem_InitEventConfirmationThresholdCounter();
#endif

    /* !LINKSTO dsn.Dem.InitializationModes,1 */
    /* after pre-initializing, mark internal flag */
    Dem_InitializationState = DEM_PREINITIALIZED;
  }

  DBG_DEM_PREINIT_EXIT(ConfigPtr);
}

/*------------------[Dem_Init]----------------------------------------------*/

FUNC(void, DEM_CODE) Dem_Init(void)
{
  DBG_DEM_INIT_ENTRY();

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO Dem.DetReport.WrongConditionInit,1 */
  if ( (Dem_InitializationState != DEM_PREINITIALIZED) &&
       (Dem_InitializationState != DEM_POSTINITIALIZED)
     )
  {
    DEM_REPORT_ERROR(DEM_SID_Init, DEM_E_WRONG_CONDITION);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
    boolean SendPreInitReportsToMaster = FALSE;
#endif
    uint8 SwUnitIdx;
    uint8 NumberOfSwUnits;

#if ( (DEM_J1939_SUPPORT == STD_ON) && \
      ( (DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON) || \
        (DEM_J1939_READING_DTC_SUPPORT == STD_ON) ) )
    uint8 J1939InitIdx;
#endif

    /* following initializations are only done, if the Dem is full initialized
     * first time */
    if (Dem_InitializationState == DEM_PREINITIALIZED)
    {
#if ( (DEM_USE_PERMANENT_STORAGE == STD_ON) && \
      (DEM_OPCYC_NVSTORAGE == STD_ON) && (DEM_NUM_DEBOUNCE_COUNTER_PERM > 0U) )
      Dem_EvIdLeastType NvDebIdx = 0U;
#endif

#if (DEM_USER_CTRL_WIR_SUPPORT == STD_ON)
      Dem_EvIdLeastType UserCtrlWIRIndex = 0U;
#endif

#if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
      Dem_EventIdType ByteIdx;
#endif

#if (DEM_NUM_DEBOUNCE_COUNTER_PERM > 0U)
      Dem_EventIdType EvId;
#endif

#if (DEM_NUM_CMB_DTCS > 0U)
      uint16_least CmbDTCIdx = 0U;
#endif

#if (DEM_OPCYC_NVSTORAGE == STD_OFF)
      Dem_OperationCycleIdType OpCycleId;
#endif

#if (DEM_USE_IMMEDIATE_NV_STORAGE)
      uint8 OriginIdx;
#endif

#if ((DEM_NUMBER_OF_CLIENTS + DEM_NUMBER_OF_VIRTUAL_CLIENTS) > 1)
      uint8 ClientIdx;
#endif

#if ( (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON) || \
      (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U))
      /* variable required to identify the reset of NVM memory */
      boolean ResetNvData = FALSE;
#endif

#if (DEM_OBD_VARIANT_SELECTABLE == STD_ON)
  /* !LINKSTO Dem.ObdVariantSwitch.CalloutObdVariantFnc.ValidVariant,1 */
  /* !LINKSTO Dem.ObdVariantSwitch.VariantActivation,1 */
  /* initialize the active OBD variant based on the callout */
  Dem_ActiveOBDVariant = DEM_GET_OBD_VARIANT_APPL();

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO Dem.ObdVariantSwitch.CalloutObdVariantFnc.InvalidVariant,1 */
  if ( (Dem_ActiveOBDVariant != DEM_OBD_VARIANT_OBD_CLASSIC) &&
       (Dem_ActiveOBDVariant != DEM_OBD_VARIANT_OBDONUDS)
     )
  {
    DEM_REPORT_ERROR(DEM_SID_Init, DEM_E_PARAM_DATA);
  }
#endif /* DEM_DEV_ERROR_DETECT */
#endif /* DEM_OBD_VARIANT_SELECTABLE == STD_ON */

#if (DEM_OPCYC_NVSTORAGE == STD_OFF)
      /* mark all operation cycles as closed */
      /* Deviation TASKING-1 */
      for (OpCycleId = 0U; OpCycleId < DEM_NUM_OPCYCLES; ++OpCycleId)
      {
        DEM_OPCYCLESTATE[OpCycleId] = DEM_CYCLE_STATE_END;
      }
#endif

#if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
      /* mark all prestored freeze frames as deleted */
      /* Deviation TASKING-1 */
      for (ByteIdx = 0U;
           ByteIdx < ((DEM_MAX_NUMBER_PRESTORED_FF + 7U) / 8U);
           ++ByteIdx)
      {
        /* set eight-bit-group at once */
        Dem_PFFEntryValid[ByteIdx] = 0U;
      }
#endif

#if (DEM_USER_CTRL_WIR_SUPPORT == STD_ON)
      /* Deviation TASKING-1 */
      for (UserCtrlWIRIndex = 0U; UserCtrlWIRIndex < DEM_USER_CTRL_WIR_STATUS_SIZE; UserCtrlWIRIndex++)
      {
        Dem_UserCtrlWIRStatus[UserCtrlWIRIndex] = 0U;
      }
#endif

#if (DEM_USE_PERMANENT_STORAGE == STD_OFF)

      /* initialize RAM mirror of non-volatile data to default values */
      Dem_ResetNvData();

#else /* DEM_USE_PERMANENT_STORAGE == STD_ON */

      /* recovery of Dem_NvData from persistent memory must have been
       * done within NvM_ReadAll() */

      /* !LINKSTO Dem.SWS_Dem_00339_Implicit1,1 */
      if (Dem_NvMGetNvRAMBlockStatus(DEM_NVM_BLOCK_ID_DEFAULT) == E_NOT_OK)
      {
#if ( (DEM_NVRAM_CONFIG_SIGNATURE_USED == STD_ON) && \
      ( (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)  || \
        (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U) ) )
        /* mark the immediate and permanent data blocks for reset */
        ResetNvData = TRUE;
#endif
        /* initialize RAM mirror of non-volatile data to default values */
        Dem_ResetNvData();
      }
      else
      {
#if (DEM_NVRAM_CONFIG_SIGNATURE_USED == STD_ON)
        /* !LINKSTO Dem.NvDataSignature.ResetNvMDataIfInvalid,1 */
        if (DEM_CONFIG_NVRAM_SIGNATURE != Dem_NvData.NvRamBlockSignature)
        {
#if ( (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)  || \
      (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U))
          /* Mark the immediate and permanent data blocks for reset */
          ResetNvData = TRUE;
#endif

          /* initialize RAM mirror of non-volatile data to default values */
          Dem_ResetNvData();
        }
#endif /* DEM_NVRAM_CONFIG_SIGNATURE_USED == STD_ON */
      }

#if (DEM_NUM_DEBOUNCE_COUNTER_PERM > 0U)
      /* !LINKSTO Dem.SWS_Dem_00675,1 */
      /* restore internal debounce counter of events with debounce counter
       * value stored non-volatile */
      for (EvId = 0U; EvId <= DEM_MAX_EVENTID; ++EvId)
      {
        if (Dem_GbiDebounceAlgo(EvId) == DEM_DEBOUNCE_COUNTERBASED)
        {
          const Dem_EventIdType DebounceStatusIdx =
            Dem_GbiDebounceStatusIdx(EvId);
          Dem_DebounceProcess(DebounceStatusIdx, EvId, &NvDebIdx);
          /* else: for events with DemDebounceCounterStorage FALSE: no need to
           * reset debounce counters as its already performed in Dem_PreInit() */
        }
      }
#endif /* DEM_NUM_DEBOUNCE_COUNTER_PERM > 0U */

#endif /* DEM_USE_PERMANENT_STORAGE == STD_OFF */

      /* initialize the bit-array that holds the EvEntryExists status for all events */
      Dem_InitEvEntryExists();

#if (DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON)
      /* initialize the StorageOrderId generator for the event status block */
      Dem_NotifyUsedStorageOrderId(
        (DEM_GET_STORAGEORDERID_UINT32(Dem_NvData.StorageOrderId)),
        DEM_STORAGEORDERID_STATUSBLOCK);
#endif

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
      /* !LINKSTO dsn.Dem.ImmediateStorage,2 */
      Dem_RestoreImmediateData(ResetNvData);

      for (OriginIdx = 0U; OriginIdx < DEM_MAXNUM_ORIGINS; ++OriginIdx)
      {
        /* clear async NvM gate write status */
        Dem_NvMGateEntryInfo[OriginIdx].Status = DEM_NVM_IDLE;
      }
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */

#if ( (DEM_USE_PERMANENT_STORAGE == STD_ON) && \
      ((DEM_STATUS_BIT_STORAGE_TF == STD_OFF) || \
      (DEM_STATUS_BIT_STORAGE_TF_PER_EVENT_SUPPORT == STD_ON)) )
      Dem_ClearStatusBitStorageTestFailed();
#endif

#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)
      Dem_PermanentMemoryInit(ResetNvData);
#endif

#if (DEM_DEV_FREEZE_FRAME_USED == STD_ON)
      /* validate the cross reference for development Freeze Frames */
      /* !LINKSTO dsn.Dem.DevFF.DemInit,2 */
      Dem_InitDevFreezeFrameEntryIdx();
#endif

#if (DEM_CLEAR_DTC_BEHAVIOR != DEM_CLRRESP_VOLATILE)
      /* initialize asynchronous ClearDTC status */
      Dem_ClearDtcAsyncStatus.EventStatusWrite = DEM_NVM_IDLE;
#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_TRIGGER)
      Dem_ClearDtcAsyncStatus.RetriggerEventStatusWrite = FALSE;
#else
      Dem_ClearDtcAsyncStatus.EventMemWrite = DEM_NVM_IDLE;
#endif
#endif /* DEM_CLEAR_DTC_BEHAVIOR != DEM_CLRRESP_VOLATILE */
      /* initialize asynchronous ClearDTC status fields related to burst reduction */
      Dem_ClearDtcAsyncStatus.RunState = DEM_CLEARDTC_STATE_IDLE;
      Dem_ClearDtcAsyncStatus.ClientId = DEM_CLIENT_ID_INVALID;

#if ((DEM_NUMBER_OF_CLIENTS + DEM_NUMBER_OF_VIRTUAL_CLIENTS) > 1)
      for(ClientIdx = 0;
          ClientIdx < DEM_NUMBER_OF_CLIENTS + DEM_NUMBER_OF_VIRTUAL_CLIENTS;
          ClientIdx++)
      {
        Dem_ClearDTCResult[ClientIdx] = DEM_CLEAR_NO_RESULT;
      }
#else
      Dem_ClearDTCResult[0U] = DEM_CLEAR_NO_RESULT;
#endif
      /* initialize the array which stores the largest value of occurrence order
       * in a memory */
      Dem_InitMaxOccOrder();

#if ( (DEM_NUM_OF_PIDS_IN_OBDFF > 0U) && \
      (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE) && \
      (DEM_USE_PERMANENT_STORAGE == STD_ON) )
      /* init maximum OBD occurrence value with the highest value saved for an
       * event entry */
      Dem_InitMaxOBDOccOrder();
#endif

#if (DEM_NUM_CMB_DTCS > 0U)
      /* initialize Dem_CmbDTCFlags with 0xff so when Dem_InitAllCmbDTCStatus is called
       * all the combined DTCs will be processed */
      /* Deviation TASKING-1 */
      for (CmbDTCIdx = 0U; CmbDTCIdx < DEM_NUM_CMB_DTCS_BYTES; CmbDTCIdx++)
      {
        Dem_CmbDTCFlags[CmbDTCIdx] = 0xFFU;
      }

#if (DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON)
      /* restore the Combined PDTC bit of all combined DTCs.*/
      /* !LINKSTO Dem.OBDonUDS.CombinedUDSDTCStatus.PDTC.NonVolatileStorage,1 */
      /* !LINKSTO dsn.Dem.OBDonUDS.EventCombination.RestoreCmbPDTC,1 */
      Dem_RestoreCmbPDTC();
#endif

      /* initialize the Combined DTC statuses of all combined DTCs.*/
      Dem_InitAllCmbDTCStatus(FALSE);
#endif /* DEM_NUM_CMB_DTCS > 0U */

#if (DEM_OBD_CENTRALIZED_PID_REL_DISTANCE_HANDLING == STD_OFF)
      /* clear variables for the time elapsed since engine start
         - used in PID31 calculation */
      Dem_LastTimeSinceEngineStart = 0U;
      Dem_MainFunctionOneSecondCounter = 0U;
#endif

#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
      SendPreInitReportsToMaster = TRUE;
#endif

#if (DEM_MILGROUP_SUPPORT == STD_ON)
      /* initialize the array that stores the first failed event in the current
       * operation cycle for each MIL group */
      Dem_MILGroupCalcAllFirstFailedEventId();
#endif

#if ((DEM_OBD_Support == STD_ON) && (DEM_READINESS_CALCULATION_SUPPORT == STD_ON))
      Dem_InitReadinessGroupProcessor();
#endif
    }

    /* following actions are also performed after DEM_POSTINITIALIZED: */

    NumberOfSwUnits = sizeof(Dem_InitSwUnitFncPtr) / sizeof (Dem_InitSwUnitFncPtr[0U]);

    /* initializes internal data elements of sw-units */
    for (SwUnitIdx = 0U; SwUnitIdx < NumberOfSwUnits; SwUnitIdx++)
    {
      Dem_InitSwUnitFncPtr[SwUnitIdx]();
    }

#if ( (DEM_J1939_SUPPORT == STD_ON) && \
      ( (DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON) || \
        (DEM_J1939_READING_DTC_SUPPORT == STD_ON) ) )
    /* initializes internal data elements of J1939 features */
    /* Deviation TASKING-1 */
    for (J1939InitIdx = 0U; J1939InitIdx < DEM_NUMBER_OF_J1939_FEATURES; J1939InitIdx++)
    {
      /* !LINKSTO Dem.J1939.Dem_J1939DcmSetFreezeFrameFilter.FilterAccepted_DemInit,1 */
      /* !LINKSTO Dem.J1939.Dem_J1939DcmSetDTCFilter.ResetFilter_DemInit,1 */
      Dem_InitJ1939FncPtr[J1939InitIdx]();
    }
#endif

    /* !LINKSTO dsn.Dem.InitializationModes,1 */
    /* after full initializing, mark internal flag */
    Dem_InitializationState = DEM_INITIALIZED;

#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  Dem_InformSatellites(SendPreInitReportsToMaster);
#endif /* (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON) */
  }

  DBG_DEM_INIT_EXIT();
}


/*------------------[Dem_Shutdown]------------------------------------------*/

FUNC(void, DEM_CODE) Dem_Shutdown(void)
{
#if ( (DEM_USE_AGING == STD_ON) && \
      (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD) )
#if (DEM_NUMBER_OF_CLIENTS > 1)
  uint8 MemoryIndex = 0;
#endif
#endif

  DBG_DEM_SHUTDOWN_ENTRY();

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_Shutdown, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_Shutdown, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
#if ( (DEM_USE_AGING == STD_ON) && \
      (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD) )
    Dem_EventIdType LockedEvId;
#endif
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    uint8 OriginIdx;
    Dem_SizeEvMemEntryType EntryIdx;
#endif

    /* finalize all pending operations */
    do
    {
      Dem_MainFunction();
    } while (!DEM_IS_ERROR_QUEUE_EMPTY());

#if (DEM_OPCYC_AUTO_END_ENABLED == STD_ON)
    /* !LINKSTO dsn.Dem.OBD.OPCYC.DemOperationCycleAutomaticEnd,1 */
    /* end all operation cycles, where DemOperationCycleAutomaticEnd
     * is configured to TRUE and are not ended yet
     */
    {
      Dem_OperationCycleIdType OpCycleIdIterator;

      for (OpCycleIdIterator = 0U;
          OpCycleIdIterator < DEM_NUM_OPCYCLES;
          OpCycleIdIterator++)
      {
        /* evaluate whether automatic end is configured for current opcycle
         * and if current opcycle is not yet ended */
        if ( (DEM_IS_BIT_SET_IN_ARRAY(Dem_OpCycAutoEndEnabledMasks, OpCycleIdIterator)) &&
             (DEM_OPCYCLESTATE[OpCycleIdIterator] != DEM_CYCLE_STATE_END) )
        {
          /* API function called here in stead of Dem_OpCycleProcessCycleEnd,
           * because storage of new cycle state and trigger for NvMWrite
           * is done outside of Dem_OpCycleProcessCycleEnd(). It's casted
           * to void because the return value can not be handled here anyway */
          (void)Dem_SetOperationCycleState(OpCycleIdIterator, DEM_CYCLE_STATE_END);
        }
      }
    }
#endif /* DEM_OPCYC_AUTO_END_ENABLED == STD_ON */

    /* before shutdown, mark internal flag */
    Dem_InitializationState = DEM_POSTINITIALIZED;

#if ( (DEM_USE_AGING == STD_ON) && \
      (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD) )

    /* !LINKSTO Dem.SWS_Dem_00270,1 */
    /* clear any aged disabled event from event memory */
#if (DEM_NUMBER_OF_CLIENTS == 1)
    LockedEvId = Dem_EvIdOfLockedMemoryEntry[0U];

    if (LockedEvId != DEM_EVENT_ID_INVALID)
    {
#else
    while(MemoryIndex < Dem_DTCRecordLockingNextFreeIndex)
    {
      LockedEvId = Dem_EvIdOfLockedMemoryEntry[MemoryIndex];
#endif
      if (DEM_AGING_ALLOWED(LockedEvId))
      {
        Dem_EventMemoryEntryPtrType EvMemEntry;

        if (Dem_SearchForEntry(LockedEvId, &EvMemEntry, NULL_PTR) == TRUE)
        {
          const Dem_EntryDataPtrType AgingCounterPtr =
            Dem_IntValEntryData(EvMemEntry);
#if (DEM_NUM_CMB_DTCS > 0U)
          const Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(LockedEvId);
          if (DEM_IS_DTC_COMBINED(DTCConfIdx))
          {
            /* get the EventId of the stored event involved in combination. */
            LockedEvId = EvMemEntry->EventId;
          }
#endif

          /* !LINKSTO Dem.SWS_Dem_01075,1 */
          if (*AgingCounterPtr == 0U)
          {
#if (DEM_NUM_CMB_DTCS > 0U)
            if (DEM_IS_DTC_COMBINED(DTCConfIdx))
            {
              boolean CurrentEventStatusChanged = FALSE;
              Dem_DTCStatusMaskType OldDTCStatusMask =
                DEM_DTC_STATUS_MASKS[LockedEvId];
              Dem_DTCStatusMaskType NewDTCStatusMask = 0U;

              Dem_ClearAgedEventEntry(LockedEvId, EvMemEntry);

              NewDTCStatusMask = DEM_DTC_STATUS_MASKS[LockedEvId];

              if (OldDTCStatusMask != NewDTCStatusMask)
              {
                CurrentEventStatusChanged = TRUE;
              }

              /* !LINKSTO dsn.Dem.InternalAging.IndirectUnlockOfDTCRecordForCmdDTCStatusUpdate,1 */
              /* after shutdown sequence started don't trigger callbacks for status change */
              Dem_ResetStatusForCmbEvents(LockedEvId,
                CurrentEventStatusChanged);
            }
            else /* for non-combined events */
#endif /* DEM_NVM_CMB_DTCS > 0 */
            {
              Dem_ClearAgedEventEntry(LockedEvId, EvMemEntry);
            }

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
            /* aged event shall be cleared from NVRAM during shutdown */
            EvMemEntry->EntryStatus = DEM_ENTRY_CHANGED;
#endif
          }
        }
      }
#if (DEM_NUMBER_OF_CLIENTS == 1)
    }
#else
      MemoryIndex++;
    }
#endif
#endif /* (DEM_USE_AGING == STD_ON) &&
          (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD) */

    /* --- shutdown RAM mirror of non-volatile data --- */
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    /* shutdown loop for all event memories */
    for (OriginIdx = 0U; OriginIdx < (uint8)DEM_MAXNUM_ORIGINS; ++OriginIdx)
    {
      /* event memory is used */
      if (Dem_NvDataBlockId[OriginIdx] != DEM_NVM_BLOCK_ID_INVALID)
      {
        /* trigger the memory-stack main functions synchronously to complete
         * immediate storage processing */
        DEM_STORAGEWAITNVMREADY(Dem_NvDataBlockId[OriginIdx]);

        /* for every event entry */
        for (EntryIdx = 0U; EntryIdx < Dem_SizeEventMem[OriginIdx]; ++EntryIdx)
        {
          /* check for events which had to be stored immediately but write to
           * NvM was not successful, events which have not to be stored
           * immediately with changed entry data, immediate storage events not
           * stored immediately due to maximum number of occurrences and event
           * memory entries whose restoration from NvM during initialization
           * was not successful */
          if (Dem_EventMem[OriginIdx][EntryIdx].EntryStatus
               != DEM_ENTRY_UNCHANGED)
          {
            const NvM_BlockIdType NvDataBlockId = Dem_NvDataBlockId[OriginIdx];

            /* select corresponding NVRAM block dataset */
            if (NvM_SetDataIndex(NvDataBlockId, EntryIdx) == E_OK)
            {
              /* store this event memory entry persistently */
              Dem_StoreImmediately(OriginIdx, EntryIdx);

              /* queue write request of gate-entry to NvM - NvM_DstPtr is unused,
               * as permanent RAM block (gate-entry) is configured */
              (void)NvM_WriteBlock(NvDataBlockId, NULL_PTR);

              /* trigger the memory-stack main functions synchronously */
              DEM_STORAGEWAITNVMREADY(Dem_NvDataBlockId[OriginIdx]);
            }
          }
        }
      }
    }
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */

#if (DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON) && \
    (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_VOLATILE)
    /* !LINKSTO dsn.Dem.IntermediateNvStorageOfDTCStatus.StorageOrderId.StatusBlock,1 */
    /* update the StorageOrderId when ClearDTCBehavior is configured as
     * volatile because NvM explicit synchronization is not enabled */
    Dem_GetNextStorageOrderId(Dem_NvData.StorageOrderId,
      DEM_STORAGEORDERID_STATUSBLOCK);
#endif

#if (DEM_USE_PERMANENT_STORAGE == STD_ON)

#if (DEM_NUM_DEBOUNCE_COUNTER_PERM > 0U)
    Dem_StoreDebounceCounterStatus();
#endif

    /* validate Dem_NvData, to be stored persistently during NvM_WriteAll() */
    (void)NvM_SetRamBlockStatus(DEM_NVM_BLOCK_ID_DEFAULT, TRUE);

    /* persistent storage of Dem_NvData must be done within NvM_WriteAll() */
#endif /* (DEM_USE_PERMANENT_STORAGE == STD_ON) */
  }

  DBG_DEM_SHUTDOWN_EXIT();
}

/*------------------[Dem_SetEventFailedWithSyncFreezeFrame]-----------------*/

#if (DEM_SEM_SUPPORT == STD_ON)
FUNC(void, DEM_CODE) Dem_SetEventFailedWithSyncFreezeFrame(
  Dem_EventIdType EventId)
{
  DBG_DEM_SETEVENTFAILEDWITHSYNCFREEZEFRAME_ENTRY(EventId);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetEventFailedWithSyncFreezeFrame, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_SetEventFailedWithSyncFreezeFrame, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_SetEventFailedWithSyncFreezeFrame, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_SetEventFailedWithSyncFreezeFrame, DEM_E_WRONG_CONFIGURATION);
  }
  else if (!DEM_IS_SECURITY_EVENT(EventId))
  {
    DEM_REPORT_ERROR(DEM_SID_SetEventFailedWithSyncFreezeFrame, DEM_E_PARAM_DATA);
  }
  else
#endif /* (DEM_DEV_ERROR_DETECT == STD_ON) */
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
  if (Dem_GbiEvAvailable(EventId) == FALSE)
  {
    /* event is disabled so reporting shall be skipped */
  }
  else
#endif
  {
    /* !LINKSTO dsn.Dem.Sem.InternalPassReport,1 */
    (void)Dem_InternalProcessEventReport(EventId, DEM_EVENT_STATUS_PASSED, DEM_FID_INTERNALSETEVENTSTATUS);

    /* !LINKSTO dsn.Dem.Sem.SetEventFailedWithSyncFreezeFrame,1 */
    (void)Dem_InternalProcessEventReport(EventId, DEM_EVENT_STATUS_FAILED, DEM_FID_INTERNALSETEVENTSTATUS);
  }

  DBG_DEM_SETEVENTFAILEDWITHSYNCFREEZEFRAME_EXIT(EventId);
}
#endif /* (DEM_SEM_SUPPORT == STD_ON) */

/*------------------[Dem_ReportErrorStatus]---------------------------------*/

#if (DEM_NUM_BSW_EVENTS > 0U)
/* !LINKSTO Dem.Dem_ReportErrorStatus.Unavailable,1 */
/* !LINKSTO Dem.BSWDistribution.DistributedFunctionality,2 */
FUNC(void, DEM_CODE) Dem_ReportErrorStatus(
  Dem_EventIdType     EventId,
  Dem_EventStatusType EventStatus)
{
  DBG_DEM_REPORTERRORSTATUS_ENTRY(EventId, EventStatus);

  /* this API can be called from Dem satellite instances.
   * only access on shared data is allowed. */

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* this function can also be called within pre-initialized state */
  if (Dem_InitializationState == DEM_UNINITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_ReportErrorStatus, DEM_E_UNINIT);
  }
  else if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_ReportErrorStatus, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_ReportErrorStatus, DEM_E_WRONG_CONFIGURATION);
  }
  else if ( ( (EventStatus != DEM_EVENT_STATUS_PASSED) &&
              (EventStatus != DEM_EVENT_STATUS_FAILED) ) &&
            ( (EventStatus != DEM_EVENT_STATUS_PREPASSED) &&
              (EventStatus != DEM_EVENT_STATUS_PREFAILED) )
          )
  {
    DEM_REPORT_ERROR(DEM_SID_ReportErrorStatus, DEM_E_PARAM_DATA);
  }
  else if (Dem_GbiEventKind(EventId) != DEM_EVENT_KIND_BSW)
  {
    DEM_REPORT_ERROR(DEM_SID_ReportErrorStatus, DEM_E_PARAM_DATA);
  }
#if (DEM_NUM_DEBOUNCE_COUNTER_PERM > 0U)
  else if (Dem_DebounceCounterWithNvStorageDuringPreInit(EventId) == TRUE)
  {
    /* !LINKSTO Dem.DebounceCounters.StartupDET,1 */
    DEM_REPORT_ERROR(DEM_SID_ReportErrorStatus, DEM_E_WRONG_CONDITION);
  }
#endif
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
    const CoreIdType CoreId = GetCoreID();

    if (CoreId == DEM_MASTER_INSTANCE)
#endif
    {
      /* direct processing for reports received on master instance */
      Dem_ReportErrorStatusCore(EventId, EventStatus, FALSE);
    }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
    else /* satellite instance */
    {
#if (DEM_DEV_ERROR_DETECT == STD_ON)
      boolean QueueOperationStatus = FALSE;
#endif
      boolean ReportQueuedOnSatellite = FALSE;

      /*
       * ENTER satellite critical section to protect the queue and write index
       *       call-context: another request from the same satellite (Task)
       */
      Dem_SatelliteFncPtr[CoreId].EnterExclusiveArea();

      if (Dem_InitializationState == DEM_PREINITIALIZED)
      {
        /* queue all requests in PREINITIALIZED state */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
        QueueOperationStatus = Dem_QueueBswEventReportOnSatellite(CoreId, EventId, EventStatus);
#else
        (void)Dem_QueueBswEventReportOnSatellite(CoreId, EventId, EventStatus);
#endif

        /* mark report as being queued locally in the satellite instance */
        ReportQueuedOnSatellite = TRUE;
      }

      /*
       * LEAVE satellite critical section
       */
      Dem_SatelliteFncPtr[CoreId].ExitExclusiveArea();

      /* Dem is fully initialized or post-initialized */
      if (ReportQueuedOnSatellite == FALSE)
      {
        /*
         * ENTER satellite critical section to protect the queue and write index
         *       call-context: another request from the same satellite or Dem_Init() (Task)
         */
        Dem_SatelliteFncPtr[CoreId].EnterExclusiveArea();

        /* check if synchronization with master instance is still ongoing */
        if (Dem_IsSatelliteQueueEmpty(CoreId) == FALSE)
        {
          /* not all BSW event reports have been sent to the master core yet
           * -> queue new report to preserve the reporting order per event */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
          QueueOperationStatus = Dem_QueueBswEventReportOnSatellite(CoreId, EventId, EventStatus);
#else
          (void)Dem_QueueBswEventReportOnSatellite(CoreId, EventId, EventStatus);
#endif

          /* mark report as being queued locally in the satellite instance */
          ReportQueuedOnSatellite = TRUE;
        }

        /*
         * LEAVE satellite critical section
         */
        Dem_SatelliteFncPtr[CoreId].ExitExclusiveArea();

        /* send request directly to the master instance for processing */
        if (ReportQueuedOnSatellite == FALSE)
        {
          Dem_EventReportInfoType LocalBswEventInfo;
          LocalBswEventInfo.EventId = EventId;
          LocalBswEventInfo.EventStatus = EventStatus;
          LocalBswEventInfo.QueuedInPreinitPhase = FALSE;

          /* ignore return value because the API has also no return value */
          (void)Dem_SatelliteFncPtr[CoreId].SchMSendReportErrorStatusToMaster(
            &LocalBswEventInfo);
        }
      }

#if (DEM_DEV_ERROR_DETECT == STD_ON)
      /* check for overflow of local queue */
      if ((QueueOperationStatus == FALSE) && (ReportQueuedOnSatellite == TRUE))
      {
        /* !LINKSTO Dem.BSWDistribution.BSWReportBufferingOnSatellites.Overflow,2 */
        DEM_REPORT_ERROR(DEM_SID_ReportErrorStatus, DEM_E_WRONG_CONFIGURATION);
      }
#endif
    }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  }

  DBG_DEM_REPORTERRORSTATUS_EXIT(EventId, EventStatus);
}

#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
FUNC(void, DEM_CODE) Dem_ReceiveBswEventReportsOnMaster(void)
{
  DBG_DEM_RECEIVEBSWEVENTREPORTSONMASTER_ENTRY();

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.BSWReportReceivingOnMaster.WrongContext,1 */
    DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_WRONG_CONTEXT);
  }
  else
#endif
  {
    Std_ReturnType SchMRetVal;
    boolean DataReceived;

    /* !LINKSTO Dem.BSWDistribution.ReceptionOfQualificationsOnMaster.Reception,1 */
    /* !LINKSTO Dem.BSWDistribution.ReceptionOfQualificationsOnMaster.StopReception,1 */
    do
    {
      Dem_EventReportInfoType EventToBeProcessed;

      /* receive the data from the satellite instances */
      SchMRetVal = SchM_Receive_Dem_ReportErrorStatusRequire(&EventToBeProcessed);
      DataReceived = ( (SchMRetVal == RTE_E_OK) || (SchMRetVal == RTE_E_LOST_DATA) ) ? TRUE : FALSE;

      /* if data was received successfully perform main processing */
      if (DataReceived == TRUE)
      {
        Dem_ReportErrorStatusCore(EventToBeProcessed.EventId,
          EventToBeProcessed.EventStatus, EventToBeProcessed.QueuedInPreinitPhase);
      }
    } while (DataReceived == TRUE);
  }

  DBG_DEM_RECEIVEBSWEVENTREPORTSONMASTER_EXIT();
}
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */

FUNC(Std_ReturnType, DEM_CODE) Dem_ReportErrorStatusPreInit
(
  Dem_EventInfoType EventInfo,
  Dem_EventStatusType EventStatus)
{
  Std_ReturnType Result = E_NOT_OK;
  boolean EntryPresent = FALSE;
  Dem_EventStatusType PreviousEntryStatus = DEM_EVENT_STATUS_FAILED;
  Dem_EventIdType EventId = EventInfo.EventId;

  DBG_DEM_REPORTERRORSTATUSPREINIT_ENTRY(EventId, EventStatus);

#if (DEM_DEV_ERROR_DETECT == STD_OFF)
  (void)Dem_DebounceEvent(EventId, &EventStatus);
#else
  if (Dem_DebounceEvent(EventId, &EventStatus) == DEM_E_DET_REPORT)
  {
    /* A DET error was identified during debouncing */
    DEM_REPORT_ERROR(DEM_SID_ReportErrorStatus, DEM_E_PARAM_DATA);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* No further check of the Result value is required,
     * since it can be invalid only for PRE-Status */
    if ( (EventStatus == DEM_EVENT_STATUS_FAILED) ||
         (EventStatus == DEM_EVENT_STATUS_PASSED) )
    {
      if (Dem_CheckProcessingConditions(EventId) == E_OK)
      {
#if (DEM_DEV_ERROR_DETECT == STD_ON)
        boolean queueWriteSuccess = TRUE;
#endif

        /*
         * ENTER critical section to protect the error-queue and queue-pointers
         *       call-context: any
         */
        DEM_ENTER_EXCLUSIVE_AREA();

        /* check if event is already present in error-queue */
        EntryPresent = Dem_CheckErrorQueueEntry(EventId, &PreviousEntryStatus);

        /* make entry in error-queue */
        if ( (EntryPresent == FALSE) || (EventStatus != PreviousEntryStatus) )
        {
          Dem_StatusTransitionType TransitionType =
            (DEM_IS_EV_ST_BIT_TFTOC_SET(EventId)) ? DEM_TRANSITION_EVENT_TFTOC : 0U;

#if (DEM_DEV_ERROR_DETECT == STD_ON)
          queueWriteSuccess = Dem_WriteErrorQueueEntry(EventInfo,
                                                       EventStatus,
                                                       TransitionType);
#else
          /* return value is used for error detection in Det only */
          (void) Dem_WriteErrorQueueEntry(EventInfo, EventStatus, TransitionType);
#endif /* DEM_DEV_ERROR_DETECT */
        }

        /*
         * LEAVE critical section
         */
        DEM_EXIT_EXCLUSIVE_AREA();

#if (DEM_DEV_ERROR_DETECT == STD_ON)
        if (queueWriteSuccess == FALSE)
        {
          DEM_REPORT_ERROR(DEM_SID_ReportErrorStatus, DEM_E_WRONG_CONFIGURATION);
        }
#endif

        Result = E_OK;
      }
    }
  }

  DBG_DEM_REPORTERRORSTATUSPREINIT_EXIT(Result, EventId, EventStatus);

  return Result;
}

STATIC FUNC(void, DEM_CODE) Dem_ReportErrorStatusCore(
  Dem_EventIdType     EventId,
  Dem_EventStatusType EventStatus,
  boolean             QueuedInPreinitPhase)
{
  DBG_DEM_REPORTERRORSTATUSCORE_ENTRY(EventId, EventStatus, QueuedInPreinitPhase);

#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
  if (Dem_GbiEvAvailable(EventId) == FALSE)
  {
    /* event is disabled so reporting shall be skipped */
  }
  else
#endif
  {
    /* !LINKSTO Dem.BufferMechanism.Startup,2 */
    if ( (Dem_InitializationState == DEM_PREINITIALIZED) || (QueuedInPreinitPhase == TRUE) )
    {
      (void)Dem_InternalProcessEventReport(EventId, EventStatus, DEM_FID_REPORTERRORSTATUSPREINIT);
    }
    else /* Dem_InitializationState == DEM_INITIALIZED/DEM_POSTINITIALIZED
          * or development error */
    {
      /* process "normal" event handling */

#if (DEM_DEV_ERROR_DETECT == STD_ON)
      if (Dem_InternalProcessEventReport(EventId, EventStatus, DEM_FID_INTERNALSETEVENTSTATUS) == DEM_E_DET_REPORT)
      {
        DEM_REPORT_ERROR(DEM_SID_ReportErrorStatus, DEM_E_WRONG_CONFIGURATION);
      }
#else
      /* return value is used for error detection in Det only */
      (void)Dem_InternalProcessEventReport(EventId, EventStatus, DEM_FID_INTERNALSETEVENTSTATUS);
#endif /* DEM_DEV_ERROR_DETECT */
    }
  }

  DBG_DEM_REPORTERRORSTATUSCORE_EXIT(EventId, EventStatus, QueuedInPreinitPhase);
}
#endif  /* (DEM_NUM_BSW_EVENTS > 0) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#if (DEM_INCLUDE_RTE == STD_ON)
#define Dem_START_SEC_CODE
#include <Dem_MemMap.h>
#else
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>
#endif

#if ( (DEM_INCLUDE_RTE == STD_OFF) || (DEM_NUM_SWC_EVENTS > 0) || \
      (DEM_REPORT_BSW_EVENTS_VIA_SET_EVENT_STATUS == STD_ON) )

/*------------------[Dem_SetEventStatus]------------------------------------*/
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventStatus(
  Dem_EventIdType     EventId,
  Dem_EventStatusType EventStatus)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_SETEVENTSTATUS_ENTRY(EventId, EventStatus);

/* !LINKSTO Dem.DiagnosticMonitor.SetEventStatusOperation.ASR2011,1 */
#if (DEM_DEFAULT_ASR_SERVICE_API == DEM_SERVICE_API_ASR2011)
  if (EventStatus != DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED)
#endif
  {
#if (DEM_REPORT_BSW_EVENTS_VIA_SET_EVENT_STATUS == STD_ON)
    if ((EventId != DEM_EVENT_ID_INVALID) && (EventId <= DEM_MAX_EVENTID) &&
        (Dem_GbiEventKind(EventId) == DEM_EVENT_KIND_BSW))
    {
      /* !LINKSTO Dem.SetEventStatus.BSWEventsDebouncing,1 */
      /* !LINKSTO Dem.BSWDistribution.DistributedFunctionality,2 */
      Dem_ReportErrorStatus(EventId, EventStatus);
      Result = E_OK;
    }
    else
#endif  /* (DEM_REPORT_BSW_EVENTS_VIA_SET_EVENT_STATUS == STD_ON) */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
    if (Dem_InitializationState != DEM_INITIALIZED)
    {
      DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_UNINIT);
    }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
    else if (GetCoreID() != DEM_MASTER_INSTANCE)
    {
      /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
      DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_WRONG_CONTEXT);
    }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
    else if (EventId == DEM_EVENT_ID_INVALID)
    {
      DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_PARAM_DATA);
    }
    else if (EventId > DEM_MAX_EVENTID)
    {
      DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_WRONG_CONFIGURATION);
    }
    else if ( ( (EventStatus != DEM_EVENT_STATUS_PASSED) &&
                (EventStatus != DEM_EVENT_STATUS_FAILED) ) &&
              ( (EventStatus != DEM_EVENT_STATUS_PREPASSED) &&
                (EventStatus != DEM_EVENT_STATUS_PREFAILED) )
            )
    {
      DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_PARAM_DATA);
    }
    else if (Dem_GbiEventKind(EventId) != DEM_EVENT_KIND_SWC)
    {
      DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_PARAM_DATA);
    }
#if (DEM_SEM_SUPPORT == STD_ON)
    else if (DEM_IS_SECURITY_EVENT(EventId))
    {
      DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_PARAM_DATA);
    }
#endif
    else
#endif /* DEM_DEV_ERROR_DETECT */
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
    if (Dem_GbiEvAvailable(EventId) == FALSE)
    {
      /* event is disabled so reporting shall be skipped */
    }
    else
#endif
    {
      Result = Dem_InternalProcessEventReport(EventId, EventStatus, DEM_FID_INTERNALSETEVENTSTATUS);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
      if (Result == DEM_E_DET_REPORT )
      {
        DEM_REPORT_ERROR(DEM_SID_SetEventStatus, DEM_E_WRONG_CONFIGURATION);
        Result = E_NOT_OK;
      }
#endif /* DEM_DEV_ERROR_DETECT */
    }
  }

  DBG_DEM_SETEVENTSTATUS_EXIT(Result, EventId, EventStatus);
  return Result;
}
#endif  /* ( (DEM_INCLUDE_RTE == STD_OFF) || (DEM_NUM_SWC_EVENTS > 0) || \
             (DEM_REPORT_BSW_EVENTS_VIA_SET_EVENT_STATUS == STD_ON) ) */

/* APIs are only allowed for SW-C events as per SWS */
#if ( (DEM_INCLUDE_RTE == STD_OFF) || (DEM_NUM_SWC_EVENTS > 0) )

/*------------------[Dem_ResetEventStatus]----------------------------------*/

/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_ResetEventStatus(Dem_EventIdType EventId)
{
  Std_ReturnType Result = E_NOT_OK;

#if ((DEM_J1939_SUPPORT == STD_ON) && (DEM_J1939_READING_DTC_SUPPORT == STD_ON))
  boolean CbTriggerJ1939Dcm = FALSE;
#endif
  DBG_DEM_RESETEVENTSTATUS_ENTRY(EventId);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_ResetEventStatus, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_ResetEventStatus, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_ResetEventStatus, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_ResetEventStatus, DEM_E_WRONG_CONFIGURATION);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
  if (Dem_GbiEvAvailable(EventId) == FALSE)
  {
    /* event is disabled so the reset shall be skipped */
    /* E_NOT_OK return value remains */
  }
  else
#endif
  {
#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
    Dem_DTCStatusMaskType OldDTCStatusMask = 0U;
    Dem_DTCStatusMaskType NewDTCStatusMask = 0U;
#endif
#if (DEM_NUM_CMB_DTCS > 0U)
    Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
    Dem_EventStatusExtendedType OldCombinedStatus = 0U;
    Dem_EventStatusExtendedType NewCombinedStatus = 0U;
#endif
    /*
     * ENTER critical section to protect the status bits AND debounce status
     *       call-context: Rte (Task)
     */
    DEM_ENTER_EXCLUSIVE_AREA();

    /* !LINKSTO Dem.SWS_Dem_00638,1 */
    /* reset of failed qualification-result is allowed only if event
     * is not already tested this operation cycle */
    if (DEM_IS_EV_ST_BIT_TNCTOC_SET(EventId))
    {
      /* clear bit only if it is set */
      if (DEM_IS_EV_ST_BIT_TF_SET(EventId))
      {
#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
        OldDTCStatusMask = DEM_DTC_STATUS_MASKS[EventId];
#endif

        /* TEST FAILED -> 0 */
        DEM_CLR_EV_ST_MASK(EventId, DEM_UDS_STATUS_TF);
#if ((DEM_J1939_SUPPORT == STD_ON) && (DEM_J1939_READING_DTC_SUPPORT == STD_ON))
        CbTriggerJ1939Dcm = TRUE;
#endif
        /* other bits are unchanged */
#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
        NewDTCStatusMask = DEM_DTC_STATUS_MASKS[EventId];
#endif
#if (DEM_NUM_CMB_DTCS > 0U)
        /* if event is combined, update the combined DTC status */
        if (DEM_IS_DTC_COMBINED(DTCConfIdx))
        {
          OldCombinedStatus = Dem_CmbDTCStatus[DTCConfIdx];
          NewCombinedStatus = Dem_CalculateCmbDTCStatus(DTCConfIdx, FALSE);
        }
        else
        {
          TS_PARAM_UNUSED(OldCombinedStatus);
          TS_PARAM_UNUSED(NewCombinedStatus);
        }
#endif /* (DEM_NUM_CMB_DTCS > 0U) */
      }
      /* else: testFailed bit is already set to 0, do nothing */

      /* reset debouncing counters for event (Dem.ASR40.SWS_Dem_00187) */
      Dem_DebounceFctPtrTable[Dem_GbiDebounceAlgo(EventId)].ResetFct(EventId);

      Result = E_OK;
    }
    /*
     * LEAVE critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();

#if ((DEM_J1939_SUPPORT == STD_ON) && (DEM_J1939_READING_DTC_SUPPORT == STD_ON))
    if (TRUE == CbTriggerJ1939Dcm)
    {
      Dem_CbTriggerJ1939Dcm(EventId);
    }
#endif
#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
    if (OldDTCStatusMask != NewDTCStatusMask)
    {
      Dem_CbTriggerOnEventStatus(EventId,
                                 OldDTCStatusMask,
                                 NewDTCStatusMask);
    }
#endif /* (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) */
#if (DEM_NUM_CMB_DTCS > 0U)
    Dem_InternalCheckOnCmbDTCStatusChange(EventId, OldCombinedStatus, NewCombinedStatus);
#endif
  }

  DBG_DEM_RESETEVENTSTATUS_EXIT(Result, EventId);
  return Result;
}

/*------------------[Dem_ResetEventDebounceStatus]--------------------------*/
/* Deviation MISRAC2012-1 */
#if (DEM_INTERNAL_DEBOUNCE_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_ResetEventDebounceStatus(
  Dem_EventIdType EventId,
  Dem_DebounceResetStatusType DebounceResetStatus)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_RESETEVENTDEBOUNCESTATUS_ENTRY(EventId, DebounceResetStatus);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* this function can also be called within pre-initialized state */
  if (Dem_InitializationState == DEM_UNINITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_ResetEventDebounceStatus, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_ResetEventDebounceStatus, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_ResetEventDebounceStatus, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_ResetEventDebounceStatus, DEM_E_WRONG_CONFIGURATION);
  }
  else if ( (DebounceResetStatus != DEM_DEBOUNCE_STATUS_FREEZE) &&
            (DebounceResetStatus != DEM_DEBOUNCE_STATUS_RESET) )
  {
    DEM_REPORT_ERROR(DEM_SID_ResetEventDebounceStatus, DEM_E_PARAM_DATA);
  }
  else if (Dem_GbiDebounceAlgo(EventId) == DEM_DEBOUNCE_MONITOR)
  {
    DEM_REPORT_ERROR(DEM_SID_ResetEventDebounceStatus, DEM_E_PARAM_CONFIG);
  }
#if (DEM_NUM_DEBOUNCE_COUNTER_PERM > 0U)
  else if (Dem_DebounceCounterWithNvStorageDuringPreInit(EventId) == TRUE)
  {
    /* !LINKSTO Dem.DebounceCounters.StartupDET,1 */
    DEM_REPORT_ERROR(DEM_SID_ResetEventDebounceStatus, DEM_E_WRONG_CONDITION);
  }
#endif
  else
#endif /* DEM_DEV_ERROR_DETECT */

#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
  if (Dem_GbiEvAvailable(EventId) == FALSE)
  {
    /* event is disabled so reporting shall be skipped */
  }
  else
#endif
  {
#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U)
    Dem_EventIdType NextEventId, LastEventId = DEM_EVENT_ID_INVALID;

    /* !LINKSTO Dem.MultiEventTriggering.ResetEventDebounceStatus,1 */
    /* check if reported event is a multi-triggering master and reset the
     * debounce status for all slaves */
    if (Dem_GetMultiEventTriggering(EventId) != NULL_PTR)
    {
      /* ENTER critical section to protect Dem_Debounce[Counter|Time|Frequency]Status
       * as the function is reentrant */
      DEM_ENTER_EXCLUSIVE_AREA();

      do
      {
        /* get the next event of the MultiEventTriggering configuration */
        NextEventId = Dem_FindNextDependentEvent(EventId, E_NOT_OK, &LastEventId);

#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
        if ( (NextEventId != DEM_EVENT_ID_INVALID) &&
             (Dem_GbiEvAvailable(NextEventId) == TRUE) )
#else
        if (NextEventId != DEM_EVENT_ID_INVALID)
#endif
        {
          Dem_ApplyDebounceStatus(NextEventId, DebounceResetStatus);
        }
      } while (NextEventId != DEM_EVENT_ID_INVALID);

      /* LEAVE critical section  */
      DEM_EXIT_EXCLUSIVE_AREA();

    }
    else
#endif
    {
      /* ENTER critical section */
      DEM_ENTER_EXCLUSIVE_AREA();

      Dem_ApplyDebounceStatus(EventId, DebounceResetStatus);

      /* LEAVE critical section  */
      DEM_EXIT_EXCLUSIVE_AREA();
    }

    Result = E_OK;
  }

  DBG_DEM_RESETEVENTDEBOUNCESTATUS_EXIT(Result, EventId, DebounceResetStatus);

  return Result;
}
#endif  /*(DEM_INTERNAL_DEBOUNCE_SUPPORT == STD_ON)*/

/*------------------[Dem_PrestoreFreezeFrame]-------------------------------*/

/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_PrestoreFreezeFrame(
  Dem_EventIdType EventId)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_PRESTOREFREEZEFRAME_ENTRY(EventId);
#if ((DEM_DEV_ERROR_DETECT != STD_ON) && (DEM_MAX_NUMBER_PRESTORED_FF == 0U))
  TS_PARAM_UNUSED(EventId);
#endif

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_PrestoreFreezeFrame, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_PrestoreFreezeFrame, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_PrestoreFreezeFrame, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_PrestoreFreezeFrame, DEM_E_WRONG_CONFIGURATION);
  }
  else if (Dem_GbiEnablePrestorage(EventId) == FALSE)
  {
    DEM_REPORT_ERROR(DEM_SID_PrestoreFreezeFrame, DEM_E_WRONG_CONFIGURATION);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
  if (Dem_GbiEvAvailable(EventId) == FALSE)
  {
    /* event is disabled so the prestore shall be skipped */
    /* E_NOT_OK return value remains */
  }
  else
#endif
  {
#if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
#if (DEM_DET_RUNTIME_CHECK == STD_ON)
    Std_ReturnType StoreFFResult;
#endif
    /* there are maximal as much PFFs as events */
    Dem_EventIdType PFFIndex = Dem_GetPFFIndex(EventId);
    Dem_EntryDataPtrType PFFEntryData = Dem_GetPFFEntryDataPtr(EventId);
    Dem_SizeEntryDataType CalcFFSize = 0U;

    /*
     * ENTER critical section to protect Dem_PFFEntryValid and PFFEntryData
     */
    DEM_ENTER_EXCLUSIVE_AREA();

    /* before filling, mark prestored freeze frame as invalid, to avoid
     * corrupt data reads */
    DEM_CLR_BIT_IN_ARRAY(Dem_PFFEntryValid, PFFIndex);

    /*
     * LEAVE critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();

    /* store new FF to the reserved PFF-entry-space of the given event Id
     * and can not be called with invalid freeze frame class because
     * it is checked in DET check */

    /* !LINKSTO dsn.Dem.ExternalDataCapturing.CapturePrestoredFFData,1 */
#if (DEM_DET_RUNTIME_CHECK == STD_ON)
    StoreFFResult = Dem_CaptureFF(
                      DEM_REGULAR_FF,
                      &Dem_FFClass[Dem_GbiFFClassIdx(EventId)],
                      EventId,
                      DEM_EVENT_STATUS_FAILED,
                      PFFEntryData,
                      &CalcFFSize);
#else
    (void)Dem_CaptureFF(
      DEM_REGULAR_FF,
      &Dem_FFClass[Dem_GbiFFClassIdx(EventId)],
      EventId,
      DEM_EVENT_STATUS_FAILED,
      PFFEntryData,
      &CalcFFSize);
#endif

    /*
     * ENTER critical section to protect Dem_PFFEntryValid and PFFEntryData
     */
    DEM_ENTER_EXCLUSIVE_AREA();

    /* mark prestored freeze frame as filled */
    DEM_SET_BIT_IN_ARRAY(Dem_PFFEntryValid, PFFIndex);
    /*
     * LEAVE critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();

#if (DEM_DET_RUNTIME_CHECK == STD_ON)
    /* !LINKSTO Dem.SWS_Dem_00463,1 */
    if (StoreFFResult == DEM_E_NODATAAVAILABLE)
    {
      /* !LINKSTO Dem.DetReport.RuntimeErrorsReporting,1 */
      /* report the DET error that occurred on reading FF data */
      DEM_REPORT_RUNTIME_ERROR(DEM_SID_PrestoreFreezeFrame, DEM_E_NODATAAVAILABLE);
    }
#endif
    Result = E_OK;
#endif /* (DEM_MAX_NUMBER_PRESTORED_FF > 0U) */
  }

  DBG_DEM_PRESTOREFREEZEFRAME_EXIT(Result, EventId);
  return Result;
}

/*------------------[Dem_ClearPrestoredFreezeFrame]-------------------------*/

/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_ClearPrestoredFreezeFrame(
  Dem_EventIdType EventId)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_CLEARPRESTOREDFREEZEFRAME_ENTRY(EventId);

#if ((DEM_DEV_ERROR_DETECT != STD_ON) && (DEM_MAX_NUMBER_PRESTORED_FF == 0U))
  TS_PARAM_UNUSED(EventId);
#endif

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_ClearPrestoredFreezeFrame, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_ClearPrestoredFreezeFrame, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_ClearPrestoredFreezeFrame, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_ClearPrestoredFreezeFrame, DEM_E_WRONG_CONFIGURATION);
  }
  else if (Dem_GbiEnablePrestorage(EventId) == FALSE)
  {
    DEM_REPORT_ERROR(DEM_SID_ClearPrestoredFreezeFrame, DEM_E_WRONG_CONFIGURATION);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
  if (Dem_GbiEvAvailable(EventId) == FALSE)
  {
    /* event is disabled so the clearing shall be skipped */
    /* E_NOT_OK return value remains */
  }
  else
#endif
  {
#if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
    Dem_EventIdType PFFIndex = Dem_GetPFFIndex(EventId);
    /*
     * ENTER critical section
     */
    DEM_ENTER_EXCLUSIVE_AREA();

    /* mark prestored freeze frame as empty */
    DEM_CLR_BIT_IN_ARRAY(Dem_PFFEntryValid, PFFIndex);

    /*
     * LEAVE critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();

    Result = E_OK;
#endif
  }

  DBG_DEM_CLEARPRESTOREDFREEZEFRAME_EXIT(Result, EventId);
  return Result;
}
#endif /* ( (DEM_INCLUDE_RTE == STD_OFF) || (DEM_NUM_SWC_EVENTS > 0) ) */

/*------------------[Dem_SetOperationCycleState]----------------------------*/

#if (DEM_OPERATION_CYCLE_PROCESSING == DEM_PROCESS_OPCYC_STATE) || \
    (DEM_OPERATION_CYCLE_PROCESSING == DEM_PROCESS_OPCYC_RESTART)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_SetOperationCycleState(
  Dem_OperationCycleIdType    OperationCycleId,
  Dem_OperationCycleStateType CycleState)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_SETOPERATIONCYCLESTATE_ENTRY(OperationCycleId, CycleState);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetOperationCycleState, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_SetOperationCycleState, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (OperationCycleId >= DEM_NUM_OPCYCLES)
  {
    DEM_REPORT_ERROR(DEM_SID_SetOperationCycleState, DEM_E_WRONG_CONFIGURATION);
  }
  else if ( (CycleState != DEM_CYCLE_STATE_START) &&
            (CycleState != DEM_CYCLE_STATE_END) )
  {
    DEM_REPORT_ERROR(DEM_SID_SetOperationCycleState, DEM_E_PARAM_DATA);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    CONSTP2VAR(Dem_OperationCycleStateType, AUTOMATIC, DEM_VAR_CLEARED)
      StoredCycleState = &DEM_OPCYCLESTATE[OperationCycleId];

    /* end previous cycle on transition: START->END or START->START */
    /* end previous cycle if stored cycle state is START, only possible
     * transitions are: START->END or START->START */
    if (*StoredCycleState == DEM_CYCLE_STATE_START)
    {
      /* 1st step: prepare the gate entry indirectly when aging or
       * update of the OpCycleCtrs is processed */
      Dem_OpCycleProcessCycleEnd(OperationCycleId);
    }

    /* start new cycle on transition: START->START or END->START */
    if (CycleState == DEM_CYCLE_STATE_START)
    {
      Dem_OpCycleProcessCycleStart(OperationCycleId);
    }

    /* switch stored state to new state */
    *StoredCycleState = CycleState;

    /* request store to update event data after state
     * modification opearation cycle */
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    /* 2nd step: trigger the requests to the NvM module
     * once for all events for performance reasons
     * always called outside the critical section */
    Dem_CheckForTriggerNvmWriteGateEntry();
#endif

    Result = E_OK;
  }

  DBG_DEM_SETOPERATIONCYCLESTATE_EXIT(Result, OperationCycleId, CycleState);
  return Result;
}

#if (DEM_OPERATION_CYCLE_PROCESSING == DEM_PROCESS_OPCYC_RESTART)
FUNC(Std_ReturnType, DEM_CODE) Dem_RestartOperationCycle(
  uint8    OperationCycleId)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_RESTARTOPERATIONCYCLE_ENTRY(OperationCycleId);

  /* !LINKSTO dsn.Dem.OperationCycle.RestartOperationCycle.Wrapper,1 */
  Result =  Dem_SetOperationCycleState(OperationCycleId, DEM_CYCLE_STATE_START);

  DBG_DEM_RESTARTOPERATIONCYCLE_EXIT(Result, OperationCycleId);
  return Result;
}
#endif /* (DEM_OPERATION_CYCLE_PROCESSING == DEM_PROCESS_OPCYC_RESTART) */
#endif /* (DEM_OPERATION_CYCLE_PROCESSING == DEM_PROCESS_OPCYC_STATE) ||
    (DEM_OPERATION_CYCLE_PROCESSING == DEM_PROCESS_OPCYC_RESTART) */

/*------------------[Dem_SetCycleQualified]---------------------------------*/
#if (DEM_DEFAULT_ASR_SERVICE_API == DEM_SERVICE_API_ASR2011)
FUNC(Std_ReturnType, DEM_CODE) Dem_SetCycleQualified(
  uint8                    OperationCycleId)
#else
FUNC(Std_ReturnType, DEM_CODE) Dem_SetCycleQualified(
  Dem_OperationCycleIdType OperationCycleId)
#endif
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_SETCYCLEQUALIFIED_ENTRY(OperationCycleId);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetCycleQualified, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_SetCycleQualified, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
#endif
#if (DEM_OPCYC_OBD_DCY_USED == STD_ON)
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  else if (OperationCycleId != DEM_OPCYC_OBD_DCY_ID)
  {
    /* !LINKSTO Dem.OperationCycleQualification.SetCycleQualified.Det,1 */
    DEM_REPORT_ERROR(DEM_SID_SetCycleQualified, DEM_E_WRONG_CONFIGURATION);
  }
  else if (DEM_OPCYCLESTATE[OperationCycleId] == DEM_CYCLE_STATE_END)
  {
    DEM_REPORT_ERROR(DEM_SID_SetCycleQualified, DEM_E_WRONG_CONDITION);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    boolean ProcessEvents = FALSE;

    DEM_ENTER_EXCLUSIVE_AREA();

    if (Dem_NvData.Dem_OpCycleDCYIsQualified == FALSE)
    {
      ProcessEvents = TRUE;
      Dem_NvData.Dem_OpCycleDCYIsQualified = TRUE;

#if ( (DEM_NUM_FAILURECYCLES > 0U) && \
      (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON) )
      /* !LINKSTO Dem.OperationCycleQualification.ProcessConfirmation,2 */
      /* trigger fault confirmation processing for events assigned to the DCY */
      Dem_DoProcessFaultConfirmation = TRUE;
#endif
    }

    DEM_EXIT_EXCLUSIVE_AREA();

    if (ProcessEvents == TRUE)
    {
#if ( ((DEM_NUM_FAILURECYCLES == 0U) || (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF)) || \
      ((DEM_NUM_INDICATOR_LINKS > 0U) && (defined DEM_MIL_ID)) )

      Dem_EventIdType EventId = 1U;

#if ( (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON) && \
      ( (DEM_NUM_FAILURECYCLES == 0U) || \
        (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF) || \
        ( (DEM_NUM_INDICATOR_LINKS > 0U) && (defined DEM_MIL_ID) && \
          (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) )) )
      boolean TriggerNvmWrite = FALSE;
#endif

      /* CDTC and/or MIL update has to be checked */

      /* !LINKSTO dsn.Dem.ProcessEventsPerCycle.SplitEventsPerCriticalSection,1 */
      /* check all DCY events */
      /* Deviation TASKING-2 */
      while (EventId <= DEM_MAX_EVENTID)
      {
        boolean StatusChanged = FALSE;
#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
        uint8 EventIdLastIdx = 0U;
        uint8 Index;
        Dem_DTCMaskChangedType DTCStatusChangedData[DEM_MAX_NUM_EVENTS_PER_CRITICAL_SECTION];
        Dem_DTCMaskChangedPtrType CurrentDTCStatusChangedData;
#endif

        /*
         * ENTER critical section to protect the event status and memory
         *       call-context: Rte (Task)
         */
        DEM_ENTER_EXCLUSIVE_AREA();

        do
        {
#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
          CurrentDTCStatusChangedData = &DTCStatusChangedData[EventIdLastIdx];
          CurrentDTCStatusChangedData->OldStatusMask = DEM_DTC_STATUS_MASKS[EventId];
#endif

#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
          if (Dem_GbiEvAvailable(EventId) == FALSE)
          {
            /* event is disabled so confirmation shall be skipped */
          }
          else
#endif
          {
            /* check only driving cycle events */
            if (Dem_GbiOpCycleIdx(EventId) == DEM_OPCYC_OBD_DCY_ID)
            {

#if ( (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON) && \
      ( (DEM_NUM_FAILURECYCLES == 0U) || \
        (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF) || \
        ( (DEM_NUM_INDICATOR_LINKS > 0U) && (defined DEM_MIL_ID) && \
          (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) )) )
              boolean EntryUpdated = Dem_ProcessDCYQualificationPerEvent(
                                       EventId,
                                       &StatusChanged);

              if (EntryUpdated == TRUE)
              {
                TriggerNvmWrite = TRUE;
              }
#else
              (void)Dem_ProcessDCYQualificationPerEvent(
                      EventId,
                      &StatusChanged);
#endif
            }
          }

#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) || (DEM_NUM_CMB_DTCS > 0U)
          if (StatusChanged == TRUE)
          {
#if (DEM_NUM_CMB_DTCS > 0U)
            const Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
            /* for combined event set a flag for its index for later status update */
            if (DEM_IS_DTC_COMBINED(DTCConfIdx))
            {
              /* set a flag corresponding to this EventId */
              DEM_SET_BIT_IN_ARRAY(Dem_CmbDTCFlags, DTCConfIdx);
            }
#endif
#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
            CurrentDTCStatusChangedData->NewStatusMask = DEM_DTC_STATUS_MASKS[EventId];

            if (CurrentDTCStatusChangedData->OldStatusMask !=
                CurrentDTCStatusChangedData->NewStatusMask)
            {
              CurrentDTCStatusChangedData->EventId = EventId;
              ++EventIdLastIdx;
            }
#endif
          }
#endif
          ++EventId;
        }
        /* Deviation TASKING-2 */
        while ( ((EventId % DEM_MAX_NUM_EVENTS_PER_CRITICAL_SECTION) != 0U) &&
                (EventId <= DEM_MAX_EVENTID)
              );
        /* loop necessary to condition the number of events processed in the one critical section */

        /*
         * LEAVE critical section
         */
        DEM_EXIT_EXCLUSIVE_AREA();

#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
        for (Index = 0U; Index < EventIdLastIdx; Index++)
        {
          CurrentDTCStatusChangedData = &DTCStatusChangedData[Index];

          /* notify application if event status has been changed */
          Dem_CbTriggerOnEventStatus(CurrentDTCStatusChangedData->EventId,
                                     CurrentDTCStatusChangedData->OldStatusMask,
                                     CurrentDTCStatusChangedData->NewStatusMask);
        }
#endif
      }
#if (DEM_NUM_CMB_DTCS > 0U)
      /* update the combined DTC status of changed combined DTCs.*/
      Dem_InitAllCmbDTCStatus(FALSE);
#endif

#if ( (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON) && \
      ( ((DEM_NUM_FAILURECYCLES == 0U) || \
           (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF)) || \
        ( (DEM_NUM_INDICATOR_LINKS > 0U) && (defined DEM_MIL_ID) && \
          (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) )) )
      if (TriggerNvmWrite == TRUE)
      {
        /* 2nd step: trigger the requests to the NvM module once
         * for all events. For performance reasons
         * always called outside the critical section */
        Dem_CheckForTriggerNvmWriteGateEntry();
      }
#endif
#endif /* ( (!((DEM_NUM_FAILURECYCLES > 0U) && (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON))) ||
        *   ((DEM_NUM_INDICATOR_LINKS > 0U) && (defined DEM_MIL_ID)) ) */
    }
    Result = E_OK;
  }
#endif /* DEM_OPCYC_OBD_DCY_USED */

#if ((DEM_OPCYC_OBD_DCY_USED == STD_OFF) || (DEM_DEV_ERROR_DETECT == STD_OFF))
  TS_PARAM_UNUSED(OperationCycleId);
#endif

  DBG_DEM_SETCYCLEQUALIFIED_EXIT(Result, OperationCycleId);

  return Result;
}

#if ((DEM_OPCYC_OBD_DCY_USED == STD_ON) && \
    ( ((DEM_NUM_FAILURECYCLES == 0U) || (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF)) || \
      ((DEM_NUM_INDICATOR_LINKS > 0U) && (defined DEM_MIL_ID)) ) )
STATIC FUNC(boolean, DEM_CODE)Dem_ProcessDCYQualificationPerEvent(
  Dem_EventIdType EventId,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC) StatusChanged)
{
  boolean EntryFound = FALSE;
  boolean EvStatusChanged = FALSE;

#if ( ( ( (DEM_NUM_FAILURECYCLES == 0U) || \
          (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF) ) && \
        ( (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON) || \
          ( (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) && \
            (DEM_VCC_OCC5_USED == STD_ON) ) ) ) || \
      ( (DEM_NUM_INDICATOR_LINKS > 0U) && (defined DEM_MIL_ID) && \
        (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) ) )

  /* EvMemEntry/EvMemEntryIdx is needed when:
   *   - immediate storage is enabled and CDTC is updated, to immediately store
   *     the CDTCFlag in the entry OR
   *   - DEM_OCC5 is updated in the entry OR
   *   - DEM_SI30 is updated in the entry
   */
  Dem_EventMemoryEntryPtrType EvMemEntry = NULL_PTR;
  Dem_SizeEvMemEntryType EvMemEntryIdx = 0U;
#endif

  DBG_DEM_PROCESSDCYQUALIFICATIONPEREVENT_ENTRY(EventId,
                                                StatusChanged);

#if ( (DEM_NUM_FAILURECYCLES == 0U) || \
      (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF) )
  /* !LINKSTO Dem.OperationCycleQualification.ProcessConfirmation,2 */
  /* if CDTC is not handled asynchronously */
  if (!DEM_IS_EV_ST_BIT_CDTC_SET(EventId))
  {
    /* check if event reached threshold while driving cycle was not yet qualified */
    if (Dem_CheckConfirmedDrivingCycle(EventId) == TRUE)
    {
      /* set CDTC bit for the received event */
#if ( (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON) || \
      ( (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) && \
        (DEM_VCC_OCC5_USED == STD_ON) ) )
      EntryFound = Dem_SearchForEntry(EventId, &EvMemEntry, &EvMemEntryIdx);
#endif

      /* Dem_CheckConfirmedDrivingCycle() already checks that there is an existing
       * event entry.
       * Note that DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT is set to STD_ON
       * here, since DEM_EXTENDED_DATA_CAPTURE is set to DEM_TRIGGER_ON_FDC_THRESHOLD
       * (This is guaranteed by a configuration check.) */

      /* sets the confirmed status bit */
      DEM_SET_EV_ST_MASK(EventId, DEM_UDS_STATUS_CDTC);

      EvStatusChanged = TRUE;

#if (DEM_GET_DTCBYOCCURRENCETIME_SUPPORT == STD_ON)
      /* store event to be detected confirmed DTC occurrence kind */
      Dem_UpdateEventIdOccurKinds(EventId,
        DEM_FIRST_DET_CONFIRMED_DTC, DEM_MOST_REC_DET_CONFIRMED_DTC);
#endif
    }
  }
#endif /*( (DEM_NUM_FAILURECYCLES == 0U) || \
           (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF) ) */
#if (DEM_NUM_INDICATOR_LINKS > 0U) && (defined DEM_MIL_ID)
  {
    /* check if WIR (MIL) has to be set */
    Dem_IndicatorIdxType IndicatorIdx;

    /* !LINKSTO Dem.OperationCycleQualification.ProcessMIL,2 */
    if (Dem_IsMILEvent(EventId, &IndicatorIdx) == TRUE)
    {
#if (DEM_CALIBRATION_SUPPORT == STD_ON)
      const Dem_IndicatorIdType IndicatorId = DEM_MIL_ID;
      CONSTP2CONST(Dem_IndicatorClassType, AUTOMATIC, DEM_CONST) IndicatorClass =
        &Dem_IndicatorClasses[IndicatorIdx];
      const Dem_IndicatorCycleCounterType FailureThreshold =
        DEM_GET_CALIBRATED_FAILURECYCLE_THRESHOLD(EventId, IndicatorClass);
      /* even if CounterDataIdx is of smaller type than EventId the cast is ok
       * because size of Dem_CounterDataIdxType depends on the amount of events in
       * the system */
      const Dem_CounterDataIdxType CounterDataIdx = (Dem_CounterDataIdxType)(EventId);
#else
      /* Deviation TASKING-9 */
      const Dem_CounterDataIdxType CounterDataIdx = (Dem_CounterDataIdxType)IndicatorIdx;
      const Dem_FailureCycleCounterInfoIdxType FailureCycleCounterInfoIdx =
        Dem_IndicatorLink[IndicatorIdx].FailureCycleCounterInfoIdx;
      const Dem_IndicatorIdType IndicatorId = DEM_INDICATOR_DEFAULT_COUNTER;
      const Dem_IndicatorCycleCounterType FailureThreshold =
        Dem_FailureCycleCounterInfo[FailureCycleCounterInfoIdx].Threshold;
#endif
      /* skip the DCY Qualification for zero-trip events/indicators */
      if (FailureThreshold != 0U)
      {
        if ( !DEM_IS_BIT_SET_IN_ARRAY(DEM_INDICATOR_CYC_COUNTER_ROLE[IndicatorId], CounterDataIdx))
        {
          /* if counter role is DEM_INDICATORCOUNTER_ROLE_FAILURE_CYCLE_COUNTER ... */
          /* Deviation TASKING-9 */
          if (Dem_ProcessIndicatorFailureCycleCounter(IndicatorIdx, EventId, FALSE) == TRUE)
          {
            /* Note that Dem_ProcessIndicatorFailureCycleCounter() will set the
            * WIR.C-bit, if needed
            */
#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)

            Dem_SetWIRSLCForFoundEntry(&EvMemEntry, &EvMemEntryIdx, &EntryFound, EventId);
#endif
            /* update event status */
            DEM_SET_EV_ST_MASK(EventId, DEM_UDS_STATUS_WIR);

#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)
            /* !LINKSTO Dem_OBD_0021,3 */
            /* !LINKSTO dsn.Dem.OBD.PermanentMemory.EventCombination.IdenticalObdDTC.Storage,1 */
            (void)Dem_PermanentMemoryAddEntry(EventId);
#endif

            EvStatusChanged = TRUE;
          }
        }
      }
    }
  }
#endif /* ((DEM_NUM_INDICATOR_LINKS > 0U) && (defined DEM_MIL_ID) */

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON) && \
    ( ( (DEM_NUM_FAILURECYCLES == 0U) || \
        (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF) )  || \
      ( (DEM_NUM_INDICATOR_LINKS > 0U) && (defined DEM_MIL_ID) && \
        (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) ) )
  /* Check for immediate storage, if entry was updated because of
   *   - CDTCFlag/DEM_OCC5 and/or
   *   - DEM_SI30 */
  if (EntryFound == TRUE)
  {
    /* !LINKSTO dsn.Dem.ImmediateStorage.StatusUpdate.CDTC,1 */
    /* !LINKSTO dsn.Dem.VCC.EventMemoryEntryChanged,4 */
    Dem_CheckForImmediateEntryStorage(EventId,
                                      EvMemEntry,
                                      EvMemEntryIdx,
                                      DEM_NVM_NO_FORCE);
  }
#endif

  *StatusChanged = EvStatusChanged;

  DBG_DEM_PROCESSDCYQUALIFICATIONPEREVENT_EXIT(EntryFound,
                                               EventId,
                                               StatusChanged);
  return EntryFound;
}
#endif

/*------------------[Dem_SetOperationCycleCntValue]-------------------------*/

/* stub is currently only supported without RTE-usage since the related condition
 * cannot be enabled so that the RTE will enable the port for this API */
#if (DEM_INCLUDE_RTE == STD_OFF)
FUNC(Std_ReturnType, DEM_CODE) Dem_SetOperationCycleCntValue(
  uint8 OperationCycleId,
  uint8 CounterValue)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_SETOPERATIONCYCLECNTVALUE_ENTRY(OperationCycleId, CounterValue);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetOperationCycleCntValue, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_SetOperationCycleCntValue, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (OperationCycleId >= DEM_NUM_OPCYCLES)
  {
    DEM_REPORT_ERROR(DEM_SID_SetOperationCycleCntValue, DEM_E_WRONG_CONFIGURATION);
  }
  else
#else
  TS_PARAM_UNUSED(OperationCycleId);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* function not fully implemented yet.
     * implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(CounterValue);
  }

  DBG_DEM_SETOPERATIONCYCLECNTVALUE_EXIT(
    Result, OperationCycleId, CounterValue);
  return Result;
}
#endif

/*------------------[Dem_SetAgingCycleState]--------------------------------*/

#if ((DEM_AGINGCYCLE_COUNTER_PROCESSING == DEM_PROCESS_AGINGCTR_INTERN) && \
    (DEM_NUM_AGINGCYCLES > 0U))
FUNC(Std_ReturnType, DEM_CODE) Dem_SetAgingCycleState(uint8 AgingCycleId)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_SETAGINGCYCLESTATE_ENTRY(AgingCycleId);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetAgingCycleState, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_SetAgingCycleState, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (AgingCycleId >= DEM_NUM_AGINGCYCLES)
  {
    DEM_REPORT_ERROR(DEM_SID_SetAgingCycleState, DEM_E_WRONG_CONFIGURATION);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
#if (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD)
    Dem_EventIdType EvId;

    /* check all events */
    for (EvId = 1U; EvId <= DEM_MAX_EVENTID; ++EvId)
    {
#if (DEM_NUM_CMB_DTCS > 0U)
      if (DEM_GET_MASTER_EVID(EvId) == EvId)
#endif
      {
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
#if (DEM_NUM_CMB_DTCS > 0U)
        if (Dem_IsAnyEvAvailable(EvId) == TRUE)
#else
        if (Dem_GbiEvAvailable(EvId) == TRUE)
#endif
#endif
      {
        /* in case of calibration support, aging can be disabled; otherwise
         * aging is always enabled, if corresponding aging cycle is set */
#if (DEM_CALIBRATION_WITHOUTEVCOMB_SUPPORT == STD_ON)
        if (DEM_AGING_ALLOWED(EvId))
#endif
        {
          /* only for events of this aging cycle */
          if (Dem_GbiAgingCycleIdx(EvId) == AgingCycleId)
          {
#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
              const Dem_DTCStatusMaskType OldDTCStatusMask =
                DEM_DTC_STATUS_MASKS[EvId];
              Dem_DTCStatusMaskType NewDTCStatusMask;
#endif

              boolean UpdateAgingCounterCriteriaFulfilled;
              uint8 AgingCriteriaMask;

#if (DEM_NUM_CMB_DTCS > 0U)
              boolean DTCStatusChanged = FALSE;
              Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EvId);
              Dem_EventStatusExtendedType OldCombinedStatus = 0U;
              Dem_EventStatusExtendedType NewCombinedStatus = 0U;
#endif

#if (DEM_AGING_REQUIRES_TESTED_CYCLE_SET_AGING_CYCLE_STATE == STD_ON)
              /* initialize the mask for the set aging cycle check */
              /* process aging algorithm only if the event was reported only as passed
               * this operation cycle: both TFTOC and TNCTOC bits are not set */
              /* !LINKSTO dsn.Dem.InternalAging.DemAgingRequiresTestedCycleSetAgingCycleState.Enabled,1 */
              AgingCriteriaMask = DEM_UDS_STATUS_TFTOC | DEM_UDS_STATUS_TNCTOC;
#else
              /* process aging algorithm only, if the event is entered and the
               * current status is passed (Dem.ASR40.SWS_Dem_00489).
               * TF bit is checked in order to ensure that the aging counter incrementation is
               * independent of a previously reported failure and independent of operation cycle */
              /* !LINKSTO dsn.Dem.InternalAging.DemAgingRequiresTestedCycleSetAgingCycleState.Disabled,2 */
              AgingCriteriaMask = DEM_UDS_STATUS_TF;
#endif

              /* if aging based on healing completion feature is enabled, additionally the WIR
               * bit needs to be checked for the aging process to occur */
              /* !LINKSTO dsn.Dem.InternalAging.DemAgingBasedOnHealingCompletionSupport,1 */
#if (DEM_AGING_BASED_ON_HEALING_COMPLETION_SUPPORT == STD_ON)
              AgingCriteriaMask |= DEM_UDS_STATUS_WIR;
#endif

              /* 1st step: prepare the gate entry indirectly when aging
               * counter is processed */
#if (DEM_NUM_CMB_DTCS > 0U)
              if (DEM_IS_DTC_COMBINED(DTCConfIdx))
              {
                UpdateAgingCounterCriteriaFulfilled = !DEM_IS_CMB_ST_BIT_SET_IN_DTC(DTCConfIdx, AgingCriteriaMask);
              }
              else
#endif
              {
                UpdateAgingCounterCriteriaFulfilled = !DEM_IS_ANY_EV_ST_BIT_SET(EvId, AgingCriteriaMask);
              }

              if (UpdateAgingCounterCriteriaFulfilled == TRUE)
              {
                /* process aging counter (may lead to status change) */
#if (DEM_NUM_CMB_DTCS > 0U)
                DTCStatusChanged = Dem_UpdateAgingCounter(EvId);
#else
                (void)Dem_UpdateAgingCounter(EvId);
#endif
              }
#if (DEM_NUM_CMB_DTCS > 0U)
              if ((DEM_IS_DTC_COMBINED(DTCConfIdx)) && (DTCStatusChanged == TRUE))
              {
                /*
                 * ENTER critical section
                 */
                DEM_ENTER_EXCLUSIVE_AREA();

                OldCombinedStatus = Dem_CmbDTCStatus[DTCConfIdx];
                NewCombinedStatus = Dem_CalculateCmbDTCStatus(DTCConfIdx, FALSE);
                /*
                 * EXIT critical section
                 */
                DEM_EXIT_EXCLUSIVE_AREA();

                Dem_InternalCheckOnCmbDTCStatusChange(EvId, OldCombinedStatus, NewCombinedStatus);
              }
#endif /* DEM_NUM_CMB_DTCS */
#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
              NewDTCStatusMask = DEM_DTC_STATUS_MASKS[EvId];
              if (OldDTCStatusMask != NewDTCStatusMask)
              {
                /* notify application if event status has changed */
                Dem_CbTriggerOnEventStatus(EvId, OldDTCStatusMask, NewDTCStatusMask);
              }
#endif
            }
          }
        }
      }
    }

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    /* 2nd step: trigger the requests to the NvM module once
     * for all events for performance reasons
     * always called outside the critical section */
    Dem_CheckForTriggerNvmWriteGateEntry();
#endif
#else /* DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD */
    TS_PARAM_UNUSED(AgingCycleId);
#endif /* DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD */
    Result = E_OK;
  }

  DBG_DEM_SETAGINGCYCLESTATE_EXIT(Result, AgingCycleId);
  return Result;
}
#endif /* (DEM_AGINGCYCLE_COUNTER_PROCESSING == DEM_PROCESS_AGINGCTR_INTERN) && \
          (DEM_NUM_AGINGCYCLES > 0U) */

/*------------------[Dem_SetAgingCycleCounterValue]-------------------------*/

/* stub is currently only supported without RTE-usage since the related condition
 * cannot be enabled so that the RTE will enable the port for this API */
#if (DEM_INCLUDE_RTE == STD_OFF)
FUNC(Std_ReturnType, DEM_CODE) Dem_SetAgingCycleCounterValue(
  uint8 CounterValue)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_SETAGINGCYCLECOUNTERVALUE_ENTRY(CounterValue);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetAgingCycleCounterValue, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_SetAgingCycleCounterValue, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* function not fully implemented yet.
     * implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(CounterValue);
  }

  DBG_DEM_SETAGINGCYCLECOUNTERVALUE_EXIT(Result, CounterValue);
  return Result;
}
#endif /* DEM_INCLUDE_RTE == STD_OFF */

/*------------------[Dem_SetWIRStatus]--------------------------------------*/
#if (DEM_USER_CTRL_WIR_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_SetWIRStatus(
  Dem_EventIdType EventId,
  boolean WIRStatus)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_SETWIRSTATUS_ENTRY(EventId, WIRStatus);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetWIRStatus, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_SetWIRStatus, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_SetWIRStatus, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_SetWIRStatus, DEM_E_WRONG_CONFIGURATION);
  }
  else if ( (WIRStatus != FALSE) && (WIRStatus != TRUE) )
  {
    DEM_REPORT_ERROR(DEM_SID_SetWIRStatus, DEM_E_PARAM_DATA);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
    if (Dem_GbiEvAvailable(EventId) == TRUE)
#endif
    {
#if ( (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) || \
      (DEM_NUM_CMB_DTCS > 0U) )
      P2CONST(Dem_DTCStatusMaskType, AUTOMATIC, DEM_VAR) DTCStatusMaskPtr
                                            = &DEM_DTC_STATUS_MASKS[EventId];
      Dem_DTCStatusMaskType OldDTCStatusMask = 0;
      Dem_DTCStatusMaskType NewDTCStatusMask = 0;
#endif
#if (DEM_NUM_CMB_DTCS > 0U)
      Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
      Dem_EventStatusExtendedType OldCombinedStatus = 0U;
      Dem_EventStatusExtendedType NewCombinedStatus = 0U;
#endif
      /* !LINKSTO Dem.SWS_Dem_00836,1 */
      /* check the DTC settings */
      if (DEM_DTC_SETTING_ALLOWED(EventId) != FALSE)
      {
        /*
         * ENTER critical section to protect consistency of DTC Status Mask
         *       call-context: Rte (Task), Dem (Task)
         */
        DEM_ENTER_EXCLUSIVE_AREA();

#if ( (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) || \
      (DEM_NUM_CMB_DTCS > 0U) )
        OldDTCStatusMask = *DTCStatusMaskPtr;
#endif
        /* !LINKSTO Dem.SWS_Dem_00833,1 */
        if (WIRStatus == TRUE)
        {
          /* store the request in array */
          DEM_SET_BIT_IN_ARRAY(Dem_UserCtrlWIRStatus, EventId);

          /* update event status mask */
          /* set DTC WIR status bit */
          DEM_SET_EV_ST_MASK(EventId, DEM_UDS_STATUS_WIR);
        }
        else /* FALSE is the only possible value at this point */
        {
          if (DEM_IS_EV_ST_BIT_WIR_SET(EventId))
          {
            /* store the request in array */
            DEM_CLR_BIT_IN_ARRAY(Dem_UserCtrlWIRStatus, EventId);

#if (DEM_NUM_INDICATOR_LINKS > 0U)
            /* !LINKSTO Dem.SWS_Dem_00834,1 */
            /* reset only if no indicators connected to the event are enabled */
            if (Dem_CheckWIROffCriteriaFulfilled(EventId) == TRUE)
#endif
            {
              /* clear DTC WIR status bit */
              DEM_CLR_EV_ST_MASK(EventId, DEM_UDS_STATUS_WIR);
            }
          }
          else
          {
            /* no updates are required for the current event */
          }
        }

#if ( (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) || \
      (DEM_NUM_CMB_DTCS > 0U) )
        NewDTCStatusMask = *DTCStatusMaskPtr;
#endif
        /*
         * EXIT critical section
         */
        DEM_EXIT_EXCLUSIVE_AREA();

        /* the request is accepted */
        Result = E_OK;
      }
      else
      {
        /* return E_NOT_OK */
      }

#if ( (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) || \
      (DEM_NUM_CMB_DTCS > 0U) )
      if (OldDTCStatusMask != NewDTCStatusMask)
      {
#if (DEM_NUM_CMB_DTCS > 0U)
        /*
         * ENTER critical section
         */
        DEM_ENTER_EXCLUSIVE_AREA();
        /* if event is combined, update the combined DTC status */
        if (DEM_IS_DTC_COMBINED(DTCConfIdx))
        {
          OldCombinedStatus = Dem_CmbDTCStatus[DTCConfIdx];
          NewCombinedStatus = Dem_CalculateCmbDTCStatus(DTCConfIdx, FALSE);
        }
        /*
         * EXIT critical section
         */
        DEM_EXIT_EXCLUSIVE_AREA();
#endif

#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
        /*  notify application as WIR-bit has changed */
        Dem_CbTriggerOnEventStatus(EventId, OldDTCStatusMask, NewDTCStatusMask);
#endif

#if (DEM_NUM_CMB_DTCS > 0U)
        Dem_InternalCheckOnCmbDTCStatusChange(EventId, OldCombinedStatus, NewCombinedStatus);
#endif
      }
#endif /* (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) || \
          (DEM_NUM_CMB_DTCS > 0U) */
    }
  }

  DBG_DEM_SETWIRSTATUS_EXIT(Result, EventId, WIRStatus);
  return Result;
}
#endif /* DEM_USER_CTRL_WIR_SUPPORT == STD_ON */

/*------------------[Dem_GetEventStatus]------------------------------------*/
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventStatus(
  Dem_EventIdType EventId,
  P2VAR(Dem_EventStatusExtendedType, AUTOMATIC, DEM_APPL_DATA)
    EventStatusExtended)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_GETEVENTSTATUS_ENTRY(EventId, EventStatusExtended);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventStatus, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_GetEventStatus, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventStatus, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventStatus, DEM_E_WRONG_CONFIGURATION);
  }
  else if (EventStatusExtended == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventStatus, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
  if (Dem_GbiEvAvailable(EventId) == FALSE)
  {
    /* event is disabled so the getting shall be skipped */
    /* E_NOT_OK return value remains */
  }
  else
#endif
  {
    /* !LINKSTO Dem.ReadDTCInformation.EventStatus,1 */
    *EventStatusExtended = (Dem_EventStatusExtendedType)
      (DEM_DTC_STATUS_MASKS[EventId] & DEM_DTC_STATUS_AVAILABILITY_MASK);

    Result = E_OK;
  }

  DBG_DEM_GETEVENTSTATUS_EXIT(Result, EventId, EventStatusExtended);
  return Result;
}

/* !LINKSTO Dem.SWS_Dem_91008,1 */
/*------------------[Dem_GetEventUdsStatus]------------------------------------*/
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventUdsStatus(
  Dem_EventIdType EventId,
  P2VAR(Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA)
  UDSStatusByte)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_GETEVENTUDSSTATUS_ENTRY(EventId, UDSStatusByte);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventUdsStatus, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_GetEventUdsStatus, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventUdsStatus, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventStatus, DEM_E_WRONG_CONFIGURATION);
  }
  else if (UDSStatusByte == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventUdsStatus, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
  if (Dem_GbiEvAvailable(EventId) == FALSE)
  {
    /* !LINKSTO Dem.SWS_Dem_01277,1 */
    /* event is disabled so the getting shall be skipped */
    /* E_NOT_OK return value remains */
  }
  else
#endif
  {
    /* !LINKSTO Dem.ReadDTCInformation.EventStatus,1 */
    /* !LINKSTO Dem.SWS_Dem_00051,1 */
    /* !LINKSTO Dem.SWS_Dem_01276,1 */
    *UDSStatusByte = (Dem_UdsStatusByteType)
      (DEM_DTC_STATUS_MASKS[EventId] & DEM_DTC_STATUS_AVAILABILITY_MASK);

    Result = E_OK;
  }

  DBG_DEM_GETEVENTUDSSTATUS_EXIT(Result, EventId, UDSStatusByte);
  return Result;
}

/*------------------[Dem_GetEventFailed]------------------------------------*/
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventFailed(
  Dem_EventIdType                          EventId,
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA) EventFailed)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_GETEVENTFAILED_ENTRY(EventId, EventFailed);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFailed, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_GetEventFailed, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFailed, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFailed, DEM_E_WRONG_CONFIGURATION);
  }
  else if (EventFailed == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFailed, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
  if (Dem_GbiEvAvailable(EventId) == FALSE)
  {
    /* event is disabled so the getting of test failed bit
     * shall be skipped */
    /* E_NOT_OK return value remains */
  }
  else
#endif
  {
    *EventFailed = (DEM_IS_EV_ST_BIT_TF_SET(EventId) ? TRUE : FALSE);

    Result = E_OK;
  }

  DBG_DEM_GETEVENTFAILED_EXIT(Result, EventId, EventFailed);
  return Result;
}

/*------------------[Dem_GetEventTested]------------------------------------*/
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventTested(
  Dem_EventIdType                          EventId,
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA) EventTested)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_GETEVENTTESTED_ENTRY(EventId, EventTested);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventTested, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_GetEventTested, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventTested, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventTested, DEM_E_WRONG_CONFIGURATION);
  }
  else if (EventTested == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventTested, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
  if (Dem_GbiEvAvailable(EventId) == FALSE)
  {
    /* event is disabled so the getting of test not complete this
     * operation cycle bit shall be skipped */
    /* E_NOT_OK return value remains */
  }
  else
#endif
  {
    if ( (DEM_IS_EV_ST_BIT_TNCTOC_SET(EventId)) )
    {
      *EventTested = FALSE;
    }
    else
    {
      *EventTested = TRUE;
    }

    Result = E_OK;
  }

  DBG_DEM_GETEVENTTESTED_EXIT(Result, EventId, EventTested);
  return Result;
}

/*------------------[Dem_GetDTCOfEvent]-------------------------------------*/
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetDTCOfEvent(
  Dem_EventIdType                              EventId,
  Dem_DTCFormatType                            DTCFormat,
  P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA)      DTCOfEvent)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_GETDTCOFEVENT_ENTRY(EventId, DTCFormat, DTCOfEvent);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* check of Dem_InitializationState is not necessary:
   * it's allowed to get DTC of event even if Dem is uninitialized */

  if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetDTCOfEvent, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetDTCOfEvent, DEM_E_WRONG_CONFIGURATION);
  }
  /* check if the DTCFormat is invalid */
  /* !LINKSTO Dem.ASR21-11.SWS_Dem_01373,1 */
  else if (!DEM_IS_DTCFMT_DEFINED(DTCFormat))
  {
    DEM_REPORT_ERROR(DEM_SID_GetDTCOfEvent, DEM_E_PARAM_DATA);
  }
#if (!( (DEM_DEFAULT_ASR_SERVICE_API == DEM_SERVICE_API_ASR42) || \
        (DEM_ENABLE_ASR42_SERVICE_API == STD_ON) || \
        (DEM_DEFAULT_ASR_SERVICE_API == DEM_SERVICE_API_ASR2011) ) )
  else if (DTCFormat == DEM_DTC_FORMAT_J1939)
  {
    DEM_REPORT_ERROR(DEM_SID_GetDTCOfEvent, DEM_E_PARAM_DATA);
  }
#endif
  else if (DTCOfEvent == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetDTCOfEvent, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
  if (Dem_GbiEvAvailable(EventId) == FALSE)
  {
    /* event is disabled so getting of DTC of event shall be skipped */
    /* E_NOT_OK return value remains */
  }
  else
#endif
  {
    uint32 DTCValue = DEM_NO_DTC;

    switch (DTCFormat)
    {
      case DEM_DTC_FORMAT_OBD:
#if (DEM_OBD_CLASSIC_SUPPORT)
#if (DEM_OBD_VARIANT_SELECTABLE == STD_ON)
        if (DEM_GET_OBD_VARIANT() == DEM_OBD_VARIANT_OBD_CLASSIC)
#endif
        {
          DTCValue = Dem_GetObdDTC(EventId);
        }
#endif /* (DEM_OBD_CLASSIC_SUPPORT) */
        break;

      case DEM_DTC_FORMAT_UDS:
        DTCValue = Dem_GetUdsDTC(EventId);
        break;

      case DEM_DTC_FORMAT_OBD_3BYTE:
#if (DEM_OBDONUDS_SUPPORT && (DEM_OBD_DTCVALUE3BYTE_SUPPORT == STD_ON))
#if (DEM_OBD_VARIANT_SELECTABLE == STD_ON)
        if (DEM_GET_OBD_VARIANT() == DEM_OBD_VARIANT_OBDONUDS)
#endif
        {
          DTCValue = Dem_GetObdDTCValue3Byte(EventId);
        }
#endif /* (DEM_OBDONUDS_SUPPORT && (DEM_OBD_DTCVALUE3BYTE_SUPPORT == STD_ON)) */
        break;

      case DEM_DTC_FORMAT_J1939: /* not supported */
      default:
        break;
    }

    Result = (DTCValue != DEM_NO_DTC) ? E_OK : DEM_E_NO_DTC_AVAILABLE;
    *DTCOfEvent = DTCValue;
  }

  DBG_DEM_GETDTCOFEVENT_EXIT(Result, EventId, DTCFormat, DTCOfEvent);
  return Result;
}

/*------------------[Dem_GetNextStorageOrderId]-----------------------------*/

#if (DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON)
FUNC(void, DEM_CODE) Dem_GetNextStorageOrderId(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) StorageOrderId,
  Dem_StorageOrderIdBlockType            BlockType)
{
  DBG_DEM_GETNEXTSTORAGEORDERID_ENTRY(StorageOrderId, BlockType);

  if (BlockType != Dem_StorageOrderIdGeneratorState.LastBlockType)
  {
    /* increment StorageOrderId generator counter */
    Dem_StorageOrderIdGeneratorState.StorageOrderIdCounter++;
    /* update StorageOrderIdgenerator state to match BlockType */
    Dem_StorageOrderIdGeneratorState.LastBlockType = BlockType;
  }
  DEM_SET_STORAGE_ORDER_ID_ARRAY(StorageOrderId,
    Dem_StorageOrderIdGeneratorState.StorageOrderIdCounter);

  DBG_DEM_GETNEXTSTORAGEORDERID_EXIT(StorageOrderId, BlockType);
}
#endif /* (DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON) */

/*------------------[Dem_SetEnableCondition]--------------------------------*/

/* feature related code-part concerning enable conditions */
#if (DEM_NUM_ENCONDGROUPS > 0)
FUNC(Std_ReturnType, DEM_CODE) Dem_SetEnableCondition(
  uint8   EnableConditionID,
  boolean ConditionFulfilled)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_SETENABLECONDITION_ENTRY(EnableConditionID, ConditionFulfilled);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetEnableCondition, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_SetEnableCondition, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (EnableConditionID >= DEM_NUM_ENABLECONDITIONS)
  {
    DEM_REPORT_ERROR(DEM_SID_SetEnableCondition, DEM_E_WRONG_CONFIGURATION);
  }
  else if ( (ConditionFulfilled != FALSE) &&
            (ConditionFulfilled != TRUE)
          )
  {
    DEM_REPORT_ERROR(DEM_SID_SetEnableCondition, DEM_E_PARAM_DATA);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {

#if ( (DEM_USE_TRIGGER_DEBOUNCE_BEHAVIOR == STD_ON) || \
      ( (DEM_INIT_MONITOR_REENABLED_SUPPORT == STD_ON) && \
        (DEM_USE_CB_INIT_MONITOR == STD_ON) ) )
    uint8 EnCondGrpIdx;
#endif

#if (DEM_USE_TRIGGER_DEBOUNCE_BEHAVIOR == STD_ON)
    /* Enable group condition flags */
    uint8 EnCondGrpDisabled[DEM_NUM_ENCONDGROUPS_BYTES];
    boolean EnCondGrpDisabledAny = FALSE;
#endif

#if ((DEM_INIT_MONITOR_REENABLED_SUPPORT == STD_ON) && (DEM_USE_CB_INIT_MONITOR == STD_ON))
    /* Enable condition group re-enabled flags */
    uint8 EnCondGrpReenabled[DEM_NUM_ENCONDGROUPS_BYTES];
    Dem_CbIndexType CbIdx;
    Dem_EventIdType CurrentEventId;

    /* initialize EnCondGrpReenabled[] with 0U */
    /* Deviation TASKING-1 */
    for (EnCondGrpIdx = 0U; EnCondGrpIdx < DEM_NUM_ENCONDGROUPS_BYTES; EnCondGrpIdx++)
    {
      EnCondGrpReenabled[EnCondGrpIdx] = 0U;
    }
#endif /* (DEM_INIT_MONITOR_REENABLED_SUPPORT == STD_ON) && (DEM_USE_CB_INIT_MONITOR == STD_ON) */

#if (DEM_USE_TRIGGER_DEBOUNCE_BEHAVIOR == STD_ON)
    /* initialize EnCondGrpDisabled[] with 0U */
    /* Deviation TASKING-1 */
    for (EnCondGrpIdx = 0U; EnCondGrpIdx < DEM_NUM_ENCONDGROUPS_BYTES; EnCondGrpIdx++)
    {
      EnCondGrpDisabled[EnCondGrpIdx] = 0U;
    }
#endif

    /* ENTER critical section to protect Dem_EnCondGrpStatusCounter[], because
     * this function is reentrant */
    DEM_ENTER_EXCLUSIVE_AREA();

    if (Dem_EnCondStatus[EnableConditionID] != ConditionFulfilled)
    {
      Dem_EnCondLnkType GrpIdx;

      /* get start- and end- index of Dem_EnCondGrpLink[] array, that
       * contains the indexes of the dedicated group counter per condition */
      const Dem_EnCondLnkType GrpLnkStartIdx = Dem_EnCondToEvIdLink[EnableConditionID];
      const Dem_EnCondLnkType GrpLnkNextIdx = Dem_EnCondToEvIdLink[EnableConditionID + 1U];

      for (GrpIdx = GrpLnkStartIdx; GrpIdx < GrpLnkNextIdx; GrpIdx++)
      {
        /* increment dedicated group counter only once per enable condition */
        if (ConditionFulfilled == FALSE)
        {
          Dem_EnCondGrpStatusCounter[Dem_EnCondGrpLink[GrpIdx]]++;

#if (DEM_USE_TRIGGER_DEBOUNCE_BEHAVIOR == STD_ON)
          /* check if the Dem_EnCondGrpStatusCounter is just set to 1 */
          if (Dem_EnCondGrpStatusCounter[Dem_EnCondGrpLink[GrpIdx]] == 1U)
          {
            /* set the bit array for the Enable groups which has the enable condition linked */
            DEM_SET_BIT_IN_ARRAY(EnCondGrpDisabled, Dem_EnCondGrpLink[GrpIdx]);

            /* set flag indicating a enable group condition has changed */
            EnCondGrpDisabledAny = TRUE;
          }
#endif
        }
        else
        {
          Dem_EnCondGrpStatusCounter[Dem_EnCondGrpLink[GrpIdx]]--;

#if ((DEM_INIT_MONITOR_REENABLED_SUPPORT == STD_ON) && (DEM_USE_CB_INIT_MONITOR == STD_ON))
          /* when Dem_EnCondGrpStatusCounter[] reaches 0, all enable conditions in the group
           * are fulfilled, set the corresponding bit in EnCondGrpReenabled */
          if (Dem_EnCondGrpStatusCounter[Dem_EnCondGrpLink[GrpIdx]] == 0U)
          {
            DEM_SET_BIT_IN_ARRAY(EnCondGrpReenabled, Dem_EnCondGrpLink[GrpIdx]);
          }
#endif
        }
      }
      Dem_EnCondStatus[EnableConditionID] = ConditionFulfilled;
    }
    /* LEAVE critical section  */
    DEM_EXIT_EXCLUSIVE_AREA();

#if (DEM_USE_TRIGGER_DEBOUNCE_BEHAVIOR == STD_ON)
    if (EnCondGrpDisabledAny == TRUE)
    {
      Dem_EventIdType EventId;

      /* loop through all events */
      /* Deviation TASKING-1 */
      for (EventId = 1U; EventId <= DEM_MAX_EVENTID; ++EventId)
      {
        EnCondGrpIdx = Dem_GbiEnCondGrpIdx(EventId);

        /* check if the configured enable condition group has the enable
         * condition that is not fulfilled */
        if (DEM_IS_BIT_SET_IN_ARRAY(EnCondGrpDisabled, EnCondGrpIdx))
        {
          Dem_TriggerDebounceAlgorithmBehavior(EventId);
        }
      }
    }
#endif /* DEM_USE_TRIGGER_DEBOUNCE_BEHAVIOR == STD_ON */

#if ((DEM_INIT_MONITOR_REENABLED_SUPPORT == STD_ON) && (DEM_USE_CB_INIT_MONITOR == STD_ON))
    /* loop trough all events that have callback DemInitMonitorForEvent configured */
    /* Deviation TASKING-1 */
    for (CbIdx = 0U; CbIdx < DEM_LOOKUP_TABLE_INIT_MONITOR_SIZE; CbIdx++)
    {
      CurrentEventId = Dem_CbLookupTableInitMonitor[CbIdx];
      EnCondGrpIdx = Dem_GbiEnCondGrpIdx(CurrentEventId);
      /* check if the configured enable condition group was re-enabled */
      if (DEM_IS_BIT_SET_IN_ARRAY(EnCondGrpReenabled, EnCondGrpIdx))
      {
        (void)Dem_CbFuncPtrInitMonitor[CbIdx](DEM_INIT_MONITOR_REENABLED);
      }
    }
#endif /* (DEM_INIT_MONITOR_REENABLED_SUPPORT == STD_ON) && (DEM_USE_CB_INIT_MONITOR == STD_ON) */

    Result = E_OK;
  }

  DBG_DEM_SETENABLECONDITION_EXIT(
    Result, EnableConditionID, ConditionFulfilled);
  return Result;
}
#endif /* (DEM_NUM_ENCONDGROUPS > 0) */

/*------------------[Dem_SetStorageCondition]-------------------------------*/

/* stub is currently only supported without RTE-usage since the related condition
 * cannot be enabled so that the RTE will enable the port for this API */
#if (DEM_INCLUDE_RTE == STD_OFF)
FUNC(Std_ReturnType, DEM_CODE) Dem_SetStorageCondition(
  uint8   StorageConditionID,
  boolean ConditionFulfilled)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_SETSTORAGECONDITION_ENTRY(StorageConditionID, ConditionFulfilled);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetStorageCondition, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_SetStorageCondition, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if ( (ConditionFulfilled != FALSE) &&
            (ConditionFulfilled != TRUE)
          )
  {
    DEM_REPORT_ERROR(DEM_SID_SetStorageCondition, DEM_E_PARAM_DATA);
  }
  else
#else
  TS_PARAM_UNUSED(ConditionFulfilled);
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* function not fully implemented yet.
     * implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(StorageConditionID);
  }

  DBG_DEM_SETSTORAGECONDITION_EXIT(
    Result, StorageConditionID, ConditionFulfilled);
  return Result;
}
#endif /* DEM_INCLUDE_RTE == STD_OFF */

#if ((DEM_INCLUDE_RTE == STD_OFF) || \
     (DEM_ENABLE_ASR42_SERVICE_API == STD_ON) || \
     (DEM_DEFAULT_ASR_SERVICE_API == DEM_SERVICE_API_ASR42) || \
     (DEM_DEFAULT_ASR_SERVICE_API == DEM_SERVICE_API_ASR2011))
/*------------------[Dem_GetDebouncingOfEvent]------------------------------*/
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetDebouncingOfEvent(
  Dem_EventIdType                                          EventId,
  P2VAR(Dem_DebouncingStateType, AUTOMATIC, DEM_APPL_DATA) DebouncingState)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_GETDEBOUNCINGOFEVENT_ENTRY(EventId, DebouncingState);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetDebouncingOfEvent, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_GetDebouncingOfEvent, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetDebouncingOfEvent, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetDebouncingOfEvent, DEM_E_WRONG_CONFIGURATION);
  }
  else if (DebouncingState == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetDebouncingOfEvent, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* function not fully implemented yet.
     * implementation is scheduled for future releases. */
    TS_PARAM_UNUSED(EventId);
    TS_PARAM_UNUSED(DebouncingState);
  }

  DBG_DEM_GETDEBOUNCINGOFEVENT_EXIT(Result, EventId, DebouncingState);
  return Result;
}
#endif /* ((DEM_INCLUDE_RTE == STD_OFF) ||
        *  (DEM_ENABLE_ASR42_SERVICE_API == STD_ON) ||
        *  (DEM_DEFAULT_ASR_SERVICE_API == DEM_SERVICE_API_ASR42) ||
        *  (DEM_DEFAULT_ASR_SERVICE_API == DEM_SERVICE_API_ASR2011)) */

#if ((DEM_INCLUDE_RTE == STD_OFF) || \
     (DEM_ENABLE_ASR42_SERVICE_API == STD_ON) || \
     ((DEM_DEFAULT_ASR_SERVICE_API == DEM_SERVICE_API_ASR42) && \
      (DEM_ENABLE_ASR43_SERVICE_API == STD_OFF)))
/*------------------[Dem_ASR42_GetEventExtendedDataRecordEx]----------------------*/
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_ASR42_GetEventExtendedDataRecordEx(
  Dem_EventIdType                         EventId,
  uint8                                   RecordNumber,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) BufSize)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_ASR42_GETEVENTEXTENDEDDATARECORDEX_ENTRY(
    EventId, RecordNumber, DestBuffer, BufSize);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventExtendedDataRecordEx, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_GetEventExtendedDataRecordEx, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventExtendedDataRecordEx, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventExtendedDataRecordEx, DEM_E_WRONG_CONFIGURATION);
  }
  else if (DestBuffer == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventExtendedDataRecordEx, DEM_E_PARAM_POINTER);
  }
  else if (BufSize == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventExtendedDataRecordEx, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    TS_PARAM_UNUSED(EventId);
    TS_PARAM_UNUSED(RecordNumber);
    TS_PARAM_UNUSED(DestBuffer);
    TS_PARAM_UNUSED(BufSize);
  }

  DBG_DEM_ASR42_GETEVENTEXTENDEDDATARECORDEX_EXIT(
    Result, EventId, RecordNumber, DestBuffer, BufSize);
  return Result;
}

/*------------------[Dem_ASR42_GetEventFreezeFrameDataEx]-------------------------*/
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_ASR42_GetEventFreezeFrameDataEx(
  Dem_EventIdType                         EventId,
  uint8                                   RecordNumber,
  uint16                                  DataId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) BufSize)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_ASR42_GETEVENTFREEZEFRAMEDATAEX_ENTRY(
    EventId, RecordNumber, DataId, DestBuffer, BufSize);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFreezeFrameDataEx, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_GetEventFreezeFrameDataEx, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFreezeFrameDataEx, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFreezeFrameDataEx, DEM_E_WRONG_CONFIGURATION);
  }
  else if (DestBuffer == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFreezeFrameDataEx, DEM_E_PARAM_POINTER);
  }
  else if (BufSize == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFreezeFrameDataEx, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    TS_PARAM_UNUSED(EventId);
    TS_PARAM_UNUSED(RecordNumber);
    TS_PARAM_UNUSED(DataId);
    TS_PARAM_UNUSED(DestBuffer);
    TS_PARAM_UNUSED(BufSize);
  }

  DBG_DEM_ASR42_GETEVENTFREEZEFRAMEDATAEX_EXIT(
    Result, EventId, RecordNumber, DataId, DestBuffer, BufSize);
  return Result;
}
#endif /* ((DEM_INCLUDE_RTE == STD_OFF) || \
        *  (DEM_ENABLE_ASR42_SERVICE_API == STD_ON) || \
        *  ((DEM_DEFAULT_ASR_SERVICE_API == DEM_SERVICE_API_ASR42) && \
        *   (DEM_ENABLE_ASR43_SERVICE_API == STD_OFF))) */

#if ((DEM_INCLUDE_RTE == STD_OFF) || \
     (DEM_DEFAULT_ASR_SERVICE_API == DEM_SERVICE_API_ASR2011) || \
     (DEM_ENABLE_ASR43_SERVICE_API == STD_ON))
/*------------------[Dem_GetEventExtendedDataRecordEx]----------------------*/
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventExtendedDataRecordEx(
  Dem_EventIdType                         EventId,
  uint8                                   RecordNumber,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) BufSize)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_GETEVENTEXTENDEDDATARECORDEX_ENTRY(
    EventId, RecordNumber, DestBuffer, BufSize);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventExtendedDataRecordEx, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_GetEventExtendedDataRecordEx, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventExtendedDataRecordEx, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventExtendedDataRecordEx, DEM_E_WRONG_CONFIGURATION);
  }
  else if ( (DestBuffer == NULL_PTR) || (BufSize == NULL_PTR) )
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventExtendedDataRecordEx, DEM_E_PARAM_POINTER);
  }
  else if (Dem_GbiDTCOrigin(EventId) == DEM_DTC_ORIGIN_MIRROR_MEMORY)
  {
    /* !LINKSTO Dem.GetEventExtendedDataRecordEx.MirrorMemoryEvent,1 */
    DEM_REPORT_ERROR(DEM_SID_GetEventExtendedDataRecordEx, DEM_E_PARAM_DATA);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    Result = Dem_InternalGetEventExtendedDataRecord(EventId, RecordNumber,
              DestBuffer, BufSize, Result);
  }

  DBG_DEM_GETEVENTEXTENDEDDATARECORDEX_EXIT(
    Result, EventId, RecordNumber, DestBuffer, BufSize);
  return Result;
}

/*------------------[Dem_GetEventFreezeFrameDataEx]-------------------------*/
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventFreezeFrameDataEx(
  Dem_EventIdType                         EventId,
  uint8                                   RecordNumber,
  uint16                                  DataId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) BufSize)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_GETEVENTFREEZEFRAMEDATAEX_ENTRY(
    EventId, RecordNumber, DataId, DestBuffer, BufSize);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFreezeFrameDataEx, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_GetEventFreezeFrameDataEx, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFreezeFrameDataEx, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFreezeFrameDataEx, DEM_E_WRONG_CONFIGURATION);
  }
  else if ( (DestBuffer == NULL_PTR) || (BufSize == NULL_PTR) )
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFreezeFrameDataEx, DEM_E_PARAM_POINTER);
  }
  else if (Dem_GbiDTCOrigin(EventId) == DEM_DTC_ORIGIN_MIRROR_MEMORY)
  {
    /* !LINKSTO Dem.FreezeFrameStorage.MirrorMemoryEvent,1 */
    DEM_REPORT_ERROR(DEM_SID_GetEventFreezeFrameDataEx, DEM_E_PARAM_DATA);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    boolean ReportTotalRecord = FALSE;

    /* !LINKSTO Dem.FreezeFrameStorage.RecentRecord,1 */
#if (DEM_FREEZE_FRAME_REC_NUMERATION_TYPE != DEM_FF_RECNUM_CALCULATED)
    if(RecordNumber != 0xFFU)
#endif
    {
      Result = Dem_InternalGetEventFreezeFrameData(EventId, RecordNumber,
                ReportTotalRecord, DataId, DestBuffer, BufSize, Result);

      /* Deviation TASKING-10 */
#pragma warning 549
      if ( (Result == DEM_E_WRONG_DIDNUMBER) ||
           (Result == DEM_E_WRONG_RECORDNUMBER) ||
           (Result == DEM_E_NODATAAVAILABLE) )
#pragma warning default
      {
        Result = DEM_NO_SUCH_ELEMENT;
      }
    }
  }

  DBG_DEM_GETEVENTFREEZEFRAMEDATAEX_EXIT(
    Result, EventId, RecordNumber, DataId, DestBuffer, BufSize);
  return Result;
}
#endif /* ((DEM_INCLUDE_RTE == STD_OFF) ||
        *  (DEM_DEFAULT_ASR_SERVICE_API == DEM_SERVICE_API_ASR2011) ||
        *  (DEM_ENABLE_ASR43_SERVICE_API == STD_ON)) */

/*------------------[Dem_GetFaultDetectionCounter]--------------------------*/

/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetFaultDetectionCounter(
  Dem_EventIdType EventId,
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA)
    FaultDetectionCounter)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_GETFAULTDETECTIONCOUNTER_ENTRY(EventId, FaultDetectionCounter);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetFaultDetectionCounter, DEM_E_UNINIT);
  }
  else if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetFaultDetectionCounter, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetFaultDetectionCounter, DEM_E_WRONG_CONFIGURATION);
  }
  else if (FaultDetectionCounter == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetFaultDetectionCounter, DEM_E_PARAM_POINTER);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_GetFaultDetectionCounter, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else
#endif /* DEM_DEV_ERROR_DETECT */
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
  if (Dem_GbiEvAvailable(EventId) == FALSE)
  {
    /* event is disabled so the getting of fault detection counter
     * shall be skipped */
    /* E_NOT_OK return value remains */
  }
  else
#endif
  {
    const Dem_DebounceType Algorithm = Dem_GbiDebounceAlgo(EventId);

#if (DEM_USE_CB_GET_FDC == STD_OFF)
    if (Dem_DebounceFctPtrTable[Algorithm].GetFDCFct != NULL_PTR)
#endif
    {
      /* get the fault detection counter from the corresponding event */
      Result = Dem_DebounceFctPtrTable[Algorithm].GetFDCFct(EventId, FaultDetectionCounter);
    }
  }

  DBG_DEM_GETFAULTDETECTIONCOUNTER_EXIT(
    Result, EventId, FaultDetectionCounter);
  return Result;
}

/*------------------[Dem_GetIndicatorStatus]--------------------------------*/

#if (DEM_NUMBER_OF_INDICATORS > 0U)
/* feature related code-part concerning indicators */
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetIndicatorStatus(
  Dem_IndicatorIdType                                      IndicatorId,
  P2VAR(Dem_IndicatorStatusType, AUTOMATIC, DEM_APPL_DATA) IndicatorStatus)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_GETINDICATORSTATUS_ENTRY(IndicatorId, IndicatorStatus);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetIndicatorStatus, DEM_E_UNINIT);
  }
  else if (IndicatorId >= DEM_NUMBER_OF_INDICATORS)
  {
    DEM_REPORT_ERROR(DEM_SID_GetIndicatorStatus, DEM_E_PARAM_DATA);
  }
  else if (IndicatorStatus == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetIndicatorStatus, DEM_E_PARAM_POINTER);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_GetIndicatorStatus, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
#if (DEM_NUM_INDICATOR_LINKS > 0U)
    /* indicator status is calculated re-entrant, as the WIR bits are evaluated
     * atomically (and further accesses are only done on constant values) */
    *IndicatorStatus = Dem_InternalGetIndicatorStatus(IndicatorId, FALSE);

#else /* none of the configured indicators has a link to an event */

#if (DEM_DEV_ERROR_DETECT == STD_OFF)
    TS_PARAM_UNUSED(IndicatorId);
#endif
    /* !LINKSTO Dem.Dem_GetIndicatorStatus.Unlinked,2 */
    *IndicatorStatus = DEM_INDICATOR_OFF;
#endif /* DEM_NUM_INDICATOR_LINKS > 0U */

    Result = E_OK;
  }

  DBG_DEM_GETINDICATORSTATUS_EXIT(Result, IndicatorId, IndicatorStatus);
  return Result;
}
#endif /* DEM_NUMBER_OF_INDICATORS > 0U */

#if ( ( (DEM_ENABLE_ASR43_SERVICE_API == STD_OFF) && \
        (DEM_DEFAULT_ASR_SERVICE_API != DEM_SERVICE_API_ASR2011) ) || \
      (DEM_ENABLE_ASR40_SERVICE_API == STD_ON) )
/* Dem_GetEventFreezeFrameData API's are only available if */
/* default ASR version is 40 ,for default version 42 Dem_ASR42_GetEventFreezeFrameData
 * API us available, starting with ASR version 43 these API's were removed */
/*------------------[Dem_GetEventFreezeFrameData]---------------------------*/

/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventFreezeFrameData(
  Dem_EventIdType                        EventId,
  uint8                                  RecordNumber,
  boolean                                ReportTotalRecord,
  uint16                                 DataId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) DestBuffer)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_GETEVENTFREEZEFRAMEDATA_ENTRY(
    EventId, RecordNumber, ReportTotalRecord, DataId, DestBuffer);

  /* ASR42_GetEventFreezeFrameData implements the full functionality */
  Result = Dem_ASR42_GetEventFreezeFrameData(
    EventId, RecordNumber, ReportTotalRecord, DataId, DestBuffer);

  /* ASR40_GetEventFreezeFrameData returns E_NOT_OK in case of any error */
  /* Deviation TASKING-4 */
#pragma warning 549
  if (Result != E_OK)
#pragma warning default
  {
    Result = E_NOT_OK;
  }

  DBG_DEM_GETEVENTFREEZEFRAMEDATA_EXIT(
    Result, EventId, RecordNumber, ReportTotalRecord, DataId, DestBuffer);
  return Result;
}
#endif /* ( ( (DEM_ENABLE_ASR43_SERVICE_API == STD_OFF) && \
              (DEM_DEFAULT_ASR_SERVICE_API != DEM_SERVICE_API_ASR2011) ) || \
            (DEM_ENABLE_ASR40_SERVICE_API == STD_ON) ) */

#if ( ( (DEM_ENABLE_ASR43_SERVICE_API == STD_OFF) && \
        (DEM_DEFAULT_ASR_SERVICE_API != DEM_SERVICE_API_ASR2011) ) || \
      (DEM_ENABLE_ASR40_SERVICE_API == STD_ON) || \
      (DEM_ENABLE_ASR42_SERVICE_API == STD_ON) )
/* Dem_ASR42_GetEventFreezeFrameData and Dem_GetEventExtendedDataRecord API's are only available if */
/* default ASR version is 40 or 42, starting with ASR version 43 these API's were removed */
/*------------------[Dem_ASR42_GetEventFreezeFrameData]---------------------*/
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_ASR42_GetEventFreezeFrameData(
  Dem_EventIdType                        EventId,
  uint8                                  RecordNumber,
  boolean                                ReportTotalRecord,
  uint16                                 DataId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) DestBuffer)
{
  Std_ReturnType Result = DEM_E_NODATAAVAILABLE;

  DBG_DEM_ASR42_GETEVENTFREEZEFRAMEDATA_ENTRY(
    EventId, RecordNumber, ReportTotalRecord, DataId, DestBuffer);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFreezeFrameData, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_GetEventFreezeFrameData, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFreezeFrameData, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFreezeFrameData, DEM_E_WRONG_CONFIGURATION);
  }
  else if ( (ReportTotalRecord != FALSE) &&
            (ReportTotalRecord != TRUE)
          )
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFreezeFrameData, DEM_E_PARAM_DATA);
  }
  else if (DestBuffer == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventFreezeFrameData, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* Bufsize is set to DEM_MAX_FFSEG_SIZE, as Bufsize info is needed for the
       Dem_GetEventFreezeFrameDataEx API common internal function is called
       for both */
    Dem_SizeFFType BufSize = DEM_MAX_FFSEG_SIZE;
    Result = Dem_InternalGetEventFreezeFrameData(EventId, RecordNumber,
              ReportTotalRecord, DataId, DestBuffer, &BufSize, Result);
  }

  DBG_DEM_ASR42_GETEVENTFREEZEFRAMEDATA_EXIT(
    Result, EventId, RecordNumber, ReportTotalRecord, DataId, DestBuffer);
  return Result;
}

/*------------------[Dem_GetEventExtendedDataRecord]------------------------*/
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventExtendedDataRecord(
  Dem_EventIdType                        EventId,
  uint8                                  RecordNumber,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) DestBuffer)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_GETEVENTEXTENDEDDATARECORD_ENTRY(EventId, RecordNumber, DestBuffer);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventExtendedDataRecord, DEM_E_UNINIT);
  }
  else if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventExtendedDataRecord, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventExtendedDataRecord, DEM_E_WRONG_CONFIGURATION);
  }
  else if ( (RecordNumber == 0U) ||
            ((RecordNumber > 0xEFU) && (RecordNumber != 0xFFU)) )
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventExtendedDataRecord, DEM_E_PARAM_DATA);
  }
  else if (DestBuffer == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventExtendedDataRecord, DEM_E_PARAM_POINTER);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_GetEventExtendedDataRecord, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* Bufsize is set to DEM_MAX_EDSEG_SIZE, as Bufsize info is needed for the
       Dem_GetEventExtendedDataRecordEx API common internal function is called
       for both */
    Dem_SizeEDType BufSize = DEM_MAX_EDSEG_SIZE;
    Result = Dem_InternalGetEventExtendedDataRecord(EventId, RecordNumber,
              DestBuffer, &BufSize, Result);
  }

  /* Deviation TASKING-11 */
#pragma warning 549
  Result = (Result != E_OK) ? E_NOT_OK: E_OK;
#pragma warning default

  DBG_DEM_GETEVENTEXTENDEDDATARECORD_EXIT(
    Result, EventId, RecordNumber, DestBuffer);
  return Result;
}
#endif /* ( ( (DEM_ENABLE_ASR43_SERVICE_API == STD_OFF) && \
              (DEM_DEFAULT_ASR_SERVICE_API != DEM_SERVICE_API_ASR2011) ) || \
            (DEM_ENABLE_ASR40_SERVICE_API == STD_ON) || \
            (DEM_ENABLE_ASR42_SERVICE_API == STD_ON) ) */

STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_InternalGetEventFreezeFrameData(
  Dem_EventIdType                         EventId,
  uint8                                   RecordNumber,
  boolean                                 ReportTotalRecord,
  uint16                                  DataId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) BufSize,
  Std_ReturnType                          ResultInit)
{
   Std_ReturnType Result = ResultInit;

  DBG_DEM_INTERNALGETEVENTFREEZEFRAMEDATA_ENTRY(EventId, RecordNumber,
    ReportTotalRecord, DataId, DestBuffer, BufSize, ResultInit);

#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
  if (Dem_GbiEvAvailable(EventId) == TRUE)
#endif
  {

#if (DEM_NUM_FFSEGS > 0U)
    Dem_EventMemoryEntryPtrType EvMemEntry;

#if (DEM_FREEZE_FRAME_REC_NUMERATION_TYPE != DEM_FF_RECNUM_CALCULATED)
    boolean FFRecNumValid = FALSE;
#endif

    const Dem_FFIdxType MaxNumFF = Dem_GbiMaxNumFFRecs(EventId);
    /* Set the result as DEM_E_NODATAAVAILABLE */
    Result = DEM_E_NODATAAVAILABLE;
    /*
     * ENTER critical section to protect the event memory entry
     *       call-context: any
     */
    DEM_ENTER_EXCLUSIVE_AREA();

#if (DEM_FREEZE_FRAME_REC_NUMERATION_TYPE != DEM_FF_RECNUM_CALCULATED)
    /* in case RecordNumber is equal to 0xFFU next condition will be fulfilled
     * anyway and there is no need for function call here. */
    if (RecordNumber != 0xFFU)
    {
      FFRecNumValid = Dem_CheckFFRecNumValid(EventId, RecordNumber);
    }
#endif
    /* check whether requested record number is valid for the event */
    /* !LINKSTO dsn.Dem.CheckRecordNumber.SearchForEntry,3 */
    /* !LINKSTO Dem.SWS_Dem_01194,1 */
#if (DEM_FREEZE_FRAME_REC_NUMERATION_TYPE == DEM_FF_RECNUM_CALCULATED)
    if ( (RecordNumber == 0xFFU) ||
         ( (RecordNumber <= MaxNumFF) && (RecordNumber != 0U) ) )
#else
    if ( (RecordNumber == 0xFFU) || (FFRecNumValid == TRUE) )
#endif
    {
      /* get freeze frame class layout */
      CONSTP2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFClass =
        &Dem_FFClass[Dem_GbiFFClassIdx(EventId)];
      Dem_SizeFFType StartByte = 0U;
      Dem_FFSegIdxType FFSegIdx = DEM_FFSEG_IDX_UNUSED;

      if (ReportTotalRecord == FALSE)
      {
        FFSegIdx = Dem_FindFFSegIdx(DEM_REGULAR_FF,
          FFClass, DataId, &StartByte);
      }

      /* check if DID is valid (is known) for this event */
      if ((ReportTotalRecord == TRUE) || (FFSegIdx != DEM_FFSEG_IDX_UNUSED))
      {
        /* search for event in event memory */
        if (Dem_SearchForEntry(EventId, &EvMemEntry, NULL_PTR) == TRUE)
        {
          const Dem_FFIdxType NumFF = DEM_NUMFF(EvMemEntry, MaxNumFF);
          Dem_FFIdxType FFIndex;

          /* check if most recent record data shall be returned */
          if (RecordNumber == 0xFFU)
          {
            FFIndex = NumFF - 1U;
          }
          else
          {
            /* valid FFIndex will be returned if the record is stored.
             * NumFF will be returned if it is not stored */
            FFIndex = Dem_CheckFFRecNumStored(EvMemEntry, RecordNumber);
          }

          /* check if record is stored */
          if (FFIndex < NumFF)
          {
            /* pointer to const FF data */
            const Dem_EntryDataPtrConstType FFEntryData =
              Dem_FFEntryData(EvMemEntry, FFClass, FFIndex);

            if (ReportTotalRecord == TRUE)
            {
              const Dem_SizeFFType SizeOfFF =
                Dem_SizeOfFF(DEM_REGULAR_FF, FFClass);

              /* write content into the destination buffer */
              TS_MemCpy(DestBuffer, &FFEntryData[0], SizeOfFF);

              Result = E_OK;
            }
            else /* report one DID only */
            {
              /* FFSegIdx can't be DEM_FFSEG_IDX_UNUSED,
               * check was already done in Dem_FindFFSegIdx */

              const Dem_SizeFFType FFSegSize =
                Dem_SizeOfFFSegment(&Dem_FFSegment[FFSegIdx]);

#if ( (DEM_DEFAULT_ASR_SERVICE_API == DEM_SERVICE_API_ASR2011) || \
      (DEM_ENABLE_ASR43_SERVICE_API == STD_ON) )
              if(FFSegSize > (Dem_SizeFFType)*BufSize)
              {
                Result = DEM_BUFFER_TOO_SMALL;
              }
              else
#endif
              {
                /* copy actual size of the DID into the buffer size */
                /* !LINKSTO Dem.SWS_Dem_00991,1 */
                *BufSize = FFSegSize;
                /* copy content of the DID into the destination buffer */
                TS_MemCpy(DestBuffer, &FFEntryData[StartByte], FFSegSize);
                Result = E_OK;
              }
            }
          } /* else: event stored, freeze frame data entry does not exist:
             * result remains DEM_E_NODATAAVAILABLE */
        } /* else: event not stored: result remains DEM_E_NODATAAVAILABLE */
      }
      else
      {
        /* data Id is not valid for this event */
        Result = DEM_E_WRONG_DIDNUMBER;
      }
    }
    else
    {
      /* non-existing record requested, "out of range" */
      Result = DEM_E_WRONG_RECORDNUMBER;
    }

    /*
     * LEAVE critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();
#else
  TS_PARAM_UNUSED(EventId);
  TS_PARAM_UNUSED(ReportTotalRecord);
  TS_PARAM_UNUSED(DestBuffer);
  TS_PARAM_UNUSED(BufSize);
  TS_PARAM_UNUSED(RecordNumber);
  TS_PARAM_UNUSED(DataId);
  TS_PARAM_UNUSED(ResultInit);
#endif
  }

  DBG_DEM_INTERNALGETEVENTFREEZEFRAMEDATA_EXIT(Result, EventId, RecordNumber,
    ReportTotalRecord, DataId, DestBuffer, BufSize, ResultInit);
  return Result;
}

STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_InternalGetEventExtendedDataRecord(
  Dem_EventIdType                         EventId,
  uint8                                   RecordNumber,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)  DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) BufSize,
  Std_ReturnType                          ResultInit)
{
  Std_ReturnType Result = ResultInit;

  DBG_DEM_INTERNALGETEVENTEXTENDEDDATARECORD_ENTRY(EventId,
    RecordNumber, DestBuffer, BufSize, ResultInit);

#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
  if (Dem_GbiEvAvailable(EventId) == TRUE)
#endif
  {
#if (DEM_MAR_SUPPORT)
    /* !LINKSTO Dem.OBDonUDS.MAR.NoEventSpecificReporting,1 */
    if (RecordNumber != DEM_MAR_EDRN)
#endif
    {
#if (DEM_NUM_EDSEGS > 0U)
      Dem_EventMemoryEntryPtrType EvMemEntry = NULL_PTR;
      Dem_EDSegIdxType SegIdx;
      Dem_EDSegIdxType SegIdxStart;
      Dem_EDSegIdxType SegIdxStop;

      /* get extended data class layout */
      CONSTP2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass =
        &Dem_EDClass[Dem_GbiEDClassIdx(EventId)];

      /* Set the result as no such element */
      Result = DEM_NO_SUCH_ELEMENT;

      if (RecordNumber != 0xFFU)
      {
        /* check if record number is valid (is known) for this event */
        SegIdxStart = Dem_FindEDNumIndex(EDClass, RecordNumber);
        SegIdxStop = SegIdxStart + 1U;
      }
      else
      {
        /* all records are requested */
        SegIdxStart = 0U;
        SegIdxStop = EDClass->NumEDSegs;
      }

      /* check if ED record is valid (is known) for this event, or service is
       * requested for all ED records */
      /* !LINKSTO dsn.Dem.CheckRecordNumber.SearchForEntry,3 */
      if ((RecordNumber == 0xFFU) || (SegIdxStart < EDClass->NumEDSegs))
      {
        boolean EventMemEntryAvail;
        Dem_SizeEntryDataType EDSegSize = 0U;
        /* calculate needed buffer size */
        Dem_SizeEDType NeededSize = 0U;
        /*
         * ENTER critical section to protect the event memory entry
         *       call-context: any
         */
        DEM_ENTER_EXCLUSIVE_AREA();

        /* search for the event in event memory */
        EventMemEntryAvail = Dem_SearchForEntry(EventId, &EvMemEntry, NULL_PTR);

        /* copy content of the all records (whole ED class) into the
         * destination buffer */
        for (SegIdx = SegIdxStart; SegIdx < SegIdxStop; ++SegIdx)
        {
          CONSTP2CONST(Dem_EDSegmentType, AUTOMATIC, DEM_CONST) EDSegment =
            &Dem_EDSegment[EDClass->EDSegIdx[SegIdx]];

          const Dem_EDStartByteType EDStartByte =
            EDClass->StartByte[SegIdx];

          /* !LINKSTO Dem.GetEventExtendedDataRecord.DataAlwaysAvailable,1 */
          /* !LINKSTO Dem.GetEventExtendedDataRecordEx.DataAlwaysAvailable,1 */
          if ( (EventMemEntryAvail == TRUE) ||
               (EDSegment->AlwaysAvailable == TRUE) )
          {
#if (DEM_MAR_SUPPORT == STD_ON)
            /* !LINKSTO dsn.Dem.OBDonUDS.MAR.NoEventSpecificReportingRecNum0xFF,1 */
            if (EDSegment->RecNum != DEM_MAR_EDRN)
#endif
            {
#if ( (DEM_DEFAULT_ASR_SERVICE_API == DEM_SERVICE_API_ASR2011) || \
      (DEM_ENABLE_ASR43_SERVICE_API == STD_ON) || \
      (DEM_INCLUDE_RTE == STD_OFF) )

#if ( (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON) || \
      (DEM_NUM_CAPTURE_ON_RETRIEVAL_DATAELEMENTS > 0U) )
              NeededSize += Dem_SizeOfNonStoredDEsInSegment(EDSegment);
#endif
              NeededSize += Dem_SizeOfStoredDEsInSegment(EDSegment);

              if ((Dem_SizeEDType)*BufSize < NeededSize)
              {
                Result = DEM_BUFFER_TOO_SMALL;
              }
              else
#endif
              {
                /* next record of ED class should be assembled consecutive to the
                 * previous record */
                /* the size returned shall be used for getting position of DestBuffer
                 * for copying the next record */
                EDSegSize += Dem_AssembleExtendedDataSeg(EventId,
                                                         EDSegment,
                                                         EDStartByte,
                                                         &DestBuffer[EDSegSize],
                                                         EvMemEntry,
                                                         FALSE,
                                                         TRUE);
              }
            }
          }/* Event is not present in the event memory and data always available is false */
        }/* End of For loop */

        /*
         * LEAVE critical section
         */
        DEM_EXIT_EXCLUSIVE_AREA();

#if (DEM_NUM_CAPTURE_ON_RETRIEVAL_DATAELEMENTS > 0U)
        /* Loop through all ED segments outside critical section because external data elements
           with CaptureOnRetrieval set as TRUE are read with Dem_ReadExternalDataElement which
           is to be called outside critical section */
        if (Result != DEM_BUFFER_TOO_SMALL)
        {
          Dem_SizeEntryDataType EDSegSize_Cor = 0U;
          for (SegIdx = SegIdxStart; SegIdx < SegIdxStop; ++SegIdx)
          {
            CONSTP2CONST(Dem_EDSegmentType, AUTOMATIC, DEM_CONST) EDSegment =
              &Dem_EDSegment[EDClass->EDSegIdx[SegIdx]];

            const Dem_EDStartByteType EDStartByte =
              EDClass->StartByte[SegIdx];

            /* !LINKSTO Dem.GetEventExtendedDataRecord.DataAlwaysAvailable,1 */
            /* !LINKSTO Dem.GetEventExtendedDataRecordEx.DataAlwaysAvailable,1 */
            if ( (EventMemEntryAvail == TRUE) ||
                 (EDSegment->AlwaysAvailable == TRUE) )
            {
#if (DEM_MAR_SUPPORT == STD_ON)
              /* !LINKSTO dsn.Dem.OBDonUDS.MAR.NoEventSpecificReportingRecNum0xFF,1 */
              if (EDSegment->RecNum != DEM_MAR_EDRN)
#endif
              {

                /* next record of ED class should be assembled consecutive to the
                 * previous record */
                /* the size returned shall be used for getting position of DestBuffer
                 * for copying the next record */
                /* !LINKSTO Dem.DataElementCaptureOnRetrieval.CallBackEventId.GetEventEDR,1 */
                EDSegSize_Cor += Dem_AssembleExtendedDataSeg(EventId,
                                                             EDSegment,
                                                             EDStartByte,
                                                             &DestBuffer[EDSegSize_Cor],
                                                             EvMemEntry,
                                                             FALSE,
                                                             FALSE);
              }
            }/* Event is not present in the event memory and data always available is false */
          }/* End of For loop */
        }
#endif /* (DEM_NUM_CAPTURE_ON_RETRIEVAL_DATAELEMENTS > 0U) */

        /* check if data has been copied and result is not equal to DEM_BUFFER_TOO_SMALL */
        /* Deviation TASKING-12 */
        if ((EDSegSize != 0U) && (Result != DEM_BUFFER_TOO_SMALL))
        {
          /* Load the Bufsize with the actual buffer size filled*/
          *BufSize = NeededSize;
          Result = E_OK;
        } /* else: no data or smaller buffer size, result can be DEM_NO_SUCH_ELEMENT
             or DEM_BUFFER_TOO_SMALL */
      }/* else: record number invalid for this event and service is not
        requested for all ED records */
#else
    TS_PARAM_UNUSED(EventId);
    TS_PARAM_UNUSED(RecordNumber);
    TS_PARAM_UNUSED(DestBuffer);
    TS_PARAM_UNUSED(BufSize);
    TS_PARAM_UNUSED(ResultInit);
#endif /* (DEM_NUM_EDSEGS > 0U) */
    }
  }

  DBG_DEM_INTERNALGETEVENTEXTENDEDDATARECORD_EXIT(Result, EventId,
    RecordNumber, DestBuffer, BufSize, ResultInit);
  return Result;
}

/*------------------[Dem_GetEventMemoryOverflow]----------------------------*/
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventMemoryOverflow(
  Dem_DTCOriginType                        DTCOrigin,
  P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA) OverflowIndication)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_GETEVENTMEMORYOVERFLOW_ENTRY(DTCOrigin, OverflowIndication);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventMemoryOverflow, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_GetEventMemoryOverflow, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  /* DTCOrigin values in the user-defined memory origin range 0x01XX are
   * not treated as invalid, because the interface between DCM and DEM is
   * based on ASR4.3 which is supporting the extended range of user defined
   * memory. The implementation is backward compatible to ASR4.0.3. */
  else if ( (DTCOrigin > (Dem_DTCOriginType)0x01FFU) ||
            ( (DTCOrigin < (Dem_DTCOriginType)0x0100U) &&
              (DTCOrigin != DEM_DTC_ORIGIN_PRIMARY_MEMORY) &&
              (DTCOrigin != DEM_DTC_ORIGIN_MIRROR_MEMORY) &&
              (DTCOrigin != DEM_DTC_ORIGIN_PERMANENT_MEMORY) &&
              (DTCOrigin != DEM_DTC_ORIGIN_SECONDARY_MEMORY)
            )
          )
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventMemoryOverflow, DEM_E_PARAM_DATA);
  }
  else if (OverflowIndication == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetEventMemoryOverflow, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    Dem_DTCOriginType MappedDTCOrigin = Dem_GetMappedDTCOrigin(
        DTCOrigin, DEM_DTC_ORIGIN_MAPPING_ASR40_IF);

    /* Check if requested DTC_ORIGIN is mapped */
    if(MappedDTCOrigin != DEM_DTC_ORIGIN_INVALID)
    {
      *OverflowIndication = DEM_IS_OVFIND_SET(MappedDTCOrigin - 1U) ? TRUE : FALSE;

      Result = E_OK;
    }
  }

  DBG_DEM_GETEVENTMEMORYOVERFLOW_EXIT(Result, DTCOrigin, OverflowIndication);
  return Result;
}

/*------------------[Dem_GetNumberOfEventMemoryEntries]---------------------*/

/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetNumberOfEventMemoryEntries(
  Dem_DTCOriginType                      DTCOrigin,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) NumberOfEventMemoryEntries)
{
  Std_ReturnType Result = E_NOT_OK;
  Dem_SizeEvMemEntryType EntryIdx;
  uint8 EventCtr = 0U;

  DBG_DEM_GETNUMBEROFEVENTMEMORYENTRIES_ENTRY(DTCOrigin, NumberOfEventMemoryEntries);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetNumberOfEventMemoryEntries, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_GetNumberOfEventMemoryEntries, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  /* DTCOrigin values in the user-defined memory origin range 0x01XX are
   * not treated as invalid, because the interface between DCM and DEM is
   * based on ASR4.3 which is supporting the extended range of user defined
   * memory. The implementation is backward compatible to ASR4.2.1. */
  else if ( (DTCOrigin > (Dem_DTCOriginType)0x01FFU) ||
            ( (DTCOrigin < (Dem_DTCOriginType)0x0100U) &&
              (DTCOrigin != DEM_DTC_ORIGIN_PRIMARY_MEMORY) &&
              (DTCOrigin != DEM_DTC_ORIGIN_MIRROR_MEMORY) &&
              (DTCOrigin != DEM_DTC_ORIGIN_PERMANENT_MEMORY) &&
              (DTCOrigin != DEM_DTC_ORIGIN_SECONDARY_MEMORY)
            )
          )
  {
    DEM_REPORT_ERROR(DEM_SID_GetNumberOfEventMemoryEntries, DEM_E_PARAM_DATA);
  }
  else if (NumberOfEventMemoryEntries == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetNumberOfEventMemoryEntries, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    Dem_DTCOriginType MappedDTCOrigin = Dem_GetMappedDTCOrigin(
        DTCOrigin, DEM_DTC_ORIGIN_MAPPING_ASR40_IF);

    /* Check if requested DTC_ORIGIN is mapped */
    if(MappedDTCOrigin != DEM_DTC_ORIGIN_INVALID)
    {
#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0)
      /* loop over event memory (permanent) and count the locations, where an EventId
         is entered (EventId != DEM_EVENT_ID_INVALID) */
      if (MappedDTCOrigin == DEM_DTC_ORIGIN_PERMANENT_MEMORY)
      {
        for (EntryIdx = 0U; (EntryIdx < DEM_MAX_NUMBER_EVENT_ENTRY_PER); EntryIdx++)
        {
          const Dem_PermanentMemoryEntryType Entry =
            Dem_EventMemoryPermanent[EntryIdx];

          if (DEM_GET_PERMANENT_MEMORY_EVENT_ID(Entry) !=
                DEM_EVENT_ID_INVALID)
          {
            EventCtr++;
          }
        }
      }
     else
#endif /* DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0 */
     {
        /* loop over event memory (mirror, primary or secondary) and count the locations,
         where an EventId is entered (EventId != DEM_EVENT_ID_INVALID) */
        for (EntryIdx = 0U; (EntryIdx < Dem_SizeEventMem[MappedDTCOrigin - 1U]); EntryIdx++)
        {
          if (Dem_EventMem[MappedDTCOrigin - 1U][EntryIdx].EventId != DEM_EVENT_ID_INVALID)
          {
            EventCtr++;
          }
        }
      }
      /* The counter value now equals the NumberOfEventMemoryEntries */
      *NumberOfEventMemoryEntries = EventCtr;

      Result = E_OK;
    }
  }

  DBG_DEM_GETNUMBEROFEVENTMEMORYENTRIES_EXIT(Result, DTCOrigin, NumberOfEventMemoryEntries);
  return Result;
}
/*------------------[Dem_SetDTCSuppression]---------------------------------*/

#if (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_SetDTCSuppression(
  uint32            DTC,
  Dem_DTCFormatType DTCFormat,
  boolean           SuppressionStatus)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_SETDTCSUPPRESSION_ENTRY(DTC, DTCFormat, SuppressionStatus);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetDTCSuppression, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_SetDTCSuppression, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  /* !LINKSTO Dem.DTC.Inputformat,1 */
#if (DEM_OBD_Support == STD_ON)
  else if ( ( (DTC == 0U) || (DTC > 0xFFFFFFU) ) ||
            ( (DTCFormat == DEM_DTC_FORMAT_OBD) && ((DTC & 0x0000FFU) != 0U) )
          )
#else
  else if ( (DTC == 0U) || (DTC > 0xFFFFFFU) )
#endif
  {
    DEM_REPORT_ERROR(DEM_SID_SetDTCSuppression, DEM_E_PARAM_DATA);
  }

  /* check if the DTCFormat is invalid */
  /* !LINKSTO Dem.ASR21-11.SWS_Dem_01373,1 */
  else if (!DEM_IS_DTCFMT_CONFIGURED(DTCFormat))
  {
    DEM_REPORT_ERROR(DEM_SID_SetDTCSuppression, DEM_E_PARAM_DATA);
  }
  else if ( (SuppressionStatus != FALSE) && (SuppressionStatus != TRUE) )
  {
    DEM_REPORT_ERROR(DEM_SID_SetDTCSuppression, DEM_E_PARAM_DATA);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    Result = Dem_InternalSetDTCSuppression((uint32) DTC,
                                           DTCFormat,
                                           SuppressionStatus);
  }

  DBG_DEM_SETDTCSUPPRESSION_EXIT(Result, DTC, DTCFormat, SuppressionStatus);
  return Result;
}
#endif /* (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION) */

/*------------------[Dem_SetEventAvailable]-----------------------------------*/

#if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
/* Deviation MISRAC2012-1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventAvailable(
  Dem_EventIdType EventId,
  boolean         AvailableStatus)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_SETEVENTAVAILABLE_ENTRY(EventId, AvailableStatus);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* Dem.ASR43.SWS_Dem_01112 is not supported, therefore the API is not available
   * before Dem_Init() */
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetEventAvailable, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_SetEventAvailable, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_SetEventAvailable, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_SetEventAvailable, DEM_E_WRONG_CONFIGURATION);
  }
  else if ( (AvailableStatus != FALSE) &&
            (AvailableStatus != TRUE)
          )
  {
    DEM_REPORT_ERROR(DEM_SID_SetEventAvailable, DEM_E_PARAM_DATA);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
#if ( (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U) && \
      (DEM_MULTIEVENTTRIGGERING_SETEVENTAVAILABLE_SUPPORT == STD_ON) )

    Dem_EventIdType NextEventId, LastEventId = DEM_EVENT_ID_INVALID;

    /* check if reported event is a multi-triggering master and apply
     * the event availability to all slaves */
    if ( Dem_GetMultiEventTriggering(EventId) != NULL_PTR )
    {
      /* !LINKSTO Dem.MultiEventTriggering.SetEventAvailable,1 */
      do
      {
        NextEventId = Dem_FindNextDependentEvent(EventId, E_NOT_OK, &LastEventId);
        if (NextEventId != DEM_EVENT_ID_INVALID)
        {
          /* !LINKSTO Dem.MultiEventTriggering.SetEventAvailable.ReturnValue,1 */
          /* last processed event is the master event */
          Result = Dem_InternalSetEventAvailable(NextEventId, AvailableStatus);
        }
      } while (NextEventId != DEM_EVENT_ID_INVALID);
    }
    else
#endif
    {
      Result = Dem_InternalSetEventAvailable(EventId, AvailableStatus);
    }
  }

  DBG_DEM_SETEVENTAVAILABLE_EXIT(Result, EventId, AvailableStatus);
  return Result;
}
#endif /* (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY) */

/*------------------[Dem_SetEventConfirmationThresholdCounter]-------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventConfirmationThresholdCounter(
  Dem_EventIdType     EventId,
  uint8 FailureCycleCounterThreshold)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_SETEVENTCONFIRMATIONTHRESHOLDCOUNTER_ENTRY(EventId, FailureCycleCounterThreshold);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  /* !LINKSTO Dem.SWS_Dem_01242,1 */
  if (Dem_InitializationState == DEM_UNINITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetEventConfirmationThresholdCounter, DEM_E_UNINIT);
  }
  else if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_SetEventConfirmationThresholdCounter, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_SetEventConfirmationThresholdCounter, DEM_E_WRONG_CONFIGURATION);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
#if (DEM_EVENT_CONFIRMATION_THRESHOLD_COUNTER_ADAPTABLE == STD_ON)
    if (DEM_IS_BIT_SET_IN_ARRAY(Dem_ConfirmThresholdAdaptable, EventId))
    {
#if (DEM_NUM_CMB_DTCS > 0U)
      const Dem_DTCConfIdxType DTCConfIdx = DEM_GBI_DTCCONFIDX(EventId);
      if (DEM_IS_DTC_COMBINED(DTCConfIdx))
      {
        const Dem_CmbDTCEvLnkType firstCmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx];
        const Dem_CmbDTCEvLnkType LastCmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx + 1U] - 1U;
        Dem_CmbDTCEvLnkType CmbEvIdx;
        for (CmbEvIdx = firstCmbEvIdx; CmbEvIdx <= LastCmbEvIdx; CmbEvIdx++)
        {
          const Dem_EventIdType CmbEventId = Dem_CmbDTCEvents[CmbEvIdx];
          /* !LINKSTO Dem.SWS_Dem_01243,1 */
          Dem_ConfirmationThresholdRuntime[CmbEventId] = FailureCycleCounterThreshold;
        }
      }
      else
#endif
      {
        /* !LINKSTO Dem.SWS_Dem_01243,1 */
        Dem_ConfirmationThresholdRuntime[EventId] = FailureCycleCounterThreshold;
      }
      Result = E_OK;
    }
#else
  TS_PARAM_UNUSED(EventId);
  TS_PARAM_UNUSED(FailureCycleCounterThreshold);
#endif /* (DEM_EVENT_CONFIRMATION_THRESHOLD_COUNTER_ADAPTABLE == STD_ON) */
  }

  DBG_DEM_SETEVENTCONFIRMATIONTHRESHOLDCOUNTER_EXIT(Result, EventId, FailureCycleCounterThreshold);

  return Result;
}

#if (DEM_INCLUDE_RTE == STD_ON)
#define Dem_STOP_SEC_CODE
#include <Dem_MemMap.h>
#else
#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>
#endif

#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*------------------[Dem_MainFunction]--------------------------------------*/

FUNC(void, DEM_CODE) Dem_MainFunction(void)
{
  DBG_DEM_MAINFUNCTION_ENTRY();

#if (DEM_DEV_ERROR_DETECT == STD_ON)
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_MainFunction, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
#endif /* DEM_DEV_ERROR_DETECT */

  /* !LINKSTO dsn.Dem.MainFunction.InitState,1 */
  /* verify initialization-status before performing any actions */
  if (DEM_INITIALIZED == Dem_InitializationState)
  {
    boolean QueueEntryIsFetched;

  /* 1st step: the gate entry is prepared indirectly when
   * events are processed (fault confirmation, event entry, debounce) */
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    boolean TriggerNvMWrite = FALSE;
#endif

    /* activate code for event burst reduction only if limits smaller than vent queue length */
    /* !LINKSTO dsn.Dem.MainFunction.EventBurstReduction.SuspendMax,1 */
#if ((DEM_MAX_HANDLED_PASSED_EVENTS_PER_SCHEDULING < DEM_BSW_ERROR_BUFFER_SIZE) || \
     (DEM_MAX_HANDLED_FAILED_EVENTS_PER_SCHEDULING < DEM_BSW_ERROR_BUFFER_SIZE))
    uint8_least HandlePassedEvents = DEM_MAX_HANDLED_PASSED_EVENTS_PER_SCHEDULING;
    uint8_least HandleFailedEvents = DEM_MAX_HANDLED_FAILED_EVENTS_PER_SCHEDULING;
#endif

    /* update timers used for debouncing */
    /* !LINKSTO dsn.Dem.MainFunction.NonEventSpecific,1 */
#if (DEM_NUM_DEBOUNCE_TIME > 0U)
    Dem_DebounceTimeTimerTick();
#endif
#if (DEM_NUM_DEBOUNCE_FREQUENCY > 0U)
    Dem_DebounceFrequencyTimerTick();
#endif
    /* !LINKSTO dsn.Dem.MainFunction.ErrorQueue,1 */
    do
    {
#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U)
       Dem_EventIdType RootId;
#endif
       Dem_ErrorQueueElementType QueueEntry = 0U;
       Dem_ReadErrorQueueReturnType ReadQueueRetVal;

      /*
       * ENTER critical section to protect the error-queue & queue-pointers
       *       call-context: Dem (Task)
       */
      DEM_ENTER_EXCLUSIVE_AREA();

      ReadQueueRetVal = Dem_ReadErrorQueueEntry(&QueueEntry);
      QueueEntryIsFetched = ReadQueueRetVal.Result;
#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U)
      RootId = ReadQueueRetVal.RootId;
#endif

      /*
       * LEAVE critical section
       */
      DEM_EXIT_EXCLUSIVE_AREA();

      if (QueueEntryIsFetched)
      {
        const Dem_EventIdType EventId = DEM_ERRORQUEUE_GET_EVID(QueueEntry);
        const Dem_EventStatusType EventStatus =
            (Dem_EventStatusType)DEM_ERRORQUEUE_GET_EVST(QueueEntry);
        Dem_StatusTransitionType TransitionType = Dem_ErrorQueueGetEventTFTOCTransitionBit(QueueEntry);
#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U)
        const Dem_EventKindType eventKind = Dem_GbiEventKind(RootId);
#else
#if ( (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_TESTFAILED) && \
      (DEM_FREEZE_FRAME_CAPTURE != DEM_TRIGGER_TESTFAILED) )
        const Dem_EventKindType eventKind = Dem_GbiEventKind(EventId);
#endif
#endif
        Dem_EventInfoType EventInfo;

        Dem_EventNotificationDataType Notification =
          {
            /* ReplacedEventMsg */
            {
#if (DEM_NUM_CMB_DTCS > 0U)
              FALSE,
#endif
              DEM_EVENT_ID_INVALID, 0x00U, 0x00U },
#if ( (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) || \
      (DEM_NUM_CMB_DTCS > 0U) )
            /* ProcessedEventMsg */
            {
#if (DEM_NUM_CMB_DTCS > 0U)
              FALSE,
#endif
              DEM_EVENT_ID_INVALID, 0x00U, 0x00U },
#endif
#if (DEM_TRIG_CB_ON_EVDAT == STD_ON)
              /* TriggerOnEvenData */
              DEM_EVENT_ID_INVALID,
#endif
#if ( (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) && \
      (DEM_SUPPORT_FIM_ON_FDC_TRESHOLD == STD_ON) )
              /* TriggerFimOnUnconfirmedData */
              DEM_EVENT_ID_INVALID,
#endif
#if ( (DEM_J1939_SUPPORT == STD_ON) && \
      (DEM_J1939_READING_DTC_SUPPORT == STD_ON) )
              /* J1939Dcm_DemTriggerOnDTCStatus */
              DEM_EVENT_ID_INVALID
#endif
          };

        Dem_ProcessEventJobMaskType ProcessEventJobs = 0x00U;

#if ( (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) || \
      (DEM_FREEZE_FRAME_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) )
        if (EventStatus == DEM_EVENT_STATUS_UNCONFIRMED)
        {
          /* consecutive UNCONFIRMED results are filtered out during queuing */
          ProcessEventJobs |= DEM_PROCESSEVENT_ENTRYUPDATE;
        }
        else
#endif
        {
#if ( (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_TESTFAILED) && \
      (DEM_FREEZE_FRAME_CAPTURE != DEM_TRIGGER_TESTFAILED) )
          if (eventKind == DEM_EVENT_KIND_SWC)
          {
            /* SWC events are filtered during event queuing */
            ProcessEventJobs |= DEM_PROCESSEVENT_ENTRYUPDATE;

#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE)
#if (DEM_TRIGGER_ON_DEQUALIFICATION_SUPPORT == STD_ON)
            /* no OBD entry update for passed events */
            if (EventStatus != DEM_EVENT_STATUS_PASSED)
#endif
            {
              if ( DEM_ERRORQUEUE_GET_DTC_PDTC_WHILE_CDTC_NOT_SET(QueueEntry) == TRUE )
              {
                /* Transition of DTC PDTC 0 -> 1 while CDTC not set. This is a special
                 * condition to update the first OBD FF (OBDonUDS or Classic). */
                TransitionType |= DEM_TRANSITION_DTC_PDTC_WHILE_CDTC_NOT_SET;
              }

#if (DEM_OBDONUDS_FF_SUPPORT == STD_ON)
              if (DEM_ERRORQUEUE_GET_DTC_TF(QueueEntry) == TRUE)
              {
                TransitionType |= DEM_TRANSITION_DTC_TF;
              }

              if ( (DEM_GET_OBD_VARIANT() == DEM_OBD_VARIANT_OBDONUDS) &&
                   (Dem_GbiDTCKind(EventId) == DEM_DTC_KIND_EMISSION_REL_DTCS) )
              {
                if ( DEM_ERRORQUEUE_GET_DTC_TFTOC(QueueEntry) == TRUE )
                {
                  /* Transition of DTC TFTOC 0 -> 1, this is a special condition only
                   * queued for OBDonUDS FF last occurrence update */
                  TransitionType |= DEM_TRANSITION_DTC_TFTOC;
                }
              }
#endif
            }
#endif /* (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE) */


#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_SINGLE)
            ProcessEventJobs |= DEM_PROCESSEVENT_OBDENTRYUPDATE;
#endif
          }
          else
#endif
          /* (eventKind == DEM_EVENT_KIND_BSW) */
          {
            /* for BSW events all new failed qualifications
             * are queued and have to be filtered out here */
            /* first FAILED might have been promoted to CONFIRMED (for threshold = 1) */
            /* !LINKSTO Dem.SetEventStatus.AsynchronousUDSStatusUpdate.BSW,1 */
            boolean ErrorReenterPrecondition =
              Dem_CheckEntryProcessingConditions(EventId, EventStatus, &TransitionType);

            ProcessEventJobs |= DEM_PROCESSEVENT_STATUSUPDATE;

            if (ErrorReenterPrecondition)
            {
              ProcessEventJobs |= DEM_PROCESSEVENT_ENTRYUPDATE;
#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_SINGLE)
              ProcessEventJobs |= DEM_PROCESSEVENT_OBDENTRYUPDATE;
#endif
            }
          }
        }

        EventInfo.EventId = EventId;
#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U)
        EventInfo.RootId = RootId;
#endif

        Dem_ProcessEvent(DEM_SID_MainFunction, EventInfo, EventStatus,
                         TransitionType, ProcessEventJobs, &Notification);

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
        /* flag to trigger NvM write after queue entry processing */
        TriggerNvMWrite = TRUE;
#endif

#if ( ( (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) || \
      (DEM_TRIG_CB_ON_EVDAT == STD_ON) ) || \
      ( (DEM_J1939_SUPPORT == STD_ON) && \
        (DEM_J1939_READING_DTC_SUPPORT == STD_ON) ) )
        Dem_ProcessEventNotifications(&Notification);
#endif

        /* activate code for event burst reduction only if limits smaller than vent queue length */
        /* !LINKSTO dsn.Dem.MainFunction.EventBurstReduction.SuspendMax,1 */
#if ((DEM_MAX_HANDLED_PASSED_EVENTS_PER_SCHEDULING < DEM_BSW_ERROR_BUFFER_SIZE) || \
     (DEM_MAX_HANDLED_FAILED_EVENTS_PER_SCHEDULING < DEM_BSW_ERROR_BUFFER_SIZE))
#if (DEM_MAX_HANDLED_PASSED_EVENTS_PER_SCHEDULING < DEM_BSW_ERROR_BUFFER_SIZE)
        if (EventStatus == DEM_EVENT_STATUS_PASSED)
        {
          HandlePassedEvents--;
        }
#endif
#if (DEM_MAX_HANDLED_FAILED_EVENTS_PER_SCHEDULING < DEM_BSW_ERROR_BUFFER_SIZE)
#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
        if ( (EventStatus == DEM_EVENT_STATUS_FAILED) ||
             (EventStatus == DEM_EVENT_STATUS_CONFIRMED) ||
             (EventStatus == DEM_EVENT_STATUS_UNCONFIRMED) )
#else
        if ( (EventStatus == DEM_EVENT_STATUS_FAILED) ||
             (EventStatus == DEM_EVENT_STATUS_CONFIRMED) )
#endif
        {
          HandleFailedEvents--;
        }
#endif /* DEM_MAX_HANDLED_FAILED_EVENTS_PER_SCHEDULING < DEM_BSW_ERROR_BUFFER_SIZE */
        /* Deviation TASKING-5 */
        if ( (HandlePassedEvents == 0U) || (HandleFailedEvents == 0U) )
        {
          break;
        }
#endif /* (DEM_MAX_HANDLED_PASSED_EVENTS_PER_SCHEDULING < DEM_BSW_ERROR_BUFFER_SIZE) || \
          (DEM_MAX_HANDLED_FAILED_EVENTS_PER_SCHEDULING < DEM_BSW_ERROR_BUFFER_SIZE) */
      }
    }
    while (QueueEntryIsFetched);

#if ( (DEM_INIT_MONITOR_REENABLED_SUPPORT == STD_ON) && \
      (DEM_USE_CB_INIT_MONITOR == STD_ON) )
    /* !LINKSTO Dem.ASR431.ControlDTCSetting.InitMonitorReason,1 */
    if (DEM_IS_INIT_MONITOR_PROCESSING_NEEDED())
    {
      Dem_ProcessInitMonitorReenable();
    }
#endif
    Dem_ProcessClearDTCNotification();
#if ( (DEM_NUM_FAILURECYCLES > 0U) && \
      (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON) )
    /* !LINKSTO dsn.Dem.MainFunction.FaultConfirmation,1 */
    if (Dem_DoProcessFaultConfirmation != FALSE)
    {
      /* is necessary to reset the trigger before setting the
       * CDTC bit to eliminate the possibility of losing a new
       * trigger rised while setting the CDTC bit */
      /* exclusively reset the fault confirmation trigger */
      DEM_ATOMIC_ASSIGN_8(Dem_DoProcessFaultConfirmation, FALSE);

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
      /* event failure cycle Counter has been changed */
      TriggerNvMWrite = TRUE;
#endif

      /* process fault confirmation for all stored events */
      Dem_SetCDTCOnConfirmation();
    }
#endif /* (DEM_NUM_FAILURECYCLES > 0U) && \
          (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON) */

    /* 2nd step: trigger the requests to the NvM module once
     * after all events are processed for performance reasons
     * always called outside the critical section */
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    /* check if NvM must be triggered */
    if (TriggerNvMWrite != FALSE)
    {
      /* event entries and/or event cycle counter have changed
       * -> trigger NvM write */
      Dem_CheckForTriggerNvmWriteGateEntry();
    }
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */

#if (DEM_OBD_CENTRALIZED_PID_REL_DISTANCE_HANDLING == STD_OFF)
    Dem_ProcessDistanceRelatedPIDs();
#endif
  }

  DBG_DEM_MAINFUNCTION_EXIT();
}

#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
/*------------------[Dem_GetSI30Status]-------------------------------------*/
FUNC(Std_ReturnType, DEM_CODE) Dem_GetSI30Status(
  Dem_EventIdType                        EventId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Status)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_GETSI30STATUS_ENTRY(EventId, Status);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetSI30Status, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_GetSI30Status, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetSI30Status, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_GetSI30Status, DEM_E_WRONG_CONFIGURATION);
  }
  else if (Status == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetSI30Status, DEM_E_PARAM_POINTER);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
  if (Dem_GbiEvAvailable(EventId) == FALSE)
  {
    /* event is disabled so the getting of SI30 status shall be skipped */
    /* E_NOT_OK return value remains */
  }
  else
#endif
  {
    /* no DET */
    {
      Dem_EventMemoryEntryPtrType EvMemEntry;

      DEM_ENTER_EXCLUSIVE_AREA();

      /* search for the event in event memory */
      if (Dem_SearchForEntry(EventId, &EvMemEntry, NULL_PTR) != FALSE)
      {
        *Status = EvMemEntry->SI30;
        Result = E_OK;
      } /* else: event not stored in event memory implicates no SI30 Status */

      /*
       * LEAVE critical section
       */
      DEM_EXIT_EXCLUSIVE_AREA();
    }
  }

  DBG_DEM_GETSI30STATUS_EXIT(
    Result, EventId, Status);
  return Result;
}

#if (DEM_SUPPORT_FIM_ON_FDC_TRESHOLD == STD_ON)
/*------------------[Dem_SetSI30Symptom]------------------------------------*/
FUNC(Std_ReturnType, DEM_CODE) Dem_SetSI30Symptom(Dem_EventIdType EventId)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_SETSI30SYMPTOM_ENTRY(EventId);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetSI30Symptom, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_SetSI30Symptom, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_SetSI30Symptom, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_SetSI30Symptom, DEM_E_WRONG_CONFIGURATION);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
  if (Dem_GbiEvAvailable(EventId) == FALSE)
  {
    /* event is disabled so the setting of SI 30 symptom shall be skipped */
    /* E_NOT_OK return value remains */
  }
  else
#endif
  {
    /* no DET */
    {
      Dem_EventMemoryEntryPtrType EvMemEntry;

      /*
       * ENTER critical section
       */
      DEM_ENTER_EXCLUSIVE_AREA();

      /* search for the event in event memory */
      if (Dem_SearchForEntry(EventId, &EvMemEntry, NULL_PTR) != FALSE)
      {
        /* Set SI30 Symptom to 1 */
        EvMemEntry->SI30 |= DEM_SI30_STATUS_SYMPTOM_SLC;
        Result = E_OK;
      } /* else: event not stored in event memory implicates no SI30 Status */

      /*
       * LEAVE critical section
       */
      DEM_EXIT_EXCLUSIVE_AREA();
    }
  }

  DBG_DEM_SETSI30SYMPTOM_EXIT(Result, EventId);
  return Result;
}

/*------------------[Dem_SetSI30Notification]-------------------------------*/
FUNC(Std_ReturnType, DEM_CODE) Dem_SetSI30Notification(
  Dem_EventIdType EventId)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_SETSI30NOTIFICATION_ENTRY(EventId);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetSI30Notification, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_SetSI30Notification, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (EventId == DEM_EVENT_ID_INVALID)
  {
    DEM_REPORT_ERROR(DEM_SID_SetSI30Notification, DEM_E_PARAM_DATA);
  }
  else if (EventId > DEM_MAX_EVENTID)
  {
    DEM_REPORT_ERROR(DEM_SID_SetSI30Notification, DEM_E_WRONG_CONFIGURATION);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
  if (Dem_GbiEvAvailable(EventId) == FALSE)
  {
    /* event is disabled so the setting of SI 30 notification shall
     * be skipped */
    /* E_NOT_OK return value remains */
  }
  else
#endif
  {
    /* no DET */
    {
      Dem_EventMemoryEntryPtrType EvMemEntry;

      /*
       * ENTER critical section
       */
      DEM_ENTER_EXCLUSIVE_AREA();

      /* search for the event in event memory */
      if (Dem_SearchForEntry(EventId, &EvMemEntry, NULL_PTR) != FALSE)
      {
        /* Set SI30 Notification to 1 */
        EvMemEntry->SI30 |= DEM_SI30_STATUS_WIR_SLC;
        Result = E_OK;
      } /* else: event not stored in event memory implicates no SI30 Status */

      /*
       * LEAVE critical section
       */
      DEM_EXIT_EXCLUSIVE_AREA();
    }
  }

  DBG_DEM_SETSI30NOTIFICATION_EXIT(Result, EventId);
  return Result;
}
#endif /* DEM_SUPPORT_FIM_ON_FDC_TRESHOLD == STD_ON */
#endif /* DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD */

/*==================[internal function definitions]=========================*/

/*------------------[NvData-related sub-functions]--------------------------*/

#if ( (DEM_USE_PERMANENT_STORAGE == STD_ON) || \
      (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U) )
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_NvMGetNvRAMBlockStatus(
  NvM_BlockIdType NvDataBlockId)
{
  Std_ReturnType Result;
  NvM_RequestResultType RestoredNvData;

  DBG_DEM_NVMGETNVRAMBLOCKSTATUS_ENTRY(NvDataBlockId);

  /* get status from NvM block */
  Result = NvM_GetErrorStatus(NvDataBlockId, &RestoredNvData);

  if ( (Result == E_OK) &&
       (RestoredNvData != NVM_REQ_OK) )
  {
    Result = E_NOT_OK;
  }

  DBG_DEM_NVMGETNVRAMBLOCKSTATUS_EXIT(Result, NvDataBlockId);
  return Result;
}
#endif /* (DEM_USE_PERMANENT_STORAGE == STD_ON) || \
          (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U) */

#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_SINGLE)
FUNC(void, DEM_CODE) Dem_ResetSingleOBDFreezeFrameNvData(void)
{
  DBG_DEM_RESETSINGLEOBDFREEZEFRAMENVDATA_ENTRY();

  /* !LINKSTO dsn.Dem.OBD.Dem_ResetSingleOBDFreezeFrameNvData.CriticalSection,1 */
  /*
   * ENTER critical section to protect the event memory
   *       call-context: Dem (Task)
   */
  DEM_ENTER_EXCLUSIVE_AREA();

  /* !LINKSTO dsn.Dem.OBD.Dem_ResetSingleOBDFreezeFrameNvData.EventIdInvalid,1 */
  /* set EventId to invalid */
  DEM_OBDFF_STORED_EVENT_ID = DEM_EVENT_ID_INVALID;

  /* !LINKSTO dsn.Dem.OBD.Dem_ResetSingleOBDFreezeFrameNvData.DataPaddingValue,1 */
  TS_MemSet(&DEM_OBDFF_STORED_DATA[0], DEM_DATA_PADDING_VALUE, DEM_SIZE_OBDFF_DATA);

  /*
   * LEAVE critical section
   */
  DEM_EXIT_EXCLUSIVE_AREA();

  DBG_DEM_RESETSINGLEOBDFREEZEFRAMENVDATA_EXIT();
}
#endif /* (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_SINGLE) */

STATIC FUNC(void, DEM_CODE) Dem_ResetNvData(void)
{
  Dem_EventIdType EvId;
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_OFF)
  uint8_least OriginIdx;
  Dem_SizeEvMemEntryType EntryIdx;
#endif
#if (DEM_OPCYC_NVSTORAGE == STD_ON)
  Dem_OperationCycleIdType OpCycleId;
#endif

  DBG_DEM_RESETNVDATA_ENTRY();

  /* init loop for events */
  for (EvId = 0U; EvId <= DEM_MAX_EVENTID; ++EvId)
  {
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
    if (Dem_GbiEvAvailable(EvId) == FALSE)
    {
      /* !LINKSTO EventAvailability.UdsStatusInitValue,1 */
      /* clear all DTC status bits for unavailable events */
      DEM_DTC_STATUS_MASKS[EvId] = DEM_NO_EVENT_AVAILABLE;
    }
    else
#endif
    {
    /* clear all DTC status bits beside "not tested this operating cycle"
     * and "not tested since last clear" */
    DEM_DTC_STATUS_MASKS[EvId] =
      DEM_UDS_STATUS_TNCSLC |
      DEM_UDS_STATUS_TNCTOC;
    }
  }

#if (DEM_IGNORE_RESET_EVENT_STATUS_FOR_ENTRY == STD_ON)
  TS_MemSet(&Dem_NvData.Dem_ResetStatusResistantTFStatus[0], 0U, DEM_RESISTANT_TF_ARRAY_SIZE);
#endif
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_OFF)
  /* init loop for event memories */
  for (OriginIdx = 0U; OriginIdx < DEM_MAXNUM_ORIGINS; ++OriginIdx)
  {
    /* for every event entry */
    for (EntryIdx = 0U; EntryIdx < Dem_SizeEventMem[OriginIdx]; ++EntryIdx)
    {
      /* mark entry in event memory as cleared */
      Dem_EventMem[OriginIdx][EntryIdx].EventId =
        DEM_EVENT_ID_INVALID;

      /* freeze frame counter of the entry needs not to be initialized */
      /* not necessary:  EventMem[OriginIdx][EntryIdx].OccCtr = 0 */

      /* SI30, FDC12, and OCCs of the entry need not to be initialized */
      /* not necessary:  EventMem[OriginIdx][EntryIdx].SI30 = 0 */
      /* not necessary:  EventMem[OriginIdx][EntryIdx].FDC12 = 0 */
      /* not necessary:  EventMem[OriginIdx][EntryIdx].OCC1 = 0 */
      /* not necessary:  EventMem[OriginIdx][EntryIdx].OCC2 = 0 */
      /* not necessary:  EventMem[OriginIdx][EntryIdx].OCC3 = 0 */
      /* not necessary:  EventMem[OriginIdx][EntryIdx].OCC4 = 0 */
      /* not necessary:  EventMem[OriginIdx][EntryIdx].OCC5 = 0 */
      /* not necessary:  EventMem[OriginIdx][EntryIdx].OCC6 = 0 */
      /* not necessary:  EventMem[OriginIdx][EntryIdx].OCC7 = 0 */
      /* not necessary:  Dem_NvData.EntryOBDFF[EntryIdx] */

      /* position of entry data will calculated on new entry */
      /* not necessary:  EventMem[OriginIdx][EntryIdx].EntryDataPos = 0 */
    }

    /* Dem_EntryDataFreePos[OriginIdx] may be NULL_PTR, if no event
     * configured for this memory has any entry data */
    if (Dem_EntryDataFreePos[OriginIdx] != NULL_PTR)
    {
      /* initialize free position of event memory entry data */
      *(Dem_EntryDataFreePos[OriginIdx]) = 0U;
    }

    /* event memory entry data need not to be initialized */
    /* Dem_EntryData[OriginIdx][0 .. DEM_SIZE_ENTRY_[DATA_ORIGIN]] = 0 */
  }
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_OFF */

#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_SINGLE)
  /* !LINKSTO dsn.Dem.OBD.Dem_ResetSingleOBDFreezeFrameNvDataCall,1 */
  /* set single OBD event memory entry data to default values */
  Dem_ResetSingleOBDFreezeFrameNvData();
#endif

  /* clear event memory overflow indication flags */
  DEM_OVFIND_FLAGS = 0U;

#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)
  /* clear permanent fault status */
  /* !LINKSTO Dem_OBD_0029,1 */
  DEM_PFC_STATUS = FALSE;
#endif

#if (DEM_OBD_CENTRALIZED_PID21_HANDLING == STD_OFF)
  /* clear PID$21 information */
  /* !LINKSTO Dem.OBD.PID$21.DistanceTraveled.MinValue,1 */
  Dem_ResetDistanceTraveledWhileMILIsActivated();
  Dem_NvData.MILPrevStatusOnlyOnOffRelevance = DEM_INDICATOR_OFF;
#endif

#if (DEM_OBD_CENTRALIZED_PID31_HANDLING == STD_OFF)
  Dem_NvData.TicksTraveledSinceDTCsCleared = 0U;
#endif

#if (DEM_NUM_INDICATOR_LINKS > 0U)
  {
    Dem_IndicatorIdType IndicatorId;
    Dem_CounterDataIdxType LinkIdx;
    Dem_CounterDataIdxType ByteIdx;

    /* Deviation TASKING-1 */
    for (IndicatorId = 0U;
         IndicatorId < DEM_INDICATOR_MULTIPLICITY;
         IndicatorId++)
    {
      /* Deviation TASKING-1 */
      for (LinkIdx = 0U; LinkIdx < DEM_NUM_INDICATOR_COUNTER; ++LinkIdx)
      {
        /* clear indicator cycle counter */
        DEM_INDICATOR_CYC_COUNTER[IndicatorId][LinkIdx] = 0U;
      }

      /* Deviation TASKING-1 */
      for (ByteIdx = 0U; ByteIdx < DEM_NUM_INDICATOR_COUNTER_BIT; ++ByteIdx)
      {
        /*  set indicator cycle counter role flag
         * (i.e: DEM_INDICATORCOUNTER_ROLE_HEALING_CYCLE_COUNTER) */
        DEM_INDICATOR_CYC_COUNTER_ROLE[IndicatorId][ByteIdx] = 0xFFU;

        /* clear indicator cycle counter WIR status */
        DEM_INDICATOR_CYC_COUNTER_WIR_STATUS[IndicatorId][ByteIdx] = 0U;
      }
    }
  }
#endif /* (DEM_NUM_INDICATOR_LINKS > 0U) */

#if (DEM_OPCYC_NVSTORAGE == STD_ON)
  /* reset operation cycle state array */
  /* Deviation TASKING-1 */
  for (OpCycleId = 0U; OpCycleId < DEM_NUM_OPCYCLES; ++OpCycleId)
  {
    DEM_OPCYCLESTATE[OpCycleId] = DEM_CYCLE_STATE_END;
  }
#if (DEM_OBDONUDS_SUPPORT)
  Dem_NvData.DenominatorStatus = DEM_IUMPR_DEN_STATUS_NOT_REACHED;
#endif
#endif

#if (DEM_OPCYC_OBD_DCY_USED == STD_ON)
    Dem_NvData.Dem_OpCycleDCYIsQualified = FALSE;
#endif

#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT_FAULT_CONFIRMATION == STD_ON)
  {
    Dem_StatusCounterIndexType CounterIndex;
#if (DEM_NUM_CMB_DTCS > 0U)
    Dem_CmbDTCEvLnkType EvIdx;
#endif

    /* reset status counters used for aging/fault confirmation */
    /* Deviation TASKING-1 */
    for (CounterIndex = 0U; CounterIndex < DEM_STATUS_COUNTER_SIZE; CounterIndex++)
    {
      Dem_NvData.StatusCounter[CounterIndex] = 0U;
    }

#if (DEM_NUM_CMB_DTCS > 0U)
    /* reset failure status counters for combined events */
    for (EvIdx = 0U; EvIdx < DEM_NUM_CMB_EVENTS; EvIdx++)
    {
      DEM_CMBEV_FAILURE_CYC_COUNTER[EvIdx] = 0U;
    }
#endif
  }
#endif

#if (DEM_GET_DTCBYOCCURRENCETIME_SUPPORT == STD_ON)
  {
    Dem_DTCRequestType OccurKindRequest;

    for (OccurKindRequest = DEM_FIRST_FAILED_DTC;
          OccurKindRequest <= DEM_MOST_REC_DET_CONFIRMED_DTC; OccurKindRequest++)
    {
      /* reset all data related to DTC occurrence kind */
      DEM_OCCURKIND_STORED_EVENT_ID(OccurKindRequest) = DEM_EVENT_ID_INVALID;
    }
  }
#endif

#if (DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON)
  /* reset the StorageOrderId in event status block */
  DEM_SET_STORAGE_ORDER_ID_ARRAY(Dem_NvData.StorageOrderId, 0U);
#endif

#if (DEM_NVRAM_CONFIG_SIGNATURE_USED == STD_ON)
  /* !LINKSTO Dem.NvDataSignature.NonVolatileStore,1 */
  /* copied configuration signature value to Nv data */
  Dem_NvData.NvRamBlockSignature = DEM_CONFIG_NVRAM_SIGNATURE;
#endif /* DEM_GET_DTCBYOCCURRENCETIME_SUPPORT == STD_ON */

#if (DEM_OBD_Support == STD_ON)
  {
    uint8 RdyIdx;

    /* Deviation TASKING-1 */
    for (RdyIdx = 0; RdyIdx < DEM_READINESS_STATUS_ARRAY_SIZE; RdyIdx++)
    {
      /* clear stored Readiness status */
      Dem_NvData.ReadinessStatus[RdyIdx] = 0U;
    }
  }

#endif

#if (DEM_MAR_SUPPORT == STD_ON)
  /* !LINKSTO Dem.OBDonUDS.MAR.MiniDenominator.NonVolatileStorageInit,1 */
  Dem_NvData.MARData.Denominator = 0U;

  /* !LINKSTO Dem.OBDonUDS.MAR.MiniNumerator.NonVolatileStorageInit,1 */
  TS_MemSet(&Dem_NvData.MARData.Numerator[0], 0x00U, DEM_NUM_MAR_EVENTS);

  /* !LINKSTO Dem.OBDonUDS.MAR.MonitorActivityRatio.NonVolatileStorageInit,1 */
  TS_MemSet(&Dem_NvData.MARData.Ratio[0], 0x00U, DEM_NUM_MAR_DTCS);
#endif

  DBG_DEM_RESETNVDATA_EXIT();
}

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
STATIC FUNC(void, DEM_CODE) Dem_RestoreImmediateData(boolean ResetImmediateNvData)
{
  uint8_least OriginIdx;
  Dem_SizeEvMemEntryType EntryIdx;
  Dem_EventIdType EvId;

  Std_ReturnType ReadBlockResult = E_NOT_OK;
  NvM_RequestResultType reqResult = NVM_REQ_NOT_OK;

#if (DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON)
  uint32 StorageOrderStatusBlockId =
    (DEM_GET_STORAGEORDERID_UINT32(Dem_NvData.StorageOrderId));
  /* initialize the LargestDataBlockId to the value
   * (StorageOrderStatusBlockId - 1U) to ensure the StorageOrderId Generator
   * is notified for the event data block with plausible LargestDataBlockId in
   * the case where event status block has a larger StorageOrderId than that
   * of the event data block */
  uint32 LargestDataBlockId = (StorageOrderStatusBlockId == 0U) ? 0U : (StorageOrderStatusBlockId - 1U);
#endif

#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE)
  P2VAR(Dem_GateEntryOBDFFPrimaryFragmentType,
    AUTOMATIC, DEM_VAR_CLEARED) GateOBDFFEntry = &Dem_NvGateEntryPrimaryData.OBDFFEntry;
#endif

  DBG_DEM_RESTOREIMMEDIATEDATA_ENTRY(ResetImmediateNvData);

#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON)
  /* !LINKSTO Dem.ASR40.SWS_Dem_00551_Implicit1,1 */
  /* !LINKSTO dsn.Dem.ImmediateStorage.CDTCBit.Init,1 */
  /* clear CDTC bits for the case, that Dem_NvData could be
   * loaded but one event memory entry (NvM block) got lost */
  for (EvId = 0U; EvId <= DEM_MAX_EVENTID; ++EvId)
  {
    DEM_CLR_EV_ST_MASK(EvId, DEM_UDS_STATUS_CDTC);
  }
#endif

  /* init loop for all event memories */
  for (OriginIdx = 0U; OriginIdx < (uint8)DEM_MAXNUM_ORIGINS; ++OriginIdx)
  {
    const Dem_SizeEvMemEntryType SizeEventMem = Dem_SizeEventMem[OriginIdx];

    /* event memory is used */
    if (SizeEventMem != (Dem_SizeEvMemEntryType)0U)
    {
      CONSTP2VAR(Dem_GateEntryBaseType, AUTOMATIC, DEM_VAR_CLEARED)
        GateEntryBase = Dem_NvGateEntryData[OriginIdx];
      const NvM_BlockIdType NvDataBlockId = Dem_NvDataBlockId[OriginIdx];
#if (DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON)
      Dem_GateEntryStorageOrderIdAndDTCStatusPtrType GateEntryStorageOrderId =
        Dem_GateEntryStorageOrderIdAndDTCStatus[OriginIdx];
#endif
#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE)
      if (OriginIdx == (DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U))
      {
          GateOBDFFEntry = &Dem_NvGateEntryPrimaryData.OBDFFEntry;
      }
#endif

      /* clear gate-entry (for the case that no event memory entry can be
       * restored) */
      GateEntryBase->EntryBase.EventId = DEM_EVENT_ID_INVALID;

      /* need not initialize entry data of the corresponding event memory
       * as during write to gate within Dem_StoreImmediately() only valid
       * freeze frame data are written and rest of the entry is initialized
       * to zero */

      /* Dem_EntryDataFreePos[OriginIdx] may be NULL_PTR, if no event
       * configured for this memory has any entry data */
      if (Dem_EntryDataFreePos[OriginIdx] != NULL_PTR)
      {
        /* initalize free position of event memory entry data */
        *(Dem_EntryDataFreePos[OriginIdx]) = 0U;
      }

      /* for each event memory entry */
      for (EntryIdx = 0U; EntryIdx < SizeEventMem; ++EntryIdx)
      {
        /* --- transfer NVRAM content into gate-entry --- */

        const Dem_EventMemoryEntryPtrType EvMemEntry =
          &Dem_EventMem[OriginIdx][EntryIdx];

        /* verify the signature for reset of Nv data */
        /* Deviation TASKING-6 */
        if (ResetImmediateNvData == FALSE)
        {
          /* select corresponding NVRAM block dataset */
          ReadBlockResult = NvM_SetDataIndex(NvDataBlockId, (uint8)EntryIdx);

          /* queue read request of gate-entry to NvM - NvM_DstPtr is unused,
           * as permanent RAM block (gate-entry) is configured */
          if (ReadBlockResult == E_OK)
          {
             ReadBlockResult = NvM_ReadBlock(NvDataBlockId, NULL_PTR);
          }
        }

        /* if NvM read request was not accepted */
        if (ReadBlockResult == E_OK)
        {
          Std_ReturnType Result;

          /* trigger the memory-stack main functions synchronously */
          DEM_STORAGEWAITNVMREADY(NvDataBlockId);

          /* check if NVRAM dataset was successfully restored */
          Result = NvM_GetErrorStatus(NvDataBlockId, &reqResult);

          /* Nv-data consistence-checks against configuration are not done and
           * has to be ensured for example by the ECU flash-process */
          if ( (E_OK == Result) && (NVM_REQ_OK == reqResult) )
          {
            /* --- transfer gate-entry into event memory entry --- */

            EvId = GateEntryBase->EntryBase.EventId;

            /* restore EventId from gate-entry */
            EvMemEntry->EventId = EvId;

            /* mark event entry as unchanged concerning its persistent data */
            EvMemEntry->EntryStatus = DEM_ENTRY_UNCHANGED;

            /* check if event exists in the event memory */
            if (EvId != DEM_EVENT_ID_INVALID)
            {
              /* !LINKSTO dsn.Dem.ImmediateStorage.DiscardDuplicateEntries,1 */
              if (DEM_IS_BIT_SET_IN_ARRAY(Dem_EvMemEntryExists, EvId))
              {
                /* duplicate entry detected for the same event, indicating
                 * inconsistent NvM contents. Design decision is to retain the
                 * first found entry */
                EvMemEntry->EventId = DEM_EVENT_ID_INVALID;

#if (DEM_NV_STORAGE_EMPTY_EVMEM_ENTRIES == STD_ON)
                /* mark entry as changed so that at least initialized data
                 * is stored persistently during next shutdown */
                EvMemEntry->EntryStatus = DEM_ENTRY_CHANGED;
#else
                /* only occupied entries will be stored, to avoid NvRAM aging */
#endif
              }
              else
              {
                Dem_SizeEntryDataType EntryDataFreePos = 0U;
                const Dem_SizeEntryDataType sizeEntryData =
                  Dem_EvMemEntrySize(EvId, TRUE);

                if (Dem_EntryDataFreePos[OriginIdx] != NULL_PTR)
                {
                  EntryDataFreePos = *(Dem_EntryDataFreePos[OriginIdx]);
                }

                /* initalize free position of event memory entry data */
                EvMemEntry->EntryDataPos = EntryDataFreePos;

#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U)
                /* restore RootId from gate-entry */
                EvMemEntry->RootId = GateEntryBase->EntryBase.RootId;
#endif

                /* restore OccCtr and OccOrder from gate-entry */
                EvMemEntry->OccCtr = GateEntryBase->EntryBase.OccCtr;

                EvMemEntry->OccOrder = GateEntryBase->EntryBase.OccOrder;

                /* restore CSLF, CSFF and FAILEDCYCLES from gate-entry */
#if (DEM_OPCYCLE_CTR_CSLF_SUPPORT == STD_ON)
                EvMemEntry->CSLF = GateEntryBase->EntryBase.CSLF;
#endif
#if (DEM_OPCYCLE_CTR_CSFF_SUPPORT == STD_ON)
                EvMemEntry->CSFF = GateEntryBase->EntryBase.CSFF;
#endif
#if (DEM_OPCYCLE_CTR_FAILEDCYCLES_SUPPORT == STD_ON)
                EvMemEntry->FAILEDCYCLES = GateEntryBase->EntryBase.FAILEDCYCLES;
#endif

#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
                /* restore SI30, FDC12, and OCCs from gate-entry */
                EvMemEntry->SI30 = GateEntryBase->EntryBase.SI30;
                EvMemEntry->FDC12 = GateEntryBase->EntryBase.FDC12;
                EvMemEntry->OCC1 = GateEntryBase->EntryBase.OCC1;
                EvMemEntry->OCC2 = GateEntryBase->EntryBase.OCC2;
                EvMemEntry->OCC3 = GateEntryBase->EntryBase.OCC3;
                EvMemEntry->OCC4 = GateEntryBase->EntryBase.OCC4;
                EvMemEntry->OCC6 = GateEntryBase->EntryBase.OCC6;
                EvMemEntry->OCC7 = GateEntryBase->EntryBase.OCC7;
#if (DEM_VCC_OCC5_USED == STD_ON)
                /* !LINKSTO dsn.Dem.OBD.OCC5.ExtensionDemRestoreImmediateData,1 */
                EvMemEntry->OCC5 = GateEntryBase->EntryBase.OCC5;
#endif
#endif /* DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD */

#if (DEM_NUM_FAILURECYCLES > 0U)
                /* restore EventFailureCycleCounter from gate-entry */
                EvMemEntry->EventFailureCycleCounter =
                  GateEntryBase->EntryBase.EventFailureCycleCounter;
#endif
#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE)
                if (OriginIdx == (DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U))
                {
                  if (Dem_GbiDTCKind(EvId) == DEM_DTC_KIND_EMISSION_REL_DTCS)
                  {
                    /* copy gate-entry OBD FF occurrence order into OBD event memory
                     * occurrence order */
                    DEM_OBDFF_ENTRY_OCCURRENCE(EntryIdx) =
                      GateOBDFFEntry->OBDFF.OBDOccOrder;

                    /* copy gate-entry OBD FF data into OBD event memory data */
                    TS_MemCpy(DEM_OBDFF_ENTRY_FFDATA_LINK(EntryIdx),
                      GateOBDFFEntry->OBDFF.OBDFFData,
                      DEM_SIZE_OBDFF_DATA);

#if (DEM_OBDONUDS_FF_SUPPORT == STD_ON)
                    /* Deviation MISRAC2012-2 */
                    if (DEM_GET_OBD_VARIANT() == DEM_OBD_VARIANT_OBDONUDS)
                    {
                      /* copy gate-entry last OBD FF data into OBD event memory data */
                      TS_MemCpy(DEM_OBDFF_ENTRY_FFDATA_2_LINK(EntryIdx),
                        GateOBDFFEntry->OBDFF.OBDFFData2,
                        DEM_SIZE_OBDONUDS_OBD_FF);
                    }
#endif
                  }
                }
#endif /* DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE */
#if (DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON)
                /* !LINKSTO dsn.Dem.IntermediateNvStorageOfDTCStatus.RestoreDTCStatus,1 */
                /* TNCSLC, TFSLC and CDTC bits based on the event memory entry
                   need not be recovered when the complete event status byte
                   is already restored */
                if (Dem_RestoreIntermediateDTCstatus(StorageOrderStatusBlockId,
                                                     &LargestDataBlockId,
                                                     GateEntryStorageOrderId,
                                                     EvId) != TRUE)
#endif /* (DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON) */
                {
                  Dem_RestoreDerivedEventStatus(GateEntryBase, EvMemEntry, EvId);
                }
                /* check if event data exists */
                if (sizeEntryData > 0U)
                {
                  /* copy gate-entry data into event memory entry data */
                  TS_MemCpy(&Dem_EntryData[OriginIdx][EntryDataFreePos],
                    (Dem_EntryDataPtrConstType)Dem_GateEntryData[OriginIdx],
                    sizeEntryData);

                  /* recalculate free position of event memory entry data */
                  *(Dem_EntryDataFreePos[OriginIdx]) += sizeEntryData;
                }

                /* set EvEntryExists status of the corresponding event or all combined events */
                Dem_SetEvEntryExists(EvId, TRUE);
              }
            }
            /* else: not necessary to reset any other data of this entry */
          }
          else /* reqResult != NVM_REQ_OK */
          {
            /* clear event memory entry */
            EvMemEntry->EventId = DEM_EVENT_ID_INVALID;

#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U)
            EvMemEntry->RootId = DEM_EVENT_ID_INVALID;
#endif

            /* not necessary to reset EvMemEntry->OccCtr (= 0) */
            /* not necessary to reset EvMemEntry->OccOrder (= 0) */
            /* for DEM_EXTENDED_DATA_CAPTURE set to
             * DEM_TRIGGER_ON_FDC_THRESHOLD: */
            /* - not necessary to reset EvMemEntry->SI30 (= 0) */
            /* - not necessary to reset EvMemEntry->FDC12 (= 0) */
            /* - not necessary to reset EvMemEntry->OCC1 (= 0) */
            /* - not necessary to reset EvMemEntry->OCC2 (= 0) */
            /* - not necessary to reset EvMemEntry->OCC3 (= 0) */
            /* - not necessary to reset EvMemEntry->OCC4 (= 0) */
            /* - not necessary to reset EvMemEntry->OCC6 (= 0) */
            /* - not necessary to reset EvMemEntry->OCC7 (= 0) */
            /* not necessary to reset EvMemEntry->EntryDataPos (= 0) */
            /* not necessary to reset EvMemEntry->CSLF (= 0) */
            /* not necessary to reset EvMemEntry->CSFF (= 0) */
            /* not necessary to reset EvMemEntry->FAILEDCYCLES (= 0) */
            /* not necessary to reset event memory entry data */
            /* not necessary to reset Dem_EntryOBDFF[EntryIdx] */

            /* !LINKSTO Dem.NvStorageEmptyEvMemEntries.Shutdown,1 */
            /* restoration of data from NvM was not successful,
             * depend on configuration: */
#if (DEM_NV_STORAGE_EMPTY_EVMEM_ENTRIES == STD_ON)
            /* mark entry as changed so that at least initialized data
             * is stored persistently during next shutdown */
            EvMemEntry->EntryStatus = DEM_ENTRY_CHANGED;
#else
            /* only occupied entries will be stored, to avoid NvRAM aging */
#endif
          }
        }
        else /* ReadBlockResult != E_OK */
        {
          /* clear event memory entry */
          EvMemEntry->EventId = DEM_EVENT_ID_INVALID;

#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U)
          EvMemEntry->RootId = DEM_EVENT_ID_INVALID;
#endif

          /* not necessary to reset EvMemEntry->OccCtr (= 0) */
          /* not necessary to reset EvMemEntry->OccOrder (= 0) */
          /* for DEM_EXTENDED_DATA_CAPTURE set to
           * DEM_TRIGGER_ON_FDC_THRESHOLD: */
          /* - not necessary to reset EvMemEntry->SI30 (= 0) */
          /* - not necessary to reset EvMemEntry->FDC12 (= 0) */
          /* - not necessary to reset EvMemEntry->OCC1 (= 0) */
          /* - not necessary to reset EvMemEntry->OCC2 (= 0) */
          /* - not necessary to reset EvMemEntry->OCC3 (= 0) */
          /* - not necessary to reset EvMemEntry->OCC4 (= 0) */
          /* - not necessary to reset EvMemEntry->OCC6 (= 0) */
          /* - not necessary to reset EvMemEntry->OCC7 (= 0) */
          /* not necessary to reset EvMemEntry->EntryDataPos (= 0) */
          /* not necessary to reset EvMemEntry->CSLF (= 0) */
          /* not necessary to reset EvMemEntry->CSFF (= 0) */
          /* not necessary to reset EvMemEntry->FAILEDCYCLES (= 0) */
          /* not necessary to reset event memory entry data */
          /* not necessary to reset Dem_EntryOBDFF[EntryIdx] */

          /* !LINKSTO Dem.NvStorageEmptyEvMemEntries.Shutdown,1 */
          /* invalid data exist (as read was not successful),
           * depend on configuration: */
#if (DEM_NV_STORAGE_EMPTY_EVMEM_ENTRIES == STD_ON)
          /* mark entry as changed so that at least initialized data
           * is stored persistently during next shutdown */
          EvMemEntry->EntryStatus = DEM_ENTRY_CHANGED;
#else
          /* only occupied entries will be stored, to avoid NvRAM aging */
#endif
        }
      }
    }
  }
#if (DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON)
  /* notify the StorageOrderId generator with the largest StorageOrderId among
   * all the event data blocks */
  Dem_NotifyUsedStorageOrderId(LargestDataBlockId, DEM_STORAGEORDERID_DATABLOCK);
#endif
  DBG_DEM_RESTOREIMMEDIATEDATA_EXIT(ResetImmediateNvData);
}

STATIC FUNC(void, DEM_CODE) Dem_RestoreDerivedEventStatus(
  P2VAR(Dem_GateEntryBaseType, AUTOMATIC, DEM_VAR_CLEARED) GateEntryBase,
  Dem_EventMemoryEntryPtrType                              EvMemEntry,
  Dem_EventIdType                                          EventId)
{
#if (DEM_NUM_FAILURECYCLES > 0U)
  uint16 EventFailureClassIdx = Dem_GbiEventFailureClassIdx(EventId);
#endif

  DBG_DEM_RESTOREDERIVEDEVENTSTATUS_ENTRY(GateEntryBase, EvMemEntry, EventId);

#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
  /* do NOT set UDS status bits if event only reached UNCONFIRMED
                     level before entry was stored to NVRAM */
  if (EvMemEntry->FDC12 == (uint8)DEM_FDC_VALUE_FAILED)
#endif
  {
    /* !LINKSTO Dem.ASR40.SWS_Dem_00551_Implicit1,1 */
    /* set the status bits consistently for the case when they may
     * not have been restored during NvM_ReadAll():
     * only bits TNCSLC, CDTC and TFSLC are set as they can directly
     * be derived from existing event memory entries */
    DEM_CLR_EV_ST_MASK(EventId, DEM_UDS_STATUS_TNCSLC);
#if ( (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) && \
    (DEM_STATUS_BIT_HANDLING_TESTFAILEDSINCELASTCLEAR == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT) )
    if (!DEM_IS_ANY_BIT_SET(EvMemEntry->SI30, DEM_SI30_STATUS_AGEDDTC) )
#endif
    {
      DEM_SET_EV_ST_MASK(EventId, DEM_UDS_STATUS_TFSLC);
    }
    /* set the CDTC bit if
     * the event has default configuration for fault confirmation
     * (i.e. CDTC bit is set immediately after the event gets
     * qualified as failed)
     * or the restored failure counter value equals the
     * configured failure counter threshold value for the event */
#if (DEM_NUM_FAILURECYCLES > 0U)
    if ((EventFailureClassIdx == DEM_NO_FAULT_CONFIRMATION) ||
        /* defensive check to capture recalibrated configuration threshold */
        (EvMemEntry->EventFailureCycleCounter >=
          DEM_INTERN_EVT_FAILCYC_CTR_THRESHOLD(EventId, EventFailureClassIdx)))
#endif
    {
#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
      if (!DEM_IS_ANY_BIT_SET(EvMemEntry->SI30, DEM_SI30_STATUS_AGEDDTC) )
#endif
      {
#if (DEM_OPCYC_OBD_DCY_USED == STD_ON)
        if (GateEntryBase->EntryBase.CDTCFlag == TRUE)
#endif
        {
          DEM_SET_EV_ST_MASK(EventId, DEM_UDS_STATUS_CDTC);
        }
      }
    }
  }
  TS_PARAM_UNUSED(GateEntryBase);
  TS_PARAM_UNUSED(EvMemEntry);

  DBG_DEM_RESTOREDERIVEDEVENTSTATUS_EXIT(GateEntryBase, EvMemEntry, EventId);
}
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */

#if (DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON)
STATIC FUNC(void, DEM_CODE) Dem_NotifyUsedStorageOrderId(
  uint32                      LargestStorageOrderId,
  Dem_StorageOrderIdBlockType BlockType)
{
  DBG_DEM_NOTIFYUSEDSTORAGEORDERID_ENTRY(LargestStorageOrderId, BlockType);

  if (BlockType == DEM_STORAGEORDERID_STATUSBLOCK)
  {
    Dem_StorageOrderIdGeneratorState.LastBlockType =
      DEM_STORAGEORDERID_STATUSBLOCK;
    /* update StorageOrderIdGenerator counter with the value corresponding
     * to the StorageOrderId of the event status block */
    Dem_StorageOrderIdGeneratorState.StorageOrderIdCounter =
      LargestStorageOrderId;
  }
  else
  {
    if (LargestStorageOrderId > Dem_StorageOrderIdGeneratorState.StorageOrderIdCounter)
    {
      Dem_StorageOrderIdGeneratorState.LastBlockType =
        DEM_STORAGEORDERID_DATABLOCK;
      /* update StorageOrderIdGenerator counter with the value corresponding
       * to the largest StorageOrderId stored in data blocks */
      Dem_StorageOrderIdGeneratorState.StorageOrderIdCounter =
        LargestStorageOrderId;
    }
  }

  DBG_DEM_NOTIFYUSEDSTORAGEORDERID_EXIT(LargestStorageOrderId, BlockType);
}

STATIC FUNC(void, DEM_CODE) Dem_RestoreDTCStatus(
  P2CONST(uint8, AUTOMATIC, DEM_APPL_DATA) DataValue,
  Dem_EventIdType                          EventId)
{
#if (DEM_NUM_CMB_DTCS > 0U)
  const Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
#endif
  DBG_DEM_RESTOREDTCSTATUS_ENTRY(DataValue, EventId);

#if (DEM_NUM_CMB_DTCS > 0U)
  if (DEM_IS_DTC_COMBINED(DTCConfIdx))
  {
    /* restore event status of all combined events */
    const Dem_CmbDTCEvLnkType LastCmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx + 1U] - 1U;
    Dem_CmbDTCEvLnkType CmbEvIdx;
    Dem_EventIdType CmbEventId;
    uint8 DTCStatusIdx = 0U;

    for (CmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx]; CmbEvIdx <= LastCmbEvIdx; CmbEvIdx++)
    {
      CmbEventId = Dem_CmbDTCEvents[CmbEvIdx];
      DEM_DTC_STATUS_MASKS[CmbEventId] = DataValue[DTCStatusIdx];
      DTCStatusIdx++;
    }
  }
  else
#endif /* DEM_NUM_CMB_DTCS > 0U */
  {
    /* restore event status of respective non-combined event */
    DEM_DTC_STATUS_MASKS[EventId] = *DataValue;
  }

  DBG_DEM_RESTOREDTCSTATUS_EXIT(DataValue, EventId);
}
STATIC FUNC(boolean, DEM_CODE) Dem_RestoreIntermediateDTCstatus(
  uint32                                    StorageOrderStatusBlockId,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC)       LargestDataBlockId,
  P2CONST(uint8, AUTOMATIC, DEM_APPL_DATA)  GateEntryStorageOrderId,
  Dem_EventIdType                           EventId)
{
  boolean Result = FALSE;
  uint32 StorageOrderDataBlockId;

  DBG_DEM_RESTOREINTERMEDIATEDTCSTATUS_ENTRY(StorageOrderStatusBlockId,
    LargestDataBlockId, GateEntryStorageOrderId, EventId);

  if (Dem_GbiImmediateStorage(EventId))
  {
    /* get the StorageOrderId of the current event entry in
       event data block*/
    StorageOrderDataBlockId =
      (DEM_GET_STORAGEORDERID_UINT32(GateEntryStorageOrderId));
    /* when the StorageOrderId of an entry in event data block is larger than
     * StorageOrderId of event status block the DTC status must be restored
     * from respective event data block */
    if (StorageOrderDataBlockId > StorageOrderStatusBlockId)
    {
      /* capture the LargestDataBlockId in order to notify the
       * StorageOrderId generator for the event data block */
      *LargestDataBlockId = StorageOrderDataBlockId;
      /* restore the DTC status from respective event data block */
      Dem_RestoreDTCStatus(&GateEntryStorageOrderId[DEM_STARTPOS_DTC_STATUS], EventId);
      Result = TRUE;
    }
  }

  DBG_DEM_RESTOREINTERMEDIATEDTCSTATUS_EXIT(IntermediateDTCrestored,
    StorageOrderStatusBlockId, LargestDataBlockId, GateEntryStorageOrderId,
    EventId);
  return Result;
}
#endif /* DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON */

#if ( (DEM_USE_PERMANENT_STORAGE == STD_ON) && \
      ((DEM_STATUS_BIT_STORAGE_TF == STD_OFF) || \
      (DEM_STATUS_BIT_STORAGE_TF_PER_EVENT_SUPPORT == STD_ON)) )
STATIC FUNC(void, DEM_CODE) Dem_ClearStatusBitStorageTestFailed(void)
{
  Dem_EventIdType EventId;

  DBG_DEM_CLEARSTATUSBITSTORAGETESTFAILED_ENTRY();

  /* !LINKSTO Dem.StatusBitStorageTestFailed.PerEvent.Enabled,1 */
  /* !LINKSTO Dem.StatusBitStorageTestFailed.PerEvent.Enabled.False,1 */
  /* !LINKSTO Dem.StatusBitStorageTestFailed.PerEvent.Enabled.True,1 */
  /* as Nv storage of TF bit is disabled, it is cleared during init
   * so that its value stored in Nv memory is not used and thus the
   * volatile storage behavior is ensured */
  /* init loop for events */
  for (EventId = 0U; EventId <= DEM_MAX_EVENTID; ++EventId)
  {
#if (DEM_STATUS_BIT_STORAGE_TF_PER_EVENT_SUPPORT == STD_ON)
        if (DEM_IS_TF_BIT_STORED_VOLATILE(EventId))
#endif /* DEM_STATUS_BIT_STORAGE_TF_PER_EVENT_SUPPORT == STD_ON */
    {
      /* clear DTC status bit "test failed" */
      DEM_CLR_EV_ST_MASK(EventId, DEM_UDS_STATUS_TF);
    }
  }

  DBG_DEM_CLEARSTATUSBITSTORAGETESTFAILED_EXIT();
}
#endif /* ((DEM_USE_PERMANENT_STORAGE == STD_ON) &&  \
          ((DEM_STATUS_BIT_STORAGE_TF == STD_OFF) || \
          (DEM_STATUS_BIT_STORAGE_TF_PER_EVENT_SUPPORT == STD_ON))) */

#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)
STATIC FUNC(void, DEM_CODE) Dem_PermanentMemoryInit(boolean ResetPermanentNvData)
{
  uint8_least EntryIdx;

  DBG_DEM_PERMANENTMEMORYINIT_ENTRY(ResetPermanentNvData);

  if (ResetPermanentNvData == TRUE)
  {
    Dem_EventMemoryPermanentUpdated = TRUE;
  }
  else
  {
    /* check the error status of the NvM block of permanent memory */
    /* !LINKSTO Dem_OBD_0075,1 */
    if (Dem_NvMGetNvRAMBlockStatus(DEM_NVM_BLOCK_ID_PERMANENT) == E_NOT_OK)
    {
      Dem_EventMemoryPermanentUpdated = TRUE;
    }
    else
    {
      Dem_EventMemoryPermanentUpdated = FALSE;
    }
  }

  /* recovery of Dem_EventMemoryPermanent[] from permanent memory
   * must be done within NvM_ReadAll() */

  for (EntryIdx = 0U;
       EntryIdx < DEM_MAX_NUMBER_EVENT_ENTRY_PER;
       EntryIdx++)
  {
    /* check the error status of the NvM block of permanent memory */
    if (Dem_EventMemoryPermanentUpdated == TRUE)
    {
      Dem_PermanentMemoryEntryType Entry = 0U;

      /* initialize RAM mirror of permanent memory */
      /* !LINKSTO Dem_OBD_0076,3, Dem_OBD_0007,2 */
      DEM_SET_PERMANENT_MEMORY_EVENT_ID(Entry, DEM_EVENT_ID_INVALID);

      /* initialize the rest of the status of the permanent fault entry for
       * robustness sake - compiler could anyway optimize this away */
      DEM_CLR_PERMANENT_MEMORY_PFC_CYCLE_COND(Entry);
      DEM_CLR_PERMANENT_MEMORY_PASSED_CYCLE_COND(Entry);
      DEM_CLR_PERMANENT_MEMORY_FILL_COND(Entry);

      Dem_EventMemoryPermanent[EntryIdx] = Entry;

      /* !LINKSTO Dem_OBD_0072,2 */
      Dem_EventMemoryPermanentNonVolatileStored[EntryIdx] =
        DEM_PERMANENT_MEMORY_V_STORED;
    }
    else if (DEM_GET_PERMANENT_MEMORY_EVENT_ID(
               Dem_EventMemoryPermanent[EntryIdx]) != DEM_EVENT_ID_INVALID)
    /* initialize all not empty Dem_EventMemoryPermanentNonVolatileStored
     * with DEM_PERMANENT_MEMORY_NV_STORED */
    {
      /* !LINKSTO Dem_OBD_0026,2 */
      Dem_EventMemoryPermanentNonVolatileStored[EntryIdx] =
        DEM_PERMANENT_MEMORY_NV_STORED;
    }
    else
    /* initialize all empty Dem_EventMemoryPermanentNonVolatileStored
     * with DEM_PERMANENT_MEMORY_V_STORED */
    {
      /* !LINKSTO Dem_OBD_0066,1 */
      Dem_EventMemoryPermanentNonVolatileStored[EntryIdx] =
        DEM_PERMANENT_MEMORY_V_STORED;
    }
  }

  DBG_DEM_PERMANENTMEMORYINIT_EXIT(ResetPermanentNvData);
}
#endif /* #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U) */

#if (defined DEM_OPCYC_WARMUP_ID)
STATIC FUNC (void, DEM_CODE) Dem_IncrementWarmupCtr(void)
{
  if (Dem_NvData.OBDWarmupCycleCtr < 255U)
  {
    /* increment warm-up counter */
    (Dem_NvData.OBDWarmupCycleCtr)++;
  }
}

#if (DEM_OBD_CENTRALIZED_PID21_HANDLING == STD_OFF)

STATIC FUNC (void, DEM_CODE) Dem_ProcessWUCWhileMILIsDeactivated(void)
{
  const Dem_IndicatorStatusType MILCurrentStatus =
    Dem_InternalGetIndicatorStatus(DEM_MIL_ID, TRUE);

  if ( (Dem_NvData.TicksTraveledWhileMILIsActivated != 0U) &&
       (MILCurrentStatus == DEM_INDICATOR_OFF) )
  {
    /* increment warm-up without MIL active counter */
    Dem_NvData.NrWUCsWhileMILInactive++;

    /* !LINKSTO Dem.OBD.PID$21.DistanceTraveled.ResetAfter40WUCs,1 */
    if (Dem_NvData.NrWUCsWhileMILInactive == DEM_WUC_ELAPSE_TO_RESET_PID21)
    {
      /* reset the distance traveled while MIL is activated information */
      Dem_NvData.TicksTraveledWhileMILIsActivated = 0U;
    }
  }
}
#endif
#endif /* #if (defined DEM_OPCYC_WARMUP_ID) */

#if ((DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) && \
     (DEM_VCC_OCC5_USED == STD_ON))
STATIC FUNC(void, DEM_CODE) Dem_IncrementAllOcc5(void)
{
  Dem_SizeEvMemEntryType       EvMemEntryIdx;
  Dem_EventMemoryEntryPtrType  PrimMemEntry;

  DBG_DEM_INCREMENTALLOCC5_ENTRY();

  PrimMemEntry = Dem_EventMem[DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U];

  /* loop over all configured events */
  /* Deviation TASKING-1 */
  /* !LINKSTO dsn.Dem.OBD.OCC5.CriticalSection,1 */
  /* ENTER critical section to protect event memory entry */
  DEM_ENTER_EXCLUSIVE_AREA();

  for (EvMemEntryIdx = 0U; EvMemEntryIdx < DEM_MAX_NUMBER_EVENT_ENTRY_PRI; ++EvMemEntryIdx)
  {
    Dem_EventMemoryEntryPtrType EvMemEntry = &(PrimMemEntry[EvMemEntryIdx]);
    const Dem_EventIdType EvId = PrimMemEntry[EvMemEntryIdx].EventId;

    if (EvId != DEM_EVENT_ID_INVALID)
    {
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
      if (Dem_GbiEvAvailable(EvId) == FALSE)
      {
        /* event is disabled so the event shall be skipped */
      }
      else
#endif
      {
        /* check whether current event is emission related */
        /* !LINKSTO dsn.Dem.OBD.OCC5.Dem_IncrementAllOcc5.DtcKind,1 */
        if (Dem_GbiDTCKind(EvId) == DEM_DTC_KIND_EMISSION_REL_DTCS)
        {
          /* !LINKSTO dsn.Dem.OBD.OCC5.Dem_IncrementAllOcc5.Status,1 */
          /* !LINKSTO dsn.Dem.OBD.OCC5.Dem_IncrementAllOcc5.Increment,1 */
          if (!(DEM_IS_ANY_EV_ST_BIT_SET(EvId, DEM_UDS_STATUS_TFTOC|DEM_UDS_STATUS_WIR)))
          {
            if (EvMemEntry->OCC5 < 255U)
            {
              /* increment OCC5 */
              (EvMemEntry->OCC5)++;
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
              /* !LINKSTO dsn.Dem.VCC.EventMemoryEntryChanged,4 */
              Dem_CheckForImmediateEntryStorage(EvId,
                                                EvMemEntry,
                                                EvMemEntryIdx,
                                                DEM_NVM_NO_FORCE);
#endif
            }
          }
        }
      }
    }
  }
  /* LEAVE critical section */
  DEM_EXIT_EXCLUSIVE_AREA();

  DBG_DEM_INCREMENTALLOCC5_EXIT();
}
#endif /* (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) */

#if (DEM_MAR_SUPPORT == STD_ON)
STATIC FUNC(void, DEM_CODE) Dem_MarUpdateMARData(void)
{
  Dem_EventIdType EventId;
  Dem_MAREventIndexType Idx;
  Dem_MAREventIndexType NumEventToProcess;
  uint8 MiniDenominator;

  DBG_DEM_MARUPDATEMARDATA_ENTRY();

  /*
   * ENTER critical section
   */
  DEM_ENTER_EXCLUSIVE_AREA();

  /* !LINKSTO Dem.OBDonUDS.MAR.GeneralDenominator.Incrementation,1 */
  if (Dem_NvData.DenominatorStatus == DEM_IUMPR_DEN_STATUS_REACHED)
  {
    /* !LINKSTO Dem.OBDonUDS.MAR.MiniDenominator.Incrementation,1 */
    Dem_NvData.MARData.Denominator++;
  }

  MiniDenominator = Dem_NvData.MARData.Denominator;

  /* unless denominator reached max value, the 'simple' processing is done for
   * all events, because only the event specific numerator is updated; if the
   * denominator reached max value, the combined MAR events are handled in the
   * subsequent loop to determine and store the minimum/DTC specific ratio */
  NumEventToProcess =
    (MiniDenominator == DEM_MAR_ELEMENT_MAX_VALUE) ?
      DEM_NUM_MAR_SINGLE_EVENTS : DEM_NUM_MAR_EVENTS;

  /* the simple MAR update algorithm is used for non-combined MAR events and for
   * the combined MAR events when denominator has not reached its max value */
  /* Deviation TASKING-1 */
  for (Idx = 0U; Idx < NumEventToProcess; Idx++)
  {
    EventId = Dem_MAREvents[Idx];

#if (DEM_CALIBRATION_SUPPORT == STD_ON)
    if (Dem_GbiDTCKind(EventId) == DEM_DTC_KIND_EMISSION_REL_DTCS)
#endif
    {
      /* check if the event was tested in the current DCY and if its
       * mini-numerator didn't reached the maximum value */
      /* !LINKSTO Dem.OBDonUDS.MAR.MiniNumerator.MaxValue,1 */
      if ( (!DEM_IS_EV_ST_BIT_TNCTOC_SET(EventId)) &&
           (Dem_NvData.MARData.Numerator[Idx] < DEM_MAR_ELEMENT_MAX_VALUE) )
      {
        /* !LINKSTO Dem.OBDonUDS.MAR.MiniNumerator.Incrementation,1 */
        Dem_NvData.MARData.Numerator[Idx]++;
      }

      if (MiniDenominator == DEM_MAR_ELEMENT_MAX_VALUE)
      {
        /* store monitor activity ratio element */
        /* !LINKSTO Dem.OBDonUDS.MAR.MonitorActivityRatio.Update,1 */
        Dem_NvData.MARData.Ratio[Idx] = Dem_NvData.MARData.Numerator[Idx];
        /* reset the mini-numerator */
        /* !LINKSTO Dem.OBDonUDS.MAR.MiniNumerator.Reset,1 */
        Dem_NvData.MARData.Numerator[Idx] = 0U;
      }
    }
  }

  /*
   * LEAVE critical section
   */
  DEM_EXIT_EXCLUSIVE_AREA();

#if (DEM_NUM_MAR_CMB_DTCS > 0U)
  /* this check is performed in order to avoid opening an exclusive area
   * when it is known that additional MAR data update is not needed */
  if (MiniDenominator == DEM_MAR_ELEMENT_MAX_VALUE)
  {
    /*
     * ENTER critical section
     */
    DEM_ENTER_EXCLUSIVE_AREA();

    /* the MAR combined events are handled separately only when denominator
     * reaches its maximum value; intentionally check the NV-variable as it may
     * have been reset by a concurrent access from Dem_ResetPerformanceCounters() */
    if (Dem_NvData.MARData.Denominator == DEM_MAR_ELEMENT_MAX_VALUE)
    {
      Dem_MAREventIndexType DTCIdx;

      /* iterate through MAR combined DTCs */
      /* Deviation TASKING-1 */
      for (DTCIdx = 0U; DTCIdx < DEM_NUM_MAR_CMB_DTCS; DTCIdx++)
      {
        Dem_MAREventIndexType MAREvIdxStart = Dem_MAREventCombinationIdx[DTCIdx];
        Dem_MAREventIndexType MAREvIdxEnd = Dem_MAREventCombinationIdx[DTCIdx + 1U];
        Dem_MAREventIndexType MAREvIdx;

        /* the number of single MAR events is used as offset */
        Dem_MAREventIndexType RatioIdx = DTCIdx + DEM_NUM_MAR_SINGLE_EVENTS;

        /* initialize numerator of the combination with the largest possible value */
        uint8 CmbNumerator = DEM_MAR_ELEMENT_MAX_VALUE;

#if (DEM_CALIBRATION_SUPPORT == STD_ON)
        EventId = Dem_MAREvents[MAREvIdxStart];

        /* check whether the event combination is emissions relevant */
        if (Dem_GbiDTCKind(EventId) == DEM_DTC_KIND_EMISSION_REL_DTCS)
#endif
        {
          /* iterate through combined events of the MAR combination */
          for (MAREvIdx = MAREvIdxStart; MAREvIdx < MAREvIdxEnd; MAREvIdx++)
          {
            EventId = Dem_MAREvents[MAREvIdx];

            if ( (!DEM_IS_EV_ST_BIT_TNCTOC_SET(EventId)) &&
                 (Dem_NvData.MARData.Numerator[MAREvIdx] < DEM_MAR_ELEMENT_MAX_VALUE) )
            {
              Dem_NvData.MARData.Numerator[MAREvIdx]++;
            }

            /* !LINKSTO Dem.OBDonUDS.MAR.CmbEvents.UnavailableEventRatio,1 */
            if ( (Dem_NvData.MARData.Numerator[MAREvIdx] < CmbNumerator) &&
                 (Dem_GbiEvAvailable(EventId) == TRUE) )
            {
              CmbNumerator = Dem_NvData.MARData.Numerator[MAREvIdx];
            }

            /* reset the numerator of the combined events */
            /* !LINKSTO Dem.OBDonUDS.MAR.MiniNumerator.Reset,1 */
            Dem_NvData.MARData.Numerator[MAREvIdx] = 0U;
          }
        }

        /* update the Ratio of the combined DTC with the smallest numerator value
         * of the events in combination */
        /* !LINKSTO Dem.OBDonUDS.MAR.CmbEvents.MonitorActivityRatio,1 */
        Dem_NvData.MARData.Ratio[RatioIdx] = CmbNumerator;
      }
    }

    /*
     * LEAVE critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();
  }
#endif /* (DEM_NUM_MAR_CMB_DTCS > 0U) */

  if (MiniDenominator == DEM_MAR_ELEMENT_MAX_VALUE)
  {
    /* reset the mini-denominator when it reaches its max value */
    /* !LINKSTO Dem.OBDonUDS.MAR.MiniDenominator.Reset,1 */
    Dem_NvData.MARData.Denominator = 0U;
  }

  DBG_DEM_MARUPDATEMARDATA_EXIT();
}
#endif /* (DEM_MAR_SUPPORT == STD_ON) */

#if (DEM_DEV_FREEZE_FRAME_USED == STD_ON)
STATIC FUNC(void, DEM_CODE) Dem_InitDevFreezeFrameEntryIdx(void)
{
  Dem_SizeEvMemEntryType      SizePrimEventMem;
  Dem_SizeEvMemEntryType      EntryIdx;
  Dem_EventMemoryEntryPtrType PrimMemEntry;
  uint8                       IdxDevFF;
  Dem_EventIdType             CurEventIdDevFF;
  uint8                       IdxDevFFKind;

  DBG_DEM_INITDEVFREEZEFRAMEENTRYIDX_ENTRY();

  SizePrimEventMem = Dem_SizeEventMem[DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U];
  PrimMemEntry = Dem_EventMem[DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U];

  for (IdxDevFFKind = DEM_DEVFF_A; IdxDevFFKind <= DEM_DEVFF_B; ++IdxDevFFKind)
  {
    /* Loop through development freeze frames */
    for (IdxDevFF = 0U; IdxDevFF < Dem_SizeDevFFMem[IdxDevFFKind]; ++IdxDevFF)
    {
      CurEventIdDevFF = Dem_DevFFEventId[IdxDevFFKind][IdxDevFF];

      /* If a development freeze frame is stored in the current entry */
      if (CurEventIdDevFF != DEM_EVENT_ID_INVALID)
      {
        /* look in Primary memory for stored eventId of Freeze Frame A and B */
        for (EntryIdx = 0U; EntryIdx < SizePrimEventMem; ++EntryIdx)
        {
          if (PrimMemEntry[EntryIdx].EventId == CurEventIdDevFF)
          {
            /* initialize DevFFEntryIdx (used for lookup) in RAM for immediate storage enabled */
            PrimMemEntry[EntryIdx].DevFFEntryIdx[IdxDevFFKind] = IdxDevFF;
          }
        }
      }
    }
  }

  DBG_DEM_INITDEVFREEZEFRAMEENTRYIDX_EXIT();
}
#endif /* (DEM_DEV_FREEZE_FRAME_USED == STD_ON) */

/* !LINKSTO dsn.Dem.Displacement.Dem_IsEventAdvancedPassive,1 */
#if (DEM_USE_ADVANCED_EVENT_DISPLACEMENT == STD_ON)
STATIC FUNC(boolean, DEM_CODE) Dem_IsEventAdvancedPassive(
  Dem_EventMemoryEntryPtrType EvMemEntry,
  Dem_EventIdType             ReportedEventId)
{
  boolean EventIsAdvancedPassive = FALSE;

  DBG_DEM_ISEVENTADVANCEDPASSIVE_ENTRY(EvMemEntry, ReportedEventId);

  /* !LINKSTO dsn.Dem.Displacement.Dem_IsEventAdvancedPassive.Condition,1 */
  if ((!DEM_IS_ANY_BIT_SET(EvMemEntry->SI30, DEM_SI30_STATUS_EMISSIONRELATEDDTC)) &&
      (!DEM_IS_ANY_BIT_SET(EvMemEntry->SI30, DEM_SI30_STATUS_WIR_SLC)))
  {
    if (!DEM_IS_ANY_BIT_SET(EvMemEntry->SI30, DEM_SI30_STATUS_SYMPTOM_SLC))
    {
      EventIsAdvancedPassive = TRUE;
    }
    else if (EvMemEntry->OCC1 < DEM_ADV_PASSIVE_OCC1_LIMIT)
    {
      uint8_least PassiveTableLinesIterator = 0U;

      /* check whether given event configured as reported event in passive
       * table
       */
      for (PassiveTableLinesIterator = 0U;
           PassiveTableLinesIterator < DEM_NUM_OF_PASSIVE_TABLE_LINES;
           PassiveTableLinesIterator++)
      {
        const Dem_EventIdType AdvDisplReportedEventId =
          Dem_AdvDisplPassiveTableLineReportedEventIds[PassiveTableLinesIterator];

        CONSTP2CONST(Dem_AdvDisplPassiveTableLinePassiveEventsType, AUTOMATIC, DEM_CONST)
          advDisplPassiveEvents =
            &Dem_AdvDisplPassiveTableLinePassiveEvents[PassiveTableLinesIterator];

        if (ReportedEventId == AdvDisplReportedEventId)
        {
          uint8_least PassiveEventRefIterator = 0U;

          /* check whether given event is configured as passive event reference
           * in passive table
           */
          for (PassiveEventRefIterator = 0U;
               PassiveEventRefIterator < advDisplPassiveEvents->NumPassiveEvents;
               PassiveEventRefIterator++)
          {
            if (EvMemEntry->EventId ==
                advDisplPassiveEvents->PassiveEventId[PassiveEventRefIterator])
            {
              EventIsAdvancedPassive = TRUE;
            }
          }
        }
      }
    }
    else
    {
      /* do nothing */
    }
  }

  DBG_DEM_ISEVENTADVANCEDPASSIVE_EXIT(
    EventIsAdvancedPassive, EvMemEntry, ReportedEventId);

  return EventIsAdvancedPassive;
}
#endif /* (DEM_USE_ADVANCED_EVENT_DISPLACEMENT == STD_ON) */

#if ((DEM_OBD_EVENT_DISPLACEMENT == STD_ON) && (DEM_USE_EVENT_DISPLACEMENT == STD_ON))
/* !LINKSTO SWS_Dem_00695_refine,1 */
STATIC FUNC(boolean, DEM_CODE) Dem_IsDisplaceOBDEventEntryAllowed(
  Dem_EventIdType EventId)
{
  boolean Result = TRUE;

  DBG_DEM_ISDISPLACEOBDEVENTENTRYALLOWED_ENTRY(EventId);

  if (Dem_GbiDTCKind(EventId) == DEM_DTC_KIND_EMISSION_REL_DTCS)
  {
    if (DEM_IS_EV_ST_BIT_PDTC_SET(EventId))
    {
      Result = FALSE;
    }
    else
#if (DEM_OBDONUDS_FF_SUPPORT == STD_ON)
    /* Deviation MISRAC2012-2 */
    if (DEM_GET_OBD_VARIANT() == DEM_OBD_VARIANT_OBDONUDS)
    {
      /* When DEM_OBDONUDS_FF_SUPPORT is ON, every OBD relevant event in primary
       * memory holds an OBDonUDS FF, and hence it shall not be displaced */
      Result = FALSE;
    }
    /* Deviation MISRAC2012-2 */
    else
#endif
    {
#if (DEM_NUM_OF_PIDS_IN_OBDFF > 0U)
      Dem_EventIdType StoredOBDFFEventId = DEM_EVENT_ID_INVALID;
#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE)
      Dem_SizeEvMemEntryType SelectedEntryIndex = 0U;

      if (Dem_SelectEntryOfOBDFreezeFrameEvent(&SelectedEntryIndex, FALSE) == TRUE)
      {
        StoredOBDFFEventId =
          Dem_EventMem[(DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U)][SelectedEntryIndex].EventId;
      }
#elif (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_SINGLE)
      StoredOBDFFEventId = DEM_OBDFF_STORED_EVENT_ID;
#endif
      if (EventId == StoredOBDFFEventId)
      {
        Result = FALSE;
      }
      else
#endif /* (DEM_NUM_OF_PIDS_IN_OBDFF > 0U) */
      {
#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)
        if (Dem_IsEventsMILIndicatorActive(EventId) == TRUE)
        {
          Result = FALSE;
        }
#endif
      }
    }
  }

  DBG_DEM_ISDISPLACEOBDEVENTENTRYALLOWED_EXIT(Result, EventId);
  return Result;
}
#endif /* (DEM_OBD_EVENT_DISPLACEMENT == STD_ON) */

/*------------------[internal root-error-queue access-function definitions]------*/

#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U)
FUNC(void, DEM_CODE) Dem_WriteRootErrorQueueEntry(
  Dem_EventIdType RootId)
{
  Dem_RootErrorQueueIdxType RootIdxGroup;
  uint8 RootIdxOffset;
  Dem_MultiEventTriggeringMasterIdxType RootIdx;

  DBG_DEM_WRITEROOTERRORQUEUEENTRY_ENTRY(RootId);

  RootIdxGroup = ((Dem_RootErrorQueueIdxType)Dem_ErrorQueueWriteIdx *
                   DEM_MULTI_EVENT_TRIGGERING_BIT_COUNT) /
                  DEM_MULTI_EVENT_TRIGGERING_COUNT_MAX_WIDTH;
  RootIdxOffset = (Dem_ErrorQueueWriteIdx * DEM_MULTI_EVENT_TRIGGERING_BIT_COUNT) %
                   DEM_MULTI_EVENT_TRIGGERING_COUNT_MAX_WIDTH;
  RootIdx = Dem_GetMultiEventTriggeringMasterIdx(RootId);

#if (DEM_ROOT_ERROR_BUFFER_SIZE > 1U)
  /* if condition is fulfilled the index of the current root overflows
   * in the next byte group */
  if ((DEM_MULTI_EVENT_TRIGGERING_COUNT_MAX_WIDTH - RootIdxOffset) <
       DEM_MULTI_EVENT_TRIGGERING_BIT_COUNT
     )
  {
    Dem_RootErrorQueueEntryWiderType Tmp =
        ((Dem_RootErrorQueueEntryWiderType)Dem_RootErrorQueue[RootIdxGroup + 1U] <<
          DEM_MULTI_EVENT_TRIGGERING_COUNT_MAX_WIDTH) |
          Dem_RootErrorQueue[RootIdxGroup];

    /* clear old value first */
    Tmp &= ~((Dem_RootErrorQueueEntryWiderType)DEM_ROOT_ERROR_ENTRY_MASK << RootIdxOffset);
    /* add new root index value  */
    Tmp |= (Dem_RootErrorQueueEntryWiderType)RootIdx << RootIdxOffset;

    Dem_RootErrorQueue[RootIdxGroup] = (Dem_RootErrorQueueEntryType)Tmp;
    Dem_RootErrorQueue[RootIdxGroup + 1U] =
      (Dem_RootErrorQueueEntryType)(Tmp >> DEM_MULTI_EVENT_TRIGGERING_COUNT_MAX_WIDTH);
  }
  else
#endif /* DEM_ROOT_ERROR_BUFFER_SIZE > 1U */
  {
    /* clear old value first */
    Dem_RootErrorQueue[RootIdxGroup] &= ~(DEM_ROOT_ERROR_ENTRY_MASK << RootIdxOffset);

    /* add new root index value  */
    Dem_RootErrorQueue[RootIdxGroup] |= RootIdx << RootIdxOffset;
  }

  DBG_DEM_WRITEROOTERRORQUEUEENTRY_EXIT(RootId);
}

FUNC(Dem_EventIdType, DEM_CODE) Dem_ReadRootErrorQueueEntry(
  Dem_ErrorQueueElementType QueueEntry)
{
  Dem_EventIdType RetVal;
  Dem_RootErrorQueueIdxType RootIdxGroup;
  uint8 RootIdxOffset;
  Dem_MultiEventTriggeringMasterIdxType RootIdx;

  DBG_DEM_READROOTERRORQUEUEENTRY_ENTRY(QueueEntry);

  RootIdxGroup = ((Dem_RootErrorQueueIdxType)Dem_ErrorQueueReadIdx *
                   DEM_MULTI_EVENT_TRIGGERING_BIT_COUNT) /
                  DEM_MULTI_EVENT_TRIGGERING_COUNT_MAX_WIDTH;
  RootIdxOffset = (Dem_ErrorQueueReadIdx * DEM_MULTI_EVENT_TRIGGERING_BIT_COUNT) %
                   DEM_MULTI_EVENT_TRIGGERING_COUNT_MAX_WIDTH;

#if (DEM_ROOT_ERROR_BUFFER_SIZE > 1U)
  /* if condition is fulfilled the index of the current root overflows
   * in the next byte group */
  if ((DEM_MULTI_EVENT_TRIGGERING_COUNT_MAX_WIDTH - RootIdxOffset) <
       DEM_MULTI_EVENT_TRIGGERING_BIT_COUNT
     )
  {
    const Dem_RootErrorQueueEntryWiderType Tmp =
        ((Dem_RootErrorQueueEntryWiderType)Dem_RootErrorQueue[RootIdxGroup + 1U] <<
          DEM_MULTI_EVENT_TRIGGERING_COUNT_MAX_WIDTH) |
          Dem_RootErrorQueue[RootIdxGroup];
    RootIdx = (Tmp >> RootIdxOffset) & DEM_ROOT_ERROR_ENTRY_MASK;
  }
  else
#endif /* DEM_ROOT_ERROR_BUFFER_SIZE > 1U */
  {
    RootIdx = ((Dem_RootErrorQueue[RootIdxGroup] >> RootIdxOffset) & DEM_ROOT_ERROR_ENTRY_MASK);
  }

  if (RootIdx != DEM_MULTIEVENTTRIGGERINGMASTERIDX_UNUSED)
  {
    /* queued event's master index found, so get it */
    RetVal = Dem_MultiEventTriggeringMasterEventId[RootIdx];
  }
  else
  {
    /* queued event not involved in multi-event triggering */
    RetVal = DEM_ERRORQUEUE_GET_EVID(QueueEntry);
  }

  DBG_DEM_READROOTERRORQUEUEENTRY_EXIT(RetVal, QueueEntry);

  return RetVal;
}
#endif /* DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U */

/*------------------[internal error-queue access-function definitions]------*/

/* !LINKSTO dsn.Dem.ErrorQueue.InvalidateErrorQueueEntry,1 */
FUNC(void, DEM_CODE) Dem_InvalidateErrorQueueEntry(Dem_EventIdType EventId)
{
  Dem_ErrorQueueIdxType ErrorQueueIndex = Dem_ErrorQueueReadIdx;
  boolean ProcessFirstEntryOfFullQueue = FALSE;

  DBG_DEM_INVALIDATEERRORQUEUEENTRY_ENTRY(EventId);

  /* if queue is full */
  if ( (ErrorQueueIndex == Dem_ErrorQueueWriteIdx) &&
       (Dem_ErrorQueue[ErrorQueueIndex] != DEM_EVENT_ID_INVALID) )
  {
    /* mark first entry to be processed since read/write-index are the same */
    ProcessFirstEntryOfFullQueue = TRUE;
  }

  /* loop through all used queue entries (from read- to write-index) */
  while ( (ErrorQueueIndex != Dem_ErrorQueueWriteIdx) ||
          (ProcessFirstEntryOfFullQueue == TRUE) )
  {
    const Dem_EventIdType ErrorQueueEventId =
      DEM_ERRORQUEUE_GET_EVID(DEM_ERRORQUEUE_READ(ErrorQueueIndex));

    /* mark entries with targeted event Id as ignore for later processing */
    if (ErrorQueueEventId == EventId)
    {
      Dem_ErrorQueue[ErrorQueueIndex] =
        (Dem_ErrorQueueEntryType)DEM_ERROR_QUEUE_ENTRY_IGNORE;
    }

#if (DEM_BSW_ERROR_BUFFER_SIZE > 1)
    ++ErrorQueueIndex;
    ErrorQueueIndex %= DEM_BSW_ERROR_BUFFER_SIZE;
#endif

    /* first entry was processed */
    ProcessFirstEntryOfFullQueue = FALSE;
  }

  DBG_DEM_INVALIDATEERRORQUEUEENTRY_EXIT(EventId);
}

/* !LINKSTO dsn.Dem.ErrorQueue.ReadErrorQueueEntry,1 */
FUNC(Dem_ReadErrorQueueReturnType, DEM_CODE) Dem_ReadErrorQueueEntry(
  P2VAR(Dem_ErrorQueueElementType, AUTOMATIC, AUTOMATIC) QueueEntry)
{
  Dem_ReadErrorQueueReturnType RetVal;

  DBG_DEM_READERRORQUEUEENTRY_ENTRY(QueueEntry);

  RetVal.Result = FALSE;

  /* ignore all invalidated entries before the next valid/empty entry */
  while (Dem_ErrorQueue[Dem_ErrorQueueReadIdx] ==
           (Dem_ErrorQueueEntryType)DEM_ERROR_QUEUE_ENTRY_IGNORE)
  {
    /* remove entry from queue */
    Dem_ErrorQueue[Dem_ErrorQueueReadIdx] = DEM_EVENT_ID_INVALID;

#if (DEM_BSW_ERROR_BUFFER_SIZE > 1)
    ++Dem_ErrorQueueReadIdx;
    Dem_ErrorQueueReadIdx %= DEM_BSW_ERROR_BUFFER_SIZE;
#endif
  }

  /* read queue entry */
  if (!DEM_IS_ERROR_QUEUE_EMPTY())
  {
    *QueueEntry = DEM_ERRORQUEUE_READ(Dem_ErrorQueueReadIdx);

    /* remove entry from queue */
    Dem_ErrorQueue[Dem_ErrorQueueReadIdx] = DEM_EVENT_ID_INVALID;

#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U)
    RetVal.RootId = Dem_ReadRootErrorQueueEntry(*QueueEntry);
#endif

#if (DEM_BSW_ERROR_BUFFER_SIZE > 1)
    ++Dem_ErrorQueueReadIdx;
    Dem_ErrorQueueReadIdx %= DEM_BSW_ERROR_BUFFER_SIZE;
#endif

    RetVal.Result = TRUE;
  }

  DBG_DEM_READERRORQUEUEENTRY_EXIT(RetVal, QueueEntry);
  return RetVal;
}

/* !LINKSTO dsn.Dem.ErrorQueue.WriteErrorQueueEntry,1 */
FUNC(boolean, DEM_CODE) Dem_WriteErrorQueueEntry(
  Dem_EventInfoType        EventInfo,
  Dem_EventStatusType      EventStatus,
  Dem_StatusTransitionType TransitionType)
{
  boolean Result = FALSE;
  Dem_EventIdType EventId = EventInfo.EventId;

  DBG_DEM_WRITEERRORQUEUEENTRY_ENTRY(EventInfo, EventStatus, TransitionType);

  if (Dem_ErrorQueue[Dem_ErrorQueueWriteIdx] ==
        (Dem_ErrorQueueEntryType)DEM_EVENT_ID_INVALID)
  {
    Dem_ErrorQueueElementType QueueEntry = (Dem_ErrorQueueElementType)EventId;

    switch (EventStatus)
    {
      case DEM_EVENT_STATUS_FAILED:
        DEM_SET_EVENT_FAILED(QueueEntry);
        break;

#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
      case DEM_EVENT_STATUS_UNCONFIRMED:
        DEM_SET_EVENT_UNCONFIRMED(QueueEntry);
        break;
#endif

#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF)
      case DEM_EVENT_STATUS_CONFIRMED:
        DEM_SET_EVENT_CONFIRMED(QueueEntry);
        break;
#endif

      default:
        /* else: for passed status, no need to clear highest bit, since default
         * value is 0 (because the event range is limited by configuration) */
        break;
    }
    if ((TransitionType & DEM_TRANSITION_EVENT_TFTOC) != 0U)
    {
      DEM_SET_EVENT_FFTOC(QueueEntry);
    }

#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE)
    if ((TransitionType & DEM_TRANSITION_DTC_PDTC_WHILE_CDTC_NOT_SET) != 0U)
    {
      DEM_SET_EVENT_DTC_PDTC_WHILE_CDTC_NOT_SET(QueueEntry);
    }
#endif

#if (DEM_OBDONUDS_FF_SUPPORT == STD_ON)
    if ((TransitionType & DEM_TRANSITION_DTC_TF) != 0U)
    {
      DEM_SET_EVENT_DTC_TF(QueueEntry);
    }
    /* Deviation MISRAC2012-2 */
    if (DEM_GET_OBD_VARIANT() == DEM_OBD_VARIANT_OBDONUDS)
    {
      if ((TransitionType & DEM_TRANSITION_DTC_TFTOC) != 0U)
      {
        DEM_SET_EVENT_DTC_TFTOC(QueueEntry);
      }
    }
#endif

#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U)
    Dem_WriteRootErrorQueueEntry(EventInfo.RootId);
#endif

    DEM_ERRORQUEUE_WRITE(Dem_ErrorQueueWriteIdx, QueueEntry);

#if (DEM_BSW_ERROR_BUFFER_SIZE > 1)
    ++Dem_ErrorQueueWriteIdx;
    Dem_ErrorQueueWriteIdx %= DEM_BSW_ERROR_BUFFER_SIZE;
#endif

    Result = TRUE;
  }

  DBG_DEM_WRITEERRORQUEUEENTRY_EXIT(Result, EventInfo, EventStatus, TransitionType);
  return Result;
}

/* !LINKSTO dsn.Dem.ErrorQueue.CheckErrorQueueEntry,1 */
FUNC(boolean, DEM_CODE) Dem_CheckErrorQueueEntry(
  Dem_EventIdType                                  EventId,
  P2VAR(Dem_EventStatusType, AUTOMATIC, AUTOMATIC) PreviousEntryStatus)
{
  boolean Result = FALSE;

  DBG_DEM_CHECKERRORQUEUEENTRY_ENTRY(EventId, PreviousEntryStatus);

  /* check if error-queue is not empty */
  if (!DEM_IS_ERROR_QUEUE_EMPTY())
  {
    Dem_ErrorQueueElementType QueueEntry;
    uint8 Index = Dem_ErrorQueueWriteIdx;

    /* search error-queue from Dem_ErrorQueueWriteIdx - 1 (most recent entry)
     * decreasing to Dem_ErrorQueueReadIdx (oldest entry) in circular way */
    do
    {
      if (Index == 0U)
      {
        Index = DEM_BSW_ERROR_BUFFER_SIZE - 1U;
      }
      else
      {
        Index--;
      }

      QueueEntry = DEM_ERRORQUEUE_READ(Index);

      if (EventId == DEM_ERRORQUEUE_GET_EVID(QueueEntry))
      {
        *PreviousEntryStatus = DEM_ERRORQUEUE_GET_EVST(QueueEntry);
        Result = TRUE;
      }
    }
    while ((Dem_ErrorQueueReadIdx != Index) && (Result == FALSE));
  }

  DBG_DEM_CHECKERRORQUEUEENTRY_EXIT(Result, EventId, PreviousEntryStatus);
  return Result;
}

/* !LINKSTO dsn.Dem.ErrorQueue.CheckErrorReQueueEntry,1 */
FUNC(void, DEM_CODE) Dem_CheckErrorReQueueEntry(
  Dem_EventInfoType           EventInfo,
  Dem_EventStatusType         EventStatus,
  Dem_EventStatusExtendedType OldDTCStatusMask,
  P2VAR(Std_ReturnType, AUTOMATIC, AUTOMATIC) SetBswEventStatusResult)
{
  /* make entry in error-queue */
  boolean EntryIsWritten;
  Dem_StatusTransitionType TransitionType = 0U;
  const Dem_EventIdType EventId = EventInfo.EventId;

  /* check that this is a transition of 0 -> 1 of TFTOC */
  if ( ( (EventStatus == DEM_EVENT_STATUS_FAILED) ||
         (EventStatus == DEM_EVENT_STATUS_CONFIRMED) ) )
  {
    if(!DEM_IS_ST_BIT_TFTOC_SET(OldDTCStatusMask))
    {
      Dem_ErrorQueueIdxType QueueIdx = Dem_ErrorQueueReadIdx;
#if (DEM_BSW_ERROR_BUFFER_SIZE > 1)
      const Dem_ErrorQueueIdxType EndIdx = Dem_ErrorQueueWriteIdx;
#endif /* DEM_BSW_ERROR_BUFFER_SIZE */

      /* assume this is first failed */
      DEM_SET_TRANSITION_EVENT_TFTOC(TransitionType);

      /* loop over queue, search for entry with same EventId marked
       * as first failed */
#if (DEM_BSW_ERROR_BUFFER_SIZE > 1)
      while (QueueIdx != EndIdx)
#endif /* DEM_BSW_ERROR_BUFFER_SIZE */
      {
        const Dem_ErrorQueueElementType Entry = DEM_ERRORQUEUE_READ(QueueIdx);
        if ( (DEM_ERRORQUEUE_GET_EVID(Entry) == EventId) &&
             (DEM_ERRORQUEUE_GET_FFTOC(Entry) == TRUE) )
        {
          /* set FirstFailed to FALSE */
          DEM_CLEAR_TRANSITION_EVENT_TFTOC(TransitionType);
#if (DEM_BSW_ERROR_BUFFER_SIZE > 1)
          /* if First Failed already set to FALSE break */
          break;
#endif    /* DEM_BSW_ERROR_BUFFER_SIZE */
        }
#if (DEM_BSW_ERROR_BUFFER_SIZE > 1)
        ++QueueIdx;
        QueueIdx %= DEM_BSW_ERROR_BUFFER_SIZE;
#endif /* DEM_BSW_ERROR_BUFFER_SIZE */
      }
    }
  }
  EntryIsWritten = Dem_WriteErrorQueueEntry(EventInfo,
                                            EventStatus,
                                            TransitionType);

  /* check if write was successful */
  if (EntryIsWritten == FALSE)
  {
    /* an error is signaled (caller will trigger DET) */
    *SetBswEventStatusResult = DEM_E_DET_REPORT;
  }
}

/* !LINKSTO dsn.Dem.ErrorQueue.CheckErrorQueueEntryForStatus,1 */
FUNC(boolean, DEM_CODE) Dem_CheckErrorQueueEntryForStatus(
  Dem_EventIdType     EventId,
  Dem_EventStatusType EntryStatus)
{
  boolean Result = FALSE;

  DBG_DEM_CHECKERRORQUEUEENTRYFORSTATUS_ENTRY(EventId, EntryStatus);

  /* check if error-queue is not empty */
  if (!DEM_IS_ERROR_QUEUE_EMPTY())
  {
    Dem_ErrorQueueElementType QueueEntry;
    uint8 Index = Dem_ErrorQueueWriteIdx;

    /* search error-queue from Dem_ErrorQueueWriteIdx - 1 (most recent entry)
     * decreasing to Dem_ErrorQueueReadIdx (oldest entry) in circular way */
    do
    {
      if (Index == 0U)
      {
        Index = DEM_BSW_ERROR_BUFFER_SIZE - 1U;
      }
      else
      {
        Index--;
      }

      QueueEntry = DEM_ERRORQUEUE_READ(Index);

      /* search event with requested status */
      if ((EventId == DEM_ERRORQUEUE_GET_EVID(QueueEntry)) &&
          (EntryStatus == DEM_ERRORQUEUE_GET_EVST(QueueEntry)))
      {
        Result = TRUE;
      }
    }
    while ((Dem_ErrorQueueReadIdx != Index) && (Result == FALSE));
  }

  DBG_DEM_CHECKERRORQUEUEENTRYFORSTATUS_EXIT(Result, EventId, EntryStatus);
  return Result;
}

#if (DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON)
FUNC(boolean, DEM_CODE) Dem_CheckErrQueueEntryForFailedCmbEvents(Dem_EventIdType EventId)
{
  boolean Result = FALSE;

  DBG_DEM_CHECKERRQUEUEENTRYFORFAILEDCMBEVENTS_ENTRY(EventId);

  /* check if error-queue is not empty */
  if (!DEM_IS_ERROR_QUEUE_EMPTY())
  {
    Dem_ErrorQueueElementType QueueEntry;
    uint8 Index = Dem_ErrorQueueWriteIdx;

    /* search error-queue from Dem_ErrorQueueWriteIdx - 1 (most recent entry)
     * decreasing to Dem_ErrorQueueReadIdx (oldest entry) in circular way */
    do
    {
      if (Index == 0U)
      {
        Index = DEM_BSW_ERROR_BUFFER_SIZE - 1U;
      }
      else
      {
        Index--;
      }

      QueueEntry = DEM_ERRORQUEUE_READ(Index);

      /* Check if any of the combined events has an event entry
       * in the error-queue with a failed status */
      if ((DEM_GET_MASTER_EVID(EventId) ==
             DEM_GET_MASTER_EVID(DEM_ERRORQUEUE_GET_EVID(QueueEntry))) &&
          (DEM_EVENT_STATUS_FAILED == DEM_ERRORQUEUE_GET_EVST(QueueEntry)))
      {
        Result = TRUE;
      }
    }
    while ((Dem_ErrorQueueReadIdx != Index) && (Result == FALSE));
  }

  DBG_DEM_CHECKERRQUEUEENTRYFORFAILEDCMBEVENTS_EXIT(Result, EventId);
  return Result;
}
#endif /* DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON */

#if (DEM_OBDONUDS_SUPPORT)
/*----------------[Dem_SetIUMPRDenCondition]---------------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_SetIUMPRDenCondition(
  Dem_IumprDenomCondIdType     ConditionId,
  Dem_IumprDenomCondStatusType ConditionStatus)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_SETIUMPRDENCONDITION_ENTRY(ConditionId, ConditionStatus);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetIUMPRDenCondition, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_SetIUMPRDenCondition, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if ( (ConditionId < DEM_IUMPR_DEN_COND_COLDSTART) ||
            (ConditionId > DEM_IUMPR_GENERAL_OBDCOND) )
  {
    DEM_REPORT_ERROR(DEM_SID_SetIUMPRDenCondition, DEM_E_PARAM_DATA);
  }
  else if (ConditionStatus > DEM_IUMPR_DEN_STATUS_INHIBITED)
  {
    DEM_REPORT_ERROR(DEM_SID_SetIUMPRDenCondition, DEM_E_PARAM_DATA);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /*
     * ENTER critical section to protect DenominatorStatus
     */
    DEM_ENTER_EXCLUSIVE_AREA();

    /* !LINKSTO Dem.OBDonUDS.MAR.InhibitedDenCondition.Duration,1 */
    if ( (ConditionId == DEM_IUMPR_GENERAL_OBDCOND) &&
         (Dem_NvData.DenominatorStatus != DEM_IUMPR_DEN_STATUS_INHIBITED) )
    {
      Dem_NvData.DenominatorStatus = ConditionStatus;
      Result = E_OK;
    }

    /*
     * LEAVE critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();
  }

  DBG_DEM_SETIUMPRDENCONDITION_EXIT(Result, ConditionId, ConditionStatus);
  return Result;
}

/*----------------[Dem_GetIUMPRDenCondition]--------------------------------*/

/* !LINKSTO Dem.ASR21-11.SWS_Dem_00734,1 */
/* !LINKSTO Dem.SWS_Dem_00966,1 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetIUMPRDenCondition(
  Dem_IumprDenomCondIdType                                      ConditionId,
  P2VAR(Dem_IumprDenomCondStatusType, AUTOMATIC, DEM_APPL_DATA) ConditionStatus)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_GETIUMPRDENCONDITION_ENTRY(ConditionId, ConditionStatus);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_GetIUMPRDenCondition, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_GetIUMPRDenCondition, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if ( (ConditionId < DEM_IUMPR_DEN_COND_COLDSTART) ||
            (ConditionId > DEM_IUMPR_GENERAL_OBDCOND) )
  {
    DEM_REPORT_ERROR(DEM_SID_GetIUMPRDenCondition, DEM_E_PARAM_DATA);
  }
  else if (ConditionStatus == NULL_PTR)
  {
    DEM_REPORT_ERROR(DEM_SID_GetIUMPRDenCondition, DEM_E_PARAM_POINTER);
  }
  else
#endif /* (DEM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* !LINKSTO Dem.SWS_Dem_00716,1 */
    if (ConditionId == DEM_IUMPR_GENERAL_OBDCOND)
    {
      *ConditionStatus = Dem_NvData.DenominatorStatus;
      Result = E_OK;
    }
  }

  DBG_DEM_GETIUMPRDENCONDITION_EXIT(Result, ConditionId, ConditionStatus);
  return Result;
}
#endif /* (DEM_OBDONUDS_SUPPORT) */

#if (DEM_RESET_PERFORMANCE_COUNTERS_ENABLED == STD_ON)
/*----------------[Dem_ResetPerformanceCounters]-----------------------------*/

FUNC(Std_ReturnType, DEM_CODE) Dem_ResetPerformanceCounters(
  Dem_PerformanceCountersKindType CountersKind)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_RESETPERFORMANCECOUNTERS_ENTRY(CountersKind);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState != DEM_INITIALIZED)
  {
    DEM_REPORT_ERROR(DEM_SID_ResetPerformanceCounters, DEM_E_UNINIT);
  }
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_SID_ResetPerformanceCounters, DEM_E_WRONG_CONTEXT);
  }
#endif
  else if (CountersKind > DEM_COUNTERS_KIND_MAR_AND_IUMPR)
  {
    DEM_REPORT_ERROR(DEM_SID_ResetPerformanceCounters, DEM_E_PARAM_DATA);
  }
  else
#endif
  {
    if (CountersKind == DEM_COUNTERS_KIND_MAR)
    {
#if (DEM_MAR_SUPPORT == STD_ON)
      /*
       * ENTER critical section
       */
      DEM_ENTER_EXCLUSIVE_AREA();

      /* !LINKSTO Dem.OBD.ResetPerformanceCounters.MARDenominator,1 */
      /* reset the mini-denominator */
      Dem_NvData.MARData.Denominator = 0U;

      /* !LINKSTO Dem.OBD.ResetPerformanceCounters.MARNumeratorAndRatio,1 */
      /* reset the mini-numerators and stored Monitor Activity Ratio of all
       * relevant events/DTCs */
      TS_MemSet(&Dem_NvData.MARData.Numerator[0], 0x00U, DEM_NUM_MAR_EVENTS);
      TS_MemSet(&Dem_NvData.MARData.Ratio[0], 0x00U, DEM_NUM_MAR_DTCS);

      /*
       * LEAVE critical section
       */
      DEM_EXIT_EXCLUSIVE_AREA();

      Result = E_OK;
#endif
    }
    else
    {
      /* !LINKSTO Dem.OBD.ResetPerformanceCounters.UnsupportedCounters,1 */
      /* do nothing as the counters requested for reset are not supported */
      /* E_NOT_OK will be returned */
    }
  }

  DBG_DEM_RESETPERFORMANCECOUNTERS_EXIT(Result, CountersKind);

  return Result;
}
#endif /* (DEM_RESET_PERFORMANCE_COUNTERS_ENABLED == STD_ON) */

/*------------------[further sub-functions]---------------------------------*/

#if (DEM_NUM_FFSEGS > 0U)
STATIC FUNC(Dem_FFSegIdxType, DEM_CODE) Dem_FindFFSegIdx(
  Dem_FFKindType                                 FFKind,
  P2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) IndividPartFFClass,
  uint16                                         DataId,
  P2VAR(Dem_SizeFFType, AUTOMATIC, AUTOMATIC)    Offset)
{
  Dem_SizeFFType StartByte = 0U;
  Dem_FFSegIdxType FFSegIdx = 0U;
  boolean IsDidFound = FALSE;
  uint8_least FFPartIdx;

  P2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFPartClass[DEM_NUM_FFPARTS];
#if (DEM_COMMON_FREEZEFRAMES_USED == STD_ON)
  FFPartClass[0] = &Dem_FFClass[Dem_CommonPartFFClassIdx[FFKind]];
#endif
  FFPartClass[DEM_NUM_FFPARTS - 1U] = IndividPartFFClass;

  DBG_DEM_FINDFFSEGIDX_ENTRY(FFKind, IndividPartFFClass, DataId, Offset);

#if (DEM_COMMON_FREEZEFRAMES_USED == STD_OFF)
  TS_PARAM_UNUSED(FFKind);
#endif

  /* Deviation TASKING-1 */
  for (FFPartIdx = 0U; FFPartIdx < DEM_NUM_FFPARTS; FFPartIdx++)
  {
    Dem_NumFFSegsType SegIdx;

    for (SegIdx = 0U; SegIdx < FFPartClass[FFPartIdx]->NumFFSegs; ++SegIdx)
    {
      FFSegIdx = FFPartClass[FFPartIdx]->FFSegIdx[SegIdx];

      if (FFSegIdx != DEM_FFSEG_IDX_UNUSED)
      {
        if (Dem_FFSegment[FFSegIdx].DataId == DataId)
        {
          IsDidFound = TRUE;
          break;
        }
        else
        {
          StartByte += Dem_SizeOfFFSegment(&Dem_FFSegment[FFSegIdx]);
        }
      }
    }

    if (IsDidFound == TRUE)
    {
      /* ending 'FFPartIdx' loop if 'FFSegIdx' is found */
      break;
    }
  }

  if (IsDidFound == FALSE)
  {
    /* to indicate that match is not found */
    FFSegIdx = DEM_FFSEG_IDX_UNUSED;
  }
  else
  {
    /* return FF segments offset */
    *Offset = StartByte;
  }

  DBG_DEM_FINDFFSEGIDX_EXIT(FFSegIdx, FFKind, IndividPartFFClass, DataId, Offset);
  return FFSegIdx;
}
#endif /* (DEM_NUM_FFSEGS > 0U) */

#if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
STATIC FUNC_P2VAR(Dem_EntryDataType, DEM_VAR_CLEARED, DEM_CODE)
  Dem_GetPFFEntryDataPtr(Dem_EventIdType EventId)
{
  Dem_EntryDataPtrType Result;
  Dem_SizeEntryDataType StartPos = 0U;

  Dem_EventIdType EvId;

  DBG_DEM_GETPFFENTRYDATAPTR_ENTRY(EventId);

  /* check if there are PFFs in front of the target PFF */
  for (EvId = 0U; EvId < EventId; ++EvId)
  {
    if (Dem_GbiEnablePrestorage(EvId) == TRUE)
    {
      /* get freeze frame class layout */
      CONSTP2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFClass =
        &Dem_FFClass[Dem_GbiFFClassIdx(EvId)];

      /* update start position of PFF */
      StartPos += Dem_SizeOfFF(DEM_REGULAR_FF, FFClass);
    }
  }

  Result = &Dem_PFFEntryData[StartPos];

  DBG_DEM_GETPFFENTRYDATAPTR_EXIT(Result, EventId);
  return Result;
}
#endif /* DEM_MAX_NUMBER_PRESTORED_FF > 0U */

#if ( (DEM_USE_AGING == STD_ON) && \
      (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD) )
STATIC FUNC(boolean, DEM_CODE) Dem_UpdateAgingCounter(Dem_EventIdType EventId)
{
  boolean SearchResult;
  Dem_EventMemoryEntryPtrType EvMemEntry;
  Dem_SizeEvMemEntryType EvMemEntryIdx;
  Dem_EventIdType CurrentEvent = EventId;
  boolean ClearAgedEventFlag = FALSE;

#if (DEM_NUM_CMB_DTCS > 0U)
  Dem_DTCStatusMaskType OldDTCStatusMask = DEM_DTC_STATUS_MASKS[CurrentEvent];
  Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(CurrentEvent);
#endif

  DBG_DEM_UPDATEAGINGCOUNTER_ENTRY(EventId);

  /*
   * ENTER critical section to protect the event status and memory
   *       call-context: Rte (Task)
   */
  DEM_ENTER_EXCLUSIVE_AREA();
  SearchResult = Dem_SearchForEntry(EventId, &EvMemEntry, &EvMemEntryIdx);
  /* !LINKSTO Dem.SWS_Dem_01185,1 */
  if (SearchResult == TRUE)
  {
    /* pointer to internal aging value */
    const Dem_EntryDataPtrType AgingCounterPtr =
      Dem_IntValEntryData(EvMemEntry);

#if (DEM_NUM_CMB_DTCS > 0U)
    CurrentEvent = EvMemEntry->EventId;
    OldDTCStatusMask = DEM_DTC_STATUS_MASKS[CurrentEvent];
#endif

    /* decrease aging counter if it has not reached zero
     * (while DTCRecordUpdate was disabled) */
    if (*AgingCounterPtr > 0U)
    {
      (*AgingCounterPtr) -= 1U;
    }

    /* !LINKSTO Dem.SWS_Dem_01075,1 */
    /* !LINKSTO Dem.SWS_Dem_00270,1 */
    /* age the event if counter reaches zero */
    if ( (!DEM_RECORD_UPDATE_LOCKED(CurrentEvent)) &&
         (*AgingCounterPtr == 0U) )
    {
      Dem_ClearAgedEventEntry(CurrentEvent, EvMemEntry);

#if ( (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON) || \
      ( (DEM_NUM_CMB_DTCS > 0U) && \
        ( (DEM_STATUS_BIT_HANDLING_TESTFAILEDSINCELASTCLEAR == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT) || \
          (DEM_RESET_PENDING_BIT_ON_OVERFLOW_SUPPORT == STD_ON) || \
          (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON) ) ) )
      ClearAgedEventFlag = TRUE;
#endif
    }

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    if ( (ClearAgedEventFlag == TRUE) || (*AgingCounterPtr != 0U) )
    {
      /* event memory entry has been updated or event is aged:
       * it needs to be stored immediately if the immediate storage
       * is enabled for the updated or cleared event */
      Dem_CheckForImmediateEntryStorage(CurrentEvent,
                                        EvMemEntry,
                                        EvMemEntryIdx,
                                        DEM_NVM_NO_FORCE);
    }
#endif
  }

  /*
   * LEAVE critical section
   */
  DEM_EXIT_EXCLUSIVE_AREA();

#if (DEM_NUM_CMB_DTCS > 0U)
  if (DEM_IS_DTC_COMBINED(DTCConfIdx))
  {
#if ( (DEM_STATUS_BIT_HANDLING_TESTFAILEDSINCELASTCLEAR == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT) || \
      (DEM_RESET_PENDING_BIT_ON_OVERFLOW_SUPPORT == STD_ON) || \
      (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON) )
    if (ClearAgedEventFlag == TRUE)
    {
      /* Cmb DTC was aged. Reset status of involved events.
       * since further events may be affected, the CmbDTC update is handled via flags below */
      Dem_ResetStatusForCmbEvents(CurrentEvent, FALSE);
    }
#endif
    if (OldDTCStatusMask != DEM_DTC_STATUS_MASKS[CurrentEvent])
    {
#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
      /* trigger here status notification for combined non-master events */
      /* for master and non-combine events it is done after the call
       * of UpdateAgingCounter */
      if (DEM_GET_MASTER_EVID(CurrentEvent) != CurrentEvent)
      {
        Dem_CbTriggerOnEventStatus(
          CurrentEvent, OldDTCStatusMask, DEM_DTC_STATUS_MASKS[CurrentEvent]);
      }
#endif

      /* set a flag corresponding to this EventId to update the cmb status */
      DEM_ATOMIC_SET_BIT_IN_ARRAY_8(Dem_CmbDTCFlags, DTCConfIdx);
    }
  }
#endif /* DEM_NUM_CMB_DTCS > 0U */

#if (DEM_CB_TRIG_ON_EVDAT_ASR403 == STD_ON)
#if ( (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON) && \
      (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON) )
  if (SearchResult == TRUE)
  {
    /* test whether the elements DEM_AGINGCTR, DEM_AGINGCTR_UPCNT or DEM_AGINGCTR_DOWNCNT
     * are mapped for CurrentEvent */
    if ( Dem_CheckIntDataElementUsage(
           CurrentEvent, DEM_INT_VAL_IDX_AGECTRUP, DEM_INT_VAL_IDX_AGECTRDWN) == TRUE )
    {
      /* notify application that event data has changed */
      Dem_CbTriggerOnEventData(CurrentEvent);
    }
  }
#endif
#endif /* (DEM_CB_TRIG_ON_EVDAT_ASR403 == STD_ON) */

  DBG_DEM_UPDATEAGINGCOUNTER_EXIT(ClearAgedEventFlag, EventId);
  return ClearAgedEventFlag;
}
#endif /* (DEM_USE_AGING == STD_ON) &&
          (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD) */

#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_SINGLE)
FUNC(void, DEM_CODE) Dem_ProcessSingleOBDFreezeFrame(
  Dem_EventIdType                  EventId,
  Dem_EntryDataPtrType             CaptureBuffer)
{
  boolean StoredOBDFFEventIdWasUpdated = FALSE;
  Dem_SizeEntryDataType CalcFFSize = 0U;
  Std_ReturnType ProcessCaptureResult = E_OK;
  Dem_EventIdType StoredOBDFFEventId;

  DBG_DEM_PROCESSSINGLEOBDFREEZEFRAME_ENTRY(EventId, CaptureBuffer);
  /*
   * ENTER critical section
   */
  DEM_ENTER_EXCLUSIVE_AREA();

  StoredOBDFFEventId = DEM_OBDFF_STORED_EVENT_ID;
  /*
   * LEAVE critical section
   */
  DEM_EXIT_EXCLUSIVE_AREA();

  /* check whether any OBD FF stored */
  if (StoredOBDFFEventId != DEM_EVENT_ID_INVALID)
  {
    /* check whether reported event is the same as currently stored, if so,
     * the OBD FF is not updated */
    /* !LINKSTO dsn.Dem.OBD.Dem_ProcessSingleOBDFreezeFrame.updateOBDFreezeFrame,2 */
    if (StoredOBDFFEventId != EventId)
    {
      /* get event priority */
      uint8 EventPrioOfStoredEvent =
        Dem_GbiPriority(StoredOBDFFEventId);
      uint8 EventPrioOfNewEvent = Dem_GbiPriority(EventId);

      /* !LINKSTO VCC_DEM_006_Req130v1,1 */
      /* !LINKSTO Dem.OBD.SingleOBDFreezeFrame.StoreOBDFF,1 */
      /* check for displacement, stored OBD freeze frame event
       * can only be displaced by event with higher prio */
      if (EventPrioOfNewEvent < EventPrioOfStoredEvent)
      {
        /* displace OBD freeze frame */
        /* !LINKSTO dsn.Dem.OBD.Dem_ProcessSingleOBDFreezeFrame.displaceOBDFreezeFrame,1 */
        /* !LINKSTO dsn.Dem.ExternalDataCapturing.CaptureSingleOBDFF,1 */
        StoredOBDFFEventIdWasUpdated = TRUE;
        ProcessCaptureResult = Dem_CaptureOBDFreezeFrame(EventId, CaptureBuffer, &CalcFFSize);
      }
    }
  }
  else /* SingleOBDEventMemoryEntry is empty */
  {
    /* store EventId and write OBD freeze frame */
    /* !LINKSTO dsn.Dem.ExternalDataCapturing.CaptureSingleOBDFF,1 */
    /* !LINKSTO VCC_DEM_006_Req130v1,1 */
    StoredOBDFFEventIdWasUpdated = TRUE;
    ProcessCaptureResult = Dem_CaptureOBDFreezeFrame(EventId, CaptureBuffer, &CalcFFSize);
  }

#if (DEM_DET_RUNTIME_CHECK == STD_ON)
  if (ProcessCaptureResult == DEM_E_NODATAAVAILABLE)
  {
    /* !LINKSTO dsn.Dem.OBD.Dem_CaptureOBDFreezeFrame.ReadDataElementResult,1 */
    /* report non-available data for OBD FF;
     * the calling context may be Dem_MainFunction or
     * Dem_SetEventStatus if DEM_FREEZE_FRAME_CAPTURE is set to DEM_TRIGGER_TESTFAILED */
    DEM_REPORT_RUNTIME_ERROR(DEM_INTERNAL_API_ID, DEM_E_NODATAAVAILABLE);
  }
#endif

  if (StoredOBDFFEventIdWasUpdated == TRUE)
  {
    /*
     * ENTER critical section
     */
    DEM_ENTER_EXCLUSIVE_AREA();

    /* !LINKSTO dsn.Dem.OBD.Dem_CaptureOBDFreezeFrame.RetrieveDataElement,1 */
    /* !LINKSTO Dem.OBD.SingleOBDFreezeFrame.ProcessStoreOBDFF,1 */
    /* !LINKSTO dsn.Dem.OBD.Dem_ProcessSingleOBDFreezeFrame.storeOBDFreezeFrame,1 */
    DEM_OBDFF_STORED_EVENT_ID = EventId;

    TS_MemCpy(DEM_OBDFF_STORED_DATA,
          CaptureBuffer,
          CalcFFSize);
    /*
     * LEAVE critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();
  }

  DBG_DEM_PROCESSSINGLEOBDFREEZEFRAME_EXIT(EventId, CaptureBuffer);
}

#elif (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE)

STATIC FUNC(void, DEM_CODE) Dem_ProcessMultipleOBDFreezeFrameEntry(
  Dem_EntryDataPtrType                        CapturedDataBuf,
  Dem_EventIdType                             EventId,
  Dem_SizeEvMemEntryType                      EventMemoryEntryIdx,
  Dem_EventEntryAllocResultType               EventEntryAllocResult,
  Dem_StatusTransitionType                    TransitionType,
  Dem_EventNotificationDataPtrType            Notification,
  Dem_ExternalEntryDataBufferManagementType   EventRelatedDataSize)
{
#if (DEM_NUM_OF_PIDS_IN_OBDFF > 0U)
  boolean ReorderingWasPerformed = FALSE;
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
  const Dem_EventMemoryEntryPtrType PrimMemEntry =
    Dem_EventMem[(DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U)];
#endif
#endif

  DBG_DEM_PROCESSMULTIPLEOBDFREEZEFRAMEENTRY_ENTRY(
    CapturedDataBuf, EventId, EventMemoryEntryIdx, EventEntryAllocResult,
    TransitionType, Notification, EventRelatedDataSize);

  if(EventRelatedDataSize.OBDFFSize > 0U)
  {
    /* processes OBD relevant events according to the OBD freeze frame */
#if (DEM_OBDONUDS_FF_SUPPORT == STD_ON)

    /* Deviation MISRAC2012-2 */
    if (DEM_GET_OBD_VARIANT() == DEM_OBD_VARIANT_OBDONUDS)
    {
      if( (EventEntryAllocResult == DEM_EVENTENTRYALLOC_ALLOCATED) ||
          (EventEntryAllocResult == DEM_EVENTENTRYALLOC_REPLACED) ||
          ( (EventEntryAllocResult == DEM_EVENTENTRYALLOC_EXISTS) &&
            ((TransitionType & DEM_TRANSITION_DTC_PDTC_WHILE_CDTC_NOT_SET ) != 0U) ) )
      {
        /* New entry was created in memory, either regular or postponed
         * (e.g. because of a TF transition without PDTC transition, which
         * could happen, if no free entry could be allocated at a previous
         * PDTC transition) or an old entry existed already, but a new PDTC
         * transition occurred. Therefore perform the storage of both first and
         * last occurrences records numbers of OBDonUDS FF */
        /* !LINKSTO Dem.OBDonUDS.OBDFF.StoreFirstOccurrenceOnEntryCreation,1 */
        /* !LINKSTO Dem.OBDonUDS.OBDFF.StoreFirstOccurrenceOnPDTCTransition,1 */
        TS_MemCpy(DEM_OBDFF_ENTRY_FFDATA_LINK(EventMemoryEntryIdx),
                  CapturedDataBuf,
                  DEM_SIZE_OBDONUDS_OBD_FF);

        /* also copy OBDonUDS FF Data to Data2 */
        /* !LINKSTO Dem.OBDonUDS.OBDFF.StoreLastOccurrence,1 */
        /* !LINKSTO dsn.Dem.OBDonUDS.OBDFF.FirstStorageOfLastOccurrence,1 */
        TS_MemCpy(DEM_OBDFF_ENTRY_FFDATA_2_LINK(EventMemoryEntryIdx),
                  DEM_OBDFF_ENTRY_FFDATA_LINK(EventMemoryEntryIdx),
                  DEM_SIZE_OBDONUDS_OBD_FF);
#if (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON)
        Notification->TriggerOnEventData = EventId;
#endif
      }

      if ( (EventEntryAllocResult == DEM_EVENTENTRYALLOC_EXISTS) &&
           ((TransitionType & DEM_TRANSITION_DTC_PDTC_WHILE_CDTC_NOT_SET ) == 0U) )
      {
        /* !LINKSTO Dem.OBDonUDS.OBDFF.UpdateLastOccurrenceOnTestFailed,1 */
        /* i.e. exclude below condition when DEM_OBDONUDS_FF_UPDATE_TRIGGER is configured
         * to the value DEM_TRIGGER_ON_TFTOC_TF
         */
#if (DEM_OBDONUDS_FF_UPDATE_TRIGGER == DEM_TRIGGER_ON_TFTOC)
        /* check if triggering criteria of last FF record update is
         * DTC TFTOC 0 -> 1 transition */
        if ( (TransitionType & DEM_TRANSITION_DTC_TFTOC) != 0U )
#endif
        {
          /* Perform only an update for the existing last OBDonUDS FF entry */
          /* !LINKSTO Dem.OBDonUDS.OBDFF.UpdateLastOccurrence,1 */
          TS_MemCpy(DEM_OBDFF_ENTRY_FFDATA_2_LINK(EventMemoryEntryIdx),
                    CapturedDataBuf,
                    DEM_SIZE_OBDONUDS_OBD_FF);
#if (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON)
          Notification->TriggerOnEventData = EventId;
#endif
        }
      }
    }
    /* Deviation MISRAC2012-2 */
    else
#endif /* (DEM_OBDONUDS_FF_SUPPORT == STD_ON) */
    {
      /* intentionally empty, if only OBDonUDS is enabled */
#if (DEM_NUM_OF_PIDS_IN_OBDFF > 0U)
      if( (EventEntryAllocResult == DEM_EVENTENTRYALLOC_ALLOCATED) ||
          (EventEntryAllocResult == DEM_EVENTENTRYALLOC_REPLACED) ||
          ( (EventEntryAllocResult == DEM_EVENTENTRYALLOC_EXISTS) &&
            ((TransitionType & DEM_TRANSITION_DTC_PDTC_WHILE_CDTC_NOT_SET ) != 0U) ) )
      {
        /* !LINKSTO Dem.OBD.MultipleOBDFreezeFrame.OBDFFUpdate,1 */
        /* !LINKSTO Dem.OBD.MultipleOBDFreezeFrame.ProcessStoreOBDFF,1 */
        /* !LINKSTO Dem.OBD.MultipleOBDFreezeFrame.StoreOBDFF,1 */
        /* !LINKSTO Dem.OBD.MultipleOBDFreezeFrame.StoreOBDFFOnPDTCTransition,1 */
        TS_MemCpy(DEM_OBDFF_ENTRY_FFDATA_LINK(EventMemoryEntryIdx),
                  CapturedDataBuf,
                  DEM_SIZE_OBDFF_DATA);
        /* set the OBD freeze frame occurrence order */
        ReorderingWasPerformed = Dem_SetOBDFFOccurrenceOrder(EventMemoryEntryIdx);
        if (ReorderingWasPerformed == TRUE)
        {
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
          Dem_CheckForImmediateEntryStorage(EventId, PrimMemEntry,
                                    EventMemoryEntryIdx, DEM_NVM_NO_FORCE);
#endif
        }
      }
#endif /* (DEM_NUM_OF_PIDS_IN_OBDFF > 0U) */
    }
#if ( (DEM_OBDONUDS_FF_SUPPORT == STD_OFF) || \
      (DEM_OBDONUDS_FF_UPDATE_TRIGGER != DEM_TRIGGER_ON_TFTOC) )
    TS_PARAM_UNUSED(TransitionType);
#endif
#if ( (DEM_OBDONUDS_FF_SUPPORT == STD_OFF) || \
      (DEM_USE_CB_TRIG_ON_EVDAT == STD_OFF) )
    TS_PARAM_UNUSED(Notification);
#endif
#if ( (DEM_USE_CB_TRIG_ON_EVDAT == STD_OFF) || \
      (DEM_USE_IMMEDIATE_NV_STORAGE == STD_OFF) )
    TS_PARAM_UNUSED(EventId);
#endif
  }
  DBG_DEM_PROCESSMULTIPLEOBDFREEZEFRAMEENTRY_EXIT(
    CapturedDataBuf, EventId, EventMemoryEntryIdx, EventEntryAllocResult,
    TransitionType, Notification, EventRelatedDataSize);
}

#if (DEM_NUM_OF_PIDS_IN_OBDFF > 0U)
FUNC(boolean, DEM_CODE) Dem_SelectEntryOfOBDFreezeFrameEvent(
  P2VAR(Dem_SizeEvMemEntryType, AUTOMATIC, DEM_APPL_DATA) SelectedEntryIndex,
  boolean                                                 SelectForReport)
{
  Dem_EventIdType SelectedEvId = DEM_EVENT_ID_INVALID;
  Dem_SizeEvMemEntryType TemporaryEntryIdx = 0U;
  uint8 EntryIdx;
  boolean IdentifiedOBDEventForReport = FALSE;

  DBG_DEM_SELECTENTRYOFOBDFREEZEFRAMEEVENT_ENTRY(SelectedEntryIndex, SelectForReport);

  /* loop through primary event memory */
  for (EntryIdx = 0U; EntryIdx < DEM_MAX_NUMBER_EVENT_ENTRY_PRI; EntryIdx++)
  {
    Dem_EventIdType CurrentEvId =
      Dem_EventMem[(DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U)][EntryIdx].EventId;
    uint32 VisibleDTC = Dem_GetVisibleCmbDTC(DEM_DTC_FORMAT_OBD, CurrentEvId);
#if(DEM_OBD_Support == STD_ON)
    uint32 ObdDTC = Dem_GetObdDTC(CurrentEvId);
#else
    uint32 ObdDTC = DEM_NO_DTC;
#endif
    Dem_DTCKindType DtcKind = Dem_GbiDTCKind(CurrentEvId);

    /* !LINKSTO Dem.OBD.MultipleOBDFreezeFrame.SelectOBDFF.ConfirmationBased,1 */
    /* check only for relevant event entries, the event is not important in case:
     * is not an OBD event
     * has the OBD DTC disabled (e.g. calibration or DTC suppression)
     * has the CDTC bit reset */
    if ( (DtcKind == DEM_DTC_KIND_EMISSION_REL_DTCS) &&
       ( ( (SelectForReport == TRUE)  && (VisibleDTC != DEM_NO_DTC) ) ||
         ( (SelectForReport == FALSE) && (ObdDTC != DEM_NO_DTC) ) )   &&
         DEM_IS_EV_ST_BIT_CDTC_SET(CurrentEvId) )
    {
      /* check if an event entry was already selected */
      if (IdentifiedOBDEventForReport == TRUE)
      {
        uint8 CurrentEventPrio  = Dem_GbiPriority(CurrentEvId);
        uint8 SelectedEventPrio = Dem_GbiPriority(SelectedEvId);
        Dem_OccOrderType CurrentOccOrder  =
          DEM_OBDFF_ENTRY_OCCURRENCE(EntryIdx);
        Dem_OccOrderType SelectedOccOrder =
          DEM_OBDFF_ENTRY_OCCURRENCE(TemporaryEntryIdx);

        /* !LINKSTO Dem.OBD.MultipleOBDFreezeFrame.SelectOBDFF.PriorityBased,1 */
        /* !LINKSTO Dem.OBD.MultipleOBDFreezeFrame.SelectOBDFF.OccurrenceBased,1 */
        /* check if the selected event entry needs to be updated */
        if ( (CurrentEventPrio < SelectedEventPrio)  ||
           ( (CurrentEventPrio == SelectedEventPrio) &&
             (CurrentOccOrder < SelectedOccOrder) ) )
        {
          SelectedEvId =
            Dem_EventMem[(DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U)][EntryIdx].EventId;
          TemporaryEntryIdx = EntryIdx;
        }
      }
      /* select first relevant event entry */
      else
      {
        SelectedEvId =
          Dem_EventMem[(DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U)][EntryIdx].EventId;
        TemporaryEntryIdx = EntryIdx;
        IdentifiedOBDEventForReport = TRUE;
      }
    }
  }

  if (IdentifiedOBDEventForReport == TRUE)
  {
    *SelectedEntryIndex = TemporaryEntryIdx;
  }

  DBG_DEM_SELECTENTRYOFOBDFREEZEFRAMEEVENT_EXIT(IdentifiedOBDEventForReport, SelectForReport, SelectedEntryIndex);
  return IdentifiedOBDEventForReport;
}

STATIC FUNC(boolean, DEM_CODE) Dem_SetOBDFFOccurrenceOrder(
  Dem_SizeEvMemEntryType EventMemoryEntryIdx)
{
  boolean OccurrenceOrderUpdated = FALSE;

  DBG_DEM_SETOBDFFOCCURRENCEORDER_ENTRY(EventMemoryEntryIdx);

  /* set the occurrence order for event memory entry */
  DEM_OBDFF_ENTRY_OCCURRENCE(EventMemoryEntryIdx) = Dem_MaxOBDOccOrder;

  /* if maximum value of occurrence order is reached
   * the occ order must be rearranged */
  if (Dem_MaxOBDOccOrder == DEM_MAX_OCC_ORDER)
  {
    Dem_RearrangeOBDOccurrenceOrder();
    OccurrenceOrderUpdated = TRUE;
  }

  Dem_MaxOBDOccOrder++;

  DBG_DEM_SETOBDFFOCCURRENCEORDER_EXIT(EventMemoryEntryIdx, OccurrenceOrderUpdated);
  return OccurrenceOrderUpdated;
}
#endif
#endif /* (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE) */

#if (DEM_MAX_NUM_EVENT_ENTRY_CAPTURE_BUFFER > 0U)
STATIC FUNC(boolean, DEM_CODE) Dem_EventMemoryCaptureBufferGet(
  P2VAR(Dem_CaptureBufferCountType, AUTOMATIC, AUTOMATIC) BufferIdx,
  P2VAR(Dem_EntryDataPtrType, AUTOMATIC, AUTOMATIC) BufferStart)
{
  boolean Result = FALSE;
  uint8 Idx;

  DBG_DEM_EVENTMEMORYCAPTUREBUFFERGET_ENTRY(BufferIdx, BufferStart);

  /*
   * ENTER critical section to protect access to BufferInUse
   *       call-context: Dem_SetEventStatus()
   */
  DEM_ENTER_EXCLUSIVE_AREA();

  for(Idx = 0; Idx < DEM_MAX_NUM_EVENT_ENTRY_CAPTURE_BUFFER; Idx++)
  {
     if (Dem_ExternalEntryDataBufferPool[Idx].BufferInUse == FALSE)
     {
       *BufferIdx = Idx;
       *BufferStart = &Dem_ExternalEntryDataBufferPool[Idx].DataBuffer[0];
       Dem_ExternalEntryDataBufferPool[Idx].BufferInUse = TRUE;
       Result = TRUE;
       break;
     }
  }

  /*
   * LEAVE critical section
   */
  DEM_EXIT_EXCLUSIVE_AREA();

  DBG_DEM_EVENTMEMORYCAPTUREBUFFERGET_EXIT(Result, BufferIdx, BufferStart);

  return Result;
}
#endif

STATIC FUNC(boolean, DEM_CODE) Dem_AllocateCaptureBuffer(
  uint8 ServiceId,
  P2VAR(Dem_CaptureBufferCountType, AUTOMATIC, AUTOMATIC) BufferIdx,
  P2VAR(Dem_EntryDataPtrType, AUTOMATIC, AUTOMATIC) BufferStart)
{
  boolean Result = FALSE;
  *BufferIdx = DEM_MAX_NUM_EVENT_ENTRY_CAPTURE_BUFFER;

  /* !LINKSTO dsn.Dem.ExternalDataCapturing.AsyncBuffer,1 */
  if (ServiceId == DEM_SID_MainFunction)
  {
    Result = TRUE;
#if (DEM_SIZE_EXTERNAL_ENTRY_DATA > 0U)
    /* use exclusive buffer for main function, which is always available,
     * when external data is configured. */
    *BufferStart = (P2VAR(Dem_EntryDataType, AUTOMATIC, AUTOMATIC))&Dem_ExternalEntryDataBuffer[0];
#else
    TS_PARAM_UNUSED(BufferStart);
#endif
  }

#if (DEM_MAX_NUM_EVENT_ENTRY_CAPTURE_BUFFER > 0U)
  if (ServiceId == DEM_SID_SetEventStatus)
  {
    /* !LINKSTO dsn.Dem.ExternalDataCapturing.SyncBufferPool,1 */
    /* try to allocate a buffer from the pool - this is only
       required for TRIGGER_ON_TESTFAILED */

    if (TRUE == Dem_EventMemoryCaptureBufferGet(BufferIdx, BufferStart))
    {
      Result = TRUE;
    }
    /* !LINKSTO dsn.Dem.ExternalDataCapturing.NoBufferAvailable.ErrorReporting,1 */
#if (DEM_DET_RUNTIME_CHECK == STD_ON)
    else
    {
      /* report heap buffer is not available */
      DEM_REPORT_RUNTIME_ERROR(ServiceId, DEM_E_NO_CAPTURE_BUFFER_AVAILABLE);
    }
#endif
  }
#else
    TS_PARAM_UNUSED(BufferIdx);
#endif

  return Result;
}

#if (DEM_MAX_NUM_EVENT_ENTRY_CAPTURE_BUFFER > 0U)
STATIC FUNC(void, DEM_CODE) Dem_EventMemoryCaptureBufferRelease(
  Dem_CaptureBufferCountType BufferIdx)
{
  if(BufferIdx < DEM_MAX_NUM_EVENT_ENTRY_CAPTURE_BUFFER)
  {
    Dem_ExternalEntryDataBufferPool[BufferIdx].BufferInUse = FALSE;
  }
}
#endif

STATIC FUNC(void, DEM_CODE) Dem_ProcessEventPreCapture(
  uint8 ServiceId,
  Dem_EventIdType EventId,
  Dem_EventStatusType EventStatus,
  Dem_EntryDataPtrType BufferStart,
  Dem_ExternalEntryDataBufferManagementType *EventRelatedDataSize,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC) ReportEDUpdate)
{
  boolean EntryExists;
#if ( ((DEM_NUM_EDSEGS > 0U) && (DEM_NUM_EXT_DATAELEMENTS > 0U)) || \
      ((DEM_NUM_FFCLS > 0U) && (DEM_NUM_FFSEGS > 0U)) || \
      (DEM_DEV_FREEZE_FRAME_USED == STD_ON) || \
      ((DEM_NUM_J1939FFSPNS > 0U) && (DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON)) || \
      (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE) )
#if (DEM_DET_RUNTIME_CHECK == STD_ON)
    Std_ReturnType ProcessCaptureResult = E_OK;
    boolean ErrorDetected = FALSE;
#endif
#else
  TS_PARAM_UNUSED(ServiceId);
  TS_PARAM_UNUSED(BufferStart);
#endif
#if (DEM_DET_RUNTIME_CHECK == STD_OFF)
  TS_PARAM_UNUSED(ServiceId);
#endif

  DBG_DEM_PROCESSEVENTPRECAPTURE_ENTRY(EventId, EventStatus, BufferStart,
    EventRelatedDataSize, ReportEDUpdate);

  EntryExists = DEM_IS_BIT_SET_IN_ARRAY(Dem_EvMemEntryExists, EventId);

  if (EventStatus != DEM_EVENT_STATUS_PASSED)
  {
#if (DEM_NUM_EDSEGS > 0U) && (DEM_NUM_EXT_DATAELEMENTS > 0U)
    /* !LINKSTO dsn.Dem.ExternalDataCapturing.CaptureExtendedData,1 */
#if (DEM_DET_RUNTIME_CHECK == STD_ON)
    ProcessCaptureResult = Dem_CaptureED(BufferStart, EntryExists, EventId,
      &EventRelatedDataSize->EDSize, ReportEDUpdate);

    if (ProcessCaptureResult == DEM_E_NODATAAVAILABLE)
    {
      ErrorDetected = TRUE;
    }
#else
    (void)Dem_CaptureED(BufferStart, EntryExists, EventId,
      &EventRelatedDataSize->EDSize, ReportEDUpdate);
#endif /* (DEM_DET_RUNTIME_CHECK == STD_ON) */
#else
  TS_PARAM_UNUSED(ReportEDUpdate);
#endif
  }
  /* Deviation TASKING-13 */
#pragma warning 549
  if ( (EventStatus != DEM_EVENT_STATUS_PASSED) ||
       ((EventStatus == DEM_EVENT_STATUS_PASSED) && (EntryExists == TRUE)) )
#pragma warning default
  {
    EventRelatedDataSize->StartPosRegularFF = EventRelatedDataSize->EDSize;
#if (DEM_NUM_FFCLS > 0U) && (DEM_NUM_FFSEGS > 0U)
    /* !LINKSTO dsn.Dem.ExternalDataCapturing.CaptureRegularFFData,1 */
#if (DEM_DET_RUNTIME_CHECK == STD_ON)
    ProcessCaptureResult = Dem_CaptureFF(DEM_REGULAR_FF,
                  &Dem_FFClass[Dem_GbiFFClassIdx(EventId)],
                  EventId,
                  EventStatus,
                  &BufferStart[EventRelatedDataSize->StartPosRegularFF],
                  &EventRelatedDataSize->RegularFFSize);

    if (ProcessCaptureResult == DEM_E_NODATAAVAILABLE)
    {
      ErrorDetected = TRUE;
    }
#else
    (void)Dem_CaptureFF(DEM_REGULAR_FF,
                  &Dem_FFClass[Dem_GbiFFClassIdx(EventId)],
                  EventId,
                  EventStatus,
                  &BufferStart[EventRelatedDataSize->StartPosRegularFF],
                  &EventRelatedDataSize->RegularFFSize);
#endif
#endif
  }
  if (EventStatus != DEM_EVENT_STATUS_PASSED)
  {
    EventRelatedDataSize->StartPosDevFF = EventRelatedDataSize->StartPosRegularFF +
                                          EventRelatedDataSize->RegularFFSize;

#if (DEM_DEV_FREEZE_FRAME_USED == STD_ON)
    /* !LINKSTO dsn.Dem.ExternalDataCapturing.CaptureDevelopmentFFData,1 */
#if (DEM_DET_RUNTIME_CHECK == STD_ON)
    ProcessCaptureResult = Dem_CaptureDevFFs(EventId,
                  &BufferStart[EventRelatedDataSize->StartPosDevFF],
                  EventRelatedDataSize);

    if (ProcessCaptureResult == DEM_E_NODATAAVAILABLE)
    {
      ErrorDetected = TRUE;
    }
#else
    (void)Dem_CaptureDevFFs(EventId,
                  &BufferStart[EventRelatedDataSize->StartPosDevFF],
                  EventRelatedDataSize);
#endif
#endif

    EventRelatedDataSize->StartPosRegularJ1939FF = EventRelatedDataSize->StartPosDevFF +
                                                   EventRelatedDataSize->DevAFFSize +
                                                   EventRelatedDataSize->DevBFFSize;
#if ( (DEM_NUM_J1939FFSPNS > 0U) && (DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON) )
#if (DEM_DET_RUNTIME_CHECK == STD_ON)
    ProcessCaptureResult = Dem_CaptureJ1939FF(
                            EventId,
                            &BufferStart[EventRelatedDataSize->StartPosRegularJ1939FF],
                            &EventRelatedDataSize->J1939FFSize);

    if (ProcessCaptureResult == DEM_E_NODATAAVAILABLE)
    {
      ErrorDetected = TRUE;
    }
#else
    (void)Dem_CaptureJ1939FF(
            EventId,
            &BufferStart[EventRelatedDataSize->StartPosRegularJ1939FF],
            &EventRelatedDataSize->J1939FFSize);
#endif
#endif

#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE)
    EventRelatedDataSize->StartPosRegularOBDFF = EventRelatedDataSize->StartPosRegularJ1939FF +
                                                 EventRelatedDataSize->J1939FFSize;
    if (Dem_GbiDTCKind(EventId) == DEM_DTC_KIND_EMISSION_REL_DTCS)
    {
      /* Deviation MISRAC2012-2 */
      if (DEM_GET_OBD_VARIANT() == DEM_OBD_VARIANT_OBDONUDS)
      {
        /* !LINKSTO dsn.Dem.ExternalDataCapturing.CaptureOBDonUDSFFData,1 */
#if (DEM_DET_RUNTIME_CHECK == STD_ON)
        ProcessCaptureResult = Dem_CaptureFF(DEM_OBDONUDS_FF,
                      &Dem_FFClass[DEM_OBDONUDS_FF_CLASS_IDX],
                      EventId,
                      EventStatus,
                      &BufferStart[EventRelatedDataSize->StartPosRegularOBDFF],
                      &EventRelatedDataSize->OBDFFSize);

        if (ProcessCaptureResult == DEM_E_NODATAAVAILABLE)
        {
          ErrorDetected = TRUE;
        }
#else
        (void)Dem_CaptureFF(DEM_OBDONUDS_FF,
                      &Dem_FFClass[DEM_OBDONUDS_FF_CLASS_IDX],
                      EventId,
                      EventStatus,
                      &BufferStart[EventRelatedDataSize->StartPosRegularOBDFF],
                      &EventRelatedDataSize->OBDFFSize);
#endif
      }
      /* Deviation MISRAC2012-2 */
      else /* (DEM_GET_OBD_VARIANT() == DEM_OBD_VARIANT_OBD_CLASSIC) */
      {
#if (DEM_NUM_OF_PIDS_IN_OBDFF > 0U)
        /* !LINKSTO dsn.Dem.ExternalDataCapturing.CaptureClassicOBDFFData,1 */
#if (DEM_DET_RUNTIME_CHECK == STD_ON)
        ProcessCaptureResult = Dem_CaptureOBDFreezeFrame(
          EventId,
          &BufferStart[EventRelatedDataSize->StartPosRegularOBDFF],
          &EventRelatedDataSize->OBDFFSize);

        if (ProcessCaptureResult == DEM_E_NODATAAVAILABLE)
        {
          ErrorDetected = TRUE;
        }
#else
        (void)Dem_CaptureOBDFreezeFrame(
                EventId,
                &BufferStart[EventRelatedDataSize->StartPosRegularOBDFF],
                &EventRelatedDataSize->OBDFFSize);
#endif
#endif
      }
    }
#endif
  }

#if (DEM_DET_RUNTIME_CHECK == STD_ON)
#if ( ((DEM_NUM_EDSEGS > 0U) && (DEM_NUM_EXT_DATAELEMENTS > 0U)) || \
      ((DEM_NUM_FFCLS > 0U) && (DEM_NUM_FFSEGS > 0U)) || \
      (DEM_DEV_FREEZE_FRAME_USED == STD_ON) || \
      ((DEM_NUM_J1939FFSPNS > 0U) && (DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON)) || \
      (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE) )
  TS_PARAM_UNUSED(ProcessCaptureResult);
  if (ErrorDetected == TRUE)
  {
    DEM_REPORT_RUNTIME_ERROR(ServiceId, DEM_E_NODATAAVAILABLE);
  }
#endif
#endif

  DBG_DEM_PROCESSEVENTPRECAPTURE_EXIT(EventId, EventStatus, BufferStart,
    EventRelatedDataSize, ReportEDUpdate);
}

FUNC(void, DEM_CODE) Dem_ProcessEvent(
  uint8                            ServiceId,
  Dem_EventInfoType                EventInfo,
  Dem_EventStatusType              EventStatus,
  Dem_StatusTransitionType         TransitionType,
  Dem_ProcessEventJobMaskType      Jobs,
  Dem_EventNotificationDataPtrType Notification)
{
  const Dem_EventIdType EventId = EventInfo.EventId;
  Dem_EntryDataPtrType BufferAddress = NULL_PTR;
  Dem_CaptureBufferCountType BufferIdx = 0U;
  boolean CaptureBufferAvailable = FALSE;
  Dem_ExternalEntryDataBufferManagementType EventRelatedDataSize =
    {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U};
  boolean ReportEDUpdate = FALSE;

#if ( (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) || \
      (DEM_NUM_CMB_DTCS > 0U) )
  /* ptr to make calculating the position happen outside the critical
     section */
  P2CONST(Dem_DTCStatusMaskType, AUTOMATIC, DEM_VAR) DTCStatusMaskPtr
                                             = &DEM_DTC_STATUS_MASKS[EventId];
#endif /* DEM_NUM_INDICATOR_LINKS, DEM_USE_CB_TRIG_ON_STATUS_CHANGE, ... */

#if (DEM_NUM_CMB_DTCS > 0U)
  Dem_DTCConfIdxType DTCConfIdx;
  Dem_EventStatusExtendedType OldCombinedStatus = 0U;
  Dem_EventStatusExtendedType NewCombinedStatus = 0U;
#endif
#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_SINGLE)
  /* check whether DTC is an OBD DTC, only necessary if any PID is configured,
   * otherwise no OBD FF needs to be processed */
  const Dem_DTCKindType DTCKind = Dem_GbiDTCKind(EventId);
#endif

  const boolean FirstFailed = ((TransitionType & DEM_TRANSITION_EVENT_TFTOC) != 0U)? TRUE:FALSE;
  DBG_DEM_PROCESSEVENT_ENTRY(ServiceId, EventInfo, EventStatus, TransitionType,
                             Jobs, Notification);

  if ((Jobs & DEM_PROCESSEVENT_ENTRYUPDATE) != 0x00U)
  {
    /* allocate buffer for capturing data */
    CaptureBufferAvailable = Dem_AllocateCaptureBuffer(ServiceId,
                                                       &BufferIdx,
                                                       &BufferAddress);

    if(CaptureBufferAvailable == TRUE)
    {
      Dem_ProcessEventPreCapture(ServiceId, EventId, EventStatus,
        BufferAddress, &EventRelatedDataSize, &ReportEDUpdate);
    }
  }
  /*
   * ENTER critical section to protect the event status and memory
   *       call-context: Dem (Task)
   */
  DEM_ENTER_EXCLUSIVE_AREA();

#if ((DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) || \
     (DEM_NUM_CMB_DTCS > 0U))

  /* ...store the old & new DTC status mask for 'status changed' notifications */
  Notification->ProcessedEventMsg.OldStatusMask = *DTCStatusMaskPtr;
#endif

  /* status and WIR update */
  Dem_ProcessEventStatusUpdate(EventId,
                               EventStatus,
                               FirstFailed,
                               Jobs,
                               Notification);
  /* !LINKSTO dsn.Dem.ExternalDataCapturing.NoBufferAvailable,1 */
  if ( ((Jobs & DEM_PROCESSEVENT_ENTRYUPDATE) != 0x00U) &&
       (CaptureBufferAvailable == TRUE) )
  {
#if (DEM_STORE_INTERNAL_EVENTS == STD_OFF)
    if (DEM_VALID_DTC_FOR_EVENT_STORAGE(EventId))
#endif
    {
      Dem_ProcessEventEntry(BufferAddress, EventInfo, EventStatus,
        Notification, TransitionType, EventRelatedDataSize);
    }
#if (DEM_TRIG_CB_ON_EVDAT == STD_ON)
    if (ReportEDUpdate == TRUE)
    {
      Notification->TriggerOnEventData = EventId;
    }
#endif
  }

#if ((DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) || \
     (DEM_NUM_CMB_DTCS > 0U))
  Notification->ProcessedEventMsg.NewStatusMask = *DTCStatusMaskPtr;

  /* check if DTC status has changed for new event
   * remark: this is always true for BSW events that were stored to
     error queue on PASSED or FAILED (TF bit changes) */
  if (Notification->ProcessedEventMsg.OldStatusMask !=
        Notification->ProcessedEventMsg.NewStatusMask)
  {
    /* status has changed, mark message 'to be sent' by writing event id */
    Notification->ProcessedEventMsg.EventId = EventId;
  }
#endif
#if (DEM_NUM_CMB_DTCS > 0U)
  DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
  if ((DEM_IS_DTC_COMBINED(DTCConfIdx)) &&
      (Notification->ProcessedEventMsg.EventId != DEM_EVENT_ID_INVALID))
  {
    OldCombinedStatus = Dem_CmbDTCStatus[DTCConfIdx];
    /* update status of combined DTC */
    NewCombinedStatus = Dem_CalculateCmbDTCStatus(DTCConfIdx, FALSE);
  }
#endif
  /*
   * LEAVE critical section
   */
  DEM_EXIT_EXCLUSIVE_AREA();

#if (DEM_NUM_CMB_DTCS > 0U)
  if (Notification->ProcessedEventMsg.EventId != DEM_EVENT_ID_INVALID)
  {
    Dem_InternalCheckOnCmbDTCStatusChange(EventId, OldCombinedStatus, NewCombinedStatus);
  }
  /* combined event was displaced. reset status of events involved in this combination.*/
  if (Notification->ReplacedEventMsg.EventId != DEM_EVENT_ID_INVALID)
  {
    if  ((DEM_IS_EVENT_COMBINED(Notification->ReplacedEventMsg.EventId)) &&
         (Notification->ReplacedEventMsg.DisplacedEvent != FALSE))
    {
      boolean CurrentEventStatusChanged = FALSE;

      if (Notification->ReplacedEventMsg.NewStatusMask !=
          Notification->ReplacedEventMsg.OldStatusMask)
      {
        CurrentEventStatusChanged = TRUE;
      }

      Dem_ResetStatusForCmbEvents(Notification->ReplacedEventMsg.EventId,
                                  CurrentEventStatusChanged);
    }
  }
#endif /* DEM_NUM_CMB_DTCS > 0U */

/* !LINKSTO Dem.Sem.CallbackEventSyncStorageProcessed,1 */
/* !LINKSTO dsn.Dem.Sem.SyncStoreProcCbAvailability,1 */
#if ( (DEM_SEM_SUPPORT == STD_ON) && (DEM_NUM_SEV_WITH_SYNC_STORE_PROC_CB > 0) )
  if ( ((Jobs & DEM_PROCESSEVENT_ENTRYUPDATE) != 0x00U) && \
       (DEM_IS_SECURITY_EVENT(EventId)) && \
       (EventStatus == DEM_EVENT_STATUS_FAILED) )
  {
    /* check if callback is configured and call it if applicable */
    Dem_CbFuncPtrSevSyncStoreProcType FuncPtr = Dem_GetSevSyncStoreProcCb(EventId);

    if (FuncPtr != NULL_PTR)
    {
      (void)FuncPtr();
    }
  }
#endif /* (DEM_SEM_SUPPORT == STD_ON) && (DEM_NUM_SEV_WITH_SYNC_STORE_PROC_CB > 0) */

#if ( (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) && \
      (DEM_SUPPORT_FIM_ON_FDC_TRESHOLD == STD_ON) )
  if (Notification->TriggerFimOnUnconfirmedData != DEM_EVENT_ID_INVALID)
  {
    /* trigger FiM with unconfirmed status */
    (void)FiM_DemTriggerOnUnconfirmed(Notification->TriggerFimOnUnconfirmedData);
  }
#endif

#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_SINGLE)
  /* !LINKSTO dsn.Dem.OBD.CheckDtcKindOfEvent,1 */
  /* check whether event is OBD relevant. If so, process OBD freeze frame.
     since Dem_ProcessSingleOBDFreezeFrame only handles OBD freeze frames,
     the check is necessary. */
  if ( ((Jobs & DEM_PROCESSEVENT_OBDENTRYUPDATE) != 0x00U) &&
       (DTCKind == DEM_DTC_KIND_EMISSION_REL_DTCS) )
  {
    Dem_ProcessSingleOBDFreezeFrame(EventId, BufferAddress);
  }
#endif /* (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_SINGLE) */

#if (DEM_MAX_NUM_EVENT_ENTRY_CAPTURE_BUFFER > 0U)
  /* release the heap buffer */
  Dem_EventMemoryCaptureBufferRelease(BufferIdx);
#endif

  DBG_DEM_PROCESSEVENT_EXIT(ServiceId, EventInfo, EventStatus, TransitionType,
                            Jobs, Notification);
}

STATIC FUNC(void, DEM_CODE) Dem_ProcessEventEntry(
  Dem_EntryDataPtrType             CapturedDataBuf,
  Dem_EventInfoType                EventInfo,
  Dem_EventStatusType              EventStatus,
  Dem_EventNotificationDataPtrType Notification,
  Dem_StatusTransitionType         TransitionType,
  Dem_ExternalEntryDataBufferManagementType EventRelatedDataSize)
{
  /* pointer to existing or newly allocated event memory entry */
  Dem_EventMemoryEntryPtrType EvMemEntryPtr =
    (Dem_EventMemoryEntryPtrType)NULL_PTR;
  /* index of existing or newly allocated event memory entry */
  Dem_SizeEvMemEntryType EvMemEntryIdx = 0U;
  Dem_EventIdType EventId = EventInfo.EventId;
  /* event id used for immediate storage. is overwritten by the
   * entry allocation function in case an existing entry is replaced. */
  Dem_EventIdType ReplacedEventId = EventId;
  Dem_EventEntryAllocResultType EventEntryAllocResult;

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
  boolean CheckImmediateStorage = FALSE;
  boolean NvMForceWrite = DEM_NVM_NO_FORCE;
#endif

  DBG_DEM_PROCESSEVENTENTRY_ENTRY(CapturedDataBuf, EventInfo, EventStatus, Notification, TransitionType);

  EventEntryAllocResult = Dem_GetEventEntryForUpdate(EventId,
                                                     EventStatus,
                                                     &EvMemEntryPtr,
                                                     &EvMemEntryIdx,
                                                     &ReplacedEventId,
                                                     Notification,
                                                     TransitionType);

#if (DEM_TRIGGER_ON_DEQUALIFICATION_SUPPORT == STD_ON) && (DEM_NUM_FFSEGS > 0U)
  if ( (EventStatus == DEM_EVENT_STATUS_PASSED) &&
       (EventEntryAllocResult == DEM_EVENTENTRYALLOC_EXISTS) &&
       (EventRelatedDataSize.RegularFFSize > 0U) )
  {
    /* for passed events only existing entries are updated */
    /* !LINKSTO Dem.FFCaptureOnDequalification.UpdateTrigger,1 */
    /* !LINKSTO Dem.FFCaptureOnDequalification.NoNewFFOnDequalification,1 */
    /* process freeze frame data for event */
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    CheckImmediateStorage = TRUE;
#endif
    Dem_ProcessEventEntryFFData(&CapturedDataBuf[EventRelatedDataSize.StartPosRegularFF],
                                EventId,
                                EventStatus,
                                EvMemEntryPtr,
                                Notification,
                                EventRelatedDataSize);
  }
#endif /* (DEM_TRIGGER_ON_DEQUALIFICATION_SUPPORT == STD_ON) && (DEM_NUM_FFSEGS > 0U) */

  if ( (EventStatus != DEM_EVENT_STATUS_PASSED) &&
       (EventEntryAllocResult != DEM_EVENTENTRYALLOC_INVALID) )
  {
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    CheckImmediateStorage = TRUE;
#endif

#if ( (DEM_USE_INT_VAL_AREA == STD_ON) || \
    (DEM_ED_OR_FF_OR_J1939FF_CONFIGURED == STD_ON) )
    /* update internal, extended and freeze frame data */

#if (DEM_OBDONUDS_FF_SUPPORT == STD_ON)
    if((TransitionType & DEM_TRANSITION_DTC_TF) != 0U)
#endif
    {
#if (DEM_USE_AGING == STD_ON)
      if (DEM_AGING_ALLOWED(EventId))
      {
        /* reset aging counter */
        DEM_ATOMIC_ASSIGN_8(*(Dem_IntValEntryData(EvMemEntryPtr)),
                            Dem_GbiNumAgingCycles(EventId));
      }
#endif /* DEM_USE_AGING */

#if ((DEM_NUM_EDSEGS > 0U) && (DEM_NUM_EXT_DATAELEMENTS > 0U))
#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
      /* if unconfirmed threshold is used for extended data capture,
       * extended data must be captured when the event status is unconfirmed
       * or when the event status reaches failed directly without having
       * reached unconfirmed in this operation cycle before */
      /* consecutive UNCONFIRMED results are filtered out during queuing */
      if ( (EventStatus == DEM_EVENT_STATUS_UNCONFIRMED) ||
           (!DEM_IS_ANY_BIT_SET(
              EvMemEntryPtr->SI30, DEM_SI30_STATUS_UNCONFIRMEDDTC_TOC)
           )
         )
#endif
      {
        /* process extended data for event */
        Dem_ProcessEventEntryEData(CapturedDataBuf, EventId, EvMemEntryPtr,
          EventEntryAllocResult, Notification, EventRelatedDataSize);
      }
#endif /* ((DEM_NUM_EDSEGS > 0U) && (DEM_NUM_EXT_DATAELEMENTS > 0U)) */

#if (DEM_FREEZE_FRAME_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
      /* if unconfirmed threshold is used for freeze frame capture,
       * only update the freeze frame if the new event status is failed,
       * or if the new status is unconfirmed and the event has not
       * failed yet. Furthermore, the event must not yet be confirmed. */
      /* consecutive UNCONFIRMED results are filtered out during queuing */
      if ( (!DEM_IS_EV_ST_BIT_CDTC_SET(EventId)) &&
           ( (EventStatus == DEM_EVENT_STATUS_FAILED) ||
             ( (EventStatus == DEM_EVENT_STATUS_UNCONFIRMED) &&
               (!DEM_IS_EV_ST_BIT_TF_SET(EventId))
             )
           )
         )
#endif /* DEM_FREEZE_FRAME_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD */
      {
        /* increment the occurrence counter of the event which is used for
         * calculating the number of freeze frames, for limiting the number of
         * times the event is stored immediately to NvM (by comparing with NvM
         * storage limit, if configured) and for using as an internal data
         * element if the occurrence counter is mapped to extended data */
        if (EvMemEntryPtr->OccCtr < 0xFFU)
        {
          ++(EvMemEntryPtr->OccCtr);
        }
#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U)
        EvMemEntryPtr->RootId = EventInfo.RootId;
#endif
#if (DEM_NUM_FFSEGS > 0U)
        /* process freeze frame data for event */
        Dem_ProcessEventEntryFFData(&CapturedDataBuf[EventRelatedDataSize.StartPosRegularFF],
                                    EventId,
                                    EventStatus,
                                    EvMemEntryPtr,
                                    Notification,
                                    EventRelatedDataSize);
#endif

#if ( (DEM_NUM_J1939FFSPNS > 0U) && (DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON) )
        Dem_StoreJ1939FF(&CapturedDataBuf[EventRelatedDataSize.StartPosRegularJ1939FF],
                         EventRelatedDataSize.J1939FFSize,
                         EvMemEntryPtr,
                         EventId,
                         Notification);
#endif
      }
    }
#endif /* ( (DEM_USE_INT_VAL_AREA == STD_ON) || \
          (DEM_ED_OR_FF_OR_J1939FF_CONFIGURED == STD_ON) ) */

#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE)
    Dem_ProcessMultipleOBDFreezeFrameEntry(
      &CapturedDataBuf[EventRelatedDataSize.StartPosRegularOBDFF],
      EventId,
      EvMemEntryIdx,
      EventEntryAllocResult,
      TransitionType,
      Notification,
      EventRelatedDataSize);
#endif /* DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE */

#if (DEM_OBDONUDS_FF_SUPPORT == STD_ON)
    if((TransitionType & DEM_TRANSITION_DTC_TF) != 0U)
#endif
    {
#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
      if (EventStatus == DEM_EVENT_STATUS_FAILED)
#endif
      {
#if ( (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) && (DEM_VCC_OCC5_USED == STD_ON) )
        /* !LINKSTO VCC_DEM_Table_10,2 */
        (EvMemEntryPtr)->OCC5 = 0U;
#endif
        /* only set the CDTC bit if the event is stored. Check needed for cmb events.*/
        if (EvMemEntryPtr->EventId == EventId)
        {
#if (DEM_NUM_FAILURECYCLES > 0U)
          const uint16 EventFailureClassIdx = Dem_GbiEventFailureClassIdx(EventId);

          /* if fault confirmation is disabled or threshold configured to one cycle */
          if ( (EventFailureClassIdx == DEM_NO_FAULT_CONFIRMATION) ||
               (EvMemEntryPtr->EventFailureCycleCounter >=
                DEM_INTERN_EVT_FAILCYC_CTR_THRESHOLD(EventId, EventFailureClassIdx)) )
#endif
          {
            /* !LINKSTO Dem.NoFaultConfirmation,1 */
            /* !LINKSTO Dem.OperationCycleQualification.SkipConfirmation,2 */
            /* !LINKSTO dsn.Dem.OBD.OPCYC.DCY.ExtensionDemProcessEventEntry,3 */
#if (DEM_OPCYC_OBD_DCY_USED == STD_ON)
            if (DEM_IS_CYCLE_QUALIFIED(EventId) == TRUE)
#endif
            {
              /* sets the confirmed status bit */
              DEM_SET_EV_ST_MASK((EventId), DEM_UDS_STATUS_CDTC);

#if (DEM_GET_DTCBYOCCURRENCETIME_SUPPORT == STD_ON)
              /* store event to be detected confirmed DTC occurrence kind */
              Dem_UpdateEventIdOccurKinds(EventId,
                DEM_FIRST_DET_CONFIRMED_DTC, DEM_MOST_REC_DET_CONFIRMED_DTC);
#endif
            }
          }

#if (DEM_RESET_PENDING_BIT_ON_OVERFLOW_SUPPORT == STD_ON)
          /* !LINKSTO dsn.Dem.SelectablePDTC.ProcessEventEntry,1 */
          /* !LINKSTO Dem.OBDonUDS.CombinedUDSDTCStatus.PDTC.SetByFailed.MemoryEntryExists,1 */
          /* set PendingDTC bit for current event */
          DEM_SET_EV_ST_MASK(EventId, DEM_UDS_STATUS_PDTC);
#endif

#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
          /* set TestFailedSinceLastClear/Aged bit */
          /* would be required only in case of new event memory entry,
           * because done synchronously otherwise */
          DEM_SET_MASK(EvMemEntryPtr->SI30, DEM_SI30_STATUS_TFSLC_AGED);

#if (DEM_OBD_Support == STD_ON)
          /* set EmissionRelatedDTC bit (Si30.Bit6) */
          if (Dem_GbiDTCKind(EventId) == DEM_DTC_KIND_EMISSION_REL_DTCS)
          {
            DEM_SET_MASK(EvMemEntryPtr->SI30, DEM_SI30_STATUS_EMISSIONRELATEDDTC);
          }
#endif
#endif /* (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) */
        }
      }
    }

#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
#if (DEM_SUPPORT_FIM_ON_FDC_TRESHOLD == STD_ON)
    /* trigger only on rising bit */
    if (!DEM_IS_ANY_BIT_SET(EvMemEntryPtr->SI30, DEM_SI30_STATUS_UNCONFIRMEDDTC))
    {
      /* trigger FiM with Unconfirmed status. Prestore EventId. The FiM callback
         is triggered later on (in Dem_ProcessAsyncEvent())outside the
         critical section.   */
      Notification->TriggerFimOnUnconfirmedData = EventId;
    }
    else
    {
      Notification->TriggerFimOnUnconfirmedData = DEM_EVENT_ID_INVALID;
    }
#endif

    /* set UnconfirmedDTC & -TOC & -SLC bits */
    /* would be required only in case of new event memory entry,
     * because done synchronously otherwise */
    DEM_SET_MASK(EvMemEntryPtr->SI30,
                 DEM_SI30_STATUS_UNCONFIRMEDDTC     |
                 DEM_SI30_STATUS_UNCONFIRMEDDTC_TOC |
                 DEM_SI30_STATUS_UNCONFIRMEDDTC_SLC);
#endif /* DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD */

#if (DEM_UPDATE_OCCORDER_ON_EVENTENTRY_UPDATE == STD_OFF)
    /* !LINKSTO Dem.SWS_Dem_00270,1 */
    /* if configured, that the OccOrder shall not be updated at every
     * failure occurrence: Check if a new event gets stored           */
    if (EventEntryAllocResult != DEM_EVENTENTRYALLOC_EXISTS)
#endif
    {
      /* !LINKSTO Dem.ASR40.SWS_Dem_00412,1, Dem.ASR40.SWS_Dem_00412_Implicit1,1 */
      /* update the occurrence order of the event */
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
      NvMForceWrite = Dem_UpdateOccurrenceOrder(EvMemEntryPtr);
#else
      (void)Dem_UpdateOccurrenceOrder(EvMemEntryPtr);
#endif
    }
  }

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
  if (CheckImmediateStorage == TRUE)
  {
    /* immediately delete the displaced entry (if configured for
     * related event) AND/OR immediately store the new/updated entry
     * (if configured for related event) */
    Dem_CheckForImmediateEntryStorage(ReplacedEventId,
                                      EvMemEntryPtr,
                                      EvMemEntryIdx,
                                      NvMForceWrite);
  }
#endif

#if (DEM_OBDONUDS_FF_SUPPORT == STD_OFF)
  TS_PARAM_UNUSED(TransitionType);
#endif
#if ( (DEM_ED_OR_FF_OR_J1939FF_CONFIGURED == STD_OFF) || \
      (DEM_OBDFF_SUPPORT_KIND != DEM_OBDFF_MULTIPLE) )
  TS_PARAM_UNUSED(CapturedDataBuf);
  TS_PARAM_UNUSED(EventRelatedDataSize);
#endif

  DBG_DEM_PROCESSEVENTENTRY_EXIT(CapturedDataBuf, EventInfo, EventStatus, Notification, TransitionType);
}

STATIC FUNC(void, DEM_CODE) Dem_ProcessEventStatusUpdate(
  Dem_EventIdType                  EventId,
  Dem_EventStatusType              EventStatus,
  boolean                          FirstFailed,
  Dem_ProcessEventJobMaskType      Jobs,
  Dem_EventNotificationDataPtrType Notification)
{
#if (DEM_NUM_INDICATOR_LINKS > 0U)
  boolean EventWIRUpdate;
  const Dem_ProcessEventJobMaskType RelevantJobs =
      (DEM_PROCESSEVENT_STATUSUPDATE | DEM_PROCESSEVENT_INDICATORUPDATE);
#else
  const Dem_ProcessEventJobMaskType RelevantJobs =
      DEM_PROCESSEVENT_STATUSUPDATE;
#endif /* (DEM_NUM_INDICATOR_LINKS > 0U) */
  DBG_DEM_PROCESSEVENTSTATUSUPDATE_ENTRY(EventId,
                                         EventStatus,
                                         FirstFailed,
                                         Jobs,
                                         Notification);
  if ((Jobs & RelevantJobs) != 0x00U)
  {
    /* asynchronous processing of BSW event status bits
     * reported on failed or passed qualification (but not on unconfirmed) */
    if ((Jobs & DEM_PROCESSEVENT_STATUSUPDATE) != 0x00U)
    {
#if (DEM_OPCYCLE_CTR_CSLF_SUPPORT == STD_ON)
      /* for event status DEM_EVENT_STATUS_FAILED or
       * DEM_EVENT_STATUS_CONFIRMED only */
      if (EventStatus != DEM_EVENT_STATUS_PASSED)
      {
        /* check if CSLF counter of event needs to be reset */
        Dem_ResetCycleSinceLastFailed(EventId);
      }
#endif
    }

    /* WIR Update */
#if (DEM_NUM_INDICATOR_LINKS > 0U)
    EventWIRUpdate = Dem_CheckForEventWIRUpdate(
                     EventId, EventStatus, FirstFailed);
#else /* DEM_NUM_INDICATOR_LINKS */
  TS_PARAM_UNUSED(FirstFailed);
#endif /* DEM_NUM_INDICATOR_LINKS */

    /* intentional nested critical section in this call */
    Dem_UpdateEventStatusOnQualification(EventId
                                       , EventStatus
#if (DEM_NUM_INDICATOR_LINKS > 0U)
                                       , EventWIRUpdate
#endif /* DEM_NUM_INDICATOR_LINKS */
                                       , Notification);
  }

  DBG_DEM_PROCESSEVENTSTATUSUPDATE_EXIT(EventId,
                                        EventStatus,
                                        FirstFailed,
                                        Jobs,
                                        Notification);
}

#if ( ( (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) || \
        (DEM_TRIG_CB_ON_EVDAT == STD_ON) ) ||           \
      ( (DEM_J1939_SUPPORT == STD_ON) &&                \
        (DEM_J1939_READING_DTC_SUPPORT == STD_ON) ) )
FUNC(void, DEM_CODE) Dem_ProcessEventNotifications(
  Dem_EventNotificationDataPtrType Notification)
{
  DBG_DEM_PROCESSEVENTNOTIFICATIONS_ENTRY(Notification);

#if ( (DEM_J1939_SUPPORT == STD_ON) && \
      (DEM_J1939_READING_DTC_SUPPORT == STD_ON) )
  if (Notification->Invoke_J1939Dcm_DemTriggerOnDTCStatus_Data != DEM_EVENT_ID_INVALID)
  {
    Dem_CbTriggerJ1939Dcm(Notification->Invoke_J1939Dcm_DemTriggerOnDTCStatus_Data);
  }
#endif

#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
    /* check if an EventStatusChangedMsg has been prepared by displacement */
  if (Notification->ReplacedEventMsg.EventId != DEM_EVENT_ID_INVALID)
  {
    Dem_CbTriggerOnEventStatus(Notification->ReplacedEventMsg.EventId,
                               Notification->ReplacedEventMsg.OldStatusMask,
                               Notification->ReplacedEventMsg.NewStatusMask);
  }
#endif

#if (DEM_TRIG_CB_ON_EVDAT == STD_ON)
  /* trigger EventDataChanged RTE/C callback (only once), when the event
   * memory entry for the event was updated */
  if (Notification->TriggerOnEventData != DEM_EVENT_ID_INVALID)
  {
    /* notify application that event data has changed */
    Dem_CbTriggerOnEventData(Notification->TriggerOnEventData);
  }
#endif /* (DEM_TRIG_CB_ON_EVDAT == STD_ON) */

#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
  if (Notification->ProcessedEventMsg.EventId != DEM_EVENT_ID_INVALID)
  {
    Dem_CbTriggerOnEventStatus(Notification->ProcessedEventMsg.EventId,
                               Notification->ProcessedEventMsg.OldStatusMask,
                               Notification->ProcessedEventMsg.NewStatusMask);
  }
#endif

  DBG_DEM_PROCESSEVENTNOTIFICATIONS_EXIT(Notification);
}
#endif /* ( (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) || \
            (DEM_TRIG_CB_ON_EVDAT == STD_ON) ) */

#if (DEM_GET_DTCBYOCCURRENCETIME_SUPPORT == STD_ON)
FUNC(void, DEM_CODE)  Dem_UpdateEventIdOccurKinds(
    Dem_EventIdType EventId,
    Dem_DTCRequestType FirstOccurKind,
    Dem_DTCRequestType MostRecentOccurKind)
{
  DBG_DEM_UPDATEEVENTIDOCCURKINDS_ENTRY(EventId, FirstOccurKind, MostRecentOccurKind);

  /* this assert ensures that FirstOccurKind and MostRecentOccurKind always fit together */
  DEM_PRECONDITION_ASSERT(
    ( (FirstOccurKind == DEM_FIRST_FAILED_DTC) &&
      (MostRecentOccurKind == DEM_MOST_RECENT_FAILED_DTC) ) ||
    ( (FirstOccurKind == DEM_FIRST_DET_CONFIRMED_DTC) &&
      (MostRecentOccurKind == DEM_MOST_REC_DET_CONFIRMED_DTC) ), DEM_INTERNAL_API_ID);

  /* check that the EventId is stored in primary memory */
  if (Dem_GbiDTCOrigin(EventId) == DEM_DTC_ORIGIN_PRIMARY_MEMORY)
  {
    /* make sure the UdsDTC for the current event is configured and not suppressed */
    if (Dem_GetVisibleUdsDTC(EventId) != DEM_NO_DTC)
    {
      Dem_EventIdType StoredFirstEventId = DEM_OCCURKIND_STORED_EVENT_ID(FirstOccurKind);
      if (StoredFirstEventId != DEM_EVENT_ID_INVALID)
      {
        if (Dem_GetVisibleUdsDTC(StoredFirstEventId) == DEM_NO_DTC)
        {
          /* invalidate the stored event if the assigned DTC is not visible */
          StoredFirstEventId = DEM_EVENT_ID_INVALID;
        }
      }
      /* if no event is stored for first occurrence kind and the assigned DTC of the stored
         event is visible */
      if (StoredFirstEventId == DEM_EVENT_ID_INVALID)
      {
        /* store event as first occurred DTC */
        DEM_OCCURKIND_STORED_EVENT_ID(FirstOccurKind) = EventId;
      }
      /* always store event as most recent occurred DTC */
      DEM_OCCURKIND_STORED_EVENT_ID(MostRecentOccurKind) = EventId;
    }
  }

  DBG_DEM_UPDATEEVENTIDOCCURKINDS_EXIT(EventId, FirstOccurKind, MostRecentOccurKind);
}
#endif /* DEM_GET_DTCBYOCCURRENCETIME_SUPPORT == STD_ON */

STATIC FUNC(Dem_EventEntryAllocResultType, DEM_CODE)
  Dem_GetEventEntryForUpdate(
    Dem_EventIdType                                          EventId,
    Dem_EventStatusType                                      EventStatus,
    P2VAR(Dem_EventMemoryEntryPtrType, AUTOMATIC, AUTOMATIC) EvMemEntryPtr,
    P2VAR(Dem_SizeEvMemEntryType, AUTOMATIC, AUTOMATIC)      EvMemIdxPtr,
    P2VAR(Dem_EventIdType, AUTOMATIC, AUTOMATIC)             ReplacedEventIdPtr,
    Dem_EventNotificationDataPtrType                         Notification,
    Dem_StatusTransitionType                                 TransitionType)
{
  Dem_EventEntryAllocResultType Result = DEM_EVENTENTRYALLOC_INVALID;

  DBG_DEM_GETEVENTENTRYFORUPDATE_ENTRY(EventId, EventStatus, EvMemEntryPtr,
    EvMemIdxPtr, ReplacedEventIdPtr, Notification, TransitionType);

#if (DEM_TRIGGER_ON_DEQUALIFICATION_SUPPORT == STD_ON) && (DEM_NUM_FFSEGS > 0U)
  if (EventStatus == DEM_EVENT_STATUS_PASSED)
  {
    /* for passed events only existing entries are updated */
    /* !LINKSTO Dem.FFCaptureOnDequalification.UpdateTrigger,1 */
    /* !LINKSTO Dem.FFCaptureOnDequalification.NoNewFFOnDequalification,1 */
    if (Dem_SearchForEntry(EventId, EvMemEntryPtr, EvMemIdxPtr) == TRUE)
    {
      Result = DEM_EVENTENTRYALLOC_EXISTS;
    }
  }
  else
#endif /* (DEM_TRIGGER_ON_DEQUALIFICATION_SUPPORT == STD_ON) */
  {
#if (DEM_OBDONUDS_FF_SUPPORT == STD_ON)
    /* on a TFTOC transition without TF transition, do not allocate an event entry,
     * but only update the last OBDonUDS FF of an existing event entry */
    if ( (DEM_GET_OBD_VARIANT() == DEM_OBD_VARIANT_OBDONUDS) &&
         ((TransitionType & DEM_TRANSITION_DTC_TF) == 0U) &&
         ((TransitionType & DEM_TRANSITION_DTC_TFTOC) != 0U))
    {
      if (Dem_SearchForEntry(EventId, EvMemEntryPtr, EvMemIdxPtr) == TRUE)
      {
        Result = DEM_EVENTENTRYALLOC_EXISTS;
      }
    }
    else
#endif
    {
      Result =
        Dem_FindOrAllocateEventEntry(EventId,
                                     EventStatus,
                                     EvMemEntryPtr,
                                     EvMemIdxPtr,
                                     ReplacedEventIdPtr,
                                     &Notification->ReplacedEventMsg);
    }
  }
#if (DEM_OBDONUDS_FF_SUPPORT == STD_OFF)
  TS_PARAM_UNUSED(TransitionType);
#endif

  DBG_DEM_GETEVENTENTRYFORUPDATE_EXIT(Result, EventId, EventStatus, EvMemEntryPtr,
    EvMemIdxPtr, ReplacedEventIdPtr, Notification, TransitionType);

  return Result;
}

STATIC FUNC(Dem_EventEntryAllocResultType, DEM_CODE)
  Dem_FindOrAllocateEventEntry(
    Dem_EventIdType                                          EventId,
    Dem_EventStatusType                                      EventStatus,
    P2VAR(Dem_EventMemoryEntryPtrType, AUTOMATIC, AUTOMATIC) EvMemEntryPtr,
    P2VAR(Dem_SizeEvMemEntryType, AUTOMATIC, AUTOMATIC)      EvMemIdxPtr,
    P2VAR(Dem_EventIdType, AUTOMATIC, AUTOMATIC)             ReplacedEventIdPtr,
    Dem_EventStatusChangedMsgPtrType                         EventStatusChangedMsgPtr)
{
  Dem_EventEntryAllocResultType AllocationResult = DEM_EVENTENTRYALLOC_INVALID;
  const uint8 OriginIdx = Dem_GbiDTCOriginIdx(EventId);

#if (DEM_NUM_FAILURECYCLES > 0U)
  const uint16 EventFailureClassIdx = Dem_GbiEventFailureClassIdx(EventId);
#endif

  DBG_DEM_FINDORALLOCATEEVENTENTRY_ENTRY(EventId, EventStatus, EvMemEntryPtr,
    EvMemIdxPtr, ReplacedEventIdPtr, EventStatusChangedMsgPtr);

#if ( (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD) || \
      ( (DEM_NUM_DEBOUNCE_COUNTER == 0U) && \
        (DEM_NUM_FAILURECYCLES == 0U) ) )
  TS_PARAM_UNUSED(EventStatus);
#endif

  /* search for DTC in event memory */
  if (Dem_SearchForEntry(EventId, EvMemEntryPtr, EvMemIdxPtr) == FALSE)
  {
    /* event entry not found -> search empty event memory entry */
    if (Dem_SearchForEmptyEntry(OriginIdx, EvMemEntryPtr, EvMemIdxPtr) == FALSE)
    {
      /* !LINKSTO Dem.ASR40.SWS_Dem_00400,1 */
      /* !LINKSTO Dem.OBDonUDS.CombinedUDSDTCStatus.FailureCounter.ResetByDisplacement,1 */
      /* empty entry not found -> find replaceable event memory entry */
      AllocationResult =
        Dem_ReplaceEventEntry(EventId, OriginIdx, EvMemEntryPtr, EvMemIdxPtr,
                              ReplacedEventIdPtr, EventStatusChangedMsgPtr);
    }
    else /* empty entry found */
    {
      /* an empty entry has been found and allocated */
      AllocationResult = DEM_EVENTENTRYALLOC_ALLOCATED;
    }

    if (AllocationResult != DEM_EVENTENTRYALLOC_INVALID)
    {
#if ( (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF) && \
      (DEM_NUM_CMB_DTCS > 0U) )
      Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
#endif
      /* create new event memory entry for the new or replaced event */
      const Dem_SizeEntryDataType width = Dem_EvMemEntrySize(EventId, TRUE);

      /* store initial event entry information depending on configuration */
      (*EvMemEntryPtr)->EventId = EventId;
      (*EvMemEntryPtr)->OccCtr = 0U;

      /* set the EvEntryExists status of the event or combined events */
      Dem_SetEvEntryExists(EventId, TRUE);

#if ( (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF) && \
      (DEM_NUM_CMB_DTCS > 0U) )
      /* clear the confirmed DTC bits for the other events in combination, as they
       * do not own the event memory entry */
      if (DEM_IS_DTC_COMBINED(DTCConfIdx))
      {
        Dem_CmbDTCEvLnkType CmbEvIdx;

        for (CmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx]; CmbEvIdx < Dem_CmbDTCEvLnk[DTCConfIdx + 1U]; CmbEvIdx++)
        {
          Dem_EventIdType CurrentEvent = Dem_CmbDTCEvents[CmbEvIdx];
          if (EventId != CurrentEvent)
          {
            /* CurrentEvent does NOT own the entry */
            DEM_CLR_EV_ST_MASK(CurrentEvent, DEM_UDS_STATUS_CDTC);
          }
        }
      }
#endif /* (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF) &&
          (DEM_NUM_CMB_DTCS > 0U) */

#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
      /* initialize DTC status indicators */
      (*EvMemEntryPtr)->SI30 = 0x00U;

      if (DEM_IS_EV_ST_BIT_WIR_SET(EventId))
      {
        /* WIR-bit already set before entry is created
         * (e.g. if FailureCycleCounterThreshold = 0)
         * -> set 'WIR since last clear'-bit */
        DEM_SET_MASK((*EvMemEntryPtr)->SI30, DEM_SI30_STATUS_WIR_SLC);
      }

#if (DEM_NUM_DEBOUNCE_COUNTER > 0U)
      if (EventStatus == DEM_EVENT_STATUS_UNCONFIRMED)
      {
        const Dem_EventIdType DebounceStatusIdx =
          Dem_GbiDebounceStatusIdx(EventId);
        const Dem_DebounceCounterClassIdxType DebounceClassIdx =
          Dem_GbiDebounceCounterClassIdx(DebounceStatusIdx);

          const sint16 UnconfirmedThreshold =
            Dem_DebounceCounterClass[DebounceClassIdx].CounterUnconfirmedThreshold;
          const sint16 FailedThreshold =
            Dem_DebounceCounterClass[DebounceClassIdx].CounterFailedThreshold;

          sint16 InternalCounter = Dem_DebounceCounterStatus[DebounceStatusIdx];

          /* check if internal debounce counter was decreased since event was
           * queued */
          if (InternalCounter < UnconfirmedThreshold)
          {
            InternalCounter = UnconfirmedThreshold;
          }

          /* set maximum fault detection counter since last clear */
          /* calculated value is always in range [1-127] */
          /* typecast sint32 (calculation range) -> sint8 (value range of same
             signedness) -> uint8 (conversion to unsigned) is based on MISRA */
          (*EvMemEntryPtr)->FDC12 = (uint8)((sint8)
            ( ((sint32)(InternalCounter) * DEM_FDC_VALUE_FAILED) /
              FailedThreshold ));

          (*EvMemEntryPtr)->OCC6 = 0U;
      }
      else /* DEM_EVENT_STATUS_FAILED */
#endif /* DEM_NUM_DEBOUNCE_COUNTER > 0U */
      {
        /* set maximum fault detection counter since last clear */
        (*EvMemEntryPtr)->FDC12 = DEM_FDC_VALUE_FAILED;

        /* initially set to 1 if status is FAILED */
        (*EvMemEntryPtr)->OCC6 = 1U;
      }

      /* OCCs set to initial values */
      (*EvMemEntryPtr)->OCC1 = 0U;
      (*EvMemEntryPtr)->OCC2 = 0U;
      (*EvMemEntryPtr)->OCC3 = 0U;
      (*EvMemEntryPtr)->OCC4 = 1U; /* set 1 to avoid update in first OpCyc */
#if ( DEM_VCC_OCC5_USED == STD_ON )
      (*EvMemEntryPtr)->OCC5 = 0U;
#endif
      /* OCC6 is already updated above */
      (*EvMemEntryPtr)->OCC7 = 0U;
#endif /* DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD */

#if (DEM_DEV_FREEZE_FRAME_USED == STD_ON)
      (*EvMemEntryPtr)->DevFFEntryIdx[DEM_DEVFF_A] = DEM_MAX_NUMBER_DEVFFA_ENTRY;
      (*EvMemEntryPtr)->DevFFEntryIdx[DEM_DEVFF_B] = DEM_MAX_NUMBER_DEVFFB_ENTRY;
#endif

#if (DEM_OPCYCLE_CTR_CSLF_SUPPORT == STD_ON)
      /* !LINKSTO Dem.OperationCycleCounters.CSLF.Allocation,1 */
      (*EvMemEntryPtr)->CSLF = 0U;
#endif
#if (DEM_OPCYCLE_CTR_CSFF_SUPPORT == STD_ON)
      /* !LINKSTO Dem.OperationCycleCounters.CSFF.Allocation,1 */
      (*EvMemEntryPtr)->CSFF = 0U;
#endif
#if (DEM_OPCYCLE_CTR_FAILEDCYCLES_SUPPORT == STD_ON)
      /* !LINKSTO Dem.OperationCycleCounters.FAILEDCYCLES.Allocation,1 */
      (*EvMemEntryPtr)->FAILEDCYCLES = 0U;
#endif

#if (DEM_NUM_FAILURECYCLES > 0U)
      if (EventFailureClassIdx != DEM_NO_FAULT_CONFIRMATION)
      {
#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON)
        /* operation and failure cycle data for event */
        const Dem_OperationCycleIdType EventFailureCycleIdx =
          Dem_GbiEventFailureCycleIdx(EventId, EventFailureClassIdx);
        const Dem_OperationCycleIdType EventOpCycleIdx =
          Dem_GbiOpCycleIdx(EventId);

#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
        /* VCC: events status can be other than FAILED */
        if (EventStatus == DEM_EVENT_STATUS_UNCONFIRMED)
        {
          /* upon first event UNCONFIRMED entry, set failure cycle counter */
          (*EvMemEntryPtr)->EventFailureCycleCounter = 0U;
        }
        else
#endif
        {
          /* upon first event FAILED entry, set failure cycle counter */
          if ( (EventFailureCycleIdx != EventOpCycleIdx) &&
               (DEM_OPCYCLESTATE[EventFailureCycleIdx] == DEM_CYCLE_STATE_END) )
          {
            /* separate failure cycle configured and
             * failure cycle not started and
             * first FAILED occurred */
            (*EvMemEntryPtr)->EventFailureCycleCounter = 0U;
          }
          else
          {
            /* no separate failure cycle configured or
             * separate failure cycle configured and separate
             * failure cycle started */
#if (DEM_MILGROUP_SUPPORT == STD_ON)
            /* !LINKSTO dsn.Dem.MILGroup.FailureCounterProcessing,1 */
            /* calculate MIL group failure counter to correctly initialize
             * the new entry */
            if (Dem_MILGroupProcessCounter(&((*EvMemEntryPtr)->EventFailureCycleCounter),
                                           EventId,
                                           DEM_NUM_INDICATOR_LINKS,
                                           DEM_MILGROUP_ENTRY_ALLOCATION) == FALSE)
#endif
            {
              /* !LINKSTO Dem.OBDonUDS.CombinedUDSDTCStatus.FailureCounter.CommonCounter,1 */
              /* !LINKSTO Dem.OBDonUDS.CombinedUDSDTCStatus.FailureCounter.Init,1 */
              /* !LINKSTO dsn.Dem.OBDonUDS.EventCombination.ResetCDTCOnOverflow.CommonFailureCounter,1 */
              /* !LINKSTO dsn.Dem.OBDonUDS.EventCombination.CmbCDTC,1 */

              /* If OBDonUDS combination is enabled, the common failure counter will be implicitly
               * set here and stored in the EventFailureCycleCounter of the first allocated
               * event memory entry owned by one of the combined events */
              (*EvMemEntryPtr)->EventFailureCycleCounter = 1U;
            }
          }
        }
#else /* DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF */
        {
          const Dem_StatusCounterPtrType FailureCounterPtr =
            Dem_GetStatusCounterReference(EventId);

          /* transfer global event failure counter into event memory entry */
          (*EvMemEntryPtr)->EventFailureCycleCounter = *FailureCounterPtr;
        }
#endif /* DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON */

#if ((DEM_NUM_CMB_DTCS > 0U) && (DEM_OBDONUDS_COMBINATION_ENABLED == STD_OFF))
        if (DEM_IS_EVENT_COMBINED(EventId))
        {
          /* VCC: initialize failure counters for combined events without checking
           * for unconfirmed status, since event combination is not available */
          Dem_InitFailureCounterOfCmbEvents(EventId);
        }
#endif /* (DEM_NUM_CMB_DTCS > 0U) && (DEM_OBDONUDS_COMBINATION_ENABLED == STD_OFF) */
      }
      else
      {
        /* no fault confirmation processing to be triggered */
        (*EvMemEntryPtr)->EventFailureCycleCounter = 0U;
      }
#endif /* (DEM_NUM_FAILURECYCLES > 0U) */

      if (width > 0U)
      {
        (*EvMemEntryPtr)->EntryDataPos = *(Dem_EntryDataFreePos[OriginIdx]);

        /* recalculate free position of event memory entry data */
        *(Dem_EntryDataFreePos[OriginIdx]) += width;
      }
    }
  }
  else /* entry exists */
  {
    /* !LINKSTO Dem.SWS_Dem_00270,1 */
    /* check if DTCRecordUpdate is locked */
    if (DEM_RECORD_UPDATE_LOCKED(EventId))
    {
      /* do not update the event memory entry */
      AllocationResult = DEM_EVENTENTRYALLOC_INVALID;
    }
    else
    {
      /* !LINKSTO Dem.OBDonUDS.CombinedUDSDTCStatus.FailureCounter.CommonCounter,1 */
      /* !LINKSTO dsn.Dem.OBDonUDS.EventCombination.ResetCDTCOnOverflow.CommonFailureCounter,1 */
      /* !LINKSTO dsn.Dem.OBDonUDS.EventCombination.CmbCDTC,1 */

      /* If OBDonUDS combination is enabled and an entry exists for one of the combined events,
       * the existed entry along with its common failure counter and its combined CDTC will remain
       * the same, maintaining one common event entry, only the event Id is updted */
#if (DEM_NUM_CMB_DTCS > 0U)
      if ((DEM_IS_EVENT_COMBINED(EventId)) && (EventId != (*EvMemEntryPtr)->EventId))
      {
#if ((DEM_NUM_FAILURECYCLES > 0U) && (DEM_OBDONUDS_COMBINATION_ENABLED == STD_OFF))
        boolean ReplaceCmbEvent = FALSE;

        if (EventFailureClassIdx != DEM_NO_FAULT_CONFIRMATION)
        {
          boolean CurrentEvThresholdReached;
          Dem_CmbDTCEvLnkType IndexOfCmbEv = Dem_GetFailureCounterIdxOfCmbEvent(EventId);
          /* check if the stored event reached its failure threshold */
          const boolean StoredEvThresholdReached = ((*EvMemEntryPtr)->EventFailureCycleCounter >=
                DEM_INTERN_EVT_FAILCYC_CTR_THRESHOLD((*EvMemEntryPtr)->EventId,
                Dem_GbiEventFailureClassIdx((*EvMemEntryPtr)->EventId))) ? TRUE: FALSE;

          /* check if the current event reached the threshold */
          CurrentEvThresholdReached = (DEM_CMBEV_FAILURE_CYC_COUNTER[IndexOfCmbEv] >=
            DEM_INTERN_EVT_FAILCYC_CTR_THRESHOLD(EventId, Dem_GbiEventFailureClassIdx(EventId))) ? TRUE: FALSE;

          /* replace the cmb ev if there is no risk to lose the confirmed state of the combined DTC */
          if ( (!StoredEvThresholdReached) || (CurrentEvThresholdReached) )
          {
            ReplaceCmbEvent = TRUE;
          }
        }
        else
        {
          /* no fault confirmation, event gets confirmed at first failed. */
          ReplaceCmbEvent = TRUE;
        }

        if (ReplaceCmbEvent == TRUE)
#endif /* (DEM_NUM_FAILURECYCLES > 0U) && (DEM_OBDONUDS_COMBINATION_ENABLED == STD_OFF) */
        {
#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
          const Dem_DTCStatusMaskType OldEventStatusMask = DEM_DTC_STATUS_MASKS[(*EvMemEntryPtr)->EventId];
#endif
          /* reset the CDTC bit of the cmb event that is replaced */
          DEM_CLR_EV_ST_MASK((*EvMemEntryPtr)->EventId, DEM_UDS_STATUS_CDTC);

#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
          /* notify application that event status has changed */
          if (OldEventStatusMask != DEM_DTC_STATUS_MASKS[(*EvMemEntryPtr)->EventId])
          {
            EventStatusChangedMsgPtr->EventId = (*EvMemEntryPtr)->EventId;
            EventStatusChangedMsgPtr->OldStatusMask = OldEventStatusMask;
            EventStatusChangedMsgPtr->NewStatusMask = DEM_DTC_STATUS_MASKS[(*EvMemEntryPtr)->EventId];
            /* EventStatusChangedMsgPtr->DisplacedEvent remains FALSE because no displacement
             * took place, only the EventId was changed */
          }
#endif
          /* replace the EventId in the memory entry because this event triggered an update */
          /* EvEntryExists status was already set for all combined events */
          (*EvMemEntryPtr)->EventId = EventId;
        }
      }
#endif /* DEM_NUM_CMB_DTCS > 0U */
      AllocationResult = DEM_EVENTENTRYALLOC_EXISTS;
    }
  }

  DBG_DEM_FINDORALLOCATEEVENTENTRY_EXIT(AllocationResult, EventId, EventStatus,
    EvMemEntryPtr, EvMemIdxPtr, ReplacedEventIdPtr, EventStatusChangedMsgPtr);

  return AllocationResult;
}

#if ((DEM_NUM_CMB_DTCS > 0U) && (DEM_NUM_FAILURECYCLES > 0U) && \
     (DEM_OBDONUDS_COMBINATION_ENABLED == STD_OFF))
STATIC FUNC(void, DEM_CODE) Dem_InitFailureCounterOfCmbEvents(
  Dem_EventIdType EventId)
{
  /* get the event failure cycle, it's the same for all cmb events */
  const uint16 EventFailureClassIdx = Dem_GbiEventFailureClassIdx(EventId);
  const Dem_OperationCycleIdType EventFailureCycleIdx =
            Dem_GbiEventFailureCycleIdx(EventId, EventFailureClassIdx);
  const Dem_DTCConfIdxType DTCConfIdx = DEM_GBI_DTCCONFIDX(EventId);
  const Dem_CmbDTCEvLnkType DTCConfIdxStart = Dem_CmbDTCEvLnk[DTCConfIdx];
  const Dem_CmbDTCEvLnkType DTCConfIdxEnd = Dem_CmbDTCEvLnk[DTCConfIdx + 1U];
  Dem_CmbDTCEvLnkType EvIdx;

  DBG_DEM_INITFAILURECTROFCMBEVENTS_ENTRY(EventId);

  for (EvIdx = DTCConfIdxStart; EvIdx < DTCConfIdxEnd; EvIdx++)
  {
    /* the operation cycle can be different for each cmb event */
    const Dem_OperationCycleIdType EventOpCycleIdx =
      Dem_GbiOpCycleIdx(Dem_CmbDTCEvents[EvIdx]);

    if ( (EventFailureCycleIdx != EventOpCycleIdx) &&
         (DEM_OPCYCLESTATE[EventFailureCycleIdx] == DEM_CYCLE_STATE_START) )
    {
      /* separate failure cycle started */
      DEM_CMBEV_FAILURE_CYC_COUNTER[EvIdx] = 1U;
    }
    else
    {
      /* no separate failure cycle or
       * separate failure cycle not started */
      DEM_CMBEV_FAILURE_CYC_COUNTER[EvIdx] = 0U;
    }

    if (EventId == Dem_CmbDTCEvents[EvIdx])
    {
      /* this is the event that is stored so it already failed, increment the failure counter */
      DEM_CMBEV_FAILURE_CYC_COUNTER[EvIdx]++;
    }
  }

  DBG_DEM_INITFAILURECTROFCMBEVENTS_EXIT(EventId);
}
#endif /* DEM_NUM_CMB_DTCS > 0U) && (DEM_NUM_FAILURECYCLES > 0U) &&
        * (DEM_OBDONUDS_COMBINATION_ENABLED == STD_OFF) */

STATIC FUNC(Dem_EventEntryAllocResultType, DEM_CODE) Dem_ReplaceEventEntry(
  Dem_EventIdType                                          EventId,
  uint8                                                    OriginIdx,
  P2VAR(Dem_EventMemoryEntryPtrType, AUTOMATIC, AUTOMATIC) EvMemEntryPtr,
  P2VAR(Dem_SizeEvMemEntryType, AUTOMATIC, AUTOMATIC)      EvMemIdxPtr,
  P2VAR(Dem_EventIdType, AUTOMATIC, AUTOMATIC)             ReplacedEventIdPtr,
  Dem_EventStatusChangedMsgPtrType                         EventStatusChangedMsgPtr)
{
  Dem_EventEntryAllocResultType AllocationResult =
    DEM_EVENTENTRYALLOC_INVALID;
#if (DEM_USE_EVENT_DISPLACEMENT == STD_ON)
  boolean ReplaceableEntryFound = FALSE;
#endif

  DBG_DEM_REPLACEEVENTENTRY_ENTRY(EventId, OriginIdx, EvMemEntryPtr,
    EvMemIdxPtr, ReplacedEventIdPtr, EventStatusChangedMsgPtr);

#if (DEM_USE_EVENT_DISPLACEMENT == STD_ON)
  /* find event memory entry to replace */
  ReplaceableEntryFound =
    Dem_SearchForEntryToReplace(OriginIdx, EventId,
      DEM_REGULAR_FF,
      EvMemEntryPtr, EvMemIdxPtr);

  /* !LINKSTO Dem.ASR40.SWS_Dem_00408,1 */
  /* clear existing event memory entry */
  if (ReplaceableEntryFound == TRUE)
  {
    Dem_EventIdType ReplacedEventId = (*EvMemEntryPtr)->EventId;

    /* !LINKSTO Dem.SWS_Dem_00270,1 */
    if (!DEM_RECORD_UPDATE_LOCKED(ReplacedEventId))
    {
#if ((DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) || (DEM_NUM_CMB_DTCS > 0U))
      Dem_DTCStatusMaskType ReplacedDTCStatusMask =
        DEM_DTC_STATUS_MASKS[ReplacedEventId];
#endif
      uint8 EventStatusClearMask = 0x00U;

      Dem_ClearEventEntry(*EvMemEntryPtr);

#if (DEM_RESET_PENDING_BIT_ON_OVERFLOW_SUPPORT == STD_ON)
      /* !LINKSTO dsn.Dem.SelectablePDTC.ReplaceEventEntry,1 */
      /* !LINKSTO SWS_Dem_00409_PendingDTC,1 */
      EventStatusClearMask |= DEM_UDS_STATUS_PDTC;
#endif

#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON)
      /* !LINKSTO SWS_Dem_00409_ConfirmedDTC,1 */
      EventStatusClearMask |= DEM_UDS_STATUS_CDTC;
#endif

#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT_FAULT_CONFIRMATION == STD_ON)
      if (Dem_GbiEventFailureClassIdx(EventId) != DEM_NO_FAULT_CONFIRMATION)
      {
        const Dem_StatusCounterPtrType FailureCounterPtr =
          Dem_GetStatusCounterReference(EventId);

        /* !LINKSTO dsn.Dem.StatusBitBehavior.EventDisplacement.Counter,2 */
        /* transfer event failure counter from displaced entry to
         * global event failure counter */
        *FailureCounterPtr = (*EvMemEntryPtr)->EventFailureCycleCounter;
      }
#endif

#if (DEM_STATUS_BIT_HANDLING_TESTFAILEDSINCELASTCLEAR == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT)
      /* clear confirmed and TestFailedSinceLastClear (only if configured),
       * but NOT warning indicator request bit */
      /* !LINKSTO Dem.SWS_Dem_01186,1 */
      EventStatusClearMask |= DEM_UDS_STATUS_TFSLC;
#endif

      DEM_CLR_EV_ST_MASK(ReplacedEventId, EventStatusClearMask);

#if ((DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) || (DEM_NUM_CMB_DTCS > 0U))
      /* notify application that event status has changed */
      EventStatusChangedMsgPtr->EventId = ReplacedEventId;
      EventStatusChangedMsgPtr->OldStatusMask = ReplacedDTCStatusMask;
      EventStatusChangedMsgPtr->NewStatusMask = DEM_DTC_STATUS_MASKS[ReplacedEventId];
#else
      TS_PARAM_UNUSED(EventStatusChangedMsgPtr);
#endif

#if (DEM_NUM_CMB_DTCS > 0U)
      /* This is needed for cmb events to know if the entry was displaced and update the status
        * of events involved in this combination. */
       EventStatusChangedMsgPtr->DisplacedEvent = TRUE;
#endif
      /* return the id of the replaced event */
      *ReplacedEventIdPtr = ReplacedEventId;
      /* a replaceable entry has been found */
      AllocationResult = DEM_EVENTENTRYALLOC_REPLACED;
    } /* else: DTCRecordUpdate is locked; DEM_EVENTENTRYALLOC_INVALID */
  } /* else: no replaceable entry has been found; DEM_EVENTENTRYALLOC_INVALID */
#else
  TS_PARAM_UNUSED(EventId);
  TS_PARAM_UNUSED(EvMemEntryPtr);
  TS_PARAM_UNUSED(EvMemIdxPtr);
  TS_PARAM_UNUSED(ReplacedEventIdPtr);
  TS_PARAM_UNUSED(EventStatusChangedMsgPtr);
#endif /* DEM_USE_EVENT_DISPLACEMENT == STD_ON */

  /* if memory overflow indication bit is not set, set it now and call
   * callback functions for events in the origin */
  if (!DEM_IS_OVFIND_SET(OriginIdx))
  {
    /* set event memory overflow indication bit */
    DEM_ATOMIC_SET_BIT_8(DEM_OVFIND_FLAGS, OriginIdx);

#if (DEM_CB_TRIG_ON_EVDAT_ASR403 == STD_ON)
#if ( (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON) && \
      (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON) )
    /* check if Event data change callback function needs to be called
     * for events in the origin and invoke callback function */
    Dem_CbTriggerOnOvfIndSet(OriginIdx);
#endif
#endif /* (DEM_CB_TRIG_ON_EVDAT_ASR403 == STD_ON) */
  }

  DBG_DEM_REPLACEEVENTENTRY_EXIT(AllocationResult, EventId, OriginIdx,
    EvMemEntryPtr, EvMemIdxPtr, ReplacedEventIdPtr, EventStatusChangedMsgPtr);
  return AllocationResult;
}

#if (DEM_NUM_FFSEGS > 0U)
STATIC FUNC(void, DEM_CODE) Dem_ProcessEventEntryFFData(
  Dem_EntryDataPtrType                        CapturedDataBuf,
  Dem_EventIdType                             EventId,
  Dem_EventStatusType                         EventStatus,
  Dem_EventMemoryEntryPtrType                 EvMemEntryPtr,
  Dem_EventNotificationDataPtrType            Notification,
  Dem_ExternalEntryDataBufferManagementType   EventRelatedDataSize)
{
  Std_ReturnType UpdateResult = DEM_EVENTENTRY_NO_UPDATE_REQUIRED;
  boolean ProcessFFStorage = TRUE;
  Dem_FFClassIdxType IndividPartFFClassIdx = Dem_GbiFFClassIdx(EventId);

  DBG_DEM_PROCESSEVENTENTRYFFDATA_ENTRY(CapturedDataBuf, EventId, EventStatus,
    EvMemEntryPtr, Notification, EventRelatedDataSize);


  if(((EventRelatedDataSize.RegularFFSize) > 0U) ||
     ((EventRelatedDataSize.DevAFFSize ) > 0U) ||
     ((EventRelatedDataSize.DevBFFSize ) > 0U))
  {
  /* check if a FF class is assigned to event */
#if (DEM_COMMON_FREEZEFRAMES_USED == STD_ON)
    if (Dem_CommonPartFFClassIdx[DEM_REGULAR_FF] == DEM_FFCLS_NULL_IDX)
#endif
    {
      if (IndividPartFFClassIdx == DEM_FFCLS_NULL_IDX)
      {
        ProcessFFStorage = FALSE;
      }
    }

    if (ProcessFFStorage == TRUE)
    {
      const Dem_FFIdxType MaxNumFF = Dem_GbiMaxNumFFRecs(EventId);

      /* get freeze frame class layout */
      CONSTP2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFClass =
        &Dem_FFClass[IndividPartFFClassIdx];

      /* if unconfirmed threshold is used for freeze frame capture, the
       * last freeze frame record always has to be stored. This is in
       * conflict with Dem.ASR40.SWS_Dem_00585. */
#if (DEM_FREEZE_FRAME_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD)
      /* If MaxNumFF = 1, a freeze frame is only captured at the very first
       * FAILED occurrence (note of Dem.ASR40.SWS_Dem_00585). Data elements
       * configured to DEM_TRIGGER_ON_DEQUALIFICATION are updated once at
       * first subsequent PASSED occurrence. */
      if ((MaxNumFF > 1U) || (EvMemEntryPtr->OccCtr == 1U))
#else
#if (DEM_CALIBRATION_WITHOUTEVCOMB_SUPPORT == STD_ON)
      const boolean FreezeFrameUpdate = Dem_GbiFreezeFrameUpdate(EventId);

      /* if the maximum number of freeze frames has been reached,
         the update strategy is calibrateable */
      if ( (EvMemEntryPtr->OccCtr <= MaxNumFF) || (FreezeFrameUpdate == TRUE) )
#endif
#endif /* DEM_FREEZE_FRAME_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD */
      {
        /* get Index where to place the new FF */
        /* FFIndex is obtained by subtracting one from DEM_NUMFF() since
         * OccCtr is incremented before.
         * if OccCtr > MaxNumFF, the most recent freeze frame record will be
         * replaced */

        /* Note for (DEM_TRIGGER_ON_DEQUALIFICATION_SUPPORT == STD_ON):
         * The following FFIndex is also valid for PASSED events, for which
         * the most recent FF is updated. Dem_ProcessEventEntry() does not
         * increment the OccCtr for passed events and accordingly FFIndex
         * as calculated below "points" to the most recent freeze frame. */
        /* !LINKSTO Dem.FFCaptureOnDequalification.NoNewFFOnDequalification,1 */
        const Dem_FFIdxType FFIndex = DEM_NUMFF(EvMemEntryPtr, MaxNumFF) - 1U;

#if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
        const Dem_EventIdType PFFIndex = Dem_GetPFFIndex(EventId);
#endif

        /* pointer to FF data - for writing */
        const Dem_EntryDataPtrType FFEntryData =
          Dem_FFEntryData(EvMemEntryPtr, FFClass, FFIndex);

#if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
        /* !LINKSTO Dem.SWS_Dem_00464,1 */
        /* check if prestored freeze frame for this event exists */
        if ( (Dem_GbiEnablePrestorage(EventId) != FALSE) &&
             DEM_IS_BIT_SET_IN_ARRAY(Dem_PFFEntryValid, PFFIndex) &&
             (EventStatus != DEM_EVENT_STATUS_PASSED) )
        {
          /* get destination pointer to prestore freeze frame */
          const Dem_EntryDataPtrConstType PFFEntryData =
            Dem_GetPFFEntryDataPtr(EventId);

          /* copy PFF to event memory */
          TS_MemCpy(FFEntryData, PFFEntryData,
            Dem_SizeOfFF(DEM_REGULAR_FF, FFClass));

          /* !LINKSTO Dem.SWS_Dem_00969,1 */
          /* mark prestored freeze frame as empty */
          DEM_CLR_BIT_IN_ARRAY(Dem_PFFEntryValid, PFFIndex);
#if (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON)
          UpdateResult = DEM_EVENTENTRY_UPDATED;
#endif
        }
        else
#endif /* DEM_MAX_NUMBER_PRESTORED_FF > 0U */
        {
          /* !LINKSTO Dem.SWS_Dem_00191,1 */
          UpdateResult = Dem_StoreFF(
                           CapturedDataBuf,
                           DEM_REGULAR_FF,
                           FFClass,
                           FFEntryData,
                           EventStatus);
        }
      }
    }

#if (DEM_DEV_FREEZE_FRAME_USED == STD_ON)
#if (DEM_TRIGGER_ON_DEQUALIFICATION_SUPPORT == STD_ON)
    if (EventStatus != DEM_EVENT_STATUS_PASSED)
#endif
    {
      /* !LINKSTO VCC_DEM_006_Req123v1,1 */
      if (EvMemEntryPtr->OccCtr == 1U)
      {
        /* !LINKSTO dsn.Dem.DevFF.IB.ProcessEventEntryFFData,1 */
        (void)Dem_StoreDevFFs(&CapturedDataBuf[EventRelatedDataSize.RegularFFSize],
                EventId, EvMemEntryPtr, EventRelatedDataSize);
      }
    }
#endif /* (DEM_DEV_FREEZE_FRAME_USED == STD_ON) */

    if (UpdateResult != DEM_EVENTENTRY_NO_UPDATE_REQUIRED)
    {
#if (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON)
      Notification->TriggerOnEventData = EventId;
#else
      TS_PARAM_UNUSED(Notification);
#endif
    }

#if (DEM_DEV_FREEZE_FRAME_USED == STD_OFF)
    TS_PARAM_UNUSED(EventRelatedDataSize);
#endif
  }

  DBG_DEM_PROCESSEVENTENTRYFFDATA_EXIT(CapturedDataBuf, EventId,
    EventStatus, EvMemEntryPtr, Notification, EventRelatedDataSize);
}
#endif /* (DEM_NUM_FFSEGS > 0U) */

#if ( (DEM_NUM_EDSEGS > 0U) && \
      (DEM_NUM_EXT_DATAELEMENTS > 0U) )
STATIC FUNC(void, DEM_CODE) Dem_ProcessEventEntryEData(
  Dem_EntryDataPtrType                        CapturedDataBuf,
  Dem_EventIdType                             EventId,
  Dem_EventMemoryEntryPtrConstType            EvMemEntryPtr,
  Dem_EventEntryAllocResultType               EventEntryAllocResult,
  Dem_EventNotificationDataPtrType            Notification,
  Dem_ExternalEntryDataBufferManagementType   EventRelatedDataSize)
{
  boolean EntryExists = FALSE;
  /* pointer to ED data - for writing */
  const Dem_EntryDataPtrType EDEntryData = Dem_EDEntryData(EvMemEntryPtr);
  /* get extended data class layout */
  CONSTP2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass =
    &Dem_EDClass[Dem_GbiEDClassIdx(EventId)];

  DBG_DEM_PROCESSEVENTENTRYEDATA_ENTRY(CapturedDataBuf, EventId,
    EvMemEntryPtr, EventEntryAllocResult, Notification, EventRelatedDataSize);

  if(EventRelatedDataSize.EDSize > 0U)
  {

    /* initialize ED entry data area at new (or displaced) entry only */
    if ( (EventEntryAllocResult == DEM_EVENTENTRYALLOC_ALLOCATED) ||
         (EventEntryAllocResult == DEM_EVENTENTRYALLOC_REPLACED) )
    {
      Dem_SizeEntryDataType Index;
      Dem_SizeEDType SizeOfED = Dem_SizeOfED(EDClass);

      for (Index = 0U; Index < SizeOfED; ++Index)
      {
        EDEntryData[Index] = 0U;
      }
    }
    else /* EventEntryAllocResult == INVALID or EXISTS */
    {
      EntryExists = TRUE;
    }

    /* update extended data */
    Dem_StoreED(CapturedDataBuf, EDEntryData, EDClass, EntryExists);

#if (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON)
  Notification->TriggerOnEventData = EventId;
#else
  TS_PARAM_UNUSED(Notification);
#endif
  }

  DBG_DEM_PROCESSEVENTENTRYEDATA_EXIT(CapturedDataBuf, EventId,
    EvMemEntryPtr, EventEntryAllocResult, Notification, EventRelatedDataSize);
}
#endif /* ( (DEM_NUM_EDSEGS > 0U) && (DEM_NUM_EXT_DATAELEMENTS > 0U) ) */

#if (DEM_NUM_FFSEGS > 0U)
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_StoreFF(
  P2VAR(Dem_EntryDataType, AUTOMATIC, AUTOMATIC)      CapturedDataBuf,
  Dem_FFKindType                                      FFKind,
  CONSTP2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) IndividPartFFClass,
  const Dem_EntryDataPtrType                          FFEntryData,
  Dem_EventStatusType                                 EventStatus)
{
  Dem_NumFFSegsType SegIdx;
  Std_ReturnType Result = DEM_EVENTENTRY_NO_UPDATE_REQUIRED;

  Dem_SizeEntryDataType FFStartByte = 0U;
  uint8_least FFPartIdx;

  P2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFPartClass[DEM_NUM_FFPARTS];
#if (DEM_COMMON_FREEZEFRAMES_USED == STD_ON)
  FFPartClass[0] = &Dem_FFClass[Dem_CommonPartFFClassIdx[FFKind]];
#endif
  FFPartClass[DEM_NUM_FFPARTS - 1U] = IndividPartFFClass;

  DBG_DEM_STOREFF_ENTRY(CapturedDataBuf, FFKind, IndividPartFFClass, FFEntryData, EventStatus);

#if (DEM_COMMON_FREEZEFRAMES_USED == STD_OFF)
  TS_PARAM_UNUSED(FFKind);
#endif
#if (DEM_TRIGGER_ON_DEQUALIFICATION_SUPPORT == STD_OFF)
  TS_PARAM_UNUSED(EventStatus);
#endif

  /* Deviation TASKING-1 */
  for (FFPartIdx = 0U; FFPartIdx < DEM_NUM_FFPARTS; FFPartIdx++)
  {
    /* get data values to all data Ids of the freeze frame class */
    for (SegIdx = 0U; SegIdx < FFPartClass[FFPartIdx]->NumFFSegs; ++SegIdx)
    {
      const Dem_FFSegIdxType FFSegIdx =
        FFPartClass[FFPartIdx]->FFSegIdx[SegIdx];

      if (FFSegIdx != DEM_FFSEG_IDX_UNUSED)
      {
        P2CONST(Dem_FFSegmentType, AUTOMATIC, DEM_CONST) FFSegment =
                                               &Dem_FFSegment[FFSegIdx];
        const Dem_SizeFFType FFSegSize =
                        Dem_SizeOfFFSegment(FFSegment);
        if (EventStatus != DEM_EVENT_STATUS_PASSED)
        {
          TS_MemCpy(&FFEntryData[FFStartByte], &CapturedDataBuf[FFStartByte], FFSegSize);
          FFStartByte += FFSegSize;
          Result = DEM_EVENTENTRY_UPDATED;
        }
#if (DEM_TRIGGER_ON_DEQUALIFICATION_SUPPORT == STD_ON)
        else
        {
          Dem_NumDataElementsType DataElementIndex;

          /* add all data elements of the FF segment */
          for (DataElementIndex = 0U;
               DataElementIndex < FFSegment->NumFFDataElements;
               ++DataElementIndex)
          {
            const Dem_DataElementIdxType DataElementIdx =
              FFSegment->DataElementIdx[DataElementIndex];
            const Dem_SizeEntryDataType DataElementSize =
              DEM_EXTERNAL_DATA_ELEMENT_SIZE(DataElementIdx);

            const Dem_DataElementTriggerPointType Trigger =
              DEM_DATA_ELEMENT_TRIGGER(Dem_DataElement[DataElementIdx].TriggerPointAndDataType);

            /* !LINKSTO Dem.FFCaptureOnDequalification.CaptureDequalificationDataElements,1 */
            if (Trigger == DEM_TRIGGER_ON_DEQUALIFICATION)
            {
              /* copy content into the destination buffer */
              TS_MemCpy(&FFEntryData[FFStartByte], &CapturedDataBuf[FFStartByte], DataElementSize);
              Result = DEM_EVENTENTRY_UPDATED;
            }

            /* add element size -> start byte for the next element */
            FFStartByte += DataElementSize;
          }
        }
#endif /* (DEM_TRIGGER_ON_DEQUALIFICATION_SUPPORT == STD_ON) */
      }
    }
  }
  DBG_DEM_STOREFF_EXIT(
    Result, CapturedDataBuf, FFKind, IndividPartFFClass, FFEntryData, EventStatus);
  return Result;
}

STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_CaptureFF(
  Dem_FFKindType                                      FFKind,
  CONSTP2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) IndividPartFFClass,
  Dem_EventIdType                                     EventId,
  Dem_EventStatusType                                 EventStatus,
  P2VAR(Dem_EntryDataType, AUTOMATIC, AUTOMATIC)      FFDataDestination,
  P2VAR(Dem_SizeEntryDataType, AUTOMATIC, AUTOMATIC)  FFSize)
{
  Dem_NumFFSegsType SegIdx;
  Std_ReturnType Result = E_OK;
  P2CONST(Dem_FFSegmentType, AUTOMATIC, DEM_CONST) FFSegment;
  Dem_NumDataElementsType DataElementIndex;
  Dem_SizeEntryDataType FFStartByte = 0U;
  uint8_least FFPartIdx;

  P2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFPartClass[DEM_NUM_FFPARTS];
#if (DEM_COMMON_FREEZEFRAMES_USED == STD_ON)
  FFPartClass[0] = &Dem_FFClass[Dem_CommonPartFFClassIdx[FFKind]];
#endif
  FFPartClass[DEM_NUM_FFPARTS - 1U] = IndividPartFFClass;

  DBG_DEM_CAPTUREFF_ENTRY(FFKind, IndividPartFFClass, EventId,
    EventStatus, FFDataDestination, FFSize);

#if (DEM_COMMON_FREEZEFRAMES_USED == STD_OFF)
  TS_PARAM_UNUSED(FFKind);
#endif
#if (DEM_TRIGGER_ON_DEQUALIFICATION_SUPPORT == STD_OFF)
  TS_PARAM_UNUSED(EventStatus);
#endif

  /* Deviation TASKING-1 */
  for (FFPartIdx = 0U; FFPartIdx < DEM_NUM_FFPARTS; FFPartIdx++)
  {
    /* get data values to all data Ids of the freeze frame class */
    for (SegIdx = 0U; SegIdx < FFPartClass[FFPartIdx]->NumFFSegs; ++SegIdx)
    {
      const Dem_FFSegIdxType FFSegIdx =
        FFPartClass[FFPartIdx]->FFSegIdx[SegIdx];

      if (FFSegIdx != DEM_FFSEG_IDX_UNUSED)
      {
        Std_ReturnType DataPresent = E_NOT_OK;

        FFSegment = &Dem_FFSegment[FFSegIdx];

        /* add all data elements of the FF segment */
        for (DataElementIndex = 0U;
             DataElementIndex < FFSegment->NumFFDataElements;
             ++DataElementIndex)
        {
          boolean FillWithPadding = FALSE;
          const Dem_DataElementIdxType DataElementIdx =
            FFSegment->DataElementIdx[DataElementIndex];
          const Dem_SizeEntryDataType DataElementSize =
            DEM_EXTERNAL_DATA_ELEMENT_SIZE(DataElementIdx);

#if (DEM_TRIGGER_ON_DEQUALIFICATION_SUPPORT == STD_ON)
          const Dem_DataElementTriggerPointType Trigger =
            DEM_DATA_ELEMENT_TRIGGER(Dem_DataElement[DataElementIdx].TriggerPointAndDataType);

          if ( ( (EventStatus == DEM_EVENT_STATUS_FAILED) ||
                 (EventStatus == DEM_EVENT_STATUS_CONFIRMED) ) &&
               (Trigger == DEM_TRIGGER_ON_DEQUALIFICATION) )
          {
            /* !LINKSTO Dem.FFCaptureOnDequalification.InitDequalificationDataElements,1 */
            FillWithPadding = TRUE;
          }
          else if ( ( ( (EventStatus == DEM_EVENT_STATUS_FAILED) ||
                        (EventStatus == DEM_EVENT_STATUS_CONFIRMED) ) &&
                      (Trigger == DEM_TRIGGER_ON_QUALIFICATION) ) ||
                    ( (EventStatus == DEM_EVENT_STATUS_PASSED) &&
                      (Trigger == DEM_TRIGGER_ON_DEQUALIFICATION) ) )
          /* !LINKSTO Dem.FFCaptureOnDequalification.CaptureDequalificationDataElements,1 */
#endif
          {
            DataPresent =
              Dem_ReadExternalDataElement(&FFDataDestination[FFStartByte],
                                          DataElementIdx,
                                          EventId);

            if (DataPresent != E_OK)
            {
              FillWithPadding = TRUE;

#if (DEM_DET_RUNTIME_CHECK == STD_ON)
              /* data for FFS cannot be read, return DEM_E_NODATAAVAILABLE;
               * this return value is used to report a DET error in
               * Dem_PrestoreFreezeFrame or outside the exclusive area opened in
               * Dem_ProcessEvent */
              Result =  DEM_E_NODATAAVAILABLE;
#endif
            }
          }
#if (DEM_TRIGGER_ON_DEQUALIFICATION_SUPPORT == STD_ON)
          else /* PASSED and DEM_TRIGGER_ON_QUALIFICATION */
          {
            /* else-path explicitly added because of MISRA rule 15.7 */
          }
#endif

          if (FillWithPadding == TRUE)
          {
            const Dem_SizeEntryDataType StartIndex = FFStartByte;
            Dem_SizeEntryDataType StopIndex;
            Dem_SizeEntryDataType Index;

            StopIndex = StartIndex + DataElementSize;

            /* fill FF segment with padding values */
            for (Index = StartIndex; Index < StopIndex; ++Index)
            {
              FFDataDestination[Index] = DEM_DATA_PADDING_VALUE;
            }
          }

          /* add element size -> start byte for the next element */
          FFStartByte += DataElementSize;
        }
      }
    }
  }

  /* FF data was stored/updated in event memory */
  *FFSize = FFStartByte;

  DBG_DEM_CAPTUREFF_EXIT(Result, FFKind, IndividPartFFClass,
    EventId, EventStatus, FFDataDestination, FFSize);
  return Result;
}

#if (DEM_DEV_FREEZE_FRAME_USED == STD_ON)
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_CaptureDevFFs(
  Dem_EventIdType                                                        EventId,
  P2VAR(Dem_EntryDataType, AUTOMATIC, AUTOMATIC)                         FFDataDestination,
  P2VAR(Dem_ExternalEntryDataBufferManagementType, AUTOMATIC, AUTOMATIC) EventRelatedDataSize)
{
  Std_ReturnType Result = E_OK;
  uint8 IdxDevFFKind;

  DBG_DEM_CAPTUREDEVFFS_ENTRY(FFKind, IndividPartFFClass, EventId,
      EventStatus, FFDataDestination, DevFFSize);
  for (IdxDevFFKind = DEM_DEVFF_A;
       IdxDevFFKind <= DEM_DEVFF_B;
       ++IdxDevFFKind)
  {
    const Dem_FFClassIdxType DevFFClassIdx =
      Dem_EventDescDevFF[EventId][IdxDevFFKind].DevFFClassIdx;
    Dem_SizeEntryDataType *DevFFSize = (IdxDevFFKind == DEM_DEVFF_A) ?
      &EventRelatedDataSize->DevAFFSize : &EventRelatedDataSize->DevBFFSize;
#if (DEM_DET_RUNTIME_CHECK == STD_ON)
    Std_ReturnType CaptureResult = E_OK;
    CaptureResult = Dem_CaptureFF(
      IdxDevFFKind,
      &Dem_FFClass[DevFFClassIdx],
      EventId,
      DEM_EVENT_STATUS_FAILED,
      &FFDataDestination[EventRelatedDataSize->DevAFFSize],
      DevFFSize);

    /* DET error can be reported by DevFFA or DevFFB, but DEM_E_NODATAAVAILABLE
     * reported by DevFFA can be overwritten by DevFFB and hence DET can't be
     * reported for DevFFA.
     * Therefore below condition is written to store the error for DevFFA */
    if (CaptureResult == DEM_E_NODATAAVAILABLE)
    {
      Result = DEM_E_NODATAAVAILABLE;
    }
#else
    (void)Dem_CaptureFF(
            IdxDevFFKind,
            &Dem_FFClass[DevFFClassIdx],
            EventId,
            DEM_EVENT_STATUS_FAILED,
            &FFDataDestination[EventRelatedDataSize->DevAFFSize],
            DevFFSize);
#endif
  }

  DBG_DEM_CAPTUREDEVFFS_EXIT(FFKind, IndividPartFFClass,
      EventId, EventStatus, FFDataDestination, DevFFSize);

  return Result;
}

/* !LINKSTO dsn.Dem.DevFF.IB.StoreDevFF,1 */
STATIC FUNC(void, DEM_CODE) Dem_StoreDevFFs(
  P2VAR(Dem_EntryDataType, AUTOMATIC, AUTOMATIC)      CapturedDataBuf,
  Dem_EventIdType                                     EventId,
  Dem_EventMemoryEntryPtrType                         EvMemEntryPtr,
  Dem_ExternalEntryDataBufferManagementType EventRelatedDataSize)
{
  uint8    IdxDevFF;
  uint8    IdxDevPrimaryMemFF = 0U;
  boolean  ReplaceableEntryFound = FALSE;
  uint8    IdxDevFFKind;
  const uint8 OriginIdx = DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U;

  DBG_DEM_STOREDEVFFS_ENTRY(CapturedDataBuf, EventId, EvMemEntryPtr);

  for (IdxDevFFKind = DEM_DEVFF_A;
       IdxDevFFKind <= DEM_DEVFF_B;
       ++IdxDevFFKind)
  {
    const uint8 SizeDevFFMem = Dem_SizeDevFFMem[IdxDevFFKind];
    Dem_SizeEntryDataType DevFFStartIndex = 0U;
    Dem_SizeEntryDataType DevFFSize = EventRelatedDataSize.DevAFFSize;

    /* for DevFFB update the values used to access the data buffer */
    if (IdxDevFFKind == DEM_DEVFF_B)
    {
      DevFFStartIndex = EventRelatedDataSize.DevAFFSize;
      DevFFSize = EventRelatedDataSize.DevBFFSize;
    }

    /* storing of development Freeze Frame */
    if (DevFFSize != 0U)
    {
      /* search for an empty place to store new development FF entry */
      for (IdxDevFF = 0U; IdxDevFF < SizeDevFFMem; IdxDevFF++)
      {
        if (Dem_DevFFEventId[IdxDevFFKind][IdxDevFF] == DEM_EVENT_ID_INVALID)
        {
          break;
        }
      }

      /* if there is not empty slot, displacement has to be checked */
      if (IdxDevFF == SizeDevFFMem)
      {
        Dem_EventMemoryEntryPtrType EvMemEntryToBeDispalcedPtr =
          (Dem_EventMemoryEntryPtrType)NULL_PTR;

        /* find event memory entry to replace */
        /* !LINKSTO VCC_DEM_006_Req125v1,1 */
        ReplaceableEntryFound =
          Dem_SearchForEntryToReplace(OriginIdx,
            EventId, IdxDevFFKind,
            &EvMemEntryToBeDispalcedPtr, &IdxDevPrimaryMemFF);

        if (ReplaceableEntryFound == TRUE)
        {
          /* saving the Index in Freeze Frame array of removed entry */
          IdxDevFF = EvMemEntryToBeDispalcedPtr->DevFFEntryIdx[IdxDevFFKind];

          /* discard the development Freeze Frame link */
          EvMemEntryToBeDispalcedPtr->DevFFEntryIdx[IdxDevFFKind] =
            SizeDevFFMem;
        }
      }

      /* if empty place is found or
       * replaceable entry in the event memory is found */
      if (IdxDevFF < SizeDevFFMem)
      {
        /* entry at free slot */
        Dem_DevFFEventId[IdxDevFFKind][IdxDevFF] = (Dem_EventIdType)EventId;

        TS_MemCpy(
          &Dem_DevFFData[IdxDevFFKind][IdxDevFF *
            DEM_DEV_FF_MAX_CLASS_SIZE(IdxDevFFKind)],
          &CapturedDataBuf[DevFFStartIndex],
          DevFFSize);

        EvMemEntryPtr->DevFFEntryIdx[IdxDevFFKind] = IdxDevFF;
      }
      /* else: event has Dev FF, but no Dev FF entry available and is
         already initialized in Dem_FindOrAllocateEventEntry */
    }
  }

  DBG_DEM_STOREDEVFFS_EXIT(CapturedDataBuf, EventId, EvMemEntryPtr);
}
#endif /* (DEM_DEV_FREEZE_FRAME_USED == STD_ON) */
#endif /* (DEM_NUM_FFSEGS > 0U) */

#if (DEM_NUM_OF_PIDS_IN_OBDFF > 0U)
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_CaptureOBDFreezeFrame(
  Dem_EventIdType                                          EventId,
  P2VAR(Dem_EntryDataType, AUTOMATIC, AUTOMATIC)           ObdDataDestination,
  P2VAR(Dem_SizeEntryDataType, AUTOMATIC, AUTOMATIC)       ObdFFSize)
{
  /* iterator for PIDs */
  uint8_least PidIterator;
  Dem_SizeEntryDataType StartByte = 0U;

  /* returned status of dataReadFunc */
  Std_ReturnType ReadFuncStatus = E_NOT_OK;

#if (DEM_DET_RUNTIME_CHECK == STD_ON)
  uint8 Result = E_OK;
#endif /* (DEM_DET_RUNTIME_CHECK == STD_ON) */

  DBG_DEM_CAPTUREOBDFREEZEFRAME_ENTRY(EventId, ObdDataDestination, ObdFFSize);

  /* loop over all entries (PIDs) in Dem_PidClass[DEM_NUM_OF_PIDS_IN_OBDFF] */
  /* Deviation TASKING-1 */
  for (PidIterator = 0U; PidIterator < DEM_NUM_OF_PIDS_IN_OBDFF; PidIterator++)
  {
    /* iterator for data elements */
    uint8_least PidDataElementIterator;

    /* get pointers to PIDClass array */
    P2CONST(Dem_PidClassType, AUTOMATIC, DEM_CONST) PidClass =
         &Dem_PidClass[PidIterator];

    /* loop over all data elements in PID */
    for (PidDataElementIterator = 0U;
         PidDataElementIterator < PidClass->NumSegDataElements;
         PidDataElementIterator++)
    {
      /* calculate Index of data element in OBDFFData[]
       * --> pos. of PID in FF + offset of data element in PID */
      const Dem_SizeEntryDataType ObdFFDataIdx =
        StartByte + PidClass->ObdFFPidDataElementOffset[PidDataElementIterator];
      const Dem_DataElementIdxType PidElementIdx =
        PidClass->DemPidDataElementIdx[PidDataElementIterator];
      const Dem_SizeEntryDataType DataElementSize =
        DEM_EXTERNAL_DATA_ELEMENT_SIZE(PidElementIdx);

      /* !LINKSTO dsn.Dem.OBD.Dem_CaptureOBDFreezeFrame.RetrieveDataElement,1 */
      ReadFuncStatus =
        Dem_ReadExternalDataElement(&ObdDataDestination[ObdFFDataIdx],
                                    PidElementIdx,
                                    EventId);

      /* check whether read data is valid according to SWS_Dem_00463 */
      if (ReadFuncStatus != E_OK)
      {
        Dem_SizeEntryDataType Index;

#if (DEM_DET_RUNTIME_CHECK == STD_ON)
        Result =  DEM_E_NODATAAVAILABLE;
#endif /* DEM_DET_RUNTIME_CHECK */

        /* fill FF segment with padding values */
        for (Index = 0U; Index < DataElementSize; Index++)
        {
          /* !LINKSTO dsn.Dem.OBD.Dem_CaptureOBDFreezeFrame.ReadDataElementResult,1 */
          ObdDataDestination[(ObdFFDataIdx + Index)] = DEM_DATA_PADDING_VALUE;
        }
      }
    }

    /* calculate start position Index of the PID */
    StartByte += (Dem_SizeEntryDataType)PidClass->Size;
  }

  *ObdFFSize = StartByte;
#if (DEM_DET_RUNTIME_CHECK == STD_ON)
  return Result;
#else
  return E_OK;
#endif

  DBG_DEM_CAPTUREOBDFREEZEFRAME_EXIT(Result, EventId, ObdDataDestination, ObdFFSize);
}
#endif

#if (DEM_OBD_CENTRALIZED_PID_REL_DISTANCE_HANDLING == STD_OFF)
#if (DEM_OBD_CENTRALIZED_PID21_HANDLING == STD_OFF)

STATIC FUNC(void, DEM_CODE) Dem_ResetDistanceTraveledWhileMILIsActivated(void)
{
  Dem_NvData.TicksTraveledWhileMILIsActivated = 0U;
  Dem_NvData.NrWUCsWhileMILInactive = 0U;
}
#endif

STATIC FUNC(void, DEM_CODE) Dem_ProcessDistanceRelatedPIDs(void)
{
  DBG_DEM_PROCESSDISTANCERELATEDPIDS_ENTER();

  Dem_MainFunctionOneSecondCounter++;

  /* calculate the value for PIDs-related distance traveled since
   * last DTC clear and/or since MIL switched ON.
   * prescaler used to reduce the amount of recomputation of distance,
   * set such that the distance be calculated only once a second. */
  if (Dem_MainFunctionOneSecondCounter == DEM_MAINCYCLE_TICKS_PER_SECOND)
  {
#if (DEM_OBD_CENTRALIZED_PID21_HANDLING == STD_OFF)
    const Dem_IndicatorStatusType MILCurrentStatus =
      Dem_InternalGetIndicatorStatus(DEM_MIL_ID, TRUE);
#endif
    /* !LINKSTO Dem.ReadExternalData.NoCriticalSection,1 */
    /* Call Dem_CalculateDeltaDistanceTravel() here, because
     * it reads external data elements and therefore must not
     * be called from within a critical section. */
    const uint32 DeltaDistanceTraveled = Dem_CalculateDeltaDistanceTravel();
    Dem_MainFunctionOneSecondCounter = 0U;

    /*
     * ENTER critical section to protect TicksTraveledWhileMILIsActivated and
     * NrWUCsWhileMILInactive
     *       call-context: Dem (Task)
     */
    DEM_ENTER_EXCLUSIVE_AREA();

#if (DEM_OBD_CENTRALIZED_PID21_HANDLING == STD_OFF)
    /* check if MIL status has changed from OFF to ON */
    if ((Dem_NvData.MILPrevStatusOnlyOnOffRelevance == DEM_INDICATOR_OFF) &&
        (MILCurrentStatus != DEM_INDICATOR_OFF))
    {
      /* !LINKSTO Dem.OBD.PID$21.DistanceTraveled.Reset.MILState-SwitchesOn,1 */
      Dem_ResetDistanceTraveledWhileMILIsActivated();
    }

    /* buffer the current MIL status to allow detecting any changes during next processing */
    Dem_NvData.MILPrevStatusOnlyOnOffRelevance = MILCurrentStatus;
#endif /* DEM_OBD_CENTRALIZED_PID21_HANDLING == STD_OFF */

    Dem_UpdateDistanceRelatedPIDs(DeltaDistanceTraveled);
    /*
     * LEAVE critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();

  }

  DBG_DEM_PROCESSDISTANCERELATEDPIDS_EXIT();
}

STATIC FUNC(void, DEM_CODE) Dem_UpdateDistanceRelatedPIDs(
  uint32 DeltaDistanceTraveled)
{
#if (DEM_OBD_CENTRALIZED_PID21_HANDLING == STD_OFF)
  /* !LINKSTO Dem.OBD.PID$21.DistanceTraveled.NoChange,1 */
  /* !LINKSTO Dem.OBD.PID$21.DistanceTraveled.IncrementCondition,1 */
  if (Dem_NvData.MILPrevStatusOnlyOnOffRelevance != DEM_INDICATOR_OFF)
  {
    /* addition of delta distance can be done without overflowing the counter
     * because the maximum distance traveled in ticks can fit in 28 bits */
    Dem_NvData.TicksTraveledWhileMILIsActivated += DeltaDistanceTraveled;

    /* !LINKSTO Dem.OBD.PID$21.DistanceTraveled.CounterOverflow,1 */
    if (Dem_NvData.TicksTraveledWhileMILIsActivated >
         DEM_MAXIMUM_DISTANCE_TRAVELED_IN_TICKS)
    {
      Dem_NvData.TicksTraveledWhileMILIsActivated =
        DEM_MAXIMUM_DISTANCE_TRAVELED_IN_TICKS;
    }
  }
#endif /* DEM_OBD_CENTRALIZED_PID21_HANDLING == STD_OFF */

#if (DEM_OBD_CENTRALIZED_PID31_HANDLING == STD_OFF)
  Dem_NvData.TicksTraveledSinceDTCsCleared += DeltaDistanceTraveled;

  if (Dem_NvData.TicksTraveledSinceDTCsCleared >
        DEM_MAXIMUM_DISTANCE_TRAVELED_IN_TICKS)
  {
    Dem_NvData.TicksTraveledSinceDTCsCleared =
      DEM_MAXIMUM_DISTANCE_TRAVELED_IN_TICKS;
  }
#endif
}

STATIC FUNC(uint32, DEM_CODE) Dem_CalculateDeltaDistanceTravel(void)
{
  uint32 DeltaDistance = 0U;

  /* local variables for getting the current values of PID0D and PID1F */
  uint8  Buffer[2];
  uint8  PID0D_Speed;
  uint16 PID1F_TimeSinceStart;
  Std_ReturnType DataPresent;

  /* stores the time elapsed in between two calculations of PID31 */
  uint16 DeltaTime = 0U;

  /* for distance traveled PIDs EventId is not used */
  DataPresent =
    Dem_ReadExternalDataElement(Buffer,
                                DEM_OBD_INDEX_PID1F,
                                DEM_EVENT_ID_INVALID);

  /* if data for PID1F is not present, values for traveled distance will not get updated */
  /* !LINKSTO Dem.OBD.DistanceTraveled.PID_1F_NotAvailable,1 */
  if (DataPresent == E_OK)
  {
    PID1F_TimeSinceStart = (uint16)((uint16)Buffer[0] << 8) + ((uint16)Buffer[1]);

    /* calculate delta. If the value received in this cycle is lower
     * than the value from the previous cycle, use
     * PID1F_TimeSinceStart for DeltaTime. This should normally not
     * occur. Otherwise the DeltaTime is calculated from the
     * difference of (current value - previous value). */
    if (PID1F_TimeSinceStart < Dem_LastTimeSinceEngineStart)
    {
      Dem_LastTimeSinceEngineStart = PID1F_TimeSinceStart;
      DeltaTime = PID1F_TimeSinceStart;
    }
    else
    {
      DeltaTime = PID1F_TimeSinceStart - Dem_LastTimeSinceEngineStart;
      Dem_LastTimeSinceEngineStart = PID1F_TimeSinceStart;
    }

    /* PID0D: speed value is only needed, when there is a DeltaTime
     * elapsed since last calculation. Otherwise, the values for
     * traveled distance will not be updated. */
    /* !LINKSTO Dem.OBD.DistanceTraveled.PID_0D_NotAvailable,1 */
    if (DeltaTime > 0U)
    {
      /* !LINKSTO Dem.ASR40.SWS_Dem_00346,1 */
      /* !LINKSTO Dem.SWS_Dem_01096,1 */
      /* PID0D. Read current value for vehicle speed from External Data Element */
      DataPresent =
        Dem_ReadExternalDataElement(Buffer,
                                    DEM_OBD_INDEX_PID0D,
                                    DEM_EVENT_ID_INVALID);

      if (DataPresent == E_OK)
      {
        PID0D_Speed = Buffer[0];

        /* PID0D_Speed == 255 is reserved for invalid values. Do the
         * calculation only for valid speed values. */
        if (PID0D_Speed < 255U)
        {
          DeltaDistance = (uint32)DeltaTime * PID0D_Speed;
        }
      }
    }
  }

  return DeltaDistance;
}
#endif /* DEM_OBD_CENTRALIZED_PID_REL_DISTANCE_HANDLING == STD_OFF */

#if ( (DEM_NUM_EDSEGS > 0U) && \
      (DEM_NUM_EXT_DATAELEMENTS > 0U) )
STATIC FUNC(void, DEM_CODE) Dem_StoreED(
  P2VAR(Dem_EntryDataType, AUTOMATIC, AUTOMATIC) CapturedDataBuf,
  Dem_EntryDataPtrType                           EDEntryData,
  P2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass,
  boolean                                        EntryExists)
{
  Dem_EDSegIdxType SegIdx;
  Dem_EDSegIdxType EDSegIdx;
  P2CONST(Dem_EDSegmentType, AUTOMATIC, DEM_CONST) EDSegment;
  Dem_DataElementOffsetType EDDataElemOffset;
  Dem_EDStartByteType EDStartByte;

  DBG_DEM_STOREED_ENTRY(CapturedDataBuf, EDEntryData, EDClass, EntryExists);

  /* get data values to all numbers of the extended data class */
  for (SegIdx = 0U; SegIdx < EDClass->NumEDSegs; ++SegIdx)
  {
    EDSegIdx = EDClass->EDSegIdx[SegIdx];
    EDSegment = &Dem_EDSegment[EDSegIdx];
    EDStartByte = EDClass->StartByte[SegIdx];

    /* !LINKSTO Dem.SWS_Dem_00815,1 */
    /* !LINKSTO Dem.SWS_Dem_00816,1 */
    /* check if ED record update is enabled */
    if ((EntryExists == FALSE) || (EDSegment->Update == TRUE))
    {
      Dem_NumDataElementsType DataElementIndex;
      Dem_DataElementIdxType DataElementIdx;

      /* add all data elements of the ED segment */
      for (DataElementIndex = 0U;
           DataElementIndex < EDSegment->NumEDDataElements; ++DataElementIndex)
      {
        DataElementIdx = EDSegment->DataElementIdx[DataElementIndex];

#if (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON)
        if (DataElementIdx < DEM_NUM_EXT_DATAELEMENTS)
#endif
        {
#if (DEM_NUM_CAPTURE_ON_RETRIEVAL_DATAELEMENTS > 0U)
          /* !LINKSTO Dem.DataElementCaptureOnRetrieval.MemoryStorage,1 */
          if(Dem_DataElement[DataElementIdx].CaptureOnRetrieval == FALSE)
#endif
          {
            const Dem_SizeEntryDataType DataElementSize =
              DEM_EXTERNAL_DATA_ELEMENT_SIZE(DataElementIdx);

            EDDataElemOffset = EDSegment->DataElementOffset[DataElementIndex];
            /* write content into the destination buffer (event memory) */
            TS_MemCpy(&EDEntryData[EDStartByte + EDDataElemOffset],
                      &CapturedDataBuf[EDStartByte + EDDataElemOffset], DataElementSize);
            }
         }
       }
    }
  }

  DBG_DEM_STOREED_EXIT(CapturedDataBuf, EDEntryData, EDClass, EntryExists);
}

STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_CaptureED(
  Dem_EntryDataPtrType                                   EDataDestination,
  boolean                                                EntryExists,
  Dem_EventIdType                                        EventId,
  P2VAR(Dem_SizeEntryDataType, AUTOMATIC, AUTOMATIC)     EDSize,
  P2VAR(boolean, AUTOMATIC, AUTOMATIC)                   ReportEDUpdate)
{
  Dem_EDSegIdxType SegIdx;
  Dem_EDSegIdxType EDSegIdx;
  Dem_SizeEntryDataType StopIndex = 0U;
  Dem_SizeEntryDataType StartIndex = 0U;
  Std_ReturnType Result = E_OK;
  P2CONST(Dem_EDSegmentType, AUTOMATIC, DEM_CONST) EDSegment;
  Dem_DataElementOffsetType EDDataElemOffset;
  Dem_EDStartByteType EDStartByte;
  CONSTP2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass =
    &Dem_EDClass[Dem_GbiEDClassIdx(EventId)];

  DBG_DEM_CAPTURE_ENTRY(EDataDestination, EntryExists,
    EventId, EDSize, ReportEDUpdate);

  /* get data values to all numbers of the extended data class */
  for (SegIdx = 0U; SegIdx < EDClass->NumEDSegs; ++SegIdx)
  {
    EDSegIdx = EDClass->EDSegIdx[SegIdx];
    EDSegment = &Dem_EDSegment[EDSegIdx];
    EDStartByte = EDClass->StartByte[SegIdx];

    /* !LINKSTO Dem.SWS_Dem_00815,1 */
    /* !LINKSTO Dem.SWS_Dem_00816,1 */
    /* check if ED record update is enabled */
    if ((EntryExists == FALSE) || (EDSegment->Update == TRUE))
    {
      Std_ReturnType DataPresent = E_NOT_OK;
      Dem_NumDataElementsType DataElementIndex;
      Dem_DataElementIdxType DataElementIdx;

      /* add all data elements of the ED segment */
      for (DataElementIndex = 0U;
           DataElementIndex < EDSegment->NumEDDataElements; ++DataElementIndex)
      {
        DataElementIdx = EDSegment->DataElementIdx[DataElementIndex];

#if (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON)
        if (DataElementIdx < DEM_NUM_EXT_DATAELEMENTS)
#endif
        {
#if (DEM_NUM_CAPTURE_ON_RETRIEVAL_DATAELEMENTS > 0U)
          /* !LINKSTO Dem.DataElementCaptureOnRetrieval.MemoryStorage,1 */
          if(Dem_DataElement[DataElementIdx].CaptureOnRetrieval == FALSE)
#endif
          {
            const Dem_SizeEntryDataType DataElementSize =
              DEM_EXTERNAL_DATA_ELEMENT_SIZE(DataElementIdx);

            EDDataElemOffset = EDSegment->DataElementOffset[DataElementIndex];

            StartIndex = (Dem_SizeEntryDataType)EDStartByte + EDDataElemOffset;
            StopIndex = StartIndex + DataElementSize;

            DataPresent =
              Dem_ReadExternalDataElement(&EDataDestination[StartIndex],
                                          DataElementIdx,
                                          EventId);

            if (DataPresent != E_OK)
            {
              Dem_SizeEntryDataType Index;

              /* fill data element with padding values */
              for (Index = StartIndex; Index < StopIndex; ++Index)
              {
                EDataDestination[Index] = DEM_DATA_PADDING_VALUE;
              }

  #if (DEM_DET_RUNTIME_CHECK == STD_ON)
              /* data for EDS cannot be read, return DEM_E_NODATAAVAILABLE;
               * this return value is used to report a DET error outside the
               * exclusive area opened in Dem_ProcessEvent() */
              Result = DEM_E_NODATAAVAILABLE;
  #endif
            }
          }
        }
      }
      *ReportEDUpdate = TRUE;
    }
  }
  *EDSize = StopIndex;

  DBG_DEM_CAPTURE_EXIT(Result, EDataDestination, EntryExists,
    EventId, EDSize, ReportEDUpdate);
  return Result;
}
#endif /* (DEM_NUM_EDSEGS > 0U) && (DEM_NUM_EXT_DATAELEMENTS > 0U) */

#if (DEM_NUM_EXT_DATAELEMENTS > 0U)
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_ReadExtDataElementUint8(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC)                 DestBuffer,
  Dem_DataElementIdxType                             DataElementIndex,
  Dem_EventIdType                                    EventId)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_READEXTDATAELEMENTUINT8_ENTRY(
    DestBuffer, DataElementIndex, EventId);

#if (DEM_DATA_ELEMENT_INTERFACE_WITH_EVENTID_SUPPORT == STD_OFF)
  TS_PARAM_UNUSED(EventId);
#endif

#if (DEM_DATA_ELEMENT_INTERFACE_WITH_EVENTID_SUPPORT == STD_ON)
  if( Dem_DataElement[DataElementIndex].EventIdSupport == TRUE)
  {
    /* invoke RTE read function with EventId parameter for reading the DataElement */
    Result =
      Dem_DataElement[DataElementIndex].ReadFunction.
      Rte_Read_DataElement_uint8_WithEventId(DestBuffer, EventId);
  }
  else
#endif /* DEM_DATA_ELEMENT_INTERFACE_WITH_EVENTID_SUPPORT == STD_ON */
  {
    /* invoke Rte read function to copy the data into the buffer */
    Result =
      Dem_DataElement[DataElementIndex].ReadFunction.
      Rte_Read_DataElement_uint8(DestBuffer);
  }

  DBG_DEM_READEXTDATAELEMENTUINT8_EXIT(
    Result, DataElementIndex, DestBuffer, EventId);
  return Result;
}

#if (DEM_INCLUDE_RTE == STD_ON)
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_ReadExtDataElementUint16(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC)                 DestBuffer,
  Dem_DataElementIdxType                             DataElementIndex,
  Dem_EventIdType                                    EventId)
{
  Std_ReturnType Result = E_NOT_OK;
  uint16 Data[DEM_MAX_SIZE_EXT_DE];

  DBG_DEM_READEXTDATAELEMENTUINT16_ENTRY(
    DestBuffer, DataElementIndex, EventId);

#if (DEM_DATA_ELEMENT_INTERFACE_WITH_EVENTID_SUPPORT == STD_OFF)
  TS_PARAM_UNUSED(EventId);
#endif

#if (DEM_DATA_ELEMENT_INTERFACE_WITH_EVENTID_SUPPORT == STD_ON)
  if( Dem_DataElement[DataElementIndex].EventIdSupport == TRUE)
  {
    /* invoke RTE read function with EventId parameter for reading the DataElement */
    Result =
      Dem_DataElement[DataElementIndex].ReadFunction.
      Rte_Read_DataElement_uint16_WithEventId(Data, EventId);
  }
  else
#endif /* DEM_DATA_ELEMENT_INTERFACE_WITH_EVENTID_SUPPORT == STD_ON */
  {
    /* invoke Rte read function to get data value */
    Result =
      Dem_DataElement[DataElementIndex].ReadFunction.Rte_Read_DataElement_uint16(Data);
  }

  /* if Rte read function was executed successfully, the data is copied in
   * the buffer */
  if ( E_OK == Result )
  {
    uint8 NumberOfArrayElements =
      DEM_EXTERNAL_DATA_ELEMENT_SIZE(DataElementIndex) / 2U;
    uint8_least Idx;

#if (DEM_SR_SUPPORT == STD_ON)
    /* check if an endiness conversion is needed */
    if (TRUE == DEM_IS_SR_ENDIANNESS_CONVERSION_REQUIRED(
            Dem_DataElement[DataElementIndex].Endianness))
    {
      if ( NumberOfArrayElements != 0U )
      {
        /* copy the elements that have the size of DataType (2 bytes) */
        for (Idx = 0U; Idx < NumberOfArrayElements; Idx++)
        {
          DestBuffer[Idx * 2U]        = (uint8)(Data[Idx] >> 8U);
          DestBuffer[(Idx * 2U) + 1U] = (uint8) Data[Idx];
        }
      }
      else
      {
        /* copy the bytes from SR buffer */
        DestBuffer[0U] = (uint8)(Data[0U] >> 8U);
      }
    }
    else
#endif /* DEM_SR_SUPPORT == STD_ON */
    {
      if ( NumberOfArrayElements != 0U )
      {
        /* copy the elements that have the size of DataType (2 bytes) */
        for (Idx = 0U; Idx < NumberOfArrayElements; Idx++)
        {
          DestBuffer[Idx * 2U]        = (uint8) Data[Idx];
          DestBuffer[(Idx * 2U) + 1U] = (uint8)(Data[Idx] >> 8U);
        }
      }
      else
      {
        /* copy the bytes from buffer */
        DestBuffer[0U] = (uint8)Data[0U];
      }
    }
  }

  DBG_DEM_READEXTDATAELEMENTUINT16_EXIT(
    Result, DataElementIndex, DestBuffer, EventId);
  return Result;
}

STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_ReadExtDataElementUint32(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC)                 DestBuffer,
  Dem_DataElementIdxType                             DataElementIndex,
  Dem_EventIdType                                    EventId)
{
  Std_ReturnType Result = E_NOT_OK;
  uint32 Data[DEM_MAX_SIZE_EXT_DE];

  DBG_DEM_READEXTDATAELEMENTUINT32_ENTRY(
    DestBuffer, DataElementIndex, EventId);

#if (DEM_DATA_ELEMENT_INTERFACE_WITH_EVENTID_SUPPORT == STD_OFF)
  TS_PARAM_UNUSED(EventId);
#endif

#if (DEM_DATA_ELEMENT_INTERFACE_WITH_EVENTID_SUPPORT == STD_ON)
  if( Dem_DataElement[DataElementIndex].EventIdSupport == TRUE)
  {
    /* invoke RTE read function with EventId parameter for reading the DataElement */
    Result =
      Dem_DataElement[DataElementIndex].ReadFunction.
      Rte_Read_DataElement_uint32_WithEventId(Data, EventId);
  }
  else
#endif /* DEM_DATA_ELEMENT_INTERFACE_WITH_EVENTID_SUPPORT == STD_ON */
  {
    /* invoke Rte read function to get data value */
    Result =
      Dem_DataElement[DataElementIndex].ReadFunction.Rte_Read_DataElement_uint32(Data);
  }

  /* if Rte read function was executed successfully, the data is copied in
   * the buffer */
  if ( E_OK == Result )
  {
    uint8 RemainingBytes = DEM_EXTERNAL_DATA_ELEMENT_SIZE(DataElementIndex) % 4U;
    uint8 NumberOfArrayElements =
      DEM_EXTERNAL_DATA_ELEMENT_SIZE(DataElementIndex) / 4U;
    uint8_least Idx;

#if (DEM_SR_SUPPORT == STD_ON)
    /* check if an endiness conversion is needed */
    if (TRUE == DEM_IS_SR_ENDIANNESS_CONVERSION_REQUIRED(
            Dem_DataElement[DataElementIndex].Endianness))
    {
      if ( NumberOfArrayElements != 0U )
      {
        /* copy the elements that have the size of DataType (4 bytes) */
        for (Idx = 0U; Idx < NumberOfArrayElements; Idx++)
        {
          DestBuffer[Idx * 4U]        = (uint8)( Data[Idx] >> 24U );
          DestBuffer[(Idx * 4U) + 1U] = (uint8)( Data[Idx] >> 16U );
          DestBuffer[(Idx * 4U) + 2U] = (uint8)( Data[Idx] >> 8U );
          DestBuffer[(Idx * 4U) + 3U] = (uint8)( Data[Idx] );
        }
      }
      else
      {
        for (Idx = 0U; Idx < RemainingBytes; Idx++)
        {
          DestBuffer[Idx] =
            (uint8)( Data[0U] >> ((3U - Idx) * 8U) );
        }
      }
    }
    else
#endif /* DEM_SR_SUPPORT == STD_ON */
    {
      if ( NumberOfArrayElements != 0U )
      {
        /* copy the elements that have the size of DataType (4 bytes) */
        for (Idx = 0U; Idx < NumberOfArrayElements; Idx++)
        {
          DestBuffer[Idx * 4U]        = (uint8)( Data[Idx] );
          DestBuffer[(Idx * 4U) + 1U] = (uint8)( Data[Idx] >> 8U );
          DestBuffer[(Idx * 4U) + 2U] = (uint8)( Data[Idx] >> 16U );
          DestBuffer[(Idx * 4U) + 3U] = (uint8)( Data[Idx] >> 24U );
        }
      }
      else
      {
        /* copy the bytes from buffer */
        for (Idx = 0U; Idx < RemainingBytes; Idx++)
        {
          DestBuffer[Idx] =
            (uint8)( Data[0U] >> (Idx * 8U) );
        }
      }
    }
  }

  DBG_DEM_READEXTDATAELEMENTUINT32_EXIT(
    Result, DataElementIndex, DestBuffer, EventId);
  return Result;
}
#endif /* #if (DEM_INCLUDE_RTE == STD_ON) */

#if (DEM_DEFAULT_ASR_SERVICE_API == DEM_SERVICE_API_ASR2011)
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_ReadExtDataElementSint8(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC)                 DestBuffer,
  Dem_DataElementIdxType                             DataElementIndex,
  Dem_EventIdType                                    EventId)
{
  Std_ReturnType Result = E_NOT_OK;
  sint8 Data[DEM_MAX_SIZE_EXT_DE];
  uint8 NumberOfArrayElements =
      DEM_EXTERNAL_DATA_ELEMENT_SIZE(DataElementIndex);
  uint8_least Idx;

  DBG_DEM_READEXTDATAELEMENTSINT8_ENTRY(
    DestBuffer, DataElementIndex, EventId);

#if (DEM_DATA_ELEMENT_INTERFACE_WITH_EVENTID_SUPPORT == STD_OFF)
  TS_PARAM_UNUSED(EventId);
#endif

#if (DEM_DATA_ELEMENT_INTERFACE_WITH_EVENTID_SUPPORT == STD_ON)
  if( Dem_DataElement[DataElementIndex].EventIdSupport == TRUE)
  {
    /* invoke RTE read function with EventId parameter for reading the DataElement */
    Result =
      Dem_DataElement[DataElementIndex].ReadFunction.
      Rte_Read_DataElement_sint8_WithEventId(Data, EventId);
  }
  else
#endif /* DEM_DATA_ELEMENT_INTERFACE_WITH_EVENTID_SUPPORT == STD_ON */
  {
   /* invoke Rte read function to copy the data into the buffer */
   Result =
     Dem_DataElement[DataElementIndex].ReadFunction.
     Rte_Read_DataElement_sint8(Data);
  }

  /* if Rte read function was executed successfully, the data is copied in
   * the buffer */
  if ( E_OK == Result )
  {
    for (Idx = 0U; Idx < NumberOfArrayElements; Idx++)
    {
      DestBuffer[Idx] = (uint8)Data[Idx];
    }
  }

  DBG_DEM_READEXTDATAELEMENTSINT8_EXIT(
    Result, DataElementIndex, DestBuffer, EventId);
  return Result;
}

STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_ReadExtDataElementSint16(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC)                 DestBuffer,
  Dem_DataElementIdxType                             DataElementIndex,
  Dem_EventIdType                                    EventId)
{
  Std_ReturnType Result = E_NOT_OK;
  sint16 Data[DEM_MAX_SIZE_EXT_DE];

  DBG_DEM_READEXTDATAELEMENTSINT16_ENTRY(
    DestBuffer, DataElementIndex, EventId);

#if (DEM_DATA_ELEMENT_INTERFACE_WITH_EVENTID_SUPPORT == STD_OFF)
  TS_PARAM_UNUSED(EventId);
#endif

#if (DEM_DATA_ELEMENT_INTERFACE_WITH_EVENTID_SUPPORT == STD_ON)
  if( Dem_DataElement[DataElementIndex].EventIdSupport == TRUE)
  {
    /* invoke RTE read function with EventId parameter for reading the DataElement */
    Result =
      Dem_DataElement[DataElementIndex].ReadFunction.
      Rte_Read_DataElement_sint16_WithEventId(Data, EventId);
  }
  else
#endif /* DEM_DATA_ELEMENT_INTERFACE_WITH_EVENTID_SUPPORT == STD_ON */
  {
    /* invoke Rte read function to get data value */
    Result =
      Dem_DataElement[DataElementIndex].ReadFunction.Rte_Read_DataElement_sint16(Data);
  }

  /* if Rte read function was executed successfully, the data is copied in
   * the buffer */
  if ( E_OK == Result )
  {
    uint8 NumberOfArrayElements =
      DEM_EXTERNAL_DATA_ELEMENT_SIZE(DataElementIndex) / 2U;
    uint8_least Idx;
    uint16 Data_unsigned[DEM_MAX_SIZE_EXT_DE];

    /* copy the elements that have the size of DataType (2 bytes) */
    for (Idx = 0U; Idx < NumberOfArrayElements; Idx++)
    {
      Data_unsigned[Idx]          = (uint16)Data[Idx];
      DestBuffer[Idx * 2U]        = (uint8) Data_unsigned[Idx];
      DestBuffer[(Idx * 2U) + 1U] = (uint8)(Data_unsigned[Idx] >> 8U);
    }
  }

  DBG_DEM_READEXTDATAELEMENTSINT16_EXIT(
    Result, DataElementIndex, DestBuffer, EventId);
  return Result;
}

STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_ReadExtDataElementSint32(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC)                 DestBuffer,
  Dem_DataElementIdxType                             DataElementIndex,
  Dem_EventIdType                                    EventId)
{
  Std_ReturnType Result = E_NOT_OK;
  sint32 Data[DEM_MAX_SIZE_EXT_DE];

  DBG_DEM_READEXTDATAELEMENTSINT32_ENTRY(
    DestBuffer, DataElementIndex, EventId);

#if (DEM_DATA_ELEMENT_INTERFACE_WITH_EVENTID_SUPPORT == STD_OFF)
  TS_PARAM_UNUSED(EventId);
#endif

#if (DEM_DATA_ELEMENT_INTERFACE_WITH_EVENTID_SUPPORT == STD_ON)
  if( Dem_DataElement[DataElementIndex].EventIdSupport == TRUE)
  {
    /* invoke RTE read function with EventId parameter for reading the DataElement */
    Result =
      Dem_DataElement[DataElementIndex].ReadFunction.
      Rte_Read_DataElement_sint32_WithEventId(Data, EventId);
  }
  else
#endif /* DEM_DATA_ELEMENT_INTERFACE_WITH_EVENTID_SUPPORT == STD_ON */
  {
    /* invoke Rte read function to get data value */
    Result =
      Dem_DataElement[DataElementIndex].ReadFunction.Rte_Read_DataElement_sint32(Data);
  }

  /* if Rte read function was executed successfully, the data is copied in
   * the buffer */
  if ( E_OK == Result )
  {
    uint8 NumberOfArrayElements =
      DEM_EXTERNAL_DATA_ELEMENT_SIZE(DataElementIndex) / 4U;
    uint8_least Idx;
    uint32 Data_unsigned[DEM_MAX_SIZE_EXT_DE];

    /* copy the elements that have the size of DataType (4 bytes) */
    for (Idx = 0U; Idx < NumberOfArrayElements; Idx++)
    {
      Data_unsigned[Idx]          = (uint32)Data[Idx];
      DestBuffer[Idx * 4U]        = (uint8)( Data_unsigned[Idx] );
      DestBuffer[(Idx * 4U) + 1U] = (uint8)( Data_unsigned[Idx] >> 8U );
      DestBuffer[(Idx * 4U) + 2U] = (uint8)( Data_unsigned[Idx] >> 16U );
      DestBuffer[(Idx * 4U) + 3U] = (uint8)( Data_unsigned[Idx] >> 24U );
    }
  }

  DBG_DEM_READEXTDATAELEMENTSINT32_EXIT(
    Result, DataElementIndex, DestBuffer, EventId);
  return Result;
}

STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_ReadExtDataElementFloat32(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC)                 DestBuffer,
  Dem_DataElementIdxType                             DataElementIndex,
  Dem_EventIdType                                    EventId)
{
  Std_ReturnType Result = E_NOT_OK;
  float32 Data[DEM_MAX_SIZE_EXT_DE];

  DBG_DEM_READEXTDATAELEMENTFLOAT32_ENTRY(
    DestBuffer, DataElementIndex, EventId);

#if (DEM_DATA_ELEMENT_INTERFACE_WITH_EVENTID_SUPPORT == STD_OFF)
  TS_PARAM_UNUSED(EventId);
#endif

#if (DEM_DATA_ELEMENT_INTERFACE_WITH_EVENTID_SUPPORT == STD_ON)
  if( Dem_DataElement[DataElementIndex].EventIdSupport == TRUE)
  {
    /* invoke RTE read function with EventId parameter for reading the DataElement */
    Result =
      Dem_DataElement[DataElementIndex].ReadFunction.
      Rte_Read_DataElement_float32_WithEventId(Data, EventId);
  }
  else
#endif /* DEM_DATA_ELEMENT_INTERFACE_WITH_EVENTID_SUPPORT == STD_ON */
  {
    /* invoke Rte read function to get data value */
    Result =
      Dem_DataElement[DataElementIndex].ReadFunction.
      Rte_Read_DataElement_float32(Data);
  }

  /* if Rte read function was executed successfully, the data is copied in
   * the buffer */
  if ( E_OK == Result )
  {
    uint8 NumberOfArrayElements =
      DEM_EXTERNAL_DATA_ELEMENT_SIZE(DataElementIndex) / 4U;
    uint8_least Idx;
    /* uint32 pointer to store the float array  */
    /* Deviation MISRAC2012-3 */
    uint32 *DataByte_uint32 = (uint32 *)Data;

    /* copy the elements that have the size of DataType (4 bytes) */
    for (Idx = 0U; Idx < NumberOfArrayElements; Idx++)
    {
      DestBuffer[Idx * 4U]        = (uint8)( DataByte_uint32[Idx] );
      DestBuffer[(Idx * 4U) + 1U] = (uint8)( DataByte_uint32[Idx] >> 8U );
      DestBuffer[(Idx * 4U) + 2U] = (uint8)( DataByte_uint32[Idx] >> 16U );
      DestBuffer[(Idx * 4U) + 3U] = (uint8)( DataByte_uint32[Idx] >> 24U );
    }
  }

  DBG_DEM_READEXTDATAELEMENTFLOAT32_EXIT(
    Result, DataElementIndex, DestBuffer, EventId);
  return Result;
}
#endif /* #if (DEM_DEFAULT_ASR_SERVICE_API == DEM_SERVICE_API_ASR2011) */


FUNC(Std_ReturnType, DEM_CODE) Dem_ReadExternalDataElement(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC)                 DestBuffer,
  Dem_DataElementIdxType                             DataElementIndex,
  Dem_EventIdType                                    EventId)
{
  Std_ReturnType Result = E_NOT_OK;
  const Dem_DataElementDataTypeType DataType =
    DEM_DATA_ELEMENT_DATATYPE(Dem_DataElement[DataElementIndex].TriggerPointAndDataType);

  DBG_DEM_READEXTERNALDATAELEMENT_ENTRY(
    DestBuffer, DataElementIndex, EventId);

#if (DEM_DATA_ELEMENT_INTERFACE_WITH_EVENTID_SUPPORT == STD_OFF)
  TS_PARAM_UNUSED(EventId);
#endif

  /* select the Callback type and copy data into Buffer */
  switch (DataType)
  {
    case DEM_READ_DATA_DATA_TYPE_BOOLEAN:
    case DEM_READ_DATA_DATA_TYPE_UINT8:
    case DEM_READ_DATA_DATA_TYPE_UINT8_N:
    {
      Result = Dem_ReadExtDataElementUint8(DestBuffer, DataElementIndex, EventId);
      break;
    }

#if (DEM_INCLUDE_RTE == STD_ON)
    case DEM_READ_DATA_DATA_TYPE_UINT16:
    case DEM_READ_DATA_DATA_TYPE_UINT16_N:
    {
      Result = Dem_ReadExtDataElementUint16(DestBuffer, DataElementIndex, EventId);
      break;
    }

    case DEM_READ_DATA_DATA_TYPE_UINT32:
    case DEM_READ_DATA_DATA_TYPE_UINT32_N:
    {
      Result = Dem_ReadExtDataElementUint32(DestBuffer, DataElementIndex, EventId);
      break;
    }
#endif

#if (DEM_DEFAULT_ASR_SERVICE_API == DEM_SERVICE_API_ASR2011)
    case DEM_READ_DATA_DATA_TYPE_SINT8:
    case DEM_READ_DATA_DATA_TYPE_SINT8_N:
    {
      Result = Dem_ReadExtDataElementSint8(DestBuffer, DataElementIndex, EventId);
      break;
    }

    case DEM_READ_DATA_DATA_TYPE_SINT16:
    case DEM_READ_DATA_DATA_TYPE_SINT16_N:
    {
      Result = Dem_ReadExtDataElementSint16(DestBuffer, DataElementIndex, EventId);
      break;
    }

    case DEM_READ_DATA_DATA_TYPE_SINT32:
    case DEM_READ_DATA_DATA_TYPE_SINT32_N:
    {
      Result = Dem_ReadExtDataElementSint32(DestBuffer, DataElementIndex, EventId);
      break;
    }

    case DEM_READ_DATA_DATA_TYPE_FLOAT32:
    case DEM_READ_DATA_DATA_TYPE_FLOAT32_N:
    {
      Result = Dem_ReadExtDataElementFloat32(DestBuffer, DataElementIndex, EventId);
      break;
    }
#endif

    /* CHECK: NOPARSE */
    default: /* should never be reached */
      DEM_UNREACHABLE_CODE_ASSERT(DEM_INTERNAL_API_ID);
      break;
    /* CHECK: PARSE */
  } /* data type */

  DBG_DEM_READEXTERNALDATAELEMENT_EXIT(
    Result, DataElementIndex, DestBuffer, EventId);
  return Result;
}
#endif /* (DEM_NUM_EXT_DATAELEMENTS > 0U) */

STATIC FUNC(boolean, DEM_CODE) Dem_SearchForEmptyEntry(
  uint8                                                  OriginIdx,
  P2VAR(Dem_EventMemoryEntryPtrType, AUTOMATIC, DEM_VAR) FoundEntry,
  P2VAR(Dem_SizeEvMemEntryType, AUTOMATIC, AUTOMATIC)    FoundEntryIdx )
{
  boolean Result = FALSE;

  const Dem_SizeEvMemEntryType SizeEventMem = Dem_SizeEventMem[OriginIdx];

  Dem_SizeEvMemEntryType EntryIdx;
  Dem_EventMemoryEntryPtrType EvMemEntry = Dem_EventMem[OriginIdx];

  DBG_DEM_SEARCHFOREMPTYENTRY_ENTRY(OriginIdx, FoundEntry, FoundEntryIdx);

  /* search for empty entry in event memory */
  /* stop if all entries checked or the first empty entry was found */
  for (EntryIdx = 0U; EntryIdx < SizeEventMem; ++EntryIdx)
  {
    if (EvMemEntry[EntryIdx].EventId == DEM_EVENT_ID_INVALID)
    {
      break;
    }
  }

  /* empty entry is found */
  if (EntryIdx < SizeEventMem)
  {
    /* mark empty entry */
    *FoundEntryIdx = EntryIdx;
    *FoundEntry = &EvMemEntry[EntryIdx];
    Result = TRUE;
  }

  DBG_DEM_SEARCHFOREMPTYENTRY_EXIT(
    Result, OriginIdx, FoundEntry, FoundEntryIdx);
  return Result;
}
/* !LINKSTO Dem.SWS_Dem_00400,1 */
#if (DEM_USE_EVENT_DISPLACEMENT == STD_ON)
STATIC FUNC(boolean, DEM_CODE) Dem_SearchForEntryToReplace(
  uint8                                                    OriginIdx,
  Dem_EventIdType                                          NewEventId,
  Dem_FFKindType                                           FFKind,
  P2VAR(Dem_EventMemoryEntryPtrType, AUTOMATIC, AUTOMATIC) FoundEntry,
  P2VAR(Dem_SizeEvMemEntryType, AUTOMATIC, AUTOMATIC)      FoundEntryIdx)
{
  boolean Result = FALSE;
  Dem_EventDisplacementCriterionMatchType CriterionMatch = DEM_CRITERION_MATCH_NONE;
  const Dem_SizeEvMemEntryType SizeEventMem = Dem_SizeEventMem[OriginIdx];
  const Dem_EventMemoryEntryPtrType EvMemEntry = Dem_EventMem[OriginIdx];

  Dem_SizeEvMemEntryType EntryIdx;
  Dem_SizeEvMemEntryType BestEntryIdx = 0U;

  const Dem_PriorityType NewEvtPrioVal = Dem_GbiPriority(NewEventId);

  /* initialize with highest allowed priority (smallest allowed value) */
  Dem_PriorityType BestPrioVal = NewEvtPrioVal;

  DBG_DEM_SEARCHFORENTRYTOREPLACE_ENTRY(
    OriginIdx, NewEventId, FFKind, FoundEntry, FoundEntryIdx);

#if (DEM_DEV_FREEZE_FRAME_USED == STD_OFF)
  TS_PARAM_UNUSED(FFKind);
#endif

  /* refer to figure 25 "Combined displacement criteria processing"
   * in SWS for the displacement algorithm of combined criteria */
  for (EntryIdx = 0U; EntryIdx < SizeEventMem; ++EntryIdx)
  {
#if (DEM_DEV_FREEZE_FRAME_USED == STD_ON)
    uint8 CurrentDevFF_A = EvMemEntry[EntryIdx].DevFFEntryIdx[DEM_DEVFF_A];
    uint8 CurrentDevFF_B = EvMemEntry[EntryIdx].DevFFEntryIdx[DEM_DEVFF_B];
#endif
    const Dem_EventIdType CurrentEventId = EvMemEntry[EntryIdx].EventId;
    const Dem_PriorityType CurrentEvtPrioVal = Dem_GbiPriority(CurrentEventId);

#if (DEM_DEV_FREEZE_FRAME_USED == STD_ON)
    if ((FFKind == DEM_REGULAR_FF) ||
        ((FFKind == DEM_DEVFF_A) &&
         (CurrentDevFF_A != DEM_MAX_NUMBER_DEVFFA_ENTRY)) ||
        ((FFKind == DEM_DEVFF_B) &&
          (CurrentDevFF_B != DEM_MAX_NUMBER_DEVFFB_ENTRY))
       )
#endif
    {
#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
      /* prefer aged events to replace at first */
      if ( DEM_IS_ANY_BIT_SET(EvMemEntry[EntryIdx].SI30, DEM_SI30_STATUS_AGEDDTC) )
      {
        BestEntryIdx = EntryIdx;
        CriterionMatch = DEM_CRITERION_MATCH_AGED;
        break;
      }
#endif
      /* !LINKSTO Dem.ASR43.SWS_Dem_00401,1
      */
      /* !LINKSTO VCC_DEM_007_Req194v1,1
      */
      /* !LINKSTO dsn.Dem.Displacement.Light,1
      */
#if (DEM_EVENT_DISPLACEMENT_STRATEGY == DEM_DISPLACEMENT_PRIO_OCC)
      if ( (CurrentEventId != DEM_EVENT_ID_INVALID) &&
           (CurrentEvtPrioVal >= BestPrioVal) )
      {
        if (CurrentEvtPrioVal > NewEvtPrioVal)
        {
          /* entry with lower priority (larger value) than new event and no
           * higher priority than best entry */
          if ( (CurrentEvtPrioVal > BestPrioVal)
                /* if entry has same priority as best entry
                 * choose first one that has highest OCC2 value */
                || ( (CurrentEvtPrioVal == BestPrioVal) &&
                     DEM_IS_EVENT_OLDER(EntryIdx, BestEntryIdx) )
              )
          {
            /* select entry with lower priority for displacement */
            BestPrioVal  = CurrentEvtPrioVal;
            BestEntryIdx = EntryIdx;
            CriterionMatch = DEM_CRITERION_MATCH_PRIO;
          }
        }
#if (DEM_EVENT_DISPLACEMENT_CRITERION_TNCTOC == STD_ON)
        /* !LINKSTO SWS_Dem_00692_refine,1 */
        else
        {
          /* entry with same priority as new event and same priority
           * as best entry i.e. no entry with lower priority found yet */
          if ( DEM_IS_EV_ST_BIT_TNCTOC_SET(CurrentEventId) &&
               ( (CriterionMatch > DEM_CRITERION_MATCH_TNCTOC_STATUS) ||
                ((CriterionMatch == DEM_CRITERION_MATCH_TNCTOC_STATUS) &&
                 DEM_IS_EVENT_OLDER(EntryIdx, BestEntryIdx)) )
             )
          {
#if (DEM_OBD_EVENT_DISPLACEMENT == STD_ON)
            /* !LINKSTO SWS_Dem_00695_refine,1 */
            /* consider entry with same priority only if not protected */
            if (Dem_IsDisplaceOBDEventEntryAllowed(CurrentEventId) == TRUE)
#endif
            {
              /* select the oldest entry of events with status bit TNCTOC==1 */
              BestEntryIdx = EntryIdx;
              CriterionMatch = DEM_CRITERION_MATCH_TNCTOC_STATUS;
            }
          }
        }
#endif /* DEM_EVENT_DISPLACEMENT_CRITERION_TNCTOC == STD_ON */
      }
#else
      /* !LINKSTO Dem.SWS_Dem_00383,1 */
      /* filter for valid event memory entries with lower or same priority than
       * new event and best entry, i.e. larger priority value */
      if ( (CurrentEventId != DEM_EVENT_ID_INVALID) &&
           (CurrentEvtPrioVal >= BestPrioVal) )
      {
        /* entry with lower priority (larger value) than best entry
         * (and new event) */
        if (CurrentEvtPrioVal > BestPrioVal)
        {
          /* select entry with lower priority for displacement */
          BestPrioVal  = CurrentEvtPrioVal;
          BestEntryIdx = EntryIdx;
          CriterionMatch = DEM_CRITERION_MATCH_PRIO;
        }
        else /* CurrentEvtPrioVal == BestPrioVal */
        {
          boolean IsCurrentEventPassive = FALSE;
          boolean IsBestEventPassive = FALSE;

          /* check whether current event is passive. For advanced displacement also
           * the EvMemEntryPtr of the current event and the event ID of the
           * reported event is necessary
           */
          IsCurrentEventPassive = DEM_IS_EVENT_PASSIVE(&EvMemEntry[EntryIdx],
            CurrentEventId, NewEventId);

          /* entry has same priority as best entry and new event */
          if (CurrentEvtPrioVal == NewEvtPrioVal)
          {
            /* !LINKSTO Dem.EventDisplacement.EqualPriority,1 */
            if ( (IsCurrentEventPassive == TRUE) &&
                 ( (CriterionMatch > DEM_CRITERION_MATCH_PASSIVE_STATUS) ||
                   ( (CriterionMatch == DEM_CRITERION_MATCH_PASSIVE_STATUS) &&
                     DEM_IS_EVENT_OLDER(EntryIdx, BestEntryIdx)) )
               )
            {
#if (DEM_OBD_EVENT_DISPLACEMENT == STD_ON)
              /* consider entry with same priority for displacing only if not protected */
              /* !LINKSTO SWS_Dem_00695_refine,1 */
              if (Dem_IsDisplaceOBDEventEntryAllowed(CurrentEventId) == TRUE)
#endif
              {
                /* select the first or oldest passive event with the same priority
                 * as the new event */
                BestEntryIdx = EntryIdx;
                CriterionMatch = DEM_CRITERION_MATCH_PASSIVE_STATUS;
              }
            }
#if (DEM_EVENT_DISPLACEMENT_CRITERION_TNCTOC == STD_ON)
            /* !LINKSTO SWS_Dem_00692_refine,1 */
            else if ( DEM_IS_EV_ST_BIT_TNCTOC_SET(CurrentEventId) &&
                      ( (CriterionMatch > DEM_CRITERION_MATCH_TNCTOC_STATUS) ||
                        ((CriterionMatch == DEM_CRITERION_MATCH_TNCTOC_STATUS) &&
                          DEM_IS_EVENT_OLDER(EntryIdx, BestEntryIdx)) )
                    )
            {
#if (DEM_OBD_EVENT_DISPLACEMENT == STD_ON)
              /* consider entry with same priority for displacing only if not protected */
              /* !LINKSTO SWS_Dem_00695_refine,1 */
              if (Dem_IsDisplaceOBDEventEntryAllowed(CurrentEventId) == TRUE)
#endif
              {
                /* select the first or oldest untested event (TNCTOC == 1) with
                 * the same priority as the new event */
                BestEntryIdx = EntryIdx;
                CriterionMatch = DEM_CRITERION_MATCH_TNCTOC_STATUS;
              }
            }
#endif /* DEM_EVENT_DISPLACEMENT_CRITERION_TNCTOC == STD_ON */
            else
            {
              /* 1) passive entry or entry with TNCTOC set must not be displaced
               *    if a corresponding older entry with same priority exists
               * 2) active entry of same priority as new event must not be
               *    displaced */
            }
          }
          else /* entry with same priority than best entry, but lower than new event */
          {
            /* check whether best event is passive. For advanced displacement also
             * the EvMemEntryPtr of the current event and the event ID of the
             * reported event is necessary
             */
            IsBestEventPassive = DEM_IS_EVENT_PASSIVE(&EvMemEntry[BestEntryIdx],
              EvMemEntry[BestEntryIdx].EventId, NewEventId);

            if ( (IsBestEventPassive == FALSE) &&
                 (IsCurrentEventPassive == TRUE) )
            {
              /* select the first passive event entry with lower priority than
               * the new event */
              BestEntryIdx = EntryIdx;
            }
            else if (IsBestEventPassive == IsCurrentEventPassive)
            {
              if (DEM_IS_EVENT_OLDER(EntryIdx, BestEntryIdx))
              {
                /* select older entry prior to a newer entry with same priority
                 * and same active/passive status for displacement */
                BestEntryIdx = EntryIdx;
              }
              /* else: entry must not be displaced if older entry with same
               *       priority is present */
            }
            else /* entry is active, but best entry is passive */
            {
              /* active entry must not be displaced if passive entry with same
               * priority is present */
            }
          }
        }
      }
#endif /* DEM_EVENT_DISPLACEMENT_STRATEGY == DEM_DISPLACEMENT_PRIO_OCC */
    }
  }

  if (CriterionMatch != DEM_CRITERION_MATCH_NONE)
  {
    *FoundEntry = &EvMemEntry[BestEntryIdx];
    *FoundEntryIdx = BestEntryIdx;
    Result = TRUE;
  }

  DBG_DEM_SEARCHFORENTRYTOREPLACE_EXIT(
    Result, OriginIdx, NewEventId, FFKind, FoundEntry, FoundEntryIdx);
  return Result;
}
#endif /* DEM_USE_EVENT_DISPLACEMENT == STD_ON */

STATIC FUNC(boolean, DEM_CODE) Dem_UpdateOccurrenceOrder(
  Dem_EventMemoryEntryPtrType UpdatedEvMemEntry)
{
  /* result value to support forced immediate write */
  boolean OrderRearranged = DEM_NVM_NO_FORCE;
  /* flag to indicate whether Dem_MaxOccOrder needs to be incremented */
  boolean MaxOccOrderIncrement = TRUE;

  const uint8 OriginIdx = Dem_GbiDTCOriginIdx(UpdatedEvMemEntry->EventId);
  const Dem_EventMemoryEntryPtrType EvMemEntry = Dem_EventMem[OriginIdx];

  Dem_SizeEvMemEntryType EntryIdx;

  DBG_DEM_UPDATEOCCURRENCEORDER_ENTRY(UpdatedEvMemEntry);

  /* no need to increment Dem_MaxOccOrder if its value is 0 (starting value)
   * and no other valid events are present in the memory, so that the value of
   * OccOrder starts from 0 and is set for first event memory entry */
  if (Dem_MaxOccOrder[OriginIdx] == 0U)
  {
    MaxOccOrderIncrement = FALSE;

    for (EntryIdx = 0U; EntryIdx < Dem_SizeEventMem[OriginIdx]; EntryIdx++)
    {
      if ( (EvMemEntry[EntryIdx].EventId != DEM_EVENT_ID_INVALID) &&
           (EvMemEntry[EntryIdx].EventId != UpdatedEvMemEntry->EventId) )
      {
        MaxOccOrderIncrement = TRUE;
        break;
      }
    }
  }

  /* OccOrder of reported event is the same than Dem_MaxOccOrder
   * since it was the newest event stored already
   * (OccOrder needs not to be incremented if it is the largest value already)
   * or the OccOrder of reported event is 0 (starting value)
   * but there was a newer event with larger occurrence order value */
  if ( (Dem_MaxOccOrder[OriginIdx] != UpdatedEvMemEntry->OccOrder) ||
       ((UpdatedEvMemEntry->OccOrder == 0U) && (MaxOccOrderIncrement == TRUE))
     )
  {
    /* update the array which stores the largest value of occurrence order
     * in the event memory */
    Dem_MaxOccOrder[OriginIdx]++;

    /* update the occurrence order of the event */
    UpdatedEvMemEntry->OccOrder = Dem_MaxOccOrder[OriginIdx];

    /* check whether the occurrence order exceeded the threshold */
    if (Dem_MaxOccOrder[OriginIdx] >= DEM_MAX_OCC_ORDER)
    {
      /* re-arrange the existing occurrence order */
      Dem_RearrangeOccurrenceOrder(OriginIdx);
      /* order rearranged, force immediate write if enabled */
      OrderRearranged = DEM_NVM_FORCE;
    }
  }

  DBG_DEM_UPDATEOCCURRENCEORDER_EXIT(OrderRearranged, UpdatedEvMemEntry);
  return OrderRearranged;
}

STATIC FUNC(void, DEM_CODE) Dem_RearrangeOccurrenceOrder(uint8 OriginIdx)
{
  const Dem_EventMemoryEntryPtrType EvMemEntry = Dem_EventMem[OriginIdx];

  Dem_SizeEvMemEntryType EntryIdx;
  Dem_SizeEvMemEntryType FoundEntryIdx = 0U;
  Dem_SizeEvMemEntryType ValidEntryIdx;
  Dem_SizeEvMemEntryType NumValidEntries = 0U;

  Dem_OccOrderType NextOccOrder = 0U;
  Dem_OccOrderType NextMinOccOrder;

  DBG_DEM_REARRANGEOCCURRENCEORDER_ENTRY(OriginIdx);

  /* calculate the number of valid event entries in the memory */
  for (EntryIdx = 0U; EntryIdx < Dem_SizeEventMem[OriginIdx]; EntryIdx++)
  {
    if (EvMemEntry[EntryIdx].EventId != DEM_EVENT_ID_INVALID)
    {
      NumValidEntries++;
    }
  }

  for (ValidEntryIdx = 0U; ValidEntryIdx < NumValidEntries; ValidEntryIdx++)
  {
    /* initialize the current occurrence order with maximum possible value of
     * OccOrder */
    NextMinOccOrder = DEM_MAX_OCC_ORDER;

    /* find the valid entry with next lowest value of OccOrder */
    for (EntryIdx = 0U; EntryIdx < Dem_SizeEventMem[OriginIdx]; EntryIdx++)
    {
      if ( (EvMemEntry[EntryIdx].EventId != DEM_EVENT_ID_INVALID) &&
           (EvMemEntry[EntryIdx].OccOrder >= NextOccOrder) &&
           (EvMemEntry[EntryIdx].OccOrder <= NextMinOccOrder) )
      {
        NextMinOccOrder = EvMemEntry[EntryIdx].OccOrder;
        FoundEntryIdx = EntryIdx;
      }
    }

    /* occurrence order value of next newer event is non-consecutive */
    if (EvMemEntry[FoundEntryIdx].OccOrder > NextOccOrder)
    {
      /* re-arrange the OccOrder of entry with lowest value of OccOrder which
       * is not re-arranged previously */
      EvMemEntry[FoundEntryIdx].OccOrder = NextOccOrder;

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
      /* 1) if EntryStatus is CLEAR_IMM never change it to sth. else
         2) if immediate storage is enabled for cleared events only
              --> target state CHANGED
         3) if immediate storage is enabled because of immediate events
              --> target state STORE_IMM */
      /* !LINKSTO dsn.Dem.ClearDTCBehavior.NonvolatileFinish,3 */
      if (EvMemEntry[FoundEntryIdx].EntryStatus != DEM_ENTRY_CLEAR_IMMEDIATELY)
      {
#if (DEM_IMMEDIATE_NV_STORAGE_TYPE == DEM_IMMEDIATE_CLEARED)
        EvMemEntry[FoundEntryIdx].EntryStatus = DEM_ENTRY_CHANGED;
#else
        EvMemEntry[FoundEntryIdx].EntryStatus = DEM_ENTRY_STORE_IMMEDIATELY;
#endif
      }
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */
    }
    /* else: next occurrence order value is consecutive already */

    NextOccOrder++;
  }

  /* update the array which stores the largest value of occurrence order in
   * a memory */
  Dem_MaxOccOrder[OriginIdx] = (Dem_OccOrderType)NumValidEntries - 1U;

  DBG_DEM_REARRANGEOCCURRENCEORDER_EXIT(OriginIdx);
}

STATIC FUNC(void, DEM_CODE) Dem_InitMaxOccOrder(void)
{
  uint8 OriginIdx;

#if (DEM_USE_PERMANENT_STORAGE == STD_ON)
  Dem_EventMemoryEntryPtrType EvMemEntry;
  Dem_SizeEvMemEntryType EntryIdx;
#endif

  DBG_DEM_INITMAXOCCORDER_ENTRY();

  for (OriginIdx = 0U; OriginIdx < DEM_MAXNUM_ORIGINS; OriginIdx++)
  {
    /* initialize the array which stores the largest value of occurrence order
     * per event memory */
    Dem_MaxOccOrder[OriginIdx] = 0U;

#if (DEM_USE_PERMANENT_STORAGE == STD_ON)
    EvMemEntry = Dem_EventMem[OriginIdx];

    for (EntryIdx = 0U; EntryIdx < Dem_SizeEventMem[OriginIdx]; EntryIdx++)
    {
      /* update largest value of occurrence order for the related event memory
       * kind, with highest valid occurrence order found */
      if ( (EvMemEntry[EntryIdx].EventId != DEM_EVENT_ID_INVALID) &&
           (EvMemEntry[EntryIdx].OccOrder > Dem_MaxOccOrder[OriginIdx]) )
      {
        Dem_MaxOccOrder[OriginIdx] = EvMemEntry[EntryIdx].OccOrder;
      }
    }
#endif /* DEM_USE_PERMANENT_STORAGE == STD_ON */
  }

  DBG_DEM_INITMAXOCCORDER_EXIT();
}

#if ( (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE) && \
      (DEM_NUM_OF_PIDS_IN_OBDFF > 0U) )
STATIC FUNC(void, DEM_CODE) Dem_RearrangeOBDOccurrenceOrder(void)
{
  Dem_SizeEvMemEntryType EntryIdx;
  Dem_SizeEvMemEntryType FoundEntryIdx = 0U;
  Dem_SizeEvMemEntryType ValidEntryIdx;
  Dem_SizeEvMemEntryType NumValidEntries = 0U;
  Dem_OccOrderType       NextOccOrder = 0U;

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
  const Dem_EventMemoryEntryPtrType EvMemEntry =
    Dem_EventMem[DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U];
#endif

  DBG_DEM_REARRANGEOBDOCCURRENCEORDER_ENTRY();

  /* calculate the number of valid event entries in the memory */
  for (EntryIdx = 0U; EntryIdx < DEM_MAX_NUMBER_EVENT_ENTRY_PRI; EntryIdx++)
  {
    Dem_EventIdType CurrentEvId =
      Dem_EventMem[(DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U)][EntryIdx].EventId;

    if ( (Dem_GbiDTCKind(CurrentEvId) == DEM_DTC_KIND_EMISSION_REL_DTCS) &&
         (CurrentEvId != DEM_EVENT_ID_INVALID) )
    {
      NumValidEntries++;
    }
  }

  for (ValidEntryIdx = 0U; ValidEntryIdx < NumValidEntries; ValidEntryIdx++)
  {
    /* initialize the current occurrence order with maximum possible value of
     * OccOrder */
    Dem_OccOrderType NextMinOccOrder = DEM_MAX_OCC_ORDER;

    /* find the valid entry with next lowest value of OccOrder */
    for (EntryIdx = 0U; EntryIdx < DEM_MAX_NUMBER_EVENT_ENTRY_PRI; EntryIdx++)
    {
      Dem_EventIdType CurrentEvId =
        Dem_EventMem[(DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U)][EntryIdx].EventId;

      if ( (Dem_GbiDTCKind(CurrentEvId) == DEM_DTC_KIND_EMISSION_REL_DTCS) &&
           (CurrentEvId != DEM_EVENT_ID_INVALID)                           &&
           (DEM_OBDFF_ENTRY_OCCURRENCE(EntryIdx) >= NextOccOrder)          &&
           (DEM_OBDFF_ENTRY_OCCURRENCE(EntryIdx) <= NextMinOccOrder) )
      {
        NextMinOccOrder = DEM_OBDFF_ENTRY_OCCURRENCE(EntryIdx);
        FoundEntryIdx = EntryIdx;
      }
    }

    /* occurrence order value of next newer event is non-consecutive */
    if (DEM_OBDFF_ENTRY_OCCURRENCE(FoundEntryIdx) > NextOccOrder)
    {
      /* re-arrange the OccOrder of entry with lowest value of OccOrder which
       * is not re-arranged previously */
      DEM_OBDFF_ENTRY_OCCURRENCE(FoundEntryIdx) = NextOccOrder;

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
      /* if immediate storage is enabled and EntryStatus is different than
       * DEM_ENTRY_CLEAR_IMMEDIATELY, the event entry shall be marked for
       * storage: DEM_ENTRY_CHANGED for DEM_IMMEDIATE_CLEARED storage type
       * and DEM_ENTRY_STORE_IMMEDIATELY for DEM_IMMEDIATE_CHANGED. */
      if (EvMemEntry[FoundEntryIdx].EntryStatus != DEM_ENTRY_CLEAR_IMMEDIATELY)
      {
#if (DEM_IMMEDIATE_NV_STORAGE_TYPE == DEM_IMMEDIATE_CLEARED)
        EvMemEntry[FoundEntryIdx].EntryStatus = DEM_ENTRY_CHANGED;
#else
        EvMemEntry[FoundEntryIdx].EntryStatus = DEM_ENTRY_STORE_IMMEDIATELY;
#endif
      }
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */
    }
    /* else: next occurrence order value is consecutive already */

    NextOccOrder++;
  }

  /* update the largest value of occurrence order */
  Dem_MaxOBDOccOrder = (Dem_OccOrderType)NumValidEntries - 1U;

  DBG_DEM_REARRANGEOBDOCCURRENCEORDER_EXIT();
}

#if (DEM_USE_PERMANENT_STORAGE == STD_ON)
STATIC FUNC(void, DEM_CODE) Dem_InitMaxOBDOccOrder(void)
{
  Dem_SizeEvMemEntryType EntryIdx;

  DBG_DEM_INITMAXOBDOCCORDER_ENTRY();

  Dem_MaxOBDOccOrder = 0U;

  /* iterate over all entries in Dem_EventMem for primary memory */
  for (EntryIdx = 0U; EntryIdx < DEM_MAX_NUMBER_EVENT_ENTRY_PRI; EntryIdx++)
  {
    Dem_EventIdType CurrentEvId =
        Dem_EventMem[(DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U)][EntryIdx].EventId;
    /* all valid OBD-relevant entries */
    if ( (Dem_GbiDTCKind(CurrentEvId) == DEM_DTC_KIND_EMISSION_REL_DTCS) &&
         (DEM_OBDFF_ENTRY_OCCURRENCE(EntryIdx) > Dem_MaxOBDOccOrder) )
    {
      Dem_MaxOBDOccOrder = DEM_OBDFF_ENTRY_OCCURRENCE(EntryIdx);
    }
  }

  DBG_DEM_INITMAXOBDOCCORDER_EXIT();
}
#endif /* DEM_USE_PERMANENT_STORAGE == STD_ON */
#endif /* ( (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE)  &&
            (DEM_NUM_OF_PIDS_IN_OBDFF > 0U) ) */


#if (DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON)
STATIC FUNC(void, DEM_CODE) Dem_RestoreCmbPDTC(void)
{
  Dem_DTCConfIdxType DTCConfIdx;

  DBG_DEM_RESTORECMBPDTC_ENTRY();

  /* Deviation TASKING-1 */
  for (DTCConfIdx = 0U; DTCConfIdx < DEM_NUM_CMB_DTCS; DTCConfIdx++)
  {
    if (DEM_IS_BIT_SET_IN_ARRAY(Dem_NvData.CmbPDTC, DTCConfIdx))
    {
      Dem_CmbDTCStatus[DTCConfIdx] |= DEM_UDS_STATUS_PDTC;
    }
  }

  DBG_DEM_RESTORECMBPDTC_EXIT();
}
#endif /* DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON */

#if (DEM_NUM_CMB_DTCS > 0U)
STATIC FUNC(void, DEM_CODE) Dem_InitAllCmbDTCStatus(boolean TriggeredByCycleEnd)
{
  Dem_DTCConfIdxType DTCConfIdx;
  Dem_CmbDTCEvLnkType FirstCmbEvIdx;
  Dem_EventIdType CurrentEvent;
  Dem_EventStatusExtendedType OldCombinedStatus = 0U;
  Dem_EventStatusExtendedType NewCombinedStatus = 0U;
  boolean resetCmbPDTC = FALSE;

  DBG_DEM_INITALLCMBDTCSTATUS_ENTRY(TriggeredByCycleEnd);

  /* Deviation TASKING-1 */
  for (DTCConfIdx = 0U; DTCConfIdx < DEM_NUM_CMB_DTCS; DTCConfIdx++)
  {
    if (DEM_IS_BIT_SET_IN_ARRAY(Dem_CmbDTCFlags, DTCConfIdx))
    {
      /* get the Index of first event combined into the DTC */
      FirstCmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx];

      /* get the first event combined into the DTC */
      CurrentEvent = Dem_CmbDTCEvents[FirstCmbEvIdx];
      /*
       * ENTER critical section
       */
      DEM_ENTER_EXCLUSIVE_AREA();

      OldCombinedStatus = Dem_CmbDTCStatus[DTCConfIdx];
#if (DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON)
      /* reset combined PDTC status if all combined events are qualified
      as Passed in current operation cycle*/
      /* !LINKSTO Dem.OBDonUDS.CombinedUDSDTCStatus.PDTC.ResetByPassedCycle,1 */
      if(TriggeredByCycleEnd == TRUE &&
              (!DEM_IS_ANY_BIT_SET(Dem_CmbDTCStatus[DTCConfIdx],
                                   DEM_UDS_STATUS_TNCTOC | DEM_UDS_STATUS_TFTOC)))
      {
        resetCmbPDTC = TRUE;
      }
#else
      TS_PARAM_UNUSED(TriggeredByCycleEnd);
#endif
      NewCombinedStatus = Dem_CalculateCmbDTCStatus(DTCConfIdx, resetCmbPDTC);
      /*
       * LEAVE critical section
       */
      DEM_EXIT_EXCLUSIVE_AREA();

      Dem_InternalCheckOnCmbDTCStatusChange(CurrentEvent, OldCombinedStatus, NewCombinedStatus);
      /* clear the bit corresponding to this already updated DTC status */
      DEM_ATOMIC_CLR_BIT_IN_ARRAY_8(Dem_CmbDTCFlags, DTCConfIdx);
    }
  }
  DBG_DEM_INITALLCMBDTCSTATUS_EXIT(TriggeredByCycleEnd);
}
#endif /* DEM_NUM_CMB_DTCS > 0U */

#if (DEM_NUM_CMB_DTCS > 0U)
FUNC(void, DEM_CODE) Dem_ResetStatusForCmbEvents(
  Dem_EventIdType EventId,
  boolean         EventStatusChanged)
{
#if ( (DEM_STATUS_BIT_HANDLING_TESTFAILEDSINCELASTCLEAR == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT) || \
      (DEM_RESET_PENDING_BIT_ON_OVERFLOW_SUPPORT == STD_ON) || \
      (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON) )
  Dem_CmbDTCEvLnkType Index;

  Dem_DTCStatusMaskType OldDTCStatusMask = 0U;
  Dem_DTCStatusMaskType NewDTCStatusMask = 0U;
#endif
  Dem_DTCConfIdxType DTCConfIdx = DEM_GBI_DTCCONFIDX(EventId);
  Dem_EventStatusExtendedType OldCombinedStatus = 0U;
  Dem_EventStatusExtendedType NewCombinedStatus = 0U;

  DBG_DEM_RESETSTATUSFORCMBEVENTS_ENTRY(EventId, EventStatusChanged);

#if ( (DEM_RESET_PENDING_BIT_ON_OVERFLOW_SUPPORT == STD_ON) || \
      (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON) || \
      (DEM_STATUS_BIT_HANDLING_TESTFAILEDSINCELASTCLEAR == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT) )
  for (Index = Dem_CmbDTCEvLnk[DTCConfIdx]; Index < Dem_CmbDTCEvLnk[DTCConfIdx + 1U]; Index++)
  {
    Dem_EventIdType CurrentEvent = Dem_CmbDTCEvents[Index];

    /* event that triggered the reset was already updated, only update the associated cmb events */
    if (CurrentEvent != EventId)
    {
      /* calculate Status Mask place outside the critical section */
      P2VAR(Dem_DTCStatusMaskType, AUTOMATIC, DEM_VAR) EventDTCStatusPtr
            = &DEM_DTC_STATUS_MASKS[CurrentEvent];

      /*
       * ENTER critical section to protect consistency of UDS Status Byte
       *       call-context: Dem_EnableDTCReocordUpdate, Dem_MainFunction,
       *                     Dem_SetAgingCycleState, Dem_SetOperationCycleState
       */
      DEM_ENTER_EXCLUSIVE_AREA();

      OldDTCStatusMask = *EventDTCStatusPtr;
      NewDTCStatusMask = OldDTCStatusMask;

#if (DEM_RESET_PENDING_BIT_ON_OVERFLOW_SUPPORT == STD_ON)
      /* !LINKSTO dsn.Dem.SelectablePDTC.ClearAgedEventEntry,1 */
      /* usually already cleared after first passed cycle in context of aging */
      DEM_CLR_MASK_8(NewDTCStatusMask, DEM_UDS_STATUS_PDTC);
#endif

#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON)
      DEM_CLR_MASK_8(NewDTCStatusMask, DEM_UDS_STATUS_CDTC);
#endif

#if (DEM_STATUS_BIT_HANDLING_TESTFAILEDSINCELASTCLEAR == \
          DEM_STATUS_BIT_AGING_AND_DISPLACEMENT)
      DEM_CLR_MASK_8(NewDTCStatusMask, DEM_UDS_STATUS_TFSLC);
#endif
      *EventDTCStatusPtr = NewDTCStatusMask;

      /*
       * LEAVE critical section
       */
      DEM_EXIT_EXCLUSIVE_AREA();

#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)

      if (OldDTCStatusMask != NewDTCStatusMask)
      {
        if (Dem_InitializationState != DEM_POSTINITIALIZED)
        {
          Dem_CbTriggerOnEventStatus(CurrentEvent, OldDTCStatusMask, NewDTCStatusMask);
        }
#if (!((DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON) && (DEM_RESET_PENDING_BIT_ON_OVERFLOW_SUPPORT == STD_ON)))
        EventStatusChanged = TRUE;
#endif
      }
#endif
    }
  }
#endif /* (DEM_RESET_PENDING_BIT_ON_OVERFLOW_SUPPORT == STD_ON) || \
          (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON) || \
          (DEM_STATUS_BIT_HANDLING_TESTFAILEDSINCELASTCLEAR == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT) */

  /* if the event status has changed, call Dem_CalculateCmbDTCStatus */
  /* Deviation TASKING-8 */
#if (!((DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON) && (DEM_RESET_PENDING_BIT_ON_OVERFLOW_SUPPORT == STD_ON)))
  if (EventStatusChanged == TRUE)
#else
  TS_PARAM_UNUSED(EventStatusChanged);
#endif
  {
    /*
     * ENTER critical section
     */
    DEM_ENTER_EXCLUSIVE_AREA();

    OldCombinedStatus = Dem_CmbDTCStatus[DTCConfIdx];
    /*rest combined PDTC status in case of aging and displacement
     *if DemResetPendingBitOnOverflow is TRUE
     */
    /* !LINKSTO Dem.OBDonUDS.CombinedUDSDTCStatus.PDTC.ResetByAging,1 */
    /* !LINKSTO Dem.OBDonUDS.CombinedUDSDTCStatus.PDTC.ResetByDisplacement,1 */
    /* !LINKSTO Dem.OBDonUDS.CombinedUDSDTCStatus.CDTC.ResetByAging,1 */
    /* !LINKSTO Dem.OBDonUDS.CombinedUDSDTCStatus.CDTC.ResetByDisplacement,1 */
#if ((DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON) && (DEM_RESET_PENDING_BIT_ON_OVERFLOW_SUPPORT == STD_ON))
    NewCombinedStatus = Dem_CalculateCmbDTCStatus(DTCConfIdx, TRUE);
#else
    NewCombinedStatus = Dem_CalculateCmbDTCStatus(DTCConfIdx, FALSE);
#endif
    /*
     * LEAVE critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();

    Dem_InternalCheckOnCmbDTCStatusChange(EventId, OldCombinedStatus, NewCombinedStatus);
  }

  DBG_DEM_RESETSTATUSFORCMBEVENTS_EXIT(EventId,EventStatusChanged);
}
#endif

#if ( ( (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF) || \
        (DEM_NUM_FAILURECYCLES == 0U) ) && \
      (DEM_OPCYC_OBD_DCY_USED == STD_ON) )
STATIC FUNC(boolean, DEM_CODE) Dem_CheckConfirmedDrivingCycle(
  Dem_EventIdType EventId)
{
  boolean Result = FALSE;

#if (DEM_NUM_FAILURECYCLES > 0U)
  const uint16 EventFailureClassIdx = Dem_GbiEventFailureClassIdx(EventId);
#else
  TS_PARAM_UNUSED(EventId);
#endif

  DBG_DEM_CHECKCONFIRMEDDRIVINGCYCLE_ENTRY(EventId);

#if (DEM_NUM_FAILURECYCLES > 0U)
  /* Note: if DEM_NUM_FAILURECYCLES > 0U, implicitly we are in the case
   *       when DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF */

  /* for events with fault confirmation configured */
  if (EventFailureClassIdx != DEM_NO_FAULT_CONFIRMATION)
  {
    /* process CDTC bit for events with DCY operation cycle which
     * reached the threshold while driving cycle was not qualified */
    const Dem_FailureCycleCounterType FailureCycleThreshold =
      DEM_INTERN_EVT_FAILCYC_CTR_THRESHOLD(EventId, EventFailureClassIdx);

    /* skip the DCY Qualification for zero-trip events */
    if (FailureCycleThreshold != 0U)
    {
      const Dem_StatusCounterPtrType FailureCounterPtr =
        Dem_GetStatusCounterReference(EventId);
      Dem_EventMemoryEntryPtrType EvMemEntry;
      const boolean EntryExists =
        Dem_SearchForEntry(EventId, &EvMemEntry, NULL_PTR);

      if ( ( (EntryExists != FALSE) &&
             (EvMemEntry->EventId == EventId) &&
             (EvMemEntry->EventFailureCycleCounter >= FailureCycleThreshold) ) ||
           ( (EntryExists == FALSE) &&
             (*FailureCounterPtr >= FailureCycleThreshold) ) )
      {
        /* counter has reached threshold: trigger CDTC bit */
        Result = TRUE;
      }
    }
  }
#else /* (DEM_NUM_FAILURECYCLES > 0U) */
  /* if there is no fault confirmation (DEM_NUM_FAILURECYCLES == 0 OR DEM_NO_FAULT_CONFIRMATION) ... */
  if (DEM_IS_EV_ST_BIT_TFTOC_SET(EventId))
  {
#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON)
    Dem_EventMemoryEntryPtrType EvMemEntry;
    boolean EntryExists = Dem_SearchForEntry(EventId, &EvMemEntry, NULL_PTR);
    /* ... and test failed this operation cycle ... */
    /* ... and if entry exists for the current event... */
    if ((EntryExists == TRUE) && (EvMemEntry->EventId == EventId))
#endif
    {
      /* ... trigger CDTC */
      Result = TRUE;
    }
  }
#endif /* (DEM_NUM_FAILURECYCLES > 0U) */

  DBG_DEM_CHECKCONFIRMEDDRIVINGCYCLE_EXIT(Result, EventId);
  return Result;
}
#endif /* ( (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF) ||
            (DEM_NUM_FAILURECYCLES == 0U) ) &&
          (DEM_OPCYC_OBD_DCY_USED == STD_ON) */

#if (DEM_NUM_FAILURECYCLES > 0U)
#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON)
STATIC FUNC(void, DEM_CODE) Dem_SetCDTCOnConfirmation(void)
{
  uint8_least OriginIdx;
  Dem_SizeEvMemEntryType Entry;
  Dem_EventIdType EventId;

  DBG_DEM_SETCDTCONCONFIRMATION_ENTRY();

  for (OriginIdx = 0U; OriginIdx < (uint8)DEM_MAXNUM_ORIGINS; ++OriginIdx)
  {
    for (Entry = 0U; Entry < Dem_SizeEventMem[OriginIdx]; ++Entry)
    {
#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
      Dem_DTCStatusMaskType NewDTCStatusMask = 0;
      Dem_DTCStatusMaskType OldDTCStatusMask = 0;
      boolean Continue = FALSE;
#endif
#if (DEM_NUM_CMB_DTCS > 0U)
      Dem_DTCConfIdxType DTCConfIdx;
      Dem_EventStatusExtendedType OldCombinedStatus = 0U;
      Dem_EventStatusExtendedType NewCombinedStatus = 0U;
#endif
      /* EventIdPtr is used to make the address resolution instructions
         happen outside the critical section, EvMemEntryPtr is to simplify
         the statement */
      Dem_EventMemoryEntryPtrType EvMemEntryPtr =
                &Dem_EventMem[OriginIdx][Entry];
      P2VAR(Dem_EventIdType, AUTOMATIC, AUTOMATIC) EventIdPtr =
            &(EvMemEntryPtr->EventId);
      /*
       * ENTER critical section to protect consistency of UDS Status Byte
       *       call-context: Dem_MainFunction
       */
      DEM_ENTER_EXCLUSIVE_AREA();

      EventId = *EventIdPtr;

      if (EventId != DEM_EVENT_ID_INVALID)
      {
#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
        OldDTCStatusMask = DEM_DTC_STATUS_MASKS[EventId];
#endif

        if (!DEM_IS_EV_ST_BIT_CDTC_SET(EventId))
        {
          /* !LINKSTO Dem.OperationCycleQualification.SkipConfirmation,2 */
          /* !LINKSTO dsn.Dem.OBD.OPCYC.DCY.ExtensionDemSetCDTCOnConfirmation.FaultConfirmation,3 */
#if (DEM_OPCYC_OBD_DCY_USED == STD_ON)
          if (DEM_IS_CYCLE_QUALIFIED(EventId) == TRUE)
#endif
          {
            uint16 EventFailureClassIdx = Dem_GbiEventFailureClassIdx(EventId);
            boolean HandleCDTCPreconditions = FALSE;

#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
            if (!DEM_IS_ANY_BIT_SET(EvMemEntryPtr->SI30, DEM_SI30_STATUS_AGEDDTC))
#endif
            {
              /* the following if statements verify the pre-conditions for setting the CDTC bit */
              if (EventFailureClassIdx != DEM_NO_FAULT_CONFIRMATION)
              {
                /* for non-confirmed DTC with fault confirmation configured the counter value
                 * needs to be checked against the threshold configured of the current event */
                HandleCDTCPreconditions = (Dem_EventMem[OriginIdx][Entry].EventFailureCycleCounter >=
                DEM_INTERN_EVT_FAILCYC_CTR_THRESHOLD(EventId, EventFailureClassIdx)) ? TRUE : FALSE;
              }
              else
              {
#if (DEM_OPCYC_OBD_DCY_USED == STD_ON)
                /* for non-confirmed DTC without fault confirmation configured referring a DCY cycle
                 * the pre-conditions are met */
                /* !LINKSTO Dem.NoFaultConfirmation,1 */
                /* !LINKSTO dsn.Dem.OBD.OPCYC.DCY.ExtensionDemSetCDTCOnConfirmation.NoFaultConfirmation,3 */
                HandleCDTCPreconditions = TRUE;
#endif
              }
            }

            /* proceed to set the CDTC bit if preconditions are met */
            if (HandleCDTCPreconditions == TRUE)
            {
              /* sets the confirmed status bit */
              DEM_SET_EV_ST_MASK((EventId), DEM_UDS_STATUS_CDTC);

#if (DEM_GET_DTCBYOCCURRENCETIME_SUPPORT == STD_ON)
              /* store event to be detected confirmed DTC occurrence kind */
              Dem_UpdateEventIdOccurKinds(EventId,
                DEM_FIRST_DET_CONFIRMED_DTC, DEM_MOST_REC_DET_CONFIRMED_DTC);
#endif
#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
              NewDTCStatusMask = DEM_DTC_STATUS_MASKS[EventId];
              /* notify application as CDTC-bit is changed and update combined
               status */
              Continue = TRUE;
#endif /* DEM_USE_CB_TRIG_ON_STATUS_CHANGE */
              /* critical section could be exited here, not because of guideline */
#if ( (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON) && \
      ( (DEM_OPCYC_OBD_DCY_USED == STD_ON) || \
        ( (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) && \
          (DEM_VCC_OCC5_USED == STD_ON) ) ) )

            /* CDTC was set and (if enabled) OCC5 counter was updated:
             * entry needs to be stored immediately if the immediate storage
             * is enabled for the updated event to save the CDTC status
             * and the OCC5 counter */
            /* !LINKSTO dsn.Dem.ImmediateStorage.StatusUpdate.CDTC,1 */
            /* !LINKSTO dsn.Dem.VCC.EventMemoryEntryChanged,4 */
            Dem_CheckForImmediateEntryStorage(EventId,
                                              EvMemEntryPtr,
                                              Entry,
                                              DEM_NVM_NO_FORCE);
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */
            }
          }
        }
      }
#if (DEM_NUM_CMB_DTCS > 0U)
      DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
      if (DEM_IS_DTC_COMBINED(DTCConfIdx))
      {
        OldCombinedStatus = Dem_CmbDTCStatus[DTCConfIdx];
        NewCombinedStatus = Dem_CalculateCmbDTCStatus(DTCConfIdx, FALSE);
      }
      else
      {
        TS_PARAM_UNUSED(OldCombinedStatus);
        TS_PARAM_UNUSED(NewCombinedStatus);
      }
#endif
      /*
       * LEAVE critical section
       */
      DEM_EXIT_EXCLUSIVE_AREA();

#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
      if (Continue == TRUE)
      {
        Dem_CbTriggerOnEventStatus(EventId,
                                   OldDTCStatusMask,
                                   NewDTCStatusMask);
      }
#endif /* (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) */
#if (DEM_NUM_CMB_DTCS > 0U)
      Dem_InternalCheckOnCmbDTCStatusChange(EventId, OldCombinedStatus, NewCombinedStatus);
#endif

    }
  }

  DBG_DEM_SETCDTCONCONFIRMATION_EXIT();
}
#endif /* DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON */

#if ((DEM_NUM_CMB_DTCS > 0U) && (DEM_OBDONUDS_COMBINATION_ENABLED == STD_OFF))
STATIC FUNC(Dem_CmbDTCEvLnkType, DEM_CODE) Dem_GetFailureCounterIdxOfCmbEvent(
  Dem_EventIdType EventId)
{
  Dem_CmbDTCEvLnkType CmbEventIdx = Dem_CmbDTCEvLnk[DEM_GBI_DTCCONFIDX(EventId)];

  DBG_DEM_GETFAILURECOUNTERIDXOFCMBEVENT_ENTRY(EventId);

  /* it is assured by the generator that the EventId of a cmb event
   * will be found in Dem_CmbDTCEvents[] */
  while (EventId != Dem_CmbDTCEvents[CmbEventIdx])
  {
    CmbEventIdx++;
  }

  DBG_DEM_GETFAILURECOUNTERIDXOFCMBEVENT_EXIT(CmbEventIdx, EventId);
  return CmbEventIdx;
}
#endif /* (DEM_NUM_CMB_DTCS > 0U) && (DEM_OBDONUDS_COMBINATION_ENABLED == STD_OFF) */

STATIC FUNC(void, DEM_CODE) Dem_ProcessFailureCounterReset(
  Dem_EventIdType          EventId,
  Dem_OperationCycleIdType OperationCycleId)
{
  const uint16 EventFailureClassIdx = Dem_GbiEventFailureClassIdx(EventId);
  Dem_EventMemoryEntryPtrType EvMemEntry;
  Dem_SizeEvMemEntryType EvMemEntryIdx;

  DBG_DEM_PROCESSFAILURECOUNTERRESET_ENTRY(EventId, OperationCycleId);

  /* for events with fault confirmation configured */
  if (EventFailureClassIdx != DEM_NO_FAULT_CONFIRMATION)
  {
    const Dem_OperationCycleIdType EventFailureCycleIdx =
      Dem_GbiEventFailureCycleIdx(EventId, EventFailureClassIdx);

    /* only for events of this failure cycle */
    if (EventFailureCycleIdx == OperationCycleId)
    {
#if (DEM_NUM_CMB_DTCS > 0U)
      const Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
#endif
      /* Rest the counter only if the event is TESTED and NOT FAILED this failure cycle,
       * and its DTC is non-confirmed */
      boolean CounterResetNotPossible = DEM_IS_ANY_EV_ST_BIT_SET(EventId, DEM_UDS_STATUS_CDTC |
                                                                          DEM_UDS_STATUS_TNCTOC |
                                                                          DEM_UDS_STATUS_TFTOC);

#if (DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON)
      /* !LINKSTO Dem.OBDonUDS.CombinedUDSDTCStatus.FailureCounter.ResetByPassedCycle,1 */
      if (DEM_IS_DTC_COMBINED(DTCConfIdx))
      {
        CounterResetNotPossible = DEM_IS_CMB_ST_BIT_SET_IN_DTC(DTCConfIdx, DEM_UDS_STATUS_CDTC |
                                                                 DEM_UDS_STATUS_TNCTOC |
                                                                 DEM_UDS_STATUS_TFTOC);
      }
#endif /* DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON */

      /* !LINKSTO Dem.FaultConfirmation.EventFailureCounterReset,1 */
      if (CounterResetNotPossible == FALSE)
      {
#if (DEM_MILGROUP_SUPPORT == STD_ON)
        boolean IsResetAllowed = TRUE;
        Dem_MILGroupIndexType MILGroupIndex = Dem_GbiMILGroupIndex(EventId);
#endif
        /*
         * ENTER critical section to protect the event memory entry
         *       call-context: Rte (Task)
         */
        DEM_ENTER_EXCLUSIVE_AREA();

#if (DEM_MILGROUP_SUPPORT == STD_ON)
        /* check if the event is assigned to a MIL group */
        if (MILGroupIndex != DEM_MILGROUP_GROUP_IDX_INVALID)
        {
#if (DEM_CALIBRATION_SUPPORT == STD_ON)
          Dem_IndicatorIdxType IndicatorIdx;

          /* !LINKSTO dsn.Dem.MILGroup.MILGroupEvent,1 */
          /* check if MIL indicator wasn't removed from event
           * through calibration */
          if (Dem_IsMILEvent(EventId, &IndicatorIdx) == TRUE)
#endif
          {
            /* evaluate if all the events in the MIL group were tested in this
             * operation cycle and only qualified as passed */
            IsResetAllowed = Dem_MILGroupCheckPassedCycleAll(EventId,
                                                             MILGroupIndex);
          }
        }
        /* !LINKSTO Dem.MILGroup.RestartCountingAfterPassedCycle,1 */
        /* for MIL group events, restart counters only after passed cycles */
        if (IsResetAllowed)
#endif /* DEM_MILGROUP_SUPPORT == STD_ON */
        {
          if (Dem_SearchForEntry(EventId, &EvMemEntry, &EvMemEntryIdx) == TRUE)
          {
#if ((DEM_NUM_CMB_DTCS > 0U) && (DEM_OBDONUDS_COMBINATION_ENABLED == STD_OFF))
            /* reset failure counter in memory entry only for the stored event */
            if (EvMemEntry->EventId == EventId)
#endif /* (DEM_NUM_CMB_DTCS > 0U) && (DEM_OBDONUDS_COMBINATION_ENABLED == STD_OFF) */
            {
              EvMemEntry->EventFailureCycleCounter = 0U;

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
              /* event memory entry has been updated:
               * it needs to be stored immediately if the immediate storage
               * is enabled for the updated event */
              Dem_CheckForImmediateEntryStorage(EventId,
                                                EvMemEntry,
                                                EvMemEntryIdx,
                                                DEM_NVM_NO_FORCE);
#endif
            }

#if ((DEM_NUM_CMB_DTCS > 0U) && (DEM_OBDONUDS_COMBINATION_ENABLED == STD_OFF))
            if (DEM_IS_DTC_COMBINED(DTCConfIdx))
            {
              Dem_CmbDTCEvLnkType IndexOfCmbEv = Dem_GetFailureCounterIdxOfCmbEvent(EventId);

              /* reset failure counter of the cmb event */
              DEM_CMBEV_FAILURE_CYC_COUNTER[IndexOfCmbEv] = 0U;
            }
#endif /* (DEM_NUM_CMB_DTCS > 0U) && (DEM_OBDONUDS_COMBINATION_ENABLED == STD_OFF) */
          }
#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF)
          else /* no entry */
          {
            const Dem_StatusCounterPtrType FailureCounterPtr =
              Dem_GetStatusCounterReference(EventId);

            /* reset failure counter for regular & combined events */
            *FailureCounterPtr = 0U;
          }
#endif
        }
        /*
         * LEAVE critical section
         */
        DEM_EXIT_EXCLUSIVE_AREA();
      }
    }
  }

  DBG_DEM_PROCESSFAILURECOUNTERRESET_EXIT(EventId, OperationCycleId);
}

STATIC FUNC(void, DEM_CODE) Dem_UpdateFailureCounterCycleStart(
  Dem_EventIdType          EventId,
  Dem_OperationCycleIdType OperationCycleId)
{
  const uint16 EventFailureClassIdx = Dem_GbiEventFailureClassIdx(EventId);

  DBG_DEM_UPDATEFAILURECOUNTERCYCLESTART_ENTRY(EventId, OperationCycleId);

  /* for events with fault confirmation configured */
  if (EventFailureClassIdx != DEM_NO_FAULT_CONFIRMATION)
  {
    const Dem_OperationCycleIdType EventFailureCycleIdx =
      Dem_GbiEventFailureCycleIdx(EventId, EventFailureClassIdx);
    const Dem_OperationCycleIdType EventOpCycleIdx =
      Dem_GbiOpCycleIdx(EventId);

    /* !LINKSTO Dem.FaultConfirmation.EventFailureCounterUpdateCycleStart,2 */
    /* only for events with this failure cycle */
    if ( (EventFailureCycleIdx == OperationCycleId) &&
         (EventFailureCycleIdx != EventOpCycleIdx) )
    {
      /* non-confirmed DTC, test failed this operation cycle */
      if ( DEM_IS_EV_ST_BIT_TFTOC_SET(EventId) &&
           (!DEM_IS_EV_ST_BIT_CDTC_SET(EventId))
         )
      {
#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON)
        boolean HandleCDTC = FALSE;
#else
        boolean HandleCDTC = TRUE;
#endif
        /* increment the failure counter */
        if (Dem_IncrementFailureCounter(EventId, HandleCDTC) == TRUE)
        {
#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON)
          /* trigger fault confirmation processing in main function */
          Dem_DoProcessFaultConfirmation = TRUE;
#else
#if (DEM_GET_DTCBYOCCURRENCETIME_SUPPORT == STD_ON)
          /* store event to be detected confirmed DTC occurrence kind */
          Dem_UpdateEventIdOccurKinds(EventId,
            DEM_FIRST_DET_CONFIRMED_DTC, DEM_MOST_REC_DET_CONFIRMED_DTC);
#endif
#endif /* DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON */
        }
      }
    }
  }

  DBG_DEM_UPDATEFAILURECOUNTERCYCLESTART_EXIT(EventId, OperationCycleId);
}

FUNC(boolean, DEM_CODE) Dem_IncrementFailureCounter(
  Dem_EventIdType EventId,
  boolean         HandleCDTC)
{
  boolean Result = FALSE;
  Dem_EventMemoryEntryPtrType EvMemEntry;
  Dem_SizeEvMemEntryType EvMemEntryIdx;

  DBG_DEM_INCREMENTFAILURECOUNTER_ENTRY(EventId, HandleCDTC);

  /* if event memory entry exists */
  if (Dem_SearchForEntry(EventId, &EvMemEntry, &EvMemEntryIdx) == TRUE)
  {
#if ((DEM_NUM_CMB_DTCS > 0U) && (DEM_OBDONUDS_COMBINATION_ENABLED == STD_OFF))
    if (DEM_IS_EVENT_COMBINED(EventId))
    {
      Dem_CmbDTCEvLnkType IndexOfCmbEv = Dem_GetFailureCounterIdxOfCmbEvent(EventId);
      boolean CurrentEvThresholdReached;
      /* check if the stored sub-event reached its failure threshold and will get confirmed */
      const boolean StoredEvThresholdReached = (EvMemEntry->EventFailureCycleCounter >=
        DEM_INTERN_EVT_FAILCYC_CTR_THRESHOLD(EvMemEntry->EventId,
          Dem_GbiEventFailureClassIdx(EvMemEntry->EventId))) ? TRUE: FALSE;

      const Dem_FailureCycleCounterType FailureCycleThreshold =
        DEM_INTERN_EVT_FAILCYC_CTR_THRESHOLD(EventId, Dem_GbiEventFailureClassIdx(EventId));

      if (DEM_CMBEV_FAILURE_CYC_COUNTER[IndexOfCmbEv] < FailureCycleThreshold)
      {
#if (DEM_MILGROUP_SUPPORT == STD_ON)
        /* !LINKSTO dsn.Dem.MILGroup.FailureCounterProcessing,1 */
        /* handle the MIL group event failure counter within the MIL group */
        if (Dem_MILGroupProcessCounter(&(DEM_CMBEV_FAILURE_CYC_COUNTER[IndexOfCmbEv]),
                                       EventId,
                                       DEM_NUM_INDICATOR_LINKS,
                                       DEM_MILGROUP_FAILURE_COUNTER_UPDATE) == FALSE)
#endif
        {
          /* update the failure counter of the combined event */
          DEM_CMBEV_FAILURE_CYC_COUNTER[IndexOfCmbEv]++;
        }
      }

      /* check if the current event reached the threshold */
      CurrentEvThresholdReached =
        (DEM_CMBEV_FAILURE_CYC_COUNTER[IndexOfCmbEv] >= FailureCycleThreshold) ? TRUE: FALSE;

      if ( (EvMemEntry->EventId == EventId) ||
           ( (StoredEvThresholdReached == FALSE) &&
             (CurrentEvThresholdReached == TRUE) ) )
      {
        /* CDTC bit not set yet for the combined status but this event reached the threshold:
         * replace the currently stored sub-event with this one so the CDTC bit can be set */
        EvMemEntry->EventId = EventId;
        EvMemEntry->EventFailureCycleCounter = DEM_CMBEV_FAILURE_CYC_COUNTER[IndexOfCmbEv];

        if ( (StoredEvThresholdReached == FALSE) &&
             (CurrentEvThresholdReached == TRUE) )
        {
          /* set/trigger CDTC bit */
          if (HandleCDTC == TRUE)
          {
            DEM_SET_EV_ST_MASK(EventId, DEM_UDS_STATUS_CDTC);
          }
          Result = TRUE;
        }

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
        /* event memory entry has been updated:
         * it needs to be stored immediately if the immediate storage
         * is enabled for the updated event */
        Dem_CheckForImmediateEntryStorage(EventId,
                                          EvMemEntry,
                                          EvMemEntryIdx,
                                          DEM_NVM_NO_FORCE);
#endif
      }
    }
    else
#endif /* (DEM_NUM_CMB_DTCS > 0U) && (DEM_OBDONUDS_COMBINATION_ENABLED == STD_OFF) */
    {
      const Dem_FailureCycleCounterType CurrentEvThreshold =
        DEM_INTERN_EVT_FAILCYC_CTR_THRESHOLD(EventId, Dem_GbiEventFailureClassIdx(EventId));

      /* check if failure counter threshold is reached or not */
      if (EvMemEntry->EventFailureCycleCounter < CurrentEvThreshold)
      {
#if (DEM_MILGROUP_SUPPORT == STD_ON)
        /* !LINKSTO dsn.Dem.MILGroup.FailureCounterProcessing,1 */
        /* handle the MIL group event failure counter within the MIL group */
        if (Dem_MILGroupProcessCounter(&(EvMemEntry->EventFailureCycleCounter),
                                       EventId,
                                       DEM_NUM_INDICATOR_LINKS,
                                       DEM_MILGROUP_FAILURE_COUNTER_UPDATE) == FALSE)
#endif
        {
          /* !LINKSTO Dem.OBDonUDS.CombinedUDSDTCStatus.FailureCounter.CommonCounter,1 */
          /* !LINKSTO dsn.Dem.OBDonUDS.EventCombination.ResetCDTCOnOverflow.CommonFailureCounter,1 */
          /* !LINKSTO Dem.OBDonUDS.CombinedUDSDTCStatus.FailureCounter.Increase,1 */

          /* threshold not reached, increment the counter */
          EvMemEntry->EventFailureCycleCounter++;

#if (DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON)
          if (DEM_IS_EVENT_COMBINED(EventId))
          {
            /* update the memory entry with the EventId of the combined event which
             * incremeted the common failure counter, if OBDonUDS combination enabled */
            EvMemEntry->EventId = EventId;
          }
#endif
        }

        if (EvMemEntry->EventFailureCycleCounter >= CurrentEvThreshold)
        {
          /* !LINKSTO Dem.OBDonUDS.CombinedUDSDTCStatus.CDTC.Set.MemoryEntryExists,1 */
          /* !LINKSTO dsn.Dem.OBDonUDS.EventCombination.CmbCDTC,1 */

          /* counter has reached threshold: set/trigger CDTC bit */
          if (HandleCDTC == TRUE)
          {
            DEM_SET_EV_ST_MASK(EventId, DEM_UDS_STATUS_CDTC);
          }
          Result = TRUE;
        }

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
        /* event memory entry has been updated:
         * it needs to be stored immediately if the immediate storage
         * is enabled for the updated event */
        Dem_CheckForImmediateEntryStorage(EventId,
                                          EvMemEntry,
                                          EvMemEntryIdx,
                                          DEM_NVM_NO_FORCE);
#endif
      }
    }
  }
#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF)
  else
  {
    const Dem_FailureCycleCounterType FailureCycleThreshold =
      DEM_INTERN_EVT_FAILCYC_CTR_THRESHOLD(EventId, Dem_GbiEventFailureClassIdx(EventId));
    /* get pointer to failure counter for regular & combined events */
    const Dem_StatusCounterPtrType FailureCounterPtr =
      Dem_GetStatusCounterReference(EventId);

#if (DEM_MILGROUP_SUPPORT == STD_ON)
    /* !LINKSTO dsn.Dem.MILGroup.FailureCounterProcessing,1 */
    /* handle the MIL group event failure counter within the MIL group */
    if (Dem_MILGroupProcessCounter(FailureCounterPtr,
                                   EventId,
                                   DEM_NUM_INDICATOR_LINKS,
                                   DEM_MILGROUP_FAILURE_COUNTER_UPDATE) == FALSE)
#endif
    {
      /* safe to increment the counter,
       * because CDTC is not set so far */
      (*FailureCounterPtr)++;
    }

    if (*FailureCounterPtr >= FailureCycleThreshold)
    {
      /* counter has reached threshold: set/trigger CDTC bit */
      if (HandleCDTC == TRUE)
      {
        DEM_SET_EV_ST_MASK(EventId, DEM_UDS_STATUS_CDTC);
      }
      Result = TRUE;
    }
  }
#endif /* DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF */

  DBG_DEM_INCREMENTFAILURECOUNTER_EXIT(Result, EventId, HandleCDTC);
  return Result;
}
#endif /* (DEM_NUM_FAILURECYCLES > 0U) */

#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT_FAULT_CONFIRMATION == STD_ON)
FUNC(void, DEM_CODE) Dem_ResetStatusCounter(Dem_EventIdType EventId)
{
  const uint16 EventFailureClassIdx = Dem_GbiEventFailureClassIdx(EventId);

  DBG_DEM_RESETSTATUSCOUNTER_ENTRY(EventId);

  if (EventFailureClassIdx != DEM_NO_FAULT_CONFIRMATION)
  {
    /* get pointer to status counter for regular & combined events */
    Dem_StatusCounterPtrType StatusCounterPtr =
      Dem_GetStatusCounterReference(EventId);

    /* reset status counter */
    *StatusCounterPtr = 0U;
  }

  DBG_DEM_RESETSTATUSCOUNTER_EXIT(EventId);
}

FUNC_P2VAR(Dem_StatusCounterType, DEM_VAR_CLEARED, DEM_CODE)
  Dem_GetStatusCounterReference(Dem_EventIdType EventId)
{
  Dem_StatusCounterPtrType Result;

  DBG_DEM_GETSTATUSCOUNTERREFERENCE_ENTRY(EventId);

#if ((DEM_NUM_CMB_DTCS > 0U) && (DEM_OBDONUDS_COMBINATION_ENABLED == STD_OFF))
  if (DEM_IS_EVENT_COMBINED(EventId))
  {
    Dem_CmbDTCEvLnkType IndexOfCmbEv = Dem_GetFailureCounterIdxOfCmbEvent(EventId);

    /* get pointer to failure counter */
    Result = &DEM_CMBEV_FAILURE_CYC_COUNTER[IndexOfCmbEv];
  }
  else
#endif /* (DEM_NUM_CMB_DTCS > 0U) && (DEM_OBDONUDS_COMBINATION_ENABLED == STD_OFF) */
  {
    const Dem_EventIdType GroupIdx = EventId / DEM_STATUS_COUNTER_GROUP_SIZE;
    const Dem_EventIdType StartEventIdOfGroup = GroupIdx * DEM_STATUS_COUNTER_GROUP_SIZE;
    Dem_EvIdLeastType EvId;
    Dem_StatusCounterIndexType StatusCounterIdxOffset = 0U;
    Dem_StatusCounterIndexType StatusCounterIdx;

    /* search for the number of events in this group with fault confirmation,
     * previous of the requested event */
    for (EvId = StartEventIdOfGroup; EvId < EventId; EvId++)
    {
#if (DEM_NUM_CMB_DTCS > 0U)
      if (!DEM_IS_EVENT_COMBINED((Dem_EventIdType)EvId))
#endif
      {
        if (Dem_GbiEventFailureClassIdx((Dem_EventIdType)EvId) !=
             DEM_NO_FAULT_CONFIRMATION)
        {
          StatusCounterIdxOffset++;
        }
      }
    }

    /* compute the Index of the status counter data:
     * base Index of the group + the calculated offset */
    StatusCounterIdx =
      Dem_StatusCounterIndex[GroupIdx] + StatusCounterIdxOffset;

    Result = &Dem_NvData.StatusCounter[StatusCounterIdx];
  }

  DBG_DEM_GETSTATUSCOUNTERREFERENCE_EXIT(Result, EventId);
  return Result;
}
#endif /* DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT_FAULT_CONFIRMATION == STD_ON */

#if (DEM_CB_TRIG_ON_EVDAT_ASR403 == STD_ON)
#if ( (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON) && \
      (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON) )
STATIC FUNC(boolean, DEM_CODE) Dem_CheckIntDataElementUsage(
  Dem_EventIdType        EventId,
  Dem_DataElementIdxType FirstDataElementIdx,
  Dem_DataElementIdxType SecondDataElementIdx)
{
  /* get extended data class layout */
  CONSTP2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass =
    &Dem_EDClass[Dem_GbiEDClassIdx(EventId)];

  Dem_EDSegIdxType SegIdx;
  P2CONST(Dem_EDSegmentType, AUTOMATIC, DEM_CONST) EDSegment;
  Dem_NumDataElementsType DataElementIndex;
  boolean EventMemIntDataElementMapFound = FALSE;

  DBG_DEM_CHECKINTDATAELEMENTUSAGE_ENTRY(EventId, FirstDataElementIdx, SecondDataElementIdx);

  for (SegIdx = 0U; (SegIdx < EDClass->NumEDSegs); ++SegIdx)
  {
    EDSegment = &Dem_EDSegment[EDClass->EDSegIdx[SegIdx]];

    for (DataElementIndex = 0U; (DataElementIndex < EDSegment->NumEDDataElements);
         ++DataElementIndex)
    {
      if ( (EDSegment->DataElementIdx[DataElementIndex] == FirstDataElementIdx) ||
           (EDSegment->DataElementIdx[DataElementIndex] == SecondDataElementIdx) )
      {
        EventMemIntDataElementMapFound = TRUE;
        break;
      }
    }

    if (EventMemIntDataElementMapFound == TRUE)
    {
      break;
    }
  }

  DBG_DEM_CHECKINTDATAELEMENTUSAGE_EXIT(
    EventMemIntDataElementMapFound, EventId, FirstDataElementIdx, SecondDataElementIdx);
  return EventMemIntDataElementMapFound;
}

STATIC FUNC(void, DEM_CODE) Dem_CbTriggerOnOvfIndSet(uint8 OriginIdx)
{
  const Dem_SizeEvMemEntryType SizeEventMem = Dem_SizeEventMem[OriginIdx];

  Dem_SizeEvMemEntryType Index;
  Dem_EventMemoryEntryPtrType EvMemEntry = Dem_EventMem[OriginIdx];

  DBG_DEM_CBTRIGGERONOVFINDSET_ENTRY(OriginIdx);

  for (Index = 0U; Index < SizeEventMem; ++Index)
  {
    const Dem_EventIdType EventId = EvMemEntry[Index].EventId;

    if (EventId != DEM_EVENT_ID_INVALID)
    {
      if ( Dem_CheckIntDataElementUsage(
             EventId, DEM_INT_VAL_IDX_OVFIND, DEM_INT_VAL_UNUSED) == TRUE )
      {
        /* notify application that event data has changed */
        Dem_CbTriggerOnEventData(EventId);
      }
    }
  }

  DBG_DEM_CBTRIGGERONOVFINDSET_EXIT(OriginIdx);
}
#endif /* (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON) && \
          (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON) */
#endif /* ( DEM_CB_TRIG_ON_EVDAT_ASR403 == STD_ON) */

#if (DEM_NUM_INDICATOR_LINKS > 0U)
STATIC FUNC(void, DEM_CODE) Dem_ProcessIndicator(
  Dem_OperationCycleIdType OperationCycleId)
{
  DBG_DEM_PROCESSINDICATOR_ENTRY(OperationCycleId);

#if (DEM_CALIBRATION_SUPPORT == STD_ON)
  {
    Dem_EventIdType EventId;

    for (EventId = 1U; EventId <= DEM_MAX_EVENTID; EventId++)
    {
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
      if (Dem_GbiEvAvailable(EventId) == FALSE)
      {
        /* event is disabled so this event shall be skipped */
      }
      else
#endif
      {
        const Dem_IndicatorGrpIdxType IndicatorClassIdx =
          Dem_GbiIndicatorClassIndex(EventId);

        if (IndicatorClassIdx < DEM_INDICATOR_UNUSED)
        {
          const Dem_IndicatorIdxType IndicatorClassIdxStart =
            Dem_IndicatorGroups[IndicatorClassIdx];
          const Dem_IndicatorIdxType IndicatorClassIdxEnd =
            Dem_IndicatorGroups[IndicatorClassIdx + 1U];
          Dem_IndicatorIdxType Idx;

          for (Idx = IndicatorClassIdxStart; Idx < IndicatorClassIdxEnd; Idx++)
          {
            CONSTP2CONST(Dem_IndicatorClassType, AUTOMATIC, DEM_CONST)
              IndicatorClass = &Dem_IndicatorClasses[Idx];

            if (IndicatorClass->Enabled == TRUE)
            {
              const Dem_OperationCycleIdType FailureCycleId =
                Dem_GbiIndicatorFailureCycleIdx(EventId, Idx);
              const Dem_OperationCycleIdType HealingCycleId =
#if (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD)
                Dem_GbiIndicatorHealingCycleIdx(EventId, Idx);
#else
                /* indicator link uses the same healing cycle as the
                 * event operation cycle (this is checked in XDM file) */
                Dem_GbiOpCycleIdx(EventId);
#endif

              /* process only links where Indicator healing cycle
               * equals to current processed operation cycle */
              /* no need for concurrency protection here as concurrent ClearDTC
                 are harmless */
              /* !LINKSTO Dem.ASR40.SWS_Dem_00506, 1 */
              if (HealingCycleId == OperationCycleId)
              {
                Dem_ProcessIndicatorOffCriteria(Idx, EventId);
              }

              /* process only links where Indicator failure cycle
               * equals to current processed operation cycle */
              if (FailureCycleId == OperationCycleId)
              {
                const Dem_OperationCycleIdType EventOperationCycle =
                  Dem_GbiOpCycleIdx(EventId);

                /* !LINKSTO dsn.Dem.IndicatorCycleCounterConsistency,1 */
                /*
                 * ENTER critical section to protect consistency of counter and role,
                 * and the event status and memory
                 *       call-context: any
                 */
                DEM_ENTER_EXCLUSIVE_AREA();

                /* !LINKSTO dsn.Dem.ProcessFailureCycleCounter_ProcessCondition,1 */
                /* !LINKSTO Dem.IndicatorFailureCycle.CounterUpdateAndWIRSetting.SeparateCycle, 1 */
                if ( (FailureCycleId != EventOperationCycle) &&
                      DEM_IS_EV_ST_BIT_TF_SET(EventId) )
                {
                  /* !LINKSTO Dem.WarningIndicator.FailureCounterProcessing.SeparateCycle, 1 */
                  Dem_ProcessIndicatorOnCriteria(Idx, EventId);

                  if (Dem_CheckWIROnCriteriaFulfilled(Idx, EventId) == TRUE)
                  {
#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
                    Dem_EventMemoryEntryPtrType EvMemEntry = NULL_PTR;
                    Dem_SizeEvMemEntryType EvMemEntryIdx   = 0U;
                    boolean EntryFound = FALSE;
#endif
#if (DEM_NUM_CMB_DTCS > 0U)
                    const Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);

                    if (DEM_IS_DTC_COMBINED(DTCConfIdx))
                    {
                      /* Set WIR bit in the DTC combined status byte */
                      Dem_CmbDTCStatus[DTCConfIdx] |= DEM_UDS_STATUS_WIR;
                    }
#endif
                    /* Set WIR bit in the event status byte */
                    DEM_SET_EV_ST_MASK(EventId, DEM_UDS_STATUS_WIR);
#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
                    /* Set WIRSLC bit in the SI30 status byte */
                    Dem_SetWIRSLCForFoundEntry(&EvMemEntry, &EvMemEntryIdx, &EntryFound, EventId);
#endif
                  }
                }

                /*
                 * EXIT critical section
                 */
                DEM_EXIT_EXCLUSIVE_AREA();
              }
            }
          }
        }
      }
    }
  }
/* calibration is disabled and event availability is not considered */
#else
  {
    Dem_IndicatorIdxType LinkIdx;

    /* Deviation TASKING-1 */
    for (LinkIdx = 0U; LinkIdx < DEM_NUM_INDICATOR_LINKS; ++LinkIdx)
    {
      const Dem_EventIdType EventId = Dem_IndicatorLink[LinkIdx].EventId;
      const Dem_OperationCycleIdType FailureCycleId =
        Dem_GbiIndicatorFailureCycleIdx(EventId, LinkIdx);
      const Dem_OperationCycleIdType HealingCycleId =
#if (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD)
        Dem_GbiIndicatorHealingCycleIdx(EventId, LinkIdx);
#else
        /* indicator link uses the same healing cycle as the
         * event operation cycle (this is checked in XDM file) */
        Dem_GbiOpCycleIdx(EventId);
#endif

      /* process only links where Indicator healing cycle
       * equals to current processed operation cycle */
      /* !LINKSTO Dem.ASR40.SWS_Dem_00506, 1 */
      if (HealingCycleId == OperationCycleId)
      {
        Dem_ProcessIndicatorOffCriteria(LinkIdx, EventId);
      }

      /* process only links where Indicator failure cycle
       * equals to current processed operation cycle */
      if (FailureCycleId == OperationCycleId)
      {
        const Dem_OperationCycleIdType EventOperationCycle =
          Dem_GbiOpCycleIdx(EventId);

        /* !LINKSTO dsn.Dem.ProcessFailureCycleCounter_ProcessCondition,1 */
        /* !LINKSTO Dem.IndicatorFailureCycle.CounterUpdateAndWIRSetting.SeparateCycle, 1 */
        if (FailureCycleId != EventOperationCycle)
        {
          /* !LINKSTO dsn.Dem.IndicatorCycleCounterConsistency,1 */
          /*
           * ENTER critical section to protect consistency of counter and roleand role,
           * and the event status and memory
           *       call-context: any
           */
          DEM_ENTER_EXCLUSIVE_AREA();

          if (DEM_IS_EV_ST_BIT_TF_SET(EventId))
          {
            /* !LINKSTO Dem.WarningIndicator.FailureCounterProcessing.SeparateCycle, 1 */
            Dem_ProcessIndicatorOnCriteria(LinkIdx, EventId);

            if (Dem_CheckWIROnCriteriaFulfilled(LinkIdx, EventId) == TRUE)
            {
#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
              Dem_EventMemoryEntryPtrType EvMemEntry = NULL_PTR;
              Dem_SizeEvMemEntryType EvMemEntryIdx   = 0U;
              boolean EntryFound = FALSE;
#endif
#if (DEM_NUM_CMB_DTCS > 0U)
              const Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);

              if (DEM_IS_DTC_COMBINED(DTCConfIdx))
              {
                /* Set WIR bit in the DTC combined status byte */
                Dem_CmbDTCStatus[DTCConfIdx] |= DEM_UDS_STATUS_WIR;
              }
#endif
              /* Set WIR bit in the event status byte */
              DEM_SET_EV_ST_MASK(EventId, DEM_UDS_STATUS_WIR);
#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
              /* Set WIRSLC bit in the SI30 status byte */
              Dem_SetWIRSLCForFoundEntry(&EvMemEntry, &EvMemEntryIdx, &EntryFound, EventId);
#endif
            }
          }

          /*
           * LEAVE critical section
           */
          DEM_EXIT_EXCLUSIVE_AREA();
        }
      }
    }
  }
#endif /* DEM_CALIBRATION_SUPPORT == STD_ON */

  DBG_DEM_PROCESSINDICATOR_EXIT(OperationCycleId);
}

STATIC FUNC(void, DEM_CODE) Dem_ProcessIndicatorOffCriteria(
  Dem_IndicatorIdxType IndicatorIdx,
  Dem_EventIdType      EventId)
{

  DBG_DEM_PROCESSINDICATOROFFCRITERIA_ENTRY(IndicatorIdx, EventId);

  if (!DEM_IS_ANY_EV_ST_BIT_SET(EventId,
                                DEM_UDS_STATUS_TNCTOC |
                                DEM_UDS_STATUS_TFTOC))
  {
    /* the event was tested and qualified only as passed in the current
     * operation cycyle */

#if (DEM_CALIBRATION_SUPPORT == STD_ON)
    CONSTP2CONST(Dem_IndicatorClassType, AUTOMATIC, DEM_CONST) IndicatorClass =
      &Dem_IndicatorClasses[IndicatorIdx];
    const Dem_IndicatorIdType IndicatorId = IndicatorClass->IndicatorId;
    /* even if CounterDataIdx is of smaller type than EventId the cast is ok
     * because size of Dem_CounterDataIdxType depends on the amount of events in
     * the system */
    const Dem_CounterDataIdxType CounterDataIdx = (Dem_CounterDataIdxType)EventId;

#if ( (DEM_MILGROUP_SUPPORT == STD_ON) || \
      ((defined DEM_MIL_ID) && (DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON)) )
    boolean IsMIL = (IndicatorId == DEM_MIL_ID) ? TRUE : FALSE;
#endif

#if (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD)
    const Dem_IndicatorCycleCounterType HealingCycleThreshold =
        IndicatorClass->HealingCycleThreshold;
#endif /* DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD */

#else
    const Dem_CounterDataIdxType CounterDataIdx =
      (Dem_CounterDataIdxType)IndicatorIdx;
    const Dem_IndicatorIdType IndicatorId = DEM_INDICATOR_DEFAULT_COUNTER;

#if ( (DEM_MILGROUP_SUPPORT == STD_ON) || \
      ((defined DEM_MIL_ID) && (DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON)) )
    const uint32 IndMILStart = Dem_IndicatorDesc[DEM_MIL_ID].StartIdx;
    const uint32 IndMILEnd = IndMILStart + Dem_IndicatorDesc[DEM_MIL_ID].Number;

    boolean IsMIL = ((IndicatorIdx >= IndMILStart) && (IndicatorIdx < IndMILEnd)) ? TRUE : FALSE;
#endif

#if (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD)
    /* these are only needed in case of healing counter, however we're prefetching
       the values so that that is done outside the critical section */
    const Dem_HealingCycleCounterInfoIdxType HealingCycleCounterInfoIdx =
      Dem_IndicatorLink[IndicatorIdx].HealingCycleCounterInfoIdx;
    const Dem_IndicatorCycleCounterType HealingCycleThreshold =
      Dem_HealingCycleCounterInfo[HealingCycleCounterInfoIdx].Threshold;
#endif /* DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD */
#endif /* DEM_CALIBRATION_SUPPORT == STD_ON */

#if ((defined DEM_MIL_ID) && (DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON))
    boolean IsPassedCycle = TRUE;
    Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);

    if (IsMIL && DEM_IS_DTC_COMBINED(DTCConfIdx))
    {
      /* if OBDonUDS combination is enabled, the common MIL is processed only if
       * all events of the combination are tested and qualified only as passed
       * in the current operation cycle */
      IsPassedCycle = !DEM_IS_CMB_ST_BIT_SET_IN_DTC(DTCConfIdx,
                                             DEM_UDS_STATUS_TNCTOC |
                                             DEM_UDS_STATUS_TFTOC);
    }

    /* the processing continues only if the initial condition wrt individual or
     * combined DTCStatus are met */
    if (IsPassedCycle)
#endif
    {
#if (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD)
      boolean Continue = FALSE;
      /* !LINKSTO dsn.Dem.OBDonUDS.EventCombination.MIL.CommonHealingCounter,1 */
      P2VAR(Dem_IndicatorCycleCounterType, AUTOMATIC, DEM_VAR) CounterPtr =
        &(DEM_INDICATOR_CYC_COUNTER[IndicatorId][CounterDataIdx]);
#endif /* DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD */

      Dem_IndicatorCounterDataRoleType IndicatorCounterDataRole =
        DEM_INDICATORCOUNTER_ROLE_FAILURE_CYCLE_COUNTER;

#if ( (DEM_MILGROUP_SUPPORT == STD_ON) || \
      (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD) )
      boolean IsWIRSet;
#endif

#if (DEM_MILGROUP_SUPPORT == STD_ON)
      boolean IsResetAllowed = TRUE;
      Dem_MILGroupIndexType MILGroupIndex = DEM_MILGROUP_GROUP_IDX_INVALID;
      if (IsMIL)
      {
        MILGroupIndex = Dem_GbiMILGroupIndex(EventId);
      }
#endif

      /*
       * ENTER critical section to protect consistency of Bit read/set and counter value
       *       call-context: any
       */
      DEM_ENTER_EXCLUSIVE_AREA();

#if ( (DEM_MILGROUP_SUPPORT == STD_ON) || \
      (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD) )
      IsWIRSet = DEM_IS_BIT_SET_IN_ARRAY(
                   DEM_INDICATOR_CYC_COUNTER_WIR_STATUS[IndicatorId],
                   CounterDataIdx);
#endif

#if (DEM_MILGROUP_SUPPORT == STD_ON)
      /* check if the event is assigned to a MIL group when the WIR is not set */
      if ( (!IsWIRSet) &&
           (MILGroupIndex != DEM_MILGROUP_GROUP_IDX_INVALID) )
      {
        /* !LINKSTO Dem.MILGroup.RestartCountingAfterPassedCycle,1 */
        IsResetAllowed = Dem_MILGroupCheckPassedCycleAll(EventId,
                                                         MILGroupIndex);
      }

      /* in case of the MIL group events, changing the indicator role to HEALING
       * and resetting the indicator counter is allowed only if the WIR.C is set
       * or if all other events in the MIL group have been reported as passed */
      if (IsWIRSet || IsResetAllowed)
#endif
      {
#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
        /* could be optimized to fetch the byte address outside the critical section */
        if (!DEM_IS_BIT_SET_IN_ARRAY(
             DEM_INDICATOR_CYC_COUNTER_ROLE[IndicatorId], CounterDataIdx))
        {
          IndicatorCounterDataRole = DEM_INDICATORCOUNTER_ROLE_HEALING_CYCLE_COUNTER;

          Dem_SetCycleCounterRole(IndicatorId, CounterDataIdx, IndicatorCounterDataRole);
          /* resetting the indicator link cycle counter is not necessary, because
           * the role changed and only OCC2 is used for healing functionality */
        }
#else
        if (!DEM_IS_BIT_SET_IN_ARRAY(
             DEM_INDICATOR_CYC_COUNTER_ROLE[IndicatorId], CounterDataIdx))
        {
          IndicatorCounterDataRole = DEM_INDICATORCOUNTER_ROLE_HEALING_CYCLE_COUNTER;

          Dem_SetCycleCounterRole(IndicatorId, CounterDataIdx, IndicatorCounterDataRole);
          DEM_INDICATOR_CYC_COUNTER[IndicatorId][CounterDataIdx] = 0U;
        }

        if (IsWIRSet == TRUE)
        {
          if((*CounterPtr) < HealingCycleThreshold)
          {
            *CounterPtr = (*CounterPtr) + 1U;
          }
          if((*CounterPtr) >= HealingCycleThreshold)
          {
            DEM_CLR_BIT_IN_ARRAY(DEM_INDICATOR_CYC_COUNTER_WIR_STATUS[IndicatorId],
                                 CounterDataIdx);
          }
          Continue = TRUE;
        }

#endif /* DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD */
      }

      /*
       * LEAVE critical section
       */
      DEM_EXIT_EXCLUSIVE_AREA();

#if (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD)
      if (Continue == TRUE)
      {
        /* defensive check to capture recalibrated configuration threshold */
        if (DEM_INDICATOR_CYC_COUNTER[IndicatorId][CounterDataIdx] >= HealingCycleThreshold)
        {
          /* due to the check for WIR.C performed above it is not necessary to check for
           * the WIR bit to be set (an indicator active can not be if the WIR bit is not set) */
#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)
#if ((DEM_MILGROUP_SUPPORT == STD_OFF) && (DEM_OBDONUDS_COMBINATION_ENABLED == STD_OFF))
#if (DEM_CALIBRATION_SUPPORT == STD_ON)
          boolean IsMIL = (IndicatorId == DEM_MIL_ID) ? TRUE : FALSE;
#else
          const uint32 IndMILStart = Dem_IndicatorDesc[DEM_MIL_ID].StartIdx;
          const uint32 IndMILEnd = IndMILStart + Dem_IndicatorDesc[DEM_MIL_ID].Number;
          boolean IsMIL = ((IndicatorIdx >= IndMILStart) && (IndicatorIdx < IndMILEnd)) ? TRUE : FALSE;
#endif
#endif /* (DEM_MILGROUP_SUPPORT == STD_OFF) && (DEM_OBDONUDS_COMBINATION_ENABLED == STD_OFF) */
          /* !LINKSTO Dem_OBD_0023,4 */
          /* remove permanent entry in case the MIL is not requested anymore */
          if (IsMIL)
          {
#if (DEM_NUM_CMB_DTCS > 0U)
            /* !LINKSTO dsn.Dem.OBD.PermanentMemory.EventCombination.Removal,1 */
            /* check if MIL indicator of combined events is active */
            if (Dem_IsCmbEventsMILIndicatorActive(EventId) == FALSE)
#endif
            {
              /*
               * ENTER critical section to protect the permanent memory
               */
              DEM_ENTER_EXCLUSIVE_AREA();

              Dem_PermanentMemoryRemoveEntry(EventId);

              /*
               * LEAVE critical section
               */
              DEM_EXIT_EXCLUSIVE_AREA();
            }
          }
#endif /* DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U */

          /* in case of calibration IndicatorClassIdx was already checked before */
          if (Dem_CheckWIROffCriteriaFulfilled(EventId) == TRUE)
          {
#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
            const Dem_DTCStatusMaskType OldDTCStatusMask = DEM_DTC_STATUS_MASKS[EventId];
#endif
#if (DEM_NUM_CMB_DTCS > 0U)
            Dem_DTCConfIdxType DTCConfgIdx = Dem_GbiDTCConfIdx(EventId);
            Dem_EventStatusExtendedType OldCombinedStatus = 0U;
            Dem_EventStatusExtendedType NewCombinedStatus = 0U;
#endif
            /* !LINKSTO Dem.ASR42.SWS_Dem_00835,1 */
#if (DEM_USER_CTRL_WIR_SUPPORT == STD_ON)
            /* allow the reset only if the user controlled WIR-bit for current event is reset */
            if (!DEM_IS_USER_CTRL_WIR_SET(EventId))
#endif
            {
              DEM_ATOMIC_CLR_EV_ST_MASK(EventId, DEM_UDS_STATUS_WIR);
            }
            /*
             * ENTER critical section
             */
            DEM_ENTER_EXCLUSIVE_AREA();
#if (DEM_NUM_CMB_DTCS > 0U)
            /* if event is combined, update the combined DTC status */
            if (DEM_IS_DTC_COMBINED(DTCConfgIdx))
            {
              OldCombinedStatus = Dem_CmbDTCStatus[DTCConfgIdx];
              NewCombinedStatus = Dem_CalculateCmbDTCStatus(DTCConfgIdx, FALSE);
            }
#endif
            /*
             * LEAVE critical section
             */
            DEM_EXIT_EXCLUSIVE_AREA();
#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
            /* notify application as WIR-bit has changed */
            Dem_CbTriggerOnEventStatus(EventId, OldDTCStatusMask,
                                       DEM_DTC_STATUS_MASKS[EventId]);
#endif
#if (DEM_NUM_CMB_DTCS > 0U)
            Dem_InternalCheckOnCmbDTCStatusChange(EventId, OldCombinedStatus, NewCombinedStatus);
#endif
          }
        }
      }
#endif /* DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD */
    }
  }

  DBG_DEM_PROCESSINDICATOROFFCRITERIA_EXIT(IndicatorIdx, EventId);
}

FUNC(void, DEM_CODE) Dem_ProcessIndicatorOnCriteria(
  Dem_IndicatorIdxType IndicatorIdx,
  Dem_EventIdType      EventId)
{
#if (DEM_CALIBRATION_SUPPORT == STD_ON)
  CONSTP2CONST(Dem_IndicatorClassType, AUTOMATIC, DEM_CONST) IndicatorClass =
    &Dem_IndicatorClasses[IndicatorIdx];
  /* even if CounterDataIdx is of smaller type than EventId the cast is ok
   * because size of Dem_CounterDataIdxType depends on the amount of events in
   * the system */
  const Dem_CounterDataIdxType CounterDataIdx = (Dem_CounterDataIdxType)EventId;
  const Dem_IndicatorCycleCounterType FailureCycleThreshold =
    DEM_GET_CALIBRATED_FAILURECYCLE_THRESHOLD(EventId, IndicatorClass);
  const Dem_IndicatorIdType IndicatorId = IndicatorClass->IndicatorId;
#else
  const Dem_CounterDataIdxType CounterDataIdx =
      (Dem_CounterDataIdxType)IndicatorIdx;
  const Dem_FailureCycleCounterInfoIdxType FailureCycleCounterInfoIdx =
    Dem_IndicatorLink[IndicatorIdx].FailureCycleCounterInfoIdx;
  const Dem_IndicatorIdType IndicatorId = DEM_INDICATOR_DEFAULT_COUNTER;
  const Dem_IndicatorCycleCounterType FailureCycleThreshold =
    Dem_FailureCycleCounterInfo[FailureCycleCounterInfoIdx].Threshold;
#endif /* DEM_CALIBRATION_SUPPORT == STD_ON */

  CONSTP2VAR(Dem_IndicatorCycleCounterType, AUTOMATIC, DEM_VAR) CycleCounter =
    DEM_INDICATOR_CYC_COUNTER[IndicatorId];

  Dem_IndicatorCounterDataRoleType IndicatorCounterDataRole =
    (DEM_IS_BIT_SET_IN_ARRAY(DEM_INDICATOR_CYC_COUNTER_ROLE[IndicatorId], CounterDataIdx) ?
      DEM_INDICATORCOUNTER_ROLE_HEALING_CYCLE_COUNTER :
      DEM_INDICATORCOUNTER_ROLE_FAILURE_CYCLE_COUNTER);

  DBG_DEM_PROCESSINDICATORONCRITERIA_ENTRY(IndicatorIdx, EventId);

#if (DEM_CALIBRATION_SUPPORT == STD_OFF)
  TS_PARAM_UNUSED(EventId);
#endif

  if (IndicatorCounterDataRole != DEM_INDICATORCOUNTER_ROLE_FAILURE_CYCLE_COUNTER)
  {
    IndicatorCounterDataRole = DEM_INDICATORCOUNTER_ROLE_FAILURE_CYCLE_COUNTER;

    Dem_SetCycleCounterRole(IndicatorId, CounterDataIdx, IndicatorCounterDataRole);
    CycleCounter[CounterDataIdx] = 0U;
  }

  if (CycleCounter[CounterDataIdx] < FailureCycleThreshold)
  {
#if (DEM_MILGROUP_SUPPORT == STD_ON)
    /* !LINKSTO dsn.Dem.MILGroup.FailureCounterProcessing,1 */
    /* handle the MIL group event failure counter within the MIL group */
    if (Dem_MILGroupProcessCounter(&(CycleCounter[CounterDataIdx]),
                                   EventId,
                                   IndicatorIdx,
                                   DEM_MILGROUP_MIL_COUNTER_UPDATE) == FALSE)
#endif
    {
      CycleCounter[CounterDataIdx]++;
    }
  }

  DBG_DEM_PROCESSINDICATORONCRITERIA_EXIT(IndicatorIdx, EventId);
}

#if ((defined DEM_MIL_ID) && (DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON))
/*------------[Dem_ProcessCommonMILOnCriteria]------------------------------*/

FUNC(void, DEM_CODE) Dem_ProcessCommonMILOnCriteria(
  Dem_IndicatorIdxType IndicatorIdx,
  Dem_EventIdType      EventId)
{
  DBG_DEM_PROCESSCOMMONMILONCRITERIA_ENTRY(IndicatorIdx, EventId);

  if (!DEM_IS_CMB_ST_BIT_SET(EventId, DEM_UDS_STATUS_TFTOC))
  {
#if (DEM_CALIBRATION_SUPPORT == STD_OFF)
    const uint32 IndMILStart = Dem_IndicatorDesc[DEM_MIL_ID].StartIdx;
    const uint32 IndMILEnd = IndMILStart + Dem_IndicatorDesc[DEM_MIL_ID].Number;
#endif

#if (DEM_CALIBRATION_SUPPORT == STD_ON)
    CONSTP2CONST(Dem_IndicatorClassType, AUTOMATIC, DEM_CONST) IndicatorClass =
      &Dem_IndicatorClasses[IndicatorIdx];
    /* even if CounterDataIdx is of smaller type than EventId the cast is ok
     * because size of Dem_CounterDataIdxType depends on the amount of events in
     * the system */
    const Dem_CounterDataIdxType CounterDataIdx = (Dem_CounterDataIdxType)EventId;
    const Dem_IndicatorCycleCounterType FailureCycleThreshold =
      DEM_GET_CALIBRATED_FAILURECYCLE_THRESHOLD(EventId, IndicatorClass);
    const Dem_IndicatorIdType IndicatorId = IndicatorClass->IndicatorId;
#else
    const Dem_CounterDataIdxType CounterDataIdx =
        (Dem_CounterDataIdxType)IndicatorIdx;
    const Dem_FailureCycleCounterInfoIdxType FailureCycleCounterInfoIdx =
      Dem_IndicatorLink[IndicatorIdx].FailureCycleCounterInfoIdx;
    const Dem_IndicatorIdType IndicatorId = DEM_INDICATOR_DEFAULT_COUNTER;
    const Dem_IndicatorCycleCounterType FailureCycleThreshold =
      Dem_FailureCycleCounterInfo[FailureCycleCounterInfoIdx].Threshold;
#endif /* DEM_CALIBRATION_SUPPORT == STD_ON */

    CONSTP2VAR(Dem_IndicatorCycleCounterType, AUTOMATIC, DEM_VAR) CycleCounter =
      DEM_INDICATOR_CYC_COUNTER[IndicatorId];

    Dem_EventIdType MasterEventId = DEM_GET_MASTER_EVID(EventId);
    Dem_IndicatorCounterDataRoleType MasterMILCounterDataRole;
    P2VAR(Dem_IndicatorCycleCounterType, AUTOMATIC, DEM_VAR) MasterCycleCounter;

#if (DEM_CALIBRATION_SUPPORT == STD_ON)
    const Dem_CounterDataIdxType MasterCounterDataIdx =
      (Dem_CounterDataIdxType)MasterEventId;
    const Dem_IndicatorIdType MILIndId = DEM_MIL_ID;
#else
    Dem_CounterDataIdxType MasterCounterDataIdx;
    const Dem_IndicatorIdType MILIndId = DEM_INDICATOR_DEFAULT_COUNTER;
    Dem_IndicatorIdxType LinkIdx = (Dem_IndicatorIdxType)IndMILStart;

    if (EventId == MasterEventId)
    {
      /* if the master event of the combination is the currently processed event,
       * then its counter data index was already determined */
      MasterCounterDataIdx = CounterDataIdx;
    }
    else
    {
      boolean MasterFound = FALSE;
      MasterCounterDataIdx = 0U;
      do
      {
        if (Dem_IndicatorLink[LinkIdx].EventId == MasterEventId)
        {
          MasterCounterDataIdx = (Dem_CounterDataIdxType)LinkIdx;
          MasterFound = TRUE;
        }
        LinkIdx++;
      } while ((MasterFound == FALSE) && (LinkIdx < IndMILEnd));
    }
#endif /* DEM_CALIBRATION_SUPPORT == STD_ON */

    /* !LINKSTO dsn.Dem.OBDonUDS.EventCombination.MIL.CommonFailureCounter,1 */
    MasterCycleCounter = DEM_INDICATOR_CYC_COUNTER[MILIndId];

    MasterMILCounterDataRole = (DEM_IS_BIT_SET_IN_ARRAY(
      DEM_INDICATOR_CYC_COUNTER_ROLE[MILIndId], MasterCounterDataIdx) ?
        DEM_INDICATORCOUNTER_ROLE_HEALING_CYCLE_COUNTER :
        DEM_INDICATORCOUNTER_ROLE_FAILURE_CYCLE_COUNTER);

    if (MasterMILCounterDataRole != DEM_INDICATORCOUNTER_ROLE_FAILURE_CYCLE_COUNTER)
    {
      Dem_CounterDataIdxType CmbCounterDataIdx;
#if (DEM_CALIBRATION_SUPPORT == STD_ON)
      const Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
      const Dem_CmbDTCEvLnkType LastCmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx + 1U] - 1U;
      Dem_CmbDTCEvLnkType CmbEvIdx;
      Dem_EventIdType CmbEventId;

      MasterMILCounterDataRole = DEM_INDICATORCOUNTER_ROLE_FAILURE_CYCLE_COUNTER;
      for (CmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx]; CmbEvIdx <= LastCmbEvIdx; CmbEvIdx++)
      {
        CmbEventId = Dem_CmbDTCEvents[CmbEvIdx];
        CmbCounterDataIdx= (Dem_CounterDataIdxType)CmbEventId;
        /* set the MIL counter role to failure, for all events in combination */
        Dem_SetCycleCounterRole(MILIndId, CmbCounterDataIdx, MasterMILCounterDataRole);
      }
#else
      MasterMILCounterDataRole = DEM_INDICATORCOUNTER_ROLE_FAILURE_CYCLE_COUNTER;
      for (LinkIdx = (Dem_IndicatorIdxType)IndMILStart; LinkIdx < IndMILEnd; ++LinkIdx)
      {
        if (DEM_GET_MASTER_EVID(Dem_IndicatorLink[LinkIdx].EventId) == MasterEventId)
        {
          CmbCounterDataIdx = (Dem_CounterDataIdxType)LinkIdx;
          /* set the MIL counter role to failure, for all events in combination */
          Dem_SetCycleCounterRole(MILIndId, CmbCounterDataIdx, MasterMILCounterDataRole);
        }
      }
#endif
      /* reset the common MIL failure counter */
      MasterCycleCounter[MasterCounterDataIdx] = 0U;
    }

    if (MasterCycleCounter[MasterCounterDataIdx] < FailureCycleThreshold)
    {
      MasterCycleCounter[MasterCounterDataIdx]++;
    }
    /* !LINKSTO dsn.Dem.OBDonUDS.EventCombination.MIL.FailureCounterSynchronization,1 */
    /* synchronize the MIL counter of the first failed event of the combination in the
     * current operation cycle with the processed MIL counter of the master event */
    CycleCounter[CounterDataIdx] = MasterCycleCounter[MasterCounterDataIdx];
  }
  else
  {
    TS_PARAM_UNUSED(IndicatorIdx);
  }

  DBG_DEM_PROCESSCOMMONMILONCRITERIA_EXIT(IndicatorIdx, EventId);
}
#endif /* (defined DEM_MIL_ID) && (DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON) */

FUNC(void, DEM_CODE) Dem_SetCycleCounterRole(
  Dem_IndicatorIdType              IndicatorId,
  Dem_CounterDataIdxType           CounterDataIdx,
  Dem_IndicatorCounterDataRoleType CounterDataRole)
{
  CONSTP2VAR(uint8, AUTOMATIC, DEM_VAR) Role =
    DEM_INDICATOR_CYC_COUNTER_ROLE[IndicatorId];

  DBG_DEM_SETCYCLECOUNTERROLE_ENTRY(IndicatorId, CounterDataIdx, CounterDataRole);

  /* no need to use atomic set bit because function is called only from
     critical section context */
  if (CounterDataRole == DEM_INDICATORCOUNTER_ROLE_HEALING_CYCLE_COUNTER)
  {
    DEM_SET_BIT_IN_ARRAY(Role, CounterDataIdx);
  }
  else
  {
    DEM_CLR_BIT_IN_ARRAY(Role, CounterDataIdx);
  }

  DBG_DEM_SETCYCLECOUNTERROLE_EXIT(IndicatorId, CounterDataIdx, CounterDataRole);
}

STATIC FUNC(boolean, DEM_CODE) Dem_CheckWIROffCriteriaFulfilled(
  Dem_EventIdType EventId)
{
  boolean Result = TRUE;

  DBG_DEM_CHECKWIROFFCRITERIAFULFILLED_ENTRY(EventId);

#if (DEM_CALIBRATION_SUPPORT == STD_ON)
  {
    /* validation of IndicatorClassIdx was done before calling this function */
    const Dem_IndicatorGrpIdxType IndicatorClassIdx =
      Dem_GbiIndicatorClassIndex(EventId);

    if (IndicatorClassIdx < DEM_INDICATOR_UNUSED)
    {
      const Dem_IndicatorIdxType IndicatorClassIdxStart =
        Dem_IndicatorGroups[IndicatorClassIdx];
      const Dem_IndicatorIdxType IndicatorClassIdxEnd =
        Dem_IndicatorGroups[IndicatorClassIdx + 1U];
      Dem_IndicatorIdxType Idx;

      for (Idx = IndicatorClassIdxStart; Idx < IndicatorClassIdxEnd; Idx++)
      {
        CONSTP2CONST(Dem_IndicatorClassType, AUTOMATIC, DEM_CONST) IndicatorClass =
          &Dem_IndicatorClasses[Idx];
        CONSTP2VAR(uint8, AUTOMATIC, DEM_VAR) CycleCounterWIR =
          DEM_INDICATOR_CYC_COUNTER_WIR_STATUS[IndicatorClass->IndicatorId];

        if ( (IndicatorClass->Enabled == TRUE) &&
             (DEM_IS_BIT_SET_IN_ARRAY(CycleCounterWIR, EventId)) )
        {
          /* one CycleCounterWIR bit of the event is not cleared yet */
          Result = FALSE;

          break;
        }
      }
    }
  }
/* calibration is disabled and event availability is not considered */
#else
  {
    Dem_IndicatorIdxType LinkIdx;
    CONSTP2VAR(uint8, AUTOMATIC, DEM_VAR) CycleCounterWIR =
      DEM_INDICATOR_CYC_COUNTER_WIR_STATUS[DEM_INDICATOR_DEFAULT_COUNTER];

    /* Deviation TASKING-1 */
    for (LinkIdx = 0U; LinkIdx < DEM_NUM_INDICATOR_LINKS; ++LinkIdx)
    {
      if (Dem_IndicatorLink[LinkIdx].EventId == EventId)
      {
        const Dem_CounterDataIdxType CounterDataIdx =
         (Dem_CounterDataIdxType)LinkIdx;

        if (DEM_IS_BIT_SET_IN_ARRAY(CycleCounterWIR, CounterDataIdx))
        {
          /* one CycleCounterWIR bit of the event is not cleared yet */
          Result = FALSE;

          break;
        }
      }
    }
  }
#endif /* DEM_CALIBRATION_SUPPORT == STD_ON */

  DBG_DEM_CHECKWIROFFCRITERIAFULFILLED_EXIT(Result, EventId);
  return Result;
}

FUNC(boolean, DEM_CODE) Dem_CheckWIROnCriteriaFulfilled(
  Dem_IndicatorIdxType IndicatorIdx,
  Dem_EventIdType      EventId)
{
  boolean Result = FALSE;

#if (DEM_CALIBRATION_SUPPORT == STD_ON)
  CONSTP2CONST(Dem_IndicatorClassType, AUTOMATIC, DEM_CONST) IndicatorClass =
    &Dem_IndicatorClasses[IndicatorIdx];
  const Dem_IndicatorIdType IndicatorId = IndicatorClass->IndicatorId;
  /* even if CounterDataIdx is of smaller type than EventId the cast is ok
   * because size of Dem_CounterDataIdxType depends on the amount of events in
   * the system */
  const Dem_CounterDataIdxType CounterDataIdx = (Dem_CounterDataIdxType)EventId;
  const Dem_IndicatorCycleCounterType FailureCounter =
    DEM_INDICATOR_CYC_COUNTER[IndicatorId][EventId];
  const Dem_IndicatorCycleCounterType FailureThreshold =
    DEM_GET_CALIBRATED_FAILURECYCLE_THRESHOLD(EventId, IndicatorClass);
#else
  const Dem_CounterDataIdxType CounterDataIdx = (Dem_CounterDataIdxType)IndicatorIdx;
  const Dem_IndicatorIdType IndicatorId = DEM_INDICATOR_DEFAULT_COUNTER;
  const Dem_FailureCycleCounterInfoIdxType FailureCycleCounterInfoIdx =
    Dem_IndicatorLink[IndicatorIdx].FailureCycleCounterInfoIdx;
  const Dem_IndicatorCycleCounterType FailureThreshold =
    Dem_FailureCycleCounterInfo[FailureCycleCounterInfoIdx].Threshold;
  const Dem_IndicatorCycleCounterType FailureCounter =
    DEM_INDICATOR_CYC_COUNTER[IndicatorId][CounterDataIdx];
#endif /* DEM_CALIBRATION_SUPPORT */

#if ( (defined DEM_MIL_ID) && \
      ((DEM_OPCYC_OBD_DCY_USED == STD_ON) || (DEM_MILGROUP_SUPPORT == STD_ON)) )
  boolean IsMIL;
#if (DEM_CALIBRATION_SUPPORT == STD_ON)
  IsMIL = (IndicatorId == DEM_MIL_ID) ? TRUE : FALSE;
#else
  const uint32 IndMILStart = Dem_IndicatorDesc[DEM_MIL_ID].StartIdx;
  const uint32 IndMILEnd = IndMILStart + Dem_IndicatorDesc[DEM_MIL_ID].Number;
  IsMIL = ((IndicatorIdx >= IndMILStart) && (IndicatorIdx < IndMILEnd)) ? TRUE : FALSE;
#endif
#endif /* (defined DEM_MIL_ID) */

  DBG_DEM_CHECKWIRONCRITERIAFULFILLED_ENTRY(IndicatorIdx, EventId);

  if (FailureCounter >= FailureThreshold)
  {
#if ( (DEM_OBD_Support == STD_ON) && (defined DEM_MIL_ID) )
    if ( (!IsMIL) || (Dem_MILActivationAllowed(EventId) == TRUE) )
#endif
    {
#if ( (DEM_MILGROUP_SUPPORT == STD_ON) && (defined DEM_MIL_ID) )
      Dem_MILGroupIndexType MILGroupIndex = Dem_GbiMILGroupIndex(EventId);

      if ( (IsMIL) &&
           (MILGroupIndex != DEM_MILGROUP_GROUP_IDX_INVALID) &&
           (!DEM_IS_BIT_SET_IN_ARRAY(DEM_INDICATOR_CYC_COUNTER_WIR_STATUS[IndicatorId],
                                       CounterDataIdx)) )
      {
        /* !LINKSTO Dem.MILGroup.RestartCountingAfterMILOn,1 */
        Dem_MILGroupResetGroupCounter(MILGroupIndex);
      }
#endif

      /* !LINKSTO Dem.MILGroup.MILOn,1 */
      /* !LINKSTO dsn.Dem.OBDonUDS.EventCombination.MIL.CommonMILStatus,1 */
      DEM_SET_BIT_IN_ARRAY(DEM_INDICATOR_CYC_COUNTER_WIR_STATUS[IndicatorId],
                           CounterDataIdx);
      Result = TRUE;

#if ( (defined DEM_MIL_ID) && (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U) )
      /* !LINKSTO Dem_OBD_0021,3 */
      /* !LINKSTO dsn.Dem.OBD.PermanentMemory.EventCombination.Storage,1 */
      /* !LINKSTO dsn.Dem.OBD.PermanentMemory.EventCombination.IdenticalObdDTC.Storage,1 */
      if (IsMIL)
      {
        (void)Dem_PermanentMemoryAddEntry(EventId);
      }
#endif
    }
  }

#if ((DEM_CALIBRATION_SUPPORT != STD_ON) && (!(defined DEM_MIL_ID)))
  TS_PARAM_UNUSED(EventId);
#endif

  DBG_DEM_CHECKWIRONCRITERIAFULFILLED_EXIT(Result, IndicatorIdx, EventId);

  return Result;
}
#endif /* (DEM_NUM_INDICATOR_LINKS > 0U) */

#if (DEM_MILGROUP_SUPPORT == STD_ON)
/*------------------[MIL group functions]-----------------------------------*/

FUNC(Dem_MILGroupIndexType, DEM_CODE) Dem_GbiMILGroupIndex(
  Dem_EventIdType EventId)
{
  Dem_MILGroupIndexType Result;

  DBG_DEM_GBIMILGROUPINDEX_ENTRY(EventId);

  Result = Dem_MILGroupIndexPerEvent[EventId];

  DBG_DEM_GBIMILGROUPINDEX_EXIT(Result, EventId);

  return Result;
}

STATIC FUNC(Dem_IndicatorCycleCounterType, DEM_CODE)
  Dem_MILGroupGetGroupCounter(Dem_MILGroupIndexType MILGroupIndex)
{
  Dem_IndicatorCycleCounterType Result = 0U;
  Dem_MILGroupEventIndexType MILGroupEventIndex;
  Dem_EventIdType MILGroupEventId;

  DBG_DEM_MILGROUPGETGROUPCOUNTER_ENTRY(MILGroupIndex);

  for (MILGroupEventIndex = Dem_MILGroupStartIndex[MILGroupIndex];
       MILGroupEventIndex < Dem_MILGroupStartIndex[MILGroupIndex + 1U];
       MILGroupEventIndex++)
  {
    MILGroupEventId = Dem_MILGroupEventId[MILGroupEventIndex];
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
    if (Dem_GbiEvAvailable(MILGroupEventId) == TRUE)
#endif
    {
      Dem_IndicatorIdxType IndicatorIdx;

      /* !LINKSTO dsn.Dem.MILGroup.MILGroupEvent,1 */
      /* Call Dem_IsMILEvent() to:
       * a) check if MIL indicator was removed from event through calibration
       * b) determine the IndicatorIdx */
      if (Dem_IsMILEvent(MILGroupEventId, &IndicatorIdx) == TRUE)
      {
#if (DEM_CALIBRATION_SUPPORT == STD_ON)
        /* even if CounterDataIdx is of smaller type than EventId the cast is
         * ok because size of Dem_CounterDataIdxType depends on the amount of
         * events in the system */
        const Dem_CounterDataIdxType CounterDataIdx =
          (Dem_CounterDataIdxType)MILGroupEventId;
        const Dem_IndicatorIdType IndicatorId = DEM_MIL_ID;
#else
        /* Deviation TASKING-9 */
        const Dem_CounterDataIdxType CounterDataIdx =
          (Dem_CounterDataIdxType)IndicatorIdx;
        const Dem_IndicatorIdType IndicatorId = DEM_INDICATOR_DEFAULT_COUNTER;
#endif
        /* check if MIL on is not requested */
        if (!DEM_IS_BIT_SET_IN_ARRAY(
             DEM_INDICATOR_CYC_COUNTER_WIR_STATUS[IndicatorId],
             CounterDataIdx))
        {
#if (DEM_CALIBRATION_SUPPORT == STD_ON)
          CONSTP2CONST(Dem_IndicatorClassType, AUTOMATIC, DEM_CONST)
              IndicatorClass = &Dem_IndicatorClasses[IndicatorIdx];
          const Dem_IndicatorCycleCounterType FailureThreshold =
            DEM_GET_CALIBRATED_FAILURECYCLE_THRESHOLD(MILGroupEventId, IndicatorClass);
#else
          const Dem_FailureCycleCounterInfoIdxType FailureCycleCounterInfoIdx =
            Dem_IndicatorLink[IndicatorIdx].FailureCycleCounterInfoIdx;
          const Dem_IndicatorCycleCounterType FailureThreshold =
            Dem_FailureCycleCounterInfo[FailureCycleCounterInfoIdx].Threshold;
#endif
          const Dem_IndicatorCycleCounterType FailureCounter =
            DEM_INDICATOR_CYC_COUNTER[IndicatorId][CounterDataIdx];
          if ( (FailureCounter < FailureThreshold) &&
               (FailureCounter > Result) )
          {
            /* update result with the highest FailedCounter that
             * doesn't request MIL on */
            Result = FailureCounter;
          }
        }
      }
    }
  }

  DBG_DEM_MILGROUPGETGROUPCOUNTER_EXIT(Result, MILGroupIndex);

  return Result;
}

STATIC FUNC(void, DEM_CODE) Dem_MILGroupCalcFirstFailedEventId(
  Dem_MILGroupIndexType MILGroupIndex)
{
  Dem_MILGroupEventIndexType MILGroupEventIndex;
  Dem_EventIdType MILGroupEventId;
  Dem_IndicatorCycleCounterType MaxFailureCounterInGroup = 0U;

  DBG_DEM_MILGROUPCALCFIRSTFAILEDEVENTID_ENTRY(MILGroupIndex);

  /* presume that no event from the group, that don't request MIL on, was
   * reported as failed in the current operation cycle */
  Dem_MILGroupFirstFailedEventId[MILGroupIndex] = DEM_MILGROUP_EVENT_NONE;

  for (MILGroupEventIndex = Dem_MILGroupStartIndex[MILGroupIndex];
       MILGroupEventIndex < Dem_MILGroupStartIndex[MILGroupIndex + 1U];
       MILGroupEventIndex++)
  {
    MILGroupEventId = Dem_MILGroupEventId[MILGroupEventIndex];

#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
    if (Dem_GbiEvAvailable(MILGroupEventId) == TRUE)
#endif
    {
      Dem_IndicatorIdxType IndicatorIdx;

      /* !LINKSTO dsn.Dem.MILGroup.MILGroupEvent,1 */
      /* Call Dem_IsMILEvent() to:
       * a) check if MIL indicator was removed from event through calibration
       * b) determine the IndicatorIdx */
      if (Dem_IsMILEvent(MILGroupEventId, &IndicatorIdx) == TRUE)
      {
#if (DEM_CALIBRATION_SUPPORT == STD_ON)
        /* even if CounterDataIdx is of smaller type than EventId the cast is
         * ok because size of Dem_CounterDataIdxType depends on the amount of
         * events in the system */
        const Dem_CounterDataIdxType CounterDataIdx =
          (Dem_CounterDataIdxType)MILGroupEventId;
        const Dem_IndicatorIdType IndicatorId = DEM_MIL_ID;
#else
        /* Deviation TASKING-9 */
        const Dem_CounterDataIdxType CounterDataIdx =
          (Dem_CounterDataIdxType)IndicatorIdx;
        const Dem_IndicatorIdType IndicatorId = DEM_INDICATOR_DEFAULT_COUNTER;
#endif
        /* check if MIL on is not requested */
        if (!DEM_IS_BIT_SET_IN_ARRAY(
               DEM_INDICATOR_CYC_COUNTER_WIR_STATUS[IndicatorId],
               CounterDataIdx))
        {
          const Dem_IndicatorCycleCounterType FailureCounter =
            DEM_INDICATOR_CYC_COUNTER[IndicatorId][CounterDataIdx];

          if ( (DEM_IS_EV_ST_BIT_TF_SET(MILGroupEventId)) &&
               (DEM_IS_EV_ST_BIT_TFTOC_SET(MILGroupEventId)) )
          {
            if (FailureCounter > MaxFailureCounterInGroup)
            {
              /* update the first failed event in the MIL group */
              Dem_MILGroupFirstFailedEventId[MILGroupIndex] = MILGroupEventId;
              /* update the max counter found in the MIL group */
              MaxFailureCounterInGroup = FailureCounter;
              /* update MIL group counter */
              Dem_MILGroupLastCalculatedCounter[MILGroupIndex] = FailureCounter;
            }
          }
        }
      }
    }
  }

  DBG_DEM_MILGROUPCALCFIRSTFAILEDEVENTID_EXIT(MILGroupIndex);
}

STATIC FUNC(void, DEM_CODE) Dem_MILGroupCalcAllFirstFailedEventId(void)
{
  Dem_MILGroupIndexType MILGroupIndex;

  DBG_DEM_MILGROUPCALCALLFIRSTFAILEDEVENTID_ENTRY();

  /* Deviation TASKING-1 */
  for (MILGroupIndex = 0U;
       MILGroupIndex < DEM_MILGROUP_NUM_GROUP;
       MILGroupIndex++)
  {
    Dem_MILGroupCalcFirstFailedEventId(MILGroupIndex);
  }

  DBG_DEM_MILGROUPCALCALLFIRSTFAILEDEVENTID_EXIT()
}

STATIC FUNC(boolean, DEM_CODE) Dem_MILGroupCheckPassedCycleAll(
  Dem_EventIdType       EventId,
  Dem_MILGroupIndexType MILGroupIndex)
{
  boolean Result = TRUE;
  Dem_MILGroupEventIndexType MILGroupEventIndex;
  Dem_EventIdType MILGroupEventId;

  DBG_DEM_MILGROUPCHECKPASSEDCYCLEALL_ENTRY(EventId, MILGroupIndex);

  for (MILGroupEventIndex = Dem_MILGroupStartIndex[MILGroupIndex];
       MILGroupEventIndex < Dem_MILGroupStartIndex[MILGroupIndex + 1U];
       MILGroupEventIndex++)
  {
    MILGroupEventId = Dem_MILGroupEventId[MILGroupEventIndex];

    /* the event that triggered the call of the function is known to be
     * tested and qualified as passed */
    if (MILGroupEventId != EventId)
    {
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
      if (Dem_GbiEvAvailable(MILGroupEventId) == TRUE)
#endif
      {
        if (DEM_IS_EV_ST_BIT_TNCTOC_SET(MILGroupEventId) ||
            DEM_IS_EV_ST_BIT_TFTOC_SET(MILGroupEventId))
        {
          Dem_IndicatorIdxType IndicatorIdx;

          /* !LINKSTO dsn.Dem.MILGroup.MILGroupEvent,1 */
          /* Call Dem_IsMILEvent() to:
           * a) check if MIL indicator was removed from event through calibration
           * b) determine the IndicatorIdx */
          if (Dem_IsMILEvent(MILGroupEventId, &IndicatorIdx) == TRUE)
          {
#if (DEM_CALIBRATION_SUPPORT == STD_ON)
            /* even if CounterDataIdx is of smaller type than EventId the cast is
             * ok because size of Dem_CounterDataIdxType depends on the amount of
             * events in the system */
            const Dem_CounterDataIdxType CounterDataIdx =
              (Dem_CounterDataIdxType)MILGroupEventId;
            const Dem_IndicatorIdType IndicatorId = DEM_MIL_ID;
#else
            /* Deviation TASKING-9 */
            const Dem_CounterDataIdxType CounterDataIdx =
              (Dem_CounterDataIdxType)IndicatorIdx;
            const Dem_IndicatorIdType IndicatorId = DEM_INDICATOR_DEFAULT_COUNTER;
#endif
            /* check if at least one event from the group, that doesn't request
             * MIL on, was not tested or reported as failed in the current
             * operation cycle */
            if (!DEM_IS_BIT_SET_IN_ARRAY(
                   DEM_INDICATOR_CYC_COUNTER_WIR_STATUS[IndicatorId],
                   CounterDataIdx))
            {
              Result = FALSE;
              break;
            }
          }
        }
      }
    }
  }

  DBG_DEM_MILGROUPCHECKPASSEDCYCLEALL_EXIT(Result, EventId, MILGroupIndex);

  return Result;
}

FUNC(void, DEM_CODE) Dem_MILGroupResetGroupCounter(
  Dem_MILGroupIndexType MILGroupIndex)
{
  Dem_MILGroupEventIndexType MILGroupEventIndex;
  Dem_EventIdType MILGroupEventId;

  DBG_DEM_MILGROUPRESETGROUPCOUNTER_ENTRY(MILGroupIndex);

  for (MILGroupEventIndex = Dem_MILGroupStartIndex[MILGroupIndex];
       MILGroupEventIndex < Dem_MILGroupStartIndex[MILGroupIndex + 1U];
       MILGroupEventIndex++)
  {
    MILGroupEventId = Dem_MILGroupEventId[MILGroupEventIndex];

#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
    if (Dem_GbiEvAvailable(MILGroupEventId) == TRUE)
#endif
    {
      Dem_IndicatorIdxType IndicatorIdx;

      /* !LINKSTO dsn.Dem.MILGroup.MILGroupEvent,1 */
      /* Call Dem_IsMILEvent() to:
       * a) check if MIL indicator was removed from event through calibration
       * b) determine the IndicatorIdx */
      if (Dem_IsMILEvent(MILGroupEventId, &IndicatorIdx) == TRUE)
      {
#if (DEM_CALIBRATION_SUPPORT == STD_ON)
        /* even if CounterDataIdx is of smaller type than EventId the cast is
         * ok because size of Dem_CounterDataIdxType depends on the amount of
         * events in the system */
        const Dem_CounterDataIdxType CounterDataIdx =
          (Dem_CounterDataIdxType)MILGroupEventId;
        const Dem_IndicatorIdType IndicatorId = DEM_MIL_ID;
#else
        /* Deviation TASKING-9 */
        const Dem_CounterDataIdxType CounterDataIdx =
          (Dem_CounterDataIdxType)IndicatorIdx;
        const Dem_IndicatorIdType IndicatorId = DEM_INDICATOR_DEFAULT_COUNTER;
#endif
        /* check if WIR.C is not set */
        if (!DEM_IS_BIT_SET_IN_ARRAY(
             DEM_INDICATOR_CYC_COUNTER_WIR_STATUS[IndicatorId],
             CounterDataIdx))
        {
          Dem_EventMemoryEntryPtrType EvMemEntry;
          Dem_SizeEvMemEntryType EvMemEntryIdx;

#if (DEM_CALIBRATION_SUPPORT == STD_ON)
          CONSTP2CONST(Dem_IndicatorClassType, AUTOMATIC, DEM_CONST)
              IndicatorClass = &Dem_IndicatorClasses[IndicatorIdx];
          const Dem_IndicatorCycleCounterType FailureThreshold =
            DEM_GET_CALIBRATED_FAILURECYCLE_THRESHOLD(MILGroupEventId, IndicatorClass);
#else
          const Dem_FailureCycleCounterInfoIdxType FailureCycleCounterInfoIdx =
            Dem_IndicatorLink[IndicatorIdx].FailureCycleCounterInfoIdx;
          const Dem_IndicatorCycleCounterType FailureThreshold =
            Dem_FailureCycleCounterInfo[FailureCycleCounterInfoIdx].Threshold;
#endif

          /* reset MIL indicator failure cycle counter */
          DEM_INDICATOR_CYC_COUNTER[IndicatorId][CounterDataIdx] = 0U;

          /* reset event failure cycle */
          if (Dem_SearchForEntry(MILGroupEventId,
                                 &EvMemEntry,
                                 &EvMemEntryIdx) == TRUE)
          {
#if ((DEM_NUM_CMB_DTCS > 0U) && (DEM_OBDONUDS_COMBINATION_ENABLED == STD_OFF))
            if (DEM_IS_EVENT_COMBINED(MILGroupEventId))
            {
              Dem_CmbDTCEvLnkType IndexOfCmbEv =
                Dem_GetFailureCounterIdxOfCmbEvent(MILGroupEventId);

              /* !LINKSTO dsn.Dem.MILGroup.ResetEventFailureCycleCounter,1 */
              /* check if event failure counter threshold is reached or not */
              if (DEM_CMBEV_FAILURE_CYC_COUNTER[IndexOfCmbEv] < FailureThreshold)
              {
                /* reset the failure counter of the combined event */
                DEM_CMBEV_FAILURE_CYC_COUNTER[IndexOfCmbEv] = 0U;
              }
            }
            else
#endif /* (DEM_NUM_CMB_DTCS > 0U) && (DEM_OBDONUDS_COMBINATION_ENABLED == STD_OFF) */
            {
              /* !LINKSTO dsn.Dem.MILGroup.ResetEventFailureCycleCounter,1 */
              /* check if event failure counter threshold is reached or not */
              if (EvMemEntry->EventFailureCycleCounter < FailureThreshold)
              {
                /* reset the event failure counter */
                EvMemEntry->EventFailureCycleCounter = 0U;
              }
            }
          }
#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF)
          else
          {
            /* get pointer to failure counter for regular & combined events */
            const Dem_StatusCounterPtrType FailureCounterPtr =
              Dem_GetStatusCounterReference(MILGroupEventId);

            /* !LINKSTO dsn.Dem.MILGroup.ResetEventFailureCycleCounter,1 */
            /* check if failure counter threshold is reached or not */
            if (*FailureCounterPtr < FailureThreshold)
            {
              /* reset the event failure counter */
              *FailureCounterPtr = 0U;
            }
          }
#endif /* (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF) */
        }
      }
    }
  }

  DBG_DEM_MILGROUPRESETGROUPCOUNTER_EXIT(MILGroupIndex);
}

STATIC FUNC(Dem_EventIdType, DEM_CODE) Dem_MILGroupGetFirstFailedEventId(
  Dem_MILGroupIndexType MILGroupIndex,
  Dem_EventIdType EventId,
  Dem_MILGroup_EventProcessingStateType ProcessingState)
{
  Dem_EventIdType Result;
  Dem_EventIdType CurrentFirstFailedEvent;

  DBG_DEM_MILGROUPGETFIRSTFAILEDEVENTID_ENTRY(MILGroupIndex,
                                              EventId,
                                              ProcessingState);

  CurrentFirstFailedEvent = Dem_MILGroupFirstFailedEventId[MILGroupIndex];

  /* check if an event was identified as first failed for the MIL group */
  if (CurrentFirstFailedEvent != DEM_MILGROUP_EVENT_NONE)
  {
    boolean IsRecalculationNeeded = FALSE;

#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
    /* check if the event is disabled */
    if (Dem_GbiEvAvailable(CurrentFirstFailedEvent) == FALSE)
    {
      IsRecalculationNeeded = TRUE;
    }
    else
#endif
    {
      /* check if the event was not reported as FAILED in this operation cycle */
      if (!DEM_IS_EV_ST_BIT_TFTOC_SET(CurrentFirstFailedEvent))
      {
        IsRecalculationNeeded = TRUE;

#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON)
        /* !LINKSTO dsn.Dem.MILGroup.NewCycleDuringEventProcessing,1 */
        if ( (ProcessingState == DEM_MILGROUP_ENTRY_ALLOCATION) &&
             (EventId == CurrentFirstFailedEvent) )
        {
          /* The entry allocation (if needed) is the last step, where the
           * MIL group counter could be processed and it is always done
           * asynchronously in the main function. Between the synchronous and
           * the asynchronous processing a new operation cycle could be started
           * which resets the TFTOC bit. This situation has to be detected to
           * avoid a recalculation of the "first failed event". This would cause
           * that the MIL group counter is incremented twice and that the
           * failure and the indicator counter are out of sync!
           */
          IsRecalculationNeeded = FALSE;
        }
        else
#endif
        {
          /* check if the event is a BSW event */
          if (Dem_GbiEventKind(CurrentFirstFailedEvent) == DEM_EVENT_KIND_BSW)
          {
            /* !LINKSTO dsn.Dem.MILGroup.FirstFailedBSWEvent1,1 */
            /* check if the event is present in the error queue with FAILED status */
            if (TRUE == Dem_CheckErrorQueueEntryForStatus(
                          CurrentFirstFailedEvent,
                          DEM_EVENT_STATUS_FAILED))
            {
              IsRecalculationNeeded = FALSE;
            }
            /* !LINKSTO dsn.Dem.MILGroup.FirstFailedBSWEvent1,1 */
            /* check if the event is present in the error queue with CONFIRMED status */
            else if (TRUE == Dem_CheckErrorQueueEntryForStatus(
                               CurrentFirstFailedEvent,
                               DEM_EVENT_STATUS_CONFIRMED))
            {
              IsRecalculationNeeded = FALSE;
            }
            else if ( (ProcessingState == DEM_MILGROUP_MIL_COUNTER_UPDATE) &&
                      (EventId == CurrentFirstFailedEvent) )
            {
              /* !LINKSTO dsn.Dem.MILGroup.FirstFailedBSWEvent2,1 */
              /* current processed event is the first failed and currently
               * Dem_ProcessIndicatorOnCriteria() is executed. At this point it is
               * unclear, if the FirstFailed is still set from the previous cycle
               * or if it was just set before in the current cycle:
               * If (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF) or if
               * an event entry exists, the FirstFailedEventId was already determined
               * in Dem_UpdateFailureCounterFirstFail()/Dem_IncrementFailureCounter()
               * which is called synchronously
               */
#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON)
               if (Dem_SearchForEntry(EventId, NULL_PTR, NULL_PTR) != FALSE)
#endif
               {
                 IsRecalculationNeeded = FALSE;
               }
            }
            else
            {
              /* do nothing */
            }
          }
        }
      }
    }

#if (DEM_CALIBRATION_SUPPORT == STD_ON)
    if (!IsRecalculationNeeded)
    {
      Dem_IndicatorIdxType IndicatorIdx;

      /* !LINKSTO dsn.Dem.MILGroup.MILGroupEvent,1 */
      if (Dem_IsMILEvent(CurrentFirstFailedEvent, &IndicatorIdx) == FALSE)
      {
        IsRecalculationNeeded = TRUE;
      }
    }
#endif

    if (IsRecalculationNeeded)
    {
      /* if event is disabled, not reported as failed in this operation cycle
       * or had the MIL indicator removed from event through calibration,
       * re-calculate the first failed event from the MIL group */
      Dem_MILGroupCalcFirstFailedEventId(MILGroupIndex);
    }
  }

  Result = Dem_MILGroupFirstFailedEventId[MILGroupIndex];

  DBG_DEM_MILGROUPGETFIRSTFAILEDEVENTID_EXIT(Result,
                                             MILGroupIndex,
                                             EventId,
                                             ProcessingState);

  return Result;
}

STATIC FUNC(boolean, DEM_CODE) Dem_MILGroupProcessCounter(
  P2VAR(Dem_IndicatorCycleCounterType, AUTOMATIC, DEM_APPL_DATA)
                                        FailureCycleCounterPtr,
  Dem_EventIdType                       EventId,
  Dem_IndicatorIdxType                  IndicatorIdx,
  Dem_MILGroup_EventProcessingStateType ProcessingState)
{
  boolean Result = FALSE;
  /* if the current function is called for an indicator (ProcessingState ==
   * DEM_MILGROUP_MIL_COUNTER_UPDATE), then ContinueProcessing variable will be
   *  reevaluated; if called for an event, its value will always be TRUE */
  boolean ContinueProcessing = TRUE;

  DBG_DEM_MILGROUPPROCESSCOUNTER_ENTRY(FailureCycleCounterPtr,
                                       EventId,
                                       IndicatorIdx,
                                       ProcessingState);

  /* check if this function was called for an indicator */
  if (ProcessingState == DEM_MILGROUP_MIL_COUNTER_UPDATE)
  {
#if (DEM_CALIBRATION_SUPPORT == STD_ON)
    CONSTP2CONST(Dem_IndicatorClassType, AUTOMATIC, DEM_CONST) IndicatorClass =
      &Dem_IndicatorClasses[IndicatorIdx];
    const Dem_IndicatorIdType IndicatorId = IndicatorClass->IndicatorId;

    ContinueProcessing = (IndicatorId == DEM_MIL_ID) ? TRUE : FALSE;
#else
    const uint32 indMILStart = Dem_IndicatorDesc[DEM_MIL_ID].StartIdx;
    const uint32 indMILEnd = indMILStart + Dem_IndicatorDesc[DEM_MIL_ID].Number;

    ContinueProcessing = ((IndicatorIdx >= indMILStart) &&
                          (IndicatorIdx < indMILEnd)) ? TRUE : FALSE;
#endif
  }

  /* if the function was called for an event, this variable is always TRUE */
  if (ContinueProcessing)
  {
    Dem_MILGroupIndexType MILGroupIndex = Dem_GbiMILGroupIndex(EventId);
    /* check if the event is assigned to a MIL group */
    if (MILGroupIndex != DEM_MILGROUP_GROUP_IDX_INVALID)
    {
      Dem_EventIdType FirstFailed =
        Dem_MILGroupGetFirstFailedEventId(MILGroupIndex, EventId, ProcessingState);

      if (FirstFailed == DEM_MILGROUP_EVENT_NONE)
      {
        /* no first failed event in the group until now */
        boolean CounterUpdateNeeded = TRUE;

        if (ProcessingState != DEM_MILGROUP_MIL_COUNTER_UPDATE)
        {
          /* !LINKSTO dsn.Dem.MILGroup.MILGroupEvent,1 */
          /* when function is called for an event, call Dem_IsMILEvent() to:
           * 1) check if the MIL was not removed from event through calibration
           * 2) determine the IndicatorIdx */
          if (Dem_IsMILEvent(EventId, &IndicatorIdx) == FALSE)
          {
            CounterUpdateNeeded = FALSE;
          }
        }

        if (CounterUpdateNeeded)
        {
#if (DEM_CALIBRATION_SUPPORT == STD_ON)
          /* even if CounterDataIdx is of smaller type than EventId the cast is
           * ok because size of Dem_CounterDataIdxType depends on the amount of
           * events in the system */
          const Dem_CounterDataIdxType CounterDataIdx =
            (Dem_CounterDataIdxType)EventId;
          const Dem_IndicatorIdType IndicatorId = DEM_MIL_ID;
#else
          const Dem_CounterDataIdxType CounterDataIdx =
            (Dem_CounterDataIdxType)IndicatorIdx;
          const Dem_IndicatorIdType IndicatorId = DEM_INDICATOR_DEFAULT_COUNTER;
#endif
          /* check if WIR.C is not set */
          if (!DEM_IS_BIT_SET_IN_ARRAY(
               DEM_INDICATOR_CYC_COUNTER_WIR_STATUS[IndicatorId],
               CounterDataIdx))
          {
            /* calculate and increase the current MIL group counter value */
            Dem_MILGroupLastCalculatedCounter[MILGroupIndex] =
              Dem_MILGroupGetGroupCounter(MILGroupIndex) + 1U;

            /* report the new MIL group counter value */
            *FailureCycleCounterPtr =
              Dem_MILGroupLastCalculatedCounter[MILGroupIndex];

            /* store the info regarding the first failed event in the group */
            Dem_MILGroupFirstFailedEventId[MILGroupIndex] = EventId;

            Result = TRUE;
          }
        }
      }
      else if (FirstFailed == EventId)
      {
        /* current event is first failed in the group, this operation cycle */
        *FailureCycleCounterPtr =
          Dem_MILGroupLastCalculatedCounter[MILGroupIndex];
        Result = TRUE;
      }
      else
      {
        /* first failed is another event from the MIL group */
         Result = TRUE;
      }
    }
  }

  DBG_DEM_MILGROUPPROCESSCOUNTER_EXIT(Result,
                                      FailureCycleCounterPtr,
                                      EventId,
                                      IndicatorIdx,
                                      ProcessingState);

  return Result;
}
#endif /* (DEM_MILGROUP_SUPPORT == STD_ON) */

#if ((DEM_OPERATION_CYCLE_PROCESSING == DEM_PROCESS_OPCYC_STATE) || \
     (DEM_OPERATION_CYCLE_PROCESSING == DEM_PROCESS_OPCYC_RESTART))
/*------------------[Dem_OpCycleProcessCycleEnd]----------------------------*/

STATIC FUNC(void, DEM_CODE) Dem_OpCycleProcessCycleEnd(
  Dem_OperationCycleIdType OperationCycleId)
{
  Dem_EventIdType EventId;
#if (DEM_MAR_SUPPORT == STD_ON)
  /* flag to indicate whether the MAR data must be updated in the current DCY */
  boolean UpdateMAR = TRUE;
#endif

  DBG_DEM_OPCYCLEPROCESSCYCLEEND_ENTRY(OperationCycleId);

#if (DEM_MAR_SUPPORT == STD_ON)
  /* !LINKSTO Dem.OBDonUDS.MAR.InhibitedDenCondition.NoMARDataUpdate,1 */
  if ( (DEM_GET_OBD_VARIANT() != DEM_OBD_VARIANT_OBDONUDS) ||
       (OperationCycleId != DEM_OPCYC_OBD_DCY_ID) ||
       (Dem_NvData.DenominatorStatus == DEM_IUMPR_DEN_STATUS_INHIBITED) )
  {
    UpdateMAR = FALSE;
  }
#endif

  /* check all events */
  /* Deviation TASKING-1 */
  for (EventId = 1U; EventId <= DEM_MAX_EVENTID; ++EventId)
  {
#if (DEM_MAR_SUPPORT == STD_ON)
    /* !LINKSTO Dem.OBDonUDS.MAR.MiniNumerator.NoIncrementOnPendingFaults,1 */
    /* !LINKSTO Dem.OBDonUDS.MAR.MiniDenominator.NoIncrementOnPendingFaults,1 */
    if ( (UpdateMAR == TRUE) &&
         (Dem_GbiDTCKind(EventId) == DEM_DTC_KIND_EMISSION_REL_DTCS) &&
         (DEM_IS_EV_ST_BIT_PDTC_SET(EventId)) )
    {
      UpdateMAR = FALSE;
    }
#endif

    /* only for events of this operation cycle */
    if (Dem_GbiOpCycleIdx(EventId) == OperationCycleId)
    {
      Dem_OpCycleProcessEventCycleEnd(EventId);
    }
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
    if (Dem_GbiEvAvailable(EventId) == FALSE)
    {
      /* event is disabled so the update of the event/DTC status
       * and trigger of StatusChanged callbacks shall be skipped */
    }
    else
#endif
    {
#if (DEM_NUM_FAILURECYCLES > 0U)
      /* for events with this failure cycle, reset the failure counter if
       * the event is tested and never failed this operation cycle */
      Dem_ProcessFailureCounterReset(EventId, OperationCycleId);
#endif
    }
  }
#if (DEM_NUM_CMB_DTCS > 0U)
  /* update the combined DTC status of changed combined DTCs.*/
  Dem_InitAllCmbDTCStatus(TRUE);
#endif

#if (DEM_OPCYCLE_CTRS_SUPPORT == STD_ON)
  /*
   * ENTER critical section
   */
  DEM_ENTER_EXCLUSIVE_AREA();

  /* !LINKSTO Dem.SWS_Dem_00773,1 */
  /* !LINKSTO Dem.SWS_Dem_00777,1 */
  /* !LINKSTO Dem.SWS_Dem_00781,1 */
  /* process the increment of operation cycle counters */
  Dem_CheckForIncrementOpCycleCounters(OperationCycleId);

  /*
   * LEAVE critical section
   */
  DEM_EXIT_EXCLUSIVE_AREA();
#endif /* DEM_OPCYCLE_CTRS_SUPPORT == STD_ON */

#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)
  /* !LINKSTO Dem_OBD_0022,2 */
  if (OperationCycleId == DEM_OPCYC_IGNITION_ID)
  {
    /* update NvM block only if permanent memory has been changed */
    if (Dem_EventMemoryPermanentUpdated == TRUE)
    {
      /* trigger update of permanent memory */
      /* the return value is ignored because negative response
       * can not be handled */
      /* !LINKSTO Dem_OBD_0009,2 */
      (void)NvM_WriteBlock(DEM_NVM_BLOCK_ID_PERMANENT, NULL_PTR);
    }
  }
#endif /* DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U */

#if (DEM_MAR_SUPPORT == STD_ON)
  if (UpdateMAR == TRUE)
  {
    /* invoke helper function used for updating MAR data */
    Dem_MarUpdateMARData();
  }
#endif

#if ((DEM_OBD_Support == STD_ON) && (DEM_USE_AGING == STD_ON) && (DEM_VCC_OCC5_USED == STD_ON) && (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD))
  if (OperationCycleId == DEM_OPCYC_WARMUP_ID)
  {
    Dem_SizeEvMemEntryType       EntryIdx;
    Dem_EventMemoryEntryPtrType  EvMemEntry;
    const Dem_EventMemoryEntryPtrType  PrimMemEntry = Dem_EventMem[DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U];

    /* ENTER critical section to protect event memory entry */
    DEM_ENTER_EXCLUSIVE_AREA();
    for (EntryIdx = 0U; EntryIdx < DEM_MAX_NUMBER_EVENT_ENTRY_PRI; ++EntryIdx)
    {
      EventId = PrimMemEntry[EntryIdx].EventId;
      EvMemEntry = &(PrimMemEntry[EntryIdx]);

      if (EventId != DEM_EVENT_ID_INVALID)
      {
        const Dem_DTCKindType DtcKind = Dem_GbiDTCKind(EventId);
        if (DtcKind == DEM_DTC_KIND_EMISSION_REL_DTCS)
        {
          const Dem_AgingCyclesType ObdAgingCycleCounterThreshold =
              Dem_GbiOBDAgingCycleCounterThreshold(EventId);
          const Dem_AgingCyclesType AgingCycleCounterThreshold =
              Dem_GbiNumAgingCycles(EventId);
          if ((DEM_OBD_AGING_ALLOWED(ObdAgingCycleCounterThreshold)) &&
              (EvMemEntry->OCC2 >= AgingCycleCounterThreshold) &&
              (EvMemEntry->OCC5 >= ObdAgingCycleCounterThreshold))
          {
            Dem_ProcessEventAging(EventId, EvMemEntry);
          }
        }
      }
    }
    /* LEAVE critical section */
    DEM_EXIT_EXCLUSIVE_AREA();
  }
#endif /*((DEM_OBD_Support == STD_ON) && (DEM_USE_AGING == STD_ON) && (DEM_VCC_OCC5_USED == STD_ON) && (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD))*/

  DBG_DEM_OPCYCLEPROCESSCYCLEEND_EXIT(OperationCycleId);
}

/*------------------[Dem_OpCycleProcessEventCycleEnd]-----------------------*/
STATIC FUNC(void, DEM_CODE) Dem_OpCycleProcessEventCycleEnd(
  Dem_EventIdType EventId)
{
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
  boolean IsEvtAvailable;
#endif
#if ( (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) || (DEM_NUM_CMB_DTCS > 0U) )
  Dem_DTCStatusMaskType OldDTCStatusMask = DEM_NO_EVENT_AVAILABLE;
  Dem_DTCStatusMaskType NewDTCStatusMask;
#endif

  DBG_DEM_OPCYCLEPROCESSEVENTCYCLEEND_ENTRY(EventId);

  /*
   * ENTER critical section
   */
  DEM_ENTER_EXCLUSIVE_AREA();

#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
  IsEvtAvailable = Dem_GbiEvAvailable(EventId);
  if (IsEvtAvailable == TRUE)
#endif
  {
#if ( (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) || (DEM_NUM_CMB_DTCS > 0U) )
  OldDTCStatusMask = DEM_DTC_STATUS_MASKS[EventId];
#endif

#if ((DEM_NUM_INDICATOR_LINKS > 0U) && \
     (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD))
  Dem_ProcessOCC2BasedHealing(EventId);
#endif

  /* test is complete, passed this operation cycle */
  if (!DEM_IS_ANY_EV_ST_BIT_SET(EventId,
                                DEM_UDS_STATUS_TNCTOC |
                                DEM_UDS_STATUS_TFTOC))
  {
#if (DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON)
    const Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
#endif
#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_SINGLE)
    /* the OBD freeze frame shall be cleared only, when PDTC changes from 1 -> 0
       and CDTC is not set. Therefore the status of CDTC (0) and PDTC (1) is
       checked here. */
    if ( (!DEM_IS_EV_ST_BIT_CDTC_SET(EventId)) &&
         DEM_IS_EV_ST_BIT_PDTC_SET(EventId)
       )
    {
      /* for multiple OBD FF the clear is not necessary */
      /* !LINKSTO Dem.OBD.SingleOBDFreezeFrame.ClearOnPDTCChange,1 */
      Dem_ClearSingleOBDFreezeFrame(EventId);
    }
#endif /* DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_SINGLE */
    /* clear "pending DTC" status bit */
    DEM_CLR_EV_ST_MASK(EventId, DEM_UDS_STATUS_PDTC);

#if (DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON)
    if (DEM_IS_DTC_COMBINED(DTCConfIdx))
    {
    /* For an event combined according to OBDonUDS,
       a passed cycle of each event can lead to a reset of the combined PDTC,
       regardless of if the events status is changed or not */
      DEM_SET_BIT_IN_ARRAY(Dem_CmbDTCFlags, DTCConfIdx);
    }
#endif
  }
  }
#if ( (DEM_NUM_CMB_DTCS > 0) && (DEM_EVENT_DISABLING_SUPPORT == STD_ON) )
  else
  {
    /* proceed with aging if given event or any other combined event is available */
    IsEvtAvailable = Dem_IsAnyEvAvailable(EventId);
  }
#endif
  /*
   * LEAVE critical section
   */
  DEM_EXIT_EXCLUSIVE_AREA();

#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
  if (IsEvtAvailable == TRUE)
#endif
  {
#if ((DEM_USE_AGING == STD_ON) && \
      (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD) )
    if (DEM_AGING_ALLOWED(EventId))
    {
#if (DEM_NUM_AGINGCYCLES > 0U)
      /* if aging cycle is not correct, skip updating aging counter. */
      /* !LINKSTO Dem.SWS_Dem_00985,1 */
      if ( Dem_GbiAgingCycleIdx(EventId) == DEM_NUM_AGINGCYCLES )
#endif
      {
        boolean UpdateAgingCounterCriteriaFulfilled = FALSE;
        /* initialize the mask for the end of the operation cycle check */
        uint8 AgingCriteriaMask = DEM_UDS_STATUS_TFTOC;
#if (DEM_NUM_CMB_DTCS > 0)
        const Dem_DTCConfIdxType DTCConfIdx_aging = Dem_GbiDTCConfIdx(EventId);
#endif

#if (DEM_AGING_REQUIRES_TESTED_CYCLE_SET_OPERATION_CYCLE_STATE == STD_ON)
        /* !LINKSTO dsn.Dem.InternalAging.DemAgingRequiresTestedCycleSetOperationCycleState.Enabled,1 */
        AgingCriteriaMask |= DEM_UDS_STATUS_TNCTOC;
#else
        /* process aging algorithm only if latest report of the event was done with
         * the state passed (TF bit is reseted) */
        /* !LINKSTO dsn.Dem.InternalAging.DemAgingRequiresTestedCycleSetOperationCycleState.Disabled,1 */
        AgingCriteriaMask |= DEM_UDS_STATUS_TF;
#endif

        /* !LINKSTO dsn.Dem.InternalAging.DemAgingBasedOnHealingCompletionSupport,1 */
        /* if aging based on healing completion feature is enabled, additionally the WIR
         * bit needs to be checked for the aging process to occur */
#if (DEM_AGING_BASED_ON_HEALING_COMPLETION_SUPPORT == STD_ON)
        AgingCriteriaMask |= DEM_UDS_STATUS_WIR;
#endif

#if (DEM_NUM_CMB_DTCS > 0)
        if (DEM_IS_DTC_COMBINED(DTCConfIdx_aging))
        {
          /* for combined events, aging should be calculated based on the combined status
           * update aging counter once for the master event */
          if (DEM_GET_MASTER_EVID(EventId) == EventId)
          {
            UpdateAgingCounterCriteriaFulfilled = !DEM_IS_CMB_ST_BIT_SET_IN_DTC(DTCConfIdx_aging, AgingCriteriaMask);
          }
        }
        else
#endif /* DEM_NUM_CMB_DTCS > 0 */
        {
          UpdateAgingCounterCriteriaFulfilled = !DEM_IS_ANY_EV_ST_BIT_SET(EventId, AgingCriteriaMask);
        }

        if (UpdateAgingCounterCriteriaFulfilled == TRUE)
        {
          /* process aging counter (may lead to status change) */
          (void)Dem_UpdateAgingCounter(EventId);
        }
      }
    }
    /* else: this event uses a different aging cycle, thus aging counter
             will be processed by Dem_SetAgingCycleState() OR aging is disabled */
#endif /* (DEM_USE_AGING == STD_ON) &&
          (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD) */

#if ( (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) || (DEM_NUM_CMB_DTCS > 0U) )
    NewDTCStatusMask = DEM_DTC_STATUS_MASKS[EventId];

    if (OldDTCStatusMask != NewDTCStatusMask)
    {
#if (DEM_NUM_CMB_DTCS > 0U)
      Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
#endif

#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
      /* notify application if event status has changed */
      Dem_CbTriggerOnEventStatus(
        EventId, OldDTCStatusMask, NewDTCStatusMask);
#endif

#if (DEM_NUM_CMB_DTCS > 0U)
      /* for combined event set a flag for its index for later status update */
      if (DEM_IS_DTC_COMBINED(DTCConfIdx))
      {
        /* set a flag corresponding to this EventId */
        DEM_ATOMIC_SET_BIT_IN_ARRAY_8(Dem_CmbDTCFlags, DTCConfIdx);
      }
#endif
    }
#endif /* (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) || (DEM_NUM_CMB_DTCS > 0U) */
  }

  DBG_DEM_OPCYCLEPROCESSEVENTCYCLEEND_EXIT(EventId);
}

#if (DEM_NUM_INDICATOR_LINKS > 0U)
#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)

STATIC FUNC(void, DEM_CODE) Dem_SetWIRSLCForFoundEntry(
  P2VAR(Dem_EventMemoryEntryPtrType, AUTOMATIC, AUTOMATIC)   FoundEntry,
  P2VAR(Dem_SizeEvMemEntryType, AUTOMATIC, AUTOMATIC)        FoundEntryIdx,
  P2VAR(Dem_SizeEvMemEntryType, AUTOMATIC, AUTOMATIC)        EntryFound,
  Dem_EventIdType                                            EventId)
{
  DBG_DEM_SETWIRSLCFORFOUNDENTRY_ENTRY(FoundEntry, FoundEntryIdx, EntryFound, EventId);
  /* search for DTC in event memory, if not already done */
#if ( !((DEM_NUM_FAILURECYCLES > 0U) && \
        (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON)) )
#if ( (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON) || \
      (DEM_VCC_OCC5_USED == STD_ON) )
  if (*EntryFound == FALSE)
#endif
#endif
  {
    *EntryFound =
      Dem_SearchForEntry(EventId, FoundEntry, FoundEntryIdx);
  }
  if (*EntryFound == TRUE)
  {
    /* set WarningIndicatorRequestedSinceLastClear bit */
    DEM_SET_MASK((*FoundEntry)->SI30, DEM_SI30_STATUS_WIR_SLC);
  }
  DBG_DEM_SETWIRSLCFORFOUNDENTRY_EXIT(FoundEntry, FoundEntryIdx, EntryFound, EventId);
}
#endif /* (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) */
#endif /* (DEM_NUM_INDICATOR_LINKS > 0U) */

/*------------------[Dem_OpCycleProcessCycleStart]--------------------------*/
STATIC FUNC(void, DEM_CODE) Dem_OpCycleProcessCycleStart(
  Dem_OperationCycleIdType OperationCycleId)
{
  Dem_EventIdType EventId = 1U;

#if (DEM_USE_CB_INIT_MONITOR == STD_ON)
    Dem_CbIndexType CbIdx = 0U;
#endif

  DBG_DEM_OPCYCLEPROCESSCYCLESTART_ENTRY(OperationCycleId);

#if (DEM_NUM_INDICATOR_LINKS > 0U)
  Dem_ProcessIndicator(OperationCycleId);
#endif

#if (DEM_OBD_Support == STD_ON) || (DEM_OPCYC_OBD_DCY_USED == STD_ON)
  /* !LINKSTO Dem_OBD_0024,2 */
  if (OperationCycleId == DEM_OPCYC_OBD_DCY_ID)
  {
#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U) && (DEM_OBD_Support == STD_ON)
    Dem_PermanentMemoryStatusUpdate();

    /* !LINKSTO Dem_OBD_0025,3 */
    if (Dem_EventMemoryPermanentUpdated == TRUE)
    {
      /* trigger update of permanent memory */
      /* the return value is ignored because negative response
       * can not be handled */
      /* !LINKSTO Dem_OBD_0009,2 */
      (void)NvM_WriteBlock(DEM_NVM_BLOCK_ID_PERMANENT, NULL_PTR);
    }
#endif

#if (DEM_OBDONUDS_SUPPORT)
    /* initialize DenominatorStatus when DCY starts */
    Dem_NvData.DenominatorStatus = DEM_IUMPR_DEN_STATUS_NOT_REACHED;
#endif
    /* !LINKSTO Dem.OperationCycleQualification.ResetQualification,1 */
    DEM_RESET_DCY_QUALIFICATION();

  }
#endif /* DEM_OBD_Support == STD_ON */

#if (defined DEM_OPCYC_WARMUP_ID)
  /* update warm-up cycle related counters */
  if (OperationCycleId == DEM_OPCYC_WARMUP_ID)
  {
    /*
     * ENTER critical section to protect OBDWarmupCycleCtr and NrWUCsWhileMILInactive
     *       call-context: Dem (Task)
     */
    DEM_ENTER_EXCLUSIVE_AREA();

    /* increment the warm-up cycle counter. The counters are incremented
     * each time, when a new operation cycle of type 'warm-up' is started.
     * the OBDWarmupCycleCtr counter can be read via PID $30 */
    Dem_IncrementWarmupCtr();

#if (DEM_OBD_CENTRALIZED_PID21_HANDLING == STD_OFF)
    /* increment the warm-up cycle since MIL was deactivated counter */
    Dem_ProcessWUCWhileMILIsDeactivated();
#endif

    /* LEAVE critical section */
    DEM_EXIT_EXCLUSIVE_AREA();

#if ((DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) && \
     (DEM_VCC_OCC5_USED == STD_ON))
    /* !LINKSTO VCC_DEM_Table_10,2 */
    /* !LINKSTO dsn.Dem.OBD.OCC5.Dem_IncrementAllOcc5.Wuc,1 */
    Dem_IncrementAllOcc5();
#endif
  }
#endif

  /* !LINKSTO dsn.Dem.ProcessEventsPerCycle.SplitEventsPerCriticalSection,1 */
  /* check all events */
  /* Deviation TASKING-2 */
  while (EventId <= DEM_MAX_EVENTID)
  {
#if (DEM_CB_EVST_CHANGED_OPCYC_START_SUPPORT == STD_ON)
    uint8 EventIdLastIdx = 0U;
    uint8 Index;
    Dem_DTCMaskChangedType DTCStatusChangedData[DEM_MAX_NUM_EVENTS_PER_CRITICAL_SECTION];
    Dem_DTCMaskChangedPtrType CurrentDTCStatusChangedData;
#endif

    /*
     * ENTER critical section to protect the event status and memory
     *       call-context: Rte (Task)
     */
    DEM_ENTER_EXCLUSIVE_AREA();

    do
    {
#if (DEM_CB_EVST_CHANGED_OPCYC_START_SUPPORT == STD_ON)
      CurrentDTCStatusChangedData = &DTCStatusChangedData[EventIdLastIdx];
      CurrentDTCStatusChangedData->OldStatusMask = DEM_DTC_STATUS_MASKS[EventId];
#endif

#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
      if (Dem_GbiEvAvailable(EventId) == FALSE)
      {
      /* event is disabled so the updating failing counter and
       * starting operation cycle for this event shall be skipped */
      }
      else
#endif
      {
        /* only for events of this operation cycle */
        if (Dem_GbiOpCycleIdx(EventId) == OperationCycleId)
        {
          Dem_OpCycleProcessEventCycleStart(EventId);
        }
        else
        {
#if (DEM_NUM_FAILURECYCLES > 0U)
          /* update failure counter for events with this failure cycle */
          Dem_UpdateFailureCounterCycleStart(EventId, OperationCycleId);
#endif
        }
      }

#if (DEM_CB_EVST_CHANGED_OPCYC_START_SUPPORT == STD_ON)
      CurrentDTCStatusChangedData->NewStatusMask = DEM_DTC_STATUS_MASKS[EventId];

      if (CurrentDTCStatusChangedData->OldStatusMask !=
          CurrentDTCStatusChangedData->NewStatusMask)
      {
        CurrentDTCStatusChangedData->EventId = EventId;
        ++EventIdLastIdx;
      }
#endif /* DEM_CB_EVST_CHANGED_OPCYC_START_SUPPORT == STD_ON */
      ++EventId;
    }
    /* Deviation TASKING-2 */
    while ( ((EventId % DEM_MAX_NUM_EVENTS_PER_CRITICAL_SECTION) != 0U) &&
            (EventId <= DEM_MAX_EVENTID)
          );
    /* loop necessary to condition the number of events processed in the one critical section */

    /*
     * LEAVE critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();

#if (DEM_CB_EVST_CHANGED_OPCYC_START_SUPPORT == STD_ON)
    for (Index = 0U; Index < EventIdLastIdx; Index++)
    {
      CurrentDTCStatusChangedData = &DTCStatusChangedData[Index];

      /* offline calibration cannot change the event availability at runtime,
       * proceed with callback notifications */
      /* notify application if event status has been changed */
      Dem_CbTriggerOnEventStatus(CurrentDTCStatusChangedData->EventId,
                                 CurrentDTCStatusChangedData->OldStatusMask,
                                 CurrentDTCStatusChangedData->NewStatusMask);
    }
#endif /* DEM_CB_EVST_CHANGED_OPCYC_START_SUPPORT == STD_ON */
  }

#if (DEM_USE_CB_INIT_MONITOR == STD_ON)
  /* loop through the CB table and initialize CBs related to current OpCycle */
  /* Deviation TASKING-1 */
  for (CbIdx = 0U; CbIdx < DEM_LOOKUP_TABLE_INIT_MONITOR_SIZE; CbIdx++)
  {
    Dem_EventIdType CurrentEventId = Dem_CbLookupTableInitMonitor[CbIdx];

#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
    /* if event is disabled via calibration so
     * the restart of monitor shall be skipped */
    if (Dem_GbiEvAvailable(CurrentEventId) == TRUE)
#endif
    {
      if (Dem_GbiOpCycleIdx(CurrentEventId) == OperationCycleId)
      {
        /* !LINKSTO Dem.ASR40.SWS_Dem_00376_Implicit1,1 */
        /* return value is ignored */
        (void) Dem_CbFuncPtrInitMonitor[CbIdx](DEM_INIT_MONITOR_RESTART);
      }
    }
  }
#endif /* (DEM_USE_CB_INIT_MONITOR == STD_ON) */

#if (DEM_NUM_CMB_DTCS > 0U)
  /* update the Combined DTC statuses of changed combined DTCs */
  Dem_InitAllCmbDTCStatus(FALSE);
#endif
#if ( (DEM_OBD_Support == STD_ON) && \
      (DEM_READINESS_CALCULATION_SUPPORT == STD_ON) )
  /* !LINKSTO dsn.Dem.ReadinessStatus.ComputationPerDCY,1 */
  if (OperationCycleId == DEM_OPCYC_OBD_DCY_ID)
  {
    Dem_RgpNotifyDCYStart();
  }
#endif

  DBG_DEM_OPCYCLEPROCESSCYCLESTART_EXIT(OperationCycleId);
}

/*------------------[Dem_OpCycleProcessEventCycleStart]---------------------*/

STATIC FUNC(void, DEM_CODE) Dem_OpCycleProcessEventCycleStart(
  Dem_EventIdType EventId)
{
#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
  Dem_EventMemoryEntryPtrType EvMemEntry;
  Dem_SizeEvMemEntryType EvMemEntryIdx;
#endif

#if (DEM_NUM_CMB_DTCS > 0U)
  Dem_DTCStatusMaskType OldDTCStatusMask;
  Dem_DTCStatusMaskType NewDTCStatusMask;
#endif

  DBG_DEM_OPCYCLEPROCESSEVENTCYCLESTART_ENTRY(EventId);

#if (DEM_NUM_CMB_DTCS > 0U)
  OldDTCStatusMask = DEM_DTC_STATUS_MASKS[EventId];
#endif

#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
  if (Dem_SearchForEntry(EventId, &EvMemEntry, &EvMemEntryIdx) == TRUE)
  {
    /* clear UnconfirmedDTCThisOperationCycle bit */
    DEM_CLR_MASK_8(
      EvMemEntry->SI30, DEM_SI30_STATUS_UNCONFIRMEDDTC_TOC);

    /* increment operation cycles since last unconfirmedDTC counter */
    if (EvMemEntry->OCC1 < 0xFFU)
    {
      ++(EvMemEntry->OCC1);
    }

    /* increment operation cycles since first unconfirmedDTC counter */
    if (EvMemEntry->OCC3 < 0xFFU)
    {
      ++(EvMemEntry->OCC3);
    }

    /* check if tested and not failed last OpCyc */
    /* bits are updated afterwards and contain values from last OpCyc */
    if (!DEM_IS_ANY_EV_ST_BIT_SET(EventId,
                                  DEM_UDS_STATUS_TNCTOC |
                                  DEM_UDS_STATUS_TFTOC))
    {
      /* reset consecutive failed operation cycle counter */
      EvMemEntry->OCC6 = 0U;
    }
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    /* !LINKSTO dsn.Dem.VCC.EventMemoryEntryChanged,4 */
    Dem_CheckForImmediateEntryStorage(EventId,
                                      EvMemEntry,
                                      EvMemEntryIdx,
                                      DEM_NVM_NO_FORCE);
#endif
  }
#endif /* DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD */

  /* set DTC status bit: "test not completed this operation cycle" */
  /* clear DTC status bit: "test failed this operation cycle" */
  DEM_CHNG_EV_ST_MASK(EventId,
                      DEM_UDS_STATUS_TNCTOC,
                      DEM_UDS_STATUS_TFTOC);

#if (DEM_NUM_CMB_DTCS > 0U)
  NewDTCStatusMask = DEM_DTC_STATUS_MASKS[EventId];
#endif

  /* reset debouncing counters for event */
  Dem_DebounceFctPtrTable[Dem_GbiDebounceAlgo(EventId)].ResetFct(EventId);

#if (DEM_NUM_CMB_DTCS > 0U)
  if (OldDTCStatusMask != NewDTCStatusMask)
  {
    const Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
    /* for combined event set a flag for its index for later status update */
    if (DEM_IS_DTC_COMBINED(DTCConfIdx))
    {
      /* set a flag corresponding to this EventId */
      DEM_SET_BIT_IN_ARRAY(Dem_CmbDTCFlags, DTCConfIdx);
    }
  }
#endif

  DBG_DEM_OPCYCLEPROCESSEVENTCYCLESTART_EXIT(EventId);
}

/*------------------[Dem_ProcessOCC2BasedHealing]---------------------------*/
#if ((DEM_NUM_INDICATOR_LINKS > 0U) && \
     (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD))
STATIC FUNC(void, DEM_CODE) Dem_ProcessOCC2BasedHealing(
  Dem_EventIdType EventId)
{
  Dem_EventMemoryEntryPtrType EvMemEntry;

  /* search for DTC in event memory */
  const boolean EntryExists =
    Dem_SearchForEntry(EventId, &EvMemEntry, NULL_PTR);

  DBG_DEM_PROCESSOCC2BASEDHEALING_ENTRY(EventId);

  if (EntryExists == TRUE)
  {
    boolean IndicatorLinkIsHealed = FALSE;
#if (DEM_CALIBRATION_SUPPORT == STD_ON)
    const Dem_IndicatorGrpIdxType IndicatorClassIdx =
      Dem_GbiIndicatorClassIndex(EventId);

    /* check for valid indicator index and prevent calibration error */
    if (IndicatorClassIdx < DEM_INDICATOR_UNUSED)
    {
      const Dem_IndicatorIdxType IndicatorClassIdxStart =
        Dem_IndicatorGroups[IndicatorClassIdx];
      const Dem_IndicatorIdxType IndicatorClassIdxEnd =
        Dem_IndicatorGroups[IndicatorClassIdx + 1U];
      Dem_IndicatorIdxType Idx;

      for (Idx = IndicatorClassIdxStart; Idx < IndicatorClassIdxEnd; Idx++)
      {
        CONSTP2CONST(Dem_IndicatorClassType, AUTOMATIC, DEM_CONST) IndicatorClass =
          &Dem_IndicatorClasses[Idx];

        if (IndicatorClass->Enabled == TRUE)
        {
          /* if indicator link uses the same healing cycle as the event operation
           * cycle and failure counter OCC2 has reached failure threshold */
          if (EvMemEntry->OCC2 >= IndicatorClass->HealingCycleThreshold)
          {
            const Dem_IndicatorIdType IndicatorId = IndicatorClass->IndicatorId;

            /* if the WIR bit related to indicator link is set */
            if (DEM_IS_BIT_SET_IN_ARRAY(
                  DEM_INDICATOR_CYC_COUNTER_WIR_STATUS[IndicatorId], EventId) )
            {
              IndicatorLinkIsHealed = TRUE;

              /* clear WIR bit related to indicator link */
              DEM_CLR_BIT_IN_ARRAY(
                DEM_INDICATOR_CYC_COUNTER_WIR_STATUS[IndicatorId],
                EventId);

#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)
              /* !LINKSTO Dem_OBD_0023,4 */
              /* remove permanent entry in case the MIL is not requested anymore */
              if (IndicatorId == DEM_MIL_ID)
              {
                /* critical section has been already entered in the caller
                 * function Dem_OpCycleProcessEventCycleEnd */
                Dem_PermanentMemoryRemoveEntry(EventId);
              }
#endif
            }
          }
        }
      }
    }
/* calibration is disabled and event availability is not considered */
#else
    {
      Dem_IndicatorIdxType LinkIdx;

      /* Deviation TASKING-1 */
      for (LinkIdx = 0U; LinkIdx < DEM_NUM_INDICATOR_LINKS; ++LinkIdx)
      {
        if (EventId == Dem_IndicatorLink[LinkIdx].EventId)
        {
          const Dem_HealingCycleCounterInfoIdxType
            HealingCycleCounterInfoIdx =
              Dem_IndicatorLink[LinkIdx].HealingCycleCounterInfoIdx;

          /* if indicator link uses the same healing cycle as the event operation
           * cycle and failure counter OCC2 has reached failure threshold */
          /* defensive check to capture recalibrated configuration threshold */
          if (EvMemEntry->OCC2 >=
              Dem_HealingCycleCounterInfo[HealingCycleCounterInfoIdx].Threshold)
          {
            const Dem_CounterDataIdxType CounterDataIdx =
              (Dem_CounterDataIdxType)LinkIdx;

            /* if the WIR bit related to indicator link is set */
            if (DEM_IS_BIT_SET_IN_ARRAY(
                  DEM_INDICATOR_CYC_COUNTER_WIR_STATUS[DEM_INDICATOR_DEFAULT_COUNTER],
                  CounterDataIdx) )
            {
              IndicatorLinkIsHealed = TRUE;

              /* clear WIR bit related to indicator link */
              DEM_CLR_BIT_IN_ARRAY(
                DEM_INDICATOR_CYC_COUNTER_WIR_STATUS[DEM_INDICATOR_DEFAULT_COUNTER],
                CounterDataIdx);

#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)
              {
                const uint32 IndMILStart = Dem_IndicatorDesc[DEM_MIL_ID].StartIdx;
                const uint32 IndMILEnd = IndMILStart + Dem_IndicatorDesc[DEM_MIL_ID].Number;

                /* !LINKSTO Dem_OBD_0023,4 */
                /* remove permanent entry in case the MIL is not requested anymore */
                if ( ((Dem_IndicatorIdxType)IndMILStart <= LinkIdx) &&
                     ((Dem_IndicatorIdxType)IndMILEnd > LinkIdx) )
                {
                  /* critical section has been already entered in the caller
                   * function Dem_OpCycleProcessEventCycleEnd */
                  Dem_PermanentMemoryRemoveEntry(EventId);
                }
              }
#endif /* DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U */
            }
          }
        }
      }
    }
#endif /* (DEM_CALIBRATION_SUPPORT == STD_ON) */

    /* the check for Warning indicator Off-Criteria loops through all indicators
     * linked - optimized run-time by executing check outside the loop */
    if (IndicatorLinkIsHealed == TRUE)
    {
      /* clear WIR status bit in case all assigned indicators are OFF */
      if (Dem_CheckWIROffCriteriaFulfilled(EventId) == TRUE)
      {
        /* !LINKSTO Dem.ASR42.SWS_Dem_00835,1 */
        /* allow the reset only if the user controlled WIR-bit for current event is reset */
#if (DEM_USER_CTRL_WIR_SUPPORT == STD_ON)
        if (!DEM_IS_USER_CTRL_WIR_SET(EventId))
#endif
        {
          DEM_CLR_EV_ST_MASK(EventId, DEM_UDS_STATUS_WIR);
        }
      }
    }

  }

  DBG_DEM_PROCESSOCC2BASEDHEALING_EXIT(EventId);
}
#endif /* (DEM_NUM_INDICATOR_LINKS > 0U) && \
          (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD */

#endif /* ((DEM_OPERATION_CYCLE_PROCESSING == DEM_PROCESS_OPCYC_STATE) ||
     (DEM_OPERATION_CYCLE_PROCESSING == DEM_PROCESS_OPCYC_RESTART)) */

#if (DEM_OPCYC_OBD_DCY_USED == STD_ON) && ((defined DEM_MIL_ID) && (DEM_NUM_INDICATOR_LINKS > 0U))
STATIC FUNC(boolean, DEM_CODE) Dem_IsMILEvent(
  Dem_EventIdType                                   EventId,
  P2VAR(Dem_IndicatorIdxType, AUTOMATIC, AUTOMATIC) IndicatorIdx)
{
  boolean Result = FALSE;
  Dem_IndicatorIdxType Index;

  DBG_DEM_ISMILEVENT_ENTRY(EventId, IndicatorIdx);

#if (DEM_CALIBRATION_SUPPORT == STD_ON)
  {
    const Dem_IndicatorGrpIdxType IndicatorClassIdx =
                Dem_GbiIndicatorClassIndex(EventId);

    if (IndicatorClassIdx < DEM_INDICATOR_UNUSED)
    {
      const Dem_IndicatorIdxType IndicatorClassIdxStart =
        Dem_IndicatorGroups[IndicatorClassIdx];
      const Dem_IndicatorIdxType IndicatorClassIdxEnd =
        Dem_IndicatorGroups[IndicatorClassIdx + 1U];

      for ( Index = IndicatorClassIdxStart;
            (Index < IndicatorClassIdxEnd);
            Index++)
      {
        CONSTP2CONST(Dem_IndicatorClassType, AUTOMATIC, DEM_CONST) IndicatorClass =
          &Dem_IndicatorClasses[Index];

        if ( (IndicatorClass->IndicatorId == DEM_MIL_ID) &&
             (IndicatorClass->Enabled == TRUE) )
        {
          *IndicatorIdx = Index;
          Result = TRUE;
          break;
        }
      }
    }
  }
#else
  if (Dem_GbiIndicatorUsed(EventId) == TRUE)
  {
    const uint32 IndMILStart = Dem_IndicatorDesc[DEM_MIL_ID].StartIdx;
    const uint32 IndMILEnd = IndMILStart + Dem_IndicatorDesc[DEM_MIL_ID].Number;

    for ( Index = (Dem_IndicatorIdxType)IndMILStart;
          (Index < (Dem_IndicatorIdxType)IndMILEnd);
          Index++)
    {
      /* Deviation TASKING-3 */
      if (EventId == Dem_IndicatorLink[Index].EventId)
      {
        *IndicatorIdx = Index;
        Result = TRUE;
        break;
      }
    }
  }
#endif

  DBG_DEM_ISMILEVENT_EXIT(Result, EventId, IndicatorIdx);
  return Result;
}
#endif /* (DEM_OPCYC_OBD_DCY_USED == STD_ON) && ((defined DEM_MIL_ID) && (DEM_NUM_INDICATOR_LINKS > 0U)) */

#if (DEM_OPCYCLE_CTRS_SUPPORT == STD_ON)
STATIC FUNC(void, DEM_CODE) Dem_CheckForIncrementOpCycleCounters(
  Dem_OperationCycleIdType OperationCycleId)
{
  uint8_least OriginIdx;
  Dem_SizeEvMemEntryType EntryIdx;

  /* loop for event memories */
  for (OriginIdx = 0U; OriginIdx < DEM_MAXNUM_ORIGINS; ++OriginIdx)
  {
    /* for every event entry */
    for (EntryIdx = 0U; EntryIdx < Dem_SizeEventMem[OriginIdx]; ++EntryIdx)
    {
      const Dem_EventIdType EventId = Dem_EventMem[OriginIdx][EntryIdx].EventId;

      /* if entry exists */
      if (EventId != DEM_EVENT_ID_INVALID)
      {
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
        if (Dem_GbiEvAvailable(EventId) == FALSE)
        {
          /* event is disabled so the update of the counters will
           * be skipped */
        }
        else
#endif
        {
          /* only for events of this operation cycle */
          if (Dem_GbiOpCycleIdx(EventId) == OperationCycleId)
          {
            Dem_EventMemoryEntryPtrType EvMemEntry =
              &Dem_EventMem[OriginIdx][EntryIdx];

#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
            /* in order to distiguish between pre-failed and failed
             * qualifications for VCC variant as long as the TF bit is set
             * or the counter CSFF is started and at least 1 continue counting */
            /* event combination and DEM_TRIGGER_ON_FDC_THRESHOLD not
             * compatible -> check event status not the combined status */
            if ( (EvMemEntry->CSFF > 0U) ||
                  DEM_IS_EV_ST_BIT_TFTOC_SET(EventId) )
#endif
            {
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
              boolean EntryUpdated = FALSE;
#endif

#if (DEM_OPCYCLE_CTR_FAILEDCYCLES_SUPPORT == STD_ON) && (DEM_NUM_CMB_DTCS > 0U)
  Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
#endif

#if (DEM_OPCYCLE_CTR_CSFF_SUPPORT == STD_ON)
              /* !LINKSTO Dem.OperationCycleCounters.CSFF.CounterOverflow,1 */
              if (EvMemEntry->CSFF != 0xFFU)
              {
                /* increment counter for cycles since first failed for
                 * this event */
                EvMemEntry->CSFF++;
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
                EntryUpdated = TRUE;
#endif
              }
#endif /* DEM_OPCYCLE_CTR_CSFF_SUPPORT == STD_ON */

#if (DEM_OPCYCLE_CTR_CSLF_SUPPORT == STD_ON)
              /* !LINKSTO Dem.OperationCycleCounters.CSLF.CounterOverflow,1 */
              if (EvMemEntry->CSLF != 0xFFU)
              {
                /* increment counter for cycles since last failed for
                 * this event */
                EvMemEntry->CSLF++;
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
                EntryUpdated = TRUE;
#endif
              }
#endif /* DEM_OPCYCLE_CTR_CSLF_SUPPORT == STD_ON */

#if (DEM_OPCYCLE_CTR_FAILEDCYCLES_SUPPORT == STD_ON)
#if (DEM_NUM_CMB_DTCS > 0U)
              /* for combined events check */
              /* !LINKSTO Dem.OperationCycleCounters.FAILEDCYCLES.CombinedEvent, 1 */
              if (DEM_IS_DTC_COMBINED(DTCConfIdx))
              {
                /* !LINKSTO Dem.OperationCycleCounters.FAILEDCYCLES.CounterOverflow, 1 */
                if ((EvMemEntry->FAILEDCYCLES != 0xFFU) && DEM_IS_CMB_ST_BIT_SET_IN_DTC(DTCConfIdx, DEM_UDS_STATUS_TFTOC))
                {
                  /* increment counter for failed cycles for
                   * this event */
                  EvMemEntry->FAILEDCYCLES++;
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
                  EntryUpdated = TRUE;
#endif
                }

              }
  else /* for non-combined events */
#endif /* DEM_NUM_CMB_DTCS > 0U */
              {
                /* !LINKSTO Dem.OperationCycleCounters.FAILEDCYCLES.CounterOverflow, 1 */
                if ((EvMemEntry->FAILEDCYCLES != 0xFFU) && (DEM_IS_EV_ST_BIT_TFTOC_SET(EventId)))
                {
                  /* increment counter for failed cycles for
                   * this event */
                  EvMemEntry->FAILEDCYCLES++;
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
                  EntryUpdated = TRUE;
#endif
                }
              }
#endif /* DEM_OPCYCLE_CTR_FAILEDCYCLES_SUPPORT == STD_ON */

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
              /* the entry is prepared for immediate non-volatile storage */
              if (EntryUpdated == TRUE)
              {
                Dem_CheckForImmediateEntryStorage(EventId,
                  EvMemEntry, EntryIdx, DEM_NVM_NO_FORCE);
              }
#endif
            }
          }
        }
      }
    }
  }
}
#endif /* DEM_OPCYCLE_CTRS_SUPPORT == STD_ON */

#if (DEM_OPCYCLE_CTR_CSLF_SUPPORT == STD_ON)
STATIC FUNC(void, DEM_CODE) Dem_ResetCycleSinceLastFailed(
  Dem_EventIdType EventId)
{
#if (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD)
 /* only for non-VCC variant: flag to determine if event is in event memory */
  boolean EventMemoryEntryExists = FALSE;
#endif
  boolean UpdateCondition = FALSE;

#if (DEM_NUM_CMB_DTCS > 0U)
  Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
  /* for combined events check */
  if (DEM_IS_DTC_COMBINED(DTCConfIdx))
  {
    /* TF of combined status */
    UpdateCondition =
      (!DEM_IS_CMB_ST_BIT_SET_IN_DTC(DTCConfIdx, DEM_UDS_STATUS_TF)) ? TRUE : FALSE;
#if (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD)
    EventMemoryEntryExists =
      DEM_IS_CMB_ST_BIT_SET_IN_DTC(DTCConfIdx, DEM_UDS_STATUS_TFSLC) ? TRUE : FALSE;
#endif
  }
  else /* for non-combined events */
#endif /* DEM_NUM_CMB_DTCS > 0U */
  {
    /* check TF bit of event status */
    UpdateCondition =
      ( !DEM_IS_EV_ST_BIT_TF_SET(EventId) ) ? TRUE : FALSE;
#if (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD)
    EventMemoryEntryExists =
      DEM_IS_ANY_EV_ST_BIT_SET(EventId, DEM_UDS_STATUS_TFSLC) ? TRUE : FALSE;
#endif
  }

   /* if TF bit transits from 0 to 1 (UpdateCondition) and event is qualified
    * (EventMemoryEntryExists), reset the CSLF counter */
  if (UpdateCondition == TRUE)
  {
#if (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD)
    if (EventMemoryEntryExists == TRUE)
#endif
    {
      Dem_EventMemoryEntryPtrType EvMemEntry;
      Dem_SizeEvMemEntryType EvMemEntryIdx;

      /* search the event in event memory */
      if (Dem_SearchForEntry(EventId, &EvMemEntry, &EvMemEntryIdx) != FALSE)
      {
        /* !LINKSTO Dem.SWS_Dem_00772,1 */
        /* reset the CSLF counter of the current entry */
        (EvMemEntry)->CSLF = 0U;

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
        /* the entry is prepared for immediate non-volatile storage */
        Dem_CheckForImmediateEntryStorage(EventId,
          EvMemEntry, EvMemEntryIdx, DEM_NVM_NO_FORCE);
#endif
      }
    }
  }
}
#endif /* DEM_OPCYCLE_CTR_CSLF_SUPPORT == STD_ON */

#if ((DEM_DEV_ERROR_DETECT == STD_ON) && (DEM_NUM_DEBOUNCE_COUNTER_PERM > 0U))
STATIC FUNC(boolean, DEM_CODE) Dem_DebounceCounterWithNvStorageDuringPreInit(Dem_EventIdType EventId)
{
  boolean Result = FALSE;

  DBG_DEM_DEBOUNCECOUNTERWITHNVSTORAGEDURINGPREINIT_ENTRY(EventId);

  if (Dem_InitializationState == DEM_PREINITIALIZED)
  {
    Dem_DebounceType DebounceAlgo = Dem_GbiDebounceAlgo(EventId);

    if (DebounceAlgo == DEM_DEBOUNCE_COUNTERBASED)
    {
      Dem_EventIdType DebounceStatusIdx = Dem_GbiDebounceStatusIdx(EventId);

      if (DEM_DEBOUNCE_COUNTER_NVSTORAGE_SUPPORT(DebounceStatusIdx) == TRUE)
      {
        Result = TRUE;
      }
    }
  }

  DBG_DEM_DEBOUNCECOUNTERWITHNVSTORAGEDURINGPREINIT_EXIT(Result, EventId);

  return Result;
}
#endif /* (DEM_DEV_ERROR_DETECT == STD_ON) && (DEM_NUM_DEBOUNCE_COUNTER_PERM > 0U) */

#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
STATIC FUNC(void, DEM_CODE) Dem_InformSatellites(boolean SendPreInitReportsToMaster)
{
  if (SendPreInitReportsToMaster == TRUE)
  {
    /* inform all satellites about full initialization state to switch
     * them into sending mode */
    SchM_Trigger_Dem_FullInitializedProvide();
  }
}
#endif /* (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON) */

#if ( (DEM_USE_PERMANENT_STORAGE == STD_ON) && \
      (DEM_NUM_DEBOUNCE_COUNTER_PERM > 0U) )
#if (DEM_OPCYC_NVSTORAGE == STD_ON)
STATIC FUNC(void, DEM_CODE) Dem_DebounceProcess(
  Dem_EventIdType                                   DebounceStatusIdx,
  Dem_EventIdType                                   EvId,
  P2VAR(Dem_EvIdLeastType,AUTOMATIC, AUTOMATIC)     NvDebIdx)
{
  if (DEM_DEBOUNCE_COUNTER_NVSTORAGE_SUPPORT(DebounceStatusIdx) == TRUE)
  {
    if (DEM_OPCYCLESTATE[Dem_GbiOpCycleIdx(EvId)] == DEM_CYCLE_STATE_START)
    {
      Dem_DebounceCounterStatus[DebounceStatusIdx] =
      Dem_NvData.DebounceCounterStatus[(*NvDebIdx)];
    }
    (*NvDebIdx)++;
  }
}
#endif /* (DEM_OPCYC_NVSTORAGE == STD_ON) */

STATIC FUNC(void, DEM_CODE) Dem_StoreDebounceCounterStatus(void)
{
  Dem_EvIdLeastType DebounceStatusIdx;
  Dem_EvIdLeastType NvDebIdx = 0U;

  /* !LINKSTO Dem.SWS_Dem_00674,1 */
  /* store internal debounce counter of events with non-volatile storage
   * of counter values enabled */
  for (DebounceStatusIdx = 0U;
       DebounceStatusIdx < DEM_NUM_DEBOUNCE_COUNTER;
       ++DebounceStatusIdx)
  {
    if (DEM_DEBOUNCE_COUNTER_NVSTORAGE_SUPPORT(DebounceStatusIdx) == TRUE)
    {
      /*
       * ENTER critical section
       */
      DEM_ENTER_EXCLUSIVE_AREA();

      Dem_NvData.DebounceCounterStatus[NvDebIdx] =
        Dem_DebounceCounterStatus[DebounceStatusIdx];
      /*
       * LEAVE critical section
       */
      DEM_EXIT_EXCLUSIVE_AREA();

      NvDebIdx++;
    }
  }
}
#endif /* ( (DEM_USE_PERMANENT_STORAGE == STD_ON) && \
            (DEM_NUM_DEBOUNCE_COUNTER_PERM > 0U) ) */

STATIC FUNC(void, DEM_CODE) Dem_ProcessClearDTCNotification(void)
{
#if (DEM_START_CLEAR_DTC_NOTIFICATION_SIZE > 0)
  boolean ClearDTCStartNotification = FALSE;
#endif
#if (DEM_FINISH_CLEAR_DTC_NOTIFICATION_SIZE > 0)
  boolean ClearDTCFinishNotification = FALSE;
#endif

  DBG_DEM_PROCESSCLEARDTCNOTIFICATION_ENTRY();
  /* Handling of STARTED state, transient state with duration of less than 1 main
   * function (change of state results in code fall through to the next state - PROCESSING_RAM)*/
  /* exclusive area to protect read/modify/write sequence */
  DEM_ENTER_EXCLUSIVE_AREA();
  if (DEM_IS_CLEAR_STARTED())
  {
    Dem_ClearDtcAsyncStatus.RunState = DEM_CLEARDTC_STATE_PROCESSING_RAM;
#if (DEM_START_CLEAR_DTC_NOTIFICATION_SIZE > 0)
    ClearDTCStartNotification = TRUE;
#endif
  }
  DEM_EXIT_EXCLUSIVE_AREA();

#if (DEM_START_CLEAR_DTC_NOTIFICATION_SIZE > 0)
  if(TRUE == ClearDTCStartNotification)
  {
    uint8 CbIdx;
    /* Deviation TASKING-1 */
    for (CbIdx = 0U; CbIdx < DEM_START_CLEAR_DTC_NOTIFICATION_SIZE; CbIdx++)
    {
      /* !LINKSTO Dem.ClearDTC.DemClearDtcNotificationTime.Start,1 */
      /* !LINKSTO dsn.Dem.DemClearDtcNotificationStart.MainFunction,1 */
      (void)Dem_CbFuncPtrStartClearDTCNotif[CbIdx](Dem_ClearDTCSelection.DTCInfo.DTC,
                                                   Dem_ClearDTCSelection.DTCInfo.DTCFormat,
                                                   Dem_ClearDTCSelection.DTCInfo.DTCOrigin);
    }
  }
#endif

  /* Handling of PROCESSING_RAM state, might extend to multiple MainFunctions */
  if (DEM_IS_CLEAR_IN_PROGRESS())
  {
    Dem_ProcessClearDTC();
  }

  /* Handling of FINISHED state, transient state that changes immediately withing Main Function to IDLE */
  /* exclusive area to protect read/modify/write sequence */
  DEM_ENTER_EXCLUSIVE_AREA();
  if (DEM_IS_CLEAR_FINISHED())
  {
    /* !LINKSTO Dem.ASR43.SWS_Dem_01042,1 */
    Dem_ClearDtcAsyncStatus.RunState = DEM_CLEARDTC_STATE_IDLE;
#if (DEM_FINISH_CLEAR_DTC_NOTIFICATION_SIZE > 0)
    ClearDTCFinishNotification = TRUE;
#endif
  }
  DEM_EXIT_EXCLUSIVE_AREA();

#if (DEM_FINISH_CLEAR_DTC_NOTIFICATION_SIZE > 0)
  if(TRUE == ClearDTCFinishNotification)
  {
    uint8 CbIdx;
    /* Deviation TASKING-1 */
    for (CbIdx = 0U; CbIdx < DEM_FINISH_CLEAR_DTC_NOTIFICATION_SIZE; CbIdx++)
    {
      /* !LINKSTO Dem.ClearDTC.DemClearDtcNotificationTime.Finish,1 */
      /* !LINKSTO dsn.Dem.DemClearDtcNotificationFinish.MainFunction,1 */
      (void)Dem_CbFuncPtrFinishClearDTCNotif[CbIdx](Dem_ClearDTCSelection.DTCInfo.DTC,
                                                    Dem_ClearDTCSelection.DTCInfo.DTCFormat,
                                                    Dem_ClearDTCSelection.DTCInfo.DTCOrigin);
    }
  }
#endif

  DBG_DEM_PROCESSCLEARDTCNOTIFICATION_EXIT();
}

STATIC FUNC(Dem_StatusTransitionType, DEM_CODE) Dem_ErrorQueueGetEventTFTOCTransitionBit(
  Dem_ErrorQueueElementType QueueEntry)
{
  return ((DEM_ERRORQUEUE_GET_FFTOC(QueueEntry) == TRUE) ? DEM_TRANSITION_EVENT_TFTOC : 0U);
}

#if ( (DEM_INCLUDE_RTE == STD_OFF) || (DEM_NUM_SWC_EVENTS > 0) )
#if (DEM_INTERNAL_DEBOUNCE_SUPPORT == STD_ON)
STATIC FUNC(void, DEM_CODE) Dem_ApplyDebounceStatus(
  Dem_EventIdType EventId,
  Dem_DebounceResetStatusType DebounceStatus)
{
  Dem_DebounceType DebounceAlgo;

  DBG_DEM_APPLYDEBOUNCESTATUS_ENTRY(EventId, DebounceStatus);

  DebounceAlgo = Dem_GbiDebounceAlgo(EventId);

  if (DebounceStatus == DEM_DEBOUNCE_STATUS_RESET)
  {
    /* reset debouncing counters for event */
    Dem_DebounceFctPtrTable[DebounceAlgo].ResetFct(EventId);
  }
  else
  {
    if (Dem_DebounceFctPtrTable[DebounceAlgo].FreezeFct != NULL_PTR)
    {
      /* freeze debouncing counters for event */
      Dem_DebounceFctPtrTable[DebounceAlgo].FreezeFct(EventId);
    }
  }

  DBG_DEM_APPLYDEBOUNCESTATUS_EXIT(EventId, DebounceStatus);
}
#endif /* (DEM_INTERNAL_DEBOUNCE_SUPPORT == STD_ON) */
#endif /* ( (DEM_INCLUDE_RTE == STD_OFF) || (DEM_NUM_SWC_EVENTS > 0) ) */

#if (DEM_EVENT_CONFIRMATION_THRESHOLD_COUNTER_ADAPTABLE == STD_ON)
STATIC FUNC(void, DEM_CODE) Dem_InitEventConfirmationThresholdCounter(void)
{
  Dem_EventIdType EventId;
  DBG_DEM_INITEVENTCONFIRMATIONTHRESHOLDCOUNTER_ENTRY();

  for (EventId = 1U; EventId <= DEM_MAX_EVENTID; ++EventId)
  {
    uint16 EventFailureClassIdx = Dem_GbiEventFailureClassIdx(EventId);

    if (EventFailureClassIdx != DEM_NO_FAULT_CONFIRMATION)
    {
#if (DEM_CALIBRATION_WITHOUTEVCOMB_SUPPORT == STD_OFF)
      Dem_ConfirmationThresholdRuntime[EventId] =
        Dem_EventFailureCycleCfg[EventFailureClassIdx].EventFailureCycleCounterThreshold;
#else
      Dem_ConfirmationThresholdRuntime[EventId] =
        Dem_EventClassDesc[DEM_GBI_EVENTCLASSDESCIDX(EventId)].EventFailureCycleCounterThreshold;
#endif
    }
    else
    {
      Dem_ConfirmationThresholdRuntime[EventId] = 0U;
    }
  }
  DBG_DEM_INITEVENTCONFIRMATIONTHRESHOLDCOUNTER_EXIT();
  return;
}
#endif /* (DEM_EVENT_CONFIRMATION_THRESHOLD_COUNTER_ADAPTABLE == STD_ON) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*==================[end of file]===========================================*/
