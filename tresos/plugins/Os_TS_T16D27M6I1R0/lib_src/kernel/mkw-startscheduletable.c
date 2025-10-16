/* mkw-startscheduletable.c
 *
 * This file contains the OS_MkwStartScheduleTable function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 10.5 (advisory)
 * The value of an expression should not be cast to an inappropriate essential type.
 *
 * Reason:
 * This is a wrapper function between microkernel counter-subsystem.
 * For some arguments, microkernel uses different essential types.
*/


#include <Os_types.h>
#if (OS_KERNEL_TYPE == OS_MICROKERNEL)

#include <public/Mk_public_types.h>
#include <Os_mkctrsub.h>
#include <Os_kernel.h>
#include <Os_panic.h>

#include <memmap/Os_mm_code_begin.h>

OS_TOOL_FUNCTION_ATTRIB_PRE
mk_parametertype_t OS_MkwStartScheduleTable(
	mk_parametertype_t p0,
	mk_parametertype_t p1,
	mk_parametertype_t p2 )
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_scheduleid_t const s = (os_scheduleid_t) p0;
	os_tick_t const offset = (os_tick_t) p1;
	/* Deviation MISRAC2012-1 <+1> */
	os_boolean_t const rel = (os_boolean_t) p2;
	/* COVPT-1 */
	return OS_KernStartScheduleTable(s, offset, rel);
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE == OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_mkw_startscheduletable_c = 0xeb;
#endif /* (OS_KERNEL_TYPE == OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
