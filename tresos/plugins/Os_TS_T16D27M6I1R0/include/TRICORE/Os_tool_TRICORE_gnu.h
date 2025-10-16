/* Os_tool_TRICORE_gnu.h - Tricore macros for gcc
 *
 * CHECK: TABS 4 (see editor commands at end of file)
 *
 * Copyright Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
*/

/*	This file contains macros (C and assembler) for use with Tricore
 *	and the gcc compiler.
*/

#ifndef OS_TOOL_TRICORE_GNU_H
#define OS_TOOL_TRICORE_GNU_H

#include <TRICORE/Os_tool_TRICORE_inline.h>

/*	Macro expansion of stringified absolute values is strange (see
 *	gcc documentation cpp.html). This is a workaround...
*/
#define OS__XSTR(s) OS__STR(s)
#define OS__STR(s) #s

/* OS_PARAM_UNUSED(p) - mark parameter p as unused parameter (or variable).
 * Usage: Function-like.
 */
#define OS_PARAM_UNUSED(p) ((void)(p))

#ifdef OS_ASM
/* CHECK: SAVE
 * CHECK: RULE 402 OFF - These macros are for the assembler, not for C
*/

/*	The Gnu assembler expects registers to be called %something
*/
#define a0		%a0
#define a1		%a1
#define a2		%a2
#define a3		%a3
#define a4		%a4
#define a5		%a5
#define a6		%a6
#define a7		%a7
#define a8		%a8
#define a9		%a9
#define a10		%a10
#define a11		%a11
#define a12		%a12
#define a13		%a13
#define a14		%a14
#define a15		%a15
#define d0		%d0
#define d1		%d1
#define d2		%d2
#define d3		%d3
#define d4		%d4
#define d5		%d5
#define d6		%d6
#define d7		%d7
#define d8		%d8
#define d9		%d9
#define d10		%d10
#define d11		%d11
#define d12		%d12
#define d13		%d13
#define d14		%d14
#define d15		%d15
#define e0		%e0
#define e2		%e2
#define e4		%e4
#define e6		%e6
#define e8		%e8
#define e10		%e10
#define e12		%e12
#define e14		%e14
#define sp		%sp

/*	The Gnu assembler does not expect any special prefix for
 *	immediate operands.
*/
#define _IMM(p,x)		x

/* Reference to temporary label (preceding)
*/
#define OS_TEMPLABEL_PREV(l) l##b

/* Reference to temporary label (following)
*/
#define OS_TEMPLABEL_NEXT(l) l##f

/*	The Gnu assembler uses EABI syntax for the bit specification in jz.t etc.
*/
#define _REGBIT(r,b)	r, b

/*	The Gnu assembler uses hi:x and lo:x to extract the
 *	high and low words from a literal.
*/
#define _hiword(x)		 hi:x
#define _loword(x)		 lo:x

/*	Gnu assembler uses .type, .globl and .extern as normal.
*/
#define _GTYPE(s,t)	.type	s,t
#define _TTYPE(s,t)	s:
#define _GLOBAL		.globl

/* The .extern is ignored by as and has no direct counterpart. Therefore
 * we simply start a comment for this line. */
#define _EXTERN		#


/*	Gnu assembler has standard .text and .data sections
*/
#define	_TEXT	.text
#define _DATA	.data

/*	The Gnu assembler uses "power of 2" notation for alignment
*/
#define _align(n,p)		.align p

/* The Gnu assembler has the .hword directive for 16-bit words */
#define _HWORD .hword

/* These macros implement the *16.* and *32.* opcodes
 * that are provided by some assemblers. The Gnu assembler
 * uses a .code16 directive instead.
 * WARNING: ld16 and st16 might be using a bug in gas.
 *
 * CHECK: NOPARSE
*/
	.macro	ret16
		.code16
		ret
	.endm

	.macro	mov16	p1,p2
		.code16
		mov		\p1,\p2
	.endm

	.macro	jeq16	p1,p2,p3
		.code16
		jeq		\p1,\p2,\p3
	.endm

	.macro	and16	p1,p2
		.code16
		and		\p1,\p2
	.endm

	.macro	or16	p1,p2
		.code16
		or	\p1,\p2
	.endm

	.macro	add16	p1,p2
		.code16
		add		\p1,\p2
	.endm

	.macro	bisr16	p1
		.code16
		bisr	\p1
	.endm

	.macro	bisr32	p1
		.code32
		bisr	\p1
	.endm

	.macro	nop16
		.code16
		nop
	.endm

	.macro	nop32
		.code32
		nop
	.endm

	.macro	ld16	p1,p2,p3
		.code16
		ld\p1	\p2,\p3
	.endm

	.macro	st16	p1,p2,p3
		.code16
		st\p1	\p2,\p3
	.endm

	.macro	_mtcr	creg,reg
		dsync
		mtcr	\creg,\reg
		isync
	.endm

/*	The GenIntVector macro generates an interrupt vector with the
 *	specified symbol, BISR-level, isr-id and entry function.
*/
	.macro	GenIntVector	name,bisrlvl,isrid,entry,exit
	.align	5
	.globl	\name
\name:
	bisr	\bisrlvl
	mov		d4,\isrid
	call	\entry
	j		\exit
	.endm

	/*	The DirectVector macro generates an interrupt vector which jumps directly to the
	 *  entry. The entry needs to use the interrupt keyword.
	 */
	.macro	DirectVector	name,entry
		.align	5
		.globl	\name
\name:
		j		\entry
	.endm

/* CHECK: PARSE */
/* CHECK: RESTORE */
#else /* !OS_ASM */

#ifdef __cplusplus
extern "C" {
#endif

#define OS_DEBUG_BREAK()	__asm__ volatile ("debug")

#define OS_NOP()	__asm__ volatile ("nop" : : : "memory")

#define OS_MTCR(csfr, val) \
	do {																		\
		register os_uint32_t os_myMtcrTmp = (val);								\
		OS_DSYNC();																\
		__asm__ volatile ("mtcr "OS__XSTR(csfr)",%0" : : "d" (os_myMtcrTmp));	\
		__asm__ volatile ("isync");												\
	} while(0)

/* Align an object to n bytes. */
#define OS_TOOL_ALIGN(bytes) __attribute__((aligned(bytes)))


/* Now it gets ugly. We want to avoid braces in expressions, so we cannot
 * use gcc's _mfcr intrinsic, which also uses braces in the expression to
 * provide the return value. This prevents us from using a macro.
 *
 * Since the CSFR ID needs to be encoded into the mfcr instruction, we cannot
 * use an inline function either.
 *
 * The ugly solution: Define one inline function per CSFR, and define the
 * OS_MFCR macro such that it uses the provided CSFR ID (e.g. OS_PSW) to call
 * the corresponding inline function. This of course only works when the macro
 * is used with the OS_xxx CSFR constants, but that should be acceptable.
 */
#define OS_MFCR_FCTEMPLATE(CSFRID) \
OS_QUAL_INLINE os_uint32_t OS_MFCR_ ##CSFRID(void) OS_ATTR_INLINE; \
OS_QUAL_INLINE os_uint32_t OS_MFCR_ ##CSFRID(void) \
{ \
	register os_uint32_t os_myMfcrRes; \
	__asm__ volatile ("mfcr %0,%1" : "=d" (os_myMfcrRes) : "i" (CSFRID)); \
	return os_myMfcrRes; \
}

#define OS_MFCR(CSFRID) OS_MFCR_ ##CSFRID()

OS_MFCR_FCTEMPLATE(OS_DPR0_L)
OS_MFCR_FCTEMPLATE(OS_DPR0_U)
OS_MFCR_FCTEMPLATE(OS_DPR1_L)
OS_MFCR_FCTEMPLATE(OS_DPR1_U)
OS_MFCR_FCTEMPLATE(OS_DPR2_L)
OS_MFCR_FCTEMPLATE(OS_DPR2_U)
OS_MFCR_FCTEMPLATE(OS_DPR3_L)
OS_MFCR_FCTEMPLATE(OS_DPR3_U)
OS_MFCR_FCTEMPLATE(OS_DPR4_L)
OS_MFCR_FCTEMPLATE(OS_DPR4_U)
OS_MFCR_FCTEMPLATE(OS_CPR0_L)
OS_MFCR_FCTEMPLATE(OS_CPR0_U)
OS_MFCR_FCTEMPLATE(OS_CPR1_L)
OS_MFCR_FCTEMPLATE(OS_CPR1_U)
OS_MFCR_FCTEMPLATE(OS_DPRE_0)
OS_MFCR_FCTEMPLATE(OS_DPRE_1)
OS_MFCR_FCTEMPLATE(OS_DPWE_0)
OS_MFCR_FCTEMPLATE(OS_DPWE_1)
OS_MFCR_FCTEMPLATE(OS_CPXE_0)
OS_MFCR_FCTEMPLATE(OS_CPXE_1)

/* The core id register has a constant value (on a core). We can tell this GCC by marking
 * this function pure.
 */
OS_QUAL_INLINE os_uint32_t OS_MFCR_OS_CORE_ID(void) __attribute__((always_inline, pure));
OS_QUAL_INLINE os_uint32_t OS_MFCR_OS_CORE_ID(void)
{
	register os_uint32_t os_myMfcrRes;
	__asm__ ("mfcr %0,%1" : "=d" (os_myMfcrRes) : "i" (OS_CORE_ID));
	return os_myMfcrRes;
}

OS_MFCR_FCTEMPLATE(OS_DBGSR)
OS_MFCR_FCTEMPLATE(OS_GPRWB)
OS_MFCR_FCTEMPLATE(OS_EXEVT)
OS_MFCR_FCTEMPLATE(OS_CREVT)
OS_MFCR_FCTEMPLATE(OS_SWEVT)
OS_MFCR_FCTEMPLATE(OS_TR0EVT)
OS_MFCR_FCTEMPLATE(OS_TR1EVT)

OS_MFCR_FCTEMPLATE(OS_DMS)
OS_MFCR_FCTEMPLATE(OS_DCX)

OS_MFCR_FCTEMPLATE(OS_PCXI)
OS_MFCR_FCTEMPLATE(OS_PSW)
OS_MFCR_FCTEMPLATE(OS_PC)
OS_MFCR_FCTEMPLATE(OS_DBITEN)
OS_MFCR_FCTEMPLATE(OS_SYSCON)
OS_MFCR_FCTEMPLATE(OS_BIV)
OS_MFCR_FCTEMPLATE(OS_BTV)
OS_MFCR_FCTEMPLATE(OS_ISP)
OS_MFCR_FCTEMPLATE(OS_ICR)
OS_MFCR_FCTEMPLATE(OS_FCX)
OS_MFCR_FCTEMPLATE(OS_LCX)

OS_MFCR_FCTEMPLATE(OS_DCON0)
OS_MFCR_FCTEMPLATE(OS_PCON0)

OS_QUAL_INLINE os_uint32_t OS_MFSP(void) OS_ATTR_INLINE;
OS_QUAL_INLINE os_uint32_t OS_MFSP(void)
{
	register os_uint32_t os_myMfspRes;
	__asm__ volatile ("mov.d %0,%%sp" : "=d" (os_myMfspRes));
	return os_myMfspRes;
}

OS_QUAL_INLINE void* OS_MFA8(void) __attribute__((always_inline, pure));
OS_QUAL_INLINE void* OS_MFA8(void)
{
	register void *os_myMfa8Res;
	__asm__ ("mov.aa %0,%%a8" : "=a" (os_myMfa8Res));
	return os_myMfa8Res;
}

OS_QUAL_INLINE os_uint32_t OS_MFRA(void) OS_ATTR_INLINE;
OS_QUAL_INLINE os_uint32_t OS_MFRA(void)
{
	register os_uint32_t os_myMfraRes;
	__asm__ volatile ("mov.d %0,%%a11" : "=d" (os_myMfraRes));
	return os_myMfraRes;
}

OS_QUAL_INLINE void OS_MTRA(void* os_myVal) OS_ATTR_INLINE;
OS_QUAL_INLINE void OS_MTRA(void* os_myVal)
{
	__asm__ volatile ("mov.aa %%a11,%0" : : "a" (os_myVal));
}

/* This one is used to store a function pointer. We need this only when very
 * restrictive compiler settings are used that disallow us to cast a function
 * pointer to a pointer to object (void*) */
OS_QUAL_INLINE void OS_MTRA_FUNCPTR(void (*os_myVal)(void)) OS_ATTR_INLINE;
OS_QUAL_INLINE void OS_MTRA_FUNCPTR(void (*os_myVal)(void))
{
	__asm__ volatile ("mov.aa %%a11,%0" : : "a" (os_myVal));
}

OS_QUAL_INLINE void OS_MTA8(void* os_myVal) OS_ATTR_INLINE;
OS_QUAL_INLINE void OS_MTA8(void* os_myVal)
{
	OS_MTCR(OS_PSW, OS_MFCR(OS_PSW) | OS_PSW_GW);
	__asm__ volatile ("mov.aa %%a8,%0" : : "a" (os_myVal));
	OS_MTCR(OS_PSW, OS_MFCR(OS_PSW) & ~OS_PSW_GW);
}

OS_QUAL_INLINE void OS_MTD4(os_uint32_t os_myVal) OS_ATTR_INLINE;
OS_QUAL_INLINE void OS_MTD4(os_uint32_t os_myVal)
{
	__asm__ volatile ("mov    %%d4,%0" : : "d" (os_myVal));
}

/* Disables interrupts and returns the previous state of ICR.IE.
 * All bits except the lowest bit of the return value are zero.
 * Memory accesses must not be reordered across this function by the compiler.
*/
OS_QUAL_INLINE os_uint32_t OS_AURIX_DISABLE(void) OS_ATTR_INLINE;
OS_QUAL_INLINE os_uint32_t OS_AURIX_DISABLE(void)
{
	register os_uint32_t os_myRes;
	__asm__ volatile ("disable %0" : "=d" (os_myRes) :: "memory");
	return os_myRes;
}
/* Restores the given interrupt state 'os_myIstate' which was previously returned by OS_AURIX_DISABLE.
 * Only the lowest bit of 'os_myIstate' is used.
 * Memory accesses must not be reordered across this function by the compiler.
*/
OS_QUAL_INLINE void OS_AURIX_RESTORE(os_uint32_t os_myIstate) OS_ATTR_INLINE;
OS_QUAL_INLINE void OS_AURIX_RESTORE(os_uint32_t os_myIstate)
{
	__asm__ volatile ("restore %0" : : "d" (os_myIstate) : "memory");
}

#define OS_DISABLE()	__asm__ volatile ("disable":::"memory")
#define OS_ENABLE()		__asm__ volatile ("enable":::"memory")

/* Macro to restore lower context
*/
#define OS_RSLCX()	__asm__ volatile ("rslcx")

/* Macro to return from a JL instruction. We call it RFJL, but it is
 * really only a JI A11.
*/
#define OS_RFJL()	__asm__ volatile ("ji %a11")

/* Macro to return from interrupt.
*/
#define OS_RFE()	__asm__ volatile ("rfe")

/* Cache operations: flush, invalidate and flush+invalidate
*/
#define OS_ArchCacheFlushLine(p)			__asm__ volatile ("cachea.w [%0]0" : : "a"(p) : "memory")
#define OS_ArchCacheInvalidateLine(p)		__asm__ volatile ("cachea.i [%0]0" : : "a"(p) : "memory")
#define OS_ArchCacheFlushInvalidateLine(p)	__asm__ volatile ("cachea.wi [%0]0" : : "a"(p) : "memory")

/* A buggy GNU compiler uses an address register when storing 32-bit data. The st.a instructions
 * need 32-bit alignment.
*/
#define OS_ArchMisalignedData(b,l)	( ( ((l) > 2) && ((((os_uint32_t)(b)) & 0x0003) != 0) ) || \
									( ((l) > 1) && ((((os_uint32_t)(b)) & 0x0001) != 0) ) )


/* Atomic load-modify-store operations:
 * AtomicModifyFlag, AtomicAndNot, AtomicOr.
 * These operations will be mapped to TriCore's LDMST instruction.
*/

/* AtomicModifyFlag: atomic { *address = (*address & ~mask) | (value & mask); }
*/
OS_QUAL_INLINE
void OS_ArchAtomicModifyFlag (os_uint32_t volatile *os_myAddr, os_uint32_t os_myMask, os_uint32_t os_myValue)
OS_ATTR_INLINE;
OS_QUAL_INLINE
void OS_ArchAtomicModifyFlag(os_uint32_t volatile *os_myAddr, os_uint32_t os_myMask, os_uint32_t os_myValue) {
	/* regValue and regMask have to be passed as asm input,
	 *   to make sure they live in their respective registers.
	 * Note that %d4 = %e4[31:0] and %d5 is %e4[63:32].
	 * This is the tasking intrinsic's signature.
	 *  A function, which is actually called, should get os_myValue (%d4) before os_myMask (%d5).
	*/
	register os_uint32_t regValue __asm__ ("%%d4");
	register os_uint32_t regMask __asm__ ("%%d5");
	regMask = os_myMask;
	regValue = os_myValue;
	__asm__ __volatile__ (
		"ldmst [%0]0, %%e4\n"
		: "=a"(os_myAddr)								/*output*/
		: "0" (os_myAddr), "d" (regMask), "d" (regValue)	/*input*/
		: "memory"									/*clobber*/
	);
}

/* AtomicAndNot: atomic { *address &= ~mask; }
*/
#define OS_ArchAtomicAndNot(address, mask) OS_ArchAtomicModifyFlag((address), (mask), 0U)

/* AtomicOr: atomic { *address |= value; }
*/
OS_QUAL_INLINE
void OS_ArchAtomicOr(os_uint32_t volatile *os_myAddress, os_uint32_t os_myValue)
OS_ATTR_INLINE;
OS_QUAL_INLINE void OS_ArchAtomicOr(os_uint32_t volatile *os_myAddress, os_uint32_t os_myValue) {
	OS_ArchAtomicModifyFlag(os_myAddress, os_myValue, os_myValue);
}

/* section attribute is deprecated on Tricore/gnu toolchain
*/
#define OS_DATA_SECTION_ATTRIB_POST(sec)	__attribute__ ((asection(#sec, "f=aw")))
#define OS_BSS_SECTION_ATTRIB_POST(sec)		__attribute__ ((asection(#sec, "f=awB")))

#define OS_GEN_STACK(var, sec, size, granule)					\
	os_stackelement_t var[size]									\
	__attribute__ ((asection(#sec, "a=" #granule, "f=awB")))	\
	OS_STACK_ATTRIB()

#ifdef __cplusplus
}
#endif

#endif /* ! OS_ASM */

#endif
/* Editor settings; DO NOT DELETE
 * vi:set ts=4:
*/
