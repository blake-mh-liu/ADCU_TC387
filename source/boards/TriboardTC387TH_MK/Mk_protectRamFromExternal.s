/* Mk_protectRamFromExternal.s
 *
 * This file implements the function void MK_ProtectRamFromExternal(void). This function needs to
 * ensure that no other bus master may write to the microkernel RAM.
 *
 * This function is called early from MK_Entry2() and therefore several restrictions apply. These
 * restrictions are defined in the safety manual. A non-authorative copy has been placed below for
 * your convenience.
 *
 * Warning: This file has not been developed in accordance with a safety standard (no ASIL)!
 *
 * (c) Elektrobit Automotive GmbH
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_ASM_STRUCT_020]
 *  Each assembly file shall contain exactly one return instruction, which is the last instruction.
 *
 * Reason:
 *  This function is not called via the "call" instruction and may not return via the "ret"
 *  instruction. Instead a "ji a11" needs to be done.
*/
/* Deviation DCG-1 <*> */

#include <private/Mk_asm.h>		/* Must be first! */

	MK_file(Mk_protectRamFromExternal.s)

	MK_ASM_SDECL_TEXT
	MK_ASM_SECTION_TEXT
	MK_ASM_ALIGN_TEXT

	MK_global	MK_ProtectRamFromExternal

/* Implementation restrictions (non-authorative, please refer to safety manual for definitive list):
 * - RAM may not be relied upon.
 * - The value of A10 (stack pointer by EABI) may not be used as stack pointer.
 * - Registers D12, D13, D14, D15 must contain their original values upon return.
 * - The function must return via jump to the address provided in A11 on entry.
*/
MK_ProtectRamFromExternal:

	ji		a11

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
