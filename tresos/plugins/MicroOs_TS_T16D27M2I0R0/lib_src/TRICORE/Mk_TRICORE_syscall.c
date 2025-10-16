/* Mk_TRICORE_syscall.c
 *
 * This file contains the function MK_TricoreSyscall()
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

#include <public/Mk_basic_types.h>
#include <private/TRICORE/Mk_TRICORE_exceptionhandling.h>
#include <private/Mk_syscall.h>

#include <private/TRICORE/Mk_TRICORE_exceptionfunctions.h>

/* MK_TricoreSyscall()
 *
 * This function is entered via a jump instruction from the System Call exception vector.
 * The vector provides the thread's PCXI value and the system-call index as parameters.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_TricoreSyscall, 1,
 * !        Microkernel.TRICORE.Entry, 1
 * !doctype src
*/
void MK_TricoreSyscall(mk_uint32_t pcxiValue, mk_uint32_t d15Value)
{
	/* Deviation MISRAC2012-1 <+1> */
	mk_kernelcontrol_t *coreVars = MK_GetCoreVars();

	/* Doesn't return if exception is not "sane" */
	MK_ExceptionHandlerCommon(pcxiValue, d15Value, coreVars, MK_exc_Syscall, MK_FALSE);

	MK_Syscall();
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
