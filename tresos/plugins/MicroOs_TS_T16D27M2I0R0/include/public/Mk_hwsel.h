/* Mk_hwsel.h
 *
 * Common definitions for hardware-specific header file selection.
 * This is the only file that has a chain of conditional preprocessor directives to include
 * a file depending on the CPU family. The file thus included defines the names of all the
 * other processor-specific files in the form:
 *  #define MK_HWSEL_PUB_FOO   <public/BLANKFAMILY/Mk_BLANKFAMILY_foo.h>
 * or
 *  #define MK_HWSEL_PRV_BAR   <private/BLANKFAMILY/Mk_BLANKFAMILY_bar.h>
 *
 * The CPU-family file shall define the following macros:
 *
 * MK_HWSEL_PUB_CHARACTERISTICS
 * MK_HWSEL_PUB_EXCEPTIONINFO
 * MK_HWSEL_PUB_API
 *
 * MK_HWSEL_PRV_ASM
 * MK_HWSEL_PRV_CORE
 * MK_HWSEL_PRV_EXCEPTIONHANDLING
 * MK_HWSEL_PRV_INTERRUPTCONTROLLER
 * MK_HWSEL_PRV_MEMORYPROTECTION
 * MK_HWSEL_PRV_STARTUP
 * MK_HWSEL_PRV_THREAD
 * MK_HWSEL_PRV_ACCOUNTING
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef MK_HWSEL_H
#define MK_HWSEL_H

#include <public/Mk_defs.h>

#if MK_CPUFAMILY==MK_BLANKFAMILY
#include <public/BLANKFAMILY/Mk_BLANKFAMILY_hwsel.h>
#elif MK_CPUFAMILY==MK_PA
#include <public/PA/Mk_PA_hwsel.h>
#elif MK_CPUFAMILY==MK_TRICORE
#include <public/TRICORE/Mk_TRICORE_hwsel.h>
#elif MK_CPUFAMILY==MK_ARM
#include <public/ARM/Mk_ARM_hwsel.h>
#elif MK_CPUFAMILY==MK_ARM64
#include <public/ARM64/Mk_ARM64_hwsel.h>
#elif MK_CPUFAMILY==MK_RH850
#include <public/RH850/Mk_RH850_hwsel.h>
#elif MK_CPUFAMILY==MK_CORTEXM
#include <public/CORTEXM/Mk_CORTEXM_hwsel.h>
#else
#error "Unknown or unsupported value for MK_CPUFAMILY. Check your Makefiles!"
#endif

#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
