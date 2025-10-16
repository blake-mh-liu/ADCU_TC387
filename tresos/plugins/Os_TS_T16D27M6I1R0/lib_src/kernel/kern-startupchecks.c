/* kern-startupchecks.c
 *
 * This file contains the OS_StartupChecks function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_panic.h>

#include <memmap/Os_mm_code_begin.h>

/* OS_StartupChecks
 *
 * This function performs a variety of consistency and sanity checks on the configuration
 * data and other tables to try to ensure that the generator is behaving itself as far as we can
 * tell.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_StartupChecks(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_result_t result = OS_E_OK;
	const os_schkfunc_t * fct;

	fct = &OS_startupCheckFunc[0];
	while ( *fct != OS_NULL )
	{
		/* COVPT-1 */
		if ( (*fct)() != OS_E_OK )
		{
			result = OS_E_PANIC;
		}
		fct++;
	}

	/* COVPT-2 */
	if ( result != OS_E_OK )
	{
		OS_ShutdownNoHooks();
	}
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_startupchecks_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
