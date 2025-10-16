/* Mk_u_libisschedulenecessary.c
 *
 * This file contains the MK_LibIsScheduleNecessary() function.
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
 *  The core variables may be stored in memory, to which access is hardware
 *  dependent. In this case, a pointer conversion is required to commit that
 *  memory to its intended purpose.
*/

#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <private/Mk_core.h>
#include <private/Mk_thread.h>
#include <private/Mk_lock.h>

/* MK_IsScheduleNecessary() returns MK_TRUE if there is a thread of higher
 * priority enqueued behind the current thread.
 * Otherwise it returns MK_FALSE.
 *
 * !LINKSTO      Microkernel.Function.IsScheduleNecessary, 2
 * !doctype      src
*/
mk_boolean_t MK_IsScheduleNecessary(void)
{
	mk_boolean_t result = MK_TRUE;
	mk_lock_t *lock;
	mk_threadprio_t lowPrio;
	/* Deviation MISRAC2012-1 <+1> */
	mk_kernelcontrol_t *coreVars = MK_GetCoreVarsFromThread();
	mk_thread_t *currThread = coreVars->currentThread;

	if ( currThread->next == MK_NULL )
	{
		/* No other threads in the queue. No point calling Schedule().
		*/
		result = MK_FALSE;
	}
	else
	{
		/* Calculate the priority that the thread has to drop to.
		 * As basis, use the queueing priority.
		 */
		lowPrio = currThread->queueingPriority;

		/* However, the priority will not drop lower than the highest lock taken, so
		 * walk the list of locks and adjust the priority to drop to.
		 */
		lock = currThread->lastLockTaken;
		while ( lock != MK_NULL )
		{
			if ( lock->cfg.ceilingPriority > lowPrio )
			{
				lowPrio = lock->cfg.ceilingPriority;
			}
			lock = lock->previousTaken;
		}

		if ( currThread->next->currentPriority > lowPrio )
		{
			/* The next thread has a higher priority than what the current thread will drop to,
			 * so Schedule() would cause a thread switch. Return TRUE (the default).
			*/
		}
		else
		{
			/* The next thread's priority is lower than (or the same as) what the current thread
			 * would drop to, so Schedule() wouldn't cause a thread switch. Return FALSE.
			*/
			result = MK_FALSE;
		}
	}

	return result;
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
