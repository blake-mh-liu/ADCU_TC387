/* Mk_TRICORE_compiler_gnu.h
 *
 * This file defines macros to permit the microkernel to be compiled with the Gnu compiler (gcc)
 *
 * (c) Elektrobit Automotive GmbH
*/

/* MISRA-C:2012 Deviation List
 *
 * MISRAC2012-1) Deviated Rule: D4.3 (required)
 *  Assembly language shall be encapsulated and isolated.
 *
 * Reason:
 *  The purpose of this function is to encapsulate this assembler instruction.
 *
 * MISRAC2012-2) Deviated Rule: 9.1 (mandatory)
 *  The value of an object with automatic storage duration shall not be read
 *  before it has been set.
 *
 * Reason:
 *  Variable is set by the assembler instruction just before its usage.
 *
 * MISRAC2012-3) Deviated Rule: 20.10 (advisory)
 *  The # and ## preprocessor operators should not be used.
 *
 * Reason:
 *  The use of the operator # is necessary to create syntactically correct names.
 *
 * MISRAC2012-4) Deviated Rule: 20.12 (required)
 *  A macro parameter used as an operand to the # and ## operators, which is
 *  itself subject to further macro replacement, shall only be used as an
 *  operand to these operators.
 *
 * Reason:
 *  This use of the macro parameter, once directly and once in its expanded form,
 *  is intentional. The intention is to create a set of functions to get certain
 *  values from hardware. To have consistent naming and no code duplication,
 *  both forms of the macro parameter are required.
*/

/* DCG Deviations:
 *
 * DCG-1) Deviated Rule: [OS_C_COMPL_010:HIS_STMT]
 *  The code shall adhere to the [HISSRCMETRIC] Metrics.
 *  In function MK_CompilerMemBarrier: Value 0.0 of metric "stmt" is out of bounds (1..50).
 *
 * Reason:
 *  MK_CompilerMemBarrier is used to prevent the compiler from reordering accesses
 *  to a certain memory location. It does not have to result in actual code.
 *  Moreover this function has one (assembler) statement.
 *  In addition to that it doesn't affect code quality, if a function has no statements in it.
 *
 * DCG-2) Deviated Rule: [OS_PREPROC_020]
 *  An #ifndef is not permitted to have an #else statement!
 *
 * Reason:
 *  EB_STATIC_CHECK is used to hide compiler specific language extensions (like the __attribute__ keyword) from
 *  MISRA checkers, because some MISRA checkers aren't able to parse them.
 *  We have to check for EB_STATIC_CHECK using #ifndef, because this macro is defined by the test environment
 *  and is not defined for production code.
 *
 * DCG-3) Deviated Rule: [OS_PREPROC_020]
 *  This #ifndef directive contains preprocessor statements other than #define or #error!
 *
 * Reason:
 *  EB_STATIC_CHECK is used to hide compiler specific language extensions from
 *  MISRA checkers, because some MISRA checkers aren't able to parse them.
 *  We have to check for EB_STATIC_CHECK using #ifndef, because this macro is defined by the test environment
 *  and is not defined for production code.
*/

#ifndef MK_TRICORE_COMPILER_GNU_H
#define MK_TRICORE_COMPILER_GNU_H

#include <public/TRICORE/Mk_TRICORE_cpu_characteristics.h>
#include <private/Mk_tool.h>
#include <public/Mk_public_types.h>

/*	Macros for stringification with argument expansion
*/
#define MK__XSTR(s) MK__STR(s)
/* Deviation MISRAC2012-3 <+1> */
#define MK__STR(s) #s

/* This combination causes GCC to always inline the function without generating
 * a callable version of it.
 */
#define MK_QUAL_INLINE static __inline__

/* Some MISRA checkers are not able to parse function prototypes having an attribute.
 * Therefore we hide this attribute from the MISRA checker (so they don't crash).
 * Using EB_STATIC_CHECK is allowed in compiler headers only,
 * because MISRA checkers are some kind of compilers.
*/
/* Deviation DCG-2 <+5> */
#ifndef EB_STATIC_CHECK
#define MK_ATTR_INLINE	__attribute__((always_inline))
#else
#define MK_ATTR_INLINE
#endif

/* Deviation DCG-3 <+1> */
#ifndef EB_STATIC_CHECK
#ifndef MK_ASM
static __inline__
void MK_TricoreAtomicModifyFlag (mk_uint32_t volatile *addr, mk_uint32_t mask, mk_uint32_t value)
__attribute__((always_inline));

static __inline__
void MK_TricoreAtomicModifyFlag(mk_uint32_t volatile *addr, mk_uint32_t mask, mk_uint32_t value)
{
	/* regValue and regMask have to be passed as asm input,
	 * to make sure they live in their respective registers.
	 * Note that %d4 = %e4[31:0] and %d5 is %e4[63:32].
	 * A function, which is actually called, should get value (%d4) before mask (%d5).
	*/
	register mk_uint32_t regValue __asm__ ("%%d4");
	register mk_uint32_t regMask __asm__ ("%%d5");
	regMask = mask;
	regValue = value;
	__asm__ __volatile__ (
		"ldmst [%0]0, %%e4\n"
		: "=a"(addr)								/*output*/
		: "0" (addr), "d" (regMask), "d" (regValue)	/*input*/
		: "memory"									/*clobber*/
	);
}

#define MK_TricoreAtomicAndNot(address, mask) MK_TricoreAtomicModifyFlag((address), (mask), 0u)

static __inline__
void MK_TricoreAtomicOr(mk_uint32_t volatile *address, mk_uint32_t value)
__attribute__((always_inline));

static __inline__ void MK_TricoreAtomicOr(mk_uint32_t volatile *address, mk_uint32_t value)
{
	MK_TricoreAtomicModifyFlag(address, value, value);
}
#endif /* MK_ASM */

#endif /* EB_STATIC_CHECK */

#ifndef MK_ASM
/* MK_DSYNC() executes a DSYNC instruction
*/
/* Deviation MISRAC2012-1 <+5> */
MK_QUAL_INLINE void MK_DSYNC(void) MK_ATTR_INLINE;
MK_QUAL_INLINE void MK_DSYNC(void)
{
	__asm__ volatile (" dsync");
	return ;
}

/* MK_ISYNC() executes an ISYNC instruction
*/
/* Deviation MISRAC2012-1 <+5> */
MK_QUAL_INLINE void MK_ISYNC(void) MK_ATTR_INLINE;
MK_QUAL_INLINE void MK_ISYNC(void)
{
	__asm__ volatile (" isync");
	return ;
}
#endif

#ifndef MK_ASM

/* Now it gets ugly. We want to avoid braces in expressions, so we cannot
 * use gcc's _mfcr intrinsic, which also uses braces in the expression to
 * provide the return value. This prevents us from using a macro.
 *
 * Since the CSFR ID needs to be encoded into the mfcr instruction, we cannot
 * use an inline function either.
 *
 * The ugly solution: Define one inline function per CSFR, and define the
 * MK_MFCR macro such that it uses the provided CSFR ID (e.g. MK_PSW) to call
 * the corresponding inline function. This of course only works when the macro
 * is used with the MK_xxx CSFR constants, but that should be acceptable.
 */
/* Deviation MISRAC2012-3 <+3> */
#define MK_MFCR_FCTEMPLATE(CSFRID) \
MK_QUAL_INLINE mk_uint32_t MK_MFCR_ ##CSFRID(void) MK_ATTR_INLINE; \
MK_QUAL_INLINE mk_uint32_t MK_MFCR_ ##CSFRID(void) \
{ \
	register mk_uint32_t mfcrRes; \
	__asm__ volatile ("mfcr %0,%1" : "=d" (mfcrRes) : "i" (CSFRID)); \
	return mfcrRes; \
}

/* Deviation MISRAC2012-3 <+1> */
#define MK_MFCR(CSFRID) MK_MFCR_ ##CSFRID()
/* Deviation MISRAC2012-1 <START>, MISRAC2012-2 <START>, MISRAC2012-4 <START> */
MK_MFCR_FCTEMPLATE(MK_DCON0)
MK_MFCR_FCTEMPLATE(MK_PCON0)
MK_MFCR_FCTEMPLATE(MK_PSW)
MK_MFCR_FCTEMPLATE(MK_CORE_ID)
MK_MFCR_FCTEMPLATE(MK_DEADD)
MK_MFCR_FCTEMPLATE(MK_DIETR)
MK_MFCR_FCTEMPLATE(MK_DIEAR)
MK_MFCR_FCTEMPLATE(MK_PIETR)
MK_MFCR_FCTEMPLATE(MK_PIEAR)
MK_MFCR_FCTEMPLATE(MK_DSTR)
MK_MFCR_FCTEMPLATE(MK_DATR)
MK_MFCR_FCTEMPLATE(MK_PSTR)
/* Deviation MISRAC2012-1 <STOP>, MISRAC2012-2 <STOP>, MISRAC2012-4 <STOP> */

/* Deviation DCG-2 <+1> */
#ifndef EB_STATIC_CHECK
/* MK_MTCR writes the content of a core special function register.
*/
#define MK_MTCR(csfr, val) \
	do {																\
		register mk_uint32_t mtcrTmp = (val);							\
		__asm__ volatile ("mtcr "MK__XSTR(csfr)",%0" : : "d" (mtcrTmp));\
		MK_ISYNC();														\
	} while(0)

#else /* EB_STATIC_CHECK */

/* Hide access function for core registers from the MISRA checker.
*/
#define MK_MTCR(csfrid, val)		do { } while (0)

#endif /* !EB_STATIC_CHECK */

/* MK_MTA9() writes an address to register A9.
*/
/* Deviation MISRAC2012-1 <+4> */
MK_QUAL_INLINE void MK_MTA9(void *) MK_ATTR_INLINE;
MK_QUAL_INLINE void MK_MTA9(void *val)
{
	__asm__ volatile ("mov.aa %%a9, %0" : : "a" (val) : "a9" );
	return ;
}

/* MK_MFA9() yields the address stored in A9.
*/
/* Deviation MISRAC2012-1 <+6>, MISRAC2012-2 <+6> */
MK_QUAL_INLINE void* MK_MFA9(void) MK_ATTR_INLINE;
MK_QUAL_INLINE void* MK_MFA9(void)
{
	register void *mfa9Res;
	__asm__ volatile ("mov.aa %0,%%a9" : "=a" (mfa9Res));
	return mfa9Res;
}

/* MK_CompilerMemBarrier() - Memory barrier implementation
*/
/* Deviation DCG-1 <+6> */
/* Deviation MISRAC2012-1 <+5>, MISRAC2012-2 <+5> */
MK_QUAL_INLINE void MK_CompilerMemBarrier(const volatile void *) MK_ATTR_INLINE;
MK_QUAL_INLINE void MK_CompilerMemBarrier(const volatile void *unused_p)
{
	MK_PARAM_UNUSED(unused_p);
	__asm__ volatile("" ::: "memory");
	return ;
}

/* MK_AtomicSwap() atomically fetches the value stored at memory location 'addr'
 * and replaces its value by 'val'.
*/
/* Deviation MISRAC2012-1 <+4> */
MK_QUAL_INLINE mk_uint32_t MK_AtomicSwap(volatile mk_uint32_t *, mk_uint32_t) MK_ATTR_INLINE;
MK_QUAL_INLINE mk_uint32_t MK_AtomicSwap(volatile mk_uint32_t *addr, mk_uint32_t val)
{
	__asm__ volatile ("swap.w [%1]0, %0" : "=d" (val) : "a" (addr), "0" (val));
	return val;
}

#endif /* MK_ASM */


#endif

/* Editor settings - DO NOT DELETE
 * vi:set ts=4:
*/
