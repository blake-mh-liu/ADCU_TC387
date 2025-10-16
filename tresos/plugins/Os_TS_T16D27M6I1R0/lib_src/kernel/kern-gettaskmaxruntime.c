/* lib-gettaskmaxruntime.c
 *
 * This file contains the OS_GetTaskMaxRuntime function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_acct_api.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_GetTaskMaxRuntime
 *
 * This library function returns the longest observed run-time for a task.
 * It can be called by any trusted application. On some architectures
 * it might be callable from non-trusted applications too.
 *
 * If the task ID is out of range, or if the task does not have runtime
 * measurement enabled, E_OS_ID is returned. Otherwise, the task's
 * longest observed runtime is placed in the out location and E_OK is returned.
 * The error handler ia not called, so no error hook is called.
 *
 * !LINKSTO Kernel.Feature.OsAccounting, 1,
 * !        Kernel.Feature.OsAccounting.API.GetTaskMaxRuntime, 1
 * !doctype SRC
*/

OS_TOOL_FUNCTION_ATTRIB_PRE
os_result_t OS_GetTaskMaxRuntime(os_taskid_t t, os_tick_t *out)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_result_t r = OS_E_ID;
	const os_task_t *ts;
	os_taskaccounting_t *ta;

	if ( t < OS_nTasks )
	{
		ts = &OS_taskTableBase[t];
		ta = OS_GET_ACCT(ts->accounting);

		if ( (ts->flags & OS_TF_MEASUREEXEC) != 0u )
		{
			*out = ta->etMax;
			r = OS_E_OK;
		}
	}

	return r;
}

#include <memmap/Os_mm_code_end.h>


#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_gettaskmaxruntime_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
