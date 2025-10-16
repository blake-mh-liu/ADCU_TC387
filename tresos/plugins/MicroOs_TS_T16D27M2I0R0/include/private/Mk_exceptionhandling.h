/* Mk_exceptionhandling.h - exception handling
 *
 * This file contains definitions for the hardware-independent part of the microkernel's
 * exception handling.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_EXCEPTIONHANDLING_H
#define MK_EXCEPTIONHANDLING_H

#include <public/Mk_hwsel.h>

#include <public/Mk_public_types.h>
#include <public/Mk_exceptioninfo.h>
#include <private/Mk_thread.h>
#include <private/Mk_types_forward.h>

#include MK_HWSEL_PRV_EXCEPTIONHANDLING

/* "Sanity" of exceptions (i.e. did the exception originate in the kernel?)
 *
 * If the hardware permits it (and the option is not otherwise forbidden) the "precise" method is
 * used. The requirement is a hardware flag (or set of flags) that:
 *	- is saved in the thread's register store (or equivalent)
 *	- has no undesirable side effects
 *	- automatically changes to a defined state on kernel entry (exception or interrupt)
*/
#if (!MK_HWHASEXCEPTIONISSANE)

#if MK_HWHASINKERNEL

#define MK_ExceptionIsSane(excType)	MK_ExceptionIsSanePrecise(excType)

/* Function prototype.
*/
mk_kernelcontrol_t *MK_ExceptionIsSanePrecise(mk_hwexceptiontype_t);

#else
#error "Unsupported configuration."
#endif

#endif /*  (!MK_HWHASEXCEPTIONISSANE) */

/* Internal helper for exception info.
*/
mk_hwexceptioninfo_t *MK_LibLookupExceptionInfoForCore(mk_objectid_t, mk_hwexceptioninfo_t * const *);

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
