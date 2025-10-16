/* Mk_tool_ticgt.h - ticgt toolchain abstraction.
 *
 * This file provides the toolchain abstraction for the TI Code Generation Tools.
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 20.10 (advisory)
 *  The # and ## preprocessor operators should not be used.
 *
 * Reason:
 *  These operators are used to construct symbols in a consistent manner.
*/

#ifndef MK_TOOL_TICGT_H
#define MK_TOOL_TICGT_H

/* MK_PARAM_UNUSED(p) - mark parameter p as unused parameter (or variable).
 * Usage: Function-like.
 */
#define MK_PARAM_UNUSED(p) ((void)(p))

/* Tool specific attributes:
*/
#define MK_ATTR_NORETURN                __attribute__((noreturn))
/* Deviation MISRAC2012-1 <+1> */
#define MK_SECTION_ATTRIB_POST(sec)     __attribute__ ((section(#sec)))
#define MK_ALIGNED_ATTRIB_POST(granule) __attribute__ ((aligned (granule)))
#define MK_ATTR_SECTION(sec)            MK_SECTION_ATTRIB_POST(sec)
#define MK_ATTR_NO_INLINE               __attribute__((noinline))

/* TICGT supports section attributes only if gcc extensions are enabled.
 * #pragma's and the pragma operator always work.
*/
/* Deviation MISRAC2012-1 <START> */
#define MK_TICGT_EMIT_PRAGMA(p)     _Pragma(#p)
#define MK_PRAGMA_SECTION(var, sec) MK_TICGT_EMIT_PRAGMA(DATA_SECTION(var, #sec))
/* Deviation MISRAC2012-1 <STOP> */

/* MK_GEN_STACK(var, sec, size, granule) - generate a variable definition for a stack.
 * var: Name of the variable
 * sec: Section, in which the variable should be put.
 * size: Size of the stack array.
 * granule: Align stack to this granule.
*/
#define MK_GEN_STACK(var, sec, size, granule) \
	mk_stackelement_t var[size] \
	MK_SECTION_ATTRIB_POST(sec) MK_ALIGNED_ATTRIB_POST(granule)

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
