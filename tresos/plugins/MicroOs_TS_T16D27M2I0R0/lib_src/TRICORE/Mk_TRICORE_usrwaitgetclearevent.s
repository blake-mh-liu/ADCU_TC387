/* Mk_TRICORE_usrwaitgetclearevent.s
 *
 * This file contains the function MK_UsrWaitGetClearEvent()
 *
 * (c) Elektrobit Automotive GmbH
*/
#include <private/Mk_asm.h>		/* Must be first! */
#include <private/Mk_syscall.h>

	MK_file(Mk_TRICORE_usrwaitgetclearevent.s)

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

	MK_global MK_UsrWaitGetClearEvent

/* MK_UsrWaitGetClearEvent
 *
 * Prototype: mk_statusandvalue_t MK_UsrWaitGetClearEvent(mk_uint32_t);
 *
 * !LINKSTO Microkernel.TRICORE.SystemCallInterfaceFunctions, 4
 * !doctype src
*/
MK_UsrWaitGetClearEvent:
	syscall	MK_imm(#, MK_SC_WaitGetClearEvent)
	ret
