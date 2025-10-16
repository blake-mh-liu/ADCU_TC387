/* mka-getactiveapplicationmode.c
 *
 * This file contains the GetActiveApplicationMode function
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE == OS_MICROKERNEL)

#include <public/Mk_autosar.h>
#include <Os_api_microkernel.h>

/*!
 * GetActiveApplicationMode
 *
 * Returns the current "application mode" (startup mode)
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
AppModeType GetActiveApplicationMode(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	/* COVPT-1 */
	return OS_GetAppMode();
}

#else /* (!(OS_KERNEL_TYPE == OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_mka_getactiveapplicationmode_c = 0xeb;
#endif /* (OS_KERNEL_TYPE == OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
