/* Mk_TRICORE_hwsetupexceptions.s
 *
 * This file contains the function MK_HwSetupExceptions(). It sets the exception table
 * to MK_ExceptionTable
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <private/Mk_asm.h>		/* Must be first! */
#include <private/Mk_startup.h>
#include <private/TRICORE/Mk_TRICORE_core.h>

	MK_file(Mk_TRICORE_hwsetupexceptions.s)

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

	MK_extern MK_ExceptionTable
	MK_extern MK_StartupExceptionTable
	MK_extern MK_WriteEndinit

	MK_global MK_HwSetupExceptions

/* void MK_HwSetupExceptions(mk_uint32_t, mk_uint32_t, mk_uint32_t, mk_uint32_t);
 *
 * Parameters:
 *	d4: endKey3
 *	d5: endKey4
 *	d6: endKey1
 *	d7: endKey2
 *
 * This routine shall set the BTV register to the base address of the microkernel's exception table.
 * This is the final step of the microkernel's startup before it becomes operational. This function
 * needs to check that the startup flow control keys (passed to this function as arguments) are correct.
 *
 * Parameters d4, d5, d6 and d7 should contain MK_ENDKEY_3, MK_ENDKEY_4, MK_ENDKEY_1 and MK_ENDKEY_2
 * respectively. If this is not the case, then the routine will set up the startup exception table
 * instead, which halts the system on every exception. In order to prevent a wild jump into this routine
 * from returning with the correct vectors set, the base address of the vector table is loaded into
 * an upper context register before the keys are verified. If the key verification fails, it is
 * overwritten with the address of the startup vectors. The register is actually written only once
 * at the end of this function.
 *
 * !LINKSTO Microkernel.TRICORE.Function.MK_HwSetupExceptions, 1
 * !doctype src
*/
MK_HwSetupExceptions:

	/* Load address of exception table
	*/
	mov     d8, MK_imm(#, MK_lo(MK_ExceptionTable))
	addih   d8, d8, MK_imm(#, MK_hi(MK_ExceptionTable))

	/* Check keys against expected values - to minimize conditional branches we do this by
	 * first XOR-ing the key parameters with their expected values and then ORing these results
	 * with each other. If all keys are correct (and only then), the final result will be zero
	*/
	mov     d10, MK_imm(#, MK_lo(MK_ENDKEY_3))
	addih   d10, d10, MK_imm(#, MK_hi(MK_ENDKEY_3))

	mov     d11, MK_imm(#, MK_lo(MK_ENDKEY_4))
	addih   d11, d11, MK_imm(#, MK_hi(MK_ENDKEY_4))

	mov     d12, MK_imm(#, MK_lo(MK_ENDKEY_1))
	addih   d12, d12, MK_imm(#, MK_hi(MK_ENDKEY_1))

	mov     d13, MK_imm(#, MK_lo(MK_ENDKEY_2))
	addih   d13, d13, MK_imm(#, MK_hi(MK_ENDKEY_2))

	xor		d4, d10
	xor		d5, d11
	xor		d6, d12
	xor		d7, d13

	or		d4, d5
	or		d4, d6
	or		d4, d7

	jz		d4, MK_DoSetupExceptions

	/* Key verification failed. Use startup exception table instead.
	*/
	mov     d8, MK_imm(#, MK_lo(MK_StartupExceptionTable))
	addih   d8, d8, MK_imm(#, MK_hi(MK_StartupExceptionTable))


MK_DoSetupExceptions:

	/* Clear ENDINIT flag
	*/
	mov		d4, MK_imm(#, 0)
	call	MK_WriteEndinit

	/* Set BTV to base of selected exception vector table
	*/
	mtcr    MK_imm(#, MK_BTV), d8
	isync

	/* Set ENDINIT again */
	mov		d4, MK_imm(#, 1)
	call	MK_WriteEndinit

	ret								/* Back to caller */

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
