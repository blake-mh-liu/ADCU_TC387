/* Mk_tool_armkeil.h - armkeil toolchain abstraction
 *
 * This file provides the toolchain abstraction for the ARM/keil Compiler Collection.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_CHARSET_010]
 *  This file contains the byte '$' (0x24) which is only permitted inside comments!
 *
 * Reason:
 *  We must use the $$ characters here because they are part of the region-related
 *  symbol names defined in the ARM KEIL toolchain.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 20.10 (advisory)
 *  The # and ## preprocessor operators should not be used.
 *
 * Reason:
 *  These operators are used to construct symbols in a consistent manner.
*/

#ifndef MK_TOOL_ARMKEIL_H
#define MK_TOOL_ARMKEIL_H

/* MK_PARAM_UNUSED(p) - mark parameter p as unused parameter (or variable).
 * Usage: Function-like.
 */
#define MK_PARAM_UNUSED(p) ((void)(p))

/* Tool specific attributes: */
#define MK_ATTR_ALIGN(granule)	__attribute__((aligned(granule)))
#define MK_ATTR_NORETURN		__attribute__((noreturn))
#define MK_ATTR_WEAK			__attribute__((weak))

/* KEIL supports section attributes, pragmas not used */
/* Deviation MISRAC2012-1 <+1> */
#define MK_ATTR_SECTION(sec)		__attribute__((section(#sec)))
#define MK_PRAGMA_SECTION(var, sec)	/* no pragma support */

#define MK_ATTR_NO_INLINE			__attribute__((noinline))


/* MK_GEN_STACK(var, sec, size, granule) - generate a variable definition for a stack.
 * var: Name of the variable
 * sec: Section, in which the variable should be put.
 * size: Size of the stack array.
 * granule: Align stack to this granule.
*/
/* Deviation MISRAC2012-1 <START> */
#define MK_GEN_STACK(var, sec, size, granule)	\
	mk_stackelement_t							\
		var[size]								\
		__attribute__((section(#sec)))			\
		MK_ATTR_ALIGN(granule)
/* Deviation MISRAC2012-1 <STOP> */

/* MK_MR_START_ADR - start address of the specified memory region, normally this
 *                   is the address which points to the RAM section
 * name: name of the memory region
 *
 * To allow a more flexible way of defining symbols by some toolchains, the
 * prefix for linker defined/generated symbols is abstracted using this macro.
*/
/* Deviation MISRAC2012-1 <+2> */
/* Deviation DCG-1 <+1> */
#define MK_MR_START_ADR(name)		(Image$$ ## data ## name ## $$Base)

/* MK_MR_LIMIT_ADR - limit address of the specified memory region, normally this
 *                   is the end address of the region at RAM
 * name: name of the memory region
 *
 * To allow a more flexible way of defining symbols by some toolchains, the
 * prefix for linker defined/generated symbols is abstracted using this macro.
*/
/* Deviation MISRAC2012-1 <+2> */
/* Deviation DCG-1 <+1> */
#define MK_MR_LIMIT_ADR(name)		(Image$$ ## bss ## name ## $$ZI$$Limit)

/* MK_MR_BSTART_ADR - start address of the bss part of the specified memory region,
 *                    normally this is the start address of the bss section at RAM
 * name: name of the memory region
 *
 * To allow a more flexible way of defining symbols by some toolchains, the
 * prefix for linker defined/generated symbols is abstracted using this macro.
*/
/* Deviation MISRAC2012-1 <+2> */
/* Deviation DCG-1 <+1> */
#define MK_MR_BSTART_ADR(name)		(Image$$ ## bss ## name ## $$Base)

/* MK_MR_IDATA_ADR - start address of the data part of the specified memory region,
 *                   normally this is the start address of the data section at ROM
 *                   which is then copied to RAM during startup
 * name: name of the memory region
 *
 * To allow a more flexible way of defining symbols by some toolchains, the
 * prefix for linker defined/generated symbols is abstracted using this macro.
*/
/* Deviation MISRAC2012-1 <+2> */
/* Deviation DCG-1 <+1> */
#define MK_MR_IDATA_ADR(name)		(Load$$ ## data ## name ## $$Base)

/* MK_MR_ANON_DATA_START - abstract the start symbol for anonymous data section
 *                         so it can be redefined by some other toolchains, if
 *                         needed
*/
#define MK_MR_ANON_DATA_START		MK_MR_START_ADR(_MK_ANON)

/* MK_MR_ANON_DATA_END - abstract the end symbol for anonymous data section so
 *                       it can be redefined by some other toolchains, if needed
*/
/* Deviation MISRAC2012-1 <+2> */
/* Deviation DCG-1 <+1> */
#define MK_MR_ANON_DATA_END			(Image$$ ## data ## _MK_ANON ## $$ZI$$Limit)

/* MK_MR_ANON_IDATA_START - abstract the start symbol for anonymous init data
 *                          section so it can be redefined by some other
 *                          toolchains, if needed
*/
#define MK_MR_ANON_IDATA_START		MK_MR_IDATA_ADR(_MK_ANON)

/* MK_MR_ANON_BSS_START - abstract the start symbol for anonymous bss section so
 *                        it can be redefined by some other toolchains, if needed
*/
#define MK_MR_ANON_BSS_START		MK_MR_BSTART_ADR(_MK_ANON)

/* MK_MR_ANON_BSS_END - abstract the end symbol for anonymous bss section so it
 *                      can be redefined by some other toolchains, if needed
*/
#define MK_MR_ANON_BSS_END			MK_MR_LIMIT_ADR(_MK_ANON)

#endif /* MK_TOOL_ARMKEIL_H */
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
