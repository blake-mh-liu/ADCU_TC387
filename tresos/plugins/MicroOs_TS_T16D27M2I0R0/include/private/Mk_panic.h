/* Mk_panic.h - kernel panic handling
 *
 * "Panic" is the last resort error handling mechanism of the microkernel. It is used
 * only when other methods of handling and reporting errors have failed, or when an internal
 * error has been detected and normal operation cannot be resumed safely.
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef MK_PANIC_H
#define MK_PANIC_H

/* Include panic codes from Mk_error.h.
*/
#include <public/Mk_error.h>
#include <private/Mk_tool.h>

#ifndef MK_ASM

/* Constant pointer to user-defined callout in MK_StartupPanic.
*/
extern const mk_paniccallout_t MK_startupPanicCallout;

/* Function prototypes for panic handling.
 *
 * MK_Panic() is used during normal operation.
 * MK_StartupPanic() is used during startup when it is known that calling MK_Panic() would be unsafe.
 * MK_PanicStop() is typically used when a panic reason occurs while already handling a panic.
*/
void MK_Panic(mk_panic_t) MK_ATTR_NORETURN;
void MK_StartupPanic(mk_panic_t) MK_ATTR_NORETURN;
void MK_PanicStop(mk_panic_t) MK_ATTR_NORETURN;

#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
