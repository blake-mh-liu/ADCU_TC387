/* kern-triggerinterrupt.c
 *
 * This file contains the OS_TriggerInterrupt function
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_TriggerInterrupt triggers the interrupt source of the specified ISR.
 *
 * If the ISR is not valid, the command is silently ignored.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_TriggerInterrupt(os_isrid_t i)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	const os_isr_t *isr;

	/* COVPT-1 */
	if ( i < OS_nInterrupts )
	{
		isr = &OS_isrTableBase[i];

		OS_TriggerIsr(isr);
	}
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_triggerinterrupt_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
