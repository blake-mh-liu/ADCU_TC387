/* Os_mkctrsub.h
 *
 * This file provides the include of the counter subsystem header file from
 * microkernel.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/
#ifndef OS_MKCTRSUB_H
#define OS_MKCTRSUB_H

#if (OS_KERNEL_TYPE!=OS_MICROKERNEL)
#error "Os_mklib.h should only be used in a microkernel environment"
#endif

#include <Mk_Version.h>

#if defined(MK_NF_REFACTORING_CTRSUB) && (MK_NF_REFACTORING_CTRSUB == 1)
#include <private/Mk_ctrsub.h>
#else
#include <private/Mk_qmos.h>
#endif

#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
