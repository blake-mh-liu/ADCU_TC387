/* Os_atomics_tsplatforms_TRICORE.h
 *
 * This file is the TRICORE header file for the set of atomic functions and types,
 * which are provided for reasons of backward compatibility with the
 * asc_Platforms module. That module offered a set of types and functions for
 * atomic bit-manipulation and interrupt control.
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/
#ifndef OS_ATOMICS_TSPLATFORMS_TRICORE_H
#define OS_ATOMICS_TSPLATFORMS_TRICORE_H

#include <Os_defs.h>
#include <Os_atomics_tsplatforms_generic_bits_reservations.h>
#include <Os_panic.h>
#include <TRICORE/Os_tool_TRICORE.h>
#include <TRICORE/Os_TRICORE_core.h>

/* Introduce declarations of Enable/DisableAllInterrupts()
 * depending on kernel type.
 */
#if OS_KERNEL_TYPE == OS_MICROKERNEL
#include <public/Mk_autosar.h>
#else
#include <Os_api_cfg.h>
#endif


/* !LINKSTO Kernel.Atomics.TSFunctionsIntCtrl, 1
*/

static OS_TOOL_INLINE_KEYWORD os_intstatus_t OS_UserAtomicTSIntDisable(void)
{
	os_intstatus_t state;
	os_uint32_t psw = OS_MFCR(OS_PSW);

	if ((psw & OS_PSW_IO) == OS_PSW_IO_U0)
	{
		SuspendAllInterrupts();
		state = 0u;
	}
	else
	{
		state = (os_intstatus_t)OS_AURIX_DISABLE();
	}
	return state;
}

static OS_TOOL_INLINE_KEYWORD void OS_UserAtomicTSIntRestore(os_intstatus_t state)
{
	os_uint32_t psw = OS_MFCR(OS_PSW);

	if ((psw & OS_PSW_IO) == OS_PSW_IO_U0)
	{
		if (state != 0u)
		{
			(void)OS_PANIC(OS_PANIC_ATOMICS_InvalidInterruptStatus);
		}
		ResumeAllInterrupts();
	}
	else
	{
		OS_AURIX_RESTORE((os_uint32_t)state);
	}
}

#endif
