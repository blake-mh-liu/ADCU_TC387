/* Os_tool_TRICORE.h
 *
 * This file includes the appropriate Os_tool_TRICORE_xxx.h include file
 * depending on the chosen architecture.
 *
 * The Makefiles must ensure that the OS_ARCH and OS_CPU macros are
 * defined appropriately on the command line.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

#ifndef OS_TOOL_TRICORE_H
#define OS_TOOL_TRICORE_H

#include <Os_defs.h>
#include <Os_types.h>

#ifndef EB_STATIC_CHECK

#if (OS_TOOL==OS_gnu)
#include <TRICORE/Os_TRICORE_core.h>
#include <TRICORE/Os_tool_TRICORE_gnu.h>
#elif (OS_TOOL==OS_clang)
#include <TRICORE/Os_TRICORE_core.h>
#include <TRICORE/Os_tool_TRICORE_clang.h>
#elif (OS_TOOL==OS_tasking)
#include <TRICORE/Os_tool_TRICORE_tasking.h>
#elif (OS_TOOL==OS_diab)
#include <TRICORE/Os_tool_TRICORE_diab.h>
#else
#error "Unknown or unsupported toolchain. Check your Makefiles!"
#endif

#else /* EB_STATIC_CHECK */

/* dummy prototypes of assembler functions for static checker */
extern void OS_DEBUG_BREAK(void);
extern void OS_NOP(void);
extern os_uint32_t OS_MFCR(os_uint32_t);
extern void OS_MTCR(os_uint32_t, os_uint32_t);
extern os_uint32_t OS_MFRA(void);
extern os_uint32_t OS_MFSP(void);
extern void OS_MTRA(void *);
extern void OS_MTA8(void *);
extern void OS_MTD4(os_uint32_t);
extern os_uint32_t OS_AURIX_DISABLE(void);
extern void OS_AURIX_RESTORE(os_uint32_t);
extern void OS_DISABLE(void);
extern void OS_ENABLE(void);
extern void OS_RSLCX(void);
extern void OS_RFJL(void);
extern void OS_RFE(void);
extern void OS_ArchCacheInvalidateLine(const volatile os_char_t *);
void OS_ArchCacheFlushLine(volatile os_char_t *);
void OS_ArchCacheFlushInvalidateLine(volatile os_char_t *);
extern void OS_MTRA_FUNCPTR(void (*)(void));
extern void OS_ArchAtomicModifyFlag(os_uint32_t volatile *, os_uint32_t, os_uint32_t);
extern void OS_ArchAtomicOr(os_uint32_t volatile *, os_uint32_t);
extern void OS_ArchAtomicAndNot(os_uint32_t volatile *, os_uint32_t);

/* MFA8 just reads the constant register A8. It has no side-effect.
 * To model this, we can't use an extern function.
*/
#define OS_MFA8() (OS_kernel_ptr[0])

#endif /* EB_STATIC_CHECK */

#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
