/* Mk_task.h - task configuration and handling
 *
 * This file contains definitions for configuration and handling of tasks.
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef MK_TASK_H
#define MK_TASK_H

#include <private/Mk_thread.h>
#include <private/Mk_interrupt.h>
#include <private/Mk_event.h>
#include <private/Mk_types_forward.h>
#include <private/Mk_message.h>
#include <public/Mk_error.h>

#ifndef MK_ASM

typedef struct mk_task_s mk_task_t;

/* Task configuration structure.
*/
struct mk_taskcfg_s
{
	mk_threadcfg_t threadCfg;
	mk_task_t *dynamic;
	mk_thread_t *thread;
	mk_stackelement_t *stack;
	mk_int_t maxActivations;
	mk_eventstatus_t *eventStatus;
};

/* Task dynamic state structure.
*/
struct mk_task_s
{
	mk_int_t activationCount;
};

extern const mk_objquantity_t MK_nTasks;
extern const mk_taskcfg_t * const MK_taskCfg;

/* Construction macros for task config structure.
*/
#define MK_TASKCFG(dyn, thr, reg, name, cor, stk, sp, ent, pm, ilvl, ie, fpu, hws, qpri, rpri, maxa,			\
				   partIdx, tid, exBgt, lkBgt, aid)																\
{																												\
	MK_THREADCFG((reg), (name), (cor), (sp), (ent), (pm), (ilvl), (ie), (fpu), (hws), (qpri), (rpri),			\
					(partIdx), (tid), MK_OBJTYPE_TASK, (exBgt), (lkBgt), (aid)),								\
	(dyn),																										\
	(thr),																										\
	(stk),																										\
	(maxa),																										\
	MK_NULL																										\
}

#define MK_ETASKCFG(dyn, thr, reg, name, cor, stk, sp, ent, pm, ilvl, ie, fpu, hws, qpri, rpri, evtptr,			\
					partIdx, tid, exBgt, lkBgt, aid)															\
{																												\
	MK_THREADCFG((reg), (name), (cor), (sp), (ent), (pm), (ilvl), (ie), (fpu), (hws), (qpri), (rpri),			\
					(partIdx), (tid), MK_OBJTYPE_TASK, (exBgt), (lkBgt), (aid)),								\
	(dyn),																										\
	(thr),																										\
	(stk),																										\
	1,																											\
	(evtptr)																									\
}

#endif

/* MK_LocalActivateTask() - internal kernel function to activate a given task on the caller's core.
 * MK_LocalSetEvent() - internal kernel function to set events for a given task on the caller's core.
 * MK_LocalGetTaskState() - internal kernel function to get the state of a given task on the caller's core.
*/
#ifndef MK_ASM
void MK_ClearTasks(mk_objectid_t);
mk_errorid_t MK_LocalActivateTask(mk_kernelcontrol_t *, mk_objectid_t, const mk_taskcfg_t *, mk_objectid_t);
mk_errorid_t MK_LocalSetEvent(mk_kernelcontrol_t *, mk_objectid_t, const mk_taskcfg_t *,
																			mk_eventmask_t, mk_objectid_t);
mk_errorid_t MK_LocalGetTaskState(mk_kernelcontrol_t *, mk_objectid_t, const mk_taskcfg_t *, mk_taskstate_t *);
#endif

#if MK_MAXCORES > 1
/* MK_MultiActivateTask() - internal kernel function to activate a given task on any core.
 * MK_MultiSetEvent() - internal kernel function to set events for a given task on any core.
 * MK_MultiGetTaskState() - internal kernel function to get the state of a given task on any core.
 * Only available on multi-core systems.
*/
#ifndef MK_ASM
mk_errorid_t MK_MultiActivateTask(mk_kernelcontrol_t *, mk_objectid_t, mk_xcall_t, mk_objectid_t);
mk_errorid_t MK_MultiSetEvent(mk_kernelcontrol_t *, mk_objectid_t, const mk_taskcfg_t *, mk_eventmask_t,
																					mk_xcall_t, mk_objectid_t);
mk_errorid_t MK_MultiGetTaskState(mk_kernelcontrol_t *, mk_objectid_t, const mk_taskcfg_t *, mk_taskstate_t *);
#endif

/* MK_InternActivateTask(), MK_InternSetEvent() and MK_InternGetTaskState() -  the multi-core case.
 *
 * !LINKSTO Microkernel.Function.MK_InternActivateTask, 2
 * !LINKSTO Microkernel.Function.MK_InternSetEvent, 2
 * !LINKSTO Microkernel.Function.MK_InternGetTaskState, 1
 * !doctype src
*/
#define MK_InternActivateTask(cv, t, mc, a)		MK_MultiActivateTask((cv), (t), (mc), (a))
#define MK_InternSetEvent(cv, t, tc, e, mc, a)	MK_MultiSetEvent((cv), (t), (tc), (e), (mc), (a))
#define MK_InternGetTaskState(cv, t, tc, s)		MK_MultiGetTaskState((cv), (t), (tc), (s))

#else

/* MK_InternActivateTask(), MK_InternSetEvent() and MK_InternGetTaskState() -  the single-core case.
 *
 * !LINKSTO Microkernel.Function.MK_InternActivateTask, 2
 * !LINKSTO Microkernel.Function.MK_InternSetEvent, 2
 * !LINKSTO Microkernel.Function.MK_InternGetTaskState, 1
 * !doctype src
*/
#define MK_InternActivateTask(cv, t, mc, a)		MK_LocalActivateTask((cv), (t), &MK_taskCfg[(t)], (a))
#define MK_InternSetEvent(cv, t, tc, e, mc, a)	MK_LocalSetEvent((cv), (t), (tc), (e), (a))
#define MK_InternGetTaskState(cv, t, tc, s)		MK_LocalGetTaskState((cv), (t), (tc), (s))

#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
