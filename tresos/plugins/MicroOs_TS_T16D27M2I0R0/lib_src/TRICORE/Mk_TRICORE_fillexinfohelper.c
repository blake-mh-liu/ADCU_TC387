/* Mk_TRICORE_fillexinfohelper.c
 *
 * This file contains a helper function to read (and clear if needed) the
 * registers DSTR, DEADD, PSTR, DATR, PIETR, PIEAR, DIETR, and DIEAR to the given
 * exceptionInfo structure.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 11.6 (required)
 *  A cast shall not be performed between pointer to void and an arithmetic type.
 *
 * Reason:
 *  The type conversion is required, because the raw value of the pointer is
 *  obtained from hardware, which has no notion of C language types.
 *
 *
 * MISRAC2012-2) Deviated Rule: 10.5 (advisory)
 * The value of an expression should not be cast to an inappropriate essential type.
 *
 * Reason:
 * The hardware specific enum mk_exceptiontype_e is constructed in a way, that its value
 * is assembled of the respective hw_exceptionclass_e and mk_exceptiontin_t values.
 * To construct a mk_exceptiontype_e the MK_ExceptionClassTinToTypeBits macro is used,
 * which performs the calculation using mk_uint32_t.
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_COMPL_010:HIS_CALLS]
 *  The code shall adhere to the [HISSRCMETRIC] Metrics.
 *
 * Reason:
 *  MK_TricoreFillExInfoHelper contains a lot of calls to MK_MFCR and MK_MTCR.
 *  These functions are necessary to read and write special function registers.
 *  There is no reason why this should affect maintainability or comprehensibility
 *  of the code. The complexity of the behaviour that is encapsulated in these
 *  function calls is comparable to the complexity of
 *  reading from and writing to memory-mapped registers.
*/
/* Deviation DCG-1 <*> */

#include <private/TRICORE/Mk_TRICORE_core.h>
#include <public/TRICORE/Mk_TRICORE_exceptioninfo.h>
#include <private/TRICORE/Mk_TRICORE_compiler.h>
#include <private/TRICORE/Mk_TRICORE_exceptionhandling.h>

/* MK_TricoreFillExInfoHelper
 *
 * This function copies various auxiliary exception information registers to
 * the exception info structure referenced by the passed pointer.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_TricoreFillExInfoHelper, 1
 * !doctype src
*/
void MK_TricoreFillExInfoHelper(
	mk_hwexceptioninfo_t *exinf,
	mk_exceptionclass_t xClass,
	mk_exceptiontin_t xTin,
	mk_lowerctx_t *lowerCtx,
	mk_upperctx_t *upperCtx)
{
	mk_uint32_t typeBits;

	/* Store arguments. */
	exinf->excClass = xClass;
	exinf->excTin = xTin;
	typeBits = MK_ExceptionClassTinToTypeBits(xClass, xTin);
	/* Deviation MISRAC2012-2 <+1> */
	exinf->type = (mk_exceptiontype_t) typeBits;

	/* Copy exception info. */
	exinf->dstr = MK_MFCR(MK_DSTR);
	exinf->datr = MK_MFCR(MK_DATR);
	/* Deviation MISRAC2012-1 <+1> */
	exinf->deadd = (void *) MK_MFCR(MK_DEADD);
	exinf->pstr = MK_MFCR(MK_PSTR);
	exinf->dietr = MK_MFCR(MK_DIETR);
	/* Deviation MISRAC2012-1 <+1> */
	exinf->diear = (void *) MK_MFCR(MK_DIEAR);
	exinf->pietr = MK_MFCR(MK_PIETR);
	/* Deviation MISRAC2012-1 <+1> */
	exinf->piear = (void *) MK_MFCR(MK_PIEAR);

	/* clear DSTR, DATR, PSTR, DIETR and PIETR */
	MK_MTCR(MK_DSTR, 0);
	MK_MTCR(MK_DATR, 0);
	MK_MTCR(MK_PSTR, 0);
	MK_MTCR(MK_DIETR, 0);
	MK_MTCR(MK_PIETR, 0);
	/* Note: MK_MTCR includes an isync, therefore, there's no need to explicitly add one here. */

	/* context information */
	exinf->lowerCtx = lowerCtx;
	exinf->upperCtx = upperCtx;
}

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
