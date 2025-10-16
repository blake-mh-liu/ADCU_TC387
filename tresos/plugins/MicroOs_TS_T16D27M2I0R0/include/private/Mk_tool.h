/* Mk_tool.h - toolchain abstraction
 *
 * This file only includes the appropriate toolchain abstraction sub-header.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 20.10 (advisory)
 *  The # and ## preprocessor operators should not be used.
 *
 * Reason:
 *  Automatic construction of symbols in a consistent manner.
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_PREPROC_010]
 *  #ifdef and the defined-preprocessor operator shall not be used.
 *
 * Reason:
 *  These constructs are necessary here because the macros EB_STATIC_CHECK and
 *  EB_SEMANTIC_CHECK are provided by external tooling outside the control of
 *  the microkernel build. These macros are used to hide tool specific extensions
 *  which would otherwise mislead a MISRA-C checker. The corresponding #else
 *  is used to prevent the repetition of the criticized constructs.
*/

#ifndef MK_TOOL_H
#define MK_TOOL_H

#include <public/Mk_defs.h>

/* Some code analysis tools have problems with toolchain-specific
 * C extensions found in the toolchain-specific header files.
*/
/* Deviation DCG-1 <START> */
#if !(defined(EB_STATIC_CHECK) || defined(EB_SEMANTIC_CHECK))
/* Include toolchain-specific header. */
#if (MK_TOOL == MK_gnu)
#include <private/Mk_tool_gnu.h>
#elif (MK_TOOL == MK_diab)
#include <private/Mk_tool_diab.h>
#elif (MK_TOOL == MK_tasking)
#include <private/Mk_tool_tasking.h>
#elif (MK_TOOL == MK_ghs)
#include <private/Mk_tool_ghs.h>
#elif (MK_TOOL == MK_ticgt)
#include <private/Mk_tool_ticgt.h>
#elif (MK_TOOL == MK_armkeil)
#include <private/Mk_tool_armkeil.h>
#else
#error "Unsupported MK_TOOL."
#endif

#else /* EB_STATIC_CHECK || EB_SEMANTIC_CHECK */

/* Dummy definitions for code analysis tools. */
#define MK_PARAM_UNUSED(p)		((void)(p))
#define MK_ATTR_NORETURN
#define MK_ATTR_ALIGN(granule)
#define MK_ATTR_SECTION(sec)
#define MK_GEN_STACK(var, sec, size, granule)	mk_stackelement_t (var)[(size)]
#define MK_PRAGMA_SECTION(var, sec)	/* nothing */
#define MK_ATTR_NO_INLINE

#endif
/* Deviation DCG-1 <STOP> */

/* MK_PARAM_UNUSED(p) - mark parameter p as unused parameter (or variable).
 * Usage: Function-like.
 */
#ifndef MK_PARAM_UNUSED
#error "MK_PARAM_UNUSED must be defined by the toolchain header."
#endif

/* MK_GEN_STACK(var, sec, size, granule) - generate a variable definition for a stack.
 * var: Name of the variable
 * sec: Section, in which the variable should be put.
 * size: Size of the stack array.
 * granule: Align stack to this granule.
*/
#ifndef MK_GEN_STACK
#error "MK_GEN_STACK must be defined by the toolchain header."
#endif

/* MK_GEN_STACK_DECL(var, sec, size, granule) - generate a variable declaration for a stack.
 * var: Name of the variable
 * sec: Section, in which the variable should be put.
 * size: Size of the stack array.
 * granule: Align stack to this granule.
 *
 * Typically, the definition and declaration look the same. However some toolchains
 * may need to override this macro, e.g. to insert a _Pragma-operator in the
 * definition only.
 *
 * Therefore, if no toolchain-specific override is present, we default to the
 * definition.
*/
#ifndef MK_GEN_STACK_DECL
#define MK_GEN_STACK_DECL	MK_GEN_STACK
#endif

/* MK_ATTR_NORETURN
 *
 * Specifies that a function does not return.
 * If a compiler doesn't support this attribute, define MK_ATTR_NORETURN to be empty.
*/
#ifndef MK_ATTR_NORETURN
#error "MK_ATTR_NORETURN must be defined by the toolchain header."
#endif

/* MK_ATTR_WEAK
 *
 * Used by some toolchains to specify a weak reference of a function symbol, so
 * it can be overwritten after the library was compiled. If some toolchains do
 * this as default behaviour, we define it here as empty.
*/
#ifndef MK_ATTR_WEAK
#define MK_ATTR_WEAK				/* weak reference */
#endif

/* Deviation MISRAC2012-1 <START> */

/* MK_MR_START_ADR - start address of the specified memory region, normally this
 *                   is the address which points to the RAM section
 * name: name of the memory region
 *
 * To allow a more flexible way of defining symbols by some toolchains, the
 * prefix for linker defined/generated symbols is abstracted using this macro.
*/
#ifndef MK_MR_START_ADR
#define MK_MR_START_ADR(name)		(MK_RSA ## name)
#endif

/* MK_MR_LIMIT_ADR - limit address of the specified memory region, normally this
 *                   is the end address of the region at RAM
 * name: name of the memory region
 *
 * To allow a more flexible way of defining symbols by some toolchains, the
 * prefix for linker defined/generated symbols is abstracted using this macro.
*/
#ifndef MK_MR_LIMIT_ADR
#define MK_MR_LIMIT_ADR(name)		(MK_RLA ## name)
#endif

/* MK_MR_BSTART_ADR - start address of the bss part of the specified memory region,
 *                    normally this is the start address of the bss section at RAM
 * name: name of the memory region
 *
 * To allow a more flexible way of defining symbols by some toolchains, the
 * prefix for linker defined/generated symbols is abstracted using this macro.
*/
#ifndef MK_MR_BSTART_ADR
#define MK_MR_BSTART_ADR(name)		(MK_BSA ## name)
#endif

/* MK_MR_IDATA_ADR - start address of the data part of the specified memory region,
 *                   normally this is the start address of the data section at ROM
 *                   which is then copied to RAM during startup
 * name: name of the memory region
 *
 * To allow a more flexible way of defining symbols by some toolchains, the
 * prefix for linker defined/generated symbols is abstracted using this macro.
*/
#ifndef MK_MR_IDATA_ADR
#define MK_MR_IDATA_ADR(name)		(MK_RDA ## name)
#endif

/* Deviation MISRAC2012-1 <STOP> */


/* MK_MR_ANON_DATA_START - abstract the start symbol for anonymous data section
 *                         so it can be redefined by some other toolchains, if
 *                         needed
*/
#ifndef MK_MR_ANON_DATA_START
#define MK_MR_ANON_DATA_START		(MK_ANON_DATA)
#endif

/* MK_MR_ANON_DATA_END - abstract the end symbol for anonymous data section so
 *                       it can be redefined by some other toolchains, if needed
*/
#ifndef MK_MR_ANON_DATA_END
#define MK_MR_ANON_DATA_END			(MK_ANON_DATA_END)
#endif

/* MK_MR_ANON_IDATA_START - abstract the start symbol for anonymous init data
 *                          section so it can be redefined by some other
 *                          toolchains, if needed
*/
#ifndef MK_MR_ANON_IDATA_START
#define MK_MR_ANON_IDATA_START		(MK_ANON_IDAT)
#endif

/* MK_MR_ANON_BSS_START - abstract the start symbol for anonymous bss section so
 *                        it can be redefined by some other toolchains, if needed
*/
#ifndef MK_MR_ANON_BSS_START
#define MK_MR_ANON_BSS_START		(MK_ANON_BSS)
#endif

/* MK_MR_ANON_BSS_END - abstract the end symbol for anonymous bss section so it
 *                      can be redefined by some other toolchains, if needed
*/
#ifndef MK_MR_ANON_BSS_END
#define MK_MR_ANON_BSS_END			(MK_ANON_BSS_END)
#endif

/* MK_ATTR_NO_STACKPROT prevents that stack checks are injected into a function.
 * This is necessary for functions which are called before the stack pointer is
 * initialized properly.
*/
#ifndef MK_ATTR_NO_STACKPROT
#define MK_ATTR_NO_STACKPROT
#endif

#ifndef MK_MR_CAL_CORE0_START
#define MK_MR_CAL_CORE0_START		    (MK_CAL_CORE0_DATA)
#endif

#ifndef MK_MR_CAL_CORE0_DATA_END
#define MK_MR_CAL_CORE0_DATA_END	    (MK_CAL_CORE0_DATA_END)
#endif

#ifndef MK_MR_CAL_CORE0_IDATA_START
#define MK_MR_CAL_CORE0_IDATA_START		(MK_CAL_CORE0_IDAT)
#endif

#ifndef MK_MR_CAL_CORE1_START
#define MK_MR_CAL_CORE1_START		    (MK_CAL_CORE1_DATA)
#endif

#ifndef MK_MR_CAL_CORE1_DATA_END
#define MK_MR_CAL_CORE1_DATA_END	    (MK_CAL_CORE1_DATA_END)
#endif

#ifndef MK_MR_CAL_CORE1_IDATA_START
#define MK_MR_CAL_CORE1_IDATA_START		(MK_CAL_CORE1_IDAT)
#endif

#ifndef MK_MR_CDD_DATA_CORE1_START
#define MK_MR_CDD_DATA_CORE1_START		(MK_CDD_DATA_CORE1)
#endif

#ifndef MK_MR_CDD_DATA_CORE1_END
#define MK_MR_CDD_DATA_CORE1_END			(MK_CDD_DATA_CORE1_END)
#endif

#ifndef MK_MR_MK_CDD_DATA_CORE1_IDAT_START
#define MK_MR_MK_CDD_DATA_CORE1_IDAT_START		(MK_CDD_DATA_CORE1_IDAT)
#endif

#ifndef MK_MR_PSPR_CORE0_START
#define MK_MR_PSPR_CORE0_START		    (MK_PSPR_RUN_CORE0)
#endif

#ifndef MK_MR_PSPR_CORE0_END
#define MK_MR_PSPR_CORE0_END	        (MK_PSPR_RUN_CORE0_END)
#endif

#ifndef MK_MR_PSPR_CORE0_IDATA_START
#define MK_MR_PSPR_CORE0_IDATA_START    (MK_PSPR_LOAD_CORE0_IDAT)
#endif

#ifndef MK_MR_PSPR_CORE1_START
#define MK_MR_PSPR_CORE1_START		    (MK_PSPR_RUN_CORE1)
#endif

#ifndef MK_MR_PSPR_CORE1_END
#define MK_MR_PSPR_CORE1_END	        (MK_PSPR_RUN_CORE1_END)
#endif

#ifndef MK_MR_PSPR_CORE1_IDATA_START
#define MK_MR_PSPR_CORE1_IDATA_START    (MK_PSPR_LOAD_CORE1_IDAT)
#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
