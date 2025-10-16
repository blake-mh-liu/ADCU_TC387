/* Mk_systemcontrol.h
 *
 * This file contains definitions for the microkernel's system-control.
 * This includes the shutdown hook.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_SYSTEMCONTROL_H
#define MK_SYSTEMCONTROL_H

#include <private/Mk_thread.h>
#include <private/Mk_core.h>

#ifndef MK_ASM

/* Configuration structures for running the shutdown hook in a thread.
 * There might be no hook configured, in which case these pointers might be NULL.
 * There is *always* a MK_shutdownThreadConfig!
*/
extern const mk_threadcfg_t * const MK_shutdownHookThreadConfig[MK_MAXCORES];
extern const mk_threadcfg_t * const MK_shutdownThreadConfig[MK_MAXCORES];

#endif

#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
