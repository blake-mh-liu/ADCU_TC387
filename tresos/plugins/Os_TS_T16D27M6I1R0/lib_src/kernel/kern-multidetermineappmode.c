/* kern-multidetermineappmode.c
 *
 * This file contains the OS_MultiDetermineAppMode function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#include <Os_kernel.h>

#if ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))

#include <Os_tool.h>

#include <Os_spinlock.h>
#include <Os_panic.h>

#include <memmap/Os_mm_code_begin.h>

static void OS_UpdateAppMode(os_appmodeid_t);
static void OS_CheckAppMode(void);

/*!
 * OS_UpdateAppMode
 *
 * Updates the global OS_appMode variable with the given 'mode'. This is done as follows:
 * - If 'mode' is OS_NULLAPPMODE, the current value in OS_appMode is not changed.
 * - If 'mode' is not OS_NULLAPPMODE, OS_appMode isn't either, but both differ, then
 *   OS_INCONSISTENT_APPMODE is written to OS_appMode to indicate failure.
 * - Otherwise, 'mode' is written to OS_appMode.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
static void OS_UpdateAppMode(os_appmodeid_t mode)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	if (mode != OS_NULLAPPMODE)
	{
		os_appmodeid_t volatile * const vpAppMode = &OS_appMode;
		os_intstatus_t const is = OS_TakeInternalLock(OS_APPMODE_LOCKID);
		{
			os_appmodeid_t currentMode;

			OS_CacheInvalidate(vpAppMode, sizeof(os_appmodeid_t));
			currentMode = *vpAppMode;

			if (currentMode != OS_NULLAPPMODE)
			{
				if ((currentMode != OS_INCONSISTENT_APPMODE) && (currentMode != mode))
				{
					*vpAppMode = OS_INCONSISTENT_APPMODE;
					OS_CacheFlush(vpAppMode, sizeof(os_appmodeid_t));
				}
			}
			else
			{
				*vpAppMode = mode;
				OS_CacheFlush(vpAppMode, sizeof(os_appmodeid_t));
			}
		}
		OS_DropInternalLock(OS_APPMODE_LOCKID, is);
	}
}

/*!
 * OS_CheckAppMode
 *
 * Checks, that the application modes passed to StartOS() are consistent.
 * When this is not the case, an endless loop is entered.
 * At least one call of StartOS() must provide a different value than OS_NULLAPPMODE
 * (same as DONOTCARE).
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
static void OS_CheckAppMode(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_appmodeid_t currentMode;
	os_appmodeid_t volatile * const vpAppMode = &OS_appMode;

	OS_CacheInvalidate(vpAppMode, sizeof(os_appmodeid_t));
	currentMode = *vpAppMode;

	if ((currentMode == OS_NULLAPPMODE) || (currentMode == OS_INCONSISTENT_APPMODE))
	{
		(void)OS_PANIC(OS_PANIC_InconsistentAppModes);
		OS_ENDLESSLOOP();	/* Just to be absolutely sure. */
	}
}


/*!
 * OS_MultiDetermineAppMode
 *
 * Determines the application mode in a multi-core system during startup.
 *
 * !LINKSTO Kernel.Autosar.Multicore.StartOS.DetermineAppMode, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_MultiDetermineAppMode(os_appmodeid_t mode)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	OS_UpdateAppMode(mode);
	/* wait until all cores had a chance to update OS_appMode */
	OS_SyncHere();
	/* from here on, OS_appMode must be treated as read-only */
	OS_CheckAppMode();
}

#include <memmap/Os_mm_code_end.h>

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_multidetermineappmode_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
