/* Mk_u_libtrytogetspinlock.c
 *
 * This file contains the TryToGetSpinlock() function.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_api.h>
#include <public/Mk_error.h>
#include <public/Mk_autosar.h>

/* TryToGetSpinlock()
 *
 * This function takes a spinlock using the MK_UsrAcquireLock system call.
 * If the system call returns MK_E_TRYAGAIN it returns E_OK and sets the output
 * variable to TRYTOGETSPINLOCK_NOSUCCESS.
 *
 * !LINKSTO Microkernel.Function.TryToGetSpinlock, 2
 * !doctype src
*/
StatusType TryToGetSpinlock(SpinlockIdType lockId, TryToGetSpinlockType *out)
{
	StatusType errorCode;

	errorCode = (StatusType)MK_UsrAcquireLock(lockId);

	if ( errorCode == E_OK )
	{
		/* Success; set the *out variable accordingly.
		*/
		*out = TRYTOGETSPINLOCK_SUCCESS;
	}
	else
	if ( errorCode == (StatusType)MK_E_TRYAGAIN )
	{
		/* Lock is occupied; set the *out variable accordingly, and return E_OK.
		*/
		*out = TRYTOGETSPINLOCK_NOSUCCESS;
		errorCode = E_OK;
	}
	else
	{
		/* MISRA branch. If the status code indicates a real error, we return it.
		 * The AUTOSAR specification requires that the *out variable shall be "undefined" in this case,
		 * but we shall leave it untouched rather than generating a random number.
		*/
	}

	return errorCode;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
