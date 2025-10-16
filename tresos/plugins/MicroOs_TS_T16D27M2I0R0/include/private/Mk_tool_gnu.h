/* Mk_tool_gnu.h - gnu toolchain abstraction
 *
 * This file provides the toolchain abstraction for the GNU Compiler Collection.
 *
 * (c) Elektrobit Automotive GmbH
*/

#ifndef MK_TOOL_GNU_H
#define MK_TOOL_GNU_H

/* MK_PARAM_UNUSED(p) - mark parameter p as unused parameter (or variable).
 * Usage: Function-like.
 */
#define MK_PARAM_UNUSED(p) ((void)(p))

/* Tool specific attributes:
 * on Tricore attribute section is deprecated, use asection instead
 */
#if (MK_CPUFAMILY==MK_TRICORE)
#define MK_ATTR_ASECTION(sec, aln, flg)	__attribute__((asection(#sec, "a=" #aln, "f=" flg)))
#define MK_ATTR_STACK(sec, granule)		MK_ATTR_ASECTION(sec, granule, "awB")
#else
#define MK_ATTR_SECTION(sec)			__attribute__((section(#sec)))
#define MK_ATTR_ALIGN(granule)			__attribute__((aligned(granule)))
#define MK_ATTR_STACK(sec, granule)		MK_ATTR_SECTION(sec)\
										MK_ATTR_ALIGN(granule)
#endif
#define MK_ATTR_NORETURN				__attribute__((noreturn))
#define MK_PRAGMA_SECTION(var, sec)		/* nothing */
#define MK_ATTR_NO_INLINE				__attribute__((noinline))


/* MK_GEN_STACK(var, sec, size, granule) - generate a variable definition for a stack.
 * var: Name of the variable
 * sec: Section, in which the variable should be put.
 * size: Size of the stack array.
 * granule: Align stack to this granule.
*/
#define MK_GEN_STACK(var, sec, size, granule)	\
	mk_stackelement_t							\
		var[size]								\
		MK_ATTR_STACK(sec, granule)


#endif

/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
