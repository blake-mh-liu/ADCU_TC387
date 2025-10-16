/* Mk_k_unknownctrsubcall.c
 *
 * This file contains the function MK_UnknownCtrSubCall().
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <public/Mk_public_types.h>
#include <public/Mk_public_api.h>
#include <private/Mk_ctrsub.h>
#include <public/Mk_error.h>

/* MK_UnknownCtrSubCall() - handle an unimplemented or unconfigured counter subsystem service call
 *
 * This function is used to fill unused entries in the counter subsystem call table - for example, to minimize the
 * "dead code" caused by unused features.
 *
 * This function runs in a counter subsystem thread and must be written accordingly.
 *
 * !LINKSTO Microkernel.Function.MK_UnknownCtrSubCall, 1
 * !doctype src
*/
mk_parametertype_t MK_UnknownCtrSubCall(mk_parametertype_t p1, mk_parametertype_t p2, mk_parametertype_t unused_p3)
{
	MK_PARAM_UNUSED(unused_p3);

	return MK_ReportError(MK_sid_UnknownService, MK_eid_UnimplementedCtrSubFunction, p1, p2);
}

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
