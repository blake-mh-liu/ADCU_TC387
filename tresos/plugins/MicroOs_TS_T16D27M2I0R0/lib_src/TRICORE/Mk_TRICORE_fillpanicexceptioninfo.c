/* Mk_TRICORE_fillpanicexceptioninfo.c
 *
 * This file contains the function Mk_FillPanicExceptionInfo()
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <private/Mk_exceptionhandling.h>
#include <private/Mk_thread.h>
#include <private/Mk_core.h>
#include <private/TRICORE/Mk_TRICORE_compiler.h>

/* Mk_FillPanicExceptionInfo()
 *
 * This function is called from the exception handlers which cause a panic.
 * It fills the panic exception info structure
 * with the contents of registers that might be useful for diagnostics. In particular, registers
 * that are not accessible by threads running in user mode are copied.
 *
 * The function takes the following parameters:
 * - the pointer to the core variables
 * - the exception class (the vector number)
 * - the trap identification number TIN (from d15)
 * - pointers to lower and upper context.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_FillPanicExceptionInfo, 1
 * !doctype src
*/
void MK_FillPanicExceptionInfo(
	mk_kernelcontrol_t *coreVars,
	mk_exceptionclass_t xClass,
	mk_exceptiontin_t xTin,
	mk_lowerctx_t *lowerCtx,
	mk_upperctx_t *upperCtx)
{
	mk_lowerctx_t *lowerCtxLocal = lowerCtx;
	mk_upperctx_t *upperCtxLocal = upperCtx;
	mk_panicexceptionctx_t *pecxt = MK_panicExceptionCtxs[coreVars->coreIndex];

	/* Depending on the current MK implementation, the kernel context that causes the exception
	 * either leaks or is freed.
	 * In both cases the safest option is to store the kernel context in a separate core-local variable,
	 * so it can be inspected later.
	*/
	MK_DSYNC();
	pecxt->lower = *lowerCtxLocal;
	pecxt->upper = *upperCtxLocal;
	lowerCtxLocal = &(pecxt->lower);
	upperCtxLocal = &(pecxt->upper);

	/* Read and clear (where necessary) the exception information and address registers
	*/
	MK_TricoreFillExInfoHelper(MK_panicExceptionInfo[coreVars->coreIndex], xClass, xTin, lowerCtxLocal, upperCtxLocal);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
