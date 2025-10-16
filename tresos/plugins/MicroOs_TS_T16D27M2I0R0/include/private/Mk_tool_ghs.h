/* Mk_tool_ghs.h - ghs toolchain abstraction
 *
 * This file provides the toolchain abstraction for the Greenhills Multi compiler suite.
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef MK_TOOL_GHS_H
#define MK_TOOL_GHS_H

/* MK_PARAM_UNUSED(p) - mark parameter p as unused parameter (or variable).
 * Usage: Function-like.
 */
#define MK_PARAM_UNUSED(p) ((void)(p))

/* GHS tool-specific attributes:
*/
#define MK_ATTR_SECTION(sec)		__attribute__((section(#sec)))
#define MK_ATTR_ALIGN(granule)		__attribute__((aligned(granule)))
#define MK_ATTR_NORETURN			__attribute__((noreturn))
#define MK_PRAGMA_SECTION(var, sec)	/* nothing */
#define MK_ATTR_NO_INLINE			__attribute__((noinline))

/* MK_GEN_STACK(var, sec, size, granule) - generate a variable definition for a stack.
 * var: Name of the variable
 * sec: Section, in which the variable should be put.
 * size: Size of the stack array.
 * granule: Align stack to this granule.
*/
#define MK_GEN_STACK(var, sec, size, granule)	\
	mk_stackelement_t							\
		var[size]								\
		__attribute__((section(#sec)))			\
		__attribute__((aligned(granule)))

#endif	/* MK_TOOL_GHS_H */
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
