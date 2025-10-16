/* Mk_TRICORE_vectortables.s
 *
 * This file contains the exception and interrupt vector tables for TriCore processors
 *
 * The interrupt vector table in this file converts the hardware vectoring scheme used
 * by TriCore processors into the software vectoring scheme preferred by the Microkernel.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_LAYOUT_020]
 *  Source files shall contain at most one routine having external linkage.
 *
 * Reason:
 *  This file contains a set of exception vector/kernel entry routines.
 *  The exception is permitted by the DCG.
 *
 * DCG-2) Deviated Rule: [OS_ASM_STRUCT_020]
 *  Each assembly file shall contain exactly one return instruction, which is the last instruction.
 *
 * Reason:
 *  This file contains a set of exception vector/kernel entry routines, each of which transfers
 *  control to a handler that exits via the dispatcher. A RET instruction at the end of the file would
 *  be unreachable code.
*/
/* Deviation DCG-1 <*> */
/* Deviation DCG-2 <*> */

#include <private/Mk_asm.h>		/* Must be first! */
#include <private/TRICORE/Mk_TRICORE_core.h>
#include <private/TRICORE/Mk_TRICORE_interruptcontroller.h>

#define MK_ASM_ALIGN_EXCVECTORTABLEENTRY	MK_align(32, 5)

	MK_file(Mk_TRICORE_vectortables.s)

/*
 * !LINKSTO        Microkernel.TRICORE.Exception.Handlers, 1,
 * !               Microkernel.TRICORE.Entry, 1
 * !description    The C handler functions for the exceptions
 * !doctype        src
*/
	MK_ASM_SDECL_EXCEPTIONTABLE
	MK_ASM_SECTION_EXCEPTIONTABLE

	/* The entire section must be aligned to 2048 bytes for the interrupt vector, which
	 * will be placed 2040 from the start of the section.
	*/
	MK_align(2048, 11)

	MK_global	MK_ExceptionTable

	MK_global	MK_Exception0_VirtualAddress
	MK_global	MK_Exception1_Protection
	MK_global	MK_Exception2_Instruction
	MK_global	MK_Exception3_Context
	MK_global	MK_Exception4_BusError
	MK_global	MK_Exception5_Assertion
	MK_global	MK_Exception6_Syscall
	MK_global	MK_Exception7_Nmi

	MK_extern	MK_HandleVirtualAddressTrap
	MK_extern	MK_HandleProtectionTrap
	MK_extern	MK_HandleInstructionTrap
	MK_extern	MK_HandleContextTrap
	MK_extern	MK_HandleBusErrorTrap
	MK_extern	MK_HandleAssertionTrap
	MK_extern	MK_HandleNmi
	MK_extern	MK_TricoreSyscall

/*
 * !LINKSTO        Microkernel.TRICORE.Exception.StartupHandlers, 1,
 * !               Microkernel.TRICORE.Entry, 1
 * !description    The C handler functions for the exceptions
 * !doctype        src
*/
	MK_global	MK_StartupExceptionTable

	MK_global	MK_StartupException0_VirtualAddress
	MK_global	MK_StartupException1_Protection
	MK_global	MK_StartupException2_Instruction
	MK_global	MK_StartupException3_Context
	MK_global	MK_StartupException4_BusError
	MK_global	MK_StartupException5_Assertion
	MK_global	MK_StartupException6_Syscall
	MK_global	MK_StartupException7_Nmi

/*
 * !LINKSTO        Microkernel.TRICORE.Entry, 1
 * !description    The handler functions for the interrupts
 * !doctype        src
*/
	MK_global	MK_InterruptTable
	MK_extern	MK_TricoreDispatchInterruptSoft

/* MK_StartupExceptionTable
 *
 * The startup exception table is a set of 8 stub routines spaced at 32-byte intervals
 * from a base address that is aligned on a 256 byte boundary.
 *
 * This exception table is designed for use during startup, before exceptions can be handled
 * by the normal microkernel handlers.
 * Each exception therefore has an endless loop as an emergency stop. A DEBUG instruction
 * is placed into each loop so that if a debugger is attached the developer is notified
 * immediately.
*/
	MK_align(256, 8)
MK_StartupExceptionTable:

/*	Entry 0: Virtual address trap
*/
	MK_ASM_ALIGN_EXCVECTORTABLEENTRY
MK_StartupException0_VirtualAddress:
	debug
	j		MK_StartupException0_VirtualAddress

/*	Entry 1: Protection trap
*/
	MK_ASM_ALIGN_EXCVECTORTABLEENTRY
MK_StartupException1_Protection:
	debug
	j		MK_StartupException1_Protection

/*	Entry 2: Instruction trap
*/
	MK_ASM_ALIGN_EXCVECTORTABLEENTRY
MK_StartupException2_Instruction:
	debug
	j		MK_StartupException2_Instruction

/*	Entry 3: Context trap
*/
	MK_ASM_ALIGN_EXCVECTORTABLEENTRY
MK_StartupException3_Context:
	debug
	j		MK_StartupException3_Context

/*	Entry 4: Bus error trap
*/
	MK_ASM_ALIGN_EXCVECTORTABLEENTRY
MK_StartupException4_BusError:
	debug
	j		MK_StartupException4_BusError

/*	Entry 5: Assertion trap
*/
	MK_ASM_ALIGN_EXCVECTORTABLEENTRY
MK_StartupException5_Assertion:
	debug
	j		MK_StartupException5_Assertion

/*	Entry 6: System call
*/
	MK_ASM_ALIGN_EXCVECTORTABLEENTRY
MK_StartupException6_Syscall:
	debug
	j		MK_StartupException6_Syscall

/*	Entry 7: NMI
*/
	MK_ASM_ALIGN_EXCVECTORTABLEENTRY
MK_StartupException7_Nmi:
	debug
	j		MK_StartupException7_Nmi

/* MK_ExceptionTable
 *
 * The exception table is a set of 8 stub routines spaced at 32-byte intervals
 * from a base address that is aligned on a 256 byte boundary.
 *
 * Each exception has its own TriCore-specific handler function that takes two
 * parameters:
 *  - pcxi (d4) head list of of CSAs that are in use by the thread (after saving lower context)
 *	- trap identification number (d5) - the value placed in d15 by the processor
*/
	MK_align(256, 8)
MK_ExceptionTable:

/*	Entry 0: Virtual address trap
*/
	MK_ASM_ALIGN_EXCVECTORTABLEENTRY
MK_Exception0_VirtualAddress:
	svlcx
	mfcr	d4, MK_imm(#, MK_PCXI)
	mov		d5, d15
	mov		d15, MK_imm(#, 0)
	mtcr	MK_imm(#, MK_PCXI), d15
	isync
	j		MK_HandleVirtualAddressTrap

/*	Entry 1: Protection trap
*/
	MK_ASM_ALIGN_EXCVECTORTABLEENTRY
MK_Exception1_Protection:
	svlcx
	mfcr	d4, MK_imm(#, MK_PCXI)
	mov		d5, d15
	mov		d15, MK_imm(#, 0)
	mtcr	MK_imm(#, MK_PCXI), d15
	isync
	j		MK_HandleProtectionTrap

/*	Entry 2: Instruction trap
*/
	MK_ASM_ALIGN_EXCVECTORTABLEENTRY
MK_Exception2_Instruction:
	svlcx
	mfcr	d4, MK_imm(#, MK_PCXI)
	mov		d5, d15
	mov		d15, MK_imm(#, 0)
	mtcr	MK_imm(#, MK_PCXI), d15
	isync
	j		MK_HandleInstructionTrap

/*	Entry 3: Context trap
*/
	MK_ASM_ALIGN_EXCVECTORTABLEENTRY
MK_Exception3_Context:
	svlcx							/* Note: in case of the (non-recoverable) FCU exception this triggers
									 *       an endless loop of FCU exceptions. This is a safe state and is
									 *       as good as any explicit detection of this exception type here.
									*/
	mfcr	d4, MK_imm(#, MK_PCXI)
	mov		d5, d15
	mov		d15, MK_imm(#, 0)
	mtcr	MK_imm(#, MK_PCXI), d15
	isync
	j		MK_HandleContextTrap

/*	Entry 4: Bus error trap
*/
	MK_ASM_ALIGN_EXCVECTORTABLEENTRY
MK_Exception4_BusError:
	svlcx
	mfcr	d4, MK_imm(#, MK_PCXI)
	mov		d5, d15
	mov		d15, MK_imm(#, 0)
	mtcr	MK_imm(#, MK_PCXI), d15
	isync
	j		MK_HandleBusErrorTrap

/*	Entry 5: Assertion trap
*/
	MK_ASM_ALIGN_EXCVECTORTABLEENTRY
MK_Exception5_Assertion:
	svlcx
	mfcr	d4, MK_imm(#, MK_PCXI)
	mov		d5, d15
	mov		d15, MK_imm(#, 0)
	mtcr	MK_imm(#, MK_PCXI), d15
	isync
	j		MK_HandleAssertionTrap

/*	Entry 6: System call
*/
	MK_ASM_ALIGN_EXCVECTORTABLEENTRY
MK_Exception6_Syscall:
	svlcx
	mfcr	d4, MK_imm(#, MK_PCXI)
	mov		d5, d15
	mov		d15, MK_imm(#, 0)
	mtcr	MK_imm(#, MK_PCXI), d15
	isync
	j		MK_TricoreSyscall

/*	Entry 7: NMI
*/
	MK_ASM_ALIGN_EXCVECTORTABLEENTRY
MK_Exception7_Nmi:
	svlcx
	mfcr	d4, MK_imm(#, MK_PCXI)
	mov		d5, d15
	mov		d15, MK_imm(#, 0)
	mtcr	MK_imm(#, MK_PCXI), d15
	isync
	j		MK_HandleNmi

/* After MK_align(1024, 10) we are at offset 1024.
*/
	MK_align(1024, 10)
	MK_WORD	0	/* section offset 1024 */

	MK_align(512, 9)
	MK_WORD	0	/* section offset 1536 */

	MK_align(256, 8)
	MK_WORD	0	/* section offset 1792 */

	MK_align(128, 7)
	MK_WORD	0	/* section offset 1920 */

	MK_align(64, 6)
	MK_WORD	0	/* section offset 1984 */

	MK_align(32, 5)
	MK_WORD	0	/* section offset 2016 */

	MK_align(16, 4)
	MK_WORD	0	/* section offset 2032 */

/* The interrupt vector is placed with an offset of 2040 bytes from a 2048-byte aligned address. This address can
 * be used as a single interrupt vector that is executed for any SRPN.
 */
	MK_align(8, 3)
MK_InterruptTable:
	svlcx
	mfcr	d4, MK_imm(#, MK_PCXI)
	mov		d15, MK_imm(#, 0)
	mtcr	MK_imm(#, MK_PCXI), d15
	isync
	j		MK_TricoreDispatchInterruptSoft


/* Editor settings: DO NOT DELETE
 * vi:set ts=4:
*/
