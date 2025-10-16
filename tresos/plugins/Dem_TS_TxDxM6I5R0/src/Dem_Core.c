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

/* This file contains definitions of Dem module internal functions. */

/* MISRA-C:2012 Deviation List
 *
 *  MISRAC2012-1) Deviated Rule: 11.5 (advisory)
 *    "A conversion should not be performed from pointer to void into pointer
 *    to object."
 *
 *    Reason:
 *    It is a pointer to void casted to a specific pointer necessary for a specific
 *    NvGate operations.
 *    In this way we have a single context type for all NvGate operations instead of
 *    different context types for each operation.
 *
 *
 *  MISRAC2012-2) Deviated Rule: 2.1 (required)
 *    "A project shall not contain unreachable code."
 *
 *    Reason:
 *    Run time check for the active OBD variant is always DEM_OBD_VARIANT_OBDONUDS
 *    when switching/selection of the OBD variant is not supported.
 *
 *
 * MISRAC2012-3) Deviated Rule: 20.7 (required)
 *     Expressions resulting from the expansion of macro parameters shall be enclosed in
 *     parentheses.
 *
 *     Reason:
 *     The macro DEM_CONST_CALIBRATION is used to modify the read-only attribute of a memory section
 *     to which a constant is assigned via the compiler abstraction macro, in order for the compiler
 *     to allow the simulation of the constant calibration. The syntax of the compiler abstraction
 *     macro definition requires that DEM_CONST_CALIBRATION macro's definition to not be enclosed in
 *     parentheses.
 */

/* tasking Deviation List
 *
 * TASKING-1) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * The compiler optimizes the 'for' loop (which has only 1 iteration) in the following way:
 * - it prepares in advance the index for the next iteration
 * - if the index is equal to '0' it goes back to check the 'for' loop conditions, otherwise it just moves on
 * - since the index is already equal to '1', it never jumps back to check the exit condition
 *
 * TASKING-2) Deviated Rule: W549
 * W549: condition is always true
 *
 * Reason:
 * "IndicatorUsed" is TRUE only if DEM_CALIBRATION_SUPPORT == STD_ON or the indicator
 * used flag is true. In other configurations, the code coverage reaches sections where
 * IndicatorUsed is FALSE.
 *
 * TASKING-3) Deviated Rule: W549
 * W549: condition is always false
 *
 * Reason:
 * It is a false positive warning. In some testcases from Dem_ConTest_Calibration,
 * the index is incremented at least two times, so the condition is executed true
 * at least once.
 *
 * TASKING-4) Deviated Rule: W549
 * W549: condition is always false
 *
 * Reason:
 * "EventStatus" is an argument that can receive a value different than DEM_EVENT_STATUS_CONFIRMED.
 * In other configurations, the code coverage reaches sections where EventStatus is
 * DEM_EVENT_STATUS_CONFIRMED.
 *
 * TASKING-5) Deviated Rule: W549
 * W549: condition is always false
 *
 * Reason:
 * "SearchForEventMemoryEntry" is FALSE when EventStatus is different than DEM_EVENT_STATUS_CONFIRMED
 * and EventWIRUpdate is FALSE. In other configurations, the code coverage reaches sections
 * where SearchForEventMemoryEntry is TRUE.
 *
 * TASKING-6) Deviated Rule: W549
 * W549: condition is always false
 *
 * Reason:
 * "SizeUsedEntryData" is 0 when no event data exists for any of the events in the
 * event memory. In other configurations, the code coverage reaches sections where
 * SizeUsedEntryData is greater than 0.
 *
 * TASKING-7) Deviated Rule: W588
 * W588: dead assignment to "Entry" eliminated
 *
 * Reason:
 * "Entry" th location of bit 15 is cleared via macro DEM_CLR_PERMANENT_MEMORY_FILL_COND(Entry)
 * the specifid bit is reading via the macro DEM_GET_PERMANENT_MEMORY_FILL_COND(Entry).
 */

/*==================[inclusions]============================================*/
/* !LINKSTO dsn.Dem.IncludeStr,1 */

#include <TSAutosar.h>                        /* EB specific standard types */
#include <TSMem.h>                          /* EB specific memory functions */
#include <Std_Types.h>                            /* AUTOSAR standard types */

#include <Dem_Int.h>             /* Module public and internal declarations */
#include <Dem_Trace.h>                        /* Dbg related macros for Dem */

#if ( (DEM_TRIGGER_FIM_REPORTS == STD_ON) || \
      ( (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) && \
        (DEM_SUPPORT_FIM_ON_FDC_TRESHOLD == STD_ON) ) )
#include <FiM.h>                    /* for trigger on event status callback */
#endif
#if (DEM_TRIGGER_DCM_REPORTS == STD_ON)
#include <Dcm.h>                      /* for trigger on DTC status callback */
#endif
#if ((DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON) || (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U))
#include <NvM.h>                                             /* Module APIs */
#include <Dem_NvMCbk.h>                              /* Module callback API */
#endif

/*==================[macros]================================================*/

#if (defined DEM_RESETFREQBASEDCOUNTERS)
#error DEM_RESETFREQBASEDCOUNTERS already defined
#endif
/** \brief Internal Macro to reset passed counter, failed counter and FDC in
 ** frequency based debouncing status structure
 */
#define DEM_RESETFREQBASEDCOUNTERS(debounceStatus) do             \
  {                                                               \
    (debounceStatus)->PassedCounter = 0U;                           \
    (debounceStatus)->FailedCounter = 0U;                           \
    (debounceStatus)->Status        = DEM_EVENT_STATUS_UNQUALIFIED; \
  } while(0)

/*==================[type definitions]======================================*/

/** \brief Internal data type to define the structure of one DTC lookup cache
 ** entry */
typedef struct
{
  uint32          DTC;             /**< DTC value, key of a key/value pair **/
  Dem_EventIdType EventId;        /**< Event Id, value of a key/value pair **/
} Dem_InternalDTCCacheEntryType;

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/** \brief Internal function to check event entry change
 ** due to a failed of unconfirmed report
 **
 ** It is called by the Dem_ProcessUnconfirmedFailed()
 **
 ** \param[in] EvMemEntry
 **
 ** \return TRUE if a change of the the event entry is expected
 **         FALSE if no change of the the event entry is expected
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
#if ((DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) && \
     (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON) )
STATIC FUNC(boolean, DEM_CODE) Dem_CheckForChangesByUnconfirmedFailedForSI30(
  Dem_EventMemoryEntryPtrType EvMemEntry);
#endif

/** \brief Updates failure counter on first fail report for the event in
 ** the operation cycle if failure cycle is already started
 **
 ** \param[in] EventId 1 < EventId <= DEM_MAX_EVENTID
 ** \param[in] EventStatus  status of event, ::DEM_EVENT_STATUS_FAILED or
 **               ::DEM_EVENT_STATUS_PASSED
 **
 ** \return Boolean indicating the failure counter has reached
 **         the failure threshold or not
 ** \retval TRUE  the failure counter reached the threshold
 ** \retval FALSE the failure counter didn't reach the threshold
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_UpdateFailureCounterFirstFail(
  Dem_EventIdType     EventId,
  Dem_EventStatusType EventStatus);

#if (DEM_C_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U)
/** \brief Function to get the first and the last index in a function pointer
 ** lookup table
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in] LookupTable  function pointer lookup table
 ** \param[in] TableSize
 ** \param[out] StartIdx  first index
 ** \param[out] LastIdx  last index
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **
 ** \pre This function must only be called for events triggering a
 ** callback-function available within the selected ::LookupTable array.
 */
STATIC FUNC(void, DEM_CODE) Dem_GetCallbackIndex(
  Dem_EventIdType                                      EventId,
  P2CONST(Dem_CbLookupTableType, AUTOMATIC, DEM_CONST) LookupTable,
  uint16                                               TableSize,
  P2VAR(uint16, AUTOMATIC, DEM_VAR)                    StartIdx,
  P2VAR(uint16, AUTOMATIC, DEM_VAR)                    LastIdx);
#endif /* DEM_C_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U */

#if (DEM_RTE_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U)
/** \brief Function to get the first and the last index in a function pointer
 ** lookup table
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in] LookupTable  function pointer lookup table
 ** \param[in] TableSize
 ** \param[out] StartIdx  first index
 ** \param[out] LastIdx  last index
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **
 ** \pre This function must only be called for events triggering a
 ** callback-function available within the selected ::LookupTable array.
 */
STATIC FUNC(void, DEM_CODE) Dem_GetRteCallbackIndex(
  Dem_EventIdType                                EventId,
  P2CONST(Dem_EventIdType, AUTOMATIC, DEM_CONST) LookupTable,
  uint16                                         TableSize,
  P2VAR(uint16, AUTOMATIC, DEM_VAR)              StartIdx,
  P2VAR(uint16, AUTOMATIC, DEM_VAR)              LastIdx);
#endif

#if (DEM_NUM_DEBOUNCE_TIME > 0U)
/** \brief Reset internal status for time based debouncing
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 **
 ** \Reentrancy{Non Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ResetDebounceTimeBased(
  Dem_EventIdType EventId);

/** \brief Freeze internal debounce timer for time based debouncing
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 **
 ** \Reentrancy{Non Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_FreezeDebounceTimeBased(
  Dem_EventIdType EventId);
#endif

/** \brief Reset internal status for monitor internal debouncing
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 **
 ** \Reentrancy{Non Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ResetDebounceMonitor(Dem_EventIdType EventId);

#if (DEM_NUM_DEBOUNCE_COUNTER > 0U)
/** \brief Reset internal status for counter based debouncing
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 **
 ** \Reentrancy{Non Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ResetDebounceCounterBased(
  Dem_EventIdType EventId);
/** \brief Freeze internal status for counter based debouncing
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 **
 ** \Reentrancy{Non Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_FreezeDebounceCounterBased(
  Dem_EventIdType EventId);
#endif

#if (DEM_NUM_DEBOUNCE_FREQUENCY > 0U)
/** \brief Reset internal status for frequency based debouncing
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 **
 ** \Reentrancy{Non Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ResetDebounceFrequencyBased(
  Dem_EventIdType EventId);

/** \brief Freeze internal timer/frequency for frequency based debouncing
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 **
 ** \Reentrancy{Non Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_FreezeDebounceFrequencyBased(
  Dem_EventIdType EventId);
#endif

#if (DEM_NUM_DEBOUNCE_COUNTER > 0U)
/** \brief Perform counter based debouncing for a given event
 **
 ** This function is called by the APIs Dem_ReportErrorStatus() and
 ** Dem_SetEventstatus() if counter based debouncing is enabled for the
 ** reported event.
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in,out] EventStatus  status of event, either DEM_EVENT_STATUS_PREPASSED
 **                  or DEM_EVENT_STATUS_PREFAILED
 **
 ** \Reentrancy{Non-reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_DebounceEventCounterBased(
  Dem_EventIdType                                      EventId,
  P2VAR(Dem_EventStatusType, AUTOMATIC, DEM_APPL_DATA) EventStatus);
#endif

#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
/** \brief Perform processing of events that have unconfirmed threshold set
 **
 ** This function is called by the Dem_DebounceEvent() and
 ** Dem_DebounceEventCounterBased() if unconfirmed threshold is set for the
 ** reported event.
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in] EventStatus  status of event, ::DEM_EVENT_STATUS_PREPASSED,
 **               ::DEM_EVENT_STATUS_PASSED, ::DEM_EVENT_STATUS_PREFAILED,
 **               ::DEM_EVENT_STATUS_FAILED
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ProcessUnconfirmedThreshold(
  Dem_EventIdType     EventId,
  Dem_EventStatusType EventStatus);

/** \brief Perform processing of passed events with unconfirmed threshold set
 **
 ** This function is called by Dem_ProcessUnconfirmedThreshold().
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[inout] EventStatusChangedMsgPtr  Pointer to notification message
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **
 ** \pre This function shall be called from within a critical section only.
 */
STATIC FUNC(void, DEM_CODE) Dem_ProcessUnconfirmedPassed(
  Dem_EventIdType                  EventId,
  Dem_EventStatusChangedMsgPtrType EventStatusChangedMsgPtr);

/** \brief Perform processing of unconfirmed or failed events with unconfirmed
 ** threshold set
 **
 ** This function is called by Dem_ProcessUnconfirmedThreshold().
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in] EventStatus  status of event, ::DEM_EVENT_STATUS_UNCONFIRMED or
 **               ::DEM_EVENT_STATUS_FAILED
 ** \param[in] FDC  Fault detection counter
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **
 ** \pre This function shall be called from within a critical section only.
 */
STATIC FUNC(void, DEM_CODE) Dem_ProcessUnconfirmedFailed(
  Dem_EventIdType     EventId,
  Dem_EventStatusType EventStatus,
  uint8               FDC);

/** \brief Perform processing of event memory data for first unconfirmed
 ** event TOC
 **
 ** This function is called by Dem_ProcessUnconfirmedFailed().
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in] EvMemEntry  pointer to event memory
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **
 ** \pre This function shall be called from within a critical section only.
 */
STATIC FUNC(void, DEM_CODE) Dem_ProcessFirstUnconfirmedTOC(
  Dem_EventIdType             EventId,
  Dem_EventMemoryEntryPtrType EvMemEntry);

#if ((DEM_USE_AGING == STD_ON) && (DEM_NUM_INDICATOR_LINKS > 0U) && (DEM_VCC_OCC5_USED == STD_ON))
/** \brief Function which sets the 'IndicatorCycleCounterRole' of all
 ** indicators assigned to the EventId to 'DEM_INDICATORCOUNTER_ROLE_HEALING_CYCLE_COUNTER'
 **
 ** This function is called by Dem_ProcessEventAging().
 ** This function loops through all indicator links belonging to the EventId
 ** and sets their role to healing.
 **
 ** \param[in] EventId Id of the entry being aged which will also require setting of the indicator role.
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_ResetIndicatorCycleCounterRoleOfEventId(
  Dem_EventIdType EventId);
#endif /*((DEM_USE_AGING == STD_ON) && (DEM_NUM_INDICATOR_LINKS > 0U) &&
          (DEM_VCC_OCC5_USED == STD_ON))*/
#endif /* DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD */

#if (DEM_NUM_DEBOUNCE_TIME > 0U)
/** \brief Perform time based debouncing for a given event
 **
 ** This function is called by the APIs Dem_ReportErrorStatus() and
 ** Dem_SetEventstatus() if time based debouncing is enabled for the
 ** reported event.
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in] EventStatus  status of event, either DEM_EVENT_STATUS_PREPASSED
 **              or DEM_EVENT_STATUS_PREFAILED
 **
 ** \Reentrancy{Non-reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_DebounceEventTimeBased(
  Dem_EventIdType                                      EventId,
  P2VAR(Dem_EventStatusType, AUTOMATIC, DEM_APPL_DATA) EventStatus);
#endif

#if (DEM_NUM_DEBOUNCE_FREQUENCY > 0U)
/** \brief Perform frequency based debouncing for a given event
 **
 ** This function is called by the APIs Dem_ReportErrorStatus() and
 ** Dem_SetEventstatus() if frequency based debouncing is enabled for the
 ** reported event.
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[in,out] EventStatus  status of event, either DEM_EVENT_STATUS_PREPASSED
 **                  or DEM_EVENT_STATUS_PREFAILED
 **
 ** \Reentrancy{Non-reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_DebounceEventFrequencyBased(
  Dem_EventIdType                                      EventId,
  P2VAR(Dem_EventStatusType, AUTOMATIC, DEM_APPL_DATA) EventStatus);
#endif

#if (DEM_NUM_DEBOUNCE_COUNTER > 0U)
/** \brief Return FDC for an event using counter based debouncing
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[out] FDC
 **
 ** \return E_OK if FDC could be acquired, E_NOT_OK otherwise
 **
 ** \Reentrancy{Non-reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_GetFDCCounterBased(
  Dem_EventIdType                        EventId,
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FDC);

#if (DEM_USE_TRIGGER_DEBOUNCE_BEHAVIOR == STD_ON)
/** \brief Return DemDebounceBehavior for an event using counter based debouncing
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[out] DemDebounceBehavior: RESET/FREEZE
 **
 ** \return E_OK if DemDebounceBehavior could be acquired, E_NOT_OK otherwise
 **
 ** \Reentrancy{Non-reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_GetBehaviorCounterBased(
  Dem_EventIdType                                           EventId,
  P2VAR(Dem_DebounceBehaviorType, AUTOMATIC, DEM_APPL_DATA) DebounceBehavior);
#endif
#endif /* DEM_NUM_DEBOUNCE_COUNTER > 0U */

#if (DEM_NUM_DEBOUNCE_TIME > 0U)
/** \brief Return FDC for an event using time based debouncing
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[out] FDC
 **
 ** \return E_OK if FDC could be acquired
 **
 ** The function Dem_GetFDCTimeBased will always return E_OK
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_GetFDCTimeBased(
  Dem_EventIdType                        EventId,
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FDC);

#if (DEM_USE_TRIGGER_DEBOUNCE_BEHAVIOR == STD_ON)
/** \brief Return DemDebounceBehavior for an event using time based debouncing
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[out] DemDebounceBehavior: RESET/FREEZE
 **
 ** \return E_OK if DemDebounceBehavior could be acquired, E_NOT_OK otherwise
 **
 ** \Reentrancy{Non-reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_GetBehaviorTimeBased(
  Dem_EventIdType                                           EventId,
  P2VAR(Dem_DebounceBehaviorType, AUTOMATIC, DEM_APPL_DATA) DebounceBehavior);
#endif
#endif /* DEM_NUM_DEBOUNCE_TIME > 0U */

#if (DEM_NUM_DEBOUNCE_FREQUENCY > 0U)
/** \brief Return FDC for an event using frequency based debouncing
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[out] FDC
 **
 ** \return E_OK if FDC could be acquired
 **
 ** The function Dem_GetFDCFrequencyBased will always return E_OK
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_GetFDCFrequencyBased(
  Dem_EventIdType                        EventId,
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FDC);

#if (DEM_USE_TRIGGER_DEBOUNCE_BEHAVIOR == STD_ON)
/** \brief Return DemDebounceBehavior for an event using frequency based debouncing
 **
 ** \param[in] EventId  0 < EventId <= DEM_MAX_EVENTID
 ** \param[out] DemDebounceBehavior: RESET/FREEZE
 **
 ** \return E_OK if DemDebounceBehavior could be acquired, E_NOT_OK otherwise
 **
 ** \Reentrancy{Non-reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_GetBehaviorFrequencyBased(
  Dem_EventIdType                                           EventId,
  P2VAR(Dem_DebounceBehaviorType, AUTOMATIC, DEM_APPL_DATA) DebounceBehavior);
#endif
#endif /* DEM_NUM_DEBOUNCE_FREQUENCY > 0U */

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
/** \brief Function to search for next entry to be stored immediately
 **
 ** This function is invoked from a single block callback function from NvM
 ** related to job end notifcation.
 **
 ** \param[in] OriginIdx
 ** \return NvMGateStatus
 ** \return Boolean value indicating whether the condition for storing
 **                 immediately is satisfied or not.
 **/
STATIC FUNC(boolean, DEM_CODE) Dem_StoreImmediatelyNext(uint8 OriginIdx);

/** \brief Common NvM block callback handler
 **
 ** This function is called by each of the configured NvM block callback
 ** functions Dem_NvMGateEntry<..>BlockCallback and commonly handles all
 ** callbacks of asynchronous NvM requests.
 **
 ** \param[in] ServiceId  NvM service identifier
 ** \param[in] OriginIdx  Origin index of event memory related to callback
 **/
STATIC FUNC(void, DEM_CODE) Dem_NvMGateEntryBlockCallback(
  uint8 ServiceId,
  uint8 OriginIdx);
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */

#if (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON)
/** \brief Function to assemble the extended data record for internal
 ** element data types.
 **
 ** \param[in] EventId          Id of the event for which the data are requested
 ** \param[in] DataElementIdx   Index of the data element which indicates what data
 **                             will be read
 ** \param[in] Dest             Pointer to a location in DestBuffer[] where
 **                             the ED seg is to be stored.
 ** \param[in] EvMemEntry  Pointer to event memory entry. Can be NULL_PTR if
 **                         an always available data element is requested.
 **
 ** \return uint8 value indicating the size of internal data element mapped
 **               to extended data
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(uint8, DEM_CODE) Dem_AssembleEDSegIntData(
  Dem_EventIdType                        EventId,
  Dem_DataElementIdxType                 DataElementIdx,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Dest,
  Dem_EventMemoryEntryPtrConstType       EvMemEntry);

#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
/** \brief Function to assemble the extended data record for internal
 ** extended data types (counter specific).
 **
 ** \param[in] DataElementIdx     Index of the data element which indicates what data will be read
 ** \param[in] Dest               Pointer to a location in DestBuffer[] where
 **                               the ED seg is to be stored.
 ** \param[in] EvMemEntry         Pointer to event memory entry. Can be NULL_PTR if
 **                               an always available data element is requested.
 **
 ** \return none
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_AssembleEDOnFDCThresholdData(
  Dem_DataElementIdxType                 DataElementIdx,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Dest,
  Dem_EventMemoryEntryPtrConstType       EvMemEntry);
#endif

#if (DEM_USE_AGING == STD_ON)
/** \brief Function to assemble the extended data record for internal
 ** element data aging counter down.
 **
 ** \param[in] EventId      Id of the event for which the data are requested
 ** \param[in] Dest         Pointer to a location in DestBuffer[] where
 **                         the ED seg is to be stored.
 ** \param[in] EvMemEntry   Pointer to event memory entry. Can be NULL_PTR if
 **                         an always available data element is requested.
 **
 ** \return none
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_AssembleEDSegAgingCounterDown(
  Dem_EventIdType                        EventId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Dest,
  Dem_EventMemoryEntryPtrConstType       EvMemEntry);

/** \brief Function to assemble the extended data record for internal
 ** element data aging counter up.
 **
 ** \param[in] EventId      Id of the event for which the data are requested
 ** \param[in] Dest         Pointer to a location in DestBuffer[] where
 **                         the ED seg is to be stored.
 ** \param[in] EvMemEntry   Pointer to event memory entry. Can be NULL_PTR if
 **                         an always available data element is requested.
 **
 ** \return none
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_AssembleEDSegAgingCounterUp(
  Dem_EventIdType                        EventId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Dest,
  Dem_EventMemoryEntryPtrConstType       EvMemEntry);
#endif /* DEM_USE_AGING == STD_ON */

/** \brief Function to assemble the extended data record for internal
 ** element of type FDC.
 **
 ** \param[in] EventId      Id of the event for which the data are requested
 ** \param[in] Dest         Pointer to a location in DestBuffer[] where
 **                         the ED seg is to be stored.
 ** \param[in] EvMemEntry   Pointer to event memory entry. Can be NULL_PTR if
 **                         an always available data element is requested.
 **
 ** \return none
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_AssembleEDSegFaultDetectionCounter(
  Dem_EventIdType                        EventId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Dest);

#if (DEM_MAR_SUPPORT == STD_ON)
/** \brief Function to assemble the extended data record for internal
 ** data element of type MAR.
 **
 ** \param[in] EventId      Id of the event for which the data are requested
 ** \param[in] Dest         Pointer to a location in DestBuffer[] where
 **                         the ED seg is to be stored.
 **
 ** \return none
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_AssembleEDSegMARData(
  Dem_EventIdType                        EventId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Dest);
#endif /* (DEM_MAR_SUPPORT == STD_ON) */
#endif /* (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON) */

#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
#if ( (DEM_CB_TABLE_TRIG_ON_DTCST_SIZE > 0U) || \
      (DEM_TRIGGER_DCM_REPORTS == STD_ON) )
/** \brief Wrapper-Function to call trigger-on-DTC-status functions
 **
 ** Dem_CbTriggerOnDTCStatus shall be enabled only if
 ** either RTE callback or C callback is configured for Trigger on DTC.
 **
 ** This must be done by a wrapper, because it depends on configuration.
 **
 ** \param[in] EventId  0 < EventId < DEM_NUMBER_OF_EVENTS
 ** \param[in] OldDTCStatusMask
 ** \param[in] NewDTCStatusMask
 */
STATIC FUNC(void, DEM_CODE) Dem_CbTriggerOnDTCStatus(
  Dem_EventIdType       EventId,
  Dem_DTCStatusMaskType OldDTCStatusMask,
  Dem_DTCStatusMaskType NewDTCStatusMask);
#endif
#endif /* DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON */

/** \brief Get the UDS DTC value from configured callout function if ::DEM_USE_DYNAMIC_DTCS
 ** is enabled, else from ::Dem_EventDesc by using index
 **
 ** Internal function to read the assigned UDS DTC regardless of the event availability
 ** and the DTC suppression status.
 ** This function shall be used instead of the external wrapper Dem_GetUdsDTC().
 **
 ** \param[in] EventId  0 < EventId < DEM_NUMBER_OF_EVENTS
 **
 ** \return DEM_NO_DTC if no UDS DTC is assigned to the event, otherwise the assigned
 **         UDS DTC value
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(uint32, DEM_CODE) Dem_InternalGetUdsDTC(Dem_EventIdType EventId);

#if (DEM_OBD_Support == STD_ON)
/** \brief Get the OBD DTC value from ::Dem_OBDDTC by using index.
 **
 ** Internal function to read the assigned OBD DTC regardless of the event availability
 ** and the DTC suppression status.
 ** This function shall be used instead of the external wrapper Dem_GetObdDTC().
 **
 ** \param[in] EventId  0 < EventId < DEM_NUMBER_OF_EVENTS
 **
 ** \return DEM_NO_DTC if no OBD DTC is assigned to the event, otherwise the assigned
 **         OBD DTC value
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(uint32, DEM_CODE) Dem_InternalGetObdDTC(Dem_EventIdType EventId);

#if (DEM_OBD_DTCVALUE3BYTE_SUPPORT == STD_ON)
/** \brief Get the 3-byte OBD DTC value from ::Dem_OBDConfig[] by using index.
 **
 ** Internal function to read the assigned 3-byte OBD DTC regardless of the event
 ** availability and the DTC suppression status.
 ** This function shall be used instead of the external wrapper Dem_GetObdDTC().
 **
 ** \param[in] EventId  0 < EventId < DEM_NUMBER_OF_EVENTS
 **
 ** \return DEM_NO_DTC if no 3-byte OBD DTC is assigned to the event, otherwise the assigned
 **         3-byte OBD DTC value
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(uint32, DEM_CODE) Dem_InternalGetObdDTCValue3Byte(Dem_EventIdType EventId);
#endif /* (DEM_OBD_DTCVALUE3BYTE_SUPPORT == STD_ON) */
#endif /* (DEM_OBD_Support == STD_ON) */

/** \brief Get the DTC value for a specific event, based on the DTC format
 **
 ** Internal function to read the DTC value for a specific event, based on the
 ** DTC format.
 ** This internal function additionally utilizes the internal function
 ** Dem_InternalGetObdDTC() to retrieve 2-byte OBD DTC,
 ** Dem_InternalGetUdsDTC() to retrieve UDS DTC,
 ** Dem_InternalGetObdDTCValue3Byte() to retrieve 3-byte OBD DTC, and
 ** Dem_InternalGetJ1939DTC() to retrieve J1939 DTC.
 **
 ** \param[in] DTCFormat  Defines the input-format of the provided DTC value
 **
 ** \param[in] EventId    EventId of an event for which DTC value is retrieved
 **
 ** \return DEM_NO_DTC if no DTC of the specified format is assigned to the
 **         event, otherwise the assigned DTC value
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(uint32, DEM_CODE) Dem_InternalGetDTC(
  Dem_DTCFormatType DTCFormat,
  Dem_EventIdType   EventId);

#if (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION)
/** \brief Get the DTC suppression status for a specific event, based on the
 ** DTC format
 **
 ** Internal function for retrieving the DTC suppression status of a specific
 ** event.
 ** This function checks, if a DTC is explicitly suppressed by Dem_SetDTCSuppression().
 ** It utilizes array Dem_OBDDTCSuppression[] to read the
 ** suppression status for 2-byte and 3-byte OBD DTCs,
 ** Dem_UDSDTCSuppression[] to read the suppression status for UDS DTCs, and
 ** Dem_J1939DTCSuppression[] to read the suppression status for J1939 DTCs.
 **
 ** \param[in] DTCFormat  Defines the input-format of the provided DTC value
 **
 ** \param[in] EventId    EventId of an event for which DTC suppression status
 **                       is retrieved
 **
 ** \return Boolean indicating DTC suppression status for a specific event
 ** \retval TRUE    the DTC for a specific event is suppressed
 ** \retval FALSE   the DTC for a specific event is unsuppressed
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_IsDTCExplicitlySuppressed(
  Dem_DTCFormatType DTCFormat,
  Dem_EventIdType   EventId);

/** \brief Get Event Id for input DTC and suppress the matching event if no event entry exists.
 **
 ** Internal function to get the matching Event Id for a given DTC by using
 ** Dem_InternalGetUdsDTC() or Dem_InternalGetObdDTC() and suppresses the
 ** corresponding event(s).
 ** This function shall be used by Dem_InternalSetDTCSuppression() when there are
 ** no identical OBD DTCs configured.
 **
 ** \param[in] DTC  Diagnostic Trouble Code.
 **
 ** \param[in] GetDTCFct  Function pointer to get the matching event for given DTC.
 **
 ** \param[in] DtcSuppressionArray Pointer to the UDS or OBD or J1939 suppression status array
 ** \param[in] SuppressionStatus  This parameter specifies whether
 **                     the respective DTC shall be disabled (TRUE)
 **                     or enabled (FALSE).
 **
 ** \return E_OK if the operation is successful,
 **     E_NOT_OK if the operation is not successful.
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_InternalCheckAndSetDTCSuppression(
  uint32                             DTC,
  Dem_GetDTCFctPtrType               GetDTCFct,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) DtcSuppressionArray,
  boolean                            SuppressionStatus);

#if ( (DEM_OBD_Support == STD_ON) && \
      (DEM_OBD_CLASSIC_SUPPORT) && \
      (DEM_IDENTICAL_OBD_DTC_AVAILABLE == STD_ON) )
/** \brief Check if an event entry exists for the input OBD DTC and
 **  if no event entry exists, suppresses all matching events for the OBD DTC.
 **
 ** Internal function to check if event/events associated with the given OBD DTC has
 ** an event entry by using Dem_ExistEntryOfObdDTC() and if no event entry is found,
 ** suppresses all the events configured for an OBD DTC.
 ** This function shall be used by Dem_InternalSetDTCSuppression() only when OBD is supported
 ** and identical OBD DTCs are configured.
 **
 ** \param[in] DTC  Diagnostic Trouble Code.
 **
 ** \param[in] SuppressionStatus  This parameter specifies whether
 **                     the respective DTC shall be disabled (TRUE)
 **                     or enabled (FALSE).
 **
 ** \return E_OK if the operation is successful,
 **     E_NOT_OK if the operation is not successful.
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_InternalCheckAndSetObdDTCSuppression(
  uint32            DTC,
  boolean           SuppressionStatus);

/** \brief Check if an event entry exists for the input OBD DTC.
 **
 ** Internal function to check if any event associated with the given OBD DTC has
 ** an event entry.
 **
 ** \param[in] DTC  Diagnostic Trouble Code.
 **
 ** \return TRUE if an event entry exists,
 **     FALSE if no event entry exists.
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_ExistEntryOfObdDTC(uint32 DTC);
#endif /* ( (DEM_OBD_Support == STD_ON) && \
            (DEM_OBD_CLASSIC_SUPPORT) && \
            (DEM_IDENTICAL_OBD_DTC_AVAILABLE == STD_ON) ) */
#endif /* (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION) */

#if (  (DEM_NUM_BSWEVENT_INDICATOR_USED > 0U) \
     &&(DEM_COMMON_OPERATION_CYCLE_SUPPORT == STD_OFF))
/** \brief Checks if reported BSW Event status needs WIR bit evaluation
 **
 ** \param[in] EventId 1 < EventId <= DEM_MAX_EVENTID
 ** \param[in] EventStatus  status of event, ::DEM_EVENT_STATUS_FAILED or
 **               ::DEM_EVENT_STATUS_PASSED
 **
 ** \return Boolean indicating whether evaluation is needed or not
 ** \retval TRUE  The event should be queued to evaluate indicator
 ** \retval FALSE the event should not be queued to evaluate indicator
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(boolean, DEM_CODE) Dem_CheckErrorRequiresIndUpdate(
  Dem_EventIdType       EventId,
  Dem_EventStatusType   EventStatus);
#endif

#if (DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON)
/** \brief Function to store current DTC or event status into a buffer
 **
 ** This function is used to fill the StorageOrderIdAndDTCStatus[] array with
 ** the current DTC status, or the current events status values of the
 ** combined DTCs respectively.
 **
 ** \param[in]  EventId     Id of the event for which the DTC status is
 **                         stored.
 ** \param[out] DestBuffer  Pointer to the memory location where the
 **                         DTC/event status will be stored.
 **
 ** \return none
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(void, DEM_CODE) Dem_StoreDTCStatus(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) DestBuffer,
  Dem_EventIdType                        EventId);
#endif

#if ((DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON) || \
     (DEM_NUM_CAPTURE_ON_RETRIEVAL_DATAELEMENTS > 0U))
/** \brief Function to get the size of an internal data element
 **
 ** \param[in] DataElementIdx     Index of the internal data element
 **
 ** \return Dem_SizeEDType        Size of the internal data element
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
STATIC FUNC(Dem_SizeEDType, DEM_CODE) Dem_SizeofInternalDE(
  Dem_DataElementIdxType       DataElementIdx);
#endif /* ((DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON) || \
           (DEM_NUM_CAPTURE_ON_RETRIEVAL_DATAELEMENTS > 0U)) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*==================[external constants]====================================*/

#define DEM_START_SEC_CONST_UNSPECIFIED
#include <Dem_MemMap.h>

/** \brief function pointer array for easy access to debouncing functions */
CONST(Dem_DebounceFctPtrTableType, DEM_CONST)
  Dem_DebounceFctPtrTable[DEM_MAXNUM_DEBOUNCECLASSES] =
{
  /* "monitor internal" debouncing - DEM_DEBOUNCE_MONITOR */
  {
    &Dem_ResetDebounceMonitor,
    NULL_PTR,
        /* "freeze counter" function for "monitor internal" debouncing is not relevant */
    NULL_PTR, /* "debounce event" function will never be called */
#if (DEM_USE_CB_GET_FDC == STD_ON)
    &Dem_CbGetFaultDetectionCounter,
#else
    NULL_PTR,
#endif
#if (DEM_USE_TRIGGER_DEBOUNCE_BEHAVIOR == STD_ON)
    NULL_PTR
        /* "get debounce behavior" function for "monitor internal" debouncing is not relevant */
#endif
  },
  /* counter based debouncing - DEM_DEBOUNCE_COUNTERBASED */
  {
#if (DEM_NUM_DEBOUNCE_COUNTER > 0U)
    &Dem_ResetDebounceCounterBased,
    &Dem_FreezeDebounceCounterBased,
        /* "freeze counter" function for counter-based debouncing is
         * not relevant - dummy function */
    &Dem_DebounceEventCounterBased,
    &Dem_GetFDCCounterBased,
#if (DEM_USE_TRIGGER_DEBOUNCE_BEHAVIOR == STD_ON)
    &Dem_GetBehaviorCounterBased
        /* "get debounce behavior" function for counter-based debouncing */
#endif
#else
    /* counter based debouncing not used - will never be called */
    NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR,
#if (DEM_USE_TRIGGER_DEBOUNCE_BEHAVIOR == STD_ON)
    NULL_PTR
#endif
#endif /* DEM_NUM_DEBOUNCE_COUNTER > 0U */
  },
  /* time based debouncing - DEM_DEBOUNCE_TIMEBASED */
  {
#if (DEM_NUM_DEBOUNCE_TIME > 0U)
    &Dem_ResetDebounceTimeBased,
    &Dem_FreezeDebounceTimeBased,
        /* "freeze counter" function for time-based event debouncing */
    &Dem_DebounceEventTimeBased,
    &Dem_GetFDCTimeBased,
#if (DEM_USE_TRIGGER_DEBOUNCE_BEHAVIOR == STD_ON)
    &Dem_GetBehaviorTimeBased
        /* "get debounce behavior" function for time-based debouncing */
#endif
#else
    /* time based debouncing not used - will never be called */
    NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR,
#if (DEM_USE_TRIGGER_DEBOUNCE_BEHAVIOR == STD_ON)
    NULL_PTR
#endif
#endif /* DEM_NUM_DEBOUNCE_TIME > 0U */
  },
  /* frequency based debouncing - DEM_DEBOUNCE_FREQUENCYBASED */
  {
#if (DEM_NUM_DEBOUNCE_FREQUENCY > 0U)
    &Dem_ResetDebounceFrequencyBased,
    &Dem_FreezeDebounceFrequencyBased,
        /* "freeze counter" function for frequency-based event debouncing */
    &Dem_DebounceEventFrequencyBased,
    &Dem_GetFDCFrequencyBased,
#if (DEM_USE_TRIGGER_DEBOUNCE_BEHAVIOR == STD_ON)
    &Dem_GetBehaviorFrequencyBased
        /* "get debounce behavior" function for frequency-based debouncing */
#endif
#else
    /* frequency based debouncing not used - will never be called */
    NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR,
#if (DEM_USE_TRIGGER_DEBOUNCE_BEHAVIOR == STD_ON)
    NULL_PTR
#endif
#endif /* DEM_NUM_DEBOUNCE_FREQUENCY > 0U */
  }
};

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include <Dem_MemMap.h>

#if (DEM_COMMON_FREEZEFRAMES_USED == STD_ON)
#define DEM_START_SEC_CALIB_16
#include <Dem_MemMap.h>

/* Deviation MISRAC2012-3 */
CONST(Dem_FFClassIdxType, DEM_CONST_CALIBRATION)
  Dem_CommonPartFFClassIdx[DEM_NUM_FFKINDS] =
{
  DEM_COMMON_DEVFFA_CLASS_IDX,
                  /* index of common development freeze frame A class */
  DEM_FFCLS_NULL_IDX,
                  /* freeze frame B class does not have common part */
  DEM_COMMON_FF_CLASS_IDX,
                  /* index of common freeze frame */
  DEM_FFCLS_NULL_IDX
                  /* OBDonUDS freeze frame does not have common part */
};

#define DEM_STOP_SEC_CALIB_16
#include <Dem_MemMap.h>
#endif /* DEM_COMMON_FREEZEFRAMES_USED == STD_ON */

/*==================[internal constants]====================================*/

#if (DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON)
#define DEM_START_SEC_CONST_UNSPECIFIED
#include <Dem_MemMap.h>
/** \brief Pointers to the to StorageOrderIdAndDTCStatus[] arrays from
 ** non volatile gate-entries of the event memory blocks. */
Dem_GateEntryStorageOrderIdAndDTCStatusPtrType Dem_GateEntryStorageOrderIdAndDTCStatus[DEM_MAXNUM_ORIGINS] =
{
#if (DEM_SIZE_STORAGE_ORDER_ID_AND_DTC_STATUS_PRIMARY != 0U)
  &Dem_NvGateEntryPrimaryData.EntryPrimary.StorageOrderIdAndDTCStatus[0U],
#else
  (Dem_GateEntryStorageOrderIdAndDTCStatusPtrType) NULL_PTR,
#endif
#if (DEM_SIZE_STORAGE_ORDER_ID_AND_DTC_STATUS_MIRROR != 0U)
  &Dem_NvGateEntryMirrorData.EntryMirror.StorageOrderIdAndDTCStatus[0U],
#else
  (Dem_GateEntryStorageOrderIdAndDTCStatusPtrType) NULL_PTR,
#endif
  (Dem_GateEntryStorageOrderIdAndDTCStatusPtrType) NULL_PTR,
#if (DEM_SIZE_STORAGE_ORDER_ID_AND_DTC_STATUS_SECONDARY != 0U)
  &Dem_NvGateEntrySecondaryData.EntrySecondary.StorageOrderIdAndDTCStatus[0U]
#else
  (Dem_GateEntryStorageOrderIdAndDTCStatusPtrType) NULL_PTR
#endif
};
#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include <Dem_MemMap.h>
#endif /* DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON */

/*==================[external data]=========================================*/

#define DEM_START_SEC_VAR_SAVED_ZONE_16
#include <Dem_MemMap.h>

#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)
/* Non-volatile permanent memory data of the Dem */
/* !LINKSTO Dem_OBD_0011,2 */
VAR(Dem_PermanentMemoryEntryType, DEM_VAR_CLEARED)
  Dem_EventMemoryPermanent[DEM_MAX_NUMBER_EVENT_ENTRY_PER];
#endif

#define DEM_STOP_SEC_VAR_SAVED_ZONE_16
#include <Dem_MemMap.h>

#define DEM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dem_MemMap.h>

#if ( (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE) &&  \
      (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON) )
/** \brief Array containing the OBD Freeze Frame data and the
 ** occurrence order of the event entries from the primary memory.*/
VAR(Dem_MultipleOBDEventMemoryEntryType, DEM_VAR_CLEARED)
  Dem_EntryOBDFF[DEM_MAX_NUMBER_EVENT_ENTRY_PRI];
#endif

#define DEM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dem_MemMap.h>

#if (DEM_NUM_DEBOUNCE_COUNTER > 0U)
#define DEM_START_SEC_VAR_CLEARED_16
#include <Dem_MemMap.h>

/** \brief per-event status for counter based debouncing */
VAR(Dem_DebounceCounterStatusType, DEM_VAR_CLEARED)
  Dem_DebounceCounterStatus[DEM_NUM_DEBOUNCE_COUNTER];

#define DEM_STOP_SEC_VAR_CLEARED_16
#include <Dem_MemMap.h>
#endif

#define DEM_START_SEC_VAR_CLEARED_8
#include <Dem_MemMap.h>

#if (DEM_OPCYC_NVSTORAGE == STD_OFF)
/** \brief Array of operation cycle states */
VAR(Dem_OperationCycleStateType, DEM_VAR_CLEARED)
  Dem_OpCycleState[DEM_NUM_OPCYCLES];
#endif

#if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
/** \brief Flags to hold validity of the PFFs */
VAR(uint8, DEM_VAR_CLEARED) Dem_PFFEntryValid[
  (DEM_MAX_NUMBER_PRESTORED_FF + 7U) / 8U];
#endif

#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)

/* stored status of permanent entries */
/* !LINKSTO Dem_OBD_0012,1 */
VAR(uint8, DEM_VAR_CLEARED)
  Dem_EventMemoryPermanentNonVolatileStored[DEM_MAX_NUMBER_EVENT_ENTRY_PER];

/* notifier that permanent memory has been updated */
/* !LINKSTO Dem_OBD_0031,1 */
VAR(boolean, DEM_VAR_CLEARED) Dem_EventMemoryPermanentUpdated;
#endif

#define DEM_STOP_SEC_VAR_CLEARED_8
#include <Dem_MemMap.h>

#define DEM_START_SEC_VAR_CLEARED_8
#include <Dem_MemMap.h>
/*------------------[variables for DTC Suppression]-------------------------*/
#if (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION)
/** \brief Bit-field array that holds the UDS DTC suppression status of all events
 ** 0: visible, 1: suppressed */
VAR(uint8, DEM_VAR) Dem_UDSDTCSuppression[DEM_DTC_SUPPRESSION_ARRAY_SIZE];

#if (DEM_OBD_Support == STD_ON)
/** \brief Bit-field array that holds the OBD DTC suppression status of all events
 ** 0: visible, 1: suppressed */
VAR(uint8, DEM_VAR) Dem_OBDDTCSuppression[DEM_DTC_SUPPRESSION_ARRAY_SIZE];
#endif
#if (DEM_J1939_SUPPORT == STD_ON)
/** \brief Bit-field array that holds the J1939 DTC suppression status of all events
 ** 0: visible, 1: suppressed */
VAR(uint8, DEM_VAR) Dem_J1939DTCSuppression[DEM_DTC_SUPPRESSION_ARRAY_SIZE];
#endif
#endif /* DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION */

#define DEM_STOP_SEC_VAR_CLEARED_8
#include <Dem_MemMap.h>

#define DEM_START_SEC_VAR_CLEARED_8
#include <Dem_MemMap.h>

/*------------------[variables for event availability]----------------------*/
#if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
/** \brief Bit-field array that holds the current event available status of all events
 ** 0: disabled/not available, 1: enabled/available */
VAR(uint8, DEM_VAR_CLEARED) Dem_EventAvailableStatus[DEM_EVENT_ENABLED_ARRAY_SIZE];
#endif

/*----------------[variables for event memory existence]--------------------*/
/** \brief Bit-field array that holds the event memory entry existence status
 ** (EvMemEntryExists) for all configured events
 ** 0: no event memory entry exists, 1: event memory entry exists */
VAR(uint8, DEM_VAR_CLEARED) Dem_EvMemEntryExists[DEM_EVTENTRY_EXISTS_ARRAY_SIZE];

#if (DEM_EVENT_CONFIRMATION_THRESHOLD_COUNTER_ADAPTABLE == STD_ON)
/* !LINKSTO Dem.AdaptableConfirmationThreshold.VolatileStorage,1 */
/*----------------[Adaptable Event Failure/Confirmation Thresholds]---------*/
VAR(uint8, DEM_VAR_CLEARED) Dem_ConfirmationThresholdRuntime[DEM_NUMBER_OF_EVENTS];
#endif

#define DEM_STOP_SEC_VAR_CLEARED_8
#include <Dem_MemMap.h>

#define DEM_START_SEC_VAR_INIT_UNSPECIFIED
#include <Dem_MemMap.h>

/** \brief Status of the Dem  */
VAR(Dem_InitializationStateType, DEM_VAR) Dem_InitializationState =
  DEM_UNINITIALIZED;

#define DEM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <Dem_MemMap.h>

/*==================[internal data]=========================================*/

#define DEM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dem_MemMap.h>

#if (DEM_NUM_DEBOUNCE_TIME > 0U)
/** \brief per-event status for time based debouncing */
STATIC VAR(Dem_DebounceTimeStatusType, DEM_VAR_CLEARED)
  Dem_DebounceTimeStatus[DEM_NUM_DEBOUNCE_TIME];
#endif

#if (DEM_NUM_DEBOUNCE_FREQUENCY > 0U)
/** \brief per-event status for frequency based debouncing */
STATIC VAR(Dem_DebounceFrequencyStatusType, DEM_VAR_CLEARED)
  Dem_DebounceFrequencyStatus[DEM_NUM_DEBOUNCE_FREQUENCY];
#endif

#define DEM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include <Dem_MemMap.h>

/*==================[external function definitions]=========================*/

#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*------------------[perform "timer tick" for all running timers]-----------*/

#if (DEM_NUM_DEBOUNCE_FREQUENCY > 0U)
FUNC(void, DEM_CODE) Dem_DebounceFrequencyTimerTick(void)
{
  Dem_EventIdType DebounceIdx;

  DBG_DEM_DEBOUNCEFREQUENCYTIMERTICK_ENTRY();

  /*
   * ENTER critical section to protect debounce status
   *       call-context: any
   */
  DEM_ENTER_EXCLUSIVE_AREA();

  /* Deviation TASKING-1 */
  for (DebounceIdx = 0U;
       DebounceIdx < DEM_NUM_DEBOUNCE_FREQUENCY;
       DebounceIdx++)
  {
    CONSTP2CONST(Dem_DebounceFrequencyCfgType, AUTOMATIC, DEM_CONST)
      DebounceCfg = &Dem_DebounceFrequencyCfg[DebounceIdx];
    const Dem_EventIdType EventId = DebounceCfg->EventId;

    Dem_OperationCycleIdType OperationCycleId = Dem_GbiOpCycleIdx(EventId);

    if (DEM_OPCYCLESTATE[OperationCycleId] != DEM_CYCLE_STATE_END)
    {
      CONSTP2VAR(Dem_DebounceFrequencyStatusType, AUTOMATIC, DEM_VAR_CLEARED)
        DebounceStatus = &Dem_DebounceFrequencyStatus[DebounceIdx];

      /* process only if freeze status is not set.
       * if internal timer for event debouncing is frozen, event debouncing
       * shall not be performed */
      if (DebounceStatus->FreezeStatus != TRUE)
      {
        if (DebounceStatus->InternalTimer != 0U)
        {
          /* timer running -> decrease timer */
          DebounceStatus->InternalTimer--;

          if (DebounceStatus->InternalTimer == 0U)
          {
            /* timer did expire */
            /* if neither threshold is reached within the time window, the
             * event is 'unqualified' (readiness is not set) */
            DebounceStatus->Status = DEM_EVENT_STATUS_UNQUALIFIED;
          }
        }
      }
    }
  } /* for (every frequency based debounced event) */

  /*
   * LEAVE critical section
   */
  DEM_EXIT_EXCLUSIVE_AREA();

  DBG_DEM_DEBOUNCEFREQUENCYTIMERTICK_EXIT();
}
#endif /* (DEM_NUM_DEBOUNCE_FREQUENCY > 0U) */

#if (DEM_NUM_DEBOUNCE_TIME > 0U)
FUNC(void, DEM_CODE) Dem_DebounceTimeTimerTick(void)
{
  Dem_EventIdType DebounceIdx;
  Dem_EventIdType DebounceStartIdx = 0U;

  DBG_DEM_DEBOUNCETIMETIMERTICK_ENTRY();

  do
  {
    Dem_EventStatusType EventDebounceStatus = DEM_EVENT_STATUS_UNQUALIFIED;

    /*
     * ENTER critical section to protect debounce status
     *       call-context: any
     */
    DEM_ENTER_EXCLUSIVE_AREA();

    for (DebounceIdx = DebounceStartIdx;
         DebounceIdx < DEM_NUM_DEBOUNCE_TIME;
         ++DebounceIdx)
    {
      const Dem_OperationCycleIdType OpCycleIdx =
        Dem_GbiOpCycleIdx(Dem_DebounceTimeCfg[DebounceIdx]);

      if (DEM_OPCYCLESTATE[OpCycleIdx] != DEM_CYCLE_STATE_END)
      {
        CONSTP2VAR(Dem_DebounceTimeStatusType, AUTOMATIC, DEM_VAR_CLEARED)
          DebounceStatus = &Dem_DebounceTimeStatus[DebounceIdx];

        /* process only if freeze status is not set.
         * if internal frequency timer for event debouncing is frozen,
         * event debouncing shall not be performed */
        if (DebounceStatus->FreezeStatus != TRUE)
        {
          if (DebounceStatus->InternalTimer != 0U)
          {
            /* timer running -> decrease timer */
            DebounceStatus->InternalTimer--;

            if (DebounceStatus->InternalTimer == 0U)
            {
              /* debouncing complete -> save event status to be used outside of
               * critical section */
              EventDebounceStatus = DebounceStatus->Direction;
              /* increment and save current index to continue later */
              DebounceStartIdx = DebounceIdx;
              /* break from search loop to process event status */
              break;
            }
          }
        }
      }
    } /* for (every time based debounced event) */

    /*
     * LEAVE critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();

    /* check if search loop has completed debouncing for an event */
    if (EventDebounceStatus != DEM_EVENT_STATUS_UNQUALIFIED)
    {
      Std_ReturnType SetStatusResult;
      Dem_EventInfoType EventInfo;
#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U)
      EventInfo.RootId = Dem_DebounceTimeCfg[DebounceIdx];
#endif
      EventInfo.EventId = Dem_DebounceTimeCfg[DebounceIdx];

      /* note: Dem_InternalSetEventStatus(PASSED|FAILED) will call
       * Dem_DebounceEventTimeBased() for the event, which in
       * turn will reset the debouncing status */
      SetStatusResult = Dem_InternalSetEventStatus(EventInfo,
                                   EventDebounceStatus);

      if (SetStatusResult == E_NOT_OK)
      { /* !LINKSTO Dem.DebounceTimeBased.Reset,1 */
        const Dem_EventIdType EventId =
          Dem_DebounceTimeCfg[DebounceIdx];
        CONSTP2VAR(Dem_DebounceTimeStatusType, AUTOMATIC, DEM_VAR_CLEARED)
          DebounceStatus = &Dem_DebounceTimeStatus[DebounceIdx];

        /* the qualification of the event was ignored. DebounceStatus->
         * Direction shall be reset to the current event status.
         * In this way, next time when Dem_DebounceEventTimeBased will be
         * called, the timer and the direction will be reset correctly, but
         * also the value returned by Dem_GetFDCTimeBased will be aligned to
         * the current status of the event.
         * Since the fault detection counter is reset upon starting a new
         * operation cycle (according to Dem.ASR40.SWS_Dem_00344), for debouncing algorithm is
         * relevant only the status of the event during the current operation
         * cycle.
         */

        /*
         * ENTER critical section to protect debounce status
         *       call-context: any
         */
        DEM_ENTER_EXCLUSIVE_AREA();

        if (DEM_IS_ANY_BIT_SET(DEM_DTC_STATUS_MASKS[EventId], DEM_UDS_STATUS_TNCTOC))
        {
          /* the event was not qualified this operation cycle */
          DebounceStatus->Direction = DEM_EVENT_STATUS_UNQUALIFIED;
        }
        else
        {
          if (DEM_IS_ANY_BIT_SET(DEM_DTC_STATUS_MASKS[EventId], DEM_UDS_STATUS_TF))
          {
            /* the event was qualified as failed this operation cycle */
            DebounceStatus->Direction = DEM_EVENT_STATUS_FAILED;
          }
          else
          {
            /* the event was qualified as passed this operation cycle */
            DebounceStatus->Direction = DEM_EVENT_STATUS_PASSED;
          }
        }

        /*
         * LEAVE critical section to protect debounce status
         */
        DEM_EXIT_EXCLUSIVE_AREA();
      }
#if (DEM_DEV_ERROR_DETECT == STD_ON)
      else
      {
        if (SetStatusResult == DEM_E_DET_REPORT)
        {
          /* error-queue overflow happened */
          DEM_REPORT_ERROR(DEM_SID_MainFunction, DEM_E_WRONG_CONFIGURATION);
        }
      }
#endif /* DEM_DEV_ERROR_DETECT */
    }
  } while (DebounceIdx < DEM_NUM_DEBOUNCE_TIME);

  DBG_DEM_DEBOUNCETIMETIMERTICK_EXIT();
}
#endif /* (DEM_NUM_DEBOUNCE_TIME > 0U) */

/*------------------[internal core-function definitions]--------------------*/
#if (DEM_NUM_INDICATOR_LINKS > 0U)

/*------------------[Dem_CheckForEventWIRUpdate]--------------------------*/
FUNC(boolean, DEM_CODE) Dem_CheckForEventWIRUpdate(
  Dem_EventIdType     EventId,
  Dem_EventStatusType EventStatus,
  boolean             FirstFailed)
{
  boolean Result = FALSE;
#if (DEM_CALIBRATION_SUPPORT == STD_ON)
  const boolean IndicatorUsed = TRUE;
#else
  const boolean IndicatorUsed = Dem_GbiIndicatorUsed(EventId);
#endif

  DBG_DEM_CHECKFOREVENTWIRUPDATE_ENTRY(EventId, EventStatus, FirstFailed);

  /* !LINKSTO Dem.WarningIndicator.OnCriteriaFulfilled,1, Dem.ASR40.SWS_Dem_00395,1 */
  /* Deviation TASKING-2 */
  if ( (IndicatorUsed != FALSE) &&
       ( (EventStatus == DEM_EVENT_STATUS_FAILED) ||
         (EventStatus == DEM_EVENT_STATUS_CONFIRMED) ) )
  {
#if (DEM_CALIBRATION_SUPPORT == STD_ON)
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
          if (Dem_ProcessIndicatorFailureCycleCounter(
                                           Idx, EventId, FirstFailed) == TRUE)
          {
            Result = TRUE;
          }
        }
      }
    }
/* calibration is disabled and event availability is not considered */
#else
    Dem_IndicatorIdxType LinkIdx;

    /* Deviation TASKING-1 */
    for (LinkIdx = 0U; LinkIdx < DEM_NUM_INDICATOR_LINKS; ++LinkIdx)
    {
      if (Dem_IndicatorLink[LinkIdx].EventId == EventId)
      {
        if (Dem_ProcessIndicatorFailureCycleCounter(
                                  LinkIdx, EventId, FirstFailed) == TRUE)
        {
          Result = TRUE;
        }
      }
    }
#endif /* DEM_CALIBRATION_SUPPORT == STD_ON */
  }

  DBG_DEM_CHECKFOREVENTWIRUPDATE_EXIT(Result, EventId, EventStatus, FirstFailed);
  return Result;
}

/*------------[Dem_ProcessIndicatorFailureCycleCounter]-------------------*/

FUNC(boolean, DEM_CODE) Dem_ProcessIndicatorFailureCycleCounter(
  Dem_IndicatorIdxType IndicatorIdx,
  Dem_EventIdType      EventId,
  boolean              FirstFailed)
{
  boolean Result = FALSE;
  const Dem_OperationCycleIdType FailureCycleId =
    Dem_GbiIndicatorFailureCycleIdx(EventId, IndicatorIdx);
  const Dem_OperationCycleIdType EventOperationCycle =
    Dem_GbiOpCycleIdx(EventId);

#if (defined DEM_MIL_ID) && \
    ( (DEM_OPCYC_OBD_DCY_USED == STD_ON) || (DEM_MILGROUP_SUPPORT == STD_ON) )
  boolean IsMIL;
#if (DEM_CALIBRATION_SUPPORT == STD_ON)
  CONSTP2CONST(Dem_IndicatorClassType, AUTOMATIC, DEM_CONST) IndicatorClass =
    &Dem_IndicatorClasses[IndicatorIdx];
  IsMIL = (IndicatorClass->IndicatorId == DEM_MIL_ID) ? TRUE : FALSE;
#else
  const uint32 IndMILStart = Dem_IndicatorDesc[DEM_MIL_ID].StartIdx;
  const uint32 IndMILEnd = IndMILStart + Dem_IndicatorDesc[DEM_MIL_ID].Number;
  IsMIL = ((IndicatorIdx >= IndMILStart) && (IndicatorIdx < IndMILEnd)) ? TRUE : FALSE;
#endif
#endif /* (defined DEM_MIL_ID) */

  DBG_DEM_PROCESSINDICATORFAIURECYCLECOUNTER_ENTRY(IndicatorIdx,
                                                   EventId,
                                                   FirstFailed);

  /* !LINKSTO dsn.Dem.ProcessFailureCycleCounter_ProcessCondition,1 */
  /* !LINKSTO Dem.IndicatorFailureCycle.CounterUpdateAndWIRSetting.SameCycle, 1 */
  if (FailureCycleId == EventOperationCycle)
  {
    /* !LINKSTO Dem.WarningIndicator.FailureCounterProcessing.SameCycle, 1 */
    if (FirstFailed == TRUE)
    {
#if ((defined DEM_MIL_ID) && (DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON))
      if (IsMIL && DEM_IS_EVENT_COMBINED(EventId))
      {
        Dem_ProcessCommonMILOnCriteria(IndicatorIdx, EventId);
      }
      else
#endif
      {
        Dem_ProcessIndicatorOnCriteria(IndicatorIdx, EventId);
      }
    }

#if ((DEM_OPCYC_OBD_DCY_USED == STD_ON) && (defined DEM_MIL_ID))
    /* !LINKSTO Dem.OperationCycleQualification.SkipMIL,2 */
    if ((IsMIL == FALSE) || (DEM_IS_CYCLE_QUALIFIED(EventId) == TRUE))
#endif /* (DEM_OPCYC_OBD_DCY_USED == STD_ON) && (defined DEM_MIL_ID) */
    {
      Result = Dem_CheckWIROnCriteriaFulfilled(IndicatorIdx, EventId);
    }
  }

  DBG_DEM_PROCESSINDICATORFAIURECYCLECOUNTER_EXIT(IndicatorIdx,
                                                  EventId,
                                                  FirstFailed,
                                                  Result);
  return Result;
}
#endif /* DEM_NUM_INDICATOR_LINKS */

#if (DEM_USE_TRIGGER_DEBOUNCE_BEHAVIOR == STD_ON)
/*------------------[Dem_TriggerDebounceAlgorithmBehavior]------------------*/

FUNC(void, DEM_CODE) Dem_TriggerDebounceAlgorithmBehavior(
  Dem_EventIdType EventId)
{
  Dem_DebounceBehaviorType DebounceBehavior;
  Dem_DebounceType DebounceAlgo = Dem_GbiDebounceAlgo(EventId);

  DBG_DEM_TRIGGERDEBOUNCEALGORITHMBEHAVIOR_ENTRY(EventId);

  /* ENTER critical section to protect Dem_Debounce[Counter|Time|Frequency]Status
   * as the function is reentrant */
  DEM_ENTER_EXCLUSIVE_AREA();

  /* retrieve debouncing algorithm behavior */
  if (Dem_DebounceFctPtrTable[DebounceAlgo].GetBehaviorFct != NULL_PTR)
  {
    /* the allowed configuration and the check that GetBehaviorFct reference is not a NULL_PTR
     * ensures that GetBehaviorFct() will always return E_OK */
    (void) Dem_DebounceFctPtrTable[DebounceAlgo].GetBehaviorFct(EventId, &DebounceBehavior);

    if (DebounceBehavior == DEM_DEBOUNCE_FREEZE)
    {
      /* freeze corresponding debounce counter */
      /* !LINKSTO Dem.SWS_Dem_00655,1, Dem.ASR42.SWS_Dem_00678,1 */
      Dem_DebounceFctPtrTable[DebounceAlgo].FreezeFct(EventId);
    }
    else if (DebounceBehavior == DEM_DEBOUNCE_RESET)
    {
      /* reset corresponding debounce counter */
      /* !LINKSTO Dem.SWS_Dem_00654,1, Dem.ASR42.SWS_Dem_00677,1 */
      Dem_DebounceFctPtrTable[DebounceAlgo].ResetFct(EventId);
    }
    else
    {
      /* DebounceBehavior is DEM_DEBOUNCE_CONTINUE. This ensures
         backward compatibility. */
    }
  }

  /* LEAVE critical section  */
  DEM_EXIT_EXCLUSIVE_AREA();

  DBG_DEM_TRIGGERDEBOUNCEALGORITHMBEHAVIOR_EXIT(EventId);
}
#endif /* DEM_USE_TRIGGER_DEBOUNCE_BEHAVIOR == STD_ON */

#if (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_TYPE1)
FUNC(Dem_DTCConfIdxType, DEM_CODE) Dem_GbiDTCConfIdx(Dem_EventIdType EventId)
{
  const Dem_DTCConfIdxType Result = DEM_GBI_DTCCONFIDX(EventId);

  DBG_DEM_GBIDTCCONFIDX_ENTRY(EventId);

  DBG_DEM_GBIDTCCONFIDX_EXIT(Result, EventId);
  return Result;
}
#endif /* (DEM_EVENT_COMBINATION_SUPPORT == DEM_EVCOMB_TYPE1) */

FUNC(uint32, DEM_CODE) Dem_GbiUdsDTC(Dem_EventIdType EventId)
{
  const uint32 DTC = DEM_BIT_FIELD_VALUE_32(DEM_DESC_CONF1(EventId),
                                                 DEM_UDS_DTC_OFFSET,
                                                 DEM_UDS_DTC_MASK);

  DBG_DEM_GBIUDSDTC_ENTRY(EventId);

  DBG_DEM_GBIUDSDTC_EXIT(DTC, EventId);
  return DTC;
}

FUNC(uint32, DEM_CODE) Dem_GetUdsDTC(Dem_EventIdType EventId)
{
  uint32 DTC;

  DBG_DEM_GETUDSDTC_ENTRY(EventId);

  DTC = Dem_InternalGetUdsDTC(EventId);

  DBG_DEM_GETUDSDTC_EXIT(EventId, DTC);
  return DTC;
}

FUNC(uint32, DEM_CODE) Dem_GetVisibleUdsDTC(Dem_EventIdType EventId)
{
  uint32 DTC;

  DBG_DEM_GETVISIBLEUDSDTC_ENTRY(EventId);

#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
  if (FALSE == Dem_GbiEvAvailable(EventId))
  {
    DTC = DEM_NO_DTC;
  }
  else
#endif
  {
#if (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION)
    if (DEM_IS_BIT_SET_IN_ARRAY(Dem_UDSDTCSuppression, EventId))
    {
      DTC = DEM_NO_DTC;
    }
    else
#endif
    {
      DTC =  Dem_InternalGetUdsDTC(EventId);
    }
  }

  DBG_DEM_GETVISIBLEUDSDTC_EXIT(DTC, EventId);
  return DTC;
}

#if (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION)
STATIC FUNC(boolean, DEM_CODE) Dem_IsDTCExplicitlySuppressed(
  Dem_DTCFormatType DTCFormat,
  Dem_EventIdType   EventId)
{
  boolean DtcSuppressionStatus = TRUE;

  DBG_DEM_ISDTCEXPLICITLYSUPPRESSED_ENTRY(DTCFormat, EventId);

  switch (DTCFormat)
  {
    case DEM_DTC_FORMAT_OBD:
    case DEM_DTC_FORMAT_OBD_3BYTE:
#if (DEM_OBD_CLASSIC_SUPPORT) || \
    (DEM_OBDONUDS_SUPPORT && (DEM_OBD_DTCVALUE3BYTE_SUPPORT == STD_ON))
      {
        DtcSuppressionStatus = DEM_IS_BIT_SET_IN_ARRAY(Dem_OBDDTCSuppression, EventId);
      }
#endif
      break;
    case DEM_DTC_FORMAT_UDS:
      DtcSuppressionStatus = DEM_IS_BIT_SET_IN_ARRAY(Dem_UDSDTCSuppression, EventId);
      break;
    case DEM_DTC_FORMAT_J1939:
#if (DEM_J1939_SUPPORT == STD_ON)
      DtcSuppressionStatus = DEM_IS_BIT_SET_IN_ARRAY(Dem_J1939DTCSuppression, EventId);
#endif
      break;
    /* CHECK: NOPARSE */
    /* should never be reached */
    default:
      DEM_UNREACHABLE_CODE_ASSERT(DEM_INTERNAL_API_ID);
      break;
    /* CHECK: PARSE */
  }

  DBG_DEM_ISDTCEXPLICITLYSUPPRESSED_EXIT(DtcSuppressionStatus, DTCFormat, EventId);
  return DtcSuppressionStatus;
}
#endif /* (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION) */

#if ( (DEM_OBD_Support == STD_ON) && (defined DEM_MIL_ID) )
FUNC(boolean, DEM_CODE) Dem_MILActivationAllowed(
  Dem_EventIdType   EventId)
{
  boolean Result = FALSE;

  DBG_DEM_MILACTIVATIONALLOWED_ENTRY(EventId);

  if (Dem_GbiDTCKind(EventId) == DEM_DTC_KIND_EMISSION_REL_DTCS)
  {
#if (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION)
    Dem_DTCFormatType DTCFormat = DEM_DTC_FORMAT_OBD;

#if (DEM_OBDONUDS_SUPPORT)
#if (DEM_OBD_VARIANT_SELECTABLE == STD_ON)
    if (DEM_GET_OBD_VARIANT() == DEM_OBD_VARIANT_OBDONUDS)
#endif
    {
#if (DEM_OBD_DTCVALUE3BYTE_SUPPORT == STD_ON)
      DTCFormat = DEM_DTC_FORMAT_OBD_3BYTE;
#else
      DTCFormat = DEM_DTC_FORMAT_UDS;
#endif
    }
#endif /* DEM_OBDONUDS_SUPPORT */
    if (Dem_IsDTCExplicitlySuppressed(DTCFormat, EventId) == FALSE)
#endif /* (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION) */
    {
      Result = TRUE;
#if (DEM_OBDONUDS_SUPPORT && (DEM_OBD_DTCVALUE3BYTE_SUPPORT == STD_OFF))
#if (DEM_OBD_VARIANT_SELECTABLE == STD_ON)
      if (DEM_GET_OBD_VARIANT() == DEM_OBD_VARIANT_OBDONUDS)
#endif
      {
        /* !LINKSTO dsn.Dem.ObdRelevance.WithoutDtcSeparation,1 */
        /* Check if DemUdsDtc available otherwise skip the MIL activation */
        if (Dem_GetVisibleUdsDTC(EventId) == DEM_NO_DTC)
        {
          Result = FALSE;
        }
      }
#endif /*(DEM_OBDONUDS_SUPPORT && (DEM_OBD_DTCVALUE3BYTE_SUPPORT == STD_OFF))*/
    }
  }

  DBG_DEM_MILACTIVATIONALLOWED_EXIT(Result, EventId);
  return Result;
}
#endif /* (DEM_OBD_Support == STD_ON) && (defined DEM_MIL_ID) */

STATIC FUNC(uint32, DEM_CODE) Dem_InternalGetDTC(
  Dem_DTCFormatType DTCFormat,
  Dem_EventIdType   EventId)
{
  uint32 DTC = DEM_NO_DTC;

  DBG_DEM_INTERNALGETDTC_ENTRY(DTCFormat, EventId);

  switch (DTCFormat)
  {
    case DEM_DTC_FORMAT_OBD:
#if (DEM_OBD_CLASSIC_SUPPORT)
      {
        DTC = Dem_InternalGetObdDTC(EventId);
      }
#endif
      break;
    case DEM_DTC_FORMAT_OBD_3BYTE:
#if (DEM_OBDONUDS_SUPPORT && (DEM_OBD_DTCVALUE3BYTE_SUPPORT == STD_ON))
      {
        DTC = Dem_InternalGetObdDTCValue3Byte(EventId);
      }
#endif
      break;
    case DEM_DTC_FORMAT_UDS:
      DTC = Dem_InternalGetUdsDTC(EventId);
      break;
    case DEM_DTC_FORMAT_J1939:
#if (DEM_J1939_SUPPORT == STD_ON)
      DTC = Dem_InternalGetJ1939DTC(EventId);
#endif
      break;
    /* CHECK: NOPARSE */
    /* should never be reached */
    default:
      DEM_UNREACHABLE_CODE_ASSERT(DEM_INTERNAL_API_ID);
      break;
    /* CHECK: PARSE */
  }

  DBG_DEM_INTERNALGETDTC_EXIT(DTC, DTCFormat, EventId);
  return DTC;
}

FUNC(uint32, DEM_CODE) Dem_GetVisibleCmbDTC(
  Dem_DTCFormatType DTCFormat,
  Dem_EventIdType   EventId)
{
  uint32 DTC = DEM_NO_DTC;

  DBG_DEM_GETVISIBLECMBDTC_ENTRY(DTCFormat, EventId);

#if (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION)
  if(FALSE == Dem_IsDTCExplicitlySuppressed(DTCFormat, EventId))
#endif
  {
#if ( (DEM_NUM_CMB_DTCS > 0U) && \
      (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY) )
    const Dem_DTCConfIdxType DTCConfIdx = DEM_GBI_DTCCONFIDX(EventId);
    if (DEM_IS_DTC_COMBINED(DTCConfIdx))
    {
      /* search for first visible UDS DTC of the combined events */

      const Dem_CmbDTCEvLnkType firstCmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx];
      const Dem_CmbDTCEvLnkType LastCmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx + 1U] - 1U;
      Dem_CmbDTCEvLnkType CmbEvIdx;
      for (CmbEvIdx = firstCmbEvIdx; CmbEvIdx <= LastCmbEvIdx; CmbEvIdx++)
      {
        const Dem_EventIdType CmbEventId = Dem_CmbDTCEvents[CmbEvIdx];
        DTC = Dem_InternalGetDTC(DTCFormat, CmbEventId);
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
        if ( (DTC != DEM_NO_DTC) && (FALSE == Dem_GbiEvAvailable(CmbEventId) ) )
        {
          DTC = DEM_NO_DTC;
        }
        else
        {
          break;
        }
#endif
      }
    }
    else
#endif /* (DEM_NUM_CMB_DTCS > 0U) && \
            (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY) */
    {
      /* event is not combined */
        DTC = Dem_InternalGetDTC(DTCFormat, EventId);
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
        if ( (DTC != DEM_NO_DTC) && (FALSE == Dem_GbiEvAvailable(EventId) ) )
        {
          DTC = DEM_NO_DTC;
        }
#endif

    }
  }

  DBG_DEM_GETVISIBLECMBDTC_EXIT(DTC, DTCFormat, EventId);
  return DTC;
}

/* !LINKSTO Dem.Interfaces.J1939Dcm_DemTriggerOnDTCStatus,1 */
#if ((DEM_J1939_SUPPORT == STD_ON) && (DEM_J1939_READING_DTC_SUPPORT == STD_ON))
FUNC(void, DEM_CODE) Dem_CbTriggerJ1939Dcm(Dem_EventIdType EventId)
{
  uint32 DTC;
  DBG_DEM_CBTRIGGERJ1939DCM_ENTRY(EventId);
  DTC = Dem_InternalGetJ1939DTC(EventId);
  if(DTC != DEM_NO_DTC)
  {
    /* !LINKSTO Dem.J1939.Dcm_DemTriggerOnDTCStatus,1 */
    J1939Dcm_DemTriggerOnDTCStatus(DTC);
  }
  DBG_DEM_CBTRIGGERJ1939DCM_EXIT(EventId);
}
#endif

/* !LINKSTO Dem_OBD_0001,2 */
#if (DEM_OBD_Support == STD_ON)
FUNC(uint32, DEM_CODE) Dem_GetObdDTC(Dem_EventIdType EventId)
{
  uint32 DTC;

  DBG_DEM_GETOBDDTC_ENTRY(EventId);

  DTC = Dem_InternalGetObdDTC(EventId);

  DBG_DEM_GETOBDDTC_EXIT(EventId, DTC);
  return DTC;
}

#if (DEM_OBD_DTCVALUE3BYTE_SUPPORT == STD_ON)
FUNC(uint32, DEM_CODE) Dem_GetObdDTCValue3Byte(Dem_EventIdType EventId)
{
  uint32 DTC;

  DBG_DEM_GETOBDDTCVALUE3BYTE_ENTRY(EventId);

  DTC = Dem_InternalGetObdDTCValue3Byte(EventId);

  DBG_DEM_GETOBDDTCVALUE3BYTE_EXIT(EventId, DTC);
  return DTC;
}

FUNC(uint32, DEM_CODE) Dem_GetVisibleObdDTCValue3Byte(Dem_EventIdType EventId)
{
  uint32 DTC;

  DBG_DEM_GETVISIBLEOBDDTCVALUE3BYTE_ENTRY(EventId);

#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
  if (FALSE == Dem_GbiEvAvailable(EventId))
  {
    DTC = DEM_NO_DTC;
  }
  else
#endif
  {
#if (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION)
    if (DEM_IS_BIT_SET_IN_ARRAY(Dem_OBDDTCSuppression, EventId))
    {
      DTC = DEM_NO_DTC;
    }
    else
#endif
    {
      DTC = Dem_InternalGetObdDTCValue3Byte(EventId);
    }
  }

  DBG_DEM_GETVISIBLEOBDDTCVALUE3BYTE_EXIT(DTC, EventId);
  return DTC;
}
#endif /* (DEM_OBD_DTCVALUE3BYTE_SUPPORT == STD_ON) */

FUNC(Dem_DTCKindType, DEM_CODE) Dem_GbiDTCKind(Dem_EventIdType EventId)
{
  /* !LINKSTO dsn.Dem.ObdRelevance.OBDClassic.WithVariantSwitch,1 */
  /* !LINKSTO dsn.Dem.ObdRelevance.WithoutDtcSeparation,1 */
  uint32 DTC = DEM_NO_DTC;
  Dem_DTCKindType DTCKind = DEM_DTC_KIND_ALL_DTCS;
#if ((DEM_OBD_CLASSIC_SUPPORT) || (DEM_OBD_DTCVALUE3BYTE_SUPPORT == STD_OFF))
  DTC = (uint32)Dem_OBDDTC[DEM_DESC_OBD_IDX(EventId)];
#endif
  DBG_DEM_GBIDTCKIND_ENTRY(EventId);

#if (DEM_OBD_DTCVALUE3BYTE_SUPPORT == STD_ON)
#if (DEM_OBD_VARIANT_SELECTABLE == STD_ON)
  if (DEM_GET_OBD_VARIANT() == DEM_OBD_VARIANT_OBDONUDS)
#endif
  {
    /* !LINKSTO dsn.Dem.ObdRelevance.WithVariantSwitch.WithDtcSeparation,1 */
    DTC = Dem_InternalGetObdDTCValue3Byte(EventId);
  }
#endif

  if (DTC != DEM_NO_DTC)
  {
    DTCKind = DEM_DTC_KIND_EMISSION_REL_DTCS;
  }

  DBG_DEM_GBIDTCKIND_EXIT(DTCKind, EventId);
  return DTCKind;
}
#endif /* (DEM_OBD_Support == STD_ON) */

FUNC(boolean, DEM_CODE) Dem_IsInternalEvent(Dem_EventIdType EventId)
{
  boolean Result = FALSE;

  DBG_DEM_ISINTERNALEVENT_ENTRY(EventId);

  if (Dem_GbiUdsDTC(EventId) == DEM_NO_DTC)
  {
#if (DEM_OBD_Support == STD_ON)
    if (Dem_InternalGetObdDTC(EventId) == DEM_NO_DTC)
#endif
    {
#if (DEM_OBDONUDS_SUPPORT && (DEM_OBD_DTCVALUE3BYTE_SUPPORT == STD_ON))
      if (Dem_InternalGetObdDTCValue3Byte(EventId) == DEM_NO_DTC)
#endif
      {
#if (DEM_J1939_SUPPORT == STD_ON)
        if (Dem_InternalGetJ1939DTC(EventId) == DEM_NO_DTC)
#endif
        {
          Result = TRUE;
        }
      }
    }
  }

  DBG_DEM_ISINTERNALEVENT_EXIT(Result, EventId);
  return Result;
}

FUNC(Dem_DTCOriginType, DEM_CODE) Dem_GbiDTCOrigin(Dem_EventIdType EventId)
{
  /* the 4 different AUTOSAR values of DTC Origin are packed into two bits in
     event description, therefore these values are transformed */
  const Dem_DTCOriginType Result =
    (Dem_DTCOriginType)(
      DEM_BIT_FIELD_VALUE_32(
        DEM_DESC_CONF1(EventId),
        DEM_DTCORIGIN_OFFSET,
        DEM_DTCORIGIN_MASK) +
        DEM_DTC_ORIGIN_PRIMARY_MEMORY);

  DBG_DEM_GBIDTCORIGIN_ENTRY(EventId);

  DBG_DEM_GBIDTCORIGIN_EXIT(Result, EventId);
  return Result;
}

FUNC(uint8, DEM_CODE) Dem_GbiDTCOriginIdx(Dem_EventIdType EventId)
{
  const uint8 Result = (uint8)DEM_BIT_FIELD_VALUE_32(
                                DEM_DESC_CONF1(EventId),
                                DEM_DTCORIGIN_OFFSET,
                                DEM_DTCORIGIN_MASK);

  DBG_DEM_GBIDTCORIGINIDX_ENTRY(EventId);

  DBG_DEM_GBIDTCORIGINIDX_EXIT(Result, EventId);
  return Result;
}

FUNC(uint8, DEM_CODE) Dem_GbiDTCGroupIdx(Dem_EventIdType EventId)
{
  const uint8 Result =
    (uint8)DEM_BIT_FIELD_VALUE_32(
      DEM_DESC_CONF2(EventId),
      DEM_DTCGROUP_OFFSET,
      DEM_DTCGROUP_MASK);

  DBG_DEM_GBIDTCGROUPIDX_ENTRY(EventId);

  DBG_DEM_GBIDTCGROUPIDX_EXIT(Result, EventId);
  return Result;
}

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
FUNC(boolean, DEM_CODE) Dem_GbiImmediateStorage(Dem_EventIdType EventId)
{
  const boolean Result =
    (boolean)DEM_BIT_FIELD_VALUE_32(
      DEM_DESC_CONF1(EventId),
      DEM_IMMEDIATESTORAGE_OFFSET,
      DEM_IMMEDIATESTORAGE_MASK);

  DBG_DEM_GBIIMMEDIATESTORAGE_ENTRY(EventId);

  DBG_DEM_GBIIMMEDIATESTORAGE_EXIT(Result, EventId);
  return Result;
}
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */

FUNC(Dem_DTCSeverityType, DEM_CODE) Dem_GbiDTCSeverity(
  Dem_EventIdType EventId)
{
  const uint8 sevNo =
    (uint8)DEM_BIT_FIELD_VALUE_32(DEM_DESC_CONF1(EventId),
                                  DEM_DTCSEVERITY_OFFSET,
                                  DEM_DTCSEVERITY_MASK);

  /* the bit-packed value represented on 2 bits is translated to the
   * mask values representing the defined severity range */
  Dem_DTCSeverityType Result =
    (Dem_DTCSeverityType)(
      (sevNo == 0U) ? DEM_SEVERITY_NO_SEVERITY :
      ( (sevNo == 1U) ? DEM_SEVERITY_MAINTENANCE_ONLY :
        ( (sevNo == 2U) ? DEM_SEVERITY_CHECK_AT_NEXT_HALT :
          DEM_SEVERITY_CHECK_IMMEDIATELY) ) );

  DBG_DEM_GBIDTCSEVERITY_ENTRY(EventId);

  DBG_DEM_GBIDTCSEVERITY_EXIT(Result, EventId);
  return Result;
}

FUNC(uint8, DEM_CODE) Dem_GbiDTCFunctionalUnit(Dem_EventIdType EventId)
{
  const uint8 Result =
    (uint8)DEM_BIT_FIELD_VALUE_32(
      DEM_DESC_CONF3(EventId),
      DEM_DTCFUNCTIONALUNIT_OFFSET,
      DEM_DTCFUNCTIONALUNIT_MASK);

  DBG_DEM_GBIDTCFUNCTIONALUNIT_ENTRY(EventId);

  DBG_DEM_GBIDTCFUNCTIONALUNIT_EXIT(Result, EventId);
  return Result;
}

#if ((DEM_DEV_ERROR_DETECT == STD_ON) || (DEM_MAX_NUMBER_PRESTORED_FF > 0U))
FUNC(boolean, DEM_CODE) Dem_GbiEnablePrestorage(Dem_EventIdType EventId)
{
#if (DEM_MAX_NUMBER_PRESTORED_FF == 0U)
  const boolean Result = FALSE;

  TS_PARAM_UNUSED(EventId);
#else
  const boolean Result =
    (boolean)DEM_BIT_FIELD_VALUE_32(
      DEM_DESC_CONF4(EventId),
      DEM_ENABLEPRESTORAGE_OFFSET,
      DEM_ENABLEPRESTORAGE_MASK);
#endif

  DBG_DEM_GBIENABLEPRESTORAGE_ENTRY(EventId);

  DBG_DEM_GBIENABLEPRESTORAGE_EXIT(Result, EventId);
  return Result;
}
#endif /* (DEM_DEV_ERROR_DETECT == STD_ON) || (DEM_MAX_NUMBER_PRESTORED_FF > 0U) */

FUNC(Dem_FFClassIdxType, DEM_CODE) Dem_GbiFFClassIdx(Dem_EventIdType EventId)
{
  const Dem_FFClassIdxType Result =
    (Dem_FFClassIdxType)DEM_BIT_FIELD_VALUE_32(
      DEM_DESC_CONF2(EventId),
      DEM_FFCLASSIDX_OFFSET,
      DEM_FFCLASSIDX_MASK);

  DBG_DEM_GBIFFCLASSIDX_ENTRY(EventId);

  DBG_DEM_GBIFFCLASSIDX_EXIT(Result, EventId);
  return Result;
}

FUNC(Dem_EvSignificanceType, DEM_CODE) Dem_GbiEvSignificance(
  Dem_EventIdType EventId)
{
  const Dem_EvSignificanceType Result =
    (Dem_EvSignificanceType)DEM_BIT_FIELD_VALUE_32(
        DEM_DESC_SIGNIFICANCE(EventId),
        DEM_EVENTSIGNIFICANCE_OFFSET,
        DEM_EVENTSIGNIFICANCE_MASK);

  DBG_DEM_GBIEVSIGNIFICANCE_ENTRY(EventId);

  DBG_DEM_GBIEVSIGNIFICANCE_EXIT(Result, EventId);
  return Result;
}

#if (DEM_NUM_FFSEGS > 0U)
FUNC(Dem_FFIdxType, DEM_CODE) Dem_GbiMaxNumFFRecs(Dem_EventIdType EventId)
{
  Dem_FFIdxType Result;

#if (DEM_FREEZE_FRAME_REC_NUMERATION_TYPE == DEM_FF_RECNUM_CALCULATED)
  Result =
    (Dem_FFIdxType)DEM_BIT_FIELD_VALUE_32(
        DEM_DESC_CONF2(EventId),
      DEM_FFRECINFO_OFFSET,
      DEM_FFRECINFO_MASK);
#else  /*DEM_FREEZE_FRAME_REC_NUMERATION_TYPE == DEM_FF_RECNUM_CONFIGURED*/
  Result =
    Dem_FFRecNumerationClass[Dem_GbiFFRecNumClassIdx(EventId)].NumFFRecs;
#endif

  DBG_DEM_GBIMAXNUMFFRECS_ENTRY(EventId);
  DBG_DEM_GBIMAXNUMFFRECS_EXIT(Result, EventId);
  return Result;
}
#endif /* (DEM_NUM_FFSEGS > 0U) */

#if (DEM_FREEZE_FRAME_REC_NUMERATION_TYPE == DEM_FF_RECNUM_CONFIGURED)
FUNC(Dem_FFRecNumClassIdxType, DEM_CODE) Dem_GbiFFRecNumClassIdx(
  Dem_EventIdType EventId)
{
  const Dem_FFRecNumClassIdxType Result =
    (Dem_FFRecNumClassIdxType)DEM_BIT_FIELD_VALUE_32(
      DEM_DESC_CONF2(EventId),
      DEM_FFRECINFO_OFFSET,
      DEM_FFRECINFO_MASK);

  DBG_DEM_GBIFFRECNUMCLASSIDX_ENTRY(EventId);

  DBG_DEM_GBIFFRECNUMCLASSIDX_EXIT(Result, EventId);
  return Result;
}
#endif /* (DEM_FREEZE_FRAME_REC_NUMERATION_TYPE == DEM_FF_RECNUM_CONFIGURED) */

FUNC(Dem_EDClassIdxType, DEM_CODE) Dem_GbiEDClassIdx(Dem_EventIdType EventId)
{
  const Dem_EDClassIdxType Result =
    (Dem_EDClassIdxType)DEM_BIT_FIELD_VALUE_32(
      DEM_DESC_CONF2(EventId),
      DEM_EDCLASSIDX_OFFSET,
      DEM_EDCLASSIDX_MASK);

  DBG_DEM_GBIEDCLASSIDX_ENTRY(EventId);

  DBG_DEM_GBIEDCLASSIDX_EXIT(Result, EventId);
  return Result;
}

FUNC(Dem_OperationCycleIdType, DEM_CODE) Dem_GbiOpCycleIdx(
  Dem_EventIdType EventId)
{

#if ( (DEM_COMMON_OPERATION_CYCLE_SUPPORT == STD_ON) && \
      (DEM_CALIBRATION_WITHOUTEVCOMB_SUPPORT == STD_ON) )
  /* !LINKSTO Dem.OperationCycle.Common,1 */
  const Dem_OperationCycleIdType Result =
    Dem_EventClassDesc[DEM_GBI_EVENTCLASSDESCIDX(EventId)].CommonOperationCycle;
#else
  const Dem_OperationCycleIdType Result =
    (Dem_OperationCycleIdType)DEM_BIT_FIELD_VALUE_32(
      DEM_DESC_CONF5(EventId),
      DEM_OPCYCLEIDX_OFFSET,
      DEM_OPCYCLEIDX_MASK);
#endif /* (DEM_COMMON_OPERATION_CYCLE_SUPPORT == STD_ON) && \
          (DEM_CALIBRATION_WITHOUTEVCOMB_SUPPORT == STD_ON) */

  DBG_DEM_GBIOPCYCLEIDX_ENTRY(EventId);

  DBG_DEM_GBIOPCYCLEIDX_EXIT(Result, EventId);
  return Result;
}

#if ( (DEM_NUM_INDICATOR_LINKS != 0) && \
      (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD) )
FUNC(Dem_OperationCycleIdType, DEM_CODE) Dem_GbiIndicatorHealingCycleIdx(
  Dem_EventIdType      EventId,
  Dem_IndicatorIdxType IndicatorIdx)
{
#if (DEM_COMMON_OPERATION_CYCLE_SUPPORT == STD_OFF)
#if (DEM_CALIBRATION_SUPPORT == STD_ON)

  const Dem_OperationCycleIdType Result =
    Dem_IndicatorClasses[IndicatorIdx].HealingCycle;

#else /* DEM_CALIBRATION_SUPPORT == STD_OFF */

  const Dem_HealingCycleCounterInfoIdxType HealingCycleCounterInfoIdx =
    Dem_IndicatorLink[IndicatorIdx].HealingCycleCounterInfoIdx;
  const Dem_OperationCycleIdType Result =
    Dem_HealingCycleCounterInfo[HealingCycleCounterInfoIdx].OperationCycleRef;

#endif /* DEM_CALIBRATION_SUPPORT == STD_ON */

  TS_PARAM_UNUSED(EventId);

#else /* DEM_COMMON_OPERATION_CYCLE_SUPPORT == STD_OFF */

  const Dem_OperationCycleIdType Result = Dem_GbiOpCycleIdx(EventId);

  TS_PARAM_UNUSED(IndicatorIdx);

#endif /* (DEM_COMMON_OPERATION_CYCLE_SUPPORT == STD_OFF) */

  DBG_DEM_GBIINDICATORHEALINGCYCLEIDX_ENTRY(EventId, IndicatorIdx);

  DBG_DEM_GBIINDICATORHEALINGCYCLEIDX_EXIT(Result, EventId, IndicatorIdx);
  return Result;
}
#endif /* (DEM_NUM_INDICATOR_LINKS != 0) && \
          (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD) */

#if (DEM_NUM_INDICATOR_LINKS != 0)
FUNC(Dem_OperationCycleIdType, DEM_CODE) Dem_GbiIndicatorFailureCycleIdx(
  Dem_EventIdType      EventId,
  Dem_IndicatorIdxType IndicatorIdx)
{
#if (DEM_COMMON_OPERATION_CYCLE_SUPPORT == STD_OFF)
#if (DEM_CALIBRATION_SUPPORT == STD_ON)

  const Dem_OperationCycleIdType Result =
    Dem_IndicatorClasses[IndicatorIdx].FailureCycle;

#else /* DEM_CALIBRATION_SUPPORT == STD_OFF */

  const Dem_FailureCycleCounterInfoIdxType FailureCycleCounterInfoIdx =
    Dem_IndicatorLink[IndicatorIdx].FailureCycleCounterInfoIdx;
  const Dem_OperationCycleIdType Result =
    Dem_FailureCycleCounterInfo[FailureCycleCounterInfoIdx].OperationCycleRef;

#endif /* DEM_CALIBRATION_SUPPORT == STD_ON */

  TS_PARAM_UNUSED(EventId);

#else /* DEM_COMMON_OPERATION_CYCLE_SUPPORT == STD_OFF */

  const Dem_OperationCycleIdType Result = Dem_GbiOpCycleIdx(EventId);

  TS_PARAM_UNUSED(IndicatorIdx);

#endif /* DEM_COMMON_OPERATION_CYCLE_SUPPORT == STD_OFF */

  DBG_DEM_GBIINDICATORFAILURECYCLEIDX_ENTRY(EventId, IndicatorIdx);

  DBG_DEM_GBIINDICATORFAILURECYCLEIDX_EXIT(Result, EventId, IndicatorIdx);
  return Result;
}
#endif /* DEM_NUM_INDICATOR_LINKS != 0 */

#if (DEM_USE_AGING == STD_ON)
FUNC(Dem_AgingCyclesType, DEM_CODE) Dem_GbiNumAgingCycles(
  Dem_EventIdType EventId)
{

#if (DEM_CALIBRATION_WITHOUTEVCOMB_SUPPORT == STD_ON)
  const Dem_AgingCyclesType Result =
      Dem_EventClassDesc[DEM_GBI_EVENTCLASSDESCIDX(EventId)].AgingCycleCounterThreshold;
#else
  const Dem_AgingCyclesType Result =
    (Dem_AgingCyclesType)DEM_BIT_FIELD_VALUE_32(
      DEM_DESC_CONF2(EventId),
      DEM_AGINGCTRTHRESHOLD_OFFSET,
      DEM_AGINGCTRTHRESHOLD_MASK);
#endif

  DBG_DEM_GBINUMAGINGCYCLES_ENTRY(EventId);

  DBG_DEM_GBINUMAGINGCYCLES_EXIT(Result, EventId);
  return Result;
}
#endif /* DEM_USE_AGING == STD_ON */

#if (DEM_NUM_AGINGCYCLES > 0U)
FUNC(Dem_OperationCycleIdType, DEM_CODE) Dem_GbiAgingCycleIdx(
  Dem_EventIdType EventId)
{

#if (DEM_COMMON_OPERATION_CYCLE_SUPPORT == STD_ON)
  const Dem_OperationCycleIdType Result = Dem_GbiOpCycleIdx(EventId);
#else
  /* calculate absolute aging cycle Id/index */
  const Dem_OperationCycleIdType Result =
    (Dem_OperationCycleIdType)(
      DEM_BIT_FIELD_VALUE_32(
        DEM_DESC_CONF3(EventId),
        DEM_AGINGCYCLEIDX_OFFSET,
        DEM_AGINGCYCLEIDX_MASK));
#endif /* DEM_COMMON_OPERATION_CYCLE_SUPPORT == STD_ON */
  DBG_DEM_GBIAGINGCYCLEIDX_ENTRY(EventId);

  DBG_DEM_GBIAGINGCYCLEIDX_EXIT(Result, EventId);
  return Result;
}
#endif /* DEM_NUM_AGINGCYCLES > 0U */

FUNC(uint16, DEM_CODE) Dem_GbiEventFailureClassIdx(Dem_EventIdType EventId)
{
  const uint16 Result =
    (uint16)DEM_BIT_FIELD_VALUE_32(
      DEM_DESC_CONF6(EventId),
      DEM_EVENTFAILURECLASSIDX_OFFSET,
      DEM_EVENTFAILURECLASSIDX_MASK);

  DBG_DEM_GBIEVENTFAILURECLASSIDX_ENTRY(EventId);

  DBG_DEM_GBIEVENTFAILURECLASSIDX_EXIT(Result, EventId);
  return Result;
}

#if (DEM_NUM_FAILURECYCLES > 0U)
FUNC(Dem_OperationCycleIdType, DEM_CODE) Dem_GbiEventFailureCycleIdx(
  Dem_EventIdType EventId,
  uint16          EventFailureClassIdx)
{
#if (DEM_COMMON_OPERATION_CYCLE_SUPPORT == STD_OFF)
  const Dem_OperationCycleIdType Result =
    Dem_EventFailureCycleCfg[EventFailureClassIdx].EventFailureCycleIdx;

  TS_PARAM_UNUSED(EventId);
#else
  const Dem_OperationCycleIdType Result = Dem_GbiOpCycleIdx(EventId);

  TS_PARAM_UNUSED(EventFailureClassIdx);
#endif

  DBG_DEM_GBIEVENTFAILURECYCLEIDX_ENTRY(EventId, EventFailureClassIdx);

  DBG_DEM_GBIEVENTFAILURECYCLEIDX_EXIT(Result, EventId, EventFailureClassIdx);
  return Result;
}
#endif /* DEM_NUM_FAILURECYCLES > 0U */

#if (DEM_NUM_ENCONDGROUPS > 0U)
FUNC(Dem_EnCondGrpIdxType, DEM_CODE) Dem_GbiEnCondGrpIdx(
  Dem_EventIdType EventId)
{

#if (DEM_CALIBRATION_WITHOUTEVCOMB_SUPPORT == STD_ON)
  const Dem_EnCondGrpIdxType Result =
      Dem_EventClassDesc[DEM_GBI_EVENTCLASSDESCIDX(EventId)].EnableConditionGroupRef;
#else
  const Dem_EnCondGrpIdxType Result =
    (Dem_EnCondGrpIdxType)DEM_BIT_FIELD_VALUE_32(
      DEM_DESC_CONF6(EventId),
      DEM_ENCONDGRPIDX_OFFSET,
      DEM_ENCONDGRPIDX_MASK);
#endif

  DBG_DEM_GBIENCONDGRPIDX_ENTRY(EventId);

  DBG_DEM_GBIENCONDGRPIDX_EXIT(Result, EventId);
  return Result;
}
#endif /* DEM_NUM_ENCONDGROUPS > 0U */

#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U)
FUNC(Dem_MultiEventTriggeringMasterIdxType, DEM_CODE)
  Dem_GetMultiEventTriggeringMasterIdx(Dem_EventIdType EventId)
{
  /* using signed variables for indices due to overflow use-cases:
   * - if EventId is smaller than all elements in array then
   *   RightIdx will be 255 after last subtraction */
  sint32 LeftIdx = 0;
  sint32 RightIdx = (sint32)DEM_MULTIEVENTTRIGGERINGMASTERIDX_UNUSED - 1;
  sint32 MiddleIdx;
  Dem_MultiEventTriggeringMasterIdxType Result = DEM_MULTIEVENTTRIGGERINGMASTERIDX_UNUSED;

  DBG_DEM_GETMULTIEVENTTRIGGERINGMASTERIDX_ENTRY(EventId);

  while (LeftIdx <= RightIdx)
  {
    /* in order to handle overflow situations don't
     * compute MiddleIdx as follows:
     * MiddleIdx = (LeftIdx + RightIdx) / 2 */
    MiddleIdx = LeftIdx + ((RightIdx - LeftIdx) / 2);

    if (EventId == Dem_MultiEventTriggeringMasterEventId[MiddleIdx])
    {
      /* if EventId found, set Result and break loop */
      Result = (Dem_MultiEventTriggeringMasterIdxType)MiddleIdx;
      break;
    }

    if (Dem_MultiEventTriggeringMasterEventId[MiddleIdx] < EventId)
    {
      /* if EventId is bigger, ignore the left half */
      LeftIdx = MiddleIdx + 1;
    }
    else
    {
      /* if EventId is smaller, ignore the right half */
      RightIdx = MiddleIdx - 1;
    }
  }

  DBG_DEM_GETMULTIEVENTTRIGGERINGMASTERIDX_EXIT(Result, EventId);
  return Result;
}

FUNC(Dem_MultiEventTriggeringClassIdxType, DEM_CODE) Dem_GbiMultiEventTriggeringIdx(
  Dem_EventIdType EventId)
{
#if (DEM_CALIBRATION_WITHOUTEVCOMB_SUPPORT == STD_ON)
  /* !LINKSTO dsn.Dem.Configuration.EvConf4.EventCombinationDisabled,1 */
  const Dem_MultiEventTriggeringClassIdxType Result =
      Dem_EventClassDesc[DEM_GBI_EVENTCLASSDESCIDX(EventId)].MultiEventTriggeringClassIdx;
#else
  /* !LINKSTO dsn.Dem.Configuration.EvConf2.EventCombinationEnabled,1 */
  const Dem_MultiEventTriggeringClassIdxType Result =
    (Dem_MultiEventTriggeringClassIdxType)DEM_BIT_FIELD_VALUE_16(
      DEM_DESC_CONF7(EventId),
      DEM_MULTIEVENTTRIGGERINGIDX_OFFSET,
      DEM_MULTIEVENTTRIGGERINGIDX_MASK);
#endif

  DBG_DEM_GBIMULTIEVENTTRIGGERINGIDX_ENTRY(EventId);

  DBG_DEM_GBIMULTIEVENTTRIGGERINGIDX_EXIT(Result, EventId);
  return Result;
}

FUNC_P2CONST(Dem_MultiEventTriggeringType, AUTOMATIC, DEM_CODE)
  Dem_GetMultiEventTriggering(Dem_EventIdType EventId)
{
  P2CONST(Dem_MultiEventTriggeringType, AUTOMATIC, AUTOMATIC) Result = NULL_PTR;

  DBG_DEM_GETMULTIEVENTTRIGGERING_ENTRY(EventId);

  if (Dem_GbiMultiEventTriggeringIdx(EventId) != DEM_MULTIEVENTTRIGGERINGIDX_UNUSED)
  {
    Result = &Dem_MultiEventTriggeringClasses[Dem_GbiMultiEventTriggeringIdx(EventId)];
  }

  DBG_DEM_GETMULTIEVENTTRIGGERING_EXIT(Result, EventId);
  return Result;
}

FUNC(Dem_EventIdType, DEM_CODE) Dem_FindNextDependentEvent(
  Dem_EventIdType                              RootId,
  Std_ReturnType                               LastRetVal,
  P2VAR(Dem_EventIdType, AUTOMATIC, AUTOMATIC) LastEventId
)
{
  Dem_EventIdType NextEventId = DEM_EVENT_ID_INVALID;
  P2CONST(Dem_MultiEventTriggeringType, AUTOMATIC, AUTOMATIC)
    MultiEvTable = Dem_GetMultiEventTriggering(RootId);

  DBG_DEM_FINDNEXTDEPENDENTEVENT_ENTRY(RootId, LastRetVal, LastEventId);

  /* ensured by caller function that MultiEvTable != NULL_PTR */
  if (*LastEventId == DEM_EVENT_ID_INVALID)
  {
    /* start processing of the multi-trigger event list */
    NextEventId = Dem_MultiEventTriggeringSlaveEventId[MultiEvTable->SlaveStartIdx];
  }
  else
  {
    if ( ( (MultiEvTable->AlternativeBehavior ==
            DEM_MULTIEVENTTRIGGERING_ALT_EXCLUSIVE_REPLACE) &&
           (LastRetVal == E_OK)
          ) ||
          (*LastEventId == RootId)
       )
    {
      /* AlternativeBehavior is DEM_MULTIEVENTTRIGGERING_ALT_EXCLUSIVE_REPLACE
       * this leads to a slave or Root being processed then the processing will end
       */
      /* !LINKSTO Dem.MultiEventTriggering.AlternativeBehavior.ExclusiveReplace.StopProcessing,1 */
      /* !LINKSTO Dem.MultiEventTriggering.AlternativeBehavior.ExclusiveReplace.ReplaceProcessing,1 */
    }
    else
    {
      Dem_EventIdType SlaveEventId;
      Dem_MultiEventTriggeringSlaveIdxType SlaveIdx = MultiEvTable->SlaveStartIdx;

      /* find the NextEventId which follows the LastEventId */
      do
      {
        SlaveEventId = Dem_MultiEventTriggeringSlaveEventId[SlaveIdx];
        SlaveIdx++;
      }
      while ( (*LastEventId != SlaveEventId) &&
              (SlaveIdx < MultiEvTable->SlaveNextIdx) );

      if (SlaveIdx < MultiEvTable->SlaveNextIdx)
      {
        NextEventId = Dem_MultiEventTriggeringSlaveEventId[SlaveIdx];
      }
      else
      {
        /* AlternativeBehavior:
         * - DEM_MULTIEVENTTRIGGERING_ALT_NONE then all slaves are processed
         * - DEM_MULTIEVENTTRIGGERING_ALT_EXCLUSIVE_REPLACE then only process the root
         */
        /* !LINKSTO Dem.MultiEventTriggering.AlternativeBehavior.ExclusiveReplace.MasterProcessing,1 */
        NextEventId = RootId;
      }
      /* else the last slave was processed -> end further processing
         NextEventId will remain DEM_EVENT_ID_INVALID */
    }
  }

  /* a new event will be processed
   * set it as last for the next call
   */
  if (NextEventId != DEM_EVENT_ID_INVALID)
  {
    *LastEventId = NextEventId;
  }

  DBG_DEM_FINDNEXTDEPENDENTEVENT_EXIT(NextEventId, RootId, LastRetVal, LastEventId);

  return NextEventId;
}

#endif

#if (DEM_CALIBRATION_SUPPORT == STD_ON)
#if (DEM_NUM_INDICATOR_LINKS > 0U)
FUNC(Dem_IndicatorGrpIdxType, DEM_CODE)
  Dem_GbiIndicatorClassIndex(Dem_EventIdType EventId)
{
#if (DEM_CALIBRATION_WITHOUTEVCOMB_SUPPORT == STD_ON)
  const Dem_IndicatorGrpIdxType Result =
    Dem_EventClassDesc[DEM_GBI_EVENTCLASSDESCIDX(EventId)].IndicatorClassIdx;
#else /* (DEM_CALIBRATION_WITHOUTEVCOMB_SUPPORT == STD_OFF) */
  const Dem_IndicatorGrpIdxType Result = Dem_EventIndicatorClassIdx[EventId];
#endif

  DBG_DEM_GBIINDICATORCLASSINDEX_ENTRY(EventId);

  DBG_DEM_GBIINDICATORCLASSINDEX_EXIT(Result, EventId);
  return Result;
}
#endif /* (DEM_NUM_INDICATOR_LINKS > 0U) */
#else /* (DEM_CALIBRATION_SUPPORT == STD_OFF) */
#if (DEM_NUM_INDICATOR_LINKS > 0U)
FUNC(boolean, DEM_CODE) Dem_GbiIndicatorUsed(Dem_EventIdType EventId)
{
  const boolean Result =
    (boolean)DEM_BIT_FIELD_VALUE_32(
      DEM_DESC_CONF4(EventId),
      DEM_INDICATORUSED_OFFSET,
      DEM_INDICATORUSED_MASK);

  DBG_DEM_GBIINDICATORUSED_ENTRY(EventId);

  DBG_DEM_GBIINDICATORUSED_EXIT(Result, EventId);
  return Result;
}
#endif /* (DEM_NUM_INDICATOR_LINKS > 0U) */
#endif /* (DEM_CALIBRATION_SUPPORT == STD_ON) */

#if ((DEM_USE_EVENT_DISPLACEMENT == STD_ON) || (DEM_NUM_OF_PIDS_IN_OBDFF > 0U))
FUNC(Dem_PriorityType, DEM_CODE) Dem_GbiPriority(Dem_EventIdType EventId)
{
#if (DEM_CALIBRATION_WITHOUTEVCOMB_SUPPORT == STD_ON)
  const Dem_PriorityType Result =
    Dem_EventClassDesc[DEM_GBI_EVENTCLASSDESCIDX(EventId)].EventPriority;
#else
  const Dem_PriorityType Result =
    (Dem_PriorityType)DEM_BIT_FIELD_VALUE_32(
      DEM_DESC_CONF3(EventId),
      DEM_PRIORITY_OFFSET,
      DEM_PRIORITY_MASK);
#endif

  DBG_DEM_GBIPRIORITY_ENTRY(EventId);

  DBG_DEM_GBIPRIORITY_EXIT(Result, EventId);
  return Result;
}
#endif /* (DEM_USE_EVENT_DISPLACEMENT == STD_ON) || (DEM_NUM_OF_PIDS_IN_OBDFF > 0U) */

FUNC(Dem_DebounceType, DEM_CODE) Dem_GbiDebounceAlgo(Dem_EventIdType EventId)
{
  const Dem_DebounceType Result =
    (Dem_DebounceType)DEM_BIT_FIELD_VALUE_32(
      DEM_DESC_CONF6(EventId),
      DEM_DEBOUNCEALGO_OFFSET,
      DEM_DEBOUNCEALGO_MASK);

  DBG_DEM_GBIDEBOUNCEALGO_ENTRY(EventId);

  DBG_DEM_GBIDEBOUNCEALGO_EXIT(Result, EventId);
  return Result;
}

#if (DEM_NUM_DEBOUNCE_COUNTER > 0U)
FUNC(Dem_DebounceCounterClassIdxType, DEM_CODE) Dem_GbiDebounceCounterClassIdx(
  Dem_EventIdType Index)
{
  const Dem_DebounceCounterClassIdxType Result =
    (Dem_DebounceCounterClassIdx[Index] &
      (Dem_DebounceCounterClassIdxType) ~DEM_DEBOUNCE_COUNTER_NVSTORAGE_MASK);

  DBG_DEM_GBIDEBOUNCECOUNTERCLASSIDX_ENTRY(Index);

  DBG_DEM_GBIDEBOUNCECOUNTERCLASSIDX_EXIT(Result, Index);
  return Result;
}
#endif /* DEM_NUM_DEBOUNCE_COUNTER > 0U */

#if ((DEM_NUM_DEBOUNCE_COUNTER > 0U) || (DEM_NUM_DEBOUNCE_COUNTER_PERM > 0U))
FUNC(Dem_EventIdType, DEM_CODE) Dem_GbiDebounceStatusIdx(
  Dem_EventIdType EventId)
{

  const Dem_EventIdType Result =
    (Dem_EventIdType)DEM_BIT_FIELD_VALUE_32(
      DEM_DESC_CONF6(EventId),
      DEM_DEBOUNCEIDX_OFFSET,
      DEM_DEBOUNCEIDX_MASK);

  DBG_DEM_GBIDEBOUNCESTATUSIDX_ENTRY(EventId);

  DBG_DEM_GBIDEBOUNCESTATUSIDX_EXIT(Result, EventId);
  return Result;
}
#endif /* (DEM_NUM_DEBOUNCE_COUNTER > 0U) || (DEM_NUM_DEBOUNCE_COUNTER_PERM > 0U) */

#if ((DEM_NUM_DEBOUNCE_TIME > 0U) || (DEM_NUM_DEBOUNCE_FREQUENCY > 0U))
FUNC(Dem_EventIdType, DEM_CODE) Dem_GbiDebounceIdx(Dem_EventIdType EventId)
{
  const Dem_EventIdType Result =
    (Dem_EventIdType)DEM_BIT_FIELD_VALUE_32(
      DEM_DESC_CONF6(EventId),
      DEM_DEBOUNCEIDX_OFFSET,
      DEM_DEBOUNCEIDX_MASK);

  DBG_DEM_GBIDEBOUNCEIDX_ENTRY(EventId);

  DBG_DEM_GBIDEBOUNCEIDX_EXIT(Result, EventId);
  return Result;
}
#endif /* (DEM_NUM_DEBOUNCE_TIME > 0U) || (DEM_NUM_DEBOUNCE_FREQUENCY > 0U) */

#if (DEM_NUM_DEBOUNCE_TIME > 0U)
FUNC(Dem_DebounceTimeClassIdxType, DEM_CODE) Dem_GbiDebounceTimeClassIdx(
  Dem_EventIdType Index)
{
  const Dem_DebounceTimeClassIdxType Result =
    Dem_DebounceTimeClassIdx[Index] ;

  DBG_DEM_GBIDEBOUNCETIMECLASSIDX_ENTRY(Index);

  DBG_DEM_GBIDEBOUNCETIMECLASSIDX_EXIT(Result, Index);
  return Result;
}
#endif

FUNC(Dem_EventKindType, DEM_CODE) Dem_GbiEventKind(Dem_EventIdType EventId)
{
  const Dem_EventKindType Result =
    (Dem_EventKindType)DEM_BIT_FIELD_VALUE_32(
      DEM_DESC_CONF4(EventId),
      DEM_EVENTKIND_OFFSET,
      DEM_EVENTKIND_MASK);

  DBG_DEM_GBIEVENTKIND_ENTRY(EventId);

  DBG_DEM_GBIEVENTKIND_EXIT(Result, EventId);
  return Result;
}

#if (DEM_OBD_Support == STD_ON)
FUNC(boolean, DEM_CODE) Dem_GbiMinRatioEvent(Dem_EventIdType EventId)
{
  /* !LINKSTO dsn.Dem.OBD.config.MinRatioEvent.0003,3 */
#if (DEM_CALIBRATION_WITHOUTEVCOMB_SUPPORT == STD_ON)
  const boolean Result = (DEM_BIT_FIELD_VALUE_8(
    Dem_EventClassDesc[DEM_GBI_EVENTCLASSDESCIDX(EventId)].Bitfield,
    DEM_MINRATIOEVENTCLASS_OFFSET,
    DEM_MINRATIOEVENTCLASS_MASK) != 0U) ? TRUE : FALSE;
#else
  const boolean Result =
    DEM_IS_BIT_SET_IN_ARRAY(Dem_MinRatioEvent, DEM_GET_MASTER_EVID(EventId));
#endif

  DBG_DEM_GBIMINRATIOEVENT_ENTRY(EventId);

  DBG_DEM_GBIMINRATIOEVENT_EXIT(Result, EventId);

  return Result;
}
#endif /* (DEM_OBD_Support == STD_ON) */

#if (DEM_DTC_WWHOBD_CLASS_SUPPORT)
FUNC(Dem_DTCSeverityType, DEM_CODE) Dem_GbiDTCClass(Dem_EventIdType EventId)
{
  Dem_DTCSeverityType Result = DEM_SEVERITY_NO_SEVERITY;

  DBG_DEM_GBIDTCCLASS_ENTRY(EventId);

#if (DEM_OBD_VARIANT_SELECTABLE == STD_ON)
  if (DEM_GET_OBD_VARIANT() != DEM_OBD_VARIANT_OBDONUDS)
  {
    TS_PARAM_UNUSED(EventId);
  }
  else
#endif
  {
    /* the DTC Class is fetched only for emission relevant events */
    if (Dem_GbiDTCKind(EventId) == DEM_DTC_KIND_EMISSION_REL_DTCS)
    {
      uint8 DTCClass;
#if (DEM_OBD_DTCVALUE3BYTE_SUPPORT == STD_ON)
      DTCClass = DEM_BIT_FIELD_VALUE_32(
        Dem_OBDConfig[DEM_DESC_OBD_IDX(EventId)],
        DEM_DTCCLASS_OFFSET,
        DEM_WWHOBD_DTCCLASS_MASK);
#else
      DTCClass = DEM_BIT_FIELD_VALUE_8(
        Dem_OBDConfig[DEM_DESC_OBD_IDX(EventId)],
        DEM_DTCCLASS_OFFSET,
        DEM_WWHOBD_DTCCLASS_MASK);
#endif

      /* the bit-packed value represented on 3 bits is translated to the
       * mask values representing the defined severity DTC class range */
      Result =
        (Dem_DTCSeverityType)(
          (DTCClass == 1U) ? DEM_SEVERITY_WWHOBD_CLASS_NO_CLASS :
            ( (DTCClass == 2U) ? DEM_SEVERITY_WWHOBD_CLASS_A :
              ( (DTCClass == 3U) ? DEM_SEVERITY_WWHOBD_CLASS_B1 :
                ( (DTCClass == 4U) ? DEM_SEVERITY_WWHOBD_CLASS_B2 :
                    DEM_SEVERITY_WWHOBD_CLASS_C) ) ) );
    }
  }

  DBG_DEM_GBIDTCCLASS_EXIT(Result, EventId);

  return Result;
}
#endif /* (DEM_DTC_WWHOBD_CLASS_SUPPORT) */

#if ( (DEM_FREEZE_FRAME_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) && \
      (DEM_CALIBRATION_WITHOUTEVCOMB_SUPPORT == STD_ON) )
FUNC(boolean, DEM_CODE) Dem_GbiFreezeFrameUpdate(Dem_EventIdType EventId)
{
  /* !LINKSTO Dem.EB.EventClass.FreezeFrameUpdate,1 */
  const boolean Result = (DEM_BIT_FIELD_VALUE_8(
    Dem_EventClassDesc[DEM_GBI_EVENTCLASSDESCIDX(EventId)].Bitfield,
    DEM_FFUPDATEEVENTCLASS_OFFSET,
    DEM_FFUPDATEEVENTCLASS_MASK) != 0U) ? TRUE : FALSE;

  DBG_DEM_GBIFREEZEFRAMEUPDTATE_ENTRY(EventId);

  DBG_DEM_GBIFREEZEFRAMEUPDTATE_EXIT(Result, EventId);
  return Result;
}
#endif

#if (DEM_OBD_Support == STD_ON)
#if (DEM_READINESS_CALIBRATION_SUPPORT == STD_OFF)
FUNC(Dem_EventOBDReadinessGroupType, DEM_CODE) Dem_GbiOBDReadinessGroup(
  Dem_EventIdType EventId)
{
#if (DEM_OBD_DTCVALUE3BYTE_SUPPORT == STD_ON)
  const Dem_EventOBDReadinessGroupType ReadinessGroup =
    (Dem_EventOBDReadinessGroupType)
      DEM_BIT_FIELD_VALUE_32(Dem_OBDConfig[DEM_DESC_OBD_IDX(EventId)],
                             DEM_OBD_READINESS_OFFSET,
                             DEM_OBD_READINESS_MASK);
#else
  const Dem_EventOBDReadinessGroupType ReadinessGroup =
    (Dem_EventOBDReadinessGroupType)
      DEM_BIT_FIELD_VALUE_8(Dem_OBDConfig[DEM_DESC_OBD_IDX(EventId)],
                            DEM_OBD_READINESS_OFFSET,
                            DEM_OBD_READINESS_MASK);

#endif
  DBG_DEM_GBIOBDREADINESSGROUP_ENTRY(EventId);

  DBG_DEM_GBIOBDREADINESSGROUP_EXIT(ReadinessGroup, EventId);
  return ReadinessGroup;
}
#endif /* (DEM_READINESS_CALIBRATION_SUPPORT == STD_OFF) */

#if (DEM_VCC_OCC5_USED == STD_ON)
FUNC(Dem_AgingCyclesType, DEM_CODE) Dem_GbiOBDAgingCycleCounterThreshold(
  Dem_EventIdType EventId)
{
#if (DEM_CALIBRATION_WITHOUTEVCOMB_SUPPORT == STD_ON)
  const Dem_AgingCyclesType Result =
    Dem_EventClassDesc[DEM_GBI_EVENTCLASSDESCIDX(EventId)].OBDAgingCycleCounterThreshold;
#else
  const Dem_AgingCyclesType Result = Dem_OBDAgingCycleThreshold[DEM_DESC_OBD_IDX(EventId)];
#endif
  DBG_DEM_GBIOBDAGINGCYCLECOUNTERTHRESHOLD_ENTRY(EventId);

  DBG_DEM_GBIOBDAGINGCYCLECOUNTERTHRESHOLD_EXIT(Result, EventId);
  return Result;
}
#endif /* DEM_VCC_OCC5_USED == STD_ON */
#endif /* DEM_OBD_Support == STD_ON */

#if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
FUNC(Dem_EventIdType, DEM_CODE) Dem_GetPFFIndex(Dem_EventIdType EventId)
{
  Dem_EventIdType Result = 0U;

  Dem_EventIdType EvId;

  DBG_DEM_GETPFFINDEX_ENTRY(EventId);

  /* check if there are PFFs in front of the target PFF */
  for (EvId = 0U; EvId < EventId; ++EvId)
  {
    if (Dem_GbiEnablePrestorage(EvId) == TRUE)
    {
      ++Result;
    }
  }

  DBG_DEM_GETPFFINDEX_EXIT(Result, EventId);
  return Result;
}
#endif /* DEM_MAX_NUMBER_PRESTORED_FF > 0U */

#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
FUNC(boolean, DEM_CODE) Dem_GbiEvAvailable(Dem_EventIdType EventId)
{
  boolean Result;

  DBG_DEM_GBIEVAVAILABLE_ENTRY(EventId);

  if (DEM_IS_BIT_SET_IN_ARRAY(DEM_EVENT_AVAILABILITY_BIT_ARRAY, EventId))
  {
    /* event is available */
    Result = TRUE;
  }
  else
  {
    /* event is not available */
    Result = FALSE;
  }

  DBG_DEM_GBIEVAVAILABLE_EXIT(Result, EventId);
  return Result;
}
#endif /* DEM_EVENT_DISABLING_SUPPORT == STD_ON */

#if ((DEM_NUM_CMB_DTCS > 0U) && (DEM_EVENT_DISABLING_SUPPORT == STD_ON))
FUNC(boolean, DEM_CODE) Dem_IsAnyEvAvailable(Dem_EventIdType EventId)
{
  boolean Result = FALSE;
  const Dem_DTCConfIdxType DTCConfIdx = DEM_GBI_DTCCONFIDX(EventId);
  DBG_DEM_ISANYEVAVAILABLE_ENTRY(EventId);

  if (DEM_IS_DTC_COMBINED(DTCConfIdx))
  {
    /* search for first available event of the event combination */
    const Dem_CmbDTCEvLnkType firstCmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx];
    const Dem_CmbDTCEvLnkType LastCmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx + 1U] - 1U;
    Dem_CmbDTCEvLnkType CmbEvIdx;

    for (CmbEvIdx = firstCmbEvIdx; CmbEvIdx <= LastCmbEvIdx; CmbEvIdx++)
    {
      /* get the event available status of the selected combined event */
      Result = Dem_GbiEvAvailable(Dem_CmbDTCEvents[CmbEvIdx]);
      if (Result == TRUE)
      {
        /* found an available combined event; stop the search */
        break;
      }
    }
  }
  else
  {
    /* event is not combined */
    Result = Dem_GbiEvAvailable(EventId);
  }

  DBG_DEM_ISANYEVAVAILABLE_EXIT(Result, EventId);
  return Result;
}
#endif /* (DEM_NUM_CMB_DTCS > 0U) */

FUNC(boolean, DEM_CODE) Dem_SearchForEntry(
  Dem_EventIdType                                          EventId,
  P2VAR(Dem_EventMemoryEntryPtrType, AUTOMATIC, AUTOMATIC) FoundEntry,
  P2VAR(Dem_SizeEvMemEntryType, AUTOMATIC, AUTOMATIC)      FoundEntryIdx)
{
  boolean Result = FALSE;

  DBG_DEM_SEARCHFORENTRY_ENTRY(EventId, FoundEntry, FoundEntryIdx);

  /* check whether an event memory entry exists for the given EventId */
  if (DEM_IS_BIT_SET_IN_ARRAY(Dem_EvMemEntryExists, EventId))
  {
    const uint8 OriginIdx = Dem_GbiDTCOriginIdx(EventId);
    const Dem_SizeEvMemEntryType SizeEventMem = Dem_SizeEventMem[OriginIdx];
    const Dem_EventIdType MasterEventId = DEM_GET_MASTER_EVID(EventId);
    const Dem_EventMemoryEntryPtrType Entry = Dem_EventMem[OriginIdx];
    Dem_SizeEvMemEntryType Index;

    /* search for entry with given event Id  */
    for (Index = 0U; Index < SizeEventMem; Index++)
    {
      const Dem_EventIdType CurrentEventId = DEM_GET_MASTER_EVID(Entry[Index].EventId);

      if ((Entry[Index].EventId != DEM_EVENT_ID_INVALID) && (MasterEventId == CurrentEventId))
      {
        /* entry found */
        if (NULL_PTR != FoundEntry)
        {
          *FoundEntry = &Entry[Index];
        }
        if (NULL_PTR != FoundEntryIdx)
        {
          *FoundEntryIdx = Index;
        }
        Result = TRUE;

        break;
      }
    }
  }

  DBG_DEM_SEARCHFORENTRY_EXIT(Result, EventId, FoundEntry, FoundEntryIdx);
  return Result;
}

FUNC(void, DEM_CODE) Dem_SetEvEntryExists(
  Dem_EventIdType EventId,
  boolean         EvEntryExitsStatus)
{
#if (DEM_NUM_CMB_DTCS > 0U)
  const Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
#endif
  DBG_DEM_SETEVENTRYEXISTS_ENTRY(EventId, EvEntryExitsStatus);

#if (DEM_NUM_CMB_DTCS > 0U)
  if (DEM_IS_DTC_COMBINED(DTCConfIdx))
  {
    /* set EntryExists status of all combined events */
    const Dem_CmbDTCEvLnkType LastCmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx + 1U] - 1U;
    Dem_CmbDTCEvLnkType CmbEvIdx;
    Dem_EventIdType CmbEventId;

    for (CmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx]; CmbEvIdx <= LastCmbEvIdx; CmbEvIdx++)
    {
      CmbEventId = Dem_CmbDTCEvents[CmbEvIdx];
      DEM_MODIFY_BIT_IN_ARRAY(Dem_EvMemEntryExists, CmbEventId, EvEntryExitsStatus);
    }
  }
  else
#endif /* DEM_NUM_CMB_DTCS > 0U */
  {
    DEM_MODIFY_BIT_IN_ARRAY(Dem_EvMemEntryExists, EventId, EvEntryExitsStatus);
  }

  DBG_DEM_SETEVENTRYEXISTS_EXIT(EventId, EvEntryExitsStatus);
}

FUNC(void, DEM_CODE) Dem_InitEvEntryExists(void)
{
#if ( (DEM_USE_PERMANENT_STORAGE == STD_ON) && \
      (DEM_USE_IMMEDIATE_NV_STORAGE == STD_OFF) )
  Dem_SizeEvMemEntryType EntryIdx;
  uint8                  OriginIdx;
#endif
  uint16                 EvEntryExitsIdx;

  DBG_DEM_INITEVENTRYEXISTS_ENTRY();

  /* Deviation TASKING-1 */
  for (EvEntryExitsIdx = 0U;
       EvEntryExitsIdx < DEM_EVTENTRY_EXISTS_ARRAY_SIZE;
       EvEntryExitsIdx++)
  {
    Dem_EvMemEntryExists[EvEntryExitsIdx] = 0U;
  }

  /* in case of non-volatile storage (DEM_USE_PERMANENT_STORAGE), the
   * EvEntryExists status has to be initialized in accordance with the
   * exiting event memory entries.
   * In case of immediated storage, this initialization takes place
   * while restoring the data in 'Dem_RestoreImmediateData()'. */
#if ( (DEM_USE_PERMANENT_STORAGE == STD_ON) && \
      (DEM_USE_IMMEDIATE_NV_STORAGE == STD_OFF) )
  for (OriginIdx = 0U; OriginIdx < DEM_MAXNUM_ORIGINS; OriginIdx++)
  {
    const Dem_EventMemoryEntryPtrType EvMemEntry = Dem_EventMem[OriginIdx];
    for (EntryIdx = 0U; EntryIdx < Dem_SizeEventMem[OriginIdx]; EntryIdx++)
    {
      const Dem_EventIdType EventId = EvMemEntry[EntryIdx].EventId;
      if (EventId != DEM_EVENT_ID_INVALID)
      {
        Dem_SetEvEntryExists(EventId, TRUE);
      }
    }
  }
#endif /* (DEM_USE_PERMANENT_STORAGE == STD_ON) && \
          (DEM_USE_IMMEDIATE_NV_STORAGE == STD_OFF) ) */

  DBG_DEM_INITEVENTRYEXISTS_EXIT();
}

#if (DEM_NUM_FFSEGS > 0U)
FUNC_P2VAR(Dem_EntryDataType, DEM_VAR_CLEARED, DEM_CODE) Dem_FFEntryData(
  Dem_EventMemoryEntryPtrConstType               EvMemEntry,
  P2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFClass,
  Dem_FFIdxType                                  FFIndex)
{
  const Dem_EventIdType EventId = EvMemEntry->EventId;

#if (DEM_NUM_EDSEGS > 0U)
#if (DEM_NUM_EXT_DATAELEMENTS > 0U)
  /* get extended data class layout */
  CONSTP2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass =
    &Dem_EDClass[Dem_GbiEDClassIdx(EventId)];
#endif
#endif

  Dem_SizeEntryDataType StartPos;
  const uint8 OriginIdx = Dem_GbiDTCOriginIdx(EventId);
  Dem_EntryDataPtrType Result;

  DBG_DEM_FFENTRYDATA_ENTRY(EvMemEntry, FFClass, FFIndex);

  /* calculate start position of the needed FF */
   StartPos = EvMemEntry->EntryDataPos;
#if (DEM_USE_INT_VAL_AREA == STD_ON)
  StartPos = StartPos + Dem_SizeOfIntValArea(EventId);
#endif
#if (DEM_NUM_EDSEGS > 0U)
  StartPos = StartPos + Dem_SizeOfED(EDClass);
#endif
  StartPos = StartPos + ((Dem_SizeEntryDataType)Dem_SizeOfFF(DEM_REGULAR_FF, FFClass) *
    FFIndex);
  Result = &Dem_EntryData[OriginIdx][StartPos];

  DBG_DEM_FFENTRYDATA_EXIT(Result, EvMemEntry, FFClass, FFIndex);
  return Result;
}

FUNC(boolean, DEM_CODE) Dem_CheckFFRecNumValid(
  Dem_EventIdType EventId,
  uint8           RecordNumber)
{
  boolean Result = FALSE;

#if (DEM_FREEZE_FRAME_REC_NUMERATION_TYPE == DEM_FF_RECNUM_CONFIGURED)
  uint8 FFRecNumIdx;
  const Dem_FFRecNumClassIdxType FFRecNumClassIdx =
    Dem_GbiFFRecNumClassIdx(EventId);
  const Dem_FFIdxType NumFF =
    Dem_FFRecNumerationClass[FFRecNumClassIdx].NumFFRecs;
  CONSTP2CONST(Dem_FFIdxType, AUTOMATIC, DEM_CONST) FFRecNumClass =
    Dem_FFRecNumerationClass[FFRecNumClassIdx].Dem_FFRecNumClassIdx;
#endif /* (DEM_FREEZE_FRAME_REC_NUMERATION_TYPE == DEM_FF_RECNUM_CONFIGURED) */

  DBG_DEM_CHECKFFRECNUMVALID_ENTRY(EventId, RecordNumber);

#if (DEM_FREEZE_FRAME_REC_NUMERATION_TYPE == DEM_FF_RECNUM_CONFIGURED)
  for (FFRecNumIdx = 0U; FFRecNumIdx < NumFF; FFRecNumIdx++)
  {
    /* check whether the requested record number is valid for the record
     * number class */
    if (RecordNumber == FFRecNumClass[FFRecNumIdx])
    {
      Result = TRUE;
      break;
    }
  }
#else
  /* in range 0x01..MaxFFNum, OBD FF 0x00 is not supported */
  if ( (RecordNumber <= Dem_GbiMaxNumFFRecs(EventId)) &&
       (RecordNumber != 0x00U) )
  {
    Result = TRUE;
  }
#endif /* DEM_FREEZE_FRAME_REC_NUMERATION_TYPE == DEM_FF_RECNUM_CONFIGURED */

  DBG_DEM_CHECKFFRECNUMVALID_EXIT(Result, EventId, RecordNumber);
  return Result;
}

FUNC(uint8, DEM_CODE) Dem_CheckFFRecNumStored(
  Dem_EventMemoryEntryPtrConstType EvMemEntry,
  uint8                            RecordNumber)
{
  uint8 FFRecNumIdx = 0U;

#if (DEM_FREEZE_FRAME_REC_NUMERATION_TYPE == DEM_FF_RECNUM_CONFIGURED)
  const Dem_FFRecNumClassIdxType FFRecNumClassIdx =
    Dem_GbiFFRecNumClassIdx(EvMemEntry->EventId);
  const Dem_FFIdxType NumFF =
    DEM_NUMFF(EvMemEntry,
              Dem_FFRecNumerationClass[FFRecNumClassIdx].NumFFRecs);
  CONSTP2CONST(Dem_FFIdxType, AUTOMATIC, DEM_CONST) FFRecNumClass =
    Dem_FFRecNumerationClass[FFRecNumClassIdx].Dem_FFRecNumClassIdx;
#endif /* (DEM_FREEZE_FRAME_REC_NUMERATION_TYPE == DEM_FF_RECNUM_CONFIGURED) */

  DBG_DEM_CHECKFFRECNUMSTORED_ENTRY(EvMemEntry, RecordNumber);

#if (DEM_FREEZE_FRAME_REC_NUMERATION_TYPE == DEM_FF_RECNUM_CONFIGURED)
  /* loop over the record numbers until the requested RecordNumber is found */
  while ( (FFRecNumIdx < NumFF) &&
          (RecordNumber != FFRecNumClass[FFRecNumIdx]) )
  {
    FFRecNumIdx++;
  }
#else
  TS_PARAM_UNUSED(EvMemEntry);

  FFRecNumIdx = RecordNumber - 1U;
#endif /* DEM_FREEZE_FRAME_REC_NUMERATION_TYPE == DEM_FF_RECNUM_CONFIGURED */

  DBG_DEM_CHECKFFRECNUMSTORED_EXIT(FFRecNumIdx, EvMemEntry, RecordNumber);
  return FFRecNumIdx;
}
#endif /* (DEM_NUM_FFSEGS > 0U) */

#if (DEM_NUM_EDSEGS > 0U)
FUNC_P2VAR(Dem_EntryDataType, DEM_VAR_CLEARED, DEM_CODE)
  Dem_EDEntryData(Dem_EventMemoryEntryPtrConstType EvMemEntry)
{
  /* calculate start position of the needed ED */
  Dem_EntryDataPtrType EDEntryData = Dem_IntValEntryData(EvMemEntry);

  DBG_DEM_EDENTRYDATA_ENTRY(EvMemEntry);

#if (DEM_USE_INT_VAL_AREA == STD_ON)
  /* if entry data starts with internal value area (e.g. for aging counter),
   * ED entry exists from the next byte only */
  EDEntryData = &EDEntryData[Dem_SizeOfIntValArea(EvMemEntry->EventId)];
#endif

  DBG_DEM_EDENTRYDATA_EXIT(EDEntryData, EvMemEntry);
  return EDEntryData;
}
#endif /* (DEM_NUM_EDSEGS > 0U) */

FUNC_P2VAR(Dem_EntryDataType, DEM_VAR_CLEARED, DEM_CODE)
  Dem_IntValEntryData(Dem_EventMemoryEntryPtrConstType EvMemEntry)
{
  Dem_EntryDataPtrType Result;

  DBG_DEM_INTVALENTRYDATA_ENTRY(EvMemEntry);
  /* the calling algorithms of Dem_IntValEntryData() function ensures that argument
   * EvMemEntry is not a NULL pointer */
  DEM_PRECONDITION_ASSERT(EvMemEntry != NULL_PTR, DEM_INTERNAL_API_ID);
  {
    /* calculate start position of the IntVal entry data */
    const Dem_SizeEntryDataType StartPos = EvMemEntry->EntryDataPos;
    const uint8 OriginIdx = Dem_GbiDTCOriginIdx(EvMemEntry->EventId);

    Result = &Dem_EntryData[OriginIdx][StartPos];
  }
  DBG_DEM_INTVALENTRYDATA_EXIT(Result, EvMemEntry);
  return Result;
}

#if (DEM_NUM_EDSEGS > 0U)
FUNC(Dem_EDSegIdxType, DEM_CODE) Dem_FindEDNumIndex(
  P2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass,
  uint8                                          Number)
{
  Dem_EDSegIdxType SegIndex;

  DBG_DEM_FINDEDNUMINDEX_ENTRY(EDClass, Number);

  for (SegIndex = 0U; SegIndex < EDClass->NumEDSegs; ++SegIndex)
  {
    if (Dem_EDSegment[EDClass->EDSegIdx[SegIndex]].RecNum == Number)
    {
      break;
    }
  }

  DBG_DEM_FINDEDNUMINDEX_EXIT(SegIndex, EDClass, Number);
  return SegIndex;
}
#endif /* (DEM_NUM_EDSEGS > 0U) */

FUNC(Std_ReturnType, DEM_CODE) Dem_CheckProcessingConditions(
  Dem_EventIdType   EventId)
{
  Std_ReturnType Result = E_OK;
  Dem_OperationCycleStateType OperationCycleState;
  Dem_OperationCycleIdType OperationCycleId;

  DBG_DEM_CHECKPROCESSINCCONDITIONS_ENTRY(EventId);

  OperationCycleId = Dem_GbiOpCycleIdx(EventId);
  OperationCycleState = DEM_OPCYCLESTATE[OperationCycleId];

  if ( (Dem_InitializationState == DEM_INITIALIZED) ||
       (Dem_InitializationState == DEM_POSTINITIALIZED)
     )
  {
    /* !LINKSTO Dem.ASR431.ControlDTCSetting.DTCStatus,2 */
    /* getter function is used in place in order to optimize runtime access */
    if ((OperationCycleState == DEM_CYCLE_STATE_END) ||
        (DEM_DTC_SETTING_ALLOWED(EventId) == FALSE))
    {
      /* the operation cycle of the event is not started: or */
      /* DTC setting of the group is not enabled: */
      /* no debounce-/qualification-handling allowed (as per Dem.ASR40.SWS_Dem_00626) */
      Result = E_NOT_OK;
    }
  }
#if (DEM_NUM_ENCONDGRP_SINGLEREF > 0U)
  /* !LINKSTO Dem.SWS_Dem_00447,1, Dem.SWS_Dem_00449,1, Dem.SWS_Dem_00450,1 */
  /* feature related code-part concerning enable conditions */
   if (Dem_EnCondGrpStatusCounter[Dem_GbiEnCondGrpIdx(EventId)] > 0U)
  {
    /* at least one enable condition referred by this event is not fulfilled */
    Result = E_NOT_OK;
  }
#endif

  DBG_DEM_CHECKPROCESSINCCONDITIONS_EXIT(Result, EventId);
  return Result;
}

FUNC(Std_ReturnType, DEM_CODE) Dem_InternalSetEventStatus(
  Dem_EventInfoType   EventInfo,
  Dem_EventStatusType EventStatus)
{
  Std_ReturnType Result = E_NOT_OK;
  const Dem_EventIdType EventId = EventInfo.EventId;
#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U)
  const Dem_EventIdType RootId = EventInfo.RootId;
#endif

  DBG_DEM_INTERNALSETEVENTSTATUS_ENTRY(EventInfo, EventStatus);

  if (Dem_CheckProcessingConditions(EventId) == E_OK)
  {
    Result = Dem_DebounceEvent(EventId, &EventStatus);
    /* no check for 'Result' is needed since 'EventStatus'
     * equals 'DEM_EVENT_STATUS_UNQUALIFIED' in error case */
    if (EventStatus != DEM_EVENT_STATUS_UNQUALIFIED)
    {
#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
      Dem_ProcessUnconfirmedThreshold(EventId, EventStatus);

      if (EventStatus != DEM_EVENT_STATUS_UNCONFIRMED)
#endif
      {
#if (DEM_MAX_NUMBER_PRESTORED_FF > 0U)
        /* release prestored freeze frame for passed events */
        if (EventStatus == DEM_EVENT_STATUS_PASSED)
        {
          if (Dem_GbiEnablePrestorage(EventId) == TRUE)
          {
            Dem_EventIdType PFFIndex = Dem_GetPFFIndex(EventId);
            /*
             * ENTER critical section
             */
            DEM_ENTER_EXCLUSIVE_AREA();

            /* mark prestored freeze frame as unused */
            DEM_CLR_BIT_IN_ARRAY(Dem_PFFEntryValid, PFFIndex);

            /*
             * LEAVE critical section
             */
            DEM_EXIT_EXCLUSIVE_AREA();
          }
        }
#endif

        /* --- event qualification-handling --- */

        /* update failure counter on first fail report of the event in the
         * operation cycle */
        if (Dem_UpdateFailureCounterFirstFail(EventId, EventStatus) == TRUE)
        {
#if ( (DEM_NUM_FAILURECYCLES > 0U) && \
      (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_ON) )
          Dem_DoProcessFaultConfirmation = TRUE;
#endif

#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF)
          /* !LINKSTO Dem.OperationCycleQualification.SkipConfirmation,2 */
          /* operation cycle must be qualified before setting the CDTC bit */
#if (DEM_OPCYC_OBD_DCY_USED == STD_ON)
          if (DEM_IS_CYCLE_QUALIFIED(EventId) == TRUE)
#endif
          {
            /* promote trigger for fault confirmation / CDTC processing */
            EventStatus = DEM_EVENT_STATUS_CONFIRMED;
          }
#endif /* DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF */
        }

        /* !LINKSTO Dem.MultiEventTriggering.ReportErrorStatus,1 */
        /* !LINKSTO Dem.MultiEventTriggering.SetEventStatus,1 */
#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U)
        if (Dem_GbiEventKind(RootId) == DEM_EVENT_KIND_SWC)
#else
        if (Dem_GbiEventKind(EventId) == DEM_EVENT_KIND_SWC)
#endif
        {
          Dem_InternalSetSwcEventStatus(EventInfo, EventStatus, &Result);
        }
        else /* DEM_EVENT_KIND_BSW */
        {
          Dem_InternalSetBswEventStatus(EventInfo, EventStatus, &Result);
        }

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON) && \
    ( (DEM_NUM_FAILURECYCLES > 0U) || \
      ((DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF) && \
       (DEM_OPCYC_OBD_DCY_USED == STD_ON)) || \
      ((DEM_NUM_INDICATOR_LINKS > 0U) && \
       (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD))|| \
      (DEM_FREEZE_FRAME_CAPTURE == DEM_TRIGGER_TESTFAILED) || \
      (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_TESTFAILED) )
        /* failure counter in event memory entry and/or
         * SWC event memory entry data on DEM_TRIGGER_TESTFAILED have changed
         * -> trigger NvM write */
        Dem_CheckForTriggerNvmWriteGateEntry();
#endif
      }
    }
  }

  DBG_DEM_INTERNALSETEVENTSTATUS_EXIT(Result, EventInfo, EventStatus);
  return Result;
}

FUNC(Std_ReturnType, DEM_CODE) Dem_InternalProcessEventReport(
  Dem_EventIdType     EventId,
  Dem_EventStatusType EventStatus,
  uint8               FunctionId)
{
  Std_ReturnType Result = E_NOT_OK;
  Dem_EventInfoType EventInfo;
#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U)
  Dem_EventIdType LastEventId = DEM_EVENT_ID_INVALID;
  P2CONST(Dem_MultiEventTriggeringType, AUTOMATIC, AUTOMATIC)
    MultiEvTable = Dem_GetMultiEventTriggering(EventId);
#endif

  DBG_DEM_INTERNALPROCESSEVENTREPORT_ENTRY(EventId, EventStatus);

#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U)
  EventInfo.RootId = EventId;

  /* check if reported event is a multi-triggering master
     and accept only FAILED qualified reports if exclusive
     replacement is involved, otherwise multiply any
     status report */
  /* !LINKSTO Dem.MultiEventTriggering,1 */
  /* !LINKSTO Dem.MultiEventTriggering.AlternativeBehavior.ExclusiveReplace,1 */
  if ( (MultiEvTable != NULL_PTR) &&
       ( (MultiEvTable->AlternativeBehavior != DEM_MULTIEVENTTRIGGERING_ALT_EXCLUSIVE_REPLACE) ||
         (EventStatus == DEM_EVENT_STATUS_FAILED) ) )
  {
#if (DEM_NUM_BSW_EVENTS > 0U)
    if (FunctionId == DEM_FID_REPORTERRORSTATUSPREINIT)
    {
      if (Dem_CheckProcessingConditions(EventId) == E_OK)
      {
        /* !LINKSTO Dem.MultiEventTriggering.AlternativeBehavior.ExclusiveReplace.ProcessingConditions.Preinit,1 */
        do
        {
          EventInfo.EventId = Dem_FindNextDependentEvent(EventId, Result, &LastEventId);
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
          if ( (EventInfo.EventId != DEM_EVENT_ID_INVALID) &&
               (Dem_GbiEvAvailable(EventInfo.EventId) == TRUE) )
#else
          if (EventInfo.EventId != DEM_EVENT_ID_INVALID)
#endif
          {
#if (DEM_NUM_ENCONDGRP_SINGLEREF > 0)
            Result =
              (Dem_EnCondGrpStatusCounter[Dem_GbiEnCondGrpIdx(EventInfo.EventId)] > 0U) ? E_NOT_OK : E_OK;
            if (Result == E_OK)
#endif /* DEM_NUM_ENCONDGRP_SINGLEREF > 0 */
            {
              (void)Dem_ReportErrorStatusPreInit(EventInfo, EventStatus);
            }
          }
        } while (EventInfo.EventId != DEM_EVENT_ID_INVALID);
      }
    }
    else
#endif /* DEM_NUM_BSW_EVENTS > 0U */
    if (Dem_CheckProcessingConditions(EventId) == E_OK)
    {
      /* !LINKSTO Dem.MultiEventTriggering.AlternativeBehavior.ExclusiveReplace.ProcessingConditions.Init,3 */
      do
      {
        EventInfo.EventId = Dem_FindNextDependentEvent(EventId, Result, &LastEventId);
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
        if ( (EventInfo.EventId != DEM_EVENT_ID_INVALID) &&
             (Dem_GbiEvAvailable(EventInfo.EventId) == TRUE) )
#else
        if (EventInfo.EventId != DEM_EVENT_ID_INVALID)
#endif
        {
          /* !LINKSTO Dem.SetEventStatus.SynchronousDebouncing.BSW,1 */
          /* !LINKSTO Dem.SetEventStatus.SynchronousDebouncing.SWC,1 */
          Result = Dem_InternalSetEventStatus(EventInfo, EventStatus);
        }
      } while (EventInfo.EventId != DEM_EVENT_ID_INVALID);
    }
    else
    {
      /* conditions not met, so discard report */
    }
  }
  else
#endif /* DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U */
  {
    /* no multi event triggering configured for this event
     * proceed with the usual event processing */
    EventInfo.EventId = EventId;
    switch (FunctionId)
    {
      case DEM_FID_INTERNALSETEVENTSTATUS:
        /* !LINKSTO Dem.SetEventStatus.SynchronousDebouncing.BSW,1 */
        /* !LINKSTO Dem.SetEventStatus.SynchronousDebouncing.SWC,1 */
        Result = Dem_InternalSetEventStatus(EventInfo, EventStatus);
        break;
#if (DEM_NUM_BSW_EVENTS > 0U)
      case DEM_FID_REPORTERRORSTATUSPREINIT:
        Result = Dem_ReportErrorStatusPreInit(EventInfo, EventStatus);
        break;
#endif
      /* CHECK: NOPARSE */
      default: /* should never be reached */
        DEM_UNREACHABLE_CODE_ASSERT(DEM_INTERNAL_API_ID);
        break;
      /* CHECK: PARSE */
    }
  }

  DBG_DEM_INTERNALPROCESSEVENTREPORT_EXIT(Result, EventId, EventStatus);
  return Result;
}

#if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
FUNC(Std_ReturnType, DEM_CODE) Dem_InternalSetEventAvailable(
  Dem_EventIdType EventId,
  boolean         AvailableStatus)
{
  Std_ReturnType Result = E_NOT_OK;
  boolean CurrentAvailableStatus;

  DBG_DEM_INTERNALSETEVENTAVAILABLE_ENTRY(EventId, AvailableStatus);

  CurrentAvailableStatus =
    DEM_IS_BIT_SET_IN_ARRAY(Dem_EventAvailableStatus, EventId) ? TRUE : FALSE;

  if (AvailableStatus != CurrentAvailableStatus)
  {
    Dem_DTCStatusMaskType OldDTCStatusMask;
    Dem_DTCStatusMaskType NewDTCStatusMask;
#if (DEM_NUM_CMB_DTCS > 0U)
    Dem_DTCConfIdxType DTCConfIdx = DEM_GBI_DTCCONFIDX(EventId);
    Dem_EventStatusExtendedType OldCombinedStatus = 0U;
    Dem_EventStatusExtendedType NewCombinedStatus = 0U;
#endif
    /*
     * ENTER critical section
     */
    DEM_ENTER_EXCLUSIVE_AREA();

    OldDTCStatusMask = DEM_DTC_STATUS_MASKS[EventId];
    if (AvailableStatus == FALSE)
    {
      /* !LINKSTO Dem.SWS_Dem_01109,1 */
      /* only allowed to disable the event, if none of the event status
       * bits TF, PDTC, CDTC or WIR is set */
      if (!DEM_IS_ANY_EV_ST_BIT_SET(EventId, DEM_UDS_STATUS_TF |
                                         DEM_UDS_STATUS_PDTC |
                                         DEM_UDS_STATUS_CDTC |
                                         DEM_UDS_STATUS_WIR) )
      {
        Dem_EventMemoryEntryPtrType EvMemEntry;

        /* only allowed to disable the event, if it does not hold an event entry */
        if ( (Dem_SearchForEntry(EventId, &EvMemEntry, NULL_PTR) == FALSE) ||
             (EvMemEntry->EventId != EventId) )
        {
          /* set the event availability status to FALSE */
          DEM_CLR_BIT_IN_ARRAY(Dem_EventAvailableStatus, EventId);
          CurrentAvailableStatus = FALSE;

          /* !LINKSTO Dem.SWS_Dem_01110,1 */
          /* reset status mask for disabled event */
          DEM_DTC_STATUS_MASKS[EventId] = DEM_NO_EVENT_AVAILABLE;

          /* clear error queue */
          Dem_InvalidateErrorQueueEntry(EventId);
        }
      }
    }
    else
    {
      /* reset debouncing counters for the event */
      Dem_DebounceFctPtrTable[Dem_GbiDebounceAlgo(EventId)].ResetFct(EventId);

      /* !LINKSTO Dem.SWS_Dem_01111,1 */
      /* reset status mask for enabled event */
      DEM_DTC_STATUS_MASKS[EventId] = DEM_UDS_STATUS_TNCSLC | DEM_UDS_STATUS_TNCTOC;

      /* set the event availability status to TRUE */
      DEM_SET_BIT_IN_ARRAY(Dem_EventAvailableStatus, EventId);
      CurrentAvailableStatus = TRUE;
    }
    NewDTCStatusMask = DEM_DTC_STATUS_MASKS[EventId];
#if (DEM_NUM_CMB_DTCS > 0U)
    /* if event is combined, update the combined DTC status */
    if (DEM_IS_DTC_COMBINED(DTCConfIdx))
    {
      OldCombinedStatus = Dem_CmbDTCStatus[DTCConfIdx];
      NewCombinedStatus = Dem_CalculateCmbDTCStatus(DTCConfIdx, FALSE);
    }
#endif /* (DEM_NUM_CMB_DTCS > 0U) */
    /*
     * LEAVE critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();

    if (AvailableStatus == CurrentAvailableStatus)
    {
      if (OldDTCStatusMask != NewDTCStatusMask)
      {
#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
        /* notify application about status change */
        Dem_CbTriggerOnEventStatus(EventId, OldDTCStatusMask, NewDTCStatusMask);
#endif
#if (DEM_NUM_CMB_DTCS > 0U)
        Dem_InternalCheckOnCmbDTCStatusChange(EventId, OldCombinedStatus, NewCombinedStatus);
#endif
#if ((DEM_INIT_MONITOR_REENABLED_SUPPORT == STD_ON) && (DEM_USE_CB_INIT_MONITOR == STD_ON))
        if (AvailableStatus == TRUE)
        {
          /* !LINKSTO Dem.SWS_Dem_01230,1 */
          /* inform application about re-enabled DTC settings */
          Dem_CbInitMonitorForEvent(EventId, DEM_INIT_MONITOR_REENABLED);
        }
#endif
      }
      /* AvailableStatus has been changed to the desired value */
      Result = E_OK;
    }
  }
  else /* (AvailableStatus != CurrentAvailableStatus) */
  {
    /* AvailableStatus already has the desired value */
    Result = E_OK;
  }

  DBG_DEM_INTERNALSETEVENTAVAILABLE_EXIT(Result, EventId, AvailableStatus);
  return Result;
}
#endif /* (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY) */

#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)
FUNC(void, DEM_CODE) Dem_PermanentMemoryNotifyClear(Dem_EventIdType EventId)
{
  Dem_SizeEvMemEntryType EntryIdx;

  DBG_DEM_PERMANENTMEMORYNOTIFYCLEAR_ENTRY(EventId);

  for (EntryIdx = 0U; EntryIdx < DEM_MAX_NUMBER_EVENT_ENTRY_PER; EntryIdx++)
  {
    /* make a copy of the permanent memory entry */
    Dem_PermanentMemoryEntryType Entry = Dem_EventMemoryPermanent[EntryIdx];

    if (DEM_GET_PERMANENT_MEMORY_EVENT_ID(Entry) == EventId)
    {
      /* !LINKSTO Dem_OBD_0084,1 */
      DEM_CLR_PERMANENT_MEMORY_PFC_CYCLE_COND(Entry);
      DEM_CLR_PERMANENT_MEMORY_PASSED_CYCLE_COND(Entry);

      /* status of the permanent memory entry changed */
      if (Dem_EventMemoryPermanent[EntryIdx] != Entry)
      {
        Dem_EventMemoryPermanent[EntryIdx] = Entry;
        /* !LINKSTO Dem_OBD_0086,1 */
        Dem_EventMemoryPermanentUpdated = TRUE;
      }

      break;
    }
  }

  DBG_DEM_PERMANENTMEMORYNOTIFYCLEAR_EXIT(EventId);
}

FUNC(Std_ReturnType, DEM_CODE) Dem_PermanentMemoryAddEntry(
  Dem_EventIdType EventId)
{
  Dem_EventIdType EntryEventId;
  Dem_SizeEvMemEntryType EntryIdx;
  Dem_SizeEvMemEntryType FreeSlot = 0U;
  boolean EmptySlotFound = FALSE;
  boolean EventFound = FALSE;
  /* !LINKSTO Dem_OBD_0037,1 */
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_PERMANENTMEMORYADDENTRY_ENTRY(EventId);

  /* !LINKSTO dsn.Dem.OBD.PermanentMemory.EventCombination.Storage,1 */
  /* for combined events having OBD configured, the master event
   * will be stored in the PM */
  EntryEventId = DEM_GET_MASTER_EVID(EventId);

  /* try to find an empty slot or whether event is already part of permanent memory */
  for (EntryIdx = 0U; EntryIdx < DEM_MAX_NUMBER_EVENT_ENTRY_PER; EntryIdx++)
  {
    Dem_PermanentMemoryEntryType Entry = Dem_EventMemoryPermanent[EntryIdx];

    /* !LINKSTO Dem_OBD_0036,1 */
    if (DEM_GET_PERMANENT_MEMORY_EVENT_ID(Entry) == EntryEventId)
    {
      EventFound = TRUE;

      /* !LINKSTO Dem_OBD_0088,1 */
      DEM_CLR_PERMANENT_MEMORY_PFC_CYCLE_COND(Entry);
      DEM_CLR_PERMANENT_MEMORY_PASSED_CYCLE_COND(Entry);

      if (Dem_EventMemoryPermanent[EntryIdx] != Entry)
      {
        Dem_EventMemoryPermanent[EntryIdx] = Entry;

        /* notification that permanent memory is updated */
        /* !LINKSTO Dem_OBD_0032,2 */
        Dem_EventMemoryPermanentUpdated = TRUE;
      }

      break;
    }
    else
    {
      /* !LINKSTO Dem_OBD_0039,2, Dem_OBD_0047,2 */
      if ( (DEM_GET_PERMANENT_MEMORY_EVENT_ID(Entry) == DEM_EVENT_ID_INVALID) &&
          (EmptySlotFound == FALSE) )
      {
        /* remember the first empty slot */
        FreeSlot = EntryIdx;
        EmptySlotFound = TRUE;
      }
    }
  }
  /*
    make an entry in permanent memory only if free slot is found and
    the event does not exist already in permanent memory
  */
  /* !LINKSTO VCC_DEM_006_Req133v1,1 */
  if (EventFound == TRUE)
  {
    /* Event is already stored in permanent memory */
    /* !LINKSTO Dem_OBD_0036,1 */
    Result = E_OK;
  }
  else
  {
    /* !LINKSTO Dem_OBD_0039,2 */
    if (EmptySlotFound == TRUE)
    {
      Dem_PermanentMemoryEntryType Entry = 0U;

      /* store new EntryEventId in permanent memory */
      /* !LINKSTO Dem_OBD_0047,2, Dem_OBD_0088,1 */
      DEM_SET_PERMANENT_MEMORY_EVENT_ID(Entry, EntryEventId);
      DEM_CLR_PERMANENT_MEMORY_PFC_CYCLE_COND(Entry);
      DEM_CLR_PERMANENT_MEMORY_PASSED_CYCLE_COND(Entry);

      Dem_EventMemoryPermanent[FreeSlot] = Entry;

      /* !LINKSTO Dem_OBD_0038,1 */
      Result = E_OK;

      /* notification that permanent memory is updated */
      /* !LINKSTO Dem_OBD_0032,2 */
      Dem_EventMemoryPermanentUpdated = TRUE;
    }
    else
    {
      DEM_SET_BIT_8(DEM_OVFIND_FLAGS, DEM_DTC_ORIGIN_IDX(DEM_DTC_ORIGIN_PERMANENT_MEMORY));

      /* Note: trigger on EventDataChanged callback not necessary, because
       * the overflow bit of the permanent memory is not mapped to an
       * extended data record */
    }
  }

  DBG_DEM_PERMANENTMEMORYADDENTRY_EXIT(EventId, Result);
  return Result;
}

FUNC(void, DEM_CODE) Dem_PermanentMemoryRemoveEntry(
  Dem_EventIdType EventId)
{
  Dem_EventIdType EntryEventId;
  Dem_SizeEvMemEntryType EntryIdx;

  DBG_DEM_PERMANENTMEMORYREMOVEENTRY_ENTRY(EventId);

  /* !LINKSTO dsn.Dem.OBD.PermanentMemory.EventCombination.Removal,1 */
  /* for combined events having OBD configured, the master event
   * will be stored in the PM */
  EntryEventId = DEM_GET_MASTER_EVID(EventId);

  /* try to find an EntryEventId stored in permanent memory */
  for (EntryIdx = 0U; EntryIdx < DEM_MAX_NUMBER_EVENT_ENTRY_PER; EntryIdx++)
  {
    Dem_PermanentMemoryEntryType Entry = Dem_EventMemoryPermanent[EntryIdx];

    if (DEM_GET_PERMANENT_MEMORY_EVENT_ID(Entry) == EntryEventId)
    {
      /* EntryEventId has been found and shall be removed from permanent
       * memory, other status flags reset for robustness sake */
      /* !LINKSTO Dem_OBD_0041,2, Dem_OBD_0007,2 */
      DEM_SET_PERMANENT_MEMORY_EVENT_ID(Entry, DEM_EVENT_ID_INVALID);
      DEM_CLR_PERMANENT_MEMORY_PFC_CYCLE_COND(Entry);
      DEM_CLR_PERMANENT_MEMORY_PASSED_CYCLE_COND(Entry);

      /* create at least one entry space if status of overflow indication bit is set */
      if (DEM_IS_OVFIND_SET(DEM_DTC_ORIGIN_PERMANENT_MEMORY - 1U))
      {
        DEM_SET_PERMANENT_MEMORY_FILL_COND(Entry);
      }
      Dem_EventMemoryPermanent[EntryIdx] = Entry;

      /* !LINKSTO Dem_OBD_0049,1 */
      /* mark it as not non-volatile stored */
      Dem_EventMemoryPermanentNonVolatileStored[EntryIdx] =
          DEM_PERMANENT_MEMORY_V_STORED;

      /* notification that permanent memory is updated */
      /* !LINKSTO Dem_OBD_0033,1 */
      Dem_EventMemoryPermanentUpdated = TRUE;

      DEM_CLR_BIT_8(DEM_OVFIND_FLAGS, DEM_DTC_ORIGIN_IDX(DEM_DTC_ORIGIN_PERMANENT_MEMORY));

      break;
    }
  }

  DBG_DEM_PERMANENTMEMORYREMOVEENTRY_EXIT(EventId);
}

FUNC(void, DEM_CODE) Dem_PermanentMemoryStatusUpdate(void)
{
  Dem_SizeEvMemEntryType EntryIdx;
  boolean Dem_EventMemoryFillPermanentEntry = FALSE;
  DBG_DEM_PERMANENTMEMORYSTATUSUPDATE_ENTRY();

  /*
   * ENTER critical section
   */
  DEM_ENTER_EXCLUSIVE_AREA();

  /* try to find whether some events can be removed from permanent memory */
  for (EntryIdx = 0U; EntryIdx < DEM_MAX_NUMBER_EVENT_ENTRY_PER; EntryIdx++)
  {
    Dem_PermanentMemoryEntryType Entry = Dem_EventMemoryPermanent[EntryIdx];
    const Dem_EventIdType EventId = DEM_GET_PERMANENT_MEMORY_EVENT_ID(Entry);

    if (EventId != DEM_EVENT_ID_INVALID)
    {
      /* a permanent fault is removed via Dem_PermanentMemoryRemoveEntry()
       * when the MIL is healed. So, an existing permanent fault with no MIL
       * activation would indicate that MIL was extinguished due to ClearDTC.
       * In this case, special conditions specified by legislation are
       * necessary to remove the permanent fault. */
#if (DEM_NUM_CMB_DTCS > 0U)
      if ( (Dem_IsEventsMILIndicatorActive(EventId) == FALSE) &&
           (Dem_IsCmbEventsMILIndicatorActive(EventId) == FALSE) )
#else
      if (Dem_IsEventsMILIndicatorActive(EventId) == FALSE)
#endif
      {
        Dem_DTCStatusMaskType DTCStatus = DEM_GET_DTC_STATUS(EventId);

        if (DEM_IS_ANY_BIT_SET(DTCStatus, DEM_UDS_STATUS_TFTOC) != FALSE)
        {
          /* !LINKSTO Dem_OBD_0091,1 */
          DEM_CLR_PERMANENT_MEMORY_PFC_CYCLE_COND(Entry);
          DEM_CLR_PERMANENT_MEMORY_PASSED_CYCLE_COND(Entry);
        }
        else
        {
          boolean MinRatio;

          /* if DemMinRatioEvent for this event is configured to TRUE */
          if (Dem_GbiMinRatioEvent(EventId) == TRUE)
          {
            /* there is no additional dependency to PfcStatus flag */
            /* !LINKSTO Dem_OBD_0060,1 */
            MinRatio = TRUE;
          }
          else
          {
            /* else consider PfcStatus flag */
            /* !LINKSTO Dem_OBD_0059,1 */
            MinRatio = DEM_PFC_STATUS;
          }

          if (MinRatio != FALSE)
          {
            /* !LINKSTO Dem_OBD_0092,1 */
            DEM_SET_PERMANENT_MEMORY_PFC_CYCLE_COND(Entry);
          }

          if (DEM_IS_ANY_BIT_SET(DTCStatus, DEM_UDS_STATUS_TNCTOC) == FALSE)
          {
            /* !LINKSTO Dem_OBD_0093,1 */
            DEM_SET_PERMANENT_MEMORY_PASSED_CYCLE_COND(Entry);
          }

          /* check following condition and decide whether EventId can be
           * removed from permanent memory
           * - Check that Passed Cycle condition is fulfilled
           * - Check that Pfc Cycle condition is fulfilled */
          /* !LINKSTO Dem_OBD_0061,6 */
          if ( (DEM_GET_PERMANENT_MEMORY_PFC_CYCLE_COND(Entry) != FALSE) &&
               (DEM_GET_PERMANENT_MEMORY_PASSED_CYCLE_COND(Entry) != FALSE) )
          {
            /* EventId has been found and shall be removed from permanent memory */
            /* !LINKSTO Dem_OBD_0007,2, Dem_OBD_0045,1 */
            DEM_SET_PERMANENT_MEMORY_EVENT_ID(Entry, DEM_EVENT_ID_INVALID);
            DEM_CLR_PERMANENT_MEMORY_PFC_CYCLE_COND(Entry);
            DEM_CLR_PERMANENT_MEMORY_PASSED_CYCLE_COND(Entry);
            DEM_SET_PERMANENT_MEMORY_FILL_COND(Entry);

           if (DEM_IS_OVFIND_SET(DEM_DTC_ORIGIN_PERMANENT_MEMORY - 1U))
           {
             /* emptied entries can be filled with other events requesting the MIL */
             Dem_EventMemoryFillPermanentEntry = TRUE;
           }

            /* mark it as not non-volatile stored */
            /* !LINKSTO Dem_OBD_0049,1 */
            Dem_EventMemoryPermanentNonVolatileStored[EntryIdx] =
                DEM_PERMANENT_MEMORY_V_STORED;

            DEM_CLR_BIT_8(DEM_OVFIND_FLAGS, DEM_DTC_ORIGIN_IDX(DEM_DTC_ORIGIN_PERMANENT_MEMORY));
          }
        }

        /* status of the permanent memory entry changed */
        if (Dem_EventMemoryPermanent[EntryIdx] != Entry)
        {
          Dem_EventMemoryPermanent[EntryIdx] = Entry;

          /* notification that permanent memory is updated */
          /* !LINKSTO Dem_OBD_0034,1, Dem_OBD_0094,1  */
          Dem_EventMemoryPermanentUpdated = TRUE;
        }
      }
    }
    else
    {
      if (DEM_GET_PERMANENT_MEMORY_FILL_COND(Entry) != FALSE)
      {
        Dem_EventMemoryFillPermanentEntry = TRUE;
      }
    }
    /* Deviation TASKING-7 */
    DEM_CLR_PERMANENT_MEMORY_FILL_COND(Entry);
  }

  /*
   * LEAVE critical section
   */
  DEM_EXIT_EXCLUSIVE_AREA();

#if (DEM_CALIBRATION_SUPPORT == STD_ON)
  {
    if (Dem_EventMemoryFillPermanentEntry == TRUE)
    {
      Dem_EventIdType EventId;

      for (EventId = 1U; EventId < DEM_NUMBER_OF_EVENTS; EventId++)
      {
        /* check if MIL indicator of EventId is active */
        if (Dem_IsEventsMILIndicatorActive(EventId) == TRUE)
        {
          Std_ReturnType AddEntryResult;
          /*
           * ENTER critical section
           */
          DEM_ENTER_EXCLUSIVE_AREA();

          /* try to add EventId to the permanent memory */
          /* !LINKSTO Dem_OBD_0035,1, Dem_OBD_0046,4 */
          AddEntryResult = Dem_PermanentMemoryAddEntry(EventId);

          /*
           * LEAVE critical section
           */
          DEM_EXIT_EXCLUSIVE_AREA();

          if (AddEntryResult != E_OK)
          {
            break;
          }
        }
      }
    }
  }
/* calibration is disabled and event availability is not considered */
#else
  {
    if (Dem_EventMemoryFillPermanentEntry == TRUE)
    {
      const uint32 indMILStart = Dem_IndicatorDesc[DEM_MIL_ID].StartIdx;
      const uint32 indMILEnd = indMILStart + Dem_IndicatorDesc[DEM_MIL_ID].Number;

      Dem_IndicatorIdxType LinkIdx;

      /* try to add confirmed entries into permanent memory */

      /* as long as empty entries in permanent memory exist,
       * check whether some other event which is connected to MIL
       * is qualified to be stored in permanent memory too */
      for ( LinkIdx = (Dem_IndicatorIdxType)indMILStart;
            (LinkIdx < (Dem_IndicatorIdxType)indMILEnd);
            ++LinkIdx)
      {
        const Dem_EventIdType EventId = Dem_IndicatorLink[LinkIdx].EventId;

        /* check if MIL indicator of EventId is active */
        if (Dem_IsEventsMILIndicatorActive(EventId) == TRUE)
        {
          Std_ReturnType AddEntryResult;
          /*
           * ENTER critical section
           */
          DEM_ENTER_EXCLUSIVE_AREA();

          /* try to add EventId to the permanent memory */
          /* !LINKSTO Dem_OBD_0035,1, Dem_OBD_0046,4 */
          AddEntryResult = Dem_PermanentMemoryAddEntry(EventId);

          /*
           * LEAVE critical section
           */
          DEM_EXIT_EXCLUSIVE_AREA();

          if (AddEntryResult != E_OK)
          {
            break;
          }
        }
      }
    }
  }
#endif /* DEM_CALIBRATION_SUPPORT == STD_ON */

  /* reset permanent fault status */
  /* !LINKSTO Dem_OBD_0030,1 */
  DEM_PFC_STATUS = FALSE;

  DBG_DEM_PERMANENTMEMORYSTATUSUPDATE_EXIT();
  return;
}
#endif /* #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U) */

FUNC(Std_ReturnType, DEM_CODE) Dem_DebounceEvent(
  Dem_EventIdType                                  EventId,
  P2VAR(Dem_EventStatusType, AUTOMATIC, AUTOMATIC) EventStatus)
{
  /* Always returns E_OK, except on DET error detection */
  Std_ReturnType Result = E_OK;

  const Dem_DebounceType DebounceAlgo = Dem_GbiDebounceAlgo(EventId);

  DBG_DEM_DEBOUNCEEVENT_ENTRY(EventId, EventStatus);

  /* event debounce-handling */
  if (DebounceAlgo != DEM_DEBOUNCE_MONITOR)
  {
    /* for every event one debouncing algorithm has to be selected
     * the way in which Dem_DebounceFctPtrTable is assembled ensures that,
     * if the debouncing algorithm is Dem internal then the reference to the
     * debouncing function is not a NULL pointer */
    DEM_PRECONDITION_ASSERT(
        (Dem_DebounceFctPtrTable[DebounceAlgo].DebounceEventFct != NULL_PTR),
        DEM_INTERNAL_API_ID);
    /* debounce event */
    Dem_DebounceFctPtrTable[DebounceAlgo].DebounceEventFct(
      EventId, EventStatus);
  }

  if ( (*EventStatus == DEM_EVENT_STATUS_PREFAILED) ||
       (*EventStatus == DEM_EVENT_STATUS_PREPASSED) )
  {
    *EventStatus = DEM_EVENT_STATUS_UNQUALIFIED;

#if (DEM_DEV_ERROR_DETECT == STD_ON)
    if (DebounceAlgo == DEM_DEBOUNCE_MONITOR)
    {
      /* if the event is not qualified and monitor internal debouncing is used,
       * an error is signaled (caller will trigger a DET error) */
      Result = DEM_E_DET_REPORT;
    }
#endif
  }

  DBG_DEM_DEBOUNCEEVENT_EXIT(Result, EventId, EventStatus);

  return Result;
}

#if (DEM_NUM_CMB_DTCS > 0U)

FUNC(Dem_EventStatusExtendedType, DEM_CODE) Dem_CalculateCmbDTCStatus(Dem_DTCConfIdxType DTCConfIdx, boolean ResetCmbPDTC)
{
  Dem_CmbDTCEvLnkType CmbEvIdx;
  Dem_EventStatusExtendedType CombinedStatus = 0x00U;
#if (DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON)
  /* Combined PDTC status is not reset when DEM_OBDONUDS_COMBINATION_ENABLED is enabled */
  Dem_EventStatusExtendedType OldCombinedPDTC = Dem_CmbDTCStatus[DTCConfIdx] & DEM_UDS_STATUS_PDTC;
#endif

  DBG_DEM_CALCULATECMBDTCSTATUS_ENTRY(DTCConfIdx, ResetCmbPDTC);

#if (DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON)
  /* When DEM_OBDONUDS_COMBINATION_ENABLED is enabled,
     the combined PDTC status is only reset on request */
  if(ResetCmbPDTC != TRUE)
  {
    CombinedStatus = OldCombinedPDTC;
  }
#else
  TS_PARAM_UNUSED(ResetCmbPDTC);
#endif

  for (CmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx]; CmbEvIdx < Dem_CmbDTCEvLnk[DTCConfIdx + 1U]; CmbEvIdx++)
  {
    Dem_EventIdType CurrentEvent = Dem_CmbDTCEvents[CmbEvIdx];
    /* !LINKSTO Dem.OBDonUDS.CombinedUDSDTCStatus.PDTC.SetByFailed.NoResetOnOverflow,1 */
    /* !LINKSTO Dem.OBDonUDS.CombinedUDSDTCStatus.PDTC.SetByFailed.MemoryEntryExists,1 */
    CombinedStatus |= DEM_DTC_STATUS_MASKS[CurrentEvent];
  }

#if (DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON)

  /* !LINKSTO dsn.Dem.OBDonUDS.EventCombination.NonVolatileCmbPDTC,1 */
  if (OldCombinedPDTC != (CombinedStatus & DEM_UDS_STATUS_PDTC))
  {
    DEM_MODIFY_BIT_IN_ARRAY(Dem_NvData.CmbPDTC, DTCConfIdx, (CombinedStatus & DEM_UDS_STATUS_PDTC) >> 2U);
  }
#endif

  /* update combined TNCTOC bit computation */
  /* check if combined DTC bit for TFTOC is set */
  if (DEM_IS_ANY_BIT_SET(CombinedStatus, DEM_UDS_STATUS_TFTOC))
  {
    /* in this case we must force a reset for the TNCTOC bit */
    CombinedStatus &= 0xBFU;
  }

  /* update combined TNCSLC bit computation */
  /* check if combined DTC bit for TFSLC is set */
  if (DEM_IS_ANY_BIT_SET(CombinedStatus, DEM_UDS_STATUS_TFSLC))
  {
    /* in this case we must force a reset for the TNCSLC bit */
    CombinedStatus &= 0xEFU;
  }
  /* update the combined DTC Status */
  Dem_CmbDTCStatus[DTCConfIdx] = CombinedStatus;

  DBG_DEM_CALCULATECMBDTCSTATUS_EXIT(CombinedStatus, DTCConfIdx, ResetCmbPDTC);

  return CombinedStatus;
}
#endif /* (DEM_NUM_CMB_DTCS > 0U */

FUNC(void, DEM_CODE) Dem_InternalSetSwcEventStatus(
  Dem_EventInfoType                           EventInfo,
  Dem_EventStatusType                         EventStatus,
  P2VAR(Std_ReturnType, AUTOMATIC, AUTOMATIC) SetSwcEventStatusResult)
{
  const Dem_EventIdType EventId = EventInfo.EventId;
  const Dem_DTCStatusMaskType OldDTCStatusMask = DEM_DTC_STATUS_MASKS[EventId];

  const Dem_EventStatusType OldEventStatus =
    DEM_IS_ANY_BIT_SET(OldDTCStatusMask, DEM_UDS_STATUS_TF) ?
      DEM_EVENT_STATUS_FAILED : DEM_EVENT_STATUS_PASSED;

  Dem_StatusTransitionType TransitionType = 0U;

#if (DEM_IGNORE_RESET_EVENT_STATUS_FOR_ENTRY == STD_ON)
  const Dem_EventStatusType OldResetResistantEventStatus =
    DEM_IS_RESISTANT_TF_STATUS_BIT_SET(EventId) ?
      DEM_EVENT_STATUS_FAILED : DEM_EVENT_STATUS_PASSED;
#endif

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

  DBG_DEM_INTERNALSETSWCEVENTSTATUS_ENTRY(EventInfo,
                                          EventStatus,
                                          SetSwcEventStatusResult);

  if ( ( (EventStatus == DEM_EVENT_STATUS_FAILED) ||
         (EventStatus == DEM_EVENT_STATUS_CONFIRMED) ) &&
       (!DEM_IS_ST_BIT_TFTOC_SET(OldDTCStatusMask)) )
  {
    /* needed for event status update, not used during entry update */
    TransitionType |= DEM_TRANSITION_EVENT_TFTOC;
  }

#if (DEM_IGNORE_RESET_EVENT_STATUS_FOR_ENTRY == STD_ON)
  /* OldEventStatus and OldResetResistantEventStatus have to be checked
   * to handle status update (based on OldEventStatus) and/or event entry
   * update (based on OldResetResistantEventStatus).
   */
  if ( (!DEM_IS_ST_BIT_TNCTOC_SET(OldDTCStatusMask)) &&
       (EventStatus == OldEventStatus) &&
       (EventStatus == OldResetResistantEventStatus) )
#else
  if ( (!DEM_IS_ST_BIT_TNCTOC_SET(OldDTCStatusMask)) &&
       (EventStatus == OldEventStatus) )
#endif
  {
#if (DEM_NUM_INDICATOR_LINKS > 0U)
#if (DEM_CALIBRATION_SUPPORT == STD_ON)
    /* Deviation TASKING-4 */
    if ( (EventStatus == DEM_EVENT_STATUS_FAILED) ||
         (EventStatus == DEM_EVENT_STATUS_CONFIRMED)
       )
#else
    const boolean IndicatorUsed = Dem_GbiIndicatorUsed(EventId);
    /* Deviation TASKING-4 */
    if ( (IndicatorUsed == TRUE) &&
        ( (EventStatus == DEM_EVENT_STATUS_FAILED) ||
          (EventStatus == DEM_EVENT_STATUS_CONFIRMED) )
      )
#endif
    {
      /* the event was already tested this operation cycle and another FAILED/CONFIRMED is
       * reported for an event with indicator: check for WIR update */
      Dem_ProcessEventJobMaskType ProcessEventJobs = DEM_PROCESSEVENT_INDICATORUPDATE;
      Dem_ProcessEvent(DEM_SID_SetEventStatus, EventInfo, EventStatus,
                       TransitionType, ProcessEventJobs, &Notification);
      *SetSwcEventStatusResult = E_OK;
    }
    else
#endif /* (DEM_NUM_INDICATOR_LINKS > 0U) */
    {
      /* the event was already tested this operation cycle and reported status
       * doesn't change: no qualification-handling necessary */
      *SetSwcEventStatusResult = E_OK;
    }
  }
  else
  {
    Dem_ProcessEventJobMaskType ProcessEventJobs = DEM_PROCESSEVENT_STATUSUPDATE;

    boolean ErrorReenterPrecondition =
      Dem_CheckEntryProcessingConditions(EventId, EventStatus, &TransitionType);

#if (DEM_NUM_CMB_DTCS > 0U)
    Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
    Dem_EventStatusExtendedType OldCombinedStatus = 0U;
    Dem_EventStatusExtendedType NewCombinedStatus = 0U;
#endif
    /* append or update event entry, if error-reenter-condition is satisfied */
    if ( ErrorReenterPrecondition )
    {
#if (DEM_STORE_INTERNAL_EVENTS == STD_OFF)
      if (DEM_VALID_DTC_FOR_EVENT_STORAGE(EventId))
#endif
      {
#if ( (DEM_FREEZE_FRAME_CAPTURE == DEM_TRIGGER_TESTFAILED) || \
      (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_TESTFAILED) )
        /* process Event synchronous */
        ProcessEventJobs |= DEM_PROCESSEVENT_ENTRYUPDATE;
#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_SINGLE)
        ProcessEventJobs |= DEM_PROCESSEVENT_OBDENTRYUPDATE;
#endif
#else
        /* enqueue Event, to it process asynchronous */
        boolean EntryIsWritten = FALSE;

        /*
         * ENTER critical section to protect the error-queue & queue-pointers
         *       call-context: Rte (Task), Dem (Task)
         */
        DEM_ENTER_EXCLUSIVE_AREA();

        /* make entry in error-queue */
        EntryIsWritten = Dem_WriteErrorQueueEntry(EventInfo,
                                                  EventStatus,
                                                  TransitionType);

        /*
         * LEAVE critical section
         */
        DEM_EXIT_EXCLUSIVE_AREA();

        /* check if write was successful */
        if (EntryIsWritten == FALSE)
        {
          /* an error is signaled (caller will trigger DET) */
          *SetSwcEventStatusResult = DEM_E_DET_REPORT;
        }
#endif /* (DEM_FREEZE_FRAME_CAPTURE == DEM_TRIGGER_TESTFAILED) || \
          (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_TESTFAILED) */
      }
    }

    /* 1st step: prepare the gate entry indirectly when
     * the event entry is processed */
    Dem_ProcessEvent(DEM_SID_SetEventStatus, EventInfo, EventStatus,
                     TransitionType, ProcessEventJobs, &Notification);

#if (DEM_NUM_CMB_DTCS > 0U)
    /*
     * ENTER critical section
     */
    DEM_ENTER_EXCLUSIVE_AREA();

    if ( (DEM_IS_DTC_COMBINED(DTCConfIdx)) &&
         (Notification.ProcessedEventMsg.EventId != DEM_EVENT_ID_INVALID) )
    {
      OldCombinedStatus = Dem_CmbDTCStatus[DTCConfIdx];
      NewCombinedStatus = Dem_CalculateCmbDTCStatus(DTCConfIdx, FALSE);
    }
    /*
     * EXIT critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();

    Dem_InternalCheckOnCmbDTCStatusChange(EventId, OldCombinedStatus, NewCombinedStatus);

#endif
  }

#if ( ((DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) || \
       (DEM_TRIG_CB_ON_EVDAT == STD_ON))            || \
        ((DEM_J1939_SUPPORT == STD_ON)              && \
         (DEM_J1939_READING_DTC_SUPPORT == STD_ON)) )
  Dem_ProcessEventNotifications(&Notification);
#endif

  DBG_DEM_INTERNALSETSWCEVENTSTATUS_EXIT(EventInfo,
                                         EventStatus,
                                         SetSwcEventStatusResult);
}

FUNC(void, DEM_CODE) Dem_InternalSetBswEventStatus(
  Dem_EventInfoType                           EventInfo,
  Dem_EventStatusType                         EventStatus,
  P2VAR(Std_ReturnType, AUTOMATIC, AUTOMATIC) SetBswEventStatusResult)
{
  Dem_EventStatusType PreviousEntryStatus;
  boolean EntryPresent;
  const Dem_EventIdType EventId = EventInfo.EventId;

  Dem_DTCStatusMaskType OldDTCStatusMask = DEM_DTC_STATUS_MASKS[EventId];

  const Dem_EventStatusType OldEventStatus =
    DEM_IS_ANY_BIT_SET(OldDTCStatusMask, DEM_UDS_STATUS_TF) ?
      DEM_EVENT_STATUS_FAILED : DEM_EVENT_STATUS_PASSED;

#if (DEM_IGNORE_RESET_EVENT_STATUS_FOR_ENTRY == STD_ON)
  const Dem_EventStatusType OldResetResistantEventStatus =
    DEM_IS_RESISTANT_TF_STATUS_BIT_SET(EventId) ?
      DEM_EVENT_STATUS_FAILED : DEM_EVENT_STATUS_PASSED;
#endif

#if ( (DEM_NUM_BSWEVENT_INDICATOR_USED > 0U) && \
      (DEM_COMMON_OPERATION_CYCLE_SUPPORT == STD_OFF) )
  boolean UpdateIndicator;
#endif

  DBG_DEM_INTERNALSETBSWEVENTSTATUS_ENTRY(EventInfo,
                                          EventStatus,
                                          SetBswEventStatusResult);

#if ( (DEM_NUM_BSWEVENT_INDICATOR_USED > 0U) && \
      (DEM_COMMON_OPERATION_CYCLE_SUPPORT == STD_OFF) )
  UpdateIndicator = Dem_CheckErrorRequiresIndUpdate(EventId,
                                                    EventStatus);
#endif

  /*
   * ENTER critical section to protect the error-queue & queue-pointers
   *       call-context: any, Dem (Task)
   */
  DEM_ENTER_EXCLUSIVE_AREA();

  /* check if event is already present in error-queue */
  EntryPresent = Dem_CheckErrorQueueEntry(EventId, &PreviousEntryStatus);

  /* append or update event entry, if error-reenter-condition is satisfied */
#if (DEM_IGNORE_RESET_EVENT_STATUS_FOR_ENTRY == STD_ON)
  /* OldEventStatus and OldResetResistantEventStatus have to be checked
   * to handle status update (based on OldEventStatus) and/or event entry
   * update (based on OldResetResistantEventStatus).
   */
  if (  ((EntryPresent == TRUE) && (EventStatus != PreviousEntryStatus)) ||
     ( (EntryPresent == FALSE) &&
       ( DEM_IS_ST_BIT_TNCTOC_SET(OldDTCStatusMask) ||
         (EventStatus != OldEventStatus)  ||
         (EventStatus != OldResetResistantEventStatus)) ) )
#else
  if (  ((EntryPresent == TRUE) && (EventStatus != PreviousEntryStatus)) ||
       ( (EntryPresent == FALSE) &&
         ( DEM_IS_ST_BIT_TNCTOC_SET(OldDTCStatusMask) ||
           (EventStatus != OldEventStatus) ) ) )
#endif
  {
    Dem_CheckErrorReQueueEntry(EventInfo, EventStatus, OldDTCStatusMask,
                               SetBswEventStatusResult);
  }
#if ( (DEM_NUM_BSWEVENT_INDICATOR_USED > 0U) && \
      (DEM_COMMON_OPERATION_CYCLE_SUPPORT == STD_OFF) )
  else if ((EntryPresent == FALSE) && (UpdateIndicator == TRUE))
  {
    Dem_CheckErrorReQueueEntry(EventInfo, EventStatus, OldDTCStatusMask,
                               SetBswEventStatusResult);
  }
  else
  {
    /* do nothing */
  }
#endif /* DEM_NUM_BSWEVENT_INDICATOR_USED DEM_COMMON_OPERATION_CYCLE_SUPPORT */

  /*
   * LEAVE critical section
   */
  DEM_EXIT_EXCLUSIVE_AREA();

  DBG_DEM_INTERNALSETBSWEVENTSTATUS_EXIT(EventInfo,
                                         EventStatus,
                                         SetBswEventStatusResult);
}

FUNC(void, DEM_CODE) Dem_UpdateEventStatusOnQualification(
  Dem_EventIdType                   EventId,
  Dem_EventStatusType               EventStatus,
#if (DEM_NUM_INDICATOR_LINKS > 0U)
  boolean                           EventWIRUpdate,
#endif /* DEM_NUM_INDICATOR_LINKS */
  Dem_EventNotificationDataPtrType  Notification)
{
#if ((DEM_J1939_SUPPORT == STD_ON) && (DEM_J1939_READING_DTC_SUPPORT == STD_ON))
  boolean ReportToJ1939Dcm = FALSE;
#endif /* ((DEM_J1939_SUPPORT == STD_ON) && (DEM_J1939_READING_DTC_SUPPORT == STD_ON)) */

#if (DEM_NUM_INDICATOR_LINKS > 0U)
  DBG_DEM_UPDATEEVENTSTATUSONQUALIFICATION_ENTRY(EventId, EventStatus, EventWIRUpdate, Notification);
#else
  DBG_DEM_UPDATEEVENTSTATUSONQUALIFICATION_ENTRY(EventId, EventStatus, 0U, Notification);
#endif

  /* check Event Status */
  if (EventStatus == DEM_EVENT_STATUS_PASSED)
  {
#if ((DEM_J1939_SUPPORT == STD_ON) && (DEM_J1939_READING_DTC_SUPPORT == STD_ON))
    if ((DEM_IS_EV_ST_BIT_TF_SET(EventId)) && (Dem_InternalGetJ1939DTC(EventId) != DEM_NO_DTC))
    {
        ReportToJ1939Dcm = TRUE;
    }
#endif /* ((DEM_J1939_SUPPORT == STD_ON) && (DEM_J1939_READING_DTC_SUPPORT == STD_ON)) */
    /* TEST NOT COMPLETE -> 0, TEST FAILED -> 0 */
    DEM_CLR_EV_ST_MASK(EventId,
                       (DEM_UDS_STATUS_TNCSLC |
                        DEM_UDS_STATUS_TNCTOC |
                        DEM_UDS_STATUS_TF));

    DEM_CLEAR_RESISTANT_TF_STATUS_BIT(EventId);

    /* EVER FAILED -> unchanged */
  }
  else /* EventStatus is DEM_EVENT_STATUS_FAILED or DEM_EVENT_STATUS_CONFIRMED */
  {
#if ( (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) || \
      ( (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF) && \
        (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)  && \
        (DEM_OPCYC_OBD_DCY_USED == STD_ON) ) || \
      ( (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF) && \
        (DEM_NUM_CMB_DTCS > 0U) ) )
    boolean SearchForEventMemoryEntry = FALSE;
    Dem_EventMemoryEntryPtrType EvMemEntry = NULL_PTR;
    Dem_SizeEvMemEntryType EvMemEntryIdx = 0U;
    boolean EntryExists = FALSE;
#endif

    /* default set DTC status mask */
    uint8 EventStatusSetMask = DEM_UDS_STATUS_TF |
                               DEM_UDS_STATUS_TFTOC |
                               DEM_UDS_STATUS_TFSLC;
    /* default clear DTC status mask */
    uint8 EventStatusClearMask = DEM_UDS_STATUS_TNCTOC |
                                 DEM_UDS_STATUS_TNCSLC;

    DEM_SET_RESISTANT_TF_STATUS_BIT(EventId);

#if ((DEM_J1939_SUPPORT == STD_ON) && (DEM_J1939_READING_DTC_SUPPORT == STD_ON))
    if (!DEM_IS_EV_ST_BIT_TF_SET(EventId))
    {
        ReportToJ1939Dcm = TRUE;
    }
#endif /* ((DEM_J1939_SUPPORT == STD_ON) && (DEM_J1939_READING_DTC_SUPPORT == STD_ON)) */

#if (DEM_GET_DTCBYOCCURRENCETIME_SUPPORT == STD_ON)
    /* only for FAILED-transition and directly promoted CONFIRMED-trigger */
    if ((EventStatus == DEM_EVENT_STATUS_FAILED) || (!DEM_IS_EV_ST_BIT_TF_SET(EventId)))
    {
      /* store event to be failed DTC occurrence kind */
      Dem_UpdateEventIdOccurKinds(EventId,
        DEM_FIRST_FAILED_DTC, DEM_MOST_RECENT_FAILED_DTC);
    }
#endif

#if (DEM_RESET_PENDING_BIT_ON_OVERFLOW_SUPPORT == STD_OFF)
    /* !LINKSTO Dem.PendingDTC.Set,1 */
    /* !LINKSTO Dem.OBDonUDS.CombinedUDSDTCStatus.PDTC.SetByFailed.NoResetOnOverflow,1 */
    EventStatusSetMask |= DEM_UDS_STATUS_PDTC;
#endif

#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF)
    if (EventStatus == DEM_EVENT_STATUS_CONFIRMED)
    {
#if (DEM_NUM_CMB_DTCS > 0U)
      boolean SetConfirmedBit = TRUE;
      if (DEM_IS_EVENT_COMBINED(EventId))
      {
        EntryExists = Dem_SearchForEntry(EventId, &EvMemEntry, &EvMemEntryIdx);
        /* for combined events, CDTC is set only for the event in combination
         * that will allocate or reallocate the event entry */
        if ( (EntryExists == TRUE) &&
             (EvMemEntry->EventId != EventId) )
        {
          SetConfirmedBit = FALSE;
        }
      }
      if (SetConfirmedBit)
#endif /* DEM_NUM_CMB_DTCS > 0U */
      {
        /* set CDTC bit */
        EventStatusSetMask |= DEM_UDS_STATUS_CDTC;

#if ( (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON) && \
      (DEM_OPCYC_OBD_DCY_USED == STD_ON) )
        SearchForEventMemoryEntry = TRUE;
#endif

#if (DEM_GET_DTCBYOCCURRENCETIME_SUPPORT == STD_ON)
        /* store event to be confirmed DTC occurrence kind */
        Dem_UpdateEventIdOccurKinds(EventId,
          DEM_FIRST_DET_CONFIRMED_DTC, DEM_MOST_REC_DET_CONFIRMED_DTC);
#endif
      }
    }
#endif /* DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF */

#if (DEM_NUM_INDICATOR_LINKS > 0U)
    if (EventWIRUpdate == TRUE)
    {
#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
      SearchForEventMemoryEntry = TRUE;
#endif /* (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) */
      /* update event status */
      EventStatusSetMask |= DEM_UDS_STATUS_WIR;
    }
#endif /* DEM_NUM_INDICATOR_LINKS */
    /* set and clear the appropriate status bits for failed/confirmed */
    DEM_CHNG_EV_ST_MASK(EventId, EventStatusSetMask, EventStatusClearMask);

#if ( (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) || \
      ( (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF) && \
        (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON) && \
        (DEM_OPCYC_OBD_DCY_USED == STD_ON) ) )
    /* Deviation TASKING-5 */
    if (SearchForEventMemoryEntry == TRUE)
    {
#if ( (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF) && \
      (DEM_NUM_CMB_DTCS > 0U) )
      if (!DEM_IS_EVENT_COMBINED(EventId))
#endif
      {
        EntryExists = Dem_SearchForEntry(EventId, &EvMemEntry, &EvMemEntryIdx);
      }

      /* search for DTC in event memory */
      /* if FailureCycleCounterThreshold is 0, event will not yet be entered
       * in event memory */
      if (EntryExists)
      {
#if ( (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) && \
      (DEM_NUM_INDICATOR_LINKS > 0U) )
        /* Note: There exists a configuration check to guarantee, that
         * DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT is set to STD_ON, if
         * DEM_EXTENDED_DATA_CAPTURE is set to DEM_TRIGGER_ON_FDC_THRESHOLD.
         * I.e. SearchForEventMemoryEntry can only be set to TRUE at one
         * of the locations above. Therefore no additional check of
         * "EventWIRUpdate" is needed here! */

        /* set WarningIndicatorRequestedSinceLastClear bit */
        DEM_SET_MASK(EvMemEntry->SI30, DEM_SI30_STATUS_WIR_SLC);
#endif /* ( (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) && \
            (DEM_NUM_INDICATOR_LINKS > 0U) ) */
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
       /* event memory entry OR immediate stored CDTC flag has been updated:
        * trigger immediate storage */
        /* !LINKSTO dsn.Dem.ImmediateStorage.StatusUpdate.CDTC,1 */
        /* !LINKSTO dsn.Dem.VCC.EventMemoryEntryChanged,4 */
        Dem_CheckForImmediateEntryStorage(
          EventId,
          EvMemEntry,
          EvMemEntryIdx,
          FALSE);
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */
      }
    }
#else
#if ( (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF) && \
      (DEM_NUM_CMB_DTCS > 0U) )
    TS_PARAM_UNUSED(SearchForEventMemoryEntry);
#endif
#endif /* ( (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) || \
            ( (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT == STD_OFF) && \
              (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON) && \
              (DEM_OPCYC_OBD_DCY_USED == STD_ON) ) ) */
  }
#if ((DEM_J1939_SUPPORT == STD_ON) && (DEM_J1939_READING_DTC_SUPPORT == STD_ON))
  if (TRUE == ReportToJ1939Dcm)
  {
      Notification->Invoke_J1939Dcm_DemTriggerOnDTCStatus_Data = EventId;
  }
#else
  TS_PARAM_UNUSED(Notification);
#endif /* ((DEM_J1939_SUPPORT == STD_ON) && (DEM_J1939_READING_DTC_SUPPORT == STD_ON)) */

#if (DEM_NUM_INDICATOR_LINKS > 0U)
  DBG_DEM_UPDATEEVENTSTATUSONQUALIFICATION_EXIT(EventId, EventStatus, EventWIRUpdate, Notification);
#else
  DBG_DEM_UPDATEEVENTSTATUSONQUALIFICATION_EXIT(EventId, EventStatus, 0U, Notification);
#endif
}

FUNC(void, DEM_CODE) Dem_ClearEventEntry(
  Dem_EventMemoryEntryPtrType EvMemEntry)
{
  /* This ENTRY debug macro is used by customers to trigger a history memory write.
   * Do not change the name or signature and ensure that all EvMemEntry data is
   * still available when this macro is expanded. */
  DBG_DEM_CLEAREVENTENTRY_ENTRY(EvMemEntry);

#if ( (DEM_USE_INT_VAL_AREA == STD_ON) || \
      (DEM_NUM_EDSEGS > 0U) || (DEM_NUM_FFSEGS > 0U) )
  {
    const Dem_SizeEntryDataType EntryDataSize =
      Dem_EvMemEntrySize(EvMemEntry->EventId, TRUE);

    if (EntryDataSize > 0U)
    {
      Dem_SizeEvMemEntryType Entry;
      const uint8 OriginIdx = Dem_GbiDTCOriginIdx(EvMemEntry->EventId);

      /* calculate entry data size behind data to delete */
      const Dem_SizeEntryDataType Width = *(Dem_EntryDataFreePos[OriginIdx]) -
        EvMemEntry->EntryDataPos - EntryDataSize;

      /* shift internal, extended and freeze frame data, to close the gap -
       * this ensures sufficient monolithic entry data capacity to store maximal
       * number of entries */
      Dem_ShiftData(Dem_IntValEntryData(EvMemEntry), EntryDataSize, Width);

      /* shift relevant event memory entry data positions */
      for (Entry = 0U; Entry < Dem_SizeEventMem[OriginIdx]; ++Entry)
      {
        if (Dem_EventMem[OriginIdx][Entry].EntryDataPos >
            EvMemEntry->EntryDataPos)
        {
          Dem_EventMem[OriginIdx][Entry].EntryDataPos -= EntryDataSize;
        }
      }

      /* recalculate free position of event memory entry data */
      *(Dem_EntryDataFreePos[OriginIdx]) -= EntryDataSize;
    }
  }
#endif /* ((DEM_USE_INT_VAL_AREA == STD_ON) ||
           (DEM_NUM_EDSEGS > 0U) || (DEM_NUM_FFSEGS > 0U)) */

#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_SINGLE)
  /* !LINKSTO dsn.Dem.OBD.Dem_ClearSingleOBDFreezeFrame.CallClearEvent,3 */
  Dem_ClearSingleOBDFreezeFrame(EvMemEntry->EventId);
#endif

  /* clear EvEntryExists status */
  Dem_SetEvEntryExists(EvMemEntry->EventId, FALSE);
  /* !LINKSTO Dem.OBD.MultipleOBDFreezeFrame.ClearOBDFF,1 */
  /* !LINKSTO Dem.OBDonUDS.CombinedUDSDTCStatus.FailureCounter.ResetByClear,1 */
  /* clear event entry information */
  EvMemEntry->EventId = DEM_EVENT_ID_INVALID;
#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U)
  EvMemEntry->RootId = DEM_EVENT_ID_INVALID;
#endif
  /* not necessary to reset EvMemEntry->OccCtr (= 0) */
  /* not necessary to reset EvMemEntry->OccOrder (= 0) */
  /* for DEM_EXTENDED_DATA_CAPTURE set to DEM_TRIGGER_ON_FDC_THRESHOLD: */
  /* - not necessary to reset EvMemEntry->SI30 (= 0) */
  /* - not necessary to reset EvMemEntry->FDC12 (= 0) */
  /* - not necessary to reset EvMemEntry->OCC1 (= 0) */
  /* - not necessary to reset EvMemEntry->OCC2 (= 0) */
  /* - not necessary to reset EvMemEntry->OCC3 (= 0) */
  /* - not necessary to reset EvMemEntry->OCC4 (= 0) */
  /* - not necessary to reset EvMemEntry->OCC6 (= 0) */
  /* - not necessary to reset EvMemEntry->OCC7 (= 0) */
  /* not necessary to reset EvMemEntry->EntryDataPos (= 0) */

  /* remove development Freeze Frame link because of defensive programming */
#if ((DEM_MAX_NUMBER_DEVFFA_ENTRY > 0U) || \
     (DEM_MAX_NUMBER_DEVFFB_ENTRY > 0U))
  {
    uint8 IdxDevFFKind;

    for (IdxDevFFKind = DEM_DEVFF_A; IdxDevFFKind <= DEM_DEVFF_B; ++IdxDevFFKind)
    {
      if (EvMemEntry->DevFFEntryIdx[IdxDevFFKind] < Dem_SizeDevFFMem[IdxDevFFKind])
      {
        Dem_DevFFEventId[IdxDevFFKind][EvMemEntry->DevFFEntryIdx[IdxDevFFKind]] =
          (Dem_EventIdType)DEM_EVENT_ID_INVALID;
        EvMemEntry->DevFFEntryIdx[IdxDevFFKind] = Dem_SizeDevFFMem[IdxDevFFKind];
      }
    }
  }
#endif /* (DEM_MAX_NUMBER_DEVFFA_ENTRY > 0U) || \
          (DEM_MAX_NUMBER_DEVFFB_ENTRY > 0U)) */

  DBG_DEM_CLEAREVENTENTRY_EXIT(EvMemEntry);
}

FUNC(Dem_SizeEntryDataType, DEM_CODE) Dem_EvMemEntrySize(
  Dem_EventIdType EventId,
  boolean         MaximalSize)
{
  Dem_SizeEntryDataType SizeOfEntryData = 0U;

#if (DEM_NUM_EDSEGS > 0U)
  /* get extended data class layout */
  CONSTP2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass =
    &Dem_EDClass[Dem_GbiEDClassIdx(EventId)];
#endif
#if (DEM_NUM_FFSEGS > 0U)
  /* get freeze frame class layout */
  CONSTP2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFClass =
    &Dem_FFClass[Dem_GbiFFClassIdx(EventId)];
  Dem_SizeEntryDataType SizeOfFF;
#endif

#if ( (DEM_NUM_J1939FFSPNS > 0U) && (DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON))
  /* get J1939 freeze frame class layout */
  CONSTP2CONST(Dem_J1939FFClassType, AUTOMATIC, DEM_CONST) J1939FFClass =
    &Dem_J1939FFClass[Dem_GbiJ1939FFClassIdx(EventId)];
  Dem_SizeEntryDataType SizeOfJ1939FF=0U;
#endif /* (DEM_NUM_J1939FFSPNS > 0U) && (DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON) */
  DBG_DEM_EVMEMENTRYSIZE_ENTRY(EventId, MaximalSize);

#if ( ( (DEM_USE_INT_VAL_AREA == STD_OFF) && \
        (DEM_NUM_EDSEGS == 0U) && (DEM_NUM_FFSEGS == 0U) ) ||\
      (DEM_NUM_EXT_DATAELEMENTS == 0U) )
  TS_PARAM_UNUSED(EventId);
#endif
#if ( (DEM_NUM_FFSEGS == 0U) || (DEM_CONSISTENT_FF_SIZE_SUPPORT != STD_ON) )
  TS_PARAM_UNUSED(MaximalSize);
#endif

#if (DEM_USE_INT_VAL_AREA == STD_ON)
  SizeOfEntryData += Dem_SizeOfIntValArea(EventId);
#endif

#if (DEM_NUM_EDSEGS > 0U)
  SizeOfEntryData += Dem_SizeOfED(EDClass);
#endif

#if (DEM_NUM_FFSEGS > 0U)
#if (DEM_CONSISTENT_FF_SIZE_SUPPORT == STD_ON)
  if (MaximalSize == TRUE)
  {
    const Dem_SizeEntryDataType FFSize[DEM_MAXNUM_ORIGINS] =
    {
      DEM_CONSISTENT_FF_SIZE_PRIMARY,
      DEM_CONSISTENT_FF_SIZE_MIRROR,
      0U, /* Permanent memory */
      DEM_CONSISTENT_FF_SIZE_SECONDARY
    };
    /* get the maximal freeze frame data size of the event */
    SizeOfFF = FFSize[Dem_GbiDTCOriginIdx(EventId)];
  }
  else
#endif /* (DEM_CONSISTENT_FF_SIZE_SUPPORT == STD_ON) */
  {
    /* get the freeze frame data size of the event */
    SizeOfFF = Dem_SizeOfFF(DEM_REGULAR_FF, FFClass);
  }

  SizeOfEntryData += SizeOfFF * Dem_GbiMaxNumFFRecs(EventId);
#endif /* (DEM_NUM_FFSEGS > 0U) */

#if ((DEM_CALIBRATION_WITHOUTEVCOMB_SUPPORT == STD_ON) && (DEM_USE_AGING == STD_ON))
  if (MaximalSize == TRUE)
  {
    if (!DEM_AGING_ALLOWED(EventId))
    {
      /* memory size for aging counter must always be included, even for
       * events without current aging */
      SizeOfEntryData += DEM_SIZE_OF_AGING_COUNTER;
    }
  }
#endif

#if ((DEM_NUM_J1939FFSPNS > 0U) && (DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON))
    SizeOfJ1939FF = Dem_SizeOfJ1939FF(J1939FFClass);
    SizeOfEntryData += SizeOfJ1939FF;
#endif /* (DEM_NUM_J1939FFSPNS > 0U) && (DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON) */

  DBG_DEM_EVMEMENTRYSIZE_EXIT(SizeOfEntryData, EventId, MaximalSize);
  return SizeOfEntryData;
}

/*------------------[interface Dem <--> NvM]--------------------------------*/

#if ( (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH) || \
      (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_TRIGGER) )
FUNC(Std_ReturnType, DEM_CODE) Dem_NvMReadCopyEventStatusBlock(
  P2CONST(void, NVM_APPL_DATA, NVM_VAR_CLEARED) NvMBuffer)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_NVMREADCOPYEVENTSTATUSBLOCK_ENTRY(NvMBuffer);

  if (Dem_InitializationState == DEM_INITIALIZED)
  {
    /* callback triggered from external source directly or
     * NvM_ReadBlock status block triggered from external source or
     * NvM module triggered it when in wrong state */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
    DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_WRONG_CONDITION);
#endif
  }
#if ( (DEM_DEV_ERROR_DETECT == STD_ON)&& \
      (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON) )
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_WRONG_CONTEXT);
  }
#endif /* (DEM_DEV_ERROR_DETECT == STD_ON) &&
          (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON) */
  else if (NvMBuffer == NULL_PTR)
  {
#if (DEM_DEV_ERROR_DETECT == STD_ON)
    DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_PARAM_POINTER);
#endif
  }
  else
  {
    /*
     * ENTER critical section to protect Dem_ClearDtcAsyncStatus and copying
     *       call-context: optional NvM(Task)
     */
    DEM_ENTER_EXCLUSIVE_AREA();

    TS_MemCpy(&Dem_NvData, NvMBuffer, sizeof(Dem_NvData));

    /*
     * LEAVE critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();

    Result = E_OK;
  }

  DBG_DEM_NVMREADCOPYEVENTSTATUSBLOCK_EXIT(Result, NvMBuffer);
  return Result;
}

FUNC(Std_ReturnType, DEM_CODE) Dem_NvMWriteCopyEventStatusBlock(
  P2VAR(void, NVM_APPL_DATA, NVM_VAR_CLEARED) NvMBuffer)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_NVMWRITECOPYEVENTSTATUSBLOCK_ENTRY(NvMBuffer);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if (Dem_InitializationState == DEM_INITIALIZED)
  {
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
    if (GetCoreID() != DEM_MASTER_INSTANCE)
    {
      /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
      DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_WRONG_CONTEXT);
    }
    else
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
    {
      if (Dem_ClearDtcAsyncStatus.EventStatusWrite != DEM_NVM_WAITING)
      {
        /* callback triggered from external source directly or
         * NvM_WriteBlock of Dem status block triggered from external source */
        /* !LINKSTO dsn.Dem.Dem_NvMWriteCopyEventStatusBlock.Det_WrongCondition,1 */
        DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_WRONG_CONDITION);
      }
#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
      else if (DEM_CLEARDTC_STATE_PROCESSING_NVRAM != Dem_ClearDtcAsyncStatus.RunState)
      {
        /* callback triggered from external source directly or
         * NvM module triggered callback when in wrong state */
        /* !LINKSTO dsn.Dem.Dem_NvMWriteCopyEventStatusBlock.Det_WrongCondition,1 */
        DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_WRONG_CONDITION);
      }
#endif
      else if (NvMBuffer == NULL_PTR)
      {
        /* !LINKSTO dsn.Dem.Dem_NvMWriteCopyEventStatusBlock.Det_ParamPointer,1 */
        DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_PARAM_POINTER);
      }
      else
      {
        /* no other Det errors to report: do nothing */
      }
    }
  }
#endif /* DEM_DEV_ERROR_DETECT */

  if (NvMBuffer != NULL_PTR)
  {
    /*
     * ENTER critical section to protect Dem_ClearDtcAsyncStatus and copying
     *       call-context: optional NvM(Task)
     */
    DEM_ENTER_EXCLUSIVE_AREA();

    Dem_ClearDtcAsyncStatus.EventStatusWrite = DEM_NVM_PENDING;
#if (DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON)
    /* !LINKSTO dsn.Dem.IntermediateNvStorageOfDTCStatus.StorageOrderId.StatusBlock,1 */
    /* update the StorageOrderId for event status block */
    Dem_GetNextStorageOrderId(Dem_NvData.StorageOrderId, DEM_STORAGEORDERID_STATUSBLOCK);
#endif
    TS_MemCpy(NvMBuffer, &Dem_NvData, sizeof(Dem_NvData));

    /*
     * LEAVE critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();

    Result = E_OK;
  }

  DBG_DEM_NVMWRITECOPYEVENTSTATUSBLOCK_EXIT(Result, NvMBuffer);
  return Result;
}

FUNC(Std_ReturnType, DEM_CODE) Dem_NvMEventStatusBlockCallback(
  uint8                 ServiceId,
  NvM_RequestResultType JobResult)
{
  Std_ReturnType Result = E_OK;

  DBG_DEM_NVMEVENTSTATUSBLOCKCALLBACK_ENTRY(ServiceId, JobResult);

  /* !LINKSTO Dem.SWS_Dem_00579,1 */
  /* retry mechanism is done by NvM, return value is ignored */
  TS_PARAM_UNUSED(JobResult);

  if ( (DEM_NVM_SID_WriteBlock == ServiceId) ||
       (DEM_NVM_SID_WriteAll == ServiceId) )
  {
#if (DEM_DEV_ERROR_DETECT == STD_ON)
    if (Dem_InitializationState == DEM_INITIALIZED)
    {
#if (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON)
      if (GetCoreID() != DEM_MASTER_INSTANCE)
      {
        /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
        DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_WRONG_CONTEXT);
      }
      else
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
      {
        if (Dem_ClearDtcAsyncStatus.EventStatusWrite != DEM_NVM_PENDING)
        {
          /* callback triggered from external source directly or
           * NvM_WriteBlock of Dem status block triggered from external source */
          DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_WRONG_CONDITION);
        }
#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
        else if (DEM_CLEARDTC_STATE_FINISHED == Dem_ClearDtcAsyncStatus.RunState)
        {
          /* NvM module triggered the callback when in wrong state */
          DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_WRONG_CONDITION);
        }
#endif
        else
        {
          /* no other Det errors to report: do nothing */
        }
      }
    }
#endif /* DEM_DEV_ERROR_DETECT */

    /*
     * ENTER critical section to protect Dem_ClearDtcAsyncStatus
     *       call-context: optional NvM(Task)
     */
    DEM_ENTER_EXCLUSIVE_AREA();

    Dem_ClearDtcAsyncStatus.EventStatusWrite = DEM_NVM_IDLE;

#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
    if (DEM_NVM_IDLE == Dem_ClearDtcAsyncStatus.EventMemWrite)
    {
      /* if one of the preceding NvM write requests failed the RunState
       * has already been advanced to FAILED. Or, if the client has performed
       * another DTC selection, the RunState is already IDLE.
       * In both cases the RunState must not be modified any more. */
      if (DEM_CLEARDTC_STATE_PROCESSING_NVRAM == Dem_ClearDtcAsyncStatus.RunState)
      {
        Dem_SetClearDTCResult(E_OK);
        Dem_ClearDtcAsyncStatus.RunState = DEM_CLEARDTC_STATE_FINISHED;
      }
      /* else: a NvM write request failed, do not change state */
    }
#endif

    /*
     * LEAVE critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();

#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_TRIGGER)
    if (Dem_ClearDtcAsyncStatus.RetriggerEventStatusWrite == TRUE)
    {
      Dem_ClearDtcAsyncStatus.RetriggerEventStatusWrite = FALSE;

      /* NvM is idle, trigger writing of the event status block */
      /* return value is not checked since Dem_ClearDTC is already finished */
      (void)Dem_TriggerNvmWriteEventStatus();
    }
#endif
  }

  DBG_DEM_NVMEVENTSTATUSBLOCKCALLBACK_EXIT(ServiceId, JobResult, Result);
  return Result;
}

#endif /* DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH/TRIGGER */

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)

FUNC(Std_ReturnType, DEM_CODE) Dem_NvMGateEntryPrimaryBlockCallback(
  uint8                 ServiceId,
  NvM_RequestResultType JobResult)
{
  DBG_DEM_NVMGATEENTRYPRIMARYBLOCKCALLBACK_ENTRY(ServiceId, JobResult);

  /* !LINKSTO Dem.SWS_Dem_00579,1 */
  /* retry mechanism is done by NvM, return value is ignored */
  TS_PARAM_UNUSED(JobResult);

  /* call generic block callback function */
  Dem_NvMGateEntryBlockCallback(
    ServiceId, (uint8)(DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U));

  DBG_DEM_NVMGATEENTRYPRIMARYBLOCKCALLBACK_EXIT(E_OK, ServiceId, JobResult);
  return E_OK;
}

#if (DEM_MAX_NUMBER_EVENT_ENTRY_SEC != 0U)
FUNC(Std_ReturnType, DEM_CODE) Dem_NvMGateEntrySecondaryBlockCallback(
  uint8                 ServiceId,
  NvM_RequestResultType JobResult)
{
  DBG_DEM_NVMGATEENTRYSECONDARYBLOCKCALLBACK_ENTRY(ServiceId, JobResult);

  /* !LINKSTO Dem.SWS_Dem_00579,1 */
  /* retry mechanism is done by NvM, return value is ignored */
  TS_PARAM_UNUSED(JobResult);

  /* call generic block callback function */
  Dem_NvMGateEntryBlockCallback(
    ServiceId, (uint8)(DEM_DTC_ORIGIN_SECONDARY_MEMORY - 1U));

  DBG_DEM_NVMGATEENTRYSECONDARYBLOCKCALLBACK_EXIT(E_OK, ServiceId, JobResult);
  return E_OK;
}
#endif /* (DEM_MAX_NUMBER_EVENT_ENTRY_SEC != 0U) */

#if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR != 0U)
FUNC(Std_ReturnType, DEM_CODE) Dem_NvMGateEntryMirrorBlockCallback(
  uint8                 ServiceId,
  NvM_RequestResultType JobResult)
{
  DBG_DEM_NVMGATEENTRYMIRRORBLOCKCALLBACK_ENTRY(ServiceId, JobResult);

  /* !LINKSTO Dem.SWS_Dem_00579,1 */
  /* retry mechanism is done by NvM, return value is ignored */
  TS_PARAM_UNUSED(JobResult);

  /* call generic block callback function */
  Dem_NvMGateEntryBlockCallback(
    ServiceId, (uint8)(DEM_DTC_ORIGIN_MIRROR_MEMORY - 1U));

  DBG_DEM_NVMGATEENTRYMIRRORBLOCKCALLBACK_EXIT(E_OK, ServiceId, JobResult);
  return E_OK;
}
#endif /* (DEM_MAX_NUMBER_EVENT_ENTRY_MIR != 0U) */
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */

#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)
FUNC(Std_ReturnType, DEM_CODE) Dem_NvMWriteFinishedPermanentMemory(
  uint8                 ServiceId,
  NvM_RequestResultType JobResult)
{
  Dem_SizeEvMemEntryType EntryIdx;
  Std_ReturnType Result = E_OK;

  DBG_DEM_NVMWRITEFINISHEDPERMANENTMEMORY_ENTRY(ServiceId, JobResult);
  TS_PARAM_UNUSED(ServiceId);

  DEM_PRECONDITION_ASSERT( (Dem_InitializationState != DEM_UNINITIALIZED),
    DEM_INTERNAL_API_ID);

#if ( (DEM_DEV_ERROR_DETECT == STD_ON) && \
       (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON) )
  if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_WRONG_CONTEXT);
    Result = E_NOT_OK;
  }
  else
#endif /*(DEM_DEV_ERROR_DETECT == STD_ON) && \
         (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON) */
  {
    /* check whether writing job was successful */
    if (JobResult == NVM_REQ_OK)
    {
      /*
      * ENTER critical section to protect the event memory
      *       call-context: NvM (Task)
      */
      DEM_ENTER_EXCLUSIVE_AREA();

      /* loop trough permanent memory to find which entries are now stored */
      for (EntryIdx = 0U; EntryIdx < DEM_MAX_NUMBER_EVENT_ENTRY_PER; EntryIdx++)
      {
        /* !LINKSTO Dem_OBD_0055,1 */
        if (Dem_EventMemoryPermanentNonVolatileStored[EntryIdx] ==
            DEM_PERMANENT_MEMORY_STORING_IN_PROCESS)
        {
          Dem_EventMemoryPermanentNonVolatileStored[EntryIdx] =
              DEM_PERMANENT_MEMORY_NV_STORED;
        }
      }

      /*
      * LEAVE critical section
      */
      DEM_EXIT_EXCLUSIVE_AREA();
    }
    else
    {
      /* !LINKSTO Dem_OBD_0077,2 */
      Dem_EventMemoryPermanentUpdated = TRUE;
    }
  }
  DBG_DEM_NVMWRITEFINISHEDPERMANENTMEMORY_EXIT(Result, ServiceId, JobResult);
  return Result;
}

FUNC(Std_ReturnType, DEM_CODE) Dem_NvMReadCopyPermanentMemory(
  P2CONST(void, NVM_APPL_DATA, NVM_VAR_CLEARED) NvMBuffer)
{
  Std_ReturnType Result = E_NOT_OK;
  CONSTP2CONST(uint8, AUTOMATIC, DEM_APPL_DATA) BufferPtr = NvMBuffer;
  uint16 BufferIndex = 0U;
  uint8 EntryIdx;

  DBG_DEM_NVMREADCOPYPERMANENTMEMORY_ENTRY(NvMBuffer);

  if (Dem_InitializationState == DEM_INITIALIZED)
  {
    /* callback triggered from external source directly or
     * NvM_ReadBlock permanent block triggered from external source or
     * NvM module triggered it when in wrong state */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
    DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_WRONG_CONDITION);
#endif
  }
#if ( (DEM_DEV_ERROR_DETECT == STD_ON) && \
      (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON) )
  else if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_WRONG_CONTEXT);
  }
#endif /* DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON */
  else if (NvMBuffer == NULL_PTR)
  {
#if (DEM_DEV_ERROR_DETECT == STD_ON)
    DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_PARAM_POINTER);
#endif /* DEM_DEV_ERROR_DETECT == STD_ON */
  }
  else
  {
    /*
     * ENTER critical section to protect the event memory
     *       call-context: NvM (Task)
     */
    DEM_ENTER_EXCLUSIVE_AREA();

    /* copy data element values for all its size */
    for (EntryIdx = 0U; EntryIdx < DEM_MAX_NUMBER_EVENT_ENTRY_PER; EntryIdx++)
    {
      /* !LINKSTO Dem_OBD_0056,2 */
      Dem_PermanentMemoryEntryType Entry;

      Entry = ((Dem_PermanentMemoryEntryType)BufferPtr[BufferIndex + 1U] << 8U);
      Entry += BufferPtr[BufferIndex];

      BufferIndex += 2U;

      Dem_EventMemoryPermanent[EntryIdx] = Entry;
    }

    Result = E_OK;

    /*
     * LEAVE critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();
  }

  DBG_DEM_NVMREADCOPYPERMANENTMEMORY_EXIT(Result, NvMBuffer);
  /* !LINKSTO Dem_OBD_0067,2 */
  return Result;
}

FUNC(Std_ReturnType, DEM_CODE) Dem_NvMWriteCopyPermanentMemory(
  P2VAR(void, NVM_APPL_DATA, NVM_VAR_CLEARED) NvMBuffer)
{
  Std_ReturnType Result = E_OK;

  DBG_DEM_NVMWRITECOPYPERMANENTMEMORY_ENTRY(NvMBuffer);

  DEM_PRECONDITION_ASSERT( (Dem_InitializationState != DEM_UNINITIALIZED),
    DEM_INTERNAL_API_ID);

#if ( (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON) &&\
      (DEM_DEV_ERROR_DETECT == STD_ON) )
  if (GetCoreID() != DEM_MASTER_INSTANCE)
  {
    /* !LINKSTO Dem.BSWDistribution.ContextCheckForNonDistributedFunctionalities,1 */
    DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_WRONG_CONTEXT);
    Result = E_NOT_OK;
  }
  else
#endif /* (DEM_BSW_DISTRIBUTION_FOR_BSW_EVENT_REPORTING == STD_ON) &&\
          (DEM_DEV_ERROR_DETECT == STD_ON) */
  {
#if (DEM_DEV_ERROR_DETECT == STD_ON)
    if (NvMBuffer == NULL_PTR)
    {
      DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_PARAM_POINTER);

      Result = E_NOT_OK;
    }
    else
#endif /* DEM_DEV_ERROR_DETECT == STD_ON */
    {
      /* Deviation MISRAC2012-1 */
      CONSTP2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) BufferPtr = (uint8 *)NvMBuffer;
      uint16 BufferIndex = 0U;
      uint8 EntryIdx;

      /*
       * ENTER critical section to protect the event memory
       *       call-context: NvM (Task)
       */
      DEM_ENTER_EXCLUSIVE_AREA();

      /* copy data element values for all its size */
      for (EntryIdx = 0U; EntryIdx < DEM_MAX_NUMBER_EVENT_ENTRY_PER; EntryIdx++)
      {
        /* !LINKSTO Dem_OBD_0051,2 */
        const Dem_PermanentMemoryEntryType Entry =
          Dem_EventMemoryPermanent[EntryIdx];

        BufferPtr[BufferIndex]      = (uint8)(Entry);
        BufferPtr[BufferIndex + 1U] = (uint8)(Entry >> 8U);

        BufferIndex += 2U;

        if (DEM_GET_PERMANENT_MEMORY_EVENT_ID(Entry) != DEM_EVENT_ID_INVALID)
        {
          /* !LINKSTO Dem_OBD_0065,2 */
          Dem_EventMemoryPermanentNonVolatileStored[EntryIdx] =
              DEM_PERMANENT_MEMORY_STORING_IN_PROCESS;
        }
      }

      /*
       * LEAVE critical section
       */
      DEM_EXIT_EXCLUSIVE_AREA();

      /* !LINKSTO Dem_OBD_0074,1 */
      Dem_EventMemoryPermanentUpdated = FALSE;
    }
  }

  DBG_DEM_NVMWRITECOPYPERMANENTMEMORY_EXIT(Result, NvMBuffer);
  /* !LINKSTO Dem_OBD_0052,2 */
  return Result;
}
#endif /* DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U */

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
STATIC FUNC(void, DEM_CODE) Dem_NvMGateEntryBlockCallback(
  uint8 ServiceId,
  uint8 OriginIdx)
{
  DBG_DEM_NVMGATEENTRYBLOCKCALLBACK_ENTRY(ServiceId, OriginIdx);

  /* Dem must not add module-initialized DET-check as NvM-block callback must
     be allowed in general */

  if (ServiceId == DEM_NVM_SID_WriteBlock)
  {
    boolean PerformStoreImmediately;

    /* 1st step: prepare the gate entry */
    /* check which event of the given origin (for which this job end
     * notification was called) shall be stored next */
    PerformStoreImmediately = Dem_StoreImmediatelyNext(OriginIdx);

    /* 2nd step: trigger the requests to the NvM module for next entry
     * always called outside the critical section */
    if (TRUE == PerformStoreImmediately)
    {
      /* immediately trigger writing of next block (faster writes) */
      /* can be skipped here in case delays of up to one main function period
       * are acceptable and/or made dependent on ASYNC_ONLY parameter */
      Dem_CheckForTriggerNvmWriteGateEntry();
    }
  }

  DBG_DEM_NVMGATEENTRYBLOCKCALLBACK_EXIT(ServiceId, OriginIdx);
}
#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */

#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_SINGLE)
FUNC(void, DEM_CODE) Dem_ClearSingleOBDFreezeFrame(Dem_EventIdType EventId)
{
  DBG_DEM_CLEARSINGLEOBDFREEZEFRAME_ENTRY(EventId);

  /* check whether given EventId is stored in OBD event memory entry */
  /* !LINKSTO dsn.Dem.OBD.Dem_ClearSingleOBDFreezeFrame.EventID,1 */
  if (EventId == DEM_OBDFF_STORED_EVENT_ID)
  {
    /* !LINKSTO dsn.Dem.OBD.Dem_ClearSingleOBDFreezeFrame.EventIdInvalid,1 */
    /* clearing OBD freeze frame by setting stored EventId to invalid */
    DEM_OBDFF_STORED_EVENT_ID = DEM_EVENT_ID_INVALID;
  }/* otherwise leave OBD freeze frame as it is */

  DBG_DEM_CLEARSINGLEOBDFREEZEFRAME_EXIT(EventId);
}
#endif /* (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_SINGLE */

/*------------------[Dem_InternalSetDTCSuppression]-------------------------*/

#if (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION)
FUNC(Std_ReturnType, DEM_CODE) Dem_InternalSetDTCSuppression(
  uint32            DTC,
  Dem_DTCFormatType DTCFormat,
  boolean           SuppressionStatus)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_INTERNALSETDTCSUPPRESSION_ENTRY(DTC, DTCFormat, SuppressionStatus);

  /* !LINKSTO Dem.SWS_Dem_01315,1 */
  switch (DTCFormat)
  {
    case DEM_DTC_FORMAT_OBD:
#if (DEM_OBD_CLASSIC_SUPPORT)
#if (DEM_OBD_VARIANT_SELECTABLE == STD_ON)
      if (DEM_GET_OBD_VARIANT() == DEM_OBD_VARIANT_OBD_CLASSIC)
#endif
      {
#if (DEM_IDENTICAL_OBD_DTC_AVAILABLE == STD_ON)
        Result = Dem_InternalCheckAndSetObdDTCSuppression(DTC,
                                                          SuppressionStatus);
#else
        Result = Dem_InternalCheckAndSetDTCSuppression(DTC,
                                                       Dem_InternalGetObdDTC,
                                                       Dem_OBDDTCSuppression,
                                                       SuppressionStatus);
#endif /* (DEM_IDENTICAL_OBD_DTC_AVAILABLE == STD_ON) */
      }
#endif /* (DEM_OBD_CLASSIC_SUPPORT) */
      break;

    case DEM_DTC_FORMAT_UDS:
      Result = Dem_InternalCheckAndSetDTCSuppression(DTC,
                                                     Dem_InternalGetUdsDTC,
                                                     Dem_UDSDTCSuppression,
                                                     SuppressionStatus);

      break;

    case DEM_DTC_FORMAT_OBD_3BYTE:
#if (DEM_OBDONUDS_SUPPORT && (DEM_OBD_DTCVALUE3BYTE_SUPPORT == STD_ON))
#if (DEM_OBD_VARIANT_SELECTABLE == STD_ON)
      if (DEM_GET_OBD_VARIANT() == DEM_OBD_VARIANT_OBDONUDS)
#endif
      {
        Result = Dem_InternalCheckAndSetDTCSuppression(DTC,
                                                       Dem_InternalGetObdDTCValue3Byte,
                                                       Dem_OBDDTCSuppression,
                                                       SuppressionStatus);
      }
#endif  /* (DEM_OBDONUDS_SUPPORT && (DEM_OBD_DTCVALUE3BYTE_SUPPORT == STD_ON)) */
      break;

    case DEM_DTC_FORMAT_J1939:
#if (DEM_J1939_SUPPORT == STD_ON)
      Result = Dem_InternalCheckAndSetDTCSuppression(DTC,
                                                     Dem_InternalGetJ1939DTC,
                                                     Dem_J1939DTCSuppression,
                                                     SuppressionStatus);
#endif
      break;

  /* CHECK: NOPARSE */
  /* should never be reached */
  default:
    DEM_UNREACHABLE_CODE_ASSERT(DEM_INTERNAL_API_ID);
    break;
  /* CHECK: PARSE */
  }

  DBG_DEM_INTERNALSETDTCSUPPRESSION_EXIT(Result, DTC, DTCFormat, SuppressionStatus);

  return Result;
}
#endif /* (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION) */

/*------------------[Dem_InternalGetIndicatorStatus]-------------------------*/
#if (DEM_NUM_INDICATOR_LINKS > 0U)

FUNC(Dem_IndicatorStatusType, DEM_CODE) Dem_InternalGetIndicatorStatus(
  Dem_IndicatorIdType IndicatorId,
  boolean NeedOnlyOnOffStatus)
{
  Dem_IndicatorStatusType Status = DEM_INDICATOR_OFF;
#if (DEM_J1939_SUPPORT == STD_ON)
  Dem_IndicatorStatusType MinStatus = DEM_INDICATOR_FAST_FLASH;
#else
  Dem_IndicatorStatusType MinStatus = DEM_INDICATOR_BLINK_CONT;
#endif

  DBG_DEM_INTERNALGETINDICATORSTATUS_ENTER(IndicatorId);

  if (NeedOnlyOnOffStatus == TRUE)
  {
    MinStatus = DEM_INDICATOR_CONTINUOUS;
  }

#if (DEM_CALIBRATION_SUPPORT == STD_ON)
  {
    Dem_EventIdType EventId;

    for (EventId = 1U; EventId <= DEM_MAX_EVENTID; EventId++)
    {
#if (DEM_EVENT_DISABLING_SUPPORT == STD_ON)
      if (Dem_GbiEvAvailable(EventId) == FALSE)
      {
        /* event is disabled so the getting of status shall be skipped */
      }
      else
#endif
      {
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

            if ( (IndicatorClass->IndicatorId == IndicatorId) &&
                 (IndicatorClass->Enabled == TRUE) )
            {
              if ( DEM_IS_BIT_SET_IN_ARRAY(
                     DEM_INDICATOR_CYC_COUNTER_WIR_STATUS[IndicatorClass->IndicatorId],
                     EventId) )
              {
                Dem_IndicatorStatusType Behaviour = IndicatorClass->Behaviour;
                if (Status == DEM_INDICATOR_OFF)
                {
                  /* set initial behaviour */
                  Status = Behaviour;
                }
                else
                {
                  if (Status != Behaviour)
                  {
                    if ((Status < DEM_INDICATOR_BLINK_CONT) && (Behaviour <= DEM_INDICATOR_BLINK_CONT))
                    {
                      /* as different behaviours are requested, SW-C is responsible
                       * for behaviour selection */
                      Status = DEM_INDICATOR_BLINK_CONT;
                    }
                    else
                    {
                      if (Behaviour > Status)
                      {
                        Status = Behaviour;
                      }
                    }
                  }
                }
                if (Status >= MinStatus)
                {
                  break;
                }
              }
              /* else: no linked event requests its warning indicator
               * -> status remains DEM_INDICATOR_OFF */
              /* !LINKSTO Dem.Dem_GetIndicatorStatus.Unlinked,2 */
            }
          }
        }
      }
    }
  }
/* calibration is disabled and event availability is not considered */
#else
  {
    P2CONST(Dem_IndicatorLinkType, AUTOMATIC, DEM_CONST) IndicatorLink;
    Dem_IndicatorIdxType LinkIdx;

    /* point to first indicator link of according data structures */
    IndicatorLink = &Dem_IndicatorLink[Dem_IndicatorDesc[IndicatorId].StartIdx];

    for (LinkIdx = 0U; LinkIdx < Dem_IndicatorDesc[IndicatorId].Number; ++LinkIdx)
    {
      const Dem_CounterDataIdxType CounterDataIdx =
         LinkIdx + Dem_IndicatorDesc[IndicatorId].StartIdx;

      if ( DEM_IS_BIT_SET_IN_ARRAY(
             DEM_INDICATOR_CYC_COUNTER_WIR_STATUS[DEM_INDICATOR_DEFAULT_COUNTER],
             CounterDataIdx)
         )
      {
        Dem_IndicatorStatusType Behaviour = IndicatorLink[LinkIdx].Behaviour;
        if (Status == DEM_INDICATOR_OFF)
        {
          /* set initial behaviour */
          Status = Behaviour;
        }
        else
        {
          if (Status != Behaviour)
          {
            if ((Status < DEM_INDICATOR_BLINK_CONT) && (Behaviour <= DEM_INDICATOR_BLINK_CONT))
            {
              /* as different behaviours are requested, SW-C is responsible
               * for behaviour selection */
              Status = DEM_INDICATOR_BLINK_CONT;
            }
            else
            {
              if (Behaviour > Status)
              {
                Status = Behaviour;
              }
            }

          }
        }
        if (Status >= MinStatus)
        {
          break;
        }
      }
      /* else: no linked event requests its warning indicator
       * -> status remains DEM_INDICATOR_OFF */
      /* !LINKSTO Dem.Dem_GetIndicatorStatus.Unlinked,2 */
    }
  }
#endif /* (DEM_CALIBRATION_SUPPORT == STD_ON) */

  DBG_DEM_INTERNALGETINDICATORSTATUS_EXIT(IndicatorId, Status);
  /* return indicator status value */
  return Status;
}
#endif /* (DEM_NUM_INDICATOR_LINKS > 0U) */

#if (DEM_NUM_CMB_DTCS > 0U)
FUNC(Dem_EventIdType, DEM_CODE) Dem_GetMasterEventId(Dem_EventIdType EventId)
{
  Dem_EventIdType Result = EventId;
  Dem_DTCConfIdxType ConfIdx;

  DBG_DEM_GETMASTEREVENTID_ENTRY(EventId);

  ConfIdx = DEM_GBI_DTCCONFIDX(EventId);

  if (ConfIdx < DEM_NUM_CMB_DTCS)
  {
    Result = Dem_CmbDTCEvents[Dem_CmbDTCEvLnk[ConfIdx]];
  }

  DBG_DEM_GETMASTEREVENTID_EXIT(Result, EventId);

  return Result;
}

FUNC(Dem_DTCStatusMaskType, DEM_CODE) Dem_GetCmbDtcStatus(Dem_EventIdType EventId)
{
  Dem_DTCStatusMaskType DTCStatus = DEM_DTC_STATUS_MASKS[(EventId)];
  Dem_DTCConfIdxType ConfIdx;

  DBG_DEM_GETCMBDTCSTATUS_ENTRY(EventId);

  ConfIdx = DEM_GBI_DTCCONFIDX(EventId);

  if (ConfIdx < DEM_NUM_CMB_DTCS)
  {
    DTCStatus = Dem_CmbDTCStatus[ConfIdx];
  }

  DBG_DEM_GETCMBDTCSTATUS_EXIT(DTCStatus, EventId);

  return DTCStatus;
}

FUNC(boolean, DEM_CODE) Dem_CheckForPassiveEvent(Dem_EventIdType EventId)
{
  boolean Result = FALSE;
  Dem_DTCConfIdxType ConfIdx;

  DBG_DEM_CHECKFORPASSIVEEVENT_ENTRY(EventId);

  ConfIdx = DEM_GBI_DTCCONFIDX(EventId);

  if (ConfIdx < DEM_NUM_CMB_DTCS)
  {
    if(!DEM_IS_CMB_ST_BIT_SET_IN_DTC(ConfIdx, DEM_UDS_STATUS_TF))
    {
      Result = TRUE;
    }
  }
  else
  {
    if(!DEM_IS_EV_ST_BIT_TF_SET(EventId))
    {
      Result = TRUE;
    }
  }

  DBG_DEM_CHECKFORPASSIVEEVENT_EXIT(Result, EventId);

  return Result;
}
#endif /* (DEM_NUM_CMB_DTCS > 0U) */

/*------------------[Interface Dem <--> SW-Components / BSW modules]--------*/

#if (DEM_USE_CB_INIT_MONITOR == STD_ON)
FUNC(void, DEM_CODE) Dem_CbInitMonitorForEvent(
  Dem_EventIdType           EventId,
  Dem_InitMonitorReasonType InitMonitorReason)
{
  DBG_DEM_CBINITMONITORFOREVENT_ENTRY(EventId, InitMonitorReason);

  if ((Dem_CbProperty[EventId] & DEM_GEN_CB_INIT_MONITOR) != 0U)
  {
    Dem_CbIndexType CbIdx = 0U;

    while ( (CbIdx < DEM_LOOKUP_TABLE_INIT_MONITOR_SIZE) &&
            (Dem_CbLookupTableInitMonitor[CbIdx] != EventId) )
    {
      CbIdx++;
    }

    DEM_PRECONDITION_ASSERT(
      (CbIdx < (Dem_CbIndexType)DEM_LOOKUP_TABLE_INIT_MONITOR_SIZE),
      DEM_INTERNAL_API_ID);

    /* !LINKSTO Dem.ASR40.SWS_Dem_00376_Implicit1,1 */
    /* return value is ignored
     * same index in both arrays */
    (void)Dem_CbFuncPtrInitMonitor[CbIdx](InitMonitorReason);
  }

  DBG_DEM_CBINITMONITORFOREVENT_EXIT(EventId, InitMonitorReason);
}
#endif /* (DEM_USE_CB_INIT_MONITOR == STD_ON) */

#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
#if ( (DEM_CB_TABLE_TRIG_ON_DTCST_SIZE > 0U) || \
      (DEM_TRIGGER_DCM_REPORTS == STD_ON) )
STATIC FUNC(void, DEM_CODE) Dem_CbTriggerOnDTCStatus(
  Dem_EventIdType       EventId,
  Dem_DTCStatusMaskType OldDTCStatusMask,
  Dem_DTCStatusMaskType NewDTCStatusMask)
{
  uint32 DTC;

  DBG_DEM_CBTRIGGERONDTCSTATUS_ENTRY(EventId, OldDTCStatusMask, NewDTCStatusMask);

  /* get the DTC mapped to event Id */
  DTC = Dem_GetVisibleUdsDTC(EventId);

  /* check if DTC is available for this event */
  if (DTC != DEM_NO_DTC)
  {
#if (DEM_CB_TABLE_TRIG_ON_DTCST_SIZE > 0U)
    Dem_CbIndexType CbIdx;
    /* Deviation TASKING-1 */
    for (CbIdx = 0U; CbIdx < DEM_CB_TABLE_TRIG_ON_DTCST_SIZE; CbIdx++)
    {
      /* !LINKSTO Dem.ASR40.SWS_Dem_00284_Implicit1,1 */
      /* return value is ignored
       * same prototype for C/RTE */
      (void)Dem_CbFuncPtrTrigOnDTCSt[CbIdx](DTC, OldDTCStatusMask, NewDTCStatusMask);
    }
#endif

    /* if trigger on DTC status callback functionality is enabled for Dcm */
#if (DEM_TRIGGER_DCM_REPORTS == STD_ON)
    (void)Dcm_DemTriggerOnDTCStatus(DTC, OldDTCStatusMask, NewDTCStatusMask);
#endif
  }

  DBG_DEM_CBTRIGGERONDTCSTATUS_EXIT(EventId, OldDTCStatusMask, NewDTCStatusMask);
}
#endif /* (DEM_CB_TABLE_TRIG_ON_DTCST_SIZE > 0U) || \
          (DEM_TRIGGER_DCM_REPORTS == STD_ON) */

FUNC(void, DEM_CODE) Dem_CbTriggerOnEventStatus(
  Dem_EventIdType       EventId,
  Dem_DTCStatusMaskType OldDTCStatusMask,
  Dem_DTCStatusMaskType NewDTCStatusMask)
{
#if ( (DEM_RTE_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U) || \
      (DEM_C_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U) )
  uint16 StartIdx = 0U;
  uint16 LastIdx = 0U;
  uint16_least LookUpIdx;
#endif

#if (DEM_C_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U)
  Dem_CbIndexType CbIdx;
#endif

  DBG_DEM_CBTRIGGERONEVENTSTATUS_ENTRY(EventId, OldDTCStatusMask, NewDTCStatusMask);

#if (DEM_SEM_SUPPORT == STD_ON)
  /* !LINKSTO dsn.Dem.Sem.SuppressCallbacks,1 */
  if (!DEM_IS_SECURITY_EVENT(EventId))
#endif
  {
#if (DEM_RTE_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U)
    if ((Dem_CbProperty[EventId] & DEM_RTE_CB_TRIG_ON_EVST) != 0U)
    {
      Dem_GetRteCallbackIndex(
        EventId,
        Dem_RteLookupTableTrigOnEvSt,
        DEM_RTE_LOOKUP_TABLE_TRIG_ON_EVST_SIZE,
        &StartIdx,
        &LastIdx);

      for (LookUpIdx = StartIdx; LookUpIdx <= LastIdx; LookUpIdx++)
      {
        /* !LINKSTO Dem.ASR40.SWS_Dem_00016_Implicit1,1 */
        /* !LINKSTO Dem.SWS_Dem_00016,1 */
        /* return value is ignored */
        (void)Dem_RteFuncPtrTrigOnEvSt[LookUpIdx](
          OldDTCStatusMask,
          NewDTCStatusMask);
      }
    }

    /* trigger global port GeneralCallbackEventStatusChange/GeneralCallbackEventUdsStatusChanged
     * (Dem.ASR40.SWS_Dem_00616, Dem.SWS_Dem_00616) */
#if DEM_DEFAULT_ASR_SERVICE_API == DEM_SERVICE_API_ASR2011
    (void)Rte_Call_GeneralCBStatusEvt_GeneralCallbackEventUdsStatusChanged(EventId,
      OldDTCStatusMask, NewDTCStatusMask);
#else
    (void)Rte_Call_GeneralCBStatusEvt_EventStatusChanged(EventId,
      OldDTCStatusMask, NewDTCStatusMask);
#endif
#endif /* (DEM_RTE_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U) */

#if (DEM_C_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U)
    if ((Dem_CbProperty[EventId] & DEM_C_CB_TRIG_ON_EVST) != 0U)
    {
      Dem_GetCallbackIndex(
        EventId,
        Dem_CbLookupTableTrigOnEvSt,
        DEM_C_LOOKUP_TABLE_TRIG_ON_EVST_SIZE,
        &StartIdx,
        &LastIdx);

      for (LookUpIdx = StartIdx; LookUpIdx <= LastIdx; LookUpIdx++)
      {
        CbIdx = Dem_CbLookupTableTrigOnEvSt[LookUpIdx].CallbackIdx;
        /* !LINKSTO Dem.ASR40.SWS_Dem_00016_Implicit1,1 */
        /* return value is ignored */
        Dem_CbFuncPtrTrigOnEvSt[CbIdx](
          EventId,
          OldDTCStatusMask,
          NewDTCStatusMask);
      }
    }
#endif /* (DEM_C_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U) */

    /* if trigger on event status callback functionality is enabled for FiM */
#if (DEM_TRIGGER_FIM_REPORTS == STD_ON)
    FiM_DemTriggerOnEventStatus(EventId, OldDTCStatusMask, NewDTCStatusMask);
#endif

#if (DEM_NUM_CMB_DTCS > 0U)
    /* check that event is not involved in event combination. */
    /* if it is, the DTC relevant callbacks will be triggered when cmb status is updated.*/
    if (!DEM_IS_EVENT_COMBINED(EventId))
#endif
    {
#if ( (DEM_CB_TABLE_TRIG_ON_DTCST_SIZE > 0U) || \
        (DEM_TRIGGER_DCM_REPORTS == STD_ON) )
      Dem_CbTriggerOnDTCStatus(EventId, OldDTCStatusMask, NewDTCStatusMask);
#endif
    }
  }
  DBG_DEM_CBTRIGGERONEVENTSTATUS_EXIT(EventId, OldDTCStatusMask, NewDTCStatusMask);
}
#endif /* (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) */

#if (DEM_NUM_CMB_DTCS > 0U)
FUNC(void, DEM_CODE) Dem_InternalCheckOnCmbDTCStatusChange(
  Dem_EventIdType       EventId,
  Dem_DTCStatusMaskType OldDTCStatusMask,
  Dem_DTCStatusMaskType NewDTCStatusMask)
{
  DBG_DEM_INTERNALCHECKONCMBDTCSTATUSCHANGE_ENTRY(EventId,
                                                  OldDTCStatusMask,
                                                  NewDTCStatusMask);

#if ( (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON) && \
      ( (DEM_CB_TABLE_TRIG_ON_DTCST_SIZE > 0U) || \
        (DEM_TRIGGER_DCM_REPORTS == STD_ON) ) )
  if (DEM_IS_EVENT_COMBINED(EventId))
  {
    /* check if the combined DTC status has changed and if module
     * is initialized, as the callbacks for DTC status must be
     * triggered after Init and never during Shutdown */
    if ( (OldDTCStatusMask != NewDTCStatusMask) &&
         (Dem_InitializationState == DEM_INITIALIZED) )
    {
      /* !LINKSTO Dem.SWS_Dem_00284,1 */
      /* !LINKSTO Dem.SWS_Dem_00828,1 */
      /* trigger relevant callbacks for DTC Status change */
      Dem_CbTriggerOnDTCStatus(EventId, OldDTCStatusMask, NewDTCStatusMask);
    }
    else
    {
      TS_PARAM_UNUSED(EventId);
    }
  }
#else
  TS_PARAM_UNUSED(EventId);
  TS_PARAM_UNUSED(OldDTCStatusMask);
  TS_PARAM_UNUSED(NewDTCStatusMask);

#endif

  DBG_DEM_INTERNALCHECKONCMBDTCSTATUSCHANGE_EXIT(EventId,
                                                 OldDTCStatusMask,
                                                 NewDTCStatusMask);
}
#endif /* (DEM_NUM_CMB_DTCS > 0U) */

#if (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON)
FUNC(void, DEM_CODE) Dem_CbTriggerOnEventData(Dem_EventIdType EventId)
{
  DBG_DEM_CBTRIGGERONEVENTDATA_ENTRY(EventId);

#if (DEM_RTE_CB_TABLE_TRIG_ON_EVDAT_SIZE > 0U)
  if ((Dem_CbProperty[EventId] & DEM_RTE_CB_TRIG_ON_EVDAT) != 0U)
  {
    Dem_CbIndexType RteCbIdx = 0U;

    while ( (RteCbIdx < DEM_RTE_LOOKUP_TABLE_TRIG_ON_EVDAT_SIZE) &&
            (Dem_RteLookupTableTrigOnEvDat[RteCbIdx] != EventId) )
    {
      RteCbIdx++;
    }

    DEM_PRECONDITION_ASSERT((RteCbIdx < DEM_RTE_LOOKUP_TABLE_TRIG_ON_EVDAT_SIZE),
                            DEM_INTERNAL_API_ID);

    /* !LINKSTO Dem.ASR40.SWS_Dem_00474_Implicit1,1 */
    /* return value is ignored
     * same index in both arrays */
    (void)Dem_RteFuncPtrTrigOnEvDat[RteCbIdx]();
  }

  /* trigger global port GeneralCallbackEventDataChanged (Dem.ASR40.SWS_Dem_00619) */
  (void)Rte_Call_GeneralCBDataEvt_EventDataChanged(EventId);
#endif /* (DEM_RTE_CB_TABLE_TRIG_ON_EVDAT_SIZE > 0U) */

#if (DEM_C_CB_TABLE_TRIG_ON_EVDAT_SIZE > 0U)
  if ((Dem_CbProperty[EventId] & DEM_C_CB_TRIG_ON_EVDAT) != 0U)
  {
    Dem_CbIndexType CCbIdx = 0U;

    while ( (CCbIdx < DEM_C_LOOKUP_TABLE_TRIG_ON_EVDAT_SIZE) &&
            (Dem_CbLookupTableTrigOnEvDat[CCbIdx].EventId != EventId) )
    {
      CCbIdx++;
    }

    DEM_PRECONDITION_ASSERT((CCbIdx < DEM_C_LOOKUP_TABLE_TRIG_ON_EVDAT_SIZE),
                            DEM_INTERNAL_API_ID);

    /* get index/link of callback function pointer */
    CCbIdx = Dem_CbLookupTableTrigOnEvDat[CCbIdx].CallbackIdx;
    /* !LINKSTO Dem.ASR40.SWS_Dem_00474_Implicit1,1 */
    /* return value is ignored */
    (void)Dem_CbFuncPtrTrigOnEvDat[CCbIdx](EventId);
  }
#endif /* (DEM_C_CB_TABLE_TRIG_ON_EVDAT_SIZE > 0U) */

  DBG_DEM_CBTRIGGERONEVENTDATA_EXIT(EventId);
}
#endif /* (DEM_USE_CB_TRIG_ON_EVDAT == STD_ON) */


#if ( (DEM_SEM_SUPPORT == STD_ON) && (DEM_NUM_SEV_WITH_SYNC_STORE_PROC_CB > 0) )
FUNC(Dem_CbFuncPtrSevSyncStoreProcType, DEM_CODE) Dem_GetSevSyncStoreProcCb(
  Dem_EventIdType EventId)
{
  Dem_CbIndexType CCbIdx = 0U;
  Dem_CbFuncPtrSevSyncStoreProcType RetVal = NULL_PTR;
  DBG_DEM_GETSEVSYNCSTOREPROCCB_ENTRY(EventId);

  while ( (CCbIdx < DEM_NUM_SEV_WITH_SYNC_STORE_PROC_CB) &&
          (Dem_SevWithSyncStoreProcCb[CCbIdx] != EventId) )
  {
    CCbIdx++;
  }

  if (CCbIdx < DEM_NUM_SEV_WITH_SYNC_STORE_PROC_CB)
  {
    /* get callback function pointer */
    RetVal = Dem_CbFncPtrSevSyncStoreProc[CCbIdx];
  }

  DBG_DEM_GETSEVSYNCSTOREPROCCB_EXIT(RetVal, EventId);
  return RetVal;
}
#endif /* ( (DEM_SEM_SUPPORT == STD_ON) && (DEM_NUM_SEV_WITH_SYNC_STORE_PROC_CB > 0) ) */


#if (DEM_USE_CB_GET_FDC == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_CbGetFaultDetectionCounter(
  Dem_EventIdType                        EventId,
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FDC)
{
  Std_ReturnType RetVal = E_NOT_OK;

  Dem_CbIndexType CbIdx;

  DBG_DEM_CBGETFAULTDETECTIONCOUNTER_ENTRY(EventId, FDC);

  if ((Dem_CbProperty[EventId] & DEM_GEN_CB_FAULT_DETECTION_CTR) != 0U)
  {
    CbIdx = 0U;

    while ( (CbIdx < DEM_LOOKUP_TABLE_GET_FDC_SIZE) &&
            (Dem_CbLookupTableGetFDC[CbIdx] != EventId) )
    {
      CbIdx++;
    }

    DEM_PRECONDITION_ASSERT(
      (CbIdx < (Dem_CbIndexType)DEM_LOOKUP_TABLE_GET_FDC_SIZE),
      DEM_INTERNAL_API_ID);

    RetVal = Dem_CbFuncPtrGetFDC[CbIdx](FDC);
  }
#if ( (DEM_ENABLE_ASR43_SERVICE_API == STD_ON) || \
      (DEM_DEFAULT_ASR_SERVICE_API == DEM_SERVICE_API_ASR2011) )
  else
  {
    /* !LINKSTO Dem.SWS_Dem_00671,1 */
    RetVal = DEM_E_NO_FDC_AVAILABLE;
  }
#endif

  if (E_OK != RetVal)
  {
    /* !LINKSTO Dem.MonitorInternalDebounce.InvalidFDCRead,1*/
    /* if callback function returns E_NOT_OK or DEM_E_NO_FDC_AVAILABLE,
     * FDC might be invalid so the value considered for the current FDC
     * shall be 0 */
    *FDC = 0;
  }

  DBG_DEM_CBGETFAULTDETECTIONCOUNTER_EXIT(RetVal, EventId, FDC);
  return RetVal;
}
#endif /* (DEM_USE_CB_GET_FDC == STD_ON) */

#if (DEM_NUM_CMB_DTCS > 0U)
FUNC(Std_ReturnType, DEM_CODE) Dem_GetFDCOfCmbDTC(
  Dem_EventIdType     EventId,
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA)
    FaultDetectionCounter)
{
  Std_ReturnType Result = E_NOT_OK;
  Dem_CmbDTCEvLnkType CmbEvIdx;
  Dem_DTCConfIdxType DTCConfIdx = DEM_GBI_DTCCONFIDX(EventId);
  sint8 MaxFDC = -128;
  sint8 FDC;

  DBG_DEM_GETFDCOFCMBDTC_ENTRY(EventId, FaultDetectionCounter);

  /* parse all events which are combined */
  for (CmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx];
       CmbEvIdx < Dem_CmbDTCEvLnk[DTCConfIdx + 1U];
       CmbEvIdx++)
  {
    Dem_DebounceType Algorithm = Dem_GbiDebounceAlgo(Dem_CmbDTCEvents[CmbEvIdx]);

#if (DEM_USE_CB_GET_FDC == STD_OFF)
    if (Dem_DebounceFctPtrTable[Algorithm].GetFDCFct != NULL_PTR)
#endif
    {
      if (E_OK == Dem_DebounceFctPtrTable[Algorithm].
                    GetFDCFct(Dem_CmbDTCEvents[CmbEvIdx], &FDC))
      {
        /* check if maximum FDC value must be updated */
        if (MaxFDC < FDC)
        {
          MaxFDC = FDC;
        }

        Result = E_OK;
      }
    }
  }

  /* for event combination return maximum FDC value from all events
   * if at least one valid read of the FDC has been made */
  if (Result == E_OK)
  {
    *FaultDetectionCounter = MaxFDC;
  }
  /* otherwise the considered FDC value will be "0" */
  else
  {
    *FaultDetectionCounter = 0;
  }

  DBG_DEM_GETFDCOFCMBDTC_EXIT(Result, EventId, FaultDetectionCounter);
  return Result;
}
#endif /* (DEM_NUM_CMB_DTCS > 0U) */

#if (DEM_NUM_FFSEGS > 0U)
FUNC(Dem_SizeFFType, DEM_CODE) Dem_SizeOfFF(
  Dem_FFKindType                                 FFKind,
  P2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) IndividPartFFClass)
{
  Dem_SizeFFType Result = 0U;
  uint8_least FFPartIdx;
  P2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFPartClass[DEM_NUM_FFPARTS];
#if (DEM_COMMON_FREEZEFRAMES_USED == STD_ON)
  FFPartClass[0] = &Dem_FFClass[Dem_CommonPartFFClassIdx[FFKind]];
#endif
  FFPartClass[DEM_NUM_FFPARTS - 1U] = IndividPartFFClass;

  DBG_DEM_SIZEOFFF_ENTRY(FFKind, IndividPartFFClass);

#if (DEM_COMMON_FREEZEFRAMES_USED == STD_OFF)
  TS_PARAM_UNUSED(FFKind);
#endif

  /* Deviation TASKING-1 */
  for (FFPartIdx = 0U; FFPartIdx < DEM_NUM_FFPARTS; FFPartIdx++)
  {
    Dem_NumFFSegsType SegIdx;

    /* add size of all FF segments */
    for (SegIdx = 0U; SegIdx < FFPartClass[FFPartIdx]->NumFFSegs; SegIdx++)
    {
      const Dem_FFSegIdxType FFSegIdx = FFPartClass[FFPartIdx]->FFSegIdx[SegIdx];

      if (FFSegIdx != DEM_FFSEG_IDX_UNUSED)
      {
        Result += Dem_SizeOfFFSegment(&Dem_FFSegment[FFSegIdx]);
      }
    }
  }

  DBG_DEM_SIZEOFFF_EXIT(Result, FFKind, IndividPartFFClass);
  return Result;
}

FUNC(Dem_SizeFFType, DEM_CODE) Dem_SizeOfFFSegment(
  P2CONST(Dem_FFSegmentType, AUTOMATIC, DEM_CONST) FFSegment)
{
  const Dem_NumDataElementsType LastDataElemIdx =
    FFSegment->NumFFDataElements - 1U;
  const Dem_SizeFFType Result =
    (FFSegment->DataElementOffset[LastDataElemIdx] +
    DEM_EXTERNAL_DATA_ELEMENT_SIZE(FFSegment->DataElementIdx[LastDataElemIdx]));

  DBG_DEM_SIZEOFFFSEGMENT_ENTRY(FFSegment);

  DBG_DEM_SIZEOFFFSEGMENT_EXIT(Result, FFSegment);
  return Result;
}

FUNC(Dem_NumFFSegsType, DEM_CODE) Dem_GetNumFFSegs(
  Dem_FFKindType                                 FFKind,
  P2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) IndividPartFFClass)
{
  Dem_NumFFSegsType NumFFSegs = 0U;
  uint8_least FFPartIdx;

  P2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFPartClass[DEM_NUM_FFPARTS];
#if (DEM_COMMON_FREEZEFRAMES_USED == STD_ON)
  FFPartClass[0] = &Dem_FFClass[Dem_CommonPartFFClassIdx[FFKind]];
#endif
  FFPartClass[DEM_NUM_FFPARTS - 1U] = IndividPartFFClass;

  DBG_DEM_GETNUMFFSEGS_ENTRY(FFKind, IndividPartFFClass);

#if (DEM_COMMON_FREEZEFRAMES_USED == STD_OFF)
  TS_PARAM_UNUSED(FFKind);
#endif

  /* Deviation TASKING-1 */
  for (FFPartIdx = 0U; FFPartIdx < DEM_NUM_FFPARTS; FFPartIdx++)
  {
#if (DEM_CALIBRATION_WITHOUTEVCOMB_SUPPORT == STD_ON)
    {
      Dem_NumFFSegsType SegIdx;

      for (SegIdx = 0U; SegIdx < FFPartClass[FFPartIdx]->NumFFSegs; SegIdx++)
      {
        if (FFPartClass[FFPartIdx]->FFSegIdx[SegIdx] != DEM_FFSEG_IDX_UNUSED)
        {
          NumFFSegs++;
        }
      }
    }
#else
    NumFFSegs += FFPartClass[FFPartIdx]->NumFFSegs;
#endif /* #if (DEM_CALIBRATION_WITHOUTEVCOMB_SUPPORT == STD_ON) */
  }

  DBG_DEM_GETNUMFFSEGS_EXIT(NumFFSegs, FFKind, IndividPartFFClass);
  return NumFFSegs;
}
#endif /* (DEM_NUM_FFSEGS > 0U) */

#if (DEM_NUM_EDSEGS > 0U)
FUNC(Dem_SizeEDType, DEM_CODE) Dem_SizeOfED(
  P2CONST(Dem_EDClassType, AUTOMATIC, DEM_CONST) EDClass)
{
  Dem_SizeEDType Result = 0U;

  DBG_DEM_SIZEOFED_ENTRY(EDClass);

  if (EDClass->NumEDSegs > 0U)
  {
    const Dem_EDSegIdxType LastSegIdx = EDClass->NumEDSegs - 1U;

    /* add start byte and size of last segment */
    Result = EDClass->StartByte[LastSegIdx] +
      Dem_SizeOfStoredDEsInSegment(&Dem_EDSegment[EDClass->EDSegIdx[LastSegIdx]]);
  }

  DBG_DEM_SIZEOFED_EXIT(Result, EDClass);
  return Result;
}

FUNC(Dem_SizeEDType, DEM_CODE) Dem_SizeOfStoredDEsInSegment(
  P2CONST(Dem_EDSegmentType, AUTOMATIC, DEM_CONST) EDSegment)
{
  const Dem_NumDataElementsType LastDataElemIdx =
    EDSegment->NumEDDataElements - 1U;
  Dem_SizeEDType Result = EDSegment->DataElementOffset[LastDataElemIdx];

  DBG_DEM_SIZEOFSTOREDDESINSEGMENT_ENTRY(EDSegment);

#if (DEM_NUM_EXT_DATAELEMENTS > 0U)
#if (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON)
  if (EDSegment->DataElementIdx[LastDataElemIdx] < DEM_NUM_EXT_DATAELEMENTS)
#endif
  {
#if (DEM_NUM_CAPTURE_ON_RETRIEVAL_DATAELEMENTS > 0U)
    if(Dem_DataElement[EDSegment->DataElementIdx[LastDataElemIdx]].CaptureOnRetrieval == FALSE)
#endif
    {
      /* add offset and size of last data element */
      Result +=
        DEM_EXTERNAL_DATA_ELEMENT_SIZE(EDSegment->DataElementIdx[LastDataElemIdx]);
    }
  }
#endif /* (DEM_NUM_EXT_DATAELEMENTS > 0U) */
  /* else: last element being an internal data element do not use the size */

  DBG_DEM_SIZEOFSTOREDDESINSEGMENT_EXIT(Result, EDSegment);
  return Result;
}

#if ((DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON) || \
     (DEM_NUM_CAPTURE_ON_RETRIEVAL_DATAELEMENTS > 0U))
FUNC(Dem_SizeEDType, DEM_CODE) Dem_SizeOfNonStoredDEsInSegment(
  P2CONST(Dem_EDSegmentType, AUTOMATIC, DEM_CONST) EDSegment)
{
  Dem_NumDataElementsType DataElementIndex;
  Dem_DataElementIdxType DataElementIdx;
  Dem_SizeEDType SizeOfNonStoredDEs = 0U;

  DBG_DEM_SIZEOFNONSTOREDDESINSEGMENT_ENTRY(EDSegment);

  /* all data elements of the ED segment */
  for (DataElementIndex = 0U;
       DataElementIndex < EDSegment->NumEDDataElements;
       ++DataElementIndex)
  {
    DataElementIdx = EDSegment->DataElementIdx[DataElementIndex];
#if (DEM_NUM_EXT_DATAELEMENTS > 0U)
    if (DataElementIdx >= DEM_NUM_EXT_DATAELEMENTS)
#endif
    {
      SizeOfNonStoredDEs += Dem_SizeofInternalDE(DataElementIdx);
    }
#if (DEM_NUM_CAPTURE_ON_RETRIEVAL_DATAELEMENTS > 0U)
    else
    {
      /* external elements with fetch on demand set to true */
      if(Dem_DataElement[DataElementIdx].CaptureOnRetrieval == TRUE)
      {
        SizeOfNonStoredDEs += DEM_EXTERNAL_DATA_ELEMENT_SIZE(DataElementIdx);
      }
    }
#endif
  }

  DBG_DEM_SIZEOFNONSTOREDDESINSEGMENT_EXIT(SizeOfNonStoredDEs, EDSegment);
  return SizeOfNonStoredDEs;
}
#endif /* ((DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON) || \
           (DEM_NUM_CAPTURE_ON_RETRIEVAL_DATAELEMENTS > 0U)) */

FUNC(Dem_SizeEntryDataType, DEM_CODE) Dem_AssembleExtendedDataSeg(
  Dem_EventIdType                                  EventId,
  P2CONST(Dem_EDSegmentType, AUTOMATIC, DEM_CONST) EDSegment,
  Dem_EDStartByteType                              EDStartByte,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)           DestBuffer,
  Dem_EventMemoryEntryPtrConstType                 EvMemEntry,
  boolean                                          PassMasterEventIdToDECallOut,
  boolean                                          CriticalSectionActive)
{
  Dem_NumDataElementsType DataElementIndex;
  Dem_SizeEntryDataType EDSegSize = 0U;

#if (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_OFF)
  TS_PARAM_UNUSED(EventId);
#endif
#if (DEM_NUM_EXT_DATAELEMENTS == 0U)
  TS_PARAM_UNUSED(EDStartByte);
#endif
#if (DEM_NUM_CAPTURE_ON_RETRIEVAL_DATAELEMENTS == 0U)
  TS_PARAM_UNUSED(PassMasterEventIdToDECallOut);
  TS_PARAM_UNUSED(CriticalSectionActive);
#endif

  DBG_DEM_ASSEMBLEEXTENDEDDATASEG_ENTRY(
    EventId, EDSegment, EDStartByte,
    DestBuffer, EvMemEntry, PassMasterEventIdToDECallOut, CriticalSectionActive);

  /* add all data elements of the ED segment */
  for (DataElementIndex = 0U;
       DataElementIndex < EDSegment->NumEDDataElements;
       ++DataElementIndex)
  {
    const Dem_DataElementIdxType DataElementIdx =
      EDSegment->DataElementIdx[DataElementIndex];

#if (DEM_NUM_EXT_DATAELEMENTS > 0U)
    const Dem_DataElementOffsetType EDDataElemOffset =
      EDSegment->DataElementOffset[DataElementIndex];

    if (DataElementIdx < DEM_NUM_EXT_DATAELEMENTS)
    {
      const Dem_SizeEntryDataType DataElementSize =
        DEM_EXTERNAL_DATA_ELEMENT_SIZE(DataElementIdx);
#if (DEM_NUM_CAPTURE_ON_RETRIEVAL_DATAELEMENTS > 0U)

      if(CriticalSectionActive == FALSE)
      {
        /* !LINKSTO Dem.DataElementCaptureOnRetrieval.DataReadContext,1 */
        /* !LINKSTO dsn.Dem.ExternalDataCapturing.CaptureExtendedData,1 */
        if(Dem_DataElement[DataElementIdx].CaptureOnRetrieval == TRUE)
        {
          Dem_EntryDataPtrType DestBufferDE = &DestBuffer[EDSegSize];
          Dem_EventIdType DECalloutEventId = EventId;

          if(PassMasterEventIdToDECallOut == TRUE)
          {
            DECalloutEventId = DEM_GET_MASTER_EVID(EventId);
          }

          if(Dem_ReadExternalDataElement(DestBufferDE, DataElementIdx, DECalloutEventId) != E_OK)
          {
            Dem_SizeEntryDataType Index = 0U;

            /* fill data element location in destination buffer with padding values */
            while (Index < DataElementSize)
            {
              /* !LINKSTO Dem.DataElementCaptureOnRetrieval.DataPadding,1 */
              DestBufferDE[Index] = DEM_DATA_PADDING_VALUE;
              Index++;
            }
          }
        }
      }
      else
#endif
      {
#if (DEM_NUM_CAPTURE_ON_RETRIEVAL_DATAELEMENTS > 0U)
        if(Dem_DataElement[DataElementIdx].CaptureOnRetrieval == FALSE)
#endif
        {
          const Dem_EntryDataPtrConstType EDEntryData =
            &(Dem_EDEntryData(EvMemEntry)[EDStartByte]);

          /* copy data element values for all its size */
          TS_MemCpy(&DestBuffer[EDSegSize],
                    &EDEntryData[EDDataElemOffset],
                    DataElementSize);
        }
      }
      /* get the data element sizes excluding internal data element */
      EDSegSize += DataElementSize;
    }
    else
#endif /* (DEM_NUM_EXT_DATAELEMENTS > 0U) */
    {
#if (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON)
#if (DEM_NUM_CAPTURE_ON_RETRIEVAL_DATAELEMENTS > 0U)
      if(CriticalSectionActive == FALSE)
      {
        /* update segment size, but don't copy data */
        EDSegSize += (Dem_SizeEntryDataType) Dem_SizeofInternalDE(DataElementIdx);
      }
      else
#endif /* (DEM_NUM_CAPTURE_ON_RETRIEVAL_DATAELEMENTS > 0U) */
      {
        /* copy data and update segment size */
        EDSegSize += Dem_AssembleEDSegIntData(
          EventId, DataElementIdx, &DestBuffer[EDSegSize], EvMemEntry);
      }
#endif /* (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON) */
    }
  }
  DBG_DEM_ASSEMBLEEXTENDEDDATASEG_EXIT(
    EventId, EDSegSize, EDSegment,
    EDStartByte, DestBuffer, EvMemEntry, PassMasterEventIdToDECallOut, CriticalSectionActive);
  return EDSegSize;
}

#if (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON)
STATIC FUNC(uint8, DEM_CODE) Dem_AssembleEDSegIntData(
  Dem_EventIdType                        EventId,
  Dem_DataElementIdxType                 DataElementIdx,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Dest,
  Dem_EventMemoryEntryPtrConstType       EvMemEntry)
{
  uint8 SizeForDataElementIdx = 1U;

  DBG_DEM_ASSEMBLEEDSEGINTDATA_ENTRY(EventId, DataElementIdx,
    Dest, EvMemEntry);

#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
  if (DataElementIdx >= DEM_INT_VAL_IDX_FDC12)
  {
    Dem_AssembleEDOnFDCThresholdData(DataElementIdx, Dest, EvMemEntry);
  }
  else
#endif
  {
    switch (DataElementIdx)
    {
      case DEM_INT_VAL_IDX_OCCCTR:
        /* read the occurrence counter from the event memory */
        *Dest = EvMemEntry->OccCtr;
        break;

#if (DEM_USE_AGING == STD_ON)
      case DEM_INT_VAL_IDX_AGECTRUP:
        Dem_AssembleEDSegAgingCounterUp(EventId, Dest, EvMemEntry);
        break;

      case DEM_INT_VAL_IDX_AGECTRDWN:
        Dem_AssembleEDSegAgingCounterDown(EventId, Dest, EvMemEntry);
        break;

#endif /* DEM_USE_AGING == STD_ON */

      case DEM_INT_VAL_IDX_OVFIND:
        {
          const uint8 OriginIdx = Dem_GbiDTCOriginIdx(EventId);

          /* read the status of overflow indication bit from EvMemOvfIndFlags
           * and transfer into format: 0x00 = no overflow, 0x01 = overflow */
          *Dest = (uint8)(DEM_IS_OVFIND_SET(OriginIdx) ? 0x01U : 0x00U);
        }
        break;

      case DEM_INT_VAL_IDX_EVSIGNIF:
        /* !LINKSTO Dem.DemInternalDataElementRange.EventSignificance,1 */
        /* get the significance level of the event and store it in the ED */
        *Dest = (uint8)Dem_GbiEvSignificance(EventId);
        break;

#if (DEM_USE_EVENT_DISPLACEMENT == STD_ON)
      case DEM_INT_VAL_IDX_PRIO:
        /* read the event priority */
        *Dest = Dem_ExternalPrioValue[Dem_GbiPriority(EventId)];
        break;
#endif

      case DEM_INT_VAL_IDX_EVENT_ID:
        /* read the eventId */
        Dest[0] = (uint8)(EvMemEntry->EventId);
        Dest[1] = (uint8)((EvMemEntry->EventId) >> 8);
        SizeForDataElementIdx = 2U;
        break;

#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U)
      case DEM_INT_VAL_IDX_ROOT_ID:
        /* read the RootId */
        Dest[0] = (uint8)(EvMemEntry->RootId);
        Dest[1] = (uint8)((EvMemEntry->RootId) >> 8);
        SizeForDataElementIdx = 2U;
        break;
#endif

      /* !LINKSTO Dem.SWS_Dem_00820,1 */
#if (DEM_OPCYCLE_CTR_CSLF_SUPPORT == STD_ON)
      case DEM_INT_VAL_IDX_CSLF:
        /* read the CSLF counter and write it in the ED */
        *Dest = EvMemEntry->CSLF;
        break;
#endif

    /* !LINKSTO Dem.SWS_Dem_00821,1 */
#if (DEM_OPCYCLE_CTR_CSFF_SUPPORT == STD_ON)
      case DEM_INT_VAL_IDX_CSFF:
        /* read the CSFF counter and write it in the ED */
        *Dest = EvMemEntry->CSFF;
        break;
#endif

    /* !LINKSTO Dem.SWS_Dem_00822,1 */
#if (DEM_OPCYCLE_CTR_FAILEDCYCLES_SUPPORT == STD_ON)
      case DEM_INT_VAL_IDX_FAILEDCYCLES:
        /* read the FAILEDCYCLES counter and write it in the ED */
        *Dest = EvMemEntry->FAILEDCYCLES;
        break;
#endif

      case DEM_INT_VAL_IDX_CURRENT_FDC:
        /* get the fault detection counter */
        Dem_AssembleEDSegFaultDetectionCounter(EventId, Dest);
        break;

#if (DEM_MAR_SUPPORT == STD_ON)
      case DEM_INT_VAL_IDX_MAD:
        /* get the monitor activity data */
        /* !LINKSTO Dem.ASR21-11.SWS_Dem_01367,1 */
        Dem_AssembleEDSegMARData(EventId, Dest);
        SizeForDataElementIdx = 2U;
        break;
#endif

      /* CHECK: NOPARSE */
      default: /* should never be reached */
        DEM_UNREACHABLE_CODE_ASSERT(DEM_SID_AssembleEDSegIntData);
        break;
      /* CHECK: PARSE */
    } /* DataElementIdx */
  }

  DBG_DEM_ASSEMBLEEDSEGINTDATA_EXIT(SizeForDataElementIdx, EventId,
    DataElementIdx, Dest, EvMemEntry);
  return SizeForDataElementIdx;
}

#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
STATIC FUNC(void, DEM_CODE) Dem_AssembleEDOnFDCThresholdData(
  Dem_DataElementIdxType                 DataElementIdx,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Dest,
  Dem_EventMemoryEntryPtrConstType       EvMemEntry)
{
  switch (DataElementIdx)
  {
    case DEM_INT_VAL_IDX_FDC12:
      /* read the maximum fault detection counter since last clear
       * from the event memory */
      *Dest = EvMemEntry->FDC12;
      break;

    case DEM_INT_VAL_IDX_SI30:
      /* read the DTC status indicators from the memory */
      *Dest = EvMemEntry->SI30;
      break;

    case DEM_INT_VAL_IDX_OCC1:
      /* read the operation cycles since last unconfirmedDTC counter
       * from the event memory */
      *Dest = EvMemEntry->OCC1;
      break;

    case DEM_INT_VAL_IDX_OCC2:
      /* read the unconfirmedDTC aging counter from the event memory */
      *Dest = EvMemEntry->OCC2;
      break;

    case DEM_INT_VAL_IDX_OCC3:
      /* read the operation cycles since first unconfirmedDTC counter from the
       * event memory */
      *Dest = EvMemEntry->OCC3;
      break;

    case DEM_INT_VAL_IDX_OCC4:
      /* read the unconfirmedDTC operation cycle counter from the event
       * memory */
      *Dest = EvMemEntry->OCC4;
      break;

#if (DEM_VCC_OCC5_USED == STD_ON)
    case DEM_INT_VAL_IDX_OCC5:
      /* read the warm-up cycles where event is reported as active until it becomes
       * confirmed from the event memory */
      *Dest = EvMemEntry->OCC5;
      break;
#endif

    case DEM_INT_VAL_IDX_OCC6:
      /* read the consecutive failed operation cycle counter from the event
       * memory */
      *Dest = EvMemEntry->OCC6;
      break;

    case DEM_INT_VAL_IDX_OCC7:
      /* read the qualified/unconfirmedDTC operation cycle counter from the
       * event memory */
      *Dest = EvMemEntry->OCC7;
      break;

      /* CHECK: NOPARSE */
    default: /* should never be reached */
      DEM_UNREACHABLE_CODE_ASSERT(DEM_SID_AssembleEDOnFDCThresholdData);
      break;
      /* CHECK: PARSE */
  } /* DataElementIdx */
}

#if ((DEM_USE_AGING == STD_ON) && (DEM_NUM_INDICATOR_LINKS > 0U) && (DEM_VCC_OCC5_USED == STD_ON))
STATIC FUNC(void, DEM_CODE) Dem_ResetIndicatorCycleCounterRoleOfEventId(
  Dem_EventIdType EventId)
{
  DBG_DEM_RESETINDICATORCYCLECOUNTERROLEOFEVENTID_ENTRY(EventId);

  /* check if any indicator is configured for current EventId */
#if (DEM_CALIBRATION_WITHOUTEVCOMB_SUPPORT == STD_ON)
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
        /* no check for IndicatorClass to be enabled; the intention is keep the synchronization
         * of event Aging-Maturing, therefore de-calibrated indicators are considered as well */

        CONSTP2CONST(Dem_IndicatorClassType, AUTOMATIC, DEM_CONST) IndicatorClass =
          &Dem_IndicatorClasses[Idx];
        /* even if CounterDataIdx is of smaller type than EventId the cast is ok
         * because size of Dem_CounterDataIdxType depends on the amount of events in
         * the system */
        const Dem_CounterDataIdxType CounterDataIdx = (Dem_CounterDataIdxType)EventId;

        /* set indicator role to healing */
        Dem_SetCycleCounterRole(IndicatorClass->IndicatorId, CounterDataIdx,
          DEM_INDICATORCOUNTER_ROLE_HEALING_CYCLE_COUNTER);
      }
    }
  }
/* calibration is disabled and event availability is not considered */
#else
  /* check if any indicator is configured for current EventId */
  if (Dem_GbiIndicatorUsed(EventId) != FALSE)
  {
    Dem_IndicatorIdxType LinkIdx;
    for (LinkIdx = 0U; LinkIdx < DEM_NUM_INDICATOR_LINKS; ++LinkIdx)
    {
      if (Dem_IndicatorLink[LinkIdx].EventId == EventId)
      {

        /* set indicator role to healing */
        Dem_SetCycleCounterRole(DEM_INDICATOR_DEFAULT_COUNTER, LinkIdx,
          DEM_INDICATORCOUNTER_ROLE_HEALING_CYCLE_COUNTER);
      }
    }
  }
#endif

  DBG_DEM_RESETINDICATORCYCLECOUNTERROLEOFEVENTID_EXIT(EventId);
}
#endif /* ((DEM_USE_AGING == STD_ON) && (DEM_NUM_INDICATOR_LINKS > 0U)  &&
           (DEM_VCC_OCC5_USED == STD_ON)) */
#endif /* (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) */

#if (DEM_USE_AGING == STD_ON)
STATIC FUNC(void, DEM_CODE) Dem_AssembleEDSegAgingCounterDown(
  Dem_EventIdType                        EventId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Dest,
  Dem_EventMemoryEntryPtrConstType       EvMemEntry)
{
  if (DEM_AGING_ALLOWED(EventId))
  {
    /* !LINKSTO Dem.SWS_Dem_00673,1 */
    /* calculate aging counter output (count-down) */
    *Dest = *(Dem_IntValEntryData(EvMemEntry));
  }
  else
  {
    /* !LINKSTO Dem.SWS_Dem_01043,1 */
    *Dest = 255U;
  }
}

STATIC FUNC(void, DEM_CODE) Dem_AssembleEDSegAgingCounterUp(
  Dem_EventIdType                        EventId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Dest,
  Dem_EventMemoryEntryPtrConstType       EvMemEntry)
{
  if (DEM_AGING_ALLOWED(EventId))
  {
    /* !LINKSTO Dem.SWS_Dem_00643,1 */
    /* calculate aging counter output (Dem.ASR40.SWS_Dem_00472, internal value is count-down
     * and stored at the beginning of entry data) */
    *Dest = Dem_GbiNumAgingCycles(EventId) -
      *(Dem_IntValEntryData(EvMemEntry));
  }
  else
  {
    /* !LINKSTO Dem.SWS_Dem_01044,1 */
    *Dest = 0U;
  }
}
#endif /* DEM_USE_AGING == STD_ON */

STATIC FUNC(void, DEM_CODE) Dem_AssembleEDSegFaultDetectionCounter(
  Dem_EventIdType                        EventId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Dest)
{
  sint8 FDC = 0;

  /* get the fault detection counter */
  /* configuration ensures that CURRENT_FDC is only used with
   * counter-based, time-based, and frequency-based debouncing,
   * i.e. function pointer will never be NULL */
  /* Dem_GetFDCCounterBased, Dem_GetFDCTimeBased, and
   * Dem_GetFDCFrequencyBased will always return E_OK */
#if (DEM_NUM_CMB_DTCS > 0U)
  if (DEM_IS_EVENT_COMBINED(EventId))
  {
    /* if event is combined get the FDC of the combined DTC */
    (void)Dem_GetFDCOfCmbDTC(EventId, &FDC);
  }
  else
#endif
  {
    /* the GetFDCFct pointer is ensured to be valid from the configuration step */
    (void)Dem_DebounceFctPtrTable[Dem_GbiDebounceAlgo(EventId)].
      GetFDCFct(EventId, &FDC);
  }

  /* transform singed internal value to unsigned value in response-buffer
   * (0x00-0x7F: 0-127, 0x80-0xFF: -128..-1) */
  *Dest = (uint8)FDC;
}

#if (DEM_MAR_SUPPORT == STD_ON)
STATIC FUNC(void, DEM_CODE) Dem_AssembleEDSegMARData(
  Dem_EventIdType                        EventId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Dest)
{
  Dem_MAREventIndexType IdxMAREvent = 0U;
#if (DEM_NUM_MAR_CMB_DTCS > 0U)
  Dem_MAREventIndexType IdxMARDTC = 0U;
#endif
  boolean IsIdxFound = FALSE;

  DBG_DEM_ASSEMBLEEDSEGMARDATA_ENTRY(EventId, Dest);

#if (DEM_NUM_MAR_CMB_DTCS > 0U)
  if (DEM_IS_EVENT_COMBINED(EventId))
  {
    /* if the MAR data was requested for one of the combined MAR events,
     * it is identified in this 'while' loop */
    while ( (!IsIdxFound) &&
            (IdxMARDTC < DEM_NUM_MAR_CMB_DTCS) )
    {
      Dem_MAREventIndexType MAREvIdxStart = Dem_MAREventCombinationIdx[IdxMARDTC];
      Dem_MAREventIndexType MAREvIdxEnd = Dem_MAREventCombinationIdx[IdxMARDTC + 1U];

      /* identify the MAR event combination in Dem_MAREvents[] array, knowing that
       * the first event of each MAR combination generated in this array is the
       * master event of the combination */
      if (Dem_MAREvents[MAREvIdxStart] == DEM_GET_MASTER_EVID(EventId))
      {
        Dem_MAREventIndexType RatioIdx = IdxMARDTC + DEM_NUM_MAR_SINGLE_EVENTS;

        /* initialize the numerator of the MAR event combination */
        uint8 CmbNumerator = DEM_MAR_ELEMENT_MAX_VALUE;

        for (IdxMAREvent = MAREvIdxStart; IdxMAREvent < MAREvIdxEnd; IdxMAREvent++)
        {
          Dem_EventIdType CmbEventId = Dem_MAREvents[IdxMAREvent];

          /* !LINKSTO Dem.OBDonUDS.MAR.CmbEvents.UnavailableEventNumeratorReport,1 */
          if ( (Dem_GbiEvAvailable(CmbEventId) == TRUE) &&
               (Dem_NvData.MARData.Numerator[IdxMAREvent] < CmbNumerator) )
          {
            /* get the smallest numerator value corresponding to the available
             * events of the MAR events combination */
            CmbNumerator = Dem_NvData.MARData.Numerator[IdxMAREvent];
          }
        }

        /* report the smallest numerator value of the events in combination */
        /* !LINKSTO Dem.OBDonUDS.MAR.CmbEvents.MiniNumerator.Report,1 */
        Dest[0] = CmbNumerator;
        /* report the stored monitor activity ratio of the event combination */
        Dest[1] = Dem_NvData.MARData.Ratio[RatioIdx];
        IsIdxFound = TRUE;
      }
      IdxMARDTC++;
    }
  }
  else
#endif /* (DEM_NUM_MAR_CMB_DTCS > 0U) */
  {
#if (DEM_NUM_MAR_SINGLE_EVENTS > 0U)
    /* if the MAR data was requested for a single (non-combined) MAR event,
     * it will be identified in this 'while' loop */
    while ( (!IsIdxFound) &&
            (IdxMAREvent < DEM_NUM_MAR_SINGLE_EVENTS) )
    {
      /* identify the Event's index in Dem_MAREvents[] array */
      if (Dem_MAREvents[IdxMAREvent] == EventId)
      {
        /* use the identified index to reference the corresponding MAR data */
        Dest[0] = Dem_NvData.MARData.Numerator[IdxMAREvent];
        Dest[1] = Dem_NvData.MARData.Ratio[IdxMAREvent];
        IsIdxFound = TRUE;
      }
      IdxMAREvent++;
    }
#endif
  }

  DBG_DEM_ASSEMBLEEDSEGMARDATA_EXIT(EventId, Dest);
}
#endif /* (DEM_MAR_SUPPORT == STD_ON) */
#endif /* (DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON) */
#endif /* (DEM_NUM_EDSEGS > 0U) */

#if ((DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON) || \
     (DEM_NUM_CAPTURE_ON_RETRIEVAL_DATAELEMENTS > 0U))
STATIC FUNC(Dem_SizeEDType, DEM_CODE) Dem_SizeofInternalDE(
  Dem_DataElementIdxType                 DataElementIdx)
{
  Dem_SizeEDType SizeOfInternalDE = 0U;
  if (DataElementIdx == DEM_INT_VAL_IDX_EVENT_ID)
  {
    /* maximum size of an internal data element is 2 bytes: EventId. */
    SizeOfInternalDE = 2U;
  }
#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U)
  else if (DataElementIdx == DEM_INT_VAL_IDX_ROOT_ID)
  {
    /* maximum size of an internal data element is 2 bytes: RootId. */
    SizeOfInternalDE = 2U;
  }
#endif
#if (DEM_MAR_SUPPORT ==STD_ON)
  else if (DataElementIdx == DEM_INT_VAL_IDX_MAD)
  {
    /* maximum size of an internal data element is 2 bytes: Monitor Activity Data. */
    SizeOfInternalDE = 2U;
  }
#endif
  else
  {
    /* size 1 byte for the following internal data elements:
     * AgeCtr: DemAgingCycleCounterThreshold range is 1 byte
     * OvfInd: for each memory type 1 bit is used
     * OccCtr: DemImmediateNvStorageLimit range is 1 byte (Immediate storage)
     *       : NumFF range is 1 byte (No immediate storage) */
    /* SI30, FDCs and OCCs: 1 byte */
    SizeOfInternalDE = 1U;
  }
  return SizeOfInternalDE;
}
#endif /* ((DEM_USE_MAPPED_INT_DATA_ELEMENTS == STD_ON) || \
           (DEM_NUM_CAPTURE_ON_RETRIEVAL_DATAELEMENTS > 0U)) */

#if (DEM_USE_INT_VAL_AREA == STD_ON)
FUNC(uint8, DEM_CODE) Dem_SizeOfIntValArea(Dem_EventIdType EventId)
{
  uint8 SizeOfIntVal = 0U;

  DBG_DEM_SIZEOFINTVALAREA_ENTRY(EventId);

#if (DEM_USE_AGING == STD_ON)
  /* aging counter internal value exists */
  if (DEM_AGING_ALLOWED(EventId))
  {
    SizeOfIntVal = 1U;
  }
#endif /* DEM_USE_AGING */

  DBG_DEM_SIZEOFINTVALAREA_EXIT(SizeOfIntVal, EventId);
  return SizeOfIntVal;
}
#endif /* DEM_USE_INT_VAL_AREA */

FUNC(void, DEM_CODE) Dem_ShiftData(
  Dem_EntryDataPtrType  EntryData,
  Dem_SizeEntryDataType Offset,
  Dem_SizeEntryDataType Width)
{
  Dem_SizeEntryDataType i;

  DBG_DEM_SHIFTDATA_ENTRY(EntryData, Offset, Width);

  for(i = 0U; i < Width; ++i)
  {
    EntryData[i] = EntryData[i+Offset];
  }

  DBG_DEM_SHIFTDATA_EXIT(EntryData, Offset, Width);
}

/*------------------[immediate storage core-functions]----------------------*/

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
FUNC(void, DEM_CODE) Dem_CheckForImmediateEntryStorage(
  Dem_EventIdType             OriginalEventId,
  Dem_EventMemoryEntryPtrType EvMemEntryPtr,
  Dem_SizeEvMemEntryType      EvMemEntryIdx,
  boolean                     ForceWrite)
{
  const uint8 OriginIdx = Dem_GbiDTCOriginIdx(OriginalEventId);
  const Dem_EventIdType CurrentEventId = EvMemEntryPtr->EventId;
  boolean ImmStorageCurrentEvent       = FALSE;
  boolean ImmStorageOriginalEvent      = FALSE;

  DBG_DEM_CHECKFORIMMEDIATEENTRYSTORAGE_ENTRY(
    OriginalEventId, EvMemEntryPtr, EvMemEntryIdx, ForceWrite);
  /* Incase of EvMemEntry was already set to DEM_ENTRY_CLEAR_IMMEDIATELY
   * means that Nvm job is ongoing and changed EvMem Location will be stored to NVM
   * subsequently through the NvM callback Dem_StoreImmediatelyNext() */
  /* !LINKSTO dsn.Dem.ClearDTCBehavior.NonvolatileFinish,3 */
  if (EvMemEntryPtr->EntryStatus != DEM_ENTRY_CLEAR_IMMEDIATELY)
  {
    if (ForceWrite == FALSE)
    {
      ImmStorageCurrentEvent = Dem_GbiImmediateStorage(CurrentEventId);
      ImmStorageOriginalEvent = Dem_GbiImmediateStorage(OriginalEventId);
    }

#if (DEM_IMMEDIATE_NV_STORAGE_LIMIT > 0U)
    if ( (ForceWrite == FALSE) &&
         (
           ( (ImmStorageCurrentEvent == FALSE) &&
             (ImmStorageOriginalEvent == FALSE) ) ||
           (EvMemEntryPtr->OccCtr > DEM_IMMEDIATE_NV_STORAGE_LIMIT)) )
#else
    if ( (ForceWrite == FALSE) &&
         (ImmStorageCurrentEvent == FALSE) &&
         (ImmStorageOriginalEvent == FALSE) )
#endif /* (DEM_IMMEDIATE_NV_STORAGE_LIMIT > 0U) */
    {
        /* entry changed but no immediate storage - store during shutdown */
        EvMemEntryPtr->EntryStatus = DEM_ENTRY_CHANGED;
    }
    else if (Dem_NvMGateEntryInfo[OriginIdx].Status != DEM_NVM_IDLE)
    {
        if (DEM_EVENT_ID_INVALID != EvMemEntryPtr->EventId)
        {
          /* entry is in use and shall be stored */
#if (DEM_IMMEDIATE_NV_STORAGE_TYPE == DEM_IMMEDIATE_CLEARED)
          /* immediate storage restricted to cleared events -> store on shutdown */
          EvMemEntryPtr->EntryStatus = DEM_ENTRY_CHANGED;
#else
          /* immediate storage unrestricted -> store immediately */
          EvMemEntryPtr->EntryStatus = DEM_ENTRY_STORE_IMMEDIATELY;
#endif
        }
        else
        {
          /* entry has been cleared -> store immediately */
          EvMemEntryPtr->EntryStatus = DEM_ENTRY_CLEAR_IMMEDIATELY;
        }
    }
    else
    {
      /* store this event memory entry persistently */
      Dem_StoreImmediately(OriginIdx, EvMemEntryIdx);
      /* promote the status of the gate only if there
       * are information stored in the gate entry to
       * be written into the NvM by preparing the gate */
      Dem_NvMGateEntryInfo[OriginIdx].Status = DEM_NVM_WAITING;
    }
  }
  DBG_DEM_CHECKFORIMMEDIATEENTRYSTORAGE_EXIT(
    OriginalEventId, EvMemEntryPtr, EvMemEntryIdx, ForceWrite);
}

#if (DEM_CLEAR_DTC_BEHAVIOR != DEM_CLRRESP_VOLATILE)
FUNC(Std_ReturnType, DEM_CODE) Dem_TriggerNvmWriteEventStatus(void)
{
#if (DEM_DEV_ERROR_DETECT == STD_ON)
  NvM_RequestResultType NvMErrorStatus = NVM_REQ_PENDING;
  Std_ReturnType NvMResult;
#endif

  Std_ReturnType WriteBlockResult = E_NOT_OK;

  DBG_DEM_TRIGGERNVMWRITEEVENTSTATUS_ENTRY();

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  NvMResult = NvM_GetErrorStatus(DEM_NVM_BLOCK_ID_DEFAULT, &NvMErrorStatus);

  if ( (E_OK != NvMResult) || (NVM_REQ_PENDING == NvMErrorStatus) )
  {
    DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_WRONG_CONDITION);
  }
#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
  else if
    ( (DEM_CLEARDTC_STATE_PROCESSING_NVRAM != Dem_ClearDtcAsyncStatus.RunState) ||
      /* for NONVOLATILE_TRIGGER this is already checked by caller: */
      (DEM_NVM_IDLE != Dem_ClearDtcAsyncStatus.EventStatusWrite) )
  {
    /* indicates the intention to call NvM_WriteBlock() from an unexpected state */
    DEM_REPORT_ERROR(DEM_INTERNAL_API_ID, DEM_E_WRONG_CONDITION);
  }
#endif
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* set write state to waiting before queuing writing event status
     * block in NvM to allow synchronous execution of write callbacks */
    Dem_ClearDtcAsyncStatus.EventStatusWrite = DEM_NVM_WAITING;

    /* queue write request of default-entry to NvM - NvM_DstPtr is unused,
     * as permanent RAM block (default-entry) is configured */
    WriteBlockResult =
      NvM_WriteBlock(DEM_NVM_BLOCK_ID_DEFAULT, NULL_PTR);

    /* if write request for immediate storage was not accepted */
    if (WriteBlockResult != E_OK)
    {
      /*
       * ENTER critical section to protect Dem_ClearDtcAsyncStatus
       *       call-context: Dem(Task), optional NvM(Task), Rte(Task)
       */
      DEM_ENTER_EXCLUSIVE_AREA();

      Dem_ClearDtcAsyncStatus.EventStatusWrite = DEM_NVM_IDLE;
#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
      /* !LINKSTO Dem.ASR41.SWS_Dem_01057,1 */
      Dem_SetClearDTCResult(DEM_CLEAR_MEMORY_ERROR);
      Dem_ClearDtcAsyncStatus.RunState = DEM_CLEARDTC_STATE_FINISHED;
#endif

      /*
       * LEAVE critical section
       */
      DEM_EXIT_EXCLUSIVE_AREA();
    }
  }

  DBG_DEM_TRIGGERNVMWRITEEVENTSTATUS_EXIT(WriteBlockResult);
  return WriteBlockResult;
}
#endif /* DEM_CLEAR_DTC_BEHAVIOR != DEM_CLRRESP_VOLATILE */

FUNC(void, DEM_CODE) Dem_CheckForTriggerNvmWriteGateEntry(void)
{
  uint8 OriginIdx;
  boolean NvMErrorHandlingNeeded;
  boolean GateIsWaiting[DEM_MAXNUM_ORIGINS];
  Std_ReturnType WriteBlockResult[DEM_MAXNUM_ORIGINS];

  DBG_DEM_CHECKFORTRIGGERNVMWRITEGATEENTRY_ENTRY();

  /* Avoid initialize arrays GateIsWaiting and WriteBlockResult
   * in a separate for loop to keep a low run time.
   * Deal with it inside the code. */
  NvMErrorHandlingNeeded = FALSE;

  /*
   * ENTER critical section to protect the Nv_Status
   *       call-context: Dem(Task), optional NvM(Task), Rte(Task)
   */
  DEM_ENTER_EXCLUSIVE_AREA();

  for (OriginIdx = 0U; OriginIdx < DEM_MAXNUM_ORIGINS; ++OriginIdx)
  {
    if (Dem_NvMGateEntryInfo[OriginIdx].Status == DEM_NVM_WAITING)
    {
      /* Dem_NvMGateEntryInfo must only be modified within crit. sect. */
      /* advance internal NvM gate status to pending. */
      /* Here the risk is to have 2 concurrent calls of the current function.*/
      Dem_NvMGateEntryInfo[OriginIdx].Status = DEM_NVM_PENDING;
      GateIsWaiting[OriginIdx] = TRUE;
    }
    else
    {
      GateIsWaiting[OriginIdx] = FALSE;
    }
  }

  /*
   * LEAVE critical section
   */
  DEM_EXIT_EXCLUSIVE_AREA();

  for (OriginIdx = 0U; OriginIdx < DEM_MAXNUM_ORIGINS; ++OriginIdx)
  {
    const NvM_BlockIdType NvDataBlockId = Dem_NvDataBlockId[OriginIdx];

    if (GateIsWaiting[OriginIdx] == TRUE)
    {
      Std_ReturnType ResultFromNvM;
      const Dem_SizeEvMemEntryType EntryIdx =
      Dem_NvMGateEntryInfo[OriginIdx].PendingEntryIdx;

      /* select corresponding NVRAM block dataset */
      ResultFromNvM = NvM_SetDataIndex(NvDataBlockId, EntryIdx);

      if (ResultFromNvM == E_OK)
      {
        /* queue write request of gate-entry to NvM - NvM_DstPtr is unused,
         * as permanent RAM block (gate-entry) is configured */
        ResultFromNvM = NvM_WriteBlock(NvDataBlockId, NULL_PTR);
      }

      if (ResultFromNvM != E_OK)
      {
        /* If there is a single error we need to know it for next actions
         * because otherwise we want to avoid entering an exclusive area. */
        NvMErrorHandlingNeeded = TRUE;
      }

      WriteBlockResult[OriginIdx] = ResultFromNvM;
    }
    else
    {
      /* Ensure initialization of all array positions
       * even if they may not be used. */
      WriteBlockResult[OriginIdx] = E_NOT_OK;
    }
  }

  if (NvMErrorHandlingNeeded == TRUE)
  {
    /*
     * ENTER critical section to protect the event memory entry
     *       call-context: Dem(Task), optional NvM(Task), Rte(Task)
     */
    DEM_ENTER_EXCLUSIVE_AREA();

    for (OriginIdx = 0U; OriginIdx < DEM_MAXNUM_ORIGINS; ++OriginIdx)
    {
      /* if write request for immediate storage was not accepted */
      if ((GateIsWaiting[OriginIdx] == TRUE)
          && (WriteBlockResult[OriginIdx] != E_OK))
      {
        const Dem_SizeEvMemEntryType EntryIdx =
        Dem_NvMGateEntryInfo[OriginIdx].PendingEntryIdx;

#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
        /* check if a ClearDTC request for this event memory is running */
        if ( (DEM_CLEARDTC_STATE_PROCESSING_NVRAM ==
                Dem_ClearDtcAsyncStatus.RunState) &&
            (OriginIdx == Dem_ClearDtcAsyncStatus.OriginIdx))
        {
          /* !LINKSTO Dem.ASR41.SWS_Dem_01057,1 */
          Dem_SetClearDTCResult(DEM_CLEAR_MEMORY_ERROR);
          Dem_ClearDtcAsyncStatus.EventMemWrite = DEM_NVM_IDLE;
          Dem_ClearDtcAsyncStatus.RunState = DEM_CLEARDTC_STATE_FINISHED;
        }
#endif
        /* mark entry as changed to store it during shutdown */
        Dem_EventMem[OriginIdx][EntryIdx].EntryStatus = DEM_ENTRY_CHANGED;

        /* set internal NvM gate status from PENDING back to IDLE */
        Dem_NvMGateEntryInfo[OriginIdx].Status = DEM_NVM_IDLE;
      }
    }

    /*
     * LEAVE critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();
  }

  DBG_DEM_CHECKFORTRIGGERNVMWRITEGATEENTRY_EXIT();
}

STATIC FUNC(boolean, DEM_CODE) Dem_StoreImmediatelyNext(uint8 OriginIdx)
{

  boolean PerformStoreImmediately = FALSE;

  DBG_DEM_STOREIMMEDIATELYNEXT_ENTRY(OriginIdx);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
  if ( (Dem_InitializationState != DEM_INITIALIZED) &&
       (Dem_InitializationState != DEM_POSTINITIALIZED) )
  {
    /* one of the NvM block callback function was triggered in an unexpected
       state of the Dem module, most probably because of an unwanted external
       Dem block write */
    DEM_REPORT_ERROR(DEM_SID_StoreImmediatelyNext, DEM_E_UNINIT);
  }
  else
#endif /* DEM_DEV_ERROR_DETECT */
  {
    /* in order to suppress conflicting parallel NvM-requests, the NvM single-
     * block callback must not be processed if it is invoked due to NvM write
     * within Dem_Shutdown() after the Dem module state has been advanced to
     * POSTINITIALIZED */
    if (Dem_InitializationState == DEM_INITIALIZED)
    {
      const Dem_SizeEvMemEntryType SizeEventMem = Dem_SizeEventMem[OriginIdx];
      const Dem_EventMemoryEntryPtrType EvMemEntry = Dem_EventMem[OriginIdx];
      Dem_SizeEvMemEntryType EntryIdx;
      Dem_SizeEvMemEntryType FoundEntryIdx = SizeEventMem;
#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
      boolean ClearedEntriesFound = FALSE;
#endif
#if ( (DEM_USE_EVENT_DISPLACEMENT == STD_ON) && \
      (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD) )
      Dem_OccOrderType MinOccOrder = DEM_MAX_OCC_ORDER;
#endif

      /*
       * ENTER critical section to protect the event memory
       *       call-context: NvM (Task)
       */
      DEM_ENTER_EXCLUSIVE_AREA();

     /* the gate has to be released inside the critical section, because the
      * possibly following re-occupation is done without an additional check */
      Dem_NvMGateEntryInfo[OriginIdx].Status = DEM_NVM_IDLE;

      for (EntryIdx = 0U; EntryIdx < SizeEventMem; ++EntryIdx)
      {
        /* check if an 'immediate write' status is set for the event entry */
        if (DEM_ENTRY_CLEAR_IMMEDIATELY == EvMemEntry[EntryIdx].EntryStatus)
        {
          /* select entry found */
          FoundEntryIdx = EntryIdx;

#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
          /* set flag that there are still entries to be cleared */
          ClearedEntriesFound = TRUE;
#endif

          /* stop searching, state CLEAR_IMMEDIATELY has highest prio */
          break;
        }
        else if (DEM_ENTRY_STORE_IMMEDIATELY ==
                  EvMemEntry[EntryIdx].EntryStatus)
        {
#if ( (DEM_USE_EVENT_DISPLACEMENT == STD_ON) && \
      (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD) )
          /* select entry with lowest occurrence order value to ensure correct
           * order at any time in case of occurrence order rearrangement */
          if (EvMemEntry[EntryIdx].OccOrder < MinOccOrder)
          {
            MinOccOrder = EvMemEntry[EntryIdx].OccOrder;
            FoundEntryIdx = EntryIdx;
            /* no break */
          }
#else
          /* select first entry found */
          FoundEntryIdx = EntryIdx;
          /* no break, continue searching for state CLEAR_IMMEDIATELY */
#endif /* (DEM_USE_EVENT_DISPLACEMENT == STD_ON) &&
          (DEM_EXTENDED_DATA_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD) */
        }
        else
        {
          /* state is CHANGED or UNCHANGED -> not handled immediately */
        }
      }

      /* next immediate-storage entry was found */
      if (FoundEntryIdx < SizeEventMem)
      {
        PerformStoreImmediately = TRUE;

        /* store this event memory entry persistently */
        Dem_StoreImmediately(OriginIdx, FoundEntryIdx);

        /* promote the status of the gate only if there
         * are information stored in the gate entry to
         * be written into the NvM by preparing the gate */
        Dem_NvMGateEntryInfo[OriginIdx].Status = DEM_NVM_WAITING;
      }
      /* else: all immediate-storage entries of this event memory are written */

#if (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH)
      /*
       * REUSE critical section to protect the ClearDtc Status
       *       call-context: NvM(Task)
       */

      /* check if a ClearDTC request for this event memory is finished */
      if ( (OriginIdx == Dem_ClearDtcAsyncStatus.OriginIdx) &&
           (FALSE == ClearedEntriesFound) )
      {
        Dem_ClearDtcAsyncStatus.EventMemWrite = DEM_NVM_IDLE;

        if (DEM_NVM_IDLE == Dem_ClearDtcAsyncStatus.EventStatusWrite)
        {
          /* if one of the preceding NvM write requests failed the RunState
           * has already been advanced to FAILED. Or, if Dcm cancelled the
           * operation, the RunState is already IDLE.
           * in both cases the RunState must not be modified anymore. */
          if (DEM_CLEARDTC_STATE_PROCESSING_NVRAM == Dem_ClearDtcAsyncStatus.RunState)
          {
            Dem_SetClearDTCResult(E_OK);
            Dem_ClearDtcAsyncStatus.RunState = DEM_CLEARDTC_STATE_FINISHED;
          }
        }
      }
#endif /* (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH) */
      /*
       * LEAVE critical section
       */
      DEM_EXIT_EXCLUSIVE_AREA();
    }
    else
    {
      /* after a successful write to NvM (followed by a call to
       * Dem_NvMGateEntryBlockCallback) the gate shall be released on all
       * execution paths, excepting those paths where the write has to be
       * continued and gate has to be moved into waiting state */
      Dem_NvMGateEntryInfo[OriginIdx].Status = DEM_NVM_IDLE;
    }
  }

  DBG_DEM_STOREIMMEDIATELYNEXT_EXIT(OriginIdx, PerformStoreImmediately);
  return PerformStoreImmediately;
}

FUNC(void, DEM_CODE) Dem_StoreImmediately(
  uint8                  OriginIdx,
  Dem_SizeEvMemEntryType EntryIdx)
{
  /* sizes of the gate-entry data
   * Incase no event data exist for any of the events of one event memory,
   * SizeGateEntryData[] will be 1 */
  const Dem_SizeEntryDataType SizeGateEntryData[DEM_MAXNUM_ORIGINS] =
  {
    DEM_SIZE_GATE_ENTRY_DATA_PRIMARY,
    DEM_SIZE_GATE_ENTRY_DATA_MIRROR,
    DEM_SIZE_GATE_ENTRY_DATA_PERMANENT,
    DEM_SIZE_GATE_ENTRY_DATA_SECONDARY
  };

  CONSTP2VAR(Dem_GateEntryBaseType, AUTOMATIC, DEM_VAR_CLEARED) GateEntryBase
    = Dem_NvGateEntryData[OriginIdx];
  const Dem_EventMemoryEntryPtrType EvMemEntry
    = &Dem_EventMem[OriginIdx][EntryIdx];

#if (DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON)
  Dem_GateEntryStorageOrderIdAndDTCStatusPtrType GateEntryStorageOrderId =
    Dem_GateEntryStorageOrderIdAndDTCStatus[OriginIdx];
#endif

#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE)
  CONSTP2VAR(Dem_GateEntryOBDFFPrimaryFragmentType, AUTOMATIC, DEM_VAR_CLEARED)
    GateOBDFFEntry = &Dem_NvGateEntryPrimaryData.OBDFFEntry;
#endif

#if ((DEM_NUM_FFSEGS > 0U) && ((DEM_NUM_J1939FFSPNS > 0U) && (DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON)))
  P2CONST(Dem_J1939FFClassType, AUTOMATIC, DEM_CONST) J1939FFClass;

  Dem_SizeEntryDataType SizeOfJ1939FF = 0U;

  Dem_SizeEntryDataType TotalSizeDataNoJ1939 = 0U;
#endif

  /* --- transfer event memory entry into gate-entry --- */

  const Dem_EventIdType EvId = EvMemEntry->EventId;

  Dem_SizeEntryDataType SizeUsedEntryData;

  DBG_DEM_STOREIMMEDIATELY_ENTRY(OriginIdx, EntryIdx);

  /* copy the event Id from event memory to gate-entry */
  GateEntryBase->EntryBase.EventId = EvId;

#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U)
  /* copy the root Id from event memory to gate-entry */
  GateEntryBase->EntryBase.RootId = EvMemEntry->RootId;
#endif

  /* check if this entry exists within the event memory */
  if (EvId != DEM_EVENT_ID_INVALID)
  {
#if (DEM_NUM_FFSEGS > 0U)
    Dem_FFIdxType MaxNumFF = Dem_GbiMaxNumFFRecs(EvId);
    Dem_FFIdxType NumFF = DEM_NUMFF(EvMemEntry, MaxNumFF);
    CONSTP2CONST(Dem_FFClassType, AUTOMATIC, DEM_CONST) FFClass =
      &Dem_FFClass[Dem_GbiFFClassIdx(EvId)];
#endif

    /* copy OccCtr and OccOrder from event memory entry */
    GateEntryBase->EntryBase.OccCtr = EvMemEntry->OccCtr;
    GateEntryBase->EntryBase.OccOrder = EvMemEntry->OccOrder;
#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
    /* copy SI30, FDC12, and OCCs from event memory entry */
    GateEntryBase->EntryBase.SI30 = EvMemEntry->SI30;
    GateEntryBase->EntryBase.FDC12 = EvMemEntry->FDC12;
    GateEntryBase->EntryBase.OCC1 = EvMemEntry->OCC1;
    GateEntryBase->EntryBase.OCC2 = EvMemEntry->OCC2;
    GateEntryBase->EntryBase.OCC3 = EvMemEntry->OCC3;
    GateEntryBase->EntryBase.OCC4 = EvMemEntry->OCC4;
    GateEntryBase->EntryBase.OCC6 = EvMemEntry->OCC6;
    GateEntryBase->EntryBase.OCC7 = EvMemEntry->OCC7;
    /* !LINKSTO dsn.Dem.OBD.OCC5.ExtensionDemStoreImmediatelyCurrentVal,1 */
#if ( DEM_VCC_OCC5_USED == STD_ON )
    GateEntryBase->EntryBase.OCC5 = EvMemEntry->OCC5;
#endif
#endif /* (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) */
#if (DEM_OPCYCLE_CTR_CSLF_SUPPORT == STD_ON)
    GateEntryBase->EntryBase.CSLF = EvMemEntry->CSLF;
#endif
#if (DEM_OPCYCLE_CTR_CSFF_SUPPORT == STD_ON)
    GateEntryBase->EntryBase.CSFF = EvMemEntry->CSFF;
#endif
#if (DEM_OPCYCLE_CTR_FAILEDCYCLES_SUPPORT == STD_ON)
    GateEntryBase->EntryBase.FAILEDCYCLES = EvMemEntry->FAILEDCYCLES;
#endif
#if (DEM_NUM_FAILURECYCLES > 0U)
    /* copy EventFailureCycleCounter from event memory entry */
    GateEntryBase->EntryBase.EventFailureCycleCounter =
      EvMemEntry->EventFailureCycleCounter;
#endif

#if (DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON)
    if (Dem_GbiImmediateStorage(EvId))
    {
      /* !LINKSTO dsn.Dem.IntermediateNvStorageOfDTCStatus.StorageOrderId.DataBlock,1 */
      /* update the StorageOrderId for event data block */
      Dem_GetNextStorageOrderId(GateEntryStorageOrderId,
        DEM_STORAGEORDERID_DATABLOCK);
      /* fill the current DTC status, or the current events status values of
       * the combined DTCs respectively */
      Dem_StoreDTCStatus(&GateEntryStorageOrderId[DEM_STARTPOS_DTC_STATUS], EvId);
    }
#endif /* (DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON) */

#if (DEM_OPCYC_OBD_DCY_USED == STD_ON)
    GateEntryBase->EntryBase.CDTCFlag =
      (DEM_IS_ANY_EV_ST_BIT_SET(EvId, DEM_UDS_STATUS_CDTC) ? TRUE : FALSE);
#endif

    SizeUsedEntryData = Dem_EvMemEntrySize(EvId, FALSE);

#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE)
    if (OriginIdx == (DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U))
    {
      if (Dem_GbiDTCKind(EvId) == DEM_DTC_KIND_EMISSION_REL_DTCS)
      {
        /* copy event memory OBD FF occurrence order into OBD gate-entry
         * occurrence order */
        GateOBDFFEntry->OBDFF.OBDOccOrder =
          DEM_OBDFF_ENTRY_OCCURRENCE(EntryIdx);

        /* copy event memory OBD FF data into OBD gate-entry data */
        TS_MemCpy(GateOBDFFEntry->OBDFF.OBDFFData,
                  DEM_OBDFF_ENTRY_FFDATA_LINK(EntryIdx),
                  DEM_SIZE_OBDFF_DATA);

#if (DEM_OBDONUDS_FF_SUPPORT == STD_ON)
        /* last occurrence of OBD FF only applicable for OBDONUDS */
        /* Deviation MISRAC2012-2 */
        if (DEM_GET_OBD_VARIANT() == DEM_OBD_VARIANT_OBDONUDS)
        {
          /* copy last OBD FF into OBD gate-entry data */
          TS_MemCpy(GateOBDFFEntry->OBDFF.OBDFFData2,
            DEM_OBDFF_ENTRY_FFDATA_2_LINK(EntryIdx),
            DEM_SIZE_OBDONUDS_OBD_FF);
        }
#endif
      }
    }
#endif /* (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE) */

#if (DEM_NUM_FFSEGS > 0U)
    /* write only the valid freeze frame data and J1939 Freeze Frame data */
#if ((DEM_NUM_J1939FFSPNS > 0U) && (DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON))
    J1939FFClass =
    &Dem_J1939FFClass[Dem_GbiJ1939FFClassIdx(EvMemEntry->EventId)];
    SizeOfJ1939FF = Dem_SizeOfJ1939FF(J1939FFClass);
    SizeUsedEntryData -= SizeOfJ1939FF;
    TotalSizeDataNoJ1939 = SizeUsedEntryData;
#endif
    SizeUsedEntryData -=
      (((Dem_SizeEntryDataType)MaxNumFF - NumFF) *
        Dem_SizeOfFF(DEM_REGULAR_FF, FFClass));
#endif

    if (Dem_GateEntryData[OriginIdx] != NULL_PTR)
    {
      /* Deviation TASKING-6 */
      if (SizeUsedEntryData > 0U)
      {
        /* copy event memory entry data into gate-entry data:
         * for the case when no event data exists for any of the events in this
         * event memory no copying takes place as SizeUsedEntryData is 0 */
        TS_MemCpy((Dem_EntryDataPtrType)Dem_GateEntryData[OriginIdx],
          &Dem_EntryData[OriginIdx][EvMemEntry->EntryDataPos], SizeUsedEntryData);
      }
#if ((DEM_NUM_FFSEGS > 0U) && ((DEM_NUM_J1939FFSPNS > 0U) && (DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON)))
      if (SizeOfJ1939FF > 0U)
      {
        /* copy J1939 event memory entry data into gate-entry data:
         * for the case when no J1939 event data exists for any of the events in this
         * event memory no copying takes place as SizeOfJ1939FF is 0 */
        TS_MemCpy((Dem_EntryDataPtrType)((uint8 *)Dem_GateEntryData[OriginIdx] + TotalSizeDataNoJ1939),
          &Dem_EntryData[OriginIdx][(EvMemEntry->EntryDataPos + TotalSizeDataNoJ1939)], SizeOfJ1939FF);
      }
#endif
    }
  }
  else /* reset gate-entry for an invalid event */
  {
    GateEntryBase->EntryBase.OccCtr = 0U;

    GateEntryBase->EntryBase.OccOrder = 0U;
#if (DEM_NUM_FAILURECYCLES > 0U)
    GateEntryBase->EntryBase.EventFailureCycleCounter = 0U;
#endif
#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
    GateEntryBase->EntryBase.SI30 = 0U;
    GateEntryBase->EntryBase.FDC12 = 0U;
    GateEntryBase->EntryBase.OCC1 = 0U;
    GateEntryBase->EntryBase.OCC2 = 0U;
    GateEntryBase->EntryBase.OCC3 = 0U;
    GateEntryBase->EntryBase.OCC4 = 0U;
    GateEntryBase->EntryBase.OCC6 = 0U;
    GateEntryBase->EntryBase.OCC7 = 0U;
    /* !LINKSTO dsn.Dem.OBD.OCC5.ExtensionDemStoreImmediatelyReset,1 */
#if ( DEM_VCC_OCC5_USED == STD_ON )
    GateEntryBase->EntryBase.OCC5 = 0U;
#endif
#endif /* DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD */
#if (DEM_OPCYCLE_CTR_CSLF_SUPPORT == STD_ON)
    GateEntryBase->EntryBase.CSLF = 0U;
#endif
#if (DEM_OPCYCLE_CTR_CSFF_SUPPORT == STD_ON)
    GateEntryBase->EntryBase.CSFF = 0U;
#endif
#if (DEM_OPCYCLE_CTR_FAILEDCYCLES_SUPPORT == STD_ON)
    GateEntryBase->EntryBase.FAILEDCYCLES = 0U;
#endif

    SizeUsedEntryData = 0U;
  }

  if (Dem_GateEntryData[OriginIdx] != NULL_PTR)
  {
    /* check if empty space remained in gate-entry after event entry is copied
     * to it:
     * - this occurs when current event data has a size lower than gate-entry
     *   size for that event memory
     * - when no event data exists for any of the events in this event memory
     *   -> there shall be only the empty entry of size 1 to be filled with 0
     */
    while (SizeUsedEntryData < SizeGateEntryData[OriginIdx])
    {
#if ((DEM_NUM_FFSEGS > 0U) && ((DEM_NUM_J1939FFSPNS > 0U) && (DEM_J1939_FREEZEFRAME_SUPPORT == STD_ON)))
      if ((SizeUsedEntryData < TotalSizeDataNoJ1939) || (SizeUsedEntryData >= (TotalSizeDataNoJ1939 + SizeOfJ1939FF)))
#endif
      {
        /* clear remaining GateEntryData[] with zero values */
        ((Dem_EntryDataPtrType) Dem_GateEntryData[OriginIdx])
                                  [SizeUsedEntryData] = 0U;
      }

      ++SizeUsedEntryData;
    }
  }

  /* --- prepare asynchronous transfer of gate-entry into NVRAM --- */

  /* protected access to these members */
  Dem_NvMGateEntryInfo[OriginIdx].PendingEntryIdx = (uint8)EntryIdx;

  /* mark entry as stored persistently */
  EvMemEntry->EntryStatus = DEM_ENTRY_UNCHANGED;

  DBG_DEM_STOREIMMEDIATELY_EXIT(OriginIdx, EntryIdx);
}

#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */

#if (DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON)
STATIC FUNC(void, DEM_CODE) Dem_StoreDTCStatus(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) DestBuffer,
  Dem_EventIdType                        EventId)
{
#if (DEM_NUM_CMB_DTCS > 0U)
  const Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
#endif
  DBG_DEM_STOREDTCSTATUS_ENTRY(DestBuffer, EventId);

#if (DEM_NUM_CMB_DTCS > 0U)
  if (DEM_IS_DTC_COMBINED(DTCConfIdx))
  {
    /* !LINKSTO Dem.IntermediateNvStorageOfDTCStatus.CombinedDTC,1 */
    /* store event status of all combined events */
    const Dem_CmbDTCEvLnkType LastCmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx + 1U] - 1U;
    Dem_CmbDTCEvLnkType CmbEvIdx;
    Dem_EventIdType CmbEventId;
    uint8 DTCStatusIdx = 0;

    for (CmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx]; CmbEvIdx <= LastCmbEvIdx; CmbEvIdx++)
    {
      CmbEventId = Dem_CmbDTCEvents[CmbEvIdx];
      DestBuffer[DTCStatusIdx] = DEM_DTC_STATUS_MASKS[CmbEventId];
      DTCStatusIdx++;
    }
  }
  else
#endif /* DEM_NUM_CMB_DTCS > 0U */
  {
    /* !LINKSTO Dem.IntermediateNvStorageOfDTCStatus.NonCombinedDTC,1 */
    *DestBuffer = DEM_DTC_STATUS_MASKS[EventId];
  }

  DBG_DEM_STOREDTCSTATUS_EXIT(DestBuffer, EventId);
}
#endif /* DEM_INTERMEDIATE_STORAGE_DTC_STATUS == STD_ON */
/*------------------[aging]-------------------------------------------------*/

#if (DEM_USE_AGING == STD_ON)
FUNC(void, DEM_CODE) Dem_ClearAgedEventEntry(
  Dem_EventIdType             EventId,
  Dem_EventMemoryEntryPtrType EvMemEntry)
{
  /* initialize status mask with CDTC bit, since it will
   * always be cleared on aging */
  /* !LINKSTO Dem.SWS_Dem_00498,1 */
  uint8 EventStatusClearMask = DEM_UDS_STATUS_CDTC;

  DBG_DEM_CLEARAGEDEVENTENTRY_ENTRY(EventId, EvMemEntry);

  Dem_ClearEventEntry(EvMemEntry);

#if (DEM_RESET_PENDING_BIT_ON_OVERFLOW_SUPPORT == STD_ON)
  /* !LINKSTO dsn.Dem.SelectablePDTC.ClearAgedEventEntry,1 */
  /* usually already cleared after first passed cycle */
  EventStatusClearMask |= DEM_UDS_STATUS_PDTC;
#endif

#if (DEM_RESET_CONFIRMED_BIT_ON_OVERFLOW_SUPPORT_FAULT_CONFIRMATION == STD_ON)
  /* reset failure counter for regular & combined events */
  /* usually already cleared after first passed cycle */
  Dem_ResetStatusCounter(EventId);
#endif

  /* clear TestFailedSinceLastClear (only if configured) */
#if (DEM_STATUS_BIT_HANDLING_TESTFAILEDSINCELASTCLEAR == \
      DEM_STATUS_BIT_AGING_AND_DISPLACEMENT)
  EventStatusClearMask |= DEM_UDS_STATUS_TFSLC;
#endif

  DEM_CLR_EV_ST_MASK(EventId, EventStatusClearMask);

  DBG_DEM_CLEARAGEDEVENTENTRY_EXIT(EventId, EvMemEntry);
}
#endif /* DEM_USE_AGING */

/*==================[internal function definitions]=========================*/

/*------------------[reset debounce status]---------------------------------*/

#if (DEM_NUM_DEBOUNCE_TIME > 0U)
STATIC FUNC(void, DEM_CODE) Dem_ResetDebounceTimeBased(
  Dem_EventIdType EventId)
{
  const Dem_EventIdType DebounceIdx = Dem_GbiDebounceIdx(EventId);
  CONSTP2VAR(Dem_DebounceTimeStatusType, AUTOMATIC, DEM_VAR_CLEARED)
    DebounceStatus = &Dem_DebounceTimeStatus[DebounceIdx];

  DBG_DEM_RESETDEBOUNCETIMEBASED_ENTRY(EventId);

  /* (re-)initialize Dem_DebounceTimeStatus */
  DebounceStatus->InternalTimer = 0U;
  DebounceStatus->Direction = DEM_EVENT_STATUS_UNQUALIFIED;
  DebounceStatus->FreezeStatus = FALSE;

  DBG_DEM_RESETDEBOUNCETIMEBASED_EXIT(EventId);
}

STATIC FUNC(void, DEM_CODE) Dem_FreezeDebounceTimeBased(
  Dem_EventIdType EventId)
{
  const Dem_EventIdType DebounceIdx = Dem_GbiDebounceIdx(EventId);
  CONSTP2VAR(Dem_DebounceTimeStatusType, AUTOMATIC, DEM_VAR_CLEARED)
    DebounceStatus = &Dem_DebounceTimeStatus[DebounceIdx];

  DBG_DEM_FREEZEDEBOUNCETIMEBASED_ENTRY(EventId);

  /* set freeze status to TRUE -> freeze event debouncing */
  DebounceStatus->FreezeStatus = TRUE;

  DBG_DEM_FREEZEDEBOUNCETIMEBASED_EXIT(EventId);
}
#endif /* (DEM_NUM_DEBOUNCE_TIME > 0U) */

#if (DEM_NUM_DEBOUNCE_COUNTER > 0U)
STATIC FUNC(void, DEM_CODE) Dem_ResetDebounceCounterBased(
  Dem_EventIdType EventId)
{
  const Dem_EventIdType DebounceStatusIdx = Dem_GbiDebounceStatusIdx(EventId);

  DBG_DEM_RESETDEBOUNCECOUNTERBASED_ENTRY(EventId);

  /* (re-)initialize Dem_DebounceCounterStatus */
  Dem_DebounceCounterStatus[DebounceStatusIdx] = 0;

  DBG_DEM_RESETDEBOUNCECOUNTERBASED_EXIT(EventId);
}

STATIC FUNC(void, DEM_CODE) Dem_FreezeDebounceCounterBased(Dem_EventIdType EventId)
{
  DBG_DEM_FREEZEDEBOUNCECOUNTERBASED_ENTRY(EventId);

  /* dummy function, do nothing */
  TS_PARAM_UNUSED(EventId);

  DBG_DEM_FREEZEDEBOUNCECOUNTERBASED_EXIT(EventId);
}

#endif /* (DEM_NUM_DEBOUNCE_COUNTER > 0U) */

#if (DEM_NUM_DEBOUNCE_FREQUENCY > 0U)
STATIC FUNC(void, DEM_CODE) Dem_ResetDebounceFrequencyBased(
  Dem_EventIdType EventId)
{
  const Dem_EventIdType DebounceIdx = Dem_GbiDebounceIdx(EventId);
  CONSTP2VAR(Dem_DebounceFrequencyStatusType, AUTOMATIC, DEM_VAR_CLEARED)
    DebounceStatus = &Dem_DebounceFrequencyStatus[DebounceIdx];

  DBG_DEM_RESETDEBOUNCEFREQUENCYBASED_ENTRY(EventId);

  /* (re-)initialize Dem_DebounceFrequencyStatus */
  DebounceStatus->InternalTimer = 0U;
  DebounceStatus->FreezeStatus = FALSE;
  /* not necessary to reset DebounceStatus->PassedCounter (= 0) */
  /* not necessary to reset DebounceStatus->FailedCounter (= 0) */
  DebounceStatus->Status   = DEM_EVENT_STATUS_UNQUALIFIED;

  DBG_DEM_RESETDEBOUNCEFREQUENCYBASED_EXIT(EventId);
}

STATIC FUNC(void, DEM_CODE) Dem_FreezeDebounceFrequencyBased(
  Dem_EventIdType EventId)
{
  const Dem_EventIdType DebounceIdx = Dem_GbiDebounceIdx(EventId);
  CONSTP2VAR(Dem_DebounceFrequencyStatusType, AUTOMATIC, DEM_VAR_CLEARED)
    DebounceStatus = &Dem_DebounceFrequencyStatus[DebounceIdx];

  DBG_DEM_FREEZEDEBOUNCEFREQUENCYBASED_ENTRY(EventId);

  /* set freeze status to TRUE -> freeze event debouncing */
  DebounceStatus->FreezeStatus = TRUE;

  DBG_DEM_FREEZEDEBOUNCEFREQUENCYBASED_EXIT(EventId);
}
#endif /* (DEM_NUM_DEBOUNCE_FREQUENCY > 0U) */

STATIC FUNC(void, DEM_CODE) Dem_ResetDebounceMonitor(Dem_EventIdType EventId)
{
  DBG_DEM_RESETDEBOUNCEMONITOR_ENTRY(EventId);

  /* dummy function, do nothing */
  TS_PARAM_UNUSED(EventId);

  DBG_DEM_RESETDEBOUNCEMONITOR_EXIT(EventId);
}

/*------------------[debounce an event entry]-------------------------------*/

#if (DEM_NUM_DEBOUNCE_COUNTER > 0U)
STATIC FUNC(void, DEM_CODE) Dem_DebounceEventCounterBased(
  Dem_EventIdType                                      EventId,
  P2VAR(Dem_EventStatusType, AUTOMATIC, DEM_APPL_DATA) EventStatus)
{
  const Dem_EventIdType DebounceStatusIdx = Dem_GbiDebounceStatusIdx(EventId);
  const Dem_DebounceCounterClassIdxType DebounceClassIdx =
    Dem_GbiDebounceCounterClassIdx(DebounceStatusIdx);

  CONSTP2CONST(Dem_DebounceCounterClassType, AUTOMATIC, DEM_CONST)
    DebounceCfg = &Dem_DebounceCounterClass[DebounceClassIdx];

  CONSTP2VAR(Dem_DebounceCounterStatusType, AUTOMATIC, DEM_VAR_CLEARED)
    DebounceCounter = &Dem_DebounceCounterStatus[DebounceStatusIdx];

  DBG_DEM_DEBOUNCEEVENTCOUNTERBASED_ENTRY(EventId, EventStatus);

  /*
   * ENTER critical section to protect debounce status
   *       call-context: any
   */
  DEM_ENTER_EXCLUSIVE_AREA();

  switch (*EventStatus)
  {
    case DEM_EVENT_STATUS_PREPASSED:
      /* jump-down enabled and counter value is greater than configured
       * jump-down value */
      if ( (DebounceCfg->JumpDown != FALSE) &&
           (*DebounceCounter > DebounceCfg->JumpDownValue) )
      {
        /* jump down (and step down in action below) */
        *DebounceCounter = DebounceCfg->JumpDownValue;
      }

      if ( *DebounceCounter > (DebounceCfg->CounterPassedThreshold +
                               (sint16)DebounceCfg->CountDecStepSize) )
      {
        /* step down */
        *DebounceCounter -= (sint16)DebounceCfg->CountDecStepSize;
      }
      else
      {
        /* step down to threshold: qualify event as passed */
        *DebounceCounter = DebounceCfg->CounterPassedThreshold;
        *EventStatus = DEM_EVENT_STATUS_PASSED;
      }
      break;

    case DEM_EVENT_STATUS_PREFAILED:
      /* jump-up enabled and counter value is less than configured
       * jump-up value */
      if ( (DebounceCfg->JumpUp != FALSE) &&
           (*DebounceCounter < DebounceCfg->JumpUpValue) )
      {
        /* jump up (and step up in action below) */
        *DebounceCounter = DebounceCfg->JumpUpValue;
      }

      if ( *DebounceCounter < (DebounceCfg->CounterFailedThreshold -
                               (sint16)DebounceCfg->CountIncStepSize) )
      {
        /* step up */
        *DebounceCounter += (sint16)DebounceCfg->CountIncStepSize;

#if ( (DEM_FREEZE_FRAME_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) || \
      (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) )
        if (*DebounceCounter >= DebounceCfg->CounterUnconfirmedThreshold)
        {
          *EventStatus = DEM_EVENT_STATUS_UNCONFIRMED;
        }
#endif
      }
      else
      {
        /* step up to threshold: qualify event as failed */
        *DebounceCounter = DebounceCfg->CounterFailedThreshold;
        *EventStatus = DEM_EVENT_STATUS_FAILED;
      }
      break;

    case DEM_EVENT_STATUS_PASSED:

      *DebounceCounter = DebounceCfg->CounterPassedThreshold;

      break;

    default: /* DEM_EVENT_STATUS_FAILED */

      *DebounceCounter = DebounceCfg->CounterFailedThreshold;

      break;
  } /* event status */

  /*
   * LEAVE critical section
   */
  DEM_EXIT_EXCLUSIVE_AREA();

  DBG_DEM_DEBOUNCEEVENTCOUNTERBASED_EXIT(EventId, EventStatus);
}
#endif /* (DEM_NUM_DEBOUNCE_COUNTER > 0U) */

#if (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
STATIC FUNC(void, DEM_CODE) Dem_ProcessUnconfirmedThreshold(
  Dem_EventIdType     EventId,
  Dem_EventStatusType EventStatus)
{
  DBG_DEM_PROCESSUNCONFIRMEDTHRESHOLD_ENTRY(EventId, EventStatus);

  /* verify initialization-status before performing any actions */
  if (Dem_InitializationState == DEM_INITIALIZED)
  {
    sint8 FDC = DEM_FDC_VALUE_FAILED;

    Dem_EventStatusChangedMsgType EventStatusChangedMsg =
      {
        DEM_EVENT_ID_INVALID, 0U, 0U,
#if (DEM_NUM_CMB_DTCS > 0U)
        FALSE
#endif
      };

#if (DEM_NUM_DEBOUNCE_COUNTER > 0U)
    if (EventStatus != DEM_EVENT_STATUS_PASSED)
    {
      if (EventStatus == DEM_EVENT_STATUS_UNCONFIRMED)
      {
        (void)Dem_GetFaultDetectionCounter(EventId, &FDC);
      }
    }
#endif

    /*
     * ENTER critical section
     */
    DEM_ENTER_EXCLUSIVE_AREA();

    if (EventStatus == DEM_EVENT_STATUS_PASSED)
    {
      Dem_ProcessUnconfirmedPassed(EventId, &EventStatusChangedMsg);
    }
    else
    {
      /* EventStatus can be only unconfirmed or failed, as unqualified values
       * are excluded in the caller function */
      Dem_ProcessUnconfirmedFailed(EventId, EventStatus, (uint8)FDC);
    }

    /*
     * LEAVE critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();

#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
    /* notify application about event status change */
    if (DEM_EVENT_ID_INVALID != EventStatusChangedMsg.EventId)
    {
      Dem_CbTriggerOnEventStatus(EventStatusChangedMsg.EventId,
                                 EventStatusChangedMsg.OldStatusMask,
                                 EventStatusChangedMsg.NewStatusMask);
    }
#endif
  } /* else: event memory not available yet, do nothing */

  DBG_DEM_PROCESSUNCONFIRMEDTHRESHOLD_EXIT(EventId, EventStatus);
}

STATIC FUNC(void, DEM_CODE) Dem_ProcessUnconfirmedPassed(
  Dem_EventIdType                  EventId,
  Dem_EventStatusChangedMsgPtrType EventStatusChangedMsgPtr)
{
  Dem_EventMemoryEntryPtrType EvMemEntry;
  Dem_SizeEvMemEntryType EvMemEntryIdx;

  /* clear event id, status message is not used in all branches */
  EventStatusChangedMsgPtr->EventId = DEM_EVENT_ID_INVALID;

  /* search for DTC in event memory */
  if (Dem_SearchForEntry(EventId, &EvMemEntry, &EvMemEntryIdx) == TRUE)
  {
    boolean PassedEntryInErrorQueue = FALSE;
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    boolean EvMemEntryChanged = FALSE;
#endif
    if (Dem_GbiEventKind(EventId) == DEM_EVENT_KIND_BSW)
    {
      PassedEntryInErrorQueue = Dem_CheckErrorQueueEntryForStatus(EventId, DEM_EVENT_STATUS_PASSED);
    }

    /* check if this passed event is the very first in this operations cycle
     * it means there were:
     * - no 'uncomplete' passed BSW event in the ErrorQueue,
     * - no complete failed or complete passed TOC (no asynchron processed TNCTOC bit)
     * - no unconfirmed and no 'uncomplete' failed (no synchron processed unconfirmedDTC_TOC bit) */
    if ( (PassedEntryInErrorQueue == FALSE) &&
         (DEM_IS_EV_ST_BIT_TNCTOC_SET(EventId)) &&
         (!DEM_IS_ANY_BIT_SET(EvMemEntry->SI30, DEM_SI30_STATUS_UNCONFIRMEDDTC_TOC)) )
    {
      if (EvMemEntry->OCC2 < 0xFFU)
      {
        /* increment unconfirmedDTC aging counter */
        /* regarding healing: indicator link counter role is processed at
         * operation cycle restart (after completed healing cycle) */
        ++(EvMemEntry->OCC2);
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
        EvMemEntryChanged = TRUE;
#endif

#if (DEM_USE_AGING == STD_ON)
        if (DEM_AGING_ALLOWED(EventId))
        {
          const Dem_AgingCyclesType agingCycleCounterThreshold =
            Dem_GbiNumAgingCycles(EventId);
          boolean AgingConditionFulfilled = FALSE;

#if ((DEM_OBD_Support == STD_ON) && (DEM_VCC_OCC5_USED == STD_ON))
          /* retain DTC kind to check for emission-related DTCs */
          const Dem_DTCKindType DTCKind = Dem_GbiDTCKind(EventId);

          /* check whether dedicated condition for aging is fulfilled */
          if (DTCKind == DEM_DTC_KIND_EMISSION_REL_DTCS)
          {
            const Dem_AgingCyclesType obdAgingCycleCounterThreshold =
              Dem_GbiOBDAgingCycleCounterThreshold(EventId);

            /* no need to check Dem_EventClass[].AgingAllowed because
             * Dem_GbiAgingAllowed() has check this already */
            /* !LINKSTO VCC_DEM_007_Req181v1,1 */
            if (DEM_OBD_AGING_ALLOWED(obdAgingCycleCounterThreshold))
            {
              uint8_least UnfinishedWUC = 0U;
              if ((EvMemEntry->OCC5 != 0U) &&
                  (DEM_OPCYCLESTATE[DEM_OPCYC_WARMUP_ID] == DEM_CYCLE_STATE_START))
              {
                UnfinishedWUC = 1U;
              }
              if ((EvMemEntry->OCC2 >= agingCycleCounterThreshold) &&
                  ((EvMemEntry->OCC5 - UnfinishedWUC) >= obdAgingCycleCounterThreshold) )
              {
                AgingConditionFulfilled = TRUE;
              }
            }
          }
          else
#endif /* ((DEM_OBD_Support == STD_ON) && (DEM_VCC_OCC5_USED == STD_ON)) */
          {
            /* unconfirmedDTC aging counter reaches aging threshold */
            /* note: counter is always > 0 here regarding the case if aging is not
             * configured (i.e. NumAgingCycles = 0) */
            if (EvMemEntry->OCC2 >= agingCycleCounterThreshold)
            {
              AgingConditionFulfilled = TRUE;
            }
          }

          if (AgingConditionFulfilled == TRUE)
          {
#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
            EventStatusChangedMsgPtr->OldStatusMask =
              DEM_DTC_STATUS_MASKS[EventId];
#endif

            Dem_ProcessEventAging(EventId, EvMemEntry);

#if (DEM_USE_CB_TRIG_ON_STATUS_CHANGE == STD_ON)
            EventStatusChangedMsgPtr->NewStatusMask =
              DEM_DTC_STATUS_MASKS[EventId];

            if (EventStatusChangedMsgPtr->OldStatusMask !=
                EventStatusChangedMsgPtr->NewStatusMask)
            {
              EventStatusChangedMsgPtr->EventId = EventId;
            }
#endif
          }
          /* else: aging is not configured for this event:
           *       aging bits won't change due to aging condition */
        }
        /* else: aging is not allowed for this event */
#endif /* (DEM_USE_AGING == STD_ON) */
      }

      if (EvMemEntry->OCC7 < 0xFFU)
      {
        /* increment qualified/unconfirmedDTC operation cycle counter */
        ++(EvMemEntry->OCC7);
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
        EvMemEntryChanged = TRUE;
#endif
      }
    }

    /* clear UnconfirmedDTC bit */
    if (DEM_IS_ANY_BIT_SET(EvMemEntry->SI30, DEM_SI30_STATUS_UNCONFIRMEDDTC))
    {
      DEM_CLR_MASK_8(EvMemEntry->SI30, DEM_SI30_STATUS_UNCONFIRMEDDTC);
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
      EvMemEntryChanged = TRUE;
#endif
    }

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    if (EvMemEntryChanged == TRUE)
    {
      /* !LINKSTO dsn.Dem.VCC.EventMemoryEntryChanged,4 */
      Dem_CheckForImmediateEntryStorage(EventId,
                                        EvMemEntry,
                                        EvMemEntryIdx,
                                        DEM_NVM_NO_FORCE);
    }
#endif

 }
}

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
STATIC FUNC(boolean, DEM_CODE) Dem_CheckForChangesByUnconfirmedFailedForSI30(
  Dem_EventMemoryEntryPtrType EvMemEntry)
{
  boolean EvMemEntryChanged = FALSE;
  if ( (!DEM_IS_EACH_BIT_SET(EvMemEntry->SI30, DEM_SI30_STATUS_UNCONFIRMEDDTC|
                             DEM_SI30_STATUS_UNCONFIRMEDDTC_TOC|
                             DEM_SI30_STATUS_UNCONFIRMEDDTC_SLC)) ||
        (EvMemEntry->OCC2 != 0U) )
  {
    EvMemEntryChanged = TRUE;
  }
  return EvMemEntryChanged;
}
#endif

STATIC FUNC(void, DEM_CODE) Dem_ProcessUnconfirmedFailed(
  Dem_EventIdType     EventId,
  Dem_EventStatusType EventStatus,
  uint8               FDC)
{
  boolean FirstUnconfirmedTOC = FALSE;
  Dem_EventMemoryEntryPtrType EvMemEntry;
  Dem_SizeEvMemEntryType EvMemEntryIdx;
  boolean EventFound = FALSE;

  /* search for DTC in event memory */
  if (Dem_SearchForEntry(EventId, &EvMemEntry, &EvMemEntryIdx) == TRUE)
  {
    /* event is not aged */
    if (((EvMemEntry)->SI30 & DEM_SI30_STATUS_AGEDDTC) == 0U)
    {
      EventFound = TRUE;
    }
    else /* event found, but aged: delete it and start with clear data */
    {
      /* clear event entry data of aged entry */
      Dem_ClearEventEntry(EvMemEntry);

      /* EventFound remains FALSE */
    }
  } /* else EventFound remains FALSE - event not found */

  /* event is found and it is not aged */
  if (EventFound == TRUE)
  {
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    boolean EvMemEntryChanged = Dem_CheckForChangesByUnconfirmedFailedForSI30(EvMemEntry);
#endif

    if (!DEM_IS_ANY_BIT_SET(EvMemEntry->SI30, DEM_SI30_STATUS_UNCONFIRMEDDTC_TOC))
    {
      FirstUnconfirmedTOC = TRUE;

      Dem_ProcessFirstUnconfirmedTOC(EventId, EvMemEntry);
    }

#if (DEM_SUPPORT_FIM_ON_FDC_TRESHOLD == STD_ON)
    /* trigger only on rising bit */
    if (!DEM_IS_ANY_BIT_SET(EvMemEntry->SI30, DEM_SI30_STATUS_UNCONFIRMEDDTC))
    {
      /* trigger FiM with Unconfirmed status */
      (void)FiM_DemTriggerOnUnconfirmed(EventId);
    }
#endif

    /* set UnconfirmedDTC & -TOC & -SLC bits */
    DEM_SET_MASK(EvMemEntry->SI30,
                 DEM_SI30_STATUS_UNCONFIRMEDDTC     |
                 DEM_SI30_STATUS_UNCONFIRMEDDTC_TOC |
                 DEM_SI30_STATUS_UNCONFIRMEDDTC_SLC);

    /* reset unconfirmedDTC aging counter */
    EvMemEntry->OCC2 = 0U;

    /* check for first failed in this OpCyc */
    if (EventStatus == DEM_EVENT_STATUS_FAILED)
    {
      /* set TestFailedSinceLastClear/Aged bit */
      DEM_SET_MASK(EvMemEntry->SI30, DEM_SI30_STATUS_TFSLC_AGED);

#if (DEM_OBD_Support == STD_ON)
      /* set EmissionRelatedDTC bit (Si30.Bit6) */
      if (Dem_GbiDTCKind(EventId) == DEM_DTC_KIND_EMISSION_REL_DTCS)
      {
        DEM_SET_MASK(EvMemEntry->SI30, DEM_SI30_STATUS_EMISSIONRELATEDDTC);
      }
#endif

      if ( (!(DEM_IS_EV_ST_BIT_TFTOC_SET(EventId))) &&
           (EvMemEntry->OCC6 < 0xFFU)
         )
      {
        /* consider only the first failed BSW event in this operation cycle */
        if ( (Dem_GbiEventKind(EventId) != DEM_EVENT_KIND_BSW) ||
             (Dem_CheckErrorQueueEntryForStatus(
              EventId, DEM_EVENT_STATUS_FAILED) == FALSE)
           )
        {
          /* increment consecutive failed operation cycle counter
           * (eventually continuing from value 1 set at event memory
           * entry creation on failed) */
          ++(EvMemEntry->OCC6);
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
          EvMemEntryChanged = TRUE;
#endif
        }
      }
      FDC = DEM_FDC_VALUE_FAILED;
    }
    /* update maximum fault detection counter since last clear */
    if (EvMemEntry->FDC12 < FDC)
    {
      EvMemEntry->FDC12 = FDC;
#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
      EvMemEntryChanged = TRUE;
#endif
    }

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)
    if (EvMemEntryChanged == TRUE)
    {
      /* !LINKSTO dsn.Dem.VCC.EventMemoryEntryChanged,4 */
      Dem_CheckForImmediateEntryStorage(EventId,
                                        EvMemEntry,
                                        EvMemEntryIdx,
                                        DEM_NVM_NO_FORCE);
    }
#endif
  }
  else /* entry is not yet stored in event memory */
  {
    if (EventStatus != DEM_EVENT_STATUS_FAILED)
    {
      if (Dem_CheckErrorQueueEntryForStatus(
          EventId, DEM_EVENT_STATUS_UNCONFIRMED) == FALSE)
      {
        /* event was not yet queued as unconfirmed */
        FirstUnconfirmedTOC = TRUE;
      }
    }
  }

  /* first time in this operation cycle */
  if (FirstUnconfirmedTOC == TRUE)
  {
    Dem_EventInfoType EventInfo;
#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U)
    EventInfo.RootId = EventId;
#endif
    EventInfo.EventId = EventId;

    /* queue unconfirmed event */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#if (DEM_STORE_INTERNAL_EVENTS == STD_OFF)
    if (DEM_VALID_DTC_FOR_EVENT_STORAGE(EventId))
#endif
    {
      if (Dem_WriteErrorQueueEntry(EventInfo,
                                   DEM_EVENT_STATUS_UNCONFIRMED,
                                   FALSE) == FALSE)
      {
        DEM_REPORT_ERROR(DEM_SID_ProcessUnconfirmedThreshold,
          DEM_E_WRONG_CONFIGURATION);
      }
    }
#else
#if (DEM_STORE_INTERNAL_EVENTS == STD_OFF)
    if (DEM_VALID_DTC_FOR_EVENT_STORAGE(EventId))
#endif
    {
      /* return value is used for error detection in Det only */
      (void)Dem_WriteErrorQueueEntry(
          EventInfo, DEM_EVENT_STATUS_UNCONFIRMED, FALSE);
    }
#endif /* DEM_DEV_ERROR_DETECT */
  }
}

STATIC FUNC(void, DEM_CODE) Dem_ProcessFirstUnconfirmedTOC(
  Dem_EventIdType             EventId,
  Dem_EventMemoryEntryPtrType EvMemEntry)
{
  boolean PassedEntryInErrorQueue = FALSE;

  if (Dem_GbiEventKind(EventId) == DEM_EVENT_KIND_BSW)
  {
    PassedEntryInErrorQueue =
      Dem_CheckErrorQueueEntryForStatus(EventId, DEM_EVENT_STATUS_PASSED);
  }

  /* reset operation cycles since last unconfirmedDTC counter */
  /* counter needs to be reset only once per OpCyc
   * (at first unconfirmed), because it is incremented on OpCyc start */
  EvMemEntry->OCC1 = 0U;

  /* increment unconfirmedDTC operation cycle counter
   * (continuing from value 1 set at event memory entry creation) */
  if (EvMemEntry->OCC4 < 0xFFU)
  {
    ++(EvMemEntry->OCC4);
  }

  /* check for first unconfirmed/failed without any passed in this OpCyc */
  if ( (PassedEntryInErrorQueue == FALSE) &&
       (DEM_IS_EV_ST_BIT_TNCTOC_SET(EventId)) &&
       (EvMemEntry->OCC7 < 0xFFU)
     )
  {
    /* increment qualified/unconfirmedDTC operation cycle counter */
    ++(EvMemEntry->OCC7);
  }
}
#endif /* (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) */

#if (DEM_NUM_DEBOUNCE_FREQUENCY > 0U)
STATIC FUNC(void, DEM_CODE) Dem_DebounceEventFrequencyBased(
  Dem_EventIdType                                      EventId,
  P2VAR(Dem_EventStatusType, AUTOMATIC, DEM_APPL_DATA) EventStatus)
{
  const Dem_EventIdType DebounceIdx = Dem_GbiDebounceIdx(EventId);
  CONSTP2CONST(Dem_DebounceFrequencyCfgType, AUTOMATIC, DEM_CONST)
    DebounceCfg = &Dem_DebounceFrequencyCfg[DebounceIdx];
  CONSTP2VAR(Dem_DebounceFrequencyStatusType, AUTOMATIC, DEM_VAR_CLEARED)
    DebounceStatus = &Dem_DebounceFrequencyStatus[DebounceIdx];

  DBG_DEM_DEBOUNCEEVENTFREQUENCYBASED_ENTRY(EventId, EventStatus);

  /*
   * ENTER critical section to protect debounce status
   *       call-context: any
   */
  DEM_ENTER_EXCLUSIVE_AREA();

  switch (*EventStatus)
  {
    case DEM_EVENT_STATUS_PREPASSED:

      if (DebounceStatus->InternalTimer == 0U)
      {
        /* timer not running -> start timer */
        DebounceStatus->InternalTimer = DebounceCfg->TimeWindowDuration;
        DEM_RESETFREQBASEDCOUNTERS(DebounceStatus);
      }

      if ( DebounceStatus->PassedCounter <
           DebounceCfg->ThresholdBeforeEvPassed )
      {
        DebounceStatus->PassedCounter++;
      }
      else /* passed-threshold reached */
      {
        /* qualify event as PASSED */
        DebounceStatus->Status = DEM_EVENT_STATUS_PASSED;
        /* not necessary to perform DebounceStatus->PassedCounter++ */
        DebounceStatus->InternalTimer = 0U;
        *EventStatus = DEM_EVENT_STATUS_PASSED;
      }

      break;

    case DEM_EVENT_STATUS_PREFAILED:

      if (DebounceStatus->InternalTimer == 0U)
      {
        /* timer not running -> start timer */
        DebounceStatus->InternalTimer = DebounceCfg->TimeWindowDuration;
          DEM_RESETFREQBASEDCOUNTERS(DebounceStatus);
      }

      if ( DebounceStatus->FailedCounter <
           DebounceCfg->ThresholdBeforeEvFailed )
      {
        DebounceStatus->FailedCounter++;
      }
      else /* failed-threshold reached */
      {
        /* qualify event as FAILED */
        DebounceStatus->Status = DEM_EVENT_STATUS_FAILED;
        /* not necessary to perform DebounceStatus->FailedCounter++ */
        DebounceStatus->InternalTimer = 0U;
        *EventStatus = DEM_EVENT_STATUS_FAILED;
      }

      break;

    case DEM_EVENT_STATUS_PASSED:

      /* stop timer, set "passed" FDC */
      DebounceStatus->InternalTimer = 0U;
      DebounceStatus->Status = DEM_EVENT_STATUS_PASSED;

      break;

    default: /* DEM_EVENT_STATUS_FAILED */

      /* stop timer, set "failed" FDC */
      DebounceStatus->InternalTimer = 0U;
      DebounceStatus->Status = DEM_EVENT_STATUS_FAILED;

      break;
  } /* event status */

  /* "unfreeze" event debouncing */
  DebounceStatus->FreezeStatus = FALSE;

  /*
   * LEAVE critical section
   */
  DEM_EXIT_EXCLUSIVE_AREA();

  DBG_DEM_DEBOUNCEEVENTFREQUENCYBASED_EXIT(EventId, EventStatus);
}
#endif /* (DEM_NUM_DEBOUNCE_FREQUENCY > 0U) */

#if (DEM_NUM_DEBOUNCE_TIME > 0U)
STATIC FUNC(void, DEM_CODE) Dem_DebounceEventTimeBased(
  Dem_EventIdType                                      EventId,
  P2VAR(Dem_EventStatusType, AUTOMATIC, DEM_APPL_DATA) EventStatus)
{
  /* Get the Debounce Configuration Index from the Event Description */
  const Dem_EventIdType DebounceIdx = Dem_GbiDebounceIdx(EventId);

  /* Get the Time Debounce Class index */
  const Dem_DebounceTimeClassIdxType DebounceClassIdx = Dem_GbiDebounceTimeClassIdx (DebounceIdx);

  /* Get  pointer to the Time Debounce Class */
  CONSTP2CONST(Dem_DebounceTimeClassType, AUTOMATIC, DEM_CONST)
    DebounceClassCfg = &Dem_DebounceTimeClass[DebounceClassIdx];

  CONSTP2VAR(Dem_DebounceTimeStatusType, AUTOMATIC, DEM_VAR_CLEARED)
    DebounceStatus = &Dem_DebounceTimeStatus[DebounceIdx];

  DBG_DEM_DEBOUNCEEVENTTIMEBASED_ENTRY(EventId, EventStatus);

  /*
   * ENTER critical section to protect debounce status
   *       call-context: any
   */
  DEM_ENTER_EXCLUSIVE_AREA();

  switch (*EventStatus)
  {
    case DEM_EVENT_STATUS_PREPASSED:

      /*
       * if either
       *  - the timer is already running, but as a "failed" timer
       * or
       *  - the timer is not running and the event has not been qualified
       *    as "passed" yet
       * then the "passed" timer must be (re-)started
       */
      if ( ( (DebounceStatus->InternalTimer != 0U) &&
             (DebounceStatus->Direction == DEM_EVENT_STATUS_FAILED)
           ) ||
           ( (DebounceStatus->InternalTimer == 0U) &&
             (DebounceStatus->Direction != DEM_EVENT_STATUS_PASSED)
           )
         )
      {
        /* if TimePassedThreshold = 0, no debouncing is started */
        DebounceStatus->InternalTimer = DebounceClassCfg->TimePassedThreshold;
        DebounceStatus->Direction = DEM_EVENT_STATUS_PASSED;
      }
      /*
       * in all other cases ("passed" timer already running or event
       * already qualified as "passed" and no timer running) there's
       * nothing to do.
       */
      break;

    case DEM_EVENT_STATUS_PREFAILED:

      /* see description above, exchanging "passed" and "failed" */

      if ( ( (DebounceStatus->InternalTimer != 0U) &&
             (DebounceStatus->Direction == DEM_EVENT_STATUS_PASSED)
           ) ||
           ( (DebounceStatus->InternalTimer == 0U) &&
             (DebounceStatus->Direction != DEM_EVENT_STATUS_FAILED)
           )
         )
      {
        /* if TimeFailedThreshold = 0, no debouncing is started */
        DebounceStatus->InternalTimer = DebounceClassCfg->TimeFailedThreshold;
        DebounceStatus->Direction = DEM_EVENT_STATUS_FAILED;
      }

      break;

    default: /* DEM_EVENT_STATUS_PASSED, DEM_EVENT_STATUS_FAILED */

      /* stop any running timer */
      DebounceStatus->InternalTimer = 0U;
      DebounceStatus->Direction = *EventStatus;

      break;
  } /* event status */

  /* "unfreeze" event debouncing */
  DebounceStatus->FreezeStatus = FALSE;

  /*
   * LEAVE critical section
   */
  DEM_EXIT_EXCLUSIVE_AREA();

  DBG_DEM_DEBOUNCEEVENTTIMEBASED_EXIT(EventId, EventStatus);
}
#endif /* (DEM_NUM_DEBOUNCE_TIME > 0U) */

#if (DEM_NUM_DEBOUNCE_COUNTER > 0U)
/*---------------[return FDC/DebounceBehavior - counter-based debouncing]---------------------*/
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_GetFDCCounterBased(
  Dem_EventIdType EventId,
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FDC)
{
  Std_ReturnType Result = E_NOT_OK;
  const Dem_EventIdType DebounceStatusIdx = Dem_GbiDebounceStatusIdx(EventId);
  const Dem_DebounceCounterClassIdxType DebounceClassIdx =
    Dem_GbiDebounceCounterClassIdx(DebounceStatusIdx);

  CONSTP2CONST(Dem_DebounceCounterClassType, AUTOMATIC, DEM_CONST)
    DebounceCfg = &Dem_DebounceCounterClass[DebounceClassIdx];
  sint16 IFdc = 0;

  DBG_DEM_GETFDCCOUNTERBASED_ENTRY(EventId, FDC);

  TS_AtomicAssign16(IFdc, Dem_DebounceCounterStatus[DebounceStatusIdx]);

    /* passed region */
    /* deriving FDC linearly from internal counter */
    if (IFdc < 0)
    {
      /* DEM_FDC_VALUE_PASSED needs to be multiplied first with the counter value
         before dividing counter value with threshold in order to avoid
         floating-point calculation */
      /* !LINKSTO dsn.Dem.FDCCounterBased,1 */
      *FDC = (sint8)
        (((sint32)(IFdc) * DEM_FDC_VALUE_PASSED) /
         DebounceCfg->CounterPassedThreshold);
      Result = E_OK;
    }
    else /* failed region */
    {
      /* DEM_FDC_VALUE_FAILED needs to be multiplied first with the counter value
         before dividing counter value with threshold in order to avoid
         floating-point calculation */
      /* !LINKSTO dsn.Dem.FDCCounterBased,1 */
      *FDC = (sint8)
        (((sint32)(IFdc) * DEM_FDC_VALUE_FAILED) /
         DebounceCfg->CounterFailedThreshold);
      Result = E_OK;
    }

  DBG_DEM_GETFDCCOUNTERBASED_EXIT(Result, EventId, FDC);
  return Result;
}

#if (DEM_USE_TRIGGER_DEBOUNCE_BEHAVIOR == STD_ON)
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_GetBehaviorCounterBased(
  Dem_EventIdType EventId,
  P2VAR(Dem_DebounceBehaviorType, AUTOMATIC, DEM_APPL_DATA) DebounceBehavior)
{
  Std_ReturnType Result = E_NOT_OK;
  const Dem_EventIdType DebounceStatusIdx = Dem_GbiDebounceStatusIdx(EventId);
  const Dem_DebounceCounterClassIdxType DebounceClassIdx =
    Dem_GbiDebounceCounterClassIdx(DebounceStatusIdx);

  CONSTP2CONST(Dem_DebounceCounterClassType, AUTOMATIC, DEM_CONST)
    DebounceCfg = &Dem_DebounceCounterClass[DebounceClassIdx];

  DBG_DEM_GETBEHAVIORCOUNTERBASED_ENTRY(EventId, DebounceBehavior);

  *DebounceBehavior = DebounceCfg->DemDebounceBehavior;
  Result = E_OK;

  DBG_DEM_GETBEHAVIORCOUNTERBASED_EXIT(Result, EventId, DebounceBehavior);
  return Result;
}
#endif /* (DEM_USE_TRIGGER_DEBOUNCE_BEHAVIOR == STD_ON) */
#endif /* (DEM_NUM_DEBOUNCE_COUNTER > 0U) */

#if (DEM_NUM_DEBOUNCE_FREQUENCY > 0U)
/*---------------[return FDC/DebounceBehavior - frequency-based debouncing]---------------------*/
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_GetFDCFrequencyBased(
  Dem_EventIdType EventId,
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FDC)
{
  const Dem_EventIdType DebounceIdx = Dem_GbiDebounceIdx(EventId);
  CONSTP2CONST(Dem_DebounceFrequencyCfgType, AUTOMATIC, DEM_CONST)
    DebounceCfg = &Dem_DebounceFrequencyCfg[DebounceIdx];
  CONSTP2VAR(Dem_DebounceFrequencyStatusType, AUTOMATIC, DEM_VAR_CLEARED)
    DebounceStatus = &Dem_DebounceFrequencyStatus[DebounceIdx];

  DBG_DEM_GETFDCFREQUENCYBASED_ENTRY(EventId, FDC);

  /* timer is running */
  if (DebounceStatus->InternalTimer != 0U)
  {
    /* DEM_FDC_VALUE_PASSED/FAILED needs to be multiplied first with the
       counter value before dividing counter value with threshold in order to
       avoid floating-point calculation */
    /* !LINKSTO dsn.Dem.FDCFrequencyBased,1 */
    *FDC = (sint8)
      (((sint32)(DebounceStatus->FailedCounter) * DEM_FDC_VALUE_FAILED) /
       ((sint32)DebounceCfg->ThresholdBeforeEvFailed + 1)) +
      (sint8)
      (((sint32)DebounceStatus->PassedCounter * DEM_FDC_VALUE_PASSED) /
       ((sint32)DebounceCfg->ThresholdBeforeEvPassed + 1));
  }
  else /* timer is not running */
  {
    if (DebounceStatus->Status == DEM_EVENT_STATUS_PASSED)
    {
      *FDC = DEM_FDC_VALUE_PASSED;
    }
    else if (DebounceStatus->Status == DEM_EVENT_STATUS_FAILED)
    {
      *FDC = DEM_FDC_VALUE_FAILED;
    }
    else
    {
      *FDC = 0;
    }
  }

  DBG_DEM_GETFDCFREQUENCYBASED_EXIT(E_OK, EventId, FDC);
  return E_OK;
}

#if (DEM_USE_TRIGGER_DEBOUNCE_BEHAVIOR == STD_ON)
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_GetBehaviorFrequencyBased(
  Dem_EventIdType EventId,
  P2VAR(Dem_DebounceBehaviorType, AUTOMATIC, DEM_APPL_DATA) DebounceBehavior)
{
  const Dem_EventIdType DebounceIdx = Dem_GbiDebounceIdx(EventId);
  CONSTP2CONST(Dem_DebounceFrequencyCfgType, AUTOMATIC, DEM_CONST)
    DebounceCfg = &Dem_DebounceFrequencyCfg[DebounceIdx];

  DBG_DEM_GETBEHAVIORFREQUENCYBASED_ENTRY(EventId, DebounceBehavior);

  *DebounceBehavior = DebounceCfg->DemDebounceBehavior;

  DBG_DEM_GETBEHAVIORFREQUENCYBASED_EXIT(E_OK, EventId, DebounceBehavior);
  return E_OK;
}
#endif /* #if (DEM_USE_TRIGGER_DEBOUNCE_BEHAVIOR == STD_ON) */
#endif /* (DEM_NUM_DEBOUNCE_FREQUENCY > 0U) */

#if (DEM_NUM_DEBOUNCE_TIME > 0U)
/*---------------[return FDC/DebounceBehavior - time-based debouncing]---------------------*/
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_GetFDCTimeBased(
  Dem_EventIdType EventId,
  P2VAR(sint8, AUTOMATIC, DEM_APPL_DATA) FDC)
{
  Std_ReturnType Result = E_NOT_OK;

  /* Get the Debounce Configuration Index from the Event Description */
  const Dem_EventIdType DebounceIdx = Dem_GbiDebounceIdx(EventId);

  /* Get the Time Debounce Class index */
  const Dem_DebounceTimeClassIdxType DebounceTimeClassIdx = Dem_GbiDebounceTimeClassIdx (DebounceIdx);

  /* Get  pointer to the Time Debounce Class */
  CONSTP2CONST(Dem_DebounceTimeClassType, AUTOMATIC, DEM_CONST)
    DebounceClassCfg = &Dem_DebounceTimeClass[DebounceTimeClassIdx];

  CONSTP2VAR(Dem_DebounceTimeStatusType, AUTOMATIC, DEM_VAR_CLEARED)
    DebounceStatus = &Dem_DebounceTimeStatus[DebounceIdx];

  DBG_DEM_GETFDCTIMEBASED_ENTRY(EventId, FDC);

  /*
   * ENTER critical section to protect debounce status
   *       call-context: any
   */
  DEM_ENTER_EXCLUSIVE_AREA();

  if (DebounceStatus->Direction != DEM_EVENT_STATUS_UNQUALIFIED)
  {
    /* deriving FDC linearly from internal timer */
    if ((DebounceStatus->Direction == DEM_EVENT_STATUS_PASSED) ||
       (DebounceStatus->Direction == DEM_EVENT_STATUS_PREPASSED))
    {
      /* DEM_FDC_VALUE_PASSED needs to be multiplied first with the counter
         value before dividing counter value with threshold in order to avoid
         floating-point calculation */
      /* !LINKSTO dsn.Dem.FDCTimeBased,1 */
      *FDC = (sint8)
        ((((sint32)(DebounceClassCfg->TimePassedThreshold) -
           (sint32)(DebounceStatus->InternalTimer)) * DEM_FDC_VALUE_PASSED) /
         (sint32)DebounceClassCfg->TimePassedThreshold);
    }
    else
    {
      /* DEM_FDC_VALUE_FAILED needs to be multiplied first with the counter
         value before dividing counter value with threshold in order to avoid
         floating-point calculation */
      /* !LINKSTO dsn.Dem.FDCTimeBased,1 */
      *FDC = (sint8)
        ((((sint32)(DebounceClassCfg->TimeFailedThreshold) -
           (sint32)(DebounceStatus->InternalTimer)) * DEM_FDC_VALUE_FAILED) /
         (sint32)DebounceClassCfg->TimeFailedThreshold);
    }
  }
  else /* unqualified state */
  {
    *FDC = 0;
  }

  /*
   * LEAVE critical section
   */
  DEM_EXIT_EXCLUSIVE_AREA();

  Result = E_OK;

  DBG_DEM_GETFDCTIMEBASED_EXIT(E_OK, EventId, FDC);
  return Result;
}

#if (DEM_USE_TRIGGER_DEBOUNCE_BEHAVIOR == STD_ON)
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_GetBehaviorTimeBased(
  Dem_EventIdType                                           EventId,
  P2VAR(Dem_DebounceBehaviorType, AUTOMATIC, DEM_APPL_DATA) DebounceBehavior)
{
  Std_ReturnType Result = E_NOT_OK;

  /* Get the Debounce Configuration Index from the Event Description */
  const Dem_EventIdType DebounceIdx = Dem_GbiDebounceIdx(EventId);

  /* Get the Time Debounce Class index */
  const Dem_DebounceTimeClassIdxType DebounceTimeClassIdx = Dem_GbiDebounceTimeClassIdx (DebounceIdx);

  /* Get  pointer to the Time Debounce Class */
  CONSTP2CONST(Dem_DebounceTimeClassType, AUTOMATIC, DEM_CONST)
     DebounceClassCfg = &Dem_DebounceTimeClass[DebounceTimeClassIdx];

  DBG_DEM_GETBEHAVIORTIMEBASED_ENTRY(EventId, DebounceBehavior);

  *DebounceBehavior = DebounceClassCfg->DemDebounceBehavior;
   Result = E_OK;

  DBG_DEM_GETBEHAVIORTIMEBASED_EXIT(Result, EventId, DebounceBehavior);
  return Result;
}

#endif /* (DEM_USE_TRIGGER_DEBOUNCE_BEHAVIOR == STD_ON) */
#endif /* (DEM_NUM_DEBOUNCE_TIME > 0U) */

STATIC FUNC(boolean, DEM_CODE) Dem_UpdateFailureCounterFirstFail(
  Dem_EventIdType     EventId,
  Dem_EventStatusType EventStatus)
{
  boolean Result = FALSE;

  DBG_DEM_UPDATEFAILURECOUNTERFIRSTFAIL_ENTRY(EventId, EventStatus);

  if (EventStatus == DEM_EVENT_STATUS_FAILED)
  {
    boolean IsFailureReported = DEM_IS_EV_ST_BIT_TFTOC_SET(EventId);

#if (DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON)

    const Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);

    if (DEM_IS_DTC_COMBINED(DTCConfIdx))
    {
      IsFailureReported = DEM_IS_ST_BIT_TFTOC_SET(Dem_CmbDTCStatus[DTCConfIdx]);
    }
#endif /* DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON */

    if (IsFailureReported == FALSE)
    {
#if (DEM_NUM_FAILURECYCLES > 0U)
      const uint16 EventFailureClassIdx = Dem_GbiEventFailureClassIdx(EventId);
      /* if fault confirmation is configured for the event */
      if (EventFailureClassIdx != DEM_NO_FAULT_CONFIRMATION)
      {
        const Dem_OperationCycleIdType EventFailureCycleIdx =
              Dem_GbiEventFailureCycleIdx(EventId, EventFailureClassIdx);
        boolean OpCyclePermission =
           ((DEM_OPCYCLESTATE[EventFailureCycleIdx] == DEM_CYCLE_STATE_START) ? TRUE : FALSE);

        /* for non-confirmed DTC,
         * configured failure cycle started and first failure report for the event
         * in this operation cycle */
        if ( (OpCyclePermission == TRUE) &&
             (!DEM_IS_ANY_EV_ST_BIT_SET(EventId, DEM_UDS_STATUS_CDTC)) )
        {
          boolean FailedEntryInErrorQueue = FALSE;

          /*
           * ENTER critical section to protect the event memory entry
           * call-context: any
           */
          DEM_ENTER_EXCLUSIVE_AREA();

#if (DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON)
          if (DEM_IS_DTC_COMBINED(DTCConfIdx))
          {
            FailedEntryInErrorQueue =
                  Dem_CheckErrQueueEntryForFailedCmbEvents(EventId);
          }
          else
#endif /* DEM_OBDONUDS_COMBINATION_ENABLED == STD_ON */
          {
            /* for BSW events the error queue will be checked for the current event Id
             * not to be present in the error-queue with FAILED status which ensures
             * that the current event has not been reported as FAILED in this operation cycle */
#if (DEM_MULTI_EVENT_TRIGGERING_COUNT > 0U)
            if (Dem_GbiEventKind(EventId) == DEM_EVENT_KIND_BSW)
#endif
            {
              FailedEntryInErrorQueue =
                Dem_CheckErrorQueueEntryForStatus(EventId, DEM_EVENT_STATUS_FAILED);
            }
          }

          if (FailedEntryInErrorQueue == FALSE)
          {
            /* !LINKSTO Dem.OBDonUDS.CombinedUDSDTCStatus.FailureCounter.Increase,1 */
            /* proceed with incrementing the failure counter */
            Result = Dem_IncrementFailureCounter(EventId, FALSE);
          }

          /*
           * LEAVE critical section
           */
          DEM_EXIT_EXCLUSIVE_AREA();
        }
      }
      else
#endif /* (DEM_NUM_FAILURECYCLES > 0U) */
      /* !LINKSTO Dem.NoFaultConfirmation,1 */
      {
        /* set the confirmed bit for events which don't have fault confirmation
         * configured, as soon as the failed bit is set */
        Result = TRUE;
      }
    }
  }

  DBG_DEM_UPDATEFAILURECOUNTERFIRSTFAIL_EXIT(Result, EventId, EventStatus);
  return Result;
}

#if (DEM_C_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U)
STATIC FUNC(void, DEM_CODE) Dem_GetCallbackIndex(
  Dem_EventIdType                                      EventId,
  P2CONST(Dem_CbLookupTableType, AUTOMATIC, DEM_CONST) LookupTable,
  uint16                                               TableSize,
  P2VAR(uint16, AUTOMATIC, DEM_VAR)                    StartIdx,
  P2VAR(uint16, AUTOMATIC, DEM_VAR)                    LastIdx)
{
  uint16 Idx = 0U;

  DBG_DEM_GETCALLBACKINDEX_ENTRY(
    EventId, LookupTable, TableSize, StartIdx, LastIdx);

  /* search for first matching CbIdx-lookup-table entry */
  while ( (Idx < TableSize) && (LookupTable[Idx].EventId != EventId) )
  {
    Idx++;
  }

  /* there MUST be (at least) one matching entry found */
  DEM_PRECONDITION_ASSERT((Idx < TableSize), DEM_INTERNAL_API_ID);

  *StartIdx = Idx;

  /* search for last matching CbIdx-lookup-table entry */
  do
  {
    Idx++;
  }
  /* Deviation TASKING-3 */
  while ( (Idx < TableSize) && (LookupTable[Idx].EventId == EventId) );

  *LastIdx = Idx - 1U;

  DBG_DEM_GETCALLBACKINDEX_EXIT(
    EventId, LookupTable, TableSize, StartIdx, LastIdx);
}
#endif /* (DEM_C_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U) */

#if (DEM_RTE_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U)
STATIC FUNC(void, DEM_CODE) Dem_GetRteCallbackIndex(
  Dem_EventIdType                                EventId,
  P2CONST(Dem_EventIdType, AUTOMATIC, DEM_CONST) LookupTable,
  uint16                                         TableSize,
  P2VAR(uint16, AUTOMATIC, DEM_VAR)              StartIdx,
  P2VAR(uint16, AUTOMATIC, DEM_VAR)              LastIdx)
{
  uint16 LeftIdx = 0U;
  uint16 RightIdx = TableSize - 1U;
  uint16 MiddleIdx, CurrentIdx;

  DBG_DEM_GETRTECALLBACKINDEX_ENTRY(
    EventId, LookupTable, TableSize, StartIdx, LastIdx);

  MiddleIdx = RightIdx / 2U;

  /* make a binary search to identify a matching CbIdx-lookup-table entry */
  while ( (LeftIdx < RightIdx) && (EventId != LookupTable[MiddleIdx]) )
  {
    if (EventId > LookupTable[MiddleIdx])
    {
      /* if EventId is bigger, ignore the left half */
      LeftIdx = MiddleIdx + 1U;
    }
    else
    {
      /* if EventId is smaller, ignore the right half */
      RightIdx = MiddleIdx - 1U;
    }

   /* in order to avoid overflow situations don't
    * compute MiddleIdx as follows:
    * MiddleIdx = (LeftIdx + RightIdx) / 2U */
    MiddleIdx = LeftIdx + ((RightIdx - LeftIdx) / 2U);
  }

  /* there MUST be (at least) one matching entry */
  DEM_PRECONDITION_ASSERT((EventId == LookupTable[MiddleIdx]),
                          DEM_INTERNAL_API_ID);

  /* identify the first matching CbIdx-lookup-table entry, as there can be
   * multiple matching entries */
  CurrentIdx = MiddleIdx;
  while (CurrentIdx > LeftIdx)
  {
    if (EventId == LookupTable[CurrentIdx - 1U])
    {
      CurrentIdx--;
    }
    else
    {
      /* CurrentIdx points to the first matching entry */
      break;
    }
  }
  *StartIdx = CurrentIdx;

  /* identify the last matching CbIdx-lookup-table entry */
  CurrentIdx = MiddleIdx;
  while (CurrentIdx < RightIdx)
  {
    if (EventId == LookupTable[CurrentIdx + 1U])
    {
      CurrentIdx++;
    }
    else
    {
      /* CurrentIdx points to the last matching entry */
      break;
    }
  }
  *LastIdx = CurrentIdx;

  DBG_DEM_GETRTECALLBACKINDEX_EXIT(
    EventId, LookupTable, TableSize, StartIdx, LastIdx);
}
#endif /* (DEM_RTE_CALLBACK_TABLE_TRIG_ON_EVST_SIZE > 0U) */

#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)
FUNC(boolean, DEM_CODE) Dem_IsEventsMILIndicatorActive(
  Dem_EventIdType EventId)
{
  Std_ReturnType Result = FALSE;

  DBG_DEM_ISEVENTSMILINDICATORACTIVE_ENTRY(EventId);

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
      Dem_IndicatorIdxType Idx;

      for (Idx = IndicatorClassIdxStart; Idx < IndicatorClassIdxEnd; Idx++)
      {
        CONSTP2CONST(Dem_IndicatorClassType, AUTOMATIC, DEM_CONST) IndicatorClass =
          &Dem_IndicatorClasses[Idx];

        if ( (IndicatorClass->IndicatorId == DEM_MIL_ID) &&
             (IndicatorClass->Enabled == TRUE) )
        {
          if ( DEM_IS_EV_ST_BIT_WIR_SET(EventId) &&
               DEM_IS_BIT_SET_IN_ARRAY(DEM_INDICATOR_CYC_COUNTER_WIR_STATUS[DEM_MIL_ID],
                                       EventId) )
          {
            Result = TRUE;

            break;
          }
        }
      }
    }
  }
#else
  /* calibration is disabled and event availability is not considered */
  {
    /* indicator status is calculated re-entrant, as the WIR bits are evaluated
     * atomically (and further accesses are only done on constant values) */
    const Dem_IndicatorIdxType LinkNumber = Dem_IndicatorDesc[DEM_MIL_ID].Number;
    /* point to MIL indicator link of according data structures */
    CONSTP2CONST(Dem_IndicatorLinkType, AUTOMATIC, DEM_CONST) IndicatorLink =
      &Dem_IndicatorLink[Dem_IndicatorDesc[DEM_MIL_ID].StartIdx];
    Dem_IndicatorIdxType LinkIdx;

    for (LinkIdx = 0U; LinkIdx < LinkNumber; ++LinkIdx)
    {
      if (IndicatorLink[LinkIdx].EventId == EventId)
      {
        const Dem_CounterDataIdxType CounterDataIdx =
            LinkIdx + Dem_IndicatorDesc[DEM_MIL_ID].StartIdx;

        if ( DEM_IS_EV_ST_BIT_WIR_SET(EventId) &&
             DEM_IS_BIT_SET_IN_ARRAY(DEM_INDICATOR_CYC_COUNTER_WIR_STATUS[
               DEM_INDICATOR_DEFAULT_COUNTER], CounterDataIdx) )
        {
          Result = TRUE;

          break;
        }
      }
    }
  }
#endif /* (DEM_CALIBRATION_SUPPORT == STD_ON) */

  DBG_DEM_ISEVENTSMILINDICATORACTIVE_EXIT(EventId, Result);
  return Result;
}

#if (DEM_NUM_CMB_DTCS > 0U)
FUNC(boolean, DEM_CODE) Dem_IsCmbEventsMILIndicatorActive(
  Dem_EventIdType EventId)
{
  Std_ReturnType Result = FALSE;
  const Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);

  DBG_DEM_ISCMBEVENTSMILINDICATORACTIVE_ENTRY(EventId);

  if (DEM_IS_DTC_COMBINED(DTCConfIdx))
  {
    /* search for the first combined event with MIL indicator active */
    const Dem_CmbDTCEvLnkType firstCmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx];
    const Dem_CmbDTCEvLnkType LastCmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx + 1U] - 1U;
    Dem_CmbDTCEvLnkType CmbEvIdx;

    for (CmbEvIdx = firstCmbEvIdx; CmbEvIdx <= LastCmbEvIdx; CmbEvIdx++)
    {
      const Dem_EventIdType CmbEventId = Dem_CmbDTCEvents[CmbEvIdx];
      /* avoid input EventId to check only other combined events */
      if (CmbEventId != EventId)
      {
        /* check if MIL indicator of EventId is active */
        if (Dem_IsEventsMILIndicatorActive(CmbEventId) == TRUE)
        {
          Result = TRUE;

          break;
        }
      }
    }
  }

  DBG_DEM_ISCMBEVENTSMILINDICATORACTIVE_EXIT(EventId, Result);
  return Result;
}
#endif /* #if (DEM_NUM_CMB_DTCS > 0U) */
#endif /* #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U) */

STATIC FUNC(uint32, DEM_CODE) Dem_InternalGetUdsDTC(Dem_EventIdType EventId)
{
  uint32 DTC;

#if ( (DEM_USE_DYNAMIC_DTCS == STD_ON) && \
      (DEM_DEV_ERROR_DETECT == STD_ON) && \
      (DEM_NUM_DTC_GROUPS > 0U) )
  sint16 RetGrpIndex = (sint16)DEM_NUM_DTC_GROUPS - 1;
  sint16 CfgGrpIndex = (sint16)Dem_GbiDTCGroupIdx(EventId);
  boolean DTCGroupFound = FALSE;
  boolean OverlapDTCGroup = FALSE;
#endif

  DBG_DEM_INTERNALGETUDSDTC_ENTRY(EventId);

  DTC = DEM_BIT_FIELD_VALUE_32(DEM_DESC_CONF1(EventId),
          DEM_UDS_DTC_OFFSET, DEM_UDS_DTC_MASK);

#if (DEM_USE_DYNAMIC_DTCS == STD_ON)
  /* enter only if a DTC is configured for the event and DTC is not disabled by calibration */
  if (DTC != DEM_NO_DTC)
  {
    /* !LINKSTO Dem.DTCConfiguration.GetDynamic,1 */
    DTC = DEM_GET_DYNAMIC_DTC(EventId, DTC);

#if (DEM_DEV_ERROR_DETECT == STD_ON)
#if (DEM_NUM_DTC_GROUPS > 0U)
    if (DTC != DEM_NO_DTC)
    {
      /* search for the index of DTC group of returned DTC. Searching uses the
       * configured DTC group array sorted in ascending order of DTC group value. */
      do
      {
        if (DTC > Dem_DTCGroups[RetGrpIndex])
        {
          DTCGroupFound = TRUE;
        }
        else if (DTC == Dem_DTCGroups[RetGrpIndex])
        {
          OverlapDTCGroup = TRUE;
        }
        else
        {
          RetGrpIndex--;
        }
      }
      while ( (RetGrpIndex >= 0) && (DTCGroupFound != TRUE) && (OverlapDTCGroup != TRUE) );

      if (RetGrpIndex == -1)
      {
        RetGrpIndex = DEM_DTCGRP_IDX_ALL_DTC;
      }

      if ((RetGrpIndex != CfgGrpIndex) || (OverlapDTCGroup == TRUE))
      {
        DTC = DEM_NO_DTC;
      }
    }
#endif /* (DEM_NUM_DTC_GROUPS > 0U) */

    if (DTC == DEM_NO_DTC)
    {
      /* !LINKSTO Dem.DetReport.Dem_GetVisibleUdsDTC,1 */
      DEM_REPORT_ERROR(DEM_SID_CalloutDynamicDTCFnc, DEM_E_INTEGRATION);
    }
#endif /* (DEM_DEV_ERROR_DETECT == STD_ON) */
  }
#endif /* DEM_USE_DYNAMIC_DTCS */

  DBG_DEM_INTERNALGETUDSDTC_EXIT(EventId, DTC);
  return DTC;
}

/* !LINKSTO Dem_OBD_0001,2 */
#if (DEM_OBD_Support == STD_ON)
STATIC FUNC(uint32, DEM_CODE) Dem_InternalGetObdDTC(Dem_EventIdType EventId)
{
  uint32 DTC = DEM_NO_DTC;

  DBG_DEM_INTERNALGETOBDDTC_ENTRY(EventId);

  /* !LINKSTO Dem.DTCformat.2ByteObdDTC,1 */
#if ((DEM_OBD_CLASSIC_SUPPORT) || (DEM_OBD_DTCVALUE3BYTE_SUPPORT == STD_OFF))
  DTC = ((uint32)((uint32)Dem_OBDDTC[DEM_DESC_OBD_IDX(EventId)]) << 8U);
#else
  TS_PARAM_UNUSED(EventId);
#endif

  DBG_DEM_INTERNALGETOBDDTC_EXIT(EventId, DTC);
  return DTC;
}

#if (DEM_OBD_DTCVALUE3BYTE_SUPPORT == STD_ON)
STATIC FUNC(uint32, DEM_CODE) Dem_InternalGetObdDTCValue3Byte(Dem_EventIdType EventId)
{
  uint32 DTC;

  DBG_DEM_INTERNALGETOBDDTCVALUE3BYTE_ENTRY(EventId);

  /* !LINKSTO Dem.DTCformat.3ByteDTC,1 */
  DTC = DEM_BIT_FIELD_VALUE_32(Dem_OBDConfig[DEM_DESC_OBD_IDX(EventId)],
          DEM_OBD_DTC_3BYTE_OFFSET, DEM_OBD_DTC_3BYTE_MASK);

  DBG_DEM_INTERNALGETOBDDTCVALUE3BYTE_EXIT(EventId, DTC);
  return DTC;
}
#endif /* (DEM_OBD_DTCVALUE3BYTE_SUPPORT == STD_ON) */
#endif /* (DEM_OBD_Support == STD_ON) */

#if (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION)
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_InternalCheckAndSetDTCSuppression(
  uint32                             DTC,
  Dem_GetDTCFctPtrType               GetDTCFct,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) DtcSuppressionArray,
  boolean                            SuppressionStatus)
{
  Std_ReturnType Result = E_NOT_OK;
  Dem_EventIdType EventId;

  DBG_DEM_INTERNALCHECKANDSETDTCSUPPRESSION_ENTRY(DTC, GetDTCFct, DtcSuppressionArray, SuppressionStatus);

  /* Deviation TASKING-1 */
  for (EventId = 1U; EventId <= DEM_MAX_EVENTID; ++EventId)
  {
    if (DTC == GetDTCFct(EventId))
    {
      /* a matching EventId for the given DTC is found */
      Result = E_OK;
      break;
    }
  }
  if (Result == E_OK)
  {
    boolean CurrentSuppressionStatus;

    /*
     * ENTER critical section
     */
    DEM_ENTER_EXCLUSIVE_AREA();

    CurrentSuppressionStatus =
      DEM_IS_BIT_SET_IN_ARRAY(DtcSuppressionArray, EventId) ? TRUE : FALSE;

    if (CurrentSuppressionStatus != SuppressionStatus)
    {
      if (SuppressionStatus == TRUE)
      {
        /* only DEM_EVCOMB_TYPE1 is supported therefore the search will find the
         * event memory entry of the master event, if any */
        /* !LINKSTO Dem.ASR40.SWS_Dem_00588,1 */
        if (Dem_SearchForEntry(EventId, NULL_PTR, NULL_PTR) == TRUE)
        {
          Result = E_NOT_OK;
        }
      }
    }
    if (Result == E_OK)
    {
#if (DEM_NUM_CMB_DTCS > 0U)

      const Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);

      if (DEM_IS_DTC_COMBINED(DTCConfIdx))
      {
        /* update DTC suppression status of all combined events */
        const Dem_CmbDTCEvLnkType LastCmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx + 1U] - 1U;
        Dem_CmbDTCEvLnkType CmbEvIdx;
        Dem_EventIdType CmbEventId;

        for (CmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx]; CmbEvIdx <= LastCmbEvIdx; CmbEvIdx++)
        {
          CmbEventId = Dem_CmbDTCEvents[CmbEvIdx];
          DEM_MODIFY_BIT_IN_ARRAY(DtcSuppressionArray, CmbEventId, SuppressionStatus);
        }
      }
      else
#endif /* (DEM_NUM_CMB_DTCS > 0U) */
      {
        DEM_MODIFY_BIT_IN_ARRAY(DtcSuppressionArray, EventId, SuppressionStatus);
      }
    }

    /*
     * LEAVE critical section
     */
    DEM_EXIT_EXCLUSIVE_AREA();
  }

  DBG_DEM_INTERNALCHECKANDSETDTCSUPPRESSION_EXIT(Result, DTC, GetDTCFct, DtcSuppressionArray, SuppressionStatus);

  return Result;
}

#if ( (DEM_OBD_Support == STD_ON) && \
      (DEM_OBD_CLASSIC_SUPPORT) && \
      (DEM_IDENTICAL_OBD_DTC_AVAILABLE == STD_ON) )
STATIC FUNC(Std_ReturnType, DEM_CODE) Dem_InternalCheckAndSetObdDTCSuppression(
  uint32            DTC,
  boolean           SuppressionStatus)
{
  Dem_EventIdType EventId;
  Std_ReturnType Result = E_NOT_OK;

  DBG_DEM_INTERNALCHECKANDSETOBDDTCSUPPRESSION_ENTER(DTC, SuppressionStatus);

  /*
   * ENTER critical section
   */
  DEM_ENTER_EXCLUSIVE_AREA();

  for (EventId = 1U; EventId <= DEM_MAX_EVENTID; ++EventId)
  {
    if (DTC == Dem_InternalGetObdDTC(EventId))
    {
      if (Result != E_OK)
      {
        const boolean CurrentSuppressionStatus =
          DEM_IS_BIT_SET_IN_ARRAY(Dem_OBDDTCSuppression, EventId) ? TRUE : FALSE;

        if (CurrentSuppressionStatus != SuppressionStatus)
        {
          if (SuppressionStatus == FALSE)
          {
            /* update Result if the requested suppression status is FALSE */
            Result = E_OK;
          }
          else
          {
            if (Dem_ExistEntryOfObdDTC(DTC) == FALSE)
            {
              /* update Result if no event entry exists for the given DTC */
              Result = E_OK;
            }
          }
        }
        else
        {
          /* update Result if the requested suppression status is same as the current suppression status */
          Result = E_OK;
        }

        if (Result != E_OK)
        {
          break;
        }
      }

      DEM_MODIFY_BIT_IN_ARRAY(Dem_OBDDTCSuppression, EventId, SuppressionStatus);
      Result = E_OK;
    }
  }

  /*
   * LEAVE critical section
   */
  DEM_EXIT_EXCLUSIVE_AREA();

  DBG_DEM_INTERNALCHECKANDSETOBDDTCSUPPRESSION_EXIT(Result, DTC, SuppressionStatus);

  return Result;
}

STATIC FUNC(boolean, DEM_CODE) Dem_ExistEntryOfObdDTC(uint32 DTC)
{
  boolean Result = FALSE;
  Dem_SizeEvMemEntryType EventEntryIdx;
  const Dem_EventMemoryEntryPtrType EventMem = Dem_EventMem[DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U];
  const Dem_SizeEvMemEntryType SizeEventMem = Dem_SizeEventMem[DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U];

  DBG_DEM_EXISTENTRYOFOBDDTC_ENTRY(DTC);

  for (EventEntryIdx = 0U; EventEntryIdx < SizeEventMem; EventEntryIdx++)
  {
    const Dem_EventIdType CurrentEventId = EventMem[EventEntryIdx].EventId;
    if (CurrentEventId != DEM_EVENT_ID_INVALID)
    {
      if (DTC == Dem_InternalGetObdDTC(CurrentEventId))
      {
        /* update Result if an entry for the given DTC is found in the fault memory */
        Result = TRUE;
        break;
      }
    }
  }

  DBG_DEM_EXISTENTRYOFOBDDTC_EXIT(Result, DTC);

  return Result;
}
#endif /* ((DEM_OBD_Support == STD_ON) && DEM_IDENTICAL_OBD_DTC_AVAILABLE == STD_ON)) */
#endif /* (DEM_SUPPRESSION_SUPPORT == DEM_DTC_SUPPRESSION) */

#if ( (DEM_NUM_BSWEVENT_INDICATOR_USED > 0U) && \
      (DEM_COMMON_OPERATION_CYCLE_SUPPORT == STD_OFF) )
STATIC FUNC(boolean, DEM_CODE) Dem_CheckErrorRequiresIndUpdate(
  Dem_EventIdType       EventId,
  Dem_EventStatusType   EventStatus)
{
  boolean Result = FALSE;
#if (DEM_CALIBRATION_SUPPORT == STD_OFF)
  const boolean IndicatorUsed = Dem_GbiIndicatorUsed(EventId);
#endif

  DBG_DEM_CHECKERRORREQUIRESINDUPDATE_ENTRY(EventId, EventStatus);

#if (DEM_CALIBRATION_SUPPORT == STD_ON)
  if ( (EventStatus == DEM_EVENT_STATUS_FAILED) ||
       (EventStatus == DEM_EVENT_STATUS_CONFIRMED) )
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
        CONSTP2CONST(Dem_IndicatorClassType, AUTOMATIC, DEM_CONST) IndicatorClass =
          &Dem_IndicatorClasses[Idx];

        if (IndicatorClass->Enabled == TRUE)
        {
          const Dem_OperationCycleIdType FailureCycleId =
              Dem_GbiIndicatorFailureCycleIdx(EventId, Idx);
          const Dem_OperationCycleIdType EventOperationCycle =
              Dem_GbiOpCycleIdx(EventId);
          if (FailureCycleId != EventOperationCycle)
          {
            Result = TRUE;
            break;
          }
        }
      }
    }
  }
/* calibration is disabled and indicator availability is not considered */
#else /* (DEM_CALIBRATION_SUPPORT == STD_OFF) */
  if ( (IndicatorUsed == TRUE) &&
       ( (EventStatus == DEM_EVENT_STATUS_FAILED) ||
         (EventStatus == DEM_EVENT_STATUS_CONFIRMED) ) )
  {
    Dem_IndicatorIdxType LinkIdx;

    /* Deviation TASKING-1 */
    for (LinkIdx = 0U; LinkIdx < DEM_NUM_INDICATOR_LINKS; LinkIdx++)
    {
      if (Dem_IndicatorLink[LinkIdx].EventId == EventId)
      {
        const Dem_OperationCycleIdType FailureCycleId =
            Dem_GbiIndicatorFailureCycleIdx(EventId, LinkIdx);
        const Dem_OperationCycleIdType EventOperationCycle =
            Dem_GbiOpCycleIdx(EventId);
        if (FailureCycleId != EventOperationCycle)
        {
          Result = TRUE;
          break;
        }
      }
    }
  }
#endif /* (DEM_CALIBRATION_SUPPORT == STD_ON) */

  DBG_DEM_CHECKERRORREQUIRESINDUPDATE_EXIT(EventId, EventStatus, Result);

  return Result;
}
#endif /*  DEM_NUM_BSWEVENT_INDICATOR_USED &&
           ! DEM_COMMON_OPERATION_CYCLE_SUPPORT */

FUNC(Dem_DTCOriginType, DEM_CODE) Dem_GetMappedDTCOrigin(
    Dem_DTCOriginType         DTCOrigin,
    Dem_DTCOriginMappingType  MappingVariant)
{
  Dem_DTCOriginType Result;

  DBG_DEM_GETMAPPEDDTCORIGIN_ENTRY(DTCOrigin, MappingVariant);

  switch(DTCOrigin)
  {

    /* Both DEM_DTC_ORIGIN_SECONDARY_MEMORY and DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY
     * are currently enumerated as 0x4U */
    /* !LINKSTO Dem.EB.MemorySelection.ObdRelevantMemoryMapping,1 */
    case DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY:
      /* For Autosar 4.3 interfaces, value 0x4U is mapped into primary memory,
         For Autosar 4.0 interfaces, value 0x4U is mapped into secondary memory (also 0x4U) */
      Result = ( (MappingVariant == DEM_DTC_ORIGIN_MAPPING_ASR43_IF) ?
          DEM_DTC_ORIGIN_PRIMARY_MEMORY : DEM_DTC_ORIGIN_SECONDARY_MEMORY );
      break;
    /* !LINKSTO Dem.EB.MemorySelection.UserDefinedMemoryMapping,1 */
#if (DEM_DTC_ORIGIN_USERDEFINED_MEMORY_MAPPED_TO_SECONDARY > 0U)
    case DEM_DTC_ORIGIN_USERDEFINED_MEMORY_MAPPED_TO_SECONDARY:
      Result = DEM_DTC_ORIGIN_SECONDARY_MEMORY;
      break;
#endif
    case DEM_DTC_ORIGIN_PRIMARY_MEMORY:
    case DEM_DTC_ORIGIN_MIRROR_MEMORY:
    case DEM_DTC_ORIGIN_PERMANENT_MEMORY:
      Result = DTCOrigin;
      break;

    default:
      Result = DEM_DTC_ORIGIN_INVALID;
      break;
  }

  DBG_DEM_GETMAPPEDDTCORIGIN_EXIT(Result, DTCOrigin, MappingVariant);
  return Result;
}

#if (DEM_FREEZE_FRAME_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD)
FUNC(boolean, DEM_CODE) Dem_IsAnyDTCStatusBitSet(
  Dem_EventIdType                      EventId,
  uint8                                Mask)
{
  boolean Result = FALSE;
#if (DEM_NUM_CMB_DTCS > 0U)
  const Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
#endif

  DBG_DEM_ISANYDTCSTATUSBITSET_ENTRY(EventId, Mask);

#if (DEM_NUM_CMB_DTCS > 0U)
  /* For combined events, check status bit of combined status.*/
  if (DEM_IS_DTC_COMBINED(DTCConfIdx))
  {
    Result = DEM_IS_CMB_ST_BIT_SET_IN_DTC(DTCConfIdx, Mask);
  }
  else
#endif
  /* for simple events, check status bit of event status.*/
  {
    Result = DEM_IS_ANY_EV_ST_BIT_SET((EventId), Mask);
  }

  DBG_DEM_ISANYDTCSTATUSBITSET_EXIT(Result, EventId, Mask);

  return Result;
}
#endif /* DEM_FREEZE_FRAME_CAPTURE != DEM_TRIGGER_ON_FDC_THRESHOLD */

#if (DEM_NUMBER_OF_CLIENTS > 1U)
FUNC(boolean, DEM_CODE)Dem_IsRecordUpdateLocked(Dem_EventIdType EventId)
{
  boolean Result = FALSE;
  uint8 RecordIndex = 0;
  const Dem_EventIdType MasterEventId = DEM_GET_MASTER_EVID(EventId);

  DBG_DEM_ISRECORDUPDATELOCKED_ENTRY();

  while(RecordIndex < Dem_DTCRecordLockingNextFreeIndex)
  {
    if(Dem_EvIdOfLockedMemoryEntry[RecordIndex] == MasterEventId)
    {
      Result = TRUE;
      break;
    }

    RecordIndex++;
  }

  DBG_DEM_ISRECORDUPDATELOCKED_EXIT(Result);

  return Result;
}
#endif

FUNC(void, DEM_CODE) Dem_SetClearDTCResult(Std_ReturnType Result)
{
  DBG_DEM_SETCLEARDTCRESULT_ENTRY(Result);
  /* DEM_CLEAR_NO_RESULT indicates Client not interested in return result anymore, in such case
   * the client result is discarded. The actual clearing DTC process is still running to completion
   * meanwhile, only the result is dropped */
  /* !LINKSTO Dem.SWS_Dem_01304,1 */
  if(DEM_CLEAR_NO_RESULT != Dem_ClearDTCResult[Dem_ClearDtcAsyncStatus.ClientId])
  {
    Dem_ClearDTCResult[Dem_ClearDtcAsyncStatus.ClientId] = Result;
  }
  DBG_DEM_SETCLEARDTCRESULT_EXIT(Result);
}

FUNC(boolean, DEM_CODE) Dem_CheckEntryProcessingConditions(
  Dem_EventIdType                                        EventId,
  Dem_EventStatusType                                    EventStatus,
  P2VAR(Dem_StatusTransitionType, AUTOMATIC, AUTOMATIC)  TransitionType)
{
  boolean Result = FALSE;

  DBG_CHECKENTRYPROCESSINGCONDITIONS_ENTRY(
    EventId, EventStatus, TransitionType);

  if ( (EventStatus == DEM_EVENT_STATUS_FAILED) ||
       (EventStatus == DEM_EVENT_STATUS_CONFIRMED) )
  {
#if (DEM_FREEZE_FRAME_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)
    /* if unconfirmed threshold is used, queue first failed result in an operation cycle */
    Result = (!DEM_IS_EV_ST_BIT_TFTOC_SET(EventId)) ? TRUE : FALSE;

    TS_PARAM_UNUSED(TransitionType);
#else
#if (DEM_IGNORE_RESET_EVENT_STATUS_FOR_ENTRY == STD_ON)
#if (DEM_NUM_CMB_DTCS > 0U)
    if (DEM_IS_EVENT_COMBINED(EventId))
    {
      /* !LINKSTO Dem.IgnoreResetEventStatusForEventRelatedDataCapturing.FailedReport,1 */
      /* Only check, if event was PASSED before. Otherwise there will be no
       * change of combined status and Result stays FALSE. */
      if (!DEM_IS_RESISTANT_TF_STATUS_BIT_SET(EventId))
      {
        /* check calculated combined status based on reset resistant TF bits */
        Dem_CmbDTCEvLnkType CmbEvIdx;
        Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
        boolean CombinedTFBitSet = FALSE;

        /* loop through combined events */
        /* Note: The following loop is not protected by an exclusive area.
         * For SWC events that are handled synchronously, it might therefore
         * happen, that another reported event interrupts this loop and
         * affects the decision for freeze frame capturing. However, data
         * consistency is not impacted and for events that are reported
         * in such a short time frame, the behavior might not be absolutely
         * deterministic anyhow. Also the captured data itself would probably
         * not change significantly in this time frame.
         * Since the theoretical benefit w.r.t. determinism is rather low, it
         * was decided to avoid the overhead of an exclusive area.
         */
        for (CmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx];
             CmbEvIdx < Dem_CmbDTCEvLnk[DTCConfIdx + 1U];
             CmbEvIdx++)
        {
          Dem_EventIdType CurrentEvent = Dem_CmbDTCEvents[CmbEvIdx];

          /* !LINKSTO Dem.IgnoreResetEventStatusForEventRelatedDataCapturing.FailedReport,1 */
          if (DEM_IS_RESISTANT_TF_STATUS_BIT_SET(CurrentEvent))
          {
            CombinedTFBitSet = TRUE;
            break;
          }
        }

        if (CombinedTFBitSet == FALSE)
        {
          /* combined status was PASSED, i.e. there is a change */
          Result = TRUE;
        }
      }
    }
    else
#endif /* (DEM_NUM_CMB_DTCS > 0U) */
    {
      /* simple events */
      /* !LINKSTO Dem.IgnoreResetEventStatusForEventRelatedDataCapturing.FailedReport,1 */
      Result =
        (!DEM_IS_CAPTURE_RELEVANT_TF_STATUS_BIT_SET(EventId)) ? TRUE : FALSE;
    }
#else /* (DEM_IGNORE_RESET_EVENT_STATUS_FOR_ENTRY == STD_ON) */
    /* if NO unconfirmed threshold is used, queue/handle failed result after passed */
    Result = !Dem_IsAnyDTCStatusBitSet(EventId, DEM_UDS_STATUS_TF);
#endif /* (DEM_IGNORE_RESET_EVENT_STATUS_FOR_ENTRY == STD_ON) */
#endif /* (DEM_FREEZE_FRAME_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD) */

#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE)
    /* Note that multiple OBD FF is not applicable for DEM_TRIGGER_ON_FDC_THRESHOLD */
#if (DEM_OBDONUDS_FF_SUPPORT == STD_ON)
    if (Result == TRUE)
    {
      /* store that DTC TF flag went through 0 -> 1 transition
       * (check already done above) */
      *TransitionType |= DEM_TRANSITION_DTC_TF;
    }

    if ((DEM_GET_OBD_VARIANT() == DEM_OBD_VARIANT_OBDONUDS) &&
        (Dem_GbiDTCKind(EventId) == DEM_DTC_KIND_EMISSION_REL_DTCS))
    {
      /* Check if TFTOC transition will occur */
      if ( Dem_IsAnyDTCStatusBitSet(EventId, DEM_UDS_STATUS_TFTOC) == FALSE )
      {
        /* Transition of DTC TFTOC 0 -> 1 detected, include event in entry
         * processing, this is a special case, that is only handled to
         * satisfy OBDonUDS FF record last occurrence trigger condition */
        *TransitionType |= DEM_TRANSITION_DTC_TFTOC;
        Result = TRUE;
      }
    }
#endif /* (DEM_OBDONUDS_FF_SUPPORT == STD_ON) */

    /* Check if PDTC transition will occur, while CDTC is not set */
    if ( Dem_IsAnyDTCStatusBitSet(EventId,
           (DEM_UDS_STATUS_CDTC | DEM_UDS_STATUS_PDTC)) == FALSE )
    {
      /* this info is used to decide, if the first OBD FF (OBDonUDS or
       * Classic) shall be updated */
      *TransitionType |= DEM_TRANSITION_DTC_PDTC_WHILE_CDTC_NOT_SET;
      Result = TRUE;
    }
#else
    TS_PARAM_UNUSED(TransitionType);
#endif /* (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_MULTIPLE) */
  }

#if (DEM_TRIGGER_ON_DEQUALIFICATION_SUPPORT == STD_ON)
  if (EventStatus == DEM_EVENT_STATUS_PASSED)
  {
#if (DEM_NUM_CMB_DTCS > 0U)
    /* for combined events, check combined status */
    if (DEM_IS_EVENT_COMBINED(EventId))
    {
      /* Only check, if event was FAILED before. Otherwise there will be no
       * change of combined status and Result stays FALSE */
      /* !LINKSTO Dem.IgnoreResetEventStatusForEventRelatedDataCapturing.PassedReport,1 */
      if (DEM_IS_CAPTURE_RELEVANT_TF_STATUS_BIT_SET(EventId))
      {
        Dem_CmbDTCEvLnkType CmbEvIdx;
        Dem_DTCConfIdxType DTCConfIdx = Dem_GbiDTCConfIdx(EventId);
        boolean CombinedTFBitStaysActive = FALSE;

        /* check TF bits of combined events excluding the current PASSED event */
        /* Note: The comment about the loop in the FAILED/CONFIRMED-path
         * above applies here as well!
         */
        for (CmbEvIdx = Dem_CmbDTCEvLnk[DTCConfIdx];
             CmbEvIdx < Dem_CmbDTCEvLnk[DTCConfIdx + 1U];
             CmbEvIdx++)
        {
          Dem_EventIdType CurrentEvent = Dem_CmbDTCEvents[CmbEvIdx];

          if (EventId != CurrentEvent)
          {
            /* !LINKSTO Dem.IgnoreResetEventStatusForEventRelatedDataCapturing.PassedReport,1 */
            if (DEM_IS_CAPTURE_RELEVANT_TF_STATUS_BIT_SET(CurrentEvent))
            {
              /* at least one event will keep the combined TF bit active */
              CombinedTFBitStaysActive = TRUE;
              break;
            }
          }
        }

        if (CombinedTFBitStaysActive == FALSE)
        {
          /* combined status will change to PASSED */
          Result = TRUE;
        }
      }
    }
    else
#endif
    /* simple event */
    {
      /* !LINKSTO Dem.IgnoreResetEventStatusForEventRelatedDataCapturing.PassedReport,1 */
      Result = (DEM_IS_CAPTURE_RELEVANT_TF_STATUS_BIT_SET(EventId)) ? TRUE : FALSE;
    }
  }
#endif /* (DEM_TRIGGER_ON_DEQUALIFICATION_SUPPORT == STD_ON) */

  DBG_CHECKENTRYPROCESSINGCONDITIONS_EXIT(
    Result, EventId, EventStatus, TransitionType);

  return Result;
}

#if ((DEM_USE_AGING == STD_ON) && (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD))
FUNC(void, DEM_CODE) Dem_ProcessEventAging(
  Dem_EventIdType                  EventId,
  Dem_EventMemoryEntryPtrType      EvMemEntry)
{
#if (DEM_OBD_Support == STD_ON)
   /* retain DTC kind to check for emission-related DTCs */
      const Dem_DTCKindType DTCKind = Dem_GbiDTCKind(EventId);
#endif

  DBG_DEM_PROCESSEVENTAGING_ENTRY(EventId,EvMemEntry);

#if ( ( DEM_OBD_Support == STD_ON) && (DEM_VCC_OCC5_USED == STD_ON) && (DEM_NUM_INDICATOR_LINKS > 0U) )
  if(DTCKind == DEM_DTC_KIND_EMISSION_REL_DTCS)
  {
    /* set role of all indicators belonging to EventId to healing */
    /* !LINKSTO dsn.ResetIndicator.OnEventAging,1 */
    Dem_ResetIndicatorCycleCounterRoleOfEventId(EventId);
  }
#endif /*((DEM_OBD_Support == STD_ON) && (DEM_VCC_OCC5_USED == STD_ON) && (DEM_NUM_INDICATOR_LINKS > 0U))*/

  /* set AgedDTC bit */
  DEM_SET_MASK(EvMemEntry->SI30, DEM_SI30_STATUS_AGEDDTC);

  /* clear TestFailedSinceLastClear/Aged bit */
  DEM_CLR_MASK_8(EvMemEntry->SI30, DEM_SI30_STATUS_TFSLC_AGED);

#if (DEM_OBD_Support == STD_ON)
  /* reset EmissionRelatedDTC bit (Si30.Bit6) */
  if (DTCKind == DEM_DTC_KIND_EMISSION_REL_DTCS)
  {
    DEM_CLR_MASK_8(EvMemEntry->SI30, DEM_SI30_STATUS_EMISSIONRELATEDDTC);
  }
#endif
#if (DEM_OBDFF_SUPPORT_KIND == DEM_OBDFF_SINGLE)
  /* !LINKSTO DemOBDFreezeFrame.ClearOnAged,1 */
  /* !LINKSTO Dem.OBD.SingleOBDFreezeFrame.ClearOnAged,1 */
  Dem_ClearSingleOBDFreezeFrame(EventId);
#endif

  /* !LINKSTO Dem.SWS_Dem_00498,1 */
  /* clear confirmed and TestFailedSinceLastClear (only if configured)
   * bits */
#if (DEM_STATUS_BIT_HANDLING_TESTFAILEDSINCELASTCLEAR == \
      DEM_STATUS_BIT_AGING_AND_DISPLACEMENT)
  DEM_CLR_EV_ST_MASK(EventId,
                     DEM_UDS_STATUS_CDTC |
                     DEM_UDS_STATUS_TFSLC);
#else
  DEM_CLR_EV_ST_MASK(EventId, DEM_UDS_STATUS_CDTC);
#endif

#if (DEM_NUM_FAILURECYCLES > 0U)
  /* reset EventFailureCycleCounter */
  EvMemEntry->EventFailureCycleCounter = 0U;
#endif
  DBG_DEM_PROCESSEVENTAGING_EXIT(EventId,EvMemEntry);
}
#endif /* ((DEM_USE_AGING == STD_ON) && (DEM_EXTENDED_DATA_CAPTURE == DEM_TRIGGER_ON_FDC_THRESHOLD)) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*==================[end of file]===========================================*/
