/* TRICORE-startupchecks.c
 *
 * This file contains the OS_StartupChecksTricore function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_configuration.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_kernel.h>
#include <Os_panic.h>


#include <memmap/Os_mm_code_begin.h>

/* OS_StartupChecksTricore
 *
 * This function checks (on multi-core processors) that the OS is executed on the correct core.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_result_t OS_StartupChecksTricore(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_result_t result = OS_E_OK;

	/* For single core processors, OS_TricoreGetCoreId() returns 0,
	 * so compiler detects that "if" condition never becomes true, and warns of unreachable statement.
	*/
#if (OS_N_CORES_MAX > 1)
	if ( OS_TricoreGetCoreId() >= OS_N_CORES_MAX )
	{
		result = OS_PANIC(OS_PANIC_SCHK_InvalidCore);
	}
#endif
	return result;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <TRICORE/Os_dummies_TRICORE.h>
const os_uint8_t OS_dummy_TRICORE_startupchecks_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
