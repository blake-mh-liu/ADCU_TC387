/* Mk_tool_diab.h - diab toolchain abstraction
 *
 * This file provides the toolchain abstraction for the Diab compiler.
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef MK_TOOL_DIAB_H
#define MK_TOOL_DIAB_H

/* MK_PARAM_UNUSED(p) - mark parameter p as unused parameter (or variable).
 * Usage: Function-like.
 */
#define MK_PARAM_UNUSED(p) ((void)(p))

/* Tool specific attributes:
*/
#define MK_ATTR_SECTION(sec)		__attribute__((section(#sec)))
#define MK_ATTR_ALIGN(granule)		__attribute__((aligned(granule)))
#define MK_PRAGMA_SECTION(var, sec)	/* nothing */
#define MK_ATTR_NO_INLINE			__attribute__((noinline))

/* On diab the noreturn attribute seems to prevent tail-call optimizations (Version 5.9.4.8, TRICORE).
 * However, one of our reasons to use this attribute is to get tail-calls.
 * Therefore, leave MK_ATTR_NORETURN empty.
*/
#define MK_ATTR_NORETURN

/* MK_GEN_STACK(var, sec, size, granule) - generate a variable definition for a stack.
 * var: Name of the variable
 * sec: Section, in which the variable should be put.
 * size: Size of the stack array.
 * granule: Align stack to this granule.
*/
#define MK_GEN_STACK(var, sec, size, granule)	\
	MK_ATTR_ALIGN(granule)						\
	MK_ATTR_SECTION(sec)						\
	mk_stackelement_t							\
		(var)[(size)]

/* Diab stack protection:
 * MK_CCOPT_USE_COMPILER_STACK_PROTECTION must be set as compiler option to use this feature,
 * in which case it is set to the "stack check fail function" __stack_chk_fail.
 *
 * !LINKSTO Microkernel.CompilerFeature.StackSmashingProtection, 2
 * !doctype src
*/
#ifndef MK_CCOPT_USE_COMPILER_STACK_PROTECTION
#define MK_CCOPT_USE_COMPILER_STACK_PROTECTION 0
#endif

#if (MK_CCOPT_USE_COMPILER_STACK_PROTECTION == 1)
#define MK_ATTR_NO_STACKPROT		__attribute__((stack_protect(0)))
#define MK_CompilerStackCheckGuard	__stack_chk_guard
#define MK_CompilerStackCheckFail	__stack_chk_fail
#endif


#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
