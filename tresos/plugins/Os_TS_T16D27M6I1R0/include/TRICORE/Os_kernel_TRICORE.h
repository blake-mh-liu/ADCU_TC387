/* Os_kernel_TRICORE.h
 *
 * This file is the architecture-dependent include file for TRICORE
 *
 * See also: Os_defs.h
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 8.6 (required)
 * An identifier with external linkage shall have exactly one external
 * definition.
 *
 * Reason:
 * These symbols are defined in assembly language files and hence are invisible
 * to the MISRA-C analysis process. They are defined exactly once, though.
 *
 *
 * MISRAC2012-2) Deviated Rule: 11.1 (required)
 * Conversions shall not be performed between a pointer to a function and
 * any type other type.
 *
 * Reason:
 * Depending on the architecture, the prototype of common assembly code for
 * setting up a hook's environment might use another function pointer type
 * than the one assumed by the common OS_CallAppHook() function.
 *
 *
 * MISRAC2012-3) Deviated Rule: 2.2 (required)
 * There shall be no dead code.
 *
 * Reason:
 * This code is required by the hardware protocol.
 */

#ifndef OS_KERNEL_TRICORE_H
#define OS_KERNEL_TRICORE_H

#include <TRICORE/Os_TRICORE_cpu.h>
#include <TRICORE/Os_TRICORE_core.h>
#include <TRICORE/Os_tool_TRICORE.h>

/* Check that value for memory proctection granularity as power of 2 is defined.
 * (Amount of lower bits not present in the protection registers).
 */
#ifndef OS_DPRX_GRANULARITY_BITS
#define OS_DPRX_GRANULARITY_BITS 0u
#endif

/* Architecture characteristics
*/
#define OS_STACKGROWS	OS_STACKGROWSDOWN
#define OS_STACKFILL	OS_U(0xebebebeb)
#define OS_HASMEMPROT	1
#define OS_HWT_POWEROF2	1

/*!
 * os_timervalue_t
 *
 * Defines a data type large enough to hold the value of a hardware timer.
*/
#ifndef OS_ASM
typedef os_uint32_t os_timervalue_t;
#endif

#define OS_MAXTIMERVALUE	OS_U(0xffffffff)

/*!
 * OS_ArchTakeSpinlock
 * OS_ArchDropSpinlock
 *
 * Tricore has a swap operation, which is used to implement spinlocks.
 */

#define OS_HAS_ARCHSPINLOCK		1
#define OS_ArchTakeSpinlock(a)	OS_TricoreTakeSpinlock(a)
#define OS_ArchDropSpinlock(a)	do { *(a) = 0; } while (0)


/*
 * Cache control:
 *
 * Aurix: Caches are disabled for all memory regions, which could contain shared mutable variables (see SM_AURIX_16).
 *        CacheInvalidate and CacheFlush aren't required.
 *        Since caches are disabled on mutable data, cores can't steal cache lines from each other,
 *        so there is no need to consider the length of a cache line.
*/
#define OS_CACHE_MODE		OS_CACHE_MODE_NONE
#define OS_CACHE_LINE_LEN	0

/* The rest of the file is not needed for a microkernel build.
*/
#if OS_KERNEL_TYPE!=OS_MICROKERNEL

/*!
 * The constant OS_intDisableLevel contains the level for disabling
 * OS (category 2) interrupts.
 * The constant OS_intDisableLevelAll contains the level for disabling
 * all (category 1 and 2) interrupts.
 * The constant OS_kernDisableLevel contains the level for disabling
 * OS (category 2) interrupts AND the timing protection interrupt(s), if any.
 * The above constants also disable cross-core interrupts.
 * The constant OS_kernOnlyXcoreLevel contains the level for disabling
 * all interrupts except for cross-core notifications.
 * The constant OS_intDisableLevelMax is the maximum of all levels and hence
 * safely disables all interrupts.
*/
#ifndef OS_ASM
extern const os_intstatus_t OS_intDisableLevel;
extern const os_intstatus_t OS_intDisableLevelAll;
extern const os_intstatus_t OS_kernDisableLevel;
extern const os_intstatus_t OS_kernOnlyXcoreLevel;
extern const os_intstatus_t OS_intDisableLevelMax;
#endif

/*!
 * os_archcontext_t
 *
 * This is the data type for the architecture-dependent task context
 * for TRICORE.
*/
#ifndef OS_ASM
typedef struct os_archcontext_s os_archcontext_t;

struct os_archcontext_s
{
	os_uint32_t		pcxiCurrent;	/* Pcxi for reeady/waiting task */
};
#endif
#define OS_SIZEOF_CTXT	OS_U(4)

#define OS_FreeTaskContext(t) \
	do {													\
		const os_task_t *tmp = (t);							\
		OS_FreeCxList(tmp->dynamic->context.pcxiCurrent);	\
		tmp->dynamic->context.pcxiCurrent = 0;				\
	} while (0)

/*! OS_GetTaskSp()
 *  OS_GetTaskSpForce()
 *
 * This macro returns the value of the stack pointer from a task's
 * saved context. The saved context is only valid if the task is in
 * one of the states OS_TS_READY_ASYNC, OS_TS_READY_SYNC or
 * OS_TS_WAITING. On some architectures the saved context might
 * be different depending on the task's state, but for Tricore it's
 * always the same.
 *
 * On TRICORE it might be possible to find the current SP for a
 * task in the OS_TS_RUNNING state by chasing the PCXI list
 * back until the stack changes from interrupt stack to task stack,
 * but this version delivers OS_NULL.
 *
 * The "Force" version always returns the task's SP. It is used in the
 * stack-check macro that's called from the dispatcher. At this point
 * the task is either RUNNING or WAITING (tested explicitly before calling)
 * and the context is known to have been saved. The stack check is performed
 * before the task leaves the RUNNING state.
 *
 * Small change: the dispatcher now calls the stack check also for terminating
 * tasks, which unfortunately don't have a CSA list.
*/
#define OS_GetTaskSp(t)	\
	( ( ((t)->dynamic->state == OS_TS_WAITING) ||					\
		((t)->dynamic->state == OS_TS_READY_SYNC) ||				\
		((t)->dynamic->state == OS_TS_READY_ASYNC) )				\
		? OS_FindTaskSp((t)->dynamic->context.pcxiCurrent)	\
		: OS_NULL )

#define OS_GetTaskSpForce(tp,td)									\
	(	((td)->state <= OS_TS_MAX_TERMINATING)						\
		? (os_address_t)OS_NULL										\
		: ((os_address_t)OS_FindTaskSp((td)->context.pcxiCurrent))	\
	)

#ifndef OS_ASM
void *OS_FindTaskSp(os_uint32_t pcxi);
#endif

/*!
 * os_archapp_s
 *
 * This is the data structure for the architecture-specific application
 * context generated by the generator. It defines the architecture-specific
 * part of the environment an application's tasks/ISRs must run in.
*/
#ifndef OS_ASM

#ifndef OS_N_DPR
#define OS_N_DPR	5	/* No. of data ranges in a set */
#endif

#ifndef OS_N_CPR
#define OS_N_CPR	2	/* No. of code ranges in a set */
#endif

typedef struct os_archapp_s os_archapp_t;

struct os_archapp_s
{
	os_uint32_t		psw;				/* PSW (incl. PRS, CDC) */
};

#define OS_HAVE_ARCHAPP_T  1

#define OS_ARCHAPP_INIT( psw )			\
	{									\
		(psw)							\
	}

#endif

/*!
 * os_savedcontext_t
 *
 * This structure stores the current context so that an execption handler
 * can return to the kernel. It is used for interrupt handling and
 * application-specific hook functions.
*/
#ifndef OS_ASM
typedef struct os_savedcontext_s os_savedcontext_t;

struct os_savedcontext_s
{
	os_uint8_t *stackLimit;		/* Where the stack is at runtime */
	os_uint32_t	pcxi;			/* Saved PCXI for return/kill */
	os_uint32_t	ra;				/* Saved return address for return/kill */
};

#define OS_SAVEDCONTEXT_INIT	\
	{							\
		OS_NULL, /*stackLimit*/	\
		0u, /*pcxi*/			\
		0u /*ra*/				\
	}

#endif

/*!
 * os_archisr_t
 *
 * A structure describing an ISR to the kernel.
 *
 * TRICORE adds the following fields to the ROM structure:
 *   srn        - pointer to service request node for the interrupt.
 *   arbPrio    - arbitration priority (programmed into SRN).
 *   runPrio    - run priority (>= arbPrio)
*/
#ifndef OS_ASM
typedef struct os_archisr_s os_archisr_t;

struct os_archisr_s
{
	os_tricoresrn_t *srn;
	os_uint8_t arbPrio;
	os_uint8_t runPrio;
};

#define OS_ARCHISR_INIT(srn, arbPrio, runPrio)	\
	{											\
		(srn),									\
		(arbPrio),								\
		(runPrio)								\
	}

#endif

/* Return the ISR's priority for use in GetResource. */
#define OS_GetIsrResPrio(isrp)	((isrp)->arch.runPrio)

/*!
 * OS_SetupIsr(), OS_EnableIsr(), OS_DisableIsr(), OS_ClearIsr() and OS_TriggerIsr();
 *
 * Setup/enable/disable/clear/trigger a specific ISR.
 *
 * The "enable" and "disable" macros do not change the priority level. Some
 * Tricores generate a spurious interrupt at level 255 when the priority
 * is changed to zero. The workaround is to globally disable interrupts while
 * doing it. Or not to do it at all ;-)
*/
#define OS_SetupIsr(isr)	OS_SetupIsrFn(isr)
#define OS_EnableIsr(isr)	OS_EnableIsrFn(isr)
#define OS_DisableIsr(isr)	OS_DisableIsrFn(isr)
#define OS_ClearIsr(isr)	OS_ClearIsrFn(isr)
#define OS_TriggerIsr(isr)	OS_TriggerIsrFn(isr)

/*!
 * OS_Idle()
 *
 * This macro forms the body of the idle loop in the dispatcher.
 * It calls the function OS_TricoreIdle() to present an optimisation
 * barrier to the compiler to ensure that global variables are updated
 * before entering the idle loop.
*/
#define OS_Idle() \
	do { \
		os_kerneldata_t * const kdata = OS_GetKernelData(); \
		kdata->inKernel = 0; \
		OS_TricoreIdle(); \
	} while (0)

#ifndef OS_ASM
void OS_TricoreIdle(void);
#endif

/*!
 * OS_IntEnable(), OS_IntDisable(), OS_IntRestore(),
 * OS_IntDisableAll()
 *
 * These routines enable, disable and restore previous state of interrupts.
 * IntEnable and IntDisable both return the old value of CCPN and IE from
 * the ICR, for use in a later IntRestore().
 *
 * The actual macros used are defined in a tool-specific way because of
 * the different macro capabilities of Gnu and Tasking. The macros
 * are defined in the relevant tool-specific include file Os_tool_TRICORE_xxx.h
*/

/*!
 * OS_SuspendInterrupts()
 * OS_SuspendInterruptsX()
 *
 * These macros are used by OS_KernSuspendInterrupts()
 * They disable at the specified level, both in the calling context and
 * in the current context.
 *
 * No special mechanism is in place to avoid multiple evaluations of the
 * parameters. However, in practice each parameter is only used once.
 *
 * The X version is used where interrupts have already been disabled in the
 * kernel function. For TRICORE, we simply call the first macro, discarding the
 * 3rd parameter.
*/
#define OS_SuspendInterrupts(olp, lvl) \
	do {																										\
		os_uppercx_t *OS_TRICORE_cx;																			\
		os_uint32_t OS_TRICORE_old;																				\
		os_uint32_t OS_TRICORE_new;																				\
																												\
		/* Get calling context, get old level from calling context */											\
		OS_DSYNC();																								\
		OS_TRICORE_cx = (os_uppercx_t *)OS_AddrFromCx(OS_MFCR(OS_PCXI));										\
		OS_TRICORE_old = (OS_TRICORE_cx->pcxi) >> OS_PCXI_PCPN_BIT;												\
																												\
		OS_TRICORE_new = (lvl) & (os_uint32_t) OS_ICR_CCPN;														\
																												\
		/* The level is never reduced by a Suspend operation! */												\
		if ( OS_TRICORE_new > OS_TRICORE_old )																	\
		{																										\
			/* Disable interrupts in local context */															\
			OS_MTCR(OS_ICR, ((OS_MFCR(OS_ICR) & (os_uint32_t) ~((os_uint32_t)OS_ICR_CCPN)) | OS_TRICORE_new));	\
																												\
			/* Disable interrupts in calling context */															\
			/* Only works if called via system call */															\
			OS_TRICORE_cx->pcxi =																				\
				(OS_TRICORE_cx->pcxi & ~OS_PCXI_PCPN) |															\
				(OS_TRICORE_new << OS_PCXI_PCPN_BIT);															\
		}																										\
		*(olp) = (os_uint8_t)OS_TRICORE_old;																	\
	} while(0)

#define OS_SuspendInterruptsX(olp, lvl, is)		OS_SuspendInterrupts(olp, lvl)

/*!
 * OS_ResumeInterrupts()
 *
 * This macro is used by OS_KernResumeInterrupts()
 * It disables at the specified level, both in the calling context and
 * in the current context.
 *
 * No special mechanism is in place to avoid multiple evaluations of the
 * parameters. However, in practice the parameter is only used once.
*/
#define OS_ResumeInterrupts(olp) \
	do {																									\
		os_uppercx_t *OS_TRICORE_cx;																		\
		os_uint32_t OS_TRICORE_old;																			\
																											\
		/* Get calling context */																			\
		OS_DSYNC();																							\
		OS_TRICORE_cx = (os_uppercx_t *)OS_AddrFromCx(OS_MFCR(OS_PCXI));									\
																											\
		OS_TRICORE_old = *(olp) & (os_uint32_t) 0xffu;														\
																											\
		/* Resume interrupts in calling context */															\
		/* Only works if called via system call */															\
		OS_TRICORE_cx->pcxi =																				\
			(OS_TRICORE_cx->pcxi & ~OS_PCXI_PCPN) |															\
			(OS_TRICORE_old << OS_PCXI_PCPN_BIT);															\
																											\
		/* Resume interrupts in current context */															\
		OS_MTCR(OS_ICR, ((OS_MFCR(OS_ICR) & (os_uint32_t) ~((os_uint32_t)OS_ICR_CCPN)) | OS_TRICORE_old));	\
	} while(0)


/*!
 * OS_SetIsrResourceLevel()
 *
 * This macro sets the current CPU priority level, *AND* that of the
 * calling context, to the level contained in the specified resource
 * priority. It is assumed that the priority really is an ISR priority.
 *
 * There's no need to mask out the isr-priority indicator from the
 * priority level - the shift eliminates all but the lower 8 bits.
 *
 * There's no need for an explicit DSYNC() before reading PCXI, because
 * the MTCR just before it contains one.
 *
 * Note: this version chases along the CSA list until an entry is found whose call-depth counter (PSW.CDC)
 * is zero. This is the CSA that results from the trap (syscall) and therefore also contains the PCXI
 * value that we need to modify. This method is a little more cumbersome than simply looking in a particular
 * CSA and is tolerant of program changes, compiler differences, compiler optimisation settings etc.
 * If the kernel API function gets called directly and no matching CSA is found, there will eventually
 * be a null-pointer exception when the 0-valued PCXI at the end of the task or ISR's list is found.
*/

#define OS_SetIsrResourceLevel(prio) \
	do {																				\
		os_uint32_t OS_sirlpcxi;														\
		os_uint32_t OS_sirlpsw;															\
		os_uppercx_t *OS_sirlcx;														\
		OS_MTCR(OS_ICR, ((OS_MFCR(OS_ICR) & (os_uint32_t) (~(os_uint32_t) OS_ICR_CCPN))	\
				| ((prio) & (os_uint32_t) OS_ICR_CCPN)));								\
		OS_sirlpcxi = OS_MFCR(OS_PCXI);													\
		do {																			\
			OS_sirlcx = (os_uppercx_t *)OS_AddrFromCx(OS_sirlpcxi);						\
			OS_sirlpcxi = OS_sirlcx->pcxi;												\
			OS_sirlpsw = OS_sirlcx->psw;												\
		} while ( (OS_sirlpsw & OS_PSW_CDC) != 0u );									\
		OS_sirlcx->pcxi = (OS_sirlpcxi & (os_uint32_t ) (~OS_PCXI_PCPN))				\
							| (((prio) & (os_uint32_t) 0xffu) << OS_PCXI_PCPN_BIT);		\
	} while (0)

/*!
 * OS_GetInterruptPriority
 *
 * This macro returns the interrupt priority from a restore value produced
 * by OS_IntDisable() etc.. The interrupt priority is the CPU priority
 * plus 0x100
*/
#define OS_GetInterruptPriority(is)		((os_prio_t) (((is) & OS_ICR_CCPN) + 0x100u))

/*!
 * OS_ResumeTaskSync()
 *
 * This macro resumes a task that relinquished the CPU voluntarily.
 * Simply load PCXI, then RSLCX/RFE.
 *
 * There is no attempt to make the boy of the macro into a single statement
 * because the macro is used in exactly one known place.
*/
#define OS_ResumeTaskSync(t) \
	OS_MTCR(OS_PCXI, (t)->dynamic->context.pcxiCurrent);	\
	OS_RSLCX();												\
	OS_RFE();

/*!
 * OS_ResumeTaskAsync()
 *
 * This macro resumes a task that relinquished the CPU involuntarily (was
 * pre-empted). For Tricore there is no difference between sync and async.
 * Same as OS_ResumeTaskSync()
*/
#define OS_ResumeTaskAsync(t)		OS_ResumeTaskSync(t)

/*!
 * OS_startupTrapTable, OS_trapTable and OS_interruptTable
 *
 * These aren't really variables - they're code stubs in their own sections.
 * The symbols are generated in assembly-language files. We declare them
 * as extern variables simply so that we can take their addresses.
*/
#ifndef OS_ASM
/* Deviation MISRAC2012-1 */
extern void OS_trapTable(void);
extern void OS_startupTrapTable(void);
extern void OS_interruptTable(void);
#endif

/*!
 * OS_GetCurrentSp() returns the current value of the stack pointer.
 * It is used in the stack check code, and in the stack initialisation
 * in OS_KernStartOs()
*/
#define OS_GetCurrentSp()	OS_MFSP()

/*!
 * OS_kernDpr, OS_kernCpr, OS_kernDpm, OS_kernCpm
 * OS_userCpm
 *
 * Data and code protection register settings (set 0) for kernel mode.
 * Code protection mode for non-trusted user mode
*/
#ifndef OS_ASM
extern const os_uint32_t OS_kernDpr[OS_N_DPR * 2];
extern const os_uint32_t OS_kernCpr[OS_N_CPR * 2];
extern const os_uint32_t OS_kernDpm;
extern const os_uint32_t OS_kernCpm;
extern const os_uint32_t OS_userCpm;
#endif


/*!
 * OS_TaskMemoryAccess()
 * OS_IsrMemoryAccess()
 *
 * These two macros check whether a nontrusted task/ISR has access to the
 * specified memory region. The private data and stack areas are checked
 * by the architecture-independent code, so we're only interested in the
 * global areas, which are read-only and possibly executable.
 *
 * On TRICORE, these two areas are represented by the constant
 * OS_globalCpr array and the variable (set at startup)
 * OS_globalDpr array. The Dpr array contains three base/limit
 * pairs. The Cpr array contains as many base/limit pairs as there are
 * code-protection register pairs in Tricore. At the moment, only one
 * of the CPR pairs is used, so this macro only tests against those
 * values. If this should ever change (TRICORE-setprotection.c, Os_configuration_TRICORE.c),
 * this macro needs attention.
*/
#ifndef OS_ASM
extern const os_uint32_t OS_globalCpr[OS_N_CPR * 2];
extern const os_uint32_t OS_globalDpr[6];
#endif

#define OS_GlobalMemoryAccess(f,l) \
	(	( (((f)>=OS_globalCpr[0]) && ((l)<=OS_globalCpr[1]))	\
			? OS_MA_EXEC										\
			: 0u												\
		) |	/* Bitwise OR - intentional! */						\
		( (((f)>=OS_globalDpr[0]) && ((l)<=OS_globalDpr[1]))	\
			? OS_MA_READ										\
			: 0u												\
		) |	/* Bitwise OR - intentional! */						\
		( (((f)>=OS_globalDpr[2]) && ((l)<=OS_globalDpr[3]))	\
			? OS_MA_READ										\
			: 0u												\
		) |	/* Bitwise OR - intentional! */						\
		( (((f)>=OS_globalDpr[4]) && ((l)<=OS_globalDpr[5]))	\
			? OS_MA_READ										\
			: 0u												\
		)														\
	)

#define OS_TaskMemoryAccess(t,f,l)	OS_GlobalMemoryAccess(f,l)
#define OS_IsrMemoryAccess(i,f,l)	OS_GlobalMemoryAccess(f,l)

/* TRICORE: word accesses must be at even addresses, unless the CPU
 * or toolchain behaves differently
*/
#ifndef OS_ArchMisalignedData
#define OS_ArchMisalignedData(b,l)	( ((l) > 1u) && ((((os_uint32_t)(b)) & 1u) != 0u) )
#endif

/*!
 * OS_GetTrustedCallerSp
 *
 * This macro returns the caller's stack pointer to be used in the stack check
 * when calling a trusted function. The provided stack pointer is expected to
 * lie between the bounds returned by the OS_GetTrustedFunctionStackBounds
 * macro.
 *
 * This is the TRICORE-specific implementation, where trusted functions are
 * executed on the stack of the calling task or ISR. The macro returns the
 * stack pointer of the calling Task/ISR from the saved context.
 *
 * Param spp: type os_address_t*, to store the caller's stack pointer
 */
#define OS_GetTrustedCallerSp(spp) \
	do {											\
		os_uint32_t cxi;							\
		os_uppercx_t *csa;							\
													\
		OS_DSYNC();									\
		cxi = OS_MFCR(OS_PCXI);						\
		csa = (os_uppercx_t *)OS_AddrFromCx(cxi);	\
		cxi = csa->pcxi;							\
		csa = (os_uppercx_t *)OS_AddrFromCx(cxi);	\
		*(spp) = csa->a10;							\
	} while (0)

/*!
 * OS_GetTrustedFunctionStackBounds
 *
 * This macro determines the lower and upper bounds for the stack of
 * a trusted function to be executed.
 *
 * On the Tricore, trusted functions are executed on the stack of the calling
 * task or ISR. Therefore, we use the implementation for function call kernels
 * here, which determines exactly these bounds.
 *
 * Param lbp: type os_address_t*, to store the lower bound
 * Param ubp: type os_address_t*, to store the upper bound
*/
#define OS_GetTrustedFunctionStackBounds(lbp,ubp) OS_GetTFStackBounds_Fctcall(lbp,ubp)
#define OS_NEEDS_GetTFStackBounds_Fctcall 1

/*!
 * OS_CallIsrDirect()
 *
 * This macro calls an ISR directly.
 *
 * The macro's parameters must be simple variables, not expressions. This
 * should not be a problem, however, because it's only used in the
 * Cat2Entry and Cat2KEntry routines.
*/
#define OS_CallIsrDirect(isr, id) \
	do {																\
		os_uint32_t oldIcr;												\
																		\
		oldIcr = OS_MFCR(OS_ICR);										\
		OS_MTCR(OS_ICR, (oldIcr & (os_uint32_t) ~((os_uint32_t)OS_ICR_CCPN)) | (isr)->arch.runPrio);	\
																		\
		(*((isr)->func))();												\
																		\
		OS_MTCR(OS_ICR, oldIcr);										\
	} while(0)

/*!
 * OS_CallIsrIndirect()
 *
 * This macro calls an ISR.
 *
 * If Autosar semantics are specified, the ISR is called via OS_TricoreCallIsr().
 * OS_TricoreCallIsr() saves its context so that if the ISR misbehaves the
 * error handler can kill it by appearing to return from the call to
 * OS_TricoreCallIsr(). For this reason setting the ISR's saved
 * context null is done here rather than in OS_TricoreCallIsr().
 *
 * The macro's parameters must be simple variables, not expressions. This
 * should not be a problem, however, because it's only used in the
 * Cat2Entry routine.
*/
#define OS_CallIsrIndirect(isr, id)		\
	do {								\
		OS_TricoreCallIsr(isr, id);		\
										\
		(id)->c.pcxi = 0U;				\
		(id)->c.stackLimit = OS_NULL;	\
	} while(0)

/*!
 * OS_GetIsrStackLimit()
 *
 * Returns the stack limit of the specified ISR, as set up by OS_CallIsr()
*/
#define OS_GetIsrStackLimit(id)	((id)->c.stackLimit)

/*!
 * OS_ArchCallStartupHook()
 * OS_ArchCallShutdownHook()
 * OS_ArchCallErrorHook()
 *
 * These macros call an application-specific hook functions when Autosar kernel semantics are configured.
 *
 * The hook is called via OS_CallAppHook().
 * OS_CallAppHook() saves its context so that if the hook misbehaves
 * the error handler can kill it by appearing to return from the call to
 * OS_CallAppHook(). For this reason setting the hook's saved
 * context to null is done here rather than in OS_CallAppHook().
 *
 * The startup and shutdown hooks can safely share a return context because
 * the two will never be used simultaneously.
 *
 * The macros' parameters must be simple variables, not expressions. This
 * should not be a problem, however, because they are only used in internal
 * kernel functions.
*/
/* Deviation MISRAC2012-2 <START> */
#define OS_ArchCallStartupHook(app) \
	do {																				\
		os_kerneldata_t * const hcall_kernel_data = OS_GetKernelData();					\
		OS_CallAppHook((app), &hcall_kernel_data->sHookContext.c, (app)->startupHook,	\
						(app)->startupHookStack, 0);									\
		hcall_kernel_data->sHookContext.c.pcxi = 0;										\
		hcall_kernel_data->sHookContext.c.stackLimit = OS_NULL;							\
	} while(0)

#define OS_ArchCallShutdownHook(app, code) \
	do {																				\
		os_kerneldata_t * const hcall_kernel_data = OS_GetKernelData();					\
		OS_CallAppHook((app), &hcall_kernel_data->sHookContext.c, (app)->shutdownHook,	\
						(app)->shutdownHookStack, (code));								\
		hcall_kernel_data->sHookContext.c.pcxi = 0;										\
		hcall_kernel_data->sHookContext.c.stackLimit = OS_NULL;							\
	} while(0)

#define OS_ArchCallErrorHook(app, code) \
	do {																			\
		os_kerneldata_t * const hcall_kernel_data = OS_GetKernelData();				\
		OS_CallAppHook((app), &hcall_kernel_data->eHookContext.c, (app)->errorHook,	\
						(app)->errorHookStack, (code));								\
		hcall_kernel_data->eHookContext.c.pcxi = 0;									\
		hcall_kernel_data->eHookContext.c.stackLimit = OS_NULL;						\
	} while(0)
/* Deviation MISRAC2012-2 <STOP> */

/*!
 * OS_CFG_INITARCH
 *
 * This macro defines the architecture-specific initialisation
 * function that gets called as the first initialisation function
 * in StartOS.
*/
#define OS_CFG_INITARCH	(&OS_InitArchTricore)

#ifndef OS_ASM
void OS_InitArchTricore(void);
#endif

/*
 * Timestamp driver
 *
 * Tricore's STM is used as the timestamp timer. It is only 56 bits, not the full 64 bits
 * expected by the generic code, but the Tricore's design is (theoretically) that the STM
 * should never overflow during the lifetime of the processor, so we don't need to consider
 * extending the range.
*/
#define OS_USEGENERICTIMESTAMP		0
#define OS_USE_GLOBAL_GENERICTIMESTAMP	0
#define OS_AdvanceTimeStamp(t)		do { } while(0)


/*!
 * Align the stack pointer sp, so that the granularity of the
 * protection registers is met.
 *
 * sp: stack pointer.
 */
#if (OS_DPRX_GRANULARITY_BITS > 0)
#define OS_ALIGN_STACK(sp)										\
	do {														\
		(sp) &= (os_uint32_t)									\
				~(((os_uint32_t)1u << OS_DPRX_GRANULARITY_BITS) - 1u);	\
	} while (0)
#else
#define OS_ALIGN_STACK(sp)
#endif /* (OS_DPRX_GRANULARITY_BITS > 0) */

#ifndef OS_ASM
/*
 * OS_StartupCheckTricore
 *
 * Function that performs TRICORE-specific startup checks.
 *
 * Currently only used for Aurix processors.
*/
os_result_t OS_StartupChecksTricore(void);
#define OS_ARCH_STARTUPCHECKS OS_StartupChecksTricore
#endif

#endif /* OS_KERNEL_TYPE!=OS_MICROKERNEL */

/* Get Kernel array pointer from A8 */
#define OS_GetKernelData()	((os_kerneldata_t *)OS_MFA8())

/* Get the address of the instruction causing the trap,
 * given the upper context previous to the OS' trap handler.
*/
#define OS_GetTrapPCFromUpperCx(ucx)	(((os_lowercx_t*)OS_AddrFromCx((ucx)->pcxi))->a11)

/* Macro OS_TricoreGetCoreId for single-core derivatives */
#if (OS_N_CORES_MAX == 1u)
#ifndef OS_TricoreGetCoreId
#define OS_TricoreGetCoreId()			((os_coreid_t)0U)
#endif
#endif

/* Multicore support.
 *
*/
#if (OS_N_CORES_MAX > 1u)

#ifndef OS_TricoreGetCoreId
#ifndef EB_STATIC_CHECK
#if (OS_TRICOREARCH == OS_TRICOREARCH_162)
/*  TC39xX doesn't have consecutive core IDs */
#define OS_TricoreGetCoreId()	((os_coreid_t)((OS_MFCR(OS_CORE_ID)==6)?5:OS_MFCR(OS_CORE_ID)))
#elif (OS_TRICOREARCH == OS_TRICOREARCH_16EP)
#define OS_TricoreGetCoreId()	((os_coreid_t)OS_MFCR(OS_CORE_ID))
#elif (OS_TRICOREARCH == OS_TRICOREARCH_18)
#define OS_TricoreGetCoreId()	((os_coreid_t)(OS_MFCR(OS_CORE_ID) & OS_CORE_MASK))
#else /* OS_TRICOREARCH */
#error "Unexpected TRICORE architecture in OS_TRICOREARCH"
#endif /* OS_TRICOREARCH */
#else
#define OS_TricoreGetCoreId()			((os_coreid_t)OS_STATIC_CHECK_ReadHwReg())
#endif /* ifndef EB_STATIC_CHECK */
#endif /* ifndef OS_TricoreGetCoreId */
#endif


#if (OS_N_CORES > 1u)

#define OS_XC_REPLY_DIRECTLY		OS_U(1)
#define OS_NHARDWARELOCKS			OS_U(0)

#define OS_GetMyCoreId()		OS_TricoreGetCoreId()

#ifndef OS_ASM
extern os_tricoresrn_t * const OS_xCoreSrc[OS_N_CORES_MAX];
#endif

#if ((OS_TRICOREARCH == OS_TRICOREARCH_16EP) || (OS_TRICOREARCH == OS_TRICOREARCH_162))

/* Deviation MISRAC2012-3 <+1> */
#define OS_NotifyCore(c)	\
	do {												\
		os_tricoresrn_t * const src = OS_xCoreSrc[(c)];	\
		if (src != OS_NULL) {							\
			*src |= OS_SRN_SETR;						\
			*src;										\
		}												\
	} while (0)

/* Deviation MISRAC2012-3 <+1> */
#define OS_AckNotifyCore()  \
	do {												\
		const os_coreid_t c = OS_GetMyCoreId();			\
		os_tricoresrn_t * const src = OS_xCoreSrc[c];	\
		if (src != OS_NULL) {							\
			*src |= OS_SRN_CLRR;						\
			*src;										\
		}												\
	} while (0)

#elif (OS_TRICOREARCH == OS_TRICOREARCH_18)

#ifndef OS_ASM
void OS_NotifyCoreTc18(os_uint32_t);
#endif

#define OS_NotifyCore OS_NotifyCoreTc18
#define OS_AckNotifyCore() do { /* Hardware acknowledges automatically. */ } while (0)

#else
#error "Unexpected OS_TRICOREARCH"
#endif

/* Semaphore handling:
 * We have no hardware semaphores.
 */
#define OS_ArchTakeHardwareLock(l, is)              \
    do {                                            \
    } while (0)

#define OS_ArchDropHardwareLock(l)  \
    do {                            \
    } while (0)


/* start a specific core */
#define OS_ArchStartCore(c) OS_TricoreStartCore(c)

#endif /* (OS_N_CORES > 1u) */

#endif /* ! OS_KERNEL_TRICORE_H */
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
