/* Os_types_arch.h
 *
 * Architecture-dependent types are included from the appropriate ARCH-types.h
 * include file depending on the chosen architecture.
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
#ifndef OS_TYPES_ARCH_H
#define OS_TYPES_ARCH_H

#include <Os_defs.h>

#include <Os_hwsel.h>
#include OS_HWSEL_TYPES

/* Os types (non-microkernel variant) */

/*!
 * os_tick_t
 *
 * Tick counter - only if not already defined
*/
#ifndef OS_ARCH_TICK_T
#ifndef OS_ASM
typedef os_uint32_t os_tick_t;
#endif
#define OS_MAXTICK		OS_U(0xffffffff)
#define OS_SIZEOF_TICK	4
#endif

/*!
 * os_alarmbase_t
 *
 * Alarmbase structure for GetAlarmBase
*/
#ifndef OS_ASM
typedef struct os_alarmbase_s os_alarmbase_t;

struct os_alarmbase_s
{
	os_tick_t	maxallowedvalue;
	os_tick_t	ticksperbase;
	os_tick_t	mincycle;
};
#endif

#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
