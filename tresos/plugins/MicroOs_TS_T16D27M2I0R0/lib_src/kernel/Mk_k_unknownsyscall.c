/* Mk_k_unknownsyscall.c
 *
 * This file contains the function MK_UnknownSyscall().
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_core.h>
#include <private/Mk_syscall.h>
#include <private/Mk_thread.h>
#include <private/Mk_errorhandling.h>

/* MK_UnknownSyscall() - handle an unimplemented or unconfigured system call
 *
 * This function is used to fill unused entries in the system call table - for example, to minimize the
 * "dead code" caused by unused features.
 * It is also called when the system call index is out of range.
 *
 * !LINKSTO Microkernel.Function.MK_UnknownSyscall, 2
 * !doctype src
*/
void MK_UnknownSyscall(mk_kernelcontrol_t *coreVars)
{
	MK_HwSetReturnValue1(coreVars->currentThread->regs,
					MK_InternReportError(coreVars, MK_sid_UnknownService, MK_eid_OsUnknownSystemCall,
																			coreVars->currentThread, MK_NULL));
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
