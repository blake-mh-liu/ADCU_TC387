/* Mk_tool_tasking.h - tasking toolchain abstraction
 *
 * This file provides the toolchain abstraction for the Tasking compiler.
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef MK_TOOL_TASKING_H
#define MK_TOOL_TASKING_H

/* MK_PARAM_UNUSED(p) - mark parameter p as unused parameter (or variable).
 * Usage: Function-like.
 *
 * Supported compiler settings do not produce such a warning,
 * hence the implementation is empty.
 *
 * Attention: When changing this implementation, ensure that the
 * resulting binary code does not differ (TRICORE has separate
 * data and address registers, so a non-fully optimizing compiler
 * might add a move from an address to a data register if the
 * parameter in question is a pointer).
 */
#define MK_PARAM_UNUSED(p) do { /* NOTHING */ } while (0)

/* Tool specific attributes:
*/
#define MK_ATTR_SECTION(sec)	__attribute__((section(#sec)))
#define MK_ATTR_ALIGN(granule)	__attribute__((__align(granule)))
#define MK_ATTR_NORETURN		__attribute__((noreturn))
#define MK_ATTR_NO_INLINE		__attribute__((noinline))

/* MK_GEN_STACK(var, sec, size, granule) - generate a variable definition for a stack.
 * var: Name of the variable
 * sec: Section, in which the variable should be put.
 * size: Size of the stack array.
 * granule: Align stack to this granule.
*/
#define MK_GEN_STACK(var, sec, size, granule)	\
	mk_stackelement_t							\
		(var)[(size)]							\
		MK_ATTR_SECTION(sec)					\
		MK_ATTR_ALIGN(granule)

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
