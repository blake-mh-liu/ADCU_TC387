/* Mk_c3_configuration.c
 *
 * This file contains the configuration items for core 3 (threads, thread configurations etc.).
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.1 (required)
 *  Conversions shall not be performed between a pointer to a function
 *  and any other type.
 *
 * Reason:
 *  The functions "main", "ProtectionHook" and "ErrorHook" are converted to
 *  mk_threadfunc_t. The microkernel itself cares about the initialization of
 *  the thread context before calling the respective functions, so the behavior
 *  is specified and predictable.
 *
 * MISRAC2012-2) Deviated Rule: 20.7 (required)
 *  Expressions resulting from the expansion of macro parameters shall be
 *  enclosed in parentheses.
 *
 * Reason:
 *  The lack of parentheses is intentional, because they would lead to syntax
 *  errors in the constructed initializer.
*/

#include <Mk_kconfig.h>

#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <public/Mk_error.h>
#include <private/Mk_core.h>
#include <private/Mk_startup.h>
#include <private/Mk_thread.h>
#include <private/Mk_task.h>
#include <private/Mk_lock.h>
#include <private/Mk_interrupt.h>
#include <private/Mk_memoryprotection.h>
#include <private/Mk_errorhandling.h>
#include <private/Mk_exceptionhandling.h>
#include <private/Mk_ctrsub.h>
#include <private/Mk_trustedfunction.h>
#include <private/Mk_message.h>
#include <private/Mk_application.h>
#include MK_HWSEL_PUB_CHARACTERISTICS
#include <public/Mk_callout.h>
#include <Mk_board.h>
#include <Mk_Cfg.h>

/*
 * !LINKSTO Microkernel.Data.CoreSeparation, 1
 * !doctype src
*/

/* This macro defines the core number for use in several places.
 * This is a local macro, so there's no MK_ prefix.
*/
#define MYCORE	3

#if (MK_COREMAPWORD_C3 & MK_COREMAPBIT_C3) == 0

/* This constant ensures that this file is a valid C compilation unit.
 * It also serves to identify which cores are not used in the compiled system.
 * Hint: nm foo.elf | grep NOT_USED
*/
const mk_uint8_t MK_c3_NOT_USED = 0xebu;

/* All the core-to-core queue pairs for this unused core are defined as NULL,NULL
*/
#define MK_C0_QUEUE		{ MK_NULL, MK_NULL }
#define MK_C1_QUEUE		{ MK_NULL, MK_NULL }
#define MK_C2_QUEUE		{ MK_NULL, MK_NULL }
#define MK_C3_QUEUE		{ MK_NULL, MK_NULL }
#define MK_C4_QUEUE		{ MK_NULL, MK_NULL }
#define MK_C5_QUEUE		{ MK_NULL, MK_NULL }
#define MK_C6_QUEUE		{ MK_NULL, MK_NULL }
#define MK_C7_QUEUE		{ MK_NULL, MK_NULL }

#else

/* Core variables
*/
mk_kernelcontrol_t MK_c3_coreVars;									/* = {0} */

/* Synchronization variable.
*/
volatile mk_syncspot_t MK_c3_syncSpot;								/* = 0 */

/* Thread structures and register stores for the threads.
*/
mk_thread_t MK_c3_idleThread;										/* = {0} */
mk_thread_t MK_c3_aux1Thread;										/* = {0} */
mk_thread_t MK_c3_aux2Thread;										/* = {0} */

static mk_threadregisters_t MK_c3_idleRegisters;					/* = {0} */
static mk_threadregisters_t MK_c3_aux1Registers;					/* = {0} */
static mk_threadregisters_t MK_c3_aux2Registers;					/* = {0} */

#if MK_CFG_C3_HAS_ERRORHOOK
mk_thread_t MK_c3_errorHookThread;									/* = {0} */
static mk_threadregisters_t MK_c3_errorHookRegisters;				/* = {0} */
#endif

#if MK_CFG_C3_HAS_PROTECTIONHOOK
mk_thread_t MK_c3_protectionHookThread;								/* = {0} */
static mk_threadregisters_t MK_c3_protectionHookRegisters;			/* = {0} */
#endif

#if MK_CFG_C3_NTASKS > 0
mk_task_t MK_c3_taskDynamic[MK_CFG_C3_NTASKS];						/* = {0} */
#endif

#if MK_CFG_C3_NTASKTHREADS > 0
mk_thread_t MK_c3_taskThreads[MK_CFG_C3_NTASKTHREADS];				/* = {0} */
#endif

#if MK_CFG_C3_NTASKREGISTERS > 0
mk_threadregisters_t MK_c3_taskRegisters[MK_CFG_C3_NTASKREGISTERS];	/* = {0} */
#endif

#if MK_CFG_C3_NETASKS > 0
mk_eventstatus_t MK_c3_eventStatus[MK_CFG_C3_NETASKS];				/* = {0} */
#endif

#if MK_CFG_C3_NISRS > 0
mk_isr_t MK_c3_isrDynamic[MK_CFG_C3_NISRS];							/* = {0} */
#endif

#if MK_CFG_C3_NISRTHREADS > 0
mk_thread_t MK_c3_isrThreads[MK_CFG_C3_NISRTHREADS];				/* = {0} */
#endif

#if MK_CFG_C3_NISRREGISTERS > 0
mk_threadregisters_t MK_c3_isrRegisters[MK_CFG_C3_NISRREGISTERS];	/* = {0} */
#endif

#if MK_CFG_C3_NLOCKS > 0
mk_lock_t MK_c3_lockTable[MK_CFG_C3_NLOCKS];						/* = {0} */
#endif

#if MK_CFG_C3_NAPPLICATIONS > 0
mk_app_t MK_c3_appDynamic[MK_CFG_C3_NAPPLICATIONS];					/* = {0} */
#endif

/* Error information structures.
*/
mk_errorinfo_t MK_c3_errorInfo =
{
	MK_sid_UnknownService,
	MK_eid_NoError,
	MK_E_OK,
	0,
	MK_OBJTYPE_UNKNOWN,
	MK_NULL,
	MK_NULL,
	MK_ERRORINFO_PARAMETER_INIT
};

mk_protectioninfo_t MK_c3_protectionInfo =
{
	MK_sid_UnknownService,
	MK_eid_NoError,
	MK_E_OK,
	MK_NULL,
	MK_APPL_NONE
};

mk_hwexceptioninfo_t MK_c3_exceptionInfo;		/* = {0} */
mk_hwexceptioninfo_t MK_c3_panicExceptionInfo;	/* = {0} */

/* Thread configurations
 *
 * These are for the core-specific threads only. The task and ISR configurations are held globally.
*/

/* Configuration for the dummy boot thread
 *
 * This is the configuration for the dummy thread that is assumed to be already running when
 * the kernel starts.
 * Many of the fields are irrelevant because this thread never actually starts as a thread.
 * The important fields are:
 *	- the register store; because the system call that terminates it will save the registers there.
 *	- the priorities; they must be high enough to ensure that the thread stays at the head of the queue
 *
 * The fields are not configurable.
*/
const mk_threadcfg_t MK_c3_bootThreadConfig =
	MK_THREADCFG(	&MK_c3_aux1Registers,
					"c3-boot",
					MYCORE,
					&MK_c3_aux1Stack[MK_CFG_C3_AUX1_STACK_NELEMENTS],
					MK_NULL,
					MK_THRMODE_SUPER,
					MK_HWDISABLEALLLEVEL,
					MK_THRIRQ_DISABLE,
					MK_THRFPU_DISABLE,
					MK_THRHWS_DEFAULT,
					(MK_CFG_C3_INIT_QPRIO+1),	/* Queueing priority; higher than that of the init (main) thread. */
					(MK_CFG_C3_INIT_RPRIO+1),	/* Running priority; higher than that of the init (main) thread. */
					-1,
					MK_OBJID_BOOT,
					MK_OBJTYPE_KERNEL,
					MK_EXECBUDGET_INFINITE,
					MK_NULL,
					MK_APPL_NONE
				);


/* Configuration for the init thread
 *
 * !description    This is the configuration for the thread that is automatically
 * !               started to bring up the system. Typically, it runs main()
 * !               and uses MK_INITFUNCTION, MK_INITPSW and MK_INITLEVEL that must be
 * !               provided by the configuration.
 * !doctype        src
*/
/* Deviation MISRAC2012-1 <+4> */
const mk_threadcfg_t MK_c3_initThreadConfig =
	MK_THREADCFG(	&MK_c3_aux2Registers,
					"c3-main",
					MYCORE,
					&MK_c3_aux2Stack[MK_CFG_C3_AUX2_STACK_NELEMENTS],
					MK_CFG_C3_INIT_FUNCTION,
					MK_CFG_C3_INIT_MODE,
					MK_CFG_C3_INIT_LEVEL,
					MK_CFG_C3_INIT_IRQEN,
					MK_CFG_C3_INIT_FPUEN,
					MK_CFG_C3_INIT_HWS,
					MK_CFG_C3_INIT_QPRIO,
					MK_CFG_C3_INIT_RPRIO,
					MK_CFG_C3_INIT_MEMPART,
					MK_OBJID_MAIN,
					MK_OBJTYPE_KERNEL,
					MK_EXECBUDGET_INFINITE,
					MK_NULL,
					MK_APPL_NONE
				);

/* Configuration for the idle thread
*/
const mk_threadcfg_t MK_c3_idleThreadConfig =
	MK_THREADCFG(	&MK_c3_idleRegisters,
					"c3-idle",
					MYCORE,
					&MK_c3_idleshutdownStack[MK_CFG_C3_IDLESHUTDOWN_STACK_NELEMENTS],
					MK_CFG_C3_IDLE_FUNCTION,
					MK_CFG_C3_IDLE_MODE,
					MK_CFG_C3_IDLE_LEVEL,
					MK_CFG_C3_IDLE_IRQEN,
					MK_CFG_C3_IDLE_FPUEN,
					MK_CFG_C3_IDLE_HWS,
					0,	/* Queueing priority */
					0,	/* Running priority  */
					MK_CFG_C3_IDLE_MEMPART,
					MK_OBJID_IDLE,
					MK_OBJTYPE_KERNEL,
					MK_EXECBUDGET_INFINITE,
					MK_NULL,
					MK_APPL_NONE
				);

/* Configuration for the shutdown thread
*/
const mk_threadcfg_t MK_c3_shutdownThreadConfig =
	MK_THREADCFG(	&MK_c3_idleRegisters,
					"c3-shutdown",
					MYCORE,
					&MK_c3_idleshutdownStack[MK_CFG_C3_IDLESHUTDOWN_STACK_NELEMENTS],
					MK_CFG_C3_SHUTDOWN_FUNCTION,
					MK_CFG_C3_SHUTDOWN_MODE,
					MK_CFG_C3_SHUTDOWN_LEVEL,
					MK_CFG_C3_SHUTDOWN_IRQEN,
					MK_CFG_C3_SHUTDOWN_FPUEN,
					MK_CFG_C3_SHUTDOWN_HWS,
					0,	/* Queueing priority */
					0,	/* Running priority */
					MK_CFG_C3_SHUTDOWN_MEMPART,
					MK_OBJID_SHUTDOWN,
					MK_OBJTYPE_KERNEL,
					MK_EXECBUDGET_INFINITE,
					MK_NULL,
					MK_APPL_NONE
				);

/* Configuration for counter subsystem threads.
 *
 * This structure is in RAM because the microkernel writes various members such as entry function,
 * memory partition etc. at runtime.
*/
#if MK_CFG_C3_HAS_CTRSUB
mk_threadcfg_t MK_c3_ctrsubThreadConfig =
	MK_THREADCFG(	&MK_c3_aux1Registers,
					"c3-ctrsub",
					MYCORE,
					&MK_c3_aux1Stack[MK_CFG_C3_AUX1_STACK_NELEMENTS],
					MK_NULL,				/* Will be added at runtime */
					MK_CFG_C3_CTRSUB_MODE,
					MK_CFG_C3_CTRSUB_LEVEL,
					MK_CFG_C3_CTRSUB_IRQEN,
					MK_CFG_C3_CTRSUB_FPUEN,
					MK_CFG_C3_CTRSUB_HWS,
					MK_CFG_C3_CTRSUB_QPRIO,	/* Minimum queueing priority */
					MK_CFG_C3_CTRSUB_RPRIO,	/* Minimum running priority */
					MK_CFG_C3_CTRSUB_MEMPART,
					0,						/* Will be added at runtime */
					MK_OBJTYPE_CTRSUB,
					MK_EXECBUDGET_INFINITE,
					MK_NULL,
					MK_APPL_NONE
				);
#endif

/* Configuration for trusted function threads.
 *
 * This structure is in RAM because the microkernel writes various members such as entry function,
 * memory partition etc. at runtime.
*/
#if MK_CFG_C3_HAS_TRUSTEDFUNCTION
mk_threadcfg_t MK_c3_trustedFunctionThreadConfig =
	MK_THREADCFG(	&MK_c3_aux2Registers,
					"c3-trustedfunction",
					MYCORE,
					&MK_c3_aux2Stack[MK_CFG_C3_AUX2_STACK_NELEMENTS],
					MK_NULL,				/* Will be added at runtime */
					MK_CFG_C3_TF_MODE,
					MK_CFG_C3_TF_LEVEL,
					MK_CFG_C3_TF_IRQEN,
					MK_CFG_C3_TF_FPUEN,
					MK_CFG_C3_TF_HWS,
					MK_CFG_C3_TF_QPRIO,		/* Minimum queueing priority */
					MK_CFG_C3_TF_RPRIO,		/* Minimum running priority */
					-1,						/* Partition can be modified at runtime */
					0,						/* Will be added at runtime */
					MK_OBJTYPE_TRUSTEDFUNCTION,
					MK_EXECBUDGET_INFINITE,
					MK_NULL,
					MK_APPL_NONE
				);
#endif

/* Configuration for error hook thread.
*/
#if MK_CFG_C3_HAS_ERRORHOOK
/* Deviation MISRAC2012-1 <+4> */
const mk_threadcfg_t MK_c3_errorHookThreadConfig =
	MK_THREADCFG(	&MK_c3_errorHookRegisters,
					"c3-error-hook",
					MYCORE,
					&MK_c3_errorhookStack[MK_CFG_C3_ERRORHOOK_STACK_NELEMENTS],
					MK_CFG_C3_ERRORHOOK_FUNCTION,
					MK_CFG_C3_ERRORHOOK_MODE,
					MK_CFG_C3_ERRORHOOK_LEVEL,
					MK_CFG_C3_ERRORHOOK_IRQEN,
					MK_CFG_C3_ERRORHOOK_FPUEN,
					MK_CFG_C3_ERRORHOOK_HWS,
					MK_CFG_C3_ERRORHOOK_QPRIO,
					MK_CFG_C3_ERRORHOOK_RPRIO,
					MK_CFG_C3_ERRORHOOK_MEMPART,
					MK_OBJID_GLOBAL,
					MK_OBJTYPE_ERRORHOOK,
					MK_EXECBUDGET_INFINITE,
					MK_NULL,
					MK_APPL_NONE
				);
#endif

/* Configuration for protection hook thread
*/
/* Deviation MISRAC2012-1 <+5> */
#if MK_CFG_C3_HAS_PROTECTIONHOOK
const mk_threadcfg_t MK_c3_protectionHookThreadConfig =
	MK_THREADCFG(	&MK_c3_protectionHookRegisters,
					"c3-protection-hook",
					MYCORE,
					&MK_c3_protectionHookStack[MK_CFG_C3_PROTECTIONHOOK_STACK_NELEMENTS],
					MK_CFG_C3_PROTECTIONHOOK_FUNCTION,
					MK_CFG_C3_PROTECTIONHOOK_MODE,
					MK_CFG_C3_PROTECTIONHOOK_LEVEL,
					MK_CFG_C3_PROTECTIONHOOK_IRQEN,
					MK_CFG_C3_PROTECTIONHOOK_FPUEN,
					MK_CFG_C3_PROTECTIONHOOK_HWS,
					MK_CFG_C3_PROTECTIONHOOK_QPRIO,
					MK_CFG_C3_PROTECTIONHOOK_RPRIO,
					MK_CFG_C3_PROTECTIONHOOK_MEMPART,
					MK_OBJID_GLOBAL,
					MK_OBJTYPE_PROTECTIONHOOK,
					MK_EXECBUDGET_INFINITE,
					MK_NULL,
					MK_APPL_NONE
				);
#endif


/* Configuration for the shutdown hook thread
*/
#if MK_CFG_C3_HAS_SHUTDOWNHOOK
const mk_threadcfg_t MK_c3_shutdownHookThreadConfig =
	MK_THREADCFG(	&MK_c3_aux2Registers,
					"c3-shutdown-hook",
					MYCORE,
					&MK_c3_aux2Stack[MK_CFG_C3_AUX2_STACK_NELEMENTS],
					MK_CFG_C3_SHUTDOWNHOOK_FUNCTION,
					MK_CFG_C3_SHUTDOWNHOOK_MODE,
					MK_CFG_C3_SHUTDOWNHOOK_LEVEL,
					MK_CFG_C3_SHUTDOWNHOOK_IRQEN,
					MK_CFG_C3_SHUTDOWNHOOK_FPUEN,
					MK_CFG_C3_SHUTDOWNHOOK_HWS,
					MK_CFG_C3_SHUTDOWNHOOK_QPRIO,
					MK_CFG_C3_SHUTDOWNHOOK_RPRIO,
					MK_CFG_C3_SHUTDOWNHOOK_MEMPART,
					MK_OBJID_GLOBAL,
					MK_OBJTYPE_SHUTDOWNHOOK,
					MK_EXECBUDGET_INFINITE,
					MK_NULL,
					MK_APPL_NONE
				);
#endif

/* Job queues
 *
*/
#if MK_CFG_C3_NJOBQUEUES > 0

mk_jobqueue_t MK_c3_jobQueue[MK_CFG_C3_NJOBQUEUES];

const mk_jobqueuecfg_t MK_c3_jobQueueCfg[MK_CFG_C3_NJOBQUEUES] = { MK_CFG_C3_JOBQUEUECONFIG };

mk_jobelement_t MK_c3_jobQueueBuffer[MK_CFG_C3_JOBQUEUEBUFLEN];

#endif

/* Message queues.
 * For each configured core (other than myself) define:
 *	- the message buffer for the outgoing queue
 *	- the insert pointer for the outgoing queue
 *	- the remove pointer for the incoming queue
 *	- the (constant) structure containing definitions for the outgoing queue
 *	- the initializer macro for the queue pair in the (constant) queues array
*/
#if (MYCORE == 0) || ((MK_COREMAPWORD_C0 & MK_COREMAPBIT_C0) == 0)

#define MK_C0_QUEUE		{ MK_NULL, MK_NULL }

#else

mk_message_t MK_c3_c0_messageBuffer[MK_CFG_MAXMSG+1];
mk_msgptrfield_t MK_c3_c0_insertPtr;
mk_msgptrfield_t MK_c0_c3_removePtr;

const mk_msgqueuedescriptor_t MK_c3_c0_queue =
{	&MK_c3_c0_messageBuffer[0],
	&MK_c3_c0_messageBuffer[MK_CFG_MAXMSG],
	&MK_c3_c0_insertPtr,
	&MK_c3_c0_removePtr
};

#define MK_C0_QUEUE		{ &MK_c3_c0_queue, &MK_c0_c3_queue }

#endif

#if (MYCORE == 1) || ((MK_COREMAPWORD_C1 & MK_COREMAPBIT_C1) == 0)

#define MK_C1_QUEUE		{ MK_NULL, MK_NULL }

#else

mk_message_t MK_c3_c1_messageBuffer[MK_CFG_MAXMSG+1];
mk_msgptrfield_t MK_c3_c1_insertPtr;
mk_msgptrfield_t MK_c1_c3_removePtr;

const mk_msgqueuedescriptor_t MK_c3_c1_queue =
{	&MK_c3_c1_messageBuffer[0],
	&MK_c3_c1_messageBuffer[MK_CFG_MAXMSG],
	&MK_c3_c1_insertPtr,
	&MK_c3_c1_removePtr
};

#define MK_C1_QUEUE		{ &MK_c3_c1_queue, &MK_c1_c3_queue }

#endif

#if (MYCORE == 2) || ((MK_COREMAPWORD_C2 & MK_COREMAPBIT_C2) == 0)

#define MK_C2_QUEUE		{ MK_NULL, MK_NULL }

#else

mk_message_t MK_c3_c2_messageBuffer[MK_CFG_MAXMSG+1];
mk_msgptrfield_t MK_c3_c2_insertPtr;
mk_msgptrfield_t MK_c2_c3_removePtr;

const mk_msgqueuedescriptor_t MK_c3_c2_queue =
{	&MK_c3_c2_messageBuffer[0],
	&MK_c3_c2_messageBuffer[MK_CFG_MAXMSG],
	&MK_c3_c2_insertPtr,
	&MK_c3_c2_removePtr
};

#define MK_C2_QUEUE		{ &MK_c3_c2_queue, &MK_c2_c3_queue }

#endif

#if (MYCORE == 3) || ((MK_COREMAPWORD_C3 & MK_COREMAPBIT_C3) == 0)

#define MK_C3_QUEUE		{ MK_NULL, MK_NULL }

#else

mk_message_t MK_c3_c3_messageBuffer[MK_CFG_MAXMSG+1];
mk_msgptrfield_t MK_c3_c3_insertPtr;
mk_msgptrfield_t MK_c3_c3_removePtr;

const mk_msgqueuedescriptor_t MK_c3_c3_queue =
{	&MK_c3_c3_messageBuffer[0],
	&MK_c3_c3_messageBuffer[MK_CFG_MAXMSG],
	&MK_c3_c3_insertPtr,
	&MK_c3_c3_removePtr
};

#define MK_C3_QUEUE		{ &MK_c3_c3_queue, &MK_c3_c3_queue }

#endif

#if (MYCORE == 4) || ((MK_COREMAPWORD_C4 & MK_COREMAPBIT_C4) == 0)

#define MK_C4_QUEUE		{ MK_NULL, MK_NULL }

#else

mk_message_t MK_c3_c4_messageBuffer[MK_CFG_MAXMSG+1];
mk_msgptrfield_t MK_c3_c4_insertPtr;
mk_msgptrfield_t MK_c4_c3_removePtr;

const mk_msgqueuedescriptor_t MK_c3_c4_queue =
{	&MK_c3_c4_messageBuffer[0],
	&MK_c3_c4_messageBuffer[MK_CFG_MAXMSG],
	&MK_c3_c4_insertPtr,
	&MK_c3_c4_removePtr
};

#define MK_C4_QUEUE		{ &MK_c3_c4_queue, &MK_c4_c3_queue }

#endif

#if (MYCORE == 5) || ((MK_COREMAPWORD_C5 & MK_COREMAPBIT_C5) == 0)

#define MK_C5_QUEUE		{ MK_NULL, MK_NULL }

#else

mk_message_t MK_c3_c5_messageBuffer[MK_CFG_MAXMSG+1];
mk_msgptrfield_t MK_c3_c5_insertPtr;
mk_msgptrfield_t MK_c5_c3_removePtr;

const mk_msgqueuedescriptor_t MK_c3_c5_queue =
{	&MK_c3_c5_messageBuffer[0],
	&MK_c3_c5_messageBuffer[MK_CFG_MAXMSG],
	&MK_c3_c5_insertPtr,
	&MK_c3_c5_removePtr
};

#define MK_C5_QUEUE		{ &MK_c3_c5_queue, &MK_c5_c3_queue }

#endif

#if (MYCORE == 6) || ((MK_COREMAPWORD_C6 & MK_COREMAPBIT_C6) == 0)

#define MK_C6_QUEUE		{ MK_NULL, MK_NULL }

#else

mk_message_t MK_c3_c6_messageBuffer[MK_CFG_MAXMSG+1];
mk_msgptrfield_t MK_c3_c6_insertPtr;
mk_msgptrfield_t MK_c6_c3_removePtr;

const mk_msgqueuedescriptor_t MK_c3_c6_queue =
{	&MK_c3_c6_messageBuffer[0],
	&MK_c3_c6_messageBuffer[MK_CFG_MAXMSG],
	&MK_c3_c6_insertPtr,
	&MK_c3_c6_removePtr
};

#define MK_C6_QUEUE		{ &MK_c3_c6_queue, &MK_c6_c3_queue }

#endif

#if (MYCORE == 7) || ((MK_COREMAPWORD_C7 & MK_COREMAPBIT_C7) == 0)

#define MK_C7_QUEUE		{ MK_NULL, MK_NULL }

#else

mk_message_t MK_c3_c7_messageBuffer[MK_CFG_MAXMSG+1];
mk_msgptrfield_t MK_c3_c7_insertPtr;
mk_msgptrfield_t MK_c7_c3_removePtr;

const mk_msgqueuedescriptor_t MK_c3_c7_queue =
{	&MK_c3_c7_messageBuffer[0],
	&MK_c3_c7_messageBuffer[MK_CFG_MAXMSG],
	&MK_c3_c7_insertPtr,
	&MK_c3_c7_removePtr
};

#define MK_C7_QUEUE		{ &MK_c3_c7_queue, &MK_c7_c3_queue }

#endif


#if (MK_MAXCORES > 1)
/* The init test variables for this core.
*/
mk_uint32_t MK_c3_initTestData = MK_INITTEST_VALUE + (mk_uint32_t)MYCORE;
mk_uint32_t MK_c3_initTestBss;
#endif

#endif

/* The array of queue pairs needs to be present even for cores that are not in use.
 * For cores that aren't in use, all entries are NULL,NULL.
*/
const mk_msgqueuepair_t MK_c3_queues[MK_MAXCORES] =
{
	/* Deviation MISRAC2012-2 */
	MK_COREARRAY(
	    MK_C0_QUEUE,
	    MK_C1_QUEUE,
	    MK_C2_QUEUE,
	    MK_C3_QUEUE,
	    MK_C4_QUEUE,
	    MK_C5_QUEUE,
	    MK_C6_QUEUE,
	    MK_C7_QUEUE)
};

#if MK_HASHEAP

#if (MK_COREMAPWORD_C3 & MK_COREMAPBIT_C3) != 0
/* Heap memory for building MMU page tables.
 * For each configured core define:
 *	- static type 0 heap for the flat memory region map
 *	- static type 1 heap for the actual page tables
 *	- a global heap structure to access type 0 and 1 heaps
*/
static mk_heaptype0_t MK_c3_heap0[MK_BOARD_C3_HEAPTYPE0_COUNT];
static mk_heaptype1_t MK_c3_heap1[MK_BOARD_C3_HEAPTYPE1_COUNT];

mk_heap_t MK_c3_heap =
{
	&MK_c3_heap0[0],
	MK_BOARD_C3_HEAPTYPE0_COUNT,
	&MK_c3_heap1[0],
	MK_BOARD_C3_HEAPTYPE1_COUNT
};

#endif

#endif

#if (MK_MEM_PROT == MK_MEM_PROT_MMU)

#if (MK_COREMAPWORD_C3 & MK_COREMAPBIT_C3) != 0
/* Memory partition ID (= array index) to page table mapping array.
 * Only necessary for configured cores.
*/
mk_pagetabledescriptor_t MK_c3_partitionToPageTable[MK_CFG_C3_NMEMORYPARTITIONS];
#endif

#endif

#if MK_USE_ORTI_TRACE
volatile mk_uint32_t MK_c3_ortiRunningThread;
#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
