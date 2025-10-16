/* Os_tool_TRICORE_tasking.h - Tricore macros for Tasking toolchain
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

#ifndef OS_TOOL_TRICORE_TASKING_H
#define OS_TOOL_TRICORE_TASKING_H

#include <TRICORE/Os_tool_TRICORE_inline.h>

/* See comment in corresponding gnu header file */
#define OS__XSTR(s) OS__STR(s)
#define OS__STR(s) #s

/* OS_PARAM_UNUSED(p) - mark parameter p as unused parameter (or variable).
 * Usage: Function-like.
 *
 * Attention: When changing this implementation, ensure that the
 * resulting binary code does not differ (TRICORE has separate
 * data and address registers, so a non-fully optimizing compiler
 * might add a move from an address to a data register if the
 * parameter in question is a pointer).
 */
#define OS_PARAM_UNUSED(p) ((void)(p))

#ifdef OS_ASM
/* CHECK: SAVE
 * CHECK: RULE 402 OFF - These are not C macros!
*/

/*	For Tasking we have to put a # operator before immediate values
 *	in the assembler. This results in a C preprocesor warning, which
 *	can be turned off for .s files.
*/
#define _IMM(p,x)	p x

/* Reference to temporary label (preceding)
*/
#define OS_TEMPLABEL_PREV(l) l##p

/* Reference to temporary label (following)
*/
#define OS_TEMPLABEL_NEXT(l) l##n

/*	The Tasking assembler expects the register bit for instructions such as jz.t
 *	to be specified as (e.g.) d15:1
*/
#define _REGBIT(r,b)	r:b


/*	The Tasking assembler uses @his(x) and @los(x) to extract the
 *	high and low words from a literal.
*/
#define _hiword(x)	@his(x)
#define _loword(x)	@los(x)

/*	Tasking uses .global instead of .globl. .extern is OK
 *	.type is completely different :-(
*/
#define _GTYPE(s,t)
#define _TTYPE(s,t)	s	.type	t
#define	_GLOBAL		.global
#define _EXTERN		.extern

/*	Tasking assembler has no standard .text and .data sections so we have
 *	to explicitly declare them as well as switch to them.
*/
/* CHECK: NOPARSE */
	.sdecl	".text",code
	.sdecl	".data",data
/* CHECK: PARSE */

#define	_TEXT	.sect ".text"
#define _DATA	.sect ".data"

/*	The Tasking assembler uses absolute notation for alignment
*/
#define _align(n,p)		.align n


/* The Tasking assembler has the .half directive for 16-bit words */
#define _HWORD .half

/* CHECK: NOPARSE */
_mtcr	.macro	creg,reg
		dsync
		mtcr	creg,reg
		isync
	.endm

/*	The GenIntVector macro generates an interrupt vector with the
 *	specified symbol, BISR-level, isr-id, entry and exit functions.
*/
GenIntVector	.macro	name,bisrlvl,isrid,entry,exit
	.align	32
	.global	name
	.extern	entry
	.extern	exit
name:
	bisr	#bisrlvl
	mov		d4,#isrid
	call	entry
	j		exit
	.endm


/*	The DirectVector macro generates an interrupt vector which jumps directly to the
 *  entry. The entry needs to use the interrupt keyword.
 */
DirectVector	.macro	name,entry
	.align	32
	.global	name
	.extern	entry
name:
	j		entry
.endm

/* CHECK: PARSE */
/* CHECK: RESTORE */
#else /* ! OS_ASM */

#ifdef __cplusplus
extern "C" {
#endif

#define OS_DEBUG_BREAK()	__asm(" debug")

#define OS_NOP()			__asm(" nop")

#define OS_MFCR(csfr)		__mfcr(csfr)

#define OS_MTCR(csfr, val) \
	do {																		\
		register os_uint32_t os_myMtcrTmp = (val);								\
		__asm(" dsync \n mtcr #"OS__XSTR(csfr)",%0" : : "d" (os_myMtcrTmp));	\
		OS_ISYNC();																\
	} while (0)

/* Align an object to n bytes. */
#define OS_TOOL_ALIGN(bytes)				__attribute__((__align(bytes)))


OS_QUAL_INLINE os_uint32_t OS_MFRA(void) OS_ATTR_INLINE;
OS_QUAL_INLINE os_uint32_t OS_MFRA(void)
{	register os_uint32_t os_myMfraRes;
	__asm("mov.d %0,a11" : "=d" (os_myMfraRes));
	return os_myMfraRes;
}

OS_QUAL_INLINE os_uint32_t OS_MFSP(void) OS_ATTR_INLINE;
OS_QUAL_INLINE os_uint32_t OS_MFSP(void)
{	register os_uint32_t os_myMfspRes;
	__asm("mov.d %0,sp" : "=d" (os_myMfspRes));
	return os_myMfspRes;
}

OS_QUAL_INLINE void *OS_MFA8(void) __attribute__((always_inline, pure));
OS_QUAL_INLINE void *OS_MFA8(void)
{	register void *os_myMfa8Res;
	__asm("mov.aa %0,a8" : "=a" (os_myMfa8Res));
	return os_myMfa8Res;
}

#define OS_MTRA_FUNCPTR(val) \
	do {															\
		register void (*os_myMtraTmp)(void) = (val);				\
		__asm volatile ("mov.aa a11,%0" : : "a" (os_myMtraTmp));	\
	} while (0)

#define OS_MTRA(val) \
	do {															\
		register void *os_myMtraTmp = (val);						\
		__asm volatile ("mov.aa a11,%0" : : "a" (os_myMtraTmp));	\
	} while (0)

#define OS_MTA8(val) \
	do {														\
		register void *os_myMta8Tmp = (val);					\
        OS_MTCR(OS_PSW, OS_MFCR(OS_PSW) | OS_PSW_GW);			\
		__asm volatile ("mov.aa a8,%0" : : "a" (os_myMta8Tmp));	\
        OS_MTCR(OS_PSW, OS_MFCR(OS_PSW) & ~OS_PSW_GW);			\
	} while (0)

#define OS_MTD4(val) \
	do {														\
		register os_uint32_t os_myMtd4Tmp = (val);				\
		__asm volatile ("mov d4,%0" : : "d" (os_myMtd4Tmp));	\
	} while (0)

/* Disables interrupts and returns the previous state of ICR.IE.
 * All bits except the lowest bit of the return value are zero.
 * Memory accesses must not be reordered across this function by the compiler.
*/
OS_QUAL_INLINE os_uint32_t OS_AURIX_DISABLE(void) OS_ATTR_INLINE;
OS_QUAL_INLINE os_uint32_t OS_AURIX_DISABLE(void)
{
	register os_uint32_t os_myRes;
	__asm volatile ("disable %0" : "=d" (os_myRes) :: "memory");
	return os_myRes;
}
/* Restores the given interrupt state 'os_myIstate' which was previously returned by OS_AURIX_DISABLE.
 * Only the lowest bit of 'os_myIstate' is used.
 * Memory accesses must not be reordered across this function by the compiler.
*/
OS_QUAL_INLINE void OS_AURIX_RESTORE(os_uint32_t os_myIstate) OS_ATTR_INLINE;
OS_QUAL_INLINE void OS_AURIX_RESTORE(os_uint32_t os_myIstate)
{
	__asm volatile ("restore %0" : : "d" (os_myIstate) : "memory");
}

#define OS_DISABLE()	__disable()
#define OS_ENABLE()		__enable()

/* Macro to restore lower context
*/
#define OS_RSLCX()			__asm ("rslcx")

/* Macro to return from a JL instruction. We call it RFJL, but it is
 * really only a JI A11.
*/
#define OS_RFJL()			__asm ("ji a11")

/* Macro to return from interrupt.
*/
#define OS_RFE()			__asm ("rfe")


/* CompilerMemBarrier:
 * Forces the compiler to place all preceding write operations to 'p' before this barrier
 * and to place all subsequent read operation after it.
 * This will make the compiler believe address p is read from a register here.
 * Since tasking treats embedded assembler as blackbox,
 * it doesn't know whether we read or write or which kind of addressing we use.
 * Therefore it must not reorder accesses to any memory location legally accessible via 'p'
 * across this barrier.
*/
#define OS_CompilerMemBarrier(p)			do { __asm("     " : : "a"(p)); } while (0)

/* Cache operations: flush, invalidate and flush+invalidate
*/
#define OS_ArchCacheFlushLine(p)			__asm ("cachea.w [%0]0" : : "a"(p))
#define OS_ArchCacheInvalidateLine(p)		__asm ("cachea.i [%0]0" : : "a"(p))
#define OS_ArchCacheFlushInvalidateLine(p)	__asm ("cachea.wi [%0]0" : : "a"(p))

/* Atomic load-modify-store operations (TriCore's LDMST instruction).
 * OS_ArchAtomicModifyFlag has the following effect:
 * atomic {
 *	*address = (*address & ~mask) | (mask & value);
 * }
 * OS_ArchAtomicAndNot does: atomic { *address &= ~mask; }
 * OS_ArchAtomicOr does    : atomic { *address |= value; }
 *
 * Note: the cast to unsigned int* is needed here to avoid a tasking warning
 * (passing incompatible pointer types). This warning is even issued when
 * cast to os_uint32_t*, which is actually the same.
*/
#define OS_ArchAtomicModifyFlag(address, mask, value) __ldmst((unsigned int*)(address), (mask), (value))
#define OS_ArchAtomicAndNot(address, mask) OS_ArchAtomicModifyFlag((address), (mask), 0U)
#define OS_ArchAtomicOr(address, value) \
	do {\
		os_uint32_t OS_ArchAtomicOrValue;\
		OS_ArchAtomicOrValue = (os_uint32_t)(value);\
		OS_ArchAtomicModifyFlag((address), OS_ArchAtomicOrValue, OS_ArchAtomicOrValue);\
	} while(0)

#ifdef __cplusplus
}
#endif

#endif

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
