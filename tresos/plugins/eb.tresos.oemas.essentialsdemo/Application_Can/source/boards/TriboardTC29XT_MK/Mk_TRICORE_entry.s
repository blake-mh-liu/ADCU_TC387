/* Mk_TRICORE_entry.s - startup file for Tricore
 *
 * The code here performs what must be done after a cold start before any C routines can be called.
 *
 * Warning: This file has not been developed in accordance with a safety standard (no ASIL)!
 *
 * (c) Elektrobit Automotive GmbH
 *
 * $Id: Mk_TRICORE_entry.s 27096 2017-01-18 19:15:27Z mist9353 $
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_ASM_STRUCT_020]
 *  Each assembly file shall contain exactly one return instruction, which is the last instruction.
 *
 * Reason:
 *  The code in this file is the startup code, not a function. MK_Entry is not expected to be called;
 *  control is transferred there by the processor after a reset, so there is nowhere to return to.
 *  Furthermore, MK_Entry2 does not return.
*/
/* Deviation DCG-1 <*> */

#include <private/Mk_asm.h>		/* Must be first! */
#include <public/Mk_hw_characteristics.h>
#include <private/TRICORE/Mk_TRICORE_core.h>

	MK_file(Mk_TRICORE_entry.s)

	MK_global	MK_Entry
	MK_extern	MK_Entry2
	MK_extern	MK_InterruptTable		/* Forces MK_InterruptTable to be linked */
#if MK_MAXCORES > 1
	MK_extern	MK_BootCsaList
	MK_extern	Tmpl_DemoStartup
#endif

	MK_ASM_SDECL_RESET
	MK_ASM_SECTION_RESET

MK_Entry:
	disable

	/* If all symbols are mapped to cached addresses (0x8 segment), we won't see our
	 * source code in the debugger, because all symbols are in a different segment than
	 * our start address. We fix this by jumping to the symbol in the respective segment.
	*/
	movh.a	a15, MK_imm(#,MK_hi(_realaddr))
	lea		a15, [a15] MK_lo(_realaddr)
	ji		a15
_realaddr:

#if MK_MAXCORES > 1
	/* The user is responsible for starting up all cores, which are under control
	 * of the Safety OS and let them jump to or call MK_Entry2.
	 * So let's call a C function, which will do this here.
	*/

	/* The stack can't be used here */
	movh.a	a10, MK_imm(#, 0x0100)

	/* Setup the CSA list, so we can call C functions.
	 *
	 * We will use space for 32 CSAs at the beginning of our core-local data scratch-pad.
	 * That's OK, because our demo doesn't have meaningful data in RAM before startup.
	 *
	 * We don't start at offset 0, because some compilers use loop unrolling optimizations
	 * which will cause traps due to accesses to "different segments" (trap class 2, tin 5).
	*/
	movh	d4, MK_imm(#, 0xd000)
	add		d4, d4, MK_imm(#, 0x40)
	mov		d6, MK_imm(#, 0x800)
	add		d5, d4, d6
	jl		MK_BootCsaList

	/* Now call the C function which starts the other cores etc.
	*/
	call	Tmpl_DemoStartup
#endif


	j		MK_Entry2

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
