/* --------{ EB Automotive C Source File }-------- */

/* This file contains the implementation of the hierarchical state machine
 * driver. */

/*  MISRA-C:2012 Deviation List
 *
 *  MISRAC2012-1) Deviated Rule: 21.1 (required)
 *     #define and #undef shall not be used on a reserved identifier or reserved macro name.
 *
 *     Reason:
 *     Library function printf() which is defined inside library <stdio.h> is used in this file,
 *     for debugging purpose only.
 *
 *  MISRAC2012-2) Deviated Rule: 21.6 (required)
 *     The Standard Library input/output functions shall not be used.
 *
 *     Reason:
 *     Library function printf() which is defined inside library <stdio.h> is used in this file,
 *     for debugging purpose only.
 *
 *  MISRAC2012-3) Deviated Rule: 14.2 (required)
 *     A for loop shall be well-formed.
 *
 *     Reason:
 *     MISRA rule 14.2 is not deviated. This is a 'false positive' in the MISRA checker.
 *
 *  MISRAC2012-4) Deviated Rule: 20.7 (required)
 *     expanded macro parameter shall be enclosed in parentheses.
 *
 *     Reason:
 *     It is used in function parameter declarations and definitions or as structure member.
 *
 *  MISRAC2012-5) Deviated Rule: 10.4 (required)
 *     Both operands of an operator in which the usual arithmetic conversions are performed shall have the
 *     same essential type category.
 *
 *     Reason:
 *     used for only for printing the string no functional impact.
 *
 */


/* CHECK: RULE 506 OFF (Variables may not start lower case) */

 /* CERT-C Deviation List
 *
 * CERTC-1) Deviated Rule: DCL.37
 * Do not declare or define a reserved identifier
 *
 * Reason:
 * Library function printf() which is defined inside library <stdio.h>
 * is used in this file,for debugging purpose only.
 *
 * CERTC-2) Deviated Rule: EXP.36
 * Do not cast pointers into more strictly aligned pointer types
 *
 * Reason:
 * This initialisation of pointer to NULL is needed at this place as otherwise it can result in
 * no value assigned in certain conditions and this will have a junk value if not initialised.
 */
/*==================[inclusions]============================================*/

#include <PROG_HsmTrace.h>
#include <Std_Types.h>          /* AUTOSAR standard types */

#include <SchM_PROG.h>           /* SchM symbols for crit. sections */

#include <PROG_Hsm.h>            /* public API of PROG_Hsm.c */

/* design debugging output */
#if (PROG_HSM_TRACE == STD_ON)
/* CHECK: RULE 501 OFF (macro needed in std headers) */
/* Deviation MISRAC2012-1 */
/* Deviation CERTC-1 */
#define __NO_ISOCEXT
#include <stdlib.h>
/* Deviation MISRAC2012-2 */
#include <stdio.h>
/* CHECK: RULE 501 ON */
#endif

/*==================[macros]================================================*/
#if (PROG_HSM_INST_MULTI_ENABLED == STD_ON)
#define PROG_HSM_DEL_FROM_QUEUE(a,b,c) PROG_HsmDelFromQueue(a,b,c)
#define PROG_HSM_TRAN(a,b,c)           PROG_HsmTran(a,b,c)
#define PROG_HSM_INIT_SUBSTATES(a,b)   PROG_HsmInitSubstates(a,b)
#define PROG_HSM_FIND_EV_TO_DISPATCH(a,b,c,d) PROG_HsmFindEvToDispatch(a,b,c,d)
#define PROG_HSM_DISPATCH_EVENT(a,b,c) PROG_HsmDispatchEvent(a,b,c)

/** \brief Access entry in event queue of a specific hsm instance */
#define PROG_EV_QUEUE_ENTRY(sc,instIdx,entryIdx) \
  ((sc)->events[((instIdx)*((sc)->numEvents))+(entryIdx)])
#define PROG_EV_COUNTER_ENTRY(sc,instIdx,entryIdx) \
  ((sc)->evCounters[((instIdx)*((sc)->numEvents))+(entryIdx)])
#else
#define PROG_HSM_DEL_FROM_QUEUE(a,b,c) PROG_HsmDelFromQueue(a,c)
#define PROG_HSM_TRAN(a,b,c)           PROG_HsmTran(a,c)
#define PROG_HSM_INIT_SUBSTATES(a,b)   PROG_HsmInitSubstates(a)
#define PROG_HSM_FIND_EV_TO_DISPATCH(a,b,c,d) PROG_HsmFindEvToDispatch(a,c,d)
#define PROG_HSM_DISPATCH_EVENT(a,b,c) PROG_HsmDispatchEvent(a,c)
#define PROG_EV_QUEUE_ENTRY(sc,instIdx,entryIdx) \
  ((sc)->events[(entryIdx)])
#define PROG_EV_COUNTER_ENTRY(sc,instIdx,entryIdx) \
  ((sc)->evCounters[(entryIdx)])
#endif

#if (PROG_HSM_TRACE == STD_ON)
#define PROG_HSM_PRINT1(a)                       \
  do                                            \
  {                                             \
    if (PROG_HsmTraceEnabled == TRUE)            \
    {                                           \
      (void)printf("HsmTrace: " a);             \
    }                                           \
  } while (0U)
#define PROG_HSM_PRINT2(a,b)                     \
  do                                            \
  {                                             \
    if (PROG_HsmTraceEnabled == TRUE)            \
    {                                           \
      (void)printf("HsmTrace: " a,(b));         \
    }                                           \
  } while (0U)
/* Deviation MISRAC2012-2 */
#define PROG_HSM_PRINT3(a,b,c)                   \
  do                                            \
  {                                             \
    if (PROG_HsmTraceEnabled == TRUE)            \
    {                                           \
      (void)printf("HsmTrace: " a,(b),(c));     \
    }                                           \
  } while (0U)
#define PROG_HSM_PRINT4(a,b,c,d)                 \
  do                                            \
  {                                             \
    if (PROG_HsmTraceEnabled == TRUE)            \
    {                                           \
      (void)printf("HsmTrace: " a,(b),(c),(d)); \
    }                                           \
  } while (0U)
#define PROG_HSM_PRINT5(a,b,c,d,e)               \
  do                                            \
  {                                             \
    if (PROG_HsmTraceEnabled == TRUE)            \
    {                                           \
      (void)printf("HsmTrace: " a,(b),(c),(d),(e));  \
    }                                           \
  } while (0U)
#else
#define PROG_HSM_PRINT1(a)          /* nothing */
#define PROG_HSM_PRINT2(a,b)        /* nothing */
#define PROG_HSM_PRINT3(a,b,c)      /* nothing */
#define PROG_HSM_PRINT4(a,b,c,d)    /* nothing */
#define PROG_HSM_PRINT5(a,b,c,d,e)  /* nothing */
#endif

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

#define PROG_START_SEC_CODE
#include <MemMap.h>

/** \brief Delete entry from event queue
 ** \param sc pointer to state chart
 ** \param instIdx index of state machine instance to work on
 ** \param queueEntryNo entry in queue to delete
 **
 ** This function must be called inside of a critical section which prevents
 ** the concurrent access to the queue.
 **/
STATIC FUNC(void, PROG_CODE) PROG_HSM_DEL_FROM_QUEUE(
  const PROG_HsmStatechartPtrType sc,
  const uint8                    instIdx,
  const uint8                    queueEntryNo);

/** \brief Execute a transition
 ** \param sc pointer to state chart
 ** \param instIdx index of state machine instance to work on
 ** \param tran Pointer to the transition description struct */
STATIC FUNC(void, PROG_CODE) PROG_HSM_TRAN(
  const PROG_HsmStatechartPtrType                      sc,
  const uint8                                         instIdx,
  CONSTP2CONST(PROG_HsmTranType, AUTOMATIC, PROG_CONST) tran);

/** \brief Initialize all substates for the current state
 ** \param sc pointer to state chart to work on
 ** \param instIdx index of state machine instance to work on */
STATIC FUNC(void, PROG_CODE) PROG_HSM_INIT_SUBSTATES(
  const PROG_HsmStatechartPtrType sc,
  const uint8                    instIdx);

/** \brief Look for dispatchable event in event queue
 ** \param sc pointer to state chart to work on
 ** \param instIdx index of state machine instance to work on
 ** \param event identified event from queue
 ** \param queueEntryNo index in queue for identified event
 ** \return look up status
 ** \retval TRUE an event is found in the queue and it is not deferred
 ** and not ignored
 ** \retval FALSE no event is not found or one which is deferred or one
 ** which is ignored in the current state
 **
 ** Events which are marked to be ignored in the current state are deleted
 ** from the queue within this function. */
STATIC FUNC(boolean, PROG_CODE) PROG_HSM_FIND_EV_TO_DISPATCH(
  const PROG_HsmStatechartPtrType                     sc,
  const uint8                                        instIdx,
  CONSTP2VAR(PROG_HsmEventType, AUTOMATIC, AUTOMATIC) event,
  CONSTP2VAR(uint8, AUTOMATIC, AUTOMATIC)            queueEntryNo);

/** \brief Dispatch event from event queue
 ** \param sc pointer to state chart to work on
 ** \param instIdx index of state machine instance to work on
 ** \param event identified event from queue
 ** \return Transition fired indicator
 ** \retval TRUE the event dispatching resulted in an fired transition
 ** \retval FALSE else */
STATIC FUNC(boolean, PROG_CODE) PROG_HSM_DISPATCH_EVENT(
  const PROG_HsmStatechartPtrType sc,
  const uint8                    instIdx,
  const PROG_HsmEventType         event);

#define PROG_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

#if (PROG_HSM_TRACE == STD_ON)

#define PROG_START_SEC_VAR_INIT_8
#include <MemMap.h>

STATIC VAR(boolean, PROG_VAR) PROG_HsmTraceEnabled = FALSE;

#define PROG_STOP_SEC_VAR_INIT_8
#include <MemMap.h>

#endif

/*==================[external function definitions]=========================*/

#define PROG_START_SEC_CODE
#include <MemMap.h>

/*------------------ init functions ----------------------------------------*/

/* CHECK: NOPARSE */
/* NOCOV-TEMPLATE */
#if (PROG_HSM_INST_MULTI_ENABLED == STD_ON)
FUNC(void, PROG_CODE) PROG_HsmInit(const PROG_HsmStatechartPtrType sc)
{
  uint8 instIdx;
  DBG_PROG_HSMINIT_ENTRY(sc);
  for (instIdx = 0U; instIdx < sc->numInstances; ++instIdx)
  {
    PROG_HSMINITINST(sc, instIdx);
  }
  DBG_PROG_HSMINIT_EXIT(sc);
}
/* else: function is implemented as macro and maps to PROG_HsmInitInst() */
#endif
/* CHECK: PARSE */

FUNC(void, PROG_CODE) PROG_HSMINITINST(
  const PROG_HsmStatechartPtrType sc,
  const uint8                    instIdx)
{
  CONSTP2VAR(PROG_HsmInstType, AUTOMATIC, PROG_VAR_NOINIT) inst
    = &PROG_INST_ACCESS(sc->instances, instIdx);
  uint8 i;

  PROG_HsmStateIdxType oldState;

  DBG_PROG_HSMINITINST_ENTRY(sc, instIdx);

  /* Deviation MISRAC2012-2 */
  PROG_HSM_PRINT3("%s %d Init\n", sc->hsmName, PROG_INST(instIdx));

  /* init all fields because the struct is placed in a NOINIT memory
   * section */
  oldState = inst->stateId;
  inst->stateId  = sc->topStateId;
  inst->sourceId = PROG_HSM_SIDX_INVALID;

  for (i = 0U; i < sc->numEvents; ++i)
  {
    PROG_EV_QUEUE_ENTRY(sc, instIdx, i) = 0U;
    PROG_EV_COUNTER_ENTRY(sc, instIdx, i) = 0U;
  }
  inst->evQueueFill       = 0U;
  inst->evQueueInsertEvNo = 0U;
/* CHECK: NOPARSE */
  if (sc->states[inst->stateId].entryFnIdx != PROG_HSM_AIDX_INVALID)
  {
    /* Deviation MISRAC2012-2 */
    PROG_HSM_PRINT4(
      "%s %d %s\n",
      sc->hsmName, PROG_INST(instIdx), sc->actionNames[inst->stateId]);

    /* enter top state */
    sc->actions[sc->states[inst->stateId].entryFnIdx](PROG_PL_SF(instIdx));
  }
/* CHECK: PARSE */
  /* init all substates */
  PROG_HSM_INIT_SUBSTATES(sc, instIdx);
  DBG_PROG_GENERIC_GRP((sc->stateChartId), (instIdx), (oldState), (inst->stateId));

  DBG_PROG_HSMINITINST_EXIT(sc, instIdx);
}

/*------------------ emit functions ----------------------------------------*/

/* CHECK: NOPARSE */
/* NOCOV-TEMPLATE */
#if (PROG_HSM_INST_MULTI_ENABLED == STD_ON)
FUNC(void, PROG_CODE) PROG_HsmEmit(
  const PROG_HsmStatechartPtrType sc,
  const PROG_HsmEventType         event)
{
  uint8 instIdx;

  DBG_PROG_HSMEMIT_ENTRY(sc, event);

  for (instIdx = 0U; instIdx < sc->numInstances; ++instIdx)
  {
    PROG_HSMEMITINST(sc, instIdx, event);
  }
  DBG_PROG_HSMEMIT_EXIT(sc, event);
}
/* else: function is implemented as macro */
#endif
/* CHECK: PARSE */

FUNC(void, PROG_CODE) PROG_HSMEMITINST(
  const PROG_HsmStatechartPtrType sc,
  const uint8                    instIdx,
  const PROG_HsmEventType         event)
{
  CONSTP2VAR(PROG_HsmInstType, AUTOMATIC, PROG_VAR_NOINIT) inst
    = &PROG_INST_ACCESS(sc->instances, instIdx);

  DBG_PROG_HSMEMITINST_ENTRY(sc, instIdx, event);

  SchM_Enter_PROG_SCHM_PROG_EXCLUSIVE_AREA_0();
  /* in case the event has already been queued don't add it again to the queue*/
  if ( PROG_EV_COUNTER_ENTRY(sc, instIdx, event) < 1U)
  {
    PROG_EV_QUEUE_ENTRY(sc, instIdx, inst->evQueueFill) = event;
    inst->evQueueFill++;
    /* leave evQueueInsertEvNo unchanged, this pointer will be updated on
     * insertion or event dispatching */
    ++PROG_EV_COUNTER_ENTRY(sc, instIdx, event);
  }
  SchM_Exit_PROG_SCHM_PROG_EXCLUSIVE_AREA_0();

  /* Deviation MISRAC2012-2 */
  PROG_HSM_PRINT4(
    "%s %d event %s enqueued\n",
    sc->hsmName, PROG_INST(instIdx), sc->eventNames[event]);

  DBG_PROG_HSMEMITINST_EXIT(sc, instIdx, event);
}

/* CHECK: NOPARSE */
/* NOCOV-TEMPLATE */
FUNC(void, PROG_CODE) PROG_HSMEMITTOSELFINST(
  const PROG_HsmStatechartPtrType sc,
  const uint8                    instIdx,
  const PROG_HsmEventType         event)
{
  CONSTP2VAR(PROG_HsmInstType, AUTOMATIC, PROG_VAR_NOINIT) inst
    = &PROG_INST_ACCESS(sc->instances, instIdx);

  DBG_PROG_HSMEMITTOSELFINST_ENTRY(sc, instIdx, event);

  SchM_Enter_PROG_SCHM_PROG_EXCLUSIVE_AREA_0();
  if ( PROG_EV_COUNTER_ENTRY(sc, instIdx, event) < 1U)
  {
    /* make room for new entry */
    uint8 j;
    for (j = inst->evQueueFill; j > inst->evQueueInsertEvNo; --j)
    {
      PROG_EV_QUEUE_ENTRY(sc, instIdx, j) = PROG_EV_QUEUE_ENTRY(sc, instIdx, j-1U);
    }
    ++inst->evQueueFill;
    ++PROG_EV_COUNTER_ENTRY(sc, instIdx, event);
    PROG_EV_QUEUE_ENTRY(sc, instIdx, inst->evQueueInsertEvNo) = event;
    inst->evQueueInsertEvNo++;
  }
  SchM_Exit_PROG_SCHM_PROG_EXCLUSIVE_AREA_0();

  /* Deviation MISRAC2012-2 */
  PROG_HSM_PRINT4(
    "%s %d event %s enqueued internally\n",
    sc->hsmName, PROG_INST(instIdx), sc->eventNames[event]);

  DBG_PROG_HSMEMITTOSELFINST_EXIT(sc, instIdx, event);
}
/* CHECK: PARSE */

/*------------------ main functions ----------------------------------------*/

/* CHECK: NOPARSE */
/* NOCOV-TEMPLATE */
#if (PROG_HSM_INST_MULTI_ENABLED == STD_ON)
FUNC(void, PROG_CODE) PROG_HsmMain(const PROG_HsmStatechartPtrType sc)
{
  boolean transitionFired;

  do
  {
    uint8 instIdx;
    transitionFired = FALSE;
    /* for all instances */
    for (instIdx = 0U; instIdx < sc->numInstances; ++instIdx)
    {
      const boolean retVal = PROG_HsmMainInst(sc, instIdx);
      transitionFired = (retVal || transitionFired);
    }
  } while (transitionFired);
}
/* else: function is implemented as macro and maps to PROG_HsmMainInst() */
#endif
/* CHECK: PARSE */

FUNC(boolean, PROG_CODE) PROG_HSMMAININST(
  const PROG_HsmStatechartPtrType sc,
  const uint8                    instIdx)
{
  CONSTP2VAR(PROG_HsmInstType, AUTOMATIC, PROG_VAR_NOINIT) inst
    = &PROG_INST_ACCESS(sc->instances,instIdx);
  /* return value, flag indicating if at least one transition fired */
  boolean          transitionFired = FALSE;
  PROG_HsmEventType event;
  uint8            queueEntryNo;
  boolean          eventPending;

  DBG_PROG_HSMMAININST_ENTRY(sc, instIdx);

  /* Deviation MISRAC2012-2 */
  PROG_HSM_PRINT3(
    "%s %d Main\n",
    sc->hsmName, PROG_INST(instIdx));

  /* reset event insertion pointer to an invalid value, this will be set to a
   * valid location if the first event is being dispatched */
  inst->evQueueInsertEvNo = 0U;

  /* check if there are is at least one pending event */
  eventPending
    = PROG_HSM_FIND_EV_TO_DISPATCH(sc, instIdx, &event, &queueEntryNo);

/* CHECK: NOPARSE */
/* NOCOV-TEMPLATE */
  do
  {
    /* dispatch all pending events from event queue */
    while (TRUE == eventPending)
    {
      boolean retVal;
      /* delete event from queue */
      SchM_Enter_PROG_SCHM_PROG_EXCLUSIVE_AREA_0();
      PROG_HSM_DEL_FROM_QUEUE(sc, instIdx, queueEntryNo);
      SchM_Exit_PROG_SCHM_PROG_EXCLUSIVE_AREA_0();

      /* dispatch event */
      retVal = PROG_HSM_DISPATCH_EVENT(sc, instIdx, event);
      transitionFired = (retVal || transitionFired);

      eventPending
        = PROG_HSM_FIND_EV_TO_DISPATCH(sc, instIdx, &event, &queueEntryNo);
    }

    /* transitions performed, execute do actions of leaf and all parent
     * states */
    {
      PROG_HsmStateIdxType stateId = inst->stateId;
      do
      {
        CONSTP2CONST(PROG_HsmStateType, AUTOMATIC, PROG_CONST) state
          = &sc->states[stateId];

        if (PROG_HSM_AIDX_INVALID != state->doFnIdx)
        {
          /* Deviation MISRAC2012-2 */
          PROG_HSM_PRINT4(
            "%s %d %s\n",
            sc->hsmName, PROG_INST(instIdx), sc->actionNames[state->doFnIdx]);
          sc->actions[state->doFnIdx](PROG_PL_SF(instIdx));
        }

        stateId = state->parentId; /* goto parent state */
      } while (PROG_HSM_SIDX_INVALID != stateId);
    }
  } while (TRUE == eventPending);
/* CHECK: PARSE */

  DBG_PROG_HSMMAININST_EXIT(transitionFired, sc, instIdx);
  return transitionFired;
}

/* CHECK: NOPARSE */
/* NOCOV-TEMPLATE */
#if (PROG_HSM_TRACE == STD_ON)
FUNC(void, PROG_CODE) PROG_HsmSetTracing(const boolean newValue)
{
  DBG_PROG_HSMSETTRACING_ENTRY(newValue);
  PROG_HsmTraceEnabled = newValue;
  DBG_PROG_HSMSETTRACING_EXIT(newValue);
}
#endif
/* CHECK: PARSE */

#define PROG_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function definitions]=========================*/

#define PROG_START_SEC_CODE
#include <MemMap.h>

STATIC FUNC(void, PROG_CODE) PROG_HSM_DEL_FROM_QUEUE(
  const PROG_HsmStatechartPtrType sc,
  const uint8                    instIdx,
  const uint8                    queueEntryNo)
{
  /* delete event no queueEntryNo from queue */
  CONSTP2VAR(PROG_HsmInstType, AUTOMATIC, PROG_VAR_NOINIT) inst
    = &PROG_INST_ACCESS(sc->instances, instIdx);
  uint8 j;

  /* reduce the occurrence counter of the respective event */
  PROG_HsmEventType event = PROG_EV_QUEUE_ENTRY(sc, instIdx, queueEntryNo);
  --PROG_EV_COUNTER_ENTRY(sc, instIdx, event);

  DBG_PROG_HSM_DEL_FROM_QUEUE_ENTRY(sc, instIdx, queueEntryNo);

  /* Deviation MISRAC2012-3 */
  for (j = queueEntryNo; (j + 1U) < inst->evQueueFill; ++j)
  {
    PROG_EV_QUEUE_ENTRY(sc, instIdx, j)
      = PROG_EV_QUEUE_ENTRY(sc, instIdx, j + 1U);
  }
  --inst->evQueueFill;
  if (queueEntryNo < inst->evQueueInsertEvNo)
  {
    /* if this was an event emitted to self also decrement the insertion
     * pointer  */
    --inst->evQueueInsertEvNo;
  }
  /* no need to check for queueEntryNo >= inst->evQueueInsertEvNo here.  This
   * will be done before dispatching the next event from the queue */
  DBG_PROG_HSM_DEL_FROM_QUEUE_EXIT(sc, instIdx, queueEntryNo);
}

STATIC FUNC(void, PROG_CODE) PROG_HSM_TRAN(
  const PROG_HsmStatechartPtrType                      sc,
  const uint8                                         instIdx,
  CONSTP2CONST(PROG_HsmTranType, AUTOMATIC, PROG_CONST) tran)
{
  P2CONST(PROG_HsmStateType, AUTOMATIC, PROG_CONST) state;
  CONSTP2VAR(PROG_HsmInstType, AUTOMATIC, PROG_VAR_NOINIT) inst
      = &PROG_INST_ACCESS(sc->instances, instIdx);

  PROG_HsmStateIdxType oldState = inst->stateId;

  DBG_PROG_HSM_TRAN_ENTRY(sc, instIdx, tran);

  /* perform simplified transition for internal transitions */
  if (tran->target == PROG_HSM_SIDX_INVALID)
  {
    /* Deviation MISRAC2012-2 */
    PROG_HSM_PRINT4(
      "%s %d %s (internal transition)\n",
      sc->hsmName, PROG_INST(instIdx), sc->actionNames[tran->steps[0U]]);
    sc->actions[tran->steps[0U]](PROG_PL_SF(instIdx));
  }
  else /* external transitions */
  {
    uint8_least i;

    /* "source" may be a superstate of "state".  exit all states from "state"
     * until "source" is reached */
    while (inst->stateId != inst->sourceId)
    {
      state = &sc->states[inst->stateId];

      if (state->exitFnIdx != PROG_HSM_AIDX_INVALID)
      {
        /* Deviation MISRAC2012-2 */
        PROG_HSM_PRINT4(
          "%s %d %s\n",
          sc->hsmName, PROG_INST(instIdx), sc->actionNames[state->exitFnIdx]);
        sc->actions[state->exitFnIdx](PROG_PL_SF(instIdx));
      }

      inst->stateId = state->parentId;
    }

    /* execute exit/transiton/entry actions on transition path */
    for (i = 0U; i < tran->numSteps; ++i)
    {
      /* Deviation MISRAC2012-2 */
      PROG_HSM_PRINT4(
        "%s %d %s\n",
        sc->hsmName, PROG_INST(instIdx), sc->actionNames[tran->steps[i]]);
      sc->actions[tran->steps[i]](PROG_PL_SF(instIdx));
    }

    /* set the new current state and perform init steps of substates */
    inst->stateId = tran->target; /* current state is last entered state */
    PROG_HSM_INIT_SUBSTATES(sc, instIdx);

    /* Deviation MISRAC2012-2 */
    PROG_HSM_PRINT4(
      "%s %d transition to state %s finished\n",
      sc->hsmName, PROG_INST(instIdx), sc->stateNames[inst->stateId]);
  }

  DBG_PROG_GENERIC_GRP((sc->stateChartId), (instIdx), (oldState), (inst->stateId));
  DBG_PROG_HSM_TRAN_EXIT(sc, instIdx, tran);
}

STATIC FUNC(void, PROG_CODE) PROG_HSM_INIT_SUBSTATES(
  const PROG_HsmStatechartPtrType sc,
  const uint8                    instIdx)
{
  CONSTP2VAR(PROG_HsmInstType, AUTOMATIC, PROG_VAR_NOINIT) inst
    = &PROG_INST_ACCESS(sc->instances,instIdx);

  PROG_HsmStateIdxType stateIdx = sc->states[inst->stateId].initId;

  DBG_PROG_HSM_INIT_SUBSTATES_ENTRY(sc, instIdx);

  while (stateIdx != PROG_HSM_SIDX_INVALID) /* init state if necessary */
  {
    P2CONST(PROG_HsmStateType, AUTOMATIC, PROG_CONST) state
      = &sc->states[stateIdx];

    inst->stateId = stateIdx; /* set new current state */
    /* enter the substate */
    if (state->entryFnIdx != PROG_HSM_AIDX_INVALID)
    {
      /* Deviation MISRAC2012-2 */
      PROG_HSM_PRINT4(
        "%s %d %s\n",
        sc->hsmName, PROG_INST(instIdx), sc->actionNames[state->entryFnIdx]);
      sc->actions[state->entryFnIdx](PROG_PL_SF(instIdx));
    }
    /* get next init state */
    stateIdx = state->initId;
  }
  DBG_PROG_HSM_INIT_SUBSTATES_EXIT(sc, instIdx);
}

STATIC FUNC(boolean, PROG_CODE) PROG_HSM_FIND_EV_TO_DISPATCH(
  const PROG_HsmStatechartPtrType                     sc,
  const uint8                                        instIdx,
  CONSTP2VAR(PROG_HsmEventType, AUTOMATIC, AUTOMATIC) event,
  CONSTP2VAR(uint8, AUTOMATIC, AUTOMATIC)            queueEntryNo)
{
    CONSTP2VAR(PROG_HsmInstType, AUTOMATIC, PROG_VAR_NOINIT) inst
      = &PROG_INST_ACCESS(sc->instances,instIdx);
    CONSTP2CONST(PROG_HsmStateType, AUTOMATIC, PROG_CONST) state
      = &sc->states[inst->stateId];
    boolean          foundEventToDispatch = FALSE;
    PROG_HsmEventType ev                   = PROG_HSM_EVENT_INVALID;
    uint8            entryNo              = 0U;

    DBG_PROG_HSM_FIND_EV_TO_DISPATCH_ENTRY(sc, instIdx, event, queueEntryNo);

    /* lock event queue access */
    SchM_Enter_PROG_SCHM_PROG_EXCLUSIVE_AREA_0();
/* CHECK: NOPARSE */
/* NOCOV-TEMPLATE */
    while ((entryNo < inst->evQueueFill)
           && (FALSE == foundEventToDispatch))
    {
      PROG_HsmEventMaskType eventMask;
      ev        = PROG_EV_QUEUE_ENTRY(sc, instIdx, entryNo);
      eventMask = (PROG_HsmEventMaskType)1UL << ev;

      if ((eventMask & state->ignoredEventMask) != 0U)
      {
        /* Deviation MISRAC2012-2 */
        PROG_HSM_PRINT4(
          "%s %d event %s ignored\n",
          sc->hsmName, PROG_INST(instIdx), sc->eventNames[ev]);

        /* delete event no 'entryNo' from queue */
        PROG_HSM_DEL_FROM_QUEUE(sc, instIdx, entryNo);
        /* do not increment entryNo */
      }
      else if ((eventMask & state->actionEventMask) != 0U)
      {
        if (inst->evQueueInsertEvNo <= entryNo)
        {
          /* if the insertion location is still unset (or pointing to an
           * invalid location) then set the insertion location to just after
           * the current event to be dispatched. */
          inst->evQueueInsertEvNo = entryNo + 1U;
        }
        /* leave while loop and dispatch event no entryNo */
        foundEventToDispatch = TRUE;
      }
      else
      {
        /* Deviation MISRAC2012-2 */
        PROG_HSM_PRINT4(
          "%s %d event %s deferred\n",
          sc->hsmName, PROG_INST(instIdx), sc->eventNames[ev]);

        /* found only deferred event, try next one in queue */
        ++entryNo;
      }
    }
/* CHECK: PARSE */
    SchM_Exit_PROG_SCHM_PROG_EXCLUSIVE_AREA_0();

    *event        = ev;
    *queueEntryNo = entryNo;

    DBG_PROG_HSM_FIND_EV_TO_DISPATCH_EXIT(foundEventToDispatch, sc, instIdx, event, queueEntryNo);
    return foundEventToDispatch;
}

STATIC FUNC(boolean, PROG_CODE) PROG_HSM_DISPATCH_EVENT(
  const PROG_HsmStatechartPtrType sc,
  const uint8                    instIdx,
  const PROG_HsmEventType         event)
{
  CONSTP2VAR(PROG_HsmInstType, AUTOMATIC, PROG_VAR_NOINIT) inst
    = &PROG_INST_ACCESS(sc->instances,instIdx);
/* Deviation CERTC-2 */
  P2CONST(PROG_HsmTranType, AUTOMATIC, PROG_CONST) trans = NULL_PTR;
  /* return value, flag indicating if at least one transition fired */
  boolean transitionFired = FALSE;
  /* flag for the trigger search algorithm */
  boolean triggerFound    = FALSE;

  DBG_PROG_HSM_DISPATCH_EVENT_ENTRY(sc, instIdx, event);

  /* *** search for transition for non-deferred and non-ignored event and
   * fire the transition if found *** */

  /* Deviation MISRAC2012-2 */
  PROG_HSM_PRINT5(
    "%s %d dispatching event %s in state %s\n",
    sc->hsmName, PROG_INST(instIdx), sc->eventNames[event],
    sc->stateNames[inst->stateId]);

  /* try current leaf state as src of transitions */
  inst->sourceId = inst->stateId;

  /* start searching for a triggering event */
  do
  {
    uint8_least i;          /* index in transition array of state */

    CONSTP2CONST(PROG_HsmStateType, AUTOMATIC, PROG_CONST) state
      = &sc->states[inst->sourceId];

    /* check all possible transitions of state */
    for (i = 0U; (i < state->numTrans) && (FALSE == triggerFound); ++i)
    {
      trans = &state->trans[i]; /* test next transition */

      if (event == trans->event)
      {
        /* evaluate guard condition */
        boolean guardCond = TRUE;

        if (trans->guardFnIdx != PROG_HSM_GIDX_INVALID)
        {
          guardCond = sc->guards[trans->guardFnIdx](PROG_PL_SF(instIdx));

          /* Deviation MISRAC2012-2, MISRAC2012-5 */
          PROG_HSM_PRINT5(
            "%s %d %s evaluates to %s\n",
            sc->hsmName, PROG_INST(instIdx),
            sc->guardNames[trans->guardFnIdx], (guardCond?"TRUE":"FALSE"));
        }

        if (TRUE == guardCond)
        {
          /* exit for loop and middle do-while loop in any case because we
           * have found at least one enabled transition for this event. */
          triggerFound    = TRUE;

          /* remember that some real event processing e.g. a state machine
           * action happened. In this case a subsequent call of this or other
           * dispatching functions may be necessary */
          transitionFired = TRUE;

          /* event+guard is OK: transition action is performed later after
           * loops are left and stack usage is lower */
        }
        /* else: if guard is false, then treat it as if the related
         * transition is not existing in the state chart model, "Practical
         * Statecharts", 2.ed, sect. 2.3.15  */
      }
    }

    if (FALSE == triggerFound)
    {
      /* we did not find the trigger in this state: try parent state as next
       * source state */
      inst->sourceId = state->parentId;
    }
  } while ((FALSE == triggerFound)
           && (PROG_HSM_SIDX_INVALID != inst->sourceId));

  /* a triggering event was found and transition is ready to be executed or
   * the top state is reached the queued event must be ignored
   *
   * we have to check if the top state is not yet reached at runtime because
   * there may still be non-ignored and not handled events due to false
   * guard conditions */

  if (TRUE == triggerFound)
  {
    PROG_HSM_TRAN(sc, instIdx, trans); /* execute the transition */
  }
  else
  {
    /* Deviation MISRAC2012-2 */
    PROG_HSM_PRINT4(
      "%s %d event %s ignored at top state\n",
      sc->hsmName, PROG_INST(instIdx), sc->eventNames[event]);
  }

  DBG_PROG_HSM_DISPATCH_EVENT_EXIT(transitionFired, sc, instIdx, event);
  return transitionFired;
}

#define PROG_STOP_SEC_CODE
#include <MemMap.h>
/*==================[end of file]===========================================*/
