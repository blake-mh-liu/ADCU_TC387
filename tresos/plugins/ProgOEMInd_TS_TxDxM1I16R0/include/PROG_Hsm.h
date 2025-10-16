/* --------{ EB Automotive C Source File }-------- */
#ifndef PROG_HSM_H
#define PROG_HSM_H

/* This file contains public interface for the hierarchical state machine
 * driver. */

/*  MISRA-C:2012 Deviation List
 *
 *  MISRAC2012-1) Deviated Rule: 20.7 (required)
 *  Expressions resulting from the expansion of macro parameters shall be enclosed in parentheses.
 *
 *  Reason:
 *  The macro is used in function parameter declarations and definitions of structure member
 *  where the number of parentheses matter.
 *
 *  MISRAC2012-2) Deviated Rule: D4.6 (advisory)
 *     'typedefs' that indicate size and signedness should be used in place
 *     of the basic types.
 *
 *     Reason:
 *     Platform depended 'char' type is only used to define debugging
 *     strings on Windows.
 *
 */

/* NOCOV List
 *
 * NOCOV-TEMPLATE:
 *
 * Reason:
 * The file is a generated from a generic template that does not
 * respect all the OsekCore rules.
 */

/*==================[inclusions]============================================*/

#include <Std_Types.h>          /* AUTOSAR standard types */
#include <TSAutosar.h>          /* TS_ARCH_FAMILY */

#include <PROG_HsmCfg.h>         /* state machine user's configuration */

/*==================[macros]================================================*/
/* CHECK: NOPARSE */
/* NOCOV-TEMPLATE */

/** \brief Special value for the data type ::PROG_HsmStateIdxType
 *
 * Pseudo state index used for non-existend states. E.g. for the parent
 * state of the top state or the init substates of leaf states. */
#define PROG_HSM_SIDX_INVALID            0xFFU
/** \brief Special value for the data type ::PROG_HsmActionIdxType
 *
 * Used for non-existend actions. */
#define PROG_HSM_AIDX_INVALID            0xFFU
/** \brief Special value for the data type ::PROG_HsmGuardIdxType
 *
 * Used for non-existend guards. */
#define PROG_HSM_GIDX_INVALID            0xFFU

/** \brief Special value for the data type ::PROG_HsmEventType
 *
 * Invalid event */
#define PROG_HSM_EVENT_INVALID           0xFFU

/* Helper macros to enable building the sources with and without multiple
 * instances support */
#if (PROG_HSM_INST_MULTI_ENABLED == STD_ON)
/* parameter list for action, guard, entry, exit state functions */
#define PROG_PL_SF(a)                   a
/* parameter definition list for action, guard, entry, exit state functions */
#define PROG_PDL_SF(a)                  a
#define PROG_HSMINITINST(a,b)           PROG_HsmInitInst(a,b)
#define PROG_HSMEMITINST(a,b,c)         PROG_HsmEmitInst(a,b,c)
#define PROG_HSMEMITTOSELFINST(a,b,c)   PROG_HsmEmitToSelfInst(a,b,c)
#define PROG_HSMMAININST(a,b)           PROG_HsmMainInst(a,b)
/* instance access macro */
#define PROG_INST_ACCESS(array,instIdx) ((array)[(instIdx)])
#define PROG_INST(instIdx)              (instIdx)
#else
#define PROG_PL_SF(a)                   /* nothing */
#define PROG_PDL_SF(a)                  void
#define PROG_HSMINITINST(a,b)           PROG_HsmInitInst(a)
#define PROG_HSMEMITINST(a,b,c)         PROG_HsmEmitInst(a,c)
#define PROG_HSMEMITTOSELFINST(a,b,c)   PROG_HsmEmitToSelfInst(a,c)
#define PROG_HSMMAININST(a,b)           PROG_HsmMainInst(a)
#define PROG_INST_ACCESS(array,instIdx) ((array)[0U])
#define PROG_INST(instIdx)              0U
#endif

/* enable tracing capabilities only on windows */
#if defined(TS_WINDOWS) && (TS_ARCH_FAMILY == TS_WINDOWS)
#define PROG_HSM_TRACE                  STD_ON
#else
#define PROG_HSM_TRACE                  STD_OFF
#endif

/*==================[type definitions]======================================*/

/* ** Events ** */

/** \brief Type to encode single events.
 *
 * Event numbers are generated, they are zero-based and consecutive. */
typedef uint8  PROG_HsmEventType;

/** \brief Type to encode event masks.
 *
 * This type describes a bit encoded set of events. The event ev of type
 * ::PROG_HsmEventType corresponds to the (1 << ev) bit in the
 * ::PROG_HsmEventMaskType. */
typedef uint32 PROG_HsmEventMaskType;

/** \brief State index type definition */
typedef uint8  PROG_HsmStateIdxType;
/** \brief Action index type definition */
typedef uint8  PROG_HsmActionIdxType;
/** \brief Guard index type definition */
typedef uint8  PROG_HsmGuardIdxType;

/** \brief Hsm instance
 *
 * Struct for an instance of state machine, placed in NOINIT RAM */
struct PROG_HsmInstStruct
{
  /** \brief Id of the currently active state */
  PROG_HsmStateIdxType   stateId;

  /** \brief Id of source state during a transition */
  PROG_HsmStateIdxType   sourceId;

  /** \brief Number of events filled up in the queue */
  uint8                 evQueueFill;

  /** \brief Index into queue where events emitted to self have to be
   * inserted */
  uint8                 evQueueInsertEvNo;
};

/** \brief Type for state machine instance data */
typedef struct PROG_HsmInstStruct PROG_HsmInstType;

/** \brief Function pointer type for entry/exit/transition action functions */
typedef P2FUNC(void, PROG_CODE, PROG_HsmActionType)(
  PROG_PDL_SF(const uint8 instIdx));

/** \brief Function pointer type for guard functions */
typedef P2FUNC(boolean, PROG_CODE, PROG_HsmGuardType)(
  PROG_PDL_SF(const uint8 instIdx));

/* forward declaration */
struct PROG_HsmTranStruct;
/** \brief Type for state transition description */
typedef struct PROG_HsmTranStruct PROG_HsmTranType;

/** \brief Structure describing a single state of a state chart
 *
 * Type describing states and their relation in the statechart. State
 * descriptions are stored in ROM */
struct PROG_HsmStateStruct
{
  /** \brief Mask of non-deferred and non-ignored events
   *
   * Events related to real actions */
  PROG_HsmEventMaskType                         actionEventMask;
  /** \brief Mask of ignored events */
  PROG_HsmEventMaskType                         ignoredEventMask;

  /** \brief Pointer to array of transitions from this state */
  P2CONST(PROG_HsmTranType, TYPEDEF, PROG_CONST) trans;

  /** \brief Parent state ID */
  PROG_HsmStateIdxType                          parentId;
  /** \brief Init substate, if initId == ::PROG_HSM_SIDX_INVALID there is no
   * substate */
  PROG_HsmStateIdxType                          initId;
  /** \brief Function pointer of entry handler function */
  PROG_HsmActionIdxType                         entryFnIdx;

  /** \brief Function pointer of exit handler function */
  PROG_HsmActionIdxType                         exitFnIdx;

  /** \brief Function pointer of do handler function */
  PROG_HsmActionIdxType                         doFnIdx;

  /** \brief Number of transitions originating from this state */
  uint8                                        numTrans;
};

/** \brief Type for state description */
typedef struct PROG_HsmStateStruct PROG_HsmStateType;

/** \brief State chart description data
 *
 * This struct is placed in ROM */
struct PROG_HsmStatechartStruct
{
  /** \brief Pointer to state description array */
  P2CONST(PROG_HsmStateType, TYPEDEF, PROG_CONST)     states;

  /** \brief Pointer to array containing the Hsm instance working data in
   * RAM */
  P2VAR(PROG_HsmInstType, TYPEDEF, PROG_VAR_NOINIT)   instances;

  /** \brief Pointer to array of all entry/exit/transition function
   * pointers */
  P2CONST(PROG_HsmActionType, TYPEDEF, PROG_CONST)    actions;

  /** \brief Pointer to array of all guard function pointers */
  P2CONST(PROG_HsmGuardType, TYPEDEF, PROG_CONST)     guards;

  /** \brief Pointer to event counter array
   *
   * Total array size equals to (numInstances * numEvents).
   *
   *  for instance #n are located in array fields events[n*numEvents]
   * .. events[(n+1)*numEvents-1] */
  P2VAR(uint8, TYPEDEF, PROG_VAR_NOINIT)             evCounters;

  /** \brief Pointer to event queue for this hsm instance
   *
   * Total array size equals to (numInstances * numEvents).
   *
   * Events for instance #n are located in array fields events[n*numEvents]
   * .. events[(n+1)*numEvents-1] */
  P2VAR(PROG_HsmEventType, TYPEDEF, PROG_VAR_NOINIT)  events;

#if defined(TS_WINDOWS) && (TS_ARCH_FAMILY == TS_WINDOWS)
  /* name of the HSM (for debugging on Windows) */
  /* Deviation MISRAC2012-2 <+9> */
  /* Deviation MISRAC2012-1 <+9> */
  P2CONST(char, PROG_CONST, PROG_CONST)               hsmName;
  P2CONST(P2CONST(char, PROG_CONST, PROG_CONST), PROG_CONST, PROG_CONST) stateNames;
  P2CONST(P2CONST(char, PROG_CONST, PROG_CONST), PROG_CONST, PROG_CONST) actionNames;
  P2CONST(P2CONST(char, PROG_CONST, PROG_CONST), PROG_CONST, PROG_CONST) guardNames;
  P2CONST(P2CONST(char, PROG_CONST, PROG_CONST), PROG_CONST, PROG_CONST) eventNames;
#endif

  /** \brief Number of available events in the state chart */
  uint8                                             numEvents;

  /** \brief Id of the state chart */
  uint8                                             stateChartId;

  /** \brief Number of hsm instances */
  uint8                                             numInstances;
  /** \brief ID of the top state */
  PROG_HsmStateIdxType                               topStateId;
};

/** \brief Type for state chart description */
typedef struct PROG_HsmStatechartStruct PROG_HsmStatechartType;

/** \brief Pointer type to state chart description */
typedef P2CONST(PROG_HsmStatechartType, TYPEDEF, PROG_CONST)
  PROG_HsmStatechartPtrType;


/** \brief State transition
 *
 * Struct type describing a transition in the statechart. Transition
 * descriptions are stored in ROM */
struct PROG_HsmTranStruct
{
  /** \brief Pointer to array of transition step indices */
  P2CONST(PROG_HsmActionIdxType, TYPEDEF, PROG_CONST) steps;

  /** \brief Number of transition steps */
  uint8                                             numSteps;

  /** \brief Triggering event for transition */
  PROG_HsmEventType                                  event;

  /** \brief Index of transition guard function */
  PROG_HsmGuardIdxType                               guardFnIdx;

  /** \brief ID of the target state */
  PROG_HsmStateIdxType                               target;
};

/*==================[external function declarations]========================*/

#define PROG_START_SEC_CODE
#include <MemMap.h>

/*------------------ init functions ----------------------------------------*/

#if (PROG_HSM_INST_MULTI_ENABLED == STD_ON)
/** \brief Init all hsm instances of single state chart
 **
 ** \param sc pointer to state chart which shall be initialized */
extern FUNC(void, PROG_CODE) PROG_HsmInit(const PROG_HsmStatechartPtrType sc);
#else
/** \brief Init hsm instance of single state chart
 **
 ** \param sc pointer to state chart which shall be initialized */
#define PROG_HsmInit(sc) PROG_HSMINITINST((sc),0U)
#endif

/** \brief Init single instance of one hsm
 **
 ** \param sc pointer to state chart which shall be initialized
 ** \param instIdx index of target instance */
extern FUNC(void, PROG_CODE) PROG_HSMINITINST(
  const PROG_HsmStatechartPtrType sc,
  const uint8                    instIdx);

/*------------------ emit functions ----------------------------------------*/

#if (PROG_HSM_INST_MULTI_ENABLED == STD_ON)
/** \brief Send an event to all instances of a state chart
 ** \param sc Pointer to target state chart
 ** \param ev event
 ** \return Success status of function
 ** \retval E_OK event was queued successfully
 ** \retval E_NOT_OK event queue overflow
 **
 ** The event is sent to all instances of the state machine. */
extern FUNC(void, PROG_CODE) PROG_HsmEmit(
  const PROG_HsmStatechartPtrType sc,
  const PROG_HsmEventType         event);

/** \brief Send an event to all instances of a state chart
 ** \param sc Pointer to target state chart
 ** \param ev event
 ** \return Success status of function
 ** \retval E_OK event was queued successfully
 ** \retval E_NOT_OK event queue overflow
 **
 ** The event is sent to all instances of the state machine. */
extern FUNC(Std_ReturnType, PROG_CODE) PROG_HsmEmitToSelf(
  const PROG_HsmStatechartPtrType sc,
  const PROG_HsmEventType         event);
#else
/** \brief Send an event to a state chart
 ** \param sc Pointer to target state chart
 ** \param ev event
 ** \return Success status of function
 ** \retval E_OK event was queued successfully
 ** \retval E_NOT_OK event queue overflow
 **
 ** The event is sent to the only instance of the state machine. */
#define PROG_HsmEmit(sc,event)       PROG_HsmEmitInst((sc),(event))

/** \brief Send an event to a state chart from
 ** within the state machine functions
 ** \param sc Pointer to target state chart
 ** \param ev event
 ** \return Success status of function
 ** \retval E_OK event was queued successfully
 ** \retval E_NOT_OK event queue overflow
 **
 ** The event is sent to the only instance of the state machine. */
#define PROG_HsmEmitToSelf(sc,event) PROG_HsmEmitToSelfInst((sc),(event))

#endif

/** \brief Send an event to a specific instance of the state machine
 ** \param sc target state chart
 ** \param instIdx index of target instance
 ** \param ev event
 ** \return Success status of function
 ** \retval E_OK event was queued successfully
 ** \retval E_NOT_OK event queue overflow */
extern FUNC(void, PROG_CODE) PROG_HSMEMITINST(
  const PROG_HsmStatechartPtrType sc,
  const uint8                    instIdx,
  const PROG_HsmEventType         event);

/** \brief Send an event to a specific instance of the state machine from
 ** within the state machine functions
 ** \param sc target state chart
 ** \param instIdx index of target instance
 ** \param ev event
 ** \return Success status of function
 ** \retval E_OK event was queued successfully
 ** \retval E_NOT_OK event queue overflow */
extern FUNC(void, PROG_CODE) PROG_HSMEMITTOSELFINST(
  const PROG_HsmStatechartPtrType sc,
  const uint8                    instIdx,
  const PROG_HsmEventType         event);

/*------------------ main functions ----------------------------------------*/

#if (PROG_HSM_INST_MULTI_ENABLED == STD_ON)
/** \brief Process events for one state chart
 ** \param sc pointer to state charts
 **
 ** This function calls PROG_HsmMainInst() for all instances of the state
 ** machine described in sc until all events are processed. */
extern FUNC(void, PROG_CODE) PROG_HsmMain(const PROG_HsmStatechartPtrType sc);
#else
/** \brief Process events for one state chart
 ** \param sc pointer to state charts
 **
 ** This function calls PROG_HsmMainInst() for the only instance of the state
 ** machine described in sc. */
#define PROG_HsmMain(sc) ((void)PROG_HSMMAININST((sc),0U))
#endif

/** \brief Process events of a state chart in one state machine instance
 ** \param sc state chart
 ** \param instIdx index of target instance
 ** \return Event processing status
 ** \retval TRUE at least one event was processed which may have lead to an
 ** action or a state change
 ** \retval FALSE No action or state change performed due to event
 ** processing */
extern FUNC(boolean, PROG_CODE) PROG_HSMMAININST(
    const PROG_HsmStatechartPtrType sc,
    const uint8                    instIdx);

/*------------------ helper functions --------------------------------------*/

#if (PROG_HSM_TRACE == STD_ON)
/** \brief Switches tracing on or off
 ** \param newValue new tracing, TRUE for on and FALSE for off */
extern FUNC(void, PROG_CODE) PROG_HsmSetTracing(const boolean newValue);
#endif

#define PROG_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/
/* CHECK: PARSE */
#endif
/*==================[end of file]===========================================*/
