/* Mk_TRICORE_usrgetappmodevoteofcore.s
 *
 * This file contains the function MK_UsrGetAppModeVoteOfCore()
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <private/Mk_asm.h>		/* Must be first! */
#include <private/Mk_syscall.h>

	MK_file(Mk_TRICORE_usrgetappmodevoteofcore.s)

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

	MK_global MK_UsrGetAppModeVoteOfCore

/* !LINKSTO Microkernel.TRICORE.SystemCallInterfaceFunctions, 4
 * !doctype src
*/
MK_UsrGetAppModeVoteOfCore:
	syscall	MK_imm(#, MK_SC_GetAppModeVoteOfCore)
	ret
