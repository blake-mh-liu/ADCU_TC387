/* kern-mkwgetcountervalue.c
 *
 * This file contains the OS_MkwGetCounterValue function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_types.h>
#if (OS_KERNEL_TYPE == OS_MICROKERNEL)

#include <public/Mk_public_types.h>
#include <Os_mkctrsub.h>
#include <Os_kernel.h>

#include <memmap/Os_mm_code_begin.h>

/* OS_MkwGetCounterValue
 *
 * This function provides a wrapper for OS_KernGetCounterValue so that it can be called
 * in an OS thread in the microkernel
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
mk_parametertype_t OS_MkwGetCounterValue(
	mk_parametertype_t p0,
	mk_parametertype_t p1,
	mk_parametertype_t p2 )
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_tick_t localcount;
	os_counterid_t const c = (os_counterid_t) p0;
	os_result_t result = OS_KernGetCounterValue(c, &localcount);

	/* COVPT-1 */
	OS_PARAM_UNUSED(p1);
	OS_PARAM_UNUSED(p2);

	MK_UsrTerminateSelfWithValue(result, localcount);
	return localcount; /*unreachable*/
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE == OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_mkw_getcountervalue_c = 0xeb;
#endif /* (OS_KERNEL_TYPE == OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
