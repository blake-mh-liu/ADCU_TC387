/* Mk_k_jqinit.c
 *
 * This file contains the MK_JqInit() function from the microkernel.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_jobqueue.h>
#include <private/Mk_thread.h>
#include <private/Mk_panic.h>

/* MK_JqInit() - associates the configured job queues with their respective threads
 *
 * The MK_JqInit() function is called by MK_StartKernel() at system startup. It loops over
 * all configured job queues for the core on which it runs and assigns each job queue to
 * the associated thread. Buffer space for the job queue is allocated from the job queue buffer
 * for the core.
 *
 * !LINKSTO Microkernel.Function.MK_JqInit, 1
 * !doctype src
 */
void MK_JqInit(mk_kernelcontrol_t *coreVars)
{
	mk_objquantity_t nJq = MK_nJobQueues[coreVars->coreIndex];				/* No. of queues in my array */
	const mk_jobqueuecfg_t *jqCfg = MK_jobQueueCfg[coreVars->coreIndex];	/* Base of my config. array */
	mk_jobqueue_t *jobQueue = MK_jobQueue[coreVars->coreIndex];				/* Base of my variable array. */

	mk_jobelement_t *buffer = MK_jobQueueBuffer[coreVars->coreIndex];		/* Base of my buffer space. */
	mk_objquantity_t nextFree = 0;											/* Next free buffer position. */
	mk_objquantity_t bufferLeft = MK_jobQueueBufLen[coreVars->coreIndex];	/* How much space is left. */

	mk_objectid_t i;
	mk_objquantity_t len;
	mk_objquantity_t size;
	mk_objquantity_t nelem;

	for ( i = 0; i < nJq; i++ )
	{
		/* Is there enough buffer space left?
		*/
		len = jqCfg[i].length;
		size = jqCfg[i].size;

		nelem = len * size;

		if ( nelem <= bufferLeft )
		{
			/* Allocate space in the job buffer.
			*/
			jobQueue[i].base = &buffer[nextFree];
			jobQueue[i].limit = &buffer[nextFree + (nelem - size)];
			nextFree += nelem;
			bufferLeft -= nelem;

			/* Set the job queue's constant fields.
			*/
			jobQueue[i].length = len;
			jobQueue[i].size = size;

			/* Initialize the job queue variables.
			*/
			jobQueue[i].next = jobQueue[i].base;
			jobQueue[i].nextFree = jobQueue[i].base;
			jobQueue[i].count = 0u;

			/* Associate the thread with the job queue.
			 * Threads with no job queue can only run a single object at a time.
			*/
			jqCfg[i].thread->jobQueue = &jobQueue[i];
		}
		else
		{
			MK_StartupPanic(MK_panic_InsufficientSpaceInJobQueueBuffer);
		}
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
