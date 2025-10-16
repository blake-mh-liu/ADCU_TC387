/* Mk_asm.h - assembler abstraction macros and other definitions for assembly-language.
 *
 * This file is included by every assembly-language source to provide toolchain-independence for
 * assembly-language files. It should be the first file included by every assembly-language file
 * and should not be included anywhere else. In particular, it must not be included by high-level
 * language files.
 *
 * What this file does:
 *
 *	- ensures that MK_ASM is defined correctly
 *	- includes the hardware-specific assembler abstraction file
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_ASM_H
#define MK_ASM_H

#define MK_ASM	1

#include <public/Mk_hwsel.h>

/* Include the hardware-specific assembler abstractions
*/
#include MK_HWSEL_PRV_ASM

#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
