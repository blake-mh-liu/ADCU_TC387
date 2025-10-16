/* Mk_thread.h - thread configuration and handling
 *
 * This file contains definitions for the hardware-independent part of
 * configuration and handling of threads. It also includes the hardware-specific
 * part.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_THREAD_H
#define MK_THREAD_H

#include <public/Mk_hwsel.h>
#include <public/Mk_public_types.h>
#include <public/Mk_error.h>

#include MK_HWSEL_PRV_THREAD

#include <private/Mk_accounting.h>
#include <private/Mk_types_forward.h>
#include <private/Mk_event.h>
#include <private/Mk_jobqueue.h>

/* Object IDs for MK_OBJTYPE_KERNEL
*/
#define MK_OBJID_IDLE			0
#define MK_OBJID_MAIN			1
#define MK_OBJID_BOOT			2
#define MK_OBJID_SHUTDOWN		3

/* Object ID for global hook functions
*/
#define MK_OBJID_GLOBAL			(-1)

#ifndef MK_ASM

/* mk_threadregisters_t is defined for the generator
*/
typedef mk_hwthreadregisters_t mk_threadregisters_t;

/* Thread priority
 *
 * mk_threadprio_t - The type representing thread priorities.
 *
 * MK_THREADPRIO_MAX_VALUE - The maximum priority which can certainly be represented by mk_threadprio_t.
*/
typedef mk_int_t mk_threadprio_t;
#define MK_THREADPRIO_MAX_VALUE	((mk_threadprio_t)0x7fff)

typedef void (*mk_threadfunc_t)(void);

/* Thread states. Note: there is no WAITING state. WAITING is a task state,
 * and while a task is WAITING it does not occupy its thread.
*/
/* !LINKSTO Microkernel.CompilerLimitation.ShortEnum, 1
 * !doctype src
*/
enum mk_threadstate_e
{	MK_THS_IDLE = 0,
	MK_THS_READY = 1,
	MK_THS_RUNNING = 2,
	MK_THS_NEW = 3				/* Used for new threads to avoid reporting them as current */
};

typedef enum mk_threadstate_e mk_threadstate_t;

/* mk_thread_s - the thread structure
 *
 * See hardware-specific definition of mk_hwthreadregisters_t for
 * - interrupt level
 * - entry point
 * - parameters
*/
struct mk_thread_s
{
	mk_threadregisters_t *regs;			/* Pointer to the register context */
	const mk_char_t *name;				/* Name of thread (makes debugging easier) */
	mk_thread_t *next;					/* Next thread in queue */
	mk_thread_t *parentThread;			/* Parent thread on the same core */
	mk_parametertype_t parentCookie;	/* Cookie to identify the parent thread on another core */
#if MK_MAXCORES > 1
	mk_statusandvalue_t xcoreReply;		/* Location for inter-core reply payload. */
#endif
	mk_accounting_t accounting;			/* Thread accounting structure */
	mk_threadstate_t state;				/* State of thread (idle, ready, running) */
	mk_threadprio_t queueingPriority;	/* Initial priority of thread */
	mk_threadprio_t runningPriority;	/* Lowest priority of thread when in running state */
	mk_threadprio_t currentPriority;	/* Current thread priority */
	mk_lock_t *lastLockTaken;			/* Most recently taken lock */
	mk_jobqueue_t *jobQueue;			/* Job queue (could be NULL) */
	mk_eventstatus_t *eventStatus;		/* Event status for extended tasks that called WaitGetClearEvent */
	mk_objectid_t memoryPartition;		/* Index of memory partition */
	mk_objectid_t currentObject;		/* Id of thread's current job */
	mk_objecttype_t objectType;			/* Type of object this thread runs */
	mk_objectid_t applicationId;		/* Id of the thread's OS-Application */
	mk_objectid_t parentCore;			/* Parent core (for counter subsystem threads) */
};


/* mk_threadcfg_s - the thread configuration structure
*/
struct mk_threadcfg_s
{
	mk_threadregisters_t *regs;			/* Pointer to the register context */
	const mk_char_t *name;				/* Name of thread (makes debugging easier) */
	mk_objectid_t coreIndex;			/* Core on which the thread runs. */
	mk_stackelement_t *initialSp;		/* Initial stack pointer */
	mk_threadfunc_t entry;				/* Thread entry function */
	mk_accountingcfg_t acctCfg;			/* Configuration for accounting (exec budget etc.) */
	mk_hwps_t ps;						/* Initial processor status (processor mode, interrupt status, level etc.) */
	mk_hwlocklevel_t lockLevel;			/* The interrupt lock level */
	mk_threadprio_t queuePrio;			/* Initial queueing priority */
	mk_threadprio_t runningPriority;	/* Initial run priority */
	mk_objectid_t memoryPartition;		/* Index of memory partition */
	mk_objectid_t currentObject;		/* Id of this thread */
	mk_objecttype_t objectType;			/* Type of object this thread represents */
	mk_objectid_t applicationId;		/* Id of the thread's OS-Application */
};

/* MK_THREADCFG() - initialization macro for a thread config structure
 *
 * This macro should be used wherever a threadcfg is initialized, to permit changes
 * in the structure to be easily identified and fixed, and to permit
 * optimizations of the structure if necessary.
 *
 * The entry function is cast to a void (*)(void) function pointer; the entry function can theoretically be
 * anything as long as the thread creation places parameters in the right place.
 */
#define MK_THREADCFG(reg, name, cor, sp, ent, pm, ilvl, ie, fpu, hws, qpri, rpri,		\
					 partIdx, objid, objtyp, exBgt, lkBgt, aid)							\
{																						\
	(reg),																				\
	(name),																				\
	(cor),																				\
	(sp),																				\
	(mk_threadfunc_t)(ent),																\
	{ (exBgt) },																		\
	MK_HWPS_INIT((pm), (ilvl), (ie), (fpu), (hws)),										\
	(ilvl),																				\
	(qpri),																				\
	(rpri),																				\
	(partIdx),																			\
	(objid),																			\
	(objtyp),																			\
	(aid)																				\
}

#endif

/* Offsets of items in thread data structure, for assembly-language code
 * We shouldn't need many of these...
*/
#define MK_THR_REGS		0

#ifndef MK_ASM

/* Global thread configuration.
 *
 * What runs in these threads?
 *
 *	idleThread				- Idle, shutdown-idle
 *	aux1Thread				- Counter subsystem (including StartOS and TerminateApplication),
 *							  boot(dummy for MK_StartKernel)
 *	aux2Thread				- Trusted functions, init("main"), startup hook, shutdown hook
 *	protectionHookThread	- protection hook
 *	errorHookThread			- error hook
 *
 *	The configuration populates these arrays with the appropriate thread structures.
 *  IMPORTANT: the trusted function thread configuration is not const because the permissions
 *  for trusted functions differ from each other.
*/
extern mk_thread_t * const MK_idleThread[MK_MAXCORES];
extern mk_thread_t * const MK_aux1Thread[MK_MAXCORES];
extern mk_thread_t * const MK_aux2Thread[MK_MAXCORES];
extern mk_thread_t * const MK_protectionHookThread[MK_MAXCORES];
extern mk_thread_t * const MK_errorHookThread[MK_MAXCORES];

extern const mk_threadcfg_t * const MK_bootThreadConfig[MK_MAXCORES];
extern const mk_threadcfg_t * const MK_idleThreadConfig[MK_MAXCORES];
extern const mk_threadcfg_t * const MK_initThreadConfig[MK_MAXCORES];
extern const mk_threadcfg_t * const MK_errorHookThreadConfig[MK_MAXCORES];
extern const mk_threadcfg_t * const MK_protectionHookThreadConfig[MK_MAXCORES];
extern mk_threadcfg_t * const MK_ctrsubThreadConfig[MK_MAXCORES];
extern mk_threadcfg_t * const MK_trustedFunctionThreadConfig[MK_MAXCORES];

/* Function prototypes for thread and thread-queue handling
*/
void MK_Idle(void);
void MK_EnqueueThread(mk_thread_t **, mk_thread_t *);
void MK_RequeueThread(mk_thread_t **, mk_thread_t *);
void MK_DequeueThread(mk_thread_t **, mk_thread_t *);
void MK_IncreasePriority(mk_thread_t **, mk_thread_t *, mk_threadprio_t, mk_hwlocklevel_t);
void MK_TerminateThread(mk_kernelcontrol_t *, mk_thread_t *, mk_hwlocklevel_t);
void MK_ClearThread(mk_thread_t *);
void MK_SetupThread(mk_thread_t *, const mk_threadcfg_t *);
void MK_StartThread(mk_thread_t **, mk_thread_t *, const mk_threadcfg_t *);
void MK_FillThreadRegisters(mk_threadregisters_t *, const mk_threadcfg_t *);
mk_thread_t *MK_FindFirstThread(mk_thread_t *, mk_objecttype_t, mk_threadstate_t);
void MK_ThreadQueueEmpty(void);

void MK_StartChildThread(mk_thread_t **, mk_thread_t *, const mk_threadcfg_t *,
							mk_thread_t *, mk_parametertype_t, mk_objectid_t);


#endif

/* Value of parentCore, if there is no parent core.
*/
#define MK_NULLPARENTCORE	(-1)

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
