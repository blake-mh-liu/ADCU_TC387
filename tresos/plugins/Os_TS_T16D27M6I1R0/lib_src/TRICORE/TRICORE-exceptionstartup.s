/* TRICORE-exceptionstartup.s
 *
 * This file contains the exception vectors for TRICORE startup
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/
#ifndef OS_ASM
#define OS_ASM
#endif

#include <Os_asm_common.h>
#if (OS_KERNEL_TYPE != OS_MICROKERNEL)

#include <Os_kernel.h>
#include <Os_tool.h>
#include <TRICORE/Os_TRICORE_core.h>

/*!
 * Exception vectors
 *
 * Tricore has 8 exception vectors. They can be located anywhere in memory,
 * as long as they are aligned on a 64-word (256-byte) boundary.
 *
 * The first 6 exceptions, numbered 0 to 5, are fairly standard processor
 * exceptions. In each case, the register D15 contains the trap
 * identification number, which gives more detail about the
 * trap that occurred.
 *
 * The 7th exception is the syscall exception. This exception is used
 * to provide the interface between user-side code and kernel code.
 * The register D15 contains the system-call number specified in the
 * instruction, which ranges from 0 to 255.
 *
 * The final exception is NMI. NMI is normally triggered as a result
 * of an external non-maskable interrupt. On some Tricore boards, NMI
 * is used instead of a normal maskable interrupt. It is a simple matter
 * to redirect the interrupt to a maskable interrupt by writing an NMI
 * handler that triggers a software-triggered interrupt (through CPUSRC1
 * for example), and then by handling the interrupt on CPUSRC1 in the
 * normal way. Note that the NMI trap can also be caused by other events,
 * such as the  watchdog timer or a PLL problem. The NMISR register can
 * be examined to determine the cause.
 * WARNING: some Tricore derivatives do not always set the NMIEXT bit in
 * this register, so if no source is indicated, an external NMI should be
 * assumed.
 *
 *
 * In this version of the exception table, all exceptions other than
 * the system call exception end up in an endless loop. The loop
 * contains a debug instruction to force the debugger (if any) to
 * break if the exception is taken.
 *
 * The system call exception is handled by a special startup version
 * of the normal system-call handler. Without a handler StartOS() wouldn't
 * work; with the normal handler the DisableAllInterrupts() family of
 * system services wouldn't be callable before StartOS().
*/
	_GLOBAL	OS_startupTrapTable
	_GLOBAL	OS_StartupTrap0
	_GLOBAL	OS_StartupTrap1
	_GLOBAL	OS_StartupTrap2
	_GLOBAL	OS_StartupTrap3
	_GLOBAL	OS_StartupTrap4
	_GLOBAL	OS_StartupTrap5
	_GLOBAL	OS_StartupTrap6
	_GLOBAL	OS_StartupTrap7

	_EXTERN	OS_TrapEntry
	_EXTERN	OS_TrapExit

/*	External functions
*/
	_EXTERN	OS_SystemCallStartup

/*	Exception vectors
*/
# if (OS_TOOL==OS_tasking)
		.sdecl	"OS_StartupVectors",code
		.sect	"OS_StartupVectors"
# else
		.section	"OS_StartupVectors","a"
# endif

/*==============================================================================
 *	Reset/MMU exception
 *==============================================================================
*/
	_align(256,8)

OS_startupTrapTable:
OS_StartupTrap0:
	debug
	j		OS_StartupTrap0

/*==============================================================================
 *	Internal protection traps
 *==============================================================================
*/
	_align(32,5)

OS_StartupTrap1:
	debug
	j		OS_StartupTrap1

/*==============================================================================
 *	Instruction errors
 *==============================================================================
*/
	_align(32,5)

OS_StartupTrap2:
	debug
	j		OS_StartupTrap2

/*==============================================================================
 *	Context management errors
 *==============================================================================
*/
	_align(32,5)

OS_StartupTrap3:
	debug
	j		OS_StartupTrap3

/*==============================================================================
 *	System bus and peripheral errors
 *==============================================================================
*/
	_align(32,5)

OS_StartupTrap4:
	debug
	j		OS_StartupTrap4

/*==============================================================================
 *	Assertion traps
 *==============================================================================
*/
	_align(32,5)

OS_StartupTrap5:
	debug
	j		OS_StartupTrap5

/*==============================================================================
 *	System call exception
 *  System calls are not true exceptions. We do not need to preserve the
 *	lower-context registers because the calling function expects them to be
 *  destroyed.
 *	The calling function has placed its parameters in the registers
 *	d4-d7 and a4-a7, so we must not use those registers. Furthermore,
 *	the system call handler will leave its return value in either
 *	d2, d2/d3 or a2, so those registers must be preserved after
 *	returning from the system call.
 *	The OS_SystemCallStartup function is specially written to either dispatch
 *	another task or return using rfe, so we simply jump there.
 *==============================================================================
*/
	_align(32,5)

OS_StartupTrap6:
	j		OS_SystemCallStartup

/*==============================================================================
 *	NMI, watchdog and PLL traps
 *==============================================================================
*/
	_align(32,5)

OS_StartupTrap7:
	debug
	j		OS_StartupTrap7

#endif /* (OS_KERNEL_TYPE != OS_MICROKERNEL) */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
