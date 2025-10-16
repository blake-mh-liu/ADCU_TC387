/* kern-sendclearpendinginterrupt.c
 *
 * This file contains the OS_SendClearPendingInterrupt() function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_kernel.h>

#if ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))

#include <Os_messagequeue.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_SendClearPendingInterrupt
 *
 * Sends the request to clear the pending interrupt source of ISR 'i' to the core on which that ISR resides.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_errorresult_t OS_SendClearPendingInterrupt(os_isrid_t i, const os_isr_t *isr)
OS_TOOL_FUNCTION_ATTRIB_POST
{
    os_paramtype_t msgParam[OS_MAXPARAM];

    msgParam[0] = (os_paramtype_t)i;
	/* !LINKSTO Kernel.Autosar.Multicore.ClearPendingInterrupt.Synchronous, 1
	*/
    return OS_SendMessageWait(OS_GetIsrCoreId(isr), OS_XC_OP_ClearPendingInterrupt, msgParam);
}

#include <memmap/Os_mm_code_end.h>

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_sendclearpendinginterrupt_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
