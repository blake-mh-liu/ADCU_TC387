/* Mk_k_reportdroppedxcorerequest.c
 *
 * This file contains the function MK_ReportDroppedXcoreRequest().
 *
 * (c) Elektrobit Automotive GmbH
*/

#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_message.h>
#include <private/Mk_tool.h>

/* MK_ReportDroppedXcoreRequest() - handle a dropped asynchronous cross-core request.
 *
 * This function counts asynchronous cross-core counter subsystem calls which are dropped, when the job queue is full.
 *
 * !LINKSTO Microkernel.Function.MK_ReportDroppedXcoreRequest, 2
 * !doctype src
*/
void MK_ReportDroppedXcoreRequest(mk_kernelcontrol_t *coreVars)
{
	/* In any case, increment the dropped jobs counter up to its maximum value.
	*/
	if ( (coreVars->nDroppedJobs + 1u) != 0u )
	{
		coreVars->nDroppedJobs++;
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
