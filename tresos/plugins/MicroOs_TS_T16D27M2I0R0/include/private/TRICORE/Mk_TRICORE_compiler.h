/* Mk_TRICORE_compiler.h
 *
 * This file includes the appropriate Mk_TRICORE_compiler_xxx.h include file depending on the chosen toolchain.
 *
 * Macros are defined that permit the same source files to be processed by the compilers of
 * all toolchains when using features such as in-line assembly language.
 *
 * The Makefiles must ensure that the MK_TOOL macro is defined appropriately on the command line.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_PREPROC_010]
 *  #ifdef directives are not permitted!
 *
 * Reason:
 *  "#ifdef EB_STATIC_CHECK" is allowed in tool specific headers, to provide an implementation of the
 *  hidden compiler abstraction layer.
*/

#ifndef MK_TRICORE_COMPILER_H
#define MK_TRICORE_COMPILER_H

#include <public/Mk_defs.h>
#include <public/Mk_public_types.h>

/* Include the appropriate abstraction file for the toolchain
*/
#if (MK_TOOL==MK_tasking)
#include <private/TRICORE/Mk_TRICORE_compiler_tasking.h>
#elif (MK_TOOL==MK_gnu)
#include <private/TRICORE/Mk_TRICORE_compiler_gnu.h>
#elif (MK_TOOL==MK_diab)
#include <private/TRICORE/Mk_TRICORE_compiler_diab.h>
#else
#error "Unknown or unsupported toolchain. Check your Makefiles!"
#endif


/******************************************************************************
 * Tool-dependent private interface for the simple schedule table (SST) feature.
 *****************************************************************************/

/* The following API is provided.
 *
 * Atomic load-modify-store operations (TriCore's LDMST instruction).
 * MK_TricoreAtomicModifyFlag has the following effect:
 * atomic {
 *  *address = (*address & ~mask) | (mask & value);
 * }
 * MK_TricoreAtomicAndNot does: atomic { *address &= ~mask; }
 * MK_TricoreAtomicOr does    : atomic { *address |= value; }
*/

/* Deviation DCG-1 <+1> */
#ifdef EB_STATIC_CHECK
#define MK_TricoreAtomicModifyFlag(addr, mask, value)	do { } while (0)
#define MK_TricoreAtomicAndNot(address, mask)			do { } while (0)
#define MK_TricoreAtomicOr(address, value)				do { } while (0)
#endif /* EB_STATIC_CHECK */


#endif

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
