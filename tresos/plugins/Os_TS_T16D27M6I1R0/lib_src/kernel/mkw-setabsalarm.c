/* kern-mkwsetabsalarm.c
 *
 * This file contains the OS_MkwSetAbsAlarm function.
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
#include <Os_panic.h>

#include <memmap/Os_mm_code_begin.h>

OS_TOOL_FUNCTION_ATTRIB_PRE
mk_parametertype_t OS_MkwSetAbsAlarm(
	mk_parametertype_t p0,
	mk_parametertype_t p1,
	mk_parametertype_t p2 )
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_alarmid_t const a = (os_alarmid_t) p0;
	os_tick_t const start = (os_tick_t) p1;
	os_tick_t const cyc = (os_tick_t) p2;
	/* COVPT-1 */
	return OS_KernSetAbsAlarm(a, start, cyc);
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE == OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_mkw_setabsalarm_c = 0xeb;
#endif /* (OS_KERNEL_TYPE == OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
