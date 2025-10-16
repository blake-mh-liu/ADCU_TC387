/* kern-mkwupdatecounter.c
 *
 * This file contains the OS_MkwUpdateCounter function.
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

/* OS_MkwUpdateCounter
 *
 * This function is a wrapper for OS_HwCounterUpdate, meant for the micro-kernel.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
mk_parametertype_t OS_MkwUpdateCounter(
	mk_parametertype_t p0,
	mk_parametertype_t p1,
	mk_parametertype_t p2 )
OS_TOOL_FUNCTION_ATTRIB_POST
{
	/* COVPT-1 */
	OS_PARAM_UNUSED(p1);
	OS_PARAM_UNUSED(p2);

	OS_HwCounterUpdate(&OS_counterTableBase[p0]);
	/* This function returns void, so the return value doesn't matter. */
	return 0;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE == OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_mkw_updatecounter_c = 0xeb;
#endif /* (OS_KERNEL_TYPE == OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
