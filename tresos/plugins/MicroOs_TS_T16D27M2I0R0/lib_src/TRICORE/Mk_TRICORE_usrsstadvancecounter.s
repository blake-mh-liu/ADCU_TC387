/* Mk_TRICORE_usrsstadvancecounter.s
 *
 * This file contains the function MK_UsrSstAdvanceCounter()
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <private/Mk_asm.h>		/* Must be first! */
#include <private/Mk_syscall.h>

	MK_file(Mk_TRICORE_usrsstadvancecounter.s)

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

	MK_global MK_UsrSstAdvanceCounter

/* !LINKSTO Microkernel.TRICORE.SystemCallInterfaceFunctions, 4
 * !doctype src
*/
MK_UsrSstAdvanceCounter:
	syscall	MK_imm(#, MK_SC_SstAdvanceCounter)
	ret
