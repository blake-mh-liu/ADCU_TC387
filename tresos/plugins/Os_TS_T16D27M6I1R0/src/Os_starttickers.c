/* Os_starttickers.c
 *
 * This file contains the function OS_StartTickers
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
#include <board.h>


/*!
 * OS_StartTickers
 *
 * This function starts all configured software-counter tickers.
 *
*/
#include <memmap/Os_mm_code_begin.h>

OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_StartTickers(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
#if OS_NINTERNALTICKERS != 0
	/* COVPT-1 */
	OS_STARTINTERNALTICKERS();
#endif
}

#include <memmap/Os_mm_code_end.h>

#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_Os_starttickers_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
