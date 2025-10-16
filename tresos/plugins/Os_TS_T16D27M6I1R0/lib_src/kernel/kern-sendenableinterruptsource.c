/* kern-sendenableinterruptsource.c
 *
 * This file contains the OS_SendEnableInterruptSource() function.
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
 * Boolean type value needs to be stored in fixed length type for cross core messaging.
*/

#include <Os_kernel.h>

#if ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))

#include <Os_messagequeue.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_SendEnableInterruptSource
 *
 * Sends the EnableInterruptSource() request to the core on which the ISR 'i' resides.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_errorresult_t OS_SendEnableInterruptSource(os_isrid_t i, const os_isr_t *isr, os_boolean_t clearPending)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_paramtype_t msgParam[OS_MAXPARAM];

	msgParam[0] = (os_paramtype_t)i;
	/* Deviation MISRAC2012-1 <+1> */
	msgParam[1] = (os_paramtype_t)clearPending;
	/* !LINKSTO Kernel.Autosar.Multicore.EnableInterruptSource.Synchronous, 1
	*/
	return OS_SendMessageWait(OS_GetIsrCoreId(isr), OS_XC_OP_EnableInterruptSource, msgParam);
}

#include <memmap/Os_mm_code_end.h>

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_sendenableinterruptsource_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
