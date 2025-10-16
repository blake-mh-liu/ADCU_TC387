/* Mk_k_cleartasks.c
 *
 * This file contains the MK_ClearTasks function.
 *
 * This function is used during shutdown to clear the state of all tasks on the specified core.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_thread.h>
#include <private/Mk_task.h>

/*
 * MK_ClearTasks() clears task state (including thread state)
 *
 * !LINKSTO Microkernel.Function.MK_ClearTasks, 1
 * !doctype src
*/
void MK_ClearTasks(mk_objectid_t coreIndex)
{
	mk_objectid_t t;

	/* Look at all tasks.
	*/
	for ( t = 0; t < MK_nTasks; t++ )
	{
		/* Only clear down tasks on the specified (calling) core.
		*/
		if ( MK_taskCfg[t].threadCfg.coreIndex == coreIndex )
		{
			/* Clear the activation counter.
			*/
			MK_taskCfg[t].dynamic->activationCount = 0;

			/* Clear the event status for extended tasks.
			*/
			if ( MK_taskCfg[t].eventStatus != MK_NULL )
			{
				MK_taskCfg[t].eventStatus->pendingEvents = 0u;
				MK_taskCfg[t].eventStatus->awaitedEvents = 0u;
				MK_taskCfg[t].eventStatus->waitingState = MK_NO_WAIT;
			}

			/* Clear the associated thread. Shared threads will get cleared more than once - it's harmless.
			*/
			MK_ClearThread(MK_taskCfg[t].thread);
		}
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
