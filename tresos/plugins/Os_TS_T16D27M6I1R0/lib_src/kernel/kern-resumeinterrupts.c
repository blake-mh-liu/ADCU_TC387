/* kern-resumeinterrupts.c
 *
 * This file contains the OS_KernResumeInterrupts() function
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.5 (advisory)
 * A conversion should not be performed from pointer to void into pointer to
 * object.
 *
 * Reason:
 * Some architectures need to access hardware directly to control interrupts.
 * These accesses involve type casts, because hardware naturally has no notion
 * of C language types.
 *
 *
 * MISRAC2012-2) Deviated Rule: 11.6 (required)
 * A cast shall not be performed between pointer to void and an arithmetic type.
 *
 * Reason:
 * Some architectures need to access hardware directly to control interrupts.
 * These accesses involve type casts, because hardware naturally has no notion
 * of C language types.
 */
/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: StatementIsUnreachable
 *   statement not reached.
 *
 * Reason:
 *   These warnings depend on the OS configuration and library optimization.
 *   The statements can be reached, if "error handling for APIs returning void" is not excluded.
 *   See also OS_EXCLUDE_ERRORHANDLINGFORVOIDAPI.
 *
 * TOOLDIAG-2) Possible diagnostic: StatementIsUnreachable
 *   statement not reached.
 *
 * Reason:
 *   These warnings depend on the OS configuration and library optimization.
 *   This statement can be reached if there are Cat-2 ISRs.
*/

#define OS_SID OS_SID_ResumeInterrupts
#define OS_SIF OS_svc_ResumeInterrupts

#include <Os_kernel.h>

#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

/* Include definitions for tracing */
#include <Os_Trace.h>

#include <memmap/Os_mm_code_begin.h>

/*!
 * OS_KernResumeInterrupts()
 *
 * Implements the ResumeOSInterrupts(), ResumeAllInterrupts() and
 * EnableAllInterrupts() services.
 *
 * This function restores the interrupt state previously saved by
 * OS_KernSuspendInterrupts(). The appropriate nesting counter
 * is decremented, and if it reaches zero the corresponding old level
 * is restored.
 *
 * The type of interrupt locking being resumed is given by the locktype
 * parameter.
 *
 * See the description of OS_KernSuspendInterrupts() for a full
 * description of the nesting counter and old level scheme.
 *
 * Look! No Cross-core calls!
 * !LINKSTO Kernel.Autosar.Multicore.InterruptAPI.CoreLocal, 1
*/
OS_TOOL_FUNCTION_ATTRIB_PRE
void OS_KernResumeInterrupts(os_intlocktype_t locktype)
OS_TOOL_FUNCTION_ATTRIB_POST
{
	os_kerneldata_t * const kernel_data = OS_GetKernelData();
	os_taskdynamic_t *td = OS_NULL;
	os_oldlevel_t *olp = OS_NULL;		/* Pointer to Old level store */
	os_uint8_t *ncp = OS_NULL;			/* Pointer to nesting counter */
	os_intstatus_t is;
	os_prio_t *pPrioBeforeSuspend = OS_NULL;

	OS_PARAMETERACCESS_DECL

	OS_SAVE_PARAMETER_N(0,(os_paramtype_t)locktype);

	OS_TRACE_RESUMEINTERRUPTS_ENTRY(locktype);

	if ( kernel_data->inFunction == OS_INTASK )
	{
		/* Called from a task context:
		 * Here we manipulate the task's own interrupt management
		 * variables.
		 *
		 * !LINKSTO Kernel.API.InterruptHandling.ResumeOSInterrupts.Interrupts, 1
		 * !LINKSTO Kernel.API.InterruptHandling.ResumeOSInterrupts.Task, 1
		 * !LINKSTO Kernel.API.InterruptHandling.ResumeAllInterrupts.Interrupts, 1
		 * !LINKSTO Kernel.API.InterruptHandling.ResumeAllInterrupts.Task, 1
		 * !LINKSTO Kernel.API.InterruptHandling.EnableAllInterrupts.Interrupts, 1
		 * !LINKSTO Kernel.API.InterruptHandling.EnableAllInterrupts.Task, 1
		*/
		td = kernel_data->taskCurrent->dynamic;

		if ( locktype == OS_LOCKTYPE_OS )
		{
			/* Operation is a no-op if nested inside SuspendAllInterrupts() or DisableAllInterrupts()
			*/
			if ( td->nestSuspendAll == 0u )
			{
				olp = &td->oldSuspendOs;
				ncp = &td->nestSuspendOs;
				pPrioBeforeSuspend = &td->prioBeforeSuspendOs;
			}
		}
		else
		{
			olp = &td->oldSuspendAll;
			ncp = &td->nestSuspendAll;
		}
	}
	else
	if ( OS_IS_INCAT2( kernel_data->inFunction ) )
	{
		/* Called from Category 2 ISR:
		 * Here we maniplulate the global old level/nesting counter
		 * variables.
		 *
		 * !LINKSTO Kernel.API.InterruptHandling.ResumeOSInterrupts.Interrupts, 1
		 * !LINKSTO Kernel.API.InterruptHandling.ResumeOSInterrupts.ISRC2, 1
		 * !LINKSTO Kernel.API.InterruptHandling.ResumeAllInterrupts.Interrupts, 1
		 * !LINKSTO Kernel.API.InterruptHandling.ResumeAllInterrupts.ISRC1, 1
		 * !LINKSTO Kernel.API.InterruptHandling.ResumeAllInterrupts.Hook, 1
		 * !LINKSTO Kernel.API.InterruptHandling.EnableAllInterrupts.Interrupts, 1
		 * !LINKSTO Kernel.API.InterruptHandling.EnableAllInterrupts.ISRC1, 1
		 * !LINKSTO Kernel.API.InterruptHandling.EnableAllInterrupts.ISRC2, 1
		*/
		/* Possible diagnostic TOOLDIAG-2 <+1> */
		if ( locktype == OS_LOCKTYPE_OS )
		{
			/* Operation is a no-op if nested inside SuspendAllInterrupts() or DisableAllInterrupts()
			*/
			if ( kernel_data->nestSuspendAll == 0u )
			{
				olp = &kernel_data->oldSuspendOs;
				ncp = &kernel_data->nestSuspendOs;
			}
		}
		else
		{
			olp = &kernel_data->oldSuspendAll;
			ncp = &kernel_data->nestSuspendAll;
		}
	}
	else
	if ( OS_CallingContextCheck() )
	{
		/* In all other permitted contexts (Cat1 interrupt, hooks), category 2 interrupts
		 * are automatically blocked.
		 * So this function becomes a no-op.
		 *
		 * !LINKSTO Kernel.API.InterruptHandling.ResumeOSInterrupts.Interrupts, 1
		 * !LINKSTO Kernel.API.InterruptHandling.ResumeOSInterrupts.ISRC1, 1
		 *
		 * ResumeOSInterrupts() is a no-op if nested inside SuspendAllInterrupts() or
		 * DisableAllInterrupts()
		*/
		if ( locktype != OS_LOCKTYPE_OS )
		{
			olp = &kernel_data->oldSuspendAll;
			ncp = &kernel_data->nestSuspendAll;
		}
	}
	else
	{
		if ( OS_ErrorHandlingForVoidApi() )
		{
			/* Called from any other context ---> error
			*/
			/* can't propagate the return value of OS_ERROR -> ignore it */
			/* Possible diagnostic TOOLDIAG-1 <+1> */
			(void) OS_ERROR(OS_ERROR_WrongContext, OS_GET_PARAMETER_VAR());
		}
	}

	if ( ncp != OS_NULL )
	{
		/* This branch actually does the job ...
		*/
		is = OS_IntDisableMax();

		/* COVPT-1 */
		if ( (td != OS_NULL) && (td->state != OS_TS_RUNNING) )
		{
			/* Task has been killed, e.g. by overrunning execution budget.
			 * In this case we just return without doing anything
			*/
			OS_IntRestoreMax(is);
		}
		else
		if ( *ncp == 1u )
		{
			if ( kernel_data->inFunction == OS_INTASK )
			{
				OS_STOPTASKINTLOCKTIMING(kernel_data->taskCurrent, locktype);
				if (pPrioBeforeSuspend != OS_NULL)
				{
					OS_LowerCurrentTasksPriority(*pPrioBeforeSuspend);
					*pPrioBeforeSuspend = 0u;
				}
			}
			else
			if ( kernel_data->inFunction == OS_INCAT2 )
			{
				OS_STOPISRINTLOCKTIMING(kernel_data->isrCurrent, locktype);
			}
			else
			{
				/* MISRA */
			}

			/* OS_ResumeInterrupts is a macro that doesn't
			 * attempt to ensure that its parameters are only evaluated
			 * once. That's OK here because the parameters are simple
			 * variables, not expressions
			*/
			*ncp = 0u;

			/* Deviation MISRAC2012-1 <+1>, MISRAC2012-2 <+1> */
			OS_ResumeInterrupts(olp);

			/* We do not restore interrupts here because
			 * OS_ResumeInterrupts() has set the level correctly
			*/
			OS_IntRestoreHardLock(is);
		}
		else
		if ( (locktype != OS_LOCKTYPE_NONEST) && (*ncp != 0u) )
		{
			(*ncp)--;

			/* No need to restore here - already at the correct level
			*/
			OS_IntRestoreHardLock(is);
		}
		else
		{
			/* !LINKSTO Kernel.Autosar.ServiceErrors.Miscellaneous.EnableInterrupts, 1
			 * !LINKSTO Kernel.Feature.RuntimeChecks.CheckSuspendResumeNesting, 1
			 * !LINKSTO Kernel.Feature.RuntimeChecks, 1
			*/
			OS_IntRestoreMax(is);

			if ( OS_ErrorHandlingForVoidApi() )
			{
				/* can't propagate the return value of OS_ERROR -> ignore it */
				/* Possible diagnostic TOOLDIAG-1 <+1> */
				(void) OS_ERROR(OS_ERROR_NestingUnderflow, OS_GET_PARAMETER_VAR());
			}
		}
	}

	OS_TRACE_RESUMEINTERRUPTS_EXIT_P(locktype);
}

#include <memmap/Os_mm_code_end.h>


#else /* (!(OS_KERNEL_TYPE != OS_MICROKERNEL)) */
#include <Os_dummies.h>
const os_uint8_t OS_dummy_kern_resumeinterrupts_c = 0xeb;
#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
