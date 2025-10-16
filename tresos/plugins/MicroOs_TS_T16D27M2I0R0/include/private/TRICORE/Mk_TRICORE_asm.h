/* Mk_TRICORE_asm.h
 *
 * This file includes the appropriate Mk_TRICORE_asm_xxx.h include file depending on the chosen toolchain.
 *
 * Macros are defined that permit the same source files to be processed by the assemblers of
 * all toolchains. This is done by including the appropriate toolchain file.
 * The assembler memory-map file is also included if appropriate.
 *
 * This file should be included at the very top of all assembly-language files. It must NOT be included
 * by files of any language other than assembler.
 *
 * The Makefiles must ensure that the MK_TOOL macro is defined appropriately on the command line.
 *
 * (c) Elektrobit Automotive GmbH
*/
#ifndef MK_TRICORE_ASM_H
#define MK_TRICORE_ASM_H

#ifndef MK_ASM
#error "MK_ASM is not defined. This file is not intended to be used in C files."
#endif

#include <public/Mk_defs.h>

/* Include the appropriate abstraction file for the toolchain
*/
#if (MK_TOOL==MK_tasking)
#include <private/TRICORE/Mk_TRICORE_asm_tasking.h>
#elif (MK_TOOL==MK_gnu)
#include <private/TRICORE/Mk_TRICORE_asm_gnu.h>
#elif (MK_TOOL==MK_diab)
#include <private/TRICORE/Mk_TRICORE_asm_diab.h>
#else
#error "Unknown or unsupported toolchain. Check your Makefiles!"
#endif

/* Text section alignment
*/
#if MK_TRICORE_CORE == MK_TRICORE_TC162
#define MK_ASM_ALIGN_TEXT	MK_align(32,5)
#else
#define MK_ASM_ALIGN_TEXT	MK_align(16,4)
#endif

#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
