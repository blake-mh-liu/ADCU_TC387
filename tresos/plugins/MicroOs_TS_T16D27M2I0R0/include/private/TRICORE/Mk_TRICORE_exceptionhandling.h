/* Mk_TRICORE_exceptionhandling.h - Tricore exception handling
 *
 * This file contains the TRICORE-specific part of the definitions for
 * exception handling.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_TRICORE_EXCEPTIONHANDLING_H
#define MK_TRICORE_EXCEPTIONHANDLING_H

#include <public/Mk_public_types.h>
#include <public/Mk_exceptioninfo.h>
#include <private/Mk_core.h>

/* The function MK_ExceptionIsSanePrecise() is not required for TriCore processors, because
 * the TriCore family implements its own ExceptionIsSane-handling (as part of MK_ExceptionHandlerCommon())
 * We link to the requirement here to show that we considered it.
 *
 * !LINKSTO Microkernel.Function.MK_ExceptionIsSanePrecise, 2,
 * !        Microkernel.TRICORE.Except.IsSane.Mapping, 1
 * !doctype src
*/
#define MK_HWHASEXCEPTIONISSANE  1
#define MK_HWHASINKERNEL         0

/* Codes passed to MK_UnknownInterrupt() on occurrence of unhandled exception-interrupt.
 * These codes must be outside the range of the known interrupt sources, so they start at 10000
*/
#define MK_UNKINT_NMI	10001

/* Exception setup and common handling functions
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_ExceptionHandlerCommon, 6,
 * !        Microkernel.TRICORE.Function.MK_HwSetupExceptions, 1
 * !doctype src
*/
void MK_HwSetupExceptions(mk_uint32_t, mk_uint32_t, mk_uint32_t, mk_uint32_t);
void MK_ExceptionHandlerCommon(mk_uint32_t, mk_uint32_t, mk_kernelcontrol_t *, mk_exceptionclass_t, mk_boolean_t);
void MK_FillExceptionInfo(mk_kernelcontrol_t *, mk_exceptionclass_t, mk_exceptiontin_t);
void MK_FillPanicExceptionInfo(
	mk_kernelcontrol_t *,
	mk_exceptionclass_t,
	mk_exceptiontin_t,
	mk_lowerctx_t *,
	mk_upperctx_t *);

/* Helper function to copy various exception information registers to the exceptionInfo structure and clear them
*/
void MK_TricoreFillExInfoHelper(
	mk_hwexceptioninfo_t *,
	mk_exceptionclass_t,
	mk_exceptiontin_t,
	mk_lowerctx_t *,
	mk_upperctx_t *);

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
