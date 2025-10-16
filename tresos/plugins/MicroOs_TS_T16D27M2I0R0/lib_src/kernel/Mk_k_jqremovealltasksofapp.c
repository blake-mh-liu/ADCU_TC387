/* Mk_k_jqremovealltasksofapp.c
 *
 * This file contains the function MK_JqRemoveAllTasksOfApp().
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <private/Mk_jobqueue.h>
#include <private/Mk_task.h>

/* MK_JqRemoveAllTasksOfApp() removes all instances of tasks belonging to a given application from the job queue.
 *
 * Preconditions:
 *  - the jobqueue parameter refers to a (possibly empty) queue of tasks
 *
 * Postconditions:
 *	- queue contains no tasks belonging to the specified application
 *  - all other tasks that were previously in the queue remain in the queue in the same order
 *
 * !LINKSTO Microkernel.Function.MK_JqRemoveAllTasksOfApp, 1
 * !doctype src
*/
void MK_JqRemoveAllTasksOfApp(mk_jobqueue_t *jq, mk_objectid_t appId)
{
	mk_objquantity_t nJobs = jq->count;
	mk_objquantity_t i;
	mk_objquantity_t job;

	for ( i = 0; i < nJobs; i++ )
	{
		/* MK_JqRemove() cannot return MK_NOJOB here because we only operate on jobs that are present.
		*/
		job = MK_JqRemove(jq);

		if ( MK_taskCfg[job].threadCfg.applicationId != appId )
		{
			MK_JqAppend(jq, job);
		}
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
