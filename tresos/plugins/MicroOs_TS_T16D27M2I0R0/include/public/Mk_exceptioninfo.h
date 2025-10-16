/* Mk_exceptioninfo.h
 *
 * This file includes the processor-specific exception-info file and then declares the
 * exception-info structure.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_EXCEPTIONINFO_H
#define MK_EXCEPTIONINFO_H

#include <public/Mk_hw_characteristics.h>
#include <public/Mk_hwsel.h>
#include MK_HWSEL_PUB_CHARACTERISTICS
#include MK_HWSEL_PUB_EXCEPTIONINFO

#ifndef MK_ASM
/* The each element of the constant MK_exceptionInfo is either NULL or is a reference to an mk_hwexceptioninfo_t
 * structure in RAM.
 * The indirection permits the feature to be disabled if RAM is in short supply.
*/
extern mk_hwexceptioninfo_t * const MK_exceptionInfo[MK_MAXCORES];
extern mk_hwexceptioninfo_t * const MK_panicExceptionInfo[MK_MAXCORES];

#define MK_GetExceptionInfo()			MK_GetExceptionInfoForCore(-1)
#define MK_GetPanicExceptionInfo()		MK_GetPanicExceptionInfoForCore(-1)

mk_hwexceptioninfo_t *MK_GetExceptionInfoForCore(mk_objectid_t);
mk_hwexceptioninfo_t *MK_GetPanicExceptionInfoForCore(mk_objectid_t);

#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
