/* kern-panic.c
 *
 * This file contains the OS_Panic function.
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
 *   OS_Panic() detects recursive calls by means of the core-local variable
 *   panicCode. If OS_Panic() is entered a second time, it calls
 *   OS_ShutdownNoHooks() which doesn't call OS_Panic() again. Instead, it
 *   stops the system, and, therefore, the maximum nesting level is two calls.
 *
 * MISRAC2012-2) Deviated Rule: 2.1 (required)
 *   A project shall not contain unreachable code.
 *
 * Reason:
 *   This statement shall never be reached, as the program is halted because of
 *   an unrecoverable error.
*/

/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: StatementIsUnreachable
 *   The statement cannot be reached by the control flow.
 *
 * Reason: This statement shall never be reached, as the program is halted because
 * of an unrecoverable error.
 *
 * TOOLDIAG-2) Possible diagnostic: InfiniteLoop
 *   Possible infinite loop
 *
 * Reason: Intentional endless loop in case of counter subsystem panic in a Safety OS system.
*/

#include <Os_kernel.h>
#include <Os_panic.h>

#if OS_KERNEL_TYPE==OS_MICROKERNEL
#include <public/Mk_autosar.h>
#endif

#include <memmap/Os_mm_code_begin.h>

/* OS_Panic
 *
 * This function is called whenever the kernel detects an internal error
 * from which it cannot recover.
*/
/* Deviation MISRAC2012-1 <+2> */
OS_TOOL_FUNCTION_ATTRIB_PRE
os_result_t OS_Panic(os_panic_t curPanicCode)
OS_TOOL_FUNCTION_ATTRIB_POST
{
#if OS_KERNEL_TYPE==OS_MICROKERNEL
	/* COVPT-1 */
	*(OS_panicCodePtrs[GetCoreID()]) = curPanicCode;

	/* Possible diagnostic TOOLDIAG-2 <1> */
#pragma warning 557
	for (;;) {}
#pragma warning default
#else
	os_kerneldata_t * const kernel_data = OS_GetKernelData();
	/* COVPT-2 */
	if (kernel_data->panicCode == OS_PANIC_NONE)
	{
		/* This is the first time OS_Panic is entered, so try OS_Shutdown. */
		kernel_data->panicCode = curPanicCode;
		/* Deviation MISRAC2012-1 <+1> */
		OS_Shutdown(OS_E_PANIC, OS_FALSE);
	}
	else
	{
		/* Entered OS_panic the second time, so call OS_ShutdownNoHooks, which can't panic. */
		OS_ShutdownNoHooks();
	}
#endif
	/* Deviation MISRAC2012-2 <+2> */
	/* Possible diagnostic TOOLDIAG-1 <1> */
#pragma warning 544
	return OS_E_PANIC;
#pragma warning default
}

#include <memmap/Os_mm_code_end.h>

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
