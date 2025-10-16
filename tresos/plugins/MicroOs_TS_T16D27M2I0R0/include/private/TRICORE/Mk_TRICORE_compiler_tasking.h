/* Mk_TRICORE_compiler_tasking.h
 *
 * This file defines macros to permit the microkernel to be compiled with the tasking compiler
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: Dir 4.3 (required)
 *  Assembly language shall be encapsulated and isolated.
 *
 * Reason:
 *  The purpose of these functions is to encapsulate an assembler instruction.
 *
 * MISRAC2012-2) Deviated Rule: 9.1 (mandatory)
 *  All automatic variables shall have been assigned a value before being used.
 *
 * Reason:
 *  Variable mfa9Res is set by the assembler instruction just before its usage.
 *
 * MISRAC2012-3) Deviated Rule: 17.3 (mandatory)
 *  Functions shall have complete visible prototypes at call.
 *
 * Reason:
 *  __mfcr and __swap are intrinsic functions of the tasking compiler. We could use an
 *  inline assembler statement instead, but this would also cause a MISRA violation.
 *
 * MISRAC2012-4) Deviated Rule: 11.8 (required)
 *  A cast shall not be performed that removes any const or volatile qualification
 *  from the type addressed by a pointer.
 *
 * Reason:
 *  Data addressed by an atomic swap operation is clearly volatile, so we can't remove
 *  the volatile qualification from the parameter list. Unfortunately tasking's intrinsic
 *  function __swap doesn't have a volatile qualification for this parameter, so we cast
 *  it away. This cast has no effect on the resulting code: A SWAP instruction will be emitted.
 *
 * MISRAC2012-5) Deviated Rule: 11.3 (required)
 *  A cast should not be performed between a pointer to object type and a different pointer to object type.
 *
 * Reason:
 *  We aren't allowed to use primitive typenames which don't indicate size and signedness of a type.
 *  Therefore we use mk_uint32_t in our atomic swap function.
 *  Unfortunately tasking's intrinsic function __swap uses a pointer to an unsigned int, so we have to
 *  cast the pointer. This cast has no effect on the resulting code.
 *
 * MISRAC2012-6) Deviated Rule: 1.2 (required)
 *  Language extensions should not be used.
 *
 * Reason:
 *  This file is compiler specific and part of the compiler abstraction.
 *  Therefore using language extensions here is not an issue.
 *
 * MISRAC2012-7) Deviated Rule: D4.3 (required)
 *  Assembly language shall be encapsulated and isolated.
 *
 * Reason:
 *  The purpose of these functions is to encapsulate assembler instructions.
*/

/* CERT-C Deviation List
 *
 * CERTC-1) Deviated Rule: DCL.31
 *  Declare identifiers before using them
 *
 * Reason:
 *  __swap is an intrinsic function of the tasking compiler. We could use an
 *  inline assembler statement instead, but this would also cause a MISRA violation.
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_PREPROC_020]
 *  An #ifndef is not permitted to have an #else statement!
 *
 * Reason:
 *  We have to hide compiler specific __attribute__ keywords from the MISRA checkers,
 *  because some MISRA checkers aren't able to parse them (see comment).
*/

/* TOOLDIAG List of possible tool diagnostics
 *
 * TOOLDIAG-1) Possible diagnostic: InfiniteLoop
 *   Possible infinite loop
 *
 * Reason: MK_JumpToPanicFuncPtr must never return. It calls pfunc which also
 *  shall not return. For reasons of defensive programming and to safisty the
 *  compiler there is an endless loop in the end.
*/

#ifndef MK_TRICORE_COMPILER_TASKING_H
#define MK_TRICORE_COMPILER_TASKING_H

#include <public/TRICORE/Mk_TRICORE_cpu_characteristics.h>
#include <public/Mk_public_types.h>

#include <public/Mk_error.h> /* Required for MK_StartupPanicTailCall. */

/* Some MISRA checkers are not able to parse function prototypes having an attribute.
 * Therefore we hide this attribute from the MISRA checker (so they don't crash).
 * Using EB_STATIC_CHECK is allowed in compiler headers only,
 * because MISRA checkers are some kind of compilers.
*/
/* Deviation DCG-1 <+5> */
#ifndef EB_STATIC_CHECK
/* Function qualifier and attribute for inline functions
*/
#define MK_QUAL_INLINE	static inline

#ifndef MK_ASM
/* MK_ATTR_INLINE tells the compiler to inline a function.
*/
#define MK_ATTR_INLINE				__attribute__((always_inline))
#define MK_ATTR_INLINE_NORETURN		__attribute__((always_inline,noreturn))

/* MK_MFCR/MK_MTCR reads/writes the content of a core special function register.
*/
#define MK_MFCR(csfr)		__mfcr(csfr)
#define MK_MTCR(csfr, val)	do {		\
		__mtcr((csfr),(val));			\
		MK_ISYNC();						\
	} while(0)

/* Note: the cast to unsigned int* is needed here to avoid a tasking warning
 * (passing incompatible pointer types). This warning is even issued when
 * cast to mk_uint32_t*, which is actually the same.
*/
#define MK_TricoreAtomicModifyFlag(address, mask, value) __ldmst((unsigned int*)(address), (mask), (value))

#define MK_TricoreAtomicAndNot(address, mask) MK_TricoreAtomicModifyFlag((address), (mask), 0U)

/* this macro opens a new block and a local variable MK_TricoreAtomicOrValue to avoid repetition of
 * side-effects related to parameter value. For example, if it's called like "MK_TricoreAtomicOr(adr, val++)"
 * the post-increment shall happen only once.
*/
#define MK_TricoreAtomicOr(address, value) \
	do {\
		mk_uint32_t MK_TricoreAtomicOrValue;\
		MK_TricoreAtomicOrValue = (mk_uint32_t)(value);\
		MK_TricoreAtomicModifyFlag((address), MK_TricoreAtomicOrValue, MK_TricoreAtomicOrValue);\
	} while(0)

/* MK_Startup*TailCall() performs a tail call to the respective panic function. */
#define MK_StartupPanicTailCall(panicreason) MK_JumpToPanicFuncPtr(&MK_StartupPanic, (panicreason))
#define MK_PanicStopTailCall(panicreason) MK_JumpToPanicFuncPtr(&MK_PanicStop, (panicreason))

#endif /* MK_ASM */
#else /* EB_STATIC_CHECK */

/* Function qualifier and attribute for inline functions
*/
#define MK_QUAL_INLINE	static

/* MISRA checkers might not be able to parse attributes.
*/
#define MK_ATTR_INLINE
#define MK_ATTR_INLINE_NORETURN

/* Hide the __mfcr and __mtcr intrinsics from the MISRA checker.
*/
#define MK_MFCR(csfrid)				((mk_uint32_t)csfrid)
#define MK_MTCR(csfrid, val)		do { } while (0)

#endif /* EB_STATIC_CHECK */

#ifndef MK_ASM
/* Deviation MISRAC2012-1 <START>, MISRAC2012-6 <START>, MISRAC2012-7 <START> */
/* MK_DSYNC() executes a DSYNC instruction
*/
MK_QUAL_INLINE void MK_DSYNC(void) MK_ATTR_INLINE;
MK_QUAL_INLINE void MK_DSYNC(void)
{
	/* dsync */
	__asm(" dsync");
	return ;
}

/* MK_ISYNC() executes an ISYNC instruction
*/
MK_QUAL_INLINE void MK_ISYNC(void) MK_ATTR_INLINE;
MK_QUAL_INLINE void MK_ISYNC(void)
{
	/* isync */
	__asm(" isync");
	return ;
}

/* MK_MTA9() writes an address to register A9.
*/
MK_QUAL_INLINE void MK_MTA9(void *) MK_ATTR_INLINE;
MK_QUAL_INLINE void MK_MTA9(void *val)
{
	/* write val to register a9 */
	__asm("mov.aa a9,%0" : : "a" (val));
	return ;
}

/* MK_MFA9() yields the address stored in register A9.
*/
/* Deviation MISRAC2012-2 <+7> */
MK_QUAL_INLINE void *MK_MFA9(void) MK_ATTR_INLINE;
MK_QUAL_INLINE void *MK_MFA9(void)
{
	register void *mfa9Res;
	/* load register a9 into mfa9Res */
	__asm("mov.aa %0,a9" : "=a" (mfa9Res));
	return mfa9Res;
}

/* MK_CompilerMemBarrier() will make the compiler believe p is used here.
 * Since tasking treats embedded assembler as blackbox,
 * it doesn't know whether we read or write
 * or which kind of addressing we use.
*/
MK_QUAL_INLINE void MK_CompilerMemBarrier(const volatile void *) MK_ATTR_INLINE;
MK_QUAL_INLINE void MK_CompilerMemBarrier(const volatile void *p)
{
	/* touch p */
	__asm("     " : : "a"(p));
	return ;
}
/* Deviation MISRAC2012-1 <STOP>, MISRAC2012-6 <STOP>, MISRAC2012-7 <STOP> */

/* MK_AtomicSwap() atomically fetches the value stored at memory location 'addr'
 * and replaces its value by 'val'.
*/
/* Deviation MISRAC2012-4 <+5>, MISRAC2012-5 <+5> */
MK_QUAL_INLINE mk_uint32_t MK_AtomicSwap(volatile mk_uint32_t *, mk_uint32_t) MK_ATTR_INLINE;
MK_QUAL_INLINE mk_uint32_t MK_AtomicSwap(volatile mk_uint32_t *addr, mk_uint32_t val)
{
	/* Deviation MISRAC2012-3 <+1>, CERTC-1 <+1> */
	return (mk_uint32_t) __swap((mk_unsigned_t*)addr, (mk_unsigned_t)val);
}

/* MK_JumpToPanicFuncPtr() jumps to the given panic function, passing the given value. */
/* Deviation MISRAC2012-1 <START>, MISRAC2012-3 <START>, MISRAC2012-6 <START>, MISRAC2012-7 <START> */
MK_QUAL_INLINE void MK_JumpToPanicFuncPtr(void (*)(mk_panic_t), mk_panic_t) MK_ATTR_INLINE_NORETURN;
MK_QUAL_INLINE void MK_JumpToPanicFuncPtr(void (*pfunc)(mk_panic_t), mk_panic_t val)
{
	__asm(
		"mov d4, %1 \n\t"
		"ji %0 \n\t"
		:
		: "a" (pfunc), "d" (val)
		: "d4" );

	/* This shall never be reached. */
	/* Possible diagnostic TOOLDIAG-1 <1> */
#pragma warning 557
	for(;;)
	{
	}
#pragma warning default
}
/* Deviation MISRAC2012-1 <STOP>, MISRAC2012-3 <STOP>, MISRAC2012-6 <STOP>, MISRAC2012-7 <STOP> */

#endif /* MK_ASM */

#endif
/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
