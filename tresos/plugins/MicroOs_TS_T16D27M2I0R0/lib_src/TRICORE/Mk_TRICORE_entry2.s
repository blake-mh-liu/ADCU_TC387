/* Mk_TRICORE_entry2.s - startup file for Tricore
 *
 * The code here performs what must be done before any C routines can be called.
 * This is the "safe boot" entry point. It can be used when another module such as a bootloader
 * has performed the hardware initialization at boot time, such as register initialization and
 * ECC RAM initialization.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_ASM_STRUCT_020]
 *  Each assembly file shall contain exactly one return instruction, which is the last instruction.
 *
 * Reason:
 *  The code in this file is the startup code, not a function. MK_Entry2 is not expected to be called,
 *  so there is nowhere to return to. Furthermore, MK_Startup is not expected to return. If it should
 *  happen to return because of some hardware fault, the only thing we can do here is enter an endless
 *  loop and wait until a watchdog trips.
*/
/* Deviation DCG-1 <*> */

#include <private/Mk_asm.h>			/* Must be first */
#include <private/Mk_startup.h>
#include <public/TRICORE/Mk_TRICORE_characteristics.h>
#include <private/TRICORE/Mk_TRICORE_core.h>

	MK_file(Mk_TRICORE_entry2.s)

	MK_global	MK_Entry2

	MK_extern	MK_ProtectRamFromExternal

	MK_extern	MK_kernelStackTop
	MK_extern	MK_coreCsas

	MK_extern	MK_StartupExceptionTable
	MK_extern	MK_WriteEndinit
	MK_extern	MK_BootCsaList
	MK_extern	MK_Startup

	MK_extern	MK_INITIAL_A0
	MK_extern	MK_INITIAL_A1
	MK_extern	MK_INITIAL_A8

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

/* MK_Entry2()
 *
 * !LINKSTO        Microkernel.TRICORE.Function.Asm.MK_entry2, 5
 * !doctype        src
 *
 * This is the entry point for the microkernel.
 *
 * Conditions for entry:
 *	- the processor is in supervisor mode. If not, this function ends in an endless loop at MK_Entry2_Stop.
 *
 * Register Usage:
 *  - a4-a7, d4-d7: Parameter/scratch registers
 *  - d12 - d15: Startup Key
*/

MK_Entry2:

/* Preload the registers d12 to d15 with the 128-bit startup key. This key is passed through all the phases
 * of the startup, with XOR transformations each time, to make it very unlikely that the startup code can
 * be partially executed without being detected.
 *
 * Disable interrupts
 *
 * Interrupt disabling is done interleaved with loading the key to reduce to near zero the likelihood
 * of loading the key and still having interrupts enabled.
*/
	disable
	mov		d12, MK_imm(#, MK_lo(MK_STARTKEY_1))
	addih	d12, d12, MK_imm(#, MK_hi(MK_STARTKEY_1))
	disable
	mov		d13, MK_imm(#, MK_lo(MK_STARTKEY_2))
	addih	d13, d13, MK_imm(#, MK_hi(MK_STARTKEY_2))
	disable
	mov		d14, MK_imm(#, MK_lo(MK_STARTKEY_3))
	addih	d14, d14, MK_imm(#, MK_hi(MK_STARTKEY_3))
	disable

/* Verify that processor is running in supervisor mode
*/
	mfcr	d4, MK_imm(#, MK_PSW)					/* Load PSW */
	extr.u	d4, d4, MK_imm(#, 10), MK_imm(#, 2)		/* Extract IO-field */
	jne		d4, MK_imm(#, 2), MK_Entry2_Stop		/* Stop if not 2, i.e. supervisor */

/* Set the stack pointer to 0x01000000. This will cause a virtual address or data access exception if the
 * stack gets used unexpectedly before it is safe to rely on the content of RAM.
*/
	movh.a	a10, MK_imm(#, 0x0100)

/* Next step is to protect the microkernel's RAM parts from modifications by external busmasters. How to do this
 * exactly depends on the derivative and even the project-specific use of the processor. It is therefore done in a
 * call-out function, but we cannot use the normal call/ret calls, because those would use CSAs which lay in
 * RAM and are therefore not available yet.
*/
	jl		MK_ProtectRamFromExternal

/* Initialize SP.
 *
 * Now that we are protected from external bus masters, we can start using the stack. Initialization of the ISP
 * is delayed, because we need to clear endinit to write ISP, which requires we setup CSAs first.
*/
	/* MK_kernelStackTop is an array, indexed with core id */
	movh.a	a10, MK_imm(#, MK_hi(MK_kernelStackTop))
	lea		a10, [a10]MK_lo(MK_kernelStackTop)
	/* read the core id */
	mfcr	d4, MK_imm(#, MK_CORE_ID)

#if MK_TRICORE_SCU == MK_SCU_TC3XX
/* By design, in TC3XX core 5 doesn't exist, this breaks sequential order of core-IDs */
	mov		d7, MK_imm(#, 5)
	jlt		d4, d7, tc3_proceed1
	mov		d6, MK_imm(#, 1)
	sub		d4, d6
tc3_proceed1:
#endif

	/* d4 = MK_kernelStackTop[coreId] */
	addsc.a	a10, a10, d4, MK_imm(#, 2)
	ld.a	a10, [a10]

/* The next important step is to set up the startup exception vector table. This can, however
 * only be done if the ENDINIT flag is cleared. Clearing this flag in assembler is tedious and
 * cannot be done without loops, so it is implemented in C. This means we need to initialize
 * at least one CSA to be able to call a function.
*/
/* Get start and end of the CSA-area.
 * MK_coreCsas is an array of CSA start-limit pairs (both are uint32)
 * - one for each core.
*/
	movh.a	a4, MK_imm(#, MK_hi(MK_coreCsas))
	lea		a4, [a4]MK_lo(MK_coreCsas)
	/* read the core id */
	mfcr	d4, MK_imm(#, MK_CORE_ID)

#if MK_TRICORE_SCU == MK_SCU_TC3XX
/* By design, in TC3XX core 5 doesn't exist, this breaks sequential order of core-IDs */
	mov		d7, MK_imm(#, 5)
	jlt		d4, d7, tc3_proceed2
	mov		d6, MK_imm(#, 1)
	sub		d4, d6
tc3_proceed2:
#endif

	/* a4 = &MK_coreCsas[coreId] (size of one entry is 8 byte) */
	addsc.a	a4, a4, d4, MK_imm(#, 3)
	/* d4 = a4->rsa (address of the first CSA) */
	ld.w	d4, [a4]
	/* d5 = a4->rla (limit address of the CSA area) */
	ld.w	d5, [a4]4
	jl		MK_BootCsaList

/* Initialize the PSW (value includes write permission for the global address registers).
*/
	mov		d4, MK_imm(#, MK_lo(MK_INITIAL_PSW))
	addih	d4, d4, MK_imm(#, MK_hi(MK_INITIAL_PSW))
	mtcr	MK_imm(#, MK_PSW), d4
	isync

/* Check whether the COMPAT register has the desired value.
 * If not we enter the endless loop at MK_Entry2_Stop.
*/
	mfcr	d4, MK_imm(#, MK_COMPAT)
	mov		d5, MK_imm(#, MK_lo(MK_COMPAT_MASK))
	addih	d5, d5, MK_imm(#, MK_hi(MK_COMPAT_MASK))
	and		d4, d4, d5
	mov		d5, MK_imm(#, MK_lo(MK_COMPAT_VALUE))
	addih	d5, d5, MK_imm(#, MK_hi(MK_COMPAT_VALUE))
	jne		d4, d5, MK_Entry2_Stop

/* We may now call the C-function to clear the ENDINIT-flag */
	mov		d4, MK_imm(#, 0)
	call	MK_WriteEndinit

/* Initialize BTV with the base of the startup vector table.
*/
	mov		d4, MK_imm(#, MK_lo(MK_StartupExceptionTable))
	addih	d4, d4, MK_imm(#, MK_hi(MK_StartupExceptionTable))
	dsync
	mtcr	MK_imm(#, MK_BTV), d4
	isync

/* We now have the startup vector table set up and can load the last startup key value.
*/
	mov		d15, MK_imm(#, MK_lo(MK_STARTKEY_4))
	addih	d15, d15, MK_imm(#, MK_hi(MK_STARTKEY_4))
	disable

/* Initialize BIV with 0. This forces a virtual address or null pointer exception if an interrupt
 * occurs before the correct vector base is loaded.
*/
	mov		d4, MK_imm(#, 0)
	mtcr	MK_imm(#, MK_BIV), d4
	isync

/* Initialize ISP
 * A10 already contains the stack pointer value.
*/
	dsync
	mov.d	d4, a10
	mtcr	MK_imm(#, MK_ISP), d4
	isync

/* set ENDINIT again */
	mov		d4, MK_imm(#, 1)
	call	MK_WriteEndinit

/* Initialize the global address registers a0, a1, a8 and a9
*/
	movh.a	a0, MK_imm(#, MK_hi(MK_INITIAL_A0))
	lea		a0, [a0]  MK_lo(MK_INITIAL_A0)

	movh.a	a1, MK_imm(#, MK_hi(MK_INITIAL_A1))
	lea		a1, [a1]  MK_lo(MK_INITIAL_A1)

	movh.a	a8, MK_imm(#, MK_hi(MK_INITIAL_A8))
	lea		a8, [a8]  MK_lo(MK_INITIAL_A8)

	/* Note: On multicore processors register A9 will point to the MK's core-local
	 * kernel control variables after start-up, no matter how it is initialized here.
	*/
	mov.a	a9, MK_imm(#, 0)

/* jump to MK_Startup()
 *
 * We now have a workable (although not quite complete) C environment,
 * so the remainder of the startup is controlled by the C function MK_Startup.
 *
 * Parameters to MK_Startup:
 *	p1 = k2 xor k3 = d13 xor d14 --> d4
 *	p2 = k3 xor k4 = d14 xor d15 --> d5
 *	p3 = k4 xor k1 = d15 xor d12 --> d6
 *	p4 = k1 xor k2 = d12 xor d13 --> d7
*/
	xor		d4, d13, d14
	xor		d5, d14, d15
	xor		d6, d15, d12
	xor		d7, d12, d13

	xor		d12, d12				/* Erase the original key, otherwise it could hang around in registers */
	xor		d13, d13
	xor		d14, d14
	xor		d15, d15

	j		MK_Startup

MK_Entry2_Stop:
	j		MK_Entry2_Stop			/* MK_Startup has returned! There's not much else we can do. */

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
