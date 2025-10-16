/* Mk_k_syscall.c
 *
 * This file contains the MK_Syscall() function from the microkernel.
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
#include <private/Mk_core.h>
#include <private/Mk_syscall.h>
#include <private/Mk_panic.h>


/* MK_Syscall() - generic system call handler
 *
 * Preconditions:
 *	- caller's context has been saved - including system call index and parameters
 *	- processor mode is suitable for microkernel
 *	- memory protection is set up for microkernel
 *	- current stack is kernel stack
 *	- interrupts are locked (hard)
 *
 * !LINKSTO Microkernel.Function.MK_Syscall, 2
 * !doctype src
*/
void MK_Syscall(void)
{
	mk_parametertype_t syscallIndex;
	/* Deviation MISRAC2012-1 <+1> */
	mk_kernelcontrol_t *coreVars = MK_GetCoreVars();

	if ( coreVars->threadQueueHead == MK_NULL )
	{
		/* Paranoia!
		 * If there's no thread in the queue the current thread is invalid.
		*/
		MK_Panic(MK_panic_UnexpectedSystemCall);
	}
	else
	if ( coreVars->currentThread == coreVars->threadQueueHead )
	{
		/* Retrieve the system call index from the thread's context
		*/
		syscallIndex = MK_HwGetSyscallIndex(coreVars->currentThread->regs);

		/* Range check
		*/
		if ( syscallIndex < (mk_parametertype_t)MK_NSYSCALL )
		{
			/* Call the appropriate microkernel function.
			 * This may result in a change to the most eligible thread.
			*/
			(*MK_syscallTable[syscallIndex])(coreVars);
		}
		else
		{
			/* Call the unknown system call handler for out-of-range index.
			 * This may result in a change to the most eligible thread.
			*/
			MK_UnknownSyscall(coreVars);
		}

		/* Dispatch the highest-priority thread; the dispatcher never returns
		*/
		MK_Dispatch(coreVars);
	}
	else
	{
		/* Paranoia!
		 * If the current thread is not at the head of the queue something has been tinkering
		 * without dispatching.
		*/
		MK_Panic(MK_panic_CurrentThreadNotAtHeadOfQueue);
	}
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
