/* Ioc_u_interlock_spinlock.c
 *
 * This file contains an cross-core lock implementation using user-mode spinlocks,
 * without the need to trap into kernel mode.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.5 (advisory)
 *  A conversion should not be performed from pointer to void into pointer to
 *  object.
 *
 * Reason:
 *  The parameter types of the spinlock functions are mandated by the design.
*/

#include <public/Ioc_basic_types.h>
#include <private/Ioc_lockinterface.h>
#include <private/Ioc_core.h>

/*
 * !LINKSTO IOC.Function.IOC_Spinlock_Lock, 1
*/
ioc_return_t IOC_Spinlock_Lock(volatile void *spinlock_ref)
{
	ioc_return_t ret = IOC_E_TRYAGAIN;

	/* Deviation MISRAC2012-1 <+1> */
	if (IOC_HwTrySpinlock((volatile ioc_uint32_t *)spinlock_ref))
	{
		ret = IOC_E_OK;
	}
	return ret;
}

/*
 * !LINKSTO IOC.Function.IOC_Spinlock_Unlock, 1
*/
ioc_return_t IOC_Spinlock_Unlock(volatile void *spinlock_ref)
{
	/* Deviation MISRAC2012-1 <+1> */
	IOC_HwDropSpinlock((volatile ioc_uint32_t *)spinlock_ref);
	return IOC_E_OK;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
