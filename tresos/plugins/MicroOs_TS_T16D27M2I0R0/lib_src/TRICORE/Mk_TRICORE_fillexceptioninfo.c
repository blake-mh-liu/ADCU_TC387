/* Mk_TRICORE_fillexceptioninfo.c
 *
 * This file contains the function Mk_FillExceptionInfo()
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_exceptionhandling.h>
#include <private/Mk_thread.h>
#include <private/Mk_core.h>

/* Mk_FillExceptionInfo()
 *
 * This function is called from the exception handlers. It fills the exception info structure
 * with the contents of registers that might be useful for diagnostics. In particular, registers
 * that are not accessible by threads running in user mode are copied.
 *
 * The function takes three parameters:
 * - the pointer to the core variables
 * - the exception class (the vector number)
 * - the trap identification number TIN (from d15)
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_FillExceptionInfo, 5
 * !doctype src
*/
void MK_FillExceptionInfo(mk_kernelcontrol_t *coreVars, mk_exceptionclass_t xClass, mk_exceptiontin_t xTin)
{
	/* Read and clear (where necessary) the exception information and address registers.
	 * We don't fill the context information. Thread contexts can be inspected using protectionInfo.
	*/
	MK_TricoreFillExInfoHelper(MK_exceptionInfo[coreVars->coreIndex], xClass, xTin, MK_NULL, MK_NULL);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
