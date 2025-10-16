/* Os_tool_TRICORE_inline.h - Tricore macros for Tasking toolchain
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/*	This file contains macros (C and assembler) for use with Tricore
 *	and the Tasking compiler.
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: 5.5 (required)
 * Identifiers shall be distinct from macro names.
 * 
 * Reason:
 * OS_ISYNC and OS_DSYNC macros are replaced by corresponding assembly mnemonics using a macro.
 * 
 * 
 * MISRAC2012-2) Deviated Rule: 5.8 (required)
 * Identifiers that define objects or functions with external linkage shall be unique.
 *
 * Reason:
 * OS_ISYNC and OS_DSYNC macros are replaced by corresponding assembly mnemonics using a macro.
 * 
 */

#ifndef OS_TOOL_TRICORE_INLINE_H
#define OS_TOOL_TRICORE_INLINE_H


#ifndef EB_STATIC_CHECK

#if (OS_TOOL==OS_gnu)

#define OS_TOOL_INLINE_KEYWORD __inline__
#define OS_TOOL_ASM_KEYWORD __asm__

/* This combination causes GCC to always inline the function without generating
 * a callable version of it.
 */
#define OS_QUAL_INLINE static __inline__
#define OS_ATTR_INLINE __attribute__((always_inline))

/* This function attribute will prevent GCC from inlining the function for
 * optimisations.
 */
#define OS_ATTR_NO_INLINE __attribute__((noinline))

#define OS_ISYNC()			__asm__ volatile ("isync")
#define OS_DSYNC()			__asm__ volatile ("dsync")


#elif (OS_TOOL==OS_clang)

#define OS_TOOL_INLINE_KEYWORD __inline__
#define OS_TOOL_ASM_KEYWORD __asm__

/* This combination causes GCC to always inline the function without generating
 * a callable version of it.
 */
#define OS_QUAL_INLINE static __inline__
#define OS_ATTR_INLINE __attribute__((always_inline))

/* This function attribute will prevent GCC from inlining the function for
 * optimisations.
 */
#define OS_ATTR_NO_INLINE __attribute__((noinline))

#define OS_ISYNC()			__asm__ volatile ("isync")
#define OS_DSYNC()			__asm__ volatile ("dsync")


#elif (OS_TOOL==OS_tasking)

#define OS_TOOL_INLINE_KEYWORD inline
#define OS_TOOL_ASM_KEYWORD __asm

/* Function qualifier and attribute for inline functions */
#define OS_QUAL_INLINE static inline
#define OS_ATTR_INLINE __attribute__((always_inline))

/* This function attribute will prevent Tasking from inlining the function for
 * optimisations.
 */
#define OS_ATTR_NO_INLINE __attribute__((noinline))

#define OS_ISYNC()			__asm(" isync")
#define OS_DSYNC()			__asm(" dsync")


#elif (OS_TOOL==OS_diab)
#define OS_TOOL_INLINE_KEYWORD __inline__
#define OS_TOOL_ASM_KEYWORD __asm
/* This combination causes DIAB to always inline the function without generating
 * a callable version of it. Note that there are some options, most notably -g,
 * which disable inlining. So this is not reliable.
 */
#define OS_QUAL_INLINE static OS_TOOL_INLINE_KEYWORD
#define OS_ATTR_INLINE __attribute__((always_inline))


/* This function attribute will prevent DIAB from inlining the function for
 * optimisations.
 */
#define OS_ATTR_NO_INLINE __attribute__((noinline))

OS_TOOL_ASM_KEYWORD volatile void OS_ISYNC(void)
{
!
	isync
}

OS_TOOL_ASM_KEYWORD volatile void OS_DSYNC(void)
{
!
	dsync
}

#else
#error "Unknown or unsupported toolchain. Check your Makefiles!"
#endif

#else
/* dummy prototypes of assembler functions for static checker */

/* Deviation MISRAC2012-1 <+2>, MISRAC2012-2 <+2> */
extern void OS_ISYNC(void);
extern void OS_DSYNC(void);

#define OS_QUAL_INLINE static
#define OS_ATTR_INLINE
#define OS_ATTR_NO_INLINE
#define OS_TOOL_ALIGN

#endif /* EB_STATIC_CHECK */

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
