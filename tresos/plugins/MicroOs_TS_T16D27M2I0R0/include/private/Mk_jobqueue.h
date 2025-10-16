/* Mk_jobqueue.h - job queue configuration and handling
 *
 * This file contains definitions for configuration and handling of job queues.
 *
 * A job queue is an array of jobs along with supporting variables to maintain a FIFO ring-buffer in the array.
 *
 * The jobs in any individual queue have the same size, but the size of the jobs is configurable, in units of
 * the basic mk_jobelement_t type.
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef MK_JOBQUEUE_H
#define MK_JOBQUEUE_H

#include <public/Mk_basic_types.h>
#include <public/Mk_public_types.h>
#include <private/Mk_types_forward.h>

#ifndef MK_ASM

typedef mk_objectid_t mk_jobid_t;
typedef mk_parametertype_t mk_jobelement_t;

#define	MK_NOJOB	(-1)	/* Return from MK_JqRemove() if the queue is empty */

struct mk_jobqueuecfg_s
{
	mk_thread_t *thread;		/* Thread that's associated with this job queue. */
	mk_objquantity_t length;	/* Length of the queue (max. no of jobs that can be queued) */
	mk_objquantity_t size;		/* Size of the job (no. of mk_jobelement_t in each job). */
};

struct mk_jobqueue_s
{
	mk_jobelement_t *base;		/* Base of the buffer for this queue (address of first job). */
	mk_jobelement_t *limit;		/* Limit of the buffer for this queue (address of last job). */
	mk_jobelement_t *next;		/* The next job in the queue. */
	mk_jobelement_t *nextFree;	/* The next free slot in the queue. */
	mk_objquantity_t count;		/* No. of jobs currently in the queue. */
	mk_objquantity_t length;	/* Number of jobs in the buffer. */
	mk_objquantity_t size;		/* Size of each job (no. of jobelements). */
};

/* MK_JOBQUEUECFG() - initialization macro for a job-queue config structure
 *
 * This macro should be used wherever a jobqueuecfg is initialized, to permit changes
 * in the structure to be easily identified and fixed, and to permit
 * optimizations of the structure if necessary.
*/
#define MK_JOBQUEUECFG(thr, len, size) \
{			\
	(thr),	\
	(len),	\
	(size)	\
}

/* A "bigjob" is defined by an array of jobelements.
 * The array can be of different sizes depending on the number of parameters.
 * These macros define the standard indexes that are the same for all job types.
*/
#define MK_BJ_ID		0			/* Function id */
#define MK_BJ_TYPE		1			/* Function type */
#define MK_BJ_PCOOKIE	2			/* Parent thread */
#define MK_BJ_P1		3			/* Parameter */
#define MK_BJ_P2		4			/* Parameter */
#define MK_BJ_P3		5			/* Parameter */
#define MK_BJ_PCORE		6			/* Parent thread's core for synchronous counter subsystem jobs */

#define MK_BJ_MAX		7			/* Biggest job - must be verified against all real job types */

extern const mk_objquantity_t MK_nJobQueues[MK_MAXCORES];
extern const mk_jobqueuecfg_t * const MK_jobQueueCfg[MK_MAXCORES];
extern mk_jobqueue_t * const MK_jobQueue[MK_MAXCORES];
extern const mk_objquantity_t MK_jobQueueBufLen[MK_MAXCORES];
extern mk_jobelement_t * const MK_jobQueueBuffer[MK_MAXCORES];

/* Functions for simple job queues (for jobs of size 1).
*/
mk_jobid_t MK_JqRemove(mk_jobqueue_t *);
void MK_JqAppend(mk_jobqueue_t *, mk_jobid_t);
void MK_JqRemoveAllTasksOfApp(mk_jobqueue_t *, mk_objectid_t);

/* Functions for bigjob queues (jobs of size > 1).
*/
mk_objquantity_t MK_BjqRemove(mk_jobqueue_t *, mk_jobelement_t *);
mk_boolean_t MK_BjqAppend(mk_jobqueue_t *, const mk_jobelement_t *, mk_objquantity_t);

void MK_JqInit(mk_kernelcontrol_t *);

#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
