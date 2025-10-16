/* Mk_u_libgetspinlock.c
 *
 * This file contains the GetSpinlock() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_api.h>
#include <public/Mk_error.h>
#include <public/Mk_autosar.h>

/* GetSpinlock()
 *
 * This function takes a spinlock using the MK_UsrAcquireLock system call.
 * If the system call returns MK_E_TRYAGAIN it tries again.
 *
 * !LINKSTO Microkernel.Function.GetSpinlock, 2
 * !doctype src
*/
StatusType GetSpinlock(SpinlockIdType lockId)
{
	StatusType errorCode;

	do
	{
		errorCode = (StatusType)MK_UsrAcquireLock(lockId);
	} while ( errorCode == (StatusType)MK_E_TRYAGAIN );

	return errorCode;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
