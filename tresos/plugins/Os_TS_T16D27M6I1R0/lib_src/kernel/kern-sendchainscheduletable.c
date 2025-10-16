/* kern-sendchainscheduletable.c
 *
 * This file contains the OS_SendChainScheduleTable() function.
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
 * OS_SendChainScheduleTable
 *
 * Sends the ChainScheduleTable() request to the core on which the schedule table 'sc' resides.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
os_errorresult_t OS_SendChainScheduleTable
(	os_scheduleid_t sc,			/* Currently-running schedule table */
	os_scheduleid_t sn,			/* Schedule table to chain */
	const os_schedule_t *scs	/* Ptr to sc structure */
)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_paramtype_t msgParam[OS_MAXPARAM];

	msgParam[0] = (os_paramtype_t)sc;
	msgParam[1] = (os_paramtype_t)sn;

	return OS_SendMessageWait(OS_GetScheduleTableCoreId(scs), OS_XC_OP_ChainScheduleTable, msgParam);
}

#include <memmap/Os_mm_code_end.h>

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_sendchainscheduletable_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
