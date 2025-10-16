/* kern-releasespinlockscurcore.c
 *
 * This file contains OS_ReleaseSpinlocksCurCore - a helper for the OS_Shutdown function.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: GNUStatementExpressionExtension
 *   Use of GNU statement expression extension.
 *
 * Reason: This function is implemented by using a function like macro that
 * makes use of the GNU statement expression extension for better maintainability.
*/
#include <Os_kernel.h>

#if ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))

#include <Os_spinlock.h>

#include <memmap/Os_mm_code_begin.h>

/* Helper function: Releases all spinlocks held by the current core.
 * Preconditions: the caller has already locked interrupts.
 *
 * !LINKSTO Kernel.Autosar.Multicore.ShutdownOS.ReleaseSpinlock, 1
 */

OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_ReleaseSpinlocksCurCore(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_autosarspinlockid_t i;
	/* Possible diagnostic TOOLDIAG-1 <+1> */
	os_coreid_t const myCoreId = OS_GetMyCoreId();

	for (i = 0; i < OS_nAutosarSpinlocks; i++)
	{
		os_autosarspinlockdyn_t * const dyn = OS_autosarSpinlockTableBase[i].dynamic;

		if (dyn->ownerCore == myCoreId)
		{
			dyn->ownerCore = OS_CORE_ID_INVALID;
			dyn->ownerType = OS_OBJ_NONE;
			dyn->ownerId = OS_NULLOBJECT;
			dyn->predecessor = OS_NULLOBJECT;

			OS_CacheFlush(dyn, sizeof(*dyn));
		}
	}
}

#include <memmap/Os_mm_code_end.h>

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_releasespinlockscurcore_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
