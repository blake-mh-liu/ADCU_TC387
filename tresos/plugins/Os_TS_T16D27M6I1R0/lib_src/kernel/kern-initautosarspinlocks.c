/* kern-initspinlocks.c
 *
 * This file contains the function OS_InitSpinlocks().
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

/*!
 * OS_InitAutosarSpinlocks()
 *
 * Initializes the AUTOSAR spinlocks.
 *
 * Notes:
 *  - internal locks must be initialized first.
 *  - this function does not lock the spinlock table, but it forces a synchronization afterwards to prevent
 *    other cores from using the locks before they are initialized.
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_InitAutosarSpinlocks(void)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_autosarspinlockid_t i;

	/* Locks are only initialized on the init-core. No need to disable interrupts here.
	 * The other cores don't have to do anything special, because they invalidate their
	 * caches anyway as soon as they use AUTOSAR spinlocks.
	*/
	/* Possible diagnostic TOOLDIAG-1 <+1> */
	if (OS_GetMyCoreId() == (os_coreid_t)OS_INITCORE)
	{
		for (i = 0; i < OS_nAutosarSpinlocks; i++)
		{
			os_autosarspinlockdyn_t * const dyn = OS_autosarSpinlockTableBase[i].dynamic;

			dyn->ownerCore = OS_CORE_ID_INVALID;
			dyn->ownerType = OS_OBJ_NONE;
			dyn->ownerId = OS_NULLOBJECT;
			dyn->predecessor = OS_NULLOBJECT;

			OS_CacheFlush(dyn, sizeof(*dyn));
		}
	}

	/* All cores must wait until the locks are initialized.
	*/
	OS_SyncHere();
}

#else /* (!((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1))) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_initautosarspinlocks_c = 0xeb;
#endif /* ((OS_KERNEL_TYPE != OS_MICROKERNEL) && (OS_N_CORES != 1)) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
