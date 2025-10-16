/* Mk_configuration_job.c
 *
 * This file contains the configuration for job queues.
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_jobqueue.h>
#include <Mk_Cfg.h>

/* !LINKSTO Microkernel.Data.Configuration, 1
 * !doctype src
*/

/* Job queues
 *
 * Each job queue configuration is copied to its thread state structure at startup. It is done
 * this way because only a subset of the threads has a job queue.
 *
 * Note: if MK_jobQueueCfg[x] or MK_jobQueue[x] is NULL, MK_nJobQueues[x] is <= 0. This fact is used in the code.
*/
mk_objquantity_t const MK_nJobQueues[MK_MAXCORES] =
{
	MK_COREARRAY(MK_CFG_C0_NJOBQUEUES,
				 MK_CFG_C1_NJOBQUEUES,
				 MK_CFG_C2_NJOBQUEUES,
				 MK_CFG_C3_NJOBQUEUES,
				 MK_CFG_C4_NJOBQUEUES,
				 MK_CFG_C5_NJOBQUEUES,
				 MK_CFG_C6_NJOBQUEUES,
				 MK_CFG_C7_NJOBQUEUES)
};

mk_jobqueue_t * const MK_jobQueue[MK_MAXCORES] =
{
	MK_COREARRAY(MK_CFG_C0_JOBQUEUE,
				 MK_CFG_C1_JOBQUEUE,
				 MK_CFG_C2_JOBQUEUE,
				 MK_CFG_C3_JOBQUEUE,
				 MK_CFG_C4_JOBQUEUE,
				 MK_CFG_C5_JOBQUEUE,
				 MK_CFG_C6_JOBQUEUE,
				 MK_CFG_C7_JOBQUEUE)
};

const mk_jobqueuecfg_t * const MK_jobQueueCfg[MK_MAXCORES] =
{
	MK_COREARRAY(MK_CFG_C0_JOBQUEUECFG,
				 MK_CFG_C1_JOBQUEUECFG,
				 MK_CFG_C2_JOBQUEUECFG,
				 MK_CFG_C3_JOBQUEUECFG,
				 MK_CFG_C4_JOBQUEUECFG,
				 MK_CFG_C5_JOBQUEUECFG,
				 MK_CFG_C6_JOBQUEUECFG,
				 MK_CFG_C7_JOBQUEUECFG)
};

const mk_objquantity_t MK_jobQueueBufLen[MK_MAXCORES] =
{
	MK_COREARRAY(MK_CFG_C0_JOBQUEUEBUFLEN,
				 MK_CFG_C1_JOBQUEUEBUFLEN,
				 MK_CFG_C2_JOBQUEUEBUFLEN,
				 MK_CFG_C3_JOBQUEUEBUFLEN,
				 MK_CFG_C4_JOBQUEUEBUFLEN,
				 MK_CFG_C5_JOBQUEUEBUFLEN,
				 MK_CFG_C6_JOBQUEUEBUFLEN,
				 MK_CFG_C7_JOBQUEUEBUFLEN)
};

mk_jobelement_t * const MK_jobQueueBuffer[MK_MAXCORES] =
{
	MK_COREARRAY(MK_CFG_C0_JOBQUEUEBUFFER,
				 MK_CFG_C1_JOBQUEUEBUFFER,
				 MK_CFG_C2_JOBQUEUEBUFFER,
				 MK_CFG_C3_JOBQUEUEBUFFER,
				 MK_CFG_C4_JOBQUEUEBUFFER,
				 MK_CFG_C5_JOBQUEUEBUFFER,
				 MK_CFG_C6_JOBQUEUEBUFFER,
				 MK_CFG_C7_JOBQUEUEBUFFER)
};

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
