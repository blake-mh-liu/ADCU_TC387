/* Mk_callout.h
 *
 * This header file defines the AUTOSAR standard callout (hook) functions.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_CALLOUT_H
#define MK_CALLOUT_H

#include <public/Mk_public_types.h>
#include <public/Mk_autosar.h>

#ifndef MK_ASM
/* These are the global hook functions that are currently supported.
*/
void ErrorHook(StatusType);
ProtectionReturnType ProtectionHook(StatusType);

void StartupHook(void);
void ShutdownHook(StatusType);

/* These functions are provided by the board package
*/
void MK_InitHardwareBeforeData(void);
void MK_InitHardwareAfterData(void);

#endif

#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
