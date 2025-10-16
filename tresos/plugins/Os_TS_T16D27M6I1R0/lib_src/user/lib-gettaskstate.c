/* lib-gettaskstate.c
 *
 * This file contains the OS_GetTaskState function.
 * The OS task state is translated into the equivalent OSEK/VDX state
 * and stored where indicated.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 12.3 (required)
 * The comma operator shall not be used.
 *
 * Reason:
 * For function-call kernels, OS API is wrapped in macros. The macro wrappers
 * need to use the comma operator to form an expression evaluating to the
 * correct result.
 *
 *
 * MISRAC2012-2) Deviated Rule: 13.3 (advisory)
 * The increment (++) and decrement (--) operators should not be mixed with
 * other operators in an expression.
 *
 * Reason:
 * For function-call kernels, OS API is wrapped in macros. The macro wrappers
 * need to handle an "in kernel" flag so that the increment operator has to be
 * used in combination with the comma operator.
 * 
 * MISRAC2012-3) Deviated Rule: 8.9 (advisory)
 * An object should be defined at block scope if its identifier only appears
 * in a single function.
 *
 * Reason:
 * Readability. Defining and initialising a large constant array inside a small
 * function obscures the purpose of the function.
*/

#include <Os_api.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_tool.h>

/* This array contains entries for each valid OS task state. The
 * entry contains the equivalent OSEK/VDX state.
*/
#include <memmap/Os_mm_const_begin.h>
/* Deviation MISRAC2012-3 <+1> */
static const TaskStateType OS_taskStateToOsek[OS_TS_NSTATES] =
{	SUSPENDED,		/* OS_TS_SUSPENDED		*/
	SUSPENDED,		/* OS_TS_QUARANTINED	*/
	READY,			/* OS_TS_NEW			*/
	READY,			/* OS_TS_READY_SYNC		*/
	READY,			/* OS_TS_READY_ASYNC	*/
	RUNNING,		/* OS_TS_RUNNING		*/
	WAITING,		/* OS_TS_WAITING		*/
};
#include <memmap/Os_mm_const_end.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_GetTaskState implements the API GetTaskState
 *
 * The system call OS_UserGetTaskState is called. This places
 * the state of the specified task in the caller-supplied variable, or
 * returns an error code. If all is OK this routine translates the return
 * value into the more limited Autosar/OSEK form. In any case the
 * return value from OS_UserGetTaskState() is returned.
 *
 * !LINKSTO Kernel.API.TaskManagement.GetTaskState.API, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
StatusType OS_GetTaskState(TaskType t, TaskStateRefType sr)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_result_t r;

	/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
	r = OS_UserGetTaskState(t, sr);

	if ( r == OS_E_OK )
	{
		/* COVPT-1 */
		if ( *sr >= OS_TS_NSTATES )
		{
			/* UNREACHABLE? - Should never get here if the kernel is behaving itself
			*/
			r = OS_E_UNKNOWN;
		}
		else
		{
			/* Translate the OS task state to OSEK/VDX value and store.
			*/
			*sr = OS_taskStateToOsek[*sr];
		}
	}

	return r;
}


#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
const os_uint8_t OS_dummy_lib_gettaskstate_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
