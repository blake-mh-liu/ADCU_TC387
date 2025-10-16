/* Mk_panictailcall.h - tail-calls to kernel-panic functions.
 *
 * This file defines macros for tail-calls to kernel-panic functions.
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef MK_PANICTAILCALL_H
#define MK_PANICTAILCALL_H

#include <public/Mk_defs.h>
#include <private/Mk_panic.h>

#include MK_HWSEL_PRV_CORE

/* Tail-call helper macros for panic functions.
 *
 * Some compilers don't notice that they can replace calls to panic functions by tail-calls to them.
 * On some targets it is necessary that some calls to panic functions are tail calls.
 * MK_StartupPanicTailCall() can be used to tell these compilers explicitly to do a tail-call to MK_StartupPanic().
 * MK_PanicStopTailCall() can be used to tell these compilers explicitly to do a tail-call to MK_PanicStop().
*/
#ifndef MK_StartupPanicTailCall
#define MK_StartupPanicTailCall MK_StartupPanic
#endif /* MK_StartupPanicTailCall */
#ifndef MK_PanicStopTailCall
#define MK_PanicStopTailCall MK_PanicStop
#endif /* MK_PanicStopTailCall */

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
