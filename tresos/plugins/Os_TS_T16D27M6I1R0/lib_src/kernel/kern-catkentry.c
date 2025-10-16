/* kern-catkentry.c
 *
 * This file contains the CatK interrupt handler wrapper.
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

/* OS_CatKEntry() - call a Category K (Kernel) ISR.
 *
 * This function calls a category K (Kernel) ISR.
 *
 * The previous value of inKernel is saved, then inKernel is set
 * to 1.
 * Then the ISR function itself is called.
 * Finally, the saved value of inKernel is returned. The real inKernel
 * flag is left at 1 because we might need to reschedule in the exit
 * routine.
 *
 * Interrupts remain at the kernel lock level priority throughout. The run priority
 * is not used for category K interrupts.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_uint8_t OS_CatKEntry(os_isrid_t iid)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	const os_isr_t *isr;
	os_isrfunc_t f;
	os_uint8_t inKernel;

	isr = &OS_isrTableBase[iid];
	f = isr->func;

	inKernel = OS_GetKernelData()->inKernel;
	OS_SetIsrinKernel();

	(*f)();

	return inKernel;
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_catkentry_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
