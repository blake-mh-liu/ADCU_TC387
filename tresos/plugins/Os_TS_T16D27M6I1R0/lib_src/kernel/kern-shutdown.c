/* kern-shutdown.c
 *
 * This file contains the OS_Shutdown function.
 * The function does the job of shutting down the kernel.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/*
 * MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 17.2 (required)
 *   Functions shall not call themselves, either directly or indirectly.
 *
 * Reason:
 *   OS_Shutdown() might call itself indirectly via OS_Panic().
 *   OS_Panic() detects recursive calls by means of the core-local variable
 *   panicCode. If OS_Panic() is entered a second time, it calls
 *   OS_ShutdownNoHooks() which doesn't call OS_Panic() again. Instead, it
 *   stops the system, and, therefore, the maximum nesting level is two calls.
*/

/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: InfiniteLoop
 *   Possible infinite loop.
 *
 * Reason: Infinite loop is wanted here.
 *
 * TOOLDIAG-2) Possible diagnostic: PointlessComparison
 *   Condition is always true.
 *
 * Reason: On single-core configurations the check, whether an application runs on the current core
 *   is always true, but on multi-core configurations it isn't.
 *
 * TOOLDIAG-3) Possible diagnostic: GNUStatementExpressionExtension
 *   Use of GNU statement expression extension.
 *
 * Reason: This function is implemented by using a function like macro that
 * makes use of the GNU statement expression extension for better maintainability.
*/

#define OS_SID	OS_SID_ShutdownOs
#define OS_SIF	OS_svc_ShutdownOs

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_tool.h> /* for OS_ENDLESSLOOP */

/* Include definitions for tracing */
#include <Os_Trace.h>

#include <memmap/Os_mm_code_begin.h>

static void OS_HandleShutdownHook(os_result_t code);
OS_TOOL_FUNCTION_ATTRIB_PRE
static void OS_HandleShutdownHook(os_result_t code)
OS_TOOL_FUNCTION_ATTRIB_POST
{
#if (OS_N_CORES > 1)
	/* Disable all interrupt sources except for cross-core interrupts */
	OS_DisableAllInterruptSources(OS_ISRF_CROSSCORE);

	/* We want to reflect the correct state before enabling cross-core interrupts.
	 * This is for the case when a cross-core interrupt gets triggered just after
	 * enabling of cross-core interrupts. We don't need the last state of inFunction.
	*/
	OS_GetKernelData()->inFunction = OS_INSHUTDOWNHOOK;
	/* This opens the cross-core interrupts so that the other cores can continue to run.
	 * We enable this before a call to shutdown hook in case shutdown hook doesn't return.
	 * All interrupt sources except for cross-core are disabled at this point including CAT1.
	*/
	OS_IntEnableXcoreFromShutdown();
#endif

	/* !LINKSTO Kernel.API.Hooks.ShutdownHook.API, 1
	 * !LINKSTO Kernel.API.Hooks.ShutdownHook.Shutdown, 1
	 * !LINKSTO Kernel.Autosar.Multicore.Shutdown.ShutdownHook, 1
	 * !LINKSTO Kernel.HookRoutines.PrioISRC2, 1
	 *		Interrupts are disabled here
	*/

	OS_CALLSHUTDOWNHOOK(code);

	OS_ShutdownNoHooks();
}

/*!
 * OS_Shutdown
 *
 * This function shuts down the OS. Interrupts are disabled at the
 * "disable all" level so that category 1 interrupts are blocked,
 * but any higher priority interrupts remain enabled.
 * This means that a future OSEK/Time subsystem would continue to run.
 * The sync parameter (if TRUE) indicates that we do a synchronized shutdown
 * of all cores on a multicore system.
 *
 * !LINKSTO Kernel.Autosar.Multicore.Shutdown, 1
 * Look! No Post-task hooks!
 * !LINKSTO Kernel.Autosar.ServiceErrors.Miscellaneous.Shutdown.PostTaskHook, 1
*/
/* Deviation MISRAC2012-1 <+2> */
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_Shutdown(os_result_t code, os_boolean_t sync)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_kerneldata_t * const kernel_data = OS_GetKernelData();

	kernel_data->inFunction = OS_ININTERNAL;

	/* !LINKSTO Kernel.HookRoutines.PrioISRC2, 1
	 *
	 * In fact, we block Cat1 interrupts too:
	 * !LINKSTO Kernel.Autosar.OSEK.Differences.ShutdownOS, 1
	 *
	 * The call to OS_IntDisableConditional) *after* OS_IntDisableAll() ensures that neither Cat1 nor Execution
	 * Timer interrupts can get through, no matter what their relative levels are. (ASCOS-1475)
	 *
	 * NOTE: This may have to be refined for multicore because the cross-core interrupt - which will be blocked
	 * by OS_IntDisableConditional() - will need to be opened at some stage.
	*/
	(void) OS_IntDisableAll(); /* old level discarded */
	(void) OS_IntDisableConditional(); /* old level discarded */
	/* Possible diagnostic TOOLDIAG-3 <+1> */
	OS_SHUTDOWNEXECTIMING();

#if (OS_N_CORES > 1)
	OS_ReleaseSpinlocksCurCore();
#endif

	/* Call all the application-specific shutdown hooks. This is done
	 * BEFORE the global shutdown hook, according to the Autosar spec.
	 *
	 * !LINKSTO Kernel.Autosar.OsApplication.ApplicationHooks.ShutdownHook.Order, 1
	*/
	if ( kernel_data->appsStarted != 0u )
	{
		/* Possible diagnostic TOOLDIAG-2 <+2> */
		/* Possible diagnostic TOOLDIAG-3 <+1> */
		OS_CALLAPPSHUTDOWNHOOKS(code);
	}

#if (OS_N_CORES == 1)
	OS_PARAM_UNUSED(sync);
#else
	/* Synchronize here before going on to the global shutdown hook
	 * !LINKSTO Kernel.Autosar.Multicore.Shutdown.Synchronize, 1
	*/
	OS_SyncHereIf(sync);
#endif

	OS_HandleShutdownHook(code);
}

OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_ShutdownNoHooks(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	/* Note: Due to MISRA 16.2
	 *  - This function must not call OS_Panic.
	 *  - This function must not call OS_TakeInternalLock/OS_DropInternalLock.
	 * See the respective functions for further information.
	*/
	/* Set inFunction to SHUTDOWN state before spinning forever. This
	 * could be used by (eg) a future mixed OSEK/Time system to determine
	 * the state of the underlying OSEK/OS.
	*/
	/* COVPT-1 */
	OS_GetKernelData()->inFunction = OS_INSHUTDOWN;

	/* Signal shutdown to tracing. */
	OS_HW_TRACE_TASK(OS_NULLTASK);
	OS_HW_TRACE_ISR(OS_NULLISR);

#if (OS_N_CORES > 1)
	/* Enable cross-core interrupts again here in case ShutdownHook called
	 * any interrupts related OS services and returns afterwards.
	*/
	OS_IntEnableXcoreFromShutdown();
#endif

	/* Do architecture-dependent actions before the wait loop is entered. */
	OS_ArchPreDynamicStop();

	/* Endless loop if the shutdown hook ever returns. When called from OS_Shutdown() (above),
	 * "all" interrupts are disabled.
	 *
	 * !LINKSTO Kernel.API.OSControl.ShutdownOS.Shutdown, 1
	 * !LINKSTO Kernel.Autosar.OSEK.Differences.ShutdownOS, 1
	 *
	*/
	OS_ENDLESSLOOP();
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_shutdown_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
